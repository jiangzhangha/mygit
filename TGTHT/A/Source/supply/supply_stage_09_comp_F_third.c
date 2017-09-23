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
**���ƣ����ӽ׶�9
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_stage09_comp_F_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://��ʼ
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_09_F_INIT_START_COOLER;
			
			break;
		}

//----------------------------------��ʼ���ý׶�------------------------------------------------------
		
		//����Һ��ù���
		case STEP_09_F_INIT_START_COOLER:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_start_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_INIT_IS_COOLER_WORK;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ת���ж�Һ�乤���Ƿ�����
		case STEP_09_F_INIT_IS_COOLER_WORK:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_is_cooler_work()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_INIT_DELAY;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�ʱ��
		case STEP_09_F_INIT_DELAY:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_INIT_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ�����¶��Ƿ�����
		case STEP_09_F_INIT_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_INIT_TGTHT530_POWER_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������������ӵ�
		case STEP_09_F_INIT_TGTHT530_POWER_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_TGTHT530_power_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_INIT_COMPRESSOR_POWER_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ�����ӵ�
		case STEP_09_F_INIT_COMPRESSOR_POWER_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_compressor_power_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_INIT_ISOLATION;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������
		case STEP_09_F_INIT_ISOLATION:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_isolation()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
//----------------------------------һ���������------------------------------------------------------

		//���������ѹ��·���ӷ���
		case STEP_09_F_1TANK_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_TIME_DELAY_A;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�ʱ��
		case STEP_09_F_1TANK_TIME_DELAY_A:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϿ��������ѹ��·���ӷ���
		case STEP_09_F_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_is_in_tank_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_IN_COMPRESSOR_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ȼѹ�������ڷ���
		case STEP_09_F_1TANK_IN_COMPRESSOR_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_in_compressor_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_TIME_DELAY1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay1
		case STEP_09_F_1TANK_TIME_DELAY1:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_time_delay1()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_IS_IN_COMPRESSOR_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ��������ѹ���Ƿ�����
		case STEP_09_F_1TANK_IS_IN_COMPRESSOR_PRESSURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_is_in_compressor_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_COMPRESSOR_START;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ȼѹ��������
		case STEP_09_F_1TANK_COMPRESSOR_START:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_compressor_start()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_TIME_DELAY_B;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�ʱ��
		case STEP_09_F_1TANK_TIME_DELAY_B:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_IS_OUT_COMPRESSOR_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ��������ѹ���Ƿ�����
		case STEP_09_F_1TANK_IS_OUT_COMPRESSOR_PRESSURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_is_out_compressor_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_OUT_COMPRESSOR_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ȼѹ�������ڷ���
		case STEP_09_F_1TANK_OUT_COMPRESSOR_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_out_compressor_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_NUMBER_COMP_GAS;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϳ�����ƿ����
		case STEP_09_F_1TANK_NUMBER_COMP_GAS:
		{
			TGTHT510_supply_stage09_comp_F_1tank_step_number_comp_gas();
			
			break;
		}

