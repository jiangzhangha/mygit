/**
  ******************************************************************************
  * @file    TGTHT510_1553b.c
  * @author  蒋章
  * @version V1.00
  * @date    20150626
  * @brief   空间站核心舱推进管理器1553B总线处理模块C文件
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"
#include "BM3803MG.h"

/*全局变量---------------------------------------------------------------*/		

extern struct lregs * regs;

uint16 is_wait_overtime;//标识等待FPGA时间是否超时。

TGTHT510_1553B_Subaddress_flag_TypeDef TGTHT510_1553B_Subaddress_flag;	//1553B子地址堆栈查询标志结构体			

TGTHT510_1553B_message_state_TypeDef TGTHT510_1553B_message_state;		//总线通讯状态数据格式

TGTHT510_which_bus_TypeDef TGTHT510_which_bus;//总线切换全局变量

TGTHT510_1553B_service_flag_TypeDef TGTHT510_1553B_service_flag;

//------------------------------------测试-------------------------------------
extern uint16 CG_supply_information_realtime_state_data[]; //实时补加信息

//------------------------------------测试-------------------------------------

extern compressor_state_TypeDef compressor_state;
extern TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;

extern valvecontrol_TypeDef TGTHT510_valvecontrol_struct;				//阀门控制结构体
extern Temperature_control_block_TypeDef Temperature_control_block[];	//共50路控温回路
extern Temperature_control_global_TypeDef Temperature_control_global;	//温度控制全局变量

extern uint16 TGTHT510_1553B_data_MEMORY[];								//内存下传数据
extern uint16 TGTHT510_1553B_data_GNC[];								//送GNC故检参数，共7个字
extern uint16 TGTHT510_1553B_data_HYCT[];
extern uint16 TGTHT510_1553B_data_CG[];									//常规遥测数组，共135个字
extern uint16 TGTHT510_1553B_data_GC[];									//工程遥测数组，共32个字
extern uint16 TGTHT510_1553B_data_YB[];									//仪表遥测数组，共21个字
extern uint16 TGTHT510_1553B_data_equiment_command[];					//设备管理指令，共11个字
extern uint16 TGTHT510_1553B_data_ask_for_service;						//服务请求指令，共1个字

extern uint16 CG_inputcommand_receive_state_data[];						//注入指令接收状态,2个字
extern uint16 CG_equiment_receive_state_data[];							//设备间数据接收状态,6个字
extern TGTHT510_supply_input_par_TypeDef TGTHT510_supply_input_par;     //补加注入参数
extern TGTHT510_supply_ctrl_TypeDef TGTHT510_supply_ctrl;				//补加控制参数
extern uint16 tt[];
extern uint16 CG_valve_state_data[];    //缓存阀门开关状态
extern uint16 CG_bus_command[2];//接收总线指令，下传指令内容与校验和

uint16 TGTHT510_1553B_data_TGTHT100[89]={0x0000};					//全局数组，缓存推进遥测线路盒除温度参数以外数据，89字
uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[65]={0x0000};			//全局数组，缓存推进遥测线路盒复帧A温度数据，65字
uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[65]={0x0000};			//全局数组，缓存推进遥测线路盒复帧B温度数据，65字
uint16 TGTHT510_1553B_data_TGTHT530[13]={0x0000};					//全局数组，缓存压气机电机驱动器遥测数据，13字
uint16 TGTHT510_1553B_data_TGTHT520a[7]={0x0000};					//全局数组，缓存推进控制驱动器主机遥测，7字
uint16 TGTHT510_1553B_data_TGTHT520b[7]={0x0000};					//全局数组，缓存推进控制驱动器备机遥测，7字
uint16 TGTHT510_1553B_R_HYCT1100[32]={0x0000};						//全局数组，缓存货运飞船发送的遥测，25字，待修改

uint16 TGTHT510_1553B_R_HYCT1100_data1[32]={0x0000};				//全局数组，缓存货运飞船发送的遥测。数据转换器1
uint16 TGTHT510_1553B_R_HYCT1100_data2[32]={0x0000};				//全局数组，缓存货运飞船发送的遥测。数据转换器2

uint16 TGTHT510_1553B_data_KPU[105]={0x0000};						//全局数组，缓存综合电子采集的推进传感器数据


											  //0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
const uint8 TGTHT510_1553B_Bcommand_code[256]={	0x00,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,//0x00
												0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0x03,0x04,0x0F,0x10,0x1B,0x1C,0x1F,0x20,0x23,0x24,//0x01
												0x27,0x28,0x2B,0x2C,0x37,0x38,0x3B,0x3C,0x3F,0x40,0x43,0x44,0x47,0x48,0x4B,0x4C,//0x02
												0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0x34,0xAD,0xAE,0xAF,0xB0,0x4D,0x4E,0x51,0x52,//0x03
												0x55,0x56,0x59,0x5A,0x5D,0x5E,0x7D,0x7E,0x81,0x82,0x07,0x08,0x13,0x14,0x85,0x86,//0x04
												0x89,0x8A,0x95,0x96,0x9D,0x9E,0xA5,0xA6,0x4F,0x50,0x53,0x54,0x57,0x58,0x5B,0x5C,//0x05
												0x5F,0x60,0x7F,0x80,0x83,0x84,0x05,0x06,0x11,0x12,0x87,0x88,0x8B,0x8C,0x97,0x98,//0x06
												0x9F,0xA0,0xA7,0xA8,0x35,0x36,0x39,0x3A,0x3D,0x3E,0x41,0x42,0x45,0x46,0x49,0x4A,//0x07
												0x01,0x02,0x0D,0x0E,0x19,0x1A,0x1D,0x1E,0x21,0x22,0x25,0x26,0x29,0x2A,0x0B,0x0C,//0x08
												0x17,0x18,0x8D,0x8E,0x91,0x92,0x99,0x9A,0xA1,0xA2,0xA9,0xAA,0x61,0x62,0x65,0x66,//0x09
												0x69,0x6A,0x6D,0x6E,0x71,0x72,0x75,0x76,0x79,0x7A,0x63,0x64,0x67,0x68,0x6B,0x6C,//0x0A
												0x6F,0x70,0x73,0x74,0x77,0x78,0x7B,0x7C,0x09,0x0A,0x15,0x16,0x8F,0x90,0x93,0x94,//0x0B
												0x9B,0x9C,0xA3,0xA4,0xAB,0xAC,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,//0x0C
												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x0D
												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//0x0E
												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00//0x0F
	
};


/*-----------------------------------------------------------------------------------------------------------------------------

总线指令内部地址编码：

1、推进主份加热器供电通：0xB1
2、推进主份加热器供电断：0xB2
3、推进备份加热器供电通：0xB3
4、推进备份加热器供电断：0xB4
5、液冷模块I主泵供电通：0xB5
6、液冷模块I备泵供电通：0xB6
7、液冷模块I主、备泵供电断：0xB7
8、液冷模块II主泵供电通：0xB8
9、液冷模块II备泵供电通：0xB9
10、液冷模块II主、备泵供电断：0xBA
11、退出补加：0xBB
12、补加开始: 0xBC
13、补加中止：0xBD
14、补加完成：0xBE
15、补加暂停：0xBF
16、进入补加：0xC0
17、紧急退出补加：0xC1
18、手动补加指令1：0xC2
19、手动补加指令2：0xC3
20、接收数管参数使能：0xC4
21、补加继续：0xC5
22、推进故检使能：0xC6
23、推进故检禁止：0xC7
24、轨控限制功耗使能：0xC8
25、轨控限制功耗禁止：0xC9
26、补加热控使能：0xCA
27、补加热控禁止：0xCB
28、液冷工作使能：0xCC
29、液冷工作禁止：0xCD
30、使用遥测线路盒数据：0xCE
31、使用数管遥测数据：0xCF
32、阀门LVb1开、LVb1关……LVb87关、DVb1开、DVb1关：0x01~0xB0

------------------------------------------------------------------------------------------------------------------------------*/



/******************************************************************************************
**名称：1553B初始化函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

  
void TGTHT510_1553b_initial(void)
{
	
	is_wait_overtime=FALSE;
	
/*子地址状态标志查询结构体初始化-----------------------------------------------*/

#ifdef TEST_VERSION
	TGTHT510_1553B_Subaddress_flag.Subaddress_05_flag=FALSE;
#endif

	TGTHT510_1553B_Subaddress_flag.Subaddress_11_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_12_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_13_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_17_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_19_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_21_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_23_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_28_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_14_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_15_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_16_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_18_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_20_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_22_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Subaddress_29_flag=FALSE;
	TGTHT510_1553B_Subaddress_flag.Current_Stack_Pointer=0xfc;

/*总线通讯状态结构体初始化-----------------------------------------------*/
	TGTHT510_1553B_message_state.CG_GC_message_count_Z=0x0000;
	TGTHT510_1553B_message_state.CG_GC_message_count_B=0x0000;
	TGTHT510_1553B_message_state.YB_message_count=0x0000;
	TGTHT510_1553B_message_state.HYCT1100_T_message_count=0x0000;
	TGTHT510_1553B_message_state.TGTHT100_message_count=0x0000;
	TGTHT510_1553B_message_state.TGTHT520a_message_count=0x0000;
	TGTHT510_1553B_message_state.TGTHT520b_message_count=0x0000;
	TGTHT510_1553B_message_state.TGTHT530_message_count=0x0000;
	TGTHT510_1553B_message_state.HYCT1100_R_message_count=0x0000;
	TGTHT510_1553B_message_state.KPU_message_count=0x0000;
	
	TGTHT510_which_bus.count=0x0000;
	TGTHT510_which_bus.last_use_BU65170=BU65170_Z;
	
	TGTHT510_1553B_message_state.TGTHT100_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	TGTHT510_1553B_message_state.TGTHT520a_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	TGTHT510_1553B_message_state.TGTHT520b_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	TGTHT510_1553B_message_state.TGTHT530_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	TGTHT510_1553B_message_state.HYCT1100_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	TGTHT510_1553B_message_state.KPU_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	
	TGTHT510_1553B_service_flag.Subaddress_11_service_flag=FALSE;
	TGTHT510_1553B_service_flag.Subaddress_12_service_flag=FALSE;
	TGTHT510_1553B_service_flag.Subaddress_13_service_flag=FALSE;
	TGTHT510_1553B_service_flag.Subaddress_17_service_flag=FALSE;
	TGTHT510_1553B_service_flag.Subaddress_19_service_flag=FALSE;
	TGTHT510_1553B_service_flag.Subaddress_21_service_flag=FALSE;
	TGTHT510_1553B_service_flag.Subaddress_23_service_flag=FALSE;
	TGTHT510_1553B_service_flag.Subaddress_28_service_flag=FALSE;
	TGTHT510_1553B_service_flag.Subaddress_14_service_flag=FALSE;
	TGTHT510_1553B_service_flag.Subaddress_15_service_flag=FALSE;
	TGTHT510_1553B_service_flag.Subaddress_16_service_flag=FALSE;
	TGTHT510_1553B_service_flag.Subaddress_18_service_flag=FALSE;
	TGTHT510_1553B_service_flag.Subaddress_20_service_flag=FALSE;
	TGTHT510_1553B_service_flag.Subaddress_22_service_flag=FALSE;
	
}


/******************************************************************************************
**名称：延时等待FPGA读写时机，可读，返回TRUE，否则返回FALSE
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_1553b_wait_for_fpga(uint16 which_bu65170)
{
	uint16 flag;
	
	flag=BU65170_READ_NOT_ALLOW;
	
	while(flag!=BU65170_READ_ALLOW)
	{
		if(which_bu65170==BU65170_Z)//读取主份BU65170数据
		{
			flag=Read_32_to_16(*(volatile uint32 *)BU65170_Z_STATUS_REG);
		}
		
		else if(which_bu65170==BU65170_B)//读取备份BU65170数据
		{
			flag=Read_32_to_16(*(volatile uint32 *)BU65170_B_STATUS_REG);
		}
		
		else
		{
			return FALSE;
		}
		
		/*
		if(is_wait_overtime==TRUE)//判断是否超时
		{
			is_wait_overtime=FALSE;
			return FALSE;
		}
		
		
		
		else
		{
			asm("nop;");
		}
		*/
		
	}
	
	return TRUE;

	
}

