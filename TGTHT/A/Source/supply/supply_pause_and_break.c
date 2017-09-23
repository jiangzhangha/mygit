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

extern TGTHT510_supply_time_TypeDef TGTHT510_supply_time;

extern TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;

TGTHT510_supply_flow_valve_state_TypeDef TGTHT510_supply_flow_valve_state;

/******************************************************************************************
**名称：补加阶段1：注入补加参数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage01_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段2：状态设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage02_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}


/******************************************************************************************
**名称：补加阶段3：浮动断接器插合
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage03_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段4：补加管路检漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage04_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}


/******************************************************************************************
**名称：补加阶段5：燃贮箱抽气
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage05_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}


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

void TGTHT510_supply_pause_stage06_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}


/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage07_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_PAUSE_07_VALVE_OFF;
			
			break;
		}
		
		case STEP_PAUSE_07_VALVE_OFF:
		{
			if(TGTHT510_supply_pause_stage07_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}

	}
	
}

/******************************************************************************************
**名称：补加阶段8：燃贮箱复压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage08_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段9：第三个燃贮箱抽气
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage09_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}


/******************************************************************************************
**名称：补加阶段10：第三个燃贮箱补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage10_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_PAUSE_10_VALVE_OFF;
			
			break;
		}
		
		case STEP_PAUSE_10_VALVE_OFF:
		{
			if(TGTHT510_supply_pause_stage07_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**名称：补加阶段11：第三个燃贮箱复压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage11_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段12：燃管路吹除
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage12_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段13：氧贮箱抽气
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage13_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段14：氧贮箱增压充填
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage14_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段15：氧推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage15_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_PAUSE_15_VALVE_OFF;
			
			break;
		}
		
		case STEP_PAUSE_15_VALVE_OFF:
		{
			if(TGTHT510_supply_pause_stage15_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
			
	}
	
}

/******************************************************************************************
**名称：补加阶段16：氧贮箱复压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage16_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段17：第三个氧贮箱抽气
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage17_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段18：第三个氧贮箱补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage18_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_PAUSE_18_VALVE_OFF;
			
			break;
		}
		
		case STEP_PAUSE_18_VALVE_OFF:
		{
			if(TGTHT510_supply_pause_stage15_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
			
	}
	
}

/******************************************************************************************
**名称：补加阶段19：第三个氧贮箱复压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage19_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段20：氧管路吹除
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage20_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段21：浮动断接器脱开
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage21_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段22：状态恢复
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_stage22_main(void)
{
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段1：注入补加参数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage01_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段2：状态设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage02_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段3：浮动断接器插合
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage03_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段4：补加管路检漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage04_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段5：燃贮箱抽气
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage05_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}


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

void TGTHT510_supply_pause_resume_stage06_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage07_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_PAUSE_RESUME_07_VALVE_ON;
			
			break;
		}
		
		case STEP_PAUSE_RESUME_07_VALVE_ON:
		{
			if(TGTHT510_supply_pause_resume_stage07_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;
			
			TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;
	
			TGTHT510_supply_ctrl.state=STATE_RUN;
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}

/******************************************************************************************
**名称：补加阶段8：燃贮箱复压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage08_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段9：第三个燃贮箱抽气
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage09_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段10：第三个燃贮箱补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage10_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_PAUSE_RESUME_10_VALVE_ON;
			
			break;
		}
		
		case STEP_PAUSE_RESUME_10_VALVE_ON:
		{
			if(TGTHT510_supply_pause_resume_stage07_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;
			
			TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;
	
			TGTHT510_supply_ctrl.state=STATE_RUN;
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}

/******************************************************************************************
**名称：补加阶段11：第三个燃贮箱复压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage11_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段12：燃管路吹除
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage12_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段13：氧贮箱抽气
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage13_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段14：氧贮箱增压充填
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage14_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段15：氧推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage15_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_PAUSE_RESUME_15_VALVE_ON;
			
			break;
		}
		
		case STEP_PAUSE_RESUME_15_VALVE_ON:
		{
			if(TGTHT510_supply_pause_resume_stage15_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;
			
			TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;
	
			TGTHT510_supply_ctrl.state=STATE_RUN;
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}

/******************************************************************************************
**名称：补加阶段16：氧贮箱复压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage16_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段17：第三个氧贮箱抽气
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage17_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段18：第三个氧贮箱补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage18_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_PAUSE_RESUME_18_VALVE_ON;
			
			break;
		}
		
		case STEP_PAUSE_RESUME_18_VALVE_ON:
		{
			if(TGTHT510_supply_pause_resume_stage15_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;
			
			TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;
	
			TGTHT510_supply_ctrl.state=STATE_RUN;
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}

/******************************************************************************************
**名称：补加阶段19：第三个氧贮箱复压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage19_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段20：氧管路吹除
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage20_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段21：浮动断接器脱开
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage21_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}

/******************************************************************************************
**名称：补加阶段22：状态恢复
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_pause_resume_stage22_main(void)
{
	TGTHT510_supply_ctrl.step=TGTHT510_supply_ctrl.step_temp;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=TGTHT510_supply_ctrl.command_temp;//补加指令：无
	
	TGTHT510_supply_ctrl.state=STATE_RUN;
	
}


/******************************************************************************************
**名称：补加阶段1：注入补加参数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage01_main(void)
{
	TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段2：状态设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage02_main(void)
{
	TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段3：浮动断接器插合
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage03_main(void)
{
	TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}


/******************************************************************************************
**名称：补加阶段4：补加管路检漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage04_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_04_VALVE_OFF;
			
			break;
		}
		
		case STEP_BREAK_04_VALVE_OFF:
		{
			if(TGTHT510_supply_break_stage04_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}

/******************************************************************************************
**名称：补加阶段5：燃贮箱抽气
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage05_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_05_COMPRESSOR_STOP;
			
			break;
		}
		
		case STEP_BREAK_05_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_break_stage05_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}

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

void TGTHT510_supply_break_stage06_main(void)
{
	TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage07_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_07_FLOW_STOP;
			
			break;
		}
		
		case STEP_BREAK_07_FLOW_STOP:
		{
			if(TGTHT510_supply_break_stage07_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}


/******************************************************************************************
**名称：补加阶段8：燃贮箱复压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage08_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_08_REPRE_STOP;
			
			break;
		}
		
		case STEP_BREAK_08_REPRE_STOP:
		{
			if(TGTHT510_supply_break_stage08_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}


/******************************************************************************************
**名称：补加阶段9：第三个燃贮箱抽气
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage09_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_09_COMPRESSOR_STOP;
			
			break;
		}
		
		case STEP_BREAK_09_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_break_stage05_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}


/******************************************************************************************
**名称：补加阶段10：第三个燃贮箱补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage10_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_10_FLOW_STOP;
			
			break;
		}
		
		case STEP_BREAK_10_FLOW_STOP:
		{
			if(TGTHT510_supply_break_stage07_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}


/******************************************************************************************
**名称：补加阶段11：第三个燃贮箱复压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage11_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_11_REPRE_STOP;
			
			break;
		}
		
		case STEP_BREAK_11_REPRE_STOP:
		{
			if(TGTHT510_supply_break_stage11_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}


/******************************************************************************************
**名称：补加阶段12：燃管路吹除
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage12_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_12_VALVE_OFF;
			
			break;
		}
		
		case STEP_BREAK_12_VALVE_OFF:
		{
			if(TGTHT510_supply_break_stage12_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}


/******************************************************************************************
**名称：补加阶段13：氧贮箱抽气
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage13_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_13_COMPRESSOR_STOP;
			
			break;
		}
		
		case STEP_BREAK_13_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_break_stage13_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}

/******************************************************************************************
**名称：补加阶段14：氧贮箱增压充填
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage14_main(void)
{
	TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}

/******************************************************************************************
**名称：补加阶段15：氧推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage15_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_15_FLOW_STOP;
			
			break;
		}
		
		case STEP_BREAK_15_FLOW_STOP:
		{
			if(TGTHT510_supply_break_stage15_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}


/******************************************************************************************
**名称：补加阶段16：氧贮箱复压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage16_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_16_REPRE_STOP;
			
			break;
		}
		
		case STEP_BREAK_16_REPRE_STOP:
		{
			if(TGTHT510_supply_break_stage16_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}


/******************************************************************************************
**名称：补加阶段17：第三个氧贮箱抽气
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage17_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_17_COMPRESSOR_STOP;
			
			break;
		}
		
		case STEP_BREAK_17_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_break_stage13_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}


/******************************************************************************************
**名称：补加阶段18：第三个氧贮箱补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage18_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_18_FLOW_STOP;
			
			break;
		}
		
		case STEP_BREAK_18_FLOW_STOP:
		{
			if(TGTHT510_supply_break_stage15_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}


/******************************************************************************************
**名称：补加阶段19：第三个氧贮箱复压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage19_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_19_REPRE_STOP;
			
			break;
		}
		
		case STEP_BREAK_19_REPRE_STOP:
		{
			if(TGTHT510_supply_break_stage19_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}


/******************************************************************************************
**名称：补加阶段20：氧管路吹除
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage20_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_ctrl.step=STEP_BREAK_20_VALVE_OFF;
			
			break;
		}
		
		case STEP_BREAK_20_VALVE_OFF:
		{
			if(TGTHT510_supply_break_stage20_command_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}


/******************************************************************************************
**名称：补加阶段21：浮动断接器脱开
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage21_main(void)
{
	TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}


/******************************************************************************************
**名称：补加阶段22：状态恢复
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_break_stage22_main(void)
{
	TGTHT510_supply_ctrl.state=STATE_BREAK;//补加状态：中止
			
	TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
	TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
	
}


/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_pause_stage07_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE_RECORD;
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE_RECORD:
		{
			TGTHT510_supply_common_valve_state_record();
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE01_OFF_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE01_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb44G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE01_OFF_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE01_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb44G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE01_OFF_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE01_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb44G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE02_OFF_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE02_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb46G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE02_OFF_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE02_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb46G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE02_OFF_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE02_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb46G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE03_OFF_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE03_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb48G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE03_OFF_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE03_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb48G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE03_OFF_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE03_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb48G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE04_OFF_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE04_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb54G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE04_OFF_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE04_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb54G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE04_OFF_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE04_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb54G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE05_OFF_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE05_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb56G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE05_OFF_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE05_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb56G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE05_OFF_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE05_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb56G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE06_OFF_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE06_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb58G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE06_OFF_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE06_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb58G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_07_VALVE06_OFF_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_07_VALVE06_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb58G);
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
	return return_state;
	
}

/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/


uint16 TGTHT510_supply_pause_stage15_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE_RECORD;
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE_RECORD:
		{
			TGTHT510_supply_common_valve_state_record();
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE01_OFF_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE01_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb43G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE01_OFF_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE01_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb43G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE01_OFF_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE01_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb43G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE02_OFF_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE02_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb45G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE02_OFF_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE02_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb45G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE02_OFF_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE02_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb45G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE03_OFF_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE03_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb47G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE03_OFF_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE03_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb47G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE03_OFF_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE03_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb47G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE04_OFF_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE04_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb53G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE04_OFF_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE04_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb53G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE04_OFF_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE04_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb53G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE05_OFF_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE05_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb55G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE05_OFF_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE05_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb55G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE05_OFF_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE05_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb55G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE06_OFF_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE06_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb57G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE06_OFF_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE06_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb57G);
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_15_VALVE06_OFF_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_15_VALVE06_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb57G);
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
	return return_state;
	
}

/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_pause_resume_stage07_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE_RECORD;
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE_RECORD:
		{
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE01_ON_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE01_ON_NO01:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb44_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb44K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE01_ON_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE01_ON_NO02:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb44_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb44K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE01_ON_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE01_ON_NO03:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb44_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb44K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE02_ON_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE02_ON_NO01:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb46_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb46K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE02_ON_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE02_ON_NO02:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb46_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb46K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE02_ON_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE02_ON_NO03:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb46_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb46K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE03_ON_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE03_ON_NO01:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb48_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb48K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE03_ON_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE03_ON_NO02:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb48_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb48K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE03_ON_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE03_ON_NO03:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb48_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb48K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE04_ON_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE04_ON_NO01:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb54_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb54K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE04_ON_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE04_ON_NO02:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb54_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb54K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE04_ON_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE04_ON_NO03:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb54_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb54K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE05_ON_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE05_ON_NO01:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb56_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb56K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE05_ON_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE05_ON_NO02:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb56_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb56K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE05_ON_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE05_ON_NO03:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb56_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb56K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE06_ON_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE06_ON_NO01:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb58_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb58K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE06_ON_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE06_ON_NO02:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb58_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb58K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_07_VALVE06_ON_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_07_VALVE06_ON_NO03:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb58_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb58K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
	return return_state;
	
}


/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_pause_resume_stage15_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE_RECORD;
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE_RECORD:
		{
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE01_ON_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE01_ON_NO01:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb43_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb43K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE01_ON_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE01_ON_NO02:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb43_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb43K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE01_ON_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE01_ON_NO03:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb43_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb43K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE02_ON_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE02_ON_NO01:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb45_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb45K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE02_ON_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE02_ON_NO02:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb45_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb45K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE02_ON_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE02_ON_NO03:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb45_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb45K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE03_ON_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE03_ON_NO01:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb47_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb47K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE03_ON_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE03_ON_NO02:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb47_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb47K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE03_ON_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE03_ON_NO03:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb47_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb47K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE04_ON_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE04_ON_NO01:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb53_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb53K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE04_ON_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE04_ON_NO02:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb53_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb53K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE04_ON_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE04_ON_NO03:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb53_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb53K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE05_ON_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE05_ON_NO01:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb55_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb55K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE05_ON_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE05_ON_NO02:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb55_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb55K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE05_ON_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE05_ON_NO03:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb55_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb55K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE06_ON_NO01;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE06_ON_NO01:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb57_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb57K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE06_ON_NO02;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE06_ON_NO02:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb57_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb57K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_PAUSE_RESUME_15_VALVE06_ON_NO03;
			
			break;
		}
		
		case COMMAND_PAUSE_RESUME_15_VALVE06_ON_NO03:
		{
			if(TGTHT510_supply_flow_valve_state.flow_LVb57_state==VALVE_ON)
			{
				TGTHT510_supply_main_lvb_set(LVb57K);
			}
			
			else
			{
				asm("nop;");
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
	return return_state;
	
}

/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_break_stage04_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE01_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE01_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb39G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE01_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE01_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb39G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE01_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE01_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb39G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE02_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE02_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb49G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE02_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE02_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb49G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE02_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE02_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb49G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE03_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE03_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb59G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE03_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE03_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb59G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE03_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE03_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb59G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE04_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE04_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb63G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE04_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE04_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb63G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE04_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE04_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb63G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE05_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE05_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb69G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE05_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE05_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb69G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE05_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE05_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb69G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE06_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE06_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb73G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE06_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE06_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb73G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE06_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE06_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb73G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE07_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE07_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb71G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE07_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE07_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb71G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE07_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE07_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb71G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE08_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE08_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb75G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE08_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE08_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb75G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE08_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE08_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb75G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE09_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE09_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb67G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE09_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE09_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb67G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE09_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE09_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb67G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE10_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE10_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb77G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE10_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE10_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb77G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE10_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE10_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb77G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE11_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE11_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb79G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE11_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE11_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb79G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE11_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE11_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb79G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE12_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE12_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb81G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE12_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE12_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb81G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE12_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE12_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb81G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE13_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE13_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb83G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE13_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE13_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb83G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE13_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE13_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb83G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE14_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE14_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb85G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE14_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE14_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb85G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE14_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE14_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb85G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE15_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE15_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb40G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE15_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE15_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb40G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE15_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE15_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb40G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE16_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE16_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb50G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE16_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE16_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb50G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE16_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE16_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb50G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE17_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE17_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb60G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE17_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE17_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb60G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE17_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE17_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb60G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE18_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE18_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb64G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE18_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE18_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb64G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE18_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE18_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb64G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE19_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE19_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb70G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE19_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE19_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb70G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE19_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE19_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb70G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE20_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE20_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb74G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE20_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE20_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb74G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE20_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE20_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb74G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE21_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE21_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb72G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE21_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE21_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb72G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE21_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE21_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb72G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE22_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE22_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb76G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE22_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE22_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb76G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE22_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE22_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb76G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE23_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE23_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb68G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE23_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE23_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb68G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE23_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE23_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb68G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE24_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE24_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb78G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE24_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE24_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb78G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE24_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE24_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb78G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE25_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE25_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb80G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE25_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE25_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb80G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE25_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE25_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb80G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE26_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE26_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb82G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE26_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE26_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb82G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE26_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE26_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb82G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE27_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE27_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb84G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE27_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE27_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb84G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE27_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE27_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb84G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE28_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE28_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb86G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE28_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE28_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb86G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_04_VALVE28_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_04_VALVE28_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb86G);
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
			break;
		}
		
		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
	return return_state;
}

/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_break_stage05_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE01_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE01_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE01_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE01_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE01_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE01_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE02_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE02_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE02_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE02_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE02_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE02_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE03_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE03_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE03_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE03_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE03_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE03_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE04_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE04_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE04_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE04_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE04_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE04_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE05_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE05_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE05_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE05_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE05_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE05_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_COMPRESSOR_STOP_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_05_COMPRESSOR_STOP_NO1:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_TIME_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_05_TIME_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_IS_TIME_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_05_IS_TIME_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_COMPRESSOR_STOP_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_05_COMPRESSOR_STOP_NO2:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_TIME_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_05_TIME_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_IS_TIME_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_05_IS_TIME_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_TIME_1MIN_START_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_05_TIME_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_IS_TIME_1MIN_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_05_IS_TIME_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_BYPATH_VALVE_ON_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_05_BYPATH_VALVE_ON_NO1:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_BYPATH_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_05_BYPATH_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_BYPATH_VALVE_ON_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_05_BYPATH_VALVE_ON_NO3:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_TIME_5SEC_START;
			
			break;
		}
		
		case COMMAND_BREAK_05_TIME_5SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_IS_TIME_5SEC;
			
			break;
		}
		
		case COMMAND_BREAK_05_IS_TIME_5SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_BYPATH_VALVE_OFF_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_05_BYPATH_VALVE_OFF_NO1:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,8);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_BYPATH_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_05_BYPATH_VALVE_OFF_NO2:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,8);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_BYPATH_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_05_BYPATH_VALVE_OFF_NO3:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,8);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE06_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE06_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE06_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE06_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE06_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE06_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE07_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE07_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,10);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE07_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE07_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,10);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE07_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE07_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,10);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE08_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE08_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,11);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE08_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE08_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,11);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE08_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE08_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,11);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE09_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE09_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,12);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE09_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE09_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,12);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE09_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE09_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,12);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE10_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE10_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,13);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE10_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE10_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,13);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_05_VALVE10_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_05_VALVE10_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_F,13);
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
			break;
		}
		
		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
		
	}
	
	return return_state;
	
}

/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_break_stage07_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE01_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE01_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE01_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE01_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE01_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE01_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE02_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE02_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE02_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE02_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE02_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE02_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE03_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE03_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE03_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE03_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE03_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE03_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_SEND_HYCT;
			
			break;
		}
		
		case COMMAND_BREAK_07_SEND_HYCT:
		{
			//送货船故障数据，待补充！！！！！！！！！！！！！！！！
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE04_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE04_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE04_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE04_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE04_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE04_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE05_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE05_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE05_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE05_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE05_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE05_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE06_ON_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE06_ON_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE06_ON_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE06_ON_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE06_ON_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE06_ON_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE07_ON_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE07_ON_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE07_ON_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE07_ON_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE07_ON_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE07_ON_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_TIME_2SEC_START;
			
			break;
		}
		
		case COMMAND_BREAK_07_TIME_2SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_IS_TIME_2SEC;
			
			break;
		}
		
		case COMMAND_BREAK_07_IS_TIME_2SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_2SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE08_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE08_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,8);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE08_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE08_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,8);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE08_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE08_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,8);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE09_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE09_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE09_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE09_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE09_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE09_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE10_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE10_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,10);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE10_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE10_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,10);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE10_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE10_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,10);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE11_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE11_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,11);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE11_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE11_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,11);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_VALVE11_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_07_VALVE11_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_F,11);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_07_SET_TEMPERATURE_LOW;
			
			break;
		}
		
		case COMMAND_BREAK_07_SET_TEMPERATURE_LOW:
		{
			//补加管路控温设置为低，待补充！！！！！！！！！！！！！！！！！！
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
	return return_state;
}

/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_break_stage08_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_VALVE01_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_08_VALVE01_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_HEAD_TANK,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_TIME_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_08_TIME_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_IS_TIME_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_08_IS_TIME_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_VALVE01_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_08_VALVE01_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_HEAD_TANK,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_TIME_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_08_TIME_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_IS_TIME_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_08_IS_TIME_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_VALVE02_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_08_VALVE02_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_HEAD_TANK,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_TIME_1MIN_START_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_08_TIME_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_IS_TIME_1MIN_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_08_IS_TIME_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_VALVE02_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_08_VALVE02_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_HEAD_TANK,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_TIME_1MIN_START_NO4;
			
			break;
		}
		
		case COMMAND_BREAK_08_TIME_1MIN_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_IS_TIME_1MIN_NO4;
			
			break;
		}
		
		case COMMAND_BREAK_08_IS_TIME_1MIN_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_VALVE03_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_08_VALVE03_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_HEAD_TANK,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_TIME_1MIN_START_NO5;
			
			break;
		}
		
		case COMMAND_BREAK_08_TIME_1MIN_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_IS_TIME_1MIN_NO5;
			
			break;
		}
		
		case COMMAND_BREAK_08_IS_TIME_1MIN_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_VALVE03_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_08_VALVE03_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_HEAD_TANK,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_TIME_1MIN_START_NO6;
			
			break;
		}
		
		case COMMAND_BREAK_08_TIME_1MIN_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_IS_TIME_1MIN_NO6;
			
			break;
		}
		
		case COMMAND_BREAK_08_IS_TIME_1MIN_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_VALVE04_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_08_VALVE04_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_HEAD_TANK,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_TIME_1MIN_START_NO7;
			
			break;
		}
		
		case COMMAND_BREAK_08_TIME_1MIN_START_NO7:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_IS_TIME_1MIN_NO7;
			
			break;
		}
		
		case COMMAND_BREAK_08_IS_TIME_1MIN_NO7:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_VALVE04_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_08_VALVE04_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_HEAD_TANK,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_TIME_1MIN_START_NO8;
			
			break;
		}
		
		case COMMAND_BREAK_08_TIME_1MIN_START_NO8:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_IS_TIME_1MIN_NO8;
			
			break;
		}
		
		case COMMAND_BREAK_08_IS_TIME_1MIN_NO8:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_VALVE05_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_08_VALVE05_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_HEAD_TANK,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_TIME_1MIN_START_NO9;
			
			break;
		}
		
		case COMMAND_BREAK_08_TIME_1MIN_START_NO9:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_IS_TIME_1MIN_NO9;
			
			break;
		}
		
		case COMMAND_BREAK_08_IS_TIME_1MIN_NO9:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_VALVE05_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_08_VALVE05_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_HEAD_TANK,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_TIME_1MIN_START_NO10;
			
			break;
		}
		
		case COMMAND_BREAK_08_TIME_1MIN_START_NO10:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_08_IS_TIME_1MIN_NO10;
			
			break;
		}
		
		case COMMAND_BREAK_08_IS_TIME_1MIN_NO10:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
	return return_state;
}



/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_break_stage11_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_VALVE01_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_11_VALVE01_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_LAST_TANK,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_TIME_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_11_TIME_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_IS_TIME_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_11_IS_TIME_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_VALVE01_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_11_VALVE01_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_LAST_TANK,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_TIME_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_11_TIME_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_IS_TIME_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_11_IS_TIME_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_VALVE02_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_11_VALVE02_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_LAST_TANK,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_TIME_1MIN_START_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_11_TIME_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_IS_TIME_1MIN_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_11_IS_TIME_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_VALVE02_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_11_VALVE02_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_LAST_TANK,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_TIME_1MIN_START_NO4;
			
			break;
		}
		
		case COMMAND_BREAK_11_TIME_1MIN_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_IS_TIME_1MIN_NO4;
			
			break;
		}
		
		case COMMAND_BREAK_11_IS_TIME_1MIN_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_VALVE03_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_11_VALVE03_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_LAST_TANK,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_TIME_1MIN_START_NO5;
			
			break;
		}
		
		case COMMAND_BREAK_11_TIME_1MIN_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_IS_TIME_1MIN_NO5;
			
			break;
		}
		
		case COMMAND_BREAK_11_IS_TIME_1MIN_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_VALVE03_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_11_VALVE03_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_LAST_TANK,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_TIME_1MIN_START_NO6;
			
			break;
		}
		
		case COMMAND_BREAK_11_TIME_1MIN_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_IS_TIME_1MIN_NO6;
			
			break;
		}
		
		case COMMAND_BREAK_11_IS_TIME_1MIN_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_VALVE04_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_11_VALVE04_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_LAST_TANK,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_TIME_1MIN_START_NO7;
			
			break;
		}
		
		case COMMAND_BREAK_11_TIME_1MIN_START_NO7:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_IS_TIME_1MIN_NO7;
			
			break;
		}
		
		case COMMAND_BREAK_11_IS_TIME_1MIN_NO7:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_VALVE04_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_11_VALVE04_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_LAST_TANK,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_TIME_1MIN_START_NO8;
			
			break;
		}
		
		case COMMAND_BREAK_11_TIME_1MIN_START_NO8:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_IS_TIME_1MIN_NO8;
			
			break;
		}
		
		case COMMAND_BREAK_11_IS_TIME_1MIN_NO8:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_VALVE05_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_11_VALVE05_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_LAST_TANK,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_TIME_1MIN_START_NO9;
			
			break;
		}
		
		case COMMAND_BREAK_11_TIME_1MIN_START_NO9:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_IS_TIME_1MIN_NO9;
			
			break;
		}
		
		case COMMAND_BREAK_11_IS_TIME_1MIN_NO9:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_VALVE05_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_11_VALVE05_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_F,BREAK_LAST_TANK,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_TIME_1MIN_START_NO10;
			
			break;
		}
		
		case COMMAND_BREAK_11_TIME_1MIN_START_NO10:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_11_IS_TIME_1MIN_NO10;
			
			break;
		}
		
		case COMMAND_BREAK_11_IS_TIME_1MIN_NO10:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
	return return_state;
}



/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_break_stage12_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE01_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE01_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb39G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE01_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE01_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb39G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE01_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE01_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb39G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE02_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE02_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb49G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE02_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE02_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb49G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE02_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE02_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb49G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE03_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE03_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb59G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE03_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE03_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb59G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE03_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE03_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb59G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE04_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE04_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb63G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE04_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE04_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb63G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE04_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE04_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb63G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE05_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE05_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb69G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE05_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE05_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb69G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE05_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE05_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb69G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE06_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE06_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb73G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE06_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE06_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb73G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE06_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE06_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb73G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE07_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE07_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb71G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE07_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE07_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb71G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE07_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE07_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb71G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE08_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE08_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb75G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE08_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE08_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb75G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE08_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE08_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb75G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE09_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE09_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb67G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE09_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE09_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb67G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE09_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE09_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb67G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE10_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE10_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb77G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE10_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE10_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb77G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE10_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE10_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb77G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE11_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE11_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb79G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE11_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE11_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb79G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE11_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE11_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb79G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE12_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE12_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb81G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE12_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE12_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb81G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE12_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE12_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb81G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE13_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE13_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb83G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE13_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE13_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb83G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE13_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE13_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb83G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE14_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE14_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb85G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE14_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE14_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb85G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_12_VALVE14_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_12_VALVE14_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb85G);
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
			break;
		}
		
		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
	return return_state;
}


/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_break_stage13_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE01_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE01_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE01_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE01_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE01_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE01_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE02_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE02_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE02_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE02_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE02_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE02_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE03_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE03_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE03_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE03_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE03_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE03_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE04_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE04_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE04_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE04_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE04_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE04_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE05_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE05_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE05_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE05_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE05_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE05_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_COMPRESSOR_STOP_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_13_COMPRESSOR_STOP_NO1:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_TIME_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_13_TIME_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_IS_TIME_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_13_IS_TIME_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_COMPRESSOR_STOP_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_13_COMPRESSOR_STOP_NO2:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_TIME_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_13_TIME_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_IS_TIME_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_13_IS_TIME_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_TIME_1MIN_START_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_13_TIME_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_IS_TIME_1MIN_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_13_IS_TIME_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_BYPATH_VALVE_ON_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_13_BYPATH_VALVE_ON_NO1:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_BYPATH_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_13_BYPATH_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_BYPATH_VALVE_ON_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_13_BYPATH_VALVE_ON_NO3:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_TIME_5SEC_START;
			
			break;
		}
		
		case COMMAND_BREAK_13_TIME_5SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_IS_TIME_5SEC;
			
			break;
		}
		
		case COMMAND_BREAK_13_IS_TIME_5SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_BYPATH_VALVE_OFF_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_13_BYPATH_VALVE_OFF_NO1:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,8);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_BYPATH_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_13_BYPATH_VALVE_OFF_NO2:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,8);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_BYPATH_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_13_BYPATH_VALVE_OFF_NO3:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,8);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE06_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE06_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE06_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE06_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE06_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE06_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE07_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE07_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,10);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE07_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE07_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,10);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE07_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE07_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,10);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE08_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE08_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,11);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE08_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE08_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,11);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE08_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE08_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,11);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE09_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE09_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,12);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE09_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE09_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,12);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE09_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE09_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,12);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE10_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE10_OFF_NO01:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,13);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE10_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE10_OFF_NO02:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,13);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_13_VALVE10_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_13_VALVE10_OFF_NO03:
		{
			TGTHT510_supply_common_break_compressor_stop(BREAK_KIND_O,13);
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
			break;
		}
		
		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
		
	}
	
	return return_state;
	
}


/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_break_stage15_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE01_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE01_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE01_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE01_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE01_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE01_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE02_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE02_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE02_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE02_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE02_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE02_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE03_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE03_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE03_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE03_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE03_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE03_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_SEND_HYCT;
			
			break;
		}
		
		case COMMAND_BREAK_15_SEND_HYCT:
		{
			//送货船故障数据，待补充！！！！！！！！！！！！！！！！
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE04_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE04_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE04_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE04_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE04_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE04_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE05_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE05_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE05_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE05_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE05_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE05_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE06_ON_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE06_ON_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE06_ON_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE06_ON_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE06_ON_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE06_ON_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE07_ON_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE07_ON_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE07_ON_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE07_ON_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE07_ON_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE07_ON_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_TIME_2SEC_START;
			
			break;
		}
		
		case COMMAND_BREAK_15_TIME_2SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_IS_TIME_2SEC;
			
			break;
		}
		
		case COMMAND_BREAK_15_IS_TIME_2SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_2SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE08_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE08_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,8);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE08_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE08_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,8);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE08_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE08_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,8);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE09_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE09_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE09_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE09_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE09_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE09_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE10_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE10_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,10);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE10_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE10_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,10);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE10_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE10_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,10);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE11_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE11_OFF_NO01:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,11);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE11_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE11_OFF_NO02:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,11);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_VALVE11_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_15_VALVE11_OFF_NO03:
		{
			TGTHT510_supply_common_break_flow_stop(BREAK_KIND_O,11);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_15_SET_TEMPERATURE_LOW;
			
			break;
		}
		
		case COMMAND_BREAK_15_SET_TEMPERATURE_LOW:
		{
			//补加管路控温设置为低，待补充！！！！！！！！！！！！！！！！！！
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
	return return_state;
}


/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_break_stage16_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_VALVE01_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_16_VALVE01_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_HEAD_TANK,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_TIME_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_16_TIME_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_IS_TIME_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_16_IS_TIME_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_VALVE01_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_16_VALVE01_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_HEAD_TANK,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_TIME_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_16_TIME_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_IS_TIME_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_16_IS_TIME_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_VALVE02_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_16_VALVE02_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_HEAD_TANK,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_TIME_1MIN_START_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_16_TIME_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_IS_TIME_1MIN_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_16_IS_TIME_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_VALVE02_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_16_VALVE02_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_HEAD_TANK,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_TIME_1MIN_START_NO4;
			
			break;
		}
		
		case COMMAND_BREAK_16_TIME_1MIN_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_IS_TIME_1MIN_NO4;
			
			break;
		}
		
		case COMMAND_BREAK_16_IS_TIME_1MIN_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_VALVE03_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_16_VALVE03_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_HEAD_TANK,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_TIME_1MIN_START_NO5;
			
			break;
		}
		
		case COMMAND_BREAK_16_TIME_1MIN_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_IS_TIME_1MIN_NO5;
			
			break;
		}
		
		case COMMAND_BREAK_16_IS_TIME_1MIN_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_VALVE03_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_16_VALVE03_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_HEAD_TANK,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_TIME_1MIN_START_NO6;
			
			break;
		}
		
		case COMMAND_BREAK_16_TIME_1MIN_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_IS_TIME_1MIN_NO6;
			
			break;
		}
		
		case COMMAND_BREAK_16_IS_TIME_1MIN_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_VALVE04_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_16_VALVE04_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_HEAD_TANK,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_TIME_1MIN_START_NO7;
			
			break;
		}
		
		case COMMAND_BREAK_16_TIME_1MIN_START_NO7:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_IS_TIME_1MIN_NO7;
			
			break;
		}
		
		case COMMAND_BREAK_16_IS_TIME_1MIN_NO7:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_VALVE04_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_16_VALVE04_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_HEAD_TANK,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_TIME_1MIN_START_NO8;
			
			break;
		}
		
		case COMMAND_BREAK_16_TIME_1MIN_START_NO8:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_IS_TIME_1MIN_NO8;
			
			break;
		}
		
		case COMMAND_BREAK_16_IS_TIME_1MIN_NO8:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_VALVE05_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_16_VALVE05_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_HEAD_TANK,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_TIME_1MIN_START_NO9;
			
			break;
		}
		
		case COMMAND_BREAK_16_TIME_1MIN_START_NO9:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_IS_TIME_1MIN_NO9;
			
			break;
		}
		
		case COMMAND_BREAK_16_IS_TIME_1MIN_NO9:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_VALVE05_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_16_VALVE05_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_HEAD_TANK,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_TIME_1MIN_START_NO10;
			
			break;
		}
		
		case COMMAND_BREAK_16_TIME_1MIN_START_NO10:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_16_IS_TIME_1MIN_NO10;
			
			break;
		}
		
		case COMMAND_BREAK_16_IS_TIME_1MIN_NO10:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
	return return_state;
}


/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_break_stage19_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_VALVE01_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_19_VALVE01_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_LAST_TANK,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_TIME_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_19_TIME_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_IS_TIME_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_BREAK_19_IS_TIME_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_VALVE01_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_19_VALVE01_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_LAST_TANK,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_TIME_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_19_TIME_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_IS_TIME_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_BREAK_19_IS_TIME_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_VALVE02_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_19_VALVE02_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_LAST_TANK,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_TIME_1MIN_START_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_19_TIME_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_IS_TIME_1MIN_NO3;
			
			break;
		}
		
		case COMMAND_BREAK_19_IS_TIME_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_VALVE02_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_19_VALVE02_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_LAST_TANK,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_TIME_1MIN_START_NO4;
			
			break;
		}
		
		case COMMAND_BREAK_19_TIME_1MIN_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_IS_TIME_1MIN_NO4;
			
			break;
		}
		
		case COMMAND_BREAK_19_IS_TIME_1MIN_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_VALVE03_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_19_VALVE03_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_LAST_TANK,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_TIME_1MIN_START_NO5;
			
			break;
		}
		
		case COMMAND_BREAK_19_TIME_1MIN_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_IS_TIME_1MIN_NO5;
			
			break;
		}
		
		case COMMAND_BREAK_19_IS_TIME_1MIN_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_VALVE03_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_19_VALVE03_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_LAST_TANK,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_TIME_1MIN_START_NO6;
			
			break;
		}
		
		case COMMAND_BREAK_19_TIME_1MIN_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_IS_TIME_1MIN_NO6;
			
			break;
		}
		
		case COMMAND_BREAK_19_IS_TIME_1MIN_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_VALVE04_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_19_VALVE04_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_LAST_TANK,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_TIME_1MIN_START_NO7;
			
			break;
		}
		
		case COMMAND_BREAK_19_TIME_1MIN_START_NO7:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_IS_TIME_1MIN_NO7;
			
			break;
		}
		
		case COMMAND_BREAK_19_IS_TIME_1MIN_NO7:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_VALVE04_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_19_VALVE04_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_LAST_TANK,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_TIME_1MIN_START_NO8;
			
			break;
		}
		
		case COMMAND_BREAK_19_TIME_1MIN_START_NO8:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_IS_TIME_1MIN_NO8;
			
			break;
		}
		
		case COMMAND_BREAK_19_IS_TIME_1MIN_NO8:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_VALVE05_OFF_NO01;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_19_VALVE05_OFF_NO01:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_LAST_TANK,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_TIME_1MIN_START_NO9;
			
			break;
		}
		
		case COMMAND_BREAK_19_TIME_1MIN_START_NO9:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_IS_TIME_1MIN_NO9;
			
			break;
		}
		
		case COMMAND_BREAK_19_IS_TIME_1MIN_NO9:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_VALVE05_OFF_NO02;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_BREAK_19_VALVE05_OFF_NO02:
		{
			TGTHT510_supply_common_break_repre_stop(BREAK_KIND_O,BREAK_LAST_TANK,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_TIME_1MIN_START_NO10;
			
			break;
		}
		
		case COMMAND_BREAK_19_TIME_1MIN_START_NO10:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_19_IS_TIME_1MIN_NO10;
			
			break;
		}
		
		case COMMAND_BREAK_19_IS_TIME_1MIN_NO10:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
	return return_state;
}


/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_break_stage20_command_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE01_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE01_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb40G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE01_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE01_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb40G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE01_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE01_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb40G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE02_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE02_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb50G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE02_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE02_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb50G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE02_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE02_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb50G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE03_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE03_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb60G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE03_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE03_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb60G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE03_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE03_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb60G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE04_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE04_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb64G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE04_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE04_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb64G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE04_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE04_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb64G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE05_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE05_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb70G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE05_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE05_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb70G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE05_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE05_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb70G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE06_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE06_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb74G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE06_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE06_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb74G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE06_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE06_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb74G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE07_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE07_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb72G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE07_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE07_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb72G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE07_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE07_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb72G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE08_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE08_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb76G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE08_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE08_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb76G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE08_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE08_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb76G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE09_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE09_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb68G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE09_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE09_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb68G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE09_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE09_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb68G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE10_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE10_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb78G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE10_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE10_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb78G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE10_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE10_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb78G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE11_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE11_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb80G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE11_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE11_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb80G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE11_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE11_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb80G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE12_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE12_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb82G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE12_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE12_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb82G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE12_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE12_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb82G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE13_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE13_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb84G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE13_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE13_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb84G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE13_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE13_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb84G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE14_OFF_NO01;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE14_OFF_NO01:
		{
			TGTHT510_supply_main_lvb_set(LVb86G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE14_OFF_NO02;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE14_OFF_NO02:
		{
			TGTHT510_supply_main_lvb_set(LVb86G);
			
			TGTHT510_supply_ctrl.command=COMMAND_BREAK_20_VALVE14_OFF_NO03;
			
			break;
		}
		
		case COMMAND_BREAK_20_VALVE14_OFF_NO03:
		{
			TGTHT510_supply_main_lvb_set(LVb86G);
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
			break;
		}
		
		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
	return return_state;
}











/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_common_valve_state_record(void)
{
	//LVb44
	if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_ON)==TRUE)
	{
		TGTHT510_supply_flow_valve_state.flow_LVb44_state=VALVE_ON;
	}
	
	else
	{
		TGTHT510_supply_flow_valve_state.flow_LVb44_state=VALVE_UNKNOW;
	}
	
	//LVb46
	if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_ON)==TRUE)
	{
		TGTHT510_supply_flow_valve_state.flow_LVb46_state=VALVE_ON;
	}
	
	else
	{
		TGTHT510_supply_flow_valve_state.flow_LVb46_state=VALVE_UNKNOW;
	}
	
	//LVb48
	if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_ON)==TRUE)
	{
		TGTHT510_supply_flow_valve_state.flow_LVb48_state=VALVE_ON;
	}
	
	else
	{
		TGTHT510_supply_flow_valve_state.flow_LVb48_state=VALVE_UNKNOW;
	}
	
	//LVb54
	if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_ON)==TRUE)
	{
		TGTHT510_supply_flow_valve_state.flow_LVb54_state=VALVE_ON;
	}
	
	else
	{
		TGTHT510_supply_flow_valve_state.flow_LVb54_state=VALVE_UNKNOW;
	}
	
	//LVb56
	if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_ON)==TRUE)
	{
		TGTHT510_supply_flow_valve_state.flow_LVb56_state=VALVE_ON;
	}
	
	else
	{
		TGTHT510_supply_flow_valve_state.flow_LVb56_state=VALVE_UNKNOW;
	}
	
	//LVb58
	if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_ON)==TRUE)
	{
		TGTHT510_supply_flow_valve_state.flow_LVb58_state=VALVE_ON;
	}
	
	else
	{
		TGTHT510_supply_flow_valve_state.flow_LVb58_state=VALVE_UNKNOW;
	}
	
	//LVb43
	if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_ON)==TRUE)
	{
		TGTHT510_supply_flow_valve_state.flow_LVb43_state=VALVE_ON;
	}
	
	else
	{
		TGTHT510_supply_flow_valve_state.flow_LVb43_state=VALVE_UNKNOW;
	}
	
	//LVb45
	if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_ON)==TRUE)
	{
		TGTHT510_supply_flow_valve_state.flow_LVb45_state=VALVE_ON;
	}
	
	else
	{
		TGTHT510_supply_flow_valve_state.flow_LVb45_state=VALVE_UNKNOW;
	}
	
	//LVb47
	if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_ON)==TRUE)
	{
		TGTHT510_supply_flow_valve_state.flow_LVb47_state=VALVE_ON;
	}
	
	else
	{
		TGTHT510_supply_flow_valve_state.flow_LVb47_state=VALVE_UNKNOW;
	}
	
	//LVb53
	if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_ON)==TRUE)
	{
		TGTHT510_supply_flow_valve_state.flow_LVb53_state=VALVE_ON;
	}
	
	else
	{
		TGTHT510_supply_flow_valve_state.flow_LVb53_state=VALVE_UNKNOW;
	}
	
	//LVb55
	if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_ON)==TRUE)
	{
		TGTHT510_supply_flow_valve_state.flow_LVb55_state=VALVE_ON;
	}
	
	else
	{
		TGTHT510_supply_flow_valve_state.flow_LVb55_state=VALVE_UNKNOW;
	}
	
	//LVb57
	if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_ON)==TRUE)
	{
		TGTHT510_supply_flow_valve_state.flow_LVb57_state=VALVE_ON;
	}
	
	else
	{
		TGTHT510_supply_flow_valve_state.flow_LVb57_state=VALVE_UNKNOW;
	}
	
}

/******************************************************************************************
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_common_break_compressor_stop(uint16 break_kind,uint16 command_number)
{
	if(break_kind==BREAK_KIND_F)
	{
		if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb8G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb10G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb12G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb18G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb20G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_equ_command_set(COMPRESS_B_STOP);
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb22K);
					
					break;
				}
				
				case 8:
				{
					TGTHT510_supply_main_lvb_set(LVb22G);
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb14G);
					
					break;
				}
				
				case 10:
				{
					TGTHT510_supply_main_lvb_set(LVb16G);
					
					break;
				}
				
				case 11:
				{
					TGTHT510_supply_main_lvb_set(LVb2G);
					
					break;
				}
				
				case 12:
				{
					TGTHT510_supply_main_lvb_set(LVb4G);
					
					break;
				}
				
				case 13:
				{
					TGTHT510_supply_main_lvb_set(LVb6G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
		}
		
		else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb8G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb10G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb12G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb25G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb26G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb87K);
					
					break;
				}
				
				case 8:
				{
					TGTHT510_supply_main_lvb_set(LVb87G);
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb23G);
					
					break;
				}
				
				case 10:
				{
					TGTHT510_supply_main_lvb_set(LVb24G);
					
					break;
				}
				
				case 11:
				{
					TGTHT510_supply_main_lvb_set(LVb2G);
					
					break;
				}
				
				case 12:
				{
					TGTHT510_supply_main_lvb_set(LVb4G);
					
					break;
				}
				
				case 13:
				{
					TGTHT510_supply_main_lvb_set(LVb6G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else
		{
			asm("nop;");
		}
		
	}
	
	else if(break_kind==BREAK_KIND_O)
	{
		if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb7G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb9G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb11G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb17G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb19G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_equ_command_set(COMPRESS_A_STOP);
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb21K);
					
					break;
				}
				
				case 8:
				{
					TGTHT510_supply_main_lvb_set(LVb21G);
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb13G);
					
					break;
				}
				
				case 10:
				{
					TGTHT510_supply_main_lvb_set(LVb15G);
					
					break;
				}
				
				case 11:
				{
					TGTHT510_supply_main_lvb_set(LVb1G);
					
					break;
				}
				
				case 12:
				{
					TGTHT510_supply_main_lvb_set(LVb3G);
					
					break;
				}
				
				case 13:
				{
					TGTHT510_supply_main_lvb_set(LVb5G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
		}
		
		else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb7G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb9G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb11G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb25G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb26G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb87K);
					
					break;
				}
				
				case 8:
				{
					TGTHT510_supply_main_lvb_set(LVb87G);
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb23G);
					
					break;
				}
				
				case 10:
				{
					TGTHT510_supply_main_lvb_set(LVb24G);
					
					break;
				}
				
				case 11:
				{
					TGTHT510_supply_main_lvb_set(LVb1G);
					
					break;
				}
				
				case 12:
				{
					TGTHT510_supply_main_lvb_set(LVb3G);
					
					break;
				}
				
				case 13:
				{
					TGTHT510_supply_main_lvb_set(LVb5G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
			
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
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_common_break_flow_stop(uint16 break_kind,uint16 command_number)
{
	if(break_kind==BREAK_KIND_F)
	{
		if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)||\
		(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3))
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb44G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb46G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb48G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb40G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb64G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb72K);
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb80K);
					
					break;
				}
				
				case 8:
				{
					TGTHT510_supply_main_lvb_set(LVb72G);
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb80G);
					
					break;
				}
				
				case 10:
				{
					TGTHT510_supply_main_lvb_set(LVb42G);
					
					break;
				}
				
				case 11:
				{
					TGTHT510_supply_main_lvb_set(LVb64G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
				
			}
			
		}
		
		else if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)||\
		(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4))
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb54G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb56G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb58G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb50G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb60G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb68K);
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb86K);
					
					break;
				}
				
				case 8:
				{
					TGTHT510_supply_main_lvb_set(LVb68G);
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb86G);
					
					break;
				}
				
				case 10:
				{
					TGTHT510_supply_main_lvb_set(LVb52G);
					
					break;
				}
				
				case 11:
				{
					TGTHT510_supply_main_lvb_set(LVb62G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
				
			}
			
			
		}
		
		else
		{
			asm("nop;");
		}
		
	}
	
	else if(break_kind==BREAK_KIND_O)
	{
		if((TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)||\
		(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3))
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb43G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb45G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb47G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb39G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb63G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb71K);
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb79K);
					
					break;
				}
				
				case 8:
				{
					TGTHT510_supply_main_lvb_set(LVb71G);
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb79G);
					
					break;
				}
				
				case 10:
				{
					TGTHT510_supply_main_lvb_set(LVb41G);
					
					break;
				}
				
				case 11:
				{
					TGTHT510_supply_main_lvb_set(LVb65G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
				
			}
			
			
		}
		
		else if((TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)||\
		(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4))
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb53G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb55G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb57G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb49G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb59G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb67K);
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb85K);
					
					break;
				}
				
				case 8:
				{
					TGTHT510_supply_main_lvb_set(LVb67G);
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb85G);
					
					break;
				}
				
				case 10:
				{
					TGTHT510_supply_main_lvb_set(LVb51G);
					
					break;
				}
				
				case 11:
				{
					TGTHT510_supply_main_lvb_set(LVb61G);
					
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
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
**名称：补加阶段7：燃推进剂补加流动
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
函数返回值TRUE，表示当前步骤结束
函数返回值FALSE，表示当前步骤未结束
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_common_break_repre_stop(uint16 break_kind,uint16 which_tank,uint16 command_number)
{
	if(break_kind==BREAK_KIND_F)
	{
		if(which_tank==BREAK_HEAD_TANK)//前一个或者两个贮箱
		{
			if(TGTHT510_supply_decode_par.number_tank_F==1)
			{
				if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt2G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt32G);
							
							break;
						}
						
						case 3:
						{
							asm("nop;");
							
							break;
						}
						
						case 4:
						{
							asm("nop;");
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
				}
				
				else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt4G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt28G);
							
							break;
						}
						
						case 3:
						{
							TGTHT510_supply_main_lvt_set(LVt30G);
							
							break;
						}
						
						case 4:
						{
							asm("nop;");
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
				}
				
				else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt6G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt34G);
							
							break;
						}
						
						case 3:
						{
							asm("nop;");
							
							break;
						}
						
						case 4:
						{
							asm("nop;");
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if((TGTHT510_supply_decode_par.number_tank_F==2)||\
			(TGTHT510_supply_decode_par.number_tank_F==3))
			{
				if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)&&\
				(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2))
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt2G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt32G);
							
							break;
						}
						
						case 3:
						{
							TGTHT510_supply_main_lvt_set(LVt4G);
							
							break;
						}
						
						case 4:
						{
							TGTHT510_supply_main_lvt_set(LVt28G);
							
							break;
						}
						
						case 5:
						{
							TGTHT510_supply_main_lvt_set(LVt30G);
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
				}
				
				else if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)&&\
				(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3))
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt2G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt6G);
							
							break;
						}
						
						case 3:
						{
							TGTHT510_supply_main_lvt_set(LVt32G);
							
							break;
						}
						
						case 4:
						{
							TGTHT510_supply_main_lvt_set(LVt34G);
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
				}
				
				else if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)&&\
				(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3))
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt6G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt34G);
							
							break;
						}
						
						case 3:
						{
							TGTHT510_supply_main_lvt_set(LVt4G);
							
							break;
						}
						
						case 4:
						{
							TGTHT510_supply_main_lvt_set(LVt28G);
							
							break;
						}
						
						case 5:
						{
							TGTHT510_supply_main_lvt_set(LVt30G);
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
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
		
		else if(which_tank==BREAK_LAST_TANK)//第三个贮箱
		{
			if(TGTHT510_supply_decode_par.number_tank_F==3)
			{
				if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt2G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt32G);
							
							break;
						}
						
						case 3:
						{
							asm("nop;");
							
							break;
						}
						
						case 4:
						{
							asm("nop;");
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
				}
				
				else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt4G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt28G);
							
							break;
						}
						
						case 3:
						{
							TGTHT510_supply_main_lvt_set(LVt30G);
							
							break;
						}
						
						case 4:
						{
							asm("nop;");
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
				}
				
				else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt6G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt34G);
							
							break;
						}
						
						case 3:
						{
							asm("nop;");
							
							break;
						}
						
						case 4:
						{
							asm("nop;");
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
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
		
		else
		{
			asm("nop;");
		}
		
	}
	
	else if(break_kind==BREAK_KIND_O)
	{
		if(which_tank==BREAK_HEAD_TANK)//前一个或者两个贮箱
		{
			if(TGTHT510_supply_decode_par.number_tank_O==1)
			{
				if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt1G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt31G);
							
							break;
						}
						
						case 3:
						{
							asm("nop;");
							
							break;
						}
						
						case 4:
						{
							asm("nop;");
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
				}
				
				else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt3G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt27G);
							
							break;
						}
						
						case 3:
						{
							TGTHT510_supply_main_lvt_set(LVt29G);
							
							break;
						}
						
						case 4:
						{
							asm("nop;");
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
				}
				
				else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt5G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt33G);
							
							break;
						}
						
						case 3:
						{
							asm("nop;");
							
							break;
						}
						
						case 4:
						{
							asm("nop;");
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if((TGTHT510_supply_decode_par.number_tank_O==2)||\
			(TGTHT510_supply_decode_par.number_tank_O==3))
			{
				if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)&&\
				(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2))
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt1G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt31G);
							
							break;
						}
						
						case 3:
						{
							TGTHT510_supply_main_lvt_set(LVt3G);
							
							break;
						}
						
						case 4:
						{
							TGTHT510_supply_main_lvt_set(LVt27G);
							
							break;
						}
						
						case 5:
						{
							TGTHT510_supply_main_lvt_set(LVt29G);
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
				}
				
				else if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)&&\
				(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3))
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt1G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt5G);
							
							break;
						}
						
						case 3:
						{
							TGTHT510_supply_main_lvt_set(LVt31G);
							
							break;
						}
						
						case 4:
						{
							TGTHT510_supply_main_lvt_set(LVt33G);
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
				}
				
				else if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)&&\
				(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3))
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt5G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt33G);
							
							break;
						}
						
						case 3:
						{
							TGTHT510_supply_main_lvt_set(LVt3G);
							
							break;
						}
						
						case 4:
						{
							TGTHT510_supply_main_lvt_set(LVt27G);
							
							break;
						}
						
						case 5:
						{
							TGTHT510_supply_main_lvt_set(LVt29G);
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
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
		
		else if(which_tank==BREAK_LAST_TANK)//第三个贮箱
		{
			if(TGTHT510_supply_decode_par.number_tank_O==3)
			{
				if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt1G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt31G);
							
							break;
						}
						
						case 3:
						{
							asm("nop;");
							
							break;
						}
						
						case 4:
						{
							asm("nop;");
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
				}
				
				else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt3G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt27G);
							
							break;
						}
						
						case 3:
						{
							TGTHT510_supply_main_lvt_set(LVt29G);
							
							break;
						}
						
						case 4:
						{
							asm("nop;");
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
				}
				
				else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
				{
					switch(command_number)
					{
						case 1:
						{
							TGTHT510_supply_main_lvt_set(LVt5G);
							
							break;
						}
						
						case 2:
						{
							TGTHT510_supply_main_lvt_set(LVt33G);
							
							break;
						}
						
						case 3:
						{
							asm("nop;");
							
							break;
						}
						
						case 4:
						{
							asm("nop;");
							
							break;
						}
						
						case 5:
						{
							asm("nop;");
							
							break;
						}
						
						default:
						{
							break;
						}
						
						
					}
					
					
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































