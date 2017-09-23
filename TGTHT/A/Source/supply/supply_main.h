/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器补加流程主程序头文件
  ******************************************************************************
  */
 
#ifndef __supply_main_h
#define __supply_main_h
 

/*声明结构体类型--------------------------------------------------------------*/

typedef struct
{
	uint16 compressor_A_state;//压气机A运行状态，COMPRESSOR_RUN或者COMPRESSOR_STOP
	uint16 compressor_B_state;//压气机B运行状态，COMPRESSOR_RUN或者COMPRESSOR_STOP
	uint16 compressor_C_state;//压气机C运行状态，COMPRESSOR_RUN或者COMPRESSOR_STOP
	
}compressor_state_TypeDef;//压气机工作运行状态结构体

typedef struct
{
	uint16	mode;					//补加模式
	uint16	state;					//补加运行状态，运行、暂停、中止、空闲

	uint16 	stage;					//补加阶段
	uint16 	step;					//处理步骤
	uint16 	command;				//指令
	
	uint16	receive;				//注入参数接受状态
	uint16 	leak_flag;				//检漏排气注入指令标志
	
	uint16 	errno;					//故障代码
	uint16	step_temp;				//缓存处理步骤
	uint16	command_temp;			//缓存指令
	
}TGTHT510_supply_ctrl_TypeDef;		//补加流程内部控制参数

typedef struct
{
//注入补加参数，变化-----------------------------------------------------------
	
	uint8	interface_F;			//燃补加接口
	uint8	interface_O;			//氧补加接口
	
	uint8	sequence_tank_F;		//燃贮箱补加顺序
	uint8	sequence_tank_O;		//氧贮箱补加顺序
	
	uint8	sequence_gas_F1;		//燃贮箱F1气瓶抽气顺序
	uint8	sequence_gas_F2;		//燃贮箱F2气瓶抽气顺序
	uint8	sequence_gas_F3;		//燃贮箱F3气瓶抽气顺序
	
	uint8	sequence_gas_O1;		//氧贮箱O1气瓶抽气顺序
	uint8	sequence_gas_O2;		//氧贮箱O2气瓶抽气顺序
	uint8	sequence_gas_O3;		//氧贮箱O3气瓶抽气顺序
	
	uint16  compressor_out_valve;	//抽气压气机号，与开启的压气机出口阀门
	
	uint16	pressure_first_F1;		//燃贮箱F1第一个抽气贮箱末压
	uint16 	pressure_second_F1;		//燃贮箱F1第二个抽气贮箱末压
	
	uint16	pressure_first_F2;		//燃贮箱F2第一个抽气贮箱末压
	uint16 	pressure_second_F2;		//燃贮箱F2第二个抽气贮箱末压
	
	uint16	pressure_first_F3;		//燃贮箱F3第一个抽气贮箱末压
	uint16 	pressure_second_F3;		//燃贮箱F3第二个抽气贮箱末压
	
	uint16	pressure_first_O1;		//氧贮箱O1第一个抽气贮箱末压
	uint16 	pressure_second_O1;		//氧贮箱O1第二个抽气贮箱末压
	
	uint16	pressure_first_O2;		//氧贮箱O2第一个抽气贮箱末压
	uint16 	pressure_second_O2;		//氧贮箱O2第二个抽气贮箱末压
	
	uint16	pressure_first_O3;		//氧贮箱O3第一个抽气贮箱末压
	uint16 	pressure_second_O3;		//氧贮箱O3第二个抽气贮箱末压
	
	uint16	pump_cooler;			//使用的液冷模块泵号
	
	uint16	volum_F1;				//燃贮箱F1补加到位剩余量
	uint16	volum_F2;				//燃贮箱F2补加到位剩余量
	uint16	volum_F3;				//燃贮箱F3补加到位剩余量
	
	uint16	volum_O1;				//氧贮箱O1补加到位剩余量
	uint16	volum_O2;				//氧贮箱O2补加到位剩余量
	uint16	volum_O3;				//氧贮箱O3补加到位剩余量
	
	uint16	mode;					//补加模式
	
	uint16 	pressure_repre_F1;		//燃贮箱F1复压压力值
	uint16 	pressure_repre_F2;		//燃贮箱F2复压压力值
	uint16 	pressure_repre_F3;		//燃贮箱F3复压压力值
	
	uint16 	pressure_repre_O1;		//氧贮箱O1复压压力值
	uint16 	pressure_repre_O2;		//氧贮箱O2复压压力值
	uint16 	pressure_repre_O3;		//氧贮箱O3复压压力值

//注入补加参数，固定-----------------------------------------------------------
	
	uint32	time_exhaust;			//检漏气体排放时间
	uint32	time_comp_max;			//最大抽气时间
	uint16	velocity_max;			//最大补加速率
	uint16	velocity_min;			//最小补加速率
	uint16 	time_flow_max;			//最大补加流动时间
	uint16	temperature_mode;		//补加管路控温模式
	uint16	temperature_start_min;	//压气机启动温度下限
	uint16	temperature_start_max;	//压气机启动温度上限
	uint16	temperature_alarm;		//压气机报警温度
	uint16	temperature_comp_cooler;//压气机与液冷温度差值
	uint16	pressure_comp_out;		//压气机正常出口压力
	uint16	pressure_comp_out_stop;	//压气机停机后出口压力
	uint16	dp_high;				//高压压力的变化幅值
	uint16	dp1_low;				//低压压力的变化幅值1
	uint16	dp2_low;				//低压压力的变化幅值2
	uint32	time_repre_max;			//最长复压时间
	uint16	v_comp_start;			//压气机启动转速
	uint16	v_comp_stop;			//压气机停机转速
	uint16	time_delay_short;		//短延时
	uint16	time_delay_long;		//长延时
	uint16	time_bypath;			//旁路阀开启时间
	uint16	eps1;					//偏差1
	uint16	eps2;					//偏差2
	uint16	pressure_comp_in_max;	//压气机最大进口压力
	uint16	pressure_comp_in_min;	//压气机最小进口压力
	uint16	pressure_comp_out_min;	//压气机最小出口压力
	uint16	pressure_hyc;			//货运飞船额定增压压力
	
	uint16	sensor_pipe_F;			//燃补加液路压力传感器设定
	uint16	sensor_pipe_O;			//氧补加液路压力传感器设定
	
	uint16	sensor_tank_F;			//燃贮箱压力传感器设定
	uint16	sensor_tank_O;			//氧贮箱压力传感器设定
	
	uint16	sensor_comp_in;			//压气机进口压力传感器设定
	uint16	sensor_pipe_low;		//低压气路压力传感器设定

	
}TGTHT510_supply_input_par_TypeDef;


