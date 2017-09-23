/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器补加流程主程序头文件
  ******************************************************************************
  */
 
#ifndef __supply_stage_04_leak_h
#define __supply_stage_04_leak_h
 

/*声明结构体类型--------------------------------------------------------------*/



/*宏定义---------------------------------------------------------------------------*/

//步骤step----------------------------------------------------------------------

#define 	STEP_04_SUPPLY_VALVE_ON_CONNECT				0x0001//开近浮动断接器补加阀门
#define 	STEP_04_SUPPLY_LEAK_INPUT_COMMAND			0x0002//检漏气体排气指令注入

//命令command-------------------------------------------------------------------

//开近浮动断接器补加阀门

#define		COMMAND_04_0001_VALVE_ON_CONNECT_NO1		0x0001//开近浮动断接器补加阀门第一组
#define		COMMAND_04_0002_IS_VALVE_ON_CONNECT_NO1		0x0002//判断开近浮动断接器补加阀门第一组
#define		COMMAND_04_0003_VALVE_ON_CONNECT_NO2		0x0003//开近浮动断接器补加阀门第二组
#define		COMMAND_04_0004_IS_VALVE_ON_CONNECT_NO2		0x0004//判断开近浮动断接器补加阀门第二组

//检漏排气指令
#define 	COMMAND_04_0005_LEAK_VALVE_NO1				0x0005//开检漏排气指令
#define 	COMMAND_04_0006_LEAK_IS_VALVE_NO1			0x0006//判断开检漏排气指令
#define 	COMMAND_04_0007_LEAK_VALVE_NO2				0x0007//开检漏排气指令
#define 	COMMAND_04_0008_LEAK_IS_VALVE_NO2			0x0008//判断开检漏排气指令
#define 	COMMAND_04_0009_LEAK_VALVE_NO3				0x0009//开检漏排气指令
#define 	COMMAND_04_0010_LEAK_IS_VALVE_NO3			0x000a//判断开检漏排气指令
#define 	COMMAND_04_0011_LEAK_VALVE_NO4				0x000b//开检漏排气指令
#define 	COMMAND_04_0012_LEAK_IS_VALVE_NO4			0x000c//判断开检漏排气指令
#define 	COMMAND_04_0013_LEAK_VALVE_NO5				0x000d//开检漏排气指令
#define 	COMMAND_04_0014_LEAK_IS_VALVE_NO5			0x000e//判断开检漏排气指令
#define 	COMMAND_04_0015_LEAK_VALVE_NO6				0x000f//开检漏排气指令
#define 	COMMAND_04_0016_LEAK_IS_VALVE_NO6			0x0010//判断开检漏排气指令
#define 	COMMAND_04_0017_LEAK_VALVE_NO7				0x0011//开检漏排气指令
#define 	COMMAND_04_0018_LEAK_IS_VALVE_NO7			0x0012//判断开检漏排气指令
#define 	COMMAND_04_0019_LEAK_VALVE_NO8				0x0013//开检漏排气指令
#define 	COMMAND_04_0020_LEAK_IS_VALVE_NO8			0x0014//判断开检漏排气指令
#define 	COMMAND_04_0021_LEAK_VALVE_NO9				0x0015//开检漏排气指令
#define 	COMMAND_04_0022_LEAK_IS_VALVE_NO9			0x0016//判断开检漏排气指令
#define 	COMMAND_04_0023_LEAK_VALVE_NO10				0x0017//开检漏排气指令
#define 	COMMAND_04_0024_LEAK_IS_VALVE_NO10			0x0018//判断开检漏排气指令
#define 	COMMAND_04_0025_LEAK_VALVE_NO11				0x0019//开检漏排气指令
#define 	COMMAND_04_0026_LEAK_IS_VALVE_NO11			0x001a//判断开检漏排气指令
#define 	COMMAND_04_0027_LEAK_VALVE_NO12				0x001b//开检漏排气指令
#define 	COMMAND_04_0028_LEAK_IS_VALVE_NO12			0x001c//判断开检漏排气指令

#define		COMMAND_04_0029_LEAK_TIME_START				0x001d//开始等待检漏排气时间
#define		COMMAND_04_0030_LEAK_IS_TIME				0x001e//判断检漏排气时间是否到

