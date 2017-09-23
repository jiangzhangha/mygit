/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ���������������������ͷ�ļ�
  ******************************************************************************
  */
 
#ifndef __supply_stage_20_blow_o_h
#define __supply_stage_20_blow_o_h
 

/*�����ṹ������--------------------------------------------------------------*/



/*�궨��---------------------------------------------------------------------------*/

//����step----------------------------------------------------------------------

#define 	STEP_20_SUPPLY_BLOW_VALVE_ON			0x0001//ȼ·��������
#define 	STEP_20_SUPPLY_IS_HYCT_TIME				0x0002//�ȴ�������Ϣ���߳�ʱ
#define 	STEP_20_SUPPLY_BLOW_VALVE_OFF			0x0003//ȼ·�������ر�


//����command-------------------------------------------------------------------

//ȼ·��������
#define		COMMAND_20_0001_VALVE_ON_NO1			0x0001//ȼ·�������򿪣���һ��
#define		COMMAND_20_0002_IS_VALVE_ON_NO1			0x0002//�ж�ȼ·�������򿪣���һ��
#define		COMMAND_20_0003_VALVE_ON_NO2			0x0003//ȼ·�������򿪣��ڶ���
#define		COMMAND_20_0004_IS_VALVE_ON_NO2			0x0004//�ж�ȼ·�������򿪣��ڶ���
#define		COMMAND_20_0005_VALVE_ON_NO3			0x0005//ȼ·�������򿪣�������
#define		COMMAND_20_0006_IS_VALVE_ON_NO3			0x0006//�ж�ȼ·�������򿪣�������
#define		COMMAND_20_0007_VALVE_ON_NO4			0x0007//ȼ·�������򿪣�������
#define		COMMAND_20_0008_IS_VALVE_ON_NO4			0x0008//�ж�ȼ·�������򿪣�������
#define		COMMAND_20_0009_VALVE_ON_NO5			0x0009//ȼ·�������򿪣�������
#define		COMMAND_20_0010_IS_VALVE_ON_NO5			0x000a//�ж�ȼ·�������򿪣�������

//�ȴ�������Ϣ���߳�ʱ
#define		COMMAND_20_0001_IS_HYCT_TIME			0x000b

//ȼ·�������ر�
#define		COMMAND_20_0001_VALVE_OFF_NO1			0x000c//ȼ·�������رգ���һ��
#define		COMMAND_20_0002_IS_VALVE_OFF_NO1		0x000d//�ж�ȼ·�������رգ���һ��
#define		COMMAND_20_0003_VALVE_OFF_NO2			0x000e//ȼ·�������رգ��ڶ���
#define		COMMAND_20_0004_IS_VALVE_OFF_NO2		0x000f//�ж�ȼ·�������رգ��ڶ���
#define		COMMAND_20_0005_VALVE_OFF_NO3			0x0010//ȼ·�������رգ�������
#define		COMMAND_20_0006_IS_VALVE_OFF_NO3		0x0011//�ж�ȼ·�������رգ�������
#define		COMMAND_20_0007_VALVE_OFF_NO4			0x0012//ȼ·�������رգ�������
#define		COMMAND_20_0008_IS_VALVE_OFF_NO4		0x0013//�ж�ȼ·�������رգ�������
#define		COMMAND_20_0009_VALVE_OFF_NO5			0x0014//ȼ·�������رգ�������
#define		COMMAND_20_0010_IS_VALVE_OFF_NO5		0x0015//�ж�ȼ·�������رգ�������
#define		COMMAND_20_0011_VALVE_OFF_NO6			0x0016//ȼ·�������رգ�������
#define		COMMAND_20_0012_IS_VALVE_OFF_NO6		0x0017//�ж�ȼ·�������رգ�������

//-------------------------��������------------------------------------------------

void TGTHT510_supply_stage20_blow_o_main(void);
uint16 TGTHT510_supply_stage20_blow_o_step_valve_on(void);
uint16 TGTHT510_supply_stage20_blow_o_step_is_hyct_time(void);
uint16 TGTHT510_supply_stage20_blow_o_step_valve_off(void);


#endif
 
 
 
 
 
 
 
 
 