typedef struct
{
	uint16 		interface_F;			//燃补加接口
	uint16		interface_O;			//氧补加接口
	
	uint16		number_tank_F;			//补加的燃贮箱个数
	uint16		first_tank_F;			//第一个补加的燃贮箱
	uint16		second_tank_F;			//第二个补加的燃贮箱
	uint16		third_tank_F;			//第三个补加的燃贮箱
	
	uint16		number_tank_O;			//补加的氧贮箱个数
	uint16		first_tank_O;			//第一个补加的氧贮箱
	uint16		second_tank_O;			//第二个补加的氧贮箱
	uint16		third_tank_O;			//第三个补加的氧贮箱
	
	uint16		number_gas_tank_F1;		//燃贮箱F1抽气气瓶个数
	uint16		first_gas_tank_F1;		//燃贮箱F1第一个抽气气瓶
	uint16		second_gas_tank_F1;		//燃贮箱F1第二个抽气气瓶
	
	uint16		number_gas_tank_F2;		//燃贮箱F2抽气气瓶个数
	uint16		first_gas_tank_F2;		//燃贮箱F2第一个抽气气瓶
	uint16		second_gas_tank_F2;		//燃贮箱F2第二个抽气气瓶
	
	uint16		number_gas_tank_F3;		//燃贮箱F3抽气气瓶个数
	uint16		first_gas_tank_F3;		//燃贮箱F3第一个抽气气瓶
	uint16		second_gas_tank_F3;		//燃贮箱F3第二个抽气气瓶
	
	uint16		number_gas_tank_O1;		//氧贮箱O1抽气气瓶个数
	uint16		first_gas_tank_O1;		//氧贮箱O1第一个抽气气瓶
	uint16		second_gas_tank_O1;		//氧贮箱O1第二个抽气气瓶
	
	uint16		number_gas_tank_O2;		//氧贮箱O2抽气气瓶个数
	uint16		first_gas_tank_O2;		//氧贮箱O2第一个抽气气瓶
	uint16		second_gas_tank_O2;		//氧贮箱O2第二个抽气气瓶
	
	uint16		number_gas_tank_O3;		//氧贮箱O3抽气气瓶个数
	uint16		first_gas_tank_O3;		//氧贮箱O3第一个抽气气瓶
	uint16		second_gas_tank_O3;		//氧贮箱O3第二个抽气气瓶
	
	uint16		compressor_F;			//燃抽气压气机号
	uint16		compressor_O;			//氧抽气压气机号
	
	uint16		valve_out_compressor_F;	//燃压气机出口阀门
	uint16		valve_out_compressor_O;	//燃压气机出口阀门
	
	uint16 		sensor_tank_F1;			//燃贮箱F1压力传感器设定
	uint16 		sensor_tank_F2;			//燃贮箱F2压力传感器设定
	uint16 		sensor_tank_F3;			//燃贮箱F3压力传感器设定
	uint16 		sensor_tank_O1;			//燃贮箱O1压力传感器设定
	uint16 		sensor_tank_O2;			//燃贮箱O2压力传感器设定
	uint16 		sensor_tank_O3;			//燃贮箱O3压力传感器设定
	
	uint16		sensor_pipe_low_F;		//燃路低压气路压力传感器设定
	uint16		sensor_pipe_low_O;		//氧路低压气路压力传感器设定
	
	uint16		sensor_in_compressor_F; //燃压气机进口压力传感器设定
	uint16		sensor_in_compressor_O; //氧压气机进口压力传感器设定
	
	uint16		cooler;					//液冷模块泵号

}TGTHT510_supply_decode_par_TypeDef;


