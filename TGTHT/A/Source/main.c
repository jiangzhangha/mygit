/**
  ******************************************************************************
  * @file    main.c
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ�������������
  ******************************************************************************
  */

#include "TGTHT510.h"
#include "BM3803MG.h"

/*��������----------------------------------------------------------------------*/
void Initial_time1(unsigned int ms);                                  //��ʱ��0��ʼ������
uint16 get_CPU(void);
void set_CPU_initial_state(void);

void CPUDispatchIRQ(unsigned int InterruptNumber);                    //ͨ���жϴ������
void INT_time1(void);                                                 //��ʱ��0�жϴ�����
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



/*ȫ�ֱ���---------------------------------------------------------------*/	

extern uint16 is_wait_overtime;//��ʶ�ȴ�FPGAʱ���Ƿ�ʱ��	
extern fault_deal_TypeDef fault_deal;	//���ϴ���-ȫ�ֿ��Ʋ���
extern fault_deal_is_CPU_A_done_TypeDef fault_deal_is_CPU_A_done;	//A�����͵Ĺʼ�ִ��״��

unsigned int INT_time1_flag = FALSE;
unsigned int Task_count = 0x00;
uint8 frame_number_A_send=0x00;

CPU_B_receive_data_TypeDef CPU_B_receive_data;
Time_flag_TypeDef Time_flag;//��ʱ�����ṹ��
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
**���ƣ�������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