/******************************************************************************************
**名称：读取缓存数据分函数，读取正确，返回TRUE，否则返回FALSE
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_1553b_get_data(uint16 which_bu65170,uint32 base_address,uint16 *buf,uint16 len)
{
	uint16 i;
	uint32 address;
	uint16 high;
	uint16 low;
	
	if(len==0)
	{
		return FALSE;
	}
	address=base_address;
	
	if(TGTHT510_1553b_wait_for_fpga(which_bu65170)==TRUE)
	{
		for(i=0;i<=2*len-1;i++)
		{
			if((i&0x0001)==0x0000)
			{
				low=Read_32_to_16(*(volatile uint32 *)address);
			}
			
			else
			{
				high=Read_32_to_16(*(volatile uint32 *)address);
				
				buf[(i-1)>>1]=((high&0xff00)|(low>>8));
			}
			
			address=address+4;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}



/******************************************************************************************
**名称：发送数据分函数，发送正确，返回TRUE，否则返回FALSE
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_1553b_set_data(uint16 which_bu65170,uint32 base_address,uint16 *buf,uint16 len)
{
	uint16 i;
	uint32 address;
	if(len==0)
	{
		return FALSE;
	}
	address=base_address;
	if(TGTHT510_1553b_wait_for_fpga(which_bu65170)==TRUE)
	{
		for(i=0;i<=len-1;i++)
		{
			*(volatile uint32 *)address=Write_16_to_32(buf[i]);
			
			address=address+4;
		}
	}
	
	else
	{
		return FALSE;
	}
	
	return TRUE;
}


/******************************************************************************************
**名称：1553B指令堆栈查询巡检函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_receiveANDtransmitdata(uint16 which_bu65170)
{
	uint16 stack_pointer;
	
	uint16 command,subaddress;
	
	uint16 stack[256];
	
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_STACK_POINTER,&stack_pointer,BU65170_R_STACK_POINTER_LEN)==FALSE)
		{
			return;
		}
		
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_STACK_DATA,stack,BU65170_R_STACK_DATA_LEN)==FALSE)
		{
			return;
		}
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_STACK_POINTER,&stack_pointer,BU65170_R_STACK_POINTER_LEN)==FALSE)
		{
			return;
		}
		
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_STACK_DATA,stack,BU65170_R_STACK_DATA_LEN)==FALSE)
		{
			return;
		}
		
	}
	
	else
	{
		return;
		
	}

	if((uint8)stack_pointer>=0xfd)//堆栈指针不可能为大于0xfd
	{
		return;
	}
	
	while(TGTHT510_1553B_Subaddress_flag.Current_Stack_Pointer!=(uint8)stack_pointer)
	{
		TGTHT510_1553B_Subaddress_flag.Current_Stack_Pointer=TGTHT510_1553B_Subaddress_flag.Current_Stack_Pointer+4;
		
		command=stack[TGTHT510_1553B_Subaddress_flag.Current_Stack_Pointer+3];
		
		subaddress=(command>>5)&0x001F;//提取指令字中的子地址数据
		
		switch(subaddress)
		{
			#ifdef TEST_VERSION
			
			case 05://发送测试件 阀门状态数据
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_05_flag=TRUE;
				break;
			}
			
			#endif
			
			case 11://发送工程遥测与常规遥测
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_11_flag=TRUE;
				
				TGTHT510_which_bus.count=0;
				
				break;
			}
			
			case 12://发送设备管理指令
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_12_flag=TRUE;
				break;
			}
			
			case 13://发送仪表遥测
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_13_flag=TRUE;
				break;
			}
			
			case 17://发送转发前（后）向口补加数据 复帧
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_17_flag=TRUE;
				break;
			}
			
			case 19://发送转GNC故检状态字
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_19_flag=TRUE;
				break;
			}
			
			case 21://发送内存下传数据
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_21_flag=TRUE;
				break;
			}
			
			case 23://发送故障代码
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_23_flag=TRUE;
				break;
			}
			
			case 28://发送服务请求
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_28_flag=TRUE;
				break;
			}
			
			case 14://接收遥测线路盒，推进控制驱动器，压气机电机驱动器遥测数据
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_14_flag=TRUE;
				break;
			}
			
			case 15://接收总线指令与手控指令
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_15_flag=TRUE;
				break;
			}
			
			case 16://接收注入指令
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_16_flag=TRUE;
				break;
			}
			
			case 18://接受货船发送补加信息（数据转换器1）
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_18_flag=TRUE;
				break;
			}
			
			case 20://接受货船发送补加信息（数据转换器2）
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_20_flag=TRUE;
				break;
			}
			
			case 22://接受综合电子采集的推进传感器参数
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_22_flag=TRUE;
				break;
			}
			
			case 29://接收勤务指令
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_29_flag=TRUE;
				break;
			}
			
			default:break;
					
		}
	}	
}




/******************************************************************************************
**名称：总线通讯状态处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
1、设备间数据接收状态共6个字，即12字节，作为常规遥测下传地面；
2、CG_equiment_receive_state_data[0]的高字节缓存常规与工程遥测通讯状态；
3、CG_equiment_receive_state_data[0]的低字节缓存仪表遥测通讯状态；
4、CG_equiment_receive_state_data[1]的高字节缓存发送货船补加数据通讯状态；
5、CG_equiment_receive_state_data[1]的低字节缓存推进遥测线路盒通讯状态；
6、CG_equiment_receive_state_data[2]的高字节缓存推进控制驱动器A机通讯状态；
7、CG_equiment_receive_state_data[2]的低字节缓存推进控制驱动器B机通讯状态；
8、CG_equiment_receive_state_data[3]的高字节缓存压气机电机驱动器通讯状态；
9、CG_equiment_receive_state_data[3]的低字节缓存接收货船补加信息数据通讯状态；
10、CG_equiment_receive_state_data[4]的高字节缓存数管遥测通讯状态；
11、通讯超时为6FH；
12、通讯正常为4EH；
13、通讯数据接收错误为AAH；

-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_message_state_dealing(void)
{
	uint16 i;
	uint16 j;
	uint16 temp[6];
	
	for(i=0;i<=5;i++)
	{
		temp[i]=0x0000;
	}
	
//-----常规遥测与工程遥测---------------------------------------------------------------
	
	if((TGTHT510_1553B_message_state.CG_GC_message_count_Z>=MESSAGE_STATE_MAX_COUNT)&&\
	(TGTHT510_1553B_message_state.CG_GC_message_count_B>=MESSAGE_STATE_MAX_COUNT))
	{
		temp[0]=temp[0]|(((uint16)MESSAGE_STATE_ABNORMAL)<<8);//常规与工程遥测通讯超时
	}
	
	else
	{
		temp[0]=temp[0]|(((uint16)MESSAGE_STATE_NORMAL)<<8);//常规与工程遥测通讯正常
	}

//-----仪表遥测-----------------------------------------------------------------------	
	
	if(TGTHT510_1553B_message_state.YB_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[0]=temp[0]|((uint16)MESSAGE_STATE_ABNORMAL);//仪表遥测通讯超时
	}
	
	else
	{
		temp[0]=temp[0]|((uint16)MESSAGE_STATE_NORMAL);//仪表遥测通讯正常
	}

//-----送货船遥测--------------------------------------------------------------------
	
	if(TGTHT510_1553B_message_state.HYCT1100_T_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[1]=temp[1]|(((uint16)MESSAGE_STATE_ABNORMAL)<<8);//送货船遥测通讯超时
	}
	
	else
	{
		temp[1]=temp[1]|(((uint16)MESSAGE_STATE_NORMAL)<<8);//送货船遥测通讯正常
	}
	
//-----接收推进遥测线路盒遥测--------------------------------------------------------	
	
	if(TGTHT510_1553B_message_state.TGTHT100_message_count>=MESSAGE_STATE_MAX_COUNT)
	{

		temp[1]=temp[1]|((uint16)MESSAGE_STATE_ABNORMAL);//推进遥测线路盒遥测通讯超时
		
		for(j=0;j<=88;j++)
		{
			TGTHT510_1553B_data_TGTHT100[j]=0x0000;
		}
		
		for(j=0;j<=64;j++)
		{
			TGTHT510_1553B_data_TGTHT100_Temper_A[j]=0x0000;
		}
		
		for(j=0;j<=64;j++)
		{
			TGTHT510_1553B_data_TGTHT100_Temper_B[j]=0x0000;
		}

		TGTHT510_1553B_message_state.TGTHT100_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	}
	
	else
	{
		if(TGTHT510_1553B_message_state.TGTHT100_validity==MESSAGE_STATE_VALIDITY_FALSE)
		{
			temp[1]=temp[1]|((uint16)MESSAGE_STATE_R_ERROR);//推进遥测线路盒接收数据错误
			
			for(j=0;j<=88;j++)
			{
				TGTHT510_1553B_data_TGTHT100[j]=0x0000;
			}
		
			for(j=0;j<=64;j++)
			{
				TGTHT510_1553B_data_TGTHT100_Temper_A[j]=0x0000;
			}
		
			for(j=0;j<=64;j++)
			{
				TGTHT510_1553B_data_TGTHT100_Temper_B[j]=0x0000;
			}
		}
		
		else
		{
			temp[1]=temp[1]|((uint16)MESSAGE_STATE_NORMAL);//推进遥测线路盒遥测通讯正常
		}

	}
	
	
//-----接收推进控制驱动器A机遥测--------------------------------------------------------	
	
	if(TGTHT510_1553B_message_state.TGTHT520a_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[2]=temp[2]|(((uint16)MESSAGE_STATE_ABNORMAL)<<8);//推进控制驱动器A机遥测通讯超时
		
		for(j=0;j<=6;j++)
		{
			TGTHT510_1553B_data_TGTHT520a[j]=0x0000;
		}
		
		TGTHT510_1553B_message_state.TGTHT520a_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	}
	
	else
	{
		if(TGTHT510_1553B_message_state.TGTHT520a_validity==MESSAGE_STATE_VALIDITY_FALSE)
		{
			temp[2]=temp[2]|(((uint16)MESSAGE_STATE_R_ERROR)<<8);//推进控制驱动器A机遥测通讯数据错误
			for(j=0;j<=6;j++)
			{
			TGTHT510_1553B_data_TGTHT520a[j]=0x0000;
			}
		}
		
		else
		{
			temp[2]=temp[2]|(((uint16)MESSAGE_STATE_NORMAL)<<8);//推进控制驱动器A机遥测通讯正常
		}
		
	}
	
//-----接收推进控制驱动器B机遥测--------------------------------------------------------	
	
	if(TGTHT510_1553B_message_state.TGTHT520b_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[2]=temp[2]|((uint16)MESSAGE_STATE_ABNORMAL);//推进控制驱动器B机遥测通讯超时
		
		for(j=0;j<=6;j++)
		{
			TGTHT510_1553B_data_TGTHT520b[j]=0x0000;
		}
		
		TGTHT510_1553B_message_state.TGTHT520b_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	}
	
	else
	{
		if(TGTHT510_1553B_message_state.TGTHT520b_validity==MESSAGE_STATE_VALIDITY_FALSE)
		{
			temp[2]=temp[2]|((uint16)MESSAGE_STATE_R_ERROR);//推进控制驱动器B机遥测通讯数据错误
			for(j=0;j<=6;j++)
			{
				TGTHT510_1553B_data_TGTHT520b[j]=0x0000;
			}
		}
		
		else
		{
			temp[2]=temp[2]|((uint16)MESSAGE_STATE_NORMAL);//推进控制驱动器B机遥测通讯正常
		}
	}
	

//-----接收压气机电机驱动器遥测--------------------------------------------------------	

	if(TGTHT510_1553B_message_state.TGTHT530_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[3]=temp[3]|(((uint16)MESSAGE_STATE_ABNORMAL)<<8);//压气机电机驱动器遥测通讯超时
		
		for(j=0;j<=12;j++)
		{
			TGTHT510_1553B_data_TGTHT530[j]=0x0000;
		}
		
		TGTHT510_1553B_message_state.TGTHT530_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	}
	
	else
	{
		if(TGTHT510_1553B_message_state.TGTHT530_validity==MESSAGE_STATE_VALIDITY_FALSE)
		{
			temp[3]=temp[3]|(((uint16)MESSAGE_STATE_R_ERROR)<<8);//压气机电机驱动器遥测通讯数据错误
			for(j=0;j<=12;j++)
			{
				TGTHT510_1553B_data_TGTHT530[j]=0x0000;
			}
		}
		
		else
		{
			temp[3]=temp[3]|(((uint16)MESSAGE_STATE_NORMAL)<<8);//压气机电机驱动器遥测通讯正常
		}
		
	}

//-----接收货船补加信息数据遥测--------------------------------------------------------	

	if(TGTHT510_1553B_message_state.HYCT1100_R_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[3]=temp[3]|((uint16)MESSAGE_STATE_ABNORMAL);//接收货船补加信息遥测通讯超时
		
		TGTHT510_1553B_message_state.HYCT1100_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	}
	
	else
	{
		if(TGTHT510_1553B_message_state.HYCT1100_validity==MESSAGE_STATE_VALIDITY_FALSE)
		{
			temp[3]=temp[3]|((uint16)MESSAGE_STATE_R_ERROR);//接收货船补加信息遥测通讯数据错误
			
			for(j=0;j<=24;j++)
			{
				TGTHT510_1553B_R_HYCT1100[j]=0x0000;
			}
		}
		
		else
		{
			temp[3]=temp[3]|((uint16)MESSAGE_STATE_NORMAL);//接收货船补加信息遥测通讯正常
		}
	}

//-----接收数管遥测----------------------------------------------------------------------	
	
	if(TGTHT510_1553B_message_state.KPU_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[4]=temp[4]|(((uint16)MESSAGE_STATE_ABNORMAL)<<8);//数管遥测通讯超时
		
		TGTHT510_1553B_message_state.KPU_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	}
	
	else
	{
		if(TGTHT510_1553B_message_state.KPU_validity==MESSAGE_STATE_VALIDITY_FALSE)
		{
			temp[4]=temp[4]|(((uint16)MESSAGE_STATE_R_ERROR)<<8);//数管遥测通讯数据错误
		}
		
		
		else
		{
			temp[4]=temp[4]|(((uint16)MESSAGE_STATE_NORMAL)<<8);//数管遥测通讯正常
		}
		
	}

//-----更新常规遥测数据----------------------------------------------------------------------	
	
	for(i=0;i<=5;i++)
	{
		CG_equiment_receive_state_data[i]=temp[i];
	}
	
	
}



/******************************************************************************************
**名称：总线通讯状态计数更新函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_message_count_update(void)
{
	if(TGTHT510_1553B_message_state.CG_GC_message_count_Z>=MESSAGE_STATE_MAX_COUNT)
	{
		TGTHT510_1553B_message_state.CG_GC_message_count_Z=MESSAGE_STATE_MAX_COUNT;
	}
	
	else
	{
		TGTHT510_1553B_message_state.CG_GC_message_count_Z++;
	}
	
	if(TGTHT510_1553B_message_state.CG_GC_message_count_B>=MESSAGE_STATE_MAX_COUNT)
	{
		TGTHT510_1553B_message_state.CG_GC_message_count_B=MESSAGE_STATE_MAX_COUNT;
	}
	
	else
	{
		TGTHT510_1553B_message_state.CG_GC_message_count_B++;
	}
	
	if(TGTHT510_1553B_message_state.YB_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		TGTHT510_1553B_message_state.YB_message_count=MESSAGE_STATE_MAX_COUNT;
	}
	
	else
	{
		TGTHT510_1553B_message_state.YB_message_count++;
	}
	
	if(TGTHT510_1553B_message_state.HYCT1100_T_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		TGTHT510_1553B_message_state.HYCT1100_T_message_count=MESSAGE_STATE_MAX_COUNT;
	}
	
	else
	{
		TGTHT510_1553B_message_state.HYCT1100_T_message_count++;
	}
	
	if(TGTHT510_1553B_message_state.TGTHT100_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		TGTHT510_1553B_message_state.TGTHT100_message_count=MESSAGE_STATE_MAX_COUNT;
	}
	
	else
	{
		TGTHT510_1553B_message_state.TGTHT100_message_count++;
	}
	
	if(TGTHT510_1553B_message_state.TGTHT520a_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		TGTHT510_1553B_message_state.TGTHT520a_message_count=MESSAGE_STATE_MAX_COUNT;
	}
	
	else
	{
		TGTHT510_1553B_message_state.TGTHT520a_message_count++;
	}
	
	if(TGTHT510_1553B_message_state.TGTHT520b_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		TGTHT510_1553B_message_state.TGTHT520b_message_count=MESSAGE_STATE_MAX_COUNT;
	}
	
	else
	{
		TGTHT510_1553B_message_state.TGTHT520b_message_count++;
	}
	
	if(TGTHT510_1553B_message_state.TGTHT530_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		TGTHT510_1553B_message_state.TGTHT530_message_count=MESSAGE_STATE_MAX_COUNT;
	}
	
	else
	{
		TGTHT510_1553B_message_state.TGTHT530_message_count++;
	}
	
	if(TGTHT510_1553B_message_state.HYCT1100_R_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		TGTHT510_1553B_message_state.HYCT1100_R_message_count=MESSAGE_STATE_MAX_COUNT;
	}
	
	else
	{
		TGTHT510_1553B_message_state.HYCT1100_R_message_count++;
	}
	
	if(TGTHT510_1553B_message_state.KPU_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		TGTHT510_1553B_message_state.KPU_message_count=MESSAGE_STATE_MAX_COUNT;
	}
	
	else
	{
		TGTHT510_1553B_message_state.KPU_message_count++;
	}

}

/******************************************************************************************
**名称：1553B处理主程序
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_which_bus_choice(void)
{
	TGTHT510_which_bus.count++;
	
	if(TGTHT510_which_bus.count>=15)
	{
		TGTHT510_which_bus.count=100;
		
		if(TGTHT510_which_bus.last_use_BU65170==BU65170_Z)
		{
			TGTHT510_which_bus.last_use_BU65170=BU65170_B;
		}
		
		else if(TGTHT510_which_bus.last_use_BU65170==BU65170_B)
		{
			TGTHT510_which_bus.last_use_BU65170=BU65170_Z;
		}
		
		else
		{
			TGTHT510_which_bus.last_use_BU65170=BU65170_Z;
		}
	}
	return TGTHT510_which_bus.last_use_BU65170;
}

/******************************************************************************************
**名称：1553B处理主程序
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_main(void)
{
	uint16 b;	
	b=TGTHT510_which_bus_choice();
	if(b==BU65170_Z)
	{
		TGTHT510_1553b_dealing(BU65170_Z);//1553B巡检结果处理
	
		TGTHT510_1553b_receiveANDtransmitdata(BU65170_Z);//对堆栈符进行巡检
	}
	
	else if(b==BU65170_B)
	{
		TGTHT510_1553b_dealing(BU65170_B);//1553B巡检结果处理
	
		TGTHT510_1553b_receiveANDtransmitdata(BU65170_B);//对堆栈符进行巡检
	}
	
	else
	{
		return;
	}
}


/******************************************************************************************
**名称：1553B巡检处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_dealing(uint16 which_bu65170)							
{
	#ifdef TEST_VERSION
	//测试件使用，发送阀门状态
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_05_flag==TRUE)
	{
		TGTHT510_1553b_transmitcommand_test_FM_state(which_bu65170);

		TGTHT510_1553B_Subaddress_flag.Subaddress_05_flag=FALSE;
	}
	#endif
	
	//发送常规与工程遥测参数
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_11_flag==TRUE)
	{
		TGTHT510_1553b_transmitdata_CGandGC(which_bu65170);
		
		if(which_bu65170==BU65170_Z)
		{
			TGTHT510_1553B_message_state.CG_GC_message_count_Z=0x0000;
		}
		
		else if(which_bu65170==BU65170_B)
		{
			TGTHT510_1553B_message_state.CG_GC_message_count_B=0x0000;
		}
		
		else
		{
			asm("nop;");
		}

		TGTHT510_1553B_Subaddress_flag.Subaddress_11_flag=FALSE;
	}
	
	//发送设备管理指令
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_12_flag==TRUE)
	{
		asm("nop;");
	}

	//发送仪表显示遥测
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_13_flag==TRUE)
	{
		TGTHT510_1553b_transmitdata_YBYC(which_bu65170);
		
		TGTHT510_1553B_message_state.YB_message_count=0x0000;
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_13_flag=FALSE;
	}
	
	//发送转发前（后）向口补加数据 复帧
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_17_flag==TRUE)
	{
		TGTHT510_1553b_transmitdata_HYCT1100(which_bu65170);
		
		TGTHT510_1553B_message_state.HYCT1100_T_message_count=0x0000;
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_17_flag=FALSE;
	}
	
	//发送转GNC故检状态字
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_19_flag==TRUE)
	{
		TGTHT510_1553b_transmitdata_GNC(which_bu65170);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_19_flag=FALSE;
	}
	
	//发送内存下传数据
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_21_flag==TRUE)
	{
		TGTHT510_1553b_transmitdata_MEMORY(which_bu65170);
		
		//TGTHT510_1553B_Subaddress_flag.Subaddress_21_flag=FALSE;
	}
	
	//发送故障代码
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_23_flag==TRUE)
	{
		TGTHT510_1553B_Subaddress_flag.Subaddress_23_flag=FALSE;
	}
	
	//发送服务请求
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_28_flag==TRUE)
	{
		TGTHT510_1553b_transmitdata_askforserive(which_bu65170);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_28_flag=FALSE;
	}
	
	//接受520、530、540互传数据
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_14_flag==TRUE)
	{
		TGTHT510_1553b_receivedata_subsystem(which_bu65170);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_14_flag=FALSE;
	}
	
	//接收总线指令与手控指令
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_15_flag==TRUE)
	{
		TGTHT510_1553b_receivecommand_buscommand(which_bu65170);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_15_flag=FALSE;
	}
	
	//接收注入指令
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_16_flag==TRUE)
	{
		TGTHT510_1553b_receivecommand_inputcommand(which_bu65170);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_16_flag=FALSE;
	}
	
	//接受货船发送补加信息（数据转换器1）
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_18_flag==TRUE)
	{
		TGTHT510_1553b_receivedata_HYCT1100(which_bu65170,TYPE_RECEIVE_HYCT_DATA1);
		
		TGTHT510_1553B_message_state.HYCT1100_R_message_count=0x0000;
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_18_flag=FALSE;
	}

	//接受货船发送补加信息（数据转换器2）
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_20_flag==TRUE)
	{
		TGTHT510_1553b_receivedata_HYCT1100(which_bu65170,TYPE_RECEIVE_HYCT_DATA2);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_20_flag=FALSE;
	}
	
	//接受综合电子采集的推进传感器参数
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_22_flag==TRUE)
	{
		TGTHT510_1553b_receivedata_KPU(which_bu65170);
		
		TGTHT510_1553B_message_state.KPU_message_count=0x0000;	
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_22_flag=FALSE;
	}
	
	//接收勤务指令
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_29_flag==TRUE)
	{
		TGTHT510_1553b_receivecommand_interactivecommand(which_bu65170);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_29_flag=FALSE;
	}

}

/******************************************************************************************
**名称：发送工程遥测与常规遥测
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_transmitdata_CGandGC(uint16 which_bu65170)
{
	uint16 temp;
	
	uint16 base_pointer;
	
	temp=0x0002;//EPDU包数量标识
	
	base_pointer=BU65170_CG_GC_POINTER;//拉指针使用
	
	TGTHT510_collectANDgroup_CG_group();//常规遥测数据组帧
	
	TGTHT510_collectANDgroup_GC_group();//工程遥测数据组帧
	
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_CG_GC_POINTER,&base_pointer,1)==FALSE)//循环拉指针
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_CG_GC_BASE,&temp,1)==FALSE)
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_CG_GC_BASE+4*1,TGTHT510_1553B_data_GC,32)==FALSE)
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_CG_GC_BASE+4*1+4*32,TGTHT510_1553B_data_CG,140)==FALSE)
		{
			return;
		}
		
	}
	
	else if(which_bu65170==BU65170_B)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_CG_GC_POINTER,&base_pointer,1)==FALSE)//循环拉指针
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_CG_GC_BASE,&temp,1)==FALSE)
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_CG_GC_BASE+4*1,TGTHT510_1553B_data_GC,32)==FALSE)
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_CG_GC_BASE+4*1+4*32,TGTHT510_1553B_data_CG,140)==FALSE)
		{
			return;
		}
		
	}
	
	else
	{
		return;
	}
}

/******************************************************************************************
**名称：发送阀门遥测状态，实验件使用
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

#ifdef TEST_VERSION

void TGTHT510_1553b_transmitcommand_test_FM_state(uint16 which_bu65170)
{
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_TEST_FM_STATE_BASE,CG_valve_state_data,23)==FALSE)
		{
			return;
		}
		
	}
	
	else if(which_bu65170==BU65170_B)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_TEST_FM_STATE_BASE,CG_valve_state_data,23)==FALSE)
		{
			return;
		}
		
	}
	
	else
	{
		return;
	}
}

#endif

/******************************************************************************************
**名称：发送仪表遥测
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_transmitdata_YBYC(uint16 which_bu65170)
{
	uint16 temp;
	
	uint16 base_pointer;
	
	temp=0x0001;//EPDU包数量标识
	
	base_pointer=BU65170_YB_POINTER;//拉指针使用
	
	TGTHT510_collectANDgroup_YB_group();//仪表遥测数据组帧
	
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_YB_POINTER,&base_pointer,1)==FALSE)//循环拉指针
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_YB_BASE,&temp,1)==FALSE)//EPDU包数量标识
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_YB_BASE+4*1,TGTHT510_1553B_data_YB,21)==FALSE)
		{
			return;
		}
		
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_YB_POINTER,&base_pointer,1)==FALSE)//循环拉指针
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_YB_BASE,&temp,1)==FALSE)//EPDU包数量标识
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_YB_BASE+4*1,TGTHT510_1553B_data_YB,21)==FALSE)
		{
			return;
		}
		
	}
	
	else
	{
		return;
	}
	
}

/******************************************************************************************
**名称：发送至货运飞船推进管理器补加状态信息数据
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_transmitdata_HYCT1100(uint16 which_bu65170)
{
	
	uint16 temp;
	
	uint16 base_pointer;
	
	temp=0x0001;//EPDU包数量标识
	
	base_pointer=BU65170_HYCT1100_POINTER;//拉指针使用
	
	TGTHT510_collectANDgroup_HYCT_group();//送货船遥测数据组帧
	
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_HYCT1100_POINTER,&base_pointer,1)==FALSE)//循环拉指针
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_HYCT1100_BASE,&temp,1)==FALSE)//EPDU包数量标识
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_HYCT1100_BASE+4*1,TGTHT510_1553B_data_HYCT,37)==FALSE)
		{
			return;
		}
		
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_HYCT1100_POINTER,&base_pointer,1)==FALSE)//循环拉指针
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_HYCT1100_BASE,&temp,1)==FALSE)//EPDU包数量标识
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_HYCT1100_BASE+4*1,TGTHT510_1553B_data_HYCT,37)==FALSE)
		{
			return;
		}
		
	}
	
	else
	{
		return;
	}
}

/******************************************************************************************
**名称：转发GNC故检数据
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_transmitdata_GNC(uint16 which_bu65170)
{
	uint16 temp;
	
	uint16 base_pointer;
	
	temp=0x0001;//EPDU包数量标识
	
	base_pointer=BU65170_GNC_POINTER;//拉指针使用
	
	TGTHT510_collectANDgroup_GNC_group();//发送转发GNC故检状态字
	
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_GNC_POINTER,&base_pointer,1)==FALSE)//循环拉指针
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_GNC_BASE,&temp,1)==FALSE)//EPDU包数量标识
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_GNC_BASE+4*1,TGTHT510_1553B_data_GNC,7)==FALSE)
		{
			return;
		}
		
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_GNC_POINTER,&base_pointer,1)==FALSE)//循环拉指针
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_GNC_BASE,&temp,1)==FALSE)//EPDU包数量标识
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_GNC_BASE+4*1,TGTHT510_1553B_data_GNC,7)==FALSE)
		{
			return;
		}
		
	}
	
	else
	{
		return;
	}
}

/******************************************************************************************
**名称：内存下传数据发送
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_transmitdata_MEMORY(uint16 which_bu65170)
{
	uint16 temp;
	
	uint16 base_pointer;
	
	temp=0x0001;//EPDU包数量标识
	
	base_pointer=BU65170_MEMORY_POINTER;//拉指针使用
	
	if(TGTHT510_1553B_service_flag.Subaddress_21_service_flag==TRUE)//接受到子地址21勤务指令
	{
		TGTHT510_1553B_service_flag.Subaddress_21_service_flag=FALSE;
		
		TGTHT510_collectANDgroup_MEMORY_group();
		
		if(which_bu65170==BU65170_Z)
		{
			
			if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_MEMORY_POINTER,&base_pointer,1)==FALSE)//循环拉指针
			{
				return;
			}
			
			if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_MEMORY_BASE,&temp,1)==FALSE)//EPDU包数量标识
			{
				return;
			}
			
			if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_MEMORY_BASE+4*1,TGTHT510_1553B_data_MEMORY,255)==FALSE)
			{
				return;
			}
			
		}
		
		else if(which_bu65170==BU65170_B)
		{
			if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_MEMORY_POINTER,&base_pointer,1)==FALSE)//循环拉指针
			{
				return;
			}
			
			if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_MEMORY_BASE,&temp,1)==FALSE)//EPDU包数量标识
			{
				return;
			}
			
			if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_MEMORY_BASE+4*1,TGTHT510_1553B_data_MEMORY,255)==FALSE)
			{
				return;
			}
			
		}
		
		else
		{
			return;
		}
			
	}
	
	else
	{
		asm("nop;");
	}
		
}


/******************************************************************************************
**名称：发送服务请求
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_transmitdata_askforserive(uint16 which_bu65170)
{
	
	uint16 base_pointer;
	
	base_pointer=BU65170_ASKFORSERIVE_POINTER;//拉指针使用
		
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_ASKFORSERIVE_POINTER,&base_pointer,1)==FALSE)//循环拉指针
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_ASKFORSERIVE_BASE,&TGTHT510_1553B_data_ask_for_service,1)==FALSE)
		{
			return;
		}
		
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_ASKFORSERIVE_POINTER,&base_pointer,1)==FALSE)//循环拉指针
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_ASKFORSERIVE_BASE,&TGTHT510_1553B_data_ask_for_service,1)==FALSE)
		{
			return;
		}
		
	}
	
	else
	{
		return;
	}
	
	TGTHT510_1553B_data_ask_for_service=0x0000;
		
}

/******************************************************************************************
**名称：发送设备管理指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_transmitcommand_equiment(uint16 which_bu65170)
{
	
	uint16 base_pointer;
	
	base_pointer=BU65170_COMMAND_EQUIP_POINTER;//拉指针使用
	
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_COMMAND_EQUIP_POINTER,&base_pointer,1)==FALSE)//循环拉指针
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_COMMAND_EQUIP_BASE,TGTHT510_1553B_data_equiment_command,11)==FALSE)
		{
			return;
		}
		
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_COMMAND_EQUIP_POINTER,&base_pointer,1)==FALSE)//循环拉指针
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_COMMAND_EQUIP_BASE,TGTHT510_1553B_data_equiment_command,11)==FALSE)
		{
			return;
		}
		
	}
	
	else
	{
		return;
	}

}

/******************************************************************************************
**名称：获取遥测线路盒，推进控制驱动器，压气机电机驱动器EPDU包累加和
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint8 TGTHT510_1553b_receivedata_subsystem_EPDU_sum_get(uint16 type,uint16 *p,uint16 length)
{
	uint8 sum;
	
	sum=(uint8)(p[length-1]>>8);
	
	/*
	if(type==EPDU_TYPE_TGTHT530)
	{
		sum=(uint8)p[length-2];
	}
	else
	{
		sum=(uint8)(p[length-1]>>8);
	}
	*/
	return sum;

}



