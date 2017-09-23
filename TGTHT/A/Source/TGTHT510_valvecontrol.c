/**
  ******************************************************************************
  * @file    TGTHT510_valvecontrol.c
  * @author  蒋章
  * @version V1.00
  * @date    20150626
  * @brief   空间站核心舱推进管理器阀门驱动控制模块C文件
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"

/*全局变量---------------------------------------------------------------*/		

 valvecontrol_TypeDef TGTHT510_valvecontrol_struct;//阀门控制数据结构体
 
 extern CPU_B_receive_data_TypeDef CPU_B_receive_data;
 
 uint16 test_val;//测试 
 
//上桥臂阀门控制字查询表
 uint16 valve_control_word_high[256]={
	
//	--00-----01-----02-----03----04------05----06------07----08-----09------0a-----0b----0c-----0d-----0e-----0f----	
	WORD88,WORD12,WORD14,WORD00,WORD02,WORD08,WORD10,WORD04,WORD06,WORD20,WORD22,WORD16,WORD18,WORD12,WORD14,WORD00,//00
	WORD02,WORD08,WORD10,WORD04,WORD06,WORD20,WORD22,WORD16,WORD18,WORD12,WORD14,WORD00,WORD02,WORD12,WORD14,WORD00,//01
	WORD02,WORD12,WORD14,WORD00,WORD02,WORD12,WORD14,WORD00,WORD02,WORD12,WORD14,WORD00,WORD02,WORD00,WORD02,WORD00,//02
	WORD02,WORD12,WORD14,WORD12,WORD14,WORD12,WORD14,WORD00,WORD02,WORD12,WORD14,WORD00,WORD02,WORD12,WORD14,WORD00,//03
	WORD02,WORD12,WORD14,WORD00,WORD02,WORD12,WORD14,WORD00,WORD02,WORD12,WORD14,WORD00,WORD02,WORD04,WORD06,WORD08,//04
	WORD10,WORD04,WORD06,WORD08,WORD10,WORD04,WORD06,WORD08,WORD10,WORD04,WORD06,WORD08,WORD10,WORD04,WORD06,WORD08,//05
	WORD10,WORD16,WORD18,WORD20,WORD22,WORD16,WORD18,WORD20,WORD22,WORD16,WORD18,WORD20,WORD22,WORD16,WORD18,WORD20,//06
	WORD22,WORD16,WORD18,WORD20,WORD22,WORD16,WORD18,WORD20,WORD22,WORD16,WORD18,WORD20,WORD22,WORD04,WORD06,WORD08,//07
	WORD10,WORD04,WORD06,WORD08,WORD10,WORD04,WORD06,WORD08,WORD10,WORD04,WORD06,WORD08,WORD10,WORD16,WORD18,WORD20,//08
	WORD22,WORD16,WORD18,WORD20,WORD22,WORD04,WORD06,WORD08,WORD10,WORD16,WORD18,WORD20,WORD22,WORD04,WORD06,WORD08,//09
	WORD10,WORD16,WORD18,WORD20,WORD22,WORD04,WORD06,WORD08,WORD10,WORD16,WORD18,WORD20,WORD22,WORD12,WORD14,WORD00,//0a
	WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,//0b
	WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,//0c
	WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,//0d
	WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,//0e
	WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88,WORD88//0f

 };
 
 