#define 	COMMAND_04_0031_LEAK_VALVE_NO13				0x001f//关检漏排气指令
#define 	COMMAND_04_0032_LEAK_IS_VALVE_NO13			0x0020//判断关检漏排气指令
#define 	COMMAND_04_0033_LEAK_VALVE_NO14				0x0021//关检漏排气指令
#define 	COMMAND_04_0034_LEAK_IS_VALVE_NO14			0x0022//判断关检漏排气指令
#define 	COMMAND_04_0035_LEAK_VALVE_NO15				0x0023//关检漏排气指令
#define 	COMMAND_04_0036_LEAK_IS_VALVE_NO15			0x0024//判断关检漏排气指令
#define 	COMMAND_04_0037_LEAK_VALVE_NO16				0x0025//关检漏排气指令
#define 	COMMAND_04_0038_LEAK_IS_VALVE_NO16			0x0026//判断关检漏排气指令
#define 	COMMAND_04_0039_LEAK_VALVE_NO17				0x0027//关检漏排气指令
#define 	COMMAND_04_0040_LEAK_IS_VALVE_NO17			0x0028//判断关检漏排气指令
#define 	COMMAND_04_0041_LEAK_VALVE_NO18				0x0029//关检漏排气指令
#define 	COMMAND_04_0042_LEAK_IS_VALVE_NO18			0x002a//判断关检漏排气指令
#define 	COMMAND_04_0043_LEAK_VALVE_NO19				0x002b//关检漏排气指令
#define 	COMMAND_04_0044_LEAK_IS_VALVE_NO19			0x002c//判断关检漏排气指令
#define 	COMMAND_04_0045_LEAK_VALVE_NO20				0x002d//关检漏排气指令
#define 	COMMAND_04_0046_LEAK_IS_VALVE_NO20			0x002e//判断关检漏排气指令
#define 	COMMAND_04_0047_LEAK_VALVE_NO21				0x002f//关检漏排气指令
#define 	COMMAND_04_0048_LEAK_IS_VALVE_NO21			0x0030//判断关检漏排气指令
#define 	COMMAND_04_0049_LEAK_VALVE_NO22				0x0031//关检漏排气指令
#define 	COMMAND_04_0050_LEAK_IS_VALVE_NO22			0x0032//判断关检漏排气指令
#define 	COMMAND_04_0051_LEAK_VALVE_NO23				0x0033//关检漏排气指令
#define 	COMMAND_04_0052_LEAK_IS_VALVE_NO23			0x0034//判断关检漏排气指令
#define 	COMMAND_04_0053_LEAK_VALVE_NO24				0x0035//关检漏排气指令
#define 	COMMAND_04_0054_LEAK_IS_VALVE_NO24			0x0036//判断关检漏排气指令

#define 	COMMAND_04_0055_LEAK_VALVE_NO25				0x0037//关近浮动断接器阀门
#define 	COMMAND_04_0056_LEAK_IS_VALVE_NO25			0x0038//判断关近浮动断接器阀门
#define 	COMMAND_04_0057_LEAK_VALVE_NO26				0x0039//关近浮动断接器阀门
#define 	COMMAND_04_0058_LEAK_IS_VALVE_NO26			0x003a//判断关近浮动断接器阀门
#define 	COMMAND_04_0059_LEAK_VALVE_NO27				0x003b//关近浮动断接器阀门
#define 	COMMAND_04_0060_LEAK_IS_VALVE_NO27			0x003c//判断关近浮动断接器阀门
#define 	COMMAND_04_0061_LEAK_VALVE_NO28				0x003d//关近浮动断接器阀门
#define 	COMMAND_04_0062_LEAK_IS_VALVE_NO28			0x003e//判断关近浮动断接器阀门
#define 	COMMAND_04_0063_LEAK_VALVE_NO29				0x003f//关近浮动断接器阀门
#define 	COMMAND_04_0064_LEAK_IS_VALVE_NO29			0x0040//判断关近浮动断接器阀门
#define 	COMMAND_04_0065_LEAK_VALVE_NO30				0x0041//关近浮动断接器阀门
#define 	COMMAND_04_0066_LEAK_IS_VALVE_NO30			0x0042//判断关近浮动断接器阀门
#define 	COMMAND_04_0067_LEAK_VALVE_NO31				0x0043//关近浮动断接器阀门
#define 	COMMAND_04_0068_LEAK_IS_VALVE_NO31			0x0044//判断关近浮动断接器阀门
#define 	COMMAND_04_0069_LEAK_VALVE_NO32				0x0045//关近浮动断接器阀门
#define 	COMMAND_04_0070_LEAK_IS_VALVE_NO32			0x0046//判断关近浮动断接器阀门



//-------------------------函数声明------------------------------------------------

void TGTHT510_supply_stage04_leak_main(void);
void TGTHT510_supply_stage04_leak_valve_on_connect(void);
void TGTHT510_supply_stage04_leak_command_valve_on_connect(uint16 n);
uint16 TGTHT510_supply_stage04_leak_command_is_valve_on_connect(uint16 n);

void TGTHT510_supply_stage04_leak_valve_on_gas(void);
void TGTHT510_supply_stage04_leak_command_valve_on_gas(uint16 n);
uint16 TGTHT510_supply_stage04_leak_command_is_valve_on_gas(uint16 n);





#endif
 
 
 
 
 

 
 
