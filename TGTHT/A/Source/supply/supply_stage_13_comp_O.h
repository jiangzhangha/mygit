/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ���������������������ͷ�ļ�
  ******************************************************************************
  */
 
#ifndef __supply_stage_13_comp_o_h
#define __supply_stage_13_comp_o_h
 

/*�����ṹ������--------------------------------------------------------------*/



/*�궨��---------------------------------------------------------------------------*/

//����step-------------------------------------------------------------------------

//----------------------------------��ʼ���ý׶�-----------------------------------

#define 	STEP_13_O_INIT_START_COOLER							0x0000//����Һ��ù���
#define 	STEP_13_O_INIT_IS_COOLER_WORK						0x0001//ͨ��ת���ж�Һ�乤���Ƿ�����
#define 	STEP_13_O_INIT_DELAY								0x0002//��ʱ�ȴ�ʱ��
#define		STEP_13_O_INIT_IS_COMPRESSOR_TEMPERATURE			0x0003//�ж�ѹ�����¶��Ƿ�����
#define		STEP_13_O_INIT_TGTHT530_POWER_ON					0x0004//�������������ӵ�
#define		STEP_13_O_INIT_COMPRESSOR_POWER_ON					0x0005//����ѹ�����ӵ�
#define		STEP_13_O_INIT_ISOLATION							0x0006//�������
#define		STEP_13_O_INIT_NUMBER_COMP_TANK						0x0007//�жϳ����������

//----------------------------------һ���������-----------------------------------

#define 	STEP_13_O_1TANK_IN_TANK_VALVE_ON					0x0008//���������ѹ��·���ӷ���

#define 	STEP_13_O_1TANK_TIME_DELAY_A						0x009e//��ʱ�ȴ�

#define 	STEP_13_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE		0x0009//ͨ��ѹ���жϿ��������ѹ��·���ӷ���
#define 	STEP_13_O_1TANK_IN_COMPRESSOR_VALVE_ON				0x000a//����ѹ�������ڷ���
#define 	STEP_13_O_1TANK_TIME_DELAY1							0x000b//��ʱ�ȴ�time_delay1
#define 	STEP_13_O_1TANK_IS_IN_COMPRESSOR_PRESSURE			0x000c//�ж�ѹ��������ѹ���Ƿ�����
#define 	STEP_13_O_1TANK_COMPRESSOR_START					0x000d//��ѹ��������

#define 	STEP_13_O_1TANK_TIME_DELAY_B						0x009f//��ʱ�ȴ�

#define 	STEP_13_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE			0x000e//�ж�ѹ��������ѹ���Ƿ�����
#define 	STEP_13_O_1TANK_OUT_COMPRESSOR_VALVE_ON				0x000f//����ѹ�������ڷ���
#define 	STEP_13_O_1TANK_NUMBER_COMP_GAS						0x0010//�жϳ�����ƿ����

//һ����ƿ����
#define 	STEP_13_O_1TANK_1GAS_IN_GAS_VALVE_ON				0x0011//������ƿ���ӷ���
#define 	STEP_13_O_1TANK_1GAS_TIME_DELAY2					0x0012//��ʱ�ȴ�time_delay2
#define 	STEP_13_O_1TANK_1GAS_IS_GAS_PRESSURE				0x0013//�ж���ƿѹ���Ƿ�����
#define 	STEP_13_O_1TANK_1GAS_IS_COMP_OVER					0x0014//�ж���ƿ�����Ƿ����
#define 	STEP_13_O_1TANK_1GAS_IN_GAS_VALVE_OFF				0x0015//����·��ƿ���ӷ���

#define		STEP_13_O_1TANK_1GAS_IS_ISOLATION_FIRST				0x0016//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define 	STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF		0x0017//�ر���ѹ�������ڷ���
#define		STEP_13_O_1TANK_1GAS_IS_ISOLATION_SECOND			0x0018//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���

#define		STEP_13_O_1TANK_1GAS_COMPRESSOR_STOP				0x0019//��ѹ����ͣ��
#define		STEP_13_O_1TANK_1GAS_IS_COMPRESSOR_STOP				0x001a//�ж���ѹ����ͣ���Ƿ�����
#define		STEP_13_O_1TANK_1GAS_BYPATH_VALVE_ON				0x001b//����ѹ������·������
#define 	STEP_13_O_1TANK_1GAS_TIME_DELAY_BYPATH				0x001c//��ʱ�ȴ�time_bypath
#define		STEP_13_O_1TANK_1GAS_BYPATH_VALVE_OFF				0x001d//����ѹ������·������
#define 	STEP_13_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2		0x001e//�ر���ѹ�������ڷ��ţ��ڶ���
#define 	STEP_13_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF		0x001f//�ر���ѹ�������ڷ���
#define 	STEP_13_O_1TANK_1GAS_IN_TANK_VALVE_OFF				0x0020//�ؽ������ѹ��·���ӷ���
#define 	STEP_13_O_1TANK_1GAS_SET_STATE_GOOD					0x0021//����������״̬��
#define 	STEP_13_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE		0x0022//�ж�ѹ�����¶��Ƿ�����
#define 	STEP_13_O_1TANK_1GAS_IS_NEED_COOLER_STOP			0x0023//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��
//#define 	STEP_13_O_1TANK_1GAS_IS_NEED_EXCHANGE				0x0023//�ж��Ƿ���Ҫ����Һ��ģ���л�����

#define 	STEP_13_O_1TANK_1GAS_TIME_DELAY3					0x0024//��ʱ�ȴ�time_delay3
//#define 	STEP_13_O_1TANK_1GAS_EXCHANGE_COOLER				0x0025//����Һ��ģ���л�����
//#define	STEP_13_O_1TANK_1GAS_IS_EXCHANGE_COOLER				0x0026//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		STEP_13_O_1TANK_1GAS_COOLER_STOP					0x0025//Һ��ģ��ͣ��

#define		STEP_13_O_1TANK_1GAS_COOLER_SET						0x0026//Һ��ģ��״̬����

#define		STEP_13_O_1TANK_1GAS_COMPRESSOR_POWER_OFF			0x0028//����ѹ�����ϵ�
#define		STEP_13_O_1TANK_1GAS_TGTHT530_POWER_OFF				0x0029//�������������ϵ�

//**************************************�������******************************************************************

//������ƿ����
#define 	STEP_13_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON			0x002a//������ƿ���ӷ���---��һ����ƿ
#define 	STEP_13_O_1TANK_2GAS_GAS1_TIME_DELAY2				0x002b//��ʱ�ȴ�time_delay2---��һ����ƿ
#define 	STEP_13_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE			0x002c//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define 	STEP_13_O_1TANK_2GAS_GAS1_IS_COMP_OVER				0x002d//�ж���ƿ�����Ƿ����---��һ����ƿ
#define 	STEP_13_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF			0x002e//����·��ƿ���ӷ���---��һ����ƿ
#define 	STEP_13_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON			0x002f//������ƿ���ӷ���---�ڶ�����ƿ
#define 	STEP_13_O_1TANK_2GAS_GAS2_TIME_DELAY2				0x0030//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define 	STEP_13_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE			0x0031//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define 	STEP_13_O_1TANK_2GAS_GAS2_IS_COMP_OVER				0x0032//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define 	STEP_13_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF			0x0033//����·��ƿ���ӷ���---�ڶ�����ƿ

#define		STEP_13_O_1TANK_2GAS_IS_ISOLATION_FIRST				0x0034//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define 	STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF		0x0035//�ر���ѹ�������ڷ���
#define		STEP_13_O_1TANK_2GAS_IS_ISOLATION_SECOND			0x0036//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���

#define		STEP_13_O_1TANK_2GAS_COMPRESSOR_STOP				0x0037//��ѹ����ͣ��
#define		STEP_13_O_1TANK_2GAS_IS_COMPRESSOR_STOP				0x0038//�ж���ѹ����ͣ���Ƿ�����
#define		STEP_13_O_1TANK_2GAS_BYPATH_VALVE_ON				0x0039//����ѹ������·������
#define 	STEP_13_O_1TANK_2GAS_TIME_DELAY_BYPATH				0x003a//��ʱ�ȴ�time_bypath
#define		STEP_13_O_1TANK_2GAS_BYPATH_VALVE_OFF				0x003b//����ѹ������·������
#define 	STEP_13_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2		0x003c//�ر���ѹ�������ڷ��ţ��ڶ���
#define 	STEP_13_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF		0x003d//�ر���ѹ�������ڷ���
#define 	STEP_13_O_1TANK_2GAS_IN_TANK_VALVE_OFF				0x003e//�ؽ������ѹ��·���ӷ���
#define 	STEP_13_O_1TANK_2GAS_SET_STATE_GOOD					0x003f//����������״̬��
#define 	STEP_13_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE		0x0040//�ж�ѹ�����¶��Ƿ�����
#define 	STEP_13_O_1TANK_2GAS_IS_NEED_COOLER_STOP			0x0041//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��

//#define 	STEP_13_O_1TANK_2GAS_IS_NEED_EXCHANGE				0x0041//�ж��Ƿ���Ҫ����Һ��ģ���л�����

#define 	STEP_13_O_1TANK_2GAS_TIME_DELAY3					0x0042//��ʱ�ȴ�time_delay3
//#define 	STEP_13_O_1TANK_2GAS_EXCHANGE_COOLER				0x0043//����Һ��ģ���л�����
//#define		STEP_13_O_1TANK_2GAS_IS_EXCHANGE_COOLER			0x0044//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		STEP_13_O_1TANK_2GAS_COOLER_STOP					0x0043//Һ��ģ��ͣ��

#define		STEP_13_O_1TANK_2GAS_COOLER_SET						0x0044//Һ��ģ��״̬����

#define		STEP_13_O_1TANK_2GAS_COMPRESSOR_POWER_OFF			0x0046//����ѹ�����ϵ�
#define		STEP_13_O_1TANK_2GAS_TGTHT530_POWER_OFF				0x0047//�������������ϵ�

//**************************************�������******************************************************************

//----------------------------------���������������һ���������-----------------------------------

#define 	STEP_13_O_2TANK_TANK1_IN_TANK_VALVE_ON				0x0048//���������ѹ��·���ӷ���---��һ������

#define 	STEP_13_O_2TANK_TANK1_TIME_DELAY_C					0x00a0//��ʱ�ȴ�

#define 	STEP_13_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE	0x0049//ͨ��ѹ���жϿ������䷧��---��һ������
#define 	STEP_13_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON		0x004a//����ѹ�������ڷ���---��һ������
#define 	STEP_13_O_2TANK_TANK1_TIME_DELAY1					0x004b//��ʱ�ȴ�time_delay1---��һ������
#define 	STEP_13_O_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE		0x004c//�ж�ѹ��������ѹ���Ƿ�����---��һ������
#define 	STEP_13_O_2TANK_TANK1_COMPRESSOR_START				0x004d//��ѹ��������---��һ������

#define 	STEP_13_O_2TANK_TANK1_TIME_DELAY_D					0x00a1//��ʱ�ȴ�

#define 	STEP_13_O_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE	0x004e//�ж�ѹ��������ѹ���Ƿ�����---��һ������
#define 	STEP_13_O_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON		0x004f//����ѹ�������ڷ���---��һ������
#define 	STEP_13_O_2TANK_TANK1_NUMBER_COMP_GAS				0x0050//�жϳ�����ƿ����---��һ������

//һ����ƿ����
#define 	STEP_13_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON				0x0051//������ƿ���ӷ���---��һ������
#define 	STEP_13_O_2TANK_TANK1_1GAS_TIME_DELAY2					0x0052//��ʱ�ȴ�time_delay2---��һ������
#define 	STEP_13_O_2TANK_TANK1_1GAS_IS_GAS_PRESSURE				0x0053//�ж���ƿѹ���Ƿ�����---��һ������
#define 	STEP_13_O_2TANK_TANK1_1GAS_IS_COMP_OVER					0x0054//�ж���ƿ�����Ƿ����---��һ������
#define 	STEP_13_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF				0x0055//����·��ƿ���ӷ���---��һ������
#define 	STEP_13_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF			0x0056//�ؽ������ѹ��·���ӷ���---��һ������
#define 	STEP_13_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE	0x0057//ͨ��ѹ���жϹؽ����䲹�ӷ�---��һ������

//**************************************����ת���ڶ����������*****************************************************

//������ƿ����
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON			0x0058//������ƿ���ӷ���---��һ����ƿ
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2				0x0059//��ʱ�ȴ�time_delay2---��һ����ƿ
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE			0x005a//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS1_IS_COMP_OVER			0x005b//�ж���ƿ�����Ƿ����---��һ����ƿ
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF		0x005c//����·��ƿ���ӷ���---��һ����ƿ
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON			0x005d//������ƿ���ӷ���---�ڶ�����ƿ
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2				0x005e//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE			0x005f//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS2_IS_COMP_OVER			0x0060//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define 	STEP_13_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF		0x0061//����·��ƿ���ӷ���---�ڶ�����ƿ
#define 	STEP_13_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF			0x0062//�ؽ������ѹ��·���ӷ���
#define 	STEP_13_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE	0x0063//ͨ��ѹ���жϹؽ����䲹�ӷ�

//**************************************����ת���ڶ����������*****************************************************

//----------------------------------��������������ڶ����������-----------------------------------

#define 	STEP_13_O_2TANK_TANK2_IN_TANK_VALVE_ON					0x0064//���������ѹ��·���ӷ���---�ڶ�������

#define 	STEP_13_O_2TANK_TANK2_TIME_DELAY_E						0x00a2//��ʱ�ȴ�

#define 	STEP_13_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE		0x0065//ͨ��ѹ���жϿ������䷧��---�ڶ�������
#define 	STEP_13_O_2TANK_TANK2_NUMBER_COMP_GAS					0x0066//�жϳ�����ƿ����---�ڶ�������

//һ����ƿ����
#define 	STEP_13_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON				0x0067//������ƿ���ӷ���---�ڶ�������
#define 	STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY2					0x0068//��ʱ�ȴ�time_delay2---�ڶ�������
#define 	STEP_13_O_2TANK_TANK2_1GAS_IS_GAS_PRESSURE				0x0069//�ж���ƿѹ���Ƿ�����---�ڶ�������
#define 	STEP_13_O_2TANK_TANK2_1GAS_IS_COMP_OVER					0x006a//�ж���ƿ�����Ƿ����---�ڶ�������
#define 	STEP_13_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF				0x006b//����·��ƿ���ӷ���---�ڶ�������

#define		STEP_13_O_2TANK_TANK2_1GAS_IS_ISOLATION_FIRST			0x006c//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define 	STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF		0x006d//�ر���ѹ�������ڷ���
#define		STEP_13_O_2TANK_TANK2_1GAS_IS_ISOLATION_SECOND			0x006e//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���

#define		STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP				0x006f//��ѹ����ͣ��
#define		STEP_13_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_STOP			0x0070//�ж���ѹ����ͣ���Ƿ�����
#define		STEP_13_O_2TANK_TANK2_1GAS_BYPATH_VALVE_ON				0x0071//����ѹ������·������
#define 	STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY_BYPATH			0x0072//��ʱ�ȴ�time_bypath
#define		STEP_13_O_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF				0x0073//����ѹ������·������
#define 	STEP_13_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2	0x0074//�ر���ѹ�������ڷ��ţ��ڶ���
#define 	STEP_13_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF		0x0075//�ر���ѹ�������ڷ���
#define 	STEP_13_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF			0x0076//�ؽ������ѹ��·���ӷ���
#define 	STEP_13_O_2TANK_TANK2_1GAS_SET_STATE_GOOD				0x0077//����������״̬��
#define 	STEP_13_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE	0x0078//�ж�ѹ�����¶��Ƿ�����
#define 	STEP_13_O_2TANK_TANK2_1GAS_IS_NEED_COOLER_STOP			0x0079//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��

//#define 	STEP_13_O_2TANK_TANK2_1GAS_IS_NEED_EXCHANGE				0x0079//�ж��Ƿ���Ҫ����Һ��ģ���л�����

#define 	STEP_13_O_2TANK_TANK2_1GAS_TIME_DELAY3					0x007a//��ʱ�ȴ�time_delay3
//#define 	STEP_13_O_2TANK_TANK2_1GAS_EXCHANGE_COOLER				0x007b//����Һ��ģ���л�����
//#define		STEP_13_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER		0x007c//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		STEP_13_O_2TANK_TANK2_1GAS_COOLER_STOP					0x007b//Һ��ģ��ͣ��

#define		STEP_13_O_2TANK_TANK2_1GAS_COOLER_SET					0x007c//Һ��ģ��״̬����

#define		STEP_13_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF			0x007e//����ѹ�����ϵ�
#define		STEP_13_O_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF			0x007f//�������������ϵ�

//**************************************�������******************************************************************

//������ƿ����
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON			0x0080//������ƿ���ӷ���---��һ����ƿ
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2				0x0081//��ʱ�ȴ�time_delay2---��һ����ƿ
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE			0x0082//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS1_IS_COMP_OVER			0x0083//�ж���ƿ�����Ƿ����---��һ����ƿ
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF		0x0084//����·��ƿ���ӷ���---��һ����ƿ
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON			0x0085//������ƿ���ӷ���---�ڶ�����ƿ
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2				0x0086//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE			0x0087//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS2_IS_COMP_OVER			0x0088//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define 	STEP_13_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF		0x0089//����·��ƿ���ӷ���---�ڶ�����ƿ

#define		STEP_13_O_2TANK_TANK2_2GAS_IS_ISOLATION_FIRST			0x008a//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define 	STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF		0x008b//�ر���ѹ�������ڷ���
#define		STEP_13_O_2TANK_TANK2_2GAS_IS_ISOLATION_SECOND			0x008c//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���

#define		STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP				0x008d//��ѹ����ͣ��
#define		STEP_13_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_STOP			0x008e//�ж���ѹ����ͣ���Ƿ�����
#define		STEP_13_O_2TANK_TANK2_2GAS_BYPATH_VALVE_ON				0x008f//����ѹ������·������
#define 	STEP_13_O_2TANK_TANK2_2GAS_TIME_DELAY_BYPATH			0x0090//��ʱ�ȴ�time_bypath
#define		STEP_13_O_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF				0x0091//����ѹ������·������
#define 	STEP_13_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2	0x0092//�ر���ѹ�������ڷ��ţ��ڶ���
#define 	STEP_13_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF		0x0093//�ر���ѹ�������ڷ���
#define 	STEP_13_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF			0x0094//�ؽ������ѹ��·���ӷ���
#define 	STEP_13_O_2TANK_TANK2_2GAS_SET_STATE_GOOD				0x0095//����������״̬��
#define 	STEP_13_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE	0x0096//�ж�ѹ�����¶��Ƿ�����
#define 	STEP_13_O_2TANK_TANK2_2GAS_IS_NEED_COOLER_STOP			0x0097//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��

//#define 	STEP_13_O_2TANK_TANK2_2GAS_IS_NEED_EXCHANGE				0x0097//�ж��Ƿ���Ҫ����Һ��ģ���л�����

#define 	STEP_13_O_2TANK_TANK2_2GAS_TIME_DELAY3					0x0098//��ʱ�ȴ�time_delay3
//#define 	STEP_13_O_2TANK_TANK2_2GAS_EXCHANGE_COOLER				0x0099//����Һ��ģ���л�����
//#define		STEP_13_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER		0x009a//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		STEP_13_O_2TANK_TANK2_2GAS_COOLER_STOP					0x0099//Һ��ģ��ͣ��

#define		STEP_13_O_2TANK_TANK2_2GAS_COOLER_SET					0x009a//Һ��ģ��״̬����

#define		STEP_13_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF			0x009c//����ѹ�����ϵ�
#define		STEP_13_O_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF			0x009d//�������������ϵ�



//0x00a2

//**************************************�������******************************************************************

//����command--------------------------------------------------------------------------------------------

//------------------------------command---��ʼ���ý׶�---------------------------------------------------

//����Һ��ù���
#define		COMMAND_13_0001_O_INIT_COOLER_VALVE_ON_NO1			0x0001//Һ��ģ�鲹��ϵͳ���ſ���һ��
#define		COMMAND_13_0002_O_INIT_IS_COOLER_VALVE_ON_NO1		0x0002//�ж�Һ��ģ�鲹��ϵͳ���ſ���һ��
#define		COMMAND_13_0003_O_INIT_COOLER_VALVE_ON_NO2			0x0003//Һ��ģ�鲹��ϵͳ���ſ��ڶ���
#define		COMMAND_13_0004_O_INIT_IS_COOLER_VALVE_ON_NO2		0x0004//�ж�Һ��ģ�鲹��ϵͳ���ſ��ڶ���
#define		COMMAND_13_0005_O_INIT_COOLER_POWER_ON				0x0005//Һ��ģ�鹩��ͨ
#define		COMMAND_13_0006_O_INIT_TIME_1MIN_START				0x0006//��ʱ1min��ʱ��ʼ
#define		COMMAND_13_0007_O_INIT_IS_TIME_1MIN					0x0007//��ʱ1min�Ƿ�

//ͨ��ת���ж�Һ�乤���Ƿ�����
#define		COMMAND_13_0001_O_INIT_IS_COOLER_WORK				0x0008//ͨ��ת���ж�Һ�乤���Ƿ�����

//��ʱ�ȴ�time_delay
#define		COMMAND_13_0001_O_INIT_TIME_DELAY_START				0x0009//��ʱ�ȴ�time_delay��ʱ��ʼ
#define		COMMAND_13_0002_O_INIT_IS_TIME_DELAY				0x000a//�ж���ʱ�ȴ�time_delay

//�ж�ѹ�����¶��Ƿ�����
#define		COMMAND_13_0001_O_INIT_IS_COMPRESSOR_TEMPERATURE	0x000b//�ж�ѹ�����¶��Ƿ�����

//�������������ӵ�
#define		COMMAND_13_0001_O_INIT_TGTHT530_POWER_ON			0x000c//�����豸����ָ��
#define		COMMAND_13_0002_O_INIT_TGTHT530_TIME_1MIN_START		0x000d//��ʱ1min��ʱ��ʼ
#define		COMMAND_13_0003_O_INIT_TGTHT530_IS_TIME_1MIN		0x000e//�жϼ�ʱ1min�Ƿ�
#define		COMMAND_13_0004_O_INIT_TGTHT530_IS_POWER_ON			0x000f//ͨ�����������жϼӵ��Ƿ�����

//����ѹ�����ӵ�
#define		COMMAND_13_0001_O_INIT_COMPRESSOR_POWER_ON			0x0010//�����豸����ָ��
#define		COMMAND_13_0002_O_INIT_COMPRESSOR_TIME_1MIN_START	0x0011//��ʱ1min��ʱ��ʼ
#define		COMMAND_13_0003_O_INIT_COMPRESSOR_IS_TIME_1MIN		0x0012//�жϼ�ʱ1min�Ƿ�

//�������
#define		COMMAND_13_0001_O_INIT_ISOLATION_VALVE_OFF_NO1		0x0013//�����ƽ�ϵͳ�������رգ���һ��
#define		COMMAND_13_0002_O_INIT_TIME_1MIN_START_NO1			0x0014//��ʱ1min��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_INIT_IS_TIME_1MIN_NO1				0x0015//��ʱ1min�Ƿ񵽣���һ��
#define		COMMAND_13_0004_O_INIT_IS_ISOLATION_VALVE_OFF_NO1	0x0016//�жϸ����ƽ�ϵͳ�������رգ���һ��

#define		COMMAND_13_0005_O_INIT_ISOLATION_VALVE_OFF_NO2		0x0017//�����ƽ�ϵͳ�������رգ��ڶ���
#define		COMMAND_13_0006_O_INIT_TIME_1MIN_START_NO2			0x0018//��ʱ1min��ʱ��ʼ���ڶ���
#define		COMMAND_13_0007_O_INIT_IS_TIME_1MIN_NO2				0x0019//��ʱ1min�Ƿ񵽣��ڶ���
#define		COMMAND_13_0008_O_INIT_IS_ISOLATION_VALVE_OFF_NO2	0x001a//�жϸ����ƽ�ϵͳ�������رգ��ڶ���

#define		COMMAND_13_0009_O_INIT_ISOLATION_VALVE_OFF_NO3		0x001b//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_13_0010_O_INIT_TIME_1MIN_START_NO3			0x001c//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_13_0011_O_INIT_IS_TIME_1MIN_NO3				0x001d//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_13_0012_O_INIT_IS_ISOLATION_VALVE_OFF_NO3	0x001e//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_13_0013_O_INIT_ISOLATION_VALVE_OFF_NO4		0x001f//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_13_0014_O_INIT_TIME_1MIN_START_NO4			0x0020//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_13_0015_O_INIT_IS_TIME_1MIN_NO4				0x0021//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_13_0016_O_INIT_IS_ISOLATION_VALVE_OFF_NO4	0x0022//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_13_0017_O_INIT_ISOLATION_VALVE_OFF_NO5		0x0023//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_13_0018_O_INIT_TIME_1MIN_START_NO5			0x0024//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_13_0019_O_INIT_IS_TIME_1MIN_NO5				0x0025//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_13_0020_O_INIT_IS_ISOLATION_VALVE_OFF_NO5	0x0026//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_13_0021_O_INIT_ISOLATION_VALVE_OFF_NO6		0x0027//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_13_0022_O_INIT_TIME_1MIN_START_NO6			0x0028//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_13_0023_O_INIT_IS_TIME_1MIN_NO6				0x0029//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_13_0024_O_INIT_IS_ISOLATION_VALVE_OFF_NO6	0x002a//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_13_0025_O_INIT_ISOLATION_VALVE_OFF_NO7		0x002b//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_13_0026_O_INIT_TIME_1MIN_START_NO7			0x002c//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_13_0027_O_INIT_IS_TIME_1MIN_NO7				0x002d//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_13_0028_O_INIT_IS_ISOLATION_VALVE_OFF_NO7	0x002e//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_13_0029_O_INIT_ISOLATION_VALVE_OFF_NO8		0x002f//�����ƽ�ϵͳ�������رգ��ڰ���
#define		COMMAND_13_0030_O_INIT_TIME_1MIN_START_NO8			0x0030//��ʱ1min��ʱ��ʼ���ڰ���
#define		COMMAND_13_0031_O_INIT_IS_TIME_1MIN_NO8				0x0031//��ʱ1min�Ƿ񵽣��ڰ���
#define		COMMAND_13_0032_O_INIT_IS_ISOLATION_VALVE_OFF_NO8	0x0032//�жϸ����ƽ�ϵͳ�������رգ��ڰ���

#define		COMMAND_13_0033_O_INIT_ISOLATION_VALVE_OFF_NO9		0x0033//�����ƽ�ϵͳ�������رգ��ھ���
#define		COMMAND_13_0034_O_INIT_TIME_1MIN_START_NO9			0x0034//��ʱ1min��ʱ��ʼ���ھ���
#define		COMMAND_13_0035_O_INIT_IS_TIME_1MIN_NO9				0x0035//��ʱ1min�Ƿ񵽣��ھ���
#define		COMMAND_13_0036_O_INIT_IS_ISOLATION_VALVE_OFF_NO9	0x0036//�жϸ����ƽ�ϵͳ�������رգ��ھ���

//�жϳ����������
#define		COMMAND_13_0001_O_INIT_NUMBER_COMP_TANK				0x0037//�жϳ����������
			
//------------------------------command---һ���������-----------------------------------------------

//���������ѹ��·���ӷ���
#define		COMMAND_13_0001_O_1TANK_IN_TANK_VALVE_ON					0x0038//���������ѹ��·���ӷ���
#define		COMMAND_13_0002_O_1TANK_IS_IN_TANK_VALVE_ON					0x0039//�жϿ��������ѹ��·���ӷ���

//ͨ��ѹ���жϿ��������ѹ��·���ӷ���
#define		COMMAND_13_0001_O_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE		0x003a//ͨ��ѹ���жϿ����ӷ���

//����ѹ�������ڷ���
#define		COMMAND_13_0001_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO1			0x003b//����ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO1		0x003c//�жϿ���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO2			0x003d//����ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO2		0x003e//�жϿ���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_1TANK_IN_COMPRESSOR_VALVE_ON_NO3			0x003f//����ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO3		0x0040//�жϿ���ѹ�������ڷ��ţ�������

//��ʱ�ȴ�time_delay1
#define		COMMAND_13_0001_O_1TANK_TIME_DELAY1_START					0x0041//��ʱ�ȴ�time_delay1��ʱ��ʼ
#define		COMMAND_13_0002_O_1TANK_IS_TIME_DELAY1						0x0042//�ж���ʱ�ȴ�time_delay1

//�ж�ѹ��������ѹ���Ƿ�����
#define		COMMAND_13_0001_O_1TANK_IS_IN_COMPRESSOR_PRESSURE			0x0043//�ж�ѹ��������ѹ���Ƿ�����

//��ѹ��������
#define		COMMAND_13_0001_O_1TANK_COMPRESSOR_START					0x0044//�����豸����ָ�ѹ��������
#define		COMMAND_13_0002_O_1TANK_COMPRESSOR_TIME_1MIN_START			0x0045//��ʱ1min��ʱ��ʼ
#define		COMMAND_13_0003_O_1TANK_COMPRESSOR_IS_TIME_1MIN				0x0046//�ж�1min��ʱ
#define		COMMAND_13_0004_O_1TANK_IS_COMPRESSOR_START					0x0047//ͨ�����������ж������Ƿ�����

//�ж�ѹ��������ѹ���Ƿ�����
#define		COMMAND_13_0001_O_1TANK_IS_OUT_COMPRESSOR_PRESSURE			0x0048//�ж�ѹ��������ѹ���Ƿ�����

//����ѹ�������ڷ���
#define		COMMAND_13_0001_O_1TANK_OUT_COMPRESSOR_VALVE_ON				0x0049//����ѹ�������ڷ���
#define		COMMAND_13_0002_O_1TANK_IS_OUT_COMPRESSOR_VALVE_ON			0x004a//�жϿ���ѹ�������ڷ���

//�жϳ�����ƿ����
#define		COMMAND_13_0001_O_1TANK_NUMBER_COMP_GAS						0x004b//�жϳ�����ƿ����


//------------------------------command---һ���������----һ����ƿ����-----------------------------------

//������ƿ���ӷ���
#define		COMMAND_13_0001_O_1TANK_1GAS_IN_GAS_VALVE_ON				0x004c//������ƿ���ӷ���
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_ON				0x004d//�жϿ�����ƿ���ӷ���

//��ʱ�ȴ�time_delay2
#define		COMMAND_13_0001_O_1TANK_1GAS_TIME_DELAY2_START				0x004e//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_DELAY2					0x004f//�ж���ʱ�ȴ�time_delay2

//�ж���ƿѹ���Ƿ�����
#define		COMMAND_13_0001_O_1TANK_1GAS_GAS_PRESSURE_NO1				0x0050//�ɼ���ƿѹ������һ��
#define		COMMAND_13_0002_O_1TANK_1GAS_TIME_30S_START_NO1				0x0051//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_1TANK_1GAS_IS_TIME_30S_NO1				0x0052//�ж϶�ʱ30s����һ��
#define		COMMAND_13_0004_O_1TANK_1GAS_GAS_PRESSURE_NO2				0x0053//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_13_0005_O_1TANK_1GAS_TIME_30S_START_NO2				0x0054//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_TIME_30S_NO2				0x0055//�ж϶�ʱ30s���ڶ���
#define		COMMAND_13_0007_O_1TANK_1GAS_GAS_PRESSURE_NO3				0x0056//�ɼ���ƿѹ����������
#define		COMMAND_13_0008_O_1TANK_1GAS_TIME_30S_START_NO3				0x0057//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_1TANK_1GAS_IS_TIME_30S_NO3				0x0058//�ж϶�ʱ30s��������
#define		COMMAND_13_0010_O_1TANK_1GAS_GAS_PRESSURE_NO4				0x0059//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_13_0011_O_1TANK_1GAS_TIME_30S_START_NO4				0x005a//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_13_0012_O_1TANK_1GAS_IS_TIME_30S_NO4				0x005b//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_13_0013_O_1TANK_1GAS_GAS_PRESSURE_NO5				0x005c//�ɼ���ƿѹ���������
#define		COMMAND_13_0014_O_1TANK_1GAS_TIME_30S_START_NO5				0x005d//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_13_0015_O_1TANK_1GAS_IS_TIME_30S_NO5				0x005e//�ж϶�ʱ30s�������
#define		COMMAND_13_0016_O_1TANK_1GAS_GAS_PRESSURE_NO6				0x005f//�ɼ���ƿѹ����������
#define		COMMAND_13_0017_O_1TANK_1GAS_TIME_30S_START_NO6				0x0060//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0018_O_1TANK_1GAS_IS_TIME_30S_NO6				0x0061//�ж϶�ʱ30s��������
#define		COMMAND_13_0019_O_1TANK_1GAS_GAS_PRESSURE_NO7				0x0062//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_13_0020_O_1TANK_1GAS_TIME_30S_START_NO7				0x0063//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_13_0021_O_1TANK_1GAS_IS_TIME_30S_NO7				0x0064//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_13_0022_O_1TANK_1GAS_GAS_PRESSURE_NO8				0x0065//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_13_0023_O_1TANK_1GAS_TIME_30S_START_NO8				0x0066//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_13_0024_O_1TANK_1GAS_IS_TIME_30S_NO8				0x0067//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_13_0025_O_1TANK_1GAS_GAS_PRESSURE_NO9				0x0068//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_13_0026_O_1TANK_1GAS_TIME_30S_START_NO9				0x0069//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_13_0027_O_1TANK_1GAS_IS_TIME_30S_NO9				0x006a//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_13_0028_O_1TANK_1GAS_GAS_PRESSURE_NO10				0x006b//�ɼ���ƿѹ������ʮ��
#define		COMMAND_13_0029_O_1TANK_1GAS_IS_GAS_PRESSURE				0x006c//ѹ���ж���ƿѹ���Ƿ�����

//�ж���ƿ�����Ƿ����
#define		COMMAND_13_0001_O_1TANK_1GAS_IS_COMP_GAS_OVER				0x006d//�ж���ƿ�����Ƿ����

//����·��ƿ���ӷ���
#define		COMMAND_13_0001_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO1			0x006e//����·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO1		0x006f//�жϹ���·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO2			0x0070//����·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO2		0x0071//�жϹ���·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_1TANK_1GAS_IN_GAS_VALVE_OFF_NO3			0x0072//����·��ƿ���ӷ��ţ�������
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO3		0x0073//�жϹ���·��ƿ���ӷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define		COMMAND_13_0001_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO1	0x0074//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_13_0002_O_1TANK_1GAS_FIRST_TIME_12S_START_NO1		0x0075//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO1			0x0076//�ж϶�ʱ12s����һ��
#define		COMMAND_13_0004_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO2	0x0077//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_13_0005_O_1TANK_1GAS_FIRST_TIME_12S_START_NO2		0x0078//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO2			0x0079//�ж϶�ʱ12s���ڶ���
#define		COMMAND_13_0007_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO3	0x007a//�ɼ�ѹ��������ѹ����������
#define		COMMAND_13_0008_O_1TANK_1GAS_FIRST_TIME_12S_START_NO3		0x007b//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_1TANK_1GAS_FIRST_IS_TIME_12S_NO3			0x007c//�ж϶�ʱ12s��������
#define		COMMAND_13_0010_O_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO4	0x007d//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_13_0011_O_1TANK_1GAS_FIRST_IS_ISOLATION				0x007e//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//�ر���ѹ�������ڷ���
#define		COMMAND_13_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1			0x007f//�ر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x0080//�жϹر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2			0x0081//�ر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x0082//�жϹر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3			0x0083//�ر���ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x0084//�жϹر���ѹ�������ڷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���
#define		COMMAND_13_0001_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO1	0x0085//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_13_0002_O_1TANK_1GAS_SECOND_TIME_12S_START_NO1		0x0086//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO1			0x0087//�ж϶�ʱ12s����һ��
#define		COMMAND_13_0004_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO2	0x0088//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_13_0005_O_1TANK_1GAS_SECOND_TIME_12S_START_NO2		0x0089//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO2			0x008a//�ж϶�ʱ12s���ڶ���
#define		COMMAND_13_0007_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO3	0x008b//�ɼ�ѹ��������ѹ����������
#define		COMMAND_13_0008_O_1TANK_1GAS_SECOND_TIME_12S_START_NO3		0x008c//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_1TANK_1GAS_SECOND_IS_TIME_12S_NO3			0x008d//�ж϶�ʱ12s��������
#define		COMMAND_13_0010_O_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO4	0x008e//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_13_0011_O_1TANK_1GAS_SECOND_IS_ISOLATION			0x008f//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//��ѹ����ͣ��
#define		COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_STOP				0x0090//�����豸����ָ�ѹ����ͣ��
#define		COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START		0x0091//��ʱ1min��ʱ��ʼ
#define		COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN		0x0092//�ж�1min��ʱ

//�ж���ѹ����ͣ���Ƿ�����
#define		COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_V_NO1				0x0093//�ɼ����ת�٣���һ��
#define		COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_V_NO2				0x0094//�ɼ����ת�٣��ڶ���
#define		COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_V_NO3				0x0095//�ɼ����ת�٣�������
#define		COMMAND_13_0004_O_1TANK_1GAS_COMPRESSOR_V_NO4				0x0096//�ɼ����ת�٣����Ĵ�
#define		COMMAND_13_0005_O_1TANK_1GAS_COMPRESSOR_V_NO5				0x0097//�ɼ����ת�٣������
#define		COMMAND_13_0006_O_1TANK_1GAS_COMPRESSOR_V_NO6				0x0098//�ɼ����ת�٣�������
#define		COMMAND_13_0007_O_1TANK_1GAS_COMPRESSOR_V_NO7				0x0099//�ɼ����ת�٣����ߴ�
#define		COMMAND_13_0008_O_1TANK_1GAS_COMPRESSOR_V_NO8				0x009a//�ɼ����ת�٣��ڰ˴�
#define		COMMAND_13_0009_O_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO1	0x009b//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_13_0010_O_1TANK_1GAS_TIME_12S_START					0x009c//��ʱ12s��ʱ��ʼ
#define		COMMAND_13_0011_O_1TANK_1GAS_IS_TIME_12S					0x009d//�ж϶�ʱ12s
#define		COMMAND_13_0012_O_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO2	0x009e//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_13_0013_O_1TANK_1GAS_IS_COMPRESSOR_STOP				0x009f//�ж���ѹ����ͣ���Ƿ�����

//����ѹ������·������
#define		COMMAND_13_0001_O_1TANK_1GAS_BYPATH_VALVE_ON				0x00a0//����ѹ������·������
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_ON				0x00a1//�жϿ���ѹ������·������

//��ʱ�ȴ�time_bypath
#define		COMMAND_13_0001_O_1TANK_1GAS_TIME_BYPATH_START				0x00a2//��ʱ�ȴ�time_bypath��ʱ����
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_BYPATH					0x00a3//�ж���ʱ�ȴ�time_bypath

//����ѹ������·������
#define		COMMAND_13_0001_O_1TANK_1GAS_BYPATH_VALVE_OFF				0x00a4//����ѹ������·������
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_BYPATH_VALVE_OFF			0x00a5//�жϹ���ѹ������·������

//�ر���ѹ�������ڷ���
#define		COMMAND_13_0001_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1			0x00a6//�ر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x00a7//�жϹر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2			0x00a8//�ر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x00a9//�жϹر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3			0x00aa//�ر���ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x00ab//�жϹر���ѹ�������ڷ��ţ�������

//�ر���ѹ�������ڷ���
#define		COMMAND_13_0001_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x00ac//�ر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1		0x00ad//�жϹر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x00ae//�ر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2		0x00af//�жϹر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x00b0//�ر���ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3		0x00b1//�жϹر���ѹ�������ڷ��ţ�������

//�ؽ������ѹ��·���ӷ���
#define		COMMAND_13_0001_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO1				0x00b2//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO1			0x00b3//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO2				0x00b4//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO2			0x00b5//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_1TANK_1GAS_IN_TANK_VALVE_OFF_NO3				0x00b6//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO3			0x00b7//�жϹؽ������ѹ��·���ӷ��ţ�������

//����������״̬��
#define		COMMAND_13_0001_O_1TANK_1GAS_SET_STATE_GOOD						0x00b8//����������״̬��

//�ж�ѹ�����¶��Ƿ�����
#define		COMMAND_13_0001_O_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE			0x00b9//�ж�ѹ�����¶��Ƿ�����

//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��
#define		COMMAND_13_0001_O_1TANK_1GAS_IS_NEED_COOLER_STOP				0x00ba//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��

//��ʱ�ȴ�time_delay3
#define		COMMAND_13_0001_O_1TANK_1GAS_TIME_DELAY3_START					0x00bb//��ʱ�ȴ�time_delay3��ʱ��ʼ
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_TIME_DELAY3						0x00bc//�ж���ʱ�ȴ�time_delay3

/*
//����Һ��ģ���л�����
#define		COMMAND_13_0001_O_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO1			0x00bd//Һ��ģ���л����򣬷��Ŷ�������һ��
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x00be//�ж�Һ��ģ���л����򣬷��Ŷ�������һ��
#define		COMMAND_13_0003_O_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO2			0x00bf//Һ��ģ���л����򣬷��Ŷ������ڶ���
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x00c0//�ж�Һ��ģ���л����򣬷��Ŷ������ڶ���
#define		COMMAND_13_0005_O_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO3			0x00c1//Һ��ģ���л����򣬷��Ŷ�����������
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x00c2//�ж�Һ��ģ���л����򣬷��Ŷ�����������
#define		COMMAND_13_0007_O_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO4			0x00c3//Һ��ģ���л����򣬷��Ŷ�����������
#define		COMMAND_13_0008_O_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x00c4//�ж�Һ��ģ���л����򣬷��Ŷ�����������

//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		COMMAND_13_0001_O_1TANK_1GAS_IS_EXCHANGE_COOLER					0x00c5//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
*/


//Һ��ģ��ͣ��
#define		COMMAND_13_0001_O_1TANK_1GAS_COOLER_POWER_OFF					0x00c6//Һ��ģ��ͣ��

//Һ��ģ��״̬����
#define		COMMAND_13_0001_O_1TANK_1GAS_COOLER_SET_NO1						0x0400
#define		COMMAND_13_0002_O_1TANK_1GAS_IS_COOLER_SET_NO1					0x0401
#define		COMMAND_13_0003_O_1TANK_1GAS_COOLER_SET_NO2						0x0402
#define		COMMAND_13_0004_O_1TANK_1GAS_IS_COOLER_SET_NO2					0x0403
#define		COMMAND_13_0005_O_1TANK_1GAS_COOLER_SET_NO3						0x0404
#define		COMMAND_13_0006_O_1TANK_1GAS_IS_COOLER_SET_NO3					0x0405
#define		COMMAND_13_0007_O_1TANK_1GAS_COOLER_SET_NO4						0x0406
#define		COMMAND_13_0008_O_1TANK_1GAS_IS_COOLER_SET_NO4					0x0407
#define		COMMAND_13_0009_O_1TANK_1GAS_COOLER_SET_NO5						0x0408
#define		COMMAND_13_0010_O_1TANK_1GAS_IS_COOLER_SET_NO5					0x0409
#define		COMMAND_13_0011_O_1TANK_1GAS_COOLER_SET_NO6						0x040a
#define		COMMAND_13_0012_O_1TANK_1GAS_IS_COOLER_SET_NO6					0x040b
#define		COMMAND_13_0013_O_1TANK_1GAS_COOLER_SET_NO7						0x040c
#define		COMMAND_13_0014_O_1TANK_1GAS_IS_COOLER_SET_NO7					0x040d
#define		COMMAND_13_0015_O_1TANK_1GAS_COOLER_SET_NO8						0x040e
#define		COMMAND_13_0016_O_1TANK_1GAS_IS_COOLER_SET_NO8					0x040f
#define		COMMAND_13_0017_O_1TANK_1GAS_COOLER_SET_NO9						0x0411
#define		COMMAND_13_0018_O_1TANK_1GAS_IS_COOLER_SET_NO9					0x0412
#define		COMMAND_13_0019_O_1TANK_1GAS_COOLER_SET_NO10					0x0413
#define		COMMAND_13_0020_O_1TANK_1GAS_IS_COOLER_SET_NO10					0x0414
#define		COMMAND_13_0021_O_1TANK_1GAS_COOLER_SET_NO11					0x0415
#define		COMMAND_13_0022_O_1TANK_1GAS_IS_COOLER_SET_NO11					0x0416
#define		COMMAND_13_0023_O_1TANK_1GAS_COOLER_SET_NO12					0x0417
#define		COMMAND_13_0024_O_1TANK_1GAS_IS_COOLER_SET_NO12					0x0418



//����ѹ�����ϵ�
#define		COMMAND_13_0001_O_1TANK_1GAS_COMPRESSOR_POWER_OFF				0x00c7//�����豸����ָ��
//#define		COMMAND_13_0002_O_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START			0x00c8//��ʱ1min��ʱ��ʼ
//#define		COMMAND_13_0003_O_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN			0x00c9//�жϼ�ʱ1min�Ƿ�

//�������������ϵ�
#define		COMMAND_13_0001_O_1TANK_1GAS_TGTHT530_POWER_OFF					0x00ca//�����豸����ָ��
#define		COMMAND_13_0002_O_1TANK_1GAS_TGTHT530_TIME_1MIN_START			0x00cb//��ʱ1min��ʱ��ʼ
#define		COMMAND_13_0003_O_1TANK_1GAS_TGTHT530_IS_TIME_1MIN				0x00cc//�жϼ�ʱ1min�Ƿ�



//------------------------------command---һ���������----������ƿ����-----------------------------------

//������ƿ���ӷ���---��һ����ƿ
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON				0x00cd//������ƿ���ӷ���
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_ON			0x00ce//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---��һ����ƿ
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS1_TIME_DELAY2_START				0x00cf//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_TIME_DELAY2				0x00d0//�ж���ʱ�ȴ�time_delay2


//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO1				0x00d1//�ɼ���ƿѹ������һ��
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS1_TIME_30S_START_NO1			0x00d2//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO1				0x00d3//�ж϶�ʱ30s����һ��
#define		COMMAND_13_0004_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO2				0x00d4//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_13_0005_O_1TANK_2GAS_GAS1_TIME_30S_START_NO2			0x00d5//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO2				0x00d6//�ж϶�ʱ30s���ڶ���
#define		COMMAND_13_0007_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO3				0x00d7//�ɼ���ƿѹ����������
#define		COMMAND_13_0008_O_1TANK_2GAS_GAS1_TIME_30S_START_NO3			0x00d8//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO3				0x00d9//�ж϶�ʱ30s��������
#define		COMMAND_13_0010_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO4				0x00da//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_13_0011_O_1TANK_2GAS_GAS1_TIME_30S_START_NO4			0x00db//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_13_0012_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO4				0x00dc//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_13_0013_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO5				0x00dd//�ɼ���ƿѹ���������
#define		COMMAND_13_0014_O_1TANK_2GAS_GAS1_TIME_30S_START_NO5			0x00de//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_13_0015_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO5				0x00df//�ж϶�ʱ30s�������
#define		COMMAND_13_0016_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO6				0x00e0//�ɼ���ƿѹ����������
#define		COMMAND_13_0017_O_1TANK_2GAS_GAS1_TIME_30S_START_NO6			0x00e1//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0018_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO6				0x00e2//�ж϶�ʱ30s��������
#define		COMMAND_13_0019_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO7				0x00e3//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_13_0020_O_1TANK_2GAS_GAS1_TIME_30S_START_NO7			0x00e4//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_13_0021_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO7				0x00e5//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_13_0022_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO8				0x00e6//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_13_0023_O_1TANK_2GAS_GAS1_TIME_30S_START_NO8			0x00e7//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_13_0024_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO8				0x00e8//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_13_0025_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO9				0x00e9//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_13_0026_O_1TANK_2GAS_GAS1_TIME_30S_START_NO9			0x00ea//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_13_0027_O_1TANK_2GAS_GAS1_IS_TIME_30S_NO9				0x00eb//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_13_0028_O_1TANK_2GAS_GAS1_GAS_PRESSURE_NO10				0x00ec//�ɼ���ƿѹ������ʮ��
#define		COMMAND_13_0029_O_1TANK_2GAS_GAS1_IS_GAS_PRESSURE				0x00ed//ѹ���ж���ƿѹ���Ƿ�����


//�ж���ƿ�����Ƿ����---��һ����ƿ
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS1_IS_COMP_GAS_OVER				0x00ee//�ж���ƿ�����Ƿ����


//����·��ƿ���ӷ���---��һ����ƿ
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1			0x00ef//����·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1		0x00f0//�жϹ���·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2			0x00f1//����·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2		0x00f2//�жϹ���·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3			0x00f3//����·��ƿ���ӷ��ţ�������
#define		COMMAND_13_0006_O_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3		0x00f4//�жϹ���·��ƿ���ӷ��ţ�������



//������ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON				0x00f5//������ƿ���ӷ���
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_ON			0x00f6//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS2_TIME_DELAY2_START				0x00f7//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_TIME_DELAY2				0x00f8//�ж���ʱ�ȴ�time_delay2



//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO1				0x00f9//�ɼ���ƿѹ������һ��
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS2_TIME_30S_START_NO1			0x00fa//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO1				0x00fb//�ж϶�ʱ30s����һ��
#define		COMMAND_13_0004_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO2				0x00fc//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_13_0005_O_1TANK_2GAS_GAS2_TIME_30S_START_NO2			0x00fd//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO2				0x00fe//�ж϶�ʱ30s���ڶ���
#define		COMMAND_13_0007_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO3				0x00ff//�ɼ���ƿѹ����������
#define		COMMAND_13_0008_O_1TANK_2GAS_GAS2_TIME_30S_START_NO3			0x0100//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO3				0x0101//�ж϶�ʱ30s��������
#define		COMMAND_13_0010_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO4				0x0102//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_13_0011_O_1TANK_2GAS_GAS2_TIME_30S_START_NO4			0x0103//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_13_0012_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO4				0x0104//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_13_0013_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO5				0x0105//�ɼ���ƿѹ���������
#define		COMMAND_13_0014_O_1TANK_2GAS_GAS2_TIME_30S_START_NO5			0x0106//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_13_0015_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO5				0x0107//�ж϶�ʱ30s�������
#define		COMMAND_13_0016_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO6				0x0108//�ɼ���ƿѹ����������
#define		COMMAND_13_0017_O_1TANK_2GAS_GAS2_TIME_30S_START_NO6			0x0109//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0018_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO6				0x010a//�ж϶�ʱ30s��������
#define		COMMAND_13_0019_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO7				0x010b//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_13_0020_O_1TANK_2GAS_GAS2_TIME_30S_START_NO7			0x010c//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_13_0021_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO7				0x010d//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_13_0022_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO8				0x010e//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_13_0023_O_1TANK_2GAS_GAS2_TIME_30S_START_NO8			0x010f//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_13_0024_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO8				0x0110//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_13_0025_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO9				0x0111//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_13_0026_O_1TANK_2GAS_GAS2_TIME_30S_START_NO9			0x0112//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_13_0027_O_1TANK_2GAS_GAS2_IS_TIME_30S_NO9				0x0113//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_13_0028_O_1TANK_2GAS_GAS2_GAS_PRESSURE_NO10				0x0114//�ɼ���ƿѹ������ʮ��
#define		COMMAND_13_0029_O_1TANK_2GAS_GAS2_IS_GAS_PRESSURE				0x0115//ѹ���ж���ƿѹ���Ƿ�����

//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS2_IS_COMP_GAS_OVER				0x0116//�ж���ƿ�����Ƿ����


//����·��ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_13_0001_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1			0x0117//����·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1		0x0118//�жϹ���·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2			0x0119//����·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2		0x011a//�жϹ���·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3			0x011b//����·��ƿ���ӷ��ţ�������
#define		COMMAND_13_0006_O_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3		0x011c//�жϹ���·��ƿ���ӷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define		COMMAND_13_0001_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO1	0x011d//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_13_0002_O_1TANK_2GAS_FIRST_TIME_12S_START_NO1		0x011e//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO1			0x011f//�ж϶�ʱ12s����һ��
#define		COMMAND_13_0004_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO2	0x0120//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_13_0005_O_1TANK_2GAS_FIRST_TIME_12S_START_NO2		0x0121//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO2			0x0122//�ж϶�ʱ12s���ڶ���
#define		COMMAND_13_0007_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO3	0x0123//�ɼ�ѹ��������ѹ����������
#define		COMMAND_13_0008_O_1TANK_2GAS_FIRST_TIME_12S_START_NO3		0x0124//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_1TANK_2GAS_FIRST_IS_TIME_12S_NO3			0x0125//�ж϶�ʱ12s��������
#define		COMMAND_13_0010_O_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO4	0x0126//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_13_0011_O_1TANK_2GAS_FIRST_IS_ISOLATION				0x0127//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//�ر���ѹ�������ڷ���
#define		COMMAND_13_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x0128//�ر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1	0x0129//�жϹر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x012a//�ر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2	0x012b//�жϹر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x012c//�ر���ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3	0x012d//�жϹر���ѹ�������ڷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���
#define		COMMAND_13_0001_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO1	0x012e//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_13_0002_O_1TANK_2GAS_SECOND_TIME_12S_START_NO1		0x012f//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO1			0x0130//�ж϶�ʱ12s����һ��
#define		COMMAND_13_0004_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO2	0x0131//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_13_0005_O_1TANK_2GAS_SECOND_TIME_12S_START_NO2		0x0132//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO2			0x0133//�ж϶�ʱ12s���ڶ���
#define		COMMAND_13_0007_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO3	0x0134//�ɼ�ѹ��������ѹ����������
#define		COMMAND_13_0008_O_1TANK_2GAS_SECOND_TIME_12S_START_NO3		0x0135//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_1TANK_2GAS_SECOND_IS_TIME_12S_NO3			0x0136//�ж϶�ʱ12s��������
#define		COMMAND_13_0010_O_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO4	0x0137//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_13_0011_O_1TANK_2GAS_SECOND_IS_ISOLATION			0x0138//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//��ѹ����ͣ��
#define		COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_STOP					0x0139//�����豸����ָ�ѹ����ͣ��
#define		COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START			0x013a//��ʱ1min��ʱ��ʼ
#define		COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN			0x013b//�ж�1min��ʱ


//�ж���ѹ����ͣ���Ƿ�����
#define		COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_V_NO1					0x013c//�ɼ����ת�٣���һ��
#define		COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_V_NO2					0x013d//�ɼ����ת�٣��ڶ���
#define		COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_V_NO3					0x013e//�ɼ����ת�٣�������
#define		COMMAND_13_0004_O_1TANK_2GAS_COMPRESSOR_V_NO4					0x013f//�ɼ����ת�٣����Ĵ�
#define		COMMAND_13_0005_O_1TANK_2GAS_COMPRESSOR_V_NO5					0x0140//�ɼ����ת�٣������
#define		COMMAND_13_0006_O_1TANK_2GAS_COMPRESSOR_V_NO6					0x0141//�ɼ����ת�٣�������
#define		COMMAND_13_0007_O_1TANK_2GAS_COMPRESSOR_V_NO7					0x0142//�ɼ����ת�٣����ߴ�
#define		COMMAND_13_0008_O_1TANK_2GAS_COMPRESSOR_V_NO8					0x0143//�ɼ����ת�٣��ڰ˴�
#define		COMMAND_13_0009_O_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO1		0x0144//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_13_0010_O_1TANK_2GAS_TIME_12S_START						0x0145//��ʱ12s��ʱ��ʼ
#define		COMMAND_13_0011_O_1TANK_2GAS_IS_TIME_12S						0x0146//�ж϶�ʱ12s
#define		COMMAND_13_0012_O_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO2		0x0147//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_13_0013_O_1TANK_2GAS_IS_COMPRESSOR_STOP					0x0148//�ж���ѹ����ͣ���Ƿ�����


//����ѹ������·������
#define		COMMAND_13_0001_O_1TANK_2GAS_BYPATH_VALVE_ON					0x0149//����ѹ������·������
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_ON					0x014a//�жϿ���ѹ������·������


//��ʱ�ȴ�time_bypath
#define		COMMAND_13_0001_O_1TANK_2GAS_TIME_BYPATH_START					0x014b//��ʱ�ȴ�time_bypath��ʱ����
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_TIME_BYPATH						0x014c//�ж���ʱ�ȴ�time_bypath


//����ѹ������·������
#define		COMMAND_13_0001_O_1TANK_2GAS_BYPATH_VALVE_OFF					0x014d//����ѹ������·������
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_BYPATH_VALVE_OFF				0x014e//�жϹ���ѹ������·������

//�ر���ѹ�������ڷ���
#define		COMMAND_13_0001_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1			0x014f//�ر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x0150//�жϹر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2			0x0151//�ر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x0152//�жϹر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3			0x0153//�ر���ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x0154//�жϹر���ѹ�������ڷ��ţ�������

//�ر���ѹ�������ڷ���
#define		COMMAND_13_0001_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x0155//�ر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1		0x0156//�жϹر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0157//�ر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0158//�жϹر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x0159//�ر���ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3		0x015a//�жϹر���ѹ�������ڷ��ţ�������


//�ؽ������ѹ��·���ӷ���
#define		COMMAND_13_0001_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO1				0x015b//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO1			0x015c//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO2				0x015d//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO2			0x015e//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_1TANK_2GAS_IN_TANK_VALVE_OFF_NO3				0x015f//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_13_0006_O_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO3			0x0160//�жϹؽ������ѹ��·���ӷ��ţ�������


//����������״̬��
#define		COMMAND_13_0001_O_1TANK_2GAS_SET_STATE_GOOD						0x0161//����������״̬��


//�ж�ѹ�����¶��Ƿ�����
#define		COMMAND_13_0001_O_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE			0x0162//�ж�ѹ�����¶��Ƿ�����

//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��
#define		COMMAND_13_0001_O_1TANK_2GAS_IS_NEED_COOLER_STOP				0x0163//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��

//��ʱ�ȴ�time_delay3
#define		COMMAND_13_0001_O_1TANK_2GAS_TIME_DELAY3_START					0x0164//��ʱ�ȴ�time_delay3��ʱ��ʼ
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_TIME_DELAY3						0x0165//�ж���ʱ�ȴ�time_delay3


/*
//����Һ��ģ���л�����
#define		COMMAND_13_0001_O_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO1			0x0166//Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x0167//�ж�Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_13_0003_O_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO2			0x0168//Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_13_0004_O_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x0169//�ж�Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_13_0005_O_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO3			0x016a//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_13_0006_O_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x016b//�ж�Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_13_0007_O_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO4			0x016c//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_13_0008_O_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x016d//�ж�Һ��ģ���л�����,���Ŷ�����������

//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		COMMAND_13_0001_O_1TANK_2GAS_IS_EXCHANGE_COOLER					0x016e//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
*/


//Һ��ģ��ͣ��
#define		COMMAND_13_0001_O_1TANK_2GAS_COOLER_POWER_OFF					0x016f//Һ��ģ��ͣ��

//Һ��ģ��״̬����
#define		COMMAND_13_0001_O_1TANK_2GAS_COOLER_SET_NO1						0x0419
#define		COMMAND_13_0002_O_1TANK_2GAS_IS_COOLER_SET_NO1					0x041a
#define		COMMAND_13_0003_O_1TANK_2GAS_COOLER_SET_NO2						0x041b
#define		COMMAND_13_0004_O_1TANK_2GAS_IS_COOLER_SET_NO2					0x041c
#define		COMMAND_13_0005_O_1TANK_2GAS_COOLER_SET_NO3						0x041d
#define		COMMAND_13_0006_O_1TANK_2GAS_IS_COOLER_SET_NO3					0x041e
#define		COMMAND_13_0007_O_1TANK_2GAS_COOLER_SET_NO4						0x041f
#define		COMMAND_13_0008_O_1TANK_2GAS_IS_COOLER_SET_NO4					0x0420
#define		COMMAND_13_0009_O_1TANK_2GAS_COOLER_SET_NO5						0x0421
#define		COMMAND_13_0010_O_1TANK_2GAS_IS_COOLER_SET_NO5					0x0422
#define		COMMAND_13_0011_O_1TANK_2GAS_COOLER_SET_NO6						0x0423
#define		COMMAND_13_0012_O_1TANK_2GAS_IS_COOLER_SET_NO6					0x0424
#define		COMMAND_13_0013_O_1TANK_2GAS_COOLER_SET_NO7						0x0425
#define		COMMAND_13_0014_O_1TANK_2GAS_IS_COOLER_SET_NO7					0x0426
#define		COMMAND_13_0015_O_1TANK_2GAS_COOLER_SET_NO8						0x0427
#define		COMMAND_13_0016_O_1TANK_2GAS_IS_COOLER_SET_NO8					0x0428
#define		COMMAND_13_0017_O_1TANK_2GAS_COOLER_SET_NO9						0x0429
#define		COMMAND_13_0018_O_1TANK_2GAS_IS_COOLER_SET_NO9					0x042a
#define		COMMAND_13_0019_O_1TANK_2GAS_COOLER_SET_NO10					0x042b
#define		COMMAND_13_0020_O_1TANK_2GAS_IS_COOLER_SET_NO10					0x042c
#define		COMMAND_13_0021_O_1TANK_2GAS_COOLER_SET_NO11					0x042d
#define		COMMAND_13_0022_O_1TANK_2GAS_IS_COOLER_SET_NO11					0x042e
#define		COMMAND_13_0023_O_1TANK_2GAS_COOLER_SET_NO12					0x042f
#define		COMMAND_13_0024_O_1TANK_2GAS_IS_COOLER_SET_NO12					0x0430




//����ѹ�����ϵ�
#define		COMMAND_13_0001_O_1TANK_2GAS_COMPRESSOR_POWER_OFF				0x0170//�����豸����ָ��
//#define		COMMAND_13_0002_O_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START			0x0171//��ʱ1min��ʱ��ʼ
//#define		COMMAND_13_0003_O_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN			0x0172//�жϼ�ʱ1min�Ƿ�

//�������������ϵ�
#define		COMMAND_13_0001_O_1TANK_2GAS_TGTHT530_POWER_OFF					0x0173//�����豸����ָ��
#define		COMMAND_13_0002_O_1TANK_2GAS_TGTHT530_TIME_1MIN_START			0x0174//��ʱ1min��ʱ��ʼ
#define		COMMAND_13_0003_O_1TANK_2GAS_TGTHT530_IS_TIME_1MIN				0x0175//�жϼ�ʱ1min�Ƿ�


//------------------------------command---�����������----��һ���������-----------------------------------

//���������ѹ��·���ӷ���---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_IN_TANK_VALVE_ON					0x0176//���������ѹ��·���ӷ���
#define		COMMAND_13_0002_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON				0x0177//�жϿ��������ѹ��·���ӷ���


//ͨ��ѹ���жϿ������䷧��---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE		0x0178//ͨ��ѹ���жϿ����ӷ���


//����ѹ�������ڷ���---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO1		0x0179//����ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO1		0x017a//�жϿ���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO2		0x017b//����ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO2		0x017c//�жϿ���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO3		0x017d//����ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO3		0x017e//�жϿ���ѹ�������ڷ��ţ�������


//��ʱ�ȴ�time_delay1---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_TIME_DELAY1_START					0x017f//��ʱ�ȴ�time_delay1��ʱ��ʼ
#define		COMMAND_13_0002_O_2TANK_TANK1_IS_TIME_DELAY1					0x0180//�ж���ʱ�ȴ�time_delay1


//�ж�ѹ��������ѹ���Ƿ�����---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE			0x0181//�ж�ѹ��������ѹ���Ƿ�����


//��ѹ��������---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_COMPRESSOR_START					0x0182//�����豸����ָ�ѹ��������
#define		COMMAND_13_0002_O_2TANK_TANK1_COMPRESSOR_TIME_1MIN_START		0x0183//��ʱ1min��ʱ��ʼ
#define		COMMAND_13_0003_O_2TANK_TANK1_COMPRESSOR_IS_TIME_1MIN			0x0184//�ж�1min��ʱ
#define		COMMAND_13_0004_O_2TANK_TANK1_IS_COMPRESSOR_START				0x0185//ͨ�����������ж������Ƿ�����


//�ж�ѹ��������ѹ���Ƿ�����---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE		0x0186//�ж�ѹ��������ѹ���Ƿ�����


//����ѹ�������ڷ���---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON			0x0187//����ѹ�������ڷ���
#define		COMMAND_13_0002_O_2TANK_TANK1_IS_OUT_COMPRESSOR_VALVE_ON		0x0188//�жϿ���ѹ�������ڷ���


//�жϳ�����ƿ����---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_NUMBER_COMP_GAS					0x0189//�жϳ�����ƿ����


//------------------------------command---�����������----��һ���������----һ����ƿ����--------------------

//������ƿ���ӷ���---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON				0x018a//������ƿ���ӷ���
#define		COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_ON			0x018b//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_TIME_DELAY2_START			0x018c//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_TIME_DELAY2				0x018d//�ж���ʱ�ȴ�time_delay2


//�ж���ƿѹ���Ƿ�����---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO1				0x018e//�ɼ���ƿѹ������һ��
#define		COMMAND_13_0002_O_2TANK_TANK1_1GAS_TIME_30S_START_NO1			0x018f//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO1				0x0190//�ж϶�ʱ30s����һ��
#define		COMMAND_13_0004_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO2				0x0191//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK1_1GAS_TIME_30S_START_NO2			0x0192//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO2				0x0193//�ж϶�ʱ30s���ڶ���
#define		COMMAND_13_0007_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO3				0x0194//�ɼ���ƿѹ����������
#define		COMMAND_13_0008_O_2TANK_TANK1_1GAS_TIME_30S_START_NO3			0x0195//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO3				0x0196//�ж϶�ʱ30s��������
#define		COMMAND_13_0010_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO4				0x0197//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_13_0011_O_2TANK_TANK1_1GAS_TIME_30S_START_NO4			0x0198//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_13_0012_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO4				0x0199//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_13_0013_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO5				0x019a//�ɼ���ƿѹ���������
#define		COMMAND_13_0014_O_2TANK_TANK1_1GAS_TIME_30S_START_NO5			0x019b//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_13_0015_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO5				0x019c//�ж϶�ʱ30s�������
#define		COMMAND_13_0016_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO6				0x019d//�ɼ���ƿѹ����������
#define		COMMAND_13_0017_O_2TANK_TANK1_1GAS_TIME_30S_START_NO6			0x019e//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0018_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO6				0x019f//�ж϶�ʱ30s��������
#define		COMMAND_13_0019_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO7				0x01a0//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_13_0020_O_2TANK_TANK1_1GAS_TIME_30S_START_NO7			0x01a1//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_13_0021_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO7				0x01a2//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_13_0022_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO8				0x01a3//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_13_0023_O_2TANK_TANK1_1GAS_TIME_30S_START_NO8			0x01a4//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_13_0024_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO8				0x01a5//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_13_0025_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO9				0x01a6//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_13_0026_O_2TANK_TANK1_1GAS_TIME_30S_START_NO9			0x01a7//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_13_0027_O_2TANK_TANK1_1GAS_IS_TIME_30S_NO9				0x01a8//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_13_0028_O_2TANK_TANK1_1GAS_GAS_PRESSURE_NO10			0x01a9//�ɼ���ƿѹ������ʮ��
#define		COMMAND_13_0029_O_2TANK_TANK1_1GAS_IS_GAS_PRESSURE				0x01aa//ѹ���ж���ƿѹ���Ƿ�����

//�ж���ƿ�����Ƿ����---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_IS_COMP_GAS_OVER				0x01ab//�ж���ƿ�����Ƿ����


//����·��ƿ���ӷ���---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO1			0x01ac//����·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO1		0x01ad//�жϹ���·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO2			0x01ae//����·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO2		0x01af//�жϹ���·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO3			0x01b0//����·��ƿ���ӷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO3		0x01b1//�жϹ���·��ƿ���ӷ��ţ�������


//�ؽ������ѹ��·���ӷ���---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO1			0x01b2//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO1			0x01b3//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO2			0x01b4//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO2			0x01b5//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO3			0x01b6//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO3			0x01b7//�жϹؽ������ѹ��·���ӷ��ţ�������

//ͨ��ѹ���жϹؽ����䲹�ӷ�---��һ������
#define		COMMAND_13_0001_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO1	0x01b8//ͨ��ѹ���жϹؽ����䲹�ӷ�����һ��
#define		COMMAND_13_0002_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO2	0x01b9//ͨ��ѹ���жϹؽ����䲹�ӷ����ڶ���
#define		COMMAND_13_0003_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO3	0x01ba//ͨ��ѹ���жϹؽ����䲹�ӷ���������
#define		COMMAND_13_0004_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO4	0x01bb//ͨ��ѹ���жϹؽ����䲹�ӷ���������
#define		COMMAND_13_0005_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO5	0x01bc//ͨ��ѹ���жϹؽ����䲹�ӷ���������
#define		COMMAND_13_0006_O_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE		0x01bd//ͨ��ѹ���жϹؽ����䲹�ӷ�����ȡ��


//------------------------------command---�����������----��һ���������----������ƿ����--------------------

//������ƿ���ӷ���---��һ����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON				0x01be//������ƿ���ӷ���
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_ON			0x01bf//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---��һ����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2_START			0x01c0//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_DELAY2				0x01c1//�ж���ʱ�ȴ�time_delay2

//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO1			0x01c2//�ɼ���ƿѹ������һ��
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO1			0x01c3//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO1				0x01c4//�ж϶�ʱ30s����һ��
#define		COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO2			0x01c5//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO2			0x01c6//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO2				0x01c7//�ж϶�ʱ30s���ڶ���
#define		COMMAND_13_0007_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO3			0x01c8//�ɼ���ƿѹ����������
#define		COMMAND_13_0008_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO3			0x01c9//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO3				0x01ca//�ж϶�ʱ30s��������
#define		COMMAND_13_0010_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO4			0x01cb//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_13_0011_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO4			0x01cc//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_13_0012_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO4				0x01cd//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_13_0013_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO5			0x01ce//�ɼ���ƿѹ���������
#define		COMMAND_13_0014_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO5			0x01cf//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_13_0015_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO5				0x01d0//�ж϶�ʱ30s�������
#define		COMMAND_13_0016_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO6			0x01d1//�ɼ���ƿѹ����������
#define		COMMAND_13_0017_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO6			0x01d2//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0018_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO6				0x01d3//�ж϶�ʱ30s��������
#define		COMMAND_13_0019_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO7			0x01d4//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_13_0020_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO7			0x01d5//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_13_0021_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO7				0x01d6//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_13_0022_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO8			0x01d7//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_13_0023_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO8			0x01d8//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_13_0024_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO8				0x01d9//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_13_0025_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO9			0x01da//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_13_0026_O_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO9			0x01db//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_13_0027_O_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO9				0x01dc//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_13_0028_O_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO10			0x01dd//�ɼ���ƿѹ������ʮ��
#define		COMMAND_13_0029_O_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE				0x01de//ѹ���ж���ƿѹ���Ƿ�����

//�ж���ƿ�����Ƿ����---��һ����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IS_COMP_GAS_OVER			0x01df//�ж���ƿ�����Ƿ����


//����·��ƿ���ӷ���---��һ����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1		0x01e0//����·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1		0x01e1//�жϹ���·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2		0x01e2//����·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2		0x01e3//�жϹ���·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3		0x01e4//����·��ƿ���ӷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3		0x01e5//�жϹ���·��ƿ���ӷ��ţ�������


//������ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON				0x01e6//������ƿ���ӷ���
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_ON			0x01e7//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2_START			0x01e8//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_DELAY2				0x01e9//�ж���ʱ�ȴ�time_delay2


//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO1			0x01ea//�ɼ���ƿѹ������һ��
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO1			0x01eb//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO1				0x01ec//�ж϶�ʱ30s����һ��
#define		COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO2			0x01ed//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO2			0x01ee//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO2				0x01ef//�ж϶�ʱ30s���ڶ���
#define		COMMAND_13_0007_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO3			0x01f0//�ɼ���ƿѹ����������
#define		COMMAND_13_0008_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO3			0x01f1//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO3				0x01f2//�ж϶�ʱ30s��������
#define		COMMAND_13_0010_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO4			0x01f3//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_13_0011_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO4			0x01f4//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_13_0012_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO4				0x01f5//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_13_0013_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO5			0x01f6//�ɼ���ƿѹ���������
#define		COMMAND_13_0014_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO5			0x01f7//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_13_0015_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO5				0x01f8//�ж϶�ʱ30s�������
#define		COMMAND_13_0016_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO6			0x01f9//�ɼ���ƿѹ����������
#define		COMMAND_13_0017_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO6			0x01fa//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0018_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO6				0x01fb//�ж϶�ʱ30s��������
#define		COMMAND_13_0019_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO7			0x01fc//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_13_0020_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO7			0x01fd//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_13_0021_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO7				0x01fe//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_13_0022_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO8			0x01ff//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_13_0023_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO8			0x0200//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_13_0024_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO8				0x0201//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_13_0025_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO9			0x0202//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_13_0026_O_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO9			0x0203//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_13_0027_O_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO9				0x0204//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_13_0028_O_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO10			0x0205//�ɼ���ƿѹ������ʮ��
#define		COMMAND_13_0029_O_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE				0x0206//ѹ���ж���ƿѹ���Ƿ�����


//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IS_COMP_GAS_OVER			0x0207//�ж���ƿ�����Ƿ����

//����·��ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1		0x0208//����·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1		0x0209//�жϹ���·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2		0x020a//����·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2		0x020b//�жϹ���·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3		0x020c//����·��ƿ���ӷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3		0x020d//�жϹ���·��ƿ���ӷ��ţ�������


//�ؽ������ѹ��·���ӷ���
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO1			0x020e//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO1			0x020f//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO2			0x0210//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO2			0x0211//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO3			0x0212//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO3			0x0213//�жϹؽ������ѹ��·���ӷ��ţ�������


//ͨ��ѹ���жϹؽ����䲹�ӷ�
#define		COMMAND_13_0001_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO1	0x0214//ͨ��ѹ���жϹؽ����䲹�ӷ�����һ��
#define		COMMAND_13_0002_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO2	0x0215//ͨ��ѹ���жϹؽ����䲹�ӷ����ڶ���
#define		COMMAND_13_0003_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO3	0x0216//ͨ��ѹ���жϹؽ����䲹�ӷ���������
#define		COMMAND_13_0004_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO4	0x0217//ͨ��ѹ���жϹؽ����䲹�ӷ���������
#define		COMMAND_13_0005_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO5	0x0218//ͨ��ѹ���жϹؽ����䲹�ӷ���������
#define		COMMAND_13_0006_O_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE		0x0219//ͨ��ѹ���жϹؽ����䲹�ӷ�����ȡ��


//------------------------------command---�����������----�ڶ����������-----------------------------------

//���������ѹ��·���ӷ���---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_IN_TANK_VALVE_ON					0x021a//���������ѹ��·���ӷ���
#define		COMMAND_13_0002_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON				0x021b//�жϿ��������ѹ��·���ӷ���


//ͨ��ѹ���жϿ������䷧��---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE		0x021c//ͨ��ѹ���жϿ����ӷ���

//�жϳ�����ƿ����---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_NUMBER_COMP_GAS					0x021d//�жϳ�����ƿ����


//------------------------------command---�����������----�ڶ����������----һ����ƿ����--------------------

//������ƿ���ӷ���---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON				0x021e//������ƿ���ӷ���
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_ON			0x021f//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_DELAY2_START			0x0220//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_DELAY2				0x0221//�ж���ʱ�ȴ�time_delay2


