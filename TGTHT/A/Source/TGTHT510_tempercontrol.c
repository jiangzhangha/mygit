/**
  ******************************************************************************
  * @file    TGTHT510_tempercontrol.c
  * @author  蒋章
  * @version V1.00
  * @date    20150626
  * @brief   空间站核心舱推进管理器自动控温模块C文件
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"






/*全局变量---------------------------------------------------------------------*/		

Temperature_control_block_TypeDef Temperature_control_block[50];//共50路控温回路

Temperature_control_global_TypeDef Temperature_control_global;//温度控制全局变量

Temperature_control_valid_data_TypeDef Temperature_control_valid_data;//控温有效参数

uint16 Temperature_control_reg[8];//加热器控制寄存器

//-------------------------------调试---------------------------
//uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[65];
//uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[65];
//uint16 CG_tempercontrol_power;

extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[];				//全局数组，缓存推进遥测线路盒复帧A温度数据，65字
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[];				//全局数组，缓存推进遥测线路盒复帧B温度数据，65字

extern Time_flag_TypeDef Time_flag;//定时计数结构体

extern uint16 CG_tempercontrol_power; //热控功耗,常规遥测

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
										};//加热回路功耗

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
											};//加热回路置位掩码

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
MF51温度值与源码的对应查询表
数组下标减去50即为温度值，如下标为100，对应的源码即为100-50=50摄氏度对应点源码值
温度范围-50摄氏度至+70摄氏度

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
MF61温度值与源码的对应查询表
数组下标减去50即为温度值，如下标为100，对应的源码即为100-50=50摄氏度对应点源码值
温度范围-50摄氏度至+70摄氏度

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
铂电阻温度值与源码的对应查询表
数组下标减去50即为温度值，如下标为100，对应的源码即为100-50=50摄氏度对应点源码值
温度范围-50摄氏度至+70摄氏度

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
**名称：控温参数初始化函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_tempercontrol_initial(void)
{
	uint16 i;

/*温度控制块结构体初始化-----------------------------------------------------------------*/
	
	for(i=0;i<=49;i++)
	{
		if(((i>=26)&&(i<=37))||((i>=44)&&(i<=49)))
		{
			Temperature_control_block[i].control_state=DISABLE;//补加系统初始化，不参与自动控温
		}
		
		else
		{
			Temperature_control_block[i].control_state=ENABLE;//推进系统初始化，参与自动控温
		}
		
		Temperature_control_block[i].fixed_output_state=DISABLE;//控温回路初始化，无固定占空比输出
		
		Temperature_control_block[i].control_spot[0]=TEMPER_SPOT_T1;//控温点T1，初始值4摄氏度，MF61源码值
		Temperature_control_block[i].control_spot[1]=TEMPER_SPOT_T2;//控温点T2，初始值8摄氏度，MF61源码值
		Temperature_control_block[i].control_spot[2]=TEMPER_SPOT_T3;//控温点T3，初始值12摄氏度，MF61源码值
		
		Temperature_control_block[i].power[0]=Tempercontrol_Power[2*i];//主路加热回路功耗
		Temperature_control_block[i].power[1]=Tempercontrol_Power[2*i+1];//备路加热回路功耗
		
		Temperature_control_block[i].fixed_output_count=0x0000;//固定占控比输出计数器
		
		Temperature_control_block[i].source_data[0]=TCB_source_data0[i];
		Temperature_control_block[i].source_data[1]=TCB_source_data1[i];
		Temperature_control_block[i].source_data[2]=TCB_source_data2[i];
		Temperature_control_block[i].source_data[3]=TCB_source_data3[i];
		Temperature_control_block[i].source_data[4]=TCB_source_data4[i];
		Temperature_control_block[i].source_data[5]=TCB_source_data5[i];
		Temperature_control_block[i].source_data[6]=TCB_source_data6[i];//控温测点位置数据初始化
	
		Temperature_control_block[i].number=i;
	}
	
	
/*温度控制全局变量结构体初始化------------------------------------------------------------*/
	
	Temperature_control_global.source=SOURCE_DATA_TGTHT100;//控温使用遥测数据来源，初始化为推进遥测线路盒
	
	Temperature_control_global.data_state_TGTHT100=ENABLE;//遥测线路盒温度数据正常
	
	Temperature_control_global.data_state_KPU=ENABLE;//数管遥测数据正常
	
	Temperature_control_global.total_power=POWER_INITIAL;//总功耗限制300W

/*温度控制有效参数结构体初始化------------------------------------------------------------*/

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
	
/*加热器控制寄存器初始化---------------------------------------------------------------------*/	
	
	for(i=0;i<=7;i++)
	{
		Temperature_control_reg[i]=0x0000;
	}
	
	
}