//----------------------------------һ�����������һ����ƿ����----------------------------------------

		//������ƿ���ӷ���
		case STEP_09_F_1TANK_1GAS_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay2
		case STEP_09_F_1TANK_1GAS_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿѹ���Ƿ�����
		case STEP_09_F_1TANK_1GAS_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿ�����Ƿ����
		case STEP_09_F_1TANK_1GAS_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ȼ·��ƿ���ӷ���
		case STEP_09_F_1TANK_1GAS_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_ISOLATION_FIRST;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
		case STEP_09_F_1TANK_1GAS_IS_ISOLATION_FIRST:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_isolation_first()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر�ȼѹ�������ڷ���
		case STEP_09_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_out_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_ISOLATION_SECOND;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���
		case STEP_09_F_1TANK_1GAS_IS_ISOLATION_SECOND:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_isolation_second()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ȼѹ����ͣ��
		case STEP_09_F_1TANK_1GAS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ȼѹ����ͣ���Ƿ�����
		case STEP_09_F_1TANK_1GAS_IS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_BYPATH_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ȼѹ������·������
		case STEP_09_F_1TANK_1GAS_BYPATH_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_bypath_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_TIME_DELAY_BYPATH;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_bypath
		case STEP_09_F_1TANK_1GAS_TIME_DELAY_BYPATH:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay_bypath()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ȼѹ������·������
		case STEP_09_F_1TANK_1GAS_BYPATH_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_bypath_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر�ȼѹ�������ڷ��ţ��ڶ���
		case STEP_09_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_out_compressor_valve_off2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر�ȼѹ�������ڷ���
		case STEP_09_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ؽ������ѹ��·���ӷ���
		case STEP_09_F_1TANK_1GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_SET_STATE_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ȼ����״̬��
		case STEP_09_F_1TANK_1GAS_SET_STATE_GOOD:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_set_state_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ�����¶��Ƿ�����
		case STEP_09_F_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_TIME_DELAY3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay3
		case STEP_09_F_1TANK_1GAS_TIME_DELAY3:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay3()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����Һ��ģ���л�����
		case STEP_09_F_1TANK_1GAS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
		case STEP_09_F_1TANK_1GAS_IS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//Һ��ģ��ͣ��
		case STEP_09_F_1TANK_1GAS_COOLER_STOP:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_COMPRESSOR_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ�����ϵ�
		case STEP_09_F_1TANK_1GAS_COMPRESSOR_POWER_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_compressor_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_TGTHT530_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������������ϵ�
		case STEP_09_F_1TANK_1GAS_TGTHT530_POWER_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_TGTHT530_power_off()==TRUE)
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
		case STEP_09_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS1_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay2---��һ����ƿ
		case STEP_09_F_1TANK_2GAS_GAS1_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS1_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿѹ���Ƿ�����---��һ����ƿ
		case STEP_09_F_1TANK_2GAS_GAS1_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS1_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿ�����Ƿ����---��һ����ƿ
		case STEP_09_F_1TANK_2GAS_GAS1_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ȼ·��ƿ���ӷ���---��һ����ƿ
		case STEP_09_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//������ƿ���ӷ���---�ڶ�����ƿ
		case STEP_09_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS2_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
		case STEP_09_F_1TANK_2GAS_GAS2_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS2_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
		case STEP_09_F_1TANK_2GAS_GAS2_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS2_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
		case STEP_09_F_1TANK_2GAS_GAS2_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ȼ·��ƿ���ӷ���---�ڶ�����ƿ
		case STEP_09_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IS_ISOLATION_FIRST;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
		case STEP_09_F_1TANK_2GAS_IS_ISOLATION_FIRST:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_isolation_first()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر�ȼѹ�������ڷ���
		case STEP_09_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_out_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IS_ISOLATION_SECOND;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���
		case STEP_09_F_1TANK_2GAS_IS_ISOLATION_SECOND:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_isolation_second()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ȼѹ����ͣ��
		case STEP_09_F_1TANK_2GAS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ȼѹ����ͣ���Ƿ�����
		case STEP_09_F_1TANK_2GAS_IS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_BYPATH_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ȼѹ������·������
		case STEP_09_F_1TANK_2GAS_BYPATH_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_bypath_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_TIME_DELAY_BYPATH;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_bypath
		case STEP_09_F_1TANK_2GAS_TIME_DELAY_BYPATH:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_time_delay_bypath()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ȼѹ������·������
		case STEP_09_F_1TANK_2GAS_BYPATH_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_bypath_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر�ȼѹ�������ڷ��ţ��ڶ���
		case STEP_09_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_out_compressor_valve_off2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ر�ȼѹ�������ڷ���
		case STEP_09_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_in_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ؽ������ѹ��·���ӷ���
		case STEP_09_F_1TANK_2GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_SET_STATE_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ȼ����״̬��
		case STEP_09_F_1TANK_2GAS_SET_STATE_GOOD:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_set_state_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж�ѹ�����¶��Ƿ�����
		case STEP_09_F_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_TIME_DELAY3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�time_delay3
		case STEP_09_F_1TANK_2GAS_TIME_DELAY3:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_time_delay3()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����Һ��ģ���л�����
		case STEP_09_F_1TANK_2GAS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
		case STEP_09_F_1TANK_2GAS_IS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//Һ��ģ��ͣ��
		case STEP_09_F_1TANK_2GAS_COOLER_STOP:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_COMPRESSOR_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//����ѹ�����ϵ�
		case STEP_09_F_1TANK_2GAS_COMPRESSOR_POWER_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_compressor_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_TGTHT530_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������������ϵ�
		case STEP_09_F_1TANK_2GAS_TGTHT530_POWER_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_TGTHT530_power_off()==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_init_step_start_cooler(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_INIT_COOLER_VALVE_ON_NO1;
			break;
		}
		
		//Һ��ģ�鲹��ϵͳ���ſ���һ��
		case COMMAND_09_0001_F_INIT_COOLER_VALVE_ON_NO1:
		{
			TGTHT510_supply_command_cooler_valve_on(1);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_IS_COOLER_VALVE_ON_NO1;
			
			break;
		}
		
		//�ж�Һ��ģ�鲹��ϵͳ���ſ���һ��
		case COMMAND_09_0002_F_INIT_IS_COOLER_VALVE_ON_NO1:
		{
			if(TGTHT510_supply_command_is_cooler_valve_on(1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_INIT_COOLER_VALVE_ON_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ�鲹��ϵͳ���ſ��ڶ���
		case COMMAND_09_0003_F_INIT_COOLER_VALVE_ON_NO2:
		{
			TGTHT510_supply_command_cooler_valve_on(2);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_INIT_IS_COOLER_VALVE_ON_NO2;
			
			break;
		}
		
		//�ж�Һ��ģ�鲹��ϵͳ���ſ��ڶ���
		case COMMAND_09_0004_F_INIT_IS_COOLER_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_command_is_cooler_valve_on(2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_INIT_COOLER_POWER_ON;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//Һ��ģ�鹩��ͨ
		case COMMAND_09_0005_F_INIT_COOLER_POWER_ON:
		{
			TGTHT510_supply_command_cooler_power_on();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_INIT_TIME_1MIN_START;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ
		case COMMAND_09_0006_F_INIT_TIME_1MIN_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_INIT_IS_TIME_1MIN;
			
			break;
		}
		
		//��ʱ1min�Ƿ�
		case COMMAND_09_0007_F_INIT_IS_TIME_1MIN:
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

uint16 TGTHT510_supply_stage09_comp_F_init_step_is_cooler_work(void)
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
		
		case COMMAND_09_0001_F_INIT_IS_COOLER_WORK:
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
uint16 TGTHT510_supply_stage09_comp_F_init_step_time_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_INIT_TIME_DELAY_START;
			break;
		}
		
		case COMMAND_09_0001_F_INIT_TIME_DELAY_START://��ʱ�ȴ�time_delay1��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_IS_TIME_DELAY;
	
			break;
		}
		
		case COMMAND_09_0002_F_INIT_IS_TIME_DELAY://�ж���ʱ�ȴ�time_delay1
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
uint16 TGTHT510_supply_stage09_comp_F_init_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_INIT_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_09_0001_F_INIT_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_F)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_init_step_TGTHT530_power_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_INIT_TGTHT530_POWER_ON;
			break;
		}
		
		case COMMAND_09_0001_F_INIT_TGTHT530_POWER_ON://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530b_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			break;
		}
		
		case COMMAND_09_0002_F_INIT_TGTHT530_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_INIT_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_INIT_TGTHT530_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
		{
			
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_INIT_TGTHT530_IS_POWER_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0004_F_INIT_TGTHT530_IS_POWER_ON://ͨ�����������жϼӵ��Ƿ�����
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
uint16 TGTHT510_supply_stage09_comp_F_init_step_compressor_power_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_INIT_COMPRESSOR_POWER_ON;
			break;
		}
		
		case COMMAND_09_0001_F_INIT_COMPRESSOR_POWER_ON://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_B_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}

			break;
		}
		
		case COMMAND_09_0002_F_INIT_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_INIT_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_INIT_COMPRESSOR_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
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
uint16 TGTHT510_supply_stage09_comp_F_init_step_isolation(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_INIT_ISOLATION_VALVE_OFF_NO1;
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ���һ��
		case COMMAND_09_0001_F_INIT_ISOLATION_VALVE_OFF_NO1:
		{
			TGTHT510_supply_command_third_isolation_valve_off(1,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_TIME_1MIN_START_NO1;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ����һ��
		case COMMAND_09_0002_F_INIT_TIME_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_INIT_IS_TIME_1MIN_NO1;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣���һ��
		case COMMAND_09_0003_F_INIT_IS_TIME_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_INIT_IS_ISOLATION_VALVE_OFF_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ���һ��
		case COMMAND_09_0004_F_INIT_IS_ISOLATION_VALVE_OFF_NO1:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(1,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_INIT_ISOLATION_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ��ڶ���
		case COMMAND_09_0005_F_INIT_ISOLATION_VALVE_OFF_NO2:
		{
			TGTHT510_supply_command_third_isolation_valve_off(2,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_INIT_TIME_1MIN_START_NO2;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ���ڶ���
		case COMMAND_09_0006_F_INIT_TIME_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_INIT_IS_TIME_1MIN_NO2;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣��ڶ���
		case COMMAND_09_0007_F_INIT_IS_TIME_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_INIT_IS_ISOLATION_VALVE_OFF_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ��ڶ���
		case COMMAND_09_0008_F_INIT_IS_ISOLATION_VALVE_OFF_NO2:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(2,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_INIT_ISOLATION_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ�������
		case COMMAND_09_0009_F_INIT_ISOLATION_VALVE_OFF_NO3:
		{
			TGTHT510_supply_command_third_isolation_valve_off(3,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_INIT_TIME_1MIN_START_NO3;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ��������
		case COMMAND_09_0010_F_INIT_TIME_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_INIT_IS_TIME_1MIN_NO3;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣�������
		case COMMAND_09_0011_F_INIT_IS_TIME_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0012_F_INIT_IS_ISOLATION_VALVE_OFF_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ�������
		case COMMAND_09_0012_F_INIT_IS_ISOLATION_VALVE_OFF_NO3:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(3,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0013_F_INIT_ISOLATION_VALVE_OFF_NO4;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ�������
		case COMMAND_09_0013_F_INIT_ISOLATION_VALVE_OFF_NO4:
		{
			TGTHT510_supply_command_third_isolation_valve_off(4,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0014_F_INIT_TIME_1MIN_START_NO4;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ��������
		case COMMAND_09_0014_F_INIT_TIME_1MIN_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0015_F_INIT_IS_TIME_1MIN_NO4;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣�������
		case COMMAND_09_0015_F_INIT_IS_TIME_1MIN_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0016_F_INIT_IS_ISOLATION_VALVE_OFF_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ�������
		case COMMAND_09_0016_F_INIT_IS_ISOLATION_VALVE_OFF_NO4:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(4,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0017_F_INIT_ISOLATION_VALVE_OFF_NO5;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ�������
		case COMMAND_09_0017_F_INIT_ISOLATION_VALVE_OFF_NO5:
		{
			TGTHT510_supply_command_third_isolation_valve_off(5,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0018_F_INIT_TIME_1MIN_START_NO5;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ��������
		case COMMAND_09_0018_F_INIT_TIME_1MIN_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0019_F_INIT_IS_TIME_1MIN_NO5;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣�������
		case COMMAND_09_0019_F_INIT_IS_TIME_1MIN_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0020_F_INIT_IS_ISOLATION_VALVE_OFF_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ�������
		case COMMAND_09_0020_F_INIT_IS_ISOLATION_VALVE_OFF_NO5:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(5,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0021_F_INIT_ISOLATION_VALVE_OFF_NO6;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ�������
		case COMMAND_09_0021_F_INIT_ISOLATION_VALVE_OFF_NO6:
		{
			TGTHT510_supply_command_third_isolation_valve_off(6,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0022_F_INIT_TIME_1MIN_START_NO6;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ��������
		case COMMAND_09_0022_F_INIT_TIME_1MIN_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0023_F_INIT_IS_TIME_1MIN_NO6;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣�������
		case COMMAND_09_0023_F_INIT_IS_TIME_1MIN_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0024_F_INIT_IS_ISOLATION_VALVE_OFF_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ�������
		case COMMAND_09_0024_F_INIT_IS_ISOLATION_VALVE_OFF_NO6:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(6,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0025_F_INIT_ISOLATION_VALVE_OFF_NO7;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ�������
		case COMMAND_09_0025_F_INIT_ISOLATION_VALVE_OFF_NO7:
		{
			TGTHT510_supply_command_third_isolation_valve_off(7,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0026_F_INIT_TIME_1MIN_START_NO7;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ��������
		case COMMAND_09_0026_F_INIT_TIME_1MIN_START_NO7:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0027_F_INIT_IS_TIME_1MIN_NO7;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣�������
		case COMMAND_09_0027_F_INIT_IS_TIME_1MIN_NO7:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0028_F_INIT_IS_ISOLATION_VALVE_OFF_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ�������
		case COMMAND_09_0028_F_INIT_IS_ISOLATION_VALVE_OFF_NO7:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(7,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0029_F_INIT_ISOLATION_VALVE_OFF_NO8;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ��ڰ���
		case COMMAND_09_0029_F_INIT_ISOLATION_VALVE_OFF_NO8:
		{
			TGTHT510_supply_command_third_isolation_valve_off(8,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0030_F_INIT_TIME_1MIN_START_NO8;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ���ڰ���
		case COMMAND_09_0030_F_INIT_TIME_1MIN_START_NO8:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0031_F_INIT_IS_TIME_1MIN_NO8;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣��ڰ���
		case COMMAND_09_0031_F_INIT_IS_TIME_1MIN_NO8:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0032_F_INIT_IS_ISOLATION_VALVE_OFF_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ��ڰ���
		case COMMAND_09_0032_F_INIT_IS_ISOLATION_VALVE_OFF_NO8:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(8,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0033_F_INIT_ISOLATION_VALVE_OFF_NO9;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//���Źرմ�����ͣ���´��������
			}
			
			break;
		}
		
		//�����ƽ�ϵͳ�������رգ��ھ���
		case COMMAND_09_0033_F_INIT_ISOLATION_VALVE_OFF_NO9:
		{
			TGTHT510_supply_command_third_isolation_valve_off(9,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0034_F_INIT_TIME_1MIN_START_NO9;
			
			break;
		}
		
		//��ʱ1min��ʱ��ʼ���ھ���
		case COMMAND_09_0034_F_INIT_TIME_1MIN_START_NO9:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0035_F_INIT_IS_TIME_1MIN_NO9;
			
			break;
		}
		
		//��ʱ1min�Ƿ񵽣��ھ���
		case COMMAND_09_0035_F_INIT_IS_TIME_1MIN_NO9:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0036_F_INIT_IS_ISOLATION_VALVE_OFF_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϸ����ƽ�ϵͳ�������رգ��ھ���
		case COMMAND_09_0036_F_INIT_IS_ISOLATION_VALVE_OFF_NO9:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(9,ISOLATION_TANK_F))==TRUE)
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


/*
*****************************************************************************************************************
-------------------------------------------------�������������----------------------------------------------------
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_IN_TANK_VALVE_ON://���������ѹ��·���ӷ���
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				TGTHT510_supply_main_lvb_set(LVb2K);
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				TGTHT510_supply_main_lvb_set(LVb4K);
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				TGTHT510_supply_main_lvb_set(LVb6K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_IS_IN_TANK_VALVE_ON://�жϿ��������ѹ��·���ӷ���
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb02,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb04,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb06,VALVE_ON)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_is_in_tank_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE://ͨ��ѹ���жϿ����ӷ���
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_F1)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_F2)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_F3)==TRUE)
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
**���ƣ���ȼѹ�������ڷ���
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_in_compressor_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO1://��ȼѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
			{
				TGTHT510_supply_main_lvb_set(LVb14K);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_main_lvb_set(LVb24K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO1;

			break;
		}
		
		case COMMAND_09_0002_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO1://�жϿ�ȼѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb14,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO2;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb24,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO2;
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
		
		case COMMAND_09_0003_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO2://��ȼѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
			{
				TGTHT510_supply_main_lvb_set(LVb16K);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
			{
				asm("nop;");
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO2://�жϿ�ȼѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb16,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO3;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO3://��ȼѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
			{
				TGTHT510_supply_main_lvb_set(LVb22G);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO3;

			break;
		}
		
		case COMMAND_09_0006_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO3://�жϿ�ȼѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb22,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_time_delay1(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_TIME_DELAY1_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_TIME_DELAY1_START://��ʱ�ȴ�time_delay1��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_IS_TIME_DELAY1;
	
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_IS_TIME_DELAY1://�ж���ʱ�ȴ�time_delay1
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_is_in_compressor_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_IS_IN_COMPRESSOR_PRESSURE;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_IS_IN_COMPRESSOR_PRESSURE://�ж�ѹ��������ѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_in_compressor_pressure(COMP_TANK_F)==TRUE)
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
**����: ȼѹ��������
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_compressor_start(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_COMPRESSOR_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_COMPRESSOR_START://�����豸����ָ�ѹ��������
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_B_START);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_START);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_COMPRESSOR_IS_TIME_1MIN://�ж�1min��ʱ
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_IS_COMPRESSOR_START;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_IS_COMPRESSOR_START://ͨ�����������ж������Ƿ�����
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_is_out_compressor_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_IS_OUT_COMPRESSOR_PRESSURE;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_IS_OUT_COMPRESSOR_PRESSURE://�ж�ѹ��������ѹ���Ƿ�����
		{
			if(TGTHT510_supply_common_is_out_compressor_pressure(COMP_TANK_F)==TRUE)
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
**����: ��ȼѹ�������ڷ���
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_out_compressor_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_OUT_COMPRESSOR_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_OUT_COMPRESSOR_VALVE_ON://��ȼѹ�������ڷ���
		{
			TGTHT510_supply_common_out_compressor_valve_on(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_IS_OUT_COMPRESSOR_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_IS_OUT_COMPRESSOR_VALVE_ON://�жϿ�ȼѹ�������ڷ���
		{
			if(TGTHT510_supply_common_is_out_compressor_valve_on(COMP_TANK_F)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_number_comp_gas(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_NUMBER_COMP_GAS;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_NUMBER_COMP_GAS://�жϳ�����ƿ����
		{
			if(TGTHT510_supply_common_number_gas(COMP_TANK_F,FIRST_TANK)==ONE_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else if(TGTHT510_supply_common_number_gas(COMP_TANK_F,FIRST_TANK)==TWO_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON;
				
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IN_GAS_VALVE_ON://������ƿ���ӷ���
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_IN_GAS_VALVE_ON://�жϿ�����ƿ���ӷ���
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_F,THIRD_TANK,FIRST_GAS)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_TIME_DELAY2_START://��ʱ�ȴ�time_delay2��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_DELAY2://�ж���ʱ�ȴ�time_delay2
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_GAS_PRESSURE_NO1://�ɼ���ƿѹ������һ��
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_TIME_30S_START_NO1://��ʱ30s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_IS_TIME_30S_NO1://�ж϶�ʱ30s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_GAS_PRESSURE_NO2://�ɼ���ƿѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_TIME_30S_START_NO2;
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_TIME_30S_START_NO2://��ʱ30s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_TIME_30S_NO2;
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_TIME_30S_NO2://�ж϶�ʱ30s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_1GAS_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_1GAS_GAS_PRESSURE_NO3://�ɼ���ƿѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_1GAS_TIME_30S_START_NO3;
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_1GAS_TIME_30S_START_NO3://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_1GAS_IS_TIME_30S_NO3;
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_1GAS_IS_TIME_30S_NO3://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_1GAS_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_1GAS_GAS_PRESSURE_NO4://�ɼ���ƿѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_1GAS_TIME_30S_START_NO4;
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_1GAS_TIME_30S_START_NO4://��ʱ30s��ʱ��ʼ�����Ĵ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0012_F_1TANK_1GAS_IS_TIME_30S_NO4;
			break;
		}
		
		case COMMAND_09_0012_F_1TANK_1GAS_IS_TIME_30S_NO4://�ж϶�ʱ30s�����Ĵ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0013_F_1TANK_1GAS_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0013_F_1TANK_1GAS_GAS_PRESSURE_NO5://�ɼ���ƿѹ���������
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0014_F_1TANK_1GAS_TIME_30S_START_NO5;
			break;
		}
		
		case COMMAND_09_0014_F_1TANK_1GAS_TIME_30S_START_NO5://��ʱ30s��ʱ��ʼ�������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0015_F_1TANK_1GAS_IS_TIME_30S_NO5;
			break;
		}
		
		case COMMAND_09_0015_F_1TANK_1GAS_IS_TIME_30S_NO5://�ж϶�ʱ30s�������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0016_F_1TANK_1GAS_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0016_F_1TANK_1GAS_GAS_PRESSURE_NO6://�ɼ���ƿѹ����������
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0017_F_1TANK_1GAS_TIME_30S_START_NO6;
			break;
		}
		
		case COMMAND_09_0017_F_1TANK_1GAS_TIME_30S_START_NO6://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0018_F_1TANK_1GAS_IS_TIME_30S_NO6;
			break;
		}
		
		case COMMAND_09_0018_F_1TANK_1GAS_IS_TIME_30S_NO6://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0019_F_1TANK_1GAS_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0019_F_1TANK_1GAS_GAS_PRESSURE_NO7://�ɼ���ƿѹ�������ߴ�
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0020_F_1TANK_1GAS_TIME_30S_START_NO7;
			break;
		}
		
		case COMMAND_09_0020_F_1TANK_1GAS_TIME_30S_START_NO7://��ʱ30s��ʱ��ʼ�����ߴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0021_F_1TANK_1GAS_IS_TIME_30S_NO7;
			break;
		}
		
		case COMMAND_09_0021_F_1TANK_1GAS_IS_TIME_30S_NO7://�ж϶�ʱ30s�����ߴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0022_F_1TANK_1GAS_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0022_F_1TANK_1GAS_GAS_PRESSURE_NO8://�ɼ���ƿѹ�����ڰ˴�
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0023_F_1TANK_1GAS_TIME_30S_START_NO8;
			break;
		}
		
		case COMMAND_09_0023_F_1TANK_1GAS_TIME_30S_START_NO8://��ʱ30s��ʱ��ʼ���ڰ˴�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0024_F_1TANK_1GAS_IS_TIME_30S_NO8;
			break;
		}
		
		case COMMAND_09_0024_F_1TANK_1GAS_IS_TIME_30S_NO8://�ж϶�ʱ30s���ڰ˴�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0025_F_1TANK_1GAS_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0025_F_1TANK_1GAS_GAS_PRESSURE_NO9://�ɼ���ƿѹ�����ھŴ�
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0026_F_1TANK_1GAS_TIME_30S_START_NO9;
			break;
		}
		
		case COMMAND_09_0026_F_1TANK_1GAS_TIME_30S_START_NO9://��ʱ30s��ʱ��ʼ���ھŴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0027_F_1TANK_1GAS_IS_TIME_30S_NO9;
			break;
		}
		
		case COMMAND_09_0027_F_1TANK_1GAS_IS_TIME_30S_NO9://�ж϶�ʱ30s���ھŴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0028_F_1TANK_1GAS_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0028_F_1TANK_1GAS_GAS_PRESSURE_NO10://�ɼ���ƿѹ������ʮ��
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0029_F_1TANK_1GAS_IS_GAS_PRESSURE;
			break;
		}
		
		case COMMAND_09_0029_F_1TANK_1GAS_IS_GAS_PRESSURE://ѹ���ж���ƿѹ���Ƿ�����
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IS_COMP_GAS_OVER://�ж���ƿ�����Ƿ����
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_F,THIRD_TANK,FIRST_GAS)==TRUE)
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
**����: ��ȼ·��ƿ���ӷ���
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			//�ɼ��ط�֮ǰ��ѹ��������ѹ��ֵ
			temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO1://��ȼ·��ƿ���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb8G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO1://�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb08,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO2://��ȼ·��ƿ���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb10G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO2;
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO2://�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb10,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO3://��ȼ·��ƿ���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb12G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO3;
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO3://�жϹ�ȼ·��ƿ���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb12,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_isolation_first(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO1;
			
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_FIRST_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_FIRST_TIME_12S_START_NO1://��ʱ12s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO1://�ж϶�ʱ12s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_FIRST_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_FIRST_TIME_12S_START_NO2://��ʱ12s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO2://�ж϶�ʱ12s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO3://�ɼ�ѹ��������ѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_1GAS_FIRST_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_1GAS_FIRST_TIME_12S_START_NO3://��ʱ12s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO3://�ж϶�ʱ12s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO4://�ɼ�ѹ��������ѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_1GAS_FIRST_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_1GAS_FIRST_IS_ISOLATION://ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_COMPRESSOR_STOP;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF;
				
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
**����: �ر�ȼѹ�������ڷ���
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_out_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1://�ر�ȼѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb18G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1://�жϹر�ȼѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb18,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2://�ر�ȼѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb20G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2://�жϹر�ȼѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb20,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3://�ر�ȼѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb26G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3://�жϹر�ȼѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb26,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_isolation_second(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_SECOND_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_SECOND_TIME_12S_START_NO1://��ʱ12s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO1://�ж϶�ʱ12s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_SECOND_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_SECOND_TIME_12S_START_NO2://��ʱ12s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO2://�ж϶�ʱ12s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO3://�ɼ�ѹ��������ѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_1GAS_SECOND_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_1GAS_SECOND_TIME_12S_START_NO3://��ʱ12s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO3://�ж϶�ʱ12s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO4://�ɼ�ѹ��������ѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_1GAS_SECOND_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_1GAS_SECOND_IS_ISOLATION://ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����
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
**����: ȼѹ����ͣ��
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_COMPRESSOR_STOP;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_COMPRESSOR_STOP://�����豸����ָ�ѹ����ͣ��
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_B_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN://�ж�1min��ʱ
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
**����: �ж�ȼѹ����ͣ���Ƿ�����
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

uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_compressor_stop(void)
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
		
		case COMMAND_09_0001_F_1TANK_1GAS_COMPRESSOR_V_NO1://�ɼ����ת�٣���һ��
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_V_NO2://�ɼ����ת�٣��ڶ���
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_COMPRESSOR_V_NO3://�ɼ����ת�٣�������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_COMPRESSOR_V_NO4://�ɼ����ת�٣����Ĵ�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_COMPRESSOR_V_NO5://�ɼ����ת�٣������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_COMPRESSOR_V_NO6://�ɼ����ת�٣�������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_1GAS_COMPRESSOR_V_NO7://�ɼ����ת�٣����ߴ�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_1GAS_COMPRESSOR_V_NO8://�ɼ����ת�٣��ڰ˴�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_1GAS_TIME_12S_START://��ʱ12s��ʱ��ʼ
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_1GAS_IS_TIME_12S://�ж϶�ʱ12s
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0012_F_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0013_F_1TANK_1GAS_IS_COMPRESSOR_STOP://�ж�ȼѹ����ͣ���Ƿ�����
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
**����: ��ȼѹ������·������
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_bypath_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_BYPATH_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_BYPATH_VALVE_ON://��ȼѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				TGTHT510_supply_main_lvb_set(LVb22K);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_ON;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
			{
				TGTHT510_supply_main_lvb_set(LVb87K);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_ON;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_ON://�жϿ�ȼѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb22,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay_bypath(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_TIME_BYPATH_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_TIME_BYPATH_START://��ʱ�ȴ�time_bypath��ʱ����
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_BYPATH;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_BYPATH://�ж���ʱ�ȴ�time_bypath
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
**����: ��ȼѹ������·������
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_bypath_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_BYPATH_VALVE_OFF;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_BYPATH_VALVE_OFF://��ȼѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				TGTHT510_supply_main_lvb_set(LVb22G);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_OFF://�жϹ�ȼѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb22,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
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
**����: �ر�ȼѹ�������ڷ��ţ��ڶ���
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_out_compressor_valve_off2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1://�ر�ȼѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb18G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1://�жϹر�ȼѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb18,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2://�ر�ȼѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb20G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2://�жϹر�ȼѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb20,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3://�ر�ȼѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb26G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3://�жϹر�ȼѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb26,VALVE_OFF)==TRUE)
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
**����: �ر�ȼѹ�������ڷ���
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1://�ر�ȼѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb14G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1://�жϹر�ȼѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb14,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2://�ر�ȼѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb16G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2://�жϹر�ȼѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb16,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3://�ر�ȼѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb24G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3://�жϹر�ȼѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb24,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO1://�ؽ������ѹ��·���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb2G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO1://�жϹؽ������ѹ��·���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb02,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO2://�ؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb4G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO2://�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb04,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO3://�ؽ������ѹ��·���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb6G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO3://�жϹؽ������ѹ��·���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb06,VALVE_OFF)==TRUE)
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
**����: ����ȼ����״̬��
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

uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_set_state_good(void)
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
		
		case COMMAND_09_0001_F_1TANK_1GAS_SET_STATE_GOOD://����ȼ����״̬��
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE://�ж�ѹ�����¶��Ƿ�����
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_F)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay3(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_TIME_DELAY3_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_TIME_DELAY3_START://��ʱ�ȴ�time_delay3��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_DELAY3;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_DELAY3://�ж���ʱ�ȴ�time_delay3
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
**����: ����Һ��ģ���л�����
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_exchange_cooler(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO1://Һ��ģ���л����򣬷��Ŷ�������һ��
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO1);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO1://�ж�Һ��ģ���л����򣬷��Ŷ�������һ��
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO2;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO2://Һ��ģ���л����򣬷��Ŷ������ڶ���
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO2);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO2://�ж�Һ��ģ���л����򣬷��Ŷ������ڶ���
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO3://Һ��ģ���л����򣬷��Ŷ�����������
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO3);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO3://�ж�Һ��ģ���л����򣬷��Ŷ�����������
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO3)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO4;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO4://Һ��ģ���л����򣬷��Ŷ�����������
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO4);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO4;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO4://�ж�Һ��ģ���л����򣬷��Ŷ�����������
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
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
**����: ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_exchange_cooler(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IS_EXCHANGE_COOLER;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IS_EXCHANGE_COOLER://ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
		{
			if(TGTHT510_supply_common_is_exchange_cooler_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER_PRESSURE);//ͨ��ѹ���ж�Һ��ģ���л������쳣
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_COOLER_POWER_OFF;
			break;
		}
	
		case COMMAND_09_0001_F_1TANK_1GAS_COOLER_POWER_OFF://Һ��ģ��ͣ��
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_compressor_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_COMPRESSOR_POWER_OFF;
			break;
		}
	
		case COMMAND_09_0001_F_1TANK_1GAS_COMPRESSOR_POWER_OFF://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_B_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_TGTHT530_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_TGTHT530_POWER_OFF;
			break;
		}
	
		case COMMAND_09_0001_F_1TANK_1GAS_TGTHT530_POWER_OFF://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530b_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_TGTHT530_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_TGTHT530_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
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
-----------------------------------���������������������ƿ����----------------------------------------------------
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON://������ƿ���ӷ���
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_ON://�жϿ�����ƿ���ӷ���
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_F,THIRD_TANK,FIRST_GAS)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS1_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS1_TIME_DELAY2_START://��ʱ�ȴ�time_delay2��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_TIME_DELAY2://�ж���ʱ�ȴ�time_delay2
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO1://�ɼ���ƿѹ������һ��
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS1_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS1_TIME_30S_START_NO1://��ʱ30s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO1://�ж϶�ʱ30s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO2://�ɼ���ƿѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_GAS1_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_GAS1_TIME_30S_START_NO2://��ʱ30s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO2://�ж϶�ʱ30s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO3://�ɼ���ƿѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_2GAS_GAS1_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_2GAS_GAS1_TIME_30S_START_NO3://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO3://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO4://�ɼ���ƿѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_2GAS_GAS1_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_2GAS_GAS1_TIME_30S_START_NO4://��ʱ30s��ʱ��ʼ�����Ĵ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0012_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_09_0012_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO4://�ж϶�ʱ30s�����Ĵ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0013_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0013_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO5://�ɼ���ƿѹ���������
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0014_F_1TANK_2GAS_GAS1_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_09_0014_F_1TANK_2GAS_GAS1_TIME_30S_START_NO5://��ʱ30s��ʱ��ʼ�������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0015_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_09_0015_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO5://�ж϶�ʱ30s�������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0016_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0016_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO6://�ɼ���ƿѹ����������
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0017_F_1TANK_2GAS_GAS1_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_09_0017_F_1TANK_2GAS_GAS1_TIME_30S_START_NO6://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0018_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_09_0018_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO6://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0019_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0019_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO7://�ɼ���ƿѹ�������ߴ�
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0020_F_1TANK_2GAS_GAS1_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_09_0020_F_1TANK_2GAS_GAS1_TIME_30S_START_NO7://��ʱ30s��ʱ��ʼ�����ߴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0021_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_09_0021_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO7://�ж϶�ʱ30s�����ߴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0022_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0022_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO8://�ɼ���ƿѹ�����ڰ˴�
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0023_F_1TANK_2GAS_GAS1_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_09_0023_F_1TANK_2GAS_GAS1_TIME_30S_START_NO8://��ʱ30s��ʱ��ʼ���ڰ˴�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0024_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_09_0024_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO8://�ж϶�ʱ30s���ڰ˴�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0025_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0025_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO9://�ɼ���ƿѹ�����ھŴ�
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0026_F_1TANK_2GAS_GAS1_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_09_0026_F_1TANK_2GAS_GAS1_TIME_30S_START_NO9://��ʱ30s��ʱ��ʼ���ھŴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0027_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_09_0027_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO9://�ж϶�ʱ30s���ھŴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0028_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0028_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO10://�ɼ���ƿѹ������ʮ��
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0029_F_1TANK_2GAS_GAS1_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_09_0029_F_1TANK_2GAS_GAS1_IS_GAS_PRESSURE://ѹ���ж���ƿѹ���Ƿ�����
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS1_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS1_IS_COMP_GAS_OVER://�ж���ƿ�����Ƿ����
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_F,THIRD_TANK,FIRST_GAS)==TRUE)
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
**����: ��ȼ·��ƿ���ӷ���---��һ����ƿ
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1://��ȼ·��ƿ���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb8G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1://�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb08,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2://��ȼ·��ƿ���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb10G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2://�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb10,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3://��ȼ·��ƿ���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb12G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3://�жϹ�ȼ·��ƿ���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb12,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON://������ƿ���ӷ���
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_ON://�жϿ�����ƿ���ӷ���
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_F,THIRD_TANK,SECOND_GAS)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS2_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS2_TIME_DELAY2_START://��ʱ�ȴ�time_delay2��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_TIME_DELAY2://�ж���ʱ�ȴ�time_delay2
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO1://�ɼ���ƿѹ������һ��
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS2_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS2_TIME_30S_START_NO1://��ʱ30s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO1://�ж϶�ʱ30s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO2://�ɼ���ƿѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_GAS2_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_GAS2_TIME_30S_START_NO2://��ʱ30s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO2://�ж϶�ʱ30s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO3://�ɼ���ƿѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_2GAS_GAS2_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_2GAS_GAS2_TIME_30S_START_NO3://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO3://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO4://�ɼ���ƿѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_2GAS_GAS2_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_2GAS_GAS2_TIME_30S_START_NO4://��ʱ30s��ʱ��ʼ�����Ĵ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0012_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_09_0012_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO4://�ж϶�ʱ30s�����Ĵ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0013_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0013_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO5://�ɼ���ƿѹ���������
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0014_F_1TANK_2GAS_GAS2_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_09_0014_F_1TANK_2GAS_GAS2_TIME_30S_START_NO5://��ʱ30s��ʱ��ʼ�������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0015_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_09_0015_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO5://�ж϶�ʱ30s�������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0016_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0016_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO6://�ɼ���ƿѹ����������
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0017_F_1TANK_2GAS_GAS2_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_09_0017_F_1TANK_2GAS_GAS2_TIME_30S_START_NO6://��ʱ30s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0018_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_09_0018_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO6://�ж϶�ʱ30s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0019_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0019_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO7://�ɼ���ƿѹ�������ߴ�
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0020_F_1TANK_2GAS_GAS2_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_09_0020_F_1TANK_2GAS_GAS2_TIME_30S_START_NO7://��ʱ30s��ʱ��ʼ�����ߴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0021_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_09_0021_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO7://�ж϶�ʱ30s�����ߴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0022_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0022_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO8://�ɼ���ƿѹ�����ڰ˴�
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0023_F_1TANK_2GAS_GAS2_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_09_0023_F_1TANK_2GAS_GAS2_TIME_30S_START_NO8://��ʱ30s��ʱ��ʼ���ڰ˴�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0024_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_09_0024_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO8://�ж϶�ʱ30s���ڰ˴�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0025_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0025_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO9://�ɼ���ƿѹ�����ھŴ�
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0026_F_1TANK_2GAS_GAS2_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_09_0026_F_1TANK_2GAS_GAS2_TIME_30S_START_NO9://��ʱ30s��ʱ��ʼ���ھŴ�
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0027_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_09_0027_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO9://�ж϶�ʱ30s���ھŴ�
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0028_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0028_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO10://�ɼ���ƿѹ������ʮ��
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0029_F_1TANK_2GAS_GAS2_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_09_0029_F_1TANK_2GAS_GAS2_IS_GAS_PRESSURE://ѹ���ж���ƿѹ���Ƿ�����
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS2_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS2_IS_COMP_GAS_OVER://�ж���ƿ�����Ƿ����
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_F,THIRD_TANK,SECOND_GAS)==TRUE)
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
**����: ��ȼ·��ƿ���ӷ���---�ڶ�����ƿ
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1://��ȼ·��ƿ���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb8G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1://�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb08,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2://��ȼ·��ƿ���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb10G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2://�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb10,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3://��ȼ·��ƿ���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb12G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3://�жϹ�ȼ·��ƿ���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb12,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_isolation_first(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_FIRST_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_FIRST_TIME_12S_START_NO1://��ʱ12s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO1://�ж϶�ʱ12s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_FIRST_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_FIRST_TIME_12S_START_NO2://��ʱ12s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO2://�ж϶�ʱ12s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO3://�ɼ�ѹ��������ѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_2GAS_FIRST_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_2GAS_FIRST_TIME_12S_START_NO3://��ʱ12s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO3://�ж϶�ʱ12s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO4://�ɼ�ѹ��������ѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_2GAS_FIRST_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_2GAS_FIRST_IS_ISOLATION://ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_COMPRESSOR_STOP;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF;
				
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
**����: �ر�ȼѹ�������ڷ���
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_out_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1://�ر�ȼѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb18G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1://�жϹر�ȼѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb18,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2://�ر�ȼѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb20G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2://�жϹر�ȼѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb20,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3://�ر�ȼѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb26G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3://�жϹر�ȼѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb26,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_isolation_second(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_SECOND_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_SECOND_TIME_12S_START_NO1://��ʱ12s��ʱ��ʼ����һ��
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO1://�ж϶�ʱ12s����һ��
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_SECOND_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_SECOND_TIME_12S_START_NO2://��ʱ12s��ʱ��ʼ���ڶ���
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO2://�ж϶�ʱ12s���ڶ���
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO3://�ɼ�ѹ��������ѹ����������
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_2GAS_SECOND_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_2GAS_SECOND_TIME_12S_START_NO3://��ʱ12s��ʱ��ʼ��������
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO3://�ж϶�ʱ12s��������
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO4://�ɼ�ѹ��������ѹ�������Ĵ�
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_2GAS_SECOND_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_2GAS_SECOND_IS_ISOLATION://ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����
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
**����: ȼѹ����ͣ��
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_COMPRESSOR_STOP;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_COMPRESSOR_STOP://�����豸����ָ�ѹ����ͣ��
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_B_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN://�ж�1min��ʱ
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
**����: �ж�ȼѹ����ͣ���Ƿ�����
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

uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_compressor_stop(void)
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
		
		case COMMAND_09_0001_F_1TANK_2GAS_COMPRESSOR_V_NO1://�ɼ����ת�٣���һ��
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_V_NO2://�ɼ����ת�٣��ڶ���
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_COMPRESSOR_V_NO3://�ɼ����ת�٣�������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_COMPRESSOR_V_NO4://�ɼ����ת�٣����Ĵ�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_COMPRESSOR_V_NO5://�ɼ����ת�٣������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_COMPRESSOR_V_NO6://�ɼ����ת�٣�������
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_2GAS_COMPRESSOR_V_NO7://�ɼ����ת�٣����ߴ�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_2GAS_COMPRESSOR_V_NO8://�ɼ����ת�٣��ڰ˴�
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO1://�ɼ�ѹ��������ѹ������һ��
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_2GAS_TIME_12S_START://��ʱ12s��ʱ��ʼ
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_2GAS_IS_TIME_12S://�ж϶�ʱ12s
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0012_F_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO2://�ɼ�ѹ��������ѹ�����ڶ���
		{
			//�����䣡������
			
			
			break;
		}
		
		case COMMAND_09_0013_F_1TANK_2GAS_IS_COMPRESSOR_STOP://�ж�ȼѹ����ͣ���Ƿ�����
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
**����: ��ȼѹ������·������
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_bypath_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_BYPATH_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_BYPATH_VALVE_ON://��ȼѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				TGTHT510_supply_main_lvb_set(LVb22K);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_ON;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
			{
				TGTHT510_supply_main_lvb_set(LVb87K);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_ON;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_ON://�жϿ�ȼѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb22,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_time_delay_bypath(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_TIME_BYPATH_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_TIME_BYPATH_START://��ʱ�ȴ�time_bypath��ʱ����
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_TIME_BYPATH;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_TIME_BYPATH://�ж���ʱ�ȴ�time_bypath
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
**����: ��ȼѹ������·������
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_bypath_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_BYPATH_VALVE_OFF;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_BYPATH_VALVE_OFF://��ȼѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				TGTHT510_supply_main_lvb_set(LVb22G);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_OFF://�жϹ�ȼѹ������·������
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb22,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
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
**����: �ر�ȼѹ�������ڷ��ţ��ڶ���
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_out_compressor_valve_off2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1://�ر�ȼѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb18G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1://�жϹر�ȼѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb18,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2://�ر�ȼѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb20G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2://�жϹر�ȼѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb20,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3://�ر�ȼѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb26G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3://�жϹر�ȼѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb26,VALVE_OFF)==TRUE)
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
**����: �ر�ȼѹ�������ڷ���
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_in_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1://�ر�ȼѹ�������ڷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb14G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1://�жϹر�ȼѹ�������ڷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb14,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2://�ر�ȼѹ�������ڷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb16G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2://�жϹر�ȼѹ�������ڷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb16,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3://�ر�ȼѹ�������ڷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb24G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3://�жϹر�ȼѹ�������ڷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb24,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO1://�ؽ������ѹ��·���ӷ��ţ���һ��
		{
			TGTHT510_supply_main_lvb_set(LVb2G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO1://�жϹؽ������ѹ��·���ӷ��ţ���һ��
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb02,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO2;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO2://�ؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			TGTHT510_supply_main_lvb_set(LVb4G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO2://�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb04,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO3://�ؽ������ѹ��·���ӷ��ţ�������
		{
			TGTHT510_supply_main_lvb_set(LVb6G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO3://�жϹؽ������ѹ��·���ӷ��ţ�������
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb06,VALVE_OFF)==TRUE)
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
**����: ����ȼ����״̬��
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

uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_set_state_good(void)
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
		
		case COMMAND_09_0001_F_1TANK_2GAS_SET_STATE_GOOD://����ȼ����״̬��
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE://�ж�ѹ�����¶��Ƿ�����
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_F)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_time_delay3(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_TIME_DELAY3_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_TIME_DELAY3_START://��ʱ�ȴ�time_delay3��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_TIME_DELAY3;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_TIME_DELAY3://�ж���ʱ�ȴ�time_delay3
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
**����: ����Һ��ģ���л�����
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_exchange_cooler(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO1://Һ��ģ���л�����,���Ŷ�������һ��
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO1);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO1://�ж�Һ��ģ���л�����,���Ŷ�������һ��
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO2;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO2://Һ��ģ���л�����,���Ŷ������ڶ���
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO2);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO2://�ж�Һ��ģ���л�����,���Ŷ������ڶ���
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO3://Һ��ģ���л�����,���Ŷ�����������
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO3);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO3://�ж�Һ��ģ���л�����,���Ŷ�����������
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO3)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO4;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO4://Һ��ģ���л�����,���Ŷ�����������
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO4);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO4;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO4://�ж�Һ��ģ���л�����,���Ŷ�����������
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
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
**����: ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_exchange_cooler(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_IS_EXCHANGE_COOLER;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_IS_EXCHANGE_COOLER://ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
		{
			if(TGTHT510_supply_common_is_exchange_cooler_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER_PRESSURE);//ͨ��ѹ���ж�Һ��ģ���л������쳣
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_COOLER_POWER_OFF;
			break;
		}
	
		case COMMAND_09_0001_F_1TANK_2GAS_COOLER_POWER_OFF://Һ��ģ��ͣ��
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_compressor_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_COMPRESSOR_POWER_OFF;
			break;
		}
	
		case COMMAND_09_0001_F_1TANK_2GAS_COMPRESSOR_POWER_OFF://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_B_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_TGTHT530_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_TGTHT530_POWER_OFF;
			break;
		}
	
		case COMMAND_09_0001_F_1TANK_2GAS_TGTHT530_POWER_OFF://�����豸����ָ��
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//ȼѹ����ΪB
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530b_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//ȼѹ����ΪC
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע������������
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_TGTHT530_TIME_1MIN_START://��ʱ1min��ʱ��ʼ
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_TGTHT530_IS_TIME_1MIN://�жϼ�ʱ1min�Ƿ�
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
**���ƣ����ӽ׶�5
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_command_third_isolation_valve_off(uint16 n,uint16 isolation_tank)
{
//----------------------ȼ�������----------------------------------------------
	
	if(isolation_tank==ISOLATION_TANK_F)
	{
		if(TGTHT510_supply_decode_par.number_tank_F==3)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				switch(n)
				{
					case 1:
					{
						TGTHT510_supply_main_lvt_set(LVt2G);
						break;
					}
					
					case 2:
					{
						TGTHT510_supply_main_lvt_set(LVt20G);
						break;
					}
					
					case 3:
					{
						TGTHT510_supply_main_lvt_set(LVt24G);
						break;
					}
					
					case 4:
					{
						TGTHT510_supply_main_lvt_set(LVt32G);
						break;
					}
					
					case 5:
					{
						
						break;
					}
					
					case 6:
					{
						
						break;
					}
					
					case 7:
					{
						
						break;
					}
					
					case 8:
					{
						
						break;
					}
					
					case 9:
					{
						
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
						break;
					}

				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				switch(n)
				{
					case 1:
					{
						TGTHT510_supply_main_lvt_set(LVt4G);
						break;
					}
					
					case 2:
					{
						TGTHT510_supply_main_lvt_set(LVt20G);
						break;
					}
					
					case 3:
					{
						TGTHT510_supply_main_lvt_set(LVt22G);
						break;
					}
					
					case 4:
					{
						TGTHT510_supply_main_lvt_set(LVt24G);
						break;
					}
					
					case 5:
					{
						TGTHT510_supply_main_lvt_set(LVt26G);
						break;
					}
					
					case 6:
					{
						TGTHT510_supply_main_lvt_set(LVt28G);
						break;
					}
					
					case 7:
					{
						TGTHT510_supply_main_lvt_set(LVt30G);
						break;
					}
					
					case 8:
					{
						
						break;
					}
					
					case 9:
					{
						
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
						break;
					}

				}
				
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				switch(n)
				{
					case 1:
					{
						TGTHT510_supply_main_lvt_set(LVt6G);
						break;
					}
					
					case 2:
					{
						TGTHT510_supply_main_lvt_set(LVt22G);
						break;
					}
					
					case 3:
					{
						TGTHT510_supply_main_lvt_set(LVt26G);
						break;
					}
					
					case 4:
					{
						TGTHT510_supply_main_lvt_set(LVt34G);
						break;
					}
					
					case 5:
					{
						
						break;
					}
					
					case 6:
					{
						
						break;
					}
					
					case 7:
					{
						
						break;
					}
					
					case 8:
					{
						
						break;
					}
					
					case 9:
					{
						
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
						break;
					}

				}
				
				
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע���������
			}

		}
		
		else
		{
			TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע���������
		}
	}

//----------------------���������----------------------------------------------
	
	else if(isolation_tank==ISOLATION_TANK_O)
	{
		if(TGTHT510_supply_decode_par.number_tank_O==3)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				switch(n)
				{
					case 1:
					{
						TGTHT510_supply_main_lvt_set(LVt1G);
						break;
					}
					
					case 2:
					{
						TGTHT510_supply_main_lvt_set(LVt19G);
						break;
					}
					
					case 3:
					{
						TGTHT510_supply_main_lvt_set(LVt23G);
						break;
					}
					
					case 4:
					{
						TGTHT510_supply_main_lvt_set(LVt31G);
						break;
					}
					
					case 5:
					{
						
						break;
					}
					
					case 6:
					{
						
						break;
					}
					
					case 7:
					{
						
						break;
					}
					
					case 8:
					{
						
						break;
					}
					
					case 9:
					{
						
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
						break;
					}

				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				switch(n)
				{
					case 1:
					{
						TGTHT510_supply_main_lvt_set(LVt3G);
						break;
					}
					
					case 2:
					{
						TGTHT510_supply_main_lvt_set(LVt19G);
						break;
					}
					
					case 3:
					{
						TGTHT510_supply_main_lvt_set(LVt21G);
						break;
					}
					
					case 4:
					{
						TGTHT510_supply_main_lvt_set(LVt23G);
						break;
					}
					
					case 5:
					{
						TGTHT510_supply_main_lvt_set(LVt25G);
						break;
					}
					
					case 6:
					{
						TGTHT510_supply_main_lvt_set(LVt27G);
						break;
					}
					
					case 7:
					{
						TGTHT510_supply_main_lvt_set(LVt29G);
						break;
					}
					
					case 8:
					{
						
						break;
					}
					
					case 9:
					{
						
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
						break;
					}

				}
				
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				switch(n)
				{
					case 1:
					{
						TGTHT510_supply_main_lvt_set(LVt5G);
						break;
					}
					
					case 2:
					{
						TGTHT510_supply_main_lvt_set(LVt21G);
						break;
					}
					
					case 3:
					{
						TGTHT510_supply_main_lvt_set(LVt25G);
						break;
					}
					
					case 4:
					{
						TGTHT510_supply_main_lvt_set(LVt33G);
						break;
					}
					
					case 5:
					{
						
						break;
					}
					
					case 6:
					{
						
						break;
					}
					
					case 7:
					{
						
						break;
					}
					
					case 8:
					{
						
						break;
					}
					
					case 9:
					{
						
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
						break;
					}

				}
				
				
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע���������
			}

		}
		
		else
		{
			TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע���������
		}
	
	}
	
	else
	{
		TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
	}

}


/******************************************************************************************
**���ƣ����ӽ׶�5
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_command_is_third_isolation_valve_off(uint16 n,uint16 isolation_tank)
{
	//----------------------ȼ�������----------------------------------------------
	
	if(isolation_tank==ISOLATION_TANK_F)
	{
		
		if(TGTHT510_supply_decode_par.number_tank_F==3)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				switch(n)
				{
					case 1:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt02,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						
						break;
					}
					
					case 2:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt20,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 3:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt24,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 4:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt32,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 5:
					{
						return TRUE;
						break;
					}
					
					case 6:
					{
						return TRUE;
						break;
					}
					
					case 7:
					{
						return TRUE;
						break;
					}
					
					case 8:
					{
						return TRUE;
						break;
					}
					
					case 9:
					{
						return TRUE;
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
						break;
					}

				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				switch(n)
				{
					case 1:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt04,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 2:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt20,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 3:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt22,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 4:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt24,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 5:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt26,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 6:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt28,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 7:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt30,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 8:
					{
						return TRUE;
						break;
					}
					
					case 9:
					{
						return TRUE;
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
						break;
					}

				}
				
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				switch(n)
				{
					case 1:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt06,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 2:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt22,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 3:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt26,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 4:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt34,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 5:
					{
						return TRUE;
						break;
					}
					
					case 6:
					{
						return TRUE;
						break;
					}
					
					case 7:
					{
						return TRUE;
						break;
					}
					
					case 8:
					{
						return TRUE;
						break;
					}
					
					case 9:
					{
						return TRUE;
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
						break;
					}

				}
				
				
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע���������
			}

		}
		
		else
		{
			TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע���������
		}
	
	}
//----------------------���������----------------------------------------------
	
	else if(isolation_tank==ISOLATION_TANK_O)
	{
	
		if(TGTHT510_supply_decode_par.number_tank_O==3)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				switch(n)
				{
					case 1:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt01,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 2:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt19,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 3:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt23,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 4:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt31,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 5:
					{
						return TRUE;
						break;
					}
					
					case 6:
					{
						return TRUE;
						break;
					}
					
					case 7:
					{
						return TRUE;
						break;
					}
					
					case 8:
					{
						return TRUE;
						break;
					}
					
					case 9:
					{
						return TRUE;
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
						break;
					}

				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				switch(n)
				{
					case 1:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt03,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 2:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt19,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 3:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt21,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 4:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt23,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 5:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt25,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 6:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt27,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 7:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt29,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 8:
					{
						return TRUE;
						break;
					}
					
					case 9:
					{
						return TRUE;
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
						break;
					}

				}
				
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				switch(n)
				{
					case 1:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt05,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 2:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt21,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 3:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt25,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 4:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt33,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 5:
					{
						return TRUE;
						break;
					}
					
					case 6:
					{
						return TRUE;
						break;
					}
					
					case 7:
					{
						return TRUE;
						break;
					}
					
					case 8:
					{
						return TRUE;
						break;
					}
					
					case 9:
					{
						return TRUE;
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
						break;
					}

				}
				
				
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע���������
			}

		}
		
		else
		{
			TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//����ע���������
		}
	
	}
	
	else
	{
		TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//�ڲ����������������
	}
	
	return FALSE;

}






















