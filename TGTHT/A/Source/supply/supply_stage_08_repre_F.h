/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器补加流程主程序头文件
  ******************************************************************************
  */
 
#ifndef __supply_stage_08_repre_f_h
#define __supply_stage_08_repre_f_h
 

/*声明结构体类型--------------------------------------------------------------*/



/*宏定义---------------------------------------------------------------------------*/

#define		REPRE_TANK_F				0x1234//燃贮箱复压
#define		REPRE_TANK_O				0x4321//氧贮箱复压

//步骤step------------------------------------------------------------------------

#define 	STEP_08_F_REPRE_TANK_NUMBER						0x0001//判断复压的贮箱数量

//---------------------一个燃贮箱复压---------------------------------------------

#define 	STEP_08_F_REPRE_1TANK_LVT_VALVE_ON				0x0002//贮箱增压，打开高压自锁阀
#define 	STEP_08_F_REPRE_1TANK_IS_REPRE_OVER				0x0003//通过压力与时间判断复压是否结束
#define 	STEP_08_F_REPRE_1TANK_LVT_VALVE_OFF				0x0004//复压结束，关闭高压自锁阀
#define 	STEP_08_F_REPRE_1TANK_OUT_TANK_VALVE_ON			0x0005//开贮箱出口阀门
#define 	STEP_08_F_REPRE_1TANK_DELAY						0x0006//延时等待
#define 	STEP_08_F_REPRE_1TANK_IS_TANK_PRESSURE			0x0007//判断贮箱压力的稳定性

//---------------------两个燃贮箱复压---------------------------------------------
#define 	STEP_08_F_REPRE_2TANK_TANK1_LVT_VALVE_ON		0x0008//贮箱增压，打开高压自锁阀，第一个贮箱
#define 	STEP_08_F_REPRE_2TANK_TANK1_IS_REPRE_OVER		0x0009//通过压力与时间判断复压是否结束，第一个贮箱
#define 	STEP_08_F_REPRE_2TANK_TANK1_LVT_VALVE_OFF		0x000a//复压结束，关闭高压自锁阀，第一个贮箱
#define 	STEP_08_F_REPRE_2TANK_TANK1_OUT_TANK_VALVE_ON	0x000b//开贮箱出口阀门，第一个贮箱
#define 	STEP_08_F_REPRE_2TANK_TANK1_DELAY				0x000c//延时等待，第一个贮箱
#define 	STEP_08_F_REPRE_2TANK_TANK1_IS_TANK_PRESSURE	0x000d//判断贮箱压力的稳定性，第一个贮箱

#define 	STEP_08_F_REPRE_2TANK_TANK2_LVT_VALVE_ON		0x000e//贮箱增压，打开高压自锁阀，第二个贮箱
#define 	STEP_08_F_REPRE_2TANK_TANK2_IS_REPRE_OVER		0x000f//通过压力与时间判断复压是否结束，第二个贮箱
#define 	STEP_08_F_REPRE_2TANK_TANK2_LVT_VALVE_OFF		0x0010//复压结束，关闭高压自锁阀，第二个贮箱
#define 	STEP_08_F_REPRE_2TANK_TANK2_OUT_TANK_VALVE_ON	0x0011//开贮箱出口阀门，第二个贮箱
#define 	STEP_08_F_REPRE_2TANK_TANK2_DELAY				0x0012//延时等待，第二个贮箱
#define 	STEP_08_F_REPRE_2TANK_TANK2_IS_TANK_PRESSURE	0x0013//判断贮箱压力的稳定性，第二个贮箱


//命令command---------------------------------------------------------------------

//判断复压的贮箱数量
#define		COMMAND_08_0001_F_REPRE_TANK_NUMBER						0x0001

//---------------------一个燃贮箱复压---------------------------------------------

//贮箱增压，打开高压自锁阀
#define		COMMAND_08_0001_F_REPRE_1TANK_LVT_VALVE_ON				0x0002
#define		COMMAND_08_0002_F_REPRE_1TANK_1MIN_START_NO1			0x0003
#define		COMMAND_08_0003_F_REPRE_1TANK_IS_1MIN_NO1				0x0004
#define		COMMAND_08_0004_F_REPRE_1TANK_IS_LVT_VALVE_ON			0x0005

