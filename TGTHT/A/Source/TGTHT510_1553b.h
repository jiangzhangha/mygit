/**
  ******************************************************************************
  * @file    TGTHT510_1553b.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器1553B总线处理模块头文件
  ******************************************************************************
  */
 
 #ifndef __TGTHT510_1553b_h
 #define __TGTHT510_1553b_h
 

/*声明结构体类型---------------------------------------------------------*/


#ifdef TEST_VERSION

typedef struct				  //子地址状态标志查询结构体
{
	uint32 Subaddress_05_flag;//测试件使用
	uint32 Subaddress_11_flag;//子地址11、发送常规遥测与工程遥测
	uint32 Subaddress_12_flag;//子地址12、发送设备管理指令
	uint32 Subaddress_13_flag;//子地址13、发送仪表显示遥测
	uint32 Subaddress_17_flag;//子地址17、发送转发前（后）向口补加数据 复帧
	uint32 Subaddress_19_flag;//子地址19、发送转GNC故检状态字
	uint32 Subaddress_21_flag;//子地址21、发送内存下传数据
	uint32 Subaddress_23_flag;//子地址23、发送故障代码
	uint32 Subaddress_28_flag;//子地址28、发送服务请求
	uint32 Subaddress_14_flag;//子地址14、接受520、530、540互传数据
	uint32 Subaddress_15_flag;//子地址15、接受总线指令与手控指令
	uint32 Subaddress_16_flag;//子地址16、接受注入指令
	uint32 Subaddress_18_flag;//子地址18、接受货船发送补加信息（数据转换器1）
	uint32 Subaddress_20_flag;//子地址20、接受货船发送补加信息（数据转换器2）
	uint32 Subaddress_22_flag;//子地址22、接受综合电子采集的推进传感器参数
	uint32 Subaddress_29_flag;//子地址29、接受勤务指令
	uint8 Current_Stack_Pointer;
}TGTHT510_1553B_Subaddress_flag_TypeDef;

#else
	
typedef struct				  //子地址状态标志查询结构体
{
	uint32 Subaddress_11_flag;//子地址11、发送常规遥测与工程遥测
	uint32 Subaddress_12_flag;//子地址12、发送设备管理指令
	uint32 Subaddress_13_flag;//子地址13、发送仪表显示遥测
	uint32 Subaddress_17_flag;//子地址17、发送转发前（后）向口补加数据 复帧
	uint32 Subaddress_19_flag;//子地址19、发送转GNC故检状态字
	uint32 Subaddress_21_flag;//子地址21、发送内存下传数据
	uint32 Subaddress_23_flag;//子地址23、发送故障代码
	uint32 Subaddress_28_flag;//子地址28、发送服务请求
	uint32 Subaddress_14_flag;//子地址14、接受520、530、540互传数据
	uint32 Subaddress_15_flag;//子地址15、接受总线指令与手控指令
	uint32 Subaddress_16_flag;//子地址16、接受注入指令
	uint32 Subaddress_18_flag;//子地址18、接受货船发送补加信息（数据转换器1）
	uint32 Subaddress_20_flag;//子地址20、接受货船发送补加信息（数据转换器2）
	uint32 Subaddress_22_flag;//子地址22、接受综合电子采集的推进传感器参数
	uint32 Subaddress_29_flag;//子地址29、接受勤务指令
	uint8 Current_Stack_Pointer;
}TGTHT510_1553B_Subaddress_flag_TypeDef;

#endif



typedef struct
{
	uint16 inputcommand_head_word1;			//注入遥控帧主导头1，1字
	uint16 inputcommand_head_word2;			//注入遥控帧主导头2，1字
	uint8  inputcommand_head_byte;			//注入遥控帧序列号，1字节
	uint16 inputcommand_data[415];			//注入遥控帧数据，最大829字节
	uint16 inputcommand_CRC;				//注入遥控帧CRC校验字，1字
	uint16 inputcommand_length;				//注入遥控帧帧长，1字
	uint16 inputcommand_data_length;		//注入遥控帧数据域长度，1字
}TGTHT510_1553B_inputcommand_TypeDef;		//注入遥控帧数据格式定义


typedef struct
{
	uint16 CG_GC_message_count_Z;			//常规与工程遥测通讯状态计数,主份BU65170
	uint16 CG_GC_message_count_B;			//常规与工程遥测通讯状态计数,备份BU65170
	uint16 YB_message_count;				//仪表遥测通讯状态计数
	uint16 HYCT1100_T_message_count;		//转发货船通讯状态计数
	uint16 TGTHT100_message_count;			//接收推进遥测线路盒通讯状态计数
	uint16 TGTHT520a_message_count;			//接收推进控制驱动器A机通讯状态计数
	uint16 TGTHT520b_message_count;			//接收推进控制驱动器B机通讯状态计数
	uint16 TGTHT530_message_count;			//接收压气机电机驱动器通讯状态计数
	uint16 HYCT1100_R_message_count;		//接收货船补加信息数据通讯状态计数
	uint16 KPU_message_count;				//接收数管遥测数据通讯状态计数
	
	uint16 TGTHT100_validity;				//接收推进遥测线路盒数据有效性标志
	uint16 TGTHT520a_validity;				//接收推进控制驱动器A机数据有效性标志
	uint16 TGTHT520b_validity;				//接收推进控制驱动器B机数据有效性标志
	uint16 TGTHT530_validity;				//接收压气机电机驱动器数据通讯状态计数
	uint16 HYCT1100_validity;				//接收货船补加数据通讯状态计数
	uint16 KPU_validity;					//接收数管遥测数据通讯状态计数
	
}TGTHT510_1553B_message_state_TypeDef;		//总线通讯状态数据格式定义


typedef struct
{
	uint16 count;
	uint16 last_use_BU65170;
}TGTHT510_which_bus_TypeDef;


typedef struct
{
	uint16 Subaddress_11_service_flag;
	uint16 Subaddress_12_service_flag;
	uint16 Subaddress_13_service_flag;
	uint16 Subaddress_17_service_flag;
	uint16 Subaddress_19_service_flag;
	uint16 Subaddress_21_service_flag;
	uint16 Subaddress_23_service_flag;
	uint16 Subaddress_28_service_flag;
	uint16 Subaddress_14_service_flag;
	uint16 Subaddress_15_service_flag;
	uint16 Subaddress_16_service_flag;
	uint16 Subaddress_18_service_flag;
	uint16 Subaddress_20_service_flag;
	uint16 Subaddress_22_service_flag;
	
}TGTHT510_1553B_service_flag_TypeDef;	//勤务指令标志结构体定义




//---------主份BU65170数据宏定义-----------------------------------------------------------------


#define BU65170_Z_RESET_REG					(uint32)0x26007ff8				//复位寄存器，写0xAA55有效
#define	BU65170_Z_STATUS_REG				(uint32)0x26007ffc				//操作状态寄存器，0x5555可操作，其他不可操作

#define BU65170_Z_T_RAM_BASE				(uint32)0x26000000				//主份BU65170发送数据区基地址
#define BU65170_Z_R_RAM_BASE				(uint32)0x26004000				//主份BU65170接收数据区基地址

#define BU65170_Z_T_CG_GC_BASE				(BU65170_Z_T_RAM_BASE+4*0x0400)	//数据基地址，RT11，发送常规遥测与工程遥测
#define BU65170_Z_T_COMMAND_EQUIP_BASE		(BU65170_Z_T_RAM_BASE+4*0x0500)	//数据基地址，RT12，发送设备管理指令
#define BU65170_Z_T_YB_BASE					(BU65170_Z_T_RAM_BASE+4*0x0520)	//数据基地址，RT13，发送仪表遥测
#define BU65170_Z_T_HYCT1100_BASE			(BU65170_Z_T_RAM_BASE+4*0x0540)	//数据基地址，RT17，发送转发前（后）向口补加数据
#define BU65170_Z_T_GNC_BASE				(BU65170_Z_T_RAM_BASE+4*0x05c0)	//数据基地址，RT19，发送转GNC故检状态字
#define BU65170_Z_T_MEMORY_BASE				(BU65170_Z_T_RAM_BASE+4*0x0600)	//数据基地址，RT21，发送内存下传数据


