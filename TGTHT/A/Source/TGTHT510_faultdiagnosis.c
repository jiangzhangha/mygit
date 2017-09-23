/**
  ******************************************************************************
  * @file    TGTHT510_faultdiagnosis.c
  * @author  蒋章
  * @version V1.00
  * @date    20150626
  * @brief   空间站核心舱推进管理器遥测状态采集与组帧模块C文件
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"
#include "BM3803MG.h"

extern uint16 TGTHT510_1553B_data_TGTHT100[];				//全局数组，缓存推进遥测线路盒除温度参数以外数据，89字
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[];		//全局数组，缓存推进遥测线路盒复帧A温度数据，65字
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[];		//全局数组，缓存推进遥测线路盒复帧B温度数据，65字
extern uint16 TGTHT510_1553B_data_TGTHT530[];			    //全局数组，缓存压气机电机驱动器遥测数据，12字
extern uint16 TGTHT510_1553B_data_TGTHT520a[];				//全局数组，缓存推进控制驱动器主机遥测，7字
extern uint16 TGTHT510_1553B_data_TGTHT520b[];				//全局数组，缓存推进控制驱动器备机遥测，7字

extern TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;
extern valvecontrol_TypeDef TGTHT510_valvecontrol_struct;//阀门控制数据结构体

extern compressor_state_TypeDef compressor_state;
extern TGTHT510_supply_ctrl_TypeDef TGTHT510_supply_ctrl;
extern CPU_B_receive_data_TypeDef CPU_B_receive_data;

extern struct lregs * regs;


uint16 TGTHT510_fault_data_CG_push[7];						//推进故检-常规遥测参数
uint16 TGTHT510_fault_data_CG_supply[30];					//补加故检-常规遥测参数

fault_deal_TypeDef fault_deal;								//故障处理-全局控制参数

fault_deal_is_CPU_A_done_TypeDef fault_deal_is_CPU_A_done;	//A机发送的故检执行状况

uint16 mode_test;//测试使用，故障模式1为1111，2为2222,3为3333


//推进部分故障检测

fault_TypeDef TGTHT510_fault_push_o_gas1_leak;					//推进故检--氧气瓶1泄漏
fault_TypeDef TGTHT510_fault_push_o_gas2_leak;					//推进故检--氧气瓶2泄漏
fault_TypeDef TGTHT510_fault_push_o_gas3_leak;					//推进故检--氧气瓶3泄漏

fault_TypeDef TGTHT510_fault_push_f_gas1_leak;					//推进故检--燃气瓶1泄漏
fault_TypeDef TGTHT510_fault_push_f_gas2_leak;					//推进故检--燃气瓶2泄漏
fault_TypeDef TGTHT510_fault_push_f_gas3_leak;					//推进故检--燃气瓶3泄漏

fault_TypeDef TGTHT510_fault_push_o_tank1_overpressure;			//推进故检--氧1贮箱超压
fault_TypeDef TGTHT510_fault_push_o_tank2_overpressure;			//推进故检--氧2贮箱超压
fault_TypeDef TGTHT510_fault_push_o_tank3_overpressure;			//推进故检--氧3贮箱超压

fault_TypeDef TGTHT510_fault_push_f_tank1_overpressure;			//推进故检--燃1贮箱超压
fault_TypeDef TGTHT510_fault_push_f_tank2_overpressure;			//推进故检--燃2贮箱超压
fault_TypeDef TGTHT510_fault_push_f_tank3_overpressure;			//推进故检--燃3贮箱超压

fault_valve_leak_TypeDef TGTHT510_fault_push_B_main_valve_leak;	//主份姿控发动机控制阀门泄漏
fault_valve_leak_TypeDef TGTHT510_fault_push_B_less_valve_leak;	//备份姿控发动机控制阀门泄漏
fault_valve_leak_TypeDef TGTHT510_fault_push_C_all_valve_leak;	//C组姿控发动机控制阀门泄漏
fault_valve_leak_TypeDef TGTHT510_fault_push_A_main_valve_leak;	//A组主份姿控发动机控制阀门泄漏
fault_valve_leak_TypeDef TGTHT510_fault_push_A_less_valve_leak;	//A组备份姿控发动机控制阀门泄漏

fault_TypeDef TGTHT510_fault_push_o_tank1_leak;					//推进故检--氧1贮箱泄漏
fault_TypeDef TGTHT510_fault_push_o_tank2_leak;					//推进故检--氧2贮箱泄漏
fault_TypeDef TGTHT510_fault_push_o_tank3_leak;					//推进故检--氧3贮箱泄漏

fault_TypeDef TGTHT510_fault_push_f_tank1_leak;					//推进故检--燃1贮箱泄漏
fault_TypeDef TGTHT510_fault_push_f_tank2_leak;					//推进故检--燃2贮箱泄漏
fault_TypeDef TGTHT510_fault_push_f_tank3_leak;					//推进故检--燃3贮箱泄漏


//补加部分故障检测

fault_TypeDef TGTHT510_fault_supply_TGTHT530;					//补加故检--电机驱动器故障		

fault_TypeDef TGTHT510_fault_supply_cooler_zz;					//补加故检--主份液冷主泵故障		
fault_TypeDef TGTHT510_fault_supply_cooler_zb;					//补加故检--主份液冷备泵故障		
fault_TypeDef TGTHT510_fault_supply_cooler_bz;					//补加故检--备份液冷主泵故障		
fault_TypeDef TGTHT510_fault_supply_cooler_bb;					//补加故检--备份液冷备泵故障

fault_TypeDef TGTHT510_fault_supply_leak_cooler_z;				//补加故检--主份液冷泄漏		
fault_TypeDef TGTHT510_fault_supply_leak_cooler_b;				//补加故检--备份液冷泄漏		
		
fault_TypeDef TGTHT510_fault_supply_compressor_A_in_over;		//补加故检--压气机A入口超压
fault_TypeDef TGTHT510_fault_supply_compressor_B_in_over;		//补加故检--压气机B入口超压
fault_TypeDef TGTHT510_fault_supply_compressor_C_in_over;		//补加故检--压气机C入口超压

fault_TypeDef TGTHT510_fault_supply_compressor_A_motor_over;	//补加故检--压气机A电机腔超压
fault_TypeDef TGTHT510_fault_supply_compressor_B_motor_over;	//补加故检--压气机B电机腔超压
fault_TypeDef TGTHT510_fault_supply_compressor_C_motor_over;	//补加故检--压气机C电机腔超压

fault_TypeDef TGTHT510_fault_supply_compressor_A_hot;			//补加故检--压气机A超温
fault_TypeDef TGTHT510_fault_supply_compressor_B_hot;			//补加故检--压气机B超温
fault_TypeDef TGTHT510_fault_supply_compressor_C_hot;			//补加故检--压气机C超温

fault_TypeDef TGTHT510_fault_supply_o_tank1_overpressure;		//补加故检--氧1补加贮箱超压
fault_TypeDef TGTHT510_fault_supply_o_tank2_overpressure;		//补加故检--氧2补加贮箱超压
fault_TypeDef TGTHT510_fault_supply_o_tank3_overpressure;		//补加故检--氧3补加贮箱超压

fault_TypeDef TGTHT510_fault_supply_f_tank1_overpressure;		//补加故检--燃1补加贮箱超压
fault_TypeDef TGTHT510_fault_supply_f_tank2_overpressure;		//补加故检--燃2补加贮箱超压
fault_TypeDef TGTHT510_fault_supply_f_tank3_overpressure;		//补加故检--燃3补加贮箱超压

fault_TypeDef TGTHT510_fault_supply_compressor_A_break;			//补加故检--压气机A膜片破裂
fault_TypeDef TGTHT510_fault_supply_compressor_B_break;			//补加故检--压气机B膜片破裂
fault_TypeDef TGTHT510_fault_supply_compressor_C_break;			//补加故检--压气机C膜片破裂

fault_TypeDef TGTHT510_fault_supply_o_gas1_leak;				//补加故检--氧气瓶1泄漏
fault_TypeDef TGTHT510_fault_supply_o_gas2_leak;				//补加故检--氧气瓶2泄漏
fault_TypeDef TGTHT510_fault_supply_o_gas3_leak;				//补加故检--氧气瓶3泄漏

fault_TypeDef TGTHT510_fault_supply_f_gas1_leak;				//补加故检--燃气瓶1泄漏
fault_TypeDef TGTHT510_fault_supply_f_gas2_leak;				//补加故检--燃气瓶2泄漏
fault_TypeDef TGTHT510_fault_supply_f_gas3_leak;				//补加故检--燃气瓶3泄漏

fault_TypeDef TGTHT510_fault_supply_pipe_leak_o_tank1;			//补加故检--氧1贮箱补加液路泄漏
fault_TypeDef TGTHT510_fault_supply_pipe_leak_o_tank2;			//补加故检--氧2贮箱补加液路泄漏
fault_TypeDef TGTHT510_fault_supply_pipe_leak_o_tank3;			//补加故检--氧3贮箱补加液路泄漏

fault_TypeDef TGTHT510_fault_supply_pipe_leak_f_tank1;			//补加故检--燃1贮箱补加液路泄漏
fault_TypeDef TGTHT510_fault_supply_pipe_leak_f_tank2;			//补加故检--燃2贮箱补加液路泄漏
fault_TypeDef TGTHT510_fault_supply_pipe_leak_f_tank3;			//补加故检--燃3贮箱补加液路泄漏

fault_TypeDef TGTHT510_fault_supply_interface_o_temperature;	//补加故检--氧吹除口温度异常
fault_TypeDef TGTHT510_fault_supply_interface_f_temperature;	//补加故检--燃吹除口温度异常

fault_TypeDef TGTHT510_fault_supply_in_leak_o_z;				//补加故检--氧主补加管路内漏
fault_TypeDef TGTHT510_fault_supply_in_leak_o_b;				//补加故检--氧备补加管路内漏
fault_TypeDef TGTHT510_fault_supply_in_leak_f_z;				//补加故检--燃主补加管路内漏
fault_TypeDef TGTHT510_fault_supply_in_leak_f_b;				//补加故检--燃备补加管路内漏

fault_TypeDef TGTHT510_fault_supply_temperature_fore_f1;		//补加故检--前向燃1浮动断接器温度异常
fault_TypeDef TGTHT510_fault_supply_temperature_fore_f2;		//补加故检--前向燃2浮动断接器温度异常
fault_TypeDef TGTHT510_fault_supply_temperature_fore_o1;		//补加故检--前向氧1浮动断接器温度异常
fault_TypeDef TGTHT510_fault_supply_temperature_fore_o2;		//补加故检--前向氧2浮动断接器温度异常

fault_TypeDef TGTHT510_fault_supply_temperature_back_f1;		//补加故检--后向燃1浮动断接器温度异常
fault_TypeDef TGTHT510_fault_supply_temperature_back_f2;		//补加故检--后向燃2浮动断接器温度异常
fault_TypeDef TGTHT510_fault_supply_temperature_back_o1;		//补加故检--后向氧1浮动断接器温度异常
fault_TypeDef TGTHT510_fault_supply_temperature_back_o2;		//补加故检--后向氧2浮动断接器温度异常

fault_TypeDef TGTHT510_fault_supply_ka_o_tank1;					//补加故检--氧1贮箱卡滞
fault_TypeDef TGTHT510_fault_supply_ka_o_tank2;					//补加故检--氧2贮箱卡滞
fault_TypeDef TGTHT510_fault_supply_ka_o_tank3;					//补加故检--氧3贮箱卡滞

fault_TypeDef TGTHT510_fault_supply_ka_f_tank1;					//补加故检--燃1贮箱卡滞
fault_TypeDef TGTHT510_fault_supply_ka_f_tank2;					//补加故检--燃2贮箱卡滞
fault_TypeDef TGTHT510_fault_supply_ka_f_tank3;					//补加故检--燃3贮箱卡滞

/******************************************************************************************
**名称：故障检测调试钩子函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_faultdiagnosis_test_hook(void)
{
	//调试使用的钩子函数
	
	//compressor_state.compressor_A_state=COMPRESSOR_RUN;
	//compressor_state.compressor_B_state=COMPRESSOR_RUN;
	//compressor_state.compressor_C_state=COMPRESSOR_RUN;
	
	//TGTHT510_supply_decode_par.compressor_F=DECODE_COMPRESSOR_C;
	//TGTHT510_supply_decode_par.compressor_O=DECODE_COMPRESSOR_C;
}

/******************************************************************************************
**名称：故障检测处理
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_faultdiagnosis_how_to_deal_fault_valve_leak_typedef(fault_valve_leak_TypeDef *p)
{
	if(get_CPU()==CPU_B)//B机
	{
		if(CPU_B_receive_data.is_B_get_power==FALSE)//B机未夺权
		{
			p->faultdiagnosis_count++;
			
			if(p->faultdiagnosis_count>=MAX_FAULTDIAGNOSIS_COUNT)
			{
				p->result=TRUE;//故障发生
				
				p->state=DISABLE;
				
				p->step=FAULT_STEP_NONE;//不再判断故障是否发生
				
				if(TGTHT510_faultdiagnosis_is_CPU_A_done_get_valve_leak(p)==FALSE)
				{
					CPU_ON();//B机夺权
				
					CPU_B_receive_data.is_B_get_power=TRUE;
				}
				
			}
			
			else
			{
				p->step=FAULT_STEP_END;
			}
			
		}
		
		else//B机已夺权
		{
			p->result=TRUE;//故障发生
		
			p->step=FAULT_STEP_NONE;//不再判断故障是否发生
		}
		
	}
	
	else//A机
	{
		p->result=TRUE;//故障发生
		
		p->state=DISABLE;
		
		p->step=FAULT_STEP_NONE;//不再判断故障是否发生
	}
}

/******************************************************************************************
**名称：故障检测处理
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(fault_TypeDef *p,uint16 which_field)
{
	if(get_CPU()==CPU_B)//B机
	{
		if(CPU_B_receive_data.is_B_get_power==FALSE)//B机未夺权
		{
			p->faultdiagnosis_count++;
		
			if(p->faultdiagnosis_count>=MAX_FAULTDIAGNOSIS_COUNT)
			{
				p->result=TRUE;//故障发生
				
				p->state=DISABLE;
				
				if(which_field==FAULT_FIELD1)
				{
					p->fault_field1.step=FAULT_STEP_NONE;//不再判断故障是否发生
				}
				
				else if(which_field==FAULT_FIELD2)
				{
					p->fault_field2.step=FAULT_STEP_NONE;//不再判断故障是否发生
					
				}
				
				else if(which_field==FAULT_FIELD3)
				{
					p->fault_field3.step=FAULT_STEP_NONE;//不再判断故障是否发生
				}
				
				else
				{
					asm("nop;");
				}
				
				if(TGTHT510_faultdiagnosis_is_CPU_A_done_get(p)==FALSE)
				{
					CPU_ON();//B机夺权
				
					CPU_B_receive_data.is_B_get_power=TRUE;
				}
			
			}
			
			else//B机继续进行新一周期故检判断
			{
				if(which_field==FAULT_FIELD1)
				{
					p->fault_field1.step=FAULT_STEP_END;
				}
				
				else if(which_field==FAULT_FIELD2)
				{
					p->fault_field2.step=FAULT_STEP_END;
					
				}
				
				else if(which_field==FAULT_FIELD3)
				{
					p->fault_field3.step=FAULT_STEP_END;
				}
				
				else
				{
					asm("nop;");
				}
			}
			
		}
		
		else//B机已夺权
		{
			p->result=TRUE;//故障发生
			
			p->state=DISABLE;
		
			if(which_field==FAULT_FIELD1)
			{
				p->fault_field1.step=FAULT_STEP_NONE;//不再判断故障是否发生
			}
			
			else if(which_field==FAULT_FIELD2)
			{
				
				p->fault_field2.step=FAULT_STEP_NONE;//不再判断故障是否发生
			}
			
			else if(which_field==FAULT_FIELD3)
			{
				p->fault_field3.step=FAULT_STEP_NONE;//不再判断故障是否发生
			}
			
			else
			{
				asm("nop;");
			}
		}
	
	}
	
	else//A机
	{
		p->result=TRUE;//故障发生
		
		p->state=DISABLE;
		
		if(which_field==FAULT_FIELD1)
		{
			p->fault_field1.step=FAULT_STEP_NONE;//不再判断故障是否发生
		}
		
		else if(which_field==FAULT_FIELD2)
		{
			
			p->fault_field2.step=FAULT_STEP_NONE;//不再判断故障是否发生
		}
		
		else if(which_field==FAULT_FIELD3)
		{
			p->fault_field3.step=FAULT_STEP_NONE;//不再判断故障是否发生
		}
		
		else
		{
			asm("nop;");
		}
		
	}

}

/******************************************************************************************
**名称：A机发送的故检状态查询
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_is_CPU_A_done_get_valve_leak(fault_valve_leak_TypeDef *p)
{
	switch(p->mode)
	{
		case FAULT_MODE_PUSH_LEAK_B_MAIN://推进故障，主份姿控发动机控制阀门泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_B_main_valve_leak_is_done;
		}
		
		case FAULT_MODE_PUSH_LEAK_B_LESS://推进故障，备份姿控发动机控制阀门泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_B_less_valve_leak_is_done;
			
		}
		
		case FAULT_MODE_PUSH_LEAK_C_ALL://推进故障，C组姿控发动机控制阀门泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_C_all_valve_leak_is_done;
			
		}
		
		case FAULT_MODE_PUSH_LEAK_A_MAIN://推进故障，A组主份姿控发动机控制阀门泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_A_main_valve_leak_is_done;
			
		}
			
		case FAULT_MODE_PUSH_LEAK_A_LESS://推进故障，A组备份姿控发动机控制阀门泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_A_less_valve_leak_is_done;
			
		}
		
		default:
		{
			return FALSE;
		}
		
	}
}



/******************************************************************************************
**名称：A机发送的故检状态查询
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_is_CPU_A_done_get(fault_TypeDef *p)
{
	switch(p->mode)
	{
		case FAULT_MODE_PUSH_LEAK_O_GAS1://推进故障，氧1气瓶泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas1_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_GAS2://推进故障，氧2气瓶泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas2_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_GAS3://推进故障，氧3气瓶泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas3_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS1://推进故障，燃1气瓶泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas1_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS2://推进故障，燃2气瓶泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas2_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS3://推进故障，燃3气瓶泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas3_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK1://推进故障，氧1贮箱超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank1_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK2://推进故障，氧2贮箱超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank2_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK3://推进故障，氧3贮箱超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank3_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK1://推进故障，燃1贮箱超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank1_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK2://推进故障，燃2贮箱超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank2_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK3://推进故障，燃3贮箱超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank3_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK1://推进故障，氧1贮箱泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank1_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK2://推进故障，氧2贮箱泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank2_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK3://推进故障，氧3贮箱泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank3_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK1://推进故障，燃1贮箱泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank1_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK2://推进故障，燃2贮箱泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank2_leak_is_done;
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK3://推进故障，燃3贮箱泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank3_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_ZZ://补加故障，主份液冷主泵故障
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_zz_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_ZB://补加故障，主份液冷备泵故障
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_zb_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_BZ://补加故障，备份液冷主泵故障
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_bz_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_BB://补加故障，备份液冷备泵故障
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_bb_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_COOLER_Z://补加故障，主份液冷泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_leak_cooler_z_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_COOLER_B://补加故障，备份液冷泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_leak_cooler_b_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_A_IN://补加故障，压气机A入口超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_in_over_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_B_IN://补加故障，压气机B入口超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_in_over_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_C_IN://补加故障，压气机C入口超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_in_over_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR://补加故障，压气机A电机腔超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_motor_over_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR://补加故障，压气机B电机腔超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_motor_over_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR://补加故障，压气机C电机腔超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_motor_over_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_A_HOT://补加故障，压气机A超温
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_hot_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_B_HOT://补加故障，压气机B超温
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_hot_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_C_HOT://补加故障，压气机C超温
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_hot_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK1://补加故障，氧1补加贮箱超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank1_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK2://补加故障，氧2补加贮箱超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank2_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK3://补加故障，氧3补加贮箱超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank3_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK1://补加故障，燃1补加贮箱超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank1_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK2://补加故障，燃2补加贮箱超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank2_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK3://补加故障，燃3补加贮箱超压
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank3_overpressure_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_A_BREAK://补加故障，压气机A膜片破裂
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_break_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_B_BREAK://补加故障，压气机B膜片破裂
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_break_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_C_BREAK://补加故障，压气机C膜片破裂
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_break_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS1://补加故障，氧1气瓶泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas1_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS2://补加故障，氧2气瓶泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas2_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS3://补加故障，氧3气瓶泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas3_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS1://补加故障，燃1气瓶泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas1_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS2://补加故障，燃2气瓶泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas2_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS3://补加故障，燃3气瓶泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas3_leak_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1://补加故障，氧1贮箱补加液路泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2://补加故障，氧2贮箱补加液路泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3://补加故障，氧3贮箱补加液路泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank3_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1://补加故障，燃1贮箱补加液路泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2://补加故障，燃2贮箱补加液路泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3://补加故障，燃3贮箱补加液路泄漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank3_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_INTERFACE_O_TEMP://补加故障，氧吹除口温度异常
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_interface_o_temperature_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_INTERFACE_F_TEMP://补加故障，燃吹除口温度异常
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_interface_f_temperature_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_O_Z://补加故障，氧主补加管路内漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_o_z_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_O_B://补加故障，氧备补加管路内漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_o_b_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_F_Z://补加故障，燃主补加管路内漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_f_z_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_F_B://补加故障，燃备补加管路内漏
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_f_b_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1://补加故障，前向燃1浮动断接器温度异常
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_f1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2://补加故障，前向燃2浮动断接器温度异常
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_f2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1://补加故障，前向氧1浮动断接器温度异常
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_o1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2://补加故障，前向氧2浮动断接器温度异常
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_o2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1://补加故障，后向燃1浮动断接器温度异常
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_f1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2://补加故障，后向燃2浮动断接器温度异常
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_f2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1://补加故障，后向氧1浮动断接器温度异常
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_o1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2://补加故障，后向氧2浮动断接器温度异常
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_o2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK1://补加故障，氧1贮箱卡滞
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK2://补加故障，氧2贮箱卡滞
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK3://补加故障，氧3贮箱卡滞
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank3_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK1://补加故障，燃1贮箱卡滞
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank1_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK2://补加故障，燃1贮箱卡滞
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank2_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK3://补加故障，燃1贮箱卡滞
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank3_is_done;
			break;
		}
		
		case FAULT_MODE_SUPPLY_TGTHT530://补加故障，电机驱动器故障
		{
			return fault_deal_is_CPU_A_done.TGTHT510_fault_supply_TGTHT530_is_done;
			break;
		}
		
		default:
		{
			return FALSE;
		}
		
	}

}



/******************************************************************************************
**名称：A机发送的故检状态设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_is_CPU_A_done_set(void)
{
	if((fault_deal_is_CPU_A_done.fault_mode_last==FAULT_MODE_NONE)&&\
	(fault_deal_is_CPU_A_done.fault_mode_moment!=FAULT_MODE_NONE))
	{
		switch(fault_deal_is_CPU_A_done.fault_mode_moment)
		{
			case FAULT_MODE_PUSH_LEAK_O_GAS1://推进故障，氧1气瓶泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas1_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_GAS2://推进故障，氧2气瓶泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas2_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_GAS3://推进故障，氧3气瓶泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas3_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_GAS1://推进故障，燃1气瓶泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas1_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_GAS2://推进故障，燃2气瓶泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas2_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_GAS3://推进故障，燃3气瓶泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas3_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_O_TANK1://推进故障，氧1贮箱超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank1_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_O_TANK2://推进故障，氧2贮箱超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank2_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_O_TANK3://推进故障，氧3贮箱超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank3_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_F_TANK1://推进故障，燃1贮箱超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank1_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_F_TANK2://推进故障，燃2贮箱超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank2_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_F_TANK3://推进故障，燃3贮箱超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank3_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_B_MAIN://推进故障，主份姿控发动机控制阀门泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_B_main_valve_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_B_LESS://推进故障，备份姿控发动机控制阀门泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_B_less_valve_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_C_ALL://推进故障，C组姿控发动机控制阀门泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_C_all_valve_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_A_MAIN://推进故障，A组主份姿控发动机控制阀门泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_A_main_valve_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_A_LESS://推进故障，A组备份姿控发动机控制阀门泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_A_less_valve_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_TANK1://推进故障，氧1贮箱泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank1_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_TANK2://推进故障，氧2贮箱泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank2_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_TANK3://推进故障，氧3贮箱泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank3_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_TANK1://推进故障，燃1贮箱泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank1_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_TANK2://推进故障，燃2贮箱泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank2_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_TANK3://推进故障，燃3贮箱泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank3_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_ZZ://补加故障，主份液冷主泵故障
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_zz_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_ZB://补加故障，主份液冷备泵故障
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_zb_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_BZ://补加故障，备份液冷主泵故障
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_bz_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_BB://补加故障，备份液冷备泵故障
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_bb_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_COOLER_Z://补加故障，主份液冷泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_leak_cooler_z_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_COOLER_B://补加故障，备份液冷泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_leak_cooler_b_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_A_IN://补加故障，压气机A入口超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_in_over_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_B_IN://补加故障，压气机B入口超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_in_over_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_C_IN://补加故障，压气机C入口超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_in_over_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR://补加故障，压气机A电机腔超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_motor_over_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR://补加故障，压气机B电机腔超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_motor_over_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR://补加故障，压气机C电机腔超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_motor_over_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_A_HOT://补加故障，压气机A超温
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_hot_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_B_HOT://补加故障，压气机B超温
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_hot_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_C_HOT://补加故障，压气机C超温
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_hot_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_O_TANK1://补加故障，氧1补加贮箱超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank1_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_O_TANK2://补加故障，氧2补加贮箱超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank2_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_O_TANK3://补加故障，氧3补加贮箱超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank3_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_F_TANK1://补加故障，燃1补加贮箱超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank1_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_F_TANK2://补加故障，燃2补加贮箱超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank2_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_F_TANK3://补加故障，燃3补加贮箱超压
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank3_overpressure_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_A_BREAK://补加故障，压气机A膜片破裂
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_break_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_B_BREAK://补加故障，压气机B膜片破裂
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_break_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_C_BREAK://补加故障，压气机C膜片破裂
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_break_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_O_GAS1://补加故障，氧1气瓶泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas1_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_O_GAS2://补加故障，氧2气瓶泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas2_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_O_GAS3://补加故障，氧3气瓶泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas3_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_F_GAS1://补加故障，燃1气瓶泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas1_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_F_GAS2://补加故障，燃2气瓶泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas2_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_F_GAS3://补加故障，燃3气瓶泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas3_leak_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1://补加故障，氧1贮箱补加液路泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2://补加故障，氧2贮箱补加液路泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3://补加故障，氧3贮箱补加液路泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank3_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1://补加故障，燃1贮箱补加液路泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2://补加故障，燃2贮箱补加液路泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3://补加故障，燃3贮箱补加液路泄漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank3_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_INTERFACE_O_TEMP://补加故障，氧吹除口温度异常
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_interface_o_temperature_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_INTERFACE_F_TEMP://补加故障，燃吹除口温度异常
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_interface_f_temperature_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_O_Z://补加故障，氧主补加管路内漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_o_z_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_O_B://补加故障，氧备补加管路内漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_o_b_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_F_Z://补加故障，燃主补加管路内漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_f_z_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_F_B://补加故障，燃备补加管路内漏
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_f_b_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1://补加故障，前向燃1浮动断接器温度异常
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_f1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2://补加故障，前向燃2浮动断接器温度异常
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_f2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1://补加故障，前向氧1浮动断接器温度异常
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_o1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2://补加故障，前向氧2浮动断接器温度异常
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_o2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1://补加故障，后向燃1浮动断接器温度异常
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_f1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2://补加故障，后向燃2浮动断接器温度异常
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_f2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1://补加故障，后向氧1浮动断接器温度异常
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_o1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2://补加故障，后向氧2浮动断接器温度异常
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_o2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_O_TANK1://补加故障，氧1贮箱卡滞
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_O_TANK2://补加故障，氧2贮箱卡滞
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_O_TANK3://补加故障，氧3贮箱卡滞
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank3_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_F_TANK1://补加故障，燃1贮箱卡滞
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank1_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_F_TANK2://补加故障，燃1贮箱卡滞
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank2_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_F_TANK3://补加故障，燃1贮箱卡滞
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank3_is_done=TRUE;
				break;
			}
			
			case FAULT_MODE_SUPPLY_TGTHT530://补加故障，电机驱动器故障
			{
				fault_deal_is_CPU_A_done.TGTHT510_fault_supply_TGTHT530_is_done=TRUE;
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
}






/******************************************************************************************
**名称：故障检测模块初始化函数--A机发送的故检状态初始化
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_is_CPU_A_done_initial(void)
{
	fault_deal_is_CPU_A_done.fault_mode_last=FAULT_MODE_NONE;
	fault_deal_is_CPU_A_done.fault_mode_moment=FAULT_MODE_NONE;
	
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas1_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas2_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_gas3_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas1_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas2_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_gas3_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank1_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank2_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank3_overpressure_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank1_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank2_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank3_overpressure_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_B_main_valve_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_B_less_valve_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_C_all_valve_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_A_main_valve_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_A_less_valve_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank1_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank2_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_o_tank3_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank1_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank2_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_push_f_tank3_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_TGTHT530_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_zz_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_zb_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_bz_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_cooler_bb_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_leak_cooler_z_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_leak_cooler_b_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_in_over_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_in_over_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_in_over_is_done=FALSE;
		
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_motor_over_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_motor_over_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_motor_over_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_hot_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_hot_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_hot_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank1_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank2_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_tank3_overpressure_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank1_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank2_overpressure_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_tank3_overpressure_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_A_break_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_B_break_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_compressor_C_break_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas1_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas2_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_o_gas3_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas1_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas2_leak_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_f_gas3_leak_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank2_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_o_tank3_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank2_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_pipe_leak_f_tank3_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_interface_o_temperature_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_interface_f_temperature_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_o_z_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_o_b_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_f_z_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_in_leak_f_b_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_f1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_f2_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_o1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_fore_o2_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_f1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_f2_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_o1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_temperature_back_o2_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank2_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_o_tank3_is_done=FALSE;
	
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank1_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank2_is_done=FALSE;
	fault_deal_is_CPU_A_done.TGTHT510_fault_supply_ka_f_tank3_is_done=FALSE;

}



/******************************************************************************************
**名称：故障检测模块初始化函数--推进部分
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_faultdiagnosis_supply_struct_mode_add(void)
{
	TGTHT510_fault_supply_TGTHT530.mode=FAULT_MODE_SUPPLY_TGTHT530;//补加故障，电机驱动器故障
	
	TGTHT510_fault_supply_cooler_zz.mode=FAULT_MODE_SUPPLY_COOLER_ZZ;//补加故障，主份液冷主泵故障
	TGTHT510_fault_supply_cooler_zb.mode=FAULT_MODE_SUPPLY_COOLER_ZB;//补加故障，主份液冷备泵故障
	TGTHT510_fault_supply_cooler_bz.mode=FAULT_MODE_SUPPLY_COOLER_BZ;//补加故障，备份液冷主泵故障
	TGTHT510_fault_supply_cooler_bb.mode=FAULT_MODE_SUPPLY_COOLER_BB;//补加故障，备份液冷备泵故障
	
	TGTHT510_fault_supply_leak_cooler_z.mode=FAULT_MODE_SUPPLY_LEAK_COOLER_Z;//补加故障，主份液冷泄漏
	TGTHT510_fault_supply_leak_cooler_b.mode=FAULT_MODE_SUPPLY_LEAK_COOLER_B;//补加故障，备份液冷泄漏
	
	TGTHT510_fault_supply_compressor_A_in_over.mode=FAULT_MODE_SUPPLY_OVER_COMP_A_IN;//补加故障，压气机A入口超压
	TGTHT510_fault_supply_compressor_B_in_over.mode=FAULT_MODE_SUPPLY_OVER_COMP_B_IN;//补加故障，压气机B入口超压
	TGTHT510_fault_supply_compressor_C_in_over.mode=FAULT_MODE_SUPPLY_OVER_COMP_C_IN;//补加故障，压气机C入口超压
	
	TGTHT510_fault_supply_compressor_A_motor_over.mode=FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR;//补加故障，压气机A电机腔超压
	TGTHT510_fault_supply_compressor_B_motor_over.mode=FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR;//补加故障，压气机B电机腔超压
	TGTHT510_fault_supply_compressor_C_motor_over.mode=FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR;//补加故障，压气机C电机腔超压
	
	TGTHT510_fault_supply_compressor_A_hot.mode=FAULT_MODE_SUPPLY_COMP_A_HOT;//补加故障，压气机A超温
	TGTHT510_fault_supply_compressor_B_hot.mode=FAULT_MODE_SUPPLY_COMP_B_HOT;//补加故障，压气机B超温
	TGTHT510_fault_supply_compressor_C_hot.mode=FAULT_MODE_SUPPLY_COMP_C_HOT;//补加故障，压气机C超温
	
	TGTHT510_fault_supply_o_tank1_overpressure.mode=FAULT_MODE_SUPPLY_OVER_O_TANK1;//补加故障，氧1补加贮箱超压
	TGTHT510_fault_supply_o_tank2_overpressure.mode=FAULT_MODE_SUPPLY_OVER_O_TANK2;//补加故障，氧2补加贮箱超压
	TGTHT510_fault_supply_o_tank3_overpressure.mode=FAULT_MODE_SUPPLY_OVER_O_TANK3;//补加故障，氧3补加贮箱超压
	
	TGTHT510_fault_supply_f_tank1_overpressure.mode=FAULT_MODE_SUPPLY_OVER_F_TANK1;//补加故障，燃1补加贮箱超压
	TGTHT510_fault_supply_f_tank2_overpressure.mode=FAULT_MODE_SUPPLY_OVER_F_TANK2;//补加故障，燃2补加贮箱超压
	TGTHT510_fault_supply_f_tank3_overpressure.mode=FAULT_MODE_SUPPLY_OVER_F_TANK3;//补加故障，燃3补加贮箱超压
	
	TGTHT510_fault_supply_compressor_A_break.mode=FAULT_MODE_SUPPLY_COMP_A_BREAK;//补加故障，压气机A膜片破裂
	TGTHT510_fault_supply_compressor_B_break.mode=FAULT_MODE_SUPPLY_COMP_B_BREAK;//补加故障，压气机B膜片破裂
	TGTHT510_fault_supply_compressor_C_break.mode=FAULT_MODE_SUPPLY_COMP_C_BREAK;//补加故障，压气机C膜片破裂
	
	TGTHT510_fault_supply_o_gas1_leak.mode=FAULT_MODE_SUPPLY_LEAK_O_GAS1;//补加故障，氧1气瓶泄漏
	TGTHT510_fault_supply_o_gas2_leak.mode=FAULT_MODE_SUPPLY_LEAK_O_GAS2;//补加故障，氧2气瓶泄漏
	TGTHT510_fault_supply_o_gas3_leak.mode=FAULT_MODE_SUPPLY_LEAK_O_GAS3;//补加故障，氧3气瓶泄漏
	
	TGTHT510_fault_supply_f_gas1_leak.mode=FAULT_MODE_SUPPLY_LEAK_F_GAS1;//补加故障，燃1气瓶泄漏
	TGTHT510_fault_supply_f_gas2_leak.mode=FAULT_MODE_SUPPLY_LEAK_F_GAS2;//补加故障，燃2气瓶泄漏
	TGTHT510_fault_supply_f_gas3_leak.mode=FAULT_MODE_SUPPLY_LEAK_F_GAS3;//补加故障，燃3气瓶泄漏
	
	TGTHT510_fault_supply_pipe_leak_o_tank1.mode=FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1;//补加故障，氧1贮箱补加液路泄漏
	TGTHT510_fault_supply_pipe_leak_o_tank2.mode=FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2;//补加故障，氧2贮箱补加液路泄漏
	TGTHT510_fault_supply_pipe_leak_o_tank3.mode=FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3;//补加故障，氧3贮箱补加液路泄漏
	
	TGTHT510_fault_supply_pipe_leak_f_tank1.mode=FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1;//补加故障，燃1贮箱补加液路泄漏
	TGTHT510_fault_supply_pipe_leak_f_tank2.mode=FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2;//补加故障，燃2贮箱补加液路泄漏
	TGTHT510_fault_supply_pipe_leak_f_tank3.mode=FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3;//补加故障，燃3贮箱补加液路泄漏
	
	TGTHT510_fault_supply_interface_o_temperature.mode=FAULT_MODE_SUPPLY_INTERFACE_O_TEMP;//补加故障，氧吹除口温度异常
	TGTHT510_fault_supply_interface_f_temperature.mode=FAULT_MODE_SUPPLY_INTERFACE_F_TEMP;//补加故障，燃吹除口温度异常
	
	TGTHT510_fault_supply_in_leak_o_z.mode=FAULT_MODE_SUPPLY_IN_LEAK_O_Z;//补加故障，氧主补加管路内漏
	TGTHT510_fault_supply_in_leak_o_b.mode=FAULT_MODE_SUPPLY_IN_LEAK_O_B;//补加故障，氧备补加管路内漏
	TGTHT510_fault_supply_in_leak_f_z.mode=FAULT_MODE_SUPPLY_IN_LEAK_F_Z;//补加故障，燃主补加管路内漏
	TGTHT510_fault_supply_in_leak_f_b.mode=FAULT_MODE_SUPPLY_IN_LEAK_F_B;//补加故障，燃备补加管路内漏
	
	TGTHT510_fault_supply_temperature_fore_f1.mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1;//补加故障，前向燃1浮动断接器温度异常
	TGTHT510_fault_supply_temperature_fore_f2.mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2;//补加故障，前向燃2浮动断接器温度异常
	TGTHT510_fault_supply_temperature_fore_o1.mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1;//补加故障，前向氧1浮动断接器温度异常
	TGTHT510_fault_supply_temperature_fore_o2.mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2;//补加故障，前向氧2浮动断接器温度异常
	
	TGTHT510_fault_supply_temperature_back_f1.mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1;//补加故障，后向燃1浮动断接器温度异常
	TGTHT510_fault_supply_temperature_back_f2.mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2;//补加故障，后向燃2浮动断接器温度异常
	TGTHT510_fault_supply_temperature_back_o1.mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1;//补加故障，后向氧1浮动断接器温度异常
	TGTHT510_fault_supply_temperature_back_o2.mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2;//补加故障，后向氧2浮动断接器温度异常
	
	TGTHT510_fault_supply_ka_o_tank1.mode=FAULT_MODE_SUPPLY_KA_O_TANK1;//补加故障，氧1贮箱卡滞
	TGTHT510_fault_supply_ka_o_tank2.mode=FAULT_MODE_SUPPLY_KA_O_TANK2;//补加故障，氧2贮箱卡滞
	TGTHT510_fault_supply_ka_o_tank3.mode=FAULT_MODE_SUPPLY_KA_O_TANK3;//补加故障，氧3贮箱卡滞
	
	TGTHT510_fault_supply_ka_f_tank1.mode=FAULT_MODE_SUPPLY_KA_F_TANK1;//补加故障，燃1贮箱卡滞
	TGTHT510_fault_supply_ka_f_tank2.mode=FAULT_MODE_SUPPLY_KA_F_TANK2;//补加故障，燃2贮箱卡滞
	TGTHT510_fault_supply_ka_f_tank3.mode=FAULT_MODE_SUPPLY_KA_F_TANK3;//补加故障，燃3贮箱卡滞
	
	
}

/******************************************************************************************
**名称：故障检测模块初始化函数--推进部分
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_faultdiagnosis_push_struct_mode_add(void)
{
	TGTHT510_fault_push_o_gas1_leak.mode=FAULT_MODE_PUSH_LEAK_O_GAS1;//推进故障，氧1气瓶泄漏
	TGTHT510_fault_push_o_gas2_leak.mode=FAULT_MODE_PUSH_LEAK_O_GAS2;//推进故障，氧2气瓶泄漏
	TGTHT510_fault_push_o_gas3_leak.mode=FAULT_MODE_PUSH_LEAK_O_GAS3;//推进故障，氧3气瓶泄漏
	
	TGTHT510_fault_push_f_gas1_leak.mode=FAULT_MODE_PUSH_LEAK_F_GAS1;//推进故障，燃1气瓶泄漏
	TGTHT510_fault_push_f_gas2_leak.mode=FAULT_MODE_PUSH_LEAK_F_GAS2;//推进故障，燃2气瓶泄漏
	TGTHT510_fault_push_f_gas3_leak.mode=FAULT_MODE_PUSH_LEAK_F_GAS3;//推进故障，燃3气瓶泄漏
	
	TGTHT510_fault_push_o_tank1_overpressure.mode=FAULT_MODE_PUSH_OVER_O_TANK1;//推进故障，氧1贮箱超压
	TGTHT510_fault_push_o_tank2_overpressure.mode=FAULT_MODE_PUSH_OVER_O_TANK2;//推进故障，氧2贮箱超压
	TGTHT510_fault_push_o_tank3_overpressure.mode=FAULT_MODE_PUSH_OVER_O_TANK3;//推进故障，氧3贮箱超压
	
	TGTHT510_fault_push_f_tank1_overpressure.mode=FAULT_MODE_PUSH_OVER_F_TANK1;//推进故障，燃1贮箱超压
	TGTHT510_fault_push_f_tank2_overpressure.mode=FAULT_MODE_PUSH_OVER_F_TANK2;//推进故障，燃2贮箱超压
	TGTHT510_fault_push_f_tank3_overpressure.mode=FAULT_MODE_PUSH_OVER_F_TANK3;//推进故障，燃3贮箱超压
	
	TGTHT510_fault_push_B_main_valve_leak.mode=FAULT_MODE_PUSH_LEAK_B_MAIN;//推进故障，主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_B_less_valve_leak.mode=FAULT_MODE_PUSH_LEAK_B_LESS;//推进故障，备份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_C_all_valve_leak.mode=FAULT_MODE_PUSH_LEAK_C_ALL;//推进故障，C组姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_main_valve_leak.mode=FAULT_MODE_PUSH_LEAK_A_MAIN;//推进故障，A组主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_less_valve_leak.mode=FAULT_MODE_PUSH_LEAK_A_LESS;//推进故障，A组备份姿控发动机控制阀门泄漏
	
	TGTHT510_fault_push_o_tank1_leak.mode=FAULT_MODE_PUSH_LEAK_O_TANK1;//推进故障，氧1贮箱泄漏
	TGTHT510_fault_push_o_tank2_leak.mode=FAULT_MODE_PUSH_LEAK_O_TANK2;//推进故障，氧2贮箱泄漏
	TGTHT510_fault_push_o_tank3_leak.mode=FAULT_MODE_PUSH_LEAK_O_TANK3;//推进故障，氧3贮箱泄漏
	
	TGTHT510_fault_push_f_tank1_leak.mode=FAULT_MODE_PUSH_LEAK_F_TANK1;//推进故障，燃1贮箱泄漏
	TGTHT510_fault_push_f_tank2_leak.mode=FAULT_MODE_PUSH_LEAK_F_TANK2;//推进故障，燃2贮箱泄漏
	TGTHT510_fault_push_f_tank3_leak.mode=FAULT_MODE_PUSH_LEAK_F_TANK3;//推进故障，燃3贮箱泄漏
	
}


/******************************************************************************************
**名称：故障检测模块初始化函数--推进部分
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_initial(fault_TypeDef *p,uint16 enable_state)
{
	if(enable_state==ENABLE)
	{
		p->state=ENABLE;						//故检使能
		TGTHT510_faultdiagnosis_push_CG_set(p->mode,FAULT_STATE_NORMAL);
		
	}
	else
	{
		p->state=DISABLE;						//故检禁止
		TGTHT510_faultdiagnosis_push_CG_set(p->mode,FAULT_STATE_DISABLE);
	}
	p->result=FALSE;							//故障未发生
	
	p->fault_field1.time_flag=FALSE;			//计时器1未使能
	p->fault_field1.step=FAULT_STEP_START;		//启动故检
	p->fault_field2.time_flag=FALSE;			//计时器1未使能
	p->fault_field2.step=FAULT_STEP_START;		//启动故检
	p->fault_field3.time_flag=FALSE;			//计时器1未使能
	p->fault_field3.step=FAULT_STEP_START;		//启动故检
	p->faultdiagnosis_count=0;
}

/******************************************************************************************
**名称：故障检测模块初始化函数--推进部分
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_initial(void)
{
	uint16 i;
	
	for(i=0;i<=6;i++)
	{
		TGTHT510_fault_data_CG_push[i]=0x0000;
	}
	
	TGTHT510_fault_data_CG_push[6]=0xffff;
	TGTHT510_fault_data_CG_push[5]=0x000f;
	
	TGTHT510_faultdiagnosis_is_CPU_A_done_initial();
	
	TGTHT510_faultdiagnosis_push_struct_mode_add();
	
	fault_deal.step=FAULT_STEP_NONE;
	fault_deal.fault_mode=FAULT_MODE_NONE;
	fault_deal.compressor_step=FAULT_STEP_NONE;
	fault_deal.time_flag=FALSE;
	mode_test=0x0000;

//调试使用的钩子函数	
	TGTHT510_faultdiagnosis_test_hook();

//推进部分故检初始化----------------------------------------------------------------------

	//氧气瓶1泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,DISABLE);
	
	//氧气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,DISABLE);
	
	//氧气瓶3泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,DISABLE);
	
	//燃气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,DISABLE);
	
	//燃气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,DISABLE);
	
	//燃气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,DISABLE);
	
	//氧1贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,DISABLE);
	
	//氧2贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,DISABLE);
	
	//氧3贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,DISABLE);
	
	//燃1贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,DISABLE);
	
	//燃2贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,DISABLE);
	
	//燃3贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,DISABLE);
	
	//主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_B_main_valve_leak.state=DISABLE;									//故检不使能
	TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_main_valve_leak.faultdiagnosis_count=0;
	
	//备份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_B_less_valve_leak.state=DISABLE;									//故检不使能
	TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_less_valve_leak.faultdiagnosis_count=0;
	
	//C组姿控发动机控制阀门泄漏
	TGTHT510_fault_push_C_all_valve_leak.state=DISABLE;									//故检不使能
	TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_C_all_valve_leak.faultdiagnosis_count=0;
	
	//A组主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_main_valve_leak.state=DISABLE;									//故检不使能
	TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_main_valve_leak.faultdiagnosis_count=0;
	
	//A组备份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_less_valve_leak.state=DISABLE;									//故检不使能
	TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_less_valve_leak.faultdiagnosis_count=0;
	
	//氧1贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,DISABLE);
	
	//氧2贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,DISABLE);
	
	//氧3贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,DISABLE);
	
	//燃1贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,DISABLE);
	
	//燃2贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,DISABLE);
	
	//燃3贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,DISABLE);
	
}


/******************************************************************************************
**名称：故障检测模块初始化函数--补加部分
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_initial(void)
{
	uint16 i;
	
	TGTHT510_faultdiagnosis_supply_struct_mode_add();
	
	for(i=0;i<=29;i++)
	{
		TGTHT510_fault_data_CG_supply[i]=0x0000;
	}
	
	mode_test=0x0000;
	//电机驱动器故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,DISABLE);
	
	//主份液冷主泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,DISABLE);
	
	//主份液冷备泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,DISABLE);
	
	//备份液冷主泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,DISABLE);
	
	//备份液冷备泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,DISABLE);
	
	//主份液冷泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,DISABLE);
	
	//备份液冷泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,DISABLE);
	
	//压气机A入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,DISABLE);
	
	//压气机B入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,DISABLE);
	
	//压气机C入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,DISABLE);
	
	//压气机A电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,DISABLE);
	
	//压气机B电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,DISABLE);
	
	//压气机C电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,DISABLE);
	
	//压气机A超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,DISABLE);
	
	//压气机B超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,DISABLE);
	
	//压气机C超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,DISABLE);
	
	//氧1补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,DISABLE);
	
	//氧2补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,DISABLE);
	
	//氧3补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,DISABLE);
	
	//燃1补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,DISABLE);
	
	//燃2补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,DISABLE);
	
	//燃3补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,DISABLE);
	
	//压气机A膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,DISABLE);
	
	//压气机B膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,DISABLE);
	
	//压气机C膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,DISABLE);
	
	//氧气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,DISABLE);
	
	//氧气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,DISABLE);
	
	//氧气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,DISABLE);
	
	//燃气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,DISABLE);
	
	//燃气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,DISABLE);
	
	//燃气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,DISABLE);
	
	//氧1贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,DISABLE);
	
	//氧2贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,DISABLE);
	
	//氧3贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,DISABLE);
	
	//燃1贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,DISABLE);
	
	//燃2贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,DISABLE);
	
	//燃3贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,DISABLE);
	
	//氧吹除口温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,DISABLE);
	
	//燃吹除口温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,DISABLE);
	
	//氧主补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,DISABLE);
	
	//氧备补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,DISABLE);
	
	//燃主补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,DISABLE);
	
	//燃备补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,DISABLE);
	
	//前向燃1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,DISABLE);
	
	//前向燃2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,DISABLE);
	
	//前向氧1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,DISABLE);
	
	//前向氧2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,DISABLE);
	
	//后向燃1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,DISABLE);
	
	//后向燃2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,DISABLE);
	
	//后向氧1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,DISABLE);
	
	//后向氧2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,DISABLE);
	
	//氧1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,DISABLE);
	
	//氧2贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,DISABLE);
	
	//氧3贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,DISABLE);
	
}

/******************************************************************************************
**名称：故障检测模块主函数--推进部分
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_main(void)
{
	//氧气瓶1泄漏
	if(TGTHT510_fault_push_o_gas1_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_gas1_leak);//时间参数处理
		TGTHT510_faultdiagnosis_push_gas_leak_big(FAULT_O_GAS1);//大漏检测
		TGTHT510_faultdiagnosis_push_gas_leak_small(FAULT_O_GAS1);//小漏检测
		TGTHT510_faultdiagnosis_push_gas_leak_min(FAULT_O_GAS1);//极限值检测
	}
	
	//氧气瓶2泄漏
	if(TGTHT510_fault_push_o_gas2_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_gas2_leak);//时间参数处理
		TGTHT510_faultdiagnosis_push_gas_leak_big(FAULT_O_GAS2);//大漏检测
		TGTHT510_faultdiagnosis_push_gas_leak_small(FAULT_O_GAS2);//小漏检测
		TGTHT510_faultdiagnosis_push_gas_leak_min(FAULT_O_GAS2);//极限值检测
	}
	
	//氧气瓶3泄漏
	if(TGTHT510_fault_push_o_gas3_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_gas3_leak);//时间参数处理
		TGTHT510_faultdiagnosis_push_gas_leak_big(FAULT_O_GAS3);//大漏检测
		TGTHT510_faultdiagnosis_push_gas_leak_small(FAULT_O_GAS3);//小漏检测
		TGTHT510_faultdiagnosis_push_gas_leak_min(FAULT_O_GAS3);//极限值检测
	}
	
	//燃气瓶1泄漏
	if(TGTHT510_fault_push_f_gas1_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_gas1_leak);//时间参数处理
		TGTHT510_faultdiagnosis_push_gas_leak_big(FAULT_F_GAS1);//大漏检测
		TGTHT510_faultdiagnosis_push_gas_leak_small(FAULT_F_GAS1);//小漏检测
		TGTHT510_faultdiagnosis_push_gas_leak_min(FAULT_F_GAS1);//极限值检测
	}
	
	//燃气瓶2泄漏
	if(TGTHT510_fault_push_f_gas2_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_gas2_leak);//时间参数处理
		TGTHT510_faultdiagnosis_push_gas_leak_big(FAULT_F_GAS2);//大漏检测
		TGTHT510_faultdiagnosis_push_gas_leak_small(FAULT_F_GAS2);//小漏检测
		TGTHT510_faultdiagnosis_push_gas_leak_min(FAULT_F_GAS2);//极限值检测
	}
	
	//燃气瓶3泄漏
	if(TGTHT510_fault_push_f_gas3_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_gas3_leak);//时间参数处理
		TGTHT510_faultdiagnosis_push_gas_leak_big(FAULT_F_GAS3);//大漏检测
		TGTHT510_faultdiagnosis_push_gas_leak_small(FAULT_F_GAS3);//小漏检测
		TGTHT510_faultdiagnosis_push_gas_leak_min(FAULT_F_GAS3);//极限值检测
	}
	
	//氧1贮箱超压
	if(TGTHT510_fault_push_o_tank1_overpressure.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_tank1_overpressure);//时间参数处理
		TGTHT510_faultdiagnosis_push_tank_overpressure(FAULT_O_TANK1);
	}
	
	//氧2贮箱超压
	if(TGTHT510_fault_push_o_tank2_overpressure.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_tank2_overpressure);//时间参数处理
		TGTHT510_faultdiagnosis_push_tank_overpressure(FAULT_O_TANK2);
	}
	
	//氧3贮箱超压
	if(TGTHT510_fault_push_o_tank3_overpressure.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_tank3_overpressure);//时间参数处理
		TGTHT510_faultdiagnosis_push_tank_overpressure(FAULT_O_TANK3);
	}
	
	//燃1贮箱超压
	if(TGTHT510_fault_push_f_tank1_overpressure.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_tank1_overpressure);//时间参数处理
		TGTHT510_faultdiagnosis_push_tank_overpressure(FAULT_F_TANK1);
	}
	
	//燃2贮箱超压
	if(TGTHT510_fault_push_f_tank2_overpressure.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_tank2_overpressure);//时间参数处理
		TGTHT510_faultdiagnosis_push_tank_overpressure(FAULT_F_TANK2);
	}
	
	//燃3贮箱超压
	if(TGTHT510_fault_push_f_tank3_overpressure.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_tank3_overpressure);//时间参数处理
		TGTHT510_faultdiagnosis_push_tank_overpressure(FAULT_F_TANK3);
	}
	
	//B组主份发动机泄漏
	if(TGTHT510_fault_push_B_main_valve_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_push_valve_leak(FAULT_B_MAIN_LEAK);
	}
	
	//B组备份发动机泄漏
	if(TGTHT510_fault_push_B_less_valve_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_push_valve_leak(FAULT_B_LESS_LEAK);
	}
	
	//C组发动机泄漏
	if(TGTHT510_fault_push_C_all_valve_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_push_valve_leak(FAULT_C_ALL_LEAK);
	}
	
	//A组主份发动机泄漏
	if(TGTHT510_fault_push_A_main_valve_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_push_valve_leak(FAULT_A_MAIN_LEAK);
	}
	
	//A组备份发动机泄漏
	if(TGTHT510_fault_push_A_less_valve_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_push_valve_leak(FAULT_A_LESS_LEAK);
	}
	
	//氧1贮箱泄漏
	if(TGTHT510_fault_push_o_tank1_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_tank1_leak);//时间参数处理
		TGTHT510_faultdiagnosis_push_tank_leak(FAULT_O_TANK1);
	}
	
	//氧2贮箱泄漏
	if(TGTHT510_fault_push_o_tank2_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_tank2_leak);//时间参数处理
		TGTHT510_faultdiagnosis_push_tank_leak(FAULT_O_TANK2);
	}
	
	//氧3贮箱泄漏
	if(TGTHT510_fault_push_o_tank3_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_o_tank3_leak);//时间参数处理
		TGTHT510_faultdiagnosis_push_tank_leak(FAULT_O_TANK3);
	}
	
	//燃1贮箱泄漏
	if(TGTHT510_fault_push_f_tank1_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_tank1_leak);//时间参数处理
		TGTHT510_faultdiagnosis_push_tank_leak(FAULT_F_TANK1);
	}
	
	//燃2贮箱泄漏
	if(TGTHT510_fault_push_f_tank2_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_tank2_leak);//时间参数处理
		TGTHT510_faultdiagnosis_push_tank_leak(FAULT_F_TANK2);
	}
	
	//燃3贮箱泄漏
	if(TGTHT510_fault_push_f_tank3_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_push_f_tank3_leak);//时间参数处理
		TGTHT510_faultdiagnosis_push_tank_leak(FAULT_F_TANK3);
	}
	
}

/******************************************************************************************
**名称：故障检测模块主函数--补加部分
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_main(void)
{
	//电机驱动器故障
	if(TGTHT510_fault_supply_TGTHT530.state==ENABLE)//使能
	{
		//待补充！！！！
		
	}
	
	//主份液冷主泵故障
	if(TGTHT510_fault_supply_cooler_zz.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_cooler_zz);//时间参数处理
		TGTHT510_faultdiagnosis_supply_cooler(FAULT_COOLER_ZZ);
	}
	
	//主份液冷备泵故障
	if(TGTHT510_fault_supply_cooler_zb.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_cooler_zb);//时间参数处理
		TGTHT510_faultdiagnosis_supply_cooler(FAULT_COOLER_ZB);
	}
	
	//备份液冷主泵故障
	if(TGTHT510_fault_supply_cooler_bz.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_cooler_bz);//时间参数处理
		TGTHT510_faultdiagnosis_supply_cooler(FAULT_COOLER_BZ);
	}
	
	//备份液冷备泵故障
	if(TGTHT510_fault_supply_cooler_bb.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_cooler_bb);//时间参数处理
		TGTHT510_faultdiagnosis_supply_cooler(FAULT_COOLER_BB);
	}
	
	//主份液冷泄漏
	if(TGTHT510_fault_supply_leak_cooler_z.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_leak_cooler_z);//时间参数处理
		TGTHT510_faultdiagnosis_supply_leak_cooler(FAULT_COOLER_Z);
	}
	
	//备份液冷泄漏
	if(TGTHT510_fault_supply_leak_cooler_b.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_leak_cooler_b);//时间参数处理
		TGTHT510_faultdiagnosis_supply_leak_cooler(FAULT_COOLER_B);
	}
	
	//压气机A入口超压
	if(TGTHT510_fault_supply_compressor_A_in_over.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_A_in_over);//时间参数处理
		TGTHT510_faultdiagnosis_supply_over_compressor(FAULT_COMPRESSOR_A_IN_OVER);
	}
	
	//压气机B入口超压
	if(TGTHT510_fault_supply_compressor_B_in_over.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_B_in_over);//时间参数处理
		TGTHT510_faultdiagnosis_supply_over_compressor(FAULT_COMPRESSOR_B_IN_OVER);
	}
	
	//压气机C入口超压
	if(TGTHT510_fault_supply_compressor_C_in_over.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_C_in_over);//时间参数处理
		TGTHT510_faultdiagnosis_supply_over_compressor(FAULT_COMPRESSOR_C_IN_OVER);
	}
	
	//压气机A电机腔超压
	if(TGTHT510_fault_supply_compressor_A_motor_over.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_A_motor_over);//时间参数处理
		TGTHT510_faultdiagnosis_supply_over_compressor(FAULT_COMPRESSOR_A_MOTOR_OVER);
	}
	
	//压气机B电机腔超压
	if(TGTHT510_fault_supply_compressor_B_motor_over.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_B_motor_over);//时间参数处理
		TGTHT510_faultdiagnosis_supply_over_compressor(FAULT_COMPRESSOR_B_MOTOR_OVER);
	}
	
	//压气机C电机腔超压
	if(TGTHT510_fault_supply_compressor_C_motor_over.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_C_motor_over);//时间参数处理
		TGTHT510_faultdiagnosis_supply_over_compressor(FAULT_COMPRESSOR_C_MOTOR_OVER);
	}
	
	//压气机A超温
	if(TGTHT510_fault_supply_compressor_A_hot.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_A_hot);//时间参数处理
		TGTHT510_faultdiagnosis_supply_hot_compressor(FAULT_COMPRESSOR_A_HOT);
	}
	
	//压气机B超温
	if(TGTHT510_fault_supply_compressor_B_hot.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_B_hot);//时间参数处理
		TGTHT510_faultdiagnosis_supply_hot_compressor(FAULT_COMPRESSOR_B_HOT);
	}
	
	//压气机C超温
	if(TGTHT510_fault_supply_compressor_C_hot.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_C_hot);//时间参数处理
		TGTHT510_faultdiagnosis_supply_hot_compressor(FAULT_COMPRESSOR_C_HOT);
	}
	
	//氧1补加贮箱超压
	if(TGTHT510_fault_supply_o_tank1_overpressure.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_o_tank1_overpressure);//时间参数处理
		TGTHT510_faultdiagnosis_supply_tank_overpressure(FAULT_O_TANK1);
	}
	
	//氧2补加贮箱超压
	if(TGTHT510_fault_supply_o_tank2_overpressure.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_o_tank2_overpressure);//时间参数处理
		TGTHT510_faultdiagnosis_supply_tank_overpressure(FAULT_O_TANK2);
	}
	
	//氧3补加贮箱超压
	if(TGTHT510_fault_supply_o_tank3_overpressure.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_o_tank3_overpressure);//时间参数处理
		TGTHT510_faultdiagnosis_supply_tank_overpressure(FAULT_O_TANK3);
	}
	
	//燃1补加贮箱超压
	if(TGTHT510_fault_supply_f_tank1_overpressure.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_f_tank1_overpressure);//时间参数处理
		TGTHT510_faultdiagnosis_supply_tank_overpressure(FAULT_F_TANK1);
	}
	
	//燃2补加贮箱超压
	if(TGTHT510_fault_supply_f_tank2_overpressure.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_f_tank2_overpressure);//时间参数处理
		TGTHT510_faultdiagnosis_supply_tank_overpressure(FAULT_F_TANK2);
	}
	
	//燃3补加贮箱超压
	if(TGTHT510_fault_supply_f_tank3_overpressure.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_f_tank3_overpressure);//时间参数处理
		TGTHT510_faultdiagnosis_supply_tank_overpressure(FAULT_F_TANK3);
	}
	
	//压气机A膜片破裂
	if(TGTHT510_fault_supply_compressor_A_break.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_A_break);//时间参数处理
		TGTHT510_faultdiagnosis_supply_compressor_break(FAULT_COMPRESSOR_A_BREAK);
	}
	
	//压气机B膜片破裂
	if(TGTHT510_fault_supply_compressor_B_break.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_B_break);//时间参数处理
		TGTHT510_faultdiagnosis_supply_compressor_break(FAULT_COMPRESSOR_B_BREAK);
	}
	
	//压气机C膜片破裂
	if(TGTHT510_fault_supply_compressor_C_break.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_compressor_C_break);//时间参数处理
		TGTHT510_faultdiagnosis_supply_compressor_break(FAULT_COMPRESSOR_C_BREAK);
	}
	
	//氧气瓶1泄漏
	if(TGTHT510_fault_supply_o_gas1_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_o_gas1_leak);//时间参数处理
		TGTHT510_faultdiagnosis_supply_gas_leak_big(FAULT_O_GAS1);		//大漏
		TGTHT510_faultdiagnosis_supply_gas_leak_small(FAULT_O_GAS1);	//小漏
		TGTHT510_faultdiagnosis_supply_gas_leak_min(FAULT_O_GAS1);		//极限值
	}
	
	//氧气瓶2泄漏
	if(TGTHT510_fault_supply_o_gas2_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_o_gas2_leak);//时间参数处理
		TGTHT510_faultdiagnosis_supply_gas_leak_big(FAULT_O_GAS2);		//大漏
		TGTHT510_faultdiagnosis_supply_gas_leak_small(FAULT_O_GAS2);	//小漏
		TGTHT510_faultdiagnosis_supply_gas_leak_min(FAULT_O_GAS2);		//极限值
	}
	
	//氧气瓶3泄漏
	if(TGTHT510_fault_supply_o_gas3_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_o_gas3_leak);//时间参数处理
		TGTHT510_faultdiagnosis_supply_gas_leak_big(FAULT_O_GAS3);		//大漏
		TGTHT510_faultdiagnosis_supply_gas_leak_small(FAULT_O_GAS3);	//小漏
		TGTHT510_faultdiagnosis_supply_gas_leak_min(FAULT_O_GAS3);		//极限值
	}
	
	//燃气瓶1泄漏
	if(TGTHT510_fault_supply_f_gas1_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_f_gas1_leak);//时间参数处理
		TGTHT510_faultdiagnosis_supply_gas_leak_big(FAULT_F_GAS1);		//大漏
		TGTHT510_faultdiagnosis_supply_gas_leak_small(FAULT_F_GAS1);	//小漏
		TGTHT510_faultdiagnosis_supply_gas_leak_min(FAULT_F_GAS1);		//极限值
	}
	
	//燃气瓶2泄漏
	if(TGTHT510_fault_supply_f_gas2_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_f_gas2_leak);//时间参数处理
		TGTHT510_faultdiagnosis_supply_gas_leak_big(FAULT_F_GAS2);		//大漏
		TGTHT510_faultdiagnosis_supply_gas_leak_small(FAULT_F_GAS2);	//小漏
		TGTHT510_faultdiagnosis_supply_gas_leak_min(FAULT_F_GAS2);		//极限值
	}
	
	//燃气瓶3泄漏
	if(TGTHT510_fault_supply_f_gas3_leak.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_f_gas3_leak);//时间参数处理
		TGTHT510_faultdiagnosis_supply_gas_leak_big(FAULT_F_GAS3);		//大漏
		TGTHT510_faultdiagnosis_supply_gas_leak_small(FAULT_F_GAS3);	//小漏
		TGTHT510_faultdiagnosis_supply_gas_leak_min(FAULT_F_GAS3);		//极限值
	}
	
	//氧1贮箱补加液路泄漏
	if(TGTHT510_fault_supply_pipe_leak_o_tank1.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_pipe_leak_o_tank1);//时间参数处理
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak(FAULT_O_TANK1);
	}
	
	//氧2贮箱补加液路泄漏
	if(TGTHT510_fault_supply_pipe_leak_o_tank2.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_pipe_leak_o_tank2);//时间参数处理
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak(FAULT_O_TANK2);
	}
	
	//氧3贮箱补加液路泄漏
	if(TGTHT510_fault_supply_pipe_leak_o_tank3.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_pipe_leak_o_tank3);//时间参数处理
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak(FAULT_O_TANK3);
	}
	
	//燃1贮箱补加液路泄漏
	if(TGTHT510_fault_supply_pipe_leak_f_tank1.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_pipe_leak_f_tank1);//时间参数处理
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak(FAULT_F_TANK1);
	}
	
	//燃2贮箱补加液路泄漏
	if(TGTHT510_fault_supply_pipe_leak_f_tank2.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_pipe_leak_f_tank2);//时间参数处理
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak(FAULT_F_TANK2);
	}
	
	//燃3贮箱补加液路泄漏
	if(TGTHT510_fault_supply_pipe_leak_f_tank3.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_pipe_leak_f_tank3);//时间参数处理
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak(FAULT_F_TANK3);
	}
	
	//氧吹除口温度异常
	if(TGTHT510_fault_supply_interface_o_temperature.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_interface_o_temperature);//时间参数处理
		TGTHT510_faultdiagnosis_supply_interface_temperature(FAULT_INTERFACE_O);
	}
	
	//燃吹除口温度异常
	if(TGTHT510_fault_supply_interface_f_temperature.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_interface_f_temperature);//时间参数处理
		TGTHT510_faultdiagnosis_supply_interface_temperature(FAULT_INTERFACE_F);
	}
	
	//氧主补加管路内漏
	if(TGTHT510_fault_supply_in_leak_o_z.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_in_leak_o_z);//时间参数处理
		TGTHT510_faultdiagnosis_supply_in_leak(FAULT_IN_LEAK_O_Z);
	}
	
	//氧备补加管路内漏
	if(TGTHT510_fault_supply_in_leak_o_b.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_in_leak_o_b);//时间参数处理
		TGTHT510_faultdiagnosis_supply_in_leak(FAULT_IN_LEAK_O_B);
	}
	
	//燃主补加管路内漏
	if(TGTHT510_fault_supply_in_leak_f_z.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_in_leak_f_z);//时间参数处理
		TGTHT510_faultdiagnosis_supply_in_leak(FAULT_IN_LEAK_F_Z);
	}
	
	//燃备补加管路内漏
	if(TGTHT510_fault_supply_in_leak_f_b.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_in_leak_f_b);//时间参数处理
		TGTHT510_faultdiagnosis_supply_in_leak(FAULT_IN_LEAK_F_B);
	}
	
	//前向燃1浮动断接器温度异常
	if(TGTHT510_fault_supply_temperature_fore_f1.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_fore_f1);//时间参数处理
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_FORE_F1);
	}
	
	//前向燃2浮动断接器温度异常
	if(TGTHT510_fault_supply_temperature_fore_f2.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_fore_f2);//时间参数处理
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_FORE_F2);
	}
	
	//前向氧1浮动断接器温度异常
	if(TGTHT510_fault_supply_temperature_fore_o1.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_fore_o1);//时间参数处理
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_FORE_O1);
	}
	
	//前向氧2浮动断接器温度异常
	if(TGTHT510_fault_supply_temperature_fore_o2.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_fore_o2);//时间参数处理
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_FORE_O2);
	}
	
	//后向燃1浮动断接器温度异常
	if(TGTHT510_fault_supply_temperature_back_f1.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_back_f1);//时间参数处理
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_BACK_F1);
	}
	
	//后向燃2浮动断接器温度异常
	if(TGTHT510_fault_supply_temperature_back_f2.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_back_f2);//时间参数处理
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_BACK_F2);
	}
	
	//后向氧1浮动断接器温度异常
	if(TGTHT510_fault_supply_temperature_back_o1.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_back_o1);//时间参数处理
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_BACK_O1);
	}
	
	//后向氧2浮动断接器温度异常
	if(TGTHT510_fault_supply_temperature_back_o2.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_temperature_back_o2);//时间参数处理
		TGTHT510_faultdiagnosis_supply_temperature(FAULT_TEMPERATURE_BACK_O2);
	}
	
	//氧1贮箱卡滞
	if(TGTHT510_fault_supply_ka_o_tank1.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_ka_o_tank1);//时间参数处理
		TGTHT510_faultdiagnosis_supply_ka_tank(FAULT_O_TANK1);
	}
	
	//氧2贮箱卡滞
	if(TGTHT510_fault_supply_ka_o_tank2.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_ka_o_tank2);//时间参数处理
		TGTHT510_faultdiagnosis_supply_ka_tank(FAULT_O_TANK2);
	}
	
	//氧3贮箱卡滞
	if(TGTHT510_fault_supply_ka_o_tank3.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_ka_o_tank3);//时间参数处理
		TGTHT510_faultdiagnosis_supply_ka_tank(FAULT_O_TANK3);
	}
	
	//燃1贮箱卡滞
	if(TGTHT510_fault_supply_ka_f_tank1.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_ka_f_tank1);//时间参数处理
		TGTHT510_faultdiagnosis_supply_ka_tank(FAULT_F_TANK1);
	}
	
	//燃2贮箱卡滞
	if(TGTHT510_fault_supply_ka_f_tank2.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_ka_f_tank2);//时间参数处理
		TGTHT510_faultdiagnosis_supply_ka_tank(FAULT_F_TANK2);
	}
	
	//燃3贮箱卡滞
	if(TGTHT510_fault_supply_ka_f_tank3.state==ENABLE)//使能
	{
		TGTHT510_faultdiagnosis_time_dealing(&TGTHT510_fault_supply_ka_f_tank3);//时间参数处理
		TGTHT510_faultdiagnosis_supply_ka_tank(FAULT_F_TANK3);
	}
	
	
}

/******************************************************************************************
**名称：补加流程暂停程序
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_pause(void)
{
	if((TGTHT510_supply_ctrl.state==STATE_RUN)&&(TGTHT510_supply_ctrl.stage!=STAGE_00_NONE))
	{
		TGTHT510_supply_main_pause(ERRNO_FAULT_DIAGNOSIS);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：补加系统阀门置位
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_lvb_set(uint16 code)
{
	if((code>=LVb1K)&&(code<=LVb87G))//输入指令代码为自锁阀开关指令，且合法
	{
		TGTHT510_valvecontrol_struct.command_from_fault=code;//阀门内部地址编码
		TGTHT510_valvecontrol_struct.command_from_fault_time=2;//脉宽200ms
	}
}


/******************************************************************************************
**名称：故障检测模块函数--推进部分，常规遥测参数置位函数--通用函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_CG_set_dealing(uint16 *p,uint16 fault_state,uint16 set_bit)
{
	if(fault_state==FAULT_STATE_DISABLE)//故检状态，不当班，置位1111
	{
		switch(set_bit)
		{
			case FAULT_BIT15_12_SET: //bit15-12设置
			{
				*p = *p | 0xf000;
				break;
			}
			
			case FAULT_BIT11_08_SET: //bit11-8设置
			{
				*p = *p | 0x0f00;
				break;
			}
			
			case FAULT_BIT07_04_SET: //bit7-4设置
			{
				*p = *p | 0x00f0;
				break;
			}
			
			case FAULT_BIT03_00_SET: //bit3-0设置
			{
				*p = *p | 0x000f;
				break;
			}
			
			default:
			{
				break;
			}
			
		}
	}
	
	else if(fault_state==FAULT_STATE_NORMAL)//故检状态，正常，置位0101
	{
		switch(set_bit)
		{
			case FAULT_BIT15_12_SET: //bit15-12设置
			{
				*p = (*p & 0x5fff) | 0x5000;
				break;
			}
			
			case FAULT_BIT11_08_SET: //bit11-8设置
			{
				*p = (*p & 0xf5ff) | 0x0500;
				break;
			}
			
			case FAULT_BIT07_04_SET: //bit7-4设置
			{
				*p = (*p & 0xff5f) | 0x0050;
				break;
			}
			
			case FAULT_BIT03_00_SET: //bit3-0设置
			{
				*p = (*p & 0xfff5) | 0x0005;
				break;
			}
			
			default:
			{
				break;
			}
			
		}
	}
	
	else if(fault_state==FAULT_STATE_ABNORMAL)//故检状态，异常，置位1010
	{
		switch(set_bit)
		{
			case FAULT_BIT15_12_SET: //bit15-12设置
			{
				*p = (*p & 0xafff) | 0xa000;
				break;
			}
			
			case FAULT_BIT11_08_SET: //bit11-8设置
			{
				*p = (*p & 0xfaff) | 0x0a00;
				break;
			}
			
			case FAULT_BIT07_04_SET: //bit7-4设置
			{
				*p = (*p & 0xffaf) | 0x00a0;
				break;
			}
			
			case FAULT_BIT03_00_SET: //bit3-0设置
			{
				*p = (*p & 0xfffa) | 0x000a;
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

/******************************************************************************************
**名称：故障检测模块函数--推进部分，常规遥测参数置位函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_CG_set(uint16 mode,uint16 state)
{
	switch(mode)
	{
		case FAULT_MODE_PUSH_LEAK_O_GAS1://推进故障，氧1气瓶泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[1],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_GAS2://推进故障，氧2气瓶泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[1],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_GAS3://推进故障，氧3气瓶泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[2],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS1://推进故障，燃1气瓶泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[2],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS2://推进故障，燃2气瓶泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[2],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS3://推进故障，燃3气瓶泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[2],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK1://推进故障，氧1贮箱超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[0],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK2://推进故障，氧2贮箱超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[0],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK3://推进故障，氧3贮箱超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[0],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK1://推进故障，燃1贮箱超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[0],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK2://推进故障，燃2贮箱超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[1],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK3://推进故障，燃3贮箱超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[1],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_B_MAIN://推进故障，主份姿控发动机控制阀门泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[5],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_B_LESS://推进故障，备份姿控发动机控制阀门泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[5],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_C_ALL://推进故障，C组姿控发动机控制阀门泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[5],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_A_MAIN://推进故障，A组主份姿控发动机控制阀门泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[4],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_A_LESS://推进故障，A组备份姿控发动机控制阀门泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[4],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK1://推进故障，氧1贮箱泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[3],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK2://推进故障，氧2贮箱泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[3],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK3://推进故障，氧3贮箱泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[3],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK1://推进故障，燃1贮箱泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[3],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK2://推进故障，燃2贮箱泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[4],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK3://推进故障，燃3贮箱泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_push[4],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_ZZ://补加故障，主份液冷主泵故障
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[0],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_ZB://补加故障，主份液冷备泵故障
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[0],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_BZ://补加故障，备份液冷主泵故障
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[0],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_BB://补加故障，备份液冷备泵故障
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[0],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_COOLER_Z://补加故障，主份液冷泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[1],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_COOLER_B://补加故障，备份液冷泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[1],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_A_IN://补加故障，压气机A入口超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[1],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_B_IN://补加故障，压气机B入口超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[1],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_C_IN://补加故障，压气机C入口超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[2],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR://补加故障，压气机A电机腔超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[2],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR://补加故障，压气机B电机腔超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[2],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR://补加故障，压气机C电机腔超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[2],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_A_HOT://补加故障，压气机A超温
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[3],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_B_HOT://补加故障，压气机B超温
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[3],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_C_HOT://补加故障，压气机C超温
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[3],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK1://补加故障，氧1补加贮箱超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[3],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK2://补加故障，氧2补加贮箱超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[4],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK3://补加故障，氧3补加贮箱超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[4],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK1://补加故障，燃1补加贮箱超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[4],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK2://补加故障，燃2补加贮箱超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[4],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK3://补加故障，燃3补加贮箱超压
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[5],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_A_BREAK://补加故障，压气机A膜片破裂
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[5],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_B_BREAK://补加故障，压气机B膜片破裂
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[5],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_C_BREAK://补加故障，压气机C膜片破裂
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[5],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS1://补加故障，氧1气瓶泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[6],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS2://补加故障，氧2气瓶泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[6],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS3://补加故障，氧3气瓶泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[6],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS1://补加故障，燃1气瓶泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[6],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS2://补加故障，燃2气瓶泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[7],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS3://补加故障，燃3气瓶泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[7],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1://补加故障，氧1贮箱补加液路泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[7],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2://补加故障，氧2贮箱补加液路泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[7],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3://补加故障，氧3贮箱补加液路泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[8],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1://补加故障，燃1贮箱补加液路泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[8],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2://补加故障，燃2贮箱补加液路泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[8],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3://补加故障，燃3贮箱补加液路泄漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[8],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_INTERFACE_O_TEMP://补加故障，氧吹除口温度异常
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[9],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_INTERFACE_F_TEMP://补加故障，燃吹除口温度异常
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[9],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_O_Z://补加故障，氧主补加管路内漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[9],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_O_B://补加故障，氧备补加管路内漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[9],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_F_Z://补加故障，燃主补加管路内漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[10],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_F_B://补加故障，燃备补加管路内漏
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[10],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1://补加故障，前向燃1浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[10],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2://补加故障，前向燃2浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[10],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1://补加故障，前向氧1浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[11],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2://补加故障，前向氧2浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[11],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1://补加故障，后向燃1浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[11],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2://补加故障，后向燃2浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[11],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1://补加故障，后向氧1浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[12],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2://补加故障，后向氧2浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[12],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK1://补加故障，氧1贮箱卡滞
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[12],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK2://补加故障，氧2贮箱卡滞
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[12],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK3://补加故障，氧3贮箱卡滞
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[13],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK1://补加故障，燃1贮箱卡滞
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[13],\
			state,FAULT_BIT11_08_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK2://补加故障，燃2贮箱卡滞
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[13],\
			state,FAULT_BIT07_04_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK3://补加故障，燃3贮箱卡滞
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[13],\
			state,FAULT_BIT03_00_SET);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TGTHT530://补加故障，电机驱动器故障
		{
			TGTHT510_faultdiagnosis_push_CG_set_dealing(&TGTHT510_fault_data_CG_supply[14],\
			state,FAULT_BIT15_12_SET);
			
			break;
		}
		
		default:
		{
			break;
		}
	}

}

/******************************************************************************************
**名称：故障检测模块函数--补加部分，常规遥测参数置位函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_CG_set(uint16 mode,uint16 state)
{
	TGTHT510_faultdiagnosis_push_CG_set(mode,state);
	
}


/******************************************************************************************
**名称：故障检测模块函数--补加部分，常规遥测参数置位函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_enable_disable_set(uint16 mode,uint16 state)
{
	switch(mode)
	{
		case FAULT_MODE_PUSH_LEAK_O_GAS1://推进故障，氧1气瓶泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_GAS2://推进故障，氧2气瓶泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_GAS3://推进故障，氧3气瓶泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS1://推进故障，燃1气瓶泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS2://推进故障，燃2气瓶泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_GAS3://推进故障，燃3气瓶泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK1://推进故障，氧1贮箱超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK2://推进故障，氧2贮箱超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_O_TANK3://推进故障，氧3贮箱超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK1://推进故障，燃1贮箱超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK2://推进故障，燃2贮箱超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_OVER_F_TANK3://推进故障，燃3贮箱超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_B_MAIN://推进故障，主份姿控发动机控制阀门泄漏
		{
			if(state==ENABLE)
			{
				TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//故检使能
				TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//故障未发生
				TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
				TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//启动故检
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_NORMAL);
			}
			
			else
			{
				TGTHT510_fault_push_B_main_valve_leak.state=DISABLE;								//故检不使能
				TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//故障未发生
				TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
				TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//启动故检
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
				
			}
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_B_LESS://推进故障，备份姿控发动机控制阀门泄漏
		{
			if(state==ENABLE)
			{
				TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//故检使能
				TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//故障未发生
				TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
				TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//启动故检
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_NORMAL);
				
			}
			
			else
			{
				TGTHT510_fault_push_B_less_valve_leak.state=DISABLE;									//故检使能
				TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//故障未发生
				TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
				TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//启动故检
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
				
			}
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_C_ALL://推进故障，C组姿控发动机控制阀门泄漏
		{
			if(state==ENABLE)
			{
				TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//故检使能
				TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//故障未发生
				TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
				TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//启动故检
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_NORMAL);
				
			}
			
			else
			{
				TGTHT510_fault_push_C_all_valve_leak.state=DISABLE;									//故检使能
				TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//故障未发生
				TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
				TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//启动故检
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
				
			}
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_A_MAIN://推进故障，A组主份姿控发动机控制阀门泄漏
		{
			if(state==ENABLE)
			{
				TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//故检使能
				TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//故障未发生
				TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
				TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//启动故检
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_NORMAL);
				
			}
			
			else
			{
				TGTHT510_fault_push_A_main_valve_leak.state=DISABLE;									//故检使能
				TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//故障未发生
				TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
				TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//启动故检
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
				
			}
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_A_LESS://推进故障，A组备份姿控发动机控制阀门泄漏
		{
			if(state==ENABLE)
			{
				TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//故检使能
				TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//故障未发生
				TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
				TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//启动故检
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_NORMAL);
				
			}
			
			else
			{
				TGTHT510_fault_push_A_less_valve_leak.state=DISABLE;									//故检使能
				TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//故障未发生
				TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
				TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//启动故检
				TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
				
			}
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK1://推进故障，氧1贮箱泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK2://推进故障，氧2贮箱泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_O_TANK3://推进故障，氧3贮箱泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK1://推进故障，燃1贮箱泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK2://推进故障，燃2贮箱泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_LEAK_F_TANK3://推进故障，燃3贮箱泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_ZZ://补加故障，主份液冷主泵故障
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_ZB://补加故障，主份液冷备泵故障
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_BZ://补加故障，备份液冷主泵故障
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COOLER_BB://补加故障，备份液冷备泵故障
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_COOLER_Z://补加故障，主份液冷泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_COOLER_B://补加故障，备份液冷泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_A_IN://补加故障，压气机A入口超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_B_IN://补加故障，压气机B入口超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_C_IN://补加故障，压气机C入口超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR://补加故障，压气机A电机腔超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR://补加故障，压气机B电机腔超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR://补加故障，压气机C电机腔超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_A_HOT://补加故障，压气机A超温
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_B_HOT://补加故障，压气机B超温
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_C_HOT://补加故障，压气机C超温
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK1://补加故障，氧1补加贮箱超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK2://补加故障，氧2补加贮箱超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_O_TANK3://补加故障，氧3补加贮箱超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK1://补加故障，燃1补加贮箱超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK2://补加故障，燃2补加贮箱超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_OVER_F_TANK3://补加故障，燃3补加贮箱超压
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_A_BREAK://补加故障，压气机A膜片破裂
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_B_BREAK://补加故障，压气机B膜片破裂
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_COMP_C_BREAK://补加故障，压气机C膜片破裂
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS1://补加故障，氧1气瓶泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS2://补加故障，氧2气瓶泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_O_GAS3://补加故障，氧3气瓶泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS1://补加故障，燃1气瓶泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS2://补加故障，燃2气瓶泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_LEAK_F_GAS3://补加故障，燃3气瓶泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1://补加故障，氧1贮箱补加液路泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2://补加故障，氧2贮箱补加液路泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3://补加故障，氧3贮箱补加液路泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1://补加故障，燃1贮箱补加液路泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2://补加故障，燃2贮箱补加液路泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3://补加故障，燃3贮箱补加液路泄漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_INTERFACE_O_TEMP://补加故障，氧吹除口温度异常
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_INTERFACE_F_TEMP://补加故障，燃吹除口温度异常
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_O_Z://补加故障，氧主补加管路内漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_O_B://补加故障，氧备补加管路内漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_F_Z://补加故障，燃主补加管路内漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_IN_LEAK_F_B://补加故障，燃备补加管路内漏
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1://补加故障，前向燃1浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2://补加故障，前向燃2浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1://补加故障，前向氧1浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2://补加故障，前向氧2浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1://补加故障，后向燃1浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2://补加故障，后向燃2浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1://补加故障，后向氧1浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2://补加故障，后向氧2浮动断接器温度异常
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK1://补加故障，氧1贮箱卡滞
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK2://补加故障，氧2贮箱卡滞
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_O_TANK3://补加故障，氧3贮箱卡滞
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK1://补加故障，燃1贮箱卡滞
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK2://补加故障，燃2贮箱卡滞
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_KA_F_TANK3://补加故障，燃3贮箱卡滞
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_TGTHT530://补加故障，电机驱动器故障
		{
			TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,state);
			
			break;
		}
		
		case FAULT_MODE_PUSH_ALL://全部补加故障，推进部分
		{
			TGTHT510_faultdiagnosis_push_all_enable_disable_set(state);
			
			break;
		}
		
		case FAULT_MODE_SUPPLY_ALL://全部补加故障，补加部分
		{
			TGTHT510_faultdiagnosis_supply_all_enable_disable_set(state);
			
			break;
		}
		
		case FAULT_MODE_ALL://全部补加
		{
			TGTHT510_faultdiagnosis_push_all_enable_disable_set(state);
			TGTHT510_faultdiagnosis_supply_all_enable_disable_set(state);
			
			break;
		}
		
		default:
		{
			break;
		}
	}

}

/******************************************************************************************
**名称：故障检测模块时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_all_enable_disable_set(uint16 state)
{
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,state);
			
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,state);
			
	if(state==ENABLE)
	{
		TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//故检使能
		TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//故障未发生
		TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
		TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//启动故检
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_NORMAL);
	}
			
	else
	{
		TGTHT510_fault_push_B_main_valve_leak.state=DISABLE;								//故检不使能
		TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//故障未发生
		TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
		TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//启动故检
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
				
	}
	
	if(state==ENABLE)
	{
		TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//故检使能
		TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//故障未发生
		TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
		TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//启动故检
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_NORMAL);
				
	}
			
	else
	{
		TGTHT510_fault_push_B_less_valve_leak.state=DISABLE;									//故检使能
		TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//故障未发生
		TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
		TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//启动故检
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
				
	}
	
	if(state==ENABLE)
	{
		TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//故检使能
		TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//故障未发生
		TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
		TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//启动故检
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_NORMAL);
				
	}
			
	else
	{
		TGTHT510_fault_push_C_all_valve_leak.state=DISABLE;									//故检使能
		TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//故障未发生
		TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
		TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//启动故检
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
				
	}
	
	if(state==ENABLE)
	{
		TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//故检使能
		TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//故障未发生
		TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
		TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//启动故检
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_NORMAL);
				
	}
			
	else
	{
		TGTHT510_fault_push_A_main_valve_leak.state=DISABLE;									//故检使能
		TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//故障未发生
		TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
		TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//启动故检
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
		
	}
	
	if(state==ENABLE)
	{
		TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//故检使能
		TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//故障未发生
		TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
		TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//启动故检
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_NORMAL);
				
	}
			
	else
	{
		TGTHT510_fault_push_A_less_valve_leak.state=DISABLE;									//故检使能
		TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//故障未发生
		TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
		TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//启动故检
		TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
				
	}
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,state);	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,state);
	
}


/******************************************************************************************
**名称：故障检测模块时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_all_enable_disable_set(uint16 state)
{
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,state);
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,state);
	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,state);

}

/******************************************************************************************
**名称：故障检测模块时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_time_dealing(fault_TypeDef *f)
{
	if(f->fault_field1.time_flag==TRUE)
	{
		f->fault_field1.time_count++;
	}
	
	else
	{
		f->fault_field1.time_count=0;
	}
	
	if(f->fault_field2.time_flag==TRUE)
	{
		f->fault_field2.time_count++;
	}
	
	else
	{
		f->fault_field2.time_count=0;
	}
	
	if(f->fault_field3.time_flag==TRUE)
	{
		f->fault_field3.time_count++;
	}
	
	else
	{
		f->fault_field3.time_count=0;
	}
	
}

/******************************************************************************************
**名称：故障检测模块时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_time1_start(fault_TypeDef *f)
{
	f->fault_field1.time_flag=TRUE;
	f->fault_field1.time_count=0;
}

/******************************************************************************************
**名称：故障检测模块时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_time1_end(fault_TypeDef *f)
{
	f->fault_field1.time_flag=FALSE;
}

/******************************************************************************************
**名称：故障检测模块时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_time2_start(fault_TypeDef *f)
{
	f->fault_field2.time_flag=TRUE;
	f->fault_field2.time_count=0;
}

/******************************************************************************************
**名称：故障检测模块时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_time2_end(fault_TypeDef *f)
{
	f->fault_field2.time_flag=FALSE;
}

/******************************************************************************************
**名称：故障检测模块时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_time1_is_get(fault_TypeDef *f,uint16 val)
{
	if(f->fault_field1.time_count>=val)
	{
		TGTHT510_faultdiagnosis_time1_end(f);
		
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**名称：故障检测模块时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_time2_is_get(fault_TypeDef *f,uint16 val)
{
	if(f->fault_field2.time_count>=val)
	{
		TGTHT510_faultdiagnosis_time2_end(f);
		
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**名称： 气瓶检漏4取3处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_gas_leak_min_four_of_three(uint16 *p,uint16 door_val)
{
	uint16 i,n;
	
	n=0;
	
	for(i=0;i<=3;i++)
	{
		if(p[i]<=door_val)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;//判断故障发生
	}
	
	else
	{
		return FALSE;//判断故障未发生
	}
}

/******************************************************************************************
**名称： 气瓶检漏4取3处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_gas_leak_four_of_three(uint16 *p,uint16 door_val)
{
	uint16 i,n;
	
	n=0;
	
	for(i=0;i<=3;i++)
	{
		if((p[i]>p[i+1])&&(((uint16)(abs(p[i]-p[i+1])))>door_val))
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;//判断故障发生
	}
	
	else
	{
		return FALSE;//判断故障未发生
	}
}

/******************************************************************************************
**名称：推进故障检测模块--气瓶泄漏--获取压力值
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//氧气瓶1泄漏
	{
		return TGTHT510_1553B_data_TGTHT100[0];//PTt1	
	}
	
	else if(gas_leak==FAULT_O_GAS2)//氧气瓶2泄漏
	{
		return TGTHT510_1553B_data_TGTHT100[2];//PTt3
	}
	
	else if(gas_leak==FAULT_O_GAS3)//氧气瓶3泄漏
	{
		return TGTHT510_1553B_data_TGTHT100[4];//PTt5
	}
	
	else if(gas_leak==FAULT_F_GAS1)//燃气瓶1泄漏
	{
		return TGTHT510_1553B_data_TGTHT100[1];//PTt2
	}
	
	else if(gas_leak==FAULT_F_GAS2)//燃气瓶2泄漏
	{
		return TGTHT510_1553B_data_TGTHT100[3];//PTt4
	}
	
	else if(gas_leak==FAULT_F_GAS3)//燃气瓶3泄漏
	{
		return TGTHT510_1553B_data_TGTHT100[5];//PTt6
	}
	
	else
	{
		return 0;
	}
	
}



/******************************************************************************************
**名称：推进故障检测模块--气瓶泄漏--大漏判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
氧气瓶1泄漏，大漏：
采集压力PTt1，间隔30s，采集5个周期，得到4个差值，至少3个差值大于0.1MPa，故障成立。

氧气瓶2泄漏，大漏：
采集压力PTt3，间隔30s，采集5个周期，得到4个差值，至少3个差值大于0.1MPa，故障成立。

氧气瓶3泄漏，大漏：
采集压力PTt5，间隔30s，采集5个周期，得到4个差值，至少3个差值大于0.1MPa，故障成立。

燃气瓶1泄漏，大漏：
采集压力PTt2，间隔30s，采集5个周期，得到4个差值，至少3个差值大于0.1MPa，故障成立。

燃气瓶2泄漏，大漏：
采集压力PTt4，间隔30s，采集5个周期，得到4个差值，至少3个差值大于0.1MPa，故障成立。

燃气瓶3泄漏，大漏：
采集压力PTt6，间隔30s，采集5个周期，得到4个差值，至少3个差值大于0.1MPa，故障成立。
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_gas_leak_big(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//氧气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(&TGTHT510_fault_push_o_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//氧气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(&TGTHT510_fault_push_o_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//氧气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(&TGTHT510_fault_push_o_gas3_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//燃气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(&TGTHT510_fault_push_f_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//燃气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(&TGTHT510_fault_push_f_gas2_leak,gas_leak);	
	}
	
	else if(gas_leak==FAULT_F_GAS3)//燃气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(&TGTHT510_fault_push_f_gas3_leak,gas_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：推进故障检测模块--气瓶泄漏--大漏判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：

-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_gas_leak_big_dealing(fault_TypeDef *p,uint16 gas_leak)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力，第一次
		{
			p->fault_field1.value[0]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://定时30s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://判断30s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://采集压力，第二次
		{
			p->fault_field1.value[1]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://定时30s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://判断30s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://采集压力，第三次
		{
			p->fault_field1.value[2]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO8;
			
			break;
		}
		
		case FAULT_STEP_NO8://定时30s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://判断30s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://采集压力，第四次
		{
			p->fault_field1.value[3]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO11;
			
			break;
		}
		
		case FAULT_STEP_NO11://定时30s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://判断30s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://采集压力，第五次
		{
			p->fault_field1.value[4]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO14;
			
			break;
		}
		
		case FAULT_STEP_NO14://处理
		{
			if(TGTHT510_faultdiagnosis_push_gas_leak_four_of_three(p->fault_field1.value,FAULT_CONST_PRESSURE_0E1)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
				
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}	
	}
	
}


/******************************************************************************************
**名称：推进故障检测模块--气瓶泄漏--小漏判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_gas_leak_small(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//氧气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(&TGTHT510_fault_push_o_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//氧气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(&TGTHT510_fault_push_o_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//氧气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(&TGTHT510_fault_push_o_gas3_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//燃气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(&TGTHT510_fault_push_f_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//燃气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(&TGTHT510_fault_push_f_gas2_leak,gas_leak);	
	}
	
	else if(gas_leak==FAULT_F_GAS3)//燃气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(&TGTHT510_fault_push_f_gas3_leak,gas_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：推进故障检测模块--气瓶泄漏--小漏判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_gas_leak_small_dealing(fault_TypeDef *p,uint16 gas_leak)
{
	switch(p->fault_field2.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field2.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力，第一次
		{
			p->fault_field2.value[0]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://定时12min开始
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://判断12min定时是否到
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_12MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://采集压力，第二次
		{
			p->fault_field2.value[1]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://定时12min开始
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://判断12min定时是否到
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_12MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://采集压力，第三次
		{
			p->fault_field2.value[2]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO8;
			
			break;
		}
		
		case FAULT_STEP_NO8://定时12min开始
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://判断12min定时是否到
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_12MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://采集压力，第四次
		{
			p->fault_field2.value[3]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO11;
			
			break;
		}
		
		case FAULT_STEP_NO11://定时12min开始
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://判断12min定时是否到
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_12MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://采集压力，第五次
		{
			p->fault_field2.value[4]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO14;
			
			break;
		}
		
		case FAULT_STEP_NO14://处理
		{
			if(TGTHT510_faultdiagnosis_push_gas_leak_four_of_three(p->fault_field2.value,FAULT_CONST_PRESSURE_0E14)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD2);
			}
			
			else
			{
				p->fault_field2.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field2.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}


/******************************************************************************************
**名称：推进故障检测模块--气瓶泄漏--极限值判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：连续4帧中3帧值小于等于P_min_gas，则判断故障成立
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_gas_leak_min(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//氧气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(&TGTHT510_fault_push_o_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//氧气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(&TGTHT510_fault_push_o_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//氧气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(&TGTHT510_fault_push_o_gas3_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//燃气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(&TGTHT510_fault_push_f_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//燃气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(&TGTHT510_fault_push_f_gas2_leak,gas_leak);	
	}
	
	else if(gas_leak==FAULT_F_GAS3)//燃气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(&TGTHT510_fault_push_f_gas3_leak,gas_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}


/******************************************************************************************
**名称：推进故障检测模块--气瓶泄漏--极限值判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_gas_leak_min_dealing(fault_TypeDef *p,uint16 gas_leak)
{
	switch(p->fault_field3.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field3.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力，第一次
		{
			p->fault_field3.value[0]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://采集压力，第二次
		{
			p->fault_field3.value[1]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://采集压力，第三次
		{
			p->fault_field3.value[2]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://采集压力，第四次
		{
			p->fault_field3.value[3]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://处理
		{
			if(TGTHT510_faultdiagnosis_push_gas_leak_min_four_of_three(&(p->fault_field3.value[0]),FAULT_CONST_PRESSURE_MIN_GAS)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD3);
			}
			
			else
			{
				p->fault_field3.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field3.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}


/******************************************************************************************
**名称：推进故障检测模块--贮箱超压--获取压力值
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(uint16 tank_overpressure,uint16 n)
{
	if(tank_overpressure==FAULT_O_TANK1)
	{
		if(n==1)
		{
			return TGTHT510_1553B_data_TGTHT100[12];//PTt13
		}
		
		else if(n==2)
		{
			return TGTHT510_1553B_data_TGTHT100[18];//PTt19
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(tank_overpressure==FAULT_O_TANK2)
	{
		if(n==1)
		{
			return TGTHT510_1553B_data_TGTHT100[14];//PTt15
		}
		
		else if(n==2)
		{
			return TGTHT510_1553B_data_TGTHT100[20];//PTt21
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(tank_overpressure==FAULT_O_TANK3)
	{
		if(n==1)
		{
			return TGTHT510_1553B_data_TGTHT100[16];//PTt17
		}
		
		else if(n==2)
		{
			return TGTHT510_1553B_data_TGTHT100[22];//PTt23
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(tank_overpressure==FAULT_F_TANK1)
	{
		if(n==1)
		{
			return TGTHT510_1553B_data_TGTHT100[13];//PTt14
		}
		
		else if(n==2)
		{
			return TGTHT510_1553B_data_TGTHT100[19];//PTt20
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(tank_overpressure==FAULT_F_TANK2)
	{
		if(n==1)
		{
			return TGTHT510_1553B_data_TGTHT100[15];//PTt16
		}
		
		else if(n==2)
		{
			return TGTHT510_1553B_data_TGTHT100[21];//PTt22
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(tank_overpressure==FAULT_F_TANK3)
	{
		if(n==1)
		{
			return TGTHT510_1553B_data_TGTHT100[17];//PTt18
		}
		
		else if(n==2)
		{
			return TGTHT510_1553B_data_TGTHT100[23];//PTt24
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
**名称：推进故障检测模块--贮箱超压--超压处理
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_tank_overpressure_is_over(uint16 *p,uint16 door_val)
{
	uint16 i,n;
	
	n=0;
	
	for(i=0;i<=6;i=i+2)
	{
		if((p[i]>door_val)||(p[i+1]>door_val))
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;//故障成立
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**名称：推进故障检测模块--贮箱超压--超压处理
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_tank_overpressure(uint16 tank_overpressure)
{
	if(tank_overpressure==FAULT_O_TANK1)//故障检测--氧1贮箱
	{
		TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(&TGTHT510_fault_push_o_tank1_overpressure,\
		tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_O_TANK2)//故障检测--氧2贮箱
	{
		TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(&TGTHT510_fault_push_o_tank2_overpressure,\
		tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_O_TANK3)//故障检测--氧3贮箱
	{
		TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(&TGTHT510_fault_push_o_tank3_overpressure,\
		tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_F_TANK1)//故障检测--燃1贮箱
	{
		TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(&TGTHT510_fault_push_f_tank1_overpressure,\
		tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_F_TANK2)//故障检测--燃2贮箱
	{
		TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(&TGTHT510_fault_push_f_tank2_overpressure,\
		tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_F_TANK3)//故障检测--燃3贮箱
	{
		TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(&TGTHT510_fault_push_f_tank3_overpressure,\
		tank_overpressure);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：推进故障检测模块--贮箱超压--超压处理
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_tank_overpressure_dealing(fault_TypeDef *p,uint16 tank_overpressure)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力
		{
			p->fault_field1.value[0]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,1);
			
			p->fault_field1.value[1]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,2);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://采集压力
		{
			p->fault_field1.value[2]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,1);
			
			p->fault_field1.value[3]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,2);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://采集压力
		{
			p->fault_field1.value[4]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,1);
			
			p->fault_field1.value[5]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,2);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://采集压力
		{
			p->fault_field1.value[6]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,1);
			
			p->fault_field1.value[7]=TGTHT510_faultdiagnosis_push_tank_overpressure_get_pressure(tank_overpressure,2);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://处理
		{
			if(TGTHT510_faultdiagnosis_push_tank_overpressure_is_over(p->fault_field1.value,FAULT_CONST_PRESSURE_OVER)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**名称：推进故障检测模块--发动机泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(uint16 valve_leak,uint16 n,uint16 *p)
{
	if(valve_leak==FAULT_B_MAIN_LEAK)//B组主份发动机泄漏
	{
		if(n==1)//法兰温度
		{
			p[0]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[4]);//B1法兰温度
			p[1]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[6]);//B3法兰温度
			p[2]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[8]);//B5法兰温度
			p[3]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[10]);//B7法兰温度
			p[4]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[12]);//B9法兰温度
			p[5]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[14]);//B11法兰温度
			p[6]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[16]);//B13法兰温度
			p[7]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[18]);//B15法兰温度
		}
		
		else if(n==2)//氧阀温度
		{
			p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[30]>>4)&0xfffc;//B1氧阀温度
			p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_A[31]>>4)&0xfffc;//B3氧阀温度
			p[2]=(TGTHT510_1553B_data_TGTHT100_Temper_A[32]>>4)&0xfffc;//B5氧阀温度
			p[3]=(TGTHT510_1553B_data_TGTHT100_Temper_A[33]>>4)&0xfffc;//B7氧阀温度
			p[4]=(TGTHT510_1553B_data_TGTHT100_Temper_A[34]>>4)&0xfffc;//B9氧阀温度
			p[5]=(TGTHT510_1553B_data_TGTHT100_Temper_A[35]>>4)&0xfffc;//B11氧阀温度
			p[6]=(TGTHT510_1553B_data_TGTHT100_Temper_A[36]>>4)&0xfffc;//B13氧阀温度
			p[7]=(TGTHT510_1553B_data_TGTHT100_Temper_A[37]>>4)&0xfffc;//B15氧阀温度
		}
		
		else//无效
		{
			p[0]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[1]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[2]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[3]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[4]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[5]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[6]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[7]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		}
	}
	
	else if(valve_leak==FAULT_B_LESS_LEAK)//B组备份发动机泄漏
	{
		if(n==1)//法兰温度
		{
			p[0]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[5]);//B2法兰温度
			p[1]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[7]);//B4法兰温度
			p[2]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[9]);//B6法兰温度
			p[3]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[11]);//B8法兰温度
			p[4]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[13]);//B10法兰温度
			p[5]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[15]);//B12法兰温度
			p[6]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[17]);//B14法兰温度
			p[7]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[19]);//B16法兰温度
		}
		
		else if(n==2)//氧阀温度
		{
			p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[38]>>4)&0xfffc;//B2氧阀温度
			p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_A[38]<<4)&0x3fff;//B4氧阀温度
			p[2]=(TGTHT510_1553B_data_TGTHT100_Temper_A[39]>>4)&0xfffc;//B6氧阀温度
			p[3]=(TGTHT510_1553B_data_TGTHT100_Temper_A[39]<<4)&0x3fff;//B8氧阀温度
			p[4]=(TGTHT510_1553B_data_TGTHT100_Temper_A[40]>>4)&0xfffc;//B10氧阀温度
			p[5]=(TGTHT510_1553B_data_TGTHT100_Temper_A[40]<<4)&0x3fff;//B12氧阀温度
			p[6]=(TGTHT510_1553B_data_TGTHT100_Temper_A[41]>>4)&0xfffc;//B14氧阀温度
			p[7]=(TGTHT510_1553B_data_TGTHT100_Temper_A[41]<<4)&0x3fff;//B16氧阀温度
		}
		
		else//无效
		{
			p[0]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[1]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[2]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[3]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[4]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[5]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[6]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[7]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		}
	}
	
	else if(valve_leak==FAULT_C_ALL_LEAK)//C组发动机泄漏
	{
		if(n==1)//法兰温度
		{
			p[0]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[20]);//C1法兰温度
			p[1]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[21]);//C2法兰温度
			p[2]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[22]);//C3法兰温度
			p[3]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[23]);//C4法兰温度
			p[4]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[24]);//C5法兰温度
			p[5]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[25]);//C6法兰温度
			p[6]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[7]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		}
		
		else if(n==2)//氧阀温度
		{
			p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[42]>>4)&0xfffc;//C1氧阀温度
			p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_A[43]>>4)&0xfffc;//C2氧阀温度
			p[2]=(TGTHT510_1553B_data_TGTHT100_Temper_A[44]>>4)&0xfffc;//C3氧阀温度
			p[3]=(TGTHT510_1553B_data_TGTHT100_Temper_A[45]>>4)&0xfffc;//C4氧阀温度
			p[4]=(TGTHT510_1553B_data_TGTHT100_Temper_A[46]>>4)&0xfffc;//C5氧阀温度
			p[5]=(TGTHT510_1553B_data_TGTHT100_Temper_A[47]>>4)&0xfffc;//C6氧阀温度
			p[6]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[7]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			
		}
		
		else//无效
		{
			p[0]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[1]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[2]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[3]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[4]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[5]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[6]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[7]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		}
	}
	
	else if(valve_leak==FAULT_A_MAIN_LEAK)//A组主份发动机泄漏
	{
		if(n==1)//法兰温度
		{
			p[0]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[0]);//A1法兰温度
			p[1]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[2]);//A3法兰温度
			p[2]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[3]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[4]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[5]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[6]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[7]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		}
		
		else if(n==2)//氧阀温度
		{
			p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[26]>>4)&0xfffc;//A1氧阀温度
			p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_A[28]>>4)&0xfffc;//A3氧阀温度
			p[2]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[3]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[4]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[5]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[6]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[7]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		}
		
		else//无效
		{
			p[0]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[1]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[2]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[3]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[4]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[5]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[6]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[7]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		}
	}
	
	else if(valve_leak==FAULT_A_LESS_LEAK)//A组备份发动机泄漏
	{
		if(n==1)//法兰温度
		{
			p[0]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[1]);//A2法兰温度
			p[1]=TGTHT510_tempercontrol_pt_to_mf61(TGTHT510_1553B_data_TGTHT100_Temper_A[3]);//A4法兰温度
			p[2]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[3]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[4]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[5]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[6]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[7]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		}
		
		else if(n==2)//氧阀温度
		{
			p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[27]>>4)&0xfffc;//A2氧阀温度
			p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_A[29]>>4)&0xfffc;//A4氧阀温度
			p[2]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[3]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[4]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[5]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[6]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[7]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		}
		
		else//无效
		{
			p[0]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[1]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[2]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[3]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[4]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[5]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[6]=TABLE_MF61_POS_70;//填充值，+70摄氏度
			p[7]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		}
	}
	
	else
	{
		p[0]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		p[1]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		p[2]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		p[3]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		p[4]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		p[5]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		p[6]=TABLE_MF61_POS_70;//填充值，+70摄氏度
		p[7]=TABLE_MF61_POS_70;//填充值，+70摄氏度
	}
	
}

/******************************************************************************************
**名称：推进故障检测模块--发动机泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_valve_leak_is_leak(uint16 (*p1)[8],uint16 (*p2)[8])
{
	uint16 i,n,j;
	
	for(i=0;i<=7;i++)
	{
		n=0;
		
		for(j=0;j<=3;j++)
		{
			if(((p1[j][i]>=TABLE_MF61_POS_04)&&(p2[j][i]>=TABLE_MF61_POS_04))&&\
			((p1[j][i]>=TABLE_MF61_NEG_10)||(p2[j][i]>=TABLE_MF61_NEG_10)))
			{
				n++;
			}
		}
		
		if(n>=3)
		{
			return TRUE;
		}
		
	}
	
	return FALSE;
}


/******************************************************************************************
**名称：推进故障检测模块--发动机泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_valve_leak(uint16 valve_leak)
{
	if(valve_leak==FAULT_B_MAIN_LEAK)//B组主份发动机泄漏
	{
		TGTHT510_faultdiagnosis_push_valve_leak_dealing(&TGTHT510_fault_push_B_main_valve_leak,valve_leak);
	}
	
	else if(valve_leak==FAULT_B_LESS_LEAK)//B组备份发动机泄漏
	{
		TGTHT510_faultdiagnosis_push_valve_leak_dealing(&TGTHT510_fault_push_B_less_valve_leak,valve_leak);
	}
	
	else if(valve_leak==FAULT_C_ALL_LEAK)//C组发动机泄漏
	{
		TGTHT510_faultdiagnosis_push_valve_leak_dealing(&TGTHT510_fault_push_C_all_valve_leak,valve_leak);
	}
	
	else if(valve_leak==FAULT_A_MAIN_LEAK)//A组主份发动机泄漏
	{
		TGTHT510_faultdiagnosis_push_valve_leak_dealing(&TGTHT510_fault_push_A_main_valve_leak,valve_leak);
	}
	
	else if(valve_leak==FAULT_A_LESS_LEAK)//A组备份发动机泄漏
	{
		TGTHT510_faultdiagnosis_push_valve_leak_dealing(&TGTHT510_fault_push_A_less_valve_leak,valve_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：推进故障检测模块--发动机泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_valve_leak_dealing(fault_valve_leak_TypeDef *p,uint16 valve_leak)
{
	switch(p->step)
	{
		case FAULT_STEP_START://开始
		{
			p->step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集温度值，第一次
		{
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,1,p->value_fa[0]);
			
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,2,p->value_va[0]);
			
			p->step=FAULT_STEP_NO2;
			
			break;
			
		}
		
		case FAULT_STEP_NO2://采集温度值，第二次
		{
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,1,p->value_fa[1]);
			
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,2,p->value_va[1]);
			
			p->step=FAULT_STEP_NO3;
			
			break;
			
		}
		
		case FAULT_STEP_NO3://采集温度值，第三次
		{
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,1,p->value_fa[2]);
			
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,2,p->value_va[2]);
			
			p->step=FAULT_STEP_NO4;
			
			break;
			
		}
		
		case FAULT_STEP_NO4://采集温度值，第四次
		{
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,1,p->value_fa[3]);
			
			TGTHT510_faultdiagnosis_push_valve_leak_get_temperature(valve_leak,2,p->value_va[3]);
			
			p->step=FAULT_STEP_NO5;
			
			break;
			
		}
		
		case FAULT_STEP_NO5://处理
		{
			if(TGTHT510_faultdiagnosis_push_valve_leak_is_leak(p->value_fa,p->value_va)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_valve_leak_typedef(p);
			}
			
			else
			{
				p->step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
			
		}
		
		case FAULT_STEP_END:
		{
			p->step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}

	}

}

/******************************************************************************************
**名称：推进故障检测模块--获取贮箱位移传感器数据
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_push_htt_get(uint16 tank_leak,uint16 n)
{
	uint16 result;
	
	result = 0;
	
	if(tank_leak==FAULT_O_TANK1)//氧1贮箱泄漏
	{
		if(n==1)
		{
			result=TGTHT510_1553B_data_TGTHT100[61];//htt1
		}
		
		else if(n==2)
		{
			result=TGTHT510_1553B_data_TGTHT100[62];//htt2
		}
		
		else if(n==3)
		{
			result=TGTHT510_1553B_data_TGTHT100[63];//htt3
		}
		
		else
		{
			asm("nop;");
		}
	
	}
	
	else if(tank_leak==FAULT_O_TANK2)//氧2贮箱泄漏
	{
		if(n==1)
		{
			result=TGTHT510_1553B_data_TGTHT100[64];//htt4
		}
		
		else if(n==2)
		{
			result=TGTHT510_1553B_data_TGTHT100[65];//htt5
		}
		
		else if(n==3)
		{
			result=TGTHT510_1553B_data_TGTHT100[66];//htt6
		}
		
		else
		{
			asm("nop;");
		}
	}
	
	else if(tank_leak==FAULT_O_TANK3)//氧3贮箱泄漏
	{
		if(n==1)
		{
			result=TGTHT510_1553B_data_TGTHT100[67];//htt7
		}
		
		else if(n==2)
		{
			result=TGTHT510_1553B_data_TGTHT100[68];//htt8
		}
		
		else if(n==3)
		{
			result=TGTHT510_1553B_data_TGTHT100[69];//htt9
		}
		
		else
		{
			asm("nop;");
		}
	}
	
	else if(tank_leak==FAULT_F_TANK1)//燃1贮箱泄漏
	{
		if(n==1)
		{
			result=TGTHT510_1553B_data_TGTHT100[70];//htt10
		}
		
		else if(n==2)
		{
			result=TGTHT510_1553B_data_TGTHT100[71];//htt11
		}
		
		else if(n==3)
		{
			result=TGTHT510_1553B_data_TGTHT100[72];//htt12
		}
		
		else
		{
			asm("nop;");
		}
	}
	
	else if(tank_leak==FAULT_F_TANK2)//燃2贮箱泄漏
	{
		if(n==1)
		{
			result=TGTHT510_1553B_data_TGTHT100[73];//htt13
		}
		
		else if(n==2)
		{
			result=TGTHT510_1553B_data_TGTHT100[74];//htt14
		}
		
		else if(n==3)
		{
			result=TGTHT510_1553B_data_TGTHT100[75];//htt15
		}
		
		else
		{
			asm("nop;");
		}
	}
	
	else if(tank_leak==FAULT_F_TANK3)//燃3贮箱泄漏
	{
		if(n==1)
		{
			result=TGTHT510_1553B_data_TGTHT100[76];//htt16
		}
		
		else if(n==2)
		{
			result=TGTHT510_1553B_data_TGTHT100[77];//htt17
		}
		
		else if(n==3)
		{
			result=TGTHT510_1553B_data_TGTHT100[78];//htt18
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
	
	return result;

}

/******************************************************************************************
**名称：推进故障检测模块--判断贮箱是否泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_push_tank_leak_is_leak(uint16 (*p)[3])
{
	uint16 i,j;
	uint16 n,k;
	n=0;
	k=0;
	
	for(j=0;j<=2;j++)
	{
		for(i=0;i<=2;i++)
		{
			if((p[i+1][j]>p[i][j])&&((p[i+1][j]-p[i][j])>=FAULT_CONST_HTT_ONE))
			{
				k++;
			}
			
		}
		
		if(k>=2)
		{
			n++;
		}
		
		k=0;
		
	}
	
	if(n>=2)
	{
		return TRUE;//故障发生
	}
	
	else
	{
		return FALSE;//故障未发生
	}
	
}

/******************************************************************************************
**名称：推进故障检测模块--贮箱泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_tank_leak(uint16 tank_leak)
{
	if(tank_leak==FAULT_O_TANK1)//氧1贮箱泄漏
	{
		TGTHT510_faultdiagnosis_push_tank_leak_dealing(&TGTHT510_fault_push_o_tank1_leak,tank_leak);
	}
	
	else if(tank_leak==FAULT_O_TANK2)//氧2贮箱泄漏
	{
		TGTHT510_faultdiagnosis_push_tank_leak_dealing(&TGTHT510_fault_push_o_tank2_leak,tank_leak);
	}
	
	else if(tank_leak==FAULT_O_TANK3)//氧3贮箱泄漏
	{
		TGTHT510_faultdiagnosis_push_tank_leak_dealing(&TGTHT510_fault_push_o_tank3_leak,tank_leak);
	}
	
	else if(tank_leak==FAULT_F_TANK1)//燃1贮箱泄漏
	{
		TGTHT510_faultdiagnosis_push_tank_leak_dealing(&TGTHT510_fault_push_f_tank1_leak,tank_leak);
	}
	
	else if(tank_leak==FAULT_F_TANK2)//燃2贮箱泄漏
	{
		TGTHT510_faultdiagnosis_push_tank_leak_dealing(&TGTHT510_fault_push_f_tank2_leak,tank_leak);
	}
	
	else if(tank_leak==FAULT_F_TANK3)//燃3贮箱泄漏
	{
		TGTHT510_faultdiagnosis_push_tank_leak_dealing(&TGTHT510_fault_push_f_tank3_leak,tank_leak);
	}
	
	else
	{
		asm("nop;");
	}
}

/******************************************************************************************
**名称：推进故障检测模块--贮箱泄漏--判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_tank_leak_dealing(fault_TypeDef *p,uint16 tank_leak)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集位移传感器htt，第一次
		{
			p->fault_field1.valve_htt[0][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[0][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[0][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://定时15s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://判断15s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://采集位移传感器htt，第二次
		{
			p->fault_field1.valve_htt[1][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[1][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[1][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://定时15s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://判断15s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://采集位移传感器htt，第三次
		{
			p->fault_field1.valve_htt[2][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[2][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[2][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			p->fault_field1.step=FAULT_STEP_NO8;
			
			break;
		}
		
		case FAULT_STEP_NO8://定时15s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://判断15s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://采集位移传感器htt，第四次
		{
			p->fault_field1.valve_htt[3][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[3][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[3][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			p->fault_field1.step=FAULT_STEP_NO11;
			
			break;
		}
		
		case FAULT_STEP_NO11://定时15s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://判断15s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://采集位移传感器htt，第五次
		{
			p->fault_field1.valve_htt[4][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[4][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[4][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			p->fault_field1.step=FAULT_STEP_NO14;
			
			break;
		}
		
		case FAULT_STEP_NO14://处理
		{
			if(TGTHT510_faultdiagnosis_push_tank_leak_is_leak(p->fault_field1.valve_htt)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
		
		
	}

}

/******************************************************************************************
**名称：补加故障检测模块--电机驱动器故障
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_TGTHT530(void)
{
	TGTHT510_faultdiagnosis_supply_TGTHT530_dealing(&TGTHT510_fault_supply_TGTHT530);
}

/******************************************************************************************
**名称：补加故障检测模块--电机驱动器故障
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_faultdiagnosis_supply_TGTHT530_dealing(fault_TypeDef *p)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://读取电机驱动器故障状态字，第一次
		{
			p->fault_field1.value[0]=TGTHT510_1553B_data_TGTHT530[7];
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2://读取电机驱动器故障状态字，第二次
		{
			p->fault_field1.value[1]=TGTHT510_1553B_data_TGTHT530[7];
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			//暂定电机驱动器无故障为0x5555，后续更改！！！！！！
			if((p->fault_field1.value[0]!=0x5555)&&(p->fault_field1.value[1]!=0x5555))
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}	
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
	
	}
}


/******************************************************************************************
**名称：补加故障检测模块--液冷模块故障
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_cooler(uint16 fault_cooler)
{
	if(fault_cooler==FAULT_COOLER_ZZ)//故障检测--主份液冷主泵
	{
		TGTHT510_faultdiagnosis_supply_cooler_dealing(&TGTHT510_fault_supply_cooler_zz,fault_cooler);
	}
	
	else if(fault_cooler==FAULT_COOLER_ZB)//故障检测--主份液冷备泵
	{
		TGTHT510_faultdiagnosis_supply_cooler_dealing(&TGTHT510_fault_supply_cooler_zb,fault_cooler);
	}
	
	else if(fault_cooler==FAULT_COOLER_BZ)//故障检测--备份液冷主泵
	{
		TGTHT510_faultdiagnosis_supply_cooler_dealing(&TGTHT510_fault_supply_cooler_bz,fault_cooler);
	}
	
	else if(fault_cooler==FAULT_COOLER_BB)//故障检测--备份液冷备泵
	{
		TGTHT510_faultdiagnosis_supply_cooler_dealing(&TGTHT510_fault_supply_cooler_bb,fault_cooler);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--液冷模块故障
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_cooler_get_value(uint16 fault_cooler)
{
	if(fault_cooler==FAULT_COOLER_ZZ)//故障检测--主份液冷主泵
	{
		return TGTHT510_1553B_data_TGTHT100[79];
	}
	
	else if(fault_cooler==FAULT_COOLER_ZB)//故障检测--主份液冷备泵
	{
		return TGTHT510_1553B_data_TGTHT100[80];
	}
	
	else if(fault_cooler==FAULT_COOLER_BZ)//故障检测--备份液冷主泵
	{
		return TGTHT510_1553B_data_TGTHT100[81];
	}
	
	else if(fault_cooler==FAULT_COOLER_BB)//故障检测--备份液冷备泵
	{
		return TGTHT510_1553B_data_TGTHT100[82];
	}
	
	else
	{
		return 0;
	}
}

/******************************************************************************************
**名称：补加故障检测模块--液冷模块故障
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_cooler_is_fault(uint16 *p)
{
	uint16 n;
	uint16 i;
	
	n=0;
	for(i=0;i<=3;i++)
	{
		if(p[i]<FAULT_CONST_COOLER)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
}

/******************************************************************************************
**名称：补加故障检测模块--液冷模块故障
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_cooler_dealing(fault_TypeDef *p,uint16 fault_cooler)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://读取泵转速，第一次
		{
			p->fault_field1.value[0]=TGTHT510_faultdiagnosis_supply_cooler_get_value(fault_cooler);
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2://读取泵转速，第二次
		{
			p->fault_field1.value[1]=TGTHT510_faultdiagnosis_supply_cooler_get_value(fault_cooler);
			p->fault_field1.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3://读取泵转速，第三次
		{
			p->fault_field1.value[2]=TGTHT510_faultdiagnosis_supply_cooler_get_value(fault_cooler);
			p->fault_field1.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4://读取泵转速，第四次
		{
			p->fault_field1.value[3]=TGTHT510_faultdiagnosis_supply_cooler_get_value(fault_cooler);
			p->fault_field1.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5://判断
		{
			if(TGTHT510_faultdiagnosis_supply_cooler_is_fault(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}	
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
}

/******************************************************************************************
**名称：补加故障检测模块--液冷模块泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_leak_cooler(uint16 leak_cooler)
{
	if(leak_cooler==FAULT_COOLER_Z)
	{
		TGTHT510_faultdiagnosis_supply_leak_cooler_dealing(&TGTHT510_fault_supply_leak_cooler_z,\
		leak_cooler);
	}
	
	else if(leak_cooler==FAULT_COOLER_B)
	{
		TGTHT510_faultdiagnosis_supply_leak_cooler_dealing(&TGTHT510_fault_supply_leak_cooler_b,\
		leak_cooler);
	}
	
	else
	{
		asm("nop;");
	}
}

/******************************************************************************************
**名称：补加故障检测模块--液冷模块泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_leak_cooler_is_leak(uint16 *p)
{
	uint16 n1,n2;
	uint16 i;
	
	n1=0;
	n2=0;
	
	for(i=0;i<=6;i=i+2)
	{
		if((uint16)(abs(p[i]-p[i+2]))>FAULT_CONST_COOLER_LEAK)//PTb11或者PTb12
		{
			n1++;
		}
	}
	
	for(i=1;i<=7;i=i+2)
	{
		if((uint16)(abs(p[i]-p[i+2]))>FAULT_CONST_COOLER_LEAK)//PTb13或者PTb14
		{
			n2++;
		}
	}
	
	if((n1>=3)||(n2>=3))
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}



/******************************************************************************************
**名称：补加故障检测模块--液冷模块泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_leak_cooler_dealing(fault_TypeDef *p,uint16 leak_cooler)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://读取传感器数据，第一次
		{
			if(leak_cooler==FAULT_COOLER_Z)
			{
				p->fault_field1.value[0]=TGTHT510_1553B_data_TGTHT100[44];//PTb11
				p->fault_field1.value[1]=TGTHT510_1553B_data_TGTHT100[46];//PTb13
			}
			
			else if(leak_cooler==FAULT_COOLER_B)
			{
				p->fault_field1.value[0]=TGTHT510_1553B_data_TGTHT100[45];//PTb12
				p->fault_field1.value[1]=TGTHT510_1553B_data_TGTHT100[47];//PTb14
			}
			
			else
			{
				p->fault_field1.value[0]=0;
				p->fault_field1.value[1]=0;
			}
			
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2://定时15s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://判断15s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://读取传感器数据，第二次
		{
			if(leak_cooler==FAULT_COOLER_Z)
			{
				p->fault_field1.value[2]=TGTHT510_1553B_data_TGTHT100[44];//PTb11
				p->fault_field1.value[3]=TGTHT510_1553B_data_TGTHT100[46];//PTb13
			}
			
			else if(leak_cooler==FAULT_COOLER_B)
			{
				p->fault_field1.value[2]=TGTHT510_1553B_data_TGTHT100[45];//PTb12
				p->fault_field1.value[3]=TGTHT510_1553B_data_TGTHT100[47];//PTb14
			}
			
			else
			{
				p->fault_field1.value[2]=0;
				p->fault_field1.value[3]=0;
			}
			
			p->fault_field1.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5://定时15s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://判断15s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://读取传感器数据，第三次
		{
			if(leak_cooler==FAULT_COOLER_Z)
			{
				p->fault_field1.value[4]=TGTHT510_1553B_data_TGTHT100[44];//PTb11
				p->fault_field1.value[5]=TGTHT510_1553B_data_TGTHT100[46];//PTb13
			}
			
			else if(leak_cooler==FAULT_COOLER_B)
			{
				p->fault_field1.value[4]=TGTHT510_1553B_data_TGTHT100[45];//PTb12
				p->fault_field1.value[5]=TGTHT510_1553B_data_TGTHT100[47];//PTb14
			}
			
			else
			{
				p->fault_field1.value[4]=0;
				p->fault_field1.value[5]=0;
			}
			
			p->fault_field1.step=FAULT_STEP_NO8;
			break;
		}
		
		case FAULT_STEP_NO8://定时15s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://判断15s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://读取传感器数据，第四次
		{
			if(leak_cooler==FAULT_COOLER_Z)
			{
				p->fault_field1.value[6]=TGTHT510_1553B_data_TGTHT100[44];//PTb11
				p->fault_field1.value[7]=TGTHT510_1553B_data_TGTHT100[46];//PTb13
			}
			
			else if(leak_cooler==FAULT_COOLER_B)
			{
				p->fault_field1.value[6]=TGTHT510_1553B_data_TGTHT100[45];//PTb12
				p->fault_field1.value[7]=TGTHT510_1553B_data_TGTHT100[47];//PTb14
			}
			
			else
			{
				p->fault_field1.value[6]=0;
				p->fault_field1.value[7]=0;
			}
			
			p->fault_field1.step=FAULT_STEP_NO11;
			break;
		}
		
		case FAULT_STEP_NO11://定时15s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://判断15s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_15SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://读取传感器数据，第五次
		{
			if(leak_cooler==FAULT_COOLER_Z)
			{
				p->fault_field1.value[8]=TGTHT510_1553B_data_TGTHT100[44];//PTb11
				p->fault_field1.value[9]=TGTHT510_1553B_data_TGTHT100[46];//PTb13
			}
			
			else if(leak_cooler==FAULT_COOLER_B)
			{
				p->fault_field1.value[8]=TGTHT510_1553B_data_TGTHT100[45];//PTb12
				p->fault_field1.value[9]=TGTHT510_1553B_data_TGTHT100[47];//PTb14
			}
			
			else
			{
				p->fault_field1.value[8]=0;
				p->fault_field1.value[9]=0;
			}
			
			p->fault_field1.step=FAULT_STEP_NO14;
			break;
		}
		
		case FAULT_STEP_NO14:
		{
			if(TGTHT510_faultdiagnosis_supply_leak_cooler_is_leak(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
	}
}


/******************************************************************************************
**名称：补加故障检测模块--压气机超压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_over_compressor(uint16 over_kind)
{
	if(over_kind==FAULT_COMPRESSOR_A_IN_OVER)//压气机A入口超压
	{
		TGTHT510_faultdiagnosis_supply_over_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_A_in_over,over_kind);
	}
	
	else if(over_kind==FAULT_COMPRESSOR_B_IN_OVER)//压气机B入口超压
	{
		TGTHT510_faultdiagnosis_supply_over_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_B_in_over,over_kind);
	}
	
	else if(over_kind==FAULT_COMPRESSOR_C_IN_OVER)//压气机C入口超压
	{
		TGTHT510_faultdiagnosis_supply_over_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_C_in_over,over_kind);
	}
	
	else if(over_kind==FAULT_COMPRESSOR_A_MOTOR_OVER)//压气机A电机腔超压
	{
		TGTHT510_faultdiagnosis_supply_over_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_A_motor_over,over_kind);
	}
	
	else if(over_kind==FAULT_COMPRESSOR_B_MOTOR_OVER)//压气机B电机腔超压
	{
		TGTHT510_faultdiagnosis_supply_over_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_B_motor_over,over_kind);
	}
	
	else if(over_kind==FAULT_COMPRESSOR_C_MOTOR_OVER)//压气机C电机腔超压
	{
		TGTHT510_faultdiagnosis_supply_over_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_C_motor_over,over_kind);
	}
	
	else
	{
		asm("nop;");
	}

}

/******************************************************************************************
**名称：补加故障检测模块--压气机超压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(uint16 over_kind,uint16 num)
{
	if(over_kind==FAULT_COMPRESSOR_A_IN_OVER)//压气机A入口超压
	{
		if(num==1)
		{
			return TGTHT510_1553B_data_TGTHT100[36];//PTb3
		}
		
		else if(num==2)
		{
			return TGTHT510_1553B_data_TGTHT100[86];//PTb29
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(over_kind==FAULT_COMPRESSOR_B_IN_OVER)//压气机B入口超压
	{
		if(num==1)
		{
			return TGTHT510_1553B_data_TGTHT100[37];//PTb4
		}
		
		else if(num==2)
		{
			return TGTHT510_1553B_data_TGTHT100[85];//PTb28
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(over_kind==FAULT_COMPRESSOR_C_IN_OVER)//压气机C入口超压
	{
		if(num==1)
		{
			return TGTHT510_1553B_data_TGTHT100[57];//PTb24
		}
		
		else if(num==2)
		{
			return TGTHT510_1553B_data_TGTHT100[56];//PTb23
		}
		
		else
		{
			return 0;
		}
	}
	
	else if(over_kind==FAULT_COMPRESSOR_A_MOTOR_OVER)//压气机A电机腔超压
	{
		return TGTHT510_1553B_data_TGTHT100[86];//PTb29
	}
	
	else if(over_kind==FAULT_COMPRESSOR_B_MOTOR_OVER)//压气机B电机腔超压
	{
		return TGTHT510_1553B_data_TGTHT100[85];//PTb28
	}
	
	else if(over_kind==FAULT_COMPRESSOR_C_MOTOR_OVER)//压气机C电机腔超压
	{
		return TGTHT510_1553B_data_TGTHT100[56];//PTb23
	}
	
	else
	{
		return 0;
	}

}

/******************************************************************************************
**名称：补加故障检测模块--压气机超压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_over_compressor_is_over(uint16 *p)
{
	uint16 i;
	uint16 n;
	n=0;
	
	for(i=0;i<=6;i=i+2)
	{
		if(p[i]>FAULT_CONST_COMPRESSOR_OVER)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	n=0;
	
	for(i=1;i<=7;i=i+2)
	{
		if(p[i]>FAULT_CONST_COMPRESSOR_OVER)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	return FALSE;
}

/******************************************************************************************
**名称：补加故障检测模块--压气机超压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_over_compressor_dealing(fault_TypeDef *p,uint16 over_kind)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力值，第一次
		{
			p->fault_field1.value[0]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,1);
			
			p->fault_field1.value[1]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,2);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2://采集压力值，第二次
		{
			p->fault_field1.value[2]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,1);
			
			p->fault_field1.value[3]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,2);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3://采集压力值，第三次
		{
			p->fault_field1.value[4]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,1);
			
			p->fault_field1.value[5]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,2);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4://采集压力值，第四次
		{
			p->fault_field1.value[6]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,1);
			
			p->fault_field1.value[7]=\
			TGTHT510_faultdiagnosis_supply_over_compressor_get_pressure(over_kind,2);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(TGTHT510_faultdiagnosis_supply_over_compressor_is_over(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
	}
}

/******************************************************************************************
**名称：补加故障检测模块--压气机超温
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_hot_compressor(uint16 hot_kind)
{
	if(hot_kind==FAULT_COMPRESSOR_A_HOT)
	{
		TGTHT510_faultdiagnosis_supply_hot_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_A_hot,hot_kind);
	}

	else if(hot_kind==FAULT_COMPRESSOR_B_HOT)
	{
		TGTHT510_faultdiagnosis_supply_hot_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_B_hot,hot_kind);
	}	
	
	else if(hot_kind==FAULT_COMPRESSOR_C_HOT)
	{
		TGTHT510_faultdiagnosis_supply_hot_compressor_dealing(\
		&TGTHT510_fault_supply_compressor_C_hot,hot_kind);
	}	
	
	else
	{
		asm("nop;");
	}
}

/******************************************************************************************
**名称：补加故障检测模块--压气机超温
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_hot_compressor_get_max(uint16 hot_kind)
{
	uint16 temperature[6];
	uint16 i,j;
	uint16 max;
	
	if(hot_kind==FAULT_COMPRESSOR_A_HOT)
	{
		temperature[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[44]&0xff00)>>4;//压气机A温度1
		temperature[1]=(TGTHT510_1553B_data_TGTHT100_Temper_B[44]&0x00ff)<<4;//压气机A温度2
		temperature[2]=(TGTHT510_1553B_data_TGTHT100_Temper_B[45]&0xff00)>>4;//压气机A温度3
		temperature[3]=(TGTHT510_1553B_data_TGTHT100_Temper_B[45]&0x00ff)<<4;//压气机A温度4
		temperature[4]=(TGTHT510_1553B_data_TGTHT100_Temper_B[46]&0xff00)>>4;//压气机A温度5
		temperature[5]=(TGTHT510_1553B_data_TGTHT100_Temper_B[46]&0x00ff)<<4;//压气机A温度6
	}

	else if(hot_kind==FAULT_COMPRESSOR_B_HOT)
	{
		temperature[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[47]&0xff00)>>4;//压气机B温度1
		temperature[1]=(TGTHT510_1553B_data_TGTHT100_Temper_B[47]&0x00ff)<<4;//压气机B温度2
		temperature[2]=(TGTHT510_1553B_data_TGTHT100_Temper_B[48]&0xff00)>>4;//压气机B温度3
		temperature[3]=(TGTHT510_1553B_data_TGTHT100_Temper_B[48]&0x00ff)<<4;//压气机B温度4
		temperature[4]=(TGTHT510_1553B_data_TGTHT100_Temper_B[49]&0xff00)>>4;//压气机B温度5
		temperature[5]=(TGTHT510_1553B_data_TGTHT100_Temper_B[49]&0x00ff)<<4;//压气机B温度6
	}	
	
	else if(hot_kind==FAULT_COMPRESSOR_C_HOT)
	{
		temperature[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[50]&0xff00)>>4;//压气机C温度1
		temperature[1]=(TGTHT510_1553B_data_TGTHT100_Temper_B[50]&0x00ff)<<4;//压气机C温度2
		temperature[2]=(TGTHT510_1553B_data_TGTHT100_Temper_B[51]&0xff00)>>4;//压气机C温度3
		temperature[3]=(TGTHT510_1553B_data_TGTHT100_Temper_B[51]&0x00ff)<<4;//压气机C温度4
		temperature[4]=(TGTHT510_1553B_data_TGTHT100_Temper_B[52]&0xff00)>>4;//压气机C温度5
		temperature[5]=(TGTHT510_1553B_data_TGTHT100_Temper_B[52]&0x00ff)<<4;//压气机C温度6
	}	
	
	else
	{
		temperature[0]=0;
		temperature[1]=0;
		temperature[2]=0;
		temperature[3]=0;
		temperature[4]=0;
		temperature[5]=0;
	}
	
	max=temperature[0];
	
	for(i=1;i<=5;i++)
	{
		if(temperature[i]>max)
		{
			max=temperature[i];
		}
	}
	
	return max;	
}

/******************************************************************************************
**名称：补加故障检测模块--压气机超温
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_hot_compressor_is_hot(uint16 *p)
{
	uint16 i;
	
	for(i=0;i<=4;i++)
	{
		if(p[i]<FAULT_CONST_COMPRESSOR_HOT)
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

/******************************************************************************************
**名称：补加故障检测模块--压气机超温
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_hot_compressor_dealing(fault_TypeDef *p,uint16 hot_kind)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压气机6个温度值的最大值，第一次
		{
			p->fault_field1.value[0]=\
			TGTHT510_faultdiagnosis_supply_hot_compressor_get_max(hot_kind);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			p->fault_field1.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3://采集压气机6个温度值的最大值，第二次
		{
			p->fault_field1.value[1]=\
			TGTHT510_faultdiagnosis_supply_hot_compressor_get_max(hot_kind);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			p->fault_field1.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5://采集压气机6个温度值的最大值，第三次
		{
			p->fault_field1.value[2]=\
			TGTHT510_faultdiagnosis_supply_hot_compressor_get_max(hot_kind);
			
			p->fault_field1.step=FAULT_STEP_NO6;
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			p->fault_field1.step=FAULT_STEP_NO7;
			break;
		}
		
		case FAULT_STEP_NO7://采集压气机6个温度值的最大值，第四次
		{
			p->fault_field1.value[3]=\
			TGTHT510_faultdiagnosis_supply_hot_compressor_get_max(hot_kind);
			
			p->fault_field1.step=FAULT_STEP_NO8;
			break;
		}
		
		case FAULT_STEP_NO8:
		{
			p->fault_field1.step=FAULT_STEP_NO9;
			break;
		}
		
		case FAULT_STEP_NO9://采集压气机6个温度值的最大值，第五次
		{
			p->fault_field1.value[4]=\
			TGTHT510_faultdiagnosis_supply_hot_compressor_get_max(hot_kind);
			
			p->fault_field1.step=FAULT_STEP_NO10;
			break;
		}
		
		case FAULT_STEP_NO10://判断故障是否成立
		{
			if(TGTHT510_faultdiagnosis_supply_hot_compressor_is_hot(p->fault_field1.value)\
			==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
	}
}

/******************************************************************************************
**名称：补加故障检测模块--补加贮箱超压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_tank_overpressure(uint16 tank_overpressure)
{
	if(tank_overpressure==FAULT_O_TANK1)//故障检测--氧1贮箱
	{
		TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(\
		&TGTHT510_fault_supply_o_tank1_overpressure,tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_O_TANK2)//故障检测--氧2贮箱
	{
		TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(\
		&TGTHT510_fault_supply_o_tank2_overpressure,tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_O_TANK3)//故障检测--氧3贮箱
	{
		TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(\
		&TGTHT510_fault_supply_o_tank3_overpressure,tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_F_TANK1)//故障检测--燃1贮箱
	{
		TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(\
		&TGTHT510_fault_supply_f_tank1_overpressure,tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_F_TANK2)//故障检测--燃2贮箱
	{
		TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(\
		&TGTHT510_fault_supply_f_tank2_overpressure,tank_overpressure);
	}
	
	else if(tank_overpressure==FAULT_F_TANK3)//故障检测--燃3贮箱
	{
		TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(\
		&TGTHT510_fault_supply_f_tank3_overpressure,tank_overpressure);
	}
	
	else
	{
		asm("nop;");
	}
	
}


/******************************************************************************************
**名称：补加故障检测模块--补加贮箱超压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_tank_overpressure_get(uint16 *p,uint16 tank_overpressure)
{
	if(tank_overpressure==FAULT_O_TANK1)//故障检测--氧1贮箱
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[12];//PTt13
		p[1]=TGTHT510_1553B_data_TGTHT100[18];//PTt19
		p[2]=TGTHT510_1553B_data_TGTHT100[34];//PTb1
	}
	
	else if(tank_overpressure==FAULT_O_TANK2)//故障检测--氧2贮箱
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[14];//PTt15
		p[1]=TGTHT510_1553B_data_TGTHT100[20];//PTt21
		p[2]=TGTHT510_1553B_data_TGTHT100[34];//PTb1
	}
	
	else if(tank_overpressure==FAULT_O_TANK3)//故障检测--氧3贮箱
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[16];//PTt17
		p[1]=TGTHT510_1553B_data_TGTHT100[22];//PTt23
		p[2]=TGTHT510_1553B_data_TGTHT100[34];//PTb1
	}
	
	else if(tank_overpressure==FAULT_F_TANK1)//故障检测--燃1贮箱
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[13];//PTt14
		p[1]=TGTHT510_1553B_data_TGTHT100[19];//PTt20
		p[2]=TGTHT510_1553B_data_TGTHT100[35];//PTb2
	}
	
	else if(tank_overpressure==FAULT_F_TANK2)//故障检测--燃2贮箱
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[15];//PTt16
		p[1]=TGTHT510_1553B_data_TGTHT100[21];//PTt22
		p[2]=TGTHT510_1553B_data_TGTHT100[35];//PTb2
	}
	
	else if(tank_overpressure==FAULT_F_TANK3)//故障检测--燃3贮箱
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[17];//PTt18
		p[1]=TGTHT510_1553B_data_TGTHT100[23];//PTt24
		p[2]=TGTHT510_1553B_data_TGTHT100[35];//PTb2
	}
	
	else
	{
		p[0]=0;
		p[1]=0;
		p[2]=0;
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--补加贮箱超压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：0 1 2 3 4 5 6 7 8 9 10 11
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_tank_overpressure_is_over(uint16 *p)
{
	uint16 n[3];
	uint16 m;
	uint16 i;
	
	n[0]=0;
	n[1]=0;
	n[2]=0;
	for(i=0;i<=9;i=i+3)
	{
		if(p[i]>FAULT_CONST_PRESSURE_OVER)
		{
			n[0]++;
		}
	}
	
	for(i=1;i<=10;i=i+3)
	{
		if(p[i]>FAULT_CONST_PRESSURE_OVER)
		{
			n[1]++;
		}
	}
	
	for(i=2;i<=11;i=i+3)
	{
		if(p[i]>FAULT_CONST_PRESSURE_OVER)
		{
			n[2]++;
		}
	}
	
	m=0;
	for(i=0;i<=2;i++)
	{
		if(n[i]>=3)
		{
			m++;
		}
	}
	
	if(m>=2)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--补加贮箱超压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_tank_overpressure_dealing(fault_TypeDef *p,uint16 tank_overpressure)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力值，第一次
		{
			TGTHT510_faultdiagnosis_supply_tank_overpressure_get(&p->fault_field1.value[0],\
			tank_overpressure);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2://采集压力值，第二次
		{
			TGTHT510_faultdiagnosis_supply_tank_overpressure_get(&p->fault_field1.value[3],\
			tank_overpressure);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3://采集压力值，第三次
		{
			TGTHT510_faultdiagnosis_supply_tank_overpressure_get(&p->fault_field1.value[6],\
			tank_overpressure);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4://采集压力值，第四次
		{
			TGTHT510_faultdiagnosis_supply_tank_overpressure_get(&p->fault_field1.value[9],\
			tank_overpressure);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5://判断故障是否发生
		{
			if(TGTHT510_faultdiagnosis_supply_tank_overpressure_is_over(p->fault_field1.value)\
			==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
}


/******************************************************************************************
**名称：补加故障检测模块--压气机膜片破裂
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_compressor_break(uint16 compressor_break)
{
	if(compressor_break==FAULT_COMPRESSOR_A_BREAK)//压气机A膜片破裂
	{
		TGTHT510_faultdiagnosis_supply_compressor_break_dealing(\
		&TGTHT510_fault_supply_compressor_A_break,compressor_break);
	}
	
	else if(compressor_break==FAULT_COMPRESSOR_B_BREAK)//压气机B膜片破裂
	{
		TGTHT510_faultdiagnosis_supply_compressor_break_dealing(\
		&TGTHT510_fault_supply_compressor_B_break,compressor_break);
	}
	
	else if(compressor_break==FAULT_COMPRESSOR_C_BREAK)//压气机C膜片破裂
	{
		TGTHT510_faultdiagnosis_supply_compressor_break_dealing(\
		&TGTHT510_fault_supply_compressor_C_break,compressor_break);
	}
	
	else
	{
		asm("nop;");
	}
}

/******************************************************************************************
**名称：补加故障检测模块--压气机膜片破裂
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_compressor_break_get_pressure(uint16 *p,uint16 compressor_break)
{
	if(compressor_break==FAULT_COMPRESSOR_A_BREAK)//压气机A膜片破裂
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[38];//PTb5
		p[1]=TGTHT510_1553B_data_TGTHT100[40];//PTb7
	}
	
	else if(compressor_break==FAULT_COMPRESSOR_B_BREAK)//压气机B膜片破裂
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[39];//PTb6
		p[1]=TGTHT510_1553B_data_TGTHT100[41];//PTb8
	}
	
	else if(compressor_break==FAULT_COMPRESSOR_C_BREAK)//压气机C膜片破裂
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[58];//PTb5
		p[1]=TGTHT510_1553B_data_TGTHT100[59];//PTb7
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--压气机膜片破裂
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_compressor_break_is_break(uint16 *p)
{
	uint16 i;
	uint16 n;
	
	n=0;
	for(i=0;i<=6;i=i+2)
	{
		if(p[i]>FAULT_CONST_COMPRESSOR_BREAK)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	n=0;
	for(i=1;i<=7;i=i+2)
	{
		if(p[i]>FAULT_CONST_COMPRESSOR_BREAK)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	return FALSE;
}


/******************************************************************************************
**名称：补加故障检测模块--压气机膜片破裂
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_compressor_break_dealing(fault_TypeDef *p,uint16 compressor_break)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力值，第一次
		{
			TGTHT510_faultdiagnosis_supply_compressor_break_get_pressure(&p->fault_field1.value[0],\
			compressor_break);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2://采集压力值，第二次
		{
			TGTHT510_faultdiagnosis_supply_compressor_break_get_pressure(&p->fault_field1.value[2],\
			compressor_break);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3://采集压力值，第三次
		{
			TGTHT510_faultdiagnosis_supply_compressor_break_get_pressure(&p->fault_field1.value[4],\
			compressor_break);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4://采集压力值，第四次
		{
			TGTHT510_faultdiagnosis_supply_compressor_break_get_pressure(&p->fault_field1.value[6],\
			compressor_break);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(TGTHT510_faultdiagnosis_supply_compressor_break_is_break(p->fault_field1.value)\
			==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
	}

}

/******************************************************************************************
**名称：补加故障检测模块--气瓶泄漏--大漏判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_gas_leak_big(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//氧气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(&TGTHT510_fault_supply_o_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//氧气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(&TGTHT510_fault_supply_o_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//氧气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(&TGTHT510_fault_supply_o_gas3_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//燃气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(&TGTHT510_fault_supply_f_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//燃气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(&TGTHT510_fault_supply_f_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS3)//燃气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(&TGTHT510_fault_supply_f_gas3_leak,gas_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--气瓶泄漏--大漏判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_gas_leak_big_is_leak(uint16 *p)
{
	uint16 i;
	uint16 n;
	n=0;
	
	for(i=0;i<=3;i++)
	{
		if(p[i]>=p[i+1])
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return FALSE;
	}
	
	else
	{
		return TRUE;
	}
}


/******************************************************************************************
**名称：补加故障检测模块--气瓶泄漏--大漏判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_gas_leak_big_dealing(fault_TypeDef *p,uint16 gas_leak)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力，第一次
		{
			p->fault_field1.value[0]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://定时30s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://判断30s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://采集压力，第二次
		{
			p->fault_field1.value[1]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://定时30s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://判断30s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://采集压力，第三次
		{
			p->fault_field1.value[2]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO8;
			
			break;
		}
		
		case FAULT_STEP_NO8://定时30s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://判断30s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://采集压力，第四次
		{
			p->fault_field1.value[3]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO11;
			
			break;
		}
		
		case FAULT_STEP_NO11://定时30s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://判断30s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://采集压力，第五次
		{
			p->fault_field1.value[4]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field1.step=FAULT_STEP_NO14;
			
			break;
		}
		
		case FAULT_STEP_NO14://处理
		{
			if(TGTHT510_faultdiagnosis_push_gas_leak_four_of_three(p->fault_field1.value,FAULT_CONST_PRESSURE_0E1)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}	
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--气瓶泄漏--小漏判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_gas_leak_small(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//氧气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(&TGTHT510_fault_supply_o_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//氧气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(&TGTHT510_fault_supply_o_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//氧气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(&TGTHT510_fault_supply_o_gas3_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//燃气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(&TGTHT510_fault_supply_f_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//燃气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(&TGTHT510_fault_supply_f_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS3)//燃气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(&TGTHT510_fault_supply_f_gas3_leak,gas_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--气瓶泄漏--小漏判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_gas_leak_small_dealing(fault_TypeDef *p,uint16 gas_leak)
{
	switch(p->fault_field2.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field2.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力，第一次
		{
			p->fault_field2.value[0]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://定时20min开始
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://判断20min定时是否到
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_20MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://采集压力，第二次
		{
			p->fault_field2.value[1]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://定时20min开始
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://判断20min定时是否到
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_20MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://采集压力，第三次
		{
			p->fault_field2.value[2]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO8;
			
			break;
		}
		
		case FAULT_STEP_NO8://定时20min开始
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://判断20min定时是否到
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_20MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://采集压力，第四次
		{
			p->fault_field2.value[3]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO11;
			
			break;
		}
		
		case FAULT_STEP_NO11://定时20min开始
		{
			TGTHT510_faultdiagnosis_time2_start(p);
			
			p->fault_field2.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://判断20min定时是否到
		{
			if(TGTHT510_faultdiagnosis_time2_is_get(p,CONST_TIME_20MIN)==TRUE)
			{
				p->fault_field2.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://采集压力，第五次
		{
			p->fault_field2.value[4]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field2.step=FAULT_STEP_NO14;
			
			break;
		}
		
		case FAULT_STEP_NO14://处理
		{
			if(TGTHT510_faultdiagnosis_push_gas_leak_four_of_three(p->fault_field2.value,FAULT_CONST_PRESSURE_0E1)==\
			TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD2);
			}
			
			else
			{
				p->fault_field2.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field2.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--气瓶泄漏--极限值判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_gas_leak_min(uint16 gas_leak)
{
	if(gas_leak==FAULT_O_GAS1)//氧气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(&TGTHT510_fault_supply_o_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//氧气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(&TGTHT510_fault_supply_o_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//氧气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(&TGTHT510_fault_supply_o_gas3_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//燃气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(&TGTHT510_fault_supply_f_gas1_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//燃气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(&TGTHT510_fault_supply_f_gas2_leak,gas_leak);
	}
	
	else if(gas_leak==FAULT_F_GAS3)//燃气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(&TGTHT510_fault_supply_f_gas3_leak,gas_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：推进故障检测模块--气瓶泄漏--极限值判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_gas_leak_min_dealing(fault_TypeDef *p,uint16 gas_leak)
{
	switch(p->fault_field3.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field3.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力，第一次
		{
			p->fault_field3.value[0]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://采集压力，第二次
		{
			p->fault_field3.value[1]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://采集压力，第三次
		{
			p->fault_field3.value[2]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://采集压力，第四次
		{
			p->fault_field3.value[3]=TGTHT510_faultdiagnosis_push_gas_leak_get_pressure(gas_leak);
			
			p->fault_field3.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://处理
		{
			if(TGTHT510_faultdiagnosis_push_gas_leak_min_four_of_three(p->fault_field3.value,\
			FAULT_CONST_PRESSURE_MIN_GAS)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD3);
			}
			
			else
			{
				p->fault_field3.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field3.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--贮箱补加液路泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_tank_pipe_leak(uint16 tank_leak)
{
	if(tank_leak==FAULT_O_TANK1)//氧1贮箱补加液路泄漏
	{
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(\
		&TGTHT510_fault_supply_pipe_leak_o_tank1,tank_leak);
	}
	
	else if(tank_leak==FAULT_O_TANK2)//氧2贮箱补加液路泄漏
	{
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(\
		&TGTHT510_fault_supply_pipe_leak_o_tank2,tank_leak);
	}
	
	else if(tank_leak==FAULT_O_TANK3)//氧3贮箱补加液路泄漏
	{
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(\
		&TGTHT510_fault_supply_pipe_leak_o_tank3,tank_leak);
	}
	
	else if(tank_leak==FAULT_F_TANK1)//燃1贮箱补加液路泄漏
	{
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(\
		&TGTHT510_fault_supply_pipe_leak_f_tank1,tank_leak);
	}
	
	else if(tank_leak==FAULT_F_TANK2)//燃2贮箱补加液路泄漏
	{
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(\
		&TGTHT510_fault_supply_pipe_leak_f_tank2,tank_leak);
	}
	
	else if(tank_leak==FAULT_F_TANK3)//燃3贮箱补加液路泄漏
	{
		TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(\
		&TGTHT510_fault_supply_pipe_leak_f_tank3,tank_leak);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--贮箱补加液路泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_tank_pipe_leak_get_pressure(uint16 *p,uint16 tank_leak)
{
	if(tank_leak==FAULT_O_TANK1)//氧1贮箱补加液路泄漏
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[18];//PTt19
		p[1]=TGTHT510_1553B_data_TGTHT100[12];//PTt13
	}
	
	else if(tank_leak==FAULT_O_TANK2)//氧2贮箱补加液路泄漏
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[20];//PTt21
		p[1]=TGTHT510_1553B_data_TGTHT100[14];//PTt15
	}
	
	else if(tank_leak==FAULT_O_TANK3)//氧3贮箱补加液路泄漏
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[22];//PTt23
		p[1]=TGTHT510_1553B_data_TGTHT100[16];//PTt17
	}
	
	else if(tank_leak==FAULT_F_TANK1)//燃1贮箱补加液路泄漏
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[19];//PTt20
		p[1]=TGTHT510_1553B_data_TGTHT100[13];//PTt14
	}
	
	else if(tank_leak==FAULT_F_TANK2)//燃2贮箱补加液路泄漏
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[21];//PTt22
		p[1]=TGTHT510_1553B_data_TGTHT100[15];//PTt16
	}
	
	else if(tank_leak==FAULT_F_TANK3)//燃3贮箱补加液路泄漏
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[23];//PTt24
		p[1]=TGTHT510_1553B_data_TGTHT100[17];//PTt18
	}
	
	else
	{
		p[0]=0;
		p[1]=0;
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--贮箱补加液路泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_tank_pipe_leak_is_leak(uint16 (*p_htt)[3],uint16 *p_pressure)
{
	uint16 n,k,m;
	uint16 i,j;

	n=0;
	
	for(j=0;j<=2;j++)
	{
		k=0;
		for(i=0;i<=4;i++)
		{
			if(p_htt[i][j]<p_htt[i+1][j])
			{
				k++;
			}
			
		}
		
		if(k>=3)
		{
			n++;
		}
	}
	
	m=0;
	for(i=0;i<=8;i=i+2)
	{
		if(((uint16)(abs(p_pressure[i]-p_pressure[i+1])))<FAULT_CONST_PRESSURE_0E2)
		{
			m++;
		}
	}
	
	if((n>=2)&&(m>=3))
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--贮箱补加液路泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_tank_pipe_leak_dealing(fault_TypeDef *p,uint16 tank_leak)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力与位移，第一次
		{
			p->fault_field1.valve_htt[0][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[0][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[0][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			
			TGTHT510_faultdiagnosis_supply_tank_pipe_leak_get_pressure(&p->fault_field1.value[0],tank_leak);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://定时30s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://判断30s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO4;
			}
			
			break;
		}
		
		case FAULT_STEP_NO4://采集压力与位移，第二次
		{
			p->fault_field1.valve_htt[1][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[1][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[1][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			
			TGTHT510_faultdiagnosis_supply_tank_pipe_leak_get_pressure(&p->fault_field1.value[2],tank_leak);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5://定时30s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6://判断30s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7://采集压力与位移，第三次
		{
			p->fault_field1.valve_htt[2][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[2][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[2][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			
			TGTHT510_faultdiagnosis_supply_tank_pipe_leak_get_pressure(&p->fault_field1.value[4],tank_leak);
			
			p->fault_field1.step=FAULT_STEP_NO8;
			
			break;
		}
		
		case FAULT_STEP_NO8://定时30s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO9;
			
			break;
		}
		
		case FAULT_STEP_NO9://判断30s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO10;
			}
			
			break;
		}
		
		case FAULT_STEP_NO10://采集压力与位移，第四次
		{
			p->fault_field1.valve_htt[3][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[3][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[3][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			
			TGTHT510_faultdiagnosis_supply_tank_pipe_leak_get_pressure(&p->fault_field1.value[6],tank_leak);
			
			p->fault_field1.step=FAULT_STEP_NO11;
			
			break;
		}
		
		case FAULT_STEP_NO11://定时30s开始
		{
			TGTHT510_faultdiagnosis_time1_start(p);
			
			p->fault_field1.step=FAULT_STEP_NO12;
			
			break;
		}
		
		case FAULT_STEP_NO12://判断30s定时是否到
		{
			if(TGTHT510_faultdiagnosis_time1_is_get(p,CONST_TIME_30SEC)==TRUE)
			{
				p->fault_field1.step=FAULT_STEP_NO13;
			}
			
			break;
		}
		
		case FAULT_STEP_NO13://采集压力与位移，第五次
		{
			p->fault_field1.valve_htt[4][0]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,1);
			p->fault_field1.valve_htt[4][1]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,2);
			p->fault_field1.valve_htt[4][2]=TGTHT510_faultdiagnosis_push_htt_get(tank_leak,3);
			
			TGTHT510_faultdiagnosis_supply_tank_pipe_leak_get_pressure(&p->fault_field1.value[8],tank_leak);
			
			p->fault_field1.step=FAULT_STEP_NO14;
			
			break;
		}
		
		case FAULT_STEP_NO14:
		{
			if(TGTHT510_faultdiagnosis_supply_tank_pipe_leak_is_leak(p->fault_field1.valve_htt,\
			p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
	
	}
	
}


/******************************************************************************************
**名称：补加故障检测模块--氧吹除口温度异常
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_interface_temperature(uint16 interface)
{
	if(interface==FAULT_INTERFACE_O)
	{
		TGTHT510_faultdiagnosis_supply_interface_temperature_dealing(\
		&TGTHT510_fault_supply_interface_o_temperature,interface);
	}
	
	else if(interface==FAULT_INTERFACE_F)
	{
		TGTHT510_faultdiagnosis_supply_interface_temperature_dealing(\
		&TGTHT510_fault_supply_interface_f_temperature,interface);
	}
	
	else
	{
		asm("nop;");
	}
}

/******************************************************************************************
**名称：补加故障检测模块--氧吹除口温度异常
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_interface_temperature_get(uint16 *p,uint16 interface)
{
	if(interface==FAULT_INTERFACE_O)
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[26]&0xff00)>>4;//吹除口1温度
		p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_B[26]&0x00ff)<<4;//吹除模块1管路温度
		p[2]=(TGTHT510_1553B_data_TGTHT100_Temper_B[27]&0xff00)>>4;//吹除模块1阀门温度
	}
	
	else if(interface==FAULT_INTERFACE_F)
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[27]&0x00ff)<<4;//吹除口2温度
		p[1]=(TGTHT510_1553B_data_TGTHT100_Temper_B[28]&0xff00)>>4;//吹除模块2管路温度
		p[2]=(TGTHT510_1553B_data_TGTHT100_Temper_B[28]&0x00ff)<<4;//吹除模块2阀门温度
	}
	
	else
	{
		p[0]=0;
		p[1]=0;
		p[2]=0;
	}
}

/******************************************************************************************
**名称：补加故障检测模块--氧吹除口温度异常
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_interface_temperature_is_normal(uint16 *p)
{
	uint16 i,j;
	uint16 m,n;
	
	n=0;
	for(i=0;i<=9;i=i+3)
	{
		m=0;
		for(j=i;j<=i+2;j++)
		{
			if(p[j]>TABLE_MF61_NEG_20)
			{
				m++;
			}
		}
		
		if(m>=2)
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--氧吹除口温度异常
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_interface_temperature_dealing(fault_TypeDef *p,uint16 interface)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集温度值，第一次
		{
			TGTHT510_faultdiagnosis_supply_interface_temperature_get(&p->fault_field1.value[0],interface);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://采集温度值，第二次
		{
			TGTHT510_faultdiagnosis_supply_interface_temperature_get(&p->fault_field1.value[3],interface);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://采集温度值，第三次
		{
			TGTHT510_faultdiagnosis_supply_interface_temperature_get(&p->fault_field1.value[6],interface);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://采集温度值，第四次
		{
			TGTHT510_faultdiagnosis_supply_interface_temperature_get(&p->fault_field1.value[9],interface);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(TGTHT510_faultdiagnosis_supply_interface_temperature_is_normal(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}

	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--补加管路内漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_in_leak(uint16 leak_kind)
{
	if(leak_kind==FAULT_IN_LEAK_O_Z)//氧主补加管路内漏
	{
		TGTHT510_faultdiagnosis_supply_in_leak_dealing(&TGTHT510_fault_supply_in_leak_o_z,leak_kind);
	}
	
	else if(leak_kind==FAULT_IN_LEAK_O_B)//氧备补加管路内漏
	{
		TGTHT510_faultdiagnosis_supply_in_leak_dealing(&TGTHT510_fault_supply_in_leak_o_b,leak_kind);
	}
	
	else if(leak_kind==FAULT_IN_LEAK_F_Z)//燃主补加管路内漏
	{
		TGTHT510_faultdiagnosis_supply_in_leak_dealing(&TGTHT510_fault_supply_in_leak_f_z,leak_kind);
	}
	
	else if(leak_kind==FAULT_IN_LEAK_F_B)//燃备补加管路内漏
	{
		TGTHT510_faultdiagnosis_supply_in_leak_dealing(&TGTHT510_fault_supply_in_leak_f_b,leak_kind);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--补加管路内漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_faultdiagnosis_supply_in_leak_get_pressure(uint16 *p,uint16 leak_kind)
{
	if(leak_kind==FAULT_IN_LEAK_O_Z)//氧主补加管路内漏
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[52];//PTb19
		p[1]=TGTHT510_1553B_data_TGTHT100[54];//PTb21
	}
	
	else if(leak_kind==FAULT_IN_LEAK_O_B)//氧备补加管路内漏
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[48];//PTb15
		p[1]=TGTHT510_1553B_data_TGTHT100[50];//PTb17
	}
	
	else if(leak_kind==FAULT_IN_LEAK_F_Z)//燃主补加管路内漏
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[53];//PTb20
		p[1]=TGTHT510_1553B_data_TGTHT100[55];//PTb22
	}
	
	else if(leak_kind==FAULT_IN_LEAK_F_B)//燃备补加管路内漏
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[49];//PTb16
		p[1]=TGTHT510_1553B_data_TGTHT100[51];//PTb18
	}
	
	else
	{
		p[0]=0;
		p[1]=0;
	}
}

/******************************************************************************************
**名称：补加故障检测模块--补加管路内漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_in_leak_is_leak(uint16 *p)
{
	uint16 i;
	uint16 n;
	
	n=0;
	for(i=0;i<=6;i=i+2)
	{
		if((p[i]>=FAULT_CONST_PRESSURE_0E4)&&(p[i+1]>=FAULT_CONST_PRESSURE_0E4))
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--补加管路内漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_in_leak_dealing(fault_TypeDef *p,uint16 leak_kind)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力值，第一次
		{
			TGTHT510_faultdiagnosis_supply_in_leak_get_pressure(&p->fault_field1.value[0],leak_kind);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://采集压力值，第二次
		{
			TGTHT510_faultdiagnosis_supply_in_leak_get_pressure(&p->fault_field1.value[2],leak_kind);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://采集压力值，第三次
		{
			TGTHT510_faultdiagnosis_supply_in_leak_get_pressure(&p->fault_field1.value[4],leak_kind);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://采集压力值，第四次
		{
			TGTHT510_faultdiagnosis_supply_in_leak_get_pressure(&p->fault_field1.value[6],leak_kind);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(TGTHT510_faultdiagnosis_supply_in_leak_is_leak(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
	
}

/******************************************************************************************
**名称：补加故障检测模块--浮动断接器温度异常
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_temperature(uint16 temperature_kind)
{
	if(temperature_kind==FAULT_TEMPERATURE_FORE_F1)//前向燃1浮动断接器温度异常
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_fore_f1,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_FORE_F2)//前向燃2浮动断接器温度异常
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_fore_f2,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_FORE_O1)//前向氧1浮动断接器温度异常
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_fore_o1,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_FORE_O2)//前向氧2浮动断接器温度异常
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_fore_o2,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_F1)//后向燃1浮动断接器温度异常
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_back_f1,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_F2)//后向燃2浮动断接器温度异常
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_back_f2,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_O1)//后向氧1浮动断接器温度异常
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_back_o1,\
		temperature_kind);
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_O2)//后向氧2浮动断接器温度异常
	{
		TGTHT510_faultdiagnosis_supply_temperature_dealing(&TGTHT510_fault_supply_temperature_back_o2,\
		temperature_kind);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--浮动断接器温度异常
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_faultdiagnosis_supply_temperature_get(uint16 *p,uint16 temperature_kind)
{
	if(temperature_kind==FAULT_TEMPERATURE_FORE_F1)//前向燃1浮动断接器温度异常
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[48]&0xff00)>>4;//前向燃1浮动断接器温度
		p[1]=0;//VCTHT109，待修改！！！
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_FORE_F2)//前向燃2浮动断接器温度异常
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[50]&0xff00)>>4;//前向燃2浮动断接器温度
		p[1]=0;//VCTHT110，待修改！！！
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_FORE_O1)//前向氧1浮动断接器温度异常
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[52]&0xff00)>>4;//前向氧1浮动断接器温度
		p[1]=0;//VCTHT111，待修改！！！
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_FORE_O2)//前向氧2浮动断接器温度异常
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[54]&0xff00)>>4;//前向氧2浮动断接器温度
		p[1]=0;//VCTHT112，待修改！！！
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_F1)//后向燃1浮动断接器温度异常
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_A[64]&0xff00)>>4;//后向燃1浮动断接器温度
		p[1]=0;//VCTHT118，待修改！！！
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_F2)//后向燃2浮动断接器温度异常
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[0]&0x00ff)<<4;//后向燃2浮动断接器温度
		p[1]=0;//VCTHT119，待修改！！！
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_O1)//后向氧1浮动断接器温度异常
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[2]&0xff00)>>4;//后向氧1浮动断接器温度
		p[1]=0;//VCTHT146，待修改！！！
	}
	
	else if(temperature_kind==FAULT_TEMPERATURE_BACK_O2)//后向氧2浮动断接器温度异常
	{
		p[0]=(TGTHT510_1553B_data_TGTHT100_Temper_B[3]&0x00ff)<<4;//后向氧2浮动断接器温度
		p[1]=0;//VCTHT147，待修改！！！
	}
	
	else
	{
		p[0]=0;
		p[1]=0;
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--浮动断接器温度异常
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_faultdiagnosis_supply_temperature_is_normal(uint16 *p)
{
	uint16 i;
	uint16 n;
	
	//待修改！！！，增加VCTHT的温度判断
	n=0;
	for(i=0;i<=6;i=i+2)
	{
		if(p[i]>TABLE_MF61_NEG_05)//低于-5摄氏度
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}



/******************************************************************************************
**名称：补加故障检测模块--浮动断接器温度异常
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_temperature_dealing(fault_TypeDef *p,uint16 temperature_kind)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力值，第一次
		{
			TGTHT510_faultdiagnosis_supply_temperature_get(&p->fault_field1.value[0],temperature_kind);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://采集压力值，第二次
		{
			TGTHT510_faultdiagnosis_supply_temperature_get(&p->fault_field1.value[2],temperature_kind);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://采集压力值，第三次
		{
			TGTHT510_faultdiagnosis_supply_temperature_get(&p->fault_field1.value[4],temperature_kind);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://采集压力值，第四次
		{
			TGTHT510_faultdiagnosis_supply_temperature_get(&p->fault_field1.value[6],temperature_kind);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(TGTHT510_faultdiagnosis_supply_temperature_is_normal(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--贮箱卡滞
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_ka_tank(uint16 ka)
{
	if(ka==FAULT_O_TANK1)//氧1贮箱卡滞
	{
		TGTHT510_faultdiagnosis_supply_ka_tank_dealing(&TGTHT510_fault_supply_ka_o_tank1,ka);
	}
	
	else if(ka==FAULT_O_TANK2)//氧2贮箱卡滞
	{
		TGTHT510_faultdiagnosis_supply_ka_tank_dealing(&TGTHT510_fault_supply_ka_o_tank2,ka);
	}
	
	else if(ka==FAULT_O_TANK3)//氧3贮箱卡滞
	{
		TGTHT510_faultdiagnosis_supply_ka_tank_dealing(&TGTHT510_fault_supply_ka_o_tank3,ka);
	}
	
	else if(ka==FAULT_F_TANK1)//燃1贮箱卡滞
	{
		TGTHT510_faultdiagnosis_supply_ka_tank_dealing(&TGTHT510_fault_supply_ka_f_tank1,ka);
	}
	
	else if(ka==FAULT_F_TANK2)//燃2贮箱卡滞
	{
		TGTHT510_faultdiagnosis_supply_ka_tank_dealing(&TGTHT510_fault_supply_ka_f_tank2,ka);
	}
	
	else if(ka==FAULT_F_TANK3)//燃3贮箱卡滞
	{
		TGTHT510_faultdiagnosis_supply_ka_tank_dealing(&TGTHT510_fault_supply_ka_f_tank3,ka);
	}
	
	else
	{
		asm("nop;");
	}

}

/******************************************************************************************
**名称：补加故障检测模块--贮箱卡滞
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdiagnosis_supply_ka_tank_is_ka(uint16 *p)
{
	uint16 i;
	uint16 n;
	
	n=0;
	for(i=0;i<=6;i=i+2)
	{
		if((p[i]>p[i+1])&&((p[i]-p[i+1])>=FAULT_CONST_PRESSURE_0E1))
		{
			n++;
		}
	}
	
	if(n>=3)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--贮箱卡滞
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_ka_tank_get_pressure(uint16 *p,uint16 ka)
{
	if(ka==FAULT_O_TANK1)//氧1贮箱卡滞
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[18];//PTt19
		p[1]=TGTHT510_1553B_data_TGTHT100[12];//PTt13
	}
	
	else if(ka==FAULT_O_TANK2)//氧2贮箱卡滞
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[20];//PTt21
		p[1]=TGTHT510_1553B_data_TGTHT100[14];//PTt15
	}
	
	else if(ka==FAULT_O_TANK3)//氧3贮箱卡滞
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[22];//PTt23
		p[1]=TGTHT510_1553B_data_TGTHT100[16];//PTt17
	}
	
	else if(ka==FAULT_F_TANK1)//燃1贮箱卡滞
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[19];//PTt20
		p[1]=TGTHT510_1553B_data_TGTHT100[13];//PTt14
	}
	
	else if(ka==FAULT_F_TANK2)//燃2贮箱卡滞
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[21];//PTt22
		p[1]=TGTHT510_1553B_data_TGTHT100[15];//PTt16
	}
	
	else if(ka==FAULT_F_TANK3)//燃3贮箱卡滞
	{
		p[0]=TGTHT510_1553B_data_TGTHT100[23];//PTt24
		p[1]=TGTHT510_1553B_data_TGTHT100[17];//PTt18
	}
	
	else
	{
		p[0]=0;
		p[1]=0;
	}
}


/******************************************************************************************
**名称：补加故障检测模块--贮箱卡滞
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_ka_tank_dealing(fault_TypeDef *p,uint16 ka)
{
	switch(p->fault_field1.step)
	{
		case FAULT_STEP_START://开始
		{
			p->fault_field1.step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1://采集压力值，第一次
		{
			TGTHT510_faultdiagnosis_supply_ka_tank_get_pressure(&p->fault_field1.value[0],ka);
			
			p->fault_field1.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2://采集压力值，第二次
		{
			TGTHT510_faultdiagnosis_supply_ka_tank_get_pressure(&p->fault_field1.value[2],ka);
			
			p->fault_field1.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3://采集压力值，第三次
		{
			TGTHT510_faultdiagnosis_supply_ka_tank_get_pressure(&p->fault_field1.value[4],ka);
			
			p->fault_field1.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4://采集压力值，第四次
		{
			TGTHT510_faultdiagnosis_supply_ka_tank_get_pressure(&p->fault_field1.value[6],ka);
			
			p->fault_field1.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(TGTHT510_faultdiagnosis_supply_ka_tank_is_ka(p->fault_field1.value)==TRUE)
			{
				TGTHT510_faultdiagnosis_how_to_deal_fault_typedef(p,FAULT_FIELD1);
			}
			
			else
			{
				p->fault_field1.step=FAULT_STEP_END;
				p->faultdiagnosis_count=0;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			p->fault_field1.step=FAULT_STEP_START;//重新开始判断故障
			
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}

/******************************************************************************************
**名称：故障处理模块--故障模式检测
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdeal_check_is_fault(fault_TypeDef *p)
{
	if(p->result==TRUE)
	{
		fault_deal.step=FAULT_STEP_START;
		p->result=FALSE;
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}

}

/******************************************************************************************
**名称：故障处理模块--故障模式检测
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdeal_check_is_fault_valve_leak(fault_valve_leak_TypeDef *p)
{
	if(p->result==TRUE)
	{
		fault_deal.step=FAULT_STEP_START;
		p->result=FALSE;
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}

}

/******************************************************************************************
**名称：故障处理模块--故障模式检测
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_check(void)
{
	//推进故检，氧气瓶1泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_gas1_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_O_GAS1;
		return;
	}
	
	//推进故检，氧气瓶2泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_gas2_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_O_GAS2;
		return;
	}
	
	//推进故检，氧气瓶3泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_gas3_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_O_GAS3;
		return;
	}
	
	//推进故障，燃1气瓶泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_gas1_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_F_GAS1;
		return;
	}
	
	//推进故障，燃2气瓶泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_gas2_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_F_GAS2;
		return;
	}
	
	//推进故障，燃3气瓶泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_gas3_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_F_GAS3;
		return;
	}
	
	//推进故障，氧1贮箱超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_tank1_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_OVER_O_TANK1;
		return;
	}
	
	//推进故障，氧2贮箱超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_tank2_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_OVER_O_TANK2;
		return;
	}
	
	//推进故障，氧3贮箱超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_tank3_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_OVER_O_TANK3;
		return;
	}
	
	//推进故障，燃1贮箱超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_tank1_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_OVER_F_TANK1;
		return;
	}
	
	//推进故障，燃2贮箱超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_tank2_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_OVER_F_TANK2;
		return;
	}
	
	//推进故障，燃3贮箱超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_tank3_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_OVER_F_TANK3;
		return;
	}
	
	//推进故障，主份姿控发动机控制阀门泄漏
	if(TGTHT510_faultdeal_check_is_fault_valve_leak(&TGTHT510_fault_push_B_main_valve_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_B_MAIN;
		return;
	}
	
	//推进故障，备份姿控发动机控制阀门泄漏
	if(TGTHT510_faultdeal_check_is_fault_valve_leak(&TGTHT510_fault_push_B_less_valve_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_B_LESS;
		return;
	}
	
	//推进故障，C组姿控发动机控制阀门泄漏
	if(TGTHT510_faultdeal_check_is_fault_valve_leak(&TGTHT510_fault_push_C_all_valve_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_C_ALL;
		return;
	}
	
	//推进故障，A组主份姿控发动机控制阀门泄漏
	if(TGTHT510_faultdeal_check_is_fault_valve_leak(&TGTHT510_fault_push_A_main_valve_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_A_MAIN;
		return;
	}
	
	//推进故障，A组备份姿控发动机控制阀门泄漏
	if(TGTHT510_faultdeal_check_is_fault_valve_leak(&TGTHT510_fault_push_A_less_valve_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_A_LESS;
		return;
	}
	
	//推进故障，氧1贮箱泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_tank1_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_O_TANK1;
		return;
	}
	
	//推进故障，氧2贮箱泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_tank2_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_O_TANK2;
		return;
	}
	
	//推进故障，氧3贮箱泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_o_tank3_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_O_TANK3;
		return;
	}
	
	//推进故障，燃1贮箱泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_tank1_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_F_TANK1;
		return;
	}
	
	//推进故障，燃2贮箱泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_tank2_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_F_TANK2;
		return;
	}
	
	//推进故障，燃3贮箱泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_push_f_tank3_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_PUSH_LEAK_F_TANK3;
		return;
	}
	
	//补加故障，电机驱动器故障
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_TGTHT530)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TGTHT530;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TGTHT530,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，主份液冷主泵故障
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_cooler_zz)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COOLER_ZZ;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COOLER_ZZ,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，主份液冷备泵故障
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_cooler_zb)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COOLER_ZB;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COOLER_ZB,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，备份液冷主泵故障
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_cooler_bz)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COOLER_BZ;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COOLER_BZ,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，备份液冷备泵故障
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_cooler_bb)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COOLER_BB;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COOLER_BB,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，主份液冷泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_leak_cooler_z)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_COOLER_Z;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_COOLER_Z,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，备份液冷泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_leak_cooler_b)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_COOLER_B;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_COOLER_B,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，压气机A入口超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_A_in_over)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_COMP_A_IN;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_COMP_A_IN,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，压气机B入口超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_B_in_over)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_COMP_B_IN;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_COMP_B_IN,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，压气机C入口超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_C_in_over)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_COMP_C_IN;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_COMP_C_IN,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，压气机A电机腔超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_A_motor_over)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，压气机B电机腔超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_B_motor_over)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，压气机C电机腔超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_C_motor_over)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，压气机A超温
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_A_hot)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COMP_A_HOT;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COMP_A_HOT,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，压气机B超温
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_B_hot)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COMP_B_HOT;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COMP_B_HOT,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，压气机C超温
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_C_hot)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COMP_C_HOT;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COMP_C_HOT,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧1补加贮箱超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_o_tank1_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_O_TANK1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_O_TANK1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧2补加贮箱超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_o_tank2_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_O_TANK2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_O_TANK2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧3补加贮箱超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_o_tank3_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_O_TANK3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_O_TANK3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃1补加贮箱超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_f_tank1_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_F_TANK1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_F_TANK1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃2补加贮箱超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_f_tank2_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_F_TANK2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_F_TANK2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃3补加贮箱超压
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_f_tank3_overpressure)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_OVER_F_TANK3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_OVER_F_TANK3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，压气机A膜片破裂
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_A_break)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COMP_A_BREAK;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COMP_A_BREAK,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，压气机B膜片破裂
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_B_break)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COMP_B_BREAK;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COMP_B_BREAK,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，压气机C膜片破裂
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_compressor_C_break)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_COMP_C_BREAK;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_COMP_C_BREAK,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧1气瓶泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_o_gas1_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_O_GAS1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_O_GAS1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧2气瓶泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_o_gas2_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_O_GAS2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_O_GAS2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧3气瓶泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_o_gas3_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_O_GAS3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_O_GAS3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃1气瓶泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_f_gas1_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_F_GAS1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_F_GAS1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃2气瓶泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_f_gas2_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_F_GAS2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_F_GAS2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃3气瓶泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_f_gas3_leak)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_LEAK_F_GAS3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_LEAK_F_GAS3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧1贮箱补加液路泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_pipe_leak_o_tank1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧2贮箱补加液路泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_pipe_leak_o_tank2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧3贮箱补加液路泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_pipe_leak_o_tank3)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃1贮箱补加液路泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_pipe_leak_f_tank1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃2贮箱补加液路泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_pipe_leak_f_tank2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃3贮箱补加液路泄漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_pipe_leak_f_tank3)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧吹除口温度异常
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_interface_o_temperature)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_INTERFACE_O_TEMP;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_INTERFACE_O_TEMP,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃吹除口温度异常
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_interface_f_temperature)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_INTERFACE_F_TEMP;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_INTERFACE_F_TEMP,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧主补加管路内漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_in_leak_o_z)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_IN_LEAK_O_Z;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_IN_LEAK_O_Z,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧备补加管路内漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_in_leak_o_b)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_IN_LEAK_O_B;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_IN_LEAK_O_B,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃主补加管路内漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_in_leak_f_z)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_IN_LEAK_F_Z;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_IN_LEAK_F_Z,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃备补加管路内漏
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_in_leak_f_b)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_IN_LEAK_F_B;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_IN_LEAK_F_B,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，前向燃1浮动断接器温度异常
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_fore_f1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，前向燃2浮动断接器温度异常
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_fore_f2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，前向氧1浮动断接器温度异常
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_fore_o1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，前向氧2浮动断接器温度异常
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_fore_o2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，后向燃1浮动断接器温度异常
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_back_f1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，后向燃2浮动断接器温度异常
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_back_f2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，后向氧1浮动断接器温度异常
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_back_o1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，后向氧2浮动断接器温度异常
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_temperature_back_o2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧1贮箱卡滞
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_ka_o_tank1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_KA_O_TANK1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_KA_O_TANK1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧2贮箱卡滞
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_ka_o_tank2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_KA_O_TANK2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_KA_O_TANK2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，氧3贮箱卡滞
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_ka_o_tank3)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_KA_O_TANK3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_KA_O_TANK3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃1贮箱卡滞
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_ka_f_tank1)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_KA_F_TANK1;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_KA_F_TANK1,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃2贮箱卡滞
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_ka_f_tank2)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_KA_F_TANK2;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_KA_F_TANK2,FAULT_STATE_ABNORMAL);
		return;
	}
	
	//补加故障，燃3贮箱卡滞
	if(TGTHT510_faultdeal_check_is_fault(&TGTHT510_fault_supply_ka_f_tank3)==TRUE)
	{
		fault_deal.fault_mode=FAULT_MODE_SUPPLY_KA_F_TANK3;
		TGTHT510_faultdiagnosis_supply_CG_set(FAULT_MODE_SUPPLY_KA_F_TANK3,FAULT_STATE_ABNORMAL);
		return;
	}
	
	fault_deal.fault_mode=FAULT_MODE_NONE;//无故障
}


/******************************************************************************************
**名称：故障处理模块--故障处理
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_main(void)
{
	TGTHT510_faultdeal_time_dealing(&fault_deal);
	
	if(fault_deal.fault_mode!=FAULT_MODE_NONE)
	{
		switch(fault_deal.fault_mode)
		{
			case FAULT_MODE_PUSH_LEAK_O_GAS1://推进故障，氧1气瓶泄漏
			{
				TGTHT510_faultdeal_push_gas_leak(FAULT_O_GAS1);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_GAS2://推进故障，氧2气瓶泄漏
			{
				TGTHT510_faultdeal_push_gas_leak(FAULT_O_GAS2);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_GAS3://推进故障，氧3气瓶泄漏
			{
				TGTHT510_faultdeal_push_gas_leak(FAULT_O_GAS3);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_GAS1://推进故障，燃1气瓶泄漏
			{
				TGTHT510_faultdeal_push_gas_leak(FAULT_F_GAS1);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_GAS2://推进故障，燃2气瓶泄漏
			{
				TGTHT510_faultdeal_push_gas_leak(FAULT_F_GAS2);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_GAS3://推进故障，燃3气瓶泄漏
			{
				TGTHT510_faultdeal_push_gas_leak(FAULT_F_GAS3);
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_O_TANK1://推进故障，氧1贮箱超压
			{
				TGTHT510_faultdeal_push_tank_overpressure(FAULT_O_TANK1);
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_O_TANK2://推进故障，氧2贮箱超压
			{
				TGTHT510_faultdeal_push_tank_overpressure(FAULT_O_TANK2);
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_O_TANK3://推进故障，氧3贮箱超压
			{
				TGTHT510_faultdeal_push_tank_overpressure(FAULT_O_TANK3);
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_F_TANK1://推进故障，燃1贮箱超压
			{
				TGTHT510_faultdeal_push_tank_overpressure(FAULT_F_TANK1);
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_F_TANK2://推进故障，燃2贮箱超压
			{
				TGTHT510_faultdeal_push_tank_overpressure(FAULT_F_TANK2);
				break;
			}
			
			case FAULT_MODE_PUSH_OVER_F_TANK3://推进故障，燃3贮箱超压
			{
				TGTHT510_faultdeal_push_tank_overpressure(FAULT_F_TANK3);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_B_MAIN://推进故障，主份姿控发动机控制阀门泄漏
			{
				TGTHT510_faultdeal_push_valve_leak(FAULT_B_MAIN_LEAK);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_B_LESS://推进故障，备份姿控发动机控制阀门泄漏
			{
				TGTHT510_faultdeal_push_valve_leak(FAULT_B_LESS_LEAK);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_C_ALL://推进故障，C组姿控发动机控制阀门泄漏
			{
				TGTHT510_faultdeal_push_valve_leak(FAULT_C_ALL_LEAK);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_A_MAIN://推进故障，A组主份姿控发动机控制阀门泄漏
			{
				TGTHT510_faultdeal_push_valve_leak(FAULT_A_MAIN_LEAK);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_A_LESS://推进故障，A组备份姿控发动机控制阀门泄漏
			{
				TGTHT510_faultdeal_push_valve_leak(FAULT_A_LESS_LEAK);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_TANK1://推进故障，氧1贮箱泄漏
			{
				TGTHT510_faultdeal_push_tank_leak(FAULT_O_TANK1);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_TANK2://推进故障，氧2贮箱泄漏
			{
				TGTHT510_faultdeal_push_tank_leak(FAULT_O_TANK2);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_O_TANK3://推进故障，氧3贮箱泄漏
			{
				TGTHT510_faultdeal_push_tank_leak(FAULT_O_TANK3);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_TANK1://推进故障，燃1贮箱泄漏
			{
				TGTHT510_faultdeal_push_tank_leak(FAULT_F_TANK1);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_TANK2://推进故障，燃2贮箱泄漏
			{
				TGTHT510_faultdeal_push_tank_leak(FAULT_F_TANK2);
				break;
			}
			
			case FAULT_MODE_PUSH_LEAK_F_TANK3://推进故障，燃3贮箱泄漏
			{
				TGTHT510_faultdeal_push_tank_leak(FAULT_F_TANK3);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TGTHT530://补加故障，电机驱动器故障
			{
				//待补充！！！！
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_ZZ://补加故障，主份液冷主泵故障
			{
				TGTHT510_faultdeal_supply_cooler(FAULT_COOLER_ZZ);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_ZB://补加故障，主份液冷备泵故障
			{
				TGTHT510_faultdeal_supply_cooler(FAULT_COOLER_ZB);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_BZ://补加故障，备份液冷主泵故障
			{
				TGTHT510_faultdeal_supply_cooler(FAULT_COOLER_BZ);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COOLER_BB://补加故障，备份液冷备泵故障
			{
				TGTHT510_faultdeal_supply_cooler(FAULT_COOLER_BB);
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_COOLER_Z://补加故障，主份液冷泄漏
			{
				TGTHT510_faultdeal_supply_leak_cooler(FAULT_COOLER_Z);
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_COOLER_B://补加故障，备份液冷泄漏
			{
				TGTHT510_faultdeal_supply_leak_cooler(FAULT_COOLER_B);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_A_IN://补加故障，压气机A入口超压
			{
				TGTHT510_faultdeal_supply_over_compressor(FAULT_COMPRESSOR_A_IN_OVER);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_B_IN://补加故障，压气机B入口超压
			{
				TGTHT510_faultdeal_supply_over_compressor(FAULT_COMPRESSOR_B_IN_OVER);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_C_IN://补加故障，压气机C入口超压
			{
				TGTHT510_faultdeal_supply_over_compressor(FAULT_COMPRESSOR_C_IN_OVER);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_A_MOTOR://补加故障，压气机A电机腔超压
			{
				TGTHT510_faultdeal_supply_over_compressor(FAULT_COMPRESSOR_A_MOTOR_OVER);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_B_MOTOR://补加故障，压气机B电机腔超压
			{
				TGTHT510_faultdeal_supply_over_compressor(FAULT_COMPRESSOR_B_MOTOR_OVER);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_COMP_C_MOTOR://补加故障，压气机C电机腔超压
			{
				TGTHT510_faultdeal_supply_over_compressor(FAULT_COMPRESSOR_C_MOTOR_OVER);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_A_HOT://补加故障，压气机A超温
			{
				TGTHT510_faultdeal_supply_hot_compressor(FAULT_COMPRESSOR_A_HOT);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_B_HOT://补加故障，压气机B超温
			{
				TGTHT510_faultdeal_supply_hot_compressor(FAULT_COMPRESSOR_B_HOT);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_C_HOT://补加故障，压气机C超温
			{
				TGTHT510_faultdeal_supply_hot_compressor(FAULT_COMPRESSOR_C_HOT);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_O_TANK1://补加故障，氧1补加贮箱超压
			{
				TGTHT510_faultdeal_supply_tank_overpressure(FAULT_O_TANK1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_O_TANK2://补加故障，氧2补加贮箱超压
			{
				TGTHT510_faultdeal_supply_tank_overpressure(FAULT_O_TANK2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_O_TANK3://补加故障，氧3补加贮箱超压
			{
				TGTHT510_faultdeal_supply_tank_overpressure(FAULT_O_TANK3);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_F_TANK1://补加故障，燃1补加贮箱超压
			{
				TGTHT510_faultdeal_supply_tank_overpressure(FAULT_F_TANK1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_F_TANK2://补加故障，燃2补加贮箱超压
			{
				TGTHT510_faultdeal_supply_tank_overpressure(FAULT_F_TANK2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_OVER_F_TANK3://补加故障，燃3补加贮箱超压
			{
				TGTHT510_faultdeal_supply_tank_overpressure(FAULT_F_TANK3);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_A_BREAK://补加故障，压气机A膜片破裂
			{
				TGTHT510_faultdeal_supply_compressor_break(FAULT_COMPRESSOR_A_BREAK);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_B_BREAK://补加故障，压气机B膜片破裂
			{
				TGTHT510_faultdeal_supply_compressor_break(FAULT_COMPRESSOR_B_BREAK);
				break;
			}
			
			case FAULT_MODE_SUPPLY_COMP_C_BREAK://补加故障，压气机C膜片破裂
			{
				TGTHT510_faultdeal_supply_compressor_break(FAULT_COMPRESSOR_C_BREAK);
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_O_GAS1://补加故障，氧1气瓶泄漏
			{
				TGTHT510_faultdeal_supply_gas_leak();
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_O_GAS2://补加故障，氧2气瓶泄漏
			{
				TGTHT510_faultdeal_supply_gas_leak();
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_O_GAS3://补加故障，氧3气瓶泄漏
			{
				TGTHT510_faultdeal_supply_gas_leak();
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_F_GAS1://补加故障，燃1气瓶泄漏
			{
				TGTHT510_faultdeal_supply_gas_leak();
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_F_GAS2://补加故障，燃2气瓶泄漏
			{
				TGTHT510_faultdeal_supply_gas_leak();
				break;
			}
			
			case FAULT_MODE_SUPPLY_LEAK_F_GAS3://补加故障，燃3气瓶泄漏
			{
				TGTHT510_faultdeal_supply_gas_leak();
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK1://补加故障，氧1贮箱补加液路泄漏
			{
				TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK2://补加故障，氧2贮箱补加液路泄漏
			{
				TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_O_TANK3://补加故障，氧3贮箱补加液路泄漏
			{
				TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK3);
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK1://补加故障，燃1贮箱补加液路泄漏
			{
				TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK2://补加故障，燃2贮箱补加液路泄漏
			{
				TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_PIPE_LEAK_F_TANK3://补加故障，燃3贮箱补加液路泄漏
			{
				TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK3);
				break;
			}
			
			case FAULT_MODE_SUPPLY_INTERFACE_O_TEMP://补加故障，氧吹除口温度异常
			{
				TGTHT510_faultdeal_supply_interface_temperature(FAULT_INTERFACE_O);
				break;
			}
			
			case FAULT_MODE_SUPPLY_INTERFACE_F_TEMP://补加故障，燃吹除口温度异常
			{
				TGTHT510_faultdeal_supply_interface_temperature(FAULT_INTERFACE_F);
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_O_Z://补加故障，氧主补加管路内漏
			{
				TGTHT510_faultdeal_supply_in_leak(FAULT_IN_LEAK_O_Z);
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_O_B://补加故障，氧备补加管路内漏
			{
				TGTHT510_faultdeal_supply_in_leak(FAULT_IN_LEAK_O_B);
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_F_Z://补加故障，燃主补加管路内漏
			{
				TGTHT510_faultdeal_supply_in_leak(FAULT_IN_LEAK_F_Z);
				break;
			}
			
			case FAULT_MODE_SUPPLY_IN_LEAK_F_B://补加故障，燃备补加管路内漏
			{
				TGTHT510_faultdeal_supply_in_leak(FAULT_IN_LEAK_F_B);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F1://补加故障，前向燃1浮动断接器温度异常
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_FORE_F1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_F2://补加故障，前向燃2浮动断接器温度异常
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_FORE_F2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O1://补加故障，前向氧1浮动断接器温度异常
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_FORE_O1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_FORE_O2://补加故障，前向氧2浮动断接器温度异常
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_FORE_O2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F1://补加故障，后向燃1浮动断接器温度异常
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_BACK_F1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_F2://补加故障，后向燃2浮动断接器温度异常
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_BACK_F2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O1://补加故障，后向氧1浮动断接器温度异常
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_BACK_O1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_TEMPERATURE_BACK_O2://补加故障，后向氧2浮动断接器温度异常
			{
				TGTHT510_faultdeal_supply_temperature(FAULT_TEMPERATURE_BACK_O2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_O_TANK1://补加故障，氧1贮箱卡滞
			{
				TGTHT510_faultdeal_supply_ka_tank(FAULT_O_TANK1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_O_TANK2://补加故障，氧2贮箱卡滞
			{
				TGTHT510_faultdeal_supply_ka_tank(FAULT_O_TANK2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_O_TANK3://补加故障，氧3贮箱卡滞
			{
				TGTHT510_faultdeal_supply_ka_tank(FAULT_O_TANK3);
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_F_TANK1://补加故障，燃1贮箱卡滞
			{
				TGTHT510_faultdeal_supply_ka_tank(FAULT_F_TANK1);
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_F_TANK2://补加故障，燃2贮箱卡滞
			{
				TGTHT510_faultdeal_supply_ka_tank(FAULT_F_TANK2);
				break;
			}
			
			case FAULT_MODE_SUPPLY_KA_F_TANK3://补加故障，燃3贮箱卡滞
			{
				TGTHT510_faultdeal_supply_ka_tank(FAULT_F_TANK3);
				break;
			}
			
			default:
			{
				fault_deal.fault_mode=FAULT_MODE_NONE;
				break;
			}
			
		}

	}
	
	else
	{
		TGTHT510_faultdeal_check();//故障巡检
	}
	
}


/******************************************************************************************
**名称：故障处理模块时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_time_start(fault_deal_TypeDef *f)
{
	f->time_flag=TRUE;
	f->time_count=0x0000;
}

/******************************************************************************************
**名称：故障处理模块时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_time_end(fault_deal_TypeDef *f)
{
	f->time_flag=FALSE;
}

/******************************************************************************************
**名称：故障处理模块时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_time_dealing(fault_deal_TypeDef *f)
{
	if(f->time_flag==TRUE)
	{
		f->time_count++;
	}
	
	else
	{
		f->time_count=0;
	}
	
}

/******************************************************************************************
**名称：故障处理模块时间处理函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdeal_time_is_get(fault_deal_TypeDef *f,uint16 val)
{
	if(f->time_count>=val)
	{
		TGTHT510_faultdeal_time_end(f);
		
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************************
**名称：故障处理模块--返回当前工作的压气机号
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdeal_which_compressor_working(void)
{
	if(compressor_state.compressor_A_state==COMPRESSOR_RUN)
	{
		return FAULT_COMPRESSOR_A;
	}
	
	else if(compressor_state.compressor_B_state==COMPRESSOR_RUN)
	{
		return FAULT_COMPRESSOR_B;
	}
	
	else if(compressor_state.compressor_C_state==COMPRESSOR_RUN)
	{
		return FAULT_COMPRESSOR_C;
	}
	
	else
	{
		return FAULT_COMPRESSOR_N;
	}
	
	/*
	返回当前工作的压气机号
	FAULT_COMPRESSOR_A
	FAULT_COMPRESSOR_B
	FAULT_COMPRESSOR_C
	FAULT_COMPRESSOR_N
	
	待修改！！！
	*/
	
}

