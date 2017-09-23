/**
  ******************************************************************************
  * @file    TGTHT510_collectANDgroup.c
  * @author  蒋章
  * @version V1.00
  * @date    20150626
  * @brief   空间站核心舱推进管理器遥测状态采集与组帧模块C文件
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"

extern uint16 TGTHT510_1553B_data_TGTHT100[];						//全局数组，缓存推进遥测线路盒除温度参数以外数据，89字
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[];				//全局数组，缓存推进遥测线路盒复帧A温度数据，65字
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[];				//全局数组，缓存推进遥测线路盒复帧B温度数据，65字
extern uint16 TGTHT510_1553B_data_TGTHT530[];						//全局数组，缓存压气机电机驱动器遥测数据，12字
extern uint16 TGTHT510_1553B_data_TGTHT520a[];						//全局数组，缓存推进控制驱动器主机遥测，7字
extern uint16 TGTHT510_1553B_data_TGTHT520b[];						//全局数组，缓存推进控制驱动器备机遥测，7字

extern TGTHT510_which_bus_TypeDef TGTHT510_which_bus;//总线切换全局变量

extern TGTHT510_supply_ctrl_TypeDef TGTHT510_supply_ctrl;

extern TGTHT510_supply_input_par_TypeDef TGTHT510_supply_input_par;

extern TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;

extern uint16 TGTHT510_fault_data_CG_push[7];						//推进故检-常规遥测参数
extern uint16 TGTHT510_fault_data_CG_supply[30];					//补加故检-常规遥测参数

extern uint16 mode_test;//测试使用


/*常规遥测全局变量-------------------------------------------------------------*/	

uint16 TGTHT510_1553B_data_CG[140];	 //常规遥测数组，共135个字

uint16 CG_EPDU_count; //EPDU源包序列计数

uint16 CG_heater_state_data[7];    //缓存加热器状态，按照遥测格式顺序
uint16 CG_valve_state_data[23];    //缓存阀门开关状态，按照遥测格式顺序
uint16 CG_yk_switch_state_data[4]; //缓存遥控阀门开关状态，与限位开关状态，按照遥测格式

uint16 CG_place_signal_enable_disable;//贮箱到位信号使能禁止标志
uint16 CG_TGTHT510_cpu_state; //推进管理器cpu状态
uint16 CG_tempercontrol_power; //热控功耗
uint16 CG_inputcommand_receive_state_data[2]; //注入指令接收状态
uint16 CG_equiment_command[3];//作为常规遥测下传的设备管理指令，分别为航天器标识，程控APID，程控应用数据。
uint16 CG_supply_fault_state_data[30]; //补加故检状态
uint16 CG_equiment_receive_state_data[6]; //设备间数据接收状态
uint16 CG_HYCT_receive_state_data[16]; //接收货船的交互数据
uint16 CG_count_number; //帧计数
uint16 CG_bus_command[2];//接收总线指令，下传指令内容与校验和

/*工程遥测全局变量-------------------------------------------------------------*/	

uint16 TGTHT510_1553B_data_GC[32];	//工程遥测数组，共32个字

uint16 GC_EPDU_count;//EPDU源包序列计数

uint16 GC_pressure_gas_bottle[6];//气瓶出口压力
uint16 GC_pressure_liquid_bottle[6];//贮箱气腔、液腔出口压力
uint16 GC_pressure_pipe[4];//管路压力
uint16 GC_remainder_liquid[6];//贮箱剩余量

uint8 GC_pressure_compressor_A;//压气机A出口压力
uint8 GC_pressure_compressor_B;//压气机B出口压力
uint8 GC_pressure_compressor_C;//压气机C出口压力

uint8 GC_pressure_engine_C_O;//姿控C机组氧环形管压力
uint8 GC_pressure_engine_C_F;//姿控C机组燃环形管压力

uint8 GC_supply_flag; //补加运行标志
uint16 GC_TJ_flag; //推进运行状态标志

uint16 GC_supply_name_state_data;	//补加阶段字

/*仪表遥测全局变量-------------------------------------------------------------*/	

uint16 TGTHT510_1553B_data_YB[21];  //仪表遥测数组，共21个字

uint16 YB_EPDU_count;//EPDU源包序列计数

uint16 YB_TJ_flag; //推进运行状态
uint16 YB_supply_flag; //补加阶段标志
uint16 YB_supply_state; //补加运行状态标志
uint16 YB_fault_state; //故障处理状态

uint16 YB_pressure_gas_bottle[6];//气瓶出口压力
uint16 YB_remainder_liquid[6];//贮箱剩余量


/*设备管理指令全局变量-------------------------------------------------------------*/	
uint16 TGTHT510_1553B_data_equiment_command[11];//设备管理指令，共11个字

uint16 equiment_command_EPDU_count;//设备管理指令帧序列号

/*服务请求指令全局变量-------------------------------------------------------------*/

uint16 TGTHT510_1553B_data_ask_for_service;

/*送货船参数全局变量-------------------------------------------------------------*/
uint16 TGTHT510_1553B_data_HYCT[37];

uint16 HYCT_EPDU_count; //EPDU源包序列计数

uint16 HYCT_data[32];//送货运飞船遥测数据

/*送GNC故检参数全局变量-------------------------------------------------------------*/
uint16 TGTHT510_1553B_data_GNC[7];

uint16 GNC_EPDU_count; //EPDU源包序列计数

/*送内存下传参数全局变量-------------------------------------------------------------*/

uint16 TGTHT510_1553B_data_MEMORY[255];

uint16 MEMORY_data[250];

uint16 MEMORY_EPDU_count; //EPDU源包序列计数




/*查询表------------------------------------------------------------------------*/	

const uint16 yk_state_from_FPGA_bit[46]={
	BIT06,//LVb39,41关
	BIT07,//LVb49,51关
	BIT08,//LVb59,61关
	BIT09,//LVb63,65关
	BIT10,//LVb40,42关
	BIT11,//LVb50,52关
	BIT12,//LVb60,62关
	BIT13,//LVb64,66关
	BIT00,//LVb7关
	BIT01,//LVb8关
	BIT02,//LVb9关
	BIT03,//LVb10关
	BIT04,//LVb11关
	BIT05,//LVb12关
	BIT14,//LVb13,15关
	BIT00,//LVb23关
	BIT01,//LVb24关
	BIT15,//LVb14,16关
	BIT05,//LVb73,77开
	BIT06,//LVb73,71开
	BIT07,//LVb73,81开
	BIT08,//LVb73,85开
	BIT09,//LVb78,74开
	BIT10,//LVb72,74开
	BIT11,//LVb82,74开
	BIT12,//LVb86,74开
	BIT13,//LVb73,69关
	BIT14,//LVb70,74关
	BIT00,//氧1贮箱到位开关1
	BIT01,//氧1贮箱到位开关2
	BIT02,//氧1贮箱到位开关3
	BIT03,//氧2贮箱到位开关1
	BIT04,//氧2贮箱到位开关2
	BIT05,//氧2贮箱到位开关3
	BIT06,//氧3贮箱到位开关1
	BIT07,//氧3贮箱到位开关2
	BIT08,//氧3贮箱到位开关3
	BIT09,//燃1贮箱到位开关1
	BIT10,//燃1贮箱到位开关2
	BIT11,//燃1贮箱到位开关3
	BIT12,//燃2贮箱到位开关1
	BIT13,//燃2贮箱到位开关2
	BIT14,//燃2贮箱到位开关3
	BIT15,//燃3贮箱到位开关1
	BIT00,//燃3贮箱到位开关2
	BIT01//燃3贮箱到位开关3

};

const uint16 yk_state_from_FPGA_word[46]={
	WORD02,//LVb39,41关
	WORD02,//LVb49,51关
	WORD02,//LVb59,61关
	WORD02,//LVb63,65关
	WORD02,//LVb40,42关
	WORD02,//LVb50,52关
	WORD02,//LVb60,62关
	WORD02,//LVb64,66关
	WORD02,//LVb7关
	WORD02,//LVb8关
	WORD02,//LVb9关
	WORD02,//LVb10关
	WORD02,//LVb11关
	WORD02,//LVb12关
	WORD02,//LVb13,15关
	WORD03,//LVb23关
	WORD03,//LVb24关
	WORD02,//LVb14,16关
	WORD03,//LVb73,77开
	WORD03,//LVb73,71开
	WORD03,//LVb73,81开
	WORD03,//LVb73,85开
	WORD03,//LVb78,74开
	WORD03,//LVb72,74开
	WORD03,//LVb82,74开
	WORD03,//LVb86,74开
	WORD03,//LVb73,69关
	WORD03,//LVb70,74关
	WORD00,//氧1贮箱到位开关1
	WORD00,//氧1贮箱到位开关2
	WORD00,//氧1贮箱到位开关3
	WORD00,//氧2贮箱到位开关1
	WORD00,//氧2贮箱到位开关2
	WORD00,//氧2贮箱到位开关3
	WORD00,//氧3贮箱到位开关1
	WORD00,//氧3贮箱到位开关2
	WORD00,//氧3贮箱到位开关3
	WORD00,//燃1贮箱到位开关1
	WORD00,//燃1贮箱到位开关2
	WORD00,//燃1贮箱到位开关3
	WORD00,//燃2贮箱到位开关1
	WORD00,//燃2贮箱到位开关2
	WORD00,//燃2贮箱到位开关3
	WORD00,//燃3贮箱到位开关1
	WORD01,//燃3贮箱到位开关2
	WORD01//燃3贮箱到位开关3
	
};


