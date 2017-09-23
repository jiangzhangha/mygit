/**
  ******************************************************************************
  * @file    TGTHT510.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ����������ͷ�ļ�
  ******************************************************************************
  */
 
#ifndef __TGTHT510_h
#define __TGTHT510_h
 

 
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

 
typedef struct
{
	uint16 time_9s_count;
	uint16 time_9s_flag;
	
}Time_flag_TypeDef;//��ʱ�����ṹ��

/*�ṹ������----------------------------------------------------------------------*/

typedef struct
{
	uint8  frame_number;		//���յ�A�����͵�֡����
	uint8  last_frame_number;	//��һ֡A�����͵�֡����
	uint16 fault_mode;			//A�����͵Ĺ���״̬
	
	uint16 count;				//�ж��Ƿ�ʱ����
	uint16 is_B_get_power;		//B���Ƿ��Ȩ��TRUE����FALSE
	uint16 error_number;		//���յ�A���Ĵ���֡����
	
}CPU_B_receive_data_TypeDef;



#define CPU_ON()		regs->piodata=regs->piodata&0xffef,regs->piodata=regs->piodata|0x0020
#define CPU_OFF()		regs->piodata=regs->piodata&0xffdf,regs->piodata=regs->piodata|0x0010

#define LED_ON()	 	regs->piodata=regs->piodata|0x1000
#define LED_OFF()	 	regs->piodata=regs->piodata&0xefff
 
#define TRUE 		0xAA55				//������
#define FALSE 		0x55AA				//�����
#define ENABLE 		0xAA55				//����ʹ��
#define DISABLE 	0x55AA				//�����ֹ
 
 //�������̲��迪ʼ�����
#define		STEP_START			0xfffd//���迪ʼ
#define		STEP_END			0xfffe//�������
#define		STEP_NONE			0xffff//������
 
 //�����������ʼ�����
#define		COMMAND_START			0xfffd//���ʼ
#define		COMMAND_END				0xfffe//�������
#define		COMMAND_NONE			0xffff//������


//����CPU��A������B��
#define 	CPU_A				0x0f0f
#define 	CPU_B				0xf0f0

//#define		TEST_VERSION		1	//���Լ�Ϊ1�����Լ�Ϊ0


/*
 * the configuration of uart control register
 */
#define   REV_EN         0x1
#define   TRANS_EN       0x2
#define   REV_INT_EN     0x4
#define   TRANS_INT_EN   0x8
#define   PAR_SEL        0x10
#define   PAR_EN         0x20
#define   FLOW_CTR       0x40
#define   LOOP_BCK       0x80

/*
 * the configuration of uart status register
 */

#define   DATA_RD       0x1
#define   TS_EMPTY      0x2
#define   TH_EMPTY      0x4
#define   BREAK_REV     0x8
#define   OVERRUN       0x10
#define   PAR_ER        0x20
#define   FRAME_ER      0x40

#include "TGTHT510_1553b.h"
#include "TGTHT510_collectANDgroup.h"
#include "TGTHT510_faultdiagnosis.h"
#include "TGTHT510_initial.h"
#include "TGTHT510_tempercontrol.h"
#include "TGTHT510_valvecontrol.h"
 
//���ӳ���ͷ�ļ�

 #include "supply_main.h"
 #include "supply_pause_and_break.h"
 #include "supply_stage_01_input.h"
 #include "supply_stage_02_set.h"
 #include "supply_stage_03_connect.h"
 #include "supply_stage_04_leak.h"
 #include "supply_stage_05_comp_F.h"
 #include "supply_stage_06_pre_F.h"
 #include "supply_stage_07_flow_F.h"
 #include "supply_stage_08_repre_F.h"
 #include "supply_stage_09_comp_F_third.h"
 #include "supply_stage_10_flow_F_third.h"
 #include "supply_stage_11_repre_F_third.h"
 #include "supply_stage_12_blow_F.h"
 #include "supply_stage_13_comp_O.h"
 #include "supply_stage_14_pre_O.h"
 #include "supply_stage_15_flow_O.h"
 #include "supply_stage_16_repre_O.h"
 #include "supply_stage_17_comp_O_third.h"
 #include "supply_stage_18_flow_O_third.h"
 #include "supply_stage_19_repre_O_third.h"
 #include "supply_stage_20_blow_O.h"
 #include "supply_stage_21_disconnect.h"
 #include "supply_stage_22_resume.h"

 #include "math.h"

 
 #endif
 
 
 
 
