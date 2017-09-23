/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器补加流程主程序头文件
  ******************************************************************************
  */
#ifndef __supply_stage_11_repre_third_f_h
#define __supply_stage_11_repre_third_f_h
 

/*声明结构体类型--------------------------------------------------------------*/

/*宏定义---------------------------------------------------------------------------*/

//步骤step------------------------------------------------------------------------

#define 	STEP_11_F_REPRE_1TANK_LVT_VALVE_ON				0x0001//贮箱增压，打开高压自锁阀
#define 	STEP_11_F_REPRE_1TANK_IS_REPRE_OVER				0x0002//通过压力与时间判断复压是否结束
#define 	STEP_11_F_REPRE_1TANK_LVT_VALVE_OFF				0x0003//复压结束，关闭高压自锁阀
#define 	STEP_11_F_REPRE_1TANK_OUT_TANK_VALVE_ON			0x0004//开贮箱出口阀门
#define 	STEP_11_F_REPRE_1TANK_DELAY						0x0005//延时等待
#define 	STEP_11_F_REPRE_1TANK_IS_TANK_PRESSURE			0x0006//判断贮箱压力的稳定性

//命令command---------------------------------------------------------------------

//贮箱增压，打开高压自锁阀
#define		COMMAND_11_0001_F_REPRE_1TANK_LVT_VALVE_ON				0x0002
#define		COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO1			0x0003
#define		COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO1				0x0004
#define		COMMAND_11_0004_F_REPRE_1TANK_IS_LVT_VALVE_ON			0x0005

//通过压力与时间判断复压是否结束
#define		COMMAND_11_0001_F_REPRE_1TANK_IS_REPRE_OVER				0x0006

//复压结束，关闭高压自锁阀
#define		COMMAND_11_0001_F_REPRE_1TANK_LVT_VALVE_OFF				0x0007
#define		COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO2			0x0008
#define		COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO2				0x0009
#define		COMMAND_11_0004_F_REPRE_1TANK_IS_LVT_VALVE_OFF			0x000a

//开贮箱出口阀门
#define		COMMAND_11_0001_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO1		0x000b
#define		COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO3			0x000c
#define		COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO3				0x000d
#define		COMMAND_11_0004_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO1	0x000e
#define		COMMAND_11_0005_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO2		0x000f
#define		COMMAND_11_0006_F_REPRE_1TANK_1MIN_START_NO4			0x0010
#define		COMMAND_11_0007_F_REPRE_1TANK_IS_1MIN_NO4				0x0011
#define		COMMAND_11_0008_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO2	0x0012


//延时等待
#define		COMMAND_11_0001_F_REPRE_1TANK_DELAY_START_NO1			0x0013
#define		COMMAND_11_0002_F_REPRE_1TANK_IS_DELAY_NO1				0x0014

//判断贮箱压力的稳定性
#define		COMMAND_11_0001_F_REPRE_1TANK_TANK_PRESSURE_NO1			0x0015
#define		COMMAND_11_0002_F_REPRE_1TANK_5SEC_START_NO1			0x0016
#define		COMMAND_11_0003_F_REPRE_1TANK_IS_5SEC_NO1				0x0017
#define		COMMAND_11_0004_F_REPRE_1TANK_TANK_PRESSURE_NO2			0x0018
#define		COMMAND_11_0005_F_REPRE_1TANK_5SEC_START_NO2			0x0019
#define		COMMAND_11_0006_F_REPRE_1TANK_IS_5SEC_NO2				0x001a
#define		COMMAND_11_0007_F_REPRE_1TANK_TANK_PRESSURE_NO3			0x001b
#define		COMMAND_11_0008_F_REPRE_1TANK_5SEC_START_NO3			0x001c
#define		COMMAND_11_0009_F_REPRE_1TANK_IS_5SEC_NO3				0x001d
#define		COMMAND_11_0010_F_REPRE_1TANK_TANK_PRESSURE_NO4			0x001e
#define		COMMAND_11_0011_F_REPRE_1TANK_5SEC_START_NO4			0x001f
#define		COMMAND_11_0012_F_REPRE_1TANK_IS_5SEC_NO4				0x0020
#define		COMMAND_11_0013_F_REPRE_1TANK_TANK_PRESSURE_NO5			0x0021
#define		COMMAND_11_0014_F_REPRE_1TANK_5SEC_START_NO5			0x0022
#define		COMMAND_11_0015_F_REPRE_1TANK_IS_5SEC_NO5				0x0023
#define		COMMAND_11_0016_F_REPRE_1TANK_TANK_PRESSURE_NO6			0x0024
#define		COMMAND_11_0017_F_REPRE_1TANK_5SEC_START_NO6			0x0025
#define		COMMAND_11_0018_F_REPRE_1TANK_IS_5SEC_NO6				0x0026
#define		COMMAND_11_0019_F_REPRE_1TANK_TANK_PRESSURE_NO7			0x0027
#define		COMMAND_11_0020_F_REPRE_1TANK_IS_PRESSURE_STABLE		0x0028


//---------------函数声明--------------------------------------------------------------


void TGTHT510_supply_stage11_repre_f_main(void);
void TGTHT510_supply_stage11_repre_f_step_tank_number(void);
uint16 TGTHT510_supply_stage11_repre_f_step_1tank_lvt_valve_on(void);
uint16 TGTHT510_supply_stage11_repre_f_step_1tank_is_repre_over(void);
uint16 TGTHT510_supply_stage11_repre_f_step_1tank_lvt_valve_off(void);
uint16 TGTHT510_supply_stage11_repre_f_step_1tank_out_tank_valve_on(void);
uint16 TGTHT510_supply_stage11_repre_f_step_1tank_delay(void);
uint16 TGTHT510_supply_stage11_repre_f_step_1tank_is_tank_pressure_stable(void);

#endif
 
 
 