//阀门控制位查询表
uint16 valve_control_bit[256]={

//---00----01----02----03----04----05-----06---07-----08---09----0a----0b----0c----0d----0e----0f-------	
	BIT88,BIT00,BIT00,BIT00,BIT00,BIT07,BIT07,BIT07,BIT07,BIT07,BIT07,BIT00,BIT00,BIT01,BIT01,BIT01,//00
	BIT01,BIT08,BIT08,BIT08,BIT08,BIT08,BIT08,BIT01,BIT01,BIT02,BIT02,BIT02,BIT02,BIT03,BIT03,BIT03,//01
	BIT03,BIT04,BIT04,BIT04,BIT04,BIT05,BIT05,BIT05,BIT05,BIT06,BIT06,BIT06,BIT06,BIT13,BIT13,BIT14,//02
	BIT14,BIT08,BIT08,BIT09,BIT09,BIT10,BIT10,BIT07,BIT07,BIT11,BIT11,BIT08,BIT08,BIT12,BIT12,BIT09,//03
	BIT09,BIT13,BIT13,BIT10,BIT10,BIT14,BIT14,BIT11,BIT11,BIT15,BIT15,BIT12,BIT12,BIT00,BIT00,BIT00,//04
	BIT00,BIT01,BIT01,BIT01,BIT01,BIT02,BIT02,BIT02,BIT02,BIT03,BIT03,BIT03,BIT03,BIT04,BIT04,BIT04,//05
	BIT04,BIT07,BIT07,BIT00,BIT00,BIT08,BIT08,BIT01,BIT01,BIT09,BIT09,BIT02,BIT02,BIT10,BIT10,BIT03,//06
	BIT03,BIT11,BIT11,BIT04,BIT04,BIT13,BIT13,BIT05,BIT05,BIT14,BIT14,BIT06,BIT06,BIT05,BIT05,BIT05,//07
	BIT05,BIT06,BIT06,BIT06,BIT06,BIT09,BIT09,BIT09,BIT09,BIT10,BIT10,BIT10,BIT10,BIT02,BIT02,BIT09,//08
	BIT09,BIT03,BIT03,BIT10,BIT10,BIT11,BIT11,BIT11,BIT11,BIT04,BIT04,BIT11,BIT11,BIT13,BIT13,BIT13,//09
	BIT13,BIT05,BIT05,BIT13,BIT13,BIT14,BIT14,BIT14,BIT14,BIT06,BIT06,BIT14,BIT14,BIT07,BIT07,BIT15,//0a
	BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,//0b
	BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,//0c
	BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,//0d
	BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,//0e
	BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88,BIT88//0f

};

 							

