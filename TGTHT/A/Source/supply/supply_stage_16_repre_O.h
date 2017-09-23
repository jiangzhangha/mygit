/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ���������������������ͷ�ļ�
  ******************************************************************************
  */
 
#ifndef __supply_stage_16_repre_o_h
#define __supply_stage_16_repre_o_h
 

/*�����ṹ������--------------------------------------------------------------*/



/*�궨��---------------------------------------------------------------------------*/

//����step------------------------------------------------------------------------

#define 	STEP_16_O_REPRE_TANK_NUMBER						0x0001//�жϸ�ѹ����������

//---------------------һ��ȼ���临ѹ---------------------------------------------

#define 	STEP_16_O_REPRE_1TANK_LVT_VALVE_ON				0x0002//������ѹ���򿪸�ѹ������
#define 	STEP_16_O_REPRE_1TANK_IS_REPRE_OVER				0x0003//ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ����
#define 	STEP_16_O_REPRE_1TANK_LVT_VALVE_OFF				0x0004//��ѹ�������رո�ѹ������
#define 	STEP_16_O_REPRE_1TANK_OUT_TANK_VALVE_ON			0x0005//��������ڷ���
#define 	STEP_16_O_REPRE_1TANK_DELAY						0x0006//��ʱ�ȴ�
#define 	STEP_16_O_REPRE_1TANK_IS_TANK_PRESSURE			0x0007//�ж�����ѹ�����ȶ���

//---------------------����ȼ���临ѹ---------------------------------------------
#define 	STEP_16_O_REPRE_2TANK_TANK1_LVT_VALVE_ON		0x0008//������ѹ���򿪸�ѹ����������һ������
#define 	STEP_16_O_REPRE_2TANK_TANK1_IS_REPRE_OVER		0x0009//ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ��������һ������
#define 	STEP_16_O_REPRE_2TANK_TANK1_LVT_VALVE_OFF		0x000a//��ѹ�������رո�ѹ����������һ������
#define 	STEP_16_O_REPRE_2TANK_TANK1_OUT_TANK_VALVE_ON	0x000b//��������ڷ��ţ���һ������
#define 	STEP_16_O_REPRE_2TANK_TANK1_DELAY				0x000c//��ʱ�ȴ�����һ������
#define 	STEP_16_O_REPRE_2TANK_TANK1_IS_TANK_PRESSURE	0x000d//�ж�����ѹ�����ȶ��ԣ���һ������

#define 	STEP_16_O_REPRE_2TANK_TANK2_LVT_VALVE_ON		0x000e//������ѹ���򿪸�ѹ���������ڶ�������
#define 	STEP_16_O_REPRE_2TANK_TANK2_IS_REPRE_OVER		0x000f//ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ�������ڶ�������
#define 	STEP_16_O_REPRE_2TANK_TANK2_LVT_VALVE_OFF		0x0010//��ѹ�������رո�ѹ���������ڶ�������
#define 	STEP_16_O_REPRE_2TANK_TANK2_OUT_TANK_VALVE_ON	0x0011//��������ڷ��ţ��ڶ�������
#define 	STEP_16_O_REPRE_2TANK_TANK2_DELAY				0x0012//��ʱ�ȴ����ڶ�������
#define 	STEP_16_O_REPRE_2TANK_TANK2_IS_TANK_PRESSURE	0x0013//�ж�����ѹ�����ȶ��ԣ��ڶ�������


//����command---------------------------------------------------------------------

//�жϸ�ѹ����������
#define		COMMAND_16_0001_O_REPRE_TANK_NUMBER						0x0001

//---------------------һ��ȼ���临ѹ---------------------------------------------

//������ѹ���򿪸�ѹ������
#define		COMMAND_16_0001_O_REPRE_1TANK_LVT_VALVE_ON				0x0002
#define		COMMAND_16_0002_O_REPRE_1TANK_1MIN_START_NO1			0x0003
#define		COMMAND_16_0003_O_REPRE_1TANK_IS_1MIN_NO1				0x0004
#define		COMMAND_16_0004_O_REPRE_1TANK_IS_LVT_VALVE_ON			0x0005

//ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ����
#define		COMMAND_16_0001_O_REPRE_1TANK_IS_REPRE_OVER				0x0006

//��ѹ�������رո�ѹ������
#define		COMMAND_16_0001_O_REPRE_1TANK_LVT_VALVE_OFF				0x0007
#define		COMMAND_16_0002_O_REPRE_1TANK_1MIN_START_NO2			0x0008
#define		COMMAND_16_0003_O_REPRE_1TANK_IS_1MIN_NO2				0x0009
#define		COMMAND_16_0004_O_REPRE_1TANK_IS_LVT_VALVE_OFF			0x000a

//��������ڷ���
#define		COMMAND_16_0001_O_REPRE_1TANK_OUT_TANK_VALVE_ON_NO1		0x000b
#define		COMMAND_16_0002_O_REPRE_1TANK_1MIN_START_NO3			0x000c
#define		COMMAND_16_0003_O_REPRE_1TANK_IS_1MIN_NO3				0x000d
#define		COMMAND_16_0004_O_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO1	0x000e
#define		COMMAND_16_0005_O_REPRE_1TANK_OUT_TANK_VALVE_ON_NO2		0x000f
#define		COMMAND_16_0006_O_REPRE_1TANK_1MIN_START_NO4			0x0010
#define		COMMAND_16_0007_O_REPRE_1TANK_IS_1MIN_NO4				0x0011
#define		COMMAND_16_0008_O_REPRE_1TANK_IS_OUT_TANK_VALVE_ON_NO2	0x0012


//��ʱ�ȴ�
#define		COMMAND_16_0001_O_REPRE_1TANK_DELAY_START_NO1			0x0013
#define		COMMAND_16_0002_O_REPRE_1TANK_IS_DELAY_NO1				0x0014


//�ж�����ѹ�����ȶ���
#define		COMMAND_16_0001_O_REPRE_1TANK_TANK_PRESSURE_NO1			0x0015
#define		COMMAND_16_0002_O_REPRE_1TANK_5SEC_START_NO1			0x0016
#define		COMMAND_16_0003_O_REPRE_1TANK_IS_5SEC_NO1				0x0017
#define		COMMAND_16_0004_O_REPRE_1TANK_TANK_PRESSURE_NO2			0x0018
#define		COMMAND_16_0005_O_REPRE_1TANK_5SEC_START_NO2			0x0019
#define		COMMAND_16_0006_O_REPRE_1TANK_IS_5SEC_NO2				0x001a
#define		COMMAND_16_0007_O_REPRE_1TANK_TANK_PRESSURE_NO3			0x001b
#define		COMMAND_16_0008_O_REPRE_1TANK_5SEC_START_NO3			0x001c
#define		COMMAND_16_0009_O_REPRE_1TANK_IS_5SEC_NO3				0x001d
#define		COMMAND_16_0010_O_REPRE_1TANK_TANK_PRESSURE_NO4			0x001e
#define		COMMAND_16_0011_O_REPRE_1TANK_5SEC_START_NO4			0x001f
#define		COMMAND_16_0012_O_REPRE_1TANK_IS_5SEC_NO4				0x0020
#define		COMMAND_16_0013_O_REPRE_1TANK_TANK_PRESSURE_NO5			0x0021
#define		COMMAND_16_0014_O_REPRE_1TANK_5SEC_START_NO5			0x0022
#define		COMMAND_16_0015_O_REPRE_1TANK_IS_5SEC_NO5				0x0023
#define		COMMAND_16_0016_O_REPRE_1TANK_TANK_PRESSURE_NO6			0x0024
#define		COMMAND_16_0017_O_REPRE_1TANK_5SEC_START_NO6			0x0025
#define		COMMAND_16_0018_O_REPRE_1TANK_IS_5SEC_NO6				0x0026
#define		COMMAND_16_0019_O_REPRE_1TANK_TANK_PRESSURE_NO7			0x0027
#define		COMMAND_16_0020_O_REPRE_1TANK_IS_PRESSURE_STABLE		0x0028


//---------------------����ȼ���临ѹ---------------------------------------------