const uint16 yk_state_to_CG_bit[46]={
	BIT08,//LVb39,41关
	BIT09,//LVb49,51关
	BIT10,//LVb59,61关
	BIT11,//LVb63,65关
	BIT12,//LVb40,42关
	BIT13,//LVb50,52关
	BIT14,//LVb60,62关
	BIT15,//LVb64,66关
	BIT00,//LVb7关
	BIT01,//LVb8关
	BIT02,//LVb9关
	BIT03,//LVb10关
	BIT04,//LVb11关
	BIT05,//LVb12关
	BIT06,//LVb13,15关
	BIT07,//LVb23关
	BIT08,//LVb24关
	BIT09,//LVb14,16关
	BIT10,//LVb73,77开
	BIT11,//LVb73,71开
	BIT12,//LVb73,81开
	BIT13,//LVb73,85开
	BIT14,//LVb78,74开
	BIT15,//LVb72,74开
	BIT00,//LVb82,74开
	BIT01,//LVb86,74开
	BIT02,//LVb73,69关
	BIT03,//LVb70,74关
	
	BIT04|BIT05,//氧1贮箱到位开关1
	BIT06|BIT07,//氧1贮箱到位开关2
	BIT08|BIT09,//氧1贮箱到位开关3
	BIT10|BIT11,//氧2贮箱到位开关1
	BIT12|BIT13,//氧2贮箱到位开关2
	BIT14|BIT15,//氧2贮箱到位开关3
	BIT00|BIT01,//氧3贮箱到位开关1
	BIT02|BIT03,//氧3贮箱到位开关2
	BIT04|BIT05,//氧3贮箱到位开关3
	BIT06|BIT07,//燃1贮箱到位开关1
	BIT08|BIT09,//燃1贮箱到位开关2
	BIT10|BIT11,//燃1贮箱到位开关3
	BIT12|BIT13,//燃2贮箱到位开关1
	BIT14|BIT15,//燃2贮箱到位开关2
	BIT00|BIT01,//燃2贮箱到位开关3
	BIT02|BIT03,//燃3贮箱到位开关1
	BIT04|BIT05,//燃3贮箱到位开关2
	BIT06|BIT07//燃3贮箱到位开关3

};


const uint16 yk_state_to_CG_word[46]={
	WORD00,//LVb39,41关
	WORD00,//LVb49,51关
	WORD00,//LVb59,61关
	WORD00,//LVb63,65关
	WORD00,//LVb40,42关
	WORD00,//LVb50,52关
	WORD00,//LVb60,62关
	WORD00,//LVb64,66关
	WORD00,//LVb7关
	WORD00,//LVb8关
	WORD00,//LVb9关
	WORD00,//LVb10关
	WORD00,//LVb11关
	WORD00,//LVb12关
	WORD00,//LVb13,15关
	WORD00,//LVb23关
	WORD01,//LVb24关
	WORD01,//LVb14,16关
	WORD01,//LVb73,77开
	WORD01,//LVb73,71开
	WORD01,//LVb73,81开
	WORD01,//LVb73,85开
	WORD01,//LVb78,74开
	WORD01,//LVb72,74开
	WORD01,//LVb82,74开
	WORD01,//LVb86,74开
	WORD01,//LVb73,69关
	WORD01,//LVb70,74关
	
	WORD01,//氧1贮箱到位开关1
	WORD01,//氧1贮箱到位开关2
	WORD02,//氧1贮箱到位开关3
	WORD02,//氧2贮箱到位开关1
	WORD02,//氧2贮箱到位开关2
	WORD02,//氧2贮箱到位开关3
	WORD02,//氧3贮箱到位开关1
	WORD02,//氧3贮箱到位开关2
	WORD02,//氧3贮箱到位开关3
	WORD02,//燃1贮箱到位开关1
	WORD03,//燃1贮箱到位开关2
	WORD03,//燃1贮箱到位开关3
	WORD03,//燃2贮箱到位开关1
	WORD03,//燃2贮箱到位开关2
	WORD03,//燃2贮箱到位开关3
	WORD03,//燃3贮箱到位开关1
	WORD03,//燃3贮箱到位开关2
	WORD03//燃3贮箱到位开关3
	
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
											};//加热回路置位掩码

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


//0、1:0x0003--------//8、9:0x0300
//2、3:0x000c--------//10、11:0x0c00
//4、5:0x0030--------//12、13:0x3000
//6、7:0x00c0--------//14、15:0xc000
//8、9:0x0300
//10、11:0x0c00
//12、13:0x3000
//14、15:0xc000


const uint16 valve_K_YC_write_word_bit[88]={0x000c,0x6000,0xc000,0x00c0,0x000c,0xc000,0x00c0,0x000c,0x000c,0x0c00,//LVb1~10开
											0x00c0,0x000c,0x0c00,0x00c0,0xc000,0x0c00,0x000c,0xc000,0x00c0,0x000c,//LVb11~20开
											0x0c00,0x00c0,0x000c,0x00c0,0x0c00,0xc000,0x0c00,0x0c00,0xc000,0xc000,//LVb21~30开
											0x000c,0x000c,0x00c0,0x00c0,0x0c00,0x0c00,0xc000,0xc000,0x0c00,0x000c,//LVb31~40开
											0xc000,0x00c0,0x000c,0x0c00,0x00c0,0xc000,0x0c00,0x000c,0x0c00,0x00c0,//LVb41~50开
											0xc000,0x0c00,0x000c,0xc000,0x00c0,0x000c,0x0c00,0x00c0,0xc000,0x0c00,//LVb51~60开
											0x000c,0xc000,0xc000,0x00c0,0x000c,0x0c00,0xc000,0x00c0,0x000c,0x0c00,//LVb61~70开
											0x00c0,0x0c00,0x0c00,0xc000,0x00c0,0xc000,0xc000,0x000c,0x0c00,0x000c,//LVb71~80开
											0x000c,0x00c0,0xc000,0x00c0,0x00c0,0x0c00,0x000c,0x00c0//LVb81~87,DVb开
	
};




const uint16 valve_K_YC_write_word_byte[88]={	13,0,10,6,20,15,13,0,10,7,//LVb1~10开
												20,15,14,0,14,1,14,1,14,1,//LVb11~20开
												15,1,3,3,4,4,12,2,12,2,//LVb21~30开
												12,2,12,2,13,3,13,3,5,8,//LVb31~40开
												5,8,5,9,5,9,6,9,17,18,//LVb41~50开
												17,19,17,19,17,19,18,19,18,20,//LVb51~60开
												18,20,6,9,6,10,7,10,7,11,//LVb61~70开
												15,21,16,21,7,11,16,21,8,11,//LVb71~80开
												16,21,8,11,16,22,4,4//LVb81~87,DVb开
};

//0、1:0x0003
//2、3:0x000c
//4、5:0x0030
//6、7:0x00c0
//8、9:0x0300
//10、11:0x0c00
//12、13:0x3000
//14、15:0xc000


const uint16 valve_G_YC_write_word_bit[88]={0x0030,0x0003,0x0003,0x0300,0x0030,0x0003,0x0300,0x0030,0x0030,0x3000,//LVb1~10关
											0x0300,0x0030,0x3000,0x0300,0x0003,0x3000,0x0030,0x0003,0x0300,0x0030,//LVb11~20关
											0x3000,0x0300,0x0030,0x0300,0x3000,0x0003,0x3000,0x3000,0x0003,0x0003,//LVb21~30关
											0x0030,0x0030,0x0300,0x0300,0x3000,0x3000,0x0003,0x0003,0x3000,0x0030,//LVb31~40关
											0x0003,0x0300,0x0030,0x3000,0x0300,0x0003,0x3000,0x0030,0x3000,0x0300,//LVb41~50关
											0x0003,0x3000,0x0030,0x0003,0x0300,0x0030,0x3000,0x0300,0x0003,0x3000,//LVb51~60关
											0x0030,0x0003,0x0003,0x0300,0x0030,0x3000,0x0003,0x0300,0x0030,0x3000,//LVb61~70关
											0x0300,0x3000,0x3000,0x0003,0x0300,0x0003,0x0003,0x0030,0x3000,0x0030,//LVb71~80关
											0x0030,0x0300,0x0003,0x0300,0x0300,0x3000,0x0030,0x0300//LVb81~87,DVb关	
};



