/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器补加流程主程序头文件
  ******************************************************************************
  */

#ifndef __supply_stage_09_comp_f_third_h
#define __supply_stage_09_comp_f_third_h

/*宏定义---------------------------------------------------------------------------*/


//步骤step-------------------------------------------------------------------------

//----------------------------------初始设置阶段-----------------------------------

#define 	STEP_09_F_INIT_START_COOLER							0x0000//启动液冷泵工作
#define 	STEP_09_F_INIT_IS_COOLER_WORK						0x0001//通过转速判断液冷工作是否正常
#define 	STEP_09_F_INIT_DELAY								0x0002//延时等待时间
#define		STEP_09_F_INIT_IS_COMPRESSOR_TEMPERATURE			0x0003//判断压气机温度是否正常
#define		STEP_09_F_INIT_TGTHT530_POWER_ON					0x0004//申请电机驱动器加电
#define		STEP_09_F_INIT_COMPRESSOR_POWER_ON					0x0005//申请压气机加电
#define		STEP_09_F_INIT_ISOLATION							0x0006//贮箱隔离

//----------------------------------第三个贮箱抽气-----------------------------------

#define 	STEP_09_F_1TANK_IN_TANK_VALVE_ON					0x0007//开进贮箱低压气路补加阀门

#define 	STEP_09_F_1TANK_TIME_DELAY_A						0x0008//延时等待

#define 	STEP_09_F_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE		0x0009//通过压力判断开进贮箱低压气路补加阀门
#define 	STEP_09_F_1TANK_IN_COMPRESSOR_VALVE_ON				0x000a//开燃压气机进口阀门
#define 	STEP_09_F_1TANK_TIME_DELAY1							0x000b//延时等待time_delay1
#define 	STEP_09_F_1TANK_IS_IN_COMPRESSOR_PRESSURE			0x000c//判断压气机进口压力是否正常
#define 	STEP_09_F_1TANK_COMPRESSOR_START					0x000d//燃压气机启动

#define 	STEP_09_F_1TANK_TIME_DELAY_B						0x000e//延时等待

#define 	STEP_09_F_1TANK_IS_OUT_COMPRESSOR_PRESSURE			0x000f//判断压气机出口压力是否正常
#define 	STEP_09_F_1TANK_OUT_COMPRESSOR_VALVE_ON				0x0010//开燃压气机出口阀门
#define 	STEP_09_F_1TANK_NUMBER_COMP_GAS						0x0011//判断抽气气瓶个数

//一个气瓶抽气
#define 	STEP_09_F_1TANK_1GAS_IN_GAS_VALVE_ON				0x0012//开进气瓶补加阀门
#define 	STEP_09_F_1TANK_1GAS_TIME_DELAY2					0x0013//延时等待time_delay2
#define 	STEP_09_F_1TANK_1GAS_IS_GAS_PRESSURE				0x0014//判断气瓶压力是否升高
#define 	STEP_09_F_1TANK_1GAS_IS_COMP_OVER					0x0015//判断气瓶抽气是否结束
#define 	STEP_09_F_1TANK_1GAS_IN_GAS_VALVE_OFF				0x0016//关燃路气瓶补加阀门

#define		STEP_09_F_1TANK_1GAS_IS_ISOLATION_FIRST				0x0017//通过压力判断高压气路隔离是否正常，第一次
#define 	STEP_09_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF		0x0018//关闭燃压气机出口阀门
#define		STEP_09_F_1TANK_1GAS_IS_ISOLATION_SECOND			0x0019//通过压力判断高压气路隔离是否正常，第二次

#define		STEP_09_F_1TANK_1GAS_COMPRESSOR_STOP				0x001a//燃压气机停机
#define		STEP_09_F_1TANK_1GAS_IS_COMPRESSOR_STOP				0x001b//判断燃压气机停机是否正常
#define		STEP_09_F_1TANK_1GAS_BYPATH_VALVE_ON				0x001c//开燃压气机旁路自锁阀
#define 	STEP_09_F_1TANK_1GAS_TIME_DELAY_BYPATH				0x001d//延时等待time_bypath
#define		STEP_09_F_1TANK_1GAS_BYPATH_VALVE_OFF				0x001e//关燃压气机旁路自锁阀
#define 	STEP_09_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2		0x001f//关闭燃压气机出口阀门，第二次
#define 	STEP_09_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF		0x0020//关闭燃压气机进口阀门
#define 	STEP_09_F_1TANK_1GAS_IN_TANK_VALVE_OFF				0x0021//关进贮箱低压气路补加阀门
#define 	STEP_09_F_1TANK_1GAS_SET_STATE_GOOD					0x0022//设置燃抽气状态好
#define 	STEP_09_F_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE		0x0023//判断压气机温度是否正常

#define 	STEP_09_F_1TANK_1GAS_TIME_DELAY3					0x0024//延时等待time_delay3
#define 	STEP_09_F_1TANK_1GAS_EXCHANGE_COOLER				0x0025//启动液冷模块切换程序
#define		STEP_09_F_1TANK_1GAS_IS_EXCHANGE_COOLER				0x0026//通过压力判断液冷模块切换是否正常
#define		STEP_09_F_1TANK_1GAS_COOLER_STOP					0x0027//液冷模块停机
#define		STEP_09_F_1TANK_1GAS_COMPRESSOR_POWER_OFF			0x0028//申请压气机断电
#define		STEP_09_F_1TANK_1GAS_TGTHT530_POWER_OFF				0x0029//申请电机驱动器断电

//**************************************程序结束******************************************************************

//两个气瓶抽气
#define 	STEP_09_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON			0x002a//开进气瓶补加阀门---第一个气瓶
#define 	STEP_09_F_1TANK_2GAS_GAS1_TIME_DELAY2				0x002b//延时等待time_delay2---第一个气瓶
#define 	STEP_09_F_1TANK_2GAS_GAS1_IS_GAS_PRESSURE			0x002c//判断气瓶压力是否升高---第一个气瓶
#define 	STEP_09_F_1TANK_2GAS_GAS1_IS_COMP_OVER				0x002d//判断气瓶抽气是否结束---第一个气瓶
#define 	STEP_09_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF			0x002e//关燃路气瓶补加阀门---第一个气瓶
#define 	STEP_09_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON			0x002f//开进气瓶补加阀门---第二个气瓶
#define 	STEP_09_F_1TANK_2GAS_GAS2_TIME_DELAY2				0x0030//延时等待time_delay2---第二个气瓶
#define 	STEP_09_F_1TANK_2GAS_GAS2_IS_GAS_PRESSURE			0x0031//判断气瓶压力是否升高---第二个气瓶
#define 	STEP_09_F_1TANK_2GAS_GAS2_IS_COMP_OVER				0x0032//判断气瓶抽气是否结束---第二个气瓶
#define 	STEP_09_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF			0x0033//关燃路气瓶补加阀门---第二个气瓶

#define		STEP_09_F_1TANK_2GAS_IS_ISOLATION_FIRST				0x0034//通过压力判断高压气路隔离是否正常，第一次
#define 	STEP_09_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF		0x0035//关闭燃压气机出口阀门
#define		STEP_09_F_1TANK_2GAS_IS_ISOLATION_SECOND			0x0036//通过压力判断高压气路隔离是否正常，第二次

