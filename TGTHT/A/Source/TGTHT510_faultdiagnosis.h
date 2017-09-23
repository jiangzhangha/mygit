/**
  ******************************************************************************
  * @file    TGTHT510_faultdiagnosis.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ�������ң��״̬�ɼ�����֡ģ��ͷ�ļ�
  ******************************************************************************
  */

  
#ifndef __TGTHT510_faultdiagnosis_h
#define __TGTHT510_faultdiagnosis_h 

/*�����ṹ������---------------------------------------------------------*/

typedef struct
{
	uint16 time_count;//��ʱ������
	
	uint16 time_flag;//��ʱ����־
	
	uint16 step;//�ʼ촦����
	
	uint16 value[12];//�ʼ촦�����
	
	uint16 valve_htt[5][3];//Htt����������
	
}fault_field_TypeDef;//���ϴ������Խṹ��



typedef struct
{
	uint16 mode;//����ģʽ
	
	uint16 state;//����ģʽʹ��״̬��ENABLE����DISABLE
	
	uint16 result;//���Ϸ�����־��TRUE����FALSE
	
	fault_field_TypeDef fault_field1;//���ϴ�������1
	
	fault_field_TypeDef fault_field2;//���ϴ�������2
	
	fault_field_TypeDef fault_field3;//���ϴ�������3
	
	uint16 faultdiagnosis_count;//���ϼ���жϴ���
	
}fault_TypeDef;//���ϼ��ṹ��


typedef struct
{
	uint16 mode;//����ģʽ
	
	uint16 state;//����ģʽʹ��״̬��ENABLE����DISABLE
	
	uint16 result;//���Ϸ�����־��TRUE����FALSE
	
	uint16 step;//�ʼ촦����
	
	uint16 strategy_step;//���ϴ�����Բ���
	
	uint16 value_fa[4][8];//��������
	
	uint16 value_va[4][8];//��������
	
	uint16 faultdiagnosis_count;//���ϼ���жϴ���
	
}fault_valve_leak_TypeDef;//������й©���ϼ��ṹ��


typedef struct
{
	uint16 fault_mode;
	
	uint16 step;
	
	uint16 compressor_step;//ѹ����ͣ��������
	
	uint16 compressor_number;//��ǰ������ѹ������
	
	uint16 time_count;//��ʱ������
	
	uint16 time_flag;//��ʱ����־
	
}fault_deal_TypeDef;//���ϴ���ȫ�ֲ����ṹ��


typedef struct
{
	uint16 fault_mode_last;
	uint16 fault_mode_moment;
	
	uint16 TGTHT510_fault_push_o_gas1_leak_is_done;
	uint16 TGTHT510_fault_push_o_gas2_leak_is_done;
	uint16 TGTHT510_fault_push_o_gas3_leak_is_done;
	
	uint16 TGTHT510_fault_push_f_gas1_leak_is_done;
	uint16 TGTHT510_fault_push_f_gas2_leak_is_done;
	uint16 TGTHT510_fault_push_f_gas3_leak_is_done;
	
	uint16 TGTHT510_fault_push_o_tank1_overpressure_is_done;
	uint16 TGTHT510_fault_push_o_tank2_overpressure_is_done;
	uint16 TGTHT510_fault_push_o_tank3_overpressure_is_done;
	
	uint16 TGTHT510_fault_push_f_tank1_overpressure_is_done;
	uint16 TGTHT510_fault_push_f_tank2_overpressure_is_done;
	uint16 TGTHT510_fault_push_f_tank3_overpressure_is_done;
	
	uint16 TGTHT510_fault_push_B_main_valve_leak_is_done;
	uint16 TGTHT510_fault_push_B_less_valve_leak_is_done;
	uint16 TGTHT510_fault_push_C_all_valve_leak_is_done;
	uint16 TGTHT510_fault_push_A_main_valve_leak_is_done;
	uint16 TGTHT510_fault_push_A_less_valve_leak_is_done;
	
	uint16 TGTHT510_fault_push_o_tank1_leak_is_done;
	uint16 TGTHT510_fault_push_o_tank2_leak_is_done;
	uint16 TGTHT510_fault_push_o_tank3_leak_is_done;
	
	uint16 TGTHT510_fault_push_f_tank1_leak_is_done;
	uint16 TGTHT510_fault_push_f_tank2_leak_is_done;
	uint16 TGTHT510_fault_push_f_tank3_leak_is_done;
	
	uint16 TGTHT510_fault_supply_TGTHT530_is_done;
	
	uint16 TGTHT510_fault_supply_cooler_zz_is_done;
	uint16 TGTHT510_fault_supply_cooler_zb_is_done;
	uint16 TGTHT510_fault_supply_cooler_bz_is_done;
	uint16 TGTHT510_fault_supply_cooler_bb_is_done;
	
	uint16 TGTHT510_fault_supply_leak_cooler_z_is_done;
	uint16 TGTHT510_fault_supply_leak_cooler_b_is_done;
	
	uint16 TGTHT510_fault_supply_compressor_A_in_over_is_done;
	uint16 TGTHT510_fault_supply_compressor_B_in_over_is_done;
	uint16 TGTHT510_fault_supply_compressor_C_in_over_is_done;
	
	uint16 TGTHT510_fault_supply_compressor_A_motor_over_is_done;
	uint16 TGTHT510_fault_supply_compressor_B_motor_over_is_done;
	uint16 TGTHT510_fault_supply_compressor_C_motor_over_is_done;
	
	uint16 TGTHT510_fault_supply_compressor_A_hot_is_done;
	uint16 TGTHT510_fault_supply_compressor_B_hot_is_done;
	uint16 TGTHT510_fault_supply_compressor_C_hot_is_done;
	
	uint16 TGTHT510_fault_supply_o_tank1_overpressure_is_done;
	uint16 TGTHT510_fault_supply_o_tank2_overpressure_is_done;
	uint16 TGTHT510_fault_supply_o_tank3_overpressure_is_done;
	
	uint16 TGTHT510_fault_supply_f_tank1_overpressure_is_done;
	uint16 TGTHT510_fault_supply_f_tank2_overpressure_is_done;
	uint16 TGTHT510_fault_supply_f_tank3_overpressure_is_done;
	
	uint16 TGTHT510_fault_supply_compressor_A_break_is_done;
	uint16 TGTHT510_fault_supply_compressor_B_break_is_done;
	uint16 TGTHT510_fault_supply_compressor_C_break_is_done;
	
	uint16 TGTHT510_fault_supply_o_gas1_leak_is_done;
	uint16 TGTHT510_fault_supply_o_gas2_leak_is_done;
	uint16 TGTHT510_fault_supply_o_gas3_leak_is_done;
	
	uint16 TGTHT510_fault_supply_f_gas1_leak_is_done;
	uint16 TGTHT510_fault_supply_f_gas2_leak_is_done;
	uint16 TGTHT510_fault_supply_f_gas3_leak_is_done;
	
	uint16 TGTHT510_fault_supply_pipe_leak_o_tank1_is_done;
	uint16 TGTHT510_fault_supply_pipe_leak_o_tank2_is_done;
	uint16 TGTHT510_fault_supply_pipe_leak_o_tank3_is_done;
	
	uint16 TGTHT510_fault_supply_pipe_leak_f_tank1_is_done;
	uint16 TGTHT510_fault_supply_pipe_leak_f_tank2_is_done;
	uint16 TGTHT510_fault_supply_pipe_leak_f_tank3_is_done;
	
	uint16 TGTHT510_fault_supply_interface_o_temperature_is_done;
	uint16 TGTHT510_fault_supply_interface_f_temperature_is_done;
	
	uint16 TGTHT510_fault_supply_in_leak_o_z_is_done;
	uint16 TGTHT510_fault_supply_in_leak_o_b_is_done;
	uint16 TGTHT510_fault_supply_in_leak_f_z_is_done;
	uint16 TGTHT510_fault_supply_in_leak_f_b_is_done;
	
	uint16 TGTHT510_fault_supply_temperature_fore_f1_is_done;
	uint16 TGTHT510_fault_supply_temperature_fore_f2_is_done;
	uint16 TGTHT510_fault_supply_temperature_fore_o1_is_done;
	uint16 TGTHT510_fault_supply_temperature_fore_o2_is_done;
	
	uint16 TGTHT510_fault_supply_temperature_back_f1_is_done;
	uint16 TGTHT510_fault_supply_temperature_back_f2_is_done;
	uint16 TGTHT510_fault_supply_temperature_back_o1_is_done;
	uint16 TGTHT510_fault_supply_temperature_back_o2_is_done;
	
	uint16 TGTHT510_fault_supply_ka_o_tank1_is_done;
	uint16 TGTHT510_fault_supply_ka_o_tank2_is_done;
	uint16 TGTHT510_fault_supply_ka_o_tank3_is_done;
	
	uint16 TGTHT510_fault_supply_ka_f_tank1_is_done;
	uint16 TGTHT510_fault_supply_ka_f_tank2_is_done;
	uint16 TGTHT510_fault_supply_ka_f_tank3_is_done;
	
	
}fault_deal_is_CPU_A_done_TypeDef;//A�����͵Ĺʼ�ִ��״��





/*�궨��----------------------------------------------------------------------*/

//����ģʽ����
#define FAULT_MODE_PUSH_LEAK_O_GAS1				0x0101		//�ƽ����ϣ���1��ƿй©
#define FAULT_MODE_PUSH_LEAK_O_GAS2				0x0202		//�ƽ����ϣ���2��ƿй©
#define FAULT_MODE_PUSH_LEAK_O_GAS3				0x0303		//�ƽ����ϣ���3��ƿй©

#define FAULT_MODE_PUSH_LEAK_F_GAS1				0x0404		//�ƽ����ϣ�ȼ1��ƿй©
#define FAULT_MODE_PUSH_LEAK_F_GAS2				0x0505		//�ƽ����ϣ�ȼ2��ƿй©
#define FAULT_MODE_PUSH_LEAK_F_GAS3				0x0606		//�ƽ����ϣ�ȼ3��ƿй©

#define FAULT_MODE_PUSH_OVER_O_TANK1			0x0707		//�ƽ����ϣ���1���䳬ѹ
#define FAULT_MODE_PUSH_OVER_O_TANK2			0x0808		//�ƽ����ϣ���2���䳬ѹ
#define FAULT_MODE_PUSH_OVER_O_TANK3			0x0909		//�ƽ����ϣ���3���䳬ѹ

#define FAULT_MODE_PUSH_OVER_F_TANK1			0x0a0a		//�ƽ����ϣ�ȼ1���䳬ѹ
#define FAULT_MODE_PUSH_OVER_F_TANK2			0x0b0b		//�ƽ����ϣ�ȼ2���䳬ѹ
#define FAULT_MODE_PUSH_OVER_F_TANK3			0x0c0c		//�ƽ����ϣ�ȼ3���䳬ѹ

#define FAULT_MODE_PUSH_LEAK_B_MAIN				0x0d0d		//�ƽ����ϣ������˿ط��������Ʒ���й©
#define FAULT_MODE_PUSH_LEAK_B_LESS				0x0e0e		//�ƽ����ϣ������˿ط��������Ʒ���й©
#define FAULT_MODE_PUSH_LEAK_C_ALL				0x0f0f		//�ƽ����ϣ�C���˿ط��������Ʒ���й©
#define FAULT_MODE_PUSH_LEAK_A_MAIN				0x1010		//�ƽ����ϣ�A�������˿ط��������Ʒ���й©
#define FAULT_MODE_PUSH_LEAK_A_LESS				0x1111		//�ƽ����ϣ�A�鱸���˿ط��������Ʒ���й©