const uint16 valve_G_YC_write_word_byte[88]={	13,0,10,7,20,15,14,0,10,7,//LVb1~10关
												21,15,14,1,14,1,14,1,15,1,//LVb11~20关
												15,2,3,4,4,4,12,2,12,2,//LVb21~30关
												12,2,13,3,13,3,13,3,5,8,//LVb31~40关
												5,9,5,9,6,9,6,9,17,19,//LVb41~50关
												17,19,17,19,18,19,18,20,18,20,//LVb51~60关
												18,20,6,10,6,10,7,11,7,11,//LVb61~70关
												16,21,16,21,8,11,16,21,8,11,//LVb71~80关
												16,22,8,12,17,22,4,5//LVb81~87,DVb关
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
	
};//设备管理指令查询表，待修改！！！！！


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
	
};//设备管理指令查询表，第一个字节，待修改！！！！！







/******************************************************************************************
**名称：遥测状态采集模块初始化函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/


void TGTHT510_collectANDgroup_initial(void)
 {
	 uint16 i;


	
/*常规遥测参数初始化---------------------------------------------------------------------*/	 
	 
	 for(i=0;i<=139;i++)
	 {
		TGTHT510_1553B_data_CG[i]=0x0000;//常规遥测初始化 
	 }
	 
	 
	 for(i=0;i<=6;i++)
	 {
		 CG_heater_state_data[i]=0xffff;//加热器状态数组初始化		 
	 }
	 
	 for(i=0;i<=22;i++)
	 {
		CG_valve_state_data[i]=0x0000;//阀门开关状态数组初始化 
		 
	 }
	 
	 for(i=0;i<=3;i++)
	 {
		CG_yk_switch_state_data[i]=0x0000; //缓存遥控阀门开关状态，与限位开关状态初始化
	 }
	 
	 for(i=0;i<=1;i++)
	 {
		 CG_inputcommand_receive_state_data[i]=0x0000; //注入指令接收状态初始化
	 }
	 
	 for(i=0;i<=29;i++)
	 {
		 CG_supply_fault_state_data[i]=0x0000;//补加故检状态初始化
	 }
	 
	 for(i=0;i<=5;i++)
	 {
		 CG_equiment_receive_state_data[i]=0x0000;//设备间数据接收状态初始化
	 }
	 
	 for(i=0;i<=15;i++)
	 {
		 CG_HYCT_receive_state_data[i]=0x0000;//接收货船的交互数据初始化
	 }
	 
	 for(i=0;i<=2;i++)
	 {
		 CG_equiment_command[i]=0x0000;//设备管理指令作为常规遥测下传
	 }
	 
	 for(i=0;i<=1;i++)
	 {
		 CG_bus_command[i]=0x0000;//总线指令指令作为常规遥测下传
	 }
	 
	 CG_tempercontrol_power=0x0000;//热控功耗
	 
	 
	 if(get_CPU()==CPU_B)//B机
	 {
		CG_TGTHT510_cpu_state=0x0b0b;//推进管理器cpu状态
	 }
	
	 else//A机
	 {
		CG_TGTHT510_cpu_state=0x0a0a;//推进管理器cpu状态
	 }
	 
	 CG_count_number=0x0000; //帧计数
	 
	 CG_place_signal_enable_disable=0x6f6f;
	 
	 CG_EPDU_count=0x0000; //EPDU源包序列计数
	 
	 

	 
/*工程遥测参数初始化---------------------------------------------------------------------*/	 
	 
	 for(i=0;i<=31;i++)
	 {
		TGTHT510_1553B_data_GC[i]=0x0000;//工程遥测初始化 
	 }
	 
	 for(i=0;i<=5;i++)
	 {
		GC_pressure_gas_bottle[i]=0x0000; //气瓶出口压力
	 }
	 
	 for(i=0;i<=5;i++)
	 {
		GC_pressure_liquid_bottle[i]=0x0000; //贮箱气腔、液腔出口压力
	 }
	 
	 for(i=0;i<=3;i++)
	 {
		GC_pressure_pipe[i]=0x0000; //管路压力
	 }
	 
	 for(i=0;i<=5;i++)
	 {
		GC_remainder_liquid[i]=0x0000; //贮箱剩余量
	 }
	 
	 GC_pressure_compressor_A=0x00;//压气机A出口压力
	 GC_pressure_compressor_B=0x00;//压气机B出口压力
	 GC_pressure_compressor_C=0x00;//压气机C出口压力
	 
	 GC_pressure_engine_C_O=0x00;//姿控C机组氧环形管压力
	 GC_pressure_engine_C_F=0x00;//姿控C机组燃环形管压力
	 
	 GC_supply_flag=0x00; //补加运行标志
	 GC_TJ_flag=0x00; //推进运行状态标志
	 
	 GC_supply_name_state_data=0x0000;	//补加阶段字
	 
	 GC_EPDU_count=0x0000; //EPDU源包序列计数
	 
/*仪表遥测参数初始化---------------------------------------------------------------------*/	 
	 
	 for(i=0;i<=20;i++)
	 {
		TGTHT510_1553B_data_YB[i]=0x0000;//仪表遥测初始化 
	 }
	 
	 YB_TJ_flag=0x0000; //推进运行状态
	 YB_supply_flag=0x0000; //补加阶段标志
	 YB_supply_state=0x0000; //补加运行状态标志
	 YB_fault_state=0x0000; //故障处理状态
	 
	 for(i=0;i<=5;i++)
	 {
		YB_pressure_gas_bottle[i]=0x0000;//气瓶出口压力
	 }
	 
	 for(i=0;i<=5;i++)
	 {
		YB_remainder_liquid[i]=0x0000;//贮箱剩余量 
	 }
	 
	 YB_EPDU_count=0x0000;//EPDU源包序列计数

/*设备管理指令参数初始化---------------------------------------------------------------------*/	 
	 
	 for(i=0;i<=10;i++)
	 {
		TGTHT510_1553B_data_equiment_command[i]=0x0000; //设备管理指令
	 }
	 
	 equiment_command_EPDU_count=0x0000;//设备管理指令帧序列号
	 
/*服务请求指令参数初始化---------------------------------------------------------------------*/	 
	 
	 TGTHT510_1553B_data_ask_for_service=0x0000;

/*送货运飞船参数初始化---------------------------------------------------------------------*/	 
	 
	 for(i=0;i<=36;i++)
	 {
		 TGTHT510_1553B_data_HYCT[i]=0x0000;
	 }
	 
	 for(i=0;i<=31;i++)
	 {
		 HYCT_data[i]=0x0000;
	 }
	 
	 HYCT_EPDU_count=0x0000;
	 
/*送GNC故检参数初始化---------------------------------------------------------------------*/	 
	 for(i=0;i<=6;i++)
	 {
		 TGTHT510_1553B_data_GNC[i]=0x0000;
	 }
	 
	 GNC_EPDU_count=0x0000;
	 
/*送内存下传参数初始化---------------------------------------------------------------------*/	 
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
**名称：遥测采集与组帧模块主函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_collectANDgroup_main(void)
{
	
	TGTHT510_collectANDgroup_heater_state_collect_save();//加热器状态采集与缓存
	
	TGTHT510_collectANDgroup_yk_state_collect_save();//OC指令与到位信号读取
	
	//TGTHT510_collectANDgroup_CG_group();//常规遥测数据组帧
	//TGTHT510_collectANDgroup_GC_group();//工程遥测数据组帧
	//TGTHT510_collectANDgroup_HYCT_group();//送货船遥测数据组帧
	//TGTHT510_collectANDgroup_GNC_group();//发送转发GNC故检状态字
	
	
}



