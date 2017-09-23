/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器补加流程主程序头文件
  ******************************************************************************
  */
 
#ifndef __supply_stage_13_comp_o_h
#define __supply_stage_13_comp_o_h
 

/*声明结构体类型--------------------------------------------------------------*/



/*宏定义---------------------------------------------------------------------------*/

//步骤step-------------------------------------------------------------------------

//----------------------------------初始设置阶段-----------------------------------

#define 	STEP_13_O_INIT_START_COOLER							0x0000//启动液冷泵工作
#define 	STEP_13_O_INIT_IS_COOLER_WORK						0x0001//通过转速判断液冷工作是否正常
#define 	STEP_13_O_INIT_DELAY								0x0002//延时等待时间
#define		STEP_13_O_INIT_IS_COMPRESSOR_TEMPERATURE			0x0003//判断压气机温度是否正常
#define		STEP_13_O_INIT_TGTHT530_POWER_ON					0x0004//申请电机驱动器加电
#define		STEP_13_O_INIT_COMPRESSOR_POWER_ON					0x0005//申请压气机加电
#define		STEP_13_O_INIT_ISOLATION							0x0006//贮箱隔离
#define		STEP_13_O_INIT_NUMBER_COMP_TANK						0x0007//判断抽气贮箱个数

//----------------------------------一个贮箱抽气-----------------------------------

#define 	STEP_13_O_1TANK_IN_TANK_VALVE_ON					0x0008//开进贮箱低压气路补加阀门

#define 	STEP_13_O_1TANK_TIME_DELAY_A						0x009e//延时等待

#define 	STEP_13_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE		0x0009//通过压力判断开进贮箱低压气路补加阀门
#define 	STEP_13_O_1TANK_IN_COMPRESSOR_VALVE_ON				0x000a//开氧压气机进口阀门
#define 	STEP_13_O_1TANK_TIME_DELAY1							0x000b//延时等待time_delay1
#define 	STEP_13_O_1TANK_IS_IN_COMPRESSOR_PRESSURE			0x000c//判断压气机进口压力是否正常
#define 	STEP_13_O_1TANK_COMPRESSOR_START					0x000d//氧压气机启动

#define 	STEP_13_O_1TANK_TIME_DELAY_B						0x009f//延时等待

#define 	STEP_13_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE			0x000e//判断压气机出口压力是否正常
#define 	STEP_13_O_1TANK_OUT_COMPRESSOR_VALVE_ON				0x000f//开氧压气机出口阀门
#define 	STEP_13_O_1TANK_NUMBER_COMP_GAS						0x0010//判断抽气气瓶个数

//一个气瓶抽气
#define 	STEP_13_O_1TANK_1GAS_IN_GAS_VALVE_ON				0x0011//开进气瓶补加阀门
#define 	STEP_13_O_1TANK_1GAS_TIME_DELAY2					0x0012//延时等待time_delay2
#define 	STEP_13_O_1TANK_1GAS_IS_GAS_PRESSURE				0x0013//判断气瓶压力是否升高
#define 	STEP_13_O_1TANK_1GAS_IS_COMP_OVER					0x0014//判断气瓶抽气是否结束
#define 	STEP_13_O_1TANK_1GAS_IN_GAS_VALVE_OFF				0x0015//关氧路气瓶补加阀门

#define		STEP_13_O_1TANK_1GAS_IS_ISOLATION_FIRST				0x0016//通过压力判断高压气路隔离是否正常，第一次
#define 	STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF		0x0017//关闭氧压气机出口阀门
#define		STEP_13_O_1TANK_1GAS_IS_ISOLATION_SECOND			0x0018//通过压力判断高压气路隔离是否正常，第二次

#define		STEP_13_O_1TANK_1GAS_COMPRESSOR_STOP				0x0019//氧压气机停机
#define		STEP_13_O_1TANK_1GAS_IS_COMPRESSOR_STOP				0x001a//判断氧压气机停机是否正常
#define		STEP_13_O_1TANK_1GAS_BYPATH_VALVE_ON				0x001b//开氧压气机旁路自锁阀
#define 	STEP_13_O_1TANK_1GAS_TIME_DELAY_BYPATH				0x001c//延时等待time_bypath
#define		STEP_13_O_1TANK_1GAS_BYPATH_VALVE_OFF				0x001d//关氧压气机旁路自锁阀
#define 	STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2		0x001e//关闭氧压气机出口阀门，第二次
#define 	STEP_13_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF		0x001f//关闭氧压气机进口阀门
#define 	STEP_13_O_1TANK_1GAS_IN_TANK_VALVE_OFF				0x0020//关进贮箱低压气路补加阀门
#define 	STEP_13_O_1TANK_1GAS_SET_STATE_GOOD					0x0021//设置氧抽气状态好
#define 	STEP_13_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE		0x0022//判断压气机温度是否正常
#define 	STEP_13_O_1TANK_1GAS_IS_NEED_COOLER_STOP			0x0023//判断是否需要进行液冷模块停机
//#define 	STEP_13_O_1TANK_1GAS_IS_NEED_EXCHANGE				0x0023//判断是否需要进行液冷模块切换程序

#define 	STEP_13_O_1TANK_1GAS_TIME_DELAY3					0x0024//延时等待time_delay3
//#define 	STEP_13_O_1TANK_1GAS_EXCHANGE_COOLER				0x0025//启动液冷模块切换程序
//#define	STEP_13_O_1TANK_1GAS_IS_EXCHANGE_COOLER				0x0026//通过压力判断液冷模块切换是否正常
#define		STEP_13_O_1TANK_1GAS_COOLER_STOP					0x0025//液冷模块停机

#define		STEP_13_O_1TANK_1GAS_COOLER_SET						0x0026//液冷模块状态设置

#define		STEP_13_O_1TANK_1GAS_COMPRESSOR_POWER_OFF			0x0028//申请压气机断电
#define		STEP_13_O_1TANK_1GAS_TGTHT530_POWER_OFF				0x0029//申请电机驱动器断电

//**************************************程序结束******************************************************************

//两个气瓶抽气
#define 	STEP_13_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON			0x002a//开进气瓶补加阀门---第一个气瓶
#define 	STEP_13_O_1TANK_2GAS_GAS1_TIME_DELAY2				0x002b//延时等待time_delay2---第一个气瓶
#define 	STEP_13_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE			0x002c//判断气瓶压力是否升高---第一个气瓶
#define 	STEP_13_O_1TANK_2GAS_GAS1_IS_COMP_OVER				0x002d//判断气瓶抽气是否结束---第一个气瓶
#define 	STEP_13_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF			0x002e//关氧路气瓶补加阀门---第一个气瓶
#define 	STEP_13_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON			0x002f//开进气瓶补加阀门---第二个气瓶
#define 	STEP_13_O_1TANK_2GAS_GAS2_TIME_DELAY2				0x0030//延时等待time_delay2---第二个气瓶
#define 	STEP_13_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE			0x0031//判断气瓶压力是否升高---第二个气瓶
#define 	STEP_13_O_1TANK_2GAS_GAS2_IS_COMP_OVER				0x0032//判断气瓶抽气是否结束---第二个气瓶
#define 	STEP_13_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF			0x0033//关氧路气瓶补加阀门---第二个气瓶

#define		STEP_13_O_1TANK_2GAS_IS_ISOLATION_FIRST				0x0034//通过压力判断高压气路隔离是否正常，第一次
#define 	STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF		0x0035//关闭氧压气机出口阀门
#define		STEP_13_O_1TANK_2GAS_IS_ISOLATION_SECOND			0x0036//通过压力判断高压气路隔离是否正常，第二次

#define		STEP_13_O_1TANK_2GAS_COMPRESSOR_STOP				0x0037//氧压气机停机
#define		STEP_13_O_1TANK_2GAS_IS_COMPRESSOR_STOP				0x0038//判断氧压气机停机是否正常
#define		STEP_13_O_1TANK_2GAS_BYPATH_VALVE_ON				0x0039//开氧压气机旁路自锁阀
#define 	STEP_13_O_1TANK_2GAS_TIME_DELAY_BYPATH				0x003a//延时等待time_bypath
#define		STEP_13_O_1TANK_2GAS_BYPATH_VALVE_OFF				0x003b//关氧压气机旁路自锁阀
#define 	STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2		0x003c//关闭氧压气机出口阀门，第二次
#define 	STEP_13_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF		0x003d//关闭氧压气机进口阀门
#define 	STEP_13_O_1TANK_2GAS_IN_TANK_VALVE_OFF				0x003e//关进贮箱低压气路补加阀门
#define 	STEP_13_O_1TANK_2GAS_SET_STATE_GOOD					0x003f//设置氧抽气状态好
#define 	STEP_13_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE		0x0040//判断压气机温度是否正常
#define 	STEP_13_O_1TANK_2GAS_IS_NEED_COOLER_STOP			0x0041//判断是否需要进行液冷模块停机

//#define 	STEP_13_O_1TANK_2GAS_IS_NEED_EXCHANGE				0x0041//判断是否需要进行液冷模块切换程序

#define 	STEP_13_O_1TANK_2GAS_TIME_DELAY3					0x0042//延时等待time_delay3
//#define 	STEP_13_O_1TANK_2GAS_EXCHANGE_COOLER				0x0043//启动液冷模块切换程序
//#define		STEP_13_O_1TANK_2GAS_IS_EXCHANGE_COOLER			0x0044//通过压力判断液冷模块切换是否正常
#define		STEP_13_O_1TANK_2GAS_COOLER_STOP					0x0043//液冷模块停机

#define		STEP_13_O_1TANK_2GAS_COOLER_SET						0x0044//液冷模块状态设置

#define		STEP_13_O_1TANK_2GAS_COMPRESSOR_POWER_OFF			0x0046//申请压气机断电
#define		STEP_13_O_1TANK_2GAS_TGTHT530_POWER_OFF				0x0047//申请电机驱动器断电

//**************************************程序结束******************************************************************

//----------------------------------两个贮箱抽气，第一个贮箱抽气-----------------------------------

#define 	STEP_13_O_2TANK_TANK1_IN_TANK_VALVE_ON				0x0048//开进贮箱低压气路补加阀门---第一个贮箱

#define 	STEP_13_O_2TANK_TANK1_TIME_DELAY_C					0x00a0//延时等待

#define 	STEP_13_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE	0x0049//通过压力判断开进贮箱阀门---第一个贮箱
#define 	STEP_13_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON		0x004a//开氧压气机进口阀门---第一个贮箱
#define 	STEP_13_O_2TANK_TANK1_TIME_DELAY1					0x004b//延时等待time_delay1---第一个贮箱
#define 	STEP_13_O_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE		0x004c//判断压气机进口压力是否正常---第一个贮箱
#define 	STEP_13_O_2TANK_TANK1_COMPRESSOR_START				0x004d//氧压气机启动---第一个贮箱

#define 	STEP_13_O_2TANK_TANK1_TIME_DELAY_D					0x00a1//延时等待

#define 	STEP_13_O_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE	0x004e//判断压气机出口压力是否正常---第一个贮箱
#define 	STEP_13_O_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON		0x004f//开氧压气机出口阀门---第一个贮箱
#define 	STEP_13_O_2TANK_TANK1_NUMBER_COMP_GAS				0x0050//判断抽气气瓶个数---第一个贮箱

//一个气瓶抽气
#define 	STEP_13_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON				0x0051//开进气瓶补加阀门---第一个贮箱
#define 	STEP_13_O_2TANK_TANK1_1GAS_TIME_DELAY2					0x0052//延时等待time_delay2---第一个贮箱
#define 	STEP_13_O_2TANK_TANK1_1GAS_IS_GAS_PRESSURE				0x0053//判断气瓶压力是否升高---第一个贮箱
#define 	STEP_13_O_2TANK_TANK1_1GAS_IS_COMP_OVER					0x0054//判断气瓶抽气是否结束---第一个贮箱
#define 	STEP_13_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF				0x0055//关氧路气瓶补加阀门---第一个贮箱
#define 	STEP_13_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF			0x0056//关进贮箱低压气路补加阀门---第一个贮箱
#define 	STEP_13_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE	0x0057//通过压力判断关进贮箱补加阀---第一个贮箱

//**************************************程序转至第二个贮箱抽气*****************************************************

//两个气瓶抽气
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON			0x0058//开进气瓶补加阀门---第一个气瓶
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2				0x0059//延时等待time_delay2---第一个气瓶
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE			0x005a//判断气瓶压力是否升高---第一个气瓶
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS1_IS_COMP_OVER			0x005b//判断气瓶抽气是否结束---第一个气瓶
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF		0x005c//关氧路气瓶补加阀门---第一个气瓶
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON			0x005d//开进气瓶补加阀门---第二个气瓶
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2				0x005e//延时等待time_delay2---第二个气瓶
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE			0x005f//判断气瓶压力是否升高---第二个气瓶
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS2_IS_COMP_OVER			0x0060//判断气瓶抽气是否结束---第二个气瓶
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF		0x0061//关氧路气瓶补加阀门---第二个气瓶
#define 	STEP_13_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF			0x0062//关进贮箱低压气路补加阀门
#define 	STEP_13_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE	0x0063//通过压力判断关进贮箱补加阀

//**************************************程序转至第二个贮箱抽气*****************************************************

//----------------------------------两个贮箱抽气，第二个贮箱抽气-----------------------------------

#define 	STEP_13_O_2TANK_TANK2_IN_TANK_VALVE_ON					0x0064//开进贮箱低压气路补加阀门---第二个贮箱

#define 	STEP_13_O_2TANK_TANK2_TIME_DELAY_E						0x00a2//延时等待

#define 	STEP_13_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE		0x0065//通过压力判断开进贮箱阀门---第二个贮箱
#define 	STEP_13_O_2TANK_TANK2_NUMBER_COMP_GAS					0x0066//判断抽气气瓶个数---第二个贮箱

