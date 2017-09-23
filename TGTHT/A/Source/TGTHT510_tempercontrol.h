/**
  ******************************************************************************
  * @file    TGTHT510_tempercontrol.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器自动控温模块头文件
  ******************************************************************************
  */

#ifndef __TGTHT510_tempercontrol_h
#define __TGTHT510_tempercontrol_h 

/*声明结构体类型---------------------------------------------------------*/

typedef struct
{
	uint16 control_state;			//是否参与控温，ENABLE与DISABLE
	uint16 fixed_output_state;		//是否固定占空比输出，ENABLE与DISABLE
	uint16 control_spot[3];			//控温点，分别为T1、T2、T3
	uint16 power[2];				//功耗，分别为主路功耗，备路功耗
	uint16 fixed_output_count;		//固定占控比输出计数器
	uint16 source_data[7];			//测点数据来源标识
	uint16 number;					//控温回路路号，序号为0~49路

}Temperature_control_block_TypeDef;	//温度控制块结构体定义

/*
source_data[7]为测点数据来源标识；

bit15—14为00表示测点温度传感器为MF51；
bit15—14为01表示测点温度传感器为铂电阻；
bit15—14为10表示测点温度传感器为MF61；

bit13-12为01表示该测点温度值位于推进遥测线路盒遥测帧复帧A帧；
bit13-12为10表示该测点温度值位于推进遥测线路盒遥测帧复帧B帧；

bit11-10为00表示该测点温度值在推进遥测线路盒遥测帧中为字（16位）表示；
bit11-10为01表示该测点温度值在推进遥测线路盒遥测帧中为高字节（8位）表示；
bit11-10为10表示该测点温度值在推进遥测线路盒遥测帧中为低字节（8位）表示；

bit9-8保持为00，预留；

bit7-0使用字节（8位）表示该测点温度值在推进遥测线路盒遥测帧中缓存位置；

无效测点代号固定为0xffff

*/



typedef struct
{
	uint16 data_state_TGTHT100;		//遥测线路盒温度数据是否正常，ENABLE与DISABLE
	uint16 data_state_KPU;			//数管遥测数据是否正常，ENABLE与DISABLE
	uint16 source;					//控温使用遥测数据来源，遥测线路盒或者数管
	uint16 total_power;				//控温限制功耗
	
}Temperature_control_global_TypeDef;//温度控制全局变量结构体定义


typedef struct
{
	uint16 auto_control_data[50];				//自动控温回路有效控温温度，按照温度从小至大顺序排列
	uint16 auto_control_num[50];				//自动控温回路路号，按照温度从小至大顺序排列
	uint16 auto_control_count;					//自动控温回路数量
	uint16 auto_control_last_state_main[50];	//自动控温，主路上一周期状态，ENABLE或者DISABLE，下标即控温回路路号
	uint16 auto_control_last_state_less[50];	//自动控温，备路上一周期状态，ENABLE或者DISABLE，下标即控温回路路号
	uint16 fixed_control_data[50];				//固定占空比输出计数
	uint16 fixed_control_num[50];				//固定占空比输出路号
	uint16 fixed_control_count;					//固定占空比输出回路数量
	
}Temperature_control_valid_data_TypeDef;//控温有效参数结构体


typedef struct
{
	uint16 temp[7];
}Temperature_control_temp_TypeDef;//缓存临时数组



/*宏定义----------------------------------------------------------------------*/

#define SOURCE_DATA_A 			0x000a//遥测线路盒复帧A
#define SOURCE_DATA_B 			0x000b//遥测线路盒复帧B
#define SOURCE_DATA_AB			0x00ab//遥测线路盒复帧a
#define SOURCE_DATA_NONE 		0xccff//无控温测点

#define TEMPER_SPOT_T1			0x0752//控温点T1，4摄氏度，MF61源码值
#define TEMPER_SPOT_T2			0x06a9//控温点T2，8摄氏度，MF61源码值
#define TEMPER_SPOT_T3			0x0608//控温点T3，12摄氏度，MF61源码值

#define SOURCE_DATA_TGTHT100	0x4e4e//控温使用遥测数据来源，推进遥测线路盒
#define SOURCE_DATA_KPU			0x6f6f//控温使用遥测数据来源，数管KPU

#define SENSOR_TYPE_51			0x5151//温度传感器类型，MF51
#define SENSOR_TYPE_61			0x6161//温度传感器类型，MF61
#define SENSOR_TYPE_PT			0xabab//温度传感器类型，铂电阻


#define HEATER_MAIN				0x3131//主份加热器通
#define HEATER_LESS				0x3939//备份加热器通
#define HEATER_BOTH				0x3f3f//主、备加热器通

#define POWER_INITIAL			0x012c//初始限制功耗300w

#define FIXED_UPDATE			0x4e4e//固定占比计数，此周期更新，出现某路计数为零
#define FIXED_NO_UPDATE			0x6f6f//固定占比计数，此周期更新，未出现某路计数为零

#define TEMP_RANGE_LESS_T1			0x2323//温度值小于控温点T1	
#define TEMP_RANGE_BETWEEN_T1_T2	0x2626//温度值在控温点T1与T2之间
#define TEMP_RANGE_BETWEEN_T2_T3	0x2929//温度值在控温点T2与T3之间
#define TEMP_RANGE_MORE_T3			0x2e2e//温度值大于控温点T3




#define TEMCONTROL_REG0 	0x21800000
#define TEMCONTROL_REG1 	0x21800004
#define TEMCONTROL_REG2 	0x21800008
#define TEMCONTROL_REG3 	0x2180000c
#define TEMCONTROL_REG4 	0x22800000
#define TEMCONTROL_REG5 	0x22800004
#define TEMCONTROL_REG6 	0x22800008
#define TEMCONTROL_REG7 	0x2280000c//加热器控制输出寄存器地址



/*
#define TEMP_MF51_NEG_50 	0x07e7//MF51,-50摄氏度对应源码值
#define TEMP_MF51_NEG_40	0x07d5//MF51,-40摄氏度对应源码值
#define TEMP_MF51_NEG_30	0x07ba//MF51,-30摄氏度对应源码值
#define TEMP_MF51_NEG_20	0x0792//MF51,-20摄氏度对应源码值
#define TEMP_MF51_NEG_10	0x0757//MF51,-10摄氏度对应源码值
#define TEMP_MF51_MID_0		0x0707//MF51,0摄氏度对应源码值
#define TEMP_MF51_POS_10	0x069e//MF51,10摄氏度对应源码值
#define TEMP_MF51_POS_20	0x061f//MF51,20摄氏度对应源码值
#define TEMP_MF51_POS_30	0x058c//MF51,30摄氏度对应源码值
#define TEMP_MF51_POS_40	0x04ec//MF51,40摄氏度对应源码值
#define TEMP_MF51_POS_50	0x0448//MF51,50摄氏度对应源码值
#define TEMP_MF51_POS_60	0x03a8//MF51,60摄氏度对应源码值
#define TEMP_MF51_POS_70	0x0315//MF51,70摄氏度对应源码值


#define TEMP_MF61_NEG_50 	0x078c//MF61,-50摄氏度对应源码值
#define TEMP_MF61_NEG_40	0x0732//MF61,-40摄氏度对应源码值
#define TEMP_MF61_NEG_30	0x06ac//MF61,-30摄氏度对应源码值
#define TEMP_MF61_NEG_20	0x05f8//MF61,-20摄氏度对应源码值
#define TEMP_MF61_NEG_10	0x051f//MF61,-10摄氏度对应源码值
#define TEMP_MF61_MID_0		0x0436//MF61,0摄氏度对应源码值
#define TEMP_MF61_POS_10	0x0357//MF61,10摄氏度对应源码值
#define TEMP_MF61_POS_20	0x0292//MF61,20摄氏度对应源码值
#define TEMP_MF61_POS_30	0x01f2//MF61,30摄氏度对应源码值
#define TEMP_MF61_POS_40	0x0175//MF61,40摄氏度对应源码值
#define TEMP_MF61_POS_50	0x0117//MF61,50摄氏度对应源码值
#define TEMP_MF61_POS_60	0x00d1//MF61,60摄氏度对应源码值
#define TEMP_MF61_POS_70	0x009e//MF61,70摄氏度对应源码值


#define TEMP_PT_NEG_50 		0x01b1//铂电阻,-50摄氏度对应源码值
#define TEMP_PT_NEG_40		0x01c1//铂电阻,-40摄氏度对应源码值
#define TEMP_PT_NEG_30		0x01d1//铂电阻,-30摄氏度对应源码值
#define TEMP_PT_NEG_20		0x01e1//铂电阻,-20摄氏度对应源码值
#define TEMP_PT_NEG_10		0x01f0//铂电阻,-10摄氏度对应源码值
#define TEMP_PT_MID_0		0x01ff//铂电阻,0摄氏度对应源码值
#define TEMP_PT_POS_10		0x020e//铂电阻,10摄氏度对应源码值
#define TEMP_PT_POS_20		0x021d//铂电阻,20摄氏度对应源码值
#define TEMP_PT_POS_30		0x022b//铂电阻,30摄氏度对应源码值
#define TEMP_PT_POS_40		0x0239//铂电阻,40摄氏度对应源码值
#define TEMP_PT_POS_50		0x0247//铂电阻,50摄氏度对应源码值
#define TEMP_PT_POS_60		0x0254//铂电阻,60摄氏度对应源码值
#define TEMP_PT_POS_70		0x0262//铂电阻,70摄氏度对应源码值

*/