/******************************************************************************************
**名称：阀门驱动控制函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_valvecontrol_initial(void)
{
	TGTHT510_valvecontrol_struct.command_from_fault=PACKCODE;
	TGTHT510_valvecontrol_struct.command_from_bus=PACKCODE;
	TGTHT510_valvecontrol_struct.command_from_supply=PACKCODE;
	TGTHT510_valvecontrol_struct.command_DVb1=PACKCODE;//阀门控制初始化为填充码
	
	TGTHT510_valvecontrol_struct.command_from_fault_time=0;
	TGTHT510_valvecontrol_struct.command_from_bus_time=0;
	TGTHT510_valvecontrol_struct.command_from_supply_time=0;
	
	test_val=0xffff; 

} 
  
 
/******************************************************************************************
**名称：阀门驱动控制函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_valvecontrol_main(void)
{
	
	uint16 control_word[24];//阀门控制字数组
	uint16 i;
	
	/*
	test_val=~test_val;
	
	for(i=0;i<=23;i++)
	{
        control_word[i]=0x0000;	
	}
	
	
	if(test_val==0xffff)
    {
        control_word[14]=0xffff;
		control_word[15]=0xffff;
    }
        
    else if(test_val==0x0000)
    {
        control_word[14]=0x0000;
		control_word[15]=0x0000;
    } 
        
    else
    {
        ;
    }      
	
	*/
	/*
	
	for(i=0;i<=23;i++)
	{
        if(test_val==0xffff)
        {
            control_word[i]=0xffff;
        }
        
        else if(test_val==0x0000)
        {
            control_word[i]=0x0000;
        } 
        
        else
        {
            ;
        }           
        
        	
	}
	*/
	
    
    
    for(i=0;i<=23;i++)
	{
        control_word[i]=0x0000;	
	}
	
	
	
	//故障检测指令
	if(TGTHT510_valvecontrol_struct.command_from_fault_time==0)
	{
		TGTHT510_valvecontrol_struct.command_from_fault=PACKCODE;
	}
	
	else if(TGTHT510_valvecontrol_struct.command_from_fault_time>=3)
	{
		TGTHT510_valvecontrol_struct.command_from_fault=PACKCODE;
	}
	
	else 
	{
		TGTHT510_valvecontrol_struct.command_from_fault_time--;
		
		TGTHT510_valvecontrol_setbit(control_word,TGTHT510_valvecontrol_struct.command_from_fault);
	}
	
	//总线指令
	if(TGTHT510_valvecontrol_struct.command_from_bus_time==0)
	{
		TGTHT510_valvecontrol_struct.command_from_bus=PACKCODE;
	}
	
	else if(TGTHT510_valvecontrol_struct.command_from_bus_time>=3)
	{
		TGTHT510_valvecontrol_struct.command_from_bus=PACKCODE;
	}
	
	else 
	{
		TGTHT510_valvecontrol_struct.command_from_bus_time--;
		
		TGTHT510_valvecontrol_setbit(control_word,TGTHT510_valvecontrol_struct.command_from_bus);
	}
	
	//补加阀门指令
	if(TGTHT510_valvecontrol_struct.command_from_supply_time==0)
	{
		TGTHT510_valvecontrol_struct.command_from_supply=PACKCODE;
	}
	
	else if(TGTHT510_valvecontrol_struct.command_from_supply_time>=3)
	{
		TGTHT510_valvecontrol_struct.command_from_supply=PACKCODE;
	}
	
	else 
	{
		TGTHT510_valvecontrol_struct.command_from_supply_time--;
		
		TGTHT510_valvecontrol_setbit(control_word,TGTHT510_valvecontrol_struct.command_from_supply);
	}
	
	TGTHT510_valvecontrol_setbit(control_word,TGTHT510_valvecontrol_struct.command_DVb1);
	
	
	
	TGTHT510_valvecontrol_output(control_word);//输出阀门控制信号
	
	//TGTHT510_valvecontrol_command_clear();//除DVb1以外的阀门控制信号初始化为填充码

}
  
  
/******************************************************************************************
**名称：控制指令置位分函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
 
void TGTHT510_valvecontrol_setbit(uint16 *p,uint16 code) 
{
	uint16 word_index_high,word_index_low;
	uint16 bit_index;
	
	if((code>=LVb1K)&&(code<=DVb1K))//输入指令代码为自锁阀开关指令，且合法
	{
		word_index_high=valve_control_word_high[code];//上桥臂控制字
		
		if(word_index_high>22)
		{
			return;
		}
		
		word_index_low=word_index_high+1;//下桥臂控制字
		
		if(valve_control_bit[code]==BIT88)
		{
			return;
		}
		
		p[word_index_high] = p[word_index_high] | valve_control_bit[code];
		p[word_index_low]  = p[word_index_low]  | valve_control_bit[code];
			
	}

	else
	{
		asm("nop;");
	}
	
}
 

 
/******************************************************************************************
**名称：控制指令输出
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_valvecontrol_output(uint16 *p)
{
	uint16 i,j;
	
	if(get_CPU()==CPU_B)//B机
	{
		if(CPU_B_receive_data.is_B_get_power==FALSE)
		{
			return;//B机，且未夺权
		}
		
	}
	
	for(i=0;i<=23;i++)
	{
		//正码
		*(volatile uint32 *)(VALVE_CONTROL_ADDRESS_BASE+(i+1)*4)=Write_16_to_32(p[i]);
		
		TGTHT510_valvecontrol_wait();
		
		//*(volatile uint32 *)(VALVE_CONTROL_ADDRESS_BASE+(i+1)*4)=Write_16_to_32(p[i]);
		
		//TGTHT510_valvecontrol_wait();
		
		//反码校验
		*(volatile uint32 *)(VALVE_CONTROL_ADDRESS_BASE+(24+1)*4)=Write_16_to_32(~p[i]);
		
		TGTHT510_valvecontrol_wait();
		
		//*(volatile uint32 *)(VALVE_CONTROL_ADDRESS_BASE+(24+1)*4)=Write_16_to_32(~p[i]);
		
		//TGTHT510_valvecontrol_wait();

	}
	
	

} 
 
/******************************************************************************************
**名称：控制指令清除
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_valvecontrol_command_clear(void)
{
	TGTHT510_valvecontrol_struct.command_from_fault=PACKCODE;
	TGTHT510_valvecontrol_struct.command_from_bus=PACKCODE;
	TGTHT510_valvecontrol_struct.command_from_supply=PACKCODE;

} 
 
/******************************************************************************************
**名称：等待
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_valvecontrol_wait(void)
{
	uint16 i;
	i=0;
	while(i<=70)
	{
		i++;
	}
}

 
 
 
 
 
  