#define BU65170_Z_T_CODEFAULT_BASE			(BU65170_Z_T_RAM_BASE+4*0x0720)	//数据基地址，RT23，发送故障代码
#define BU65170_Z_T_ASKFORSERIVE_BASE		(BU65170_Z_T_RAM_BASE+4*0x0760)	//数据基地址，RT28，发送服务请求


#ifdef TEST_VERSION

#define BU65170_Z_T_TEST_FM_STATE_BASE		(BU65170_Z_T_RAM_BASE+4*0x0e00)	//数据基地址，RT05，发送阀门状态信息数据
#define BU65170_Z_T_TEST_FM_STATE_POINTER	(BU65170_Z_T_RAM_BASE+4*0x0165)	//查询指针，RT05，发送阀门状态信息数据

#endif

#define BU65170_Z_T_CG_GC_POINTER			(BU65170_Z_T_RAM_BASE+4*0x016b)	//查询指针，RT11，发送常规遥测与工程遥测
#define BU65170_Z_T_COMMAND_EQUIP_POINTER	(BU65170_Z_T_RAM_BASE+4*0x016c)	//查询指针，RT12，发送设备管理指令
#define BU65170_Z_T_YB_POINTER				(BU65170_Z_T_RAM_BASE+4*0x016d)	//查询指针，RT13，发送仪表遥测
#define BU65170_Z_T_HYCT1100_POINTER		(BU65170_Z_T_RAM_BASE+4*0x0171)	//查询指针，RT17，发送货船补加信息遥测
#define BU65170_Z_T_GNC_POINTER				(BU65170_Z_T_RAM_BASE+4*0x0173)	//查询指针，RT19，发送转GNC故检状态字
#define BU65170_Z_T_MEMORY_POINTER			(BU65170_Z_T_RAM_BASE+4*0x0175)	//查询指针，RT21，发送内存下传数据


#define BU65170_Z_T_CODEFAULT_POINTER		(BU65170_Z_T_RAM_BASE+4*0x0177)	//查询指针，RT23，发送故障代码
#define BU65170_Z_T_ASKFORSERIVE_POINTER	(BU65170_Z_T_RAM_BASE+4*0x017c)	//查询指针，RT28，发送服务请求

//----SRAM区-----------------------
#define BU65170_Z_R_TGTHT_BASE				(BU65170_Z_R_RAM_BASE+4*0x0203)	//数据基地址，RT14，接收驱动器、线路盒与压气机数据203-402
#define BU65170_Z_R_BUS_COMMAND_BASE		(BU65170_Z_R_RAM_BASE+4*0x0403)	//数据基地址，RT15，接收总线指令数据403-442
#define BU65170_Z_R_INPUT_COMMAND_BASE		(BU65170_Z_R_RAM_BASE+4*0x0443)	//数据基地址，RT16，接收注入指令数据443-842
#define BU65170_Z_R_HYCT1100_DATA1_BASE		(BU65170_Z_R_RAM_BASE+4*0x0843)	//数据基地址，RT18，接收货运飞船补加数据843-902
#define BU65170_Z_R_HYCT1100_DATA2_BASE		(BU65170_Z_R_RAM_BASE+4*0x0903)	//数据基地址，RT20，接收货运飞船补加数据903-982


#define BU65170_Z_R_KPU_BASE				(BU65170_Z_R_RAM_BASE+4*0x0983)	//数据基地址，RT22，接收数管遥测数据983-a02
#define BU65170_Z_R_INTER_COMMAND_BASE		(BU65170_Z_R_RAM_BASE+4*0x0a03)	//数据基地址，RT29，接收勤务指令数据a03-b02
#define BU65170_Z_R_MODE_CODE_BASE			(BU65170_Z_R_RAM_BASE+4*0x0b03)	//数据基地址，RT31，接收方式代码数据ac3-b02

#define BU65170_Z_R_STACK_DATA				(BU65170_Z_R_RAM_BASE+4*0x0000)	//堆栈A数据,0-200
#define BU65170_Z_R_STACK_POINTER			(BU65170_Z_R_RAM_BASE+4*0x0201)	//堆栈A指针201-202


//---------备份BU65170数据宏定义-----------------------------------------------------------------


#define BU65170_B_RESET_REG					(uint32)0x26027ff8				//复位寄存器，写0xAA55有效
#define	BU65170_B_STATUS_REG				(uint32)0x26027ffc				//操作状态寄存器，0x5555可操作，其他不可操作

#define BU65170_B_T_RAM_BASE				(uint32)0x26020000				//备份BU65170发送数据区基地址
#define BU65170_B_R_RAM_BASE				(uint32)0x26024000				//备份BU65170接收数据区基地址

#define BU65170_B_T_CG_GC_BASE				(BU65170_B_T_RAM_BASE+4*0x0400)	//数据基地址，RT11，发送常规遥测与工程遥测
#define BU65170_B_T_COMMAND_EQUIP_BASE		(BU65170_B_T_RAM_BASE+4*0x0500)	//数据基地址，RT12，发送设备管理指令
#define BU65170_B_T_YB_BASE					(BU65170_B_T_RAM_BASE+4*0x0520)	//数据基地址，RT13，发送仪表遥测
#define BU65170_B_T_HYCT1100_BASE			(BU65170_B_T_RAM_BASE+4*0x0540)	//数据基地址，RT17，发送货船补加信息遥测
#define BU65170_B_T_GNC_BASE				(BU65170_B_T_RAM_BASE+4*0x05c0)	//数据基地址，RT19，发送转GNC故检状态字
#define BU65170_B_T_MEMORY_BASE				(BU65170_B_T_RAM_BASE+4*0x0600)	//数据基地址，RT21，发送内存下传数据


#define BU65170_B_T_CODEFAULT_BASE			(BU65170_B_T_RAM_BASE+4*0x0720)	//数据基地址，RT23，发送故障代码
#define BU65170_B_T_ASKFORSERIVE_BASE		(BU65170_B_T_RAM_BASE+4*0x0760)	//数据基地址，RT28，发送服务请求

#ifdef TEST_VERSION

#define BU65170_B_T_TEST_FM_STATE_BASE		(BU65170_B_T_RAM_BASE+4*0x0e00)	//数据基地址，RT05，发送阀门状态信息数据
#define BU65170_B_T_TEST_FM_STATE_POINTER	(BU65170_B_T_RAM_BASE+4*0x0165)	//查询指针，RT05，发送阀门状态信息数据

#endif

#define BU65170_B_T_CG_GC_POINTER			(BU65170_B_T_RAM_BASE+4*0x016b)	//查询指针，RT11，发送常规遥测与工程遥测
#define BU65170_B_T_COMMAND_EQUIP_POINTER	(BU65170_B_T_RAM_BASE+4*0x016c)	//查询指针，RT12，发送设备管理指令
#define BU65170_B_T_YB_POINTER				(BU65170_B_T_RAM_BASE+4*0x016d)	//查询指针，RT13，发送仪表遥测
#define BU65170_B_T_HYCT1100_POINTER		(BU65170_B_T_RAM_BASE+4*0x0171)	//查询指针，RT17，发送货船补加信息遥测
#define BU65170_B_T_GNC_POINTER				(BU65170_B_T_RAM_BASE+4*0x0173)	//查询指针，RT19，发送转GNC故检状态字!
#define BU65170_B_T_MEMORY_POINTER			(BU65170_B_T_RAM_BASE+4*0x0175)	//查询指针，RT21，发送内存下传数据