/******************************************************************************************
**名称：MF51转换为MF61转换函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
		range=TGTHT510_tempercontrol_mf51_range_calculate(temp_mf51);//获取MF51温度的范围
		num=TGTHT510_tempercontrol_mf51_sourcecode_to_centigrade_calculate(temp_mf51,range);//获取MF51温度源码对应的摄氏度，即查询表下标
		mf61_temper=Tempercontrol_MF61_code[num];//根据摄氏度，查表得对应MF61的源码值
	}

	return mf61_temper;
}

/******************************************************************************************
**名称：MF51温度范围计算函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_tempercontrol_mf51_range_calculate(uint16 temp_mf51)
{
	uint16 range;
	
	if(temp_mf51>TEMP_MF51_NEG_50)//MF51温度范围，小于-50摄氏度
	{
		range=TEMP_MF51_RANGE_LARGER_POS_70;
		//range=TEMP_MF61_RANGE_SMALLER_NEG_50;
	}
	
	else if((temp_mf51<=TEMP_MF51_NEG_50)&&(temp_mf51>TEMP_MF51_NEG_40))//MF51温度范围，大于等于-50摄氏度，小于-40摄氏度
	{
		range=TEMP_MF51_RANGE_NEG_50_40;
	}
	
	else if((temp_mf51<=TEMP_MF51_NEG_40)&&(temp_mf51>TEMP_MF51_NEG_30))//MF51温度范围，大于等于-40摄氏度，小于-30摄氏度
	{
		range=TEMP_MF51_RANGE_NEG_40_30;
	}

	else if((temp_mf51<=TEMP_MF51_NEG_30)&&(temp_mf51>TEMP_MF51_NEG_20))//MF51温度范围，大于等于-30摄氏度，小于-20摄氏度
	{
		range=TEMP_MF51_RANGE_NEG_30_20;
	}
	
	else if((temp_mf51<=TEMP_MF51_NEG_20)&&(temp_mf51>TEMP_MF51_NEG_10))//MF51温度范围，大于等于-20摄氏度，小于-10摄氏度
	{
		range=TEMP_MF51_RANGE_NEG_20_10;
	}
	
	else if((temp_mf51<=TEMP_MF51_NEG_10)&&(temp_mf51>TEMP_MF51_MID_0))//MF51温度范围，大于等于-10摄氏度，小于0摄氏度
	{
		range=TEMP_MF51_RANGE_NEG_10_0;
	}
	
	else if((temp_mf51<=TEMP_MF51_MID_0)&&(temp_mf51>TEMP_MF51_POS_10))//MF51温度范围，大于等于0摄氏度，小于10摄氏度
	{
		range=TEMP_MF51_RANGE_POS_0_10;
	}
	
	else if((temp_mf51<=TEMP_MF51_POS_10)&&(temp_mf51>TEMP_MF51_POS_20))//MF51温度范围，大于等于10摄氏度，小于20摄氏度
	{
		range=TEMP_MF51_RANGE_POS_10_20;
	}
	
	else if((temp_mf51<=TEMP_MF51_POS_20)&&(temp_mf51>TEMP_MF51_POS_30))//MF51温度范围，大于等于20摄氏度，小于30摄氏度
	{
		range=TEMP_MF51_RANGE_POS_20_30;
	}
	
	else if((temp_mf51<=TEMP_MF51_POS_30)&&(temp_mf51>TEMP_MF51_POS_40))//MF51温度范围，大于等于30摄氏度，小于40摄氏度
	{
		range=TEMP_MF51_RANGE_POS_30_40;
	}
	
	else if((temp_mf51<=TEMP_MF51_POS_40)&&(temp_mf51>TEMP_MF51_POS_50))//MF51温度范围，大于等于40摄氏度，小于50摄氏度
	{
		range=TEMP_MF51_RANGE_POS_40_50;
	}
	
	else if((temp_mf51<=TEMP_MF51_POS_50)&&(temp_mf51>TEMP_MF51_POS_60))//MF51温度范围，大于等于50摄氏度，小于60摄氏度
	{
		range=TEMP_MF51_RANGE_POS_50_60;
	}
	
	else if((temp_mf51<=TEMP_MF51_POS_60)&&(temp_mf51>TEMP_MF51_POS_70))//MF51温度范围，大于等于60摄氏度，小于70摄氏度
	{
		range=TEMP_MF51_RANGE_POS_60_70;
	}
	
	else//MF51温度范围，大于等于70摄氏度
	{
		range=TEMP_MF51_RANGE_LARGER_POS_70;
	}
	
	return range;
	
}



/******************************************************************************************
**名称：MF51温度源码转换为摄氏度计算函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_tempercontrol_mf51_sourcecode_to_centigrade_calculate(uint16 temp_mf51,uint16 range)
{
	uint16 num;
	uint16 i;
	
	switch(range)
	{
		case TEMP_MF51_RANGE_SMALLER_NEG_50://MF51温度范围，小于-50摄氏度
		{
			num=0;
			break;
		}
		
		case TEMP_MF51_RANGE_NEG_50_40://MF51温度范围，大于等于-50摄氏度，小于-40摄氏度
		{
			i=TEMP_MF51_RANGE_NEG_50_40_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_NEG_40_30://MF51温度范围，大于等于-40摄氏度，小于-30摄氏度
		{
			i=TEMP_MF51_RANGE_NEG_40_30_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_NEG_30_20://MF51温度范围，大于等于-30摄氏度，小于-20摄氏度
		{
			i=TEMP_MF51_RANGE_NEG_30_20_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_NEG_20_10://MF51温度范围，大于等于-20摄氏度，小于-10摄氏度
		{
			i=TEMP_MF51_RANGE_NEG_20_10_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_NEG_10_0://MF51温度范围，大于等于-10摄氏度，小于0摄氏度
		{
			i=TEMP_MF51_RANGE_NEG_10_0_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_0_10://MF51温度范围，大于等于0摄氏度，小于10摄氏度
		{
			i=TEMP_MF51_RANGE_POS_0_10_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_10_20://MF51温度范围，大于等于10摄氏度，小于20摄氏度
		{
			i=TEMP_MF51_RANGE_POS_10_20_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_20_30://MF51温度范围，大于等于20摄氏度，小于30摄氏度
		{
			i=TEMP_MF51_RANGE_POS_20_30_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_30_40://MF51温度范围，大于等于30摄氏度，小于40摄氏度
		{
			i=TEMP_MF51_RANGE_POS_30_40_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_40_50://MF51温度范围，大于等于40摄氏度，小于50摄氏度
		{
			i=TEMP_MF51_RANGE_POS_40_50_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_50_60://MF51温度范围，大于等于50摄氏度，小于600摄氏度
		{
			i=TEMP_MF51_RANGE_POS_50_60_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_POS_60_70://MF51温度范围，大于等于60摄氏度，小于70摄氏度
		{
			i=TEMP_MF51_RANGE_POS_60_70_START_NUM;
			num=TGTHT510_tempercontrol_mf51_centigrade_num_calculate(i,temp_mf51);
			break;
		}
		
		case TEMP_MF51_RANGE_LARGER_POS_70://MF51温度范围，大于等于70摄氏度
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
**名称：MF51温度源码近似计算函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
**名称：铂电阻转换为MF61转换函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
		range=TGTHT510_tempercontrol_pt_range_calculate(temp_pt);//获取铂电阻温度的范围
		num=TGTHT510_tempercontrol_pt_sourcecode_to_centigrade_calculate(temp_pt,range);//获取铂电阻温度源码对应的摄氏度
		mf61_temper=Tempercontrol_MF61_code[num];//根据摄氏度，查表得对应MF61的源码值
	}
	
	return mf61_temper;

}


/******************************************************************************************
**名称：铂电阻温度范围计算函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_tempercontrol_pt_range_calculate(uint16 temp_pt)
{
	uint16 range;
	
	if(temp_pt<TEMP_PT_NEG_50)//铂电阻温度范围，小于-50摄氏度
	{
		range=TEMP_PT_RANGE_LARGER_POS_70;
		//range=TEMP_PT_RANGE_SMALLER_NEG_50;
		
	}
	
	else if((temp_pt>=TEMP_PT_NEG_50)&&(temp_pt<TEMP_PT_NEG_40))//铂电阻温度范围，大于等于-50摄氏度，小于-40摄氏度
	{
		range=TEMP_PT_RANGE_NEG_50_40;
		
	}
	
	else if((temp_pt>=TEMP_PT_NEG_40)&&(temp_pt<TEMP_PT_NEG_30))//铂电阻温度范围，大于等于-40摄氏度，小于-30摄氏度
	{
		range=TEMP_PT_RANGE_NEG_40_30;
	}
	
	else if((temp_pt>=TEMP_PT_NEG_30)&&(temp_pt<TEMP_PT_NEG_20))//铂电阻温度范围，大于等于-30摄氏度，小于-20摄氏度
	{
		range=TEMP_PT_RANGE_NEG_30_20;
	}
	
	else if((temp_pt>=TEMP_PT_NEG_20)&&(temp_pt<TEMP_PT_NEG_10))//铂电阻温度范围，大于等于-20摄氏度，小于-10摄氏度
	{
		range=TEMP_PT_RANGE_NEG_20_10;
		
	}
	
	else if((temp_pt>=TEMP_PT_NEG_10)&&(temp_pt<TEMP_PT_MID_0))//铂电阻温度范围，大于等于-10摄氏度，小于0摄氏度
	{
		range=TEMP_PT_RANGE_NEG_10_0;
		
	}
	
	else if((temp_pt>=TEMP_PT_MID_0)&&(temp_pt<TEMP_PT_POS_10))//铂电阻温度范围，大于等于0摄氏度，小于10摄氏度
	{
		range=TEMP_PT_RANGE_POS_0_10;
		
	}
	
	else if((temp_pt>=TEMP_PT_POS_10)&&(temp_pt<TEMP_PT_POS_20))//铂电阻温度范围，大于等于10摄氏度，小于20摄氏度
	{
		range=TEMP_PT_RANGE_POS_10_20;
		
	}
	
	else if((temp_pt>=TEMP_PT_POS_20)&&(temp_pt<TEMP_PT_POS_30))//铂电阻温度范围，大于等于20摄氏度，小于30摄氏度
	{
		range=TEMP_PT_RANGE_POS_20_30;
		
	}
	
	else if((temp_pt>=TEMP_PT_POS_30)&&(temp_pt<TEMP_PT_POS_40))//铂电阻温度范围，大于等于30摄氏度，小于40摄氏度
	{
		range=TEMP_PT_RANGE_POS_30_40;
		
	}
	
	else if((temp_pt>=TEMP_PT_POS_40)&&(temp_pt<TEMP_PT_POS_50))//铂电阻温度范围，大于等于40摄氏度，小于50摄氏度
	{
		range=TEMP_PT_RANGE_POS_40_50;
		
	}
	
	else if((temp_pt>=TEMP_PT_POS_50)&&(temp_pt<TEMP_PT_POS_60))//铂电阻温度范围，大于等于50摄氏度，小于60摄氏度
	{
		range=TEMP_PT_RANGE_POS_50_60;
		
	}
	
	else if((temp_pt>=TEMP_PT_POS_60)&&(temp_pt<TEMP_PT_POS_70))//铂电阻温度范围，大于等于60摄氏度，小于70摄氏度
	{
		range=TEMP_PT_RANGE_POS_60_70;
		
	}
	
	else//铂电阻温度范围，大于等于70摄氏度
	{
		range=TEMP_PT_RANGE_LARGER_POS_70;
		
	}
	
	return range;
	
	
}

/******************************************************************************************
**名称：铂电阻温度源码近似计算函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
**名称：铂电阻温度源码转换为摄氏度计算函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_tempercontrol_pt_sourcecode_to_centigrade_calculate(uint16 temp_pt,uint16 range)
{
	uint16 num;
	uint16 i;
	
	switch(range)
	{
		case TEMP_PT_RANGE_SMALLER_NEG_50://铂电阻温度范围，小于-50摄氏度
		{
			num=0;
			break;
		}
		
		case TEMP_PT_RANGE_NEG_50_40://铂电阻温度范围，大于等于-50摄氏度，小于-40摄氏度
		{
			i=TEMP_PT_RANGE_NEG_50_40_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_NEG_40_30://铂电阻温度范围，大于等于-40摄氏度，小于-30摄氏度
		{
			i=TEMP_PT_RANGE_NEG_40_30_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_NEG_30_20://铂电阻温度范围，大于等于-30摄氏度，小于-20摄氏度
		{
			i=TEMP_PT_RANGE_NEG_30_20_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_NEG_20_10://铂电阻温度范围，大于等于-20摄氏度，小于-10摄氏度
		{
			i=TEMP_PT_RANGE_NEG_20_10_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_NEG_10_0://铂电阻温度范围，大于等于-10摄氏度，小于0摄氏度
		{
			i=TEMP_PT_RANGE_NEG_10_0_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_0_10://铂电阻温度范围，大于等于0摄氏度，小于10摄氏度
		{
			i=TEMP_PT_RANGE_POS_0_10_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_10_20://铂电阻温度范围，大于等于10摄氏度，小于20摄氏度
		{
			i=TEMP_PT_RANGE_POS_10_20_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_20_30://铂电阻温度范围，大于等于20摄氏度，小于30摄氏度
		{
			i=TEMP_PT_RANGE_POS_20_30_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_30_40://铂电阻温度范围，大于等于30摄氏度，小于40摄氏度
		{
			i=TEMP_PT_RANGE_POS_30_40_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_40_50://铂电阻温度范围，大于等于40摄氏度，小于50摄氏度
		{
			i=TEMP_PT_RANGE_POS_40_50_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_50_60://铂电阻温度范围，大于等于50摄氏度，小于600摄氏度
		{
			i=TEMP_PT_RANGE_POS_50_60_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_POS_60_70://铂电阻温度范围，大于等于60摄氏度，小于70摄氏度
		{
			i=TEMP_PT_RANGE_POS_60_70_START_NUM;
			num=TGTHT510_tempercontrol_pt_centigrade_num_calculate(i,temp_pt);
			break;
		}
		
		case TEMP_PT_RANGE_LARGER_POS_70://铂电阻温度范围，大于等于70摄氏度
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
**名称：控温有效数据生成函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：输入type为SOURCE_DATA_TGTHT100，即为使用推进遥测线路盒
		输入type为SOURCE_DATA_KPU，即为数管
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/


void TGTHT510_tempercontrol_valid_data_generate(uint16 type)
{
	uint16 i;
	
	if(type==SOURCE_DATA_TGTHT100)//根据推进遥测线路盒温度数据生成控温有效数据
	{
		TGTHT510_tempercontrol_valid_data_from_TGTHT100();
		
	}
	
	else if(type==SOURCE_DATA_KPU)//根据数管温度数据生成控温有效数据
	{

/*------------------------------------待修改----------------------------------------------*/	
/*温度控制有效参数结构体初始化------------------------------------------------------------*/
		
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
**名称：推进遥测线路盒控温有效数据生成函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_tempercontrol_valid_data_from_TGTHT100(void)
{
	uint16 i;
	uint16 temp[7];
	
	Temperature_control_valid_data.fixed_control_count=0;//固定占空比输出回路数量清零
	Temperature_control_valid_data.auto_control_count=0;//自动控温回路数量清零
	
	for(i=0;i<=49;i++)
	{
		if(Temperature_control_block[i].control_state==ENABLE)//该控温回路参与控温
		{
			if(Temperature_control_block[i].fixed_output_state==ENABLE)//固定占空比输出
			{	
				TGTHT510_tempercontrol_valid_data_from_TGTHT100_fixed_control(i);//固定占空比有效数据
			}
			
			else//自动控温
			{
				TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control(i);//自动控温有效数据
			}

			
		}
		else
		{
			asm("nop;");
		}	
	}
	
	if(Temperature_control_valid_data.auto_control_count>=1)
	{
		TGTHT510_tempercontrol_valid_data_from_TGTHT100_sort();//需要对自动控温的参数Temperature_control_valid_data进行排序
	}
	
	else
	{
		asm("nop;");
	}
	
	
	
	
}



