/**
  ******************************************************************************
  * @file    TGTHT510_tempercontrol.c
  * @author  ����
  * @version V1.00
  * @date    20150626
  * @brief   �ռ�վ���Ĳ��ƽ��������Զ�����ģ��C�ļ�
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"






/*ȫ�ֱ���---------------------------------------------------------------------*/		

Temperature_control_block_TypeDef Temperature_control_block[50];//��50·���»�·

Temperature_control_global_TypeDef Temperature_control_global;//�¶ȿ���ȫ�ֱ���

Temperature_control_valid_data_TypeDef Temperature_control_valid_data;//������Ч����

uint16 Temperature_control_reg[8];//���������ƼĴ���

//-------------------------------����---------------------------
//uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[65];
//uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[65];
//uint16 CG_tempercontrol_power;

extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[];				//ȫ�����飬�����ƽ�ң����·�и�֡A�¶����ݣ�65��
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[];				//ȫ�����飬�����ƽ�ң����·�и�֡B�¶����ݣ�65��

extern Time_flag_TypeDef Time_flag;//��ʱ�����ṹ��

extern uint16 CG_tempercontrol_power; //�ȿع���,����ң��

extern CPU_B_receive_data_TypeDef CPU_B_receive_data;


const uint16 Tempercontrol_Power[100]={ 23,11,23,11,23,11,23,11,4,4,	//sc1-10
										4,4,4,4,4,4,14,14,6,6,			//sc11-20
										14,14,6,6,17,17,6,6,3,3,		//sc21-30
										17,17,6,6,3,3,17,17,12,12,		//sc31-40
										17,17,12,12,17,17,12,12,17,17,	//sc41-50
										12,12,6,6,6,6,6,6,6,6,			//sc51-60
										14,14,5,5,14,14,5,5,4,4,		//sc61-70
										5,5,4,4,3,3,22,22,15,15,		//sc71-80
										22,22,15,15,14,14,14,14,3,3,	//sc81-90
										3,3,3,3,3,3,4,4,4,4				//sc91-100
										};//���Ȼ�·����

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
										
