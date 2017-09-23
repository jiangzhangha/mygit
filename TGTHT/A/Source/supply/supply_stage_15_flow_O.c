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
**���ƣ����ӽ׶�9��ȼ�ƽ�����������������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_supply_stage15_flow_o_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://��ʼ
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_15_O_FLOW_TANK_NUMBER;
			
			break;
		}

//--------------------------�жϲ�����������������-----------------------------------------		
		
		//�жϲ�����������������
		case STEP_15_O_FLOW_TANK_NUMBER:
		{
			TGTHT510_supply_stage15_flow_o_step_tank_number();
			break;
		}
				
//---------------------һ��ȼ���䲹������---------------------------------------
		
		//�жϻ�����ѹ״̬��
		case STEP_15_O_1TANK_IS_HYCT_GOOD:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_is_hyct_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//���������Ͻ�������
		case STEP_15_O_1TANK_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_interface_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϽ������Ͻ������ſ����Ƿ�����
		case STEP_15_O_1TANK_IS_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_is_interface_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_MIDDLE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ȼ���ӽӿ��м䷧��
		case STEP_15_O_1TANK_MIDDLE_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_middle_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_DELAY1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�
		case STEP_15_O_1TANK_DELAY1:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_PIPE_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���ж�ȼ���ӽӿڹ�·ѹ���Ƿ��ȶ�
		case STEP_15_O_1TANK_IS_PIPE_PRESSURE:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_is_pipe_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������䲹��Һ·����
		case STEP_15_O_1TANK_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_FLOW_CORRECT_V;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ�����������жϲ��ӹ����Ƿ�����
		case STEP_15_O_1TANK_IS_FLOW_CORRECT_V:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_is_flow_correct()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_FLOW_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϲ����Ƿ�λ
		case STEP_15_O_1TANK_IS_FLOW_OVER:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_is_flow_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_SET_FLOW_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//���ò��ӵ�λ��Ϣ�����ͻ���
		case STEP_15_O_1TANK_SET_FLOW_GOOD:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_set_flow_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ؽ����䲹��Һ·����
		case STEP_15_O_1TANK_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���ж����䷧�Źر��Ƿ�����
		case STEP_15_O_1TANK_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_is_valve_off_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_NEED_FLOW_THIRD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж��Ƿ���Ե����������������
		case STEP_15_O_1TANK_IS_NEED_FLOW_THIRD:
		{
			TGTHT510_supply_stage15_flow_o_step_1tank_is_need_flow_third();
			
			break;
		}
		
		//�ܱչ�·�������
		case STEP_15_O_1TANK_PIPE_DEAL:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_pipe_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
	
		