#define BU65170_B_T_CODEFAULT_POINTER		(BU65170_B_T_RAM_BASE+4*0x0177)	//查询指针，RT23，发送故障代码
#define BU65170_B_T_ASKFORSERIVE_POINTER	(BU65170_B_T_RAM_BASE+4*0x017c)	//查询指针，RT28，发送服务请求


//----SRAM区-----------------------
#define BU65170_B_R_TGTHT_BASE				(BU65170_B_R_RAM_BASE+4*0x0203)	//数据基地址，RT14，接收驱动器、线路盒与压气机数据203-402
#define BU65170_B_R_BUS_COMMAND_BASE		(BU65170_B_R_RAM_BASE+4*0x0403)	//数据基地址，RT15，接收总线指令数据403-442
#define BU65170_B_R_INPUT_COMMAND_BASE		(BU65170_B_R_RAM_BASE+4*0x0443)	//数据基地址，RT16，接收注入指令数据443-842
#define BU65170_B_R_HYCT1100_DATA1_BASE		(BU65170_B_R_RAM_BASE+4*0x0843)	//数据基地址，RT18，接收货运飞船补加数据843-902
#define BU65170_B_R_HYCT1100_DATA2_BASE		(BU65170_B_R_RAM_BASE+4*0x0903)	//数据基地址，RT18，接收货运飞船补加数据903-982


#define BU65170_B_R_KPU_BASE				(BU65170_B_R_RAM_BASE+4*0x0983)	//数据基地址，RT22，接收数管遥测数据983-a02
#define BU65170_B_R_INTER_COMMAND_BASE		(BU65170_B_R_RAM_BASE+4*0x0a03)	//数据基地址，RT29，接收勤务指令数据a03-b02
#define BU65170_B_R_MODE_CODE_BASE			(BU65170_B_R_RAM_BASE+4*0x0b03)	//数据基地址，RT31，接收方式代码数据ac3-b02

#define BU65170_B_R_STACK_DATA				(BU65170_B_R_RAM_BASE+4*0x0000)	//堆栈A数据,0-200
#define BU65170_B_R_STACK_POINTER			(BU65170_B_R_RAM_BASE+4*0x0201)	//堆栈A指针201-202


//---------公用数据宏定义---------------------------------------------------------------------
//#define BU65170_READ_ALLOW					0x0000
#define BU65170_READ_ALLOW					0x5555
#define BU65170_READ_NOT_ALLOW				0xaaaa

#define BU65170_Z							(uint16)0x1234					//主份BU65170
#define BU65170_B							(uint16)0x4321					//备份BU65170

#define BU65170_CG_GC_POINTER				0x0400
#define BU65170_YB_POINTER					0x0520
#define BU65170_TGTHT_POINTER				0x0800
#define BU65170_INPUT_COMMAND_POINTER		0x0a00
#define BU65170_HYCT1100_POINTER			0x0540
#define BU65170_ASKFORSERIVE_POINTER		0x0760
#define BU65170_COMMAND_EQUIP_POINTER		0x0500
#define BU65170_GNC_POINTER					0x05c0
#define BU65170_MEMORY_POINTER				0x0600
#define BU65170_HYCT_DATA1_POINTER			0x0c00
#define BU65170_HYCT_DATA2_POINTER			0x0c80



#define BU65170_R_STACK_DATA_LEN			0x0100							//堆栈长度
#define BU65170_R_STACK_POINTER_LEN			0x0001							//堆栈A指针长度

#define TYPE_SEND_HYCT_FORE					(uint16)0x1234 //标志，发送转发前向口补加数据
#define TYPE_SEND_HYCT_BACK					(uint16)0x4321 //标志，发送转发后向口补加数据

#define TYPE_RECEIVE_HYCT_DATA1				(uint16)0x1234 //标志，接受货船发送补加信息，数据转换器1
#define TYPE_RECEIVE_HYCT_DATA2				(uint16)0x4321 //标志，接受货船发送补加信息，数据转换器2



