/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ���������������������ͷ�ļ�
  ******************************************************************************
  */
 
#ifndef __supply_stage_15_flow_o_h
#define __supply_stage_15_flow_o_h
 

/*�����ṹ������--------------------------------------------------------------*/

/*�궨��---------------------------------------------------------------------------*/

//����step----------------------------------------------------------------------

#define 	STEP_15_O_FLOW_TANK_NUMBER						0x0001//�жϲ�����������������

//---------------------һ��ȼ���䲹������---------------------------------------

#define 	STEP_15_O_1TANK_IS_HYCT_GOOD					0x0002//�жϻ�����ѹ״̬��
#define 	STEP_15_O_1TANK_INTERFACE_VALVE_ON				0x0003//���������Ͻ�������
#define 	STEP_15_O_1TANK_IS_INTERFACE_VALVE_ON			0x0004//ͨ��ѹ���жϽ������Ͻ������ſ����Ƿ�����
#define 	STEP_15_O_1TANK_MIDDLE_VALVE_ON					0x0005//��ȼ���ӽӿ��м䷧��
#define 	STEP_15_O_1TANK_DELAY1							0x0006//��ʱ�ȴ�
#define 	STEP_15_O_1TANK_IS_PIPE_PRESSURE				0x0007//ͨ��ѹ���ж�ȼ���ӽӿڹ�·ѹ���Ƿ��ȶ�
#define 	STEP_15_O_1TANK_IN_TANK_VALVE_ON				0x0008//�������䲹��Һ·����
#define 	STEP_15_O_1TANK_IS_FLOW_CORRECT_V				0x0009//ͨ�����������жϲ��ӹ����Ƿ�����
#define 	STEP_15_O_1TANK_IS_FLOW_OVER					0x000a//�жϲ����Ƿ�λ
#define 	STEP_15_O_1TANK_SET_FLOW_GOOD					0x000b//���ò��ӵ�λ��Ϣ�����ͻ���
#define 	STEP_15_O_1TANK_IN_TANK_VALVE_OFF				0x000c//�ؽ����䲹��Һ·����
#define 	STEP_15_O_1TANK_IS_IN_TANK_VALVE_OFF			0x000d//ͨ��ѹ���ж����䷧�Źر��Ƿ�����
#define 	STEP_15_O_1TANK_IS_NEED_FLOW_THIRD				0x000e//�ж��Ƿ���Ե����������������

//*********����Ե���������������ӣ��򱾽׶γ�����������򱾽׶μ���************

#define 	STEP_15_O_1TANK_PIPE_DEAL						0x000f//�ܱչ�·�������

//---------------------����ȼ���䲹������---------------------------------------

#define 	STEP_15_O_2TANK_IS_HYCT_GOOD					0x0010//�жϻ�����ѹ״̬��
#define 	STEP_15_O_2TANK_INTERFACE_VALVE_ON				0x0011//���������Ͻ�������
#define 	STEP_15_O_2TANK_IS_INTERFACE_VALVE_ON			0x0012//ͨ��ѹ���жϽ������Ͻ������ſ����Ƿ�����
#define 	STEP_15_O_2TANK_MIDDLE_VALVE_ON					0x0013//��ȼ���ӽӿ��м䷧��
#define 	STEP_15_O_2TANK_DELAY1							0x0014//��ʱ�ȴ�
#define 	STEP_15_O_2TANK_IS_PIPE_PRESSURE				0x0015//ͨ��ѹ���ж�ȼ���ӽӿڹ�·ѹ���Ƿ��ȶ�
#define 	STEP_15_O_2TANK_TANK1_IN_TANK_VALVE_ON			0x0016//�������䲹��Һ·���ţ���һ������
#define 	STEP_15_O_2TANK_TANK1_IS_FLOW_CORRECT_V			0x0017//ͨ�����������жϲ��ӹ����Ƿ���������һ������
#define 	STEP_15_O_2TANK_TANK1_IS_FLOW_OVER				0x0018//�жϲ����Ƿ�λ����һ������
#define 	STEP_15_O_2TANK_TANK1_IN_TANK_VALVE_OFF			0x0019//�ؽ����䲹��Һ·���ţ���һ������
#define 	STEP_15_O_2TANK_TANK1_IS_IN_TANK_VALVE_OFF		0x001a//ͨ��ѹ���ж����䷧�Źر��Ƿ���������һ������

#define 	STEP_15_O_2TANK_TANK2_IN_TANK_VALVE_ON			0x001b//�������䲹��Һ·���ţ��ڶ�������
#define 	STEP_15_O_2TANK_TANK2_IS_FLOW_CORRECT_V			0x001c//ͨ�����������жϲ��ӹ����Ƿ��������ڶ�������
#define 	STEP_15_O_2TANK_TANK2_IS_FLOW_OVER				0x001d//�жϲ����Ƿ�λ���ڶ�������
#define 	STEP_15_O_2TANK_SET_FLOW_GOOD					0x001e//���ò��ӵ�λ��Ϣ�����ͻ���
#define 	STEP_15_O_2TANK_TANK2_IN_TANK_VALVE_OFF			0x001f//�ؽ����䲹��Һ·���ţ��ڶ�������
#define 	STEP_15_O_2TANK_TANK2_IS_IN_TANK_VALVE_OFF		0x0020//ͨ��ѹ���ж����䷧�Źر��Ƿ��������ڶ�������

#define 	STEP_15_O_2TANK_IS_NEED_FLOW_THIRD				0x0021//�ж��Ƿ���Ե����������������

//*********����Ե���������������ӣ��򱾽׶γ�����������򱾽׶μ���************

#define 	STEP_15_O_2TANK_PIPE_DEAL						0x0023//�ܱչ�·�������


//����command-------------------------------------------------------------------

//�жϲ�����������������
#define		COMMAND_15_0001_O_FLOW_TANK_NUMBER				0x0001

//---------------------һ��ȼ���䲹������---------------------------------------

//�жϻ�����ѹ״̬��
#define		COMMAND_15_0001_O_1TANK_IS_HYCT_GOOD			0x0002

//���������Ͻ�������
#define		COMMAND_15_0001_O_1TANK_INTERFACE_VALVE_ON		0x0003//���������Ͻ�������
#define		COMMAND_15_0002_O_1TANK_IS_INTERFACE_VALVE_ON	0x0004//�жϷ��ſ����Ƿ�����

//ͨ��ѹ���жϽ������Ͻ������ſ����Ƿ�����
#define		COMMAND_15_0001_O_1TANK_INTERFACE_VALVE_ON_P	0x0005

//��ȼ���ӽӿ��м䷧��
#define		COMMAND_15_0001_O_1TANK_MIDDLE_VALVE_ON			0x0006//��ȼ���ӽӿ��м䷧��
#define		COMMAND_15_0002_O_1TANK_IS_MIDDLE_VALVE_ON		0x0007//�жϷ��ſ����Ƿ�����

//��ʱ�ȴ�
#define		COMMAND_15_0001_O_1TANK_DELAY1_START			0x0008//��ʱ�ȴ���ʱ��ʼ
#define		COMMAND_15_0002_O_1TANK_IS_DELAY1				0x0009//�ж���ʱ�ȴ��Ƿ�

//ͨ��ѹ���ж�ȼ���ӽӿڹ�·ѹ���Ƿ��ȶ�
#define		COMMAND_15_0001_O_1TANK_PIPE_PRESSURE_NO1		0x000a//�ɼ���·ѹ������һ��
#define		COMMAND_15_0002_O_1TANK_5SEC_START_NO1			0x000b//5s��ʱ��ʼ
#define		COMMAND_15_0003_O_1TANK_IS_5SEC_NO1				0x000c//�ж�5s��ʱ�Ƿ����
#define		COMMAND_15_0004_O_1TANK_PIPE_PRESSURE_NO2		0x000d//�ɼ���·ѹ�����ڶ���
#define		COMMAND_15_0005_O_1TANK_5SEC_START_NO2			0x000e//5s��ʱ��ʼ
#define		COMMAND_15_0006_O_1TANK_IS_5SEC_NO2				0x000f//�ж�5s��ʱ�Ƿ����
#define		COMMAND_15_0007_O_1TANK_PIPE_PRESSURE_NO3		0x0010//�ɼ���·ѹ����������
#define		COMMAND_15_0008_O_1TANK_5SEC_START_NO3			0x0011//5s��ʱ��ʼ
#define		COMMAND_15_0009_O_1TANK_IS_5SEC_NO3				0x0012//�ж�5s��ʱ�Ƿ����
#define		COMMAND_15_0010_O_1TANK_PIPE_PRESSURE_NO4		0x0013//�ɼ���·ѹ�������Ĵ�
#define		COMMAND_15_0011_O_1TANK_5SEC_START_NO4			0x0014//5s��ʱ��ʼ
#define		COMMAND_15_0012_O_1TANK_IS_5SEC_NO4				0x0015//�ж�5s��ʱ�Ƿ����
#define		COMMAND_15_0013_O_1TANK_PIPE_PRESSURE_NO5		0x0016//�ɼ���·ѹ���������
#define		COMMAND_15_0014_O_1TANK_5SEC_START_NO5			0x0017//5s��ʱ��ʼ
#define		COMMAND_15_0015_O_1TANK_IS_5SEC_NO5				0x0018//�ж�5s��ʱ�Ƿ����
#define		COMMAND_15_0016_O_1TANK_PIPE_PRESSURE_NO6		0x0019//�ɼ���·ѹ����������
#define		COMMAND_15_0017_O_1TANK_5SEC_START_NO6			0x001a//5s��ʱ��ʼ
#define		COMMAND_15_0018_O_1TANK_IS_5SEC_NO6				0x001b//�ж�5s��ʱ�Ƿ����
#define		COMMAND_15_0019_O_1TANK_PIPE_PRESSURE_NO7		0x001c//�ɼ���·ѹ�������ߴ�
#define		COMMAND_15_0020_O_1TANK_IS_PIPE_PRESSURE		0x001d//�жϹ�·ѹ���Ƿ��ȶ�

//�������䲹��Һ·����
#define		COMMAND_15_0001_O_1TANK_IN_TANK_VALVE_ON		0x001e
#define		COMMAND_15_0002_O_1TANK_IS_IN_TANK_VALVE_ON		0x001f

//ͨ�����������жϲ��ӹ����Ƿ�����
#define		COMMAND_15_0001_O_1TANK_HTT_NO1					0x0020
#define		COMMAND_15_0002_O_1TANK_1MIN_START_NO1			0x0021
#define		COMMAND_15_0003_O_1TANK_IS_1MIN_NO1				0x0022
#define		COMMAND_15_0004_O_1TANK_HTT_NO2					0x0023
#define		COMMAND_15_0005_O_1TANK_1MIN_START_NO2			0x0024
#define		COMMAND_15_0006_O_1TANK_IS_1MIN_NO2				0x0025
#define		COMMAND_15_0007_O_1TANK_HTT_NO3					0x0026
#define		COMMAND_15_0008_O_1TANK_IS_FLOW_CORRECT			0x0027

//�жϲ����Ƿ�λ
#define		COMMAND_15_0001_O_1TANK_IS_FLOW_OVER_NO1		0x0028
#define		COMMAND_15_0002_O_1TANK_IS_FLOW_OVER_NO2		0x0029
#define		COMMAND_15_0003_O_1TANK_IS_FLOW_OVER_NO3		0x002a