#define TEMP_MF51_RANGE_SMALLER_NEG_50		0x0101//MF51温度范围，小于-50摄氏度
#define TEMP_MF51_RANGE_NEG_50_40			0x0202//MF51温度范围，大于等于-50摄氏度，小于-40摄氏度
#define TEMP_MF51_RANGE_NEG_40_30			0x0303//MF51温度范围，大于等于-40摄氏度，小于-30摄氏度
#define TEMP_MF51_RANGE_NEG_30_20			0x0404//MF51温度范围，大于等于-30摄氏度，小于-20摄氏度
#define TEMP_MF51_RANGE_NEG_20_10			0x0505//MF51温度范围，大于等于-20摄氏度，小于-10摄氏度
#define TEMP_MF51_RANGE_NEG_10_0			0x0606//MF51温度范围，大于等于-10摄氏度，小于0摄氏度
#define TEMP_MF51_RANGE_POS_0_10			0x0707//MF51温度范围，大于等于0摄氏度，小于10摄氏度
#define TEMP_MF51_RANGE_POS_10_20			0x0808//MF51温度范围，大于等于10摄氏度，小于20摄氏度
#define TEMP_MF51_RANGE_POS_20_30			0x0909//MF51温度范围，大于等于20摄氏度，小于30摄氏度
#define TEMP_MF51_RANGE_POS_30_40			0x0a0a//MF51温度范围，大于等于30摄氏度，小于40摄氏度
#define TEMP_MF51_RANGE_POS_40_50			0x0b0b//MF51温度范围，大于等于40摄氏度，小于50摄氏度
#define TEMP_MF51_RANGE_POS_50_60			0x0c0c//MF51温度范围，大于等于50摄氏度，小于600摄氏度
#define TEMP_MF51_RANGE_POS_60_70			0x0d0d//MF51温度范围，大于等于60摄氏度，小于70摄氏度
#define TEMP_MF51_RANGE_LARGER_POS_70		0x0e0e//MF51温度范围，大于等于70摄氏度


#define TEMP_MF51_RANGE_NEG_50_40_START_NUM		0//MF51温度范围起始查询表下标值
#define TEMP_MF51_RANGE_NEG_40_30_START_NUM		10//MF51温度范围起始查询表下标值
#define TEMP_MF51_RANGE_NEG_30_20_START_NUM		20//MF51温度范围起始查询表下标值
#define TEMP_MF51_RANGE_NEG_20_10_START_NUM		30//MF51温度范围起始查询表下标值
#define TEMP_MF51_RANGE_NEG_10_0_START_NUM		40//MF51温度范围起始查询表下标值
#define TEMP_MF51_RANGE_POS_0_10_START_NUM		50//MF51温度范围起始查询表下标值
#define TEMP_MF51_RANGE_POS_10_20_START_NUM		60//MF51温度范围起始查询表下标值
#define TEMP_MF51_RANGE_POS_20_30_START_NUM		70//MF51温度范围起始查询表下标值
#define TEMP_MF51_RANGE_POS_30_40_START_NUM		80//MF51温度范围起始查询表下标值
#define TEMP_MF51_RANGE_POS_40_50_START_NUM		90//MF51温度范围起始查询表下标值
#define TEMP_MF51_RANGE_POS_50_60_START_NUM		100//MF51温度范围起始查询表下标值
#define TEMP_MF51_RANGE_POS_60_70_START_NUM		110//MF51温度范围起始查询表下标值



#define TEMP_MF61_RANGE_SMALLER_NEG_50		0x0101//MF61温度范围，小于-50摄氏度
#define TEMP_MF61_RANGE_NEG_50_40			0x0202//MF61温度范围，大于等于-50摄氏度，小于-40摄氏度
#define TEMP_MF61_RANGE_NEG_40_30			0x0303//MF61温度范围，大于等于-40摄氏度，小于-30摄氏度
#define TEMP_MF61_RANGE_NEG_30_20			0x0404//MF61温度范围，大于等于-30摄氏度，小于-20摄氏度
#define TEMP_MF61_RANGE_NEG_20_10			0x0505//MF61温度范围，大于等于-20摄氏度，小于-10摄氏度
#define TEMP_MF61_RANGE_NEG_10_0			0x0606//MF61温度范围，大于等于-10摄氏度，小于0摄氏度
#define TEMP_MF61_RANGE_POS_0_10			0x0707//MF61温度范围，大于等于0摄氏度，小于10摄氏度
#define TEMP_MF61_RANGE_POS_10_20			0x0808//MF61温度范围，大于等于10摄氏度，小于20摄氏度
#define TEMP_MF61_RANGE_POS_20_30			0x0909//MF61温度范围，大于等于20摄氏度，小于30摄氏度
#define TEMP_MF61_RANGE_POS_30_40			0x0a0a//MF61温度范围，大于等于30摄氏度，小于40摄氏度
#define TEMP_MF61_RANGE_POS_40_50			0x0b0b//MF61温度范围，大于等于40摄氏度，小于50摄氏度
#define TEMP_MF61_RANGE_POS_50_60			0x0c0c//MF61温度范围，大于等于50摄氏度，小于600摄氏度
#define TEMP_MF61_RANGE_POS_60_70			0x0d0d//MF61温度范围，大于等于60摄氏度，小于70摄氏度
#define TEMP_MF61_RANGE_LARGER_POS_70		0x0e0e//MF61温度范围，大于等于70摄氏度



#define TEMP_MF61_RANGE_NEG_50_40_START_NUM		0//MF61温度范围起始查询表下标值
#define TEMP_MF61_RANGE_NEG_40_30_START_NUM		10//MF61温度范围起始查询表下标值
#define TEMP_MF61_RANGE_NEG_30_20_START_NUM		20//MF61温度范围起始查询表下标值
#define TEMP_MF61_RANGE_NEG_20_10_START_NUM		30//MF61温度范围起始查询表下标值
#define TEMP_MF61_RANGE_NEG_10_0_START_NUM		40//MF61温度范围起始查询表下标值
#define TEMP_MF61_RANGE_POS_0_10_START_NUM		50//MF61温度范围起始查询表下标值
#define TEMP_MF61_RANGE_POS_10_20_START_NUM		60//MF61温度范围起始查询表下标值
#define TEMP_MF61_RANGE_POS_20_30_START_NUM		70//MF61温度范围起始查询表下标值
#define TEMP_MF61_RANGE_POS_30_40_START_NUM		80//MF61温度范围起始查询表下标值
#define TEMP_MF61_RANGE_POS_40_50_START_NUM		90//MF61温度范围起始查询表下标值
#define TEMP_MF61_RANGE_POS_50_60_START_NUM		100//MF61温度范围起始查询表下标值
#define TEMP_MF61_RANGE_POS_60_70_START_NUM		110//MF61温度范围起始查询表下标值