//������ѹ���򿪸�ѹ����������һ������
#define		COMMAND_16_0001_O_REPRE_2TANK_TANK1_LVT_VALVE_ON			0x0029
#define		COMMAND_16_0002_O_REPRE_2TANK_TANK1_1MIN_START_NO1			0x002a
#define		COMMAND_16_0003_O_REPRE_2TANK_TANK1_IS_1MIN_NO1				0x002b
#define		COMMAND_16_0004_O_REPRE_2TANK_TANK1_IS_LVT_VALVE_ON			0x002c

//ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ��������һ������
#define		COMMAND_16_0001_O_REPRE_2TANK_TANK1_IS_REPRE_OVER			0x002d

//��ѹ�������رո�ѹ����������һ������
#define		COMMAND_16_0001_O_REPRE_2TANK_TANK1_LVT_VALVE_OFF			0x002e
#define		COMMAND_16_0002_O_REPRE_2TANK_TANK1_1MIN_START_NO2			0x002f
#define		COMMAND_16_0003_O_REPRE_2TANK_TANK1_IS_1MIN_NO2				0x0030
#define		COMMAND_16_0004_O_REPRE_2TANK_TANK1_IS_LVT_VALVE_OFF		0x0031

//��������ڷ��ţ���һ������
#define		COMMAND_16_0001_O_REPRE_2TANK_TANK1_OUT_TANK_VALVE_ON_NO1		0x0032
#define		COMMAND_16_0002_O_REPRE_2TANK_TANK1_1MIN_START_NO3				0x0033
#define		COMMAND_16_0003_O_REPRE_2TANK_TANK1_IS_1MIN_NO3					0x0034
#define		COMMAND_16_0004_O_REPRE_2TANK_TANK1_IS_OUT_TANK_VALVE_ON_NO1	0x0035
#define		COMMAND_16_0005_O_REPRE_2TANK_TANK1_OUT_TANK_VALVE_ON_NO2		0x0036
#define		COMMAND_16_0006_O_REPRE_2TANK_TANK1_1MIN_START_NO4				0x0037
#define		COMMAND_16_0007_O_REPRE_2TANK_TANK1_IS_1MIN_NO4					0x0038
#define		COMMAND_16_0008_O_REPRE_2TANK_TANK1_IS_OUT_TANK_VALVE_ON_NO2	0x0039

//��ʱ�ȴ�����һ������
#define		COMMAND_16_0001_O_REPRE_2TANK_TANK1_DELAY_START_NO1			0x003a
#define		COMMAND_16_0002_O_REPRE_2TANK_TANK1_IS_DELAY_NO1			0x003b


//�ж�����ѹ�����ȶ��ԣ���һ������
#define		COMMAND_16_0001_O_REPRE_2TANK_TANK1_TANK_PRESSURE_NO1		0x003c
#define		COMMAND_16_0002_O_REPRE_2TANK_TANK1_5SEC_START_NO1			0x003d
#define		COMMAND_16_0003_O_REPRE_2TANK_TANK1_IS_5SEC_NO1				0x003e
#define		COMMAND_16_0004_O_REPRE_2TANK_TANK1_TANK_PRESSURE_NO2		0x003f
#define		COMMAND_16_0005_O_REPRE_2TANK_TANK1_5SEC_START_NO2			0x0040
#define		COMMAND_16_0006_O_REPRE_2TANK_TANK1_IS_5SEC_NO2				0x0041
#define		COMMAND_16_0007_O_REPRE_2TANK_TANK1_TANK_PRESSURE_NO3		0x0042
#define		COMMAND_16_0008_O_REPRE_2TANK_TANK1_5SEC_START_NO3			0x0043
#define		COMMAND_16_0009_O_REPRE_2TANK_TANK1_IS_5SEC_NO3				0x0044
#define		COMMAND_16_0010_O_REPRE_2TANK_TANK1_TANK_PRESSURE_NO4		0x0045
#define		COMMAND_16_0011_O_REPRE_2TANK_TANK1_5SEC_START_NO4			0x0046
#define		COMMAND_16_0012_O_REPRE_2TANK_TANK1_IS_5SEC_NO4				0x0047
#define		COMMAND_16_0013_O_REPRE_2TANK_TANK1_TANK_PRESSURE_NO5		0x0048
#define		COMMAND_16_0014_O_REPRE_2TANK_TANK1_5SEC_START_NO5			0x0049
#define		COMMAND_16_0015_O_REPRE_2TANK_TANK1_IS_5SEC_NO5				0x004a
#define		COMMAND_16_0016_O_REPRE_2TANK_TANK1_TANK_PRESSURE_NO6		0x004b
#define		COMMAND_16_0017_O_REPRE_2TANK_TANK1_5SEC_START_NO6			0x004c
#define		COMMAND_16_0018_O_REPRE_2TANK_TANK1_IS_5SEC_NO6				0x004d
#define		COMMAND_16_0019_O_REPRE_2TANK_TANK1_TANK_PRESSURE_NO7		0x004e
#define		COMMAND_16_0020_O_REPRE_2TANK_TANK1_IS_PRESSURE_STABLE		0x004f