#define		STEP_09_F_1TANK_2GAS_COMPRESSOR_STOP				0x0037//燃压气机停机
#define		STEP_09_F_1TANK_2GAS_IS_COMPRESSOR_STOP				0x0038//判断燃压气机停机是否正常
#define		STEP_09_F_1TANK_2GAS_BYPATH_VALVE_ON				0x0039//开燃压气机旁路自锁阀
#define 	STEP_09_F_1TANK_2GAS_TIME_DELAY_BYPATH				0x003a//延时等待time_bypath
#define		STEP_09_F_1TANK_2GAS_BYPATH_VALVE_OFF				0x003b//关燃压气机旁路自锁阀
#define 	STEP_09_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2		0x003c//关闭燃压气机出口阀门，第二次
#define 	STEP_09_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF		0x003d//关闭燃压气机进口阀门
#define 	STEP_09_F_1TANK_2GAS_IN_TANK_VALVE_OFF				0x003e//关进贮箱低压气路补加阀门
#define 	STEP_09_F_1TANK_2GAS_SET_STATE_GOOD					0x003f//设置燃抽气状态好
#define 	STEP_09_F_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE		0x0040//判断压气机温度是否正常

#define 	STEP_09_F_1TANK_2GAS_TIME_DELAY3					0x0041//延时等待time_delay3
#define 	STEP_09_F_1TANK_2GAS_EXCHANGE_COOLER				0x0042//启动液冷模块切换程序
#define		STEP_09_F_1TANK_2GAS_IS_EXCHANGE_COOLER				0x0043//通过压力判断液冷模块切换是否正常
#define		STEP_09_F_1TANK_2GAS_COOLER_STOP					0x0044//液冷模块停机
#define		STEP_09_F_1TANK_2GAS_COMPRESSOR_POWER_OFF			0x0045//申请压气机断电
#define		STEP_09_F_1TANK_2GAS_TGTHT530_POWER_OFF				0x0046//申请电机驱动器断电

//**************************************程序结束******************************************************************

//命令command--------------------------------------------------------------------------------------------

//------------------------------command---初始设置阶段---------------------------------------------------

//启动液冷泵工作
#define		COMMAND_09_0001_F_INIT_COOLER_VALVE_ON_NO1			0x0001//液冷模块补加系统阀门开第一组
#define		COMMAND_09_0002_F_INIT_IS_COOLER_VALVE_ON_NO1		0x0002//判断液冷模块补加系统阀门开第一组
#define		COMMAND_09_0003_F_INIT_COOLER_VALVE_ON_NO2			0x0003//液冷模块补加系统阀门开第二组
#define		COMMAND_09_0004_F_INIT_IS_COOLER_VALVE_ON_NO2		0x0004//判断液冷模块补加系统阀门开第二组
#define		COMMAND_09_0005_F_INIT_COOLER_POWER_ON				0x0005//液冷模块供电通
#define		COMMAND_09_0006_F_INIT_TIME_1MIN_START				0x0006//延时1min计时开始
#define		COMMAND_09_0007_F_INIT_IS_TIME_1MIN					0x0007//延时1min是否到

//通过转速判断液冷工作是否正常
#define		COMMAND_09_0001_F_INIT_IS_COOLER_WORK				0x0008//通过转速判断液冷工作是否正常

//延时等待time_delay
#define		COMMAND_09_0001_F_INIT_TIME_DELAY_START				0x0009//延时等待time_delay计时开始
#define		COMMAND_09_0002_F_INIT_IS_TIME_DELAY				0x000a//判断延时等待time_delay

//判断压气机温度是否正常
#define		COMMAND_09_0001_F_INIT_IS_COMPRESSOR_TEMPERATURE	0x000b//判断压气机温度是否正常

//申请电机驱动器加电
#define		COMMAND_09_0001_F_INIT_TGTHT530_POWER_ON			0x000c//申请设备管理指令
#define		COMMAND_09_0002_F_INIT_TGTHT530_TIME_1MIN_START		0x000d//延时1min计时开始
#define		COMMAND_09_0003_F_INIT_TGTHT530_IS_TIME_1MIN		0x000e//判断计时1min是否到
#define		COMMAND_09_0004_F_INIT_TGTHT530_IS_POWER_ON			0x000f//通过互传数据判断加电是否正常

//申请压气机加电
#define		COMMAND_09_0001_F_INIT_COMPRESSOR_POWER_ON			0x0010//申请设备管理指令
#define		COMMAND_09_0002_F_INIT_COMPRESSOR_TIME_1MIN_START	0x0011//延时1min计时开始
#define		COMMAND_09_0003_F_INIT_COMPRESSOR_IS_TIME_1MIN		0x0012//判断计时1min是否到

//贮箱隔离
#define		COMMAND_09_0001_F_INIT_ISOLATION_VALVE_OFF_NO1		0x0013//隔离推进系统自锁阀关闭，第一组
#define		COMMAND_09_0002_F_INIT_TIME_1MIN_START_NO1			0x0014//延时1min计时开始，第一组
#define		COMMAND_09_0003_F_INIT_IS_TIME_1MIN_NO1				0x0015//延时1min是否到，第一组
#define		COMMAND_09_0004_F_INIT_IS_ISOLATION_VALVE_OFF_NO1	0x0016//判断隔离推进系统自锁阀关闭，第一组

#define		COMMAND_09_0005_F_INIT_ISOLATION_VALVE_OFF_NO2		0x0017//隔离推进系统自锁阀关闭，第二组
#define		COMMAND_09_0006_F_INIT_TIME_1MIN_START_NO2			0x0018//延时1min计时开始，第二组
#define		COMMAND_09_0007_F_INIT_IS_TIME_1MIN_NO2				0x0019//延时1min是否到，第二组
#define		COMMAND_09_0008_F_INIT_IS_ISOLATION_VALVE_OFF_NO2	0x001a//判断隔离推进系统自锁阀关闭，第二组

#define		COMMAND_09_0009_F_INIT_ISOLATION_VALVE_OFF_NO3		0x001b//隔离推进系统自锁阀关闭，第三组
#define		COMMAND_09_0010_F_INIT_TIME_1MIN_START_NO3			0x001c//延时1min计时开始，第三组
#define		COMMAND_09_0011_F_INIT_IS_TIME_1MIN_NO3				0x001d//延时1min是否到，第三组
#define		COMMAND_09_0012_F_INIT_IS_ISOLATION_VALVE_OFF_NO3	0x001e//判断隔离推进系统自锁阀关闭，第三组

#define		COMMAND_09_0013_F_INIT_ISOLATION_VALVE_OFF_NO4		0x001f//隔离推进系统自锁阀关闭，第四组
#define		COMMAND_09_0014_F_INIT_TIME_1MIN_START_NO4			0x0020//延时1min计时开始，第四组
#define		COMMAND_09_0015_F_INIT_IS_TIME_1MIN_NO4				0x0021//延时1min是否到，第四组
#define		COMMAND_09_0016_F_INIT_IS_ISOLATION_VALVE_OFF_NO4	0x0022//判断隔离推进系统自锁阀关闭，第四组

