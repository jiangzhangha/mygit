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

extern TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;


extern valvecontrol_TypeDef TGTHT510_valvecontrol_struct;	//阀门控制结构体
extern uint16 TGTHT510_1553B_data_TGTHT100[];				//全局数组，缓存推进遥测线路盒除温度参数以外数据，89字
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[];		//全局数组，缓存推进遥测线路盒复帧A温度数据，65字
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[];		//全局数组，缓存推进遥测线路盒复帧B温度数据，65字
extern uint16 TGTHT510_1553B_data_TGTHT530[];				//全局数组，缓存压气机电机驱动器遥测数据，14字
extern uint16 TGTHT510_1553B_data_TGTHT520a[];				//全局数组，缓存推进控制驱动器主机遥测，7字
extern uint16 TGTHT510_1553B_data_TGTHT520b[];				//全局数组，缓存推进控制驱动器备机遥测，7字
extern uint16 TGTHT510_1553B_R_HYCT1100[];					//全局数组，缓存货船发送的遥测数据

uint16 temp_gloal[10];

/******************************************************************************************
**名称：补加阶段9：燃推进剂补加流动主函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_supply_stage15_flow_o_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_15_O_FLOW_TANK_NUMBER;
			
			break;
		}

//--------------------------判断补加流动的贮箱数量-----------------------------------------		
		
		//判断补加流动的贮箱数量
		case STEP_15_O_FLOW_TANK_NUMBER:
		{
			TGTHT510_supply_stage15_flow_o_step_tank_number();
			break;
		}
				
//---------------------一个燃贮箱补加流动---------------------------------------
		
		//判断货船增压状态好
		case STEP_15_O_1TANK_IS_HYCT_GOOD:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_is_hyct_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开近浮动断接器阀门
		case STEP_15_O_1TANK_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_interface_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断近浮动断接器阀门开启是否正常
		case STEP_15_O_1TANK_IS_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_is_interface_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_MIDDLE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开燃补加接口中间阀门
		case STEP_15_O_1TANK_MIDDLE_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_middle_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_DELAY1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待
		case STEP_15_O_1TANK_DELAY1:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_PIPE_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断燃补加接口管路压力是否稳定
		case STEP_15_O_1TANK_IS_PIPE_PRESSURE:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_is_pipe_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开进贮箱补加液路阀门
		case STEP_15_O_1TANK_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_FLOW_CORRECT_V;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过补加速率判断补加过程是否正常
		case STEP_15_O_1TANK_IS_FLOW_CORRECT_V:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_is_flow_correct()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_FLOW_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断补加是否到位
		case STEP_15_O_1TANK_IS_FLOW_OVER:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_is_flow_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_SET_FLOW_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//设置补加到位信息，发送货船
		case STEP_15_O_1TANK_SET_FLOW_GOOD:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_set_flow_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关进贮箱补加液路阀门
		case STEP_15_O_1TANK_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断贮箱阀门关闭是否正常
		case STEP_15_O_1TANK_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_is_valve_off_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_NEED_FLOW_THIRD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断是否需对第三个贮箱继续补加
		case STEP_15_O_1TANK_IS_NEED_FLOW_THIRD:
		{
			TGTHT510_supply_stage15_flow_o_step_1tank_is_need_flow_third();
			
			break;
		}
		
		//密闭管路处理策略
		case STEP_15_O_1TANK_PIPE_DEAL:
		{
			if(TGTHT510_supply_stage15_flow_o_step_1tank_pipe_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
	
		
//---------------------两个燃贮箱补加流动---------------------------------------
		
		//判断货船增压状态好
		case STEP_15_O_2TANK_IS_HYCT_GOOD:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_is_hyct_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开近浮动断接器阀门
		case STEP_15_O_2TANK_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_interface_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_IS_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断近浮动断接器阀门开启是否正常
		case STEP_15_O_2TANK_IS_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_is_interface_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_MIDDLE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开燃补加接口中间阀门
		case STEP_15_O_2TANK_MIDDLE_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_middle_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_DELAY1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待
		case STEP_15_O_2TANK_DELAY1:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_IS_PIPE_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断燃补加接口管路压力是否稳定
		case STEP_15_O_2TANK_IS_PIPE_PRESSURE:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_is_pipe_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK1_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开进贮箱补加液路阀门，第一个贮箱
		case STEP_15_O_2TANK_TANK1_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank1_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK1_IS_FLOW_CORRECT_V;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过补加速率判断补加过程是否正常，第一个贮箱
		case STEP_15_O_2TANK_TANK1_IS_FLOW_CORRECT_V:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_flow_correct()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK1_IS_FLOW_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断补加是否到位，第一个贮箱
		case STEP_15_O_2TANK_TANK1_IS_FLOW_OVER:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_flow_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK1_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关进贮箱补加液路阀门，第一个贮箱
		case STEP_15_O_2TANK_TANK1_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank1_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK1_IS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断贮箱阀门关闭是否正常，第一个贮箱
		case STEP_15_O_2TANK_TANK1_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_valve_off_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK2_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开进贮箱补加液路阀门，第二个贮箱
		case STEP_15_O_2TANK_TANK2_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank2_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK2_IS_FLOW_CORRECT_V;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过补加速率判断补加过程是否正常，第二个贮箱
		case STEP_15_O_2TANK_TANK2_IS_FLOW_CORRECT_V:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_flow_correct()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK2_IS_FLOW_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断补加是否到位，第二个贮箱
		case STEP_15_O_2TANK_TANK2_IS_FLOW_OVER:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_flow_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_SET_FLOW_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//设置补加到位信息，发送货船
		case STEP_15_O_2TANK_SET_FLOW_GOOD:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_set_flow_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK2_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		
		//关进贮箱补加液路阀门，第二个贮箱
		case STEP_15_O_2TANK_TANK2_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank2_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_TANK2_IS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断贮箱阀门关闭是否正常，第二个贮箱
		case STEP_15_O_2TANK_TANK2_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_valve_off_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_IS_NEED_FLOW_THIRD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断是否需对第三个贮箱继续补加
		case STEP_15_O_2TANK_IS_NEED_FLOW_THIRD:
		{
			TGTHT510_supply_stage15_flow_o_step_2tank_is_need_flow_third();
			
			break;
		}
		
		//密闭管路处理策略
		case STEP_15_O_2TANK_PIPE_DEAL:
		{
			if(TGTHT510_supply_stage15_flow_o_step_2tank_pipe_deal()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
			
//----------------------------------结束--------------------------------------------------------------
	
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
**名称：判断补加流动的贮箱数量
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

void TGTHT510_supply_stage15_flow_o_step_tank_number(void)
{
	if(TGTHT510_supply_decode_par.number_tank_O==1)
	{
		TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_IS_HYCT_GOOD;
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
	
	else if((TGTHT510_supply_decode_par.number_tank_O==2)||\
	(TGTHT510_supply_decode_par.number_tank_O==3))
	{
		TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_IS_HYCT_GOOD;
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
	
	else
	{
		TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
	}

}

/******************************************************************************************
**名称：判断货船增压状态好
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_hyct_good(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IS_HYCT_GOOD;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_IS_HYCT_GOOD:
		{
			if(TGTHT510_supply_common_is_hyct_good(FLOW_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//货船增压状态异常
				//TGTHT510_supply_main_pause(ERRNO_HYCT_PRESSURE);
				TGTHT510_supply_ctrl.command=COMMAND_END;
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
**名称：开近浮动断接器阀门
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_interface_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_INTERFACE_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_INTERFACE_VALVE_ON:
		{
			TGTHT510_supply_common_interface_valve_on(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_INTERFACE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_common_is_interface_valve_on(FLOW_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
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
**名称：通过压力判断近浮动断接器阀门开启是否正常
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_interface_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_INTERFACE_VALVE_ON_P;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_INTERFACE_VALVE_ON_P:
		{
			if(TGTHT510_supply_common_is_interface_valve_on_pressure(FLOW_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//通过压力判断近浮动断接器阀门开启异常
				TGTHT510_supply_main_pause(ERRNO_INTERFACE_VALVE_ON_PRESSURE);
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
**名称：开燃补加接口中间阀门
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_middle_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_MIDDLE_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_MIDDLE_VALVE_ON:
		{
			TGTHT510_supply_common_middle_valve_on(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_MIDDLE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_MIDDLE_VALVE_ON:
		{
			if(TGTHT510_supply_common_is_middle_valve_on(FLOW_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
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
**名称：延时等待
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_DELAY1_START;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_DELAY1_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_DELAY1;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_DELAY1:
		{
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_delay_short)==TRUE)
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
**名称：通过压力判断燃补加接口管路压力是否稳定
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_pipe_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_PIPE_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_PIPE_PRESSURE_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_1TANK_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_15_0003_O_1TANK_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_1TANK_PIPE_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0004_O_1TANK_PIPE_PRESSURE_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_1TANK_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0005_O_1TANK_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_1TANK_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_15_0006_O_1TANK_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_1TANK_PIPE_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_1TANK_PIPE_PRESSURE_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_1TANK_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_15_0008_O_1TANK_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0009_O_1TANK_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_15_0009_O_1TANK_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0010_O_1TANK_PIPE_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0010_O_1TANK_PIPE_PRESSURE_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0011_O_1TANK_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_15_0011_O_1TANK_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0012_O_1TANK_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_15_0012_O_1TANK_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0013_O_1TANK_PIPE_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0013_O_1TANK_PIPE_PRESSURE_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0014_O_1TANK_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_15_0014_O_1TANK_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0015_O_1TANK_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_15_0015_O_1TANK_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0016_O_1TANK_PIPE_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0016_O_1TANK_PIPE_PRESSURE_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0017_O_1TANK_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_15_0017_O_1TANK_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0018_O_1TANK_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_15_0018_O_1TANK_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0019_O_1TANK_PIPE_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0019_O_1TANK_PIPE_PRESSURE_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0020_O_1TANK_IS_PIPE_PRESSURE;
			
			break;
		}
		
		case COMMAND_15_0020_O_1TANK_IS_PIPE_PRESSURE:
		{
			if(TGTHT510_supply_common_is_pipe_pressure_stable(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加接口管路压力不稳定
				TGTHT510_supply_main_pause(ERRNO_PIPE_PRESSURE_STABLE);
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
**名称：开进贮箱补加液路阀门
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_IN_TANK_VALVE_ON:
		{
			TGTHT510_supply_common_flow_in_tank_valve_on(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_on(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
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
**名称：通过补加速率判断补加过程是否正常
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_flow_correct(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_HTT_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_HTT_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_1TANK_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_15_0003_O_1TANK_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_1TANK_HTT_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0004_O_1TANK_HTT_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_1TANK_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0005_O_1TANK_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_1TANK_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_15_0006_O_1TANK_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_1TANK_HTT_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_1TANK_HTT_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_1TANK_IS_FLOW_CORRECT;
			
			break;
		}
		
		case COMMAND_15_0008_O_1TANK_IS_FLOW_CORRECT:
		{
			if(TGTHT510_supply_common_is_flow_correct(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//判断出补加速率异常，暂不处理，待修改！！！！！！！！！！！！
				TGTHT510_supply_ctrl.command=COMMAND_END;
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
**名称：判断补加是否到位
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_flow_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IS_FLOW_OVER_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_IS_FLOW_OVER_NO1:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_FLOW_OVER_NO2;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_FLOW_OVER_NO2:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_1TANK_IS_FLOW_OVER_NO3;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_15_0003_O_1TANK_IS_FLOW_OVER_NO3:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IS_FLOW_OVER_NO1;
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
**名称：关进贮箱补加液路阀门
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IN_TANK_VALVE_OFF;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_IN_TANK_VALVE_OFF:
		{
			TGTHT510_supply_common_flow_in_tank_valve_off(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_IN_TANK_VALVE_OFF;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_off(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加系统阀门关闭异常
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
**名称：通过压力判断贮箱阀门关闭是否正常
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_valve_off_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_IS_PRESSURE;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_IS_PRESSURE:
		{
			if(TGTHT510_supply_common_is_tank_valve_off_pressure(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加流动时通过压力判断进贮箱阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_PRESSURE);
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
**名称：判断是否需对第三个贮箱继续补加
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

void TGTHT510_supply_stage15_flow_o_step_1tank_is_need_flow_third(void)
{
	if(TGTHT510_supply_decode_par.number_tank_O==3)
	{
		TGTHT510_supply_ctrl.step=STEP_END;//程序结束
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
			
	else
	{
		TGTHT510_supply_ctrl.step=STEP_15_O_1TANK_PIPE_DEAL;//程序继续
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
		
}

/******************************************************************************************
**名称：设置补加到位信息，发送货船
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

//待修改！！！！！！！！！！！！

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_set_flow_good(void)
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
		
		case COMMAND_15_0001_O_1TANK_SET_FLOW_GOOD:
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
**名称：密闭管路处理策略
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

uint16 TGTHT510_supply_stage15_flow_o_step_1tank_pipe_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_1TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_1TANK_VALVE_OFF_NO1:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_1TANK_IS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_1TANK_IS_VALVE_OFF_NO1:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_1TANK_VALVE_ON_NO2;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0003_O_1TANK_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_1TANK_IS_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_15_0004_O_1TANK_IS_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_1TANK_5SEC_START;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_15_0005_O_1TANK_5SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_1TANK_IS_5SEC;
			
			break;
		}
		
		case COMMAND_15_0006_O_1TANK_IS_5SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_1TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_1TANK_VALVE_OFF_NO3:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_1TANK_IS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_15_0008_O_1TANK_IS_VALVE_OFF_NO3:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,6)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0009_O_1TANK_VALVE_OFF_NO4;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0009_O_1TANK_VALVE_OFF_NO4:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0010_O_1TANK_IS_VALVE_OFF_NO4;
			
			break;
		}
		
		case COMMAND_15_0010_O_1TANK_IS_VALVE_OFF_NO4:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,8)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0011_O_1TANK_VALVE_OFF_NO5;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0011_O_1TANK_VALVE_OFF_NO5:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0012_O_1TANK_IS_VALVE_OFF_NO5;
			
			break;
		}
		
		case COMMAND_15_0012_O_1TANK_IS_VALVE_OFF_NO5:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,10)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0013_O_1TANK_10SEC_START;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0013_O_1TANK_10SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0014_O_1TANK_IS_10SEC;
			
			break;
		}
		
		case COMMAND_15_0014_O_1TANK_IS_10SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_10SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0015_O_1TANK_PIPE_GET_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0015_O_1TANK_PIPE_GET_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0016_O_1TANK_PIPE_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0016_O_1TANK_PIPE_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0017_O_1TANK_PIPE_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_15_0017_O_1TANK_PIPE_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0018_O_1TANK_PIPE_GET_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0018_O_1TANK_PIPE_GET_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0019_O_1TANK_PIPE_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0019_O_1TANK_PIPE_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0020_O_1TANK_PIPE_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_15_0020_O_1TANK_PIPE_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0021_O_1TANK_PIPE_GET_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0021_O_1TANK_PIPE_GET_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0022_O_1TANK_PIPE_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_15_0022_O_1TANK_PIPE_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0023_O_1TANK_PIPE_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_15_0023_O_1TANK_PIPE_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0024_O_1TANK_PIPE_GET_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0024_O_1TANK_PIPE_GET_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0025_O_1TANK_PIPE_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_15_0025_O_1TANK_PIPE_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0026_O_1TANK_PIPE_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_15_0026_O_1TANK_PIPE_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0027_O_1TANK_PIPE_GET_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0027_O_1TANK_PIPE_GET_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0028_O_1TANK_PIPE_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_15_0028_O_1TANK_PIPE_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0029_O_1TANK_PIPE_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_15_0029_O_1TANK_PIPE_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0030_O_1TANK_PIPE_GET_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0030_O_1TANK_PIPE_GET_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0031_O_1TANK_PIPE_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_15_0031_O_1TANK_PIPE_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0032_O_1TANK_PIPE_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_15_0032_O_1TANK_PIPE_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0033_O_1TANK_PIPE_GET_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0033_O_1TANK_PIPE_GET_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0034_O_1TANK_PIPE_DEAL_PRESSURE;
			
			break;
		}
		
		case COMMAND_15_0034_O_1TANK_PIPE_DEAL_PRESSURE:
		{
			if(TGTHT510_supply_common_is_pipe_pressure_stable(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加接口管路压力不稳定
				TGTHT510_supply_main_pause(ERRNO_PIPE_PRESSURE_STABLE);
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


//************************两个贮箱补加流动************************************************

/******************************************************************************************
**名称：判断货船增压状态好
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_is_hyct_good(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_IS_HYCT_GOOD;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_IS_HYCT_GOOD:
		{
			if(TGTHT510_supply_common_is_hyct_good(FLOW_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//货船增压状态异常
				//TGTHT510_supply_main_pause(ERRNO_HYCT_PRESSURE);
				TGTHT510_supply_ctrl.command=COMMAND_END;
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
**名称：开近浮动断接器阀门
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_interface_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_INTERFACE_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_INTERFACE_VALVE_ON:
		{
			TGTHT510_supply_common_interface_valve_on(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_IS_INTERFACE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_IS_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_common_is_interface_valve_on(FLOW_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
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
**名称：通过压力判断近浮动断接器阀门开启是否正常
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_is_interface_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_INTERFACE_VALVE_ON_P;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_INTERFACE_VALVE_ON_P:
		{
			if(TGTHT510_supply_common_is_interface_valve_on_pressure(FLOW_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//通过压力判断近浮动断接器阀门开启异常
				TGTHT510_supply_main_pause(ERRNO_INTERFACE_VALVE_ON_PRESSURE);
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
**名称：开燃补加接口中间阀门
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_middle_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_MIDDLE_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_MIDDLE_VALVE_ON:
		{
			TGTHT510_supply_common_middle_valve_on(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_IS_MIDDLE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_IS_MIDDLE_VALVE_ON:
		{
			if(TGTHT510_supply_common_is_middle_valve_on(FLOW_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
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
**名称：延时等待
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_DELAY1_START;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_DELAY1_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_IS_DELAY1;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_IS_DELAY1:
		{
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_delay_short)==TRUE)
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
**名称：通过压力判断燃补加接口管路压力是否稳定
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_is_pipe_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_PIPE_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_PIPE_PRESSURE_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_2TANK_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_15_0003_O_2TANK_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_2TANK_PIPE_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0004_O_2TANK_PIPE_PRESSURE_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_2TANK_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0005_O_2TANK_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_2TANK_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_15_0006_O_2TANK_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_2TANK_PIPE_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_2TANK_PIPE_PRESSURE_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_2TANK_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_15_0008_O_2TANK_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0009_O_2TANK_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_15_0009_O_2TANK_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0010_O_2TANK_PIPE_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0010_O_2TANK_PIPE_PRESSURE_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0011_O_2TANK_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_15_0011_O_2TANK_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0012_O_2TANK_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_15_0012_O_2TANK_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0013_O_2TANK_PIPE_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0013_O_2TANK_PIPE_PRESSURE_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0014_O_2TANK_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_15_0014_O_2TANK_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0015_O_2TANK_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_15_0015_O_2TANK_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0016_O_2TANK_PIPE_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0016_O_2TANK_PIPE_PRESSURE_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0017_O_2TANK_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_15_0017_O_2TANK_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0018_O_2TANK_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_15_0018_O_2TANK_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0019_O_2TANK_PIPE_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0019_O_2TANK_PIPE_PRESSURE_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0020_O_2TANK_IS_PIPE_PRESSURE;
			
			break;
		}
		
		case COMMAND_15_0020_O_2TANK_IS_PIPE_PRESSURE:
		{
			if(TGTHT510_supply_common_is_pipe_pressure_stable(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加接口管路压力不稳定
				TGTHT510_supply_main_pause(ERRNO_PIPE_PRESSURE_STABLE);
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
**名称：开进贮箱补加液路阀门
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK1_IN_TANK_VALVE_ON:
		{
			TGTHT510_supply_common_flow_in_tank_valve_on(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_on(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
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
**名称：通过补加速率判断补加过程是否正常
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_flow_correct(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_HTT_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK1_HTT_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK1_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK1_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_2TANK_TANK1_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_15_0003_O_2TANK_TANK1_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_2TANK_TANK1_HTT_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0004_O_2TANK_TANK1_HTT_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_2TANK_TANK1_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0005_O_2TANK_TANK1_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_2TANK_TANK1_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_15_0006_O_2TANK_TANK1_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_2TANK_TANK1_HTT_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_2TANK_TANK1_HTT_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_2TANK_TANK1_IS_FLOW_CORRECT;
			
			break;
		}
		
		case COMMAND_15_0008_O_2TANK_TANK1_IS_FLOW_CORRECT:
		{
			if(TGTHT510_supply_common_is_flow_correct(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//判断出补加速率异常，暂不处理，待修改！！！！！！！！！！！！
				TGTHT510_supply_ctrl.command=COMMAND_END;
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
**名称：判断补加是否到位
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_flow_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IS_FLOW_OVER_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK1_IS_FLOW_OVER_NO1:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK1_IS_FLOW_OVER_NO2;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK1_IS_FLOW_OVER_NO2:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_2TANK_TANK1_IS_FLOW_OVER_NO3;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_15_0003_O_2TANK_TANK1_IS_FLOW_OVER_NO3:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IS_FLOW_OVER_NO1;
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
**名称：关进贮箱补加液路阀门
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IN_TANK_VALVE_OFF;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK1_IN_TANK_VALVE_OFF:
		{
			TGTHT510_supply_common_flow_in_tank_valve_off(FLOW_TANK_O,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_OFF;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_off(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加系统阀门关闭异常
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
**名称：通过压力判断贮箱阀门关闭是否正常
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_valve_off_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK1_IS_PRESSURE;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK1_IS_PRESSURE:
		{
			if(TGTHT510_supply_common_is_tank_valve_off_pressure(FLOW_TANK_O,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加流动时通过压力判断进贮箱阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_PRESSURE);
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
**名称：开进贮箱补加液路阀门
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK2_IN_TANK_VALVE_ON:
		{
			TGTHT510_supply_common_flow_in_tank_valve_on(FLOW_TANK_O,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_on(FLOW_TANK_O,SECOND_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
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
**名称：通过补加速率判断补加过程是否正常
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_flow_correct(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_HTT_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK2_HTT_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK2_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK2_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_2TANK_TANK2_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_15_0003_O_2TANK_TANK2_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_2TANK_TANK2_HTT_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0004_O_2TANK_TANK2_HTT_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_2TANK_TANK2_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0005_O_2TANK_TANK2_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_2TANK_TANK2_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_15_0006_O_2TANK_TANK2_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_2TANK_TANK2_HTT_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_2TANK_TANK2_HTT_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_O,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_2TANK_TANK2_IS_FLOW_CORRECT;
			
			break;
		}
		
		case COMMAND_15_0008_O_2TANK_TANK2_IS_FLOW_CORRECT:
		{
			if(TGTHT510_supply_common_is_flow_correct(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//判断出补加速率异常，暂不处理，待修改！！！！！！！！！！！！
				TGTHT510_supply_ctrl.command=COMMAND_END;
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
**名称：判断补加是否到位
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_flow_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IS_FLOW_OVER_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK2_IS_FLOW_OVER_NO1:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,SECOND_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK2_IS_FLOW_OVER_NO2;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK2_IS_FLOW_OVER_NO2:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,SECOND_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_2TANK_TANK2_IS_FLOW_OVER_NO3;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_15_0003_O_2TANK_TANK2_IS_FLOW_OVER_NO3:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_O,SECOND_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IS_FLOW_OVER_NO1;
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
**名称：关进贮箱补加液路阀门
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IN_TANK_VALVE_OFF;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK2_IN_TANK_VALVE_OFF:
		{
			TGTHT510_supply_common_flow_in_tank_valve_off(FLOW_TANK_O,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_OFF;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_off(FLOW_TANK_O,SECOND_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加系统阀门关闭异常
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
**名称：通过压力判断贮箱阀门关闭是否正常
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_valve_off_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_TANK2_IS_PRESSURE;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_TANK2_IS_PRESSURE:
		{
			if(TGTHT510_supply_common_is_tank_valve_off_pressure(FLOW_TANK_O,SECOND_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加流动时通过压力判断进贮箱阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_PRESSURE);
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
**名称：判断是否需对第三个贮箱继续补加
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

void TGTHT510_supply_stage15_flow_o_step_2tank_is_need_flow_third(void)
{
	if(TGTHT510_supply_decode_par.number_tank_O==3)
	{
		TGTHT510_supply_ctrl.step=STEP_END;//程序结束
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
			
	else
	{
		TGTHT510_supply_ctrl.step=STEP_15_O_2TANK_PIPE_DEAL;//程序继续
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}	
}

/******************************************************************************************
**名称：设置补加到位信息，发送货船
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

//待修改！！！！！！！！！！！！

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_set_flow_good(void)
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
		
		case COMMAND_15_0001_O_2TANK_SET_FLOW_GOOD:
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
**名称：密闭管路处理策略
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

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_pipe_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_15_0001_O_2TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_15_0001_O_2TANK_VALVE_OFF_NO1:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0002_O_2TANK_IS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_15_0002_O_2TANK_IS_VALVE_OFF_NO1:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0003_O_2TANK_VALVE_ON_NO2;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0003_O_2TANK_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0004_O_2TANK_IS_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_15_0004_O_2TANK_IS_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0005_O_2TANK_5SEC_START;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_15_0005_O_2TANK_5SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0006_O_2TANK_IS_5SEC;
			
			break;
		}
		
		case COMMAND_15_0006_O_2TANK_IS_5SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0007_O_2TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0007_O_2TANK_VALVE_OFF_NO3:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0008_O_2TANK_IS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_15_0008_O_2TANK_IS_VALVE_OFF_NO3:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,6)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0009_O_2TANK_VALVE_OFF_NO4;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0009_O_2TANK_VALVE_OFF_NO4:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0010_O_2TANK_IS_VALVE_OFF_NO4;
			
			break;
		}
		
		case COMMAND_15_0010_O_2TANK_IS_VALVE_OFF_NO4:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,8)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0011_O_2TANK_VALVE_OFF_NO5;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0011_O_2TANK_VALVE_OFF_NO5:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0012_O_2TANK_IS_VALVE_OFF_NO5;
			
			break;
		}
		
		case COMMAND_15_0012_O_2TANK_IS_VALVE_OFF_NO5:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_O,10)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0013_O_2TANK_10SEC_START;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_15_0013_O_2TANK_10SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0014_O_2TANK_IS_10SEC;
			
			break;
		}
		
		case COMMAND_15_0014_O_2TANK_IS_10SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_10SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0015_O_2TANK_PIPE_GET_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0015_O_2TANK_PIPE_GET_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0016_O_2TANK_PIPE_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_15_0016_O_2TANK_PIPE_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0017_O_2TANK_PIPE_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_15_0017_O_2TANK_PIPE_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0018_O_2TANK_PIPE_GET_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0018_O_2TANK_PIPE_GET_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0019_O_2TANK_PIPE_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_15_0019_O_2TANK_PIPE_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0020_O_2TANK_PIPE_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_15_0020_O_2TANK_PIPE_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0021_O_2TANK_PIPE_GET_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0021_O_2TANK_PIPE_GET_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0022_O_2TANK_PIPE_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_15_0022_O_2TANK_PIPE_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0023_O_2TANK_PIPE_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_15_0023_O_2TANK_PIPE_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0024_O_2TANK_PIPE_GET_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0024_O_2TANK_PIPE_GET_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0025_O_2TANK_PIPE_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_15_0025_O_2TANK_PIPE_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0026_O_2TANK_PIPE_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_15_0026_O_2TANK_PIPE_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0027_O_2TANK_PIPE_GET_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0027_O_2TANK_PIPE_GET_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0028_O_2TANK_PIPE_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_15_0028_O_2TANK_PIPE_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0029_O_2TANK_PIPE_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_15_0029_O_2TANK_PIPE_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0030_O_2TANK_PIPE_GET_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0030_O_2TANK_PIPE_GET_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0031_O_2TANK_PIPE_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_15_0031_O_2TANK_PIPE_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0032_O_2TANK_PIPE_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_15_0032_O_2TANK_PIPE_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_15_0033_O_2TANK_PIPE_GET_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_15_0033_O_2TANK_PIPE_GET_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_15_0034_O_2TANK_PIPE_DEAL_PRESSURE;
			
			break;
		}
		
		case COMMAND_15_0034_O_2TANK_PIPE_DEAL_PRESSURE:
		{
			if(TGTHT510_supply_common_is_pipe_pressure_stable(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//补加接口管路压力不稳定
				TGTHT510_supply_main_pause(ERRNO_PIPE_PRESSURE_STABLE);
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


