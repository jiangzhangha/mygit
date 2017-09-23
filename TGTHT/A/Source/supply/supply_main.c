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

TGTHT510_supply_ctrl_TypeDef TGTHT510_supply_ctrl;

TGTHT510_supply_input_par_TypeDef TGTHT510_supply_input_par;

TGTHT510_supply_time_TypeDef TGTHT510_supply_time;

TGTHT510_supply_decode_par_TypeDef TGTHT510_supply_decode_par;

compressor_state_TypeDef compressor_state;


extern valvecontrol_TypeDef TGTHT510_valvecontrol_struct;	//阀门控制结构体
extern uint16 TGTHT510_1553B_data_TGTHT100[];				//全局数组，缓存推进遥测线路盒除温度参数以外数据，89字
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[];		//全局数组，缓存推进遥测线路盒复帧A温度数据，65字
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[];		//全局数组，缓存推进遥测线路盒复帧B温度数据，65字
extern uint16 TGTHT510_1553B_data_TGTHT530[];				//全局数组，缓存压气机电机驱动器遥测数据，14字
extern uint16 TGTHT510_1553B_data_TGTHT520a[];				//全局数组，缓存推进控制驱动器主机遥测，7字
extern uint16 TGTHT510_1553B_data_TGTHT520b[];				//全局数组，缓存推进控制驱动器备机遥测，7字
extern uint16 TGTHT510_1553B_R_HYCT1100[];					//全局数组，缓存货船发送的遥测数据

extern CPU_B_receive_data_TypeDef CPU_B_receive_data;

//主路推进控制驱动器自锁阀状态查询表
uint16 valve_state_TGTHT520a_lookup[TGTHT510A_NUMBER]={
	TGTHT520_L_BYTE_L_BIT,//LVt09阀门开关状态
	TGTHT520_L_BYTE_H_BIT,//LVt11阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt01阀门开关状态
	TGTHT520_H_BYTE_H_BIT,//LVt07阀门开关状态
	TGTHT520_L_BYTE_L_BIT,//LVt43阀门开关状态
	TGTHT520_L_BYTE_H_BIT,//LVt45阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt31阀门开关状态
	TGTHT520_H_BYTE_H_BIT,//LVt37阀门开关状态
	TGTHT520_L_BYTE_L_BIT,//LVt08阀门开关状态
	TGTHT520_L_BYTE_H_BIT,//LVt10阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt51阀门开关状态
	TGTHT520_H_BYTE_H_BIT,//LVt02阀门开关状态
	TGTHT520_L_BYTE_L_BIT,//LVt38阀门开关状态
	TGTHT520_L_BYTE_H_BIT,//LVt44阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt12阀门开关状态
	TGTHT520_H_BYTE_H_BIT,//LVt32阀门开关状态
	TGTHT520_L_BYTE_L_BIT,//LVt03阀门开关状态
	TGTHT520_L_BYTE_H_BIT,//LVt20阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt46阀门开关状态
	TGTHT520_H_BYTE_H_BIT,//LVt52阀门开关状态
	TGTHT520_L_BYTE_L_BIT,//LVt35阀门开关状态
	TGTHT520_L_BYTE_H_BIT,//LVt19阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt24阀门开关状态
	TGTHT520_H_BYTE_H_BIT,//LVt27阀门开关状态
	TGTHT520_L_BYTE_L_BIT,//LVt36阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt23阀门开关状态
	TGTHT520_H_BYTE_H_BIT //LVt28阀门开关状态
};

uint16 valve_word_TGTHT520a_lookup[TGTHT510A_NUMBER]={
	0,0,0,0,
	1,1,1,1,
	2,2,2,2,
	3,3,3,3,
	4,4,4,4,
	5,5,5,5,
	6,6,6
};


//备路推进控制驱动器自锁阀状态查询表
uint16 valve_state_TGTHT520b_lookup[TGTHT510B_NUMBER]={
	TGTHT520_L_BYTE_L_BIT,//LVt18阀门开关状态
	TGTHT520_L_BYTE_H_BIT,//LVt22阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt06阀门开关状态
	TGTHT520_H_BYTE_H_BIT,//LVt16阀门开关状态
	TGTHT520_L_BYTE_L_BIT,//LVt29阀门开关状态
	TGTHT520_L_BYTE_H_BIT,//LVt39阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt26阀门开关状态
	TGTHT520_H_BYTE_H_BIT,//LVt13阀门开关状态
	TGTHT520_L_BYTE_L_BIT,//LVt15阀门开关状态
	TGTHT520_L_BYTE_H_BIT,//LVt17阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt41阀门开关状态
	TGTHT520_H_BYTE_H_BIT,//LVt05阀门开关状态
	TGTHT520_L_BYTE_L_BIT,//LVt34阀门开关状态
	TGTHT520_L_BYTE_H_BIT,//LVt48阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt21阀门开关状态
	TGTHT520_H_BYTE_H_BIT,//LVt25阀门开关状态
	TGTHT520_L_BYTE_L_BIT,//LVt33阀门开关状态
	TGTHT520_L_BYTE_H_BIT,//LVt47阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt50阀门开关状态
	TGTHT520_H_BYTE_H_BIT,//LVt54阀门开关状态
	TGTHT520_L_BYTE_L_BIT,//LVt04阀门开关状态
	TGTHT520_L_BYTE_H_BIT,//LVt14阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt49阀门开关状态
	TGTHT520_H_BYTE_H_BIT,//LVt53阀门开关状态
	TGTHT520_L_BYTE_L_BIT,//LVt42阀门开关状态
	TGTHT520_H_BYTE_L_BIT,//LVt30阀门开关状态
	TGTHT520_H_BYTE_H_BIT //LVt40阀门开关状态
};