#define TEMP_PT_RANGE_SMALLER_NEG_50		0x0101//铂电阻温度范围，小于-50摄氏度
#define TEMP_PT_RANGE_NEG_50_40				0x0202//铂电阻温度范围，大于等于-50摄氏度，小于-40摄氏度
#define TEMP_PT_RANGE_NEG_40_30				0x0303//铂电阻温度范围，大于等于-40摄氏度，小于-30摄氏度
#define TEMP_PT_RANGE_NEG_30_20				0x0404//铂电阻温度范围，大于等于-30摄氏度，小于-20摄氏度
#define TEMP_PT_RANGE_NEG_20_10				0x0505//铂电阻温度范围，大于等于-20摄氏度，小于-10摄氏度
#define TEMP_PT_RANGE_NEG_10_0				0x0606//铂电阻温度范围，大于等于-10摄氏度，小于0摄氏度
#define TEMP_PT_RANGE_POS_0_10				0x0707//铂电阻温度范围，大于等于0摄氏度，小于10摄氏度
#define TEMP_PT_RANGE_POS_10_20				0x0808//铂电阻温度范围，大于等于10摄氏度，小于20摄氏度
#define TEMP_PT_RANGE_POS_20_30				0x0909//铂电阻温度范围，大于等于20摄氏度，小于30摄氏度
#define TEMP_PT_RANGE_POS_30_40				0x0a0a//铂电阻温度范围，大于等于30摄氏度，小于40摄氏度
#define TEMP_PT_RANGE_POS_40_50				0x0b0b//铂电阻温度范围，大于等于40摄氏度，小于50摄氏度
#define TEMP_PT_RANGE_POS_50_60				0x0c0c//铂电阻温度范围，大于等于50摄氏度，小于600摄氏度
#define TEMP_PT_RANGE_POS_60_70				0x0d0d//铂电阻温度范围，大于等于60摄氏度，小于70摄氏度
#define TEMP_PT_RANGE_LARGER_POS_70			0x0e0e//铂电阻温度范围，大于等于70摄氏度


#define TEMP_PT_RANGE_NEG_50_40_START_NUM		0//铂电阻温度范围起始查询表下标值
#define TEMP_PT_RANGE_NEG_40_30_START_NUM		10//铂电阻温度范围起始查询表下标值
#define TEMP_PT_RANGE_NEG_30_20_START_NUM		20//铂电阻温度范围起始查询表下标值
#define TEMP_PT_RANGE_NEG_20_10_START_NUM		30//铂电阻温度范围起始查询表下标值
#define TEMP_PT_RANGE_NEG_10_0_START_NUM		40//铂电阻温度范围起始查询表下标值
#define TEMP_PT_RANGE_POS_0_10_START_NUM		50//铂电阻温度范围起始查询表下标值
#define TEMP_PT_RANGE_POS_10_20_START_NUM		60//铂电阻温度范围起始查询表下标值
#define TEMP_PT_RANGE_POS_20_30_START_NUM		70//铂电阻温度范围起始查询表下标值
#define TEMP_PT_RANGE_POS_30_40_START_NUM		80//铂电阻温度范围起始查询表下标值
#define TEMP_PT_RANGE_POS_40_50_START_NUM		90//铂电阻温度范围起始查询表下标值
#define TEMP_PT_RANGE_POS_50_60_START_NUM		100//铂电阻温度范围起始查询表下标值
#define TEMP_PT_RANGE_POS_60_70_START_NUM		110//铂电阻温度范围起始查询表下标值

//------------------------------------温度控制块宏定义------------------------------

#define TCB_INVALID_DATA	0xffff		//无效测点

#define TCB_SENSOR_PT_R		0x4000		//测点温度传感器为铂电阻
#define TCB_SENSOR_MF51		0x0000		//测点温度传感器为MF51
#define TCB_SENSOR_MF61		0x8000		//测点温度传感器为MF61

#define TCB_FROM_100_A		0x1000		//测点数据位于推进遥测线路盒遥测帧复帧A帧
#define TCB_FROM_100_B		0x2000		//测点数据位于推进遥测线路盒遥测帧复帧B帧

#define TCB_WORD_A			0x0000		//测点数据在推进遥测线路盒遥测帧中为字（16位）表示
#define TCB_BYTE_H			0x0400		//测点数据在推进遥测线路盒遥测帧中为高字节（8位）表示
#define TCB_BYTE_L			0x0800		//测点数据在推进遥测线路盒遥测帧中为低字节（8位）表示

#define TCB_LOC_00			0x0000		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_01			0x0001		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_02			0x0002		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_03			0x0003		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_04			0x0004		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_05			0x0005		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_06			0x0006		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_07			0x0007		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_08			0x0008		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_09			0x0009		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_10			0x000a		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_11			0x000b		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_12			0x000c		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_13			0x000d		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_14			0x000e		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_15			0x000f		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_16			0x0010		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_17			0x0011		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_18			0x0012		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_19			0x0013		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_20			0x0014		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_21			0x0015		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_22			0x0016		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_23			0x0017		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_24			0x0018		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_25			0x0019		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_26			0x001a		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_27			0x001b		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_28			0x001c		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_29			0x001d		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_30			0x001e		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_31			0x001f		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_32			0x0020		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_33			0x0021		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_34			0x0022		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_35			0x0023		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_36			0x0024		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_37			0x0025		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_38			0x0026		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_39			0x0027		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_40			0x0028		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_41			0x0029		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_42			0x002a		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_43			0x002b		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_44			0x002c		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_45			0x002d		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_46			0x002e		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_47			0x002f		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_48			0x0030		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_49			0x0031		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_50			0x0032		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_51			0x0033		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_52			0x0034		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_53			0x0035		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_54			0x0036		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_55			0x0037		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_56			0x0038		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_57			0x0039		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_58			0x003a		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_59			0x003b		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_60			0x003c		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_61			0x003d		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_62			0x003e		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_63			0x003f		//测点数据在推进遥测线路盒遥测帧中位置定义
#define TCB_LOC_64			0x0040		//测点数据在推进遥测线路盒遥测帧中位置定义


//------------------------------------MF51温度源码查询表宏定义------------------------------

