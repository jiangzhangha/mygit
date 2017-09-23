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
**名称：补加阶段10：燃推进剂补加流动主函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_supply_stage10_flow_f_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_10_F_1TANK_IS_HYCT_GOOD;
			
			break;
		}
				
//---------------------第三个燃贮箱补加流动---------------------------------------
		
		//判断货船增压状态好
		case STEP_10_F_1TANK_IS_HYCT_GOOD:
		{
			if(TGTHT510_supply_stage10_flow_f_step_1tank_is_hyct_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_10_F_1TANK_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开近浮动断接器阀门
		case STEP_10_F_1TANK_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage10_flow_f_step_1tank_interface_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_10_F_1TANK_IS_INTERFACE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断近浮动断接器阀门开启是否正常
		case STEP_10_F_1TANK_IS_INTERFACE_VALVE_ON:
		{
			if(TGTHT510_supply_stage10_flow_f_step_1tank_is_interface_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_10_F_1TANK_MIDDLE_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开燃补加接口中间阀门
		case STEP_10_F_1TANK_MIDDLE_VALVE_ON:
		{
			if(TGTHT510_supply_stage10_flow_f_step_1tank_middle_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_10_F_1TANK_DELAY1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待
		case STEP_10_F_1TANK_DELAY1:
		{
			if(TGTHT510_supply_stage10_flow_f_step_1tank_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_10_F_1TANK_IS_PIPE_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断燃补加接口管路压力是否稳定
		case STEP_10_F_1TANK_IS_PIPE_PRESSURE:
		{
			if(TGTHT510_supply_stage10_flow_f_step_1tank_is_pipe_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_10_F_1TANK_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开进贮箱补加液路阀门
		case STEP_10_F_1TANK_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage10_flow_f_step_1tank_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_10_F_1TANK_IS_FLOW_CORRECT_V;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过补加速率判断补加过程是否正常
		case STEP_10_F_1TANK_IS_FLOW_CORRECT_V:
		{
			if(TGTHT510_supply_stage10_flow_f_step_1tank_is_flow_correct()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_10_F_1TANK_IS_FLOW_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断补加是否到位
		case STEP_10_F_1TANK_IS_FLOW_OVER:
		{
			if(TGTHT510_supply_stage10_flow_f_step_1tank_is_flow_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_10_F_1TANK_SET_FLOW_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//设置补加到位信息，发送货船
		case STEP_10_F_1TANK_SET_FLOW_GOOD:
		{
			if(TGTHT510_supply_stage10_flow_f_step_1tank_set_flow_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_10_F_1TANK_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关进贮箱补加液路阀门
		case STEP_10_F_1TANK_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage10_flow_f_step_1tank_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_10_F_1TANK_IS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断贮箱阀门关闭是否正常
		case STEP_10_F_1TANK_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage10_flow_f_step_1tank_is_valve_off_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_10_F_1TANK_PIPE_DEAL;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//密闭管路处理策略
		case STEP_10_F_1TANK_PIPE_DEAL:
		{
			if(TGTHT510_supply_stage10_flow_f_step_1tank_pipe_deal()==TRUE)
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

uint16 TGTHT510_supply_stage10_flow_f_step_1tank_is_hyct_good(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_IS_HYCT_GOOD;
			break;
		}
		
		case COMMAND_10_0001_F_1TANK_IS_HYCT_GOOD:
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

uint16 TGTHT510_supply_stage10_flow_f_step_1tank_interface_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_INTERFACE_VALVE_ON;
			break;
		}
		
		case COMMAND_10_0001_F_1TANK_INTERFACE_VALVE_ON:
		{
			TGTHT510_supply_common_interface_valve_on(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0002_F_1TANK_IS_INTERFACE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_10_0002_F_1TANK_IS_INTERFACE_VALVE_ON:
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

uint16 TGTHT510_supply_stage10_flow_f_step_1tank_is_interface_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_INTERFACE_VALVE_ON_P;
			break;
		}
		
		case COMMAND_10_0001_F_1TANK_INTERFACE_VALVE_ON_P:
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

uint16 TGTHT510_supply_stage10_flow_f_step_1tank_middle_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_MIDDLE_VALVE_ON;
			break;
		}
		
		case COMMAND_10_0001_F_1TANK_MIDDLE_VALVE_ON:
		{
			TGTHT510_supply_common_middle_valve_on(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0002_F_1TANK_IS_MIDDLE_VALVE_ON;
			
			break;
		}
		
		case COMMAND_10_0002_F_1TANK_IS_MIDDLE_VALVE_ON:
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

uint16 TGTHT510_supply_stage10_flow_f_step_1tank_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_DELAY1_START;
			break;
		}
		
		case COMMAND_10_0001_F_1TANK_DELAY1_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0002_F_1TANK_IS_DELAY1;
			
			break;
		}
		
		case COMMAND_10_0002_F_1TANK_IS_DELAY1:
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

uint16 TGTHT510_supply_stage10_flow_f_step_1tank_is_pipe_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_PIPE_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_10_0001_F_1TANK_PIPE_PRESSURE_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0002_F_1TANK_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_10_0002_F_1TANK_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0003_F_1TANK_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_10_0003_F_1TANK_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0004_F_1TANK_PIPE_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0004_F_1TANK_PIPE_PRESSURE_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0005_F_1TANK_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_10_0005_F_1TANK_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0006_F_1TANK_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_10_0006_F_1TANK_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0007_F_1TANK_PIPE_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0007_F_1TANK_PIPE_PRESSURE_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0008_F_1TANK_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_10_0008_F_1TANK_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0009_F_1TANK_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_10_0009_F_1TANK_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0010_F_1TANK_PIPE_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0010_F_1TANK_PIPE_PRESSURE_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0011_F_1TANK_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_10_0011_F_1TANK_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0012_F_1TANK_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_10_0012_F_1TANK_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0013_F_1TANK_PIPE_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0013_F_1TANK_PIPE_PRESSURE_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0014_F_1TANK_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_10_0014_F_1TANK_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0015_F_1TANK_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_10_0015_F_1TANK_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0016_F_1TANK_PIPE_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0016_F_1TANK_PIPE_PRESSURE_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0017_F_1TANK_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_10_0017_F_1TANK_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0018_F_1TANK_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_10_0018_F_1TANK_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0019_F_1TANK_PIPE_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0019_F_1TANK_PIPE_PRESSURE_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0020_F_1TANK_IS_PIPE_PRESSURE;
			
			break;
		}
		
		case COMMAND_10_0020_F_1TANK_IS_PIPE_PRESSURE:
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

uint16 TGTHT510_supply_stage10_flow_f_step_1tank_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_10_0001_F_1TANK_IN_TANK_VALVE_ON:
		{
			TGTHT510_supply_common_flow_in_tank_valve_on(FLOW_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0002_F_1TANK_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_10_0002_F_1TANK_IS_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_on(FLOW_TANK_F,THIRD_TANK)==TRUE)
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

uint16 TGTHT510_supply_stage10_flow_f_step_1tank_is_flow_correct(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_HTT_NO1;
			break;
		}
		
		case COMMAND_10_0001_F_1TANK_HTT_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0002_F_1TANK_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_10_0002_F_1TANK_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0003_F_1TANK_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_10_0003_F_1TANK_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0004_F_1TANK_HTT_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0004_F_1TANK_HTT_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0005_F_1TANK_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_10_0005_F_1TANK_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0006_F_1TANK_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_10_0006_F_1TANK_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0007_F_1TANK_HTT_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0007_F_1TANK_HTT_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_flow_htt_get(FLOW_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0008_F_1TANK_IS_FLOW_CORRECT;
			
			break;
		}
		
		case COMMAND_10_0008_F_1TANK_IS_FLOW_CORRECT:
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

uint16 TGTHT510_supply_stage10_flow_f_step_1tank_is_flow_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_IS_FLOW_OVER_NO1;
			break;
		}
		
		case COMMAND_10_0001_F_1TANK_IS_FLOW_OVER_NO1:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_F,THIRD_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0002_F_1TANK_IS_FLOW_OVER_NO2;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_10_0002_F_1TANK_IS_FLOW_OVER_NO2:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_F,THIRD_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0003_F_1TANK_IS_FLOW_OVER_NO3;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_IS_FLOW_OVER_NO1;
			}
			
			break;
		}
		
		case COMMAND_10_0003_F_1TANK_IS_FLOW_OVER_NO3:
		{
			if(TGTHT510_supply_common_is_flow_over(FLOW_TANK_F,THIRD_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_IS_FLOW_OVER_NO1;
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

uint16 TGTHT510_supply_stage10_flow_f_step_1tank_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_IN_TANK_VALVE_OFF;
			break;
		}
		
		case COMMAND_10_0001_F_1TANK_IN_TANK_VALVE_OFF:
		{
			TGTHT510_supply_common_flow_in_tank_valve_off(FLOW_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0002_F_1TANK_IS_IN_TANK_VALVE_OFF;
			
			break;
		}
		
		case COMMAND_10_0002_F_1TANK_IS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_common_flow_is_in_tank_valve_off(FLOW_TANK_F,THIRD_TANK)==TRUE)
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

uint16 TGTHT510_supply_stage10_flow_f_step_1tank_is_valve_off_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_IS_PRESSURE;
			break;
		}
		
		case COMMAND_10_0001_F_1TANK_IS_PRESSURE:
		{
			if(TGTHT510_supply_common_is_tank_valve_off_pressure(FLOW_TANK_F,THIRD_TANK)==TRUE)
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

uint16 TGTHT510_supply_stage10_flow_f_step_1tank_set_flow_good(void)
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
		
		case COMMAND_10_0001_F_1TANK_SET_FLOW_GOOD:
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

uint16 TGTHT510_supply_stage10_flow_f_step_1tank_pipe_deal(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_10_0001_F_1TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_10_0001_F_1TANK_VALVE_OFF_NO1:
		{
			TGTHT510_supply_common_third_flow_pipe_deal(FLOW_TANK_F,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0002_F_1TANK_IS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_10_0002_F_1TANK_IS_VALVE_OFF_NO1:
		{
			if(TGTHT510_supply_common_third_flow_pipe_deal(FLOW_TANK_F,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0003_F_1TANK_VALVE_ON_NO2;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_10_0003_F_1TANK_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_third_flow_pipe_deal(FLOW_TANK_F,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0004_F_1TANK_IS_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_10_0004_F_1TANK_IS_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_third_flow_pipe_deal(FLOW_TANK_F,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0005_F_1TANK_5SEC_START;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_10_0005_F_1TANK_5SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0006_F_1TANK_IS_5SEC;
			
			break;
		}
		
		case COMMAND_10_0006_F_1TANK_IS_5SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0007_F_1TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0007_F_1TANK_VALVE_OFF_NO3:
		{
			TGTHT510_supply_common_third_flow_pipe_deal(FLOW_TANK_F,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0008_F_1TANK_IS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_10_0008_F_1TANK_IS_VALVE_OFF_NO3:
		{
			if(TGTHT510_supply_common_third_flow_pipe_deal(FLOW_TANK_F,6)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0009_F_1TANK_VALVE_OFF_NO4;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_10_0009_F_1TANK_VALVE_OFF_NO4:
		{
			TGTHT510_supply_common_third_flow_pipe_deal(FLOW_TANK_F,7);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0010_F_1TANK_IS_VALVE_OFF_NO4;
			
			break;
		}
		
		case COMMAND_10_0010_F_1TANK_IS_VALVE_OFF_NO4:
		{
			if(TGTHT510_supply_common_third_flow_pipe_deal(FLOW_TANK_F,8)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0011_F_1TANK_VALVE_OFF_NO5;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_10_0011_F_1TANK_VALVE_OFF_NO5:
		{
			TGTHT510_supply_common_third_flow_pipe_deal(FLOW_TANK_F,9);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0012_F_1TANK_IS_VALVE_OFF_NO5;
			
			break;
		}
		
		case COMMAND_10_0012_F_1TANK_IS_VALVE_OFF_NO5:
		{
			if(TGTHT510_supply_common_third_flow_pipe_deal(FLOW_TANK_F,10)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0013_F_1TANK_10SEC_START;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_10_0013_F_1TANK_10SEC_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0014_F_1TANK_IS_10SEC;
			
			break;
		}
		
		case COMMAND_10_0014_F_1TANK_IS_10SEC:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_10SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0015_F_1TANK_PIPE_GET_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0015_F_1TANK_PIPE_GET_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0016_F_1TANK_PIPE_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_10_0016_F_1TANK_PIPE_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0017_F_1TANK_PIPE_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_10_0017_F_1TANK_PIPE_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0018_F_1TANK_PIPE_GET_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0018_F_1TANK_PIPE_GET_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0019_F_1TANK_PIPE_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_10_0019_F_1TANK_PIPE_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0020_F_1TANK_PIPE_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_10_0020_F_1TANK_PIPE_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0021_F_1TANK_PIPE_GET_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0021_F_1TANK_PIPE_GET_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0022_F_1TANK_PIPE_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_10_0022_F_1TANK_PIPE_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0023_F_1TANK_PIPE_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_10_0023_F_1TANK_PIPE_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0024_F_1TANK_PIPE_GET_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0024_F_1TANK_PIPE_GET_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0025_F_1TANK_PIPE_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_10_0025_F_1TANK_PIPE_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0026_F_1TANK_PIPE_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_10_0026_F_1TANK_PIPE_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0027_F_1TANK_PIPE_GET_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0027_F_1TANK_PIPE_GET_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0028_F_1TANK_PIPE_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_10_0028_F_1TANK_PIPE_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0029_F_1TANK_PIPE_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_10_0029_F_1TANK_PIPE_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0030_F_1TANK_PIPE_GET_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0030_F_1TANK_PIPE_GET_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0031_F_1TANK_PIPE_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_10_0031_F_1TANK_PIPE_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0032_F_1TANK_PIPE_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_10_0032_F_1TANK_PIPE_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_10_0033_F_1TANK_PIPE_GET_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_10_0033_F_1TANK_PIPE_GET_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_pipe_pressure_get(FLOW_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_10_0034_F_1TANK_PIPE_DEAL_PRESSURE;
			
			break;
		}
		
		case COMMAND_10_0034_F_1TANK_PIPE_DEAL_PRESSURE:
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

uint16 TGTHT510_supply_common_third_flow_pipe_deal(uint16 flow_kind,uint16 command_number)
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
					TGTHT510_supply_main_lvb_set(LVb76K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb76,VALVE_ON)==TRUE)
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
					TGTHT510_supply_main_lvb_set(LVb78K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb78,VALVE_ON)==TRUE)
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
					TGTHT510_supply_main_lvb_set(LVb82K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb82,VALVE_ON)==TRUE)
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
					TGTHT510_supply_main_lvb_set(LVb86K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb86,VALVE_ON)==TRUE)
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
					TGTHT510_supply_main_lvb_set(LVb75K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb75,VALVE_ON)==TRUE)
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
					TGTHT510_supply_main_lvb_set(LVb77K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb77,VALVE_ON)==TRUE)
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
					TGTHT510_supply_main_lvb_set(LVb81K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb81,VALVE_ON)==TRUE)
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
					TGTHT510_supply_main_lvb_set(LVb85K);
					
					return TRUE;
					
					break;
				}
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb85,VALVE_ON)==TRUE)
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