//������ѹ���򿪸�ѹ���������ڶ�������
#define		COMMAND_16_0001_O_REPRE_2TANK_TANK2_LVT_VALVE_ON			0x0050
#define		COMMAND_16_0002_O_REPRE_2TANK_TANK2_1MIN_START_NO1			0x0051
#define		COMMAND_16_0003_O_REPRE_2TANK_TANK2_IS_1MIN_NO1				0x0052
#define		COMMAND_16_0004_O_REPRE_2TANK_TANK2_IS_LVT_VALVE_ON			0x0053

//ͨ��ѹ����ʱ���жϸ�ѹ�Ƿ�������ڶ�������
#define		COMMAND_16_0001_O_REPRE_2TANK_TANK2_IS_REPRE_OVER			0x0054

//��ѹ�������رո�ѹ���������ڶ�������
#define		COMMAND_16_0001_O_REPRE_2TANK_TANK2_LVT_VALVE_OFF			0x0055
#define		COMMAND_16_0002_O_REPRE_2TANK_TANK2_1MIN_START_NO2			0x0056
#define		COMMAND_16_0003_O_REPRE_2TANK_TANK2_IS_1MIN_NO2				0x0057
#define		COMMAND_16_0004_O_REPRE_2TANK_TANK2_IS_LVT_VALVE_OFF		0x0058

//��������ڷ��ţ��ڶ�������
#define		COMMAND_16_0001_O_REPRE_2TANK_TANK2_OUT_TANK_VALVE_ON_NO1		0x0059
#define		COMMAND_16_0002_O_REPRE_2TANK_TANK2_1MIN_START_NO3				0x005a
#define		COMMAND_16_0003_O_REPRE_2TANK_TANK2_IS_1MIN_NO3					0x005b
#define		COMMAND_16_0004_O_REPRE_2TANK_TANK2_IS_OUT_TANK_VALVE_ON_NO1	0x005c
#define		COMMAND_16_0005_O_REPRE_2TANK_TANK2_OUT_TANK_VALVE_ON_NO2		0x005d
#define		COMMAND_16_0006_O_REPRE_2TANK_TANK2_1MIN_START_NO4				0x005e
#define		COMMAND_16_0007_O_REPRE_2TANK_TANK2_IS_1MIN_NO4					0x005f
#define		COMMAND_16_0008_O_REPRE_2TANK_TANK2_IS_OUT_TANK_VALVE_ON_NO2	0x0060


//��ʱ�ȴ����ڶ�������
#define		COMMAND_16_0001_O_REPRE_2TANK_TANK2_DELAY_START_NO1			0x0061
#define		COMMAND_16_0002_O_REPRE_2TANK_TANK2_IS_DELAY_NO1			0x0062


