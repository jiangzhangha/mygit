/**
  ******************************************************************************
  * @file    TGTHT510_initial.c
  * @author  ����
  * @version V1.00
  * @date    20150626
  * @brief   �ռ�վ���Ĳ��ƽ���������ʼ��ģ��C�ļ�
  ******************************************************************************
  */

/*Includes---------------------------------------------------------------------*/
#include "TGTHT510.h"



/******************************************************************************************
**���ƣ���ʼ������������
**���ߣ�����
**���ڣ�20150728
**�汾��1.00
**������
-------------------------------------------------------------------------------------------
**�޸�ʱ�䣺
**�汾��
**�޸����ݣ�
******************************************************************************************/

void TGTHT510_initial_main(void)
{
	TGTHT510_time_initial();
	TGTHT510_CPU_B_receive_data_initial();
	TGTHT510_1553b_initial();
	TGTHT510_collectANDgroup_initial();
	TGTHT510_valvecontrol_initial();
    TGTHT510_tempercontrol_initial();
	TGTHT510_supply_main_initial();
	
	TGTHT510_faultdiagnosis_push_initial();
	TGTHT510_faultdiagnosis_supply_initial();

}

















