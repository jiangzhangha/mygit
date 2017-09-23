/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ���������������������ͷ�ļ�
  ******************************************************************************
  */
 
#ifndef __supply_main_h
#define __supply_main_h
 

/*�����ṹ������--------------------------------------------------------------*/

typedef struct
{
	uint16 compressor_A_state;//ѹ����A����״̬��COMPRESSOR_RUN����COMPRESSOR_STOP
	uint16 compressor_B_state;//ѹ����B����״̬��COMPRESSOR_RUN����COMPRESSOR_STOP
	uint16 compressor_C_state;//ѹ����C����״̬��COMPRESSOR_RUN����COMPRESSOR_STOP
	
}compressor_state_TypeDef;//ѹ������������״̬�ṹ��

typedef struct
{
	uint16	mode;					//����ģʽ
	uint16	state;					//��������״̬�����С���ͣ����ֹ������

	uint16 	stage;					//���ӽ׶�
	uint16 	step;					//������
	uint16 	command;				//ָ��
	
	uint16	receive;				//ע���������״̬
	uint16 	leak_flag;				//��©����ע��ָ���־
	
	uint16 	errno;					//���ϴ���
	uint16	step_temp;				//���洦����
	uint16	command_temp;			//����ָ��
	
}TGTHT510_supply_ctrl_TypeDef;		//���������ڲ����Ʋ���

