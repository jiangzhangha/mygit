/**
  ******************************************************************************
  * @file    TGTHT510_collectANDgroup.c
  * @author  ����
  * @version V1.00
  * @date    20150626
  * @brief   �ռ�վ���Ĳ��ƽ�������ң��״̬�ɼ�����֡ģ��C�ļ�
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"

extern uint16 TGTHT510_1553B_data_TGTHT100[];						//ȫ�����飬�����ƽ�ң����·�г��¶Ȳ����������ݣ�89��
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[];				//ȫ�����飬�����ƽ�ң����·�и�֡A�¶����ݣ�65��
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[];				//ȫ�����飬�����ƽ�ң����·�и�֡B�¶����ݣ�65��
extern uint16 TGTHT510_1553B_data_TGTHT530[];						//ȫ�����飬����ѹ�������������ң�����ݣ�12��
extern uint16 TGTHT510_1553B_data_TGTHT520a[];						//ȫ�����飬�����ƽ���������������ң�⣬7��
extern uint16 TGTHT510_1553B_data_TGTHT520b[];						//ȫ�����飬�����ƽ���������������ң�⣬7��

extern TGTHT510_which_bus_TypeDef TGTHT510_which_bus;//�����л�ȫ�ֱ���

extern TGTHT510_supply_ctrl_TypeDef TGTHT510_supply_ctrl;

extern TGTHT510_supply_input_par_TypeDef TGTHT510_supply_input_par;

extern TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;

extern uint16 TGTHT510_fault_data_CG_push[7];						//�ƽ��ʼ�-����ң�����
extern uint16 TGTHT510_fault_data_CG_supply[30];					//���ӹʼ�-����ң�����

extern uint16 mode_test;//����ʹ��


/*����ң��ȫ�ֱ���-------------------------------------------------------------*/	

uint16 TGTHT510_1553B_data_CG[140];	 //����ң�����飬��135����

uint16 CG_EPDU_count; //EPDUԴ�����м���

uint16 CG_heater_state_data[7];    //���������״̬������ң���ʽ˳��
uint16 CG_valve_state_data[23];    //���淧�ſ���״̬������ң���ʽ˳��
uint16 CG_yk_switch_state_data[4]; //����ң�ط��ſ���״̬������λ����״̬������ң���ʽ

uint16 CG_place_signal_enable_disable;//���䵽λ�ź�ʹ�ܽ�ֹ��־
uint16 CG_TGTHT510_cpu_state; //�ƽ�������cpu״̬
uint16 CG_tempercontrol_power; //�ȿع���
uint16 CG_inputcommand_receive_state_data[2]; //ע��ָ�����״̬
uint16 CG_equiment_command[3];//��Ϊ����ң���´����豸����ָ��ֱ�Ϊ��������ʶ���̿�APID���̿�Ӧ�����ݡ�
uint16 CG_supply_fault_state_data[30]; //���ӹʼ�״̬
uint16 CG_equiment_receive_state_data[6]; //�豸�����ݽ���״̬
uint16 CG_HYCT_receive_state_data[16]; //���ջ����Ľ�������
uint16 CG_count_number; //֡����
uint16 CG_bus_command[2];//��������ָ��´�ָ��������У���

/*����ң��ȫ�ֱ���-------------------------------------------------------------*/	

uint16 TGTHT510_1553B_data_GC[32];	//����ң�����飬��32����

uint16 GC_EPDU_count;//EPDUԴ�����м���

uint16 GC_pressure_gas_bottle[6];//��ƿ����ѹ��
uint16 GC_pressure_liquid_bottle[6];//������ǻ��Һǻ����ѹ��
uint16 GC_pressure_pipe[4];//��·ѹ��
uint16 GC_remainder_liquid[6];//����ʣ����

uint8 GC_pressure_compressor_A;//ѹ����A����ѹ��
uint8 GC_pressure_compressor_B;//ѹ����B����ѹ��
uint8 GC_pressure_compressor_C;//ѹ����C����ѹ��

uint8 GC_pressure_engine_C_O;//�˿�C���������ι�ѹ��
uint8 GC_pressure_engine_C_F;//�˿�C����ȼ���ι�ѹ��

uint8 GC_supply_flag; //�������б�־
uint16 GC_TJ_flag; //�ƽ�����״̬��־

uint16 GC_supply_name_state_data;	//���ӽ׶���

/*�Ǳ�ң��ȫ�ֱ���-------------------------------------------------------------*/	

uint16 TGTHT510_1553B_data_YB[21];  //�Ǳ�ң�����飬��21����

uint16 YB_EPDU_count;//EPDUԴ�����м���

uint16 YB_TJ_flag; //�ƽ�����״̬
uint16 YB_supply_flag; //���ӽ׶α�־
uint16 YB_supply_state; //��������״̬��־
uint16 YB_fault_state; //���ϴ���״̬

uint16 YB_pressure_gas_bottle[6];//��ƿ����ѹ��
uint16 YB_remainder_liquid[6];//����ʣ����


/*�豸����ָ��ȫ�ֱ���-------------------------------------------------------------*/	
uint16 TGTHT510_1553B_data_equiment_command[11];//�豸����ָ���11����

uint16 equiment_command_EPDU_count;//�豸����ָ��֡���к�

/*��������ָ��ȫ�ֱ���-------------------------------------------------------------*/

uint16 TGTHT510_1553B_data_ask_for_service;

/*�ͻ�������ȫ�ֱ���-------------------------------------------------------------*/
uint16 TGTHT510_1553B_data_HYCT[37];

uint16 HYCT_EPDU_count; //EPDUԴ�����м���

uint16 HYCT_data[32];//�ͻ��˷ɴ�ң������

/*��GNC�ʼ����ȫ�ֱ���-------------------------------------------------------------*/
uint16 TGTHT510_1553B_data_GNC[7];

uint16 GNC_EPDU_count; //EPDUԴ�����м���

/*���ڴ��´�����ȫ�ֱ���-------------------------------------------------------------*/

uint16 TGTHT510_1553B_data_MEMORY[255];

uint16 MEMORY_data[250];

uint16 MEMORY_EPDU_count; //EPDUԴ�����м���




/*��ѯ��------------------------------------------------------------------------*/	

const uint16 yk_state_from_FPGA_bit[46]={
	BIT06,//LVb39,41��
	BIT07,//LVb49,51��
	BIT08,//LVb59,61��
	BIT09,//LVb63,65��
	BIT10,//LVb40,42��
	BIT11,//LVb50,52��
	BIT12,//LVb60,62��
	BIT13,//LVb64,66��
	BIT00,//LVb7��
	BIT01,//LVb8��
	BIT02,//LVb9��
	BIT03,//LVb10��
	BIT04,//LVb11��
	BIT05,//LVb12��
	BIT14,//LVb13,15��
	BIT00,//LVb23��
	BIT01,//LVb24��
	BIT15,//LVb14,16��
	BIT05,//LVb73,77��
	BIT06,//LVb73,71��
	BIT07,//LVb73,81��
	BIT08,//LVb73,85��
	BIT09,//LVb78,74��
	BIT10,//LVb72,74��
	BIT11,//LVb82,74��
	BIT12,//LVb86,74��
	BIT13,//LVb73,69��
	BIT14,//LVb70,74��
	BIT00,//��1���䵽λ����1
	BIT01,//��1���䵽λ����2
	BIT02,//��1���䵽λ����3
	BIT03,//��2���䵽λ����1
	BIT04,//��2���䵽λ����2
	BIT05,//��2���䵽λ����3
	BIT06,//��3���䵽λ����1
	BIT07,//��3���䵽λ����2
	BIT08,//��3���䵽λ����3
	BIT09,//ȼ1���䵽λ����1
	BIT10,//ȼ1���䵽λ����2
	BIT11,//ȼ1���䵽λ����3
	BIT12,//ȼ2���䵽λ����1
	BIT13,//ȼ2���䵽λ����2
	BIT14,//ȼ2���䵽λ����3
	BIT15,//ȼ3���䵽λ����1
	BIT00,//ȼ3���䵽λ����2
	BIT01//ȼ3���䵽λ����3

};

const uint16 yk_state_from_FPGA_word[46]={
	WORD02,//LVb39,41��
	WORD02,//LVb49,51��
	WORD02,//LVb59,61��
	WORD02,//LVb63,65��
	WORD02,//LVb40,42��
	WORD02,//LVb50,52��
	WORD02,//LVb60,62��
	WORD02,//LVb64,66��
	WORD02,//LVb7��
	WORD02,//LVb8��
	WORD02,//LVb9��
	WORD02,//LVb10��
	WORD02,//LVb11��
	WORD02,//LVb12��
	WORD02,//LVb13,15��
	WORD03,//LVb23��
	WORD03,//LVb24��
	WORD02,//LVb14,16��
	WORD03,//LVb73,77��
	WORD03,//LVb73,71��
	WORD03,//LVb73,81��
	WORD03,//LVb73,85��
	WORD03,//LVb78,74��
	WORD03,//LVb72,74��
	WORD03,//LVb82,74��
	WORD03,//LVb86,74��
	WORD03,//LVb73,69��
	WORD03,//LVb70,74��
	WORD00,//��1���䵽λ����1
	WORD00,//��1���䵽λ����2
	WORD00,//��1���䵽λ����3
	WORD00,//��2���䵽λ����1
	WORD00,//��2���䵽λ����2
	WORD00,//��2���䵽λ����3
	WORD00,//��3���䵽λ����1
	WORD00,//��3���䵽λ����2
	WORD00,//��3���䵽λ����3
	WORD00,//ȼ1���䵽λ����1
	WORD00,//ȼ1���䵽λ����2
	WORD00,//ȼ1���䵽λ����3
	WORD00,//ȼ2���䵽λ����1
	WORD00,//ȼ2���䵽λ����2
	WORD00,//ȼ2���䵽λ����3
	WORD00,//ȼ3���䵽λ����1
	WORD01,//ȼ3���䵽λ����2
	WORD01//ȼ3���䵽λ����3
	
};