//---------------------����ȼ���䲹������---------------------------------------
		
		//�жϻ�����ѹ״̬��
		case STEP_15_O_2TANK_IS_HYCT_GOOD:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_is_hyct_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//���������Ͻ�������
		case STEP_15_O_2TANK_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_interface_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_IS_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���жϽ������Ͻ������ſ����Ƿ�����
		case STEP_15_O_2TANK_IS_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_is_interface_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_MIDDLE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ȼ���ӽӿ��м䷧��
		case STEP_15_O_2TANK_MIDDLE_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_middle_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_DELAY1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//��ʱ�ȴ�
		case STEP_15_O_2TANK_DELAY1:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_IS_PIPE_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���ж�ȼ���ӽӿڹ�·ѹ���Ƿ��ȶ�
		case STEP_15_O_2TANK_IS_PIPE_PRESSURE:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_is_pipe_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK1_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������䲹��Һ·���ţ���һ������
		case STEP_15_O_2TANK_TANK1_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank1_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK1_IS_FLOW_CORRECT_V;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ�����������жϲ��ӹ����Ƿ���������һ������
		case STEP_15_O_2TANK_TANK1_IS_FLOW_CORRECT_V:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_flow_correct()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK1_IS_FLOW_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϲ����Ƿ�λ����һ������
		case STEP_15_O_2TANK_TANK1_IS_FLOW_OVER:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_flow_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK1_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ؽ����䲹��Һ·���ţ���һ������
		case STEP_15_O_2TANK_TANK1_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank1_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK1_IS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���ж����䷧�Źر��Ƿ���������һ������
		case STEP_15_O_2TANK_TANK1_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_valve_off_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK2_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�������䲹��Һ·���ţ��ڶ�������
		case STEP_15_O_2TANK_TANK2_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank2_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK2_IS_FLOW_CORRECT_V;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ�����������жϲ��ӹ����Ƿ��������ڶ�������
		case STEP_15_O_2TANK_TANK2_IS_FLOW_CORRECT_V:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_flow_correct()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK2_IS_FLOW_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�жϲ����Ƿ�λ���ڶ�������
		case STEP_15_O_2TANK_TANK2_IS_FLOW_OVER:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_flow_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_SET_FLOW_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//���ò��ӵ�λ��Ϣ�����ͻ���
		case STEP_15_O_2TANK_SET_FLOW_GOOD:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_set_flow_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK2_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		
		//�ؽ����䲹��Һ·���ţ��ڶ�������
		case STEP_15_O_2TANK_TANK2_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank2_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK2_IS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ͨ��ѹ���ж����䷧�Źر��Ƿ��������ڶ�������
		case STEP_15_O_2TANK_TANK2_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_valve_off_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_IS_NEED_FLOW_THIRD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ж��Ƿ���Ե����������������
		case STEP_15_O_2TANK_IS_NEED_FLOW_THIRD:
		{
			TGTHT510_supply_stage15_flow_o_step_2tank_is_need_flow_third();
			
			break;
		}
		
		//�ܱչ�·�������
		case STEP_15_O_2TANK_PIPE_DEAL:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_pipe_deal()==TRUE)
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
**���ƣ��жϲ�����������������
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