//���ò��ӵ�λ��Ϣ�����ͻ���
#define		COMMAND_15_0001_O_1TANK_SET_FLOW_GOOD			0x002b


//�ؽ����䲹��Һ·����
#define		COMMAND_15_0001_O_1TANK_IN_TANK_VALVE_OFF		0x002c
#define		COMMAND_15_0002_O_1TANK_IS_IN_TANK_VALVE_OFF	0x002d

//ͨ��ѹ���ж����䷧�Źر��Ƿ�����
#define		COMMAND_15_0001_O_1TANK_IS_PRESSURE				0x002e

//�ж��Ƿ���Ե����������������
#define		COMMAND_15_0001_O_1TANK_IS_NEED_FLOW_THIRD		0x002f

//�ܱչ�·�������
#define		COMMAND_15_0001_O_1TANK_VALVE_OFF_NO1			0x0030
#define		COMMAND_15_0002_O_1TANK_IS_VALVE_OFF_NO1		0x0031
#define		COMMAND_15_0003_O_1TANK_VALVE_ON_NO2			0x0032
#define		COMMAND_15_0004_O_1TANK_IS_VALVE_ON_NO2			0x0033
#define		COMMAND_15_0005_O_1TANK_5SEC_START				0x0034
#define		COMMAND_15_0006_O_1TANK_IS_5SEC					0x0035
#define		COMMAND_15_0007_O_1TANK_VALVE_OFF_NO3			0x0036
#define		COMMAND_15_0008_O_1TANK_IS_VALVE_OFF_NO3		0x0037
#define		COMMAND_15_0009_O_1TANK_VALVE_OFF_NO4			0x0038
#define		COMMAND_15_0010_O_1TANK_IS_VALVE_OFF_NO4		0x0039
#define		COMMAND_15_0011_O_1TANK_VALVE_OFF_NO5			0x003a
#define		COMMAND_15_0012_O_1TANK_IS_VALVE_OFF_NO5		0x003b

#define		COMMAND_15_0013_O_1TANK_10SEC_START				0x003c
#define		COMMAND_15_0014_O_1TANK_IS_10SEC				0x003d

#define		COMMAND_15_0015_O_1TANK_PIPE_GET_NO1			0x003e//�ɼ�ѹ��
#define		COMMAND_15_0016_O_1TANK_PIPE_5SEC_START_NO1		0x003f//5s��ʱ��ʼ
#define		COMMAND_15_0017_O_1TANK_PIPE_IS_5SEC_NO1		0x0040//�ж�5s��ʱ�Ƿ����

#define		COMMAND_15_0018_O_1TANK_PIPE_GET_NO2			0x0041//�ɼ�ѹ��
#define		COMMAND_15_0019_O_1TANK_PIPE_5SEC_START_NO2		0x0042//5s��ʱ��ʼ
#define		COMMAND_15_0020_O_1TANK_PIPE_IS_5SEC_NO2		0x0043//�ж�5s��ʱ�Ƿ����

#define		COMMAND_15_0021_O_1TANK_PIPE_GET_NO3			0x0044//�ɼ�ѹ��
#define		COMMAND_15_0022_O_1TANK_PIPE_5SEC_START_NO3		0x0045//5s��ʱ��ʼ
#define		COMMAND_15_0023_O_1TANK_PIPE_IS_5SEC_NO3		0x0046//�ж�5s��ʱ�Ƿ����

#define		COMMAND_15_0024_O_1TANK_PIPE_GET_NO4			0x0047//�ɼ�ѹ��
#define		COMMAND_15_0025_O_1TANK_PIPE_5SEC_START_NO4		0x0048//5s��ʱ��ʼ
#define		COMMAND_15_0026_O_1TANK_PIPE_IS_5SEC_NO4		0x0049//�ж�5s��ʱ�Ƿ����

