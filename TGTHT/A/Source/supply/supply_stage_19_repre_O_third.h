/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ���������������������ͷ�ļ�
  ******************************************************************************
  */
 
#ifndef __supply_stage_19_repre_third_o_h
#define __supply_stage_19_repre_third_o_h
 

/*�����ṹ������--------------------------------------------------------------*/

/*�궨��---------------------------------------------------------------------------*/

//����step------------------------------------------------------------------------

#define 	STEP_19_O_REPRE_1TANK_LVT_VALVE_ON				0x0001//������ѹ���򿪸�ѹ������
#define 	STEP_19_O_REPRE_1TANK_IS_REPRE_OVER				0x0002//ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ����
#define 	STEP_19_O_REPRE_1TANK_LVT_VALVE_OFF				0x0003//��ѹ�������رո�ѹ������
#define 	STEP_19_O_REPRE_1TANK_OUT_TANK_VALVE_ON			0x0004//��������ڷ���
#define 	STEP_19_O_REPRE_1TANK_DELAY						0x0005//��ʱ�ȴ�
#define 	STEP_19_O_REPRE_1TANK_IS_TANK_PRESSURE			0x0006//�ж�����ѹ�����ȶ���

//����command---------------------------------------------------------------------

//������ѹ���򿪸�ѹ������
#define		COMMAND_19_0001_O_REPRE_1TANK_LVT_VALVE_ON				0x0002
#define		COMMAND_19_0002_O_REPRE_1TANK_1MIN_START_NO1			0x0003
#define		COMMAND_19_0003_O_REPRE_1TANK_IS_1MIN_NO1				0x0004
#define		COMMAND_19_0004_O_REPRE_1TANK_IS_LVT_VALVE_ON			0x0005

//ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ����
#define		COMMAND_19_0001_O_REPRE_1TANK_IS_REPRE_OVER				0x0006

//��ѹ�������رո�ѹ������
#define		COMMAND_19_0001_O_REPRE_1TANK_LVT_VALVE_OFF				0x0007
#define		COMMAND_19_0002_O_REPRE_1TANK_1MIN_START_NO2			0x0008
#define		COMMAND_19_0003_O_REPRE_1TANK_IS_1MIN_NO2				0x0009
#define		COMMAND_19_0004_O_REPRE_1TANK_IS_LVT_VALVE_OFF			0x000a

//��������ڷ���
#define		COMMAND_19_0001_O_REPRE_1TANK_OUT_TANK_VALVE_ON_NO1		0x000b
#define		COMMAND_19_0002_O_REPRE_1TANK_1MIN_START_NO3			0x000c
#define		COMMAND_19_0003_O_REPRE_1TANK_IS_1MIN_NO3				0x000d
#define		COMMAND_19_0004_O_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO1	0x000e
#define		COMMAND_19_0005_O_REPRE_1TANK_OUT_TANK_VALVE_ON_NO2		0x000f
#define		COMMAND_19_0006_O_REPRE_1TANK_1MIN_START_NO4			0x0010
#define		COMMAND_19_0007_O_REPRE_1TANK_IS_1MIN_NO4				0x0011
#define		COMMAND_19_0008_O_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO2	0x0012


//��ʱ�ȴ�
#define		COMMAND_19_0001_O_REPRE_1TANK_DELAY_START_NO1			0x0013
#define		COMMAND_19_0002_O_REPRE_1TANK_IS_DELAY_NO1				0x0014

//�ж�����ѹ�����ȶ���
#define		COMMAND_19_0001_O_REPRE_1TANK_TANK_PRESSURE_NO1			0x0015
#define		COMMAND_19_0002_O_REPRE_1TANK_5SEC_START_NO1			0x0016
#define		COMMAND_19_0003_O_REPRE_1TANK_IS_5SEC_NO1				0x0017
#define		COMMAND_19_0004_O_REPRE_1TANK_TANK_PRESSURE_NO2			0x0018
#define		COMMAND_19_0005_O_REPRE_1TANK_5SEC_START_NO2			0x0019
#define		COMMAND_19_0006_O_REPRE_1TANK_IS_5SEC_NO2				0x001a
#define		COMMAND_19_0007_O_REPRE_1TANK_TANK_PRESSURE_NO3			0x001b
#define		COMMAND_19_0008_O_REPRE_1TANK_5SEC_START_NO3			0x001c
#define		COMMAND_19_0009_O_REPRE_1TANK_IS_5SEC_NO3				0x001d
#define		COMMAND_19_0010_O_REPRE_1TANK_TANK_PRESSURE_NO4			0x001e
#define		COMMAND_19_0011_O_REPRE_1TANK_5SEC_START_NO4			0x001f
#define		COMMAND_19_0012_O_REPRE_1TANK_IS_5SEC_NO4				0x0020
#define		COMMAND_19_0013_O_REPRE_1TANK_TANK_PRESSURE_NO5			0x0021
#define		COMMAND_19_0014_O_REPRE_1TANK_5SEC_START_NO5			0x0022
#define		COMMAND_19_0015_O_REPRE_1TANK_IS_5SEC_NO5				0x0023
#define		COMMAND_19_0016_O_REPRE_1TANK_TANK_PRESSURE_NO6			0x0024
#define		COMMAND_19_0017_O_REPRE_1TANK_5SEC_START_NO6			0x0025
#define		COMMAND_19_0018_O_REPRE_1TANK_IS_5SEC_NO6				0x0026
#define		COMMAND_19_0019_O_REPRE_1TANK_TANK_PRESSURE_NO7			0x0027
#define		COMMAND_19_0020_O_REPRE_1TANK_IS_PRESSURE_STABLE		0x0028


//---------------��������--------------------------------------------------------------


void TGTHT510_supply_stage19_repre_o_main(void);
void TGTHT510_supply_stage19_repre_o_step_tank_number(void);
uint16 TGTHT510_supply_stage19_repre_o_step_1tank_lvt_valve_on(void);
uint16 TGTHT510_supply_stage19_repre_o_step_1tank_is_repre_over(void);
uint16 TGTHT510_supply_stage19_repre_o_step_1tank_lvt_valve_off(void);
uint16 TGTHT510_supply_stage19_repre_o_step_1tank_out_tank_valve_on(void);
uint16 TGTHT510_supply_stage19_repre_o_step_1tank_delay(void);
uint16 TGTHT510_supply_stage19_repre_o_step_1tank_is_tank_pressure_stable(void);



#endif
 
 
 
 
 
 