const uint16 Tempercontrol_word_bit[100]={	0x0001,0x0001,0x0002,0x0002,0x0004,0x0004,0x0008,0x0008,0x0010,0x0010,//sc1~10
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

const uint16 Tempercontrol_word_byte[100]={	0,4,0,4,0,4,0,4,0,4,//sc1~10
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


/*
MF51�¶�ֵ��Դ��Ķ�Ӧ��ѯ��
�����±��ȥ50��Ϊ�¶�ֵ�����±�Ϊ100����Ӧ��Դ�뼴Ϊ100-50=50���϶ȶ�Ӧ��Դ��ֵ
�¶ȷ�Χ-50���϶���+70���϶�

*/											

const uint16 Tempercontrol_MF51_code[121]={
	
	TABLE_MF51_NEG_50,TABLE_MF51_NEG_49,TABLE_MF51_NEG_48,TABLE_MF51_NEG_47,TABLE_MF51_NEG_46,
	TABLE_MF51_NEG_45,TABLE_MF51_NEG_44,TABLE_MF51_NEG_43,TABLE_MF51_NEG_42,TABLE_MF51_NEG_41,
	TABLE_MF51_NEG_40,TABLE_MF51_NEG_39,TABLE_MF51_NEG_38,TABLE_MF51_NEG_37,TABLE_MF51_NEG_36,
	TABLE_MF51_NEG_35,TABLE_MF51_NEG_34,TABLE_MF51_NEG_33,TABLE_MF51_NEG_32,TABLE_MF51_NEG_31,
	TABLE_MF51_NEG_30,TABLE_MF51_NEG_29,TABLE_MF51_NEG_28,TABLE_MF51_NEG_27,TABLE_MF51_NEG_26,
	TABLE_MF51_NEG_25,TABLE_MF51_NEG_24,TABLE_MF51_NEG_23,TABLE_MF51_NEG_22,TABLE_MF51_NEG_21,
	TABLE_MF51_NEG_20,TABLE_MF51_NEG_19,TABLE_MF51_NEG_18,TABLE_MF51_NEG_17,TABLE_MF51_NEG_16,
	TABLE_MF51_NEG_15,TABLE_MF51_NEG_14,TABLE_MF51_NEG_13,TABLE_MF51_NEG_12,TABLE_MF51_NEG_11,
	TABLE_MF51_NEG_10,TABLE_MF51_NEG_09,TABLE_MF51_NEG_08,TABLE_MF51_NEG_07,TABLE_MF51_NEG_06,
	TABLE_MF51_NEG_05,TABLE_MF51_NEG_04,TABLE_MF51_NEG_03,TABLE_MF51_NEG_02,TABLE_MF51_NEG_01,
	TABLE_MF51_MID_00,
	TABLE_MF51_POS_01,TABLE_MF51_POS_02,TABLE_MF51_POS_03,TABLE_MF51_POS_04,TABLE_MF51_POS_05,
	TABLE_MF51_POS_06,TABLE_MF51_POS_07,TABLE_MF51_POS_08,TABLE_MF51_POS_09,TABLE_MF51_POS_10,
	TABLE_MF51_POS_11,TABLE_MF51_POS_12,TABLE_MF51_POS_13,TABLE_MF51_POS_14,TABLE_MF51_POS_15,
	TABLE_MF51_POS_16,TABLE_MF51_POS_17,TABLE_MF51_POS_18,TABLE_MF51_POS_19,TABLE_MF51_POS_20,
	TABLE_MF51_POS_21,TABLE_MF51_POS_22,TABLE_MF51_POS_23,TABLE_MF51_POS_24,TABLE_MF51_POS_25,
	TABLE_MF51_POS_26,TABLE_MF51_POS_27,TABLE_MF51_POS_28,TABLE_MF51_POS_29,TABLE_MF51_POS_30,
	TABLE_MF51_POS_31,TABLE_MF51_POS_32,TABLE_MF51_POS_33,TABLE_MF51_POS_34,TABLE_MF51_POS_35,
	TABLE_MF51_POS_36,TABLE_MF51_POS_37,TABLE_MF51_POS_38,TABLE_MF51_POS_39,TABLE_MF51_POS_40,
	TABLE_MF51_POS_41,TABLE_MF51_POS_42,TABLE_MF51_POS_43,TABLE_MF51_POS_44,TABLE_MF51_POS_45,
	TABLE_MF51_POS_46,TABLE_MF51_POS_47,TABLE_MF51_POS_48,TABLE_MF51_POS_49,TABLE_MF51_POS_50,
	TABLE_MF51_POS_51,TABLE_MF51_POS_52,TABLE_MF51_POS_53,TABLE_MF51_POS_54,TABLE_MF51_POS_55,
	TABLE_MF51_POS_56,TABLE_MF51_POS_57,TABLE_MF51_POS_58,TABLE_MF51_POS_59,TABLE_MF51_POS_60,
	TABLE_MF51_POS_61,TABLE_MF51_POS_62,TABLE_MF51_POS_63,TABLE_MF51_POS_64,TABLE_MF51_POS_65,
	TABLE_MF51_POS_66,TABLE_MF51_POS_67,TABLE_MF51_POS_68,TABLE_MF51_POS_69,TABLE_MF51_POS_70
	};

																					
/*
MF61�¶�ֵ��Դ��Ķ�Ӧ��ѯ��
�����±��ȥ50��Ϊ�¶�ֵ�����±�Ϊ100����Ӧ��Դ�뼴Ϊ100-50=50���϶ȶ�Ӧ��Դ��ֵ
�¶ȷ�Χ-50���϶���+70���϶�

*/

const uint16 Tempercontrol_MF61_code[121]={	

	TABLE_MF61_NEG_50,TABLE_MF61_NEG_49,TABLE_MF61_NEG_48,TABLE_MF61_NEG_47,TABLE_MF61_NEG_46,
	TABLE_MF61_NEG_45,TABLE_MF61_NEG_44,TABLE_MF61_NEG_43,TABLE_MF61_NEG_42,TABLE_MF61_NEG_41,
	TABLE_MF61_NEG_40,TABLE_MF61_NEG_39,TABLE_MF61_NEG_38,TABLE_MF61_NEG_37,TABLE_MF61_NEG_36,
	TABLE_MF61_NEG_35,TABLE_MF61_NEG_34,TABLE_MF61_NEG_33,TABLE_MF61_NEG_32,TABLE_MF61_NEG_31,
	TABLE_MF61_NEG_30,TABLE_MF61_NEG_29,TABLE_MF61_NEG_28,TABLE_MF61_NEG_27,TABLE_MF61_NEG_26,
	TABLE_MF61_NEG_25,TABLE_MF61_NEG_24,TABLE_MF61_NEG_23,TABLE_MF61_NEG_22,TABLE_MF61_NEG_21,
	TABLE_MF61_NEG_20,TABLE_MF61_NEG_19,TABLE_MF61_NEG_18,TABLE_MF61_NEG_17,TABLE_MF61_NEG_16,
	TABLE_MF61_NEG_15,TABLE_MF61_NEG_14,TABLE_MF61_NEG_13,TABLE_MF61_NEG_12,TABLE_MF61_NEG_11,
	TABLE_MF61_NEG_10,TABLE_MF61_NEG_09,TABLE_MF61_NEG_08,TABLE_MF61_NEG_07,TABLE_MF61_NEG_06,
	TABLE_MF61_NEG_05,TABLE_MF61_NEG_04,TABLE_MF61_NEG_03,TABLE_MF61_NEG_02,TABLE_MF61_NEG_01,
	TABLE_MF61_MID_00,
	TABLE_MF61_POS_01,TABLE_MF61_POS_02,TABLE_MF61_POS_03,TABLE_MF61_POS_04,TABLE_MF61_POS_05,
	TABLE_MF61_POS_06,TABLE_MF61_POS_07,TABLE_MF61_POS_08,TABLE_MF61_POS_09,TABLE_MF61_POS_10,
	TABLE_MF61_POS_11,TABLE_MF61_POS_12,TABLE_MF61_POS_13,TABLE_MF61_POS_14,TABLE_MF61_POS_15,
	TABLE_MF61_POS_16,TABLE_MF61_POS_17,TABLE_MF61_POS_18,TABLE_MF61_POS_19,TABLE_MF61_POS_20,
	TABLE_MF61_POS_21,TABLE_MF61_POS_22,TABLE_MF61_POS_23,TABLE_MF61_POS_24,TABLE_MF61_POS_25,
	TABLE_MF61_POS_26,TABLE_MF61_POS_27,TABLE_MF61_POS_28,TABLE_MF61_POS_29,TABLE_MF61_POS_30,
	TABLE_MF61_POS_31,TABLE_MF61_POS_32,TABLE_MF61_POS_33,TABLE_MF61_POS_34,TABLE_MF61_POS_35,
	TABLE_MF61_POS_36,TABLE_MF61_POS_37,TABLE_MF61_POS_38,TABLE_MF61_POS_39,TABLE_MF61_POS_40,
	TABLE_MF61_POS_41,TABLE_MF61_POS_42,TABLE_MF61_POS_43,TABLE_MF61_POS_44,TABLE_MF61_POS_45,
	TABLE_MF61_POS_46,TABLE_MF61_POS_47,TABLE_MF61_POS_48,TABLE_MF61_POS_49,TABLE_MF61_POS_50,
	TABLE_MF61_POS_51,TABLE_MF61_POS_52,TABLE_MF61_POS_53,TABLE_MF61_POS_54,TABLE_MF61_POS_55,
	TABLE_MF61_POS_56,TABLE_MF61_POS_57,TABLE_MF61_POS_58,TABLE_MF61_POS_59,TABLE_MF61_POS_60,
	TABLE_MF61_POS_61,TABLE_MF61_POS_62,TABLE_MF61_POS_63,TABLE_MF61_POS_64,TABLE_MF61_POS_65,
	TABLE_MF61_POS_66,TABLE_MF61_POS_67,TABLE_MF61_POS_68,TABLE_MF61_POS_69,TABLE_MF61_POS_70
											
	};


/*
�������¶�ֵ��Դ��Ķ�Ӧ��ѯ��
�����±��ȥ50��Ϊ�¶�ֵ�����±�Ϊ100����Ӧ��Դ�뼴Ϊ100-50=50���϶ȶ�Ӧ��Դ��ֵ
�¶ȷ�Χ-50���϶���+70���϶�

*/											


const uint16 Tempercontrol_Pt_code[121]={	
	
	TABLE_PT_NEG_50,TABLE_PT_NEG_49,TABLE_PT_NEG_48,TABLE_PT_NEG_47,TABLE_PT_NEG_46,
	TABLE_PT_NEG_45,TABLE_PT_NEG_44,TABLE_PT_NEG_43,TABLE_PT_NEG_42,TABLE_PT_NEG_41,
	TABLE_PT_NEG_40,TABLE_PT_NEG_39,TABLE_PT_NEG_38,TABLE_PT_NEG_37,TABLE_PT_NEG_36,
	TABLE_PT_NEG_35,TABLE_PT_NEG_34,TABLE_PT_NEG_33,TABLE_PT_NEG_32,TABLE_PT_NEG_31,
	TABLE_PT_NEG_30,TABLE_PT_NEG_29,TABLE_PT_NEG_28,TABLE_PT_NEG_27,TABLE_PT_NEG_26,
	TABLE_PT_NEG_25,TABLE_PT_NEG_24,TABLE_PT_NEG_23,TABLE_PT_NEG_22,TABLE_PT_NEG_21,
	TABLE_PT_NEG_20,TABLE_PT_NEG_19,TABLE_PT_NEG_18,TABLE_PT_NEG_17,TABLE_PT_NEG_16,
	TABLE_PT_NEG_15,TABLE_PT_NEG_14,TABLE_PT_NEG_13,TABLE_PT_NEG_12,TABLE_PT_NEG_11,
	TABLE_PT_NEG_10,TABLE_PT_NEG_09,TABLE_PT_NEG_08,TABLE_PT_NEG_07,TABLE_PT_NEG_06,
	TABLE_PT_NEG_05,TABLE_PT_NEG_04,TABLE_PT_NEG_03,TABLE_PT_NEG_02,TABLE_PT_NEG_01,
	TABLE_PT_MID_00,
	TABLE_PT_POS_01,TABLE_PT_POS_02,TABLE_PT_POS_03,TABLE_PT_POS_04,TABLE_PT_POS_05,
	TABLE_PT_POS_06,TABLE_PT_POS_07,TABLE_PT_POS_08,TABLE_PT_POS_09,TABLE_PT_POS_10,
	TABLE_PT_POS_11,TABLE_PT_POS_12,TABLE_PT_POS_13,TABLE_PT_POS_14,TABLE_PT_POS_15,
	TABLE_PT_POS_16,TABLE_PT_POS_17,TABLE_PT_POS_18,TABLE_PT_POS_19,TABLE_PT_POS_20,
	TABLE_PT_POS_21,TABLE_PT_POS_22,TABLE_PT_POS_23,TABLE_PT_POS_24,TABLE_PT_POS_25,
	TABLE_PT_POS_26,TABLE_PT_POS_27,TABLE_PT_POS_28,TABLE_PT_POS_29,TABLE_PT_POS_30,
	TABLE_PT_POS_31,TABLE_PT_POS_32,TABLE_PT_POS_33,TABLE_PT_POS_34,TABLE_PT_POS_35,
	TABLE_PT_POS_36,TABLE_PT_POS_37,TABLE_PT_POS_38,TABLE_PT_POS_39,TABLE_PT_POS_40,
	TABLE_PT_POS_41,TABLE_PT_POS_42,TABLE_PT_POS_43,TABLE_PT_POS_44,TABLE_PT_POS_45,
	TABLE_PT_POS_46,TABLE_PT_POS_47,TABLE_PT_POS_48,TABLE_PT_POS_49,TABLE_PT_POS_50,
	TABLE_PT_POS_51,TABLE_PT_POS_52,TABLE_PT_POS_53,TABLE_PT_POS_54,TABLE_PT_POS_55,
	TABLE_PT_POS_56,TABLE_PT_POS_57,TABLE_PT_POS_58,TABLE_PT_POS_59,TABLE_PT_POS_60,
	TABLE_PT_POS_61,TABLE_PT_POS_62,TABLE_PT_POS_63,TABLE_PT_POS_64,TABLE_PT_POS_65,
	TABLE_PT_POS_66,TABLE_PT_POS_67,TABLE_PT_POS_68,TABLE_PT_POS_69,TABLE_PT_POS_70
	
	};

											
uint16 TCB_source_data0[50]={	TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_00,//0
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_01,//1
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_02,//2
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_03,//3
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_26,//4
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_27,//5
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_28,//6
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_29,//7
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_04,//8
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_30,//9
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_08,//10
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_32,//11
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_06,//12
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_31,//13
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_46,//14
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_10,//15
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_33,//16
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_47,//17
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_12,//18
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_34,//19
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_14,//20
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_35,//21
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_16,//22
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_36,//23
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_18,//24
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_37,//25
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_48,//26
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_50,//27
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_52,//28
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_54,//29
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_56,//30
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_58,//31
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_60,//32
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_62,//33
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_64,//34
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_00,//35
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_02,//36
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_03,//37
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_05,//38
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_08,//39
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_10,//40
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_13,//41
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_17,//42
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_18,//43
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_22,//44
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_22,//45
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_24,//46
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_24,//47
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_26,//48
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_27//49
								
	
};


uint16 TCB_source_data1[50]={	TCB_INVALID_DATA,//0
								TCB_INVALID_DATA,//1
								TCB_INVALID_DATA,//2
								TCB_INVALID_DATA,//3
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_26,//4
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_27,//5
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_28,//6
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_29,//7
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_05,//8
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_38,//9
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_09,//10
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_39,//11
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_07,//12
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_31,//13
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_46,//14
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_11,//15
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_33,//16
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_47,//17
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_13,//18
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_34,//19
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_15,//20
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_35,//21
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_17,//22
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_36,//23
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_19,//24
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_37,//25
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_48,//26
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_50,//27
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_52,//28
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_54,//29
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_56,//30
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_58,//31
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_60,//32
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_62,//33
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_64,//34
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_01,//35
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_02,//36
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_04,//37
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_05,//38
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_08,//39
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_10,//40
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_13,//41
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_19,//42
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_19,//43
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_23,//44
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_23,//45
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_25,//46
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_25,//47
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_26,//48
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_28//49
	
};

uint16 TCB_source_data2[50]={	TCB_INVALID_DATA,//0
								TCB_INVALID_DATA,//1
								TCB_INVALID_DATA,//2
								TCB_INVALID_DATA,//3
								TCB_INVALID_DATA,//4
								TCB_INVALID_DATA,//5
								TCB_INVALID_DATA,//6
								TCB_INVALID_DATA,//7
								TCB_INVALID_DATA,//8
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_30,//9
								TCB_INVALID_DATA,//10
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_32,//11
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_24,//12
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_38,//13
								TCB_INVALID_DATA,//14
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_25,//15
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_39,//16
								TCB_INVALID_DATA,//17
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_20,//18
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_42,//19
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_21,//20
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_43,//21
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_22,//22
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_44,//23
								TCB_SENSOR_PT_R|TCB_FROM_100_A|TCB_WORD_A|TCB_LOC_23,//24
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_45,//25
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_49,//26
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_51,//27
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_53,//28
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_55,//29
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_57,//30
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_59,//31
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_61,//32
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_63,//33
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_00,//34
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_01,//35
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_03,//36
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_04,//37
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_06,//38
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_09,//39
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_11,//40
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_14,//41
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_15,//42
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_16,//43
								TCB_INVALID_DATA,//44
								TCB_INVALID_DATA,//45
								TCB_INVALID_DATA,//46
								TCB_INVALID_DATA,//47
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_27,//48
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_28//49
	
};

uint16 TCB_source_data3[50]={	TCB_INVALID_DATA,//0
								TCB_INVALID_DATA,//1
								TCB_INVALID_DATA,//2
								TCB_INVALID_DATA,//3
								TCB_INVALID_DATA,//4
								TCB_INVALID_DATA,//5
								TCB_INVALID_DATA,//6
								TCB_INVALID_DATA,//7
								TCB_INVALID_DATA,//8
								TCB_INVALID_DATA,//9
								TCB_INVALID_DATA,//10
								TCB_INVALID_DATA,//11
								TCB_INVALID_DATA,//12
								TCB_INVALID_DATA,//13
								TCB_INVALID_DATA,//14
								TCB_INVALID_DATA,//15
								TCB_INVALID_DATA,//16
								TCB_INVALID_DATA,//17
								TCB_INVALID_DATA,//18
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_42,//19
								TCB_INVALID_DATA,//20
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_43,//21
								TCB_INVALID_DATA,//22
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_44,//23
								TCB_INVALID_DATA,//24
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_45,//25
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_49,//26
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_51,//27
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_53,//28
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_55,//29
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_57,//30
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_59,//31
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_61,//32
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_63,//33
								TCB_INVALID_DATA,//34
								TCB_INVALID_DATA,//35
								TCB_INVALID_DATA,//36
								TCB_INVALID_DATA,//37
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_06,//38
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_09,//39
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_11,//40
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_14,//41
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_17,//42
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_18,//43
								TCB_INVALID_DATA,//44
								TCB_INVALID_DATA,//45
								TCB_INVALID_DATA,//46
								TCB_INVALID_DATA,//47
								TCB_INVALID_DATA,//48
								TCB_INVALID_DATA//49
};

uint16 TCB_source_data4[50]={	TCB_INVALID_DATA,//0
								TCB_INVALID_DATA,//1
								TCB_INVALID_DATA,//2
								TCB_INVALID_DATA,//3
								TCB_INVALID_DATA,//4
								TCB_INVALID_DATA,//5
								TCB_INVALID_DATA,//6
								TCB_INVALID_DATA,//7
								TCB_INVALID_DATA,//8
								TCB_INVALID_DATA,//9
								TCB_INVALID_DATA,//10
								TCB_INVALID_DATA,//11
								TCB_INVALID_DATA,//12
								TCB_INVALID_DATA,//13
								TCB_INVALID_DATA,//14
								TCB_INVALID_DATA,//15
								TCB_INVALID_DATA,//16
								TCB_INVALID_DATA,//17
								TCB_INVALID_DATA,//18
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_40,//19
								TCB_INVALID_DATA,//20
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_40,//21
								TCB_INVALID_DATA,//22
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_H|TCB_LOC_41,//23
								TCB_INVALID_DATA,//24
								TCB_SENSOR_MF61|TCB_FROM_100_A|TCB_BYTE_L|TCB_LOC_41,//25
								TCB_INVALID_DATA,//26
								TCB_INVALID_DATA,//27
								TCB_INVALID_DATA,//28
								TCB_INVALID_DATA,//29
								TCB_INVALID_DATA,//30
								TCB_INVALID_DATA,//31
								TCB_INVALID_DATA,//32
								TCB_INVALID_DATA,//33
								TCB_INVALID_DATA,//34
								TCB_INVALID_DATA,//35
								TCB_INVALID_DATA,//36
								TCB_INVALID_DATA,//37
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_07,//38
								TCB_INVALID_DATA,//39
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_12,//40
								TCB_INVALID_DATA,//41
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_15,//42
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_16,//43
								TCB_INVALID_DATA,//44
								TCB_INVALID_DATA,//45
								TCB_INVALID_DATA,//46
								TCB_INVALID_DATA,//47
								TCB_INVALID_DATA,//48
								TCB_INVALID_DATA//49
	
};

uint16 TCB_source_data5[50]={	TCB_INVALID_DATA,//0
								TCB_INVALID_DATA,//1
								TCB_INVALID_DATA,//2
								TCB_INVALID_DATA,//3
								TCB_INVALID_DATA,//4
								TCB_INVALID_DATA,//5
								TCB_INVALID_DATA,//6
								TCB_INVALID_DATA,//7
								TCB_INVALID_DATA,//8
								TCB_INVALID_DATA,//9
								TCB_INVALID_DATA,//10
								TCB_INVALID_DATA,//11
								TCB_INVALID_DATA,//12
								TCB_INVALID_DATA,//13
								TCB_INVALID_DATA,//14
								TCB_INVALID_DATA,//15
								TCB_INVALID_DATA,//16
								TCB_INVALID_DATA,//17
								TCB_INVALID_DATA,//18
								TCB_INVALID_DATA,//19
								TCB_INVALID_DATA,//20
								TCB_INVALID_DATA,//21
								TCB_INVALID_DATA,//22
								TCB_INVALID_DATA,//23
								TCB_INVALID_DATA,//24
								TCB_INVALID_DATA,//25
								TCB_INVALID_DATA,//26
								TCB_INVALID_DATA,//27
								TCB_INVALID_DATA,//28
								TCB_INVALID_DATA,//29
								TCB_INVALID_DATA,//30
								TCB_INVALID_DATA,//31
								TCB_INVALID_DATA,//32
								TCB_INVALID_DATA,//33
								TCB_INVALID_DATA,//34
								TCB_INVALID_DATA,//35
								TCB_INVALID_DATA,//36
								TCB_INVALID_DATA,//37
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_07,//38
								TCB_INVALID_DATA,//39
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_12,//40
								TCB_INVALID_DATA,//41
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_20,//42
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_H|TCB_LOC_21,//43
								TCB_INVALID_DATA,//44
								TCB_INVALID_DATA,//45
								TCB_INVALID_DATA,//46
								TCB_INVALID_DATA,//47
								TCB_INVALID_DATA,//48
								TCB_INVALID_DATA//49
	
};

uint16 TCB_source_data6[50]={	TCB_INVALID_DATA,//0
								TCB_INVALID_DATA,//1
								TCB_INVALID_DATA,//2
								TCB_INVALID_DATA,//3
								TCB_INVALID_DATA,//4
								TCB_INVALID_DATA,//5
								TCB_INVALID_DATA,//6
								TCB_INVALID_DATA,//7
								TCB_INVALID_DATA,//8
								TCB_INVALID_DATA,//9
								TCB_INVALID_DATA,//10
								TCB_INVALID_DATA,//11
								TCB_INVALID_DATA,//12
								TCB_INVALID_DATA,//13
								TCB_INVALID_DATA,//14
								TCB_INVALID_DATA,//15
								TCB_INVALID_DATA,//16
								TCB_INVALID_DATA,//17
								TCB_INVALID_DATA,//18
								TCB_INVALID_DATA,//19
								TCB_INVALID_DATA,//20
								TCB_INVALID_DATA,//21
								TCB_INVALID_DATA,//22
								TCB_INVALID_DATA,//23
								TCB_INVALID_DATA,//24
								TCB_INVALID_DATA,//25
								TCB_INVALID_DATA,//26
								TCB_INVALID_DATA,//27
								TCB_INVALID_DATA,//28
								TCB_INVALID_DATA,//29
								TCB_INVALID_DATA,//30
								TCB_INVALID_DATA,//31
								TCB_INVALID_DATA,//32
								TCB_INVALID_DATA,//33
								TCB_INVALID_DATA,//34
								TCB_INVALID_DATA,//35
								TCB_INVALID_DATA,//36
								TCB_INVALID_DATA,//37
								TCB_INVALID_DATA,//38
								TCB_INVALID_DATA,//39
								TCB_INVALID_DATA,//40
								TCB_INVALID_DATA,//41
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_20,//42
								TCB_SENSOR_MF61|TCB_FROM_100_B|TCB_BYTE_L|TCB_LOC_21,//43
								TCB_INVALID_DATA,//44
								TCB_INVALID_DATA,//45
								TCB_INVALID_DATA,//46
								TCB_INVALID_DATA,//47
								TCB_INVALID_DATA,//48
								TCB_INVALID_DATA//49
	
};
											
											
/******************************************************************************************
**���ƣ����²�����ʼ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_tempercontrol_initial(void)
{
	uint16 i;

/*�¶ȿ��ƿ�ṹ���ʼ��-----------------------------------------------------------------*/
	
	for(i=0;i<=49;i++)
	{
		if(((i>=26)&&(i<=37))||((i>=44)&&(i<=49)))
		{
			Temperature_control_block[i].control_state=DISABLE;//����ϵͳ��ʼ�����������Զ�����
		}
		
		else
		{
			Temperature_control_block[i].control_state=ENABLE;//�ƽ�ϵͳ��ʼ���������Զ�����
		}
		
		Temperature_control_block[i].fixed_output_state=DISABLE;//���»�·��ʼ�����޹̶�ռ�ձ����
		
		Temperature_control_block[i].control_spot[0]=TEMPER_SPOT_T1;//���µ�T1����ʼֵ4���϶ȣ�MF61Դ��ֵ
		Temperature_control_block[i].control_spot[1]=TEMPER_SPOT_T2;//���µ�T2����ʼֵ8���϶ȣ�MF61Դ��ֵ
		Temperature_control_block[i].control_spot[2]=TEMPER_SPOT_T3;//���µ�T3����ʼֵ12���϶ȣ�MF61Դ��ֵ
		
		Temperature_control_block[i].power[0]=Tempercontrol_Power[2*i];//��·���Ȼ�·����
		Temperature_control_block[i].power[1]=Tempercontrol_Power[2*i+1];//��·���Ȼ�·����
		
		Temperature_control_block[i].fixed_output_count=0x0000;//�̶�ռ�ر����������
		
		Temperature_control_block[i].source_data[0]=TCB_source_data0[i];
		Temperature_control_block[i].source_data[1]=TCB_source_data1[i];
		Temperature_control_block[i].source_data[2]=TCB_source_data2[i];
		Temperature_control_block[i].source_data[3]=TCB_source_data3[i];
		Temperature_control_block[i].source_data[4]=TCB_source_data4[i];
		Temperature_control_block[i].source_data[5]=TCB_source_data5[i];
		Temperature_control_block[i].source_data[6]=TCB_source_data6[i];//���²��λ�����ݳ�ʼ��
	
		Temperature_control_block[i].number=i;
	}
	
	
/*�¶ȿ���ȫ�ֱ����ṹ���ʼ��------------------------------------------------------------*/
	
	Temperature_control_global.source=SOURCE_DATA_TGTHT100;//����ʹ��ң��������Դ����ʼ��Ϊ�ƽ�ң����·��
	
	Temperature_control_global.data_state_TGTHT100=ENABLE;//ң����·���¶���������
	
	Temperature_control_global.data_state_KPU=ENABLE;//����ң����������
	
	Temperature_control_global.total_power=POWER_INITIAL;//�ܹ�������300W

/*�¶ȿ�����Ч�����ṹ���ʼ��------------------------------------------------------------*/

	Temperature_control_valid_data.auto_control_count=0;
		
	Temperature_control_valid_data.fixed_control_count=0;
		
	for(i=0;i<=49;i++)
	{
		Temperature_control_valid_data.auto_control_data[i]=TEMPER_SPOT_T3;
		
		Temperature_control_valid_data.auto_control_num[i]=i;
		
		Temperature_control_valid_data.fixed_control_data[i]=0x0000;
		
		Temperature_control_valid_data.fixed_control_num[i]=i;
		
		Temperature_control_valid_data.auto_control_last_state_main[i]=DISABLE;
		
		Temperature_control_valid_data.auto_control_last_state_less[i]=DISABLE;

	}
	
/*���������ƼĴ�����ʼ��---------------------------------------------------------------------*/	
	
	for(i=0;i<=7;i++)
	{
		Temperature_control_reg[i]=0x0000;
	}
	
	
}



/******************************************************************************************
**���ƣ�MF51ת��ΪMF61ת������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_tempercontrol_mf51_to_mf61(uint16 temp_mf51)
{
	uint16 range;
	uint16 mf61_temper;
	uint16 num;
	
	if((temp_mf51>TEMP_MF51_NEG_50)||(temp_mf51<TEMP_MF51_POS_70))
	{
		mf61_temper=TEMP_MF61_POS_70;
	}
	
	else
	{
		range=TGTHT510_tempercontrol_mf51_range_calculate(temp_mf51);//��ȡMF51�¶ȵķ�Χ
		num=TGTHT510_tempercontrol_mf51_sourcecode_to_centigrade_calculate(temp_mf51,range);//��ȡMF51�¶�Դ���Ӧ�����϶ȣ�����ѯ���±�
		mf61_temper=Tempercontrol_MF61_code[num];//�������϶ȣ����ö�ӦMF61��Դ��ֵ
	}

	return mf61_temper;
}

/******************************************************************************************
**���ƣ�MF51�¶ȷ�Χ���㺯��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_tempercontrol_mf51_range_calculate(uint16 temp_mf51)
{
	uint16 range;
	
	if(temp_mf51>TEMP_MF51_NEG_50)//MF51�¶ȷ�Χ��С��-50���϶�
	{
		range=TEMP_MF51_RANGE_LARGER_POS_70;
		//range=TEMP_MF61_RANGE_SMALLER_NEG_50;
	}
	
	else if((temp_mf51<=TEMP_MF51_NEG_50)&&(temp_mf51>TEMP_MF51_NEG_40))//MF51�¶ȷ�Χ�����ڵ���-50���϶ȣ�С��-40���϶�
	{
		range=TEMP_MF51_RANGE_NEG_50_40;
	}
	
	else if((temp_mf51<=TEMP_MF51_NEG_40)&&(temp_mf51>TEMP_MF51_NEG_30))//MF51�¶ȷ�Χ�����ڵ���-40���϶ȣ�С��-30���϶�
	{
		range=TEMP_MF51_RANGE_NEG_40_30;
	}

	else if((temp_mf51<=TEMP_MF51_NEG_30)&&(temp_mf51>TEMP_MF51_NEG_20))//MF51�¶ȷ�Χ�����ڵ���-30���϶ȣ�С��-20���϶�
	{
		range=TEMP_MF51_RANGE_NEG_30_20;
	}
	
	else if((temp_mf51<=TEMP_MF51_NEG_20)&&(temp_mf51>TEMP_MF51_NEG_10))//MF51�¶ȷ�Χ�����ڵ���-20���϶ȣ�С��-10���϶�
	{
		range=TEMP_MF51_RANGE_NEG_20_10;
	}
	
	else if((temp_mf51<=TEMP_MF51_NEG_10)&&(temp_mf51>TEMP_MF51_MID_0))//MF51�¶ȷ�Χ�����ڵ���-10���϶ȣ�С��0���϶�
	{
		range=TEMP_MF51_RANGE_NEG_10_0;
	}
	
	else if((temp_mf51<=TEMP_MF51_MID_0)&&(temp_mf51>TEMP_MF51_POS_10))//MF51�¶ȷ�Χ�����ڵ���0���϶ȣ�С��10���϶�
	{
		range=TEMP_MF51_RANGE_POS_0_10;
	}
	
	else if((temp_mf51<=TEMP_MF51_POS_10)&&(temp_mf51>TEMP_MF51_POS_20))//MF51�¶ȷ�Χ�����ڵ���10���϶ȣ�С��20���϶�
	{
		range=TEMP_MF51_RANGE_POS_10_20;
	}
	
	else if((temp_mf51<=TEMP_MF51_POS_20)&&(temp_mf51>TEMP_MF51_POS_30))//MF51�¶ȷ�Χ�����ڵ���20���϶ȣ�С��30���϶�
	{
		range=TEMP_MF51_RANGE_POS_20_30;
	}
	
	else if((temp_mf51<=TEMP_MF51_POS_30)&&(temp_mf51>TEMP_MF51_POS_40))//MF51�¶ȷ�Χ�����ڵ���30���϶ȣ�С��40���϶�
	{
		range=TEMP_MF51_RANGE_POS_30_40;
	}
	
	else if((temp_mf51<=TEMP_MF51_POS_40)&&(temp_mf51>TEMP_MF51_POS_50))//MF51�¶ȷ�Χ�����ڵ���40���϶ȣ�С��50���϶�
	{
		range=TEMP_MF51_RANGE_POS_40_50;
	}
	
	else if((temp_mf51<=TEMP_MF51_POS_50)&&(temp_mf51>TEMP_MF51_POS_60))//MF51�¶ȷ�Χ�����ڵ���50���϶ȣ�С��60���϶�
	{
		range=TEMP_MF51_RANGE_POS_50_60;
	}
	
	else if((temp_mf51<=TEMP_MF51_POS_60)&&(temp_mf51>TEMP_MF51_POS_70))//MF51�¶ȷ�Χ�����ڵ���60���϶ȣ�С��70���϶�
	{
		range=TEMP_MF51_RANGE_POS_60_70;
	}
	
	else//MF51�¶ȷ�Χ�����ڵ���70���϶�
	{
		range=TEMP_MF51_RANGE_LARGER_POS_70;
	}
	
	return range;
	
}



/******************************************************************************************
**���ƣ�MF51�¶�Դ��ת��Ϊ���϶ȼ��㺯��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_tempercontrol_mf51_sourcecode_to_centigrade_calculate(uint16 temp_mf51,uint16 range)
{
	uint16 num;
	uint16 i;
	
	switch(range)
	{
		case TEMP_MF51_RANGE_SMALLER_NEG_50://MF51�¶ȷ�Χ��С��-50���϶�
		{
			num=0;
			break;
		}
		
		case TEMP_MF51_RANGE_NEG_50_40://MF51�¶ȷ�Χ�����ڵ���-50���϶ȣ�С��-40���϶�
		{
			i=TEMP_MF51_RANGE_NEG_50_40_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_NEG_40_30://MF51�¶ȷ�Χ�����ڵ���-40���϶ȣ�С��-30���϶�
		{
			i=TEMP_MF51_RANGE_NEG_40_30_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_NEG_30_20://MF51�¶ȷ�Χ�����ڵ���-30���϶ȣ�С��-20���϶�
		{
			i=TEMP_MF51_RANGE_NEG_30_20_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_NEG_20_10://MF51�¶ȷ�Χ�����ڵ���-20���϶ȣ�С��-10���϶�
		{
			i=TEMP_MF51_RANGE_NEG_20_10_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_NEG_10_0://MF51�¶ȷ�Χ�����ڵ���-10���϶ȣ�С��0���϶�
		{
			i=TEMP_MF51_RANGE_NEG_10_0_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_0_10://MF51�¶ȷ�Χ�����ڵ���0���϶ȣ�С��10���϶�
		{
			i=TEMP_MF51_RANGE_POS_0_10_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_10_20://MF51�¶ȷ�Χ�����ڵ���10���϶ȣ�С��20���϶�
		{
			i=TEMP_MF51_RANGE_POS_10_20_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_20_30://MF51�¶ȷ�Χ�����ڵ���20���϶ȣ�С��30���϶�
		{
			i=TEMP_MF51_RANGE_POS_20_30_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_30_40://MF51�¶ȷ�Χ�����ڵ���30���϶ȣ�С��40���϶�
		{
			i=TEMP_MF51_RANGE_POS_30_40_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_40_50://MF51�¶ȷ�Χ�����ڵ���40���϶ȣ�С��50���϶�
		{
			i=TEMP_MF51_RANGE_POS_40_50_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_50_60://MF51�¶ȷ�Χ�����ڵ���50���϶ȣ�С��600���϶�
		{
			i=TEMP_MF51_RANGE_POS_50_60_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_60_70://MF51�¶ȷ�Χ�����ڵ���60���϶ȣ�С��70���϶�
		{
			i=TEMP_MF51_RANGE_POS_60_70_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_LARGER_POS_70://MF51�¶ȷ�Χ�����ڵ���70���϶�
		{
			num=120;
			break;
		}
		
		default:
		{
			num=120;
			break;
		}
		
		
	}
	
	return num;
	
}


/******************************************************************************************
**���ƣ�MF51�¶�Դ����Ƽ��㺯��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_tempercontrol_mf51_centigrade_num_calculate(uint16 start_i,uint16 temp_mf51)
{
	uint16 i;
	uint16 last_abs_num;
	uint16 now_abs_num;
	uint16 centigrade_num;
	
	last_abs_num=abs(temp_mf51-Tempercontrol_MF51_code[start_i]);
	centigrade_num=start_i;
	i=start_i;
	
	while(i<=start_i+9)
	{
		i++;
		now_abs_num=abs(temp_mf51-Tempercontrol_MF51_code[i]);
		if(now_abs_num>=last_abs_num)
		{
			centigrade_num=i-1;
			break;
		}
		
		centigrade_num=i-1;
		
		last_abs_num=now_abs_num;
		
	}
	
	return centigrade_num;
	
	
}

/******************************************************************************************
**���ƣ�������ת��ΪMF61ת������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_tempercontrol_pt_to_mf61(uint16 temp_pt)
{
	uint16 range;
	uint16 mf61_temper;
	uint16 num;
	
	
	if((temp_pt>TEMP_PT_POS_70)||(temp_pt<TEMP_PT_NEG_50))
	{
		mf61_temper=TEMP_MF61_POS_70;
	}
	
	else
	{
		range=TGTHT510_tempercontrol_pt_range_calculate(temp_pt);//��ȡ�������¶ȵķ�Χ
		num=TGTHT510_tempercontrol_pt_sourcecode_to_centigrade_calculate(temp_pt,range);//��ȡ�������¶�Դ���Ӧ�����϶�
		mf61_temper=Tempercontrol_MF61_code[num];//�������϶ȣ����ö�ӦMF61��Դ��ֵ
	}
	
	return mf61_temper;

}


/******************************************************************************************
**���ƣ��������¶ȷ�Χ���㺯��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_tempercontrol_pt_range_calculate(uint16 temp_pt)
{
	uint16 range;
	
	if(temp_pt<TEMP_PT_NEG_50)//�������¶ȷ�Χ��С��-50���϶�
	{
		range=TEMP_PT_RANGE_LARGER_POS_70;
		//range=TEMP_PT_RANGE_SMALLER_NEG_50;
		
	}
	
	else if((temp_pt>=TEMP_PT_NEG_50)&&(temp_pt<TEMP_PT_NEG_40))//�������¶ȷ�Χ�����ڵ���-50���϶ȣ�С��-40���϶�
	{
		range=TEMP_PT_RANGE_NEG_50_40;
		
	}
	
	else if((temp_pt>=TEMP_PT_NEG_40)&&(temp_pt<TEMP_PT_NEG_30))//�������¶ȷ�Χ�����ڵ���-40���϶ȣ�С��-30���϶�
	{
		range=TEMP_PT_RANGE_NEG_40_30;
	}
	
	else if((temp_pt>=TEMP_PT_NEG_30)&&(temp_pt<TEMP_PT_NEG_20))//�������¶ȷ�Χ�����ڵ���-30���϶ȣ�С��-20���϶�
	{
		range=TEMP_PT_RANGE_NEG_30_20;
	}
	
	else if((temp_pt>=TEMP_PT_NEG_20)&&(temp_pt<TEMP_PT_NEG_10))//�������¶ȷ�Χ�����ڵ���-20���϶ȣ�С��-10���϶�
	{
		range=TEMP_PT_RANGE_NEG_20_10;
		
	}
	
	else if((temp_pt>=TEMP_PT_NEG_10)&&(temp_pt<TEMP_PT_MID_0))//�������¶ȷ�Χ�����ڵ���-10���϶ȣ�С��0���϶�
	{
		range=TEMP_PT_RANGE_NEG_10_0;
		
	}
	
	else if((temp_pt>=TEMP_PT_MID_0)&&(temp_pt<TEMP_PT_POS_10))//�������¶ȷ�Χ�����ڵ���0���϶ȣ�С��10���϶�
	{
		range=TEMP_PT_RANGE_POS_0_10;
		
	}
	
	else if((temp_pt>=TEMP_PT_POS_10)&&(temp_pt<TEMP_PT_POS_20))//�������¶ȷ�Χ�����ڵ���10���϶ȣ�С��20���϶�
	{
		range=TEMP_PT_RANGE_POS_10_20;
		
	}
	
	else if((temp_pt>=TEMP_PT_POS_20)&&(temp_pt<TEMP_PT_POS_30))//�������¶ȷ�Χ�����ڵ���20���϶ȣ�С��30���϶�
	{
		range=TEMP_PT_RANGE_POS_20_30;
		
	}
	
	else if((temp_pt>=TEMP_PT_POS_30)&&(temp_pt<TEMP_PT_POS_40))//�������¶ȷ�Χ�����ڵ���30���϶ȣ�С��40���϶�
	{
		range=TEMP_PT_RANGE_POS_30_40;
		
	}
	
	else if((temp_pt>=TEMP_PT_POS_40)&&(temp_pt<TEMP_PT_POS_50))//�������¶ȷ�Χ�����ڵ���40���϶ȣ�С��50���϶�
	{
		range=TEMP_PT_RANGE_POS_40_50;
		
	}
	
	else if((temp_pt>=TEMP_PT_POS_50)&&(temp_pt<TEMP_PT_POS_60))//�������¶ȷ�Χ�����ڵ���50���϶ȣ�С��60���϶�
	{
		range=TEMP_PT_RANGE_POS_50_60;
		
	}
	
	else if((temp_pt>=TEMP_PT_POS_60)&&(temp_pt<TEMP_PT_POS_70))//�������¶ȷ�Χ�����ڵ���60���϶ȣ�С��70���϶�
	{
		range=TEMP_PT_RANGE_POS_60_70;
		
	}
	
	else//�������¶ȷ�Χ�����ڵ���70���϶�
	{
		range=TEMP_PT_RANGE_LARGER_POS_70;
		
	}
	
	return range;
	
	
}

/******************************************************************************************
**���ƣ��������¶�Դ����Ƽ��㺯��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_tempercontrol_pt_centigrade_num_calculate(uint16 start_i,uint16 temp_pt)
{
	uint16 i;
	uint16 last_abs_num;
	uint16 now_abs_num;
	uint16 centigrade_num;
	
	last_abs_num=abs(temp_pt-Tempercontrol_Pt_code[start_i]);
	centigrade_num=start_i;
	i=start_i;
	
	while(i<=start_i+9)
	{
		i++;
		now_abs_num=abs(temp_pt-Tempercontrol_Pt_code[i]);
		if(now_abs_num>=last_abs_num)
		{
			centigrade_num=i-1;
			break;
		}
		
		centigrade_num=i-1;
		
		last_abs_num=now_abs_num;
	}
	
	return centigrade_num;
}

/******************************************************************************************
**���ƣ��������¶�Դ��ת��Ϊ���϶ȼ��㺯��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_tempercontrol_pt_sourcecode_to_centigrade_calculate(uint16 temp_pt,uint16 range)
{
	uint16 num;
	uint16 i;
	
	switch(range)
	{
		case TEMP_PT_RANGE_SMALLER_NEG_50://�������¶ȷ�Χ��С��-50���϶�
		{
			num=0;
			break;
		}
		
		case TEMP_PT_RANGE_NEG_50_40://�������¶ȷ�Χ�����ڵ���-50���϶ȣ�С��-40���϶�
		{
			i=TEMP_PT_RANGE_NEG_50_40_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_NEG_40_30://�������¶ȷ�Χ�����ڵ���-40���϶ȣ�С��-30���϶�
		{
			i=TEMP_PT_RANGE_NEG_40_30_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_NEG_30_20://�������¶ȷ�Χ�����ڵ���-30���϶ȣ�С��-20���϶�
		{
			i=TEMP_PT_RANGE_NEG_30_20_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_NEG_20_10://�������¶ȷ�Χ�����ڵ���-20���϶ȣ�С��-10���϶�
		{
			i=TEMP_PT_RANGE_NEG_20_10_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_NEG_10_0://�������¶ȷ�Χ�����ڵ���-10���϶ȣ�С��0���϶�
		{
			i=TEMP_PT_RANGE_NEG_10_0_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_0_10://�������¶ȷ�Χ�����ڵ���0���϶ȣ�С��10���϶�
		{
			i=TEMP_PT_RANGE_POS_0_10_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_10_20://�������¶ȷ�Χ�����ڵ���10���϶ȣ�С��20���϶�
		{
			i=TEMP_PT_RANGE_POS_10_20_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_20_30://�������¶ȷ�Χ�����ڵ���20���϶ȣ�С��30���϶�
		{
			i=TEMP_PT_RANGE_POS_20_30_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_30_40://�������¶ȷ�Χ�����ڵ���30���϶ȣ�С��40���϶�
		{
			i=TEMP_PT_RANGE_POS_30_40_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_40_50://�������¶ȷ�Χ�����ڵ���40���϶ȣ�С��50���϶�
		{
			i=TEMP_PT_RANGE_POS_40_50_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_50_60://�������¶ȷ�Χ�����ڵ���50���϶ȣ�С��600���϶�
		{
			i=TEMP_PT_RANGE_POS_50_60_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_60_70://�������¶ȷ�Χ�����ڵ���60���϶ȣ�С��70���϶�
		{
			i=TEMP_PT_RANGE_POS_60_70_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_LARGER_POS_70://�������¶ȷ�Χ�����ڵ���70���϶�
		{
			num=120;
			break;
		}
		
		default:
		{
			num=120;
			break;
		}
		
		
	}
	
	return num;
	
}



/******************************************************************************************
**���ƣ�������Ч�������ɺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**����������typeΪSOURCE_DATA_TGTHT100����Ϊʹ���ƽ�ң����·��
		����typeΪSOURCE_DATA_KPU����Ϊ����
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/


void TGTHT510_tempercontrol_valid_data_generate(uint16 type)
{
	uint16 i;
	
	if(type==SOURCE_DATA_TGTHT100)//�����ƽ�ң����·���¶��������ɿ�����Ч����
	{
		TGTHT510_tempercontrol_valid_data_from_TGTHT100();
		
	}
	
	else if(type==SOURCE_DATA_KPU)//���������¶��������ɿ�����Ч����
	{

/*------------------------------------���޸�----------------------------------------------*/	
/*�¶ȿ�����Ч�����ṹ���ʼ��------------------------------------------------------------*/
		
		Temperature_control_valid_data.auto_control_count=0;
		
		Temperature_control_valid_data.fixed_control_count=0;
		
		for(i=0;i<=49;i++)
		{
			Temperature_control_valid_data.auto_control_data[i]=TEMPER_SPOT_T3;
		
			Temperature_control_valid_data.auto_control_num[i]=i;
		
			Temperature_control_valid_data.fixed_control_data[i]=0x0000;
		
			Temperature_control_valid_data.fixed_control_num[i]=i;

		}
/*---------------------------------------------------------------------------------------*/

		
	}
	
	else
	{
		Temperature_control_valid_data.auto_control_count=0;
		
		Temperature_control_valid_data.fixed_control_count=0;
		
		for(i=0;i<=49;i++)
		{
			Temperature_control_valid_data.auto_control_data[i]=TEMPER_SPOT_T3;
		
			Temperature_control_valid_data.auto_control_num[i]=i;
		
			Temperature_control_valid_data.fixed_control_data[i]=0x0000;
		
			Temperature_control_valid_data.fixed_control_num[i]=i;

		}
	}

}