#define		COMMAND_09_0017_F_INIT_ISOLATION_VALVE_OFF_NO5		0x0023//隔离推进系统自锁阀关闭，第五组
#define		COMMAND_09_0018_F_INIT_TIME_1MIN_START_NO5			0x0024//延时1min计时开始，第五组
#define		COMMAND_09_0019_F_INIT_IS_TIME_1MIN_NO5				0x0025//延时1min是否到，第五组
#define		COMMAND_09_0020_F_INIT_IS_ISOLATION_VALVE_OFF_NO5	0x0026//判断隔离推进系统自锁阀关闭，第五组

#define		COMMAND_09_0021_F_INIT_ISOLATION_VALVE_OFF_NO6		0x0027//隔离推进系统自锁阀关闭，第六组
#define		COMMAND_09_0022_F_INIT_TIME_1MIN_START_NO6			0x0028//延时1min计时开始，第六组
#define		COMMAND_09_0023_F_INIT_IS_TIME_1MIN_NO6				0x0029//延时1min是否到，第六组
#define		COMMAND_09_0024_F_INIT_IS_ISOLATION_VALVE_OFF_NO6	0x002a//判断隔离推进系统自锁阀关闭，第六组

#define		COMMAND_09_0025_F_INIT_ISOLATION_VALVE_OFF_NO7		0x002b//隔离推进系统自锁阀关闭，第七组
#define		COMMAND_09_0026_F_INIT_TIME_1MIN_START_NO7			0x002c//延时1min计时开始，第七组
#define		COMMAND_09_0027_F_INIT_IS_TIME_1MIN_NO7				0x002d//延时1min是否到，第七组
#define		COMMAND_09_0028_F_INIT_IS_ISOLATION_VALVE_OFF_NO7	0x002e//判断隔离推进系统自锁阀关闭，第七组

#define		COMMAND_09_0029_F_INIT_ISOLATION_VALVE_OFF_NO8		0x002f//隔离推进系统自锁阀关闭，第八组
#define		COMMAND_09_0030_F_INIT_TIME_1MIN_START_NO8			0x0030//延时1min计时开始，第八组
#define		COMMAND_09_0031_F_INIT_IS_TIME_1MIN_NO8				0x0031//延时1min是否到，第八组
#define		COMMAND_09_0032_F_INIT_IS_ISOLATION_VALVE_OFF_NO8	0x0032//判断隔离推进系统自锁阀关闭，第八组

#define		COMMAND_09_0033_F_INIT_ISOLATION_VALVE_OFF_NO9		0x0033//隔离推进系统自锁阀关闭，第九组
#define		COMMAND_09_0034_F_INIT_TIME_1MIN_START_NO9			0x0034//延时1min计时开始，第九组
#define		COMMAND_09_0035_F_INIT_IS_TIME_1MIN_NO9				0x0035//延时1min是否到，第九组
#define		COMMAND_09_0036_F_INIT_IS_ISOLATION_VALVE_OFF_NO9	0x0036//判断隔离推进系统自锁阀关闭，第九组

//------------------------------command---第三个贮箱抽气-----------------------------------------------

//开进贮箱低压气路补加阀门
#define		COMMAND_09_0001_F_1TANK_IN_TANK_VALVE_ON					0x0038//开进贮箱低压气路补加阀门
#define		COMMAND_09_0002_F_1TANK_IS_IN_TANK_VALVE_ON					0x0039//判断开进贮箱低压气路补加阀门

//通过压力判断开进贮箱低压气路补加阀门
#define		COMMAND_09_0001_F_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE		0x003a//通过压力判断开补加阀门

//开燃压气机进口阀门
#define		COMMAND_09_0001_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO1			0x003b//开燃压气机进口阀门，第一组
#define		COMMAND_09_0002_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO1		0x003c//判断开燃压气机进口阀门，第一组
#define		COMMAND_09_0003_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO2			0x003d//开燃压气机进口阀门，第二组
#define		COMMAND_09_0004_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO2		0x003e//判断开燃压气机进口阀门，第二组
#define		COMMAND_09_0005_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO3			0x003f//开燃压气机进口阀门，第三组
#define		COMMAND_09_0006_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO3		0x0040//判断开燃压气机进口阀门，第三组

//延时等待time_delay1
#define		COMMAND_09_0001_F_1TANK_TIME_DELAY1_START					0x0041//延时等待time_delay1计时开始
#define		COMMAND_09_0002_F_1TANK_IS_TIME_DELAY1						0x0042//判断延时等待time_delay1

//判断压气机进口压力是否正常
#define		COMMAND_09_0001_F_1TANK_IS_IN_COMPRESSOR_PRESSURE			0x0043//判断压气机进口压力是否正常

//燃压气机启动
#define		COMMAND_09_0001_F_1TANK_COMPRESSOR_START					0x0044//申请设备管理指令，压气机启动
#define		COMMAND_09_0002_F_1TANK_COMPRESSOR_TIME_1MIN_START			0x0045//延时1min计时开始
#define		COMMAND_09_0003_F_1TANK_COMPRESSOR_IS_TIME_1MIN				0x0046//判断1min定时
#define		COMMAND_09_0004_F_1TANK_IS_COMPRESSOR_START					0x0047//通过互传数据判断启动是否正常

//判断压气机出口压力是否正常
#define		COMMAND_09_0001_F_1TANK_IS_OUT_COMPRESSOR_PRESSURE			0x0048//判断压气机出口压力是否正常

//开燃压气机出口阀门
#define		COMMAND_09_0001_F_1TANK_OUT_COMPRESSOR_VALVE_ON				0x0049//开燃压气机出口阀门
#define		COMMAND_09_0002_F_1TANK_IS_OUT_COMPRESSOR_VALVE_ON			0x004a//判断开燃压气机出口阀门

//判断抽气气瓶个数
#define		COMMAND_09_0001_F_1TANK_NUMBER_COMP_GAS						0x004b//判断抽气气瓶个数


//------------------------------command---第三个贮箱抽气----一个气瓶抽气-----------------------------------

//开进气瓶补加阀门
#define		COMMAND_09_0001_F_1TANK_1GAS_IN_GAS_VALVE_ON				0x004c//开进气瓶补加阀门
#define		COMMAND_09_0002_F_1TANK_1GAS_IS_IN_GAS_VALVE_ON				0x004d//判断开进气瓶补加阀门

//延时等待time_delay2
#define		COMMAND_09_0001_F_1TANK_1GAS_TIME_DELAY2_START				0x004e//延时等待time_delay2计时开始
#define		COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_DELAY2					0x004f//判断延时等待time_delay2


