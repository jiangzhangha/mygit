/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ���������������������ͷ�ļ�
  ******************************************************************************
  */
 
#ifndef __supply_stage_10_flow_f_third_h
#define __supply_stage_10_flow_f_third_h
 

/*�����ṹ������--------------------------------------------------------------*/



/*�궨��---------------------------------------------------------------------------*/

//����step----------------------------------------------------------------------

#define 	STEP_10_F_1TANK_IS_HYCT_GOOD					0x0001//�жϻ�����ѹ״̬��
#define 	STEP_10_F_1TANK_INTERFACE_VALVE_ON				0x0002//���������Ͻ�������
#define 	STEP_10_F_1TANK_IS_INTERFACE_VALVE_ON			0x0003//ͨ��ѹ���жϽ������Ͻ������ſ����Ƿ�����
#define 	STEP_10_F_1TANK_MIDDLE_VALVE_ON					0x0004//��ȼ���ӽӿ��м䷧��
#define 	STEP_10_F_1TANK_DELAY1							0x0005//��ʱ�ȴ�
#define 	STEP_10_F_1TANK_IS_PIPE_PRESSURE				0x0006//ͨ��ѹ���ж�ȼ���ӽӿڹ�·ѹ���Ƿ��ȶ�
#define 	STEP_10_F_1TANK_IN_TANK_VALVE_ON				0x0007//�������䲹��Һ·����
#define 	STEP_10_F_1TANK_IS_FLOW_CORRECT_V				0x0008//ͨ�����������жϲ��ӹ����Ƿ�����
#define 	STEP_10_F_1TANK_IS_FLOW_OVER					0x0009//�жϲ����Ƿ�λ
#define 	STEP_10_F_1TANK_SET_FLOW_GOOD					0x000a//���ò��ӵ�λ��Ϣ�����ͻ���
#define 	STEP_10_F_1TANK_IN_TANK_VALVE_OFF				0x000b//�ؽ����䲹��Һ·����
#define 	STEP_10_F_1TANK_IS_IN_TANK_VALVE_OFF			0x000c//ͨ��ѹ���ж����䷧�Źر��Ƿ�����
#define 	STEP_10_F_1TANK_PIPE_DEAL						0x000d//�ܱչ�·��������


//����command-------------------------------------------------------------------

//�жϻ�����ѹ״̬��
#define		COMMAND_10_0001_F_1TANK_IS_HYCT_GOOD			0x0002

//���������Ͻ�������
#define		COMMAND_10_0001_F_1TANK_INTERFACE_VALVE_ON		0x0003//���������Ͻ�������
#define		COMMAND_10_0002_F_1TANK_IS_INTERFACE_VALVE_ON	0x0004//�жϷ��ſ����Ƿ�����

//ͨ��ѹ���жϽ������Ͻ������ſ����Ƿ�����
#define		COMMAND_10_0001_F_1TANK_INTERFACE_VALVE_ON_P	0x0005

//��ȼ���ӽӿ��м䷧��
#define		COMMAND_10_0001_F_1TANK_MIDDLE_VALVE_ON			0x0006//��ȼ���ӽӿ��м䷧��
#define		COMMAND_10_0002_F_1TANK_IS_MIDDLE_VALVE_ON		0x0007//�жϷ��ſ����Ƿ�����

//��ʱ�ȴ�
#define		COMMAND_10_0001_F_1TANK_DELAY1_START			0x0008//��ʱ�ȴ���ʱ��ʼ
#define		COMMAND_10_0002_F_1TANK_IS_DELAY1				0x0009//�ж���ʱ�ȴ��Ƿ�

//ͨ��ѹ���ж�ȼ���ӽӿڹ�·ѹ���Ƿ��ȶ�
#define		COMMAND_10_0001_F_1TANK_PIPE_PRESSURE_NO1		0x000a//�ɼ���·ѹ������һ��
#define		COMMAND_10_0002_F_1TANK_5SEC_START_NO1			0x000b//5s��ʱ��ʼ
#define		COMMAND_10_0003_F_1TANK_IS_5SEC_NO1				0x000c//�ж�5s��ʱ�Ƿ����
#define		COMMAND_10_0004_F_1TANK_PIPE_PRESSURE_NO2		0x000d//�ɼ���·ѹ�����ڶ���
#define		COMMAND_10_0005_F_1TANK_5SEC_START_NO2			0x000e//5s��ʱ��ʼ
#define		COMMAND_10_0006_F_1TANK_IS_5SEC_NO2				0x000f//�ж�5s��ʱ�Ƿ����
#define		COMMAND_10_0007_F_1TANK_PIPE_PRESSURE_NO3		0x0010//�ɼ���·ѹ����������
#define		COMMAND_10_0008_F_1TANK_5SEC_START_NO3			0x0011//5s��ʱ��ʼ
#define		COMMAND_10_0009_F_1TANK_IS_5SEC_NO3				0x0012//�ж�5s��ʱ�Ƿ����
#define		COMMAND_10_0010_F_1TANK_PIPE_PRESSURE_NO4		0x0013//�ɼ���·ѹ�������Ĵ�
#define		COMMAND_10_0011_F_1TANK_5SEC_START_NO4			0x0014//5s��ʱ��ʼ
#define		COMMAND_10_0012_F_1TANK_IS_5SEC_NO4				0x0015//�ж�5s��ʱ�Ƿ����
#define		COMMAND_10_0013_F_1TANK_PIPE_PRESSURE_NO5		0x0016//�ɼ���·ѹ���������
#define		COMMAND_10_0014_F_1TANK_5SEC_START_NO5			0x0017//5s��ʱ��ʼ
#define		COMMAND_10_0015_F_1TANK_IS_5SEC_NO5				0x0018//�ж�5s��ʱ�Ƿ����
#define		COMMAND_10_0016_F_1TANK_PIPE_PRESSURE_NO6		0x0019//�ɼ���·ѹ����������
#define		COMMAND_10_0017_F_1TANK_5SEC_START_NO6			0x001a//5s��ʱ��ʼ
#define		COMMAND_10_0018_F_1TANK_IS_5SEC_NO6				0x001b//�ж�5s��ʱ�Ƿ����
#define		COMMAND_10_0019_F_1TANK_PIPE_PRESSURE_NO7		0x001c//�ɼ���·ѹ�������ߴ�
#define		COMMAND_10_0020_F_1TANK_IS_PIPE_PRESSURE		0x001d//�жϹ�·ѹ���Ƿ��ȶ�

//�������䲹��Һ·����
#define		COMMAND_10_0001_F_1TANK_IN_TANK_VALVE_ON		0x001e
#define		COMMAND_10_0002_F_1TANK_IS_IN_TANK_VALVE_ON		0x001f

//ͨ�����������жϲ��ӹ����Ƿ�����
#define		COMMAND_10_0001_F_1TANK_HTT_NO1					0x0020
#define		COMMAND_10_0002_F_1TANK_1MIN_START_NO1			0x0021
#define		COMMAND_10_0003_F_1TANK_IS_1MIN_NO1				0x0022
#define		COMMAND_10_0004_F_1TANK_HTT_NO2					0x0023
#define		COMMAND_10_0005_F_1TANK_1MIN_START_NO2			0x0024
#define		COMMAND_10_0006_F_1TANK_IS_1MIN_NO2				0x0025
#define		COMMAND_10_0007_F_1TANK_HTT_NO3					0x0026
#define		COMMAND_10_0008_F_1TANK_IS_FLOW_CORRECT			0x0027

//�жϲ����Ƿ�λ
#define		COMMAND_10_0001_F_1TANK_IS_FLOW_OVER_NO1		0x0028
#define		COMMAND_10_0002_F_1TANK_IS_FLOW_OVER_NO2		0x0029
#define		COMMAND_10_0003_F_1TANK_IS_FLOW_OVER_NO3		0x002a

//���ò��ӵ�λ��Ϣ�����ͻ���
#define		COMMAND_10_0001_F_1TANK_SET_FLOW_GOOD			0x002b


//�ؽ����䲹��Һ·����
#define		COMMAND_10_0001_F_1TANK_IN_TANK_VALVE_OFF		0x002c
#define		COMMAND_10_0002_F_1TANK_IS_IN_TANK_VALVE_OFF	0x002d

//ͨ��ѹ���ж����䷧�Źر��Ƿ�����
#define		COMMAND_10_0001_F_1TANK_IS_PRESSURE				0x002e

//�ܱչ�·��������
#define		COMMAND_10_0001_F_1TANK_VALVE_OFF_NO1			0x0030
#define		COMMAND_10_0002_F_1TANK_IS_VALVE_OFF_NO1		0x0031
#define		COMMAND_10_0003_F_1TANK_VALVE_ON_NO2			0x0032
#define		COMMAND_10_0004_F_1TANK_IS_VALVE_ON_NO2			0x0033
#define		COMMAND_10_0005_F_1TANK_5SEC_START				0x0034
#define		COMMAND_10_0006_F_1TANK_IS_5SEC					0x0035
#define		COMMAND_10_0007_F_1TANK_VALVE_OFF_NO3			0x0036
#define		COMMAND_10_0008_F_1TANK_IS_VALVE_OFF_NO3		0x0037
#define		COMMAND_10_0009_F_1TANK_VALVE_OFF_NO4			0x0038
#define		COMMAND_10_0010_F_1TANK_IS_VALVE_OFF_NO4		0x0039
#define		COMMAND_10_0011_F_1TANK_VALVE_OFF_NO5			0x003a
#define		COMMAND_10_0012_F_1TANK_IS_VALVE_OFF_NO5		0x003b