/******************************************************************************************
**���ƣ��ƽ�ң����·�п�����Ч�������ɺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_tempercontrol_valid_data_from_TGTHT100(void)
{
	uint16 i;
	uint16 temp[7];
	
	Temperature_control_valid_data.fixed_control_count=0;//�̶�ռ�ձ������·��������
	Temperature_control_valid_data.auto_control_count=0;//�Զ����»�·��������
	
	for(i=0;i<=49;i++)
	{
		if(Temperature_control_block[i].control_state==ENABLE)//�ÿ��»�·�������
		{
			if(Temperature_control_block[i].fixed_output_state==ENABLE)//�̶�ռ�ձ����
			{	
				TGTHT510_tempercontrol_valid_data_from_TGTHT100_fixed_control(i);//�̶�ռ�ձ���Ч����
			}
			
			else//�Զ�����
			{
				TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control(i);//�Զ�������Ч����
			}

			
		}
		else
		{
			asm("nop;");
		}	
	}
	
	if(Temperature_control_valid_data.auto_control_count>=1)
	{
		TGTHT510_tempercontrol_valid_data_from_TGTHT100_sort();//��Ҫ���Զ����µĲ���Temperature_control_valid_data��������
	}
	
	else
	{
		asm("nop;");
	}
	
	
	
	
}



/******************************************************************************************
**���ƣ��ƽ�ң����·�п�����Ч�������ɺ���֮�̶�ռ�ձ������Ч����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_tempercontrol_valid_data_from_TGTHT100_fixed_control(uint16 num)
{
	uint16 i;
	i=Temperature_control_valid_data.fixed_control_count;
	
	Temperature_control_valid_data.fixed_control_data[i]=Temperature_control_block[num].fixed_output_count;
	
	Temperature_control_valid_data.fixed_control_num[i]=Temperature_control_block[num].number;
	
	Temperature_control_valid_data.fixed_control_count++;

}


/******************************************************************************************
**���ƣ��ƽ�ң����·�п�����Ч�������ɺ���֮�Զ�������Ч����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control(uint16 num)
{
	Temperature_control_temp_TypeDef a;
	uint16 i;
	uint16 r;
	
	a=TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control_source_data(num);//��øÿ��»�·��7�����Դ��ֵ���Ѿ�ת��ΪMF61Դ��
	
	r=TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control_source_data_sort(a);//��ȡ�ÿ��»�·��7�����Դ��ֵ���¶���͵�Դ��ֵ
	
	i=Temperature_control_valid_data.auto_control_count;
	
	Temperature_control_valid_data.auto_control_data[i]=r;//�����¶���͵�Դ��ֵ
	
	Temperature_control_valid_data.auto_control_num[i]=Temperature_control_block[num].number;//������»�··��
	
	Temperature_control_valid_data.auto_control_count++;//���»�·��������

	
}



/******************************************************************************************
**���ƣ��ƽ�ң����·�п�����Ч�������ɺ���֮�Զ�������Ч����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

Temperature_control_temp_TypeDef TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control_source_data(uint16 num)
{
	Temperature_control_temp_TypeDef d;//��ʱ����ṹ������
	uint16 i;
	uint16 m,j,k;
	
	for(i=0;i<=6;i++)
	{
		m=Temperature_control_block[num].source_data[i];//���������Դ��ʶ
		
		if(m==0xffff)//�޲�㣬�����
		{
			d.temp[i]=TEMP_MF61_POS_70;//���Ϊ70���϶�MF61Դ��ֵ
		}
		
		else
		{
			if((m&0x3000)==0x1000)//����ң����·�и�֡A֡
			{
				if((m&0x0c00)==0x0000)//ң��֡��
				{
					if((m&0xc000)==0x0000)//������ΪMF51
					{
						j=TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff];
						d.temp[i]=TGTHT510_tempercontrol_mf51_to_mf61(j);	
					}
					
					else if((m&0xc000)==0x4000)//������Ϊ������
					{
						j=TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff];
						d.temp[i]=TGTHT510_tempercontrol_pt_to_mf61(j);
					}
					
					else if((m&0xc000)==0x8000)//������ΪMF61
					{
						d.temp[i]=TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff];
						if(d.temp[i]>=TEMP_MF61_NEG_50)//MF61�¶ȵ���-50���϶�
						{
							d.temp[i]=TEMP_MF61_POS_70;
						}
					}
					
					else//��Դ��ʶ����
					{
						for(k=0;k<=6;k++)
						{
							d.temp[k]=TEMP_MF61_POS_70;//���Ϊ70���϶�MF61Դ��ֵ
							return d;
						}
					}

				}
				
				else if((m&0x0c00)==0x0400)//ң��֡���ֽ�
				{
					if((m&0xc000)==0x0000)//������ΪMF51
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff])&0xff00)>>4);
						d.temp[i]=TGTHT510_tempercontrol_mf51_to_mf61(j);
					}
					
					else if((m&0xc000)==0x4000)//������Ϊ������
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff])&0xff00)>>4);
						d.temp[i]=TGTHT510_tempercontrol_pt_to_mf61(j);
					}
					
					else if((m&0xc000)==0x8000)//������ΪMF61
					{
						d.temp[i]=(((TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff])&0xff00)>>4);
						if(d.temp[i]>=TEMP_MF61_NEG_50)//MF61�¶ȵ���-50���϶�
						{
							d.temp[i]=TEMP_MF61_POS_70;
						}
					}
					
					else//��Դ��ʶ����
					{
						for(k=0;k<=6;k++)
						{
							d.temp[k]=TEMP_MF61_POS_70;//���Ϊ70���϶�MF61Դ��ֵ
							return d;
						}
					}
					
				}
				
				else if((m&0x0c00)==0x0800)//ң��֡���ֽ�
				{
					if((m&0xc000)==0x0000)//������ΪMF51
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff])&0x00ff)<<4);
						d.temp[i]=TGTHT510_tempercontrol_mf51_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x4000)//������Ϊ������
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff])&0x00ff)<<4);
						d.temp[i]=TGTHT510_tempercontrol_pt_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x8000)//������ΪMF61
					{
						d.temp[i]=(((TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff])&0x00ff)<<4);
						if(d.temp[i]>=TEMP_MF61_NEG_50)//MF61�¶ȵ���-50���϶�
						{
							d.temp[i]=TEMP_MF61_POS_70;
						}
					}
					
					else//��Դ��ʶ����
					{
						for(k=0;k<=6;k++)
						{
							d.temp[k]=TEMP_MF61_POS_70;//���Ϊ70���϶�MF61Դ��ֵ
							return d;
						}
					}
					
				}
				
				else//��Դ��ʶ����
				{
					for(k=0;k<=6;k++)
					{
						d.temp[k]=TEMP_MF61_POS_70;//���Ϊ70���϶�MF61Դ��ֵ
						return d;
					}
					
				}

			}
			
			else if((m&0x3000)==0x2000)//����ң����·�и�֡B֡
			{
				if((m&0x0c00)==0x0000)//ң��֡��
				{
					if((m&0xc000)==0x0000)//������ΪMF51
					{
						j=TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff];
						d.temp[i]=TGTHT510_tempercontrol_mf51_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x4000)//������Ϊ������
					{
						j=TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff];
						d.temp[i]=TGTHT510_tempercontrol_pt_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x8000)//������ΪMF61
					{
						d.temp[i]=TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff];
						if(d.temp[i]>=TEMP_MF61_NEG_50)//MF61�¶ȵ���-50���϶�
						{
							d.temp[i]=TEMP_MF61_POS_70;
						}
						
					}
					
					else//��Դ��ʶ����
					{
						for(k=0;k<=6;k++)
						{
							d.temp[k]=TEMP_MF61_POS_70;//���Ϊ70���϶�MF61Դ��ֵ
							return d;
						}
						
					}
					
				}
				
				else if((m&0x0c00)==0x0400)//ң��֡���ֽ�
				{
					if((m&0xc000)==0x0000)//������ΪMF51
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff])&0xff00)>>4);
						d.temp[i]=TGTHT510_tempercontrol_mf51_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x4000)//������Ϊ������
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff])&0xff00)>>4);
						d.temp[i]=TGTHT510_tempercontrol_pt_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x8000)//������ΪMF61
					{
						d.temp[i]=(((TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff])&0xff00)>>4);
						if(d.temp[i]>=TEMP_MF61_NEG_50)//MF61�¶ȵ���-50���϶�
						{
							d.temp[i]=TEMP_MF61_POS_70;
						}
						
					}
					
					else//��Դ��ʶ����
					{
						for(k=0;k<=6;k++)
						{
							d.temp[k]=TEMP_MF61_POS_70;//���Ϊ70���϶�MF61Դ��ֵ
							return d;
						}
						
					}
					
				}
				
				else if((m&0x0c00)==0x0800)//ң��֡���ֽ�
				{
					if((m&0xc000)==0x0000)//������ΪMF51
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff])&0x00ff)<<4);
						d.temp[i]=TGTHT510_tempercontrol_mf51_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x4000)//������Ϊ������
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff])&0x00ff)<<4);
						d.temp[i]=TGTHT510_tempercontrol_pt_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x8000)//������ΪMF61
					{
						d.temp[i]=(((TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff])&0x00ff)<<4);
						if(d.temp[i]>=TEMP_MF61_NEG_50)//MF61�¶ȵ���-50���϶�
						{
							d.temp[i]=TEMP_MF61_POS_70;
						}
						
					}
					
					else//��Դ��ʶ����
					{
						for(k=0;k<=6;k++)
						{
							d.temp[k]=TEMP_MF61_POS_70;//���Ϊ70���϶�MF61Դ��ֵ
							return d;
						}
						
					}
					
				}
				
				else//��Դ��ʶ����
				{
					for(k=0;k<=6;k++)
					{
						d.temp[k]=TEMP_MF61_POS_70;//���Ϊ70���϶�MF61Դ��ֵ
						return d;
					}
					
				}
				
			}
			
			else//��Դ��ʶ����
			{
				for(k=0;k<=6;k++)
				{
					d.temp[k]=TEMP_MF61_POS_70;//���Ϊ70���϶�MF61Դ��ֵ
					return d;
				}
	
			}

		}

	}
	
	return d;
}


/******************************************************************************************
**���ƣ��ƽ�ң����·�п�����Ч�������ɺ���֮�Զ�������Ч��������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**���������������7�����ݣ������Ѿ�ת��ΪMF61��Դ��ֵ���������¶���͵�Դ��ֵ������ӦԴ����ֵ���
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control_source_data_sort(Temperature_control_temp_TypeDef d)
{
	uint16 i;
	uint16 max;
	
	max=d.temp[0];
	
	for(i=1;i<=6;i++)
	{
		if(d.temp[i]>max)
		{
			max=d.temp[i];
		}
		
		else
		{
			max=max;
		}
		
	}
	
	return max;
	
	
}

/******************************************************************************************
**���ƣ��Զ����µĲ���Temperature_control_valid_data��������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**���������������7�����ݣ������Ѿ�ת��ΪMF61��Դ��ֵ���������¶���͵�Դ��ֵ������ӦԴ����ֵ���
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_tempercontrol_valid_data_from_TGTHT100_sort(void)
{
	uint16 i;
	uint16 j;
	uint16 temp;
	
	for(i=0;i<=Temperature_control_valid_data.auto_control_count-1;i++)
	{
		for(j=i+1;j<=Temperature_control_valid_data.auto_control_count;j++)
		{
			if(Temperature_control_valid_data.auto_control_data[i]<Temperature_control_valid_data.auto_control_data[j])
			{
				temp=Temperature_control_valid_data.auto_control_data[i];
				Temperature_control_valid_data.auto_control_data[i]=Temperature_control_valid_data.auto_control_data[j];
				Temperature_control_valid_data.auto_control_data[j]=temp;
				
				temp=Temperature_control_valid_data.auto_control_num[i];
				Temperature_control_valid_data.auto_control_num[i]=Temperature_control_valid_data.auto_control_num[j];
				Temperature_control_valid_data.auto_control_num[j]=temp;
			}

		}

	}

}

/******************************************************************************************
**���ƣ����¿���������ֺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_tempercontrol_reg_output(void)
{
	if(get_CPU()==CPU_B)//B��
	{
		if(CPU_B_receive_data.is_B_get_power==FALSE)
		{
			return;//B������δ��Ȩ
		}
		
	}
	
	*(volatile uint32 *)TEMCONTROL_REG0=Write_16_to_32(Temperature_control_reg[0]);
	*(volatile uint32 *)TEMCONTROL_REG1=Write_16_to_32(Temperature_control_reg[1]);
	*(volatile uint32 *)TEMCONTROL_REG2=Write_16_to_32(Temperature_control_reg[2]);
	*(volatile uint32 *)TEMCONTROL_REG3=Write_16_to_32(Temperature_control_reg[3]);
	*(volatile uint32 *)TEMCONTROL_REG4=Write_16_to_32(Temperature_control_reg[4]);
	*(volatile uint32 *)TEMCONTROL_REG5=Write_16_to_32(Temperature_control_reg[5]);
	*(volatile uint32 *)TEMCONTROL_REG6=Write_16_to_32(Temperature_control_reg[6]);
	*(volatile uint32 *)TEMCONTROL_REG7=Write_16_to_32(Temperature_control_reg[7]);

	asm("nop;");
	TGTHT510_tempercontrol_reg_clear();
	
}

/******************************************************************************************
**���ƣ����¿�������λ�ֺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**����������numΪ���»�·�ţ�typeΪ��·���߱�·����������·
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_tempercontrol_reg_setbit(uint16 num,uint16 type)
{
	uint16 i;
	
	if(type==HEATER_MAIN)
	{
		i=Tempercontrol_word_byte[2*num];
		
		Temperature_control_reg[i]=Temperature_control_reg[i]|Tempercontrol_word_bit[2*num];
	}
	
	else if(type==HEATER_LESS)
	{
		i=Tempercontrol_word_byte[2*num+1];
		
		Temperature_control_reg[i]=Temperature_control_reg[i]|Tempercontrol_word_bit[2*num+1];
		
	}
	
	else if(type==HEATER_BOTH)
	{
		i=Tempercontrol_word_byte[2*num];
		
		Temperature_control_reg[i]=Temperature_control_reg[i]|Tempercontrol_word_bit[2*num];
		
		i=Tempercontrol_word_byte[2*num+1];
		
		Temperature_control_reg[i]=Temperature_control_reg[i]|Tempercontrol_word_bit[2*num+1];
		
	}
	
	else
	{
		asm("nop;");
	}

}

/******************************************************************************************
**���ƣ����¿���������ֺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**����������numΪ���»�·�ţ�typeΪ��·���߱�·����������·
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_tempercontrol_reg_clear(void)
{
	uint16 i;
	
	for(i=0;i<=7;i++)
	{
		Temperature_control_reg[i]=0x0000;
	}
	
	
}

/******************************************************************************************
**���ƣ����¹��Ĳ�ѯ�ֺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**����������numΪ���»�·�ţ�typeΪ��·���߱�·����������·
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_tempercontrol_power_calculate(uint16 num,uint16 type)
{
	uint16 power;
	
	power=0;
	
	if(num<=49)
	{
		if(type==HEATER_MAIN)//������·����
		{
			power=Tempercontrol_Power[2*num];
			
		}
		
		else if(type==HEATER_LESS)//���㱸·����
		{
			power=Tempercontrol_Power[2*num+1];
			
		}
		
		else if(type==HEATER_BOTH)//������·�뱸·����
		{
			power=Tempercontrol_Power[2*num];
			
			power=power+Tempercontrol_Power[2*num+1];
			
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
	
	
	return power;
	
}



/******************************************************************************************
**���ƣ�9sʱ���־��ѯ�ֺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**����������numΪ���»�·�ţ�typeΪ��·���߱�·����������·
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/


uint16 TGTHT510_tempercontrol_9s_flag(void)
{
	uint16 flag;
	
	if(Time_flag.time_9s_flag==TRUE)//9s��ʱʱ���־��Ч
	{
		flag=TRUE;
		Time_flag.time_9s_flag=FALSE;
		
	}
	
	else
	{
		flag=FALSE;
	}
	
	
	return flag;
	
}



/******************************************************************************************
**���ƣ�����������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_tempercontrol_main(void)
{
	uint16 fixed_control_state;	
	uint16 power;
	uint16 fixed_control_power;//����̶�ռ�ձ�������ĵĹ���
	uint16 auto_control_power;//�����Զ�����������ĵĹ���
	
	uint16 i;
	uint16 t[26];
	
	t[0]=TGTHT510_tempercontrol_pt_to_mf61(0x04e7);
	t[1]=TGTHT510_tempercontrol_pt_to_mf61(0x04e8);
	t[2]=TGTHT510_tempercontrol_pt_to_mf61(0x04e9);
	t[3]=TGTHT510_tempercontrol_pt_to_mf61(0x04ea);
	t[4]=TGTHT510_tempercontrol_pt_to_mf61(0x04eb);
	t[5]=TGTHT510_tempercontrol_pt_to_mf61(0x04ec);
	t[6]=TGTHT510_tempercontrol_pt_to_mf61(0x04ed);
	t[7]=TGTHT510_tempercontrol_pt_to_mf61(0x04ee);
	t[8]=TGTHT510_tempercontrol_pt_to_mf61(0x04ef);
	t[9]=TGTHT510_tempercontrol_pt_to_mf61(0x04f0);
	t[10]=TGTHT510_tempercontrol_pt_to_mf61(0x04f1);
	t[11]=TGTHT510_tempercontrol_pt_to_mf61(0x04f2);
	t[12]=TGTHT510_tempercontrol_pt_to_mf61(0x04f3);
	t[13]=TGTHT510_tempercontrol_pt_to_mf61(0x04f4);
	t[14]=TGTHT510_tempercontrol_pt_to_mf61(0x04f5);
	t[15]=TGTHT510_tempercontrol_pt_to_mf61(0x04f6);
	t[16]=TGTHT510_tempercontrol_pt_to_mf61(0x04f7);
	t[17]=TGTHT510_tempercontrol_pt_to_mf61(0x04f8);
	t[18]=TGTHT510_tempercontrol_pt_to_mf61(0x04f9);
	t[19]=TGTHT510_tempercontrol_pt_to_mf61(0x04fa);
	t[20]=TGTHT510_tempercontrol_pt_to_mf61(0x04fb);
	t[21]=TGTHT510_tempercontrol_pt_to_mf61(0x04fc);
	t[22]=TGTHT510_tempercontrol_pt_to_mf61(0x04fd);
	t[23]=TGTHT510_tempercontrol_pt_to_mf61(0x04fe);
	t[24]=TGTHT510_tempercontrol_pt_to_mf61(0x04ff);
	t[25]=TGTHT510_tempercontrol_pt_to_mf61(0x0500);
	
	/*
	t[0]=TGTHT510_tempercontrol_pt_to_mf61(0x04f0);
	t[1]=TGTHT510_tempercontrol_pt_to_mf61(0x0500);
	t[2]=TGTHT510_tempercontrol_pt_to_mf61(0x0510);
	t[3]=TGTHT510_tempercontrol_pt_to_mf61(0x0520);
	t[4]=TGTHT510_tempercontrol_pt_to_mf61(0x0530);
	t[5]=TGTHT510_tempercontrol_pt_to_mf61(0x0540);
	t[6]=TGTHT510_tempercontrol_pt_to_mf61(0x0550);
	t[7]=TGTHT510_tempercontrol_pt_to_mf61(0x0560);
	t[8]=TGTHT510_tempercontrol_pt_to_mf61(0x0570);
	t[9]=TGTHT510_tempercontrol_pt_to_mf61(0x0580);
	t[10]=TGTHT510_tempercontrol_pt_to_mf61(0x0590);
	*/
	