const uint16 yk_state_to_CG_bit[46]={
	BIT08,//LVb39,41��
	BIT09,//LVb49,51��
	BIT10,//LVb59,61��
	BIT11,//LVb63,65��
	BIT12,//LVb40,42��
	BIT13,//LVb50,52��
	BIT14,//LVb60,62��
	BIT15,//LVb64,66��
	BIT00,//LVb7��
	BIT01,//LVb8��
	BIT02,//LVb9��
	BIT03,//LVb10��
	BIT04,//LVb11��
	BIT05,//LVb12��
	BIT06,//LVb13,15��
	BIT07,//LVb23��
	BIT08,//LVb24��
	BIT09,//LVb14,16��
	BIT10,//LVb73,77��
	BIT11,//LVb73,71��
	BIT12,//LVb73,81��
	BIT13,//LVb73,85��
	BIT14,//LVb78,74��
	BIT15,//LVb72,74��
	BIT00,//LVb82,74��
	BIT01,//LVb86,74��
	BIT02,//LVb73,69��
	BIT03,//LVb70,74��
	
	BIT04|BIT05,//��1���䵽λ����1
	BIT06|BIT07,//��1���䵽λ����2
	BIT08|BIT09,//��1���䵽λ����3
	BIT10|BIT11,//��2���䵽λ����1
	BIT12|BIT13,//��2���䵽λ����2
	BIT14|BIT15,//��2���䵽λ����3
	BIT00|BIT01,//��3���䵽λ����1
	BIT02|BIT03,//��3���䵽λ����2
	BIT04|BIT05,//��3���䵽λ����3
	BIT06|BIT07,//ȼ1���䵽λ����1
	BIT08|BIT09,//ȼ1���䵽λ����2
	BIT10|BIT11,//ȼ1���䵽λ����3
	BIT12|BIT13,//ȼ2���䵽λ����1
	BIT14|BIT15,//ȼ2���䵽λ����2
	BIT00|BIT01,//ȼ2���䵽λ����3
	BIT02|BIT03,//ȼ3���䵽λ����1
	BIT04|BIT05,//ȼ3���䵽λ����2
	BIT06|BIT07//ȼ3���䵽λ����3

};


const uint16 yk_state_to_CG_word[46]={
	WORD00,//LVb39,41��
	WORD00,//LVb49,51��
	WORD00,//LVb59,61��
	WORD00,//LVb63,65��
	WORD00,//LVb40,42��
	WORD00,//LVb50,52��
	WORD00,//LVb60,62��
	WORD00,//LVb64,66��
	WORD00,//LVb7��
	WORD00,//LVb8��
	WORD00,//LVb9��
	WORD00,//LVb10��
	WORD00,//LVb11��
	WORD00,//LVb12��
	WORD00,//LVb13,15��
	WORD00,//LVb23��
	WORD01,//LVb24��
	WORD01,//LVb14,16��
	WORD01,//LVb73,77��
	WORD01,//LVb73,71��
	WORD01,//LVb73,81��
	WORD01,//LVb73,85��
	WORD01,//LVb78,74��
	WORD01,//LVb72,74��
	WORD01,//LVb82,74��
	WORD01,//LVb86,74��
	WORD01,//LVb73,69��
	WORD01,//LVb70,74��
	
	WORD01,//��1���䵽λ����1
	WORD01,//��1���䵽λ����2
	WORD02,//��1���䵽λ����3
	WORD02,//��2���䵽λ����1
	WORD02,//��2���䵽λ����2
	WORD02,//��2���䵽λ����3
	WORD02,//��3���䵽λ����1
	WORD02,//��3���䵽λ����2
	WORD02,//��3���䵽λ����3
	WORD02,//ȼ1���䵽λ����1
	WORD03,//ȼ1���䵽λ����2
	WORD03,//ȼ1���䵽λ����3
	WORD03,//ȼ2���䵽λ����1
	WORD03,//ȼ2���䵽λ����2
	WORD03,//ȼ2���䵽λ����3
	WORD03,//ȼ3���䵽λ����1
	WORD03,//ȼ3���䵽λ����2
	WORD03//ȼ3���䵽λ����3
	
};




	
const uint16 heater_read_word_bit[100]={	0x0001,0x0001,0x0002,0x0002,0x0004,0x0004,0x0008,0x0008,0x0010,0x0010,//sc1~10
											0x0020,0x0020,0x0040,0x0040,0x0080,0x0080,0x0100,0x0100,0x0200,0x0200,//sc11~20
											0x0400,0x0400,0x0800,0x0800,0x1000,0x1000,0x2000,0x2000,0x4000,0x4000,//sc21~30
											0x8000,0x8000,0x0001,0x0001,0x0002,0x0002,0x0004,0x0004,0x0008,0x0008,//sc31~40
											0x0010,0x0010,0x0020,0x0020,0x0040,0x0040,0x0080,0x0080,0x0100,0x0100,//sc41~50
											0x0200,0x0200,0x0400,0x0400,0x0800,0x0800,0x1000,0x1000,0x2000,0x2000,//sc51~60
											0x4000,0x4000,0x8000,0x8000,0x0001,0x0001,0x0002,0x0002,0x0004,0x0004,//sc61~70
											0x0008,0x0008,0x0010,0x0010,0x0020,0x0020,0x0040,0x0040,0x0080,0x0080,//sc71~80
											0x0100,0x0100,0x0200,0x0200,0x0400,0x0400,0x0800,0x0800,0x1000,0x1000,//sc81~90
											0x2000,0x2000,0x4000,0x4000,0x8000,0x8000,0x0001,0x0001,0x0002,0x0002//sc91~100
											};//���Ȼ�·��λ����

const uint16 heater_read_word_byte[100]={	0,4,0,4,0,4,0,4,0,4,//sc1~10
											0,4,0,4,0,4,0,4,0,4,//sc11~20
											0,4,0,4,0,4,0,4,0,4,//sc21~30
											0,4,1,5,1,5,1,5,1,5,//sc31~40
											1,5,1,5,1,5,1,5,1,5,//sc41~50
											1,5,1,5,1,5,1,5,1,5,//sc51~60
											1,5,1,5,2,6,2,6,2,6,//sc61~70
											2,6,2,6,2,6,2,6,2,6,//sc71~80
											2,6,2,6,2,6,2,6,2,6,//sc81~90
											2,6,2,6,2,6,3,7,3,7//sc91~100											
};

//0:0x0001
//1:0x0002
//2:0x0004
//3:0x0008
//4:0x0010
//5:0x0020
//6:0x0040
//7:0x0080
//8:0x0100
//9:0x0200
//10:0x0400
//11:0x0800
//12:0x1000
//13:0x2000
//14:0x4000
//15:0x8000
const uint16 heater_write_word_bit[100]={	0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000,0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,//sc01~16
											0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000,0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,//sc17~32
											0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000,0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,//sc33~48
											0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000,0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,//sc49~64
											0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000,0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,//sc65~80
											0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000,0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,//sc81~96
											0x0100,0x0200,0x0400,0x0800//sc97~100
};


const uint16 heater_write_word_byte[100]={	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//sc1~16
											1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//sc17~32
											2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,//sc33~48
											3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,//sc49~64
											4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,//sc65~80
											5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,//sc81~96
											6,6,6,6//sc97~100	
};


const uint16 valve_read_word_bit[88]={	0x0001,0x0001,0x0080,0x0080,0x0080,0x0001,0x0002,0x0002,0x0100,0x0100,//LVb1~10
										0x0100,0x0002,0x0004,0x0004,0x0008,0x0008,0x0010,0x0010,0x0020,0x0020,//LVb11~20
										0x0040,0x0040,0x2000,0x4000,0x0100,0x0200,0x0400,0x0080,0x0800,0x0100,//LVb21~30
										0x1000,0x0200,0x2000,0x0400,0x4000,0x0800,0x8000,0x1000,0x0001,0x0001,//LVb31~40
										0x0002,0x0002,0x0004,0x0004,0x0008,0x0008,0x0010,0x0010,0x0080,0x0001,//LVb41~50
										0x0100,0x0002,0x0200,0x0004,0x0400,0x0008,0x0800,0x0010,0x2000,0x0020,//LVb51~60
										0x4000,0x0040,0x0020,0x0020,0x0040,0x0040,0x0200,0x0200,0x0400,0x0400,//LVb61~70
										0x0004,0x0200,0x0008,0x0400,0x0800,0x0800,0x0010,0x0800,0x2000,0x2000,//LVb71~80
										0x0020,0x2000,0x4000,0x4000,0x0040,0x4000,0x0080,0x8000//LVb81~87,DVb
};


const uint16 valve_K_read_word_byte[88]={	6,0,4,2,10,8,6,0,4,2,//LVb1~10
											10,8,6,0,6,0,6,0,6,0,//LVb11~20
											6,0,0,0,6,6,6,0,6,0,//LVb21~30
											6,0,6,0,6,0,6,0,2,4,//LVb31~40
											2,4,2,4,2,4,2,4,8,10,//LVb41~50
											8,10,8,10,8,10,8,10,8,10,//LVb51~60
											8,10,2,4,2,4,2,4,2,4,//LVb61~70
											8,10,8,10,2,4,8,10,2,4,//LVb71~80
											8,10,2,4,8,10,6,0//LVb81~87,DVb
	
};


//0��1:0x0003--------//8��9:0x0300
//2��3:0x000c--------//10��11:0x0c00
//4��5:0x0030--------//12��13:0x3000
//6��7:0x00c0--------//14��15:0xc000
//8��9:0x0300
//10��11:0x0c00
//12��13:0x3000
//14��15:0xc000


const uint16 valve_K_YC_write_word_bit[88]={0x000c,0x6000,0xc000,0x00c0,0x000c,0xc000,0x00c0,0x000c,0x000c,0x0c00,//LVb1~10��
											0x00c0,0x000c,0x0c00,0x00c0,0xc000,0x0c00,0x000c,0xc000,0x00c0,0x000c,//LVb11~20��
											0x0c00,0x00c0,0x000c,0x00c0,0x0c00,0xc000,0x0c00,0x0c00,0xc000,0xc000,//LVb21~30��
											0x000c,0x000c,0x00c0,0x00c0,0x0c00,0x0c00,0xc000,0xc000,0x0c00,0x000c,//LVb31~40��
											0xc000,0x00c0,0x000c,0x0c00,0x00c0,0xc000,0x0c00,0x000c,0x0c00,0x00c0,//LVb41~50��
											0xc000,0x0c00,0x000c,0xc000,0x00c0,0x000c,0x0c00,0x00c0,0xc000,0x0c00,//LVb51~60��
											0x000c,0xc000,0xc000,0x00c0,0x000c,0x0c00,0xc000,0x00c0,0x000c,0x0c00,//LVb61~70��
											0x00c0,0x0c00,0x0c00,0xc000,0x00c0,0xc000,0xc000,0x000c,0x0c00,0x000c,//LVb71~80��
											0x000c,0x00c0,0xc000,0x00c0,0x00c0,0x0c00,0x000c,0x00c0//LVb81~87,DVb��
	
};




const uint16 valve_K_YC_write_word_byte[88]={	13,0,10,6,20,15,13,0,10,7,//LVb1~10��
												20,15,14,0,14,1,14,1,14,1,//LVb11~20��
												15,1,3,3,4,4,12,2,12,2,//LVb21~30��
												12,2,12,2,13,3,13,3,5,8,//LVb31~40��
												5,8,5,9,5,9,6,9,17,18,//LVb41~50��
												17,19,17,19,17,19,18,19,18,20,//LVb51~60��
												18,20,6,9,6,10,7,10,7,11,//LVb61~70��
												15,21,16,21,7,11,16,21,8,11,//LVb71~80��
												16,21,8,11,16,22,4,4//LVb81~87,DVb��
};

//0��1:0x0003
//2��3:0x000c
//4��5:0x0030
//6��7:0x00c0
//8��9:0x0300
//10��11:0x0c00
//12��13:0x3000
//14��15:0xc000


