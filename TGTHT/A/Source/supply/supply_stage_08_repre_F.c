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
**���ƣ����ӽ׶�12��ȼ���临ѹ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_supply_stage08_repre_f_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://��ʼ
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_TANK_NUMBER;
			
			break;
		}
		
//----------------�жϸ�ѹ����������------------------------------------------------------

		//�жϸ�ѹ����������
		case STEP_08_F_REPRE_TANK_NUMBER:
		{
			TGTHT510_supply_stage08_repre_f_step_tank_number();
			
			break;
		}

//---------------------һ��ȼ���临ѹ---------------------------------------------
		
		//������ѹ���򿪸�ѹ������
		case STEP_08_F_REPRE_1TANK_LVT_VALVE_ON:
		{
			if(TGTHT510_supply_stage08_repre_f_step_1tank_lvt_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_1TANK_IS_REPRE_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ����
		case STEP_08_F_REPRE_1TANK_IS_REPRE_OVER:
		{
			if(TGTHT510_supply_stage08_repre_f_step_1tank_is_repre_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_1TANK_LVT_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ѹ�������رո�ѹ������
		case STEP_08_F_REPRE_1TANK_LVT_VALVE_OFF:
		{
			if(TGTHT510_supply_stage08_repre_f_step_1tank_lvt_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_1TANK_OUT_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��������ڷ���
		case STEP_08_F_REPRE_1TANK_OUT_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage08_repre_f_step_1tank_out_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_1TANK_DELAY;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�
		case STEP_08_F_REPRE_1TANK_DELAY:
		{
			if(TGTHT510_supply_stage08_repre_f_step_1tank_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_1TANK_IS_TANK_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�����ѹ�����ȶ���
		case STEP_08_F_REPRE_1TANK_IS_TANK_PRESSURE:
		{
			if(TGTHT510_supply_stage08_repre_f_step_1tank_is_tank_pressure_stable()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}

//---------------------����ȼ���临ѹ---------------------------------------------

		//������ѹ���򿪸�ѹ����������һ������
		case STEP_08_F_REPRE_2TANK_TANK1_LVT_VALVE_ON:
		{
			if(TGTHT510_supply_stage08_repre_f_step_2tank_tank1_lvt_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_2TANK_TANK1_IS_REPRE_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ��������һ������
		case STEP_08_F_REPRE_2TANK_TANK1_IS_REPRE_OVER:
		{
			if(TGTHT510_supply_stage08_repre_f_step_2tank_tank1_is_repre_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_2TANK_TANK1_LVT_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ѹ�������رո�ѹ����������һ������
		case STEP_08_F_REPRE_2TANK_TANK1_LVT_VALVE_OFF:
		{
			if(TGTHT510_supply_stage08_repre_f_step_2tank_tank1_lvt_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_2TANK_TANK1_OUT_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��������ڷ��ţ���һ������
		case STEP_08_F_REPRE_2TANK_TANK1_OUT_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage08_repre_f_step_2tank_tank1_out_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_2TANK_TANK1_DELAY;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�����һ������
		case STEP_08_F_REPRE_2TANK_TANK1_DELAY:
		{
			if(TGTHT510_supply_stage08_repre_f_step_2tank_tank1_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_2TANK_TANK1_IS_TANK_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�����ѹ�����ȶ��ԣ���һ������
		case STEP_08_F_REPRE_2TANK_TANK1_IS_TANK_PRESSURE:
		{
			if(TGTHT510_supply_stage08_repre_f_step_2tank_tank1_is_tank_pressure_stable()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_2TANK_TANK2_LVT_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//������ѹ���򿪸�ѹ���������ڶ�������
		case STEP_08_F_REPRE_2TANK_TANK2_LVT_VALVE_ON:
		{
			if(TGTHT510_supply_stage08_repre_f_step_2tank_tank2_lvt_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_2TANK_TANK2_IS_REPRE_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ�������ڶ�������
		case STEP_08_F_REPRE_2TANK_TANK2_IS_REPRE_OVER:
		{
			if(TGTHT510_supply_stage08_repre_f_step_2tank_tank2_is_repre_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_2TANK_TANK2_LVT_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ѹ�������رո�ѹ���������ڶ�������
		case STEP_08_F_REPRE_2TANK_TANK2_LVT_VALVE_OFF:
		{
			if(TGTHT510_supply_stage08_repre_f_step_2tank_tank2_lvt_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_2TANK_TANK2_OUT_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��������ڷ��ţ��ڶ�������
		case STEP_08_F_REPRE_2TANK_TANK2_OUT_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage08_repre_f_step_2tank_tank2_out_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_2TANK_TANK2_DELAY;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ����ڶ�������
		case STEP_08_F_REPRE_2TANK_TANK2_DELAY:
		{
			if(TGTHT510_supply_stage08_repre_f_step_2tank_tank2_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_2TANK_TANK2_IS_TANK_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�����ѹ�����ȶ��ԣ��ڶ�������
		case STEP_08_F_REPRE_2TANK_TANK2_IS_TANK_PRESSURE:
		{
			if(TGTHT510_supply_stage08_repre_f_step_2tank_tank1_is_tank_pressure_stable()==TRUE)
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
**���ƣ��жϸ�ѹ����������
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

void TGTHT510_supply_stage08_repre_f_step_tank_number(void)
{
	if(TGTHT510_supply_decode_par.number_tank_F==1)
	{
		TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_1TANK_LVT_VALVE_ON;
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
	
	else if((TGTHT510_supply_decode_par.number_tank_F==2)||\
	(TGTHT510_supply_decode_par.number_tank_F==3))
	{
		TGTHT510_supply_ctrl.step=STEP_08_F_REPRE_2TANK_TANK1_LVT_VALVE_ON;
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
		
	}
	
	else
	{
		TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
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

uint16 TGTHT510_supply_stage08_repre_f_step_1tank_lvt_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_1TANK_LVT_VALVE_ON;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_1TANK_LVT_VALVE_ON:
		{
			TGTHT510_supply_common_repre_lvt_valve_on(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_1TANK_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_1TANK_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0003_F_REPRE_1TANK_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_08_0003_F_REPRE_1TANK_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0004_F_REPRE_1TANK_IS_LVT_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0004_F_REPRE_1TANK_IS_LVT_VALVE_ON:
		{
			if(TGTHT510_supply_common_repre_is_lvt_valve_on(REPRE_TANK_F,FIRST_TANK)==TRUE)
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

uint16 TGTHT510_supply_stage08_repre_f_step_1tank_is_repre_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_1TANK_IS_REPRE_OVER;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_1TANK_IS_REPRE_OVER:
		{
			if(TGTHT510_supply_common_repre_is_repre_over(REPRE_TANK_F,FIRST_TANK)==TRUE)
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

uint16 TGTHT510_supply_stage08_repre_f_step_1tank_lvt_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_1TANK_LVT_VALVE_OFF;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_1TANK_LVT_VALVE_OFF:
		{
			TGTHT510_supply_common_repre_lvt_valve_off(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_1TANK_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_1TANK_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0003_F_REPRE_1TANK_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_08_0003_F_REPRE_1TANK_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0004_F_REPRE_1TANK_IS_LVT_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0004_F_REPRE_1TANK_IS_LVT_VALVE_OFF:
		{
			if(TGTHT510_supply_common_repre_is_lvt_valve_off(REPRE_TANK_F,FIRST_TANK)==TRUE)
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

uint16 TGTHT510_supply_stage08_repre_f_step_1tank_out_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO1:
		{
			TGTHT510_supply_common_repre_out_tank_valve_on(REPRE_TANK_F,FIRST_TANK,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_1TANK_1MIN_START_NO3;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_1TANK_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0003_F_REPRE_1TANK_IS_1MIN_NO3;
			
			break;
		}
		
		case COMMAND_08_0003_F_REPRE_1TANK_IS_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0004_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0004_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO1:
		{
			if(TGTHT510_supply_common_repre_is_out_tank_valve_on(REPRE_TANK_F,FIRST_TANK,1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0005_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO2;
			}
			
			else
			{
				//�ƽ�ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_ON);
				//TGTHT510_supply_ctrl.command=COMMAND_08_0005_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO2;
			}
			
			break;
		}
		
		case COMMAND_08_0005_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_repre_out_tank_valve_on(REPRE_TANK_F,FIRST_TANK,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0006_F_REPRE_1TANK_1MIN_START_NO4;
			
			break;
		}
		
		case COMMAND_08_0006_F_REPRE_1TANK_1MIN_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0007_F_REPRE_1TANK_IS_1MIN_NO4;
			
			break;
		}
		
		case COMMAND_08_0007_F_REPRE_1TANK_IS_1MIN_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0008_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0008_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_repre_is_out_tank_valve_on(REPRE_TANK_F,FIRST_TANK,2)==TRUE)
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

uint16 TGTHT510_supply_stage08_repre_f_step_1tank_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_1TANK_DELAY_START_NO1;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_1TANK_DELAY_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_1TANK_IS_DELAY_NO1;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_1TANK_IS_DELAY_NO1:
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

uint16 TGTHT510_supply_stage08_repre_f_step_1tank_is_tank_pressure_stable(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_1TANK_TANK_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_1TANK_TANK_PRESSURE_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_1TANK_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_1TANK_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0003_F_REPRE_1TANK_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_08_0003_F_REPRE_1TANK_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0004_F_REPRE_1TANK_TANK_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0004_F_REPRE_1TANK_TANK_PRESSURE_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0005_F_REPRE_1TANK_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_08_0005_F_REPRE_1TANK_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0006_F_REPRE_1TANK_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_08_0006_F_REPRE_1TANK_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0007_F_REPRE_1TANK_TANK_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0007_F_REPRE_1TANK_TANK_PRESSURE_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0008_F_REPRE_1TANK_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_08_0008_F_REPRE_1TANK_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0009_F_REPRE_1TANK_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_08_0009_F_REPRE_1TANK_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0010_F_REPRE_1TANK_TANK_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0010_F_REPRE_1TANK_TANK_PRESSURE_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0011_F_REPRE_1TANK_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_08_0011_F_REPRE_1TANK_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0012_F_REPRE_1TANK_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_08_0012_F_REPRE_1TANK_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0013_F_REPRE_1TANK_TANK_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0013_F_REPRE_1TANK_TANK_PRESSURE_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0014_F_REPRE_1TANK_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_08_0014_F_REPRE_1TANK_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0015_F_REPRE_1TANK_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_08_0015_F_REPRE_1TANK_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0016_F_REPRE_1TANK_TANK_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0016_F_REPRE_1TANK_TANK_PRESSURE_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0017_F_REPRE_1TANK_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_08_0017_F_REPRE_1TANK_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0018_F_REPRE_1TANK_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_08_0018_F_REPRE_1TANK_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0019_F_REPRE_1TANK_TANK_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0019_F_REPRE_1TANK_TANK_PRESSURE_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0020_F_REPRE_1TANK_IS_PRESSURE_STABLE;
			
			break;
		}
		
		case COMMAND_08_0020_F_REPRE_1TANK_IS_PRESSURE_STABLE:
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


/******************************************************************************************
**���ƣ�������ѹ���򿪸�ѹ����������һ������
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

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank1_lvt_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_2TANK_TANK1_LVT_VALVE_ON;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_2TANK_TANK1_LVT_VALVE_ON:
		{
			TGTHT510_supply_common_repre_lvt_valve_on(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_2TANK_TANK1_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_2TANK_TANK1_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0003_F_REPRE_2TANK_TANK1_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_08_0003_F_REPRE_2TANK_TANK1_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0004_F_REPRE_2TANK_TANK1_IS_LVT_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0004_F_REPRE_2TANK_TANK1_IS_LVT_VALVE_ON:
		{
			if(TGTHT510_supply_common_repre_is_lvt_valve_on(REPRE_TANK_F,FIRST_TANK)==TRUE)
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
**���ƣ�ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ��������һ������
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

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank1_is_repre_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_2TANK_TANK1_IS_REPRE_OVER;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_2TANK_TANK1_IS_REPRE_OVER:
		{
			if(TGTHT510_supply_common_repre_is_repre_over(REPRE_TANK_F,FIRST_TANK)==TRUE)
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
**���ƣ���ѹ�������رո�ѹ����������һ������
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

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank1_lvt_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_2TANK_TANK1_LVT_VALVE_OFF;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_2TANK_TANK1_LVT_VALVE_OFF:
		{
			TGTHT510_supply_common_repre_lvt_valve_off(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_2TANK_TANK1_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_2TANK_TANK1_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0003_F_REPRE_2TANK_TANK1_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_08_0003_F_REPRE_2TANK_TANK1_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0004_F_REPRE_2TANK_TANK1_IS_LVT_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0004_F_REPRE_2TANK_TANK1_IS_LVT_VALVE_OFF:
		{
			if(TGTHT510_supply_common_repre_is_lvt_valve_off(REPRE_TANK_F,FIRST_TANK)==TRUE)
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
**���ƣ���������ڷ��ţ���һ������
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

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank1_out_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_2TANK_TANK1_OUT_TANK_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_2TANK_TANK1_OUT_TANK_VALVE_ON_NO1:
		{
			TGTHT510_supply_common_repre_out_tank_valve_on(REPRE_TANK_F,FIRST_TANK,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_2TANK_TANK1_1MIN_START_NO3;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_2TANK_TANK1_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0003_F_REPRE_2TANK_TANK1_IS_1MIN_NO3;
			
			break;
		}
		
		case COMMAND_08_0003_F_REPRE_2TANK_TANK1_IS_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0004_F_REPRE_2TANK_TANK1_IS_OUT_TANK_VALVE_ON_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0004_F_REPRE_2TANK_TANK1_IS_OUT_TANK_VALVE_ON_NO1:
		{
			if(TGTHT510_supply_common_repre_is_out_tank_valve_on(REPRE_TANK_F,FIRST_TANK,1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0005_F_REPRE_2TANK_TANK1_OUT_TANK_VALVE_ON_NO2;
			}
			
			else
			{
				//�ƽ�ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_ON);
				//TGTHT510_supply_ctrl.command=COMMAND_08_0005_F_REPRE_2TANK_TANK1_OUT_TANK_VALVE_ON_NO2;
			}
			
			break;
		}
		
		case COMMAND_08_0005_F_REPRE_2TANK_TANK1_OUT_TANK_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_repre_out_tank_valve_on(REPRE_TANK_F,FIRST_TANK,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0006_F_REPRE_2TANK_TANK1_1MIN_START_NO4;
			
			break;
		}
		
		case COMMAND_08_0006_F_REPRE_2TANK_TANK1_1MIN_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0007_F_REPRE_2TANK_TANK1_IS_1MIN_NO4;
			
			break;
		}
		
		case COMMAND_08_0007_F_REPRE_2TANK_TANK1_IS_1MIN_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0008_F_REPRE_2TANK_TANK1_IS_OUT_TANK_VALVE_ON_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0008_F_REPRE_2TANK_TANK1_IS_OUT_TANK_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_repre_is_out_tank_valve_on(REPRE_TANK_F,FIRST_TANK,2)==TRUE)
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
**���ƣ���ʱ�ȴ�����һ������
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

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank1_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_2TANK_TANK1_DELAY_START_NO1;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_2TANK_TANK1_DELAY_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_2TANK_TANK1_IS_DELAY_NO1;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_2TANK_TANK1_IS_DELAY_NO1:
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
**���ƣ��ж�����ѹ�����ȶ��ԣ���һ������
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

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank1_is_tank_pressure_stable(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_2TANK_TANK1_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_2TANK_TANK1_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0003_F_REPRE_2TANK_TANK1_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_08_0003_F_REPRE_2TANK_TANK1_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0004_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0004_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0005_F_REPRE_2TANK_TANK1_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_08_0005_F_REPRE_2TANK_TANK1_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0006_F_REPRE_2TANK_TANK1_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_08_0006_F_REPRE_2TANK_TANK1_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0007_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0007_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0008_F_REPRE_2TANK_TANK1_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_08_0008_F_REPRE_2TANK_TANK1_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0009_F_REPRE_2TANK_TANK1_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_08_0009_F_REPRE_2TANK_TANK1_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0010_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0010_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0011_F_REPRE_2TANK_TANK1_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_08_0011_F_REPRE_2TANK_TANK1_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0012_F_REPRE_2TANK_TANK1_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_08_0012_F_REPRE_2TANK_TANK1_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0013_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0013_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0014_F_REPRE_2TANK_TANK1_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_08_0014_F_REPRE_2TANK_TANK1_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0015_F_REPRE_2TANK_TANK1_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_08_0015_F_REPRE_2TANK_TANK1_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0016_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0016_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0017_F_REPRE_2TANK_TANK1_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_08_0017_F_REPRE_2TANK_TANK1_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0018_F_REPRE_2TANK_TANK1_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_08_0018_F_REPRE_2TANK_TANK1_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0019_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0019_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0020_F_REPRE_2TANK_TANK1_IS_PRESSURE_STABLE;
			
			break;
		}
		
		case COMMAND_08_0020_F_REPRE_2TANK_TANK1_IS_PRESSURE_STABLE:
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


/******************************************************************************************
**���ƣ�������ѹ���򿪸�ѹ���������ڶ�������
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

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank2_lvt_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_2TANK_TANK2_LVT_VALVE_ON;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_2TANK_TANK2_LVT_VALVE_ON:
		{
			TGTHT510_supply_common_repre_lvt_valve_on(REPRE_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_2TANK_TANK2_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_2TANK_TANK2_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0003_F_REPRE_2TANK_TANK2_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_08_0003_F_REPRE_2TANK_TANK2_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0004_F_REPRE_2TANK_TANK2_IS_LVT_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0004_F_REPRE_2TANK_TANK2_IS_LVT_VALVE_ON:
		{
			if(TGTHT510_supply_common_repre_is_lvt_valve_on(REPRE_TANK_F,SECOND_TANK)==TRUE)
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
**���ƣ�ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ�������ڶ�������
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

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank2_is_repre_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_2TANK_TANK2_IS_REPRE_OVER;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_2TANK_TANK2_IS_REPRE_OVER:
		{
			if(TGTHT510_supply_common_repre_is_repre_over(REPRE_TANK_F,SECOND_TANK)==TRUE)
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
**���ƣ���ѹ�������رո�ѹ���������ڶ�������
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

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank2_lvt_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_2TANK_TANK2_LVT_VALVE_OFF;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_2TANK_TANK2_LVT_VALVE_OFF:
		{
			TGTHT510_supply_common_repre_lvt_valve_off(REPRE_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_2TANK_TANK2_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_2TANK_TANK2_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0003_F_REPRE_2TANK_TANK2_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_08_0003_F_REPRE_2TANK_TANK2_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0004_F_REPRE_2TANK_TANK2_IS_LVT_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0004_F_REPRE_2TANK_TANK2_IS_LVT_VALVE_OFF:
		{
			if(TGTHT510_supply_common_repre_is_lvt_valve_off(REPRE_TANK_F,SECOND_TANK)==TRUE)
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
**���ƣ���������ڷ��ţ��ڶ�������
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

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank2_out_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_2TANK_TANK2_OUT_TANK_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_2TANK_TANK2_OUT_TANK_VALVE_ON_NO1:
		{
			TGTHT510_supply_common_repre_out_tank_valve_on(REPRE_TANK_F,SECOND_TANK,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_2TANK_TANK2_1MIN_START_NO3;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_2TANK_TANK2_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0003_F_REPRE_2TANK_TANK2_IS_1MIN_NO3;
			
			break;
		}
		
		case COMMAND_08_0003_F_REPRE_2TANK_TANK2_IS_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0004_F_REPRE_2TANK_TANK2_IS_OUT_TANK_VALVE_ON_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0004_F_REPRE_2TANK_TANK2_IS_OUT_TANK_VALVE_ON_NO1:
		{
			if(TGTHT510_supply_common_repre_is_out_tank_valve_on(REPRE_TANK_F,SECOND_TANK,1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0005_F_REPRE_2TANK_TANK2_OUT_TANK_VALVE_ON_NO2;
			}
			
			else
			{
				//�ƽ�ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_ON);
				//TGTHT510_supply_ctrl.command=COMMAND_08_0005_F_REPRE_2TANK_TANK2_OUT_TANK_VALVE_ON_NO2;
			}
			
			break;
		}
		
		case COMMAND_08_0005_F_REPRE_2TANK_TANK2_OUT_TANK_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_repre_out_tank_valve_on(REPRE_TANK_F,SECOND_TANK,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0006_F_REPRE_2TANK_TANK2_1MIN_START_NO4;
			
			break;
		}
		
		case COMMAND_08_0006_F_REPRE_2TANK_TANK2_1MIN_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0007_F_REPRE_2TANK_TANK2_IS_1MIN_NO4;
			
			break;
		}
		
		case COMMAND_08_0007_F_REPRE_2TANK_TANK2_IS_1MIN_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0008_F_REPRE_2TANK_TANK2_IS_OUT_TANK_VALVE_ON_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0008_F_REPRE_2TANK_TANK2_IS_OUT_TANK_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_repre_is_out_tank_valve_on(REPRE_TANK_F,SECOND_TANK,2)==TRUE)
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
**���ƣ���ʱ�ȴ�����һ������
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

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank2_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_2TANK_TANK2_DELAY_START_NO1;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_2TANK_TANK2_DELAY_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_2TANK_TANK2_IS_DELAY_NO1;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_2TANK_TANK2_IS_DELAY_NO1:
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
**���ƣ��ж�����ѹ�����ȶ��ԣ��ڶ�������
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

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank2_is_tank_pressure_stable(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_08_0001_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_08_0001_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0002_F_REPRE_2TANK_TANK2_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_08_0002_F_REPRE_2TANK_TANK2_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0003_F_REPRE_2TANK_TANK2_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_08_0003_F_REPRE_2TANK_TANK2_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0004_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0004_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0005_F_REPRE_2TANK_TANK2_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_08_0005_F_REPRE_2TANK_TANK2_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0006_F_REPRE_2TANK_TANK2_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_08_0006_F_REPRE_2TANK_TANK2_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0007_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0007_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0008_F_REPRE_2TANK_TANK2_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_08_0008_F_REPRE_2TANK_TANK2_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0009_F_REPRE_2TANK_TANK2_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_08_0009_F_REPRE_2TANK_TANK2_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0010_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0010_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0011_F_REPRE_2TANK_TANK2_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_08_0011_F_REPRE_2TANK_TANK2_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0012_F_REPRE_2TANK_TANK2_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_08_0012_F_REPRE_2TANK_TANK2_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0013_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0013_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0014_F_REPRE_2TANK_TANK2_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_08_0014_F_REPRE_2TANK_TANK2_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0015_F_REPRE_2TANK_TANK2_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_08_0015_F_REPRE_2TANK_TANK2_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0016_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0016_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0017_F_REPRE_2TANK_TANK2_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_08_0017_F_REPRE_2TANK_TANK2_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0018_F_REPRE_2TANK_TANK2_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_08_0018_F_REPRE_2TANK_TANK2_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_08_0019_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_08_0019_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_08_0020_F_REPRE_2TANK_TANK2_IS_PRESSURE_STABLE;
			
			break;
		}
		
		case COMMAND_08_0020_F_REPRE_2TANK_TANK2_IS_PRESSURE_STABLE:
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


/******************************************************************************************
**����: ͨ�ú���-������ѹ���򿪸�ѹ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
�������򷵻�TRUE��
���򷵻�FALSE
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_common_repre_lvt_valve_on(uint16 repre_kind,uint16 tank_sequence)
{
	if(repre_kind==REPRE_TANK_F)//ȼ���临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				TGTHT510_supply_main_lvt_set(LVt2K);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				TGTHT510_supply_main_lvt_set(LVt4K);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				TGTHT510_supply_main_lvt_set(LVt6K);
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				TGTHT510_supply_main_lvt_set(LVt2K);
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				TGTHT510_supply_main_lvt_set(LVt4K);
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				TGTHT510_supply_main_lvt_set(LVt6K);
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				TGTHT510_supply_main_lvt_set(LVt2K);
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				TGTHT510_supply_main_lvt_set(LVt4K);
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				TGTHT510_supply_main_lvt_set(LVt6K);
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else
		{
			asm("nop;");
		}

	}
	
	else if(repre_kind==REPRE_TANK_O)//�����临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				TGTHT510_supply_main_lvt_set(LVt1K);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				TGTHT510_supply_main_lvt_set(LVt3K);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				TGTHT510_supply_main_lvt_set(LVt5K);
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				TGTHT510_supply_main_lvt_set(LVt1K);
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				TGTHT510_supply_main_lvt_set(LVt3K);
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				TGTHT510_supply_main_lvt_set(LVt5K);
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				TGTHT510_supply_main_lvt_set(LVt1K);
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				TGTHT510_supply_main_lvt_set(LVt3K);
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				TGTHT510_supply_main_lvt_set(LVt5K);
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else
		{
			asm("nop;");
		}
		
	}
	
	else
	{
		asm("nop;");
	}

}


/******************************************************************************************
**����: ͨ�ú���-�ж�������ѹ���򿪸�ѹ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
�������򷵻�TRUE��
���򷵻�FALSE
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_common_repre_is_lvt_valve_on(uint16 repre_kind,uint16 tank_sequence)
{
	if(repre_kind==REPRE_TANK_F)//ȼ���临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt02,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt04,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt06,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt02,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt04,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt06,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt02,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt04,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt06,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else
		{
			return FALSE;
		}

	}
	
	else if(repre_kind==REPRE_TANK_O)//�����临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt01,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt03,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt05,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt01,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt03,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt05,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt01,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt03,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt05,VALVE_ON)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else
	{
		return FALSE;
	}

}

/******************************************************************************************
**����: ͨ�ú���-������ѹ���رո�ѹ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
�������򷵻�TRUE��
���򷵻�FALSE
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_common_repre_lvt_valve_off(uint16 repre_kind,uint16 tank_sequence)
{
	if(repre_kind==REPRE_TANK_F)//ȼ���临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				TGTHT510_supply_main_lvt_set(LVt2G);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				TGTHT510_supply_main_lvt_set(LVt4G);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				TGTHT510_supply_main_lvt_set(LVt6G);
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				TGTHT510_supply_main_lvt_set(LVt2G);
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				TGTHT510_supply_main_lvt_set(LVt4G);
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				TGTHT510_supply_main_lvt_set(LVt6G);
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				TGTHT510_supply_main_lvt_set(LVt2G);
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				TGTHT510_supply_main_lvt_set(LVt4G);
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				TGTHT510_supply_main_lvt_set(LVt6G);
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else
		{
			asm("nop;");
		}

	}
	
	else if(repre_kind==REPRE_TANK_O)//�����临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				TGTHT510_supply_main_lvt_set(LVt1G);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				TGTHT510_supply_main_lvt_set(LVt3G);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				TGTHT510_supply_main_lvt_set(LVt5G);
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				TGTHT510_supply_main_lvt_set(LVt1G);
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				TGTHT510_supply_main_lvt_set(LVt3G);
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				TGTHT510_supply_main_lvt_set(LVt5G);
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				TGTHT510_supply_main_lvt_set(LVt1G);
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				TGTHT510_supply_main_lvt_set(LVt3G);
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				TGTHT510_supply_main_lvt_set(LVt5G);
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else
		{
			asm("nop;");
		}
		
	}
	
	else
	{
		asm("nop;");
	}

}

/******************************************************************************************
**����: ͨ�ú���-�ж�������ѹ���رո�ѹ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
�������򷵻�TRUE��
���򷵻�FALSE
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_common_repre_is_lvt_valve_off(uint16 repre_kind,uint16 tank_sequence)
{
	if(repre_kind==REPRE_TANK_F)//ȼ���临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt02,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt04,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt06,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt02,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt04,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt06,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt02,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt04,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt06,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else
		{
			return FALSE;
		}

	}
	
	else if(repre_kind==REPRE_TANK_O)//�����临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt01,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt03,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt05,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt01,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt03,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt05,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt01,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt03,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_main_lvt_get(STATE_LVt05,VALVE_OFF)==TRUE)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else
	{
		return FALSE;
	}

}


/******************************************************************************************
**����: ͨ�ú���-��������ڷ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
�������򷵻�TRUE��
���򷵻�FALSE
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_common_repre_out_tank_valve_on(uint16 repre_kind,uint16 tank_sequence,uint16 n)
{
	if(repre_kind==REPRE_TANK_F)//ȼ���临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt32K);
				}
				
				else if(n=2)
				{
					asm("nop;");
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt28K);
				}
				
				else if(n=2)
				{
					TGTHT510_supply_main_lvt_set(LVt30K);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt34K);
				}
				
				else if(n=2)
				{
					asm("nop;");
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt32K);
				}
				
				else if(n=2)
				{
					asm("nop;");
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt28K);
				}
				
				else if(n=2)
				{
					TGTHT510_supply_main_lvt_set(LVt30K);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt34K);
				}
				
				else if(n=2)
				{
					asm("nop;");
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt32K);
				}
				
				else if(n=2)
				{
					asm("nop;");
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt28K);
				}
				
				else if(n=2)
				{
					TGTHT510_supply_main_lvt_set(LVt30K);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt34K);
				}
				
				else if(n=2)
				{
					asm("nop;");
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else
		{
			asm("nop;");
		}

	}
	
	else if(repre_kind==REPRE_TANK_O)//�����临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt31K);
				}
				
				else if(n=2)
				{
					asm("nop;");
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt27K);
				}
				
				else if(n=2)
				{
					TGTHT510_supply_main_lvt_set(LVt29K);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt33K);
				}
				
				else if(n=2)
				{
					asm("nop;");
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt31K);
				}
				
				else if(n=2)
				{
					asm("nop;");
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt27K);
				}
				
				else if(n=2)
				{
					TGTHT510_supply_main_lvt_set(LVt29K);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt33K);
				}
				
				else if(n=2)
				{
					asm("nop;");
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt31K);
				}
				
				else if(n=2)
				{
					asm("nop;");
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt27K);
				}
				
				else if(n=2)
				{
					TGTHT510_supply_main_lvt_set(LVt29K);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				if(n=1)
				{
					TGTHT510_supply_main_lvt_set(LVt33K);
				}
				
				else if(n=2)
				{
					asm("nop;");
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else
		{
			asm("nop;");
		}
		
	}
	
	else
	{
		asm("nop;");
	}

}


/******************************************************************************************
**����: ͨ�ú���-�жϿ�������ڷ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
�������򷵻�TRUE��
���򷵻�FALSE
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_common_repre_is_out_tank_valve_on(uint16 repre_kind,uint16 tank_sequence,uint16 n)
{
	if(repre_kind==REPRE_TANK_F)//ȼ���临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt32,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt28,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt30,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt34,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt32,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt28,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt30,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt34,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt32,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt28,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt30,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt34,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else
		{
			return FALSE;
		}

	}
	
	else if(repre_kind==REPRE_TANK_O)//�����临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt31,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt27,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt29,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt33,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt31,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt27,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt29,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt33,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt31,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt27,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt29,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				if(n=1)
				{
					if(TGTHT510_supply_main_lvt_get(STATE_LVt33,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(n=2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else
	{
		return FALSE;
	}

}


/******************************************************************************************
**����: ͨ�ú���-��ȡ����ѹ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
�������򷵻�TRUE��
���򷵻�FALSE
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_common_repre_tank_pressure_get(uint16 repre_kind,uint16 tank_sequence)
{
	uint16 pressure_tank;
	
	pressure_tank=0;
	
	if(repre_kind==REPRE_TANK_F)//ȼ���临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F1==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[13];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F1==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[19];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F2==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[15];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F2==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[21];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F3==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[17];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F3==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[23];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F1==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[13];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F1==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[19];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F2==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[15];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F2==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[21];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F3==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[17];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F3==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[23];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F1==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[13];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F1==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[19];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F2==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[15];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F2==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[21];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F3==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[17];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F3==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[23];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else
		{
			asm("nop;");
		}

	}
	
	else if(repre_kind==REPRE_TANK_O)//�����临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O1==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[12];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O1==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[18];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O2==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[14];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O2==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[20];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O3==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[16];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O3==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[22];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O1==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[12];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O1==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[18];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O2==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[14];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O2==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[20];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O3==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[16];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O3==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[22];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O1==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[12];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O1==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[18];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O2==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[14];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O2==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[20];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O3==DECODE_SENSOR_TANK_Z)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[16];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O3==DECODE_SENSOR_TANK_B)
				{
					pressure_tank=TGTHT510_1553B_data_TGTHT100[22];
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else
			{
				asm("nop;");
			}
		}
		
		else
		{
			asm("nop;");
		}
		
	}
	
	else
	{
		asm("nop;");
	}
	
	return pressure_tank;
}


/******************************************************************************************
**����: ͨ�ú���-�ж����临ѹ�Ƿ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
�������򷵻�TRUE��
���򷵻�FALSE
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_common_repre_is_repre_over(uint16 repre_kind,uint16 tank_sequence)
{
	uint16 pressure_tank;
	
	uint32 repre_time;
	
	TGTHT510_supply_time_stage_get(&repre_time);
	
	//ʱ�䳬��
	if(repre_time>=TGTHT510_supply_input_par.time_repre_max)
	{
		return TRUE;
	}
	
	pressure_tank=TGTHT510_supply_common_repre_tank_pressure_get(repre_kind,tank_sequence);//��ȡ����ѹ��
	
	if(repre_kind==REPRE_TANK_F)//ȼ���临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_F1)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_F2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_F3)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_F1)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_F2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_F3)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_F1)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_F2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_F3)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else
		{
			return FALSE;
		}

	}
	
	else if(repre_kind==REPRE_TANK_O)//�����临ѹ
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_O1)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_O2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_O3)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_O1)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_O2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_O3)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_O1)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_O2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				if(pressure_tank<=TGTHT510_supply_input_par.pressure_repre_O3)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else
	{
		return FALSE;
	}

}


/******************************************************************************************
**����: ͨ�ú���-�ж�����ѹ��ֵ�Ƿ��ȶ�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
�������򷵻�TRUE��
���򷵻�FALSE
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_common_repre_is_tank_pressure_stable(uint16 *p)
{
	uint16 n,i;
	
	n=0;
	
	for(i=0;i<=5;i++)
	{
		if((uint16)(abs(p[i+1]-p[i]))<=TGTHT510_supply_input_par.dp1_low)
		{
			n++;
		}
		
		else
		{
			asm("nop;");
		}
		
	}
	
	if((n>=5)&&(n<=6))
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