uint16 valve_word_TGTHT520b_lookup[TGTHT510B_NUMBER]={
	0,0,0,0,
	1,1,1,1,
	2,2,2,2,
	3,3,3,3,
	4,4,4,4,
	5,5,5,5,
	6,6,6
};


/******************************************************************************************
**名称：补加阶段初始化函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_supply_main_initial(void)
{
	TGTHT510_supply_time.time_stage_flag=FALSE;
	TGTHT510_supply_time.time_step_flag=FALSE;
	TGTHT510_supply_time.time_stage=0;
	TGTHT510_supply_time.time_step=0;
	
//注入补加参数，变化-----------------------------------------------------------
	TGTHT510_supply_input_par.interface_F=0;
	TGTHT510_supply_input_par.interface_O=0;
	TGTHT510_supply_input_par.sequence_tank_F=0;
	TGTHT510_supply_input_par.sequence_tank_O=0;
	TGTHT510_supply_input_par.sequence_gas_F1=0;
	TGTHT510_supply_input_par.sequence_gas_F2=0;
	TGTHT510_supply_input_par.sequence_gas_F3=0;
	TGTHT510_supply_input_par.sequence_gas_O1=0;
	TGTHT510_supply_input_par.sequence_gas_O2=0;
	TGTHT510_supply_input_par.sequence_gas_O3=0;
	TGTHT510_supply_input_par.compressor_out_valve=0;
	TGTHT510_supply_input_par.pressure_first_F1=0;
	TGTHT510_supply_input_par.pressure_second_F1=0;
	TGTHT510_supply_input_par.pressure_first_F2=0;
	TGTHT510_supply_input_par.pressure_second_F2=0;
	TGTHT510_supply_input_par.pressure_first_F3=0;
	TGTHT510_supply_input_par.pressure_second_F3=0;
	TGTHT510_supply_input_par.pressure_first_O1=0;
	TGTHT510_supply_input_par.pressure_second_O1=0;
	TGTHT510_supply_input_par.pressure_first_O2=0;
	TGTHT510_supply_input_par.pressure_second_O2=0;
	TGTHT510_supply_input_par.pressure_first_O3=0;
	TGTHT510_supply_input_par.pressure_second_O3=0;
	TGTHT510_supply_input_par.pump_cooler=0;
	TGTHT510_supply_input_par.volum_F1=0;
	TGTHT510_supply_input_par.volum_F2=0;
	TGTHT510_supply_input_par.volum_F3=0;
	TGTHT510_supply_input_par.volum_O1=0;
	TGTHT510_supply_input_par.volum_O2=0;
	TGTHT510_supply_input_par.volum_O3=0;
	TGTHT510_supply_input_par.mode=0;
	TGTHT510_supply_input_par.pressure_repre_F1=0;
	TGTHT510_supply_input_par.pressure_repre_F2=0;
	TGTHT510_supply_input_par.pressure_repre_F3=0;
	TGTHT510_supply_input_par.pressure_repre_O1=0;
	TGTHT510_supply_input_par.pressure_repre_O2=0;
	TGTHT510_supply_input_par.pressure_repre_O3=0;
	
//注入补加参数，固定-----------------------------------------------------------
	
	TGTHT510_supply_input_par.time_exhaust=CONST_TIME_1MIN;
	TGTHT510_supply_input_par.time_comp_max=CONST_MAX_COMP_TIME;
	TGTHT510_supply_input_par.velocity_max=0;
	TGTHT510_supply_input_par.velocity_min=0;
	TGTHT510_supply_input_par.time_flow_max=0;
	TGTHT510_supply_input_par.temperature_mode=0;
	TGTHT510_supply_input_par.temperature_start_min=0x0010;//暂定
	TGTHT510_supply_input_par.temperature_start_max=0x0080;//暂定
	TGTHT510_supply_input_par.temperature_alarm=0;
	TGTHT510_supply_input_par.temperature_comp_cooler=0;
	TGTHT510_supply_input_par.pressure_comp_out=0;
	TGTHT510_supply_input_par.pressure_comp_out_stop=0;
	TGTHT510_supply_input_par.dp_high=0;
	TGTHT510_supply_input_par.dp1_low=30;
	TGTHT510_supply_input_par.dp2_low=0;
	TGTHT510_supply_input_par.time_repre_max=0x0960;//复压时间，暂定20min
	TGTHT510_supply_input_par.v_comp_start=0;
	TGTHT510_supply_input_par.v_comp_stop=0;
	TGTHT510_supply_input_par.time_delay_short=CONST_TIME_10SEC;
	TGTHT510_supply_input_par.time_delay_long=CONST_TIME_1MIN;
	TGTHT510_supply_input_par.time_bypath=CONST_TIME_10SEC;
	TGTHT510_supply_input_par.eps1=0xFF00;
	TGTHT510_supply_input_par.eps2=20;
	TGTHT510_supply_input_par.pressure_comp_in_max=0;
	TGTHT510_supply_input_par.pressure_comp_in_min=0;
	TGTHT510_supply_input_par.pressure_comp_out_min=0;
	TGTHT510_supply_input_par.pressure_hyc=0x0004;
	TGTHT510_supply_input_par.sensor_pipe_F=0;
	TGTHT510_supply_input_par.sensor_pipe_O=0;
	TGTHT510_supply_input_par.sensor_tank_F=0x0015;
	TGTHT510_supply_input_par.sensor_tank_O=0x0015;
	TGTHT510_supply_input_par.sensor_comp_in=0x0015;
	TGTHT510_supply_input_par.sensor_pipe_low=0;

//注入解码，------------------------------------------------------------------
	
	TGTHT510_supply_decode_par.interface_F=DECODE_NONE;
	TGTHT510_supply_decode_par.interface_O=DECODE_NONE;
	TGTHT510_supply_decode_par.number_tank_F=DECODE_NONE;
	TGTHT510_supply_decode_par.first_tank_F=DECODE_NONE;
	TGTHT510_supply_decode_par.second_tank_F=DECODE_NONE;
	TGTHT510_supply_decode_par.third_tank_F=DECODE_NONE;
	TGTHT510_supply_decode_par.number_tank_O=DECODE_NONE;
	TGTHT510_supply_decode_par.first_tank_O=DECODE_NONE;
	TGTHT510_supply_decode_par.second_tank_O=DECODE_NONE;
	TGTHT510_supply_decode_par.third_tank_O=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_F1=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_F1=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_F2=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_F2=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_F3=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_F3=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_O1=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_O1=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_O2=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_O2=DECODE_NONE;
	TGTHT510_supply_decode_par.number_gas_tank_O3=DECODE_NONE;
	TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_NONE;
	TGTHT510_supply_decode_par.second_gas_tank_O3=DECODE_NONE;
	TGTHT510_supply_decode_par.compressor_F=DECODE_NONE;
	TGTHT510_supply_decode_par.compressor_O=DECODE_NONE;
	TGTHT510_supply_decode_par.valve_out_compressor_F=DECODE_NONE;
	TGTHT510_supply_decode_par.valve_out_compressor_O=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_F1=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_F2=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_F3=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_O1=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_O2=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_tank_O3=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_pipe_low_F=DECODE_NONE;
	TGTHT510_supply_decode_par.sensor_pipe_low_O=DECODE_NONE;
	TGTHT510_supply_decode_par.cooler=DECODE_NONE;


//注入控制参数------------------------------------------------------------------

	TGTHT510_supply_ctrl.mode=MODE_HALF_AUTO;
	TGTHT510_supply_ctrl.state=STATE_NONE;
	TGTHT510_supply_ctrl.stage=STAGE_00_NONE;
	TGTHT510_supply_ctrl.step=STEP_NONE;
	TGTHT510_supply_ctrl.command=COMMAND_NONE;
	TGTHT510_supply_ctrl.receive=FALSE;
	TGTHT510_supply_ctrl.leak_flag=FALSE;
	TGTHT510_supply_ctrl.errno=ERRNO_NONE;
	TGTHT510_supply_ctrl.step_temp=STEP_NONE;
	TGTHT510_supply_ctrl.command_temp=COMMAND_NONE;

//压气机运行状态
	compressor_state.compressor_A_state=COMPRESSOR_STOP;
	compressor_state.compressor_B_state=COMPRESSOR_STOP;
	compressor_state.compressor_C_state=COMPRESSOR_STOP;
}


/******************************************************************************************
**名称：补加阶段主函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
void TGTHT510_supply_main(void)
{
	if(get_CPU()==CPU_B)//B机
	{
		if(CPU_B_receive_data.is_B_get_power==FALSE)
		{
			return;//B机，且未夺权，则补加流程不走
		}
		
	}
	
	TGTHT510_supply_time_dealing();//补加过程计时分函数
	
	switch(TGTHT510_supply_ctrl.mode)
	{
		case MODE_AUTO://自动补加模式
		{
			
			break;
		}
		
		case MODE_HALF_AUTO://半自动补加模式
		{
			TGTHT510_supply_main_half_auto();
			break;
		}
		
		case MODE_MAN_MADE://手动补加模式
		{
			
			break;
		}
		
		case MODE_NONE://无
		{
			
			break;
		}
		
		default:
		{
			break;
		}
		
		
	}

}

/******************************************************************************************
**名称：半自主补加阶段主函数
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_main_half_auto(void)
{
	
	switch(TGTHT510_supply_ctrl.state)
	{
		case STATE_RUN://补加运行
		{
			TGTHT510_supply_main_run();
			break;
		}
		
		case STATE_PAUSE://补加暂停
		{
			TGTHT510_supply_main_pause_deal();
			
			break;
		}
		
		case STATE_PAUSE_RESUME://暂停恢复
		{
			TGTHT510_supply_main_pause_resume_deal();
			
			break;
		}
		
		case STATE_BREAK://补加中止
		{
			TGTHT510_supply_main_break_deal();
			
			break;
		}
		
		case STATE_NONE://未补加
		{
			
			break;
		}
	}
	
}

/******************************************************************************************
**名称：补加运行
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_main_run(void)
{
	switch(TGTHT510_supply_ctrl.stage)
	{
		case STAGE_00_NONE://补加阶段0：空闲
		{
			
			break;
		}
		
		case STAGE_01_INPUT://补加阶段1：注入补加参数
		{
			TGTHT510_supply_stage01_input_main();
			break;
		}
		
		case STAGE_02_SET://补加阶段2：状态设置
		{
			TGTHT510_supply_stage02_set_main();
			break;
		}
		
		case STAGE_03_CONNECT://补加阶段3：浮动断接器插合
		{
			TGTHT510_supply_stage03_connect_main();
			break;
		}
		
		case STAGE_04_LEAK://补加阶段4：补加管路检漏
		{
			TGTHT510_supply_stage04_leak_main();
			break;
		}
		
		case STAGE_05_COMP_F://补加阶段5：燃贮箱抽气
		{
			TGTHT510_supply_stage05_comp_F_main();
			break;
		}
		
		case STAGE_06_PRE_F://补加阶段6：燃贮箱增压充填
		{
			TGTHT510_supply_stage06_pre_f_main();
			break;
		}
		
		case STAGE_07_FLOW_F://补加阶段7：燃推进剂补加流动
		{
			TGTHT510_supply_stage07_flow_f_main();
			break;
		}
		
		case STAGE_08_REPRE_F://补加阶段8：燃贮箱复压
		{
			TGTHT510_supply_stage08_repre_f_main();
			break;
		}
		
		case STAGE_09_COMP_F_T://补加阶段9：第三个燃贮箱抽气
		{
			TGTHT510_supply_stage09_comp_F_main();
			break;
		}
		
		case STAGE_10_FLOW_F_T://补加阶段10：第三个燃贮箱补加流动
		{
			TGTHT510_supply_stage10_flow_f_main();
			break;
		}
		
		case STAGE_11_REPRE_F_T://补加阶段11：第三个燃贮箱复压
		{
			TGTHT510_supply_stage11_repre_f_main();
			break;
		}
		
		case STAGE_12_BLOW_F://补加阶段12：燃管路吹除
		{
			TGTHT510_supply_stage12_blow_f_main();
			break;
		}
		
		case STAGE_13_COMP_O://补加阶段13：氧贮箱抽气
		{
			TGTHT510_supply_stage13_comp_O_main();
			break;
		}
		
		case STAGE_14_PRE_O://补加阶段14：氧贮箱增压充填
		{
			TGTHT510_supply_stage14_pre_o_main();
			break;
		}
		
		case STAGE_15_FLOW_O://补加阶段15：氧推进剂补加流动
		{
			TGTHT510_supply_stage15_flow_o_main();
			break;
		}
		
		case STAGE_16_REPRE_O://补加阶段16：氧贮箱复压
		{
			TGTHT510_supply_stage16_repre_o_main();
			break;
		}
		
		case STAGE_17_COMP_O_T://补加阶段17：第三个氧贮箱抽气
		{
			TGTHT510_supply_stage17_comp_O_main();
			break;
		}
		
		case STAGE_18_FLOW_O_T://补加阶段18：第三个氧贮箱补加流动
		{
			TGTHT510_supply_stage18_flow_o_main();
			break;
		}
		
		case STAGE_19_REPRE_O_T://补加阶段19：第三个氧贮箱复压
		{
			TGTHT510_supply_stage19_repre_o_main();
			break;
		}
		
		case STAGE_20_BLOW_O://补加阶段20：氧管路吹除
		{
			TGTHT510_supply_stage20_blow_o_main();
			break;
		}
		
		case STAGE_21_DISCONNECT://补加阶段21：浮动断接器脱开
		{
			TGTHT510_supply_stage21_disconnect_main();
			break;
		}
		
		case STAGE_22_RESUME://补加阶段22：状态恢复
		{
			TGTHT510_supply_stage22_resume_main();
			break;
		}
		
		default:
		{
			TGTHT510_supply_ctrl.state=STATE_NONE;//补加状态：空闲
			
			TGTHT510_supply_ctrl.stage=STAGE_00_NONE;//补加阶段：无
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		
	}

	
}



/******************************************************************************************
**名称：补加暂停
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_main_pause_deal(void)
{
	switch(TGTHT510_supply_ctrl.stage)
	{
		case STAGE_00_NONE://补加阶段0：空闲
		{
			
			
			break;
		}
		
		case STAGE_01_INPUT://补加阶段1：注入补加参数
		{
			TGTHT510_supply_pause_stage01_main();
			
			break;
		}
		
		case STAGE_02_SET://补加阶段2：状态设置
		{
			TGTHT510_supply_pause_stage02_main();
			
			break;
		}
		
		case STAGE_03_CONNECT://补加阶段3：浮动断接器插合
		{
			TGTHT510_supply_pause_stage03_main();
			
			break;
		}
		
		case STAGE_04_LEAK://补加阶段4：补加管路检漏
		{
			TGTHT510_supply_pause_stage04_main();
			
			break;
		}
		
		case STAGE_05_COMP_F://补加阶段5：燃贮箱抽气
		{
			TGTHT510_supply_pause_stage05_main();
			
			break;
		}
		
		case STAGE_06_PRE_F://补加阶段6：燃贮箱增压充填
		{
			TGTHT510_supply_pause_stage06_main();
			
			break;
		}
		
		case STAGE_07_FLOW_F://补加阶段7：燃推进剂补加流动
		{
			TGTHT510_supply_pause_stage07_main();
			
			break;
		}
		
		case STAGE_08_REPRE_F://补加阶段8：燃贮箱复压
		{
			TGTHT510_supply_pause_stage08_main();
			
			break;
		}
		
		case STAGE_09_COMP_F_T://补加阶段9：第三个燃贮箱抽气
		{
			TGTHT510_supply_pause_stage09_main();
			
			break;
		}
		
		case STAGE_10_FLOW_F_T://补加阶段10：第三个燃贮箱补加流动
		{
			TGTHT510_supply_pause_stage10_main();
			
			break;
		}
		
		case STAGE_11_REPRE_F_T://补加阶段11：第三个燃贮箱复压
		{
			TGTHT510_supply_pause_stage11_main();
			
			break;
		}
		
		case STAGE_12_BLOW_F://补加阶段12：燃管路吹除
		{
			TGTHT510_supply_pause_stage12_main();
			
			break;
		}
		
		case STAGE_13_COMP_O://补加阶段13：氧贮箱抽气
		{
			TGTHT510_supply_pause_stage13_main();
			
			break;
		}
		
		case STAGE_14_PRE_O://补加阶段14：氧贮箱增压充填
		{
			TGTHT510_supply_pause_stage14_main();
			
			break;
		}
		
		case STAGE_15_FLOW_O://补加阶段15：氧推进剂补加流动
		{
			TGTHT510_supply_pause_stage15_main();
			
			break;
		}
		
		case STAGE_16_REPRE_O://补加阶段16：氧贮箱复压
		{
			TGTHT510_supply_pause_stage16_main();
			
			break;
		}
		
		case STAGE_17_COMP_O_T://补加阶段17：第三个氧贮箱抽气
		{
			TGTHT510_supply_pause_stage17_main();
			
			break;
		}
		
		case STAGE_18_FLOW_O_T://补加阶段18：第三个氧贮箱补加流动
		{
			TGTHT510_supply_pause_stage18_main();
			
			break;
		}
		
		case STAGE_19_REPRE_O_T://补加阶段19：第三个氧贮箱复压
		{
			TGTHT510_supply_pause_stage19_main();
			
			break;
		}
		
		case STAGE_20_BLOW_O://补加阶段20：氧管路吹除
		{
			TGTHT510_supply_pause_stage20_main();
			
			break;
		}
		
		case STAGE_21_DISCONNECT://补加阶段21：浮动断接器脱开
		{
			TGTHT510_supply_pause_stage21_main();
			
			break;
		}
		
		case STAGE_22_RESUME://补加阶段22：状态恢复
		{
			TGTHT510_supply_pause_stage22_main();
			
			break;
		}
		
		default:
		{
			TGTHT510_supply_ctrl.state=STATE_NONE;//补加状态：空闲
			
			TGTHT510_supply_ctrl.stage=STAGE_00_NONE;//补加阶段：无
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		
	}

	
}


/******************************************************************************************
**名称：补加恢复
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_main_pause_resume_deal(void)
{
	switch(TGTHT510_supply_ctrl.stage)
	{
		case STAGE_00_NONE://补加阶段0：空闲
		{
			
			
			break;
		}
		
		case STAGE_01_INPUT://补加阶段1：注入补加参数
		{
			TGTHT510_supply_pause_resume_stage01_main();
			
			break;
		}
		
		case STAGE_02_SET://补加阶段2：状态设置
		{
			TGTHT510_supply_pause_resume_stage02_main();
			
			break;
		}
		
		case STAGE_03_CONNECT://补加阶段3：浮动断接器插合
		{
			TGTHT510_supply_pause_resume_stage03_main();
			
			break;
		}
		
		case STAGE_04_LEAK://补加阶段4：补加管路检漏
		{
			TGTHT510_supply_pause_resume_stage04_main();
			
			break;
		}
		
		case STAGE_05_COMP_F://补加阶段5：燃贮箱抽气
		{
			TGTHT510_supply_pause_resume_stage05_main();
			
			break;
		}
		
		case STAGE_06_PRE_F://补加阶段6：燃贮箱增压充填
		{
			TGTHT510_supply_pause_resume_stage06_main();
			
			break;
		}
		
		case STAGE_07_FLOW_F://补加阶段7：燃推进剂补加流动
		{
			TGTHT510_supply_pause_resume_stage07_main();
			
			break;
		}
		
		case STAGE_08_REPRE_F://补加阶段8：燃贮箱复压
		{
			TGTHT510_supply_pause_resume_stage08_main();
			
			break;
		}
		
		case STAGE_09_COMP_F_T://补加阶段9：第三个燃贮箱抽气
		{
			TGTHT510_supply_pause_resume_stage09_main();
			
			break;
		}
		
		case STAGE_10_FLOW_F_T://补加阶段10：第三个燃贮箱补加流动
		{
			TGTHT510_supply_pause_resume_stage10_main();
			
			break;
		}
		
		case STAGE_11_REPRE_F_T://补加阶段11：第三个燃贮箱复压
		{
			TGTHT510_supply_pause_resume_stage11_main();
			
			break;
		}
		
		case STAGE_12_BLOW_F://补加阶段12：燃管路吹除
		{
			TGTHT510_supply_pause_resume_stage12_main();
			
			break;
		}
		
		case STAGE_13_COMP_O://补加阶段13：氧贮箱抽气
		{
			TGTHT510_supply_pause_resume_stage13_main();
			
			break;
		}
		
		case STAGE_14_PRE_O://补加阶段14：氧贮箱增压充填
		{
			TGTHT510_supply_pause_resume_stage14_main();
			
			break;
		}
		
		case STAGE_15_FLOW_O://补加阶段15：氧推进剂补加流动
		{
			TGTHT510_supply_pause_resume_stage15_main();
			
			break;
		}
		
		case STAGE_16_REPRE_O://补加阶段16：氧贮箱复压
		{
			TGTHT510_supply_pause_resume_stage16_main();
			
			break;
		}
		
		case STAGE_17_COMP_O_T://补加阶段17：第三个氧贮箱抽气
		{
			TGTHT510_supply_pause_resume_stage17_main();
			
			break;
		}
		
		case STAGE_18_FLOW_O_T://补加阶段18：第三个氧贮箱补加流动
		{
			TGTHT510_supply_pause_resume_stage18_main();
			
			break;
		}
		
		case STAGE_19_REPRE_O_T://补加阶段19：第三个氧贮箱复压
		{
			TGTHT510_supply_pause_resume_stage19_main();
			
			break;
		}
		
		case STAGE_20_BLOW_O://补加阶段20：氧管路吹除
		{
			TGTHT510_supply_pause_resume_stage20_main();
			
			break;
		}
		
		case STAGE_21_DISCONNECT://补加阶段21：浮动断接器脱开
		{
			TGTHT510_supply_pause_resume_stage21_main();
			
			break;
		}
		
		case STAGE_22_RESUME://补加阶段22：状态恢复
		{
			TGTHT510_supply_pause_resume_stage22_main();
			
			break;
		}
		
		default:
		{
			TGTHT510_supply_ctrl.state=STATE_NONE;//补加状态：空闲
			
			TGTHT510_supply_ctrl.stage=STAGE_00_NONE;//补加阶段：无
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		
	}

	
}


/******************************************************************************************
**名称：补加中止
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_main_break_deal(void)
{
	switch(TGTHT510_supply_ctrl.stage)
	{
		case STAGE_00_NONE://补加阶段0：空闲
		{
			
			
			break;
		}
		
		case STAGE_01_INPUT://补加阶段1：注入补加参数
		{
			TGTHT510_supply_break_stage01_main();

			
			break;
		}
		
		case STAGE_02_SET://补加阶段2：状态设置
		{
			TGTHT510_supply_break_stage02_main();

			
			break;
		}
		
		case STAGE_03_CONNECT://补加阶段3：浮动断接器插合
		{
			TGTHT510_supply_break_stage03_main();
			
			break;
		}
		
		case STAGE_04_LEAK://补加阶段4：补加管路检漏
		{
			TGTHT510_supply_break_stage04_main();
			
			break;
		}
		
		case STAGE_05_COMP_F://补加阶段5：燃贮箱抽气
		{
			TGTHT510_supply_break_stage05_main();
			
			break;
		}
		
		case STAGE_06_PRE_F://补加阶段6：燃贮箱增压充填
		{
			TGTHT510_supply_break_stage06_main();
			
			break;
		}
		
		case STAGE_07_FLOW_F://补加阶段7：燃推进剂补加流动
		{
			TGTHT510_supply_break_stage07_main();
			
			break;
		}
		
		case STAGE_08_REPRE_F://补加阶段8：燃贮箱复压
		{
			TGTHT510_supply_break_stage08_main();
			
			break;
		}
		
		case STAGE_09_COMP_F_T://补加阶段9：第三个燃贮箱抽气
		{
			TGTHT510_supply_break_stage09_main();
			
			break;
		}
		
		case STAGE_10_FLOW_F_T://补加阶段10：第三个燃贮箱补加流动
		{
			TGTHT510_supply_break_stage10_main();
			
			break;
		}
		
		case STAGE_11_REPRE_F_T://补加阶段11：第三个燃贮箱复压
		{
			TGTHT510_supply_break_stage11_main();
			
			break;
		}
		
		case STAGE_12_BLOW_F://补加阶段12：燃管路吹除
		{
			TGTHT510_supply_break_stage12_main();
			
			break;
		}
		
		case STAGE_13_COMP_O://补加阶段13：氧贮箱抽气
		{
			TGTHT510_supply_break_stage13_main();
			
			break;
		}
		
		case STAGE_14_PRE_O://补加阶段14：氧贮箱增压充填
		{
			TGTHT510_supply_break_stage14_main();
			
			break;
		}
		
		case STAGE_15_FLOW_O://补加阶段15：氧推进剂补加流动
		{
			TGTHT510_supply_break_stage15_main();
			
			break;
		}
		
		case STAGE_16_REPRE_O://补加阶段16：氧贮箱复压
		{
			TGTHT510_supply_break_stage16_main();
			
			break;
		}
		
		case STAGE_17_COMP_O_T://补加阶段17：第三个氧贮箱抽气
		{
			TGTHT510_supply_break_stage17_main();
			
			break;
		}
		
		case STAGE_18_FLOW_O_T://补加阶段18：第三个氧贮箱补加流动
		{
			TGTHT510_supply_break_stage18_main();
			
			break;
		}
		
		case STAGE_19_REPRE_O_T://补加阶段19：第三个氧贮箱复压
		{
			TGTHT510_supply_break_stage19_main();
			
			break;
		}
		
		case STAGE_20_BLOW_O://补加阶段20：氧管路吹除
		{
			TGTHT510_supply_break_stage20_main();
			
			break;
		}
		
		case STAGE_21_DISCONNECT://补加阶段21：浮动断接器脱开
		{
			TGTHT510_supply_break_stage21_main();
			
			break;
		}
		
		case STAGE_22_RESUME://补加阶段22：状态恢复
		{
			TGTHT510_supply_break_stage22_main();
			
			break;
		}
		
		default:
		{
			TGTHT510_supply_ctrl.state=STATE_NONE;//补加状态：空闲
			
			TGTHT510_supply_ctrl.stage=STAGE_00_NONE;//补加阶段：无
			
			TGTHT510_supply_ctrl.step=STEP_NONE;//补加步骤：无
			
			TGTHT510_supply_ctrl.command=COMMAND_NONE;//补加指令：无
			
			break;
		}
		
		
	}

	
}








/******************************************************************************************
**名称：
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_main_pause(uint16 errno)
{
	TGTHT510_supply_ctrl.errno=errno;
	
	TGTHT510_supply_ctrl.step_temp=TGTHT510_supply_ctrl.step;
	
	TGTHT510_supply_ctrl.command_temp=TGTHT510_supply_ctrl.command;
	
	TGTHT510_supply_ctrl.state=STATE_PAUSE;
	
	TGTHT510_supply_ctrl.step=STEP_START;
	
	TGTHT510_supply_ctrl.command=COMMAND_START;

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

void TGTHT510_supply_main_lvb_set(uint16 code)
{
	if((code>=LVb1K)&&(code<=LVb87G))//输入指令代码为自锁阀开关指令，且合法
	{
		TGTHT510_valvecontrol_struct.command_from_supply=code;//阀门内部地址编码
		TGTHT510_valvecontrol_struct.command_from_supply_time=2;//脉宽200ms
	}
}

/******************************************************************************************
**名称：补加系统阀门状态判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：状态判断正确则返回TRUE，否则返回FALSE
输入为VALVE_ON或者VALVE_OFF
输入为STATE_LVb01，STATE_LVb02，STATE_LVb03，STATE_LVb04………………
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_main_lvb_get(uint16 code,uint16 on_or_off)
{
	uint16 temp;
	
	if(code>STATE_DVb)//编码非法
	{
		return FALSE;
	}
	
	if((on_or_off!=VALVE_ON)&&(on_or_off!=VALVE_OFF))//编码非法
	{
		return FALSE;
	}
	
	temp=TGTHT510_collectANDgroup_is_valve_state(code);
	
	if(temp==on_or_off)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
	
}


/******************************************************************************************
**名称：推进系统阀门置位
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_main_lvt_set(uint16 code)
{
	if(code>LVt42G)//编码非法
	{
		return;
	}
	
	TGTHT510_collectANDgroup_equiment_command_generate(code);
}


/******************************************************************************************
**名称：推进系统阀门状态判断
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：状态判断正确则返回TRUE，否则返回FALSE
输入为VALVE_ON或者VALVE_OFF
输入为STATE_LVt01，STATE_LVt02，STATE_LVt03，STATE_LVt04………………
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_main_lvt_get(uint16 code,uint16 on_or_off)
{
	uint16 temp;
	
	if(code>STATE_LVt40)//编码非法
	{
		return FALSE;
	}
	
	if((on_or_off!=VALVE_ON)&&(on_or_off!=VALVE_OFF))//编码非法
	{
		return FALSE;
	}
	
	temp=TGTHT510_supply_main_valve_state_TGTHT520(code);
	
	if(temp==TGTHT520_VALVE_ON)
	{
		if(on_or_off==VALVE_ON)
		{
			return TRUE;
		}
		
		else
		{
			return FALSE;
		}
	}
	
	else if(temp==TGTHT520_VALVE_OFF)
	{
		if(on_or_off==VALVE_OFF)
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
**名称：推进控制驱动器自锁阀开关状态判断函数
**作者：蒋章
**日期：20160217
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

uint16 TGTHT510_supply_main_valve_state_TGTHT520(uint16 state_code)
{
	uint16 lookup_state;
	uint16 lookup_word;
	uint16 valve_state;
	
	if(state_code<=STATE_LVt28)//主路推进控制驱动器阀门
	{
		lookup_state=valve_state_TGTHT520a_lookup[state_code];
		
		lookup_word=valve_word_TGTHT520a_lookup[state_code];
		
		valve_state=(TGTHT510_1553B_data_TGTHT520a[lookup_word]&lookup_state);
	
	}
	
	else if((state_code>=STATE_LVt18)&&(state_code<=STATE_LVt40))//备路推进控制驱动器阀门
	{
		lookup_state=valve_state_TGTHT520b_lookup[state_code-STATE_OFFSET];
		
		lookup_word=valve_word_TGTHT520b_lookup[state_code-STATE_OFFSET];
		
		valve_state=(TGTHT510_1553B_data_TGTHT520b[lookup_word]&lookup_state);
		
	}
	
	else//函数输入参数非法
	{
		return TGTHT520_VALVE_NONE;
		
	}
	
	if(lookup_state==TGTHT520_L_BYTE_L_BIT)
	{
		valve_state=valve_state;
			
	}
		
	else if(lookup_state==TGTHT520_L_BYTE_H_BIT)
	{
		valve_state=(valve_state>>4);
			
	}
		
	else if(lookup_state==TGTHT520_H_BYTE_L_BIT)
	{
		valve_state=(valve_state>>8);
			
	}
		
	else if(lookup_state==TGTHT520_H_BYTE_H_BIT)
	{
		valve_state=(valve_state>>12);
	}
		
	else
	{
		return TGTHT520_VALVE_NONE;
	}
	
	if(valve_state==TGTHT520_VALVE_ON)
	{
		return TGTHT520_VALVE_ON;
		
	}
	
	else if(valve_state==TGTHT520_VALVE_OFF)
	{
		return TGTHT520_VALVE_OFF;
	}
	
	else
	{
		return TGTHT520_VALVE_NONE;
	}

}


/******************************************************************************************
**名称：除自锁阀以外的其他设备管理指令函数
**作者：蒋章
**日期：20160217
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_main_equ_command_set(uint16 code)
{
	if((code<TGTHT530a_ON_POWER)||(code>VALVE_SUPPLY_OFF_POWER))//编码错误
	{
		return;
	}
	
	TGTHT510_collectANDgroup_equiment_command_generate(code);
	
	switch(code)
	{
		case COMPRESS_A_START://压气机A启动
		{
			compressor_state.compressor_A_state=COMPRESSOR_RUN;
			break;
		}
		
		case COMPRESS_B_START://压气机B启动
		{
			compressor_state.compressor_B_state=COMPRESSOR_RUN;
			break;
		}
		
		case COMPRESS_C_START://压气机C启动
		{
			compressor_state.compressor_C_state=COMPRESSOR_RUN;
			break;
		}
		
		case COMPRESS_A_STOP://压气机A停机
		{
			compressor_state.compressor_A_state=COMPRESSOR_STOP;
			break;
		}
		
		case COMPRESS_B_STOP://压气机B停机
		{
			compressor_state.compressor_B_state=COMPRESSOR_STOP;
			break;
		}
		
		case COMPRESS_C_STOP://压气机C停机
		{
			compressor_state.compressor_C_state=COMPRESSOR_STOP;
			break;
		}
		
		default:
		{
			break;
		}
	}
	
}



/******************************************************************************************
**名称：
**作者：蒋章
**日期：20160217
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_time_dealing(void)
{
	if(TGTHT510_supply_time.time_stage_flag==TRUE)
	{
		TGTHT510_supply_time.time_stage++;
	}
	
	else
	{
		TGTHT510_supply_time.time_stage=0;
	}
	
	if(TGTHT510_supply_time.time_step_flag==TRUE)
	{
		TGTHT510_supply_time.time_step++;
	}
	
	else
	{
		TGTHT510_supply_time.time_step=0;
	}

}

/******************************************************************************************
**名称：
**作者：蒋章
**日期：20160217
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_time_stage_start(void)
{
	TGTHT510_supply_time.time_stage_flag=TRUE;
	
	TGTHT510_supply_time.time_stage=0;
}


/******************************************************************************************
**名称：
**作者：蒋章
**日期：20160217
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_time_stage_end(void)
{
	TGTHT510_supply_time.time_stage_flag=FALSE;
}


/******************************************************************************************
**名称：
**作者：蒋章
**日期：20160217
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_time_stage_get(uint32 *time_val)
{
	*time_val=TGTHT510_supply_time.time_stage;
}



/******************************************************************************************
**名称：
**作者：蒋章
**日期：20160217
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_time_step_start(void)
{
	TGTHT510_supply_time.time_step_flag=TRUE;
}


/******************************************************************************************
**名称：
**作者：蒋章
**日期：20160217
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_supply_time_step_end(void)
{
	TGTHT510_supply_time.time_step_flag=FALSE;
}


/******************************************************************************************
**名称：
**作者：蒋章
**日期：20160217
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16	TGTHT510_supply_time_step_is_get(uint32 const_val)
{
	if(TGTHT510_supply_time.time_step>=const_val)//计时时间到
	{
		TGTHT510_supply_time_step_end();
		
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}	
}





