//通过压力与时间判断复压是否结束
#define		COMMAND_08_0001_F_REPRE_1TANK_IS_REPRE_OVER				0x0006

//复压结束，关闭高压自锁阀
#define		COMMAND_08_0001_F_REPRE_1TANK_LVT_VALVE_OFF				0x0007
#define		COMMAND_08_0002_F_REPRE_1TANK_1MIN_START_NO2			0x0008
#define		COMMAND_08_0003_F_REPRE_1TANK_IS_1MIN_NO2				0x0009
#define		COMMAND_08_0004_F_REPRE_1TANK_IS_LVT_VALVE_OFF			0x000a

//开贮箱出口阀门
#define		COMMAND_08_0001_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO1		0x000b
#define		COMMAND_08_0002_F_REPRE_1TANK_1MIN_START_NO3			0x000c
#define		COMMAND_08_0003_F_REPRE_1TANK_IS_1MIN_NO3				0x000d
#define		COMMAND_08_0004_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO1	0x000e
#define		COMMAND_08_0005_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO2		0x000f
#define		COMMAND_08_0006_F_REPRE_1TANK_1MIN_START_NO4			0x0010
#define		COMMAND_08_0007_F_REPRE_1TANK_IS_1MIN_NO4				0x0011
#define		COMMAND_08_0008_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO2	0x0012


//延时等待
#define		COMMAND_08_0001_F_REPRE_1TANK_DELAY_START_NO1			0x0013
#define		COMMAND_08_0002_F_REPRE_1TANK_IS_DELAY_NO1				0x0014


//判断贮箱压力的稳定性
#define		COMMAND_08_0001_F_REPRE_1TANK_TANK_PRESSURE_NO1			0x0015
#define		COMMAND_08_0002_F_REPRE_1TANK_5SEC_START_NO1			0x0016
#define		COMMAND_08_0003_F_REPRE_1TANK_IS_5SEC_NO1				0x0017
#define		COMMAND_08_0004_F_REPRE_1TANK_TANK_PRESSURE_NO2			0x0018
#define		COMMAND_08_0005_F_REPRE_1TANK_5SEC_START_NO2			0x0019
#define		COMMAND_08_0006_F_REPRE_1TANK_IS_5SEC_NO2				0x001a
#define		COMMAND_08_0007_F_REPRE_1TANK_TANK_PRESSURE_NO3			0x001b
#define		COMMAND_08_0008_F_REPRE_1TANK_5SEC_START_NO3			0x001c
#define		COMMAND_08_0009_F_REPRE_1TANK_IS_5SEC_NO3				0x001d
#define		COMMAND_08_0010_F_REPRE_1TANK_TANK_PRESSURE_NO4			0x001e
#define		COMMAND_08_0011_F_REPRE_1TANK_5SEC_START_NO4			0x001f
#define		COMMAND_08_0012_F_REPRE_1TANK_IS_5SEC_NO4				0x0020
#define		COMMAND_08_0013_F_REPRE_1TANK_TANK_PRESSURE_NO5			0x0021
#define		COMMAND_08_0014_F_REPRE_1TANK_5SEC_START_NO5			0x0022
#define		COMMAND_08_0015_F_REPRE_1TANK_IS_5SEC_NO5				0x0023
#define		COMMAND_08_0016_F_REPRE_1TANK_TANK_PRESSURE_NO6			0x0024
#define		COMMAND_08_0017_F_REPRE_1TANK_5SEC_START_NO6			0x0025
#define		COMMAND_08_0018_F_REPRE_1TANK_IS_5SEC_NO6				0x0026
#define		COMMAND_08_0019_F_REPRE_1TANK_TANK_PRESSURE_NO7			0x0027
#define		COMMAND_08_0020_F_REPRE_1TANK_IS_PRESSURE_STABLE		0x0028


