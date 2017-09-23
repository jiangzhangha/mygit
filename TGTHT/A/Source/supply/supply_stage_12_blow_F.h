/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器补加流程主程序头文件
  ******************************************************************************
  */
 
#ifndef __supply_stage_12_blow_f_h
#define __supply_stage_12_blow_f_h
 

/*声明结构体类型--------------------------------------------------------------*/



/*宏定义---------------------------------------------------------------------------*/

#define		BLOW_TANK_F				0x1234//燃贮箱吹除
#define		BLOW_TANK_O				0x4321//氧贮箱吹除


//步骤step----------------------------------------------------------------------

#define 	STEP_12_SUPPLY_BLOW_VALVE_ON			0x0001//燃路吹除阀打开
#define 	STEP_12_SUPPLY_IS_HYCT_TIME				0x0002//等待货船信息或者超时
#define 	STEP_12_SUPPLY_BLOW_VALVE_OFF			0x0003//燃路吹除阀关闭


//命令command-------------------------------------------------------------------

//燃路吹除阀打开
#define		COMMAND_12_0001_VALVE_ON_NO1			0x0001//燃路吹除阀打开，第一组
#define		COMMAND_12_0002_IS_VALVE_ON_NO1			0x0002//判断燃路吹除阀打开，第一组
#define		COMMAND_12_0003_VALVE_ON_NO2			0x0003//燃路吹除阀打开，第二组
#define		COMMAND_12_0004_IS_VALVE_ON_NO2			0x0004//判断燃路吹除阀打开，第二组
#define		COMMAND_12_0005_VALVE_ON_NO3			0x0005//燃路吹除阀打开，第三组
#define		COMMAND_12_0006_IS_VALVE_ON_NO3			0x0006//判断燃路吹除阀打开，第三组
#define		COMMAND_12_0007_VALVE_ON_NO4			0x0007//燃路吹除阀打开，第四组
#define		COMMAND_12_0008_IS_VALVE_ON_NO4			0x0008//判断燃路吹除阀打开，第四组
#define		COMMAND_12_0009_VALVE_ON_NO5			0x0009//燃路吹除阀打开，第五组
#define		COMMAND_12_0010_IS_VALVE_ON_NO5			0x000a//判断燃路吹除阀打开，第五组

//等待货船信息或者超时
#define		COMMAND_12_0001_IS_HYCT_TIME			0x000b

//燃路吹除阀关闭
#define		COMMAND_12_0001_VALVE_OFF_NO1			0x000c//燃路吹除阀关闭，第一组
#define		COMMAND_12_0002_IS_VALVE_OFF_NO1		0x000d//判断燃路吹除阀关闭，第一组
#define		COMMAND_12_0003_VALVE_OFF_NO2			0x000e//燃路吹除阀关闭，第二组
#define		COMMAND_12_0004_IS_VALVE_OFF_NO2		0x000f//判断燃路吹除阀关闭，第二组
#define		COMMAND_12_0005_VALVE_OFF_NO3			0x0010//燃路吹除阀关闭，第三组
#define		COMMAND_12_0006_IS_VALVE_OFF_NO3		0x0011//判断燃路吹除阀关闭，第三组
#define		COMMAND_12_0007_VALVE_OFF_NO4			0x0012//燃路吹除阀关闭，第四组
#define		COMMAND_12_0008_IS_VALVE_OFF_NO4		0x0013//判断燃路吹除阀关闭，第四组
#define		COMMAND_12_0009_VALVE_OFF_NO5			0x0014//燃路吹除阀关闭，第五组
#define		COMMAND_12_0010_IS_VALVE_OFF_NO5		0x0015//判断燃路吹除阀关闭，第五组
#define		COMMAND_12_0011_VALVE_OFF_NO6			0x0016//燃路吹除阀关闭，第五组
#define		COMMAND_12_0012_IS_VALVE_OFF_NO6		0x0017//判断燃路吹除阀关闭，第五组

//-------------------------函数声明------------------------------------------------

void TGTHT510_supply_stage12_blow_f_main(void);
uint16 TGTHT510_supply_stage12_blow_f_step_valve_on(void);
uint16 TGTHT510_supply_stage12_blow_f_step_is_hyct_time(void);
uint16 TGTHT510_supply_stage12_blow_f_step_valve_off(void);
void TGTHT510_supply_common_blow_valve_on(uint16 blow_kind,uint16 command_number);
uint16 TGTHT510_supply_common_blow_is_valve_on(uint16 blow_kind,uint16 command_number);
void TGTHT510_supply_common_blow_valve_off(uint16 blow_kind,uint16 command_number);
uint16 TGTHT510_supply_common_blow_is_valve_off(uint16 blow_kind,uint16 command_number);
uint16 TGTHT510_supply_common_is_blow_over(void);


#endif
 
 
 
 
 
 