//判断气瓶压力是否升高
#define		COMMAND_09_0001_F_1TANK_1GAS_GAS_PRESSURE_NO1				0x0050//采集气瓶压力，第一次
#define		COMMAND_09_0002_F_1TANK_1GAS_TIME_30S_START_NO1				0x0051//计时30s计时开始，第一次
#define		COMMAND_09_0003_F_1TANK_1GAS_IS_TIME_30S_NO1				0x0052//判断定时30s，第一次
#define		COMMAND_09_0004_F_1TANK_1GAS_GAS_PRESSURE_NO2				0x0053//采集气瓶压力，第二次
#define		COMMAND_09_0005_F_1TANK_1GAS_TIME_30S_START_NO2				0x0054//计时30s计时开始，第二次
#define		COMMAND_09_0006_F_1TANK_1GAS_IS_TIME_30S_NO2				0x0055//判断定时30s，第二次
#define		COMMAND_09_0007_F_1TANK_1GAS_GAS_PRESSURE_NO3				0x0056//采集气瓶压力，第三次
#define		COMMAND_09_0008_F_1TANK_1GAS_TIME_30S_START_NO3				0x0057//计时30s计时开始，第三次
#define		COMMAND_09_0009_F_1TANK_1GAS_IS_TIME_30S_NO3				0x0058//判断定时30s，第三次
#define		COMMAND_09_0010_F_1TANK_1GAS_GAS_PRESSURE_NO4				0x0059//采集气瓶压力，第四次
#define		COMMAND_09_0011_F_1TANK_1GAS_TIME_30S_START_NO4				0x005a//计时30s计时开始，第四次
#define		COMMAND_09_0012_F_1TANK_1GAS_IS_TIME_30S_NO4				0x005b//判断定时30s，第四次
#define		COMMAND_09_0013_F_1TANK_1GAS_GAS_PRESSURE_NO5				0x005c//采集气瓶压力，第五次
#define		COMMAND_09_0014_F_1TANK_1GAS_TIME_30S_START_NO5				0x005d//计时30s计时开始，第五次
#define		COMMAND_09_0015_F_1TANK_1GAS_IS_TIME_30S_NO5				0x005e//判断定时30s，第五次
#define		COMMAND_09_0016_F_1TANK_1GAS_GAS_PRESSURE_NO6				0x005f//采集气瓶压力，第六次
#define		COMMAND_09_0017_F_1TANK_1GAS_TIME_30S_START_NO6				0x0060//计时30s计时开始，第六次
#define		COMMAND_09_0018_F_1TANK_1GAS_IS_TIME_30S_NO6				0x0061//判断定时30s，第六次
#define		COMMAND_09_0019_F_1TANK_1GAS_GAS_PRESSURE_NO7				0x0062//采集气瓶压力，第七次
#define		COMMAND_09_0020_F_1TANK_1GAS_TIME_30S_START_NO7				0x0063//计时30s计时开始，第七次
#define		COMMAND_09_0021_F_1TANK_1GAS_IS_TIME_30S_NO7				0x0064//判断定时30s，第七次
#define		COMMAND_09_0022_F_1TANK_1GAS_GAS_PRESSURE_NO8				0x0065//采集气瓶压力，第八次
#define		COMMAND_09_0023_F_1TANK_1GAS_TIME_30S_START_NO8				0x0066//计时30s计时开始，第八次
#define		COMMAND_09_0024_F_1TANK_1GAS_IS_TIME_30S_NO8				0x0067//判断定时30s，第八次
#define		COMMAND_09_0025_F_1TANK_1GAS_GAS_PRESSURE_NO9				0x0068//采集气瓶压力，第九次
#define		COMMAND_09_0026_F_1TANK_1GAS_TIME_30S_START_NO9				0x0069//计时30s计时开始，第九次
#define		COMMAND_09_0027_F_1TANK_1GAS_IS_TIME_30S_NO9				0x006a//判断定时30s，第九次
#define		COMMAND_09_0028_F_1TANK_1GAS_GAS_PRESSURE_NO10				0x006b//采集气瓶压力，第十次
#define		COMMAND_09_0029_F_1TANK_1GAS_IS_GAS_PRESSURE				0x006c//压差判断气瓶压力是否升高

//判断气瓶抽气是否结束
#define		COMMAND_09_0001_F_1TANK_1GAS_IS_COMP_GAS_OVER				0x006d//判断气瓶抽气是否结束

//关燃路气瓶补加阀门
#define		COMMAND_09_0001_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO1			0x006e//关燃路气瓶补加阀门，第一组
#define		COMMAND_09_0002_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO1		0x006f//判断关燃路气瓶补加阀门，第一组
#define		COMMAND_09_0003_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO2			0x0070//关燃路气瓶补加阀门，第二组
#define		COMMAND_09_0004_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO2		0x0071//判断关燃路气瓶补加阀门，第二组
#define		COMMAND_09_0005_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO3			0x0072//关燃路气瓶补加阀门，第三组
#define		COMMAND_09_0006_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO3		0x0073//判断关燃路气瓶补加阀门，第三组

//通过压力判断高压气路隔离是否正常，第一次
#define		COMMAND_09_0001_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO1	0x0074//采集压气机出口压力，第一次
#define		COMMAND_09_0002_F_1TANK_1GAS_FIRST_TIME_12S_START_NO1		0x0075//计时12s计时开始，第一次
#define		COMMAND_09_0003_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO1			0x0076//判断定时12s，第一次
#define		COMMAND_09_0004_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO2	0x0077//采集压气机出口压力，第二次
#define		COMMAND_09_0005_F_1TANK_1GAS_FIRST_TIME_12S_START_NO2		0x0078//计时12s计时开始，第二次
#define		COMMAND_09_0006_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO2			0x0079//判断定时12s，第二次
#define		COMMAND_09_0007_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO3	0x007a//采集压气机出口压力，第三次
#define		COMMAND_09_0008_F_1TANK_1GAS_FIRST_TIME_12S_START_NO3		0x007b//计时12s计时开始，第三次
#define		COMMAND_09_0009_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO3			0x007c//判断定时12s，第三次
#define		COMMAND_09_0010_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO4	0x007d//采集压气机出口压力，第四次
#define		COMMAND_09_0011_F_1TANK_1GAS_FIRST_IS_ISOLATION				0x007e//通过压力判断高压气路隔离是否正常

//关闭燃压气机出口阀门
#define		COMMAND_09_0001_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1			0x007f//关闭燃压气机出口阀门，第一组
#define		COMMAND_09_0002_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x0080//判断关闭燃压气机出口阀门，第一组
#define		COMMAND_09_0003_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2			0x0081//关闭燃压气机出口阀门，第二组
#define		COMMAND_09_0004_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x0082//判断关闭燃压气机出口阀门，第二组
#define		COMMAND_09_0005_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3			0x0083//关闭燃压气机出口阀门，第三组
#define		COMMAND_09_0006_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x0084//判断关闭燃压气机出口阀门，第三组

//通过压力判断高压气路隔离是否正常，第二次
#define		COMMAND_09_0001_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO1	0x0085//采集压气机出口压力，第一次
#define		COMMAND_09_0002_F_1TANK_1GAS_SECOND_TIME_12S_START_NO1		0x0086//计时12s计时开始，第一次
#define		COMMAND_09_0003_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO1			0x0087//判断定时12s，第一次
#define		COMMAND_09_0004_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO2	0x0088//采集压气机出口压力，第二次
#define		COMMAND_09_0005_F_1TANK_1GAS_SECOND_TIME_12S_START_NO2		0x0089//计时12s计时开始，第二次
#define		COMMAND_09_0006_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO2			0x008a//判断定时12s，第二次
#define		COMMAND_09_0007_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO3	0x008b//采集压气机出口压力，第三次
#define		COMMAND_09_0008_F_1TANK_1GAS_SECOND_TIME_12S_START_NO3		0x008c//计时12s计时开始，第三次
#define		COMMAND_09_0009_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO3			0x008d//判断定时12s，第三次
#define		COMMAND_09_0010_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO4	0x008e//采集压气机出口压力，第四次
#define		COMMAND_09_0011_F_1TANK_1GAS_SECOND_IS_ISOLATION			0x008f//通过压力判断高压气路隔离是否正常

