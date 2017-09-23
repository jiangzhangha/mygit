/**
  ******************************************************************************
  * @file    TGTHT510_supply.c
  * @author  ����
  * @version V1.00
  * @date    20150626
  * @brief   �ռ�վ���Ĳ��ƽ�����������ģ��C�ļ�
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"


/*ȫ�ֱ���---------------------------------------------------------------------*/		

extern TGTHT510_supply_ctrl_TypeDef TGTHT510_supply_ctrl;

extern TGTHT510_supply_input_par_TypeDef TGTHT510_supply_input_par;

extern TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;



/******************************************************************************************
**���ƣ����ӽ׶�1��ע�����������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_supply_stage01_input_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://��ʼ
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_01_IS_INPUT;
			break;
		}
		
		case STEP_01_IS_INPUT://�Ƿ���ܵ����Ӳ���
		{
			if(TGTHT510_supply_ctrl.receive==TRUE)//ע��������ܽ���
			{
				TGTHT510_supply_ctrl.receive=FALSE;
				
				if(TGTHT510_supply_stage01_input_decode()==TRUE)
				{
					TGTHT510_supply_ctrl.step=STEP_END;
				}
				
				else
				{
					TGTHT510_supply_stage01_input_clear();
					
					TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
					//������󣡣�������ͣ��������������
				}
				
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://����
		{
			TGTHT510_supply_ctrl.state=STATE_NONE;//����״̬������
			
			TGTHT510_supply_ctrl.stage=STAGE_00_NONE;//���ӽ׶Σ���
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//���Ӳ��裺��
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//����ָ���
			
			TGTHT510_supply_time_stage_end();
			
			break;
		}
		
		default:
		{
			break;
		}

	}	
	
}

/******************************************************************************************
**���ƣ����ӽ׶�1��ע�����������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_supply_stage01_input_clear(void)
{
	TGTHT510_supply_decode_par.interface_F=DECODE_NONE;
	TGTHT510_supply_decode_par.interface_O=DECODE_NONE;
	TGTHT510_supply_decode_par.number_tank_F=DECODE_NONE;
	TGTHT510_supply_decode_par.first_tank_F=DECODE_NONE;
	TGTHT510_supply_decode_par.second_tank_F=DECODE_NONE;
	TGTHT510_supply_decode_par.third_tank_F=DECODE_NONE;
	TGTHT510_supply_decode_par.number_tank_O=DECODE_NONE;
	TGTHT510_supply_decode_par.first_tank_O=DECODE_NONE;
	TGTHT510_supply_decode_par.second_tank_O=DECODE_NONE;
	TGTHT510_supply_decode_par.third_tank_O=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_F1=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_F1=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_F2=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_F2=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_F3=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_F3=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_O1=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_O1=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_O2=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_O2=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_O3=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_O3=DECODE_NONE;
	TGTHT510_supply_decode_par.compressor_F=DECODE_NONE;
	TGTHT510_supply_decode_par.compressor_O=DECODE_NONE;
	TGTHT510_supply_decode_par.valve_out_compressor_F=DECODE_NONE;
	TGTHT510_supply_decode_par.valve_out_compressor_O=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_F1=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_F2=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_F3=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_O1=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_O2=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_O3=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_pipe_low_F=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_pipe_low_O=DECODE_NONE;
	TGTHT510_supply_decode_par.cooler=DECODE_NONE;
}



/******************************************************************************************
**���ƣ�
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������������ȷ������TRUE������ΪFALSE

**************************************ע�벹�Ӳ������仯������****************************

1��ȼ���ӽӿڣ�1�ֽڣ���
0x03�Ǻ�����R1��
0x0c�Ǻ���R2��
0x30��ǰ����R3��
0xc0��ǰ��R4��

2�������ӽӿڣ�1�ֽڣ���
0x03�Ǻ�����O1��
0x0c�Ǻ���O2��
0x30��ǰ����O3��
0xc0��ǰ��O4��

3��ȼ���䲹��˳��1�ֽڣ�:
bit0��1Ϊ��һ���������ţ�
bit2��3Ϊ�ڶ����������ţ�
bit4��5Ϊ�������������ţ�
bit6��7Ϊ����ȼ�����������
01��ʾȼ����F1
10��ʾȼ����F2
11��ʾȼ����F3
00��ʾ������

4�������䲹��˳��1�ֽڣ�:
bit0��1Ϊ��һ���������ţ�
bit2��3Ϊ�ڶ����������ţ�
bit4��5Ϊ�������������ţ�
bit6��7Ϊ�����������������
01��ʾ������O1
10��ʾ������O2
11��ʾ������O3
00��ʾ������


5��ȼ����F1����ƿ����˳��1�ֽڣ�
bit0��1Ϊ��һ��������ƿ����ţ�
bit2��3Ϊ�ڶ���������ƿ����ţ�
bit4��5Ϊ��
bit7��8Ϊ��������ƿ����
01��ʾȼ��ƿF1
10��ʾȼ��ƿF2
11��ʾȼ��ƿF3
00��ʾ����ƿ

6��ȼ����F2����ƿ����˳��1�ֽڣ�
bit0��1Ϊ��һ��������ƿ����ţ�
bit2��3Ϊ�ڶ���������ƿ����ţ�
bit4��5Ϊ��
bit7��8Ϊ��������ƿ����
01��ʾȼ��ƿF1
10��ʾȼ��ƿF2
11��ʾȼ��ƿF3
00��ʾ����ƿ

7��ȼ����F3����ƿ����˳��1�ֽڣ�
bit0��1Ϊ��һ��������ƿ����ţ�
bit2��3Ϊ�ڶ���������ƿ����ţ�
bit4��5Ϊ��
bit7��8Ϊ��������ƿ����
01��ʾȼ��ƿF1
10��ʾȼ��ƿF2
11��ʾȼ��ƿF3
00��ʾ����ƿ

8��������O1����ƿ����˳��1�ֽڣ�
bit0��1Ϊ��һ��������ƿ����ţ�
bit2��3Ϊ�ڶ���������ƿ����ţ�
bit4��5Ϊ��
bit7��8Ϊ��������ƿ����
01��ʾ����ƿO1
10��ʾ����ƿO2
11��ʾ����ƿO3
00��ʾ����ƿ

9��������O2����ƿ����˳��1�ֽڣ�
bit0��1Ϊ��һ��������ƿ����ţ�
bit2��3Ϊ�ڶ���������ƿ����ţ�
bit4��5Ϊ��
bit7��8Ϊ��������ƿ����
01��ʾ����ƿO1
10��ʾ����ƿO2
11��ʾ����ƿO3
00��ʾ����ƿ

10��������O3����ƿ����˳��1�ֽڣ�
bit0��1Ϊ��һ��������ƿ����ţ�
bit2��3Ϊ�ڶ���������ƿ����ţ�
bit4��5Ϊ��
bit7��8Ϊ��������ƿ����
01��ʾ����ƿO1
10��ʾ����ƿO2
11��ʾ����ƿO3
00��ʾ����ƿ

11��ȼ������ѹ����������ڷ��ţ�2�ֽڣ�
bit0��1Ϊ01��ʾȼ����ѹ����ΪB����Ϊ10��ʾȼ����ѹ����ΪC��
bit2��3Ϊ01��ʾ������ȼѹ�������ڷ���Ϊ����10��ʾ������ȼѹ�������ڷ���Ϊ��
bit4��5Ϊ01��ʾ������ѹ����ΪA����Ϊ10��ʾ������ѹ����ΪC��
bit6��7Ϊ01��ʾ��������ѹ�������ڷ���Ϊ����10��ʾ��������ѹ�������ڷ���Ϊ��
bit8-15Ϊ��

12��ȼ����F1��һ����ƿ�ĳ�����ĩѹֵ��2�ֽڣ�

13��ȼ����F1�ڶ�����ƿ�ĳ�����ĩѹֵ��2�ֽڣ�

14��ȼ����F2��һ����ƿ�ĳ�����ĩѹֵ��2�ֽڣ�

15��ȼ����F2�ڶ�����ƿ�ĳ�����ĩѹֵ��2�ֽڣ�

16��ȼ����F3��һ����ƿ�ĳ�����ĩѹֵ��2�ֽڣ�

17��ȼ����F3�ڶ�����ƿ�ĳ�����ĩѹֵ��2�ֽڣ�

18��������O1��һ����ƿ�ĳ�����ĩѹֵ��2�ֽڣ�

19��������O1�ڶ�����ƿ�ĳ�����ĩѹֵ��2�ֽڣ�

20��������O2��һ����ƿ�ĳ�����ĩѹֵ��2�ֽڣ�

21��������O2�ڶ�����ƿ�ĳ�����ĩѹֵ��2�ֽڣ�

22��������O3��һ����ƿ�ĳ�����ĩѹֵ��2�ֽڣ�

23��������O3�ڶ�����ƿ�ĳ�����ĩѹֵ��2�ֽڣ�

24��Һ��ģ��úţ�2�ֽڣ�
���ֽ���Ч��
���ֽ�Ϊ0x03����Һ��I��
���ֽ�Ϊ0x0c����Һ��II��
���ֽ�Ϊ0x30�Ǳ�Һ��I��
���ֽ�Ϊ0xc0�Ǳ�Һ��II��

25��ȼ����F1���ӵ�λʣ������2�ֽڣ�

26��ȼ����F2���ӵ�λʣ������2�ֽڣ�

27��ȼ����F3���ӵ�λʣ������2�ֽڣ�

28��������O1���ӵ�λʣ������2�ֽڣ�

29��������O2���ӵ�λʣ������2�ֽڣ�

30��������O3���ӵ�λʣ������2�ֽڣ�

31������ģʽ��2�ֽڣ�
Ϊ0x00ffΪ����������ģʽ
Ϊ0xff00Ϊ��������ģʽ

32��ȼ����F1��ѹѹ��ֵ��2�ֽڣ�

33��ȼ����F2��ѹѹ��ֵ��2�ֽڣ�

34��ȼ����F3��ѹѹ��ֵ��2�ֽڣ�

35��������O1��ѹѹ��ֵ��2�ֽڣ�

36��������O2��ѹѹ��ֵ��2�ֽڣ�

37��������O3��ѹѹ��ֵ��2�ֽڣ�


**************************************ע�벹�Ӳ��������������****************************

1��ȼ����ѹ���������趨��2�ֽڣ�
���ֽ���Ч��
���ֽ�bit0��1Ϊ01��ʾȼ����F1ʹ�����ݴ�����PTt14��Ϊ10��ʾȼ����F1ʹ�ñ��ݴ�����PTt20
���ֽ�bit2��3Ϊ01��ʾȼ����F2ʹ�����ݴ�����PTt16��Ϊ10��ʾȼ����F2ʹ�ñ��ݴ�����PTt22
���ֽ�bit4��5Ϊ01��ʾȼ����F3ʹ�����ݴ�����PTt18��Ϊ10��ʾȼ����F3ʹ�ñ��ݴ�����PTt24

2��������ѹ���������趨��2�ֽڣ�
���ֽ���Ч��
���ֽ�bit0��1Ϊ01��ʾ������O1ʹ�����ݴ�����PTt13��Ϊ10��ʾ������O1ʹ�ñ��ݴ�����PTt19
���ֽ�bit2��3Ϊ01��ʾ������O2ʹ�����ݴ�����PTt15��Ϊ10��ʾ������O2ʹ�ñ��ݴ�����PTt21
���ֽ�bit4��5Ϊ01��ʾ������O3ʹ�����ݴ�����PTt17��Ϊ10��ʾ������O3ʹ�ñ��ݴ�����PTt23

3����ѹ��·�������趨��2�ֽڣ�
���ֽ�Ϊ0x00��ȼ·ʹ�ô�����PTb2
���ֽ�Ϊ0x03��ȼ·ʹ�ô�����PTb4
���ֽ�Ϊ0x0c��ȼ·ʹ�ô�����PTb24

���ֽ�Ϊ0x00����·ʹ�ô�����PTb1
���ֽ�Ϊ0x03����·ʹ�ô�����PTb3
���ֽ�Ϊ0x0c����·ʹ�ô�����PTb24

4��ѹ��������ѹ���������趨��2�ֽڣ�
���ֽ���Ч��
���ֽ�bit0��1Ϊ01��ʾ��ѹ����A����ѹ��������PTb03��Ϊ10��ʾ��ѹ����A����ѹ��������PTb29
���ֽ�bit2��3Ϊ01��ʾȼѹ����B����ѹ��������PTb04��Ϊ10��ʾ��ѹ����B����ѹ��������PTb28
���ֽ�bit4��5��6��7Ϊ0001��ʾ����ѹ����C����ѹ��������ΪPTb24��
Ϊ1000��ʾ����ѹ����C����ѹ��������ΪPTb24��



-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
uint16 TGTHT510_supply_stage01_input_decode(void)
{
	uint16 return_state;
	
	return_state=TRUE;
	
	//ȼ���ӽӿڽ���
	if(TGTHT510_supply_input_par.interface_F==0x03)
	{
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R1;
	}
	
	else if(TGTHT510_supply_input_par.interface_F==0x0c)
	{
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R2;
	}
	
	else if(TGTHT510_supply_input_par.interface_F==0x30)
	{
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R3;
	}
	
	else if(TGTHT510_supply_input_par.interface_F==0xc0)
	{
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R4;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	//�����ӽӿڽ���
	if(TGTHT510_supply_input_par.interface_O==0x03)
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O1;
	}
	
	else if(TGTHT510_supply_input_par.interface_O==0x0c)
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O2;
	}
	
	else if(TGTHT510_supply_input_par.interface_O==0x30)
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O3;
	}
	
	else if(TGTHT510_supply_input_par.interface_O==0xc0)
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O4;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	//ȼ���䲹��˳��1�ֽڣ�
	
	if((TGTHT510_supply_input_par.sequence_tank_F>>6)==0)//ȼ���䲹������Ϊ0
	{
		TGTHT510_supply_decode_par.number_tank_F=0;
		TGTHT510_supply_decode_par.first_tank_F=DECODE_NONE;
		TGTHT510_supply_decode_par.second_tank_F=DECODE_NONE;
		TGTHT510_supply_decode_par.third_tank_F=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_tank_F>>6)==1)//ȼ���䲹������Ϊ1
	{
		TGTHT510_supply_decode_par.number_tank_F=1;
		TGTHT510_supply_decode_par.second_tank_F=DECODE_NONE;
		TGTHT510_supply_decode_par.third_tank_F=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x01)//��һ��ȼ����F1
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x02)//��һ��ȼ����F2
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x03)//��һ��ȼ����F3
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_tank_F>>6)==2)//ȼ���䲹������Ϊ2
	{
		TGTHT510_supply_decode_par.number_tank_F=2;
		TGTHT510_supply_decode_par.third_tank_F=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x01)//��һ��ȼ����F1
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x02)//��һ��ȼ����F2
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x03)//��һ��ȼ����F3
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_tank_F&0x0c)>>2)==0x01)//�ڶ���ȼ����F1
		{
			TGTHT510_supply_decode_par.second_tank_F=DECODE_TANK_F1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_F&0x0c)>>2)==0x02)//�ڶ���ȼ����F2
		{
			TGTHT510_supply_decode_par.second_tank_F=DECODE_TANK_F2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_F&0x0c)>>2)==0x03)//�ڶ���ȼ����F3
		{
			TGTHT510_supply_decode_par.second_tank_F=DECODE_TANK_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_tank_F>>6)==3)//ȼ���䲹������Ϊ3
	{
		TGTHT510_supply_decode_par.number_tank_F=3;
		
		if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x01)//��һ��ȼ����F1
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x02)//��һ��ȼ����F2
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x03)//��һ��ȼ����F3
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_tank_F&0x0c)>>2)==0x01)//�ڶ���ȼ����F1
		{
			TGTHT510_supply_decode_par.second_tank_F=DECODE_TANK_F1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_F&0x0c)>>2)==0x02)//�ڶ���ȼ����F2
		{
			TGTHT510_supply_decode_par.second_tank_F=DECODE_TANK_F2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_F&0x0c)>>2)==0x03)//�ڶ���ȼ����F3
		{
			TGTHT510_supply_decode_par.second_tank_F=DECODE_TANK_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_tank_F&0x30)>>4)==0x01)//������ȼ����F1
		{
			TGTHT510_supply_decode_par.third_tank_F=DECODE_TANK_F1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_F&0x30)>>4)==0x02)//������ȼ����F2
		{
			TGTHT510_supply_decode_par.third_tank_F=DECODE_TANK_F2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_F&0x30)>>4)==0x03)//������ȼ����F3
		{
			TGTHT510_supply_decode_par.third_tank_F=DECODE_TANK_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
	
	}
	
	else//����
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//�����䲹��˳��1�ֽڣ�
	
	if((TGTHT510_supply_input_par.sequence_tank_O>>6)==0)//�����䲹������Ϊ0
	{
		TGTHT510_supply_decode_par.number_tank_O=0;
		TGTHT510_supply_decode_par.first_tank_O=DECODE_NONE;
		TGTHT510_supply_decode_par.second_tank_O=DECODE_NONE;
		TGTHT510_supply_decode_par.third_tank_O=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_tank_O>>6)==1)//�����䲹������Ϊ1
	{
		TGTHT510_supply_decode_par.number_tank_O=1;
		TGTHT510_supply_decode_par.second_tank_O=DECODE_NONE;
		TGTHT510_supply_decode_par.third_tank_O=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x01)//��һ��������F1
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x02)//��һ��������F2
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x03)//��һ��������F3
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_tank_O>>6)==2)//�����䲹������Ϊ2
	{
		TGTHT510_supply_decode_par.number_tank_O=2;
		TGTHT510_supply_decode_par.third_tank_O=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x01)//��һ��������F1
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x02)//��һ��������F2
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x03)//��һ��������F3
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_tank_O&0x0c)>>2)==0x01)//�ڶ���������F1
		{
			TGTHT510_supply_decode_par.second_tank_O=DECODE_TANK_O1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_O&0x0c)>>2)==0x02)//�ڶ���������F2
		{
			TGTHT510_supply_decode_par.second_tank_O=DECODE_TANK_O2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_O&0x0c)>>2)==0x03)//�ڶ���������F3
		{
			TGTHT510_supply_decode_par.second_tank_O=DECODE_TANK_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_tank_O>>6)==3)//�����䲹������Ϊ3
	{
		TGTHT510_supply_decode_par.number_tank_O=3;
		
		if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x01)//��һ��������F1
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x02)//��һ��������F2
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x03)//��һ��������F3
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_tank_O&0x0c)>>2)==0x01)//�ڶ���������F1
		{
			TGTHT510_supply_decode_par.second_tank_O=DECODE_TANK_O1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_O&0x0c)>>2)==0x02)//�ڶ���������F2
		{
			TGTHT510_supply_decode_par.second_tank_O=DECODE_TANK_O2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_O&0x0c)>>2)==0x03)//�ڶ���������F3
		{
			TGTHT510_supply_decode_par.second_tank_O=DECODE_TANK_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_tank_O&0x30)>>4)==0x01)//������������F1
		{
			TGTHT510_supply_decode_par.third_tank_O=DECODE_TANK_O1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_O&0x30)>>4)==0x02)//������������F2
		{
			TGTHT510_supply_decode_par.third_tank_O=DECODE_TANK_O2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_O&0x30)>>4)==0x03)//������������F3
		{
			TGTHT510_supply_decode_par.third_tank_O=DECODE_TANK_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
	
	}
	
	else//����
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//ȼ����F1����ƿ����˳��1�ֽڣ�
	
	if((TGTHT510_supply_input_par.sequence_gas_F1>>6)==0)//ȼ����F1����ƿ��������Ϊ0
	{
		TGTHT510_supply_decode_par.number_gas_tank_F1=0;
		TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_NONE;
		TGTHT510_supply_decode_par.second_gas_tank_F1=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_F1>>6)==1)//ȼ����F1����ƿ��������Ϊ1
	{
		TGTHT510_supply_decode_par.number_gas_tank_F1=1;
		TGTHT510_supply_decode_par.second_gas_tank_F1=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_gas_F1&0x03)==0x01)//��һ��������ƿΪF1
		{
			TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_GAS_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F1&0x03)==0x02)//��һ��������ƿΪF2
		{
			TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_GAS_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F1&0x03)==0x03)//��һ��������ƿΪF3
		{
			TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_F1>>6)==2)//ȼ����F1����ƿ��������Ϊ2
	{
		TGTHT510_supply_decode_par.number_gas_tank_F1=2;
		
		if((TGTHT510_supply_input_par.sequence_gas_F1&0x03)==0x01)//��һ��������ƿΪF1
		{
			TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_GAS_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F1&0x03)==0x02)//��һ��������ƿΪF2
		{
			TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_GAS_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F1&0x03)==0x03)//��һ��������ƿΪF3
		{
			TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_gas_F1&0x0c)>>2)==0x01)//�ڶ���������ƿΪF1
		{
			TGTHT510_supply_decode_par.second_gas_tank_F1=DECODE_GAS_F1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_F1&0x0c)>>2)==0x02)//�ڶ���������ƿΪF2
		{
			TGTHT510_supply_decode_par.second_gas_tank_F1=DECODE_GAS_F2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_F1&0x0c)>>2)==0x03)//�ڶ���������ƿΪF3
		{
			TGTHT510_supply_decode_par.second_gas_tank_F1=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//ȼ����F2����ƿ����˳��1�ֽڣ�
	
	if((TGTHT510_supply_input_par.sequence_gas_F2>>6)==0)//ȼ����F2����ƿ��������Ϊ0
	{
		TGTHT510_supply_decode_par.number_gas_tank_F2=0;
		TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_NONE;
		TGTHT510_supply_decode_par.second_gas_tank_F2=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_F2>>6)==1)//ȼ����F2����ƿ��������Ϊ1
	{
		TGTHT510_supply_decode_par.number_gas_tank_F2=1;
		TGTHT510_supply_decode_par.second_gas_tank_F2=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_gas_F2&0x03)==0x01)//��һ��������ƿΪF1
		{
			TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_GAS_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F2&0x03)==0x02)//��һ��������ƿΪF2
		{
			TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_GAS_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F2&0x03)==0x03)//��һ��������ƿΪF3
		{
			TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_F2>>6)==2)//ȼ����F2����ƿ��������Ϊ2
	{
		TGTHT510_supply_decode_par.number_gas_tank_F2=2;
		
		if((TGTHT510_supply_input_par.sequence_gas_F2&0x03)==0x01)//��һ��������ƿΪF1
		{
			TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_GAS_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F2&0x03)==0x02)//��һ��������ƿΪF2
		{
			TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_GAS_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F2&0x03)==0x03)//��һ��������ƿΪF3
		{
			TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_gas_F2&0x0c)>>2)==0x01)//�ڶ���������ƿΪF1
		{
			TGTHT510_supply_decode_par.second_gas_tank_F2=DECODE_GAS_F1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_F2&0x0c)>>2)==0x02)//�ڶ���������ƿΪF2
		{
			TGTHT510_supply_decode_par.second_gas_tank_F2=DECODE_GAS_F2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_F2&0x0c)>>2)==0x03)//�ڶ���������ƿΪF3
		{
			TGTHT510_supply_decode_par.second_gas_tank_F2=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
		
	//ȼ����F3����ƿ����˳��1�ֽڣ�
	
	if((TGTHT510_supply_input_par.sequence_gas_F3>>6)==0)//ȼ����F3����ƿ��������Ϊ0
	{
		TGTHT510_supply_decode_par.number_gas_tank_F3=0;
		TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_NONE;
		TGTHT510_supply_decode_par.second_gas_tank_F3=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_F3>>6)==1)//ȼ����F3����ƿ��������Ϊ1
	{
		TGTHT510_supply_decode_par.number_gas_tank_F3=1;
		TGTHT510_supply_decode_par.second_gas_tank_F3=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_gas_F3&0x03)==0x01)//��һ��������ƿΪF1
		{
			TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_GAS_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F3&0x03)==0x02)//��һ��������ƿΪF2
		{
			TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_GAS_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F3&0x03)==0x03)//��һ��������ƿΪF3
		{
			TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_F3>>6)==2)//ȼ����F3����ƿ��������Ϊ2
	{
		TGTHT510_supply_decode_par.number_gas_tank_F3=2;
		
		if((TGTHT510_supply_input_par.sequence_gas_F3&0x03)==0x01)//��һ��������ƿΪF1
		{
			TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_GAS_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F3&0x03)==0x02)//��һ��������ƿΪF2
		{
			TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_GAS_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F3&0x03)==0x03)//��һ��������ƿΪF3
		{
			TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_gas_F3&0x0c)>>2)==0x01)//�ڶ���������ƿΪF1
		{
			TGTHT510_supply_decode_par.second_gas_tank_F3=DECODE_GAS_F1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_F3&0x0c)>>2)==0x02)//�ڶ���������ƿΪF2
		{
			TGTHT510_supply_decode_par.second_gas_tank_F3=DECODE_GAS_F2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_F3&0x0c)>>2)==0x03)//�ڶ���������ƿΪF3
		{
			TGTHT510_supply_decode_par.second_gas_tank_F3=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//������O1����ƿ����˳��1�ֽڣ�
	
	if((TGTHT510_supply_input_par.sequence_gas_O1>>6)==0)//������O1����ƿ��������Ϊ0
	{
		TGTHT510_supply_decode_par.number_gas_tank_O1=0;
		TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_NONE;
		TGTHT510_supply_decode_par.second_gas_tank_O1=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_O1>>6)==1)//������O1����ƿ��������Ϊ1
	{
		TGTHT510_supply_decode_par.number_gas_tank_O1=1;
		TGTHT510_supply_decode_par.second_gas_tank_O1=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_gas_O1&0x03)==0x01)//��һ��������ƿΪO1
		{
			TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_GAS_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O1&0x03)==0x02)//��һ��������ƿΪO2
		{
			TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_GAS_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O1&0x03)==0x03)//��һ��������ƿΪO3
		{
			TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_O1>>6)==2)//������O1����ƿ��������Ϊ2
	{
		TGTHT510_supply_decode_par.number_gas_tank_O1=2;
		
		if((TGTHT510_supply_input_par.sequence_gas_O1&0x03)==0x01)//��һ��������ƿΪO1
		{
			TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_GAS_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O1&0x03)==0x02)//��һ��������ƿΪO2
		{
			TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_GAS_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O1&0x03)==0x03)//��һ��������ƿΪO3
		{
			TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_gas_O1&0x0c)>>2)==0x01)//�ڶ���������ƿΪO1
		{
			TGTHT510_supply_decode_par.second_gas_tank_O1=DECODE_GAS_O1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_O1&0x0c)>>2)==0x02)//�ڶ���������ƿΪO2
		{
			TGTHT510_supply_decode_par.second_gas_tank_O1=DECODE_GAS_O2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_O1&0x0c)>>2)==0x03)//�ڶ���������ƿΪO3
		{
			TGTHT510_supply_decode_par.second_gas_tank_O1=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//������O2����ƿ����˳��1�ֽڣ�
	
	if((TGTHT510_supply_input_par.sequence_gas_O2>>6)==0)//������O2����ƿ��������Ϊ0
	{
		TGTHT510_supply_decode_par.number_gas_tank_O2=0;
		TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_NONE;
		TGTHT510_supply_decode_par.second_gas_tank_O2=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_O2>>6)==1)//������O2����ƿ��������Ϊ1
	{
		TGTHT510_supply_decode_par.number_gas_tank_O2=1;
		TGTHT510_supply_decode_par.second_gas_tank_O2=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_gas_O2&0x03)==0x01)//��һ��������ƿΪO1
		{
			TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_GAS_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O2&0x03)==0x02)//��һ��������ƿΪO2
		{
			TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_GAS_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O2&0x03)==0x03)//��һ��������ƿΪO3
		{
			TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_O2>>6)==2)//������O2����ƿ��������Ϊ2
	{
		TGTHT510_supply_decode_par.number_gas_tank_O2=2;
		
		if((TGTHT510_supply_input_par.sequence_gas_O2&0x03)==0x01)//��һ��������ƿΪO1
		{
			TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_GAS_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O2&0x03)==0x02)//��һ��������ƿΪO2
		{
			TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_GAS_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O2&0x03)==0x03)//��һ��������ƿΪO3
		{
			TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_gas_O2&0x0c)>>2)==0x01)//�ڶ���������ƿΪO1
		{
			TGTHT510_supply_decode_par.second_gas_tank_O2=DECODE_GAS_O1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_O2&0x0c)>>2)==0x02)//�ڶ���������ƿΪO2
		{
			TGTHT510_supply_decode_par.second_gas_tank_O2=DECODE_GAS_O2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_O2&0x0c)>>2)==0x03)//�ڶ���������ƿΪO3
		{
			TGTHT510_supply_decode_par.second_gas_tank_O2=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
		
	//������O3����ƿ����˳��1�ֽڣ�
	
	if((TGTHT510_supply_input_par.sequence_gas_O3>>6)==0)//������O3����ƿ��������Ϊ0
	{
		TGTHT510_supply_decode_par.number_gas_tank_O3=0;
		TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_NONE;
		TGTHT510_supply_decode_par.second_gas_tank_O3=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_O3>>6)==1)//������O3����ƿ��������Ϊ1
	{
		TGTHT510_supply_decode_par.number_gas_tank_O3=1;
		TGTHT510_supply_decode_par.second_gas_tank_O3=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_gas_O3&0x03)==0x01)//��һ��������ƿΪO1
		{
			TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_GAS_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O3&0x03)==0x02)//��һ��������ƿΪO2
		{
			TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_GAS_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O3&0x03)==0x03)//��һ��������ƿΪO3
		{
			TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_O3>>6)==2)//������O3����ƿ��������Ϊ2
	{
		TGTHT510_supply_decode_par.number_gas_tank_O3=2;
		
		if((TGTHT510_supply_input_par.sequence_gas_O3&0x03)==0x01)//��һ��������ƿΪO1
		{
			TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_GAS_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O3&0x03)==0x02)//��һ��������ƿΪO2
		{
			TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_GAS_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O3&0x03)==0x03)//��һ��������ƿΪO3
		{
			TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_gas_O3&0x0c)>>2)==0x01)//�ڶ���������ƿΪO1
		{
			TGTHT510_supply_decode_par.second_gas_tank_O3=DECODE_GAS_O1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_O3&0x0c)>>2)==0x02)//�ڶ���������ƿΪO2
		{
			TGTHT510_supply_decode_par.second_gas_tank_O3=DECODE_GAS_O2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_O3&0x0c)>>2)==0x03)//�ڶ���������ƿΪO3
		{
			TGTHT510_supply_decode_par.second_gas_tank_O3=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//ȼ������ѹ����������ڷ��ţ�2�ֽڣ�
	
	/*
11��ȼ������ѹ����������ڷ��ţ�2�ֽڣ�
bit0��1Ϊ01��ʾȼ����ѹ����ΪB����Ϊ10��ʾȼ����ѹ����ΪC��
bit2��3Ϊ01��ʾ������ȼѹ�������ڷ���Ϊ����10��ʾ������ȼѹ�������ڷ���Ϊ��
bit4��5Ϊ01��ʾ������ѹ����ΪA����Ϊ10��ʾ������ѹ����ΪC��
bit6��7Ϊ01��ʾ��������ѹ�������ڷ���Ϊ����10��ʾ��������ѹ�������ڷ���Ϊ��
bit8-15Ϊ��
	
	*/
	
	//ȼѹ������
	if((TGTHT510_supply_input_par.compressor_out_valve&0x0003)==0x0001)
	{
		TGTHT510_supply_decode_par.compressor_F=DECODE_COMPRESSOR_B;
	}
	
	else if((TGTHT510_supply_input_par.compressor_out_valve&0x0003)==0x0002)
	{
		TGTHT510_supply_decode_par.compressor_F=DECODE_COMPRESSOR_C;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	//������ȼѹ�������ڷ���
	if(((TGTHT510_supply_input_par.compressor_out_valve&0x000c)>>2)==0x0001)
	{
		TGTHT510_supply_decode_par.valve_out_compressor_F=DECODE_COMP_VALVE_Z;
	}
	
	else if(((TGTHT510_supply_input_par.compressor_out_valve&0x000c)>>2)==0x0002)
	{
		TGTHT510_supply_decode_par.valve_out_compressor_F=DECODE_COMP_VALVE_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	//��ѹ������
	if(((TGTHT510_supply_input_par.compressor_out_valve&0x0030)>>4)==0x0001)
	{
		TGTHT510_supply_decode_par.compressor_O=DECODE_COMPRESSOR_A;
	}
	
	else if(((TGTHT510_supply_input_par.compressor_out_valve&0x0030)>>4)==0x0002)
	{
		TGTHT510_supply_decode_par.compressor_O=DECODE_COMPRESSOR_C;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	//��������ѹ�������ڷ���
	if(((TGTHT510_supply_input_par.compressor_out_valve&0x00c0)>>6)==0x0001)
	{
		TGTHT510_supply_decode_par.valve_out_compressor_O=DECODE_COMP_VALVE_Z;
	}
	
	else if(((TGTHT510_supply_input_par.compressor_out_valve&0x00c0)>>6)==0x0002)
	{
		TGTHT510_supply_decode_par.valve_out_compressor_O=DECODE_COMP_VALVE_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	/*
24��Һ��ģ��úţ�2�ֽڣ�
���ֽ���Ч��
���ֽ�Ϊ0x03����Һ��I��
���ֽ�Ϊ0x0c����Һ��II��
���ֽ�Ϊ0x30�Ǳ�Һ��I��
���ֽ�Ϊ0xc0�Ǳ�Һ��II��
	
	*/
	
	//Һ��ģ��úţ�2�ֽڣ�
	if((TGTHT510_supply_input_par.pump_cooler&0x00ff)==0x0003)
	{
		TGTHT510_supply_decode_par.cooler=DECODE_COOLER_Z_1;
	}
	
	else if((TGTHT510_supply_input_par.pump_cooler&0x00ff)==0x000c)
	{
		TGTHT510_supply_decode_par.cooler=DECODE_COOLER_Z_2;
	}
	
	else if((TGTHT510_supply_input_par.pump_cooler&0x00ff)==0x0030)
	{
		TGTHT510_supply_decode_par.cooler=DECODE_COOLER_B_1;
	}
	
	else if((TGTHT510_supply_input_par.pump_cooler&0x00ff)==0x00c0)
	{
		TGTHT510_supply_decode_par.cooler=DECODE_COOLER_B_2;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	/*
1��ȼ����ѹ���������趨��2�ֽڣ�
���ֽ���Ч��
���ֽ�bit0��1Ϊ01��ʾȼ����F1ʹ�����ݴ�����PTt14��Ϊ10��ʾȼ����F1ʹ�ñ��ݴ�����PTt20
���ֽ�bit2��3Ϊ01��ʾȼ����F2ʹ�����ݴ�����PTt16��Ϊ10��ʾȼ����F2ʹ�ñ��ݴ�����PTt22
���ֽ�bit4��5Ϊ01��ʾȼ����F3ʹ�����ݴ�����PTt18��Ϊ10��ʾȼ����F3ʹ�ñ��ݴ�����PTt24
	*/
	
	//ȼ����ѹ���������趨��2�ֽڣ�
	if(((TGTHT510_supply_input_par.sensor_tank_F&0x0003)>>0)==0x0001)
	{
		TGTHT510_supply_decode_par.sensor_tank_F1=DECODE_SENSOR_TANK_Z;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_tank_F&0x0003)>>0)==0x0002)
	{
		TGTHT510_supply_decode_par.sensor_tank_F1=DECODE_SENSOR_TANK_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	if(((TGTHT510_supply_input_par.sensor_tank_F&0x000c)>>2)==0x0001)
	{
		TGTHT510_supply_decode_par.sensor_tank_F2=DECODE_SENSOR_TANK_Z;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_tank_F&0x000c)>>2)==0x0002)
	{
		TGTHT510_supply_decode_par.sensor_tank_F2=DECODE_SENSOR_TANK_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	if(((TGTHT510_supply_input_par.sensor_tank_F&0x0030)>>4)==0x0001)
	{
		TGTHT510_supply_decode_par.sensor_tank_F3=DECODE_SENSOR_TANK_Z;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_tank_F&0x0030)>>4)==0x0002)
	{
		TGTHT510_supply_decode_par.sensor_tank_F3=DECODE_SENSOR_TANK_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//������ѹ���������趨��2�ֽڣ�
	if(((TGTHT510_supply_input_par.sensor_tank_O&0x0003)>>0)==0x0001)
	{
		TGTHT510_supply_decode_par.sensor_tank_O1=DECODE_SENSOR_TANK_Z;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_tank_O&0x0003)>>0)==0x0002)
	{
		TGTHT510_supply_decode_par.sensor_tank_O1=DECODE_SENSOR_TANK_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	if(((TGTHT510_supply_input_par.sensor_tank_O&0x000c)>>2)==0x0001)
	{
		TGTHT510_supply_decode_par.sensor_tank_O2=DECODE_SENSOR_TANK_Z;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_tank_O&0x000c)>>2)==0x0002)
	{
		TGTHT510_supply_decode_par.sensor_tank_O2=DECODE_SENSOR_TANK_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	if(((TGTHT510_supply_input_par.sensor_tank_O&0x0030)>>4)==0x0001)
	{
		TGTHT510_supply_decode_par.sensor_tank_O3=DECODE_SENSOR_TANK_Z;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_tank_O&0x0030)>>4)==0x0002)
	{
		TGTHT510_supply_decode_par.sensor_tank_O3=DECODE_SENSOR_TANK_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	/*
3����ѹ��·�������趨��2�ֽڣ�
���ֽ�Ϊ0x00��ȼ·ʹ�ô�����PTb2
���ֽ�Ϊ0x03��ȼ·ʹ�ô�����PTb4
���ֽ�Ϊ0x0c��ȼ·ʹ�ô�����PTb24

���ֽ�Ϊ0x00����·ʹ�ô�����PTb1
���ֽ�Ϊ0x03����·ʹ�ô�����PTb3
���ֽ�Ϊ0x0c����·ʹ�ô�����PTb24
	*/
	
	//��ѹ��·�������趨��2�ֽڣ�
	
	if(((TGTHT510_supply_input_par.sensor_pipe_low&0xff00)>>8)==0x0000)
	{
		TGTHT510_supply_decode_par.sensor_pipe_low_F=DECODE_SENSOR_PIPE_LOW_PTB02;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_pipe_low&0xff00)>>8)==0x0003)
	{
		TGTHT510_supply_decode_par.sensor_pipe_low_F=DECODE_SENSOR_PIPE_LOW_PTB04;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_pipe_low&0xff00)>>8)==0x000c)
	{
		TGTHT510_supply_decode_par.sensor_pipe_low_F=DECODE_SENSOR_PIPE_LOW_PTB24;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	if(((TGTHT510_supply_input_par.sensor_pipe_low&0x00ff)>>0)==0x0000)
	{
		TGTHT510_supply_decode_par.sensor_pipe_low_O=DECODE_SENSOR_PIPE_LOW_PTB01;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_pipe_low&0x00ff)>>0)==0x0003)
	{
		TGTHT510_supply_decode_par.sensor_pipe_low_O=DECODE_SENSOR_PIPE_LOW_PTB03;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_pipe_low&0x00ff)>>0)==0x000c)
	{
		TGTHT510_supply_decode_par.sensor_pipe_low_O=DECODE_SENSOR_PIPE_LOW_PTB24;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
/*	
	4��ѹ��������ѹ���������趨��2�ֽڣ�
���ֽ���Ч��
���ֽ�bit0��1Ϊ01��ʾ��ѹ����A����ѹ��������PTb03��Ϊ10��ʾ��ѹ����A����ѹ��������PTb29
���ֽ�bit2��3Ϊ01��ʾȼѹ����B����ѹ��������PTb04��Ϊ10��ʾ��ѹ����B����ѹ��������PTb28
���ֽ�bit4��5��6��7Ϊ0001��ʾ����ѹ����C����ѹ��������ΪPTb24��
Ϊ1000��ʾ����ѹ����C����ѹ��������ΪPTb24��
	
*/

	//ѹ��������ѹ���������趨��2�ֽڣ�
	
	if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
	{
		if(((TGTHT510_supply_input_par.sensor_comp_in&0x000c)>>2)==0x0001)//PTb04
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_F=DECODE_SENSOR_PIPE_LOW_PTB04;
		}
		
		else if(((TGTHT510_supply_input_par.sensor_comp_in&0x000c)>>2)==0x0002)//PTb28
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_F=DECODE_SENSOR_PIPE_LOW_PTB28;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
	
	}
	
	else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
	{
		if(((TGTHT510_supply_input_par.sensor_comp_in&0x00f0)>>4)==0x0001)//PTb24
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_F=DECODE_SENSOR_PIPE_LOW_PTB24;
		}
		
		else if(((TGTHT510_supply_input_par.sensor_comp_in&0x00f0)>>4)==0x0008)//PTb24
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_F=DECODE_SENSOR_PIPE_LOW_PTB24;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
	{
		if(((TGTHT510_supply_input_par.sensor_comp_in&0x0003)>>0)==0x0001)//PTb03
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_O=DECODE_SENSOR_PIPE_LOW_PTB03;
		}
		
		else if(((TGTHT510_supply_input_par.sensor_comp_in&0x0003)>>0)==0x0002)//PTb29
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_O=DECODE_SENSOR_PIPE_LOW_PTB29;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
	}
	
	else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
	{
		if(((TGTHT510_supply_input_par.sensor_comp_in&0x00f0)>>4)==0x0001)//PTb24
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_O=DECODE_SENSOR_PIPE_LOW_PTB24;
		}
		
		else if(((TGTHT510_supply_input_par.sensor_comp_in&0x00f0)>>4)==0x0008)//PTb24
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_O=DECODE_SENSOR_PIPE_LOW_PTB24;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	return return_state;
}