//一个气瓶抽气
#define 	STEP_13_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON				0x0067//开进气瓶补加阀门---第二个贮箱
#define 	STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY2					0x0068//延时等待time_delay2---第二个贮箱
#define 	STEP_13_O_2TANK_TANK2_1GAS_IS_GAS_PRESSURE				0x0069//判断气瓶压力是否升高---第二个贮箱
#define 	STEP_13_O_2TANK_TANK2_1GAS_IS_COMP_OVER					0x006a//判断气瓶抽气是否结束---第二个贮箱
#define 	STEP_13_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF				0x006b//关氧路气瓶补加阀门---第二个贮箱

#define		STEP_13_O_2TANK_TANK2_1GAS_IS_ISOLATION_FIRST			0x006c//通过压力判断高压气路隔离是否正常，第一次
#define 	STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF		0x006d//关闭氧压气机出口阀门
#define		STEP_13_O_2TANK_TANK2_1GAS_IS_ISOLATION_SECOND			0x006e//通过压力判断高压气路隔离是否正常，第二次

#define		STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP				0x006f//氧压气机停机
#define		STEP_13_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_STOP			0x0070//判断氧压气机停机是否正常
#define		STEP_13_O_2TANK_TANK2_1GAS_BYPATH_VALVE_ON				0x0071//开氧压气机旁路自锁阀
#define 	STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY_BYPATH			0x0072//延时等待time_bypath
#define		STEP_13_O_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF				0x0073//关氧压气机旁路自锁阀
#define 	STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2	0x0074//关闭氧压气机出口阀门，第二次
#define 	STEP_13_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF		0x0075//关闭氧压气机进口阀门
#define 	STEP_13_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF			0x0076//关进贮箱低压气路补加阀门
#define 	STEP_13_O_2TANK_TANK2_1GAS_SET_STATE_GOOD				0x0077//设置氧抽气状态好
#define 	STEP_13_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE	0x0078//判断压气机温度是否正常
#define 	STEP_13_O_2TANK_TANK2_1GAS_IS_NEED_COOLER_STOP			0x0079//判断是否需要进行液冷模块停机

//#define 	STEP_13_O_2TANK_TANK2_1GAS_IS_NEED_EXCHANGE				0x0079//判断是否需要进行液冷模块切换程序

#define 	STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY3					0x007a//延时等待time_delay3
//#define 	STEP_13_O_2TANK_TANK2_1GAS_EXCHANGE_COOLER				0x007b//启动液冷模块切换程序
//#define		STEP_13_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER		0x007c//通过压力判断液冷模块切换是否正常
#define		STEP_13_O_2TANK_TANK2_1GAS_COOLER_STOP					0x007b//液冷模块停机

#define		STEP_13_O_2TANK_TANK2_1GAS_COOLER_SET					0x007c//液冷模块状态设置

#define		STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF			0x007e//申请压气机断电
#define		STEP_13_O_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF			0x007f//申请电机驱动器断电

//**************************************程序结束******************************************************************

//两个气瓶抽气
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON			0x0080//开进气瓶补加阀门---第一个气瓶
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2				0x0081//延时等待time_delay2---第一个气瓶
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE			0x0082//判断气瓶压力是否升高---第一个气瓶
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS1_IS_COMP_OVER			0x0083//判断气瓶抽气是否结束---第一个气瓶
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF		0x0084//关氧路气瓶补加阀门---第一个气瓶
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON			0x0085//开进气瓶补加阀门---第二个气瓶
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2				0x0086//延时等待time_delay2---第二个气瓶
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE			0x0087//判断气瓶压力是否升高---第二个气瓶
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS2_IS_COMP_OVER			0x0088//判断气瓶抽气是否结束---第二个气瓶
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF		0x0089//关氧路气瓶补加阀门---第二个气瓶

#define		STEP_13_O_2TANK_TANK2_2GAS_IS_ISOLATION_FIRST			0x008a//通过压力判断高压气路隔离是否正常，第一次
#define 	STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF		0x008b//关闭氧压气机出口阀门
#define		STEP_13_O_2TANK_TANK2_2GAS_IS_ISOLATION_SECOND			0x008c//通过压力判断高压气路隔离是否正常，第二次

#define		STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP				0x008d//氧压气机停机
#define		STEP_13_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_STOP			0x008e//判断氧压气机停机是否正常
#define		STEP_13_O_2TANK_TANK2_2GAS_BYPATH_VALVE_ON				0x008f//开氧压气机旁路自锁阀
#define 	STEP_13_O_2TANK_TANK2_2GAS_TIME_DELAY_BYPATH			0x0090//延时等待time_bypath
#define		STEP_13_O_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF				0x0091//关氧压气机旁路自锁阀
#define 	STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2	0x0092//关闭氧压气机出口阀门，第二次
#define 	STEP_13_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF		0x0093//关闭氧压气机进口阀门
#define 	STEP_13_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF			0x0094//关进贮箱低压气路补加阀门
#define 	STEP_13_O_2TANK_TANK2_2GAS_SET_STATE_GOOD				0x0095//设置氧抽气状态好
#define 	STEP_13_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE	0x0096//判断压气机温度是否正常
#define 	STEP_13_O_2TANK_TANK2_2GAS_IS_NEED_COOLER_STOP			0x0097//判断是否需要进行液冷模块停机

//#define 	STEP_13_O_2TANK_TANK2_2GAS_IS_NEED_EXCHANGE				0x0097//判断是否需要进行液冷模块切换程序

#define 	STEP_13_O_2TANK_TANK2_2GAS_TIME_DELAY3					0x0098//延时等待time_delay3
//#define 	STEP_13_O_2TANK_TANK2_2GAS_EXCHANGE_COOLER				0x0099//启动液冷模块切换程序
//#define		STEP_13_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER		0x009a//通过压力判断液冷模块切换是否正常
#define		STEP_13_O_2TANK_TANK2_2GAS_COOLER_STOP					0x0099//液冷模块停机

#define		STEP_13_O_2TANK_TANK2_2GAS_COOLER_SET					0x009a//液冷模块状态设置

#define		STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF			0x009c//申请压气机断电
#define		STEP_13_O_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF			0x009d//申请电机驱动器断电



//0x00a2

//**************************************程序结束******************************************************************

//命令command--------------------------------------------------------------------------------------------

//------------------------------command---初始设置阶段---------------------------------------------------

//启动液冷泵工作
#define		COMMAND_13_0001_O_INIT_COOLER_VALVE_ON_NO1			0x0001//液冷模块补加系统阀门开第一组
#define		COMMAND_13_0002_O_INIT_IS_COOLER_VALVE_ON_NO1		0x0002//判断液冷模块补加系统阀门开第一组
#define		COMMAND_13_0003_O_INIT_COOLER_VALVE_ON_NO2			0x0003//液冷模块补加系统阀门开第二组
#define		COMMAND_13_0004_O_INIT_IS_COOLER_VALVE_ON_NO2		0x0004//判断液冷模块补加系统阀门开第二组
#define		COMMAND_13_0005_O_INIT_COOLER_POWER_ON				0x0005//液冷模块供电通
#define		COMMAND_13_0006_O_INIT_TIME_1MIN_START				0x0006//延时1min计时开始
#define		COMMAND_13_0007_O_INIT_IS_TIME_1MIN					0x0007//延时1min是否到

//通过转速判断液冷工作是否正常
#define		COMMAND_13_0001_O_INIT_IS_COOLER_WORK				0x0008//通过转速判断液冷工作是否正常

//延时等待time_delay
#define		COMMAND_13_0001_O_INIT_TIME_DELAY_START				0x0009//延时等待time_delay计时开始
#define		COMMAND_13_0002_O_INIT_IS_TIME_DELAY				0x000a//判断延时等待time_delay

//判断压气机温度是否正常
#define		COMMAND_13_0001_O_INIT_IS_COMPRESSOR_TEMPERATURE	0x000b//判断压气机温度是否正常

//申请电机驱动器加电
#define		COMMAND_13_0001_O_INIT_TGTHT530_POWER_ON			0x000c//申请设备管理指令
#define		COMMAND_13_0002_O_INIT_TGTHT530_TIME_1MIN_START		0x000d//延时1min计时开始
#define		COMMAND_13_0003_O_INIT_TGTHT530_IS_TIME_1MIN		0x000e//判断计时1min是否到
#define		COMMAND_13_0004_O_INIT_TGTHT530_IS_POWER_ON			0x000f//通过互传数据判断加电是否正常

//申请压气机加电
#define		COMMAND_13_0001_O_INIT_COMPRESSOR_POWER_ON			0x0010//申请设备管理指令
#define		COMMAND_13_0002_O_INIT_COMPRESSOR_TIME_1MIN_START	0x0011//延时1min计时开始
#define		COMMAND_13_0003_O_INIT_COMPRESSOR_IS_TIME_1MIN		0x0012//判断计时1min是否到

//贮箱隔离
#define		COMMAND_13_0001_O_INIT_ISOLATION_VALVE_OFF_NO1		0x0013//隔离推进系统自锁阀关闭，第一组
#define		COMMAND_13_0002_O_INIT_TIME_1MIN_START_NO1			0x0014//延时1min计时开始，第一组
#define		COMMAND_13_0003_O_INIT_IS_TIME_1MIN_NO1				0x0015//延时1min是否到，第一组
#define		COMMAND_13_0004_O_INIT_IS_ISOLATION_VALVE_OFF_NO1	0x0016//判断隔离推进系统自锁阀关闭，第一组

#define		COMMAND_13_0005_O_INIT_ISOLATION_VALVE_OFF_NO2		0x0017//隔离推进系统自锁阀关闭，第二组
#define		COMMAND_13_0006_O_INIT_TIME_1MIN_START_NO2			0x0018//延时1min计时开始，第二组
#define		COMMAND_13_0007_O_INIT_IS_TIME_1MIN_NO2				0x0019//延时1min是否到，第二组
#define		COMMAND_13_0008_O_INIT_IS_ISOLATION_VALVE_OFF_NO2	0x001a//判断隔离推进系统自锁阀关闭，第二组

#define		COMMAND_13_0009_O_INIT_ISOLATION_VALVE_OFF_NO3		0x001b//隔离推进系统自锁阀关闭，第三组
#define		COMMAND_13_0010_O_INIT_TIME_1MIN_START_NO3			0x001c//延时1min计时开始，第三组
#define		COMMAND_13_0011_O_INIT_IS_TIME_1MIN_NO3				0x001d//延时1min是否到，第三组
#define		COMMAND_13_0012_O_INIT_IS_ISOLATION_VALVE_OFF_NO3	0x001e//判断隔离推进系统自锁阀关闭，第三组

#define		COMMAND_13_0013_O_INIT_ISOLATION_VALVE_OFF_NO4		0x001f//隔离推进系统自锁阀关闭，第四组
#define		COMMAND_13_0014_O_INIT_TIME_1MIN_START_NO4			0x0020//延时1min计时开始，第四组
#define		COMMAND_13_0015_O_INIT_IS_TIME_1MIN_NO4				0x0021//延时1min是否到，第四组
#define		COMMAND_13_0016_O_INIT_IS_ISOLATION_VALVE_OFF_NO4	0x0022//判断隔离推进系统自锁阀关闭，第四组

#define		COMMAND_13_0017_O_INIT_ISOLATION_VALVE_OFF_NO5		0x0023//隔离推进系统自锁阀关闭，第五组
#define		COMMAND_13_0018_O_INIT_TIME_1MIN_START_NO5			0x0024//延时1min计时开始，第五组
#define		COMMAND_13_0019_O_INIT_IS_TIME_1MIN_NO5				0x0025//延时1min是否到，第五组
#define		COMMAND_13_0020_O_INIT_IS_ISOLATION_VALVE_OFF_NO5	0x0026//判断隔离推进系统自锁阀关闭，第五组

#define		COMMAND_13_0021_O_INIT_ISOLATION_VALVE_OFF_NO6		0x0027//隔离推进系统自锁阀关闭，第六组
#define		COMMAND_13_0022_O_INIT_TIME_1MIN_START_NO6			0x0028//延时1min计时开始，第六组
#define		COMMAND_13_0023_O_INIT_IS_TIME_1MIN_NO6				0x0029//延时1min是否到，第六组
#define		COMMAND_13_0024_O_INIT_IS_ISOLATION_VALVE_OFF_NO6	0x002a//判断隔离推进系统自锁阀关闭，第六组

#define		COMMAND_13_0025_O_INIT_ISOLATION_VALVE_OFF_NO7		0x002b//隔离推进系统自锁阀关闭，第七组
#define		COMMAND_13_0026_O_INIT_TIME_1MIN_START_NO7			0x002c//延时1min计时开始，第七组
#define		COMMAND_13_0027_O_INIT_IS_TIME_1MIN_NO7				0x002d//延时1min是否到，第七组
#define		COMMAND_13_0028_O_INIT_IS_ISOLATION_VALVE_OFF_NO7	0x002e//判断隔离推进系统自锁阀关闭，第七组

#define		COMMAND_13_0029_O_INIT_ISOLATION_VALVE_OFF_NO8		0x002f//隔离推进系统自锁阀关闭，第八组
#define		COMMAND_13_0030_O_INIT_TIME_1MIN_START_NO8			0x0030//延时1min计时开始，第八组
#define		COMMAND_13_0031_O_INIT_IS_TIME_1MIN_NO8				0x0031//延时1min是否到，第八组
#define		COMMAND_13_0032_O_INIT_IS_ISOLATION_VALVE_OFF_NO8	0x0032//判断隔离推进系统自锁阀关闭，第八组

#define		COMMAND_13_0033_O_INIT_ISOLATION_VALVE_OFF_NO9		0x0033//隔离推进系统自锁阀关闭，第九组
#define		COMMAND_13_0034_O_INIT_TIME_1MIN_START_NO9			0x0034//延时1min计时开始，第九组
#define		COMMAND_13_0035_O_INIT_IS_TIME_1MIN_NO9				0x0035//延时1min是否到，第九组
#define		COMMAND_13_0036_O_INIT_IS_ISOLATION_VALVE_OFF_NO9	0x0036//判断隔离推进系统自锁阀关闭，第九组