//-------------------------------�������----------------------------------------	
	//TGTHT510_test_TGTHT100_Temper();

//-------------------------------�������----------------------------------------

	
	fixed_control_power=0;
	auto_control_power=0;

	if(TGTHT510_tempercontrol_9s_flag()==TRUE)//9s��ʱʱ�䵽
	{
		//TGTHT510_tempercontrol_reg_output();
		
		TGTHT510_tempercontrol_valid_data_generate(Temperature_control_global.source);//���ɿ�����Ч����
		
		fixed_control_state=TGTHT510_tempercontrol_fixed_control_count_update();//�̶�ռ�ر��������������
		
		power=Temperature_control_global.total_power;//�����ܹ���
		
		fixed_control_power=TGTHT510_tempercontrol_fixed_control(power);//�̶�ռ�ձȻ�·��λ�����ع̶�ռ�ձ����Ĺ���
		
		if(fixed_control_power<power)
		{
			auto_control_power=TGTHT510_tempercontrol_auto_control(power-fixed_control_power);//�Զ����»�·��λ�������Զ��������Ĺ���
		}
		
		CG_tempercontrol_power=fixed_control_power+auto_control_power;//�����ܹ��ģ���Ϊ����ң�����
		
		TGTHT510_tempercontrol_reg_output();//��������������ź�
		
		

	}
	
	else//9s��ʱʱ��δ��
	{
		
		fixed_control_state=TGTHT510_tempercontrol_fixed_control_count_update();//�̶�ռ�ر��������������
		
		if(fixed_control_state==FIXED_UPDATE)//�������й̶�ռ�ȱ����������������Զ����µ���
		{
			fixed_control_state=FIXED_NO_UPDATE;
			
			power=Temperature_control_global.total_power;//�����ܹ���
			
			fixed_control_power=TGTHT510_tempercontrol_fixed_control(power);//�̶�ռ�ձȻ�·��λ�����ع̶�ռ�ձ����Ĺ���
			
			if(fixed_control_power<power)
			{
				auto_control_power=TGTHT510_tempercontrol_auto_control(power-fixed_control_power);//�Զ����»�·��λ�������Զ��������Ĺ���
			}
			
			CG_tempercontrol_power=fixed_control_power+auto_control_power;//�����ܹ��ģ���Ϊ����ң�����
			
			TGTHT510_tempercontrol_reg_output();//��������������ź�
		}
		
		else//�������޹̶�ռ�ȱ��������
		{
			asm("nop;");
		}
		

	}
	
}