int main()
{
    uint16 m,n;
	
	uint8 t=0;
	
	TGTHT510_initial_main();
	regs->piodir=0x1038;
	Initial_time1(100);					//��ʼ����ʱ��1�����ö�ʱʱ��Ϊ100ms
	regs->timerctrl1 = 0x07;			//��ʱ��0ʹ��
	regs->irqmask |= 0x0FFFE;			//�ж����μĴ�����
	regs->irqclear  =0x1000;
	LED_OFF();
	set_CPU_initial_state();
	Initial_uart3(115200);
	
	
	while(1)
	{
		while(INT_time1_flag == FALSE)
		{
			asm("nop;");					//��ʱ��0��100ms��ʱδ��
		}
		
		INT_time1_flag = FALSE;				// 100ms��ʱ�����ñ�־��Ч
		
		TGTHT510_time();
		TGTHT510_1553b_main();
		TGTHT510_collectANDgroup_valve_state_collect_save();
		TGTHT510_valvecontrol_main();
		
		TGTHT510_CPU_A_send_data();//A�����ͻ�������
		
		switch(Task_count)
		{
			case 1:							//����ʱ��Ƭ1
			{
				LED_ON();
				TGTHT510_tempercontrol_main();
				break;
			}
			
			case 2:							//����ʱ��Ƭ2
			{
				LED_OFF();
				TGTHT510_supply_main();
				break;
			}
			
			case 3:							//����ʱ��Ƭ3
			{
				LED_ON();
				TGTHT510_faultdiagnosis_push_main();
				break;
			}
			
			case 4:							//����ʱ��Ƭ4
			{
				LED_OFF();
				TGTHT510_faultdiagnosis_supply_main();
				
				TGTHT510_1553b_message_state_dealing();
				TGTHT510_1553b_message_count_update();
				break;
			}
			
			case 5:							//����ʱ��Ƭ5
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
**���ƣ���ȡ��ǰCPUΪA������B��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 get_CPU(void)
{
	//ͨ��IO���жϵ�ǰΪA������B��
	
	//ʵ�����״̬��
	//IO6Ϊ�ͣ���IO7Ϊ�ͣ���ΪA��
	//IO6Ϊ�ߣ���IO7Ϊ�ߣ���ΪB��
	
	//���Լ�����������״̬��
	//IO6Ϊ�ͣ���IO7Ϊ�ͣ���ΪB��
	//IO6Ϊ�ߣ���IO7Ϊ�ߣ���ΪA��
	
	#ifdef TEST_VERSION
	
	if((regs->piodata&0x00c0)==0x00c0)//B��
	{
		return CPU_B;
	}
	
	else if((regs->piodata&0x00c0)==0x0000)//A��
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
		
	if((regs->piodata&0x00c0)==0x00c0)//A��
	{
		return CPU_A;
	}
	
	else if((regs->piodata&0x00c0)==0x0000)//B��
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
**���ƣ����ó�ʼCPU״̬
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void set_CPU_initial_state(void)
{
	if(get_CPU()==CPU_B)//B��
	{
		
		#ifdef TEST_VERSION
		
		CPU_OFF();
		
		#else
			
		CPU_OFF();
		
		#endif
	}
	
	else//A��
	{
		CPU_ON();
	}
}

/******************************************************************************************
**���ƣ���ʱ��0�жϴ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void INT_time1(void)
{
	INT_time1_flag=TRUE;				//��ʱ100msʱ�䵽���ñ�־��Ч
	is_wait_overtime=TRUE;
	Task_count++;						//����ʱ��Ƭ�����ۼ�
	return;	
}



/******************************************************************************************
**���ƣ��ж���ת����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void CPUDispatchIRQ( unsigned int InterruptNumber)
{

#if 0
	if (InterruptNumber == 15)						//������һ�β��������ж�
	{
		
    }
#endif
	
    if( IRQVector[InterruptNumber] )				/* call registered interrupt handler */
    {       	
	    IRQVector[InterruptNumber]();			//	(*(IRQVector[InterruptNumber]))();
	}
}

/******************************************************************************************
**���ƣ���ʱ��0��ʼ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void Initial_time1(unsigned int ms)
{
	regs->scalerload = CPU_FREQ/1000000 -1;
	regs->scalercnt  = CPU_FREQ/1000000 -1;
	
	regs->timercnt1  = 1000 * ms - 1;
	regs->timerload1 = 1000 * ms - 1;
	regs->timerctrl1 = 0;                                               //��ʹ�ܶ�ʱ��1
}

/******************************************************************************************
**���ƣ�ʱ�䴦���ʼ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_time_initial(void)
{
	Time_flag.time_9s_count=TIME_9S_COUNT_NUMBER;
	
	Time_flag.time_9s_flag=FALSE;
	
}

/******************************************************************************************
**���ƣ�ʱ�䴦���ʼ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�ʱ�䴦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_time(void)
{
	Time_flag.time_9s_count--;
	if(Time_flag.time_9s_count==0x0000)
	{
		Time_flag.time_9s_flag=TRUE;
		Time_flag.time_9s_count=TIME_9S_COUNT_NUMBER;
	}
	
	if(get_CPU()==CPU_B)//B��
	{
		CPU_B_receive_data.count--;
		
		if(CPU_B_receive_data.count==0x0000)//B����Ȩ
		{
			CPU_B_receive_data.count=0x000f;
			CPU_ON();//B����Ȩ
			CPU_B_receive_data.is_B_get_power=TRUE;
		}
		
	}
	
}

/******************************************************************************************
**���ƣ�д�ֺ�����16λת��Ϊ32λ����Ч����Ϊ��16λ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint32 Write_16_to_32(uint16 num)
{
	return ((uint32)num<<16);	
}


/******************************************************************************************
**���ƣ����ֺ�����32λת��Ϊ16λ��ȡ32λ�ĸ�16λΪ��Ч����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 Read_32_to_16(uint32 num)
{
	return ((uint16)(num>>16));
}


/******************************************************************************************
**���ƣ�UART��ʼ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void Initial_uart3(int baut_rate)
{
	regs->uartscaler3 = ((((CPU_FREQ*10) / (8 * baut_rate))-5)/10);
    regs->uartstatus3 = 0;
	
	if(get_CPU()==CPU_B)//B��
	{
		regs->uartctrl3   = (REV_EN | REV_INT_EN | PAR_SEL | PAR_EN);
	}
	
	else//A��
	{
		regs->uartctrl3   = (TRANS_EN | PAR_SEL | PAR_EN);
	}

}


/******************************************************************************************
**���ƣ�UART���ͺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�UART���պ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�UART�жϴ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������12
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void INT_uart3(void)
{
	/*
		A�����͸�B���Ļ������ݸ�ʽΪ��
		ͬ��ͷ��2�ֽڣ��̶�ΪEBH��90H
		���ϴ�����Ϣ��2�ֽ�
		֡������1�ֽڣ�00H~FFHѭ����
		�ۼӺͣ�1�ֽ�
	*/
	uint8 receive_data[4];
	uint8 sum=0x00;
	uint16 i;
	
	if((get_CPU()==CPU_B)&&(CPU_B_receive_data.is_B_get_power!=TRUE))//B�������ж�����
	{
		if(TGTHT510_uart3_get_data()==0xeb)//����ͷ0xeb
		{
			if(TGTHT510_uart3_get_data()==0x90)//����ͷ0x90
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
		
		if(CPU_B_receive_data.error_number>=30)//���������������30����B����Ȩ
		{
			CPU_ON();//B����Ȩ
			CPU_B_receive_data.is_B_get_power=TRUE;
		}
		
		CPU_B_receive_data.count=0x000f;
		regs->irqclear=0x1000;
		
	}
	
}

/******************************************************************************************
**���ƣ�A�����ͻ�������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������12
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_CPU_A_send_data(void)
{
	/*
		A�����͸�B���Ļ������ݸ�ʽΪ��
		ͬ��ͷ��2�ֽڣ��̶�ΪEBH��90H
		���ϴ�����Ϣ��2�ֽ�
		֡������1�ֽڣ�00H~FFHѭ����
		�ۼӺͣ�1�ֽ�
	*/
	
	uint8 send_data[6];
	uint16 i;
	
	if(get_CPU()==CPU_A)//A����������
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
**���ƣ�A�����ͻ�������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������12
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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