//判断抽气贮箱个数
#define		COMMAND_13_0001_O_INIT_NUMBER_COMP_TANK				0x0037//判断抽气贮箱个数
			
//------------------------------command---一个贮箱抽气-----------------------------------------------

//开进贮箱低压气路补加阀门
#define		COMMAND_13_0001_O_1TANK_IN_TANK_VALVE_ON					0x0038//开进贮箱低压气路补加阀门
#define		COMMAND_13_0002_O_1TANK_IS_IN_TANK_VALVE_ON					0x0039//判断开进贮箱低压气路补加阀门

//通过压力判断开进贮箱低压气路补加阀门
#define		COMMAND_13_0001_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE		0x003a//通过压力判断开补加阀门

//开氧压气机进口阀门
#define		COMMAND_13_0001_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO1			0x003b//开氧压气机进口阀门，第一组
#define		COMMAND_13_0002_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO1		0x003c//判断开氧压气机进口阀门，第一组
#define		COMMAND_13_0003_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO2			0x003d//开氧压气机进口阀门，第二组
#define		COMMAND_13_0004_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO2		0x003e//判断开氧压气机进口阀门，第二组
#define		COMMAND_13_0005_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO3			0x003f//开氧压气机进口阀门，第三组
#define		COMMAND_13_0006_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO3		0x0040//判断开氧压气机进口阀门，第三组

//延时等待time_delay1
#define		COMMAND_13_0001_O_1TANK_TIME_DELAY1_START					0x0041//延时等待time_delay1计时开始
#define		COMMAND_13_0002_O_1TANK_IS_TIME_DELAY1						0x0042//判断延时等待time_delay1

//判断压气机进口压力是否正常
#define		COMMAND_13_0001_O_1TANK_IS_IN_COMPRESSOR_PRESSURE			0x0043//判断压气机进口压力是否正常

//氧压气机启动
#define		COMMAND_13_0001_O_1TANK_COMPRESSOR_START					0x0044//申请设备管理指令，压气机启动
#define		COMMAND_13_0002_O_1TANK_COMPRESSOR_TIME_1MIN_START			0x0045//延时1min计时开始
#define		COMMAND_13_0003_O_1TANK_COMPRESSOR_IS_TIME_1MIN				0x0046//判断1min定时
#define		COMMAND_13_0004_O_1TANK_IS_COMPRESSOR_START					0x0047//通过互传数据判断启动是否正常

//判断压气机出口压力是否正常
#define		COMMAND_13_0001_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE			0x0048//判断压气机出口压力是否正常

//开氧压气机出口阀门
#define		COMMAND_13_0001_O_1TANK_OUT_COMPRESSOR_VALVE_ON				0x0049//开氧压气机出口阀门
#define		COMMAND_13_0002_O_1TANK_IS_OUT_COMPRESSOR_VALVE_ON			0x004a//判断开氧压气机出口阀门

//判断抽气气瓶个数
#define		COMMAND_13_0001_O_1TANK_NUMBER_COMP_GAS						0x004b//判断抽气气瓶个数


//------------------------------command---一个贮箱抽气----一个气瓶抽气-----------------------------------

//开进气瓶补加阀门
#define		COMMAND_13_0001_O_1TANK_1GAS_IN_GAS_VALVE_ON				0x004c//开进气瓶补加阀门
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_ON				0x004d//判断开进气瓶补加阀门

//延时等待time_delay2
#define		COMMAND_13_0001_O_1TANK_1GAS_TIME_DELAY2_START				0x004e//延时等待time_delay2计时开始
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_DELAY2					0x004f//判断延时等待time_delay2

//判断气瓶压力是否升高
#define		COMMAND_13_0001_O_1TANK_1GAS_GAS_PRESSURE_NO1				0x0050//采集气瓶压力，第一次
#define		COMMAND_13_0002_O_1TANK_1GAS_TIME_30S_START_NO1				0x0051//计时30s计时开始，第一次
#define		COMMAND_13_0003_O_1TANK_1GAS_IS_TIME_30S_NO1				0x0052//判断定时30s，第一次
#define		COMMAND_13_0004_O_1TANK_1GAS_GAS_PRESSURE_NO2				0x0053//采集气瓶压力，第二次
#define		COMMAND_13_0005_O_1TANK_1GAS_TIME_30S_START_NO2				0x0054//计时30s计时开始，第二次
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_TIME_30S_NO2				0x0055//判断定时30s，第二次
#define		COMMAND_13_0007_O_1TANK_1GAS_GAS_PRESSURE_NO3				0x0056//采集气瓶压力，第三次
#define		COMMAND_13_0008_O_1TANK_1GAS_TIME_30S_START_NO3				0x0057//计时30s计时开始，第三次
#define		COMMAND_13_0009_O_1TANK_1GAS_IS_TIME_30S_NO3				0x0058//判断定时30s，第三次
#define		COMMAND_13_0010_O_1TANK_1GAS_GAS_PRESSURE_NO4				0x0059//采集气瓶压力，第四次
#define		COMMAND_13_0011_O_1TANK_1GAS_TIME_30S_START_NO4				0x005a//计时30s计时开始，第四次
#define		COMMAND_13_0012_O_1TANK_1GAS_IS_TIME_30S_NO4				0x005b//判断定时30s，第四次
#define		COMMAND_13_0013_O_1TANK_1GAS_GAS_PRESSURE_NO5				0x005c//采集气瓶压力，第五次
#define		COMMAND_13_0014_O_1TANK_1GAS_TIME_30S_START_NO5				0x005d//计时30s计时开始，第五次
#define		COMMAND_13_0015_O_1TANK_1GAS_IS_TIME_30S_NO5				0x005e//判断定时30s，第五次
#define		COMMAND_13_0016_O_1TANK_1GAS_GAS_PRESSURE_NO6				0x005f//采集气瓶压力，第六次
#define		COMMAND_13_0017_O_1TANK_1GAS_TIME_30S_START_NO6				0x0060//计时30s计时开始，第六次
#define		COMMAND_13_0018_O_1TANK_1GAS_IS_TIME_30S_NO6				0x0061//判断定时30s，第六次
#define		COMMAND_13_0019_O_1TANK_1GAS_GAS_PRESSURE_NO7				0x0062//采集气瓶压力，第七次
#define		COMMAND_13_0020_O_1TANK_1GAS_TIME_30S_START_NO7				0x0063//计时30s计时开始，第七次
#define		COMMAND_13_0021_O_1TANK_1GAS_IS_TIME_30S_NO7				0x0064//判断定时30s，第七次
#define		COMMAND_13_0022_O_1TANK_1GAS_GAS_PRESSURE_NO8				0x0065//采集气瓶压力，第八次
#define		COMMAND_13_0023_O_1TANK_1GAS_TIME_30S_START_NO8				0x0066//计时30s计时开始，第八次
#define		COMMAND_13_0024_O_1TANK_1GAS_IS_TIME_30S_NO8				0x0067//判断定时30s，第八次
#define		COMMAND_13_0025_O_1TANK_1GAS_GAS_PRESSURE_NO9				0x0068//采集气瓶压力，第九次
#define		COMMAND_13_0026_O_1TANK_1GAS_TIME_30S_START_NO9				0x0069//计时30s计时开始，第九次
#define		COMMAND_13_0027_O_1TANK_1GAS_IS_TIME_30S_NO9				0x006a//判断定时30s，第九次
#define		COMMAND_13_0028_O_1TANK_1GAS_GAS_PRESSURE_NO10				0x006b//采集气瓶压力，第十次
#define		COMMAND_13_0029_O_1TANK_1GAS_IS_GAS_PRESSURE				0x006c//压差判断气瓶压力是否升高

//判断气瓶抽气是否结束
#define		COMMAND_13_0001_O_1TANK_1GAS_IS_COMP_GAS_OVER				0x006d//判断气瓶抽气是否结束

//关氧路气瓶补加阀门
#define		COMMAND_13_0001_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO1			0x006e//关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO1		0x006f//判断关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0003_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO2			0x0070//关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO2		0x0071//判断关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0005_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO3			0x0072//关氧路气瓶补加阀门，第三组
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO3		0x0073//判断关氧路气瓶补加阀门，第三组

//通过压力判断高压气路隔离是否正常，第一次
#define		COMMAND_13_0001_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO1	0x0074//采集压气机出口压力，第一次
#define		COMMAND_13_0002_O_1TANK_1GAS_FIRST_TIME_12S_START_NO1		0x0075//计时12s计时开始，第一次
#define		COMMAND_13_0003_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO1			0x0076//判断定时12s，第一次
#define		COMMAND_13_0004_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO2	0x0077//采集压气机出口压力，第二次
#define		COMMAND_13_0005_O_1TANK_1GAS_FIRST_TIME_12S_START_NO2		0x0078//计时12s计时开始，第二次
#define		COMMAND_13_0006_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO2			0x0079//判断定时12s，第二次
#define		COMMAND_13_0007_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO3	0x007a//采集压气机出口压力，第三次
#define		COMMAND_13_0008_O_1TANK_1GAS_FIRST_TIME_12S_START_NO3		0x007b//计时12s计时开始，第三次
#define		COMMAND_13_0009_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO3			0x007c//判断定时12s，第三次
#define		COMMAND_13_0010_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO4	0x007d//采集压气机出口压力，第四次
#define		COMMAND_13_0011_O_1TANK_1GAS_FIRST_IS_ISOLATION				0x007e//通过压力判断高压气路隔离是否正常

//关闭氧压气机出口阀门
#define		COMMAND_13_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1			0x007f//关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x0080//判断关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2			0x0081//关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x0082//判断关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3			0x0083//关闭氧压气机出口阀门，第三组
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x0084//判断关闭氧压气机出口阀门，第三组

//通过压力判断高压气路隔离是否正常，第二次
#define		COMMAND_13_0001_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO1	0x0085//采集压气机出口压力，第一次
#define		COMMAND_13_0002_O_1TANK_1GAS_SECOND_TIME_12S_START_NO1		0x0086//计时12s计时开始，第一次
#define		COMMAND_13_0003_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO1			0x0087//判断定时12s，第一次
#define		COMMAND_13_0004_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO2	0x0088//采集压气机出口压力，第二次
#define		COMMAND_13_0005_O_1TANK_1GAS_SECOND_TIME_12S_START_NO2		0x0089//计时12s计时开始，第二次
#define		COMMAND_13_0006_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO2			0x008a//判断定时12s，第二次
#define		COMMAND_13_0007_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO3	0x008b//采集压气机出口压力，第三次
#define		COMMAND_13_0008_O_1TANK_1GAS_SECOND_TIME_12S_START_NO3		0x008c//计时12s计时开始，第三次
#define		COMMAND_13_0009_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO3			0x008d//判断定时12s，第三次
#define		COMMAND_13_0010_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO4	0x008e//采集压气机出口压力，第四次
#define		COMMAND_13_0011_O_1TANK_1GAS_SECOND_IS_ISOLATION			0x008f//通过压力判断高压气路隔离是否正常

//氧压气机停机
#define		COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_STOP				0x0090//申请设备管理指令，压气机停机
#define		COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START		0x0091//延时1min计时开始
#define		COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN		0x0092//判断1min定时

//判断氧压气机停机是否正常
#define		COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_V_NO1				0x0093//采集电机转速，第一次
#define		COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_V_NO2				0x0094//采集电机转速，第二次
#define		COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_V_NO3				0x0095//采集电机转速，第三次
#define		COMMAND_13_0004_O_1TANK_1GAS_COMPRESSOR_V_NO4				0x0096//采集电机转速，第四次
#define		COMMAND_13_0005_O_1TANK_1GAS_COMPRESSOR_V_NO5				0x0097//采集电机转速，第五次
#define		COMMAND_13_0006_O_1TANK_1GAS_COMPRESSOR_V_NO6				0x0098//采集电机转速，第六次
#define		COMMAND_13_0007_O_1TANK_1GAS_COMPRESSOR_V_NO7				0x0099//采集电机转速，第七次
#define		COMMAND_13_0008_O_1TANK_1GAS_COMPRESSOR_V_NO8				0x009a//采集电机转速，第八次
#define		COMMAND_13_0009_O_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO1	0x009b//采集压气机出口压力，第一次
#define		COMMAND_13_0010_O_1TANK_1GAS_TIME_12S_START					0x009c//计时12s计时开始
#define		COMMAND_13_0011_O_1TANK_1GAS_IS_TIME_12S					0x009d//判断定时12s
#define		COMMAND_13_0012_O_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO2	0x009e//采集压气机出口压力，第二次
#define		COMMAND_13_0013_O_1TANK_1GAS_IS_COMPRESSOR_STOP				0x009f//判断氧压气机停机是否正常

//开氧压气机旁路自锁阀
#define		COMMAND_13_0001_O_1TANK_1GAS_BYPATH_VALVE_ON				0x00a0//开氧压气机旁路自锁阀
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_ON				0x00a1//判断开氧压气机旁路自锁阀

//延时等待time_bypath
#define		COMMAND_13_0001_O_1TANK_1GAS_TIME_BYPATH_START				0x00a2//延时等待time_bypath计时开启
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_BYPATH					0x00a3//判断延时等待time_bypath

//关氧压气机旁路自锁阀
#define		COMMAND_13_0001_O_1TANK_1GAS_BYPATH_VALVE_OFF				0x00a4//关氧压气机旁路自锁阀
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_OFF			0x00a5//判断关氧压气机旁路自锁阀

//关闭氧压气机出口阀门
#define		COMMAND_13_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1			0x00a6//关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x00a7//判断关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2			0x00a8//关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x00a9//判断关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3			0x00aa//关闭氧压气机出口阀门，第三组
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x00ab//判断关闭氧压气机出口阀门，第三组

//关闭氧压气机进口阀门
#define		COMMAND_13_0001_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x00ac//关闭氧压气机进口阀门，第一组
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1		0x00ad//判断关闭氧压气机进口阀门，第一组
#define		COMMAND_13_0003_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x00ae//关闭氧压气机进口阀门，第二组
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2		0x00af//判断关闭氧压气机进口阀门，第二组
#define		COMMAND_13_0005_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x00b0//关闭氧压气机进口阀门，第三组
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3		0x00b1//判断关闭氧压气机进口阀门，第三组

