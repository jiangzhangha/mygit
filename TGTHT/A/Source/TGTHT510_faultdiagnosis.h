/**
  ******************************************************************************
  * @file    TGTHT510_faultdiagnosis.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器遥测状态采集与组帧模块头文件
  ******************************************************************************
  */

  
#ifndef __TGTHT510_faultdiagnosis_h
#define __TGTHT510_faultdiagnosis_h 

/*声明结构体类型---------------------------------------------------------*/

typedef struct
{
	uint16 time_count;//计时器计数
	
	uint16 time_flag;//计时器标志
	
	uint16 step;//故检处理步骤
	
	uint16 value[12];//故检处理参数
	
	uint16 valve_htt[5][3];//Htt传感器参数
	
}fault_field_TypeDef;//故障处理属性结构体



typedef struct
{
	uint16 mode;//故障模式
	
	uint16 state;//故障模式使能状态，ENABLE或者DISABLE
	
	uint16 result;//故障发生标志，TRUE或者FALSE
	
	fault_field_TypeDef fault_field1;//故障处理属性1
	
	fault_field_TypeDef fault_field2;//故障处理属性2
	
	fault_field_TypeDef fault_field3;//故障处理属性3
	
	uint16 faultdiagnosis_count;//故障检测判断次数
	
}fault_TypeDef;//故障检测结构体


typedef struct
{
	uint16 mode;//故障模式
	
	uint16 state;//故障模式使能状态，ENABLE或者DISABLE
	
	uint16 result;//故障发生标志，TRUE或者FALSE
	
	uint16 step;//故检处理步骤
	
	uint16 strategy_step;//故障处理策略步骤
	
	uint16 value_fa[4][8];//法兰壁温
	
	uint16 value_va[4][8];//氧阀壁温
	
	uint16 faultdiagnosis_count;//故障检测判断次数
	
}fault_valve_leak_TypeDef;//发动机泄漏故障检测结构体


typedef struct
{
	uint16 fault_mode;
	
	uint16 step;
	
	uint16 compressor_step;//压气机停机程序步骤
	
	uint16 compressor_number;//当前工作的压气机号
	
	uint16 time_count;//计时器计数
	
	uint16 time_flag;//计时器标志
	
}fault_deal_TypeDef;//故障处理全局参数结构体


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
	
	
}fault_deal_is_CPU_A_done_TypeDef;//A机发送的故检执行状况





/*宏定义----------------------------------------------------------------------*/

//故障模式编码
#define FAULT_MODE_PUSH_LEAK_O_GAS1				0x0101		//推进故障，氧1气瓶泄漏
#define FAULT_MODE_PUSH_LEAK_O_GAS2				0x0202		//推进故障，氧2气瓶泄漏
#define FAULT_MODE_PUSH_LEAK_O_GAS3				0x0303		//推进故障，氧3气瓶泄漏

#define FAULT_MODE_PUSH_LEAK_F_GAS1				0x0404		//推进故障，燃1气瓶泄漏
#define FAULT_MODE_PUSH_LEAK_F_GAS2				0x0505		//推进故障，燃2气瓶泄漏
#define FAULT_MODE_PUSH_LEAK_F_GAS3				0x0606		//推进故障，燃3气瓶泄漏

#define FAULT_MODE_PUSH_OVER_O_TANK1			0x0707		//推进故障，氧1贮箱超压
#define FAULT_MODE_PUSH_OVER_O_TANK2			0x0808		//推进故障，氧2贮箱超压
#define FAULT_MODE_PUSH_OVER_O_TANK3			0x0909		//推进故障，氧3贮箱超压

#define FAULT_MODE_PUSH_OVER_F_TANK1			0x0a0a		//推进故障，燃1贮箱超压
#define FAULT_MODE_PUSH_OVER_F_TANK2			0x0b0b		//推进故障，燃2贮箱超压
#define FAULT_MODE_PUSH_OVER_F_TANK3			0x0c0c		//推进故障，燃3贮箱超压

