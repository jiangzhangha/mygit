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
void TGTHT510_supply_stage12_blow_f_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_12_SUPPLY_BLOW_VALVE_ON;
			
			break;
		}
		
		//燃路吹除阀打开
		case STEP_12_SUPPLY_BLOW_VALVE_ON:
		{
			if(TGTHT510_supply_stage12_blow_f_step_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_12_SUPPLY_IS_HYCT_TIME;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//等待货船信息或者超时
		case STEP_12_SUPPLY_IS_HYCT_TIME:
		{
			if(TGTHT510_supply_stage12_blow_f_step_is_hyct_time()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_12_SUPPLY_BLOW_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//燃路吹除阀关闭
		case STEP_12_SUPPLY_BLOW_VALVE_OFF:
		{
			if(TGTHT510_supply_stage12_blow_f_step_valve_off()==TRUE)
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
**名称：燃路吹除阀打开
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

uint16 TGTHT510_supply_stage12_blow_f_step_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_12_0001_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_12_0001_VALVE_ON_NO1:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_F,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0002_IS_VALVE_ON_NO1;
			
			break;
		}
		
		case COMMAND_12_0002_IS_VALVE_ON_NO1:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_F,1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0003_VALVE_ON_NO2;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_12_0003_VALVE_ON_NO2:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_F,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0004_IS_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_12_0004_IS_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_F,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0005_VALVE_ON_NO3;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_12_0005_VALVE_ON_NO3:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_F,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0006_IS_VALVE_ON_NO3;
			
			break;
		}
		
		case COMMAND_12_0006_IS_VALVE_ON_NO3:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_F,3)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0007_VALVE_ON_NO4;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_12_0007_VALVE_ON_NO4:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_F,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0008_IS_VALVE_ON_NO4;
			
			break;
		}
		
		case COMMAND_12_0008_IS_VALVE_ON_NO4:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_F,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0009_VALVE_ON_NO5;
			}
			
			else
			{
				//补加系统阀门打开异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_12_0009_VALVE_ON_NO5:
		{
			TGTHT510_supply_common_blow_valve_on(BLOW_TANK_F,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0010_IS_VALVE_ON_NO5;
			
			break;
		}
		
		case COMMAND_12_0010_IS_VALVE_ON_NO5:
		{
			if(TGTHT510_supply_common_blow_is_valve_on(BLOW_TANK_F,5)==TRUE)
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
**名称：燃路吹除阀关闭
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

uint16 TGTHT510_supply_stage12_blow_f_step_is_hyct_time(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_12_0001_IS_HYCT_TIME;
			break;
		}
		
		case COMMAND_12_0001_IS_HYCT_TIME:
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
**名称：燃路吹除阀关闭
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

uint16 TGTHT510_supply_stage12_blow_f_step_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_12_0001_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_12_0001_VALVE_OFF_NO1:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_F,1);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0002_IS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_12_0002_IS_VALVE_OFF_NO1:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_F,1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0003_VALVE_OFF_NO2;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_12_0003_VALVE_OFF_NO2:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_F,2);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0004_IS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_12_0004_IS_VALVE_OFF_NO2:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_F,2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0005_VALVE_OFF_NO3;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_12_0005_VALVE_OFF_NO3:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_F,3);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0006_IS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_12_0006_IS_VALVE_OFF_NO3:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_F,3)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0007_VALVE_OFF_NO4;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_12_0007_VALVE_OFF_NO4:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_F,4);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0008_IS_VALVE_OFF_NO4;
			
			break;
		}
		
		case COMMAND_12_0008_IS_VALVE_OFF_NO4:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_F,4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0009_VALVE_OFF_NO5;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_12_0009_VALVE_OFF_NO5:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_F,5);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0010_IS_VALVE_OFF_NO5;
			
			break;
		}
		
		case COMMAND_12_0010_IS_VALVE_OFF_NO5:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_F,5)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_12_0011_VALVE_OFF_NO6;
			}
			
			else
			{
				//补加系统阀门关闭异常
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_12_0011_VALVE_OFF_NO6:
		{
			TGTHT510_supply_common_blow_valve_off(BLOW_TANK_F,6);
			
			TGTHT510_supply_ctrl.command=COMMAND_12_0012_IS_VALVE_OFF_NO6;
			
			break;
		}
		
		case COMMAND_12_0012_IS_VALVE_OFF_NO6:
		{
			if(TGTHT510_supply_common_blow_is_valve_off(BLOW_TANK_F,6)==TRUE)
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
**名称: 通用函数-燃路吹除阀打开
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

void TGTHT510_supply_common_blow_valve_on(uint16 blow_kind,uint16 command_number)
{
	if(blow_kind==BLOW_TANK_F)
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb40K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb72K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb76K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb70K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb74K);
					
					break;
				}
				
				default:
				{
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
					TGTHT510_supply_main_lvb_set(LVb50K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb68K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb78K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb70K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb74K);
					
					break;
				}
				
				default:
				{
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
					TGTHT510_supply_main_lvb_set(LVb60K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb80K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb82K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb70K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb74K);
					
					break;
				}
				
				default:
				{
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
					TGTHT510_supply_main_lvb_set(LVb64K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb84K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb86K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb70K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb74K);
					
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
	
	else if(blow_kind==BLOW_TANK_O)
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb39K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb69K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb73K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb71K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb75K);
					
					break;
				}
				
				default:
				{
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
					TGTHT510_supply_main_lvb_set(LVb49K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb69K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb73K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb67K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb77K);
					
					break;
				}
				
				default:
				{
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
					TGTHT510_supply_main_lvb_set(LVb59K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb69K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb73K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb79K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb81K);
					
					break;
				}
				
				default:
				{
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
					TGTHT510_supply_main_lvb_set(LVb63K);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb69K);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb73K);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb83K);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb85K);
					
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
**名称: 通用函数-判断燃路吹除阀打开
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

