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
**名称：补加阶段24：状态恢复主函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_supply_stage22_resume_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_24_SUPPLY_DETECTION_DISABLE;
			
			break;
		}
		
		//补加故障检测禁止
		case STEP_24_SUPPLY_DETECTION_DISABLE:
		{
			if(TGTHT510_supply_stage22_resume_step_detection_disable()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_24_SUPPLY_TEMPER_CTRL_DISABLE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//补加自动控温禁止
		case STEP_24_SUPPLY_TEMPER_CTRL_DISABLE:
		{
			if(TGTHT510_supply_stage22_resume_step_supply_temperature_control_disable()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_24_SUPPLY_VALVE_ALL_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//补加系统自锁阀关闭
		case STEP_24_SUPPLY_VALVE_ALL_OFF:
		{
			if(TGTHT510_supply_stage22_resume_step_valve_all_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_24_SUPPLY_VALVE_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//补加系统自锁阀断电
		case STEP_24_SUPPLY_VALVE_POWER_OFF:
		{
			if(TGTHT510_supply_stage22_resume_step_valve_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_24_SUPPLY_IS_VALVE_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断补加系统自锁阀断电
		case STEP_24_SUPPLY_IS_VALVE_POWER_OFF:
		{
			if(TGTHT510_supply_stage22_resume_step_is_valve_power_off()==TRUE)
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

/******************************************************************************************
**名称：补加故障检测禁止
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

uint16 TGTHT510_supply_stage22_resume_step_detection_disable(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_24_0001_DETECTION_DISABLE:
		{
			
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
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
**名称：补加自动控温禁止
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

uint16 TGTHT510_supply_stage22_resume_step_supply_temperature_control_disable(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_24_0001_TEMPER_CTRL_DISABLE;
			break;
		}
		
		case COMMAND_24_0001_TEMPER_CTRL_DISABLE:
		{
			TGTHT510_tempercontrol_supply_is_auto_control(DISABLE);
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
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
**名称：补加系统自锁阀关闭
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

uint16 TGTHT510_supply_stage22_resume_step_valve_all_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_24_0001_LVB01_OFF;
			break;
		}
		
		
		case COMMAND_24_0001_LVB01_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0001_IS_LVB01_OFF;
			
			break;
		}
		
		case COMMAND_24_0001_IS_LVB01_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0002_LVB02_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0002_LVB02_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb2G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0002_IS_LVB02_OFF;
			
			break;
		}
		
		case COMMAND_24_0002_IS_LVB02_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb02,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0003_LVB03_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0003_LVB03_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0003_IS_LVB03_OFF;
			
			break;
		}
		
		case COMMAND_24_0003_IS_LVB03_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0004_LVB04_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0004_LVB04_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb4G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0004_IS_LVB04_OFF;
			
			break;
		}
		
		case COMMAND_24_0004_IS_LVB04_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb04,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0005_LVB05_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0005_LVB05_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0005_IS_LVB05_OFF;
			
			break;
		}
		
		case COMMAND_24_0005_IS_LVB05_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0006_LVB06_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0006_LVB06_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb6G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0006_IS_LVB06_OFF;
			
			break;
		}
		
		case COMMAND_24_0006_IS_LVB06_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb06,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0007_LVB07_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0007_LVB07_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0007_IS_LVB07_OFF;
			
			break;
		}
		
		case COMMAND_24_0007_IS_LVB07_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0008_LVB08_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0008_LVB08_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb8G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0008_IS_LVB08_OFF;
			
			break;
		}
		
		case COMMAND_24_0008_IS_LVB08_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb08,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0009_LVB09_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0009_LVB09_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0009_IS_LVB09_OFF;
			
			break;
		}
		
		case COMMAND_24_0009_IS_LVB09_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0010_LVB10_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0010_LVB10_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb10G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0010_IS_LVB10_OFF;
			
			break;
		}
		
		case COMMAND_24_0010_IS_LVB10_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb10,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0011_LVB11_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0011_LVB11_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0011_IS_LVB11_OFF;
			
			break;
		}
		
		case COMMAND_24_0011_IS_LVB11_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0012_LVB12_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0012_LVB12_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb12G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0012_IS_LVB12_OFF;
			
			break;
		}
		
		case COMMAND_24_0012_IS_LVB12_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb12,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0013_LVB13_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0013_LVB13_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb13G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0013_IS_LVB13_OFF;
			
			break;
		}
		
		case COMMAND_24_0013_IS_LVB13_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0014_LVB14_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0014_LVB14_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb14G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0014_IS_LVB14_OFF;
			
			break;
		}
		
		case COMMAND_24_0014_IS_LVB14_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb14,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0015_LVB15_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0015_LVB15_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb15G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0015_IS_LVB15_OFF;
			
			break;
		}
		
		case COMMAND_24_0015_IS_LVB15_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0016_LVB16_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0016_LVB16_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb16G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0016_IS_LVB16_OFF;
			
			break;
		}
		
		case COMMAND_24_0016_IS_LVB16_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb16,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0017_LVB17_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0017_LVB17_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0017_IS_LVB17_OFF;
			
			break;
		}
		
		case COMMAND_24_0017_IS_LVB17_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0018_LVB18_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0018_LVB18_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb18G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0018_IS_LVB18_OFF;
			
			break;
		}
		
		case COMMAND_24_0018_IS_LVB18_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb18,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0019_LVB19_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0019_LVB19_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0019_IS_LVB19_OFF;
			
			break;
		}
		
		case COMMAND_24_0019_IS_LVB19_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0020_LVB20_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0020_LVB20_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb20G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0020_IS_LVB20_OFF;
			
			break;
		}
		
		case COMMAND_24_0020_IS_LVB20_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb20,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0021_LVB21_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0021_LVB21_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb21G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0021_IS_LVB21_OFF;
			
			break;
		}
		
		case COMMAND_24_0021_IS_LVB21_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0022_LVB22_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0022_LVB22_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb22G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0022_IS_LVB22_OFF;
			
			break;
		}
		
		case COMMAND_24_0022_IS_LVB22_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb22,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0023_LVB23_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0023_LVB23_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb23G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0023_IS_LVB23_OFF;
			
			break;
		}
		
		case COMMAND_24_0023_IS_LVB23_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb23,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0024_LVB24_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0024_LVB24_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb24G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0024_IS_LVB24_OFF;
			
			break;
		}
		
		case COMMAND_24_0024_IS_LVB24_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb24,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0025_LVB25_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0025_LVB25_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0025_IS_LVB25_OFF;
			
			break;
		}
		
		case COMMAND_24_0025_IS_LVB25_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0026_LVB26_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0026_LVB26_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb26G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0026_IS_LVB26_OFF;
			
			break;
		}
		
		case COMMAND_24_0026_IS_LVB26_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb26,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0027_LVB39_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0027_LVB39_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb39G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0027_IS_LVB39_OFF;
			
			break;
		}
		
		case COMMAND_24_0027_IS_LVB39_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb39,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0028_LVB40_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0028_LVB40_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb40G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0028_IS_LVB40_OFF;
			
			break;
		}
		
		case COMMAND_24_0028_IS_LVB40_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb40,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0029_LVB41_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0029_LVB41_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb41G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0029_IS_LVB41_OFF;
			
			break;
		}
		
		case COMMAND_24_0029_IS_LVB41_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb41,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0030_LVB42_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0030_LVB42_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb42G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0030_IS_LVB42_OFF;
			
			break;
		}
		
		case COMMAND_24_0030_IS_LVB42_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb42,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0031_LVB43_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0031_LVB43_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb43G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0031_IS_LVB43_OFF;
			
			break;
		}
		
		case COMMAND_24_0031_IS_LVB43_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0032_LVB44_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0032_LVB44_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb44G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0032_IS_LVB44_OFF;
			
			break;
		}
		
		case COMMAND_24_0032_IS_LVB44_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0033_LVB45_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0033_LVB45_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb45G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0033_IS_LVB45_OFF;
			
			break;
		}
		
		case COMMAND_24_0033_IS_LVB45_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0034_LVB46_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0034_LVB46_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb46G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0034_IS_LVB46_OFF;
			
			break;
		}
		
		case COMMAND_24_0034_IS_LVB46_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0035_LVB47_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0035_LVB47_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb47G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0035_IS_LVB47_OFF;
			
			break;
		}
		
		case COMMAND_24_0035_IS_LVB47_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0036_LVB48_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0036_LVB48_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb48G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0036_IS_LVB48_OFF;
			
			break;
		}
		
		case COMMAND_24_0036_IS_LVB48_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0037_LVB49_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0037_LVB49_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb49G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0037_IS_LVB49_OFF;
			
			break;
		}
		
		case COMMAND_24_0037_IS_LVB49_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb49,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0038_LVB50_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0038_LVB50_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb50G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0038_IS_LVB50_OFF;
			
			break;
		}
		
		case COMMAND_24_0038_IS_LVB50_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb50,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0039_LVB51_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0039_LVB51_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb51G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0039_IS_LVB51_OFF;
			
			break;
		}
		
		case COMMAND_24_0039_IS_LVB51_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb51,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0040_LVB52_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0040_LVB52_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb52G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0040_IS_LVB52_OFF;
			
			break;
		}
		
		case COMMAND_24_0040_IS_LVB52_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb52,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0041_LVB53_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0041_LVB53_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb53G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0041_IS_LVB53_OFF;
			
			break;
		}
		
		case COMMAND_24_0041_IS_LVB53_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0042_LVB54_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0042_LVB54_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb54G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0042_IS_LVB54_OFF;
			
			break;
		}
		
		case COMMAND_24_0042_IS_LVB54_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0043_LVB55_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0043_LVB55_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb55G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0043_IS_LVB55_OFF;
			
			break;
		}
		
		case COMMAND_24_0043_IS_LVB55_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0044_LVB56_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0044_LVB56_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb56G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0044_IS_LVB56_OFF;
			
			break;
		}
		
		case COMMAND_24_0044_IS_LVB56_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0045_LVB57_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0045_LVB57_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb57G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0045_IS_LVB57_OFF;
			
			break;
		}
		
		case COMMAND_24_0045_IS_LVB57_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0046_LVB58_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0046_LVB58_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb58G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0046_IS_LVB58_OFF;
			
			break;
		}
		
		case COMMAND_24_0046_IS_LVB58_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0047_LVB59_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0047_LVB59_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb59G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0047_IS_LVB59_OFF;
			
			break;
		}
		
		case COMMAND_24_0047_IS_LVB59_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb59,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0048_LVB60_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0048_LVB60_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb60G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0048_IS_LVB60_OFF;
			
			break;
		}
		
		case COMMAND_24_0048_IS_LVB60_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb60,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0049_LVB61_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0049_LVB61_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb61G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0049_IS_LVB61_OFF;
			
			break;
		}
		
		case COMMAND_24_0049_IS_LVB61_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb61,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0050_LVB62_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0050_LVB62_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb62G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0050_IS_LVB62_OFF;
			
			break;
		}
		
		case COMMAND_24_0050_IS_LVB62_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb62,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0051_LVB63_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0051_LVB63_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb63G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0051_IS_LVB63_OFF;
			
			break;
		}
		
		case COMMAND_24_0051_IS_LVB63_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb63,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0052_LVB64_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0052_LVB64_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb64G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0052_IS_LVB64_OFF;
			
			break;
		}
		
		case COMMAND_24_0052_IS_LVB64_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb64,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0053_LVB65_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0053_LVB65_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb65G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0053_IS_LVB65_OFF;
			
			break;
		}
		
		case COMMAND_24_0053_IS_LVB65_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb65,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0054_LVB66_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0054_LVB66_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb66G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0054_IS_LVB66_OFF;
			
			break;
		}
		
		case COMMAND_24_0054_IS_LVB66_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb66,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0055_LVB67_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0055_LVB67_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb67G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0055_IS_LVB67_OFF;
			
			break;
		}
		
		case COMMAND_24_0055_IS_LVB67_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb67,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0056_LVB68_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0056_LVB68_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb68G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0056_IS_LVB68_OFF;
			
			break;
		}
		
		case COMMAND_24_0056_IS_LVB68_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb68,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0057_LVB69_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0057_LVB69_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb69G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0057_IS_LVB69_OFF;
			
			break;
		}
		
		case COMMAND_24_0057_IS_LVB69_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0058_LVB70_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0058_LVB70_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb70G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0058_IS_LVB70_OFF;
			
			break;
		}
		
		case COMMAND_24_0058_IS_LVB70_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0059_LVB71_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0059_LVB71_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb71G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0059_IS_LVB71_OFF;
			
			break;
		}
		
		case COMMAND_24_0059_IS_LVB71_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb71,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0060_LVB72_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0060_LVB72_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb72G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0060_IS_LVB72_OFF;
			
			break;
		}
		
		case COMMAND_24_0060_IS_LVB72_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb72,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0061_LVB73_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0061_LVB73_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb73G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0061_IS_LVB73_OFF;
			
			break;
		}
		
		case COMMAND_24_0061_IS_LVB73_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0062_LVB74_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0062_LVB74_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb74G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0062_IS_LVB74_OFF;
			
			break;
		}
		
		case COMMAND_24_0062_IS_LVB74_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0063_LVB75_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0063_LVB75_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb75G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0063_IS_LVB75_OFF;
			
			break;
		}
		
		case COMMAND_24_0063_IS_LVB75_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb75,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0064_LVB76_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0064_LVB76_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb76G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0064_IS_LVB76_OFF;
			
			break;
		}
		
		case COMMAND_24_0064_IS_LVB76_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb76,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0065_LVB77_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0065_LVB77_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb77G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0065_IS_LVB77_OFF;
			
			break;
		}
		
		case COMMAND_24_0065_IS_LVB77_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb77,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0066_LVB78_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0066_LVB78_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb78G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0066_IS_LVB78_OFF;
			
			break;
		}
		
		case COMMAND_24_0066_IS_LVB78_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb78,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0067_LVB79_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0067_LVB79_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb79G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0067_IS_LVB79_OFF;
			
			break;
		}
		
		case COMMAND_24_0067_IS_LVB79_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb79,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0068_LVB80_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0068_LVB80_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb80G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0068_IS_LVB80_OFF;
			
			break;
		}
		
		case COMMAND_24_0068_IS_LVB80_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb80,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0069_LVB81_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0069_LVB81_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb81G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0069_IS_LVB81_OFF;
			
			break;
		}
		
		case COMMAND_24_0069_IS_LVB81_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb81,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0070_LVB82_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0070_LVB82_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb82G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0070_IS_LVB82_OFF;
			
			break;
		}
		
		case COMMAND_24_0070_IS_LVB82_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb82,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0071_LVB83_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0071_LVB83_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb83G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0071_IS_LVB83_OFF;
			
			break;
		}
		
		case COMMAND_24_0071_IS_LVB83_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb83,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0072_LVB84_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0072_LVB84_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb84G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0072_IS_LVB84_OFF;
			
			break;
		}
		
		case COMMAND_24_0072_IS_LVB84_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb84,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0073_LVB85_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0073_LVB85_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb85G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0073_IS_LVB85_OFF;
			
			break;
		}
		
		case COMMAND_24_0073_IS_LVB85_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb85,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0074_LVB86_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0074_LVB86_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb86G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0074_IS_LVB86_OFF;
			
			break;
		}
		
		case COMMAND_24_0074_IS_LVB86_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb86,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_24_0075_LVB87_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_24_0075_LVB87_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb87G);
			
			TGTHT510_supply_ctrl.command=COMMAND_24_0075_IS_LVB87_OFF;
			
			break;
		}
		
		case COMMAND_24_0075_IS_LVB87_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
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
**名称：补加系统自锁阀断电
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

uint16 TGTHT510_supply_stage22_resume_step_valve_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_24_0001_VALVE_POWER_OFF;
			break;
		}
		
		case COMMAND_24_0001_VALVE_POWER_OFF:
		{
			TGTHT510_supply_main_equ_command_set(VALVE_SUPPLY_OFF_POWER);
			
			TGTHT510_supply_ctrl.command=COMMAND_END;
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
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
**名称：补加系统自锁阀断电
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

uint16 TGTHT510_supply_stage22_resume_step_is_valve_power_off(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_24_0001_IS_VALVE_POWER_OFF:
		{
			for(i=STATE_LVb01;i<=STATE_LVb87;i++)
			{
				if(TGTHT510_collectANDgroup_is_valve_state(i)==VALVE_NO_POWER)//阀门未加电
				{
					asm("nop;");
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_POWER_OFF);
					
					return return_state;
				}
				
			}
			
			break;
		}

		case COMMAND_END:
		{
			return_state=TRUE;
			
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
			break;
		}
		
		default:
		{
			break;
		}
	
	}
	
	return return_state;
}