/*宏定义----------------------------------------------------------------------*/

 
 #define TGTHT510_1553B_REG_BASE (uint32)0x26000000   						//1553B寄存器基地址
 #define TGTHT510_1553B_RAM_BASE (uint32)0x26010000							//1553B数据区基地址
 
 #define TGTHT510_1553B_REG_InterruptMaskReg 					(TGTHT510_1553B_REG_BASE+4*0x00)
 #define TGTHT510_1553B_REG_ConfigurationReg1 					(TGTHT510_1553B_REG_BASE+4*0x01)
 #define TGTHT510_1553B_REG_ConfigurationReg2 					(TGTHT510_1553B_REG_BASE+4*0x02)
 #define TGTHT510_1553B_REG_StartResetReg 						(TGTHT510_1553B_REG_BASE+4*0x03)
 #define TGTHT510_1553B_REG_CommandStackPointerReg 				(TGTHT510_1553B_REG_BASE+4*0x03)
 #define TGTHT510_1553B_REG_RTSubaddressControlWordReg 			(TGTHT510_1553B_REG_BASE+4*0x04)
 #define TGTHT510_1553B_REG_TimeTagReg 							(TGTHT510_1553B_REG_BASE+4*0x05)
 #define TGTHT510_1553B_REG_InterruptStatusReg 					(TGTHT510_1553B_REG_BASE+4*0x06)
 #define TGTHT510_1553B_REG_ConfigurationReg3 					(TGTHT510_1553B_REG_BASE+4*0x07)
 #define TGTHT510_1553B_REG_ConfigurationReg4 					(TGTHT510_1553B_REG_BASE+4*0x08)
 #define TGTHT510_1553B_REG_ConfigurationReg5 					(TGTHT510_1553B_REG_BASE+4*0x09)
 #define TGTHT510_1553B_REG_DataStackAddressReg 				(TGTHT510_1553B_REG_BASE+4*0x0A)
 #define TGTHT510_1553B_REG_BCFrameTimeRemainingReg 			(TGTHT510_1553B_REG_BASE+4*0x0B)
 #define TGTHT510_1553B_REG_BCTimeRemainingToNextMessageReg 	(TGTHT510_1553B_REG_BASE+4*0x0C)
 #define TGTHT510_1553B_REG_RTLastCommandWord 					(TGTHT510_1553B_REG_BASE+4*0x0D)
 #define TGTHT510_1553B_REG_RTStatusWordReg 					(TGTHT510_1553B_REG_BASE+4*0x0E)
 #define TGTHT510_1553B_REG_RTBITWordReg 						(TGTHT510_1553B_REG_BASE+4*0x0F)

 #define TGTHT510_1553B_RAM_STACK_POINTER_A 					(TGTHT510_1553B_RAM_BASE+4*0x0100)	//RT指令堆栈指针A
 #define TGTHT510_1553B_RAM_LOOKUP_A_BASE 						(TGTHT510_1553B_RAM_BASE+4*0x0140)	//RT查询表A基地址
 #define TGTHT510_1553B_RAM_MODE_INTERRUPT_TABLE 				(TGTHT510_1553B_RAM_BASE+4*0x0108)	//方式指令选择中断表基地址
 
 #define TGTHT510_1553B_RAM_ILLEGAL_NONBROADCAST_TABLE			(TGTHT510_1553B_RAM_BASE+4*0x0380)	//非广播接收、发送消息非法表基地址
 #define TGTHT510_1553B_RAM_BUSY_TABLE							(TGTHT510_1553B_RAM_BASE+4*0x0240)	//忙表基地址
 
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_LOOKUP			(TGTHT510_1553B_RAM_BASE+4*0x01A0)   //RT查询表子地址控制字基地址
 #define TGTHT510_1553B_RAM_RECEIVE_LOOKUP 						(TGTHT510_1553B_RAM_BASE+4*0x0140)	//RT查询表接收查询指针基地址
 #define TGTHT510_1553B_RAM_TRANSMIT_LOOKUP   					(TGTHT510_1553B_RAM_BASE+4*0x0160)	//RT查询表发送查询指针基地址
 #define TGTHT510_1553B_RAM_BROADCAST_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x0180)	//RT查询表广播查询指针基地址
 
 #define TGTHT510_1553B_RAM_RT11_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x016B)   //RT子地址11发送查询指针
 #define TGTHT510_1553B_RAM_RT12_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x016C)   //RT子地址12发送查询指针
 #define TGTHT510_1553B_RAM_RT13_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x016D)   //RT子地址13发送查询指针
 #define TGTHT510_1553B_RAM_RT17_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x0171)   //RT子地址17发送查询指针
 #define TGTHT510_1553B_RAM_RT23_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x0177)   //RT子地址23发送查询指针
 #define TGTHT510_1553B_RAM_RT25_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x0179)   //RT子地址25发送查询指针
 #define TGTHT510_1553B_RAM_RT28_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x017C)   //RT子地址28发送查询指针

 #define TGTHT510_1553B_RAM_RT14_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x014E)	//RT子地址14接收查询指针
 #define TGTHT510_1553B_RAM_RT15_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x014F)	//RT子地址15接收查询指针
 #define TGTHT510_1553B_RAM_RT16_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x0150)	//RT子地址16接收查询指针
 #define TGTHT510_1553B_RAM_RT18_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x0152)	//RT子地址18接收查询指针
 #define TGTHT510_1553B_RAM_RT22_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x0156)	//RT子地址22接收查询指针
 #define TGTHT510_1553B_RAM_RT29_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x015D)	//RT子地址29接收查询指针
 #define TGTHT510_1553B_RAM_RT31_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x015F)	//RT子地址31接收查询指针
 
 
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT11				(TGTHT510_1553B_RAM_BASE+4*0x01AB)	//RT子地址11控制字
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT12				(TGTHT510_1553B_RAM_BASE+4*0x01AC)	//RT子地址12控制字
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT13				(TGTHT510_1553B_RAM_BASE+4*0x01AD)	//RT子地址13控制字
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT17				(TGTHT510_1553B_RAM_BASE+4*0x01B1)	//RT子地址17控制字
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT23				(TGTHT510_1553B_RAM_BASE+4*0x01B7)	//RT子地址23控制字
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT25				(TGTHT510_1553B_RAM_BASE+4*0x01B9)	//RT子地址25控制字
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT28				(TGTHT510_1553B_RAM_BASE+4*0x01BC)	//RT子地址28控制字
 
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT14				(TGTHT510_1553B_RAM_BASE+4*0x01AE)	//RT子地址14控制字
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT15				(TGTHT510_1553B_RAM_BASE+4*0x01AF)	//RT子地址15控制字
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT16				(TGTHT510_1553B_RAM_BASE+4*0x01B0)	//RT子地址16控制字
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT18				(TGTHT510_1553B_RAM_BASE+4*0x01B2)	//RT子地址18控制字
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT22				(TGTHT510_1553B_RAM_BASE+4*0x01B6)	//RT子地址22控制字
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT29				(TGTHT510_1553B_RAM_BASE+4*0x01BD)	//RT子地址29控制字
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT31				(TGTHT510_1553B_RAM_BASE+4*0x01BF)	//RT子地址31控制字
 
 /*数据指针基地址，待修改-----------------------------------------------------*/
#define TGTHT510_1553B_RAM_TRANSMIT_CG_GC_BASE 				0x0400						//常规与工程遥测数据基地址，RT11
#define TGTHT510_1553B_RAM_TRANSMIT_COMMAND_EQUIP_BASE  	0x0540						//设备间管理指令基地址，RT12
#define TGTHT510_1553B_RAM_TRANSMIT_YB_BASE 				0x05A0						//仪表遥测数据基地址，RT13
#define TGTHT510_1553B_RAM_TRANSMIT_HYCT1100_BASE			0x0C00						//送货船遥测数据基地址，RT17
#define TGTHT510_1553B_RAM_TRANSMIT_CODEFAULT_BASE         	0x0600						//推进故障代码基地址，RT23
#define TGTHT510_1553B_RAM_TRANSMIT_TGTHT510_BASE			0x0DC0						//送推进管理器备机遥测数据基地址，RT25
#define TGTHT510_1553B_RAM_TRANSMIT_ASKFORSERIVE_BASE     	0x0660                 		//服务请求数据基地址，RT28

#define TGTHT510_1553B_RAM_RECEIVE_FROM_TGTHT_BASE			0x0700						//接收遥测线路盒、压气机、驱动器遥测，RT14
#define TGTHT510_1553B_RAM_RECEIVE_BUS_COMMAND_BASE			0x0840						//接收总线与手控指令，RT15
#define TGTHT510_1553B_RAM_RECEIVE_INPUT_COMMAND_BASE 		0x08A0						//接收注入指令，RT16
#define TGTHT510_1553B_RAM_RECEIVE_FROM_HYCT1100_BASE		0x0C80						//接收货运飞船补加数据，RT18
#define TGTHT510_1553B_RAM_RECEIVE_FROM_KPU_BASE			0x0D00						//接收数管遥测数据，RT22
#define TGTHT510_1553B_RAM_RECEIVE_INTERACTIVE_COMMAND_BASE	0x0AE0						//接收勤务指令数据，RT29
#define TGTHT510_1553B_RAM_RECEIVE_MODE_CODE_BASE			0x0BA0						//接收方式代码，RT31
 
 /*RT子地址控制字，待修改-----------------------------------------------------*/
 
#define T_SUBADD_CONTROL_WORD_RT11						0x0800//发送常规遥测与工程遥测，循环缓冲模式，256字
#define T_SUBADD_CONTROL_WORD_RT12						0x0000//发送设备管理指令，单消息模式
#define T_SUBADD_CONTROL_WORD_RT13						0x0000//发送仪表遥测，单消息模式
#define T_SUBADD_CONTROL_WORD_RT17						0x0000//发送货船遥测数据，待定！！！
#define T_SUBADD_CONTROL_WORD_RT23						0x0000//发送推进故障代码，单消息模式
#define T_SUBADD_CONTROL_WORD_RT25						0x0000//发送管理器B机遥测，待定！！！
#define T_SUBADD_CONTROL_WORD_RT28						0x0000//发送服务请求，单消息模式

#define R_SUBADD_CONTROL_WORD_RT14						0x0040//接收遥测线路盒、压气机、驱动器遥测，循环缓冲模式，256字
#define R_SUBADD_CONTROL_WORD_RT15						0x0000//接收总线与手控指令，单消息模式
#define R_SUBADD_CONTROL_WORD_RT16						0x0060//接收注入指令，循环缓冲模式，512字
#define R_SUBADD_CONTROL_WORD_RT18						0x0000//接收货船补加数据，待定！！！
#define R_SUBADD_CONTROL_WORD_RT22						0x0000//接收数管遥测数据，待定！！！
#define R_SUBADD_CONTROL_WORD_RT29						0x0020//接收勤务指令，循环缓冲模式，128字
#define R_SUBADD_CONTROL_WORD_RT31						0x0000//接收方式代码，单消息模式