typedef struct
{
//ע�벹�Ӳ������仯-----------------------------------------------------------
	
	uint8	interface_F;			//ȼ���ӽӿ�
	uint8	interface_O;			//�����ӽӿ�
	
	uint8	sequence_tank_F;		//ȼ���䲹��˳��
	uint8	sequence_tank_O;		//�����䲹��˳��
	
	uint8	sequence_gas_F1;		//ȼ����F1��ƿ����˳��
	uint8	sequence_gas_F2;		//ȼ����F2��ƿ����˳��
	uint8	sequence_gas_F3;		//ȼ����F3��ƿ����˳��
	
	uint8	sequence_gas_O1;		//������O1��ƿ����˳��
	uint8	sequence_gas_O2;		//������O2��ƿ����˳��
	uint8	sequence_gas_O3;		//������O3��ƿ����˳��
	
	uint16  compressor_out_valve;	//����ѹ�����ţ��뿪����ѹ�������ڷ���
	
	uint16	pressure_first_F1;		//ȼ����F1��һ����������ĩѹ
	uint16 	pressure_second_F1;		//ȼ����F1�ڶ�����������ĩѹ
	
	uint16	pressure_first_F2;		//ȼ����F2��һ����������ĩѹ
	uint16 	pressure_second_F2;		//ȼ����F2�ڶ�����������ĩѹ
	
	uint16	pressure_first_F3;		//ȼ����F3��һ����������ĩѹ
	uint16 	pressure_second_F3;		//ȼ����F3�ڶ�����������ĩѹ
	
	uint16	pressure_first_O1;		//������O1��һ����������ĩѹ
	uint16 	pressure_second_O1;		//������O1�ڶ�����������ĩѹ
	
	uint16	pressure_first_O2;		//������O2��һ����������ĩѹ
	uint16 	pressure_second_O2;		//������O2�ڶ�����������ĩѹ
	
	uint16	pressure_first_O3;		//������O3��һ����������ĩѹ
	uint16 	pressure_second_O3;		//������O3�ڶ�����������ĩѹ
	
	uint16	pump_cooler;			//ʹ�õ�Һ��ģ��ú�
	
	uint16	volum_F1;				//ȼ����F1���ӵ�λʣ����
	uint16	volum_F2;				//ȼ����F2���ӵ�λʣ����
	uint16	volum_F3;				//ȼ����F3���ӵ�λʣ����
	
	uint16	volum_O1;				//������O1���ӵ�λʣ����
	uint16	volum_O2;				//������O2���ӵ�λʣ����
	uint16	volum_O3;				//������O3���ӵ�λʣ����
	
	uint16	mode;					//����ģʽ
	
	uint16 	pressure_repre_F1;		//ȼ����F1��ѹѹ��ֵ
	uint16 	pressure_repre_F2;		//ȼ����F2��ѹѹ��ֵ
	uint16 	pressure_repre_F3;		//ȼ����F3��ѹѹ��ֵ
	
	uint16 	pressure_repre_O1;		//������O1��ѹѹ��ֵ
	uint16 	pressure_repre_O2;		//������O2��ѹѹ��ֵ
	uint16 	pressure_repre_O3;		//������O3��ѹѹ��ֵ

//ע�벹�Ӳ������̶�-----------------------------------------------------------
	
	uint32	time_exhaust;			//��©�����ŷ�ʱ��
	uint32	time_comp_max;			//������ʱ��
	uint16	velocity_max;			//��󲹼�����
	uint16	velocity_min;			//��С��������
	uint16 	time_flow_max;			//��󲹼�����ʱ��
	uint16	temperature_mode;		//���ӹ�·����ģʽ
	uint16	temperature_start_min;	//ѹ���������¶�����
	uint16	temperature_start_max;	//ѹ���������¶�����
	uint16	temperature_alarm;		//ѹ���������¶�
	uint16	temperature_comp_cooler;//ѹ������Һ���¶Ȳ�ֵ
	uint16	pressure_comp_out;		//ѹ������������ѹ��
	uint16	pressure_comp_out_stop;	//ѹ����ͣ�������ѹ��
	uint16	dp_high;				//��ѹѹ���ı仯��ֵ
	uint16	dp1_low;				//��ѹѹ���ı仯��ֵ1
	uint16	dp2_low;				//��ѹѹ���ı仯��ֵ2
	uint32	time_repre_max;			//���ѹʱ��
	uint16	v_comp_start;			//ѹ��������ת��
	uint16	v_comp_stop;			//ѹ����ͣ��ת��
	uint16	time_delay_short;		//����ʱ
	uint16	time_delay_long;		//����ʱ
	uint16	time_bypath;			//��·������ʱ��
	uint16	eps1;					//ƫ��1
	uint16	eps2;					//ƫ��2
	uint16	pressure_comp_in_max;	//ѹ����������ѹ��
	uint16	pressure_comp_in_min;	//ѹ������С����ѹ��
	uint16	pressure_comp_out_min;	//ѹ������С����ѹ��
	uint16	pressure_hyc;			//���˷ɴ����ѹѹ��
	
	uint16	sensor_pipe_F;			//ȼ����Һ·ѹ���������趨
	uint16	sensor_pipe_O;			//������Һ·ѹ���������趨
	
	uint16	sensor_tank_F;			//ȼ����ѹ���������趨
	uint16	sensor_tank_O;			//������ѹ���������趨
	
	uint16	sensor_comp_in;			//ѹ��������ѹ���������趨
	uint16	sensor_pipe_low;		//��ѹ��·ѹ���������趨

	
}TGTHT510_supply_input_par_TypeDef;