//关进贮箱低压气路补加阀门
#define		COMMAND_13_0001_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO1				0x00b2//关进贮箱低压气路补加阀门，第一组
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO1			0x00b3//判断关进贮箱低压气路补加阀门，第一组
#define		COMMAND_13_0003_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO2				0x00b4//关进贮箱低压气路补加阀门，第二组
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO2			0x00b5//判断关进贮箱低压气路补加阀门，第二组
#define		COMMAND_13_0005_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO3				0x00b6//关进贮箱低压气路补加阀门，第三组
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO3			0x00b7//判断关进贮箱低压气路补加阀门，第三组

//设置氧抽气状态好
#define		COMMAND_13_0001_O_1TANK_1GAS_SET_STATE_GOOD						0x00b8//设置氧抽气状态好

//判断压气机温度是否正常
#define		COMMAND_13_0001_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE			0x00b9//判断压气机温度是否正常

//判断是否需要进行液冷模块停机
#define		COMMAND_13_0001_O_1TANK_1GAS_IS_NEED_COOLER_STOP				0x00ba//判断是否需要进行液冷模块停机

//延时等待time_delay3
#define		COMMAND_13_0001_O_1TANK_1GAS_TIME_DELAY3_START					0x00bb//延时等待time_delay3计时开始
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_DELAY3						0x00bc//判断延时等待time_delay3

/*
//启动液冷模块切换程序
#define		COMMAND_13_0001_O_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO1			0x00bd//液冷模块切换程序，阀门动作，第一组
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x00be//判断液冷模块切换程序，阀门动作，第一组
#define		COMMAND_13_0003_O_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO2			0x00bf//液冷模块切换程序，阀门动作，第二组
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x00c0//判断液冷模块切换程序，阀门动作，第二组
#define		COMMAND_13_0005_O_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO3			0x00c1//液冷模块切换程序，阀门动作，第三组
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x00c2//判断液冷模块切换程序，阀门动作，第三组
#define		COMMAND_13_0007_O_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO4			0x00c3//液冷模块切换程序，阀门动作，第四组
#define		COMMAND_13_0008_O_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x00c4//判断液冷模块切换程序，阀门动作，第四组

//通过压力判断液冷模块切换是否正常
#define		COMMAND_13_0001_O_1TANK_1GAS_IS_EXCHANGE_COOLER					0x00c5//通过压力判断液冷模块切换是否正常
*/


//液冷模块停机
#define		COMMAND_13_0001_O_1TANK_1GAS_COOLER_POWER_OFF					0x00c6//液冷模块停机

//液冷模块状态设置
#define		COMMAND_13_0001_O_1TANK_1GAS_COOLER_SET_NO1						0x0400
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_COOLER_SET_NO1					0x0401
#define		COMMAND_13_0003_O_1TANK_1GAS_COOLER_SET_NO2						0x0402
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_COOLER_SET_NO2					0x0403
#define		COMMAND_13_0005_O_1TANK_1GAS_COOLER_SET_NO3						0x0404
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_COOLER_SET_NO3					0x0405
#define		COMMAND_13_0007_O_1TANK_1GAS_COOLER_SET_NO4						0x0406
#define		COMMAND_13_0008_O_1TANK_1GAS_IS_COOLER_SET_NO4					0x0407
#define		COMMAND_13_0009_O_1TANK_1GAS_COOLER_SET_NO5						0x0408
#define		COMMAND_13_0010_O_1TANK_1GAS_IS_COOLER_SET_NO5					0x0409
#define		COMMAND_13_0011_O_1TANK_1GAS_COOLER_SET_NO6						0x040a
#define		COMMAND_13_0012_O_1TANK_1GAS_IS_COOLER_SET_NO6					0x040b
#define		COMMAND_13_0013_O_1TANK_1GAS_COOLER_SET_NO7						0x040c
#define		COMMAND_13_0014_O_1TANK_1GAS_IS_COOLER_SET_NO7					0x040d
#define		COMMAND_13_0015_O_1TANK_1GAS_COOLER_SET_NO8						0x040e
#define		COMMAND_13_0016_O_1TANK_1GAS_IS_COOLER_SET_NO8					0x040f
#define		COMMAND_13_0017_O_1TANK_1GAS_COOLER_SET_NO9						0x0411
#define		COMMAND_13_0018_O_1TANK_1GAS_IS_COOLER_SET_NO9					0x0412
#define		COMMAND_13_0019_O_1TANK_1GAS_COOLER_SET_NO10					0x0413
#define		COMMAND_13_0020_O_1TANK_1GAS_IS_COOLER_SET_NO10					0x0414
#define		COMMAND_13_0021_O_1TANK_1GAS_COOLER_SET_NO11					0x0415
#define		COMMAND_13_0022_O_1TANK_1GAS_IS_COOLER_SET_NO11					0x0416
#define		COMMAND_13_0023_O_1TANK_1GAS_COOLER_SET_NO12					0x0417
#define		COMMAND_13_0024_O_1TANK_1GAS_IS_COOLER_SET_NO12					0x0418



//申请压气机断电
#define		COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_POWER_OFF				0x00c7//申请设备管理指令
//#define		COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START			0x00c8//延时1min计时开始
//#define		COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN			0x00c9//判断计时1min是否到

//申请电机驱动器断电
#define		COMMAND_13_0001_O_1TANK_1GAS_TGTHT530_POWER_OFF					0x00ca//申请设备管理指令
#define		COMMAND_13_0002_O_1TANK_1GAS_TGTHT530_TIME_1MIN_START			0x00cb//延时1min计时开始
#define		COMMAND_13_0003_O_1TANK_1GAS_TGTHT530_IS_TIME_1MIN				0x00cc//判断计时1min是否到



//------------------------------command---一个贮箱抽气----两个气瓶抽气-----------------------------------

//开进气瓶补加阀门---第一个气瓶
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON				0x00cd//开进气瓶补加阀门
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_ON			0x00ce//判断开进气瓶补加阀门


//延时等待time_delay2---第一个气瓶
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS1_TIME_DELAY2_START				0x00cf//延时等待time_delay2计时开始
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_TIME_DELAY2				0x00d0//判断延时等待time_delay2


//判断气瓶压力是否升高---第一个气瓶
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO1				0x00d1//采集气瓶压力，第一次
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS1_TIME_30S_START_NO1			0x00d2//计时30s计时开始，第一次
#define		COMMAND_13_0003_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO1				0x00d3//判断定时30s，第一次
#define		COMMAND_13_0004_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO2				0x00d4//采集气瓶压力，第二次
#define		COMMAND_13_0005_O_1TANK_2GAS_GAS1_TIME_30S_START_NO2			0x00d5//计时30s计时开始，第二次
#define		COMMAND_13_0006_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO2				0x00d6//判断定时30s，第二次
#define		COMMAND_13_0007_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO3				0x00d7//采集气瓶压力，第三次
#define		COMMAND_13_0008_O_1TANK_2GAS_GAS1_TIME_30S_START_NO3			0x00d8//计时30s计时开始，第三次
#define		COMMAND_13_0009_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO3				0x00d9//判断定时30s，第三次
#define		COMMAND_13_0010_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO4				0x00da//采集气瓶压力，第四次
#define		COMMAND_13_0011_O_1TANK_2GAS_GAS1_TIME_30S_START_NO4			0x00db//计时30s计时开始，第四次
#define		COMMAND_13_0012_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO4				0x00dc//判断定时30s，第四次
#define		COMMAND_13_0013_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO5				0x00dd//采集气瓶压力，第五次
#define		COMMAND_13_0014_O_1TANK_2GAS_GAS1_TIME_30S_START_NO5			0x00de//计时30s计时开始，第五次
#define		COMMAND_13_0015_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO5				0x00df//判断定时30s，第五次
#define		COMMAND_13_0016_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO6				0x00e0//采集气瓶压力，第六次
#define		COMMAND_13_0017_O_1TANK_2GAS_GAS1_TIME_30S_START_NO6			0x00e1//计时30s计时开始，第六次
#define		COMMAND_13_0018_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO6				0x00e2//判断定时30s，第六次
#define		COMMAND_13_0019_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO7				0x00e3//采集气瓶压力，第七次
#define		COMMAND_13_0020_O_1TANK_2GAS_GAS1_TIME_30S_START_NO7			0x00e4//计时30s计时开始，第七次
#define		COMMAND_13_0021_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO7				0x00e5//判断定时30s，第七次
#define		COMMAND_13_0022_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO8				0x00e6//采集气瓶压力，第八次
#define		COMMAND_13_0023_O_1TANK_2GAS_GAS1_TIME_30S_START_NO8			0x00e7//计时30s计时开始，第八次
#define		COMMAND_13_0024_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO8				0x00e8//判断定时30s，第八次
#define		COMMAND_13_0025_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO9				0x00e9//采集气瓶压力，第九次
#define		COMMAND_13_0026_O_1TANK_2GAS_GAS1_TIME_30S_START_NO9			0x00ea//计时30s计时开始，第九次
#define		COMMAND_13_0027_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO9				0x00eb//判断定时30s，第九次
#define		COMMAND_13_0028_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO10				0x00ec//采集气瓶压力，第十次
#define		COMMAND_13_0029_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE				0x00ed//压差判断气瓶压力是否升高


//判断气瓶抽气是否结束---第一个气瓶
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS1_IS_COMP_GAS_OVER				0x00ee//判断气瓶抽气是否结束


//关氧路气瓶补加阀门---第一个气瓶
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1			0x00ef//关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1		0x00f0//判断关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0003_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2			0x00f1//关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0004_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2		0x00f2//判断关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0005_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3			0x00f3//关氧路气瓶补加阀门，第三组
#define		COMMAND_13_0006_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3		0x00f4//判断关氧路气瓶补加阀门，第三组



//开进气瓶补加阀门---第二个气瓶
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON				0x00f5//开进气瓶补加阀门
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_ON			0x00f6//判断开进气瓶补加阀门


//延时等待time_delay2---第二个气瓶
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS2_TIME_DELAY2_START				0x00f7//延时等待time_delay2计时开始
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_TIME_DELAY2				0x00f8//判断延时等待time_delay2



//判断气瓶压力是否升高---第二个气瓶
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO1				0x00f9//采集气瓶压力，第一次
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS2_TIME_30S_START_NO1			0x00fa//计时30s计时开始，第一次
#define		COMMAND_13_0003_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO1				0x00fb//判断定时30s，第一次
#define		COMMAND_13_0004_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO2				0x00fc//采集气瓶压力，第二次
#define		COMMAND_13_0005_O_1TANK_2GAS_GAS2_TIME_30S_START_NO2			0x00fd//计时30s计时开始，第二次
#define		COMMAND_13_0006_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO2				0x00fe//判断定时30s，第二次
#define		COMMAND_13_0007_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO3				0x00ff//采集气瓶压力，第三次
#define		COMMAND_13_0008_O_1TANK_2GAS_GAS2_TIME_30S_START_NO3			0x0100//计时30s计时开始，第三次
#define		COMMAND_13_0009_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO3				0x0101//判断定时30s，第三次
#define		COMMAND_13_0010_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO4				0x0102//采集气瓶压力，第四次
#define		COMMAND_13_0011_O_1TANK_2GAS_GAS2_TIME_30S_START_NO4			0x0103//计时30s计时开始，第四次
#define		COMMAND_13_0012_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO4				0x0104//判断定时30s，第四次
#define		COMMAND_13_0013_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO5				0x0105//采集气瓶压力，第五次
#define		COMMAND_13_0014_O_1TANK_2GAS_GAS2_TIME_30S_START_NO5			0x0106//计时30s计时开始，第五次
#define		COMMAND_13_0015_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO5				0x0107//判断定时30s，第五次
#define		COMMAND_13_0016_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO6				0x0108//采集气瓶压力，第六次
#define		COMMAND_13_0017_O_1TANK_2GAS_GAS2_TIME_30S_START_NO6			0x0109//计时30s计时开始，第六次
#define		COMMAND_13_0018_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO6				0x010a//判断定时30s，第六次
#define		COMMAND_13_0019_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO7				0x010b//采集气瓶压力，第七次
#define		COMMAND_13_0020_O_1TANK_2GAS_GAS2_TIME_30S_START_NO7			0x010c//计时30s计时开始，第七次
#define		COMMAND_13_0021_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO7				0x010d//判断定时30s，第七次
#define		COMMAND_13_0022_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO8				0x010e//采集气瓶压力，第八次
#define		COMMAND_13_0023_O_1TANK_2GAS_GAS2_TIME_30S_START_NO8			0x010f//计时30s计时开始，第八次
#define		COMMAND_13_0024_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO8				0x0110//判断定时30s，第八次
#define		COMMAND_13_0025_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO9				0x0111//采集气瓶压力，第九次
#define		COMMAND_13_0026_O_1TANK_2GAS_GAS2_TIME_30S_START_NO9			0x0112//计时30s计时开始，第九次
#define		COMMAND_13_0027_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO9				0x0113//判断定时30s，第九次
#define		COMMAND_13_0028_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO10				0x0114//采集气瓶压力，第十次
#define		COMMAND_13_0029_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE				0x0115//压差判断气瓶压力是否升高

//判断气瓶抽气是否结束---第二个气瓶
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS2_IS_COMP_GAS_OVER				0x0116//判断气瓶抽气是否结束


//关氧路气瓶补加阀门---第二个气瓶
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1			0x0117//关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1		0x0118//判断关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0003_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2			0x0119//关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0004_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2		0x011a//判断关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0005_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3			0x011b//关氧路气瓶补加阀门，第三组
#define		COMMAND_13_0006_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3		0x011c//判断关氧路气瓶补加阀门，第三组