#define FAULT_MODE_PUSH_LEAK_O_TANK1			0x1212		//�ƽ����ϣ���1����й©
#define FAULT_MODE_PUSH_LEAK_O_TANK2			0x1313		//�ƽ����ϣ���2����й©
#define FAULT_MODE_PUSH_LEAK_O_TANK3			0x1414		//�ƽ����ϣ���3����й©

#define FAULT_MODE_PUSH_LEAK_F_TANK1			0x1515		//�ƽ����ϣ�ȼ1����й©
#define FAULT_MODE_PUSH_LEAK_F_TANK2			0x1616		//�ƽ����ϣ�ȼ2����й©
#define FAULT_MODE_PUSH_LEAK_F_TANK3			0x1717		//�ƽ����ϣ�ȼ3����й©

#define FAULT_MODE_SUPPLY_COOLER_ZZ				0x1818		//���ӹ��ϣ�����Һ�����ù���
#define FAULT_MODE_SUPPLY_COOLER_ZB				0x1919		//���ӹ��ϣ�����Һ�䱸�ù���
#define FAULT_MODE_SUPPLY_COOLER_BZ				0x1a1a		//���ӹ��ϣ�����Һ�����ù���
#define FAULT_MODE_SUPPLY_COOLER_BB				0x1b1b		//���ӹ��ϣ�����Һ�䱸�ù���

#define FAULT_MODE_SUPPLY_LEAK_COOLER_Z			0x1c1c		//���ӹ��ϣ�����Һ��й©
#define FAULT_MODE_SUPPLY_LEAK_COOLER_B			0x1d1d		//���ӹ��ϣ�����Һ��й©

#define FAULT_MODE_SUPPLY_OVER_COMP_A_IN		0x1e1e		//���ӹ��ϣ�ѹ����A��ڳ�ѹ
#define FAULT_MODE_SUPPLY_OVER_COMP_B_IN		0x1f1f		//���ӹ��ϣ�ѹ����B��ڳ�ѹ
#define FAULT_MODE_SUPPLY_OVER_COMP_C_IN		0x2020		//���ӹ��ϣ�ѹ����C��ڳ�ѹ

#define FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR		0x2121		//���ӹ��ϣ�ѹ����A���ǻ��ѹ
#define FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR		0x2222		//���ӹ��ϣ�ѹ����B���ǻ��ѹ
#define FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR		0x2323		//���ӹ��ϣ�ѹ����C���ǻ��ѹ

#define FAULT_MODE_SUPPLY_COMP_A_HOT			0x2424		//���ӹ��ϣ�ѹ����A����
#define FAULT_MODE_SUPPLY_COMP_B_HOT			0x2525		//���ӹ��ϣ�ѹ����B����
#define FAULT_MODE_SUPPLY_COMP_C_HOT			0x2626		//���ӹ��ϣ�ѹ����C����

#define FAULT_MODE_SUPPLY_OVER_O_TANK1			0x2727		//���ӹ��ϣ���1�������䳬ѹ
#define FAULT_MODE_SUPPLY_OVER_O_TANK2			0x2828		//���ӹ��ϣ���2�������䳬ѹ
#define FAULT_MODE_SUPPLY_OVER_O_TANK3			0x2929		//���ӹ��ϣ���3�������䳬ѹ

#define FAULT_MODE_SUPPLY_OVER_F_TANK1			0x2a2a		//���ӹ��ϣ�ȼ1�������䳬ѹ
#define FAULT_MODE_SUPPLY_OVER_F_TANK2			0x2b2b		//���ӹ��ϣ�ȼ2�������䳬ѹ
#define FAULT_MODE_SUPPLY_OVER_F_TANK3			0x2c2c		//���ӹ��ϣ�ȼ3�������䳬ѹ

#define FAULT_MODE_SUPPLY_COMP_A_BREAK			0x2d2d		//���ӹ��ϣ�ѹ����AĤƬ����
#define FAULT_MODE_SUPPLY_COMP_B_BREAK			0x2e2e		//���ӹ��ϣ�ѹ����BĤƬ����
#define FAULT_MODE_SUPPLY_COMP_C_BREAK			0x2f2f		//���ӹ��ϣ�ѹ����CĤƬ����

#define FAULT_MODE_SUPPLY_LEAK_O_GAS1			0x3030		//���ӹ��ϣ���1��ƿй©
#define FAULT_MODE_SUPPLY_LEAK_O_GAS2			0x3131		//���ӹ��ϣ���2��ƿй©
#define FAULT_MODE_SUPPLY_LEAK_O_GAS3			0x3232		//���ӹ��ϣ���3��ƿй©

#define FAULT_MODE_SUPPLY_LEAK_F_GAS1			0x3333		//���ӹ��ϣ�ȼ1��ƿй©
#define FAULT_MODE_SUPPLY_LEAK_F_GAS2			0x3434		//���ӹ��ϣ�ȼ2��ƿй©
#define FAULT_MODE_SUPPLY_LEAK_F_GAS3			0x3535		//���ӹ��ϣ�ȼ3��ƿй©

#define FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1		0x3636		//���ӹ��ϣ���1���䲹��Һ·й©
#define FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2		0x3737		//���ӹ��ϣ���2���䲹��Һ·й©
#define FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3		0x3838		//���ӹ��ϣ���3���䲹��Һ·й©

#define FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1		0x3939		//���ӹ��ϣ�ȼ1���䲹��Һ·й©
#define FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2		0x3a3a		//���ӹ��ϣ�ȼ2���䲹��Һ·й©
#define FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3		0x3b3b		//���ӹ��ϣ�ȼ3���䲹��Һ·й©

#define FAULT_MODE_SUPPLY_INTERFACE_O_TEMP		0x3c3c		//���ӹ��ϣ����������¶��쳣
#define FAULT_MODE_SUPPLY_INTERFACE_F_TEMP		0x3d3d		//���ӹ��ϣ�ȼ�������¶��쳣

