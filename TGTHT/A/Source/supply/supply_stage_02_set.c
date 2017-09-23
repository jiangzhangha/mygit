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
**名称：
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_supply_stage02_set_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_02_SUPPLY_VALVE_POWER_ON;
			break;
		}
		
		case STEP_02_SUPPLY_DETECTION_ENABLE://补加故障检测使能
		{
			//待补充！！！！！
			TGTHT510_supply_ctrl.step=STEP_02_SUPPLY_TEMPER_CTRL_ENABLE;
			break;
		}
		
		case STEP_02_SUPPLY_TEMPER_CTRL_ENABLE://补加自动控温使能
		{
			TGTHT510_tempercontrol_supply_is_auto_control(ENABLE);
			
			TGTHT510_supply_ctrl.step=STEP_02_SUPPLY_VALVE_POWER_ON;
			
			break;
		}
		
		case STEP_02_SUPPLY_VALVE_POWER_ON://补加系统自锁阀加电
		{
			TGTHT510_supply_stage02_set_supply_valve_power_on();
			break;
		}
		
		case STEP_02_SUPPLY_VALVE_ALL_OFF://补加系统自锁阀关闭
		{
			TGTHT510_supply_stage02_set_supply_valve_all_off();
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
**名称：补加阶段2
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_stage02_set_supply_valve_power_on(void)
{
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_02_0001_EQU_VALVE_POWER_ON;
			break;
		}
		
		case COMMAND_02_0001_EQU_VALVE_POWER_ON://补加阀门加电
		{
			TGTHT510_supply_main_equ_command_set(VALVE_SUPPLY_ON_POWER);
			TGTHT510_supply_ctrl.command=COMMAND_02_0002_ASK_FOR_SERVICE;
			break;
		}
		
		case COMMAND_02_0002_ASK_FOR_SERVICE://发送服务请求
		{
			TGTHT510_supply_ctrl.command=COMMAND_02_0003_TIME_1MIN_START;
			break;
		}
		
		case COMMAND_02_0003_TIME_1MIN_START://开始一分钟计时
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0004_IS_TIME_1MIN;
			break;
		}
		
		case COMMAND_02_0004_IS_TIME_1MIN://判断一分钟是否到
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0005_IS_VALVE_POWER_ON;
			}
			
			break;
		}
		
		case COMMAND_02_0005_IS_VALVE_POWER_ON:
		{
			//待补充！！！！！
			TGTHT510_supply_ctrl.command=COMMAND_END;
			break;
		}
		
		case COMMAND_END:
		{
			TGTHT510_supply_ctrl.step=STEP_02_SUPPLY_VALVE_ALL_OFF;
			
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}