/******************************************************************************************
**名称：推进遥测线路盒控温有效数据生成函数之固定占空比输出有效数据
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
**名称：推进遥测线路盒控温有效数据生成函数之自动控温有效数据
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control(uint16 num)
{
	Temperature_control_temp_TypeDef a;
	uint16 i;
	uint16 r;
	
	a=TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control_source_data(num);//获得该控温回路的7个测点源码值，已经转换为MF61源码
	
	r=TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control_source_data_sort(a);//获取该控温回路的7个测点源码值，温度最低的源码值
	
	i=Temperature_control_valid_data.auto_control_count;
	
	Temperature_control_valid_data.auto_control_data[i]=r;//缓存温度最低的源码值
	
	Temperature_control_valid_data.auto_control_num[i]=Temperature_control_block[num].number;//缓存控温回路路号
	
	Temperature_control_valid_data.auto_control_count++;//控温回路计数更新

	
}



/******************************************************************************************
**名称：推进遥测线路盒控温有效数据生成函数之自动控温有效数据
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

Temperature_control_temp_TypeDef TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control_source_data(uint16 num)
{
	Temperature_control_temp_TypeDef d;//临时数组结构体数据
	uint16 i;
	uint16 m,j,k;
	
	for(i=0;i<=6;i++)
	{
		m=Temperature_control_block[num].source_data[i];//测点数据来源标识
		
		if(m==0xffff)//无测点，填充码
		{
			d.temp[i]=TEMP_MF61_POS_70;//填充为70摄氏度MF61源码值
		}
		
		else
		{
			if((m&0x3000)==0x1000)//来自遥测线路盒复帧A帧
			{
				if((m&0x0c00)==0x0000)//遥测帧字
				{
					if((m&0xc000)==0x0000)//传感器为MF51
					{
						j=TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff];
						d.temp[i]=TGTHT510_tempercontrol_mf51_to_mf61(j);	
					}
					
					else if((m&0xc000)==0x4000)//传感器为铂电阻
					{
						j=TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff];
						d.temp[i]=TGTHT510_tempercontrol_pt_to_mf61(j);
					}
					
					else if((m&0xc000)==0x8000)//传感器为MF61
					{
						d.temp[i]=TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff];
						if(d.temp[i]>=TEMP_MF61_NEG_50)//MF61温度低于-50摄氏度
						{
							d.temp[i]=TEMP_MF61_POS_70;
						}
					}
					
					else//来源标识错误
					{
						for(k=0;k<=6;k++)
						{
							d.temp[k]=TEMP_MF61_POS_70;//填充为70摄氏度MF61源码值
							return d;
						}
					}

				}
				
				else if((m&0x0c00)==0x0400)//遥测帧高字节
				{
					if((m&0xc000)==0x0000)//传感器为MF51
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff])&0xff00)>>4);
						d.temp[i]=TGTHT510_tempercontrol_mf51_to_mf61(j);
					}
					
					else if((m&0xc000)==0x4000)//传感器为铂电阻
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff])&0xff00)>>4);
						d.temp[i]=TGTHT510_tempercontrol_pt_to_mf61(j);
					}
					
					else if((m&0xc000)==0x8000)//传感器为MF61
					{
						d.temp[i]=(((TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff])&0xff00)>>4);
						if(d.temp[i]>=TEMP_MF61_NEG_50)//MF61温度低于-50摄氏度
						{
							d.temp[i]=TEMP_MF61_POS_70;
						}
					}
					
					else//来源标识错误
					{
						for(k=0;k<=6;k++)
						{
							d.temp[k]=TEMP_MF61_POS_70;//填充为70摄氏度MF61源码值
							return d;
						}
					}
					
				}
				
				else if((m&0x0c00)==0x0800)//遥测帧低字节
				{
					if((m&0xc000)==0x0000)//传感器为MF51
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff])&0x00ff)<<4);
						d.temp[i]=TGTHT510_tempercontrol_mf51_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x4000)//传感器为铂电阻
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff])&0x00ff)<<4);
						d.temp[i]=TGTHT510_tempercontrol_pt_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x8000)//传感器为MF61
					{
						d.temp[i]=(((TGTHT510_1553B_data_TGTHT100_Temper_A[m&0x00ff])&0x00ff)<<4);
						if(d.temp[i]>=TEMP_MF61_NEG_50)//MF61温度低于-50摄氏度
						{
							d.temp[i]=TEMP_MF61_POS_70;
						}
					}
					
					else//来源标识错误
					{
						for(k=0;k<=6;k++)
						{
							d.temp[k]=TEMP_MF61_POS_70;//填充为70摄氏度MF61源码值
							return d;
						}
					}
					
				}
				
				else//来源标识错误
				{
					for(k=0;k<=6;k++)
					{
						d.temp[k]=TEMP_MF61_POS_70;//填充为70摄氏度MF61源码值
						return d;
					}
					
				}

			}
			
			else if((m&0x3000)==0x2000)//来自遥测线路盒复帧B帧
			{
				if((m&0x0c00)==0x0000)//遥测帧字
				{
					if((m&0xc000)==0x0000)//传感器为MF51
					{
						j=TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff];
						d.temp[i]=TGTHT510_tempercontrol_mf51_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x4000)//传感器为铂电阻
					{
						j=TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff];
						d.temp[i]=TGTHT510_tempercontrol_pt_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x8000)//传感器为MF61
					{
						d.temp[i]=TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff];
						if(d.temp[i]>=TEMP_MF61_NEG_50)//MF61温度低于-50摄氏度
						{
							d.temp[i]=TEMP_MF61_POS_70;
						}
						
					}
					
					else//来源标识错误
					{
						for(k=0;k<=6;k++)
						{
							d.temp[k]=TEMP_MF61_POS_70;//填充为70摄氏度MF61源码值
							return d;
						}
						
					}
					
				}
				
				else if((m&0x0c00)==0x0400)//遥测帧高字节
				{
					if((m&0xc000)==0x0000)//传感器为MF51
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff])&0xff00)>>4);
						d.temp[i]=TGTHT510_tempercontrol_mf51_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x4000)//传感器为铂电阻
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff])&0xff00)>>4);
						d.temp[i]=TGTHT510_tempercontrol_pt_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x8000)//传感器为MF61
					{
						d.temp[i]=(((TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff])&0xff00)>>4);
						if(d.temp[i]>=TEMP_MF61_NEG_50)//MF61温度低于-50摄氏度
						{
							d.temp[i]=TEMP_MF61_POS_70;
						}
						
					}
					
					else//来源标识错误
					{
						for(k=0;k<=6;k++)
						{
							d.temp[k]=TEMP_MF61_POS_70;//填充为70摄氏度MF61源码值
							return d;
						}
						
					}
					
				}
				
				else if((m&0x0c00)==0x0800)//遥测帧低字节
				{
					if((m&0xc000)==0x0000)//传感器为MF51
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff])&0x00ff)<<4);
						d.temp[i]=TGTHT510_tempercontrol_mf51_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x4000)//传感器为铂电阻
					{
						j=(((TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff])&0x00ff)<<4);
						d.temp[i]=TGTHT510_tempercontrol_pt_to_mf61(j);
						
					}
					
					else if((m&0xc000)==0x8000)//传感器为MF61
					{
						d.temp[i]=(((TGTHT510_1553B_data_TGTHT100_Temper_B[m&0x00ff])&0x00ff)<<4);
						if(d.temp[i]>=TEMP_MF61_NEG_50)//MF61温度低于-50摄氏度
						{
							d.temp[i]=TEMP_MF61_POS_70;
						}
						
					}
					
					else//来源标识错误
					{
						for(k=0;k<=6;k++)
						{
							d.temp[k]=TEMP_MF61_POS_70;//填充为70摄氏度MF61源码值
							return d;
						}
						
					}
					
				}
				
				else//来源标识错误
				{
					for(k=0;k<=6;k++)
					{
						d.temp[k]=TEMP_MF61_POS_70;//填充为70摄氏度MF61源码值
						return d;
					}
					
				}
				
			}
			
			else//来源标识错误
			{
				for(k=0;k<=6;k++)
				{
					d.temp[k]=TEMP_MF61_POS_70;//填充为70摄氏度MF61源码值
					return d;
				}
	
			}

		}

	}
	
	return d;
}


/******************************************************************************************
**名称：推进遥测线路盒控温有效数据生成函数之自动控温有效数据排序
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：根据输入的7个数据，数据已经转换为MF61的源码值，需挑出温度最低的源码值，即对应源码数值最大
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
**名称：自动控温的参数Temperature_control_valid_data进行排序
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：根据输入的7个数据，数据已经转换为MF61的源码值，需挑出温度最低的源码值，即对应源码数值最大
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
**名称：控温控制字输出分函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_tempercontrol_reg_output(void)
{
	if(get_CPU()==CPU_B)//B机
	{
		if(CPU_B_receive_data.is_B_get_power==FALSE)
		{
			return;//B机，且未夺权
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
**名称：控温控制字置位分函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：输入num为控温回路号，type为主路或者备路，或者主备路
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
**名称：控温控制字清零分函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：输入num为控温回路号，type为主路或者备路，或者主备路
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
**名称：控温功耗查询分函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：输入num为控温回路号，type为主路或者备路，或者主备路
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_tempercontrol_power_calculate(uint16 num,uint16 type)
{
	uint16 power;
	
	power=0;
	
	if(num<=49)
	{
		if(type==HEATER_MAIN)//计算主路功耗
		{
			power=Tempercontrol_Power[2*num];
			
		}
		
		else if(type==HEATER_LESS)//计算备路功耗
		{
			power=Tempercontrol_Power[2*num+1];
			
		}
		
		else if(type==HEATER_BOTH)//计算主路与备路功耗
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
**名称：9s时间标志查询分函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：输入num为控温回路号，type为主路或者备路，或者主备路
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/


uint16 TGTHT510_tempercontrol_9s_flag(void)
{
	uint16 flag;
	
	if(Time_flag.time_9s_flag==TRUE)//9s定时时间标志有效
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
**名称：控温主函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_tempercontrol_main(void)
{
	uint16 fixed_control_state;	
	uint16 power;
	uint16 fixed_control_power;//缓存固定占空比输出消耗的功耗
	uint16 auto_control_power;//缓存自动控温输出消耗的功耗
	
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
	
//-------------------------------测试语句----------------------------------------	
	//TGTHT510_test_TGTHT100_Temper();

//-------------------------------测试语句----------------------------------------

	
	fixed_control_power=0;
	auto_control_power=0;

	if(TGTHT510_tempercontrol_9s_flag()==TRUE)//9s定时时间到
	{
		//TGTHT510_tempercontrol_reg_output();
		
		TGTHT510_tempercontrol_valid_data_generate(Temperature_control_global.source);//生成控温有效参数
		
		fixed_control_state=TGTHT510_tempercontrol_fixed_control_count_update();//固定占控比输出计数器更新
		
		power=Temperature_control_global.total_power;//限制总功耗
		
		fixed_control_power=TGTHT510_tempercontrol_fixed_control(power);//固定占空比回路置位，返回固定占空比消耗功耗
		
		if(fixed_control_power<power)
		{
			auto_control_power=TGTHT510_tempercontrol_auto_control(power-fixed_control_power);//自动控温回路置位，返回自动控温消耗功耗
		}
		
		CG_tempercontrol_power=fixed_control_power+auto_control_power;//消耗总功耗，作为常规遥测参数
		
		TGTHT510_tempercontrol_reg_output();//输出加热器控制信号
		
		

	}
	
	else//9s定时时间未到
	{
		
		fixed_control_state=TGTHT510_tempercontrol_fixed_control_count_update();//固定占控比输出计数器更新
		
		if(fixed_control_state==FIXED_UPDATE)//本周期有固定占比比输出结束，需进行自动控温调整
		{
			fixed_control_state=FIXED_NO_UPDATE;
			
			power=Temperature_control_global.total_power;//限制总功耗
			
			fixed_control_power=TGTHT510_tempercontrol_fixed_control(power);//固定占空比回路置位，返回固定占空比消耗功耗
			
			if(fixed_control_power<power)
			{
				auto_control_power=TGTHT510_tempercontrol_auto_control(power-fixed_control_power);//自动控温回路置位，返回自动控温消耗功耗
			}
			
			CG_tempercontrol_power=fixed_control_power+auto_control_power;//消耗总功耗，作为常规遥测参数
			
			TGTHT510_tempercontrol_reg_output();//输出加热器控制信号
		}
		
		else//本周期无固定占比比输出结束
		{
			asm("nop;");
		}
		

	}
	
}

/******************************************************************************************
**名称：固定占空比输出计数更新分函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：若有某控温回路占空比计数，此周期更新为零，则返回FIXED_UPDATE，否则返回FIXED_NO_UPDATE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
**名称：固定占空比输出控制分函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：输入限制功耗，返回实际损耗的功耗
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_tempercontrol_fixed_control(uint16 max_power)
{
	uint16 i;
	uint16 power;
	uint16 temp_power;
	uint16 num;
	
	power=0;//实际消耗的功耗初始化为零
	temp_power=0;//实际消耗功耗临时存储
	
	if(Temperature_control_valid_data.fixed_control_count>=1)//占空比输出路数不为零
	{
		for(i=0;i<=Temperature_control_valid_data.fixed_control_count-1;i++)
		{
			if(Temperature_control_valid_data.fixed_control_data[i]>=1)//占空比计数不为零
			{
				num=Temperature_control_valid_data.fixed_control_num[i];//控温回路路数
				
				temp_power=temp_power+TGTHT510_tempercontrol_power_calculate(num,HEATER_BOTH);//计算主路与备路功耗
				
				if(temp_power>max_power)//超功耗
				{
					return power;
				}
				
				else//未超功耗
				{
					power=temp_power;
					
					TGTHT510_tempercontrol_reg_setbit(num,HEATER_BOTH);//加热器控制位置位
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
**名称：自动控温输出控制分函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：输入限制功耗，返回实际损耗的功耗
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_tempercontrol_auto_control(uint16 max_power)
{
	uint16 i;
	uint16 power;
	uint16 temp_power;
	uint16 num;
	uint16 temper;
	uint16 range;
	
	uint16 last_state_main[50];//临时记录本周期控温回路主路加热器状态，ENABLE或者DISABLE
	uint16 last_state_less[50];//临时记录本周期控温回路备路加热器状态，ENABLE或者DISABLE
	
	for(i=0;i<=49;i++)
	{
		last_state_main[i]=DISABLE;
		last_state_less[i]=DISABLE;
		
	}
	
	power=0;//实际消耗的功耗初始化为零
	temp_power=0;//实际消耗功耗临时存储
	
	if(Temperature_control_valid_data.auto_control_count>=1)
	{
		for(i=0;i<=Temperature_control_valid_data.auto_control_count-1;i++)
		{
			num=Temperature_control_valid_data.auto_control_num[i];//控温回路路数
			
			temper=Temperature_control_valid_data.auto_control_data[i];//控温回路控温温度值
			
			range=TGTHT510_tempercontrol_auto_control_temper_range(num,temper);//计算温度值在控温点的区间范围
			
			switch(range)
			{
				case TEMP_RANGE_LESS_T1://温度低于控温点T1，则功耗允许情况下，主、备路均开
				{
					
					/*计算是否开启主路加热器--------------------------------------------------------------*/
					
					temp_power=temp_power+TGTHT510_tempercontrol_power_calculate(num,HEATER_MAIN);//计算主路功耗
					
					if(temp_power>max_power)//功耗超限制
					{
						for(i=0;i<=49;i++)
						{
							Temperature_control_valid_data.auto_control_last_state_main[i]=last_state_main[i];
							Temperature_control_valid_data.auto_control_last_state_less[i]=last_state_less[i];//缓存本次自动控温加热器状态
						}
						
						return power;//返回实际损耗的功耗	
					}
					
					else//功耗未超限制
					{
						power=temp_power;//更新功耗累计
						
						TGTHT510_tempercontrol_reg_setbit(num,HEATER_MAIN);//主路加热器控制位置位
						
						last_state_main[num]=ENABLE;//缓存本次加热器开关状态数据	
					}
					
					
					/*计算是否开启备路加热器--------------------------------------------------------------*/
					
					temp_power=temp_power+TGTHT510_tempercontrol_power_calculate(num,HEATER_LESS);//计算备路功耗
					
					if(temp_power>max_power)//功耗超限制
					{
						for(i=0;i<=49;i++)
						{
							Temperature_control_valid_data.auto_control_last_state_main[i]=last_state_main[i];
							Temperature_control_valid_data.auto_control_last_state_less[i]=last_state_less[i];//缓存本次自动控温加热器状态
						}
						
						return power;//返回实际损耗的功耗	
					}
					
					else//功耗未超限制
					{
						power=temp_power;//更新功耗累计
						
						TGTHT510_tempercontrol_reg_setbit(num,HEATER_LESS);//备路加热器控制位置位
						
						last_state_less[num]=ENABLE;//缓存本次加热器开关状态数据	
					}
					
					break;
				}
				
				case TEMP_RANGE_BETWEEN_T1_T2://温度位于控温点T1与T2之间，主路加热器打开，备路加热器需根据上一周期状态决定是否打开
				{
					
					/*计算是否开启主路加热器--------------------------------------------------------------*/
					
					temp_power=temp_power+TGTHT510_tempercontrol_power_calculate(num,HEATER_MAIN);//计算主路功耗
					
					if(temp_power>max_power)//功耗超限制
					{
						for(i=0;i<=49;i++)
						{
							Temperature_control_valid_data.auto_control_last_state_main[i]=last_state_main[i];
							Temperature_control_valid_data.auto_control_last_state_less[i]=last_state_less[i];//缓存本次自动控温加热器状态
						}
						
						return power;//返回实际损耗的功耗	
					}
					
					else//功耗未超限制
					{
						power=temp_power;//更新功耗累计
						
						TGTHT510_tempercontrol_reg_setbit(num,HEATER_MAIN);//主路加热器控制位置位
						
						last_state_main[num]=ENABLE;//缓存本次加热器开关状态数据	
					}
					
					/*计算是否开启备路加热器--------------------------------------------------------------*/
					
					if(Temperature_control_valid_data.auto_control_last_state_less[num]==ENABLE)//上一周期备路加热器打开
					{
						
						temp_power=temp_power+TGTHT510_tempercontrol_power_calculate(num,HEATER_LESS);//计算备路功耗
					
						if(temp_power>max_power)//功耗超限制
						{
							for(i=0;i<=49;i++)
							{
								Temperature_control_valid_data.auto_control_last_state_main[i]=last_state_main[i];
								Temperature_control_valid_data.auto_control_last_state_less[i]=last_state_less[i];//缓存本次自动控温加热器状态
							}
						
							return power;//返回实际损耗的功耗	
						}
					
						else//功耗未超限制
						{
							power=temp_power;//更新功耗累计
						
							TGTHT510_tempercontrol_reg_setbit(num,HEATER_LESS);//备路加热器控制位置位
						
							last_state_less[num]=ENABLE;//缓存本次加热器开关状态数据	
						}
	
					}
					
					else
					{
						asm("nop;");
					}
					
					break;
				}
				
				case TEMP_RANGE_BETWEEN_T2_T3://温度位于控温点T2与T3之间，备路加热器关闭，主路加热器需根据上一周期状态决定是否打开
				{
					
					/*计算是否开启主路加热器--------------------------------------------------------------*/
					
					if(Temperature_control_valid_data.auto_control_last_state_main[num]==ENABLE)//上一周期主路加热器打开
					{
						
						temp_power=temp_power+TGTHT510_tempercontrol_power_calculate(num,HEATER_MAIN);//计算主路功耗
					
						if(temp_power>max_power)//功耗超限制
						{
							for(i=0;i<=49;i++)
							{
								Temperature_control_valid_data.auto_control_last_state_main[i]=last_state_main[i];
								Temperature_control_valid_data.auto_control_last_state_less[i]=last_state_less[i];//缓存本次自动控温加热器状态
							}
						
							return power;//返回实际损耗的功耗	
						}
					
						else//功耗未超限制
						{
							power=temp_power;//更新功耗累计
						
							TGTHT510_tempercontrol_reg_setbit(num,HEATER_MAIN);//主路加热器控制位置位
						
							last_state_main[num]=ENABLE;//缓存本次加热器开关状态数据	
						}
	
					}
					
					else
					{
						asm("nop;");
					}

					break;
				}
				
				case TEMP_RANGE_MORE_T3://温度大于控温点T3，主、备路加热器均关闭
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
		Temperature_control_valid_data.auto_control_last_state_less[i]=last_state_less[i];//缓存本次自动控温加热器状态
	}
						
	return power;//返回实际损耗的功耗
	
	
}