#define TABLE_MF51_NEG_50	0x0136		//MF51温度源码查询表，-50摄氏度
#define TABLE_MF51_NEG_49	0x0126		//MF51温度源码查询表，-49摄氏度
#define TABLE_MF51_NEG_48	0x0117		//MF51温度源码查询表，-48摄氏度
#define TABLE_MF51_NEG_47	0x0108		//MF51温度源码查询表，-47摄氏度
#define TABLE_MF51_NEG_46	0x00fb		//MF51温度源码查询表，-46摄氏度
#define TABLE_MF51_NEG_45	0x00ee		//MF51温度源码查询表，-45摄氏度
#define TABLE_MF51_NEG_44	0x00e2		//MF51温度源码查询表，-44摄氏度
#define TABLE_MF51_NEG_43	0x00d6		//MF51温度源码查询表，-43摄氏度
#define TABLE_MF51_NEG_42	0x00cb		//MF51温度源码查询表，-42摄氏度
#define TABLE_MF51_NEG_41	0x00c1		//MF51温度源码查询表，-41摄氏度
#define TABLE_MF51_NEG_40	0x00b7		//MF51温度源码查询表，-40摄氏度
#define TABLE_MF51_NEG_39	0x00ae		//MF51温度源码查询表，-39摄氏度
#define TABLE_MF51_NEG_38	0x00a5		//MF51温度源码查询表，-38摄氏度
#define TABLE_MF51_NEG_37	0x009d		//MF51温度源码查询表，-37摄氏度
#define TABLE_MF51_NEG_36	0x0095		//MF51温度源码查询表，-36摄氏度
#define TABLE_MF51_NEG_35	0x008e		//MF51温度源码查询表，-35摄氏度
#define TABLE_MF51_NEG_34	0x0087		//MF51温度源码查询表，-34摄氏度
#define TABLE_MF51_NEG_33	0x0080		//MF51温度源码查询表，-33摄氏度
#define TABLE_MF51_NEG_32	0x007a		//MF51温度源码查询表，-32摄氏度
#define TABLE_MF51_NEG_31	0x0074		//MF51温度源码查询表，-31摄氏度
#define TABLE_MF51_NEG_30	0x006f		//MF51温度源码查询表，-30摄氏度
#define TABLE_MF51_NEG_29	0x0069		//MF51温度源码查询表，-29摄氏度
#define TABLE_MF51_NEG_28	0x0064		//MF51温度源码查询表，-28摄氏度
#define TABLE_MF51_NEG_27	0x005f		//MF51温度源码查询表，-27摄氏度
#define TABLE_MF51_NEG_26	0x005b		//MF51温度源码查询表，-26摄氏度
#define TABLE_MF51_NEG_25	0x0057		//MF51温度源码查询表，-25摄氏度
#define TABLE_MF51_NEG_24	0x0053		//MF51温度源码查询表，-24摄氏度
#define TABLE_MF51_NEG_23	0x004f		//MF51温度源码查询表，-23摄氏度
#define TABLE_MF51_NEG_22	0x004b		//MF51温度源码查询表，-22摄氏度
#define TABLE_MF51_NEG_21	0x0048		//MF51温度源码查询表，-21摄氏度
#define TABLE_MF51_NEG_20	0x0044		//MF51温度源码查询表，-20摄氏度
#define TABLE_MF51_NEG_19	0x0041		//MF51温度源码查询表，-19摄氏度
#define TABLE_MF51_NEG_18	0x003e		//MF51温度源码查询表，-18摄氏度
#define TABLE_MF51_NEG_17	0x003b		//MF51温度源码查询表，-17摄氏度
#define TABLE_MF51_NEG_16	0x0039		//MF51温度源码查询表，-16摄氏度
#define TABLE_MF51_NEG_15	0x0036		//MF51温度源码查询表，-15摄氏度
#define TABLE_MF51_NEG_14	0x0034		//MF51温度源码查询表，-14摄氏度
#define TABLE_MF51_NEG_13	0x0031		//MF51温度源码查询表，-13摄氏度
#define TABLE_MF51_NEG_12	0x002f		//MF51温度源码查询表，-12摄氏度
#define TABLE_MF51_NEG_11	0x002d		//MF51温度源码查询表，-11摄氏度
#define TABLE_MF51_NEG_10	0x002b		//MF51温度源码查询表，-10摄氏度
#define TABLE_MF51_NEG_09	0x0029		//MF51温度源码查询表，-09摄氏度
#define TABLE_MF51_NEG_08	0x0028		//MF51温度源码查询表，-08摄氏度
#define TABLE_MF51_NEG_07	0x0026		//MF51温度源码查询表，-07摄氏度
#define TABLE_MF51_NEG_06	0x0024		//MF51温度源码查询表，-06摄氏度
#define TABLE_MF51_NEG_05	0x0023		//MF51温度源码查询表，-05摄氏度
#define TABLE_MF51_NEG_04	0x0021		//MF51温度源码查询表，-04摄氏度
#define TABLE_MF51_NEG_03	0x0020		//MF51温度源码查询表，-03摄氏度
#define TABLE_MF51_NEG_02	0x001f		//MF51温度源码查询表，-02摄氏度
#define TABLE_MF51_NEG_01	0x001d		//MF51温度源码查询表，-01摄氏度
#define TABLE_MF51_MID_00	0x001c		//MF51温度源码查询表，-00摄氏度
#define TABLE_MF51_POS_01	0x001b		//MF51温度源码查询表，+01摄氏度
#define TABLE_MF51_POS_02	0x001a		//MF51温度源码查询表，+02摄氏度
#define TABLE_MF51_POS_03	0x0019		//MF51温度源码查询表，+03摄氏度
#define TABLE_MF51_POS_04	0x0018		//MF51温度源码查询表，+04摄氏度
#define TABLE_MF51_POS_05	0x0017		//MF51温度源码查询表，+05摄氏度
#define TABLE_MF51_POS_06	0x0016		//MF51温度源码查询表，+06摄氏度
#define TABLE_MF51_POS_07	0x0015		//MF51温度源码查询表，+07摄氏度
#define TABLE_MF51_POS_08	0x0014		//MF51温度源码查询表，+08摄氏度
#define TABLE_MF51_POS_09	0x0013		//MF51温度源码查询表，+09摄氏度
#define TABLE_MF51_POS_10	0x0013		//MF51温度源码查询表，+10摄氏度
#define TABLE_MF51_POS_11	0x0012		//MF51温度源码查询表，+11摄氏度
#define TABLE_MF51_POS_12	0x0011		//MF51温度源码查询表，+12摄氏度
#define TABLE_MF51_POS_13	0x0011		//MF51温度源码查询表，+13摄氏度
#define TABLE_MF51_POS_14	0x0010		//MF51温度源码查询表，+14摄氏度
#define TABLE_MF51_POS_15	0x000f		//MF51温度源码查询表，+15摄氏度
#define TABLE_MF51_POS_16	0x000f		//MF51温度源码查询表，+16摄氏度
#define TABLE_MF51_POS_17	0x000e		//MF51温度源码查询表，+17摄氏度
#define TABLE_MF51_POS_18	0x000e		//MF51温度源码查询表，+18摄氏度
#define TABLE_MF51_POS_19	0x000d		//MF51温度源码查询表，+19摄氏度
#define TABLE_MF51_POS_20	0x000d		//MF51温度源码查询表，+20摄氏度
#define TABLE_MF51_POS_21	0x000c		//MF51温度源码查询表，+21摄氏度
#define TABLE_MF51_POS_22	0x000c		//MF51温度源码查询表，+22摄氏度
#define TABLE_MF51_POS_23	0x000b		//MF51温度源码查询表，+23摄氏度
#define TABLE_MF51_POS_24	0x000b		//MF51温度源码查询表，+24摄氏度
#define TABLE_MF51_POS_25	0x000b		//MF51温度源码查询表，+25摄氏度
#define TABLE_MF51_POS_26	0x000a		//MF51温度源码查询表，+26摄氏度
#define TABLE_MF51_POS_27	0x000a		//MF51温度源码查询表，+27摄氏度
#define TABLE_MF51_POS_28	0x0009		//MF51温度源码查询表，+28摄氏度
#define TABLE_MF51_POS_29	0x0009		//MF51温度源码查询表，+29摄氏度
#define TABLE_MF51_POS_30	0x0009		//MF51温度源码查询表，+30摄氏度
#define TABLE_MF51_POS_31	0x0008		//MF51温度源码查询表，+31摄氏度
#define TABLE_MF51_POS_32	0x0008		//MF51温度源码查询表，+32摄氏度
#define TABLE_MF51_POS_33	0x0008		//MF51温度源码查询表，+33摄氏度
#define TABLE_MF51_POS_34	0x0008		//MF51温度源码查询表，+34摄氏度
#define TABLE_MF51_POS_35	0x0007		//MF51温度源码查询表，+35摄氏度
#define TABLE_MF51_POS_36	0x0007		//MF51温度源码查询表，+36摄氏度
#define TABLE_MF51_POS_37	0x0007		//MF51温度源码查询表，+37摄氏度
#define TABLE_MF51_POS_38	0x0007		//MF51温度源码查询表，+38摄氏度
#define TABLE_MF51_POS_39	0x0006		//MF51温度源码查询表，+39摄氏度
#define TABLE_MF51_POS_40	0x0006		//MF51温度源码查询表，+40摄氏度
#define TABLE_MF51_POS_41	0x0006		//MF51温度源码查询表，+41摄氏度
#define TABLE_MF51_POS_42	0x0006		//MF51温度源码查询表，+42摄氏度
#define TABLE_MF51_POS_43	0x0006		//MF51温度源码查询表，+43摄氏度
#define TABLE_MF51_POS_44	0x0005		//MF51温度源码查询表，+44摄氏度
#define TABLE_MF51_POS_45	0x0005		//MF51温度源码查询表，+45摄氏度
#define TABLE_MF51_POS_46	0x0005		//MF51温度源码查询表，+46摄氏度
#define TABLE_MF51_POS_47	0x0005		//MF51温度源码查询表，+47摄氏度
#define TABLE_MF51_POS_48	0x0005		//MF51温度源码查询表，+48摄氏度
#define TABLE_MF51_POS_49	0x0005		//MF51温度源码查询表，+49摄氏度
#define TABLE_MF51_POS_50	0x0004		//MF51温度源码查询表，+50摄氏度
#define TABLE_MF51_POS_51	0x0004		//MF51温度源码查询表，+51摄氏度
#define TABLE_MF51_POS_52	0x0004		//MF51温度源码查询表，+52摄氏度
#define TABLE_MF51_POS_53	0x0004		//MF51温度源码查询表，+53摄氏度
#define TABLE_MF51_POS_54	0x0004		//MF51温度源码查询表，+54摄氏度
#define TABLE_MF51_POS_55	0x0004		//MF51温度源码查询表，+55摄氏度
#define TABLE_MF51_POS_56	0x0004		//MF51温度源码查询表，+56摄氏度
#define TABLE_MF51_POS_57	0x0004		//MF51温度源码查询表，+57摄氏度
#define TABLE_MF51_POS_58	0x0003		//MF51温度源码查询表，+58摄氏度
#define TABLE_MF51_POS_59	0x0003		//MF51温度源码查询表，+59摄氏度
#define TABLE_MF51_POS_60	0x0003		//MF51温度源码查询表，+60摄氏度
#define TABLE_MF51_POS_61	0x0003		//MF51温度源码查询表，+61摄氏度
#define TABLE_MF51_POS_62	0x0003		//MF51温度源码查询表，+62摄氏度
#define TABLE_MF51_POS_63	0x0003		//MF51温度源码查询表，+63摄氏度
#define TABLE_MF51_POS_64	0x0003		//MF51温度源码查询表，+64摄氏度
#define TABLE_MF51_POS_65	0x0003		//MF51温度源码查询表，+65摄氏度
#define TABLE_MF51_POS_66	0x0003		//MF51温度源码查询表，+66摄氏度
#define TABLE_MF51_POS_67	0x0003		//MF51温度源码查询表，+67摄氏度
#define TABLE_MF51_POS_68	0x0003		//MF51温度源码查询表，+68摄氏度
#define TABLE_MF51_POS_69	0x0003		//MF51温度源码查询表，+69摄氏度
#define TABLE_MF51_POS_70	0x0002		//MF51温度源码查询表，+70摄氏度