/******************************************************************************************
**名称：补加阶段2
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_stage02_set_supply_valve_all_off(void)
{
		switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_02_0006_LVB01_OFF;
			break;
		}
		
		//LVb1
		case COMMAND_02_0006_LVB01_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0081_IS_LVB01_OFF;
			
			break;
		}
		
		case COMMAND_02_0081_IS_LVB01_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0007_LVB02_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb2
		case COMMAND_02_0007_LVB02_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb2G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0082_IS_LVB02_OFF;
			
			break;
		}
		
		case COMMAND_02_0082_IS_LVB02_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb02,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0008_LVB03_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb3
		case COMMAND_02_0008_LVB03_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0083_IS_LVB03_OFF;
			
			break;
		}
		
		case COMMAND_02_0083_IS_LVB03_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0009_LVB04_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb4
		case COMMAND_02_0009_LVB04_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb4G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0084_IS_LVB04_OFF;
			
			break;
		}
		
		case COMMAND_02_0084_IS_LVB04_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb04,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0010_LVB05_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb5
		case COMMAND_02_0010_LVB05_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0085_IS_LVB05_OFF;
			
			break;
		}
		
		case COMMAND_02_0085_IS_LVB05_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0011_LVB06_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb6
		case COMMAND_02_0011_LVB06_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb6G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0086_IS_LVB06_OFF;
			
			break;
		}
		
		case COMMAND_02_0086_IS_LVB06_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb06,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0012_LVB07_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb7
		case COMMAND_02_0012_LVB07_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0087_IS_LVB07_OFF;
			
			break;
		}
		
		case COMMAND_02_0087_IS_LVB07_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0013_LVB08_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb8
		case COMMAND_02_0013_LVB08_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb8G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0088_IS_LVB08_OFF;
			
			break;
		}
		
		case COMMAND_02_0088_IS_LVB08_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb08,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0014_LVB09_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb9
		case COMMAND_02_0014_LVB09_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0089_IS_LVB09_OFF;
			
			break;
		}
		
		case COMMAND_02_0089_IS_LVB09_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0015_LVB10_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb10
		case COMMAND_02_0015_LVB10_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb10G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0090_IS_LVB10_OFF;
			
			break;
		}
		
		case COMMAND_02_0090_IS_LVB10_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb10,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0016_LVB11_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb11
		case COMMAND_02_0016_LVB11_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0091_IS_LVB11_OFF;
			
			break;
		}
		
		case COMMAND_02_0091_IS_LVB11_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0017_LVB12_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		
		//LVb12
		case COMMAND_02_0017_LVB12_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb12G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0092_IS_LVB12_OFF;
			
			break;
		}
		
		case COMMAND_02_0092_IS_LVB12_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb12,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0018_LVB13_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		
		//LVb13
		case COMMAND_02_0018_LVB13_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb13G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0093_IS_LVB13_OFF;
			
			break;
		}
		
		case COMMAND_02_0093_IS_LVB13_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0019_LVB14_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb14
		case COMMAND_02_0019_LVB14_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb14G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0094_IS_LVB14_OFF;
			
			break;
		}
		
		case COMMAND_02_0094_IS_LVB14_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb14,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0020_LVB15_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb15
		case COMMAND_02_0020_LVB15_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb15G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0095_IS_LVB15_OFF;
			
			break;
		}
		
		case COMMAND_02_0095_IS_LVB15_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0021_LVB16_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb16
		case COMMAND_02_0021_LVB16_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb16G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0096_IS_LVB16_OFF;
			
			break;
		}
		
		case COMMAND_02_0096_IS_LVB16_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb16,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0022_LVB17_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb17
		case COMMAND_02_0022_LVB17_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0097_IS_LVB17_OFF;
			
			break;
		}
		
		case COMMAND_02_0097_IS_LVB17_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0023_LVB18_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb18
		case COMMAND_02_0023_LVB18_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb18G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0098_IS_LVB18_OFF;
			
			break;
		}
		
		case COMMAND_02_0098_IS_LVB18_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb18,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0024_LVB19_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb19
		case COMMAND_02_0024_LVB19_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0099_IS_LVB19_OFF;
			
			break;
		}
		
		case COMMAND_02_0099_IS_LVB19_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0025_LVB20_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb20
		case COMMAND_02_0025_LVB20_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb20G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0100_IS_LVB20_OFF;
			
			break;
		}
		
		case COMMAND_02_0100_IS_LVB20_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb20,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0026_LVB21_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb21
		case COMMAND_02_0026_LVB21_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb21G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0101_IS_LVB21_OFF;
			
			break;
		}
		
		case COMMAND_02_0101_IS_LVB21_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0027_LVB22_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb22
		case COMMAND_02_0027_LVB22_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb22G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0102_IS_LVB22_OFF;
			
			break;
		}
		
		case COMMAND_02_0102_IS_LVB22_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb22,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0028_LVB23_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb23
		case COMMAND_02_0028_LVB23_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb23G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0103_IS_LVB23_OFF;
			
			break;
		}
		
		case COMMAND_02_0103_IS_LVB23_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb23,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0029_LVB24_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb24
		case COMMAND_02_0029_LVB24_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb24G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0104_IS_LVB24_OFF;
			
			break;
		}
		
		case COMMAND_02_0104_IS_LVB24_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb24,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0030_LVB25_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb25
		case COMMAND_02_0030_LVB25_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0105_IS_LVB25_OFF;
			
			break;
		}
		
		case COMMAND_02_0105_IS_LVB25_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0031_LVB26_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb26
		case COMMAND_02_0031_LVB26_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb26G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0106_IS_LVB26_OFF;
			
			break;
		}
		
		case COMMAND_02_0106_IS_LVB26_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb26,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0032_LVB39_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb39
		case COMMAND_02_0032_LVB39_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb39G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0107_IS_LVB39_OFF;
			
			break;
		}
		
		case COMMAND_02_0107_IS_LVB39_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb39,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0033_LVB40_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb40
		case COMMAND_02_0033_LVB40_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb40G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0108_IS_LVB40_OFF;
			
			break;
		}
		
		case COMMAND_02_0108_IS_LVB40_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb40,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0034_LVB41_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb41
		case COMMAND_02_0034_LVB41_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb41G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0109_IS_LVB41_OFF;
			
			break;
		}
		
		case COMMAND_02_0109_IS_LVB41_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb41,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0035_LVB42_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb42
		case COMMAND_02_0035_LVB42_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb42G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0110_IS_LVB42_OFF;
			
			break;
		}
		
		case COMMAND_02_0110_IS_LVB42_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb42,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0036_LVB43_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb43
		case COMMAND_02_0036_LVB43_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb43G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0111_IS_LVB43_OFF;
			
			break;
		}
		
		case COMMAND_02_0111_IS_LVB43_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0037_LVB44_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb44
		case COMMAND_02_0037_LVB44_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb44G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0112_IS_LVB44_OFF;
			
			break;
		}
		
		case COMMAND_02_0112_IS_LVB44_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0038_LVB45_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb45
		case COMMAND_02_0038_LVB45_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb45G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0113_IS_LVB45_OFF;
			
			break;
		}
		
		case COMMAND_02_0113_IS_LVB45_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0039_LVB46_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb46
		case COMMAND_02_0039_LVB46_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb46G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0114_IS_LVB46_OFF;
			
			break;
		}
		
		case COMMAND_02_0114_IS_LVB46_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0040_LVB47_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb47
		case COMMAND_02_0040_LVB47_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb47G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0115_IS_LVB47_OFF;
			
			break;
		}
		
		case COMMAND_02_0115_IS_LVB47_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0041_LVB48_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb48
		case COMMAND_02_0041_LVB48_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb48G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0116_IS_LVB48_OFF;
			
			break;
		}
		
		case COMMAND_02_0116_IS_LVB48_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0042_LVB49_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb49
		case COMMAND_02_0042_LVB49_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb49G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0117_IS_LVB49_OFF;
			
			break;
		}
		
		case COMMAND_02_0117_IS_LVB49_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb49,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0043_LVB50_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		
		//LVb50
		case COMMAND_02_0043_LVB50_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb50G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0118_IS_LVB50_OFF;
			
			break;
		}
		
		case COMMAND_02_0118_IS_LVB50_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb50,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0044_LVB51_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb51
		case COMMAND_02_0044_LVB51_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb51G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0119_IS_LVB51_OFF;
			
			break;
		}
		
		case COMMAND_02_0119_IS_LVB51_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb51,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0045_LVB52_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb52
		case COMMAND_02_0045_LVB52_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb52G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0120_IS_LVB52_OFF;
			
			break;
		}
		
		case COMMAND_02_0120_IS_LVB52_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb52,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0046_LVB53_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb53
		case COMMAND_02_0046_LVB53_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb53G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0121_IS_LVB53_OFF;
			
			break;
		}
		
		case COMMAND_02_0121_IS_LVB53_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0047_LVB54_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb54
		case COMMAND_02_0047_LVB54_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb54G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0122_IS_LVB54_OFF;
			
			break;
		}
		
		case COMMAND_02_0122_IS_LVB54_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0048_LVB55_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb55
		case COMMAND_02_0048_LVB55_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb55G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0123_IS_LVB55_OFF;
			
			break;
		}
		
		case COMMAND_02_0123_IS_LVB55_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0049_LVB56_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb56
		case COMMAND_02_0049_LVB56_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb56G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0124_IS_LVB56_OFF;
			
			break;
		}
		
		case COMMAND_02_0124_IS_LVB56_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0050_LVB57_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb57
		case COMMAND_02_0050_LVB57_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb57G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0125_IS_LVB57_OFF;
			
			break;
		}
		
		case COMMAND_02_0125_IS_LVB57_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0051_LVB58_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb58
		case COMMAND_02_0051_LVB58_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb58G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0126_IS_LVB58_OFF;
			
			break;
		}
		
		case COMMAND_02_0126_IS_LVB58_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0052_LVB59_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb59
		case COMMAND_02_0052_LVB59_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb59G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0127_IS_LVB59_OFF;
			
			break;
		}
		
		case COMMAND_02_0127_IS_LVB59_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb59,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0053_LVB60_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb60
		case COMMAND_02_0053_LVB60_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb60G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0128_IS_LVB60_OFF;
			
			break;
		}
		
		case COMMAND_02_0128_IS_LVB60_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb60,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0054_LVB61_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb61
		case COMMAND_02_0054_LVB61_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb61G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0129_IS_LVB61_OFF;
			
			break;
		}
		
		case COMMAND_02_0129_IS_LVB61_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb61,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0055_LVB62_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb62
		case COMMAND_02_0055_LVB62_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb62G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0130_IS_LVB62_OFF;
			
			break;
		}
		
		case COMMAND_02_0130_IS_LVB62_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb62,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0056_LVB63_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb63
		case COMMAND_02_0056_LVB63_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb63G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0131_IS_LVB63_OFF;
			
			break;
		}
		
		case COMMAND_02_0131_IS_LVB63_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb63,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0057_LVB64_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb64
		case COMMAND_02_0057_LVB64_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb64G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0132_IS_LVB64_OFF;
			
			break;
		}
		
		case COMMAND_02_0132_IS_LVB64_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb64,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0058_LVB65_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb65
		case COMMAND_02_0058_LVB65_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb65G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0133_IS_LVB65_OFF;
			
			break;
		}
		
		case COMMAND_02_0133_IS_LVB65_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb65,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0059_LVB66_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb66
		case COMMAND_02_0059_LVB66_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb66G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0134_IS_LVB66_OFF;
			
			break;
		}
		
		case COMMAND_02_0134_IS_LVB66_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb66,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0060_LVB67_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			break;
		}
		
		//LVb67
		case COMMAND_02_0060_LVB67_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb67G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0135_IS_LVB67_OFF;
			
			break;
		}
		
		case COMMAND_02_0135_IS_LVB67_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb67,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0061_LVB68_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb68
		case COMMAND_02_0061_LVB68_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb68G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0136_IS_LVB68_OFF;
			
			break;
		}
		
		case COMMAND_02_0136_IS_LVB68_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb68,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0062_LVB69_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb69
		case COMMAND_02_0062_LVB69_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb69G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0137_IS_LVB69_OFF;
			
			break;
		}
		
		case COMMAND_02_0137_IS_LVB69_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0063_LVB70_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		
		//LVb70
		case COMMAND_02_0063_LVB70_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb70G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0138_IS_LVB70_OFF;
			
			break;
		}
		
		case COMMAND_02_0138_IS_LVB70_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0064_LVB71_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb71
		case COMMAND_02_0064_LVB71_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb71G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0139_IS_LVB71_OFF;
			
			break;
		}
		
		case COMMAND_02_0139_IS_LVB71_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb71,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0065_LVB72_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb72
		case COMMAND_02_0065_LVB72_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb72G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0140_IS_LVB72_OFF;
			
			break;
		}
		
		case COMMAND_02_0140_IS_LVB72_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb72,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0066_LVB73_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb73
		case COMMAND_02_0066_LVB73_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb73G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0141_IS_LVB73_OFF;
			
			break;
		}
		
		case COMMAND_02_0141_IS_LVB73_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0067_LVB74_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb74
		case COMMAND_02_0067_LVB74_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb74G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0142_IS_LVB74_OFF;
			
			break;
		}
		
		case COMMAND_02_0142_IS_LVB74_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0068_LVB75_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb75
		case COMMAND_02_0068_LVB75_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb75G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0143_IS_LVB75_OFF;
			
			break;
		}
		
		case COMMAND_02_0143_IS_LVB75_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb75,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0069_LVB76_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb76
		case COMMAND_02_0069_LVB76_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb76G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0144_IS_LVB76_OFF;
			
			break;
		}
		
		case COMMAND_02_0144_IS_LVB76_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb76,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0070_LVB77_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb77
		case COMMAND_02_0070_LVB77_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb77G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0145_IS_LVB77_OFF;
			
			break;
		}
		
		case COMMAND_02_0145_IS_LVB77_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb77,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0071_LVB78_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb78
		case COMMAND_02_0071_LVB78_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb78G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0146_IS_LVB78_OFF;
			
			break;
		}
		
		case COMMAND_02_0146_IS_LVB78_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb78,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0072_LVB79_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb79
		case COMMAND_02_0072_LVB79_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb79G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0147_IS_LVB79_OFF;
			
			break;
		}
		
		case COMMAND_02_0147_IS_LVB79_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb79,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0073_LVB80_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb80
		case COMMAND_02_0073_LVB80_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb80G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0148_IS_LVB80_OFF;
			
			break;
		}
		
		case COMMAND_02_0148_IS_LVB80_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb80,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0074_LVB81_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb81
		case COMMAND_02_0074_LVB81_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb81G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0149_IS_LVB81_OFF;
			
			break;
		}
		
		case COMMAND_02_0149_IS_LVB81_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb81,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0075_LVB82_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb82
		case COMMAND_02_0075_LVB82_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb82G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0150_IS_LVB82_OFF;
			
			break;
		}
		
		case COMMAND_02_0150_IS_LVB82_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb82,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0076_LVB83_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb83
		case COMMAND_02_0076_LVB83_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb83G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0151_IS_LVB83_OFF;
			
			break;
		}
		
		case COMMAND_02_0151_IS_LVB83_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb83,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0077_LVB84_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb84
		case COMMAND_02_0077_LVB84_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb84G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0152_IS_LVB84_OFF;
			
			break;
		}
		
		case COMMAND_02_0152_IS_LVB84_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb84,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0078_LVB85_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb85
		case COMMAND_02_0078_LVB85_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb85G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0153_IS_LVB85_OFF;
			
			break;
		}
		
		case COMMAND_02_0153_IS_LVB85_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb85,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0079_LVB86_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb86
		case COMMAND_02_0079_LVB86_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb86G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0154_IS_LVB86_OFF;
			
			break;
		}
		
		case COMMAND_02_0154_IS_LVB86_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb86,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_02_0080_LVB87_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//LVb87
		case COMMAND_02_0080_LVB87_OFF:
		{
			TGTHT510_supply_main_lvb_set(LVb87G);
			
			TGTHT510_supply_ctrl.command=COMMAND_02_0155_IS_LVB87_OFF;
			
			break;
		}
		
		case COMMAND_02_0155_IS_LVB87_OFF:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)//阀门关闭正确
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			break;
		}
		
		
		case COMMAND_END:
		{
			TGTHT510_supply_ctrl.step=STEP_END;//补加阶段2结束
			
			TGTHT510_supply_ctrl.command=COMMAND_START;
			
			break;
		}
		
	}

	
}

