#define		COMMAND_10_0013_F_1TANK_10SEC_START				0x003c
#define		COMMAND_10_0014_F_1TANK_IS_10SEC				0x003d

#define		COMMAND_10_0015_F_1TANK_PIPE_GET_NO1			0x003e//�ɼ�ѹ��
#define		COMMAND_10_0016_F_1TANK_PIPE_5SEC_START_NO1		0x003f//5s��ʱ��ʼ
#define		COMMAND_10_0017_F_1TANK_PIPE_IS_5SEC_NO1		0x0040//�ж�5s��ʱ�Ƿ����

#define		COMMAND_10_0018_F_1TANK_PIPE_GET_NO2			0x0041//�ɼ�ѹ��
#define		COMMAND_10_0019_F_1TANK_PIPE_5SEC_START_NO2		0x0042//5s��ʱ��ʼ
#define		COMMAND_10_0020_F_1TANK_PIPE_IS_5SEC_NO2		0x0043//�ж�5s��ʱ�Ƿ����

#define		COMMAND_10_0021_F_1TANK_PIPE_GET_NO3			0x0044//�ɼ�ѹ��
#define		COMMAND_10_0022_F_1TANK_PIPE_5SEC_START_NO3		0x0045//5s��ʱ��ʼ
#define		COMMAND_10_0023_F_1TANK_PIPE_IS_5SEC_NO3		0x0046//�ж�5s��ʱ�Ƿ����

#define		COMMAND_10_0024_F_1TANK_PIPE_GET_NO4			0x0047//�ɼ�ѹ��
#define		COMMAND_10_0025_F_1TANK_PIPE_5SEC_START_NO4		0x0048//5s��ʱ��ʼ
#define		COMMAND_10_0026_F_1TANK_PIPE_IS_5SEC_NO4		0x0049//�ж�5s��ʱ�Ƿ����

#define		COMMAND_10_0027_F_1TANK_PIPE_GET_NO5			0x004a//�ɼ�ѹ��
#define		COMMAND_10_0028_F_1TANK_PIPE_5SEC_START_NO5		0x004b//5s��ʱ��ʼ
#define		COMMAND_10_0029_F_1TANK_PIPE_IS_5SEC_NO5		0x004c//�ж�5s��ʱ�Ƿ����

#define		COMMAND_10_0030_F_1TANK_PIPE_GET_NO6			0x004d//�ɼ�ѹ��
#define		COMMAND_10_0031_F_1TANK_PIPE_5SEC_START_NO6		0x004e//5s��ʱ��ʼ
#define		COMMAND_10_0032_F_1TANK_PIPE_IS_5SEC_NO6		0x004f//�ж�5s��ʱ�Ƿ����

#define		COMMAND_10_0033_F_1TANK_PIPE_GET_NO7			0x0050//�ɼ�ѹ��
#define		COMMAND_10_0034_F_1TANK_PIPE_DEAL_PRESSURE		0x0051//�жϹ�·ѹ���Ƿ��ȶ�


//��������------------------------------------------------------------------------------

void TGTHT510_supply_stage10_flow_f_main(void);
void TGTHT510_supply_stage10_flow_f_step_tank_number(void);
uint16 TGTHT510_supply_stage10_flow_f_step_1tank_is_hyct_good(void);
uint16 TGTHT510_supply_stage10_flow_f_step_1tank_interface_valve_on(void);
uint16 TGTHT510_supply_stage10_flow_f_step_1tank_is_interface_valve_on_pressure(void);
uint16 TGTHT510_supply_stage10_flow_f_step_1tank_middle_valve_on(void);
uint16 TGTHT510_supply_stage10_flow_f_step_1tank_delay(void);
uint16 TGTHT510_supply_stage10_flow_f_step_1tank_is_pipe_pressure(void);
uint16 TGTHT510_supply_stage10_flow_f_step_1tank_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage10_flow_f_step_1tank_is_flow_correct(void);
uint16 TGTHT510_supply_stage10_flow_f_step_1tank_is_flow_over(void);
uint16 TGTHT510_supply_stage10_flow_f_step_1tank_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage10_flow_f_step_1tank_is_valve_off_pressure(void);
uint16 TGTHT510_supply_stage10_flow_f_step_1tank_set_flow_good(void);
uint16 TGTHT510_supply_stage10_flow_f_step_1tank_pipe_deal(void);
uint16 TGTHT510_supply_common_third_flow_pipe_deal(uint16 flow_kind,uint16 command_number);


#endif
 
 
 