//燃压气机停机
#define		COMMAND_09_0001_F_1TANK_1GAS_COMPRESSOR_STOP				0x0090//申请设备管理指令，压气机停机
#define		COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START		0x0091//延时1min计时开始
#define		COMMAND_09_0003_F_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN		0x0092//判断1min定时

//判断燃压气机停机是否正常
#define		COMMAND_09_0001_F_1TANK_1GAS_COMPRESSOR_V_NO1				0x0093//采集电机转速，第一次
#define		COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_V_NO2				0x0094//采集电机转速，第二次
#define		COMMAND_09_0003_F_1TANK_1GAS_COMPRESSOR_V_NO3				0x0095//采集电机转速，第三次
#define		COMMAND_09_0004_F_1TANK_1GAS_COMPRESSOR_V_NO4				0x0096//采集电机转速，第四次
#define		COMMAND_09_0005_F_1TANK_1GAS_COMPRESSOR_V_NO5				0x0097//采集电机转速，第五次
#define		COMMAND_09_0006_F_1TANK_1GAS_COMPRESSOR_V_NO6				0x0098//采集电机转速，第六次
#define		COMMAND_09_0007_F_1TANK_1GAS_COMPRESSOR_V_NO7				0x0099//采集电机转速，第七次
#define		COMMAND_09_0008_F_1TANK_1GAS_COMPRESSOR_V_NO8				0x009a//采集电机转速，第八次
#define		COMMAND_09_0009_F_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO1	0x009b//采集压气机出口压力，第一次
#define		COMMAND_09_0010_F_1TANK_1GAS_TIME_12S_START					0x009c//计时12s计时开始
#define		COMMAND_09_0011_F_1TANK_1GAS_IS_TIME_12S					0x009d//判断定时12s
#define		COMMAND_09_0012_F_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO2	0x009e//采集压气机出口压力，第二次
#define		COMMAND_09_0013_F_1TANK_1GAS_IS_COMPRESSOR_STOP				0x009f//判断燃压气机停机是否正常

//开燃压气机旁路自锁阀
#define		COMMAND_09_0001_F_1TANK_1GAS_BYPATH_VALVE_ON				0x00a0//开燃压气机旁路自锁阀
#define		COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_ON				0x00a1//判断开燃压气机旁路自锁阀

//延时等待time_bypath
#define		COMMAND_09_0001_F_1TANK_1GAS_TIME_BYPATH_START				0x00a2//延时等待time_bypath计时开启
#define		COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_BYPATH					0x00a3//判断延时等待time_bypath

//关燃压气机旁路自锁阀
#define		COMMAND_09_0001_F_1TANK_1GAS_BYPATH_VALVE_OFF				0x00a4//关燃压气机旁路自锁阀
#define		COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_OFF			0x00a5//判断关燃压气机旁路自锁阀

//关闭燃压气机出口阀门
#define		COMMAND_09_0001_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1			0x00a6//关闭燃压气机出口阀门，第一组
#define		COMMAND_09_0002_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x00a7//判断关闭燃压气机出口阀门，第一组
#define		COMMAND_09_0003_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2			0x00a8//关闭燃压气机出口阀门，第二组
#define		COMMAND_09_0004_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x00a9//判断关闭燃压气机出口阀门，第二组
#define		COMMAND_09_0005_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3			0x00aa//关闭燃压气机出口阀门，第三组
#define		COMMAND_09_0006_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x00ab//判断关闭燃压气机出口阀门，第三组

//关闭燃压气机进口阀门
#define		COMMAND_09_0001_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x00ac//关闭燃压气机进口阀门，第一组
#define		COMMAND_09_0002_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1		0x00ad//判断关闭燃压气机进口阀门，第一组
#define		COMMAND_09_0003_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x00ae//关闭燃压气机进口阀门，第二组
#define		COMMAND_09_0004_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2		0x00af//判断关闭燃压气机进口阀门，第二组
#define		COMMAND_09_0005_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x00b0//关闭燃压气机进口阀门，第三组
#define		COMMAND_09_0006_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3		0x00b1//判断关闭燃压气机进口阀门，第三组

//关进贮箱低压气路补加阀门
#define		COMMAND_09_0001_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO1				0x00b2//关进贮箱低压气路补加阀门，第一组
#define		COMMAND_09_0002_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO1			0x00b3//判断关进贮箱低压气路补加阀门，第一组
#define		COMMAND_09_0003_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO2				0x00b4//关进贮箱低压气路补加阀门，第二组
#define		COMMAND_09_0004_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO2			0x00b5//判断关进贮箱低压气路补加阀门，第二组
#define		COMMAND_09_0005_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO3				0x00b6//关进贮箱低压气路补加阀门，第三组
#define		COMMAND_09_0006_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO3			0x00b7//判断关进贮箱低压气路补加阀门，第三组

//设置燃抽气状态好
#define		COMMAND_09_0001_F_1TANK_1GAS_SET_STATE_GOOD						0x00b8//设置燃抽气状态好

//判断压气机温度是否正常
#define		COMMAND_09_0001_F_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE			0x00b9//判断压气机温度是否正常


//延时等待time_delay3
#define		COMMAND_09_0001_F_1TANK_1GAS_TIME_DELAY3_START					0x00bb//延时等待time_delay3计时开始
#define		COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_DELAY3						0x00bc//判断延时等待time_delay3

//启动液冷模块切换程序
#define		COMMAND_09_0001_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO1			0x00bd//液冷模块切换程序，阀门动作，第一组
#define		COMMAND_09_0002_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x00be//判断液冷模块切换程序，阀门动作，第一组
#define		COMMAND_09_0003_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO2			0x00bf//液冷模块切换程序，阀门动作，第二组
#define		COMMAND_09_0004_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x00c0//判断液冷模块切换程序，阀门动作，第二组
#define		COMMAND_09_0005_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO3			0x00c1//液冷模块切换程序，阀门动作，第三组
#define		COMMAND_09_0006_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x00c2//判断液冷模块切换程序，阀门动作，第三组
#define		COMMAND_09_0007_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO4			0x00c3//液冷模块切换程序，阀门动作，第四组
#define		COMMAND_09_0008_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x00c4//判断液冷模块切换程序，阀门动作，第四组

//通过压力判断液冷模块切换是否正常
#define		COMMAND_09_0001_F_1TANK_1GAS_IS_EXCHANGE_COOLER					0x00c5//通过压力判断液冷模块切换是否正常

//液冷模块停机
#define		COMMAND_09_0001_F_1TANK_1GAS_COOLER_POWER_OFF					0x00c6//液冷模块停机

//申请压气机断电
#define		COMMAND_09_0001_F_1TANK_1GAS_COMPRESSOR_POWER_OFF				0x00c7//申请设备管理指令

//申请电机驱动器断电
#define		COMMAND_09_0001_F_1TANK_1GAS_TGTHT530_POWER_OFF					0x00c8//申请设备管理指令
#define		COMMAND_09_0002_F_1TANK_1GAS_TGTHT530_TIME_1MIN_START			0x00c9//延时1min计时开始
#define		COMMAND_09_0003_F_1TANK_1GAS_TGTHT530_IS_TIME_1MIN				0x00ca//判断计时1min是否到

//------------------------------command---第三个贮箱抽气----两个气瓶抽气-----------------------------------

