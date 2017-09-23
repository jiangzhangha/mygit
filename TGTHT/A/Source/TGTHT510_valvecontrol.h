/**
  ******************************************************************************
  * @file    TGTHT510_valvecontrol.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器阀门驱动控制模块头文件
  ******************************************************************************
  */

#ifndef __TGTHT510_valvecontrol_h
#define __TGTHT510_valvecontrol_h
 
/*声明结构体类型---------------------------------------------------------*/
 
 typedef struct
 {
	uint16 command_from_fault;//故检自锁阀指令
	uint16 command_from_fault_time;//故检自锁阀指令脉宽
	
	uint16 command_from_bus;//总线自锁阀指令
	uint16 command_from_bus_time;//总线自锁阀指令脉宽
	
	uint16 command_from_supply;//补加流程控制自锁阀指令
	uint16 command_from_supply_time;//补加流程控制自锁阀指令脉宽
	
	uint16 command_DVb1;//排放电磁阀指令
 }valvecontrol_TypeDef;

 
 
 /*宏定义----------------------------------------------------------------------*/

 #define LVb1K 0x01//12,0,13,0
 #define LVb1G 0x02//14,0,15,0
 #define LVb2K 0x03//0,0,1,0
 #define LVb2G 0x04//2,0,3,0
 #define LVb3K 0x05//8,7,9,7
 #define LVb3G 0x06//10,7,11,7
 #define LVb4K 0x07//4,7,5,7
 #define LVb4G 0x08//6,7,7,7
 #define LVb5K 0x09//20,7,21,7
 #define LVb5G 0x0A//22,7,23,7
 #define LVb6K 0x0B//16,0,17,0
 #define LVb6G 0x0C//18,0,19,0
 #define LVb7K 0x0D//12,1,13,1
 #define LVb7G 0x0E//14,1,15,1
 #define LVb8K 0x0F//0,1,1,1
 #define LVb8G 0x10//2,1,3,1
 #define LVb9K 0x11//8,8,9,8
 #define LVb9G 0x12//10,8,11,8
 #define LVb10K 0x13//4,8,5,8
 #define LVb10G 0x14//6,8,7,8
 #define LVb11K 0x15//20,8,21,8
 #define LVb11G 0x16//22,8,23,8
 #define LVb12K 0x17//16,1,17,1
 #define LVb12G 0x18//18,1,19,1
 #define LVb13K 0x19//12,2,13,2
 #define LVb13G 0x1A//14,2,15,2
 #define LVb14K 0x1B//0,2,1,2
 #define LVb14G 0x1C//2,2,3,2
 #define LVb15K 0x1D//12,3,13,3
 #define LVb15G 0x1E//14,3,15,3
 #define LVb16K 0x1F//0,3,1,3
 #define LVb16G 0x20//2,3,3,3
 #define LVb17K 0x21//12,4,13,4
 #define LVb17G 0x22//14,4,15,4
 #define LVb18K 0x23//0,4,1,4
 #define LVb18G 0x24//2,4,3,4
 #define LVb19K 0x25//12,5,13,5
 #define LVb19G 0x26//14,5,15,5
 #define LVb20K 0x27//0,5,1,5
 #define LVb20G 0x28//2,5,3,5
 #define LVb21K 0x29//12,6,13,6
 #define LVb21G 0x2A//14,6,15,6
 #define LVb22K 0x2B//0,6,1,6
 #define LVb22G 0x2C//2,6,3,6
 #define LVb23K 0x2D//0,13,1,13
 #define LVb23G 0x2E//2,13,3,13
 #define LVb24K 0x2F//0,14,1,14
 #define LVb24G 0x30//2,14,3,14
 #define LVb25K 0x31//12,8,13,8
 #define LVb25G 0x32//14,8,15,8
 #define LVb26K 0x33//12,9,13,9
 #define LVb26G 0x34//14,9,15,9
 #define LVb27K 0x35//12,10,13,10
 #define LVb27G 0x36//14,10,15,10
 #define LVb28K 0x37//0,7,1,7
 #define LVb28G 0x38//2,7,3,7
 #define LVb29K 0x39//12,11,13,11
 #define LVb29G 0x3A//14,11,15,11
 #define LVb30K 0x3B//0,8,1,8
 #define LVb30G 0x3C//2,8,3,8
 #define LVb31K 0x3D//12,12,13,12
 #define LVb31G 0x3E//14,12,15,12
 #define LVb32K 0x3F//0,9,1,9
 #define LVb32G 0x40//2,9,3,9
 #define LVb33K 0x41//12,13,13,13
 #define LVb33G 0x42//14,13,15,13
 #define LVb34K 0x43//0,10,1,10
 #define LVb34G 0x44//2,10,3,10
 #define LVb35K 0x45//12,14,13,14
 #define LVb35G 0x46//14,14,15,14
 #define LVb36K 0x47//0,11,1,11
 #define LVb36G 0x48//2,11,3,11
 #define LVb37K 0x49//12,15,13,15
 #define LVb37G 0x4A//14,15,15,15
 #define LVb38K 0x4B//0,12,1,12
 #define LVb38G 0x4C//2,12,3,12
 #define LVb39K 0x4D//4,0,5,0
 #define LVb39G 0x4E//6,0,7,0
 #define LVb40K 0x4F//8,0,9,0
 #define LVb40G 0x50//10,0,11,0
 #define LVb41K 0x51//4,1,5,1
 #define LVb41G 0x52//6,1,7,1
 #define LVb42K 0x53//8,1,9,1
 #define LVb42G 0x54//10,1,11,1
 #define LVb43K 0x55//4,2,5,2
 #define LVb43G 0x56//6,2,7,2
 #define LVb44K 0x57//8,2,9,2
 #define LVb44G 0x58//10,2,11,2
 #define LVb45K 0x59//4,3,5,3
 #define LVb45G 0x5A//6,3,7,3
 #define LVb46K 0x5B//8,3,9,3
 #define LVb46G 0x5C//10,3,11,3
 #define LVb47K 0x5D//4,4,5,4
 #define LVb47G 0x5E//6,4,7,4
 #define LVb48K 0x5F//8,4,9,4
 #define LVb48G 0x60//10,4,11,4
 #define LVb49K 0x61//16,7,17,7
 #define LVb49G 0x62//18,7,19,7
 #define LVb50K 0x63//20,0,21,0
 #define LVb50G 0x64//22,0,23,0
 #define LVb51K 0x65//16,8,17,8
 #define LVb51G 0x66//18,8,19,8
 #define LVb52K 0x67//20,1,21,1
 #define LVb52G 0x68//22,1,23,1
 #define LVb53K 0x69//16,9,17,9
 #define LVb53G 0x6A//18,9,19,9
 #define LVb54K 0x6B//20,2,21,2
 #define LVb54G 0x6C//22,2,23,2
 #define LVb55K 0x6D//16,10,17,10
 #define LVb55G 0x6E//18,10,19,10
 #define LVb56K 0x6F//20,3,21,3
 #define LVb56G 0x70//22,3,23,3
 #define LVb57K 0x71//16,11,17,11
 #define LVb57G 0x72//18,11,19,11
 #define LVb58K 0x73//20,4,21,4
 #define LVb58G 0x74//22,4,23,4
 #define LVb59K 0x75//16,13,17,13
 #define LVb59G 0x76//18,13,19,13
 #define LVb60K 0x77//20,5,21,5
 #define LVb60G 0x78//22,5,23,5
 #define LVb61K 0x79//16,14,17,14
 #define LVb61G 0x7A//18,14,19,14
 #define LVb62K 0x7B//20,6,21,6
 #define LVb62G 0x7C//22,6,23,6
 #define LVb63K 0x7D//4,5,5,5
 #define LVb63G 0x7E//6,5,7,5
 #define LVb64K 0x7F//8,5,9,5
 #define LVb64G 0x80//10,5,11,5
 #define LVb65K 0x81//4,6,5,6
 #define LVb65G 0x82//6,6,7,6
 #define LVb66K 0x83//8,6,9,6
 #define LVb66G 0x84//10,6,11,6
 #define LVb67K 0x85//4,9,5,9
 #define LVb67G 0x86//6,9,7,9
 #define LVb68K 0x87//8,9,9,9
 #define LVb68G 0x88//10,9,11,9
 #define LVb69K 0x89//4,10,5,10
 #define LVb69G 0x8A//6,10,7,10
 #define LVb70K 0x8B//8,10,9,10
 #define LVb70G 0x8C//10,10,11,10
 #define LVb71K 0x8D//16,2,17,2
 #define LVb71G 0x8E//18,2,19,2
 #define LVb72K 0x8F//20,9,21,9
 #define LVb72G 0x90//22,9,23,9
 #define LVb73K 0x91//16,3,17,3
 #define LVb73G 0x92//18,3,19,3
 #define LVb74K 0x93//20,10,21,10
 #define LVb74G 0x94//22,10,23,10
 #define LVb75K 0x95//4,11,5,11
 #define LVb75G 0x96//6,11,7,11
 #define LVb76K 0x97//8,11,9,11
 #define LVb76G 0x98//10,11,11,11
 #define LVb77K 0x99//16,4,17,4
 #define LVb77G 0x9A//18,4,19,4
 #define LVb78K 0x9B//20,11,21,11
 #define LVb78G 0x9C//22,11,23,11
 #define LVb79K 0x9D//4,13,5,13
 #define LVb79G 0x9E//6,13,7,13
 #define LVb80K 0x9F//8,13,9,13
 #define LVb80G 0xA0//10,13,11,13
 #define LVb81K 0xA1//16,5,17,5
 #define LVb81G 0xA2//18,5,19,5
 #define LVb82K 0xA3//20,13,21,13
 #define LVb82G 0xA4//22,13,23,13
 #define LVb83K 0xA5//4,14,5,14
 #define LVb83G 0xA6//6,14,7,14
 #define LVb84K 0xA7//8,14,9,14
 #define LVb84G 0xA8//10,14,11,14
 #define LVb85K 0xA9//16,6,17,6
 #define LVb85G 0xAA//18,6,19,6
 #define LVb86K 0xAB//20,14,21,14
 #define LVb86G 0xAC//22,14,23,14
 #define LVb87K 0xAD//12,7,13,7
 #define LVb87G 0xAE//14,7,15,7
 #define DVb1K 0xAF//0,15,1,15
 #define DVb1G 0xB0//
 #define PACKCODE 0xFF//
 
 
 
 #define VALVE_CONTROL_ADDRESS_BASE 0x23800000	//阀门驱动控制基地址
 
 //1-24,25
 
 #define BIT00_BIT08	0x0008					//阀门驱动控制字位00与位08
 #define BIT01_BIT09	0x0109					//阀门驱动控制字位01与位09
 #define BIT02_BIT10	0x0210					//阀门驱动控制字位02与位10
 #define BIT03_BIT11	0x0311					//阀门驱动控制字位03与位11
 #define BIT04_BIT12	0x0412					//阀门驱动控制字位04与位12
 #define BIT05_BIT13	0x0513					//阀门驱动控制字位05与位13
 #define BIT06_BIT14	0x0614					//阀门驱动控制字位06与位14
 #define BIT07_BIT15	0x0715					//阀门驱动控制字位07与位15
 #define BIT_ILLEGAL	0x55aa					//阀门驱动控制字位非法
 
 #define BIT00_BIT08_SET	0x0001
 #define BIT00_BIT08_CLR	0xfeff
 #define BIT01_BIT09_SET	0x0002
 #define BIT01_BIT09_CLR	0xfdff
 #define BIT02_BIT10_SET	0x0004
 #define BIT02_BIT10_CLR	0xfbff
 #define BIT03_BIT11_SET	0x0008
 #define BIT03_BIT11_CLR	0xf7ff
 #define BIT04_BIT12_SET	0x0010
 #define BIT04_BIT12_CLR	0xefff
 #define BIT05_BIT13_SET	0x0020
 #define BIT05_BIT13_CLR	0xdfff
 #define BIT06_BIT14_SET	0x0040
 #define BIT06_BIT14_CLR	0xbfff
 #define BIT07_BIT15_SET	0x0080
 #define BIT07_BIT15_CLR	0x7fff

 


 
 
/*阀门驱动控制模块函数声明---------------------------------------------------*/
void TGTHT510_valvecontrol_initial(void);
void TGTHT510_valvecontrol_main(void);
void TGTHT510_valvecontrol_setbit(uint16 *p,uint16 code); 
void TGTHT510_valvecontrol_output(uint16 *p);
void TGTHT510_valvecontrol_command_clear(void);
void TGTHT510_valvecontrol_wait(void);



 
#endif 