/******************************************************************************************
**名称：加热器状态采集与缓存函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_collectANDgroup_heater_state_collect_save(void)
{
	uint16 state[7];
	uint16 i,j;
	uint16 state_gk;//轨控备份加热状态
	
	
	state[0]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG0);
	state[1]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG1);
	state[2]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG2);
	state[3]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG3);
	state[4]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG4);
	state[5]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG5);
	state[6]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG6);
	state[7]=Read_32_to_16(*(volatile uint32 *)HEATER_STATE_READ_REG7);//读取并缓存加热器状态

	for(i=0;i<=6;i++)
	{
		CG_heater_state_data[i]=0xffff;//加热器状态函数初始化		 
	}
	
	
	for(i=0;i<=99;i++)
	{
		if(TGTHT510_collectANDgroup_is_heater_state(state,i)==HEATER_ON)//某控温回路加热器为导通状态
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
	
	if((state_gk&0xc000)==0x8000)//通
	{
		CG_heater_state_data[6]=CG_heater_state_data[6]&0xefff;
	}
	
	else if((state_gk&0xc000)==0x4000)//断
	{
		asm("nop;");
	}
	
	else
	{
		asm("nop;");
	}
	
	

}



/******************************************************************************************
**名称：加热器状态判断函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

//输入加热回路的路号，0~99，加热器状态数组p，返回加热与否的状态
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
**名称：阀门状态采集与缓存函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
	//读取遥测状态后，取反，
	//若未加电，开关状态均为高
	//阀门打开，则开状态高，关状态低
	//阀门关闭，则开状态低，关状态高
	//阀门初始加电，则开关状态均为低
	
	
	
	for(i=0x00;i<=0x56;i++)//LVb1~87
	{
		k_num=valve_K_read_word_byte[i];//阀门开状态缓存字节号
		g_num=k_num+1;
		k_state=state[k_num]&valve_read_word_bit[i];
		g_state=state[g_num]&valve_read_word_bit[i];
		if((k_state!=0)&&(g_state==0))
		{
			m=valve_K_YC_write_word_byte[i];
			CG_valve_state_data[m]=CG_valve_state_data[m]|valve_K_YC_write_word_bit[i];//遥测数据阀门开状态置位
			m=valve_G_YC_write_word_byte[i];
			CG_valve_state_data[m]=CG_valve_state_data[m]&(~valve_G_YC_write_word_bit[i]);//遥测数据阀门关状态置零	
		}
		
		else if((k_state==0)&&(g_state!=0))
		{
			m=valve_G_YC_write_word_byte[i];
			CG_valve_state_data[m]=CG_valve_state_data[m]|valve_G_YC_write_word_bit[i];//遥测数据阀门关状态置位
			m=valve_K_YC_write_word_byte[i];
			CG_valve_state_data[m]=CG_valve_state_data[m]&(~valve_K_YC_write_word_bit[i]);//遥测数据阀门开状态置零	
		}
		else
		{
			i=i;
		}

	}
	

	j=valve_K_read_word_byte[0x57];//DVb1的状态缓存字节号
	k=state[j]&valve_read_word_bit[0x57];
	if(k!=0)
	{
		m=valve_K_YC_write_word_byte[0x57];
		CG_valve_state_data[m]=CG_valve_state_data[m]|valve_K_YC_write_word_bit[0x57];//遥测数据DVb1阀门开状态置位
		m=valve_G_YC_write_word_byte[0x57];
		CG_valve_state_data[m]=CG_valve_state_data[m]&(~valve_G_YC_write_word_bit[0x57]);//遥测数据DVb1阀门关状态置零
		
	}
	else
	{
		m=valve_G_YC_write_word_byte[0x57];
		CG_valve_state_data[m]=CG_valve_state_data[m]|valve_G_YC_write_word_bit[0x57];//遥测数据DVb1阀门关状态置位
		m=valve_K_YC_write_word_byte[0x57];
		CG_valve_state_data[m]=CG_valve_state_data[m]&(~valve_K_YC_write_word_bit[0x57]);//遥测数据DVb1阀门开状态置零
		
	}

	
}

/******************************************************************************************
**名称：阀门状态判断函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_collectANDgroup_is_valve_state(uint16 valve_number)
{
	uint16 i,j,k,m,n;
	uint16 state_on,state_off;
	if(valve_number<=0x57)//输入的阀门内部编号合法
	{
		i=valve_K_YC_write_word_byte[valve_number];//阀门开状态遥测字节号
		j=valve_K_YC_write_word_bit[valve_number];//阀门开状态位置掩码
		if((CG_valve_state_data[i]&j)==j)
		{
			state_on=TRUE;
		}
		
		else
		{
			state_on=FALSE;
		}
		
		i=valve_G_YC_write_word_byte[valve_number];//阀门关状态遥测字节号
		j=valve_G_YC_write_word_bit[valve_number];//阀门关状态位置掩码
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
			return VALVE_NO_POWER;//阀门未加电
		}
		
		else if((state_on==FALSE)&&(state_off==FALSE))
		{
			return VALVE_UNKNOW;//阀门状态未知
		}
		
		else if((state_on==TRUE)&&(state_off==FALSE))
		{
			return VALVE_ON;//阀门为打开状态
		}
		
		else if((state_on==FALSE)&&(state_off==TRUE))
		{
			return VALVE_OFF;//阀门为关闭状态
		}
		
		else
		{
			return VALVE_UNKNOW;//阀门状态未知
		}
		
	}
	else
	{
		return VALVE_UNDEFINE;//输入的阀门内部编号非法
	}

}


/******************************************************************************************
**名称：EPDU包序列计数生成函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
**名称：EPDU包序列计数生成函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
**名称：常规遥测数据组帧
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_collectANDgroup_CG_group(void)
{
	uint16 i;
	uint8 sum;
	
	uint32 supply_stage_time_val;
	
	TGTHT510_supply_time_stage_get(&supply_stage_time_val);
	
	TGTHT510_collectANDgroup_CG_data_generate();
	
	TGTHT510_1553B_data_CG[0]=0x0b00;//包版本：000、包类型：0、数据域头标志：1、APID：0110_000_0000
	
	CG_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(CG_EPDU_count,COUNT_14BIT);//更新EPDU源包序列计数
	
	TGTHT510_1553B_data_CG[1]=(CG_EPDU_count&0x3fff)|0xc000;//分组标志：11，包序列计数
	
	TGTHT510_1553B_data_CG[2]=0x0111;//源包长度
	
	if(get_CPU()==CPU_B)//B机
	{
		TGTHT510_1553B_data_CG[3]=0x0200;//服务类型，服务子类型
	}
	
	else//A机
	{
		TGTHT510_1553B_data_CG[3]=0x0100;//服务类型，服务子类型
	}
	
	for(i=0;i<=3;i++)
	{
		TGTHT510_1553B_data_CG[i+4]=CG_yk_switch_state_data[i];//缓存遥控阀门开关状态，与限位开关状态
	}
	
	for(i=0;i<=6;i++)
	{
		TGTHT510_1553B_data_CG[i+8]=CG_heater_state_data[i]; //缓存加热器状态
		
	}
	
	TGTHT510_1553B_data_CG[14]=TGTHT510_1553B_data_CG[14]&0x1f00;
	CG_valve_state_data[0]=CG_valve_state_data[0]&0xe0ff;
	TGTHT510_1553B_data_CG[14]=TGTHT510_1553B_data_CG[14]|CG_valve_state_data[0];//拼帧
	
	for(i=1;i<=22;i++)
	{
		TGTHT510_1553B_data_CG[i+14]=CG_valve_state_data[i];//缓存阀门开关状态
	}
	
	TGTHT510_1553B_data_CG[36]=TGTHT510_1553B_data_CG[36]|0x00ff;
	
	//注入参数：燃补加接口，氧补加接口
	TGTHT510_1553B_data_CG[37]=(TGTHT510_supply_decode_par.interface_F<<8)|(TGTHT510_supply_decode_par.interface_O>>8);
	
	//注入参数：燃抽气压气机号，氧抽气压气机号
	TGTHT510_1553B_data_CG[38]=(TGTHT510_supply_decode_par.compressor_F<<8)|(TGTHT510_supply_decode_par.compressor_O>>8);

	//注入参数：燃抽气压气机出口阀门，氧补抽气压气机出口阀门
	TGTHT510_1553B_data_CG[39]=(TGTHT510_supply_decode_par.valve_out_compressor_F<<8)|(TGTHT510_supply_decode_par.valve_out_compressor_O>>8);
	
	//注入参数：补加的燃贮箱个数，补加的氧贮箱个数
	TGTHT510_1553B_data_CG[40]=(TGTHT510_supply_decode_par.number_tank_F<<8)|(TGTHT510_supply_decode_par.number_tank_F&0x00ff);
	
	//注入参数：第一个补加的燃贮箱号，第一个补加的氧贮箱号
	TGTHT510_1553B_data_CG[41]=(TGTHT510_supply_decode_par.first_tank_F<<8)|(TGTHT510_supply_decode_par.first_tank_O>>8);
	
	//注入参数：第二个补加的燃贮箱号，第二个补加的氧贮箱号
	TGTHT510_1553B_data_CG[42]=(TGTHT510_supply_decode_par.second_tank_F<<8)|(TGTHT510_supply_decode_par.second_tank_O>>8);
	
	//注入参数：第三个补加的燃贮箱号，第三个补加的氧贮箱号
	TGTHT510_1553B_data_CG[43]=(TGTHT510_supply_decode_par.third_tank_F<<8)|(TGTHT510_supply_decode_par.third_tank_O>>8);
	
	//注入参数：燃贮箱F1抽气气瓶个数，氧贮箱O1抽气气瓶个数
	TGTHT510_1553B_data_CG[44]=(TGTHT510_supply_decode_par.number_gas_tank_F1<<8)|(TGTHT510_supply_decode_par.number_gas_tank_O1&0x00ff);
	
	//注入参数：燃贮箱F1的第一个抽气气瓶号，氧贮箱O1的第一个抽气气瓶号
	TGTHT510_1553B_data_CG[45]=(TGTHT510_supply_decode_par.first_gas_tank_F1<<8)|(TGTHT510_supply_decode_par.first_gas_tank_O1>>8);
	
	//注入参数：燃贮箱F1的第二个抽气气瓶号，氧贮箱O1的第二个抽气气瓶号
	TGTHT510_1553B_data_CG[46]=(TGTHT510_supply_decode_par.second_gas_tank_F1<<8)|(TGTHT510_supply_decode_par.second_gas_tank_O1>>8);
	
	//注入参数：燃贮箱F2抽气气瓶个数，氧贮箱O2抽气气瓶个数
	TGTHT510_1553B_data_CG[47]=(TGTHT510_supply_decode_par.number_gas_tank_F2<<8)|(TGTHT510_supply_decode_par.number_gas_tank_O2&0x00ff);
	
	//注入参数：燃贮箱F2的第一个抽气气瓶号，氧贮箱O2的第一个抽气气瓶号
	TGTHT510_1553B_data_CG[48]=(TGTHT510_supply_decode_par.first_gas_tank_F2<<8)|(TGTHT510_supply_decode_par.first_gas_tank_O2>>8);
	
	//注入参数：燃贮箱F2的第二个抽气气瓶号，氧贮箱O2的第二个抽气气瓶号
	TGTHT510_1553B_data_CG[49]=(TGTHT510_supply_decode_par.second_gas_tank_F2<<8)|(TGTHT510_supply_decode_par.second_gas_tank_O2>>8);
	
	//注入参数：燃贮箱F3抽气气瓶个数，氧贮箱O3抽气气瓶个数
	TGTHT510_1553B_data_CG[50]=(TGTHT510_supply_decode_par.number_gas_tank_F3<<8)|(TGTHT510_supply_decode_par.number_gas_tank_O3&0x00ff);
	
	//注入参数：燃贮箱F3的第一个抽气气瓶号，氧贮箱O3的第一个抽气气瓶号
	TGTHT510_1553B_data_CG[51]=(TGTHT510_supply_decode_par.first_gas_tank_F3<<8)|(TGTHT510_supply_decode_par.first_gas_tank_O3>>8);
	
	//注入参数：燃贮箱F3的第二个抽气气瓶号，氧贮箱O3的第二个抽气气瓶号
	TGTHT510_1553B_data_CG[52]=(TGTHT510_supply_decode_par.second_gas_tank_F3<<8)|(TGTHT510_supply_decode_par.second_gas_tank_O3>>8);
	
	//注入参数：液冷模块泵号
	TGTHT510_1553B_data_CG[53]=TGTHT510_supply_decode_par.cooler;
	
	//注入参数：燃贮箱F1补加到位剩余量
	TGTHT510_1553B_data_CG[54]=TGTHT510_supply_input_par.volum_F1;
	
	//注入参数：燃贮箱F2补加到位剩余量
	TGTHT510_1553B_data_CG[55]=TGTHT510_supply_input_par.volum_F2;
	
	//注入参数：燃贮箱F3补加到位剩余量
	TGTHT510_1553B_data_CG[56]=TGTHT510_supply_input_par.volum_F3;
	
	//注入参数：氧贮箱O1补加到位剩余量
	TGTHT510_1553B_data_CG[57]=TGTHT510_supply_input_par.volum_O1;
	
	//注入参数：氧贮箱O2补加到位剩余量
	TGTHT510_1553B_data_CG[58]=TGTHT510_supply_input_par.volum_O2;
	
	//注入参数：氧贮箱O3补加到位剩余量
	TGTHT510_1553B_data_CG[59]=TGTHT510_supply_input_par.volum_O3;
	
	//补加状态：当前补加模式
	TGTHT510_1553B_data_CG[60]=TGTHT510_supply_ctrl.mode;
	
	//补加状态：当前补加运行状态（运行，暂停，中止，空闲）
	TGTHT510_1553B_data_CG[61]=TGTHT510_supply_ctrl.state;
	
	//补加状态：当前补加阶段
	TGTHT510_1553B_data_CG[62]=TGTHT510_supply_ctrl.stage;
	
	//补加状态：当前补加处理步骤号
	TGTHT510_1553B_data_CG[63]=TGTHT510_supply_ctrl.step;
	
	//补加状态：当前补加处理指令号
	TGTHT510_1553B_data_CG[64]=TGTHT510_supply_ctrl.command;
	
	//补加状态：当前补加故障代码
	TGTHT510_1553B_data_CG[65]=TGTHT510_supply_ctrl.errno;
	
	//补加状态：当前补加运行时间（高字）
	TGTHT510_1553B_data_CG[66]=(uint16)(supply_stage_time_val>>16);
	
	//补加状态：当前补加运行时间（低字）
	TGTHT510_1553B_data_CG[67]=(uint16)(supply_stage_time_val>>0);
	
	//总线指令的指令内容
	TGTHT510_1553B_data_CG[68]=CG_bus_command[0];
	
	//总线指令的指令校验
	TGTHT510_1553B_data_CG[69]=CG_bus_command[1];
	
	//贮箱到位信号使能禁止标志
	TGTHT510_1553B_data_CG[70]=CG_place_signal_enable_disable;
	
	//推进管理器cpu状态
	TGTHT510_1553B_data_CG[71]=CG_TGTHT510_cpu_state;
	
	//推进故检
	for(i=0;i<=6;i++)
	{
		TGTHT510_1553B_data_CG[i+72]=TGTHT510_fault_data_CG_push[i];
	}
	
	//1553B总线通道标识
	TGTHT510_1553B_data_CG[79]=TGTHT510_which_bus.last_use_BU65170;
	
	//热控功耗
	TGTHT510_1553B_data_CG[80]=CG_tempercontrol_power; //热控功耗
	
	//注入指令接收状态
	for(i=0;i<=1;i++)
	{
		TGTHT510_1553B_data_CG[i+81]=CG_inputcommand_receive_state_data[i];//注入指令接收状态
	}
	
	//设备管理指令
	TGTHT510_1553B_data_CG[83]=CG_equiment_command[0];
	
	TGTHT510_1553B_data_CG[84]=CG_equiment_command[1];
	
	TGTHT510_1553B_data_CG[85]=CG_equiment_command[2];
	
	//补加故检状态
	for(i=0;i<=29;i++)
	{
		TGTHT510_1553B_data_CG[i+86]=TGTHT510_fault_data_CG_supply[i];
	}
	
	//设备间数据接收状态
	for(i=0;i<=5;i++)
	{
		TGTHT510_1553B_data_CG[i+116]=CG_equiment_receive_state_data[i]; 
	}
	
	//接收货船的交互数据
	for(i=0;i<=15;i++)
	{
		TGTHT510_1553B_data_CG[i+122]=CG_HYCT_receive_state_data[i];
	}
	
	//TGTHT510_1553B_data_CG[137]=mode_test;//测试使用
	
	//帧计数
	CG_count_number++;
	TGTHT510_1553B_data_CG[138]=CG_count_number;
	
	//字节累加和
	sum=TGTHT510_collectANDgroup_sum_generate(TGTHT510_1553B_data_CG,139);
	
	TGTHT510_1553B_data_CG[139]=(((uint16)sum)<<8)|0x00aa;
}


/******************************************************************************************
**名称：常规遥测数据提取
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_collectANDgroup_CG_data_generate(void)
{
	//TGTHT510_collectANDgroup_CG_supply_group();
	
	/*
//---------------------------------测试----------------------------------------------------	
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

//--------------------------------------------测试---------------------------------
	
	
	//常规遥测参数提取
	
	*/
	
}





