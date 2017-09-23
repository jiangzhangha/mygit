/**
  ******************************************************************************
  * @file    TGTHT510_faultdiagnosis.c
  * @author  ����
  * @version V1.00
  * @date    20150626
  * @brief   �ռ�վ���Ĳ��ƽ�������ң��״̬�ɼ�����֡ģ��C�ļ�
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"
#include "BM3803MG.h"

extern uint16 TGTHT510_1553B_data_TGTHT100[];				//ȫ�����飬�����ƽ�ң����·�г��¶Ȳ����������ݣ�89��
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[];		//ȫ�����飬�����ƽ�ң����·�и�֡A�¶����ݣ�65��
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[];		//ȫ�����飬�����ƽ�ң����·�и�֡B�¶����ݣ�65��
extern uint16 TGTHT510_1553B_data_TGTHT530[];			    //ȫ�����飬����ѹ�������������ң�����ݣ�12��
extern uint16 TGTHT510_1553B_data_TGTHT520a[];				//ȫ�����飬�����ƽ���������������ң�⣬7��
extern uint16 TGTHT510_1553B_data_TGTHT520b[];				//ȫ�����飬�����ƽ���������������ң�⣬7��

extern TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;
extern valvecontrol_TypeDef TGTHT510_valvecontrol_struct;//���ſ������ݽṹ��

extern compressor_state_TypeDef compressor_state;
extern TGTHT510_supply_ctrl_TypeDef TGTHT510_supply_ctrl;
extern CPU_B_receive_data_TypeDef CPU_B_receive_data;

extern struct lregs * regs;


uint16 TGTHT510_fault_data_CG_push[7];						//�ƽ��ʼ�-����ң�����
uint16 TGTHT510_fault_data_CG_supply[30];					//���ӹʼ�-����ң�����

fault_deal_TypeDef fault_deal;								//���ϴ���-ȫ�ֿ��Ʋ���

fault_deal_is_CPU_A_done_TypeDef fault_deal_is_CPU_A_done;	//A�����͵Ĺʼ�ִ��״��

uint16 mode_test;//����ʹ�ã�����ģʽ1Ϊ1111��2Ϊ2222,3Ϊ3333


//�ƽ����ֹ��ϼ��

fault_TypeDef TGTHT510_fault_push_o_gas1_leak;					//�ƽ��ʼ�--����ƿ1й©
fault_TypeDef TGTHT510_fault_push_o_gas2_leak;					//�ƽ��ʼ�--����ƿ2й©
fault_TypeDef TGTHT510_fault_push_o_gas3_leak;					//�ƽ��ʼ�--����ƿ3й©

fault_TypeDef TGTHT510_fault_push_f_gas1_leak;					//�ƽ��ʼ�--ȼ��ƿ1й©
fault_TypeDef TGTHT510_fault_push_f_gas2_leak;					//�ƽ��ʼ�--ȼ��ƿ2й©
fault_TypeDef TGTHT510_fault_push_f_gas3_leak;					//�ƽ��ʼ�--ȼ��ƿ3й©

fault_TypeDef TGTHT510_fault_push_o_tank1_overpressure;			//�ƽ��ʼ�--��1���䳬ѹ
fault_TypeDef TGTHT510_fault_push_o_tank2_overpressure;			//�ƽ��ʼ�--��2���䳬ѹ
fault_TypeDef TGTHT510_fault_push_o_tank3_overpressure;			//�ƽ��ʼ�--��3���䳬ѹ

fault_TypeDef TGTHT510_fault_push_f_tank1_overpressure;			//�ƽ��ʼ�--ȼ1���䳬ѹ
fault_TypeDef TGTHT510_fault_push_f_tank2_overpressure;			//�ƽ��ʼ�--ȼ2���䳬ѹ
fault_TypeDef TGTHT510_fault_push_f_tank3_overpressure;			//�ƽ��ʼ�--ȼ3���䳬ѹ

fault_valve_leak_TypeDef TGTHT510_fault_push_B_main_valve_leak;	//�����˿ط��������Ʒ���й©
fault_valve_leak_TypeDef TGTHT510_fault_push_B_less_valve_leak;	//�����˿ط��������Ʒ���й©
fault_valve_leak_TypeDef TGTHT510_fault_push_C_all_valve_leak;	//C���˿ط��������Ʒ���й©
fault_valve_leak_TypeDef TGTHT510_fault_push_A_main_valve_leak;	//A�������˿ط��������Ʒ���й©
fault_valve_leak_TypeDef TGTHT510_fault_push_A_less_valve_leak;	//A�鱸���˿ط��������Ʒ���й©

fault_TypeDef TGTHT510_fault_push_o_tank1_leak;					//�ƽ��ʼ�--��1����й©
fault_TypeDef TGTHT510_fault_push_o_tank2_leak;					//�ƽ��ʼ�--��2����й©
fault_TypeDef TGTHT510_fault_push_o_tank3_leak;					//�ƽ��ʼ�--��3����й©

fault_TypeDef TGTHT510_fault_push_f_tank1_leak;					//�ƽ��ʼ�--ȼ1����й©
fault_TypeDef TGTHT510_fault_push_f_tank2_leak;					//�ƽ��ʼ�--ȼ2����й©
fault_TypeDef TGTHT510_fault_push_f_tank3_leak;					//�ƽ��ʼ�--ȼ3����й©


//���Ӳ��ֹ��ϼ��

fault_TypeDef TGTHT510_fault_supply_TGTHT530;					//���ӹʼ�--�������������		

fault_TypeDef TGTHT510_fault_supply_cooler_zz;					//���ӹʼ�--����Һ�����ù���		
fault_TypeDef TGTHT510_fault_supply_cooler_zb;					//���ӹʼ�--����Һ�䱸�ù���		
fault_TypeDef TGTHT510_fault_supply_cooler_bz;					//���ӹʼ�--����Һ�����ù���		
fault_TypeDef TGTHT510_fault_supply_cooler_bb;					//���ӹʼ�--����Һ�䱸�ù���

fault_TypeDef TGTHT510_fault_supply_leak_cooler_z;				//���ӹʼ�--����Һ��й©		
fault_TypeDef TGTHT510_fault_supply_leak_cooler_b;				//���ӹʼ�--����Һ��й©		
		
fault_TypeDef TGTHT510_fault_supply_compressor_A_in_over;		//���ӹʼ�--ѹ����A��ڳ�ѹ
fault_TypeDef TGTHT510_fault_supply_compressor_B_in_over;		//���ӹʼ�--ѹ����B��ڳ�ѹ
fault_TypeDef TGTHT510_fault_supply_compressor_C_in_over;		//���ӹʼ�--ѹ����C��ڳ�ѹ

fault_TypeDef TGTHT510_fault_supply_compressor_A_motor_over;	//���ӹʼ�--ѹ����A���ǻ��ѹ
fault_TypeDef TGTHT510_fault_supply_compressor_B_motor_over;	//���ӹʼ�--ѹ����B���ǻ��ѹ
fault_TypeDef TGTHT510_fault_supply_compressor_C_motor_over;	//���ӹʼ�--ѹ����C���ǻ��ѹ

fault_TypeDef TGTHT510_fault_supply_compressor_A_hot;			//���ӹʼ�--ѹ����A����
fault_TypeDef TGTHT510_fault_supply_compressor_B_hot;			//���ӹʼ�--ѹ����B����
fault_TypeDef TGTHT510_fault_supply_compressor_C_hot;			//���ӹʼ�--ѹ����C����

fault_TypeDef TGTHT510_fault_supply_o_tank1_overpressure;		//���ӹʼ�--��1�������䳬ѹ
fault_TypeDef TGTHT510_fault_supply_o_tank2_overpressure;		//���ӹʼ�--��2�������䳬ѹ
fault_TypeDef TGTHT510_fault_supply_o_tank3_overpressure;		//���ӹʼ�--��3�������䳬ѹ

fault_TypeDef TGTHT510_fault_supply_f_tank1_overpressure;		//���ӹʼ�--ȼ1�������䳬ѹ
fault_TypeDef TGTHT510_fault_supply_f_tank2_overpressure;		//���ӹʼ�--ȼ2�������䳬ѹ
fault_TypeDef TGTHT510_fault_supply_f_tank3_overpressure;		//���ӹʼ�--ȼ3�������䳬ѹ

fault_TypeDef TGTHT510_fault_supply_compressor_A_break;			//���ӹʼ�--ѹ����AĤƬ����
fault_TypeDef TGTHT510_fault_supply_compressor_B_break;			//���ӹʼ�--ѹ����BĤƬ����
fault_TypeDef TGTHT510_fault_supply_compressor_C_break;			//���ӹʼ�--ѹ����CĤƬ����

fault_TypeDef TGTHT510_fault_supply_o_gas1_leak;				//���ӹʼ�--����ƿ1й©
fault_TypeDef TGTHT510_fault_supply_o_gas2_leak;				//���ӹʼ�--����ƿ2й©
fault_TypeDef TGTHT510_fault_supply_o_gas3_leak;				//���ӹʼ�--����ƿ3й©

fault_TypeDef TGTHT510_fault_supply_f_gas1_leak;				//���ӹʼ�--ȼ��ƿ1й©
fault_TypeDef TGTHT510_fault_supply_f_gas2_leak;				//���ӹʼ�--ȼ��ƿ2й©
fault_TypeDef TGTHT510_fault_supply_f_gas3_leak;				//���ӹʼ�--ȼ��ƿ3й©

fault_TypeDef TGTHT510_fault_supply_pipe_leak_o_tank1;			//���ӹʼ�--��1���䲹��Һ·й©
fault_TypeDef TGTHT510_fault_supply_pipe_leak_o_tank2;			//���ӹʼ�--��2���䲹��Һ·й©
fault_TypeDef TGTHT510_fault_supply_pipe_leak_o_tank3;			//���ӹʼ�--��3���䲹��Һ·й©

fault_TypeDef TGTHT510_fault_supply_pipe_leak_f_tank1;			//���ӹʼ�--ȼ1���䲹��Һ·й©
fault_TypeDef TGTHT510_fault_supply_pipe_leak_f_tank2;			//���ӹʼ�--ȼ2���䲹��Һ·й©
fault_TypeDef TGTHT510_fault_supply_pipe_leak_f_tank3;			//���ӹʼ�--ȼ3���䲹��Һ·й©

fault_TypeDef TGTHT510_fault_supply_interface_o_temperature;	//���ӹʼ�--���������¶��쳣
fault_TypeDef TGTHT510_fault_supply_interface_f_temperature;	//���ӹʼ�--ȼ�������¶��쳣

fault_TypeDef TGTHT510_fault_supply_in_leak_o_z;				//���ӹʼ�--�������ӹ�·��©
fault_TypeDef TGTHT510_fault_supply_in_leak_o_b;				//���ӹʼ�--�������ӹ�·��©
fault_TypeDef TGTHT510_fault_supply_in_leak_f_z;				//���ӹʼ�--ȼ�����ӹ�·��©
fault_TypeDef TGTHT510_fault_supply_in_leak_f_b;				//���ӹʼ�--ȼ�����ӹ�·��©

fault_TypeDef TGTHT510_fault_supply_temperature_fore_f1;		//���ӹʼ�--ǰ��ȼ1�����Ͻ����¶��쳣
fault_TypeDef TGTHT510_fault_supply_temperature_fore_f2;		//���ӹʼ�--ǰ��ȼ2�����Ͻ����¶��쳣
fault_TypeDef TGTHT510_fault_supply_temperature_fore_o1;		//���ӹʼ�--ǰ����1�����Ͻ����¶��쳣
fault_TypeDef TGTHT510_fault_supply_temperature_fore_o2;		//���ӹʼ�--ǰ����2�����Ͻ����¶��쳣

fault_TypeDef TGTHT510_fault_supply_temperature_back_f1;		//���ӹʼ�--����ȼ1�����Ͻ����¶��쳣
fault_TypeDef TGTHT510_fault_supply_temperature_back_f2;		//���ӹʼ�--����ȼ2�����Ͻ����¶��쳣
fault_TypeDef TGTHT510_fault_supply_temperature_back_o1;		//���ӹʼ�--������1�����Ͻ����¶��쳣
fault_TypeDef TGTHT510_fault_supply_temperature_back_o2;		//���ӹʼ�--������2�����Ͻ����¶��쳣

fault_TypeDef TGTHT510_fault_supply_ka_o_tank1;					//���ӹʼ�--��1���俨��
fault_TypeDef TGTHT510_fault_supply_ka_o_tank2;					//���ӹʼ�--��2���俨��
fault_TypeDef TGTHT510_fault_supply_ka_o_tank3;					//���ӹʼ�--��3���俨��

fault_TypeDef TGTHT510_fault_supply_ka_f_tank1;					//���ӹʼ�--ȼ1���俨��
fault_TypeDef TGTHT510_fault_supply_ka_f_tank2;					//���ӹʼ�--ȼ2���俨��
fault_TypeDef TGTHT510_fault_supply_ka_f_tank3;					//���ӹʼ�--ȼ3���俨��

/******************************************************************************************
**���ƣ����ϼ����Թ��Ӻ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_faultdiagnosis_test_hook(void)
{
	//����ʹ�õĹ��Ӻ���
	
	//compressor_state.compressor_A_state=COMPRESSOR_RUN;
	//compressor_state.compressor_B_state=COMPRESSOR_RUN;
	//compressor_state.compressor_C_state=COMPRESSOR_RUN;
	
	//TGTHT510_supply_decode_par.compressor_F=DECODE_COMPRESSOR_C;
	//TGTHT510_supply_decode_par.compressor_O=DECODE_COMPRESSOR_C;
}

/******************************************************************************************
**���ƣ����ϼ�⴦��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_faultdiagnosis_how_to_deal_fault_valve_leak_typedef(fault_valve_leak_TypeDef *p)
{
	if(get_CPU()==CPU_B)//B��
	{
		if(CPU_B_receive_data.is_B_get_power==FALSE)//B��δ��Ȩ
		{
			p->faultdiagnosis_count++;
			
			if(p->faultdiagnosis_count>=MAX_FAULTDIAGNOSIS_COUNT)
			{
				p->result=TRUE;//���Ϸ���
				
				p->state=DISABLE;
				
				p->step=FAULT_STEP_NONE;//�����жϹ����Ƿ���
				
				if(TGTHT510_faultdiagnosis_is_CPU_A_done_get_valve_leak(p)==FALSE)
				{
					CPU_ON();//B����Ȩ
				
					CPU_B_receive_data.is_B_get_power=TRUE;
				}
				
			}
			
			else
			{
				p->step=FAULT_STEP_END;
			}
			
		}
		
		else//B���Ѷ�Ȩ
		{
			p->result=TRUE;//���Ϸ���
		
			p->step=FAULT_STEP_NONE;//�����жϹ����Ƿ���
		}
		
	}
	
	else//A��
	{
		p->result=TRUE;//���Ϸ���
		
		p->state=DISABLE;
		
		p->step=FAULT_STEP_NONE;//�����жϹ����Ƿ���
	}
}

/******************************************************************************************
**���ƣ����ϼ�⴦��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(fault_TypeDef *p,uint16 which_field)
{
	if(get_CPU()==CPU_B)//B��
	{
		if(CPU_B_receive_data.is_B_get_power==FALSE)//B��δ��Ȩ
		{
			p->faultdiagnosis_count++;
		
			if(p->faultdiagnosis_count>=MAX_FAULTDIAGNOSIS_COUNT)
			{
				p->result=TRUE;//���Ϸ���
				
				p->state=DISABLE;
				
				if(which_field==FAULT_FIELD1)
				{
					p->fault_field1.step=FAULT_STEP_NONE;//�����жϹ����Ƿ���
				}
				
				else if(which_field==FAULT_FIELD2)
				{
					p->fault_field2.step=FAULT_STEP_NONE;//�����жϹ����Ƿ���
					
				}
				
				else if(which_field==FAULT_FIELD3)
				{
					p->fault_field3.step=FAULT_STEP_NONE;//�����жϹ����Ƿ���
				}
				
				else
				{
					asm("nop;");
				}
				
				if(TGTHT510_faultdiagnosis_is_CPU_A_done_get(p)==FALSE)
				{
					CPU_ON();//B����Ȩ
				
					CPU_B_receive_data.is_B_get_power=TRUE;
				}
			
			}
			
			else//B������������һ���ڹʼ��ж�
			{
				if(which_field==FAULT_FIELD1)
				{
					p->fault_field1.step=FAULT_STEP_END;
				}
				
				else if(which_field==FAULT_FIELD2)
				{
					p->fault_field2.step=FAULT_STEP_END;
					
				}
				
				else if(which_field==FAULT_FIELD3)
				{
					p->fault_field3.step=FAULT_STEP_END;
				}
				
				else
				{
					asm("nop;");
				}
			}
			
		}
		
		else//B���Ѷ�Ȩ
		{
			p->result=TRUE;//���Ϸ���
			
			p->state=DISABLE;
		
			if(which_field==FAULT_FIELD1)
			{
				p->fault_field1.step=FAULT_STEP_NONE;//�����жϹ����Ƿ���
			}
			
			else if(which_field==FAULT_FIELD2)
			{
				
				p->fault_field2.step=FAULT_STEP_NONE;//�����жϹ����Ƿ���
			}
			
			else if(which_field==FAULT_FIELD3)
			{
				p->fault_field3.step=FAULT_STEP_NONE;//�����жϹ����Ƿ���
			}
			
			else
			{
				asm("nop;");
			}
		}
	
	}
	
	else//A��
	{
		p->result=TRUE;//���Ϸ���
		
		p->state=DISABLE;
		
		if(which_field==FAULT_FIELD1)
		{
			p->fault_field1.step=FAULT_STEP_NONE;//�����жϹ����Ƿ���
		}
		
		else if(which_field==FAULT_FIELD2)
		{
			
			p->fault_field2.step=FAULT_STEP_NONE;//�����жϹ����Ƿ���
		}
		
		else if(which_field==FAULT_FIELD3)
		{
			p->fault_field3.step=FAULT_STEP_NONE;//�����жϹ����Ƿ���
		}
		
		else
		{
			asm("nop;");
		}
		
	}

}

/******************************************************************************************
**���ƣ�A�����͵Ĺʼ�״̬��ѯ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_is_CPU_A_done_get_valve_leak(fault_valve_leak_TypeDef *p)
{
	switch(p->mode)
	{
		case FAULT_MODE_PUSH_LEAK_B_MAIN://�ƽ����ϣ������˿ط��������Ʒ���й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_B_main_valve_leak_is_done;
		}
		
		case FAULT_MODE_PUSH_LEAK_B_LESS://�ƽ����ϣ������˿ط��������Ʒ���й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_B_less_valve_leak_is_done;
			
		}
		
		case FAULT_MODE_PUSH_LEAK_C_ALL://�ƽ����ϣ�C���˿ط��������Ʒ���й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_C_all_valve_leak_is_done;
			
		}
		
		case FAULT_MODE_PUSH_LEAK_A_MAIN://�ƽ����ϣ�A�������˿ط��������Ʒ���й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_A_main_valve_leak_is_done;
			
		}
			
		case FAULT_MODE_PUSH_LEAK_A_LESS://�ƽ����ϣ�A�鱸���˿ط��������Ʒ���й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_A_less_valve_leak_is_done;
			
		}
		
		default:
		{
			return FALSE;
		}
		
	}
}



/******************************************************************************************
**���ƣ�A�����͵Ĺʼ�״̬��ѯ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_is_CPU_A_done_get(fault_TypeDef *p)
{
	switch(p->mode)
	{
		case FAULT_MODE_PUSH_LEAK_O_GAS1://�ƽ����ϣ���1��ƿй©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas1_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_GAS2://�ƽ����ϣ���2��ƿй©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas2_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_GAS3://�ƽ����ϣ���3��ƿй©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas3_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS1://�ƽ����ϣ�ȼ1��ƿй©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas1_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS2://�ƽ����ϣ�ȼ2��ƿй©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas2_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS3://�ƽ����ϣ�ȼ3��ƿй©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas3_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK1://�ƽ����ϣ���1���䳬ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank1_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK2://�ƽ����ϣ���2���䳬ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank2_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK3://�ƽ����ϣ���3���䳬ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank3_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK1://�ƽ����ϣ�ȼ1���䳬ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank1_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK2://�ƽ����ϣ�ȼ2���䳬ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank2_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK3://�ƽ����ϣ�ȼ3���䳬ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank3_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK1://�ƽ����ϣ���1����й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank1_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK2://�ƽ����ϣ���2����й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank2_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK3://�ƽ����ϣ���3����й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank3_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK1://�ƽ����ϣ�ȼ1����й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank1_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK2://�ƽ����ϣ�ȼ2����й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank2_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK3://�ƽ����ϣ�ȼ3����й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank3_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_ZZ://���ӹ��ϣ�����Һ�����ù���
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_zz_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_ZB://���ӹ��ϣ�����Һ�䱸�ù���
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_zb_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_BZ://���ӹ��ϣ�����Һ�����ù���
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_bz_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_BB://���ӹ��ϣ�����Һ�䱸�ù���
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_bb_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_COOLER_Z://���ӹ��ϣ�����Һ��й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_leak_cooler_z_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_COOLER_B://���ӹ��ϣ�����Һ��й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_leak_cooler_b_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_A_IN://���ӹ��ϣ�ѹ����A��ڳ�ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_in_over_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_B_IN://���ӹ��ϣ�ѹ����B��ڳ�ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_in_over_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_C_IN://���ӹ��ϣ�ѹ����C��ڳ�ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_in_over_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR://���ӹ��ϣ�ѹ����A���ǻ��ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_motor_over_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR://���ӹ��ϣ�ѹ����B���ǻ��ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_motor_over_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR://���ӹ��ϣ�ѹ����C���ǻ��ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_motor_over_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_A_HOT://���ӹ��ϣ�ѹ����A����
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_hot_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_B_HOT://���ӹ��ϣ�ѹ����B����
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_hot_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_C_HOT://���ӹ��ϣ�ѹ����C����
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_hot_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK1://���ӹ��ϣ���1�������䳬ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank1_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK2://���ӹ��ϣ���2�������䳬ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank2_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK3://���ӹ��ϣ���3�������䳬ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank3_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK1://���ӹ��ϣ�ȼ1�������䳬ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank1_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK2://���ӹ��ϣ�ȼ2�������䳬ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank2_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK3://���ӹ��ϣ�ȼ3�������䳬ѹ
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank3_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_A_BREAK://���ӹ��ϣ�ѹ����AĤƬ����
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_break_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_B_BREAK://���ӹ��ϣ�ѹ����BĤƬ����
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_break_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_C_BREAK://���ӹ��ϣ�ѹ����CĤƬ����
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_break_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS1://���ӹ��ϣ���1��ƿй©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas1_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS2://���ӹ��ϣ���2��ƿй©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas2_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS3://���ӹ��ϣ���3��ƿй©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas3_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS1://���ӹ��ϣ�ȼ1��ƿй©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas1_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS2://���ӹ��ϣ�ȼ2��ƿй©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas2_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS3://���ӹ��ϣ�ȼ3��ƿй©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas3_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1://���ӹ��ϣ���1���䲹��Һ·й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2://���ӹ��ϣ���2���䲹��Һ·й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3://���ӹ��ϣ���3���䲹��Һ·й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank3_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1://���ӹ��ϣ�ȼ1���䲹��Һ·й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2://���ӹ��ϣ�ȼ2���䲹��Һ·й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3://���ӹ��ϣ�ȼ3���䲹��Һ·й©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank3_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_INTERFACE_O_TEMP://���ӹ��ϣ����������¶��쳣
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_interface_o_temperature_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_INTERFACE_F_TEMP://���ӹ��ϣ�ȼ�������¶��쳣
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_interface_f_temperature_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_O_Z://���ӹ��ϣ��������ӹ�·��©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_o_z_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_O_B://���ӹ��ϣ��������ӹ�·��©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_o_b_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_F_Z://���ӹ��ϣ�ȼ�����ӹ�·��©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_f_z_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_F_B://���ӹ��ϣ�ȼ�����ӹ�·��©
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_f_b_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1://���ӹ��ϣ�ǰ��ȼ1�����Ͻ����¶��쳣
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_f1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2://���ӹ��ϣ�ǰ��ȼ2�����Ͻ����¶��쳣
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_f2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1://���ӹ��ϣ�ǰ����1�����Ͻ����¶��쳣
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_o1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2://���ӹ��ϣ�ǰ����2�����Ͻ����¶��쳣
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_o2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1://���ӹ��ϣ�����ȼ1�����Ͻ����¶��쳣
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_f1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2://���ӹ��ϣ�����ȼ2�����Ͻ����¶��쳣
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_f2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1://���ӹ��ϣ�������1�����Ͻ����¶��쳣
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_o1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2://���ӹ��ϣ�������2�����Ͻ����¶��쳣
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_o2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK1://���ӹ��ϣ���1���俨��
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK2://���ӹ��ϣ���2���俨��
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK3://���ӹ��ϣ���3���俨��
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank3_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK1://���ӹ��ϣ�ȼ1���俨��
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK2://���ӹ��ϣ�ȼ1���俨��
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK3://���ӹ��ϣ�ȼ1���俨��
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank3_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TGTHT530://���ӹ��ϣ��������������
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_TGTHT530_is_done;
			break;
		}
		
		default:
		{
			return FALSE;
		}
		
	}

}



/******************************************************************************************
**���ƣ�A�����͵Ĺʼ�״̬����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_is_CPU_A_done_set(void)
{
	if((fault_deal_is_CPU_A_done.fault_mode_last==FAULT_MODE_NONE)&&\
	(fault_deal_is_CPU_A_done.fault_mode_moment!=FAULT_MODE_NONE))
	{
		switch(fault_deal_is_CPU_A_done.fault_mode_moment)
		{
			case FAULT_MODE_PUSH_LEAK_O_GAS1://�ƽ����ϣ���1��ƿй©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas1_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_GAS2://�ƽ����ϣ���2��ƿй©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas2_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_GAS3://�ƽ����ϣ���3��ƿй©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas3_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_GAS1://�ƽ����ϣ�ȼ1��ƿй©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas1_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_GAS2://�ƽ����ϣ�ȼ2��ƿй©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas2_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_GAS3://�ƽ����ϣ�ȼ3��ƿй©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas3_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_O_TANK1://�ƽ����ϣ���1���䳬ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank1_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_O_TANK2://�ƽ����ϣ���2���䳬ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank2_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_O_TANK3://�ƽ����ϣ���3���䳬ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank3_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_F_TANK1://�ƽ����ϣ�ȼ1���䳬ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank1_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_F_TANK2://�ƽ����ϣ�ȼ2���䳬ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank2_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_F_TANK3://�ƽ����ϣ�ȼ3���䳬ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank3_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_B_MAIN://�ƽ����ϣ������˿ط��������Ʒ���й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_B_main_valve_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_B_LESS://�ƽ����ϣ������˿ط��������Ʒ���й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_B_less_valve_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_C_ALL://�ƽ����ϣ�C���˿ط��������Ʒ���й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_C_all_valve_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_A_MAIN://�ƽ����ϣ�A�������˿ط��������Ʒ���й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_A_main_valve_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_A_LESS://�ƽ����ϣ�A�鱸���˿ط��������Ʒ���й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_A_less_valve_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_TANK1://�ƽ����ϣ���1����й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank1_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_TANK2://�ƽ����ϣ���2����й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank2_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_TANK3://�ƽ����ϣ���3����й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank3_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_TANK1://�ƽ����ϣ�ȼ1����й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank1_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_TANK2://�ƽ����ϣ�ȼ2����й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank2_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_TANK3://�ƽ����ϣ�ȼ3����й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank3_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_ZZ://���ӹ��ϣ�����Һ�����ù���
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_zz_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_ZB://���ӹ��ϣ�����Һ�䱸�ù���
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_zb_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_BZ://���ӹ��ϣ�����Һ�����ù���
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_bz_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_BB://���ӹ��ϣ�����Һ�䱸�ù���
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_bb_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_COOLER_Z://���ӹ��ϣ�����Һ��й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_leak_cooler_z_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_COOLER_B://���ӹ��ϣ�����Һ��й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_leak_cooler_b_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_A_IN://���ӹ��ϣ�ѹ����A��ڳ�ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_in_over_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_B_IN://���ӹ��ϣ�ѹ����B��ڳ�ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_in_over_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_C_IN://���ӹ��ϣ�ѹ����C��ڳ�ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_in_over_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR://���ӹ��ϣ�ѹ����A���ǻ��ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_motor_over_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR://���ӹ��ϣ�ѹ����B���ǻ��ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_motor_over_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR://���ӹ��ϣ�ѹ����C���ǻ��ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_motor_over_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_A_HOT://���ӹ��ϣ�ѹ����A����
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_hot_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_B_HOT://���ӹ��ϣ�ѹ����B����
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_hot_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_C_HOT://���ӹ��ϣ�ѹ����C����
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_hot_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_O_TANK1://���ӹ��ϣ���1�������䳬ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank1_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_O_TANK2://���ӹ��ϣ���2�������䳬ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank2_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_O_TANK3://���ӹ��ϣ���3�������䳬ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank3_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_F_TANK1://���ӹ��ϣ�ȼ1�������䳬ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank1_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_F_TANK2://���ӹ��ϣ�ȼ2�������䳬ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank2_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_F_TANK3://���ӹ��ϣ�ȼ3�������䳬ѹ
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank3_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_A_BREAK://���ӹ��ϣ�ѹ����AĤƬ����
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_break_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_B_BREAK://���ӹ��ϣ�ѹ����BĤƬ����
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_break_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_C_BREAK://���ӹ��ϣ�ѹ����CĤƬ����
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_break_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_O_GAS1://���ӹ��ϣ���1��ƿй©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas1_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_O_GAS2://���ӹ��ϣ���2��ƿй©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas2_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_O_GAS3://���ӹ��ϣ���3��ƿй©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas3_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_F_GAS1://���ӹ��ϣ�ȼ1��ƿй©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas1_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_F_GAS2://���ӹ��ϣ�ȼ2��ƿй©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas2_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_F_GAS3://���ӹ��ϣ�ȼ3��ƿй©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas3_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1://���ӹ��ϣ���1���䲹��Һ·й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2://���ӹ��ϣ���2���䲹��Һ·й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3://���ӹ��ϣ���3���䲹��Һ·й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank3_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1://���ӹ��ϣ�ȼ1���䲹��Һ·й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2://���ӹ��ϣ�ȼ2���䲹��Һ·й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3://���ӹ��ϣ�ȼ3���䲹��Һ·й©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank3_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_INTERFACE_O_TEMP://���ӹ��ϣ����������¶��쳣
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_interface_o_temperature_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_INTERFACE_F_TEMP://���ӹ��ϣ�ȼ�������¶��쳣
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_interface_f_temperature_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_O_Z://���ӹ��ϣ��������ӹ�·��©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_o_z_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_O_B://���ӹ��ϣ��������ӹ�·��©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_o_b_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_F_Z://���ӹ��ϣ�ȼ�����ӹ�·��©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_f_z_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_F_B://���ӹ��ϣ�ȼ�����ӹ�·��©
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_f_b_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1://���ӹ��ϣ�ǰ��ȼ1�����Ͻ����¶��쳣
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_f1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2://���ӹ��ϣ�ǰ��ȼ2�����Ͻ����¶��쳣
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_f2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1://���ӹ��ϣ�ǰ����1�����Ͻ����¶��쳣
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_o1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2://���ӹ��ϣ�ǰ����2�����Ͻ����¶��쳣
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_o2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1://���ӹ��ϣ�����ȼ1�����Ͻ����¶��쳣
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_f1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2://���ӹ��ϣ�����ȼ2�����Ͻ����¶��쳣
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_f2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1://���ӹ��ϣ�������1�����Ͻ����¶��쳣
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_o1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2://���ӹ��ϣ�������2�����Ͻ����¶��쳣
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_o2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_O_TANK1://���ӹ��ϣ���1���俨��
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_O_TANK2://���ӹ��ϣ���2���俨��
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_O_TANK3://���ӹ��ϣ���3���俨��
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank3_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_F_TANK1://���ӹ��ϣ�ȼ1���俨��
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_F_TANK2://���ӹ��ϣ�ȼ1���俨��
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_F_TANK3://���ӹ��ϣ�ȼ1���俨��
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank3_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TGTHT530://���ӹ��ϣ��������������
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_TGTHT530_is_done=TRUE;
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
}






/******************************************************************************************
**���ƣ����ϼ��ģ���ʼ������--A�����͵Ĺʼ�״̬��ʼ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_is_CPU_A_done_initial(void)
{
	fault_deal_is_CPU_A_done.fault_mode_last=FAULT_MODE_NONE;
	fault_deal_is_CPU_A_done.fault_mode_moment=FAULT_MODE_NONE;
	
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas1_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas2_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas3_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas1_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas2_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas3_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank1_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank2_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank3_overpressure_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank1_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank2_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank3_overpressure_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_B_main_valve_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_B_less_valve_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_C_all_valve_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_A_main_valve_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_A_less_valve_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank1_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank2_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank3_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank1_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank2_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank3_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_TGTHT530_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_zz_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_zb_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_bz_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_bb_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_leak_cooler_z_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_leak_cooler_b_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_in_over_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_in_over_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_in_over_is_done=FALSE;
		
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_motor_over_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_motor_over_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_motor_over_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_hot_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_hot_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_hot_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank1_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank2_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank3_overpressure_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank1_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank2_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank3_overpressure_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_break_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_break_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_break_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas1_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas2_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas3_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas1_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas2_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas3_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank2_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank3_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank2_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank3_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_interface_o_temperature_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_interface_f_temperature_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_o_z_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_o_b_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_f_z_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_f_b_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_f1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_f2_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_o1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_o2_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_f1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_f2_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_o1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_o2_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank2_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank3_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank2_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank3_is_done=FALSE;

}



/******************************************************************************************
**���ƣ����ϼ��ģ���ʼ������--�ƽ�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_faultdiagnosis_supply_struct_mode_add(void)
{
	TGTHT510_fault_supply_TGTHT530.mode=FAULT_MODE_SUPPLY_TGTHT530;//���ӹ��ϣ��������������
	
	TGTHT510_fault_supply_cooler_zz.mode=FAULT_MODE_SUPPLY_COOLER_ZZ;//���ӹ��ϣ�����Һ�����ù���
	TGTHT510_fault_supply_cooler_zb.mode=FAULT_MODE_SUPPLY_COOLER_ZB;//���ӹ��ϣ�����Һ�䱸�ù���
	TGTHT510_fault_supply_cooler_bz.mode=FAULT_MODE_SUPPLY_COOLER_BZ;//���ӹ��ϣ�����Һ�����ù���
	TGTHT510_fault_supply_cooler_bb.mode=FAULT_MODE_SUPPLY_COOLER_BB;//���ӹ��ϣ�����Һ�䱸�ù���
	
	TGTHT510_fault_supply_leak_cooler_z.mode=FAULT_MODE_SUPPLY_LEAK_COOLER_Z;//���ӹ��ϣ�����Һ��й©
	TGTHT510_fault_supply_leak_cooler_b.mode=FAULT_MODE_SUPPLY_LEAK_COOLER_B;//���ӹ��ϣ�����Һ��й©
	
	TGTHT510_fault_supply_compressor_A_in_over.mode=FAULT_MODE_SUPPLY_OVER_COMP_A_IN;//���ӹ��ϣ�ѹ����A��ڳ�ѹ
	TGTHT510_fault_supply_compressor_B_in_over.mode=FAULT_MODE_SUPPLY_OVER_COMP_B_IN;//���ӹ��ϣ�ѹ����B��ڳ�ѹ
	TGTHT510_fault_supply_compressor_C_in_over.mode=FAULT_MODE_SUPPLY_OVER_COMP_C_IN;//���ӹ��ϣ�ѹ����C��ڳ�ѹ
	
	TGTHT510_fault_supply_compressor_A_motor_over.mode=FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR;//���ӹ��ϣ�ѹ����A���ǻ��ѹ
	TGTHT510_fault_supply_compressor_B_motor_over.mode=FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR;//���ӹ��ϣ�ѹ����B���ǻ��ѹ
	TGTHT510_fault_supply_compressor_C_motor_over.mode=FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR;//���ӹ��ϣ�ѹ����C���ǻ��ѹ
	
	TGTHT510_fault_supply_compressor_A_hot.mode=FAULT_MODE_SUPPLY_COMP_A_HOT;//���ӹ��ϣ�ѹ����A����
	TGTHT510_fault_supply_compressor_B_hot.mode=FAULT_MODE_SUPPLY_COMP_B_HOT;//���ӹ��ϣ�ѹ����B����
	TGTHT510_fault_supply_compressor_C_hot.mode=FAULT_MODE_SUPPLY_COMP_C_HOT;//���ӹ��ϣ�ѹ����C����
	
	TGTHT510_fault_supply_o_tank1_overpressure.mode=FAULT_MODE_SUPPLY_OVER_O_TANK1;//���ӹ��ϣ���1�������䳬ѹ
	TGTHT510_fault_supply_o_tank2_overpressure.mode=FAULT_MODE_SUPPLY_OVER_O_TANK2;//���ӹ��ϣ���2�������䳬ѹ
	TGTHT510_fault_supply_o_tank3_overpressure.mode=FAULT_MODE_SUPPLY_OVER_O_TANK3;//���ӹ��ϣ���3�������䳬ѹ
	
	TGTHT510_fault_supply_f_tank1_overpressure.mode=FAULT_MODE_SUPPLY_OVER_F_TANK1;//���ӹ��ϣ�ȼ1�������䳬ѹ
	TGTHT510_fault_supply_f_tank2_overpressure.mode=FAULT_MODE_SUPPLY_OVER_F_TANK2;//���ӹ��ϣ�ȼ2�������䳬ѹ
	TGTHT510_fault_supply_f_tank3_overpressure.mode=FAULT_MODE_SUPPLY_OVER_F_TANK3;//���ӹ��ϣ�ȼ3�������䳬ѹ
	
	TGTHT510_fault_supply_compressor_A_break.mode=FAULT_MODE_SUPPLY_COMP_A_BREAK;//���ӹ��ϣ�ѹ����AĤƬ����
	TGTHT510_fault_supply_compressor_B_break.mode=FAULT_MODE_SUPPLY_COMP_B_BREAK;//���ӹ��ϣ�ѹ����BĤƬ����
	TGTHT510_fault_supply_compressor_C_break.mode=FAULT_MODE_SUPPLY_COMP_C_BREAK;//���ӹ��ϣ�ѹ����CĤƬ����
	
	TGTHT510_fault_supply_o_gas1_leak.mode=FAULT_MODE_SUPPLY_LEAK_O_GAS1;//���ӹ��ϣ���1��ƿй©
	TGTHT510_fault_supply_o_gas2_leak.mode=FAULT_MODE_SUPPLY_LEAK_O_GAS2;//���ӹ��ϣ���2��ƿй©
	TGTHT510_fault_supply_o_gas3_leak.mode=FAULT_MODE_SUPPLY_LEAK_O_GAS3;//���ӹ��ϣ���3��ƿй©
	
	TGTHT510_fault_supply_f_gas1_leak.mode=FAULT_MODE_SUPPLY_LEAK_F_GAS1;//���ӹ��ϣ�ȼ1��ƿй©
	TGTHT510_fault_supply_f_gas2_leak.mode=FAULT_MODE_SUPPLY_LEAK_F_GAS2;//���ӹ��ϣ�ȼ2��ƿй©
	TGTHT510_fault_supply_f_gas3_leak.mode=FAULT_MODE_SUPPLY_LEAK_F_GAS3;//���ӹ��ϣ�ȼ3��ƿй©
	
	TGTHT510_fault_supply_pipe_leak_o_tank1.mode=FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1;//���ӹ��ϣ���1���䲹��Һ·й©
	TGTHT510_fault_supply_pipe_leak_o_tank2.mode=FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2;//���ӹ��ϣ���2���䲹��Һ·й©
	TGTHT510_fault_supply_pipe_leak_o_tank3.mode=FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3;//���ӹ��ϣ���3���䲹��Һ·й©
	
	TGTHT510_fault_supply_pipe_leak_f_tank1.mode=FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1;//���ӹ��ϣ�ȼ1���䲹��Һ·й©
	TGTHT510_fault_supply_pipe_leak_f_tank2.mode=FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2;//���ӹ��ϣ�ȼ2���䲹��Һ·й©
	TGTHT510_fault_supply_pipe_leak_f_tank3.mode=FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3;//���ӹ��ϣ�ȼ3���䲹��Һ·й©
	
	TGTHT510_fault_supply_interface_o_temperature.mode=FAULT_MODE_SUPPLY_INTERFACE_O_TEMP;//���ӹ��ϣ����������¶��쳣
	TGTHT510_fault_supply_interface_f_temperature.mode=FAULT_MODE_SUPPLY_INTERFACE_F_TEMP;//���ӹ��ϣ�ȼ�������¶��쳣
	
	TGTHT510_fault_supply_in_leak_o_z.mode=FAULT_MODE_SUPPLY_IN_LEAK_O_Z;//���ӹ��ϣ��������ӹ�·��©
	TGTHT510_fault_supply_in_leak_o_b.mode=FAULT_MODE_SUPPLY_IN_LEAK_O_B;//���ӹ��ϣ��������ӹ�·��©
	TGTHT510_fault_supply_in_leak_f_z.mode=FAULT_MODE_SUPPLY_IN_LEAK_F_Z;//���ӹ��ϣ�ȼ�����ӹ�·��©
	TGTHT510_fault_supply_in_leak_f_b.mode=FAULT_MODE_SUPPLY_IN_LEAK_F_B;//���ӹ��ϣ�ȼ�����ӹ�·��©
	
	TGTHT510_fault_supply_temperature_fore_f1.mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1;//���ӹ��ϣ�ǰ��ȼ1�����Ͻ����¶��쳣
	TGTHT510_fault_supply_temperature_fore_f2.mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2;//���ӹ��ϣ�ǰ��ȼ2�����Ͻ����¶��쳣
	TGTHT510_fault_supply_temperature_fore_o1.mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1;//���ӹ��ϣ�ǰ����1�����Ͻ����¶��쳣
	TGTHT510_fault_supply_temperature_fore_o2.mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2;//���ӹ��ϣ�ǰ����2�����Ͻ����¶��쳣
	
	TGTHT510_fault_supply_temperature_back_f1.mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1;//���ӹ��ϣ�����ȼ1�����Ͻ����¶��쳣
	TGTHT510_fault_supply_temperature_back_f2.mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2;//���ӹ��ϣ�����ȼ2�����Ͻ����¶��쳣
	TGTHT510_fault_supply_temperature_back_o1.mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1;//���ӹ��ϣ�������1�����Ͻ����¶��쳣
	TGTHT510_fault_supply_temperature_back_o2.mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2;//���ӹ��ϣ�������2�����Ͻ����¶��쳣
	
	TGTHT510_fault_supply_ka_o_tank1.mode=FAULT_MODE_SUPPLY_KA_O_TANK1;//���ӹ��ϣ���1���俨��
	TGTHT510_fault_supply_ka_o_tank2.mode=FAULT_MODE_SUPPLY_KA_O_TANK2;//���ӹ��ϣ���2���俨��
	TGTHT510_fault_supply_ka_o_tank3.mode=FAULT_MODE_SUPPLY_KA_O_TANK3;//���ӹ��ϣ���3���俨��
	
	TGTHT510_fault_supply_ka_f_tank1.mode=FAULT_MODE_SUPPLY_KA_F_TANK1;//���ӹ��ϣ�ȼ1���俨��
	TGTHT510_fault_supply_ka_f_tank2.mode=FAULT_MODE_SUPPLY_KA_F_TANK2;//���ӹ��ϣ�ȼ2���俨��
	TGTHT510_fault_supply_ka_f_tank3.mode=FAULT_MODE_SUPPLY_KA_F_TANK3;//���ӹ��ϣ�ȼ3���俨��
	
	
}

/******************************************************************************************
**���ƣ����ϼ��ģ���ʼ������--�ƽ�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_faultdiagnosis_push_struct_mode_add(void)
{
	TGTHT510_fault_push_o_gas1_leak.mode=FAULT_MODE_PUSH_LEAK_O_GAS1;//�ƽ����ϣ���1��ƿй©
	TGTHT510_fault_push_o_gas2_leak.mode=FAULT_MODE_PUSH_LEAK_O_GAS2;//�ƽ����ϣ���2��ƿй©
	TGTHT510_fault_push_o_gas3_leak.mode=FAULT_MODE_PUSH_LEAK_O_GAS3;//�ƽ����ϣ���3��ƿй©
	
	TGTHT510_fault_push_f_gas1_leak.mode=FAULT_MODE_PUSH_LEAK_F_GAS1;//�ƽ����ϣ�ȼ1��ƿй©
	TGTHT510_fault_push_f_gas2_leak.mode=FAULT_MODE_PUSH_LEAK_F_GAS2;//�ƽ����ϣ�ȼ2��ƿй©
	TGTHT510_fault_push_f_gas3_leak.mode=FAULT_MODE_PUSH_LEAK_F_GAS3;//�ƽ����ϣ�ȼ3��ƿй©
	
	TGTHT510_fault_push_o_tank1_overpressure.mode=FAULT_MODE_PUSH_OVER_O_TANK1;//�ƽ����ϣ���1���䳬ѹ
	TGTHT510_fault_push_o_tank2_overpressure.mode=FAULT_MODE_PUSH_OVER_O_TANK2;//�ƽ����ϣ���2���䳬ѹ
	TGTHT510_fault_push_o_tank3_overpressure.mode=FAULT_MODE_PUSH_OVER_O_TANK3;//�ƽ����ϣ���3���䳬ѹ
	
	TGTHT510_fault_push_f_tank1_overpressure.mode=FAULT_MODE_PUSH_OVER_F_TANK1;//�ƽ����ϣ�ȼ1���䳬ѹ
	TGTHT510_fault_push_f_tank2_overpressure.mode=FAULT_MODE_PUSH_OVER_F_TANK2;//�ƽ����ϣ�ȼ2���䳬ѹ
	TGTHT510_fault_push_f_tank3_overpressure.mode=FAULT_MODE_PUSH_OVER_F_TANK3;//�ƽ����ϣ�ȼ3���䳬ѹ
	
	TGTHT510_fault_push_B_main_valve_leak.mode=FAULT_MODE_PUSH_LEAK_B_MAIN;//�ƽ����ϣ������˿ط��������Ʒ���й©
	TGTHT510_fault_push_B_less_valve_leak.mode=FAULT_MODE_PUSH_LEAK_B_LESS;//�ƽ����ϣ������˿ط��������Ʒ���й©
	TGTHT510_fault_push_C_all_valve_leak.mode=FAULT_MODE_PUSH_LEAK_C_ALL;//�ƽ����ϣ�C���˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_main_valve_leak.mode=FAULT_MODE_PUSH_LEAK_A_MAIN;//�ƽ����ϣ�A�������˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_less_valve_leak.mode=FAULT_MODE_PUSH_LEAK_A_LESS;//�ƽ����ϣ�A�鱸���˿ط��������Ʒ���й©
	
	TGTHT510_fault_push_o_tank1_leak.mode=FAULT_MODE_PUSH_LEAK_O_TANK1;//�ƽ����ϣ���1����й©
	TGTHT510_fault_push_o_tank2_leak.mode=FAULT_MODE_PUSH_LEAK_O_TANK2;//�ƽ����ϣ���2����й©
	TGTHT510_fault_push_o_tank3_leak.mode=FAULT_MODE_PUSH_LEAK_O_TANK3;//�ƽ����ϣ���3����й©
	
	TGTHT510_fault_push_f_tank1_leak.mode=FAULT_MODE_PUSH_LEAK_F_TANK1;//�ƽ����ϣ�ȼ1����й©
	TGTHT510_fault_push_f_tank2_leak.mode=FAULT_MODE_PUSH_LEAK_F_TANK2;//�ƽ����ϣ�ȼ2����й©
	TGTHT510_fault_push_f_tank3_leak.mode=FAULT_MODE_PUSH_LEAK_F_TANK3;//�ƽ����ϣ�ȼ3����й©
	
}


/******************************************************************************************
**���ƣ����ϼ��ģ���ʼ������--�ƽ�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_initial(fault_TypeDef *p,uint16 enable_state)
{
	if(enable_state==ENABLE)
	{
		p->state=ENABLE;						//�ʼ�ʹ��
		TGTHT510_faultdiagnosis_push_CG_set(p->mode,FAULT_STATE_NORMAL);
		
	}
	else
	{
		p->state=DISABLE;						//�ʼ��ֹ
		TGTHT510_faultdiagnosis_push_CG_set(p->mode,FAULT_STATE_DISABLE);
	}
	p->result=FALSE;							//����δ����
	
	p->fault_field1.time_flag=FALSE;			//��ʱ��1δʹ��
	p->fault_field1.step=FAULT_STEP_START;		//�����ʼ�
	p->fault_field2.time_flag=FALSE;			//��ʱ��1δʹ��
	p->fault_field2.step=FAULT_STEP_START;		//�����ʼ�
	p->fault_field3.time_flag=FALSE;			//��ʱ��1δʹ��
	p->fault_field3.step=FAULT_STEP_START;		//�����ʼ�
	p->faultdiagnosis_count=0;
}

/******************************************************************************************
**���ƣ����ϼ��ģ���ʼ������--�ƽ�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_initial(void)
{
	uint16 i;
	
	for(i=0;i<=6;i++)
	{
		TGTHT510_fault_data_CG_push[i]=0x0000;
	}
	
	TGTHT510_fault_data_CG_push[6]=0xffff;
	TGTHT510_fault_data_CG_push[5]=0x000f;
	
	TGTHT510_faultdiagnosis_is_CPU_A_done_initial();
	
	TGTHT510_faultdiagnosis_push_struct_mode_add();
	
	fault_deal.step=FAULT_STEP_NONE;
	fault_deal.fault_mode=FAULT_MODE_NONE;
	fault_deal.compressor_step=FAULT_STEP_NONE;
	fault_deal.time_flag=FALSE;
	mode_test=0x0000;

//����ʹ�õĹ��Ӻ���	
	TGTHT510_faultdiagnosis_test_hook();

//�ƽ����ֹʼ��ʼ��----------------------------------------------------------------------

	//����ƿ1й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,DISABLE);
	
	//����ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,DISABLE);
	
	//����ƿ3й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,DISABLE);
	
	//ȼ��ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,DISABLE);
	
	//ȼ��ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,DISABLE);
	
	//ȼ��ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,DISABLE);
	
	//��1���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,DISABLE);
	
	//��2���䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,DISABLE);
	
	//��3���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,DISABLE);
	
	//ȼ1���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,DISABLE);
	
	//ȼ2���䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,DISABLE);
	
	//ȼ3���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,DISABLE);
	
	//�����˿ط��������Ʒ���й©
	TGTHT510_fault_push_B_main_valve_leak.state=DISABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_main_valve_leak.faultdiagnosis_count=0;
	
	//�����˿ط��������Ʒ���й©
	TGTHT510_fault_push_B_less_valve_leak.state=DISABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_less_valve_leak.faultdiagnosis_count=0;
	
	//C���˿ط��������Ʒ���й©
	TGTHT510_fault_push_C_all_valve_leak.state=DISABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_C_all_valve_leak.faultdiagnosis_count=0;
	
	//A�������˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_main_valve_leak.state=DISABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_main_valve_leak.faultdiagnosis_count=0;
	
	//A�鱸���˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_less_valve_leak.state=DISABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_less_valve_leak.faultdiagnosis_count=0;
	
	//��1����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,DISABLE);
	
	//��2����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,DISABLE);
	
	//��3����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,DISABLE);
	
	//ȼ1����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,DISABLE);
	
	//ȼ2����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,DISABLE);
	
	//ȼ3����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,DISABLE);
	
}


/******************************************************************************************
**���ƣ����ϼ��ģ���ʼ������--���Ӳ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_initial(void)
{
	uint16 i;
	
	TGTHT510_faultdiagnosis_supply_struct_mode_add();
	
	for(i=0;i<=29;i++)
	{
		TGTHT510_fault_data_CG_supply[i]=0x0000;
	}
	
	mode_test=0x0000;
	//�������������
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,DISABLE);
	
	//����Һ�����ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,DISABLE);
	
	//����Һ�䱸�ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,DISABLE);
	
	//����Һ�����ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,DISABLE);
	
	//����Һ�䱸�ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,DISABLE);
	
	//����Һ��й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,DISABLE);
	
	//����Һ��й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,DISABLE);
	
	//ѹ����A��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,DISABLE);
	
	//ѹ����B��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,DISABLE);
	
	//ѹ����C��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,DISABLE);
	
	//ѹ����A���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,DISABLE);
	
	//ѹ����B���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,DISABLE);
	
	//ѹ����C���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,DISABLE);
	
	//ѹ����A����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,DISABLE);
	
	//ѹ����B����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,DISABLE);
	
	//ѹ����C����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,DISABLE);
	
	//��1�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,DISABLE);
	
	//��2�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,DISABLE);
	
	//��3�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,DISABLE);
	
	//ȼ1�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,DISABLE);
	
	//ȼ2�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,DISABLE);
	
	//ȼ3�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,DISABLE);
	
	//ѹ����AĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,DISABLE);
	
	//ѹ����BĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,DISABLE);
	
	//ѹ����CĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,DISABLE);
	
	//����ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,DISABLE);
	
	//����ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,DISABLE);
	
	//����ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,DISABLE);
	
	//ȼ��ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,DISABLE);
	
	//ȼ��ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,DISABLE);
	
	//ȼ��ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,DISABLE);
	
	//��1���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,DISABLE);
	
	//��2���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,DISABLE);
	
	//��3���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,DISABLE);
	
	//ȼ1���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,DISABLE);
	
	//ȼ2���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,DISABLE);
	
	//ȼ3���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,DISABLE);
	
	//���������¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,DISABLE);
	
	//ȼ�������¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,DISABLE);
	
	//�������ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,DISABLE);
	
	//�������ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,DISABLE);
	
	//ȼ�����ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,DISABLE);
	
	//ȼ�����ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,DISABLE);
	
	//ǰ��ȼ1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,DISABLE);
	
	//ǰ��ȼ2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,DISABLE);
	
	//ǰ����1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,DISABLE);
	
	//ǰ����2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,DISABLE);
	
	//����ȼ1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,DISABLE);
	
	//����ȼ2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,DISABLE);
	
	//������1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,DISABLE);
	
	//������2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,DISABLE);
	
	//��1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,DISABLE);
	
	//��2���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,DISABLE);
	
	//��3���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,DISABLE);
	
}

/******************************************************************************************
**���ƣ����ϼ��ģ��������--�ƽ�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_main(void)
{
	//����ƿ1й©
	if(TGTHT510_fault_push_o_gas1_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_gas1_leak);//ʱ���������
		TGTHT510_faultdiagnosis_push_gas_leak_big(FAULT_O_GAS1);//��©���
		TGTHT510_faultdiagnosis_push_gas_leak_small(FAULT_O_GAS1);//С©���
		TGTHT510_faultdiagnosis_push_gas_leak_min(FAULT_O_GAS1);//����ֵ���
	}
	
	//����ƿ2й©
	if(TGTHT510_fault_push_o_gas2_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_gas2_leak);//ʱ���������
		TGTHT510_faultdiagnosis_push_gas_leak_big(FAULT_O_GAS2);//��©���
		TGTHT510_faultdiagnosis_push_gas_leak_small(FAULT_O_GAS2);//С©���
		TGTHT510_faultdiagnosis_push_gas_leak_min(FAULT_O_GAS2);//����ֵ���
	}
	
	//����ƿ3й©
	if(TGTHT510_fault_push_o_gas3_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_gas3_leak);//ʱ���������
		TGTHT510_faultdiagnosis_push_gas_leak_big(FAULT_O_GAS3);//��©���
		TGTHT510_faultdiagnosis_push_gas_leak_small(FAULT_O_GAS3);//С©���
		TGTHT510_faultdiagnosis_push_gas_leak_min(FAULT_O_GAS3);//����ֵ���
	}
	
	//ȼ��ƿ1й©
	if(TGTHT510_fault_push_f_gas1_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_gas1_leak);//ʱ���������
		TGTHT510_faultdiagnosis_push_gas_leak_big(FAULT_F_GAS1);//��©���
		TGTHT510_faultdiagnosis_push_gas_leak_small(FAULT_F_GAS1);//С©���
		TGTHT510_faultdiagnosis_push_gas_leak_min(FAULT_F_GAS1);//����ֵ���
	}
	
	//ȼ��ƿ2й©
	if(TGTHT510_fault_push_f_gas2_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_gas2_leak);//ʱ���������
		TGTHT510_faultdiagnosis_push_gas_leak_big(FAULT_F_GAS2);//��©���
		TGTHT510_faultdiagnosis_push_gas_leak_small(FAULT_F_GAS2);//С©���
		TGTHT510_faultdiagnosis_push_gas_leak_min(FAULT_F_GAS2);//����ֵ���
	}
	
	//ȼ��ƿ3й©
	if(TGTHT510_fault_push_f_gas3_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_gas3_leak);//ʱ���������
		TGTHT510_faultdiagnosis_push_gas_leak_big(FAULT_F_GAS3);//��©���
		TGTHT510_faultdiagnosis_push_gas_leak_small(FAULT_F_GAS3);//С©���
		TGTHT510_faultdiagnosis_push_gas_leak_min(FAULT_F_GAS3);//����ֵ���
	}
	
	//��1���䳬ѹ
	if(TGTHT510_fault_push_o_tank1_overpressure.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_tank1_overpressure);//ʱ���������
		TGTHT510_faultdiagnosis_push_tank_overpressure(FAULT_O_TANK1);
	}
	
	//��2���䳬ѹ
	if(TGTHT510_fault_push_o_tank2_overpressure.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_tank2_overpressure);//ʱ���������
		TGTHT510_faultdiagnosis_push_tank_overpressure(FAULT_O_TANK2);
	}
	
	//��3���䳬ѹ
	if(TGTHT510_fault_push_o_tank3_overpressure.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_tank3_overpressure);//ʱ���������
		TGTHT510_faultdiagnosis_push_tank_overpressure(FAULT_O_TANK3);
	}
	
	//ȼ1���䳬ѹ
	if(TGTHT510_fault_push_f_tank1_overpressure.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_tank1_overpressure);//ʱ���������
		TGTHT510_faultdiagnosis_push_tank_overpressure(FAULT_F_TANK1);
	}
	
	//ȼ2���䳬ѹ
	if(TGTHT510_fault_push_f_tank2_overpressure.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_tank2_overpressure);//ʱ���������
		TGTHT510_faultdiagnosis_push_tank_overpressure(FAULT_F_TANK2);
	}
	
	//ȼ3���䳬ѹ
	if(TGTHT510_fault_push_f_tank3_overpressure.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_tank3_overpressure);//ʱ���������
		TGTHT510_faultdiagnosis_push_tank_overpressure(FAULT_F_TANK3);
	}
	
	//B�����ݷ�����й©
	if(TGTHT510_fault_push_B_main_valve_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_push_valve_leak(FAULT_B_MAIN_LEAK);
	}
	
	//B�鱸�ݷ�����й©
	if(TGTHT510_fault_push_B_less_valve_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_push_valve_leak(FAULT_B_LESS_LEAK);
	}
	
	//C�鷢����й©
	if(TGTHT510_fault_push_C_all_valve_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_push_valve_leak(FAULT_C_ALL_LEAK);
	}
	
	//A�����ݷ�����й©
	if(TGTHT510_fault_push_A_main_valve_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_push_valve_leak(FAULT_A_MAIN_LEAK);
	}
	
	//A�鱸�ݷ�����й©
	if(TGTHT510_fault_push_A_less_valve_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_push_valve_leak(FAULT_A_LESS_LEAK);
	}
	
	//��1����й©
	if(TGTHT510_fault_push_o_tank1_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_tank1_leak);//ʱ���������
		TGTHT510_faultdiagnosis_push_tank_leak(FAULT_O_TANK1);
	}
	
	//��2����й©
	if(TGTHT510_fault_push_o_tank2_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_tank2_leak);//ʱ���������
		TGTHT510_faultdiagnosis_push_tank_leak(FAULT_O_TANK2);
	}
	
	//��3����й©
	if(TGTHT510_fault_push_o_tank3_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_tank3_leak);//ʱ���������
		TGTHT510_faultdiagnosis_push_tank_leak(FAULT_O_TANK3);
	}
	
	//ȼ1����й©
	if(TGTHT510_fault_push_f_tank1_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_tank1_leak);//ʱ���������
		TGTHT510_faultdiagnosis_push_tank_leak(FAULT_F_TANK1);
	}
	
	//ȼ2����й©
	if(TGTHT510_fault_push_f_tank2_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_tank2_leak);//ʱ���������
		TGTHT510_faultdiagnosis_push_tank_leak(FAULT_F_TANK2);
	}
	
	//ȼ3����й©
	if(TGTHT510_fault_push_f_tank3_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_tank3_leak);//ʱ���������
		TGTHT510_faultdiagnosis_push_tank_leak(FAULT_F_TANK3);
	}
	
}

/******************************************************************************************
**���ƣ����ϼ��ģ��������--���Ӳ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_main(void)
{
	//�������������
	if(TGTHT510_fault_supply_TGTHT530.state==ENABLE)//ʹ��
	{
		//�����䣡������
		
	}
	
	//����Һ�����ù���
	if(TGTHT510_fault_supply_cooler_zz.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_cooler_zz);//ʱ���������
		TGTHT510_faultdiagnosis_supply_cooler(FAULT_COOLER_ZZ);
	}
	
	//����Һ�䱸�ù���
	if(TGTHT510_fault_supply_cooler_zb.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_cooler_zb);//ʱ���������
		TGTHT510_faultdiagnosis_supply_cooler(FAULT_COOLER_ZB);
	}
	
	//����Һ�����ù���
	if(TGTHT510_fault_supply_cooler_bz.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_cooler_bz);//ʱ���������
		TGTHT510_faultdiagnosis_supply_cooler(FAULT_COOLER_BZ);
	}
	
	//����Һ�䱸�ù���
	if(TGTHT510_fault_supply_cooler_bb.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_cooler_bb);//ʱ���������
		TGTHT510_faultdiagnosis_supply_cooler(FAULT_COOLER_BB);
	}
	
	//����Һ��й©
	if(TGTHT510_fault_supply_leak_cooler_z.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_leak_cooler_z);//ʱ���������
		TGTHT510_faultdiagnosis_supply_leak_cooler(FAULT_COOLER_Z);
	}
	
	//����Һ��й©
	if(TGTHT510_fault_supply_leak_cooler_b.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_leak_cooler_b);//ʱ���������
		TGTHT510_faultdiagnosis_supply_leak_cooler(FAULT_COOLER_B);
	}
	
	//ѹ����A��ڳ�ѹ
	if(TGTHT510_fault_supply_compressor_A_in_over.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_A_in_over);//ʱ���������
		TGTHT510_faultdiagnosis_supply_over_compressor(FAULT_COMPRESSOR_A_IN_OVER);
	}
	
	//ѹ����B��ڳ�ѹ
	if(TGTHT510_fault_supply_compressor_B_in_over.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_B_in_over);//ʱ���������
		TGTHT510_faultdiagnosis_supply_over_compressor(FAULT_COMPRESSOR_B_IN_OVER);
	}
	
	//ѹ����C��ڳ�ѹ
	if(TGTHT510_fault_supply_compressor_C_in_over.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_C_in_over);//ʱ���������
		TGTHT510_faultdiagnosis_supply_over_compressor(FAULT_COMPRESSOR_C_IN_OVER);
	}
	
	//ѹ����A���ǻ��ѹ
	if(TGTHT510_fault_supply_compressor_A_motor_over.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_A_motor_over);//ʱ���������
		TGTHT510_faultdiagnosis_supply_over_compressor(FAULT_COMPRESSOR_A_MOTOR_OVER);
	}
	
	//ѹ����B���ǻ��ѹ
	if(TGTHT510_fault_supply_compressor_B_motor_over.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_B_motor_over);//ʱ���������
		TGTHT510_faultdiagnosis_supply_over_compressor(FAULT_COMPRESSOR_B_MOTOR_OVER);
	}
	
	//ѹ����C���ǻ��ѹ
	if(TGTHT510_fault_supply_compressor_C_motor_over.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_C_motor_over);//ʱ���������
		TGTHT510_faultdiagnosis_supply_over_compressor(FAULT_COMPRESSOR_C_MOTOR_OVER);
	}
	
	//ѹ����A����
	if(TGTHT510_fault_supply_compressor_A_hot.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_A_hot);//ʱ���������
		TGTHT510_faultdiagnosis_supply_hot_compressor(FAULT_COMPRESSOR_A_HOT);
	}
	
	//ѹ����B����
	if(TGTHT510_fault_supply_compressor_B_hot.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_B_hot);//ʱ���������
		TGTHT510_faultdiagnosis_supply_hot_compressor(FAULT_COMPRESSOR_B_HOT);
	}
	
	//ѹ����C����
	if(TGTHT510_fault_supply_compressor_C_hot.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_C_hot);//ʱ���������
		TGTHT510_faultdiagnosis_supply_hot_compressor(FAULT_COMPRESSOR_C_HOT);
	}
	
	//��1�������䳬ѹ
	if(TGTHT510_fault_supply_o_tank1_overpressure.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_o_tank1_overpressure);//ʱ���������
		TGTHT510_faultdiagnosis_supply_tank_overpressure(FAULT_O_TANK1);
	}
	
	//��2�������䳬ѹ
	if(TGTHT510_fault_supply_o_tank2_overpressure.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_o_tank2_overpressure);//ʱ���������
		TGTHT510_faultdiagnosis_supply_tank_overpressure(FAULT_O_TANK2);
	}
	
	//��3�������䳬ѹ
	if(TGTHT510_fault_supply_o_tank3_overpressure.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_o_tank3_overpressure);//ʱ���������
		TGTHT510_faultdiagnosis_supply_tank_overpressure(FAULT_O_TANK3);
	}
	
	//ȼ1�������䳬ѹ
	if(TGTHT510_fault_supply_f_tank1_overpressure.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_f_tank1_overpressure);//ʱ���������
		TGTHT510_faultdiagnosis_supply_tank_overpressure(FAULT_F_TANK1);
	}
	
	//ȼ2�������䳬ѹ
	if(TGTHT510_fault_supply_f_tank2_overpressure.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_f_tank2_overpressure);//ʱ���������
		TGTHT510_faultdiagnosis_supply_tank_overpressure(FAULT_F_TANK2);
	}
	
	//ȼ3�������䳬ѹ
	if(TGTHT510_fault_supply_f_tank3_overpressure.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_f_tank3_overpressure);//ʱ���������
		TGTHT510_faultdiagnosis_supply_tank_overpressure(FAULT_F_TANK3);
	}
	
	//ѹ����AĤƬ����
	if(TGTHT510_fault_supply_compressor_A_break.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_A_break);//ʱ���������
		TGTHT510_faultdiagnosis_supply_compressor_break(FAULT_COMPRESSOR_A_BREAK);
	}
	
	//ѹ����BĤƬ����
	if(TGTHT510_fault_supply_compressor_B_break.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_B_break);//ʱ���������
		TGTHT510_faultdiagnosis_supply_compressor_break(FAULT_COMPRESSOR_B_BREAK);
	}
	
	//ѹ����CĤƬ����
	if(TGTHT510_fault_supply_compressor_C_break.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_C_break);//ʱ���������
		TGTHT510_faultdiagnosis_supply_compressor_break(FAULT_COMPRESSOR_C_BREAK);
	}
	
	//����ƿ1й©
	if(TGTHT510_fault_supply_o_gas1_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_o_gas1_leak);//ʱ���������
		TGTHT510_faultdiagnosis_supply_gas_leak_big(FAULT_O_GAS1);		//��©
		TGTHT510_faultdiagnosis_supply_gas_leak_small(FAULT_O_GAS1);	//С©
		TGTHT510_faultdiagnosis_supply_gas_leak_min(FAULT_O_GAS1);		//����ֵ
	}
	
	//����ƿ2й©
	if(TGTHT510_fault_supply_o_gas2_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_o_gas2_leak);//ʱ���������
		TGTHT510_faultdiagnosis_supply_gas_leak_big(FAULT_O_GAS2);		//��©
		TGTHT510_faultdiagnosis_supply_gas_leak_small(FAULT_O_GAS2);	//С©
		TGTHT510_faultdiagnosis_supply_gas_leak_min(FAULT_O_GAS2);		//����ֵ
	}
	
	//����ƿ3й©
	if(TGTHT510_fault_supply_o_gas3_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_o_gas3_leak);//ʱ���������
		TGTHT510_faultdiagnosis_supply_gas_leak_big(FAULT_O_GAS3);		//��©
		TGTHT510_faultdiagnosis_supply_gas_leak_small(FAULT_O_GAS3);	//С©
		TGTHT510_faultdiagnosis_supply_gas_leak_min(FAULT_O_GAS3);		//����ֵ
	}
	
	//ȼ��ƿ1й©
	if(TGTHT510_fault_supply_f_gas1_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_f_gas1_leak);//ʱ���������
		TGTHT510_faultdiagnosis_supply_gas_leak_big(FAULT_F_GAS1);		//��©
		TGTHT510_faultdiagnosis_supply_gas_leak_small(FAULT_F_GAS1);	//С©
		TGTHT510_faultdiagnosis_supply_gas_leak_min(FAULT_F_GAS1);		//����ֵ
	}
	
	//ȼ��ƿ2й©
	if(TGTHT510_fault_supply_f_gas2_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_f_gas2_leak);//ʱ���������
		TGTHT510_faultdiagnosis_supply_gas_leak_big(FAULT_F_GAS2);		//��©
		TGTHT510_faultdiagnosis_supply_gas_leak_small(FAULT_F_GAS2);	//С©
		TGTHT510_faultdiagnosis_supply_gas_leak_min(FAULT_F_GAS2);		//����ֵ
	}
	
	//ȼ��ƿ3й©
	if(TGTHT510_fault_supply_f_gas3_leak.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_f_gas3_leak);//ʱ���������
		TGTHT510_faultdiagnosis_supply_gas_leak_big(FAULT_F_GAS3);		//��©
		TGTHT510_faultdiagnosis_supply_gas_leak_small(FAULT_F_GAS3);	//С©
		TGTHT510_faultdiagnosis_supply_gas_leak_min(FAULT_F_GAS3);		//����ֵ
	}
	
	//��1���䲹��Һ·й©
	if(TGTHT510_fault_supply_pipe_leak_o_tank1.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_pipe_leak_o_tank1);//ʱ���������
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak(FAULT_O_TANK1);
	}
	
	//��2���䲹��Һ·й©
	if(TGTHT510_fault_supply_pipe_leak_o_tank2.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_pipe_leak_o_tank2);//ʱ���������
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak(FAULT_O_TANK2);
	}
	
	//��3���䲹��Һ·й©
	if(TGTHT510_fault_supply_pipe_leak_o_tank3.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_pipe_leak_o_tank3);//ʱ���������
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak(FAULT_O_TANK3);
	}
	
	//ȼ1���䲹��Һ·й©
	if(TGTHT510_fault_supply_pipe_leak_f_tank1.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_pipe_leak_f_tank1);//ʱ���������
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak(FAULT_F_TANK1);
	}
	
	//ȼ2���䲹��Һ·й©
	if(TGTHT510_fault_supply_pipe_leak_f_tank2.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_pipe_leak_f_tank2);//ʱ���������
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak(FAULT_F_TANK2);
	}
	
	//ȼ3���䲹��Һ·й©
	if(TGTHT510_fault_supply_pipe_leak_f_tank3.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_pipe_leak_f_tank3);//ʱ���������
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak(FAULT_F_TANK3);
	}
	
	//���������¶��쳣
	if(TGTHT510_fault_supply_interface_o_temperature.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_interface_o_temperature);//ʱ���������
		TGTHT510_faultdiagnosis_supply_interface_temperature(FAULT_INTERFACE_O);
	}
	
	//ȼ�������¶��쳣
	if(TGTHT510_fault_supply_interface_f_temperature.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_interface_f_temperature);//ʱ���������
		TGTHT510_faultdiagnosis_supply_interface_temperature(FAULT_INTERFACE_F);
	}
	
	//�������ӹ�·��©
	if(TGTHT510_fault_supply_in_leak_o_z.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_in_leak_o_z);//ʱ���������
		TGTHT510_faultdiagnosis_supply_in_leak(FAULT_IN_LEAK_O_Z);
	}
	
	//�������ӹ�·��©
	if(TGTHT510_fault_supply_in_leak_o_b.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_in_leak_o_b);//ʱ���������
		TGTHT510_faultdiagnosis_supply_in_leak(FAULT_IN_LEAK_O_B);
	}
	
	//ȼ�����ӹ�·��©
	if(TGTHT510_fault_supply_in_leak_f_z.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_in_leak_f_z);//ʱ���������
		TGTHT510_faultdiagnosis_supply_in_leak(FAULT_IN_LEAK_F_Z);
	}
	
	//ȼ�����ӹ�·��©
	if(TGTHT510_fault_supply_in_leak_f_b.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_in_leak_f_b);//ʱ���������
		TGTHT510_faultdiagnosis_supply_in_leak(FAULT_IN_LEAK_F_B);
	}
	
	//ǰ��ȼ1�����Ͻ����¶��쳣
	if(TGTHT510_fault_supply_temperature_fore_f1.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_fore_f1);//ʱ���������
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_FORE_F1);
	}
	
	//ǰ��ȼ2�����Ͻ����¶��쳣
	if(TGTHT510_fault_supply_temperature_fore_f2.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_fore_f2);//ʱ���������
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_FORE_F2);
	}
	
	//ǰ����1�����Ͻ����¶��쳣
	if(TGTHT510_fault_supply_temperature_fore_o1.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_fore_o1);//ʱ���������
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_FORE_O1);
	}
	
	//ǰ����2�����Ͻ����¶��쳣
	if(TGTHT510_fault_supply_temperature_fore_o2.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_fore_o2);//ʱ���������
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_FORE_O2);
	}
	
	//����ȼ1�����Ͻ����¶��쳣
	if(TGTHT510_fault_supply_temperature_back_f1.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_back_f1);//ʱ���������
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_BACK_F1);
	}
	
	//����ȼ2�����Ͻ����¶��쳣
	if(TGTHT510_fault_supply_temperature_back_f2.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_back_f2);//ʱ���������
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_BACK_F2);
	}
	
	//������1�����Ͻ����¶��쳣
	if(TGTHT510_fault_supply_temperature_back_o1.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_back_o1);//ʱ���������
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_BACK_O1);
	}
	
	//������2�����Ͻ����¶��쳣
	if(TGTHT510_fault_supply_temperature_back_o2.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_back_o2);//ʱ���������
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_BACK_O2);
	}
	
	//��1���俨��
	if(TGTHT510_fault_supply_ka_o_tank1.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_ka_o_tank1);//ʱ���������
		TGTHT510_faultdiagnosis_supply_ka_tank(FAULT_O_TANK1);
	}
	
	//��2���俨��
	if(TGTHT510_fault_supply_ka_o_tank2.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_ka_o_tank2);//ʱ���������
		TGTHT510_faultdiagnosis_supply_ka_tank(FAULT_O_TANK2);
	}
	
	//��3���俨��
	if(TGTHT510_fault_supply_ka_o_tank3.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_ka_o_tank3);//ʱ���������
		TGTHT510_faultdiagnosis_supply_ka_tank(FAULT_O_TANK3);
	}
	
	//ȼ1���俨��
	if(TGTHT510_fault_supply_ka_f_tank1.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_ka_f_tank1);//ʱ���������
		TGTHT510_faultdiagnosis_supply_ka_tank(FAULT_F_TANK1);
	}
	
	//ȼ2���俨��
	if(TGTHT510_fault_supply_ka_f_tank2.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_ka_f_tank2);//ʱ���������
		TGTHT510_faultdiagnosis_supply_ka_tank(FAULT_F_TANK2);
	}
	
	//ȼ3���俨��
	if(TGTHT510_fault_supply_ka_f_tank3.state==ENABLE)//ʹ��
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_ka_f_tank3);//ʱ���������
		TGTHT510_faultdiagnosis_supply_ka_tank(FAULT_F_TANK3);
	}
	
	
}

/******************************************************************************************
**���ƣ�����������ͣ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_pause(void)
{
	if((TGTHT510_supply_ctrl.state==STATE_RUN)&&(TGTHT510_supply_ctrl.stage!=STAGE_00_NONE))
	{
		TGTHT510_supply_main_pause(ERRNO_FAULT_DIAGNOSIS);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ�����ϵͳ������λ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_lvb_set(uint16 code)
{
	if((code>=LVb1K)&&(code<=LVb87G))//����ָ�����Ϊ����������ָ��ҺϷ�
	{
		TGTHT510_valvecontrol_struct.command_from_fault=code;//�����ڲ���ַ����
		TGTHT510_valvecontrol_struct.command_from_fault_time=2;//����200ms
	}
}


/******************************************************************************************
**���ƣ����ϼ��ģ�麯��--�ƽ����֣�����ң�������λ����--ͨ�ú���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_CG_set_dealing(uint16 *p,uint16 fault_state,uint16 set_bit)
{
	if(fault_state==FAULT_STATE_DISABLE)//�ʼ�״̬�������࣬��λ1111
	{
		switch(set_bit)
		{
			case FAULT_BIT15_12_SET: //bit15-12����
			{
				*p = *p | 0xf000;
				break;
			}
			
			case FAULT_BIT11_08_SET: //bit11-8����
			{
				*p = *p | 0x0f00;
				break;
			}
			
			case FAULT_BIT07_04_SET: //bit7-4����
			{
				*p = *p | 0x00f0;
				break;
			}
			
			case FAULT_BIT03_00_SET: //bit3-0����
			{
				*p = *p | 0x000f;
				break;
			}
			
			default:
			{
				break;
			}
			
		}
	}
	
	else if(fault_state==FAULT_STATE_NORMAL)//�ʼ�״̬����������λ0101
	{
		switch(set_bit)
		{
			case FAULT_BIT15_12_SET: //bit15-12����
			{
				*p = (*p & 0x5fff) | 0x5000;
				break;
			}
			
			case FAULT_BIT11_08_SET: //bit11-8����
			{
				*p = (*p & 0xf5ff) | 0x0500;
				break;
			}
			
			case FAULT_BIT07_04_SET: //bit7-4����
			{
				*p = (*p & 0xff5f) | 0x0050;
				break;
			}
			
			case FAULT_BIT03_00_SET: //bit3-0����
			{
				*p = (*p & 0xfff5) | 0x0005;
				break;
			}
			
			default:
			{
				break;
			}
			
		}
	}
	
	else if(fault_state==FAULT_STATE_ABNORMAL)//�ʼ�״̬���쳣����λ1010
	{
		switch(set_bit)
		{
			case FAULT_BIT15_12_SET: //bit15-12����
			{
				*p = (*p & 0xafff) | 0xa000;
				break;
			}
			
			case FAULT_BIT11_08_SET: //bit11-8����
			{
				*p = (*p & 0xfaff) | 0x0a00;
				break;
			}
			
			case FAULT_BIT07_04_SET: //bit7-4����
			{
				*p = (*p & 0xffaf) | 0x00a0;
				break;
			}
			
			case FAULT_BIT03_00_SET: //bit3-0����
			{
				*p = (*p & 0xfffa) | 0x000a;
				break;
			}
			
			default:
			{
				break;
			}
			
		}
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ����ϼ��ģ�麯��--�ƽ����֣�����ң�������λ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_CG_set(uint16 mode,uint16 state)
{
	switch(mode)
	{
		case FAULT_MODE_PUSH_LEAK_O_GAS1://�ƽ����ϣ���1��ƿй©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[1],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_GAS2://�ƽ����ϣ���2��ƿй©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[1],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_GAS3://�ƽ����ϣ���3��ƿй©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[2],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS1://�ƽ����ϣ�ȼ1��ƿй©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[2],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS2://�ƽ����ϣ�ȼ2��ƿй©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[2],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS3://�ƽ����ϣ�ȼ3��ƿй©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[2],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK1://�ƽ����ϣ���1���䳬ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[0],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK2://�ƽ����ϣ���2���䳬ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[0],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK3://�ƽ����ϣ���3���䳬ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[0],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK1://�ƽ����ϣ�ȼ1���䳬ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[0],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK2://�ƽ����ϣ�ȼ2���䳬ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[1],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK3://�ƽ����ϣ�ȼ3���䳬ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[1],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_B_MAIN://�ƽ����ϣ������˿ط��������Ʒ���й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[5],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_B_LESS://�ƽ����ϣ������˿ط��������Ʒ���й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[5],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_C_ALL://�ƽ����ϣ�C���˿ط��������Ʒ���й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[5],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_A_MAIN://�ƽ����ϣ�A�������˿ط��������Ʒ���й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[4],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_A_LESS://�ƽ����ϣ�A�鱸���˿ط��������Ʒ���й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[4],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK1://�ƽ����ϣ���1����й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[3],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK2://�ƽ����ϣ���2����й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[3],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK3://�ƽ����ϣ���3����й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[3],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK1://�ƽ����ϣ�ȼ1����й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[3],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK2://�ƽ����ϣ�ȼ2����й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[4],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK3://�ƽ����ϣ�ȼ3����й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[4],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_ZZ://���ӹ��ϣ�����Һ�����ù���
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[0],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_ZB://���ӹ��ϣ�����Һ�䱸�ù���
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[0],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_BZ://���ӹ��ϣ�����Һ�����ù���
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[0],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_BB://���ӹ��ϣ�����Һ�䱸�ù���
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[0],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_COOLER_Z://���ӹ��ϣ�����Һ��й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[1],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_COOLER_B://���ӹ��ϣ�����Һ��й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[1],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_A_IN://���ӹ��ϣ�ѹ����A��ڳ�ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[1],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_B_IN://���ӹ��ϣ�ѹ����B��ڳ�ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[1],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_C_IN://���ӹ��ϣ�ѹ����C��ڳ�ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[2],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR://���ӹ��ϣ�ѹ����A���ǻ��ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[2],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR://���ӹ��ϣ�ѹ����B���ǻ��ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[2],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR://���ӹ��ϣ�ѹ����C���ǻ��ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[2],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_A_HOT://���ӹ��ϣ�ѹ����A����
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[3],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_B_HOT://���ӹ��ϣ�ѹ����B����
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[3],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_C_HOT://���ӹ��ϣ�ѹ����C����
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[3],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK1://���ӹ��ϣ���1�������䳬ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[3],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK2://���ӹ��ϣ���2�������䳬ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[4],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK3://���ӹ��ϣ���3�������䳬ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[4],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK1://���ӹ��ϣ�ȼ1�������䳬ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[4],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK2://���ӹ��ϣ�ȼ2�������䳬ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[4],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK3://���ӹ��ϣ�ȼ3�������䳬ѹ
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[5],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_A_BREAK://���ӹ��ϣ�ѹ����AĤƬ����
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[5],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_B_BREAK://���ӹ��ϣ�ѹ����BĤƬ����
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[5],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_C_BREAK://���ӹ��ϣ�ѹ����CĤƬ����
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[5],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS1://���ӹ��ϣ���1��ƿй©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[6],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS2://���ӹ��ϣ���2��ƿй©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[6],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS3://���ӹ��ϣ���3��ƿй©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[6],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS1://���ӹ��ϣ�ȼ1��ƿй©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[6],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS2://���ӹ��ϣ�ȼ2��ƿй©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[7],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS3://���ӹ��ϣ�ȼ3��ƿй©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[7],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1://���ӹ��ϣ���1���䲹��Һ·й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[7],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2://���ӹ��ϣ���2���䲹��Һ·й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[7],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3://���ӹ��ϣ���3���䲹��Һ·й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[8],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1://���ӹ��ϣ�ȼ1���䲹��Һ·й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[8],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2://���ӹ��ϣ�ȼ2���䲹��Һ·й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[8],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3://���ӹ��ϣ�ȼ3���䲹��Һ·й©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[8],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_INTERFACE_O_TEMP://���ӹ��ϣ����������¶��쳣
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[9],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_INTERFACE_F_TEMP://���ӹ��ϣ�ȼ�������¶��쳣
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[9],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_O_Z://���ӹ��ϣ��������ӹ�·��©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[9],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_O_B://���ӹ��ϣ��������ӹ�·��©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[9],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_F_Z://���ӹ��ϣ�ȼ�����ӹ�·��©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[10],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_F_B://���ӹ��ϣ�ȼ�����ӹ�·��©
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[10],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1://���ӹ��ϣ�ǰ��ȼ1�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[10],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2://���ӹ��ϣ�ǰ��ȼ2�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[10],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1://���ӹ��ϣ�ǰ����1�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[11],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2://���ӹ��ϣ�ǰ����2�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[11],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1://���ӹ��ϣ�����ȼ1�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[11],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2://���ӹ��ϣ�����ȼ2�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[11],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1://���ӹ��ϣ�������1�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[12],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2://���ӹ��ϣ�������2�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[12],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK1://���ӹ��ϣ���1���俨��
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[12],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK2://���ӹ��ϣ���2���俨��
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[12],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK3://���ӹ��ϣ���3���俨��
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[13],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK1://���ӹ��ϣ�ȼ1���俨��
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[13],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK2://���ӹ��ϣ�ȼ2���俨��
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[13],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK3://���ӹ��ϣ�ȼ3���俨��
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[13],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TGTHT530://���ӹ��ϣ��������������
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[14],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		default:
		{
			break;
		}
	}

}

/******************************************************************************************
**���ƣ����ϼ��ģ�麯��--���Ӳ��֣�����ң�������λ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_CG_set(uint16 mode,uint16 state)
{
	TGTHT510_faultdiagnosis_push_CG_set(mode,state);
	
}


/******************************************************************************************
**���ƣ����ϼ��ģ�麯��--���Ӳ��֣�����ң�������λ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_enable_disable_set(uint16 mode,uint16 state)
{
	switch(mode)
	{
		case FAULT_MODE_PUSH_LEAK_O_GAS1://�ƽ����ϣ���1��ƿй©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_GAS2://�ƽ����ϣ���2��ƿй©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_GAS3://�ƽ����ϣ���3��ƿй©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS1://�ƽ����ϣ�ȼ1��ƿй©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS2://�ƽ����ϣ�ȼ2��ƿй©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS3://�ƽ����ϣ�ȼ3��ƿй©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK1://�ƽ����ϣ���1���䳬ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK2://�ƽ����ϣ���2���䳬ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK3://�ƽ����ϣ���3���䳬ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK1://�ƽ����ϣ�ȼ1���䳬ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK2://�ƽ����ϣ�ȼ2���䳬ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK3://�ƽ����ϣ�ȼ3���䳬ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_B_MAIN://�ƽ����ϣ������˿ط��������Ʒ���й©
		{
			if(state==ENABLE)
			{
				TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//�ʼ�ʹ��
				TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//����δ����
				TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
				TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_NORMAL);
			}
			
			else
			{
				TGTHT510_fault_push_B_main_valve_leak.state=DISABLE;								//�ʼ첻ʹ��
				TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//����δ����
				TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
				TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
				
			}
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_B_LESS://�ƽ����ϣ������˿ط��������Ʒ���й©
		{
			if(state==ENABLE)
			{
				TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//�ʼ�ʹ��
				TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//����δ����
				TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
				TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_NORMAL);
				
			}
			
			else
			{
				TGTHT510_fault_push_B_less_valve_leak.state=DISABLE;									//�ʼ�ʹ��
				TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//����δ����
				TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
				TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
				
			}
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_C_ALL://�ƽ����ϣ�C���˿ط��������Ʒ���й©
		{
			if(state==ENABLE)
			{
				TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//�ʼ�ʹ��
				TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//����δ����
				TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
				TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//�����ʼ�
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_NORMAL);
				
			}
			
			else
			{
				TGTHT510_fault_push_C_all_valve_leak.state=DISABLE;									//�ʼ�ʹ��
				TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//����δ����
				TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
				TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//�����ʼ�
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
				
			}
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_A_MAIN://�ƽ����ϣ�A�������˿ط��������Ʒ���й©
		{
			if(state==ENABLE)
			{
				TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//�ʼ�ʹ��
				TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//����δ����
				TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
				TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_NORMAL);
				
			}
			
			else
			{
				TGTHT510_fault_push_A_main_valve_leak.state=DISABLE;									//�ʼ�ʹ��
				TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//����δ����
				TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
				TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
				
			}
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_A_LESS://�ƽ����ϣ�A�鱸���˿ط��������Ʒ���й©
		{
			if(state==ENABLE)
			{
				TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//�ʼ�ʹ��
				TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//����δ����
				TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
				TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_NORMAL);
				
			}
			
			else
			{
				TGTHT510_fault_push_A_less_valve_leak.state=DISABLE;									//�ʼ�ʹ��
				TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//����δ����
				TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
				TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
				
			}
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK1://�ƽ����ϣ���1����й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK2://�ƽ����ϣ���2����й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK3://�ƽ����ϣ���3����й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK1://�ƽ����ϣ�ȼ1����й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK2://�ƽ����ϣ�ȼ2����й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK3://�ƽ����ϣ�ȼ3����й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_ZZ://���ӹ��ϣ�����Һ�����ù���
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_ZB://���ӹ��ϣ�����Һ�䱸�ù���
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_BZ://���ӹ��ϣ�����Һ�����ù���
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_BB://���ӹ��ϣ�����Һ�䱸�ù���
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_COOLER_Z://���ӹ��ϣ�����Һ��й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_COOLER_B://���ӹ��ϣ�����Һ��й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_A_IN://���ӹ��ϣ�ѹ����A��ڳ�ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_B_IN://���ӹ��ϣ�ѹ����B��ڳ�ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_C_IN://���ӹ��ϣ�ѹ����C��ڳ�ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR://���ӹ��ϣ�ѹ����A���ǻ��ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR://���ӹ��ϣ�ѹ����B���ǻ��ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR://���ӹ��ϣ�ѹ����C���ǻ��ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_A_HOT://���ӹ��ϣ�ѹ����A����
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_B_HOT://���ӹ��ϣ�ѹ����B����
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_C_HOT://���ӹ��ϣ�ѹ����C����
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK1://���ӹ��ϣ���1�������䳬ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK2://���ӹ��ϣ���2�������䳬ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK3://���ӹ��ϣ���3�������䳬ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK1://���ӹ��ϣ�ȼ1�������䳬ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK2://���ӹ��ϣ�ȼ2�������䳬ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK3://���ӹ��ϣ�ȼ3�������䳬ѹ
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_A_BREAK://���ӹ��ϣ�ѹ����AĤƬ����
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_B_BREAK://���ӹ��ϣ�ѹ����BĤƬ����
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_C_BREAK://���ӹ��ϣ�ѹ����CĤƬ����
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS1://���ӹ��ϣ���1��ƿй©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS2://���ӹ��ϣ���2��ƿй©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS3://���ӹ��ϣ���3��ƿй©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS1://���ӹ��ϣ�ȼ1��ƿй©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS2://���ӹ��ϣ�ȼ2��ƿй©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS3://���ӹ��ϣ�ȼ3��ƿй©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1://���ӹ��ϣ���1���䲹��Һ·й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2://���ӹ��ϣ���2���䲹��Һ·й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3://���ӹ��ϣ���3���䲹��Һ·й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1://���ӹ��ϣ�ȼ1���䲹��Һ·й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2://���ӹ��ϣ�ȼ2���䲹��Һ·й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3://���ӹ��ϣ�ȼ3���䲹��Һ·й©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_INTERFACE_O_TEMP://���ӹ��ϣ����������¶��쳣
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_INTERFACE_F_TEMP://���ӹ��ϣ�ȼ�������¶��쳣
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_O_Z://���ӹ��ϣ��������ӹ�·��©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_O_B://���ӹ��ϣ��������ӹ�·��©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_F_Z://���ӹ��ϣ�ȼ�����ӹ�·��©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_F_B://���ӹ��ϣ�ȼ�����ӹ�·��©
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1://���ӹ��ϣ�ǰ��ȼ1�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2://���ӹ��ϣ�ǰ��ȼ2�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1://���ӹ��ϣ�ǰ����1�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2://���ӹ��ϣ�ǰ����2�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1://���ӹ��ϣ�����ȼ1�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2://���ӹ��ϣ�����ȼ2�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1://���ӹ��ϣ�������1�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2://���ӹ��ϣ�������2�����Ͻ����¶��쳣
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK1://���ӹ��ϣ���1���俨��
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK2://���ӹ��ϣ���2���俨��
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK3://���ӹ��ϣ���3���俨��
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK1://���ӹ��ϣ�ȼ1���俨��
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK2://���ӹ��ϣ�ȼ2���俨��
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK3://���ӹ��ϣ�ȼ3���俨��
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TGTHT530://���ӹ��ϣ��������������
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_ALL://ȫ�����ӹ��ϣ��ƽ�����
		{
			TGTHT510_faultdiagnosis_push_all_enable_disable_set(state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_ALL://ȫ�����ӹ��ϣ����Ӳ���
		{
			TGTHT510_faultdiagnosis_supply_all_enable_disable_set(state);
			
			break;
		}
		
		case FAULT_MODE_ALL://ȫ������
		{
			TGTHT510_faultdiagnosis_push_all_enable_disable_set(state);
			TGTHT510_faultdiagnosis_supply_all_enable_disable_set(state);
			
			break;
		}
		
		default:
		{
			break;
		}
	}

}

/******************************************************************************************
**���ƣ����ϼ��ģ��ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_all_enable_disable_set(uint16 state)
{
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,state);
			
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,state);
			
	if(state==ENABLE)
	{
		TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//�ʼ�ʹ��
		TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//����δ����
		TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
		TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_NORMAL);
	}
			
	else
	{
		TGTHT510_fault_push_B_main_valve_leak.state=DISABLE;								//�ʼ첻ʹ��
		TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//����δ����
		TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
		TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
				
	}
	
	if(state==ENABLE)
	{
		TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//�ʼ�ʹ��
		TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//����δ����
		TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
		TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_NORMAL);
				
	}
			
	else
	{
		TGTHT510_fault_push_B_less_valve_leak.state=DISABLE;									//�ʼ�ʹ��
		TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//����δ����
		TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
		TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
				
	}
	
	if(state==ENABLE)
	{
		TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//�ʼ�ʹ��
		TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//����δ����
		TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
		TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//�����ʼ�
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_NORMAL);
				
	}
			
	else
	{
		TGTHT510_fault_push_C_all_valve_leak.state=DISABLE;									//�ʼ�ʹ��
		TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//����δ����
		TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
		TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//�����ʼ�
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
				
	}
	
	if(state==ENABLE)
	{
		TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//�ʼ�ʹ��
		TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//����δ����
		TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
		TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_NORMAL);
				
	}
			
	else
	{
		TGTHT510_fault_push_A_main_valve_leak.state=DISABLE;									//�ʼ�ʹ��
		TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//����δ����
		TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
		TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
		
	}
	
	if(state==ENABLE)
	{
		TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//�ʼ�ʹ��
		TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//����δ����
		TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
		TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_NORMAL);
				
	}
			
	else
	{
		TGTHT510_fault_push_A_less_valve_leak.state=DISABLE;									//�ʼ�ʹ��
		TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//����δ����
		TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
		TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
				
	}
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,state);	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,state);
	
}


/******************************************************************************************
**���ƣ����ϼ��ģ��ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_all_enable_disable_set(uint16 state)
{
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,state);

}

/******************************************************************************************
**���ƣ����ϼ��ģ��ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_time_dealing(fault_TypeDef *f)
{
	if(f->fault_field1.time_flag==TRUE)
	{
		f->fault_field1.time_count++;
	}
	
	else
	{
		f->fault_field1.time_count=0;
	}
	
	if(f->fault_field2.time_flag==TRUE)
	{
		f->fault_field2.time_count++;
	}
	
	else
	{
		f->fault_field2.time_count=0;
	}
	
	if(f->fault_field3.time_flag==TRUE)
	{
		f->fault_field3.time_count++;
	}
	
	else
	{
		f->fault_field3.time_count=0;
	}
	
}

/******************************************************************************************
**���ƣ����ϼ��ģ��ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_time1_start(fault_TypeDef *f)
{
	f->fault_field1.time_flag=TRUE;
	f->fault_field1.time_count=0;
}

/******************************************************************************************
**���ƣ����ϼ��ģ��ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_time1_end(fault_TypeDef *f)
{
	f->fault_field1.time_flag=FALSE;
}

/******************************************************************************************
**���ƣ����ϼ��ģ��ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_time2_start(fault_TypeDef *f)
{
	f->fault_field2.time_flag=TRUE;
	f->fault_field2.time_count=0;
}

/******************************************************************************************
**���ƣ����ϼ��ģ��ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_time2_end(fault_TypeDef *f)
{
	f->fault_field2.time_flag=FALSE;
}

/******************************************************************************************
**���ƣ����ϼ��ģ��ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_time1_is_get(fault_TypeDef *f,uint16 val)
{
	if(f->fault_field1.time_count>=val)
	{
		TGTHT510_faultdiagnosis_time1_end(f);
		
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**���ƣ����ϼ��ģ��ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_time2_is_get(fault_TypeDef *f,uint16 val)
{
	if(f->fault_field2.time_count>=val)
	{
		TGTHT510_faultdiagnosis_time2_end(f);
		
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**���ƣ� ��ƿ��©4ȡ3������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_gas_leak_min_four_of_three(uint16 *p,uint16 door_val)
{
	uint16 i,n;
	
	n=0;
	
	for(i=0;i<=3;i++)
	{
		if(p[i]<=door_val)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;//�жϹ��Ϸ���
	}
	
	else
	{
		return FALSE;//�жϹ���δ����
	}
}

/******************************************************************************************
**���ƣ� ��ƿ��©4ȡ3������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_gas_leak_four_of_three(uint16 *p,uint16 door_val)
{
	uint16 i,n;
	
	n=0;
	
	for(i=0;i<=3;i++)
	{
		if((p[i]>p[i+1])&&(((uint16)(abs(p[i]-p[i+1])))>door_val))
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;//�жϹ��Ϸ���
	}
	
	else
	{
		return FALSE;//�жϹ���δ����
	}
}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--��ƿй©--��ȡѹ��ֵ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//����ƿ1й©
	{
		return TGTHT510_1553B_data_TGTHT100[0];//PTt1	
	}
	
	else if(gas_leak==FAULT_O_GAS2)//����ƿ2й©
	{
		return TGTHT510_1553B_data_TGTHT100[2];//PTt3
	}
	
	else if(gas_leak==FAULT_O_GAS3)//����ƿ3й©
	{
		return TGTHT510_1553B_data_TGTHT100[4];//PTt5
	}
	
	else if(gas_leak==FAULT_F_GAS1)//ȼ��ƿ1й©
	{
		return TGTHT510_1553B_data_TGTHT100[1];//PTt2
	}
	
	else if(gas_leak==FAULT_F_GAS2)//ȼ��ƿ2й©
	{
		return TGTHT510_1553B_data_TGTHT100[3];//PTt4
	}
	
	else if(gas_leak==FAULT_F_GAS3)//ȼ��ƿ3й©
	{
		return TGTHT510_1553B_data_TGTHT100[5];//PTt6
	}
	
	else
	{
		return 0;
	}
	
}



/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--��ƿй©--��©�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
����ƿ1й©����©��
�ɼ�ѹ��PTt1�����30s���ɼ�5�����ڣ��õ�4����ֵ������3����ֵ����0.1MPa�����ϳ�����

����ƿ2й©����©��
�ɼ�ѹ��PTt3�����30s���ɼ�5�����ڣ��õ�4����ֵ������3����ֵ����0.1MPa�����ϳ�����

����ƿ3й©����©��
�ɼ�ѹ��PTt5�����30s���ɼ�5�����ڣ��õ�4����ֵ������3����ֵ����0.1MPa�����ϳ�����

ȼ��ƿ1й©����©��
�ɼ�ѹ��PTt2�����30s���ɼ�5�����ڣ��õ�4����ֵ������3����ֵ����0.1MPa�����ϳ�����

ȼ��ƿ2й©����©��
�ɼ�ѹ��PTt4�����30s���ɼ�5�����ڣ��õ�4����ֵ������3����ֵ����0.1MPa�����ϳ�����

ȼ��ƿ3й©����©��
�ɼ�ѹ��PTt6�����30s���ɼ�5�����ڣ��õ�4����ֵ������3����ֵ����0.1MPa�����ϳ�����
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_gas_leak_big(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//����ƿ1й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(&TGTHT510_fault_push_o_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//����ƿ2й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(&TGTHT510_fault_push_o_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//����ƿ3й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(&TGTHT510_fault_push_o_gas3_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//ȼ��ƿ1й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(&TGTHT510_fault_push_f_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//ȼ��ƿ2й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(&TGTHT510_fault_push_f_gas2_leak,gas_leak);	
	}
	
	else if(gas_leak==FAULT_F_GAS3)//ȼ��ƿ3й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(&TGTHT510_fault_push_f_gas3_leak,gas_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--��ƿй©--��©�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������

-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(fault_TypeDef *p,uint16 gas_leak)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ������һ��
		{
			p->fault_field1.value[0]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://��ʱ30s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ж�30s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ�����ڶ���
		{
			p->fault_field1.value[1]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://��ʱ30s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://�ж�30s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://�ɼ�ѹ����������
		{
			p->fault_field1.value[2]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO8;
			
			break;
		}
		
		case FAULT_STEP_NO8://��ʱ30s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://�ж�30s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://�ɼ�ѹ�������Ĵ�
		{
			p->fault_field1.value[3]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO11;
			
			break;
		}
		
		case FAULT_STEP_NO11://��ʱ30s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://�ж�30s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://�ɼ�ѹ���������
		{
			p->fault_field1.value[4]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO14;
			
			break;
		}
		
		case FAULT_STEP_NO14://����
		{
			if(TGTHT510_faultdiagnosis_push_gas_leak_four_of_three(p->fault_field1.value,FAULT_CONST_PRESSURE_0E1)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
				
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}	
	}
	
}


/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--��ƿй©--С©�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_gas_leak_small(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//����ƿ1й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(&TGTHT510_fault_push_o_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//����ƿ2й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(&TGTHT510_fault_push_o_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//����ƿ3й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(&TGTHT510_fault_push_o_gas3_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//ȼ��ƿ1й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(&TGTHT510_fault_push_f_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//ȼ��ƿ2й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(&TGTHT510_fault_push_f_gas2_leak,gas_leak);	
	}
	
	else if(gas_leak==FAULT_F_GAS3)//ȼ��ƿ3й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(&TGTHT510_fault_push_f_gas3_leak,gas_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--��ƿй©--С©�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(fault_TypeDef *p,uint16 gas_leak)
{
	switch(p->fault_field2.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field2.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ������һ��
		{
			p->fault_field2.value[0]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://��ʱ12min��ʼ
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ж�12min��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_12MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ�����ڶ���
		{
			p->fault_field2.value[1]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://��ʱ12min��ʼ
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://�ж�12min��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_12MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://�ɼ�ѹ����������
		{
			p->fault_field2.value[2]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO8;
			
			break;
		}
		
		case FAULT_STEP_NO8://��ʱ12min��ʼ
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://�ж�12min��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_12MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://�ɼ�ѹ�������Ĵ�
		{
			p->fault_field2.value[3]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO11;
			
			break;
		}
		
		case FAULT_STEP_NO11://��ʱ12min��ʼ
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://�ж�12min��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_12MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://�ɼ�ѹ���������
		{
			p->fault_field2.value[4]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO14;
			
			break;
		}
		
		case FAULT_STEP_NO14://����
		{
			if(TGTHT510_faultdiagnosis_push_gas_leak_four_of_three(p->fault_field2.value,FAULT_CONST_PRESSURE_0E14)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD2);
			}
			
			else
			{
				p->fault_field2.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field2.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}


/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--��ƿй©--����ֵ�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**����������4֡��3ֵ֡С�ڵ���P_min_gas�����жϹ��ϳ���
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_gas_leak_min(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//����ƿ1й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(&TGTHT510_fault_push_o_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//����ƿ2й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(&TGTHT510_fault_push_o_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//����ƿ3й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(&TGTHT510_fault_push_o_gas3_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//ȼ��ƿ1й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(&TGTHT510_fault_push_f_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//ȼ��ƿ2й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(&TGTHT510_fault_push_f_gas2_leak,gas_leak);	
	}
	
	else if(gas_leak==FAULT_F_GAS3)//ȼ��ƿ3й©
	{
		TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(&TGTHT510_fault_push_f_gas3_leak,gas_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}


/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--��ƿй©--����ֵ�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(fault_TypeDef *p,uint16 gas_leak)
{
	switch(p->fault_field3.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field3.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ������һ��
		{
			p->fault_field3.value[0]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://�ɼ�ѹ�����ڶ���
		{
			p->fault_field3.value[1]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ɼ�ѹ����������
		{
			p->fault_field3.value[2]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ�������Ĵ�
		{
			p->fault_field3.value[3]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://����
		{
			if(TGTHT510_faultdiagnosis_push_gas_leak_min_four_of_three(&(p->fault_field3.value[0]),FAULT_CONST_PRESSURE_MIN_GAS)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD3);
			}
			
			else
			{
				p->fault_field3.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field3.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}


/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--���䳬ѹ--��ȡѹ��ֵ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(uint16 tank_overpressure,uint16 n)
{
	if(tank_overpressure==FAULT_O_TANK1)
	{
		if(n==1)
		{
			return TGTHT510_1553B_data_TGTHT100[12];//PTt13
		}
		
		else if(n==2)
		{
			return TGTHT510_1553B_data_TGTHT100[18];//PTt19
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(tank_overpressure==FAULT_O_TANK2)
	{
		if(n==1)
		{
			return TGTHT510_1553B_data_TGTHT100[14];//PTt15
		}
		
		else if(n==2)
		{
			return TGTHT510_1553B_data_TGTHT100[20];//PTt21
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(tank_overpressure==FAULT_O_TANK3)
	{
		if(n==1)
		{
			return TGTHT510_1553B_data_TGTHT100[16];//PTt17
		}
		
		else if(n==2)
		{
			return TGTHT510_1553B_data_TGTHT100[22];//PTt23
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(tank_overpressure==FAULT_F_TANK1)
	{
		if(n==1)
		{
			return TGTHT510_1553B_data_TGTHT100[13];//PTt14
		}
		
		else if(n==2)
		{
			return TGTHT510_1553B_data_TGTHT100[19];//PTt20
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(tank_overpressure==FAULT_F_TANK2)
	{
		if(n==1)
		{
			return TGTHT510_1553B_data_TGTHT100[15];//PTt16
		}
		
		else if(n==2)
		{
			return TGTHT510_1553B_data_TGTHT100[21];//PTt22
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(tank_overpressure==FAULT_F_TANK3)
	{
		if(n==1)
		{
			return TGTHT510_1553B_data_TGTHT100[17];//PTt18
		}
		
		else if(n==2)
		{
			return TGTHT510_1553B_data_TGTHT100[23];//PTt24
		}
		
		else
		{
			return 0;
		}
	}
	
	else
	{
		return 0;
	}
	
}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--���䳬ѹ--��ѹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_tank_overpressure_is_over(uint16 *p,uint16 door_val)
{
	uint16 i,n;
	
	n=0;
	
	for(i=0;i<=6;i=i+2)
	{
		if((p[i]>door_val)||(p[i+1]>door_val))
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;//���ϳ���
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--���䳬ѹ--��ѹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_tank_overpressure(uint16 tank_overpressure)
{
	if(tank_overpressure==FAULT_O_TANK1)//���ϼ��--��1����
	{
		TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(&TGTHT510_fault_push_o_tank1_overpressure,\
		tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_O_TANK2)//���ϼ��--��2����
	{
		TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(&TGTHT510_fault_push_o_tank2_overpressure,\
		tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_O_TANK3)//���ϼ��--��3����
	{
		TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(&TGTHT510_fault_push_o_tank3_overpressure,\
		tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_F_TANK1)//���ϼ��--ȼ1����
	{
		TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(&TGTHT510_fault_push_f_tank1_overpressure,\
		tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_F_TANK2)//���ϼ��--ȼ2����
	{
		TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(&TGTHT510_fault_push_f_tank2_overpressure,\
		tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_F_TANK3)//���ϼ��--ȼ3����
	{
		TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(&TGTHT510_fault_push_f_tank3_overpressure,\
		tank_overpressure);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--���䳬ѹ--��ѹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(fault_TypeDef *p,uint16 tank_overpressure)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ��
		{
			p->fault_field1.value[0]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,1);
			
			p->fault_field1.value[1]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,2);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://�ɼ�ѹ��
		{
			p->fault_field1.value[2]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,1);
			
			p->fault_field1.value[3]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,2);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ɼ�ѹ��
		{
			p->fault_field1.value[4]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,1);
			
			p->fault_field1.value[5]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,2);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ��
		{
			p->fault_field1.value[6]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,1);
			
			p->fault_field1.value[7]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,2);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://����
		{
			if(TGTHT510_faultdiagnosis_push_tank_overpressure_is_over(p->fault_field1.value,FAULT_CONST_PRESSURE_OVER)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--������й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(uint16 valve_leak,uint16 n,uint16 *p)
{
	if(valve_leak==FAULT_B_MAIN_LEAK)//B�����ݷ�����й©
	{
		if(n==1)//�����¶�
		{
			p[0]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[4]);//B1�����¶�
			p[1]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[6]);//B3�����¶�
			p[2]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[8]);//B5�����¶�
			p[3]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[10]);//B7�����¶�
			p[4]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[12]);//B9�����¶�
			p[5]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[14]);//B11�����¶�
			p[6]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[16]);//B13�����¶�
			p[7]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[18]);//B15�����¶�
		}
		
		else if(n==2)//�����¶�
		{
			p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[30]>>4)&0xfffc;//B1�����¶�
			p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_A[31]>>4)&0xfffc;//B3�����¶�
			p[2]=(TGTHT510_1553B_data_TGTHT100_Temper_A[32]>>4)&0xfffc;//B5�����¶�
			p[3]=(TGTHT510_1553B_data_TGTHT100_Temper_A[33]>>4)&0xfffc;//B7�����¶�
			p[4]=(TGTHT510_1553B_data_TGTHT100_Temper_A[34]>>4)&0xfffc;//B9�����¶�
			p[5]=(TGTHT510_1553B_data_TGTHT100_Temper_A[35]>>4)&0xfffc;//B11�����¶�
			p[6]=(TGTHT510_1553B_data_TGTHT100_Temper_A[36]>>4)&0xfffc;//B13�����¶�
			p[7]=(TGTHT510_1553B_data_TGTHT100_Temper_A[37]>>4)&0xfffc;//B15�����¶�
		}
		
		else//��Ч
		{
			p[0]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[1]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[2]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[3]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[4]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[5]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[6]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[7]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		}
	}
	
	else if(valve_leak==FAULT_B_LESS_LEAK)//B�鱸�ݷ�����й©
	{
		if(n==1)//�����¶�
		{
			p[0]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[5]);//B2�����¶�
			p[1]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[7]);//B4�����¶�
			p[2]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[9]);//B6�����¶�
			p[3]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[11]);//B8�����¶�
			p[4]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[13]);//B10�����¶�
			p[5]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[15]);//B12�����¶�
			p[6]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[17]);//B14�����¶�
			p[7]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[19]);//B16�����¶�
		}
		
		else if(n==2)//�����¶�
		{
			p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[38]>>4)&0xfffc;//B2�����¶�
			p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_A[38]<<4)&0x3fff;//B4�����¶�
			p[2]=(TGTHT510_1553B_data_TGTHT100_Temper_A[39]>>4)&0xfffc;//B6�����¶�
			p[3]=(TGTHT510_1553B_data_TGTHT100_Temper_A[39]<<4)&0x3fff;//B8�����¶�
			p[4]=(TGTHT510_1553B_data_TGTHT100_Temper_A[40]>>4)&0xfffc;//B10�����¶�
			p[5]=(TGTHT510_1553B_data_TGTHT100_Temper_A[40]<<4)&0x3fff;//B12�����¶�
			p[6]=(TGTHT510_1553B_data_TGTHT100_Temper_A[41]>>4)&0xfffc;//B14�����¶�
			p[7]=(TGTHT510_1553B_data_TGTHT100_Temper_A[41]<<4)&0x3fff;//B16�����¶�
		}
		
		else//��Ч
		{
			p[0]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[1]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[2]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[3]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[4]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[5]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[6]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[7]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		}
	}
	
	else if(valve_leak==FAULT_C_ALL_LEAK)//C�鷢����й©
	{
		if(n==1)//�����¶�
		{
			p[0]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[20]);//C1�����¶�
			p[1]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[21]);//C2�����¶�
			p[2]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[22]);//C3�����¶�
			p[3]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[23]);//C4�����¶�
			p[4]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[24]);//C5�����¶�
			p[5]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[25]);//C6�����¶�
			p[6]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[7]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		}
		
		else if(n==2)//�����¶�
		{
			p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[42]>>4)&0xfffc;//C1�����¶�
			p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_A[43]>>4)&0xfffc;//C2�����¶�
			p[2]=(TGTHT510_1553B_data_TGTHT100_Temper_A[44]>>4)&0xfffc;//C3�����¶�
			p[3]=(TGTHT510_1553B_data_TGTHT100_Temper_A[45]>>4)&0xfffc;//C4�����¶�
			p[4]=(TGTHT510_1553B_data_TGTHT100_Temper_A[46]>>4)&0xfffc;//C5�����¶�
			p[5]=(TGTHT510_1553B_data_TGTHT100_Temper_A[47]>>4)&0xfffc;//C6�����¶�
			p[6]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[7]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			
		}
		
		else//��Ч
		{
			p[0]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[1]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[2]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[3]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[4]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[5]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[6]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[7]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		}
	}
	
	else if(valve_leak==FAULT_A_MAIN_LEAK)//A�����ݷ�����й©
	{
		if(n==1)//�����¶�
		{
			p[0]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[0]);//A1�����¶�
			p[1]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[2]);//A3�����¶�
			p[2]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[3]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[4]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[5]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[6]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[7]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		}
		
		else if(n==2)//�����¶�
		{
			p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[26]>>4)&0xfffc;//A1�����¶�
			p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_A[28]>>4)&0xfffc;//A3�����¶�
			p[2]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[3]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[4]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[5]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[6]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[7]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		}
		
		else//��Ч
		{
			p[0]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[1]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[2]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[3]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[4]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[5]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[6]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[7]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		}
	}
	
	else if(valve_leak==FAULT_A_LESS_LEAK)//A�鱸�ݷ�����й©
	{
		if(n==1)//�����¶�
		{
			p[0]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[1]);//A2�����¶�
			p[1]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[3]);//A4�����¶�
			p[2]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[3]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[4]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[5]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[6]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[7]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		}
		
		else if(n==2)//�����¶�
		{
			p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[27]>>4)&0xfffc;//A2�����¶�
			p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_A[29]>>4)&0xfffc;//A4�����¶�
			p[2]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[3]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[4]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[5]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[6]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[7]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		}
		
		else//��Ч
		{
			p[0]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[1]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[2]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[3]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[4]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[5]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[6]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
			p[7]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		}
	}
	
	else
	{
		p[0]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		p[1]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		p[2]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		p[3]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		p[4]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		p[5]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		p[6]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
		p[7]=TABLE_MF61_POS_70;//���ֵ��+70���϶�
	}
	
}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--������й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_valve_leak_is_leak(uint16 (*p1)[8],uint16 (*p2)[8])
{
	uint16 i,n,j;
	
	for(i=0;i<=7;i++)
	{
		n=0;
		
		for(j=0;j<=3;j++)
		{
			if(((p1[j][i]>=TABLE_MF61_POS_04)&&(p2[j][i]>=TABLE_MF61_POS_04))&&\
			((p1[j][i]>=TABLE_MF61_NEG_10)||(p2[j][i]>=TABLE_MF61_NEG_10)))
			{
				n++;
			}
		}
		
		if(n>=3)
		{
			return TRUE;
		}
		
	}
	
	return FALSE;
}


/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--������й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_valve_leak(uint16 valve_leak)
{
	if(valve_leak==FAULT_B_MAIN_LEAK)//B�����ݷ�����й©
	{
		TGTHT510_faultdiagnosis_push_valve_leak_dealing(&TGTHT510_fault_push_B_main_valve_leak,valve_leak);
	}
	
	else if(valve_leak==FAULT_B_LESS_LEAK)//B�鱸�ݷ�����й©
	{
		TGTHT510_faultdiagnosis_push_valve_leak_dealing(&TGTHT510_fault_push_B_less_valve_leak,valve_leak);
	}
	
	else if(valve_leak==FAULT_C_ALL_LEAK)//C�鷢����й©
	{
		TGTHT510_faultdiagnosis_push_valve_leak_dealing(&TGTHT510_fault_push_C_all_valve_leak,valve_leak);
	}
	
	else if(valve_leak==FAULT_A_MAIN_LEAK)//A�����ݷ�����й©
	{
		TGTHT510_faultdiagnosis_push_valve_leak_dealing(&TGTHT510_fault_push_A_main_valve_leak,valve_leak);
	}
	
	else if(valve_leak==FAULT_A_LESS_LEAK)//A�鱸�ݷ�����й©
	{
		TGTHT510_faultdiagnosis_push_valve_leak_dealing(&TGTHT510_fault_push_A_less_valve_leak,valve_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--������й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_valve_leak_dealing(fault_valve_leak_TypeDef *p,uint16 valve_leak)
{
	switch(p->step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ��¶�ֵ����һ��
		{
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,1,p->value_fa[0]);
			
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,2,p->value_va[0]);
			
			p->step=FAULT_STEP_NO2;
			
			break;
			
		}
		
		case FAULT_STEP_NO2://�ɼ��¶�ֵ���ڶ���
		{
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,1,p->value_fa[1]);
			
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,2,p->value_va[1]);
			
			p->step=FAULT_STEP_NO3;
			
			break;
			
		}
		
		case FAULT_STEP_NO3://�ɼ��¶�ֵ��������
		{
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,1,p->value_fa[2]);
			
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,2,p->value_va[2]);
			
			p->step=FAULT_STEP_NO4;
			
			break;
			
		}
		
		case FAULT_STEP_NO4://�ɼ��¶�ֵ�����Ĵ�
		{
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,1,p->value_fa[3]);
			
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,2,p->value_va[3]);
			
			p->step=FAULT_STEP_NO5;
			
			break;
			
		}
		
		case FAULT_STEP_NO5://����
		{
			if(TGTHT510_faultdiagnosis_push_valve_leak_is_leak(p->value_fa,p->value_va)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_valve_leak_typedef(p);
			}
			
			else
			{
				p->step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
			
		}
		
		case FAULT_STEP_END:
		{
			p->step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}

	}

}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--��ȡ����λ�ƴ���������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_htt_get(uint16 tank_leak,uint16 n)
{
	uint16 result;
	
	result = 0;
	
	if(tank_leak==FAULT_O_TANK1)//��1����й©
	{
		if(n==1)
		{
			result=TGTHT510_1553B_data_TGTHT100[61];//htt1
		}
		
		else if(n==2)
		{
			result=TGTHT510_1553B_data_TGTHT100[62];//htt2
		}
		
		else if(n==3)
		{
			result=TGTHT510_1553B_data_TGTHT100[63];//htt3
		}
		
		else
		{
			asm("nop;");
		}
	
	}
	
	else if(tank_leak==FAULT_O_TANK2)//��2����й©
	{
		if(n==1)
		{
			result=TGTHT510_1553B_data_TGTHT100[64];//htt4
		}
		
		else if(n==2)
		{
			result=TGTHT510_1553B_data_TGTHT100[65];//htt5
		}
		
		else if(n==3)
		{
			result=TGTHT510_1553B_data_TGTHT100[66];//htt6
		}
		
		else
		{
			asm("nop;");
		}
	}
	
	else if(tank_leak==FAULT_O_TANK3)//��3����й©
	{
		if(n==1)
		{
			result=TGTHT510_1553B_data_TGTHT100[67];//htt7
		}
		
		else if(n==2)
		{
			result=TGTHT510_1553B_data_TGTHT100[68];//htt8
		}
		
		else if(n==3)
		{
			result=TGTHT510_1553B_data_TGTHT100[69];//htt9
		}
		
		else
		{
			asm("nop;");
		}
	}
	
	else if(tank_leak==FAULT_F_TANK1)//ȼ1����й©
	{
		if(n==1)
		{
			result=TGTHT510_1553B_data_TGTHT100[70];//htt10
		}
		
		else if(n==2)
		{
			result=TGTHT510_1553B_data_TGTHT100[71];//htt11
		}
		
		else if(n==3)
		{
			result=TGTHT510_1553B_data_TGTHT100[72];//htt12
		}
		
		else
		{
			asm("nop;");
		}
	}
	
	else if(tank_leak==FAULT_F_TANK2)//ȼ2����й©
	{
		if(n==1)
		{
			result=TGTHT510_1553B_data_TGTHT100[73];//htt13
		}
		
		else if(n==2)
		{
			result=TGTHT510_1553B_data_TGTHT100[74];//htt14
		}
		
		else if(n==3)
		{
			result=TGTHT510_1553B_data_TGTHT100[75];//htt15
		}
		
		else
		{
			asm("nop;");
		}
	}
	
	else if(tank_leak==FAULT_F_TANK3)//ȼ3����й©
	{
		if(n==1)
		{
			result=TGTHT510_1553B_data_TGTHT100[76];//htt16
		}
		
		else if(n==2)
		{
			result=TGTHT510_1553B_data_TGTHT100[77];//htt17
		}
		
		else if(n==3)
		{
			result=TGTHT510_1553B_data_TGTHT100[78];//htt18
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
	
	return result;

}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--�ж������Ƿ�й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_push_tank_leak_is_leak(uint16 (*p)[3])
{
	uint16 i,j;
	uint16 n,k;
	n=0;
	k=0;
	
	for(j=0;j<=2;j++)
	{
		for(i=0;i<=2;i++)
		{
			if((p[i+1][j]>p[i][j])&&((p[i+1][j]-p[i][j])>=FAULT_CONST_HTT_ONE))
			{
				k++;
			}
			
		}
		
		if(k>=2)
		{
			n++;
		}
		
		k=0;
		
	}
	
	if(n>=2)
	{
		return TRUE;//���Ϸ���
	}
	
	else
	{
		return FALSE;//����δ����
	}
	
}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--����й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_tank_leak(uint16 tank_leak)
{
	if(tank_leak==FAULT_O_TANK1)//��1����й©
	{
		TGTHT510_faultdiagnosis_push_tank_leak_dealing(&TGTHT510_fault_push_o_tank1_leak,tank_leak);
	}
	
	else if(tank_leak==FAULT_O_TANK2)//��2����й©
	{
		TGTHT510_faultdiagnosis_push_tank_leak_dealing(&TGTHT510_fault_push_o_tank2_leak,tank_leak);
	}
	
	else if(tank_leak==FAULT_O_TANK3)//��3����й©
	{
		TGTHT510_faultdiagnosis_push_tank_leak_dealing(&TGTHT510_fault_push_o_tank3_leak,tank_leak);
	}
	
	else if(tank_leak==FAULT_F_TANK1)//ȼ1����й©
	{
		TGTHT510_faultdiagnosis_push_tank_leak_dealing(&TGTHT510_fault_push_f_tank1_leak,tank_leak);
	}
	
	else if(tank_leak==FAULT_F_TANK2)//ȼ2����й©
	{
		TGTHT510_faultdiagnosis_push_tank_leak_dealing(&TGTHT510_fault_push_f_tank2_leak,tank_leak);
	}
	
	else if(tank_leak==FAULT_F_TANK3)//ȼ3����й©
	{
		TGTHT510_faultdiagnosis_push_tank_leak_dealing(&TGTHT510_fault_push_f_tank3_leak,tank_leak);
	}
	
	else
	{
		asm("nop;");
	}
}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--����й©--�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_tank_leak_dealing(fault_TypeDef *p,uint16 tank_leak)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�λ�ƴ�����htt����һ��
		{
			p->fault_field1.valve_htt[0][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[0][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[0][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://��ʱ15s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ж�15s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�λ�ƴ�����htt���ڶ���
		{
			p->fault_field1.valve_htt[1][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[1][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[1][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://��ʱ15s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://�ж�15s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://�ɼ�λ�ƴ�����htt��������
		{
			p->fault_field1.valve_htt[2][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[2][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[2][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			p->fault_field1.step=FAULT_STEP_NO8;
			
			break;
		}
		
		case FAULT_STEP_NO8://��ʱ15s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://�ж�15s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://�ɼ�λ�ƴ�����htt�����Ĵ�
		{
			p->fault_field1.valve_htt[3][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[3][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[3][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			p->fault_field1.step=FAULT_STEP_NO11;
			
			break;
		}
		
		case FAULT_STEP_NO11://��ʱ15s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://�ж�15s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://�ɼ�λ�ƴ�����htt�������
		{
			p->fault_field1.valve_htt[4][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[4][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[4][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			p->fault_field1.step=FAULT_STEP_NO14;
			
			break;
		}
		
		case FAULT_STEP_NO14://����
		{
			if(TGTHT510_faultdiagnosis_push_tank_leak_is_leak(p->fault_field1.valve_htt)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
		
		
	}

}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--�������������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_TGTHT530(void)
{
	TGTHT510_faultdiagnosis_supply_TGTHT530_dealing(&TGTHT510_fault_supply_TGTHT530);
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--�������������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_faultdiagnosis_supply_TGTHT530_dealing(fault_TypeDef *p)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://��ȡ�������������״̬�֣���һ��
		{
			p->fault_field1.value[0]=TGTHT510_1553B_data_TGTHT530[7];
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2://��ȡ�������������״̬�֣��ڶ���
		{
			p->fault_field1.value[1]=TGTHT510_1553B_data_TGTHT530[7];
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			//�ݶ�����������޹���Ϊ0x5555���������ģ�����������
			if((p->fault_field1.value[0]!=0x5555)&&(p->fault_field1.value[1]!=0x5555))
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}	
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
	
	}
}


/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--Һ��ģ�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_cooler(uint16 fault_cooler)
{
	if(fault_cooler==FAULT_COOLER_ZZ)//���ϼ��--����Һ������
	{
		TGTHT510_faultdiagnosis_supply_cooler_dealing(&TGTHT510_fault_supply_cooler_zz,fault_cooler);
	}
	
	else if(fault_cooler==FAULT_COOLER_ZB)//���ϼ��--����Һ�䱸��
	{
		TGTHT510_faultdiagnosis_supply_cooler_dealing(&TGTHT510_fault_supply_cooler_zb,fault_cooler);
	}
	
	else if(fault_cooler==FAULT_COOLER_BZ)//���ϼ��--����Һ������
	{
		TGTHT510_faultdiagnosis_supply_cooler_dealing(&TGTHT510_fault_supply_cooler_bz,fault_cooler);
	}
	
	else if(fault_cooler==FAULT_COOLER_BB)//���ϼ��--����Һ�䱸��
	{
		TGTHT510_faultdiagnosis_supply_cooler_dealing(&TGTHT510_fault_supply_cooler_bb,fault_cooler);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--Һ��ģ�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_cooler_get_value(uint16 fault_cooler)
{
	if(fault_cooler==FAULT_COOLER_ZZ)//���ϼ��--����Һ������
	{
		return TGTHT510_1553B_data_TGTHT100[79];
	}
	
	else if(fault_cooler==FAULT_COOLER_ZB)//���ϼ��--����Һ�䱸��
	{
		return TGTHT510_1553B_data_TGTHT100[80];
	}
	
	else if(fault_cooler==FAULT_COOLER_BZ)//���ϼ��--����Һ������
	{
		return TGTHT510_1553B_data_TGTHT100[81];
	}
	
	else if(fault_cooler==FAULT_COOLER_BB)//���ϼ��--����Һ�䱸��
	{
		return TGTHT510_1553B_data_TGTHT100[82];
	}
	
	else
	{
		return 0;
	}
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--Һ��ģ�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_cooler_is_fault(uint16 *p)
{
	uint16 n;
	uint16 i;
	
	n=0;
	for(i=0;i<=3;i++)
	{
		if(p[i]<FAULT_CONST_COOLER)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--Һ��ģ�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_cooler_dealing(fault_TypeDef *p,uint16 fault_cooler)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://��ȡ��ת�٣���һ��
		{
			p->fault_field1.value[0]=TGTHT510_faultdiagnosis_supply_cooler_get_value(fault_cooler);
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2://��ȡ��ת�٣��ڶ���
		{
			p->fault_field1.value[1]=TGTHT510_faultdiagnosis_supply_cooler_get_value(fault_cooler);
			p->fault_field1.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3://��ȡ��ת�٣�������
		{
			p->fault_field1.value[2]=TGTHT510_faultdiagnosis_supply_cooler_get_value(fault_cooler);
			p->fault_field1.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4://��ȡ��ת�٣����Ĵ�
		{
			p->fault_field1.value[3]=TGTHT510_faultdiagnosis_supply_cooler_get_value(fault_cooler);
			p->fault_field1.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5://�ж�
		{
			if(TGTHT510_faultdiagnosis_supply_cooler_is_fault(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}	
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--Һ��ģ��й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_leak_cooler(uint16 leak_cooler)
{
	if(leak_cooler==FAULT_COOLER_Z)
	{
		TGTHT510_faultdiagnosis_supply_leak_cooler_dealing(&TGTHT510_fault_supply_leak_cooler_z,\
		leak_cooler);
	}
	
	else if(leak_cooler==FAULT_COOLER_B)
	{
		TGTHT510_faultdiagnosis_supply_leak_cooler_dealing(&TGTHT510_fault_supply_leak_cooler_b,\
		leak_cooler);
	}
	
	else
	{
		asm("nop;");
	}
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--Һ��ģ��й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_leak_cooler_is_leak(uint16 *p)
{
	uint16 n1,n2;
	uint16 i;
	
	n1=0;
	n2=0;
	
	for(i=0;i<=6;i=i+2)
	{
		if((uint16)(abs(p[i]-p[i+2]))>FAULT_CONST_COOLER_LEAK)//PTb11����PTb12
		{
			n1++;
		}
	}
	
	for(i=1;i<=7;i=i+2)
	{
		if((uint16)(abs(p[i]-p[i+2]))>FAULT_CONST_COOLER_LEAK)//PTb13����PTb14
		{
			n2++;
		}
	}
	
	if((n1>=3)||(n2>=3))
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}



/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--Һ��ģ��й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_leak_cooler_dealing(fault_TypeDef *p,uint16 leak_cooler)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://��ȡ���������ݣ���һ��
		{
			if(leak_cooler==FAULT_COOLER_Z)
			{
				p->fault_field1.value[0]=TGTHT510_1553B_data_TGTHT100[44];//PTb11
				p->fault_field1.value[1]=TGTHT510_1553B_data_TGTHT100[46];//PTb13
			}
			
			else if(leak_cooler==FAULT_COOLER_B)
			{
				p->fault_field1.value[0]=TGTHT510_1553B_data_TGTHT100[45];//PTb12
				p->fault_field1.value[1]=TGTHT510_1553B_data_TGTHT100[47];//PTb14
			}
			
			else
			{
				p->fault_field1.value[0]=0;
				p->fault_field1.value[1]=0;
			}
			
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2://��ʱ15s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ж�15s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://��ȡ���������ݣ��ڶ���
		{
			if(leak_cooler==FAULT_COOLER_Z)
			{
				p->fault_field1.value[2]=TGTHT510_1553B_data_TGTHT100[44];//PTb11
				p->fault_field1.value[3]=TGTHT510_1553B_data_TGTHT100[46];//PTb13
			}
			
			else if(leak_cooler==FAULT_COOLER_B)
			{
				p->fault_field1.value[2]=TGTHT510_1553B_data_TGTHT100[45];//PTb12
				p->fault_field1.value[3]=TGTHT510_1553B_data_TGTHT100[47];//PTb14
			}
			
			else
			{
				p->fault_field1.value[2]=0;
				p->fault_field1.value[3]=0;
			}
			
			p->fault_field1.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5://��ʱ15s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://�ж�15s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://��ȡ���������ݣ�������
		{
			if(leak_cooler==FAULT_COOLER_Z)
			{
				p->fault_field1.value[4]=TGTHT510_1553B_data_TGTHT100[44];//PTb11
				p->fault_field1.value[5]=TGTHT510_1553B_data_TGTHT100[46];//PTb13
			}
			
			else if(leak_cooler==FAULT_COOLER_B)
			{
				p->fault_field1.value[4]=TGTHT510_1553B_data_TGTHT100[45];//PTb12
				p->fault_field1.value[5]=TGTHT510_1553B_data_TGTHT100[47];//PTb14
			}
			
			else
			{
				p->fault_field1.value[4]=0;
				p->fault_field1.value[5]=0;
			}
			
			p->fault_field1.step=FAULT_STEP_NO8;
			break;
		}
		
		case FAULT_STEP_NO8://��ʱ15s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://�ж�15s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://��ȡ���������ݣ����Ĵ�
		{
			if(leak_cooler==FAULT_COOLER_Z)
			{
				p->fault_field1.value[6]=TGTHT510_1553B_data_TGTHT100[44];//PTb11
				p->fault_field1.value[7]=TGTHT510_1553B_data_TGTHT100[46];//PTb13
			}
			
			else if(leak_cooler==FAULT_COOLER_B)
			{
				p->fault_field1.value[6]=TGTHT510_1553B_data_TGTHT100[45];//PTb12
				p->fault_field1.value[7]=TGTHT510_1553B_data_TGTHT100[47];//PTb14
			}
			
			else
			{
				p->fault_field1.value[6]=0;
				p->fault_field1.value[7]=0;
			}
			
			p->fault_field1.step=FAULT_STEP_NO11;
			break;
		}
		
		case FAULT_STEP_NO11://��ʱ15s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://�ж�15s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://��ȡ���������ݣ������
		{
			if(leak_cooler==FAULT_COOLER_Z)
			{
				p->fault_field1.value[8]=TGTHT510_1553B_data_TGTHT100[44];//PTb11
				p->fault_field1.value[9]=TGTHT510_1553B_data_TGTHT100[46];//PTb13
			}
			
			else if(leak_cooler==FAULT_COOLER_B)
			{
				p->fault_field1.value[8]=TGTHT510_1553B_data_TGTHT100[45];//PTb12
				p->fault_field1.value[9]=TGTHT510_1553B_data_TGTHT100[47];//PTb14
			}
			
			else
			{
				p->fault_field1.value[8]=0;
				p->fault_field1.value[9]=0;
			}
			
			p->fault_field1.step=FAULT_STEP_NO14;
			break;
		}
		
		case FAULT_STEP_NO14:
		{
			if(TGTHT510_faultdiagnosis_supply_leak_cooler_is_leak(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
	}
}


/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--ѹ������ѹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_over_compressor(uint16 over_kind)
{
	if(over_kind==FAULT_COMPRESSOR_A_IN_OVER)//ѹ����A��ڳ�ѹ
	{
		TGTHT510_faultdiagnosis_supply_over_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_A_in_over,over_kind);
	}
	
	else if(over_kind==FAULT_COMPRESSOR_B_IN_OVER)//ѹ����B��ڳ�ѹ
	{
		TGTHT510_faultdiagnosis_supply_over_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_B_in_over,over_kind);
	}
	
	else if(over_kind==FAULT_COMPRESSOR_C_IN_OVER)//ѹ����C��ڳ�ѹ
	{
		TGTHT510_faultdiagnosis_supply_over_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_C_in_over,over_kind);
	}
	
	else if(over_kind==FAULT_COMPRESSOR_A_MOTOR_OVER)//ѹ����A���ǻ��ѹ
	{
		TGTHT510_faultdiagnosis_supply_over_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_A_motor_over,over_kind);
	}
	
	else if(over_kind==FAULT_COMPRESSOR_B_MOTOR_OVER)//ѹ����B���ǻ��ѹ
	{
		TGTHT510_faultdiagnosis_supply_over_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_B_motor_over,over_kind);
	}
	
	else if(over_kind==FAULT_COMPRESSOR_C_MOTOR_OVER)//ѹ����C���ǻ��ѹ
	{
		TGTHT510_faultdiagnosis_supply_over_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_C_motor_over,over_kind);
	}
	
	else
	{
		asm("nop;");
	}

}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--ѹ������ѹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(uint16 over_kind,uint16 num)
{
	if(over_kind==FAULT_COMPRESSOR_A_IN_OVER)//ѹ����A��ڳ�ѹ
	{
		if(num==1)
		{
			return TGTHT510_1553B_data_TGTHT100[36];//PTb3
		}
		
		else if(num==2)
		{
			return TGTHT510_1553B_data_TGTHT100[86];//PTb29
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(over_kind==FAULT_COMPRESSOR_B_IN_OVER)//ѹ����B��ڳ�ѹ
	{
		if(num==1)
		{
			return TGTHT510_1553B_data_TGTHT100[37];//PTb4
		}
		
		else if(num==2)
		{
			return TGTHT510_1553B_data_TGTHT100[85];//PTb28
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(over_kind==FAULT_COMPRESSOR_C_IN_OVER)//ѹ����C��ڳ�ѹ
	{
		if(num==1)
		{
			return TGTHT510_1553B_data_TGTHT100[57];//PTb24
		}
		
		else if(num==2)
		{
			return TGTHT510_1553B_data_TGTHT100[56];//PTb23
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(over_kind==FAULT_COMPRESSOR_A_MOTOR_OVER)//ѹ����A���ǻ��ѹ
	{
		return TGTHT510_1553B_data_TGTHT100[86];//PTb29
	}
	
	else if(over_kind==FAULT_COMPRESSOR_B_MOTOR_OVER)//ѹ����B���ǻ��ѹ
	{
		return TGTHT510_1553B_data_TGTHT100[85];//PTb28
	}
	
	else if(over_kind==FAULT_COMPRESSOR_C_MOTOR_OVER)//ѹ����C���ǻ��ѹ
	{
		return TGTHT510_1553B_data_TGTHT100[56];//PTb23
	}
	
	else
	{
		return 0;
	}

}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--ѹ������ѹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_over_compressor_is_over(uint16 *p)
{
	uint16 i;
	uint16 n;
	n=0;
	
	for(i=0;i<=6;i=i+2)
	{
		if(p[i]>FAULT_CONST_COMPRESSOR_OVER)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	n=0;
	
	for(i=1;i<=7;i=i+2)
	{
		if(p[i]>FAULT_CONST_COMPRESSOR_OVER)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	return FALSE;
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--ѹ������ѹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_over_compressor_dealing(fault_TypeDef *p,uint16 over_kind)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ��ֵ����һ��
		{
			p->fault_field1.value[0]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,1);
			
			p->fault_field1.value[1]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,2);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2://�ɼ�ѹ��ֵ���ڶ���
		{
			p->fault_field1.value[2]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,1);
			
			p->fault_field1.value[3]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,2);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3://�ɼ�ѹ��ֵ��������
		{
			p->fault_field1.value[4]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,1);
			
			p->fault_field1.value[5]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,2);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ��ֵ�����Ĵ�
		{
			p->fault_field1.value[6]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,1);
			
			p->fault_field1.value[7]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,2);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(TGTHT510_faultdiagnosis_supply_over_compressor_is_over(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
	}
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--ѹ��������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_hot_compressor(uint16 hot_kind)
{
	if(hot_kind==FAULT_COMPRESSOR_A_HOT)
	{
		TGTHT510_faultdiagnosis_supply_hot_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_A_hot,hot_kind);
	}

	else if(hot_kind==FAULT_COMPRESSOR_B_HOT)
	{
		TGTHT510_faultdiagnosis_supply_hot_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_B_hot,hot_kind);
	}	
	
	else if(hot_kind==FAULT_COMPRESSOR_C_HOT)
	{
		TGTHT510_faultdiagnosis_supply_hot_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_C_hot,hot_kind);
	}	
	
	else
	{
		asm("nop;");
	}
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--ѹ��������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_hot_compressor_get_max(uint16 hot_kind)
{
	uint16 temperature[6];
	uint16 i,j;
	uint16 max;
	
	if(hot_kind==FAULT_COMPRESSOR_A_HOT)
	{
		temperature[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[44]&0xff00)>>4;//ѹ����A�¶�1
		temperature[1]=(TGTHT510_1553B_data_TGTHT100_Temper_B[44]&0x00ff)<<4;//ѹ����A�¶�2
		temperature[2]=(TGTHT510_1553B_data_TGTHT100_Temper_B[45]&0xff00)>>4;//ѹ����A�¶�3
		temperature[3]=(TGTHT510_1553B_data_TGTHT100_Temper_B[45]&0x00ff)<<4;//ѹ����A�¶�4
		temperature[4]=(TGTHT510_1553B_data_TGTHT100_Temper_B[46]&0xff00)>>4;//ѹ����A�¶�5
		temperature[5]=(TGTHT510_1553B_data_TGTHT100_Temper_B[46]&0x00ff)<<4;//ѹ����A�¶�6
	}

	else if(hot_kind==FAULT_COMPRESSOR_B_HOT)
	{
		temperature[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[47]&0xff00)>>4;//ѹ����B�¶�1
		temperature[1]=(TGTHT510_1553B_data_TGTHT100_Temper_B[47]&0x00ff)<<4;//ѹ����B�¶�2
		temperature[2]=(TGTHT510_1553B_data_TGTHT100_Temper_B[48]&0xff00)>>4;//ѹ����B�¶�3
		temperature[3]=(TGTHT510_1553B_data_TGTHT100_Temper_B[48]&0x00ff)<<4;//ѹ����B�¶�4
		temperature[4]=(TGTHT510_1553B_data_TGTHT100_Temper_B[49]&0xff00)>>4;//ѹ����B�¶�5
		temperature[5]=(TGTHT510_1553B_data_TGTHT100_Temper_B[49]&0x00ff)<<4;//ѹ����B�¶�6
	}	
	
	else if(hot_kind==FAULT_COMPRESSOR_C_HOT)
	{
		temperature[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[50]&0xff00)>>4;//ѹ����C�¶�1
		temperature[1]=(TGTHT510_1553B_data_TGTHT100_Temper_B[50]&0x00ff)<<4;//ѹ����C�¶�2
		temperature[2]=(TGTHT510_1553B_data_TGTHT100_Temper_B[51]&0xff00)>>4;//ѹ����C�¶�3
		temperature[3]=(TGTHT510_1553B_data_TGTHT100_Temper_B[51]&0x00ff)<<4;//ѹ����C�¶�4
		temperature[4]=(TGTHT510_1553B_data_TGTHT100_Temper_B[52]&0xff00)>>4;//ѹ����C�¶�5
		temperature[5]=(TGTHT510_1553B_data_TGTHT100_Temper_B[52]&0x00ff)<<4;//ѹ����C�¶�6
	}	
	
	else
	{
		temperature[0]=0;
		temperature[1]=0;
		temperature[2]=0;
		temperature[3]=0;
		temperature[4]=0;
		temperature[5]=0;
	}
	
	max=temperature[0];
	
	for(i=1;i<=5;i++)
	{
		if(temperature[i]>max)
		{
			max=temperature[i];
		}
	}
	
	return max;	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--ѹ��������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_hot_compressor_is_hot(uint16 *p)
{
	uint16 i;
	
	for(i=0;i<=4;i++)
	{
		if(p[i]<FAULT_CONST_COMPRESSOR_HOT)
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--ѹ��������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_hot_compressor_dealing(fault_TypeDef *p,uint16 hot_kind)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ����6���¶�ֵ�����ֵ����һ��
		{
			p->fault_field1.value[0]=\
			TGTHT510_faultdiagnosis_supply_hot_compressor_get_max(hot_kind);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			p->fault_field1.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3://�ɼ�ѹ����6���¶�ֵ�����ֵ���ڶ���
		{
			p->fault_field1.value[1]=\
			TGTHT510_faultdiagnosis_supply_hot_compressor_get_max(hot_kind);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			p->fault_field1.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5://�ɼ�ѹ����6���¶�ֵ�����ֵ��������
		{
			p->fault_field1.value[2]=\
			TGTHT510_faultdiagnosis_supply_hot_compressor_get_max(hot_kind);
			
			p->fault_field1.step=FAULT_STEP_NO6;
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			p->fault_field1.step=FAULT_STEP_NO7;
			break;
		}
		
		case FAULT_STEP_NO7://�ɼ�ѹ����6���¶�ֵ�����ֵ�����Ĵ�
		{
			p->fault_field1.value[3]=\
			TGTHT510_faultdiagnosis_supply_hot_compressor_get_max(hot_kind);
			
			p->fault_field1.step=FAULT_STEP_NO8;
			break;
		}
		
		case FAULT_STEP_NO8:
		{
			p->fault_field1.step=FAULT_STEP_NO9;
			break;
		}
		
		case FAULT_STEP_NO9://�ɼ�ѹ����6���¶�ֵ�����ֵ�������
		{
			p->fault_field1.value[4]=\
			TGTHT510_faultdiagnosis_supply_hot_compressor_get_max(hot_kind);
			
			p->fault_field1.step=FAULT_STEP_NO10;
			break;
		}
		
		case FAULT_STEP_NO10://�жϹ����Ƿ����
		{
			if(TGTHT510_faultdiagnosis_supply_hot_compressor_is_hot(p->fault_field1.value)\
			==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
	}
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--�������䳬ѹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_tank_overpressure(uint16 tank_overpressure)
{
	if(tank_overpressure==FAULT_O_TANK1)//���ϼ��--��1����
	{
		TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(\
		&TGTHT510_fault_supply_o_tank1_overpressure,tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_O_TANK2)//���ϼ��--��2����
	{
		TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(\
		&TGTHT510_fault_supply_o_tank2_overpressure,tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_O_TANK3)//���ϼ��--��3����
	{
		TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(\
		&TGTHT510_fault_supply_o_tank3_overpressure,tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_F_TANK1)//���ϼ��--ȼ1����
	{
		TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(\
		&TGTHT510_fault_supply_f_tank1_overpressure,tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_F_TANK2)//���ϼ��--ȼ2����
	{
		TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(\
		&TGTHT510_fault_supply_f_tank2_overpressure,tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_F_TANK3)//���ϼ��--ȼ3����
	{
		TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(\
		&TGTHT510_fault_supply_f_tank3_overpressure,tank_overpressure);
	}
	
	else
	{
		asm("nop;");
	}
	
}


/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--�������䳬ѹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_tank_overpressure_get(uint16 *p,uint16 tank_overpressure)
{
	if(tank_overpressure==FAULT_O_TANK1)//���ϼ��--��1����
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[12];//PTt13
		p[1]=TGTHT510_1553B_data_TGTHT100[18];//PTt19
		p[2]=TGTHT510_1553B_data_TGTHT100[34];//PTb1
	}
	
	else if(tank_overpressure==FAULT_O_TANK2)//���ϼ��--��2����
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[14];//PTt15
		p[1]=TGTHT510_1553B_data_TGTHT100[20];//PTt21
		p[2]=TGTHT510_1553B_data_TGTHT100[34];//PTb1
	}
	
	else if(tank_overpressure==FAULT_O_TANK3)//���ϼ��--��3����
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[16];//PTt17
		p[1]=TGTHT510_1553B_data_TGTHT100[22];//PTt23
		p[2]=TGTHT510_1553B_data_TGTHT100[34];//PTb1
	}
	
	else if(tank_overpressure==FAULT_F_TANK1)//���ϼ��--ȼ1����
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[13];//PTt14
		p[1]=TGTHT510_1553B_data_TGTHT100[19];//PTt20
		p[2]=TGTHT510_1553B_data_TGTHT100[35];//PTb2
	}
	
	else if(tank_overpressure==FAULT_F_TANK2)//���ϼ��--ȼ2����
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[15];//PTt16
		p[1]=TGTHT510_1553B_data_TGTHT100[21];//PTt22
		p[2]=TGTHT510_1553B_data_TGTHT100[35];//PTb2
	}
	
	else if(tank_overpressure==FAULT_F_TANK3)//���ϼ��--ȼ3����
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[17];//PTt18
		p[1]=TGTHT510_1553B_data_TGTHT100[23];//PTt24
		p[2]=TGTHT510_1553B_data_TGTHT100[35];//PTb2
	}
	
	else
	{
		p[0]=0;
		p[1]=0;
		p[2]=0;
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--�������䳬ѹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�0 1 2 3 4 5 6 7 8 9 10 11
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_tank_overpressure_is_over(uint16 *p)
{
	uint16 n[3];
	uint16 m;
	uint16 i;
	
	n[0]=0;
	n[1]=0;
	n[2]=0;
	for(i=0;i<=9;i=i+3)
	{
		if(p[i]>FAULT_CONST_PRESSURE_OVER)
		{
			n[0]++;
		}
	}
	
	for(i=1;i<=10;i=i+3)
	{
		if(p[i]>FAULT_CONST_PRESSURE_OVER)
		{
			n[1]++;
		}
	}
	
	for(i=2;i<=11;i=i+3)
	{
		if(p[i]>FAULT_CONST_PRESSURE_OVER)
		{
			n[2]++;
		}
	}
	
	m=0;
	for(i=0;i<=2;i++)
	{
		if(n[i]>=3)
		{
			m++;
		}
	}
	
	if(m>=2)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--�������䳬ѹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(fault_TypeDef *p,uint16 tank_overpressure)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ��ֵ����һ��
		{
			TGTHT510_faultdiagnosis_supply_tank_overpressure_get(&p->fault_field1.value[0],\
			tank_overpressure);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2://�ɼ�ѹ��ֵ���ڶ���
		{
			TGTHT510_faultdiagnosis_supply_tank_overpressure_get(&p->fault_field1.value[3],\
			tank_overpressure);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3://�ɼ�ѹ��ֵ��������
		{
			TGTHT510_faultdiagnosis_supply_tank_overpressure_get(&p->fault_field1.value[6],\
			tank_overpressure);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ��ֵ�����Ĵ�
		{
			TGTHT510_faultdiagnosis_supply_tank_overpressure_get(&p->fault_field1.value[9],\
			tank_overpressure);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5://�жϹ����Ƿ���
		{
			if(TGTHT510_faultdiagnosis_supply_tank_overpressure_is_over(p->fault_field1.value)\
			==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
}


/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--ѹ����ĤƬ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_compressor_break(uint16 compressor_break)
{
	if(compressor_break==FAULT_COMPRESSOR_A_BREAK)//ѹ����AĤƬ����
	{
		TGTHT510_faultdiagnosis_supply_compressor_break_dealing(\
		&TGTHT510_fault_supply_compressor_A_break,compressor_break);
	}
	
	else if(compressor_break==FAULT_COMPRESSOR_B_BREAK)//ѹ����BĤƬ����
	{
		TGTHT510_faultdiagnosis_supply_compressor_break_dealing(\
		&TGTHT510_fault_supply_compressor_B_break,compressor_break);
	}
	
	else if(compressor_break==FAULT_COMPRESSOR_C_BREAK)//ѹ����CĤƬ����
	{
		TGTHT510_faultdiagnosis_supply_compressor_break_dealing(\
		&TGTHT510_fault_supply_compressor_C_break,compressor_break);
	}
	
	else
	{
		asm("nop;");
	}
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--ѹ����ĤƬ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_compressor_break_get_pressure(uint16 *p,uint16 compressor_break)
{
	if(compressor_break==FAULT_COMPRESSOR_A_BREAK)//ѹ����AĤƬ����
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[38];//PTb5
		p[1]=TGTHT510_1553B_data_TGTHT100[40];//PTb7
	}
	
	else if(compressor_break==FAULT_COMPRESSOR_B_BREAK)//ѹ����BĤƬ����
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[39];//PTb6
		p[1]=TGTHT510_1553B_data_TGTHT100[41];//PTb8
	}
	
	else if(compressor_break==FAULT_COMPRESSOR_C_BREAK)//ѹ����CĤƬ����
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[58];//PTb5
		p[1]=TGTHT510_1553B_data_TGTHT100[59];//PTb7
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--ѹ����ĤƬ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_compressor_break_is_break(uint16 *p)
{
	uint16 i;
	uint16 n;
	
	n=0;
	for(i=0;i<=6;i=i+2)
	{
		if(p[i]>FAULT_CONST_COMPRESSOR_BREAK)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	n=0;
	for(i=1;i<=7;i=i+2)
	{
		if(p[i]>FAULT_CONST_COMPRESSOR_BREAK)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	return FALSE;
}


/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--ѹ����ĤƬ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_compressor_break_dealing(fault_TypeDef *p,uint16 compressor_break)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ��ֵ����һ��
		{
			TGTHT510_faultdiagnosis_supply_compressor_break_get_pressure(&p->fault_field1.value[0],\
			compressor_break);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2://�ɼ�ѹ��ֵ���ڶ���
		{
			TGTHT510_faultdiagnosis_supply_compressor_break_get_pressure(&p->fault_field1.value[2],\
			compressor_break);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3://�ɼ�ѹ��ֵ��������
		{
			TGTHT510_faultdiagnosis_supply_compressor_break_get_pressure(&p->fault_field1.value[4],\
			compressor_break);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ��ֵ�����Ĵ�
		{
			TGTHT510_faultdiagnosis_supply_compressor_break_get_pressure(&p->fault_field1.value[6],\
			compressor_break);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(TGTHT510_faultdiagnosis_supply_compressor_break_is_break(p->fault_field1.value)\
			==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
	}

}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--��ƿй©--��©�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_gas_leak_big(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//����ƿ1й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(&TGTHT510_fault_supply_o_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//����ƿ2й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(&TGTHT510_fault_supply_o_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//����ƿ3й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(&TGTHT510_fault_supply_o_gas3_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//ȼ��ƿ1й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(&TGTHT510_fault_supply_f_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//ȼ��ƿ2й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(&TGTHT510_fault_supply_f_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS3)//ȼ��ƿ3й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(&TGTHT510_fault_supply_f_gas3_leak,gas_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--��ƿй©--��©�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_gas_leak_big_is_leak(uint16 *p)
{
	uint16 i;
	uint16 n;
	n=0;
	
	for(i=0;i<=3;i++)
	{
		if(p[i]>=p[i+1])
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return FALSE;
	}
	
	else
	{
		return TRUE;
	}
}


/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--��ƿй©--��©�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(fault_TypeDef *p,uint16 gas_leak)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ������һ��
		{
			p->fault_field1.value[0]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://��ʱ30s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ж�30s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ�����ڶ���
		{
			p->fault_field1.value[1]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://��ʱ30s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://�ж�30s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://�ɼ�ѹ����������
		{
			p->fault_field1.value[2]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO8;
			
			break;
		}
		
		case FAULT_STEP_NO8://��ʱ30s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://�ж�30s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://�ɼ�ѹ�������Ĵ�
		{
			p->fault_field1.value[3]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO11;
			
			break;
		}
		
		case FAULT_STEP_NO11://��ʱ30s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://�ж�30s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://�ɼ�ѹ���������
		{
			p->fault_field1.value[4]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO14;
			
			break;
		}
		
		case FAULT_STEP_NO14://����
		{
			if(TGTHT510_faultdiagnosis_push_gas_leak_four_of_three(p->fault_field1.value,FAULT_CONST_PRESSURE_0E1)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}	
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--��ƿй©--С©�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_gas_leak_small(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//����ƿ1й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(&TGTHT510_fault_supply_o_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//����ƿ2й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(&TGTHT510_fault_supply_o_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//����ƿ3й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(&TGTHT510_fault_supply_o_gas3_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//ȼ��ƿ1й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(&TGTHT510_fault_supply_f_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//ȼ��ƿ2й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(&TGTHT510_fault_supply_f_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS3)//ȼ��ƿ3й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(&TGTHT510_fault_supply_f_gas3_leak,gas_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--��ƿй©--С©�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(fault_TypeDef *p,uint16 gas_leak)
{
	switch(p->fault_field2.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field2.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ������һ��
		{
			p->fault_field2.value[0]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://��ʱ20min��ʼ
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ж�20min��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_20MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ�����ڶ���
		{
			p->fault_field2.value[1]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://��ʱ20min��ʼ
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://�ж�20min��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_20MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://�ɼ�ѹ����������
		{
			p->fault_field2.value[2]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO8;
			
			break;
		}
		
		case FAULT_STEP_NO8://��ʱ20min��ʼ
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://�ж�20min��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_20MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://�ɼ�ѹ�������Ĵ�
		{
			p->fault_field2.value[3]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO11;
			
			break;
		}
		
		case FAULT_STEP_NO11://��ʱ20min��ʼ
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://�ж�20min��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_20MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://�ɼ�ѹ���������
		{
			p->fault_field2.value[4]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO14;
			
			break;
		}
		
		case FAULT_STEP_NO14://����
		{
			if(TGTHT510_faultdiagnosis_push_gas_leak_four_of_three(p->fault_field2.value,FAULT_CONST_PRESSURE_0E1)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD2);
			}
			
			else
			{
				p->fault_field2.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field2.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--��ƿй©--����ֵ�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_gas_leak_min(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//����ƿ1й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(&TGTHT510_fault_supply_o_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//����ƿ2й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(&TGTHT510_fault_supply_o_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//����ƿ3й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(&TGTHT510_fault_supply_o_gas3_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//ȼ��ƿ1й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(&TGTHT510_fault_supply_f_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//ȼ��ƿ2й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(&TGTHT510_fault_supply_f_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS3)//ȼ��ƿ3й©
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(&TGTHT510_fault_supply_f_gas3_leak,gas_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--��ƿй©--����ֵ�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(fault_TypeDef *p,uint16 gas_leak)
{
	switch(p->fault_field3.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field3.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ������һ��
		{
			p->fault_field3.value[0]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://�ɼ�ѹ�����ڶ���
		{
			p->fault_field3.value[1]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ɼ�ѹ����������
		{
			p->fault_field3.value[2]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ�������Ĵ�
		{
			p->fault_field3.value[3]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://����
		{
			if(TGTHT510_faultdiagnosis_push_gas_leak_min_four_of_three(p->fault_field3.value,\
			FAULT_CONST_PRESSURE_MIN_GAS)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD3);
			}
			
			else
			{
				p->fault_field3.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field3.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���䲹��Һ·й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_tank_pipe_leak(uint16 tank_leak)
{
	if(tank_leak==FAULT_O_TANK1)//��1���䲹��Һ·й©
	{
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(\
		&TGTHT510_fault_supply_pipe_leak_o_tank1,tank_leak);
	}
	
	else if(tank_leak==FAULT_O_TANK2)//��2���䲹��Һ·й©
	{
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(\
		&TGTHT510_fault_supply_pipe_leak_o_tank2,tank_leak);
	}
	
	else if(tank_leak==FAULT_O_TANK3)//��3���䲹��Һ·й©
	{
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(\
		&TGTHT510_fault_supply_pipe_leak_o_tank3,tank_leak);
	}
	
	else if(tank_leak==FAULT_F_TANK1)//ȼ1���䲹��Һ·й©
	{
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(\
		&TGTHT510_fault_supply_pipe_leak_f_tank1,tank_leak);
	}
	
	else if(tank_leak==FAULT_F_TANK2)//ȼ2���䲹��Һ·й©
	{
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(\
		&TGTHT510_fault_supply_pipe_leak_f_tank2,tank_leak);
	}
	
	else if(tank_leak==FAULT_F_TANK3)//ȼ3���䲹��Һ·й©
	{
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(\
		&TGTHT510_fault_supply_pipe_leak_f_tank3,tank_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���䲹��Һ·й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_tank_pipe_leak_get_pressure(uint16 *p,uint16 tank_leak)
{
	if(tank_leak==FAULT_O_TANK1)//��1���䲹��Һ·й©
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[18];//PTt19
		p[1]=TGTHT510_1553B_data_TGTHT100[12];//PTt13
	}
	
	else if(tank_leak==FAULT_O_TANK2)//��2���䲹��Һ·й©
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[20];//PTt21
		p[1]=TGTHT510_1553B_data_TGTHT100[14];//PTt15
	}
	
	else if(tank_leak==FAULT_O_TANK3)//��3���䲹��Һ·й©
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[22];//PTt23
		p[1]=TGTHT510_1553B_data_TGTHT100[16];//PTt17
	}
	
	else if(tank_leak==FAULT_F_TANK1)//ȼ1���䲹��Һ·й©
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[19];//PTt20
		p[1]=TGTHT510_1553B_data_TGTHT100[13];//PTt14
	}
	
	else if(tank_leak==FAULT_F_TANK2)//ȼ2���䲹��Һ·й©
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[21];//PTt22
		p[1]=TGTHT510_1553B_data_TGTHT100[15];//PTt16
	}
	
	else if(tank_leak==FAULT_F_TANK3)//ȼ3���䲹��Һ·й©
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[23];//PTt24
		p[1]=TGTHT510_1553B_data_TGTHT100[17];//PTt18
	}
	
	else
	{
		p[0]=0;
		p[1]=0;
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���䲹��Һ·й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_tank_pipe_leak_is_leak(uint16 (*p_htt)[3],uint16 *p_pressure)
{
	uint16 n,k,m;
	uint16 i,j;

	n=0;
	
	for(j=0;j<=2;j++)
	{
		k=0;
		for(i=0;i<=4;i++)
		{
			if(p_htt[i][j]<p_htt[i+1][j])
			{
				k++;
			}
			
		}
		
		if(k>=3)
		{
			n++;
		}
	}
	
	m=0;
	for(i=0;i<=8;i=i+2)
	{
		if(((uint16)(abs(p_pressure[i]-p_pressure[i+1])))<FAULT_CONST_PRESSURE_0E2)
		{
			m++;
		}
	}
	
	if((n>=2)&&(m>=3))
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���䲹��Һ·й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(fault_TypeDef *p,uint16 tank_leak)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ����λ�ƣ���һ��
		{
			p->fault_field1.valve_htt[0][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[0][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[0][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			
			TGTHT510_faultdiagnosis_supply_tank_pipe_leak_get_pressure(&p->fault_field1.value[0],tank_leak);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://��ʱ30s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ж�30s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ����λ�ƣ��ڶ���
		{
			p->fault_field1.valve_htt[1][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[1][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[1][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			
			TGTHT510_faultdiagnosis_supply_tank_pipe_leak_get_pressure(&p->fault_field1.value[2],tank_leak);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://��ʱ30s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://�ж�30s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://�ɼ�ѹ����λ�ƣ�������
		{
			p->fault_field1.valve_htt[2][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[2][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[2][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			
			TGTHT510_faultdiagnosis_supply_tank_pipe_leak_get_pressure(&p->fault_field1.value[4],tank_leak);
			
			p->fault_field1.step=FAULT_STEP_NO8;
			
			break;
		}
		
		case FAULT_STEP_NO8://��ʱ30s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://�ж�30s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://�ɼ�ѹ����λ�ƣ����Ĵ�
		{
			p->fault_field1.valve_htt[3][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[3][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[3][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			
			TGTHT510_faultdiagnosis_supply_tank_pipe_leak_get_pressure(&p->fault_field1.value[6],tank_leak);
			
			p->fault_field1.step=FAULT_STEP_NO11;
			
			break;
		}
		
		case FAULT_STEP_NO11://��ʱ30s��ʼ
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://�ж�30s��ʱ�Ƿ�
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://�ɼ�ѹ����λ�ƣ������
		{
			p->fault_field1.valve_htt[4][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[4][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[4][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			
			TGTHT510_faultdiagnosis_supply_tank_pipe_leak_get_pressure(&p->fault_field1.value[8],tank_leak);
			
			p->fault_field1.step=FAULT_STEP_NO14;
			
			break;
		}
		
		case FAULT_STEP_NO14:
		{
			if(TGTHT510_faultdiagnosis_supply_tank_pipe_leak_is_leak(p->fault_field1.valve_htt,\
			p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
	
	}
	
}


/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���������¶��쳣
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_interface_temperature(uint16 interface)
{
	if(interface==FAULT_INTERFACE_O)
	{
		TGTHT510_faultdiagnosis_supply_interface_temperature_dealing(\
		&TGTHT510_fault_supply_interface_o_temperature,interface);
	}
	
	else if(interface==FAULT_INTERFACE_F)
	{
		TGTHT510_faultdiagnosis_supply_interface_temperature_dealing(\
		&TGTHT510_fault_supply_interface_f_temperature,interface);
	}
	
	else
	{
		asm("nop;");
	}
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���������¶��쳣
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_interface_temperature_get(uint16 *p,uint16 interface)
{
	if(interface==FAULT_INTERFACE_O)
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[26]&0xff00)>>4;//������1�¶�
		p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_B[26]&0x00ff)<<4;//����ģ��1��·�¶�
		p[2]=(TGTHT510_1553B_data_TGTHT100_Temper_B[27]&0xff00)>>4;//����ģ��1�����¶�
	}
	
	else if(interface==FAULT_INTERFACE_F)
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[27]&0x00ff)<<4;//������2�¶�
		p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_B[28]&0xff00)>>4;//����ģ��2��·�¶�
		p[2]=(TGTHT510_1553B_data_TGTHT100_Temper_B[28]&0x00ff)<<4;//����ģ��2�����¶�
	}
	
	else
	{
		p[0]=0;
		p[1]=0;
		p[2]=0;
	}
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���������¶��쳣
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_interface_temperature_is_normal(uint16 *p)
{
	uint16 i,j;
	uint16 m,n;
	
	n=0;
	for(i=0;i<=9;i=i+3)
	{
		m=0;
		for(j=i;j<=i+2;j++)
		{
			if(p[j]>TABLE_MF61_NEG_20)
			{
				m++;
			}
		}
		
		if(m>=2)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���������¶��쳣
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_interface_temperature_dealing(fault_TypeDef *p,uint16 interface)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ��¶�ֵ����һ��
		{
			TGTHT510_faultdiagnosis_supply_interface_temperature_get(&p->fault_field1.value[0],interface);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://�ɼ��¶�ֵ���ڶ���
		{
			TGTHT510_faultdiagnosis_supply_interface_temperature_get(&p->fault_field1.value[3],interface);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ɼ��¶�ֵ��������
		{
			TGTHT510_faultdiagnosis_supply_interface_temperature_get(&p->fault_field1.value[6],interface);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ��¶�ֵ�����Ĵ�
		{
			TGTHT510_faultdiagnosis_supply_interface_temperature_get(&p->fault_field1.value[9],interface);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(TGTHT510_faultdiagnosis_supply_interface_temperature_is_normal(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}

	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���ӹ�·��©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_in_leak(uint16 leak_kind)
{
	if(leak_kind==FAULT_IN_LEAK_O_Z)//�������ӹ�·��©
	{
		TGTHT510_faultdiagnosis_supply_in_leak_dealing(&TGTHT510_fault_supply_in_leak_o_z,leak_kind);
	}
	
	else if(leak_kind==FAULT_IN_LEAK_O_B)//�������ӹ�·��©
	{
		TGTHT510_faultdiagnosis_supply_in_leak_dealing(&TGTHT510_fault_supply_in_leak_o_b,leak_kind);
	}
	
	else if(leak_kind==FAULT_IN_LEAK_F_Z)//ȼ�����ӹ�·��©
	{
		TGTHT510_faultdiagnosis_supply_in_leak_dealing(&TGTHT510_fault_supply_in_leak_f_z,leak_kind);
	}
	
	else if(leak_kind==FAULT_IN_LEAK_F_B)//ȼ�����ӹ�·��©
	{
		TGTHT510_faultdiagnosis_supply_in_leak_dealing(&TGTHT510_fault_supply_in_leak_f_b,leak_kind);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���ӹ�·��©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_faultdiagnosis_supply_in_leak_get_pressure(uint16 *p,uint16 leak_kind)
{
	if(leak_kind==FAULT_IN_LEAK_O_Z)//�������ӹ�·��©
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[52];//PTb19
		p[1]=TGTHT510_1553B_data_TGTHT100[54];//PTb21
	}
	
	else if(leak_kind==FAULT_IN_LEAK_O_B)//�������ӹ�·��©
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[48];//PTb15
		p[1]=TGTHT510_1553B_data_TGTHT100[50];//PTb17
	}
	
	else if(leak_kind==FAULT_IN_LEAK_F_Z)//ȼ�����ӹ�·��©
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[53];//PTb20
		p[1]=TGTHT510_1553B_data_TGTHT100[55];//PTb22
	}
	
	else if(leak_kind==FAULT_IN_LEAK_F_B)//ȼ�����ӹ�·��©
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[49];//PTb16
		p[1]=TGTHT510_1553B_data_TGTHT100[51];//PTb18
	}
	
	else
	{
		p[0]=0;
		p[1]=0;
	}
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���ӹ�·��©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_in_leak_is_leak(uint16 *p)
{
	uint16 i;
	uint16 n;
	
	n=0;
	for(i=0;i<=6;i=i+2)
	{
		if((p[i]>=FAULT_CONST_PRESSURE_0E4)&&(p[i+1]>=FAULT_CONST_PRESSURE_0E4))
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���ӹ�·��©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_in_leak_dealing(fault_TypeDef *p,uint16 leak_kind)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ��ֵ����һ��
		{
			TGTHT510_faultdiagnosis_supply_in_leak_get_pressure(&p->fault_field1.value[0],leak_kind);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://�ɼ�ѹ��ֵ���ڶ���
		{
			TGTHT510_faultdiagnosis_supply_in_leak_get_pressure(&p->fault_field1.value[2],leak_kind);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ɼ�ѹ��ֵ��������
		{
			TGTHT510_faultdiagnosis_supply_in_leak_get_pressure(&p->fault_field1.value[4],leak_kind);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ��ֵ�����Ĵ�
		{
			TGTHT510_faultdiagnosis_supply_in_leak_get_pressure(&p->fault_field1.value[6],leak_kind);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(TGTHT510_faultdiagnosis_supply_in_leak_is_leak(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--�����Ͻ����¶��쳣
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_temperature(uint16 temperature_kind)
{
	if(temperature_kind==FAULT_TEMPERATURE_FORE_F1)//ǰ��ȼ1�����Ͻ����¶��쳣
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_fore_f1,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_FORE_F2)//ǰ��ȼ2�����Ͻ����¶��쳣
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_fore_f2,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_FORE_O1)//ǰ����1�����Ͻ����¶��쳣
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_fore_o1,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_FORE_O2)//ǰ����2�����Ͻ����¶��쳣
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_fore_o2,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_F1)//����ȼ1�����Ͻ����¶��쳣
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_back_f1,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_F2)//����ȼ2�����Ͻ����¶��쳣
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_back_f2,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_O1)//������1�����Ͻ����¶��쳣
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_back_o1,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_O2)//������2�����Ͻ����¶��쳣
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_back_o2,\
		temperature_kind);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--�����Ͻ����¶��쳣
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_faultdiagnosis_supply_temperature_get(uint16 *p,uint16 temperature_kind)
{
	if(temperature_kind==FAULT_TEMPERATURE_FORE_F1)//ǰ��ȼ1�����Ͻ����¶��쳣
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[48]&0xff00)>>4;//ǰ��ȼ1�����Ͻ����¶�
		p[1]=0;//VCTHT109�����޸ģ�����
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_FORE_F2)//ǰ��ȼ2�����Ͻ����¶��쳣
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[50]&0xff00)>>4;//ǰ��ȼ2�����Ͻ����¶�
		p[1]=0;//VCTHT110�����޸ģ�����
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_FORE_O1)//ǰ����1�����Ͻ����¶��쳣
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[52]&0xff00)>>4;//ǰ����1�����Ͻ����¶�
		p[1]=0;//VCTHT111�����޸ģ�����
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_FORE_O2)//ǰ����2�����Ͻ����¶��쳣
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[54]&0xff00)>>4;//ǰ����2�����Ͻ����¶�
		p[1]=0;//VCTHT112�����޸ģ�����
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_F1)//����ȼ1�����Ͻ����¶��쳣
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[64]&0xff00)>>4;//����ȼ1�����Ͻ����¶�
		p[1]=0;//VCTHT118�����޸ģ�����
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_F2)//����ȼ2�����Ͻ����¶��쳣
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[0]&0x00ff)<<4;//����ȼ2�����Ͻ����¶�
		p[1]=0;//VCTHT119�����޸ģ�����
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_O1)//������1�����Ͻ����¶��쳣
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[2]&0xff00)>>4;//������1�����Ͻ����¶�
		p[1]=0;//VCTHT146�����޸ģ�����
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_O2)//������2�����Ͻ����¶��쳣
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[3]&0x00ff)<<4;//������2�����Ͻ����¶�
		p[1]=0;//VCTHT147�����޸ģ�����
	}
	
	else
	{
		p[0]=0;
		p[1]=0;
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--�����Ͻ����¶��쳣
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_temperature_is_normal(uint16 *p)
{
	uint16 i;
	uint16 n;
	
	//���޸ģ�����������VCTHT���¶��ж�
	n=0;
	for(i=0;i<=6;i=i+2)
	{
		if(p[i]>TABLE_MF61_NEG_05)//����-5���϶�
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}



/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--�����Ͻ����¶��쳣
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_temperature_dealing(fault_TypeDef *p,uint16 temperature_kind)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ��ֵ����һ��
		{
			TGTHT510_faultdiagnosis_supply_temperature_get(&p->fault_field1.value[0],temperature_kind);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://�ɼ�ѹ��ֵ���ڶ���
		{
			TGTHT510_faultdiagnosis_supply_temperature_get(&p->fault_field1.value[2],temperature_kind);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ɼ�ѹ��ֵ��������
		{
			TGTHT510_faultdiagnosis_supply_temperature_get(&p->fault_field1.value[4],temperature_kind);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ��ֵ�����Ĵ�
		{
			TGTHT510_faultdiagnosis_supply_temperature_get(&p->fault_field1.value[6],temperature_kind);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(TGTHT510_faultdiagnosis_supply_temperature_is_normal(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���俨��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_ka_tank(uint16 ka)
{
	if(ka==FAULT_O_TANK1)//��1���俨��
	{
		TGTHT510_faultdiagnosis_supply_ka_tank_dealing(&TGTHT510_fault_supply_ka_o_tank1,ka);
	}
	
	else if(ka==FAULT_O_TANK2)//��2���俨��
	{
		TGTHT510_faultdiagnosis_supply_ka_tank_dealing(&TGTHT510_fault_supply_ka_o_tank2,ka);
	}
	
	else if(ka==FAULT_O_TANK3)//��3���俨��
	{
		TGTHT510_faultdiagnosis_supply_ka_tank_dealing(&TGTHT510_fault_supply_ka_o_tank3,ka);
	}
	
	else if(ka==FAULT_F_TANK1)//ȼ1���俨��
	{
		TGTHT510_faultdiagnosis_supply_ka_tank_dealing(&TGTHT510_fault_supply_ka_f_tank1,ka);
	}
	
	else if(ka==FAULT_F_TANK2)//ȼ2���俨��
	{
		TGTHT510_faultdiagnosis_supply_ka_tank_dealing(&TGTHT510_fault_supply_ka_f_tank2,ka);
	}
	
	else if(ka==FAULT_F_TANK3)//ȼ3���俨��
	{
		TGTHT510_faultdiagnosis_supply_ka_tank_dealing(&TGTHT510_fault_supply_ka_f_tank3,ka);
	}
	
	else
	{
		asm("nop;");
	}

}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���俨��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_ka_tank_is_ka(uint16 *p)
{
	uint16 i;
	uint16 n;
	
	n=0;
	for(i=0;i<=6;i=i+2)
	{
		if((p[i]>p[i+1])&&((p[i]-p[i+1])>=FAULT_CONST_PRESSURE_0E1))
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���俨��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_ka_tank_get_pressure(uint16 *p,uint16 ka)
{
	if(ka==FAULT_O_TANK1)//��1���俨��
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[18];//PTt19
		p[1]=TGTHT510_1553B_data_TGTHT100[12];//PTt13
	}
	
	else if(ka==FAULT_O_TANK2)//��2���俨��
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[20];//PTt21
		p[1]=TGTHT510_1553B_data_TGTHT100[14];//PTt15
	}
	
	else if(ka==FAULT_O_TANK3)//��3���俨��
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[22];//PTt23
		p[1]=TGTHT510_1553B_data_TGTHT100[16];//PTt17
	}
	
	else if(ka==FAULT_F_TANK1)//ȼ1���俨��
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[19];//PTt20
		p[1]=TGTHT510_1553B_data_TGTHT100[13];//PTt14
	}
	
	else if(ka==FAULT_F_TANK2)//ȼ2���俨��
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[21];//PTt22
		p[1]=TGTHT510_1553B_data_TGTHT100[15];//PTt16
	}
	
	else if(ka==FAULT_F_TANK3)//ȼ3���俨��
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[23];//PTt24
		p[1]=TGTHT510_1553B_data_TGTHT100[17];//PTt18
	}
	
	else
	{
		p[0]=0;
		p[1]=0;
	}
}


/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���俨��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_ka_tank_dealing(fault_TypeDef *p,uint16 ka)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://��ʼ
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://�ɼ�ѹ��ֵ����һ��
		{
			TGTHT510_faultdiagnosis_supply_ka_tank_get_pressure(&p->fault_field1.value[0],ka);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://�ɼ�ѹ��ֵ���ڶ���
		{
			TGTHT510_faultdiagnosis_supply_ka_tank_get_pressure(&p->fault_field1.value[2],ka);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://�ɼ�ѹ��ֵ��������
		{
			TGTHT510_faultdiagnosis_supply_ka_tank_get_pressure(&p->fault_field1.value[4],ka);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://�ɼ�ѹ��ֵ�����Ĵ�
		{
			TGTHT510_faultdiagnosis_supply_ka_tank_get_pressure(&p->fault_field1.value[6],ka);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(TGTHT510_faultdiagnosis_supply_ka_tank_is_ka(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//���¿�ʼ�жϹ���
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}

/******************************************************************************************
**���ƣ����ϴ���ģ��--����ģʽ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdeal_check_is_fault(fault_TypeDef *p)
{
	if(p->result==TRUE)
	{
		fault_deal.step=FAULT_STEP_START;
		p->result=FALSE;
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}

}

/******************************************************************************************
**���ƣ����ϴ���ģ��--����ģʽ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdeal_check_is_fault_valve_leak(fault_valve_leak_TypeDef *p)
{
	if(p->result==TRUE)
	{
		fault_deal.step=FAULT_STEP_START;
		p->result=FALSE;
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}

}

/******************************************************************************************
**���ƣ����ϴ���ģ��--����ģʽ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_check(void)
{
	//�ƽ��ʼ죬����ƿ1й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_gas1_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_O_GAS1;
		return;
	}
	
	//�ƽ��ʼ죬����ƿ2й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_gas2_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_O_GAS2;
		return;
	}
	
	//�ƽ��ʼ죬����ƿ3й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_gas3_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_O_GAS3;
		return;
	}
	
	//�ƽ����ϣ�ȼ1��ƿй©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_gas1_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_F_GAS1;
		return;
	}
	
	//�ƽ����ϣ�ȼ2��ƿй©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_gas2_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_F_GAS2;
		return;
	}
	
	//�ƽ����ϣ�ȼ3��ƿй©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_gas3_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_F_GAS3;
		return;
	}
	
	//�ƽ����ϣ���1���䳬ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_tank1_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_OVER_O_TANK1;
		return;
	}
	
	//�ƽ����ϣ���2���䳬ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_tank2_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_OVER_O_TANK2;
		return;
	}
	
	//�ƽ����ϣ���3���䳬ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_tank3_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_OVER_O_TANK3;
		return;
	}
	
	//�ƽ����ϣ�ȼ1���䳬ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_tank1_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_OVER_F_TANK1;
		return;
	}
	
	//�ƽ����ϣ�ȼ2���䳬ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_tank2_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_OVER_F_TANK2;
		return;
	}
	
	//�ƽ����ϣ�ȼ3���䳬ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_tank3_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_OVER_F_TANK3;
		return;
	}
	
	//�ƽ����ϣ������˿ط��������Ʒ���й©
	if(TGTHT510_faultdeal_check_is_fault_valve_leak(&TGTHT510_fault_push_B_main_valve_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_B_MAIN;
		return;
	}
	
	//�ƽ����ϣ������˿ط��������Ʒ���й©
	if(TGTHT510_faultdeal_check_is_fault_valve_leak(&TGTHT510_fault_push_B_less_valve_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_B_LESS;
		return;
	}
	
	//�ƽ����ϣ�C���˿ط��������Ʒ���й©
	if(TGTHT510_faultdeal_check_is_fault_valve_leak(&TGTHT510_fault_push_C_all_valve_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_C_ALL;
		return;
	}
	
	//�ƽ����ϣ�A�������˿ط��������Ʒ���й©
	if(TGTHT510_faultdeal_check_is_fault_valve_leak(&TGTHT510_fault_push_A_main_valve_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_A_MAIN;
		return;
	}
	
	//�ƽ����ϣ�A�鱸���˿ط��������Ʒ���й©
	if(TGTHT510_faultdeal_check_is_fault_valve_leak(&TGTHT510_fault_push_A_less_valve_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_A_LESS;
		return;
	}
	
	//�ƽ����ϣ���1����й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_tank1_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_O_TANK1;
		return;
	}
	
	//�ƽ����ϣ���2����й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_tank2_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_O_TANK2;
		return;
	}
	
	//�ƽ����ϣ���3����й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_tank3_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_O_TANK3;
		return;
	}
	
	//�ƽ����ϣ�ȼ1����й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_tank1_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_F_TANK1;
		return;
	}
	
	//�ƽ����ϣ�ȼ2����й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_tank2_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_F_TANK2;
		return;
	}
	
	//�ƽ����ϣ�ȼ3����й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_tank3_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_F_TANK3;
		return;
	}
	
	//���ӹ��ϣ��������������
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_TGTHT530)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TGTHT530;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TGTHT530,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�����Һ�����ù���
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_cooler_zz)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COOLER_ZZ;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COOLER_ZZ,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�����Һ�䱸�ù���
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_cooler_zb)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COOLER_ZB;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COOLER_ZB,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�����Һ�����ù���
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_cooler_bz)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COOLER_BZ;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COOLER_BZ,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�����Һ�䱸�ù���
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_cooler_bb)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COOLER_BB;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COOLER_BB,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�����Һ��й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_leak_cooler_z)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_COOLER_Z;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_COOLER_Z,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�����Һ��й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_leak_cooler_b)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_COOLER_B;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_COOLER_B,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ѹ����A��ڳ�ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_A_in_over)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_COMP_A_IN;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_COMP_A_IN,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ѹ����B��ڳ�ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_B_in_over)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_COMP_B_IN;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_COMP_B_IN,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ѹ����C��ڳ�ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_C_in_over)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_COMP_C_IN;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_COMP_C_IN,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ѹ����A���ǻ��ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_A_motor_over)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ѹ����B���ǻ��ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_B_motor_over)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ѹ����C���ǻ��ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_C_motor_over)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ѹ����A����
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_A_hot)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COMP_A_HOT;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COMP_A_HOT,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ѹ����B����
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_B_hot)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COMP_B_HOT;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COMP_B_HOT,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ѹ����C����
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_C_hot)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COMP_C_HOT;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COMP_C_HOT,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ���1�������䳬ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_o_tank1_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_O_TANK1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_O_TANK1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ���2�������䳬ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_o_tank2_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_O_TANK2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_O_TANK2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ���3�������䳬ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_o_tank3_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_O_TANK3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_O_TANK3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ1�������䳬ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_f_tank1_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_F_TANK1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_F_TANK1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ2�������䳬ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_f_tank2_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_F_TANK2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_F_TANK2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ3�������䳬ѹ
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_f_tank3_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_F_TANK3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_F_TANK3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ѹ����AĤƬ����
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_A_break)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COMP_A_BREAK;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COMP_A_BREAK,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ѹ����BĤƬ����
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_B_break)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COMP_B_BREAK;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COMP_B_BREAK,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ѹ����CĤƬ����
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_C_break)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COMP_C_BREAK;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COMP_C_BREAK,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ���1��ƿй©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_o_gas1_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_O_GAS1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_O_GAS1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ���2��ƿй©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_o_gas2_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_O_GAS2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_O_GAS2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ���3��ƿй©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_o_gas3_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_O_GAS3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_O_GAS3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ1��ƿй©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_f_gas1_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_F_GAS1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_F_GAS1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ2��ƿй©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_f_gas2_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_F_GAS2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_F_GAS2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ3��ƿй©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_f_gas3_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_F_GAS3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_F_GAS3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ���1���䲹��Һ·й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_pipe_leak_o_tank1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ���2���䲹��Һ·й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_pipe_leak_o_tank2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ���3���䲹��Һ·й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_pipe_leak_o_tank3)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ1���䲹��Һ·й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_pipe_leak_f_tank1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ2���䲹��Һ·й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_pipe_leak_f_tank2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ3���䲹��Һ·й©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_pipe_leak_f_tank3)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ����������¶��쳣
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_interface_o_temperature)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_INTERFACE_O_TEMP;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_INTERFACE_O_TEMP,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ�������¶��쳣
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_interface_f_temperature)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_INTERFACE_F_TEMP;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_INTERFACE_F_TEMP,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ��������ӹ�·��©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_in_leak_o_z)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_IN_LEAK_O_Z;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_IN_LEAK_O_Z,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ��������ӹ�·��©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_in_leak_o_b)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_IN_LEAK_O_B;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_IN_LEAK_O_B,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ�����ӹ�·��©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_in_leak_f_z)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_IN_LEAK_F_Z;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_IN_LEAK_F_Z,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ�����ӹ�·��©
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_in_leak_f_b)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_IN_LEAK_F_B;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_IN_LEAK_F_B,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ǰ��ȼ1�����Ͻ����¶��쳣
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_fore_f1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ǰ��ȼ2�����Ͻ����¶��쳣
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_fore_f2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ǰ����1�����Ͻ����¶��쳣
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_fore_o1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ǰ����2�����Ͻ����¶��쳣
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_fore_o2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�����ȼ1�����Ͻ����¶��쳣
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_back_f1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�����ȼ2�����Ͻ����¶��쳣
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_back_f2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�������1�����Ͻ����¶��쳣
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_back_o1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�������2�����Ͻ����¶��쳣
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_back_o2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ���1���俨��
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_ka_o_tank1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_KA_O_TANK1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_KA_O_TANK1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ���2���俨��
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_ka_o_tank2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_KA_O_TANK2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_KA_O_TANK2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ���3���俨��
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_ka_o_tank3)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_KA_O_TANK3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_KA_O_TANK3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ1���俨��
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_ka_f_tank1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_KA_F_TANK1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_KA_F_TANK1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ2���俨��
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_ka_f_tank2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_KA_F_TANK2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_KA_F_TANK2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//���ӹ��ϣ�ȼ3���俨��
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_ka_f_tank3)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_KA_F_TANK3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_KA_F_TANK3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	fault_deal.fault_mode=FAULT_MODE_NONE;//�޹���
}


/******************************************************************************************
**���ƣ����ϴ���ģ��--���ϴ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_main(void)
{
	TGTHT510_faultdeal_time_dealing(&fault_deal);
	
	if(fault_deal.fault_mode!=FAULT_MODE_NONE)
	{
		switch(fault_deal.fault_mode)
		{
			case FAULT_MODE_PUSH_LEAK_O_GAS1://�ƽ����ϣ���1��ƿй©
			{
				TGTHT510_faultdeal_push_gas_leak(FAULT_O_GAS1);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_GAS2://�ƽ����ϣ���2��ƿй©
			{
				TGTHT510_faultdeal_push_gas_leak(FAULT_O_GAS2);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_GAS3://�ƽ����ϣ���3��ƿй©
			{
				TGTHT510_faultdeal_push_gas_leak(FAULT_O_GAS3);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_GAS1://�ƽ����ϣ�ȼ1��ƿй©
			{
				TGTHT510_faultdeal_push_gas_leak(FAULT_F_GAS1);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_GAS2://�ƽ����ϣ�ȼ2��ƿй©
			{
				TGTHT510_faultdeal_push_gas_leak(FAULT_F_GAS2);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_GAS3://�ƽ����ϣ�ȼ3��ƿй©
			{
				TGTHT510_faultdeal_push_gas_leak(FAULT_F_GAS3);
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_O_TANK1://�ƽ����ϣ���1���䳬ѹ
			{
				TGTHT510_faultdeal_push_tank_overpressure(FAULT_O_TANK1);
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_O_TANK2://�ƽ����ϣ���2���䳬ѹ
			{
				TGTHT510_faultdeal_push_tank_overpressure(FAULT_O_TANK2);
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_O_TANK3://�ƽ����ϣ���3���䳬ѹ
			{
				TGTHT510_faultdeal_push_tank_overpressure(FAULT_O_TANK3);
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_F_TANK1://�ƽ����ϣ�ȼ1���䳬ѹ
			{
				TGTHT510_faultdeal_push_tank_overpressure(FAULT_F_TANK1);
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_F_TANK2://�ƽ����ϣ�ȼ2���䳬ѹ
			{
				TGTHT510_faultdeal_push_tank_overpressure(FAULT_F_TANK2);
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_F_TANK3://�ƽ����ϣ�ȼ3���䳬ѹ
			{
				TGTHT510_faultdeal_push_tank_overpressure(FAULT_F_TANK3);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_B_MAIN://�ƽ����ϣ������˿ط��������Ʒ���й©
			{
				TGTHT510_faultdeal_push_valve_leak(FAULT_B_MAIN_LEAK);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_B_LESS://�ƽ����ϣ������˿ط��������Ʒ���й©
			{
				TGTHT510_faultdeal_push_valve_leak(FAULT_B_LESS_LEAK);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_C_ALL://�ƽ����ϣ�C���˿ط��������Ʒ���й©
			{
				TGTHT510_faultdeal_push_valve_leak(FAULT_C_ALL_LEAK);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_A_MAIN://�ƽ����ϣ�A�������˿ط��������Ʒ���й©
			{
				TGTHT510_faultdeal_push_valve_leak(FAULT_A_MAIN_LEAK);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_A_LESS://�ƽ����ϣ�A�鱸���˿ط��������Ʒ���й©
			{
				TGTHT510_faultdeal_push_valve_leak(FAULT_A_LESS_LEAK);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_TANK1://�ƽ����ϣ���1����й©
			{
				TGTHT510_faultdeal_push_tank_leak(FAULT_O_TANK1);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_TANK2://�ƽ����ϣ���2����й©
			{
				TGTHT510_faultdeal_push_tank_leak(FAULT_O_TANK2);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_TANK3://�ƽ����ϣ���3����й©
			{
				TGTHT510_faultdeal_push_tank_leak(FAULT_O_TANK3);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_TANK1://�ƽ����ϣ�ȼ1����й©
			{
				TGTHT510_faultdeal_push_tank_leak(FAULT_F_TANK1);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_TANK2://�ƽ����ϣ�ȼ2����й©
			{
				TGTHT510_faultdeal_push_tank_leak(FAULT_F_TANK2);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_TANK3://�ƽ����ϣ�ȼ3����й©
			{
				TGTHT510_faultdeal_push_tank_leak(FAULT_F_TANK3);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TGTHT530://���ӹ��ϣ��������������
			{
				//�����䣡������
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_ZZ://���ӹ��ϣ�����Һ�����ù���
			{
				TGTHT510_faultdeal_supply_cooler(FAULT_COOLER_ZZ);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_ZB://���ӹ��ϣ�����Һ�䱸�ù���
			{
				TGTHT510_faultdeal_supply_cooler(FAULT_COOLER_ZB);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_BZ://���ӹ��ϣ�����Һ�����ù���
			{
				TGTHT510_faultdeal_supply_cooler(FAULT_COOLER_BZ);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_BB://���ӹ��ϣ�����Һ�䱸�ù���
			{
				TGTHT510_faultdeal_supply_cooler(FAULT_COOLER_BB);
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_COOLER_Z://���ӹ��ϣ�����Һ��й©
			{
				TGTHT510_faultdeal_supply_leak_cooler(FAULT_COOLER_Z);
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_COOLER_B://���ӹ��ϣ�����Һ��й©
			{
				TGTHT510_faultdeal_supply_leak_cooler(FAULT_COOLER_B);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_A_IN://���ӹ��ϣ�ѹ����A��ڳ�ѹ
			{
				TGTHT510_faultdeal_supply_over_compressor(FAULT_COMPRESSOR_A_IN_OVER);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_B_IN://���ӹ��ϣ�ѹ����B��ڳ�ѹ
			{
				TGTHT510_faultdeal_supply_over_compressor(FAULT_COMPRESSOR_B_IN_OVER);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_C_IN://���ӹ��ϣ�ѹ����C��ڳ�ѹ
			{
				TGTHT510_faultdeal_supply_over_compressor(FAULT_COMPRESSOR_C_IN_OVER);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR://���ӹ��ϣ�ѹ����A���ǻ��ѹ
			{
				TGTHT510_faultdeal_supply_over_compressor(FAULT_COMPRESSOR_A_MOTOR_OVER);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR://���ӹ��ϣ�ѹ����B���ǻ��ѹ
			{
				TGTHT510_faultdeal_supply_over_compressor(FAULT_COMPRESSOR_B_MOTOR_OVER);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR://���ӹ��ϣ�ѹ����C���ǻ��ѹ
			{
				TGTHT510_faultdeal_supply_over_compressor(FAULT_COMPRESSOR_C_MOTOR_OVER);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_A_HOT://���ӹ��ϣ�ѹ����A����
			{
				TGTHT510_faultdeal_supply_hot_compressor(FAULT_COMPRESSOR_A_HOT);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_B_HOT://���ӹ��ϣ�ѹ����B����
			{
				TGTHT510_faultdeal_supply_hot_compressor(FAULT_COMPRESSOR_B_HOT);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_C_HOT://���ӹ��ϣ�ѹ����C����
			{
				TGTHT510_faultdeal_supply_hot_compressor(FAULT_COMPRESSOR_C_HOT);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_O_TANK1://���ӹ��ϣ���1�������䳬ѹ
			{
				TGTHT510_faultdeal_supply_tank_overpressure(FAULT_O_TANK1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_O_TANK2://���ӹ��ϣ���2�������䳬ѹ
			{
				TGTHT510_faultdeal_supply_tank_overpressure(FAULT_O_TANK2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_O_TANK3://���ӹ��ϣ���3�������䳬ѹ
			{
				TGTHT510_faultdeal_supply_tank_overpressure(FAULT_O_TANK3);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_F_TANK1://���ӹ��ϣ�ȼ1�������䳬ѹ
			{
				TGTHT510_faultdeal_supply_tank_overpressure(FAULT_F_TANK1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_F_TANK2://���ӹ��ϣ�ȼ2�������䳬ѹ
			{
				TGTHT510_faultdeal_supply_tank_overpressure(FAULT_F_TANK2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_F_TANK3://���ӹ��ϣ�ȼ3�������䳬ѹ
			{
				TGTHT510_faultdeal_supply_tank_overpressure(FAULT_F_TANK3);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_A_BREAK://���ӹ��ϣ�ѹ����AĤƬ����
			{
				TGTHT510_faultdeal_supply_compressor_break(FAULT_COMPRESSOR_A_BREAK);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_B_BREAK://���ӹ��ϣ�ѹ����BĤƬ����
			{
				TGTHT510_faultdeal_supply_compressor_break(FAULT_COMPRESSOR_B_BREAK);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_C_BREAK://���ӹ��ϣ�ѹ����CĤƬ����
			{
				TGTHT510_faultdeal_supply_compressor_break(FAULT_COMPRESSOR_C_BREAK);
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_O_GAS1://���ӹ��ϣ���1��ƿй©
			{
				TGTHT510_faultdeal_supply_gas_leak();
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_O_GAS2://���ӹ��ϣ���2��ƿй©
			{
				TGTHT510_faultdeal_supply_gas_leak();
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_O_GAS3://���ӹ��ϣ���3��ƿй©
			{
				TGTHT510_faultdeal_supply_gas_leak();
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_F_GAS1://���ӹ��ϣ�ȼ1��ƿй©
			{
				TGTHT510_faultdeal_supply_gas_leak();
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_F_GAS2://���ӹ��ϣ�ȼ2��ƿй©
			{
				TGTHT510_faultdeal_supply_gas_leak();
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_F_GAS3://���ӹ��ϣ�ȼ3��ƿй©
			{
				TGTHT510_faultdeal_supply_gas_leak();
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1://���ӹ��ϣ���1���䲹��Һ·й©
			{
				TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2://���ӹ��ϣ���2���䲹��Һ·й©
			{
				TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3://���ӹ��ϣ���3���䲹��Һ·й©
			{
				TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK3);
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1://���ӹ��ϣ�ȼ1���䲹��Һ·й©
			{
				TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2://���ӹ��ϣ�ȼ2���䲹��Һ·й©
			{
				TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3://���ӹ��ϣ�ȼ3���䲹��Һ·й©
			{
				TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK3);
				break;
			}
			
			case FAULT_MODE_SUPPLY_INTERFACE_O_TEMP://���ӹ��ϣ����������¶��쳣
			{
				TGTHT510_faultdeal_supply_interface_temperature(FAULT_INTERFACE_O);
				break;
			}
			
			case FAULT_MODE_SUPPLY_INTERFACE_F_TEMP://���ӹ��ϣ�ȼ�������¶��쳣
			{
				TGTHT510_faultdeal_supply_interface_temperature(FAULT_INTERFACE_F);
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_O_Z://���ӹ��ϣ��������ӹ�·��©
			{
				TGTHT510_faultdeal_supply_in_leak(FAULT_IN_LEAK_O_Z);
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_O_B://���ӹ��ϣ��������ӹ�·��©
			{
				TGTHT510_faultdeal_supply_in_leak(FAULT_IN_LEAK_O_B);
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_F_Z://���ӹ��ϣ�ȼ�����ӹ�·��©
			{
				TGTHT510_faultdeal_supply_in_leak(FAULT_IN_LEAK_F_Z);
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_F_B://���ӹ��ϣ�ȼ�����ӹ�·��©
			{
				TGTHT510_faultdeal_supply_in_leak(FAULT_IN_LEAK_F_B);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1://���ӹ��ϣ�ǰ��ȼ1�����Ͻ����¶��쳣
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_FORE_F1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2://���ӹ��ϣ�ǰ��ȼ2�����Ͻ����¶��쳣
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_FORE_F2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1://���ӹ��ϣ�ǰ����1�����Ͻ����¶��쳣
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_FORE_O1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2://���ӹ��ϣ�ǰ����2�����Ͻ����¶��쳣
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_FORE_O2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1://���ӹ��ϣ�����ȼ1�����Ͻ����¶��쳣
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_BACK_F1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2://���ӹ��ϣ�����ȼ2�����Ͻ����¶��쳣
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_BACK_F2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1://���ӹ��ϣ�������1�����Ͻ����¶��쳣
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_BACK_O1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2://���ӹ��ϣ�������2�����Ͻ����¶��쳣
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_BACK_O2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_O_TANK1://���ӹ��ϣ���1���俨��
			{
				TGTHT510_faultdeal_supply_ka_tank(FAULT_O_TANK1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_O_TANK2://���ӹ��ϣ���2���俨��
			{
				TGTHT510_faultdeal_supply_ka_tank(FAULT_O_TANK2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_O_TANK3://���ӹ��ϣ���3���俨��
			{
				TGTHT510_faultdeal_supply_ka_tank(FAULT_O_TANK3);
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_F_TANK1://���ӹ��ϣ�ȼ1���俨��
			{
				TGTHT510_faultdeal_supply_ka_tank(FAULT_F_TANK1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_F_TANK2://���ӹ��ϣ�ȼ2���俨��
			{
				TGTHT510_faultdeal_supply_ka_tank(FAULT_F_TANK2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_F_TANK3://���ӹ��ϣ�ȼ3���俨��
			{
				TGTHT510_faultdeal_supply_ka_tank(FAULT_F_TANK3);
				break;
			}
			
			default:
			{
				fault_deal.fault_mode=FAULT_MODE_NONE;
				break;
			}
			
		}

	}
	
	else
	{
		TGTHT510_faultdeal_check();//����Ѳ��
	}
	
}


/******************************************************************************************
**���ƣ����ϴ���ģ��ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_time_start(fault_deal_TypeDef *f)
{
	f->time_flag=TRUE;
	f->time_count=0x0000;
}

/******************************************************************************************
**���ƣ����ϴ���ģ��ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_time_end(fault_deal_TypeDef *f)
{
	f->time_flag=FALSE;
}

/******************************************************************************************
**���ƣ����ϴ���ģ��ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_time_dealing(fault_deal_TypeDef *f)
{
	if(f->time_flag==TRUE)
	{
		f->time_count++;
	}
	
	else
	{
		f->time_count=0;
	}
	
}

/******************************************************************************************
**���ƣ����ϴ���ģ��ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdeal_time_is_get(fault_deal_TypeDef *f,uint16 val)
{
	if(f->time_count>=val)
	{
		TGTHT510_faultdeal_time_end(f);
		
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**���ƣ����ϴ���ģ��--���ص�ǰ������ѹ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdeal_which_compressor_working(void)
{
	if(compressor_state.compressor_A_state==COMPRESSOR_RUN)
	{
		return FAULT_COMPRESSOR_A;
	}
	
	else if(compressor_state.compressor_B_state==COMPRESSOR_RUN)
	{
		return FAULT_COMPRESSOR_B;
	}
	
	else if(compressor_state.compressor_C_state==COMPRESSOR_RUN)
	{
		return FAULT_COMPRESSOR_C;
	}
	
	else
	{
		return FAULT_COMPRESSOR_N;
	}
	
	/*
	���ص�ǰ������ѹ������
	FAULT_COMPRESSOR_A
	FAULT_COMPRESSOR_B
	FAULT_COMPRESSOR_C
	FAULT_COMPRESSOR_N
	
	���޸ģ�����
	*/
	
}

