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

/******************************************************************************************
**���ƣ����ӽ׶�6��ȼ������ѹ����
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/
void TGTHT510_supply_stage06_pre_f_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://��ʼ
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_06_F_IS_INERFACE;
			
			break;
		}
		
		case STEP_06_F_IS_INERFACE://
		{
			asm("nop;");
			
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