//------------------------------------MF61温度源码查询表宏定义------------------------------

#define TABLE_MF61_NEG_50	0x0e56		//MF61温度源码查询表，-50摄氏度
#define TABLE_MF61_NEG_49	0x0e48		//MF61温度源码查询表，-49摄氏度
#define TABLE_MF61_NEG_48	0x0e3a		//MF61温度源码查询表，-48摄氏度
#define TABLE_MF61_NEG_47	0x0e2b		//MF61温度源码查询表，-47摄氏度
#define TABLE_MF61_NEG_46	0x0e1b		//MF61温度源码查询表，-46摄氏度
#define TABLE_MF61_NEG_45	0x0e0b		//MF61温度源码查询表，-45摄氏度
#define TABLE_MF61_NEG_44	0x0df9		//MF61温度源码查询表，-44摄氏度
#define TABLE_MF61_NEG_43	0x0de7		//MF61温度源码查询表，-43摄氏度
#define TABLE_MF61_NEG_42	0x0dd4		//MF61温度源码查询表，-42摄氏度
#define TABLE_MF61_NEG_41	0x0dc1		//MF61温度源码查询表，-41摄氏度
#define TABLE_MF61_NEG_40	0x0dac		//MF61温度源码查询表，-40摄氏度
#define TABLE_MF61_NEG_39	0x0d97		//MF61温度源码查询表，-39摄氏度
#define TABLE_MF61_NEG_38	0x0d80		//MF61温度源码查询表，-38摄氏度
#define TABLE_MF61_NEG_37	0x0d69		//MF61温度源码查询表，-37摄氏度
#define TABLE_MF61_NEG_36	0x0d51		//MF61温度源码查询表，-36摄氏度
#define TABLE_MF61_NEG_35	0x0d38		//MF61温度源码查询表，-35摄氏度
#define TABLE_MF61_NEG_34	0x0d1e		//MF61温度源码查询表，-34摄氏度
#define TABLE_MF61_NEG_33	0x0d04		//MF61温度源码查询表，-33摄氏度
#define TABLE_MF61_NEG_32	0x0ce8		//MF61温度源码查询表，-32摄氏度
#define TABLE_MF61_NEG_31	0x0ccb		//MF61温度源码查询表，-31摄氏度
#define TABLE_MF61_NEG_30	0x0cae		//MF61温度源码查询表，-30摄氏度
#define TABLE_MF61_NEG_29	0x0c90		//MF61温度源码查询表，-29摄氏度
#define TABLE_MF61_NEG_28	0x0c70		//MF61温度源码查询表，-28摄氏度
#define TABLE_MF61_NEG_27	0x0c50		//MF61温度源码查询表，-27摄氏度
#define TABLE_MF61_NEG_26	0x0c2f		//MF61温度源码查询表，-26摄氏度
#define TABLE_MF61_NEG_25	0x0c0d		//MF61温度源码查询表，-25摄氏度
#define TABLE_MF61_NEG_24	0x0bea		//MF61温度源码查询表，-24摄氏度
#define TABLE_MF61_NEG_23	0x0bc7		//MF61温度源码查询表，-23摄氏度
#define TABLE_MF61_NEG_22	0x0ba2		//MF61温度源码查询表，-22摄氏度
#define TABLE_MF61_NEG_21	0x0b7d		//MF61温度源码查询表，-21摄氏度
#define TABLE_MF61_NEG_20	0x0b57		//MF61温度源码查询表，-20摄氏度
#define TABLE_MF61_NEG_19	0x0b31		//MF61温度源码查询表，-19摄氏度
#define TABLE_MF61_NEG_18	0x0b09		//MF61温度源码查询表，-18摄氏度
#define TABLE_MF61_NEG_17	0x0ae2		//MF61温度源码查询表，-17摄氏度
#define TABLE_MF61_NEG_16	0x0ab9		//MF61温度源码查询表，-16摄氏度
#define TABLE_MF61_NEG_15	0x0a90		//MF61温度源码查询表，-15摄氏度
#define TABLE_MF61_NEG_14	0x0a66		//MF61温度源码查询表，-14摄氏度
#define TABLE_MF61_NEG_13	0x0a3c		//MF61温度源码查询表，-13摄氏度
#define TABLE_MF61_NEG_12	0x0a11		//MF61温度源码查询表，-12摄氏度
#define TABLE_MF61_NEG_11	0x09e6		//MF61温度源码查询表，-11摄氏度
#define TABLE_MF61_NEG_10	0x09bb		//MF61温度源码查询表，-10摄氏度
#define TABLE_MF61_NEG_09	0x098f		//MF61温度源码查询表，-09摄氏度
#define TABLE_MF61_NEG_08	0x0963		//MF61温度源码查询表，-08摄氏度
#define TABLE_MF61_NEG_07	0x0937		//MF61温度源码查询表，-07摄氏度
#define TABLE_MF61_NEG_06	0x090b		//MF61温度源码查询表，-06摄氏度
#define TABLE_MF61_NEG_05	0x08df		//MF61温度源码查询表，-05摄氏度
#define TABLE_MF61_NEG_04	0x08b2		//MF61温度源码查询表，-04摄氏度
#define TABLE_MF61_NEG_03	0x0886		//MF61温度源码查询表，-03摄氏度
#define TABLE_MF61_NEG_02	0x0859		//MF61温度源码查询表，-02摄氏度
#define TABLE_MF61_NEG_01	0x082d		//MF61温度源码查询表，-01摄氏度
#define TABLE_MF61_MID_00	0x0801		//MF61温度源码查询表，-00摄氏度
#define TABLE_MF61_POS_01	0x07d5		//MF61温度源码查询表，+01摄氏度
#define TABLE_MF61_POS_02	0x07a9		//MF61温度源码查询表，+02摄氏度
#define TABLE_MF61_POS_03	0x077e		//MF61温度源码查询表，+03摄氏度
#define TABLE_MF61_POS_04	0x0752		//MF61温度源码查询表，+04摄氏度
#define TABLE_MF61_POS_05	0x0728		//MF61温度源码查询表，+05摄氏度
#define TABLE_MF61_POS_06	0x06fd		//MF61温度源码查询表，+06摄氏度
#define TABLE_MF61_POS_07	0x06d3		//MF61温度源码查询表，+07摄氏度
#define TABLE_MF61_POS_08	0x06a9		//MF61温度源码查询表，+08摄氏度
#define TABLE_MF61_POS_09	0x0680		//MF61温度源码查询表，+09摄氏度
#define TABLE_MF61_POS_10	0x0658		//MF61温度源码查询表，+10摄氏度
#define TABLE_MF61_POS_11	0x0630		//MF61温度源码查询表，+11摄氏度
#define TABLE_MF61_POS_12	0x0608		//MF61温度源码查询表，+12摄氏度
#define TABLE_MF61_POS_13	0x05e1		//MF61温度源码查询表，+13摄氏度
#define TABLE_MF61_POS_14	0x05bb		//MF61温度源码查询表，+14摄氏度
#define TABLE_MF61_POS_15	0x0595		//MF61温度源码查询表，+15摄氏度
#define TABLE_MF61_POS_16	0x0570		//MF61温度源码查询表，+16摄氏度
#define TABLE_MF61_POS_17	0x054c		//MF61温度源码查询表，+17摄氏度
#define TABLE_MF61_POS_18	0x0528		//MF61温度源码查询表，+18摄氏度
#define TABLE_MF61_POS_19	0x0505		//MF61温度源码查询表，+19摄氏度
#define TABLE_MF61_POS_20	0x04e3		//MF61温度源码查询表，+20摄氏度
#define TABLE_MF61_POS_21	0x04c1		//MF61温度源码查询表，+21摄氏度
#define TABLE_MF61_POS_22	0x04a0		//MF61温度源码查询表，+22摄氏度
#define TABLE_MF61_POS_23	0x0480		//MF61温度源码查询表，+23摄氏度
#define TABLE_MF61_POS_24	0x0460		//MF61温度源码查询表，+24摄氏度
#define TABLE_MF61_POS_25	0x0441		//MF61温度源码查询表，+25摄氏度
#define TABLE_MF61_POS_26	0x0423		//MF61温度源码查询表，+26摄氏度
#define TABLE_MF61_POS_27	0x0406		//MF61温度源码查询表，+27摄氏度
#define TABLE_MF61_POS_28	0x03e9		//MF61温度源码查询表，+28摄氏度
#define TABLE_MF61_POS_29	0x03cd		//MF61温度源码查询表，+29摄氏度
#define TABLE_MF61_POS_30	0x03b2		//MF61温度源码查询表，+30摄氏度
#define TABLE_MF61_POS_31	0x0397		//MF61温度源码查询表，+31摄氏度
#define TABLE_MF61_POS_32	0x037d		//MF61温度源码查询表，+32摄氏度
#define TABLE_MF61_POS_33	0x0364		//MF61温度源码查询表，+33摄氏度
#define TABLE_MF61_POS_34	0x034b		//MF61温度源码查询表，+34摄氏度
#define TABLE_MF61_POS_35	0x0333		//MF61温度源码查询表，+35摄氏度
#define TABLE_MF61_POS_36	0x031c		//MF61温度源码查询表，+36摄氏度
#define TABLE_MF61_POS_37	0x0305		//MF61温度源码查询表，+37摄氏度
#define TABLE_MF61_POS_38	0x02ef		//MF61温度源码查询表，+38摄氏度
#define TABLE_MF61_POS_39	0x02d9		//MF61温度源码查询表，+39摄氏度
#define TABLE_MF61_POS_40	0x02c4		//MF61温度源码查询表，+40摄氏度
#define TABLE_MF61_POS_41	0x02b0		//MF61温度源码查询表，+41摄氏度
#define TABLE_MF61_POS_42	0x029c		//MF61温度源码查询表，+42摄氏度
#define TABLE_MF61_POS_43	0x0289		//MF61温度源码查询表，+43摄氏度
#define TABLE_MF61_POS_44	0x0276		//MF61温度源码查询表，+44摄氏度
#define TABLE_MF61_POS_45	0x0264		//MF61温度源码查询表，+45摄氏度
#define TABLE_MF61_POS_46	0x0253		//MF61温度源码查询表，+46摄氏度
#define TABLE_MF61_POS_47	0x0242		//MF61温度源码查询表，+47摄氏度
#define TABLE_MF61_POS_48	0x0231		//MF61温度源码查询表，+48摄氏度
#define TABLE_MF61_POS_49	0x0221		//MF61温度源码查询表，+49摄氏度
#define TABLE_MF61_POS_50	0x0211		//MF61温度源码查询表，+50摄氏度
#define TABLE_MF61_POS_51	0x0202		//MF61温度源码查询表，+51摄氏度
#define TABLE_MF61_POS_52	0x01f4		//MF61温度源码查询表，+52摄氏度
#define TABLE_MF61_POS_53	0x01e5		//MF61温度源码查询表，+53摄氏度
#define TABLE_MF61_POS_54	0x01d8		//MF61温度源码查询表，+54摄氏度
#define TABLE_MF61_POS_55	0x01ca		//MF61温度源码查询表，+55摄氏度
#define TABLE_MF61_POS_56	0x01bd		//MF61温度源码查询表，+56摄氏度
#define TABLE_MF61_POS_57	0x01b0		//MF61温度源码查询表，+57摄氏度
#define TABLE_MF61_POS_58	0x01a4		//MF61温度源码查询表，+58摄氏度
#define TABLE_MF61_POS_59	0x0198		//MF61温度源码查询表，+59摄氏度
#define TABLE_MF61_POS_60	0x018d		//MF61温度源码查询表，+60摄氏度
#define TABLE_MF61_POS_61	0x0182		//MF61温度源码查询表，+61摄氏度
#define TABLE_MF61_POS_62	0x0177		//MF61温度源码查询表，+62摄氏度
#define TABLE_MF61_POS_63	0x016c		//MF61温度源码查询表，+63摄氏度
#define TABLE_MF61_POS_64	0x0162		//MF61温度源码查询表，+64摄氏度
#define TABLE_MF61_POS_65	0x0158		//MF61温度源码查询表，+65摄氏度
#define TABLE_MF61_POS_66	0x014f		//MF61温度源码查询表，+66摄氏度
#define TABLE_MF61_POS_67	0x0146		//MF61温度源码查询表，+67摄氏度
#define TABLE_MF61_POS_68	0x013d		//MF61温度源码查询表，+68摄氏度
#define TABLE_MF61_POS_69	0x0134		//MF61温度源码查询表，+69摄氏度
#define TABLE_MF61_POS_70	0x012b		//MF61温度源码查询表，+70摄氏度



