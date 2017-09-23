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

TGTHT510_supply_ctrl_TypeDef TGTHT510_supply_ctrl;

TGTHT510_supply_input_par_TypeDef TGTHT510_supply_input_par;

TGTHT510_supply_time_TypeDef TGTHT510_supply_time;

TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;

compressor_state_TypeDef compressor_state;


extern valvecontrol_TypeDef TGTHT510_valvecontrol_struct;	//���ſ��ƽṹ��
extern uint16 TGTHT510_1553B_data_TGTHT100[];				//ȫ�����飬�����ƽ�ң����·�г��¶Ȳ����������ݣ�89��
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[];		//ȫ�����飬�����ƽ�ң����·�и�֡A�¶����ݣ�65��
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[];		//ȫ�����飬�����ƽ�ң����·�и�֡B�¶����ݣ�65��
extern uint16 TGTHT510_1553B_data_TGTHT530[];				//ȫ�����飬����ѹ�������������ң�����ݣ�14��
extern uint16 TGTHT510_1553B_data_TGTHT520a[];				//ȫ�����飬�����ƽ���������������ң�⣬7��
extern uint16 TGTHT510_1553B_data_TGTHT520b[];				//ȫ�����飬�����ƽ���������������ң�⣬7��
extern uint16 TGTHT510_1553B_R_HYCT1100[];					//ȫ�����飬����������͵�ң������

extern CPU_B_receive_data_TypeDef CPU_B_receive_data;

//��·�ƽ�����������������״̬��ѯ��
uint16 valve_state_TGTHT520a_lookup[TGTHT510A_NUMBER]={
	TGTHT520_L_BYTE_L_BIT,//LVt09���ſ���״̬
	TGTHT520_L_BYTE_H_BIT,//LVt11���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt01���ſ���״̬
	TGTHT520_H_BYTE_H_BIT,//LVt07���ſ���״̬
	TGTHT520_L_BYTE_L_BIT,//LVt43���ſ���״̬
	TGTHT520_L_BYTE_H_BIT,//LVt45���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt31���ſ���״̬
	TGTHT520_H_BYTE_H_BIT,//LVt37���ſ���״̬
	TGTHT520_L_BYTE_L_BIT,//LVt08���ſ���״̬
	TGTHT520_L_BYTE_H_BIT,//LVt10���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt51���ſ���״̬
	TGTHT520_H_BYTE_H_BIT,//LVt02���ſ���״̬
	TGTHT520_L_BYTE_L_BIT,//LVt38���ſ���״̬
	TGTHT520_L_BYTE_H_BIT,//LVt44���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt12���ſ���״̬
	TGTHT520_H_BYTE_H_BIT,//LVt32���ſ���״̬
	TGTHT520_L_BYTE_L_BIT,//LVt03���ſ���״̬
	TGTHT520_L_BYTE_H_BIT,//LVt20���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt46���ſ���״̬
	TGTHT520_H_BYTE_H_BIT,//LVt52���ſ���״̬
	TGTHT520_L_BYTE_L_BIT,//LVt35���ſ���״̬
	TGTHT520_L_BYTE_H_BIT,//LVt19���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt24���ſ���״̬
	TGTHT520_H_BYTE_H_BIT,//LVt27���ſ���״̬
	TGTHT520_L_BYTE_L_BIT,//LVt36���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt23���ſ���״̬
	TGTHT520_H_BYTE_H_BIT //LVt28���ſ���״̬
};

uint16 valve_word_TGTHT520a_lookup[TGTHT510A_NUMBER]={
	0,0,0,0,
	1,1,1,1,
	2,2,2,2,
	3,3,3,3,
	4,4,4,4,
	5,5,5,5,
	6,6,6
};


//��·�ƽ�����������������״̬��ѯ��
uint16 valve_state_TGTHT520b_lookup[TGTHT510B_NUMBER]={
	TGTHT520_L_BYTE_L_BIT,//LVt18���ſ���״̬
	TGTHT520_L_BYTE_H_BIT,//LVt22���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt06���ſ���״̬
	TGTHT520_H_BYTE_H_BIT,//LVt16���ſ���״̬
	TGTHT520_L_BYTE_L_BIT,//LVt29���ſ���״̬
	TGTHT520_L_BYTE_H_BIT,//LVt39���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt26���ſ���״̬
	TGTHT520_H_BYTE_H_BIT,//LVt13���ſ���״̬
	TGTHT520_L_BYTE_L_BIT,//LVt15���ſ���״̬
	TGTHT520_L_BYTE_H_BIT,//LVt17���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt41���ſ���״̬
	TGTHT520_H_BYTE_H_BIT,//LVt05���ſ���״̬
	TGTHT520_L_BYTE_L_BIT,//LVt34���ſ���״̬
	TGTHT520_L_BYTE_H_BIT,//LVt48���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt21���ſ���״̬
	TGTHT520_H_BYTE_H_BIT,//LVt25���ſ���״̬
	TGTHT520_L_BYTE_L_BIT,//LVt33���ſ���״̬
	TGTHT520_L_BYTE_H_BIT,//LVt47���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt50���ſ���״̬
	TGTHT520_H_BYTE_H_BIT,//LVt54���ſ���״̬
	TGTHT520_L_BYTE_L_BIT,//LVt04���ſ���״̬
	TGTHT520_L_BYTE_H_BIT,//LVt14���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt49���ſ���״̬
	TGTHT520_H_BYTE_H_BIT,//LVt53���ſ���״̬
	TGTHT520_L_BYTE_L_BIT,//LVt42���ſ���״̬
	TGTHT520_H_BYTE_L_BIT,//LVt30���ſ���״̬
	TGTHT520_H_BYTE_H_BIT //LVt40���ſ���״̬
};