typedef struct
{
	uint32	time_stage;//补加阶段计时
	
	uint16	time_stage_flag;//TRUE计时，FALSE停止
	
	uint32	time_step;//补加步骤计时
	
	uint16	time_step_flag;//TRUE计时，FALSE停止
	
}TGTHT510_supply_time_TypeDef;		//补加流程内部控制参数


/*宏定义---------------------------------------------------------------------------*/

//故障代码

#define		ERRNO_NONE							0x0000//无故障代码
#define		ERRNO_SUPPLY_VALVE_POWER_ON			0x0101//补加系统阀门加电异常
#define		ERRNO_SUPPLY_VALVE_OFF				0x0202//补加系统阀门关闭异常
#define		ERRNO_SUPPLY_VALVE_ON				0x0303//补加系统阀门打开异常
#define		ERRNO_TUIJIN_VALVE_OFF				0x0404//推进系统阀门关闭异常
#define		ERRNO_TUIJIN_VALVE_ON				0x0505//推进系统阀门打开异常
#define		ERRNO_FUNCTION_INPUT_ERROR			0x0606//内部函数输入参数错误
#define		ERRNO_INPUT_PAR_DECODE				0x0707//补加注入参数解码错误
#define		ERRNO_COOLER_WORK					0x0808//液冷泵转速状态异常
#define		ERRNO_TEMPER_COOLER_TO_COMPRESSOR	0x0909//液冷对压气机的冷却状态异常
#define		ERRNO_COMPRESSOR_TEMPERATURE		0x0a0a//压气机测定温度异常
#define		ERRNO_TANK_VALVE_ON_PRESSURE		0x0b0b//通过压力判断贮箱阀门开启异常
#define		ERRNO_IN_COMPRESSOR_PRESSURE		0x0c0c//压气机进口压力异常
#define		ERRNO_OUT_COMPRESSOR_PRESSURE		0x0d0d//压气机出口压力异常
#define		ERRNO_GAS_PRESSURE					0x0e0e//气瓶压力升高异常
#define		ERRNO_ISOLATION						0x0f0f//高压气路隔离异常
#define		ERRNO_EXCHANGE_COOLER				0x1010//液冷模块切换程序异常
#define		ERRNO_EXCHANGE_COOLER_PRESSURE		0x1111//通过压力判断液冷模块切换程序异常
#define		ERRNO_HYCT_PRESSURE					0x1212//货船增压状态异常
#define		ERRNO_INTERFACE_VALVE_ON_PRESSURE	0x1313//通过压力判断近浮动断接器阀门开启异常
#define		ERRNO_PIPE_PRESSURE_STABLE			0x1414//补加接口管路压力不稳定
#define		ERRNO_TANK_PRESSURE_STABLE			0x1515//贮箱压力不稳定
#define		ERRNO_SUPPLY_VALVE_POWER_OFF		0x1616//补加系统阀门断电异常
#define		ERRNO_TANK_VALVE_PRESSURE			0x1717//补加流动时通过压力判断进贮箱阀门关闭异常
#define		ERRNO_LEAK_INTERFACE_ERROR			0x1818//检漏排气补加接口解码错误