//------------------------------------铂电阻温度源码查询表宏定义------------------------------

#define TABLE_PT_NEG_50		0x045c		//铂电阻温度源码查询表，-50摄氏度
#define TABLE_PT_NEG_49		0x045f		//铂电阻温度源码查询表，-49摄氏度
#define TABLE_PT_NEG_48		0x0463		//铂电阻温度源码查询表，-48摄氏度
#define TABLE_PT_NEG_47		0x0467		//铂电阻温度源码查询表，-47摄氏度
#define TABLE_PT_NEG_46		0x046b		//铂电阻温度源码查询表，-46摄氏度
#define TABLE_PT_NEG_45		0x046f		//铂电阻温度源码查询表，-45摄氏度
#define TABLE_PT_NEG_44		0x0473		//铂电阻温度源码查询表，-44摄氏度
#define TABLE_PT_NEG_43		0x0476		//铂电阻温度源码查询表，-43摄氏度
#define TABLE_PT_NEG_42		0x047a		//铂电阻温度源码查询表，-42摄氏度
#define TABLE_PT_NEG_41		0x047e		//铂电阻温度源码查询表，-41摄氏度
#define TABLE_PT_NEG_40		0x0482		//铂电阻温度源码查询表，-40摄氏度
#define TABLE_PT_NEG_39		0x0485		//铂电阻温度源码查询表，-39摄氏度
#define TABLE_PT_NEG_38		0x0489		//铂电阻温度源码查询表，-38摄氏度
#define TABLE_PT_NEG_37		0x048d		//铂电阻温度源码查询表，-37摄氏度
#define TABLE_PT_NEG_36		0x0491		//铂电阻温度源码查询表，-36摄氏度
#define TABLE_PT_NEG_35		0x0494		//铂电阻温度源码查询表，-35摄氏度
#define TABLE_PT_NEG_34		0x0498		//铂电阻温度源码查询表，-34摄氏度
#define TABLE_PT_NEG_33		0x049c		//铂电阻温度源码查询表，-33摄氏度
#define TABLE_PT_NEG_32		0x049f		//铂电阻温度源码查询表，-32摄氏度
#define TABLE_PT_NEG_31		0x04a3		//铂电阻温度源码查询表，-31摄氏度
#define TABLE_PT_NEG_30		0x04a7		//铂电阻温度源码查询表，-30摄氏度
#define TABLE_PT_NEG_29		0x04aa		//铂电阻温度源码查询表，-29摄氏度
#define TABLE_PT_NEG_28		0x04ae		//铂电阻温度源码查询表，-28摄氏度
#define TABLE_PT_NEG_27		0x04b1		//铂电阻温度源码查询表，-27摄氏度
#define TABLE_PT_NEG_26		0x04b5		//铂电阻温度源码查询表，-26摄氏度
#define TABLE_PT_NEG_25		0x04b9		//铂电阻温度源码查询表，-25摄氏度
#define TABLE_PT_NEG_24		0x04bc		//铂电阻温度源码查询表，-24摄氏度
#define TABLE_PT_NEG_23		0x04c0		//铂电阻温度源码查询表，-23摄氏度
#define TABLE_PT_NEG_22		0x04c3		//铂电阻温度源码查询表，-22摄氏度
#define TABLE_PT_NEG_21		0x04c7		//铂电阻温度源码查询表，-21摄氏度
#define TABLE_PT_NEG_20		0x04cb		//铂电阻温度源码查询表，-20摄氏度
#define TABLE_PT_NEG_19		0x04ce		//铂电阻温度源码查询表，-19摄氏度
#define TABLE_PT_NEG_18		0x04d2		//铂电阻温度源码查询表，-18摄氏度
#define TABLE_PT_NEG_17		0x04d5		//铂电阻温度源码查询表，-17摄氏度
#define TABLE_PT_NEG_16		0x04d9		//铂电阻温度源码查询表，-16摄氏度
#define TABLE_PT_NEG_15		0x04dc		//铂电阻温度源码查询表，-15摄氏度
#define TABLE_PT_NEG_14		0x04e0		//铂电阻温度源码查询表，-14摄氏度
#define TABLE_PT_NEG_13		0x04e3		//铂电阻温度源码查询表，-13摄氏度
#define TABLE_PT_NEG_12		0x04e7		//铂电阻温度源码查询表，-12摄氏度
#define TABLE_PT_NEG_11		0x04ea		//铂电阻温度源码查询表，-11摄氏度
#define TABLE_PT_NEG_10		0x04ee		//铂电阻温度源码查询表，-10摄氏度
#define TABLE_PT_NEG_09		0x04f1		//铂电阻温度源码查询表，-09摄氏度
#define TABLE_PT_NEG_08		0x04f5		//铂电阻温度源码查询表，-08摄氏度
#define TABLE_PT_NEG_07		0x04f8		//铂电阻温度源码查询表，-07摄氏度
#define TABLE_PT_NEG_06		0x04fb		//铂电阻温度源码查询表，-06摄氏度
#define TABLE_PT_NEG_05		0x04ff		//铂电阻温度源码查询表，-05摄氏度
#define TABLE_PT_NEG_04		0x0502		//铂电阻温度源码查询表，-04摄氏度
#define TABLE_PT_NEG_03		0x0506		//铂电阻温度源码查询表，-03摄氏度
#define TABLE_PT_NEG_02		0x0509		//铂电阻温度源码查询表，-02摄氏度
#define TABLE_PT_NEG_01		0x050c		//铂电阻温度源码查询表，-01摄氏度
#define TABLE_PT_MID_00		0x0510		//铂电阻温度源码查询表，-00摄氏度
#define TABLE_PT_POS_01		0x0513		//铂电阻温度源码查询表，+01摄氏度
#define TABLE_PT_POS_02		0x0516		//铂电阻温度源码查询表，+02摄氏度
#define TABLE_PT_POS_03		0x051a		//铂电阻温度源码查询表，+03摄氏度
#define TABLE_PT_POS_04		0x051d		//铂电阻温度源码查询表，+04摄氏度
#define TABLE_PT_POS_05		0x0521		//铂电阻温度源码查询表，+05摄氏度
#define TABLE_PT_POS_06		0x0524		//铂电阻温度源码查询表，+06摄氏度
#define TABLE_PT_POS_07		0x0527		//铂电阻温度源码查询表，+07摄氏度
#define TABLE_PT_POS_08		0x052a		//铂电阻温度源码查询表，+08摄氏度
#define TABLE_PT_POS_09		0x052e		//铂电阻温度源码查询表，+09摄氏度
#define TABLE_PT_POS_10		0x0531		//铂电阻温度源码查询表，+10摄氏度
#define TABLE_PT_POS_11		0x0534		//铂电阻温度源码查询表，+11摄氏度
#define TABLE_PT_POS_12		0x0538		//铂电阻温度源码查询表，+12摄氏度
#define TABLE_PT_POS_13		0x053b		//铂电阻温度源码查询表，+13摄氏度
#define TABLE_PT_POS_14		0x053e		//铂电阻温度源码查询表，+14摄氏度
#define TABLE_PT_POS_15		0x0541		//铂电阻温度源码查询表，+15摄氏度
#define TABLE_PT_POS_16		0x0545		//铂电阻温度源码查询表，+16摄氏度
#define TABLE_PT_POS_17		0x0548		//铂电阻温度源码查询表，+17摄氏度
#define TABLE_PT_POS_18		0x054b		//铂电阻温度源码查询表，+18摄氏度
#define TABLE_PT_POS_19		0x054e		//铂电阻温度源码查询表，+19摄氏度
#define TABLE_PT_POS_20		0x0551		//铂电阻温度源码查询表，+20摄氏度
#define TABLE_PT_POS_21		0x0555		//铂电阻温度源码查询表，+21摄氏度
#define TABLE_PT_POS_22		0x0558		//铂电阻温度源码查询表，+22摄氏度
#define TABLE_PT_POS_23		0x055b		//铂电阻温度源码查询表，+23摄氏度
#define TABLE_PT_POS_24		0x055e		//铂电阻温度源码查询表，+24摄氏度
#define TABLE_PT_POS_25		0x0561		//铂电阻温度源码查询表，+25摄氏度
#define TABLE_PT_POS_26		0x0564		//铂电阻温度源码查询表，+26摄氏度
#define TABLE_PT_POS_27		0x0568		//铂电阻温度源码查询表，+27摄氏度
#define TABLE_PT_POS_28		0x056b		//铂电阻温度源码查询表，+28摄氏度
#define TABLE_PT_POS_29		0x056e		//铂电阻温度源码查询表，+29摄氏度
#define TABLE_PT_POS_30		0x0571		//铂电阻温度源码查询表，+30摄氏度
#define TABLE_PT_POS_31		0x0574		//铂电阻温度源码查询表，+31摄氏度
#define TABLE_PT_POS_32		0x0577		//铂电阻温度源码查询表，+32摄氏度
#define TABLE_PT_POS_33		0x057a		//铂电阻温度源码查询表，+33摄氏度
#define TABLE_PT_POS_34		0x057d		//铂电阻温度源码查询表，+34摄氏度
#define TABLE_PT_POS_35		0x0581		//铂电阻温度源码查询表，+35摄氏度
#define TABLE_PT_POS_36		0x0584		//铂电阻温度源码查询表，+36摄氏度
#define TABLE_PT_POS_37		0x0587		//铂电阻温度源码查询表，+37摄氏度
#define TABLE_PT_POS_38		0x058a		//铂电阻温度源码查询表，+38摄氏度
#define TABLE_PT_POS_39		0x058d		//铂电阻温度源码查询表，+39摄氏度
#define TABLE_PT_POS_40		0x0590		//铂电阻温度源码查询表，+40摄氏度
#define TABLE_PT_POS_41		0x0593		//铂电阻温度源码查询表，+41摄氏度
#define TABLE_PT_POS_42		0x0596		//铂电阻温度源码查询表，+42摄氏度
#define TABLE_PT_POS_43		0x0599		//铂电阻温度源码查询表，+43摄氏度
#define TABLE_PT_POS_44		0x059c		//铂电阻温度源码查询表，+44摄氏度
#define TABLE_PT_POS_45		0x059f		//铂电阻温度源码查询表，+45摄氏度
#define TABLE_PT_POS_46		0x05a2		//铂电阻温度源码查询表，+46摄氏度
#define TABLE_PT_POS_47		0x05a5		//铂电阻温度源码查询表，+47摄氏度
#define TABLE_PT_POS_48		0x05a8		//铂电阻温度源码查询表，+48摄氏度
#define TABLE_PT_POS_49		0x05ab		//铂电阻温度源码查询表，+49摄氏度
#define TABLE_PT_POS_50		0x05ae		//铂电阻温度源码查询表，+50摄氏度
#define TABLE_PT_POS_51		0x05b1		//铂电阻温度源码查询表，+51摄氏度
#define TABLE_PT_POS_52		0x05b4		//铂电阻温度源码查询表，+52摄氏度
#define TABLE_PT_POS_53		0x05b7		//铂电阻温度源码查询表，+53摄氏度
#define TABLE_PT_POS_54		0x05ba		//铂电阻温度源码查询表，+54摄氏度
#define TABLE_PT_POS_55		0x05bd		//铂电阻温度源码查询表，+55摄氏度
#define TABLE_PT_POS_56		0x05c0		//铂电阻温度源码查询表，+56摄氏度
#define TABLE_PT_POS_57		0x05c3		//铂电阻温度源码查询表，+57摄氏度
#define TABLE_PT_POS_58		0x05c5		//铂电阻温度源码查询表，+58摄氏度
#define TABLE_PT_POS_59		0x05c8		//铂电阻温度源码查询表，+59摄氏度
#define TABLE_PT_POS_60		0x05cb		//铂电阻温度源码查询表，+60摄氏度
#define TABLE_PT_POS_61		0x05ce		//铂电阻温度源码查询表，+61摄氏度
#define TABLE_PT_POS_62		0x05d1		//铂电阻温度源码查询表，+62摄氏度
#define TABLE_PT_POS_63		0x05d4		//铂电阻温度源码查询表，+63摄氏度
#define TABLE_PT_POS_64		0x05d7		//铂电阻温度源码查询表，+64摄氏度
#define TABLE_PT_POS_65		0x05da		//铂电阻温度源码查询表，+65摄氏度
#define TABLE_PT_POS_66		0x05dd		//铂电阻温度源码查询表，+66摄氏度
#define TABLE_PT_POS_67		0x05df		//铂电阻温度源码查询表，+67摄氏度
#define TABLE_PT_POS_68		0x05e2		//铂电阻温度源码查询表，+68摄氏度
#define TABLE_PT_POS_69		0x05e5		//铂电阻温度源码查询表，+69摄氏度
#define TABLE_PT_POS_70		0x05e8		//铂电阻温度源码查询表，+70摄氏度





