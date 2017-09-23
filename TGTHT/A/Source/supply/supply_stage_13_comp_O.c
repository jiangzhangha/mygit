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

extern TGTHT510_supply_time_TypeDef TGTHT510_supply_time;

extern TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;

extern valvecontrol_TypeDef TGTHT510_valvecontrol_struct;	//阀门控制结构体
extern uint16 TGTHT510_1553B_data_TGTHT100[];				//全局数组，缓存推进遥测线路盒除温度参数以外数据，89字
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[];		//全局数组，缓存推进遥测线路盒复帧A温度数据，65字
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[];		//全局数组，缓存推进遥测线路盒复帧B温度数据，65字
extern uint16 TGTHT510_1553B_data_TGTHT530[];				//全局数组，缓存压气机电机驱动器遥测数据，14字
extern uint16 TGTHT510_1553B_data_TGTHT520a[];				//全局数组，缓存推进控制驱动器主机遥测，7字
extern uint16 TGTHT510_1553B_data_TGTHT520b[];				//全局数组，缓存推进控制驱动器备机遥测，7字
extern uint16 TGTHT510_1553B_R_HYCT1100[];					//全局数组，缓存货船发送的遥测数据

uint16 temp_global[10];//全部临时变量数组

/******************************************************************************************
**名称：补加阶段6
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_supply_stage13_comp_O_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_13_O_INIT_START_COOLER;
			
			break;
		}

//----------------------------------初始设置阶段------------------------------------------------------
		
		//启动液冷泵工作
		case STEP_13_O_INIT_START_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_start_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_IS_COOLER_WORK;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过转速判断液冷工作是否正常
		case STEP_13_O_INIT_IS_COOLER_WORK:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_is_cooler_work()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_DELAY;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待时间
		case STEP_13_O_INIT_DELAY:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机温度是否正常
		case STEP_13_O_INIT_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_TGTHT530_POWER_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请电机驱动器加电
		case STEP_13_O_INIT_TGTHT530_POWER_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_TGTHT530_power_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_COMPRESSOR_POWER_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请压气机加电
		case STEP_13_O_INIT_COMPRESSOR_POWER_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_compressor_power_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_ISOLATION;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//贮箱隔离
		case STEP_13_O_INIT_ISOLATION:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_isolation()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_INIT_NUMBER_COMP_TANK;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断抽气贮箱个数
		case STEP_13_O_INIT_NUMBER_COMP_TANK:
		{
			TGTHT510_supply_stage13_comp_O_init_step_number_comp_tank();
			
			break;
		}

//----------------------------------一个贮箱抽气------------------------------------------------------

		//开进贮箱低压气路补加阀门
		case STEP_13_O_1TANK_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_TIME_DELAY_A;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待时间
		case STEP_13_O_1TANK_TIME_DELAY_A:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断开进贮箱低压气路补加阀门
		case STEP_13_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_is_in_tank_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_IN_COMPRESSOR_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开氧压气机进口阀门
		case STEP_13_O_1TANK_IN_COMPRESSOR_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_in_compressor_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_TIME_DELAY1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay1
		case STEP_13_O_1TANK_TIME_DELAY1:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_time_delay1()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_IS_IN_COMPRESSOR_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机进口压力是否正常
		case STEP_13_O_1TANK_IS_IN_COMPRESSOR_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_is_in_compressor_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_COMPRESSOR_START;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//氧压气机启动
		case STEP_13_O_1TANK_COMPRESSOR_START:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_compressor_start()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_TIME_DELAY_B;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待时间
		case STEP_13_O_1TANK_TIME_DELAY_B:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机出口压力是否正常
		case STEP_13_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_is_out_compressor_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_OUT_COMPRESSOR_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开氧压气机出口阀门
		case STEP_13_O_1TANK_OUT_COMPRESSOR_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_step_out_compressor_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_NUMBER_COMP_GAS;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断抽气气瓶个数
		case STEP_13_O_1TANK_NUMBER_COMP_GAS:
		{
			TGTHT510_supply_stage13_comp_O_1tank_step_number_comp_gas();
			
			break;
		}

//----------------------------------一个贮箱抽气、一个气瓶抽气----------------------------------------

		//开进气瓶补加阀门
		case STEP_13_O_1TANK_1GAS_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay2
		case STEP_13_O_1TANK_1GAS_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶压力是否升高
		case STEP_13_O_1TANK_1GAS_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶抽气是否结束
		case STEP_13_O_1TANK_1GAS_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关氧路气瓶补加阀门
		case STEP_13_O_1TANK_1GAS_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_ISOLATION_FIRST;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断高压气路隔离是否正常，第一次
		case STEP_13_O_1TANK_1GAS_IS_ISOLATION_FIRST:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_isolation_first()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭氧压气机出口阀门
		case STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_out_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_ISOLATION_SECOND;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断高压气路隔离是否正常，第二次
		case STEP_13_O_1TANK_1GAS_IS_ISOLATION_SECOND:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_isolation_second()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//氧压气机停机
		case STEP_13_O_1TANK_1GAS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断氧压气机停机是否正常
		case STEP_13_O_1TANK_1GAS_IS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_BYPATH_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开氧压气机旁路自锁阀
		case STEP_13_O_1TANK_1GAS_BYPATH_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_bypath_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_TIME_DELAY_BYPATH;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_bypath
		case STEP_13_O_1TANK_1GAS_TIME_DELAY_BYPATH:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay_bypath()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关氧压气机旁路自锁阀
		case STEP_13_O_1TANK_1GAS_BYPATH_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_bypath_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭氧压气机出口阀门，第二次
		case STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_out_compressor_valve_off2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭氧压气机进口阀门
		case STEP_13_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关进贮箱低压气路补加阀门
		case STEP_13_O_1TANK_1GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_SET_STATE_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//设置氧抽气状态好
		case STEP_13_O_1TANK_1GAS_SET_STATE_GOOD:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_set_state_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机温度是否正常
		case STEP_13_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_NEED_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断是否需要进行液冷模块停机
		case STEP_13_O_1TANK_1GAS_IS_NEED_COOLER_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_need_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_TIME_DELAY3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay3
		case STEP_13_O_1TANK_1GAS_TIME_DELAY3:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay3()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		/*
		//启动液冷模块切换程序
		case STEP_13_O_1TANK_1GAS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断液冷模块切换是否正常
		case STEP_13_O_1TANK_1GAS_IS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		*/
		
		//液冷模块停机
		case STEP_13_O_1TANK_1GAS_COOLER_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COOLER_SET;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//液冷模块状态设置
		case STEP_13_O_1TANK_1GAS_COOLER_SET:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_cooler_set()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COMPRESSOR_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请压气机断电
		case STEP_13_O_1TANK_1GAS_COMPRESSOR_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_compressor_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_TGTHT530_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请电机驱动器断电
		case STEP_13_O_1TANK_1GAS_TGTHT530_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_1gas_step_TGTHT530_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
				
				//程序结束！！！！！！！！！！！！！！！！！！！！！
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}

//----------------------------------一个贮箱抽气、两个气瓶抽气----------------------------------------
		
		//开进气瓶补加阀门---第一个气瓶
		case STEP_13_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS1_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay2---第一个气瓶
		case STEP_13_O_1TANK_2GAS_GAS1_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶压力是否升高---第一个气瓶
		case STEP_13_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS1_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶抽气是否结束---第一个气瓶
		case STEP_13_O_1TANK_2GAS_GAS1_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关氧路气瓶补加阀门---第一个气瓶
		case STEP_13_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开进气瓶补加阀门---第二个气瓶
		case STEP_13_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS2_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay2---第二个气瓶
		case STEP_13_O_1TANK_2GAS_GAS2_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶压力是否升高---第二个气瓶
		case STEP_13_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS2_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶抽气是否结束---第二个气瓶
		case STEP_13_O_1TANK_2GAS_GAS2_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关氧路气瓶补加阀门---第二个气瓶
		case STEP_13_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IS_ISOLATION_FIRST;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断高压气路隔离是否正常，第一次
		case STEP_13_O_1TANK_2GAS_IS_ISOLATION_FIRST:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_isolation_first()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭氧压气机出口阀门
		case STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_out_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IS_ISOLATION_SECOND;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断高压气路隔离是否正常，第二次
		case STEP_13_O_1TANK_2GAS_IS_ISOLATION_SECOND:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_isolation_second()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//氧压气机停机
		case STEP_13_O_1TANK_2GAS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断氧压气机停机是否正常
		case STEP_13_O_1TANK_2GAS_IS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_BYPATH_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开氧压气机旁路自锁阀
		case STEP_13_O_1TANK_2GAS_BYPATH_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_bypath_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_TIME_DELAY_BYPATH;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_bypath
		case STEP_13_O_1TANK_2GAS_TIME_DELAY_BYPATH:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_time_delay_bypath()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关氧压气机旁路自锁阀
		case STEP_13_O_1TANK_2GAS_BYPATH_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_bypath_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭氧压气机出口阀门，第二次
		case STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_out_compressor_valve_off2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭氧压气机进口阀门
		case STEP_13_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_in_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关进贮箱低压气路补加阀门
		case STEP_13_O_1TANK_2GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_SET_STATE_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//设置氧抽气状态好
		case STEP_13_O_1TANK_2GAS_SET_STATE_GOOD:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_set_state_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机温度是否正常
		case STEP_13_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IS_NEED_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断是否需要进行液冷模块停机
		case STEP_13_O_1TANK_2GAS_IS_NEED_COOLER_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_need_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_TIME_DELAY3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay3
		case STEP_13_O_1TANK_2GAS_TIME_DELAY3:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_time_delay3()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		/*
		//启动液冷模块切换程序
		case STEP_13_O_1TANK_2GAS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_IS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断液冷模块切换是否正常
		case STEP_13_O_1TANK_2GAS_IS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		*/
		
		//液冷模块停机
		case STEP_13_O_1TANK_2GAS_COOLER_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COOLER_SET;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//液冷模块状态设置
		case STEP_13_O_1TANK_2GAS_COOLER_SET:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_cooler_set()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COMPRESSOR_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请压气机断电
		case STEP_13_O_1TANK_2GAS_COMPRESSOR_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_compressor_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_TGTHT530_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请电机驱动器断电
		case STEP_13_O_1TANK_2GAS_TGTHT530_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_1tank_2gas_step_TGTHT530_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
				
				//程序结束！！！！！！！！！！！！！！！！！！！！！
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}


//----------------------------------两个贮箱抽气、第一个贮箱抽气--------------------------------------

		//开进贮箱低压气路补加阀门---第一个贮箱
		case STEP_13_O_2TANK_TANK1_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_TIME_DELAY_C;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待时间
		case STEP_13_O_2TANK_TANK1_TIME_DELAY_C:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断开进贮箱阀门---第一个贮箱
		case STEP_13_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_in_tank_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开氧压气机进口阀门---第一个贮箱
		case STEP_13_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_in_compressor_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_TIME_DELAY1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay1---第一个贮箱
		case STEP_13_O_2TANK_TANK1_TIME_DELAY1:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_time_delay1()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机进口压力是否正常---第一个贮箱
		case STEP_13_O_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_in_compressor_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_COMPRESSOR_START;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//氧压气机启动---第一个贮箱
		case STEP_13_O_2TANK_TANK1_COMPRESSOR_START:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_compressor_start()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_TIME_DELAY_D;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待时间
		case STEP_13_O_2TANK_TANK1_TIME_DELAY_D:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机出口压力是否正常---第一个贮箱
		case STEP_13_O_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_out_compressor_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开氧压气机出口阀门---第一个贮箱
		case STEP_13_O_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_out_compressor_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_NUMBER_COMP_GAS;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断抽气气瓶个数---第一个贮箱
		case STEP_13_O_2TANK_TANK1_NUMBER_COMP_GAS:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_step_number_comp_gas()==TRUE)
			{
				asm("nop;");
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}

//----------------------------------两个贮箱抽气、第一个贮箱抽气、一个气瓶抽气------------------------

		//开进气瓶补加阀门---第一个贮箱
		case STEP_13_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay2---第一个贮箱
		case STEP_13_O_2TANK_TANK1_1GAS_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶压力是否升高---第一个贮箱
		case STEP_13_O_2TANK_TANK1_1GAS_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶抽气是否结束---第一个贮箱
		case STEP_13_O_2TANK_TANK1_1GAS_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关氧路气瓶补加阀门---第一个贮箱
		case STEP_13_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关进贮箱低压气路补加阀门---第一个贮箱
		case STEP_13_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断关进贮箱补加阀---第一个贮箱
		case STEP_13_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_in_tank_valve_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}

//----------------------------------两个贮箱抽气、第一个贮箱抽气、两个气瓶抽气------------------------

		//开进气瓶补加阀门---第一个气瓶
		case STEP_13_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay2---第一个气瓶
		case STEP_13_O_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶压力是否升高---第一个气瓶
		case STEP_13_O_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS1_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶抽气是否结束---第一个气瓶
		case STEP_13_O_2TANK_TANK1_2GAS_GAS1_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关氧路气瓶补加阀门---第一个气瓶
		case STEP_13_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开进气瓶补加阀门---第二个气瓶
		case STEP_13_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay2---第二个气瓶
		case STEP_13_O_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶压力是否升高---第二个气瓶
		case STEP_13_O_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS2_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶抽气是否结束---第二个气瓶
		case STEP_13_O_2TANK_TANK1_2GAS_GAS2_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关氧路气瓶补加阀门---第二个气瓶
		case STEP_13_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关进贮箱低压气路补加阀门
		case STEP_13_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断关进贮箱补加阀
		case STEP_13_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_step_is_in_tank_valve_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}

