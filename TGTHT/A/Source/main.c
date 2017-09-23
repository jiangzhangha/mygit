/**
  ******************************************************************************
  * @file    main.c
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器主程序
			该版本使用了Git版本控制工具进行版本管理。
  ******************************************************************************
  */

#include "TGTHT510.h"
#include "BM3803MG.h"

/*函数声明----------------------------------------------------------------------*/
void Initial_time1(unsigned int ms);                                  //定时器0初始化函数
uint16 get_CPU(void);
void set_CPU_initial_state(void);

void CPUDispatchIRQ(unsigned int InterruptNumber);                    //通用中断处理程序
void INT_time1(void);                                                 //定时器0中断处理函数
void TGTHT510_time_initial(void);
void TGTHT510_CPU_B_receive_data_initial(void);

void TGTHT510_time(void);
uint32 Write_16_to_32(uint16 num);
uint16 Read_32_to_16(uint32 num);
void Initial_uart3(int baut_rate);
void TGTHT510_uart3_set_data(uint8 c);
uint8 TGTHT510_uart3_get_data(void);
void INT_uart3(void);
void TGTHT510_CPU_A_send_data(void);
void TGTHT510_CPU_A_send_data_generate(uint8 *data);



/*全局变量---------------------------------------------------------------*/	

extern uint16 is_wait_overtime;//标识等待FPGA时间是否超时。	
extern fault_deal_TypeDef fault_deal;	//故障处理-全局控制参数
extern fault_deal_is_CPU_A_done_TypeDef fault_deal_is_CPU_A_done;	//A机发送的故检执行状况

unsigned int INT_time1_flag = FALSE;
unsigned int Task_count = 0x00;
uint8 frame_number_A_send=0x00;

CPU_B_receive_data_TypeDef CPU_B_receive_data;
Time_flag_TypeDef Time_flag;//定时计数结构体
struct lregs * regs = (struct lregs *)0x80000000;
typedef void (* PFUNC) (void);


PFUNC IRQVector[] =
{
					/*handler: tt   */
	0,				/* 0x10 */
	0,				/* 0x11 */
	0,				/* 0x12 */
	0,				/* 0x13 */
	0,				/* 0x14 */
	0,				/* 0x15 */
	0,				/* 0x16 */
	0,				/* 0x17 */
	INT_time1,  	/* 0x18 timer1_irq */
	0,  			/* 0x19 timer2_irq */
	0,  			/* 0x1A */
	0,				/* 0x1B */
	INT_uart3,		/* 0x1C */
	0,				/* 0x1D */
	0,				/* 0x1E PCI*/
	0,				/* 0x1F */
};