const uint16 valve_G_YC_write_word_bit[88]={0x0030,0x0003,0x0003,0x0300,0x0030,0x0003,0x0300,0x0030,0x0030,0x3000,//LVb1~10��
											0x0300,0x0030,0x3000,0x0300,0x0003,0x3000,0x0030,0x0003,0x0300,0x0030,//LVb11~20��
											0x3000,0x0300,0x0030,0x0300,0x3000,0x0003,0x3000,0x3000,0x0003,0x0003,//LVb21~30��
											0x0030,0x0030,0x0300,0x0300,0x3000,0x3000,0x0003,0x0003,0x3000,0x0030,//LVb31~40��
											0x0003,0x0300,0x0030,0x3000,0x0300,0x0003,0x3000,0x0030,0x3000,0x0300,//LVb41~50��
											0x0003,0x3000,0x0030,0x0003,0x0300,0x0030,0x3000,0x0300,0x0003,0x3000,//LVb51~60��
											0x0030,0x0003,0x0003,0x0300,0x0030,0x3000,0x0003,0x0300,0x0030,0x3000,//LVb61~70��
											0x0300,0x3000,0x3000,0x0003,0x0300,0x0003,0x0003,0x0030,0x3000,0x0030,//LVb71~80��
											0x0030,0x0300,0x0003,0x0300,0x0300,0x3000,0x0030,0x0300//LVb81~87,DVb��	
};



const uint16 valve_G_YC_write_word_byte[88]={	13,0,10,7,20,15,14,0,10,7,//LVb1~10��
												21,15,14,1,14,1,14,1,15,1,//LVb11~20��
												15,2,3,4,4,4,12,2,12,2,//LVb21~30��
												12,2,13,3,13,3,13,3,5,8,//LVb31~40��
												5,9,5,9,6,9,6,9,17,19,//LVb41~50��
												17,19,17,19,18,19,18,20,18,20,//LVb51~60��
												18,20,6,10,6,10,7,11,7,11,//LVb61~70��
												16,21,16,21,8,11,16,21,8,11,//LVb71~80��
												16,22,8,12,17,22,4,5//LVb81~87,DVb��
};



									  //0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
const uint8 equiment_command_code[256]={0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,0x80,0x81,0x82,0x83,//0x00
										0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,0x90,0x91,0x92,0x93,//0x01
										0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,0xA0,0xA1,0xA2,0xA3,//0x02
										0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,0xE0,0xE1,//0x03
										0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,0xF0,0xF1,//0x04
										0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,0x01,0x02,//0x05
										0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x8A,0x8C,0x8E,0x8B,//0x06
										0x8D,0x8F,0x90,0x92,0x94,0x91,0x93,0x95,0x29,0x29,0x29,0x2A,0x2A,0x2A,0x25,0x26,//0x07
										0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x08
										0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x09
										0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x0A
										0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x0B
										0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x0C
										0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x0D
										0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x0E
										0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00//0x0F
	
};//�豸����ָ���ѯ�����޸ģ���������


									   //0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
const uint8 equiment_command_code1[256]={0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//0x00
										 0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//0x01
										 0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//0x02
										 0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//0x03
										 0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//0x04
										 0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//0x05
										 0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x03,0x03,0x03,0x03,//0x06
										 0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,0x02,0x02,0x02,0x02,0x02,0x06,0x06,//0x07
										 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x08
										 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x09
										 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x0A
										 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x0B
										 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x0C
										 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x0D
										 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x0E
										 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00//0x0F
	
};//�豸����ָ���ѯ����һ���ֽڣ����޸ģ���������







/******************************************************************************************
**���ƣ�ң��״̬�ɼ�ģ���ʼ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/


void TGTHT510_collectANDgroup_initial(void)
 {
	 uint16 i;


	
/*����ң�������ʼ��---------------------------------------------------------------------*/	 
	 
	 for(i=0;i<=139;i++)
	 {
		TGTHT510_1553B_data_CG[i]=0x0000;//����ң���ʼ�� 
	 }
	 
	 
	 for(i=0;i<=6;i++)
	 {
		 CG_heater_state_data[i]=0xffff;//������״̬�����ʼ��		 
	 }
	 
	 for(i=0;i<=22;i++)
	 {
		CG_valve_state_data[i]=0x0000;//���ſ���״̬�����ʼ�� 
		 
	 }
	 
	 for(i=0;i<=3;i++)
	 {
		CG_yk_switch_state_data[i]=0x0000; //����ң�ط��ſ���״̬������λ����״̬��ʼ��
	 }
	 
	 for(i=0;i<=1;i++)
	 {
		 CG_inputcommand_receive_state_data[i]=0x0000; //ע��ָ�����״̬��ʼ��
	 }
	 
	 for(i=0;i<=29;i++)
	 {
		 CG_supply_fault_state_data[i]=0x0000;//���ӹʼ�״̬��ʼ��
	 }
	 
	 for(i=0;i<=5;i++)
	 {
		 CG_equiment_receive_state_data[i]=0x0000;//�豸�����ݽ���״̬��ʼ��
	 }
	 
	 for(i=0;i<=15;i++)
	 {
		 CG_HYCT_receive_state_data[i]=0x0000;//���ջ����Ľ������ݳ�ʼ��
	 }
	 
	 for(i=0;i<=2;i++)
	 {
		 CG_equiment_command[i]=0x0000;//�豸����ָ����Ϊ����ң���´�
	 }
	 
	 for(i=0;i<=1;i++)
	 {
		 CG_bus_command[i]=0x0000;//����ָ��ָ����Ϊ����ң���´�
	 }
	 
	 CG_tempercontrol_power=0x0000;//�ȿع���
	 
	 
	 if(get_CPU()==CPU_B)//B��
	 {
		CG_TGTHT510_cpu_state=0x0b0b;//�ƽ�������cpu״̬
	 }
	
	 else//A��
	 {
		CG_TGTHT510_cpu_state=0x0a0a;//�ƽ�������cpu״̬
	 }
	 
	 CG_count_number=0x0000; //֡����
	 
	 CG_place_signal_enable_disable=0x6f6f;
	 
	 CG_EPDU_count=0x0000; //EPDUԴ�����м���
	 
	 

	 
/*����ң�������ʼ��---------------------------------------------------------------------*/	 
	 
	 for(i=0;i<=31;i++)
	 {
		TGTHT510_1553B_data_GC[i]=0x0000;//����ң���ʼ�� 
	 }
	 
	 for(i=0;i<=5;i++)
	 {
		GC_pressure_gas_bottle[i]=0x0000; //��ƿ����ѹ��
	 }
	 
	 for(i=0;i<=5;i++)
	 {
		GC_pressure_liquid_bottle[i]=0x0000; //������ǻ��Һǻ����ѹ��
	 }
	 
	 for(i=0;i<=3;i++)
	 {
		GC_pressure_pipe[i]=0x0000; //��·ѹ��
	 }
	 
	 for(i=0;i<=5;i++)
	 {
		GC_remainder_liquid[i]=0x0000; //����ʣ����
	 }
	 
	 GC_pressure_compressor_A=0x00;//ѹ����A����ѹ��
	 GC_pressure_compressor_B=0x00;//ѹ����B����ѹ��
	 GC_pressure_compressor_C=0x00;//ѹ����C����ѹ��
	 
	 GC_pressure_engine_C_O=0x00;//�˿�C���������ι�ѹ��
	 GC_pressure_engine_C_F=0x00;//�˿�C����ȼ���ι�ѹ��
	 
	 GC_supply_flag=0x00; //�������б�־
	 GC_TJ_flag=0x00; //�ƽ�����״̬��־
	 
	 GC_supply_name_state_data=0x0000;	//���ӽ׶���
	 
	 GC_EPDU_count=0x0000; //EPDUԴ�����м���
	 
/*�Ǳ�ң�������ʼ��---------------------------------------------------------------------*/	 
	 
	 for(i=0;i<=20;i++)
	 {
		TGTHT510_1553B_data_YB[i]=0x0000;//�Ǳ�ң���ʼ�� 
	 }
	 
	 YB_TJ_flag=0x0000; //�ƽ�����״̬
	 YB_supply_flag=0x0000; //���ӽ׶α�־
	 YB_supply_state=0x0000; //��������״̬��־
	 YB_fault_state=0x0000; //���ϴ���״̬
	 
	 for(i=0;i<=5;i++)
	 {
		YB_pressure_gas_bottle[i]=0x0000;//��ƿ����ѹ��
	 }
	 
	 for(i=0;i<=5;i++)
	 {
		YB_remainder_liquid[i]=0x0000;//����ʣ���� 
	 }
	 
	 YB_EPDU_count=0x0000;//EPDUԴ�����м���

/*�豸����ָ�������ʼ��---------------------------------------------------------------------*/	 
	 
	 for(i=0;i<=10;i++)
	 {
		TGTHT510_1553B_data_equiment_command[i]=0x0000; //�豸����ָ��
	 }
	 
	 equiment_command_EPDU_count=0x0000;//�豸����ָ��֡���к�
	 
/*��������ָ�������ʼ��---------------------------------------------------------------------*/	 
	 
	 TGTHT510_1553B_data_ask_for_service=0x0000;

/*�ͻ��˷ɴ�������ʼ��---------------------------------------------------------------------*/	 
	 
	 for(i=0;i<=36;i++)
	 {
		 TGTHT510_1553B_data_HYCT[i]=0x0000;
	 }
	 
	 for(i=0;i<=31;i++)
	 {
		 HYCT_data[i]=0x0000;
	 }
	 
	 HYCT_EPDU_count=0x0000;
	 
/*��GNC�ʼ������ʼ��---------------------------------------------------------------------*/	 
	 for(i=0;i<=6;i++)
	 {
		 TGTHT510_1553B_data_GNC[i]=0x0000;
	 }
	 
	 GNC_EPDU_count=0x0000;
	 
/*���ڴ��´�������ʼ��---------------------------------------------------------------------*/	 
	 for(i=0;i<=254;i++)
	 {
		 TGTHT510_1553B_data_MEMORY[i]=0x0000;
	 }
	 
	 for(i=0;i<=249;i++)
	 {
		 MEMORY_data[i]=0x0000;
	 }
	 
	 MEMORY_EPDU_count=0x0000;
	 
 
 }