//----------------------------------两个贮箱抽气、第二个贮箱抽气--------------------------------------

		//开进贮箱低压气路补加阀门---第二个贮箱
		case STEP_13_O_2TANK_TANK2_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_step_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_TIME_DELAY_E;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待时间
		case STEP_13_O_2TANK_TANK2_TIME_DELAY_E:
		{
			if(TGTHT510_supply_stage13_comp_O_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断开进贮箱阀门---第二个贮箱
		case STEP_13_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_step_is_in_tank_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_NUMBER_COMP_GAS;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断抽气气瓶个数---第二个贮箱
		case STEP_13_O_2TANK_TANK2_NUMBER_COMP_GAS:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_step_number_comp_gas()==TRUE)
			{
				asm("nop;");
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}

//----------------------------------两个贮箱抽气、第二个贮箱抽气、一个气瓶抽气------------------------
		
		//开进气瓶补加阀门---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay2---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶压力是否升高---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶抽气是否结束---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关氧路气瓶补加阀门---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_ISOLATION_FIRST;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断高压气路隔离是否正常，第一次
		case STEP_13_O_2TANK_TANK2_1GAS_IS_ISOLATION_FIRST:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_isolation_first()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		
		//关闭氧压气机出口阀门---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_out_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_ISOLATION_SECOND;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断高压气路隔离是否正常，第二次
		case STEP_13_O_2TANK_TANK2_1GAS_IS_ISOLATION_SECOND:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_isolation_second()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//氧压气机停机---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断氧压气机停机是否正常---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_BYPATH_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开氧压气机旁路自锁阀---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_BYPATH_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_bypath_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY_BYPATH;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_bypath---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY_BYPATH:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay_bypath()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关氧压气机旁路自锁阀---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_bypath_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭氧压气机出口阀门，第二次
		case STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_out_compressor_valve_off2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭氧压气机进口阀门---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关进贮箱低压气路补加阀门---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_SET_STATE_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//设置氧抽气状态好---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_SET_STATE_GOOD:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_set_state_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机温度是否正常---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_NEED_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断是否需要进行液冷模块停机
		case STEP_13_O_2TANK_TANK2_1GAS_IS_NEED_COOLER_STOP:
		{	
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_need_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay3---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY3:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay3()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		
		/*
		//启动液冷模块切换程序---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断液冷模块切换是否正常---第二个贮箱
		case STEP_13_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		*/
		
		//液冷模块停机
		case STEP_13_O_2TANK_TANK2_1GAS_COOLER_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COOLER_SET;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//液冷模块状态设置
		case STEP_13_O_2TANK_TANK2_1GAS_COOLER_SET:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_cooler_set()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请压气机断电
		case STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_compressor_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请电机驱动器断电
		case STEP_13_O_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_TGTHT530_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_END;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//程序结束！！！！！！！！！！！！！！！！！！！！！

//----------------------------------两个贮箱抽气、第二个贮箱抽气、两个气瓶抽气------------------------

		//开进气瓶补加阀门---第一个气瓶
		case STEP_13_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay2---第一个气瓶
		case STEP_13_O_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶压力是否升高---第一个气瓶
		case STEP_13_O_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS1_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶抽气是否结束---第一个气瓶
		case STEP_13_O_2TANK_TANK2_2GAS_GAS1_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关氧路气瓶补加阀门---第一个气瓶
		case STEP_13_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开进气瓶补加阀门---第二个气瓶
		case STEP_13_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay2---第二个气瓶
		case STEP_13_O_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶压力是否升高---第二个气瓶
		case STEP_13_O_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS2_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶抽气是否结束---第二个气瓶
		case STEP_13_O_2TANK_TANK2_2GAS_GAS2_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关氧路气瓶补加阀门---第二个气瓶
		case STEP_13_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IS_ISOLATION_FIRST;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断高压气路隔离是否正常，第一次
		case STEP_13_O_2TANK_TANK2_2GAS_IS_ISOLATION_FIRST:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_isolation_first()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭氧压气机出口阀门
		case STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_out_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IS_ISOLATION_SECOND;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断高压气路隔离是否正常，第二次
		case STEP_13_O_2TANK_TANK2_2GAS_IS_ISOLATION_SECOND:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_isolation_second()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//氧压气机停机
		case STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断氧压气机停机是否正常
		case STEP_13_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_BYPATH_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开氧压气机旁路自锁阀
		case STEP_13_O_2TANK_TANK2_2GAS_BYPATH_VALVE_ON:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_bypath_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_TIME_DELAY_BYPATH;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_bypath
		case STEP_13_O_2TANK_TANK2_2GAS_TIME_DELAY_BYPATH:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_time_delay_bypath()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关氧压气机旁路自锁阀
		case STEP_13_O_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_bypath_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭氧压气机出口阀门，第二次
		case STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_out_compressor_valve_off2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭氧压气机进口阀门
		case STEP_13_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_in_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关进贮箱低压气路补加阀门
		case STEP_13_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_SET_STATE_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//设置氧抽气状态好
		case STEP_13_O_2TANK_TANK2_2GAS_SET_STATE_GOOD:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_set_state_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机温度是否正常
		case STEP_13_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IS_NEED_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断是否需要进行液冷模块停机
		case STEP_13_O_2TANK_TANK2_2GAS_IS_NEED_COOLER_STOP:
		{
		
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_need_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_TIME_DELAY3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay3
		case STEP_13_O_2TANK_TANK2_2GAS_TIME_DELAY3:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_time_delay3()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		
		/*
		//启动液冷模块切换程序
		case STEP_13_O_2TANK_TANK2_2GAS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断液冷模块切换是否正常
		case STEP_13_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		*/
		
		//液冷模块停机
		case STEP_13_O_2TANK_TANK2_2GAS_COOLER_STOP:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COOLER_SET;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//液冷模块状态设置
		case STEP_13_O_2TANK_TANK2_2GAS_COOLER_SET:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_cooler_set()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请压气机断电
		case STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_compressor_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请电机驱动器断电
		case STEP_13_O_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF:
		{
			if(TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_TGTHT530_power_off()==TRUE)
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


/*
*****************************************************************************************************************
-------------------------------------------------初始设置阶段----------------------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**名称：启动液冷泵工作
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_start_cooler(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_COOLER_VALVE_ON_NO1;
			break;
		}
		
		//液冷模块补加系统阀门开第一组
		case COMMAND_13_0001_O_INIT_COOLER_VALVE_ON_NO1:
		{
			TGTHT510_supply_command_cooler_valve_on(1);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_IS_COOLER_VALVE_ON_NO1;
			
			break;
		}
		
		//判断液冷模块补加系统阀门开第一组
		case COMMAND_13_0002_O_INIT_IS_COOLER_VALVE_ON_NO1:
		{
			if(TGTHT510_supply_command_is_cooler_valve_on(1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_INIT_COOLER_VALVE_ON_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块补加系统阀门开第二组
		case COMMAND_13_0003_O_INIT_COOLER_VALVE_ON_NO2:
		{
			TGTHT510_supply_command_cooler_valve_on(2);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_INIT_IS_COOLER_VALVE_ON_NO2;
			
			break;
		}
		
		//判断液冷模块补加系统阀门开第二组
		case COMMAND_13_0004_O_INIT_IS_COOLER_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_command_is_cooler_valve_on(2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_INIT_COOLER_POWER_ON;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块供电通
		case COMMAND_13_0005_O_INIT_COOLER_POWER_ON:
		{
			TGTHT510_supply_command_cooler_power_on();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_INIT_TIME_1MIN_START;
			
			break;
		}
		
		//延时1min计时开始
		case COMMAND_13_0006_O_INIT_TIME_1MIN_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_INIT_IS_TIME_1MIN;
			
			break;
		}
		
		//延时1min是否到
		case COMMAND_13_0007_O_INIT_IS_TIME_1MIN:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**名称：通过转速判断液冷工作是否正常
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

uint16 TGTHT510_supply_stage13_comp_O_init_step_is_cooler_work(void)
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
		
		case COMMAND_13_0001_O_INIT_IS_COOLER_WORK:
		{
			if(TGTHT510_supply_common_cooler_work(3)==TRUE)//阈值待修改！！！
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_COOLER_WORK);
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
**名称: 延时等待time_delay1
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_time_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_TIME_DELAY_START;
			break;
		}
		
		case COMMAND_13_0001_O_INIT_TIME_DELAY_START://延时等待time_delay1计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_IS_TIME_DELAY;
	
			break;
		}
		
		case COMMAND_13_0002_O_INIT_IS_TIME_DELAY://判断延时等待time_delay1
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
**名称：判断压气机温度是否正常
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_13_0001_O_INIT_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_COMPRESSOR_TEMPERATURE);//压气机测定温度异常
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
**名称：申请电机驱动器加电
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_TGTHT530_power_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_TGTHT530_POWER_ON;
			break;
		}
		
		case COMMAND_13_0001_O_INIT_TGTHT530_POWER_ON://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530a_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			break;
		}
		
		case COMMAND_13_0002_O_INIT_TGTHT530_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_INIT_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_INIT_TGTHT530_IS_TIME_1MIN://判断计时1min是否到
		{
			
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_INIT_TGTHT530_IS_POWER_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_INIT_TGTHT530_IS_POWER_ON://通过互传数据判断加电是否正常
		{
			//待补充！！！！
			
			TGTHT510_supply_ctrl.command=COMMAND_END;//待补充！！！！
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
**名称：申请压气机加电
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_compressor_power_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_COMPRESSOR_POWER_ON;
			break;
		}
		
		case COMMAND_13_0001_O_INIT_COMPRESSOR_POWER_ON://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}

			break;
		}
		
		case COMMAND_13_0002_O_INIT_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_INIT_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_INIT_COMPRESSOR_IS_TIME_1MIN://判断计时1min是否到
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**名称：贮箱隔离
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_isolation(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_ISOLATION_VALVE_OFF_NO1;
			break;
		}
		
		//隔离推进系统自锁阀关闭，第一组
		case COMMAND_13_0001_O_INIT_ISOLATION_VALVE_OFF_NO1:
		{
			TGTHT510_supply_command_isolation_valve_off(1,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_INIT_TIME_1MIN_START_NO1;
			
			break;
		}
		
		//延时1min计时开始，第一组
		case COMMAND_13_0002_O_INIT_TIME_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_INIT_IS_TIME_1MIN_NO1;
			
			break;
		}
		
		//延时1min是否到，第一组
		case COMMAND_13_0003_O_INIT_IS_TIME_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_INIT_IS_ISOLATION_VALVE_OFF_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第一组
		case COMMAND_13_0004_O_INIT_IS_ISOLATION_VALVE_OFF_NO1:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(1,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_INIT_ISOLATION_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第二组
		case COMMAND_13_0005_O_INIT_ISOLATION_VALVE_OFF_NO2:
		{
			TGTHT510_supply_command_isolation_valve_off(2,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_INIT_TIME_1MIN_START_NO2;
			
			break;
		}
		
		//延时1min计时开始，第二组
		case COMMAND_13_0006_O_INIT_TIME_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_INIT_IS_TIME_1MIN_NO2;
			
			break;
		}
		
		//延时1min是否到，第二组
		case COMMAND_13_0007_O_INIT_IS_TIME_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_INIT_IS_ISOLATION_VALVE_OFF_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第二组
		case COMMAND_13_0008_O_INIT_IS_ISOLATION_VALVE_OFF_NO2:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(2,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_INIT_ISOLATION_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第三组
		case COMMAND_13_0009_O_INIT_ISOLATION_VALVE_OFF_NO3:
		{
			TGTHT510_supply_command_isolation_valve_off(3,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_INIT_TIME_1MIN_START_NO3;
			
			break;
		}
		
		//延时1min计时开始，第三组
		case COMMAND_13_0010_O_INIT_TIME_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_INIT_IS_TIME_1MIN_NO3;
			
			break;
		}
		
		//延时1min是否到，第三组
		case COMMAND_13_0011_O_INIT_IS_TIME_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_INIT_IS_ISOLATION_VALVE_OFF_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第三组
		case COMMAND_13_0012_O_INIT_IS_ISOLATION_VALVE_OFF_NO3:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(3,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_INIT_ISOLATION_VALVE_OFF_NO4;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第四组
		case COMMAND_13_0013_O_INIT_ISOLATION_VALVE_OFF_NO4:
		{
			TGTHT510_supply_command_isolation_valve_off(4,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_INIT_TIME_1MIN_START_NO4;
			
			break;
		}
		
		//延时1min计时开始，第四组
		case COMMAND_13_0014_O_INIT_TIME_1MIN_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_INIT_IS_TIME_1MIN_NO4;
			
			break;
		}
		
		//延时1min是否到，第四组
		case COMMAND_13_0015_O_INIT_IS_TIME_1MIN_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_INIT_IS_ISOLATION_VALVE_OFF_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第四组
		case COMMAND_13_0016_O_INIT_IS_ISOLATION_VALVE_OFF_NO4:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(4,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_INIT_ISOLATION_VALVE_OFF_NO5;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第五组
		case COMMAND_13_0017_O_INIT_ISOLATION_VALVE_OFF_NO5:
		{
			TGTHT510_supply_command_isolation_valve_off(5,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_INIT_TIME_1MIN_START_NO5;
			
			break;
		}
		
		//延时1min计时开始，第五组
		case COMMAND_13_0018_O_INIT_TIME_1MIN_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_INIT_IS_TIME_1MIN_NO5;
			
			break;
		}
		
		//延时1min是否到，第五组
		case COMMAND_13_0019_O_INIT_IS_TIME_1MIN_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_INIT_IS_ISOLATION_VALVE_OFF_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第五组
		case COMMAND_13_0020_O_INIT_IS_ISOLATION_VALVE_OFF_NO5:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(5,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_INIT_ISOLATION_VALVE_OFF_NO6;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第六组
		case COMMAND_13_0021_O_INIT_ISOLATION_VALVE_OFF_NO6:
		{
			TGTHT510_supply_command_isolation_valve_off(6,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_INIT_TIME_1MIN_START_NO6;
			
			break;
		}
		
		//延时1min计时开始，第六组
		case COMMAND_13_0022_O_INIT_TIME_1MIN_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_INIT_IS_TIME_1MIN_NO6;
			
			break;
		}
		
		//延时1min是否到，第六组
		case COMMAND_13_0023_O_INIT_IS_TIME_1MIN_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_INIT_IS_ISOLATION_VALVE_OFF_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第六组
		case COMMAND_13_0024_O_INIT_IS_ISOLATION_VALVE_OFF_NO6:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(6,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_INIT_ISOLATION_VALVE_OFF_NO7;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第七组
		case COMMAND_13_0025_O_INIT_ISOLATION_VALVE_OFF_NO7:
		{
			TGTHT510_supply_command_isolation_valve_off(7,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_INIT_TIME_1MIN_START_NO7;
			
			break;
		}
		
		//延时1min计时开始，第七组
		case COMMAND_13_0026_O_INIT_TIME_1MIN_START_NO7:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_INIT_IS_TIME_1MIN_NO7;
			
			break;
		}
		
		//延时1min是否到，第七组
		case COMMAND_13_0027_O_INIT_IS_TIME_1MIN_NO7:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_INIT_IS_ISOLATION_VALVE_OFF_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第七组
		case COMMAND_13_0028_O_INIT_IS_ISOLATION_VALVE_OFF_NO7:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(7,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_INIT_ISOLATION_VALVE_OFF_NO8;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第八组
		case COMMAND_13_0029_O_INIT_ISOLATION_VALVE_OFF_NO8:
		{
			TGTHT510_supply_command_isolation_valve_off(8,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0030_O_INIT_TIME_1MIN_START_NO8;
			
			break;
		}
		
		//延时1min计时开始，第八组
		case COMMAND_13_0030_O_INIT_TIME_1MIN_START_NO8:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0031_O_INIT_IS_TIME_1MIN_NO8;
			
			break;
		}
		
		//延时1min是否到，第八组
		case COMMAND_13_0031_O_INIT_IS_TIME_1MIN_NO8:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0032_O_INIT_IS_ISOLATION_VALVE_OFF_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第八组
		case COMMAND_13_0032_O_INIT_IS_ISOLATION_VALVE_OFF_NO8:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(8,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0033_O_INIT_ISOLATION_VALVE_OFF_NO9;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第九组
		case COMMAND_13_0033_O_INIT_ISOLATION_VALVE_OFF_NO9:
		{
			TGTHT510_supply_command_isolation_valve_off(9,ISOLATION_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0034_O_INIT_TIME_1MIN_START_NO9;
			
			break;
		}
		
		//延时1min计时开始，第九组
		case COMMAND_13_0034_O_INIT_TIME_1MIN_START_NO9:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0035_O_INIT_IS_TIME_1MIN_NO9;
			
			break;
		}
		
		//延时1min是否到，第九组
		case COMMAND_13_0035_O_INIT_IS_TIME_1MIN_NO9:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0036_O_INIT_IS_ISOLATION_VALVE_OFF_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第九组
		case COMMAND_13_0036_O_INIT_IS_ISOLATION_VALVE_OFF_NO9:
		{
			if((TGTHT510_supply_command_is_isolation_valve_off(9,ISOLATION_TANK_O))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
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
**名称：判断抽气贮箱个数
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
uint16 TGTHT510_supply_stage13_comp_O_init_step_number_comp_tank(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_INIT_NUMBER_COMP_TANK;
			break;
		}
		
		case COMMAND_13_0001_O_INIT_NUMBER_COMP_TANK://判断抽气贮箱个数
		{
			if(TGTHT510_supply_decode_par.number_tank_O==1)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_IN_TANK_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else if((TGTHT510_supply_decode_par.number_tank_O==2)||\
			(TGTHT510_supply_decode_par.number_tank_O==3))
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_IN_TANK_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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


/*
*****************************************************************************************************************
-------------------------------------------------一个贮箱抽气----------------------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**名称：开进贮箱低压气路补加阀门
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_IN_TANK_VALVE_ON://开进贮箱低压气路补加阀门
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				TGTHT510_supply_main_lvb_set(LVb1K);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				TGTHT510_supply_main_lvb_set(LVb3K);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				TGTHT510_supply_main_lvb_set(LVb5K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_IS_IN_TANK_VALVE_ON://判断开进贮箱低压气路补加阀门
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称：通过压力判断开进贮箱低压气路补加阀门
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_is_in_tank_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE://通过压力判断开补加阀门
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O1)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O2)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O3)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称：开氧压气机进口阀门
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_in_compressor_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO1://开氧压气机进口阀门，第一组
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				TGTHT510_supply_main_lvb_set(LVb13K);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_main_lvb_set(LVb24K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO1;

			break;
		}
		
		case COMMAND_13_0002_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO1://判断开氧压气机进口阀门，第一组
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO2;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb24,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO2;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO2://开氧压气机进口阀门，第二组
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				TGTHT510_supply_main_lvb_set(LVb15K);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				asm("nop;");
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO2://判断开氧压气机进口阀门，第二组
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO3;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO3://开氧压气机进口阀门，第三组
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				TGTHT510_supply_main_lvb_set(LVb21G);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO3;

			break;
		}
		
		case COMMAND_13_0006_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO3://判断开氧压气机进口阀门，第三组
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 延时等待time_delay1
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_time_delay1(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_TIME_DELAY1_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_TIME_DELAY1_START://延时等待time_delay1计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_IS_TIME_DELAY1;
	
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_IS_TIME_DELAY1://判断延时等待time_delay1
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
**名称: 判断压气机进口压力是否正常
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_is_in_compressor_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_IS_IN_COMPRESSOR_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_IS_IN_COMPRESSOR_PRESSURE://判断压气机进口压力是否正常
		{
			if(TGTHT510_supply_common_is_in_compressor_pressure(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_IN_COMPRESSOR_PRESSURE);
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
**名称: 氧压气机启动
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_compressor_start(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_COMPRESSOR_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_COMPRESSOR_START://申请设备管理指令，压气机启动
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_START);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_START);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_COMPRESSOR_IS_TIME_1MIN://判断1min定时
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_IS_COMPRESSOR_START;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_IS_COMPRESSOR_START://通过互传数据判断启动是否正常
		{
			//待补充！！！！
			
			TGTHT510_supply_ctrl.command=COMMAND_END;//待补充！！！！
			
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
**名称: 判断压气机出口压力是否正常
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_is_out_compressor_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE://判断压气机出口压力是否正常
		{
			if(TGTHT510_supply_common_is_out_compressor_pressure(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_OUT_COMPRESSOR_PRESSURE);
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
**名称: 开氧压气机出口阀门
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_out_compressor_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_OUT_COMPRESSOR_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_OUT_COMPRESSOR_VALVE_ON://开氧压气机出口阀门
		{
			TGTHT510_supply_common_out_compressor_valve_on(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_IS_OUT_COMPRESSOR_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_IS_OUT_COMPRESSOR_VALVE_ON://判断开氧压气机出口阀门
		{
			if(TGTHT510_supply_common_is_out_compressor_valve_on(COMP_TANK_O)==TRUE)
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
**名称: 判断抽气气瓶个数
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_number_comp_gas(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_NUMBER_COMP_GAS;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_NUMBER_COMP_GAS://判断抽气气瓶个数
		{
			if(TGTHT510_supply_common_number_gas(COMP_TANK_O,FIRST_TANK)==ONE_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else if(TGTHT510_supply_common_number_gas(COMP_TANK_O,FIRST_TANK)==TWO_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else 
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
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


/*
*****************************************************************************************************************
-----------------------------------一个贮箱抽气，一个气瓶抽气----------------------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**名称: 开进气瓶补加阀门
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IN_GAS_VALVE_ON://开进气瓶补加阀门
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_ON://判断开进气瓶补加阀门
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
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
**名称: 延时等待time_delay2
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_TIME_DELAY2_START://延时等待time_delay2计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_DELAY2://判断延时等待time_delay2
		{
			
			/*
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_delay_short)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			*/
			if(TGTHT510_supply_time_step_is_get(0)==TRUE)
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
**名称: 判断气瓶压力是否升高
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_GAS_PRESSURE_NO1://采集气瓶压力，第一次
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_TIME_30S_START_NO1://计时30s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_IS_TIME_30S_NO1://判断定时30s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_GAS_PRESSURE_NO2://采集气瓶压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_TIME_30S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_TIME_30S_START_NO2://计时30s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_TIME_30S_NO2;
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_IS_TIME_30S_NO2://判断定时30s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_1GAS_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_1GAS_GAS_PRESSURE_NO3://采集气瓶压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_1GAS_TIME_30S_START_NO3;
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_1GAS_TIME_30S_START_NO3://计时30s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_1GAS_IS_TIME_30S_NO3;
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_1GAS_IS_TIME_30S_NO3://判断定时30s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_1GAS_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_1GAS_GAS_PRESSURE_NO4://采集气瓶压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_1GAS_TIME_30S_START_NO4;
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_1GAS_TIME_30S_START_NO4://计时30s计时开始，第四次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_1TANK_1GAS_IS_TIME_30S_NO4;
			break;
		}
		
		case COMMAND_13_0012_O_1TANK_1GAS_IS_TIME_30S_NO4://判断定时30s，第四次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_1TANK_1GAS_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0013_O_1TANK_1GAS_GAS_PRESSURE_NO5://采集气瓶压力，第五次
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_1TANK_1GAS_TIME_30S_START_NO5;
			break;
		}
		
		case COMMAND_13_0014_O_1TANK_1GAS_TIME_30S_START_NO5://计时30s计时开始，第五次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_1TANK_1GAS_IS_TIME_30S_NO5;
			break;
		}
		
		case COMMAND_13_0015_O_1TANK_1GAS_IS_TIME_30S_NO5://判断定时30s，第五次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_1TANK_1GAS_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0016_O_1TANK_1GAS_GAS_PRESSURE_NO6://采集气瓶压力，第六次
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_1TANK_1GAS_TIME_30S_START_NO6;
			break;
		}
		
		case COMMAND_13_0017_O_1TANK_1GAS_TIME_30S_START_NO6://计时30s计时开始，第六次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_1TANK_1GAS_IS_TIME_30S_NO6;
			break;
		}
		
		case COMMAND_13_0018_O_1TANK_1GAS_IS_TIME_30S_NO6://判断定时30s，第六次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_1TANK_1GAS_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0019_O_1TANK_1GAS_GAS_PRESSURE_NO7://采集气瓶压力，第七次
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_1TANK_1GAS_TIME_30S_START_NO7;
			break;
		}
		
		case COMMAND_13_0020_O_1TANK_1GAS_TIME_30S_START_NO7://计时30s计时开始，第七次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_1TANK_1GAS_IS_TIME_30S_NO7;
			break;
		}
		
		case COMMAND_13_0021_O_1TANK_1GAS_IS_TIME_30S_NO7://判断定时30s，第七次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_1TANK_1GAS_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0022_O_1TANK_1GAS_GAS_PRESSURE_NO8://采集气瓶压力，第八次
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_1TANK_1GAS_TIME_30S_START_NO8;
			break;
		}
		
		case COMMAND_13_0023_O_1TANK_1GAS_TIME_30S_START_NO8://计时30s计时开始，第八次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_1TANK_1GAS_IS_TIME_30S_NO8;
			break;
		}
		
		case COMMAND_13_0024_O_1TANK_1GAS_IS_TIME_30S_NO8://判断定时30s，第八次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_1TANK_1GAS_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0025_O_1TANK_1GAS_GAS_PRESSURE_NO9://采集气瓶压力，第九次
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_1TANK_1GAS_TIME_30S_START_NO9;
			break;
		}
		
		case COMMAND_13_0026_O_1TANK_1GAS_TIME_30S_START_NO9://计时30s计时开始，第九次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_1TANK_1GAS_IS_TIME_30S_NO9;
			break;
		}
		
		case COMMAND_13_0027_O_1TANK_1GAS_IS_TIME_30S_NO9://判断定时30s，第九次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_1TANK_1GAS_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0028_O_1TANK_1GAS_GAS_PRESSURE_NO10://采集气瓶压力，第十次
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_1TANK_1GAS_IS_GAS_PRESSURE;
			break;
		}
		
		case COMMAND_13_0029_O_1TANK_1GAS_IS_GAS_PRESSURE://压差判断气瓶压力是否升高
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**名称: 判断气瓶抽气是否结束
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IS_COMP_GAS_OVER://判断气瓶抽气是否结束
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
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
**名称: 关氧路气瓶补加阀门
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			//采集关阀之前的压气机出口压力值
			temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO1://关氧路气瓶补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO1://判断关氧路气瓶补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO2://关氧路气瓶补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO2;
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO2://判断关氧路气瓶补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO3://关氧路气瓶补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO3;
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO3://判断关氧路气瓶补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
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
**名称: 通过压力判断高压气路隔离是否正常，第一次
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_isolation_first(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO1;
			
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_FIRST_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_FIRST_TIME_12S_START_NO1://计时12s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO1://判断定时12s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_FIRST_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_FIRST_TIME_12S_START_NO2://计时12s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO2://判断定时12s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO3://采集压气机出口压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_1GAS_FIRST_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_1GAS_FIRST_TIME_12S_START_NO3://计时12s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO3://判断定时12s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO4://采集压气机出口压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_1GAS_FIRST_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_1GAS_FIRST_IS_ISOLATION://通过压力判断高压气路隔离是否正常
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COMPRESSOR_STOP;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**名称: 关闭氧压气机出口阀门
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_out_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1://关闭氧压气机出口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1://判断关闭氧压气机出口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2://关闭氧压气机出口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2://判断关闭氧压气机出口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3://关闭氧压气机出口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3://判断关闭氧压气机出口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
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
**名称: 通过压力判断高压气路隔离是否正常，第2次
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_isolation_second(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_SECOND_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_SECOND_TIME_12S_START_NO1://计时12s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO1://判断定时12s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_SECOND_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_SECOND_TIME_12S_START_NO2://计时12s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO2://判断定时12s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO3://采集压气机出口压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_1GAS_SECOND_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_1GAS_SECOND_TIME_12S_START_NO3://计时12s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO3://判断定时12s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO4://采集压气机出口压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_1GAS_SECOND_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_1GAS_SECOND_IS_ISOLATION://通过压力判断高压气路隔离是否正常
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_ISOLATION);//高压气路隔离异常
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**名称: 氧压气机停机
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_STOP://申请设备管理指令，压气机停机
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN://判断1min定时
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**名称: 判断氧压气机停机是否正常
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

//该函数待修改！！！！！！！！！！！！！

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_compressor_stop(void)
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
		
		case COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_V_NO1://采集电机转速，第一次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_V_NO2://采集电机转速，第二次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_V_NO3://采集电机转速，第三次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_COMPRESSOR_V_NO4://采集电机转速，第四次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_COMPRESSOR_V_NO5://采集电机转速，第五次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_COMPRESSOR_V_NO6://采集电机转速，第六次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_1GAS_COMPRESSOR_V_NO7://采集电机转速，第七次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_1GAS_COMPRESSOR_V_NO8://采集电机转速，第八次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_1GAS_TIME_12S_START://计时12s计时开始
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_1GAS_IS_TIME_12S://判断定时12s
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0012_O_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0013_O_1TANK_1GAS_IS_COMPRESSOR_STOP://判断氧压气机停机是否正常
		{
			//待补充！！！！
			
			
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
**名称: 开氧压气机旁路自锁阀
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_bypath_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_BYPATH_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_BYPATH_VALVE_ON://开氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_lvb_set(LVb21K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_ON;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_lvb_set(LVb87K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_ON;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_ON://判断开氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 延时等待time_bypath
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay_bypath(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_TIME_BYPATH_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_TIME_BYPATH_START://延时等待time_bypath计时开启
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_BYPATH;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_BYPATH://判断延时等待time_bypath
		{
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_bypath)==TRUE)
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
**名称: 关氧压气机旁路自锁阀
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_bypath_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_BYPATH_VALVE_OFF;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_BYPATH_VALVE_OFF://关氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_lvb_set(LVb21G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_OFF://判断关氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 关闭氧压气机出口阀门，第二次
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_out_compressor_valve_off2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1://关闭氧压气机出口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1://判断关闭氧压气机出口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2://关闭氧压气机出口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2://判断关闭氧压气机出口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3://关闭氧压气机出口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3://判断关闭氧压气机出口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
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
**名称: 关闭氧压气机进口阀门
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1://关闭氧压气机进口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb13G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1://判断关闭氧压气机进口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2://关闭氧压气机进口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb15G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2://判断关闭氧压气机进口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3://关闭氧压气机进口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb23G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3://判断关闭氧压气机进口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb23,VALVE_OFF)==TRUE)
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
**名称: 关进贮箱低压气路补加阀门
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO1://关进贮箱低压气路补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO1://判断关进贮箱低压气路补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO2://关进贮箱低压气路补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO2://判断关进贮箱低压气路补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO3://关进贮箱低压气路补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO3://判断关进贮箱低压气路补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)
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
**名称: 设置氧抽气状态好
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

//待补充！！！！

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_set_state_good(void)
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
		
		case COMMAND_13_0001_O_1TANK_1GAS_SET_STATE_GOOD://设置氧抽气状态好
		{
			//待补充！！！！
			
			
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
**名称: 判断压气机温度是否正常
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE://判断压气机温度是否正常
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_COMPRESSOR_TEMPERATURE);//压气机测定温度异常
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
**名称: 判断是否需要进行液冷模块切换程序
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_need_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_IS_NEED_COOLER_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_IS_NEED_COOLER_STOP://判断是否需要进行液冷模块停机
		{
			if(TGTHT510_supply_decode_par.number_tank_F==3)
			{
				//具有第三个补加贮箱，不进行液冷模块切换程序
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_1GAS_COMPRESSOR_POWER_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
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
**名称: 延时等待time_delay3
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay3(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_TIME_DELAY3_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_1GAS_TIME_DELAY3_START://延时等待time_delay3计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_DELAY3;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_DELAY3://判断延时等待time_delay3
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
**名称: 液冷模块停机
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_COOLER_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_1TANK_1GAS_COOLER_POWER_OFF://液冷模块停机
		{
			TGTHT510_supply_command_cooler_power_off();
			
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
**名称: 液冷模块状态设置
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_cooler_set(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_COOLER_SET_NO1;
			break;
		}
		
		//液冷模块状态设置1
		case COMMAND_13_0001_O_1TANK_1GAS_COOLER_SET_NO1:
		{
			TGTHT510_supply_main_lvb_set(LVb35K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_IS_COOLER_SET_NO1;
			
			break;
		}
		
		//判断液冷模块状态设置1
		case COMMAND_13_0002_O_1TANK_1GAS_IS_COOLER_SET_NO1:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb35,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_COOLER_SET_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块状态设置2
		case COMMAND_13_0003_O_1TANK_1GAS_COOLER_SET_NO2:
		{
			TGTHT510_supply_main_lvb_set(LVb28K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_1GAS_IS_COOLER_SET_NO2;
			
			break;
		}
		
		//判断液冷模块状态设置2
		case COMMAND_13_0004_O_1TANK_1GAS_IS_COOLER_SET_NO2:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb28,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_1GAS_COOLER_SET_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块状态设置3
		case COMMAND_13_0005_O_1TANK_1GAS_COOLER_SET_NO3:
		{
			TGTHT510_supply_main_lvb_set(LVb30K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_1GAS_IS_COOLER_SET_NO3;
			
			break;
		}
		
		//判断液冷模块状态设置3
		case COMMAND_13_0006_O_1TANK_1GAS_IS_COOLER_SET_NO3:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb30,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_1GAS_COOLER_SET_NO4;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块状态设置4
		case COMMAND_13_0007_O_1TANK_1GAS_COOLER_SET_NO4:
		{
			TGTHT510_supply_main_lvb_set(LVb31G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_1GAS_IS_COOLER_SET_NO4;
			
			break;
		}
		
		//判断液冷模块状态设置4
		case COMMAND_13_0008_O_1TANK_1GAS_IS_COOLER_SET_NO4:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb31,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_1GAS_COOLER_SET_NO5;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置5
		case COMMAND_13_0009_O_1TANK_1GAS_COOLER_SET_NO5:
		{
			TGTHT510_supply_main_lvb_set(LVb27G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_1GAS_IS_COOLER_SET_NO5;
			
			break;
		}
		
		//判断液冷模块状态设置5
		case COMMAND_13_0010_O_1TANK_1GAS_IS_COOLER_SET_NO5:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb27,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_1GAS_COOLER_SET_NO6;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置6
		case COMMAND_13_0011_O_1TANK_1GAS_COOLER_SET_NO6:
		{
			TGTHT510_supply_main_lvb_set(LVb29G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_1TANK_1GAS_IS_COOLER_SET_NO6;
			
			break;
		}
		
		//判断液冷模块状态设置6
		case COMMAND_13_0012_O_1TANK_1GAS_IS_COOLER_SET_NO6:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb29,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_1TANK_1GAS_COOLER_SET_NO7;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置7
		case COMMAND_13_0013_O_1TANK_1GAS_COOLER_SET_NO7:
		{
			TGTHT510_supply_main_lvb_set(LVb33G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_1TANK_1GAS_IS_COOLER_SET_NO7;
			
			break;
		}
		
		//判断液冷模块状态设置7
		case COMMAND_13_0014_O_1TANK_1GAS_IS_COOLER_SET_NO7:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb33,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_1TANK_1GAS_COOLER_SET_NO8;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置8
		case COMMAND_13_0015_O_1TANK_1GAS_COOLER_SET_NO8:
		{
			TGTHT510_supply_main_lvb_set(LVb37G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_1TANK_1GAS_IS_COOLER_SET_NO8;
			
			break;
		}
		
		//判断液冷模块状态设置8
		case COMMAND_13_0016_O_1TANK_1GAS_IS_COOLER_SET_NO8:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb37,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_1TANK_1GAS_COOLER_SET_NO9;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置9
		case COMMAND_13_0017_O_1TANK_1GAS_COOLER_SET_NO9:
		{
			TGTHT510_supply_main_lvb_set(LVb32G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_1TANK_1GAS_IS_COOLER_SET_NO9;
			
			break;
		}
		
		//判断液冷模块状态设置9
		case COMMAND_13_0018_O_1TANK_1GAS_IS_COOLER_SET_NO9:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb32,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_1TANK_1GAS_COOLER_SET_NO10;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置10
		case COMMAND_13_0019_O_1TANK_1GAS_COOLER_SET_NO10:
		{
			TGTHT510_supply_main_lvb_set(LVb34G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_1TANK_1GAS_IS_COOLER_SET_NO10;
			
			break;
		}
		
		//判断液冷模块状态设置10
		case COMMAND_13_0020_O_1TANK_1GAS_IS_COOLER_SET_NO10:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb34,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_1TANK_1GAS_COOLER_SET_NO11;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置11
		case COMMAND_13_0021_O_1TANK_1GAS_COOLER_SET_NO11:
		{
			TGTHT510_supply_main_lvb_set(LVb36G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_1TANK_1GAS_IS_COOLER_SET_NO11;
			
			break;
		}
		
		//判断液冷模块状态设置11
		case COMMAND_13_0022_O_1TANK_1GAS_IS_COOLER_SET_NO11:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb36,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_1TANK_1GAS_COOLER_SET_NO12;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置12
		case COMMAND_13_0023_O_1TANK_1GAS_COOLER_SET_NO12:
		{
			TGTHT510_supply_main_lvb_set(LVb38G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_1TANK_1GAS_IS_COOLER_SET_NO12;
			
			break;
		}
		
		//判断液冷模块状态设置12
		case COMMAND_13_0024_O_1TANK_1GAS_IS_COOLER_SET_NO12:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb38,VALVE_OFF)==TRUE)
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
**名称: 申请压气机断电
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_compressor_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_POWER_OFF://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN://判断计时1min是否到
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**名称: 申请电机驱动器断电
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_TGTHT530_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_1GAS_TGTHT530_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_1TANK_1GAS_TGTHT530_POWER_OFF://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530a_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_1GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_1GAS_TGTHT530_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_1GAS_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_1GAS_TGTHT530_IS_TIME_1MIN://判断计时1min是否到
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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


/*
*****************************************************************************************************************
-----------------------------------一个贮箱抽气，两个气瓶抽气----------------------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**名称: 开进气瓶补加阀门---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON://开进气瓶补加阀门
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_ON://判断开进气瓶补加阀门
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
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
**名称: 延时等待time_delay2---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS1_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS1_TIME_DELAY2_START://延时等待time_delay2计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_TIME_DELAY2://判断延时等待time_delay2
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
**名称: 判断气瓶压力是否升高---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO1://采集气瓶压力，第一次
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS1_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS1_TIME_30S_START_NO1://计时30s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO1://判断定时30s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO2://采集气瓶压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_GAS1_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_GAS1_TIME_30S_START_NO2://计时30s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO2://判断定时30s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO3://采集气瓶压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_2GAS_GAS1_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_2GAS_GAS1_TIME_30S_START_NO3://计时30s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO3://判断定时30s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO4://采集气瓶压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_2GAS_GAS1_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_2GAS_GAS1_TIME_30S_START_NO4://计时30s计时开始，第四次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO4://判断定时30s，第四次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO5://采集气瓶压力，第五次
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_1TANK_2GAS_GAS1_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_1TANK_2GAS_GAS1_TIME_30S_START_NO5://计时30s计时开始，第五次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO5://判断定时30s，第五次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO6://采集气瓶压力，第六次
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_1TANK_2GAS_GAS1_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_1TANK_2GAS_GAS1_TIME_30S_START_NO6://计时30s计时开始，第六次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO6://判断定时30s，第六次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO7://采集气瓶压力，第七次
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_1TANK_2GAS_GAS1_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_1TANK_2GAS_GAS1_TIME_30S_START_NO7://计时30s计时开始，第七次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO7://判断定时30s，第七次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO8://采集气瓶压力，第八次
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_1TANK_2GAS_GAS1_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_1TANK_2GAS_GAS1_TIME_30S_START_NO8://计时30s计时开始，第八次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO8://判断定时30s，第八次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO9://采集气瓶压力，第九次
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_1TANK_2GAS_GAS1_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_1TANK_2GAS_GAS1_TIME_30S_START_NO9://计时30s计时开始，第九次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO9://判断定时30s，第九次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO10://采集气瓶压力，第十次
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE://压差判断气瓶压力是否升高
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**名称: 判断气瓶抽气是否结束---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS1_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS1_IS_COMP_GAS_OVER://判断气瓶抽气是否结束
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
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
**名称: 关氧路气瓶补加阀门---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1://关氧路气瓶补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1://判断关氧路气瓶补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2://关氧路气瓶补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2://判断关氧路气瓶补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3://关氧路气瓶补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3://判断关氧路气瓶补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
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
**名称: 开进气瓶补加阀门---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON://开进气瓶补加阀门
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_ON://判断开进气瓶补加阀门
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,SECOND_GAS)==TRUE)
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
**名称: 延时等待time_delay2---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS2_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS2_TIME_DELAY2_START://延时等待time_delay2计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_TIME_DELAY2://判断延时等待time_delay2
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
**名称: 判断气瓶压力是否升高---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO1://采集气瓶压力，第一次
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS2_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS2_TIME_30S_START_NO1://计时30s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO1://判断定时30s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO2://采集气瓶压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_GAS2_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_GAS2_TIME_30S_START_NO2://计时30s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO2://判断定时30s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO3://采集气瓶压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_2GAS_GAS2_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_2GAS_GAS2_TIME_30S_START_NO3://计时30s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO3://判断定时30s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO4://采集气瓶压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_2GAS_GAS2_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_2GAS_GAS2_TIME_30S_START_NO4://计时30s计时开始，第四次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO4://判断定时30s，第四次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO5://采集气瓶压力，第五次
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_1TANK_2GAS_GAS2_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_1TANK_2GAS_GAS2_TIME_30S_START_NO5://计时30s计时开始，第五次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO5://判断定时30s，第五次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO6://采集气瓶压力，第六次
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_1TANK_2GAS_GAS2_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_1TANK_2GAS_GAS2_TIME_30S_START_NO6://计时30s计时开始，第六次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO6://判断定时30s，第六次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO7://采集气瓶压力，第七次
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_1TANK_2GAS_GAS2_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_1TANK_2GAS_GAS2_TIME_30S_START_NO7://计时30s计时开始，第七次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO7://判断定时30s，第七次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO8://采集气瓶压力，第八次
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_1TANK_2GAS_GAS2_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_1TANK_2GAS_GAS2_TIME_30S_START_NO8://计时30s计时开始，第八次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO8://判断定时30s，第八次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO9://采集气瓶压力，第九次
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_1TANK_2GAS_GAS2_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_1TANK_2GAS_GAS2_TIME_30S_START_NO9://计时30s计时开始，第九次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO9://判断定时30s，第九次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO10://采集气瓶压力，第十次
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE://压差判断气瓶压力是否升高
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**名称: 判断气瓶抽气是否结束---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS2_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS2_IS_COMP_GAS_OVER://判断气瓶抽气是否结束
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,FIRST_TANK,SECOND_GAS)==TRUE)
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
**名称: 关氧路气瓶补加阀门---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1://关氧路气瓶补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1://判断关氧路气瓶补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2://关氧路气瓶补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2://判断关氧路气瓶补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3://关氧路气瓶补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3://判断关氧路气瓶补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
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
**名称: 通过压力判断高压气路隔离是否正常，第一次
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_isolation_first(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_FIRST_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_FIRST_TIME_12S_START_NO1://计时12s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO1://判断定时12s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_FIRST_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_FIRST_TIME_12S_START_NO2://计时12s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO2://判断定时12s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO3://采集压气机出口压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_2GAS_FIRST_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_2GAS_FIRST_TIME_12S_START_NO3://计时12s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO3://判断定时12s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO4://采集压气机出口压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_2GAS_FIRST_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_2GAS_FIRST_IS_ISOLATION://通过压力判断高压气路隔离是否正常
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COMPRESSOR_STOP;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**名称: 关闭氧压气机出口阀门
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_out_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1://关闭氧压气机出口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1://判断关闭氧压气机出口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2://关闭氧压气机出口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2://判断关闭氧压气机出口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3://关闭氧压气机出口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3://判断关闭氧压气机出口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
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
**名称: 通过压力判断高压气路隔离是否正常，第2次
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_isolation_second(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_SECOND_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_SECOND_TIME_12S_START_NO1://计时12s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO1://判断定时12s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_SECOND_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_SECOND_TIME_12S_START_NO2://计时12s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO2://判断定时12s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO3://采集压气机出口压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_2GAS_SECOND_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_2GAS_SECOND_TIME_12S_START_NO3://计时12s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO3://判断定时12s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO4://采集压气机出口压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_2GAS_SECOND_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_2GAS_SECOND_IS_ISOLATION://通过压力判断高压气路隔离是否正常
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_ISOLATION);//高压气路隔离异常
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**名称: 氧压气机停机
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_STOP://申请设备管理指令，压气机停机
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN://判断1min定时
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**名称: 判断氧压气机停机是否正常
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

//该函数待修改！！！！！！！！！！！！！

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_compressor_stop(void)
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
		
		case COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_V_NO1://采集电机转速，第一次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_V_NO2://采集电机转速，第二次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_V_NO3://采集电机转速，第三次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_COMPRESSOR_V_NO4://采集电机转速，第四次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_COMPRESSOR_V_NO5://采集电机转速，第五次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_COMPRESSOR_V_NO6://采集电机转速，第六次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0007_O_1TANK_2GAS_COMPRESSOR_V_NO7://采集电机转速，第七次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_2GAS_COMPRESSOR_V_NO8://采集电机转速，第八次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0009_O_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0010_O_1TANK_2GAS_TIME_12S_START://计时12s计时开始
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0011_O_1TANK_2GAS_IS_TIME_12S://判断定时12s
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0012_O_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0013_O_1TANK_2GAS_IS_COMPRESSOR_STOP://判断氧压气机停机是否正常
		{
			//待补充！！！！
			
			
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
**名称: 开氧压气机旁路自锁阀
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_bypath_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_BYPATH_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_BYPATH_VALVE_ON://开氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_lvb_set(LVb21K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_ON;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_lvb_set(LVb87K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_ON;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_ON://判断开氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 延时等待time_bypath
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_time_delay_bypath(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_TIME_BYPATH_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_TIME_BYPATH_START://延时等待time_bypath计时开启
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_TIME_BYPATH;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_TIME_BYPATH://判断延时等待time_bypath
		{
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_bypath)==TRUE)
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
**名称: 关氧压气机旁路自锁阀
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_bypath_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_BYPATH_VALVE_OFF;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_BYPATH_VALVE_OFF://关氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_lvb_set(LVb21G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_OFF://判断关氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 关闭氧压气机出口阀门，第二次
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_out_compressor_valve_off2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1://关闭氧压气机出口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1://判断关闭氧压气机出口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2://关闭氧压气机出口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2://判断关闭氧压气机出口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3://关闭氧压气机出口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3://判断关闭氧压气机出口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
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
**名称: 关闭氧压气机进口阀门
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_in_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1://关闭氧压气机进口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb13G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1://判断关闭氧压气机进口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2://关闭氧压气机进口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb15G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2://判断关闭氧压气机进口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3://关闭氧压气机进口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb23G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3://判断关闭氧压气机进口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb23,VALVE_OFF)==TRUE)
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
**名称: 关进贮箱低压气路补加阀门
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO1://关进贮箱低压气路补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO1://判断关进贮箱低压气路补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO2;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO2://关进贮箱低压气路补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO2://判断关进贮箱低压气路补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO3://关进贮箱低压气路补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO3://判断关进贮箱低压气路补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)
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
**名称: 设置氧抽气状态好
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

//待补充！！！！

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_set_state_good(void)
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
		
		case COMMAND_13_0001_O_1TANK_2GAS_SET_STATE_GOOD://设置氧抽气状态好
		{
			//待补充！！！！
			
			
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
**名称: 判断压气机温度是否正常
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE://判断压气机温度是否正常
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_COMPRESSOR_TEMPERATURE);//压气机测定温度异常
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
**名称: 判断是否需要进行液冷模块切换程序
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

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_need_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_IS_NEED_COOLER_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_IS_NEED_COOLER_STOP://判断是否需要进行液冷模块停机
		{
			if(TGTHT510_supply_decode_par.number_tank_F==3)
			{
				//具有第三个补加贮箱，不进行液冷模块停机
				TGTHT510_supply_ctrl.step=STEP_13_O_1TANK_2GAS_COMPRESSOR_POWER_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
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
**名称: 延时等待time_delay3
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_time_delay3(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_TIME_DELAY3_START;
			break;
		}
		
		case COMMAND_13_0001_O_1TANK_2GAS_TIME_DELAY3_START://延时等待time_delay3计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_TIME_DELAY3;
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_IS_TIME_DELAY3://判断延时等待time_delay3
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
**名称: 液冷模块停机
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_COOLER_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_1TANK_2GAS_COOLER_POWER_OFF://液冷模块停机
		{
			TGTHT510_supply_command_cooler_power_off();
			
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
**名称: 液冷模块状态设置
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_cooler_set(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_COOLER_SET_NO1;
			break;
		}
		
		//液冷模块状态设置1
		case COMMAND_13_0001_O_1TANK_2GAS_COOLER_SET_NO1:
		{
			TGTHT510_supply_main_lvb_set(LVb35K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_IS_COOLER_SET_NO1;
			
			break;
		}
		
		//判断液冷模块状态设置1
		case COMMAND_13_0002_O_1TANK_2GAS_IS_COOLER_SET_NO1:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb35,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_COOLER_SET_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块状态设置2
		case COMMAND_13_0003_O_1TANK_2GAS_COOLER_SET_NO2:
		{
			TGTHT510_supply_main_lvb_set(LVb28K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_1TANK_2GAS_IS_COOLER_SET_NO2;
			
			break;
		}
		
		//判断液冷模块状态设置2
		case COMMAND_13_0004_O_1TANK_2GAS_IS_COOLER_SET_NO2:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb28,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_1TANK_2GAS_COOLER_SET_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块状态设置3
		case COMMAND_13_0005_O_1TANK_2GAS_COOLER_SET_NO3:
		{
			TGTHT510_supply_main_lvb_set(LVb30K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_1TANK_2GAS_IS_COOLER_SET_NO3;
			
			break;
		}
		
		//判断液冷模块状态设置3
		case COMMAND_13_0006_O_1TANK_2GAS_IS_COOLER_SET_NO3:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb30,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_1TANK_2GAS_COOLER_SET_NO4;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块状态设置4
		case COMMAND_13_0007_O_1TANK_2GAS_COOLER_SET_NO4:
		{
			TGTHT510_supply_main_lvb_set(LVb31G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_2GAS_IS_COOLER_SET_NO4;
			
			break;
		}
		
		//判断液冷模块状态设置4
		case COMMAND_13_0008_O_1TANK_2GAS_IS_COOLER_SET_NO4:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb31,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_1TANK_2GAS_COOLER_SET_NO5;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置5
		case COMMAND_13_0009_O_1TANK_2GAS_COOLER_SET_NO5:
		{
			TGTHT510_supply_main_lvb_set(LVb27G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_1TANK_2GAS_IS_COOLER_SET_NO5;
			
			break;
		}
		
		//判断液冷模块状态设置5
		case COMMAND_13_0010_O_1TANK_2GAS_IS_COOLER_SET_NO5:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb27,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_1TANK_2GAS_COOLER_SET_NO6;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置6
		case COMMAND_13_0011_O_1TANK_2GAS_COOLER_SET_NO6:
		{
			TGTHT510_supply_main_lvb_set(LVb29G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_1TANK_2GAS_IS_COOLER_SET_NO6;
			
			break;
		}
		
		//判断液冷模块状态设置6
		case COMMAND_13_0012_O_1TANK_2GAS_IS_COOLER_SET_NO6:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb29,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_1TANK_2GAS_COOLER_SET_NO7;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置7
		case COMMAND_13_0013_O_1TANK_2GAS_COOLER_SET_NO7:
		{
			TGTHT510_supply_main_lvb_set(LVb33G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_1TANK_2GAS_IS_COOLER_SET_NO7;
			
			break;
		}
		
		//判断液冷模块状态设置7
		case COMMAND_13_0014_O_1TANK_2GAS_IS_COOLER_SET_NO7:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb33,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_1TANK_2GAS_COOLER_SET_NO8;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置8
		case COMMAND_13_0015_O_1TANK_2GAS_COOLER_SET_NO8:
		{
			TGTHT510_supply_main_lvb_set(LVb37G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_1TANK_2GAS_IS_COOLER_SET_NO8;
			
			break;
		}
		
		//判断液冷模块状态设置8
		case COMMAND_13_0016_O_1TANK_2GAS_IS_COOLER_SET_NO8:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb37,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_1TANK_2GAS_COOLER_SET_NO9;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置9
		case COMMAND_13_0017_O_1TANK_2GAS_COOLER_SET_NO9:
		{
			TGTHT510_supply_main_lvb_set(LVb32G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_1TANK_2GAS_IS_COOLER_SET_NO9;
			
			break;
		}
		
		//判断液冷模块状态设置9
		case COMMAND_13_0018_O_1TANK_2GAS_IS_COOLER_SET_NO9:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb32,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_1TANK_2GAS_COOLER_SET_NO10;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置10
		case COMMAND_13_0019_O_1TANK_2GAS_COOLER_SET_NO10:
		{
			TGTHT510_supply_main_lvb_set(LVb34G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_1TANK_2GAS_IS_COOLER_SET_NO10;
			
			break;
		}
		
		//判断液冷模块状态设置10
		case COMMAND_13_0020_O_1TANK_2GAS_IS_COOLER_SET_NO10:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb34,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_1TANK_2GAS_COOLER_SET_NO11;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置11
		case COMMAND_13_0021_O_1TANK_2GAS_COOLER_SET_NO11:
		{
			TGTHT510_supply_main_lvb_set(LVb36G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_1TANK_2GAS_IS_COOLER_SET_NO11;
			
			break;
		}
		
		//判断液冷模块状态设置11
		case COMMAND_13_0022_O_1TANK_2GAS_IS_COOLER_SET_NO11:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb36,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_1TANK_2GAS_COOLER_SET_NO12;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置12
		case COMMAND_13_0023_O_1TANK_2GAS_COOLER_SET_NO12:
		{
			TGTHT510_supply_main_lvb_set(LVb38G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_1TANK_2GAS_IS_COOLER_SET_NO12;
			
			break;
		}
		
		//判断液冷模块状态设置12
		case COMMAND_13_0024_O_1TANK_2GAS_IS_COOLER_SET_NO12:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb38,VALVE_OFF)==TRUE)
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
**名称: 申请压气机断电
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_compressor_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_POWER_OFF://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN://判断计时1min是否到
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**名称: 申请电机驱动器断电
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
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_TGTHT530_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_1TANK_2GAS_TGTHT530_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_1TANK_2GAS_TGTHT530_POWER_OFF://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530a_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_1TANK_2GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_1TANK_2GAS_TGTHT530_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_1TANK_2GAS_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_1TANK_2GAS_TGTHT530_IS_TIME_1MIN://判断计时1min是否到
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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


/*
*****************************************************************************************************************
---------------------------------两个贮箱抽气，第一个贮箱抽气----------------------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**名称: 开进贮箱低压气路补加阀门---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_IN_TANK_VALVE_ON://开进贮箱低压气路补加阀门
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				TGTHT510_supply_main_lvb_set(LVb1K);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				TGTHT510_supply_main_lvb_set(LVb3K);
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				TGTHT510_supply_main_lvb_set(LVb5K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON://判断开进贮箱低压气路补加阀门
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 通过压力判断开进贮箱阀门---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_in_tank_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE://通过压力判断开补加阀门
		{
			if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O1)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O2)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.first_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O3)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 开氧压气机进口阀门---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_in_compressor_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO1://开氧压气机进口阀门，第一组
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				TGTHT510_supply_main_lvb_set(LVb13K);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_main_lvb_set(LVb24K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO1://判断开氧压气机进口阀门，第一组
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO2;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb24,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO2;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO2://开氧压气机进口阀门，第二组
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				TGTHT510_supply_main_lvb_set(LVb15K);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				asm("nop;");
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO2://判断开氧压气机进口阀门，第二组
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO3;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO3://开氧压气机进口阀门，第三组
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				TGTHT510_supply_main_lvb_set(LVb21G);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO3://判断开氧压气机进口阀门，第三组
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 延时等待time_delay1---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_time_delay1(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_TIME_DELAY1_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_TIME_DELAY1_START://延时等待time_delay1计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_IS_TIME_DELAY1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_IS_TIME_DELAY1://判断延时等待time_delay1
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
**名称: 判断压气机进口压力是否正常---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_in_compressor_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE://判断压气机进口压力是否正常
		{
			if(TGTHT510_supply_common_is_in_compressor_pressure(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_IN_COMPRESSOR_PRESSURE);
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
**名称: 氧压气机启动---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_compressor_start(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_COMPRESSOR_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_COMPRESSOR_START://申请设备管理指令，压气机启动
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_START);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_START);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_COMPRESSOR_IS_TIME_1MIN://判断1min定时
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_IS_COMPRESSOR_START;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_IS_COMPRESSOR_START://通过互传数据判断启动是否正常
		{
			//待补充！！！！
			
			TGTHT510_supply_ctrl.command=COMMAND_END;//待补充！！！！
			
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
**名称: 判断压气机出口压力是否正常---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_out_compressor_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE://判断压气机出口压力是否正常
		{
			if(TGTHT510_supply_common_is_out_compressor_pressure(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_OUT_COMPRESSOR_PRESSURE);
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
**名称: 开氧压气机出口阀门---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_out_compressor_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON://开氧压气机出口阀门
		{
			TGTHT510_supply_common_out_compressor_valve_on(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_IS_OUT_COMPRESSOR_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_IS_OUT_COMPRESSOR_VALVE_ON://判断开氧压气机出口阀门
		{
			if(TGTHT510_supply_common_is_out_compressor_valve_on(COMP_TANK_O)==TRUE)
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
**名称: 判断抽气气瓶个数---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_number_comp_gas(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_NUMBER_COMP_GAS;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_NUMBER_COMP_GAS://判断抽气气瓶个数
		{
			if(TGTHT510_supply_common_number_gas(COMP_TANK_O,FIRST_TANK)==ONE_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else if(TGTHT510_supply_common_number_gas(COMP_TANK_O,FIRST_TANK)==TWO_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else 
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
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



/*
*****************************************************************************************************************
---------------------------------两个贮箱抽气，第一个贮箱抽气，一个气瓶抽气--------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**名称: 开进气瓶补加阀门---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON://开进气瓶补加阀门
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_ON://判断开进气瓶补加阀门
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
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
**名称: 延时等待time_delay2---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_1GAS_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_TIME_DELAY2_START://延时等待time_delay2计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_TIME_DELAY2://判断延时等待time_delay2
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
**名称: 判断气瓶压力是否升高---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO1://采集气瓶压力，第一次
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_1GAS_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_1GAS_TIME_30S_START_NO1://计时30s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO1://判断定时30s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO2://采集气瓶压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_1GAS_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_1GAS_TIME_30S_START_NO2://计时30s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO2://判断定时30s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO3://采集气瓶压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK1_1GAS_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK1_1GAS_TIME_30S_START_NO3://计时30s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO3://判断定时30s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO4://采集气瓶压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK1_1GAS_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK1_1GAS_TIME_30S_START_NO4://计时30s计时开始，第四次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO4://判断定时30s，第四次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO5://采集气瓶压力，第五次
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK1_1GAS_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_2TANK_TANK1_1GAS_TIME_30S_START_NO5://计时30s计时开始，第五次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO5://判断定时30s，第五次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO6://采集气瓶压力，第六次
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK1_1GAS_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_2TANK_TANK1_1GAS_TIME_30S_START_NO6://计时30s计时开始，第六次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO6://判断定时30s，第六次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO7://采集气瓶压力，第七次
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK1_1GAS_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_2TANK_TANK1_1GAS_TIME_30S_START_NO7://计时30s计时开始，第七次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO7://判断定时30s，第七次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO8://采集气瓶压力，第八次
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK1_1GAS_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_2TANK_TANK1_1GAS_TIME_30S_START_NO8://计时30s计时开始，第八次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO8://判断定时30s，第八次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO9://采集气瓶压力，第九次
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_2TANK_TANK1_1GAS_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_2TANK_TANK1_1GAS_TIME_30S_START_NO9://计时30s计时开始，第九次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO9://判断定时30s，第九次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO10://采集气瓶压力，第十次
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_2TANK_TANK1_1GAS_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_2TANK_TANK1_1GAS_IS_GAS_PRESSURE://压差判断气瓶压力是否升高
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**名称: 判断气瓶抽气是否结束---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_1GAS_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_IS_COMP_GAS_OVER://判断气瓶抽气是否结束
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
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
**名称: 关氧路气瓶补加阀门---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO1://关氧路气瓶补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO1://判断关氧路气瓶补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO2://关氧路气瓶补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO2://判断关氧路气瓶补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO3://关氧路气瓶补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO3://判断关氧路气瓶补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
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
**名称: 关进贮箱低压气路补加阀门---第一个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO1://关进贮箱低压气路补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO1://判断关进贮箱低压气路补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO2://关进贮箱低压气路补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO2://判断关进贮箱低压气路补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO3://关进贮箱低压气路补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO3://判断关进贮箱低压气路补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)
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
**名称: 通过压力判断关进贮箱补加阀---第一个贮箱
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

//待补充！！！！

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_in_tank_valve_pressure(void)
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
		
		case COMMAND_13_0001_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO1://通过压力判断关进贮箱补加阀，第一组
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO2://通过压力判断关进贮箱补加阀，第二组
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO3://通过压力判断关进贮箱补加阀，第三组
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO4://通过压力判断关进贮箱补加阀，第四组
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO5://通过压力判断关进贮箱补加阀，第五组
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE://通过压力判断关进贮箱补加阀，五取三
		{
			//待补充！！！！
			
			
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


/*
*****************************************************************************************************************
---------------------------------两个贮箱抽气，第一个贮箱抽气，两个气瓶抽气--------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**名称: 开进气瓶补加阀门---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON://开进气瓶补加阀门
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_ON://判断开进气瓶补加阀门
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
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
**名称: 延时等待time_delay2---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2_START://延时等待time_delay2计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_DELAY2://判断延时等待time_delay2
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
**名称: 判断气瓶压力是否升高---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO1://采集气瓶压力，第一次
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO1://计时30s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO1://判断定时30s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO2://采集气瓶压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO2://计时30s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO2://判断定时30s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO3://采集气瓶压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO3://计时30s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO3://判断定时30s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO4://采集气瓶压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO4://计时30s计时开始，第四次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO4://判断定时30s，第四次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO5://采集气瓶压力，第五次
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO5://计时30s计时开始，第五次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO5://判断定时30s，第五次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO6://采集气瓶压力，第六次
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO6://计时30s计时开始，第六次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO6://判断定时30s，第六次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO7://采集气瓶压力，第七次
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO7://计时30s计时开始，第七次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO7://判断定时30s，第七次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO8://采集气瓶压力，第八次
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO8://计时30s计时开始，第八次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO8://判断定时30s，第八次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO9://采集气瓶压力，第九次
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO9://计时30s计时开始，第九次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO9://判断定时30s，第九次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO10://采集气瓶压力，第十次
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE://压差判断气瓶压力是否升高
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**名称: 判断气瓶抽气是否结束---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IS_COMP_GAS_OVER://判断气瓶抽气是否结束
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,FIRST_TANK,FIRST_GAS)==TRUE)
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
**名称: 关氧路气瓶补加阀门---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1://关氧路气瓶补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1://判断关氧路气瓶补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2://关氧路气瓶补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2://判断关氧路气瓶补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3://关氧路气瓶补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3://判断关氧路气瓶补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
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
**名称: 开进气瓶补加阀门---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON://开进气瓶补加阀门
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_ON://判断开进气瓶补加阀门
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,FIRST_TANK,SECOND_GAS)==TRUE)
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
**名称: 延时等待time_delay2---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2_START://延时等待time_delay2计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_DELAY2://判断延时等待time_delay2
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
**名称: 判断气瓶压力是否升高---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO1://采集气瓶压力，第一次
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO1://计时30s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO1://判断定时30s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO2://采集气瓶压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO2://计时30s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO2://判断定时30s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO3://采集气瓶压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_1TANK_2GAS_GAS2_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_1TANK_2GAS_GAS2_TIME_30S_START_NO3://计时30s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO3://判断定时30s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO4://采集气瓶压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO4://计时30s计时开始，第四次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO4://判断定时30s，第四次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO5://采集气瓶压力，第五次
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO5://计时30s计时开始，第五次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO5://判断定时30s，第五次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO6://采集气瓶压力，第六次
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO6://计时30s计时开始，第六次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO6://判断定时30s，第六次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO7://采集气瓶压力，第七次
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO7://计时30s计时开始，第七次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO7://判断定时30s，第七次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO8://采集气瓶压力，第八次
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO8://计时30s计时开始，第八次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO8://判断定时30s，第八次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO9://采集气瓶压力，第九次
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO9://计时30s计时开始，第九次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO9://判断定时30s，第九次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO10://采集气瓶压力，第十次
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,FIRST_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE://压差判断气瓶压力是否升高
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**名称: 判断气瓶抽气是否结束---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IS_COMP_GAS_OVER://判断气瓶抽气是否结束
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,FIRST_TANK,SECOND_GAS)==TRUE)
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
**名称: 关氧路气瓶补加阀门---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1://关氧路气瓶补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1://判断关氧路气瓶补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2://关氧路气瓶补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2://判断关氧路气瓶补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3://关氧路气瓶补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3://判断关氧路气瓶补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
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
**名称: 关进贮箱低压气路补加阀门
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO1://关进贮箱低压气路补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO1://判断关进贮箱低压气路补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO2;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO2://关进贮箱低压气路补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO2://判断关进贮箱低压气路补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO3://关进贮箱低压气路补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO3://判断关进贮箱低压气路补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)
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
**名称: 通过压力判断关进贮箱补加阀
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

//函数待补充！！！！！！！！！！！！！

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_step_is_in_tank_valve_pressure(void)
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
		
		case COMMAND_13_0001_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO1://通过压力判断关进贮箱补加阀，第一组
		{
			
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO2://通过压力判断关进贮箱补加阀，第二组
		{
			
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO3://通过压力判断关进贮箱补加阀，第三组
		{
			
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO4://通过压力判断关进贮箱补加阀，第四组
		{
			
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO5://通过压力判断关进贮箱补加阀，第五组
		{
			
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE://通过压力判断关进贮箱补加阀，五取三
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


/*
*****************************************************************************************************************
---------------------------------两个贮箱抽气，第二个贮箱抽气----------------------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**名称: 开进贮箱低压气路补加阀门---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_step_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_IN_TANK_VALVE_ON://开进贮箱低压气路补加阀门
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				TGTHT510_supply_main_lvb_set(LVb1K);
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				TGTHT510_supply_main_lvb_set(LVb3K);
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				TGTHT510_supply_main_lvb_set(LVb5K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON://判断开进贮箱低压气路补加阀门
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 通过压力判断开进贮箱阀门---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_step_is_in_tank_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE://通过压力判断开补加阀门
		{
			if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O1)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O1)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O2)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O2)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.second_tank_O==DECODE_TANK_O3)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_O3)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 判断抽气气瓶个数---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_step_number_comp_gas(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_NUMBER_COMP_GAS;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_NUMBER_COMP_GAS://判断抽气气瓶个数
		{
			if(TGTHT510_supply_common_number_gas(COMP_TANK_O,SECOND_TANK)==ONE_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else if(TGTHT510_supply_common_number_gas(COMP_TANK_O,SECOND_TANK)==TWO_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else 
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
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

/*
*****************************************************************************************************************
---------------------------------两个贮箱抽气，第二个贮箱抽气，一个气瓶抽气--------------------------------------
*****************************************************************************************************************
*/

/******************************************************************************************
**名称: 开进气瓶补加阀门---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON://开进气瓶补加阀门
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_ON://判断开进气瓶补加阀门
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,SECOND_TANK,FIRST_GAS)==TRUE)
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
**名称: 延时等待time_delay2---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_DELAY2_START://延时等待time_delay2计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_DELAY2://判断延时等待time_delay2
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
**名称: 判断气瓶压力是否升高---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO1://采集气瓶压力，第一次
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_TIME_30S_START_NO1://计时30s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO1://判断定时30s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO2://采集气瓶压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_TIME_30S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_TIME_30S_START_NO2://计时30s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO2;
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO2://判断定时30s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO3://采集气瓶压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_1GAS_TIME_30S_START_NO3;
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_1GAS_TIME_30S_START_NO3://计时30s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO3;
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO3://判断定时30s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO4://采集气瓶压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_1GAS_TIME_30S_START_NO4;
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_1GAS_TIME_30S_START_NO4://计时30s计时开始，第四次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO4;
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO4://判断定时30s，第四次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO5://采集气瓶压力，第五次
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK2_1GAS_TIME_30S_START_NO5;
			break;
		}
		
		case COMMAND_13_0014_O_2TANK_TANK2_1GAS_TIME_30S_START_NO5://计时30s计时开始，第五次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO5;
			break;
		}
		
		case COMMAND_13_0015_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO5://判断定时30s，第五次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0016_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO6://采集气瓶压力，第六次
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK2_1GAS_TIME_30S_START_NO6;
			break;
		}
		
		case COMMAND_13_0017_O_2TANK_TANK2_1GAS_TIME_30S_START_NO6://计时30s计时开始，第六次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO6;
			break;
		}
		
		case COMMAND_13_0018_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO6://判断定时30s，第六次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0019_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO7://采集气瓶压力，第七次
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK2_1GAS_TIME_30S_START_NO7;
			break;
		}
		
		case COMMAND_13_0020_O_2TANK_TANK2_1GAS_TIME_30S_START_NO7://计时30s计时开始，第七次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO7;
			break;
		}
		
		case COMMAND_13_0021_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO7://判断定时30s，第七次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0022_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO8://采集气瓶压力，第八次
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK2_1GAS_TIME_30S_START_NO8;
			break;
		}
		
		case COMMAND_13_0023_O_2TANK_TANK2_1GAS_TIME_30S_START_NO8://计时30s计时开始，第八次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO8;
			break;
		}
		
		case COMMAND_13_0024_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO8://判断定时30s，第八次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0025_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO9://采集气瓶压力，第九次
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_2TANK_TANK2_1GAS_TIME_30S_START_NO9;
			break;
		}
		
		case COMMAND_13_0026_O_2TANK_TANK2_1GAS_TIME_30S_START_NO9://计时30s计时开始，第九次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO9;
			break;
		}
		
		case COMMAND_13_0027_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO9://判断定时30s，第九次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0028_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO10://采集气瓶压力，第十次
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_2TANK_TANK2_1GAS_IS_GAS_PRESSURE;
			break;
		}
		
		case COMMAND_13_0029_O_2TANK_TANK2_1GAS_IS_GAS_PRESSURE://压差判断气瓶压力是否升高
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**名称: 判断气瓶抽气是否结束---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_COMP_GAS_OVER://判断气瓶抽气是否结束
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,SECOND_TANK,FIRST_GAS)==TRUE)
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
**名称: 关氧路气瓶补加阀门---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO1://关氧路气瓶补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO1://判断关氧路气瓶补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO2://关氧路气瓶补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO2;
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO2://判断关氧路气瓶补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO3://关氧路气瓶补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO3;
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO3://判断关氧路气瓶补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
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
**名称: 通过压力判断高压气路隔离是否正常，第一次
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_isolation_first(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO1://计时12s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO1://判断定时12s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO2://计时12s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO2://判断定时12s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO3://采集压气机出口压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO3://计时12s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO3://判断定时12s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO4://采集压气机出口压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_1GAS_FIRST_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_1GAS_FIRST_IS_ISOLATION://通过压力判断高压气路隔离是否正常
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**名称: 关闭氧压气机出口阀门---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_out_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1://关闭氧压气机出口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1://判断关闭氧压气机出口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2://关闭氧压气机出口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2://判断关闭氧压气机出口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3://关闭氧压气机出口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3://判断关闭氧压气机出口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
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
**名称: 通过压力判断高压气路隔离是否正常，第2次
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_isolation_second(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO1://计时12s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO1://判断定时12s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO2://计时12s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO2://判断定时12s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO3://采集压气机出口压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO3://计时12s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO3://判断定时12s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO4://采集压气机出口压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_1GAS_SECOND_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_1GAS_SECOND_IS_ISOLATION://通过压力判断高压气路隔离是否正常
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_ISOLATION);//高压气路隔离异常
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**名称: 氧压气机停机---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP://申请设备管理指令，压气机停机
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为B
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN://判断1min定时
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**名称: 判断氧压气机停机是否正常---第二个贮箱
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

//函数待补充！！！！！！！！！！！！！

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_compressor_stop(void)
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
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO1://采集电机转速，第一次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO2://采集电机转速，第二次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO3://采集电机转速，第三次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO4://采集电机转速，第四次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO5://采集电机转速，第五次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO6://采集电机转速，第六次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO7://采集电机转速，第七次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO8://采集电机转速，第八次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_1GAS_TIME_12S_START://计时12s计时开始
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_1GAS_IS_TIME_12S://判断定时12s
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_STOP://判断氧压气机停机是否正常
		{
			//待补充！！！！
			
			
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
**名称: 开氧压气机旁路自锁阀---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_bypath_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_BYPATH_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_BYPATH_VALVE_ON://开氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_lvb_set(LVb21K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_ON;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_lvb_set(LVb87K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_ON;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_ON://判断开氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 延时等待time_bypath---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay_bypath(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_BYPATH_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_BYPATH_START://延时等待time_bypath计时开启
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_BYPATH;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_BYPATH://判断延时等待time_bypath
		{
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_bypath)==TRUE)
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
**名称: 关氧压气机旁路自锁阀---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_bypath_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF://关氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_lvb_set(LVb21G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_OFF://判断关氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 关闭氧压气机出口阀门---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_out_compressor_valve_off2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1://关闭氧压气机出口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1://判断关闭氧压气机出口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2://关闭氧压气机出口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2://判断关闭氧压气机出口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3://关闭氧压气机出口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3://判断关闭氧压气机出口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
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
**名称: 关闭氧压气机进口阀门---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1://关闭氧压气机进口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb13G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1://判断关闭氧压气机进口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2://关闭氧压气机进口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb15G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2://判断关闭氧压气机进口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3://关闭氧压气机进口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb23G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3://判断关闭氧压气机进口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb23,VALVE_OFF)==TRUE)
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
**名称: 关进贮箱低压气路补加阀门---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO1://关进贮箱低压气路补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO1://判断关进贮箱低压气路补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO2://关进贮箱低压气路补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO2://判断关进贮箱低压气路补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO3://关进贮箱低压气路补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO3://判断关进贮箱低压气路补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)
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
**名称: 设置氧抽气状态好---第二个贮箱
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

//函数待补充！！！！！！！！！！！！！

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_set_state_good(void)
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
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_SET_STATE_GOOD://设置氧抽气状态好
		{
			//待补充！！！！
			
			
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
**名称: 判断压气机温度是否正常---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE://判断压气机温度是否正常
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_COMPRESSOR_TEMPERATURE);//压气机测定温度异常
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
**名称: 判断是否需要进行液冷模块停机
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

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_need_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_NEED_COOLER_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_NEED_COOLER_STOP://判断是否需要进行液冷模块停机
		{
			if(TGTHT510_supply_decode_par.number_tank_F==3)
			{
				//具有第三个补加贮箱，不进行液冷模块停机
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
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
**名称: 延时等待time_delay3---第二个贮箱
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay3(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_DELAY3_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_DELAY3_START://延时等待time_delay3计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_DELAY3;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_DELAY3://判断延时等待time_delay3
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
**名称: 液冷模块停机
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_COOLER_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_COOLER_POWER_OFF://液冷模块停机
		{
			TGTHT510_supply_command_cooler_power_off();
			
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
**名称: 液冷模块状态设置
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_cooler_set(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_COOLER_SET_NO1;
			break;
		}
		
		//液冷模块状态设置1
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_COOLER_SET_NO1:
		{
			TGTHT510_supply_main_lvb_set(LVb35K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO1;
			
			break;
		}
		
		//判断液冷模块状态设置1
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO1:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb35,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_COOLER_SET_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块状态设置2
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_COOLER_SET_NO2:
		{
			TGTHT510_supply_main_lvb_set(LVb28K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO2;
			
			break;
		}
		
		//判断液冷模块状态设置2
		case COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO2:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb28,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_1GAS_COOLER_SET_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块状态设置3
		case COMMAND_13_0005_O_2TANK_TANK2_1GAS_COOLER_SET_NO3:
		{
			TGTHT510_supply_main_lvb_set(LVb30K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO3;
			
			break;
		}
		
		//判断液冷模块状态设置3
		case COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO3:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb30,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_1GAS_COOLER_SET_NO4;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块状态设置4
		case COMMAND_13_0007_O_2TANK_TANK2_1GAS_COOLER_SET_NO4:
		{
			TGTHT510_supply_main_lvb_set(LVb31G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO4;
			
			break;
		}
		
		//判断液冷模块状态设置4
		case COMMAND_13_0008_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO4:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb31,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_1GAS_COOLER_SET_NO5;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置5
		case COMMAND_13_0009_O_2TANK_TANK2_1GAS_COOLER_SET_NO5:
		{
			TGTHT510_supply_main_lvb_set(LVb27G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO5;
			
			break;
		}
		
		//判断液冷模块状态设置5
		case COMMAND_13_0010_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO5:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb27,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_1GAS_COOLER_SET_NO6;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置6
		case COMMAND_13_0011_O_2TANK_TANK2_1GAS_COOLER_SET_NO6:
		{
			TGTHT510_supply_main_lvb_set(LVb29G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO6;
			
			break;
		}
		
		//判断液冷模块状态设置6
		case COMMAND_13_0012_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO6:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb29,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK2_1GAS_COOLER_SET_NO7;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置7
		case COMMAND_13_0013_O_2TANK_TANK2_1GAS_COOLER_SET_NO7:
		{
			TGTHT510_supply_main_lvb_set(LVb33G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO7;
			
			break;
		}
		
		//判断液冷模块状态设置7
		case COMMAND_13_0014_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO7:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb33,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK2_1GAS_COOLER_SET_NO8;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置8
		case COMMAND_13_0015_O_2TANK_TANK2_1GAS_COOLER_SET_NO8:
		{
			TGTHT510_supply_main_lvb_set(LVb37G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO8;
			
			break;
		}
		
		//判断液冷模块状态设置8
		case COMMAND_13_0016_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO8:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb37,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK2_1GAS_COOLER_SET_NO9;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置9
		case COMMAND_13_0017_O_2TANK_TANK2_1GAS_COOLER_SET_NO9:
		{
			TGTHT510_supply_main_lvb_set(LVb32G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO9;
			
			break;
		}
		
		//判断液冷模块状态设置9
		case COMMAND_13_0018_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO9:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb32,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK2_1GAS_COOLER_SET_NO10;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置10
		case COMMAND_13_0019_O_2TANK_TANK2_1GAS_COOLER_SET_NO10:
		{
			TGTHT510_supply_main_lvb_set(LVb34G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO10;
			
			break;
		}
		
		//判断液冷模块状态设置10
		case COMMAND_13_0020_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO10:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb34,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK2_1GAS_COOLER_SET_NO11;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置11
		case COMMAND_13_0021_O_2TANK_TANK2_1GAS_COOLER_SET_NO11:
		{
			TGTHT510_supply_main_lvb_set(LVb36G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO11;
			
			break;
		}
		
		//判断液冷模块状态设置11
		case COMMAND_13_0022_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO11:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb36,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK2_1GAS_COOLER_SET_NO12;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置12
		case COMMAND_13_0023_O_2TANK_TANK2_1GAS_COOLER_SET_NO12:
		{
			TGTHT510_supply_main_lvb_set(LVb38G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO12;
			
			break;
		}
		
		//判断液冷模块状态设置12
		case COMMAND_13_0024_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO12:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb38,VALVE_OFF)==TRUE)
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
**名称: 申请压气机断电
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_compressor_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN://判断计时1min是否到
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**名称: 申请电机驱动器断电
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_TGTHT530_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530a_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_1GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_1GAS_TGTHT530_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_1GAS_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_1GAS_TGTHT530_IS_TIME_1MIN://判断计时1min是否到
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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


/*
*****************************************************************************************************************
---------------------------------两个贮箱抽气，第二个贮箱抽气，两个气瓶抽气--------------------------------------
*****************************************************************************************************************
*/


/******************************************************************************************
**名称: 开进气瓶补加阀门---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON://开进气瓶补加阀门
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_ON://判断开进气瓶补加阀门
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,SECOND_TANK,FIRST_GAS)==TRUE)
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
**名称: 延时等待time_delay2---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2_START://延时等待time_delay2计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_DELAY2://判断延时等待time_delay2
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
**名称: 判断气瓶压力是否升高---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO1://采集气瓶压力，第一次
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO1://计时30s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO1://判断定时30s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO2://采集气瓶压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO2://计时30s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO2://判断定时30s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO3://采集气瓶压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO3://计时30s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO3://判断定时30s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO4://采集气瓶压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO4://计时30s计时开始，第四次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO4://判断定时30s，第四次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO5://采集气瓶压力，第五次
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO5://计时30s计时开始，第五次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO5://判断定时30s，第五次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO6://采集气瓶压力，第六次
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO6://计时30s计时开始，第六次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO6://判断定时30s，第六次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO7://采集气瓶压力，第七次
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO7://计时30s计时开始，第七次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO7://判断定时30s，第七次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO8://采集气瓶压力，第八次
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO8://计时30s计时开始，第八次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO8://判断定时30s，第八次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO9://采集气瓶压力，第九次
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO9://计时30s计时开始，第九次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO9://判断定时30s，第九次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO10://采集气瓶压力，第十次
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE://压差判断气瓶压力是否升高
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**名称: 判断气瓶抽气是否结束---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IS_COMP_GAS_OVER://判断气瓶抽气是否结束
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,SECOND_TANK,FIRST_GAS)==TRUE)
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
**名称: 关氧路气瓶补加阀门---第一个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1://关氧路气瓶补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1://判断关氧路气瓶补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2://关氧路气瓶补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2://判断关氧路气瓶补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3://关氧路气瓶补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3://判断关氧路气瓶补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
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
**名称: 开进气瓶补加阀门---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON://开进气瓶补加阀门
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_ON://判断开进气瓶补加阀门
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_O,SECOND_TANK,SECOND_GAS)==TRUE)
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
**名称: 延时等待time_delay2---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2_START://延时等待time_delay2计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_DELAY2://判断延时等待time_delay2
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
**名称: 判断气瓶压力是否升高---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO1://采集气瓶压力，第一次
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO1://计时30s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO1://判断定时30s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO2://采集气瓶压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO2://计时30s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO2://判断定时30s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO3://采集气瓶压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO3://计时30s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO3://判断定时30s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO4://采集气瓶压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO4://计时30s计时开始，第四次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO4://判断定时30s，第四次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO5://采集气瓶压力，第五次
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_13_0014_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO5://计时30s计时开始，第五次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_13_0015_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO5://判断定时30s，第五次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0016_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO6://采集气瓶压力，第六次
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_13_0017_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO6://计时30s计时开始，第六次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_13_0018_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO6://判断定时30s，第六次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0019_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO7://采集气瓶压力，第七次
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_13_0020_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO7://计时30s计时开始，第七次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_13_0021_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO7://判断定时30s，第七次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0022_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO8://采集气瓶压力，第八次
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_13_0023_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO8://计时30s计时开始，第八次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_13_0024_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO8://判断定时30s，第八次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0025_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0025_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO9://采集气瓶压力，第九次
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0026_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_13_0026_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO9://计时30s计时开始，第九次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0027_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_13_0027_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO9://判断定时30s，第九次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0028_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0028_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO10://采集气瓶压力，第十次
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_O,SECOND_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0029_O_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_13_0029_O_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE://压差判断气瓶压力是否升高
		{
			if(TGTHT510_supply_common_is_gas_pressure(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_GAS_PRESSURE);
			}
			
			for(i=0;i<=9;i++)
			{
				temp_global[i]=0;
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
**名称: 判断气瓶抽气是否结束---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IS_COMP_GAS_OVER://判断气瓶抽气是否结束
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_O,SECOND_TANK,SECOND_GAS)==TRUE)
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
**名称: 关氧路气瓶补加阀门---第二个气瓶
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1://关氧路气瓶补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb7G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1://判断关氧路气瓶补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb07,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2://关氧路气瓶补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb9G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2://判断关氧路气瓶补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb09,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3://关氧路气瓶补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb11G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3://判断关氧路气瓶补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb11,VALVE_OFF)==TRUE)
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
**名称: 通过压力判断高压气路隔离是否正常，第一次
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_isolation_first(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO1://计时12s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO1://判断定时12s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO2://计时12s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO2://判断定时12s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO3://采集压气机出口压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO3://计时12s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO3://判断定时12s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO4://采集压气机出口压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_2GAS_FIRST_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_2GAS_FIRST_IS_ISOLATION://通过压力判断高压气路隔离是否正常
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**名称: 关闭氧压气机出口阀门
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_out_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1://关闭氧压气机出口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1://判断关闭氧压气机出口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2://关闭氧压气机出口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2://判断关闭氧压气机出口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3://关闭氧压气机出口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3://判断关闭氧压气机出口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
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
**名称: 通过压力判断高压气路隔离是否正常，第2次
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_isolation_second(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO1://计时12s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO1://判断定时12s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO2://计时12s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO2://判断定时12s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO3://采集压气机出口压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO3://计时12s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO3://判断定时12s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO4://采集压气机出口压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_O);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_2GAS_SECOND_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_2GAS_SECOND_IS_ISOLATION://通过压力判断高压气路隔离是否正常
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_ISOLATION);//高压气路隔离异常
			}
			
			for(i=0;i<=3;i++)
			{
				temp_global[i]=0;
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
**名称: 氧压气机停机
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP://申请设备管理指令，压气机停机
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN://判断1min定时
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**名称: 判断氧压气机停机是否正常
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

//该函数待修改！！！！！！！！！！！！！

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_compressor_stop(void)
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
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO1://采集电机转速，第一次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO2://采集电机转速，第二次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO3://采集电机转速，第三次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO4://采集电机转速，第四次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO5://采集电机转速，第五次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO6://采集电机转速，第六次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0007_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO7://采集电机转速，第七次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0008_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO8://采集电机转速，第八次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0009_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0010_O_2TANK_TANK2_2GAS_TIME_12S_START://计时12s计时开始
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0011_O_2TANK_TANK2_2GAS_IS_TIME_12S://判断定时12s
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0012_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_13_0013_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_STOP://判断氧压气机停机是否正常
		{
			//待补充！！！！
			
			
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
**名称: 开氧压气机旁路自锁阀
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_bypath_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_BYPATH_VALVE_ON;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_BYPATH_VALVE_ON://开氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_lvb_set(LVb21K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_ON;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_lvb_set(LVb87K);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_ON;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_ON://判断开氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 延时等待time_bypath
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_time_delay_bypath(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_TIME_BYPATH_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_TIME_BYPATH_START://延时等待time_bypath计时开启
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_TIME_BYPATH;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_TIME_BYPATH://判断延时等待time_bypath
		{
			if(TGTHT510_supply_time_step_is_get(TGTHT510_supply_input_par.time_bypath)==TRUE)
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
**名称: 关氧压气机旁路自锁阀
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_bypath_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF://关氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_lvb_set(LVb21G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_OFF://判断关氧压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb21,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb87,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
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
**名称: 关闭氧压气机出口阀门
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_out_compressor_valve_off2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1://关闭氧压气机出口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb17G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1://判断关闭氧压气机出口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb17,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2://关闭氧压气机出口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb19G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2://判断关闭氧压气机出口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb19,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3://关闭氧压气机出口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb25G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3://判断关闭氧压气机出口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb25,VALVE_OFF)==TRUE)
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
**名称: 关闭氧压气机进口阀门
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_in_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1://关闭氧压气机进口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb13G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1://判断关闭氧压气机进口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb13,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2://关闭氧压气机进口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb15G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2://判断关闭氧压气机进口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb15,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3://关闭氧压气机进口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb23G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3://判断关闭氧压气机进口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb23,VALVE_OFF)==TRUE)
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
**名称: 关进贮箱低压气路补加阀门
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO1://关进贮箱低压气路补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb1G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO1://判断关进贮箱低压气路补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb01,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO2;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO2://关进贮箱低压气路补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb3G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO2://判断关进贮箱低压气路补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb03,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO3://关进贮箱低压气路补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb5G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO3://判断关进贮箱低压气路补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb05,VALVE_OFF)==TRUE)
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
**名称: 设置氧抽气状态好
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

//待补充！！！！

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_set_state_good(void)
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
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_SET_STATE_GOOD://设置氧抽气状态好
		{
			//待补充！！！！
			
			
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
**名称: 判断压气机温度是否正常
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE://判断压气机温度是否正常
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_O)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_COMPRESSOR_TEMPERATURE);//压气机测定温度异常
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
**名称: 判断是否需要进行液冷模块停机
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

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_need_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_NEED_COOLER_STOP;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_NEED_COOLER_STOP://判断是否需要进行液冷模块停机
		{
			if(TGTHT510_supply_decode_par.number_tank_F==3)
			{
				//具有第三个补加贮箱，不进行液冷模块停机
				TGTHT510_supply_ctrl.step=STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
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
**名称: 延时等待time_delay3
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_time_delay3(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_TIME_DELAY3_START;
			break;
		}
		
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_TIME_DELAY3_START://延时等待time_delay3计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_TIME_DELAY3;
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_TIME_DELAY3://判断延时等待time_delay3
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
**名称: 液冷模块停机
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_COOLER_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_COOLER_POWER_OFF://液冷模块停机
		{
			TGTHT510_supply_command_cooler_power_off();
			
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
**名称: 液冷模块状态设置
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_cooler_set(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_COOLER_SET_NO1;
			break;
		}
		
		//液冷模块状态设置1
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_COOLER_SET_NO1:
		{
			TGTHT510_supply_main_lvb_set(LVb35K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO1;
			
			break;
		}
		
		//判断液冷模块状态设置1
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO1:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb35,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_COOLER_SET_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块状态设置2
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_COOLER_SET_NO2:
		{
			TGTHT510_supply_main_lvb_set(LVb28K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO2;
			
			break;
		}
		
		//判断液冷模块状态设置2
		case COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO2:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb28,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0005_O_2TANK_TANK2_2GAS_COOLER_SET_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块状态设置3
		case COMMAND_13_0005_O_2TANK_TANK2_2GAS_COOLER_SET_NO3:
		{
			TGTHT510_supply_main_lvb_set(LVb30K);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO3;
			
			break;
		}
		
		//判断液冷模块状态设置3
		case COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO3:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb30,VALVE_ON)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0007_O_2TANK_TANK2_2GAS_COOLER_SET_NO4;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块状态设置4
		case COMMAND_13_0007_O_2TANK_TANK2_2GAS_COOLER_SET_NO4:
		{
			TGTHT510_supply_main_lvb_set(LVb31G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0008_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO4;
			
			break;
		}
		
		//判断液冷模块状态设置4
		case COMMAND_13_0008_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO4:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb31,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0009_O_2TANK_TANK2_2GAS_COOLER_SET_NO5;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置5
		case COMMAND_13_0009_O_2TANK_TANK2_2GAS_COOLER_SET_NO5:
		{
			TGTHT510_supply_main_lvb_set(LVb27G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0010_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO5;
			
			break;
		}
		
		//判断液冷模块状态设置5
		case COMMAND_13_0010_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO5:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb27,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0011_O_2TANK_TANK2_2GAS_COOLER_SET_NO6;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置6
		case COMMAND_13_0011_O_2TANK_TANK2_2GAS_COOLER_SET_NO6:
		{
			TGTHT510_supply_main_lvb_set(LVb29G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0012_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO6;
			
			break;
		}
		
		//判断液冷模块状态设置6
		case COMMAND_13_0012_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO6:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb29,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0013_O_2TANK_TANK2_2GAS_COOLER_SET_NO7;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置7
		case COMMAND_13_0013_O_2TANK_TANK2_2GAS_COOLER_SET_NO7:
		{
			TGTHT510_supply_main_lvb_set(LVb33G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0014_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO7;
			
			break;
		}
		
		//判断液冷模块状态设置7
		case COMMAND_13_0014_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO7:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb33,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0015_O_2TANK_TANK2_2GAS_COOLER_SET_NO8;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置8
		case COMMAND_13_0015_O_2TANK_TANK2_2GAS_COOLER_SET_NO8:
		{
			TGTHT510_supply_main_lvb_set(LVb37G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0016_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO8;
			
			break;
		}
		
		//判断液冷模块状态设置8
		case COMMAND_13_0016_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO8:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb37,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0017_O_2TANK_TANK2_2GAS_COOLER_SET_NO9;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置9
		case COMMAND_13_0017_O_2TANK_TANK2_2GAS_COOLER_SET_NO9:
		{
			TGTHT510_supply_main_lvb_set(LVb32G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0018_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO9;
			
			break;
		}
		
		//判断液冷模块状态设置9
		case COMMAND_13_0018_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO9:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb32,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0019_O_2TANK_TANK2_2GAS_COOLER_SET_NO10;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置10
		case COMMAND_13_0019_O_2TANK_TANK2_2GAS_COOLER_SET_NO10:
		{
			TGTHT510_supply_main_lvb_set(LVb34G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0020_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO10;
			
			break;
		}
		
		//判断液冷模块状态设置10
		case COMMAND_13_0020_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO10:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb34,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0021_O_2TANK_TANK2_2GAS_COOLER_SET_NO11;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置11
		case COMMAND_13_0021_O_2TANK_TANK2_2GAS_COOLER_SET_NO11:
		{
			TGTHT510_supply_main_lvb_set(LVb36G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0022_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO11;
			
			break;
		}
		
		//判断液冷模块状态设置11
		case COMMAND_13_0022_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO11:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb36,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_13_0023_O_2TANK_TANK2_2GAS_COOLER_SET_NO12;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		//液冷模块状态设置12
		case COMMAND_13_0023_O_2TANK_TANK2_2GAS_COOLER_SET_NO12:
		{
			TGTHT510_supply_main_lvb_set(LVb38G);
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0024_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO12;
			
			break;
		}
		
		//判断液冷模块状态设置12
		case COMMAND_13_0024_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO12:
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb38,VALVE_OFF)==TRUE)
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
**名称: 申请压气机断电
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_compressor_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_A_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN://判断计时1min是否到
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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
**名称: 申请电机驱动器断电
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
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_TGTHT530_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_13_0001_O_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF;
			break;
		}
	
		case COMMAND_13_0001_O_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)//氧压气机为A
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530a_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)//氧压气机为C
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_13_0002_O_2TANK_TANK2_2GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_13_0002_O_2TANK_TANK2_2GAS_TGTHT530_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_13_0003_O_2TANK_TANK2_2GAS_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_13_0003_O_2TANK_TANK2_2GAS_TGTHT530_IS_TIME_1MIN://判断计时1min是否到
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
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


/*
*****************************************************************************************************************
---------------------------------------------------------通用函数------------------------------------------------
*****************************************************************************************************************
*/