/******************************************************************************************
**名称：工程遥测数据提取
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_collectANDgroup_GC_data_generate(void)
{
	
	uint16 i;
	
	GC_pressure_gas_bottle[0]=TGTHT510_1553B_data_TGTHT100[0];//氧1气瓶出口压力
	GC_pressure_gas_bottle[1]=TGTHT510_1553B_data_TGTHT100[2];//氧2气瓶出口压力
	GC_pressure_gas_bottle[2]=TGTHT510_1553B_data_TGTHT100[4];//氧3气瓶出口压力
	GC_pressure_gas_bottle[3]=TGTHT510_1553B_data_TGTHT100[1];//燃1气瓶出口压力
	GC_pressure_gas_bottle[4]=TGTHT510_1553B_data_TGTHT100[3];//燃2气瓶出口压力
	GC_pressure_gas_bottle[5]=TGTHT510_1553B_data_TGTHT100[5];//燃3气瓶出口压力
	
	//氧1贮箱气腔压力，氧2贮箱气腔压力
	GC_pressure_liquid_bottle[0]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[12],TGTHT510_1553B_data_TGTHT100[14]);
	
	//氧3贮箱气腔压力，燃1贮箱气腔压力
	GC_pressure_liquid_bottle[1]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[16],TGTHT510_1553B_data_TGTHT100[13]);
	
	//燃2贮箱气腔压力，燃3贮箱气腔压力
	GC_pressure_liquid_bottle[2]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[15],TGTHT510_1553B_data_TGTHT100[17]);

	//氧1贮箱液腔压力，氧2贮箱液腔压力
	GC_pressure_liquid_bottle[3]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[18],TGTHT510_1553B_data_TGTHT100[20]);
	
	//氧3贮箱液腔压力，燃1贮箱液腔压力
	GC_pressure_liquid_bottle[4]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[22],TGTHT510_1553B_data_TGTHT100[19]);
	
	//燃2贮箱液腔压力，燃3贮箱液腔压力
	GC_pressure_liquid_bottle[5]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[21],TGTHT510_1553B_data_TGTHT100[23]);
	
	//轨控A1，A3氧管路压力，轨控A2，A4氧管路压力
	GC_pressure_pipe[0]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[24],TGTHT510_1553B_data_TGTHT100[26]);
	
	//轨控A1，A3燃管路压力，轨控A2，A4燃管路压力
	GC_pressure_pipe[1]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[25],TGTHT510_1553B_data_TGTHT100[27]);
	
	//姿控B组氧I环形管压力，姿控B组燃I环形管压力
	GC_pressure_pipe[2]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[28],TGTHT510_1553B_data_TGTHT100[29]);
	
	//姿控B组氧II环形管压力，姿控B组燃II环形管压力
	GC_pressure_pipe[3]=TGTHT510_collectANDgroup_combine(TGTHT510_1553B_data_TGTHT100[30],TGTHT510_1553B_data_TGTHT100[31]);
	
	GC_remainder_liquid[0]=TGTHT510_1553B_data_TGTHT100[61];//氧1贮箱剩余量，取位移信号1
	GC_remainder_liquid[1]=TGTHT510_1553B_data_TGTHT100[64];//氧2贮箱剩余量，取位移信号1
	GC_remainder_liquid[2]=TGTHT510_1553B_data_TGTHT100[67];//氧3贮箱剩余量，取位移信号1
	GC_remainder_liquid[3]=TGTHT510_1553B_data_TGTHT100[70];//燃1贮箱剩余量，取位移信号1
	GC_remainder_liquid[4]=TGTHT510_1553B_data_TGTHT100[73];//燃2贮箱剩余量，取位移信号1
	GC_remainder_liquid[5]=TGTHT510_1553B_data_TGTHT100[76];//燃3贮箱剩余量，取位移信号1
	
	
	GC_pressure_compressor_A=(uint8)(TGTHT510_1553B_data_TGTHT100[42]>>4);//压气机A出口压力
	GC_pressure_compressor_B=(uint8)(TGTHT510_1553B_data_TGTHT100[43]>>4);//压气机B出口压力
	GC_pressure_compressor_C=(uint8)(TGTHT510_1553B_data_TGTHT100[60]>>4);//压气机C出口压力
	
	GC_pressure_engine_C_O=(uint8)(TGTHT510_1553B_data_TGTHT100[32]>>4);//姿控C组氧环形管压力
	GC_pressure_engine_C_F=(uint8)(TGTHT510_1553B_data_TGTHT100[32]>>4);//姿控C组氧环形管压力
	
}


/******************************************************************************************
**名称：仪表遥测数据提取
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_collectANDgroup_YB_data_generate(void)
{
	YB_pressure_gas_bottle[0]=TGTHT510_1553B_data_TGTHT100[0];//氧1气瓶出口压力
	YB_pressure_gas_bottle[1]=TGTHT510_1553B_data_TGTHT100[2];//氧2气瓶出口压力
	YB_pressure_gas_bottle[2]=TGTHT510_1553B_data_TGTHT100[4];//氧3气瓶出口压力
	YB_pressure_gas_bottle[3]=TGTHT510_1553B_data_TGTHT100[1];//燃1气瓶出口压力
	YB_pressure_gas_bottle[4]=TGTHT510_1553B_data_TGTHT100[3];//燃2气瓶出口压力
	YB_pressure_gas_bottle[5]=TGTHT510_1553B_data_TGTHT100[5];//燃3气瓶出口压力
	
	YB_remainder_liquid[0]=TGTHT510_1553B_data_TGTHT100[61];//氧1贮箱剩余量，取位移信号1
	YB_remainder_liquid[1]=TGTHT510_1553B_data_TGTHT100[64];//氧2贮箱剩余量，取位移信号1
	YB_remainder_liquid[2]=TGTHT510_1553B_data_TGTHT100[67];//氧3贮箱剩余量，取位移信号1
	YB_remainder_liquid[3]=TGTHT510_1553B_data_TGTHT100[70];//燃1贮箱剩余量，取位移信号1
	YB_remainder_liquid[4]=TGTHT510_1553B_data_TGTHT100[73];//燃2贮箱剩余量，取位移信号1
	YB_remainder_liquid[5]=TGTHT510_1553B_data_TGTHT100[76];//燃3贮箱剩余量，取位移信号1
	
}







/******************************************************************************************
**名称：工程遥测数据组帧
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_collectANDgroup_GC_group(void)
{
	uint16 i;
	uint8 sum;
	
	TGTHT510_collectANDgroup_GC_data_generate();//工程遥测数据提取
	
	TGTHT510_1553B_data_GC[0]=0x0b01;//包版本：000、包类型：0、数据域头标志：1、APID：0110_000_0001
	
	GC_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(GC_EPDU_count,COUNT_14BIT);
	TGTHT510_1553B_data_GC[1]=(GC_EPDU_count&0x3fff)|0xc000;//分组标志：11，包序列计数
	
	//TGTHT510_1553B_data_GC[1]=0xc000;
	
	TGTHT510_1553B_data_GC[2]=0x39;//源包长度
	
	TGTHT510_1553B_data_GC[3]=0x0100;//服务类型，服务子类型
	
	for(i=0;i<=5;i++)
	{
		TGTHT510_1553B_data_GC[i+4]=GC_pressure_gas_bottle[i];//气瓶出口压力	
	}
	
	for(i=0;i<=5;i++)
	{
		TGTHT510_1553B_data_GC[i+10]=GC_pressure_liquid_bottle[i];//贮箱气腔、液腔出口压力	
	}
	
	for(i=0;i<=3;i++)
	{
		TGTHT510_1553B_data_GC[i+16]=GC_pressure_pipe[i];//管路压力	
	}
	
	for(i=0;i<=5;i++)
	{
		TGTHT510_1553B_data_GC[i+20]=GC_remainder_liquid[i];//贮箱剩余量	
	}
	
	TGTHT510_1553B_data_GC[26]=(((uint16)GC_pressure_compressor_A)<<8)|((uint16)GC_pressure_compressor_B);//压气机A出口压力、压气机B出口压力
	
	TGTHT510_1553B_data_GC[27]=(((uint16)GC_pressure_compressor_C)<<8)|((uint16)GC_pressure_engine_C_O);//压气机C出口压力、姿控C机组氧环形管压力
	
	TGTHT510_1553B_data_GC[28]=(((uint16)GC_pressure_engine_C_F)<<8)|((uint16)GC_supply_flag);//姿控C机组燃环形管压力,补加运行标志
	
	TGTHT510_1553B_data_GC[29]=GC_TJ_flag;//推进运行状态标志
	
	TGTHT510_1553B_data_GC[30]=GC_supply_name_state_data;	//补加阶段字
	
	sum=TGTHT510_collectANDgroup_sum_generate(TGTHT510_1553B_data_GC,31);
	TGTHT510_1553B_data_GC[31]=(((uint16)sum)<<8)|0x00aa;//字节累加和

}

/******************************************************************************************
**名称：送货船遥测数据组帧
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_collectANDgroup_HYCT_group(void)
{
	uint16 i;
	uint8 sum;
	
	HYCT_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(HYCT_EPDU_count,COUNT_14BIT);
	
	//发送转发前向口补加数据
	if(HYCT_EPDU_count%2==0)
	{
		TGTHT510_1553B_data_HYCT[0]=(0x0800|T_APID_HYCT_FORE);
		TGTHT510_1553B_data_HYCT[1]=(HYCT_EPDU_count&0x3fff)|0xc000;//分组标志：11，包序列计数
		TGTHT510_1553B_data_HYCT[2]=0x0043;
		TGTHT510_1553B_data_HYCT[3]=T_SUBSERVICE_HYCT_FORE;
	}
	
	//发送转发后向口补加数据
	else
	{
		TGTHT510_1553B_data_HYCT[0]=(0x0800|T_APID_HYCT_BACK);
		TGTHT510_1553B_data_HYCT[1]=(HYCT_EPDU_count&0x3fff)|0xc000;//分组标志：11，包序列计数
		TGTHT510_1553B_data_HYCT[2]=0x0043;
		TGTHT510_1553B_data_HYCT[3]=T_SUBSERVICE_HYCT_BACK;
	}
	
	for(i=0;i<=31;i++)
	{
		TGTHT510_1553B_data_HYCT[i+4]=HYCT_data[i];
	}
	
	sum=TGTHT510_collectANDgroup_sum_generate(TGTHT510_1553B_data_HYCT,36);
	TGTHT510_1553B_data_HYCT[36]=(((uint16)sum)<<8)|0x00aa;//字节累加和;
	
}

/******************************************************************************************
**名称：仪表遥测数据组帧
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_collectANDgroup_YB_group(void)
{
	uint16 i;
	uint8 sum;
	
	TGTHT510_collectANDgroup_YB_data_generate();//仪表遥测数据提取
	
	TGTHT510_1553B_data_YB[0]=0x0b02;//包版本：000、包类型：0、数据域头标志：1、APID：0110_000_0010
	
	YB_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(YB_EPDU_count,COUNT_14BIT);
	TGTHT510_1553B_data_YB[1]=(YB_EPDU_count&0x3fff)|0xc000;//分组标志：11，包序列计数
	
	TGTHT510_1553B_data_YB[2]=0x23;//源包长度
	
	TGTHT510_1553B_data_YB[3]=0x0100;//服务类型，服务子类型
	
	TGTHT510_1553B_data_YB[4]=YB_TJ_flag; //推进运行状态
	
	TGTHT510_1553B_data_YB[5]=TGTHT510_supply_ctrl.stage; //补加阶段标志
	
	TGTHT510_1553B_data_YB[6]=TGTHT510_supply_ctrl.state; //补加运行状态标志
	
	TGTHT510_1553B_data_YB[7]=YB_fault_state; //故障处理状态
	
	for(i=0;i<=5;i++)
	{
		TGTHT510_1553B_data_YB[i+8]=YB_pressure_gas_bottle[i];//气瓶出口压力
	}
	
	for(i=0;i<=5;i++)
	{
		TGTHT510_1553B_data_YB[i+14]=YB_remainder_liquid[i];//贮箱剩余量
	}
	
	sum=TGTHT510_collectANDgroup_sum_generate(TGTHT510_1553B_data_YB,20);
	TGTHT510_1553B_data_YB[20]=(((uint16)sum)<<8)|0x00aa;//字节累加和

}

/******************************************************************************************
**名称：转发GNC故检数据组帧
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_collectANDgroup_GNC_group(void)
{
	uint8 sum;
	GNC_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(GNC_EPDU_count,COUNT_14BIT);
	
	TGTHT510_1553B_data_GNC[0]=(0x0800|T_APID_GNC);
	TGTHT510_1553B_data_GNC[1]=(GNC_EPDU_count&0x3fff)|0xc000;//分组标志：11，包序列计数
	TGTHT510_1553B_data_GNC[2]=0x0007;
	TGTHT510_1553B_data_GNC[3]=T_SUBSERVICE_GNC;
	
	TGTHT510_1553B_data_GNC[4]=(((TGTHT510_fault_data_CG_push[4]&0x00ff)<<8)|\
	((TGTHT510_fault_data_CG_push[5]&0xff00)>>8));
	
	TGTHT510_1553B_data_GNC[5]=(((TGTHT510_fault_data_CG_push[5]&0x00f0)<<8)|(0x0fff));
	
	sum=TGTHT510_collectANDgroup_sum_generate(TGTHT510_1553B_data_GNC,6);
	TGTHT510_1553B_data_GNC[6]=(((uint16)sum)<<8)|0x00aa;//字节累加和;
	
}

/******************************************************************************************
**名称：内存下传数据组帧
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_collectANDgroup_MEMORY_group(void)
{
	uint8 sum;
	uint16 i;
	MEMORY_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(MEMORY_EPDU_count,COUNT_14BIT);
	
	TGTHT510_1553B_data_MEMORY[0]=(0x0800|T_APID_MEMORY);
	TGTHT510_1553B_data_MEMORY[1]=(MEMORY_EPDU_count&0x3fff)|0xc000;//分组标志：11，包序列计数
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
	TGTHT510_1553B_data_MEMORY[254]=(((uint16)sum)<<8)|0x00aa;//字节累加和;
}





/******************************************************************************************
**名称：服务请求指令生产
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_collectANDgroup_ask_for_service_generate(uint16 mode)
{
	
	if(mode==ASK_FOR_SERVICE_EQUIMENT_COMMAND)//服务请求，设备管理指令
	{
		TGTHT510_1553B_data_ask_for_service=TGTHT510_1553B_data_ask_for_service|0x0300;
		
	}
	
	else if(mode==ASK_FOR_SERVICE_FAULT_CODE)//服务请求，故障代码
	{
		TGTHT510_1553B_data_ask_for_service=TGTHT510_1553B_data_ask_for_service|0x0003;
		
	}
	
	else if(mode==ASK_FOR_SERVICE_MEMORY)//服务请求，内存下传
	{
		TGTHT510_1553B_data_ask_for_service=TGTHT510_1553B_data_ask_for_service|0x000c;
		
	}
	
	else//输入参数非法
	{
		TGTHT510_1553B_data_ask_for_service=0x0000;
	}
	
	
}


/******************************************************************************************
**名称：设备管理指令生产
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_collectANDgroup_equiment_command_generate(uint8 command)
{
	equiment_command_EPDU_command_data_TypeDef c;//程控指令数据
	equiment_command_EPDU_APID_VCID_TypeDef command_ID;//VCID、APID	
	uint16 i;
	uint16 CRC;
	
	for(i=0;i<=10;i++)
	{
		TGTHT510_1553B_data_equiment_command[i]=0x0000;//初始化清零
	}
	
	c=TGTHT510_collectANDgroup_equiment_command_EPDU_command_generate(command);//程控指令数据
	
	command_ID=TGTHT510_collectANDgroup_equiment_command_APID_VCID_generate(command);//VCID
	
	TGTHT510_1553B_data_equiment_command[0]=0x0001;//版本：00、通过标志：0、控制命令标志：0、空闲：00、航天器标识：0000000001
	
	TGTHT510_1553B_data_equiment_command[1]=(((uint16)command_ID.VCID)<<10)|0x0015;//VCID、帧长固定21
	
	equiment_command_EPDU_count=TGTHT510_collectANDgroup_EPDU_count_generate(equiment_command_EPDU_count,COUNT_8BIT);//帧序列计数
	
	TGTHT510_1553B_data_equiment_command[2]=(equiment_command_EPDU_count<<8)|((uint16)c.command_data[0]);//帧序列号、EPDU包头
	
	TGTHT510_1553B_data_equiment_command[3]=(((uint16)c.command_data[1])<<8)|((uint16)c.command_data[2]);
	
	TGTHT510_1553B_data_equiment_command[4]=(((uint16)c.command_data[3])<<8)|((uint16)c.command_data[4]);
	
	TGTHT510_1553B_data_equiment_command[5]=(((uint16)c.command_data[5])<<8)|((uint16)c.command_data[6]);
	
	TGTHT510_1553B_data_equiment_command[6]=(((uint16)c.command_data[7])<<8)|((uint16)c.command_data[8]);
	
	TGTHT510_1553B_data_equiment_command[7]=(((uint16)c.command_data[9])<<8)|((uint16)c.command_data[10]);
	
	TGTHT510_1553B_data_equiment_command[8]=(((uint16)c.command_data[11])<<8)|((uint16)c.command_data[12]);
	
	TGTHT510_1553B_data_equiment_command[9]=(((uint16)c.command_data[13])<<8)|0x00aa;
	
	CRC=TGTHT510_collectANDgroup_CRC_generate(TGTHT510_1553B_data_equiment_command,10);//CRC校验码
	
	TGTHT510_1553B_data_equiment_command[10]=CRC;
	
	TGTHT510_1553b_transmitcommand_equiment(BU65170_Z);//设备管理指令内容写入1553B缓存区
	
	TGTHT510_1553b_transmitcommand_equiment(BU65170_B);//设备管理指令内容写入1553B缓存区
	
	TGTHT510_collectANDgroup_ask_for_service_generate(ASK_FOR_SERVICE_EQUIMENT_COMMAND);//服务请求
	
}

/******************************************************************************************
**名称：设备管理指令之程控指令码生产
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

equiment_command_EPDU_command_data_TypeDef TGTHT510_collectANDgroup_equiment_command_EPDU_command_generate(uint8 command)
{
	equiment_command_EPDU_command_data_TypeDef a;
	equiment_command_EPDU_APID_VCID_TypeDef command_ID;
	uint16 i,sum_ISO;
	
	for(i=0;i<=13;i++)
	{
		a.command_data[i]=0x00;//初始化清零
	}
	
	command_ID=TGTHT510_collectANDgroup_equiment_command_APID_VCID_generate(command);//APID、VCID
	
	if(command_ID.APID==APID_ERROR)
	{
		return a;//APID错误，返回全零的程控指令码
	}
	
	a.command_data[0]=0x18|((uint8)(command_ID.APID>>8));//程控指令，包版本：000、包类型：1，APID高三位
	
	a.command_data[1]=(uint8)command_ID.APID;//APID低八位
	
	a.command_data[2]=0x00;//分组标志：00，包序列计数:000000
	
	a.command_data[3]=0x00;//包序列计数：00000000
	
	a.command_data[4]=0x00;//包长度，高字节
	
	a.command_data[5]=0x07;//包长度，低字节
	
	a.command_data[6]=0x02;//服务类型
	
	a.command_data[7]=0x02;//服务子类型
	
	a.command_data[8]=equiment_command_code1[command];//设备管理指令内容1
	
	a.command_data[9]=equiment_command_code[command];//设备管理指令内容2
	
	a.command_data[10]=equiment_command_code1[command];//设备管理指令内容1
	
	a.command_data[11]=equiment_command_code[command];//设备管理指令内容2
	
	sum_ISO=TGTHT510_collectANDgroup_equiment_command_ISO_generate(a.command_data,12);
	
	a.command_data[12]=(uint8)(sum_ISO>>8);
	
	a.command_data[13]=(uint8)sum_ISO;
	
	CG_equiment_command[0]=0x0001;//常规遥测，下传航天器标识
	
	CG_equiment_command[1]=command_ID.APID;//常规遥测，下传APID
	
	CG_equiment_command[2]=((uint16)(a.command_data[8])<<8)|((uint16)(a.command_data[9]));
	
	//CG_equiment_command[2]=0x0100|((uint16)a.command_data[9]);//常规遥测，下传指令内容
	
	return a;

}


/******************************************************************************************
**名称：设备管理指令之程控指令APID,VCID生成函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

equiment_command_EPDU_APID_VCID_TypeDef TGTHT510_collectANDgroup_equiment_command_APID_VCID_generate(uint8 command)
{
	equiment_command_EPDU_APID_VCID_TypeDef a;
	
	if(command<=0x35)//主路控制驱动器自锁阀指令
	{
		a.APID=APID_TGTHT520a_VALVE_EQUIMENT_COMMAND;
		a.VCID=VCID_TGTHT520_A_EQUIMENT_COMMAND;
		
	}
	
	else if((command>=0x36)&&(command<=0x6b))//备路控制驱动器自锁阀指令
	{
		a.APID=APID_TGTHT520b_VALVE_EQUIMENT_COMMAND;
		a.VCID=VCID_TGTHT520_B_EQUIMENT_COMMAND;
		
	}
	
	else if((command>=0x6c)&&(command<=0x71))//电机驱动器加断电指令
	{
		a.APID=APID_TGTHT530_POWER_EQUIMENT_COMMAND;
		if((command==0x6c)||(command==0x6f))//电机驱动器A
		{
			a.VCID=VCID_TGTHT530_A_EQUIMENT_COMMAND;
		}
		
		else if((command==0x6d)||(command==0x70))//电机驱动器B
		{
			a.VCID=VCID_TGTHT530_B_EQUIMENT_COMMAND;
		}
		
		else if((command==0x6e)||(command==0x71))//电机驱动器C
		{
			a.VCID=VCID_TGTHT530_C_EQUIMENT_COMMAND;
		}
	}
	
	else if((command>=0x72)&&(command<=0x77))//压气机加断电指令
	{
		a.APID=APID_COMPRESS_POWER_EQUIMENT_COMMAND;
		if((command==0x72)||(command==0x75))//压气机A
		{
			a.VCID=VCID_TGTHT530_A_EQUIMENT_COMMAND;
		}
		
		else if((command==0x73)||(command==0x76))//压气机B
		{
			a.VCID=VCID_TGTHT530_B_EQUIMENT_COMMAND;
		}
		
		else if((command==0x74)||(command==0x77))//压气机C
		{
			a.VCID=VCID_TGTHT530_C_EQUIMENT_COMMAND;
		}
	}
	
	else if((command>=0x78)&&(command<=0x7d))//压气机启动、停机指令
	{
		a.APID=APID_COMPRESS_START_STOP_EQUIMENT_COMMAND;
		if((command==0x78)||(command==0x7b))//压气机A
		{
			a.VCID=VCID_TGTHT530_A_EQUIMENT_COMMAND;
		}
		
		else if((command==0x79)||(command==0x7c))//压气机B
		{
			a.VCID=VCID_TGTHT530_B_EQUIMENT_COMMAND;
		}
		
		else if((command==0x7a)||(command==0x7d))//压气机C
		{
			a.VCID=VCID_TGTHT530_C_EQUIMENT_COMMAND;
		}
		
	}
	
	else if((command>=0x7e)&&(command<=0x7f))//补加阀门加断电指令
	{
		a.APID=APID_VALVE_POWER_EQUIMENT_COMMAND;
		a.VCID=VCID_POWER_EQUIMENT_COMMAND;
		
	}
	
	else//指令编码非法
	{
		a.APID=APID_ERROR;
		a.VCID=VCID_ERROR;
	}
	
	return a;
	
}

/******************************************************************************************
**名称：设备管理指令之程控指令校验码ISO生成函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
**名称：按照字节生成CRC校验码
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
//CRC表示输入的校验码，inputdata为输入字节数据
uint16 TGTHT510_collectANDgroup_Byte_CRC(uint16 CRC,uint8 inputdata)
{
	uint16 in;
	uint16 POLY=0x1021;//生成项，G(X)=X16+X12+X5+1
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
**名称：数组生成CRC校验码
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
//p为字数组的指针，size为数组的长度
uint16 TGTHT510_collectANDgroup_CRC_generate(uint16 *p,uint16 size)
{
	uint16 i;
	uint16 CRC=0x0000;
	uint8 m;
	
	for(i=0;i<=size-1;i++)
	{
		m=(uint8)(p[i]>>8);//字的高字节
		CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,m);
		m=(uint8)p[i];//字的低字节
		CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,m);
		
	}
	
	return CRC;
	
}

/******************************************************************************************
**名称：OC指令与到位信号读取
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
	
	//清除
	
	*(volatile uint32 *)(YK_ADDRESS_BASE+4*(26))=Write_16_to_32(0xaaaa);
	
	CG_place_signal_enable_disable=Read_32_to_16(*(volatile uint32 *)(YK_ADDRESS_BASE+4*32));
	
	for(i=0;i<=3;i++)
	{
		CG_yk_switch_state_data[i]=0x0000; //缓存遥控阀门开关状态，与限位开关状态初始化
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
**名称：拼帧，将high的bit4~11位拼至高字节，将low的bit4~11位拼至低字节
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
**名称：贮箱到位使能与禁止
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
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
**名称：补加系统遥测参数组帧
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_collectANDgroup_CG_supply_group(void)
{
	
	/*
	CG_supply_fault_state_data[0]=TGTHT510_supply_ctrl.errno;
	
	
	//补加阶段字
	CG_supply_name_state_data=TGTHT510_supply_ctrl.stage;
	
	//补加运行状态
	CG_supply_flag=TGTHT510_supply_ctrl.state;
	
	//补加运行步骤
	CG_supply_step=TGTHT510_supply_ctrl.step;
	
	//补加运行命令
	CG_supply_command=TGTHT510_supply_ctrl.command;
	
	//补加过程故障代码
	
	*/
}