/*APID定义，待修改-----------------------------------------------------*/
#define T_APID_CG 					0x0300//APID发送常规遥测
#define T_APID_GC					0x0301//APID发送工程遥测
#define T_APID_YB					0x0302//APID发送仪表遥测
#define T_APID_HYCT_FORE			0x0016//APID发送转发前向口补加数据
#define T_APID_HYCT_BACK			0x0016//APID发送转发后向口补加数据
#define T_APID_GNC					0x0306//APID发送转发GNC故检状态字
#define T_APID_MEMORY				0x0307//APID发送内存下传数据
#define T_APID_CODEFAULT			0x0304//APID发送故障代码

#define R_APID_TGTHT100				0x0306//APID接收推进遥测线路盒遥测
#define R_APID_TGTHT530				0x0306//APID接收压气机电机驱动器遥测
#define R_APID_TGTHT520a			0x0306//APID接收推进控制驱动器主机遥测
#define R_APID_TGTHT520b			0x0306//APID接收推进控制驱动器备机遥测
#define R_APID_HYCT_DATA1			0x0308//APID接收货船发送的补加状态信息（数据转换器1）
#define R_APID_HYCT_DATA2			0x0308//APID接收货船发送的补加状态信息（数据转换器2）
#define R_APID_KPU					0x0306//APID接收综合电子采集的推进传感器参数

 /*副导头定义，待修改-----------------------------------------------------*/
 
#define T_SUBSERVICE_CG 			0x0100//副导头，发送常规遥测
#define T_SUBSERVICE_GC				0x0100//副导头，发送工程遥测
#define T_SUBSERVICE_YB				0x0100//副导头，发送仪表遥测
#define T_SUBSERVICE_HYCT_FORE		0x0167//副导头，发送转发前向口补加数据
#define T_SUBSERVICE_HYCT_BACK		0x0168//副导头，发送转发后向口补加数据
#define T_SUBSERVICE_GNC			0x1060//副导头，发送转发GNC故检状态字
#define T_SUBSERVICE_MEMORY			0x0100//副导头，发送内存下传数据
#define T_SUBSERVICE_CODEFAULT		0x0100//副导头，发送故障代码

#define R_SUBSERVICE_TGTHT100_A		0x0160//副导头，接收推进遥测线路盒遥测
#define R_SUBSERVICE_TGTHT100_B		0x0166//副导头，接收推进遥测线路盒遥测

#define R_SUBSERVICE_TGTHT530		0x0165//副导头，接收压气机电机驱动器遥测
#define R_SUBSERVICE_TGTHT520a		0x0163//副导头，接收推进控制驱动器主机遥测
#define R_SUBSERVICE_TGTHT520b		0x0161//副导头，接收推进控制驱动器备机遥测
#define R_SUBSERVICE_HYCT_DATA1		0x0100//副导头，接收货船发送的补加状态信息（数据转换器1）
#define R_SUBSERVICE_HYCT_DATA2		0x0101//副导头，接收货船发送的补加状态信息（数据转换器2）
#define R_SUBSERVICE_KPU			0x0100//副导头，接收综合电子采集的推进传感器参数

 /*源包长度定义，待修改--------------------------------------------------------*/
 
 #define EPDU_LENGTH_TGTHT100		0x009f//推进遥测线路盒EPDU源包长度，159字
 #define EPDU_LENGTH_TGTHT530		0x001f//电机驱动器EPDU源包长度，32字
 #define EPDU_LENGTH_TGTHT520A		0x000c//推进控制驱动器主路EPDU源包长度，12字
 #define EPDU_LENGTH_TGTHT520B		0x000c//推进控制驱动器备路EPDU源包长度，12字
 #define EPDU_LENGTH_ERROR			0xefef//EPDU源包长度错误
 
 /*EPDU源包类型，待修改--------------------------------------------------------*/
 #define EPDU_TYPE_TGTHT100A 			0x0101//推进遥测线路盒EPDU源包复帧A
 #define EPDU_TYPE_TGTHT100B 			0x0202//推进遥测线路盒EPDU源包复帧B
 #define EPDU_TYPE_TGTHT530 			0x0303//电机驱动器EPDU源包
 #define EPDU_TYPE_TGTHT520A 			0x0404//推进控制驱动器主路EPDU源包
 #define EPDU_TYPE_TGTHT520B 			0x0505//推进控制驱动器备路EPDU源包
 #define EPDU_TYPE_ERROR				0x0606//EPDU源包类型错误
 
 /*注入指令类型，待修改--------------------------------------------------------*/
 #define INPUT_COMMAND_TYPE_POWER				0x0101//修改峰值功耗
 #define INPUT_COMMAND_TYPE_MULTI_CONTR_SPOT	0x0202//修改多个控温回路的控温点
 #define INPUT_COMMAND_TYPE_ALL_CONTR_SPOT		0x0303//修改全部控温回路的控温点
 #define INPUT_COMMAND_TYPE_ONE_MEA_SPOT		0x0404//修改某一控温回路的控温测点
 #define INPUT_COMMAND_TYPE_ONE_FIXED			0x0505//指定某一控温回路按照指定占空比输出
 #define INPUT_COMMAND_TYPE_ALL_RESUME			0x0606//恢复所有控温回路控温状态
 #define INPUT_COMMAND_TYPE_SOURCE				0x0707//指定控温参数来源选用
 #define INPUT_COMMAND_TYPE_PLACE_SIGNAL_EN		0x0808//指定某一路贮箱到位信号使能
 #define INPUT_COMMAND_TYPE_PLACE_SIGNAL_DIS	0x0909//指定某一路贮箱到位信号禁止
 #define INPUT_COMMAND_TYPE_FAULT_EN			0x0a0a//指定某一路故检使能
 #define INPUT_COMMAND_TYPE_FAULT_DIS			0x0b0b//指定某一路故检禁止
 #define INPUT_COMMAND_TYPE_SUPPLY_STAGE		0x0c0c//补加阶段注入
 #define INPUT_COMMAND_TYPE_SUPPLY_PARA			0x0d0d//补加参数注入
 #define INPUT_COMMAND_TYPE_EXHAUST				0x0e0e//注入检漏气体排放时间
 #define INPUT_COMMAND_TYPE_MAX_COMP			0x0f0f//注入最大抽气时间
 #define INPUT_COMMAND_TYPE_MAX_VELOCITY		0x1010//注入最大补加速率
 #define INPUT_COMMAND_TYPE_MIN_VELOCITY		0x1111//注入最小补加速率
 #define INPUT_COMMAND_TYPE_MAX_FLOW			0x1212//注入最大补加流动时间
 #define INPUT_COMMAND_TYPE_TEMP_CONTR_MODE		0x1313//注入补加管路温度控制模式
 #define INPUT_COMMAND_TYPE_COMP_START_MIN		0x1414//注入压气机启动温度下限
 #define INPUT_COMMAND_TYPE_COMP_START_MAX		0x1515//注入压气机启动温度上限
 #define INPUT_COMMAND_TYPE_COMP_ALARM			0x1616//注入压气机报警温度阈值
 #define INPUT_COMMAND_TYPE_COM_COOLER			0x1717//注入压气机与液冷温度差值
 #define INPUT_COMMAND_TYPE_COMP_PRESSURE		0x1818//注入压气机正常出口压力
 #define INPUT_COMMAND_TYPE_COMP_STOP_PRE		0x1919//注入压气机停机后出口压力值
 #define INPUT_COMMAND_TYPE_DP_HIGH				0x1a1a//注入高压压力变化幅值
 #define INPUT_COMMAND_TYPE_DP1_LOW				0x1b1b//注入低压压力变化幅值1
 #define INPUT_COMMAND_TYPE_DP2_LOW				0x1c1c//注入低压压力变化幅值2
 #define INPUT_COMMAND_TYPE_MAX_REPRESS			0x1d1d//注入最大复压时间
 #define INPUT_COMMAND_TYPE_COMP_START_SPEED	0x1e1e//注入压气机启动转速
 #define INPUT_COMMAND_TYPE_COMP_STOP_SPEED		0x1f1f//注入压气机停机转速
 #define INPUT_COMMAND_TYPE_DELAY_SHORT			0x2020//注入修改短延时
 #define INPUT_COMMAND_TYPE_DELAY_LONG			0x2121//注入修改长延时
 #define INPUT_COMMAND_TYPE_BYPATH_TIME			0x2222//注入修改旁路阀开启时间
 #define INPUT_COMMAND_TYPE_EPS1				0x2323//注入修改偏差eps1
 #define INPUT_COMMAND_TYPE_EPS2				0x2424//注入修改偏差eps2
 #define INPUT_COMMAND_TYPE_IN_COMP_MAX			0x2525//注入修改压气机最大进口压力
 #define INPUT_COMMAND_TYPE_IN_COMP_MIN			0x2626//注入修改压气机最小进口压力
 #define INPUT_COMMAND_TYPE_OUT_COMP_MIN		0x2727//注入修改压气机最小出口压力
 #define INPUT_COMMAND_TYPE_HYCT				0x2828//注入修改货船额定增压压力
 #define INPUT_COMMAND_TYPE_SENSOR_PIPE_F		0x2929//注入修改燃补加液路压力传感器设定
 #define INPUT_COMMAND_TYPE_SENSOR_PIPE_O		0x2a2a//注入修改氧补加液路压力传感器设定
 #define INPUT_COMMAND_TYPE_SENSOR_TANK_F		0x2b2b//注入修改燃贮箱压力传感器设定
 #define INPUT_COMMAND_TYPE_SENSOR_TANK_O		0x2c2c//注入修改氧贮箱压力传感器设定
 #define INPUT_COMMAND_TYPE_SENSOR_IN_COMP		0x2d2d//注入修改压气机进口压力传感器设定
 #define INPUT_COMMAND_TYPE_SENSOR_LOW_PIPE		0x2e2e//注入修改低压气路压力传感器设定
 #define INPUT_COMMAND_TYPE_SUPPLY_CONTINUE_G	0x2f2f//注入指定补加步骤继续补加
 #define INPUT_COMMAND_TYPE_AUTO_RESUME			0x3030//恢复某一控温回路为自动控温状态
 #define INPUT_COMMAND_TYPE_EQU_COMMAND			0x3131//注入设备管理指令
 #define INPUT_COMMAND_TYPE_HEAT_ON				0x3232//注入加热器通指令
 
 #define INPUT_COMMAND_TYPE_SUPPLY_PAUSE		0x3333//注入补加暂停指令
 #define INPUT_COMMAND_TYPE_SUPPLY_BREAK		0x3434//注入补加中止指令
 #define INPUT_COMMAND_TYPE_SUPPLY_CONTINUE		0x3535//注入补加继续指令

 #define INPUT_COMMAND_TYPE_CPU_SET				0x3636//注入CPU状态置位指令
 #define INPUT_COMMAND_TYPE_SUPPLY_LEAK			0x3737//注入检漏排气指令
 #define INPUT_COMMAND_TYPE_STAGE_FAULT			0x3838//注入阶段故检状态设置
 
 #define INPUT_COMMAND_TYPE_COMPRESSOR_FLAG		0x3939//注入压气机使用标志，测试指令


 
 #define INPUT_COMMAND_TYPE_ERROR				0xefff//注入指令类型非法

 