/******************************************************************************************
**���ƣ�ң��ɼ�����֡ģ��������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_collectANDgroup_main(void)
{
	
	TGTHT510_collectANDgroup_heater_state_collect_save();//������״̬�ɼ��뻺��
	
	TGTHT510_collectANDgroup_yk_state_collect_save();//OCָ���뵽λ�źŶ�ȡ
	
	//TGTHT510_collectANDgroup_CG_group();//����ң��������֡
	//TGTHT510_collectANDgroup_GC_group();//����ң��������֡
	//TGTHT510_collectANDgroup_HYCT_group();//�ͻ���ң��������֡
	//TGTHT510_collectANDgroup_GNC_group();//����ת��GNC�ʼ�״̬��
	
	
}



/******************************************************************************************
**���ƣ�������״̬�ɼ��뻺�溯��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_collectANDgroup_heater_state_collect_save(void)
{
	uint16 state[7];
	uint16 i,j;
	uint16 state_gk;//��ر��ݼ���״̬
	
	
	state[0]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG0);
	state[1]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG1);
	state[2]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG2);
	state[3]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG3);
	state[4]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG4);
	state[5]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG5);
	state[6]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG6);
	state[7]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG7);//��ȡ�����������״̬

	for(i=0;i<=6;i++)
	{
		CG_heater_state_data[i]=0xffff;//������״̬������ʼ��		 
	}
	
	
	for(i=0;i<=99;i++)
	{
		if(TGTHT510_collectANDgroup_is_heater_state(state,i)==HEATER_ON)//ĳ���»�·������Ϊ��ͨ״̬
		{
			j=heater_write_word_byte[i];
			CG_heater_state_data[j]=CG_heater_state_data[j]&(~heater_write_word_bit[i]);	
		}
		
		else
		{
			asm("nop;");
		}

	}
	
	state_gk=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_GK);
	
	if((state_gk&0xc000)==0x8000)//ͨ
	{
		CG_heater_state_data[6]=CG_heater_state_data[6]&0xefff;
	}
	
	else if((state_gk&0xc000)==0x4000)//��
	{
		asm("nop;");
	}
	
	else
	{
		asm("nop;");
	}
	
	

}



/******************************************************************************************
**���ƣ�������״̬�жϺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

//������Ȼ�·��·�ţ�0~99��������״̬����p�����ؼ�������״̬
uint16 TGTHT510_collectANDgroup_is_heater_state(uint16 *p,uint16 sc_number)
{
	uint16 i,m;
	i=heater_read_word_byte[sc_number];
	m=p[i]&heater_read_word_bit[sc_number];
	if(m!=0)
	{
		return HEATER_ON;
	}
	
	else
	{
		return HEATER_OFF;
	}

}


/******************************************************************************************
**���ƣ�����״̬�ɼ��뻺�溯��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_collectANDgroup_valve_state_collect_save(void)
{
	uint16 state[12];
	uint16 k_num,g_num,k_state,g_state;
	uint16 i,j,k,m;
	
	state[0]=~Read_32_to_16(*(volatile uint32 *)VALVE_STATE_READ_REG0);
	state[1]=~Read_32_to_16(*(volatile uint32 *)VALVE_STATE_READ_REG1);
	state[2]=~Read_32_to_16(*(volatile uint32 *)VALVE_STATE_READ_REG2);
	state[3]=~Read_32_to_16(*(volatile uint32 *)VALVE_STATE_READ_REG3);
	state[4]=~Read_32_to_16(*(volatile uint32 *)VALVE_STATE_READ_REG4);
	state[5]=~Read_32_to_16(*(volatile uint32 *)VALVE_STATE_READ_REG5);
	state[6]=~Read_32_to_16(*(volatile uint32 *)VALVE_STATE_READ_REG6);
	state[7]=~Read_32_to_16(*(volatile uint32 *)VALVE_STATE_READ_REG7);
	state[8]=~Read_32_to_16(*(volatile uint32 *)VALVE_STATE_READ_REG8);
	state[9]=~Read_32_to_16(*(volatile uint32 *)VALVE_STATE_READ_REG9);
	state[10]=~Read_32_to_16(*(volatile uint32 *)VALVE_STATE_READ_REG10);
	state[11]=~Read_32_to_16(*(volatile uint32 *)VALVE_STATE_READ_REG11);
	//��ȡң��״̬��ȡ����
	//��δ�ӵ磬����״̬��Ϊ��
	//���Ŵ򿪣���״̬�ߣ���״̬��
	//���Źرգ���״̬�ͣ���״̬��
	//���ų�ʼ�ӵ磬�򿪹�״̬��Ϊ��
	
	
	
	for(i=0x00;i<=0x56;i++)//LVb1~87
	{
		k_num=valve_K_read_word_byte[i];//���ſ�״̬�����ֽں�
		g_num=k_num+1;
		k_state=state[k_num]&valve_read_word_bit[i];
		g_state=state[g_num]&valve_read_word_bit[i];
		if((k_state!=0)&&(g_state==0))
		{
			m=valve_K_YC_write_word_byte[i];
			CG_valve_state_data[m]=CG_valve_state_data[m]|valve_K_YC_write_word_bit[i];//ң�����ݷ��ſ�״̬��λ
			m=valve_G_YC_write_word_byte[i];
			CG_valve_state_data[m]=CG_valve_state_data[m]&(~valve_G_YC_write_word_bit[i]);//ң�����ݷ��Ź�״̬����	
		}
		
		else if((k_state==0)&&(g_state!=0))
		{
			m=valve_G_YC_write_word_byte[i];
			CG_valve_state_data[m]=CG_valve_state_data[m]|valve_G_YC_write_word_bit[i];//ң�����ݷ��Ź�״̬��λ
			m=valve_K_YC_write_word_byte[i];
			CG_valve_state_data[m]=CG_valve_state_data[m]&(~valve_K_YC_write_word_bit[i]);//ң�����ݷ��ſ�״̬����	
		}
		else
		{
			i=i;
		}

	}
	

	j=valve_K_read_word_byte[0x57];//DVb1��״̬�����ֽں�
	k=state[j]&valve_read_word_bit[0x57];
	if(k!=0)
	{
		m=valve_K_YC_write_word_byte[0x57];
		CG_valve_state_data[m]=CG_valve_state_data[m]|valve_K_YC_write_word_bit[0x57];//ң������DVb1���ſ�״̬��λ
		m=valve_G_YC_write_word_byte[0x57];
		CG_valve_state_data[m]=CG_valve_state_data[m]&(~valve_G_YC_write_word_bit[0x57]);//ң������DVb1���Ź�״̬����
		
	}
	else
	{
		m=valve_G_YC_write_word_byte[0x57];
		CG_valve_state_data[m]=CG_valve_state_data[m]|valve_G_YC_write_word_bit[0x57];//ң������DVb1���Ź�״̬��λ
		m=valve_K_YC_write_word_byte[0x57];
		CG_valve_state_data[m]=CG_valve_state_data[m]&(~valve_K_YC_write_word_bit[0x57]);//ң������DVb1���ſ�״̬����
		
	}

	
}

/******************************************************************************************
**���ƣ�����״̬�жϺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_collectANDgroup_is_valve_state(uint16 valve_number)
{
	uint16 i,j,k,m,n;
	uint16 state_on,state_off;
	if(valve_number<=0x57)//����ķ����ڲ���źϷ�
	{
		i=valve_K_YC_write_word_byte[valve_number];//���ſ�״̬ң���ֽں�
		j=valve_K_YC_write_word_bit[valve_number];//���ſ�״̬λ������
		if((CG_valve_state_data[i]&j)==j)
		{
			state_on=TRUE;
		}
		
		else
		{
			state_on=FALSE;
		}
		
		i=valve_G_YC_write_word_byte[valve_number];//���Ź�״̬ң���ֽں�
		j=valve_G_YC_write_word_bit[valve_number];//���Ź�״̬λ������
		if((CG_valve_state_data[i]&j)==j)
		{
			state_off=TRUE;
		}
		
		else
		{
			state_off=FALSE;
		}
		
		
		if((state_on==TRUE)&&(state_off==TRUE))
		{
			return VALVE_NO_POWER;//����δ�ӵ�
		}
		
		else if((state_on==FALSE)&&(state_off==FALSE))
		{
			return VALVE_UNKNOW;//����״̬δ֪
		}
		
		else if((state_on==TRUE)&&(state_off==FALSE))
		{
			return VALVE_ON;//����Ϊ��״̬
		}
		
		else if((state_on==FALSE)&&(state_off==TRUE))
		{
			return VALVE_OFF;//����Ϊ�ر�״̬
		}
		
		else
		{
			return VALVE_UNKNOW;//����״̬δ֪
		}
		
	}
	else
	{
		return VALVE_UNDEFINE;//����ķ����ڲ���ŷǷ�
	}

}


/******************************************************************************************
**���ƣ�EPDU�����м������ɺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_collectANDgroup_EPDU_count_generate(uint16 count,uint16 mode)
{
	
	uint16 n;
	n=count;
	n++;
	
	if(mode==COUNT_8BIT)
	{
		if(n>=0x0100)
		{
			n=0x0000;
		}
		
		else
		{
			asm("nop;");
		}

	}
	
	else if(mode==COUNT_14BIT)
	{
		if(n>=0x4000)
		{
			n=0x0000;
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

	return n;

}


/******************************************************************************************
**���ƣ�EPDU�����м������ɺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint8 TGTHT510_collectANDgroup_sum_generate(uint16 *p,uint16 number)
{
	uint8 sum;
	uint16 i;
	
	sum=0x00;
	
	for(i=0;i<=number-1;i++)
	{
		sum=sum+(uint8)p[i];
		sum=sum+(uint8)(p[i]>>8);
	}
		
	return sum;

}






/******************************************************************************************
**���ƣ�����ң��������֡
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_collectANDgroup_CG_group(void)
{
	uint16 i;
	uint8 sum;
	
	uint32 supply_stage_time_val;
	
	TGTHT510_supply_time_stage_get(&supply_stage_time_val);
	
	TGTHT510_collectANDgroup_CG_data_generate();
	
	TGTHT510_1553B_data_CG[0]=0x0b00;//���汾��000�������ͣ�0��������ͷ��־��1��APID��0110_000_0000
	
	CG_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(CG_EPDU_count,COUNT_14BIT);//����EPDUԴ�����м���
	
	TGTHT510_1553B_data_CG[1]=(CG_EPDU_count&0x3fff)|0xc000;//�����־��11�������м���
	
	TGTHT510_1553B_data_CG[2]=0x0111;//Դ������
	
	if(get_CPU()==CPU_B)//B��
	{
		TGTHT510_1553B_data_CG[3]=0x0200;//�������ͣ�����������
	}
	
	else//A��
	{
		TGTHT510_1553B_data_CG[3]=0x0100;//�������ͣ�����������
	}
	
	for(i=0;i<=3;i++)
	{
		TGTHT510_1553B_data_CG[i+4]=CG_yk_switch_state_data[i];//����ң�ط��ſ���״̬������λ����״̬
	}
	
	for(i=0;i<=6;i++)
	{
		TGTHT510_1553B_data_CG[i+8]=CG_heater_state_data[i]; //���������״̬
		
	}
	
	TGTHT510_1553B_data_CG[14]=TGTHT510_1553B_data_CG[14]&0x1f00;
	CG_valve_state_data[0]=CG_valve_state_data[0]&0xe0ff;
	TGTHT510_1553B_data_CG[14]=TGTHT510_1553B_data_CG[14]|CG_valve_state_data[0];//ƴ֡
	
	for(i=1;i<=22;i++)
	{
		TGTHT510_1553B_data_CG[i+14]=CG_valve_state_data[i];//���淧�ſ���״̬
	}
	
	TGTHT510_1553B_data_CG[36]=TGTHT510_1553B_data_CG[36]|0x00ff;
	
	//ע�������ȼ���ӽӿڣ������ӽӿ�
	TGTHT510_1553B_data_CG[37]=(TGTHT510_supply_decode_par.interface_F<<8)|(TGTHT510_supply_decode_par.interface_O>>8);
	
	//ע�������ȼ����ѹ�����ţ�������ѹ������
	TGTHT510_1553B_data_CG[38]=(TGTHT510_supply_decode_par.compressor_F<<8)|(TGTHT510_supply_decode_par.compressor_O>>8);

	//ע�������ȼ����ѹ�������ڷ��ţ���������ѹ�������ڷ���
	TGTHT510_1553B_data_CG[39]=(TGTHT510_supply_decode_par.valve_out_compressor_F<<8)|(TGTHT510_supply_decode_par.valve_out_compressor_O>>8);
	
	//ע����������ӵ�ȼ������������ӵ����������
	TGTHT510_1553B_data_CG[40]=(TGTHT510_supply_decode_par.number_tank_F<<8)|(TGTHT510_supply_decode_par.number_tank_F&0x00ff);
	
	//ע���������һ�����ӵ�ȼ����ţ���һ�����ӵ��������
	TGTHT510_1553B_data_CG[41]=(TGTHT510_supply_decode_par.first_tank_F<<8)|(TGTHT510_supply_decode_par.first_tank_O>>8);
	
	//ע��������ڶ������ӵ�ȼ����ţ��ڶ������ӵ��������
	TGTHT510_1553B_data_CG[42]=(TGTHT510_supply_decode_par.second_tank_F<<8)|(TGTHT510_supply_decode_par.second_tank_O>>8);
	
	//ע����������������ӵ�ȼ����ţ����������ӵ��������
	TGTHT510_1553B_data_CG[43]=(TGTHT510_supply_decode_par.third_tank_F<<8)|(TGTHT510_supply_decode_par.third_tank_O>>8);
	
	//ע�������ȼ����F1������ƿ������������O1������ƿ����
	TGTHT510_1553B_data_CG[44]=(TGTHT510_supply_decode_par.number_gas_tank_F1<<8)|(TGTHT510_supply_decode_par.number_gas_tank_O1&0x00ff);
	
	//ע�������ȼ����F1�ĵ�һ��������ƿ�ţ�������O1�ĵ�һ��������ƿ��
	TGTHT510_1553B_data_CG[45]=(TGTHT510_supply_decode_par.first_gas_tank_F1<<8)|(TGTHT510_supply_decode_par.first_gas_tank_O1>>8);
	
	//ע�������ȼ����F1�ĵڶ���������ƿ�ţ�������O1�ĵڶ���������ƿ��
	TGTHT510_1553B_data_CG[46]=(TGTHT510_supply_decode_par.second_gas_tank_F1<<8)|(TGTHT510_supply_decode_par.second_gas_tank_O1>>8);
	
	//ע�������ȼ����F2������ƿ������������O2������ƿ����
	TGTHT510_1553B_data_CG[47]=(TGTHT510_supply_decode_par.number_gas_tank_F2<<8)|(TGTHT510_supply_decode_par.number_gas_tank_O2&0x00ff);
	
	//ע�������ȼ����F2�ĵ�һ��������ƿ�ţ�������O2�ĵ�һ��������ƿ��
	TGTHT510_1553B_data_CG[48]=(TGTHT510_supply_decode_par.first_gas_tank_F2<<8)|(TGTHT510_supply_decode_par.first_gas_tank_O2>>8);
	
	//ע�������ȼ����F2�ĵڶ���������ƿ�ţ�������O2�ĵڶ���������ƿ��
	TGTHT510_1553B_data_CG[49]=(TGTHT510_supply_decode_par.second_gas_tank_F2<<8)|(TGTHT510_supply_decode_par.second_gas_tank_O2>>8);
	
	//ע�������ȼ����F3������ƿ������������O3������ƿ����
	TGTHT510_1553B_data_CG[50]=(TGTHT510_supply_decode_par.number_gas_tank_F3<<8)|(TGTHT510_supply_decode_par.number_gas_tank_O3&0x00ff);
	
	//ע�������ȼ����F3�ĵ�һ��������ƿ�ţ�������O3�ĵ�һ��������ƿ��
	TGTHT510_1553B_data_CG[51]=(TGTHT510_supply_decode_par.first_gas_tank_F3<<8)|(TGTHT510_supply_decode_par.first_gas_tank_O3>>8);
	
	//ע�������ȼ����F3�ĵڶ���������ƿ�ţ�������O3�ĵڶ���������ƿ��
	TGTHT510_1553B_data_CG[52]=(TGTHT510_supply_decode_par.second_gas_tank_F3<<8)|(TGTHT510_supply_decode_par.second_gas_tank_O3>>8);
	
	//ע�������Һ��ģ��ú�
	TGTHT510_1553B_data_CG[53]=TGTHT510_supply_decode_par.cooler;
	
	//ע�������ȼ����F1���ӵ�λʣ����
	TGTHT510_1553B_data_CG[54]=TGTHT510_supply_input_par.volum_F1;
	
	//ע�������ȼ����F2���ӵ�λʣ����
	TGTHT510_1553B_data_CG[55]=TGTHT510_supply_input_par.volum_F2;
	
	//ע�������ȼ����F3���ӵ�λʣ����
	TGTHT510_1553B_data_CG[56]=TGTHT510_supply_input_par.volum_F3;
	
	//ע�������������O1���ӵ�λʣ����
	TGTHT510_1553B_data_CG[57]=TGTHT510_supply_input_par.volum_O1;
	
	//ע�������������O2���ӵ�λʣ����
	TGTHT510_1553B_data_CG[58]=TGTHT510_supply_input_par.volum_O2;
	
	//ע�������������O3���ӵ�λʣ����
	TGTHT510_1553B_data_CG[59]=TGTHT510_supply_input_par.volum_O3;
	
	//����״̬����ǰ����ģʽ
	TGTHT510_1553B_data_CG[60]=TGTHT510_supply_ctrl.mode;
	
	//����״̬����ǰ��������״̬�����У���ͣ����ֹ�����У�
	TGTHT510_1553B_data_CG[61]=TGTHT510_supply_ctrl.state;
	
	//����״̬����ǰ���ӽ׶�
	TGTHT510_1553B_data_CG[62]=TGTHT510_supply_ctrl.stage;
	
	//����״̬����ǰ���Ӵ������
	TGTHT510_1553B_data_CG[63]=TGTHT510_supply_ctrl.step;
	
	//����״̬����ǰ���Ӵ���ָ���
	TGTHT510_1553B_data_CG[64]=TGTHT510_supply_ctrl.command;
	
	//����״̬����ǰ���ӹ��ϴ���
	TGTHT510_1553B_data_CG[65]=TGTHT510_supply_ctrl.errno;
	
	//����״̬����ǰ��������ʱ�䣨���֣�
	TGTHT510_1553B_data_CG[66]=(uint16)(supply_stage_time_val>>16);
	
	//����״̬����ǰ��������ʱ�䣨���֣�
	TGTHT510_1553B_data_CG[67]=(uint16)(supply_stage_time_val>>0);
	
	//����ָ���ָ������
	TGTHT510_1553B_data_CG[68]=CG_bus_command[0];
	
	//����ָ���ָ��У��
	TGTHT510_1553B_data_CG[69]=CG_bus_command[1];
	
	//���䵽λ�ź�ʹ�ܽ�ֹ��־
	TGTHT510_1553B_data_CG[70]=CG_place_signal_enable_disable;
	
	//�ƽ�������cpu״̬
	TGTHT510_1553B_data_CG[71]=CG_TGTHT510_cpu_state;
	
	//�ƽ��ʼ�
	for(i=0;i<=6;i++)
	{
		TGTHT510_1553B_data_CG[i+72]=TGTHT510_fault_data_CG_push[i];
	}
	
	//1553B����ͨ����ʶ
	TGTHT510_1553B_data_CG[79]=TGTHT510_which_bus.last_use_BU65170;
	
	//�ȿع���
	TGTHT510_1553B_data_CG[80]=CG_tempercontrol_power; //�ȿع���
	
	//ע��ָ�����״̬
	for(i=0;i<=1;i++)
	{
		TGTHT510_1553B_data_CG[i+81]=CG_inputcommand_receive_state_data[i];//ע��ָ�����״̬
	}
	
	//�豸����ָ��
	TGTHT510_1553B_data_CG[83]=CG_equiment_command[0];
	
	TGTHT510_1553B_data_CG[84]=CG_equiment_command[1];
	
	TGTHT510_1553B_data_CG[85]=CG_equiment_command[2];
	
	//���ӹʼ�״̬
	for(i=0;i<=29;i++)
	{
		TGTHT510_1553B_data_CG[i+86]=TGTHT510_fault_data_CG_supply[i];
	}
	
	//�豸�����ݽ���״̬
	for(i=0;i<=5;i++)
	{
		TGTHT510_1553B_data_CG[i+116]=CG_equiment_receive_state_data[i]; 
	}
	
	//���ջ����Ľ�������
	for(i=0;i<=15;i++)
	{
		TGTHT510_1553B_data_CG[i+122]=CG_HYCT_receive_state_data[i];
	}
	
	//TGTHT510_1553B_data_CG[137]=mode_test;//����ʹ��
	
	//֡����
	CG_count_number++;
	TGTHT510_1553B_data_CG[138]=CG_count_number;
	
	//�ֽ��ۼӺ�
	sum=TGTHT510_collectANDgroup_sum_generate(TGTHT510_1553B_data_CG,139);
	
	TGTHT510_1553B_data_CG[139]=(((uint16)sum)<<8)|0x00aa;
}


/******************************************************************************************
**���ƣ�����ң��������ȡ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_collectANDgroup_CG_data_generate(void)
{
	//TGTHT510_collectANDgroup_CG_supply_group();
	
	/*
//---------------------------------����----------------------------------------------------	
	uint16 i;
	for(i=0;i<=29;i++)
	{
		if(i<=4)
		{
			CG_supply_fault_state_data[i]=TGTHT510_1553B_data_TGTHT100[i];
		}
		
		else if((i>=5)&&(i<=9))
		{
			CG_supply_fault_state_data[i]=TGTHT510_1553B_data_TGTHT100_Temper_A[i-5];
		}
		
		else if((i>=10)&&(i<=14))
		{
			CG_supply_fault_state_data[i]=TGTHT510_1553B_data_TGTHT100_Temper_B[i-10];
		}
		
		else if((i>=15)&&(i<=19))
		{
			CG_supply_fault_state_data[i]=TGTHT510_1553B_data_TGTHT530[i-15];
		}
		
		else if((i>=20)&&(i<=24))
		{
			CG_supply_fault_state_data[i]=TGTHT510_1553B_data_TGTHT520a[i-20];
		}
		
		else if((i>=25)&&(i<=29))
		{
			CG_supply_fault_state_data[i]=TGTHT510_1553B_data_TGTHT520b[i-25];
		}
		
		else
		{
			asm("nop;");
		}
		
		
	}

//--------------------------------------------����---------------------------------
	
	
	//����ң�������ȡ
	
	*/
	
}