/******************************************************************************************
**���ƣ��ƽ�������ģ��--ѹ����ͣ����������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������ѹ����ͣ���������������TRUE��δ�����򷵻�FALSE
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_compressor_stop_dealing(uint16 compressor,uint16 valve_number)
{
	if(compressor==FAULT_COMPRESSOR_A)//ѹ����A��
	{
		switch(valve_number)
		{
			case 1://LVb7��
			{
				TGTHT510_faultdeal_lvb_set(LVb7G);
				break;
			}
			
			case 2://LVb9��
			{
				TGTHT510_faultdeal_lvb_set(LVb9G);
				break;
			}
			
			case 3://LVb11��
			{
				TGTHT510_faultdeal_lvb_set(LVb11G);
				break;
			}
			
			case 4://LVb17��
			{
				TGTHT510_faultdeal_lvb_set(LVb17G);
				break;
			}
			
			case 5://LVb19��
			{
				TGTHT510_faultdeal_lvb_set(LVb19G);
				break;
			}
			
			case 6://LVb21��
			{
				TGTHT510_faultdeal_lvb_set(LVb21K);
				break;
			}
			
			case 7://LVb21��
			{
				TGTHT510_faultdeal_lvb_set(LVb21G);
				break;
			}
			
			case 8://LVb13��
			{
				TGTHT510_faultdeal_lvb_set(LVb13G);
				break;
			}
			
			case 9://LVb15��
			{
				TGTHT510_faultdeal_lvb_set(LVb15G);
				break;
			}
			
			case 10://LVb1��
			{
				TGTHT510_faultdeal_lvb_set(LVb1G);
				break;
			}
			
			case 11://LVb3��
			{
				TGTHT510_faultdeal_lvb_set(LVb3G);
				break;
			}
			
			case 12://LVb5��
			{
				TGTHT510_faultdeal_lvb_set(LVb5G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
	else if(compressor==FAULT_COMPRESSOR_B)//ѹ����B��
	{
		switch(valve_number)
		{
			case 1://LVb8��
			{
				TGTHT510_faultdeal_lvb_set(LVb8G);
				break;
			}
			
			case 2://LVb10��
			{
				TGTHT510_faultdeal_lvb_set(LVb10G);
				break;
			}
			
			case 3://LVb12��
			{
				TGTHT510_faultdeal_lvb_set(LVb12G);
				break;
			}
			
			case 4://LVb18��
			{
				TGTHT510_faultdeal_lvb_set(LVb18G);
				break;
			}
			
			case 5://LVb20��
			{
				TGTHT510_faultdeal_lvb_set(LVb20G);
				break;
			}
			
			case 6://LVb22��
			{
				TGTHT510_faultdeal_lvb_set(LVb22K);
				break;
			}
			
			case 7://LVb22��
			{
				TGTHT510_faultdeal_lvb_set(LVb22G);
				break;
			}
			
			case 8://LVb14��
			{
				TGTHT510_faultdeal_lvb_set(LVb14G);
				break;
			}
			
			case 9://LVb16��
			{
				TGTHT510_faultdeal_lvb_set(LVb16G);
				break;
			}
			
			case 10://LVb2��
			{
				TGTHT510_faultdeal_lvb_set(LVb2G);
				break;
			}
			
			case 11://LVb4��
			{
				TGTHT510_faultdeal_lvb_set(LVb4G);
				break;
			}
			
			case 12://LVb6��
			{
				TGTHT510_faultdeal_lvb_set(LVb6G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
		
	}
	
	else if(compressor==FAULT_COMPRESSOR_C)//ѹ����C��
	{
		if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
		{
			switch(valve_number)
			{
				case 1://LVb8��
				{
					TGTHT510_faultdeal_lvb_set(LVb8G);
					break;
				}
				
				case 2://LVb10��
				{
					TGTHT510_faultdeal_lvb_set(LVb10G);
					break;
				}
				
				case 3://LVb12��
				{
					TGTHT510_faultdeal_lvb_set(LVb12G);
					break;
				}
				
				case 4://LVb25��
				{
					TGTHT510_faultdeal_lvb_set(LVb25G);
					break;
				}
				
				case 5://LVb26��
				{
					TGTHT510_faultdeal_lvb_set(LVb26G);
					break;
				}
				
				case 6://LVb87��
				{
					TGTHT510_faultdeal_lvb_set(LVb87K);
					break;
				}
				
				case 7://LVb87��
				{
					TGTHT510_faultdeal_lvb_set(LVb87G);
					break;
				}
				
				case 8://LVb23��
				{
					TGTHT510_faultdeal_lvb_set(LVb23G);
					break;
				}
				
				case 9://LVb24��
				{
					TGTHT510_faultdeal_lvb_set(LVb24G);
					break;
				}
				
				case 10://LVb2��
				{
					TGTHT510_faultdeal_lvb_set(LVb2G);
					break;
				}
				
				case 11://LVb4��
				{
					TGTHT510_faultdeal_lvb_set(LVb4G);
					break;
				}
				
				case 12://LVb6��
				{
					TGTHT510_faultdeal_lvb_set(LVb6G);
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
		}
		
		else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
		{
			switch(valve_number)
			{
				case 1://LVb7��
				{
					TGTHT510_faultdeal_lvb_set(LVb7G);
					break;
				}
				
				case 2://LVb9��
				{
					TGTHT510_faultdeal_lvb_set(LVb9G);
					break;
				}
				
				case 3://LVb11��
				{
					TGTHT510_faultdeal_lvb_set(LVb11G);
					break;
				}
				
				case 4://LVb25��
				{
					TGTHT510_faultdeal_lvb_set(LVb25G);
					break;
				}
				
				case 5://LVb26��
				{
					TGTHT510_faultdeal_lvb_set(LVb26G);
					break;
				}
				
				case 6://LVb87��
				{
					TGTHT510_faultdeal_lvb_set(LVb87K);
					break;
				}
				
				case 7://LVb87��
				{
					TGTHT510_faultdeal_lvb_set(LVb87G);
					break;
				}
				
				case 8://LVb23��
				{
					TGTHT510_faultdeal_lvb_set(LVb23G);
					break;
				}
				
				case 9://LVb24��
				{
					TGTHT510_faultdeal_lvb_set(LVb24G);
					break;
				}
				
				case 10://LVb1��
				{
					TGTHT510_faultdeal_lvb_set(LVb1G);
					break;
				}
				
				case 11://LVb3��
				{
					TGTHT510_faultdeal_lvb_set(LVb3G);
					break;
				}
				
				case 12://LVb5��
				{
					TGTHT510_faultdeal_lvb_set(LVb5G);
					break;
				}
				
				default:
				{
					break;
				}
				
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
**���ƣ��ƽ�������ģ��--ѹ����ͣ����������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������ѹ����ͣ���������������TRUE��δ�����򷵻�FALSE
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_compressor_stop_equment_command(uint16 compressor)
{
	if(compressor==FAULT_COMPRESSOR_A)//ѹ����A��
	{
		TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_A_STOP);
	}
	
	else if(compressor==FAULT_COMPRESSOR_B)//ѹ����B��
	{
		TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_B_STOP);
	}
	
	else if(compressor==FAULT_COMPRESSOR_C)//ѹ����C��
	{
		TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_C_STOP);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ��ƽ�������ģ��--ѹ����ͣ����������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������ѹ����ͣ���������������TRUE��δ�����򷵻�FALSE
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_faultdeal_compressor_stop(uint16 compressor)
{
	switch(fault_deal.compressor_step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.compressor_step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,1);
			fault_deal.compressor_step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,2);
			fault_deal.compressor_step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,3);
			fault_deal.compressor_step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,4);
			fault_deal.compressor_step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,5);
			fault_deal.compressor_step=FAULT_STEP_NO6;
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,6);
			fault_deal.compressor_step=FAULT_STEP_NO7;
			break;
		}
		
		case FAULT_STEP_NO7://�豸����ָ�ѹ�����ػ�
		{
			TGTHT510_faultdeal_compressor_stop_equment_command(compressor);
			fault_deal.compressor_step=FAULT_STEP_NO8;
			break;
		}
		
		case FAULT_STEP_NO8://��ʼ��ʱ�ȴ�
		{
			TGTHT510_faultdeal_time_start(&fault_deal);
			fault_deal.compressor_step=FAULT_STEP_NO9;
			break;
		}
		
		case FAULT_STEP_NO9://��ʱ�ȴ�1min
		{
			if(TGTHT510_faultdeal_time_is_get(&fault_deal,CONST_TIME_1MIN)==TRUE)
			{
				fault_deal.compressor_step=FAULT_STEP_NO10;
			}
			break;
		}
		
		case FAULT_STEP_NO10:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,7);
			fault_deal.compressor_step=FAULT_STEP_NO11;
			break;
		}
		
		case FAULT_STEP_NO11:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,8);
			fault_deal.compressor_step=FAULT_STEP_NO12;
			break;
		}
		
		case FAULT_STEP_NO12:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,9);
			fault_deal.compressor_step=FAULT_STEP_NO13;
			break;
		}
		
		case FAULT_STEP_NO13:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,10);
			fault_deal.compressor_step=FAULT_STEP_NO14;
			break;
		}
		
		case FAULT_STEP_NO14:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,11);
			fault_deal.compressor_step=FAULT_STEP_NO15;
			break;
		}
		
		case FAULT_STEP_NO15:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,12);
			fault_deal.compressor_step=FAULT_STEP_END;
			break;
		}
		
		case FAULT_STEP_END:
		{
			fault_deal.compressor_step=FAULT_STEP_NONE;
			
			return TRUE;//�������н���������TRUE
			
			break;
		}
		
		default:
		{
			return TRUE;//�������н���������TRUE
			break;
		}
		
	}
	
	return FALSE;//��������δ����������FALSE
}




/******************************************************************************************
**���ƣ��ƽ����ϴ���ģ��--��ƿй©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_push_gas_leak(uint16 gas_leak)
{
	//���ö�Ӧ�ĳ������ң�����Ϊ�쳣״̬�������ܴ���
	
	if(gas_leak==FAULT_O_GAS1)//����ƿ1й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_O_GAS1,FAULT_STATE_ABNORMAL);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//����ƿ2й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_O_GAS2,FAULT_STATE_ABNORMAL);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//����ƿ3й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_O_GAS3,FAULT_STATE_ABNORMAL);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//ȼ��ƿ1й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_F_GAS1,FAULT_STATE_ABNORMAL);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//ȼ��ƿ2й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_F_GAS2,FAULT_STATE_ABNORMAL);	
	}
	
	else if(gas_leak==FAULT_F_GAS3)//ȼ��ƿ3й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_F_GAS3,FAULT_STATE_ABNORMAL);
	}
	
	else
	{
		asm("nop;");
	}
	
	fault_deal.fault_mode=FAULT_MODE_NONE;
	
	fault_deal.step=FAULT_STEP_NONE;
}

/******************************************************************************************
**���ƣ��ƽ����ϴ���ģ��--���䳬ѹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_push_tank_overpressure(uint16 tank_overpressure)
{
	if(tank_overpressure==FAULT_O_TANK1)//���ϼ��--��1����
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_OVER_O_TANK1,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_overpressure==FAULT_O_TANK2)//���ϼ��--��2����
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_OVER_O_TANK2,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_overpressure==FAULT_O_TANK3)//���ϼ��--��3����
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_OVER_O_TANK3,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_overpressure==FAULT_F_TANK1)//���ϼ��--ȼ1����
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_OVER_F_TANK1,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_overpressure==FAULT_F_TANK2)//���ϼ��--ȼ2����
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_OVER_F_TANK2,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_overpressure==FAULT_F_TANK3)//���ϼ��--ȼ3����
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_OVER_F_TANK3,FAULT_STATE_ABNORMAL);
	}
	
	else
	{
		asm("nop;");
	}
	
	fault_deal.fault_mode=FAULT_MODE_NONE;
	
	fault_deal.step=FAULT_STEP_NONE;
	
}

/******************************************************************************************
**���ƣ��ƽ����ϼ��ģ��--������й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_push_valve_leak(uint16 valve_leak)
{
	if(valve_leak==FAULT_B_MAIN_LEAK)//B�����ݷ�����й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_B_MAIN,FAULT_STATE_ABNORMAL);
	}
	
	else if(valve_leak==FAULT_B_LESS_LEAK)//B�鱸�ݷ�����й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_B_LESS,FAULT_STATE_ABNORMAL);
	}
	
	else if(valve_leak==FAULT_C_ALL_LEAK)//C�鷢����й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_C_ALL,FAULT_STATE_ABNORMAL);
	}
	
	else if(valve_leak==FAULT_A_MAIN_LEAK)//A�����ݷ�����й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_A_MAIN,FAULT_STATE_ABNORMAL);
	}
	
	else if(valve_leak==FAULT_A_LESS_LEAK)//A�鱸�ݷ�����й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_A_LESS,FAULT_STATE_ABNORMAL);
	}
	
	else
	{
		asm("nop;");
	}
	
	fault_deal.fault_mode=FAULT_MODE_NONE;
	
	fault_deal.step=FAULT_STEP_NONE;
	
}

/******************************************************************************************
**���ƣ��ƽ�������ģ��--����й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_push_tank_leak(uint16 tank_leak)
{
	if(tank_leak==FAULT_O_TANK1)//��1����й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_O_TANK1,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_leak==FAULT_O_TANK2)//��2����й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_O_TANK2,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_leak==FAULT_O_TANK3)//��3����й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_O_TANK3,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_leak==FAULT_F_TANK1)//ȼ1����й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_F_TANK1,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_leak==FAULT_F_TANK2)//ȼ2����й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_F_TANK2,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_leak==FAULT_F_TANK3)//ȼ3����й©
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_F_TANK3,FAULT_STATE_ABNORMAL);
	}
	
	else
	{
		asm("nop;");
	}
	
	fault_deal.fault_mode=FAULT_MODE_NONE;
	
	fault_deal.step=FAULT_STEP_NONE;
	
}


/******************************************************************************************
**���ƣ����ӹ��ϴ���ģ��--Һ��ģ�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_cooler(uint16 fault_cooler)
{
	if(fault_cooler==FAULT_COOLER_ZZ)//���ϼ��--����Һ������
	{
		TGTHT510_1553b_relay_dealing(BUS_COOLER_1_POWER_OFF);//�����öϵ�
		TGTHT510_1553b_relay_dealing(BUS_COOLER_1_LESS_POWER_ON);//���üӵ�
		
		fault_deal.fault_mode=FAULT_MODE_NONE;
		fault_deal.step=FAULT_STEP_NONE;
		
	}
	
	else if(fault_cooler==FAULT_COOLER_ZB)//���ϼ��--����Һ�䱸��
	{
		TGTHT510_faultdeal_supply_cooler_dealing();
		TGTHT510_faultdeal_supply_pause();//����������ͣ
	}
	
	else if(fault_cooler==FAULT_COOLER_BZ)//���ϼ��--����Һ������
	{
		TGTHT510_1553b_relay_dealing(BUS_COOLER_2_POWER_OFF);//�����öϵ�
		TGTHT510_1553b_relay_dealing(BUS_COOLER_2_LESS_POWER_ON);//���üӵ�
		
		fault_deal.fault_mode=FAULT_MODE_NONE;
		fault_deal.step=FAULT_STEP_NONE;
	}
	
	else if(fault_cooler==FAULT_COOLER_BB)//���ϼ��--����Һ�䱸��
	{
		TGTHT510_faultdeal_supply_cooler_dealing();
		TGTHT510_faultdeal_supply_pause();//����������ͣ
	}
	
	else
	{
		fault_deal.fault_mode=FAULT_MODE_NONE;
		fault_deal.step=FAULT_STEP_NONE;
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϴ���ģ��--Һ��ģ�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_cooler_dealing(void)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			fault_deal.compressor_number=TGTHT510_faultdeal_which_compressor_working();
			
			if(fault_deal.compressor_number==FAULT_COMPRESSOR_N)//��ѹ��������
			{
				fault_deal.fault_mode=FAULT_MODE_NONE;
				fault_deal.step=FAULT_STEP_NONE;
			}
			
			else//��ѹ�������ڹ���
			{
				fault_deal.compressor_step=FAULT_STEP_START;
				fault_deal.step=FAULT_STEP_NO2;
			}
			break;
		}
		
		case FAULT_STEP_NO2://ѹ����ͣ������
		{
			if(TGTHT510_faultdeal_compressor_stop(fault_deal.compressor_number)==TRUE)
			{
				fault_deal.step=FAULT_STEP_END;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			fault_deal.compressor_number=FAULT_COMPRESSOR_N;
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}

	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϴ���ģ��--Һ��ģ��й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_leak_cooler(uint16 leak_cooler)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			if(leak_cooler==FAULT_COOLER_Z)//����Һ��й©
			{
				TGTHT510_faultdeal_lvb_set(LVb27G);
			}
			
			else if(leak_cooler==FAULT_COOLER_B)//����Һ��й©
			{
				TGTHT510_faultdeal_lvb_set(LVb28G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			if(leak_cooler==FAULT_COOLER_Z)//����Һ��й©
			{
				TGTHT510_faultdeal_lvb_set(LVb29G);
			}
			
			else if(leak_cooler==FAULT_COOLER_B)//����Һ��й©
			{
				TGTHT510_faultdeal_lvb_set(LVb30G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			if(leak_cooler==FAULT_COOLER_Z)//����Һ��й©
			{
				TGTHT510_faultdeal_lvb_set(LVb31G);
			}
			
			else if(leak_cooler==FAULT_COOLER_B)//����Һ��й©
			{
				TGTHT510_faultdeal_lvb_set(LVb32G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			if(leak_cooler==FAULT_COOLER_Z)//����Һ��й©
			{
				TGTHT510_faultdeal_lvb_set(LVb33G);
			}
			
			else if(leak_cooler==FAULT_COOLER_B)//����Һ��й©
			{
				TGTHT510_faultdeal_lvb_set(LVb34G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(leak_cooler==FAULT_COOLER_Z)//����Һ��й©
			{
				TGTHT510_faultdeal_lvb_set(LVb35G);
			}
			
			else if(leak_cooler==FAULT_COOLER_B)//����Һ��й©
			{
				TGTHT510_faultdeal_lvb_set(LVb36G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			if(leak_cooler==FAULT_COOLER_Z)//����Һ��й©
			{
				TGTHT510_faultdeal_lvb_set(LVb37G);
			}
			
			else if(leak_cooler==FAULT_COOLER_B)//����Һ��й©
			{
				TGTHT510_faultdeal_lvb_set(LVb38G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO7;
			
			break;
		}
		
		case FAULT_STEP_NO7:
		{
			fault_deal.compressor_number=TGTHT510_faultdeal_which_compressor_working();
			
			if(fault_deal.compressor_number==FAULT_COMPRESSOR_N)//��ѹ��������
			{
				fault_deal.fault_mode=FAULT_MODE_NONE;
				fault_deal.step=FAULT_STEP_NONE;
			}
			
			else//��ѹ�������ڹ���
			{
				fault_deal.compressor_step=FAULT_STEP_START;
				fault_deal.step=FAULT_STEP_NO8;
			}
			
			break;
		}
		
		case FAULT_STEP_NO8:
		{
			if(TGTHT510_faultdeal_compressor_stop(fault_deal.compressor_number)==TRUE)
			{
				fault_deal.step=FAULT_STEP_END;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			TGTHT510_faultdeal_supply_pause();//����������ͣ
			fault_deal.compressor_number=FAULT_COMPRESSOR_N;
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}

	}
	
}


/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--ѹ������ѹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_over_compressor(uint16 over_kind)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			if(over_kind==FAULT_COMPRESSOR_A_IN_OVER)//ѹ����A��ڳ�ѹ
			{
				TGTHT510_faultdeal_lvb_set(LVb13G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_B_IN_OVER)//ѹ����B��ڳ�ѹ
			{
				TGTHT510_faultdeal_lvb_set(LVb14G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_C_IN_OVER)//ѹ����C��ڳ�ѹ
			{
				TGTHT510_faultdeal_lvb_set(LVb23G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_A_MOTOR_OVER)//ѹ����A���ǻ��ѹ
			{
				TGTHT510_faultdeal_lvb_set(LVb17G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_B_MOTOR_OVER)//ѹ����B���ǻ��ѹ
			{
				TGTHT510_faultdeal_lvb_set(LVb18G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_C_MOTOR_OVER)//ѹ����C���ǻ��ѹ
			{
				TGTHT510_faultdeal_lvb_set(LVb25G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			if(over_kind==FAULT_COMPRESSOR_A_IN_OVER)//ѹ����A��ڳ�ѹ
			{
				TGTHT510_faultdeal_lvb_set(LVb15G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_B_IN_OVER)//ѹ����B��ڳ�ѹ
			{
				TGTHT510_faultdeal_lvb_set(LVb16G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_C_IN_OVER)//ѹ����C��ڳ�ѹ
			{
				TGTHT510_faultdeal_lvb_set(LVb24G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_A_MOTOR_OVER)//ѹ����A���ǻ��ѹ
			{
				TGTHT510_faultdeal_lvb_set(LVb19G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_B_MOTOR_OVER)//ѹ����B���ǻ��ѹ
			{
				TGTHT510_faultdeal_lvb_set(LVb20G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_C_MOTOR_OVER)//ѹ����C���ǻ��ѹ
			{
				TGTHT510_faultdeal_lvb_set(LVb26G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			fault_deal.compressor_step=FAULT_STEP_START;
			fault_deal.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			if(over_kind==FAULT_COMPRESSOR_A_IN_OVER)//ѹ����A��ڳ�ѹ
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_A)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(over_kind==FAULT_COMPRESSOR_B_IN_OVER)//ѹ����B��ڳ�ѹ
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_B)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(over_kind==FAULT_COMPRESSOR_C_IN_OVER)//ѹ����C��ڳ�ѹ
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_C)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(over_kind==FAULT_COMPRESSOR_A_MOTOR_OVER)//ѹ����A���ǻ��ѹ
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_A)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(over_kind==FAULT_COMPRESSOR_B_MOTOR_OVER)//ѹ����B���ǻ��ѹ
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_B)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(over_kind==FAULT_COMPRESSOR_C_MOTOR_OVER)//ѹ����C���ǻ��ѹ
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_C)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else
			{
				fault_deal.step=FAULT_STEP_END;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			TGTHT510_faultdeal_supply_pause();//����������ͣ
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϴ���ģ��--ѹ��������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_hot_compressor(uint16 hot_kind)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			fault_deal.compressor_step=FAULT_STEP_START;
			fault_deal.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			if(hot_kind==FAULT_COMPRESSOR_A_HOT)
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_A)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}

			else if(hot_kind==FAULT_COMPRESSOR_B_HOT)
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_B)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}	
			
			else if(hot_kind==FAULT_COMPRESSOR_C_HOT)
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_C)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}	
			
			else
			{
				fault_deal.step=FAULT_STEP_END;
			}
			
			break;
		
		}
		
		case FAULT_STEP_END:
		{
			TGTHT510_faultdeal_supply_pause();//����������ͣ
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϴ���ģ��--�������䳬ѹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_tank_overpressure(uint16 tank_overpressure)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			if(tank_overpressure==FAULT_O_TANK1)//���ϼ��--��1����
			{
				TGTHT510_faultdeal_lvb_set(LVb7G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK2)//���ϼ��--��2����
			{
				TGTHT510_faultdeal_lvb_set(LVb9G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK3)//���ϼ��--��3����
			{
				TGTHT510_faultdeal_lvb_set(LVb11G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK1)//���ϼ��--ȼ1����
			{
				TGTHT510_faultdeal_lvb_set(LVb8G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK2)//���ϼ��--ȼ2����
			{
				TGTHT510_faultdeal_lvb_set(LVb10G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK3)//���ϼ��--ȼ3����
			{
				TGTHT510_faultdeal_lvb_set(LVb12G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			if(tank_overpressure==FAULT_O_TANK1)//���ϼ��--��1����
			{
				TGTHT510_supply_main_lvt_set(LVt1G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK2)//���ϼ��--��2����
			{
				TGTHT510_supply_main_lvt_set(LVt3G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK3)//���ϼ��--��3����
			{
				TGTHT510_supply_main_lvt_set(LVt5G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK1)//���ϼ��--ȼ1����
			{
				TGTHT510_supply_main_lvt_set(LVt2G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK2)//���ϼ��--ȼ2����
			{
				TGTHT510_supply_main_lvt_set(LVt4G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK3)//���ϼ��--ȼ3����
			{
				TGTHT510_supply_main_lvt_set(LVt6G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO3;
			
			break;
			
		}
		
		case FAULT_STEP_NO3://��ʼ��ʱ�ȴ�
		{
			TGTHT510_faultdeal_time_start(&fault_deal);
			fault_deal.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4://��ʱ�ȴ�1min
		{
			if(TGTHT510_faultdeal_time_is_get(&fault_deal,CONST_TIME_1MIN)==TRUE)
			{
				fault_deal.step=FAULT_STEP_NO5;
			}
			break;
		}
	
		case FAULT_STEP_NO5:
		{
			fault_deal.compressor_number=TGTHT510_faultdeal_which_compressor_working();
			
			if(fault_deal.compressor_number==FAULT_COMPRESSOR_N)//��ѹ��������
			{
				fault_deal.fault_mode=FAULT_MODE_NONE;
				fault_deal.step=FAULT_STEP_END;
			}
			
			else//��ѹ�������ڹ���
			{
				fault_deal.compressor_step=FAULT_STEP_START;
				fault_deal.step=FAULT_STEP_NO6;
			}
			
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			if(TGTHT510_faultdeal_compressor_stop(fault_deal.compressor_number)==TRUE)
			{
				fault_deal.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7:
		{
			if(tank_overpressure==FAULT_O_TANK1)//���ϼ��--��1����
			{
				TGTHT510_supply_main_lvt_set(LVt7G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK2)//���ϼ��--��2����
			{
				TGTHT510_supply_main_lvt_set(LVt11G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK3)//���ϼ��--��3����
			{
				TGTHT510_supply_main_lvt_set(LVt15G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK1)//���ϼ��--ȼ1����
			{
				TGTHT510_supply_main_lvt_set(LVt8G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK2)//���ϼ��--ȼ2����
			{
				TGTHT510_supply_main_lvt_set(LVt12G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK3)//���ϼ��--ȼ3����
			{
				TGTHT510_supply_main_lvt_set(LVt16G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO8;
			
			break;
			
		}
		
		case FAULT_STEP_NO8://��ʼ��ʱ�ȴ�
		{
			TGTHT510_faultdeal_time_start(&fault_deal);
			fault_deal.step=FAULT_STEP_NO9;
			break;
		}
		
		case FAULT_STEP_NO9://��ʱ�ȴ�1min
		{
			if(TGTHT510_faultdeal_time_is_get(&fault_deal,CONST_TIME_1MIN)==TRUE)
			{
				fault_deal.step=FAULT_STEP_NO10;
			}
			break;
		}
		
		case FAULT_STEP_NO10:
		{
			if(tank_overpressure==FAULT_O_TANK1)//���ϼ��--��1����
			{
				TGTHT510_supply_main_lvt_set(LVt9G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK2)//���ϼ��--��2����
			{
				TGTHT510_supply_main_lvt_set(LVt13G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK3)//���ϼ��--��3����
			{
				TGTHT510_supply_main_lvt_set(LVt17G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK1)//���ϼ��--ȼ1����
			{
				TGTHT510_supply_main_lvt_set(LVt10G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK2)//���ϼ��--ȼ2����
			{
				TGTHT510_supply_main_lvt_set(LVt14G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK3)//���ϼ��--ȼ3����
			{
				TGTHT510_supply_main_lvt_set(LVt18G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO11;
			
			break;
			
		}
		
		case FAULT_STEP_NO11://��ʼ��ʱ�ȴ�
		{
			TGTHT510_faultdeal_time_start(&fault_deal);
			fault_deal.step=FAULT_STEP_NO12;
			break;
		}
		
		case FAULT_STEP_NO12://��ʱ�ȴ�1min
		{
			if(TGTHT510_faultdeal_time_is_get(&fault_deal,CONST_TIME_1MIN)==TRUE)
			{
				fault_deal.step=FAULT_STEP_END;
			}
			break;
		}
		
		case FAULT_STEP_END:
		{
			TGTHT510_faultdeal_supply_pause();//����������ͣ
			fault_deal.compressor_number=FAULT_COMPRESSOR_N;
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϴ���ģ��--ѹ����ĤƬ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_compressor_break(uint16 compressor_break)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			fault_deal.compressor_step=FAULT_STEP_START;
			fault_deal.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			if(compressor_break==FAULT_COMPRESSOR_A_BREAK)//ѹ����AĤƬ����
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_A)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(compressor_break==FAULT_COMPRESSOR_B_BREAK)//ѹ����BĤƬ����
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_B)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(compressor_break==FAULT_COMPRESSOR_C_BREAK)//ѹ����CĤƬ����
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_C)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			else
			{
				fault_deal.step=FAULT_STEP_END;
			}
			
			break;
			
		}
		
		case FAULT_STEP_END:
		{
			TGTHT510_faultdeal_supply_pause();//����������ͣ
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			break;
		}
		
		default:
		{
			break;
		}
	
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϴ���ģ��--������ƿй©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������NE58651577231
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_gas_leak(void)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			fault_deal.compressor_number=TGTHT510_faultdeal_which_compressor_working();
			
			if(fault_deal.compressor_number==FAULT_COMPRESSOR_N)//��ѹ��������
			{
				fault_deal.fault_mode=FAULT_MODE_NONE;
				fault_deal.step=FAULT_STEP_NONE;
			}
			
			else//��ѹ�������ڹ���
			{
				fault_deal.compressor_step=FAULT_STEP_START;
				fault_deal.step=FAULT_STEP_NO2;
			}
			
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			if(TGTHT510_faultdeal_compressor_stop(fault_deal.compressor_number)==TRUE)
			{
				fault_deal.step=FAULT_STEP_END;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			TGTHT510_faultdeal_supply_pause();//����������ͣ
			fault_deal.compressor_number=FAULT_COMPRESSOR_N;
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϴ���ģ��--���䲹��Һ·й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(uint16 tank_leak,uint16 number)
{
	//�����䲹��Һ·
	if((tank_leak==FAULT_O_TANK1)||(tank_leak==FAULT_O_TANK2)||(tank_leak==FAULT_O_TANK3))
	{
		if((TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)||\
		(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3))//��·���ӽӿ�
		{
			switch(number)
			{
				case 1:
				{
					TGTHT510_faultdeal_lvb_set(LVb43G);
					break;
				}
				
				case 2:
				{
					TGTHT510_faultdeal_lvb_set(LVb45G);
					break;
				}
				
				case 3:
				{
					TGTHT510_faultdeal_lvb_set(LVb47G);
					break;
				}
				
				case 4:
				{
					TGTHT510_faultdeal_lvb_set(LVb39G);
					break;
				}
				
				case 5:
				{
					TGTHT510_faultdeal_lvb_set(LVb63G);
					break;
				}
				
				case 6:
				{
					TGTHT510_faultdeal_lvb_set(LVb71K);
					break;
				}
				
				case 7:
				{
					TGTHT510_faultdeal_lvb_set(LVb79K);
					break;
				}
				
				case 8:
				{
					TGTHT510_faultdeal_lvb_set(LVb71G);
					break;
				}
				
				case 9:
				{
					TGTHT510_faultdeal_lvb_set(LVb79G);
					break;
				}
				
				case 10:
				{
					TGTHT510_faultdeal_lvb_set(LVb41G);
					break;
				}
				
				case 11:
				{
					TGTHT510_faultdeal_lvb_set(LVb65G);
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
		}
		
		
		else if((TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)||\
		(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4))//��·���ӽӿ�
		{
			switch(number)
			{
				case 1:
				{
					TGTHT510_faultdeal_lvb_set(LVb53G);
					break;
				}
				
				case 2:
				{
					TGTHT510_faultdeal_lvb_set(LVb55G);
					break;
				}
				
				case 3:
				{
					TGTHT510_faultdeal_lvb_set(LVb57G);
					break;
				}
				
				case 4:
				{
					TGTHT510_faultdeal_lvb_set(LVb49G);
					break;
				}
				
				case 5:
				{
					TGTHT510_faultdeal_lvb_set(LVb59G);
					break;
				}
				
				case 6:
				{
					TGTHT510_faultdeal_lvb_set(LVb67K);
					break;
				}
				
				case 7:
				{
					TGTHT510_faultdeal_lvb_set(LVb85K);
					break;
				}
				
				case 8:
				{
					TGTHT510_faultdeal_lvb_set(LVb67G);
					break;
				}
				
				case 9:
				{
					TGTHT510_faultdeal_lvb_set(LVb85G);
					break;
				}
				
				case 10:
				{
					TGTHT510_faultdeal_lvb_set(LVb51G);
					break;
				}
				
				case 11:
				{
					TGTHT510_faultdeal_lvb_set(LVb61G);
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
		}
		
		else
		{
			asm("nop;");
		}
		
	}
	//ȼ���䲹��Һ·
	else if((tank_leak==FAULT_F_TANK1)||(tank_leak==FAULT_F_TANK2)||(tank_leak==FAULT_F_TANK3))
	{
		if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)||\
		(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3))//��·���ӽӿ�
		{
			switch(number)
			{
				case 1:
				{
					TGTHT510_faultdeal_lvb_set(LVb44G);
					break;
				}
				
				case 2:
				{
					TGTHT510_faultdeal_lvb_set(LVb46G);
					break;
				}
				
				case 3:
				{
					TGTHT510_faultdeal_lvb_set(LVb48G);
					break;
				}
				
				case 4:
				{
					TGTHT510_faultdeal_lvb_set(LVb40G);
					break;
				}
				
				case 5:
				{
					TGTHT510_faultdeal_lvb_set(LVb64G);
					break;
				}
				
				case 6:
				{
					TGTHT510_faultdeal_lvb_set(LVb72K);
					break;
				}
				
				case 7:
				{
					TGTHT510_faultdeal_lvb_set(LVb80K);
					break;
				}
				
				case 8:
				{
					TGTHT510_faultdeal_lvb_set(LVb72G);
					break;
				}
				
				case 9:
				{
					TGTHT510_faultdeal_lvb_set(LVb80G);
					break;
				}
				
				case 10:
				{
					TGTHT510_faultdeal_lvb_set(LVb42G);
					break;
				}
				
				case 11:
				{
					TGTHT510_faultdeal_lvb_set(LVb66G);
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
		}
		
		else if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)||\
		(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4))//��·���ӽӿ�
		{
			switch(number)
			{
				case 1:
				{
					TGTHT510_faultdeal_lvb_set(LVb54G);
					break;
				}
				
				case 2:
				{
					TGTHT510_faultdeal_lvb_set(LVb56G);
					break;
				}
				
				case 3:
				{
					TGTHT510_faultdeal_lvb_set(LVb58G);
					break;
				}
				
				case 4:
				{
					TGTHT510_faultdeal_lvb_set(LVb50G);
					break;
				}
				
				case 5:
				{
					TGTHT510_faultdeal_lvb_set(LVb60G);
					break;
				}
				
				case 6:
				{
					TGTHT510_faultdeal_lvb_set(LVb68K);
					break;
				}
				
				case 7:
				{
					TGTHT510_faultdeal_lvb_set(LVb86K);
					break;
				}
				
				case 8:
				{
					TGTHT510_faultdeal_lvb_set(LVb68G);
					break;
				}
				
				case 9:
				{
					TGTHT510_faultdeal_lvb_set(LVb86G);
					break;
				}
				
				case 10:
				{
					TGTHT510_faultdeal_lvb_set(LVb52G);
					break;
				}
				
				case 11:
				{
					TGTHT510_faultdeal_lvb_set(LVb62G);
					break;
				}
				
				default:
				{
					break;
				}
				
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
**���ƣ����ӹ��ϴ���ģ��--���䲹��Һ·й©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_tank_pipe_leak(uint16 tank_leak)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			TGTHT510_faultdeal_supply_pause();//����������ͣ
			fault_deal.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,1);
			fault_deal.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,2);
			fault_deal.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,3);
			fault_deal.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,4);
			fault_deal.step=FAULT_STEP_NO6;
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,5);
			fault_deal.step=FAULT_STEP_NO7;
			break;
		}
		
		case FAULT_STEP_NO7:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,6);
			fault_deal.step=FAULT_STEP_NO8;
			break;
		}
		
		case FAULT_STEP_NO8:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,7);
			fault_deal.step=FAULT_STEP_NO9;
			break;
		}
		
		case FAULT_STEP_NO9://��ʱ�ȴ�
		{
			fault_deal.step=FAULT_STEP_NO15;
			break;
		}
		
		case FAULT_STEP_NO15://��ʱ�ȴ�
		{
			fault_deal.step=FAULT_STEP_NO16;
			break;
		}
		
		case FAULT_STEP_NO16://��ʱ�ȴ�
		{
			fault_deal.step=FAULT_STEP_NO10;
			break;
		}
		
		case FAULT_STEP_NO10:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,8);
			fault_deal.step=FAULT_STEP_NO11;
			break;
		}
		
		case FAULT_STEP_NO11:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,9);
			fault_deal.step=FAULT_STEP_NO12;
			break;
		}
		
		case FAULT_STEP_NO12:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,10);
			fault_deal.step=FAULT_STEP_NO13;
			break;
		}
		
		case FAULT_STEP_NO13:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,11);
			fault_deal.step=FAULT_STEP_NO14;
			break;
		}
		
		case FAULT_STEP_NO14:
		{
			//���ӹ�·�¶ȿ��µ�����Ϊ�ͣ������䣡������
			fault_deal.step=FAULT_STEP_END;
			break;
		}
		
		case FAULT_STEP_END:
		{
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϴ���ģ��--�������¶��쳣
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_interface_temperature_dealing(uint16 interface,uint16 number)
{
	if(interface==FAULT_INTERFACE_O)
	{
		switch(number)
		{
			case 1:
			{
				TGTHT510_faultdeal_lvb_set(LVb69G);
				break;
			}
			
			case 2:
			{
				TGTHT510_faultdeal_lvb_set(LVb73G);
				break;
			}
			
			case 3:
			{
				TGTHT510_faultdeal_lvb_set(LVb67G);
				break;
			}
			
			case 4:
			{
				TGTHT510_faultdeal_lvb_set(LVb77G);
				break;
			}
			
			case 5:
			{
				TGTHT510_faultdeal_lvb_set(LVb71G);
				break;
			}
			
			case 6:
			{
				TGTHT510_faultdeal_lvb_set(LVb75G);
				break;
			}
			
			case 7:
			{
				TGTHT510_faultdeal_lvb_set(LVb79G);
				break;
			}
			
			case 8:
			{
				TGTHT510_faultdeal_lvb_set(LVb81G);
				break;
			}
			
			case 9:
			{
				TGTHT510_faultdeal_lvb_set(LVb83G);
				break;
			}
			
			case 10:
			{
				TGTHT510_faultdeal_lvb_set(LVb85G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
	else if(interface==FAULT_INTERFACE_F)
	{
		switch(number)
		{
			case 1:
			{
				TGTHT510_faultdeal_lvb_set(LVb70G);
				break;
			}
			
			case 2:
			{
				TGTHT510_faultdeal_lvb_set(LVb74G);
				break;
			}
			
			case 3:
			{
				TGTHT510_faultdeal_lvb_set(LVb68G);
				break;
			}
			
			case 4:
			{
				TGTHT510_faultdeal_lvb_set(LVb78G);
				break;
			}
			
			case 5:
			{
				TGTHT510_faultdeal_lvb_set(LVb72G);
				break;
			}
			
			case 6:
			{
				TGTHT510_faultdeal_lvb_set(LVb76G);
				break;
			}
			
			case 7:
			{
				TGTHT510_faultdeal_lvb_set(LVb80G);
				break;
			}
			
			case 8:
			{
				TGTHT510_faultdeal_lvb_set(LVb82G);
				break;
			}
			
			case 9:
			{
				TGTHT510_faultdeal_lvb_set(LVb84G);
				break;
			}
			
			case 10:
			{
				TGTHT510_faultdeal_lvb_set(LVb86G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
	else
	{
		asm("nop;");
	}
	
}



/******************************************************************************************
**���ƣ����ӹ��ϴ���ģ��--�������¶��쳣
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_interface_temperature(uint16 interface)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,1);
			fault_deal.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,2);
			fault_deal.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,3);
			fault_deal.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,4);
			fault_deal.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,5);
			fault_deal.step=FAULT_STEP_NO6;
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,6);
			fault_deal.step=FAULT_STEP_NO7;
			break;
		}
		
		case FAULT_STEP_NO7:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,7);
			fault_deal.step=FAULT_STEP_NO8;
			break;
		}
		
		case FAULT_STEP_NO8:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,8);
			fault_deal.step=FAULT_STEP_NO9;
			break;
		}
		
		case FAULT_STEP_NO9:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,9);
			fault_deal.step=FAULT_STEP_NO10;
			break;
		}
		
		case FAULT_STEP_NO10:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,10);
			fault_deal.step=FAULT_STEP_END;
			break;
		}
		
		case FAULT_STEP_END:
		{
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϼ��ģ��--���ӹ�·��©
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_in_leak(uint16 leak_kind)
{
	uint16 temp;
	
	if(leak_kind==FAULT_IN_LEAK_O_Z)//�������ӹ�·��©
	{
		temp=TGTHT510_supply_decode_par.interface_O;
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O1;
		
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK1);
		
		TGTHT510_supply_decode_par.interface_O=temp;
	}
	
	else if(leak_kind==FAULT_IN_LEAK_O_B)//�������ӹ�·��©
	{
		temp=TGTHT510_supply_decode_par.interface_O;
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O2;
		
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK1);
		
		TGTHT510_supply_decode_par.interface_O=temp;
	}
	
	else if(leak_kind==FAULT_IN_LEAK_F_Z)//ȼ�����ӹ�·��©
	{
		temp=TGTHT510_supply_decode_par.interface_F;
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R1;
		
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK1);
		
		TGTHT510_supply_decode_par.interface_F=temp;
	}
	
	else if(leak_kind==FAULT_IN_LEAK_F_B)//ȼ�����ӹ�·��©
	{
		temp=TGTHT510_supply_decode_par.interface_F;
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R2;
		
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK1);
		
		TGTHT510_supply_decode_par.interface_F=temp;
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϴ���ģ��--�����Ͻ����¶��쳣
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_temperature_dealing(uint16 temperature_kind,uint16 number)
{
	//ǰ��ȼ1�����Ͻ����¶��쳣�����ߺ���ȼ1�����Ͻ����¶��쳣
	if((temperature_kind==FAULT_TEMPERATURE_FORE_F1)||(temperature_kind==FAULT_TEMPERATURE_BACK_F1))
	{
		switch(number)
		{
			case 1:
			{
				TGTHT510_faultdeal_lvb_set(LVb40G);
				break;
			}
			
			case 2:
			{
				TGTHT510_faultdeal_lvb_set(LVb64G);
				break;
			}
			
			case 3:
			{
				TGTHT510_faultdeal_lvb_set(LVb44G);
				break;
			}
			
			case 4:
			{
				TGTHT510_faultdeal_lvb_set(LVb46G);
				break;
			}
			
			case 5:
			{
				TGTHT510_faultdeal_lvb_set(LVb48G);
				break;
			}
			
			case 6:
			{
				TGTHT510_faultdeal_lvb_set(LVb72K);
				break;
			}
			
			case 7:
			{
				TGTHT510_faultdeal_lvb_set(LVb80K);
				break;
			}
			
			case 8:
			{
				TGTHT510_faultdeal_lvb_set(LVb72G);
				break;
			}
			
			case 9:
			{
				TGTHT510_faultdeal_lvb_set(LVb80G);
				break;
			}
			
			case 10:
			{
				TGTHT510_faultdeal_lvb_set(LVb42G);
				break;
			}
			
			case 11:
			{
				TGTHT510_faultdeal_lvb_set(LVb66G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
	//ǰ��ȼ2�����Ͻ����¶��쳣�����ߺ���ȼ2�����Ͻ����¶��쳣
	else if((temperature_kind==FAULT_TEMPERATURE_FORE_F2)||(temperature_kind==FAULT_TEMPERATURE_BACK_F2))
	{
		switch(number)
		{
			case 1:
			{
				TGTHT510_faultdeal_lvb_set(LVb50G);
				break;
			}
			
			case 2:
			{
				TGTHT510_faultdeal_lvb_set(LVb60G);
				break;
			}
			
			case 3:
			{
				TGTHT510_faultdeal_lvb_set(LVb54G);
				break;
			}
			
			case 4:
			{
				TGTHT510_faultdeal_lvb_set(LVb56G);
				break;
			}
			
			case 5:
			{
				TGTHT510_faultdeal_lvb_set(LVb58G);
				break;
			}
			
			case 6:
			{
				TGTHT510_faultdeal_lvb_set(LVb68K);
				break;
			}
			
			case 7:
			{
				TGTHT510_faultdeal_lvb_set(LVb86K);
				break;
			}
			
			case 8:
			{
				TGTHT510_faultdeal_lvb_set(LVb68G);
				break;
			}
			
			case 9:
			{
				TGTHT510_faultdeal_lvb_set(LVb86G);
				break;
			}
			
			case 10:
			{
				TGTHT510_faultdeal_lvb_set(LVb52G);
				break;
			}
			
			case 11:
			{
				TGTHT510_faultdeal_lvb_set(LVb62G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
	//ǰ����1�����Ͻ����¶��쳣�����ߺ�����1�����Ͻ����¶��쳣
	else if((temperature_kind==FAULT_TEMPERATURE_FORE_O1)||(temperature_kind==FAULT_TEMPERATURE_BACK_O1))
	{
		switch(number)
		{
			case 1:
			{
				TGTHT510_faultdeal_lvb_set(LVb39G);
				break;
			}
			
			case 2:
			{
				TGTHT510_faultdeal_lvb_set(LVb63G);
				break;
			}
			
			case 3:
			{
				TGTHT510_faultdeal_lvb_set(LVb43G);
				break;
			}
			
			case 4:
			{
				TGTHT510_faultdeal_lvb_set(LVb45G);
				break;
			}
			
			case 5:
			{
				TGTHT510_faultdeal_lvb_set(LVb47G);
				break;
			}
			
			case 6:
			{
				TGTHT510_faultdeal_lvb_set(LVb71K);
				break;
			}
			
			case 7:
			{
				TGTHT510_faultdeal_lvb_set(LVb79K);
				break;
			}
			
			case 8:
			{
				TGTHT510_faultdeal_lvb_set(LVb71G);
				break;
			}
			
			case 9:
			{
				TGTHT510_faultdeal_lvb_set(LVb79G);
				break;
			}
			
			case 10:
			{
				TGTHT510_faultdeal_lvb_set(LVb41G);
				break;
			}
			
			case 11:
			{
				TGTHT510_faultdeal_lvb_set(LVb65G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
	//ǰ����2�����Ͻ����¶��쳣�����ߺ�����2�����Ͻ����¶��쳣
	else if((temperature_kind==FAULT_TEMPERATURE_FORE_O2)||(temperature_kind==FAULT_TEMPERATURE_BACK_O2))
	{
		switch(number)
		{
			case 1:
			{
				TGTHT510_faultdeal_lvb_set(LVb49G);
				break;
			}
			
			case 2:
			{
				TGTHT510_faultdeal_lvb_set(LVb59G);
				break;
			}
			
			case 3:
			{
				TGTHT510_faultdeal_lvb_set(LVb53G);
				break;
			}
			
			case 4:
			{
				TGTHT510_faultdeal_lvb_set(LVb55G);
				break;
			}
			
			case 5:
			{
				TGTHT510_faultdeal_lvb_set(LVb57G);
				break;
			}
			
			case 6:
			{
				TGTHT510_faultdeal_lvb_set(LVb67K);
				break;
			}
			
			case 7:
			{
				TGTHT510_faultdeal_lvb_set(LVb85K);
				break;
			}
			
			case 8:
			{
				TGTHT510_faultdeal_lvb_set(LVb67G);
				break;
			}
			
			case 9:
			{
				TGTHT510_faultdeal_lvb_set(LVb85G);
				break;
			}
			
			case 10:
			{
				TGTHT510_faultdeal_lvb_set(LVb51G);
				break;
			}
			
			case 11:
			{
				TGTHT510_faultdeal_lvb_set(LVb61G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
	else
	{
		asm("nop;");
	}

}

/******************************************************************************************
**���ƣ����ӹ��ϴ���ģ��--�����Ͻ����¶��쳣
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_temperature(uint16 temperature_kind)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,1);
			fault_deal.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,2);
			fault_deal.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,3);
			fault_deal.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,4);
			fault_deal.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,5);
			fault_deal.step=FAULT_STEP_NO6;
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,6);
			fault_deal.step=FAULT_STEP_NO7;
			break;
		}
		
		case FAULT_STEP_NO7:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,7);
			fault_deal.step=FAULT_STEP_NO19;
			break;
		}
		
		case FAULT_STEP_NO19:
		{
			fault_deal.step=FAULT_STEP_NO20;
			break;
			
		}
		
		case FAULT_STEP_NO20:
		{
			fault_deal.step=FAULT_STEP_NO8;
			break;
			
		}
		
		case FAULT_STEP_NO8:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,8);
			fault_deal.step=FAULT_STEP_NO9;
			break;
		}
		
		case FAULT_STEP_NO9:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,9);
			fault_deal.step=FAULT_STEP_NO10;
			break;
		}
		
		case FAULT_STEP_NO10:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,10);
			fault_deal.step=FAULT_STEP_NO11;
			break;
		}
		
		case FAULT_STEP_NO11:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,11);
			
			
			fault_deal.step=FAULT_STEP_END;
			break;
		}
		
		case FAULT_STEP_END:
		{
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**���ƣ����ӹ��ϴ���ģ��--���俨��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdeal_supply_ka_tank(uint16 ka)
{
	if(ka==FAULT_O_TANK1)//��1���俨��
	{
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK1);
	}
	
	else if(ka==FAULT_O_TANK2)//��2���俨��
	{
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK2);
	}
	
	else if(ka==FAULT_O_TANK3)//��3���俨��
	{
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK3);
	}
	
	else if(ka==FAULT_F_TANK1)//ȼ1���俨��
	{
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK1);
	}
	
	else if(ka==FAULT_F_TANK2)//ȼ2���俨��
	{
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK2);
	}
	
	else if(ka==FAULT_F_TANK3)//ȼ3���俨��
	{
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK3);
	}
	
	else
	{
		asm("nop;");
	}

}



/******************************************************************************************
**���ƣ� ����� ---�ƽ��ʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_launch(void)
{

	//����ƿ1й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,DISABLE);
	
	//����ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,DISABLE);
	
	//����ƿ3й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,DISABLE);
	
	//ȼ��ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,DISABLE);
	
	//ȼ��ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,DISABLE);
	
	//ȼ��ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,DISABLE);
	
	//��1���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,ENABLE);
	
	//��2���䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,ENABLE);
	
	//��3���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,ENABLE);
	
	//ȼ1���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,ENABLE);
	
	//ȼ2���䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,ENABLE);
	
	//ȼ3���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,ENABLE);
	
	//�����˿ط��������Ʒ���й©
	TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_main_valve_leak.faultdiagnosis_count=0;
	
	//�����˿ط��������Ʒ���й©
	TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_less_valve_leak.faultdiagnosis_count=0;
	
	//C���˿ط��������Ʒ���й©
	TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_C_all_valve_leak.faultdiagnosis_count=0;
	
	//A�������˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_main_valve_leak.faultdiagnosis_count=0;
	
	//A�鱸���˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_less_valve_leak.faultdiagnosis_count=0;
	
	//��1����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,DISABLE);
	
	//��2����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,DISABLE);
	
	//��3����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,DISABLE);
	
	//ȼ1����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,DISABLE);
	
	//ȼ2����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,DISABLE);
	
	//ȼ3����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,DISABLE);
	
}


/******************************************************************************************
**���ƣ� ���� ---�ƽ��ʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_orbit(void)
{
	TGTHT510_faultdiagnosis_push_set_stage_launch();
}


/******************************************************************************************
**���ƣ� Ѳ��� ---�ƽ��ʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_polling(void)
{
	//����ƿ1й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,ENABLE);
	
	//����ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,ENABLE);
	
	//����ƿ3й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,ENABLE);
	
	//ȼ��ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,ENABLE);
	
	//ȼ��ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,ENABLE);
	
	//ȼ��ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,ENABLE);
	
	//��1���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,ENABLE);
	
	//��2���䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,ENABLE);
	
	//��3���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,ENABLE);
	
	//ȼ1���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,ENABLE);
	
	//ȼ2���䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,ENABLE);
	
	//ȼ3���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,ENABLE);
	
	//�����˿ط��������Ʒ���й©
	TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_main_valve_leak.faultdiagnosis_count=0;
	
	//�����˿ط��������Ʒ���й©
	TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_less_valve_leak.faultdiagnosis_count=0;
	
	//C���˿ط��������Ʒ���й©
	TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_C_all_valve_leak.faultdiagnosis_count=0;
	
	//A�������˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_main_valve_leak.faultdiagnosis_count=0;
	
	//A�鱸���˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_less_valve_leak.faultdiagnosis_count=0;
	
	//��1����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,ENABLE);
	
	//��2����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,ENABLE);
	
	//��3����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,ENABLE);
	
	//ȼ1����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,ENABLE);
	
	//ȼ2����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,ENABLE);
	
	//ȼ3����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,ENABLE);
	
}

/******************************************************************************************
**���ƣ� ѹ���������� ---�ƽ��ʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_gas(void)
{
	TGTHT510_faultdiagnosis_push_set_stage_polling();
}

/******************************************************************************************
**���ƣ� ���ӳ����� ---�ƽ��ʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_comp(void)
{
	if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)||\
	(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)||\
	(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1))
	{
		//ȼ1���䳬ѹ	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,DISABLE);
		
		//ȼ1����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,DISABLE);
	}
	
	else
	{
		//ȼ1���䳬ѹ	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,ENABLE);
		
		//ȼ1����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)||\
	(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)||\
	(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2))
	{
		//ȼ2���䳬ѹ	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,DISABLE);
		
		//ȼ2����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,DISABLE);
	}
	
	else
	{
		//ȼ2���䳬ѹ	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,ENABLE);
		
		//ȼ2����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)||\
	(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)||\
	(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3))
	{
		//ȼ3���䳬ѹ	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,DISABLE);
		
		//ȼ3����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,DISABLE);
	}
	
	else
	{
		//ȼ3���䳬ѹ	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,ENABLE);
		
		//ȼ3����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)||\
	(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)||\
	(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1))
	{
		//��1���䳬ѹ	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,DISABLE);
		
		//��1����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,DISABLE);
	}
	
	else
	{
		//��1���䳬ѹ	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,ENABLE);
		
		//��1����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)||\
	(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)||\
	(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2))
	{
		//��2���䳬ѹ	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,DISABLE);
		
		//��2����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,DISABLE);
	}
	
	else
	{
		//��2���䳬ѹ	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,ENABLE);
		
		//��2����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)||\
	(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)||\
	(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3))
	{
		//��3���䳬ѹ	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,DISABLE);
		
		//��3����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,DISABLE);
	}
	
	else
	{
		//��3���䳬ѹ	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,ENABLE);
		
		//��3����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_gas_tank_F1==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F1==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F2==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F2==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F3==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F3==DECODE_GAS_F1))
	{
		//ȼ��ƿ1й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,DISABLE);
	}
	
	else
	{
		//ȼ��ƿ1й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_gas_tank_F1==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F1==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F2==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F2==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F3==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F3==DECODE_GAS_F2))
	{
		//ȼ��ƿ2й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,DISABLE);
	}
	
	else
	{
		//ȼ��ƿ2й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_gas_tank_F1==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F1==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F2==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F2==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F3==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F3==DECODE_GAS_F3))
	{
		//ȼ��ƿ3й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,DISABLE);
	}
	
	else
	{
		//ȼ��ƿ3й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_gas_tank_O1==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O1==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O2==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O2==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O3==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O3==DECODE_GAS_O1))
	{
		//����ƿ1й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,DISABLE);
	}
	
	else
	{
		//����ƿ1й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_gas_tank_O1==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O1==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O2==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O2==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O3==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O3==DECODE_GAS_O2))
	{
		//����ƿ2й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,DISABLE);
	}
	
	else
	{
		//����ƿ2й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_gas_tank_O1==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O1==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O2==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O2==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O3==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O3==DECODE_GAS_O3))
	{
		//����ƿ3й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,DISABLE);
	}
	
	else
	{
		//����ƿ3й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,ENABLE);
	}
	
	
	//�����˿ط��������Ʒ���й©
	TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_main_valve_leak.faultdiagnosis_count=0;
	
	//�����˿ط��������Ʒ���й©
	TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_less_valve_leak.faultdiagnosis_count=0;
	
	//C���˿ط��������Ʒ���й©
	TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_C_all_valve_leak.faultdiagnosis_count=0;
	
	//A�������˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_main_valve_leak.faultdiagnosis_count=0;
	
	//A�鱸���˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_less_valve_leak.faultdiagnosis_count=0;
	
}


/******************************************************************************************
**���ƣ� ���������� ---�ƽ��ʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_flow(void)
{
	//����ƿ1й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,ENABLE);
	
	//����ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,ENABLE);
	
	//����ƿ3й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,ENABLE);
	
	//ȼ��ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,ENABLE);
	
	//ȼ��ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,ENABLE);
	
	//ȼ��ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,ENABLE);
	
	//��1���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,ENABLE);
	
	//��2���䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,ENABLE);
	
	//��3���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,ENABLE);
	
	//ȼ1���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,ENABLE);
	
	//ȼ2���䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,ENABLE);
	
	//ȼ3���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,ENABLE);
	
	//�����˿ط��������Ʒ���й©
	TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_main_valve_leak.faultdiagnosis_count=0;
	
	//�����˿ط��������Ʒ���й©
	TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_less_valve_leak.faultdiagnosis_count=0;
	
	//C���˿ط��������Ʒ���й©
	TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_C_all_valve_leak.faultdiagnosis_count=0;
	
	//A�������˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_main_valve_leak.faultdiagnosis_count=0;
	
	//A�鱸���˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_less_valve_leak.faultdiagnosis_count=0;
	
	
	
	if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)||\
	(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)||\
	(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1))
	{
		//ȼ1����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,DISABLE);
	}
	
	else
	{
		//ȼ1����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)||\
	(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)||\
	(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2))
	{
		//ȼ2����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,DISABLE);
	}
	
	else
	{
		//ȼ2����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)||\
	(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)||\
	(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3))
	{
		//ȼ3����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,DISABLE);
	}
	
	else
	{
		//ȼ3����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)||\
	(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)||\
	(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1))
	{
		//��1����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,DISABLE);
	}
	
	else
	{
		//��1����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)||\
	(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)||\
	(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2))
	{
		//��2����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,DISABLE);
	}
	
	else
	{
		//��2����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)||\
	(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)||\
	(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3))
	{
		//��3����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,DISABLE);
	}
	
	else
	{
		//��3����й©	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,ENABLE);
	}
	
	
}


/******************************************************************************************
**���ƣ� ���Ӹ�ѹ�� ---�ƽ��ʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_repre(void)
{
	if((TGTHT510_supply_decode_par.first_gas_tank_F1==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F1==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F2==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F2==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F3==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F3==DECODE_GAS_F1))
	{
		//ȼ��ƿ1й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,DISABLE);
	}
	
	else
	{
		//ȼ��ƿ1й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_gas_tank_F1==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F1==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F2==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F2==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F3==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F3==DECODE_GAS_F2))
	{
		//ȼ��ƿ2й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,DISABLE);
	}
	
	else
	{
		//ȼ��ƿ2й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_gas_tank_F1==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F1==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F2==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F2==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F3==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F3==DECODE_GAS_F3))
	{
		//ȼ��ƿ3й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,DISABLE);
	}
	
	else
	{
		//ȼ��ƿ3й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_gas_tank_O1==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O1==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O2==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O2==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O3==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O3==DECODE_GAS_O1))
	{
		//����ƿ1й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,DISABLE);
	}
	
	else
	{
		//����ƿ1й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_gas_tank_O1==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O1==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O2==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O2==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O3==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O3==DECODE_GAS_O2))
	{
		//����ƿ2й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,DISABLE);
	}
	
	else
	{
		//����ƿ2й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_gas_tank_O1==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O1==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O2==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O2==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O3==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O3==DECODE_GAS_O3))
	{
		//����ƿ3й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,DISABLE);
	}
	
	else
	{
		//����ƿ3й©
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,ENABLE);
	}
	
	
	//��1���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,ENABLE);
	
	//��2���䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,ENABLE);
	
	//��3���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,ENABLE);
	
	//ȼ1���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,ENABLE);
	
	//ȼ2���䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,ENABLE);
	
	//ȼ3���䳬ѹ	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,ENABLE);
	
	//�����˿ط��������Ʒ���й©
	TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_main_valve_leak.faultdiagnosis_count=0;
	
	//�����˿ط��������Ʒ���й©
	TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_less_valve_leak.faultdiagnosis_count=0;
	
	//C���˿ط��������Ʒ���й©
	TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_C_all_valve_leak.faultdiagnosis_count=0;
	
	//A�������˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_main_valve_leak.faultdiagnosis_count=0;
	
	//A�鱸���˿ط��������Ʒ���й©
	TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//�ʼ첻ʹ��
	TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//����δ����
	TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//���ϲ��Բ�����
	TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//�����ʼ�
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_less_valve_leak.faultdiagnosis_count=0;
	
	//��1����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,ENABLE);
	
	//��2����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,ENABLE);
	
	//��3����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,ENABLE);
	
	//ȼ1����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,ENABLE);
	
	//ȼ2����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,ENABLE);
	
	//ȼ3����й©	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,ENABLE);
	
	
}


/******************************************************************************************
**���ƣ� ���������� ---�ƽ��ʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_other(void)
{
	TGTHT510_faultdiagnosis_push_set_stage_polling();
}


/******************************************************************************************
**���ƣ� ���ж� ---�ƽ��ʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_run(void)
{
	TGTHT510_faultdiagnosis_push_set_stage_polling();
}


/******************************************************************************************
**���ƣ� ����� ---���ӹʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_launch(void)
{
	//�������������
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,DISABLE);
	
	//����Һ�����ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,DISABLE);
	
	//����Һ�䱸�ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,DISABLE);
	
	//����Һ�����ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,DISABLE);
	
	//����Һ�䱸�ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,DISABLE);
	
	//����Һ��й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,DISABLE);
	
	//����Һ��й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,DISABLE);
	
	//ѹ����A��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,DISABLE);
	
	//ѹ����B��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,DISABLE);
	
	//ѹ����C��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,DISABLE);
	
	//ѹ����A���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,DISABLE);
	
	//ѹ����B���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,DISABLE);
	
	//ѹ����C���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,DISABLE);
	
	//ѹ����A����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,DISABLE);
	
	//ѹ����B����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,DISABLE);
	
	//ѹ����C����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,DISABLE);
	
	//��1�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,DISABLE);
	
	//��2�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,DISABLE);
	
	//��3�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,DISABLE);
	
	//ȼ1�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,DISABLE);
	
	//ȼ2�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,DISABLE);
	
	//ȼ3�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,DISABLE);
	
	//ѹ����AĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,DISABLE);
	
	//ѹ����BĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,DISABLE);
	
	//ѹ����CĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,DISABLE);
	
	//����ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,DISABLE);
	
	//����ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,DISABLE);
	
	//����ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,DISABLE);
	
	//ȼ��ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,DISABLE);
	
	//ȼ��ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,DISABLE);
	
	//ȼ��ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,DISABLE);
	
	//��1���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,DISABLE);
	
	//��2���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,DISABLE);
	
	//��3���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,DISABLE);
	
	//ȼ1���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,DISABLE);
	
	//ȼ2���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,DISABLE);
	
	//ȼ3���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,DISABLE);
	
	//���������¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,DISABLE);
	
	//ȼ�������¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,DISABLE);
	
	//�������ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,DISABLE);
	
	//�������ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,DISABLE);
	
	//ȼ�����ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,DISABLE);
	
	//ȼ�����ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,DISABLE);
	
	//ǰ��ȼ1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,DISABLE);
	
	//ǰ��ȼ2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,DISABLE);
	
	//ǰ����1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,DISABLE);
	
	//ǰ����2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,DISABLE);
	
	//����ȼ1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,DISABLE);
	
	//����ȼ2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,DISABLE);
	
	//������1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,DISABLE);
	
	//������2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,DISABLE);
	
	//��1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,DISABLE);
	
	//��2���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,DISABLE);
	
	//��3���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,DISABLE);
	
	
}


/******************************************************************************************
**���ƣ� ���� ---���ӹʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_orbit(void)
{
	TGTHT510_faultdiagnosis_supply_set_stage_launch();
}


/******************************************************************************************
**���ƣ� Ѳ��� ---���ӹʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_polling(void)
{
	//�������������
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,ENABLE);
	
	//����Һ�����ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,ENABLE);
	
	//����Һ�䱸�ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,ENABLE);
	
	//����Һ�����ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,ENABLE);
	
	//����Һ�䱸�ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,ENABLE);
	
	//����Һ��й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,DISABLE);
	
	//����Һ��й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,DISABLE);
	
	//ѹ����A��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,ENABLE);
	
	//ѹ����B��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,ENABLE);
	
	//ѹ����C��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,ENABLE);
	
	//ѹ����A���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,DISABLE);
	
	//ѹ����B���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,DISABLE);
	
	//ѹ����C���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,DISABLE);
	
	//ѹ����A����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,ENABLE);
	
	//ѹ����B����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,ENABLE);
	
	//ѹ����C����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,ENABLE);
	
	//��1�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,DISABLE);
	
	//��2�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,DISABLE);
	
	//��3�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,DISABLE);
	
	//ȼ1�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,DISABLE);
	
	//ȼ2�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,DISABLE);
	
	//ȼ3�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,DISABLE);
	
	//ѹ����AĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,DISABLE);
	
	//ѹ����BĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,DISABLE);
	
	//ѹ����CĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,DISABLE);
	
	//����ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,DISABLE);
	
	//����ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,DISABLE);
	
	//����ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,DISABLE);
	
	//ȼ��ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,DISABLE);
	
	//ȼ��ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,DISABLE);
	
	//ȼ��ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,DISABLE);
	
	//��1���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,DISABLE);
	
	//��2���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,DISABLE);
	
	//��3���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,DISABLE);
	
	//ȼ1���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,DISABLE);
	
	//ȼ2���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,DISABLE);
	
	//ȼ3���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,DISABLE);
	
	//���������¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,DISABLE);
	
	//ȼ�������¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,DISABLE);
	
	//�������ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,DISABLE);
	
	//�������ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,DISABLE);
	
	//ȼ�����ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,DISABLE);
	
	//ȼ�����ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,DISABLE);
	
	//ǰ��ȼ1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,DISABLE);
	
	//ǰ��ȼ2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,DISABLE);
	
	//ǰ����1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,DISABLE);
	
	//ǰ����2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,DISABLE);
	
	//����ȼ1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,DISABLE);
	
	//����ȼ2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,DISABLE);
	
	//������1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,DISABLE);
	
	//������2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,DISABLE);
	
	//��1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,DISABLE);
	
	//��2���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,DISABLE);
	
	//��3���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,DISABLE);
	
	
}


/******************************************************************************************
**���ƣ� ѹ���������� ---���ӹʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_gas(void)
{
	//�������������
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,DISABLE);
	
	//����Һ�����ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,DISABLE);
	
	//����Һ�䱸�ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,DISABLE);
	
	//����Һ�����ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,DISABLE);
	
	//����Һ�䱸�ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,DISABLE);
	
	//����Һ��й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,DISABLE);
	
	//����Һ��й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,DISABLE);
	
	//ѹ����A��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,ENABLE);
	
	//ѹ����B��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,ENABLE);
	
	//ѹ����C��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,ENABLE);
	
	//ѹ����A���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,DISABLE);
	
	//ѹ����B���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,DISABLE);
	
	//ѹ����C���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,DISABLE);
	
	//ѹ����A����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,DISABLE);
	
	//ѹ����B����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,DISABLE);
	
	//ѹ����C����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,DISABLE);
	
	//��1�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,DISABLE);
	
	//��2�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,DISABLE);
	
	//��3�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,DISABLE);
	
	//ȼ1�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,DISABLE);
	
	//ȼ2�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,DISABLE);
	
	//ȼ3�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,DISABLE);
	
	//ѹ����AĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,DISABLE);
	
	//ѹ����BĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,DISABLE);
	
	//ѹ����CĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,DISABLE);
	
	//����ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,DISABLE);
	
	//����ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,DISABLE);
	
	//����ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,DISABLE);
	
	//ȼ��ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,DISABLE);
	
	//ȼ��ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,DISABLE);
	
	//ȼ��ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,DISABLE);
	
	//��1���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,DISABLE);
	
	//��2���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,DISABLE);
	
	//��3���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,DISABLE);
	
	//ȼ1���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,DISABLE);
	
	//ȼ2���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,DISABLE);
	
	//ȼ3���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,DISABLE);
	
	//���������¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,DISABLE);
	
	//ȼ�������¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,DISABLE);
	
	//�������ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,DISABLE);
	
	//�������ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,DISABLE);
	
	//ȼ�����ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,DISABLE);
	
	//ȼ�����ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,DISABLE);
	
	//ǰ��ȼ1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,DISABLE);
	
	//ǰ��ȼ2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,DISABLE);
	
	//ǰ����1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,DISABLE);
	
	//ǰ����2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,DISABLE);
	
	//����ȼ1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,DISABLE);
	
	//����ȼ2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,DISABLE);
	
	//������1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,DISABLE);
	
	//������2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,DISABLE);
	
	//��1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,DISABLE);
	
	//��2���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,DISABLE);
	
	//��3���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,DISABLE);
	
	
}


/******************************************************************************************
**���ƣ� ���ӳ����� ---���ӹʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_comp(void)
{
	//�������������
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,ENABLE);
	
	//����Һ�����ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,ENABLE);
	
	//����Һ�䱸�ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,ENABLE);
	
	//����Һ�����ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,ENABLE);
	
	//����Һ�䱸�ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,ENABLE);
	
	//����Һ��й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,DISABLE);
	
	//����Һ��й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,DISABLE);
	
	//ѹ����A��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,ENABLE);
	
	//ѹ����B��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,ENABLE);
	
	//ѹ����C��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,ENABLE);
	
	//ѹ����A���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,DISABLE);
	
	//ѹ����B���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,DISABLE);
	
	//ѹ����C���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,DISABLE);
	
	//ѹ����A����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,ENABLE);
	
	//ѹ����B����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,ENABLE);
	
	//ѹ����C����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,ENABLE);
	
	//��1�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,ENABLE);
	
	//��2�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,ENABLE);
	
	//��3�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,ENABLE);
	
	//ȼ1�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,ENABLE);
	
	//ȼ2�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,ENABLE);
	
	//ȼ3�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,ENABLE);
	
	//ѹ����AĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,ENABLE);
	
	//ѹ����BĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,ENABLE);
	
	//ѹ����CĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,ENABLE);
	
	//����ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,ENABLE);
	
	//����ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,ENABLE);
	
	//����ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,ENABLE);
	
	//ȼ��ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,ENABLE);
	
	//ȼ��ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,ENABLE);
	
	//ȼ��ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,ENABLE);
	
	//��1���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,DISABLE);
	
	//��2���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,DISABLE);
	
	//��3���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,DISABLE);
	
	//ȼ1���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,DISABLE);
	
	//ȼ2���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,DISABLE);
	
	//ȼ3���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,DISABLE);
	
	//���������¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,DISABLE);
	
	//ȼ�������¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,DISABLE);
	
	//�������ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,DISABLE);
	
	//�������ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,DISABLE);
	
	//ȼ�����ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,DISABLE);
	
	//ȼ�����ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,DISABLE);
	
	//ǰ��ȼ1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,DISABLE);
	
	//ǰ��ȼ2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,DISABLE);
	
	//ǰ����1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,DISABLE);
	
	//ǰ����2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,DISABLE);
	
	//����ȼ1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,DISABLE);
	
	//����ȼ2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,DISABLE);
	
	//������1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,DISABLE);
	
	//������2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,DISABLE);
	
	//��1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,DISABLE);
	
	//��2���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,DISABLE);
	
	//��3���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,DISABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,DISABLE);
	
	
}


/******************************************************************************************
**���ƣ� ���������� ---���ӹʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_flow(void)
{
	//�������������
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,DISABLE);
	
	//����Һ�����ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,DISABLE);
	
	//����Һ�䱸�ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,DISABLE);
	
	//����Һ�����ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,DISABLE);
	
	//����Һ�䱸�ù���
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,DISABLE);
	
	//����Һ��й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,DISABLE);
	
	//����Һ��й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,DISABLE);
	
	//ѹ����A��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,DISABLE);
	
	//ѹ����B��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,DISABLE);
	
	//ѹ����C��ڳ�ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,DISABLE);
	
	//ѹ����A���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,DISABLE);
	
	//ѹ����B���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,DISABLE);
	
	//ѹ����C���ǻ��ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,DISABLE);
	
	//ѹ����A����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,DISABLE);
	
	//ѹ����B����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,DISABLE);
	
	//ѹ����C����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,DISABLE);
	
	//��1�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,DISABLE);
	
	//��2�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,DISABLE);
	
	//��3�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,DISABLE);
	
	//ȼ1�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,DISABLE);
	
	//ȼ2�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,DISABLE);
	
	//ȼ3�������䳬ѹ
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,DISABLE);
	
	//ѹ����AĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,DISABLE);
	
	//ѹ����BĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,DISABLE);
	
	//ѹ����CĤƬ����
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,DISABLE);
	
	//����ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,DISABLE);
	
	//����ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,DISABLE);
	
	//����ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,DISABLE);
	
	//ȼ��ƿ1й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,DISABLE);
	
	//ȼ��ƿ2й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,DISABLE);
	
	//ȼ��ƿ3й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,DISABLE);
	
	//��1���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,ENABLE);
	
	//��2���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,ENABLE);
	
	//��3���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,ENABLE);
	
	//ȼ1���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,ENABLE);
	
	//ȼ2���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,ENABLE);
	
	//ȼ3���䲹��Һ·й©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,ENABLE);
	
	//���������¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,ENABLE);
	
	//ȼ�������¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,ENABLE);
	
	//�������ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,ENABLE);
	
	//�������ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,ENABLE);
	
	//ȼ�����ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,ENABLE);
	
	//ȼ�����ӹ�·��©
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,ENABLE);
	
	//ǰ��ȼ1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,ENABLE);
	
	//ǰ��ȼ2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,ENABLE);
	
	//ǰ����1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,ENABLE);
	
	//ǰ����2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,ENABLE);
	
	//����ȼ1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,ENABLE);
	
	//����ȼ2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,ENABLE);
	
	//������1�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,ENABLE);
	
	//������2�����Ͻ����¶��쳣
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,ENABLE);
	
	//��1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,ENABLE);
	
	//��2���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,ENABLE);
	
	//��3���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,ENABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,ENABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,ENABLE);
	
	//ȼ1���俨��
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,ENABLE);
	
}

/******************************************************************************************
**���ƣ� ���Ӹ�ѹ�� ---���ӹʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_repre(void)
{
	TGTHT510_faultdiagnosis_supply_set_stage_launch();
}


/******************************************************************************************
**���ƣ� ���������� ---���ӹʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_other(void)
{
	TGTHT510_faultdiagnosis_supply_set_stage_launch();
}

/******************************************************************************************
**���ƣ� ���ж� ---���ӹʼ�ʹ�ܽ�ֹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_run(void)
{
	TGTHT510_faultdiagnosis_supply_set_stage_launch();
}




















  