#define		COMMAND_15_0027_O_1TANK_PIPE_GET_NO5			0x004a//�ɼ�ѹ��
#define		COMMAND_15_0028_O_1TANK_PIPE_5SEC_START_NO5		0x004b//5s��ʱ��ʼ
#define		COMMAND_15_0029_O_1TANK_PIPE_IS_5SEC_NO5		0x004c//�ж�5s��ʱ�Ƿ����

#define		COMMAND_15_0030_O_1TANK_PIPE_GET_NO6			0x004d//�ɼ�ѹ��
#define		COMMAND_15_0031_O_1TANK_PIPE_5SEC_START_NO6		0x004e//5s��ʱ��ʼ
#define		COMMAND_15_0032_O_1TANK_PIPE_IS_5SEC_NO6		0x004f//�ж�5s��ʱ�Ƿ����

#define		COMMAND_15_0033_O_1TANK_PIPE_GET_NO7			0x0050//�ɼ�ѹ��
#define		COMMAND_15_0034_O_1TANK_PIPE_DEAL_PRESSURE		0x0051//�жϹ�·ѹ���Ƿ��ȶ�


//---------------------����ȼ���䲹������---------------------------------------

//�жϻ�����ѹ״̬��
#define		COMMAND_15_0001_O_2TANK_IS_HYCT_GOOD			0x0052

//���������Ͻ�������
#define		COMMAND_15_0001_O_2TANK_INTERFACE_VALVE_ON		0x0053//���������Ͻ�������
#define		COMMAND_15_0002_O_2TANK_IS_INTERFACE_VALVE_ON	0x0054//�жϷ��ſ����Ƿ�����

//ͨ��ѹ���жϽ������Ͻ������ſ����Ƿ�����
#define		COMMAND_15_0001_O_2TANK_INTERFACE_VALVE_ON_P	0x0055

//��ȼ���ӽӿ��м䷧��
#define		COMMAND_15_0001_O_2TANK_MIDDLE_VALVE_ON			0x0056//��ȼ���ӽӿ��м䷧��
#define		COMMAND_15_0002_O_2TANK_IS_MIDDLE_VALVE_ON		0x0057//�жϷ��ſ����Ƿ�����

//��ʱ�ȴ�
#define		COMMAND_15_0001_O_2TANK_DELAY1_START			0x0058//��ʱ�ȴ���ʱ��ʼ
#define		COMMAND_15_0002_O_2TANK_IS_DELAY1				0x0059//�ж���ʱ�ȴ��Ƿ�

//ͨ��ѹ���ж�ȼ���ӽӿڹ�·ѹ���Ƿ��ȶ�
#define		COMMAND_15_0001_O_2TANK_PIPE_PRESSURE_NO1		0x005a//�ɼ���·ѹ������һ��
#define		COMMAND_15_0002_O_2TANK_5SEC_START_NO1			0x005b//5s��ʱ��ʼ
#define		COMMAND_15_0003_O_2TANK_IS_5SEC_NO1				0x005c//�ж�5s��ʱ�Ƿ����
#define		COMMAND_15_0004_O_2TANK_PIPE_PRESSURE_NO2		0x005d//�ɼ���·ѹ�����ڶ���
#define		COMMAND_15_0005_O_2TANK_5SEC_START_NO2			0x005e//5s��ʱ��ʼ
#define		COMMAND_15_0006_O_2TANK_IS_5SEC_NO2				0x005f//�ж�5s��ʱ�Ƿ����
#define		COMMAND_15_0007_O_2TANK_PIPE_PRESSURE_NO3		0x0060//�ɼ���·ѹ����������
#define		COMMAND_15_0008_O_2TANK_5SEC_START_NO3			0x0061//5s��ʱ��ʼ
#define		COMMAND_15_0009_O_2TANK_IS_5SEC_NO3				0x0062//�ж�5s��ʱ�Ƿ����
#define		COMMAND_15_0010_O_2TANK_PIPE_PRESSURE_NO4		0x0063//�ɼ���·ѹ�������Ĵ�
#define		COMMAND_15_0011_O_2TANK_5SEC_START_NO4			0x0064//5s��ʱ��ʼ
#define		COMMAND_15_0012_O_2TANK_IS_5SEC_NO4				0x0065//�ж�5s��ʱ�Ƿ����
#define		COMMAND_15_0013_O_2TANK_PIPE_PRESSURE_NO5		0x0066//�ɼ���·ѹ���������
#define		COMMAND_15_0014_O_2TANK_5SEC_START_NO5			0x0067//5s��ʱ��ʼ
#define		COMMAND_15_0015_O_2TANK_IS_5SEC_NO5				0x0068//�ж�5s��ʱ�Ƿ����
#define		COMMAND_15_0016_O_2TANK_PIPE_PRESSURE_NO6		0x0069//�ɼ���·ѹ����������
#define		COMMAND_15_0017_O_2TANK_5SEC_START_NO6			0x006a//5s��ʱ��ʼ
#define		COMMAND_15_0018_O_2TANK_IS_5SEC_NO6				0x006b//�ж�5s��ʱ�Ƿ����
#define		COMMAND_15_0019_O_2TANK_PIPE_PRESSURE_NO7		0x006c//�ɼ���·ѹ�������ߴ�
#define		COMMAND_15_0020_O_2TANK_IS_PIPE_PRESSURE		0x006d//�жϹ�·ѹ���Ƿ��ȶ�


//***************��һ������*******************************************************

//�������䲹��Һ·����
#define		COMMAND_15_0001_O_2TANK_TANK1_IN_TANK_VALVE_ON			0x006e
#define		COMMAND_15_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON		0x006f

//ͨ�����������жϲ��ӹ����Ƿ�����
#define		COMMAND_15_0001_O_2TANK_TANK1_HTT_NO1					0x0070
#define		COMMAND_15_0002_O_2TANK_TANK1_1MIN_START_NO1			0x0071
#define		COMMAND_15_0003_O_2TANK_TANK1_IS_1MIN_NO1				0x0072
#define		COMMAND_15_0004_O_2TANK_TANK1_HTT_NO2					0x0073
#define		COMMAND_15_0005_O_2TANK_TANK1_1MIN_START_NO2			0x0074
#define		COMMAND_15_0006_O_2TANK_TANK1_IS_1MIN_NO2				0x0075
#define		COMMAND_15_0007_O_2TANK_TANK1_HTT_NO3					0x0076
#define		COMMAND_15_0008_O_2TANK_TANK1_IS_FLOW_CORRECT			0x0077

//�жϲ����Ƿ�λ
#define		COMMAND_15_0001_O_2TANK_TANK1_IS_FLOW_OVER_NO1			0x0078
#define		COMMAND_15_0002_O_2TANK_TANK1_IS_FLOW_OVER_NO2			0x0079
#define		COMMAND_15_0003_O_2TANK_TANK1_IS_FLOW_OVER_NO3			0x007a

//�ؽ����䲹��Һ·����
#define		COMMAND_15_0001_O_2TANK_TANK1_IN_TANK_VALVE_OFF			0x007b
#define		COMMAND_15_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_OFF		0x007c

//ͨ��ѹ���ж����䷧�Źر��Ƿ�����
#define		COMMAND_15_0001_O_2TANK_TANK1_IS_PRESSURE				0x007d


//***************�ڶ�������*******************************************************

//�������䲹��Һ·����
#define		COMMAND_15_0001_O_2TANK_TANK2_IN_TANK_VALVE_ON			0x007e
#define		COMMAND_15_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON		0x007f

