/**
  ******************************************************************************
  * @file    TGTHT510_supply.c
  * @author  ����
  * @version V1.00
  * @date    20150626
  * @brief   �ռ�վ���Ĳ��ƽ�����������ģ��C�ļ�
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"


/*ȫ�ֱ���---------------------------------------------------------------------*/		

extern TGTHT510_supply_ctrl_TypeDef TGTHT510_supply_ctrl;

extern TGTHT510_supply_input_par_TypeDef TGTHT510_supply_input_par;

extern TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;

extern valvecontrol_TypeDef TGTHT510_valvecontrol_struct;	//���ſ��ƽṹ��
extern uint16 TGTHT510_1553B_data_TGTHT100[];				//ȫ�����飬�����ƽ�ң����·�г��¶Ȳ����������ݣ�89��
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[];		//ȫ�����飬�����ƽ�ң����·�и�֡A�¶����ݣ�65��
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[];		//ȫ�����飬�����ƽ�ң����·�и�֡B�¶����ݣ�65��
extern uint16 TGTHT510_1553B_data_TGTHT530[];				//ȫ�����飬����ѹ�������������ң�����ݣ�14��
extern uint16 TGTHT510_1553B_data_TGTHT520a[];				//ȫ�����飬�����ƽ���������������ң�⣬7��
extern uint16 TGTHT510_1553B_data_TGTHT520b[];				//ȫ�����飬�����ƽ���������������ң�⣬7��
extern uint16 TGTHT510_1553B_R_HYCT1100[];					//ȫ�����飬����������͵�ң������

uint16 temp_gloal[10];

