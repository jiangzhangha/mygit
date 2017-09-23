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
**名称：第三个燃贮箱复压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_supply_stage11_repre_f_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_11_F_REPRE_1TANK_LVT_VALVE_ON;
			
			break;
		}
		
//---------------------第三个燃贮箱复压---------------------------------------------
		
		//贮箱增压，打开高压自锁阀
		case STEP_11_F_REPRE_1TANK_LVT_VALVE_ON:
		{
			if(TGTHT510_supply_stage11_repre_f_step_1tank_lvt_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_11_F_REPRE_1TANK_IS_REPRE_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力与时间判断复压是否结束
		case STEP_11_F_REPRE_1TANK_IS_REPRE_OVER:
		{
			if(TGTHT510_supply_stage11_repre_f_step_1tank_is_repre_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_11_F_REPRE_1TANK_LVT_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//复压结束，关闭高压自锁阀
		case STEP_11_F_REPRE_1TANK_LVT_VALVE_OFF:
		{
			if(TGTHT510_supply_stage11_repre_f_step_1tank_lvt_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_11_F_REPRE_1TANK_OUT_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开贮箱出口阀门
		case STEP_11_F_REPRE_1TANK_OUT_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage11_repre_f_step_1tank_out_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_11_F_REPRE_1TANK_DELAY;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待
		case STEP_11_F_REPRE_1TANK_DELAY:
		{
			if(TGTHT510_supply_stage11_repre_f_step_1tank_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_11_F_REPRE_1TANK_IS_TANK_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断贮箱压力的稳定性
		case STEP_11_F_REPRE_1TANK_IS_TANK_PRESSURE:
		{
			if(TGTHT510_supply_stage11_repre_f_step_1tank_is_tank_pressure_stable()==TRUE)
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
**名称：贮箱增压，打开高压自锁阀
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

uint16 TGTHT510_supply_stage11_repre_f_step_1tank_lvt_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_11_0001_F_REPRE_1TANK_LVT_VALVE_ON;
			break;
		}
		
		case COMMAND_11_0001_F_REPRE_1TANK_LVT_VALVE_ON:
		{
			TGTHT510_supply_common_repre_lvt_valve_on(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO1;
			
			break;
		}
		
		case COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO1;
			
			break;
		}
		
		case COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0004_F_REPRE_1TANK_IS_LVT_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0004_F_REPRE_1TANK_IS_LVT_VALVE_ON:
		{
			if(TGTHT510_supply_common_repre_is_lvt_valve_on(REPRE_TANK_F,THIRD_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//推进系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_ON);
				//TGTHT510_supply_ctrl.command=COMMAND_END;
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
**名称：通过压力与时间判断复压是否结束
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

uint16 TGTHT510_supply_stage11_repre_f_step_1tank_is_repre_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_11_0001_F_REPRE_1TANK_IS_REPRE_OVER;
			break;
		}
		
		case COMMAND_11_0001_F_REPRE_1TANK_IS_REPRE_OVER:
		{
			if(TGTHT510_supply_common_repre_is_repre_over(REPRE_TANK_F,THIRD_TANK)==TRUE)
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
**名称：复压结束，关闭高压自锁阀
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

uint16 TGTHT510_supply_stage11_repre_f_step_1tank_lvt_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_11_0001_F_REPRE_1TANK_LVT_VALVE_OFF;
			break;
		}
		
		case COMMAND_11_0001_F_REPRE_1TANK_LVT_VALVE_OFF:
		{
			TGTHT510_supply_common_repre_lvt_valve_off(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO2;
			
			break;
		}
		
		case COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO2;
			
			break;
		}
		
		case COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0004_F_REPRE_1TANK_IS_LVT_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0004_F_REPRE_1TANK_IS_LVT_VALVE_OFF:
		{
			if(TGTHT510_supply_common_repre_is_lvt_valve_off(REPRE_TANK_F,THIRD_TANK)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//推进系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);
				//TGTHT510_supply_ctrl.command=COMMAND_END;
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
**名称：开贮箱出口阀门
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

uint16 TGTHT510_supply_stage11_repre_f_step_1tank_out_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_11_0001_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_11_0001_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO1:
		{
			TGTHT510_supply_common_repre_out_tank_valve_on(REPRE_TANK_F,THIRD_TANK,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO3;
			
			break;
		}
		
		case COMMAND_11_0002_F_REPRE_1TANK_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO3;
			
			break;
		}
		
		case COMMAND_11_0003_F_REPRE_1TANK_IS_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0004_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0004_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO1:
		{
			if(TGTHT510_supply_common_repre_is_out_tank_valve_on(REPRE_TANK_F,THIRD_TANK,1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0005_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO2;
			}
			
			else
			{
				//推进系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_ON);
				//TGTHT510_supply_ctrl.command=COMMAND_11_0005_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO2;
			}
			
			break;
		}
		
		case COMMAND_11_0005_F_REPRE_1TANK_OUT_TANK_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_repre_out_tank_valve_on(REPRE_TANK_F,THIRD_TANK,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0006_F_REPRE_1TANK_1MIN_START_NO4;
			
			break;
		}
		
		case COMMAND_11_0006_F_REPRE_1TANK_1MIN_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0007_F_REPRE_1TANK_IS_1MIN_NO4;
			
			break;
		}
		
		case COMMAND_11_0007_F_REPRE_1TANK_IS_1MIN_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0008_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0008_F_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_repre_is_out_tank_valve_on(REPRE_TANK_F,THIRD_TANK,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//推进系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_ON);
				//TGTHT510_supply_ctrl.command=COMMAND_END;
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

uint16 TGTHT510_supply_stage11_repre_f_step_1tank_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_11_0001_F_REPRE_1TANK_DELAY_START_NO1;
			break;
		}
		
		case COMMAND_11_0001_F_REPRE_1TANK_DELAY_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0002_F_REPRE_1TANK_IS_DELAY_NO1;
			
			break;
		}
		
		case COMMAND_11_0002_F_REPRE_1TANK_IS_DELAY_NO1:
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
**名称：判断贮箱压力的稳定性
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

uint16 TGTHT510_supply_stage11_repre_f_step_1tank_is_tank_pressure_stable(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_11_0001_F_REPRE_1TANK_TANK_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_11_0001_F_REPRE_1TANK_TANK_PRESSURE_NO1:
		{
			temp_gloal[0]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0002_F_REPRE_1TANK_5SEC_START_NO1;
			
			break;
		}
		
		case COMMAND_11_0002_F_REPRE_1TANK_5SEC_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0003_F_REPRE_1TANK_IS_5SEC_NO1;
			
			break;
		}
		
		case COMMAND_11_0003_F_REPRE_1TANK_IS_5SEC_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0004_F_REPRE_1TANK_TANK_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0004_F_REPRE_1TANK_TANK_PRESSURE_NO2:
		{
			temp_gloal[1]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0005_F_REPRE_1TANK_5SEC_START_NO2;
			
			break;
		}
		
		case COMMAND_11_0005_F_REPRE_1TANK_5SEC_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0006_F_REPRE_1TANK_IS_5SEC_NO2;
			
			break;
		}
		
		case COMMAND_11_0006_F_REPRE_1TANK_IS_5SEC_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0007_F_REPRE_1TANK_TANK_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0007_F_REPRE_1TANK_TANK_PRESSURE_NO3:
		{
			temp_gloal[2]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0008_F_REPRE_1TANK_5SEC_START_NO3;
			
			break;
		}
		
		case COMMAND_11_0008_F_REPRE_1TANK_5SEC_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0009_F_REPRE_1TANK_IS_5SEC_NO3;
			
			break;
		}
		
		case COMMAND_11_0009_F_REPRE_1TANK_IS_5SEC_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0010_F_REPRE_1TANK_TANK_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0010_F_REPRE_1TANK_TANK_PRESSURE_NO4:
		{
			temp_gloal[3]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0011_F_REPRE_1TANK_5SEC_START_NO4;
			
			break;
		}
		
		case COMMAND_11_0011_F_REPRE_1TANK_5SEC_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0012_F_REPRE_1TANK_IS_5SEC_NO4;
			
			break;
		}
		
		case COMMAND_11_0012_F_REPRE_1TANK_IS_5SEC_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0013_F_REPRE_1TANK_TANK_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0013_F_REPRE_1TANK_TANK_PRESSURE_NO5:
		{
			temp_gloal[4]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0014_F_REPRE_1TANK_5SEC_START_NO5;
			
			break;
		}
		
		case COMMAND_11_0014_F_REPRE_1TANK_5SEC_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0015_F_REPRE_1TANK_IS_5SEC_NO5;
			
			break;
		}
		
		case COMMAND_11_0015_F_REPRE_1TANK_IS_5SEC_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0016_F_REPRE_1TANK_TANK_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0016_F_REPRE_1TANK_TANK_PRESSURE_NO6:
		{
			temp_gloal[5]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0017_F_REPRE_1TANK_5SEC_START_NO6;
			
			break;
		}
		
		case COMMAND_11_0017_F_REPRE_1TANK_5SEC_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0018_F_REPRE_1TANK_IS_5SEC_NO6;
			
			break;
		}
		
		case COMMAND_11_0018_F_REPRE_1TANK_IS_5SEC_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_5SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_11_0019_F_REPRE_1TANK_TANK_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_11_0019_F_REPRE_1TANK_TANK_PRESSURE_NO7:
		{
			temp_gloal[6]=TGTHT510_supply_common_repre_tank_pressure_get(REPRE_TANK_F,THIRD_TANK);
			
			TGTHT510_supply_ctrl.command=COMMAND_11_0020_F_REPRE_1TANK_IS_PRESSURE_STABLE;
			
			break;
		}
		
		case COMMAND_11_0020_F_REPRE_1TANK_IS_PRESSURE_STABLE:
		{
			if(TGTHT510_supply_common_repre_is_tank_pressure_stable(temp_gloal)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//贮箱压力不稳定
				TGTHT510_supply_main_pause(ERRNO_TANK_PRESSURE_STABLE);
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
































