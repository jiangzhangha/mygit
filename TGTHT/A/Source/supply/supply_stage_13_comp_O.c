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

extern TGTHT510_supply_time_TypeDef TGTHT510_supply_time;

extern TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;

extern valvecontrol_TypeDef TGTHT510_valvecontrol_struct;	//���ſ��ƽṹ��
extern uint16 TGTHT510_1553B_data_TGTHT100[];				//ȫ�����飬�����ƽ�ң����·�г��¶Ȳ����������ݣ�89��
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[];		//ȫ�����飬�����ƽ�ң����·�и�֡A�¶����ݣ�65��
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[];		//ȫ�����飬�����ƽ�ң����·�и�֡B�¶����ݣ�65��
extern uint16 TGTHT510_1553B_data_TGTHT530[];				//ȫ�����飬����ѹ�������������ң�����ݣ�14��
extern uint16 TGTHT510_1553B_data_TGTHT520a[];				//ȫ�����飬�����ƽ���������������ң�⣬7��
extern uint16 TGTHT510_1553B_data_TGTHT520b[];				//ȫ�����飬�����ƽ���������������ң�⣬7��
extern uint16 TGTHT510_1553B_R_HYCT1100[];					//ȫ�����飬����������͵�ң������

uint16 temp_global[10];//ȫ����ʱ��������

/******************************************************************************************
**���ƣ����ӽ׶�6
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_supply_stage13_comp_O_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://��ʼ
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_13_O_INIT_START_COOLER;
			
			break;
		}

//----------------------------------��ʼ���ý׶�------------------------------------------------------
		
		//����Һ��ù���
		case STEP_13_O_INIT_START_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_start_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_IS_COOLER_WORK;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ת���ж�Һ�乤���Ƿ�����
		case STEP_13_O_INIT_IS_COOLER_WORK:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_is_cooler_work()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_DELAY;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�ʱ��
		case STEP_13_O_INIT_DELAY:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ�����¶��Ƿ�����
		case STEP_13_O_INIT_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_TGTHT530_POWER_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������������ӵ�
		case STEP_13_O_INIT_TGTHT530_POWER_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_TGTHT530_power_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_COMPRESSOR_POWER_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ�����ӵ�
		case STEP_13_O_INIT_COMPRESSOR_POWER_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_compressor_power_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_ISOLATION;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������
		case STEP_13_O_INIT_ISOLATION:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_isolation()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_NUMBER_COMP_TANK;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϳ����������
		case STEP_13_O_INIT_NUMBER_COMP_TANK:
		{
			TGTHT510_supply_stage13_comp_O_init_step_number_comp_tank();
			
			break;
		}

//----------------------------------һ���������------------------------------------------------------

		//���������ѹ��·���ӷ���
		case STEP_13_O_1TANK_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_TIME_DELAY_A;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�ʱ��
		case STEP_13_O_1TANK_TIME_DELAY_A:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϿ��������ѹ��·���ӷ���
		case STEP_13_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_is_in_tank_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_IN_COMPRESSOR_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ�������ڷ���
		case STEP_13_O_1TANK_IN_COMPRESSOR_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_in_compressor_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_TIME_DELAY1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay1
		case STEP_13_O_1TANK_TIME_DELAY1:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_time_delay1()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_IS_IN_COMPRESSOR_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ��������ѹ���Ƿ�����
		case STEP_13_O_1TANK_IS_IN_COMPRESSOR_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_is_in_compressor_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_COMPRESSOR_START;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ѹ��������
		case STEP_13_O_1TANK_COMPRESSOR_START:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_compressor_start()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_TIME_DELAY_B;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�ʱ��
		case STEP_13_O_1TANK_TIME_DELAY_B:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ��������ѹ���Ƿ�����
		case STEP_13_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_is_out_compressor_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_OUT_COMPRESSOR_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ�������ڷ���
		case STEP_13_O_1TANK_OUT_COMPRESSOR_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_out_compressor_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_NUMBER_COMP_GAS;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϳ�����ƿ����
		case STEP_13_O_1TANK_NUMBER_COMP_GAS:
		{
			TGTHT510_supply_stage13_comp_O_1tank_step_number_comp_gas();
			
			break;
		}

//----------------------------------һ�����������һ����ƿ����----------------------------------------

		//������ƿ���ӷ���
		case STEP_13_O_1TANK_1GAS_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay2
		case STEP_13_O_1TANK_1GAS_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿѹ���Ƿ�����
		case STEP_13_O_1TANK_1GAS_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿ�����Ƿ����
		case STEP_13_O_1TANK_1GAS_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����·��ƿ���ӷ���
		case STEP_13_O_1TANK_1GAS_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_ISOLATION_FIRST;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
		case STEP_13_O_1TANK_1GAS_IS_ISOLATION_FIRST:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_isolation_first()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر���ѹ�������ڷ���
		case STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_out_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_ISOLATION_SECOND;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���
		case STEP_13_O_1TANK_1GAS_IS_ISOLATION_SECOND:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_isolation_second()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ѹ����ͣ��
		case STEP_13_O_1TANK_1GAS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ѹ����ͣ���Ƿ�����
		case STEP_13_O_1TANK_1GAS_IS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_BYPATH_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ������·������
		case STEP_13_O_1TANK_1GAS_BYPATH_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_bypath_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_TIME_DELAY_BYPATH;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_bypath
		case STEP_13_O_1TANK_1GAS_TIME_DELAY_BYPATH:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay_bypath()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ������·������
		case STEP_13_O_1TANK_1GAS_BYPATH_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_bypath_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر���ѹ�������ڷ��ţ��ڶ���
		case STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_out_compressor_valve_off2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر���ѹ�������ڷ���
		case STEP_13_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ؽ������ѹ��·���ӷ���
		case STEP_13_O_1TANK_1GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_SET_STATE_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����������״̬��
		case STEP_13_O_1TANK_1GAS_SET_STATE_GOOD:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_set_state_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ�����¶��Ƿ�����
		case STEP_13_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_NEED_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��
		case STEP_13_O_1TANK_1GAS_IS_NEED_COOLER_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_need_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_TIME_DELAY3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay3
		case STEP_13_O_1TANK_1GAS_TIME_DELAY3:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay3()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		/*
		//����Һ��ģ���л�����
		case STEP_13_O_1TANK_1GAS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
		case STEP_13_O_1TANK_1GAS_IS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		*/
		
		//Һ��ģ��ͣ��
		case STEP_13_O_1TANK_1GAS_COOLER_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COOLER_SET;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//Һ��ģ��״̬����
		case STEP_13_O_1TANK_1GAS_COOLER_SET:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_cooler_set()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COMPRESSOR_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ�����ϵ�
		case STEP_13_O_1TANK_1GAS_COMPRESSOR_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_compressor_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_TGTHT530_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������������ϵ�
		case STEP_13_O_1TANK_1GAS_TGTHT530_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_TGTHT530_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
				
				//�������������������������������������������������
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}

//----------------------------------һ�����������������ƿ����----------------------------------------
		
		//������ƿ���ӷ���---��һ����ƿ
		case STEP_13_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS1_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay2---��һ����ƿ
		case STEP_13_O_1TANK_2GAS_GAS1_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿѹ���Ƿ�����---��һ����ƿ
		case STEP_13_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS1_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿ�����Ƿ����---��һ����ƿ
		case STEP_13_O_1TANK_2GAS_GAS1_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����·��ƿ���ӷ���---��һ����ƿ
		case STEP_13_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//������ƿ���ӷ���---�ڶ�����ƿ
		case STEP_13_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS2_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
		case STEP_13_O_1TANK_2GAS_GAS2_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
		case STEP_13_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS2_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
		case STEP_13_O_1TANK_2GAS_GAS2_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����·��ƿ���ӷ���---�ڶ�����ƿ
		case STEP_13_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IS_ISOLATION_FIRST;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
		case STEP_13_O_1TANK_2GAS_IS_ISOLATION_FIRST:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_isolation_first()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر���ѹ�������ڷ���
		case STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_out_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IS_ISOLATION_SECOND;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���
		case STEP_13_O_1TANK_2GAS_IS_ISOLATION_SECOND:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_isolation_second()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ѹ����ͣ��
		case STEP_13_O_1TANK_2GAS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ѹ����ͣ���Ƿ�����
		case STEP_13_O_1TANK_2GAS_IS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_BYPATH_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ������·������
		case STEP_13_O_1TANK_2GAS_BYPATH_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_bypath_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_TIME_DELAY_BYPATH;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_bypath
		case STEP_13_O_1TANK_2GAS_TIME_DELAY_BYPATH:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_time_delay_bypath()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ������·������
		case STEP_13_O_1TANK_2GAS_BYPATH_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_bypath_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر���ѹ�������ڷ��ţ��ڶ���
		case STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_out_compressor_valve_off2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر���ѹ�������ڷ���
		case STEP_13_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_in_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ؽ������ѹ��·���ӷ���
		case STEP_13_O_1TANK_2GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_SET_STATE_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����������״̬��
		case STEP_13_O_1TANK_2GAS_SET_STATE_GOOD:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_set_state_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ�����¶��Ƿ�����
		case STEP_13_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IS_NEED_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��
		case STEP_13_O_1TANK_2GAS_IS_NEED_COOLER_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_need_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_TIME_DELAY3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay3
		case STEP_13_O_1TANK_2GAS_TIME_DELAY3:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_time_delay3()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		/*
		//����Һ��ģ���л�����
		case STEP_13_O_1TANK_2GAS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
		case STEP_13_O_1TANK_2GAS_IS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		*/
		
		//Һ��ģ��ͣ��
		case STEP_13_O_1TANK_2GAS_COOLER_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COOLER_SET;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//Һ��ģ��״̬����
		case STEP_13_O_1TANK_2GAS_COOLER_SET:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_cooler_set()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COMPRESSOR_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ�����ϵ�
		case STEP_13_O_1TANK_2GAS_COMPRESSOR_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_compressor_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_TGTHT530_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������������ϵ�
		case STEP_13_O_1TANK_2GAS_TGTHT530_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_TGTHT530_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
				
				//�������������������������������������������������
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}


//----------------------------------���������������һ���������--------------------------------------

		//���������ѹ��·���ӷ���---��һ������
		case STEP_13_O_2TANK_TANK1_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_TIME_DELAY_C;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�ʱ��
		case STEP_13_O_2TANK_TANK1_TIME_DELAY_C:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϿ������䷧��---��һ������
		case STEP_13_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_in_tank_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ�������ڷ���---��һ������
		case STEP_13_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_in_compressor_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_TIME_DELAY1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay1---��һ������
		case STEP_13_O_2TANK_TANK1_TIME_DELAY1:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_time_delay1()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ��������ѹ���Ƿ�����---��һ������
		case STEP_13_O_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_in_compressor_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_COMPRESSOR_START;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ѹ��������---��һ������
		case STEP_13_O_2TANK_TANK1_COMPRESSOR_START:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_compressor_start()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_TIME_DELAY_D;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�ʱ��
		case STEP_13_O_2TANK_TANK1_TIME_DELAY_D:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ��������ѹ���Ƿ�����---��һ������
		case STEP_13_O_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_out_compressor_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ�������ڷ���---��һ������
		case STEP_13_O_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_out_compressor_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_NUMBER_COMP_GAS;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϳ�����ƿ����---��һ������
		case STEP_13_O_2TANK_TANK1_NUMBER_COMP_GAS:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_number_comp_gas()==TRUE)
			{
				asm("nop;");
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}

//----------------------------------���������������һ�����������һ����ƿ����------------------------

		//������ƿ���ӷ���---��һ������
		case STEP_13_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay2---��һ������
		case STEP_13_O_2TANK_TANK1_1GAS_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿѹ���Ƿ�����---��һ������
		case STEP_13_O_2TANK_TANK1_1GAS_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿ�����Ƿ����---��һ������
		case STEP_13_O_2TANK_TANK1_1GAS_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����·��ƿ���ӷ���---��һ������
		case STEP_13_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ؽ������ѹ��·���ӷ���---��һ������
		case STEP_13_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϹؽ����䲹�ӷ�---��һ������
		case STEP_13_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_in_tank_valve_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}

//----------------------------------���������������һ�����������������ƿ����------------------------

		//������ƿ���ӷ���---��һ����ƿ
		case STEP_13_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay2---��һ����ƿ
		case STEP_13_O_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿѹ���Ƿ�����---��һ����ƿ
		case STEP_13_O_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS1_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿ�����Ƿ����---��һ����ƿ
		case STEP_13_O_2TANK_TANK1_2GAS_GAS1_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����·��ƿ���ӷ���---��һ����ƿ
		case STEP_13_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//������ƿ���ӷ���---�ڶ�����ƿ
		case STEP_13_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
		case STEP_13_O_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
		case STEP_13_O_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS2_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
		case STEP_13_O_2TANK_TANK1_2GAS_GAS2_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����·��ƿ���ӷ���---�ڶ�����ƿ
		case STEP_13_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ؽ������ѹ��·���ӷ���
		case STEP_13_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϹؽ����䲹�ӷ�
		case STEP_13_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_step_is_in_tank_valve_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}