#define FAULT_MODE_SUPPLY_IN_LEAK_O_Z			0x3e3e		//���ӹ��ϣ��������ӹ�·��©
#define FAULT_MODE_SUPPLY_IN_LEAK_O_B			0x3f3f		//���ӹ��ϣ��������ӹ�·��©
#define FAULT_MODE_SUPPLY_IN_LEAK_F_Z			0x4040		//���ӹ��ϣ�ȼ�����ӹ�·��©
#define FAULT_MODE_SUPPLY_IN_LEAK_F_B			0x4141		//���ӹ��ϣ�ȼ�����ӹ�·��©

#define FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1	0x4242		//���ӹ��ϣ�ǰ��ȼ1�����Ͻ����¶��쳣
#define FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2	0x4343		//���ӹ��ϣ�ǰ��ȼ2�����Ͻ����¶��쳣
#define FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1	0x4444		//���ӹ��ϣ�ǰ����1�����Ͻ����¶��쳣
#define FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2	0x4545		//���ӹ��ϣ�ǰ����2�����Ͻ����¶��쳣

#define FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1	0x4646		//���ӹ��ϣ�����ȼ1�����Ͻ����¶��쳣
#define FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2	0x4747		//���ӹ��ϣ�����ȼ2�����Ͻ����¶��쳣
#define FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1	0x4848		//���ӹ��ϣ�������1�����Ͻ����¶��쳣
#define FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2	0x4949		//���ӹ��ϣ�������2�����Ͻ����¶��쳣

#define FAULT_MODE_SUPPLY_KA_O_TANK1			0x4a4a		//���ӹ��ϣ���1���俨��
#define FAULT_MODE_SUPPLY_KA_O_TANK2			0x4b4b		//���ӹ��ϣ���2���俨��
#define FAULT_MODE_SUPPLY_KA_O_TANK3			0x4c4c		//���ӹ��ϣ���3���俨��

#define FAULT_MODE_SUPPLY_KA_F_TANK1			0x4d4d		//���ӹ��ϣ�ȼ1���俨��
#define FAULT_MODE_SUPPLY_KA_F_TANK2			0x4e4e		//���ӹ��ϣ�ȼ2���俨��
#define FAULT_MODE_SUPPLY_KA_F_TANK3			0x4f4f		//���ӹ��ϣ�ȼ3���俨��

#define FAULT_MODE_SUPPLY_TGTHT530				0x5050		//���ӹ��ϣ��������������

#define FAULT_MODE_PUSH_ALL						0xbfbf		//ȫ�����ӹ��ϣ��ƽ�����
#define FAULT_MODE_SUPPLY_ALL					0xcfcf		//ȫ�����ӹ��ϣ����Ӳ���

#define FAULT_MODE_ALL							0xdfdf		//ȫ������
#define FAULT_MODE_NONE							0xefef		//�޹���


//����״̬
#define FAULT_STATE_DISABLE						0x0101		//�ʼ�״̬��������
#define FAULT_STATE_NORMAL						0x0202		//�ʼ�״̬������
#define FAULT_STATE_ABNORMAL					0x0303		//�ʼ�״̬���쳣

#define FAULT_BIT15_12_SET						0x0404		//bit15-12����
#define FAULT_BIT11_08_SET						0x0505		//bit11-8����
#define FAULT_BIT07_04_SET						0x0606		//bit7-4����
#define FAULT_BIT03_00_SET						0x0707		//bit3-0����



//���ϼ�ⲽ��
#define FAULT_STEP_START	0x0000			//���ϼ�ⲽ��-��ʼ
#define FAULT_STEP_NO1		0x0101			//���ϼ�ⲽ��1
#define FAULT_STEP_NO2		0x0202			//���ϼ�ⲽ��2
#define FAULT_STEP_NO3		0x0303			//���ϼ�ⲽ��3
#define FAULT_STEP_NO4		0x0404			//���ϼ�ⲽ��4
#define FAULT_STEP_NO5		0x0505			//���ϼ�ⲽ��5
#define FAULT_STEP_NO6		0x0606			//���ϼ�ⲽ��6
#define FAULT_STEP_NO7		0x0707			//���ϼ�ⲽ��7
#define FAULT_STEP_NO8		0x0808			//���ϼ�ⲽ��8
#define FAULT_STEP_NO9		0x0909			//���ϼ�ⲽ��9
#define FAULT_STEP_NO10		0x0a0a			//���ϼ�ⲽ��10
#define FAULT_STEP_NO11		0x0b0b			//���ϼ�ⲽ��11
#define FAULT_STEP_NO12		0x0c0c			//���ϼ�ⲽ��12
#define FAULT_STEP_NO13		0x0d0d			//���ϼ�ⲽ��13
#define FAULT_STEP_NO14		0x0e0e			//���ϼ�ⲽ��14
#define FAULT_STEP_NO15		0x0f0f			//���ϼ�ⲽ��15
#define FAULT_STEP_NO16		0x1010			//���ϼ�ⲽ��16
#define FAULT_STEP_NO17		0x1111			//���ϼ�ⲽ��17
#define FAULT_STEP_NO18		0x1212			//���ϼ�ⲽ��18
#define FAULT_STEP_NO19		0x1313			//���ϼ�ⲽ��19
#define FAULT_STEP_NO20		0x1414			//���ϼ�ⲽ��20
#define FAULT_STEP_END		0xfefe			//���ϼ�ⲽ��-����
#define FAULT_STEP_NONE		0xfdfd			//���ϼ�ⲽ��-��

//���ϲ��Բ���
#define FAULT_STRATEGY_STEP_START 	0x0000  //���ϲ��Բ���-��ʼ
#define FAULT_STRATEGY_STEP_NO1 	0x0101  //���ϲ��Բ���1
#define FAULT_STRATEGY_STEP_NO2 	0x0202  //���ϲ��Բ���2
#define FAULT_STRATEGY_STEP_NO3 	0x0303  //���ϲ��Բ���3
#define FAULT_STRATEGY_STEP_NO4 	0x0404  //���ϲ��Բ���4
#define FAULT_STRATEGY_STEP_NO5 	0x0505  //���ϲ��Բ���5
#define FAULT_STRATEGY_STEP_NO6 	0x0606  //���ϲ��Բ���6
#define FAULT_STRATEGY_STEP_NO7 	0x0707  //���ϲ��Բ���7

#define FAULT_STRATEGY_STEP_END 	0xfefe  //���ϲ��Բ���-����
#define FAULT_STRATEGY_STEP_NONE 	0xfdfd  //���ϲ��Բ���-��

//���ϱ��

#define FAULT_O_GAS1		0x0101			//���ϼ��--��1��ƿ
#define FAULT_O_GAS2		0x0202			//���ϼ��--��2��ƿ
#define FAULT_O_GAS3		0x0303			//���ϼ��--��3��ƿ

#define FAULT_F_GAS1		0x0404			//���ϼ��--ȼ1��ƿ
#define FAULT_F_GAS2		0x0505			//���ϼ��--ȼ2��ƿ
#define FAULT_F_GAS3		0x0606			//���ϼ��--ȼ3��ƿ

#define FAULT_O_TANK1		0x0707			//���ϼ��--��1����
#define FAULT_O_TANK2		0x0808			//���ϼ��--��2����
#define FAULT_O_TANK3		0x0909			//���ϼ��--��3����

#define FAULT_F_TANK1		0x0a0a			//���ϼ��--ȼ1����
#define FAULT_F_TANK2		0x0b0b			//���ϼ��--ȼ2����
#define FAULT_F_TANK3		0x0c0c			//���ϼ��--ȼ3����

#define	FAULT_B_MAIN_LEAK	0x0d0d			//���ϼ��--B�����ݷ�����й©
#define	FAULT_B_LESS_LEAK	0x0e0e			//���ϼ��--B�鱸�ݷ�����й©
#define	FAULT_A_MAIN_LEAK	0x0f0f			//���ϼ��--A�����ݷ�����й©
#define	FAULT_A_LESS_LEAK	0x1010			//���ϼ��--A�鱸�ݷ�����й©
#define	FAULT_C_ALL_LEAK	0x1111			//���ϼ��--C�鷢����й©

#define FAULT_COOLER_ZZ		0x1212			//���ϼ��--����Һ������
#define FAULT_COOLER_ZB		0x1313			//���ϼ��--����Һ�䱸��
#define FAULT_COOLER_BZ		0x1414			//���ϼ��--����Һ������
#define FAULT_COOLER_BB		0x1515			//���ϼ��--����Һ�䱸��

#define FAULT_COOLER_Z		0x1616			//���ϼ��--����Һ��й©
#define FAULT_COOLER_B		0x1717			//���ϼ��--����Һ��й©

#define FAULT_COMPRESSOR_A_IN_OVER		0x1818 	//���ϼ��--ѹ����A��ڳ�ѹ
#define FAULT_COMPRESSOR_B_IN_OVER		0x1919 	//���ϼ��--ѹ����B��ڳ�ѹ
#define FAULT_COMPRESSOR_C_IN_OVER		0x1a1a 	//���ϼ��--ѹ����C��ڳ�ѹ

#define FAULT_COMPRESSOR_A_MOTOR_OVER	0x1b1b 	//���ϼ��--ѹ����A���ǻ��ѹ
#define FAULT_COMPRESSOR_B_MOTOR_OVER	0x1c1c 	//���ϼ��--ѹ����B���ǻ��ѹ
#define FAULT_COMPRESSOR_C_MOTOR_OVER	0x1d1d 	//���ϼ��--ѹ����C���ǻ��ѹ

#define FAULT_COMPRESSOR_A_HOT			0x1e1e 	//���ϼ��--ѹ����A����
#define FAULT_COMPRESSOR_B_HOT			0x1f1f 	//���ϼ��--ѹ����B����
#define FAULT_COMPRESSOR_C_HOT			0x2020 	//���ϼ��--ѹ����C����

#define FAULT_COMPRESSOR_A_BREAK		0x2121 	//���ϼ��--ѹ����AĤƬ����
#define FAULT_COMPRESSOR_B_BREAK		0x2222 	//���ϼ��--ѹ����BĤƬ����
#define FAULT_COMPRESSOR_C_BREAK		0x2323 	//���ϼ��--ѹ����CĤƬ����

#define FAULT_INTERFACE_O				0x2424	//���ϼ��--��������
#define FAULT_INTERFACE_F				0x2525	//���ϼ��--��������

#define FAULT_IN_LEAK_O_Z				0x2626  //���ϼ��--�������ӹ�·��©
#define FAULT_IN_LEAK_O_B				0x2727  //���ϼ��--�������ӹ�·��©
#define FAULT_IN_LEAK_F_Z				0x2828  //���ϼ��--ȼ�����ӹ�·��©
#define FAULT_IN_LEAK_F_B				0x2929  //���ϼ��--ȼ�����ӹ�·��©

#define FAULT_TEMPERATURE_FORE_F1		0x2f2f  //���ϼ��--ǰ��ȼ1�����Ͻ����¶��쳣
#define FAULT_TEMPERATURE_FORE_F2		0x3030  //���ϼ��--ǰ��ȼ2�����Ͻ����¶��쳣
#define FAULT_TEMPERATURE_FORE_O1		0x3131  //���ϼ��--ǰ����1�����Ͻ����¶��쳣
#define FAULT_TEMPERATURE_FORE_O2		0x3232  //���ϼ��--ǰ����2�����Ͻ����¶��쳣

