/**
  ******************************************************************************
  * @file    TGTHT510_1553b.c
  * @author  ����
  * @version V1.00
  * @date    20150626
  * @brief   �ռ�վ���Ĳ��ƽ�������1553B���ߴ���ģ��C�ļ�
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"
#include "BM3803MG.h"

/*ȫ�ֱ���---------------------------------------------------------------*/		

extern struct lregs * regs;

uint16 is_wait_overtime;//��ʶ�ȴ�FPGAʱ���Ƿ�ʱ��

TGTHT510_1553B_Subaddress_flag_TypeDef TGTHT510_1553B_Subaddress_flag;	//1553B�ӵ�ַ��ջ��ѯ��־�ṹ��			

TGTHT510_1553B_message_state_TypeDef TGTHT510_1553B_message_state;		//����ͨѶ״̬���ݸ�ʽ

TGTHT510_which_bus_TypeDef TGTHT510_which_bus;//�����л�ȫ�ֱ���

TGTHT510_1553B_service_flag_TypeDef TGTHT510_1553B_service_flag;

//------------------------------------����-------------------------------------
extern uint16 CG_supply_information_realtime_state_data[]; //ʵʱ������Ϣ

//------------------------------------����-------------------------------------

extern compressor_state_TypeDef compressor_state;
extern TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;

extern valvecontrol_TypeDef TGTHT510_valvecontrol_struct;				//���ſ��ƽṹ��
extern Temperature_control_block_TypeDef Temperature_control_block[];	//��50·���»�·
extern Temperature_control_global_TypeDef Temperature_control_global;	//�¶ȿ���ȫ�ֱ���

extern uint16 TGTHT510_1553B_data_MEMORY[];								//�ڴ��´�����
extern uint16 TGTHT510_1553B_data_GNC[];								//��GNC�ʼ��������7����
extern uint16 TGTHT510_1553B_data_HYCT[];
extern uint16 TGTHT510_1553B_data_CG[];									//����ң�����飬��135����
extern uint16 TGTHT510_1553B_data_GC[];									//����ң�����飬��32����
extern uint16 TGTHT510_1553B_data_YB[];									//�Ǳ�ң�����飬��21����
extern uint16 TGTHT510_1553B_data_equiment_command[];					//�豸����ָ���11����
extern uint16 TGTHT510_1553B_data_ask_for_service;						//��������ָ���1����

extern uint16 CG_inputcommand_receive_state_data[];						//ע��ָ�����״̬,2����
extern uint16 CG_equiment_receive_state_data[];							//�豸�����ݽ���״̬,6����
extern TGTHT510_supply_input_par_TypeDef TGTHT510_supply_input_par;     //����ע�����
extern TGTHT510_supply_ctrl_TypeDef TGTHT510_supply_ctrl;				//���ӿ��Ʋ���
extern uint16 tt[];
extern uint16 CG_valve_state_data[];    //���淧�ſ���״̬
extern uint16 CG_bus_command[2];//��������ָ��´�ָ��������У���

uint16 TGTHT510_1553B_data_TGTHT100[89]={0x0000};					//ȫ�����飬�����ƽ�ң����·�г��¶Ȳ����������ݣ�89��
uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[65]={0x0000};			//ȫ�����飬�����ƽ�ң����·�и�֡A�¶����ݣ�65��
uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[65]={0x0000};			//ȫ�����飬�����ƽ�ң����·�и�֡B�¶����ݣ�65��
uint16 TGTHT510_1553B_data_TGTHT530[13]={0x0000};					//ȫ�����飬����ѹ�������������ң�����ݣ�13��
uint16 TGTHT510_1553B_data_TGTHT520a[7]={0x0000};					//ȫ�����飬�����ƽ���������������ң�⣬7��
uint16 TGTHT510_1553B_data_TGTHT520b[7]={0x0000};					//ȫ�����飬�����ƽ���������������ң�⣬7��
uint16 TGTHT510_1553B_R_HYCT1100[32]={0x0000};						//ȫ�����飬������˷ɴ����͵�ң�⣬25�֣����޸�

uint16 TGTHT510_1553B_R_HYCT1100_data1[32]={0x0000};				//ȫ�����飬������˷ɴ����͵�ң�⡣����ת����1
uint16 TGTHT510_1553B_R_HYCT1100_data2[32]={0x0000};				//ȫ�����飬������˷ɴ����͵�ң�⡣����ת����2

uint16 TGTHT510_1553B_data_KPU[105]={0x0000};						//ȫ�����飬�����ۺϵ��Ӳɼ����ƽ�����������


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

����ָ���ڲ���ַ���룺

1���ƽ����ݼ���������ͨ��0xB1
2���ƽ����ݼ���������ϣ�0xB2
3���ƽ����ݼ���������ͨ��0xB3
4���ƽ����ݼ���������ϣ�0xB4
5��Һ��ģ��I���ù���ͨ��0xB5
6��Һ��ģ��I���ù���ͨ��0xB6
7��Һ��ģ��I�������ù���ϣ�0xB7
8��Һ��ģ��II���ù���ͨ��0xB8
9��Һ��ģ��II���ù���ͨ��0xB9
10��Һ��ģ��II�������ù���ϣ�0xBA
11���˳����ӣ�0xBB
12�����ӿ�ʼ: 0xBC
13��������ֹ��0xBD
14��������ɣ�0xBE
15��������ͣ��0xBF
16�����벹�ӣ�0xC0
17�������˳����ӣ�0xC1
18���ֶ�����ָ��1��0xC2
19���ֶ�����ָ��2��0xC3
20���������ܲ���ʹ�ܣ�0xC4
21�����Ӽ�����0xC5
22���ƽ��ʼ�ʹ�ܣ�0xC6
23���ƽ��ʼ��ֹ��0xC7
24��������ƹ���ʹ�ܣ�0xC8
25��������ƹ��Ľ�ֹ��0xC9
26�������ȿ�ʹ�ܣ�0xCA
27�������ȿؽ�ֹ��0xCB
28��Һ�乤��ʹ�ܣ�0xCC
29��Һ�乤����ֹ��0xCD
30��ʹ��ң����·�����ݣ�0xCE
31��ʹ������ң�����ݣ�0xCF
32������LVb1����LVb1�ء���LVb87�ء�DVb1����DVb1�أ�0x01~0xB0

------------------------------------------------------------------------------------------------------------------------------*/



/******************************************************************************************
**���ƣ�1553B��ʼ������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

  
void TGTHT510_1553b_initial(void)
{
	
	is_wait_overtime=FALSE;
	
/*�ӵ�ַ״̬��־��ѯ�ṹ���ʼ��-----------------------------------------------*/

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