//�ж���ƿѹ���Ƿ�����---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO1				0x0222//�ɼ���ƿѹ������һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_TIME_30S_START_NO1			0x0223//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO1				0x0224//�ж϶�ʱ30s����һ��
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO2				0x0225//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_TIME_30S_START_NO2			0x0226//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO2				0x0227//�ж϶�ʱ30s���ڶ���
#define		COMMAND_13_0007_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO3				0x0228//�ɼ���ƿѹ����������
#define		COMMAND_13_0008_O_2TANK_TANK2_1GAS_TIME_30S_START_NO3			0x0229//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO3				0x022a//�ж϶�ʱ30s��������
#define		COMMAND_13_0010_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO4				0x022b//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_13_0011_O_2TANK_TANK2_1GAS_TIME_30S_START_NO4			0x022c//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_13_0012_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO4				0x022d//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_13_0013_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO5				0x022e//�ɼ���ƿѹ���������
#define		COMMAND_13_0014_O_2TANK_TANK2_1GAS_TIME_30S_START_NO5			0x022f//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_13_0015_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO5				0x0230//�ж϶�ʱ30s�������
#define		COMMAND_13_0016_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO6				0x0231//�ɼ���ƿѹ����������
#define		COMMAND_13_0017_O_2TANK_TANK2_1GAS_TIME_30S_START_NO6			0x0232//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0018_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO6				0x0233//�ж϶�ʱ30s��������
#define		COMMAND_13_0019_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO7				0x0234//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_13_0020_O_2TANK_TANK2_1GAS_TIME_30S_START_NO7			0x0235//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_13_0021_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO7				0x0236//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_13_0022_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO8				0x0237//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_13_0023_O_2TANK_TANK2_1GAS_TIME_30S_START_NO8			0x0238//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_13_0024_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO8				0x0239//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_13_0025_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO9				0x023a//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_13_0026_O_2TANK_TANK2_1GAS_TIME_30S_START_NO9			0x023b//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_13_0027_O_2TANK_TANK2_1GAS_IS_TIME_30S_NO9				0x023c//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_13_0028_O_2TANK_TANK2_1GAS_GAS_PRESSURE_NO10			0x023d//�ɼ���ƿѹ������ʮ��
#define		COMMAND_13_0029_O_2TANK_TANK2_1GAS_IS_GAS_PRESSURE				0x023e//ѹ���ж���ƿѹ���Ƿ�����


//�ж���ƿ�����Ƿ����---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_COMP_GAS_OVER				0x023f//�ж���ƿ�����Ƿ����


//����·��ƿ���ӷ���---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO1			0x0240//����·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO1		0x0241//�жϹ���·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO2			0x0242//����·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO2		0x0243//�жϹ���·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO3			0x0244//����·��ƿ���ӷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO3		0x0245//�жϹ���·��ƿ���ӷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO1	0x0246//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO1		0x0247//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO1		0x0248//�ж϶�ʱ12s����һ��
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO2	0x0249//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO2		0x024a//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO2		0x024b//�ж϶�ʱ12s���ڶ���
#define		COMMAND_13_0007_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO3	0x024c//�ɼ�ѹ��������ѹ����������
#define		COMMAND_13_0008_O_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO3		0x024d//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO3		0x024e//�ж϶�ʱ12s��������
#define		COMMAND_13_0010_O_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO4	0x024f//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_13_0011_O_2TANK_TANK2_1GAS_FIRST_IS_ISOLATION			0x0250//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//�ر���ѹ�������ڷ���---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x0251//�ر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1	0x0252//�жϹر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x0253//�ر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2	0x0254//�жϹر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x0255//�ر���ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3	0x0256//�жϹر���ѹ�������ڷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO1	0x0257//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO1		0x0258//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO1			0x0259//�ж϶�ʱ12s����һ��
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO2	0x025a//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO2		0x025b//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO2			0x025c//�ж϶�ʱ12s���ڶ���
#define		COMMAND_13_0007_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO3	0x025d//�ɼ�ѹ��������ѹ����������
#define		COMMAND_13_0008_O_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO3		0x025e//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO3			0x025f//�ж϶�ʱ12s��������
#define		COMMAND_13_0010_O_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO4	0x0260//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_13_0011_O_2TANK_TANK2_1GAS_SECOND_IS_ISOLATION				0x0261//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//��ѹ����ͣ��---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_STOP					0x0262//�����豸����ָ�ѹ����ͣ��
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START		0x0263//��ʱ1min��ʱ��ʼ
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN			0x0264//�ж�1min��ʱ


//�ж���ѹ����ͣ���Ƿ�����---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO1					0x0265//�ɼ����ת�٣���һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO2					0x0266//�ɼ����ת�٣��ڶ���
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO3					0x0267//�ɼ����ת�٣�������
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO4					0x0268//�ɼ����ת�٣����Ĵ�
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO5					0x0269//�ɼ����ת�٣������
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO6					0x026a//�ɼ����ת�٣�������
#define		COMMAND_13_0007_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO7					0x026b//�ɼ����ת�٣����ߴ�
#define		COMMAND_13_0008_O_2TANK_TANK2_1GAS_COMPRESSOR_V_NO8					0x026c//�ɼ����ת�٣��ڰ˴�
#define		COMMAND_13_0009_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_PRESSURE_NO1		0x026d//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_13_0010_O_2TANK_TANK2_1GAS_TIME_12S_START					0x026e//��ʱ12s��ʱ��ʼ
#define		COMMAND_13_0011_O_2TANK_TANK2_1GAS_IS_TIME_12S						0x026f//�ж϶�ʱ12s
#define		COMMAND_13_0012_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_PRESSURE_NO2		0x0270//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_13_0013_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_STOP				0x0271//�ж���ѹ����ͣ���Ƿ�����


//����ѹ������·������---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_BYPATH_VALVE_ON					0x0272//����ѹ������·������
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_ON				0x0273//�жϿ���ѹ������·������


//��ʱ�ȴ�time_bypath---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_BYPATH_START				0x0274//��ʱ�ȴ�time_bypath��ʱ����
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_BYPATH					0x0275//�ж���ʱ�ȴ�time_bypath


//����ѹ������·������---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF					0x0276//����ѹ������·������
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_OFF				0x0277//�жϹ���ѹ������·������

//�ر���ѹ�������ڷ���
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x0278//�ر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x0279//�жϹر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x027a//�ر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x027b//�жϹر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x027c//�ر���ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x027d//�жϹر���ѹ�������ڷ��ţ�������

//�ر���ѹ�������ڷ���
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x027e//�ر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1	0x027f//�жϹر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0280//�ر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2	0x0281//�жϹر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x0282//�ر���ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3	0x0283//�жϹر���ѹ�������ڷ��ţ�������


//�ؽ������ѹ��·���ӷ���---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO1			0x0284//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO1			0x0285//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO2			0x0286//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO2			0x0287//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO3			0x0288//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO3			0x0289//�жϹؽ������ѹ��·���ӷ��ţ�������


//����������״̬��---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_SET_STATE_GOOD					0x028a//����������״̬��


//�ж�ѹ�����¶��Ƿ�����---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE		0x028b//�ж�ѹ�����¶��Ƿ�����

//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_NEED_COOLER_STOP				0x028c//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��

//��ʱ�ȴ�time_delay3---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_TIME_DELAY3_START				0x028d//��ʱ�ȴ�time_delay3��ʱ��ʼ
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_TIME_DELAY3					0x028e//�ж���ʱ�ȴ�time_delay3



/*
//����Һ��ģ���л�����---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_EXCHANGE_COOLER_VALVE_NO1		0x028f//Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x0290//�ж�Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_EXCHANGE_COOLER_VALVE_NO2		0x0291//Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x0292//�ж�Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_EXCHANGE_COOLER_VALVE_NO3		0x0293//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x0294//�ж�Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_13_0007_O_2TANK_TANK2_1GAS_EXCHANGE_COOLER_VALVE_NO4		0x0295//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_13_0008_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x0296//�ж�Һ��ģ���л�����,���Ŷ�����������


//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����---�ڶ�������
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER				0x0297//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
*/


//Һ��ģ��ͣ��
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_COOLER_POWER_OFF					0x0298//Һ��ģ��ͣ��

//Һ��ģ��״̬����
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_COOLER_SET_NO1					0x0431
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO1				0x0432
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_COOLER_SET_NO2					0x0433
#define		COMMAND_13_0004_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO2				0x0434
#define		COMMAND_13_0005_O_2TANK_TANK2_1GAS_COOLER_SET_NO3					0x0435
#define		COMMAND_13_0006_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO3				0x0436
#define		COMMAND_13_0007_O_2TANK_TANK2_1GAS_COOLER_SET_NO4					0x0437
#define		COMMAND_13_0008_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO4				0x0438
#define		COMMAND_13_0009_O_2TANK_TANK2_1GAS_COOLER_SET_NO5					0x0439
#define		COMMAND_13_0010_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO5				0x043a
#define		COMMAND_13_0011_O_2TANK_TANK2_1GAS_COOLER_SET_NO6					0x043b
#define		COMMAND_13_0012_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO6				0x043c
#define		COMMAND_13_0013_O_2TANK_TANK2_1GAS_COOLER_SET_NO7					0x043d
#define		COMMAND_13_0014_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO7				0x043e
#define		COMMAND_13_0015_O_2TANK_TANK2_1GAS_COOLER_SET_NO8					0x043f
#define		COMMAND_13_0016_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO8				0x0440
#define		COMMAND_13_0017_O_2TANK_TANK2_1GAS_COOLER_SET_NO9					0x0441
#define		COMMAND_13_0018_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO9				0x0442
#define		COMMAND_13_0019_O_2TANK_TANK2_1GAS_COOLER_SET_NO10					0x0443
#define		COMMAND_13_0020_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO10				0x0444
#define		COMMAND_13_0021_O_2TANK_TANK2_1GAS_COOLER_SET_NO11					0x0445
#define		COMMAND_13_0022_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO11				0x0446
#define		COMMAND_13_0023_O_2TANK_TANK2_1GAS_COOLER_SET_NO12					0x0447
#define		COMMAND_13_0024_O_2TANK_TANK2_1GAS_IS_COOLER_SET_NO12				0x0448


//����ѹ�����ϵ�
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF				0x0299//�����豸����ָ��
//#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START		0x029a//��ʱ1min��ʱ��ʼ
//#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN			0x029b//�жϼ�ʱ1min�Ƿ�

//�������������ϵ�
#define		COMMAND_13_0001_O_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF				0x029c//�����豸����ָ��
#define		COMMAND_13_0002_O_2TANK_TANK2_1GAS_TGTHT530_TIME_1MIN_START			0x029d//��ʱ1min��ʱ��ʼ
#define		COMMAND_13_0003_O_2TANK_TANK2_1GAS_TGTHT530_IS_TIME_1MIN			0x029e//�жϼ�ʱ1min�Ƿ�


//------------------------------command---�����������----�ڶ����������----������ƿ����--------------------

//������ƿ���ӷ���---��һ����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON				0x029f//������ƿ���ӷ���
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_ON			0x02a0//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---��һ����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2_START			0x02a1//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_DELAY2				0x02a2//�ж���ʱ�ȴ�time_delay2


//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO1			0x02a3//�ɼ���ƿѹ������һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO1			0x02a4//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO1				0x02a5//�ж϶�ʱ30s����һ��
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO2			0x02a6//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO2			0x02a7//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO2				0x02a8//�ж϶�ʱ30s���ڶ���
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO3			0x02a9//�ɼ���ƿѹ����������
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO3			0x02aa//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO3				0x02ab//�ж϶�ʱ30s��������
#define		COMMAND_13_0010_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO4			0x02ac//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_13_0011_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO4			0x02ad//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_13_0012_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO4				0x02ae//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_13_0013_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO5			0x02af//�ɼ���ƿѹ���������
#define		COMMAND_13_0014_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO5			0x02b0//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_13_0015_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO5				0x02b1//�ж϶�ʱ30s�������
#define		COMMAND_13_0016_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO6			0x02b2//�ɼ���ƿѹ����������
#define		COMMAND_13_0017_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO6			0x02b3//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0018_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO6				0x02b4//�ж϶�ʱ30s��������
#define		COMMAND_13_0019_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO7			0x02b5//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_13_0020_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO7			0x02b6//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_13_0021_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO7				0x02b7//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_13_0022_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO8			0x02b8//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_13_0023_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO8			0x02b9//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_13_0024_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO8				0x02ba//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_13_0025_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO9			0x02bb//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_13_0026_O_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO9			0x02bc//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_13_0027_O_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO9				0x02bd//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_13_0028_O_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO10			0x02be//�ɼ���ƿѹ������ʮ��
#define		COMMAND_13_0029_O_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE				0x02bf//ѹ���ж���ƿѹ���Ƿ�����


//�ж���ƿ�����Ƿ����---��һ����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IS_COMP_GAS_OVER			0x02c0//�ж���ƿ�����Ƿ����


//����·��ƿ���ӷ���---��һ����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1		0x02c1//����·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1		0x02c2//�жϹ���·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2		0x02c3//����·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2		0x02c4//�жϹ���·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3		0x02c5//����·��ƿ���ӷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3		0x02c6//�жϹ���·��ƿ���ӷ��ţ�������


//������ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON				0x02c7//������ƿ���ӷ���
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_ON			0x02c8//�жϿ�����ƿ���ӷ���

//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2_START			0x02c9//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_DELAY2				0x02ca//�ж���ʱ�ȴ�time_delay2


//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO1			0x02cb//�ɼ���ƿѹ������һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO1			0x02cc//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO1				0x02cd//�ж϶�ʱ30s����һ��
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO2			0x02ce//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO2			0x02cf//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO2				0x02d0//�ж϶�ʱ30s���ڶ���
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO3			0x02d1//�ɼ���ƿѹ����������
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO3			0x02d2//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO3				0x02d3//�ж϶�ʱ30s��������
#define		COMMAND_13_0010_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO4			0x02d4//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_13_0011_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO4			0x02d5//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_13_0012_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO4				0x02d6//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_13_0013_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO5			0x02d7//�ɼ���ƿѹ���������
#define		COMMAND_13_0014_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO5			0x02d8//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_13_0015_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO5				0x02d9//�ж϶�ʱ30s�������
#define		COMMAND_13_0016_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO6			0x02da//�ɼ���ƿѹ����������
#define		COMMAND_13_0017_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO6			0x02db//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_13_0018_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO6				0x02dc//�ж϶�ʱ30s��������
#define		COMMAND_13_0019_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO7			0x02dd//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_13_0020_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO7			0x02de//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_13_0021_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO7				0x02df//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_13_0022_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO8			0x02e0//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_13_0023_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO8			0x02e1//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_13_0024_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO8				0x02e2//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_13_0025_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO9			0x02e3//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_13_0026_O_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO9			0x02e4//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_13_0027_O_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO9				0x02e5//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_13_0028_O_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO10			0x02e6//�ɼ���ƿѹ������ʮ��
#define		COMMAND_13_0029_O_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE				0x02e7//ѹ���ж���ƿѹ���Ƿ�����


//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IS_COMP_GAS_OVER			0x02e8//�ж���ƿ�����Ƿ����


//����·��ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1		0x02e9//����·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1		0x02ea//�жϹ���·��ƿ���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2		0x02eb//����·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2		0x02ec//�жϹ���·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3		0x02ed//����·��ƿ���ӷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3		0x02ee//�жϹ���·��ƿ���ӷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO1		0x02ef//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO1			0x02f0//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO1			0x02f1//�ж϶�ʱ12s����һ��
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO2		0x02f2//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO2			0x02f3//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO2			0x02f4//�ж϶�ʱ12s���ڶ���
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO3		0x02f5//�ɼ�ѹ��������ѹ����������
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO3			0x02f6//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO3			0x02f7//�ж϶�ʱ12s��������
#define		COMMAND_13_0010_O_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO4		0x02f8//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_13_0011_O_2TANK_TANK2_2GAS_FIRST_IS_ISOLATION				0x02f9//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//�ر���ѹ�������ڷ���
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x02fa//�ر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1	0x02fb//�жϹر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x02fc//�ر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2	0x02fd//�жϹر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x02fe//�ر���ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3	0x02ff//�жϹر���ѹ�������ڷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������2��
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO1	0x0300//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO1		0x0301//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO1			0x0302//�ж϶�ʱ12s����һ��
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO2	0x0303//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO2		0x0304//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO2			0x0305//�ж϶�ʱ12s���ڶ���
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO3	0x0306//�ɼ�ѹ��������ѹ����������
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO3		0x0307//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_13_0009_O_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO3			0x0308//�ж϶�ʱ12s��������
#define		COMMAND_13_0010_O_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO4	0x0309//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_13_0011_O_2TANK_TANK2_2GAS_SECOND_IS_ISOLATION				0x030a//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//��ѹ����ͣ��
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_STOP					0x030b//�����豸����ָ�ѹ����ͣ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START		0x030c//��ʱ1min��ʱ��ʼ
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN			0x030d//�ж�1min��ʱ


//�ж���ѹ����ͣ���Ƿ�����
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO1					0x030e//�ɼ����ת�٣���һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO2					0x030f//�ɼ����ת�٣��ڶ���
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO3					0x0310//�ɼ����ת�٣�������
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO4					0x0311//�ɼ����ת�٣����Ĵ�
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO5					0x0312//�ɼ����ת�٣������
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO6					0x0313//�ɼ����ת�٣�������
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO7					0x0314//�ɼ����ת�٣����ߴ�
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_COMPRESSOR_V_NO8					0x0315//�ɼ����ת�٣��ڰ˴�
#define		COMMAND_13_0009_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_PRESSURE_NO1		0x0316//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_13_0010_O_2TANK_TANK2_2GAS_TIME_12S_START					0x0317//��ʱ12s��ʱ��ʼ
#define		COMMAND_13_0011_O_2TANK_TANK2_2GAS_IS_TIME_12S						0x0318//�ж϶�ʱ12s
#define		COMMAND_13_0012_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_PRESSURE_NO2		0x0319//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_13_0013_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_STOP				0x031a//�ж���ѹ����ͣ���Ƿ�����


//����ѹ������·������
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_BYPATH_VALVE_ON					0x031b//����ѹ������·������
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_ON				0x031c//�жϿ���ѹ������·������


//��ʱ�ȴ�time_bypath
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_TIME_BYPATH_START				0x031d//��ʱ�ȴ�time_bypath��ʱ����
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_TIME_BYPATH					0x031e//�ж���ʱ�ȴ�time_bypath


//����ѹ������·������
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF					0x031f//����ѹ������·������
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_OFF				0x0320//�жϹ���ѹ������·������

//�ر���ѹ�������ڷ���
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1	0x0321//�ر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1	0x0322//�жϹر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2	0x0323//�ر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2	0x0324//�жϹر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3	0x0325//�ر���ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3	0x0326//�жϹر���ѹ�������ڷ��ţ�������


//�ر���ѹ�������ڷ���
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x0327//�ر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1	0x0328//�жϹر���ѹ�������ڷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0329//�ر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2	0x032a//�жϹر���ѹ�������ڷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x032b//�ر���ѹ�������ڷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3	0x032c//�жϹر���ѹ�������ڷ��ţ�������


//�ؽ������ѹ��·���ӷ���
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO1			0x032d//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO1			0x032e//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO2			0x032f//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO2			0x0330//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO3			0x0331//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO3			0x0332//�жϹؽ������ѹ��·���ӷ��ţ�������


//����������״̬��
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_SET_STATE_GOOD					0x0333//����������״̬��


//�ж�ѹ�����¶��Ƿ�����
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE		0x0334//�ж�ѹ�����¶��Ƿ�����

//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_NEED_COOLER_STOP				0x0335//�ж��Ƿ���Ҫ����Һ��ģ��ͣ��

//��ʱ�ȴ�time_delay3
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_TIME_DELAY3_START				0x0336//��ʱ�ȴ�time_delay3��ʱ��ʼ
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_TIME_DELAY3					0x0337//�ж���ʱ�ȴ�time_delay3


/*
//����Һ��ģ���л�����
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_EXCHANGE_COOLER_VALVE_NO1		0x0338//Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x0339//�ж�Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_EXCHANGE_COOLER_VALVE_NO2		0x033a//Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x033b//�ж�Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_EXCHANGE_COOLER_VALVE_NO3		0x033c//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x033d//�ж�Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_EXCHANGE_COOLER_VALVE_NO4		0x033e//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x033f//�ж�Һ��ģ���л�����,���Ŷ�����������

//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER				0x0340//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
*/


//Һ��ģ��ͣ��
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_COOLER_POWER_OFF					0x0341//Һ��ģ��ͣ��


//Һ��ģ��״̬����
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_COOLER_SET_NO1					0x0449
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO1				0x044a
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_COOLER_SET_NO2					0x044b
#define		COMMAND_13_0004_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO2				0x044c
#define		COMMAND_13_0005_O_2TANK_TANK2_2GAS_COOLER_SET_NO3					0x044d
#define		COMMAND_13_0006_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO3				0x044e
#define		COMMAND_13_0007_O_2TANK_TANK2_2GAS_COOLER_SET_NO4					0x044f
#define		COMMAND_13_0008_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO4				0x0450
#define		COMMAND_13_0009_O_2TANK_TANK2_2GAS_COOLER_SET_NO5					0x0451
#define		COMMAND_13_0010_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO5				0x0452
#define		COMMAND_13_0011_O_2TANK_TANK2_2GAS_COOLER_SET_NO6					0x0453
#define		COMMAND_13_0012_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO6				0x0454
#define		COMMAND_13_0013_O_2TANK_TANK2_2GAS_COOLER_SET_NO7					0x0455
#define		COMMAND_13_0014_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO7				0x0456
#define		COMMAND_13_0015_O_2TANK_TANK2_2GAS_COOLER_SET_NO8					0x0457
#define		COMMAND_13_0016_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO8				0x0458
#define		COMMAND_13_0017_O_2TANK_TANK2_2GAS_COOLER_SET_NO9					0x0459
#define		COMMAND_13_0018_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO9				0x045a
#define		COMMAND_13_0019_O_2TANK_TANK2_2GAS_COOLER_SET_NO10					0x045b
#define		COMMAND_13_0020_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO10				0x045c
#define		COMMAND_13_0021_O_2TANK_TANK2_2GAS_COOLER_SET_NO11					0x045d
#define		COMMAND_13_0022_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO11				0x045e
#define		COMMAND_13_0023_O_2TANK_TANK2_2GAS_COOLER_SET_NO12					0x045f
#define		COMMAND_13_0024_O_2TANK_TANK2_2GAS_IS_COOLER_SET_NO12				0x0460


//����ѹ�����ϵ�
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF				0x0342//�����豸����ָ��
//#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START		0x0343//��ʱ1min��ʱ��ʼ
//#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN			0x0344//�жϼ�ʱ1min�Ƿ�

//�������������ϵ�
#define		COMMAND_13_0001_O_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF				0x0345//�����豸����ָ��
#define		COMMAND_13_0002_O_2TANK_TANK2_2GAS_TGTHT530_TIME_1MIN_START			0x0346//��ʱ1min��ʱ��ʼ
#define		COMMAND_13_0003_O_2TANK_TANK2_2GAS_TGTHT530_IS_TIME_1MIN			0x0347//�жϼ�ʱ1min�Ƿ�


//0x0460
//------------------------��������---------------------------------------------------------

void TGTHT510_supply_stage13_comp_O_main(void);

//-------------------------------------------------��ʼ���ý׶�----------------------------------------------------

uint16 TGTHT510_supply_stage13_comp_O_init_step_start_cooler(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_is_cooler_work(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_time_delay(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_is_compressor_temperature(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_TGTHT530_power_on(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_compressor_power_on(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_isolation(void);
uint16 TGTHT510_supply_stage13_comp_O_init_step_number_comp_tank(void);

//-------------------------------------------------һ���������----------------------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_is_in_tank_valve_on_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_in_compressor_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_time_delay1(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_is_in_compressor_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_compressor_start(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_is_out_compressor_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_out_compressor_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_step_number_comp_gas(void);

//-----------------------------------һ�����������һ����ƿ����----------------------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_compressor_temperature(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_is_need_cooler_stop(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_time_delay3(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_cooler_set(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_1gas_step_TGTHT530_power_off(void);


//-----------------------------------һ�����������������ƿ����----------------------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas1_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_gas2_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_compressor_temperature(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_is_need_cooler_stop(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_time_delay3(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_cooler_set(void);

uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage13_comp_O_1tank_2gas_step_TGTHT530_power_off(void);


//---------------------------------���������������һ���������----------------------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_in_tank_valve_on_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_in_compressor_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_time_delay1(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_in_compressor_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_compressor_start(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_is_out_compressor_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_out_compressor_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_step_number_comp_gas(void);

//---------------------------------���������������һ�����������һ����ƿ����--------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_1gas_step_is_in_tank_valve_pressure(void);

//---------------------------------���������������һ�����������������ƿ����--------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas1_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_gas2_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank1_2gas_step_is_in_tank_valve_pressure(void);

//---------------------------------��������������ڶ����������----------------------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_step_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_step_is_in_tank_valve_on_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_step_number_comp_gas(void);

//---------------------------------��������������ڶ������������һ����ƿ����--------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_compressor_temperature(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_is_need_cooler_stop(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_time_delay3(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_cooler_set(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_1gas_step_TGTHT530_power_off(void);


//---------------------------------��������������ڶ������������������ƿ����--------------------------------------
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas1_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_time_delay2(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_is_comp_over(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_gas2_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_compressor_temperature(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_is_need_cooler_stop(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_time_delay3(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_cooler_set(void);

uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage13_comp_O_2tank_tank2_2gas_step_TGTHT530_power_off(void);


//---------------------------------------------------------ͨ�ú���------------------------------------------------



#endif
 
 
 