/******************************************************************************************
**名称：主程序
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

int main()
{
    uint16 m,n;
	
	uint8 t=0;
	
	TGTHT510_initial_main();
	regs->piodir=0x1038;
	Initial_time1(100);					//初始化定时器1，设置定时时间为100ms
	regs->timerctrl1 = 0x07;			//定时器0使能
	regs->irqmask |= 0x0FFFE;			//中断屏蔽寄存器打开
	regs->irqclear  =0x1000;
	LED_OFF();
	set_CPU_initial_state();
	Initial_uart3(115200);
	
	
	while(1)
	{
		while(INT_time1_flag == FALSE)
		{
			asm("nop;");					//定时器0的100ms定时未到
		}
		
		INT_time1_flag = FALSE;				// 100ms定时到，置标志无效
		
		TGTHT510_time();
		TGTHT510_1553b_main();
		TGTHT510_collectANDgroup_valve_state_collect_save();
		TGTHT510_valvecontrol_main();
		
		TGTHT510_CPU_A_send_data();//A机发送互传数据
		
		switch(Task_count)
		{
			case 1:							//任务时间片1
			{
				LED_ON();
				TGTHT510_tempercontrol_main();
				break;
			}
			
			case 2:							//任务时间片2
			{
				LED_OFF();
				TGTHT510_supply_main();
				break;
			}
			
			case 3:							//任务时间片3
			{
				LED_ON();
				TGTHT510_faultdiagnosis_push_main();
				break;
			}
			
			case 4:							//任务时间片4
			{
				LED_OFF();
				TGTHT510_faultdiagnosis_supply_main();
				
				TGTHT510_1553b_message_state_dealing();
				TGTHT510_1553b_message_count_update();
				break;
			}
			
			case 5:							//任务时间片5
			{
				LED_ON();
				TGTHT510_faultdeal_main();
				
				TGTHT510_collectANDgroup_main();
				Task_count=0x00;
				break;
			}
			
			default:
			{
				
                Task_count=0x00;
				break;	
			}
				
		}
	}

    return 0;
}

/******************************************************************************************
**名称：获取当前CPU为A机或者B机
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 get_CPU(void)
{
	//通过IO口判断当前为A机或者B机
	
	//实验件的状态：
	//IO6为低，且IO7为低，则为A机
	//IO6为高，且IO7为高，则为B机
	
	//电性件、鉴定件的状态：
	//IO6为低，且IO7为低，则为B机
	//IO6为高，且IO7为高，则为A机
	
	#ifdef TEST_VERSION
	
	if((regs->piodata&0x00c0)==0x00c0)//B机
	{
		return CPU_B;
	}
	
	else if((regs->piodata&0x00c0)==0x0000)//A机
	{
		return CPU_A;
	}
	
	else
	{
		while(1)
		{
			asm("nop;");
		}
	}
	
	#else
		
	if((regs->piodata&0x00c0)==0x00c0)//A机
	{
		return CPU_A;
	}
	
	else if((regs->piodata&0x00c0)==0x0000)//B机
	{
		return CPU_B;
	}
	
	else
	{
		while(1)
		{
			asm("nop;");
		}
	}
		
	#endif
	
	
	
}

/******************************************************************************************
**名称：设置初始CPU状态
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void set_CPU_initial_state(void)
{
	if(get_CPU()==CPU_B)//B机
	{
		
		#ifdef TEST_VERSION
		
		CPU_OFF();
		
		#else
			
		CPU_OFF();
		
		#endif
	}
	
	else//A机
	{
		CPU_ON();
	}
}

/******************************************************************************************
**名称：定时器0中断处理程序
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void INT_time1(void)
{
	INT_time1_flag=TRUE;				//定时100ms时间到，置标志有效
	is_wait_overtime=TRUE;
	Task_count++;						//任务时间片计数累加
	return;	
}



/******************************************************************************************
**名称：中断跳转程序
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void CPUDispatchIRQ( unsigned int InterruptNumber)
{

#if 0
	if (InterruptNumber == 15)						//发生了一次不可屏蔽中断
	{
		
    }
#endif
	
    if( IRQVector[InterruptNumber] )				/* call registered interrupt handler */
    {       	
	    IRQVector[InterruptNumber]();			//	(*(IRQVector[InterruptNumber]))();
	}
}

/******************************************************************************************
**名称：定时器0初始化函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void Initial_time1(unsigned int ms)
{
	regs->scalerload = CPU_FREQ/1000000 -1;
	regs->scalercnt  = CPU_FREQ/1000000 -1;
	
	regs->timercnt1  = 1000 * ms - 1;
	regs->timerload1 = 1000 * ms - 1;
	regs->timerctrl1 = 0;                                               //不使能定时器1
}

/******************************************************************************************
**名称：时间处理初始化函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_time_initial(void)
{
	Time_flag.time_9s_count=TIME_9S_COUNT_NUMBER;
	
	Time_flag.time_9s_flag=FALSE;
	
}

/******************************************************************************************
**名称：时间处理初始化函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_CPU_B_receive_data_initial(void)
{
	CPU_B_receive_data.frame_number=0x01;
	CPU_B_receive_data.last_frame_number=0x00;
	CPU_B_receive_data.fault_mode=FAULT_MODE_NONE;
	
	CPU_B_receive_data.count=0x000f;
	CPU_B_receive_data.is_B_get_power=FALSE;
	CPU_B_receive_data.error_number=0x0000;
	
}




/******************************************************************************************
**名称：时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_time(void)
{
	Time_flag.time_9s_count--;
	if(Time_flag.time_9s_count==0x0000)
	{
		Time_flag.time_9s_flag=TRUE;
		Time_flag.time_9s_count=TIME_9S_COUNT_NUMBER;
	}
	
	if(get_CPU()==CPU_B)//B机
	{
		CPU_B_receive_data.count--;
		
		if(CPU_B_receive_data.count==0x0000)//B机夺权
		{
			CPU_B_receive_data.count=0x000f;
			CPU_ON();//B机夺权
			CPU_B_receive_data.is_B_get_power=TRUE;
		}
		
	}
	
}

/******************************************************************************************
**名称：写分函数，16位转换为32位，有效数据为高16位
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint32 Write_16_to_32(uint16 num)
{
	return ((uint32)num<<16);	
}


/******************************************************************************************
**名称：读分函数，32位转换为16位，取32位的高16位为有效数据
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 Read_32_to_16(uint32 num)
{
	return ((uint16)(num>>16));
}


/******************************************************************************************
**名称：UART初始化函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void Initial_uart3(int baut_rate)
{
	regs->uartscaler3 = ((((CPU_FREQ*10) / (8 * baut_rate))-5)/10);
    regs->uartstatus3 = 0;
	
	if(get_CPU()==CPU_B)//B机
	{
		regs->uartctrl3   = (REV_EN | REV_INT_EN | PAR_SEL | PAR_EN);
	}
	
	else//A机
	{
		regs->uartctrl3   = (TRANS_EN | PAR_SEL | PAR_EN);
	}

}


/******************************************************************************************
**名称：UART发送函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_uart3_set_data(uint8 c)
{
	uint16 i=0x00ff;
	
	while(!(regs->uartstatus3 & TH_EMPTY))
	{
		i--;
		if(i==0x0000)
		{
			return;
		}
	}
   
    regs->uartdata3 = c; /* write char to Transmit Buffer Register */
	
}