#define TEMP_MF51_NEG_50 	TABLE_MF51_NEG_50//MF51,-50摄氏度对应源码值
#define TEMP_MF51_NEG_40	TABLE_MF51_NEG_40//MF51,-40摄氏度对应源码值
#define TEMP_MF51_NEG_30	TABLE_MF51_NEG_30//MF51,-30摄氏度对应源码值
#define TEMP_MF51_NEG_20	TABLE_MF51_NEG_20//MF51,-20摄氏度对应源码值
#define TEMP_MF51_NEG_10	TABLE_MF51_NEG_10//MF51,-10摄氏度对应源码值
#define TEMP_MF51_MID_0		TABLE_MF51_MID_00//MF51,0摄氏度对应源码值
#define TEMP_MF51_POS_10	TABLE_MF51_POS_10//MF51,10摄氏度对应源码值
#define TEMP_MF51_POS_20	TABLE_MF51_POS_20//MF51,20摄氏度对应源码值
#define TEMP_MF51_POS_30	TABLE_MF51_POS_30//MF51,30摄氏度对应源码值
#define TEMP_MF51_POS_40	TABLE_MF51_POS_40//MF51,40摄氏度对应源码值
#define TEMP_MF51_POS_50	TABLE_MF51_POS_50//MF51,50摄氏度对应源码值
#define TEMP_MF51_POS_60	TABLE_MF51_POS_60//MF51,60摄氏度对应源码值
#define TEMP_MF51_POS_70	TABLE_MF51_POS_70//MF51,70摄氏度对应源码值