#define		ERRNO_FAULT_DIAGNOSIS				0xabab//故障检测与处理，补加暂停



//补加模式
#define		MODE_AUTO				0x0101//自动
#define		MODE_HALF_AUTO			0x0202//半自动
#define		MODE_MAN_MADE			0x0303//手动
#define		MODE_NONE				0x0404//无

//运行状态
#define		STATE_NONE				0x0000//空闲
#define		STATE_RUN				0x0101//运行
#define		STATE_PAUSE				0x0202//暂停
#define		STATE_BREAK				0x0303//中止
#define		STATE_PAUSE_RESUME		0x0404//暂停恢复


//补加阶段
#define		STAGE_00_NONE			0x0000//补加阶段0：空闲
#define		STAGE_01_INPUT			0x0101//补加阶段1：注入补加参数
#define		STAGE_02_SET			0x0202//补加阶段2：状态设置
#define		STAGE_03_CONNECT		0x0303//补加阶段3：浮动断接器插合
#define		STAGE_04_LEAK			0x0404//补加阶段4：补加管路检漏
#define		STAGE_05_COMP_F			0x0505//补加阶段5：燃贮箱抽气
#define		STAGE_06_PRE_F			0x0606//补加阶段6：燃贮箱增压充填
#define		STAGE_07_FLOW_F			0x0707//补加阶段7：燃推进剂补加流动
#define		STAGE_08_REPRE_F		0x0808//补加阶段8：燃贮箱复压
#define		STAGE_09_COMP_F_T		0x0909//补加阶段9：第三个燃贮箱抽气
#define		STAGE_10_FLOW_F_T		0x0a0a//补加阶段10：第三个燃贮箱补加流动
#define		STAGE_11_REPRE_F_T		0x0b0b//补加阶段11：第三个燃贮箱复压
#define		STAGE_12_BLOW_F			0x0c0c//补加阶段12：燃管路吹除
#define		STAGE_13_COMP_O			0x0d0d//补加阶段13：氧贮箱抽气
#define		STAGE_14_PRE_O			0x0e0e//补加阶段14：氧贮箱增压充填
#define		STAGE_15_FLOW_O			0x0f0f//补加阶段15：氧推进剂补加流动
#define		STAGE_16_REPRE_O		0x1010//补加阶段16：氧贮箱复压
#define		STAGE_17_COMP_O_T		0x1111//补加阶段17：第三个氧贮箱抽气
#define		STAGE_18_FLOW_O_T		0x1212//补加阶段18：第三个氧贮箱补加流动
#define		STAGE_19_REPRE_O_T		0x1313//补加阶段19：第三个氧贮箱复压
#define		STAGE_20_BLOW_O			0x1414//补加阶段20：氧管路吹除
#define		STAGE_21_DISCONNECT		0x1515//补加阶段21：浮动断接器脱开
#define		STAGE_22_RESUME			0x1616//补加阶段22：状态恢复


/*注入参数解码----------------------------------------------------------------------------*/

#define		DECODE_NONE				0x0000//无

#define		DECODE_INTERFACE_R1		0x0101//燃补加接口R1
#define		DECODE_INTERFACE_R2		0x0202//燃补加接口R2
#define		DECODE_INTERFACE_R3		0x0303//燃补加接口R3
#define		DECODE_INTERFACE_R4		0x0404//燃补加接口R4
#define		DECODE_INTERFACE_O1		0x0505//氧补加接口O1
#define		DECODE_INTERFACE_O2		0x0606//氧补加接口O2
#define		DECODE_INTERFACE_O3		0x0707//氧补加接口O3
#define		DECODE_INTERFACE_O4		0x0808//氧补加接口O4

#define		DECODE_TANK_F1			0x0909//燃贮箱F1
#define		DECODE_TANK_F2			0x0a0a//燃贮箱F2
#define		DECODE_TANK_F3			0x0b0b//燃贮箱F3
#define		DECODE_TANK_O1			0x0c0c//氧贮箱O1
#define		DECODE_TANK_O2			0x0d0d//氧贮箱O2
#define		DECODE_TANK_O3			0x0e0e//氧贮箱O3