/******************************************************************************************
**���ƣ�����ң��������ȡ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_collectANDgroup_GC_data_generate(void)
{
	
	uint16 i;
	
	GC_pressure_gas_bottle[0]=TGTHT510_1553B_data_TGTHT100[0];//��1��ƿ����ѹ��
	GC_pressure_gas_bottle[1]=TGTHT510_1553B_data_TGTHT100[2];//��2��ƿ����ѹ��
	GC_pressure_gas_bottle[2]=TGTHT510_1553B_data_TGTHT100[4];//��3��ƿ����ѹ��
	GC_pressure_gas_bottle[3]=TGTHT510_1553B_data_TGTHT100[1];//ȼ1��ƿ����ѹ��
	GC_pressure_gas_bottle[4]=TGTHT510_1553B_data_TGTHT100[3];//ȼ2��ƿ����ѹ��
	GC_pressure_gas_bottle[5]=TGTHT510_1553B_data_TGTHT100[5];//ȼ3��ƿ����ѹ��
	
	//��1������ǻѹ������2������ǻѹ��
	GC_pressure_liquid_bottle[0]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[12],TGTHT510_1553B_data_TGTHT100[14]);
	
	//��3������ǻѹ����ȼ1������ǻѹ��
	GC_pressure_liquid_bottle[1]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[16],TGTHT510_1553B_data_TGTHT100[13]);
	
	//ȼ2������ǻѹ����ȼ3������ǻѹ��
	GC_pressure_liquid_bottle[2]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[15],TGTHT510_1553B_data_TGTHT100[17]);

	//��1����Һǻѹ������2����Һǻѹ��
	GC_pressure_liquid_bottle[3]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[18],TGTHT510_1553B_data_TGTHT100[20]);
	
	//��3����Һǻѹ����ȼ1����Һǻѹ��
	GC_pressure_liquid_bottle[4]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[22],TGTHT510_1553B_data_TGTHT100[19]);
	
	//ȼ2����Һǻѹ����ȼ3����Һǻѹ��
	GC_pressure_liquid_bottle[5]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[21],TGTHT510_1553B_data_TGTHT100[23]);
	
	//���A1��A3����·ѹ�������A2��A4����·ѹ��
	GC_pressure_pipe[0]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[24],TGTHT510_1553B_data_TGTHT100[26]);
	
	//���A1��A3ȼ��·ѹ�������A2��A4ȼ��·ѹ��
	GC_pressure_pipe[1]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[25],TGTHT510_1553B_data_TGTHT100[27]);
	
	//�˿�B����I���ι�ѹ�����˿�B��ȼI���ι�ѹ��
	GC_pressure_pipe[2]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[28],TGTHT510_1553B_data_TGTHT100[29]);
	
	//�˿�B����II���ι�ѹ�����˿�B��ȼII���ι�ѹ��
	GC_pressure_pipe[3]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[30],TGTHT510_1553B_data_TGTHT100[31]);
	
	GC_remainder_liquid[0]=TGTHT510_1553B_data_TGTHT100[61];//��1����ʣ������ȡλ���ź�1
	GC_remainder_liquid[1]=TGTHT510_1553B_data_TGTHT100[64];//��2����ʣ������ȡλ���ź�1
	GC_remainder_liquid[2]=TGTHT510_1553B_data_TGTHT100[67];//��3����ʣ������ȡλ���ź�1
	GC_remainder_liquid[3]=TGTHT510_1553B_data_TGTHT100[70];//ȼ1����ʣ������ȡλ���ź�1
	GC_remainder_liquid[4]=TGTHT510_1553B_data_TGTHT100[73];//ȼ2����ʣ������ȡλ���ź�1
	GC_remainder_liquid[5]=TGTHT510_1553B_data_TGTHT100[76];//ȼ3����ʣ������ȡλ���ź�1
	
	
	GC_pressure_compressor_A=(uint8)(TGTHT510_1553B_data_TGTHT100[42]>>4);//ѹ����A����ѹ��
	GC_pressure_compressor_B=(uint8)(TGTHT510_1553B_data_TGTHT100[43]>>4);//ѹ����B����ѹ��
	GC_pressure_compressor_C=(uint8)(TGTHT510_1553B_data_TGTHT100[60]>>4);//ѹ����C����ѹ��
	
	GC_pressure_engine_C_O=(uint8)(TGTHT510_1553B_data_TGTHT100[32]>>4);//�˿�C�������ι�ѹ��
	GC_pressure_engine_C_F=(uint8)(TGTHT510_1553B_data_TGTHT100[32]>>4);//�˿�C�������ι�ѹ��
	
}


/******************************************************************************************
**���ƣ��Ǳ�ң��������ȡ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_collectANDgroup_YB_data_generate(void)
{
	YB_pressure_gas_bottle[0]=TGTHT510_1553B_data_TGTHT100[0];//��1��ƿ����ѹ��
	YB_pressure_gas_bottle[1]=TGTHT510_1553B_data_TGTHT100[2];//��2��ƿ����ѹ��
	YB_pressure_gas_bottle[2]=TGTHT510_1553B_data_TGTHT100[4];//��3��ƿ����ѹ��
	YB_pressure_gas_bottle[3]=TGTHT510_1553B_data_TGTHT100[1];//ȼ1��ƿ����ѹ��
	YB_pressure_gas_bottle[4]=TGTHT510_1553B_data_TGTHT100[3];//ȼ2��ƿ����ѹ��
	YB_pressure_gas_bottle[5]=TGTHT510_1553B_data_TGTHT100[5];//ȼ3��ƿ����ѹ��
	
	YB_remainder_liquid[0]=TGTHT510_1553B_data_TGTHT100[61];//��1����ʣ������ȡλ���ź�1
	YB_remainder_liquid[1]=TGTHT510_1553B_data_TGTHT100[64];//��2����ʣ������ȡλ���ź�1
	YB_remainder_liquid[2]=TGTHT510_1553B_data_TGTHT100[67];//��3����ʣ������ȡλ���ź�1
	YB_remainder_liquid[3]=TGTHT510_1553B_data_TGTHT100[70];//ȼ1����ʣ������ȡλ���ź�1
	YB_remainder_liquid[4]=TGTHT510_1553B_data_TGTHT100[73];//ȼ2����ʣ������ȡλ���ź�1
	YB_remainder_liquid[5]=TGTHT510_1553B_data_TGTHT100[76];//ȼ3����ʣ������ȡλ���ź�1
	
}







/******************************************************************************************
**���ƣ�����ң��������֡
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_collectANDgroup_GC_group(void)
{
	uint16 i;
	uint8 sum;
	
	TGTHT510_collectANDgroup_GC_data_generate();//����ң��������ȡ
	
	TGTHT510_1553B_data_GC[0]=0x0b01;//���汾��000�������ͣ�0��������ͷ��־��1��APID��0110_000_0001
	
	GC_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(GC_EPDU_count,COUNT_14BIT);
	TGTHT510_1553B_data_GC[1]=(GC_EPDU_count&0x3fff)|0xc000;//�����־��11�������м���
	
	//TGTHT510_1553B_data_GC[1]=0xc000;
	
	TGTHT510_1553B_data_GC[2]=0x39;//Դ������
	
	TGTHT510_1553B_data_GC[3]=0x0100;//�������ͣ�����������
	
	for(i=0;i<=5;i++)
	{
		TGTHT510_1553B_data_GC[i+4]=GC_pressure_gas_bottle[i];//��ƿ����ѹ��	
	}
	
	for(i=0;i<=5;i++)
	{
		TGTHT510_1553B_data_GC[i+10]=GC_pressure_liquid_bottle[i];//������ǻ��Һǻ����ѹ��	
	}
	
	for(i=0;i<=3;i++)
	{
		TGTHT510_1553B_data_GC[i+16]=GC_pressure_pipe[i];//��·ѹ��	
	}
	
	for(i=0;i<=5;i++)
	{
		TGTHT510_1553B_data_GC[i+20]=GC_remainder_liquid[i];//����ʣ����	
	}
	
	TGTHT510_1553B_data_GC[26]=(((uint16)GC_pressure_compressor_A)<<8)|((uint16)GC_pressure_compressor_B);//ѹ����A����ѹ����ѹ����B����ѹ��
	
	TGTHT510_1553B_data_GC[27]=(((uint16)GC_pressure_compressor_C)<<8)|((uint16)GC_pressure_engine_C_O);//ѹ����C����ѹ�����˿�C���������ι�ѹ��
	
	TGTHT510_1553B_data_GC[28]=(((uint16)GC_pressure_engine_C_F)<<8)|((uint16)GC_supply_flag);//�˿�C����ȼ���ι�ѹ��,�������б�־
	
	TGTHT510_1553B_data_GC[29]=GC_TJ_flag;//�ƽ�����״̬��־
	
	TGTHT510_1553B_data_GC[30]=GC_supply_name_state_data;	//���ӽ׶���
	
	sum=TGTHT510_collectANDgroup_sum_generate(TGTHT510_1553B_data_GC,31);
	TGTHT510_1553B_data_GC[31]=(((uint16)sum)<<8)|0x00aa;//�ֽ��ۼӺ�

}

/******************************************************************************************
**���ƣ��ͻ���ң��������֡
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_collectANDgroup_HYCT_group(void)
{
	uint16 i;
	uint8 sum;
	
	HYCT_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(HYCT_EPDU_count,COUNT_14BIT);
	
	//����ת��ǰ��ڲ�������
	if(HYCT_EPDU_count%2==0)
	{
		TGTHT510_1553B_data_HYCT[0]=(0x0800|T_APID_HYCT_FORE);
		TGTHT510_1553B_data_HYCT[1]=(HYCT_EPDU_count&0x3fff)|0xc000;//�����־��11�������м���
		TGTHT510_1553B_data_HYCT[2]=0x0043;
		TGTHT510_1553B_data_HYCT[3]=T_SUBSERVICE_HYCT_FORE;
	}
	
	//����ת������ڲ�������
	else
	{
		TGTHT510_1553B_data_HYCT[0]=(0x0800|T_APID_HYCT_BACK);
		TGTHT510_1553B_data_HYCT[1]=(HYCT_EPDU_count&0x3fff)|0xc000;//�����־��11�������м���
		TGTHT510_1553B_data_HYCT[2]=0x0043;
		TGTHT510_1553B_data_HYCT[3]=T_SUBSERVICE_HYCT_BACK;
	}
	
	for(i=0;i<=31;i++)
	{
		TGTHT510_1553B_data_HYCT[i+4]=HYCT_data[i];
	}
	
	sum=TGTHT510_collectANDgroup_sum_generate(TGTHT510_1553B_data_HYCT,36);
	TGTHT510_1553B_data_HYCT[36]=(((uint16)sum)<<8)|0x00aa;//�ֽ��ۼӺ�;
	
}

/******************************************************************************************
**���ƣ��Ǳ�ң��������֡
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_collectANDgroup_YB_group(void)
{
	uint16 i;
	uint8 sum;
	
	TGTHT510_collectANDgroup_YB_data_generate();//�Ǳ�ң��������ȡ
	
	TGTHT510_1553B_data_YB[0]=0x0b02;//���汾��000�������ͣ�0��������ͷ��־��1��APID��0110_000_0010
	
	YB_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(YB_EPDU_count,COUNT_14BIT);
	TGTHT510_1553B_data_YB[1]=(YB_EPDU_count&0x3fff)|0xc000;//�����־��11�������м���
	
	TGTHT510_1553B_data_YB[2]=0x23;//Դ������
	
	TGTHT510_1553B_data_YB[3]=0x0100;//�������ͣ�����������
	
	TGTHT510_1553B_data_YB[4]=YB_TJ_flag; //�ƽ�����״̬
	
	TGTHT510_1553B_data_YB[5]=TGTHT510_supply_ctrl.stage; //���ӽ׶α�־
	
	TGTHT510_1553B_data_YB[6]=TGTHT510_supply_ctrl.state; //��������״̬��־
	
	TGTHT510_1553B_data_YB[7]=YB_fault_state; //���ϴ���״̬
	
	for(i=0;i<=5;i++)
	{
		TGTHT510_1553B_data_YB[i+8]=YB_pressure_gas_bottle[i];//��ƿ����ѹ��
	}
	
	for(i=0;i<=5;i++)
	{
		TGTHT510_1553B_data_YB[i+14]=YB_remainder_liquid[i];//����ʣ����
	}
	
	sum=TGTHT510_collectANDgroup_sum_generate(TGTHT510_1553B_data_YB,20);
	TGTHT510_1553B_data_YB[20]=(((uint16)sum)<<8)|0x00aa;//�ֽ��ۼӺ�

}

/******************************************************************************************
**���ƣ�ת��GNC�ʼ�������֡
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_collectANDgroup_GNC_group(void)
{
	uint8 sum;
	GNC_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(GNC_EPDU_count,COUNT_14BIT);
	
	TGTHT510_1553B_data_GNC[0]=(0x0800|T_APID_GNC);
	TGTHT510_1553B_data_GNC[1]=(GNC_EPDU_count&0x3fff)|0xc000;//�����־��11�������м���
	TGTHT510_1553B_data_GNC[2]=0x0007;
	TGTHT510_1553B_data_GNC[3]=T_SUBSERVICE_GNC;
	
	TGTHT510_1553B_data_GNC[4]=(((TGTHT510_fault_data_CG_push[4]&0x00ff)<<8)|\
	((TGTHT510_fault_data_CG_push[5]&0xff00)>>8));
	
	TGTHT510_1553B_data_GNC[5]=(((TGTHT510_fault_data_CG_push[5]&0x00f0)<<8)|(0x0fff));
	
	sum=TGTHT510_collectANDgroup_sum_generate(TGTHT510_1553B_data_GNC,6);
	TGTHT510_1553B_data_GNC[6]=(((uint16)sum)<<8)|0x00aa;//�ֽ��ۼӺ�;
	
}

/******************************************************************************************
**���ƣ��ڴ��´�������֡
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_collectANDgroup_MEMORY_group(void)
{
	uint8 sum;
	uint16 i;
	MEMORY_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(MEMORY_EPDU_count,COUNT_14BIT);
	
	TGTHT510_1553B_data_MEMORY[0]=(0x0800|T_APID_MEMORY);
	TGTHT510_1553B_data_MEMORY[1]=(MEMORY_EPDU_count&0x3fff)|0xc000;//�����־��11�������м���
	TGTHT510_1553B_data_MEMORY[2]=0x01f7;
	TGTHT510_1553B_data_MEMORY[3]=T_SUBSERVICE_MEMORY;
	
	for(i=0;i<=249;i++)
	{
		if(i<=26)
		{
			TGTHT510_1553B_data_MEMORY[i+4]=0x1111;
		}
		
		else if((i>=27)&&(i<=58))
		{
			TGTHT510_1553B_data_MEMORY[i+4]=0x2222;
		}
		
		else if((i>=59)&&(i<=90))
		{
			TGTHT510_1553B_data_MEMORY[i+4]=0x3333;
		}
		
		else if((i>=91)&&(i<=122))
		{
			TGTHT510_1553B_data_MEMORY[i+4]=0x4444;
		}
		
		else if((i>=123)&&(i<=154))
		{
			TGTHT510_1553B_data_MEMORY[i+4]=0x5555;
		}
		
		else if((i>=155)&&(i<=186))
		{
			TGTHT510_1553B_data_MEMORY[i+4]=0x6666;
		}
		
		else if((i>=187)&&(i<=218))
		{
			TGTHT510_1553B_data_MEMORY[i+4]=0x7777;
		}
		
		else
		{
			TGTHT510_1553B_data_MEMORY[i+4]=0x8888;
		}
		
		//TGTHT510_1553B_data_MEMORY[i+4]=MEMORY_data[i];
		//TGTHT510_1553B_data_MEMORY[i+4]=0x5555;
	}
	
	sum=TGTHT510_collectANDgroup_sum_generate(TGTHT510_1553B_data_MEMORY,254);
	TGTHT510_1553B_data_MEMORY[254]=(((uint16)sum)<<8)|0x00aa;//�ֽ��ۼӺ�;
}





/******************************************************************************************
**���ƣ���������ָ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_collectANDgroup_ask_for_service_generate(uint16 mode)
{
	
	if(mode==ASK_FOR_SERVICE_EQUIMENT_COMMAND)//���������豸����ָ��
	{
		TGTHT510_1553B_data_ask_for_service=TGTHT510_1553B_data_ask_for_service|0x0300;
		
	}
	
	else if(mode==ASK_FOR_SERVICE_FAULT_CODE)//�������󣬹��ϴ���
	{
		TGTHT510_1553B_data_ask_for_service=TGTHT510_1553B_data_ask_for_service|0x0003;
		
	}
	
	else if(mode==ASK_FOR_SERVICE_MEMORY)//���������ڴ��´�
	{
		TGTHT510_1553B_data_ask_for_service=TGTHT510_1553B_data_ask_for_service|0x000c;
		
	}
	
	else//��������Ƿ�
	{
		TGTHT510_1553B_data_ask_for_service=0x0000;
	}
	
	
}


/******************************************************************************************
**���ƣ��豸����ָ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_collectANDgroup_equiment_command_generate(uint8 command)
{
	equiment_command_EPDU_command_data_TypeDef c;//�̿�ָ������
	equiment_command_EPDU_APID_VCID_TypeDef command_ID;//VCID��APID	
	uint16 i;
	uint16 CRC;
	
	for(i=0;i<=10;i++)
	{
		TGTHT510_1553B_data_equiment_command[i]=0x0000;//��ʼ������
	}
	
	c=TGTHT510_collectANDgroup_equiment_command_EPDU_command_generate(command);//�̿�ָ������
	
	command_ID=TGTHT510_collectANDgroup_equiment_command_APID_VCID_generate(command);//VCID
	
	TGTHT510_1553B_data_equiment_command[0]=0x0001;//�汾��00��ͨ����־��0�����������־��0�����У�00����������ʶ��0000000001
	
	TGTHT510_1553B_data_equiment_command[1]=(((uint16)command_ID.VCID)<<10)|0x0015;//VCID��֡���̶�21
	
	equiment_command_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(equiment_command_EPDU_count,COUNT_8BIT);//֡���м���
	
	TGTHT510_1553B_data_equiment_command[2]=(equiment_command_EPDU_count<<8)|((uint16)c.command_data[0]);//֡���кš�EPDU��ͷ
	
	TGTHT510_1553B_data_equiment_command[3]=(((uint16)c.command_data[1])<<8)|((uint16)c.command_data[2]);
	
	TGTHT510_1553B_data_equiment_command[4]=(((uint16)c.command_data[3])<<8)|((uint16)c.command_data[4]);
	
	TGTHT510_1553B_data_equiment_command[5]=(((uint16)c.command_data[5])<<8)|((uint16)c.command_data[6]);
	
	TGTHT510_1553B_data_equiment_command[6]=(((uint16)c.command_data[7])<<8)|((uint16)c.command_data[8]);
	
	TGTHT510_1553B_data_equiment_command[7]=(((uint16)c.command_data[9])<<8)|((uint16)c.command_data[10]);
	
	TGTHT510_1553B_data_equiment_command[8]=(((uint16)c.command_data[11])<<8)|((uint16)c.command_data[12]);
	
	TGTHT510_1553B_data_equiment_command[9]=(((uint16)c.command_data[13])<<8)|0x00aa;
	
	CRC=TGTHT510_collectANDgroup_CRC_generate(TGTHT510_1553B_data_equiment_command,10);//CRCУ����
	
	TGTHT510_1553B_data_equiment_command[10]=CRC;
	
	TGTHT510_1553b_transmitcommand_equiment(BU65170_Z);//�豸����ָ������д��1553B������
	
	TGTHT510_1553b_transmitcommand_equiment(BU65170_B);//�豸����ָ������д��1553B������
	
	TGTHT510_collectANDgroup_ask_for_service_generate(ASK_FOR_SERVICE_EQUIMENT_COMMAND);//��������
	
}

/******************************************************************************************
**���ƣ��豸����ָ��֮�̿�ָ��������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

equiment_command_EPDU_command_data_TypeDef TGTHT510_collectANDgroup_equiment_command_EPDU_command_generate(uint8 command)
{
	equiment_command_EPDU_command_data_TypeDef a;
	equiment_command_EPDU_APID_VCID_TypeDef command_ID;
	uint16 i,sum_ISO;
	
	for(i=0;i<=13;i++)
	{
		a.command_data[i]=0x00;//��ʼ������
	}
	
	command_ID=TGTHT510_collectANDgroup_equiment_command_APID_VCID_generate(command);//APID��VCID
	
	if(command_ID.APID==APID_ERROR)
	{
		return a;//APID���󣬷���ȫ��ĳ̿�ָ����
	}
	
	a.command_data[0]=0x18|((uint8)(command_ID.APID>>8));//�̿�ָ����汾��000�������ͣ�1��APID����λ
	
	a.command_data[1]=(uint8)command_ID.APID;//APID�Ͱ�λ
	
	a.command_data[2]=0x00;//�����־��00�������м���:000000
	
	a.command_data[3]=0x00;//�����м�����00000000
	
	a.command_data[4]=0x00;//�����ȣ����ֽ�
	
	a.command_data[5]=0x07;//�����ȣ����ֽ�
	
	a.command_data[6]=0x02;//��������
	
	a.command_data[7]=0x02;//����������
	
	a.command_data[8]=equiment_command_code1[command];//�豸����ָ������1
	
	a.command_data[9]=equiment_command_code[command];//�豸����ָ������2
	
	a.command_data[10]=equiment_command_code1[command];//�豸����ָ������1
	
	a.command_data[11]=equiment_command_code[command];//�豸����ָ������2
	
	sum_ISO=TGTHT510_collectANDgroup_equiment_command_ISO_generate(a.command_data,12);
	
	a.command_data[12]=(uint8)(sum_ISO>>8);
	
	a.command_data[13]=(uint8)sum_ISO;
	
	CG_equiment_command[0]=0x0001;//����ң�⣬�´���������ʶ
	
	CG_equiment_command[1]=command_ID.APID;//����ң�⣬�´�APID
	
	CG_equiment_command[2]=((uint16)(a.command_data[8])<<8)|((uint16)(a.command_data[9]));
	
	//CG_equiment_command[2]=0x0100|((uint16)a.command_data[9]);//����ң�⣬�´�ָ������
	
	return a;

}


/******************************************************************************************
**���ƣ��豸����ָ��֮�̿�ָ��APID,VCID���ɺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

equiment_command_EPDU_APID_VCID_TypeDef TGTHT510_collectANDgroup_equiment_command_APID_VCID_generate(uint8 command)
{
	equiment_command_EPDU_APID_VCID_TypeDef a;
	
	if(command<=0x35)//��·����������������ָ��
	{
		a.APID=APID_TGTHT520a_VALVE_EQUIMENT_COMMAND;
		a.VCID=VCID_TGTHT520_A_EQUIMENT_COMMAND;
		
	}
	
	else if((command>=0x36)&&(command<=0x6b))//��·����������������ָ��
	{
		a.APID=APID_TGTHT520b_VALVE_EQUIMENT_COMMAND;
		a.VCID=VCID_TGTHT520_B_EQUIMENT_COMMAND;
		
	}
	
	else if((command>=0x6c)&&(command<=0x71))//����������Ӷϵ�ָ��
	{
		a.APID=APID_TGTHT530_POWER_EQUIMENT_COMMAND;
		if((command==0x6c)||(command==0x6f))//���������A
		{
			a.VCID=VCID_TGTHT530_A_EQUIMENT_COMMAND;
		}
		
		else if((command==0x6d)||(command==0x70))//���������B
		{
			a.VCID=VCID_TGTHT530_B_EQUIMENT_COMMAND;
		}
		
		else if((command==0x6e)||(command==0x71))//���������C
		{
			a.VCID=VCID_TGTHT530_C_EQUIMENT_COMMAND;
		}
	}
	
	else if((command>=0x72)&&(command<=0x77))//ѹ�����Ӷϵ�ָ��
	{
		a.APID=APID_COMPRESS_POWER_EQUIMENT_COMMAND;
		if((command==0x72)||(command==0x75))//ѹ����A
		{
			a.VCID=VCID_TGTHT530_A_EQUIMENT_COMMAND;
		}
		
		else if((command==0x73)||(command==0x76))//ѹ����B
		{
			a.VCID=VCID_TGTHT530_B_EQUIMENT_COMMAND;
		}
		
		else if((command==0x74)||(command==0x77))//ѹ����C
		{
			a.VCID=VCID_TGTHT530_C_EQUIMENT_COMMAND;
		}
	}
	
	else if((command>=0x78)&&(command<=0x7d))//ѹ����������ͣ��ָ��
	{
		a.APID=APID_COMPRESS_START_STOP_EQUIMENT_COMMAND;
		if((command==0x78)||(command==0x7b))//ѹ����A
		{
			a.VCID=VCID_TGTHT530_A_EQUIMENT_COMMAND;
		}
		
		else if((command==0x79)||(command==0x7c))//ѹ����B
		{
			a.VCID=VCID_TGTHT530_B_EQUIMENT_COMMAND;
		}
		
		else if((command==0x7a)||(command==0x7d))//ѹ����C
		{
			a.VCID=VCID_TGTHT530_C_EQUIMENT_COMMAND;
		}
		
	}
	
	else if((command>=0x7e)&&(command<=0x7f))//���ӷ��żӶϵ�ָ��
	{
		a.APID=APID_VALVE_POWER_EQUIMENT_COMMAND;
		a.VCID=VCID_POWER_EQUIMENT_COMMAND;
		
	}
	
	else//ָ�����Ƿ�
	{
		a.APID=APID_ERROR;
		a.VCID=VCID_ERROR;
	}
	
	return a;
	
}

/******************************************************************************************
**���ƣ��豸����ָ��֮�̿�ָ��У����ISO���ɺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_collectANDgroup_equiment_command_ISO_generate(uint8 *p,uint16 size)
{
	uint16 ck1,ck2;
	uint16 c0,c1,i,temp;

	c0=0;
	c1=0;
	for(i=0;i<=size-1;i++)
	{	
		c0=c0+p[i];
		c1=c1+c0;
	}
	c0=c0%255;
	c1=c1%255;
	ck1=(-c0-c1)%255-1;
	ck2=c1;
	
	
	if(ck1==0)
    {
       ck1=255;
    }
        
    if(ck2==0)
    {
       ck2=255;
    }
	
	
	temp=(ck1<<8)|((uint16)ck2);
	return temp;

}

/******************************************************************************************
**���ƣ������ֽ�����CRCУ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
//CRC��ʾ�����У���룬inputdataΪ�����ֽ�����
uint16 TGTHT510_collectANDgroup_Byte_CRC(uint16 CRC,uint8 inputdata)
{
	uint16 in;
	uint16 POLY=0x1021;//�����G(X)=X16+X12+X5+1
	uint16 CRC_buf,m;
	uint16 i=0x0000;
	
	in=(uint16)inputdata;
	in=in<<8;
	CRC_buf=CRC^in;
	
	do
	{
		m=CRC_buf&0x8000;
		CRC_buf=CRC_buf<<1;
		if(m==0x8000)
		{
			CRC_buf=CRC_buf^POLY;
		}
		i++;
		
	}while(i<8);
		
	return CRC_buf;
	
}

/******************************************************************************************
**���ƣ���������CRCУ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
//pΪ�������ָ�룬sizeΪ����ĳ���
uint16 TGTHT510_collectANDgroup_CRC_generate(uint16 *p,uint16 size)
{
	uint16 i;
	uint16 CRC=0x0000;
	uint8 m;
	
	for(i=0;i<=size-1;i++)
	{
		m=(uint8)(p[i]>>8);//�ֵĸ��ֽ�
		CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,m);
		m=(uint8)p[i];//�ֵĵ��ֽ�
		CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,m);
		
	}
	
	return CRC;
	
}

/******************************************************************************************
**���ƣ�OCָ���뵽λ�źŶ�ȡ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_collectANDgroup_yk_state_collect_save(void)
{
	uint16 state[4];
	uint16 i;
	uint16 temp;
	
	for(i=0;i<=3;i++)
	{
		state[i]=Read_32_to_16(*(volatile uint32 *)(YK_ADDRESS_BASE+4*(28+i)));
		
	}
	
	//���
	
	*(volatile uint32 *)(YK_ADDRESS_BASE+4*(26))=Write_16_to_32(0xaaaa);
	
	CG_place_signal_enable_disable=Read_32_to_16(*(volatile uint32 *)(YK_ADDRESS_BASE+4*32));
	
	for(i=0;i<=3;i++)
	{
		CG_yk_switch_state_data[i]=0x0000; //����ң�ط��ſ���״̬������λ����״̬��ʼ��
	}
	
	for(i=0;i<=45;i++)
	{
		temp=(state[yk_state_from_FPGA_word[i]]&yk_state_from_FPGA_bit[i]);
		
		if(temp!=0x0000)
		{
			CG_yk_switch_state_data[yk_state_to_CG_word[i]]|=yk_state_to_CG_bit[i];
			
		}
		
		else
		{
			asm("nop;");
		}

	}
	
}


/******************************************************************************************
**���ƣ�ƴ֡����high��bit4~11λƴ�����ֽڣ���low��bit4~11λƴ�����ֽ�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_collectANDgroup_combine(uint16 high,uint16 low)
{
	uint16 a;
	uint16 b;
	uint16 result;
	
	a=(high>>4)&0x00ff;
	b=(low>>4)&0x00ff;
	
	result=(a<<8)|b;
	return result;

}


/******************************************************************************************
**���ƣ����䵽λʹ�����ֹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_tank_position_set(uint16 tank,uint16 flag)
{
	switch(tank)
	{
		case TANK_O1_POSITION:
		{
			if(flag==ENABLE)
			{
				*(volatile uint32 *)(YK_ADDRESS_BASE+27*4)=Write_16_to_32(0xaaab);
			}
			
			else if(flag==DISABLE)
			{
				*(volatile uint32 *)(YK_ADDRESS_BASE+27*4)=Write_16_to_32(0xaaa8);
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case TANK_O2_POSITION:
		{
			if(flag==ENABLE)
			{
				*(volatile uint32 *)(YK_ADDRESS_BASE+27*4)=Write_16_to_32(0xaaae);
			}
			
			else if(flag==DISABLE)
			{
				*(volatile uint32 *)(YK_ADDRESS_BASE+27*4)=Write_16_to_32(0xaaa2);
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case TANK_O3_POSITION:
		{
			if(flag==ENABLE)
			{
				*(volatile uint32 *)(YK_ADDRESS_BASE+27*4)=Write_16_to_32(0xaaba);
			}
			
			else if(flag==DISABLE)
			{
				*(volatile uint32 *)(YK_ADDRESS_BASE+27*4)=Write_16_to_32(0xaa8a);
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case TANK_F1_POSITION:
		{
			if(flag==ENABLE)
			{
				*(volatile uint32 *)(YK_ADDRESS_BASE+27*4)=Write_16_to_32(0xaaea);
			}
			
			else if(flag==DISABLE)
			{
				*(volatile uint32 *)(YK_ADDRESS_BASE+27*4)=Write_16_to_32(0xaa2a);
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case TANK_F2_POSITION:
		{
			if(flag==ENABLE)
			{
				*(volatile uint32 *)(YK_ADDRESS_BASE+27*4)=Write_16_to_32(0xabaa);
			}
			
			else if(flag==DISABLE)
			{
				*(volatile uint32 *)(YK_ADDRESS_BASE+27*4)=Write_16_to_32(0xa8aa);
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case TANK_F3_POSITION:
		{
			if(flag==ENABLE)
			{
				*(volatile uint32 *)(YK_ADDRESS_BASE+27*4)=Write_16_to_32(0xaeaa);
			}
			
			else if(flag==DISABLE)
			{
				*(volatile uint32 *)(YK_ADDRESS_BASE+27*4)=Write_16_to_32(0xa2aa);
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		default:
		{
			break;
		}
		
		
	}

}

/******************************************************************************************
**���ƣ�����ϵͳң�������֡
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_collectANDgroup_CG_supply_group(void)
{
	
	/*
	CG_supply_fault_state_data[0]=TGTHT510_supply_ctrl.errno;
	
	
	//���ӽ׶���
	CG_supply_name_state_data=TGTHT510_supply_ctrl.stage;
	
	//��������״̬
	CG_supply_flag=TGTHT510_supply_ctrl.state;
	
	//�������в���
	CG_supply_step=TGTHT510_supply_ctrl.step;
	
	//������������
	CG_supply_command=TGTHT510_supply_ctrl.command;
	
	//���ӹ��̹��ϴ���
	
	*/
}