#define TEMP_MF61_NEG_50 	TABLE_MF61_NEG_50//MF61,-50摄氏度对应源码值
#define TEMP_MF61_NEG_40	TABLE_MF61_NEG_40//MF61,-40摄氏度对应源码值
#define TEMP_MF61_NEG_30	TABLE_MF61_NEG_30//MF61,-30摄氏度对应源码值
#define TEMP_MF61_NEG_20	TABLE_MF61_NEG_20//MF61,-20摄氏度对应源码值
#define TEMP_MF61_NEG_10	TABLE_MF61_NEG_10//MF61,-10摄氏度对应源码值
#define TEMP_MF61_MID_0		TABLE_MF61_MID_00//MF61,0摄氏度对应源码值
#define TEMP_MF61_POS_10	TABLE_MF61_POS_10//MF61,10摄氏度对应源码值
#define TEMP_MF61_POS_20	TABLE_MF61_POS_20//MF61,20摄氏度对应源码值
#define TEMP_MF61_POS_30	TABLE_MF61_POS_30//MF61,30摄氏度对应源码值
#define TEMP_MF61_POS_40	TABLE_MF61_POS_40//MF61,40摄氏度对应源码值
#define TEMP_MF61_POS_50	TABLE_MF61_POS_50//MF61,50摄氏度对应源码值
#define TEMP_MF61_POS_60	TABLE_MF61_POS_60//MF61,60摄氏度对应源码值
#define TEMP_MF61_POS_70	TABLE_MF61_POS_70//MF61,70摄氏度对应源码值


#define TEMP_PT_NEG_50 		TABLE_PT_NEG_50//铂电阻,-50摄氏度对应源码值
#define TEMP_PT_NEG_40		TABLE_PT_NEG_40//铂电阻,-40摄氏度对应源码值
#define TEMP_PT_NEG_30		TABLE_PT_NEG_30//铂电阻,-30摄氏度对应源码值
#define TEMP_PT_NEG_20		TABLE_PT_NEG_20//铂电阻,-20摄氏度对应源码值
#define TEMP_PT_NEG_10		TABLE_PT_NEG_10//铂电阻,-10摄氏度对应源码值
#define TEMP_PT_MID_0		TABLE_PT_MID_00//铂电阻,0摄氏度对应源码值
#define TEMP_PT_POS_10		TABLE_PT_POS_10//铂电阻,10摄氏度对应源码值
#define TEMP_PT_POS_20		TABLE_PT_POS_20//铂电阻,20摄氏度对应源码值
#define TEMP_PT_POS_30		TABLE_PT_POS_30//铂电阻,30摄氏度对应源码值
#define TEMP_PT_POS_40		TABLE_PT_POS_40//铂电阻,40摄氏度对应源码值
#define TEMP_PT_POS_50		TABLE_PT_POS_50//铂电阻,50摄氏度对应源码值
#define TEMP_PT_POS_60		TABLE_PT_POS_60//铂电阻,60摄氏度对应源码值
#define TEMP_PT_POS_70		TABLE_PT_POS_70//铂电阻,70摄氏度对应源码值



/*函数声明--------------------------------------------------------------------*/

void TGTHT510_tempercontrol_initial(void);
uint16 TGTHT510_tempercontrol_mf51_to_mf61(uint16 temp_mf51);
uint16 TGTHT510_tempercontrol_mf51_range_calculate(uint16 temp_mf51);
uint16 TGTHT510_tempercontrol_mf51_sourcecode_to_centigrade_calculate(uint16 temp_mf51,uint16 range);
uint16 TGTHT510_tempercontrol_mf51_centigrade_num_calculate(uint16 start_i,uint16 temp_mf51);
uint16 TGTHT510_tempercontrol_pt_to_mf61(uint16 temp_pt);
uint16 TGTHT510_tempercontrol_pt_range_calculate(uint16 temp_pt);
uint16 TGTHT510_tempercontrol_pt_centigrade_num_calculate(uint16 start_i,uint16 temp_pt);
uint16 TGTHT510_tempercontrol_pt_sourcecode_to_centigrade_calculate(uint16 temp_pt,uint16 range);
void TGTHT510_tempercontrol_valid_data_generate(uint16 type);
void TGTHT510_tempercontrol_valid_data_from_TGTHT100(void);
void TGTHT510_tempercontrol_valid_data_from_TGTHT100_fixed_control(uint16 num);
void TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control(uint16 num);
Temperature_control_temp_TypeDef TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control_source_data(uint16 num);
uint16 TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control_source_data_sort(Temperature_control_temp_TypeDef d);
void TGTHT510_tempercontrol_valid_data_from_TGTHT100_sort(void);
void TGTHT510_tempercontrol_reg_output(void);
void TGTHT510_tempercontrol_reg_setbit(uint16 num,uint16 type);
void TGTHT510_tempercontrol_reg_clear(void);
uint16 TGTHT510_tempercontrol_power_calculate(uint16 num,uint16 type);
uint16 TGTHT510_tempercontrol_9s_flag(void);
void TGTHT510_tempercontrol_main(void);
uint16 TGTHT510_tempercontrol_fixed_control_count_update(void);
uint16 TGTHT510_tempercontrol_fixed_control(uint16 max_power);
uint16 TGTHT510_tempercontrol_auto_control(uint16 max_power);
uint16 TGTHT510_tempercontrol_auto_control_temper_range(uint16 num,uint16 temper);
void TGTHT510_tempercontrol_supply_is_auto_control(uint16 mode);



#endif 
  















  
  
  