/*注入指令长度，即EPDU包全包长度，单位为字-----------------------------------------------*/
 
 #define INPUT_COMMAND_LEN_POWER				0x0007//修改峰值功耗
 //#define INPUT_COMMAND_LEN_MULTI_CONTR_SPOT		0x0202//修改多个控温回路的控温点
 #define INPUT_COMMAND_LEN_ALL_CONTR_SPOT		0x0009//修改全部控温回路的控温点
 #define INPUT_COMMAND_LEN_ONE_MEA_SPOT			0x000e//修改某一控温回路的控温测点
 #define INPUT_COMMAND_LEN_ONE_FIXED			0x0008//指定某一控温回路按照指定占空比输出
 #define INPUT_COMMAND_LEN_ALL_RESUME			0x0007//恢复所有控温回路控温状态
 #define INPUT_COMMAND_LEN_SOURCE				0x0007//指定控温参数来源选用
 #define INPUT_COMMAND_LEN_PLACE_SIGNAL_EN		0x0007//指定某一路贮箱到位信号使能
 #define INPUT_COMMAND_LEN_PLACE_SIGNAL_DIS		0x0007//指定某一路贮箱到位信号禁止
 #define INPUT_COMMAND_LEN_FAULT_EN				0x0007//指定某一路故检使能
 #define INPUT_COMMAND_LEN_FAULT_DIS			0x0007//指定某一路故检禁止
 #define INPUT_COMMAND_LEN_SUPPLY_STAGE			0x0007//补加阶段注入
 #define INPUT_COMMAND_LEN_SUPPLY_PARA			0x0026//补加参数注入
 #define INPUT_COMMAND_LEN_EXHAUST				0x0007//注入检漏气体排放时间
 #define INPUT_COMMAND_LEN_MAX_COMP				0x0008//注入最大抽气时间
 #define INPUT_COMMAND_LEN_MAX_VELOCITY			0x0007//注入最大补加速率
 #define INPUT_COMMAND_LEN_MIN_VELOCITY			0x0007//注入最小补加速率
 #define INPUT_COMMAND_LEN_MAX_FLOW				0x0007//注入最大补加流动时间
 #define INPUT_COMMAND_LEN_TEMP_CONTR_MODE		0x0007//注入补加管路温度控制模式
 #define INPUT_COMMAND_LEN_COMP_START_MIN		0x0007//注入压气机启动温度下限
 #define INPUT_COMMAND_LEN_COMP_START_MAX		0x0007//注入压气机启动温度上限
 #define INPUT_COMMAND_LEN_COMP_ALARM			0x0007//注入压气机报警温度阈值
 #define INPUT_COMMAND_LEN_COM_COOLER			0x0007//注入压气机与液冷温度差值
 #define INPUT_COMMAND_LEN_COMP_PRESSURE		0x0007//注入压气机正常出口压力
 #define INPUT_COMMAND_LEN_COMP_STOP_PRE		0x0007//注入压气机停机后出口压力值
 #define INPUT_COMMAND_LEN_DP_HIGH				0x0007//注入高压压力变化幅值
 #define INPUT_COMMAND_LEN_DP1_LOW				0x0007//注入低压压力变化幅值1
 #define INPUT_COMMAND_LEN_DP2_LOW				0x0007//注入低压压力变化幅值2
 #define INPUT_COMMAND_LEN_MAX_REPRESS			0x0007//注入最大复压时间
 #define INPUT_COMMAND_LEN_COMP_START_SPEED		0x0007//注入压气机启动转速
 #define INPUT_COMMAND_LEN_COMP_STOP_SPEED		0x0007//注入压气机停机转速
 #define INPUT_COMMAND_LEN_DELAY_SHORT			0x0007//注入修改短延时
 #define INPUT_COMMAND_LEN_DELAY_LONG			0x0007//注入修改长延时
 #define INPUT_COMMAND_LEN_BYPATH_TIME			0x0007//注入修改旁路阀开启时间
 #define INPUT_COMMAND_LEN_EPS1					0x0007//注入修改偏差eps1
 #define INPUT_COMMAND_LEN_EPS2					0x0007//注入修改偏差eps2
 #define INPUT_COMMAND_LEN_IN_COMP_MAX			0x0007//注入修改压气机最大进口压力
 #define INPUT_COMMAND_LEN_IN_COMP_MIN			0x0007//注入修改压气机最小进口压力
 #define INPUT_COMMAND_LEN_OUT_COMP_MIN			0x0007//注入修改压气机最小出口压力
 #define INPUT_COMMAND_LEN_HYCT					0x0007//注入修改货船额定增压压力
 #define INPUT_COMMAND_LEN_SENSOR_PIPE_F		0x0007//注入修改燃补加液路压力传感器设定
 #define INPUT_COMMAND_LEN_SENSOR_PIPE_O		0x0007//注入修改氧补加液路压力传感器设定
 #define INPUT_COMMAND_LEN_SENSOR_TANK_F		0x0007//注入修改燃贮箱压力传感器设定
 #define INPUT_COMMAND_LEN_SENSOR_TANK_O		0x0007//注入修改氧贮箱压力传感器设定
 #define INPUT_COMMAND_LEN_SENSOR_IN_COMP		0x0007//注入修改压气机进口压力传感器设定
 #define INPUT_COMMAND_LEN_SENSOR_LOW_PIPE		0x0007//注入修改低压气路压力传感器设定
 #define INPUT_COMMAND_LEN_SUPPLY_CONTINUE_G	0x0008//注入指定补加步骤继续补加
 #define INPUT_COMMAND_LEN_AUTO_RESUME			0x0007//恢复某一控温回路为自动控温状态
 #define INPUT_COMMAND_LEN_EQU_COMMAND			0x0007//注入设备管理指令
 #define INPUT_COMMAND_LEN_HEAT_ON				0x0007//注入加热器通指令
 
 #define INPUT_COMMAND_LEN_SUPPLY_PAUSE			0x0007//注入补加暂停指令
 #define INPUT_COMMAND_LEN_SUPPLY_BREAK			0x0007//注入补加中止指令
 #define INPUT_COMMAND_LEN_SUPPLY_CONTINUE		0x0007//注入补加继续指令
 
 #define INPUT_COMMAND_LEN_CPU_SET				0x0007//注入CPU状态置位指令
 #define INPUT_COMMAND_LEN_SUPPLY_LEAK			0x0007//注入检漏排气指令
 #define INPUT_COMMAND_LEN_STAGE_FAULT			0x0007//注入阶段故检状态设置
 
 #define INPUT_COMMAND_LEN_COMPRESSOR_FLAG		0x0007//注入压气机使用标志，测试指令

 
 #define INPUT_COMMAND_LEN_UNKNOW				0xdfff//注入指令类型非法
 