#define FAULT_MODE_PUSH_LEAK_B_MAIN				0x0d0d		//推进故障，主份姿控发动机控制阀门泄漏
#define FAULT_MODE_PUSH_LEAK_B_LESS				0x0e0e		//推进故障，备份姿控发动机控制阀门泄漏
#define FAULT_MODE_PUSH_LEAK_C_ALL				0x0f0f		//推进故障，C组姿控发动机控制阀门泄漏
#define FAULT_MODE_PUSH_LEAK_A_MAIN				0x1010		//推进故障，A组主份姿控发动机控制阀门泄漏
#define FAULT_MODE_PUSH_LEAK_A_LESS				0x1111		//推进故障，A组备份姿控发动机控制阀门泄漏

#define FAULT_MODE_PUSH_LEAK_O_TANK1			0x1212		//推进故障，氧1贮箱泄漏
#define FAULT_MODE_PUSH_LEAK_O_TANK2			0x1313		//推进故障，氧2贮箱泄漏
#define FAULT_MODE_PUSH_LEAK_O_TANK3			0x1414		//推进故障，氧3贮箱泄漏

#define FAULT_MODE_PUSH_LEAK_F_TANK1			0x1515		//推进故障，燃1贮箱泄漏
#define FAULT_MODE_PUSH_LEAK_F_TANK2			0x1616		//推进故障，燃2贮箱泄漏
#define FAULT_MODE_PUSH_LEAK_F_TANK3			0x1717		//推进故障，燃3贮箱泄漏

#define FAULT_MODE_SUPPLY_COOLER_ZZ				0x1818		//补加故障，主份液冷主泵故障
#define FAULT_MODE_SUPPLY_COOLER_ZB				0x1919		//补加故障，主份液冷备泵故障
#define FAULT_MODE_SUPPLY_COOLER_BZ				0x1a1a		//补加故障，备份液冷主泵故障
#define FAULT_MODE_SUPPLY_COOLER_BB				0x1b1b		//补加故障，备份液冷备泵故障

#define FAULT_MODE_SUPPLY_LEAK_COOLER_Z			0x1c1c		//补加故障，主份液冷泄漏
#define FAULT_MODE_SUPPLY_LEAK_COOLER_B			0x1d1d		//补加故障，备份液冷泄漏

#define FAULT_MODE_SUPPLY_OVER_COMP_A_IN		0x1e1e		//补加故障，压气机A入口超压
#define FAULT_MODE_SUPPLY_OVER_COMP_B_IN		0x1f1f		//补加故障，压气机B入口超压
#define FAULT_MODE_SUPPLY_OVER_COMP_C_IN		0x2020		//补加故障，压气机C入口超压

#define FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR		0x2121		//补加故障，压气机A电机腔超压
#define FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR		0x2222		//补加故障，压气机B电机腔超压
#define FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR		0x2323		//补加故障，压气机C电机腔超压

#define FAULT_MODE_SUPPLY_COMP_A_HOT			0x2424		//补加故障，压气机A超温
#define FAULT_MODE_SUPPLY_COMP_B_HOT			0x2525		//补加故障，压气机B超温
#define FAULT_MODE_SUPPLY_COMP_C_HOT			0x2626		//补加故障，压气机C超温

#define FAULT_MODE_SUPPLY_OVER_O_TANK1			0x2727		//补加故障，氧1补加贮箱超压
#define FAULT_MODE_SUPPLY_OVER_O_TANK2			0x2828		//补加故障，氧2补加贮箱超压
#define FAULT_MODE_SUPPLY_OVER_O_TANK3			0x2929		//补加故障，氧3补加贮箱超压

#define FAULT_MODE_SUPPLY_OVER_F_TANK1			0x2a2a		//补加故障，燃1补加贮箱超压
#define FAULT_MODE_SUPPLY_OVER_F_TANK2			0x2b2b		//补加故障，燃2补加贮箱超压
#define FAULT_MODE_SUPPLY_OVER_F_TANK3			0x2c2c		//补加故障，燃3补加贮箱超压

#define FAULT_MODE_SUPPLY_COMP_A_BREAK			0x2d2d		//补加故障，压气机A膜片破裂
#define FAULT_MODE_SUPPLY_COMP_B_BREAK			0x2e2e		//补加故障，压气机B膜片破裂
#define FAULT_MODE_SUPPLY_COMP_C_BREAK			0x2f2f		//补加故障，压气机C膜片破裂