//----------------------------------��������������ڶ����������--------------------------------------

		//���������ѹ��·���ӷ���---�ڶ�������
		case STEP_13_O_2TANK_TANK2_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_step_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_TIME_DELAY_E;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�ʱ��
		case STEP_13_O_2TANK_TANK2_TIME_DELAY_E:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϿ������䷧��---�ڶ�������
		case STEP_13_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_step_is_in_tank_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_NUMBER_COMP_GAS;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϳ�����ƿ����---�ڶ�������
		case STEP_13_O_2TANK_TANK2_NUMBER_COMP_GAS:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_step_number_comp_gas()==TRUE)
			{
				asm("nop;");
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}

//----------------------------------��������������ڶ������������һ����ƿ����------------------------
		
		//������ƿ���ӷ���---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay2---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿѹ���Ƿ�����---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿ�����Ƿ����---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����·��ƿ���ӷ���---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_ISOLATION_FIRST;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
		case STEP_13_O_2TANK_TANK2_1GAS_IS_ISOLATION_FIRST:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_isolation_first()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		
		//�ر���ѹ�������ڷ���---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_out_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_ISOLATION_SECOND;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���
		case STEP_13_O_2TANK_TANK2_1GAS_IS_ISOLATION_SECOND:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_isolation_second()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ѹ����ͣ��---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ѹ����ͣ���Ƿ�����---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_BYPATH_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ������·������---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_BYPATH_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_bypath_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY_BYPATH;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_bypath---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY_BYPATH:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay_bypath()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ������·������---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_bypath_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر���ѹ�������ڷ��ţ��ڶ���
		case STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_out_compressor_valve_off2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر���ѹ�������ڷ���---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ؽ������ѹ��·���ӷ���---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_SET_STATE_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����������״̬��---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_SET_STATE_GOOD:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_set_state_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ�����¶��Ƿ�����---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_NEED_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��
		case STEP_13_O_2TANK_TANK2_1GAS_IS_NEED_COOLER_STOP:
		{	
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_need_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay3---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY3:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay3()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		
		/*
		//����Һ��ģ���л�����---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����---�ڶ�������
		case STEP_13_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		*/
		
		//Һ��ģ��ͣ��
		case STEP_13_O_2TANK_TANK2_1GAS_COOLER_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COOLER_SET;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//Һ��ģ��״̬����
		case STEP_13_O_2TANK_TANK2_1GAS_COOLER_SET:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_cooler_set()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ�����ϵ�
		case STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_compressor_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������������ϵ�
		case STEP_13_O_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_TGTHT530_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������������������������������������������������

//----------------------------------��������������ڶ������������������ƿ����------------------------

		//������ƿ���ӷ���---��һ����ƿ
		case STEP_13_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay2---��һ����ƿ
		case STEP_13_O_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿѹ���Ƿ�����---��һ����ƿ
		case STEP_13_O_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS1_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿ�����Ƿ����---��һ����ƿ
		case STEP_13_O_2TANK_TANK2_2GAS_GAS1_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����·��ƿ���ӷ���---��һ����ƿ
		case STEP_13_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//������ƿ���ӷ���---�ڶ�����ƿ
		case STEP_13_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
		case STEP_13_O_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
		case STEP_13_O_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS2_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
		case STEP_13_O_2TANK_TANK2_2GAS_GAS2_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����·��ƿ���ӷ���---�ڶ�����ƿ
		case STEP_13_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IS_ISOLATION_FIRST;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
		case STEP_13_O_2TANK_TANK2_2GAS_IS_ISOLATION_FIRST:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_isolation_first()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر���ѹ�������ڷ���
		case STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_out_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IS_ISOLATION_SECOND;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���
		case STEP_13_O_2TANK_TANK2_2GAS_IS_ISOLATION_SECOND:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_isolation_second()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ѹ����ͣ��
		case STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ѹ����ͣ���Ƿ�����
		case STEP_13_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_BYPATH_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ������·������
		case STEP_13_O_2TANK_TANK2_2GAS_BYPATH_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_bypath_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_TIME_DELAY_BYPATH;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_bypath
		case STEP_13_O_2TANK_TANK2_2GAS_TIME_DELAY_BYPATH:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_time_delay_bypath()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ������·������
		case STEP_13_O_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_bypath_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر���ѹ�������ڷ��ţ��ڶ���
		case STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_out_compressor_valve_off2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر���ѹ�������ڷ���
		case STEP_13_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_in_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ؽ������ѹ��·���ӷ���
		case STEP_13_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_SET_STATE_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����������״̬��
		case STEP_13_O_2TANK_TANK2_2GAS_SET_STATE_GOOD:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_set_state_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ�����¶��Ƿ�����
		case STEP_13_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IS_NEED_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��
		case STEP_13_O_2TANK_TANK2_2GAS_IS_NEED_COOLER_STOP:
		{
		
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_need_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_TIME_DELAY3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay3
		case STEP_13_O_2TANK_TANK2_2GAS_TIME_DELAY3:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_time_delay3()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		
		/*
		//����Һ��ģ���л�����
		case STEP_13_O_2TANK_TANK2_2GAS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
		case STEP_13_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		*/
		
		//Һ��ģ��ͣ��
		case STEP_13_O_2TANK_TANK2_2GAS_COOLER_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COOLER_SET;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//Һ��ģ��״̬����
		case STEP_13_O_2TANK_TANK2_2GAS_COOLER_SET:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_cooler_set()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ�����ϵ�
		case STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_compressor_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������������ϵ�
		case STEP_13_O_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_TGTHT530_power_off()==TRUE)
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


/*
*****************************************************************************************************************
-------------------------------------------------��ʼ���ý׶�----------------------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**���ƣ�����Һ��ù���
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_start_cooler(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_COOLER_VALVE_ON_NO1;
			break;
		}
		
		//Һ��ģ�鲹��ϵͳ���ſ���һ��
		case COMMAND_13_0001_O_INIT_COOLER_VALVE_ON_NO1:
		{
			TGTHT510_supply_command_cooler_valve_on(1);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_IS_COOLER_VALVE_ON_NO1;
			
			break;
		}
		
		//�ж�Һ��ģ�鲹��ϵͳ���ſ���һ��
		case COMMAND_13_0002_O_INIT_IS_COOLER_VALVE_ON_NO1:
		{
			if(TGTHT510_supply_command_is_cooler_valve_on(1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_INIT_COOLER_VALVE_ON_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ�鲹��ϵͳ���ſ��ڶ���
		case COMMAND_13_0003_O_INIT_COOLER_VALVE_ON_NO2:
		{
			TGTHT510_supply_command_cooler_valve_on(2);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_INIT_IS_COOLER_VALVE_ON_NO2;
			
			break;
		}
		
		//�ж�Һ��ģ�鲹��ϵͳ���ſ��ڶ���
		case COMMAND_13_0004_O_INIT_IS_COOLER_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_command_is_cooler_valve_on(2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_INIT_COOLER_POWER_ON;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ�鹩��ͨ
		case COMMAND_13_0005_O_INIT_COOLER_POWER_ON:
		{
			TGTHT510_supply_command_cooler_power_on();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_INIT_TIME_1MIN_START;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ
		case COMMAND_13_0006_O_INIT_TIME_1MIN_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_INIT_IS_TIME_1MIN;
			
			break;
		}
		
		//��ʱ1min�Ƿ�
		case COMMAND_13_0007_O_INIT_IS_TIME_1MIN:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**���ƣ�ͨ��ת���ж�Һ�乤���Ƿ�����
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

uint16 TGTHT510_supply_stage13_comp_O_init_step_is_cooler_work(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_13_0001_O_INIT_IS_COOLER_WORK:
		{
			if(TGTHT510_supply_common_cooler_work(3)==TRUE)//��ֵ���޸ģ�����
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_COOLER_WORK);
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
**����: ��ʱ�ȴ�time_delay1
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_time_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_TIME_DELAY_START;
			break;
		}
		
		case COMMAND_13_0001_O_INIT_TIME_DELAY_START://��ʱ�ȴ�time_delay1��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_IS_TIME_DELAY;
	
			break;
		}
		
		case COMMAND_13_0002_O_INIT_IS_TIME_DELAY://�ж���ʱ�ȴ�time_delay1
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
**���ƣ��ж�ѹ�����¶��Ƿ�����
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_13_0001_O_INIT_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_COMPRESSOR_TEMPERATURE);//ѹ�����ⶨ�¶��쳣
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
**���ƣ��������������ӵ�
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_TGTHT530_power_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_TGTHT530_POWER_ON;
			break;
		}
		
		case COMMAND_13_0001_O_INIT_TGTHT530_POWER_ON://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530a_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			break;
		}
		
		case COMMAND_13_0002_O_INIT_TGTHT530_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_INIT_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_INIT_TGTHT530_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
		{
			
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_INIT_TGTHT530_IS_POWER_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_INIT_TGTHT530_IS_POWER_ON://ͨ�����������жϼӵ��Ƿ�����
		{
			//�����䣡������
			
			TGTHT510_supply_ctrl.command=COMMAND_END;//�����䣡������
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
**���ƣ�����ѹ�����ӵ�
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_compressor_power_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_COMPRESSOR_POWER_ON;
			break;
		}
		
		case COMMAND_13_0001_O_INIT_COMPRESSOR_POWER_ON://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}

			break;
		}
		
		case COMMAND_13_0002_O_INIT_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_INIT_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_INIT_COMPRESSOR_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**���ƣ��������
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_isolation(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_ISOLATION_VALVE_OFF_NO1;
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ���һ��
		case COMMAND_13_0001_O_INIT_ISOLATION_VALVE_OFF_NO1:
		{
			TGTHT510_supply_command_isolation_valve_off(1,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_TIME_1MIN_START_NO1;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ����һ��
		case COMMAND_13_0002_O_INIT_TIME_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_INIT_IS_TIME_1MIN_NO1;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣���һ��
		case COMMAND_13_0003_O_INIT_IS_TIME_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_INIT_IS_ISOLATION_VALVE_OFF_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ���һ��
		case COMMAND_13_0004_O_INIT_IS_ISOLATION_VALVE_OFF_NO1:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(1,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_INIT_ISOLATION_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ��ڶ���
		case COMMAND_13_0005_O_INIT_ISOLATION_VALVE_OFF_NO2:
		{
			TGTHT510_supply_command_isolation_valve_off(2,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_INIT_TIME_1MIN_START_NO2;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ���ڶ���
		case COMMAND_13_0006_O_INIT_TIME_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_INIT_IS_TIME_1MIN_NO2;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣��ڶ���
		case COMMAND_13_0007_O_INIT_IS_TIME_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_INIT_IS_ISOLATION_VALVE_OFF_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ��ڶ���
		case COMMAND_13_0008_O_INIT_IS_ISOLATION_VALVE_OFF_NO2:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(2,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_INIT_ISOLATION_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ�������
		case COMMAND_13_0009_O_INIT_ISOLATION_VALVE_OFF_NO3:
		{
			TGTHT510_supply_command_isolation_valve_off(3,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_INIT_TIME_1MIN_START_NO3;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ��������
		case COMMAND_13_0010_O_INIT_TIME_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_INIT_IS_TIME_1MIN_NO3;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣�������
		case COMMAND_13_0011_O_INIT_IS_TIME_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_INIT_IS_ISOLATION_VALVE_OFF_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ�������
		case COMMAND_13_0012_O_INIT_IS_ISOLATION_VALVE_OFF_NO3:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(3,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_INIT_ISOLATION_VALVE_OFF_NO4;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ�������
		case COMMAND_13_0013_O_INIT_ISOLATION_VALVE_OFF_NO4:
		{
			TGTHT510_supply_command_isolation_valve_off(4,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_INIT_TIME_1MIN_START_NO4;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ��������
		case COMMAND_13_0014_O_INIT_TIME_1MIN_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_INIT_IS_TIME_1MIN_NO4;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣�������
		case COMMAND_13_0015_O_INIT_IS_TIME_1MIN_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_INIT_IS_ISOLATION_VALVE_OFF_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ�������
		case COMMAND_13_0016_O_INIT_IS_ISOLATION_VALVE_OFF_NO4:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(4,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_INIT_ISOLATION_VALVE_OFF_NO5;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ�������
		case COMMAND_13_0017_O_INIT_ISOLATION_VALVE_OFF_NO5:
		{
			TGTHT510_supply_command_isolation_valve_off(5,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_INIT_TIME_1MIN_START_NO5;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ��������
		case COMMAND_13_0018_O_INIT_TIME_1MIN_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_INIT_IS_TIME_1MIN_NO5;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣�������
		case COMMAND_13_0019_O_INIT_IS_TIME_1MIN_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_INIT_IS_ISOLATION_VALVE_OFF_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ�������
		case COMMAND_13_0020_O_INIT_IS_ISOLATION_VALVE_OFF_NO5:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(5,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_INIT_ISOLATION_VALVE_OFF_NO6;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ�������
		case COMMAND_13_0021_O_INIT_ISOLATION_VALVE_OFF_NO6:
		{
			TGTHT510_supply_command_isolation_valve_off(6,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_INIT_TIME_1MIN_START_NO6;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ��������
		case COMMAND_13_0022_O_INIT_TIME_1MIN_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_INIT_IS_TIME_1MIN_NO6;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣�������
		case COMMAND_13_0023_O_INIT_IS_TIME_1MIN_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_INIT_IS_ISOLATION_VALVE_OFF_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ�������
		case COMMAND_13_0024_O_INIT_IS_ISOLATION_VALVE_OFF_NO6:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(6,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_INIT_ISOLATION_VALVE_OFF_NO7;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ�������
		case COMMAND_13_0025_O_INIT_ISOLATION_VALVE_OFF_NO7:
		{
			TGTHT510_supply_command_isolation_valve_off(7,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_INIT_TIME_1MIN_START_NO7;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ��������
		case COMMAND_13_0026_O_INIT_TIME_1MIN_START_NO7:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_INIT_IS_TIME_1MIN_NO7;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣�������
		case COMMAND_13_0027_O_INIT_IS_TIME_1MIN_NO7:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_INIT_IS_ISOLATION_VALVE_OFF_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ�������
		case COMMAND_13_0028_O_INIT_IS_ISOLATION_VALVE_OFF_NO7:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(7,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_INIT_ISOLATION_VALVE_OFF_NO8;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ��ڰ���
		case COMMAND_13_0029_O_INIT_ISOLATION_VALVE_OFF_NO8:
		{
			TGTHT510_supply_command_isolation_valve_off(8,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0030_O_INIT_TIME_1MIN_START_NO8;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ���ڰ���
		case COMMAND_13_0030_O_INIT_TIME_1MIN_START_NO8:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0031_O_INIT_IS_TIME_1MIN_NO8;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣��ڰ���
		case COMMAND_13_0031_O_INIT_IS_TIME_1MIN_NO8:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0032_O_INIT_IS_ISOLATION_VALVE_OFF_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ��ڰ���
		case COMMAND_13_0032_O_INIT_IS_ISOLATION_VALVE_OFF_NO8:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(8,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0033_O_INIT_ISOLATION_VALVE_OFF_NO9;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ��ھ���
		case COMMAND_13_0033_O_INIT_ISOLATION_VALVE_OFF_NO9:
		{
			TGTHT510_supply_command_isolation_valve_off(9,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0034_O_INIT_TIME_1MIN_START_NO9;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ���ھ���
		case COMMAND_13_0034_O_INIT_TIME_1MIN_START_NO9:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0035_O_INIT_IS_TIME_1MIN_NO9;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣��ھ���
		case COMMAND_13_0035_O_INIT_IS_TIME_1MIN_NO9:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0036_O_INIT_IS_ISOLATION_VALVE_OFF_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ��ھ���
		case COMMAND_13_0036_O_INIT_IS_ISOLATION_VALVE_OFF_NO9:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(9,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
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
**���ƣ��жϳ����������
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_number_comp_tank(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_NUMBER_COMP_TANK;
			break;
		}
		
		case COMMAND_13_0001_O_INIT_NUMBER_COMP_TANK://�жϳ����������
		{
			if(TGTHT510_supply_decode_par.number_tank_O==1)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_IN_TANK_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else if((TGTHT510_supply_decode_par.number_tank_O==2)||\
			(TGTHT510_supply_decode_par.number_tank_O==3))
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_IN_TANK_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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


/*
*****************************************************************************************************************
-------------------------------------------------һ���������----------------------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**���ƣ����������ѹ��·���ӷ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_IN_TANK_VALVE_ON://���������ѹ��·���ӷ���
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				TGTHT510_supply_main_lvb_set(LVb1K);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				TGTHT510_supply_main_lvb_set(LVb3K);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				TGTHT510_supply_main_lvb_set(LVb5K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_IS_IN_TANK_VALVE_ON://�жϿ��������ѹ��·���ӷ���
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**���ƣ�ͨ��ѹ���жϿ��������ѹ��·���ӷ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_is_in_tank_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE://ͨ��ѹ���жϿ����ӷ���
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O1)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O2)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O3)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**���ƣ�����ѹ�������ڷ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_in_compressor_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO1://����ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				TGTHT510_supply_main_lvb_set(LVb13K);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_main_lvb_set(LVb24K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO1;

			break;
		}
		
		case COMMAND_13_0002_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO1://�жϿ���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO2;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb24,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO2;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO2://����ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				TGTHT510_supply_main_lvb_set(LVb15K);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				asm("nop;");
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO2://�жϿ���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO3;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO3://����ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				TGTHT510_supply_main_lvb_set(LVb21G);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO3;

			break;
		}
		
		case COMMAND_13_0006_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO3://�жϿ���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: ��ʱ�ȴ�time_delay1
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_time_delay1(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_TIME_DELAY1_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_TIME_DELAY1_START://��ʱ�ȴ�time_delay1��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_IS_TIME_DELAY1;
	
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_IS_TIME_DELAY1://�ж���ʱ�ȴ�time_delay1
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
**����: �ж�ѹ��������ѹ���Ƿ�����
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_is_in_compressor_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_IS_IN_COMPRESSOR_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_IS_IN_COMPRESSOR_PRESSURE://�ж�ѹ��������ѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_in_compressor_pressure(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_IN_COMPRESSOR_PRESSURE);
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
**����: ��ѹ��������
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_compressor_start(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_COMPRESSOR_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_COMPRESSOR_START://�����豸����ָ�ѹ��������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_START);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_START);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_COMPRESSOR_IS_TIME_1MIN://�ж�1min��ʱ
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_IS_COMPRESSOR_START;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_IS_COMPRESSOR_START://ͨ�����������ж������Ƿ�����
		{
			//�����䣡������
			
			TGTHT510_supply_ctrl.command=COMMAND_END;//�����䣡������
			
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
**����: �ж�ѹ��������ѹ���Ƿ�����
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_is_out_compressor_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE://�ж�ѹ��������ѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_out_compressor_pressure(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_OUT_COMPRESSOR_PRESSURE);
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
**����: ����ѹ�������ڷ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_out_compressor_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_OUT_COMPRESSOR_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_OUT_COMPRESSOR_VALVE_ON://����ѹ�������ڷ���
		{
			TGTHT510_supply_common_out_compressor_valve_on(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_IS_OUT_COMPRESSOR_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_IS_OUT_COMPRESSOR_VALVE_ON://�жϿ���ѹ�������ڷ���
		{
			if(TGTHT510_supply_common_is_out_compressor_valve_on(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
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
**����: �жϳ�����ƿ����
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_number_comp_gas(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_NUMBER_COMP_GAS;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_NUMBER_COMP_GAS://�жϳ�����ƿ����
		{
			if(TGTHT510_supply_common_number_gas(COMP_TANK_O,FIRST_TANK)==ONE_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else if(TGTHT510_supply_common_number_gas(COMP_TANK_O,FIRST_TANK)==TWO_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else 
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
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


/*
*****************************************************************************************************************
-----------------------------------һ�����������һ����ƿ����----------------------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**����: ������ƿ���ӷ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IN_GAS_VALVE_ON://������ƿ���ӷ���
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_ON://�жϿ�����ƿ���ӷ���
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else 
			{
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
**����: ��ʱ�ȴ�time_delay2
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_TIME_DELAY2_START://��ʱ�ȴ�time_delay2��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_DELAY2://�ж���ʱ�ȴ�time_delay2
		{
			
			/*
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_delay_short)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			*/
			if(TGTHT510_supply_time_step_is_get(0)==TRUE)
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
**����: �ж���ƿѹ���Ƿ�����
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_GAS_PRESSURE_NO1://�ɼ���ƿѹ������һ��
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_TIME_30S_START_NO1://��ʱ30s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_IS_TIME_30S_NO1://�ж϶�ʱ30s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_GAS_PRESSURE_NO2://�ɼ���ƿѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_TIME_30S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_TIME_30S_START_NO2://��ʱ30s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_TIME_30S_NO2;
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_IS_TIME_30S_NO2://�ж϶�ʱ30s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_1GAS_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_1GAS_GAS_PRESSURE_NO3://�ɼ���ƿѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_1GAS_TIME_30S_START_NO3;
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_1GAS_TIME_30S_START_NO3://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_1GAS_IS_TIME_30S_NO3;
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_1GAS_IS_TIME_30S_NO3://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_1GAS_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_1GAS_GAS_PRESSURE_NO4://�ɼ���ƿѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_1GAS_TIME_30S_START_NO4;
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_1GAS_TIME_30S_START_NO4://��ʱ30s��ʱ��ʼ�����Ĵ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_1TANK_1GAS_IS_TIME_30S_NO4;
			break;
		}
		
		case COMMAND_13_0012_O_1TANK_1GAS_IS_TIME_30S_NO4://�ж϶�ʱ30s�����Ĵ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_1TANK_1GAS_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0013_O_1TANK_1GAS_GAS_PRESSURE_NO5://�ɼ���ƿѹ���������
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_1TANK_1GAS_TIME_30S_START_NO5;
			break;
		}
		
		case COMMAND_13_0014_O_1TANK_1GAS_TIME_30S_START_NO5://��ʱ30s��ʱ��ʼ�������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_1TANK_1GAS_IS_TIME_30S_NO5;
			break;
		}
		
		case COMMAND_13_0015_O_1TANK_1GAS_IS_TIME_30S_NO5://�ж϶�ʱ30s�������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_1TANK_1GAS_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0016_O_1TANK_1GAS_GAS_PRESSURE_NO6://�ɼ���ƿѹ����������
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_1TANK_1GAS_TIME_30S_START_NO6;
			break;
		}
		
		case COMMAND_13_0017_O_1TANK_1GAS_TIME_30S_START_NO6://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_1TANK_1GAS_IS_TIME_30S_NO6;
			break;
		}
		
		case COMMAND_13_0018_O_1TANK_1GAS_IS_TIME_30S_NO6://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_1TANK_1GAS_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0019_O_1TANK_1GAS_GAS_PRESSURE_NO7://�ɼ���ƿѹ�������ߴ�
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_1TANK_1GAS_TIME_30S_START_NO7;
			break;
		}
		
		case COMMAND_13_0020_O_1TANK_1GAS_TIME_30S_START_NO7://��ʱ30s��ʱ��ʼ�����ߴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_1TANK_1GAS_IS_TIME_30S_NO7;
			break;
		}
		
		case COMMAND_13_0021_O_1TANK_1GAS_IS_TIME_30S_NO7://�ж϶�ʱ30s�����ߴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_1TANK_1GAS_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0022_O_1TANK_1GAS_GAS_PRESSURE_NO8://�ɼ���ƿѹ�����ڰ˴�
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_1TANK_1GAS_TIME_30S_START_NO8;
			break;
		}
		
		case COMMAND_13_0023_O_1TANK_1GAS_TIME_30S_START_NO8://��ʱ30s��ʱ��ʼ���ڰ˴�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_1TANK_1GAS_IS_TIME_30S_NO8;
			break;
		}
		
		case COMMAND_13_0024_O_1TANK_1GAS_IS_TIME_30S_NO8://�ж϶�ʱ30s���ڰ˴�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_1TANK_1GAS_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0025_O_1TANK_1GAS_GAS_PRESSURE_NO9://�ɼ���ƿѹ�����ھŴ�
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_1TANK_1GAS_TIME_30S_START_NO9;
			break;
		}
		
		case COMMAND_13_0026_O_1TANK_1GAS_TIME_30S_START_NO9://��ʱ30s��ʱ��ʼ���ھŴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_1TANK_1GAS_IS_TIME_30S_NO9;
			break;
		}
		
		case COMMAND_13_0027_O_1TANK_1GAS_IS_TIME_30S_NO9://�ж϶�ʱ30s���ھŴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_1TANK_1GAS_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0028_O_1TANK_1GAS_GAS_PRESSURE_NO10://�ɼ���ƿѹ������ʮ��
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_1TANK_1GAS_IS_GAS_PRESSURE;
			break;
		}
		
		case COMMAND_13_0029_O_1TANK_1GAS_IS_GAS_PRESSURE://ѹ���ж���ƿѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**����: �ж���ƿ�����Ƿ����
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IS_COMP_GAS_OVER://�ж���ƿ�����Ƿ����
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
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
**����: ����·��ƿ���ӷ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			//�ɼ��ط�֮ǰ��ѹ��������ѹ��ֵ
			temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO1://����·��ƿ���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO1://�жϹ���·��ƿ���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO2://����·��ƿ���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO2;
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO2://�жϹ���·��ƿ���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO3://����·��ƿ���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO3;
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO3://�жϹ���·��ƿ���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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