//开进气瓶补加阀门---第一个气瓶
#define		COMMAND_09_0001_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON				0x00cb//开进气瓶补加阀门
#define		COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_ON			0x00cc//判断开进气瓶补加阀门


//延时等待time_delay2---第一个气瓶
#define		COMMAND_09_0001_F_1TANK_2GAS_GAS1_TIME_DELAY2_START				0x00cd//延时等待time_delay2计时开始
#define		COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_TIME_DELAY2				0x00ce//判断延时等待time_delay2

//判断气瓶压力是否升高---第一个气瓶
#define		COMMAND_09_0001_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO1				0x00cf//采集气瓶压力，第一次
#define		COMMAND_09_0002_F_1TANK_2GAS_GAS1_TIME_30S_START_NO1			0x00d0//计时30s计时开始，第一次
#define		COMMAND_09_0003_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO1				0x00d1//判断定时30s，第一次
#define		COMMAND_09_0004_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO2				0x00d2//采集气瓶压力，第二次
#define		COMMAND_09_0005_F_1TANK_2GAS_GAS1_TIME_30S_START_NO2			0x00d3//计时30s计时开始，第二次
#define		COMMAND_09_0006_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO2				0x00d4//判断定时30s，第二次
#define		COMMAND_09_0007_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO3				0x00d5//采集气瓶压力，第三次
#define		COMMAND_09_0008_F_1TANK_2GAS_GAS1_TIME_30S_START_NO3			0x00d6//计时30s计时开始，第三次
#define		COMMAND_09_0009_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO3				0x00d7//判断定时30s，第三次
#define		COMMAND_09_0010_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO4				0x00d8//采集气瓶压力，第四次
#define		COMMAND_09_0011_F_1TANK_2GAS_GAS1_TIME_30S_START_NO4			0x00d9//计时30s计时开始，第四次
#define		COMMAND_09_0012_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO4				0x00da//判断定时30s，第四次
#define		COMMAND_09_0013_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO5				0x00db//采集气瓶压力，第五次
#define		COMMAND_09_0014_F_1TANK_2GAS_GAS1_TIME_30S_START_NO5			0x00dc//计时30s计时开始，第五次
#define		COMMAND_09_0015_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO5				0x00dd//判断定时30s，第五次
#define		COMMAND_09_0016_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO6				0x00de//采集气瓶压力，第六次
#define		COMMAND_09_0017_F_1TANK_2GAS_GAS1_TIME_30S_START_NO6			0x00df//计时30s计时开始，第六次
#define		COMMAND_09_0018_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO6				0x00e0//判断定时30s，第六次
#define		COMMAND_09_0019_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO7				0x00e1//采集气瓶压力，第七次
#define		COMMAND_09_0020_F_1TANK_2GAS_GAS1_TIME_30S_START_NO7			0x00e2//计时30s计时开始，第七次
#define		COMMAND_09_0021_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO7				0x00e3//判断定时30s，第七次
#define		COMMAND_09_0022_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO8				0x00e4//采集气瓶压力，第八次
#define		COMMAND_09_0023_F_1TANK_2GAS_GAS1_TIME_30S_START_NO8			0x00e5//计时30s计时开始，第八次
#define		COMMAND_09_0024_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO8				0x00e6//判断定时30s，第八次
#define		COMMAND_09_0025_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO9				0x00e7//采集气瓶压力，第九次
#define		COMMAND_09_0026_F_1TANK_2GAS_GAS1_TIME_30S_START_NO9			0x00e8//计时30s计时开始，第九次
#define		COMMAND_09_0027_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO9				0x00e9//判断定时30s，第九次
#define		COMMAND_09_0028_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO10				0x00ea//采集气瓶压力，第十次
#define		COMMAND_09_0029_F_1TANK_2GAS_GAS1_IS_GAS_PRESSURE				0x00eb//压差判断气瓶压力是否升高


//判断气瓶抽气是否结束---第一个气瓶
#define		COMMAND_09_0001_F_1TANK_2GAS_GAS1_IS_COMP_GAS_OVER				0x00ec//判断气瓶抽气是否结束


//关燃路气瓶补加阀门---第一个气瓶
#define		COMMAND_09_0001_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1			0x00ed//关燃路气瓶补加阀门，第一组
#define		COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1		0x00ee//判断关燃路气瓶补加阀门，第一组
#define		COMMAND_09_0003_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2			0x00ef//关燃路气瓶补加阀门，第二组
#define		COMMAND_09_0004_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2		0x00f0//判断关燃路气瓶补加阀门，第二组
#define		COMMAND_09_0005_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3			0x00f1//关燃路气瓶补加阀门，第三组
#define		COMMAND_09_0006_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3		0x00f2//判断关燃路气瓶补加阀门，第三组

//开进气瓶补加阀门---第二个气瓶
#define		COMMAND_09_0001_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON				0x00f3//开进气瓶补加阀门
#define		COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_ON			0x00f4//判断开进气瓶补加阀门


//延时等待time_delay2---第二个气瓶
#define		COMMAND_09_0001_F_1TANK_2GAS_GAS2_TIME_DELAY2_START				0x00f5//延时等待time_delay2计时开始
#define		COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_TIME_DELAY2				0x00f6//判断延时等待time_delay2



//判断气瓶压力是否升高---第二个气瓶
#define		COMMAND_09_0001_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO1				0x00f7//采集气瓶压力，第一次
#define		COMMAND_09_0002_F_1TANK_2GAS_GAS2_TIME_30S_START_NO1			0x00f8//计时30s计时开始，第一次
#define		COMMAND_09_0003_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO1				0x00f9//判断定时30s，第一次
#define		COMMAND_09_0004_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO2				0x00fa//采集气瓶压力，第二次
#define		COMMAND_09_0005_F_1TANK_2GAS_GAS2_TIME_30S_START_NO2			0x00fb//计时30s计时开始，第二次
#define		COMMAND_09_0006_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO2				0x00fc//判断定时30s，第二次
#define		COMMAND_09_0007_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO3				0x00fd//采集气瓶压力，第三次
#define		COMMAND_09_0008_F_1TANK_2GAS_GAS2_TIME_30S_START_NO3			0x00fe//计时30s计时开始，第三次
#define		COMMAND_09_0009_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO3				0x00ff//判断定时30s，第三次
#define		COMMAND_09_0010_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO4				0x0100//采集气瓶压力，第四次
#define		COMMAND_09_0011_F_1TANK_2GAS_GAS2_TIME_30S_START_NO4			0x0101//计时30s计时开始，第四次
#define		COMMAND_09_0012_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO4				0x0102//判断定时30s，第四次
#define		COMMAND_09_0013_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO5				0x0103//采集气瓶压力，第五次
#define		COMMAND_09_0014_F_1TANK_2GAS_GAS2_TIME_30S_START_NO5			0x0104//计时30s计时开始，第五次
#define		COMMAND_09_0015_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO5				0x0105//判断定时30s，第五次
#define		COMMAND_09_0016_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO6				0x0106//采集气瓶压力，第六次
#define		COMMAND_09_0017_F_1TANK_2GAS_GAS2_TIME_30S_START_NO6			0x0107//计时30s计时开始，第六次
#define		COMMAND_09_0018_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO6				0x0108//判断定时30s，第六次
#define		COMMAND_09_0019_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO7				0x0109//采集气瓶压力，第七次
#define		COMMAND_09_0020_F_1TANK_2GAS_GAS2_TIME_30S_START_NO7			0x010a//计时30s计时开始，第七次
#define		COMMAND_09_0021_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO7				0x010b//判断定时30s，第七次
#define		COMMAND_09_0022_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO8				0x010c//采集气瓶压力，第八次
#define		COMMAND_09_0023_F_1TANK_2GAS_GAS2_TIME_30S_START_NO8			0x010d//计时30s计时开始，第八次
#define		COMMAND_09_0024_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO8				0x010e//判断定时30s，第八次
#define		COMMAND_09_0025_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO9				0x010f//采集气瓶压力，第九次
#define		COMMAND_09_0026_F_1TANK_2GAS_GAS2_TIME_30S_START_NO9			0x0110//计时30s计时开始，第九次
#define		COMMAND_09_0027_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO9				0x0111//判断定时30s，第九次
#define		COMMAND_09_0028_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO10				0x0112//采集气瓶压力，第十次
#define		COMMAND_09_0029_F_1TANK_2GAS_GAS2_IS_GAS_PRESSURE				0x0113//压差判断气瓶压力是否升高