#define FAULT_MODE_SUPPLY_LEAK_O_GAS1			0x3030		//补加故障，氧1气瓶泄漏
#define FAULT_MODE_SUPPLY_LEAK_O_GAS2			0x3131		//补加故障，氧2气瓶泄漏
#define FAULT_MODE_SUPPLY_LEAK_O_GAS3			0x3232		//补加故障，氧3气瓶泄漏

#define FAULT_MODE_SUPPLY_LEAK_F_GAS1			0x3333		//补加故障，燃1气瓶泄漏
#define FAULT_MODE_SUPPLY_LEAK_F_GAS2			0x3434		//补加故障，燃2气瓶泄漏
#define FAULT_MODE_SUPPLY_LEAK_F_GAS3			0x3535		//补加故障，燃3气瓶泄漏

#define FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1		0x3636		//补加故障，氧1贮箱补加液路泄漏
#define FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2		0x3737		//补加故障，氧2贮箱补加液路泄漏
#define FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3		0x3838		//补加故障，氧3贮箱补加液路泄漏

#define FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1		0x3939		//补加故障，燃1贮箱补加液路泄漏
#define FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2		0x3a3a		//补加故障，燃2贮箱补加液路泄漏
#define FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3		0x3b3b		//补加故障，燃3贮箱补加液路泄漏

#define FAULT_MODE_SUPPLY_INTERFACE_O_TEMP		0x3c3c		//补加故障，氧吹除口温度异常
#define FAULT_MODE_SUPPLY_INTERFACE_F_TEMP		0x3d3d		//补加故障，燃吹除口温度异常

#define FAULT_MODE_SUPPLY_IN_LEAK_O_Z			0x3e3e		//补加故障，氧主补加管路内漏
#define FAULT_MODE_SUPPLY_IN_LEAK_O_B			0x3f3f		//补加故障，氧备补加管路内漏
#define FAULT_MODE_SUPPLY_IN_LEAK_F_Z			0x4040		//补加故障，燃主补加管路内漏
#define FAULT_MODE_SUPPLY_IN_LEAK_F_B			0x4141		//补加故障，燃备补加管路内漏

#define FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1	0x4242		//补加故障，前向燃1浮动断接器温度异常
#define FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2	0x4343		//补加故障，前向燃2浮动断接器温度异常
#define FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1	0x4444		//补加故障，前向氧1浮动断接器温度异常
#define FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2	0x4545		//补加故障，前向氧2浮动断接器温度异常

#define FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1	0x4646		//补加故障，后向燃1浮动断接器温度异常
#define FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2	0x4747		//补加故障，后向燃2浮动断接器温度异常
#define FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1	0x4848		//补加故障，后向氧1浮动断接器温度异常
#define FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2	0x4949		//补加故障，后向氧2浮动断接器温度异常

#define FAULT_MODE_SUPPLY_KA_O_TANK1			0x4a4a		//补加故障，氧1贮箱卡滞
#define FAULT_MODE_SUPPLY_KA_O_TANK2			0x4b4b		//补加故障，氧2贮箱卡滞
#define FAULT_MODE_SUPPLY_KA_O_TANK3			0x4c4c		//补加故障，氧3贮箱卡滞

#define FAULT_MODE_SUPPLY_KA_F_TANK1			0x4d4d		//补加故障，燃1贮箱卡滞
#define FAULT_MODE_SUPPLY_KA_F_TANK2			0x4e4e		//补加故障，燃2贮箱卡滞
#define FAULT_MODE_SUPPLY_KA_F_TANK3			0x4f4f		//补加故障，燃3贮箱卡滞

#define FAULT_MODE_SUPPLY_TGTHT530				0x5050		//补加故障，电机驱动器故障

#define FAULT_MODE_PUSH_ALL						0xbfbf		//全部补加故障，推进部分
#define FAULT_MODE_SUPPLY_ALL					0xcfcf		//全部补加故障，补加部分

#define FAULT_MODE_ALL							0xdfdf		//全部补加
#define FAULT_MODE_NONE							0xefef		//无故障


//故障状态
#define FAULT_STATE_DISABLE						0x0101		//故检状态，不当班
#define FAULT_STATE_NORMAL						0x0202		//故检状态，正常
#define FAULT_STATE_ABNORMAL					0x0303		//故检状态，异常

