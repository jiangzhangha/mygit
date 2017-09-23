/**
  ******************************************************************************
  * @file    TGTHT510_supply.c
  * @author  蒋章
  * @version V1.00
  * @date    20150626
  * @brief   空间站核心舱推进管理器补加模块C文件
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"


/*全局变量---------------------------------------------------------------------*/		

extern TGTHT510_supply_ctrl_TypeDef TGTHT510_supply_ctrl;

extern TGTHT510_supply_input_par_TypeDef TGTHT510_supply_input_par;

/******************************************************************************************
**名称：补加阶段6：燃贮箱增压充填
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_supply_stage06_pre_f_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
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
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_NONE;//补加状态：空闲
			
			TGTHT510_supply_ctrl.stage=STAGE_00_NONE;//补加阶段：无
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			TGTHT510_supply_time_stage_end();
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}








