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
void TGTHT510_supply_stage07_flow_f_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_07_F_FLOW_TANK_NUMBER;
			
			break;
		}

//--------------------------判断补加流动的贮箱数量-----------------------------------------		
		
		//判断补加流动的贮箱数量
		case STEP_07_F_FLOW_TANK_NUMBER:
		{
			TGTHT510_supply_stage07_flow_f_step_tank_number();
			break;
		}
				
//---------------------一个燃贮箱补加流动---------------------------------------
		
		//判断货船增压状态好
		case STEP_07_F_1TANK_IS_HYCT_GOOD:
		{
			if(TGTHT510_supply_stage07_flow_f_step_1tank_is_hyct_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开近浮动断接器阀门
		case STEP_07_F_1TANK_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage07_flow_f_step_1tank_interface_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_IS_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断近浮动断接器阀门开启是否正常
		case STEP_07_F_1TANK_IS_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage07_flow_f_step_1tank_is_interface_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_MIDDLE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开燃补加接口中间阀门
		case STEP_07_F_1TANK_MIDDLE_VALVE_ON:
		{
			if(TGTHT510_supply_stage07_flow_f_step_1tank_middle_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_DELAY1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待
		case STEP_07_F_1TANK_DELAY1:
		{
			if(TGTHT510_supply_stage07_flow_f_step_1tank_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_IS_PIPE_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断燃补加接口管路压力是否稳定
		case STEP_07_F_1TANK_IS_PIPE_PRESSURE:
		{
			if(TGTHT510_supply_stage07_flow_f_step_1tank_is_pipe_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开进贮箱补加液路阀门
		case STEP_07_F_1TANK_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage07_flow_f_step_1tank_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_IS_FLOW_CORRECT_V;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过补加速率判断补加过程是否正常
		case STEP_07_F_1TANK_IS_FLOW_CORRECT_V:
		{
			if(TGTHT510_supply_stage07_flow_f_step_1tank_is_flow_correct()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_IS_FLOW_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断补加是否到位
		case STEP_07_F_1TANK_IS_FLOW_OVER:
		{
			if(TGTHT510_supply_stage07_flow_f_step_1tank_is_flow_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_SET_FLOW_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//设置补加到位信息，发送货船
		case STEP_07_F_1TANK_SET_FLOW_GOOD:
		{
			if(TGTHT510_supply_stage07_flow_f_step_1tank_set_flow_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关进贮箱补加液路阀门
		case STEP_07_F_1TANK_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage07_flow_f_step_1tank_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_IS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断贮箱阀门关闭是否正常
		case STEP_07_F_1TANK_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage07_flow_f_step_1tank_is_valve_off_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_IS_NEED_FLOW_THIRD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断是否需对第三个贮箱继续补加
		case STEP_07_F_1TANK_IS_NEED_FLOW_THIRD:
		{
			TGTHT510_supply_stage07_flow_f_step_1tank_is_need_flow_third();
			
			break;
		}
		
		//密闭管路处理策略
		case STEP_07_F_1TANK_PIPE_DEAL:
		{
			if(TGTHT510_supply_stage07_flow_f_step_1tank_pipe_deal()==TRUE)
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
		case STEP_07_F_2TANK_IS_HYCT_GOOD:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_is_hyct_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开近浮动断接器阀门
		case STEP_07_F_2TANK_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_interface_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_IS_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断近浮动断接器阀门开启是否正常
		case STEP_07_F_2TANK_IS_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_is_interface_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_MIDDLE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开燃补加接口中间阀门
		case STEP_07_F_2TANK_MIDDLE_VALVE_ON:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_middle_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_DELAY1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待
		case STEP_07_F_2TANK_DELAY1:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_IS_PIPE_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断燃补加接口管路压力是否稳定
		case STEP_07_F_2TANK_IS_PIPE_PRESSURE:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_is_pipe_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_TANK1_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开进贮箱补加液路阀门，第一个贮箱
		case STEP_07_F_2TANK_TANK1_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_tank1_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_TANK1_IS_FLOW_CORRECT_V;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过补加速率判断补加过程是否正常，第一个贮箱
		case STEP_07_F_2TANK_TANK1_IS_FLOW_CORRECT_V:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_tank1_is_flow_correct()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_TANK1_IS_FLOW_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断补加是否到位，第一个贮箱
		case STEP_07_F_2TANK_TANK1_IS_FLOW_OVER:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_tank1_is_flow_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_TANK1_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关进贮箱补加液路阀门，第一个贮箱
		case STEP_07_F_2TANK_TANK1_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_tank1_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_TANK1_IS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断贮箱阀门关闭是否正常，第一个贮箱
		case STEP_07_F_2TANK_TANK1_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_tank1_is_valve_off_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_TANK2_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开进贮箱补加液路阀门，第二个贮箱
		case STEP_07_F_2TANK_TANK2_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_tank2_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_TANK2_IS_FLOW_CORRECT_V;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过补加速率判断补加过程是否正常，第二个贮箱
		case STEP_07_F_2TANK_TANK2_IS_FLOW_CORRECT_V:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_tank2_is_flow_correct()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_TANK2_IS_FLOW_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断补加是否到位，第二个贮箱
		case STEP_07_F_2TANK_TANK2_IS_FLOW_OVER:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_tank2_is_flow_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_SET_FLOW_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//设置补加到位信息，发送货船
		case STEP_07_F_2TANK_SET_FLOW_GOOD:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_set_flow_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_TANK2_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		
		//关进贮箱补加液路阀门，第二个贮箱
		case STEP_07_F_2TANK_TANK2_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_tank2_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_TANK2_IS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断贮箱阀门关闭是否正常，第二个贮箱
		case STEP_07_F_2TANK_TANK2_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_tank2_is_valve_off_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_IS_NEED_FLOW_THIRD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断是否需对第三个贮箱继续补加
		case STEP_07_F_2TANK_IS_NEED_FLOW_THIRD:
		{
			TGTHT510_supply_stage07_flow_f_step_2tank_is_need_flow_third();
			
			break;
		}
		
		//密闭管路处理策略
		case STEP_07_F_2TANK_PIPE_DEAL:
		{
			if(TGTHT510_supply_stage07_flow_f_step_2tank_pipe_deal()==TRUE)
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

void TGTHT510_supply_stage07_flow_f_step_tank_number(void)
{
	if(TGTHT510_supply_decode_par.number_tank_F==1)
	{
		TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_IS_HYCT_GOOD;
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
	
	else if((TGTHT510_supply_decode_par.number_tank_F==2)||\
	(TGTHT510_supply_decode_par.number_tank_F==3))
	{
		TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_IS_HYCT_GOOD;
			
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

uint16 TGTHT510_supply_stage07_flow_f_step_1tank_is_hyct_good(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_IS_HYCT_GOOD;
			break;
		}
		
		case COMMAND_07_0001_F_1TANK_IS_HYCT_GOOD:
		{
			if(TGTHT510_supply_common_is_hyct_good(FLOW_TANK_F)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_1tank_interface_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_INTERFACE_VALVE_ON;
			break;
		}
		
		case COMMAND_07_0001_F_1TANK_INTERFACE_VALVE_ON:
		{
			TGTHT510_supply_common_interface_valve_on(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_1TANK_IS_INTERFACE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_07_0002_F_1TANK_IS_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_common_is_interface_valve_on(FLOW_TANK_F)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_1tank_is_interface_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_INTERFACE_VALVE_ON_P;
			break;
		}
		
		case COMMAND_07_0001_F_1TANK_INTERFACE_VALVE_ON_P:
		{
			if(TGTHT510_supply_common_is_interface_valve_on_pressure(FLOW_TANK_F)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_1tank_middle_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_MIDDLE_VALVE_ON;
			break;
		}
		
		case COMMAND_07_0001_F_1TANK_MIDDLE_VALVE_ON:
		{
			TGTHT510_supply_common_middle_valve_on(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_1TANK_IS_MIDDLE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_07_0002_F_1TANK_IS_MIDDLE_VALVE_ON:
		{
			if(TGTHT510_supply_common_is_middle_valve_on(FLOW_TANK_F)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_1tank_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_DELAY1_START;
			break;
		}
		
		case COMMAND_07_0001_F_1TANK_DELAY1_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_1TANK_IS_DELAY1;
			
			break;
		}
		
		case COMMAND_07_0002_F_1TANK_IS_DELAY1:
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

uint16 TGTHT510_supply_stage07_flow_f_step_1tank_is_pipe_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_PIPE_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_07_0001_F_1TANK_PIPE_PRESSURE_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_1TANK_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_07_0002_F_1TANK_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0003_F_1TANK_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_07_0003_F_1TANK_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0004_F_1TANK_PIPE_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0004_F_1TANK_PIPE_PRESSURE_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0005_F_1TANK_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_07_0005_F_1TANK_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0006_F_1TANK_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_07_0006_F_1TANK_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0007_F_1TANK_PIPE_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0007_F_1TANK_PIPE_PRESSURE_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0008_F_1TANK_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_07_0008_F_1TANK_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0009_F_1TANK_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_07_0009_F_1TANK_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0010_F_1TANK_PIPE_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0010_F_1TANK_PIPE_PRESSURE_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0011_F_1TANK_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_07_0011_F_1TANK_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0012_F_1TANK_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_07_0012_F_1TANK_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0013_F_1TANK_PIPE_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0013_F_1TANK_PIPE_PRESSURE_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0014_F_1TANK_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_07_0014_F_1TANK_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0015_F_1TANK_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_07_0015_F_1TANK_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0016_F_1TANK_PIPE_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0016_F_1TANK_PIPE_PRESSURE_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0017_F_1TANK_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_07_0017_F_1TANK_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0018_F_1TANK_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_07_0018_F_1TANK_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0019_F_1TANK_PIPE_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0019_F_1TANK_PIPE_PRESSURE_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0020_F_1TANK_IS_PIPE_PRESSURE;
			
			break;
		}
		
		case COMMAND_07_0020_F_1TANK_IS_PIPE_PRESSURE:
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

uint16 TGTHT510_supply_stage07_flow_f_step_1tank_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_07_0001_F_1TANK_IN_TANK_VALVE_ON:
		{
			TGTHT510_supply_common_flow_in_tank_valve_on(FLOW_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_1TANK_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_07_0002_F_1TANK_IS_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_on(FLOW_TANK_F,FIRST_TANK)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_1tank_is_flow_correct(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_HTT_NO1;
			break;
		}
		
		case COMMAND_07_0001_F_1TANK_HTT_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_1TANK_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_07_0002_F_1TANK_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0003_F_1TANK_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_07_0003_F_1TANK_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0004_F_1TANK_HTT_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0004_F_1TANK_HTT_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0005_F_1TANK_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_07_0005_F_1TANK_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0006_F_1TANK_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_07_0006_F_1TANK_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0007_F_1TANK_HTT_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0007_F_1TANK_HTT_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0008_F_1TANK_IS_FLOW_CORRECT;
			
			break;
		}
		
		case COMMAND_07_0008_F_1TANK_IS_FLOW_CORRECT:
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

uint16 TGTHT510_supply_stage07_flow_f_step_1tank_is_flow_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_IS_FLOW_OVER_NO1;
			break;
		}
		
		case COMMAND_07_0001_F_1TANK_IS_FLOW_OVER_NO1:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_F,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_1TANK_IS_FLOW_OVER_NO2;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_07_0002_F_1TANK_IS_FLOW_OVER_NO2:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_F,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0003_F_1TANK_IS_FLOW_OVER_NO3;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_07_0003_F_1TANK_IS_FLOW_OVER_NO3:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_F,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_IS_FLOW_OVER_NO1;
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

uint16 TGTHT510_supply_stage07_flow_f_step_1tank_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_IN_TANK_VALVE_OFF;
			break;
		}
		
		case COMMAND_07_0001_F_1TANK_IN_TANK_VALVE_OFF:
		{
			TGTHT510_supply_common_flow_in_tank_valve_off(FLOW_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_1TANK_IS_IN_TANK_VALVE_OFF;
			
			break;
		}
		
		case COMMAND_07_0002_F_1TANK_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_off(FLOW_TANK_F,FIRST_TANK)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_1tank_is_valve_off_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_IS_PRESSURE;
			break;
		}
		
		case COMMAND_07_0001_F_1TANK_IS_PRESSURE:
		{
			if(TGTHT510_supply_common_is_tank_valve_off_pressure(FLOW_TANK_F,FIRST_TANK)==TRUE)
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

void TGTHT510_supply_stage07_flow_f_step_1tank_is_need_flow_third(void)
{
	if(TGTHT510_supply_decode_par.number_tank_F==3)
	{
		TGTHT510_supply_ctrl.step=STEP_END;//程序结束
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
			
	else
	{
		TGTHT510_supply_ctrl.step=STEP_07_F_1TANK_PIPE_DEAL;//程序继续
			
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

uint16 TGTHT510_supply_stage07_flow_f_step_1tank_set_flow_good(void)
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
		
		case COMMAND_07_0001_F_1TANK_SET_FLOW_GOOD:
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

uint16 TGTHT510_supply_stage07_flow_f_step_1tank_pipe_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_1TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_07_0001_F_1TANK_VALVE_OFF_NO1:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_1TANK_IS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_07_0002_F_1TANK_IS_VALVE_OFF_NO1:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0003_F_1TANK_VALVE_ON_NO2;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_07_0003_F_1TANK_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0004_F_1TANK_IS_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_07_0004_F_1TANK_IS_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0005_F_1TANK_5SEC_START;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_07_0005_F_1TANK_5SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0006_F_1TANK_IS_5SEC;
			
			break;
		}
		
		case COMMAND_07_0006_F_1TANK_IS_5SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0007_F_1TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0007_F_1TANK_VALVE_OFF_NO3:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0008_F_1TANK_IS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_07_0008_F_1TANK_IS_VALVE_OFF_NO3:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,6)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0009_F_1TANK_VALVE_OFF_NO4;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_07_0009_F_1TANK_VALVE_OFF_NO4:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0010_F_1TANK_IS_VALVE_OFF_NO4;
			
			break;
		}
		
		case COMMAND_07_0010_F_1TANK_IS_VALVE_OFF_NO4:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,8)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0011_F_1TANK_VALVE_OFF_NO5;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_07_0011_F_1TANK_VALVE_OFF_NO5:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0012_F_1TANK_IS_VALVE_OFF_NO5;
			
			break;
		}
		
		case COMMAND_07_0012_F_1TANK_IS_VALVE_OFF_NO5:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,10)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0013_F_1TANK_10SEC_START;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_07_0013_F_1TANK_10SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0014_F_1TANK_IS_10SEC;
			
			break;
		}
		
		case COMMAND_07_0014_F_1TANK_IS_10SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_10SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0015_F_1TANK_PIPE_GET_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0015_F_1TANK_PIPE_GET_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0016_F_1TANK_PIPE_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_07_0016_F_1TANK_PIPE_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0017_F_1TANK_PIPE_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_07_0017_F_1TANK_PIPE_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0018_F_1TANK_PIPE_GET_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0018_F_1TANK_PIPE_GET_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0019_F_1TANK_PIPE_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_07_0019_F_1TANK_PIPE_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0020_F_1TANK_PIPE_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_07_0020_F_1TANK_PIPE_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0021_F_1TANK_PIPE_GET_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0021_F_1TANK_PIPE_GET_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0022_F_1TANK_PIPE_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_07_0022_F_1TANK_PIPE_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0023_F_1TANK_PIPE_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_07_0023_F_1TANK_PIPE_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0024_F_1TANK_PIPE_GET_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0024_F_1TANK_PIPE_GET_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0025_F_1TANK_PIPE_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_07_0025_F_1TANK_PIPE_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0026_F_1TANK_PIPE_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_07_0026_F_1TANK_PIPE_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0027_F_1TANK_PIPE_GET_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0027_F_1TANK_PIPE_GET_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0028_F_1TANK_PIPE_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_07_0028_F_1TANK_PIPE_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0029_F_1TANK_PIPE_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_07_0029_F_1TANK_PIPE_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0030_F_1TANK_PIPE_GET_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0030_F_1TANK_PIPE_GET_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0031_F_1TANK_PIPE_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_07_0031_F_1TANK_PIPE_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0032_F_1TANK_PIPE_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_07_0032_F_1TANK_PIPE_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0033_F_1TANK_PIPE_GET_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0033_F_1TANK_PIPE_GET_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0034_F_1TANK_PIPE_DEAL_PRESSURE;
			
			break;
		}
		
		case COMMAND_07_0034_F_1TANK_PIPE_DEAL_PRESSURE:
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_is_hyct_good(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_IS_HYCT_GOOD;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_IS_HYCT_GOOD:
		{
			if(TGTHT510_supply_common_is_hyct_good(FLOW_TANK_F)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_interface_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_INTERFACE_VALVE_ON;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_INTERFACE_VALVE_ON:
		{
			TGTHT510_supply_common_interface_valve_on(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_2TANK_IS_INTERFACE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_07_0002_F_2TANK_IS_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_common_is_interface_valve_on(FLOW_TANK_F)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_is_interface_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_INTERFACE_VALVE_ON_P;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_INTERFACE_VALVE_ON_P:
		{
			if(TGTHT510_supply_common_is_interface_valve_on_pressure(FLOW_TANK_F)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_middle_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_MIDDLE_VALVE_ON;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_MIDDLE_VALVE_ON:
		{
			TGTHT510_supply_common_middle_valve_on(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_2TANK_IS_MIDDLE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_07_0002_F_2TANK_IS_MIDDLE_VALVE_ON:
		{
			if(TGTHT510_supply_common_is_middle_valve_on(FLOW_TANK_F)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_DELAY1_START;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_DELAY1_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_2TANK_IS_DELAY1;
			
			break;
		}
		
		case COMMAND_07_0002_F_2TANK_IS_DELAY1:
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_is_pipe_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_PIPE_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_PIPE_PRESSURE_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_2TANK_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_07_0002_F_2TANK_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0003_F_2TANK_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_07_0003_F_2TANK_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0004_F_2TANK_PIPE_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0004_F_2TANK_PIPE_PRESSURE_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0005_F_2TANK_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_07_0005_F_2TANK_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0006_F_2TANK_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_07_0006_F_2TANK_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0007_F_2TANK_PIPE_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0007_F_2TANK_PIPE_PRESSURE_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0008_F_2TANK_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_07_0008_F_2TANK_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0009_F_2TANK_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_07_0009_F_2TANK_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0010_F_2TANK_PIPE_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0010_F_2TANK_PIPE_PRESSURE_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0011_F_2TANK_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_07_0011_F_2TANK_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0012_F_2TANK_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_07_0012_F_2TANK_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0013_F_2TANK_PIPE_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0013_F_2TANK_PIPE_PRESSURE_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0014_F_2TANK_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_07_0014_F_2TANK_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0015_F_2TANK_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_07_0015_F_2TANK_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0016_F_2TANK_PIPE_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0016_F_2TANK_PIPE_PRESSURE_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0017_F_2TANK_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_07_0017_F_2TANK_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0018_F_2TANK_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_07_0018_F_2TANK_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0019_F_2TANK_PIPE_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0019_F_2TANK_PIPE_PRESSURE_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0020_F_2TANK_IS_PIPE_PRESSURE;
			
			break;
		}
		
		case COMMAND_07_0020_F_2TANK_IS_PIPE_PRESSURE:
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_tank1_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK1_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_TANK1_IN_TANK_VALVE_ON:
		{
			TGTHT510_supply_common_flow_in_tank_valve_on(FLOW_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_2TANK_TANK1_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_07_0002_F_2TANK_TANK1_IS_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_on(FLOW_TANK_F,FIRST_TANK)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_tank1_is_flow_correct(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK1_HTT_NO1;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_TANK1_HTT_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_2TANK_TANK1_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_07_0002_F_2TANK_TANK1_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0003_F_2TANK_TANK1_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_07_0003_F_2TANK_TANK1_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0004_F_2TANK_TANK1_HTT_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0004_F_2TANK_TANK1_HTT_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0005_F_2TANK_TANK1_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_07_0005_F_2TANK_TANK1_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0006_F_2TANK_TANK1_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_07_0006_F_2TANK_TANK1_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0007_F_2TANK_TANK1_HTT_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0007_F_2TANK_TANK1_HTT_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0008_F_2TANK_TANK1_IS_FLOW_CORRECT;
			
			break;
		}
		
		case COMMAND_07_0008_F_2TANK_TANK1_IS_FLOW_CORRECT:
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_tank1_is_flow_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK1_IS_FLOW_OVER_NO1;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_TANK1_IS_FLOW_OVER_NO1:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_F,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_2TANK_TANK1_IS_FLOW_OVER_NO2;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK1_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_07_0002_F_2TANK_TANK1_IS_FLOW_OVER_NO2:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_F,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0003_F_2TANK_TANK1_IS_FLOW_OVER_NO3;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK1_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_07_0003_F_2TANK_TANK1_IS_FLOW_OVER_NO3:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_F,FIRST_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK1_IS_FLOW_OVER_NO1;
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_tank1_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK1_IN_TANK_VALVE_OFF;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_TANK1_IN_TANK_VALVE_OFF:
		{
			TGTHT510_supply_common_flow_in_tank_valve_off(FLOW_TANK_F,FIRST_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_2TANK_TANK1_IS_IN_TANK_VALVE_OFF;
			
			break;
		}
		
		case COMMAND_07_0002_F_2TANK_TANK1_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_off(FLOW_TANK_F,FIRST_TANK)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_tank1_is_valve_off_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK1_IS_PRESSURE;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_TANK1_IS_PRESSURE:
		{
			if(TGTHT510_supply_common_is_tank_valve_off_pressure(FLOW_TANK_F,FIRST_TANK)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_tank2_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK2_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_TANK2_IN_TANK_VALVE_ON:
		{
			TGTHT510_supply_common_flow_in_tank_valve_on(FLOW_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_2TANK_TANK2_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_07_0002_F_2TANK_TANK2_IS_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_on(FLOW_TANK_F,SECOND_TANK)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_tank2_is_flow_correct(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK2_HTT_NO1;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_TANK2_HTT_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_2TANK_TANK2_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_07_0002_F_2TANK_TANK2_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0003_F_2TANK_TANK2_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_07_0003_F_2TANK_TANK2_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0004_F_2TANK_TANK2_HTT_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0004_F_2TANK_TANK2_HTT_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0005_F_2TANK_TANK2_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_07_0005_F_2TANK_TANK2_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0006_F_2TANK_TANK2_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_07_0006_F_2TANK_TANK2_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0007_F_2TANK_TANK2_HTT_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0007_F_2TANK_TANK2_HTT_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0008_F_2TANK_TANK2_IS_FLOW_CORRECT;
			
			break;
		}
		
		case COMMAND_07_0008_F_2TANK_TANK2_IS_FLOW_CORRECT:
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_tank2_is_flow_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK2_IS_FLOW_OVER_NO1;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_TANK2_IS_FLOW_OVER_NO1:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_F,SECOND_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_2TANK_TANK2_IS_FLOW_OVER_NO2;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK2_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_07_0002_F_2TANK_TANK2_IS_FLOW_OVER_NO2:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_F,SECOND_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0003_F_2TANK_TANK2_IS_FLOW_OVER_NO3;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK2_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_07_0003_F_2TANK_TANK2_IS_FLOW_OVER_NO3:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_F,SECOND_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK2_IS_FLOW_OVER_NO1;
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_tank2_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK2_IN_TANK_VALVE_OFF;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_TANK2_IN_TANK_VALVE_OFF:
		{
			TGTHT510_supply_common_flow_in_tank_valve_off(FLOW_TANK_F,SECOND_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_2TANK_TANK2_IS_IN_TANK_VALVE_OFF;
			
			break;
		}
		
		case COMMAND_07_0002_F_2TANK_TANK2_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_off(FLOW_TANK_F,SECOND_TANK)==TRUE)
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_tank2_is_valve_off_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_TANK2_IS_PRESSURE;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_TANK2_IS_PRESSURE:
		{
			if(TGTHT510_supply_common_is_tank_valve_off_pressure(FLOW_TANK_F,SECOND_TANK)==TRUE)
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

void TGTHT510_supply_stage07_flow_f_step_2tank_is_need_flow_third(void)
{
	if(TGTHT510_supply_decode_par.number_tank_F==3)
	{
		TGTHT510_supply_ctrl.step=STEP_END;//程序结束
			
		TGTHT510_supply_ctrl.command=COMMAND_START;
	}
			
	else
	{
		TGTHT510_supply_ctrl.step=STEP_07_F_2TANK_PIPE_DEAL;//程序继续
			
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_set_flow_good(void)
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
		
		case COMMAND_07_0001_F_2TANK_SET_FLOW_GOOD:
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

uint16 TGTHT510_supply_stage07_flow_f_step_2tank_pipe_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_07_0001_F_2TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_07_0001_F_2TANK_VALVE_OFF_NO1:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0002_F_2TANK_IS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_07_0002_F_2TANK_IS_VALVE_OFF_NO1:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0003_F_2TANK_VALVE_ON_NO2;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_07_0003_F_2TANK_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0004_F_2TANK_IS_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_07_0004_F_2TANK_IS_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0005_F_2TANK_5SEC_START;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_07_0005_F_2TANK_5SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0006_F_2TANK_IS_5SEC;
			
			break;
		}
		
		case COMMAND_07_0006_F_2TANK_IS_5SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0007_F_2TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0007_F_2TANK_VALVE_OFF_NO3:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0008_F_2TANK_IS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_07_0008_F_2TANK_IS_VALVE_OFF_NO3:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,6)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0009_F_2TANK_VALVE_OFF_NO4;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_07_0009_F_2TANK_VALVE_OFF_NO4:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0010_F_2TANK_IS_VALVE_OFF_NO4;
			
			break;
		}
		
		case COMMAND_07_0010_F_2TANK_IS_VALVE_OFF_NO4:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,8)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0011_F_2TANK_VALVE_OFF_NO5;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_07_0011_F_2TANK_VALVE_OFF_NO5:
		{
			TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0012_F_2TANK_IS_VALVE_OFF_NO5;
			
			break;
		}
		
		case COMMAND_07_0012_F_2TANK_IS_VALVE_OFF_NO5:
		{
			if(TGTHT510_supply_common_flow_pipe_deal(FLOW_TANK_F,10)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0013_F_2TANK_10SEC_START;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_07_0013_F_2TANK_10SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0014_F_2TANK_IS_10SEC;
			
			break;
		}
		
		case COMMAND_07_0014_F_2TANK_IS_10SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_10SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0015_F_2TANK_PIPE_GET_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0015_F_2TANK_PIPE_GET_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0016_F_2TANK_PIPE_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_07_0016_F_2TANK_PIPE_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0017_F_2TANK_PIPE_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_07_0017_F_2TANK_PIPE_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0018_F_2TANK_PIPE_GET_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0018_F_2TANK_PIPE_GET_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0019_F_2TANK_PIPE_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_07_0019_F_2TANK_PIPE_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0020_F_2TANK_PIPE_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_07_0020_F_2TANK_PIPE_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0021_F_2TANK_PIPE_GET_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0021_F_2TANK_PIPE_GET_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0022_F_2TANK_PIPE_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_07_0022_F_2TANK_PIPE_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0023_F_2TANK_PIPE_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_07_0023_F_2TANK_PIPE_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0024_F_2TANK_PIPE_GET_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0024_F_2TANK_PIPE_GET_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0025_F_2TANK_PIPE_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_07_0025_F_2TANK_PIPE_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0026_F_2TANK_PIPE_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_07_0026_F_2TANK_PIPE_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0027_F_2TANK_PIPE_GET_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0027_F_2TANK_PIPE_GET_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0028_F_2TANK_PIPE_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_07_0028_F_2TANK_PIPE_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0029_F_2TANK_PIPE_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_07_0029_F_2TANK_PIPE_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0030_F_2TANK_PIPE_GET_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0030_F_2TANK_PIPE_GET_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0031_F_2TANK_PIPE_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_07_0031_F_2TANK_PIPE_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0032_F_2TANK_PIPE_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_07_0032_F_2TANK_PIPE_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_07_0033_F_2TANK_PIPE_GET_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_07_0033_F_2TANK_PIPE_GET_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_07_0034_F_2TANK_PIPE_DEAL_PRESSURE;
			
			break;
		}
		
		case COMMAND_07_0034_F_2TANK_PIPE_DEAL_PRESSURE:
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
**名称: 通用函数-取中间值
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_middle_get(uint16 a,uint16 b,uint16 c)
{
	uint16 v[3];
	uint16 d;
	
	v[0]=a;
	v[1]=b;
	v[2]=c;
	
	if(v[0]>v[1])
	{
		d=v[1];
		v[1]=v[0];
		v[0]=d;
	}
	
	if(v[0]>v[2])
	{
		d=v[2];
		v[2]=v[0];
		v[0]=d;
	}
	
	if(v[1]>v[2])
	{
		d=v[2];
		v[2]=v[1];
		v[1]=d;
	}
	
	return v[1];
}


/******************************************************************************************
**名称: 通用函数-取最大值
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_max_get(uint16 a,uint16 b,uint16 c)
{
	uint16 v[3];
	uint16 d;
	
	v[0]=a;
	v[1]=b;
	v[2]=c;
	
	if(v[0]>v[1])
	{
		d=v[1];
		v[1]=v[0];
		v[0]=d;
	}
	
	if(v[0]>v[2])
	{
		d=v[2];
		v[2]=v[0];
		v[0]=d;
	}
	
	if(v[1]>v[2])
	{
		d=v[2];
		v[2]=v[1];
		v[1]=d;
	}
	
	return v[2];
}




/******************************************************************************************
**名称: 通用函数-判断货船增压状态
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_is_hyct_good(uint16 flow_kind)
{
	uint16 p_hyct;
	
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)||\
		(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3))
		{
			//货船参数PTb12、14、16
			p_hyct=TGTHT510_supply_common_middle_get(TGTHT510_1553B_R_HYCT1100[4],\
			TGTHT510_1553B_R_HYCT1100[5],TGTHT510_1553B_R_HYCT1100[9]);
		}
		
		else if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)||\
		(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4))
		{
			//货船参数PTb18、20、22
			p_hyct=TGTHT510_supply_common_middle_get(TGTHT510_1553B_R_HYCT1100[6],\
			TGTHT510_1553B_R_HYCT1100[7],TGTHT510_1553B_R_HYCT1100[11]);
		}
		
		else
		{
			return FALSE;
		}
		
		if(p_hyct>=TGTHT510_supply_input_par.pressure_hyc)
		{
			return TRUE;
		}
		
		else
		{
			return FALSE;
		}
	
	}
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if((TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)||\
		(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3))
		{
			//货船参数PTb11、13、15
			p_hyct=TGTHT510_supply_common_middle_get(TGTHT510_1553B_R_HYCT1100[0],\
			TGTHT510_1553B_R_HYCT1100[1],TGTHT510_1553B_R_HYCT1100[8]);
		}
		
		else if((TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)||\
		(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4))
		{
			//货船参数PTb17、19、21
			p_hyct=TGTHT510_supply_common_middle_get(TGTHT510_1553B_R_HYCT1100[2],\
			TGTHT510_1553B_R_HYCT1100[3],TGTHT510_1553B_R_HYCT1100[10]);
		}
		
		else
		{
			return FALSE;
		}
		
		if(p_hyct>=TGTHT510_supply_input_par.pressure_hyc)
		{
			return TRUE;
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else
	{
		return FALSE;
	}
}


/******************************************************************************************
**名称: 通用函数-开近浮动断接器阀门
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_common_interface_valve_on(uint16 flow_kind)
{
	
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			TGTHT510_supply_main_lvb_set(LVb40K);
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
		{
			TGTHT510_supply_main_lvb_set(LVb50K);
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
		{
			TGTHT510_supply_main_lvb_set(LVb64K);
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
		{
			TGTHT510_supply_main_lvb_set(LVb60K);
		}
		
		else
		{
			//补加注入参数解码错误
			TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
		}
		
	}
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			TGTHT510_supply_main_lvb_set(LVb39K);
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
		{
			TGTHT510_supply_main_lvb_set(LVb49K);
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
		{
			TGTHT510_supply_main_lvb_set(LVb63K);
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
		{
			TGTHT510_supply_main_lvb_set(LVb59K);
		}
		
		else
		{
			//补加注入参数解码错误
			TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
		}
	}
	
	else
	{
		//内部函数输入参数错误
		TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);
	}

}


/******************************************************************************************
**名称: 通用函数-判断开近浮动断接器阀门
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_is_interface_valve_on(uint16 flow_kind)
{
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb40,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb50,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb64,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb60,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb39,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb49,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb63,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb59,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else
		{
			return FALSE;
		}
	}
	
	else
	{
		return FALSE;
	}

}


/******************************************************************************************
**名称: 通用函数-通过压力判断开近浮动断接器阀门
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_is_interface_valve_on_pressure(uint16 flow_kind)
{
	uint16 p_core;
	uint16 p_hyct;
	
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			//货船参数PTb12、14、16
			p_hyct=TGTHT510_supply_common_middle_get(TGTHT510_1553B_R_HYCT1100[4],\
			TGTHT510_1553B_R_HYCT1100[5],TGTHT510_1553B_R_HYCT1100[9]);
			
			//核心舱PTb22
			p_core=TGTHT510_1553B_data_TGTHT100[55];
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
		{
			//货船参数PTb18、20、22
			p_hyct=TGTHT510_supply_common_middle_get(TGTHT510_1553B_R_HYCT1100[6],\
			TGTHT510_1553B_R_HYCT1100[7],TGTHT510_1553B_R_HYCT1100[11]);
			
			//核心舱PTb18
			p_core=TGTHT510_1553B_data_TGTHT100[51];
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
		{
			//货船参数PTb12、14、16
			p_hyct=TGTHT510_supply_common_middle_get(TGTHT510_1553B_R_HYCT1100[4],\
			TGTHT510_1553B_R_HYCT1100[5],TGTHT510_1553B_R_HYCT1100[9]);
			
			//核心舱PTb20
			p_core=TGTHT510_1553B_data_TGTHT100[53];
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
		{
			//货船参数PTb18、20、22
			p_hyct=TGTHT510_supply_common_middle_get(TGTHT510_1553B_R_HYCT1100[6],\
			TGTHT510_1553B_R_HYCT1100[7],TGTHT510_1553B_R_HYCT1100[11]);
			
			//核心舱PTb16
			p_core=TGTHT510_1553B_data_TGTHT100[49];
		}
		
		else
		{
			return FALSE;
		}
		
		if((uint16)(abs(p_hyct-p_core))<=TGTHT510_supply_input_par.eps1)
		{
			return TRUE;
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			//货船参数PTb11、13、15
			p_hyct=TGTHT510_supply_common_middle_get(TGTHT510_1553B_R_HYCT1100[0],\
			TGTHT510_1553B_R_HYCT1100[1],TGTHT510_1553B_R_HYCT1100[8]);
			
			//核心舱PTb21
			p_core=TGTHT510_1553B_data_TGTHT100[54];
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
		{
			//货船参数PTb17、19、21
			p_hyct=TGTHT510_supply_common_middle_get(TGTHT510_1553B_R_HYCT1100[2],\
			TGTHT510_1553B_R_HYCT1100[3],TGTHT510_1553B_R_HYCT1100[10]);
			
			//核心舱PTb17
			p_core=TGTHT510_1553B_data_TGTHT100[50];
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
		{
			//货船参数PTb11、13、15
			p_hyct=TGTHT510_supply_common_middle_get(TGTHT510_1553B_R_HYCT1100[0],\
			TGTHT510_1553B_R_HYCT1100[1],TGTHT510_1553B_R_HYCT1100[8]);
			
			//核心舱PTb19
			p_core=TGTHT510_1553B_data_TGTHT100[52];
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
		{
			//货船参数PTb17、19、21
			p_hyct=TGTHT510_supply_common_middle_get(TGTHT510_1553B_R_HYCT1100[2],\
			TGTHT510_1553B_R_HYCT1100[3],TGTHT510_1553B_R_HYCT1100[10]);
			
			//核心舱PTb15
			p_core=TGTHT510_1553B_data_TGTHT100[48];
		}
		
		else
		{
			return FALSE;
		}
		
		if((uint16)(abs(p_hyct-p_core))<=TGTHT510_supply_input_par.eps1)
		{
			return TRUE;
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**名称: 通用函数-开燃补加接口中间阀门
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_common_middle_valve_on(uint16 flow_kind)
{
	
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			TGTHT510_supply_main_lvb_set(LVb42K);
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
		{
			TGTHT510_supply_main_lvb_set(LVb52K);
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
		{
			TGTHT510_supply_main_lvb_set(LVb66K);
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
		{
			TGTHT510_supply_main_lvb_set(LVb62K);
		}
		
		else
		{
			//补加注入参数解码错误
			TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
		}
		
	}
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			TGTHT510_supply_main_lvb_set(LVb41K);
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
		{
			TGTHT510_supply_main_lvb_set(LVb51K);
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
		{
			TGTHT510_supply_main_lvb_set(LVb65K);
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
		{
			TGTHT510_supply_main_lvb_set(LVb61K);
		}
		
		else
		{
			//补加注入参数解码错误
			TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
		}
	}
	
	else
	{
		//内部函数输入参数错误
		TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);
	}

}



/******************************************************************************************
**名称: 通用函数-判断开燃补加接口中间阀门
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_is_middle_valve_on(uint16 flow_kind)
{
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb42,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb52,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb66,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb62,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb41,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb51,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb65,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb61,VALVE_ON)==TRUE)
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else
		{
			return FALSE;
		}
	}
	
	else
	{
		return FALSE;
	}

}


/******************************************************************************************
**名称: 通用函数-补加接口管路压力获取
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_pipe_pressure_get(uint16 flow_kind)
{
	uint16 a,b,c,d;
	
	uint16 e;
	
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			//货船参数PTb12、14、16，核心舱参数PTb22的平均值
			a=TGTHT510_1553B_R_HYCT1100[4];
			b=TGTHT510_1553B_R_HYCT1100[5];
			c=TGTHT510_1553B_R_HYCT1100[9];
			d=TGTHT510_1553B_data_TGTHT100[55];
			
			e=(uint16)(((uint32)(a)+(uint32)(b)+(uint32)(c)+(uint32)(d))>>4);	
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
		{
			//货船参数PTb18、20、22，核心舱参数PTb18的平均值
			a=TGTHT510_1553B_R_HYCT1100[6];
			b=TGTHT510_1553B_R_HYCT1100[7];
			c=TGTHT510_1553B_R_HYCT1100[11];
			d=TGTHT510_1553B_data_TGTHT100[51];
			
			e=(uint16)(((uint32)(a)+(uint32)(b)+(uint32)(c)+(uint32)(d))>>4);
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
		{
			//货船参数PTb12、14、16，核心舱参数PTb20的平均值
			a=TGTHT510_1553B_R_HYCT1100[4];
			b=TGTHT510_1553B_R_HYCT1100[5];
			c=TGTHT510_1553B_R_HYCT1100[9];
			d=TGTHT510_1553B_data_TGTHT100[53];
			
			e=(uint16)(((uint32)(a)+(uint32)(b)+(uint32)(c)+(uint32)(d))>>4);
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
		{
			//货船参数PTb18、20、22，核心舱参数PTb16的平均值
			a=TGTHT510_1553B_R_HYCT1100[6];
			b=TGTHT510_1553B_R_HYCT1100[7];
			c=TGTHT510_1553B_R_HYCT1100[11];
			d=TGTHT510_1553B_data_TGTHT100[49];
			
			e=(uint16)(((uint32)(a)+(uint32)(b)+(uint32)(c)+(uint32)(d))>>4);
		}
		
		else
		{
			return 0;
		}
		
	}
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			//货船参数PTb11、13、15，核心舱参数PTb21的平均值
			a=TGTHT510_1553B_R_HYCT1100[0];
			b=TGTHT510_1553B_R_HYCT1100[1];
			c=TGTHT510_1553B_R_HYCT1100[8];
			d=TGTHT510_1553B_data_TGTHT100[54];
			
			e=(uint16)(((uint32)(a)+(uint32)(b)+(uint32)(c)+(uint32)(d))>>4);
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
		{
			//货船参数PTb17、19、21，核心舱参数PTb17的平均值
			a=TGTHT510_1553B_R_HYCT1100[2];
			b=TGTHT510_1553B_R_HYCT1100[3];
			c=TGTHT510_1553B_R_HYCT1100[10];
			d=TGTHT510_1553B_data_TGTHT100[50];
			
			e=(uint16)(((uint32)(a)+(uint32)(b)+(uint32)(c)+(uint32)(d))>>4);
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
		{
			//货船参数PTb11、13、15，核心舱参数PTb19的平均值
			a=TGTHT510_1553B_R_HYCT1100[0];
			b=TGTHT510_1553B_R_HYCT1100[1];
			c=TGTHT510_1553B_R_HYCT1100[8];
			d=TGTHT510_1553B_data_TGTHT100[52];
			
			e=(uint16)(((uint32)(a)+(uint32)(b)+(uint32)(c)+(uint32)(d))>>4);
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
		{
			//货船参数PTb17、19、21，核心舱参数PTb15的平均值
			a=TGTHT510_1553B_R_HYCT1100[2];
			b=TGTHT510_1553B_R_HYCT1100[3];
			c=TGTHT510_1553B_R_HYCT1100[10];
			d=TGTHT510_1553B_data_TGTHT100[48];
			
			e=(uint16)(((uint32)(a)+(uint32)(b)+(uint32)(c)+(uint32)(d))>>4);
		}
		
		else
		{
			return 0;
		}
	}
	
	else
	{
		return 0;
	}
	
	return e;

}

/******************************************************************************************
**名称: 通用函数-判断管路压力值是否稳定
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_is_pipe_pressure_stable(uint16 *p)
{
	uint16 n,i;
	
	n=0;
	
	for(i=0;i<=5;i++)
	{
		if((uint16)(abs(p[i+1]-p[i]))<=TGTHT510_supply_input_par.dp1_low)
		{
			n++;
		}
		
		else
		{
			asm("nop;");
		}
		
	}
	
	if((n>=5)&&(n<=6))
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}


/******************************************************************************************
**名称: 通用函数-开进贮箱补加液路阀门
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_common_flow_in_tank_valve_on(uint16 flow_kind,uint16 tank_sequence)
{
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb44K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb54K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb44K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb54K);
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb46K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb56K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb46K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb56K);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb48K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb58K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb48K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb58K);
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
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb44K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb54K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb44K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb54K);
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb46K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb56K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb46K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb56K);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb48K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb58K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb48K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb58K);
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
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb44K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb54K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb44K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb54K);
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb46K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb56K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb46K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb56K);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb48K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb58K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb48K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb58K);
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
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb43K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb53K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb43K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb53K);
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb45K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb55K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb45K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb55K);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb47K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb57K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb47K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb57K);
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
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb43K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb53K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb43K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb53K);
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb45K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb55K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb45K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb55K);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb47K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb57K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb47K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb57K);
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
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb43K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb53K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb43K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb53K);
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb45K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb55K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb45K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb55K);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb47K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb57K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb47K);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb57K);
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

/******************************************************************************************
**名称: 通用函数-判断开进贮箱补加液路阀门
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_flow_is_in_tank_valve_on(uint16 flow_kind,uint16 tank_sequence)
{
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else
	{
		return FALSE;
	}

}

/******************************************************************************************
**名称: 通用函数-获取位移剩余量
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_flow_htt_get(uint16 flow_kind,uint16 tank_sequence)
{
	uint16 a,b,c;
	
	uint16 m;
	
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				//核心舱参数HTt10、11、12
				a=TGTHT510_1553B_data_TGTHT100[70];
				b=TGTHT510_1553B_data_TGTHT100[71];
				c=TGTHT510_1553B_data_TGTHT100[72];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				//核心舱参数HTt13、14、15
				a=TGTHT510_1553B_data_TGTHT100[73];
				b=TGTHT510_1553B_data_TGTHT100[74];
				c=TGTHT510_1553B_data_TGTHT100[75];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				//核心舱参数HTt16、17、18
				a=TGTHT510_1553B_data_TGTHT100[76];
				b=TGTHT510_1553B_data_TGTHT100[77];
				c=TGTHT510_1553B_data_TGTHT100[78];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else
			{
				asm("nop;");
			}
			
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				//核心舱参数HTt10、11、12
				a=TGTHT510_1553B_data_TGTHT100[70];
				b=TGTHT510_1553B_data_TGTHT100[71];
				c=TGTHT510_1553B_data_TGTHT100[72];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				//核心舱参数HTt13、14、15
				a=TGTHT510_1553B_data_TGTHT100[73];
				b=TGTHT510_1553B_data_TGTHT100[74];
				c=TGTHT510_1553B_data_TGTHT100[75];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				//核心舱参数HTt16、17、18
				a=TGTHT510_1553B_data_TGTHT100[76];
				b=TGTHT510_1553B_data_TGTHT100[77];
				c=TGTHT510_1553B_data_TGTHT100[78];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else
			{
				asm("nop;");
			}
			
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				//核心舱参数HTt10、11、12
				a=TGTHT510_1553B_data_TGTHT100[70];
				b=TGTHT510_1553B_data_TGTHT100[71];
				c=TGTHT510_1553B_data_TGTHT100[72];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				//核心舱参数HTt13、14、15
				a=TGTHT510_1553B_data_TGTHT100[73];
				b=TGTHT510_1553B_data_TGTHT100[74];
				c=TGTHT510_1553B_data_TGTHT100[75];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				//核心舱参数HTt16、17、18
				a=TGTHT510_1553B_data_TGTHT100[76];
				b=TGTHT510_1553B_data_TGTHT100[77];
				c=TGTHT510_1553B_data_TGTHT100[78];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else
			{
				return 0;
			}
			
		}
		
		else
		{
			return 0;
		}
		
	}
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				//核心舱参数HTt1、2、3
				a=TGTHT510_1553B_data_TGTHT100[61];
				b=TGTHT510_1553B_data_TGTHT100[62];
				c=TGTHT510_1553B_data_TGTHT100[63];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				//核心舱参数HTt4、5、6
				a=TGTHT510_1553B_data_TGTHT100[64];
				b=TGTHT510_1553B_data_TGTHT100[65];
				c=TGTHT510_1553B_data_TGTHT100[66];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				//核心舱参数HTt7、8、9
				a=TGTHT510_1553B_data_TGTHT100[67];
				b=TGTHT510_1553B_data_TGTHT100[68];
				c=TGTHT510_1553B_data_TGTHT100[69];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else
			{
				return 0;
			}
			
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				//核心舱参数HTt1、2、3
				a=TGTHT510_1553B_data_TGTHT100[61];
				b=TGTHT510_1553B_data_TGTHT100[62];
				c=TGTHT510_1553B_data_TGTHT100[63];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				//核心舱参数HTt4、5、6
				a=TGTHT510_1553B_data_TGTHT100[64];
				b=TGTHT510_1553B_data_TGTHT100[65];
				c=TGTHT510_1553B_data_TGTHT100[66];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				//核心舱参数HTt7、8、9
				a=TGTHT510_1553B_data_TGTHT100[67];
				b=TGTHT510_1553B_data_TGTHT100[68];
				c=TGTHT510_1553B_data_TGTHT100[69];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else
			{
				return 0;
			}
			
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				//核心舱参数HTt1、2、3
				a=TGTHT510_1553B_data_TGTHT100[61];
				b=TGTHT510_1553B_data_TGTHT100[62];
				c=TGTHT510_1553B_data_TGTHT100[63];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				//核心舱参数HTt4、5、6
				a=TGTHT510_1553B_data_TGTHT100[64];
				b=TGTHT510_1553B_data_TGTHT100[65];
				c=TGTHT510_1553B_data_TGTHT100[66];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				//核心舱参数HTt7、8、9
				a=TGTHT510_1553B_data_TGTHT100[67];
				b=TGTHT510_1553B_data_TGTHT100[68];
				c=TGTHT510_1553B_data_TGTHT100[69];
				m=TGTHT510_supply_common_max_get(a,b,c);
				
				return m;
			}
			
			else
			{
				return 0;
			}
			
		}
		
		else
		{
			return 0;
		}
		
	}
	
	else
	{
		return 0;
	}

}

/******************************************************************************************
**名称: 通用函数-通过速率判断补加过程是否正常
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_is_flow_correct(uint16 *p)
{
	if((p[1]>p[0])&&(p[2]>p[1]))
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**名称: 通用函数-判断是否到位
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_is_flow_over(uint16 flow_kind,uint16 tank_sequence)
{
	uint16 htt;
	
	htt=TGTHT510_supply_common_flow_htt_get(flow_kind,tank_sequence);
	
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_F1))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_F2))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_F3))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_F1))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_F2))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_F3))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_F1))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_F2))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_F3))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_O1))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_O2))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_O3))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_O1))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_O2))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_O3))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_O1))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_O2))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				if((uint16)(abs(htt-TGTHT510_supply_input_par.volum_O3))<=TGTHT510_supply_input_par.eps2)
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else
	{
		return FALSE;
	}

}


/******************************************************************************************
**名称: 通用函数-关进贮箱补加液路阀门
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_common_flow_in_tank_valve_off(uint16 flow_kind,uint16 tank_sequence)
{
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb44G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb54G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb44G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb54G);
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb46G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb56G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb46G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb56G);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb48G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb58G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb48G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb58G);
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
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb44G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb54G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb44G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb54G);
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb46G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb56G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb46G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb56G);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb48G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb58G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb48G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb58G);
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
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb44G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb54G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb44G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb54G);
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb46G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb56G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb46G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb56G);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					TGTHT510_supply_main_lvb_set(LVb48G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					TGTHT510_supply_main_lvb_set(LVb58G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					TGTHT510_supply_main_lvb_set(LVb48G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					TGTHT510_supply_main_lvb_set(LVb58G);
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
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb43G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb53G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb43G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb53G);
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb45G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb55G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb45G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb55G);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb47G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb57G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb47G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb57G);
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
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb43G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb53G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb43G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb53G);
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb45G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb55G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb45G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb55G);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb47G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb57G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb47G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb57G);
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
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb43G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb53G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb43G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb53G);
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb45G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb55G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb45G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb55G);
				}
				
				else
				{
					asm("nop;");
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					TGTHT510_supply_main_lvb_set(LVb47G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					TGTHT510_supply_main_lvb_set(LVb57G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					TGTHT510_supply_main_lvb_set(LVb47G);
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					TGTHT510_supply_main_lvb_set(LVb57G);
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

/******************************************************************************************
**名称: 通用函数-判断关进贮箱补加液路阀门
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_flow_is_in_tank_valve_off(uint16 flow_kind,uint16 tank_sequence)
{
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb44,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb54,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb46,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb56,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb48,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb58,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if(tank_sequence==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else if(tank_sequence==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else if(tank_sequence==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb43,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb53,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb45,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb55,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb47,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb57,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
				}
				
				else
				{
					return FALSE;
				}
			}
			
			else
			{
				return FALSE;
			}
			
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else
	{
		return FALSE;
	}

}

/******************************************************************************************
**名称: 通用函数-密闭管路处理部分指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
正常，则返回TRUE，
否则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_flow_pipe_deal(uint16 flow_kind,uint16 command_number)
{
	if(flow_kind==FLOW_TANK_F)//燃贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb40G);
					
					return TRUE;
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb40,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb72K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb72,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb72G);
					
					return TRUE;
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb72,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb76G);
					
					return TRUE;
					
					break;
				}
				
				case 8:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb76,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb42G);
					
					return TRUE;
					
					break;
				}
				
				case 10:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb42,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
				
			}
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb50G);
					
					return TRUE;
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb50,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb68K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb68,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb68G);
					
					return TRUE;
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb68,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb78G);
					
					return TRUE;
					
					break;
				}
				
				case 8:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb78,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb52G);
					
					return TRUE;
					
					break;
				}
				
				case 10:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb52,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
			}
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb64G);
					
					return TRUE;
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb64,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb80K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb80,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb80G);
					
					return TRUE;
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb80,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb82G);
					
					return TRUE;
					
					break;
				}
				
				case 8:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb82,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb66G);
					
					return TRUE;
					
					break;
				}
				
				case 10:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb66,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
				
			}
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb60G);
					
					return TRUE;
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb60,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb84K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb84,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb84G);
					
					return TRUE;
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb84,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb86G);
					
					return TRUE;
					
					break;
				}
				
				case 8:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb86,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb62G);
					
					return TRUE;
					
					break;
				}
				
				case 10:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb62,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
				
			}
			
		}
		
		else
		{
			return FALSE;
		}
		
	}
	
	else if(flow_kind==FLOW_TANK_O)//氧贮箱流动
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb39G);
					
					return TRUE;
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb39,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb71K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb71,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb71G);
					
					return TRUE;
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb71,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb75G);
					
					return TRUE;
					
					break;
				}
				
				case 8:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb75,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb41G);
					
					return TRUE;
					
					break;
				}
				
				case 10:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb41,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
				
			}
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb49G);
					
					return TRUE;
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb49,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb67K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb67,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb67G);
					
					return TRUE;
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb67,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb77G);
					
					return TRUE;
					
					break;
				}
				
				case 8:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb77,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb51G);
					
					return TRUE;
					
					break;
				}
				
				case 10:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb51,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
				
			}
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb63G);
					
					return TRUE;
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb63,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb79K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb79,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb79G);
					
					return TRUE;
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb79,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb81G);
					
					return TRUE;
					
					break;
				}
				
				case 8:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb81,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb65G);
					
					return TRUE;
					
					break;
				}
				
				case 10:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb65,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
				
			}
			
		}
		
		else if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb59G);
					
					return TRUE;
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb59,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb83K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb83,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb83G);
					
					return TRUE;
					
					break;
				}
				
				case 6:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb83,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 7:
				{
					TGTHT510_supply_main_lvb_set(LVb85G);
					
					return TRUE;
					
					break;
				}
				
				case 8:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb85,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 9:
				{
					TGTHT510_supply_main_lvb_set(LVb61G);
					
					return TRUE;
					
					break;
				}
				
				case 10:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb61,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				default:
				{
					return FALSE;
					
					break;
				}
				
			}
			
		}
		
		else
		{
			return FALSE;
		}
	}
	
	else
	{
		return FALSE;
	}

}

/******************************************************************************************
**名称: 通用函数-获得贮箱压力值
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
返回贮箱压力值
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_flow_tank_pressure_get(uint16 flow_kind,uint16 tank_no)
{	
	uint16 tank_pressure;
	
	tank_pressure=0;
	
	if(flow_kind==FLOW_TANK_F)
	{
		if(tank_no==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F1==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[13];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F1==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[19];
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F2==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[15];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F2==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[21];
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F3==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[17];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F3==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[23];
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
		
		else if(tank_no==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F1==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[13];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F1==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[19];
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F2==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[15];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F2==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[21];
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F3==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[17];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F3==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[23];
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
		
		else if(tank_no==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F1==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[13];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F1==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[19];
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F2==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[15];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F2==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[21];
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_F3==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[17];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_F3==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[23];
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
	
	else if(flow_kind==FLOW_TANK_F)
	{
		if(tank_no==FIRST_TANK)
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O1==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[12];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O1==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[18];
				}
				
				else
				{
					asm("nop;");
				}

			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O2==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[14];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O2==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[20];
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O3==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[16];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O3==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[22];
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
		
		else if(tank_no==SECOND_TANK)
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O1==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[12];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O1==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[18];
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O2==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[14];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O2==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[20];
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O3==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[16];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O3==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[22];
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
		
		else if(tank_no==THIRD_TANK)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O1==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[12];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O1==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[18];
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O2==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[14];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O2==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[20];
				}
				
				else
				{
					asm("nop;");
				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_decode_par.sensor_tank_O3==DECODE_SENSOR_TANK_Z)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[16];
				}
				
				else if(TGTHT510_supply_decode_par.sensor_tank_O3==DECODE_SENSOR_TANK_B)
				{
					tank_pressure=TGTHT510_1553B_data_TGTHT100[22];
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
	
	return tank_pressure;
	
}

/******************************************************************************************
**名称: 通用函数-通过压力判断贮箱阀门关闭
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
返回贮箱压力值
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_common_is_tank_valve_off_pressure(uint16 flow_kind,uint16 tank_no)
{
	uint16 a,b;
	
	a=TGTHT510_supply_common_pipe_pressure_get(flow_kind);
	
	b=TGTHT510_supply_common_flow_tank_pressure_get(flow_kind,tank_no);
	
	if((uint16)(abs(a-b))>=TGTHT510_supply_input_par.eps2)
	{
		return TRUE;
	}
	
	else 
	{
		return FALSE;
	}

}