/*����ͨѶ״̬�ṹ���ʼ��-----------------------------------------------*/
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
**���ƣ���ʱ�ȴ�FPGA��дʱ�����ɶ�������TRUE�����򷵻�FALSE
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_1553b_wait_for_fpga(uint16 which_bu65170)
{
	uint16 flag;
	
	flag=BU65170_READ_NOT_ALLOW;
	
	while(flag!=BU65170_READ_ALLOW)
	{
		if(which_bu65170==BU65170_Z)//��ȡ����BU65170����
		{
			flag=Read_32_to_16(*(volatile uint32 *)BU65170_Z_STATUS_REG);
		}
		
		else if(which_bu65170==BU65170_B)//��ȡ����BU65170����
		{
			flag=Read_32_to_16(*(volatile uint32 *)BU65170_B_STATUS_REG);
		}
		
		else
		{
			return FALSE;
		}
		
		/*
		if(is_wait_overtime==TRUE)//�ж��Ƿ�ʱ
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
**���ƣ���ȡ�������ݷֺ�������ȡ��ȷ������TRUE�����򷵻�FALSE
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ��������ݷֺ�����������ȷ������TRUE�����򷵻�FALSE
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�1553Bָ���ջ��ѯѲ�캯��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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

	if((uint8)stack_pointer>=0xfd)//��ջָ�벻����Ϊ����0xfd
	{
		return;
	}
	
	while(TGTHT510_1553B_Subaddress_flag.Current_Stack_Pointer!=(uint8)stack_pointer)
	{
		TGTHT510_1553B_Subaddress_flag.Current_Stack_Pointer=TGTHT510_1553B_Subaddress_flag.Current_Stack_Pointer+4;
		
		command=stack[TGTHT510_1553B_Subaddress_flag.Current_Stack_Pointer+3];
		
		subaddress=(command>>5)&0x001F;//��ȡָ�����е��ӵ�ַ����
		
		switch(subaddress)
		{
			#ifdef TEST_VERSION
			
			case 05://���Ͳ��Լ� ����״̬����
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_05_flag=TRUE;
				break;
			}
			
			#endif
			
			case 11://���͹���ң���볣��ң��
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_11_flag=TRUE;
				
				TGTHT510_which_bus.count=0;
				
				break;
			}
			
			case 12://�����豸����ָ��
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_12_flag=TRUE;
				break;
			}
			
			case 13://�����Ǳ�ң��
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_13_flag=TRUE;
				break;
			}
			
			case 17://����ת��ǰ������ڲ������� ��֡
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_17_flag=TRUE;
				break;
			}
			
			case 19://����תGNC�ʼ�״̬��
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_19_flag=TRUE;
				break;
			}
			
			case 21://�����ڴ��´�����
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_21_flag=TRUE;
				break;
			}
			
			case 23://���͹��ϴ���
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_23_flag=TRUE;
				break;
			}
			
			case 28://���ͷ�������
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_28_flag=TRUE;
				break;
			}
			
			case 14://����ң����·�У��ƽ�������������ѹ�������������ң������
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_14_flag=TRUE;
				break;
			}
			
			case 15://��������ָ�����ֿ�ָ��
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_15_flag=TRUE;
				break;
			}
			
			case 16://����ע��ָ��
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_16_flag=TRUE;
				break;
			}
			
			case 18://���ܻ������Ͳ�����Ϣ������ת����1��
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_18_flag=TRUE;
				break;
			}
			
			case 20://���ܻ������Ͳ�����Ϣ������ת����2��
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_20_flag=TRUE;
				break;
			}
			
			case 22://�����ۺϵ��Ӳɼ����ƽ�����������
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_22_flag=TRUE;
				break;
			}
			
			case 29://��������ָ��
			{
				TGTHT510_1553B_Subaddress_flag.Subaddress_29_flag=TRUE;
				break;
			}
			
			default:break;
					
		}
	}	
}




/******************************************************************************************
**���ƣ�����ͨѶ״̬������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
1���豸�����ݽ���״̬��6���֣���12�ֽڣ���Ϊ����ң���´����棻
2��CG_equiment_receive_state_data[0]�ĸ��ֽڻ��泣���빤��ң��ͨѶ״̬��
3��CG_equiment_receive_state_data[0]�ĵ��ֽڻ����Ǳ�ң��ͨѶ״̬��
4��CG_equiment_receive_state_data[1]�ĸ��ֽڻ��淢�ͻ�����������ͨѶ״̬��
5��CG_equiment_receive_state_data[1]�ĵ��ֽڻ����ƽ�ң����·��ͨѶ״̬��
6��CG_equiment_receive_state_data[2]�ĸ��ֽڻ����ƽ�����������A��ͨѶ״̬��
7��CG_equiment_receive_state_data[2]�ĵ��ֽڻ����ƽ�����������B��ͨѶ״̬��
8��CG_equiment_receive_state_data[3]�ĸ��ֽڻ���ѹ�������������ͨѶ״̬��
9��CG_equiment_receive_state_data[3]�ĵ��ֽڻ�����ջ���������Ϣ����ͨѶ״̬��
10��CG_equiment_receive_state_data[4]�ĸ��ֽڻ�������ң��ͨѶ״̬��
11��ͨѶ��ʱΪ6FH��
12��ͨѶ����Ϊ4EH��
13��ͨѶ���ݽ��մ���ΪAAH��

-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
	
//-----����ң���빤��ң��---------------------------------------------------------------
	
	if((TGTHT510_1553B_message_state.CG_GC_message_count_Z>=MESSAGE_STATE_MAX_COUNT)&&\
	(TGTHT510_1553B_message_state.CG_GC_message_count_B>=MESSAGE_STATE_MAX_COUNT))
	{
		temp[0]=temp[0]|(((uint16)MESSAGE_STATE_ABNORMAL)<<8);//�����빤��ң��ͨѶ��ʱ
	}
	
	else
	{
		temp[0]=temp[0]|(((uint16)MESSAGE_STATE_NORMAL)<<8);//�����빤��ң��ͨѶ����
	}

//-----�Ǳ�ң��-----------------------------------------------------------------------	
	
	if(TGTHT510_1553B_message_state.YB_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[0]=temp[0]|((uint16)MESSAGE_STATE_ABNORMAL);//�Ǳ�ң��ͨѶ��ʱ
	}
	
	else
	{
		temp[0]=temp[0]|((uint16)MESSAGE_STATE_NORMAL);//�Ǳ�ң��ͨѶ����
	}

//-----�ͻ���ң��--------------------------------------------------------------------
	
	if(TGTHT510_1553B_message_state.HYCT1100_T_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[1]=temp[1]|(((uint16)MESSAGE_STATE_ABNORMAL)<<8);//�ͻ���ң��ͨѶ��ʱ
	}
	
	else
	{
		temp[1]=temp[1]|(((uint16)MESSAGE_STATE_NORMAL)<<8);//�ͻ���ң��ͨѶ����
	}
	
//-----�����ƽ�ң����·��ң��--------------------------------------------------------	
	
	if(TGTHT510_1553B_message_state.TGTHT100_message_count>=MESSAGE_STATE_MAX_COUNT)
	{

		temp[1]=temp[1]|((uint16)MESSAGE_STATE_ABNORMAL);//�ƽ�ң����·��ң��ͨѶ��ʱ
		
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
			temp[1]=temp[1]|((uint16)MESSAGE_STATE_R_ERROR);//�ƽ�ң����·�н������ݴ���
			
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
			temp[1]=temp[1]|((uint16)MESSAGE_STATE_NORMAL);//�ƽ�ң����·��ң��ͨѶ����
		}

	}
	
	
//-----�����ƽ�����������A��ң��--------------------------------------------------------	
	
	if(TGTHT510_1553B_message_state.TGTHT520a_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[2]=temp[2]|(((uint16)MESSAGE_STATE_ABNORMAL)<<8);//�ƽ�����������A��ң��ͨѶ��ʱ
		
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
			temp[2]=temp[2]|(((uint16)MESSAGE_STATE_R_ERROR)<<8);//�ƽ�����������A��ң��ͨѶ���ݴ���
			for(j=0;j<=6;j++)
			{
			TGTHT510_1553B_data_TGTHT520a[j]=0x0000;
			}
		}
		
		else
		{
			temp[2]=temp[2]|(((uint16)MESSAGE_STATE_NORMAL)<<8);//�ƽ�����������A��ң��ͨѶ����
		}
		
	}
	
//-----�����ƽ�����������B��ң��--------------------------------------------------------	
	
	if(TGTHT510_1553B_message_state.TGTHT520b_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[2]=temp[2]|((uint16)MESSAGE_STATE_ABNORMAL);//�ƽ�����������B��ң��ͨѶ��ʱ
		
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
			temp[2]=temp[2]|((uint16)MESSAGE_STATE_R_ERROR);//�ƽ�����������B��ң��ͨѶ���ݴ���
			for(j=0;j<=6;j++)
			{
				TGTHT510_1553B_data_TGTHT520b[j]=0x0000;
			}
		}
		
		else
		{
			temp[2]=temp[2]|((uint16)MESSAGE_STATE_NORMAL);//�ƽ�����������B��ң��ͨѶ����
		}
	}
	

//-----����ѹ�������������ң��--------------------------------------------------------	

	if(TGTHT510_1553B_message_state.TGTHT530_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[3]=temp[3]|(((uint16)MESSAGE_STATE_ABNORMAL)<<8);//ѹ�������������ң��ͨѶ��ʱ
		
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
			temp[3]=temp[3]|(((uint16)MESSAGE_STATE_R_ERROR)<<8);//ѹ�������������ң��ͨѶ���ݴ���
			for(j=0;j<=12;j++)
			{
				TGTHT510_1553B_data_TGTHT530[j]=0x0000;
			}
		}
		
		else
		{
			temp[3]=temp[3]|(((uint16)MESSAGE_STATE_NORMAL)<<8);//ѹ�������������ң��ͨѶ����
		}
		
	}

//-----���ջ���������Ϣ����ң��--------------------------------------------------------	

	if(TGTHT510_1553B_message_state.HYCT1100_R_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[3]=temp[3]|((uint16)MESSAGE_STATE_ABNORMAL);//���ջ���������Ϣң��ͨѶ��ʱ
		
		TGTHT510_1553B_message_state.HYCT1100_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	}
	
	else
	{
		if(TGTHT510_1553B_message_state.HYCT1100_validity==MESSAGE_STATE_VALIDITY_FALSE)
		{
			temp[3]=temp[3]|((uint16)MESSAGE_STATE_R_ERROR);//���ջ���������Ϣң��ͨѶ���ݴ���
			
			for(j=0;j<=24;j++)
			{
				TGTHT510_1553B_R_HYCT1100[j]=0x0000;
			}
		}
		
		else
		{
			temp[3]=temp[3]|((uint16)MESSAGE_STATE_NORMAL);//���ջ���������Ϣң��ͨѶ����
		}
	}

//-----��������ң��----------------------------------------------------------------------	
	
	if(TGTHT510_1553B_message_state.KPU_message_count>=MESSAGE_STATE_MAX_COUNT)
	{
		temp[4]=temp[4]|(((uint16)MESSAGE_STATE_ABNORMAL)<<8);//����ң��ͨѶ��ʱ
		
		TGTHT510_1553B_message_state.KPU_validity=MESSAGE_STATE_VALIDITY_UNKNOW;
	}
	
	else
	{
		if(TGTHT510_1553B_message_state.KPU_validity==MESSAGE_STATE_VALIDITY_FALSE)
		{
			temp[4]=temp[4]|(((uint16)MESSAGE_STATE_R_ERROR)<<8);//����ң��ͨѶ���ݴ���
		}
		
		
		else
		{
			temp[4]=temp[4]|(((uint16)MESSAGE_STATE_NORMAL)<<8);//����ң��ͨѶ����
		}
		
	}

//-----���³���ң������----------------------------------------------------------------------	
	
	for(i=0;i<=5;i++)
	{
		CG_equiment_receive_state_data[i]=temp[i];
	}
	
	
}



/******************************************************************************************
**���ƣ�����ͨѶ״̬�������º���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�1553B����������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�1553B����������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_main(void)
{
	uint16 b;	
	b=TGTHT510_which_bus_choice();
	if(b==BU65170_Z)
	{
		TGTHT510_1553b_dealing(BU65170_Z);//1553BѲ��������
	
		TGTHT510_1553b_receiveANDtransmitdata(BU65170_Z);//�Զ�ջ������Ѳ��
	}
	
	else if(b==BU65170_B)
	{
		TGTHT510_1553b_dealing(BU65170_B);//1553BѲ��������
	
		TGTHT510_1553b_receiveANDtransmitdata(BU65170_B);//�Զ�ջ������Ѳ��
	}
	
	else
	{
		return;
	}
}


/******************************************************************************************
**���ƣ�1553BѲ�촦����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_dealing(uint16 which_bu65170)							
{
	#ifdef TEST_VERSION
	//���Լ�ʹ�ã����ͷ���״̬
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_05_flag==TRUE)
	{
		TGTHT510_1553b_transmitcommand_test_FM_state(which_bu65170);

		TGTHT510_1553B_Subaddress_flag.Subaddress_05_flag=FALSE;
	}
	#endif
	
	//���ͳ����빤��ң�����
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
	
	//�����豸����ָ��
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_12_flag==TRUE)
	{
		asm("nop;");
	}

	//�����Ǳ���ʾң��
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_13_flag==TRUE)
	{
		TGTHT510_1553b_transmitdata_YBYC(which_bu65170);
		
		TGTHT510_1553B_message_state.YB_message_count=0x0000;
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_13_flag=FALSE;
	}
	
	//����ת��ǰ������ڲ������� ��֡
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_17_flag==TRUE)
	{
		TGTHT510_1553b_transmitdata_HYCT1100(which_bu65170);
		
		TGTHT510_1553B_message_state.HYCT1100_T_message_count=0x0000;
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_17_flag=FALSE;
	}
	
	//����תGNC�ʼ�״̬��
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_19_flag==TRUE)
	{
		TGTHT510_1553b_transmitdata_GNC(which_bu65170);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_19_flag=FALSE;
	}
	
	//�����ڴ��´�����
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_21_flag==TRUE)
	{
		TGTHT510_1553b_transmitdata_MEMORY(which_bu65170);
		
		//TGTHT510_1553B_Subaddress_flag.Subaddress_21_flag=FALSE;
	}
	
	//���͹��ϴ���
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_23_flag==TRUE)
	{
		TGTHT510_1553B_Subaddress_flag.Subaddress_23_flag=FALSE;
	}
	
	//���ͷ�������
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_28_flag==TRUE)
	{
		TGTHT510_1553b_transmitdata_askforserive(which_bu65170);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_28_flag=FALSE;
	}
	
	//����520��530��540��������
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_14_flag==TRUE)
	{
		TGTHT510_1553b_receivedata_subsystem(which_bu65170);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_14_flag=FALSE;
	}
	
	//��������ָ�����ֿ�ָ��
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_15_flag==TRUE)
	{
		TGTHT510_1553b_receivecommand_buscommand(which_bu65170);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_15_flag=FALSE;
	}
	
	//����ע��ָ��
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_16_flag==TRUE)
	{
		TGTHT510_1553b_receivecommand_inputcommand(which_bu65170);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_16_flag=FALSE;
	}
	
	//���ܻ������Ͳ�����Ϣ������ת����1��
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_18_flag==TRUE)
	{
		TGTHT510_1553b_receivedata_HYCT1100(which_bu65170,TYPE_RECEIVE_HYCT_DATA1);
		
		TGTHT510_1553B_message_state.HYCT1100_R_message_count=0x0000;
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_18_flag=FALSE;
	}

	//���ܻ������Ͳ�����Ϣ������ת����2��
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_20_flag==TRUE)
	{
		TGTHT510_1553b_receivedata_HYCT1100(which_bu65170,TYPE_RECEIVE_HYCT_DATA2);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_20_flag=FALSE;
	}
	
	//�����ۺϵ��Ӳɼ����ƽ�����������
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_22_flag==TRUE)
	{
		TGTHT510_1553b_receivedata_KPU(which_bu65170);
		
		TGTHT510_1553B_message_state.KPU_message_count=0x0000;	
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_22_flag=FALSE;
	}
	
	//��������ָ��
	if(TGTHT510_1553B_Subaddress_flag.Subaddress_29_flag==TRUE)
	{
		TGTHT510_1553b_receivecommand_interactivecommand(which_bu65170);
		
		TGTHT510_1553B_Subaddress_flag.Subaddress_29_flag=FALSE;
	}

}

/******************************************************************************************
**���ƣ����͹���ң���볣��ң��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_transmitdata_CGandGC(uint16 which_bu65170)
{
	uint16 temp;
	
	uint16 base_pointer;
	
	temp=0x0002;//EPDU��������ʶ
	
	base_pointer=BU65170_CG_GC_POINTER;//��ָ��ʹ��
	
	TGTHT510_collectANDgroup_CG_group();//����ң��������֡
	
	TGTHT510_collectANDgroup_GC_group();//����ң��������֡
	
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_CG_GC_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
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
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_CG_GC_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
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
**���ƣ����ͷ���ң��״̬��ʵ���ʹ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ������Ǳ�ң��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_transmitdata_YBYC(uint16 which_bu65170)
{
	uint16 temp;
	
	uint16 base_pointer;
	
	temp=0x0001;//EPDU��������ʶ
	
	base_pointer=BU65170_YB_POINTER;//��ָ��ʹ��
	
	TGTHT510_collectANDgroup_YB_group();//�Ǳ�ң��������֡
	
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_YB_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_YB_BASE,&temp,1)==FALSE)//EPDU��������ʶ
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
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_YB_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_YB_BASE,&temp,1)==FALSE)//EPDU��������ʶ
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
**���ƣ����������˷ɴ��ƽ�����������״̬��Ϣ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_transmitdata_HYCT1100(uint16 which_bu65170)
{
	
	uint16 temp;
	
	uint16 base_pointer;
	
	temp=0x0001;//EPDU��������ʶ
	
	base_pointer=BU65170_HYCT1100_POINTER;//��ָ��ʹ��
	
	TGTHT510_collectANDgroup_HYCT_group();//�ͻ���ң��������֡
	
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_HYCT1100_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_HYCT1100_BASE,&temp,1)==FALSE)//EPDU��������ʶ
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
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_HYCT1100_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_HYCT1100_BASE,&temp,1)==FALSE)//EPDU��������ʶ
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
**���ƣ�ת��GNC�ʼ�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_transmitdata_GNC(uint16 which_bu65170)
{
	uint16 temp;
	
	uint16 base_pointer;
	
	temp=0x0001;//EPDU��������ʶ
	
	base_pointer=BU65170_GNC_POINTER;//��ָ��ʹ��
	
	TGTHT510_collectANDgroup_GNC_group();//����ת��GNC�ʼ�״̬��
	
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_GNC_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_GNC_BASE,&temp,1)==FALSE)//EPDU��������ʶ
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
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_GNC_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
		{
			return;
		}
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_GNC_BASE,&temp,1)==FALSE)//EPDU��������ʶ
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
**���ƣ��ڴ��´����ݷ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_transmitdata_MEMORY(uint16 which_bu65170)
{
	uint16 temp;
	
	uint16 base_pointer;
	
	temp=0x0001;//EPDU��������ʶ
	
	base_pointer=BU65170_MEMORY_POINTER;//��ָ��ʹ��
	
	if(TGTHT510_1553B_service_flag.Subaddress_21_service_flag==TRUE)//���ܵ��ӵ�ַ21����ָ��
	{
		TGTHT510_1553B_service_flag.Subaddress_21_service_flag=FALSE;
		
		TGTHT510_collectANDgroup_MEMORY_group();
		
		if(which_bu65170==BU65170_Z)
		{
			
			if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_MEMORY_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
			{
				return;
			}
			
			if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_MEMORY_BASE,&temp,1)==FALSE)//EPDU��������ʶ
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
			if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_MEMORY_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
			{
				return;
			}
			
			if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_MEMORY_BASE,&temp,1)==FALSE)//EPDU��������ʶ
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
**���ƣ����ͷ�������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_transmitdata_askforserive(uint16 which_bu65170)
{
	
	uint16 base_pointer;
	
	base_pointer=BU65170_ASKFORSERIVE_POINTER;//��ָ��ʹ��
		
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_ASKFORSERIVE_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
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
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_ASKFORSERIVE_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
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
**���ƣ������豸����ָ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_transmitcommand_equiment(uint16 which_bu65170)
{
	
	uint16 base_pointer;
	
	base_pointer=BU65170_COMMAND_EQUIP_POINTER;//��ָ��ʹ��
	
	if(which_bu65170==BU65170_Z)
	{
		
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_Z_T_COMMAND_EQUIP_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
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
		if(TGTHT510_1553b_set_data(which_bu65170,BU65170_B_T_COMMAND_EQUIP_POINTER,&base_pointer,1)==FALSE)//ѭ����ָ��
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
**���ƣ���ȡң����·�У��ƽ�������������ѹ�������������EPDU���ۼӺ�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�����ң����·�У��ƽ�������������ѹ�������������EPDU���ۼӺ�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�����ң����·�У��ƽ�������������ѹ�������������EPDU������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_1553b_receivedata_subsystem_EPDU_length_generate(uint16 type)
{
	uint16 length;
	if((type==EPDU_TYPE_TGTHT100A)||(type==EPDU_TYPE_TGTHT100B))//�ƽ�ң����·��EPDUԴ��
	{
		length=EPDU_LENGTH_TGTHT100;
	}
	
	else if(type==EPDU_TYPE_TGTHT530)//���������EPDUԴ��
	{
		length=EPDU_LENGTH_TGTHT530;
	}
	
	else if(type==EPDU_TYPE_TGTHT520A)//�ƽ�������������·EPDUԴ��
	{
		length=EPDU_LENGTH_TGTHT520A;
	}
	
	else if(type==EPDU_TYPE_TGTHT520B)//�ƽ�������������·EPDUԴ��
	{
		length=EPDU_LENGTH_TGTHT520B;
	}
	
	else
	{
		length=EPDU_LENGTH_ERROR;//EPDUԴ�����ʹ���
	}
	
	return length;
	
}


/******************************************************************************************
**���ƣ�����ң����·�У��ƽ�������������ѹ�������������EPDU������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_receivedata_subsystem_buffer(uint16 type,uint16 *p,uint16 length)
{
	uint16 i;
	if((type==EPDU_TYPE_TGTHT100A)||(type==EPDU_TYPE_TGTHT100B))//�ƽ�ң����·��ң�⸴֡����
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
		
		
	else if(type==EPDU_TYPE_TGTHT530)//ѹ�������������ң������
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
		return;//EPDUԴ�����ʹ���
	}

}

/******************************************************************************************
**���ƣ�����ң����·�У��ƽ�������������ѹ�������������EPDU������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_1553b_receivedata_subsystem_save_EPDU(uint16 type,uint16 start_i,uint16 which_bu65170)
{
	uint16 EPDU_data[160];
	uint8 EPDU_sum;//EPDU�ۼӺ�
	uint8 calculate_sum;//�����ۼӺ�
	uint16 i;
	uint16 length;
	
	length=TGTHT510_1553b_receivedata_subsystem_EPDU_length_generate(type);
	
	if(length==EPDU_LENGTH_ERROR)
	{
		return FALSE;//EPDUԴ�����ȴ���
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
	
	calculate_sum=TGTHT510_1553b_receivedata_subsystem_EPDU_sum_calculate(type,EPDU_data,length-1);//�����ۼӺ�
	
	EPDU_sum=TGTHT510_1553b_receivedata_subsystem_EPDU_sum_get(type,EPDU_data,length);//EPDU�ۼӺ�
	
	TGTHT510_1553b_receivedata_subsystem_buffer(type,EPDU_data,length);
	/*
	if(calculate_sum==EPDU_sum)
	{
		TGTHT510_1553b_receivedata_subsystem_buffer(type,EPDU_data,length);

	}
	else
	{
		return FALSE;//EPDUԴ���ۼӺʹ���
	}
	*/
	
	return TRUE;

}


/******************************************************************************************
**���ƣ�����ң����·�У��ƽ�������������ѹ�������������ң������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_receivedata_subsystem(uint16 which_bu65170)
{
	uint16 i;
	uint16 EPDU_num;//EPDUԴ����������
	uint16 EPDU_APID;//EPDUԴ��APID
	uint16 EPDU_subservice;//EPDUԴ������ͷ
	uint8 EPDU_sum;//EPDUԴ���ۼӺ�
	uint16 temp;
	
	//��ȡEPDU����������
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
		return;	//Դ���������������˳����շֺ���	
	}
	
	else
	{
		i=0x0001;
		while(EPDU_num!=0)
		{
			EPDU_num--;
			
			//��ȡEPDU_APID
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
			
			//��ȡEPDU_subservice
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
			
			if((EPDU_APID==R_APID_TGTHT100)&&(EPDU_subservice==R_SUBSERVICE_TGTHT100_A))//�ƽ�ң����·��ң�⸴֡A����
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
			
			else if((EPDU_APID==R_APID_TGTHT100)&&(EPDU_subservice==R_SUBSERVICE_TGTHT100_B))//�ƽ�ң����·��ң�⸴֡B����
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
			
			else if((EPDU_APID==R_APID_TGTHT530)&&(EPDU_subservice==R_SUBSERVICE_TGTHT530))//ѹ�������������ң������
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
			
			else if((EPDU_APID==R_APID_TGTHT520a)&&(EPDU_subservice==R_SUBSERVICE_TGTHT520a))//�ƽ���������������ң������
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
			
			else if((EPDU_APID==R_APID_TGTHT520b)&&(EPDU_subservice==R_SUBSERVICE_TGTHT520b))//�ƽ���������������ң������
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
				return;	//�˳����շֺ���
			}
	
		}
		
	}

}

/******************************************************************************************
**���ƣ���������ָ��ISOУ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ��ж�����ָ���ʽ�Ƿ���ȷ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_1553b_receivecommand_buscommand_is_correct(uint16 *p)
{
	uint16 i;
	uint16 data[6];
	uint16 sum;
	
	if(p[0]!=0x0001)
	{
		return FALSE;//EPDU��������ʶ����
	}
	
	if((p[1]!=0x1b01)||(p[2]!=0x0000)||(p[3]!=0x0007))
	{
		return FALSE;//������ͷ����
	}
	
	if((p[4]!=0x0202)&&(p[4]!=0x0201))
	{
		return FALSE;//�������ͣ����������ʹ���
	}
	
	if(p[5]!=p[6])
	{
		return FALSE;//ָ�����ݲ���ͬ
	}
	
	for(i=0;i<=5;i++)
	{
		data[i]=p[i+1];
	}
	
	sum=TGTHT510_1553b_receivecommand_buscommand_ISO_calculate(data,6);//����ISOУ����
	
	if(sum!=p[7])
	{
		return FALSE;//ISOУ�����
	}
	
	return TRUE;
	

}


/******************************************************************************************
**���ƣ�����ָ�����ݴ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_receivecommand_buscommand_code_dealing(uint8 code)
{
	
	if((code>=LVb1K)&&(code<=LVb87G))//������ָ��
	{
		TGTHT510_valvecontrol_struct.command_from_bus=code;//���ſ���ȫ�ֽṹ��д�뷧���ڲ���ַ����
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
				case 0xB1://�ƽ����ݼ���������ͨ��0xB1
				{
					TGTHT510_1553b_relay_dealing(BUS_MAIN_HEATER_POWER_ON);
					
					break;
				}
				
				case 0xB2://�ƽ����ݼ���������ϣ�0xB2
				{
					TGTHT510_1553b_relay_dealing(BUS_MAIN_HEATER_POWER_OFF);
					
					break;
				}
				
				case 0xB3://�ƽ����ݼ���������ͨ��0xB3
				{
					TGTHT510_1553b_relay_dealing(BUS_LESS_HEATER_POWER_ON);
					break;
				}
				
				case 0xB4://�ƽ����ݼ���������ϣ�0xB4
				{
					TGTHT510_1553b_relay_dealing(BUS_LESS_HEATER_POWER_OFF);
					break;
				}
				
				case 0xB5://Һ��ģ��I���ù���ͨ��0xB5
				{
					TGTHT510_1553b_relay_dealing(BUS_COOLER_1_MAIN_POWER_ON);
					break;
				}
				
				case 0xB6://Һ��ģ��I���ù���ͨ��0xB6
				{
					TGTHT510_1553b_relay_dealing(BUS_COOLER_1_LESS_POWER_ON);
					break;
				}
				
				case 0xB7://Һ��ģ��I�������ù���ϣ�0xB7
				{
					TGTHT510_1553b_relay_dealing(BUS_COOLER_1_POWER_OFF);
					break;
				}
				
				case 0xB8://Һ��ģ��II���ù���ͨ��0xB8
				{
					TGTHT510_1553b_relay_dealing(BUS_COOLER_2_MAIN_POWER_ON);
					break;
				}
				
				case 0xB9://Һ��ģ��II���ù���ͨ��0xB9
				{
					TGTHT510_1553b_relay_dealing(BUS_COOLER_2_LESS_POWER_ON);
					break;
				}
				
				case 0xBA://Һ��ģ��II�������ù���ϣ�0xBA
				{
					TGTHT510_1553b_relay_dealing(BUS_COOLER_2_POWER_OFF);
					break;
				}
				
				case 0xBB://�˳����ӣ�0xBB
				{
					TGTHT510_supply_ctrl.state=STATE_NONE;//����״̬������
			
					TGTHT510_supply_ctrl.stage=STAGE_00_NONE;//���ӽ׶Σ���
					
					TGTHT510_supply_ctrl.step=STEP_NONE;//���Ӳ��裺��
					
					TGTHT510_supply_ctrl.command=COMMAND_NONE;//����ָ���
					
					TGTHT510_supply_time_stage_end();
					
					TGTHT510_supply_main_initial();
					
					break;
				}
				
				case 0xBC://���ӿ�ʼ��0xBC
				{
					//���޾��幦��
					
					break;
				}
				
				case 0xBD://������ֹ��0xBD
				{
					TGTHT510_supply_ctrl.state=STATE_BREAK;
	
					TGTHT510_supply_ctrl.step=STEP_START;
	
					TGTHT510_supply_ctrl.command=COMMAND_START;
					
					break;
				}
				
				case 0xBE://������ɣ�0xBE
				{
					//���޾��幦��
					
					break;
				}
				
				case 0xBF://������ͣ��0xBF
				{
					TGTHT510_supply_ctrl.step_temp=TGTHT510_supply_ctrl.step;
	
					TGTHT510_supply_ctrl.command_temp=TGTHT510_supply_ctrl.command;
					
					TGTHT510_supply_ctrl.state=STATE_PAUSE;
	
					TGTHT510_supply_ctrl.step=STEP_START;
	
					TGTHT510_supply_ctrl.command=COMMAND_START;
					
					break;
				}
				
				case 0xC0://���벹�ӣ�0xC0
				{
					//���޾��幦��
					
					break;
				}
				
				case 0xC1://�����˳����ӣ�0xC1
				{
					//���޾��幦��
					
					break;
				}
				
				case 0xC2://�ֶ�����ָ��1��0xC2
				{
					
					//���޾��幦��
					
					break;
				}
				
				case 0xC3://�ֶ�����ָ��2��0xC3
				{
					//���޾��幦��
					
					break;
				}
				
				case 0xC4://�������ܲ���ʹ�ܣ�0xC4
				{
					
					break;
				}
				
				case 0xC5://���Ӽ�����0xC5
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
				
				case 0xC6://�ƽ��ʼ�ʹ�ܣ�0xC6
				{
					TGTHT510_faultdiagnosis_push_all_enable_disable_set(ENABLE);
					break;
				}
				
				case 0xC7://�ƽ��ʼ��ֹ��0xC7
				{
					TGTHT510_faultdiagnosis_push_all_enable_disable_set(DISABLE);
					break;
				}
				
				case 0xC8://������ƹ���ʹ�ܣ�0xC8
				{
					Temperature_control_global.total_power=70;
					break;
				}
				
				case 0xC9://������ƹ��Ľ�ֹ��0xC9
				{
					Temperature_control_global.total_power=300;
					break;
				}
				
				case 0xCA://�����ȿ�ʹ�ܣ�0xCA
				{
					TGTHT510_tempercontrol_supply_is_auto_control(ENABLE);
					break;
				}
				
				case 0xCB://�����ȿؽ�ֹ��0xCB
				{
					TGTHT510_tempercontrol_supply_is_auto_control(DISABLE);
					break;
				}
				
				case 0xCC://Һ�乤��ʹ�ܣ�0xCC
				{
					
					break;
				}
				
				case 0xCD://Һ�乤����ֹ��0xCD
				{
					
					break;
				}
				
				case 0xCE://ʹ��ң����·�����ݣ�0xCE
				{
					
					break;
				}
				
				case 0xCF://ʹ������ң�����ݣ�0xCF
				{
					
					break;
				}
				
				default:break;
	
			}

	}

}


/******************************************************************************************
**���ƣ���������ָ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_receivecommand_buscommand(uint16 which_bu65170)
{
	uint16 bus_command_data[8];//��������ָ����������
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
		return;//ָ���ʽ����
	}
	
	command_code=TGTHT510_1553B_Bcommand_code[((uint8)bus_command_data[5])];//����ָ���ڲ���ַ����
	
	TGTHT510_1553b_receivecommand_buscommand_code_dealing(command_code);//����ָ�����ݴ���
	
	CG_bus_command[0]=bus_command_data[6];//����ָ��������Ϊ����ң���´�
	CG_bus_command[1]=bus_command_data[7];//����ָ��У����Ϊ����ң���´�

}

/******************************************************************************************
**���ƣ���ȡע��ָ���ָ��������У��ͣ���Ϊ����ң���´�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_receivecommand_inputcommand_state_data(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i,uint16 length)
{
	uint16 type;		//����ָ������
	uint16 sum;			//����ע��EPDU��У���
	
	CG_inputcommand_receive_state_data[0]=a.inputcommand_data[start_i+4];//ָ������
	
	CG_inputcommand_receive_state_data[1]=a.inputcommand_data[start_i+length-1];//ע��EPDU��У���

}

/******************************************************************************************
**���ƣ�����ע��ָ��CRCУ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_1553b_receivecommand_inputcommand_CRC_calculate(TGTHT510_1553B_inputcommand_TypeDef a)
{
	uint16 i;
	uint16 CRC;//У����
	uint8 temp;
	CRC=0x0000;
	
	temp=(uint8)(a.inputcommand_head_word1>>8);//���ֽ�
	CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	
	temp=(uint8)(a.inputcommand_head_word1);//���ֽ�
	CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	
	temp=(uint8)(a.inputcommand_head_word2>>8);//���ֽ�
	CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	
	temp=(uint8)(a.inputcommand_head_word2);//���ֽ�
	CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	
	temp=a.inputcommand_head_byte;
	CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	
	for(i=0;i<=a.inputcommand_data_length-2;i++)
	{
		temp=(uint8)(a.inputcommand_data[i]>>8);//���ֽ�
		CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
		
		temp=(uint8)(a.inputcommand_data[i]);//���ֽ�
		CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	}
	
	temp=(uint8)(a.inputcommand_data[a.inputcommand_data_length-1]>>8);//���ֽ�
	CRC=TGTHT510_collectANDgroup_Byte_CRC(CRC,temp);
	
	return CRC;

}



/******************************************************************************************
**���ƣ��ж�ע��ָ���ʽ�Ƿ���ȷ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_1553b_receivecommand_inputcommand_is_correct(TGTHT510_1553B_inputcommand_TypeDef a)
{
	uint16 VCID;
	uint16 length;
	uint16 CRC;
	
	if(a.inputcommand_head_word1!=0x0001)
	{
		return FALSE;//����ͷ����
	}
	
	VCID=a.inputcommand_head_word2>>10;//����ͨ��
	
	if((VCID!=0x0010)&&(VCID!=0x0015))
	{
		return FALSE;//����ͨ������
	}
	
	length=a.inputcommand_head_word2&0x03ff;
	
	if((length!=835)&&(length!=233))
	{
		return FALSE;//֡���ȴ���
	}
	
	CRC=TGTHT510_1553b_receivecommand_inputcommand_CRC_calculate(a);//����CRCУ����
	
	if(CRC!=a.inputcommand_CRC)
	{
		//return FALSE;//CRCУ�����
	}
	
	return TRUE;

}



/******************************************************************************************
**���ƣ�����ע��ָ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
TGTHT510_1553B_inputcommand_TypeDef TGTHT510_1553b_receivecommand_inputcommand_save(uint16 which_bu65170)
{
	TGTHT510_1553B_inputcommand_TypeDef a;//����ע��ָ��
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
	a.inputcommand_length=0x0000;//��ʼ��ע��֡���ݽṹ��
	
	//��ȡע��ָ��֡����
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
	
	length=length&0x03ff;//ң�ش���֡��֡��
	
	if((length==233)||(length==835))
	{
		a.inputcommand_length=length;//����֡����
	}
	else
	{
		return a;//֡������
	}
	
	i_max=(a.inputcommand_length-5)>>1;
	a.inputcommand_data_length=i_max;
	
	//֡��Ϊ233����234�ֽڣ�������227�ֽڣ�16bit����Ϊ2*114��=228�ֽ�
	//֡��Ϊ835����836�ֽڣ�������829�ֽڣ�16bit����Ϊ2*415��=830�ֽ�
	
	//a.inputcommand_data���1�ֵĵ��ֽڲ��Ǵ���֡�����������
	
	//����ͷ1
	
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
	
	//����ͷ2
	
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

	//֡���к�
	
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
	
	//���ֽڻ���ң��֡���������һ�ֽڣ����ֽڷ�����������
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
**���ƣ�ע��ָ���EPDU�����ݴ����������ش����EPDU������,�봦����������2bitΪ11��ʾ�������00��ʾ������ȷ����14λΪEPDU������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
		return result;//����EPDU�����ȴ���
	}
	
	result=result|(length&0x3fff);
	
	correct=TGTHT510_1553b_receivecommand_inputcommand_EPDU_is_correct(a,start_i,length);
	
	if(correct==FALSE)
	{
		result=(result&0x3fff)|0xc000;
		return result;//EPDU��ʽ����
	}
	
	type=a.inputcommand_data[start_i+4];
	
	switch(type)
	{
		case INPUT_COMMAND_TYPE_POWER://�޸ķ�ֵ����
		{
			TGTHT510_1553b_inputcommand_dealing_power(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MULTI_CONTR_SPOT://�޸Ķ�����»�·�Ŀ��µ�
		{
			TGTHT510_1553b_inputcommand_dealing_multi_contr_spot(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ALL_CONTR_SPOT://�޸�ȫ�����»�·�Ŀ��µ�
		{
			TGTHT510_1553b_inputcommand_dealing_all_contr_spot(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ONE_MEA_SPOT://�޸�ĳһ���»�·�Ŀ��²��
		{
			TGTHT510_1553b_inputcommand_dealing_one_mea_spot(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ONE_FIXED://ָ��ĳһ���»�·����ָ��ռ�ձ����
		{
			TGTHT510_1553b_inputcommand_dealing_one_fixed(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_AUTO_RESUME://�ָ�ĳһ���»�·Ϊ�Զ�����״̬
		{
			TGTHT510_1553b_inputcommand_dealing_auto_resume(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ALL_RESUME://�ָ����п��»�·����״̬
		{
			TGTHT510_1553b_inputcommand_dealing_all_resume(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SOURCE://ָ�����²�����Դѡ��
		{
			TGTHT510_1553b_inputcommand_dealing_source(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_PLACE_SIGNAL_EN://ָ��ĳһ·���䵽λ�ź�ʹ��
		{
			TGTHT510_1553b_inputcommand_dealing_place_signal_en(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_PLACE_SIGNAL_DIS://ָ��ĳһ·���䵽λ�źŽ�ֹ
		{
			TGTHT510_1553b_inputcommand_dealing_place_signal_dis(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_FAULT_EN://ָ��ĳһ·�ʼ�ʹ��
		{
			TGTHT510_1553b_inputcommand_dealing_fault_en(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_FAULT_DIS://ָ��ĳһ·�ʼ��ֹ
		{
			TGTHT510_1553b_inputcommand_dealing_fault_dis(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_STAGE://���ӽ׶�ע��
		{
			TGTHT510_1553b_inputcommand_dealing_supply_stage(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_PARA://���Ӳ���ע��
		{
			TGTHT510_1553b_inputcommand_dealing_supply_para(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EXHAUST://ע���©�����ŷ�ʱ��
		{
			TGTHT510_1553b_inputcommand_dealing_exhaust(a,start_i);
			break;	
		}
		
		
		case INPUT_COMMAND_TYPE_MAX_COMP://ע��������ʱ��
		{
			TGTHT510_1553b_inputcommand_dealing_max_comp(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_VELOCITY://ע����󲹼�����
		{
			TGTHT510_1553b_inputcommand_dealing_max_velocity(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MIN_VELOCITY://ע����С��������
		{
			TGTHT510_1553b_inputcommand_dealing_min_velocity(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_FLOW://ע����󲹼�����ʱ��
		{
			TGTHT510_1553b_inputcommand_dealing_max_flow(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_TEMP_CONTR_MODE://ע�벹�ӹ�·�¶ȿ���ģʽ
		{
			TGTHT510_1553b_inputcommand_dealing_temp_contr_mode(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_START_MIN://ע��ѹ���������¶�����
		{
			TGTHT510_1553b_inputcommand_dealing_comp_start_min(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_START_MAX://ע��ѹ���������¶�����
		{
			TGTHT510_1553b_inputcommand_dealing_comp_start_max(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_ALARM://ע��ѹ���������¶���ֵ
		{
			TGTHT510_1553b_inputcommand_dealing_comp_alarm(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COM_COOLER://ע��ѹ������Һ���¶Ȳ�ֵ
		{
			
			break;	
		}

		case INPUT_COMMAND_TYPE_COMP_PRESSURE://ע��ѹ������������ѹ��
		{
			TGTHT510_1553b_inputcommand_dealing_comp_pressure(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_STOP_PRE://ע��ѹ����ͣ�������ѹ��ֵ
		{
			TGTHT510_1553b_inputcommand_dealing_comp_stop_pre(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DP_HIGH://ע���ѹѹ���仯��ֵ
		{
			TGTHT510_1553b_inputcommand_dealing_dp_high(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DP1_LOW://ע���ѹѹ���仯��ֵ1
		{
			TGTHT510_1553b_inputcommand_dealing_dp1_low(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DP2_LOW://ע���ѹѹ���仯��ֵ2
		{
			TGTHT510_1553b_inputcommand_dealing_dp2_low(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_REPRESS://ע�����ѹʱ��
		{
			TGTHT510_1553b_inputcommand_dealing_max_repress(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_START_SPEED://ע��ѹ��������ת��
		{
			TGTHT510_1553b_inputcommand_dealing_comp_start_speed(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_STOP_SPEED://ע��ѹ����ͣ��ת��
		{
			TGTHT510_1553b_inputcommand_dealing_comp_stop_speed(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DELAY_SHORT://ע���޸Ķ���ʱ
		{
			TGTHT510_1553b_inputcommand_dealing_delay_short(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DELAY_LONG://ע���޸ĳ���ʱ
		{
			TGTHT510_1553b_inputcommand_dealing_delay_long(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_BYPATH_TIME://ע���޸���·������ʱ��
		{
			TGTHT510_1553b_inputcommand_dealing_time_bypath(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EPS1://ע���޸�ƫ��eps1
		{
			TGTHT510_1553b_inputcommand_dealing_eps1(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EPS2://ע���޸�ƫ��eps2
		{
			TGTHT510_1553b_inputcommand_dealing_eps2(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_IN_COMP_MAX://ע���޸�ѹ����������ѹ��
		{
			TGTHT510_1553b_inputcommand_dealing_pressure_comp_in_max(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_IN_COMP_MIN://ע���޸�ѹ������С����ѹ��
		{
			TGTHT510_1553b_inputcommand_dealing_pressure_comp_in_min(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_OUT_COMP_MIN://ע���޸�ѹ������С����ѹ��
		{
			TGTHT510_1553b_inputcommand_dealing_pressure_comp_out_min(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_HYCT://ע���޸Ļ������ѹѹ��
		{
			TGTHT510_1553b_inputcommand_dealing_pressure_hyc(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_PIPE_F://ע���޸�ȼ����Һ·ѹ���������趨
		{
			TGTHT510_1553b_inputcommand_dealing_sensor_pipe_F(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_PIPE_O://ע���޸�������Һ·ѹ���������趨
		{
			TGTHT510_1553b_inputcommand_dealing_sensor_pipe_O(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_TANK_F://ע���޸�ȼ����ѹ���������趨
		{
			TGTHT510_1553b_inputcommand_dealing_sensor_tank_F(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_TANK_O://ע���޸�������ѹ���������趨
		{
			TGTHT510_1553b_inputcommand_dealing_sensor_tank_O(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_IN_COMP://ע���޸�ѹ��������ѹ���������趨
		{
			TGTHT510_1553b_inputcommand_dealing_sensor_comp_in(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_LOW_PIPE://ע���޸ĵ�ѹ��·ѹ���������趨
		{
			TGTHT510_1553b_inputcommand_dealing_sensor_pipe_low(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_CONTINUE_G://ע��ָ�����Ӳ����������
		{
			TGTHT510_1553b_inputcommand_dealing_supply_continue_g(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EQU_COMMAND://ע���豸����ָ��
		{
			TGTHT510_1553b_inputcommand_dealing_equ_command(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_HEAT_ON://ע�������ָͨ��
		{
			TGTHT510_1553b_inputcommand_dealing_heat_on(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_PAUSE://ע�벹����ָͣ��
		{
			TGTHT510_1553b_inputcommand_dealing_supply_pause(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_BREAK://ע�벹����ָֹ��
		{
			TGTHT510_1553b_inputcommand_dealing_supply_break(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_CONTINUE://ע�벹�Ӽ���ָ��
		{
			TGTHT510_1553b_inputcommand_dealing_supply_continue(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_CPU_SET://ע��CPU״̬��λָ��
		{
			TGTHT510_1553b_inputcommand_dealing_cpu_set(a,start_i);
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_LEAK://ע���©����ָ��
		{
			TGTHT510_1553b_inputcommand_dealing_leak(a,start_i);
			
			break;	
		}
		
		case INPUT_COMMAND_TYPE_STAGE_FAULT://ע��׶ιʼ�״̬����
		{
			TGTHT510_1553b_inputcommand_dealing_stage_fault(a,start_i);			
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMPRESSOR_FLAG://ע��ѹ����ʹ�ñ�־������ָ��
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
**���ƣ�ע��ָ���EPDU����ʽ�Ƿ���ȷ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_is_correct(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i,uint16 length)
{
	uint16 i;
	uint16 data[50];//�����С���޸�
	uint16 checker;
	uint16 type;
	for(i=start_i;i<=start_i+length-1;i++)
	{
		data[i-start_i]=a.inputcommand_data[i];//����EPDU����
	}
	
	if((data[0]&0xff80)!=0x1b00)
	{
		return FALSE;//EPDU��ʶ�����
	}
	
	if(data[3]!=0x0404)
	{
		return FALSE;//EPDU���������ͣ����������ʹ���
	}
	
	
	checker=TGTHT510_1553b_receivecommand_buscommand_ISO_calculate(data,length-1);
	
	if(data[length-1]!=checker)
	{
		//return FALSE;//EPDU��ISOУ�����
	}
	
	return TRUE;
	
	
}

/******************************************************************************************
**���ƣ�ע��ָ���EPDU�����Ȼ�ȡ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_length_get(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 length;
	uint16 type;
	uint16 n;
	
	type=a.inputcommand_data[start_i+4];//ע��ָ������
	if(type==INPUT_COMMAND_TYPE_MULTI_CONTR_SPOT)//�޸Ķ�����»�·�Ŀ��µ�
	{
		n=a.inputcommand_data[start_i+8];
		length=n+10;
		
	}
		
	else
	{
		length=TGTHT510_1553b_receivecommand_inputcommand_EPDU_length_type_judge(type);
	}
	
	return length;//����EPDU��ȫ�����ȣ���λΪ��
	
}



/******************************************************************************************
**���ƣ�ע��ָ���EPDU�����ȼ���,ָ�������Ƿ�Ϸ��жϷֺ���
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_length_type_judge(uint16 type)
{
	uint16 length;
	switch(type)
	{
		case INPUT_COMMAND_TYPE_POWER://�޸ķ�ֵ����
		{
			length=INPUT_COMMAND_LEN_POWER;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ALL_CONTR_SPOT://�޸�ȫ�����»�·�Ŀ��µ�
		{
			length=INPUT_COMMAND_LEN_ALL_CONTR_SPOT;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ONE_MEA_SPOT://�޸�ĳһ���»�·�Ŀ��²��
		{
			length=INPUT_COMMAND_LEN_ONE_MEA_SPOT;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ONE_FIXED://ָ��ĳһ���»�·����ָ��ռ�ձ����
		{
			length=INPUT_COMMAND_LEN_ONE_FIXED;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_AUTO_RESUME://�ָ�ĳһ���»�·Ϊ�Զ�����״̬
		{
			length=INPUT_COMMAND_LEN_AUTO_RESUME;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_ALL_RESUME://�ָ����п��»�·����״̬
		{
			length=INPUT_COMMAND_LEN_ALL_RESUME;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SOURCE://ָ�����²�����Դѡ��
		{
			length=INPUT_COMMAND_LEN_SOURCE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_PLACE_SIGNAL_EN://ָ��ĳһ·���䵽λ�ź�ʹ��
		{
			length=INPUT_COMMAND_LEN_PLACE_SIGNAL_EN;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_PLACE_SIGNAL_DIS://ָ��ĳһ·���䵽λ�źŽ�ֹ
		{
			length=INPUT_COMMAND_LEN_PLACE_SIGNAL_DIS;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_FAULT_EN://ָ��ĳһ·�ʼ�ʹ��
		{
			length=INPUT_COMMAND_LEN_FAULT_EN;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_FAULT_DIS://ָ��ĳһ·�ʼ��ֹ
		{
			length=INPUT_COMMAND_LEN_FAULT_DIS;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_STAGE://���ӽ׶�ע��
		{
			length=INPUT_COMMAND_LEN_SUPPLY_STAGE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_PARA://���Ӳ���ע��
		{
			length=INPUT_COMMAND_LEN_SUPPLY_PARA;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EXHAUST://ע���©�����ŷ�ʱ��
		{
			length=INPUT_COMMAND_LEN_EXHAUST;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_COMP://ע��������ʱ��
		{
			length=INPUT_COMMAND_LEN_MAX_COMP;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_VELOCITY://ע����󲹼�����
		{
			length=INPUT_COMMAND_LEN_MAX_VELOCITY;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MIN_VELOCITY://ע����С��������
		{
			length=INPUT_COMMAND_LEN_MIN_VELOCITY;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_FLOW://ע����󲹼�����ʱ��
		{
			length=INPUT_COMMAND_LEN_MAX_FLOW;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_TEMP_CONTR_MODE://ע�벹�ӹ�·�¶ȿ���ģʽ
		{
			length=INPUT_COMMAND_LEN_TEMP_CONTR_MODE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_START_MIN://ע��ѹ���������¶�����
		{
			length=INPUT_COMMAND_LEN_COMP_START_MIN;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_START_MAX://ע��ѹ���������¶�����
		{
			length=INPUT_COMMAND_LEN_COMP_START_MAX;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_ALARM://ע��ѹ���������¶���ֵ
		{
			length=INPUT_COMMAND_LEN_COMP_ALARM;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COM_COOLER://ע��ѹ������Һ���¶Ȳ�ֵ
		{
			length=INPUT_COMMAND_LEN_COM_COOLER;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_PRESSURE://ע��ѹ������������ѹ��
		{
			length=INPUT_COMMAND_LEN_COMP_PRESSURE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_STOP_PRE://ע��ѹ����ͣ�������ѹ��ֵ
		{
			length=INPUT_COMMAND_LEN_COMP_STOP_PRE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DP_HIGH://ע���ѹѹ���仯��ֵ
		{
			length=INPUT_COMMAND_LEN_DP_HIGH;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DP1_LOW://ע���ѹѹ���仯��ֵ1
		{
			length=INPUT_COMMAND_LEN_DP1_LOW;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DP2_LOW://ע���ѹѹ���仯��ֵ2
		{
			length=INPUT_COMMAND_LEN_DP2_LOW;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_MAX_REPRESS://ע�����ѹʱ��
		{
			length=INPUT_COMMAND_LEN_MAX_REPRESS;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_START_SPEED://ע��ѹ��������ת��
		{
			length=INPUT_COMMAND_LEN_COMP_START_SPEED;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMP_STOP_SPEED://ע��ѹ����ͣ��ת��
		{
			length=INPUT_COMMAND_LEN_COMP_STOP_SPEED;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DELAY_SHORT://ע���޸Ķ���ʱ
		{
			length=INPUT_COMMAND_LEN_DELAY_SHORT;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_DELAY_LONG://ע���޸ĳ���ʱ
		{
			length=INPUT_COMMAND_LEN_DELAY_LONG;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_BYPATH_TIME://ע���޸���·������ʱ��
		{
			length=INPUT_COMMAND_LEN_BYPATH_TIME;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EPS1://ע���޸�ƫ��eps1
		{
			length=INPUT_COMMAND_LEN_EPS1;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EPS2://ע���޸�ƫ��eps2
		{
			length=INPUT_COMMAND_LEN_EPS2;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_IN_COMP_MAX://ע���޸�ѹ����������ѹ��
		{
			length=INPUT_COMMAND_LEN_IN_COMP_MAX;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_IN_COMP_MIN://ע���޸�ѹ������С����ѹ��
		{
			length=INPUT_COMMAND_LEN_IN_COMP_MIN;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_OUT_COMP_MIN://ע���޸�ѹ������С����ѹ��
		{
			length=INPUT_COMMAND_LEN_OUT_COMP_MIN;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_HYCT://ע���޸Ļ������ѹѹ��
		{
			length=INPUT_COMMAND_LEN_HYCT;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_PIPE_F://ע���޸�ȼ����Һ·ѹ���������趨
		{
			length=INPUT_COMMAND_LEN_SENSOR_PIPE_F;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_PIPE_O://ע���޸�������Һ·ѹ���������趨
		{
			length=INPUT_COMMAND_LEN_SENSOR_PIPE_O;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_TANK_F://ע���޸�ȼ����ѹ���������趨
		{
			length=INPUT_COMMAND_LEN_SENSOR_TANK_F;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_TANK_O://ע���޸�������ѹ���������趨
		{
			length=INPUT_COMMAND_LEN_SENSOR_TANK_O;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_IN_COMP://ע���޸�ѹ��������ѹ���������趨
		{
			length=INPUT_COMMAND_LEN_SENSOR_IN_COMP;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SENSOR_LOW_PIPE://ע���޸ĵ�ѹ��·ѹ���������趨
		{
			length=INPUT_COMMAND_LEN_SENSOR_LOW_PIPE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_CONTINUE_G://ע��ָ�����Ӳ����������
		{
			length=INPUT_COMMAND_LEN_SUPPLY_CONTINUE_G;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_EQU_COMMAND://ע���豸����ָ��
		{
			length=INPUT_COMMAND_LEN_EQU_COMMAND;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_HEAT_ON://ע�������ָͨ��
		{
			length=INPUT_COMMAND_LEN_HEAT_ON;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_PAUSE://ע�벹����ָͣ��
		{
			length=INPUT_COMMAND_LEN_SUPPLY_PAUSE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_BREAK://ע�벹����ָֹ��
		{
			length=INPUT_COMMAND_LEN_SUPPLY_BREAK;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_CONTINUE://ע�벹�Ӽ���ָ��
		{
			length=INPUT_COMMAND_LEN_SUPPLY_CONTINUE;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_CPU_SET://ע��CPU״̬��λָ��
		{
			length=INPUT_COMMAND_LEN_CPU_SET;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_SUPPLY_LEAK://ע���©����ָ��
		{
			length=INPUT_COMMAND_LEN_SUPPLY_LEAK;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_STAGE_FAULT://ע��׶ιʼ�״̬����
		{
			length=INPUT_COMMAND_LEN_STAGE_FAULT;
			break;	
		}
		
		case INPUT_COMMAND_TYPE_COMPRESSOR_FLAG://ע��ѹ����ʹ�ñ�־������ָ��
		{
			length=INPUT_COMMAND_LEN_COMPRESSOR_FLAG;
			break;	
		}
		
		
		default:
		{
			length=INPUT_COMMAND_LEN_UNKNOW;//ע��ָ�����ͷǷ�
			break;
		}

	}
	
	return length;

}

/******************************************************************************************
**���ƣ�ע��ָ�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_receivecommand_inputcommand_dealing(TGTHT510_1553B_inputcommand_TypeDef a)
{
	uint16 i;
	uint16 EPDU_num;//EPDUң�ذ���������
	uint16 EPDU_result;
	uint16 temp;
	
	EPDU_num=a.inputcommand_data[0];//EPDUң�ذ���������
	
	if(EPDU_num==0)
	{
		CG_inputcommand_receive_state_data[0]=INPUT_COMMAND_EPDU_NUM_ERROR;
		CG_inputcommand_receive_state_data[1]=INPUT_COMMAND_EPDU_NUM_ERROR;//Դ�������������󣬳���ң�⴫��AAAAH
		
		return;//Դ���������������˳�����
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
			CG_inputcommand_receive_state_data[1]=INPUT_COMMAND_EPDU_DEAL_ERROR;//EPDU�������������ң�⴫��BBBBH
			return;//EPDU����������˳�������
		}
		
		temp=EPDU_result&0x3fff;
		
		TGTHT510_1553b_receivecommand_inputcommand_state_data(a,i,temp);//����ң�⴫�����һ��ע��EPDU��ָ��������У���
		
		i=i+temp;

	}

}


/******************************************************************************************
**���ƣ�����ע��ָ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_receivecommand_inputcommand(uint16 which_bu65170)
{
	TGTHT510_1553B_inputcommand_TypeDef inputcommand;
	uint16 correct;
	
	inputcommand=TGTHT510_1553b_receivecommand_inputcommand_save(which_bu65170);//��������ָ���������ṹ��������
	
	correct=TGTHT510_1553b_receivecommand_inputcommand_is_correct(inputcommand);//�ж�ע��ָ���ʽ�Ƿ���ȷ
	
	if(correct==FALSE)
	{
		return;//ע��ָ���ʽ�����˳�ע��ָ�����
	}
	
	TGTHT510_1553b_receivecommand_inputcommand_dealing(inputcommand);//ע��ָ���
	
}

/******************************************************************************************
**���ƣ����ջ�������״̬��Ϣ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������

-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ���������ң��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ���������ָ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
		
		if(temp[0]==0x1515)//�ڴ��´��ӵ�ַ
		{
			TGTHT510_1553b_transmitdata_MEMORY(which_bu65170);
			
			
		}
		
		
	}
	
}


/******************************************************************************************
**���ƣ�����ָ��̵�������������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_relay_dealing(uint16 code)
{
	uint16 reg;
	
	reg=0x5555;
	
	
	switch(code)
	{
		case BUS_MAIN_HEATER_POWER_ON://�ƽ����ݼ���������ͨ
		{
			reg=(reg&BUS_MAIN_HEATER_POWER_ON_AND)|BUS_MAIN_HEATER_POWER_ON_OR;
			
			*(volatile uint32 *)(BUS_RELAY_HEATER_ON_BASE_ADDRESS)=Write_16_to_32(reg);
			
			return;
			
			break;
		}
		
		case BUS_MAIN_HEATER_POWER_OFF://�ƽ����ݼ����������
		{
			reg=(reg&BUS_MAIN_HEATER_POWER_OFF_AND)|BUS_MAIN_HEATER_POWER_OFF_OR;
			break;
		}
		
		case BUS_LESS_HEATER_POWER_ON://�ƽ����ݼ���������ͨ
		{
			reg=(reg&BUS_LESS_HEATER_POWER_ON_AND)|BUS_LESS_HEATER_POWER_ON_OR;
			
			*(volatile uint32 *)(BUS_RELAY_HEATER_ON_BASE_ADDRESS)=Write_16_to_32(reg);
			
			return;
			
			break;
		}
		
		case BUS_LESS_HEATER_POWER_OFF://�ƽ����ݼ����������
		{
			reg=(reg&BUS_LESS_HEATER_POWER_OFF_AND)|BUS_LESS_HEATER_POWER_OFF_OR;
			break;
		}
		
		case BUS_COOLER_1_MAIN_POWER_ON://Һ��ģ��I���ù���ͨ
		{
			reg=(reg&BUS_COOLER_1_MAIN_POWER_ON_AND)|BUS_COOLER_1_MAIN_POWER_ON_OR;
			break;
		}
		
		case BUS_COOLER_1_LESS_POWER_ON://Һ��ģ��I���ù���ͨ
		{
			reg=(reg&BUS_COOLER_1_LESS_POWER_ON_AND)|BUS_COOLER_1_LESS_POWER_ON_OR;
			break;
		}
		
		case BUS_COOLER_1_POWER_OFF://Һ��ģ��I�������ù����
		{
			reg=(reg&BUS_COOLER_1_POWER_OFF_AND)|BUS_COOLER_1_POWER_OFF_OR;
			break;
		}
		
		case BUS_COOLER_2_MAIN_POWER_ON://Һ��ģ��II���ù���ͨ
		{
			reg=(reg&BUS_COOLER_2_MAIN_POWER_ON_AND)|BUS_COOLER_2_MAIN_POWER_ON_OR;
			break;
		}
		
		case BUS_COOLER_2_LESS_POWER_ON://Һ��ģ��II���ù���ͨ
		{
			reg=(reg&BUS_COOLER_2_LESS_POWER_ON_AND)|BUS_COOLER_2_LESS_POWER_ON_OR;
			break;
		}
		
		case BUS_COOLER_2_POWER_OFF://Һ��ģ��II�������ù����
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
**���ƣ�ע��ָ��������޸ķ�ֵ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_power(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	Temperature_control_global.total_power=a.inputcommand_data[start_i+5];
}

/******************************************************************************************
**���ƣ�ע��ָ��������޸Ķ�����»�·�Ŀ��µ�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_multi_contr_spot(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 t1,t2,t3;
	uint16 n;
	uint16 i;
	uint16 xx;
	
	t1=a.inputcommand_data[start_i+5];//���µ�T1
	t2=a.inputcommand_data[start_i+6];//���µ�T2
	t3=a.inputcommand_data[start_i+7];//���µ�T3
	
	if((t1>t2)&&(t2>t3))//��T1�¶ȵ���T2�¶ȣ�T2�¶ȵ���T3�¶�
	{
		asm("nop;");
	}
	
	else
	{
		return;
	}
	
	n=a.inputcommand_data[start_i+8];//��Ҫ�޸ĵĿ��»�·��·��
	
	if((n==0)||(n>50))//���»�·��·��ֵ�Ƿ�
	{
		return;
	}
	
	for(i=0;i<=n-1;i++)
	{
		if(a.inputcommand_data[start_i+9+i]>49)//���»�·��·�ŷǷ�
		{
			return;
		}
		
		else
		{
			asm("nop;");
		}
	}
	
	for(i=0;i<=n-1;i++)//���¿��µ�T1��T2��T3
	{
		xx=a.inputcommand_data[start_i+9+i];
		Temperature_control_block[xx].control_spot[0]=t1;
		Temperature_control_block[xx].control_spot[1]=t2;
		Temperature_control_block[xx].control_spot[2]=t3;
	}

}


/******************************************************************************************
**���ƣ�ע��ָ��������޸�ȫ�����»�·�Ŀ��µ�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_all_contr_spot(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 t1,t2,t3;
	uint16 i;
	
	t1=a.inputcommand_data[start_i+5];//���µ�T1
	t2=a.inputcommand_data[start_i+6];//���µ�T2
	t3=a.inputcommand_data[start_i+7];//���µ�T3
	
	if((t1>t2)&&(t2>t3))//��T1�¶ȵ���T2�¶ȣ�T2�¶ȵ���T3�¶�
	{
		asm("nop;");
	}
	
	else
	{
		return;
	}
	
	for(i=0;i<=49;i++)//���¿��µ�T1��T2��T3
	{
		Temperature_control_block[i].control_spot[0]=t1;
		Temperature_control_block[i].control_spot[1]=t2;
		Temperature_control_block[i].control_spot[2]=t3;
	}

}


/******************************************************************************************
**���ƣ�ע��ָ��������޸�ĳһ���»�·�Ŀ��²��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_one_mea_spot(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 n;			//�޸ĵĿ��»�·��·��
	uint16 temp[7];		//���²��Ĵ���
	uint16 i;
	
	n=a.inputcommand_data[start_i+5];
	
	if(n>50)			//���»�·��·��ֵ�Ƿ�
	{
		return;
	}
	
	for(i=0;i<=6;i++)
	{
		temp[i]=a.inputcommand_data[start_i+6+i];//������
		
		if(temp[i]!=0xffff)
		{
			//Bit15~14Ϊ00��ʾ����¶ȴ�����ΪMF51��Ϊ01��ʾ����¶ȴ�����Ϊ�����裬Ϊ10��ʾ����¶ȴ�����ΪMF61
			if((temp[i]&0xc000)==0xc000)
			{
				return;
			}
			
			//Bit13~12Ϊ01��ʾ�ò���¶�ֵλ�ڸ�֡A֡��Ϊ10��ʾ�ò���¶�ֵλ�ڸ�֡B֡��
			if(((temp[i]&0x3000)==0x3000)||((temp[i]&0x3000)==0x0000))
			{
				return;
			}
			
			//Bit11~10Ϊ00��ʾ��ң��֡��Ϊ�֣�16λ����ʾ��Ϊ01��ʾ��ң��֡��Ϊ���ֽڣ�8λ����ʾ��Ϊ10��ʾ��ң��֡��Ϊ���ֽڣ�8λ����ʾ��
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
	
	
	for(i=0;i<=6;i++)//���¿��²��
	{
		Temperature_control_block[n].source_data[i]=temp[i];
	}
	
	

}


/******************************************************************************************
**���ƣ�ע��ָ�������ָ��ĳһ���»�·����ָ��ռ�ձ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_one_fixed(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 n;				//�޸ĵĿ��»�·��·��
	uint16 fixed_count;		//ռ�ձ�����
	
	n=a.inputcommand_data[start_i+5];
	
	if(n>50)			//���»�·��·��ֵ�Ƿ�
	{
		return;
	}
	
	fixed_count=a.inputcommand_data[start_i+6];
	
	if(fixed_count==0x0000)//������Ϊ�㣬�򱾴�ע����Ч
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
**���ƣ�ע��ָ��������ָ�ĳһ���»�·Ϊ�Զ�����ģʽ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_inputcommand_dealing_auto_resume(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 n;				//�޸ĵĿ��»�·��·��
	
	n=a.inputcommand_data[start_i+5];
	
	if(n>50)			//���»�·��·��ֵ�Ƿ�
	{
		return;
	}
	
	Temperature_control_block[n].fixed_output_state=DISABLE;
		
	Temperature_control_block[n].fixed_output_count=0x0000;
	
}


/******************************************************************************************
**���ƣ�ע��ָ��������ָ����п��»�·����״̬
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�ע��ָ�������ָ�����²�����Դѡ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
	
void TGTHT510_1553b_inputcommand_dealing_source(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0xe5e5)
	{
		//����ʹ��ң��������Դ���ƽ�ң����·��
		Temperature_control_global.source=SOURCE_DATA_TGTHT100;

	}
	
	else if(temp==0xc5c5)
	{
		//����ʹ��ң��������Դ������KPU
		Temperature_control_global.source=SOURCE_DATA_KPU;
	}
	
	else
	{
		asm("nop;");
	}

}



/******************************************************************************************
**���ƣ�ע��ָ�������ָ��ĳһ·���䵽λ�ź�ʹ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�ע��ָ�������ָ��ĳһ·���䵽λ�źŽ�ֹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�ע��ָ�������ָ��ĳһ·�ʼ�ʹ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_fault_en(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	TGTHT510_faultdiagnosis_enable_disable_set(temp,ENABLE);

}


/******************************************************************************************
**���ƣ�ע��ָ�������ָ��ĳһ·�ʼ��ֹ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_fault_dis(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	TGTHT510_faultdiagnosis_enable_disable_set(temp,DISABLE);

}



/******************************************************************************************
**���ƣ�ע��ָ����������ӽ׶�ע��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_supply_stage(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0x0000)//���ӿ��н׶�
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
**���ƣ�ע��ָ����������Ӳ���ע��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_supply_para(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	
	temp=a.inputcommand_data[start_i+5];
	
	TGTHT510_supply_input_par.interface_F=(uint8)(temp>>8);//ȼ���ӽӿ�
	TGTHT510_supply_input_par.interface_O=(uint8)(temp>>0);//�����ӽӿ�
	
	temp=a.inputcommand_data[start_i+6];
	
	TGTHT510_supply_input_par.sequence_tank_F=(uint8)(temp>>8);//ȼ���䲹��˳��
	TGTHT510_supply_input_par.sequence_tank_O=(uint8)(temp>>0);//�����䲹��˳��
	
	temp=a.inputcommand_data[start_i+7];
	
	TGTHT510_supply_input_par.sequence_gas_F1=(uint8)(temp>>8);//ȼ����F1��ƿ����˳��
	TGTHT510_supply_input_par.sequence_gas_F2=(uint8)(temp>>0);//ȼ����F2��ƿ����˳��
	
	temp=a.inputcommand_data[start_i+8];
	
	TGTHT510_supply_input_par.sequence_gas_F3=(uint8)(temp>>8);//ȼ����F3��ƿ����˳��
	TGTHT510_supply_input_par.sequence_gas_O1=(uint8)(temp>>0);//������O1��ƿ����˳��
	
	temp=a.inputcommand_data[start_i+9];
	
	TGTHT510_supply_input_par.sequence_gas_O2=(uint8)(temp>>8);//������O2��ƿ����˳��
	TGTHT510_supply_input_par.sequence_gas_O3=(uint8)(temp>>0);//������O3��ƿ����˳��
	
	temp=a.inputcommand_data[start_i+10];
	
	TGTHT510_supply_input_par.compressor_out_valve=temp;//����ѹ�����ţ��뿪����ѹ�������ڷ���
	
	temp=a.inputcommand_data[start_i+11];
	
	TGTHT510_supply_input_par.pressure_first_F1=temp;//ȼ����F1��һ����������ĩѹ
	
	temp=a.inputcommand_data[start_i+12];
	
	TGTHT510_supply_input_par.pressure_second_F1=temp;//ȼ����F1�ڶ�����������ĩѹ
	
	temp=a.inputcommand_data[start_i+13];
	
	TGTHT510_supply_input_par.pressure_first_F2=temp;//ȼ����F2��һ����������ĩѹ
	
	temp=a.inputcommand_data[start_i+14];
	
	TGTHT510_supply_input_par.pressure_second_F2=temp;//ȼ����F2�ڶ�����������ĩѹ
	
	temp=a.inputcommand_data[start_i+15];
	
	TGTHT510_supply_input_par.pressure_first_F3=temp;//ȼ����F3��һ����������ĩѹ
	
	temp=a.inputcommand_data[start_i+16];
	
	TGTHT510_supply_input_par.pressure_second_F3=temp;//ȼ����F3�ڶ�����������ĩѹ
	
	temp=a.inputcommand_data[start_i+17];
	
	TGTHT510_supply_input_par.pressure_first_O1=temp;//������O1��һ����������ĩѹ
	
	temp=a.inputcommand_data[start_i+18];
	
	TGTHT510_supply_input_par.pressure_second_O1=temp;//������O1�ڶ�����������ĩѹ
	
	temp=a.inputcommand_data[start_i+19];
	
	TGTHT510_supply_input_par.pressure_first_O2=temp;//������O2��һ����������ĩѹ
	
	temp=a.inputcommand_data[start_i+20];
	
	TGTHT510_supply_input_par.pressure_second_O2=temp;//������O2�ڶ�����������ĩѹ
	
	temp=a.inputcommand_data[start_i+21];
	
	TGTHT510_supply_input_par.pressure_first_O3=temp;//������O3��һ����������ĩѹ
	
	temp=a.inputcommand_data[start_i+22];
	
	TGTHT510_supply_input_par.pressure_second_O3=temp;//������O3�ڶ�����������ĩѹ
	
	temp=a.inputcommand_data[start_i+23];
	
	TGTHT510_supply_input_par.pump_cooler=temp;//ʹ�õ�Һ��ģ��ú�
	
	temp=a.inputcommand_data[start_i+24];
	
	TGTHT510_supply_input_par.volum_F1=temp;//ȼ����F1���ӵ�λʣ����
	
	temp=a.inputcommand_data[start_i+25];
	
	TGTHT510_supply_input_par.volum_F2=temp;//ȼ����F2���ӵ�λʣ����
	
	temp=a.inputcommand_data[start_i+26];
	
	TGTHT510_supply_input_par.volum_F3=temp;//ȼ����F3���ӵ�λʣ����
	
	temp=a.inputcommand_data[start_i+27];
	
	TGTHT510_supply_input_par.volum_O1=temp;//������O1���ӵ�λʣ����
	
	temp=a.inputcommand_data[start_i+28];
	
	TGTHT510_supply_input_par.volum_O2=temp;//������O2���ӵ�λʣ����
	
	temp=a.inputcommand_data[start_i+29];
	
	TGTHT510_supply_input_par.volum_O3=temp;//������O3���ӵ�λʣ����
	
	temp=a.inputcommand_data[start_i+30];
	
	TGTHT510_supply_input_par.mode=temp;//����ģʽ
	
	temp=a.inputcommand_data[start_i+31];
	
	TGTHT510_supply_input_par.pressure_repre_F1=temp;//ȼ����F1��ѹѹ��ֵ
	
	temp=a.inputcommand_data[start_i+32];
	
	TGTHT510_supply_input_par.pressure_repre_F2=temp;//ȼ����F2��ѹѹ��ֵ
	
	temp=a.inputcommand_data[start_i+33];
	
	TGTHT510_supply_input_par.pressure_repre_F3=temp;//ȼ����F3��ѹѹ��ֵ
	
	temp=a.inputcommand_data[start_i+34];
	
	TGTHT510_supply_input_par.pressure_repre_O1=temp;//������O1��ѹѹ��ֵ
	
	temp=a.inputcommand_data[start_i+35];
	
	TGTHT510_supply_input_par.pressure_repre_O2=temp;//������O2��ѹѹ��ֵ
	
	temp=a.inputcommand_data[start_i+36];
	
	TGTHT510_supply_input_par.pressure_repre_O3=temp;//������O3��ѹѹ��ֵ
	
	TGTHT510_supply_ctrl.receive=TRUE;
	
	
}


/******************************************************************************************
**���ƣ�ע��ָ�������ע���©�����ŷ�ʱ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_exhaust(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	TGTHT510_supply_input_par.time_exhaust=(uint32)(temp);

}



/******************************************************************************************
**���ƣ�ע��ָ�������ע��������ʱ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_max_comp(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp1,temp2;
	
	temp1=a.inputcommand_data[start_i+5];
	
	temp2=a.inputcommand_data[start_i+6];
	
	TGTHT510_supply_input_par.time_comp_max=(((uint32)(temp1))<<16)|((uint32)(temp2));

}


/******************************************************************************************
**���ƣ�ע��ָ�������ע����󲹼�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_max_velocity(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.velocity_max=a.inputcommand_data[start_i+5];

}



/******************************************************************************************
**���ƣ�ע��ָ�������ע����С��������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_min_velocity(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.velocity_min=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע����󲹼�����ʱ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_max_flow(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.time_flow_max=a.inputcommand_data[start_i+5];

}



/******************************************************************************************
**���ƣ�ע��ָ�������ע�벹�ӹ�·�¶ȿ���ģʽ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_temp_contr_mode(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	

}


/******************************************************************************************
**���ƣ�ע��ָ�������ע��ѹ���������¶�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_start_min(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.temperature_start_min=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**���ƣ�ע��ָ�������ע��ѹ���������¶�����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_start_max(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.temperature_start_max=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**���ƣ�ע��ָ�������ע��ѹ���������¶���ֵ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_alarm(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.temperature_alarm=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע��ѹ������Һ���¶Ȳ�ֵ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_cooler(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.temperature_comp_cooler=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע��ѹ������������ѹ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_pressure(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.pressure_comp_out=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע��ѹ����ͣ�������ѹ��ֵ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_stop_pre(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.pressure_comp_out_stop=a.inputcommand_data[start_i+5];

}



/******************************************************************************************
**���ƣ�ע��ָ�������ע���ѹѹ���仯��ֵ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_dp_high(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.dp_high=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**���ƣ�ע��ָ�������ע���ѹѹ���仯��ֵ1
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_dp1_low(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.dp1_low=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**���ƣ�ע��ָ�������ע���ѹѹ���仯��ֵ2
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_dp2_low(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.dp2_low=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**���ƣ�ע��ָ�������ע�����ѹʱ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_max_repress(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp1,temp2;
	
	temp1=a.inputcommand_data[start_i+5];
	
	temp2=a.inputcommand_data[start_i+6];
	
	TGTHT510_supply_input_par.time_repre_max=(((uint32)(temp1))<<16)|((uint32)(temp2));

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע��ѹ��������ת��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_start_speed(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.v_comp_start=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**���ƣ�ע��ָ�������ע��ѹ����ͣ��ת��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_comp_stop_speed(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.v_comp_stop=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸Ķ���ʱ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_delay_short(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.time_delay_short=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸ĳ���ʱ
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_delay_long(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.time_delay_long=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸���·������ʱ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_time_bypath(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.time_bypath=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸�ƫ��1
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_eps1(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.eps1=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸�ƫ��2
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_eps2(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.eps2=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸�ѹ����������ѹ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_pressure_comp_in_max(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.pressure_comp_in_max=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸�ѹ������С����ѹ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_pressure_comp_in_min(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.pressure_comp_in_min=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸�ѹ������С����ѹ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_pressure_comp_out_min(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.pressure_comp_out_min=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸Ļ��˷ɴ����ѹѹ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_pressure_hyc(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.pressure_hyc=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸�ȼ����Һ·ѹ���������趨
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_sensor_pipe_F(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.sensor_pipe_F=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸�������Һ·ѹ���������趨
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_sensor_pipe_O(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.sensor_pipe_O=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸�ȼ����ѹ���������趨
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_sensor_tank_F(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.sensor_tank_F=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸�������ѹ���������趨
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_sensor_tank_O(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.sensor_tank_O=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸�ѹ��������ѹ���������趨
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_sensor_comp_in(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.sensor_comp_in=a.inputcommand_data[start_i+5];

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���޸ĵ�ѹ��·ѹ���������趨
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_sensor_pipe_low(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	TGTHT510_supply_input_par.sensor_pipe_low=a.inputcommand_data[start_i+5];

}


/******************************************************************************************
**���ƣ�ע��ָ�������ָ�����Ӳ����������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�ע���豸����ָ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�ע���������ָ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�ע��ָ�������ע�벹����ָͣ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�ע��ָ�������ע�벹����ָֹ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�ע��ָ�������ע�벹����ָͣ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�ע��ָ�������ע�벹����ָͣ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_1553b_inputcommand_dealing_cpu_set(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0xaa22)//��A��Ϊ��ȷ
	{
		CPU_ON();
	}
	
	else if(temp==0xaa44)//��A��Ϊ����
	{
		CPU_OFF();
		
	}
	
	else if(temp==0xbb22)//��B��Ϊ��ȷ
	{
		
		
	}
	
	else if(temp==0xbb44)//��B��Ϊ����
	{
		
		
	}
	
	else
	{
		asm("nop;");
	}

}

/******************************************************************************************
**���ƣ�ע��ָ�������ע���©����ָ��
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
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
**���ƣ�ע��ָ�������ע��׶ιʼ�״̬����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_inputcommand_dealing_stage_fault(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	switch(temp)
	{
		case 0x0101://����ιʼ�
		{
			TGTHT510_faultdiagnosis_push_set_stage_launch();
			TGTHT510_faultdiagnosis_supply_set_stage_launch();
			break;
		}
		
		case 0x0202://���ιʼ�
		{
			TGTHT510_faultdiagnosis_push_set_stage_orbit();
			TGTHT510_faultdiagnosis_supply_set_stage_orbit();
			break;
		}
		
		case 0x0303://Ѳ��ιʼ�
		{
			TGTHT510_faultdiagnosis_push_set_stage_polling();
			TGTHT510_faultdiagnosis_supply_set_stage_polling();
			break;
		}
		
		case 0x0404://ѹ���������ιʼ�
		{
			TGTHT510_faultdiagnosis_push_set_stage_gas();
			TGTHT510_faultdiagnosis_supply_set_stage_gas();
			break;
		}
		
		case 0x0505://���ӳ����ιʼ�
		{
			TGTHT510_faultdiagnosis_push_set_stage_comp();
			TGTHT510_faultdiagnosis_supply_set_stage_comp();
			break;
		}
		
		case 0x0606://���������ιʼ�
		{
			TGTHT510_faultdiagnosis_push_set_stage_flow();
			TGTHT510_faultdiagnosis_supply_set_stage_flow();
			break;
		}
		
		case 0x0707://���Ӹ�ѹ�ιʼ�
		{
			TGTHT510_faultdiagnosis_push_set_stage_repre();
			TGTHT510_faultdiagnosis_supply_set_stage_repre();
			break;
		}
		
		case 0x0808://���������ιʼ�
		{
			TGTHT510_faultdiagnosis_push_set_stage_other();
			TGTHT510_faultdiagnosis_supply_set_stage_other();
			break;
		}
		
		case 0x0909://���жιʼ�
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
**���ƣ�ע��ָ�������ע��״̬����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_1553b_inputcommand_dealing_compressor_flag_set(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i)
{
	uint16 temp;
	
	temp=a.inputcommand_data[start_i+5];
	
	if(temp==0x0a0a)//���õ�ǰʹ�õ�ѹ����ΪA��
	{
		compressor_state.compressor_A_state=COMPRESSOR_RUN;
		compressor_state.compressor_B_state=COMPRESSOR_STOP;
		compressor_state.compressor_C_state=COMPRESSOR_STOP;
	
		TGTHT510_supply_decode_par.compressor_F=DECODE_NONE;
		TGTHT510_supply_decode_par.compressor_O=DECODE_NONE;
		
		
	}
	
	else if(temp==0x0b0b)//���õ�ǰʹ�õ�ѹ����ΪB��
	{
		compressor_state.compressor_A_state=COMPRESSOR_STOP;
		compressor_state.compressor_B_state=COMPRESSOR_RUN;
		compressor_state.compressor_C_state=COMPRESSOR_STOP;
	
		TGTHT510_supply_decode_par.compressor_F=DECODE_NONE;
		TGTHT510_supply_decode_par.compressor_O=DECODE_NONE;
		
	}
	
	else if(temp==0x0c01)//���õ�ǰʹ�õ�ѹ����ΪC������Ϊ��·
	{
		compressor_state.compressor_A_state=COMPRESSOR_STOP;
		compressor_state.compressor_B_state=COMPRESSOR_STOP;
		compressor_state.compressor_C_state=COMPRESSOR_RUN;
	
		TGTHT510_supply_decode_par.compressor_F=DECODE_NONE;
		TGTHT510_supply_decode_par.compressor_O=DECODE_COMPRESSOR_C;
		
	}
	
	else if(temp==0x0c02)//���õ�ǰʹ�õ�ѹ����ΪC������Ϊȼ·
	{
		compressor_state.compressor_A_state=COMPRESSOR_STOP;
		compressor_state.compressor_B_state=COMPRESSOR_STOP;
		compressor_state.compressor_C_state=COMPRESSOR_RUN;
	
		TGTHT510_supply_decode_par.compressor_F=DECODE_COMPRESSOR_C;
		TGTHT510_supply_decode_par.compressor_O=DECODE_NONE;
		
	}
	
	else if(temp==0x0202)//��ǰʹ�õ���·���ӽӿ�ΪO1
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O1;
		
	}
	
	else if(temp==0x0303)//��ǰʹ�õ���·���ӽӿ�ΪO2
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O2;
		
	}
	
	else if(temp==0x0404)//��ǰʹ�õ���·���ӽӿ�ΪO3
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O3;
		
	}
	
	else if(temp==0x0505)//��ǰʹ�õ���·���ӽӿ�ΪO4
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O4;
		
	}
	
	else if(temp==0x0606)//��ǰʹ�õ�ȼ·���ӽӿ�ΪF1
	{
		
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R1;
		
	}
	
	else if(temp==0x0707)//��ǰʹ�õ�ȼ·���ӽӿ�ΪF2
	{
		
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R2;
		
	}
	
	else if(temp==0x0808)//��ǰʹ�õ�ȼ·���ӽӿ�ΪF3
	{
		
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R3;
		
	}
	
	else if(temp==0x0909)//��ǰʹ�õ�ȼ·���ӽӿ�ΪF4
	{
		
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R4;
		
	}
	
	else
	{
		asm("nop;");
	}
	
}












 