typedef struct
{
	uint16 		interface_F;			//ȼ���ӽӿ�
	uint16		interface_O;			//�����ӽӿ�
	
	uint16		number_tank_F;			//���ӵ�ȼ�������
	uint16		first_tank_F;			//��һ�����ӵ�ȼ����
	uint16		second_tank_F;			//�ڶ������ӵ�ȼ����
	uint16		third_tank_F;			//���������ӵ�ȼ����
	
	uint16		number_tank_O;			//���ӵ����������
	uint16		first_tank_O;			//��һ�����ӵ�������
	uint16		second_tank_O;			//�ڶ������ӵ�������
	uint16		third_tank_O;			//���������ӵ�������
	
	uint16		number_gas_tank_F1;		//ȼ����F1������ƿ����
	uint16		first_gas_tank_F1;		//ȼ����F1��һ��������ƿ
	uint16		second_gas_tank_F1;		//ȼ����F1�ڶ���������ƿ
	
	uint16		number_gas_tank_F2;		//ȼ����F2������ƿ����
	uint16		first_gas_tank_F2;		//ȼ����F2��һ��������ƿ
	uint16		second_gas_tank_F2;		//ȼ����F2�ڶ���������ƿ
	
	uint16		number_gas_tank_F3;		//ȼ����F3������ƿ����
	uint16		first_gas_tank_F3;		//ȼ����F3��һ��������ƿ
	uint16		second_gas_tank_F3;		//ȼ����F3�ڶ���������ƿ
	
	uint16		number_gas_tank_O1;		//������O1������ƿ����
	uint16		first_gas_tank_O1;		//������O1��һ��������ƿ
	uint16		second_gas_tank_O1;		//������O1�ڶ���������ƿ
	
	uint16		number_gas_tank_O2;		//������O2������ƿ����
	uint16		first_gas_tank_O2;		//������O2��һ��������ƿ
	uint16		second_gas_tank_O2;		//������O2�ڶ���������ƿ
	
	uint16		number_gas_tank_O3;		//������O3������ƿ����
	uint16		first_gas_tank_O3;		//������O3��һ��������ƿ
	uint16		second_gas_tank_O3;		//������O3�ڶ���������ƿ
	
	uint16		compressor_F;			//ȼ����ѹ������
	uint16		compressor_O;			//������ѹ������
	
	uint16		valve_out_compressor_F;	//ȼѹ�������ڷ���
	uint16		valve_out_compressor_O;	//ȼѹ�������ڷ���
	
	uint16 		sensor_tank_F1;			//ȼ����F1ѹ���������趨
	uint16 		sensor_tank_F2;			//ȼ����F2ѹ���������趨
	uint16 		sensor_tank_F3;			//ȼ����F3ѹ���������趨
	uint16 		sensor_tank_O1;			//ȼ����O1ѹ���������趨
	uint16 		sensor_tank_O2;			//ȼ����O2ѹ���������趨
	uint16 		sensor_tank_O3;			//ȼ����O3ѹ���������趨
	
	uint16		sensor_pipe_low_F;		//ȼ·��ѹ��·ѹ���������趨
	uint16		sensor_pipe_low_O;		//��·��ѹ��·ѹ���������趨
	
	uint16		sensor_in_compressor_F; //ȼѹ��������ѹ���������趨
	uint16		sensor_in_compressor_O; //��ѹ��������ѹ���������趨
	
	uint16		cooler;					//Һ��ģ��ú�

}TGTHT510_supply_decode_par_TypeDef;


typedef struct
{
	uint32	time_stage;//���ӽ׶μ�ʱ
	
	uint16	time_stage_flag;//TRUE��ʱ��FALSEֹͣ
	
	uint32	time_step;//���Ӳ����ʱ
	
	uint16	time_step_flag;//TRUE��ʱ��FALSEֹͣ
	
}TGTHT510_supply_time_TypeDef;		//���������ڲ����Ʋ���


/*�궨��---------------------------------------------------------------------------*/

//���ϴ���

#define		ERRNO_NONE							0x0000//�޹��ϴ���
#define		ERRNO_SUPPLY_VALVE_POWER_ON			0x0101//����ϵͳ���żӵ��쳣
#define		ERRNO_SUPPLY_VALVE_OFF				0x0202//����ϵͳ���Źر��쳣
#define		ERRNO_SUPPLY_VALVE_ON				0x0303//����ϵͳ���Ŵ��쳣
#define		ERRNO_TUIJIN_VALVE_OFF				0x0404//�ƽ�ϵͳ���Źر��쳣
#define		ERRNO_TUIJIN_VALVE_ON				0x0505//�ƽ�ϵͳ���Ŵ��쳣
#define		ERRNO_FUNCTION_INPUT_ERROR			0x0606//�ڲ����������������
#define		ERRNO_INPUT_PAR_DECODE				0x0707//����ע������������
#define		ERRNO_COOLER_WORK					0x0808//Һ���ת��״̬�쳣
#define		ERRNO_TEMPER_COOLER_TO_COMPRESSOR	0x0909//Һ���ѹ��������ȴ״̬�쳣
#define		ERRNO_COMPRESSOR_TEMPERATURE		0x0a0a//ѹ�����ⶨ�¶��쳣
#define		ERRNO_TANK_VALVE_ON_PRESSURE		0x0b0b//ͨ��ѹ���ж����䷧�ſ����쳣
#define		ERRNO_IN_COMPRESSOR_PRESSURE		0x0c0c//ѹ��������ѹ���쳣
#define		ERRNO_OUT_COMPRESSOR_PRESSURE		0x0d0d//ѹ��������ѹ���쳣
#define		ERRNO_GAS_PRESSURE					0x0e0e//��ƿѹ�������쳣
#define		ERRNO_ISOLATION						0x0f0f//��ѹ��·�����쳣
#define		ERRNO_EXCHANGE_COOLER				0x1010//Һ��ģ���л������쳣
#define		ERRNO_EXCHANGE_COOLER_PRESSURE		0x1111//ͨ��ѹ���ж�Һ��ģ���л������쳣
#define		ERRNO_HYCT_PRESSURE					0x1212//������ѹ״̬�쳣
#define		ERRNO_INTERFACE_VALVE_ON_PRESSURE	0x1313//ͨ��ѹ���жϽ������Ͻ������ſ����쳣
#define		ERRNO_PIPE_PRESSURE_STABLE			0x1414//���ӽӿڹ�·ѹ�����ȶ�
#define		ERRNO_TANK_PRESSURE_STABLE			0x1515//����ѹ�����ȶ�
#define		ERRNO_SUPPLY_VALVE_POWER_OFF		0x1616//����ϵͳ���Ŷϵ��쳣
#define		ERRNO_TANK_VALVE_PRESSURE			0x1717//��������ʱͨ��ѹ���жϽ����䷧�Źر��쳣
#define		ERRNO_LEAK_INTERFACE_ERROR			0x1818//��©�������ӽӿڽ������

#define		ERRNO_FAULT_DIAGNOSIS				0xabab//���ϼ���봦��������ͣ



//����ģʽ
#define		MODE_AUTO				0x0101//�Զ�
#define		MODE_HALF_AUTO			0x0202//���Զ�
#define		MODE_MAN_MADE			0x0303//�ֶ�
#define		MODE_NONE				0x0404//��

//����״̬
#define		STATE_NONE				0x0000//����
#define		STATE_RUN				0x0101//����
#define		STATE_PAUSE				0x0202//��ͣ
#define		STATE_BREAK				0x0303//��ֹ
#define		STATE_PAUSE_RESUME		0x0404//��ͣ�ָ�


//���ӽ׶�
#define		STAGE_00_NONE			0x0000//���ӽ׶�0������
#define		STAGE_01_INPUT			0x0101//���ӽ׶�1��ע�벹�Ӳ���
#define		STAGE_02_SET			0x0202//���ӽ׶�2��״̬����
#define		STAGE_03_CONNECT		0x0303//���ӽ׶�3�������Ͻ������
#define		STAGE_04_LEAK			0x0404//���ӽ׶�4�����ӹ�·��©
#define		STAGE_05_COMP_F			0x0505//���ӽ׶�5��ȼ�������
#define		STAGE_06_PRE_F			0x0606//���ӽ׶�6��ȼ������ѹ����
#define		STAGE_07_FLOW_F			0x0707//���ӽ׶�7��ȼ�ƽ�����������
#define		STAGE_08_REPRE_F		0x0808//���ӽ׶�8��ȼ���临ѹ
#define		STAGE_09_COMP_F_T		0x0909//���ӽ׶�9��������ȼ�������
#define		STAGE_10_FLOW_F_T		0x0a0a//���ӽ׶�10��������ȼ���䲹������
#define		STAGE_11_REPRE_F_T		0x0b0b//���ӽ׶�11��������ȼ���临ѹ
#define		STAGE_12_BLOW_F			0x0c0c//���ӽ׶�12��ȼ��·����
#define		STAGE_13_COMP_O			0x0d0d//���ӽ׶�13�����������
#define		STAGE_14_PRE_O			0x0e0e//���ӽ׶�14����������ѹ����
#define		STAGE_15_FLOW_O			0x0f0f//���ӽ׶�15�����ƽ�����������
#define		STAGE_16_REPRE_O		0x1010//���ӽ׶�16�������临ѹ
#define		STAGE_17_COMP_O_T		0x1111//���ӽ׶�17�����������������
#define		STAGE_18_FLOW_O_T		0x1212//���ӽ׶�18�������������䲹������
#define		STAGE_19_REPRE_O_T		0x1313//���ӽ׶�19�������������临ѹ
#define		STAGE_20_BLOW_O			0x1414//���ӽ׶�20������·����
#define		STAGE_21_DISCONNECT		0x1515//���ӽ׶�21�������Ͻ����ѿ�
#define		STAGE_22_RESUME			0x1616//���ӽ׶�22��״̬�ָ�


/*ע���������----------------------------------------------------------------------------*/

#define		DECODE_NONE				0x0000//��

#define		DECODE_INTERFACE_R1		0x0101//ȼ���ӽӿ�R1
#define		DECODE_INTERFACE_R2		0x0202//ȼ���ӽӿ�R2
#define		DECODE_INTERFACE_R3		0x0303//ȼ���ӽӿ�R3
#define		DECODE_INTERFACE_R4		0x0404//ȼ���ӽӿ�R4
#define		DECODE_INTERFACE_O1		0x0505//�����ӽӿ�O1
#define		DECODE_INTERFACE_O2		0x0606//�����ӽӿ�O2
#define		DECODE_INTERFACE_O3		0x0707//�����ӽӿ�O3
#define		DECODE_INTERFACE_O4		0x0808//�����ӽӿ�O4

#define		DECODE_TANK_F1			0x0909//ȼ����F1
#define		DECODE_TANK_F2			0x0a0a//ȼ����F2
#define		DECODE_TANK_F3			0x0b0b//ȼ����F3
#define		DECODE_TANK_O1			0x0c0c//������O1
#define		DECODE_TANK_O2			0x0d0d//������O2
#define		DECODE_TANK_O3			0x0e0e//������O3

#define		DECODE_GAS_F1			0x0f0f//ȼ��ƿF1
#define		DECODE_GAS_F2			0x1010//ȼ��ƿF2
#define		DECODE_GAS_F3			0x1111//ȼ��ƿF3
#define		DECODE_GAS_O1			0x1212//����ƿO1
#define		DECODE_GAS_O2			0x1313//����ƿO2
#define		DECODE_GAS_O3			0x1414//����ƿO3

#define		DECODE_COMPRESSOR_A		0x1515//ѹ����A
#define		DECODE_COMPRESSOR_B		0x1616//ѹ����B
#define		DECODE_COMPRESSOR_C		0x1717//ѹ����C

#define		DECODE_COOLER_Z_1		0x1818//Һ��ģ����I
#define		DECODE_COOLER_Z_2		0x1919//Һ��ģ����II
#define		DECODE_COOLER_B_1		0x1a1a//Һ��ģ�鱸I
#define		DECODE_COOLER_B_2		0x1b1b//Һ��ģ�鱸II

#define		DECODE_COMP_VALVE_Z		0x1c1c//ѹ�����������ݷ�
#define		DECODE_COMP_VALVE_B		0x1d1d//ѹ�������ڱ��ݷ�

#define		DECODE_SENSOR_TANK_Z	0x1e1e//����ѹ������������
#define		DECODE_SENSOR_TANK_B	0x1f1f//����ѹ������������

#define		DECODE_SENSOR_PIPE_LOW_PTB02	0x2020//��ѹ��·ѹ���������趨��ȼ·PTb2
#define		DECODE_SENSOR_PIPE_LOW_PTB04	0x2121//��ѹ��·ѹ���������趨��ȼ·PTb4
#define		DECODE_SENSOR_PIPE_LOW_PTB24	0x2222//��ѹ��·ѹ���������趨��ȼ·������·PTb24

#define		DECODE_SENSOR_PIPE_LOW_PTB01	0x2323//��ѹ��·ѹ���������趨����·PTb1
#define		DECODE_SENSOR_PIPE_LOW_PTB03	0x2424//��ѹ��·ѹ���������趨����·PTb3

#define		DECODE_SENSOR_PIPE_LOW_PTB28	0x2525//ѹ��������PTb28
#define		DECODE_SENSOR_PIPE_LOW_PTB29	0x2626//ѹ��������PTb29

/*�ƽ�����������������״̬�궨��----------------------------------------------------------*/

//��·�ƽ������������ƽ�������
#define STATE_LVt09	0x00
#define STATE_LVt11	0x01
#define STATE_LVt01	0x02
#define STATE_LVt07	0x03
#define STATE_LVt43	0x04
#define STATE_LVt45	0x05
#define STATE_LVt31	0x06
#define STATE_LVt37	0x07
#define STATE_LVt08	0x08
#define STATE_LVt10	0x09
#define STATE_LVt51	0x0a
#define STATE_LVt02	0x0b
#define STATE_LVt38	0x0c
#define STATE_LVt44	0x0d
#define STATE_LVt12	0x0e
#define STATE_LVt32	0x0f
#define STATE_LVt03	0x10
#define STATE_LVt20	0x11
#define STATE_LVt46	0x12
#define STATE_LVt52	0x13
#define STATE_LVt35	0x14
#define STATE_LVt19	0x15
#define STATE_LVt24	0x16
#define STATE_LVt27	0x17
#define STATE_LVt36	0x18
#define STATE_LVt23	0x19
#define STATE_LVt28	0x1a


//��·�ƽ������������ƽ�������
#define STATE_LVt18	0x1b
#define STATE_LVt22	0x1c
#define STATE_LVt06	0x1d
#define STATE_LVt16	0x1e
#define STATE_LVt29	0x1f
#define STATE_LVt39	0x20
#define STATE_LVt26	0x21
#define STATE_LVt13	0x22
#define STATE_LVt15	0x23
#define STATE_LVt17	0x24
#define STATE_LVt41	0x25
#define STATE_LVt05	0x26
#define STATE_LVt34	0x27
#define STATE_LVt48	0x28
#define STATE_LVt21	0x29
#define STATE_LVt25	0x2a
#define STATE_LVt33	0x2b
#define STATE_LVt47	0x2c
#define STATE_LVt50	0x2d
#define STATE_LVt54	0x2e
#define STATE_LVt04	0x2f
#define STATE_LVt14	0x30
#define STATE_LVt49	0x31
#define STATE_LVt53	0x32
#define STATE_LVt42	0x33
#define STATE_LVt30	0x34
#define STATE_LVt40	0x35

//ƫ����
#define STATE_OFFSET 	0x1b

//��λ��
#define TGTHT520_L_BYTE_L_BIT	0x000f
#define TGTHT520_L_BYTE_H_BIT	0x00f0
#define TGTHT520_H_BYTE_L_BIT	0x0f00
#define TGTHT520_H_BYTE_H_BIT	0xf000

//����״̬
#define TGTHT520_VALVE_ON	0x0003
#define TGTHT520_VALVE_OFF	0x000c
#define TGTHT520_VALVE_NONE	0x000f