#define FAULT_TEMPERATURE_BACK_F1		0x3333  //���ϼ��--����ȼ1�����Ͻ����¶��쳣
#define FAULT_TEMPERATURE_BACK_F2		0x3434  //���ϼ��--����ȼ2�����Ͻ����¶��쳣
#define FAULT_TEMPERATURE_BACK_O1		0x3535  //���ϼ��--������1�����Ͻ����¶��쳣
#define FAULT_TEMPERATURE_BACK_O2		0x3636  //���ϼ��--������2�����Ͻ����¶��쳣

#define FAULT_COMPRESSOR_A				0x3737	//���ϴ���--ѹ����A����
#define FAULT_COMPRESSOR_B				0x3838	//���ϴ���--ѹ����B����
#define FAULT_COMPRESSOR_C				0x3939	//���ϴ���--ѹ����C����

#define FAULT_COMPRESSOR_N				0xfefe	//���ϴ���--��ѹ�������ڹ���


#define FAULT_FIELD1					0x0101
#define FAULT_FIELD2					0x0202
#define FAULT_FIELD3					0x0303

#define FAULT_IN_LEAK					0x0101
#define FAULT_PIPE_LEAK					0x0202



//��������

#define MAX_FAULTDIAGNOSIS_COUNT			0x0003//�����ϼ���жϴ���

#define FAULT_CONST_PRESSURE_0E1			0x0009//��ֵ����ƿй©��ֵ��0.1MPa�����޸ģ�
#define FAULT_CONST_PRESSURE_0E2			0x0012//��ֵ����ƿ����Һ·й©��ֵ��0.2MPa�����޸ģ�
#define FAULT_CONST_PRESSURE_0E4			0x0025//��ֵ�����ӹ�·��©��ֵ��0.4MPa�����޸ģ�

#define FAULT_CONST_PRESSURE_0E14			0x000d//��ֵ����ƿй©��ֵ��0.14MPa�����޸ģ�
#define FAULT_CONST_PRESSURE_MIN_GAS		0x03dd//����ֵ����ƿй©��ֵ����С��ƿѹ��ֵ9MPa�����޸ģ�

#define FAULT_CONST_PRESSURE_OVER			0x0150//���䳬ѹ��ֵ��1.95MPa�����޸ģ�
#define FAULT_CONST_HTT_ONE					0x0007//����й©��ֵ��Ĭ��Ϊ1�������޸ģ�

#define FAULT_CONST_COOLER					0x0625//Һ���ת��6000תÿ���ӣ����޸ģ�

#define FAULT_CONST_COOLER_LEAK				0x0003//Һ��ģ��й©��1kp�����޸ģ�

#define FAULT_CONST_COMPRESSOR_OVER			0x00c1//ѹ������ѹ��0.4MPa�����޸ģ�
#define FAULT_CONST_COMPRESSOR_HOT			0x029c//ѹ�������£�42���϶ȣ����޸ģ�

#define FAULT_CONST_COMPRESSOR_BREAK		0x00f8//ѹ����ĤƬ���ѣ�1MPa�����޸ģ�


//��������

void TGTHT510_faultdiagnosis_test_hook(void);

void TGTHT510_faultdiagnosis_how_to_deal_fault_valve_leak_typedef(fault_valve_leak_TypeDef *p);
void TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(fault_TypeDef *p,uint16 which_field);
uint16 TGTHT510_faultdiagnosis_is_CPU_A_done_get_valve_leak(fault_valve_leak_TypeDef *p);
uint16 TGTHT510_faultdiagnosis_is_CPU_A_done_get(fault_TypeDef *p);


void TGTHT510_faultdiagnosis_is_CPU_A_done_set(void);
void TGTHT510_faultdiagnosis_is_CPU_A_done_initial(void);

void TGTHT510_faultdiagnosis_supply_struct_mode_add(void);
void TGTHT510_faultdiagnosis_push_struct_mode_add(void);

void TGTHT510_faultdiagnosis_initial(fault_TypeDef *p,uint16 enable_state);
void TGTHT510_faultdiagnosis_push_initial(void);
void TGTHT510_faultdiagnosis_supply_initial(void);
void TGTHT510_faultdiagnosis_push_main(void);
void TGTHT510_faultdiagnosis_supply_main(void);
void TGTHT510_faultdeal_lvb_set(uint16 code);
void TGTHT510_faultdeal_supply_pause(void);

void TGTHT510_faultdiagnosis_push_CG_set_dealing(uint16 *p,uint16 fault_state,uint16 set_bit);
void TGTHT510_faultdiagnosis_push_CG_set(uint16 mode,uint16 state);
void TGTHT510_faultdiagnosis_supply_CG_set(uint16 mode,uint16 state);
void TGTHT510_faultdiagnosis_enable_disable_set(uint16 mode,uint16 state);
void TGTHT510_faultdiagnosis_push_all_enable_disable_set(uint16 state);
void TGTHT510_faultdiagnosis_supply_all_enable_disable_set(uint16 state);


void TGTHT510_faultdiagnosis_time_dealing(fault_TypeDef *f);
void TGTHT510_faultdiagnosis_time1_start(fault_TypeDef *f);
void TGTHT510_faultdiagnosis_time1_end(fault_TypeDef *f);
void TGTHT510_faultdiagnosis_time2_start(fault_TypeDef *f);
void TGTHT510_faultdiagnosis_time2_end(fault_TypeDef *f);
uint16 TGTHT510_faultdiagnosis_time1_is_get(fault_TypeDef *f,uint16 val);
uint16 TGTHT510_faultdiagnosis_time2_is_get(fault_TypeDef *f,uint16 val);