/******************************************************************************************
**����: ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_isolation_first(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO1;
			
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_FIRST_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_FIRST_TIME_12S_START_NO1://��ʱ12s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO1://�ж϶�ʱ12s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_FIRST_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_FIRST_TIME_12S_START_NO2://��ʱ12s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO2://�ж϶�ʱ12s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO3://�ɼ�ѹ��������ѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_1GAS_FIRST_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_1GAS_FIRST_TIME_12S_START_NO3://��ʱ12s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO3://�ж϶�ʱ12s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO4://�ɼ�ѹ��������ѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_1GAS_FIRST_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_1GAS_FIRST_IS_ISOLATION://ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COMPRESSOR_STOP;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**����: �ر���ѹ�������ڷ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_out_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1://�ر���ѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1://�жϹر���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2://�ر���ѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2://�жϹر���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3://�ر���ѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3://�жϹر���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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


/******************************************************************************************
**����: ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������2��
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_isolation_second(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_SECOND_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_SECOND_TIME_12S_START_NO1://��ʱ12s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO1://�ж϶�ʱ12s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_SECOND_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_SECOND_TIME_12S_START_NO2://��ʱ12s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO2://�ж϶�ʱ12s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO3://�ɼ�ѹ��������ѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_1GAS_SECOND_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_1GAS_SECOND_TIME_12S_START_NO3://��ʱ12s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO3://�ж϶�ʱ12s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO4://�ɼ�ѹ��������ѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_1GAS_SECOND_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_1GAS_SECOND_IS_ISOLATION://ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_ISOLATION);//��ѹ��·�����쳣
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**����: ��ѹ����ͣ��
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_STOP://�����豸����ָ�ѹ����ͣ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN://�ж�1min��ʱ
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**����: �ж���ѹ����ͣ���Ƿ�����
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

//�ú������޸ģ�������������������������

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_V_NO1://�ɼ����ת�٣���һ��
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_V_NO2://�ɼ����ת�٣��ڶ���
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_V_NO3://�ɼ����ת�٣�������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_COMPRESSOR_V_NO4://�ɼ����ת�٣����Ĵ�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_COMPRESSOR_V_NO5://�ɼ����ת�٣������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_COMPRESSOR_V_NO6://�ɼ����ת�٣�������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_1GAS_COMPRESSOR_V_NO7://�ɼ����ת�٣����ߴ�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_1GAS_COMPRESSOR_V_NO8://�ɼ����ת�٣��ڰ˴�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_1GAS_TIME_12S_START://��ʱ12s��ʱ��ʼ
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_1GAS_IS_TIME_12S://�ж϶�ʱ12s
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0012_O_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0013_O_1TANK_1GAS_IS_COMPRESSOR_STOP://�ж���ѹ����ͣ���Ƿ�����
		{
			//�����䣡������
			
			
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
**����: ����ѹ������·������
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_bypath_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_BYPATH_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_BYPATH_VALVE_ON://����ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_lvb_set(LVb21K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_ON;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_lvb_set(LVb87K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_ON;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_ON://�жϿ���ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: ��ʱ�ȴ�time_bypath
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay_bypath(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_TIME_BYPATH_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_TIME_BYPATH_START://��ʱ�ȴ�time_bypath��ʱ����
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_BYPATH;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_BYPATH://�ж���ʱ�ȴ�time_bypath
		{
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_bypath)==TRUE)
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
**����: ����ѹ������·������
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_bypath_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_BYPATH_VALVE_OFF;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_BYPATH_VALVE_OFF://����ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_lvb_set(LVb21G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_OFF://�жϹ���ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: �ر���ѹ�������ڷ��ţ��ڶ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_out_compressor_valve_off2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1://�ر���ѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1://�жϹر���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2://�ر���ѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2://�жϹر���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3://�ر���ѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3://�жϹر���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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



/******************************************************************************************
**����: �ر���ѹ�������ڷ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1://�ر���ѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb13G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1://�жϹر���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2://�ر���ѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb15G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2://�жϹر���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3://�ر���ѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb23G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3://�жϹر���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb23,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
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


/******************************************************************************************
**����: �ؽ������ѹ��·���ӷ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO1://�ؽ������ѹ��·���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO1://�жϹؽ������ѹ��·���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO2://�ؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO2://�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO3://�ؽ������ѹ��·���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO3://�жϹؽ������ѹ��·���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
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



/******************************************************************************************
**����: ����������״̬��
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

//�����䣡������

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_set_state_good(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_SET_STATE_GOOD://����������״̬��
		{
			//�����䣡������
			
			
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
**����: �ж�ѹ�����¶��Ƿ�����
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE://�ж�ѹ�����¶��Ƿ�����
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_COMPRESSOR_TEMPERATURE);//ѹ�����ⶨ�¶��쳣
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
**����: �ж��Ƿ���Ҫ����Һ��ģ���л�����
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_need_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IS_NEED_COOLER_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IS_NEED_COOLER_STOP://�ж��Ƿ���Ҫ����Һ��ģ��ͣ��
		{
			if(TGTHT510_supply_decode_par.number_tank_F==3)
			{
				//���е������������䣬������Һ��ģ���л�����
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COMPRESSOR_POWER_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
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
**����: ��ʱ�ȴ�time_delay3
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay3(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_TIME_DELAY3_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_TIME_DELAY3_START://��ʱ�ȴ�time_delay3��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_DELAY3;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_DELAY3://�ж���ʱ�ȴ�time_delay3
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
**����: Һ��ģ��ͣ��
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_COOLER_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_1TANK_1GAS_COOLER_POWER_OFF://Һ��ģ��ͣ��
		{
			TGTHT510_supply_command_cooler_power_off();
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
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
**����: Һ��ģ��״̬����
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_cooler_set(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_COOLER_SET_NO1;
			break;
		}
		
		//Һ��ģ��״̬����1
		case COMMAND_13_0001_O_1TANK_1GAS_COOLER_SET_NO1:
		{
			TGTHT510_supply_main_lvb_set(LVb35K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_COOLER_SET_NO1;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����1
		case COMMAND_13_0002_O_1TANK_1GAS_IS_COOLER_SET_NO1:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb35,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_COOLER_SET_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����2
		case COMMAND_13_0003_O_1TANK_1GAS_COOLER_SET_NO2:
		{
			TGTHT510_supply_main_lvb_set(LVb28K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_IS_COOLER_SET_NO2;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����2
		case COMMAND_13_0004_O_1TANK_1GAS_IS_COOLER_SET_NO2:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb28,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_COOLER_SET_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����3
		case COMMAND_13_0005_O_1TANK_1GAS_COOLER_SET_NO3:
		{
			TGTHT510_supply_main_lvb_set(LVb30K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_COOLER_SET_NO3;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����3
		case COMMAND_13_0006_O_1TANK_1GAS_IS_COOLER_SET_NO3:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb30,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_1GAS_COOLER_SET_NO4;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����4
		case COMMAND_13_0007_O_1TANK_1GAS_COOLER_SET_NO4:
		{
			TGTHT510_supply_main_lvb_set(LVb31G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_1GAS_IS_COOLER_SET_NO4;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����4
		case COMMAND_13_0008_O_1TANK_1GAS_IS_COOLER_SET_NO4:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb31,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_1GAS_COOLER_SET_NO5;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����5
		case COMMAND_13_0009_O_1TANK_1GAS_COOLER_SET_NO5:
		{
			TGTHT510_supply_main_lvb_set(LVb27G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_1GAS_IS_COOLER_SET_NO5;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����5
		case COMMAND_13_0010_O_1TANK_1GAS_IS_COOLER_SET_NO5:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb27,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_1GAS_COOLER_SET_NO6;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����6
		case COMMAND_13_0011_O_1TANK_1GAS_COOLER_SET_NO6:
		{
			TGTHT510_supply_main_lvb_set(LVb29G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_1TANK_1GAS_IS_COOLER_SET_NO6;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����6
		case COMMAND_13_0012_O_1TANK_1GAS_IS_COOLER_SET_NO6:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb29,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_1TANK_1GAS_COOLER_SET_NO7;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����7
		case COMMAND_13_0013_O_1TANK_1GAS_COOLER_SET_NO7:
		{
			TGTHT510_supply_main_lvb_set(LVb33G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_1TANK_1GAS_IS_COOLER_SET_NO7;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����7
		case COMMAND_13_0014_O_1TANK_1GAS_IS_COOLER_SET_NO7:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb33,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_1TANK_1GAS_COOLER_SET_NO8;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����8
		case COMMAND_13_0015_O_1TANK_1GAS_COOLER_SET_NO8:
		{
			TGTHT510_supply_main_lvb_set(LVb37G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_1TANK_1GAS_IS_COOLER_SET_NO8;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����8
		case COMMAND_13_0016_O_1TANK_1GAS_IS_COOLER_SET_NO8:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb37,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_1TANK_1GAS_COOLER_SET_NO9;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����9
		case COMMAND_13_0017_O_1TANK_1GAS_COOLER_SET_NO9:
		{
			TGTHT510_supply_main_lvb_set(LVb32G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_1TANK_1GAS_IS_COOLER_SET_NO9;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����9
		case COMMAND_13_0018_O_1TANK_1GAS_IS_COOLER_SET_NO9:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb32,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_1TANK_1GAS_COOLER_SET_NO10;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����10
		case COMMAND_13_0019_O_1TANK_1GAS_COOLER_SET_NO10:
		{
			TGTHT510_supply_main_lvb_set(LVb34G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_1TANK_1GAS_IS_COOLER_SET_NO10;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����10
		case COMMAND_13_0020_O_1TANK_1GAS_IS_COOLER_SET_NO10:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb34,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_1TANK_1GAS_COOLER_SET_NO11;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����11
		case COMMAND_13_0021_O_1TANK_1GAS_COOLER_SET_NO11:
		{
			TGTHT510_supply_main_lvb_set(LVb36G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_1TANK_1GAS_IS_COOLER_SET_NO11;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����11
		case COMMAND_13_0022_O_1TANK_1GAS_IS_COOLER_SET_NO11:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb36,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_1TANK_1GAS_COOLER_SET_NO12;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����12
		case COMMAND_13_0023_O_1TANK_1GAS_COOLER_SET_NO12:
		{
			TGTHT510_supply_main_lvb_set(LVb38G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_1TANK_1GAS_IS_COOLER_SET_NO12;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����12
		case COMMAND_13_0024_O_1TANK_1GAS_IS_COOLER_SET_NO12:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb38,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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


/******************************************************************************************
**����: ����ѹ�����ϵ�
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_compressor_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_POWER_OFF://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**����: �������������ϵ�
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_TGTHT530_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_TGTHT530_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_1TANK_1GAS_TGTHT530_POWER_OFF://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530a_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_TGTHT530_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_TGTHT530_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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


/*
*****************************************************************************************************************
-----------------------------------һ�����������������ƿ����----------------------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**����: ������ƿ���ӷ���---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON://������ƿ���ӷ���
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_ON://�жϿ�����ƿ���ӷ���
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else 
			{
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
**����: ��ʱ�ȴ�time_delay2---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS1_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS1_TIME_DELAY2_START://��ʱ�ȴ�time_delay2��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_TIME_DELAY2://�ж���ʱ�ȴ�time_delay2
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
**����: �ж���ƿѹ���Ƿ�����---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO1://�ɼ���ƿѹ������һ��
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS1_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS1_TIME_30S_START_NO1://��ʱ30s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO1://�ж϶�ʱ30s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO2://�ɼ���ƿѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_GAS1_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_GAS1_TIME_30S_START_NO2://��ʱ30s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO2://�ж϶�ʱ30s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO3://�ɼ���ƿѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_2GAS_GAS1_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_2GAS_GAS1_TIME_30S_START_NO3://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO3://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO4://�ɼ���ƿѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_2GAS_GAS1_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_2GAS_GAS1_TIME_30S_START_NO4://��ʱ30s��ʱ��ʼ�����Ĵ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO4://�ж϶�ʱ30s�����Ĵ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO5://�ɼ���ƿѹ���������
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_1TANK_2GAS_GAS1_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_1TANK_2GAS_GAS1_TIME_30S_START_NO5://��ʱ30s��ʱ��ʼ�������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO5://�ж϶�ʱ30s�������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO6://�ɼ���ƿѹ����������
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_1TANK_2GAS_GAS1_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_1TANK_2GAS_GAS1_TIME_30S_START_NO6://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO6://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO7://�ɼ���ƿѹ�������ߴ�
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_1TANK_2GAS_GAS1_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_1TANK_2GAS_GAS1_TIME_30S_START_NO7://��ʱ30s��ʱ��ʼ�����ߴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO7://�ж϶�ʱ30s�����ߴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO8://�ɼ���ƿѹ�����ڰ˴�
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_1TANK_2GAS_GAS1_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_1TANK_2GAS_GAS1_TIME_30S_START_NO8://��ʱ30s��ʱ��ʼ���ڰ˴�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO8://�ж϶�ʱ30s���ڰ˴�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO9://�ɼ���ƿѹ�����ھŴ�
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_1TANK_2GAS_GAS1_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_1TANK_2GAS_GAS1_TIME_30S_START_NO9://��ʱ30s��ʱ��ʼ���ھŴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO9://�ж϶�ʱ30s���ھŴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO10://�ɼ���ƿѹ������ʮ��
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE://ѹ���ж���ƿѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**����: �ж���ƿ�����Ƿ����---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS1_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS1_IS_COMP_GAS_OVER://�ж���ƿ�����Ƿ����
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
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
**����: ����·��ƿ���ӷ���---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1://����·��ƿ���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1://�жϹ���·��ƿ���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2://����·��ƿ���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2://�жϹ���·��ƿ���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3://����·��ƿ���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3://�жϹ���·��ƿ���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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

/******************************************************************************************
**����: ������ƿ���ӷ���---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON://������ƿ���ӷ���
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_ON://�жϿ�����ƿ���ӷ���
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,SECOND_GAS)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else 
			{
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
**����: ��ʱ�ȴ�time_delay2---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS2_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS2_TIME_DELAY2_START://��ʱ�ȴ�time_delay2��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_TIME_DELAY2://�ж���ʱ�ȴ�time_delay2
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
**����: �ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO1://�ɼ���ƿѹ������һ��
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS2_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS2_TIME_30S_START_NO1://��ʱ30s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO1://�ж϶�ʱ30s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO2://�ɼ���ƿѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_GAS2_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_GAS2_TIME_30S_START_NO2://��ʱ30s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO2://�ж϶�ʱ30s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO3://�ɼ���ƿѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_2GAS_GAS2_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_2GAS_GAS2_TIME_30S_START_NO3://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO3://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO4://�ɼ���ƿѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_2GAS_GAS2_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_2GAS_GAS2_TIME_30S_START_NO4://��ʱ30s��ʱ��ʼ�����Ĵ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO4://�ж϶�ʱ30s�����Ĵ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO5://�ɼ���ƿѹ���������
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_1TANK_2GAS_GAS2_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_1TANK_2GAS_GAS2_TIME_30S_START_NO5://��ʱ30s��ʱ��ʼ�������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO5://�ж϶�ʱ30s�������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO6://�ɼ���ƿѹ����������
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_1TANK_2GAS_GAS2_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_1TANK_2GAS_GAS2_TIME_30S_START_NO6://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO6://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO7://�ɼ���ƿѹ�������ߴ�
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_1TANK_2GAS_GAS2_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_1TANK_2GAS_GAS2_TIME_30S_START_NO7://��ʱ30s��ʱ��ʼ�����ߴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO7://�ж϶�ʱ30s�����ߴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO8://�ɼ���ƿѹ�����ڰ˴�
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_1TANK_2GAS_GAS2_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_1TANK_2GAS_GAS2_TIME_30S_START_NO8://��ʱ30s��ʱ��ʼ���ڰ˴�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO8://�ж϶�ʱ30s���ڰ˴�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO9://�ɼ���ƿѹ�����ھŴ�
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_1TANK_2GAS_GAS2_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_1TANK_2GAS_GAS2_TIME_30S_START_NO9://��ʱ30s��ʱ��ʼ���ھŴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO9://�ж϶�ʱ30s���ھŴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO10://�ɼ���ƿѹ������ʮ��
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE://ѹ���ж���ƿѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**����: �ж���ƿ�����Ƿ����---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS2_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS2_IS_COMP_GAS_OVER://�ж���ƿ�����Ƿ����
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,FIRST_TANK,SECOND_GAS)==TRUE)
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
**����: ����·��ƿ���ӷ���---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1://����·��ƿ���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1://�жϹ���·��ƿ���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2://����·��ƿ���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2://�жϹ���·��ƿ���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3://����·��ƿ���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3://�жϹ���·��ƿ���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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


/******************************************************************************************
**����: ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_isolation_first(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_FIRST_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_FIRST_TIME_12S_START_NO1://��ʱ12s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO1://�ж϶�ʱ12s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_FIRST_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_FIRST_TIME_12S_START_NO2://��ʱ12s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO2://�ж϶�ʱ12s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO3://�ɼ�ѹ��������ѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_2GAS_FIRST_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_2GAS_FIRST_TIME_12S_START_NO3://��ʱ12s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO3://�ж϶�ʱ12s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO4://�ɼ�ѹ��������ѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_2GAS_FIRST_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_2GAS_FIRST_IS_ISOLATION://ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COMPRESSOR_STOP;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**����: �ر���ѹ�������ڷ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_out_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1://�ر���ѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1://�жϹر���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2://�ر���ѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2://�жϹر���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3://�ر���ѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3://�жϹر���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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

/******************************************************************************************
**����: ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������2��
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_isolation_second(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_SECOND_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_SECOND_TIME_12S_START_NO1://��ʱ12s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO1://�ж϶�ʱ12s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_SECOND_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_SECOND_TIME_12S_START_NO2://��ʱ12s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO2://�ж϶�ʱ12s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO3://�ɼ�ѹ��������ѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_2GAS_SECOND_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_2GAS_SECOND_TIME_12S_START_NO3://��ʱ12s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO3://�ж϶�ʱ12s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO4://�ɼ�ѹ��������ѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_2GAS_SECOND_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_2GAS_SECOND_IS_ISOLATION://ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_ISOLATION);//��ѹ��·�����쳣
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**����: ��ѹ����ͣ��
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_STOP://�����豸����ָ�ѹ����ͣ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN://�ж�1min��ʱ
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**����: �ж���ѹ����ͣ���Ƿ�����
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

//�ú������޸ģ�������������������������

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_V_NO1://�ɼ����ת�٣���һ��
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_V_NO2://�ɼ����ת�٣��ڶ���
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_V_NO3://�ɼ����ת�٣�������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_COMPRESSOR_V_NO4://�ɼ����ת�٣����Ĵ�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_COMPRESSOR_V_NO5://�ɼ����ת�٣������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_COMPRESSOR_V_NO6://�ɼ����ת�٣�������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_2GAS_COMPRESSOR_V_NO7://�ɼ����ת�٣����ߴ�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_2GAS_COMPRESSOR_V_NO8://�ɼ����ת�٣��ڰ˴�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_2GAS_TIME_12S_START://��ʱ12s��ʱ��ʼ
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_2GAS_IS_TIME_12S://�ж϶�ʱ12s
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0012_O_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0013_O_1TANK_2GAS_IS_COMPRESSOR_STOP://�ж���ѹ����ͣ���Ƿ�����
		{
			//�����䣡������
			
			
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
**����: ����ѹ������·������
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_bypath_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_BYPATH_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_BYPATH_VALVE_ON://����ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_lvb_set(LVb21K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_ON;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_lvb_set(LVb87K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_ON;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_ON://�жϿ���ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: ��ʱ�ȴ�time_bypath
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_time_delay_bypath(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_TIME_BYPATH_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_TIME_BYPATH_START://��ʱ�ȴ�time_bypath��ʱ����
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_TIME_BYPATH;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_TIME_BYPATH://�ж���ʱ�ȴ�time_bypath
		{
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_bypath)==TRUE)
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
**����: ����ѹ������·������
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_bypath_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_BYPATH_VALVE_OFF;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_BYPATH_VALVE_OFF://����ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_lvb_set(LVb21G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_OFF://�жϹ���ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: �ر���ѹ�������ڷ��ţ��ڶ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_out_compressor_valve_off2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1://�ر���ѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1://�жϹر���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2://�ر���ѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2://�жϹر���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3://�ر���ѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3://�жϹر���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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



/******************************************************************************************
**����: �ر���ѹ�������ڷ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_in_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1://�ر���ѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb13G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1://�жϹر���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2://�ر���ѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb15G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2://�жϹر���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3://�ر���ѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb23G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3://�жϹر���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb23,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
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


/******************************************************************************************
**����: �ؽ������ѹ��·���ӷ���
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO1://�ؽ������ѹ��·���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO1://�жϹؽ������ѹ��·���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO2;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO2://�ؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO2://�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO3://�ؽ������ѹ��·���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO3://�жϹؽ������ѹ��·���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
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


/******************************************************************************************
**����: ����������״̬��
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

//�����䣡������

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_set_state_good(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_SET_STATE_GOOD://����������״̬��
		{
			//�����䣡������
			
			
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
**����: �ж�ѹ�����¶��Ƿ�����
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE://�ж�ѹ�����¶��Ƿ�����
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_COMPRESSOR_TEMPERATURE);//ѹ�����ⶨ�¶��쳣
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
**����: �ж��Ƿ���Ҫ����Һ��ģ���л�����
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

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_need_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_IS_NEED_COOLER_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_IS_NEED_COOLER_STOP://�ж��Ƿ���Ҫ����Һ��ģ��ͣ��
		{
			if(TGTHT510_supply_decode_par.number_tank_F==3)
			{
				//���е������������䣬������Һ��ģ��ͣ��
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COMPRESSOR_POWER_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
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
**����: ��ʱ�ȴ�time_delay3
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_time_delay3(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_TIME_DELAY3_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_TIME_DELAY3_START://��ʱ�ȴ�time_delay3��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_TIME_DELAY3;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_TIME_DELAY3://�ж���ʱ�ȴ�time_delay3
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
**����: Һ��ģ��ͣ��
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_COOLER_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_1TANK_2GAS_COOLER_POWER_OFF://Һ��ģ��ͣ��
		{
			TGTHT510_supply_command_cooler_power_off();
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
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
**����: Һ��ģ��״̬����
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_cooler_set(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_COOLER_SET_NO1;
			break;
		}
		
		//Һ��ģ��״̬����1
		case COMMAND_13_0001_O_1TANK_2GAS_COOLER_SET_NO1:
		{
			TGTHT510_supply_main_lvb_set(LVb35K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_COOLER_SET_NO1;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����1
		case COMMAND_13_0002_O_1TANK_2GAS_IS_COOLER_SET_NO1:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb35,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_COOLER_SET_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����2
		case COMMAND_13_0003_O_1TANK_2GAS_COOLER_SET_NO2:
		{
			TGTHT510_supply_main_lvb_set(LVb28K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_IS_COOLER_SET_NO2;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����2
		case COMMAND_13_0004_O_1TANK_2GAS_IS_COOLER_SET_NO2:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb28,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_COOLER_SET_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����3
		case COMMAND_13_0005_O_1TANK_2GAS_COOLER_SET_NO3:
		{
			TGTHT510_supply_main_lvb_set(LVb30K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_IS_COOLER_SET_NO3;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����3
		case COMMAND_13_0006_O_1TANK_2GAS_IS_COOLER_SET_NO3:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb30,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_2GAS_COOLER_SET_NO4;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����4
		case COMMAND_13_0007_O_1TANK_2GAS_COOLER_SET_NO4:
		{
			TGTHT510_supply_main_lvb_set(LVb31G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_2GAS_IS_COOLER_SET_NO4;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����4
		case COMMAND_13_0008_O_1TANK_2GAS_IS_COOLER_SET_NO4:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb31,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_2GAS_COOLER_SET_NO5;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����5
		case COMMAND_13_0009_O_1TANK_2GAS_COOLER_SET_NO5:
		{
			TGTHT510_supply_main_lvb_set(LVb27G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_2GAS_IS_COOLER_SET_NO5;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����5
		case COMMAND_13_0010_O_1TANK_2GAS_IS_COOLER_SET_NO5:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb27,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_2GAS_COOLER_SET_NO6;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����6
		case COMMAND_13_0011_O_1TANK_2GAS_COOLER_SET_NO6:
		{
			TGTHT510_supply_main_lvb_set(LVb29G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_1TANK_2GAS_IS_COOLER_SET_NO6;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����6
		case COMMAND_13_0012_O_1TANK_2GAS_IS_COOLER_SET_NO6:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb29,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_1TANK_2GAS_COOLER_SET_NO7;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����7
		case COMMAND_13_0013_O_1TANK_2GAS_COOLER_SET_NO7:
		{
			TGTHT510_supply_main_lvb_set(LVb33G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_1TANK_2GAS_IS_COOLER_SET_NO7;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����7
		case COMMAND_13_0014_O_1TANK_2GAS_IS_COOLER_SET_NO7:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb33,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_1TANK_2GAS_COOLER_SET_NO8;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����8
		case COMMAND_13_0015_O_1TANK_2GAS_COOLER_SET_NO8:
		{
			TGTHT510_supply_main_lvb_set(LVb37G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_1TANK_2GAS_IS_COOLER_SET_NO8;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����8
		case COMMAND_13_0016_O_1TANK_2GAS_IS_COOLER_SET_NO8:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb37,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_1TANK_2GAS_COOLER_SET_NO9;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����9
		case COMMAND_13_0017_O_1TANK_2GAS_COOLER_SET_NO9:
		{
			TGTHT510_supply_main_lvb_set(LVb32G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_1TANK_2GAS_IS_COOLER_SET_NO9;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����9
		case COMMAND_13_0018_O_1TANK_2GAS_IS_COOLER_SET_NO9:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb32,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_1TANK_2GAS_COOLER_SET_NO10;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����10
		case COMMAND_13_0019_O_1TANK_2GAS_COOLER_SET_NO10:
		{
			TGTHT510_supply_main_lvb_set(LVb34G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_1TANK_2GAS_IS_COOLER_SET_NO10;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����10
		case COMMAND_13_0020_O_1TANK_2GAS_IS_COOLER_SET_NO10:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb34,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_1TANK_2GAS_COOLER_SET_NO11;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����11
		case COMMAND_13_0021_O_1TANK_2GAS_COOLER_SET_NO11:
		{
			TGTHT510_supply_main_lvb_set(LVb36G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_1TANK_2GAS_IS_COOLER_SET_NO11;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����11
		case COMMAND_13_0022_O_1TANK_2GAS_IS_COOLER_SET_NO11:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb36,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_1TANK_2GAS_COOLER_SET_NO12;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����12
		case COMMAND_13_0023_O_1TANK_2GAS_COOLER_SET_NO12:
		{
			TGTHT510_supply_main_lvb_set(LVb38G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_1TANK_2GAS_IS_COOLER_SET_NO12;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����12
		case COMMAND_13_0024_O_1TANK_2GAS_IS_COOLER_SET_NO12:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb38,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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



/******************************************************************************************
**����: ����ѹ�����ϵ�
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_compressor_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_POWER_OFF://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**����: �������������ϵ�
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_TGTHT530_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_TGTHT530_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_1TANK_2GAS_TGTHT530_POWER_OFF://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530a_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_TGTHT530_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_TGTHT530_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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


/*
*****************************************************************************************************************
---------------------------------���������������һ���������----------------------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**����: ���������ѹ��·���ӷ���---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_IN_TANK_VALVE_ON://���������ѹ��·���ӷ���
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				TGTHT510_supply_main_lvb_set(LVb1K);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				TGTHT510_supply_main_lvb_set(LVb3K);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				TGTHT510_supply_main_lvb_set(LVb5K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON://�жϿ��������ѹ��·���ӷ���
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: ͨ��ѹ���жϿ������䷧��---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_in_tank_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE://ͨ��ѹ���жϿ����ӷ���
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O1)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O2)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O3)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: ����ѹ�������ڷ���---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_in_compressor_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO1://����ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				TGTHT510_supply_main_lvb_set(LVb13K);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_main_lvb_set(LVb24K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO1://�жϿ���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO2;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb24,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO2;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO2://����ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				TGTHT510_supply_main_lvb_set(LVb15K);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				asm("nop;");
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO2://�жϿ���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO3;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO3://����ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				TGTHT510_supply_main_lvb_set(LVb21G);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO3://�жϿ���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: ��ʱ�ȴ�time_delay1---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_time_delay1(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_TIME_DELAY1_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_TIME_DELAY1_START://��ʱ�ȴ�time_delay1��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_IS_TIME_DELAY1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_IS_TIME_DELAY1://�ж���ʱ�ȴ�time_delay1
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
**����: �ж�ѹ��������ѹ���Ƿ�����---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_in_compressor_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE://�ж�ѹ��������ѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_in_compressor_pressure(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_IN_COMPRESSOR_PRESSURE);
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
**����: ��ѹ��������---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_compressor_start(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_COMPRESSOR_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_COMPRESSOR_START://�����豸����ָ�ѹ��������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_START);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_START);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_COMPRESSOR_IS_TIME_1MIN://�ж�1min��ʱ
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_IS_COMPRESSOR_START;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_IS_COMPRESSOR_START://ͨ�����������ж������Ƿ�����
		{
			//�����䣡������
			
			TGTHT510_supply_ctrl.command=COMMAND_END;//�����䣡������
			
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
**����: �ж�ѹ��������ѹ���Ƿ�����---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_out_compressor_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE://�ж�ѹ��������ѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_out_compressor_pressure(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_OUT_COMPRESSOR_PRESSURE);
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
**����: ����ѹ�������ڷ���---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_out_compressor_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON://����ѹ�������ڷ���
		{
			TGTHT510_supply_common_out_compressor_valve_on(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_IS_OUT_COMPRESSOR_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_IS_OUT_COMPRESSOR_VALVE_ON://�жϿ���ѹ�������ڷ���
		{
			if(TGTHT510_supply_common_is_out_compressor_valve_on(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
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
**����: �жϳ�����ƿ����---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_number_comp_gas(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_NUMBER_COMP_GAS;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_NUMBER_COMP_GAS://�жϳ�����ƿ����
		{
			if(TGTHT510_supply_common_number_gas(COMP_TANK_O,FIRST_TANK)==ONE_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else if(TGTHT510_supply_common_number_gas(COMP_TANK_O,FIRST_TANK)==TWO_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else 
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
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



/*
*****************************************************************************************************************
---------------------------------���������������һ�����������һ����ƿ����--------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**����: ������ƿ���ӷ���---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON://������ƿ���ӷ���
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_ON://�жϿ�����ƿ���ӷ���
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else 
			{
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
**����: ��ʱ�ȴ�time_delay2---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_1GAS_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_TIME_DELAY2_START://��ʱ�ȴ�time_delay2��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_TIME_DELAY2://�ж���ʱ�ȴ�time_delay2
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
**����: �ж���ƿѹ���Ƿ�����---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO1://�ɼ���ƿѹ������һ��
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_1GAS_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_1GAS_TIME_30S_START_NO1://��ʱ30s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO1://�ж϶�ʱ30s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO2://�ɼ���ƿѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_1GAS_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_1GAS_TIME_30S_START_NO2://��ʱ30s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO2://�ж϶�ʱ30s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO3://�ɼ���ƿѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK1_1GAS_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK1_1GAS_TIME_30S_START_NO3://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO3://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO4://�ɼ���ƿѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK1_1GAS_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK1_1GAS_TIME_30S_START_NO4://��ʱ30s��ʱ��ʼ�����Ĵ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO4://�ж϶�ʱ30s�����Ĵ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO5://�ɼ���ƿѹ���������
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK1_1GAS_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_2TANK_TANK1_1GAS_TIME_30S_START_NO5://��ʱ30s��ʱ��ʼ�������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO5://�ж϶�ʱ30s�������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO6://�ɼ���ƿѹ����������
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK1_1GAS_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_2TANK_TANK1_1GAS_TIME_30S_START_NO6://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO6://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO7://�ɼ���ƿѹ�������ߴ�
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK1_1GAS_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_2TANK_TANK1_1GAS_TIME_30S_START_NO7://��ʱ30s��ʱ��ʼ�����ߴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO7://�ж϶�ʱ30s�����ߴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO8://�ɼ���ƿѹ�����ڰ˴�
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK1_1GAS_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_2TANK_TANK1_1GAS_TIME_30S_START_NO8://��ʱ30s��ʱ��ʼ���ڰ˴�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO8://�ж϶�ʱ30s���ڰ˴�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO9://�ɼ���ƿѹ�����ھŴ�
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_2TANK_TANK1_1GAS_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_2TANK_TANK1_1GAS_TIME_30S_START_NO9://��ʱ30s��ʱ��ʼ���ھŴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO9://�ж϶�ʱ30s���ھŴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO10://�ɼ���ƿѹ������ʮ��
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_2TANK_TANK1_1GAS_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_2TANK_TANK1_1GAS_IS_GAS_PRESSURE://ѹ���ж���ƿѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**����: �ж���ƿ�����Ƿ����---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_1GAS_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_IS_COMP_GAS_OVER://�ж���ƿ�����Ƿ����
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
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
**����: ����·��ƿ���ӷ���---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO1://����·��ƿ���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO1://�жϹ���·��ƿ���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO2://����·��ƿ���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO2://�жϹ���·��ƿ���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO3://����·��ƿ���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO3://�жϹ���·��ƿ���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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


/******************************************************************************************
**����: �ؽ������ѹ��·���ӷ���---��һ������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO1://�ؽ������ѹ��·���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO1://�жϹؽ������ѹ��·���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO2://�ؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO2://�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO3://�ؽ������ѹ��·���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO3://�жϹؽ������ѹ��·���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
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

/******************************************************************************************
**����: ͨ��ѹ���жϹؽ����䲹�ӷ�---��һ������
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

//�����䣡������

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_in_tank_valve_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO1://ͨ��ѹ���жϹؽ����䲹�ӷ�����һ��
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO2://ͨ��ѹ���жϹؽ����䲹�ӷ����ڶ���
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO3://ͨ��ѹ���жϹؽ����䲹�ӷ���������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO4://ͨ��ѹ���жϹؽ����䲹�ӷ���������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO5://ͨ��ѹ���жϹؽ����䲹�ӷ���������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE://ͨ��ѹ���жϹؽ����䲹�ӷ�����ȡ��
		{
			//�����䣡������
			
			
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


/*
*****************************************************************************************************************
---------------------------------���������������һ�����������������ƿ����--------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**����: ������ƿ���ӷ���---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON://������ƿ���ӷ���
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_ON://�жϿ�����ƿ���ӷ���
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else 
			{
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
**����: ��ʱ�ȴ�time_delay2---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2_START://��ʱ�ȴ�time_delay2��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_DELAY2://�ж���ʱ�ȴ�time_delay2
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
**����: �ж���ƿѹ���Ƿ�����---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO1://�ɼ���ƿѹ������һ��
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO1://��ʱ30s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO1://�ж϶�ʱ30s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO2://�ɼ���ƿѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO2://��ʱ30s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO2://�ж϶�ʱ30s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO3://�ɼ���ƿѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO3://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO3://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO4://�ɼ���ƿѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO4://��ʱ30s��ʱ��ʼ�����Ĵ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO4://�ж϶�ʱ30s�����Ĵ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO5://�ɼ���ƿѹ���������
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO5://��ʱ30s��ʱ��ʼ�������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO5://�ж϶�ʱ30s�������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO6://�ɼ���ƿѹ����������
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO6://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO6://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO7://�ɼ���ƿѹ�������ߴ�
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO7://��ʱ30s��ʱ��ʼ�����ߴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO7://�ж϶�ʱ30s�����ߴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO8://�ɼ���ƿѹ�����ڰ˴�
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO8://��ʱ30s��ʱ��ʼ���ڰ˴�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO8://�ж϶�ʱ30s���ڰ˴�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO9://�ɼ���ƿѹ�����ھŴ�
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO9://��ʱ30s��ʱ��ʼ���ھŴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO9://�ж϶�ʱ30s���ھŴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO10://�ɼ���ƿѹ������ʮ��
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE://ѹ���ж���ƿѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**����: �ж���ƿ�����Ƿ����---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IS_COMP_GAS_OVER://�ж���ƿ�����Ƿ����
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
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
**����: ����·��ƿ���ӷ���---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1://����·��ƿ���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1://�жϹ���·��ƿ���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2://����·��ƿ���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2://�жϹ���·��ƿ���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3://����·��ƿ���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3://�жϹ���·��ƿ���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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


/******************************************************************************************
**����: ������ƿ���ӷ���---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON://������ƿ���ӷ���
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_ON://�жϿ�����ƿ���ӷ���
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,SECOND_GAS)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else 
			{
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
**����: ��ʱ�ȴ�time_delay2---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2_START://��ʱ�ȴ�time_delay2��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_DELAY2://�ж���ʱ�ȴ�time_delay2
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
**����: �ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO1://�ɼ���ƿѹ������һ��
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO1://��ʱ30s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO1://�ж϶�ʱ30s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO2://�ɼ���ƿѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO2://��ʱ30s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO2://�ж϶�ʱ30s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO3://�ɼ���ƿѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_2GAS_GAS2_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_2GAS_GAS2_TIME_30S_START_NO3://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO3://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO4://�ɼ���ƿѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO4://��ʱ30s��ʱ��ʼ�����Ĵ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO4://�ж϶�ʱ30s�����Ĵ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO5://�ɼ���ƿѹ���������
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO5://��ʱ30s��ʱ��ʼ�������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO5://�ж϶�ʱ30s�������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO6://�ɼ���ƿѹ����������
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO6://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO6://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO7://�ɼ���ƿѹ�������ߴ�
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO7://��ʱ30s��ʱ��ʼ�����ߴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO7://�ж϶�ʱ30s�����ߴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO8://�ɼ���ƿѹ�����ڰ˴�
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO8://��ʱ30s��ʱ��ʼ���ڰ˴�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO8://�ж϶�ʱ30s���ڰ˴�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO9://�ɼ���ƿѹ�����ھŴ�
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO9://��ʱ30s��ʱ��ʼ���ھŴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO9://�ж϶�ʱ30s���ھŴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO10://�ɼ���ƿѹ������ʮ��
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE://ѹ���ж���ƿѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**����: �ж���ƿ�����Ƿ����---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IS_COMP_GAS_OVER://�ж���ƿ�����Ƿ����
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,FIRST_TANK,SECOND_GAS)==TRUE)
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
**����: ����·��ƿ���ӷ���---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1://����·��ƿ���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1://�жϹ���·��ƿ���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2://����·��ƿ���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2://�жϹ���·��ƿ���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3://����·��ƿ���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3://�жϹ���·��ƿ���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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


/******************************************************************************************
**����: �ؽ������ѹ��·���ӷ���
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO1://�ؽ������ѹ��·���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO1://�жϹؽ������ѹ��·���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO2;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO2://�ؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO2://�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO3://�ؽ������ѹ��·���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO3://�жϹؽ������ѹ��·���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
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


/******************************************************************************************
**����: ͨ��ѹ���жϹؽ����䲹�ӷ�
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

//���������䣡������������������������

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_step_is_in_tank_valve_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO1://ͨ��ѹ���жϹؽ����䲹�ӷ�����һ��
		{
			
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO2://ͨ��ѹ���жϹؽ����䲹�ӷ����ڶ���
		{
			
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO3://ͨ��ѹ���жϹؽ����䲹�ӷ���������
		{
			
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO4://ͨ��ѹ���жϹؽ����䲹�ӷ���������
		{
			
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO5://ͨ��ѹ���жϹؽ����䲹�ӷ���������
		{
			
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE://ͨ��ѹ���жϹؽ����䲹�ӷ�����ȡ��
		{
			
			
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


/*
*****************************************************************************************************************
---------------------------------��������������ڶ����������----------------------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**����: ���������ѹ��·���ӷ���---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_step_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_IN_TANK_VALVE_ON://���������ѹ��·���ӷ���
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				TGTHT510_supply_main_lvb_set(LVb1K);
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				TGTHT510_supply_main_lvb_set(LVb3K);
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				TGTHT510_supply_main_lvb_set(LVb5K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON://�жϿ��������ѹ��·���ӷ���
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: ͨ��ѹ���жϿ������䷧��---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_step_is_in_tank_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE://ͨ��ѹ���жϿ����ӷ���
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O1)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O2)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O3)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: �жϳ�����ƿ����---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_step_number_comp_gas(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_NUMBER_COMP_GAS;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_NUMBER_COMP_GAS://�жϳ�����ƿ����
		{
			if(TGTHT510_supply_common_number_gas(COMP_TANK_O,SECOND_TANK)==ONE_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else if(TGTHT510_supply_common_number_gas(COMP_TANK_O,SECOND_TANK)==TWO_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else 
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
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

/*
*****************************************************************************************************************
---------------------------------��������������ڶ������������һ����ƿ����--------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**����: ������ƿ���ӷ���---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON://������ƿ���ӷ���
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_ON://�жϿ�����ƿ���ӷ���
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,SECOND_TANK,FIRST_GAS)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else 
			{
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
**����: ��ʱ�ȴ�time_delay2---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_DELAY2_START://��ʱ�ȴ�time_delay2��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_DELAY2://�ж���ʱ�ȴ�time_delay2
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
**����: �ж���ƿѹ���Ƿ�����---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO1://�ɼ���ƿѹ������һ��
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_TIME_30S_START_NO1://��ʱ30s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO1://�ж϶�ʱ30s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO2://�ɼ���ƿѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_TIME_30S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_TIME_30S_START_NO2://��ʱ30s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO2;
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO2://�ж϶�ʱ30s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO3://�ɼ���ƿѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_1GAS_TIME_30S_START_NO3;
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_1GAS_TIME_30S_START_NO3://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO3;
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO3://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO4://�ɼ���ƿѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_1GAS_TIME_30S_START_NO4;
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_1GAS_TIME_30S_START_NO4://��ʱ30s��ʱ��ʼ�����Ĵ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO4;
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO4://�ж϶�ʱ30s�����Ĵ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO5://�ɼ���ƿѹ���������
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK2_1GAS_TIME_30S_START_NO5;
			break;
		}
		
		case COMMAND_13_0014_O_2TANK_TANK2_1GAS_TIME_30S_START_NO5://��ʱ30s��ʱ��ʼ�������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO5;
			break;
		}
		
		case COMMAND_13_0015_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO5://�ж϶�ʱ30s�������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0016_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO6://�ɼ���ƿѹ����������
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK2_1GAS_TIME_30S_START_NO6;
			break;
		}
		
		case COMMAND_13_0017_O_2TANK_TANK2_1GAS_TIME_30S_START_NO6://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO6;
			break;
		}
		
		case COMMAND_13_0018_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO6://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0019_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO7://�ɼ���ƿѹ�������ߴ�
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK2_1GAS_TIME_30S_START_NO7;
			break;
		}
		
		case COMMAND_13_0020_O_2TANK_TANK2_1GAS_TIME_30S_START_NO7://��ʱ30s��ʱ��ʼ�����ߴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO7;
			break;
		}
		
		case COMMAND_13_0021_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO7://�ж϶�ʱ30s�����ߴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0022_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO8://�ɼ���ƿѹ�����ڰ˴�
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK2_1GAS_TIME_30S_START_NO8;
			break;
		}
		
		case COMMAND_13_0023_O_2TANK_TANK2_1GAS_TIME_30S_START_NO8://��ʱ30s��ʱ��ʼ���ڰ˴�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO8;
			break;
		}
		
		case COMMAND_13_0024_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO8://�ж϶�ʱ30s���ڰ˴�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0025_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO9://�ɼ���ƿѹ�����ھŴ�
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_2TANK_TANK2_1GAS_TIME_30S_START_NO9;
			break;
		}
		
		case COMMAND_13_0026_O_2TANK_TANK2_1GAS_TIME_30S_START_NO9://��ʱ30s��ʱ��ʼ���ھŴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO9;
			break;
		}
		
		case COMMAND_13_0027_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO9://�ж϶�ʱ30s���ھŴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0028_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO10://�ɼ���ƿѹ������ʮ��
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_2TANK_TANK2_1GAS_IS_GAS_PRESSURE;
			break;
		}
		
		case COMMAND_13_0029_O_2TANK_TANK2_1GAS_IS_GAS_PRESSURE://ѹ���ж���ƿѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**����: �ж���ƿ�����Ƿ����---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_COMP_GAS_OVER://�ж���ƿ�����Ƿ����
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,SECOND_TANK,FIRST_GAS)==TRUE)
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
**����: ����·��ƿ���ӷ���---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO1://����·��ƿ���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO1://�жϹ���·��ƿ���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO2://����·��ƿ���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO2;
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO2://�жϹ���·��ƿ���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO3://����·��ƿ���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO3;
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO3://�жϹ���·��ƿ���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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



/******************************************************************************************
**����: ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_isolation_first(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO1://��ʱ12s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO1://�ж϶�ʱ12s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO2://��ʱ12s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO2://�ж϶�ʱ12s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO3://�ɼ�ѹ��������ѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO3://��ʱ12s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO3://�ж϶�ʱ12s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO4://�ɼ�ѹ��������ѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_1GAS_FIRST_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_1GAS_FIRST_IS_ISOLATION://ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**����: �ر���ѹ�������ڷ���---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_out_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1://�ر���ѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1://�жϹر���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2://�ر���ѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2://�жϹر���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3://�ر���ѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3://�жϹر���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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


/******************************************************************************************
**����: ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������2��
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_isolation_second(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO1://��ʱ12s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO1://�ж϶�ʱ12s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO2://��ʱ12s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO2://�ж϶�ʱ12s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO3://�ɼ�ѹ��������ѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO3://��ʱ12s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO3://�ж϶�ʱ12s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO4://�ɼ�ѹ��������ѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_1GAS_SECOND_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_1GAS_SECOND_IS_ISOLATION://ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_ISOLATION);//��ѹ��·�����쳣
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**����: ��ѹ����ͣ��---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP://�����豸����ָ�ѹ����ͣ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪB
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN://�ж�1min��ʱ
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**����: �ж���ѹ����ͣ���Ƿ�����---�ڶ�������
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

//���������䣡������������������������

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO1://�ɼ����ת�٣���һ��
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO2://�ɼ����ת�٣��ڶ���
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO3://�ɼ����ת�٣�������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO4://�ɼ����ת�٣����Ĵ�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO5://�ɼ����ת�٣������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO6://�ɼ����ת�٣�������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO7://�ɼ����ת�٣����ߴ�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO8://�ɼ����ת�٣��ڰ˴�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_1GAS_TIME_12S_START://��ʱ12s��ʱ��ʼ
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_1GAS_IS_TIME_12S://�ж϶�ʱ12s
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_STOP://�ж���ѹ����ͣ���Ƿ�����
		{
			//�����䣡������
			
			
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
**����: ����ѹ������·������---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_bypath_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_BYPATH_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_BYPATH_VALVE_ON://����ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_lvb_set(LVb21K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_ON;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_lvb_set(LVb87K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_ON;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_ON://�жϿ���ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: ��ʱ�ȴ�time_bypath---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay_bypath(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_BYPATH_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_BYPATH_START://��ʱ�ȴ�time_bypath��ʱ����
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_BYPATH;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_BYPATH://�ж���ʱ�ȴ�time_bypath
		{
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_bypath)==TRUE)
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
**����: ����ѹ������·������---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_bypath_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF://����ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_lvb_set(LVb21G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_OFF://�жϹ���ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: �ر���ѹ�������ڷ���---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_out_compressor_valve_off2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1://�ر���ѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1://�жϹر���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2://�ر���ѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2://�жϹر���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3://�ر���ѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3://�жϹر���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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



/******************************************************************************************
**����: �ر���ѹ�������ڷ���---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1://�ر���ѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb13G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1://�жϹر���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2://�ر���ѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb15G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2://�жϹر���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3://�ر���ѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb23G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3://�жϹر���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb23,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
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



/******************************************************************************************
**����: �ؽ������ѹ��·���ӷ���---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO1://�ؽ������ѹ��·���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO1://�жϹؽ������ѹ��·���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO2://�ؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO2://�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO3://�ؽ������ѹ��·���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO3://�жϹؽ������ѹ��·���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
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

/******************************************************************************************
**����: ����������״̬��---�ڶ�������
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

//���������䣡������������������������

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_set_state_good(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_SET_STATE_GOOD://����������״̬��
		{
			//�����䣡������
			
			
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
**����: �ж�ѹ�����¶��Ƿ�����---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE://�ж�ѹ�����¶��Ƿ�����
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_COMPRESSOR_TEMPERATURE);//ѹ�����ⶨ�¶��쳣
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
**����: �ж��Ƿ���Ҫ����Һ��ģ��ͣ��
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

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_need_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_NEED_COOLER_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_NEED_COOLER_STOP://�ж��Ƿ���Ҫ����Һ��ģ��ͣ��
		{
			if(TGTHT510_supply_decode_par.number_tank_F==3)
			{
				//���е������������䣬������Һ��ģ��ͣ��
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
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
**����: ��ʱ�ȴ�time_delay3---�ڶ�������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay3(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_DELAY3_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_DELAY3_START://��ʱ�ȴ�time_delay3��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_DELAY3;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_DELAY3://�ж���ʱ�ȴ�time_delay3
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
**����: Һ��ģ��ͣ��
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_COOLER_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_COOLER_POWER_OFF://Һ��ģ��ͣ��
		{
			TGTHT510_supply_command_cooler_power_off();
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
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
**����: Һ��ģ��״̬����
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_cooler_set(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_COOLER_SET_NO1;
			break;
		}
		
		//Һ��ģ��״̬����1
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_COOLER_SET_NO1:
		{
			TGTHT510_supply_main_lvb_set(LVb35K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO1;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����1
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO1:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb35,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_COOLER_SET_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����2
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_COOLER_SET_NO2:
		{
			TGTHT510_supply_main_lvb_set(LVb28K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO2;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����2
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO2:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb28,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_COOLER_SET_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����3
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_COOLER_SET_NO3:
		{
			TGTHT510_supply_main_lvb_set(LVb30K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO3;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����3
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO3:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb30,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_1GAS_COOLER_SET_NO4;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����4
		case COMMAND_13_0007_O_2TANK_TANK2_1GAS_COOLER_SET_NO4:
		{
			TGTHT510_supply_main_lvb_set(LVb31G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO4;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����4
		case COMMAND_13_0008_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO4:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb31,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_1GAS_COOLER_SET_NO5;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����5
		case COMMAND_13_0009_O_2TANK_TANK2_1GAS_COOLER_SET_NO5:
		{
			TGTHT510_supply_main_lvb_set(LVb27G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO5;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����5
		case COMMAND_13_0010_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO5:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb27,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_1GAS_COOLER_SET_NO6;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����6
		case COMMAND_13_0011_O_2TANK_TANK2_1GAS_COOLER_SET_NO6:
		{
			TGTHT510_supply_main_lvb_set(LVb29G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO6;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����6
		case COMMAND_13_0012_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO6:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb29,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK2_1GAS_COOLER_SET_NO7;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����7
		case COMMAND_13_0013_O_2TANK_TANK2_1GAS_COOLER_SET_NO7:
		{
			TGTHT510_supply_main_lvb_set(LVb33G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO7;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����7
		case COMMAND_13_0014_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO7:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb33,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK2_1GAS_COOLER_SET_NO8;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����8
		case COMMAND_13_0015_O_2TANK_TANK2_1GAS_COOLER_SET_NO8:
		{
			TGTHT510_supply_main_lvb_set(LVb37G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO8;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����8
		case COMMAND_13_0016_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO8:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb37,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK2_1GAS_COOLER_SET_NO9;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����9
		case COMMAND_13_0017_O_2TANK_TANK2_1GAS_COOLER_SET_NO9:
		{
			TGTHT510_supply_main_lvb_set(LVb32G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO9;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����9
		case COMMAND_13_0018_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO9:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb32,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK2_1GAS_COOLER_SET_NO10;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����10
		case COMMAND_13_0019_O_2TANK_TANK2_1GAS_COOLER_SET_NO10:
		{
			TGTHT510_supply_main_lvb_set(LVb34G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO10;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����10
		case COMMAND_13_0020_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO10:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb34,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK2_1GAS_COOLER_SET_NO11;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����11
		case COMMAND_13_0021_O_2TANK_TANK2_1GAS_COOLER_SET_NO11:
		{
			TGTHT510_supply_main_lvb_set(LVb36G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO11;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����11
		case COMMAND_13_0022_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO11:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb36,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK2_1GAS_COOLER_SET_NO12;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����12
		case COMMAND_13_0023_O_2TANK_TANK2_1GAS_COOLER_SET_NO12:
		{
			TGTHT510_supply_main_lvb_set(LVb38G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO12;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����12
		case COMMAND_13_0024_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO12:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb38,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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


/******************************************************************************************
**����: ����ѹ�����ϵ�
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_compressor_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**����: �������������ϵ�
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_TGTHT530_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530a_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_TGTHT530_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_TGTHT530_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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


/*
*****************************************************************************************************************
---------------------------------��������������ڶ������������������ƿ����--------------------------------------
*****************************************************************************************************************
*/