//通过压力判断高压气路隔离是否正常，第一次
#define		COMMAND_13_0001_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO1	0x011d//采集压气机出口压力，第一次
#define		COMMAND_13_0002_O_1TANK_2GAS_FIRST_TIME_12S_START_NO1		0x011e//计时12s计时开始，第一次
#define		COMMAND_13_0003_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO1			0x011f//判断定时12s，第一次
#define		COMMAND_13_0004_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO2	0x0120//采集压气机出口压力，第二次
#define		COMMAND_13_0005_O_1TANK_2GAS_FIRST_TIME_12S_START_NO2		0x0121//计时12s计时开始，第二次
#define		COMMAND_13_0006_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO2			0x0122//判断定时12s，第二次
#define		COMMAND_13_0007_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO3	0x0123//采集压气机出口压力，第三次
#define		COMMAND_13_0008_O_1TANK_2GAS_FIRST_TIME_12S_START_NO3		0x0124//计时12s计时开始，第三次
#define		COMMAND_13_0009_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO3			0x0125//判断定时12s，第三次
#define		COMMAND_13_0010_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO4	0x0126//采集压气机出口压力，第四次
#define		COMMAND_13_0011_O_1TANK_2GAS_FIRST_IS_ISOLATION				0x0127//通过压力判断高压气路隔离是否正常

//关闭氧压气机出口阀门
#define		COMMAND_13_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x0128//关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1	0x0129//判断关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x012a//关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2	0x012b//判断关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x012c//关闭氧压气机出口阀门，第三组
#define		COMMAND_13_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3	0x012d//判断关闭氧压气机出口阀门，第三组

//通过压力判断高压气路隔离是否正常，第二次
#define		COMMAND_13_0001_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO1	0x012e//采集压气机出口压力，第一次
#define		COMMAND_13_0002_O_1TANK_2GAS_SECOND_TIME_12S_START_NO1		0x012f//计时12s计时开始，第一次
#define		COMMAND_13_0003_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO1			0x0130//判断定时12s，第一次
#define		COMMAND_13_0004_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO2	0x0131//采集压气机出口压力，第二次
#define		COMMAND_13_0005_O_1TANK_2GAS_SECOND_TIME_12S_START_NO2		0x0132//计时12s计时开始，第二次
#define		COMMAND_13_0006_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO2			0x0133//判断定时12s，第二次
#define		COMMAND_13_0007_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO3	0x0134//采集压气机出口压力，第三次
#define		COMMAND_13_0008_O_1TANK_2GAS_SECOND_TIME_12S_START_NO3		0x0135//计时12s计时开始，第三次
#define		COMMAND_13_0009_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO3			0x0136//判断定时12s，第三次
#define		COMMAND_13_0010_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO4	0x0137//采集压气机出口压力，第四次
#define		COMMAND_13_0011_O_1TANK_2GAS_SECOND_IS_ISOLATION			0x0138//通过压力判断高压气路隔离是否正常

//氧压气机停机
#define		COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_STOP					0x0139//申请设备管理指令，压气机停机
#define		COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START			0x013a//延时1min计时开始
#define		COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN			0x013b//判断1min定时


//判断氧压气机停机是否正常
#define		COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_V_NO1					0x013c//采集电机转速，第一次
#define		COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_V_NO2					0x013d//采集电机转速，第二次
#define		COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_V_NO3					0x013e//采集电机转速，第三次
#define		COMMAND_13_0004_O_1TANK_2GAS_COMPRESSOR_V_NO4					0x013f//采集电机转速，第四次
#define		COMMAND_13_0005_O_1TANK_2GAS_COMPRESSOR_V_NO5					0x0140//采集电机转速，第五次
#define		COMMAND_13_0006_O_1TANK_2GAS_COMPRESSOR_V_NO6					0x0141//采集电机转速，第六次
#define		COMMAND_13_0007_O_1TANK_2GAS_COMPRESSOR_V_NO7					0x0142//采集电机转速，第七次
#define		COMMAND_13_0008_O_1TANK_2GAS_COMPRESSOR_V_NO8					0x0143//采集电机转速，第八次
#define		COMMAND_13_0009_O_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO1		0x0144//采集压气机出口压力，第一次
#define		COMMAND_13_0010_O_1TANK_2GAS_TIME_12S_START						0x0145//计时12s计时开始
#define		COMMAND_13_0011_O_1TANK_2GAS_IS_TIME_12S						0x0146//判断定时12s
#define		COMMAND_13_0012_O_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO2		0x0147//采集压气机出口压力，第二次
#define		COMMAND_13_0013_O_1TANK_2GAS_IS_COMPRESSOR_STOP					0x0148//判断氧压气机停机是否正常


//开氧压气机旁路自锁阀
#define		COMMAND_13_0001_O_1TANK_2GAS_BYPATH_VALVE_ON					0x0149//开氧压气机旁路自锁阀
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_ON					0x014a//判断开氧压气机旁路自锁阀


//延时等待time_bypath
#define		COMMAND_13_0001_O_1TANK_2GAS_TIME_BYPATH_START					0x014b//延时等待time_bypath计时开启
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_TIME_BYPATH						0x014c//判断延时等待time_bypath


//关氧压气机旁路自锁阀
#define		COMMAND_13_0001_O_1TANK_2GAS_BYPATH_VALVE_OFF					0x014d//关氧压气机旁路自锁阀
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_OFF				0x014e//判断关氧压气机旁路自锁阀

//关闭氧压气机出口阀门
#define		COMMAND_13_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1			0x014f//关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x0150//判断关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2			0x0151//关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x0152//判断关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3			0x0153//关闭氧压气机出口阀门，第三组
#define		COMMAND_13_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x0154//判断关闭氧压气机出口阀门，第三组

//关闭氧压气机进口阀门
#define		COMMAND_13_0001_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x0155//关闭氧压气机进口阀门，第一组
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1		0x0156//判断关闭氧压气机进口阀门，第一组
#define		COMMAND_13_0003_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0157//关闭氧压气机进口阀门，第二组
#define		COMMAND_13_0004_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0158//判断关闭氧压气机进口阀门，第二组
#define		COMMAND_13_0005_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x0159//关闭氧压气机进口阀门，第三组
#define		COMMAND_13_0006_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3		0x015a//判断关闭氧压气机进口阀门，第三组


//关进贮箱低压气路补加阀门
#define		COMMAND_13_0001_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO1				0x015b//关进贮箱低压气路补加阀门，第一组
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO1			0x015c//判断关进贮箱低压气路补加阀门，第一组
#define		COMMAND_13_0003_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO2				0x015d//关进贮箱低压气路补加阀门，第二组
#define		COMMAND_13_0004_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO2			0x015e//判断关进贮箱低压气路补加阀门，第二组
#define		COMMAND_13_0005_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO3				0x015f//关进贮箱低压气路补加阀门，第三组
#define		COMMAND_13_0006_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO3			0x0160//判断关进贮箱低压气路补加阀门，第三组


//设置氧抽气状态好
#define		COMMAND_13_0001_O_1TANK_2GAS_SET_STATE_GOOD						0x0161//设置氧抽气状态好


//判断压气机温度是否正常
#define		COMMAND_13_0001_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE			0x0162//判断压气机温度是否正常

//判断是否需要进行液冷模块停机
#define		COMMAND_13_0001_O_1TANK_2GAS_IS_NEED_COOLER_STOP				0x0163//判断是否需要进行液冷模块停机

//延时等待time_delay3
#define		COMMAND_13_0001_O_1TANK_2GAS_TIME_DELAY3_START					0x0164//延时等待time_delay3计时开始
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_TIME_DELAY3						0x0165//判断延时等待time_delay3


/*
//启动液冷模块切换程序
#define		COMMAND_13_0001_O_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO1			0x0166//液冷模块切换程序,阀门动作，第一组
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x0167//判断液冷模块切换程序,阀门动作，第一组
#define		COMMAND_13_0003_O_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO2			0x0168//液冷模块切换程序,阀门动作，第二组
#define		COMMAND_13_0004_O_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x0169//判断液冷模块切换程序,阀门动作，第二组
#define		COMMAND_13_0005_O_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO3			0x016a//液冷模块切换程序,阀门动作，第三组
#define		COMMAND_13_0006_O_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x016b//判断液冷模块切换程序,阀门动作，第三组
#define		COMMAND_13_0007_O_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO4			0x016c//液冷模块切换程序,阀门动作，第四组
#define		COMMAND_13_0008_O_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x016d//判断液冷模块切换程序,阀门动作，第四组

//通过压力判断液冷模块切换是否正常
#define		COMMAND_13_0001_O_1TANK_2GAS_IS_EXCHANGE_COOLER					0x016e//通过压力判断液冷模块切换是否正常
*/


//液冷模块停机
#define		COMMAND_13_0001_O_1TANK_2GAS_COOLER_POWER_OFF					0x016f//液冷模块停机

//液冷模块状态设置
#define		COMMAND_13_0001_O_1TANK_2GAS_COOLER_SET_NO1						0x0419
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_COOLER_SET_NO1					0x041a
#define		COMMAND_13_0003_O_1TANK_2GAS_COOLER_SET_NO2						0x041b
#define		COMMAND_13_0004_O_1TANK_2GAS_IS_COOLER_SET_NO2					0x041c
#define		COMMAND_13_0005_O_1TANK_2GAS_COOLER_SET_NO3						0x041d
#define		COMMAND_13_0006_O_1TANK_2GAS_IS_COOLER_SET_NO3					0x041e
#define		COMMAND_13_0007_O_1TANK_2GAS_COOLER_SET_NO4						0x041f
#define		COMMAND_13_0008_O_1TANK_2GAS_IS_COOLER_SET_NO4					0x0420
#define		COMMAND_13_0009_O_1TANK_2GAS_COOLER_SET_NO5						0x0421
#define		COMMAND_13_0010_O_1TANK_2GAS_IS_COOLER_SET_NO5					0x0422
#define		COMMAND_13_0011_O_1TANK_2GAS_COOLER_SET_NO6						0x0423
#define		COMMAND_13_0012_O_1TANK_2GAS_IS_COOLER_SET_NO6					0x0424
#define		COMMAND_13_0013_O_1TANK_2GAS_COOLER_SET_NO7						0x0425
#define		COMMAND_13_0014_O_1TANK_2GAS_IS_COOLER_SET_NO7					0x0426
#define		COMMAND_13_0015_O_1TANK_2GAS_COOLER_SET_NO8						0x0427
#define		COMMAND_13_0016_O_1TANK_2GAS_IS_COOLER_SET_NO8					0x0428
#define		COMMAND_13_0017_O_1TANK_2GAS_COOLER_SET_NO9						0x0429
#define		COMMAND_13_0018_O_1TANK_2GAS_IS_COOLER_SET_NO9					0x042a
#define		COMMAND_13_0019_O_1TANK_2GAS_COOLER_SET_NO10					0x042b
#define		COMMAND_13_0020_O_1TANK_2GAS_IS_COOLER_SET_NO10					0x042c
#define		COMMAND_13_0021_O_1TANK_2GAS_COOLER_SET_NO11					0x042d
#define		COMMAND_13_0022_O_1TANK_2GAS_IS_COOLER_SET_NO11					0x042e
#define		COMMAND_13_0023_O_1TANK_2GAS_COOLER_SET_NO12					0x042f
#define		COMMAND_13_0024_O_1TANK_2GAS_IS_COOLER_SET_NO12					0x0430




//申请压气机断电
#define		COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_POWER_OFF				0x0170//申请设备管理指令
//#define		COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START			0x0171//延时1min计时开始
//#define		COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN			0x0172//判断计时1min是否到

//申请电机驱动器断电
#define		COMMAND_13_0001_O_1TANK_2GAS_TGTHT530_POWER_OFF					0x0173//申请设备管理指令
#define		COMMAND_13_0002_O_1TANK_2GAS_TGTHT530_TIME_1MIN_START			0x0174//延时1min计时开始
#define		COMMAND_13_0003_O_1TANK_2GAS_TGTHT530_IS_TIME_1MIN				0x0175//判断计时1min是否到


//------------------------------command---两个贮箱抽气----第一个贮箱抽气-----------------------------------

//开进贮箱低压气路补加阀门---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_IN_TANK_VALVE_ON					0x0176//开进贮箱低压气路补加阀门
#define		COMMAND_13_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON				0x0177//判断开进贮箱低压气路补加阀门


//通过压力判断开进贮箱阀门---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE		0x0178//通过压力判断开补加阀门


//开氧压气机进口阀门---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO1		0x0179//开氧压气机进口阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO1		0x017a//判断开氧压气机进口阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO2		0x017b//开氧压气机进口阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO2		0x017c//判断开氧压气机进口阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO3		0x017d//开氧压气机进口阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO3		0x017e//判断开氧压气机进口阀门，第三组


//延时等待time_delay1---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_TIME_DELAY1_START					0x017f//延时等待time_delay1计时开始
#define		COMMAND_13_0002_O_2TANK_TANK1_IS_TIME_DELAY1					0x0180//判断延时等待time_delay1


//判断压气机进口压力是否正常---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE			0x0181//判断压气机进口压力是否正常


//氧压气机启动---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_COMPRESSOR_START					0x0182//申请设备管理指令，压气机启动
#define		COMMAND_13_0002_O_2TANK_TANK1_COMPRESSOR_TIME_1MIN_START		0x0183//延时1min计时开始
#define		COMMAND_13_0003_O_2TANK_TANK1_COMPRESSOR_IS_TIME_1MIN			0x0184//判断1min定时
#define		COMMAND_13_0004_O_2TANK_TANK1_IS_COMPRESSOR_START				0x0185//通过互传数据判断启动是否正常


//判断压气机出口压力是否正常---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE		0x0186//判断压气机出口压力是否正常


//开氧压气机出口阀门---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON			0x0187//开氧压气机出口阀门
#define		COMMAND_13_0002_O_2TANK_TANK1_IS_OUT_COMPRESSOR_VALVE_ON		0x0188//判断开氧压气机出口阀门


//判断抽气气瓶个数---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_NUMBER_COMP_GAS					0x0189//判断抽气气瓶个数


//------------------------------command---两个贮箱抽气----第一个贮箱抽气----一个气瓶抽气--------------------