uint16 TGTHT510_faultdiagnosis_push_gas_leak_min_four_of_three(uint16 *p,uint16 door_val);
uint16 TGTHT510_faultdiagnosis_push_gas_leak_four_of_three(uint16 *p,uint16 door_val);
uint16 TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(uint16 gas_leak);
void TGTHT510_faultdiagnosis_push_gas_leak_big(uint16 gas_leak);
void TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(fault_TypeDef *p,uint16 gas_leak);
void TGTHT510_faultdiagnosis_push_gas_leak_small(uint16 gas_leak);
void TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(fault_TypeDef *p,uint16 gas_leak);
void TGTHT510_faultdiagnosis_push_gas_leak_min(uint16 gas_leak);
void TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(fault_TypeDef *p,uint16 gas_leak);
uint16 TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(uint16 tank_overpressure,uint16 n);
uint16 TGTHT510_faultdiagnosis_push_tank_overpressure_is_over(uint16 *p,uint16 door_val);
void TGTHT510_faultdiagnosis_push_tank_overpressure(uint16 tank_overpressure);
void TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(fault_TypeDef *p,uint16 tank_overpressure);
void TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(uint16 valve_leak,uint16 n,uint16 *p);
uint16 TGTHT510_faultdiagnosis_push_valve_leak_is_leak(uint16 (*p1)[8],uint16 (*p2)[8]);

//uint16 TGTHT510_faultdiagnosis_push_valve_leak_is_leak(uint16 *p1,uint16 *p2);
void TGTHT510_faultdiagnosis_push_valve_leak(uint16 valve_leak);
void TGTHT510_faultdiagnosis_push_valve_leak_dealing(fault_valve_leak_TypeDef *p,uint16 valve_leak);
uint16 TGTHT510_faultdiagnosis_push_htt_get(uint16 tank_leak,uint16 n);
//uint16 TGTHT510_faultdiagnosis_push_tank_leak_is_leak(uint16 *p);
uint16 TGTHT510_faultdiagnosis_push_tank_leak_is_leak(uint16 (*p)[3]);

void TGTHT510_faultdiagnosis_push_tank_leak(uint16 tank_leak);
void TGTHT510_faultdiagnosis_push_tank_leak_dealing(fault_TypeDef *p,uint16 tank_leak);
void TGTHT510_faultdiagnosis_supply_TGTHT530(void);
void TGTHT510_faultdiagnosis_supply_TGTHT530_dealing(fault_TypeDef *p);
void TGTHT510_faultdiagnosis_supply_cooler(uint16 fault_cooler);
uint16 TGTHT510_faultdiagnosis_supply_cooler_get_value(uint16 fault_cooler);
uint16 TGTHT510_faultdiagnosis_supply_cooler_is_fault(uint16 *p);
void TGTHT510_faultdiagnosis_supply_cooler_dealing(fault_TypeDef *p,uint16 fault_cooler);
void TGTHT510_faultdiagnosis_supply_leak_cooler(uint16 leak_cooler);
uint16 TGTHT510_faultdiagnosis_supply_leak_cooler_is_leak(uint16 *p);
void TGTHT510_faultdiagnosis_supply_leak_cooler_dealing(fault_TypeDef *p,uint16 leak_cooler);
void TGTHT510_faultdiagnosis_supply_over_compressor(uint16 over_kind);
uint16 TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(uint16 over_kind,uint16 num);
uint16 TGTHT510_faultdiagnosis_supply_over_compressor_is_over(uint16 *p);
void TGTHT510_faultdiagnosis_supply_over_compressor_dealing(fault_TypeDef *p,uint16 over_kind);
void TGTHT510_faultdiagnosis_supply_hot_compressor(uint16 hot_kind);
uint16 TGTHT510_faultdiagnosis_supply_hot_compressor_get_max(uint16 hot_kind);
uint16 TGTHT510_faultdiagnosis_supply_hot_compressor_is_hot(uint16 *p);
void TGTHT510_faultdiagnosis_supply_hot_compressor_dealing(fault_TypeDef *p,uint16 hot_kind);
void TGTHT510_faultdiagnosis_supply_tank_overpressure(uint16 tank_overpressure);
void TGTHT510_faultdiagnosis_supply_tank_overpressure_get(uint16 *p,uint16 tank_overpressure);
uint16 TGTHT510_faultdiagnosis_supply_tank_overpressure_is_over(uint16 *p);
void TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(fault_TypeDef *p,uint16 tank_overpressure);
void TGTHT510_faultdiagnosis_supply_compressor_break(uint16 compressor_break);
void TGTHT510_faultdiagnosis_supply_compressor_break_get_pressure(uint16 *p,uint16 compressor_break);
uint16 TGTHT510_faultdiagnosis_supply_compressor_break_is_break(uint16 *p);
void TGTHT510_faultdiagnosis_supply_compressor_break_dealing(fault_TypeDef *p,uint16 compressor_break);
void TGTHT510_faultdiagnosis_supply_gas_leak_big(uint16 gas_leak);
//void TGTHT510_faultdiagnosis_supply_gas_leak_big_is_leak(uint16 *p);
uint16 TGTHT510_faultdiagnosis_supply_gas_leak_big_is_leak(uint16 *p);

void TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(fault_TypeDef *p,uint16 gas_leak);
void TGTHT510_faultdiagnosis_supply_gas_leak_small(uint16 gas_leak);
void TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(fault_TypeDef *p,uint16 gas_leak);
void TGTHT510_faultdiagnosis_supply_gas_leak_min(uint16 gas_leak);
void TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(fault_TypeDef *p,uint16 gas_leak);
void TGTHT510_faultdiagnosis_supply_tank_pipe_leak(uint16 tank_leak);
void TGTHT510_faultdiagnosis_supply_tank_pipe_leak_get_pressure(uint16 *p,uint16 tank_leak);
//uint16 TGTHT510_faultdiagnosis_supply_tank_pipe_leak_is_leak(uint16 *p_htt,uint16 *p_pressure);
uint16 TGTHT510_faultdiagnosis_supply_tank_pipe_leak_is_leak(uint16 (*p_htt)[3],uint16 *p_pressure);

void TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(fault_TypeDef *p,uint16 tank_leak);
void TGTHT510_faultdiagnosis_supply_interface_temperature(uint16 interface);
void TGTHT510_faultdiagnosis_supply_interface_temperature_get(uint16 *p,uint16 interface);
uint16 TGTHT510_faultdiagnosis_supply_interface_temperature_is_normal(uint16 *p);
void TGTHT510_faultdiagnosis_supply_interface_temperature_dealing(fault_TypeDef *p,uint16 interface);
void TGTHT510_faultdiagnosis_supply_in_leak(uint16 leak_kind);
void TGTHT510_faultdiagnosis_supply_in_leak_get_pressure(uint16 *p,uint16 leak_kind);
uint16 TGTHT510_faultdiagnosis_supply_in_leak_is_leak(uint16 *p);
void TGTHT510_faultdiagnosis_supply_in_leak_dealing(fault_TypeDef *p,uint16 leak_kind);
void TGTHT510_faultdiagnosis_supply_temperature(uint16 temperature_kind);
void TGTHT510_faultdiagnosis_supply_temperature_get(uint16 *p,uint16 temperature_kind);
uint16 TGTHT510_faultdiagnosis_supply_temperature_is_normal(uint16 *p);
void TGTHT510_faultdiagnosis_supply_temperature_dealing(fault_TypeDef *p,uint16 temperature_kind);
void TGTHT510_faultdiagnosis_supply_ka_tank(uint16 ka);
uint16 TGTHT510_faultdiagnosis_supply_ka_tank_is_ka(uint16 *p);
void TGTHT510_faultdiagnosis_supply_ka_tank_get_pressure(uint16 *p,uint16 ka);
void TGTHT510_faultdiagnosis_supply_ka_tank_dealing(fault_TypeDef *p,uint16 ka);

uint16 TGTHT510_faultdeal_check_is_fault(fault_TypeDef *p);
uint16 TGTHT510_faultdeal_check_is_fault_valve_leak(fault_valve_leak_TypeDef *p);
void TGTHT510_faultdeal_check(void);
void TGTHT510_faultdeal_main(void);
void TGTHT510_faultdeal_time_start(fault_deal_TypeDef *f);
void TGTHT510_faultdeal_time_end(fault_deal_TypeDef *f);
void TGTHT510_faultdeal_time_dealing(fault_deal_TypeDef *f);
uint16 TGTHT510_faultdeal_time_is_get(fault_deal_TypeDef *f,uint16 val);
uint16 TGTHT510_faultdeal_which_compressor_working(void);
void TGTHT510_faultdeal_compressor_stop_dealing(uint16 compressor,uint16 valve_number);
void TGTHT510_faultdeal_compressor_stop_equment_command(uint16 compressor);
uint16 TGTHT510_faultdeal_compressor_stop(uint16 compressor);
void TGTHT510_faultdeal_push_gas_leak(uint16 gas_leak);
void TGTHT510_faultdeal_push_tank_overpressure(uint16 tank_overpressure);
void TGTHT510_faultdeal_push_valve_leak(uint16 valve_leak);
void TGTHT510_faultdeal_push_tank_leak(uint16 tank_leak);
void TGTHT510_faultdeal_supply_cooler(uint16 fault_cooler);
void TGTHT510_faultdeal_supply_cooler_dealing(void);
void TGTHT510_faultdeal_supply_leak_cooler(uint16 leak_cooler);
void TGTHT510_faultdeal_supply_over_compressor(uint16 over_kind);
void TGTHT510_faultdeal_supply_hot_compressor(uint16 hot_kind);
void TGTHT510_faultdeal_supply_tank_overpressure(uint16 tank_overpressure);
void TGTHT510_faultdeal_supply_compressor_break(uint16 compressor_break);
//void TGTHT510_faultdeal_supply_gas_leak(uint16 gas_leak);
void TGTHT510_faultdeal_supply_gas_leak(void);

void TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(uint16 tank_leak,uint16 number);
void TGTHT510_faultdeal_supply_tank_pipe_leak(uint16 tank_leak);
void TGTHT510_faultdeal_supply_interface_temperature_dealing(uint16 interface,uint16 number);
void TGTHT510_faultdeal_supply_interface_temperature(uint16 interface);
void TGTHT510_faultdeal_supply_in_leak(uint16 leak_kind);
void TGTHT510_faultdeal_supply_temperature_dealing(uint16 temperature_kind,uint16 number);
void TGTHT510_faultdeal_supply_temperature(uint16 temperature_kind);
void TGTHT510_faultdeal_supply_ka_tank(uint16 ka);

void TGTHT510_faultdiagnosis_push_set_stage_launch(void);		//�����		�ƽ��ʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_push_set_stage_orbit(void);		//����		�ƽ��ʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_push_set_stage_polling(void);		//Ѳ���		�ƽ��ʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_push_set_stage_gas(void);			//ѹ����������	�ƽ��ʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_push_set_stage_comp(void);			//���ӳ�����	�ƽ��ʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_push_set_stage_flow(void);			//����������	�ƽ��ʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_push_set_stage_repre(void);		//���Ӹ�ѹ��	�ƽ��ʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_push_set_stage_other(void);		//����������	�ƽ��ʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_push_set_stage_run(void);			//���ж�		�ƽ��ʼ�ʹ�ܽ�ֹ����


void TGTHT510_faultdiagnosis_supply_set_stage_launch(void);		//�����		���ӹʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_supply_set_stage_orbit(void);		//����		���ӹʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_supply_set_stage_polling(void);	//Ѳ���		���ӹʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_supply_set_stage_gas(void);		//ѹ����������	���ӹʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_supply_set_stage_comp(void);		//���ӳ�����	���ӹʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_supply_set_stage_flow(void);		//����������	���ӹʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_supply_set_stage_repre(void);		//���Ӹ�ѹ��	���ӹʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_supply_set_stage_other(void);		//����������	���ӹʼ�ʹ�ܽ�ֹ����
void TGTHT510_faultdiagnosis_supply_set_stage_run(void);		//���ж�		���ӹʼ�ʹ�ܽ�ֹ����



#endif