/******************************************************************************************
**名称：自动控温温度范围分函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：输入控温回路路号，以及温度值，返回温度范围
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_tempercontrol_auto_control_temper_range(uint16 num,uint16 temper)
{
	uint16 T1,T2,T3;
	uint16 i;
	uint16 range;
	
	T1=Temperature_control_block[num].control_spot[0];
	T2=Temperature_control_block[num].control_spot[1];
	T3=Temperature_control_block[num].control_spot[2];
	
	if(temper>=T1)//输入温度小于等于T1
	{
		range=TEMP_RANGE_LESS_T1;
	}
	
	else if((temper<T1)&&(temper>=T2))//输入温度大于T1，小于等于T2
	{
		range=TEMP_RANGE_BETWEEN_T1_T2;
	}
	
	else if((temper<T2)&&(temper>=T3))//输入温度大于T2，小于等于T3
	{
		range=TEMP_RANGE_BETWEEN_T2_T3;
	}
	
	else//输入温度大于T3
	{
		range=TEMP_RANGE_MORE_T3;
	}
	
	return range;
	
}


/******************************************************************************************
**名称：补加管路自动控温使能或者禁止分函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_tempercontrol_supply_is_auto_control(uint16 mode)
{
	uint16 i;
	
	if(mode==ENABLE)
	{
		for(i=26;i<=37;i++)
		{
			Temperature_control_block[i].control_state=ENABLE;//补加系统自动控温使能
		}
		
		for(i=44;i<=49;i++)
		{
			Temperature_control_block[i].control_state=ENABLE;//补加系统自动控温使能
		}
		
	}
	
	else if(mode==DISABLE)
	{
		for(i=26;i<=37;i++)
		{
			Temperature_control_block[i].control_state=DISABLE;//补加系统自动控温禁止
		}
		
		for(i=44;i<=49;i++)
		{
			Temperature_control_block[i].control_state=DISABLE;//补加系统自动控温禁止
		}
		
	}
	
	else
	{
		asm("nop;");
	}

}

