#define FAULT_BIT15_12_SET						0x0404		//bit15-12设置
#define FAULT_BIT11_08_SET						0x0505		//bit11-8设置
#define FAULT_BIT07_04_SET						0x0606		//bit7-4设置
#define FAULT_BIT03_00_SET						0x0707		//bit3-0设置



//故障检测步骤
#define FAULT_STEP_START	0x0000			//故障检测步骤-开始
#define FAULT_STEP_NO1		0x0101			//故障检测步骤1
#define FAULT_STEP_NO2		0x0202			//故障检测步骤2
#define FAULT_STEP_NO3		0x0303			//故障检测步骤3
#define FAULT_STEP_NO4		0x0404			//故障检测步骤4
#define FAULT_STEP_NO5		0x0505			//故障检测步骤5
#define FAULT_STEP_NO6		0x0606			//故障检测步骤6
#define FAULT_STEP_NO7		0x0707			//故障检测步骤7
#define FAULT_STEP_NO8		0x0808			//故障检测步骤8
#define FAULT_STEP_NO9		0x0909			//故障检测步骤9
#define FAULT_STEP_NO10		0x0a0a			//故障检测步骤10
#define FAULT_STEP_NO11		0x0b0b			//故障检测步骤11
#define FAULT_STEP_NO12		0x0c0c			//故障检测步骤12
#define FAULT_STEP_NO13		0x0d0d			//故障检测步骤13
#define FAULT_STEP_NO14		0x0e0e			//故障检测步骤14
#define FAULT_STEP_NO15		0x0f0f			//故障检测步骤15
#define FAULT_STEP_NO16		0x1010			//故障检测步骤16
#define FAULT_STEP_NO17		0x1111			//故障检测步骤17
#define FAULT_STEP_NO18		0x1212			//故障检测步骤18
#define FAULT_STEP_NO19		0x1313			//故障检测步骤19
#define FAULT_STEP_NO20		0x1414			//故障检测步骤20
#define FAULT_STEP_END		0xfefe			//故障检测步骤-结束
#define FAULT_STEP_NONE		0xfdfd			//故障检测步骤-无

//故障策略步骤
#define FAULT_STRATEGY_STEP_START 	0x0000  //故障策略步骤-开始
#define FAULT_STRATEGY_STEP_NO1 	0x0101  //故障策略步骤1
#define FAULT_STRATEGY_STEP_NO2 	0x0202  //故障策略步骤2
#define FAULT_STRATEGY_STEP_NO3 	0x0303  //故障策略步骤3
#define FAULT_STRATEGY_STEP_NO4 	0x0404  //故障策略步骤4
#define FAULT_STRATEGY_STEP_NO5 	0x0505  //故障策略步骤5
#define FAULT_STRATEGY_STEP_NO6 	0x0606  //故障策略步骤6
#define FAULT_STRATEGY_STEP_NO7 	0x0707  //故障策略步骤7

#define FAULT_STRATEGY_STEP_END 	0xfefe  //故障策略步骤-结束
#define FAULT_STRATEGY_STEP_NONE 	0xfdfd  //故障策略步骤-无

//故障编号

#define FAULT_O_GAS1		0x0101			//故障检测--氧1气瓶
#define FAULT_O_GAS2		0x0202			//故障检测--氧2气瓶
#define FAULT_O_GAS3		0x0303			//故障检测--氧3气瓶

#define FAULT_F_GAS1		0x0404			//故障检测--燃1气瓶
#define FAULT_F_GAS2		0x0505			//故障检测--燃2气瓶
#define FAULT_F_GAS3		0x0606			//故障检测--燃3气瓶

#define FAULT_O_TANK1		0x0707			//故障检测--氧1贮箱
#define FAULT_O_TANK2		0x0808			//故障检测--氧2贮箱
#define FAULT_O_TANK3		0x0909			//故障检测--氧3贮箱

#define FAULT_F_TANK1		0x0a0a			//故障检测--燃1贮箱
#define FAULT_F_TANK2		0x0b0b			//故障检测--燃2贮箱
#define FAULT_F_TANK3		0x0c0c			//故障检测--燃3贮箱