//---------------------两个燃贮箱复压---------------------------------------------

//贮箱增压，打开高压自锁阀，第一个贮箱
#define		COMMAND_08_0001_F_REPRE_2TANK_TANK1_LVT_VALVE_ON			0x0029
#define		COMMAND_08_0002_F_REPRE_2TANK_TANK1_1MIN_START_NO1			0x002a
#define		COMMAND_08_0003_F_REPRE_2TANK_TANK1_IS_1MIN_NO1				0x002b
#define		COMMAND_08_0004_F_REPRE_2TANK_TANK1_IS_LVT_VALVE_ON			0x002c

//通过压力与时间判断复压是否结束，第一个贮箱
#define		COMMAND_08_0001_F_REPRE_2TANK_TANK1_IS_REPRE_OVER			0x002d

//复压结束，关闭高压自锁阀，第一个贮箱
#define		COMMAND_08_0001_F_REPRE_2TANK_TANK1_LVT_VALVE_OFF			0x002e
#define		COMMAND_08_0002_F_REPRE_2TANK_TANK1_1MIN_START_NO2			0x002f
#define		COMMAND_08_0003_F_REPRE_2TANK_TANK1_IS_1MIN_NO2				0x0030
#define		COMMAND_08_0004_F_REPRE_2TANK_TANK1_IS_LVT_VALVE_OFF		0x0031

//开贮箱出口阀门，第一个贮箱
#define		COMMAND_08_0001_F_REPRE_2TANK_TANK1_OUT_TANK_VALVE_ON_NO1		0x0032
#define		COMMAND_08_0002_F_REPRE_2TANK_TANK1_1MIN_START_NO3				0x0033
#define		COMMAND_08_0003_F_REPRE_2TANK_TANK1_IS_1MIN_NO3					0x0034
#define		COMMAND_08_0004_F_REPRE_2TANK_TANK1_IS_OUT_TANK_VALVE_ON_NO1	0x0035
#define		COMMAND_08_0005_F_REPRE_2TANK_TANK1_OUT_TANK_VALVE_ON_NO2		0x0036
#define		COMMAND_08_0006_F_REPRE_2TANK_TANK1_1MIN_START_NO4				0x0037
#define		COMMAND_08_0007_F_REPRE_2TANK_TANK1_IS_1MIN_NO4					0x0038
#define		COMMAND_08_0008_F_REPRE_2TANK_TANK1_IS_OUT_TANK_VALVE_ON_NO2	0x0039

//延时等待，第一个贮箱
#define		COMMAND_08_0001_F_REPRE_2TANK_TANK1_DELAY_START_NO1			0x003a
#define		COMMAND_08_0002_F_REPRE_2TANK_TANK1_IS_DELAY_NO1			0x003b


//判断贮箱压力的稳定性，第一个贮箱
#define		COMMAND_08_0001_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO1		0x003c
#define		COMMAND_08_0002_F_REPRE_2TANK_TANK1_5SEC_START_NO1			0x003d
#define		COMMAND_08_0003_F_REPRE_2TANK_TANK1_IS_5SEC_NO1				0x003e
#define		COMMAND_08_0004_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO2		0x003f
#define		COMMAND_08_0005_F_REPRE_2TANK_TANK1_5SEC_START_NO2			0x0040
#define		COMMAND_08_0006_F_REPRE_2TANK_TANK1_IS_5SEC_NO2				0x0041
#define		COMMAND_08_0007_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO3		0x0042
#define		COMMAND_08_0008_F_REPRE_2TANK_TANK1_5SEC_START_NO3			0x0043
#define		COMMAND_08_0009_F_REPRE_2TANK_TANK1_IS_5SEC_NO3				0x0044
#define		COMMAND_08_0010_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO4		0x0045
#define		COMMAND_08_0011_F_REPRE_2TANK_TANK1_5SEC_START_NO4			0x0046
#define		COMMAND_08_0012_F_REPRE_2TANK_TANK1_IS_5SEC_NO4				0x0047
#define		COMMAND_08_0013_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO5		0x0048
#define		COMMAND_08_0014_F_REPRE_2TANK_TANK1_5SEC_START_NO5			0x0049
#define		COMMAND_08_0015_F_REPRE_2TANK_TANK1_IS_5SEC_NO5				0x004a
#define		COMMAND_08_0016_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO6		0x004b
#define		COMMAND_08_0017_F_REPRE_2TANK_TANK1_5SEC_START_NO6			0x004c
#define		COMMAND_08_0018_F_REPRE_2TANK_TANK1_IS_5SEC_NO6				0x004d
#define		COMMAND_08_0019_F_REPRE_2TANK_TANK1_TANK_PRESSURE_NO7		0x004e
#define		COMMAND_08_0020_F_REPRE_2TANK_TANK1_IS_PRESSURE_STABLE		0x004f