/*注入指令常规遥测状态 宏定义--------------------------------------------------------*/

 #define INPUT_COMMAND_EPDU_NUM_ERROR			0xaaaa
 #define INPUT_COMMAND_EPDU_DEAL_ERROR			0xbbbb
 
 
/*总线指令，继电器动作，待修改--------------------------------------------------------*/
 
 #define BUS_RELAY_BASE_ADDRESS					(uint32)0x25800000
 
 #define BUS_RELAY_HEATER_ON_BASE_ADDRESS		(uint32)0x25800004
 
 #define BUS_MAIN_HEATER_POWER_ON				0xe1e1//推进主份加热器供电通
 #define BUS_MAIN_HEATER_POWER_OFF				0xe2e2//推进主份加热器供电断
 #define BUS_LESS_HEATER_POWER_ON				0xe3e3//推进备份加热器供电通
 #define BUS_LESS_HEATER_POWER_OFF				0xe4e4//推进备份加热器供电断
 
 #define BUS_COOLER_1_MAIN_POWER_ON				0xe5e5//液冷模块I主泵供电通
 #define BUS_COOLER_1_LESS_POWER_ON				0xe6e6//液冷模块I备泵供电通
 #define BUS_COOLER_1_POWER_OFF					0xe7e7//液冷模块I主、备泵供电断
 #define BUS_COOLER_2_MAIN_POWER_ON				0xe8e8//液冷模块II主泵供电通
 #define BUS_COOLER_2_LESS_POWER_ON				0xe9e9//液冷模块II备泵供电通
 #define BUS_COOLER_2_POWER_OFF					0xeaea//液冷模块II主、备泵供电断
 
 //-----------------------------------掩码--------------------------------------------------
 #define BUS_MAIN_HEATER_POWER_OFF_AND			0xbfff//推进主份加热器供电断，控制掩码
 #define BUS_MAIN_HEATER_POWER_OFF_OR			0x8000//推进主份加热器供电断，控制掩码
 //bit15为1，bit14为0
 
 #define BUS_MAIN_HEATER_POWER_ON_AND			0xbfff//推进主份加热器供电通，控制掩码
 #define BUS_MAIN_HEATER_POWER_ON_OR			0x8000//推进主份加热器供电通，控制掩码
 //bit15为1，bit14为0
 
 #define BUS_LESS_HEATER_POWER_OFF_AND			0xffbf//推进备份加热器供电断，控制掩码
 #define BUS_LESS_HEATER_POWER_OFF_OR			0x0080//推进备份加热器供电断，控制掩码
 //bit7为1，bit6为0
 
 #define BUS_LESS_HEATER_POWER_ON_AND			0xefff//推进备份加热器供电通，控制掩码
 #define BUS_LESS_HEATER_POWER_ON_OR			0x2000//推进备份加热器供电通，控制掩码
 //bit13为1，bit12为0
 
 #define BUS_COOLER_1_MAIN_POWER_ON_AND			0xefff//液冷模块I主泵供电通，控制掩码
 #define BUS_COOLER_1_MAIN_POWER_ON_OR			0x2000//液冷模块I主泵供电通，控制掩码
 //bit13为1，bit12为0
 
 #define BUS_COOLER_1_LESS_POWER_ON_AND			0xfbff//液冷模块I备泵供电通，控制掩码
 #define BUS_COOLER_1_LESS_POWER_ON_OR			0x0800//液冷模块I备泵供电通，控制掩码
 //bit11为1，bit10为0
 
 #define BUS_COOLER_1_POWER_OFF_AND				0xfeff//液冷模块I主、备泵供电断，控制掩码
 #define BUS_COOLER_1_POWER_OFF_OR				0x0200//液冷模块I主、备泵供电断，控制掩码
 //bit9为1，bit8为0
 
 #define BUS_COOLER_2_MAIN_POWER_ON_AND			0xffef//液冷模块II主泵供电通，控制掩码
 #define BUS_COOLER_2_MAIN_POWER_ON_OR			0x0020//液冷模块II主泵供电通，控制掩码
 //bit5为1，bit4为0
 
 #define BUS_COOLER_2_LESS_POWER_ON_AND			0xfffb//液冷模块II备泵供电通，控制掩码
 #define BUS_COOLER_2_LESS_POWER_ON_OR			0x0008//液冷模块II备泵供电通，控制掩码
 //bit3为1，bit2为0
 
 #define BUS_COOLER_2_POWER_OFF_AND				0xfffe//液冷模块II主、备泵供电断，控制掩码
 #define BUS_COOLER_2_POWER_OFF_OR				0x0002//液冷模块II主、备泵供电断，控制掩码
 //bit1为1，bit0为0
 
 /*总线通讯状态 宏定义-----------------------------------------------------------*/

 #define MESSAGE_STATE_MAX_COUNT				0x0003	//超时时间计数门槛值，约1.5s
 
 #define MESSAGE_STATE_VALIDITY_TRUE			0xaaaa	//数据内容接收有效
 #define MESSAGE_STATE_VALIDITY_FALSE			0x5555	//数据内容接收无效
 #define MESSAGE_STATE_VALIDITY_UNKNOW			0x55aa	//数据内容有效性未知
 
 #define MESSAGE_STATE_NORMAL					0x4e	//通讯正常
 #define MESSAGE_STATE_ABNORMAL					0x6f	//通讯超时
 #define MESSAGE_STATE_R_ERROR					0xaa	//通讯接收数据错误
 
 
