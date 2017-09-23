/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ���������������������ͷ�ļ�
  ******************************************************************************
  */

#ifndef __supply_stage_17_comp_o_third_h
#define __supply_stage_17_comp_o_third_h

/*�궨��---------------------------------------------------------------------------*/


//����step-------------------------------------------------------------------------

//----------------------------------��ʼ���ý׶�-----------------------------------

#define 	STEP_17_O_INIT_START_COOLER							0x0000//����Һ��ù���
#define 	STEP_17_O_INIT_IS_COOLER_WORK						0x0001//ͨ��ת���ж�Һ�乤���Ƿ�����
#define 	STEP_17_O_INIT_DELAY								0x0002//��ʱ�ȴ�ʱ��
#define		STEP_17_O_INIT_IS_COMPRESSOR_TEMPERATURE			0x0003//�ж�ѹ�����¶��Ƿ�����
#define		STEP_17_O_INIT_TGTHT530_POWER_ON					0x0004//�������������ӵ�
#define		STEP_17_O_INIT_COMPRESSOR_POWER_ON					0x0005//����ѹ�����ӵ�
#define		STEP_17_O_INIT_ISOLATION							0x0006//�������

//----------------------------------�������������-----------------------------------

#define 	STEP_17_O_1TANK_IN_TANK_VALVE_ON					0x0007//���������ѹ��·���ӷ���

#define 	STEP_17_O_1TANK_TIME_DELAY_A						0x0008//��ʱ�ȴ�

#define 	STEP_17_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE		0x0009//ͨ��ѹ���жϿ��������ѹ��·���ӷ���
#define 	STEP_17_O_1TANK_IN_COMPRESSOR_VALVE_ON				0x000a//��ȼѹ�������ڷ���
#define 	STEP_17_O_1TANK_TIME_DELAY1							0x000b//��ʱ�ȴ�time_delay1
#define 	STEP_17_O_1TANK_IS_IN_COMPRESSOR_PRESSURE			0x000c//�ж�ѹ��������ѹ���Ƿ�����
#define 	STEP_17_O_1TANK_COMPRESSOR_START					0x000d//ȼѹ��������

#define 	STEP_17_O_1TANK_TIME_DELAY_B						0x000e//��ʱ�ȴ�

#define 	STEP_17_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE			0x000f//�ж�ѹ��������ѹ���Ƿ�����
#define 	STEP_17_O_1TANK_OUT_COMPRESSOR_VALVE_ON				0x0010//��ȼѹ�������ڷ���
#define 	STEP_17_O_1TANK_NUMBER_COMP_GAS						0x0011//�жϳ�����ƿ����

//һ����ƿ����
#define 	STEP_17_O_1TANK_1GAS_IN_GAS_VALVE_ON				0x0012//������ƿ���ӷ���
#define 	STEP_17_O_1TANK_1GAS_TIME_DELAY2					0x0013//��ʱ�ȴ�time_delay2
#define 	STEP_17_O_1TANK_1GAS_IS_GAS_PRESSURE				0x0014//�ж���ƿѹ���Ƿ�����
#define 	STEP_17_O_1TANK_1GAS_IS_COMP_OVER					0x0015//�ж���ƿ�����Ƿ����
#define 	STEP_17_O_1TANK_1GAS_IN_GAS_VALVE_OFF				0x0016//��ȼ·��ƿ���ӷ���

#define		STEP_17_O_1TANK_1GAS_IS_ISOLATION_FIRST				0x0017//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define 	STEP_17_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF		0x0018//�ر�ȼѹ�������ڷ���
#define		STEP_17_O_1TANK_1GAS_IS_ISOLATION_SECOND			0x0019//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���

#define		STEP_17_O_1TANK_1GAS_COMPRESSOR_STOP				0x001a//ȼѹ����ͣ��
#define		STEP_17_O_1TANK_1GAS_IS_COMPRESSOR_STOP				0x001b//�ж�ȼѹ����ͣ���Ƿ�����
#define		STEP_17_O_1TANK_1GAS_BYPATH_VALVE_ON				0x001c//��ȼѹ������·������
#define 	STEP_17_O_1TANK_1GAS_TIME_DELAY_BYPATH				0x001d//��ʱ�ȴ�time_bypath
#define		STEP_17_O_1TANK_1GAS_BYPATH_VALVE_OFF				0x001e//��ȼѹ������·������
#define 	STEP_17_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2		0x001f//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define 	STEP_17_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF		0x0020//�ر�ȼѹ�������ڷ���
#define 	STEP_17_O_1TANK_1GAS_IN_TANK_VALVE_OFF				0x0021//�ؽ������ѹ��·���ӷ���
#define 	STEP_17_O_1TANK_1GAS_SET_STATE_GOOD					0x0022//����ȼ����״̬��
#define 	STEP_17_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE		0x0023//�ж�ѹ�����¶��Ƿ�����

#define 	STEP_17_O_1TANK_1GAS_TIME_DELAY3					0x0024//��ʱ�ȴ�time_delay3

//#define 	STEP_17_O_1TANK_1GAS_EXCHANGE_COOLER				0x0025//����Һ��ģ���л�����
//#define	STEP_17_O_1TANK_1GAS_IS_EXCHANGE_COOLER				0x0026//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����

#define		STEP_17_O_1TANK_1GAS_COOLER_STOP					0x0025//Һ��ģ��ͣ��
#define		STEP_17_O_1TANK_1GAS_COOLER_SET						0x0026//Һ��ģ��״̬����

#define		STEP_17_O_1TANK_1GAS_COMPRESSOR_POWER_OFF			0x0028//����ѹ�����ϵ�
#define		STEP_17_O_1TANK_1GAS_TGTHT530_POWER_OFF				0x0029//�������������ϵ�

//**************************************�������******************************************************************

//������ƿ����
#define 	STEP_17_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON			0x002a//������ƿ���ӷ���---��һ����ƿ
#define 	STEP_17_O_1TANK_2GAS_GAS1_TIME_DELAY2				0x002b//��ʱ�ȴ�time_delay2---��һ����ƿ
#define 	STEP_17_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE			0x002c//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define 	STEP_17_O_1TANK_2GAS_GAS1_IS_COMP_OVER				0x002d//�ж���ƿ�����Ƿ����---��һ����ƿ
#define 	STEP_17_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF			0x002e//��ȼ·��ƿ���ӷ���---��һ����ƿ
#define 	STEP_17_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON			0x002f//������ƿ���ӷ���---�ڶ�����ƿ
#define 	STEP_17_O_1TANK_2GAS_GAS2_TIME_DELAY2				0x0030//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define 	STEP_17_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE			0x0031//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define 	STEP_17_O_1TANK_2GAS_GAS2_IS_COMP_OVER				0x0032//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define 	STEP_17_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF			0x0033//��ȼ·��ƿ���ӷ���---�ڶ�����ƿ

#define		STEP_17_O_1TANK_2GAS_IS_ISOLATION_FIRST				0x0034//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define 	STEP_17_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF		0x0035//�ر�ȼѹ�������ڷ���
#define		STEP_17_O_1TANK_2GAS_IS_ISOLATION_SECOND			0x0036//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���

#define		STEP_17_O_1TANK_2GAS_COMPRESSOR_STOP				0x0037//ȼѹ����ͣ��
#define		STEP_17_O_1TANK_2GAS_IS_COMPRESSOR_STOP				0x0038//�ж�ȼѹ����ͣ���Ƿ�����
#define		STEP_17_O_1TANK_2GAS_BYPATH_VALVE_ON				0x0039//��ȼѹ������·������
#define 	STEP_17_O_1TANK_2GAS_TIME_DELAY_BYPATH				0x003a//��ʱ�ȴ�time_bypath
#define		STEP_17_O_1TANK_2GAS_BYPATH_VALVE_OFF				0x003b//��ȼѹ������·������
#define 	STEP_17_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2		0x003c//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define 	STEP_17_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF		0x003d//�ر�ȼѹ�������ڷ���
#define 	STEP_17_O_1TANK_2GAS_IN_TANK_VALVE_OFF				0x003e//�ؽ������ѹ��·���ӷ���
#define 	STEP_17_O_1TANK_2GAS_SET_STATE_GOOD					0x003f//����ȼ����״̬��
#define 	STEP_17_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE		0x0040//�ж�ѹ�����¶��Ƿ�����

#define 	STEP_17_O_1TANK_2GAS_TIME_DELAY3					0x0041//��ʱ�ȴ�time_delay3

//#define 	STEP_17_O_1TANK_2GAS_EXCHANGE_COOLER				0x0042//����Һ��ģ���л�����
//#define	STEP_17_O_1TANK_2GAS_IS_EXCHANGE_COOLER				0x0043//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����

#define		STEP_17_O_1TANK_2GAS_COOLER_STOP					0x0042//Һ��ģ��ͣ��
#define		STEP_17_O_1TANK_2GAS_COOLER_SET						0x0043//Һ��ģ��״̬����

#define		STEP_17_O_1TANK_2GAS_COMPRESSOR_POWER_OFF			0x0045//����ѹ�����ϵ�
#define		STEP_17_O_1TANK_2GAS_TGTHT530_POWER_OFF				0x0046//�������������ϵ�

//**************************************�������******************************************************************

//����command--------------------------------------------------------------------------------------------

//------------------------------command---��ʼ���ý׶�---------------------------------------------------

//����Һ��ù���
#define		COMMAND_17_0001_O_INIT_COOLER_VALVE_ON_NO1			0x0001//Һ��ģ�鲹��ϵͳ���ſ���һ��
#define		COMMAND_17_0002_O_INIT_IS_COOLER_VALVE_ON_NO1		0x0002//�ж�Һ��ģ�鲹��ϵͳ���ſ���һ��
#define		COMMAND_17_0003_O_INIT_COOLER_VALVE_ON_NO2			0x0003//Һ��ģ�鲹��ϵͳ���ſ��ڶ���
#define		COMMAND_17_0004_O_INIT_IS_COOLER_VALVE_ON_NO2		0x0004//�ж�Һ��ģ�鲹��ϵͳ���ſ��ڶ���
#define		COMMAND_17_0005_O_INIT_COOLER_POWER_ON				0x0005//Һ��ģ�鹩��ͨ
#define		COMMAND_17_0006_O_INIT_TIME_1MIN_START				0x0006//��ʱ1min��ʱ��ʼ
#define		COMMAND_17_0007_O_INIT_IS_TIME_1MIN					0x0007//��ʱ1min�Ƿ�

//ͨ��ת���ж�Һ�乤���Ƿ�����
#define		COMMAND_17_0001_O_INIT_IS_COOLER_WORK				0x0008//ͨ��ת���ж�Һ�乤���Ƿ�����

//��ʱ�ȴ�time_delay
#define		COMMAND_17_0001_O_INIT_TIME_DELAY_START				0x0009//��ʱ�ȴ�time_delay��ʱ��ʼ
#define		COMMAND_17_0002_O_INIT_IS_TIME_DELAY				0x000a//�ж���ʱ�ȴ�time_delay

//�ж�ѹ�����¶��Ƿ�����
#define		COMMAND_17_0001_O_INIT_IS_COMPRESSOR_TEMPERATURE	0x000b//�ж�ѹ�����¶��Ƿ�����

//�������������ӵ�
#define		COMMAND_17_0001_O_INIT_TGTHT530_POWER_ON			0x000c//�����豸����ָ��
#define		COMMAND_17_0002_O_INIT_TGTHT530_TIME_1MIN_START		0x000d//��ʱ1min��ʱ��ʼ
#define		COMMAND_17_0003_O_INIT_TGTHT530_IS_TIME_1MIN		0x000e//�жϼ�ʱ1min�Ƿ�
#define		COMMAND_17_0004_O_INIT_TGTHT530_IS_POWER_ON			0x000f//ͨ�����������жϼӵ��Ƿ�����

//����ѹ�����ӵ�
#define		COMMAND_17_0001_O_INIT_COMPRESSOR_POWER_ON			0x0010//�����豸����ָ��
#define		COMMAND_17_0002_O_INIT_COMPRESSOR_TIME_1MIN_START	0x0011//��ʱ1min��ʱ��ʼ
#define		COMMAND_17_0003_O_INIT_COMPRESSOR_IS_TIME_1MIN		0x0012//�жϼ�ʱ1min�Ƿ�

//�������
#define		COMMAND_17_0001_O_INIT_ISOLATION_VALVE_OFF_NO1		0x0013//�����ƽ�ϵͳ�������رգ���һ��
#define		COMMAND_17_0002_O_INIT_TIME_1MIN_START_NO1			0x0014//��ʱ1min��ʱ��ʼ����һ��
#define		COMMAND_17_0003_O_INIT_IS_TIME_1MIN_NO1				0x0015//��ʱ1min�Ƿ񵽣���һ��
#define		COMMAND_17_0004_O_INIT_IS_ISOLATION_VALVE_OFF_NO1	0x0016//�жϸ����ƽ�ϵͳ�������رգ���һ��

#define		COMMAND_17_0005_O_INIT_ISOLATION_VALVE_OFF_NO2		0x0017//�����ƽ�ϵͳ�������رգ��ڶ���
#define		COMMAND_17_0006_O_INIT_TIME_1MIN_START_NO2			0x0018//��ʱ1min��ʱ��ʼ���ڶ���
#define		COMMAND_17_0007_O_INIT_IS_TIME_1MIN_NO2				0x0019//��ʱ1min�Ƿ񵽣��ڶ���
#define		COMMAND_17_0008_O_INIT_IS_ISOLATION_VALVE_OFF_NO2	0x001a//�жϸ����ƽ�ϵͳ�������رգ��ڶ���

#define		COMMAND_17_0009_O_INIT_ISOLATION_VALVE_OFF_NO3		0x001b//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_17_0010_O_INIT_TIME_1MIN_START_NO3			0x001c//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_17_0011_O_INIT_IS_TIME_1MIN_NO3				0x001d//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_17_0012_O_INIT_IS_ISOLATION_VALVE_OFF_NO3	0x001e//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_17_0013_O_INIT_ISOLATION_VALVE_OFF_NO4		0x001f//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_17_0014_O_INIT_TIME_1MIN_START_NO4			0x0020//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_17_0015_O_INIT_IS_TIME_1MIN_NO4				0x0021//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_17_0016_O_INIT_IS_ISOLATION_VALVE_OFF_NO4	0x0022//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_17_0017_O_INIT_ISOLATION_VALVE_OFF_NO5		0x0023//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_17_0018_O_INIT_TIME_1MIN_START_NO5			0x0024//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_17_0019_O_INIT_IS_TIME_1MIN_NO5				0x0025//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_17_0020_O_INIT_IS_ISOLATION_VALVE_OFF_NO5	0x0026//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_17_0021_O_INIT_ISOLATION_VALVE_OFF_NO6		0x0027//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_17_0022_O_INIT_TIME_1MIN_START_NO6			0x0028//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_17_0023_O_INIT_IS_TIME_1MIN_NO6				0x0029//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_17_0024_O_INIT_IS_ISOLATION_VALVE_OFF_NO6	0x002a//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_17_0025_O_INIT_ISOLATION_VALVE_OFF_NO7		0x002b//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_17_0026_O_INIT_TIME_1MIN_START_NO7			0x002c//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_17_0027_O_INIT_IS_TIME_1MIN_NO7				0x002d//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_17_0028_O_INIT_IS_ISOLATION_VALVE_OFF_NO7	0x002e//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_17_0029_O_INIT_ISOLATION_VALVE_OFF_NO8		0x002f//�����ƽ�ϵͳ�������رգ��ڰ���
#define		COMMAND_17_0030_O_INIT_TIME_1MIN_START_NO8			0x0030//��ʱ1min��ʱ��ʼ���ڰ���
#define		COMMAND_17_0031_O_INIT_IS_TIME_1MIN_NO8				0x0031//��ʱ1min�Ƿ񵽣��ڰ���
#define		COMMAND_17_0032_O_INIT_IS_ISOLATION_VALVE_OFF_NO8	0x0032//�жϸ����ƽ�ϵͳ�������رգ��ڰ���

#define		COMMAND_17_0033_O_INIT_ISOLATION_VALVE_OFF_NO9		0x0033//�����ƽ�ϵͳ�������رգ��ھ���
#define		COMMAND_17_0034_O_INIT_TIME_1MIN_START_NO9			0x0034//��ʱ1min��ʱ��ʼ���ھ���
#define		COMMAND_17_0035_O_INIT_IS_TIME_1MIN_NO9				0x0035//��ʱ1min�Ƿ񵽣��ھ���
#define		COMMAND_17_0036_O_INIT_IS_ISOLATION_VALVE_OFF_NO9	0x0036//�жϸ����ƽ�ϵͳ�������رգ��ھ���

//------------------------------command---�������������-----------------------------------------------

//���������ѹ��·���ӷ���
#define		COMMAND_17_0001_O_1TANK_IN_TANK_VALVE_ON					0x0038//���������ѹ��·���ӷ���
#define		COMMAND_17_0002_O_1TANK_IS_IN_TANK_VALVE_ON					0x0039//�жϿ��������ѹ��·���ӷ���

//ͨ��ѹ���жϿ��������ѹ��·���ӷ���
#define		COMMAND_17_0001_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE		0x003a//ͨ��ѹ���жϿ����ӷ���

//��ȼѹ�������ڷ���
#define		COMMAND_17_0001_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO1			0x003b//��ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0002_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO1		0x003c//�жϿ�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0003_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO2			0x003d//��ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0004_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO2		0x003e//�жϿ�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0005_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO3			0x003f//��ȼѹ�������ڷ��ţ�������
#define		COMMAND_17_0006_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO3		0x0040//�жϿ�ȼѹ�������ڷ��ţ�������

//��ʱ�ȴ�time_delay1
#define		COMMAND_17_0001_O_1TANK_TIME_DELAY1_START					0x0041//��ʱ�ȴ�time_delay1��ʱ��ʼ
#define		COMMAND_17_0002_O_1TANK_IS_TIME_DELAY1						0x0042//�ж���ʱ�ȴ�time_delay1

//�ж�ѹ��������ѹ���Ƿ�����
#define		COMMAND_17_0001_O_1TANK_IS_IN_COMPRESSOR_PRESSURE			0x0043//�ж�ѹ��������ѹ���Ƿ�����

//ȼѹ��������
#define		COMMAND_17_0001_O_1TANK_COMPRESSOR_START					0x0044//�����豸����ָ�ѹ��������
#define		COMMAND_17_0002_O_1TANK_COMPRESSOR_TIME_1MIN_START			0x0045//��ʱ1min��ʱ��ʼ
#define		COMMAND_17_0003_O_1TANK_COMPRESSOR_IS_TIME_1MIN				0x0046//�ж�1min��ʱ
#define		COMMAND_17_0004_O_1TANK_IS_COMPRESSOR_START					0x0047//ͨ�����������ж������Ƿ�����

//�ж�ѹ��������ѹ���Ƿ�����
#define		COMMAND_17_0001_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE			0x0048//�ж�ѹ��������ѹ���Ƿ�����

//��ȼѹ�������ڷ���
#define		COMMAND_17_0001_O_1TANK_OUT_COMPRESSOR_VALVE_ON				0x0049//��ȼѹ�������ڷ���
#define		COMMAND_17_0002_O_1TANK_IS_OUT_COMPRESSOR_VALVE_ON			0x004a//�жϿ�ȼѹ�������ڷ���

//�жϳ�����ƿ����
#define		COMMAND_17_0001_O_1TANK_NUMBER_COMP_GAS						0x004b//�жϳ�����ƿ����


//------------------------------command---�������������----һ����ƿ����-----------------------------------

//������ƿ���ӷ���
#define		COMMAND_17_0001_O_1TANK_1GAS_IN_GAS_VALVE_ON				0x004c//������ƿ���ӷ���
#define		COMMAND_17_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_ON				0x004d//�жϿ�����ƿ���ӷ���

//��ʱ�ȴ�time_delay2
#define		COMMAND_17_0001_O_1TANK_1GAS_TIME_DELAY2_START				0x004e//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_17_0002_O_1TANK_1GAS_IS_TIME_DELAY2					0x004f//�ж���ʱ�ȴ�time_delay2