//贮箱增压，打开高压自锁阀，第二个贮箱
#define		COMMAND_08_0001_F_REPRE_2TANK_TANK2_LVT_VALVE_ON			0x0050
#define		COMMAND_08_0002_F_REPRE_2TANK_TANK2_1MIN_START_NO1			0x0051
#define		COMMAND_08_0003_F_REPRE_2TANK_TANK2_IS_1MIN_NO1				0x0052
#define		COMMAND_08_0004_F_REPRE_2TANK_TANK2_IS_LVT_VALVE_ON			0x0053

//通过压力与时间判断复压是否结束，第二个贮箱
#define		COMMAND_08_0001_F_REPRE_2TANK_TANK2_IS_REPRE_OVER			0x0054

//复压结束，关闭高压自锁阀，第二个贮箱
#define		COMMAND_08_0001_F_REPRE_2TANK_TANK2_LVT_VALVE_OFF			0x0055
#define		COMMAND_08_0002_F_REPRE_2TANK_TANK2_1MIN_START_NO2			0x0056
#define		COMMAND_08_0003_F_REPRE_2TANK_TANK2_IS_1MIN_NO2				0x0057
#define		COMMAND_08_0004_F_REPRE_2TANK_TANK2_IS_LVT_VALVE_OFF		0x0058

//开贮箱出口阀门，第二个贮箱
#define		COMMAND_08_0001_F_REPRE_2TANK_TANK2_OUT_TANK_VALVE_ON_NO1		0x0059
#define		COMMAND_08_0002_F_REPRE_2TANK_TANK2_1MIN_START_NO3				0x005a
#define		COMMAND_08_0003_F_REPRE_2TANK_TANK2_IS_1MIN_NO3					0x005b
#define		COMMAND_08_0004_F_REPRE_2TANK_TANK2_IS_OUT_TANK_VALVE_ON_NO1	0x005c
#define		COMMAND_08_0005_F_REPRE_2TANK_TANK2_OUT_TANK_VALVE_ON_NO2		0x005d
#define		COMMAND_08_0006_F_REPRE_2TANK_TANK2_1MIN_START_NO4				0x005e
#define		COMMAND_08_0007_F_REPRE_2TANK_TANK2_IS_1MIN_NO4					0x005f
#define		COMMAND_08_0008_F_REPRE_2TANK_TANK2_IS_OUT_TANK_VALVE_ON_NO2	0x0060


//延时等待，第二个贮箱
#define		COMMAND_08_0001_F_REPRE_2TANK_TANK2_DELAY_START_NO1			0x0061
#define		COMMAND_08_0002_F_REPRE_2TANK_TANK2_IS_DELAY_NO1			0x0062