#define		DECODE_GAS_F1			0x0f0f//燃气瓶F1
#define		DECODE_GAS_F2			0x1010//燃气瓶F2
#define		DECODE_GAS_F3			0x1111//燃气瓶F3
#define		DECODE_GAS_O1			0x1212//氧气瓶O1
#define		DECODE_GAS_O2			0x1313//氧气瓶O2
#define		DECODE_GAS_O3			0x1414//氧气瓶O3

#define		DECODE_COMPRESSOR_A		0x1515//压气机A
#define		DECODE_COMPRESSOR_B		0x1616//压气机B
#define		DECODE_COMPRESSOR_C		0x1717//压气机C

#define		DECODE_COOLER_Z_1		0x1818//液冷模块主I
#define		DECODE_COOLER_Z_2		0x1919//液冷模块主II
#define		DECODE_COOLER_B_1		0x1a1a//液冷模块备I
#define		DECODE_COOLER_B_2		0x1b1b//液冷模块备II

#define		DECODE_COMP_VALVE_Z		0x1c1c//压气机出口主份阀
#define		DECODE_COMP_VALVE_B		0x1d1d//压气机出口备份阀

#define		DECODE_SENSOR_TANK_Z	0x1e1e//贮箱压力传感器主份
#define		DECODE_SENSOR_TANK_B	0x1f1f//贮箱压力传感器备份

#define		DECODE_SENSOR_PIPE_LOW_PTB02	0x2020//低压气路压力传感器设定，燃路PTb2
#define		DECODE_SENSOR_PIPE_LOW_PTB04	0x2121//低压气路压力传感器设定，燃路PTb4
#define		DECODE_SENSOR_PIPE_LOW_PTB24	0x2222//低压气路压力传感器设定，燃路或者氧路PTb24

#define		DECODE_SENSOR_PIPE_LOW_PTB01	0x2323//低压气路压力传感器设定，氧路PTb1
#define		DECODE_SENSOR_PIPE_LOW_PTB03	0x2424//低压气路压力传感器设定，氧路PTb3

#define		DECODE_SENSOR_PIPE_LOW_PTB28	0x2525//压力传感器PTb28
#define		DECODE_SENSOR_PIPE_LOW_PTB29	0x2626//压力传感器PTb29

/*推进控制驱动器自锁阀状态宏定义----------------------------------------------------------*/

//主路推进控制驱动器推进自锁阀
#define STATE_LVt09	0x00
#define STATE_LVt11	0x01
#define STATE_LVt01	0x02
#define STATE_LVt07	0x03
#define STATE_LVt43	0x04
#define STATE_LVt45	0x05
#define STATE_LVt31	0x06
#define STATE_LVt37	0x07
#define STATE_LVt08	0x08
#define STATE_LVt10	0x09
#define STATE_LVt51	0x0a
#define STATE_LVt02	0x0b
#define STATE_LVt38	0x0c
#define STATE_LVt44	0x0d
#define STATE_LVt12	0x0e
#define STATE_LVt32	0x0f
#define STATE_LVt03	0x10
#define STATE_LVt20	0x11
#define STATE_LVt46	0x12
#define STATE_LVt52	0x13
#define STATE_LVt35	0x14
#define STATE_LVt19	0x15
#define STATE_LVt24	0x16
#define STATE_LVt27	0x17
#define STATE_LVt36	0x18
#define STATE_LVt23	0x19
#define STATE_LVt28	0x1a


//备路推进控制驱动器推进自锁阀
#define STATE_LVt18	0x1b
#define STATE_LVt22	0x1c
#define STATE_LVt06	0x1d
#define STATE_LVt16	0x1e
#define STATE_LVt29	0x1f
#define STATE_LVt39	0x20
#define STATE_LVt26	0x21
#define STATE_LVt13	0x22
#define STATE_LVt15	0x23
#define STATE_LVt17	0x24
#define STATE_LVt41	0x25
#define STATE_LVt05	0x26
#define STATE_LVt34	0x27
#define STATE_LVt48	0x28
#define STATE_LVt21	0x29
#define STATE_LVt25	0x2a
#define STATE_LVt33	0x2b
#define STATE_LVt47	0x2c
#define STATE_LVt50	0x2d
#define STATE_LVt54	0x2e
#define STATE_LVt04	0x2f
#define STATE_LVt14	0x30
#define STATE_LVt49	0x31
#define STATE_LVt53	0x32
#define STATE_LVt42	0x33
#define STATE_LVt30	0x34
#define STATE_LVt40	0x35

