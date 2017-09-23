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

/******************************************************************************************
**名称：补加阶段
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_supply_stage04_leak_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.leak_flag=FALSE;
			
			TGTHT510_supply_ctrl.step=STEP_04_SUPPLY_VALVE_ON_CONNECT;
			break;
		}
		
		case STEP_04_SUPPLY_VALVE_ON_CONNECT://开近浮动断接器补加阀门
		{
			TGTHT510_supply_stage04_leak_valve_on_connect();
			
			break;
		}
		
		case STEP_04_SUPPLY_LEAK_INPUT_COMMAND://检漏气体排气指令注入
		{
			if(TGTHT510_supply_ctrl.leak_flag==TRUE)
			{
				TGTHT510_supply_stage04_leak_valve_on_gas();
			}
			
			break;
		}

		case STEP_END://结束
		{
			TGTHT510_supply_ctrl.leak_flag=FALSE;
			
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

void TGTHT510_supply_stage04_leak_valve_on_connect(void)
{
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_04_0001_VALVE_ON_CONNECT_NO1;
			break;
		}
		
		case COMMAND_04_0001_VALVE_ON_CONNECT_NO1:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_connect(1);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0002_IS_VALVE_ON_CONNECT_NO1;
			
			break;
		}
		
		case COMMAND_04_0002_IS_VALVE_ON_CONNECT_NO1:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_connect(1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0003_VALVE_ON_CONNECT_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_04_0003_VALVE_ON_CONNECT_NO2:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_connect(2);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0004_IS_VALVE_ON_CONNECT_NO2;
			
			break;
		}
		
		case COMMAND_04_0004_IS_VALVE_ON_CONNECT_NO2:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_connect(2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		
		case COMMAND_END:
		{
			TGTHT510_supply_ctrl.step=STEP_04_SUPPLY_LEAK_INPUT_COMMAND;
			
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
**名称：补加阶段4
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_stage04_leak_command_valve_on_connect(uint16 n)
{
	//燃氧补加接口为R1O1
	if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)&&\
	(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1))
	{
		if(n==1)
		{
			TGTHT510_supply_main_lvb_set(LVb40K);
		}
		
		else if(n==2)
		{
			TGTHT510_supply_main_lvb_set(LVb39K);
		}
		
		else
		{
			TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
		}
		
	}
	
	//燃氧补加接口为R2O2
	else if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)&&\
	(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2))
	{
		if(n==1)
		{
			TGTHT510_supply_main_lvb_set(LVb50K);
		}
		
		else if(n==2)
		{
			TGTHT510_supply_main_lvb_set(LVb49K);
		}
		
		else
		{
			TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
		}
		
	}
	
	//燃氧补加接口为R3O3
	else if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)&&\
	(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3))
	{
		if(n==1)
		{
			TGTHT510_supply_main_lvb_set(LVb60K);
		}
		
		else if(n==2)
		{
			TGTHT510_supply_main_lvb_set(LVb59K);
		}
		
		else
		{
			TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
		}
		
	}
	
	//燃氧补加接口为R4O4
	else if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)&&\
	(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4))
	{
		if(n==1)
		{
			TGTHT510_supply_main_lvb_set(LVb64K);
		}
		
		else if(n==2)
		{
			TGTHT510_supply_main_lvb_set(LVb63K);
		}
		
		else
		{
			TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
		}
		
	}
	
	else
	{
		TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数错误

	}

}



/******************************************************************************************
**名称：补加阶段4
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_stage04_leak_command_is_valve_on_connect(uint16 n)
{
	//燃氧补加接口为R1O1
	if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)&&\
	(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1))
	{
		if(n==1)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb40,VALVE_ON)==TRUE)//阀门打开正确
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(n==2)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb39,VALVE_ON)==TRUE)//阀门打开正确
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
			TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
			return FALSE;
		}
		
	}
	
	//燃氧补加接口为R2O2
	else if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)&&\
	(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2))
	{
		if(n==1)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb50,VALVE_ON)==TRUE)//阀门打开正确
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(n==2)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb49,VALVE_ON)==TRUE)//阀门打开正确
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
			TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
			return FALSE;
		}
		
	}
	
	//燃氧补加接口为R3O3
	else if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)&&\
	(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3))
	{
		if(n==1)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb60,VALVE_ON)==TRUE)//阀门打开正确
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(n==2)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb59,VALVE_ON)==TRUE)//阀门打开正确
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
			TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
			return FALSE;
		}
		
	}
	
	//燃氧补加接口为R4O4
	else if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4)&&\
	(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4))
	{
		if(n==1)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb64,VALVE_ON)==TRUE)//阀门打开正确
			{
				return TRUE;
			}
			
			else
			{
				return FALSE;
			}
		}
		
		else if(n==2)
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb63,VALVE_ON)==TRUE)//阀门打开正确
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
			TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
			return FALSE;
		}
		
	}
	
	else
	{
		TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//内部函数输入参数错误
		return FALSE;

	}

}

/******************************************************************************************
**名称：补加阶段4：检漏排气指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_stage04_leak_valve_on_gas(void)
{
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_04_0005_LEAK_VALVE_NO1;
			break;
		}
		
		//检漏气体排气指令 打开阀门1
		case COMMAND_04_0005_LEAK_VALVE_NO1:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(1);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0006_LEAK_IS_VALVE_NO1;
			
			break;
		}
		
		case COMMAND_04_0006_LEAK_IS_VALVE_NO1:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0007_LEAK_VALVE_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 打开阀门2
		case COMMAND_04_0007_LEAK_VALVE_NO2:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(2);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0008_LEAK_IS_VALVE_NO2;
			
			break;
		}
		
		case COMMAND_04_0008_LEAK_IS_VALVE_NO2:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0009_LEAK_VALVE_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 打开阀门3
		case COMMAND_04_0009_LEAK_VALVE_NO3:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(3);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0010_LEAK_IS_VALVE_NO3;
			
			break;
		}
		
		case COMMAND_04_0010_LEAK_IS_VALVE_NO3:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(3)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0011_LEAK_VALVE_NO4;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 打开阀门4
		case COMMAND_04_0011_LEAK_VALVE_NO4:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(4);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0012_LEAK_IS_VALVE_NO4;
			
			break;
		}
		
		case COMMAND_04_0012_LEAK_IS_VALVE_NO4:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0013_LEAK_VALVE_NO5;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 打开阀门5
		case COMMAND_04_0013_LEAK_VALVE_NO5:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(5);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0014_LEAK_IS_VALVE_NO5;
			
			break;
		}
		
		case COMMAND_04_0014_LEAK_IS_VALVE_NO5:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(5)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0015_LEAK_VALVE_NO6;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 打开阀门6
		case COMMAND_04_0015_LEAK_VALVE_NO6:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(6);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0016_LEAK_IS_VALVE_NO6;
			
			break;
		}
		
		case COMMAND_04_0016_LEAK_IS_VALVE_NO6:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(6)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0017_LEAK_VALVE_NO7;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 打开阀门7
		case COMMAND_04_0017_LEAK_VALVE_NO7:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(7);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0018_LEAK_IS_VALVE_NO7;
			
			break;
		}
		
		case COMMAND_04_0018_LEAK_IS_VALVE_NO7:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(7)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0019_LEAK_VALVE_NO8;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 打开阀门8
		case COMMAND_04_0019_LEAK_VALVE_NO8:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(8);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0020_LEAK_IS_VALVE_NO8;
			
			break;
		}
		
		case COMMAND_04_0020_LEAK_IS_VALVE_NO8:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(8)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0021_LEAK_VALVE_NO9;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 打开阀门9
		case COMMAND_04_0021_LEAK_VALVE_NO9:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(9);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0022_LEAK_IS_VALVE_NO9;
			
			break;
		}
		
		case COMMAND_04_0022_LEAK_IS_VALVE_NO9:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(9)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0023_LEAK_VALVE_NO10;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 打开阀门10
		case COMMAND_04_0023_LEAK_VALVE_NO10:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(10);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0024_LEAK_IS_VALVE_NO10;
			
			break;
		}
		
		case COMMAND_04_0024_LEAK_IS_VALVE_NO10:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(10)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0025_LEAK_VALVE_NO11;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 打开阀门11
		case COMMAND_04_0025_LEAK_VALVE_NO11:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(11);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0026_LEAK_IS_VALVE_NO11;
			
			break;
		}
		
		case COMMAND_04_0026_LEAK_IS_VALVE_NO11:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(11)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0027_LEAK_VALVE_NO12;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 打开阀门12
		case COMMAND_04_0027_LEAK_VALVE_NO12:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(12);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0028_LEAK_IS_VALVE_NO12;
			
			break;
		}
		
		case COMMAND_04_0028_LEAK_IS_VALVE_NO12:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(12)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0029_LEAK_TIME_START;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		
		//检漏气体排气指令 等待气体排放时间
		case COMMAND_04_0029_LEAK_TIME_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0030_LEAK_IS_TIME;
			
			break;
		}
		
		case COMMAND_04_0030_LEAK_IS_TIME:
		{
			//检漏气体排放等待时间，默认为5min
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_exhaust)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0031_LEAK_VALVE_NO13;
			}
			
			break;
		}
		
		//检漏气体排气指令 关闭阀门1
		case COMMAND_04_0031_LEAK_VALVE_NO13:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(13);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0032_LEAK_IS_VALVE_NO13;
			
			break;
		}
		
		case COMMAND_04_0032_LEAK_IS_VALVE_NO13:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(13)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0033_LEAK_VALVE_NO14;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关闭阀门2
		case COMMAND_04_0033_LEAK_VALVE_NO14:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(14);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0034_LEAK_IS_VALVE_NO14;
			
			break;
		}
		
		case COMMAND_04_0034_LEAK_IS_VALVE_NO14:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(14)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0035_LEAK_VALVE_NO15;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关闭阀门3
		case COMMAND_04_0035_LEAK_VALVE_NO15:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(15);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0036_LEAK_IS_VALVE_NO15;
			
			break;
		}
		
		case COMMAND_04_0036_LEAK_IS_VALVE_NO15:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(15)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0037_LEAK_VALVE_NO16;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关闭阀门4
		case COMMAND_04_0037_LEAK_VALVE_NO16:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(16);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0038_LEAK_IS_VALVE_NO16;
			
			break;
		}
		
		case COMMAND_04_0038_LEAK_IS_VALVE_NO16:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(16)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0039_LEAK_VALVE_NO17;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关闭阀门5
		case COMMAND_04_0039_LEAK_VALVE_NO17:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(17);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0040_LEAK_IS_VALVE_NO17;
			
			break;
		}
		
		case COMMAND_04_0040_LEAK_IS_VALVE_NO17:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(17)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0041_LEAK_VALVE_NO18;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关闭阀门6
		case COMMAND_04_0041_LEAK_VALVE_NO18:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(18);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0042_LEAK_IS_VALVE_NO18;
			
			break;
		}
		
		case COMMAND_04_0042_LEAK_IS_VALVE_NO18:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(18)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0043_LEAK_VALVE_NO19;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关闭阀门7
		case COMMAND_04_0043_LEAK_VALVE_NO19:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(19);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0044_LEAK_IS_VALVE_NO19;
			
			break;
		}
		
		case COMMAND_04_0044_LEAK_IS_VALVE_NO19:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(19)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0045_LEAK_VALVE_NO20;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关闭阀门8
		case COMMAND_04_0045_LEAK_VALVE_NO20:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(20);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0046_LEAK_IS_VALVE_NO20;
			
			break;
		}
		
		case COMMAND_04_0046_LEAK_IS_VALVE_NO20:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(20)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0047_LEAK_VALVE_NO21;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关闭阀门9
		case COMMAND_04_0047_LEAK_VALVE_NO21:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(21);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0048_LEAK_IS_VALVE_NO21;
			
			break;
		}
		
		case COMMAND_04_0048_LEAK_IS_VALVE_NO21:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(21)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0049_LEAK_VALVE_NO22;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关闭阀门10
		case COMMAND_04_0049_LEAK_VALVE_NO22:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(22);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0050_LEAK_IS_VALVE_NO22;
			
			break;
		}
		
		case COMMAND_04_0050_LEAK_IS_VALVE_NO22:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(22)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0051_LEAK_VALVE_NO23;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关闭阀门11
		case COMMAND_04_0051_LEAK_VALVE_NO23:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(23);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0052_LEAK_IS_VALVE_NO23;
			
			break;
		}
		
		case COMMAND_04_0052_LEAK_IS_VALVE_NO23:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(23)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0053_LEAK_VALVE_NO24;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关闭阀门12
		case COMMAND_04_0053_LEAK_VALVE_NO24:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(24);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0054_LEAK_IS_VALVE_NO24;
			
			break;
		}
		
		case COMMAND_04_0054_LEAK_IS_VALVE_NO24:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(24)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0055_LEAK_VALVE_NO25;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		
		//检漏气体排气指令 关近浮动断接器阀门1
		case COMMAND_04_0055_LEAK_VALVE_NO25:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(25);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0056_LEAK_IS_VALVE_NO25;
			
			break;
		}
		
		case COMMAND_04_0056_LEAK_IS_VALVE_NO25:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(25)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0057_LEAK_VALVE_NO26;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关近浮动断接器阀门2
		case COMMAND_04_0057_LEAK_VALVE_NO26:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(26);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0058_LEAK_IS_VALVE_NO26;
			
			break;
		}
		
		case COMMAND_04_0058_LEAK_IS_VALVE_NO26:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(26)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0059_LEAK_VALVE_NO27;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关近浮动断接器阀门3
		case COMMAND_04_0059_LEAK_VALVE_NO27:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(27);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0060_LEAK_IS_VALVE_NO27;
			
			break;
		}
		
		case COMMAND_04_0060_LEAK_IS_VALVE_NO27:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(27)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0061_LEAK_VALVE_NO28;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关近浮动断接器阀门4
		case COMMAND_04_0061_LEAK_VALVE_NO28:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(28);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0062_LEAK_IS_VALVE_NO28;
			
			break;
		}
		
		case COMMAND_04_0062_LEAK_IS_VALVE_NO28:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(28)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0063_LEAK_VALVE_NO29;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关近浮动断接器阀门5
		case COMMAND_04_0063_LEAK_VALVE_NO29:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(29);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0064_LEAK_IS_VALVE_NO29;
			
			break;
		}
		
		case COMMAND_04_0064_LEAK_IS_VALVE_NO29:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(29)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0065_LEAK_VALVE_NO30;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关近浮动断接器阀门6
		case COMMAND_04_0065_LEAK_VALVE_NO30:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(30);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0066_LEAK_IS_VALVE_NO30;
			
			break;
		}
		
		case COMMAND_04_0066_LEAK_IS_VALVE_NO30:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(30)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0067_LEAK_VALVE_NO31;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关近浮动断接器阀门7
		case COMMAND_04_0067_LEAK_VALVE_NO31:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(31);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0068_LEAK_IS_VALVE_NO31;
			
			break;
		}
		
		case COMMAND_04_0068_LEAK_IS_VALVE_NO31:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(31)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_04_0069_LEAK_VALVE_NO32;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//检漏气体排气指令 关近浮动断接器阀门8
		case COMMAND_04_0069_LEAK_VALVE_NO32:
		{
			TGTHT510_supply_stage04_leak_command_valve_on_gas(32);
			
			TGTHT510_supply_ctrl.command=COMMAND_04_0070_LEAK_IS_VALVE_NO32;
			
			break;
		}
		
		case COMMAND_04_0070_LEAK_IS_VALVE_NO32:
		{
			if(TGTHT510_supply_stage04_leak_command_is_valve_on_gas(32)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		case COMMAND_END:
		{
			TGTHT510_supply_ctrl.step=STEP_END;
			
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
**名称：补加阶段4：检漏排气指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_stage04_leak_command_valve_on_gas(uint16 n)
{
	//燃补加接口为R1或者R2，并且，氧补加接口为O1或者O2
	if(((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)||\
	(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2))&&\
	((TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)||\
	(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)))
	{
		switch(n)
		{
			case 1:
			{
				TGTHT510_supply_main_lvb_set(LVb70K);
				
				break;
			}
			
			case 2:
			{
				TGTHT510_supply_main_lvb_set(LVb74K);
				
				break;
			}
			
			case 3:
			{
				TGTHT510_supply_main_lvb_set(LVb68K);
				
				break;
			}
			
			case 4:
			{
				TGTHT510_supply_main_lvb_set(LVb78K);
				
				break;
			}
			
			case 5:
			{
				TGTHT510_supply_main_lvb_set(LVb72K);
				
				break;
			}
			
			case 6:
			{
				TGTHT510_supply_main_lvb_set(LVb76K);
				
				break;
			}
			
			case 7:
			{
				TGTHT510_supply_main_lvb_set(LVb69K);
				
				break;
			}
			
			case 8:
			{
				TGTHT510_supply_main_lvb_set(LVb73K);
				
				break;
			}
			
			case 9:
			{
				TGTHT510_supply_main_lvb_set(LVb67K);
				
				break;
			}
			
			case 10:
			{
				TGTHT510_supply_main_lvb_set(LVb77K);
				
				break;
			}
			
			case 11:
			{
				TGTHT510_supply_main_lvb_set(LVb71K);
				
				break;
			}
			
			case 12:
			{
				TGTHT510_supply_main_lvb_set(LVb75K);
				
				break;
			}
			
			case 13:
			{
				TGTHT510_supply_main_lvb_set(LVb70G);
				
				break;
			}
			
			case 14:
			{
				TGTHT510_supply_main_lvb_set(LVb74G);
				
				break;
			}
			
			case 15:
			{
				TGTHT510_supply_main_lvb_set(LVb68G);
				
				break;
			}
			
			case 16:
			{
				TGTHT510_supply_main_lvb_set(LVb78G);
				
				break;
			}
			
			case 17:
			{
				TGTHT510_supply_main_lvb_set(LVb72G);
				
				break;
			}
			
			case 18:
			{
				TGTHT510_supply_main_lvb_set(LVb76G);
				
				break;
			}
			
			case 19:
			{
				TGTHT510_supply_main_lvb_set(LVb69G);
				
				break;
			}
			
			case 20:
			{
				TGTHT510_supply_main_lvb_set(LVb73G);
				
				break;
			}
			
			case 21:
			{
				TGTHT510_supply_main_lvb_set(LVb67G);
				
				break;
			}
			
			case 22:
			{
				TGTHT510_supply_main_lvb_set(LVb77G);
				
				break;
			}
			
			case 23:
			{
				TGTHT510_supply_main_lvb_set(LVb71G);
				
				break;
			}
			
			case 24:
			{
				TGTHT510_supply_main_lvb_set(LVb75G);
				
				break;
			}
			
			case 25:
			{
				TGTHT510_supply_main_lvb_set(LVb40G);
				
				break;
			}
			
			case 26:
			{
				TGTHT510_supply_main_lvb_set(LVb50G);
				
				break;
			}
			
			case 27:
			{
				TGTHT510_supply_main_lvb_set(LVb60G);
				
				break;
			}
			
			case 28:
			{
				TGTHT510_supply_main_lvb_set(LVb64G);
				
				break;
			}
			
			case 29:
			{
				TGTHT510_supply_main_lvb_set(LVb39G);
				
				break;
			}
			
			case 30:
			{
				TGTHT510_supply_main_lvb_set(LVb49G);
				
				break;
			}
			
			case 31:
			{
				TGTHT510_supply_main_lvb_set(LVb59G);
				
				break;
			}
			
			case 32:
			{
				TGTHT510_supply_main_lvb_set(LVb63G);
				
				break;
			}
			
			default:
			{
				TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
				break;
			}
			
			
		}
		
	}
	
	//燃补加接口为R3或者R4，并且，氧补加接口为O3或者O4
	else if(((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)||\
	(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4))&&\
	((TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)||\
	(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)))
	{
		switch(n)
		{
			case 1:
			{
				TGTHT510_supply_main_lvb_set(LVb70K);
				
				break;
			}
			
			case 2:
			{
				TGTHT510_supply_main_lvb_set(LVb74K);
				
				break;
			}
			
			case 3:
			{
				TGTHT510_supply_main_lvb_set(LVb84K);
				
				break;
			}
			
			case 4:
			{
				TGTHT510_supply_main_lvb_set(LVb86K);
				
				break;
			}
			
			case 5:
			{
				TGTHT510_supply_main_lvb_set(LVb80K);
				
				break;
			}
			
			case 6:
			{
				TGTHT510_supply_main_lvb_set(LVb82K);
				
				break;
			}
			
			case 7:
			{
				TGTHT510_supply_main_lvb_set(LVb69K);
				
				break;
			}
			
			case 8:
			{
				TGTHT510_supply_main_lvb_set(LVb73K);
				
				break;
			}
			
			case 9:
			{
				TGTHT510_supply_main_lvb_set(LVb83K);
				
				break;
			}
			
			case 10:
			{
				TGTHT510_supply_main_lvb_set(LVb85K);
				
				break;
			}
			
			case 11:
			{
				TGTHT510_supply_main_lvb_set(LVb79K);
				
				break;
			}
			
			case 12:
			{
				TGTHT510_supply_main_lvb_set(LVb81K);
				
				break;
			}
			
			case 13:
			{
				TGTHT510_supply_main_lvb_set(LVb70G);
				
				break;
			}
			
			case 14:
			{
				TGTHT510_supply_main_lvb_set(LVb74G);
				
				break;
			}
			
			case 15:
			{
				TGTHT510_supply_main_lvb_set(LVb84G);
				
				break;
			}
			
			case 16:
			{
				TGTHT510_supply_main_lvb_set(LVb86G);
				
				break;
			}
			
			case 17:
			{
				TGTHT510_supply_main_lvb_set(LVb80G);
				
				break;
			}
			
			case 18:
			{
				TGTHT510_supply_main_lvb_set(LVb82G);
				
				break;
			}
			
			case 19:
			{
				TGTHT510_supply_main_lvb_set(LVb69G);
				
				break;
			}
			
			case 20:
			{
				TGTHT510_supply_main_lvb_set(LVb73G);
				
				break;
			}
			
			case 21:
			{
				TGTHT510_supply_main_lvb_set(LVb83G);
				
				break;
			}
			
			case 22:
			{
				TGTHT510_supply_main_lvb_set(LVb85G);
				
				break;
			}
			
			case 23:
			{
				TGTHT510_supply_main_lvb_set(LVb79G);
				
				break;
			}
			
			case 24:
			{
				TGTHT510_supply_main_lvb_set(LVb81G);
				
				break;
			}
			
			case 25:
			{
				TGTHT510_supply_main_lvb_set(LVb40G);
				
				break;
			}
			
			case 26:
			{
				TGTHT510_supply_main_lvb_set(LVb50G);
				
				break;
			}
			
			case 27:
			{
				TGTHT510_supply_main_lvb_set(LVb60G);
				
				break;
			}
			
			case 28:
			{
				TGTHT510_supply_main_lvb_set(LVb64G);
				
				break;
			}
			
			case 29:
			{
				TGTHT510_supply_main_lvb_set(LVb39G);
				
				break;
			}
			
			case 30:
			{
				TGTHT510_supply_main_lvb_set(LVb49G);
				
				break;
			}
			
			case 31:
			{
				TGTHT510_supply_main_lvb_set(LVb59G);
				
				break;
			}
			
			case 32:
			{
				TGTHT510_supply_main_lvb_set(LVb63G);
				
				break;
			}
			
			default:
			{
				TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
				break;
			}
			
			
		}
		
		
	}
	
	else
	{
		TGTHT510_supply_main_pause(ERRNO_LEAK_INTERFACE_ERROR);//检漏排气补加接口解码错误
	}
	
}


/******************************************************************************************
**名称：补加阶段4：检漏排气指令
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_stage04_leak_command_is_valve_on_gas(uint16 n)
{
	//燃补加接口为R1或者R2，并且，氧补加接口为O1或者O2
	if(((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)||\
	(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2))&&\
	((TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)||\
	(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)))
	{
		switch(n)
		{
			case 1:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb68,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb78,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb72,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb76,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_ON)==TRUE)//阀门打开正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 8:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb67,VALVE_ON)==TRUE)//阀门打开正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 10:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb77,VALVE_ON)==TRUE)//阀门打开正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 11:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb71,VALVE_ON)==TRUE)//阀门打开正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 12:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb75,VALVE_ON)==TRUE)//阀门打开正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 13:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 14:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 15:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb68,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 16:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb78,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 17:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb72,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 18:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb76,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 19:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 20:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 21:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb67,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 22:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb77,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 23:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb71,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 24:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb75,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 25:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb40,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 26:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb50,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 27:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb60,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 28:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb64,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 29:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb39,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 30:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb49,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 31:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb59,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 32:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb63,VALVE_OFF)==TRUE)//阀门关闭正确
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
				TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
				break;
			}
			
			
		}
		
	}
	
	//燃补加接口为R3或者R4，并且，氧补加接口为O3或者O4
	else if(((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3)||\
	(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4))&&\
	((TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3)||\
	(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4)))
	{
		switch(n)
		{
			case 1:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb84,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb86,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb80,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb82,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_ON)==TRUE)//阀门打开正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 8:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_ON)==TRUE)//阀门打开正确
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
				if(TGTHT510_supply_main_lvb_get(STATE_LVb83,VALVE_ON)==TRUE)//阀门打开正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 10:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb85,VALVE_ON)==TRUE)//阀门打开正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 11:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb79,VALVE_ON)==TRUE)//阀门打开正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 12:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb81,VALVE_ON)==TRUE)//阀门打开正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 13:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb70,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 14:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb74,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 15:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb84,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 16:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb86,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 17:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb80,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 18:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb82,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 19:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb69,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 20:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb73,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 21:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb83,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 22:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb85,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 23:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb79,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 24:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb81,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 25:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb40,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 26:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb50,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 27:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb60,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 28:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb64,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 29:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb39,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 30:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb49,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 31:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb59,VALVE_OFF)==TRUE)//阀门关闭正确
				{
					return TRUE;
				}
				
				else
				{
					return FALSE;
				}
				
				break;
			}
			
			case 32:
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb63,VALVE_OFF)==TRUE)//阀门关闭正确
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
				TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
				break;
			}
			
			
		}
		
		
	}
	
	else
	{
		TGTHT510_supply_main_pause(ERRNO_LEAK_INTERFACE_ERROR);//检漏排气补加接口解码错误
	}
	
}