/******************************************************************************************
**名称：计算遥测线路盒，推进控制驱动器，压气机电机驱动器EPDU包累加和
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint8 TGTHT510_1553b_receivedata_subsystem_EPDU_sum_calculate(uint16 type,uint16 *p,uint16 size)
{
	uint8 sum;
	uint16 i;
	sum=0;
	
	for(i=0;i<=size-1;i++)
	{
		sum=sum+(uint8)(p[i]>>8);
		sum=sum+(uint8)(p[i]);
	}
	
	/*
	if(type==EPDU_TYPE_TGTHT530)
	{
		for(i=0;i<=size-2;i++)
		{
			sum=sum+(uint8)(p[i]>>8);
			sum=sum+(uint8)(p[i]);
		}
		sum=sum+(uint8)(p[size-1]>>8);
		
	}
	
	else
	{
		for(i=0;i<=size-1;i++)
		{
			sum=sum+(uint8)(p[i]>>8);
			sum=sum+(uint8)(p[i]);
		}
	}
	*/
	
	return sum;

}


/******************************************************************************************
**名称：计算遥测线路盒，推进控制驱动器，压气机电机驱动器EPDU包长度
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_1553b_receivedata_subsystem_EPDU_length_generate(uint16 type)
{
	uint16 length;
	if((type==EPDU_TYPE_TGTHT100A)||(type==EPDU_TYPE_TGTHT100B))//推进遥测线路盒EPDU源包
	{
		length=EPDU_LENGTH_TGTHT100;
	}
	
	else if(type==EPDU_TYPE_TGTHT530)//电机驱动器EPDU源包
	{
		length=EPDU_LENGTH_TGTHT530;
	}
	
	else if(type==EPDU_TYPE_TGTHT520A)//推进控制驱动器主路EPDU源包
	{
		length=EPDU_LENGTH_TGTHT520A;
	}
	
	else if(type==EPDU_TYPE_TGTHT520B)//推进控制驱动器备路EPDU源包
	{
		length=EPDU_LENGTH_TGTHT520B;
	}
	
	else
	{
		length=EPDU_LENGTH_ERROR;//EPDU源包类型错误
	}
	
	return length;
	
}


/******************************************************************************************
**名称：缓存遥测线路盒，推进控制驱动器，压气机电机驱动器EPDU包数据
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_receivedata_subsystem_buffer(uint16 type,uint16 *p,uint16 length)
{
	uint16 i;
	if((type==EPDU_TYPE_TGTHT100A)||(type==EPDU_TYPE_TGTHT100B))//推进遥测线路盒遥测复帧数据
	{
		for(i=0;i<=length-1;i++)
		{
			if((i>=4)&&(i<=82))
			{
				TGTHT510_1553B_data_TGTHT100[i-4]=p[i];
			}
			
			else if((i>=83)&&(i<=147))
			{
				if(type==EPDU_TYPE_TGTHT100A)
				{
					TGTHT510_1553B_data_TGTHT100_Temper_A[i-83]=p[i];
				}
				else
				{
					TGTHT510_1553B_data_TGTHT100_Temper_B[i-83]=p[i];
				}
	
			}
			
			else if((i>=148)&&(i<=157))
			{
				TGTHT510_1553B_data_TGTHT100[i-69]=p[i];
			}
			else
			{
				asm("nop;");
			}

		}			
			
			
	}
		
		
	else if(type==EPDU_TYPE_TGTHT530)//压气机电机驱动器遥测数据
	{
		for(i=0;i<=length-1;i++)
		{
			if((i>=4)&&(i<=16))
			{
				TGTHT510_1553B_data_TGTHT530[i-4]=p[i];
			}
			
			else
			{
				asm("nop;");
			}

		}
	
	}
		
	else if(type==EPDU_TYPE_TGTHT520A)
	{
		for(i=0;i<=length-1;i++)
		{
			if((i>=4)&&(i<=10))
			{
				TGTHT510_1553B_data_TGTHT520a[i-4]=p[i];
			}
			
			else
			{
				asm("nop;");
			}
			
		}			
			
	}
		
	else if(type==EPDU_TYPE_TGTHT520B)
	{
		for(i=0;i<=length-1;i++)
		{
			if((i>=4)&&(i<=10))
			{
				TGTHT510_1553B_data_TGTHT520b[i-4]=p[i];
			}
			
			else
			{
				asm("nop;");
			}
			
		}	
	}
		
	else
	{
		return;//EPDU源包类型错误
	}

}

/******************************************************************************************
**名称：缓存遥测线路盒，推进控制驱动器，压气机电机驱动器EPDU包数据
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_1553b_receivedata_subsystem_save_EPDU(uint16 type,uint16 start_i,uint16 which_bu65170)
{
	uint16 EPDU_data[160];
	uint8 EPDU_sum;//EPDU累加和
	uint8 calculate_sum;//计算累加和
	uint16 i;
	uint16 length;
	
	length=TGTHT510_1553b_receivedata_subsystem_EPDU_length_generate(type);
	
	if(length==EPDU_LENGTH_ERROR)
	{
		return FALSE;//EPDU源包长度错误
	}
	
	if(which_bu65170==BU65170_Z)
	{	
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_TGTHT_BASE+4*start_i*2,EPDU_data,length)==FALSE)
		{
			return;
		}	
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_TGTHT_BASE+4*start_i*2,EPDU_data,length)==FALSE)
		{
			return;
		}
	}
	
	else
	{
		return;
	}
	
	calculate_sum=TGTHT510_1553b_receivedata_subsystem_EPDU_sum_calculate(type,EPDU_data,length-1);//计算累加和
	
	EPDU_sum=TGTHT510_1553b_receivedata_subsystem_EPDU_sum_get(type,EPDU_data,length);//EPDU累加和
	
	TGTHT510_1553b_receivedata_subsystem_buffer(type,EPDU_data,length);
	/*
	if(calculate_sum==EPDU_sum)
	{
		TGTHT510_1553b_receivedata_subsystem_buffer(type,EPDU_data,length);

	}
	else
	{
		return FALSE;//EPDU源包累加和错误
	}
	*/
	
	return TRUE;

}