#define	FAULT_B_MAIN_LEAK	0x0d0d			//故障检测--B组主份发动机泄漏
#define	FAULT_B_LESS_LEAK	0x0e0e			//故障检测--B组备份发动机泄漏
#define	FAULT_A_MAIN_LEAK	0x0f0f			//故障检测--A组主份发动机泄漏
#define	FAULT_A_LESS_LEAK	0x1010			//故障检测--A组备份发动机泄漏
#define	FAULT_C_ALL_LEAK	0x1111			//故障检测--C组发动机泄漏

#define FAULT_COOLER_ZZ		0x1212			//故障检测--主份液冷主泵
#define FAULT_COOLER_ZB		0x1313			//故障检测--主份液冷备泵
#define FAULT_COOLER_BZ		0x1414			//故障检测--备份液冷主泵
#define FAULT_COOLER_BB		0x1515			//故障检测--备份液冷备泵

#define FAULT_COOLER_Z		0x1616			//故障检测--主份液冷泄漏
#define FAULT_COOLER_B		0x1717			//故障检测--备份液冷泄漏

#define FAULT_COMPRESSOR_A_IN_OVER		0x1818 	//故障检测--压气机A入口超压
#define FAULT_COMPRESSOR_B_IN_OVER		0x1919 	//故障检测--压气机B入口超压
#define FAULT_COMPRESSOR_C_IN_OVER		0x1a1a 	//故障检测--压气机C入口超压

#define FAULT_COMPRESSOR_A_MOTOR_OVER	0x1b1b 	//故障检测--压气机A电机腔超压
#define FAULT_COMPRESSOR_B_MOTOR_OVER	0x1c1c 	//故障检测--压气机B电机腔超压
#define FAULT_COMPRESSOR_C_MOTOR_OVER	0x1d1d 	//故障检测--压气机C电机腔超压

#define FAULT_COMPRESSOR_A_HOT			0x1e1e 	//故障检测--压气机A超温
#define FAULT_COMPRESSOR_B_HOT			0x1f1f 	//故障检测--压气机B超温
#define FAULT_COMPRESSOR_C_HOT			0x2020 	//故障检测--压气机C超温

#define FAULT_COMPRESSOR_A_BREAK		0x2121 	//故障检测--压气机A膜片破裂
#define FAULT_COMPRESSOR_B_BREAK		0x2222 	//故障检测--压气机B膜片破裂
#define FAULT_COMPRESSOR_C_BREAK		0x2323 	//故障检测--压气机C膜片破裂

#define FAULT_INTERFACE_O				0x2424	//故障检测--氧吹除口
#define FAULT_INTERFACE_F				0x2525	//故障检测--氧吹除口

#define FAULT_IN_LEAK_O_Z				0x2626  //故障检测--氧主补加管路内漏
#define FAULT_IN_LEAK_O_B				0x2727  //故障检测--氧备补加管路内漏
#define FAULT_IN_LEAK_F_Z				0x2828  //故障检测--燃主补加管路内漏
#define FAULT_IN_LEAK_F_B				0x2929  //故障检测--燃备补加管路内漏

#define FAULT_TEMPERATURE_FORE_F1		0x2f2f  //故障检测--前向燃1浮动断接器温度异常
#define FAULT_TEMPERATURE_FORE_F2		0x3030  //故障检测--前向燃2浮动断接器温度异常
#define FAULT_TEMPERATURE_FORE_O1		0x3131  //故障检测--前向氧1浮动断接器温度异常
#define FAULT_TEMPERATURE_FORE_O2		0x3232  //故障检测--前向氧2浮动断接器温度异常

#define FAULT_TEMPERATURE_BACK_F1		0x3333  //故障检测--后向燃1浮动断接器温度异常
#define FAULT_TEMPERATURE_BACK_F2		0x3434  //故障检测--后向燃2浮动断接器温度异常
#define FAULT_TEMPERATURE_BACK_O1		0x3535  //故障检测--后向氧1浮动断接器温度异常
#define FAULT_TEMPERATURE_BACK_O2		0x3636  //故障检测--后向氧2浮动断接器温度异常

#define FAULT_COMPRESSOR_A				0x3737	//故障处理--压气机A故障
#define FAULT_COMPRESSOR_B				0x3838	//故障处理--压气机B故障
#define FAULT_COMPRESSOR_C				0x3939	//故障处理--压气机C故障