/******************************************************************************************
**���ƣ�������ȼ���临ѹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_supply_stage11_repre_f_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://��ʼ
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_11_F_REPRE_1TANK_LVT_VALVE_ON;
			
			break;
		}
		
//---------------------������ȼ���临ѹ---------------------------------------------
		
		//������ѹ���򿪸�ѹ������
		case STEP_11_F_REPRE_1TANK_LVT_VALVE_ON:
		{
			if(TGTHT510_supply_stage11_repre_f_step_1tank_lvt_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_11_F_REPRE_1TANK_IS_REPRE_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ����
		case STEP_11_F_REPRE_1TANK_IS_REPRE_OVER:
		{
			if(TGTHT510_supply_stage11_repre_f_step_1tank_is_repre_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_11_F_REPRE_1TANK_LVT_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ѹ�������رո�ѹ������
		case STEP_11_F_REPRE_1TANK_LVT_VALVE_OFF:
		{
			if(TGTHT510_supply_stage11_repre_f_step_1tank_lvt_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_11_F_REPRE_1TANK_OUT_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��������ڷ���
		case STEP_11_F_REPRE_1TANK_OUT_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage11_repre_f_step_1tank_out_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_11_F_REPRE_1TANK_DELAY;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�
		case STEP_11_F_REPRE_1TANK_DELAY:
		{
			if(TGTHT510_supply_stage11_repre_f_step_1tank_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_11_F_REPRE_1TANK_IS_TANK_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�����ѹ�����ȶ���
		case STEP_11_F_REPRE_1TANK_IS_TANK_PRESSURE:
		{
			if(TGTHT510_supply_stage11_repre_f_step_1tank_is_tank_pressure_stable()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
	
//----------------------------------����--------------------------------------------------------------
	
		case STEP_END://����
		{
			TGTHT510_supply_ctrl.state=STATE_NONE;//����״̬������
			
			TGTHT510_supply_ctrl.stage=STAGE_00_NONE;//���ӽ׶Σ���
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//���Ӳ��裺��
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//����ָ���
			
			TGTHT510_supply_time_stage_end();
			
			break;
		}
		
		default:
		{
			break;
		}
	
	}
}


/******************************************************************************************
**���ƣ�������ѹ���򿪸�ѹ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������

��������ֵTRUE����ʾ��ǰ�������
��������ֵFALSE����ʾ��ǰ����δ����

-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_stage11_repre_f_step_1tank_lvt_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_11_0001_F_REPRE_1TANK_LVT_VALVE_ON;
			break;
		}
		
		case COMMAND_11_0001_F_REPRE_1TANK_LVT_VALVE_ON:
		{
			TGTHT510_supply_common_repre_lvt_valve_on(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0004_F_REPRE_1TANK_IS_LVT_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0004_F_REPRE_1TANK_IS_LVT_VALVE_ON:
		{
			if(TGTHT510_supply_common_repre_is_lvt_valve_on(REPRE_TANK_F,THIRD_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//�ƽ�ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_ON);
				//TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
			break;
		}
		
		default:
		{
			break;
		}

	}
	
	return return_state;	
}


/******************************************************************************************
**���ƣ�ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������

��������ֵTRUE����ʾ��ǰ�������
��������ֵFALSE����ʾ��ǰ����δ����

-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_stage11_repre_f_step_1tank_is_repre_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_11_0001_F_REPRE_1TANK_IS_REPRE_OVER;
			break;
		}
		
		case COMMAND_11_0001_F_REPRE_1TANK_IS_REPRE_OVER:
		{
			if(TGTHT510_supply_common_repre_is_repre_over(REPRE_TANK_F,THIRD_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
			break;
		}
		
		default:
		{
			break;
		}

		
	}
	
	return return_state;	
}


/******************************************************************************************
**���ƣ���ѹ�������رո�ѹ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������

��������ֵTRUE����ʾ��ǰ�������
��������ֵFALSE����ʾ��ǰ����δ����

-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_stage11_repre_f_step_1tank_lvt_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_11_0001_F_REPRE_1TANK_LVT_VALVE_OFF;
			break;
		}
		
		case COMMAND_11_0001_F_REPRE_1TANK_LVT_VALVE_OFF:
		{
			TGTHT510_supply_common_repre_lvt_valve_off(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0004_F_REPRE_1TANK_IS_LVT_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0004_F_REPRE_1TANK_IS_LVT_VALVE_OFF:
		{
			if(TGTHT510_supply_common_repre_is_lvt_valve_off(REPRE_TANK_F,THIRD_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//�ƽ�ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);
				//TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
			break;
		}
		
		default:
		{
			break;
		}

		
	}
	
	return return_state;	
}


/******************************************************************************************
**���ƣ���������ڷ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������

��������ֵTRUE����ʾ��ǰ�������
��������ֵFALSE����ʾ��ǰ����δ����

-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_stage11_repre_f_step_1tank_out_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_11_0001_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_11_0001_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO1:
		{
			TGTHT510_supply_common_repre_out_tank_valve_on(REPRE_TANK_F,THIRD_TANK,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO3;
			
			break;
		}
		
		case COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO3;
			
			break;
		}
		
		case COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0004_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0004_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO1:
		{
			if(TGTHT510_supply_common_repre_is_out_tank_valve_on(REPRE_TANK_F,THIRD_TANK,1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0005_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO2;
			}
			
			else
			{
				//�ƽ�ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_ON);
				//TGTHT510_supply_ctrl.command=COMMAND_11_0005_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO2;
			}
			
			break;
		}
		
		case COMMAND_11_0005_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_repre_out_tank_valve_on(REPRE_TANK_F,THIRD_TANK,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0006_F_REPRE_1TANK_1MIN_START_NO4;
			
			break;
		}
		
		case COMMAND_11_0006_F_REPRE_1TANK_1MIN_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0007_F_REPRE_1TANK_IS_1MIN_NO4;
			
			break;
		}
		
		case COMMAND_11_0007_F_REPRE_1TANK_IS_1MIN_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0008_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0008_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_repre_is_out_tank_valve_on(REPRE_TANK_F,THIRD_TANK,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//�ƽ�ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_ON);
				//TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
			break;
		}
		
		default:
		{
			break;
		}

		
	}
	
	return return_state;	
}


/******************************************************************************************
**���ƣ���ʱ�ȴ�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������

��������ֵTRUE����ʾ��ǰ�������
��������ֵFALSE����ʾ��ǰ����δ����

-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_stage11_repre_f_step_1tank_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_11_0001_F_REPRE_1TANK_DELAY_START_NO1;
			break;
		}
		
		case COMMAND_11_0001_F_REPRE_1TANK_DELAY_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0002_F_REPRE_1TANK_IS_DELAY_NO1;
			
			break;
		}
		
		case COMMAND_11_0002_F_REPRE_1TANK_IS_DELAY_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_delay_short)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
			break;
		}
		
		default:
		{
			break;
		}

		
	}
	
	return return_state;	
}


/******************************************************************************************
**���ƣ��ж�����ѹ�����ȶ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������

��������ֵTRUE����ʾ��ǰ�������
��������ֵFALSE����ʾ��ǰ����δ����

-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_stage11_repre_f_step_1tank_is_tank_pressure_stable(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_11_0001_F_REPRE_1TANK_TANK_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_11_0001_F_REPRE_1TANK_TANK_PRESSURE_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0002_F_REPRE_1TANK_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_11_0002_F_REPRE_1TANK_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0003_F_REPRE_1TANK_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_11_0003_F_REPRE_1TANK_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0004_F_REPRE_1TANK_TANK_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0004_F_REPRE_1TANK_TANK_PRESSURE_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0005_F_REPRE_1TANK_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_11_0005_F_REPRE_1TANK_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0006_F_REPRE_1TANK_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_11_0006_F_REPRE_1TANK_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0007_F_REPRE_1TANK_TANK_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0007_F_REPRE_1TANK_TANK_PRESSURE_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0008_F_REPRE_1TANK_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_11_0008_F_REPRE_1TANK_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0009_F_REPRE_1TANK_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_11_0009_F_REPRE_1TANK_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0010_F_REPRE_1TANK_TANK_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0010_F_REPRE_1TANK_TANK_PRESSURE_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0011_F_REPRE_1TANK_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_11_0011_F_REPRE_1TANK_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0012_F_REPRE_1TANK_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_11_0012_F_REPRE_1TANK_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0013_F_REPRE_1TANK_TANK_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0013_F_REPRE_1TANK_TANK_PRESSURE_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0014_F_REPRE_1TANK_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_11_0014_F_REPRE_1TANK_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0015_F_REPRE_1TANK_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_11_0015_F_REPRE_1TANK_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0016_F_REPRE_1TANK_TANK_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0016_F_REPRE_1TANK_TANK_PRESSURE_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0017_F_REPRE_1TANK_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_11_0017_F_REPRE_1TANK_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0018_F_REPRE_1TANK_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_11_0018_F_REPRE_1TANK_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0019_F_REPRE_1TANK_TANK_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0019_F_REPRE_1TANK_TANK_PRESSURE_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0020_F_REPRE_1TANK_IS_PRESSURE_STABLE;
			
			break;
		}
		
		case COMMAND_11_0020_F_REPRE_1TANK_IS_PRESSURE_STABLE:
		{
			if(TGTHT510_supply_common_repre_is_tank_pressure_stable(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//����ѹ�����ȶ�
				TGTHT510_supply_main_pause(ERRNO_TANK_PRESSURE_STABLE);
			}
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
			break;
		}
		
		default:
		{
			break;
		}

		
	}
	
	return return_state;	
}
































