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
**名称：补加阶段1：注入参数主函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_supply_stage20_blow_o_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_20_SUPPLY_BLOW_VALVE_ON;
			
			break;
		}
		
		//氧路吹除阀打开
		case STEP_20_SUPPLY_BLOW_VALVE_ON:
		{
			if(TGTHT510_supply_stage20_blow_o_step_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_20_SUPPLY_IS_HYCT_TIME;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//等待货船信息或者超时
		case STEP_20_SUPPLY_IS_HYCT_TIME:
		{
			if(TGTHT510_supply_stage20_blow_o_step_is_hyct_time()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_20_SUPPLY_BLOW_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//氧路吹除阀关闭
		case STEP_20_SUPPLY_BLOW_VALVE_OFF:
		{
			if(TGTHT510_supply_stage20_blow_o_step_valve_off()==TRUE)
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
**名称：氧路吹除阀打开
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

uint16 TGTHT510_supply_stage20_blow_o_step_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_20_0001_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_20_0001_VALVE_ON_NO1:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0002_IS_VALVE_ON_NO1;
			
			break;
		}
		
		case COMMAND_20_0002_IS_VALVE_ON_NO1:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_O,1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0003_VALVE_ON_NO2;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_20_0003_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_O,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0004_IS_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_20_0004_IS_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_O,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0005_VALVE_ON_NO3;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_20_0005_VALVE_ON_NO3:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0006_IS_VALVE_ON_NO3;
			
			break;
		}
		
		case COMMAND_20_0006_IS_VALVE_ON_NO3:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_O,3)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0007_VALVE_ON_NO4;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_20_0007_VALVE_ON_NO4:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_O,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0008_IS_VALVE_ON_NO4;
			
			break;
		}
		
		case COMMAND_20_0008_IS_VALVE_ON_NO4:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_O,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0009_VALVE_ON_NO5;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_20_0009_VALVE_ON_NO5:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0010_IS_VALVE_ON_NO5;
			
			break;
		}
		
		case COMMAND_20_0010_IS_VALVE_ON_NO5:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_O,5)==TRUE)
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
**名称：氧路吹除阀关闭
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

uint16 TGTHT510_supply_stage20_blow_o_step_is_hyct_time(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_20_0001_IS_HYCT_TIME;
			break;
		}
		
		case COMMAND_20_0001_IS_HYCT_TIME:
		{
			if(TGTHT510_supply_common_is_blow_over()==TRUE)
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
**名称：氧路吹除阀关闭
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

uint16 TGTHT510_supply_stage20_blow_o_step_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_20_0001_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_20_0001_VALVE_OFF_NO1:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_O,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0002_IS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_20_0002_IS_VALVE_OFF_NO1:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_O,1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0003_VALVE_OFF_NO2;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_20_0003_VALVE_OFF_NO2:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_O,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0004_IS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_20_0004_IS_VALVE_OFF_NO2:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_O,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0005_VALVE_OFF_NO3;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_20_0005_VALVE_OFF_NO3:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_O,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0006_IS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_20_0006_IS_VALVE_OFF_NO3:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_O,3)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0007_VALVE_OFF_NO4;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_20_0007_VALVE_OFF_NO4:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_O,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0008_IS_VALVE_OFF_NO4;
			
			break;
		}
		
		case COMMAND_20_0008_IS_VALVE_OFF_NO4:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_O,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0009_VALVE_OFF_NO5;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_20_0009_VALVE_OFF_NO5:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_O,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0010_IS_VALVE_OFF_NO5;
			
			break;
		}
		
		case COMMAND_20_0010_IS_VALVE_OFF_NO5:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_O,5)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_20_0011_VALVE_OFF_NO6;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_20_0011_VALVE_OFF_NO6:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_O,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_20_0012_IS_VALVE_OFF_NO6;
			
			break;
		}
		
		case COMMAND_20_0012_IS_VALVE_OFF_NO6:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_O,6)==TRUE)
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