#define FAULT_COMPRESSOR_N				0xfefe	//故障处理--无压气机正在工作


#define FAULT_FIELD1					0x0101
#define FAULT_FIELD2					0x0202
#define FAULT_FIELD3					0x0303

#define FAULT_IN_LEAK					0x0101
#define FAULT_PIPE_LEAK					0x0202



//常量定义

#define MAX_FAULTDIAGNOSIS_COUNT			0x0003//最大故障检测判断次数

#define FAULT_CONST_PRESSURE_0E1			0x0009//差值，气瓶泄漏阈值，0.1MPa（待修改）
#define FAULT_CONST_PRESSURE_0E2			0x0012//差值，气瓶补加液路泄漏阈值，0.2MPa（待修改）
#define FAULT_CONST_PRESSURE_0E4			0x0025//差值，补加管路内漏阈值，0.4MPa（待修改）

#define FAULT_CONST_PRESSURE_0E14			0x000d//差值，气瓶泄漏阈值，0.14MPa（待修改）
#define FAULT_CONST_PRESSURE_MIN_GAS		0x03dd//绝对值，气瓶泄漏阈值，最小气瓶压力值9MPa（待修改）

#define FAULT_CONST_PRESSURE_OVER			0x0150//贮箱超压阈值，1.95MPa（待修改）
#define FAULT_CONST_HTT_ONE					0x0007//贮箱泄漏阈值，默认为1升（待修改）

#define FAULT_CONST_COOLER					0x0625//液冷泵转速6000转每分钟（待修改）

#define FAULT_CONST_COOLER_LEAK				0x0003//液冷模块泄漏，1kp（待修改）

#define FAULT_CONST_COMPRESSOR_OVER			0x00c1//压气机超压，0.4MPa（待修改）
#define FAULT_CONST_COMPRESSOR_HOT			0x029c//压气机超温，42摄氏度（待修改）

#define FAULT_CONST_COMPRESSOR_BREAK		0x00f8//压气机膜片破裂，1MPa（待修改）


//函数声明

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

void TGTHT510_faultdiagnosis_push_set_stage_launch(void);		//发射段		推进故检使能禁止设置
void TGTHT510_faultdiagnosis_push_set_stage_orbit(void);		//变轨段		推进故检使能禁止设置
void TGTHT510_faultdiagnosis_push_set_stage_polling(void);		//巡检段		推进故检使能禁止设置
void TGTHT510_faultdiagnosis_push_set_stage_gas(void);			//压气机补气段	推进故检使能禁止设置
void TGTHT510_faultdiagnosis_push_set_stage_comp(void);			//补加抽气段	推进故检使能禁止设置
void TGTHT510_faultdiagnosis_push_set_stage_flow(void);			//补加流动段	推进故检使能禁止设置
void TGTHT510_faultdiagnosis_push_set_stage_repre(void);		//补加复压段	推进故检使能禁止设置
void TGTHT510_faultdiagnosis_push_set_stage_other(void);		//补加其他段	推进故检使能禁止设置
void TGTHT510_faultdiagnosis_push_set_stage_run(void);			//运行段		推进故检使能禁止设置


void TGTHT510_faultdiagnosis_supply_set_stage_launch(void);		//发射段		补加故检使能禁止设置
void TGTHT510_faultdiagnosis_supply_set_stage_orbit(void);		//变轨段		补加故检使能禁止设置
void TGTHT510_faultdiagnosis_supply_set_stage_polling(void);	//巡检段		补加故检使能禁止设置
void TGTHT510_faultdiagnosis_supply_set_stage_gas(void);		//压气机补气段	补加故检使能禁止设置
void TGTHT510_faultdiagnosis_supply_set_stage_comp(void);		//补加抽气段	补加故检使能禁止设置
void TGTHT510_faultdiagnosis_supply_set_stage_flow(void);		//补加流动段	补加故检使能禁止设置
void TGTHT510_faultdiagnosis_supply_set_stage_repre(void);		//补加复压段	补加故检使能禁止设置
void TGTHT510_faultdiagnosis_supply_set_stage_other(void);		//补加其他段	补加故检使能禁止设置
void TGTHT510_faultdiagnosis_supply_set_stage_run(void);		//运行段		补加故检使能禁止设置



#endif