uint16 TGTHT510_supply_common_blow_is_valve_on(uint16 blow_kind,uint16 command_number)
{
	if(blow_kind==BLOW_TANK_F)
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb40,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
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
				
				case 3:
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
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_ON)==TRUE)
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_ON)==TRUE)
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb50,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
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
				
				case 3:
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
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_ON)==TRUE)
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_ON)==TRUE)
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb60,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
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
				
				case 3:
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
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_ON)==TRUE)
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_ON)==TRUE)
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb64,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
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
				
				case 3:
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
				
				case 4:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_ON)==TRUE)
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_ON)==TRUE)
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
	
	else if(blow_kind==BLOW_TANK_O)
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb39,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_ON)==TRUE)
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb49,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_ON)==TRUE)
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb59,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_ON)==TRUE)
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb63,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_ON)==TRUE)
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_ON)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
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
**名称: 通用函数-燃路吹除阀关闭
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

void TGTHT510_supply_common_blow_valve_off(uint16 blow_kind,uint16 command_number)
{
	if(blow_kind==BLOW_TANK_F)
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb70G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb74G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb72G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb76G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb40G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb50G);
					
					break;
				}
				
				default:
				{
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
					TGTHT510_supply_main_lvb_set(LVb70G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb74G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb68G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb78G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb40G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb50G);
					
					break;
				}
				
				default:
				{
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
					TGTHT510_supply_main_lvb_set(LVb70G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb74G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb80G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb82G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb60G);
					
					break;
				}
				
				case 6:
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
		
		else if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb70G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb74G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb84G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb86G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb60G);
					
					break;
				}
				
				case 6:
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
		
		else
		{
			asm("nop;");
		}
		
	}
	
	else if(blow_kind==BLOW_TANK_O)
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			switch(command_number)
			{
				case 1:
				{
					TGTHT510_supply_main_lvb_set(LVb69G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb73G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb71G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb75G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb39G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb49G);
					
					break;
				}
				
				default:
				{
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
					TGTHT510_supply_main_lvb_set(LVb69G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb73G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb67G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb77G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb39G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb49G);
					
					break;
				}
				
				default:
				{
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
					TGTHT510_supply_main_lvb_set(LVb69G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb73G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb79G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb81G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb59G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb63G);
					
					break;
				}
				
				default:
				{
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
					TGTHT510_supply_main_lvb_set(LVb69G);
					
					break;
				}
				
				case 2:
				{
					TGTHT510_supply_main_lvb_set(LVb73G);
					
					break;
				}
				
				case 3:
				{
					TGTHT510_supply_main_lvb_set(LVb83G);
					
					break;
				}
				
				case 4:
				{
					TGTHT510_supply_main_lvb_set(LVb85G);
					
					break;
				}
				
				case 5:
				{
					TGTHT510_supply_main_lvb_set(LVb59G);
					
					break;
				}
				
				case 6:
				{
					TGTHT510_supply_main_lvb_set(LVb63G);
					
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
**名称: 通用函数-燃路吹除阀关闭
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

uint16 TGTHT510_supply_common_blow_is_valve_off(uint16 blow_kind,uint16 command_number)
{
	if(blow_kind==BLOW_TANK_F)
	{
		if(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_OFF)==TRUE)
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
				
				case 4:
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
				
				case 5:
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
				
				case 6:
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_OFF)==TRUE)
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
				
				case 4:
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
				
				case 5:
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
				
				case 6:
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_OFF)==TRUE)
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
				
				case 4:
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
				
				case 5:
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
				
				case 6:
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_OFF)==TRUE)
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
				
				case 4:
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
				
				case 5:
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
				
				case 6:
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
	
	else if(blow_kind==BLOW_TANK_O)
	{
		if(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)
		{
			switch(command_number)
			{
				case 1:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_OFF)==TRUE)
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
				
				case 4:
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
				
				case 5:
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
				
				case 6:
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_OFF)==TRUE)
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
				
				case 4:
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
				
				case 5:
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
				
				case 6:
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_OFF)==TRUE)
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
				
				case 4:
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
				
				case 5:
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
				
				case 6:
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
					if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_OFF)==TRUE)
					{
						return TRUE;
					}
					
					else
					{
						return FALSE;
					}
					
					break;
				}
				
				case 2:
				{
					if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_OFF)==TRUE)
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
				
				case 4:
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
				
				case 5:
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
				
				case 6:
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
**名称: 通用函数-判断吹除是否结束
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

uint16 TGTHT510_supply_common_is_blow_over(void)
{
	//函数待补充，增加判断货船发送的信息，调整判断的时间间隔！！！！
	
	uint32 time_val;
	
	TGTHT510_supply_time_stage_get(&time_val);
	
	if(time_val>=(uint32)(4*TGTHT510_supply_input_par.time_delay_long))
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}