//开进气瓶补加阀门---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON				0x018a//开进气瓶补加阀门
#define		COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_ON			0x018b//判断开进气瓶补加阀门


//延时等待time_delay2---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_TIME_DELAY2_START			0x018c//延时等待time_delay2计时开始
#define		COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_TIME_DELAY2				0x018d//判断延时等待time_delay2


//判断气瓶压力是否升高---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO1				0x018e//采集气瓶压力，第一次
#define		COMMAND_13_0002_O_2TANK_TANK1_1GAS_TIME_30S_START_NO1			0x018f//计时30s计时开始，第一次
#define		COMMAND_13_0003_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO1				0x0190//判断定时30s，第一次
#define		COMMAND_13_0004_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO2				0x0191//采集气瓶压力，第二次
#define		COMMAND_13_0005_O_2TANK_TANK1_1GAS_TIME_30S_START_NO2			0x0192//计时30s计时开始，第二次
#define		COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO2				0x0193//判断定时30s，第二次
#define		COMMAND_13_0007_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO3				0x0194//采集气瓶压力，第三次
#define		COMMAND_13_0008_O_2TANK_TANK1_1GAS_TIME_30S_START_NO3			0x0195//计时30s计时开始，第三次
#define		COMMAND_13_0009_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO3				0x0196//判断定时30s，第三次
#define		COMMAND_13_0010_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO4				0x0197//采集气瓶压力，第四次
#define		COMMAND_13_0011_O_2TANK_TANK1_1GAS_TIME_30S_START_NO4			0x0198//计时30s计时开始，第四次
#define		COMMAND_13_0012_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO4				0x0199//判断定时30s，第四次
#define		COMMAND_13_0013_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO5				0x019a//采集气瓶压力，第五次
#define		COMMAND_13_0014_O_2TANK_TANK1_1GAS_TIME_30S_START_NO5			0x019b//计时30s计时开始，第五次
#define		COMMAND_13_0015_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO5				0x019c//判断定时30s，第五次
#define		COMMAND_13_0016_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO6				0x019d//采集气瓶压力，第六次
#define		COMMAND_13_0017_O_2TANK_TANK1_1GAS_TIME_30S_START_NO6			0x019e//计时30s计时开始，第六次
#define		COMMAND_13_0018_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO6				0x019f//判断定时30s，第六次
#define		COMMAND_13_0019_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO7				0x01a0//采集气瓶压力，第七次
#define		COMMAND_13_0020_O_2TANK_TANK1_1GAS_TIME_30S_START_NO7			0x01a1//计时30s计时开始，第七次
#define		COMMAND_13_0021_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO7				0x01a2//判断定时30s，第七次
#define		COMMAND_13_0022_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO8				0x01a3//采集气瓶压力，第八次
#define		COMMAND_13_0023_O_2TANK_TANK1_1GAS_TIME_30S_START_NO8			0x01a4//计时30s计时开始，第八次
#define		COMMAND_13_0024_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO8				0x01a5//判断定时30s，第八次
#define		COMMAND_13_0025_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO9				0x01a6//采集气瓶压力，第九次
#define		COMMAND_13_0026_O_2TANK_TANK1_1GAS_TIME_30S_START_NO9			0x01a7//计时30s计时开始，第九次
#define		COMMAND_13_0027_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO9				0x01a8//判断定时30s，第九次
#define		COMMAND_13_0028_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO10			0x01a9//采集气瓶压力，第十次
#define		COMMAND_13_0029_O_2TANK_TANK1_1GAS_IS_GAS_PRESSURE				0x01aa//压差判断气瓶压力是否升高

//判断气瓶抽气是否结束---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_IS_COMP_GAS_OVER				0x01ab//判断气瓶抽气是否结束


//关氧路气瓶补加阀门---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO1			0x01ac//关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO1		0x01ad//判断关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO2			0x01ae//关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO2		0x01af//判断关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO3			0x01b0//关氧路气瓶补加阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO3		0x01b1//判断关氧路气瓶补加阀门，第三组


//关进贮箱低压气路补加阀门---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO1			0x01b2//关进贮箱低压气路补加阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO1			0x01b3//判断关进贮箱低压气路补加阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO2			0x01b4//关进贮箱低压气路补加阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO2			0x01b5//判断关进贮箱低压气路补加阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO3			0x01b6//关进贮箱低压气路补加阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO3			0x01b7//判断关进贮箱低压气路补加阀门，第三组

//通过压力判断关进贮箱补加阀---第一个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO1	0x01b8//通过压力判断关进贮箱补加阀，第一组
#define		COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO2	0x01b9//通过压力判断关进贮箱补加阀，第二组
#define		COMMAND_13_0003_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO3	0x01ba//通过压力判断关进贮箱补加阀，第三组
#define		COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO4	0x01bb//通过压力判断关进贮箱补加阀，第四组
#define		COMMAND_13_0005_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO5	0x01bc//通过压力判断关进贮箱补加阀，第五组
#define		COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE		0x01bd//通过压力判断关进贮箱补加阀，五取三


//------------------------------command---两个贮箱抽气----第一个贮箱抽气----两个气瓶抽气--------------------

//开进气瓶补加阀门---第一个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON				0x01be//开进气瓶补加阀门
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_ON			0x01bf//判断开进气瓶补加阀门


//延时等待time_delay2---第一个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2_START			0x01c0//延时等待time_delay2计时开始
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_DELAY2				0x01c1//判断延时等待time_delay2

//判断气瓶压力是否升高---第一个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO1			0x01c2//采集气瓶压力，第一次
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO1			0x01c3//计时30s计时开始，第一次
#define		COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO1				0x01c4//判断定时30s，第一次
#define		COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO2			0x01c5//采集气瓶压力，第二次
#define		COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO2			0x01c6//计时30s计时开始，第二次
#define		COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO2				0x01c7//判断定时30s，第二次
#define		COMMAND_13_0007_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO3			0x01c8//采集气瓶压力，第三次
#define		COMMAND_13_0008_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO3			0x01c9//计时30s计时开始，第三次
#define		COMMAND_13_0009_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO3				0x01ca//判断定时30s，第三次
#define		COMMAND_13_0010_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO4			0x01cb//采集气瓶压力，第四次
#define		COMMAND_13_0011_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO4			0x01cc//计时30s计时开始，第四次
#define		COMMAND_13_0012_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO4				0x01cd//判断定时30s，第四次
#define		COMMAND_13_0013_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO5			0x01ce//采集气瓶压力，第五次
#define		COMMAND_13_0014_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO5			0x01cf//计时30s计时开始，第五次
#define		COMMAND_13_0015_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO5				0x01d0//判断定时30s，第五次
#define		COMMAND_13_0016_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO6			0x01d1//采集气瓶压力，第六次
#define		COMMAND_13_0017_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO6			0x01d2//计时30s计时开始，第六次
#define		COMMAND_13_0018_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO6				0x01d3//判断定时30s，第六次
#define		COMMAND_13_0019_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO7			0x01d4//采集气瓶压力，第七次
#define		COMMAND_13_0020_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO7			0x01d5//计时30s计时开始，第七次
#define		COMMAND_13_0021_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO7				0x01d6//判断定时30s，第七次
#define		COMMAND_13_0022_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO8			0x01d7//采集气瓶压力，第八次
#define		COMMAND_13_0023_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO8			0x01d8//计时30s计时开始，第八次
#define		COMMAND_13_0024_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO8				0x01d9//判断定时30s，第八次
#define		COMMAND_13_0025_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO9			0x01da//采集气瓶压力，第九次
#define		COMMAND_13_0026_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO9			0x01db//计时30s计时开始，第九次
#define		COMMAND_13_0027_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO9				0x01dc//判断定时30s，第九次
#define		COMMAND_13_0028_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO10			0x01dd//采集气瓶压力，第十次
#define		COMMAND_13_0029_O_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE				0x01de//压差判断气瓶压力是否升高

//判断气瓶抽气是否结束---第一个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IS_COMP_GAS_OVER			0x01df//判断气瓶抽气是否结束


//关氧路气瓶补加阀门---第一个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1		0x01e0//关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1		0x01e1//判断关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2		0x01e2//关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2		0x01e3//判断关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3		0x01e4//关氧路气瓶补加阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3		0x01e5//判断关氧路气瓶补加阀门，第三组


//开进气瓶补加阀门---第二个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON				0x01e6//开进气瓶补加阀门
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_ON			0x01e7//判断开进气瓶补加阀门


//延时等待time_delay2---第二个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2_START			0x01e8//延时等待time_delay2计时开始
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_DELAY2				0x01e9//判断延时等待time_delay2


//判断气瓶压力是否升高---第二个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO1			0x01ea//采集气瓶压力，第一次
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO1			0x01eb//计时30s计时开始，第一次
#define		COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO1				0x01ec//判断定时30s，第一次
#define		COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO2			0x01ed//采集气瓶压力，第二次
#define		COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO2			0x01ee//计时30s计时开始，第二次
#define		COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO2				0x01ef//判断定时30s，第二次
#define		COMMAND_13_0007_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO3			0x01f0//采集气瓶压力，第三次
#define		COMMAND_13_0008_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO3			0x01f1//计时30s计时开始，第三次
#define		COMMAND_13_0009_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO3				0x01f2//判断定时30s，第三次
#define		COMMAND_13_0010_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO4			0x01f3//采集气瓶压力，第四次
#define		COMMAND_13_0011_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO4			0x01f4//计时30s计时开始，第四次
#define		COMMAND_13_0012_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO4				0x01f5//判断定时30s，第四次
#define		COMMAND_13_0013_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO5			0x01f6//采集气瓶压力，第五次
#define		COMMAND_13_0014_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO5			0x01f7//计时30s计时开始，第五次
#define		COMMAND_13_0015_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO5				0x01f8//判断定时30s，第五次
#define		COMMAND_13_0016_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO6			0x01f9//采集气瓶压力，第六次
#define		COMMAND_13_0017_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO6			0x01fa//计时30s计时开始，第六次
#define		COMMAND_13_0018_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO6				0x01fb//判断定时30s，第六次
#define		COMMAND_13_0019_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO7			0x01fc//采集气瓶压力，第七次
#define		COMMAND_13_0020_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO7			0x01fd//计时30s计时开始，第七次
#define		COMMAND_13_0021_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO7				0x01fe//判断定时30s，第七次
#define		COMMAND_13_0022_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO8			0x01ff//采集气瓶压力，第八次
#define		COMMAND_13_0023_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO8			0x0200//计时30s计时开始，第八次
#define		COMMAND_13_0024_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO8				0x0201//判断定时30s，第八次
#define		COMMAND_13_0025_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO9			0x0202//采集气瓶压力，第九次
#define		COMMAND_13_0026_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO9			0x0203//计时30s计时开始，第九次
#define		COMMAND_13_0027_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO9				0x0204//判断定时30s，第九次
#define		COMMAND_13_0028_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO10			0x0205//采集气瓶压力，第十次
#define		COMMAND_13_0029_O_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE				0x0206//压差判断气瓶压力是否升高


//判断气瓶抽气是否结束---第二个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IS_COMP_GAS_OVER			0x0207//判断气瓶抽气是否结束

//关氧路气瓶补加阀门---第二个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1		0x0208//关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1		0x0209//判断关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2		0x020a//关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2		0x020b//判断关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3		0x020c//关氧路气瓶补加阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3		0x020d//判断关氧路气瓶补加阀门，第三组


//关进贮箱低压气路补加阀门
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO1			0x020e//关进贮箱低压气路补加阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO1			0x020f//判断关进贮箱低压气路补加阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO2			0x0210//关进贮箱低压气路补加阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO2			0x0211//判断关进贮箱低压气路补加阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO3			0x0212//关进贮箱低压气路补加阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO3			0x0213//判断关进贮箱低压气路补加阀门，第三组


//通过压力判断关进贮箱补加阀
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO1	0x0214//通过压力判断关进贮箱补加阀，第一组
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO2	0x0215//通过压力判断关进贮箱补加阀，第二组
#define		COMMAND_13_0003_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO3	0x0216//通过压力判断关进贮箱补加阀，第三组
#define		COMMAND_13_0004_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO4	0x0217//通过压力判断关进贮箱补加阀，第四组
#define		COMMAND_13_0005_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO5	0x0218//通过压力判断关进贮箱补加阀，第五组
#define		COMMAND_13_0006_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE		0x0219//通过压力判断关进贮箱补加阀，五取三


//------------------------------command---两个贮箱抽气----第二个贮箱抽气-----------------------------------

//开进贮箱低压气路补加阀门---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_IN_TANK_VALVE_ON					0x021a//开进贮箱低压气路补加阀门
#define		COMMAND_13_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON				0x021b//判断开进贮箱低压气路补加阀门


//通过压力判断开进贮箱阀门---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE		0x021c//通过压力判断开补加阀门

//判断抽气气瓶个数---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_NUMBER_COMP_GAS					0x021d//判断抽气气瓶个数


//------------------------------command---两个贮箱抽气----第二个贮箱抽气----一个气瓶抽气--------------------

//开进气瓶补加阀门---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON				0x021e//开进气瓶补加阀门
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_ON			0x021f//判断开进气瓶补加阀门


//延时等待time_delay2---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_DELAY2_START			0x0220//延时等待time_delay2计时开始
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_DELAY2				0x0221//判断延时等待time_delay2