//判断气瓶抽气是否结束---第二个气瓶
#define		COMMAND_09_0001_F_1TANK_2GAS_GAS2_IS_COMP_GAS_OVER				0x0114//判断气瓶抽气是否结束


//关燃路气瓶补加阀门---第二个气瓶
#define		COMMAND_09_0001_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1			0x0115//关燃路气瓶补加阀门，第一组
#define		COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1		0x0116//判断关燃路气瓶补加阀门，第一组
#define		COMMAND_09_0003_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2			0x0117//关燃路气瓶补加阀门，第二组
#define		COMMAND_09_0004_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2		0x0118//判断关燃路气瓶补加阀门，第二组
#define		COMMAND_09_0005_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3			0x0119//关燃路气瓶补加阀门，第三组
#define		COMMAND_09_0006_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3		0x011a//判断关燃路气瓶补加阀门，第三组

//通过压力判断高压气路隔离是否正常，第一次
#define		COMMAND_09_0001_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO1	0x011b//采集压气机出口压力，第一次
#define		COMMAND_09_0002_F_1TANK_2GAS_FIRST_TIME_12S_START_NO1		0x011c//计时12s计时开始，第一次
#define		COMMAND_09_0003_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO1			0x011d//判断定时12s，第一次
#define		COMMAND_09_0004_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO2	0x011e//采集压气机出口压力，第二次
#define		COMMAND_09_0005_F_1TANK_2GAS_FIRST_TIME_12S_START_NO2		0x011f//计时12s计时开始，第二次
#define		COMMAND_09_0006_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO2			0x0120//判断定时12s，第二次
#define		COMMAND_09_0007_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO3	0x0121//采集压气机出口压力，第三次
#define		COMMAND_09_0008_F_1TANK_2GAS_FIRST_TIME_12S_START_NO3		0x0122//计时12s计时开始，第三次
#define		COMMAND_09_0009_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO3			0x0123//判断定时12s，第三次
#define		COMMAND_09_0010_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO4	0x0124//采集压气机出口压力，第四次
#define		COMMAND_09_0011_F_1TANK_2GAS_FIRST_IS_ISOLATION				0x0125//通过压力判断高压气路隔离是否正常

//关闭燃压气机出口阀门
#define		COMMAND_09_0001_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x0126//关闭燃压气机出口阀门，第一组
#define		COMMAND_09_0002_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1	0x0127//判断关闭燃压气机出口阀门，第一组
#define		COMMAND_09_0003_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x0128//关闭燃压气机出口阀门，第二组
#define		COMMAND_09_0004_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2	0x0129//判断关闭燃压气机出口阀门，第二组
#define		COMMAND_09_0005_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x012a//关闭燃压气机出口阀门，第三组
#define		COMMAND_09_0006_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3	0x012b//判断关闭燃压气机出口阀门，第三组

//通过压力判断高压气路隔离是否正常，第二次
#define		COMMAND_09_0001_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO1	0x012c//采集压气机出口压力，第一次
#define		COMMAND_09_0002_F_1TANK_2GAS_SECOND_TIME_12S_START_NO1		0x012d//计时12s计时开始，第一次
#define		COMMAND_09_0003_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO1			0x012e//判断定时12s，第一次
#define		COMMAND_09_0004_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO2	0x012f//采集压气机出口压力，第二次
#define		COMMAND_09_0005_F_1TANK_2GAS_SECOND_TIME_12S_START_NO2		0x0130//计时12s计时开始，第二次
#define		COMMAND_09_0006_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO2			0x0131//判断定时12s，第二次
#define		COMMAND_09_0007_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO3	0x0132//采集压气机出口压力，第三次
#define		COMMAND_09_0008_F_1TANK_2GAS_SECOND_TIME_12S_START_NO3		0x0133//计时12s计时开始，第三次
#define		COMMAND_09_0009_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO3			0x0134//判断定时12s，第三次
#define		COMMAND_09_0010_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO4	0x0135//采集压气机出口压力，第四次
#define		COMMAND_09_0011_F_1TANK_2GAS_SECOND_IS_ISOLATION			0x0136//通过压力判断高压气路隔离是否正常

//燃压气机停机
#define		COMMAND_09_0001_F_1TANK_2GAS_COMPRESSOR_STOP					0x0137//申请设备管理指令，压气机停机
#define		COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START			0x0138//延时1min计时开始
#define		COMMAND_09_0003_F_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN			0x0139//判断1min定时


//判断燃压气机停机是否正常
#define		COMMAND_09_0001_F_1TANK_2GAS_COMPRESSOR_V_NO1					0x013a//采集电机转速，第一次
#define		COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_V_NO2					0x013b//采集电机转速，第二次
#define		COMMAND_09_0003_F_1TANK_2GAS_COMPRESSOR_V_NO3					0x013c//采集电机转速，第三次
#define		COMMAND_09_0004_F_1TANK_2GAS_COMPRESSOR_V_NO4					0x013d//采集电机转速，第四次
#define		COMMAND_09_0005_F_1TANK_2GAS_COMPRESSOR_V_NO5					0x013e//采集电机转速，第五次
#define		COMMAND_09_0006_F_1TANK_2GAS_COMPRESSOR_V_NO6					0x013f//采集电机转速，第六次
#define		COMMAND_09_0007_F_1TANK_2GAS_COMPRESSOR_V_NO7					0x0140//采集电机转速，第七次
#define		COMMAND_09_0008_F_1TANK_2GAS_COMPRESSOR_V_NO8					0x0141//采集电机转速，第八次
#define		COMMAND_09_0009_F_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO1		0x0142//采集压气机出口压力，第一次
#define		COMMAND_09_0010_F_1TANK_2GAS_TIME_12S_START						0x0143//计时12s计时开始
#define		COMMAND_09_0011_F_1TANK_2GAS_IS_TIME_12S						0x0144//判断定时12s
#define		COMMAND_09_0012_F_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO2		0x0145//采集压气机出口压力，第二次
#define		COMMAND_09_0013_F_1TANK_2GAS_IS_COMPRESSOR_STOP					0x0146//判断燃压气机停机是否正常

