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
**���ƣ����ӽ׶�1��ע�����������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_supply_stage20_blow_o_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://��ʼ
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_20_SUPPLY_BLOW_VALVE_ON;
			
			break;
		}
		
		//��·��������
		case STEP_20_SUPPLY_BLOW_VALVE_ON:
		{
			if(TGTHT510_supply_stage20_blow_o_step_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_20_SUPPLY_IS_HYCT_TIME;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ȴ�������Ϣ���߳�ʱ
		case STEP_20_SUPPLY_IS_HYCT_TIME:
		{
			if(TGTHT510_supply_stage20_blow_o_step_is_hyct_time()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_20_SUPPLY_BLOW_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��·�������ر�
		case STEP_20_SUPPLY_BLOW_VALVE_OFF:
		{
			if(TGTHT510_supply_stage20_blow_o_step_valve_off()==TRUE)
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
**���ƣ���·��������
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

uint16 TGTHT510_supply_stage20_blow_o_step_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_20_0001_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_20_0001_VALVE_ON_NO1:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0002_IS_VALVE_ON_NO1;
			
			break;
		}
		
		case COMMAND_20_0002_IS_VALVE_ON_NO1:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_O,1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0003_VALVE_ON_NO2;
			}
			
			else
			{
				//����ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_20_0003_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_O,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0004_IS_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_20_0004_IS_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_O,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0005_VALVE_ON_NO3;
			}
			
			else
			{
				//����ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_20_0005_VALVE_ON_NO3:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0006_IS_VALVE_ON_NO3;
			
			break;
		}
		
		case COMMAND_20_0006_IS_VALVE_ON_NO3:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_O,3)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0007_VALVE_ON_NO4;
			}
			
			else
			{
				//����ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_20_0007_VALVE_ON_NO4:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_O,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0008_IS_VALVE_ON_NO4;
			
			break;
		}
		
		case COMMAND_20_0008_IS_VALVE_ON_NO4:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_O,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0009_VALVE_ON_NO5;
			}
			
			else
			{
				//����ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_20_0009_VALVE_ON_NO5:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0010_IS_VALVE_ON_NO5;
			
			break;
		}
		
		case COMMAND_20_0010_IS_VALVE_ON_NO5:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_O,5)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//����ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
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
**���ƣ���·�������ر�
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

uint16 TGTHT510_supply_stage20_blow_o_step_is_hyct_time(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_20_0001_IS_HYCT_TIME;
			break;
		}
		
		case COMMAND_20_0001_IS_HYCT_TIME:
		{
			if(TGTHT510_supply_common_is_blow_over()==TRUE)
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
**���ƣ���·�������ر�
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

uint16 TGTHT510_supply_stage20_blow_o_step_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_20_0001_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_20_0001_VALVE_OFF_NO1:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0002_IS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_20_0002_IS_VALVE_OFF_NO1:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_O,1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0003_VALVE_OFF_NO2;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_20_0003_VALVE_OFF_NO2:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_O,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0004_IS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_20_0004_IS_VALVE_OFF_NO2:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_O,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0005_VALVE_OFF_NO3;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_20_0005_VALVE_OFF_NO3:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0006_IS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_20_0006_IS_VALVE_OFF_NO3:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_O,3)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0007_VALVE_OFF_NO4;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_20_0007_VALVE_OFF_NO4:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_O,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0008_IS_VALVE_OFF_NO4;
			
			break;
		}
		
		case COMMAND_20_0008_IS_VALVE_OFF_NO4:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_O,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0009_VALVE_OFF_NO5;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_20_0009_VALVE_OFF_NO5:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0010_IS_VALVE_OFF_NO5;
			
			break;
		}
		
		case COMMAND_20_0010_IS_VALVE_OFF_NO5:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_O,5)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0011_VALVE_OFF_NO6;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_20_0011_VALVE_OFF_NO6:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_O,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0012_IS_VALVE_OFF_NO6;
			
			break;
		}
		
		case COMMAND_20_0012_IS_VALVE_OFF_NO6:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_O,6)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
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