/******************************************************************************************
**���ƣ��̶�ռ�ձ�����������·ֺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**����������ĳ���»�·ռ�ձȼ����������ڸ���Ϊ�㣬�򷵻�FIXED_UPDATE�����򷵻�FIXED_NO_UPDATE
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_tempercontrol_fixed_control_count_update(void)
{
	uint16 state;
	uint16 i;
	
	state=FIXED_NO_UPDATE;
	
	if(Temperature_control_valid_data.fixed_control_count>=1)
	{
		for(i=0;i<=Temperature_control_valid_data.fixed_control_count-1;i++)
		{
			if(Temperature_control_valid_data.fixed_control_data[i]>=1)
			{
				Temperature_control_valid_data.fixed_control_data[i]--;
				if(Temperature_control_valid_data.fixed_control_data[i]==0)
				{
					state=FIXED_UPDATE;
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
		
		
	}
	
	else
	{
		asm("nop;");
	}
	
	return state;
	
}

/******************************************************************************************
**���ƣ��̶�ռ�ձ�������Ʒֺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**�������������ƹ��ģ�����ʵ����ĵĹ���
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_tempercontrol_fixed_control(uint16 max_power)
{
	uint16 i;
	uint16 power;
	uint16 temp_power;
	uint16 num;
	
	power=0;//ʵ�����ĵĹ��ĳ�ʼ��Ϊ��
	temp_power=0;//ʵ�����Ĺ�����ʱ�洢
	
	if(Temperature_control_valid_data.fixed_control_count>=1)//ռ�ձ����·����Ϊ��
	{
		for(i=0;i<=Temperature_control_valid_data.fixed_control_count-1;i++)
		{
			if(Temperature_control_valid_data.fixed_control_data[i]>=1)//ռ�ձȼ�����Ϊ��
			{
				num=Temperature_control_valid_data.fixed_control_num[i];//���»�··��
				
				temp_power=temp_power+TGTHT510_tempercontrol_power_calculate(num,HEATER_BOTH);//������·�뱸·����
				
				if(temp_power>max_power)//������
				{
					return power;
				}
				
				else//δ������
				{
					power=temp_power;
					
					TGTHT510_tempercontrol_reg_setbit(num,HEATER_BOTH);//����������λ��λ
				}

			}
			
			else
			{
				asm("nop;");
			}
			
		}

	}
	
	else
	{
		asm("nop;");
	}
	
	return power;

}


/******************************************************************************************
**���ƣ��Զ�����������Ʒֺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**�������������ƹ��ģ�����ʵ����ĵĹ���
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_tempercontrol_auto_control(uint16 max_power)
{
	uint16 i;
	uint16 power;
	uint16 temp_power;
	uint16 num;
	uint16 temper;
	uint16 range;
	
	uint16 last_state_main[50];//��ʱ��¼�����ڿ��»�·��·������״̬��ENABLE����DISABLE
	uint16 last_state_less[50];//��ʱ��¼�����ڿ��»�·��·������״̬��ENABLE����DISABLE
	
	for(i=0;i<=49;i++)
	{
		last_state_main[i]=DISABLE;
		last_state_less[i]=DISABLE;
		
	}
	
	power=0;//ʵ�����ĵĹ��ĳ�ʼ��Ϊ��
	temp_power=0;//ʵ�����Ĺ�����ʱ�洢
	
	if(Temperature_control_valid_data.auto_control_count>=1)
	{
		for(i=0;i<=Temperature_control_valid_data.auto_control_count-1;i++)
		{
			num=Temperature_control_valid_data.auto_control_num[i];//���»�··��
			
			temper=Temperature_control_valid_data.auto_control_data[i];//���»�·�����¶�ֵ
			
			range=TGTHT510_tempercontrol_auto_control_temper_range(num,temper);//�����¶�ֵ�ڿ��µ�����䷶Χ
			
			switch(range)
			{
				case TEMP_RANGE_LESS_T1://�¶ȵ��ڿ��µ�T1���򹦺���������£�������·����
				{
					
					/*�����Ƿ�����·������--------------------------------------------------------------*/
					
					temp_power=temp_power+TGTHT510_tempercontrol_power_calculate(num,HEATER_MAIN);//������·����
					
					if(temp_power>max_power)//���ĳ�����
					{
						for(i=0;i<=49;i++)
						{
							Temperature_control_valid_data.auto_control_last_state_main[i]=last_state_main[i];
							Temperature_control_valid_data.auto_control_last_state_less[i]=last_state_less[i];//���汾���Զ����¼�����״̬
						}
						
						return power;//����ʵ����ĵĹ���	
					}
					
					else//����δ������
					{
						power=temp_power;//���¹����ۼ�
						
						TGTHT510_tempercontrol_reg_setbit(num,HEATER_MAIN);//��·����������λ��λ
						
						last_state_main[num]=ENABLE;//���汾�μ���������״̬����	
					}
					
					
					/*�����Ƿ�����·������--------------------------------------------------------------*/
					
					temp_power=temp_power+TGTHT510_tempercontrol_power_calculate(num,HEATER_LESS);//���㱸·����
					
					if(temp_power>max_power)//���ĳ�����
					{
						for(i=0;i<=49;i++)
						{
							Temperature_control_valid_data.auto_control_last_state_main[i]=last_state_main[i];
							Temperature_control_valid_data.auto_control_last_state_less[i]=last_state_less[i];//���汾���Զ����¼�����״̬
						}
						
						return power;//����ʵ����ĵĹ���	
					}
					
					else//����δ������
					{
						power=temp_power;//���¹����ۼ�
						
						TGTHT510_tempercontrol_reg_setbit(num,HEATER_LESS);//��·����������λ��λ
						
						last_state_less[num]=ENABLE;//���汾�μ���������״̬����	
					}
					
					break;
				}
				
				case TEMP_RANGE_BETWEEN_T1_T2://�¶�λ�ڿ��µ�T1��T2֮�䣬��·�������򿪣���·�������������һ����״̬�����Ƿ��
				{
					
					/*�����Ƿ�����·������--------------------------------------------------------------*/
					
					temp_power=temp_power+TGTHT510_tempercontrol_power_calculate(num,HEATER_MAIN);//������·����
					
					if(temp_power>max_power)//���ĳ�����
					{
						for(i=0;i<=49;i++)
						{
							Temperature_control_valid_data.auto_control_last_state_main[i]=last_state_main[i];
							Temperature_control_valid_data.auto_control_last_state_less[i]=last_state_less[i];//���汾���Զ����¼�����״̬
						}
						
						return power;//����ʵ����ĵĹ���	
					}
					
					else//����δ������
					{
						power=temp_power;//���¹����ۼ�
						
						TGTHT510_tempercontrol_reg_setbit(num,HEATER_MAIN);//��·����������λ��λ
						
						last_state_main[num]=ENABLE;//���汾�μ���������״̬����	
					}
					
					/*�����Ƿ�����·������--------------------------------------------------------------*/
					
					if(Temperature_control_valid_data.auto_control_last_state_less[num]==ENABLE)//��һ���ڱ�·��������
					{
						
						temp_power=temp_power+TGTHT510_tempercontrol_power_calculate(num,HEATER_LESS);//���㱸·����
					
						if(temp_power>max_power)//���ĳ�����
						{
							for(i=0;i<=49;i++)
							{
								Temperature_control_valid_data.auto_control_last_state_main[i]=last_state_main[i];
								Temperature_control_valid_data.auto_control_last_state_less[i]=last_state_less[i];//���汾���Զ����¼�����״̬
							}
						
							return power;//����ʵ����ĵĹ���	
						}
					
						else//����δ������
						{
							power=temp_power;//���¹����ۼ�
						
							TGTHT510_tempercontrol_reg_setbit(num,HEATER_LESS);//��·����������λ��λ
						
							last_state_less[num]=ENABLE;//���汾�μ���������״̬����	
						}
	
					}
					
					else
					{
						asm("nop;");
					}
					
					break;
				}
				
				case TEMP_RANGE_BETWEEN_T2_T3://�¶�λ�ڿ��µ�T2��T3֮�䣬��·�������رգ���·�������������һ����״̬�����Ƿ��
				{
					
					/*�����Ƿ�����·������--------------------------------------------------------------*/
					
					if(Temperature_control_valid_data.auto_control_last_state_main[num]==ENABLE)//��һ������·��������
					{
						
						temp_power=temp_power+TGTHT510_tempercontrol_power_calculate(num,HEATER_MAIN);//������·����
					
						if(temp_power>max_power)//���ĳ�����
						{
							for(i=0;i<=49;i++)
							{
								Temperature_control_valid_data.auto_control_last_state_main[i]=last_state_main[i];
								Temperature_control_valid_data.auto_control_last_state_less[i]=last_state_less[i];//���汾���Զ����¼�����״̬
							}
						
							return power;//����ʵ����ĵĹ���	
						}
					
						else//����δ������
						{
							power=temp_power;//���¹����ۼ�
						
							TGTHT510_tempercontrol_reg_setbit(num,HEATER_MAIN);//��·����������λ��λ
						
							last_state_main[num]=ENABLE;//���汾�μ���������״̬����	
						}
	
					}
					
					else
					{
						asm("nop;");
					}

					break;
				}
				
				case TEMP_RANGE_MORE_T3://�¶ȴ��ڿ��µ�T3��������·���������ر�
				{
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
		}
		
	}
	
	else
	{
		asm("nop;");
	}
	
	
	for(i=0;i<=49;i++)
	{
		Temperature_control_valid_data.auto_control_last_state_main[i]=last_state_main[i];
		Temperature_control_valid_data.auto_control_last_state_less[i]=last_state_less[i];//���汾���Զ����¼�����״̬
	}
						
	return power;//����ʵ����ĵĹ���
	
	
}