//�ж�����ѹ�����ȶ��ԣ��ڶ�������
#define		COMMAND_16_0001_O_REPRE_2TANK_TANK2_TANK_PRESSURE_NO1		0x0063
#define		COMMAND_16_0002_O_REPRE_2TANK_TANK2_5SEC_START_NO1			0x0064
#define		COMMAND_16_0003_O_REPRE_2TANK_TANK2_IS_5SEC_NO1				0x0065
#define		COMMAND_16_0004_O_REPRE_2TANK_TANK2_TANK_PRESSURE_NO2		0x0066
#define		COMMAND_16_0005_O_REPRE_2TANK_TANK2_5SEC_START_NO2			0x0067
#define		COMMAND_16_0006_O_REPRE_2TANK_TANK2_IS_5SEC_NO2				0x0068
#define		COMMAND_16_0007_O_REPRE_2TANK_TANK2_TANK_PRESSURE_NO3		0x0069
#define		COMMAND_16_0008_O_REPRE_2TANK_TANK2_5SEC_START_NO3			0x006a
#define		COMMAND_16_0009_O_REPRE_2TANK_TANK2_IS_5SEC_NO3				0x006b
#define		COMMAND_16_0010_O_REPRE_2TANK_TANK2_TANK_PRESSURE_NO4		0x006c
#define		COMMAND_16_0011_O_REPRE_2TANK_TANK2_5SEC_START_NO4			0x006d
#define		COMMAND_16_0012_O_REPRE_2TANK_TANK2_IS_5SEC_NO4				0x006e
#define		COMMAND_16_0013_O_REPRE_2TANK_TANK2_TANK_PRESSURE_NO5		0x006f
#define		COMMAND_16_0014_O_REPRE_2TANK_TANK2_5SEC_START_NO5			0x0070
#define		COMMAND_16_0015_O_REPRE_2TANK_TANK2_IS_5SEC_NO5				0x0071
#define		COMMAND_16_0016_O_REPRE_2TANK_TANK2_TANK_PRESSURE_NO6		0x0072
#define		COMMAND_16_0017_O_REPRE_2TANK_TANK2_5SEC_START_NO6			0x0073
#define		COMMAND_16_0018_O_REPRE_2TANK_TANK2_IS_5SEC_NO6				0x0074
#define		COMMAND_16_0019_O_REPRE_2TANK_TANK2_TANK_PRESSURE_NO7		0x0075
#define		COMMAND_16_0020_O_REPRE_2TANK_TANK2_IS_PRESSURE_STABLE		0x0076


//---------------��������--------------------------------------------------------------

void TGTHT510_supply_stage16_repre_o_main(void);
void TGTHT510_supply_stage16_repre_o_step_tank_number(void);
uint16 TGTHT510_supply_stage16_repre_o_step_1tank_lvt_valve_on(void);
uint16 TGTHT510_supply_stage16_repre_o_step_1tank_is_repre_over(void);
uint16 TGTHT510_supply_stage16_repre_o_step_1tank_lvt_valve_off(void);
uint16 TGTHT510_supply_stage16_repre_o_step_1tank_out_tank_valve_on(void);
uint16 TGTHT510_supply_stage16_repre_o_step_1tank_delay(void);
uint16 TGTHT510_supply_stage16_repre_o_step_1tank_is_tank_pressure_stable(void);

uint16 TGTHT510_supply_stage16_repre_o_step_2tank_tank1_lvt_valve_on(void);
uint16 TGTHT510_supply_stage16_repre_o_step_2tank_tank1_is_repre_over(void);
uint16 TGTHT510_supply_stage16_repre_o_step_2tank_tank1_lvt_valve_off(void);
uint16 TGTHT510_supply_stage16_repre_o_step_2tank_tank1_out_tank_valve_on(void);
uint16 TGTHT510_supply_stage16_repre_o_step_2tank_tank1_delay(void);
uint16 TGTHT510_supply_stage16_repre_o_step_2tank_tank1_is_tank_pressure_stable(void);

uint16 TGTHT510_supply_stage16_repre_o_step_2tank_tank2_lvt_valve_on(void);
uint16 TGTHT510_supply_stage16_repre_o_step_2tank_tank2_is_repre_over(void);
uint16 TGTHT510_supply_stage16_repre_o_step_2tank_tank2_lvt_valve_off(void);
uint16 TGTHT510_supply_stage16_repre_o_step_2tank_tank2_out_tank_valve_on(void);
uint16 TGTHT510_supply_stage16_repre_o_step_2tank_tank2_delay(void);
uint16 TGTHT510_supply_stage16_repre_o_step_2tank_tank2_is_tank_pressure_stable(void);

#endif
 
 
 

 
 
 