//判断气瓶压力是否升高---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO1				0x0222//采集气瓶压力，第一次
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_TIME_30S_START_NO1			0x0223//计时30s计时开始，第一次
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO1				0x0224//判断定时30s，第一次
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO2				0x0225//采集气瓶压力，第二次
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_TIME_30S_START_NO2			0x0226//计时30s计时开始，第二次
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO2				0x0227//判断定时30s，第二次
#define		COMMAND_13_0007_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO3				0x0228//采集气瓶压力，第三次
#define		COMMAND_13_0008_O_2TANK_TANK2_1GAS_TIME_30S_START_NO3			0x0229//计时30s计时开始，第三次
#define		COMMAND_13_0009_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO3				0x022a//判断定时30s，第三次
#define		COMMAND_13_0010_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO4				0x022b//采集气瓶压力，第四次
#define		COMMAND_13_0011_O_2TANK_TANK2_1GAS_TIME_30S_START_NO4			0x022c//计时30s计时开始，第四次
#define		COMMAND_13_0012_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO4				0x022d//判断定时30s，第四次
#define		COMMAND_13_0013_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO5				0x022e//采集气瓶压力，第五次
#define		COMMAND_13_0014_O_2TANK_TANK2_1GAS_TIME_30S_START_NO5			0x022f//计时30s计时开始，第五次
#define		COMMAND_13_0015_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO5				0x0230//判断定时30s，第五次
#define		COMMAND_13_0016_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO6				0x0231//采集气瓶压力，第六次
#define		COMMAND_13_0017_O_2TANK_TANK2_1GAS_TIME_30S_START_NO6			0x0232//计时30s计时开始，第六次
#define		COMMAND_13_0018_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO6				0x0233//判断定时30s，第六次
#define		COMMAND_13_0019_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO7				0x0234//采集气瓶压力，第七次
#define		COMMAND_13_0020_O_2TANK_TANK2_1GAS_TIME_30S_START_NO7			0x0235//计时30s计时开始，第七次
#define		COMMAND_13_0021_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO7				0x0236//判断定时30s，第七次
#define		COMMAND_13_0022_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO8				0x0237//采集气瓶压力，第八次
#define		COMMAND_13_0023_O_2TANK_TANK2_1GAS_TIME_30S_START_NO8			0x0238//计时30s计时开始，第八次
#define		COMMAND_13_0024_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO8				0x0239//判断定时30s，第八次
#define		COMMAND_13_0025_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO9				0x023a//采集气瓶压力，第九次
#define		COMMAND_13_0026_O_2TANK_TANK2_1GAS_TIME_30S_START_NO9			0x023b//计时30s计时开始，第九次
#define		COMMAND_13_0027_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO9				0x023c//判断定时30s，第九次
#define		COMMAND_13_0028_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO10			0x023d//采集气瓶压力，第十次
#define		COMMAND_13_0029_O_2TANK_TANK2_1GAS_IS_GAS_PRESSURE				0x023e//压差判断气瓶压力是否升高


//判断气瓶抽气是否结束---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_COMP_GAS_OVER				0x023f//判断气瓶抽气是否结束


//关氧路气瓶补加阀门---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO1			0x0240//关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO1		0x0241//判断关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO2			0x0242//关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO2		0x0243//判断关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO3			0x0244//关氧路气瓶补加阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO3		0x0245//判断关氧路气瓶补加阀门，第三组

//通过压力判断高压气路隔离是否正常，第一次
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO1	0x0246//采集压气机出口压力，第一次
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO1		0x0247//计时12s计时开始，第一次
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO1		0x0248//判断定时12s，第一次
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO2	0x0249//采集压气机出口压力，第二次
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO2		0x024a//计时12s计时开始，第二次
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO2		0x024b//判断定时12s，第二次
#define		COMMAND_13_0007_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO3	0x024c//采集压气机出口压力，第三次
#define		COMMAND_13_0008_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO3		0x024d//计时12s计时开始，第三次
#define		COMMAND_13_0009_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO3		0x024e//判断定时12s，第三次
#define		COMMAND_13_0010_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO4	0x024f//采集压气机出口压力，第四次
#define		COMMAND_13_0011_O_2TANK_TANK2_1GAS_FIRST_IS_ISOLATION			0x0250//通过压力判断高压气路隔离是否正常

//关闭氧压气机出口阀门---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x0251//关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1	0x0252//判断关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x0253//关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2	0x0254//判断关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x0255//关闭氧压气机出口阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3	0x0256//判断关闭氧压气机出口阀门，第三组

//通过压力判断高压气路隔离是否正常，第一次
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO1	0x0257//采集压气机出口压力，第一次
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO1		0x0258//计时12s计时开始，第一次
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO1			0x0259//判断定时12s，第一次
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO2	0x025a//采集压气机出口压力，第二次
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO2		0x025b//计时12s计时开始，第二次
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO2			0x025c//判断定时12s，第二次
#define		COMMAND_13_0007_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO3	0x025d//采集压气机出口压力，第三次
#define		COMMAND_13_0008_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO3		0x025e//计时12s计时开始，第三次
#define		COMMAND_13_0009_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO3			0x025f//判断定时12s，第三次
#define		COMMAND_13_0010_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO4	0x0260//采集压气机出口压力，第四次
#define		COMMAND_13_0011_O_2TANK_TANK2_1GAS_SECOND_IS_ISOLATION				0x0261//通过压力判断高压气路隔离是否正常

//氧压气机停机---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP					0x0262//申请设备管理指令，压气机停机
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START		0x0263//延时1min计时开始
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN			0x0264//判断1min定时


//判断氧压气机停机是否正常---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO1					0x0265//采集电机转速，第一次
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO2					0x0266//采集电机转速，第二次
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO3					0x0267//采集电机转速，第三次
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO4					0x0268//采集电机转速，第四次
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO5					0x0269//采集电机转速，第五次
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO6					0x026a//采集电机转速，第六次
#define		COMMAND_13_0007_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO7					0x026b//采集电机转速，第七次
#define		COMMAND_13_0008_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO8					0x026c//采集电机转速，第八次
#define		COMMAND_13_0009_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_PRESSURE_NO1		0x026d//采集压气机出口压力，第一次
#define		COMMAND_13_0010_O_2TANK_TANK2_1GAS_TIME_12S_START					0x026e//计时12s计时开始
#define		COMMAND_13_0011_O_2TANK_TANK2_1GAS_IS_TIME_12S						0x026f//判断定时12s
#define		COMMAND_13_0012_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_PRESSURE_NO2		0x0270//采集压气机出口压力，第二次
#define		COMMAND_13_0013_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_STOP				0x0271//判断氧压气机停机是否正常


//开氧压气机旁路自锁阀---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_BYPATH_VALVE_ON					0x0272//开氧压气机旁路自锁阀
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_ON				0x0273//判断开氧压气机旁路自锁阀


//延时等待time_bypath---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_BYPATH_START				0x0274//延时等待time_bypath计时开启
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_BYPATH					0x0275//判断延时等待time_bypath


//关氧压气机旁路自锁阀---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF					0x0276//关氧压气机旁路自锁阀
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_OFF				0x0277//判断关氧压气机旁路自锁阀

//关闭氧压气机出口阀门
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x0278//关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x0279//判断关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x027a//关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x027b//判断关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x027c//关闭氧压气机出口阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x027d//判断关闭氧压气机出口阀门，第三组

//关闭氧压气机进口阀门
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x027e//关闭氧压气机进口阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1	0x027f//判断关闭氧压气机进口阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0280//关闭氧压气机进口阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2	0x0281//判断关闭氧压气机进口阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x0282//关闭氧压气机进口阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3	0x0283//判断关闭氧压气机进口阀门，第三组


//关进贮箱低压气路补加阀门---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO1			0x0284//关进贮箱低压气路补加阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO1			0x0285//判断关进贮箱低压气路补加阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO2			0x0286//关进贮箱低压气路补加阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO2			0x0287//判断关进贮箱低压气路补加阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO3			0x0288//关进贮箱低压气路补加阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO3			0x0289//判断关进贮箱低压气路补加阀门，第三组


//设置氧抽气状态好---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_SET_STATE_GOOD					0x028a//设置氧抽气状态好


//判断压气机温度是否正常---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE		0x028b//判断压气机温度是否正常

//判断是否需要进行液冷模块停机
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_NEED_COOLER_STOP				0x028c//判断是否需要进行液冷模块停机

//延时等待time_delay3---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_DELAY3_START				0x028d//延时等待time_delay3计时开始
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_DELAY3					0x028e//判断延时等待time_delay3



/*
//启动液冷模块切换程序---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_EXCHANGE_COOLER_VALVE_NO1		0x028f//液冷模块切换程序,阀门动作，第一组
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x0290//判断液冷模块切换程序,阀门动作，第一组
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_EXCHANGE_COOLER_VALVE_NO2		0x0291//液冷模块切换程序,阀门动作，第二组
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x0292//判断液冷模块切换程序,阀门动作，第二组
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_EXCHANGE_COOLER_VALVE_NO3		0x0293//液冷模块切换程序,阀门动作，第三组
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x0294//判断液冷模块切换程序,阀门动作，第三组
#define		COMMAND_13_0007_O_2TANK_TANK2_1GAS_EXCHANGE_COOLER_VALVE_NO4		0x0295//液冷模块切换程序,阀门动作，第四组
#define		COMMAND_13_0008_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x0296//判断液冷模块切换程序,阀门动作，第四组


//通过压力判断液冷模块切换是否正常---第二个贮箱
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER				0x0297//通过压力判断液冷模块切换是否正常
*/


//液冷模块停机
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_COOLER_POWER_OFF					0x0298//液冷模块停机

//液冷模块状态设置
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_COOLER_SET_NO1					0x0431
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO1				0x0432
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_COOLER_SET_NO2					0x0433
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO2				0x0434
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_COOLER_SET_NO3					0x0435
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO3				0x0436
#define		COMMAND_13_0007_O_2TANK_TANK2_1GAS_COOLER_SET_NO4					0x0437
#define		COMMAND_13_0008_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO4				0x0438
#define		COMMAND_13_0009_O_2TANK_TANK2_1GAS_COOLER_SET_NO5					0x0439
#define		COMMAND_13_0010_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO5				0x043a
#define		COMMAND_13_0011_O_2TANK_TANK2_1GAS_COOLER_SET_NO6					0x043b
#define		COMMAND_13_0012_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO6				0x043c
#define		COMMAND_13_0013_O_2TANK_TANK2_1GAS_COOLER_SET_NO7					0x043d
#define		COMMAND_13_0014_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO7				0x043e
#define		COMMAND_13_0015_O_2TANK_TANK2_1GAS_COOLER_SET_NO8					0x043f
#define		COMMAND_13_0016_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO8				0x0440
#define		COMMAND_13_0017_O_2TANK_TANK2_1GAS_COOLER_SET_NO9					0x0441
#define		COMMAND_13_0018_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO9				0x0442
#define		COMMAND_13_0019_O_2TANK_TANK2_1GAS_COOLER_SET_NO10					0x0443
#define		COMMAND_13_0020_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO10				0x0444
#define		COMMAND_13_0021_O_2TANK_TANK2_1GAS_COOLER_SET_NO11					0x0445
#define		COMMAND_13_0022_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO11				0x0446
#define		COMMAND_13_0023_O_2TANK_TANK2_1GAS_COOLER_SET_NO12					0x0447
#define		COMMAND_13_0024_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO12				0x0448


//申请压气机断电
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF				0x0299//申请设备管理指令
//#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START		0x029a//延时1min计时开始
//#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN			0x029b//判断计时1min是否到

//申请电机驱动器断电
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF				0x029c//申请设备管理指令
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_TGTHT530_TIME_1MIN_START			0x029d//延时1min计时开始
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_TGTHT530_IS_TIME_1MIN			0x029e//判断计时1min是否到


//------------------------------command---两个贮箱抽气----第二个贮箱抽气----两个气瓶抽气--------------------

//开进气瓶补加阀门---第一个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON				0x029f//开进气瓶补加阀门
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_ON			0x02a0//判断开进气瓶补加阀门


//延时等待time_delay2---第一个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2_START			0x02a1//延时等待time_delay2计时开始
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_DELAY2				0x02a2//判断延时等待time_delay2


//判断气瓶压力是否升高---第一个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO1			0x02a3//采集气瓶压力，第一次
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO1			0x02a4//计时30s计时开始，第一次
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO1				0x02a5//判断定时30s，第一次
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO2			0x02a6//采集气瓶压力，第二次
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO2			0x02a7//计时30s计时开始，第二次
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO2				0x02a8//判断定时30s，第二次
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO3			0x02a9//采集气瓶压力，第三次
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO3			0x02aa//计时30s计时开始，第三次
#define		COMMAND_13_0009_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO3				0x02ab//判断定时30s，第三次
#define		COMMAND_13_0010_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO4			0x02ac//采集气瓶压力，第四次
#define		COMMAND_13_0011_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO4			0x02ad//计时30s计时开始，第四次
#define		COMMAND_13_0012_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO4				0x02ae//判断定时30s，第四次
#define		COMMAND_13_0013_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO5			0x02af//采集气瓶压力，第五次
#define		COMMAND_13_0014_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO5			0x02b0//计时30s计时开始，第五次
#define		COMMAND_13_0015_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO5				0x02b1//判断定时30s，第五次
#define		COMMAND_13_0016_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO6			0x02b2//采集气瓶压力，第六次
#define		COMMAND_13_0017_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO6			0x02b3//计时30s计时开始，第六次
#define		COMMAND_13_0018_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO6				0x02b4//判断定时30s，第六次
#define		COMMAND_13_0019_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO7			0x02b5//采集气瓶压力，第七次
#define		COMMAND_13_0020_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO7			0x02b6//计时30s计时开始，第七次
#define		COMMAND_13_0021_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO7				0x02b7//判断定时30s，第七次
#define		COMMAND_13_0022_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO8			0x02b8//采集气瓶压力，第八次
#define		COMMAND_13_0023_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO8			0x02b9//计时30s计时开始，第八次
#define		COMMAND_13_0024_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO8				0x02ba//判断定时30s，第八次
#define		COMMAND_13_0025_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO9			0x02bb//采集气瓶压力，第九次
#define		COMMAND_13_0026_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO9			0x02bc//计时30s计时开始，第九次
#define		COMMAND_13_0027_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO9				0x02bd//判断定时30s，第九次
#define		COMMAND_13_0028_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO10			0x02be//采集气瓶压力，第十次
#define		COMMAND_13_0029_O_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE				0x02bf//压差判断气瓶压力是否升高


//判断气瓶抽气是否结束---第一个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IS_COMP_GAS_OVER			0x02c0//判断气瓶抽气是否结束