uint16 valve_word_TGTHT520b_lookup[TGTHT510B_NUMBER]={
	0,0,0,0,
	1,1,1,1,
	2,2,2,2,
	3,3,3,3,
	4,4,4,4,
	5,5,5,5,
	6,6,6
};


/******************************************************************************************
**���ƣ����ӽ׶γ�ʼ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_supply_main_initial(void)
{
	TGTHT510_supply_time.time_stage_flag=FALSE;
	TGTHT510_supply_time.time_step_flag=FALSE;
	TGTHT510_supply_time.time_stage=0;
	TGTHT510_supply_time.time_step=0;
	
//ע�벹�Ӳ������仯-----------------------------------------------------------
	TGTHT510_supply_input_par.interface_F=0;
	TGTHT510_supply_input_par.interface_O=0;
	TGTHT510_supply_input_par.sequence_tank_F=0;
	TGTHT510_supply_input_par.sequence_tank_O=0;
	TGTHT510_supply_input_par.sequence_gas_F1=0;
	TGTHT510_supply_input_par.sequence_gas_F2=0;
	TGTHT510_supply_input_par.sequence_gas_F3=0;
	TGTHT510_supply_input_par.sequence_gas_O1=0;
	TGTHT510_supply_input_par.sequence_gas_O2=0;
	TGTHT510_supply_input_par.sequence_gas_O3=0;
	TGTHT510_supply_input_par.compressor_out_valve=0;
	TGTHT510_supply_input_par.pressure_first_F1=0;
	TGTHT510_supply_input_par.pressure_second_F1=0;
	TGTHT510_supply_input_par.pressure_first_F2=0;
	TGTHT510_supply_input_par.pressure_second_F2=0;
	TGTHT510_supply_input_par.pressure_first_F3=0;
	TGTHT510_supply_input_par.pressure_second_F3=0;
	TGTHT510_supply_input_par.pressure_first_O1=0;
	TGTHT510_supply_input_par.pressure_second_O1=0;
	TGTHT510_supply_input_par.pressure_first_O2=0;
	TGTHT510_supply_input_par.pressure_second_O2=0;
	TGTHT510_supply_input_par.pressure_first_O3=0;
	TGTHT510_supply_input_par.pressure_second_O3=0;
	TGTHT510_supply_input_par.pump_cooler=0;
	TGTHT510_supply_input_par.volum_F1=0;
	TGTHT510_supply_input_par.volum_F2=0;
	TGTHT510_supply_input_par.volum_F3=0;
	TGTHT510_supply_input_par.volum_O1=0;
	TGTHT510_supply_input_par.volum_O2=0;
	TGTHT510_supply_input_par.volum_O3=0;
	TGTHT510_supply_input_par.mode=0;
	TGTHT510_supply_input_par.pressure_repre_F1=0;
	TGTHT510_supply_input_par.pressure_repre_F2=0;
	TGTHT510_supply_input_par.pressure_repre_F3=0;
	TGTHT510_supply_input_par.pressure_repre_O1=0;
	TGTHT510_supply_input_par.pressure_repre_O2=0;
	TGTHT510_supply_input_par.pressure_repre_O3=0;
	
//ע�벹�Ӳ������̶�-----------------------------------------------------------
	
	TGTHT510_supply_input_par.time_exhaust=CONST_TIME_1MIN;
	TGTHT510_supply_input_par.time_comp_max=CONST_MAX_COMP_TIME;
	TGTHT510_supply_input_par.velocity_max=0;
	TGTHT510_supply_input_par.velocity_min=0;
	TGTHT510_supply_input_par.time_flow_max=0;
	TGTHT510_supply_input_par.temperature_mode=0;
	TGTHT510_supply_input_par.temperature_start_min=0x0010;//�ݶ�
	TGTHT510_supply_input_par.temperature_start_max=0x0080;//�ݶ�
	TGTHT510_supply_input_par.temperature_alarm=0;
	TGTHT510_supply_input_par.temperature_comp_cooler=0;
	TGTHT510_supply_input_par.pressure_comp_out=0;
	TGTHT510_supply_input_par.pressure_comp_out_stop=0;
	TGTHT510_supply_input_par.dp_high=0;
	TGTHT510_supply_input_par.dp1_low=30;
	TGTHT510_supply_input_par.dp2_low=0;
	TGTHT510_supply_input_par.time_repre_max=0x0960;//��ѹʱ�䣬�ݶ�20min
	TGTHT510_supply_input_par.v_comp_start=0;
	TGTHT510_supply_input_par.v_comp_stop=0;
	TGTHT510_supply_input_par.time_delay_short=CONST_TIME_10SEC;
	TGTHT510_supply_input_par.time_delay_long=CONST_TIME_1MIN;
	TGTHT510_supply_input_par.time_bypath=CONST_TIME_10SEC;
	TGTHT510_supply_input_par.eps1=0xFF00;
	TGTHT510_supply_input_par.eps2=20;
	TGTHT510_supply_input_par.pressure_comp_in_max=0;
	TGTHT510_supply_input_par.pressure_comp_in_min=0;
	TGTHT510_supply_input_par.pressure_comp_out_min=0;
	TGTHT510_supply_input_par.pressure_hyc=0x0004;
	TGTHT510_supply_input_par.sensor_pipe_F=0;
	TGTHT510_supply_input_par.sensor_pipe_O=0;
	TGTHT510_supply_input_par.sensor_tank_F=0x0015;
	TGTHT510_supply_input_par.sensor_tank_O=0x0015;
	TGTHT510_supply_input_par.sensor_comp_in=0x0015;
	TGTHT510_supply_input_par.sensor_pipe_low=0;

//ע����룬------------------------------------------------------------------
	
	TGTHT510_supply_decode_par.interface_F=DECODE_NONE;
	TGTHT510_supply_decode_par.interface_O=DECODE_NONE;
	TGTHT510_supply_decode_par.number_tank_F=DECODE_NONE;
	TGTHT510_supply_decode_par.first_tank_F=DECODE_NONE;
	TGTHT510_supply_decode_par.second_tank_F=DECODE_NONE;
	TGTHT510_supply_decode_par.third_tank_F=DECODE_NONE;
	TGTHT510_supply_decode_par.number_tank_O=DECODE_NONE;
	TGTHT510_supply_decode_par.first_tank_O=DECODE_NONE;
	TGTHT510_supply_decode_par.second_tank_O=DECODE_NONE;
	TGTHT510_supply_decode_par.third_tank_O=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_F1=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_F1=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_F2=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_F2=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_F3=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_F3=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_O1=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_O1=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_O2=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_O2=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_O3=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_O3=DECODE_NONE;
	TGTHT510_supply_decode_par.compressor_F=DECODE_NONE;
	TGTHT510_supply_decode_par.compressor_O=DECODE_NONE;
	TGTHT510_supply_decode_par.valve_out_compressor_F=DECODE_NONE;
	TGTHT510_supply_decode_par.valve_out_compressor_O=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_F1=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_F2=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_F3=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_O1=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_O2=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_O3=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_pipe_low_F=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_pipe_low_O=DECODE_NONE;
	TGTHT510_supply_decode_par.cooler=DECODE_NONE;


//ע����Ʋ���------------------------------------------------------------------

	TGTHT510_supply_ctrl.mode=MODE_HALF_AUTO;
	TGTHT510_supply_ctrl.state=STATE_NONE;
	TGTHT510_supply_ctrl.stage=STAGE_00_NONE;
	TGTHT510_supply_ctrl.step=STEP_NONE;
	TGTHT510_supply_ctrl.command=COMMAND_NONE;
	TGTHT510_supply_ctrl.receive=FALSE;
	TGTHT510_supply_ctrl.leak_flag=FALSE;
	TGTHT510_supply_ctrl.errno=ERRNO_NONE;
	TGTHT510_supply_ctrl.step_temp=STEP_NONE;
	TGTHT510_supply_ctrl.command_temp=COMMAND_NONE;

//ѹ��������״̬
	compressor_state.compressor_A_state=COMPRESSOR_STOP;
	compressor_state.compressor_B_state=COMPRESSOR_STOP;
	compressor_state.compressor_C_state=COMPRESSOR_STOP;
}


/******************************************************************************************
**���ƣ����ӽ׶�������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_supply_main(void)
{
	if(get_CPU()==CPU_B)//B��
	{
		if(CPU_B_receive_data.is_B_get_power==FALSE)
		{
			return;//B������δ��Ȩ���򲹼����̲���
		}
		
	}
	
	TGTHT510_supply_time_dealing();//���ӹ��̼�ʱ�ֺ���
	
	switch(TGTHT510_supply_ctrl.mode)
	{
		case MODE_AUTO://�Զ�����ģʽ
		{
			
			break;
		}
		
		case MODE_HALF_AUTO://���Զ�����ģʽ
		{
			TGTHT510_supply_main_half_auto();
			break;
		}
		
		case MODE_MAN_MADE://�ֶ�����ģʽ
		{
			
			break;
		}
		
		case MODE_NONE://��
		{
			
			break;
		}
		
		default:
		{
			break;
		}
		
		
	}

}

/******************************************************************************************
**���ƣ����������ӽ׶�������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_main_half_auto(void)
{
	
	switch(TGTHT510_supply_ctrl.state)
	{
		case STATE_RUN://��������
		{
			TGTHT510_supply_main_run();
			break;
		}
		
		case STATE_PAUSE://������ͣ
		{
			TGTHT510_supply_main_pause_deal();
			
			break;
		}
		
		case STATE_PAUSE_RESUME://��ͣ�ָ�
		{
			TGTHT510_supply_main_pause_resume_deal();
			
			break;
		}
		
		case STATE_BREAK://������ֹ
		{
			TGTHT510_supply_main_break_deal();
			
			break;
		}
		
		case STATE_NONE://δ����
		{
			
			break;
		}
	}
	
}

/******************************************************************************************
**���ƣ���������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_main_run(void)
{
	switch(TGTHT510_supply_ctrl.stage)
	{
		case STAGE_00_NONE://���ӽ׶�0������
		{
			
			break;
		}
		
		case STAGE_01_INPUT://���ӽ׶�1��ע�벹�Ӳ���
		{
			TGTHT510_supply_stage01_input_main();
			break;
		}
		
		case STAGE_02_SET://���ӽ׶�2��״̬����
		{
			TGTHT510_supply_stage02_set_main();
			break;
		}
		
		case STAGE_03_CONNECT://���ӽ׶�3�������Ͻ������
		{
			TGTHT510_supply_stage03_connect_main();
			break;
		}
		
		case STAGE_04_LEAK://���ӽ׶�4�����ӹ�·��©
		{
			TGTHT510_supply_stage04_leak_main();
			break;
		}
		
		case STAGE_05_COMP_F://���ӽ׶�5��ȼ�������
		{
			TGTHT510_supply_stage05_comp_F_main();
			break;
		}
		
		case STAGE_06_PRE_F://���ӽ׶�6��ȼ������ѹ����
		{
			TGTHT510_supply_stage06_pre_f_main();
			break;
		}
		
		case STAGE_07_FLOW_F://���ӽ׶�7��ȼ�ƽ�����������
		{
			TGTHT510_supply_stage07_flow_f_main();
			break;
		}
		
		case STAGE_08_REPRE_F://���ӽ׶�8��ȼ���临ѹ
		{
			TGTHT510_supply_stage08_repre_f_main();
			break;
		}
		
		case STAGE_09_COMP_F_T://���ӽ׶�9��������ȼ�������
		{
			TGTHT510_supply_stage09_comp_F_main();
			break;
		}
		
		case STAGE_10_FLOW_F_T://���ӽ׶�10��������ȼ���䲹������
		{
			TGTHT510_supply_stage10_flow_f_main();
			break;
		}
		
		case STAGE_11_REPRE_F_T://���ӽ׶�11��������ȼ���临ѹ
		{
			TGTHT510_supply_stage11_repre_f_main();
			break;
		}
		
		case STAGE_12_BLOW_F://���ӽ׶�12��ȼ��·����
		{
			TGTHT510_supply_stage12_blow_f_main();
			break;
		}
		
		case STAGE_13_COMP_O://���ӽ׶�13�����������
		{
			TGTHT510_supply_stage13_comp_O_main();
			break;
		}
		
		case STAGE_14_PRE_O://���ӽ׶�14����������ѹ����
		{
			TGTHT510_supply_stage14_pre_o_main();
			break;
		}
		
		case STAGE_15_FLOW_O://���ӽ׶�15�����ƽ�����������
		{
			TGTHT510_supply_stage15_flow_o_main();
			break;
		}
		
		case STAGE_16_REPRE_O://���ӽ׶�16�������临ѹ
		{
			TGTHT510_supply_stage16_repre_o_main();
			break;
		}
		
		case STAGE_17_COMP_O_T://���ӽ׶�17�����������������
		{
			TGTHT510_supply_stage17_comp_O_main();
			break;
		}
		
		case STAGE_18_FLOW_O_T://���ӽ׶�18�������������䲹������
		{
			TGTHT510_supply_stage18_flow_o_main();
			break;
		}
		
		case STAGE_19_REPRE_O_T://���ӽ׶�19�������������临ѹ
		{
			TGTHT510_supply_stage19_repre_o_main();
			break;
		}
		
		case STAGE_20_BLOW_O://���ӽ׶�20������·����
		{
			TGTHT510_supply_stage20_blow_o_main();
			break;
		}
		
		case STAGE_21_DISCONNECT://���ӽ׶�21�������Ͻ����ѿ�
		{
			TGTHT510_supply_stage21_disconnect_main();
			break;
		}
		
		case STAGE_22_RESUME://���ӽ׶�22��״̬�ָ�
		{
			TGTHT510_supply_stage22_resume_main();
			break;
		}
		
		default:
		{
			TGTHT510_supply_ctrl.state=STATE_NONE;//����״̬������
			
			TGTHT510_supply_ctrl.stage=STAGE_00_NONE;//���ӽ׶Σ���
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//���Ӳ��裺��
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//����ָ���
			
			break;
		}
		
		
	}

	
}



/******************************************************************************************
**���ƣ�������ͣ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_main_pause_deal(void)
{
	switch(TGTHT510_supply_ctrl.stage)
	{
		case STAGE_00_NONE://���ӽ׶�0������
		{
			
			
			break;
		}
		
		case STAGE_01_INPUT://���ӽ׶�1��ע�벹�Ӳ���
		{
			TGTHT510_supply_pause_stage01_main();
			
			break;
		}
		
		case STAGE_02_SET://���ӽ׶�2��״̬����
		{
			TGTHT510_supply_pause_stage02_main();
			
			break;
		}
		
		case STAGE_03_CONNECT://���ӽ׶�3�������Ͻ������
		{
			TGTHT510_supply_pause_stage03_main();
			
			break;
		}
		
		case STAGE_04_LEAK://���ӽ׶�4�����ӹ�·��©
		{
			TGTHT510_supply_pause_stage04_main();
			
			break;
		}
		
		case STAGE_05_COMP_F://���ӽ׶�5��ȼ�������
		{
			TGTHT510_supply_pause_stage05_main();
			
			break;
		}
		
		case STAGE_06_PRE_F://���ӽ׶�6��ȼ������ѹ����
		{
			TGTHT510_supply_pause_stage06_main();
			
			break;
		}
		
		case STAGE_07_FLOW_F://���ӽ׶�7��ȼ�ƽ�����������
		{
			TGTHT510_supply_pause_stage07_main();
			
			break;
		}
		
		case STAGE_08_REPRE_F://���ӽ׶�8��ȼ���临ѹ
		{
			TGTHT510_supply_pause_stage08_main();
			
			break;
		}
		
		case STAGE_09_COMP_F_T://���ӽ׶�9��������ȼ�������
		{
			TGTHT510_supply_pause_stage09_main();
			
			break;
		}
		
		case STAGE_10_FLOW_F_T://���ӽ׶�10��������ȼ���䲹������
		{
			TGTHT510_supply_pause_stage10_main();
			
			break;
		}
		
		case STAGE_11_REPRE_F_T://���ӽ׶�11��������ȼ���临ѹ
		{
			TGTHT510_supply_pause_stage11_main();
			
			break;
		}
		
		case STAGE_12_BLOW_F://���ӽ׶�12��ȼ��·����
		{
			TGTHT510_supply_pause_stage12_main();
			
			break;
		}
		
		case STAGE_13_COMP_O://���ӽ׶�13�����������
		{
			TGTHT510_supply_pause_stage13_main();
			
			break;
		}
		
		case STAGE_14_PRE_O://���ӽ׶�14����������ѹ����
		{
			TGTHT510_supply_pause_stage14_main();
			
			break;
		}
		
		case STAGE_15_FLOW_O://���ӽ׶�15�����ƽ�����������
		{
			TGTHT510_supply_pause_stage15_main();
			
			break;
		}
		
		case STAGE_16_REPRE_O://���ӽ׶�16�������临ѹ
		{
			TGTHT510_supply_pause_stage16_main();
			
			break;
		}
		
		case STAGE_17_COMP_O_T://���ӽ׶�17�����������������
		{
			TGTHT510_supply_pause_stage17_main();
			
			break;
		}
		
		case STAGE_18_FLOW_O_T://���ӽ׶�18�������������䲹������
		{
			TGTHT510_supply_pause_stage18_main();
			
			break;
		}
		
		case STAGE_19_REPRE_O_T://���ӽ׶�19�������������临ѹ
		{
			TGTHT510_supply_pause_stage19_main();
			
			break;
		}
		
		case STAGE_20_BLOW_O://���ӽ׶�20������·����
		{
			TGTHT510_supply_pause_stage20_main();
			
			break;
		}
		
		case STAGE_21_DISCONNECT://���ӽ׶�21�������Ͻ����ѿ�
		{
			TGTHT510_supply_pause_stage21_main();
			
			break;
		}
		
		case STAGE_22_RESUME://���ӽ׶�22��״̬�ָ�
		{
			TGTHT510_supply_pause_stage22_main();
			
			break;
		}
		
		default:
		{
			TGTHT510_supply_ctrl.state=STATE_NONE;//����״̬������
			
			TGTHT510_supply_ctrl.stage=STAGE_00_NONE;//���ӽ׶Σ���
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//���Ӳ��裺��
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//����ָ���
			
			break;
		}
		
		
	}

	
}


/******************************************************************************************
**���ƣ����ӻָ�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_main_pause_resume_deal(void)
{
	switch(TGTHT510_supply_ctrl.stage)
	{
		case STAGE_00_NONE://���ӽ׶�0������
		{
			
			
			break;
		}
		
		case STAGE_01_INPUT://���ӽ׶�1��ע�벹�Ӳ���
		{
			TGTHT510_supply_pause_resume_stage01_main();
			
			break;
		}
		
		case STAGE_02_SET://���ӽ׶�2��״̬����
		{
			TGTHT510_supply_pause_resume_stage02_main();
			
			break;
		}
		
		case STAGE_03_CONNECT://���ӽ׶�3�������Ͻ������
		{
			TGTHT510_supply_pause_resume_stage03_main();
			
			break;
		}
		
		case STAGE_04_LEAK://���ӽ׶�4�����ӹ�·��©
		{
			TGTHT510_supply_pause_resume_stage04_main();
			
			break;
		}
		
		case STAGE_05_COMP_F://���ӽ׶�5��ȼ�������
		{
			TGTHT510_supply_pause_resume_stage05_main();
			
			break;
		}
		
		case STAGE_06_PRE_F://���ӽ׶�6��ȼ������ѹ����
		{
			TGTHT510_supply_pause_resume_stage06_main();
			
			break;
		}
		
		case STAGE_07_FLOW_F://���ӽ׶�7��ȼ�ƽ�����������
		{
			TGTHT510_supply_pause_resume_stage07_main();
			
			break;
		}
		
		case STAGE_08_REPRE_F://���ӽ׶�8��ȼ���临ѹ
		{
			TGTHT510_supply_pause_resume_stage08_main();
			
			break;
		}
		
		case STAGE_09_COMP_F_T://���ӽ׶�9��������ȼ�������
		{
			TGTHT510_supply_pause_resume_stage09_main();
			
			break;
		}
		
		case STAGE_10_FLOW_F_T://���ӽ׶�10��������ȼ���䲹������
		{
			TGTHT510_supply_pause_resume_stage10_main();
			
			break;
		}
		
		case STAGE_11_REPRE_F_T://���ӽ׶�11��������ȼ���临ѹ
		{
			TGTHT510_supply_pause_resume_stage11_main();
			
			break;
		}
		
		case STAGE_12_BLOW_F://���ӽ׶�12��ȼ��·����
		{
			TGTHT510_supply_pause_resume_stage12_main();
			
			break;
		}
		
		case STAGE_13_COMP_O://���ӽ׶�13�����������
		{
			TGTHT510_supply_pause_resume_stage13_main();
			
			break;
		}
		
		case STAGE_14_PRE_O://���ӽ׶�14����������ѹ����
		{
			TGTHT510_supply_pause_resume_stage14_main();
			
			break;
		}
		
		case STAGE_15_FLOW_O://���ӽ׶�15�����ƽ�����������
		{
			TGTHT510_supply_pause_resume_stage15_main();
			
			break;
		}
		
		case STAGE_16_REPRE_O://���ӽ׶�16�������临ѹ
		{
			TGTHT510_supply_pause_resume_stage16_main();
			
			break;
		}
		
		case STAGE_17_COMP_O_T://���ӽ׶�17�����������������
		{
			TGTHT510_supply_pause_resume_stage17_main();
			
			break;
		}
		
		case STAGE_18_FLOW_O_T://���ӽ׶�18�������������䲹������
		{
			TGTHT510_supply_pause_resume_stage18_main();
			
			break;
		}
		
		case STAGE_19_REPRE_O_T://���ӽ׶�19�������������临ѹ
		{
			TGTHT510_supply_pause_resume_stage19_main();
			
			break;
		}
		
		case STAGE_20_BLOW_O://���ӽ׶�20������·����
		{
			TGTHT510_supply_pause_resume_stage20_main();
			
			break;
		}
		
		case STAGE_21_DISCONNECT://���ӽ׶�21�������Ͻ����ѿ�
		{
			TGTHT510_supply_pause_resume_stage21_main();
			
			break;
		}
		
		case STAGE_22_RESUME://���ӽ׶�22��״̬�ָ�
		{
			TGTHT510_supply_pause_resume_stage22_main();
			
			break;
		}
		
		default:
		{
			TGTHT510_supply_ctrl.state=STATE_NONE;//����״̬������
			
			TGTHT510_supply_ctrl.stage=STAGE_00_NONE;//���ӽ׶Σ���
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//���Ӳ��裺��
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//����ָ���
			
			break;
		}
		
		
	}

	
}


/******************************************************************************************
**���ƣ�������ֹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_main_break_deal(void)
{
	switch(TGTHT510_supply_ctrl.stage)
	{
		case STAGE_00_NONE://���ӽ׶�0������
		{
			
			
			break;
		}
		
		case STAGE_01_INPUT://���ӽ׶�1��ע�벹�Ӳ���
		{
			TGTHT510_supply_break_stage01_main();

			
			break;
		}
		
		case STAGE_02_SET://���ӽ׶�2��״̬����
		{
			TGTHT510_supply_break_stage02_main();

			
			break;
		}
		
		case STAGE_03_CONNECT://���ӽ׶�3�������Ͻ������
		{
			TGTHT510_supply_break_stage03_main();
			
			break;
		}
		
		case STAGE_04_LEAK://���ӽ׶�4�����ӹ�·��©
		{
			TGTHT510_supply_break_stage04_main();
			
			break;
		}
		
		case STAGE_05_COMP_F://���ӽ׶�5��ȼ�������
		{
			TGTHT510_supply_break_stage05_main();
			
			break;
		}
		
		case STAGE_06_PRE_F://���ӽ׶�6��ȼ������ѹ����
		{
			TGTHT510_supply_break_stage06_main();
			
			break;
		}
		
		case STAGE_07_FLOW_F://���ӽ׶�7��ȼ�ƽ�����������
		{
			TGTHT510_supply_break_stage07_main();
			
			break;
		}
		
		case STAGE_08_REPRE_F://���ӽ׶�8��ȼ���临ѹ
		{
			TGTHT510_supply_break_stage08_main();
			
			break;
		}
		
		case STAGE_09_COMP_F_T://���ӽ׶�9��������ȼ�������
		{
			TGTHT510_supply_break_stage09_main();
			
			break;
		}
		
		case STAGE_10_FLOW_F_T://���ӽ׶�10��������ȼ���䲹������
		{
			TGTHT510_supply_break_stage10_main();
			
			break;
		}
		
		case STAGE_11_REPRE_F_T://���ӽ׶�11��������ȼ���临ѹ
		{
			TGTHT510_supply_break_stage11_main();
			
			break;
		}
		
		case STAGE_12_BLOW_F://���ӽ׶�12��ȼ��·����
		{
			TGTHT510_supply_break_stage12_main();
			
			break;
		}
		
		case STAGE_13_COMP_O://���ӽ׶�13�����������
		{
			TGTHT510_supply_break_stage13_main();
			
			break;
		}
		
		case STAGE_14_PRE_O://���ӽ׶�14����������ѹ����
		{
			TGTHT510_supply_break_stage14_main();
			
			break;
		}
		
		case STAGE_15_FLOW_O://���ӽ׶�15�����ƽ�����������
		{
			TGTHT510_supply_break_stage15_main();
			
			break;
		}
		
		case STAGE_16_REPRE_O://���ӽ׶�16�������临ѹ
		{
			TGTHT510_supply_break_stage16_main();
			
			break;
		}
		
		case STAGE_17_COMP_O_T://���ӽ׶�17�����������������
		{
			TGTHT510_supply_break_stage17_main();
			
			break;
		}
		
		case STAGE_18_FLOW_O_T://���ӽ׶�18�������������䲹������
		{
			TGTHT510_supply_break_stage18_main();
			
			break;
		}
		
		case STAGE_19_REPRE_O_T://���ӽ׶�19�������������临ѹ
		{
			TGTHT510_supply_break_stage19_main();
			
			break;
		}
		
		case STAGE_20_BLOW_O://���ӽ׶�20������·����
		{
			TGTHT510_supply_break_stage20_main();
			
			break;
		}
		
		case STAGE_21_DISCONNECT://���ӽ׶�21�������Ͻ����ѿ�
		{
			TGTHT510_supply_break_stage21_main();
			
			break;
		}
		
		case STAGE_22_RESUME://���ӽ׶�22��״̬�ָ�
		{
			TGTHT510_supply_break_stage22_main();
			
			break;
		}
		
		default:
		{
			TGTHT510_supply_ctrl.state=STATE_NONE;//����״̬������
			
			TGTHT510_supply_ctrl.stage=STAGE_00_NONE;//���ӽ׶Σ���
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//���Ӳ��裺��
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//����ָ���
			
			break;
		}
		
		
	}

	
}








/******************************************************************************************
**���ƣ�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_main_pause(uint16 errno)
{
	TGTHT510_supply_ctrl.errno=errno;
	
	TGTHT510_supply_ctrl.step_temp=TGTHT510_supply_ctrl.step;
	
	TGTHT510_supply_ctrl.command_temp=TGTHT510_supply_ctrl.command;
	
	TGTHT510_supply_ctrl.state=STATE_PAUSE;
	
	TGTHT510_supply_ctrl.step=STEP_START;
	
	TGTHT510_supply_ctrl.command=COMMAND_START;

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

void TGTHT510_supply_main_lvb_set(uint16 code)
{
	if((code>=LVb1K)&&(code<=LVb87G))//����ָ�����Ϊ����������ָ��ҺϷ�
	{
		TGTHT510_valvecontrol_struct.command_from_supply=code;//�����ڲ���ַ����
		TGTHT510_valvecontrol_struct.command_from_supply_time=2;//����200ms
	}
}

/******************************************************************************************
**���ƣ�����ϵͳ����״̬�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������״̬�ж���ȷ�򷵻�TRUE�����򷵻�FALSE
����ΪVALVE_ON����VALVE_OFF
����ΪSTATE_LVb01��STATE_LVb02��STATE_LVb03��STATE_LVb04������������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_main_lvb_get(uint16 code,uint16 on_or_off)
{
	uint16 temp;
	
	if(code>STATE_DVb)//����Ƿ�
	{
		return FALSE;
	}
	
	if((on_or_off!=VALVE_ON)&&(on_or_off!=VALVE_OFF))//����Ƿ�
	{
		return FALSE;
	}
	
	temp=TGTHT510_collectANDgroup_is_valve_state(code);
	
	if(temp==on_or_off)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
	
}


/******************************************************************************************
**���ƣ��ƽ�ϵͳ������λ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_main_lvt_set(uint16 code)
{
	if(code>LVt42G)//����Ƿ�
	{
		return;
	}
	
	TGTHT510_collectANDgroup_equiment_command_generate(code);
}


/******************************************************************************************
**���ƣ��ƽ�ϵͳ����״̬�ж�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������״̬�ж���ȷ�򷵻�TRUE�����򷵻�FALSE
����ΪVALVE_ON����VALVE_OFF
����ΪSTATE_LVt01��STATE_LVt02��STATE_LVt03��STATE_LVt04������������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_main_lvt_get(uint16 code,uint16 on_or_off)
{
	uint16 temp;
	
	if(code>STATE_LVt40)//����Ƿ�
	{
		return FALSE;
	}
	
	if((on_or_off!=VALVE_ON)&&(on_or_off!=VALVE_OFF))//����Ƿ�
	{
		return FALSE;
	}
	
	temp=TGTHT510_supply_main_valve_state_TGTHT520(code);
	
	if(temp==TGTHT520_VALVE_ON)
	{
		if(on_or_off==VALVE_ON)
		{
			return TRUE;
		}
		
		else
		{
			return FALSE;
		}
	}
	
	else if(temp==TGTHT520_VALVE_OFF)
	{
		if(on_or_off==VALVE_OFF)
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


/******************************************************************************************
**���ƣ��ƽ���������������������״̬�жϺ���
**���ߣ�����
**���ڣ�20160217
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_supply_main_valve_state_TGTHT520(uint16 state_code)
{
	uint16 lookup_state;
	uint16 lookup_word;
	uint16 valve_state;
	
	if(state_code<=STATE_LVt28)//��·�ƽ���������������
	{
		lookup_state=valve_state_TGTHT520a_lookup[state_code];
		
		lookup_word=valve_word_TGTHT520a_lookup[state_code];
		
		valve_state=(TGTHT510_1553B_data_TGTHT520a[lookup_word]&lookup_state);
	
	}
	
	else if((state_code>=STATE_LVt18)&&(state_code<=STATE_LVt40))//��·�ƽ���������������
	{
		lookup_state=valve_state_TGTHT520b_lookup[state_code-STATE_OFFSET];
		
		lookup_word=valve_word_TGTHT520b_lookup[state_code-STATE_OFFSET];
		
		valve_state=(TGTHT510_1553B_data_TGTHT520b[lookup_word]&lookup_state);
		
	}
	
	else//������������Ƿ�
	{
		return TGTHT520_VALVE_NONE;
		
	}
	
	if(lookup_state==TGTHT520_L_BYTE_L_BIT)
	{
		valve_state=valve_state;
			
	}
		
	else if(lookup_state==TGTHT520_L_BYTE_H_BIT)
	{
		valve_state=(valve_state>>4);
			
	}
		
	else if(lookup_state==TGTHT520_H_BYTE_L_BIT)
	{
		valve_state=(valve_state>>8);
			
	}
		
	else if(lookup_state==TGTHT520_H_BYTE_H_BIT)
	{
		valve_state=(valve_state>>12);
	}
		
	else
	{
		return TGTHT520_VALVE_NONE;
	}
	
	if(valve_state==TGTHT520_VALVE_ON)
	{
		return TGTHT520_VALVE_ON;
		
	}
	
	else if(valve_state==TGTHT520_VALVE_OFF)
	{
		return TGTHT520_VALVE_OFF;
	}
	
	else
	{
		return TGTHT520_VALVE_NONE;
	}

}


/******************************************************************************************
**���ƣ�������������������豸����ָ���
**���ߣ�����
**���ڣ�20160217
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_main_equ_command_set(uint16 code)
{
	if((code<TGTHT530a_ON_POWER)||(code>VALVE_SUPPLY_OFF_POWER))//�������
	{
		return;
	}
	
	TGTHT510_collectANDgroup_equiment_command_generate(code);
	
	switch(code)
	{
		case COMPRESS_A_START://ѹ����A����
		{
			compressor_state.compressor_A_state=COMPRESSOR_RUN;
			break;
		}
		
		case COMPRESS_B_START://ѹ����B����
		{
			compressor_state.compressor_B_state=COMPRESSOR_RUN;
			break;
		}
		
		case COMPRESS_C_START://ѹ����C����
		{
			compressor_state.compressor_C_state=COMPRESSOR_RUN;
			break;
		}
		
		case COMPRESS_A_STOP://ѹ����Aͣ��
		{
			compressor_state.compressor_A_state=COMPRESSOR_STOP;
			break;
		}
		
		case COMPRESS_B_STOP://ѹ����Bͣ��
		{
			compressor_state.compressor_B_state=COMPRESSOR_STOP;
			break;
		}
		
		case COMPRESS_C_STOP://ѹ����Cͣ��
		{
			compressor_state.compressor_C_state=COMPRESSOR_STOP;
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}



/******************************************************************************************
**���ƣ�
**���ߣ�����
**���ڣ�20160217
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_time_dealing(void)
{
	if(TGTHT510_supply_time.time_stage_flag==TRUE)
	{
		TGTHT510_supply_time.time_stage++;
	}
	
	else
	{
		TGTHT510_supply_time.time_stage=0;
	}
	
	if(TGTHT510_supply_time.time_step_flag==TRUE)
	{
		TGTHT510_supply_time.time_step++;
	}
	
	else
	{
		TGTHT510_supply_time.time_step=0;
	}

}

/******************************************************************************************
**���ƣ�
**���ߣ�����
**���ڣ�20160217
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_time_stage_start(void)
{
	TGTHT510_supply_time.time_stage_flag=TRUE;
	
	TGTHT510_supply_time.time_stage=0;
}


/******************************************************************************************
**���ƣ�
**���ߣ�����
**���ڣ�20160217
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_time_stage_end(void)
{
	TGTHT510_supply_time.time_stage_flag=FALSE;
}


/******************************************************************************************
**���ƣ�
**���ߣ�����
**���ڣ�20160217
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_time_stage_get(uint32 *time_val)
{
	*time_val=TGTHT510_supply_time.time_stage;
}



/******************************************************************************************
**���ƣ�
**���ߣ�����
**���ڣ�20160217
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_time_step_start(void)
{
	TGTHT510_supply_time.time_step_flag=TRUE;
}


/******************************************************************************************
**���ƣ�
**���ߣ�����
**���ڣ�20160217
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_supply_time_step_end(void)
{
	TGTHT510_supply_time.time_step_flag=FALSE;
}


/******************************************************************************************
**���ƣ�
**���ߣ�����
**���ڣ�20160217
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16	TGTHT510_supply_time_step_is_get(uint32 const_val)
{
	if(TGTHT510_supply_time.time_step>=const_val)//��ʱʱ�䵽
	{
		TGTHT510_supply_time_step_end();
		
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}	
}





















