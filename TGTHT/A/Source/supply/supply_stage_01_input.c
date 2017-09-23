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
void TGTHT510_supply_stage01_input_main(void)
{
	switch(TGTHT510_supply_ctrl.step)
	{
		case STEP_START://开始
		{
			TGTHT510_supply_time_stage_start();
			
			TGTHT510_supply_ctrl.step=STEP_01_IS_INPUT;
			break;
		}
		
		case STEP_01_IS_INPUT://是否接受到补加参数
		{
			if(TGTHT510_supply_ctrl.receive==TRUE)//注入参数接受结束
			{
				TGTHT510_supply_ctrl.receive=FALSE;
				
				if(TGTHT510_supply_stage01_input_decode()==TRUE)
				{
					TGTHT510_supply_ctrl.step=STEP_END;
				}
				
				else
				{
					TGTHT510_supply_stage01_input_clear();
					
					TGTHT510_supply_main_pause(ERRNO_INPUT_PAR_DECODE);
					//解码错误！！！！暂停！！！！！！！
				}
				
			}
			
			else
			{
				asm("nop;");
			}
			
			break;
		}
		
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
void TGTHT510_supply_stage01_input_clear(void)
{
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
}



/******************************************************************************************
**名称：
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：解码正确，返回TRUE，否则为FALSE

**************************************注入补加参数（变化参数）****************************

1、燃补加接口（1字节）：
0x03是后向主R1，
0x0c是后向备R2，
0x30是前向主R3，
0xc0是前向备R4。

2、氧补加接口（1字节）：
0x03是后向主O1，
0x0c是后向备O2，
0x30是前向主O3，
0xc0是前向备O4。

3、燃贮箱补加顺序（1字节）:
bit0、1为第一个贮箱的序号，
bit2、3为第二个贮箱的序号，
bit4、5为第三个贮箱的序号，
bit6、7为补加燃贮箱的数量，
01表示燃贮箱F1
10表示燃贮箱F2
11表示燃贮箱F3
00表示无贮箱

4、氧贮箱补加顺序（1字节）:
bit0、1为第一个贮箱的序号，
bit2、3为第二个贮箱的序号，
bit4、5为第三个贮箱的序号，
bit6、7为补加氧贮箱的数量，
01表示氧贮箱O1
10表示氧贮箱O2
11表示氧贮箱O3
00表示无贮箱


5、燃贮箱F1的气瓶抽气顺序（1字节）
bit0、1为第一个抽气气瓶的序号，
bit2、3为第二个抽气气瓶的序号，
bit4、5为空
bit7、8为抽气的气瓶数量
01表示燃气瓶F1
10表示燃气瓶F2
11表示燃气瓶F3
00表示无气瓶

6、燃贮箱F2的气瓶抽气顺序（1字节）
bit0、1为第一个抽气气瓶的序号，
bit2、3为第二个抽气气瓶的序号，
bit4、5为空
bit7、8为抽气的气瓶数量
01表示燃气瓶F1
10表示燃气瓶F2
11表示燃气瓶F3
00表示无气瓶

7、燃贮箱F3的气瓶抽气顺序（1字节）
bit0、1为第一个抽气气瓶的序号，
bit2、3为第二个抽气气瓶的序号，
bit4、5为空
bit7、8为抽气的气瓶数量
01表示燃气瓶F1
10表示燃气瓶F2
11表示燃气瓶F3
00表示无气瓶

8、氧贮箱O1的气瓶抽气顺序（1字节）
bit0、1为第一个抽气气瓶的序号，
bit2、3为第二个抽气气瓶的序号，
bit4、5为空
bit7、8为抽气的气瓶数量
01表示氧气瓶O1
10表示氧气瓶O2
11表示氧气瓶O3
00表示无气瓶

9、氧贮箱O2的气瓶抽气顺序（1字节）
bit0、1为第一个抽气气瓶的序号，
bit2、3为第二个抽气气瓶的序号，
bit4、5为空
bit7、8为抽气的气瓶数量
01表示氧气瓶O1
10表示氧气瓶O2
11表示氧气瓶O3
00表示无气瓶

10、氧贮箱O3的气瓶抽气顺序（1字节）
bit0、1为第一个抽气气瓶的序号，
bit2、3为第二个抽气气瓶的序号，
bit4、5为空
bit7、8为抽气的气瓶数量
01表示氧气瓶O1
10表示氧气瓶O2
11表示氧气瓶O3
00表示无气瓶

11、燃氧抽气压气机号与出口阀门（2字节）
bit0、1为01表示燃抽气压气机为B机，为10表示燃抽气压气机为C机
bit2、3为01表示开启的燃压气机出口阀门为主，10表示开启的燃压气机出口阀门为备
bit4、5为01表示氧抽气压气机为A机，为10表示氧抽气压气机为C机
bit6、7为01表示开启的氧压气机出口阀门为主，10表示开启的氧压气机出口阀门为备
bit8-15为空

12、燃贮箱F1第一个气瓶的抽气后末压值（2字节）

13、燃贮箱F1第二个气瓶的抽气后末压值（2字节）

14、燃贮箱F2第一个气瓶的抽气后末压值（2字节）

15、燃贮箱F2第二个气瓶的抽气后末压值（2字节）

16、燃贮箱F3第一个气瓶的抽气后末压值（2字节）

17、燃贮箱F3第二个气瓶的抽气后末压值（2字节）

18、氧贮箱O1第一个气瓶的抽气后末压值（2字节）

19、氧贮箱O1第二个气瓶的抽气后末压值（2字节）

20、氧贮箱O2第一个气瓶的抽气后末压值（2字节）

21、氧贮箱O2第二个气瓶的抽气后末压值（2字节）

22、氧贮箱O3第一个气瓶的抽气后末压值（2字节）

23、氧贮箱O3第二个气瓶的抽气后末压值（2字节）

24、液冷模块泵号（2字节）
高字节无效，
低字节为0x03是主液冷I泵
低字节为0x0c是主液冷II泵
低字节为0x30是备液冷I泵
低字节为0xc0是备液冷II泵

25、燃贮箱F1补加到位剩余量（2字节）

26、燃贮箱F2补加到位剩余量（2字节）

27、燃贮箱F3补加到位剩余量（2字节）

28、氧贮箱O1补加到位剩余量（2字节）

29、氧贮箱O2补加到位剩余量（2字节）

30、氧贮箱O3补加到位剩余量（2字节）

31、补加模式（2字节）
为0x00ff为半自主补加模式
为0xff00为自主补加模式

32、燃贮箱F1复压压力值（2字节）

33、燃贮箱F2复压压力值（2字节）

34、燃贮箱F3复压压力值（2字节）

35、氧贮箱O1复压压力值（2字节）

36、氧贮箱O2复压压力值（2字节）

37、氧贮箱O3复压压力值（2字节）


**************************************注入补加参数（不变参数）****************************

1、燃贮箱压力传感器设定（2字节）
高字节无效，
低字节bit0、1为01表示燃贮箱F1使用主份传感器PTt14，为10表示燃贮箱F1使用备份传感器PTt20
低字节bit2、3为01表示燃贮箱F2使用主份传感器PTt16，为10表示燃贮箱F2使用备份传感器PTt22
低字节bit4、5为01表示燃贮箱F3使用主份传感器PTt18，为10表示燃贮箱F3使用备份传感器PTt24

2、氧贮箱压力传感器设定（2字节）
高字节无效，
低字节bit0、1为01表示氧贮箱O1使用主份传感器PTt13，为10表示氧贮箱O1使用备份传感器PTt19
低字节bit2、3为01表示氧贮箱O2使用主份传感器PTt15，为10表示氧贮箱O2使用备份传感器PTt21
低字节bit4、5为01表示氧贮箱O3使用主份传感器PTt17，为10表示氧贮箱O3使用备份传感器PTt23

3、低压气路传感器设定（2字节）
高字节为0x00是燃路使用传感器PTb2
高字节为0x03是燃路使用传感器PTb4
高字节为0x0c是燃路使用传感器PTb24

低字节为0x00是氧路使用传感器PTb1
低字节为0x03是氧路使用传感器PTb3
低字节为0x0c是氧路使用传感器PTb24

4、压气机进口压力传感器设定（2字节）
高字节无效，
低字节bit0、1为01表示氧压气机A进口压力传感器PTb03，为10表示氧压气机A进口压力传感器PTb29
低字节bit2、3为01表示燃压气机B进口压力传感器PTb04，为10表示氧压气机B进口压力传感器PTb28
高字节bit4、5、6、7为0001表示备份压气机C进口压力传感器为PTb24，
为1000表示备份压气机C进口压力传感器为PTb24。



-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/
uint16 TGTHT510_supply_stage01_input_decode(void)
{
	uint16 return_state;
	
	return_state=TRUE;
	
	//燃补加接口解码
	if(TGTHT510_supply_input_par.interface_F==0x03)
	{
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R1;
	}
	
	else if(TGTHT510_supply_input_par.interface_F==0x0c)
	{
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R2;
	}
	
	else if(TGTHT510_supply_input_par.interface_F==0x30)
	{
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R3;
	}
	
	else if(TGTHT510_supply_input_par.interface_F==0xc0)
	{
		TGTHT510_supply_decode_par.interface_F=DECODE_INTERFACE_R4;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	//氧补加接口解码
	if(TGTHT510_supply_input_par.interface_O==0x03)
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O1;
	}
	
	else if(TGTHT510_supply_input_par.interface_O==0x0c)
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O2;
	}
	
	else if(TGTHT510_supply_input_par.interface_O==0x30)
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O3;
	}
	
	else if(TGTHT510_supply_input_par.interface_O==0xc0)
	{
		TGTHT510_supply_decode_par.interface_O=DECODE_INTERFACE_O4;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	//燃贮箱补加顺序（1字节）
	
	if((TGTHT510_supply_input_par.sequence_tank_F>>6)==0)//燃贮箱补加数量为0
	{
		TGTHT510_supply_decode_par.number_tank_F=0;
		TGTHT510_supply_decode_par.first_tank_F=DECODE_NONE;
		TGTHT510_supply_decode_par.second_tank_F=DECODE_NONE;
		TGTHT510_supply_decode_par.third_tank_F=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_tank_F>>6)==1)//燃贮箱补加数量为1
	{
		TGTHT510_supply_decode_par.number_tank_F=1;
		TGTHT510_supply_decode_par.second_tank_F=DECODE_NONE;
		TGTHT510_supply_decode_par.third_tank_F=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x01)//第一个燃贮箱F1
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x02)//第一个燃贮箱F2
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x03)//第一个燃贮箱F3
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_tank_F>>6)==2)//燃贮箱补加数量为2
	{
		TGTHT510_supply_decode_par.number_tank_F=2;
		TGTHT510_supply_decode_par.third_tank_F=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x01)//第一个燃贮箱F1
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x02)//第一个燃贮箱F2
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x03)//第一个燃贮箱F3
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_tank_F&0x0c)>>2)==0x01)//第二个燃贮箱F1
		{
			TGTHT510_supply_decode_par.second_tank_F=DECODE_TANK_F1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_F&0x0c)>>2)==0x02)//第二个燃贮箱F2
		{
			TGTHT510_supply_decode_par.second_tank_F=DECODE_TANK_F2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_F&0x0c)>>2)==0x03)//第二个燃贮箱F3
		{
			TGTHT510_supply_decode_par.second_tank_F=DECODE_TANK_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_tank_F>>6)==3)//燃贮箱补加数量为3
	{
		TGTHT510_supply_decode_par.number_tank_F=3;
		
		if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x01)//第一个燃贮箱F1
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x02)//第一个燃贮箱F2
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_F&0x03)==0x03)//第一个燃贮箱F3
		{
			TGTHT510_supply_decode_par.first_tank_F=DECODE_TANK_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_tank_F&0x0c)>>2)==0x01)//第二个燃贮箱F1
		{
			TGTHT510_supply_decode_par.second_tank_F=DECODE_TANK_F1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_F&0x0c)>>2)==0x02)//第二个燃贮箱F2
		{
			TGTHT510_supply_decode_par.second_tank_F=DECODE_TANK_F2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_F&0x0c)>>2)==0x03)//第二个燃贮箱F3
		{
			TGTHT510_supply_decode_par.second_tank_F=DECODE_TANK_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_tank_F&0x30)>>4)==0x01)//第三个燃贮箱F1
		{
			TGTHT510_supply_decode_par.third_tank_F=DECODE_TANK_F1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_F&0x30)>>4)==0x02)//第三个燃贮箱F2
		{
			TGTHT510_supply_decode_par.third_tank_F=DECODE_TANK_F2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_F&0x30)>>4)==0x03)//第三个燃贮箱F3
		{
			TGTHT510_supply_decode_par.third_tank_F=DECODE_TANK_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
	
	}
	
	else//错误
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//氧贮箱补加顺序（1字节）
	
	if((TGTHT510_supply_input_par.sequence_tank_O>>6)==0)//氧贮箱补加数量为0
	{
		TGTHT510_supply_decode_par.number_tank_O=0;
		TGTHT510_supply_decode_par.first_tank_O=DECODE_NONE;
		TGTHT510_supply_decode_par.second_tank_O=DECODE_NONE;
		TGTHT510_supply_decode_par.third_tank_O=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_tank_O>>6)==1)//氧贮箱补加数量为1
	{
		TGTHT510_supply_decode_par.number_tank_O=1;
		TGTHT510_supply_decode_par.second_tank_O=DECODE_NONE;
		TGTHT510_supply_decode_par.third_tank_O=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x01)//第一个氧贮箱F1
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x02)//第一个氧贮箱F2
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x03)//第一个氧贮箱F3
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_tank_O>>6)==2)//氧贮箱补加数量为2
	{
		TGTHT510_supply_decode_par.number_tank_O=2;
		TGTHT510_supply_decode_par.third_tank_O=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x01)//第一个氧贮箱F1
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x02)//第一个氧贮箱F2
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x03)//第一个氧贮箱F3
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_tank_O&0x0c)>>2)==0x01)//第二个氧贮箱F1
		{
			TGTHT510_supply_decode_par.second_tank_O=DECODE_TANK_O1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_O&0x0c)>>2)==0x02)//第二个氧贮箱F2
		{
			TGTHT510_supply_decode_par.second_tank_O=DECODE_TANK_O2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_O&0x0c)>>2)==0x03)//第二个氧贮箱F3
		{
			TGTHT510_supply_decode_par.second_tank_O=DECODE_TANK_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_tank_O>>6)==3)//氧贮箱补加数量为3
	{
		TGTHT510_supply_decode_par.number_tank_O=3;
		
		if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x01)//第一个氧贮箱F1
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x02)//第一个氧贮箱F2
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_tank_O&0x03)==0x03)//第一个氧贮箱F3
		{
			TGTHT510_supply_decode_par.first_tank_O=DECODE_TANK_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_tank_O&0x0c)>>2)==0x01)//第二个氧贮箱F1
		{
			TGTHT510_supply_decode_par.second_tank_O=DECODE_TANK_O1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_O&0x0c)>>2)==0x02)//第二个氧贮箱F2
		{
			TGTHT510_supply_decode_par.second_tank_O=DECODE_TANK_O2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_O&0x0c)>>2)==0x03)//第二个氧贮箱F3
		{
			TGTHT510_supply_decode_par.second_tank_O=DECODE_TANK_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_tank_O&0x30)>>4)==0x01)//第三个氧贮箱F1
		{
			TGTHT510_supply_decode_par.third_tank_O=DECODE_TANK_O1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_O&0x30)>>4)==0x02)//第三个氧贮箱F2
		{
			TGTHT510_supply_decode_par.third_tank_O=DECODE_TANK_O2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_tank_O&0x30)>>4)==0x03)//第三个氧贮箱F3
		{
			TGTHT510_supply_decode_par.third_tank_O=DECODE_TANK_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
	
	}
	
	else//错误
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//燃贮箱F1的气瓶抽气顺序（1字节）
	
	if((TGTHT510_supply_input_par.sequence_gas_F1>>6)==0)//燃贮箱F1的气瓶抽气数量为0
	{
		TGTHT510_supply_decode_par.number_gas_tank_F1=0;
		TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_NONE;
		TGTHT510_supply_decode_par.second_gas_tank_F1=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_F1>>6)==1)//燃贮箱F1的气瓶抽气数量为1
	{
		TGTHT510_supply_decode_par.number_gas_tank_F1=1;
		TGTHT510_supply_decode_par.second_gas_tank_F1=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_gas_F1&0x03)==0x01)//第一个抽气气瓶为F1
		{
			TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_GAS_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F1&0x03)==0x02)//第一个抽气气瓶为F2
		{
			TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_GAS_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F1&0x03)==0x03)//第一个抽气气瓶为F3
		{
			TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_F1>>6)==2)//燃贮箱F1的气瓶抽气数量为2
	{
		TGTHT510_supply_decode_par.number_gas_tank_F1=2;
		
		if((TGTHT510_supply_input_par.sequence_gas_F1&0x03)==0x01)//第一个抽气气瓶为F1
		{
			TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_GAS_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F1&0x03)==0x02)//第一个抽气气瓶为F2
		{
			TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_GAS_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F1&0x03)==0x03)//第一个抽气气瓶为F3
		{
			TGTHT510_supply_decode_par.first_gas_tank_F1=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_gas_F1&0x0c)>>2)==0x01)//第二个抽气气瓶为F1
		{
			TGTHT510_supply_decode_par.second_gas_tank_F1=DECODE_GAS_F1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_F1&0x0c)>>2)==0x02)//第二个抽气气瓶为F2
		{
			TGTHT510_supply_decode_par.second_gas_tank_F1=DECODE_GAS_F2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_F1&0x0c)>>2)==0x03)//第二个抽气气瓶为F3
		{
			TGTHT510_supply_decode_par.second_gas_tank_F1=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//燃贮箱F2的气瓶抽气顺序（1字节）
	
	if((TGTHT510_supply_input_par.sequence_gas_F2>>6)==0)//燃贮箱F2的气瓶抽气数量为0
	{
		TGTHT510_supply_decode_par.number_gas_tank_F2=0;
		TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_NONE;
		TGTHT510_supply_decode_par.second_gas_tank_F2=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_F2>>6)==1)//燃贮箱F2的气瓶抽气数量为1
	{
		TGTHT510_supply_decode_par.number_gas_tank_F2=1;
		TGTHT510_supply_decode_par.second_gas_tank_F2=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_gas_F2&0x03)==0x01)//第一个抽气气瓶为F1
		{
			TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_GAS_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F2&0x03)==0x02)//第一个抽气气瓶为F2
		{
			TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_GAS_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F2&0x03)==0x03)//第一个抽气气瓶为F3
		{
			TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_F2>>6)==2)//燃贮箱F2的气瓶抽气数量为2
	{
		TGTHT510_supply_decode_par.number_gas_tank_F2=2;
		
		if((TGTHT510_supply_input_par.sequence_gas_F2&0x03)==0x01)//第一个抽气气瓶为F1
		{
			TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_GAS_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F2&0x03)==0x02)//第一个抽气气瓶为F2
		{
			TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_GAS_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F2&0x03)==0x03)//第一个抽气气瓶为F3
		{
			TGTHT510_supply_decode_par.first_gas_tank_F2=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_gas_F2&0x0c)>>2)==0x01)//第二个抽气气瓶为F1
		{
			TGTHT510_supply_decode_par.second_gas_tank_F2=DECODE_GAS_F1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_F2&0x0c)>>2)==0x02)//第二个抽气气瓶为F2
		{
			TGTHT510_supply_decode_par.second_gas_tank_F2=DECODE_GAS_F2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_F2&0x0c)>>2)==0x03)//第二个抽气气瓶为F3
		{
			TGTHT510_supply_decode_par.second_gas_tank_F2=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
		
	//燃贮箱F3的气瓶抽气顺序（1字节）
	
	if((TGTHT510_supply_input_par.sequence_gas_F3>>6)==0)//燃贮箱F3的气瓶抽气数量为0
	{
		TGTHT510_supply_decode_par.number_gas_tank_F3=0;
		TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_NONE;
		TGTHT510_supply_decode_par.second_gas_tank_F3=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_F3>>6)==1)//燃贮箱F3的气瓶抽气数量为1
	{
		TGTHT510_supply_decode_par.number_gas_tank_F3=1;
		TGTHT510_supply_decode_par.second_gas_tank_F3=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_gas_F3&0x03)==0x01)//第一个抽气气瓶为F1
		{
			TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_GAS_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F3&0x03)==0x02)//第一个抽气气瓶为F2
		{
			TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_GAS_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F3&0x03)==0x03)//第一个抽气气瓶为F3
		{
			TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_F3>>6)==2)//燃贮箱F3的气瓶抽气数量为2
	{
		TGTHT510_supply_decode_par.number_gas_tank_F3=2;
		
		if((TGTHT510_supply_input_par.sequence_gas_F3&0x03)==0x01)//第一个抽气气瓶为F1
		{
			TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_GAS_F1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F3&0x03)==0x02)//第一个抽气气瓶为F2
		{
			TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_GAS_F2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_F3&0x03)==0x03)//第一个抽气气瓶为F3
		{
			TGTHT510_supply_decode_par.first_gas_tank_F3=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_gas_F3&0x0c)>>2)==0x01)//第二个抽气气瓶为F1
		{
			TGTHT510_supply_decode_par.second_gas_tank_F3=DECODE_GAS_F1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_F3&0x0c)>>2)==0x02)//第二个抽气气瓶为F2
		{
			TGTHT510_supply_decode_par.second_gas_tank_F3=DECODE_GAS_F2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_F3&0x0c)>>2)==0x03)//第二个抽气气瓶为F3
		{
			TGTHT510_supply_decode_par.second_gas_tank_F3=DECODE_GAS_F3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//氧贮箱O1的气瓶抽气顺序（1字节）
	
	if((TGTHT510_supply_input_par.sequence_gas_O1>>6)==0)//氧贮箱O1的气瓶抽气数量为0
	{
		TGTHT510_supply_decode_par.number_gas_tank_O1=0;
		TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_NONE;
		TGTHT510_supply_decode_par.second_gas_tank_O1=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_O1>>6)==1)//氧贮箱O1的气瓶抽气数量为1
	{
		TGTHT510_supply_decode_par.number_gas_tank_O1=1;
		TGTHT510_supply_decode_par.second_gas_tank_O1=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_gas_O1&0x03)==0x01)//第一个抽气气瓶为O1
		{
			TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_GAS_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O1&0x03)==0x02)//第一个抽气气瓶为O2
		{
			TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_GAS_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O1&0x03)==0x03)//第一个抽气气瓶为O3
		{
			TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_O1>>6)==2)//氧贮箱O1的气瓶抽气数量为2
	{
		TGTHT510_supply_decode_par.number_gas_tank_O1=2;
		
		if((TGTHT510_supply_input_par.sequence_gas_O1&0x03)==0x01)//第一个抽气气瓶为O1
		{
			TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_GAS_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O1&0x03)==0x02)//第一个抽气气瓶为O2
		{
			TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_GAS_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O1&0x03)==0x03)//第一个抽气气瓶为O3
		{
			TGTHT510_supply_decode_par.first_gas_tank_O1=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_gas_O1&0x0c)>>2)==0x01)//第二个抽气气瓶为O1
		{
			TGTHT510_supply_decode_par.second_gas_tank_O1=DECODE_GAS_O1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_O1&0x0c)>>2)==0x02)//第二个抽气气瓶为O2
		{
			TGTHT510_supply_decode_par.second_gas_tank_O1=DECODE_GAS_O2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_O1&0x0c)>>2)==0x03)//第二个抽气气瓶为O3
		{
			TGTHT510_supply_decode_par.second_gas_tank_O1=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//氧贮箱O2的气瓶抽气顺序（1字节）
	
	if((TGTHT510_supply_input_par.sequence_gas_O2>>6)==0)//氧贮箱O2的气瓶抽气数量为0
	{
		TGTHT510_supply_decode_par.number_gas_tank_O2=0;
		TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_NONE;
		TGTHT510_supply_decode_par.second_gas_tank_O2=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_O2>>6)==1)//氧贮箱O2的气瓶抽气数量为1
	{
		TGTHT510_supply_decode_par.number_gas_tank_O2=1;
		TGTHT510_supply_decode_par.second_gas_tank_O2=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_gas_O2&0x03)==0x01)//第一个抽气气瓶为O1
		{
			TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_GAS_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O2&0x03)==0x02)//第一个抽气气瓶为O2
		{
			TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_GAS_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O2&0x03)==0x03)//第一个抽气气瓶为O3
		{
			TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_O2>>6)==2)//氧贮箱O2的气瓶抽气数量为2
	{
		TGTHT510_supply_decode_par.number_gas_tank_O2=2;
		
		if((TGTHT510_supply_input_par.sequence_gas_O2&0x03)==0x01)//第一个抽气气瓶为O1
		{
			TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_GAS_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O2&0x03)==0x02)//第一个抽气气瓶为O2
		{
			TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_GAS_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O2&0x03)==0x03)//第一个抽气气瓶为O3
		{
			TGTHT510_supply_decode_par.first_gas_tank_O2=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_gas_O2&0x0c)>>2)==0x01)//第二个抽气气瓶为O1
		{
			TGTHT510_supply_decode_par.second_gas_tank_O2=DECODE_GAS_O1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_O2&0x0c)>>2)==0x02)//第二个抽气气瓶为O2
		{
			TGTHT510_supply_decode_par.second_gas_tank_O2=DECODE_GAS_O2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_O2&0x0c)>>2)==0x03)//第二个抽气气瓶为O3
		{
			TGTHT510_supply_decode_par.second_gas_tank_O2=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
		
	//氧贮箱O3的气瓶抽气顺序（1字节）
	
	if((TGTHT510_supply_input_par.sequence_gas_O3>>6)==0)//氧贮箱O3的气瓶抽气数量为0
	{
		TGTHT510_supply_decode_par.number_gas_tank_O3=0;
		TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_NONE;
		TGTHT510_supply_decode_par.second_gas_tank_O3=DECODE_NONE;
	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_O3>>6)==1)//氧贮箱O3的气瓶抽气数量为1
	{
		TGTHT510_supply_decode_par.number_gas_tank_O3=1;
		TGTHT510_supply_decode_par.second_gas_tank_O3=DECODE_NONE;
		
		if((TGTHT510_supply_input_par.sequence_gas_O3&0x03)==0x01)//第一个抽气气瓶为O1
		{
			TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_GAS_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O3&0x03)==0x02)//第一个抽气气瓶为O2
		{
			TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_GAS_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O3&0x03)==0x03)//第一个抽气气瓶为O3
		{
			TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else if((TGTHT510_supply_input_par.sequence_gas_O3>>6)==2)//氧贮箱O3的气瓶抽气数量为2
	{
		TGTHT510_supply_decode_par.number_gas_tank_O3=2;
		
		if((TGTHT510_supply_input_par.sequence_gas_O3&0x03)==0x01)//第一个抽气气瓶为O1
		{
			TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_GAS_O1;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O3&0x03)==0x02)//第一个抽气气瓶为O2
		{
			TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_GAS_O2;
		}
		
		else if((TGTHT510_supply_input_par.sequence_gas_O3&0x03)==0x03)//第一个抽气气瓶为O3
		{
			TGTHT510_supply_decode_par.first_gas_tank_O3=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
		
		if(((TGTHT510_supply_input_par.sequence_gas_O3&0x0c)>>2)==0x01)//第二个抽气气瓶为O1
		{
			TGTHT510_supply_decode_par.second_gas_tank_O3=DECODE_GAS_O1;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_O3&0x0c)>>2)==0x02)//第二个抽气气瓶为O2
		{
			TGTHT510_supply_decode_par.second_gas_tank_O3=DECODE_GAS_O2;
		}
		
		else if(((TGTHT510_supply_input_par.sequence_gas_O3&0x0c)>>2)==0x03)//第二个抽气气瓶为O3
		{
			TGTHT510_supply_decode_par.second_gas_tank_O3=DECODE_GAS_O3;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}

	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//燃氧抽气压气机号与出口阀门（2字节）
	
	/*
11、燃氧抽气压气机号与出口阀门（2字节）
bit0、1为01表示燃抽气压气机为B机，为10表示燃抽气压气机为C机
bit2、3为01表示开启的燃压气机出口阀门为主，10表示开启的燃压气机出口阀门为备
bit4、5为01表示氧抽气压气机为A机，为10表示氧抽气压气机为C机
bit6、7为01表示开启的氧压气机出口阀门为主，10表示开启的氧压气机出口阀门为备
bit8-15为空
	
	*/
	
	//燃压气机号
	if((TGTHT510_supply_input_par.compressor_out_valve&0x0003)==0x0001)
	{
		TGTHT510_supply_decode_par.compressor_F=DECODE_COMPRESSOR_B;
	}
	
	else if((TGTHT510_supply_input_par.compressor_out_valve&0x0003)==0x0002)
	{
		TGTHT510_supply_decode_par.compressor_F=DECODE_COMPRESSOR_C;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	//开启的燃压气机出口阀门
	if(((TGTHT510_supply_input_par.compressor_out_valve&0x000c)>>2)==0x0001)
	{
		TGTHT510_supply_decode_par.valve_out_compressor_F=DECODE_COMP_VALVE_Z;
	}
	
	else if(((TGTHT510_supply_input_par.compressor_out_valve&0x000c)>>2)==0x0002)
	{
		TGTHT510_supply_decode_par.valve_out_compressor_F=DECODE_COMP_VALVE_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	//氧压气机号
	if(((TGTHT510_supply_input_par.compressor_out_valve&0x0030)>>4)==0x0001)
	{
		TGTHT510_supply_decode_par.compressor_O=DECODE_COMPRESSOR_A;
	}
	
	else if(((TGTHT510_supply_input_par.compressor_out_valve&0x0030)>>4)==0x0002)
	{
		TGTHT510_supply_decode_par.compressor_O=DECODE_COMPRESSOR_C;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	//开启的氧压气机出口阀门
	if(((TGTHT510_supply_input_par.compressor_out_valve&0x00c0)>>6)==0x0001)
	{
		TGTHT510_supply_decode_par.valve_out_compressor_O=DECODE_COMP_VALVE_Z;
	}
	
	else if(((TGTHT510_supply_input_par.compressor_out_valve&0x00c0)>>6)==0x0002)
	{
		TGTHT510_supply_decode_par.valve_out_compressor_O=DECODE_COMP_VALVE_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	/*
24、液冷模块泵号（2字节）
高字节无效，
低字节为0x03是主液冷I泵
低字节为0x0c是主液冷II泵
低字节为0x30是备液冷I泵
低字节为0xc0是备液冷II泵
	
	*/
	
	//液冷模块泵号（2字节）
	if((TGTHT510_supply_input_par.pump_cooler&0x00ff)==0x0003)
	{
		TGTHT510_supply_decode_par.cooler=DECODE_COOLER_Z_1;
	}
	
	else if((TGTHT510_supply_input_par.pump_cooler&0x00ff)==0x000c)
	{
		TGTHT510_supply_decode_par.cooler=DECODE_COOLER_Z_2;
	}
	
	else if((TGTHT510_supply_input_par.pump_cooler&0x00ff)==0x0030)
	{
		TGTHT510_supply_decode_par.cooler=DECODE_COOLER_B_1;
	}
	
	else if((TGTHT510_supply_input_par.pump_cooler&0x00ff)==0x00c0)
	{
		TGTHT510_supply_decode_par.cooler=DECODE_COOLER_B_2;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	/*
1、燃贮箱压力传感器设定（2字节）
高字节无效，
低字节bit0、1为01表示燃贮箱F1使用主份传感器PTt14，为10表示燃贮箱F1使用备份传感器PTt20
低字节bit2、3为01表示燃贮箱F2使用主份传感器PTt16，为10表示燃贮箱F2使用备份传感器PTt22
低字节bit4、5为01表示燃贮箱F3使用主份传感器PTt18，为10表示燃贮箱F3使用备份传感器PTt24
	*/
	
	//燃贮箱压力传感器设定（2字节）
	if(((TGTHT510_supply_input_par.sensor_tank_F&0x0003)>>0)==0x0001)
	{
		TGTHT510_supply_decode_par.sensor_tank_F1=DECODE_SENSOR_TANK_Z;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_tank_F&0x0003)>>0)==0x0002)
	{
		TGTHT510_supply_decode_par.sensor_tank_F1=DECODE_SENSOR_TANK_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	if(((TGTHT510_supply_input_par.sensor_tank_F&0x000c)>>2)==0x0001)
	{
		TGTHT510_supply_decode_par.sensor_tank_F2=DECODE_SENSOR_TANK_Z;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_tank_F&0x000c)>>2)==0x0002)
	{
		TGTHT510_supply_decode_par.sensor_tank_F2=DECODE_SENSOR_TANK_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	if(((TGTHT510_supply_input_par.sensor_tank_F&0x0030)>>4)==0x0001)
	{
		TGTHT510_supply_decode_par.sensor_tank_F3=DECODE_SENSOR_TANK_Z;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_tank_F&0x0030)>>4)==0x0002)
	{
		TGTHT510_supply_decode_par.sensor_tank_F3=DECODE_SENSOR_TANK_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	//氧贮箱压力传感器设定（2字节）
	if(((TGTHT510_supply_input_par.sensor_tank_O&0x0003)>>0)==0x0001)
	{
		TGTHT510_supply_decode_par.sensor_tank_O1=DECODE_SENSOR_TANK_Z;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_tank_O&0x0003)>>0)==0x0002)
	{
		TGTHT510_supply_decode_par.sensor_tank_O1=DECODE_SENSOR_TANK_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	if(((TGTHT510_supply_input_par.sensor_tank_O&0x000c)>>2)==0x0001)
	{
		TGTHT510_supply_decode_par.sensor_tank_O2=DECODE_SENSOR_TANK_Z;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_tank_O&0x000c)>>2)==0x0002)
	{
		TGTHT510_supply_decode_par.sensor_tank_O2=DECODE_SENSOR_TANK_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	if(((TGTHT510_supply_input_par.sensor_tank_O&0x0030)>>4)==0x0001)
	{
		TGTHT510_supply_decode_par.sensor_tank_O3=DECODE_SENSOR_TANK_Z;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_tank_O&0x0030)>>4)==0x0002)
	{
		TGTHT510_supply_decode_par.sensor_tank_O3=DECODE_SENSOR_TANK_B;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
	/*
3、低压气路传感器设定（2字节）
高字节为0x00是燃路使用传感器PTb2
高字节为0x03是燃路使用传感器PTb4
高字节为0x0c是燃路使用传感器PTb24

低字节为0x00是氧路使用传感器PTb1
低字节为0x03是氧路使用传感器PTb3
低字节为0x0c是氧路使用传感器PTb24
	*/
	
	//低压气路传感器设定（2字节）
	
	if(((TGTHT510_supply_input_par.sensor_pipe_low&0xff00)>>8)==0x0000)
	{
		TGTHT510_supply_decode_par.sensor_pipe_low_F=DECODE_SENSOR_PIPE_LOW_PTB02;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_pipe_low&0xff00)>>8)==0x0003)
	{
		TGTHT510_supply_decode_par.sensor_pipe_low_F=DECODE_SENSOR_PIPE_LOW_PTB04;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_pipe_low&0xff00)>>8)==0x000c)
	{
		TGTHT510_supply_decode_par.sensor_pipe_low_F=DECODE_SENSOR_PIPE_LOW_PTB24;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	if(((TGTHT510_supply_input_par.sensor_pipe_low&0x00ff)>>0)==0x0000)
	{
		TGTHT510_supply_decode_par.sensor_pipe_low_O=DECODE_SENSOR_PIPE_LOW_PTB01;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_pipe_low&0x00ff)>>0)==0x0003)
	{
		TGTHT510_supply_decode_par.sensor_pipe_low_O=DECODE_SENSOR_PIPE_LOW_PTB03;
	}
	
	else if(((TGTHT510_supply_input_par.sensor_pipe_low&0x00ff)>>0)==0x000c)
	{
		TGTHT510_supply_decode_par.sensor_pipe_low_O=DECODE_SENSOR_PIPE_LOW_PTB24;
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	
/*	
	4、压气机进口压力传感器设定（2字节）
高字节无效，
低字节bit0、1为01表示氧压气机A进口压力传感器PTb03，为10表示氧压气机A进口压力传感器PTb29
低字节bit2、3为01表示燃压气机B进口压力传感器PTb04，为10表示氧压气机B进口压力传感器PTb28
高字节bit4、5、6、7为0001表示备份压气机C进口压力传感器为PTb24，
为1000表示备份压气机C进口压力传感器为PTb24。
	
*/

	//压气机进口压力传感器设定（2字节）
	
	if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_B)
	{
		if(((TGTHT510_supply_input_par.sensor_comp_in&0x000c)>>2)==0x0001)//PTb04
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_F=DECODE_SENSOR_PIPE_LOW_PTB04;
		}
		
		else if(((TGTHT510_supply_input_par.sensor_comp_in&0x000c)>>2)==0x0002)//PTb28
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_F=DECODE_SENSOR_PIPE_LOW_PTB28;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
	
	}
	
	else if(TGTHT510_supply_decode_par.compressor_F==DECODE_COMPRESSOR_C)
	{
		if(((TGTHT510_supply_input_par.sensor_comp_in&0x00f0)>>4)==0x0001)//PTb24
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_F=DECODE_SENSOR_PIPE_LOW_PTB24;
		}
		
		else if(((TGTHT510_supply_input_par.sensor_comp_in&0x00f0)>>4)==0x0008)//PTb24
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_F=DECODE_SENSOR_PIPE_LOW_PTB24;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_A)
	{
		if(((TGTHT510_supply_input_par.sensor_comp_in&0x0003)>>0)==0x0001)//PTb03
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_O=DECODE_SENSOR_PIPE_LOW_PTB03;
		}
		
		else if(((TGTHT510_supply_input_par.sensor_comp_in&0x0003)>>0)==0x0002)//PTb29
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_O=DECODE_SENSOR_PIPE_LOW_PTB29;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
	}
	
	else if(TGTHT510_supply_decode_par.compressor_O==DECODE_COMPRESSOR_C)
	{
		if(((TGTHT510_supply_input_par.sensor_comp_in&0x00f0)>>4)==0x0001)//PTb24
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_O=DECODE_SENSOR_PIPE_LOW_PTB24;
		}
		
		else if(((TGTHT510_supply_input_par.sensor_comp_in&0x00f0)>>4)==0x0008)//PTb24
		{
			TGTHT510_supply_decode_par.sensor_in_compressor_O=DECODE_SENSOR_PIPE_LOW_PTB24;
		}
		
		else
		{
			return_state=FALSE;
		
			return return_state;
		}
	}
	
	else
	{
		return_state=FALSE;
		
		return return_state;
	}
	
	return return_state;
}