/******************************************************************************************
**名称：UART接收函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint8 TGTHT510_uart3_get_data(void)
{
	uint16 i=0x00ff;
	
	while (!(regs->uartstatus3 & DATA_RD))
	{
		i--;
		if(i==0x0000)
		{
			return 0;
		}
	}
    
    return (uint8)(regs->uartdata3);
}

/******************************************************************************************
**名称：UART中断处理程序
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：12
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void INT_uart3(void)
{
	/*
		A机发送给B机的互传数据格式为：
		同步头，2字节，固定为EBH、90H
		故障处理信息，2字节
		帧计数，1字节，00H~FFH循环；
		累加和，1字节
	*/
	uint8 receive_data[4];
	uint8 sum=0x00;
	uint16 i;
	
	if((get_CPU()==CPU_B)&&(CPU_B_receive_data.is_B_get_power!=TRUE))//B机接收中断数据
	{
		if(TGTHT510_uart3_get_data()==0xeb)//数据头0xeb
		{
			if(TGTHT510_uart3_get_data()==0x90)//数据头0x90
			{
				for(i=0;i<=3;i++)
				{
					receive_data[i]=TGTHT510_uart3_get_data();
				}
				
				sum=(uint8)(0xeb+0x90+receive_data[0]+receive_data[1]+receive_data[2]);
				
				if(sum==receive_data[3])
				{
					CPU_B_receive_data.last_frame_number=CPU_B_receive_data.frame_number;
					CPU_B_receive_data.frame_number=receive_data[2];
					
					if((CPU_B_receive_data.last_frame_number+1)==CPU_B_receive_data.frame_number)
					{
						CPU_B_receive_data.fault_mode=((((uint16)receive_data[0])<<8)|((uint16)receive_data[1]));
						fault_deal_is_CPU_A_done.fault_mode_last=fault_deal_is_CPU_A_done.fault_mode_moment;
						fault_deal_is_CPU_A_done.fault_mode_moment=CPU_B_receive_data.fault_mode;
						TGTHT510_faultdiagnosis_is_CPU_A_done_set();
						
						CPU_B_receive_data.error_number=0;
					}
					
					else
					{
						CPU_B_receive_data.error_number++;
					}
					
				}
				
				else
				{
					CPU_B_receive_data.error_number++;
				}
			}
			
			else
			{
				CPU_B_receive_data.error_number++;
			}
			
		}
		
		else
		{
			CPU_B_receive_data.error_number++;
		}
		
		if(CPU_B_receive_data.error_number>=30)//连续错误次数大于30个，B机夺权
		{
			CPU_ON();//B机夺权
			CPU_B_receive_data.is_B_get_power=TRUE;
		}
		
		CPU_B_receive_data.count=0x000f;
		regs->irqclear=0x1000;
		
	}
	
}

/******************************************************************************************
**名称：A机发送互传数据
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：12
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_CPU_A_send_data(void)
{
	/*
		A机发送给B机的互传数据格式为：
		同步头，2字节，固定为EBH、90H
		故障处理信息，2字节
		帧计数，1字节，00H~FFH循环；
		累加和，1字节
	*/
	
	uint8 send_data[6];
	uint16 i;
	
	if(get_CPU()==CPU_A)//A机发送数据
	{
		TGTHT510_CPU_A_send_data_generate(send_data);
		
		for(i=0;i<=5;i++)
		{
			TGTHT510_uart3_set_data(send_data[i]);
			asm("nop;");
			asm("nop;");
			asm("nop;");
			asm("nop;");
			asm("nop;");
			asm("nop;");
			asm("nop;");
			asm("nop;");
			asm("nop;");
			asm("nop;");
		}
		
	}
	
}

/******************************************************************************************
**名称：A机发送互传数据
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：12
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_CPU_A_send_data_generate(uint8 *data)
{
	frame_number_A_send++;
	data[0]=0xeb;
	data[1]=0x90;
	data[2]=(uint8)(fault_deal.fault_mode>>8);
	data[3]=(uint8)(fault_deal.fault_mode);
	data[4]=frame_number_A_send;
	data[5]=(uint8)(data[0]+data[1]+data[2]+data[3]+data[4]);
}