/******************************************************************************************
**名称：推进处理检测模块--压气机停机程序序列
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：压气机停机程序结束，返回TRUE，未结束则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_compressor_stop_dealing(uint16 compressor,uint16 valve_number)
{
	if(compressor==FAULT_COMPRESSOR_A)//压气机A机
	{
		switch(valve_number)
		{
			case 1://LVb7关
			{
				TGTHT510_faultdeal_lvb_set(LVb7G);
				break;
			}
			
			case 2://LVb9关
			{
				TGTHT510_faultdeal_lvb_set(LVb9G);
				break;
			}
			
			case 3://LVb11关
			{
				TGTHT510_faultdeal_lvb_set(LVb11G);
				break;
			}
			
			case 4://LVb17关
			{
				TGTHT510_faultdeal_lvb_set(LVb17G);
				break;
			}
			
			case 5://LVb19关
			{
				TGTHT510_faultdeal_lvb_set(LVb19G);
				break;
			}
			
			case 6://LVb21开
			{
				TGTHT510_faultdeal_lvb_set(LVb21K);
				break;
			}
			
			case 7://LVb21关
			{
				TGTHT510_faultdeal_lvb_set(LVb21G);
				break;
			}
			
			case 8://LVb13关
			{
				TGTHT510_faultdeal_lvb_set(LVb13G);
				break;
			}
			
			case 9://LVb15关
			{
				TGTHT510_faultdeal_lvb_set(LVb15G);
				break;
			}
			
			case 10://LVb1关
			{
				TGTHT510_faultdeal_lvb_set(LVb1G);
				break;
			}
			
			case 11://LVb3关
			{
				TGTHT510_faultdeal_lvb_set(LVb3G);
				break;
			}
			
			case 12://LVb5关
			{
				TGTHT510_faultdeal_lvb_set(LVb5G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
	else if(compressor==FAULT_COMPRESSOR_B)//压气机B机
	{
		switch(valve_number)
		{
			case 1://LVb8关
			{
				TGTHT510_faultdeal_lvb_set(LVb8G);
				break;
			}
			
			case 2://LVb10关
			{
				TGTHT510_faultdeal_lvb_set(LVb10G);
				break;
			}
			
			case 3://LVb12关
			{
				TGTHT510_faultdeal_lvb_set(LVb12G);
				break;
			}
			
			case 4://LVb18关
			{
				TGTHT510_faultdeal_lvb_set(LVb18G);
				break;
			}
			
			case 5://LVb20关
			{
				TGTHT510_faultdeal_lvb_set(LVb20G);
				break;
			}
			
			case 6://LVb22开
			{
				TGTHT510_faultdeal_lvb_set(LVb22K);
				break;
			}
			
			case 7://LVb22关
			{
				TGTHT510_faultdeal_lvb_set(LVb22G);
				break;
			}
			
			case 8://LVb14关
			{
				TGTHT510_faultdeal_lvb_set(LVb14G);
				break;
			}
			
			case 9://LVb16关
			{
				TGTHT510_faultdeal_lvb_set(LVb16G);
				break;
			}
			
			case 10://LVb2关
			{
				TGTHT510_faultdeal_lvb_set(LVb2G);
				break;
			}
			
			case 11://LVb4关
			{
				TGTHT510_faultdeal_lvb_set(LVb4G);
				break;
			}
			
			case 12://LVb6关
			{
				TGTHT510_faultdeal_lvb_set(LVb6G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
		
	}
	
	else if(compressor==FAULT_COMPRESSOR_C)//压气机C机
	{
		if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
		{
			switch(valve_number)
			{
				case 1://LVb8关
				{
					TGTHT510_faultdeal_lvb_set(LVb8G);
					break;
				}
				
				case 2://LVb10关
				{
					TGTHT510_faultdeal_lvb_set(LVb10G);
					break;
				}
				
				case 3://LVb12关
				{
					TGTHT510_faultdeal_lvb_set(LVb12G);
					break;
				}
				
				case 4://LVb25关
				{
					TGTHT510_faultdeal_lvb_set(LVb25G);
					break;
				}
				
				case 5://LVb26关
				{
					TGTHT510_faultdeal_lvb_set(LVb26G);
					break;
				}
				
				case 6://LVb87开
				{
					TGTHT510_faultdeal_lvb_set(LVb87K);
					break;
				}
				
				case 7://LVb87关
				{
					TGTHT510_faultdeal_lvb_set(LVb87G);
					break;
				}
				
				case 8://LVb23关
				{
					TGTHT510_faultdeal_lvb_set(LVb23G);
					break;
				}
				
				case 9://LVb24关
				{
					TGTHT510_faultdeal_lvb_set(LVb24G);
					break;
				}
				
				case 10://LVb2关
				{
					TGTHT510_faultdeal_lvb_set(LVb2G);
					break;
				}
				
				case 11://LVb4关
				{
					TGTHT510_faultdeal_lvb_set(LVb4G);
					break;
				}
				
				case 12://LVb6关
				{
					TGTHT510_faultdeal_lvb_set(LVb6G);
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
		}
		
		else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
		{
			switch(valve_number)
			{
				case 1://LVb7关
				{
					TGTHT510_faultdeal_lvb_set(LVb7G);
					break;
				}
				
				case 2://LVb9关
				{
					TGTHT510_faultdeal_lvb_set(LVb9G);
					break;
				}
				
				case 3://LVb11关
				{
					TGTHT510_faultdeal_lvb_set(LVb11G);
					break;
				}
				
				case 4://LVb25关
				{
					TGTHT510_faultdeal_lvb_set(LVb25G);
					break;
				}
				
				case 5://LVb26关
				{
					TGTHT510_faultdeal_lvb_set(LVb26G);
					break;
				}
				
				case 6://LVb87开
				{
					TGTHT510_faultdeal_lvb_set(LVb87K);
					break;
				}
				
				case 7://LVb87关
				{
					TGTHT510_faultdeal_lvb_set(LVb87G);
					break;
				}
				
				case 8://LVb23关
				{
					TGTHT510_faultdeal_lvb_set(LVb23G);
					break;
				}
				
				case 9://LVb24关
				{
					TGTHT510_faultdeal_lvb_set(LVb24G);
					break;
				}
				
				case 10://LVb1关
				{
					TGTHT510_faultdeal_lvb_set(LVb1G);
					break;
				}
				
				case 11://LVb3关
				{
					TGTHT510_faultdeal_lvb_set(LVb3G);
					break;
				}
				
				case 12://LVb5关
				{
					TGTHT510_faultdeal_lvb_set(LVb5G);
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
**名称：推进处理检测模块--压气机停机程序序列
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：压气机停机程序结束，返回TRUE，未结束则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_compressor_stop_equment_command(uint16 compressor)
{
	if(compressor==FAULT_COMPRESSOR_A)//压气机A机
	{
		TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_A_STOP);
	}
	
	else if(compressor==FAULT_COMPRESSOR_B)//压气机B机
	{
		TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_B_STOP);
	}
	
	else if(compressor==FAULT_COMPRESSOR_C)//压气机C机
	{
		TGTHT510_collectANDgroup_equiment_command_generate(COMPRESS_C_STOP);
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：推进处理检测模块--压气机停机程序序列
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：压气机停机程序结束，返回TRUE，未结束则返回FALSE
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_faultdeal_compressor_stop(uint16 compressor)
{
	switch(fault_deal.compressor_step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.compressor_step=FAULT_STEP_NO1;
			
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,1);
			fault_deal.compressor_step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,2);
			fault_deal.compressor_step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,3);
			fault_deal.compressor_step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,4);
			fault_deal.compressor_step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,5);
			fault_deal.compressor_step=FAULT_STEP_NO6;
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,6);
			fault_deal.compressor_step=FAULT_STEP_NO7;
			break;
		}
		
		case FAULT_STEP_NO7://设备管理指令，压气机关机
		{
			TGTHT510_faultdeal_compressor_stop_equment_command(compressor);
			fault_deal.compressor_step=FAULT_STEP_NO8;
			break;
		}
		
		case FAULT_STEP_NO8://开始延时等待
		{
			TGTHT510_faultdeal_time_start(&fault_deal);
			fault_deal.compressor_step=FAULT_STEP_NO9;
			break;
		}
		
		case FAULT_STEP_NO9://延时等待1min
		{
			if(TGTHT510_faultdeal_time_is_get(&fault_deal,CONST_TIME_1MIN)==TRUE)
			{
				fault_deal.compressor_step=FAULT_STEP_NO10;
			}
			break;
		}
		
		case FAULT_STEP_NO10:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,7);
			fault_deal.compressor_step=FAULT_STEP_NO11;
			break;
		}
		
		case FAULT_STEP_NO11:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,8);
			fault_deal.compressor_step=FAULT_STEP_NO12;
			break;
		}
		
		case FAULT_STEP_NO12:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,9);
			fault_deal.compressor_step=FAULT_STEP_NO13;
			break;
		}
		
		case FAULT_STEP_NO13:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,10);
			fault_deal.compressor_step=FAULT_STEP_NO14;
			break;
		}
		
		case FAULT_STEP_NO14:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,11);
			fault_deal.compressor_step=FAULT_STEP_NO15;
			break;
		}
		
		case FAULT_STEP_NO15:
		{
			TGTHT510_faultdeal_compressor_stop_dealing(compressor,12);
			fault_deal.compressor_step=FAULT_STEP_END;
			break;
		}
		
		case FAULT_STEP_END:
		{
			fault_deal.compressor_step=FAULT_STEP_NONE;
			
			return TRUE;//程序序列结束，返回TRUE
			
			break;
		}
		
		default:
		{
			return TRUE;//程序序列结束，返回TRUE
			break;
		}
		
	}
	
	return FALSE;//程序序列未结束，返回FALSE
}




/******************************************************************************************
**名称：推进故障处理模块--气瓶泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_push_gas_leak(uint16 gas_leak)
{
	//设置对应的常规故障遥测参数为异常状态，由数管处理
	
	if(gas_leak==FAULT_O_GAS1)//氧气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_O_GAS1,FAULT_STATE_ABNORMAL);
	}
	
	else if(gas_leak==FAULT_O_GAS2)//氧气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_O_GAS2,FAULT_STATE_ABNORMAL);
	}
	
	else if(gas_leak==FAULT_O_GAS3)//氧气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_O_GAS3,FAULT_STATE_ABNORMAL);
	}
	
	else if(gas_leak==FAULT_F_GAS1)//燃气瓶1泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_F_GAS1,FAULT_STATE_ABNORMAL);
	}
	
	else if(gas_leak==FAULT_F_GAS2)//燃气瓶2泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_F_GAS2,FAULT_STATE_ABNORMAL);	
	}
	
	else if(gas_leak==FAULT_F_GAS3)//燃气瓶3泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_F_GAS3,FAULT_STATE_ABNORMAL);
	}
	
	else
	{
		asm("nop;");
	}
	
	fault_deal.fault_mode=FAULT_MODE_NONE;
	
	fault_deal.step=FAULT_STEP_NONE;
}

/******************************************************************************************
**名称：推进故障处理模块--贮箱超压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_push_tank_overpressure(uint16 tank_overpressure)
{
	if(tank_overpressure==FAULT_O_TANK1)//故障检测--氧1贮箱
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_OVER_O_TANK1,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_overpressure==FAULT_O_TANK2)//故障检测--氧2贮箱
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_OVER_O_TANK2,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_overpressure==FAULT_O_TANK3)//故障检测--氧3贮箱
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_OVER_O_TANK3,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_overpressure==FAULT_F_TANK1)//故障检测--燃1贮箱
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_OVER_F_TANK1,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_overpressure==FAULT_F_TANK2)//故障检测--燃2贮箱
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_OVER_F_TANK2,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_overpressure==FAULT_F_TANK3)//故障检测--燃3贮箱
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_OVER_F_TANK3,FAULT_STATE_ABNORMAL);
	}
	
	else
	{
		asm("nop;");
	}
	
	fault_deal.fault_mode=FAULT_MODE_NONE;
	
	fault_deal.step=FAULT_STEP_NONE;
	
}

/******************************************************************************************
**名称：推进故障检测模块--发动机泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_push_valve_leak(uint16 valve_leak)
{
	if(valve_leak==FAULT_B_MAIN_LEAK)//B组主份发动机泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_B_MAIN,FAULT_STATE_ABNORMAL);
	}
	
	else if(valve_leak==FAULT_B_LESS_LEAK)//B组备份发动机泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_B_LESS,FAULT_STATE_ABNORMAL);
	}
	
	else if(valve_leak==FAULT_C_ALL_LEAK)//C组发动机泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_C_ALL,FAULT_STATE_ABNORMAL);
	}
	
	else if(valve_leak==FAULT_A_MAIN_LEAK)//A组主份发动机泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_A_MAIN,FAULT_STATE_ABNORMAL);
	}
	
	else if(valve_leak==FAULT_A_LESS_LEAK)//A组备份发动机泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_A_LESS,FAULT_STATE_ABNORMAL);
	}
	
	else
	{
		asm("nop;");
	}
	
	fault_deal.fault_mode=FAULT_MODE_NONE;
	
	fault_deal.step=FAULT_STEP_NONE;
	
}

/******************************************************************************************
**名称：推进处理检测模块--贮箱泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_push_tank_leak(uint16 tank_leak)
{
	if(tank_leak==FAULT_O_TANK1)//氧1贮箱泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_O_TANK1,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_leak==FAULT_O_TANK2)//氧2贮箱泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_O_TANK2,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_leak==FAULT_O_TANK3)//氧3贮箱泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_O_TANK3,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_leak==FAULT_F_TANK1)//燃1贮箱泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_F_TANK1,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_leak==FAULT_F_TANK2)//燃2贮箱泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_F_TANK2,FAULT_STATE_ABNORMAL);
	}
	
	else if(tank_leak==FAULT_F_TANK3)//燃3贮箱泄漏
	{
		TGTHT510_faultdiagnosis_push_CG_set(FAULT_MODE_PUSH_LEAK_F_TANK3,FAULT_STATE_ABNORMAL);
	}
	
	else
	{
		asm("nop;");
	}
	
	fault_deal.fault_mode=FAULT_MODE_NONE;
	
	fault_deal.step=FAULT_STEP_NONE;
	
}


/******************************************************************************************
**名称：补加故障处理模块--液冷模块故障
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_cooler(uint16 fault_cooler)
{
	if(fault_cooler==FAULT_COOLER_ZZ)//故障检测--主份液冷主泵
	{
		TGTHT510_1553b_relay_dealing(BUS_COOLER_1_POWER_OFF);//主备泵断电
		TGTHT510_1553b_relay_dealing(BUS_COOLER_1_LESS_POWER_ON);//备泵加电
		
		fault_deal.fault_mode=FAULT_MODE_NONE;
		fault_deal.step=FAULT_STEP_NONE;
		
	}
	
	else if(fault_cooler==FAULT_COOLER_ZB)//故障检测--主份液冷备泵
	{
		TGTHT510_faultdeal_supply_cooler_dealing();
		TGTHT510_faultdeal_supply_pause();//补加流程暂停
	}
	
	else if(fault_cooler==FAULT_COOLER_BZ)//故障检测--备份液冷主泵
	{
		TGTHT510_1553b_relay_dealing(BUS_COOLER_2_POWER_OFF);//主备泵断电
		TGTHT510_1553b_relay_dealing(BUS_COOLER_2_LESS_POWER_ON);//备泵加电
		
		fault_deal.fault_mode=FAULT_MODE_NONE;
		fault_deal.step=FAULT_STEP_NONE;
	}
	
	else if(fault_cooler==FAULT_COOLER_BB)//故障检测--备份液冷备泵
	{
		TGTHT510_faultdeal_supply_cooler_dealing();
		TGTHT510_faultdeal_supply_pause();//补加流程暂停
	}
	
	else
	{
		fault_deal.fault_mode=FAULT_MODE_NONE;
		fault_deal.step=FAULT_STEP_NONE;
	}
	
}

/******************************************************************************************
**名称：补加故障处理模块--液冷模块故障
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_cooler_dealing(void)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			fault_deal.compressor_number=TGTHT510_faultdeal_which_compressor_working();
			
			if(fault_deal.compressor_number==FAULT_COMPRESSOR_N)//无压气机工作
			{
				fault_deal.fault_mode=FAULT_MODE_NONE;
				fault_deal.step=FAULT_STEP_NONE;
			}
			
			else//有压气机正在工作
			{
				fault_deal.compressor_step=FAULT_STEP_START;
				fault_deal.step=FAULT_STEP_NO2;
			}
			break;
		}
		
		case FAULT_STEP_NO2://压气机停机程序
		{
			if(TGTHT510_faultdeal_compressor_stop(fault_deal.compressor_number)==TRUE)
			{
				fault_deal.step=FAULT_STEP_END;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			fault_deal.compressor_number=FAULT_COMPRESSOR_N;
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}

	}
	
}

/******************************************************************************************
**名称：补加故障处理模块--液冷模块泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_leak_cooler(uint16 leak_cooler)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			if(leak_cooler==FAULT_COOLER_Z)//主份液冷泄漏
			{
				TGTHT510_faultdeal_lvb_set(LVb27G);
			}
			
			else if(leak_cooler==FAULT_COOLER_B)//备份液冷泄漏
			{
				TGTHT510_faultdeal_lvb_set(LVb28G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			if(leak_cooler==FAULT_COOLER_Z)//主份液冷泄漏
			{
				TGTHT510_faultdeal_lvb_set(LVb29G);
			}
			
			else if(leak_cooler==FAULT_COOLER_B)//备份液冷泄漏
			{
				TGTHT510_faultdeal_lvb_set(LVb30G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			if(leak_cooler==FAULT_COOLER_Z)//主份液冷泄漏
			{
				TGTHT510_faultdeal_lvb_set(LVb31G);
			}
			
			else if(leak_cooler==FAULT_COOLER_B)//备份液冷泄漏
			{
				TGTHT510_faultdeal_lvb_set(LVb32G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			if(leak_cooler==FAULT_COOLER_Z)//主份液冷泄漏
			{
				TGTHT510_faultdeal_lvb_set(LVb33G);
			}
			
			else if(leak_cooler==FAULT_COOLER_B)//备份液冷泄漏
			{
				TGTHT510_faultdeal_lvb_set(LVb34G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO5;
			
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			if(leak_cooler==FAULT_COOLER_Z)//主份液冷泄漏
			{
				TGTHT510_faultdeal_lvb_set(LVb35G);
			}
			
			else if(leak_cooler==FAULT_COOLER_B)//备份液冷泄漏
			{
				TGTHT510_faultdeal_lvb_set(LVb36G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO6;
			
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			if(leak_cooler==FAULT_COOLER_Z)//主份液冷泄漏
			{
				TGTHT510_faultdeal_lvb_set(LVb37G);
			}
			
			else if(leak_cooler==FAULT_COOLER_B)//备份液冷泄漏
			{
				TGTHT510_faultdeal_lvb_set(LVb38G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO7;
			
			break;
		}
		
		case FAULT_STEP_NO7:
		{
			fault_deal.compressor_number=TGTHT510_faultdeal_which_compressor_working();
			
			if(fault_deal.compressor_number==FAULT_COMPRESSOR_N)//无压气机工作
			{
				fault_deal.fault_mode=FAULT_MODE_NONE;
				fault_deal.step=FAULT_STEP_NONE;
			}
			
			else//有压气机正在工作
			{
				fault_deal.compressor_step=FAULT_STEP_START;
				fault_deal.step=FAULT_STEP_NO8;
			}
			
			break;
		}
		
		case FAULT_STEP_NO8:
		{
			if(TGTHT510_faultdeal_compressor_stop(fault_deal.compressor_number)==TRUE)
			{
				fault_deal.step=FAULT_STEP_END;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			TGTHT510_faultdeal_supply_pause();//补加流程暂停
			fault_deal.compressor_number=FAULT_COMPRESSOR_N;
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}

	}
	
}


/******************************************************************************************
**名称：补加故障检测模块--压气机超压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_over_compressor(uint16 over_kind)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			if(over_kind==FAULT_COMPRESSOR_A_IN_OVER)//压气机A入口超压
			{
				TGTHT510_faultdeal_lvb_set(LVb13G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_B_IN_OVER)//压气机B入口超压
			{
				TGTHT510_faultdeal_lvb_set(LVb14G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_C_IN_OVER)//压气机C入口超压
			{
				TGTHT510_faultdeal_lvb_set(LVb23G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_A_MOTOR_OVER)//压气机A电机腔超压
			{
				TGTHT510_faultdeal_lvb_set(LVb17G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_B_MOTOR_OVER)//压气机B电机腔超压
			{
				TGTHT510_faultdeal_lvb_set(LVb18G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_C_MOTOR_OVER)//压气机C电机腔超压
			{
				TGTHT510_faultdeal_lvb_set(LVb25G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			if(over_kind==FAULT_COMPRESSOR_A_IN_OVER)//压气机A入口超压
			{
				TGTHT510_faultdeal_lvb_set(LVb15G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_B_IN_OVER)//压气机B入口超压
			{
				TGTHT510_faultdeal_lvb_set(LVb16G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_C_IN_OVER)//压气机C入口超压
			{
				TGTHT510_faultdeal_lvb_set(LVb24G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_A_MOTOR_OVER)//压气机A电机腔超压
			{
				TGTHT510_faultdeal_lvb_set(LVb19G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_B_MOTOR_OVER)//压气机B电机腔超压
			{
				TGTHT510_faultdeal_lvb_set(LVb20G);
			}
			
			else if(over_kind==FAULT_COMPRESSOR_C_MOTOR_OVER)//压气机C电机腔超压
			{
				TGTHT510_faultdeal_lvb_set(LVb26G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO3;
			
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			fault_deal.compressor_step=FAULT_STEP_START;
			fault_deal.step=FAULT_STEP_NO4;
			
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			if(over_kind==FAULT_COMPRESSOR_A_IN_OVER)//压气机A入口超压
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_A)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(over_kind==FAULT_COMPRESSOR_B_IN_OVER)//压气机B入口超压
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_B)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(over_kind==FAULT_COMPRESSOR_C_IN_OVER)//压气机C入口超压
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_C)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(over_kind==FAULT_COMPRESSOR_A_MOTOR_OVER)//压气机A电机腔超压
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_A)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(over_kind==FAULT_COMPRESSOR_B_MOTOR_OVER)//压气机B电机腔超压
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_B)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(over_kind==FAULT_COMPRESSOR_C_MOTOR_OVER)//压气机C电机腔超压
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_C)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else
			{
				fault_deal.step=FAULT_STEP_END;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			TGTHT510_faultdeal_supply_pause();//补加流程暂停
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**名称：补加故障处理模块--压气机超温
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_hot_compressor(uint16 hot_kind)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			fault_deal.compressor_step=FAULT_STEP_START;
			fault_deal.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			if(hot_kind==FAULT_COMPRESSOR_A_HOT)
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_A)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}

			else if(hot_kind==FAULT_COMPRESSOR_B_HOT)
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_B)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}	
			
			else if(hot_kind==FAULT_COMPRESSOR_C_HOT)
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_C)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}	
			
			else
			{
				fault_deal.step=FAULT_STEP_END;
			}
			
			break;
		
		}
		
		case FAULT_STEP_END:
		{
			TGTHT510_faultdeal_supply_pause();//补加流程暂停
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**名称：补加故障处理模块--补加贮箱超压
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_tank_overpressure(uint16 tank_overpressure)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			if(tank_overpressure==FAULT_O_TANK1)//故障检测--氧1贮箱
			{
				TGTHT510_faultdeal_lvb_set(LVb7G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK2)//故障检测--氧2贮箱
			{
				TGTHT510_faultdeal_lvb_set(LVb9G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK3)//故障检测--氧3贮箱
			{
				TGTHT510_faultdeal_lvb_set(LVb11G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK1)//故障检测--燃1贮箱
			{
				TGTHT510_faultdeal_lvb_set(LVb8G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK2)//故障检测--燃2贮箱
			{
				TGTHT510_faultdeal_lvb_set(LVb10G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK3)//故障检测--燃3贮箱
			{
				TGTHT510_faultdeal_lvb_set(LVb12G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			if(tank_overpressure==FAULT_O_TANK1)//故障检测--氧1贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt1G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK2)//故障检测--氧2贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt3G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK3)//故障检测--氧3贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt5G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK1)//故障检测--燃1贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt2G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK2)//故障检测--燃2贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt4G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK3)//故障检测--燃3贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt6G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO3;
			
			break;
			
		}
		
		case FAULT_STEP_NO3://开始延时等待
		{
			TGTHT510_faultdeal_time_start(&fault_deal);
			fault_deal.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4://延时等待1min
		{
			if(TGTHT510_faultdeal_time_is_get(&fault_deal,CONST_TIME_1MIN)==TRUE)
			{
				fault_deal.step=FAULT_STEP_NO5;
			}
			break;
		}
	
		case FAULT_STEP_NO5:
		{
			fault_deal.compressor_number=TGTHT510_faultdeal_which_compressor_working();
			
			if(fault_deal.compressor_number==FAULT_COMPRESSOR_N)//无压气机工作
			{
				fault_deal.fault_mode=FAULT_MODE_NONE;
				fault_deal.step=FAULT_STEP_END;
			}
			
			else//有压气机正在工作
			{
				fault_deal.compressor_step=FAULT_STEP_START;
				fault_deal.step=FAULT_STEP_NO6;
			}
			
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			if(TGTHT510_faultdeal_compressor_stop(fault_deal.compressor_number)==TRUE)
			{
				fault_deal.step=FAULT_STEP_NO7;
			}
			
			break;
		}
		
		case FAULT_STEP_NO7:
		{
			if(tank_overpressure==FAULT_O_TANK1)//故障检测--氧1贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt7G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK2)//故障检测--氧2贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt11G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK3)//故障检测--氧3贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt15G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK1)//故障检测--燃1贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt8G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK2)//故障检测--燃2贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt12G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK3)//故障检测--燃3贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt16G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO8;
			
			break;
			
		}
		
		case FAULT_STEP_NO8://开始延时等待
		{
			TGTHT510_faultdeal_time_start(&fault_deal);
			fault_deal.step=FAULT_STEP_NO9;
			break;
		}
		
		case FAULT_STEP_NO9://延时等待1min
		{
			if(TGTHT510_faultdeal_time_is_get(&fault_deal,CONST_TIME_1MIN)==TRUE)
			{
				fault_deal.step=FAULT_STEP_NO10;
			}
			break;
		}
		
		case FAULT_STEP_NO10:
		{
			if(tank_overpressure==FAULT_O_TANK1)//故障检测--氧1贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt9G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK2)//故障检测--氧2贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt13G);
			}
			
			else if(tank_overpressure==FAULT_O_TANK3)//故障检测--氧3贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt17G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK1)//故障检测--燃1贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt10G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK2)//故障检测--燃2贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt14G);
			}
			
			else if(tank_overpressure==FAULT_F_TANK3)//故障检测--燃3贮箱
			{
				TGTHT510_supply_main_lvt_set(LVt18G);
			}
			
			else
			{
				asm("nop;");
			}
			
			fault_deal.step=FAULT_STEP_NO11;
			
			break;
			
		}
		
		case FAULT_STEP_NO11://开始延时等待
		{
			TGTHT510_faultdeal_time_start(&fault_deal);
			fault_deal.step=FAULT_STEP_NO12;
			break;
		}
		
		case FAULT_STEP_NO12://延时等待1min
		{
			if(TGTHT510_faultdeal_time_is_get(&fault_deal,CONST_TIME_1MIN)==TRUE)
			{
				fault_deal.step=FAULT_STEP_END;
			}
			break;
		}
		
		case FAULT_STEP_END:
		{
			TGTHT510_faultdeal_supply_pause();//补加流程暂停
			fault_deal.compressor_number=FAULT_COMPRESSOR_N;
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**名称：补加故障处理模块--压气机膜片破裂
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_compressor_break(uint16 compressor_break)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			fault_deal.compressor_step=FAULT_STEP_START;
			fault_deal.step=FAULT_STEP_NO2;
			
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			if(compressor_break==FAULT_COMPRESSOR_A_BREAK)//压气机A膜片破裂
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_A)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(compressor_break==FAULT_COMPRESSOR_B_BREAK)//压气机B膜片破裂
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_B)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			
			else if(compressor_break==FAULT_COMPRESSOR_C_BREAK)//压气机C膜片破裂
			{
				if(TGTHT510_faultdeal_compressor_stop(FAULT_COMPRESSOR_C)==TRUE)
				{
					fault_deal.step=FAULT_STEP_END;
				}
			}
			else
			{
				fault_deal.step=FAULT_STEP_END;
			}
			
			break;
			
		}
		
		case FAULT_STEP_END:
		{
			TGTHT510_faultdeal_supply_pause();//补加流程暂停
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			break;
		}
		
		default:
		{
			break;
		}
	
	}
	
}

/******************************************************************************************
**名称：补加故障处理模块--补加气瓶泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：NE58651577231
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_gas_leak(void)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			fault_deal.compressor_number=TGTHT510_faultdeal_which_compressor_working();
			
			if(fault_deal.compressor_number==FAULT_COMPRESSOR_N)//无压气机工作
			{
				fault_deal.fault_mode=FAULT_MODE_NONE;
				fault_deal.step=FAULT_STEP_NONE;
			}
			
			else//有压气机正在工作
			{
				fault_deal.compressor_step=FAULT_STEP_START;
				fault_deal.step=FAULT_STEP_NO2;
			}
			
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			if(TGTHT510_faultdeal_compressor_stop(fault_deal.compressor_number)==TRUE)
			{
				fault_deal.step=FAULT_STEP_END;
			}
			
			break;
		}
		
		case FAULT_STEP_END:
		{
			TGTHT510_faultdeal_supply_pause();//补加流程暂停
			fault_deal.compressor_number=FAULT_COMPRESSOR_N;
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**名称：补加故障处理模块--贮箱补加液路泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(uint16 tank_leak,uint16 number)
{
	//氧贮箱补加液路
	if((tank_leak==FAULT_O_TANK1)||(tank_leak==FAULT_O_TANK2)||(tank_leak==FAULT_O_TANK3))
	{
		if((TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O1)||\
		(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O3))//主路补加接口
		{
			switch(number)
			{
				case 1:
				{
					TGTHT510_faultdeal_lvb_set(LVb43G);
					break;
				}
				
				case 2:
				{
					TGTHT510_faultdeal_lvb_set(LVb45G);
					break;
				}
				
				case 3:
				{
					TGTHT510_faultdeal_lvb_set(LVb47G);
					break;
				}
				
				case 4:
				{
					TGTHT510_faultdeal_lvb_set(LVb39G);
					break;
				}
				
				case 5:
				{
					TGTHT510_faultdeal_lvb_set(LVb63G);
					break;
				}
				
				case 6:
				{
					TGTHT510_faultdeal_lvb_set(LVb71K);
					break;
				}
				
				case 7:
				{
					TGTHT510_faultdeal_lvb_set(LVb79K);
					break;
				}
				
				case 8:
				{
					TGTHT510_faultdeal_lvb_set(LVb71G);
					break;
				}
				
				case 9:
				{
					TGTHT510_faultdeal_lvb_set(LVb79G);
					break;
				}
				
				case 10:
				{
					TGTHT510_faultdeal_lvb_set(LVb41G);
					break;
				}
				
				case 11:
				{
					TGTHT510_faultdeal_lvb_set(LVb65G);
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
		}
		
		
		else if((TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O2)||\
		(TGTHT510_supply_decode_par.interface_O==DECODE_INTERFACE_O4))//备路补加接口
		{
			switch(number)
			{
				case 1:
				{
					TGTHT510_faultdeal_lvb_set(LVb53G);
					break;
				}
				
				case 2:
				{
					TGTHT510_faultdeal_lvb_set(LVb55G);
					break;
				}
				
				case 3:
				{
					TGTHT510_faultdeal_lvb_set(LVb57G);
					break;
				}
				
				case 4:
				{
					TGTHT510_faultdeal_lvb_set(LVb49G);
					break;
				}
				
				case 5:
				{
					TGTHT510_faultdeal_lvb_set(LVb59G);
					break;
				}
				
				case 6:
				{
					TGTHT510_faultdeal_lvb_set(LVb67K);
					break;
				}
				
				case 7:
				{
					TGTHT510_faultdeal_lvb_set(LVb85K);
					break;
				}
				
				case 8:
				{
					TGTHT510_faultdeal_lvb_set(LVb67G);
					break;
				}
				
				case 9:
				{
					TGTHT510_faultdeal_lvb_set(LVb85G);
					break;
				}
				
				case 10:
				{
					TGTHT510_faultdeal_lvb_set(LVb51G);
					break;
				}
				
				case 11:
				{
					TGTHT510_faultdeal_lvb_set(LVb61G);
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
	//燃贮箱补加液路
	else if((tank_leak==FAULT_F_TANK1)||(tank_leak==FAULT_F_TANK2)||(tank_leak==FAULT_F_TANK3))
	{
		if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R1)||\
		(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R3))//主路补加接口
		{
			switch(number)
			{
				case 1:
				{
					TGTHT510_faultdeal_lvb_set(LVb44G);
					break;
				}
				
				case 2:
				{
					TGTHT510_faultdeal_lvb_set(LVb46G);
					break;
				}
				
				case 3:
				{
					TGTHT510_faultdeal_lvb_set(LVb48G);
					break;
				}
				
				case 4:
				{
					TGTHT510_faultdeal_lvb_set(LVb40G);
					break;
				}
				
				case 5:
				{
					TGTHT510_faultdeal_lvb_set(LVb64G);
					break;
				}
				
				case 6:
				{
					TGTHT510_faultdeal_lvb_set(LVb72K);
					break;
				}
				
				case 7:
				{
					TGTHT510_faultdeal_lvb_set(LVb80K);
					break;
				}
				
				case 8:
				{
					TGTHT510_faultdeal_lvb_set(LVb72G);
					break;
				}
				
				case 9:
				{
					TGTHT510_faultdeal_lvb_set(LVb80G);
					break;
				}
				
				case 10:
				{
					TGTHT510_faultdeal_lvb_set(LVb42G);
					break;
				}
				
				case 11:
				{
					TGTHT510_faultdeal_lvb_set(LVb66G);
					break;
				}
				
				default:
				{
					break;
				}
				
			}
			
		}
		
		else if((TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R2)||\
		(TGTHT510_supply_decode_par.interface_F==DECODE_INTERFACE_R4))//备路补加接口
		{
			switch(number)
			{
				case 1:
				{
					TGTHT510_faultdeal_lvb_set(LVb54G);
					break;
				}
				
				case 2:
				{
					TGTHT510_faultdeal_lvb_set(LVb56G);
					break;
				}
				
				case 3:
				{
					TGTHT510_faultdeal_lvb_set(LVb58G);
					break;
				}
				
				case 4:
				{
					TGTHT510_faultdeal_lvb_set(LVb50G);
					break;
				}
				
				case 5:
				{
					TGTHT510_faultdeal_lvb_set(LVb60G);
					break;
				}
				
				case 6:
				{
					TGTHT510_faultdeal_lvb_set(LVb68K);
					break;
				}
				
				case 7:
				{
					TGTHT510_faultdeal_lvb_set(LVb86K);
					break;
				}
				
				case 8:
				{
					TGTHT510_faultdeal_lvb_set(LVb68G);
					break;
				}
				
				case 9:
				{
					TGTHT510_faultdeal_lvb_set(LVb86G);
					break;
				}
				
				case 10:
				{
					TGTHT510_faultdeal_lvb_set(LVb52G);
					break;
				}
				
				case 11:
				{
					TGTHT510_faultdeal_lvb_set(LVb62G);
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
**名称：补加故障处理模块--贮箱补加液路泄漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_tank_pipe_leak(uint16 tank_leak)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			TGTHT510_faultdeal_supply_pause();//补加流程暂停
			fault_deal.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,1);
			fault_deal.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,2);
			fault_deal.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,3);
			fault_deal.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,4);
			fault_deal.step=FAULT_STEP_NO6;
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,5);
			fault_deal.step=FAULT_STEP_NO7;
			break;
		}
		
		case FAULT_STEP_NO7:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,6);
			fault_deal.step=FAULT_STEP_NO8;
			break;
		}
		
		case FAULT_STEP_NO8:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,7);
			fault_deal.step=FAULT_STEP_NO9;
			break;
		}
		
		case FAULT_STEP_NO9://延时等待
		{
			fault_deal.step=FAULT_STEP_NO15;
			break;
		}
		
		case FAULT_STEP_NO15://延时等待
		{
			fault_deal.step=FAULT_STEP_NO16;
			break;
		}
		
		case FAULT_STEP_NO16://延时等待
		{
			fault_deal.step=FAULT_STEP_NO10;
			break;
		}
		
		case FAULT_STEP_NO10:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,8);
			fault_deal.step=FAULT_STEP_NO11;
			break;
		}
		
		case FAULT_STEP_NO11:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,9);
			fault_deal.step=FAULT_STEP_NO12;
			break;
		}
		
		case FAULT_STEP_NO12:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,10);
			fault_deal.step=FAULT_STEP_NO13;
			break;
		}
		
		case FAULT_STEP_NO13:
		{
			TGTHT510_faultdeal_supply_tank_pipe_leak_dealing(tank_leak,11);
			fault_deal.step=FAULT_STEP_NO14;
			break;
		}
		
		case FAULT_STEP_NO14:
		{
			//补加管路温度控温点设置为低，待补充！！！！
			fault_deal.step=FAULT_STEP_END;
			break;
		}
		
		case FAULT_STEP_END:
		{
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**名称：补加故障处理模块--吹除口温度异常
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_interface_temperature_dealing(uint16 interface,uint16 number)
{
	if(interface==FAULT_INTERFACE_O)
	{
		switch(number)
		{
			case 1:
			{
				TGTHT510_faultdeal_lvb_set(LVb69G);
				break;
			}
			
			case 2:
			{
				TGTHT510_faultdeal_lvb_set(LVb73G);
				break;
			}
			
			case 3:
			{
				TGTHT510_faultdeal_lvb_set(LVb67G);
				break;
			}
			
			case 4:
			{
				TGTHT510_faultdeal_lvb_set(LVb77G);
				break;
			}
			
			case 5:
			{
				TGTHT510_faultdeal_lvb_set(LVb71G);
				break;
			}
			
			case 6:
			{
				TGTHT510_faultdeal_lvb_set(LVb75G);
				break;
			}
			
			case 7:
			{
				TGTHT510_faultdeal_lvb_set(LVb79G);
				break;
			}
			
			case 8:
			{
				TGTHT510_faultdeal_lvb_set(LVb81G);
				break;
			}
			
			case 9:
			{
				TGTHT510_faultdeal_lvb_set(LVb83G);
				break;
			}
			
			case 10:
			{
				TGTHT510_faultdeal_lvb_set(LVb85G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
	else if(interface==FAULT_INTERFACE_F)
	{
		switch(number)
		{
			case 1:
			{
				TGTHT510_faultdeal_lvb_set(LVb70G);
				break;
			}
			
			case 2:
			{
				TGTHT510_faultdeal_lvb_set(LVb74G);
				break;
			}
			
			case 3:
			{
				TGTHT510_faultdeal_lvb_set(LVb68G);
				break;
			}
			
			case 4:
			{
				TGTHT510_faultdeal_lvb_set(LVb78G);
				break;
			}
			
			case 5:
			{
				TGTHT510_faultdeal_lvb_set(LVb72G);
				break;
			}
			
			case 6:
			{
				TGTHT510_faultdeal_lvb_set(LVb76G);
				break;
			}
			
			case 7:
			{
				TGTHT510_faultdeal_lvb_set(LVb80G);
				break;
			}
			
			case 8:
			{
				TGTHT510_faultdeal_lvb_set(LVb82G);
				break;
			}
			
			case 9:
			{
				TGTHT510_faultdeal_lvb_set(LVb84G);
				break;
			}
			
			case 10:
			{
				TGTHT510_faultdeal_lvb_set(LVb86G);
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



/******************************************************************************************
**名称：补加故障处理模块--吹除口温度异常
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_interface_temperature(uint16 interface)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,1);
			fault_deal.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,2);
			fault_deal.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,3);
			fault_deal.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,4);
			fault_deal.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,5);
			fault_deal.step=FAULT_STEP_NO6;
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,6);
			fault_deal.step=FAULT_STEP_NO7;
			break;
		}
		
		case FAULT_STEP_NO7:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,7);
			fault_deal.step=FAULT_STEP_NO8;
			break;
		}
		
		case FAULT_STEP_NO8:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,8);
			fault_deal.step=FAULT_STEP_NO9;
			break;
		}
		
		case FAULT_STEP_NO9:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,9);
			fault_deal.step=FAULT_STEP_NO10;
			break;
		}
		
		case FAULT_STEP_NO10:
		{
			TGTHT510_faultdeal_supply_interface_temperature_dealing(interface,10);
			fault_deal.step=FAULT_STEP_END;
			break;
		}
		
		case FAULT_STEP_END:
		{
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**名称：补加故障检测模块--补加管路内漏
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_in_leak(uint16 leak_kind)
{
	uint16 temp;
	
	if(leak_kind==FAULT_IN_LEAK_O_Z)//氧主补加管路内漏
	{
		temp=TGTHT510_supply_decode_par.interface_O;
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O1;
		
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK1);
		
		TGTHT510_supply_decode_par.interface_O=temp;
	}
	
	else if(leak_kind==FAULT_IN_LEAK_O_B)//氧备补加管路内漏
	{
		temp=TGTHT510_supply_decode_par.interface_O;
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O2;
		
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK1);
		
		TGTHT510_supply_decode_par.interface_O=temp;
	}
	
	else if(leak_kind==FAULT_IN_LEAK_F_Z)//燃主补加管路内漏
	{
		temp=TGTHT510_supply_decode_par.interface_F;
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R1;
		
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK1);
		
		TGTHT510_supply_decode_par.interface_F=temp;
	}
	
	else if(leak_kind==FAULT_IN_LEAK_F_B)//燃备补加管路内漏
	{
		temp=TGTHT510_supply_decode_par.interface_F;
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R2;
		
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK1);
		
		TGTHT510_supply_decode_par.interface_F=temp;
	}
	
	else
	{
		asm("nop;");
	}
	
}

/******************************************************************************************
**名称：补加故障处理模块--浮动断接器温度异常
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_temperature_dealing(uint16 temperature_kind,uint16 number)
{
	//前向燃1浮动断接器温度异常，或者后向燃1浮动断接器温度异常
	if((temperature_kind==FAULT_TEMPERATURE_FORE_F1)||(temperature_kind==FAULT_TEMPERATURE_BACK_F1))
	{
		switch(number)
		{
			case 1:
			{
				TGTHT510_faultdeal_lvb_set(LVb40G);
				break;
			}
			
			case 2:
			{
				TGTHT510_faultdeal_lvb_set(LVb64G);
				break;
			}
			
			case 3:
			{
				TGTHT510_faultdeal_lvb_set(LVb44G);
				break;
			}
			
			case 4:
			{
				TGTHT510_faultdeal_lvb_set(LVb46G);
				break;
			}
			
			case 5:
			{
				TGTHT510_faultdeal_lvb_set(LVb48G);
				break;
			}
			
			case 6:
			{
				TGTHT510_faultdeal_lvb_set(LVb72K);
				break;
			}
			
			case 7:
			{
				TGTHT510_faultdeal_lvb_set(LVb80K);
				break;
			}
			
			case 8:
			{
				TGTHT510_faultdeal_lvb_set(LVb72G);
				break;
			}
			
			case 9:
			{
				TGTHT510_faultdeal_lvb_set(LVb80G);
				break;
			}
			
			case 10:
			{
				TGTHT510_faultdeal_lvb_set(LVb42G);
				break;
			}
			
			case 11:
			{
				TGTHT510_faultdeal_lvb_set(LVb66G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
	//前向燃2浮动断接器温度异常，或者后向燃2浮动断接器温度异常
	else if((temperature_kind==FAULT_TEMPERATURE_FORE_F2)||(temperature_kind==FAULT_TEMPERATURE_BACK_F2))
	{
		switch(number)
		{
			case 1:
			{
				TGTHT510_faultdeal_lvb_set(LVb50G);
				break;
			}
			
			case 2:
			{
				TGTHT510_faultdeal_lvb_set(LVb60G);
				break;
			}
			
			case 3:
			{
				TGTHT510_faultdeal_lvb_set(LVb54G);
				break;
			}
			
			case 4:
			{
				TGTHT510_faultdeal_lvb_set(LVb56G);
				break;
			}
			
			case 5:
			{
				TGTHT510_faultdeal_lvb_set(LVb58G);
				break;
			}
			
			case 6:
			{
				TGTHT510_faultdeal_lvb_set(LVb68K);
				break;
			}
			
			case 7:
			{
				TGTHT510_faultdeal_lvb_set(LVb86K);
				break;
			}
			
			case 8:
			{
				TGTHT510_faultdeal_lvb_set(LVb68G);
				break;
			}
			
			case 9:
			{
				TGTHT510_faultdeal_lvb_set(LVb86G);
				break;
			}
			
			case 10:
			{
				TGTHT510_faultdeal_lvb_set(LVb52G);
				break;
			}
			
			case 11:
			{
				TGTHT510_faultdeal_lvb_set(LVb62G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
	//前向氧1浮动断接器温度异常，或者后向氧1浮动断接器温度异常
	else if((temperature_kind==FAULT_TEMPERATURE_FORE_O1)||(temperature_kind==FAULT_TEMPERATURE_BACK_O1))
	{
		switch(number)
		{
			case 1:
			{
				TGTHT510_faultdeal_lvb_set(LVb39G);
				break;
			}
			
			case 2:
			{
				TGTHT510_faultdeal_lvb_set(LVb63G);
				break;
			}
			
			case 3:
			{
				TGTHT510_faultdeal_lvb_set(LVb43G);
				break;
			}
			
			case 4:
			{
				TGTHT510_faultdeal_lvb_set(LVb45G);
				break;
			}
			
			case 5:
			{
				TGTHT510_faultdeal_lvb_set(LVb47G);
				break;
			}
			
			case 6:
			{
				TGTHT510_faultdeal_lvb_set(LVb71K);
				break;
			}
			
			case 7:
			{
				TGTHT510_faultdeal_lvb_set(LVb79K);
				break;
			}
			
			case 8:
			{
				TGTHT510_faultdeal_lvb_set(LVb71G);
				break;
			}
			
			case 9:
			{
				TGTHT510_faultdeal_lvb_set(LVb79G);
				break;
			}
			
			case 10:
			{
				TGTHT510_faultdeal_lvb_set(LVb41G);
				break;
			}
			
			case 11:
			{
				TGTHT510_faultdeal_lvb_set(LVb65G);
				break;
			}
			
			default:
			{
				break;
			}
			
		}
		
	}
	
	//前向氧2浮动断接器温度异常，或者后向氧2浮动断接器温度异常
	else if((temperature_kind==FAULT_TEMPERATURE_FORE_O2)||(temperature_kind==FAULT_TEMPERATURE_BACK_O2))
	{
		switch(number)
		{
			case 1:
			{
				TGTHT510_faultdeal_lvb_set(LVb49G);
				break;
			}
			
			case 2:
			{
				TGTHT510_faultdeal_lvb_set(LVb59G);
				break;
			}
			
			case 3:
			{
				TGTHT510_faultdeal_lvb_set(LVb53G);
				break;
			}
			
			case 4:
			{
				TGTHT510_faultdeal_lvb_set(LVb55G);
				break;
			}
			
			case 5:
			{
				TGTHT510_faultdeal_lvb_set(LVb57G);
				break;
			}
			
			case 6:
			{
				TGTHT510_faultdeal_lvb_set(LVb67K);
				break;
			}
			
			case 7:
			{
				TGTHT510_faultdeal_lvb_set(LVb85K);
				break;
			}
			
			case 8:
			{
				TGTHT510_faultdeal_lvb_set(LVb67G);
				break;
			}
			
			case 9:
			{
				TGTHT510_faultdeal_lvb_set(LVb85G);
				break;
			}
			
			case 10:
			{
				TGTHT510_faultdeal_lvb_set(LVb51G);
				break;
			}
			
			case 11:
			{
				TGTHT510_faultdeal_lvb_set(LVb61G);
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

/******************************************************************************************
**名称：补加故障处理模块--浮动断接器温度异常
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_temperature(uint16 temperature_kind)
{
	switch(fault_deal.step)
	{
		case FAULT_STEP_START:
		{
			fault_deal.step=FAULT_STEP_NO1;
			break;
		}
		
		case FAULT_STEP_NO1:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,1);
			fault_deal.step=FAULT_STEP_NO2;
			break;
		}
		
		case FAULT_STEP_NO2:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,2);
			fault_deal.step=FAULT_STEP_NO3;
			break;
		}
		
		case FAULT_STEP_NO3:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,3);
			fault_deal.step=FAULT_STEP_NO4;
			break;
		}
		
		case FAULT_STEP_NO4:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,4);
			fault_deal.step=FAULT_STEP_NO5;
			break;
		}
		
		case FAULT_STEP_NO5:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,5);
			fault_deal.step=FAULT_STEP_NO6;
			break;
		}
		
		case FAULT_STEP_NO6:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,6);
			fault_deal.step=FAULT_STEP_NO7;
			break;
		}
		
		case FAULT_STEP_NO7:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,7);
			fault_deal.step=FAULT_STEP_NO19;
			break;
		}
		
		case FAULT_STEP_NO19:
		{
			fault_deal.step=FAULT_STEP_NO20;
			break;
			
		}
		
		case FAULT_STEP_NO20:
		{
			fault_deal.step=FAULT_STEP_NO8;
			break;
			
		}
		
		case FAULT_STEP_NO8:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,8);
			fault_deal.step=FAULT_STEP_NO9;
			break;
		}
		
		case FAULT_STEP_NO9:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,9);
			fault_deal.step=FAULT_STEP_NO10;
			break;
		}
		
		case FAULT_STEP_NO10:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,10);
			fault_deal.step=FAULT_STEP_NO11;
			break;
		}
		
		case FAULT_STEP_NO11:
		{
			TGTHT510_faultdeal_supply_temperature_dealing(temperature_kind,11);
			
			
			fault_deal.step=FAULT_STEP_END;
			break;
		}
		
		case FAULT_STEP_END:
		{
			fault_deal.fault_mode=FAULT_MODE_NONE;
			fault_deal.step=FAULT_STEP_NONE;
			
			break;
		}
		
		default:
		{
			break;
		}
		
	}
	
}

/******************************************************************************************
**名称：补加故障处理模块--贮箱卡滞
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdeal_supply_ka_tank(uint16 ka)
{
	if(ka==FAULT_O_TANK1)//氧1贮箱卡滞
	{
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK1);
	}
	
	else if(ka==FAULT_O_TANK2)//氧2贮箱卡滞
	{
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK2);
	}
	
	else if(ka==FAULT_O_TANK3)//氧3贮箱卡滞
	{
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_O_TANK3);
	}
	
	else if(ka==FAULT_F_TANK1)//燃1贮箱卡滞
	{
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK1);
	}
	
	else if(ka==FAULT_F_TANK2)//燃2贮箱卡滞
	{
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK2);
	}
	
	else if(ka==FAULT_F_TANK3)//燃3贮箱卡滞
	{
		TGTHT510_faultdeal_supply_tank_pipe_leak(FAULT_F_TANK3);
	}
	
	else
	{
		asm("nop;");
	}

}



/******************************************************************************************
**名称： 发射段 ---推进故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_launch(void)
{

	//氧气瓶1泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,DISABLE);
	
	//氧气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,DISABLE);
	
	//氧气瓶3泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,DISABLE);
	
	//燃气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,DISABLE);
	
	//燃气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,DISABLE);
	
	//燃气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,DISABLE);
	
	//氧1贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,ENABLE);
	
	//氧2贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,ENABLE);
	
	//氧3贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,ENABLE);
	
	//燃1贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,ENABLE);
	
	//燃2贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,ENABLE);
	
	//燃3贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,ENABLE);
	
	//主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_main_valve_leak.faultdiagnosis_count=0;
	
	//备份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_less_valve_leak.faultdiagnosis_count=0;
	
	//C组姿控发动机控制阀门泄漏
	TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_C_all_valve_leak.faultdiagnosis_count=0;
	
	//A组主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_main_valve_leak.faultdiagnosis_count=0;
	
	//A组备份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_less_valve_leak.faultdiagnosis_count=0;
	
	//氧1贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,DISABLE);
	
	//氧2贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,DISABLE);
	
	//氧3贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,DISABLE);
	
	//燃1贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,DISABLE);
	
	//燃2贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,DISABLE);
	
	//燃3贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,DISABLE);
	
}


/******************************************************************************************
**名称： 变轨段 ---推进故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_orbit(void)
{
	TGTHT510_faultdiagnosis_push_set_stage_launch();
}


/******************************************************************************************
**名称： 巡检段 ---推进故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_polling(void)
{
	//氧气瓶1泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,ENABLE);
	
	//氧气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,ENABLE);
	
	//氧气瓶3泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,ENABLE);
	
	//燃气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,ENABLE);
	
	//燃气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,ENABLE);
	
	//燃气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,ENABLE);
	
	//氧1贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,ENABLE);
	
	//氧2贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,ENABLE);
	
	//氧3贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,ENABLE);
	
	//燃1贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,ENABLE);
	
	//燃2贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,ENABLE);
	
	//燃3贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,ENABLE);
	
	//主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_main_valve_leak.faultdiagnosis_count=0;
	
	//备份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_less_valve_leak.faultdiagnosis_count=0;
	
	//C组姿控发动机控制阀门泄漏
	TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_C_all_valve_leak.faultdiagnosis_count=0;
	
	//A组主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_main_valve_leak.faultdiagnosis_count=0;
	
	//A组备份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_less_valve_leak.faultdiagnosis_count=0;
	
	//氧1贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,ENABLE);
	
	//氧2贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,ENABLE);
	
	//氧3贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,ENABLE);
	
	//燃1贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,ENABLE);
	
	//燃2贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,ENABLE);
	
	//燃3贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,ENABLE);
	
}

/******************************************************************************************
**名称： 压气机补气段 ---推进故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_gas(void)
{
	TGTHT510_faultdiagnosis_push_set_stage_polling();
}

/******************************************************************************************
**名称： 补加抽气段 ---推进故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_comp(void)
{
	if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)||\
	(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)||\
	(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1))
	{
		//燃1贮箱超压	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,DISABLE);
		
		//燃1贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,DISABLE);
	}
	
	else
	{
		//燃1贮箱超压	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,ENABLE);
		
		//燃1贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)||\
	(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)||\
	(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2))
	{
		//燃2贮箱超压	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,DISABLE);
		
		//燃2贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,DISABLE);
	}
	
	else
	{
		//燃2贮箱超压	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,ENABLE);
		
		//燃2贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)||\
	(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)||\
	(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3))
	{
		//燃3贮箱超压	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,DISABLE);
		
		//燃3贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,DISABLE);
	}
	
	else
	{
		//燃3贮箱超压	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,ENABLE);
		
		//燃3贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)||\
	(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)||\
	(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1))
	{
		//氧1贮箱超压	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,DISABLE);
		
		//氧1贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,DISABLE);
	}
	
	else
	{
		//氧1贮箱超压	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,ENABLE);
		
		//氧1贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)||\
	(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)||\
	(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2))
	{
		//氧2贮箱超压	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,DISABLE);
		
		//氧2贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,DISABLE);
	}
	
	else
	{
		//氧2贮箱超压	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,ENABLE);
		
		//氧2贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)||\
	(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)||\
	(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3))
	{
		//氧3贮箱超压	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,DISABLE);
		
		//氧3贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,DISABLE);
	}
	
	else
	{
		//氧3贮箱超压	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,ENABLE);
		
		//氧3贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_gas_tank_F1==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F1==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F2==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F2==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F3==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F3==DECODE_GAS_F1))
	{
		//燃气瓶1泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,DISABLE);
	}
	
	else
	{
		//燃气瓶1泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_gas_tank_F1==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F1==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F2==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F2==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F3==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F3==DECODE_GAS_F2))
	{
		//燃气瓶2泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,DISABLE);
	}
	
	else
	{
		//燃气瓶2泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_gas_tank_F1==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F1==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F2==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F2==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F3==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F3==DECODE_GAS_F3))
	{
		//燃气瓶3泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,DISABLE);
	}
	
	else
	{
		//燃气瓶3泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_gas_tank_O1==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O1==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O2==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O2==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O3==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O3==DECODE_GAS_O1))
	{
		//氧气瓶1泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,DISABLE);
	}
	
	else
	{
		//氧气瓶1泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_gas_tank_O1==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O1==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O2==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O2==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O3==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O3==DECODE_GAS_O2))
	{
		//氧气瓶2泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,DISABLE);
	}
	
	else
	{
		//氧气瓶2泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_gas_tank_O1==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O1==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O2==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O2==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O3==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O3==DECODE_GAS_O3))
	{
		//氧气瓶3泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,DISABLE);
	}
	
	else
	{
		//氧气瓶3泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,ENABLE);
	}
	
	
	//主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_main_valve_leak.faultdiagnosis_count=0;
	
	//备份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_less_valve_leak.faultdiagnosis_count=0;
	
	//C组姿控发动机控制阀门泄漏
	TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_C_all_valve_leak.faultdiagnosis_count=0;
	
	//A组主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_main_valve_leak.faultdiagnosis_count=0;
	
	//A组备份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_less_valve_leak.faultdiagnosis_count=0;
	
}


/******************************************************************************************
**名称： 补加流动段 ---推进故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_flow(void)
{
	//氧气瓶1泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,ENABLE);
	
	//氧气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,ENABLE);
	
	//氧气瓶3泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,ENABLE);
	
	//燃气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,ENABLE);
	
	//燃气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,ENABLE);
	
	//燃气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,ENABLE);
	
	//氧1贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,ENABLE);
	
	//氧2贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,ENABLE);
	
	//氧3贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,ENABLE);
	
	//燃1贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,ENABLE);
	
	//燃2贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,ENABLE);
	
	//燃3贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,ENABLE);
	
	//主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_main_valve_leak.faultdiagnosis_count=0;
	
	//备份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_less_valve_leak.faultdiagnosis_count=0;
	
	//C组姿控发动机控制阀门泄漏
	TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_C_all_valve_leak.faultdiagnosis_count=0;
	
	//A组主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_main_valve_leak.faultdiagnosis_count=0;
	
	//A组备份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_less_valve_leak.faultdiagnosis_count=0;
	
	
	
	if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F1)||\
	(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F1)||\
	(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1))
	{
		//燃1贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,DISABLE);
	}
	
	else
	{
		//燃1贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F2)||\
	(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F2)||\
	(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2))
	{
		//燃2贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,DISABLE);
	}
	
	else
	{
		//燃2贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_tank_F==DECODE_TANK_F3)||\
	(TGTHT510_supply_decode_par.second_tank_F==DECODE_TANK_F3)||\
	(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3))
	{
		//燃3贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,DISABLE);
	}
	
	else
	{
		//燃3贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)||\
	(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)||\
	(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1))
	{
		//氧1贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,DISABLE);
	}
	
	else
	{
		//氧1贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)||\
	(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)||\
	(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2))
	{
		//氧2贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,DISABLE);
	}
	
	else
	{
		//氧2贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)||\
	(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)||\
	(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3))
	{
		//氧3贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,DISABLE);
	}
	
	else
	{
		//氧3贮箱泄漏	
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,ENABLE);
	}
	
	
}


/******************************************************************************************
**名称： 补加复压段 ---推进故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_repre(void)
{
	if((TGTHT510_supply_decode_par.first_gas_tank_F1==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F1==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F2==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F2==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F3==DECODE_GAS_F1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F3==DECODE_GAS_F1))
	{
		//燃气瓶1泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,DISABLE);
	}
	
	else
	{
		//燃气瓶1泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas1_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_gas_tank_F1==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F1==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F2==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F2==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F3==DECODE_GAS_F2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F3==DECODE_GAS_F2))
	{
		//燃气瓶2泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,DISABLE);
	}
	
	else
	{
		//燃气瓶2泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas2_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_gas_tank_F1==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F1==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F2==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F2==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_F3==DECODE_GAS_F3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_F3==DECODE_GAS_F3))
	{
		//燃气瓶3泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,DISABLE);
	}
	
	else
	{
		//燃气瓶3泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_gas3_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_gas_tank_O1==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O1==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O2==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O2==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O3==DECODE_GAS_O1)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O3==DECODE_GAS_O1))
	{
		//氧气瓶1泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,DISABLE);
	}
	
	else
	{
		//氧气瓶1泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas1_leak,ENABLE);
	}
	
	
	if((TGTHT510_supply_decode_par.first_gas_tank_O1==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O1==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O2==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O2==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O3==DECODE_GAS_O2)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O3==DECODE_GAS_O2))
	{
		//氧气瓶2泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,DISABLE);
	}
	
	else
	{
		//氧气瓶2泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas2_leak,ENABLE);
	}
	
	if((TGTHT510_supply_decode_par.first_gas_tank_O1==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O1==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O2==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O2==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.first_gas_tank_O3==DECODE_GAS_O3)||\
	(TGTHT510_supply_decode_par.second_gas_tank_O3==DECODE_GAS_O3))
	{
		//氧气瓶3泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,DISABLE);
	}
	
	else
	{
		//氧气瓶3泄漏
		TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_gas3_leak,ENABLE);
	}
	
	
	//氧1贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_overpressure,ENABLE);
	
	//氧2贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_overpressure,ENABLE);
	
	//氧3贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_overpressure,ENABLE);
	
	//燃1贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_overpressure,ENABLE);
	
	//燃2贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_overpressure,ENABLE);
	
	//燃3贮箱超压	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_overpressure,ENABLE);
	
	//主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_B_main_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_B_main_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_B_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_B_main_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_main_valve_leak.faultdiagnosis_count=0;
	
	//备份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_B_less_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_B_less_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_B_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_B_less_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_B_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_B_less_valve_leak.faultdiagnosis_count=0;
	
	//C组姿控发动机控制阀门泄漏
	TGTHT510_fault_push_C_all_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_C_all_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_C_all_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_C_all_valve_leak.step=FAULT_STEP_START;							//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_C_all_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_C_all_valve_leak.faultdiagnosis_count=0;
	
	//A组主份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_main_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_A_main_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_A_main_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_A_main_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_main_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_main_valve_leak.faultdiagnosis_count=0;
	
	//A组备份姿控发动机控制阀门泄漏
	TGTHT510_fault_push_A_less_valve_leak.state=ENABLE;									//故检不使能
	TGTHT510_fault_push_A_less_valve_leak.result=FALSE;									//故障未发生
	TGTHT510_fault_push_A_less_valve_leak.strategy_step=FAULT_STRATEGY_STEP_NONE;		//故障策略步骤无
	TGTHT510_fault_push_A_less_valve_leak.step=FAULT_STEP_START;						//启动故检
	TGTHT510_faultdiagnosis_push_CG_set(TGTHT510_fault_push_A_less_valve_leak.mode,FAULT_STATE_DISABLE);
	TGTHT510_fault_push_A_less_valve_leak.faultdiagnosis_count=0;
	
	//氧1贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank1_leak,ENABLE);
	
	//氧2贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank2_leak,ENABLE);
	
	//氧3贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_o_tank3_leak,ENABLE);
	
	//燃1贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank1_leak,ENABLE);
	
	//燃2贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank2_leak,ENABLE);
	
	//燃3贮箱泄漏	
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_push_f_tank3_leak,ENABLE);
	
	
}


/******************************************************************************************
**名称： 补加其他段 ---推进故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_other(void)
{
	TGTHT510_faultdiagnosis_push_set_stage_polling();
}


/******************************************************************************************
**名称： 运行段 ---推进故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_push_set_stage_run(void)
{
	TGTHT510_faultdiagnosis_push_set_stage_polling();
}


/******************************************************************************************
**名称： 发射段 ---补加故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_launch(void)
{
	//电机驱动器故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,DISABLE);
	
	//主份液冷主泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,DISABLE);
	
	//主份液冷备泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,DISABLE);
	
	//备份液冷主泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,DISABLE);
	
	//备份液冷备泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,DISABLE);
	
	//主份液冷泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,DISABLE);
	
	//备份液冷泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,DISABLE);
	
	//压气机A入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,DISABLE);
	
	//压气机B入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,DISABLE);
	
	//压气机C入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,DISABLE);
	
	//压气机A电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,DISABLE);
	
	//压气机B电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,DISABLE);
	
	//压气机C电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,DISABLE);
	
	//压气机A超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,DISABLE);
	
	//压气机B超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,DISABLE);
	
	//压气机C超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,DISABLE);
	
	//氧1补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,DISABLE);
	
	//氧2补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,DISABLE);
	
	//氧3补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,DISABLE);
	
	//燃1补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,DISABLE);
	
	//燃2补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,DISABLE);
	
	//燃3补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,DISABLE);
	
	//压气机A膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,DISABLE);
	
	//压气机B膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,DISABLE);
	
	//压气机C膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,DISABLE);
	
	//氧气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,DISABLE);
	
	//氧气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,DISABLE);
	
	//氧气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,DISABLE);
	
	//燃气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,DISABLE);
	
	//燃气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,DISABLE);
	
	//燃气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,DISABLE);
	
	//氧1贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,DISABLE);
	
	//氧2贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,DISABLE);
	
	//氧3贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,DISABLE);
	
	//燃1贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,DISABLE);
	
	//燃2贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,DISABLE);
	
	//燃3贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,DISABLE);
	
	//氧吹除口温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,DISABLE);
	
	//燃吹除口温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,DISABLE);
	
	//氧主补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,DISABLE);
	
	//氧备补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,DISABLE);
	
	//燃主补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,DISABLE);
	
	//燃备补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,DISABLE);
	
	//前向燃1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,DISABLE);
	
	//前向燃2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,DISABLE);
	
	//前向氧1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,DISABLE);
	
	//前向氧2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,DISABLE);
	
	//后向燃1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,DISABLE);
	
	//后向燃2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,DISABLE);
	
	//后向氧1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,DISABLE);
	
	//后向氧2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,DISABLE);
	
	//氧1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,DISABLE);
	
	//氧2贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,DISABLE);
	
	//氧3贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,DISABLE);
	
	
}


/******************************************************************************************
**名称： 变轨段 ---补加故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_orbit(void)
{
	TGTHT510_faultdiagnosis_supply_set_stage_launch();
}


/******************************************************************************************
**名称： 巡检段 ---补加故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_polling(void)
{
	//电机驱动器故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,ENABLE);
	
	//主份液冷主泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,ENABLE);
	
	//主份液冷备泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,ENABLE);
	
	//备份液冷主泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,ENABLE);
	
	//备份液冷备泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,ENABLE);
	
	//主份液冷泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,DISABLE);
	
	//备份液冷泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,DISABLE);
	
	//压气机A入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,ENABLE);
	
	//压气机B入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,ENABLE);
	
	//压气机C入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,ENABLE);
	
	//压气机A电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,DISABLE);
	
	//压气机B电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,DISABLE);
	
	//压气机C电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,DISABLE);
	
	//压气机A超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,ENABLE);
	
	//压气机B超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,ENABLE);
	
	//压气机C超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,ENABLE);
	
	//氧1补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,DISABLE);
	
	//氧2补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,DISABLE);
	
	//氧3补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,DISABLE);
	
	//燃1补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,DISABLE);
	
	//燃2补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,DISABLE);
	
	//燃3补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,DISABLE);
	
	//压气机A膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,DISABLE);
	
	//压气机B膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,DISABLE);
	
	//压气机C膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,DISABLE);
	
	//氧气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,DISABLE);
	
	//氧气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,DISABLE);
	
	//氧气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,DISABLE);
	
	//燃气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,DISABLE);
	
	//燃气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,DISABLE);
	
	//燃气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,DISABLE);
	
	//氧1贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,DISABLE);
	
	//氧2贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,DISABLE);
	
	//氧3贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,DISABLE);
	
	//燃1贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,DISABLE);
	
	//燃2贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,DISABLE);
	
	//燃3贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,DISABLE);
	
	//氧吹除口温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,DISABLE);
	
	//燃吹除口温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,DISABLE);
	
	//氧主补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,DISABLE);
	
	//氧备补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,DISABLE);
	
	//燃主补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,DISABLE);
	
	//燃备补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,DISABLE);
	
	//前向燃1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,DISABLE);
	
	//前向燃2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,DISABLE);
	
	//前向氧1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,DISABLE);
	
	//前向氧2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,DISABLE);
	
	//后向燃1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,DISABLE);
	
	//后向燃2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,DISABLE);
	
	//后向氧1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,DISABLE);
	
	//后向氧2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,DISABLE);
	
	//氧1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,DISABLE);
	
	//氧2贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,DISABLE);
	
	//氧3贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,DISABLE);
	
	
}


/******************************************************************************************
**名称： 压气机补气段 ---补加故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_gas(void)
{
	//电机驱动器故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,DISABLE);
	
	//主份液冷主泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,DISABLE);
	
	//主份液冷备泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,DISABLE);
	
	//备份液冷主泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,DISABLE);
	
	//备份液冷备泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,DISABLE);
	
	//主份液冷泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,DISABLE);
	
	//备份液冷泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,DISABLE);
	
	//压气机A入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,ENABLE);
	
	//压气机B入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,ENABLE);
	
	//压气机C入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,ENABLE);
	
	//压气机A电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,DISABLE);
	
	//压气机B电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,DISABLE);
	
	//压气机C电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,DISABLE);
	
	//压气机A超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,DISABLE);
	
	//压气机B超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,DISABLE);
	
	//压气机C超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,DISABLE);
	
	//氧1补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,DISABLE);
	
	//氧2补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,DISABLE);
	
	//氧3补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,DISABLE);
	
	//燃1补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,DISABLE);
	
	//燃2补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,DISABLE);
	
	//燃3补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,DISABLE);
	
	//压气机A膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,DISABLE);
	
	//压气机B膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,DISABLE);
	
	//压气机C膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,DISABLE);
	
	//氧气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,DISABLE);
	
	//氧气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,DISABLE);
	
	//氧气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,DISABLE);
	
	//燃气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,DISABLE);
	
	//燃气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,DISABLE);
	
	//燃气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,DISABLE);
	
	//氧1贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,DISABLE);
	
	//氧2贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,DISABLE);
	
	//氧3贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,DISABLE);
	
	//燃1贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,DISABLE);
	
	//燃2贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,DISABLE);
	
	//燃3贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,DISABLE);
	
	//氧吹除口温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,DISABLE);
	
	//燃吹除口温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,DISABLE);
	
	//氧主补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,DISABLE);
	
	//氧备补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,DISABLE);
	
	//燃主补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,DISABLE);
	
	//燃备补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,DISABLE);
	
	//前向燃1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,DISABLE);
	
	//前向燃2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,DISABLE);
	
	//前向氧1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,DISABLE);
	
	//前向氧2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,DISABLE);
	
	//后向燃1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,DISABLE);
	
	//后向燃2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,DISABLE);
	
	//后向氧1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,DISABLE);
	
	//后向氧2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,DISABLE);
	
	//氧1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,DISABLE);
	
	//氧2贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,DISABLE);
	
	//氧3贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,DISABLE);
	
	
}


/******************************************************************************************
**名称： 补加抽气段 ---补加故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_comp(void)
{
	//电机驱动器故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,ENABLE);
	
	//主份液冷主泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,ENABLE);
	
	//主份液冷备泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,ENABLE);
	
	//备份液冷主泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,ENABLE);
	
	//备份液冷备泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,ENABLE);
	
	//主份液冷泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,DISABLE);
	
	//备份液冷泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,DISABLE);
	
	//压气机A入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,ENABLE);
	
	//压气机B入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,ENABLE);
	
	//压气机C入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,ENABLE);
	
	//压气机A电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,DISABLE);
	
	//压气机B电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,DISABLE);
	
	//压气机C电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,DISABLE);
	
	//压气机A超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,ENABLE);
	
	//压气机B超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,ENABLE);
	
	//压气机C超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,ENABLE);
	
	//氧1补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,ENABLE);
	
	//氧2补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,ENABLE);
	
	//氧3补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,ENABLE);
	
	//燃1补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,ENABLE);
	
	//燃2补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,ENABLE);
	
	//燃3补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,ENABLE);
	
	//压气机A膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,ENABLE);
	
	//压气机B膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,ENABLE);
	
	//压气机C膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,ENABLE);
	
	//氧气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,ENABLE);
	
	//氧气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,ENABLE);
	
	//氧气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,ENABLE);
	
	//燃气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,ENABLE);
	
	//燃气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,ENABLE);
	
	//燃气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,ENABLE);
	
	//氧1贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,DISABLE);
	
	//氧2贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,DISABLE);
	
	//氧3贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,DISABLE);
	
	//燃1贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,DISABLE);
	
	//燃2贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,DISABLE);
	
	//燃3贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,DISABLE);
	
	//氧吹除口温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,DISABLE);
	
	//燃吹除口温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,DISABLE);
	
	//氧主补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,DISABLE);
	
	//氧备补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,DISABLE);
	
	//燃主补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,DISABLE);
	
	//燃备补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,DISABLE);
	
	//前向燃1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,DISABLE);
	
	//前向燃2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,DISABLE);
	
	//前向氧1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,DISABLE);
	
	//前向氧2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,DISABLE);
	
	//后向燃1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,DISABLE);
	
	//后向燃2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,DISABLE);
	
	//后向氧1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,DISABLE);
	
	//后向氧2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,DISABLE);
	
	//氧1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,DISABLE);
	
	//氧2贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,DISABLE);
	
	//氧3贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,DISABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,DISABLE);
	
	
}


/******************************************************************************************
**名称： 补加流动段 ---补加故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_flow(void)
{
	//电机驱动器故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_TGTHT530,DISABLE);
	
	//主份液冷主泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zz,DISABLE);
	
	//主份液冷备泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_zb,DISABLE);
	
	//备份液冷主泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bz,DISABLE);
	
	//备份液冷备泵故障
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_cooler_bb,DISABLE);
	
	//主份液冷泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_z,DISABLE);
	
	//备份液冷泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_leak_cooler_b,DISABLE);
	
	//压气机A入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_in_over,DISABLE);
	
	//压气机B入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_in_over,DISABLE);
	
	//压气机C入口超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_in_over,DISABLE);
	
	//压气机A电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_motor_over,DISABLE);
	
	//压气机B电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_motor_over,DISABLE);
	
	//压气机C电机腔超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_motor_over,DISABLE);
	
	//压气机A超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_hot,DISABLE);
	
	//压气机B超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_hot,DISABLE);
	
	//压气机C超温
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_hot,DISABLE);
	
	//氧1补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank1_overpressure,DISABLE);
	
	//氧2补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank2_overpressure,DISABLE);
	
	//氧3补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_tank3_overpressure,DISABLE);
	
	//燃1补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank1_overpressure,DISABLE);
	
	//燃2补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank2_overpressure,DISABLE);
	
	//燃3补加贮箱超压
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_tank3_overpressure,DISABLE);
	
	//压气机A膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_A_break,DISABLE);
	
	//压气机B膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_B_break,DISABLE);
	
	//压气机C膜片破裂
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_compressor_C_break,DISABLE);
	
	//氧气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas1_leak,DISABLE);
	
	//氧气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas2_leak,DISABLE);
	
	//氧气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_o_gas3_leak,DISABLE);
	
	//燃气瓶1泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas1_leak,DISABLE);
	
	//燃气瓶2泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas2_leak,DISABLE);
	
	//燃气瓶3泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_f_gas3_leak,DISABLE);
	
	//氧1贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank1,ENABLE);
	
	//氧2贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank2,ENABLE);
	
	//氧3贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_o_tank3,ENABLE);
	
	//燃1贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank1,ENABLE);
	
	//燃2贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank2,ENABLE);
	
	//燃3贮箱补加液路泄漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_pipe_leak_f_tank3,ENABLE);
	
	//氧吹除口温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_o_temperature,ENABLE);
	
	//燃吹除口温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_interface_f_temperature,ENABLE);
	
	//氧主补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_z,ENABLE);
	
	//氧备补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_o_b,ENABLE);
	
	//燃主补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_z,ENABLE);
	
	//燃备补加管路内漏
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_in_leak_f_b,ENABLE);
	
	//前向燃1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f1,ENABLE);
	
	//前向燃2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_f2,ENABLE);
	
	//前向氧1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o1,ENABLE);
	
	//前向氧2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_fore_o2,ENABLE);
	
	//后向燃1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f1,ENABLE);
	
	//后向燃2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_f2,ENABLE);
	
	//后向氧1浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o1,ENABLE);
	
	//后向氧2浮动断接器温度异常
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_temperature_back_o2,ENABLE);
	
	//氧1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank1,ENABLE);
	
	//氧2贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank2,ENABLE);
	
	//氧3贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_o_tank3,ENABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank1,ENABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank2,ENABLE);
	
	//燃1贮箱卡滞
	TGTHT510_faultdiagnosis_initial(&TGTHT510_fault_supply_ka_f_tank3,ENABLE);
	
}

/******************************************************************************************
**名称： 补加复压段 ---补加故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_repre(void)
{
	TGTHT510_faultdiagnosis_supply_set_stage_launch();
}


/******************************************************************************************
**名称： 补加其他段 ---补加故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_other(void)
{
	TGTHT510_faultdiagnosis_supply_set_stage_launch();
}

/******************************************************************************************
**名称： 运行段 ---补加故检使能禁止设置
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_faultdiagnosis_supply_set_stage_run(void)
{
	TGTHT510_faultdiagnosis_supply_set_stage_launch();
}




















  