/******************************************************************************************
**����: ������ƿ���ӷ���---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON://������ƿ���ӷ���
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_ON://�жϿ�����ƿ���ӷ���
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,SECOND_TANK,FIRST_GAS)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else 
			{
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
**����: ��ʱ�ȴ�time_delay2---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2_START://��ʱ�ȴ�time_delay2��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_DELAY2://�ж���ʱ�ȴ�time_delay2
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
**����: �ж���ƿѹ���Ƿ�����---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO1://�ɼ���ƿѹ������һ��
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO1://��ʱ30s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO1://�ж϶�ʱ30s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO2://�ɼ���ƿѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO2://��ʱ30s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO2://�ж϶�ʱ30s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO3://�ɼ���ƿѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO3://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO3://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO4://�ɼ���ƿѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO4://��ʱ30s��ʱ��ʼ�����Ĵ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO4://�ж϶�ʱ30s�����Ĵ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO5://�ɼ���ƿѹ���������
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO5://��ʱ30s��ʱ��ʼ�������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO5://�ж϶�ʱ30s�������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO6://�ɼ���ƿѹ����������
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO6://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO6://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO7://�ɼ���ƿѹ�������ߴ�
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO7://��ʱ30s��ʱ��ʼ�����ߴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO7://�ж϶�ʱ30s�����ߴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO8://�ɼ���ƿѹ�����ڰ˴�
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO8://��ʱ30s��ʱ��ʼ���ڰ˴�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO8://�ж϶�ʱ30s���ڰ˴�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO9://�ɼ���ƿѹ�����ھŴ�
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO9://��ʱ30s��ʱ��ʼ���ھŴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO9://�ж϶�ʱ30s���ھŴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO10://�ɼ���ƿѹ������ʮ��
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE://ѹ���ж���ƿѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**����: �ж���ƿ�����Ƿ����---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IS_COMP_GAS_OVER://�ж���ƿ�����Ƿ����
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,SECOND_TANK,FIRST_GAS)==TRUE)
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
**����: ����·��ƿ���ӷ���---��һ����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1://����·��ƿ���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1://�жϹ���·��ƿ���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2://����·��ƿ���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2://�жϹ���·��ƿ���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3://����·��ƿ���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3://�жϹ���·��ƿ���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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

/******************************************************************************************
**����: ������ƿ���ӷ���---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON://������ƿ���ӷ���
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_ON://�жϿ�����ƿ���ӷ���
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,SECOND_TANK,SECOND_GAS)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else 
			{
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
**����: ��ʱ�ȴ�time_delay2---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2_START://��ʱ�ȴ�time_delay2��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_DELAY2://�ж���ʱ�ȴ�time_delay2
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
**����: �ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO1://�ɼ���ƿѹ������һ��
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO1://��ʱ30s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO1://�ж϶�ʱ30s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO2://�ɼ���ƿѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO2://��ʱ30s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO2://�ж϶�ʱ30s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO3://�ɼ���ƿѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO3://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO3://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO4://�ɼ���ƿѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO4://��ʱ30s��ʱ��ʼ�����Ĵ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO4://�ж϶�ʱ30s�����Ĵ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO5://�ɼ���ƿѹ���������
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO5://��ʱ30s��ʱ��ʼ�������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO5://�ж϶�ʱ30s�������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO6://�ɼ���ƿѹ����������
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO6://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO6://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO7://�ɼ���ƿѹ�������ߴ�
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO7://��ʱ30s��ʱ��ʼ�����ߴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO7://�ж϶�ʱ30s�����ߴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO8://�ɼ���ƿѹ�����ڰ˴�
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO8://��ʱ30s��ʱ��ʼ���ڰ˴�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO8://�ж϶�ʱ30s���ڰ˴�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO9://�ɼ���ƿѹ�����ھŴ�
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO9://��ʱ30s��ʱ��ʼ���ھŴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO9://�ж϶�ʱ30s���ھŴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO10://�ɼ���ƿѹ������ʮ��
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE://ѹ���ж���ƿѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**����: �ж���ƿ�����Ƿ����---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IS_COMP_GAS_OVER://�ж���ƿ�����Ƿ����
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,SECOND_TANK,SECOND_GAS)==TRUE)
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
**����: ����·��ƿ���ӷ���---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1://����·��ƿ���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1://�жϹ���·��ƿ���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2://����·��ƿ���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2://�жϹ���·��ƿ���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3://����·��ƿ���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3://�жϹ���·��ƿ���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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


/******************************************************************************************
**����: ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_isolation_first(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO1://��ʱ12s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO1://�ж϶�ʱ12s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO2://��ʱ12s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO2://�ж϶�ʱ12s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO3://�ɼ�ѹ��������ѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO3://��ʱ12s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO3://�ж϶�ʱ12s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO4://�ɼ�ѹ��������ѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_2GAS_FIRST_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_2GAS_FIRST_IS_ISOLATION://ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**����: �ر���ѹ�������ڷ���
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_out_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1://�ر���ѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1://�жϹر���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2://�ر���ѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2://�жϹر���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3://�ر���ѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3://�жϹر���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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


/******************************************************************************************
**����: ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������2��
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_isolation_second(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO1://��ʱ12s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO1://�ж϶�ʱ12s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO2://��ʱ12s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO2://�ж϶�ʱ12s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO3://�ɼ�ѹ��������ѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO3://��ʱ12s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO3://�ж϶�ʱ12s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO4://�ɼ�ѹ��������ѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_2GAS_SECOND_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_2GAS_SECOND_IS_ISOLATION://ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_ISOLATION);//��ѹ��·�����쳣
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**����: ��ѹ����ͣ��
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP://�����豸����ָ�ѹ����ͣ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN://�ж�1min��ʱ
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**����: �ж���ѹ����ͣ���Ƿ�����
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

//�ú������޸ģ�������������������������

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO1://�ɼ����ת�٣���һ��
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO2://�ɼ����ת�٣��ڶ���
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO3://�ɼ����ת�٣�������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO4://�ɼ����ת�٣����Ĵ�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO5://�ɼ����ת�٣������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO6://�ɼ����ת�٣�������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO7://�ɼ����ת�٣����ߴ�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO8://�ɼ����ת�٣��ڰ˴�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_2GAS_TIME_12S_START://��ʱ12s��ʱ��ʼ
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_2GAS_IS_TIME_12S://�ж϶�ʱ12s
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_STOP://�ж���ѹ����ͣ���Ƿ�����
		{
			//�����䣡������
			
			
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
**����: ����ѹ������·������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_bypath_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_BYPATH_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_BYPATH_VALVE_ON://����ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_lvb_set(LVb21K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_ON;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_lvb_set(LVb87K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_ON;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_ON://�жϿ���ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: ��ʱ�ȴ�time_bypath
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_time_delay_bypath(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_TIME_BYPATH_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_TIME_BYPATH_START://��ʱ�ȴ�time_bypath��ʱ����
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_TIME_BYPATH;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_TIME_BYPATH://�ж���ʱ�ȴ�time_bypath
		{
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_bypath)==TRUE)
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
**����: ����ѹ������·������
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_bypath_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF://����ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_lvb_set(LVb21G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_OFF://�жϹ���ѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
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
**����: �ر���ѹ�������ڷ���
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_out_compressor_valve_off2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1://�ر���ѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1://�жϹر���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2://�ر���ѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2://�жϹر���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3://�ر���ѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3://�жϹر���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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


/******************************************************************************************
**����: �ر���ѹ�������ڷ���
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_in_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1://�ر���ѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb13G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1://�жϹر���ѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2://�ر���ѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb15G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2://�жϹر���ѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3://�ر���ѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb23G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3://�жϹر���ѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb23,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
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


/******************************************************************************************
**����: �ؽ������ѹ��·���ӷ���
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO1://�ؽ������ѹ��·���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO1://�жϹؽ������ѹ��·���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO2;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO2://�ؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO2://�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO3://�ؽ������ѹ��·���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO3://�жϹؽ������ѹ��·���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
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


/******************************************************************************************
**����: ����������״̬��
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

//�����䣡������

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_set_state_good(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_SET_STATE_GOOD://����������״̬��
		{
			//�����䣡������
			
			
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
**����: �ж�ѹ�����¶��Ƿ�����
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE://�ж�ѹ�����¶��Ƿ�����
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_COMPRESSOR_TEMPERATURE);//ѹ�����ⶨ�¶��쳣
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
**����: �ж��Ƿ���Ҫ����Һ��ģ��ͣ��
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

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_need_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_NEED_COOLER_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_NEED_COOLER_STOP://�ж��Ƿ���Ҫ����Һ��ģ��ͣ��
		{
			if(TGTHT510_supply_decode_par.number_tank_F==3)
			{
				//���е������������䣬������Һ��ģ��ͣ��
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
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
**����: ��ʱ�ȴ�time_delay3
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_time_delay3(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_TIME_DELAY3_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_TIME_DELAY3_START://��ʱ�ȴ�time_delay3��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_TIME_DELAY3;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_TIME_DELAY3://�ж���ʱ�ȴ�time_delay3
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
**����: Һ��ģ��ͣ��
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_COOLER_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_COOLER_POWER_OFF://Һ��ģ��ͣ��
		{
			TGTHT510_supply_command_cooler_power_off();
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
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
**����: Һ��ģ��״̬����
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_cooler_set(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_COOLER_SET_NO1;
			break;
		}
		
		//Һ��ģ��״̬����1
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_COOLER_SET_NO1:
		{
			TGTHT510_supply_main_lvb_set(LVb35K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO1;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����1
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO1:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb35,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_COOLER_SET_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����2
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_COOLER_SET_NO2:
		{
			TGTHT510_supply_main_lvb_set(LVb28K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO2;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����2
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO2:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb28,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_COOLER_SET_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����3
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_COOLER_SET_NO3:
		{
			TGTHT510_supply_main_lvb_set(LVb30K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO3;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����3
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO3:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb30,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_2GAS_COOLER_SET_NO4;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����4
		case COMMAND_13_0007_O_2TANK_TANK2_2GAS_COOLER_SET_NO4:
		{
			TGTHT510_supply_main_lvb_set(LVb31G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO4;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����4
		case COMMAND_13_0008_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO4:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb31,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_2GAS_COOLER_SET_NO5;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����5
		case COMMAND_13_0009_O_2TANK_TANK2_2GAS_COOLER_SET_NO5:
		{
			TGTHT510_supply_main_lvb_set(LVb27G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO5;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����5
		case COMMAND_13_0010_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO5:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb27,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_2GAS_COOLER_SET_NO6;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����6
		case COMMAND_13_0011_O_2TANK_TANK2_2GAS_COOLER_SET_NO6:
		{
			TGTHT510_supply_main_lvb_set(LVb29G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO6;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����6
		case COMMAND_13_0012_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO6:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb29,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK2_2GAS_COOLER_SET_NO7;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����7
		case COMMAND_13_0013_O_2TANK_TANK2_2GAS_COOLER_SET_NO7:
		{
			TGTHT510_supply_main_lvb_set(LVb33G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO7;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����7
		case COMMAND_13_0014_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO7:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb33,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK2_2GAS_COOLER_SET_NO8;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����8
		case COMMAND_13_0015_O_2TANK_TANK2_2GAS_COOLER_SET_NO8:
		{
			TGTHT510_supply_main_lvb_set(LVb37G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO8;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����8
		case COMMAND_13_0016_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO8:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb37,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK2_2GAS_COOLER_SET_NO9;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����9
		case COMMAND_13_0017_O_2TANK_TANK2_2GAS_COOLER_SET_NO9:
		{
			TGTHT510_supply_main_lvb_set(LVb32G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO9;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����9
		case COMMAND_13_0018_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO9:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb32,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK2_2GAS_COOLER_SET_NO10;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����10
		case COMMAND_13_0019_O_2TANK_TANK2_2GAS_COOLER_SET_NO10:
		{
			TGTHT510_supply_main_lvb_set(LVb34G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO10;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����10
		case COMMAND_13_0020_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO10:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb34,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK2_2GAS_COOLER_SET_NO11;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����11
		case COMMAND_13_0021_O_2TANK_TANK2_2GAS_COOLER_SET_NO11:
		{
			TGTHT510_supply_main_lvb_set(LVb36G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO11;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����11
		case COMMAND_13_0022_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO11:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb36,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK2_2GAS_COOLER_SET_NO12;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//Һ��ģ��״̬����12
		case COMMAND_13_0023_O_2TANK_TANK2_2GAS_COOLER_SET_NO12:
		{
			TGTHT510_supply_main_lvb_set(LVb38G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO12;
			
			break;
		}
		
		//�ж�Һ��ģ��״̬����12
		case COMMAND_13_0024_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO12:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb38,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
				
			else
			{
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

/******************************************************************************************
**����: ����ѹ�����ϵ�
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_compressor_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**����: �������������ϵ�
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_TGTHT530_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//��ѹ����ΪA
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530a_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//��ѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_TGTHT530_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_TGTHT530_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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


/*
*****************************************************************************************************************
---------------------------------------------------------ͨ�ú���------------------------------------------------
*****************************************************************************************************************
*/