//关氧路气瓶补加阀门---第一个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1		0x02c1//关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1		0x02c2//判断关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2		0x02c3//关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2		0x02c4//判断关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3		0x02c5//关氧路气瓶补加阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3		0x02c6//判断关氧路气瓶补加阀门，第三组


//开进气瓶补加阀门---第二个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON				0x02c7//开进气瓶补加阀门
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_ON			0x02c8//判断开进气瓶补加阀门

//延时等待time_delay2---第二个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2_START			0x02c9//延时等待time_delay2计时开始
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_DELAY2				0x02ca//判断延时等待time_delay2


//判断气瓶压力是否升高---第二个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO1			0x02cb//采集气瓶压力，第一次
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO1			0x02cc//计时30s计时开始，第一次
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO1				0x02cd//判断定时30s，第一次
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO2			0x02ce//采集气瓶压力，第二次
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO2			0x02cf//计时30s计时开始，第二次
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO2				0x02d0//判断定时30s，第二次
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO3			0x02d1//采集气瓶压力，第三次
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO3			0x02d2//计时30s计时开始，第三次
#define		COMMAND_13_0009_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO3				0x02d3//判断定时30s，第三次
#define		COMMAND_13_0010_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO4			0x02d4//采集气瓶压力，第四次
#define		COMMAND_13_0011_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO4			0x02d5//计时30s计时开始，第四次
#define		COMMAND_13_0012_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO4				0x02d6//判断定时30s，第四次
#define		COMMAND_13_0013_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO5			0x02d7//采集气瓶压力，第五次
#define		COMMAND_13_0014_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO5			0x02d8//计时30s计时开始，第五次
#define		COMMAND_13_0015_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO5				0x02d9//判断定时30s，第五次
#define		COMMAND_13_0016_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO6			0x02da//采集气瓶压力，第六次
#define		COMMAND_13_0017_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO6			0x02db//计时30s计时开始，第六次
#define		COMMAND_13_0018_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO6				0x02dc//判断定时30s，第六次
#define		COMMAND_13_0019_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO7			0x02dd//采集气瓶压力，第七次
#define		COMMAND_13_0020_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO7			0x02de//计时30s计时开始，第七次
#define		COMMAND_13_0021_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO7				0x02df//判断定时30s，第七次
#define		COMMAND_13_0022_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO8			0x02e0//采集气瓶压力，第八次
#define		COMMAND_13_0023_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO8			0x02e1//计时30s计时开始，第八次
#define		COMMAND_13_0024_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO8				0x02e2//判断定时30s，第八次
#define		COMMAND_13_0025_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO9			0x02e3//采集气瓶压力，第九次
#define		COMMAND_13_0026_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO9			0x02e4//计时30s计时开始，第九次
#define		COMMAND_13_0027_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO9				0x02e5//判断定时30s，第九次
#define		COMMAND_13_0028_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO10			0x02e6//采集气瓶压力，第十次
#define		COMMAND_13_0029_O_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE				0x02e7//压差判断气瓶压力是否升高


//判断气瓶抽气是否结束---第二个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IS_COMP_GAS_OVER			0x02e8//判断气瓶抽气是否结束


//关氧路气瓶补加阀门---第二个气瓶
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1		0x02e9//关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1		0x02ea//判断关氧路气瓶补加阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2		0x02eb//关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2		0x02ec//判断关氧路气瓶补加阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3		0x02ed//关氧路气瓶补加阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3		0x02ee//判断关氧路气瓶补加阀门，第三组

//通过压力判断高压气路隔离是否正常，第一次
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO1		0x02ef//采集压气机出口压力，第一次
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO1			0x02f0//计时12s计时开始，第一次
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO1			0x02f1//判断定时12s，第一次
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO2		0x02f2//采集压气机出口压力，第二次
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO2			0x02f3//计时12s计时开始，第二次
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO2			0x02f4//判断定时12s，第二次
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO3		0x02f5//采集压气机出口压力，第三次
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO3			0x02f6//计时12s计时开始，第三次
#define		COMMAND_13_0009_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO3			0x02f7//判断定时12s，第三次
#define		COMMAND_13_0010_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO4		0x02f8//采集压气机出口压力，第四次
#define		COMMAND_13_0011_O_2TANK_TANK2_2GAS_FIRST_IS_ISOLATION				0x02f9//通过压力判断高压气路隔离是否正常

//关闭氧压气机出口阀门
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x02fa//关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1	0x02fb//判断关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x02fc//关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2	0x02fd//判断关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x02fe//关闭氧压气机出口阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3	0x02ff//判断关闭氧压气机出口阀门，第三组

//通过压力判断高压气路隔离是否正常，第2次
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO1	0x0300//采集压气机出口压力，第一次
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO1		0x0301//计时12s计时开始，第一次
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO1			0x0302//判断定时12s，第一次
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO2	0x0303//采集压气机出口压力，第二次
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO2		0x0304//计时12s计时开始，第二次
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO2			0x0305//判断定时12s，第二次
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO3	0x0306//采集压气机出口压力，第三次
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO3		0x0307//计时12s计时开始，第三次
#define		COMMAND_13_0009_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO3			0x0308//判断定时12s，第三次
#define		COMMAND_13_0010_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO4	0x0309//采集压气机出口压力，第四次
#define		COMMAND_13_0011_O_2TANK_TANK2_2GAS_SECOND_IS_ISOLATION				0x030a//通过压力判断高压气路隔离是否正常

//氧压气机停机
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP					0x030b//申请设备管理指令，压气机停机
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START		0x030c//延时1min计时开始
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN			0x030d//判断1min定时


//判断氧压气机停机是否正常
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO1					0x030e//采集电机转速，第一次
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO2					0x030f//采集电机转速，第二次
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO3					0x0310//采集电机转速，第三次
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO4					0x0311//采集电机转速，第四次
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO5					0x0312//采集电机转速，第五次
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO6					0x0313//采集电机转速，第六次
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO7					0x0314//采集电机转速，第七次
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO8					0x0315//采集电机转速，第八次
#define		COMMAND_13_0009_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_PRESSURE_NO1		0x0316//采集压气机出口压力，第一次
#define		COMMAND_13_0010_O_2TANK_TANK2_2GAS_TIME_12S_START					0x0317//计时12s计时开始
#define		COMMAND_13_0011_O_2TANK_TANK2_2GAS_IS_TIME_12S						0x0318//判断定时12s
#define		COMMAND_13_0012_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_PRESSURE_NO2		0x0319//采集压气机出口压力，第二次
#define		COMMAND_13_0013_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_STOP				0x031a//判断氧压气机停机是否正常


//开氧压气机旁路自锁阀
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_BYPATH_VALVE_ON					0x031b//开氧压气机旁路自锁阀
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_ON				0x031c//判断开氧压气机旁路自锁阀


//延时等待time_bypath
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_TIME_BYPATH_START				0x031d//延时等待time_bypath计时开启
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_TIME_BYPATH					0x031e//判断延时等待time_bypath


//关氧压气机旁路自锁阀
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF					0x031f//关氧压气机旁路自锁阀
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_OFF				0x0320//判断关氧压气机旁路自锁阀

//关闭氧压气机出口阀门
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1	0x0321//关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1	0x0322//判断关闭氧压气机出口阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2	0x0323//关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2	0x0324//判断关闭氧压气机出口阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3	0x0325//关闭氧压气机出口阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3	0x0326//判断关闭氧压气机出口阀门，第三组


//关闭氧压气机进口阀门
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x0327//关闭氧压气机进口阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1	0x0328//判断关闭氧压气机进口阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0329//关闭氧压气机进口阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2	0x032a//判断关闭氧压气机进口阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x032b//关闭氧压气机进口阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3	0x032c//判断关闭氧压气机进口阀门，第三组


//关进贮箱低压气路补加阀门
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO1			0x032d//关进贮箱低压气路补加阀门，第一组
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO1			0x032e//判断关进贮箱低压气路补加阀门，第一组
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO2			0x032f//关进贮箱低压气路补加阀门，第二组
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO2			0x0330//判断关进贮箱低压气路补加阀门，第二组
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO3			0x0331//关进贮箱低压气路补加阀门，第三组
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO3			0x0332//判断关进贮箱低压气路补加阀门，第三组


//设置氧抽气状态好
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_SET_STATE_GOOD					0x0333//设置氧抽气状态好


//判断压气机温度是否正常
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE		0x0334//判断压气机温度是否正常

//判断是否需要进行液冷模块停机
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_NEED_COOLER_STOP				0x0335//判断是否需要进行液冷模块停机

//延时等待time_delay3
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_TIME_DELAY3_START				0x0336//延时等待time_delay3计时开始
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_TIME_DELAY3					0x0337//判断延时等待time_delay3


/*
//启动液冷模块切换程序
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_EXCHANGE_COOLER_VALVE_NO1		0x0338//液冷模块切换程序,阀门动作，第一组
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x0339//判断液冷模块切换程序,阀门动作，第一组
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_EXCHANGE_COOLER_VALVE_NO2		0x033a//液冷模块切换程序,阀门动作，第二组
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x033b//判断液冷模块切换程序,阀门动作，第二组
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_EXCHANGE_COOLER_VALVE_NO3		0x033c//液冷模块切换程序,阀门动作，第三组
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x033d//判断液冷模块切换程序,阀门动作，第三组
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_EXCHANGE_COOLER_VALVE_NO4		0x033e//液冷模块切换程序,阀门动作，第四组
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x033f//判断液冷模块切换程序,阀门动作，第四组

//通过压力判断液冷模块切换是否正常
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER				0x0340//通过压力判断液冷模块切换是否正常
*/


//液冷模块停机
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_COOLER_POWER_OFF					0x0341//液冷模块停机


//液冷模块状态设置
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_COOLER_SET_NO1					0x0449
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO1				0x044a
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_COOLER_SET_NO2					0x044b
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO2				0x044c
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_COOLER_SET_NO3					0x044d
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO3				0x044e
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_COOLER_SET_NO4					0x044f
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO4				0x0450
#define		COMMAND_13_0009_O_2TANK_TANK2_2GAS_COOLER_SET_NO5					0x0451
#define		COMMAND_13_0010_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO5				0x0452
#define		COMMAND_13_0011_O_2TANK_TANK2_2GAS_COOLER_SET_NO6					0x0453
#define		COMMAND_13_0012_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO6				0x0454
#define		COMMAND_13_0013_O_2TANK_TANK2_2GAS_COOLER_SET_NO7					0x0455
#define		COMMAND_13_0014_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO7				0x0456
#define		COMMAND_13_0015_O_2TANK_TANK2_2GAS_COOLER_SET_NO8					0x0457
#define		COMMAND_13_0016_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO8				0x0458
#define		COMMAND_13_0017_O_2TANK_TANK2_2GAS_COOLER_SET_NO9					0x0459
#define		COMMAND_13_0018_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO9				0x045a
#define		COMMAND_13_0019_O_2TANK_TANK2_2GAS_COOLER_SET_NO10					0x045b
#define		COMMAND_13_0020_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO10				0x045c
#define		COMMAND_13_0021_O_2TANK_TANK2_2GAS_COOLER_SET_NO11					0x045d
#define		COMMAND_13_0022_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO11				0x045e
#define		COMMAND_13_0023_O_2TANK_TANK2_2GAS_COOLER_SET_NO12					0x045f
#define		COMMAND_13_0024_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO12				0x0460


//申请压气机断电
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF				0x0342//申请设备管理指令
//#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START		0x0343//延时1min计时开始
//#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN			0x0344//判断计时1min是否到

//申请电机驱动器断电
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF				0x0345//申请设备管理指令
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_TGTHT530_TIME_1MIN_START			0x0346//延时1min计时开始
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_TGTHT530_IS_TIME_1MIN			0x0347//判断计时1min是否到


//0x0460
//------------------------函数声明---------------------------------------------------------

void TGTHT510_supply_stage13_comp_O_main(void);

//-------------------------------------------------初始设置阶段----------------------------------------------------

uint16 TGTHT510_supply_stage13_comp_O_init_step_start_cooler(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_is_cooler_work(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_time_delay(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_is_compressor_temperature(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_TGTHT530_power_on(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_compressor_power_on(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_isolation(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_number_comp_tank(void);

//-------------------------------------------------一个贮箱抽气----------------------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_is_in_tank_valve_on_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_in_compressor_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_time_delay1(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_is_in_compressor_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_compressor_start(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_is_out_compressor_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_out_compressor_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_number_comp_gas(void);

//-----------------------------------一个贮箱抽气，一个气瓶抽气----------------------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_compressor_temperature(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_need_cooler_stop(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay3(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_cooler_set(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_TGTHT530_power_off(void);


//-----------------------------------一个贮箱抽气，两个气瓶抽气----------------------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_compressor_temperature(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_need_cooler_stop(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_time_delay3(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_cooler_set(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_TGTHT530_power_off(void);


//---------------------------------两个贮箱抽气，第一个贮箱抽气----------------------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_in_tank_valve_on_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_in_compressor_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_time_delay1(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_in_compressor_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_compressor_start(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_out_compressor_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_out_compressor_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_number_comp_gas(void);

//---------------------------------两个贮箱抽气，第一个贮箱抽气，一个气瓶抽气--------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_in_tank_valve_pressure(void);

//---------------------------------两个贮箱抽气，第一个贮箱抽气，两个气瓶抽气--------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_step_is_in_tank_valve_pressure(void);

//---------------------------------两个贮箱抽气，第二个贮箱抽气----------------------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_step_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_step_is_in_tank_valve_on_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_step_number_comp_gas(void);

//---------------------------------两个贮箱抽气，第二个贮箱抽气，一个气瓶抽气--------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_compressor_temperature(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_need_cooler_stop(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay3(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_cooler_set(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_TGTHT530_power_off(void);


//---------------------------------两个贮箱抽气，第二个贮箱抽气，两个气瓶抽气--------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_compressor_temperature(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_need_cooler_stop(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_time_delay3(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_cooler_set(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_TGTHT530_power_off(void);


//---------------------------------------------------------通用函数------------------------------------------------



#endif
 
 
 