//偏移量
#define STATE_OFFSET 	0x1b

//字位置
#define TGTHT520_L_BYTE_L_BIT	0x000f
#define TGTHT520_L_BYTE_H_BIT	0x00f0
#define TGTHT520_H_BYTE_L_BIT	0x0f00
#define TGTHT520_H_BYTE_H_BIT	0xf000

//开关状态
#define TGTHT520_VALVE_ON	0x0003
#define TGTHT520_VALVE_OFF	0x000c
#define TGTHT520_VALVE_NONE	0x000f

//自锁阀数量
#define TGTHT510A_NUMBER	0x1b
#define TGTHT510B_NUMBER	0x1b

//定义常量
#define FIRST_TANK			0x0101//第一个补加贮箱	
#define SECOND_TANK			0x0202//第二个补加贮箱
#define THIRD_TANK			0x0303//第三个补加贮箱

#define ONE_GAS				0x0404//一个抽气气瓶
#define TWO_GAS				0x0505//两个抽气气瓶
#define NONE_GAS			0x0606//气瓶数量错误

#define FIRST_GAS			0x0707//第一个抽气气瓶
#define SECOND_GAS			0x0808//第二个抽气气瓶

//压气机运行状态
#define COMPRESSOR_RUN		0x1234//压气机处于运行状态
#define COMPRESSOR_STOP		0x4321//压气机处于停止状态			

//时间常量
#define		CONST_TIME_2SEC		0x0004//定时常量2s
#define		CONST_TIME_5SEC		0x000a//定时常量5s
#define		CONST_TIME_10SEC	0x0014//定时常量10s
#define		CONST_TIME_12SEC	0x0018//定时常量12s
#define		CONST_TIME_15SEC	0x001e//定时常量15s

#define		CONST_TIME_30SEC	0x003c//定时常量30s
#define		CONST_TIME_1MIN		0x0078//定时常量1min
#define		CONST_TIME_5MIN		0x0258//定时常量5min

#define		CONST_TIME_12MIN	0x05a0//定时常量12min
#define		CONST_TIME_20MIN	0x0960//定时常量20min

//#define		CONST_TIME_1MIN		0x0018//定时常量1min-------调试！！！！！！


//其他
#define 	CONST_ISOLATION			0x0003//通过压力判断贮箱气路隔离的阈值
#define		EXCHANGE_COOLER_NO1		0x0101//液冷模块切换指令1
#define		EXCHANGE_COOLER_NO2		0x0202//液冷模块切换指令2
#define		EXCHANGE_COOLER_NO3		0x0303//液冷模块切换指令3
#define		EXCHANGE_COOLER_NO4		0x0404//液冷模块切换指令4

//#define 	CONST_MAX_COMP_TIME		0x00023280//最大抽气时间，约20小时

#define 	CONST_MAX_COMP_TIME		0x00000e10//最大抽气时间，约30min

#define 	CONST_COOLER_START_V	0x033C//液冷启动，泵转速判断阈值
#define		CONST_NUM_ZERO			0x0000


//函数声明----------------------------------------------------------------

void TGTHT510_supply_main_initial(void);
void TGTHT510_supply_main(void);
void TGTHT510_supply_main_half_auto(void);
void TGTHT510_supply_main_run(void);
void TGTHT510_supply_main_pause_deal(void);
void TGTHT510_supply_main_pause_resume_deal(void);
void TGTHT510_supply_main_break_deal(void);



void TGTHT510_supply_main_pause(uint16 errno);
void TGTHT510_supply_main_lvb_set(uint16 code);
uint16 TGTHT510_supply_main_lvb_get(uint16 code,uint16 on_or_off);
void TGTHT510_supply_main_lvt_set(uint16 code);
uint16 TGTHT510_supply_main_lvt_get(uint16 code,uint16 on_or_off);
uint16 TGTHT510_supply_main_valve_state_TGTHT520(uint16 state_code);
void TGTHT510_supply_main_equ_command_set(uint16 code);
void TGTHT510_supply_time_dealing(void);
void TGTHT510_supply_time_stage_start(void);
void TGTHT510_supply_time_stage_end(void);
void TGTHT510_supply_time_stage_get(uint32 *time_val);
void TGTHT510_supply_time_step_start(void);
void TGTHT510_supply_time_step_end(void);
uint16	TGTHT510_supply_time_step_is_get(uint32 const_val);


#endif