/******************************************************************************************
**名称：接收遥测线路盒，推进控制驱动器，压气机电机驱动器遥测数据
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_receivedata_subsystem(uint16 which_bu65170)
{
	uint16 i;
	uint16 EPDU_num;//EPDU源包序列数量
	uint16 EPDU_APID;//EPDU源包APID
	uint16 EPDU_subservice;//EPDU源包副导头
	uint8 EPDU_sum;//EPDU源包累加和
	uint16 temp;
	
	//读取EPDU包序列数量
	if(which_bu65170==BU65170_Z)
	{	
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_TGTHT_BASE+4*0*2,&EPDU_num,1)==FALSE)
		{
			return;
		}	
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_TGTHT_BASE+4*0*2,&EPDU_num,1)==FALSE)
		{
			return;
		}
	}
	
	else
	{
		return;
	}
	
	if((EPDU_num==0)||(EPDU_num>=5))
	{	
		return;	//源包序列数量错误，退出接收分函数	
	}
	
	else
	{
		i=0x0001;
		while(EPDU_num!=0)
		{
			EPDU_num--;
			
			//读取EPDU_APID
			if(which_bu65170==BU65170_Z)
			{	
				if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_TGTHT_BASE+4*i*2,&EPDU_APID,1)==FALSE)
				{
					return;
				}	
			}
			
			else if(which_bu65170==BU65170_B)
			{
				if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_TGTHT_BASE+4*i*2,&EPDU_APID,1)==FALSE)
				{
					return;
				}
			}
			
			else
			{
				return;
			}
			
			EPDU_APID=EPDU_APID&0x07ff;
			
			//读取EPDU_subservice
			if(which_bu65170==BU65170_Z)
			{	
				if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_TGTHT_BASE+4*(i+3)*2,&EPDU_subservice,1)==FALSE)
				{
					return;
				}	
			}
			
			else if(which_bu65170==BU65170_B)
			{
				if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_TGTHT_BASE+4*(i+3)*2,&EPDU_subservice,1)==FALSE)
				{
					return;
				}
			}
			
			else
			{
				return;
			}
			
			if((EPDU_APID==R_APID_TGTHT100)&&(EPDU_subservice==R_SUBSERVICE_TGTHT100_A))//推进遥测线路盒遥测复帧A数据
			{
				temp=TGTHT510_1553b_receivedata_subsystem_save_EPDU(EPDU_TYPE_TGTHT100A,i,which_bu65170);
				
				TGTHT510_1553B_message_state.TGTHT100_message_count=0x0000;
				
				if(temp==TRUE)
				{
					TGTHT510_1553B_message_state.TGTHT100_validity=MESSAGE_STATE_VALIDITY_TRUE;
				}
				
				else
				{
					TGTHT510_1553B_message_state.TGTHT100_validity=MESSAGE_STATE_VALIDITY_FALSE;
				}
				
				i=i+EPDU_LENGTH_TGTHT100;

			}
			
			else if((EPDU_APID==R_APID_TGTHT100)&&(EPDU_subservice==R_SUBSERVICE_TGTHT100_B))//推进遥测线路盒遥测复帧B数据
			{
				temp=TGTHT510_1553b_receivedata_subsystem_save_EPDU(EPDU_TYPE_TGTHT100B,i,which_bu65170);
				
				if(temp==TRUE)
				{
					TGTHT510_1553B_message_state.TGTHT100_validity=MESSAGE_STATE_VALIDITY_TRUE;
				}
				
				else
				{
					TGTHT510_1553B_message_state.TGTHT100_validity=MESSAGE_STATE_VALIDITY_FALSE;
				}
				
				TGTHT510_1553B_message_state.TGTHT100_message_count=0x0000;
				
				i=i+EPDU_LENGTH_TGTHT100;
				
			}
			
			else if((EPDU_APID==R_APID_TGTHT530)&&(EPDU_subservice==R_SUBSERVICE_TGTHT530))//压气机电机驱动器遥测数据
			{
				temp=TGTHT510_1553b_receivedata_subsystem_save_EPDU(EPDU_TYPE_TGTHT530,i,which_bu65170);
				
				if(temp==TRUE)
				{
					TGTHT510_1553B_message_state.TGTHT530_validity=MESSAGE_STATE_VALIDITY_TRUE;
				}
				
				else
				{
					TGTHT510_1553B_message_state.TGTHT530_validity=MESSAGE_STATE_VALIDITY_FALSE;
				}
				
				
				TGTHT510_1553B_message_state.TGTHT530_message_count=0x0000;
				
				i=i+EPDU_LENGTH_TGTHT530;
				
			}
			
			else if((EPDU_APID==R_APID_TGTHT520a)&&(EPDU_subservice==R_SUBSERVICE_TGTHT520a))//推进控制驱动器主机遥测数据
			{
				temp=TGTHT510_1553b_receivedata_subsystem_save_EPDU(EPDU_TYPE_TGTHT520A,i,which_bu65170);
				
				if(temp==TRUE)
				{
					TGTHT510_1553B_message_state.TGTHT520a_validity=MESSAGE_STATE_VALIDITY_TRUE;
				}
				
				else
				{
					TGTHT510_1553B_message_state.TGTHT520a_validity=MESSAGE_STATE_VALIDITY_FALSE;
				}

				
				TGTHT510_1553B_message_state.TGTHT520a_message_count=0x0000;
				
				i=i+EPDU_LENGTH_TGTHT520A;
				
			}
			
			else if((EPDU_APID==R_APID_TGTHT520b)&&(EPDU_subservice==R_SUBSERVICE_TGTHT520b))//推进控制驱动器备机遥测数据
			{
				temp=TGTHT510_1553b_receivedata_subsystem_save_EPDU(EPDU_TYPE_TGTHT520B,i,which_bu65170);
				
				if(temp==TRUE)
				{
					TGTHT510_1553B_message_state.TGTHT520b_validity=MESSAGE_STATE_VALIDITY_TRUE;
				}
				
				else
				{
					TGTHT510_1553B_message_state.TGTHT520b_validity=MESSAGE_STATE_VALIDITY_FALSE;
				}

				TGTHT510_1553B_message_state.TGTHT520b_message_count=0x0000;
				
				i=i+EPDU_LENGTH_TGTHT520B;
			}
			
			else
			{
				return;	//退出接收分函数
			}
	
		}
		
	}

}

/******************************************************************************************
**名称：计算总线指令ISO校验
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_1553b_receivecommand_buscommand_ISO_calculate(uint16 *p,uint16 size)
{
	uint16 ck1,ck2;
	uint16 c0,c1,i,temp;
	c0=0;
	c1=0;
	for(i=0;i<=size-1;i++)
	{	
		c0=c0+(p[i]>>8);
		c1=c1+c0;
		c0=c0+(p[i]&0x00ff);
		c1=c1+c0;
	
	}
	c0=c0%255;
	c1=c1%255;
	ck1=(-c0-c1)%255-1;
	ck2=c1;
	if(ck1==0)
    {
       ck1=255;
    }
        
    if(ck2==0)
    {
       ck2=255;
    }
	temp=(ck1<<8)|((uint16)ck2);
	return temp;
}


/******************************************************************************************
**名称：判断总线指令格式是否正确
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_1553b_receivecommand_buscommand_is_correct(uint16 *p)
{
	uint16 i;
	uint16 data[6];
	uint16 sum;
	
	if(p[0]!=0x0001)
	{
		return FALSE;//EPDU包数量标识错误
	}
	
	if((p[1]!=0x1b01)||(p[2]!=0x0000)||(p[3]!=0x0007))
	{
		return FALSE;//包主导头错误
	}
	
	if((p[4]!=0x0202)&&(p[4]!=0x0201))
	{
		return FALSE;//服务类型，服务子类型错误
	}
	
	if(p[5]!=p[6])
	{
		return FALSE;//指令内容不相同
	}
	
	for(i=0;i<=5;i++)
	{
		data[i]=p[i+1];
	}
	
	sum=TGTHT510_1553b_receivecommand_buscommand_ISO_calculate(data,6);//计算ISO校验字
	
	if(sum!=p[7])
	{
		return FALSE;//ISO校验错误
	}
	
	return TRUE;
	

}


/******************************************************************************************
**名称：总线指令内容处理
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_receivecommand_buscommand_code_dealing(uint8 code)
{
	
	if((code>=LVb1K)&&(code<=LVb87G))//自锁阀指令
	{
		TGTHT510_valvecontrol_struct.command_from_bus=code;//向阀门控制全局结构体写入阀门内部地址编码
		TGTHT510_valvecontrol_struct.command_from_bus_time=2;
	}
	
	else if((code==DVb1K)||(code==DVb1G))
	{
		TGTHT510_valvecontrol_struct.command_DVb1=code;
	}
	
	else
	{
		switch(code)
			{
				case 0xB1://推进主份加热器供电通：0xB1
				{
					TGTHT510_1553b_relay_dealing(BUS_MAIN_HEATER_POWER_ON);
					
					break;
				}
				
				case 0xB2://推进主份加热器供电断：0xB2
				{
					TGTHT510_1553b_relay_dealing(BUS_MAIN_HEATER_POWER_OFF);
					
					break;
				}
				
				case 0xB3://推进备份加热器供电通：0xB3
				{
					TGTHT510_1553b_relay_dealing(BUS_LESS_HEATER_POWER_ON);
					break;
				}
				
				case 0xB4://推进备份加热器供电断：0xB4
				{
					TGTHT510_1553b_relay_dealing(BUS_LESS_HEATER_POWER_OFF);
					break;
				}
				
				case 0xB5://液冷模块I主泵供电通：0xB5
				{
					TGTHT510_1553b_relay_dealing(BUS_COOLER_1_MAIN_POWER_ON);
					break;
				}
				
				case 0xB6://液冷模块I备泵供电通：0xB6
				{
					TGTHT510_1553b_relay_dealing(BUS_COOLER_1_LESS_POWER_ON);
					break;
				}
				
				case 0xB7://液冷模块I主、备泵供电断：0xB7
				{
					TGTHT510_1553b_relay_dealing(BUS_COOLER_1_POWER_OFF);
					break;
				}
				
				case 0xB8://液冷模块II主泵供电通：0xB8
				{
					TGTHT510_1553b_relay_dealing(BUS_COOLER_2_MAIN_POWER_ON);
					break;
				}
				
				case 0xB9://液冷模块II备泵供电通：0xB9
				{
					TGTHT510_1553b_relay_dealing(BUS_COOLER_2_LESS_POWER_ON);
					break;
				}
				
				case 0xBA://液冷模块II主、备泵供电断：0xBA
				{
					TGTHT510_1553b_relay_dealing(BUS_COOLER_2_POWER_OFF);
					break;
				}
				
				case 0xBB://退出补加：0xBB
				{
					TGTHT510_supply_ctrl.state=STATE_NONE;//补加状态：空闲
			
					TGTHT510_supply_ctrl.stage=STAGE_00_NONE;//补加阶段：无
					
					TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
					
					TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
					
					TGTHT510_supply_time_stage_end();
					
					TGTHT510_supply_main_initial();
					
					break;
				}
				
				case 0xBC://补加开始：0xBC
				{
					//暂无具体功能
					
					break;
				}
				
				case 0xBD://补加中止：0xBD
				{
					TGTHT510_supply_ctrl.state=STATE_BREAK;
	
					TGTHT510_supply_ctrl.step=STEP_START;
	
					TGTHT510_supply_ctrl.command=COMMAND_START;
					
					break;
				}
				
				case 0xBE://补加完成：0xBE
				{
					//暂无具体功能
					
					break;
				}
				
				case 0xBF://补加暂停：0xBF
				{
					TGTHT510_supply_ctrl.step_temp=TGTHT510_supply_ctrl.step;
	
					TGTHT510_supply_ctrl.command_temp=TGTHT510_supply_ctrl.command;
					
					TGTHT510_supply_ctrl.state=STATE_PAUSE;
	
					TGTHT510_supply_ctrl.step=STEP_START;
	
					TGTHT510_supply_ctrl.command=COMMAND_START;
					
					break;
				}
				
				case 0xC0://进入补加：0xC0
				{
					//暂无具体功能
					
					break;
				}
				
				case 0xC1://紧急退出补加：0xC1
				{
					//暂无具体功能
					
					break;
				}
				
				case 0xC2://手动补加指令1：0xC2
				{
					
					//暂无具体功能
					
					break;
				}
				
				case 0xC3://手动补加指令2：0xC3
				{
					//暂无具体功能
					
					break;
				}
				
				case 0xC4://接收数管参数使能：0xC4
				{
					
					break;
				}
				
				case 0xC5://补加继续：0xC5
				{
					
                    if(TGTHT510_supply_ctrl.state==STATE_PAUSE)
					{
						TGTHT510_supply_ctrl.errno=0;
				
						TGTHT510_supply_ctrl.state=STATE_PAUSE_RESUME;
				
						TGTHT510_supply_ctrl.step=STEP_START;
				
						TGTHT510_supply_ctrl.command=COMMAND_START;
					}
					
					else
					{
						asm("nop;");
					}
					
					
					break;
				}
				
				case 0xC6://推进故检使能：0xC6
				{
					TGTHT510_faultdiagnosis_push_all_enable_disable_set(ENABLE);
					break;
				}
				
				case 0xC7://推进故检禁止：0xC7
				{
					TGTHT510_faultdiagnosis_push_all_enable_disable_set(DISABLE);
					break;
				}
				
				case 0xC8://轨控限制功耗使能：0xC8
				{
					Temperature_control_global.total_power=70;
					break;
				}
				
				case 0xC9://轨控限制功耗禁止：0xC9
				{
					Temperature_control_global.total_power=300;
					break;
				}
				
				case 0xCA://补加热控使能：0xCA
				{
					TGTHT510_tempercontrol_supply_is_auto_control(ENABLE);
					break;
				}
				
				case 0xCB://补加热控禁止：0xCB
				{
					TGTHT510_tempercontrol_supply_is_auto_control(DISABLE);
					break;
				}
				
				case 0xCC://液冷工作使能：0xCC
				{
					
					break;
				}
				
				case 0xCD://液冷工作禁止：0xCD
				{
					
					break;
				}
				
				case 0xCE://使用遥测线路盒数据：0xCE
				{
					
					break;
				}
				
				case 0xCF://使用数管遥测数据：0xCF
				{
					
					break;
				}
				
				default:break;
	
			}

	}

}


/******************************************************************************************
**名称：接收总线指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_receivecommand_buscommand(uint16 which_bu65170)
{
	uint16 bus_command_data[8];//缓存总线指令数据内容
	uint16 i,correct;
	uint8 command_code;
	
	if(which_bu65170==BU65170_Z)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_BUS_COMMAND_BASE+4*0*2,bus_command_data,8)==FALSE)
		{
			return;
		}
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_BUS_COMMAND_BASE+4*0*2,bus_command_data,8)==FALSE)
		{
			return;
		}
	}
	
	else
	{
		return;
	}
		
	correct=TGTHT510_1553b_receivecommand_buscommand_is_correct(bus_command_data);
	
	if(correct==FALSE)
	{
		return;//指令格式错误
	}
	
	command_code=TGTHT510_1553B_Bcommand_code[((uint8)bus_command_data[5])];//总线指令内部地址编码
	
	TGTHT510_1553b_receivecommand_buscommand_code_dealing(command_code);//总线指令内容处理
	
	CG_bus_command[0]=bus_command_data[6];//总线指令内容作为常规遥测下传
	CG_bus_command[1]=bus_command_data[7];//总线指令校验作为常规遥测下传

}

/******************************************************************************************
**名称：提取注入指令的指令类型与校验和，作为常规遥测下传
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_receivecommand_inputcommand_state_data(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i,uint16 length)
{
	uint16 type;		//缓存指令类型
	uint16 sum;			//缓存注入EPDU的校验和
	
	CG_inputcommand_receive_state_data[0]=a.inputcommand_data[start_i+4];//指令类型
	
	CG_inputcommand_receive_state_data[1]=a.inputcommand_data[start_i+length-1];//注入EPDU的校验和

}

/******************************************************************************************
**名称：计算注入指令CRC校验码
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_1553b_receivecommand_inputcommand_CRC_calculate(TGTHT510_1553B_inputcommand_TypeDef a)
{
	uint16 i;
	uint16 CRC;//校验字
	uint8 temp;
	CRC=0x0000;
	
	temp=(uint8)(a.inputcommand_head_word1>>8);//高字节
	CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	
	temp=(uint8)(a.inputcommand_head_word1);//低字节
	CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	
	temp=(uint8)(a.inputcommand_head_word2>>8);//高字节
	CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	
	temp=(uint8)(a.inputcommand_head_word2);//低字节
	CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	
	temp=a.inputcommand_head_byte;
	CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	
	for(i=0;i<=a.inputcommand_data_length-2;i++)
	{
		temp=(uint8)(a.inputcommand_data[i]>>8);//高字节
		CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
		
		temp=(uint8)(a.inputcommand_data[i]);//低字节
		CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	}
	
	temp=(uint8)(a.inputcommand_data[a.inputcommand_data_length-1]>>8);//高字节
	CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	
	return CRC;

}



/******************************************************************************************
**名称：判断注入指令格式是否正确
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_1553b_receivecommand_inputcommand_is_correct(TGTHT510_1553B_inputcommand_TypeDef a)
{
	uint16 VCID;
	uint16 length;
	uint16 CRC;
	
	if(a.inputcommand_head_word1!=0x0001)
	{
		return FALSE;//主导头错误
	}
	
	VCID=a.inputcommand_head_word2>>10;//虚拟通道
	
	if((VCID!=0x0010)&&(VCID!=0x0015))
	{
		return FALSE;//虚拟通道错误
	}
	
	length=a.inputcommand_head_word2&0x03ff;
	
	if((length!=835)&&(length!=233))
	{
		return FALSE;//帧长度错误
	}
	
	CRC=TGTHT510_1553b_receivecommand_inputcommand_CRC_calculate(a);//计算CRC校验字
	
	if(CRC!=a.inputcommand_CRC)
	{
		//return FALSE;//CRC校验错误
	}
	
	return TRUE;

}



/******************************************************************************************
**名称：缓存注入指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
TGTHT510_1553B_inputcommand_TypeDef TGTHT510_1553b_receivecommand_inputcommand_save(uint16 which_bu65170)
{
	TGTHT510_1553B_inputcommand_TypeDef a;//缓存注入指令
	uint16 i,length;
	uint16 temp,t;
	uint16 i_max;
	
	a.inputcommand_head_word1=0x0000;
	a.inputcommand_head_word2=0x0000;
	a.inputcommand_head_byte=0x00;
	for(i=0;i<=414;i++)
	{
		a.inputcommand_data[i]=0x0000;
	}
	a.inputcommand_CRC=0x0000;
	a.inputcommand_length=0x0000;//初始化注入帧数据结构体
	
	//读取注入指令帧长度
	if(which_bu65170==BU65170_Z)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_INPUT_COMMAND_BASE+4*1*2,&length,1)==FALSE)
		{
			return;
		}
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_INPUT_COMMAND_BASE+4*1*2,&length,1)==FALSE)
		{
			return;
		}
	}
	
	else
	{
		return;
	}
	
	length=length&0x03ff;//遥控传送帧的帧长
	
	if((length==233)||(length==835))
	{
		a.inputcommand_length=length;//缓存帧长度
	}
	else
	{
		return a;//帧长错误
	}
	
	i_max=(a.inputcommand_length-5)>>1;
	a.inputcommand_data_length=i_max;
	
	//帧长为233，则共234字节，数据域227字节，16bit缓存为2*114字=228字节
	//帧长为835，则共836字节，数据域829字节，16bit缓存为2*415字=830字节
	
	//a.inputcommand_data最后1字的低字节不是传送帧数据域的数据
	
	//主导头1
	
	if(which_bu65170==BU65170_Z)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_INPUT_COMMAND_BASE+4*0*2,&t,1)==FALSE)
		{
			return;
		}
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_INPUT_COMMAND_BASE+4*0*2,&t,1)==FALSE)
		{
			return;
		}
	}
	
	else
	{
		return;
	}
	
	a.inputcommand_head_word1=t;
	
	//主导头2
	
	if(which_bu65170==BU65170_Z)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_INPUT_COMMAND_BASE+4*1*2,&t,1)==FALSE)
		{
			return;
		}
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_INPUT_COMMAND_BASE+4*1*2,&t,1)==FALSE)
		{
			return;
		}
	}
	
	else
	{
		return;
	}
	
	a.inputcommand_head_word2=t;

	//帧序列号
	
	if(which_bu65170==BU65170_Z)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_INPUT_COMMAND_BASE+4*2*2,&t,1)==FALSE)
		{
			return;
		}
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_INPUT_COMMAND_BASE+4*2*2,&t,1)==FALSE)
		{
			return;
		}
	}
	
	else
	{
		return;
	}
	
	a.inputcommand_head_byte=(uint8)(t>>8);
	
	for(i=0;i<=i_max-2;i++)
	{
		if(which_bu65170==BU65170_Z)
		{
			if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_INPUT_COMMAND_BASE+4*(i+2)*2,&temp,1)==FALSE)
			{
				return;
			}
		}
		
		else if(which_bu65170==BU65170_B)
		{
			if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_INPUT_COMMAND_BASE+4*(i+2)*2,&temp,1)==FALSE)
			{
				return;
			}
		}
		
		else
		{
			return;
		}
		
		a.inputcommand_data[i]=(a.inputcommand_data[i]&0x00ff)|(temp<<8);
		
		if(which_bu65170==BU65170_Z)
		{
			if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_INPUT_COMMAND_BASE+4*(i+3)*2,&temp,1)==FALSE)
			{
				return;
			}
		}
		
		else if(which_bu65170==BU65170_B)
		{
			if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_INPUT_COMMAND_BASE+4*(i+3)*2,&temp,1)==FALSE)
			{
				return;
			}
		}
		
		else
		{
			return;
		}
		
		a.inputcommand_data[i]=(a.inputcommand_data[i]&0xff00)|(temp>>8);
		
	}
	
	if(which_bu65170==BU65170_Z)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_INPUT_COMMAND_BASE+4*(i_max+1)*2,&temp,1)==FALSE)
		{
			return;
		}
	}
		
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_INPUT_COMMAND_BASE+4*(i_max+1)*2,&temp,1)==FALSE)
		{
			return;
		}
	}
		
	else
	{
		return;
	}
	
	//高字节缓存遥控帧数据域最后一字节，低字节非数据域数据
	a.inputcommand_data[i_max-1]=(a.inputcommand_data[i_max-1]&0x00ff)|(temp<<8);
	
	if(which_bu65170==BU65170_Z)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_INPUT_COMMAND_BASE+4*(i_max+2)*2,&temp,1)==FALSE)
		{
			return;
		}
	}
		
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_INPUT_COMMAND_BASE+4*(i_max+2)*2,&temp,1)==FALSE)
		{
			return;
		}
	}
		
	else
	{
		return;
	}
	
	a.inputcommand_CRC=temp;
	
	return a;

}

/******************************************************************************************
**名称：注入指令处理EPDU包数据处理函数，返回处理的EPDU包长度,与处理结果，若高2bit为11表示处理出错，00表示处理正确，低14位为EPDU包长度
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_dealing(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 i;
	uint16 length;
	uint16 type;
	uint16 correct;
	uint16 result;
	result=0x0000;
	
	length=TGTHT510_1553b_receivecommand_inputcommand_EPDU_length_get(a,start_i);
	
	if(length==INPUT_COMMAND_LEN_UNKNOW)
	{
		result=(result&0x3fff)|0xc000;
		return result;//返回EPDU包长度错误
	}
	
	result=result|(length&0x3fff);
	
	correct=TGTHT510_1553b_receivecommand_inputcommand_EPDU_is_correct(a,start_i,length);
	
	if(correct==FALSE)
	{
		result=(result&0x3fff)|0xc000;
		return result;//EPDU格式错误
	}
	
	type=a.inputcommand_data[start_i+4];
	
	switch(type)
	{
		case INPUT_COMMAND_TYPE_POWER://修改峰值功耗
		{
			TGTHT510_1553b_inputcommand_dealing_power(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MULTI_CONTR_SPOT://修改多个控温回路的控温点
		{
			TGTHT510_1553b_inputcommand_dealing_multi_contr_spot(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ALL_CONTR_SPOT://修改全部控温回路的控温点
		{
			TGTHT510_1553b_inputcommand_dealing_all_contr_spot(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ONE_MEA_SPOT://修改某一控温回路的控温测点
		{
			TGTHT510_1553b_inputcommand_dealing_one_mea_spot(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ONE_FIXED://指定某一控温回路按照指定占空比输出
		{
			TGTHT510_1553b_inputcommand_dealing_one_fixed(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_AUTO_RESUME://恢复某一控温回路为自动控温状态
		{
			TGTHT510_1553b_inputcommand_dealing_auto_resume(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ALL_RESUME://恢复所有控温回路控温状态
		{
			TGTHT510_1553b_inputcommand_dealing_all_resume(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SOURCE://指定控温参数来源选用
		{
			TGTHT510_1553b_inputcommand_dealing_source(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_PLACE_SIGNAL_EN://指定某一路贮箱到位信号使能
		{
			TGTHT510_1553b_inputcommand_dealing_place_signal_en(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_PLACE_SIGNAL_DIS://指定某一路贮箱到位信号禁止
		{
			TGTHT510_1553b_inputcommand_dealing_place_signal_dis(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_FAULT_EN://指定某一路故检使能
		{
			TGTHT510_1553b_inputcommand_dealing_fault_en(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_FAULT_DIS://指定某一路故检禁止
		{
			TGTHT510_1553b_inputcommand_dealing_fault_dis(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_STAGE://补加阶段注入
		{
			TGTHT510_1553b_inputcommand_dealing_supply_stage(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_PARA://补加参数注入
		{
			TGTHT510_1553b_inputcommand_dealing_supply_para(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EXHAUST://注入检漏气体排放时间
		{
			TGTHT510_1553b_inputcommand_dealing_exhaust(a,start_i);
			break;	
		}
		
		
		case INPUT_COMMAND_TYPE_MAX_COMP://注入最大抽气时间
		{
			TGTHT510_1553b_inputcommand_dealing_max_comp(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_VELOCITY://注入最大补加速率
		{
			TGTHT510_1553b_inputcommand_dealing_max_velocity(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MIN_VELOCITY://注入最小补加速率
		{
			TGTHT510_1553b_inputcommand_dealing_min_velocity(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_FLOW://注入最大补加流动时间
		{
			TGTHT510_1553b_inputcommand_dealing_max_flow(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_TEMP_CONTR_MODE://注入补加管路温度控制模式
		{
			TGTHT510_1553b_inputcommand_dealing_temp_contr_mode(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_START_MIN://注入压气机启动温度下限
		{
			TGTHT510_1553b_inputcommand_dealing_comp_start_min(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_START_MAX://注入压气机启动温度上限
		{
			TGTHT510_1553b_inputcommand_dealing_comp_start_max(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_ALARM://注入压气机报警温度阈值
		{
			TGTHT510_1553b_inputcommand_dealing_comp_alarm(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COM_COOLER://注入压气机与液冷温度差值
		{
			
			break;	
		}

		case INPUT_COMMAND_TYPE_COMP_PRESSURE://注入压气机正常出口压力
		{
			TGTHT510_1553b_inputcommand_dealing_comp_pressure(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_STOP_PRE://注入压气机停机后出口压力值
		{
			TGTHT510_1553b_inputcommand_dealing_comp_stop_pre(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DP_HIGH://注入高压压力变化幅值
		{
			TGTHT510_1553b_inputcommand_dealing_dp_high(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DP1_LOW://注入低压压力变化幅值1
		{
			TGTHT510_1553b_inputcommand_dealing_dp1_low(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DP2_LOW://注入低压压力变化幅值2
		{
			TGTHT510_1553b_inputcommand_dealing_dp2_low(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_REPRESS://注入最大复压时间
		{
			TGTHT510_1553b_inputcommand_dealing_max_repress(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_START_SPEED://注入压气机启动转速
		{
			TGTHT510_1553b_inputcommand_dealing_comp_start_speed(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_STOP_SPEED://注入压气机停机转速
		{
			TGTHT510_1553b_inputcommand_dealing_comp_stop_speed(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DELAY_SHORT://注入修改短延时
		{
			TGTHT510_1553b_inputcommand_dealing_delay_short(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DELAY_LONG://注入修改长延时
		{
			TGTHT510_1553b_inputcommand_dealing_delay_long(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_BYPATH_TIME://注入修改旁路阀开启时间
		{
			TGTHT510_1553b_inputcommand_dealing_time_bypath(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EPS1://注入修改偏差eps1
		{
			TGTHT510_1553b_inputcommand_dealing_eps1(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EPS2://注入修改偏差eps2
		{
			TGTHT510_1553b_inputcommand_dealing_eps2(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_IN_COMP_MAX://注入修改压气机最大进口压力
		{
			TGTHT510_1553b_inputcommand_dealing_pressure_comp_in_max(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_IN_COMP_MIN://注入修改压气机最小进口压力
		{
			TGTHT510_1553b_inputcommand_dealing_pressure_comp_in_min(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_OUT_COMP_MIN://注入修改压气机最小出口压力
		{
			TGTHT510_1553b_inputcommand_dealing_pressure_comp_out_min(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_HYCT://注入修改货船额定增压压力
		{
			TGTHT510_1553b_inputcommand_dealing_pressure_hyc(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_PIPE_F://注入修改燃补加液路压力传感器设定
		{
			TGTHT510_1553b_inputcommand_dealing_sensor_pipe_F(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_PIPE_O://注入修改氧补加液路压力传感器设定
		{
			TGTHT510_1553b_inputcommand_dealing_sensor_pipe_O(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_TANK_F://注入修改燃贮箱压力传感器设定
		{
			TGTHT510_1553b_inputcommand_dealing_sensor_tank_F(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_TANK_O://注入修改氧贮箱压力传感器设定
		{
			TGTHT510_1553b_inputcommand_dealing_sensor_tank_O(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_IN_COMP://注入修改压气机进口压力传感器设定
		{
			TGTHT510_1553b_inputcommand_dealing_sensor_comp_in(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_LOW_PIPE://注入修改低压气路压力传感器设定
		{
			TGTHT510_1553b_inputcommand_dealing_sensor_pipe_low(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_CONTINUE_G://注入指定补加步骤继续补加
		{
			TGTHT510_1553b_inputcommand_dealing_supply_continue_g(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EQU_COMMAND://注入设备管理指令
		{
			TGTHT510_1553b_inputcommand_dealing_equ_command(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_HEAT_ON://注入加热器通指令
		{
			TGTHT510_1553b_inputcommand_dealing_heat_on(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_PAUSE://注入补加暂停指令
		{
			TGTHT510_1553b_inputcommand_dealing_supply_pause(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_BREAK://注入补加中止指令
		{
			TGTHT510_1553b_inputcommand_dealing_supply_break(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_CONTINUE://注入补加继续指令
		{
			TGTHT510_1553b_inputcommand_dealing_supply_continue(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_CPU_SET://注入CPU状态置位指令
		{
			TGTHT510_1553b_inputcommand_dealing_cpu_set(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_LEAK://注入检漏排气指令
		{
			TGTHT510_1553b_inputcommand_dealing_leak(a,start_i);
			
			break;	
		}
		
		case INPUT_COMMAND_TYPE_STAGE_FAULT://注入阶段故检状态设置
		{
			TGTHT510_1553b_inputcommand_dealing_stage_fault(a,start_i);			
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMPRESSOR_FLAG://注入压气机使用标志，测试指令
		{
			TGTHT510_1553b_inputcommand_dealing_compressor_flag_set(a,start_i);			
			break;	
		}
		
		default:
		{
			break;
		}
		
	}
	
	return result;

}


/******************************************************************************************
**名称：注入指令处理EPDU包格式是否正确
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_is_correct(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i,uint16 length)
{
	uint16 i;
	uint16 data[50];//数组大小待修改
	uint16 checker;
	uint16 type;
	for(i=start_i;i<=start_i+length-1;i++)
	{
		data[i-start_i]=a.inputcommand_data[i];//缓存EPDU数据
	}
	
	if((data[0]&0xff80)!=0x1b00)
	{
		return FALSE;//EPDU包识别错误
	}
	
	if(data[3]!=0x0404)
	{
		return FALSE;//EPDU包服务类型，服务子类型错误
	}
	
	
	checker=TGTHT510_1553b_receivecommand_buscommand_ISO_calculate(data,length-1);
	
	if(data[length-1]!=checker)
	{
		//return FALSE;//EPDU包ISO校验错误
	}
	
	return TRUE;
	
	
}

/******************************************************************************************
**名称：注入指令处理EPDU包长度获取
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_length_get(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 length;
	uint16 type;
	uint16 n;
	
	type=a.inputcommand_data[start_i+4];//注入指令类型
	if(type==INPUT_COMMAND_TYPE_MULTI_CONTR_SPOT)//修改多个控温回路的控温点
	{
		n=a.inputcommand_data[start_i+8];
		length=n+10;
		
	}
		
	else
	{
		length=TGTHT510_1553b_receivecommand_inputcommand_EPDU_length_type_judge(type);
	}
	
	return length;//返回EPDU包全包长度，单位为字
	
}



/******************************************************************************************
**名称：注入指令处理EPDU包长度计算,指令类型是否合法判断分函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_length_type_judge(uint16 type)
{
	uint16 length;
	switch(type)
	{
		case INPUT_COMMAND_TYPE_POWER://修改峰值功耗
		{
			length=INPUT_COMMAND_LEN_POWER;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ALL_CONTR_SPOT://修改全部控温回路的控温点
		{
			length=INPUT_COMMAND_LEN_ALL_CONTR_SPOT;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ONE_MEA_SPOT://修改某一控温回路的控温测点
		{
			length=INPUT_COMMAND_LEN_ONE_MEA_SPOT;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ONE_FIXED://指定某一控温回路按照指定占空比输出
		{
			length=INPUT_COMMAND_LEN_ONE_FIXED;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_AUTO_RESUME://恢复某一控温回路为自动控温状态
		{
			length=INPUT_COMMAND_LEN_AUTO_RESUME;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ALL_RESUME://恢复所有控温回路控温状态
		{
			length=INPUT_COMMAND_LEN_ALL_RESUME;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SOURCE://指定控温参数来源选用
		{
			length=INPUT_COMMAND_LEN_SOURCE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_PLACE_SIGNAL_EN://指定某一路贮箱到位信号使能
		{
			length=INPUT_COMMAND_LEN_PLACE_SIGNAL_EN;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_PLACE_SIGNAL_DIS://指定某一路贮箱到位信号禁止
		{
			length=INPUT_COMMAND_LEN_PLACE_SIGNAL_DIS;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_FAULT_EN://指定某一路故检使能
		{
			length=INPUT_COMMAND_LEN_FAULT_EN;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_FAULT_DIS://指定某一路故检禁止
		{
			length=INPUT_COMMAND_LEN_FAULT_DIS;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_STAGE://补加阶段注入
		{
			length=INPUT_COMMAND_LEN_SUPPLY_STAGE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_PARA://补加参数注入
		{
			length=INPUT_COMMAND_LEN_SUPPLY_PARA;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EXHAUST://注入检漏气体排放时间
		{
			length=INPUT_COMMAND_LEN_EXHAUST;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_COMP://注入最大抽气时间
		{
			length=INPUT_COMMAND_LEN_MAX_COMP;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_VELOCITY://注入最大补加速率
		{
			length=INPUT_COMMAND_LEN_MAX_VELOCITY;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MIN_VELOCITY://注入最小补加速率
		{
			length=INPUT_COMMAND_LEN_MIN_VELOCITY;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_FLOW://注入最大补加流动时间
		{
			length=INPUT_COMMAND_LEN_MAX_FLOW;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_TEMP_CONTR_MODE://注入补加管路温度控制模式
		{
			length=INPUT_COMMAND_LEN_TEMP_CONTR_MODE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_START_MIN://注入压气机启动温度下限
		{
			length=INPUT_COMMAND_LEN_COMP_START_MIN;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_START_MAX://注入压气机启动温度上限
		{
			length=INPUT_COMMAND_LEN_COMP_START_MAX;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_ALARM://注入压气机报警温度阈值
		{
			length=INPUT_COMMAND_LEN_COMP_ALARM;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COM_COOLER://注入压气机与液冷温度差值
		{
			length=INPUT_COMMAND_LEN_COM_COOLER;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_PRESSURE://注入压气机正常出口压力
		{
			length=INPUT_COMMAND_LEN_COMP_PRESSURE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_STOP_PRE://注入压气机停机后出口压力值
		{
			length=INPUT_COMMAND_LEN_COMP_STOP_PRE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DP_HIGH://注入高压压力变化幅值
		{
			length=INPUT_COMMAND_LEN_DP_HIGH;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DP1_LOW://注入低压压力变化幅值1
		{
			length=INPUT_COMMAND_LEN_DP1_LOW;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DP2_LOW://注入低压压力变化幅值2
		{
			length=INPUT_COMMAND_LEN_DP2_LOW;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_REPRESS://注入最大复压时间
		{
			length=INPUT_COMMAND_LEN_MAX_REPRESS;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_START_SPEED://注入压气机启动转速
		{
			length=INPUT_COMMAND_LEN_COMP_START_SPEED;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_STOP_SPEED://注入压气机停机转速
		{
			length=INPUT_COMMAND_LEN_COMP_STOP_SPEED;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DELAY_SHORT://注入修改短延时
		{
			length=INPUT_COMMAND_LEN_DELAY_SHORT;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DELAY_LONG://注入修改长延时
		{
			length=INPUT_COMMAND_LEN_DELAY_LONG;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_BYPATH_TIME://注入修改旁路阀开启时间
		{
			length=INPUT_COMMAND_LEN_BYPATH_TIME;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EPS1://注入修改偏差eps1
		{
			length=INPUT_COMMAND_LEN_EPS1;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EPS2://注入修改偏差eps2
		{
			length=INPUT_COMMAND_LEN_EPS2;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_IN_COMP_MAX://注入修改压气机最大进口压力
		{
			length=INPUT_COMMAND_LEN_IN_COMP_MAX;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_IN_COMP_MIN://注入修改压气机最小进口压力
		{
			length=INPUT_COMMAND_LEN_IN_COMP_MIN;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_OUT_COMP_MIN://注入修改压气机最小出口压力
		{
			length=INPUT_COMMAND_LEN_OUT_COMP_MIN;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_HYCT://注入修改货船额定增压压力
		{
			length=INPUT_COMMAND_LEN_HYCT;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_PIPE_F://注入修改燃补加液路压力传感器设定
		{
			length=INPUT_COMMAND_LEN_SENSOR_PIPE_F;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_PIPE_O://注入修改氧补加液路压力传感器设定
		{
			length=INPUT_COMMAND_LEN_SENSOR_PIPE_O;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_TANK_F://注入修改燃贮箱压力传感器设定
		{
			length=INPUT_COMMAND_LEN_SENSOR_TANK_F;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_TANK_O://注入修改氧贮箱压力传感器设定
		{
			length=INPUT_COMMAND_LEN_SENSOR_TANK_O;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_IN_COMP://注入修改压气机进口压力传感器设定
		{
			length=INPUT_COMMAND_LEN_SENSOR_IN_COMP;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_LOW_PIPE://注入修改低压气路压力传感器设定
		{
			length=INPUT_COMMAND_LEN_SENSOR_LOW_PIPE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_CONTINUE_G://注入指定补加步骤继续补加
		{
			length=INPUT_COMMAND_LEN_SUPPLY_CONTINUE_G;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EQU_COMMAND://注入设备管理指令
		{
			length=INPUT_COMMAND_LEN_EQU_COMMAND;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_HEAT_ON://注入加热器通指令
		{
			length=INPUT_COMMAND_LEN_HEAT_ON;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_PAUSE://注入补加暂停指令
		{
			length=INPUT_COMMAND_LEN_SUPPLY_PAUSE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_BREAK://注入补加中止指令
		{
			length=INPUT_COMMAND_LEN_SUPPLY_BREAK;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_CONTINUE://注入补加继续指令
		{
			length=INPUT_COMMAND_LEN_SUPPLY_CONTINUE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_CPU_SET://注入CPU状态置位指令
		{
			length=INPUT_COMMAND_LEN_CPU_SET;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_LEAK://注入检漏排气指令
		{
			length=INPUT_COMMAND_LEN_SUPPLY_LEAK;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_STAGE_FAULT://注入阶段故检状态设置
		{
			length=INPUT_COMMAND_LEN_STAGE_FAULT;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMPRESSOR_FLAG://注入压气机使用标志，测试指令
		{
			length=INPUT_COMMAND_LEN_COMPRESSOR_FLAG;
			break;	
		}
		
		
		default:
		{
			length=INPUT_COMMAND_LEN_UNKNOW;//注入指令类型非法
			break;
		}

	}
	
	return length;

}

/******************************************************************************************
**名称：注入指令处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_receivecommand_inputcommand_dealing(TGTHT510_1553B_inputcommand_TypeDef a)
{
	uint16 i;
	uint16 EPDU_num;//EPDU遥控包序列数量
	uint16 EPDU_result;
	uint16 temp;
	
	EPDU_num=a.inputcommand_data[0];//EPDU遥控包序列数量
	
	if(EPDU_num==0)
	{
		CG_inputcommand_receive_state_data[0]=INPUT_COMMAND_EPDU_NUM_ERROR;
		CG_inputcommand_receive_state_data[1]=INPUT_COMMAND_EPDU_NUM_ERROR;//源包序列数量错误，常规遥测传送AAAAH
		
		return;//源包序列数量错误，退出函数
	}
	
	i=0x0001;
	while(EPDU_num!=0)
	{
		EPDU_num--;
		EPDU_result=TGTHT510_1553b_receivecommand_inputcommand_EPDU_dealing(a,i);
		
		temp=EPDU_result&0xc000;
		if(temp==0xc000)
		{
			CG_inputcommand_receive_state_data[0]=INPUT_COMMAND_EPDU_DEAL_ERROR;
			CG_inputcommand_receive_state_data[1]=INPUT_COMMAND_EPDU_DEAL_ERROR;//EPDU包处理出错，常规遥测传送BBBBH
			return;//EPDU包处理出错，退出处理函数
		}
		
		temp=EPDU_result&0x3fff;
		
		TGTHT510_1553b_receivecommand_inputcommand_state_data(a,i,temp);//常规遥测传送最后一个注入EPDU的指令类型与校验和
		
		i=i+temp;

	}

}


/******************************************************************************************
**名称：接收注入指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_receivecommand_inputcommand(uint16 which_bu65170)
{
	TGTHT510_1553B_inputcommand_TypeDef inputcommand;
	uint16 correct;
	
	inputcommand=TGTHT510_1553b_receivecommand_inputcommand_save(which_bu65170);//缓存输入指令内容至结构体数据中
	
	correct=TGTHT510_1553b_receivecommand_inputcommand_is_correct(inputcommand);//判断注入指令格式是否正确
	
	if(correct==FALSE)
	{
		return;//注入指令格式错误，退出注入指令处理函数
	}
	
	TGTHT510_1553b_receivecommand_inputcommand_dealing(inputcommand);//注入指令处理
	
}

/******************************************************************************************
**名称：接收货船补加状态信息数据
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：

-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_receivedata_HYCT1100(uint16 which_bu65170,uint16 type)
{
	uint16 temp[38];
	
	uint16 i;
	
	if(type==TYPE_RECEIVE_HYCT_DATA1)
	{
		
		if(which_bu65170==BU65170_Z)
		{
			
			if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_HYCT1100_DATA1_BASE+4*0*2,temp,38)==FALSE)
			{
				return;
			}
		}
		
		else if(which_bu65170==BU65170_B)
		{
			if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_HYCT1100_DATA1_BASE+4*0*2,temp,38)==FALSE)
			{
				return;
			}
		}
		
		else
		{
			return;
		}
		
		for(i=0;i<=31;i++)
		{	
			TGTHT510_1553B_R_HYCT1100_data1[i]=temp[i+5];
		}
		
	}
	
	else if(type==TYPE_RECEIVE_HYCT_DATA2)
	{
		if(which_bu65170==BU65170_Z)
		{
			if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_HYCT1100_DATA2_BASE+4*0*2,temp,38)==FALSE)
			{
				return;
			}
		}
		
		else if(which_bu65170==BU65170_B)
		{
			if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_HYCT1100_DATA2_BASE+4*0*2,temp,38)==FALSE)
			{
				return;
			}
		}
		
		else
		{
			return;
		}
		
		for(i=0;i<=31;i++)
		{	
			TGTHT510_1553B_R_HYCT1100_data2[i]=temp[i+5];
		}
	}
	
	else
	{
		asm("nop;");
	}
}

/******************************************************************************************
**名称：接收数管遥测
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_receivedata_KPU(uint16 which_bu65170)
{
	uint16 temp[111];
	
	uint16 i;
	
	if(which_bu65170==BU65170_Z)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_KPU_BASE+4*0*2,temp,111)==FALSE)
		{
			return;
		}
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_KPU_BASE+4*0*2,temp,111)==FALSE)
		{
			return;
		}
	}
	
	else
	{
		return;
	}
	
	for(i=0;i<=104;i++)
	{	
		TGTHT510_1553B_data_KPU[i]=temp[i+5];
	}
	
}

/******************************************************************************************
**名称：接收勤务指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_receivecommand_interactivecommand(uint16 which_bu65170)
{
	uint16 temp[256];
	
	uint16 i;
	
	if(which_bu65170==BU65170_Z)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_Z_R_INTER_COMMAND_BASE+4*0*2,temp,256)==FALSE)
		{
			return;
		}
	}
	
	else if(which_bu65170==BU65170_B)
	{
		if(TGTHT510_1553b_get_data(which_bu65170,BU65170_B_R_INTER_COMMAND_BASE+4*0*2,temp,256)==FALSE)
		{
			return;
		}
	}
	
	else
	{
		return;
	}
	
	for(i=0;i<=224;i=i+32)
	{
		if(temp[i]==0)
		{
			break;
		}
		
		if(temp[0]==0x1515)//内存下传子地址
		{
			TGTHT510_1553b_transmitdata_MEMORY(which_bu65170);
			
			
		}
		
		
	}
	
}


/******************************************************************************************
**名称：总线指令，继电器动作处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_relay_dealing(uint16 code)
{
	uint16 reg;
	
	reg=0x5555;
	
	
	switch(code)
	{
		case BUS_MAIN_HEATER_POWER_ON://推进主份加热器供电通
		{
			reg=(reg&BUS_MAIN_HEATER_POWER_ON_AND)|BUS_MAIN_HEATER_POWER_ON_OR;
			
			*(volatile uint32 *)(BUS_RELAY_HEATER_ON_BASE_ADDRESS)=Write_16_to_32(reg);
			
			return;
			
			break;
		}
		
		case BUS_MAIN_HEATER_POWER_OFF://推进主份加热器供电断
		{
			reg=(reg&BUS_MAIN_HEATER_POWER_OFF_AND)|BUS_MAIN_HEATER_POWER_OFF_OR;
			break;
		}
		
		case BUS_LESS_HEATER_POWER_ON://推进备份加热器供电通
		{
			reg=(reg&BUS_LESS_HEATER_POWER_ON_AND)|BUS_LESS_HEATER_POWER_ON_OR;
			
			*(volatile uint32 *)(BUS_RELAY_HEATER_ON_BASE_ADDRESS)=Write_16_to_32(reg);
			
			return;
			
			break;
		}
		
		case BUS_LESS_HEATER_POWER_OFF://推进备份加热器供电断
		{
			reg=(reg&BUS_LESS_HEATER_POWER_OFF_AND)|BUS_LESS_HEATER_POWER_OFF_OR;
			break;
		}
		
		case BUS_COOLER_1_MAIN_POWER_ON://液冷模块I主泵供电通
		{
			reg=(reg&BUS_COOLER_1_MAIN_POWER_ON_AND)|BUS_COOLER_1_MAIN_POWER_ON_OR;
			break;
		}
		
		case BUS_COOLER_1_LESS_POWER_ON://液冷模块I备泵供电通
		{
			reg=(reg&BUS_COOLER_1_LESS_POWER_ON_AND)|BUS_COOLER_1_LESS_POWER_ON_OR;
			break;
		}
		
		case BUS_COOLER_1_POWER_OFF://液冷模块I主、备泵供电断
		{
			reg=(reg&BUS_COOLER_1_POWER_OFF_AND)|BUS_COOLER_1_POWER_OFF_OR;
			break;
		}
		
		case BUS_COOLER_2_MAIN_POWER_ON://液冷模块II主泵供电通
		{
			reg=(reg&BUS_COOLER_2_MAIN_POWER_ON_AND)|BUS_COOLER_2_MAIN_POWER_ON_OR;
			break;
		}
		
		case BUS_COOLER_2_LESS_POWER_ON://液冷模块II备泵供电通
		{
			reg=(reg&BUS_COOLER_2_LESS_POWER_ON_AND)|BUS_COOLER_2_LESS_POWER_ON_OR;
			break;
		}
		
		case BUS_COOLER_2_POWER_OFF://液冷模块II主、备泵供电断
		{
			reg=(reg&BUS_COOLER_2_POWER_OFF_AND)|BUS_COOLER_2_POWER_OFF_OR;
			break;
		}
		
		default:
		{
			break;
		}
	}
	
	*(volatile uint32 *)(BUS_RELAY_BASE_ADDRESS)=Write_16_to_32(reg);

}


/******************************************************************************************
**名称：注入指令处理函数：修改峰值功耗
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_power(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	Temperature_control_global.total_power=a.inputcommand_data[start_i+5];
}

/******************************************************************************************
**名称：注入指令处理函数：修改多个控温回路的控温点
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_multi_contr_spot(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 t1,t2,t3;
	uint16 n;
	uint16 i;
	uint16 xx;
	
	t1=a.inputcommand_data[start_i+5];//控温点T1
	t2=a.inputcommand_data[start_i+6];//控温点T2
	t3=a.inputcommand_data[start_i+7];//控温点T3
	
	if((t1>t2)&&(t2>t3))//需T1温度低于T2温度，T2温度低于T3温度
	{
		asm("nop;");
	}
	
	else
	{
		return;
	}
	
	n=a.inputcommand_data[start_i+8];//需要修改的控温回路的路数
	
	if((n==0)||(n>50))//控温回路的路数值非法
	{
		return;
	}
	
	for(i=0;i<=n-1;i++)
	{
		if(a.inputcommand_data[start_i+9+i]>49)//控温回路的路号非法
		{
			return;
		}
		
		else
		{
			asm("nop;");
		}
	}
	
	for(i=0;i<=n-1;i++)//更新控温点T1、T2、T3
	{
		xx=a.inputcommand_data[start_i+9+i];
		Temperature_control_block[xx].control_spot[0]=t1;
		Temperature_control_block[xx].control_spot[1]=t2;
		Temperature_control_block[xx].control_spot[2]=t3;
	}

}


/******************************************************************************************
**名称：注入指令处理函数：修改全部控温回路的控温点
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_all_contr_spot(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 t1,t2,t3;
	uint16 i;
	
	t1=a.inputcommand_data[start_i+5];//控温点T1
	t2=a.inputcommand_data[start_i+6];//控温点T2
	t3=a.inputcommand_data[start_i+7];//控温点T3
	
	if((t1>t2)&&(t2>t3))//需T1温度低于T2温度，T2温度低于T3温度
	{
		asm("nop;");
	}
	
	else
	{
		return;
	}
	
	for(i=0;i<=49;i++)//更新控温点T1、T2、T3
	{
		Temperature_control_block[i].control_spot[0]=t1;
		Temperature_control_block[i].control_spot[1]=t2;
		Temperature_control_block[i].control_spot[2]=t3;
	}

}


/******************************************************************************************
**名称：注入指令处理函数：修改某一控温回路的控温测点
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_one_mea_spot(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 n;			//修改的控温回路的路号
	uint16 temp[7];		//控温测点的代号
	uint16 i;
	
	n=a.inputcommand_data[start_i+5];
	
	if(n>50)			//控温回路的路号值非法
	{
		return;
	}
	
	for(i=0;i<=6;i++)
	{
		temp[i]=a.inputcommand_data[start_i+6+i];//测点代号
		
		if(temp[i]!=0xffff)
		{
			//Bit15~14为00表示测点温度传感器为MF51，为01表示测点温度传感器为铂电阻，为10表示测点温度传感器为MF61
			if((temp[i]&0xc000)==0xc000)
			{
				return;
			}
			
			//Bit13~12为01表示该测点温度值位于复帧A帧，为10表示该测点温度值位于复帧B帧；
			if(((temp[i]&0x3000)==0x3000)||((temp[i]&0x3000)==0x0000))
			{
				return;
			}
			
			//Bit11~10为00表示在遥测帧中为字（16位）表示，为01表示在遥测帧中为高字节（8位）表示，为10表示在遥测帧中为低字节（8位）表示；
			if((temp[i]&0x0c00)==0x0c00)
			{
				return;
			}

		}
		
		else
		{
			asm("nop;");
		}		
	}
	
	
	for(i=0;i<=6;i++)//更新控温测点
	{
		Temperature_control_block[n].source_data[i]=temp[i];
	}
	
	

}


/******************************************************************************************
**名称：注入指令处理函数：指定某一控温回路按照指定占空比输出
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_one_fixed(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 n;				//修改的控温回路的路号
	uint16 fixed_count;		//占空比脉宽
	
	n=a.inputcommand_data[start_i+5];
	
	if(n>50)			//控温回路的路号值非法
	{
		return;
	}
	
	fixed_count=a.inputcommand_data[start_i+6];
	
	if(fixed_count==0x0000)//若脉宽为零，则本次注入无效
	{
		return;
	}
	
	else
	{
		Temperature_control_block[n].fixed_output_state=ENABLE;
		
		Temperature_control_block[n].fixed_output_count=fixed_count+1;
	}
}


/******************************************************************************************
**名称：注入指令处理函数：恢复某一控温回路为自动控温模式
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_inputcommand_dealing_auto_resume(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 n;				//修改的控温回路的路号
	
	n=a.inputcommand_data[start_i+5];
	
	if(n>50)			//控温回路的路号值非法
	{
		return;
	}
	
	Temperature_control_block[n].fixed_output_state=DISABLE;
		
	Temperature_control_block[n].fixed_output_count=0x0000;
	
}


/******************************************************************************************
**名称：注入指令处理函数：恢复所有控温回路控温状态
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_all_resume(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0x4e4e)
	{
		TGTHT510_tempercontrol_initial();
	}
	
	else
	{
		asm("nop;");
	}
}


/******************************************************************************************
**名称：注入指令处理函数：指定控温参数来源选择
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_source(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0xe5e5)
	{
		//控温使用遥测数据来源，推进遥测线路盒
		Temperature_control_global.source=SOURCE_DATA_TGTHT100;

	}
	
	else if(temp==0xc5c5)
	{
		//控温使用遥测数据来源，数管KPU
		Temperature_control_global.source=SOURCE_DATA_KPU;
	}
	
	else
	{
		asm("nop;");
	}

}



/******************************************************************************************
**名称：注入指令处理函数：指定某一路贮箱到位信号使能
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_place_signal_en(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0xa1a1)
	{
		TGTHT510_tank_position_set(TANK_O1_POSITION,ENABLE);
	}
	
	else if(temp==0xa2a2)
	{
		TGTHT510_tank_position_set(TANK_O2_POSITION,ENABLE);
	}
	
	else if(temp==0xa4a4)
	{
		TGTHT510_tank_position_set(TANK_O3_POSITION,ENABLE);
	}
	
	else if(temp==0xa7a7)
	{
		TGTHT510_tank_position_set(TANK_F1_POSITION,ENABLE);
	}
	
	else if(temp==0xa9a9)
	{
		TGTHT510_tank_position_set(TANK_F2_POSITION,ENABLE);
	}
	
	else if(temp==0xabab)
	{
		TGTHT510_tank_position_set(TANK_F3_POSITION,ENABLE);
	}
	
	else
	{
		asm("nop;");
	}

}

/******************************************************************************************
**名称：注入指令处理函数：指定某一路贮箱到位信号禁止
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_place_signal_dis(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0xa1a1)
	{
		TGTHT510_tank_position_set(TANK_O1_POSITION,DISABLE);
	}
	
	else if(temp==0xa2a2)
	{
		TGTHT510_tank_position_set(TANK_O2_POSITION,DISABLE);
	}
	
	else if(temp==0xa4a4)
	{
		TGTHT510_tank_position_set(TANK_O3_POSITION,DISABLE);
	}
	
	else if(temp==0xa7a7)
	{
		TGTHT510_tank_position_set(TANK_F1_POSITION,DISABLE);
	}
	
	else if(temp==0xa9a9)
	{
		TGTHT510_tank_position_set(TANK_F2_POSITION,DISABLE);
	}
	
	else if(temp==0xabab)
	{
		TGTHT510_tank_position_set(TANK_F3_POSITION,DISABLE);
	}
	
	else
	{
		asm("nop;");
	}

}


/******************************************************************************************
**名称：注入指令处理函数：指定某一路故检使能
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_fault_en(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	TGTHT510_faultdiagnosis_enable_disable_set(temp,ENABLE);

}


/******************************************************************************************
**名称：注入指令处理函数：指定某一路故检禁止
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_fault_dis(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	TGTHT510_faultdiagnosis_enable_disable_set(temp,DISABLE);

}



/******************************************************************************************
**名称：注入指令处理函数：补加阶段注入
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_supply_stage(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0x0000)//补加空闲阶段
	{
		TGTHT510_supply_ctrl.stage=temp;
		
		TGTHT510_supply_ctrl.step=STEP_NONE;
	
		TGTHT510_supply_ctrl.command=COMMAND_NONE;
		
		TGTHT510_supply_ctrl.state=STATE_NONE;
		
		TGTHT510_supply_ctrl.errno=ERRNO_NONE;
	
		TGTHT510_supply_time_stage_end();
	}
	
	else
	{
		TGTHT510_supply_ctrl.stage=temp;
	
		TGTHT510_supply_ctrl.step=STEP_START;
		
		TGTHT510_supply_ctrl.command=COMMAND_START;
		
		TGTHT510_supply_ctrl.state=STATE_RUN;
		
		TGTHT510_supply_ctrl.errno=ERRNO_NONE;
		
		TGTHT510_supply_time_stage_end();
	}
	

}



/******************************************************************************************
**名称：注入指令处理函数：补加参数注入
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_supply_para(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	
	temp=a.inputcommand_data[start_i+5];
	
	TGTHT510_supply_input_par.interface_F=(uint8)(temp>>8);//燃补加接口
	TGTHT510_supply_input_par.interface_O=(uint8)(temp>>0);//氧补加接口
	
	temp=a.inputcommand_data[start_i+6];
	
	TGTHT510_supply_input_par.sequence_tank_F=(uint8)(temp>>8);//燃贮箱补加顺序
	TGTHT510_supply_input_par.sequence_tank_O=(uint8)(temp>>0);//氧贮箱补加顺序
	
	temp=a.inputcommand_data[start_i+7];
	
	TGTHT510_supply_input_par.sequence_gas_F1=(uint8)(temp>>8);//燃贮箱F1气瓶抽气顺序
	TGTHT510_supply_input_par.sequence_gas_F2=(uint8)(temp>>0);//燃贮箱F2气瓶抽气顺序
	
	temp=a.inputcommand_data[start_i+8];
	
	TGTHT510_supply_input_par.sequence_gas_F3=(uint8)(temp>>8);//燃贮箱F3气瓶抽气顺序
	TGTHT510_supply_input_par.sequence_gas_O1=(uint8)(temp>>0);//氧贮箱O1气瓶抽气顺序
	
	temp=a.inputcommand_data[start_i+9];
	
	TGTHT510_supply_input_par.sequence_gas_O2=(uint8)(temp>>8);//氧贮箱O2气瓶抽气顺序
	TGTHT510_supply_input_par.sequence_gas_O3=(uint8)(temp>>0);//氧贮箱O3气瓶抽气顺序
	
	temp=a.inputcommand_data[start_i+10];
	
	TGTHT510_supply_input_par.compressor_out_valve=temp;//抽气压气机号，与开启的压气机出口阀门
	
	temp=a.inputcommand_data[start_i+11];
	
	TGTHT510_supply_input_par.pressure_first_F1=temp;//燃贮箱F1第一个抽气贮箱末压
	
	temp=a.inputcommand_data[start_i+12];
	
	TGTHT510_supply_input_par.pressure_second_F1=temp;//燃贮箱F1第二个抽气贮箱末压
	
	temp=a.inputcommand_data[start_i+13];
	
	TGTHT510_supply_input_par.pressure_first_F2=temp;//燃贮箱F2第一个抽气贮箱末压
	
	temp=a.inputcommand_data[start_i+14];
	
	TGTHT510_supply_input_par.pressure_second_F2=temp;//燃贮箱F2第二个抽气贮箱末压
	
	temp=a.inputcommand_data[start_i+15];
	
	TGTHT510_supply_input_par.pressure_first_F3=temp;//燃贮箱F3第一个抽气贮箱末压
	
	temp=a.inputcommand_data[start_i+16];
	
	TGTHT510_supply_input_par.pressure_second_F3=temp;//燃贮箱F3第二个抽气贮箱末压
	
	temp=a.inputcommand_data[start_i+17];
	
	TGTHT510_supply_input_par.pressure_first_O1=temp;//氧贮箱O1第一个抽气贮箱末压
	
	temp=a.inputcommand_data[start_i+18];
	
	TGTHT510_supply_input_par.pressure_second_O1=temp;//氧贮箱O1第二个抽气贮箱末压
	
	temp=a.inputcommand_data[start_i+19];
	
	TGTHT510_supply_input_par.pressure_first_O2=temp;//氧贮箱O2第一个抽气贮箱末压
	
	temp=a.inputcommand_data[start_i+20];
	
	TGTHT510_supply_input_par.pressure_second_O2=temp;//氧贮箱O2第二个抽气贮箱末压
	
	temp=a.inputcommand_data[start_i+21];
	
	TGTHT510_supply_input_par.pressure_first_O3=temp;//氧贮箱O3第一个抽气贮箱末压
	
	temp=a.inputcommand_data[start_i+22];
	
	TGTHT510_supply_input_par.pressure_second_O3=temp;//氧贮箱O3第二个抽气贮箱末压
	
	temp=a.inputcommand_data[start_i+23];
	
	TGTHT510_supply_input_par.pump_cooler=temp;//使用的液冷模块泵号
	
	temp=a.inputcommand_data[start_i+24];
	
	TGTHT510_supply_input_par.volum_F1=temp;//燃贮箱F1补加到位剩余量
	
	temp=a.inputcommand_data[start_i+25];
	
	TGTHT510_supply_input_par.volum_F2=temp;//燃贮箱F2补加到位剩余量
	
	temp=a.inputcommand_data[start_i+26];
	
	TGTHT510_supply_input_par.volum_F3=temp;//燃贮箱F3补加到位剩余量
	
	temp=a.inputcommand_data[start_i+27];
	
	TGTHT510_supply_input_par.volum_O1=temp;//氧贮箱O1补加到位剩余量
	
	temp=a.inputcommand_data[start_i+28];
	
	TGTHT510_supply_input_par.volum_O2=temp;//氧贮箱O2补加到位剩余量
	
	temp=a.inputcommand_data[start_i+29];
	
	TGTHT510_supply_input_par.volum_O3=temp;//氧贮箱O3补加到位剩余量
	
	temp=a.inputcommand_data[start_i+30];
	
	TGTHT510_supply_input_par.mode=temp;//补加模式
	
	temp=a.inputcommand_data[start_i+31];
	
	TGTHT510_supply_input_par.pressure_repre_F1=temp;//燃贮箱F1复压压力值
	
	temp=a.inputcommand_data[start_i+32];
	
	TGTHT510_supply_input_par.pressure_repre_F2=temp;//燃贮箱F2复压压力值
	
	temp=a.inputcommand_data[start_i+33];
	
	TGTHT510_supply_input_par.pressure_repre_F3=temp;//燃贮箱F3复压压力值
	
	temp=a.inputcommand_data[start_i+34];
	
	TGTHT510_supply_input_par.pressure_repre_O1=temp;//氧贮箱O1复压压力值
	
	temp=a.inputcommand_data[start_i+35];
	
	TGTHT510_supply_input_par.pressure_repre_O2=temp;//氧贮箱O2复压压力值
	
	temp=a.inputcommand_data[start_i+36];
	
	TGTHT510_supply_input_par.pressure_repre_O3=temp;//氧贮箱O3复压压力值
	
	TGTHT510_supply_ctrl.receive=TRUE;
	
	
}


/******************************************************************************************
**名称：注入指令处理函数：注入检漏气体排放时间
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_exhaust(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	TGTHT510_supply_input_par.time_exhaust=(uint32)(temp);

}



/******************************************************************************************
**名称：注入指令处理函数：注入最大抽气时间
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_max_comp(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp1,temp2;
	
	temp1=a.inputcommand_data[start_i+5];
	
	temp2=a.inputcommand_data[start_i+6];
	
	TGTHT510_supply_input_par.time_comp_max=(((uint32)(temp1))<<16)|((uint32)(temp2));

}


/******************************************************************************************
**名称：注入指令处理函数：注入最大补加速率
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_max_velocity(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.velocity_max=a.inputcommand_data[start_i+5];

}



/******************************************************************************************
**名称：注入指令处理函数：注入最小补加速率
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_min_velocity(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.velocity_min=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入最大补加流动时间
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_max_flow(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.time_flow_max=a.inputcommand_data[start_i+5];

}



/******************************************************************************************
**名称：注入指令处理函数：注入补加管路温度控制模式
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_temp_contr_mode(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	

}


/******************************************************************************************
**名称：注入指令处理函数：注入压气机启动温度下限
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_start_min(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.temperature_start_min=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**名称：注入指令处理函数：注入压气机启动温度上限
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_start_max(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.temperature_start_max=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**名称：注入指令处理函数：注入压气机报警温度阈值
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_alarm(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.temperature_alarm=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入压气机与液冷温度差值
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_cooler(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.temperature_comp_cooler=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入压气机正常出口压力
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_pressure(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.pressure_comp_out=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入压气机停机后出口压力值
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_stop_pre(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.pressure_comp_out_stop=a.inputcommand_data[start_i+5];

}



/******************************************************************************************
**名称：注入指令处理函数：注入高压压力变化幅值
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_dp_high(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.dp_high=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**名称：注入指令处理函数：注入低压压力变化幅值1
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_dp1_low(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.dp1_low=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**名称：注入指令处理函数：注入低压压力变化幅值2
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_dp2_low(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.dp2_low=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**名称：注入指令处理函数：注入最大复压时间
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_max_repress(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp1,temp2;
	
	temp1=a.inputcommand_data[start_i+5];
	
	temp2=a.inputcommand_data[start_i+6];
	
	TGTHT510_supply_input_par.time_repre_max=(((uint32)(temp1))<<16)|((uint32)(temp2));

}

/******************************************************************************************
**名称：注入指令处理函数：注入压气机启动转速
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_start_speed(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.v_comp_start=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**名称：注入指令处理函数：注入压气机停机转速
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_stop_speed(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.v_comp_stop=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改短延时
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_delay_short(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.time_delay_short=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改长延时
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_delay_long(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.time_delay_long=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改旁路阀开启时间
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_time_bypath(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.time_bypath=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改偏差1
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_eps1(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.eps1=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改偏差2
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_eps2(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.eps2=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改压气机最大进口压力
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_pressure_comp_in_max(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.pressure_comp_in_max=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改压气机最小进口压力
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_pressure_comp_in_min(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.pressure_comp_in_min=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改压气机最小出口压力
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_pressure_comp_out_min(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.pressure_comp_out_min=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改货运飞船额定增压压力
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_pressure_hyc(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.pressure_hyc=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改燃补加液路压力传感器设定
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_sensor_pipe_F(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.sensor_pipe_F=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改氧补加液路压力传感器设定
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_sensor_pipe_O(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.sensor_pipe_O=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改燃贮箱压力传感器设定
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_sensor_tank_F(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.sensor_tank_F=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改氧贮箱压力传感器设定
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_sensor_tank_O(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.sensor_tank_O=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改压气机进口压力传感器设定
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_sensor_comp_in(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.sensor_comp_in=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**名称：注入指令处理函数：注入修改低压气路压力传感器设定
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_sensor_pipe_low(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.sensor_pipe_low=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**名称：注入指令处理函数：指定补加步骤继续补加
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_supply_continue_g(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	TGTHT510_supply_ctrl.step_temp=temp;
	
	temp=a.inputcommand_data[start_i+6];
	
	TGTHT510_supply_ctrl.command_temp=temp;
	
	TGTHT510_supply_ctrl.errno=0;
	
	TGTHT510_supply_ctrl.state=STATE_PAUSE_RESUME;
	
	TGTHT510_supply_ctrl.step=STEP_START;
	
	TGTHT510_supply_ctrl.command=COMMAND_START;

}



/******************************************************************************************
**名称：注入设备管理指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_equ_command(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 type;
	type=a.inputcommand_data[start_i+5];
	
	switch(type)
	{
		case INPUT_COMMAND_TYPE_TGTHT530a_ON_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(TGTHT530a_ON_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_TGTHT530b_ON_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(TGTHT530b_ON_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_TGTHT530c_ON_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(TGTHT530c_ON_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_TGTHT530a_OFF_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(TGTHT530a_OFF_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_TGTHT530b_OFF_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(TGTHT530b_OFF_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_TGTHT530c_OFF_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(TGTHT530c_OFF_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_COMPRESS_A_ON_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_A_ON_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_COMPRESS_B_ON_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_B_ON_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_COMPRESS_C_ON_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_C_ON_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_COMPRESS_A_OFF_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_A_OFF_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_COMPRESS_B_OFF_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_B_OFF_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_COMPRESS_C_OFF_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_C_OFF_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_COMPRESS_A_START:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_A_START);
			break;
		}
		
		case INPUT_COMMAND_TYPE_COMPRESS_B_START:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_B_START);
			break;
		}
		
		case INPUT_COMMAND_TYPE_COMPRESS_C_START:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_C_START);
			break;
		}
		
		case INPUT_COMMAND_TYPE_COMPRESS_A_STOP:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_A_STOP);
			break;
		}
		
		case INPUT_COMMAND_TYPE_COMPRESS_B_STOP:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_B_STOP);
			break;
		}
		
		case INPUT_COMMAND_TYPE_COMPRESS_C_STOP:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_C_STOP);
			break;
		}
		
		case INPUT_COMMAND_TYPE_VALVE_SUPPLY_ON_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(VALVE_SUPPLY_ON_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_VALVE_SUPPLY_OFF_POWER:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(VALVE_SUPPLY_OFF_POWER);
			break;
		}
		
		case INPUT_COMMAND_TYPE_LVt1K:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(LVt1K);
			break;
		}
		
		case INPUT_COMMAND_TYPE_LVt1G:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(LVt1G);
			break;
		}
		
		case INPUT_COMMAND_TYPE_LVt6K:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(LVt6K);
			break;
		}
		
		case INPUT_COMMAND_TYPE_LVt6G:
		{
			TGTHT510_collectANDgroup_equiment_command_generate(LVt6G);
			break;
		}
		
		default:
		{
			break;
		}

	}
	

}


/******************************************************************************************
**名称：注入加热器开指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_heat_on(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 num,heat_num;
	uint16 type;
	num=a.inputcommand_data[start_i+5];
	heat_num=(num&0x00ff);
	
	if(heat_num>=50)
	{
		return;
	}
	
	if((num&0xff00)==0xaa00)
	{
		type=HEATER_MAIN;
	}
	
	else if((num&0xff00)==0xbb00)
	{
		type=HEATER_LESS;
	}
	
	else if((num&0xff00)==0xcc00)
	{
		type=HEATER_BOTH;
	}
	
	TGTHT510_tempercontrol_reg_setbit(heat_num,type);
	
}


/******************************************************************************************
**名称：注入指令处理函数：注入补加暂停指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_supply_pause(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0xaa55)
	{
		TGTHT510_supply_ctrl.step_temp=TGTHT510_supply_ctrl.step;
	
		TGTHT510_supply_ctrl.command_temp=TGTHT510_supply_ctrl.command;
		
		TGTHT510_supply_ctrl.state=STATE_PAUSE;
	
		TGTHT510_supply_ctrl.step=STEP_START;
	
		TGTHT510_supply_ctrl.command=COMMAND_START;
		
	}
	
	else
	{
		asm("nop;");
	}

}

/******************************************************************************************
**名称：注入指令处理函数：注入补加中止指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_supply_break(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0x55aa)
	{
		TGTHT510_supply_ctrl.state=STATE_BREAK;
	
		TGTHT510_supply_ctrl.step=STEP_START;
	
		TGTHT510_supply_ctrl.command=COMMAND_START;
		
	}
	
	else
	{
		asm("nop;");
	}

}

/******************************************************************************************
**名称：注入指令处理函数：注入补加暂停指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_supply_continue(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0x7788)
	{
		
        if(TGTHT510_supply_ctrl.state==STATE_PAUSE)
		{
			TGTHT510_supply_ctrl.errno=ERRNO_NONE;
	
			TGTHT510_supply_ctrl.state=STATE_PAUSE_RESUME;
	
			TGTHT510_supply_ctrl.step=STEP_START;
	
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
		}
		
		else
		{
			asm("nop;");
		}
		
	}
	
	else
	{
		asm("nop;");
	}

}


/******************************************************************************************
**名称：注入指令处理函数：注入补加暂停指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_cpu_set(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0xaa22)//置A机为正确
	{
		CPU_ON();
	}
	
	else if(temp==0xaa44)//置A机为错误
	{
		CPU_OFF();
		
	}
	
	else if(temp==0xbb22)//置B机为正确
	{
		
		
	}
	
	else if(temp==0xbb44)//置B机为错误
	{
		
		
	}
	
	else
	{
		asm("nop;");
	}

}

/******************************************************************************************
**名称：注入指令处理函数：注入检漏排气指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_inputcommand_dealing_leak(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0xa5a5)
	{
		TGTHT510_supply_ctrl.leak_flag=TRUE;
	}
	
}


/******************************************************************************************
**名称：注入指令处理函数：注入阶段故检状态设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_inputcommand_dealing_stage_fault(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	switch(temp)
	{
		case 0x0101://发射段故检
		{
			TGTHT510_faultdiagnosis_push_set_stage_launch();
			TGTHT510_faultdiagnosis_supply_set_stage_launch();
			break;
		}
		
		case 0x0202://变轨段故检
		{
			TGTHT510_faultdiagnosis_push_set_stage_orbit();
			TGTHT510_faultdiagnosis_supply_set_stage_orbit();
			break;
		}
		
		case 0x0303://巡检段故检
		{
			TGTHT510_faultdiagnosis_push_set_stage_polling();
			TGTHT510_faultdiagnosis_supply_set_stage_polling();
			break;
		}
		
		case 0x0404://压气机补气段故检
		{
			TGTHT510_faultdiagnosis_push_set_stage_gas();
			TGTHT510_faultdiagnosis_supply_set_stage_gas();
			break;
		}
		
		case 0x0505://补加抽气段故检
		{
			TGTHT510_faultdiagnosis_push_set_stage_comp();
			TGTHT510_faultdiagnosis_supply_set_stage_comp();
			break;
		}
		
		case 0x0606://补加流动段故检
		{
			TGTHT510_faultdiagnosis_push_set_stage_flow();
			TGTHT510_faultdiagnosis_supply_set_stage_flow();
			break;
		}
		
		case 0x0707://补加复压段故检
		{
			TGTHT510_faultdiagnosis_push_set_stage_repre();
			TGTHT510_faultdiagnosis_supply_set_stage_repre();
			break;
		}
		
		case 0x0808://补加其他段故检
		{
			TGTHT510_faultdiagnosis_push_set_stage_other();
			TGTHT510_faultdiagnosis_supply_set_stage_other();
			break;
		}
		
		case 0x0909://运行段故检
		{
			TGTHT510_faultdiagnosis_push_set_stage_run();
			TGTHT510_faultdiagnosis_supply_set_stage_run();
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}


/******************************************************************************************
**名称：注入指令处理函数：注入状态设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_1553b_inputcommand_dealing_compressor_flag_set(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0x0a0a)//设置当前使用的压气机为A机
	{
		compressor_state.compressor_A_state=COMPRESSOR_RUN;
		compressor_state.compressor_B_state=COMPRESSOR_STOP;
		compressor_state.compressor_C_state=COMPRESSOR_STOP;
	
		TGTHT510_supply_decode_par.compressor_F=DECODE_NONE;
		TGTHT510_supply_decode_par.compressor_O=DECODE_NONE;
		
		
	}
	
	else if(temp==0x0b0b)//设置当前使用的压气机为B机
	{
		compressor_state.compressor_A_state=COMPRESSOR_STOP;
		compressor_state.compressor_B_state=COMPRESSOR_RUN;
		compressor_state.compressor_C_state=COMPRESSOR_STOP;
	
		TGTHT510_supply_decode_par.compressor_F=DECODE_NONE;
		TGTHT510_supply_decode_par.compressor_O=DECODE_NONE;
		
	}
	
	else if(temp==0x0c01)//设置当前使用的压气机为C机，且为氧路
	{
		compressor_state.compressor_A_state=COMPRESSOR_STOP;
		compressor_state.compressor_B_state=COMPRESSOR_STOP;
		compressor_state.compressor_C_state=COMPRESSOR_RUN;
	
		TGTHT510_supply_decode_par.compressor_F=DECODE_NONE;
		TGTHT510_supply_decode_par.compressor_O=DECODE_COMPRESSOR_C;
		
	}
	
	else if(temp==0x0c02)//设置当前使用的压气机为C机，且为燃路
	{
		compressor_state.compressor_A_state=COMPRESSOR_STOP;
		compressor_state.compressor_B_state=COMPRESSOR_STOP;
		compressor_state.compressor_C_state=COMPRESSOR_RUN;
	
		TGTHT510_supply_decode_par.compressor_F=DECODE_COMPRESSOR_C;
		TGTHT510_supply_decode_par.compressor_O=DECODE_NONE;
		
	}
	
	else if(temp==0x0202)//当前使用的氧路补加接口为O1
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O1;
		
	}
	
	else if(temp==0x0303)//当前使用的氧路补加接口为O2
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O2;
		
	}
	
	else if(temp==0x0404)//当前使用的氧路补加接口为O3
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O3;
		
	}
	
	else if(temp==0x0505)//当前使用的氧路补加接口为O4
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O4;
		
	}
	
	else if(temp==0x0606)//当前使用的燃路补加接口为F1
	{
		
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R1;
		
	}
	
	else if(temp==0x0707)//当前使用的燃路补加接口为F2
	{
		
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R2;
		
	}
	
	else if(temp==0x0808)//当前使用的燃路补加接口为F3
	{
		
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R3;
		
	}
	
	else if(temp==0x0909)//当前使用的燃路补加接口为F4
	{
		
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R4;
		
	}
	
	else
	{
		asm("nop;");
	}
	
}












 
