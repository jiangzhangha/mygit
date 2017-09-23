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
void TGTHT510_supply_stage12_blow_f_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://��ʼ
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_12_SUPPLY_BLOW_VALVE_ON;
			
			break;
		}
		
		//ȼ·��������
		case STEP_12_SUPPLY_BLOW_VALVE_ON:
		{
			if(TGTHT510_supply_stage12_blow_f_step_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_12_SUPPLY_IS_HYCT_TIME;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//�ȴ�������Ϣ���߳�ʱ
		case STEP_12_SUPPLY_IS_HYCT_TIME:
		{
			if(TGTHT510_supply_stage12_blow_f_step_is_hyct_time()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_12_SUPPLY_BLOW_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//ȼ·�������ر�
		case STEP_12_SUPPLY_BLOW_VALVE_OFF:
		{
			if(TGTHT510_supply_stage12_blow_f_step_valve_off()==TRUE)
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
**���ƣ�ȼ·��������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������

��������ֵTRUE����ʾ��ǰ�������
��������ֵFALSE����ʾ��ǰ����δ����

-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_stage12_blow_f_step_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_12_0001_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_12_0001_VALVE_ON_NO1:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_F,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0002_IS_VALVE_ON_NO1;
			
			break;
		}
		
		case COMMAND_12_0002_IS_VALVE_ON_NO1:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_F,1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0003_VALVE_ON_NO2;
			}
			
			else
			{
				//����ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_12_0003_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_F,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0004_IS_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_12_0004_IS_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_F,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0005_VALVE_ON_NO3;
			}
			
			else
			{
				//����ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_12_0005_VALVE_ON_NO3:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_F,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0006_IS_VALVE_ON_NO3;
			
			break;
		}
		
		case COMMAND_12_0006_IS_VALVE_ON_NO3:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_F,3)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0007_VALVE_ON_NO4;
			}
			
			else
			{
				//����ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_12_0007_VALVE_ON_NO4:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_F,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0008_IS_VALVE_ON_NO4;
			
			break;
		}
		
		case COMMAND_12_0008_IS_VALVE_ON_NO4:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_F,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0009_VALVE_ON_NO5;
			}
			
			else
			{
				//����ϵͳ���Ŵ��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_12_0009_VALVE_ON_NO5:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_F,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0010_IS_VALVE_ON_NO5;
			
			break;
		}
		
		case COMMAND_12_0010_IS_VALVE_ON_NO5:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_F,5)==TRUE)
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
**���ƣ�ȼ·�������ر�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������

��������ֵTRUE����ʾ��ǰ�������
��������ֵFALSE����ʾ��ǰ����δ����

-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_stage12_blow_f_step_is_hyct_time(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_12_0001_IS_HYCT_TIME;
			break;
		}
		
		case COMMAND_12_0001_IS_HYCT_TIME:
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
**���ƣ�ȼ·�������ر�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������

��������ֵTRUE����ʾ��ǰ�������
��������ֵFALSE����ʾ��ǰ����δ����

-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_stage12_blow_f_step_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://��ʼ
		{
			TGTHT510_supply_ctrl.command=COMMAND_12_0001_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_12_0001_VALVE_OFF_NO1:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_F,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0002_IS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_12_0002_IS_VALVE_OFF_NO1:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_F,1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0003_VALVE_OFF_NO2;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_12_0003_VALVE_OFF_NO2:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_F,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0004_IS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_12_0004_IS_VALVE_OFF_NO2:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_F,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0005_VALVE_OFF_NO3;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_12_0005_VALVE_OFF_NO3:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_F,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0006_IS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_12_0006_IS_VALVE_OFF_NO3:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_F,3)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0007_VALVE_OFF_NO4;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_12_0007_VALVE_OFF_NO4:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_F,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0008_IS_VALVE_OFF_NO4;
			
			break;
		}
		
		case COMMAND_12_0008_IS_VALVE_OFF_NO4:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_F,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0009_VALVE_OFF_NO5;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_12_0009_VALVE_OFF_NO5:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_F,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0010_IS_VALVE_OFF_NO5;
			
			break;
		}
		
		case COMMAND_12_0010_IS_VALVE_OFF_NO5:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_F,5)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0011_VALVE_OFF_NO6;
			}
			
			else
			{
				//����ϵͳ���Źر��쳣
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_12_0011_VALVE_OFF_NO6:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_F,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0012_IS_VALVE_OFF_NO6;
			
			break;
		}
		
		case COMMAND_12_0012_IS_VALVE_OFF_NO6:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_F,6)==TRUE)
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
**����: ͨ�ú���-ȼ·��������
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

void TGTHT510_supply_common_blow_valve_on(uint16 blow_kind,uint16 command_number)
{
	if(blow_kind==BLOW_TANK_F)
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb40K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb72K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb76K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb70K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb74K);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb50K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb68K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb78K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb70K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb74K);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb60K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb80K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb82K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb70K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb74K);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb64K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb84K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb86K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb70K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb74K);
					
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
	
	else if(blow_kind==BLOW_TANK_O)
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb39K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb69K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb73K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb71K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb75K);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb49K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb69K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb73K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb67K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb77K);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb59K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb69K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb73K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb79K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb81K);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb63K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb69K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb73K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb83K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb85K);
					
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
**����: ͨ�ú���-�ж�ȼ·��������
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

uint16 TGTHT510_supply_common_blow_is_valve_on(uint16 blow_kind,uint16 command_number)
{
	if(blow_kind==BLOW_TANK_F)
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb40,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb72,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb76,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb50,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb68,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb78,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb60,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb80,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb82,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb64,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb84,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb86,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else if(blow_kind==BLOW_TANK_O)
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb39,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb71,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb75,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb49,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb67,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb77,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb59,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb79,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb81,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb63,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb83,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb85,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
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
**����: ͨ�ú���-ȼ·�������ر�
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

void TGTHT510_supply_common_blow_valve_off(uint16 blow_kind,uint16 command_number)
{
	if(blow_kind==BLOW_TANK_F)
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb70G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb74G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb72G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb76G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb40G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb50G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb70G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb74G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb68G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb78G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb40G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb50G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb70G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb74G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb80G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb82G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb60G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb64G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb70G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb74G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb84G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb86G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb60G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb64G);
					
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
	
	else if(blow_kind==BLOW_TANK_O)
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb69G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb73G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb71G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb75G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb39G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb49G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb69G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb73G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb67G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb77G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb39G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb49G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb69G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb73G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb79G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb81G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb59G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb63G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb69G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb73G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb83G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb85G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb59G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb63G);
					
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
**����: ͨ�ú���-ȼ·�������ر�
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

uint16 TGTHT510_supply_common_blow_is_valve_off(uint16 blow_kind,uint16 command_number)
{
	if(blow_kind==BLOW_TANK_F)
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb72,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb76,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb40,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb50,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb68,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb78,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb40,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb50,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb80,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb82,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb60,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb64,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb84,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb86,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb60,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb64,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else if(blow_kind==BLOW_TANK_O)
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb71,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb75,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb39,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb49,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb67,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb77,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb39,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb49,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb79,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb81,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb59,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb63,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb83,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb85,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb59,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb63,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
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
**����: ͨ�ú���-�жϴ����Ƿ����
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

uint16 TGTHT510_supply_common_is_blow_over(void)
{
	//���������䣬�����жϻ������͵���Ϣ�������жϵ�ʱ������������
	
	uint32 time_val;
	
	TGTHT510_supply_time_stage_get(&time_val);
	
	if(time_val>=(uint32)(4*TGTHT510_supply_input_par.time_delay_long))
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}







