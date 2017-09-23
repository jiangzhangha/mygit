/**
  ******************************************************************************
  * @file    TGTHT510_test.c
  * @author  蒋章
  * @version V1.00
  * @date    20150626
  * @brief   空间站核心舱推进管理器测试代码
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"

extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_A[];				//全局数组，缓存推进遥测线路盒复帧A温度数据，65字
extern uint16 TGTHT510_1553B_data_TGTHT100_Temper_B[];				//全局数组，缓存推进遥测线路盒复帧B温度数据，65字




/******************************************************************************************
**名称：初始化温度控制测试代码
**作者：蒋章
**日期：20150728
**版本：1.00
**描述：
-------------------------------------------------------------------------------------------
**修改时间：
**版本：
**修改内容：
******************************************************************************************/

void TGTHT510_test_TGTHT100_Temper(void)
{
	uint16 i;
	
	
//----------------------------复帧A，铂电阻--------------------------------	
	
	for(i=0;i<=25;i++)
	{
		TGTHT510_1553B_data_TGTHT100_Temper_A[i]=TEMPER_PT_POS_20;//温度20摄氏度
	}
	
//----------------------------复帧A，MF61电阻--------------------------------	
	
	for(i=26;i<=64;i++)
	{
		TGTHT510_1553B_data_TGTHT100_Temper_A[i]=(TEMPER_MF61_POS_20<<8)|(TEMPER_MF61_POS_20);//温度20摄氏度
	}

//----------------------------复帧B，MF61电阻--------------------------------	
	
	for(i=0;i<=57;i++)
	{
		TGTHT510_1553B_data_TGTHT100_Temper_B[i]=(TEMPER_MF61_POS_20<<8)|(TEMPER_MF61_POS_20);//温度20摄氏度
	}
	
//----------------------------复帧B，MF51电阻--------------------------------	
	
	for(i=58;i<=64;i++)
	{
		TGTHT510_1553B_data_TGTHT100_Temper_B[i]=(TEMPER_MF51_POS_20<<8)|(TEMPER_MF51_POS_20);//温度20摄氏度
	}

//----------------------------测试，设定温度--------------------------------

	for(i=0;i<=3;i++)
	{
		TGTHT510_1553B_data_TGTHT100_Temper_A[i]=TEMPER_PT_POS_06;//设定加热回路0-3测温点6摄氏度
	}
	

}


