//����������
#define TGTHT510A_NUMBER	0x1b
#define TGTHT510B_NUMBER	0x1b

//���峣��
#define FIRST_TANK			0x0101//��һ����������	
#define SECOND_TANK			0x0202//�ڶ�����������
#define THIRD_TANK			0x0303//��������������

#define ONE_GAS				0x0404//һ��������ƿ
#define TWO_GAS				0x0505//����������ƿ
#define NONE_GAS			0x0606//��ƿ��������

#define FIRST_GAS			0x0707//��һ��������ƿ
#define SECOND_GAS			0x0808//�ڶ���������ƿ

//ѹ��������״̬
#define COMPRESSOR_RUN		0x1234//ѹ������������״̬
#define COMPRESSOR_STOP		0x4321//ѹ��������ֹͣ״̬			

//ʱ�䳣��
#define		CONST_TIME_2SEC		0x0004//��ʱ����2s
#define		CONST_TIME_5SEC		0x000a//��ʱ����5s
#define		CONST_TIME_10SEC	0x0014//��ʱ����10s
#define		CONST_TIME_12SEC	0x0018//��ʱ����12s
#define		CONST_TIME_15SEC	0x001e//��ʱ����15s

#define		CONST_TIME_30SEC	0x003c//��ʱ����30s
#define		CONST_TIME_1MIN		0x0078//��ʱ����1min
#define		CONST_TIME_5MIN		0x0258//��ʱ����5min

#define		CONST_TIME_12MIN	0x05a0//��ʱ����12min
#define		CONST_TIME_20MIN	0x0960//��ʱ����20min

//#define		CONST_TIME_1MIN		0x0018//��ʱ����1min-------���ԣ�����������


//����
#define 	CONST_ISOLATION			0x0003//ͨ��ѹ���ж�������·�������ֵ
#define		EXCHANGE_COOLER_NO1		0x0101//Һ��ģ���л�ָ��1
#define		EXCHANGE_COOLER_NO2		0x0202//Һ��ģ���л�ָ��2
#define		EXCHANGE_COOLER_NO3		0x0303//Һ��ģ���л�ָ��3
#define		EXCHANGE_COOLER_NO4		0x0404//Һ��ģ���л�ָ��4

//#define 	CONST_MAX_COMP_TIME		0x00023280//������ʱ�䣬Լ20Сʱ

#define 	CONST_MAX_COMP_TIME		0x00000e10//������ʱ�䣬Լ30min

#define 	CONST_COOLER_START_V	0x033C//Һ����������ת���ж���ֵ
#define		CONST_NUM_ZERO			0x0000


//��������----------------------------------------------------------------

void TGTHT510_supply_main_initial(void);
void TGTHT510_supply_main(void);
void TGTHT510_supply_main_half_auto(void);
void TGTHT510_supply_main_run(void);
void TGTHT510_supply_main_pause_deal(void);
void TGTHT510_supply_main_pause_resume_deal(void);
void TGTHT510_supply_main_break_deal(void);



void TGTHT510_supply_main_pause(uint16 errno);
void TGTHT510_supply_main_lvb_set(uint16 code);
uint16 TGTHT510_supply_main_lvb_get(uint16 code,uint16 on_or_off);
void TGTHT510_supply_main_lvt_set(uint16 code);
uint16 TGTHT510_supply_main_lvt_get(uint16 code,uint16 on_or_off);
uint16 TGTHT510_supply_main_valve_state_TGTHT520(uint16 state_code);
void TGTHT510_supply_main_equ_command_set(uint16 code);
void TGTHT510_supply_time_dealing(void);
void TGTHT510_supply_time_stage_start(void);
void TGTHT510_supply_time_stage_end(void);
void TGTHT510_supply_time_stage_get(uint32 *time_val);
void TGTHT510_supply_time_step_start(void);
void TGTHT510_supply_time_step_end(void);
uint16	TGTHT510_supply_time_step_is_get(uint32 const_val);


#endif