//判断贮箱压力的稳定性，第二个贮箱
#define		COMMAND_08_0001_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO1		0x0063
#define		COMMAND_08_0002_F_REPRE_2TANK_TANK2_5SEC_START_NO1			0x0064
#define		COMMAND_08_0003_F_REPRE_2TANK_TANK2_IS_5SEC_NO1				0x0065
#define		COMMAND_08_0004_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO2		0x0066
#define		COMMAND_08_0005_F_REPRE_2TANK_TANK2_5SEC_START_NO2			0x0067
#define		COMMAND_08_0006_F_REPRE_2TANK_TANK2_IS_5SEC_NO2				0x0068
#define		COMMAND_08_0007_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO3		0x0069
#define		COMMAND_08_0008_F_REPRE_2TANK_TANK2_5SEC_START_NO3			0x006a
#define		COMMAND_08_0009_F_REPRE_2TANK_TANK2_IS_5SEC_NO3				0x006b
#define		COMMAND_08_0010_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO4		0x006c
#define		COMMAND_08_0011_F_REPRE_2TANK_TANK2_5SEC_START_NO4			0x006d
#define		COMMAND_08_0012_F_REPRE_2TANK_TANK2_IS_5SEC_NO4				0x006e
#define		COMMAND_08_0013_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO5		0x006f
#define		COMMAND_08_0014_F_REPRE_2TANK_TANK2_5SEC_START_NO5			0x0070
#define		COMMAND_08_0015_F_REPRE_2TANK_TANK2_IS_5SEC_NO5				0x0071
#define		COMMAND_08_0016_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO6		0x0072
#define		COMMAND_08_0017_F_REPRE_2TANK_TANK2_5SEC_START_NO6			0x0073
#define		COMMAND_08_0018_F_REPRE_2TANK_TANK2_IS_5SEC_NO6				0x0074
#define		COMMAND_08_0019_F_REPRE_2TANK_TANK2_TANK_PRESSURE_NO7		0x0075
#define		COMMAND_08_0020_F_REPRE_2TANK_TANK2_IS_PRESSURE_STABLE		0x0076


//---------------函数声明--------------------------------------------------------------

void TGTHT510_supply_stage08_repre_f_main(void);
void TGTHT510_supply_stage08_repre_f_step_tank_number(void);
uint16 TGTHT510_supply_stage08_repre_f_step_1tank_lvt_valve_on(void);
uint16 TGTHT510_supply_stage08_repre_f_step_1tank_is_repre_over(void);
uint16 TGTHT510_supply_stage08_repre_f_step_1tank_lvt_valve_off(void);
uint16 TGTHT510_supply_stage08_repre_f_step_1tank_out_tank_valve_on(void);
uint16 TGTHT510_supply_stage08_repre_f_step_1tank_delay(void);
uint16 TGTHT510_supply_stage08_repre_f_step_1tank_is_tank_pressure_stable(void);

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank1_lvt_valve_on(void);
uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank1_is_repre_over(void);
uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank1_lvt_valve_off(void);
uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank1_out_tank_valve_on(void);
uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank1_delay(void);
uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank1_is_tank_pressure_stable(void);

uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank2_lvt_valve_on(void);
uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank2_is_repre_over(void);
uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank2_lvt_valve_off(void);
uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank2_out_tank_valve_on(void);
uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank2_delay(void);
uint16 TGTHT510_supply_stage08_repre_f_step_2tank_tank2_is_tank_pressure_stable(void);

void TGTHT510_supply_common_repre_lvt_valve_on(uint16 repre_kind,uint16 tank_sequence);
uint16 TGTHT510_supply_common_repre_is_lvt_valve_on(uint16 repre_kind,uint16 tank_sequence);
void TGTHT510_supply_common_repre_lvt_valve_off(uint16 repre_kind,uint16 tank_sequence);
uint16 TGTHT510_supply_common_repre_is_lvt_valve_off(uint16 repre_kind,uint16 tank_sequence);
void TGTHT510_supply_common_repre_out_tank_valve_on(uint16 repre_kind,uint16 tank_sequence,uint16 n);
uint16 TGTHT510_supply_common_repre_is_out_tank_valve_on(uint16 repre_kind,uint16 tank_sequence,uint16 n);
uint16 TGTHT510_supply_common_repre_tank_pressure_get(uint16 repre_kind,uint16 tank_sequence);
uint16 TGTHT510_supply_common_repre_is_repre_over(uint16 repre_kind,uint16 tank_sequence);
uint16 TGTHT510_supply_common_repre_is_tank_pressure_stable(uint16 *p);



#endif
 
 
 