/******************************************************************************************
**���ƣ��Զ������¶ȷ�Χ�ֺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������������»�··�ţ��Լ��¶�ֵ�������¶ȷ�Χ
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_tempercontrol_auto_control_temper_range(uint16 num,uint16 temper)
{
	uint16 T1,T2,T3;
	uint16 i;
	uint16 range;
	
	T1=Temperature_control_block[num].control_spot[0];
	T2=Temperature_control_block[num].control_spot[1];
	T3=Temperature_control_block[num].control_spot[2];
	
	if(temper>=T1)//�����¶�С�ڵ���T1
	{
		range=TEMP_RANGE_LESS_T1;
	}
	
	else if((temper<T1)&&(temper>=T2))//�����¶ȴ���T1��С�ڵ���T2
	{
		range=TEMP_RANGE_BETWEEN_T1_T2;
	}
	
	else if((temper<T2)&&(temper>=T3))//�����¶ȴ���T2��С�ڵ���T3
	{
		range=TEMP_RANGE_BETWEEN_T2_T3;
	}
	
	else//�����¶ȴ���T3
	{
		range=TEMP_RANGE_MORE_T3;
	}
	
	return range;
	
}


/******************************************************************************************
**���ƣ����ӹ�·�Զ�����ʹ�ܻ��߽�ֹ�ֺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_tempercontrol_supply_is_auto_control(uint16 mode)
{
	uint16 i;
	
	if(mode==ENABLE)
	{
		for(i=26;i<=37;i++)
		{
			Temperature_control_block[i].control_state=ENABLE;//����ϵͳ�Զ�����ʹ��
		}
		
		for(i=44;i<=49;i++)
		{
			Temperature_control_block[i].control_state=ENABLE;//����ϵͳ�Զ�����ʹ��
		}
		
	}
	
	else if(mode==DISABLE)
	{
		for(i=26;i<=37;i++)
		{
			Temperature_control_block[i].control_state=DISABLE;//����ϵͳ�Զ����½�ֹ
		}
		
		for(i=44;i<=49;i++)
		{
			Temperature_control_block[i].control_state=DISABLE;//����ϵͳ�Զ����½�ֹ
		}
		
	}
	
	else
	{
		asm("nop;");
	}

}

