//�ж���ƿѹ���Ƿ�����
#define		COMMAND_17_0001_O_1TANK_1GAS_GAS_PRESSURE_NO1				0x0050//�ɼ���ƿѹ������һ��
#define		COMMAND_17_0002_O_1TANK_1GAS_TIME_30S_START_NO1				0x0051//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_17_0003_O_1TANK_1GAS_IS_TIME_30S_NO1				0x0052//�ж϶�ʱ30s����һ��
#define		COMMAND_17_0004_O_1TANK_1GAS_GAS_PRESSURE_NO2				0x0053//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_17_0005_O_1TANK_1GAS_TIME_30S_START_NO2				0x0054//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_17_0006_O_1TANK_1GAS_IS_TIME_30S_NO2				0x0055//�ж϶�ʱ30s���ڶ���
#define		COMMAND_17_0007_O_1TANK_1GAS_GAS_PRESSURE_NO3				0x0056//�ɼ���ƿѹ����������
#define		COMMAND_17_0008_O_1TANK_1GAS_TIME_30S_START_NO3				0x0057//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_17_0009_O_1TANK_1GAS_IS_TIME_30S_NO3				0x0058//�ж϶�ʱ30s��������
#define		COMMAND_17_0010_O_1TANK_1GAS_GAS_PRESSURE_NO4				0x0059//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_17_0011_O_1TANK_1GAS_TIME_30S_START_NO4				0x005a//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_17_0012_O_1TANK_1GAS_IS_TIME_30S_NO4				0x005b//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_17_0013_O_1TANK_1GAS_GAS_PRESSURE_NO5				0x005c//�ɼ���ƿѹ���������
#define		COMMAND_17_0014_O_1TANK_1GAS_TIME_30S_START_NO5				0x005d//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_17_0015_O_1TANK_1GAS_IS_TIME_30S_NO5				0x005e//�ж϶�ʱ30s�������
#define		COMMAND_17_0016_O_1TANK_1GAS_GAS_PRESSURE_NO6				0x005f//�ɼ���ƿѹ����������
#define		COMMAND_17_0017_O_1TANK_1GAS_TIME_30S_START_NO6				0x0060//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_17_0018_O_1TANK_1GAS_IS_TIME_30S_NO6				0x0061//�ж϶�ʱ30s��������
#define		COMMAND_17_0019_O_1TANK_1GAS_GAS_PRESSURE_NO7				0x0062//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_17_0020_O_1TANK_1GAS_TIME_30S_START_NO7				0x0063//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_17_0021_O_1TANK_1GAS_IS_TIME_30S_NO7				0x0064//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_17_0022_O_1TANK_1GAS_GAS_PRESSURE_NO8				0x0065//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_17_0023_O_1TANK_1GAS_TIME_30S_START_NO8				0x0066//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_17_0024_O_1TANK_1GAS_IS_TIME_30S_NO8				0x0067//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_17_0025_O_1TANK_1GAS_GAS_PRESSURE_NO9				0x0068//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_17_0026_O_1TANK_1GAS_TIME_30S_START_NO9				0x0069//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_17_0027_O_1TANK_1GAS_IS_TIME_30S_NO9				0x006a//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_17_0028_O_1TANK_1GAS_GAS_PRESSURE_NO10				0x006b//�ɼ���ƿѹ������ʮ��
#define		COMMAND_17_0029_O_1TANK_1GAS_IS_GAS_PRESSURE				0x006c//ѹ���ж���ƿѹ���Ƿ�����

//�ж���ƿ�����Ƿ����
#define		COMMAND_17_0001_O_1TANK_1GAS_IS_COMP_GAS_OVER				0x006d//�ж���ƿ�����Ƿ����

//��ȼ·��ƿ���ӷ���
#define		COMMAND_17_0001_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO1			0x006e//��ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_17_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO1		0x006f//�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_17_0003_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO2			0x0070//��ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_17_0004_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO2		0x0071//�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_17_0005_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO3			0x0072//��ȼ·��ƿ���ӷ��ţ�������
#define		COMMAND_17_0006_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO3		0x0073//�жϹ�ȼ·��ƿ���ӷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define		COMMAND_17_0001_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO1	0x0074//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_17_0002_O_1TANK_1GAS_FIRST_TIME_12S_START_NO1		0x0075//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_17_0003_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO1			0x0076//�ж϶�ʱ12s����һ��
#define		COMMAND_17_0004_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO2	0x0077//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_17_0005_O_1TANK_1GAS_FIRST_TIME_12S_START_NO2		0x0078//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_17_0006_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO2			0x0079//�ж϶�ʱ12s���ڶ���
#define		COMMAND_17_0007_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO3	0x007a//�ɼ�ѹ��������ѹ����������
#define		COMMAND_17_0008_O_1TANK_1GAS_FIRST_TIME_12S_START_NO3		0x007b//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_17_0009_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO3			0x007c//�ж϶�ʱ12s��������
#define		COMMAND_17_0010_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO4	0x007d//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_17_0011_O_1TANK_1GAS_FIRST_IS_ISOLATION				0x007e//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//�ر�ȼѹ�������ڷ���
#define		COMMAND_17_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1			0x007f//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x0080//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2			0x0081//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x0082//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3			0x0083//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_17_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x0084//�жϹر�ȼѹ�������ڷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���
#define		COMMAND_17_0001_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO1	0x0085//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_17_0002_O_1TANK_1GAS_SECOND_TIME_12S_START_NO1		0x0086//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_17_0003_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO1			0x0087//�ж϶�ʱ12s����һ��
#define		COMMAND_17_0004_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO2	0x0088//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_17_0005_O_1TANK_1GAS_SECOND_TIME_12S_START_NO2		0x0089//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_17_0006_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO2			0x008a//�ж϶�ʱ12s���ڶ���
#define		COMMAND_17_0007_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO3	0x008b//�ɼ�ѹ��������ѹ����������
#define		COMMAND_17_0008_O_1TANK_1GAS_SECOND_TIME_12S_START_NO3		0x008c//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_17_0009_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO3			0x008d//�ж϶�ʱ12s��������
#define		COMMAND_17_0010_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO4	0x008e//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_17_0011_O_1TANK_1GAS_SECOND_IS_ISOLATION			0x008f//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//ȼѹ����ͣ��
#define		COMMAND_17_0001_O_1TANK_1GAS_COMPRESSOR_STOP				0x0090//�����豸����ָ�ѹ����ͣ��
#define		COMMAND_17_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START		0x0091//��ʱ1min��ʱ��ʼ
#define		COMMAND_17_0003_O_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN		0x0092//�ж�1min��ʱ

//�ж�ȼѹ����ͣ���Ƿ�����
#define		COMMAND_17_0001_O_1TANK_1GAS_COMPRESSOR_V_NO1				0x0093//�ɼ����ת�٣���һ��
#define		COMMAND_17_0002_O_1TANK_1GAS_COMPRESSOR_V_NO2				0x0094//�ɼ����ת�٣��ڶ���
#define		COMMAND_17_0003_O_1TANK_1GAS_COMPRESSOR_V_NO3				0x0095//�ɼ����ת�٣�������
#define		COMMAND_17_0004_O_1TANK_1GAS_COMPRESSOR_V_NO4				0x0096//�ɼ����ת�٣����Ĵ�
#define		COMMAND_17_0005_O_1TANK_1GAS_COMPRESSOR_V_NO5				0x0097//�ɼ����ת�٣������
#define		COMMAND_17_0006_O_1TANK_1GAS_COMPRESSOR_V_NO6				0x0098//�ɼ����ת�٣�������
#define		COMMAND_17_0007_O_1TANK_1GAS_COMPRESSOR_V_NO7				0x0099//�ɼ����ת�٣����ߴ�
#define		COMMAND_17_0008_O_1TANK_1GAS_COMPRESSOR_V_NO8				0x009a//�ɼ����ת�٣��ڰ˴�
#define		COMMAND_17_0009_O_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO1	0x009b//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_17_0010_O_1TANK_1GAS_TIME_12S_START					0x009c//��ʱ12s��ʱ��ʼ
#define		COMMAND_17_0011_O_1TANK_1GAS_IS_TIME_12S					0x009d//�ж϶�ʱ12s
#define		COMMAND_17_0012_O_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO2	0x009e//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_17_0013_O_1TANK_1GAS_IS_COMPRESSOR_STOP				0x009f//�ж�ȼѹ����ͣ���Ƿ�����

//��ȼѹ������·������
#define		COMMAND_17_0001_O_1TANK_1GAS_BYPATH_VALVE_ON				0x00a0//��ȼѹ������·������
#define		COMMAND_17_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_ON				0x00a1//�жϿ�ȼѹ������·������

//��ʱ�ȴ�time_bypath
#define		COMMAND_17_0001_O_1TANK_1GAS_TIME_BYPATH_START				0x00a2//��ʱ�ȴ�time_bypath��ʱ����
#define		COMMAND_17_0002_O_1TANK_1GAS_IS_TIME_BYPATH					0x00a3//�ж���ʱ�ȴ�time_bypath

//��ȼѹ������·������
#define		COMMAND_17_0001_O_1TANK_1GAS_BYPATH_VALVE_OFF				0x00a4//��ȼѹ������·������
#define		COMMAND_17_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_OFF			0x00a5//�жϹ�ȼѹ������·������

//�ر�ȼѹ�������ڷ���
#define		COMMAND_17_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1			0x00a6//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x00a7//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2			0x00a8//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x00a9//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3			0x00aa//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_17_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x00ab//�жϹر�ȼѹ�������ڷ��ţ�������

//�ر�ȼѹ�������ڷ���
#define		COMMAND_17_0001_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x00ac//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0002_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1		0x00ad//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0003_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x00ae//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0004_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2		0x00af//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0005_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x00b0//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_17_0006_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3		0x00b1//�жϹر�ȼѹ�������ڷ��ţ�������

//�ؽ������ѹ��·���ӷ���
#define		COMMAND_17_0001_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO1				0x00b2//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_17_0002_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO1			0x00b3//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_17_0003_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO2				0x00b4//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_17_0004_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO2			0x00b5//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_17_0005_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO3				0x00b6//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_17_0006_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO3			0x00b7//�жϹؽ������ѹ��·���ӷ��ţ�������

//����ȼ����״̬��
#define		COMMAND_17_0001_O_1TANK_1GAS_SET_STATE_GOOD						0x00b8//����ȼ����״̬��

//�ж�ѹ�����¶��Ƿ�����
#define		COMMAND_17_0001_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE			0x00b9//�ж�ѹ�����¶��Ƿ�����


//��ʱ�ȴ�time_delay3
#define		COMMAND_17_0001_O_1TANK_1GAS_TIME_DELAY3_START					0x00bb//��ʱ�ȴ�time_delay3��ʱ��ʼ
#define		COMMAND_17_0002_O_1TANK_1GAS_IS_TIME_DELAY3						0x00bc//�ж���ʱ�ȴ�time_delay3


/*
//����Һ��ģ���л�����
#define		COMMAND_17_0001_O_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO1			0x00bd//Һ��ģ���л����򣬷��Ŷ�������һ��
#define		COMMAND_17_0002_O_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x00be//�ж�Һ��ģ���л����򣬷��Ŷ�������һ��
#define		COMMAND_17_0003_O_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO2			0x00bf//Һ��ģ���л����򣬷��Ŷ������ڶ���
#define		COMMAND_17_0004_O_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x00c0//�ж�Һ��ģ���л����򣬷��Ŷ������ڶ���
#define		COMMAND_17_0005_O_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO3			0x00c1//Һ��ģ���л����򣬷��Ŷ�����������
#define		COMMAND_17_0006_O_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x00c2//�ж�Һ��ģ���л����򣬷��Ŷ�����������
#define		COMMAND_17_0007_O_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO4			0x00c3//Һ��ģ���л����򣬷��Ŷ�����������
#define		COMMAND_17_0008_O_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x00c4//�ж�Һ��ģ���л����򣬷��Ŷ�����������

//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		COMMAND_17_0001_O_1TANK_1GAS_IS_EXCHANGE_COOLER					0x00c5//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����

*/


//Һ��ģ��ͣ��
#define		COMMAND_17_0001_O_1TANK_1GAS_COOLER_POWER_OFF					0x00c6//Һ��ģ��ͣ��

//Һ��ģ��״̬����
#define		COMMAND_17_0001_O_1TANK_1GAS_COOLER_SET_NO1						0x0200
#define		COMMAND_17_0002_O_1TANK_1GAS_IS_COOLER_SET_NO1					0x0201
#define		COMMAND_17_0003_O_1TANK_1GAS_COOLER_SET_NO2						0x0202
#define		COMMAND_17_0004_O_1TANK_1GAS_IS_COOLER_SET_NO2					0x0203
#define		COMMAND_17_0005_O_1TANK_1GAS_COOLER_SET_NO3						0x0204
#define		COMMAND_17_0006_O_1TANK_1GAS_IS_COOLER_SET_NO3					0x0205
#define		COMMAND_17_0007_O_1TANK_1GAS_COOLER_SET_NO4						0x0206
#define		COMMAND_17_0008_O_1TANK_1GAS_IS_COOLER_SET_NO4					0x0207
#define		COMMAND_17_0009_O_1TANK_1GAS_COOLER_SET_NO5						0x0208
#define		COMMAND_17_0010_O_1TANK_1GAS_IS_COOLER_SET_NO5					0x0209
#define		COMMAND_17_0011_O_1TANK_1GAS_COOLER_SET_NO6						0x020a
#define		COMMAND_17_0012_O_1TANK_1GAS_IS_COOLER_SET_NO6					0x020b
#define		COMMAND_17_0013_O_1TANK_1GAS_COOLER_SET_NO7						0x020c
#define		COMMAND_17_0014_O_1TANK_1GAS_IS_COOLER_SET_NO7					0x020d
#define		COMMAND_17_0015_O_1TANK_1GAS_COOLER_SET_NO8						0x020e
#define		COMMAND_17_0016_O_1TANK_1GAS_IS_COOLER_SET_NO8					0x020f
#define		COMMAND_17_0017_O_1TANK_1GAS_COOLER_SET_NO9						0x0211
#define		COMMAND_17_0018_O_1TANK_1GAS_IS_COOLER_SET_NO9					0x0212
#define		COMMAND_17_0019_O_1TANK_1GAS_COOLER_SET_NO10					0x0213
#define		COMMAND_17_0020_O_1TANK_1GAS_IS_COOLER_SET_NO10					0x0214
#define		COMMAND_17_0021_O_1TANK_1GAS_COOLER_SET_NO11					0x0215
#define		COMMAND_17_0022_O_1TANK_1GAS_IS_COOLER_SET_NO11					0x0216
#define		COMMAND_17_0023_O_1TANK_1GAS_COOLER_SET_NO12					0x0217
#define		COMMAND_17_0024_O_1TANK_1GAS_IS_COOLER_SET_NO12					0x0218