/*注入设备管理指令 宏定义-----------------------------------------------------------*/

#define INPUT_COMMAND_TYPE_TGTHT530a_ON_POWER 		0xa1a1
#define INPUT_COMMAND_TYPE_TGTHT530b_ON_POWER 		0xa2a2
#define INPUT_COMMAND_TYPE_TGTHT530c_ON_POWER 		0xa3a3
#define INPUT_COMMAND_TYPE_TGTHT530a_OFF_POWER 		0xa4a4
#define INPUT_COMMAND_TYPE_TGTHT530b_OFF_POWER 		0xa5a5
#define INPUT_COMMAND_TYPE_TGTHT530c_OFF_POWER 		0xa6a6
#define INPUT_COMMAND_TYPE_COMPRESS_A_ON_POWER 		0xa7a7
#define INPUT_COMMAND_TYPE_COMPRESS_B_ON_POWER 		0xa8a8
#define INPUT_COMMAND_TYPE_COMPRESS_C_ON_POWER 		0xa9a9
#define INPUT_COMMAND_TYPE_COMPRESS_A_OFF_POWER 	0xaaaa
#define INPUT_COMMAND_TYPE_COMPRESS_B_OFF_POWER		0xabab
#define INPUT_COMMAND_TYPE_COMPRESS_C_OFF_POWER 	0xacac
#define INPUT_COMMAND_TYPE_COMPRESS_A_START 		0xadad
#define INPUT_COMMAND_TYPE_COMPRESS_B_START 		0xaeae
#define INPUT_COMMAND_TYPE_COMPRESS_C_START 		0xafaf
#define INPUT_COMMAND_TYPE_COMPRESS_A_STOP 			0xb0b0
#define INPUT_COMMAND_TYPE_COMPRESS_B_STOP 			0xb1b1
#define INPUT_COMMAND_TYPE_COMPRESS_C_STOP 			0xb2b2
#define INPUT_COMMAND_TYPE_VALVE_SUPPLY_ON_POWER 	0xb3b3
#define INPUT_COMMAND_TYPE_VALVE_SUPPLY_OFF_POWER 	0xb4b4
#define INPUT_COMMAND_TYPE_LVt1K					0xb5b5
#define INPUT_COMMAND_TYPE_LVt1G					0xb6b6
#define INPUT_COMMAND_TYPE_LVt6K					0xb7b7
#define INPUT_COMMAND_TYPE_LVt6G					0xb8b8

 
 
/*1553B总线处理模块函数声明---------------------------------------------------*/


#ifdef TEST_VERSION

void TGTHT510_1553b_transmitcommand_test_FM_state(uint16 which_bu65170);

#endif


void TGTHT510_1553b_initial(void);
uint16 TGTHT510_1553b_wait_for_fpga(uint16 which_bu65170);
uint16 TGTHT510_1553b_get_data(uint16 which_bu65170,uint32 base_address,uint16 *buf,uint16 len);
uint16 TGTHT510_1553b_set_data(uint16 which_bu65170,uint32 base_address,uint16 *buf,uint16 len);
void TGTHT510_1553b_receiveANDtransmitdata(uint16 which_bu65170);
void TGTHT510_1553b_message_state_dealing(void);
void TGTHT510_1553b_message_count_update(void);
uint16 TGTHT510_which_bus_choice(void);
void TGTHT510_1553b_main(void);	
void TGTHT510_1553b_dealing(uint16 which_bu65170);	
void TGTHT510_1553b_transmitdata_CGandGC(uint16 which_bu65170);
void TGTHT510_1553b_transmitdata_YBYC(uint16 which_bu65170);
void TGTHT510_1553b_transmitdata_HYCT1100(uint16 which_bu65170);
void TGTHT510_1553b_transmitdata_GNC(uint16 which_bu65170);
void TGTHT510_1553b_transmitdata_MEMORY(uint16 which_bu65170);

void TGTHT510_1553b_transmitdata_askforserive(uint16 which_bu65170);

void TGTHT510_1553b_transmitcommand_equiment(uint16 which_bu65170);
uint8 TGTHT510_1553b_receivedata_subsystem_EPDU_sum_get(uint16 type,uint16 *p,uint16 length);
uint8 TGTHT510_1553b_receivedata_subsystem_EPDU_sum_calculate(uint16 type,uint16 *p,uint16 size);
uint16 TGTHT510_1553b_receivedata_subsystem_EPDU_length_generate(uint16 type);
void TGTHT510_1553b_receivedata_subsystem_buffer(uint16 type,uint16 *p,uint16 length);
uint16 TGTHT510_1553b_receivedata_subsystem_save_EPDU(uint16 type,uint16 start_i,uint16 which_bu65170);
void TGTHT510_1553b_receivedata_subsystem(uint16 which_bu65170);
uint16 TGTHT510_1553b_receivecommand_buscommand_ISO_calculate(uint16 *p,uint16 size);
uint16 TGTHT510_1553b_receivecommand_buscommand_is_correct(uint16 *p);
void TGTHT510_1553b_receivecommand_buscommand_code_dealing(uint8 code);
void TGTHT510_1553b_receivecommand_buscommand(uint16 which_bu65170);
uint16 TGTHT510_1553b_receivecommand_inputcommand_CRC_calculate(TGTHT510_1553B_inputcommand_TypeDef a);
uint16 TGTHT510_1553b_receivecommand_inputcommand_is_correct(TGTHT510_1553B_inputcommand_TypeDef a);
TGTHT510_1553B_inputcommand_TypeDef TGTHT510_1553b_receivecommand_inputcommand_save(uint16 which_bu65170);
uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_dealing(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_is_correct(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i,uint16 length);
uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_length_get(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_length_type_judge(uint16 type);
void TGTHT510_1553b_receivecommand_inputcommand_dealing(TGTHT510_1553B_inputcommand_TypeDef a);
void TGTHT510_1553b_receivecommand_inputcommand(uint16 which_bu65170);
void TGTHT510_1553b_receivedata_HYCT1100(uint16 which_bu65170,uint16 type);

void TGTHT510_1553b_receivedata_KPU(uint16 which_bu65170);

void TGTHT510_1553b_receivecommand_interactivecommand(uint16 which_bu65170);
void TGTHT510_1553b_relay_dealing(uint16 code);

void TGTHT510_1553b_inputcommand_dealing_power(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_multi_contr_spot(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_all_contr_spot(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_one_mea_spot(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_one_fixed(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_auto_resume(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_all_resume(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_source(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_place_signal_en(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_place_signal_dis(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_fault_en(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_fault_dis(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_supply_stage(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_supply_para(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_exhaust(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_max_comp(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_max_velocity(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_min_velocity(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_max_flow(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_temp_contr_mode(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_start_min(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_start_max(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_alarm(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_cooler(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_comp_pressure(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_stop_pre(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_dp_high(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_dp1_low(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_dp2_low(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_max_repress(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_start_speed(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_stop_speed(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_delay_short(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_delay_long(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_time_bypath(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_eps1(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_eps2(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_pressure_comp_in_max(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_pressure_comp_in_min(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_pressure_comp_out_min(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_pressure_hyc(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_sensor_pipe_F(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_sensor_pipe_O(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_sensor_tank_F(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_sensor_tank_O(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_sensor_comp_in(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_sensor_pipe_low(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_supply_continue_g(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_equ_command(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_heat_on(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_supply_pause(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_supply_break(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_supply_continue(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_cpu_set(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_leak(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_stage_fault(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_compressor_flag_set(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);


 
 #endif
