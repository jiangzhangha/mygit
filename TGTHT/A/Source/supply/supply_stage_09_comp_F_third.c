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
**名称：补加阶段9
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_stage09_comp_F_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_09_F_INIT_START_COOLER;
			
			break;
		}

//----------------------------------初始设置阶段------------------------------------------------------
		
		//启动液冷泵工作
		case STEP_09_F_INIT_START_COOLER:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_start_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_INIT_IS_COOLER_WORK;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过转速判断液冷工作是否正常
		case STEP_09_F_INIT_IS_COOLER_WORK:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_is_cooler_work()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_INIT_DELAY;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待时间
		case STEP_09_F_INIT_DELAY:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_INIT_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机温度是否正常
		case STEP_09_F_INIT_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_INIT_TGTHT530_POWER_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请电机驱动器加电
		case STEP_09_F_INIT_TGTHT530_POWER_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_TGTHT530_power_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_INIT_COMPRESSOR_POWER_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请压气机加电
		case STEP_09_F_INIT_COMPRESSOR_POWER_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_compressor_power_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_INIT_ISOLATION;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//贮箱隔离
		case STEP_09_F_INIT_ISOLATION:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_isolation()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_IN_TANK_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
//----------------------------------一个贮箱抽气------------------------------------------------------

		//开进贮箱低压气路补加阀门
		case STEP_09_F_1TANK_IN_TANK_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_in_tank_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_TIME_DELAY_A;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待时间
		case STEP_09_F_1TANK_TIME_DELAY_A:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断开进贮箱低压气路补加阀门
		case STEP_09_F_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_is_in_tank_valve_on_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_IN_COMPRESSOR_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开燃压气机进口阀门
		case STEP_09_F_1TANK_IN_COMPRESSOR_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_in_compressor_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_TIME_DELAY1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay1
		case STEP_09_F_1TANK_TIME_DELAY1:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_time_delay1()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_IS_IN_COMPRESSOR_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机进口压力是否正常
		case STEP_09_F_1TANK_IS_IN_COMPRESSOR_PRESSURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_is_in_compressor_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_COMPRESSOR_START;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//燃压气机启动
		case STEP_09_F_1TANK_COMPRESSOR_START:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_compressor_start()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_TIME_DELAY_B;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待时间
		case STEP_09_F_1TANK_TIME_DELAY_B:
		{
			if(TGTHT510_supply_stage09_comp_F_init_step_time_delay()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_IS_OUT_COMPRESSOR_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机出口压力是否正常
		case STEP_09_F_1TANK_IS_OUT_COMPRESSOR_PRESSURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_is_out_compressor_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_OUT_COMPRESSOR_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开燃压气机出口阀门
		case STEP_09_F_1TANK_OUT_COMPRESSOR_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_step_out_compressor_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_NUMBER_COMP_GAS;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断抽气气瓶个数
		case STEP_09_F_1TANK_NUMBER_COMP_GAS:
		{
			TGTHT510_supply_stage09_comp_F_1tank_step_number_comp_gas();
			
			break;
		}

//----------------------------------一个贮箱抽气、一个气瓶抽气----------------------------------------

		//开进气瓶补加阀门
		case STEP_09_F_1TANK_1GAS_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay2
		case STEP_09_F_1TANK_1GAS_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶压力是否升高
		case STEP_09_F_1TANK_1GAS_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶抽气是否结束
		case STEP_09_F_1TANK_1GAS_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关燃路气瓶补加阀门
		case STEP_09_F_1TANK_1GAS_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_ISOLATION_FIRST;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断高压气路隔离是否正常，第一次
		case STEP_09_F_1TANK_1GAS_IS_ISOLATION_FIRST:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_isolation_first()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭燃压气机出口阀门
		case STEP_09_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_out_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_ISOLATION_SECOND;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断高压气路隔离是否正常，第二次
		case STEP_09_F_1TANK_1GAS_IS_ISOLATION_SECOND:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_isolation_second()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//燃压气机停机
		case STEP_09_F_1TANK_1GAS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断燃压气机停机是否正常
		case STEP_09_F_1TANK_1GAS_IS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_BYPATH_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开燃压气机旁路自锁阀
		case STEP_09_F_1TANK_1GAS_BYPATH_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_bypath_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_TIME_DELAY_BYPATH;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_bypath
		case STEP_09_F_1TANK_1GAS_TIME_DELAY_BYPATH:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay_bypath()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关燃压气机旁路自锁阀
		case STEP_09_F_1TANK_1GAS_BYPATH_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_bypath_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭燃压气机出口阀门，第二次
		case STEP_09_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_out_compressor_valve_off2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭燃压气机进口阀门
		case STEP_09_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关进贮箱低压气路补加阀门
		case STEP_09_F_1TANK_1GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_SET_STATE_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//设置燃抽气状态好
		case STEP_09_F_1TANK_1GAS_SET_STATE_GOOD:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_set_state_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机温度是否正常
		case STEP_09_F_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_TIME_DELAY3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay3
		case STEP_09_F_1TANK_1GAS_TIME_DELAY3:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay3()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//启动液冷模块切换程序
		case STEP_09_F_1TANK_1GAS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断液冷模块切换是否正常
		case STEP_09_F_1TANK_1GAS_IS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//液冷模块停机
		case STEP_09_F_1TANK_1GAS_COOLER_STOP:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_COMPRESSOR_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请压气机断电
		case STEP_09_F_1TANK_1GAS_COMPRESSOR_POWER_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_compressor_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_TGTHT530_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请电机驱动器断电
		case STEP_09_F_1TANK_1GAS_TGTHT530_POWER_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_1gas_step_TGTHT530_power_off()==TRUE)
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
		case STEP_09_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS1_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay2---第一个气瓶
		case STEP_09_F_1TANK_2GAS_GAS1_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS1_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶压力是否升高---第一个气瓶
		case STEP_09_F_1TANK_2GAS_GAS1_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS1_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶抽气是否结束---第一个气瓶
		case STEP_09_F_1TANK_2GAS_GAS1_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关燃路气瓶补加阀门---第一个气瓶
		case STEP_09_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开进气瓶补加阀门---第二个气瓶
		case STEP_09_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_in_gas_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS2_TIME_DELAY2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay2---第二个气瓶
		case STEP_09_F_1TANK_2GAS_GAS2_TIME_DELAY2:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_time_delay2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS2_IS_GAS_PRESSURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶压力是否升高---第二个气瓶
		case STEP_09_F_1TANK_2GAS_GAS2_IS_GAS_PRESSURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_is_gas_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS2_IS_COMP_OVER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断气瓶抽气是否结束---第二个气瓶
		case STEP_09_F_1TANK_2GAS_GAS2_IS_COMP_OVER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_is_comp_over()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关燃路气瓶补加阀门---第二个气瓶
		case STEP_09_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_in_gas_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IS_ISOLATION_FIRST;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断高压气路隔离是否正常，第一次
		case STEP_09_F_1TANK_2GAS_IS_ISOLATION_FIRST:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_isolation_first()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭燃压气机出口阀门
		case STEP_09_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_out_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IS_ISOLATION_SECOND;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断高压气路隔离是否正常，第二次
		case STEP_09_F_1TANK_2GAS_IS_ISOLATION_SECOND:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_isolation_second()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//燃压气机停机
		case STEP_09_F_1TANK_2GAS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IS_COMPRESSOR_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断燃压气机停机是否正常
		case STEP_09_F_1TANK_2GAS_IS_COMPRESSOR_STOP:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_compressor_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_BYPATH_VALVE_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//开燃压气机旁路自锁阀
		case STEP_09_F_1TANK_2GAS_BYPATH_VALVE_ON:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_bypath_valve_on()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_TIME_DELAY_BYPATH;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_bypath
		case STEP_09_F_1TANK_2GAS_TIME_DELAY_BYPATH:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_time_delay_bypath()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关燃压气机旁路自锁阀
		case STEP_09_F_1TANK_2GAS_BYPATH_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_bypath_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭燃压气机出口阀门，第二次
		case STEP_09_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_out_compressor_valve_off2()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关闭燃压气机进口阀门
		case STEP_09_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_in_compressor_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IN_TANK_VALVE_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//关进贮箱低压气路补加阀门
		case STEP_09_F_1TANK_2GAS_IN_TANK_VALVE_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_in_tank_valve_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_SET_STATE_GOOD;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//设置燃抽气状态好
		case STEP_09_F_1TANK_2GAS_SET_STATE_GOOD:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_set_state_good()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断压气机温度是否正常
		case STEP_09_F_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_compressor_temperature()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_TIME_DELAY3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//延时等待time_delay3
		case STEP_09_F_1TANK_2GAS_TIME_DELAY3:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_time_delay3()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//启动液冷模块切换程序
		case STEP_09_F_1TANK_2GAS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_IS_EXCHANGE_COOLER;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//通过压力判断液冷模块切换是否正常
		case STEP_09_F_1TANK_2GAS_IS_EXCHANGE_COOLER:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_exchange_cooler()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_COOLER_STOP;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//液冷模块停机
		case STEP_09_F_1TANK_2GAS_COOLER_STOP:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_cooler_stop()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_COMPRESSOR_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请压气机断电
		case STEP_09_F_1TANK_2GAS_COMPRESSOR_POWER_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_compressor_power_off()==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_TGTHT530_POWER_OFF;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//申请电机驱动器断电
		case STEP_09_F_1TANK_2GAS_TGTHT530_POWER_OFF:
		{
			if(TGTHT510_supply_stage09_comp_F_1tank_2gas_step_TGTHT530_power_off()==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_init_step_start_cooler(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_INIT_COOLER_VALVE_ON_NO1;
			break;
		}
		
		//液冷模块补加系统阀门开第一组
		case COMMAND_09_0001_F_INIT_COOLER_VALVE_ON_NO1:
		{
			TGTHT510_supply_command_cooler_valve_on(1);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_IS_COOLER_VALVE_ON_NO1;
			
			break;
		}
		
		//判断液冷模块补加系统阀门开第一组
		case COMMAND_09_0002_F_INIT_IS_COOLER_VALVE_ON_NO1:
		{
			if(TGTHT510_supply_command_is_cooler_valve_on(1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_INIT_COOLER_VALVE_ON_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块补加系统阀门开第二组
		case COMMAND_09_0003_F_INIT_COOLER_VALVE_ON_NO2:
		{
			TGTHT510_supply_command_cooler_valve_on(2);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_INIT_IS_COOLER_VALVE_ON_NO2;
			
			break;
		}
		
		//判断液冷模块补加系统阀门开第二组
		case COMMAND_09_0004_F_INIT_IS_COOLER_VALVE_ON_NO2:
		{
			if(TGTHT510_supply_command_is_cooler_valve_on(2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_INIT_COOLER_POWER_ON;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
			}
			
			break;
		}
		
		//液冷模块供电通
		case COMMAND_09_0005_F_INIT_COOLER_POWER_ON:
		{
			TGTHT510_supply_command_cooler_power_on();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_INIT_TIME_1MIN_START;
			
			break;
		}
		
		//延时1min计时开始
		case COMMAND_09_0006_F_INIT_TIME_1MIN_START:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_INIT_IS_TIME_1MIN;
			
			break;
		}
		
		//延时1min是否到
		case COMMAND_09_0007_F_INIT_IS_TIME_1MIN:
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

uint16 TGTHT510_supply_stage09_comp_F_init_step_is_cooler_work(void)
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
		
		case COMMAND_09_0001_F_INIT_IS_COOLER_WORK:
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
uint16 TGTHT510_supply_stage09_comp_F_init_step_time_delay(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_INIT_TIME_DELAY_START;
			break;
		}
		
		case COMMAND_09_0001_F_INIT_TIME_DELAY_START://延时等待time_delay1计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_IS_TIME_DELAY;
	
			break;
		}
		
		case COMMAND_09_0002_F_INIT_IS_TIME_DELAY://判断延时等待time_delay1
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
uint16 TGTHT510_supply_stage09_comp_F_init_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_INIT_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_09_0001_F_INIT_IS_COMPRESSOR_TEMPERATURE:
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_F)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_init_step_TGTHT530_power_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_INIT_TGTHT530_POWER_ON;
			break;
		}
		
		case COMMAND_09_0001_F_INIT_TGTHT530_POWER_ON://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530b_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			break;
		}
		
		case COMMAND_09_0002_F_INIT_TGTHT530_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_INIT_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_INIT_TGTHT530_IS_TIME_1MIN://判断计时1min是否到
		{
			
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_INIT_TGTHT530_IS_POWER_ON;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0004_F_INIT_TGTHT530_IS_POWER_ON://通过互传数据判断加电是否正常
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
uint16 TGTHT510_supply_stage09_comp_F_init_step_compressor_power_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_INIT_COMPRESSOR_POWER_ON;
			break;
		}
		
		case COMMAND_09_0001_F_INIT_COMPRESSOR_POWER_ON://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_B_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_ON_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}

			break;
		}
		
		case COMMAND_09_0002_F_INIT_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_INIT_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_INIT_COMPRESSOR_IS_TIME_1MIN://判断计时1min是否到
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
uint16 TGTHT510_supply_stage09_comp_F_init_step_isolation(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_INIT_ISOLATION_VALVE_OFF_NO1;
			break;
		}
		
		//隔离推进系统自锁阀关闭，第一组
		case COMMAND_09_0001_F_INIT_ISOLATION_VALVE_OFF_NO1:
		{
			TGTHT510_supply_command_third_isolation_valve_off(1,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_INIT_TIME_1MIN_START_NO1;
			
			break;
		}
		
		//延时1min计时开始，第一组
		case COMMAND_09_0002_F_INIT_TIME_1MIN_START_NO1:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_INIT_IS_TIME_1MIN_NO1;
			
			break;
		}
		
		//延时1min是否到，第一组
		case COMMAND_09_0003_F_INIT_IS_TIME_1MIN_NO1:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_INIT_IS_ISOLATION_VALVE_OFF_NO1;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第一组
		case COMMAND_09_0004_F_INIT_IS_ISOLATION_VALVE_OFF_NO1:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(1,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_INIT_ISOLATION_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第二组
		case COMMAND_09_0005_F_INIT_ISOLATION_VALVE_OFF_NO2:
		{
			TGTHT510_supply_command_third_isolation_valve_off(2,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_INIT_TIME_1MIN_START_NO2;
			
			break;
		}
		
		//延时1min计时开始，第二组
		case COMMAND_09_0006_F_INIT_TIME_1MIN_START_NO2:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_INIT_IS_TIME_1MIN_NO2;
			
			break;
		}
		
		//延时1min是否到，第二组
		case COMMAND_09_0007_F_INIT_IS_TIME_1MIN_NO2:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_INIT_IS_ISOLATION_VALVE_OFF_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第二组
		case COMMAND_09_0008_F_INIT_IS_ISOLATION_VALVE_OFF_NO2:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(2,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_INIT_ISOLATION_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第三组
		case COMMAND_09_0009_F_INIT_ISOLATION_VALVE_OFF_NO3:
		{
			TGTHT510_supply_command_third_isolation_valve_off(3,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_INIT_TIME_1MIN_START_NO3;
			
			break;
		}
		
		//延时1min计时开始，第三组
		case COMMAND_09_0010_F_INIT_TIME_1MIN_START_NO3:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_INIT_IS_TIME_1MIN_NO3;
			
			break;
		}
		
		//延时1min是否到，第三组
		case COMMAND_09_0011_F_INIT_IS_TIME_1MIN_NO3:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0012_F_INIT_IS_ISOLATION_VALVE_OFF_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第三组
		case COMMAND_09_0012_F_INIT_IS_ISOLATION_VALVE_OFF_NO3:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(3,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0013_F_INIT_ISOLATION_VALVE_OFF_NO4;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第四组
		case COMMAND_09_0013_F_INIT_ISOLATION_VALVE_OFF_NO4:
		{
			TGTHT510_supply_command_third_isolation_valve_off(4,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0014_F_INIT_TIME_1MIN_START_NO4;
			
			break;
		}
		
		//延时1min计时开始，第四组
		case COMMAND_09_0014_F_INIT_TIME_1MIN_START_NO4:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0015_F_INIT_IS_TIME_1MIN_NO4;
			
			break;
		}
		
		//延时1min是否到，第四组
		case COMMAND_09_0015_F_INIT_IS_TIME_1MIN_NO4:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0016_F_INIT_IS_ISOLATION_VALVE_OFF_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第四组
		case COMMAND_09_0016_F_INIT_IS_ISOLATION_VALVE_OFF_NO4:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(4,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0017_F_INIT_ISOLATION_VALVE_OFF_NO5;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第五组
		case COMMAND_09_0017_F_INIT_ISOLATION_VALVE_OFF_NO5:
		{
			TGTHT510_supply_command_third_isolation_valve_off(5,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0018_F_INIT_TIME_1MIN_START_NO5;
			
			break;
		}
		
		//延时1min计时开始，第五组
		case COMMAND_09_0018_F_INIT_TIME_1MIN_START_NO5:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0019_F_INIT_IS_TIME_1MIN_NO5;
			
			break;
		}
		
		//延时1min是否到，第五组
		case COMMAND_09_0019_F_INIT_IS_TIME_1MIN_NO5:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0020_F_INIT_IS_ISOLATION_VALVE_OFF_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第五组
		case COMMAND_09_0020_F_INIT_IS_ISOLATION_VALVE_OFF_NO5:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(5,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0021_F_INIT_ISOLATION_VALVE_OFF_NO6;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第六组
		case COMMAND_09_0021_F_INIT_ISOLATION_VALVE_OFF_NO6:
		{
			TGTHT510_supply_command_third_isolation_valve_off(6,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0022_F_INIT_TIME_1MIN_START_NO6;
			
			break;
		}
		
		//延时1min计时开始，第六组
		case COMMAND_09_0022_F_INIT_TIME_1MIN_START_NO6:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0023_F_INIT_IS_TIME_1MIN_NO6;
			
			break;
		}
		
		//延时1min是否到，第六组
		case COMMAND_09_0023_F_INIT_IS_TIME_1MIN_NO6:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0024_F_INIT_IS_ISOLATION_VALVE_OFF_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第六组
		case COMMAND_09_0024_F_INIT_IS_ISOLATION_VALVE_OFF_NO6:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(6,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0025_F_INIT_ISOLATION_VALVE_OFF_NO7;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第七组
		case COMMAND_09_0025_F_INIT_ISOLATION_VALVE_OFF_NO7:
		{
			TGTHT510_supply_command_third_isolation_valve_off(7,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0026_F_INIT_TIME_1MIN_START_NO7;
			
			break;
		}
		
		//延时1min计时开始，第七组
		case COMMAND_09_0026_F_INIT_TIME_1MIN_START_NO7:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0027_F_INIT_IS_TIME_1MIN_NO7;
			
			break;
		}
		
		//延时1min是否到，第七组
		case COMMAND_09_0027_F_INIT_IS_TIME_1MIN_NO7:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0028_F_INIT_IS_ISOLATION_VALVE_OFF_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第七组
		case COMMAND_09_0028_F_INIT_IS_ISOLATION_VALVE_OFF_NO7:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(7,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0029_F_INIT_ISOLATION_VALVE_OFF_NO8;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第八组
		case COMMAND_09_0029_F_INIT_ISOLATION_VALVE_OFF_NO8:
		{
			TGTHT510_supply_command_third_isolation_valve_off(8,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0030_F_INIT_TIME_1MIN_START_NO8;
			
			break;
		}
		
		//延时1min计时开始，第八组
		case COMMAND_09_0030_F_INIT_TIME_1MIN_START_NO8:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0031_F_INIT_IS_TIME_1MIN_NO8;
			
			break;
		}
		
		//延时1min是否到，第八组
		case COMMAND_09_0031_F_INIT_IS_TIME_1MIN_NO8:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0032_F_INIT_IS_ISOLATION_VALVE_OFF_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第八组
		case COMMAND_09_0032_F_INIT_IS_ISOLATION_VALVE_OFF_NO8:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(8,ISOLATION_TANK_F))==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0033_F_INIT_ISOLATION_VALVE_OFF_NO9;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_TUIJIN_VALVE_OFF);//阀门关闭错误，暂停，下传错误代码
			}
			
			break;
		}
		
		//隔离推进系统自锁阀关闭，第九组
		case COMMAND_09_0033_F_INIT_ISOLATION_VALVE_OFF_NO9:
		{
			TGTHT510_supply_command_third_isolation_valve_off(9,ISOLATION_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0034_F_INIT_TIME_1MIN_START_NO9;
			
			break;
		}
		
		//延时1min计时开始，第九组
		case COMMAND_09_0034_F_INIT_TIME_1MIN_START_NO9:
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0035_F_INIT_IS_TIME_1MIN_NO9;
			
			break;
		}
		
		//延时1min是否到，第九组
		case COMMAND_09_0035_F_INIT_IS_TIME_1MIN_NO9:
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0036_F_INIT_IS_ISOLATION_VALVE_OFF_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		//判断隔离推进系统自锁阀关闭，第九组
		case COMMAND_09_0036_F_INIT_IS_ISOLATION_VALVE_OFF_NO9:
		{
			if((TGTHT510_supply_command_is_third_isolation_valve_off(9,ISOLATION_TANK_F))==TRUE)
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


/*
*****************************************************************************************************************
-------------------------------------------------第三个贮箱抽气----------------------------------------------------
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_in_tank_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_IN_TANK_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_IN_TANK_VALVE_ON://开进贮箱低压气路补加阀门
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				TGTHT510_supply_main_lvb_set(LVb2K);
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				TGTHT510_supply_main_lvb_set(LVb4K);
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				TGTHT510_supply_main_lvb_set(LVb6K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_IS_IN_TANK_VALVE_ON;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_IS_IN_TANK_VALVE_ON://判断开进贮箱低压气路补加阀门
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb02,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb04,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb06,VALVE_ON)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_is_in_tank_valve_on_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE://通过压力判断开补加阀门
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_F1)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_F2)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_TANK_VALVE_ON_PRESSURE);
				}
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				if(TGTHT510_supply_common_is_in_tank_valve_on_pressure(DECODE_TANK_F3)==TRUE)
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
**名称：开燃压气机进口阀门
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_in_compressor_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO1://开燃压气机进口阀门，第一组
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
			{
				TGTHT510_supply_main_lvb_set(LVb14K);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_main_lvb_set(LVb24K);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO1;

			break;
		}
		
		case COMMAND_09_0002_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO1://判断开燃压气机进口阀门，第一组
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb14,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO2;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb24,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO2;
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
		
		case COMMAND_09_0003_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO2://开燃压气机进口阀门，第二组
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
			{
				TGTHT510_supply_main_lvb_set(LVb16K);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
			{
				asm("nop;");
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO2://判断开燃压气机进口阀门，第二组
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb16,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO3;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO3://开燃压气机进口阀门，第三组
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
			{
				TGTHT510_supply_main_lvb_set(LVb22G);
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO3;

			break;
		}
		
		case COMMAND_09_0006_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO3://判断开燃压气机进口阀门，第三组
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb22,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_time_delay1(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_TIME_DELAY1_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_TIME_DELAY1_START://延时等待time_delay1计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_IS_TIME_DELAY1;
	
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_IS_TIME_DELAY1://判断延时等待time_delay1
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_is_in_compressor_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_IS_IN_COMPRESSOR_PRESSURE;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_IS_IN_COMPRESSOR_PRESSURE://判断压气机进口压力是否正常
		{
			if(TGTHT510_supply_common_is_in_compressor_pressure(COMP_TANK_F)==TRUE)
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
**名称: 燃压气机启动
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_compressor_start(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_COMPRESSOR_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_COMPRESSOR_START://申请设备管理指令，压气机启动
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_B_START);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_START);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_COMPRESSOR_IS_TIME_1MIN://判断1min定时
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_1MIN)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_IS_COMPRESSOR_START;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_IS_COMPRESSOR_START://通过互传数据判断启动是否正常
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_is_out_compressor_pressure(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_IS_OUT_COMPRESSOR_PRESSURE;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_IS_OUT_COMPRESSOR_PRESSURE://判断压气机出口压力是否正常
		{
			if(TGTHT510_supply_common_is_out_compressor_pressure(COMP_TANK_F)==TRUE)
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
**名称: 开燃压气机出口阀门
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_out_compressor_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_OUT_COMPRESSOR_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_OUT_COMPRESSOR_VALVE_ON://开燃压气机出口阀门
		{
			TGTHT510_supply_common_out_compressor_valve_on(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_IS_OUT_COMPRESSOR_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_IS_OUT_COMPRESSOR_VALVE_ON://判断开燃压气机出口阀门
		{
			if(TGTHT510_supply_common_is_out_compressor_valve_on(COMP_TANK_F)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_step_number_comp_gas(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_NUMBER_COMP_GAS;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_NUMBER_COMP_GAS://判断抽气气瓶个数
		{
			if(TGTHT510_supply_common_number_gas(COMP_TANK_F,FIRST_TANK)==ONE_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_IN_GAS_VALVE_ON;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else if(TGTHT510_supply_common_number_gas(COMP_TANK_F,FIRST_TANK)==TWO_GAS)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON;
				
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IN_GAS_VALVE_ON://开进气瓶补加阀门
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_IN_GAS_VALVE_ON://判断开进气瓶补加阀门
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_F,THIRD_TANK,FIRST_GAS)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_TIME_DELAY2_START://延时等待time_delay2计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_DELAY2://判断延时等待time_delay2
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_GAS_PRESSURE_NO1://采集气瓶压力，第一次
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_TIME_30S_START_NO1://计时30s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_IS_TIME_30S_NO1://判断定时30s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_GAS_PRESSURE_NO2://采集气瓶压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_TIME_30S_START_NO2;
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_TIME_30S_START_NO2://计时30s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_TIME_30S_NO2;
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_TIME_30S_NO2://判断定时30s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_1GAS_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_1GAS_GAS_PRESSURE_NO3://采集气瓶压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_1GAS_TIME_30S_START_NO3;
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_1GAS_TIME_30S_START_NO3://计时30s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_1GAS_IS_TIME_30S_NO3;
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_1GAS_IS_TIME_30S_NO3://判断定时30s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_1GAS_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_1GAS_GAS_PRESSURE_NO4://采集气瓶压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_1GAS_TIME_30S_START_NO4;
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_1GAS_TIME_30S_START_NO4://计时30s计时开始，第四次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0012_F_1TANK_1GAS_IS_TIME_30S_NO4;
			break;
		}
		
		case COMMAND_09_0012_F_1TANK_1GAS_IS_TIME_30S_NO4://判断定时30s，第四次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0013_F_1TANK_1GAS_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0013_F_1TANK_1GAS_GAS_PRESSURE_NO5://采集气瓶压力，第五次
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0014_F_1TANK_1GAS_TIME_30S_START_NO5;
			break;
		}
		
		case COMMAND_09_0014_F_1TANK_1GAS_TIME_30S_START_NO5://计时30s计时开始，第五次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0015_F_1TANK_1GAS_IS_TIME_30S_NO5;
			break;
		}
		
		case COMMAND_09_0015_F_1TANK_1GAS_IS_TIME_30S_NO5://判断定时30s，第五次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0016_F_1TANK_1GAS_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0016_F_1TANK_1GAS_GAS_PRESSURE_NO6://采集气瓶压力，第六次
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0017_F_1TANK_1GAS_TIME_30S_START_NO6;
			break;
		}
		
		case COMMAND_09_0017_F_1TANK_1GAS_TIME_30S_START_NO6://计时30s计时开始，第六次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0018_F_1TANK_1GAS_IS_TIME_30S_NO6;
			break;
		}
		
		case COMMAND_09_0018_F_1TANK_1GAS_IS_TIME_30S_NO6://判断定时30s，第六次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0019_F_1TANK_1GAS_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0019_F_1TANK_1GAS_GAS_PRESSURE_NO7://采集气瓶压力，第七次
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0020_F_1TANK_1GAS_TIME_30S_START_NO7;
			break;
		}
		
		case COMMAND_09_0020_F_1TANK_1GAS_TIME_30S_START_NO7://计时30s计时开始，第七次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0021_F_1TANK_1GAS_IS_TIME_30S_NO7;
			break;
		}
		
		case COMMAND_09_0021_F_1TANK_1GAS_IS_TIME_30S_NO7://判断定时30s，第七次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0022_F_1TANK_1GAS_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0022_F_1TANK_1GAS_GAS_PRESSURE_NO8://采集气瓶压力，第八次
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0023_F_1TANK_1GAS_TIME_30S_START_NO8;
			break;
		}
		
		case COMMAND_09_0023_F_1TANK_1GAS_TIME_30S_START_NO8://计时30s计时开始，第八次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0024_F_1TANK_1GAS_IS_TIME_30S_NO8;
			break;
		}
		
		case COMMAND_09_0024_F_1TANK_1GAS_IS_TIME_30S_NO8://判断定时30s，第八次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0025_F_1TANK_1GAS_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0025_F_1TANK_1GAS_GAS_PRESSURE_NO9://采集气瓶压力，第九次
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0026_F_1TANK_1GAS_TIME_30S_START_NO9;
			break;
		}
		
		case COMMAND_09_0026_F_1TANK_1GAS_TIME_30S_START_NO9://计时30s计时开始，第九次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0027_F_1TANK_1GAS_IS_TIME_30S_NO9;
			break;
		}
		
		case COMMAND_09_0027_F_1TANK_1GAS_IS_TIME_30S_NO9://判断定时30s，第九次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0028_F_1TANK_1GAS_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0028_F_1TANK_1GAS_GAS_PRESSURE_NO10://采集气瓶压力，第十次
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0029_F_1TANK_1GAS_IS_GAS_PRESSURE;
			break;
		}
		
		case COMMAND_09_0029_F_1TANK_1GAS_IS_GAS_PRESSURE://压差判断气瓶压力是否升高
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IS_COMP_GAS_OVER://判断气瓶抽气是否结束
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_F,THIRD_TANK,FIRST_GAS)==TRUE)
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
**名称: 关燃路气瓶补加阀门
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			//采集关阀之前的压气机出口压力值
			temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO1://关燃路气瓶补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb8G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO1://判断关燃路气瓶补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb08,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO2://关燃路气瓶补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb10G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO2;
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO2://判断关燃路气瓶补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb10,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO3://关燃路气瓶补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb12G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO3;
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO3://判断关燃路气瓶补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb12,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_isolation_first(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO1;
			
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_FIRST_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_FIRST_TIME_12S_START_NO1://计时12s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO1://判断定时12s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_FIRST_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_FIRST_TIME_12S_START_NO2://计时12s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO2://判断定时12s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO3://采集压气机出口压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_1GAS_FIRST_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_1GAS_FIRST_TIME_12S_START_NO3://计时12s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO3://判断定时12s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO4://采集压气机出口压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_1GAS_FIRST_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_1GAS_FIRST_IS_ISOLATION://通过压力判断高压气路隔离是否正常
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_COMPRESSOR_STOP;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF;
				
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
**名称: 关闭燃压气机出口阀门
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_out_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1://关闭燃压气机出口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb18G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1://判断关闭燃压气机出口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb18,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2://关闭燃压气机出口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb20G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2://判断关闭燃压气机出口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb20,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3://关闭燃压气机出口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb26G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3://判断关闭燃压气机出口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb26,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_isolation_second(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_SECOND_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_SECOND_TIME_12S_START_NO1://计时12s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO1://判断定时12s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_SECOND_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_SECOND_TIME_12S_START_NO2://计时12s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO2://判断定时12s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO3://采集压气机出口压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_1GAS_SECOND_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_1GAS_SECOND_TIME_12S_START_NO3://计时12s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO3://判断定时12s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO4://采集压气机出口压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_1GAS_SECOND_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_1GAS_SECOND_IS_ISOLATION://通过压力判断高压气路隔离是否正常
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
**名称: 燃压气机停机
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_COMPRESSOR_STOP;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_COMPRESSOR_STOP://申请设备管理指令，压气机停机
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_B_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN://判断1min定时
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
**名称: 判断燃压气机停机是否正常
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

uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_compressor_stop(void)
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
		
		case COMMAND_09_0001_F_1TANK_1GAS_COMPRESSOR_V_NO1://采集电机转速，第一次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_V_NO2://采集电机转速，第二次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_COMPRESSOR_V_NO3://采集电机转速，第三次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_COMPRESSOR_V_NO4://采集电机转速，第四次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_COMPRESSOR_V_NO5://采集电机转速，第五次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_COMPRESSOR_V_NO6://采集电机转速，第六次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_1GAS_COMPRESSOR_V_NO7://采集电机转速，第七次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_1GAS_COMPRESSOR_V_NO8://采集电机转速，第八次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_1GAS_TIME_12S_START://计时12s计时开始
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_1GAS_IS_TIME_12S://判断定时12s
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0012_F_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0013_F_1TANK_1GAS_IS_COMPRESSOR_STOP://判断燃压气机停机是否正常
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
**名称: 开燃压气机旁路自锁阀
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_bypath_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_BYPATH_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_BYPATH_VALVE_ON://开燃压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				TGTHT510_supply_main_lvb_set(LVb22K);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_ON;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
			{
				TGTHT510_supply_main_lvb_set(LVb87K);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_ON;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_ON://判断开燃压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb22,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay_bypath(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_TIME_BYPATH_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_TIME_BYPATH_START://延时等待time_bypath计时开启
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_BYPATH;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_BYPATH://判断延时等待time_bypath
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
**名称: 关燃压气机旁路自锁阀
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_bypath_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_BYPATH_VALVE_OFF;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_BYPATH_VALVE_OFF://关燃压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				TGTHT510_supply_main_lvb_set(LVb22G);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_OFF://判断关燃压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb22,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
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
**名称: 关闭燃压气机出口阀门，第二次
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_out_compressor_valve_off2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1://关闭燃压气机出口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb18G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1://判断关闭燃压气机出口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb18,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2://关闭燃压气机出口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb20G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2://判断关闭燃压气机出口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb20,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3://关闭燃压气机出口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb26G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3://判断关闭燃压气机出口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb26,VALVE_OFF)==TRUE)
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
**名称: 关闭燃压气机进口阀门
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1://关闭燃压气机进口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb14G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1://判断关闭燃压气机进口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb14,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2://关闭燃压气机进口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb16G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2://判断关闭燃压气机进口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb16,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3://关闭燃压气机进口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb24G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3://判断关闭燃压气机进口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb24,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO1://关进贮箱低压气路补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb2G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO1://判断关进贮箱低压气路补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb02,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO2://关进贮箱低压气路补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb4G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO2://判断关进贮箱低压气路补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb04,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO3://关进贮箱低压气路补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb6G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO3://判断关进贮箱低压气路补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb06,VALVE_OFF)==TRUE)
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
**名称: 设置燃抽气状态好
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

uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_set_state_good(void)
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
		
		case COMMAND_09_0001_F_1TANK_1GAS_SET_STATE_GOOD://设置燃抽气状态好
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE://判断压气机温度是否正常
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_F)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_time_delay3(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_TIME_DELAY3_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_TIME_DELAY3_START://延时等待time_delay3计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_DELAY3;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_TIME_DELAY3://判断延时等待time_delay3
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
**名称: 启动液冷模块切换程序
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_exchange_cooler(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO1://液冷模块切换程序，阀门动作，第一组
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO1);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO1://判断液冷模块切换程序，阀门动作，第一组
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO2;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO2://液冷模块切换程序，阀门动作，第二组
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO2);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO2://判断液冷模块切换程序，阀门动作，第二组
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO3://液冷模块切换程序，阀门动作，第三组
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO3);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO3://判断液冷模块切换程序，阀门动作，第三组
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO3)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO4;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO4://液冷模块切换程序，阀门动作，第四组
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO4);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO4;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO4://判断液冷模块切换程序，阀门动作，第四组
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
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
**名称: 通过压力判断液冷模块切换是否正常
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_is_exchange_cooler(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_IS_EXCHANGE_COOLER;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_1GAS_IS_EXCHANGE_COOLER://通过压力判断液冷模块切换是否正常
		{
			if(TGTHT510_supply_common_is_exchange_cooler_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER_PRESSURE);//通过压力判断液冷模块切换程序异常
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_COOLER_POWER_OFF;
			break;
		}
	
		case COMMAND_09_0001_F_1TANK_1GAS_COOLER_POWER_OFF://液冷模块停机
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_compressor_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_COMPRESSOR_POWER_OFF;
			break;
		}
	
		case COMMAND_09_0001_F_1TANK_1GAS_COMPRESSOR_POWER_OFF://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_B_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN://判断计时1min是否到
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_1gas_step_TGTHT530_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_1GAS_TGTHT530_POWER_OFF;
			break;
		}
	
		case COMMAND_09_0001_F_1TANK_1GAS_TGTHT530_POWER_OFF://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530b_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_1GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_1GAS_TGTHT530_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_1GAS_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_1GAS_TGTHT530_IS_TIME_1MIN://判断计时1min是否到
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
-----------------------------------第三个贮箱抽气，两个气瓶抽气----------------------------------------------------
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON://开进气瓶补加阀门
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_ON://判断开进气瓶补加阀门
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_F,THIRD_TANK,FIRST_GAS)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS1_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS1_TIME_DELAY2_START://延时等待time_delay2计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_TIME_DELAY2://判断延时等待time_delay2
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO1://采集气瓶压力，第一次
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS1_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS1_TIME_30S_START_NO1://计时30s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO1://判断定时30s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO2://采集气瓶压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_GAS1_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_GAS1_TIME_30S_START_NO2://计时30s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO2://判断定时30s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO3://采集气瓶压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_2GAS_GAS1_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_2GAS_GAS1_TIME_30S_START_NO3://计时30s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO3://判断定时30s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO4://采集气瓶压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_2GAS_GAS1_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_2GAS_GAS1_TIME_30S_START_NO4://计时30s计时开始，第四次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0012_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_09_0012_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO4://判断定时30s，第四次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0013_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0013_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO5://采集气瓶压力，第五次
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0014_F_1TANK_2GAS_GAS1_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_09_0014_F_1TANK_2GAS_GAS1_TIME_30S_START_NO5://计时30s计时开始，第五次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0015_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_09_0015_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO5://判断定时30s，第五次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0016_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0016_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO6://采集气瓶压力，第六次
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0017_F_1TANK_2GAS_GAS1_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_09_0017_F_1TANK_2GAS_GAS1_TIME_30S_START_NO6://计时30s计时开始，第六次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0018_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_09_0018_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO6://判断定时30s，第六次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0019_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0019_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO7://采集气瓶压力，第七次
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0020_F_1TANK_2GAS_GAS1_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_09_0020_F_1TANK_2GAS_GAS1_TIME_30S_START_NO7://计时30s计时开始，第七次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0021_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_09_0021_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO7://判断定时30s，第七次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0022_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0022_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO8://采集气瓶压力，第八次
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0023_F_1TANK_2GAS_GAS1_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_09_0023_F_1TANK_2GAS_GAS1_TIME_30S_START_NO8://计时30s计时开始，第八次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0024_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_09_0024_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO8://判断定时30s，第八次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0025_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0025_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO9://采集气瓶压力，第九次
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0026_F_1TANK_2GAS_GAS1_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_09_0026_F_1TANK_2GAS_GAS1_TIME_30S_START_NO9://计时30s计时开始，第九次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0027_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_09_0027_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO9://判断定时30s，第九次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0028_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0028_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO10://采集气瓶压力，第十次
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,FIRST_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0029_F_1TANK_2GAS_GAS1_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_09_0029_F_1TANK_2GAS_GAS1_IS_GAS_PRESSURE://压差判断气瓶压力是否升高
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS1_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS1_IS_COMP_GAS_OVER://判断气瓶抽气是否结束
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_F,THIRD_TANK,FIRST_GAS)==TRUE)
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
**名称: 关燃路气瓶补加阀门---第一个气瓶
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas1_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1://关燃路气瓶补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb8G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1://判断关燃路气瓶补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb08,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2://关燃路气瓶补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb10G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2://判断关燃路气瓶补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb10,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3://关燃路气瓶补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb12G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3://判断关燃路气瓶补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb12,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_in_gas_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON://开进气瓶补加阀门
		{
			TGTHT510_supply_common_in_gas_valve_on(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_ON;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_ON://判断开进气瓶补加阀门
		{
			if(TGTHT510_supply_common_is_in_gas_valve_on(COMP_TANK_F,THIRD_TANK,SECOND_GAS)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_time_delay2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS2_TIME_DELAY2_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS2_TIME_DELAY2_START://延时等待time_delay2计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_TIME_DELAY2;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_TIME_DELAY2://判断延时等待time_delay2
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_is_gas_pressure(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO1://采集气瓶压力，第一次
		{
			temp_global[0]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS2_TIME_30S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS2_TIME_30S_START_NO1://计时30s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO1;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO1://判断定时30s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO2://采集气瓶压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_GAS2_TIME_30S_START_NO2;
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_GAS2_TIME_30S_START_NO2://计时30s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO2;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO2://判断定时30s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO3://采集气瓶压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_2GAS_GAS2_TIME_30S_START_NO3;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_2GAS_GAS2_TIME_30S_START_NO3://计时30s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO3;
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO3://判断定时30s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO4://采集气瓶压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_2GAS_GAS2_TIME_30S_START_NO4;
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_2GAS_GAS2_TIME_30S_START_NO4://计时30s计时开始，第四次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0012_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO4;
			
			break;
		}
		
		case COMMAND_09_0012_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO4://判断定时30s，第四次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0013_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO5;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0013_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO5://采集气瓶压力，第五次
		{
			temp_global[4]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0014_F_1TANK_2GAS_GAS2_TIME_30S_START_NO5;
			
			break;
		}
		
		case COMMAND_09_0014_F_1TANK_2GAS_GAS2_TIME_30S_START_NO5://计时30s计时开始，第五次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0015_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO5;
			
			break;
		}
		
		case COMMAND_09_0015_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO5://判断定时30s，第五次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0016_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO6;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0016_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO6://采集气瓶压力，第六次
		{
			temp_global[5]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0017_F_1TANK_2GAS_GAS2_TIME_30S_START_NO6;
			
			break;
		}
		
		case COMMAND_09_0017_F_1TANK_2GAS_GAS2_TIME_30S_START_NO6://计时30s计时开始，第六次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0018_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO6;
			
			break;
		}
		
		case COMMAND_09_0018_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO6://判断定时30s，第六次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0019_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO7;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0019_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO7://采集气瓶压力，第七次
		{
			temp_global[6]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0020_F_1TANK_2GAS_GAS2_TIME_30S_START_NO7;
			
			break;
		}
		
		case COMMAND_09_0020_F_1TANK_2GAS_GAS2_TIME_30S_START_NO7://计时30s计时开始，第七次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0021_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO7;
			
			break;
		}
		
		case COMMAND_09_0021_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO7://判断定时30s，第七次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0022_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO8;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0022_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO8://采集气瓶压力，第八次
		{
			temp_global[7]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0023_F_1TANK_2GAS_GAS2_TIME_30S_START_NO8;
			
			break;
		}
		
		case COMMAND_09_0023_F_1TANK_2GAS_GAS2_TIME_30S_START_NO8://计时30s计时开始，第八次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0024_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO8;
			
			break;
		}
		
		case COMMAND_09_0024_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO8://判断定时30s，第八次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0025_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO9;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0025_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO9://采集气瓶压力，第九次
		{
			temp_global[8]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0026_F_1TANK_2GAS_GAS2_TIME_30S_START_NO9;
			
			break;
		}
		
		case COMMAND_09_0026_F_1TANK_2GAS_GAS2_TIME_30S_START_NO9://计时30s计时开始，第九次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0027_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO9;
			
			break;
		}
		
		case COMMAND_09_0027_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO9://判断定时30s，第九次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_30SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0028_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO10;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0028_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO10://采集气瓶压力，第十次
		{
			temp_global[9]=TGTHT510_supply_common_gas_pressure_get(COMP_TANK_F,THIRD_TANK,SECOND_GAS);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0029_F_1TANK_2GAS_GAS2_IS_GAS_PRESSURE;
			
			break;
		}
		
		case COMMAND_09_0029_F_1TANK_2GAS_GAS2_IS_GAS_PRESSURE://压差判断气瓶压力是否升高
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_is_comp_over(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS2_IS_COMP_GAS_OVER;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS2_IS_COMP_GAS_OVER://判断气瓶抽气是否结束
		{
			if(TGTHT510_supply_common_is_gas_comp_over(COMP_TANK_F,THIRD_TANK,SECOND_GAS)==TRUE)
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
**名称: 关燃路气瓶补加阀门---第二个气瓶
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_gas2_step_in_gas_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1://关燃路气瓶补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb8G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1://判断关燃路气瓶补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb08,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2://关燃路气瓶补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb10G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2://判断关燃路气瓶补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb10,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3://关燃路气瓶补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb12G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3://判断关燃路气瓶补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb12,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_isolation_first(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_FIRST_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_FIRST_TIME_12S_START_NO1://计时12s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO1://判断定时12s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_FIRST_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_FIRST_TIME_12S_START_NO2://计时12s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO2://判断定时12s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO3://采集压气机出口压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_2GAS_FIRST_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_2GAS_FIRST_TIME_12S_START_NO3://计时12s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO3://判断定时12s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO4://采集压气机出口压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_2GAS_FIRST_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_2GAS_FIRST_IS_ISOLATION://通过压力判断高压气路隔离是否正常
		{
			if(TGTHT510_supply_common_is_isolation(temp_global)==TRUE)
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_COMPRESSOR_STOP;
				
				TGTHT510_supply_ctrl.command=COMMAND_START;
			}
			
			else
			{
				TGTHT510_supply_ctrl.step=STEP_09_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF;
				
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
**名称: 关闭燃压气机出口阀门
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_out_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1://关闭燃压气机出口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb18G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1://判断关闭燃压气机出口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb18,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2://关闭燃压气机出口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb20G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2://判断关闭燃压气机出口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb20,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3://关闭燃压气机出口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb26G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3://判断关闭燃压气机出口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb26,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_isolation_second(void)
{
	uint16 return_state;
	
	uint16 i;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//temp_global[0]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_SECOND_TIME_12S_START_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_SECOND_TIME_12S_START_NO1://计时12s计时开始，第一次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO1;
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO1://判断定时12s，第一次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO2;
			}
			
			else
			{
				asm("nop;");
			}
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			temp_global[1]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_SECOND_TIME_12S_START_NO2;
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_SECOND_TIME_12S_START_NO2://计时12s计时开始，第二次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO2;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO2://判断定时12s，第二次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO3;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO3://采集压气机出口压力，第三次
		{
			temp_global[2]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_2GAS_SECOND_TIME_12S_START_NO3;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_2GAS_SECOND_TIME_12S_START_NO3://计时12s计时开始，第三次
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0009_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO3;
			
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO3://判断定时12s，第三次
		{
			if(TGTHT510_supply_time_step_is_get(CONST_TIME_12SEC)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0010_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO4;
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO4://采集压气机出口压力，第四次
		{
			temp_global[3]=TGTHT510_supply_common_out_compressor_pressure_get(COMP_TANK_F);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0011_F_1TANK_2GAS_SECOND_IS_ISOLATION;
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_2GAS_SECOND_IS_ISOLATION://通过压力判断高压气路隔离是否正常
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
**名称: 燃压气机停机
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_compressor_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_COMPRESSOR_STOP;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_COMPRESSOR_STOP://申请设备管理指令，压气机停机
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_B_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_STOP);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN://判断1min定时
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
**名称: 判断燃压气机停机是否正常
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

uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_compressor_stop(void)
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
		
		case COMMAND_09_0001_F_1TANK_2GAS_COMPRESSOR_V_NO1://采集电机转速，第一次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_V_NO2://采集电机转速，第二次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_COMPRESSOR_V_NO3://采集电机转速，第三次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_COMPRESSOR_V_NO4://采集电机转速，第四次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_COMPRESSOR_V_NO5://采集电机转速，第五次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_COMPRESSOR_V_NO6://采集电机转速，第六次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_2GAS_COMPRESSOR_V_NO7://采集电机转速，第七次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_2GAS_COMPRESSOR_V_NO8://采集电机转速，第八次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0009_F_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO1://采集压气机出口压力，第一次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0010_F_1TANK_2GAS_TIME_12S_START://计时12s计时开始
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0011_F_1TANK_2GAS_IS_TIME_12S://判断定时12s
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0012_F_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO2://采集压气机出口压力，第二次
		{
			//待补充！！！！
			
			
			break;
		}
		
		case COMMAND_09_0013_F_1TANK_2GAS_IS_COMPRESSOR_STOP://判断燃压气机停机是否正常
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
**名称: 开燃压气机旁路自锁阀
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_bypath_valve_on(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_BYPATH_VALVE_ON;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_BYPATH_VALVE_ON://开燃压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				TGTHT510_supply_main_lvb_set(LVb22K);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_ON;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
			{
				TGTHT510_supply_main_lvb_set(LVb87K);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_ON;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_ON://判断开燃压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb22,VALVE_ON)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_ON);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_time_delay_bypath(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_TIME_BYPATH_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_TIME_BYPATH_START://延时等待time_bypath计时开启
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_TIME_BYPATH;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_TIME_BYPATH://判断延时等待time_bypath
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
**名称: 关燃压气机旁路自锁阀
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_bypath_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_BYPATH_VALVE_OFF;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_BYPATH_VALVE_OFF://关燃压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				TGTHT510_supply_main_lvb_set(LVb22G);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
			{
				TGTHT510_supply_main_lvb_set(LVb87G);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_OFF;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_OFF://判断关燃压气机旁路自锁阀
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				if(TGTHT510_supply_main_lvb_get(STATE_LVb22,VALVE_OFF)==TRUE)
				{
					TGTHT510_supply_ctrl.command=COMMAND_END;
				}
				
				else
				{
					TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
				}
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
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
**名称: 关闭燃压气机出口阀门，第二次
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_out_compressor_valve_off2(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1://关闭燃压气机出口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb18G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1://判断关闭燃压气机出口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb18,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2://关闭燃压气机出口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb20G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2://判断关闭燃压气机出口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb20,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			}
				
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3://关闭燃压气机出口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb26G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3://判断关闭燃压气机出口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb26,VALVE_OFF)==TRUE)
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
**名称: 关闭燃压气机进口阀门
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_in_compressor_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1://关闭燃压气机进口阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb14G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1://判断关闭燃压气机进口阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb14,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2://关闭燃压气机进口阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb16G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2://判断关闭燃压气机进口阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb16,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3;
			}
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3://关闭燃压气机进口阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb24G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3://判断关闭燃压气机进口阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb24,VALVE_OFF)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_in_tank_valve_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO1://关进贮箱低压气路补加阀门，第一组
		{
			TGTHT510_supply_main_lvb_set(LVb2G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO1://判断关进贮箱低压气路补加阀门，第一组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb02,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO2;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO2://关进贮箱低压气路补加阀门，第二组
		{
			TGTHT510_supply_main_lvb_set(LVb4G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO2://判断关进贮箱低压气路补加阀门，第二组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb04,VALVE_OFF)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_SUPPLY_VALVE_OFF);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO3://关进贮箱低压气路补加阀门，第三组
		{
			TGTHT510_supply_main_lvb_set(LVb6G);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO3://判断关进贮箱低压气路补加阀门，第三组
		{
			if(TGTHT510_supply_main_lvb_get(STATE_LVb06,VALVE_OFF)==TRUE)
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
**名称: 设置燃抽气状态好
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

uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_set_state_good(void)
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
		
		case COMMAND_09_0001_F_1TANK_2GAS_SET_STATE_GOOD://设置燃抽气状态好
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_compressor_temperature(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE://判断压气机温度是否正常
		{
			if(TGTHT510_supply_common_is_compressor_temperature(COMP_TANK_F)==TRUE)
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_time_delay3(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_TIME_DELAY3_START;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_TIME_DELAY3_START://延时等待time_delay3计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_TIME_DELAY3;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_TIME_DELAY3://判断延时等待time_delay3
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
**名称: 启动液冷模块切换程序
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_exchange_cooler(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO1;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO1://液冷模块切换程序,阀门动作，第一组
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO1);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO1;
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO1://判断液冷模块切换程序,阀门动作，第一组
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO1)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO2;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
			}
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO2://液冷模块切换程序,阀门动作，第二组
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO2);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0004_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO2;
			
			break;
		}
		
		case COMMAND_09_0004_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO2://判断液冷模块切换程序,阀门动作，第二组
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO2)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0005_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO3;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
			}
			
			break;
		}
		
		case COMMAND_09_0005_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO3://液冷模块切换程序,阀门动作，第三组
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO3);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0006_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO3;
			
			break;
		}
		
		case COMMAND_09_0006_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO3://判断液冷模块切换程序,阀门动作，第三组
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO3)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_09_0007_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO4;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
			}
			
			break;
		}
		
		case COMMAND_09_0007_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO4://液冷模块切换程序,阀门动作，第四组
		{
			TGTHT510_supply_common_exchange_cooler(EXCHANGE_COOLER_NO4);
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0008_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO4;
			
			break;
		}
		
		case COMMAND_09_0008_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO4://判断液冷模块切换程序,阀门动作，第四组
		{
			if(TGTHT510_supply_common_is_exchange_cooler(EXCHANGE_COOLER_NO4)==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER);
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
**名称: 通过压力判断液冷模块切换是否正常
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_is_exchange_cooler(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_IS_EXCHANGE_COOLER;
			break;
		}
		
		case COMMAND_09_0001_F_1TANK_2GAS_IS_EXCHANGE_COOLER://通过压力判断液冷模块切换是否正常
		{
			if(TGTHT510_supply_common_is_exchange_cooler_pressure()==TRUE)
			{
				TGTHT510_supply_ctrl.command=COMMAND_END;
			}
			
			else
			{
				//TGTHT510_supply_main_pause(ERRNO_EXCHANGE_COOLER_PRESSURE);//通过压力判断液冷模块切换程序异常
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_cooler_stop(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_COOLER_POWER_OFF;
			break;
		}
	
		case COMMAND_09_0001_F_1TANK_2GAS_COOLER_POWER_OFF://液冷模块停机
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_compressor_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_COMPRESSOR_POWER_OFF;
			break;
		}
	
		case COMMAND_09_0001_F_1TANK_2GAS_COMPRESSOR_POWER_OFF://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_B_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
			{
				TGTHT510_supply_main_equ_command_set(COMPRESS_C_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN://判断计时1min是否到
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
uint16 TGTHT510_supply_stage09_comp_F_1tank_2gas_step_TGTHT530_power_off(void)
{
	uint16 return_state;
	
	return_state=FALSE;
	
	switch(TGTHT510_supply_ctrl.command)
	{
		case COMMAND_START://开始
		{
			TGTHT510_supply_ctrl.command=COMMAND_09_0001_F_1TANK_2GAS_TGTHT530_POWER_OFF;
			break;
		}
	
		case COMMAND_09_0001_F_1TANK_2GAS_TGTHT530_POWER_OFF://申请设备管理指令
		{
			if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)//燃压气机为B
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530b_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)//燃压气机为C
			{
				TGTHT510_supply_main_equ_command_set(TGTHT530c_OFF_POWER);
				
				TGTHT510_supply_ctrl.command=COMMAND_09_0002_F_1TANK_2GAS_TGTHT530_TIME_1MIN_START;
			}
			
			else
			{
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数解码错误
			}
			
			break;
		}
		
		case COMMAND_09_0002_F_1TANK_2GAS_TGTHT530_TIME_1MIN_START://延时1min计时开始
		{
			TGTHT510_supply_time_step_start();
			
			TGTHT510_supply_ctrl.command=COMMAND_09_0003_F_1TANK_2GAS_TGTHT530_IS_TIME_1MIN;
			
			break;
		}
		
		case COMMAND_09_0003_F_1TANK_2GAS_TGTHT530_IS_TIME_1MIN://判断计时1min是否到
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
**名称：补加阶段5
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_command_third_isolation_valve_off(uint16 n,uint16 isolation_tank)
{
//----------------------燃贮箱隔离----------------------------------------------
	
	if(isolation_tank==ISOLATION_TANK_F)
	{
		if(TGTHT510_supply_decode_par.number_tank_F==3)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				switch(n)
				{
					case 1:
					{
						TGTHT510_supply_main_lvt_set(LVt2G);
						break;
					}
					
					case 2:
					{
						TGTHT510_supply_main_lvt_set(LVt20G);
						break;
					}
					
					case 3:
					{
						TGTHT510_supply_main_lvt_set(LVt24G);
						break;
					}
					
					case 4:
					{
						TGTHT510_supply_main_lvt_set(LVt32G);
						break;
					}
					
					case 5:
					{
						
						break;
					}
					
					case 6:
					{
						
						break;
					}
					
					case 7:
					{
						
						break;
					}
					
					case 8:
					{
						
						break;
					}
					
					case 9:
					{
						
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
						break;
					}

				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				switch(n)
				{
					case 1:
					{
						TGTHT510_supply_main_lvt_set(LVt4G);
						break;
					}
					
					case 2:
					{
						TGTHT510_supply_main_lvt_set(LVt20G);
						break;
					}
					
					case 3:
					{
						TGTHT510_supply_main_lvt_set(LVt22G);
						break;
					}
					
					case 4:
					{
						TGTHT510_supply_main_lvt_set(LVt24G);
						break;
					}
					
					case 5:
					{
						TGTHT510_supply_main_lvt_set(LVt26G);
						break;
					}
					
					case 6:
					{
						TGTHT510_supply_main_lvt_set(LVt28G);
						break;
					}
					
					case 7:
					{
						TGTHT510_supply_main_lvt_set(LVt30G);
						break;
					}
					
					case 8:
					{
						
						break;
					}
					
					case 9:
					{
						
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
						break;
					}

				}
				
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				switch(n)
				{
					case 1:
					{
						TGTHT510_supply_main_lvt_set(LVt6G);
						break;
					}
					
					case 2:
					{
						TGTHT510_supply_main_lvt_set(LVt22G);
						break;
					}
					
					case 3:
					{
						TGTHT510_supply_main_lvt_set(LVt26G);
						break;
					}
					
					case 4:
					{
						TGTHT510_supply_main_lvt_set(LVt34G);
						break;
					}
					
					case 5:
					{
						
						break;
					}
					
					case 6:
					{
						
						break;
					}
					
					case 7:
					{
						
						break;
					}
					
					case 8:
					{
						
						break;
					}
					
					case 9:
					{
						
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
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数错误
			}

		}
		
		else
		{
			TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数错误
		}
	}

//----------------------氧贮箱隔离----------------------------------------------
	
	else if(isolation_tank==ISOLATION_TANK_O)
	{
		if(TGTHT510_supply_decode_par.number_tank_O==3)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				switch(n)
				{
					case 1:
					{
						TGTHT510_supply_main_lvt_set(LVt1G);
						break;
					}
					
					case 2:
					{
						TGTHT510_supply_main_lvt_set(LVt19G);
						break;
					}
					
					case 3:
					{
						TGTHT510_supply_main_lvt_set(LVt23G);
						break;
					}
					
					case 4:
					{
						TGTHT510_supply_main_lvt_set(LVt31G);
						break;
					}
					
					case 5:
					{
						
						break;
					}
					
					case 6:
					{
						
						break;
					}
					
					case 7:
					{
						
						break;
					}
					
					case 8:
					{
						
						break;
					}
					
					case 9:
					{
						
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
						break;
					}

				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				switch(n)
				{
					case 1:
					{
						TGTHT510_supply_main_lvt_set(LVt3G);
						break;
					}
					
					case 2:
					{
						TGTHT510_supply_main_lvt_set(LVt19G);
						break;
					}
					
					case 3:
					{
						TGTHT510_supply_main_lvt_set(LVt21G);
						break;
					}
					
					case 4:
					{
						TGTHT510_supply_main_lvt_set(LVt23G);
						break;
					}
					
					case 5:
					{
						TGTHT510_supply_main_lvt_set(LVt25G);
						break;
					}
					
					case 6:
					{
						TGTHT510_supply_main_lvt_set(LVt27G);
						break;
					}
					
					case 7:
					{
						TGTHT510_supply_main_lvt_set(LVt29G);
						break;
					}
					
					case 8:
					{
						
						break;
					}
					
					case 9:
					{
						
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
						break;
					}

				}
				
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				switch(n)
				{
					case 1:
					{
						TGTHT510_supply_main_lvt_set(LVt5G);
						break;
					}
					
					case 2:
					{
						TGTHT510_supply_main_lvt_set(LVt21G);
						break;
					}
					
					case 3:
					{
						TGTHT510_supply_main_lvt_set(LVt25G);
						break;
					}
					
					case 4:
					{
						TGTHT510_supply_main_lvt_set(LVt33G);
						break;
					}
					
					case 5:
					{
						
						break;
					}
					
					case 6:
					{
						
						break;
					}
					
					case 7:
					{
						
						break;
					}
					
					case 8:
					{
						
						break;
					}
					
					case 9:
					{
						
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
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数错误
			}

		}
		
		else
		{
			TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数错误
		}
	
	}
	
	else
	{
		TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
	}

}


/******************************************************************************************
**名称：补加阶段5
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_command_is_third_isolation_valve_off(uint16 n,uint16 isolation_tank)
{
	//----------------------燃贮箱隔离----------------------------------------------
	
	if(isolation_tank==ISOLATION_TANK_F)
	{
		
		if(TGTHT510_supply_decode_par.number_tank_F==3)
		{
			if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F1)
			{
				switch(n)
				{
					case 1:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt02,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						
						break;
					}
					
					case 2:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt20,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 3:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt24,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 4:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt32,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 5:
					{
						return TRUE;
						break;
					}
					
					case 6:
					{
						return TRUE;
						break;
					}
					
					case 7:
					{
						return TRUE;
						break;
					}
					
					case 8:
					{
						return TRUE;
						break;
					}
					
					case 9:
					{
						return TRUE;
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
						break;
					}

				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F2)
			{
				switch(n)
				{
					case 1:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt04,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 2:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt20,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 3:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt22,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 4:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt24,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 5:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt26,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 6:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt28,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 7:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt30,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 8:
					{
						return TRUE;
						break;
					}
					
					case 9:
					{
						return TRUE;
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
						break;
					}

				}
				
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_F==DECODE_TANK_F3)
			{
				switch(n)
				{
					case 1:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt06,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 2:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt22,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 3:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt26,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 4:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt34,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 5:
					{
						return TRUE;
						break;
					}
					
					case 6:
					{
						return TRUE;
						break;
					}
					
					case 7:
					{
						return TRUE;
						break;
					}
					
					case 8:
					{
						return TRUE;
						break;
					}
					
					case 9:
					{
						return TRUE;
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
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数错误
			}

		}
		
		else
		{
			TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数错误
		}
	
	}
//----------------------氧贮箱隔离----------------------------------------------
	
	else if(isolation_tank==ISOLATION_TANK_O)
	{
	
		if(TGTHT510_supply_decode_par.number_tank_O==3)
		{
			if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O1)
			{
				switch(n)
				{
					case 1:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt01,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 2:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt19,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 3:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt23,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 4:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt31,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 5:
					{
						return TRUE;
						break;
					}
					
					case 6:
					{
						return TRUE;
						break;
					}
					
					case 7:
					{
						return TRUE;
						break;
					}
					
					case 8:
					{
						return TRUE;
						break;
					}
					
					case 9:
					{
						return TRUE;
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
						break;
					}

				}
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O2)
			{
				switch(n)
				{
					case 1:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt03,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 2:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt19,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 3:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt21,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 4:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt23,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 5:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt25,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 6:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt27,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 7:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt29,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 8:
					{
						return TRUE;
						break;
					}
					
					case 9:
					{
						return TRUE;
						break;
					}
					
					default:
					{
						TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
						break;
					}

				}
				
				
			}
			
			else if(TGTHT510_supply_decode_par.third_tank_O==DECODE_TANK_O3)
			{
				switch(n)
				{
					case 1:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt05,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 2:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt21,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 3:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt25,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 4:
					{
						if(TGTHT510_supply_main_lvt_get(STATE_LVt33,VALVE_OFF)==TRUE)
						{
							return TRUE;
						}
						break;
					}
					
					case 5:
					{
						return TRUE;
						break;
					}
					
					case 6:
					{
						return TRUE;
						break;
					}
					
					case 7:
					{
						return TRUE;
						break;
					}
					
					case 8:
					{
						return TRUE;
						break;
					}
					
					case 9:
					{
						return TRUE;
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
				TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数错误
			}

		}
		
		else
		{
			TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);//补加注入参数错误
		}
	
	}
	
	else
	{
		TGTHT510_supply_main_pause(ERRNO_FUNCTION_INPUT_ERROR);//内部函数输入参数错误
	}
	
	return FALSE;

}






