//����ѹ�����ϵ�
#define		COMMAND_17_0001_O_1TANK_1GAS_COMPRESSOR_POWER_OFF				0x00c7//�����豸����ָ��

//�������������ϵ�
#define		COMMAND_17_0001_O_1TANK_1GAS_TGTHT530_POWER_OFF					0x00c8//�����豸����ָ��
#define		COMMAND_17_0002_O_1TANK_1GAS_TGTHT530_TIME_1MIN_START			0x00c9//��ʱ1min��ʱ��ʼ
#define		COMMAND_17_0003_O_1TANK_1GAS_TGTHT530_IS_TIME_1MIN				0x00ca//�жϼ�ʱ1min�Ƿ�

//------------------------------command---�������������----������ƿ����-----------------------------------

//������ƿ���ӷ���---��һ����ƿ
#define		COMMAND_17_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON				0x00cb//������ƿ���ӷ���
#define		COMMAND_17_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_ON			0x00cc//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---��һ����ƿ
#define		COMMAND_17_0001_O_1TANK_2GAS_GAS1_TIME_DELAY2_START				0x00cd//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_17_0002_O_1TANK_2GAS_GAS1_IS_TIME_DELAY2				0x00ce//�ж���ʱ�ȴ�time_delay2

//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define		COMMAND_17_0001_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO1				0x00cf//�ɼ���ƿѹ������һ��
#define		COMMAND_17_0002_O_1TANK_2GAS_GAS1_TIME_30S_START_NO1			0x00d0//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_17_0003_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO1				0x00d1//�ж϶�ʱ30s����һ��
#define		COMMAND_17_0004_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO2				0x00d2//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_17_0005_O_1TANK_2GAS_GAS1_TIME_30S_START_NO2			0x00d3//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_17_0006_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO2				0x00d4//�ж϶�ʱ30s���ڶ���
#define		COMMAND_17_0007_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO3				0x00d5//�ɼ���ƿѹ����������
#define		COMMAND_17_0008_O_1TANK_2GAS_GAS1_TIME_30S_START_NO3			0x00d6//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_17_0009_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO3				0x00d7//�ж϶�ʱ30s��������
#define		COMMAND_17_0010_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO4				0x00d8//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_17_0011_O_1TANK_2GAS_GAS1_TIME_30S_START_NO4			0x00d9//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_17_0012_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO4				0x00da//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_17_0013_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO5				0x00db//�ɼ���ƿѹ���������
#define		COMMAND_17_0014_O_1TANK_2GAS_GAS1_TIME_30S_START_NO5			0x00dc//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_17_0015_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO5				0x00dd//�ж϶�ʱ30s�������
#define		COMMAND_17_0016_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO6				0x00de//�ɼ���ƿѹ����������
#define		COMMAND_17_0017_O_1TANK_2GAS_GAS1_TIME_30S_START_NO6			0x00df//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_17_0018_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO6				0x00e0//�ж϶�ʱ30s��������
#define		COMMAND_17_0019_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO7				0x00e1//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_17_0020_O_1TANK_2GAS_GAS1_TIME_30S_START_NO7			0x00e2//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_17_0021_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO7				0x00e3//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_17_0022_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO8				0x00e4//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_17_0023_O_1TANK_2GAS_GAS1_TIME_30S_START_NO8			0x00e5//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_17_0024_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO8				0x00e6//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_17_0025_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO9				0x00e7//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_17_0026_O_1TANK_2GAS_GAS1_TIME_30S_START_NO9			0x00e8//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_17_0027_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO9				0x00e9//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_17_0028_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO10				0x00ea//�ɼ���ƿѹ������ʮ��
#define		COMMAND_17_0029_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE				0x00eb//ѹ���ж���ƿѹ���Ƿ�����


//�ж���ƿ�����Ƿ����---��һ����ƿ
#define		COMMAND_17_0001_O_1TANK_2GAS_GAS1_IS_COMP_GAS_OVER				0x00ec//�ж���ƿ�����Ƿ����


//��ȼ·��ƿ���ӷ���---��һ����ƿ
#define		COMMAND_17_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1			0x00ed//��ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_17_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1		0x00ee//�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_17_0003_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2			0x00ef//��ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_17_0004_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2		0x00f0//�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_17_0005_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3			0x00f1//��ȼ·��ƿ���ӷ��ţ�������
#define		COMMAND_17_0006_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3		0x00f2//�жϹ�ȼ·��ƿ���ӷ��ţ�������

//������ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_17_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON				0x00f3//������ƿ���ӷ���
#define		COMMAND_17_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_ON			0x00f4//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define		COMMAND_17_0001_O_1TANK_2GAS_GAS2_TIME_DELAY2_START				0x00f5//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_17_0002_O_1TANK_2GAS_GAS2_IS_TIME_DELAY2				0x00f6//�ж���ʱ�ȴ�time_delay2



//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define		COMMAND_17_0001_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO1				0x00f7//�ɼ���ƿѹ������һ��
#define		COMMAND_17_0002_O_1TANK_2GAS_GAS2_TIME_30S_START_NO1			0x00f8//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_17_0003_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO1				0x00f9//�ж϶�ʱ30s����һ��
#define		COMMAND_17_0004_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO2				0x00fa//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_17_0005_O_1TANK_2GAS_GAS2_TIME_30S_START_NO2			0x00fb//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_17_0006_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO2				0x00fc//�ж϶�ʱ30s���ڶ���
#define		COMMAND_17_0007_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO3				0x00fd//�ɼ���ƿѹ����������
#define		COMMAND_17_0008_O_1TANK_2GAS_GAS2_TIME_30S_START_NO3			0x00fe//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_17_0009_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO3				0x00ff//�ж϶�ʱ30s��������
#define		COMMAND_17_0010_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO4				0x0100//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_17_0011_O_1TANK_2GAS_GAS2_TIME_30S_START_NO4			0x0101//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_17_0012_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO4				0x0102//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_17_0013_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO5				0x0103//�ɼ���ƿѹ���������
#define		COMMAND_17_0014_O_1TANK_2GAS_GAS2_TIME_30S_START_NO5			0x0104//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_17_0015_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO5				0x0105//�ж϶�ʱ30s�������
#define		COMMAND_17_0016_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO6				0x0106//�ɼ���ƿѹ����������
#define		COMMAND_17_0017_O_1TANK_2GAS_GAS2_TIME_30S_START_NO6			0x0107//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_17_0018_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO6				0x0108//�ж϶�ʱ30s��������
#define		COMMAND_17_0019_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO7				0x0109//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_17_0020_O_1TANK_2GAS_GAS2_TIME_30S_START_NO7			0x010a//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_17_0021_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO7				0x010b//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_17_0022_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO8				0x010c//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_17_0023_O_1TANK_2GAS_GAS2_TIME_30S_START_NO8			0x010d//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_17_0024_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO8				0x010e//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_17_0025_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO9				0x010f//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_17_0026_O_1TANK_2GAS_GAS2_TIME_30S_START_NO9			0x0110//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_17_0027_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO9				0x0111//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_17_0028_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO10				0x0112//�ɼ���ƿѹ������ʮ��
#define		COMMAND_17_0029_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE				0x0113//ѹ���ж���ƿѹ���Ƿ�����

//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define		COMMAND_17_0001_O_1TANK_2GAS_GAS2_IS_COMP_GAS_OVER				0x0114//�ж���ƿ�����Ƿ����


//��ȼ·��ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_17_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1			0x0115//��ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_17_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1		0x0116//�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_17_0003_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2			0x0117//��ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_17_0004_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2		0x0118//�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_17_0005_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3			0x0119//��ȼ·��ƿ���ӷ��ţ�������
#define		COMMAND_17_0006_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3		0x011a//�жϹ�ȼ·��ƿ���ӷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define		COMMAND_17_0001_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO1	0x011b//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_17_0002_O_1TANK_2GAS_FIRST_TIME_12S_START_NO1		0x011c//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_17_0003_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO1			0x011d//�ж϶�ʱ12s����һ��
#define		COMMAND_17_0004_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO2	0x011e//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_17_0005_O_1TANK_2GAS_FIRST_TIME_12S_START_NO2		0x011f//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_17_0006_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO2			0x0120//�ж϶�ʱ12s���ڶ���
#define		COMMAND_17_0007_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO3	0x0121//�ɼ�ѹ��������ѹ����������
#define		COMMAND_17_0008_O_1TANK_2GAS_FIRST_TIME_12S_START_NO3		0x0122//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_17_0009_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO3			0x0123//�ж϶�ʱ12s��������
#define		COMMAND_17_0010_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO4	0x0124//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_17_0011_O_1TANK_2GAS_FIRST_IS_ISOLATION				0x0125//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//�ر�ȼѹ�������ڷ���
#define		COMMAND_17_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x0126//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1	0x0127//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x0128//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2	0x0129//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x012a//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_17_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3	0x012b//�жϹر�ȼѹ�������ڷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���
#define		COMMAND_17_0001_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO1	0x012c//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_17_0002_O_1TANK_2GAS_SECOND_TIME_12S_START_NO1		0x012d//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_17_0003_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO1			0x012e//�ж϶�ʱ12s����һ��
#define		COMMAND_17_0004_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO2	0x012f//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_17_0005_O_1TANK_2GAS_SECOND_TIME_12S_START_NO2		0x0130//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_17_0006_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO2			0x0131//�ж϶�ʱ12s���ڶ���
#define		COMMAND_17_0007_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO3	0x0132//�ɼ�ѹ��������ѹ����������
#define		COMMAND_17_0008_O_1TANK_2GAS_SECOND_TIME_12S_START_NO3		0x0133//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_17_0009_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO3			0x0134//�ж϶�ʱ12s��������
#define		COMMAND_17_0010_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO4	0x0135//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_17_0011_O_1TANK_2GAS_SECOND_IS_ISOLATION			0x0136//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//ȼѹ����ͣ��
#define		COMMAND_17_0001_O_1TANK_2GAS_COMPRESSOR_STOP					0x0137//�����豸����ָ�ѹ����ͣ��
#define		COMMAND_17_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START			0x0138//��ʱ1min��ʱ��ʼ
#define		COMMAND_17_0003_O_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN			0x0139//�ж�1min��ʱ


//�ж�ȼѹ����ͣ���Ƿ�����
#define		COMMAND_17_0001_O_1TANK_2GAS_COMPRESSOR_V_NO1					0x013a//�ɼ����ת�٣���һ��
#define		COMMAND_17_0002_O_1TANK_2GAS_COMPRESSOR_V_NO2					0x013b//�ɼ����ת�٣��ڶ���
#define		COMMAND_17_0003_O_1TANK_2GAS_COMPRESSOR_V_NO3					0x013c//�ɼ����ת�٣�������
#define		COMMAND_17_0004_O_1TANK_2GAS_COMPRESSOR_V_NO4					0x013d//�ɼ����ת�٣����Ĵ�
#define		COMMAND_17_0005_O_1TANK_2GAS_COMPRESSOR_V_NO5					0x013e//�ɼ����ת�٣������
#define		COMMAND_17_0006_O_1TANK_2GAS_COMPRESSOR_V_NO6					0x013f//�ɼ����ת�٣�������
#define		COMMAND_17_0007_O_1TANK_2GAS_COMPRESSOR_V_NO7					0x0140//�ɼ����ת�٣����ߴ�
#define		COMMAND_17_0008_O_1TANK_2GAS_COMPRESSOR_V_NO8					0x0141//�ɼ����ת�٣��ڰ˴�
#define		COMMAND_17_0009_O_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO1		0x0142//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_17_0010_O_1TANK_2GAS_TIME_12S_START						0x0143//��ʱ12s��ʱ��ʼ
#define		COMMAND_17_0011_O_1TANK_2GAS_IS_TIME_12S						0x0144//�ж϶�ʱ12s
#define		COMMAND_17_0012_O_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO2		0x0145//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_17_0013_O_1TANK_2GAS_IS_COMPRESSOR_STOP					0x0146//�ж�ȼѹ����ͣ���Ƿ�����

//��ȼѹ������·������
#define		COMMAND_17_0001_O_1TANK_2GAS_BYPATH_VALVE_ON					0x0147//��ȼѹ������·������
#define		COMMAND_17_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_ON					0x0148//�жϿ�ȼѹ������·������


//��ʱ�ȴ�time_bypath
#define		COMMAND_17_0001_O_1TANK_2GAS_TIME_BYPATH_START					0x0149//��ʱ�ȴ�time_bypath��ʱ����
#define		COMMAND_17_0002_O_1TANK_2GAS_IS_TIME_BYPATH						0x014a//�ж���ʱ�ȴ�time_bypath


//��ȼѹ������·������
#define		COMMAND_17_0001_O_1TANK_2GAS_BYPATH_VALVE_OFF					0x014b//��ȼѹ������·������
#define		COMMAND_17_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_OFF				0x014c//�жϹ�ȼѹ������·������

//�ر�ȼѹ�������ڷ���
#define		COMMAND_17_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1			0x014d//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x014e//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2			0x014f//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x0150//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3			0x0151//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_17_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x0152//�жϹر�ȼѹ�������ڷ��ţ�������

//�ر�ȼѹ�������ڷ���
#define		COMMAND_17_0001_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x0153//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0002_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1		0x0154//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_17_0003_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0155//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0004_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0156//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_17_0005_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x0157//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_17_0006_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3		0x0158//�жϹر�ȼѹ�������ڷ��ţ�������


//�ؽ������ѹ��·���ӷ���
#define		COMMAND_17_0001_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO1				0x0159//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_17_0002_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO1			0x015a//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_17_0003_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO2				0x015b//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_17_0004_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO2			0x015c//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_17_0005_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO3				0x015d//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_17_0006_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO3			0x015e//�жϹؽ������ѹ��·���ӷ��ţ�������


//����ȼ����״̬��
#define		COMMAND_17_0001_O_1TANK_2GAS_SET_STATE_GOOD						0x015f//����ȼ����״̬��


//�ж�ѹ�����¶��Ƿ�����
#define		COMMAND_17_0001_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE			0x0160//�ж�ѹ�����¶��Ƿ�����

//��ʱ�ȴ�time_delay3
#define		COMMAND_17_0001_O_1TANK_2GAS_TIME_DELAY3_START					0x0161//��ʱ�ȴ�time_delay3��ʱ��ʼ
#define		COMMAND_17_0002_O_1TANK_2GAS_IS_TIME_DELAY3						0x0162//�ж���ʱ�ȴ�time_delay3

/*

//����Һ��ģ���л�����
#define		COMMAND_17_0001_O_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO1			0x0163//Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_17_0002_O_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x0164//�ж�Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_17_0003_O_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO2			0x0165//Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_17_0004_O_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x0166//�ж�Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_17_0005_O_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO3			0x0167//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_17_0006_O_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x0168//�ж�Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_17_0007_O_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO4			0x0169//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_17_0008_O_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x016a//�ж�Һ��ģ���л�����,���Ŷ�����������

//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		COMMAND_17_0001_O_1TANK_2GAS_IS_EXCHANGE_COOLER					0x016b//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����

*/


//Һ��ģ��ͣ��
#define		COMMAND_17_0001_O_1TANK_2GAS_COOLER_POWER_OFF					0x016c//Һ��ģ��ͣ��

//Һ��ģ��״̬����
#define		COMMAND_17_0001_O_1TANK_2GAS_COOLER_SET_NO1						0x0219
#define		COMMAND_17_0002_O_1TANK_2GAS_IS_COOLER_SET_NO1					0x021a
#define		COMMAND_17_0003_O_1TANK_2GAS_COOLER_SET_NO2						0x021b
#define		COMMAND_17_0004_O_1TANK_2GAS_IS_COOLER_SET_NO2					0x021c
#define		COMMAND_17_0005_O_1TANK_2GAS_COOLER_SET_NO3						0x021d
#define		COMMAND_17_0006_O_1TANK_2GAS_IS_COOLER_SET_NO3					0x021e
#define		COMMAND_17_0007_O_1TANK_2GAS_COOLER_SET_NO4						0x021f
#define		COMMAND_17_0008_O_1TANK_2GAS_IS_COOLER_SET_NO4					0x0220
#define		COMMAND_17_0009_O_1TANK_2GAS_COOLER_SET_NO5						0x0221
#define		COMMAND_17_0010_O_1TANK_2GAS_IS_COOLER_SET_NO5					0x0222
#define		COMMAND_17_0011_O_1TANK_2GAS_COOLER_SET_NO6						0x0223
#define		COMMAND_17_0012_O_1TANK_2GAS_IS_COOLER_SET_NO6					0x0224
#define		COMMAND_17_0013_O_1TANK_2GAS_COOLER_SET_NO7						0x0225
#define		COMMAND_17_0014_O_1TANK_2GAS_IS_COOLER_SET_NO7					0x0226
#define		COMMAND_17_0015_O_1TANK_2GAS_COOLER_SET_NO8						0x0227
#define		COMMAND_17_0016_O_1TANK_2GAS_IS_COOLER_SET_NO8					0x0228
#define		COMMAND_17_0017_O_1TANK_2GAS_COOLER_SET_NO9						0x0229
#define		COMMAND_17_0018_O_1TANK_2GAS_IS_COOLER_SET_NO9					0x022a
#define		COMMAND_17_0019_O_1TANK_2GAS_COOLER_SET_NO10					0x022b
#define		COMMAND_17_0020_O_1TANK_2GAS_IS_COOLER_SET_NO10					0x022c
#define		COMMAND_17_0021_O_1TANK_2GAS_COOLER_SET_NO11					0x022d
#define		COMMAND_17_0022_O_1TANK_2GAS_IS_COOLER_SET_NO11					0x022e
#define		COMMAND_17_0023_O_1TANK_2GAS_COOLER_SET_NO12					0x022f
#define		COMMAND_17_0024_O_1TANK_2GAS_IS_COOLER_SET_NO12					0x0230

//����ѹ�����ϵ�
#define		COMMAND_17_0001_O_1TANK_2GAS_COMPRESSOR_POWER_OFF				0x016d//�����豸����ָ��

//�������������ϵ�
#define		COMMAND_17_0001_O_1TANK_2GAS_TGTHT530_POWER_OFF					0x016e//�����豸����ָ��
#define		COMMAND_17_0002_O_1TANK_2GAS_TGTHT530_TIME_1MIN_START			0x016f//��ʱ1min��ʱ��ʼ
#define		COMMAND_17_0003_O_1TANK_2GAS_TGTHT530_IS_TIME_1MIN				0x0170//�жϼ�ʱ1min�Ƿ�


//------------------------��������---------------------------------------------------------

void TGTHT510_supply_stage17_comp_O_main(void);

//-------------------------------------------------��ʼ���ý׶�----------------------------------------------------

uint16 TGTHT510_supply_stage17_comp_O_init_step_start_cooler(void);
uint16 TGTHT510_supply_stage17_comp_O_init_step_is_cooler_work(void);
uint16 TGTHT510_supply_stage17_comp_O_init_step_time_delay(void);
uint16 TGTHT510_supply_stage17_comp_O_init_step_is_compressor_temperature(void);
uint16 TGTHT510_supply_stage17_comp_O_init_step_TGTHT530_power_on(void);
uint16 TGTHT510_supply_stage17_comp_O_init_step_compressor_power_on(void);
uint16 TGTHT510_supply_stage17_comp_O_init_step_isolation(void);

//-------------------------------------------------һ���������----------------------------------------------------
uint16 TGTHT510_supply_stage17_comp_O_1tank_step_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_step_is_in_tank_valve_on_pressure(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_step_in_compressor_valve_on(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_step_time_delay1(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_step_is_in_compressor_pressure(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_step_compressor_start(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_step_is_out_compressor_pressure(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_step_out_compressor_valve_on(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_step_number_comp_gas(void);

//-----------------------------------һ�����������һ����ƿ����----------------------------------------------------
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_time_delay2(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_is_comp_over(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_is_compressor_temperature(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_time_delay3(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_cooler_set(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_1gas_step_TGTHT530_power_off(void);

//-----------------------------------һ�����������������ƿ����----------------------------------------------------
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_gas1_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_gas1_step_time_delay2(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_gas1_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_gas1_step_is_comp_over(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_gas1_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_gas2_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_gas2_step_time_delay2(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_gas2_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_gas2_step_is_comp_over(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_gas2_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_is_compressor_temperature(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_time_delay3(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_cooler_set(void);

uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage17_comp_O_1tank_2gas_step_TGTHT530_power_off(void);

//---------------------------------------------------------ͨ�ú���------------------------------------------------

#endif


 
 
 