//ͨ�����������жϲ��ӹ����Ƿ�����
#define		COMMAND_15_0001_O_2TANK_TANK2_HTT_NO1					0x0080
#define		COMMAND_15_0002_O_2TANK_TANK2_1MIN_START_NO1			0x0081
#define		COMMAND_15_0003_O_2TANK_TANK2_IS_1MIN_NO1				0x0082
#define		COMMAND_15_0004_O_2TANK_TANK2_HTT_NO2					0x0083
#define		COMMAND_15_0005_O_2TANK_TANK2_1MIN_START_NO2			0x0084
#define		COMMAND_15_0006_O_2TANK_TANK2_IS_1MIN_NO2				0x0085
#define		COMMAND_15_0007_O_2TANK_TANK2_HTT_NO3					0x0086
#define		COMMAND_15_0008_O_2TANK_TANK2_IS_FLOW_CORRECT			0x0087

//�жϲ����Ƿ�λ
#define		COMMAND_15_0001_O_2TANK_TANK2_IS_FLOW_OVER_NO1			0x0088
#define		COMMAND_15_0002_O_2TANK_TANK2_IS_FLOW_OVER_NO2			0x0089
#define		COMMAND_15_0003_O_2TANK_TANK2_IS_FLOW_OVER_NO3			0x008a

//���ò��ӵ�λ��Ϣ�����ͻ���
#define		COMMAND_15_0001_O_2TANK_SET_FLOW_GOOD					0x008b

//�ؽ����䲹��Һ·����
#define		COMMAND_15_0001_O_2TANK_TANK2_IN_TANK_VALVE_OFF			0x008c
#define		COMMAND_15_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_OFF		0x008d

//ͨ��ѹ���ж����䷧�Źر��Ƿ�����
#define		COMMAND_15_0001_O_2TANK_TANK2_IS_PRESSURE				0x008e

//�ж��Ƿ���Ե����������������
#define		COMMAND_15_0001_O_2TANK_IS_NEED_FLOW_THIRD		0x008f

//�ܱչ�·�������
#define		COMMAND_15_0001_O_2TANK_VALVE_OFF_NO1			0x0090
#define		COMMAND_15_0002_O_2TANK_IS_VALVE_OFF_NO1		0x0091
#define		COMMAND_15_0003_O_2TANK_VALVE_ON_NO2			0x0092
#define		COMMAND_15_0004_O_2TANK_IS_VALVE_ON_NO2			0x0093
#define		COMMAND_15_0005_O_2TANK_5SEC_START				0x0094
#define		COMMAND_15_0006_O_2TANK_IS_5SEC					0x0095
#define		COMMAND_15_0007_O_2TANK_VALVE_OFF_NO3			0x0096
#define		COMMAND_15_0008_O_2TANK_IS_VALVE_OFF_NO3		0x0097
#define		COMMAND_15_0009_O_2TANK_VALVE_OFF_NO4			0x0098
#define		COMMAND_15_0010_O_2TANK_IS_VALVE_OFF_NO4		0x0099
#define		COMMAND_15_0011_O_2TANK_VALVE_OFF_NO5			0x009a
#define		COMMAND_15_0012_O_2TANK_IS_VALVE_OFF_NO5		0x009b

#define		COMMAND_15_0013_O_2TANK_10SEC_START				0x009c
#define		COMMAND_15_0014_O_2TANK_IS_10SEC				0x009d

#define		COMMAND_15_0015_O_2TANK_PIPE_GET_NO1			0x009e//�ɼ�ѹ��
#define		COMMAND_15_0016_O_2TANK_PIPE_5SEC_START_NO1		0x009f//5s��ʱ��ʼ
#define		COMMAND_15_0017_O_2TANK_PIPE_IS_5SEC_NO1		0x00a0//�ж�5s��ʱ�Ƿ����

#define		COMMAND_15_0018_O_2TANK_PIPE_GET_NO2			0x00a1//�ɼ�ѹ��
#define		COMMAND_15_0019_O_2TANK_PIPE_5SEC_START_NO2		0x00a2//5s��ʱ��ʼ
#define		COMMAND_15_0020_O_2TANK_PIPE_IS_5SEC_NO2		0x00a3//�ж�5s��ʱ�Ƿ����

#define		COMMAND_15_0021_O_2TANK_PIPE_GET_NO3			0x00a4//�ɼ�ѹ��
#define		COMMAND_15_0022_O_2TANK_PIPE_5SEC_START_NO3		0x00a5//5s��ʱ��ʼ
#define		COMMAND_15_0023_O_2TANK_PIPE_IS_5SEC_NO3		0x00a6//�ж�5s��ʱ�Ƿ����

#define		COMMAND_15_0024_O_2TANK_PIPE_GET_NO4			0x00a7//�ɼ�ѹ��
#define		COMMAND_15_0025_O_2TANK_PIPE_5SEC_START_NO4		0x00a8//5s��ʱ��ʼ
#define		COMMAND_15_0026_O_2TANK_PIPE_IS_5SEC_NO4		0x00a9//�ж�5s��ʱ�Ƿ����

#define		COMMAND_15_0027_O_2TANK_PIPE_GET_NO5			0x00aa//�ɼ�ѹ��
#define		COMMAND_15_0028_O_2TANK_PIPE_5SEC_START_NO5		0x00ab//5s��ʱ��ʼ
#define		COMMAND_15_0029_O_2TANK_PIPE_IS_5SEC_NO5		0x00ac//�ж�5s��ʱ�Ƿ����

#define		COMMAND_15_0030_O_2TANK_PIPE_GET_NO6			0x00ad//�ɼ�ѹ��
#define		COMMAND_15_0031_O_2TANK_PIPE_5SEC_START_NO6		0x00ae//5s��ʱ��ʼ
#define		COMMAND_15_0032_O_2TANK_PIPE_IS_5SEC_NO6		0x00af//�ж�5s��ʱ�Ƿ����

#define		COMMAND_15_0033_O_2TANK_PIPE_GET_NO7			0x00b0//�ɼ�ѹ��
#define		COMMAND_15_0034_O_2TANK_PIPE_DEAL_PRESSURE		0x00b1//�жϹ�·ѹ���Ƿ��ȶ�


//��������------------------------------------------------------------------------------

void TGTHT510_supply_stage15_flow_o_main(void);
void TGTHT510_supply_stage15_flow_o_step_tank_number(void);
uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_hyct_good(void);
uint16 TGTHT510_supply_stage15_flow_o_step_1tank_interface_valve_on(void);
uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_interface_valve_on_pressure(void);
uint16 TGTHT510_supply_stage15_flow_o_step_1tank_middle_valve_on(void);
uint16 TGTHT510_supply_stage15_flow_o_step_1tank_delay(void);
uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_pipe_pressure(void);
uint16 TGTHT510_supply_stage15_flow_o_step_1tank_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_flow_correct(void);
uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_flow_over(void);
uint16 TGTHT510_supply_stage15_flow_o_step_1tank_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage15_flow_o_step_1tank_is_valve_off_pressure(void);
void TGTHT510_supply_stage15_flow_o_step_1tank_is_need_flow_third(void);
uint16 TGTHT510_supply_stage15_flow_o_step_1tank_set_flow_good(void);
uint16 TGTHT510_supply_stage15_flow_o_step_1tank_pipe_deal(void);

uint16 TGTHT510_supply_stage15_flow_o_step_2tank_is_hyct_good(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_interface_valve_on(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_is_interface_valve_on_pressure(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_middle_valve_on(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_delay(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_is_pipe_pressure(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_flow_correct(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_flow_over(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank1_is_valve_off_pressure(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_flow_correct(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_flow_over(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_tank2_is_valve_off_pressure(void);
void TGTHT510_supply_stage15_flow_o_step_2tank_is_need_flow_third(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_set_flow_good(void);
uint16 TGTHT510_supply_stage15_flow_o_step_2tank_pipe_deal(void);


#endif
 
 

 
 


 