void TGTHT510_supply_stage15_flow_o_step_tank_number(void)
{
	if(TGTHT510_supply_decode_par.number_tank_O==1)
	{
		TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_HYCT_GOOD;
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
	
	else if((TGTHT510_supply_decode_par.number_tank_O==2)||\
	(TGTHT510_supply_decode_par.number_tank_O==3))
	{
		TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_IS_HYCT_GOOD;
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
	
	else
	{
		TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
	}

}

/******************************************************************************************
**���ƣ��жϻ�����ѹ״̬��
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_hyct_good(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IS_HYCT_GOOD;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_IS_HYCT_GOOD:
		{
			if(TGTHT510_supply_common_is_hyct_good(FLOW_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//������ѹ״̬�쳣
				//TGTHT510_supply_main_pause(ERRNO_HYCT_PRESSURE);
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
**���ƣ����������Ͻ�������
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_interface_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_INTERFACE_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_INTERFACE_VALVE_ON:
		{
			TGTHT510_supply_common_interface_valve_on(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_INTERFACE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_common_is_interface_valve_on(FLOW_TANK_O)==TRUE)
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
**���ƣ�ͨ��ѹ���жϽ������Ͻ������ſ����Ƿ�����
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_interface_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_INTERFACE_VALVE_ON_P;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_INTERFACE_VALVE_ON_P:
		{
			if(TGTHT510_supply_common_is_interface_valve_on_pressure(FLOW_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//ͨ��ѹ���жϽ������Ͻ������ſ����쳣
				TGTHT510_supply_main_pause(ERRNO_INTERFACE_VALVE_ON_PRESSURE);
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
**���ƣ���ȼ���ӽӿ��м䷧��
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_middle_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_MIDDLE_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_MIDDLE_VALVE_ON:
		{
			TGTHT510_supply_common_middle_valve_on(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_MIDDLE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_MIDDLE_VALVE_ON:
		{
			if(TGTHT510_supply_common_is_middle_valve_on(FLOW_TANK_O)==TRUE)
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_DELAY1_START;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_DELAY1_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_DELAY1;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_DELAY1:
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
**���ƣ�ͨ��ѹ���ж�ȼ���ӽӿڹ�·ѹ���Ƿ��ȶ�
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_pipe_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_PIPE_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_PIPE_PRESSURE_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_1TANK_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_15_0003_O_1TANK_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_1TANK_PIPE_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0004_O_1TANK_PIPE_PRESSURE_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_1TANK_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0005_O_1TANK_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_1TANK_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_15_0006_O_1TANK_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_1TANK_PIPE_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_1TANK_PIPE_PRESSURE_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_1TANK_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_15_0008_O_1TANK_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0009_O_1TANK_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_15_0009_O_1TANK_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0010_O_1TANK_PIPE_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0010_O_1TANK_PIPE_PRESSURE_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0011_O_1TANK_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_15_0011_O_1TANK_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0012_O_1TANK_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_15_0012_O_1TANK_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0013_O_1TANK_PIPE_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0013_O_1TANK_PIPE_PRESSURE_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0014_O_1TANK_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_15_0014_O_1TANK_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0015_O_1TANK_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_15_0015_O_1TANK_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0016_O_1TANK_PIPE_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0016_O_1TANK_PIPE_PRESSURE_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0017_O_1TANK_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_15_0017_O_1TANK_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0018_O_1TANK_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_15_0018_O_1TANK_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0019_O_1TANK_PIPE_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0019_O_1TANK_PIPE_PRESSURE_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0020_O_1TANK_IS_PIPE_PRESSURE;
			
			break;
		}
		
		case COMMAND_15_0020_O_1TANK_IS_PIPE_PRESSURE:
		{
			if(TGTHT510_supply_common_is_pipe_pressure_stable(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//���ӽӿڹ�·ѹ�����ȶ�
				TGTHT510_supply_main_pause(ERRNO_PIPE_PRESSURE_STABLE);
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
**���ƣ��������䲹��Һ·����
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_IN_TANK_VALVE_ON:
		{
			TGTHT510_supply_common_flow_in_tank_valve_on(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_on(FLOW_TANK_O,FIRST_TANK)==TRUE)
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
**���ƣ�ͨ�����������жϲ��ӹ����Ƿ�����
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_flow_correct(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_HTT_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_HTT_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_1TANK_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_15_0003_O_1TANK_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_1TANK_HTT_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0004_O_1TANK_HTT_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_1TANK_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0005_O_1TANK_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_1TANK_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_15_0006_O_1TANK_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_1TANK_HTT_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_1TANK_HTT_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_1TANK_IS_FLOW_CORRECT;
			
			break;
		}
		
		case COMMAND_15_0008_O_1TANK_IS_FLOW_CORRECT:
		{
			if(TGTHT510_supply_common_is_flow_correct(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//�жϳ����������쳣���ݲ��������޸ģ�����������������������
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
**���ƣ��жϲ����Ƿ�λ
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_flow_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IS_FLOW_OVER_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_IS_FLOW_OVER_NO1:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_FLOW_OVER_NO2;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_FLOW_OVER_NO2:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_1TANK_IS_FLOW_OVER_NO3;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_15_0003_O_1TANK_IS_FLOW_OVER_NO3:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IS_FLOW_OVER_NO1;
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
**���ƣ��ؽ����䲹��Һ·����
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IN_TANK_VALVE_OFF;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_IN_TANK_VALVE_OFF:
		{
			TGTHT510_supply_common_flow_in_tank_valve_off(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_IN_TANK_VALVE_OFF;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_off(FLOW_TANK_O,FIRST_TANK)==TRUE)
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

/******************************************************************************************
**���ƣ�ͨ��ѹ���ж����䷧�Źر��Ƿ�����
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_valve_off_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IS_PRESSURE;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_IS_PRESSURE:
		{
			if(TGTHT510_supply_common_is_tank_valve_off_pressure(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//��������ʱͨ��ѹ���жϽ����䷧�Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_PRESSURE);
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
**���ƣ��ж��Ƿ���Ե����������������
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

void TGTHT510_supply_stage15_flow_o_step_1tank_is_need_flow_third(void)
{
	if(TGTHT510_supply_decode_par.number_tank_O==3)
	{
		TGTHT510_supply_ctrl.step=STEP_END;//�������
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
			
	else
	{
		TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_PIPE_DEAL;//�������
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
		
}

/******************************************************************************************
**���ƣ����ò��ӵ�λ��Ϣ�����ͻ���
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

//���޸ģ�����������������������

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_set_flow_good(void)
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
		
		case COMMAND_15_0001_O_1TANK_SET_FLOW_GOOD:
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


/******************************************************************************************
**���ƣ��ܱչ�·�������
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_pipe_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_VALVE_OFF_NO1:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_VALVE_OFF_NO1:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_1TANK_VALVE_ON_NO2;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0003_O_1TANK_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_1TANK_IS_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_15_0004_O_1TANK_IS_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_1TANK_5SEC_START;
			}
			
			else
			{
				//����ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_15_0005_O_1TANK_5SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_1TANK_IS_5SEC;
			
			break;
		}
		
		case COMMAND_15_0006_O_1TANK_IS_5SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_1TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_1TANK_VALVE_OFF_NO3:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_1TANK_IS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_15_0008_O_1TANK_IS_VALVE_OFF_NO3:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,6)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0009_O_1TANK_VALVE_OFF_NO4;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0009_O_1TANK_VALVE_OFF_NO4:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0010_O_1TANK_IS_VALVE_OFF_NO4;
			
			break;
		}
		
		case COMMAND_15_0010_O_1TANK_IS_VALVE_OFF_NO4:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,8)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0011_O_1TANK_VALVE_OFF_NO5;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0011_O_1TANK_VALVE_OFF_NO5:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0012_O_1TANK_IS_VALVE_OFF_NO5;
			
			break;
		}
		
		case COMMAND_15_0012_O_1TANK_IS_VALVE_OFF_NO5:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,10)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0013_O_1TANK_10SEC_START;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0013_O_1TANK_10SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0014_O_1TANK_IS_10SEC;
			
			break;
		}
		
		case COMMAND_15_0014_O_1TANK_IS_10SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_10SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0015_O_1TANK_PIPE_GET_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0015_O_1TANK_PIPE_GET_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0016_O_1TANK_PIPE_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0016_O_1TANK_PIPE_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0017_O_1TANK_PIPE_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_15_0017_O_1TANK_PIPE_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0018_O_1TANK_PIPE_GET_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0018_O_1TANK_PIPE_GET_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0019_O_1TANK_PIPE_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0019_O_1TANK_PIPE_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0020_O_1TANK_PIPE_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_15_0020_O_1TANK_PIPE_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0021_O_1TANK_PIPE_GET_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0021_O_1TANK_PIPE_GET_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0022_O_1TANK_PIPE_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_15_0022_O_1TANK_PIPE_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0023_O_1TANK_PIPE_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_15_0023_O_1TANK_PIPE_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0024_O_1TANK_PIPE_GET_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0024_O_1TANK_PIPE_GET_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0025_O_1TANK_PIPE_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_15_0025_O_1TANK_PIPE_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0026_O_1TANK_PIPE_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_15_0026_O_1TANK_PIPE_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0027_O_1TANK_PIPE_GET_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0027_O_1TANK_PIPE_GET_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0028_O_1TANK_PIPE_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_15_0028_O_1TANK_PIPE_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0029_O_1TANK_PIPE_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_15_0029_O_1TANK_PIPE_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0030_O_1TANK_PIPE_GET_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0030_O_1TANK_PIPE_GET_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0031_O_1TANK_PIPE_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_15_0031_O_1TANK_PIPE_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0032_O_1TANK_PIPE_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_15_0032_O_1TANK_PIPE_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0033_O_1TANK_PIPE_GET_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0033_O_1TANK_PIPE_GET_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0034_O_1TANK_PIPE_DEAL_PRESSURE;
			
			break;
		}
		
		case COMMAND_15_0034_O_1TANK_PIPE_DEAL_PRESSURE:
		{
			if(TGTHT510_supply_common_is_pipe_pressure_stable(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//���ӽӿڹ�·ѹ�����ȶ�
				TGTHT510_supply_main_pause(ERRNO_PIPE_PRESSURE_STABLE);
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


//************************�������䲹������************************************************

/******************************************************************************************
**���ƣ��жϻ�����ѹ״̬��
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_is_hyct_good(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_IS_HYCT_GOOD;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_IS_HYCT_GOOD:
		{
			if(TGTHT510_supply_common_is_hyct_good(FLOW_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//������ѹ״̬�쳣
				//TGTHT510_supply_main_pause(ERRNO_HYCT_PRESSURE);
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
**���ƣ����������Ͻ�������
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_interface_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_INTERFACE_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_INTERFACE_VALVE_ON:
		{
			TGTHT510_supply_common_interface_valve_on(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_IS_INTERFACE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_IS_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_common_is_interface_valve_on(FLOW_TANK_O)==TRUE)
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
**���ƣ�ͨ��ѹ���жϽ������Ͻ������ſ����Ƿ�����
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_is_interface_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_INTERFACE_VALVE_ON_P;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_INTERFACE_VALVE_ON_P:
		{
			if(TGTHT510_supply_common_is_interface_valve_on_pressure(FLOW_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//ͨ��ѹ���жϽ������Ͻ������ſ����쳣
				TGTHT510_supply_main_pause(ERRNO_INTERFACE_VALVE_ON_PRESSURE);
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
**���ƣ���ȼ���ӽӿ��м䷧��
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_middle_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_MIDDLE_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_MIDDLE_VALVE_ON:
		{
			TGTHT510_supply_common_middle_valve_on(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_IS_MIDDLE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_IS_MIDDLE_VALVE_ON:
		{
			if(TGTHT510_supply_common_is_middle_valve_on(FLOW_TANK_O)==TRUE)
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_DELAY1_START;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_DELAY1_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_IS_DELAY1;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_IS_DELAY1:
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
**���ƣ�ͨ��ѹ���ж�ȼ���ӽӿڹ�·ѹ���Ƿ��ȶ�
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_is_pipe_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_PIPE_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_PIPE_PRESSURE_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_2TANK_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_15_0003_O_2TANK_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_2TANK_PIPE_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0004_O_2TANK_PIPE_PRESSURE_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_2TANK_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0005_O_2TANK_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_2TANK_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_15_0006_O_2TANK_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_2TANK_PIPE_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_2TANK_PIPE_PRESSURE_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_2TANK_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_15_0008_O_2TANK_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0009_O_2TANK_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_15_0009_O_2TANK_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0010_O_2TANK_PIPE_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0010_O_2TANK_PIPE_PRESSURE_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0011_O_2TANK_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_15_0011_O_2TANK_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0012_O_2TANK_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_15_0012_O_2TANK_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0013_O_2TANK_PIPE_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0013_O_2TANK_PIPE_PRESSURE_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0014_O_2TANK_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_15_0014_O_2TANK_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0015_O_2TANK_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_15_0015_O_2TANK_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0016_O_2TANK_PIPE_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0016_O_2TANK_PIPE_PRESSURE_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0017_O_2TANK_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_15_0017_O_2TANK_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0018_O_2TANK_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_15_0018_O_2TANK_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0019_O_2TANK_PIPE_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0019_O_2TANK_PIPE_PRESSURE_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0020_O_2TANK_IS_PIPE_PRESSURE;
			
			break;
		}
		
		case COMMAND_15_0020_O_2TANK_IS_PIPE_PRESSURE:
		{
			if(TGTHT510_supply_common_is_pipe_pressure_stable(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//���ӽӿڹ�·ѹ�����ȶ�
				TGTHT510_supply_main_pause(ERRNO_PIPE_PRESSURE_STABLE);
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
**���ƣ��������䲹��Һ·����
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK1_IN_TANK_VALVE_ON:
		{
			TGTHT510_supply_common_flow_in_tank_valve_on(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_on(FLOW_TANK_O,FIRST_TANK)==TRUE)
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
**���ƣ�ͨ�����������жϲ��ӹ����Ƿ�����
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_flow_correct(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_HTT_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK1_HTT_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK1_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK1_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_2TANK_TANK1_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_15_0003_O_2TANK_TANK1_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_2TANK_TANK1_HTT_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0004_O_2TANK_TANK1_HTT_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_2TANK_TANK1_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0005_O_2TANK_TANK1_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_2TANK_TANK1_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_15_0006_O_2TANK_TANK1_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_2TANK_TANK1_HTT_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_2TANK_TANK1_HTT_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_2TANK_TANK1_IS_FLOW_CORRECT;
			
			break;
		}
		
		case COMMAND_15_0008_O_2TANK_TANK1_IS_FLOW_CORRECT:
		{
			if(TGTHT510_supply_common_is_flow_correct(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//�жϳ����������쳣���ݲ��������޸ģ�����������������������
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
**���ƣ��жϲ����Ƿ�λ
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_flow_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IS_FLOW_OVER_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK1_IS_FLOW_OVER_NO1:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK1_IS_FLOW_OVER_NO2;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK1_IS_FLOW_OVER_NO2:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_2TANK_TANK1_IS_FLOW_OVER_NO3;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_15_0003_O_2TANK_TANK1_IS_FLOW_OVER_NO3:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IS_FLOW_OVER_NO1;
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
**���ƣ��ؽ����䲹��Һ·����
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IN_TANK_VALVE_OFF;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK1_IN_TANK_VALVE_OFF:
		{
			TGTHT510_supply_common_flow_in_tank_valve_off(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_OFF;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_off(FLOW_TANK_O,FIRST_TANK)==TRUE)
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

/******************************************************************************************
**���ƣ�ͨ��ѹ���ж����䷧�Źر��Ƿ�����
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_valve_off_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IS_PRESSURE;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK1_IS_PRESSURE:
		{
			if(TGTHT510_supply_common_is_tank_valve_off_pressure(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//��������ʱͨ��ѹ���жϽ����䷧�Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_PRESSURE);
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
**���ƣ��������䲹��Һ·����
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK2_IN_TANK_VALVE_ON:
		{
			TGTHT510_supply_common_flow_in_tank_valve_on(FLOW_TANK_O,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_on(FLOW_TANK_O,SECOND_TANK)==TRUE)
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
**���ƣ�ͨ�����������жϲ��ӹ����Ƿ�����
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_flow_correct(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_HTT_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK2_HTT_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK2_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK2_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_2TANK_TANK2_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_15_0003_O_2TANK_TANK2_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_2TANK_TANK2_HTT_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0004_O_2TANK_TANK2_HTT_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_2TANK_TANK2_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0005_O_2TANK_TANK2_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_2TANK_TANK2_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_15_0006_O_2TANK_TANK2_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_2TANK_TANK2_HTT_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_2TANK_TANK2_HTT_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_2TANK_TANK2_IS_FLOW_CORRECT;
			
			break;
		}
		
		case COMMAND_15_0008_O_2TANK_TANK2_IS_FLOW_CORRECT:
		{
			if(TGTHT510_supply_common_is_flow_correct(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//�жϳ����������쳣���ݲ��������޸ģ�����������������������
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
**���ƣ��жϲ����Ƿ�λ
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_flow_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IS_FLOW_OVER_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK2_IS_FLOW_OVER_NO1:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,SECOND_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK2_IS_FLOW_OVER_NO2;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK2_IS_FLOW_OVER_NO2:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,SECOND_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_2TANK_TANK2_IS_FLOW_OVER_NO3;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_15_0003_O_2TANK_TANK2_IS_FLOW_OVER_NO3:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,SECOND_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IS_FLOW_OVER_NO1;
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
**���ƣ��ؽ����䲹��Һ·����
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IN_TANK_VALVE_OFF;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK2_IN_TANK_VALVE_OFF:
		{
			TGTHT510_supply_common_flow_in_tank_valve_off(FLOW_TANK_O,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_OFF;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_off(FLOW_TANK_O,SECOND_TANK)==TRUE)
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

/******************************************************************************************
**���ƣ�ͨ��ѹ���ж����䷧�Źر��Ƿ�����
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_valve_off_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IS_PRESSURE;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK2_IS_PRESSURE:
		{
			if(TGTHT510_supply_common_is_tank_valve_off_pressure(FLOW_TANK_O,SECOND_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//��������ʱͨ��ѹ���жϽ����䷧�Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_PRESSURE);
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
**���ƣ��ж��Ƿ���Ե����������������
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

void TGTHT510_supply_stage15_flow_o_step_2tank_is_need_flow_third(void)
{
	if(TGTHT510_supply_decode_par.number_tank_O==3)
	{
		TGTHT510_supply_ctrl.step=STEP_END;//�������
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
			
	else
	{
		TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_PIPE_DEAL;//�������
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}	
}

/******************************************************************************************
**���ƣ����ò��ӵ�λ��Ϣ�����ͻ���
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

//���޸ģ�����������������������

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_set_flow_good(void)
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
		
		case COMMAND_15_0001_O_2TANK_SET_FLOW_GOOD:
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

/******************************************************************************************
**���ƣ��ܱչ�·�������
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_pipe_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_VALVE_OFF_NO1:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_IS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_IS_VALVE_OFF_NO1:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_2TANK_VALVE_ON_NO2;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0003_O_2TANK_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_2TANK_IS_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_15_0004_O_2TANK_IS_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_2TANK_5SEC_START;
			}
			
			else
			{
				//����ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_15_0005_O_2TANK_5SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_2TANK_IS_5SEC;
			
			break;
		}
		
		case COMMAND_15_0006_O_2TANK_IS_5SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_2TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_2TANK_VALVE_OFF_NO3:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_2TANK_IS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_15_0008_O_2TANK_IS_VALVE_OFF_NO3:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,6)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0009_O_2TANK_VALVE_OFF_NO4;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0009_O_2TANK_VALVE_OFF_NO4:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0010_O_2TANK_IS_VALVE_OFF_NO4;
			
			break;
		}
		
		case COMMAND_15_0010_O_2TANK_IS_VALVE_OFF_NO4:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,8)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0011_O_2TANK_VALVE_OFF_NO5;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0011_O_2TANK_VALVE_OFF_NO5:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0012_O_2TANK_IS_VALVE_OFF_NO5;
			
			break;
		}
		
		case COMMAND_15_0012_O_2TANK_IS_VALVE_OFF_NO5:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,10)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0013_O_2TANK_10SEC_START;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0013_O_2TANK_10SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0014_O_2TANK_IS_10SEC;
			
			break;
		}
		
		case COMMAND_15_0014_O_2TANK_IS_10SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_10SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0015_O_2TANK_PIPE_GET_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0015_O_2TANK_PIPE_GET_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0016_O_2TANK_PIPE_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0016_O_2TANK_PIPE_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0017_O_2TANK_PIPE_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_15_0017_O_2TANK_PIPE_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0018_O_2TANK_PIPE_GET_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0018_O_2TANK_PIPE_GET_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0019_O_2TANK_PIPE_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0019_O_2TANK_PIPE_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0020_O_2TANK_PIPE_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_15_0020_O_2TANK_PIPE_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0021_O_2TANK_PIPE_GET_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0021_O_2TANK_PIPE_GET_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0022_O_2TANK_PIPE_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_15_0022_O_2TANK_PIPE_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0023_O_2TANK_PIPE_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_15_0023_O_2TANK_PIPE_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0024_O_2TANK_PIPE_GET_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0024_O_2TANK_PIPE_GET_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0025_O_2TANK_PIPE_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_15_0025_O_2TANK_PIPE_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0026_O_2TANK_PIPE_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_15_0026_O_2TANK_PIPE_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0027_O_2TANK_PIPE_GET_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0027_O_2TANK_PIPE_GET_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0028_O_2TANK_PIPE_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_15_0028_O_2TANK_PIPE_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0029_O_2TANK_PIPE_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_15_0029_O_2TANK_PIPE_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0030_O_2TANK_PIPE_GET_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0030_O_2TANK_PIPE_GET_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0031_O_2TANK_PIPE_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_15_0031_O_2TANK_PIPE_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0032_O_2TANK_PIPE_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_15_0032_O_2TANK_PIPE_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0033_O_2TANK_PIPE_GET_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0033_O_2TANK_PIPE_GET_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0034_O_2TANK_PIPE_DEAL_PRESSURE;
			
			break;
		}
		
		case COMMAND_15_0034_O_2TANK_PIPE_DEAL_PRESSURE:
		{
			if(TGTHT510_supply_common_is_pipe_pressure_stable(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//���ӽӿڹ�·ѹ�����ȶ�
				TGTHT510_supply_main_pause(ERRNO_PIPE_PRESSURE_STABLE);
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