//开燃压气机旁路自锁阀
#define		COMMAND_09_0001_F_1TANK_2GAS_BYPATH_VALVE_ON					0x0147//开燃压气机旁路自锁阀
#define		COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_ON					0x0148//判断开燃压气机旁路自锁阀


//延时等待time_bypath
#define		COMMAND_09_0001_F_1TANK_2GAS_TIME_BYPATH_START					0x0149//延时等待time_bypath计时开启
#define		COMMAND_09_0002_F_1TANK_2GAS_IS_TIME_BYPATH						0x014a//判断延时等待time_bypath


//关燃压气机旁路自锁阀
#define		COMMAND_09_0001_F_1TANK_2GAS_BYPATH_VALVE_OFF					0x014b//关燃压气机旁路自锁阀
#define		COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_OFF				0x014c//判断关燃压气机旁路自锁阀

//关闭燃压气机出口阀门
#define		COMMAND_09_0001_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1			0x014d//关闭燃压气机出口阀门，第一组
#define		COMMAND_09_0002_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x014e//判断关闭燃压气机出口阀门，第一组
#define		COMMAND_09_0003_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2			0x014f//关闭燃压气机出口阀门，第二组
#define		COMMAND_09_0004_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x0150//判断关闭燃压气机出口阀门，第二组
#define		COMMAND_09_0005_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3			0x0151//关闭燃压气机出口阀门，第三组
#define		COMMAND_09_0006_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x0152//判断关闭燃压气机出口阀门，第三组

//关闭燃压气机进口阀门
#define		COMMAND_09_0001_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x0153//关闭燃压气机进口阀门，第一组
#define		COMMAND_09_0002_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1		0x0154//判断关闭燃压气机进口阀门，第一组
#define		COMMAND_09_0003_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0155//关闭燃压气机进口阀门，第二组
#define		COMMAND_09_0004_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0156//判断关闭燃压气机进口阀门，第二组
#define		COMMAND_09_0005_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x0157//关闭燃压气机进口阀门，第三组
#define		COMMAND_09_0006_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3		0x0158//判断关闭燃压气机进口阀门，第三组


//关进贮箱低压气路补加阀门
#define		COMMAND_09_0001_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO1				0x0159//关进贮箱低压气路补加阀门，第一组
#define		COMMAND_09_0002_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO1			0x015a//判断关进贮箱低压气路补加阀门，第一组
#define		COMMAND_09_0003_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO2				0x015b//关进贮箱低压气路补加阀门，第二组
#define		COMMAND_09_0004_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO2			0x015c//判断关进贮箱低压气路补加阀门，第二组
#define		COMMAND_09_0005_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO3				0x015d//关进贮箱低压气路补加阀门，第三组
#define		COMMAND_09_0006_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO3			0x015e//判断关进贮箱低压气路补加阀门，第三组


//设置燃抽气状态好
#define		COMMAND_09_0001_F_1TANK_2GAS_SET_STATE_GOOD						0x015f//设置燃抽气状态好


//判断压气机温度是否正常
#define		COMMAND_09_0001_F_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE			0x0160//判断压气机温度是否正常

//延时等待time_delay3
#define		COMMAND_09_0001_F_1TANK_2GAS_TIME_DELAY3_START					0x0161//延时等待time_delay3计时开始
#define		COMMAND_09_0002_F_1TANK_2GAS_IS_TIME_DELAY3						0x0162//判断延时等待time_delay3


//启动液冷模块切换程序
#define		COMMAND_09_0001_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO1			0x0163//液冷模块切换程序,阀门动作，第一组
#define		COMMAND_09_0002_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x0164//判断液冷模块切换程序,阀门动作，第一组
#define		COMMAND_09_0003_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO2			0x0165//液冷模块切换程序,阀门动作，第二组
#define		COMMAND_09_0004_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x0166//判断液冷模块切换程序,阀门动作，第二组
#define		COMMAND_09_0005_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO3			0x0167//液冷模块切换程序,阀门动作，第三组
#define		COMMAND_09_0006_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x0168//判断液冷模块切换程序,阀门动作，第三组
#define		COMMAND_09_0007_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO4			0x0169//液冷模块切换程序,阀门动作，第四组
#define		COMMAND_09_0008_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x016a//判断液冷模块切换程序,阀门动作，第四组

//通过压力判断液冷模块切换是否正常
#define		COMMAND_09_0001_F_1TANK_2GAS_IS_EXCHANGE_COOLER					0x016b//通过压力判断液冷模块切换是否正常

//液冷模块停机
#define		COMMAND_09_0001_F_1TANK_2GAS_COOLER_POWER_OFF					0x016c//液冷模块停机

//申请压气机断电
#define		COMMAND_09_0001_F_1TANK_2GAS_COMPRESSOR_POWER_OFF				0x016d//申请设备管理指令

//申请电机驱动器断电
#define		COMMAND_09_0001_F_1TANK_2GAS_TGTHT530_POWER_OFF					0x016e//申请设备管理指令
#define		COMMAND_09_0002_F_1TANK_2GAS_TGTHT530_TIME_1MIN_START			0x016f//延时1min计时开始
#define		COMMAND_09_0003_F_1TANK_2GAS_TGTHT530_IS_TIME_1MIN				0x0170//判断计时1min是否到


//------------------------函数声明---------------------------------------------------------

void TGTHT510_supply_stage09_comp_F_main(void);

//-------------------------------------------------初始设置阶段----------------------------------------------------

uint16 TGTHT510_supply_stage09_comp_F_init_step_start_cooler(void);
uint16 TGTHT510_supply_stage09_comp_F_init_step_is_cooler_work(void);
uint16 TGTHT510_supply_stage09_comp_F_init_step_time_delay(void);
uint16 TGTHT510_supply_stage09_comp_F_init_step_is_compressor_temperature(void);
uint16 TGTHT510_supply_stage09_comp_F_init_step_TGTHT530_power_on(void);
uint16 TGTHT510_supply_stage09_comp_F_init_step_compressor_power_on(void);
uint16 TGTHT510_supply_stage09_comp_F_init_step_isolation(void);

//-------------------------------------------------一个贮箱抽气----------------------------------------------------
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_is_in_tank_valve_on_pressure(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_in_compressor_valve_on(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_time_delay1(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_is_in_compressor_pressure(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_compressor_start(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_is_out_compressor_pressure(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_out_compressor_valve_on(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_number_comp_gas(void);

//-----------------------------------一个贮箱抽气，一个气瓶抽气----------------------------------------------------
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay2(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_comp_over(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_compressor_temperature(void);

uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay3(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_exchange_cooler(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_exchange_cooler(void);

uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_TGTHT530_power_off(void);

//-----------------------------------一个贮箱抽气，两个气瓶抽气----------------------------------------------------
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_time_delay2(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_is_comp_over(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_time_delay2(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_is_comp_over(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_compressor_temperature(void);

uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_time_delay3(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_exchange_cooler(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_exchange_cooler(void);

uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_TGTHT530_power_off(void);

//---------------------------------------------------------通用函数------------------------------------------------

void TGTHT510_supply_command_third_isolation_valve_off(uint16 n,uint16 isolation_tank);
uint16 TGTHT510_supply_command_is_third_isolation_valve_off(uint16 n,uint16 isolation_tank);



#endif

