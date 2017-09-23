/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ���������������������ͷ�ļ�
  ******************************************************************************
  */
 
#ifndef __supply_stage_05_comp_f_h
#define __supply_stage_05_comp_f_h
 

/*�����ṹ������--------------------------------------------------------------*/



/*�궨��---------------------------------------------------------------------------*/

#define		COMP_TANK_F									0x0101//ȼ�������
#define		COMP_TANK_O									0x0202//���������

#define		ISOLATION_TANK_F							0x0101//ȼ�������
#define		ISOLATION_TANK_O							0x0202//���������


//����step-------------------------------------------------------------------------

//----------------------------------��ʼ���ý׶�-----------------------------------

#define 	STEP_05_F_INIT_START_COOLER							0x0000//����Һ��ù���
#define 	STEP_05_F_INIT_IS_COOLER_WORK						0x0001//ͨ��ת���ж�Һ�乤���Ƿ�����
#define 	STEP_05_F_INIT_DELAY								0x0002//��ʱ�ȴ�ʱ��
#define		STEP_05_F_INIT_IS_COMPRESSOR_TEMPERATURE			0x0003//�ж�ѹ�����¶��Ƿ�����
#define		STEP_05_F_INIT_TGTHT530_POWER_ON					0x0004//�������������ӵ�
#define		STEP_05_F_INIT_COMPRESSOR_POWER_ON					0x0005//����ѹ�����ӵ�
#define		STEP_05_F_INIT_ISOLATION							0x0006//�������
#define		STEP_05_F_INIT_NUMBER_COMP_TANK						0x0007//�жϳ����������

//----------------------------------һ���������-----------------------------------

#define 	STEP_05_F_1TANK_IN_TANK_VALVE_ON					0x0008//���������ѹ��·���ӷ���

#define 	STEP_05_F_1TANK_TIME_DELAY_A						0x009e//��ʱ�ȴ�

#define 	STEP_05_F_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE		0x0009//ͨ��ѹ���жϿ��������ѹ��·���ӷ���
#define 	STEP_05_F_1TANK_IN_COMPRESSOR_VALVE_ON				0x000a//��ȼѹ�������ڷ���
#define 	STEP_05_F_1TANK_TIME_DELAY1							0x000b//��ʱ�ȴ�time_delay1
#define 	STEP_05_F_1TANK_IS_IN_COMPRESSOR_PRESSURE			0x000c//�ж�ѹ��������ѹ���Ƿ�����
#define 	STEP_05_F_1TANK_COMPRESSOR_START					0x000d//ȼѹ��������

#define 	STEP_05_F_1TANK_TIME_DELAY_B						0x009f//��ʱ�ȴ�

#define 	STEP_05_F_1TANK_IS_OUT_COMPRESSOR_PRESSURE			0x000e//�ж�ѹ��������ѹ���Ƿ�����
#define 	STEP_05_F_1TANK_OUT_COMPRESSOR_VALVE_ON				0x000f//��ȼѹ�������ڷ���
#define 	STEP_05_F_1TANK_NUMBER_COMP_GAS						0x0010//�жϳ�����ƿ����

//һ����ƿ����
#define 	STEP_05_F_1TANK_1GAS_IN_GAS_VALVE_ON				0x0011//������ƿ���ӷ���
#define 	STEP_05_F_1TANK_1GAS_TIME_DELAY2					0x0012//��ʱ�ȴ�time_delay2
#define 	STEP_05_F_1TANK_1GAS_IS_GAS_PRESSURE				0x0013//�ж���ƿѹ���Ƿ�����
#define 	STEP_05_F_1TANK_1GAS_IS_COMP_OVER					0x0014//�ж���ƿ�����Ƿ����
#define 	STEP_05_F_1TANK_1GAS_IN_GAS_VALVE_OFF				0x0015//��ȼ·��ƿ���ӷ���

#define		STEP_05_F_1TANK_1GAS_IS_ISOLATION_FIRST				0x0016//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define 	STEP_05_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF		0x0017//�ر�ȼѹ�������ڷ���
#define		STEP_05_F_1TANK_1GAS_IS_ISOLATION_SECOND			0x0018//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���

#define		STEP_05_F_1TANK_1GAS_COMPRESSOR_STOP				0x0019//ȼѹ����ͣ��
#define		STEP_05_F_1TANK_1GAS_IS_COMPRESSOR_STOP				0x001a//�ж�ȼѹ����ͣ���Ƿ�����
#define		STEP_05_F_1TANK_1GAS_BYPATH_VALVE_ON				0x001b//��ȼѹ������·������
#define 	STEP_05_F_1TANK_1GAS_TIME_DELAY_BYPATH				0x001c//��ʱ�ȴ�time_bypath
#define		STEP_05_F_1TANK_1GAS_BYPATH_VALVE_OFF				0x001d//��ȼѹ������·������
#define 	STEP_05_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2		0x001e//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define 	STEP_05_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF		0x001f//�ر�ȼѹ�������ڷ���
#define 	STEP_05_F_1TANK_1GAS_IN_TANK_VALVE_OFF				0x0020//�ؽ������ѹ��·���ӷ���
#define 	STEP_05_F_1TANK_1GAS_SET_STATE_GOOD					0x0021//����ȼ����״̬��
#define 	STEP_05_F_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE		0x0022//�ж�ѹ�����¶��Ƿ�����
#define 	STEP_05_F_1TANK_1GAS_IS_NEED_EXCHANGE				0x0023//�ж��Ƿ���Ҫ����Һ��ģ���л�����

#define 	STEP_05_F_1TANK_1GAS_TIME_DELAY3					0x0024//��ʱ�ȴ�time_delay3
#define 	STEP_05_F_1TANK_1GAS_EXCHANGE_COOLER				0x0025//����Һ��ģ���л�����
#define		STEP_05_F_1TANK_1GAS_IS_EXCHANGE_COOLER				0x0026//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		STEP_05_F_1TANK_1GAS_COOLER_STOP					0x0027//Һ��ģ��ͣ��
#define		STEP_05_F_1TANK_1GAS_COMPRESSOR_POWER_OFF			0x0028//����ѹ�����ϵ�
#define		STEP_05_F_1TANK_1GAS_TGTHT530_POWER_OFF				0x0029//�������������ϵ�

//**************************************�������******************************************************************

//������ƿ����
#define 	STEP_05_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON			0x002a//������ƿ���ӷ���---��һ����ƿ
#define 	STEP_05_F_1TANK_2GAS_GAS1_TIME_DELAY2				0x002b//��ʱ�ȴ�time_delay2---��һ����ƿ
#define 	STEP_05_F_1TANK_2GAS_GAS1_IS_GAS_PRESSURE			0x002c//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define 	STEP_05_F_1TANK_2GAS_GAS1_IS_COMP_OVER				0x002d//�ж���ƿ�����Ƿ����---��һ����ƿ
#define 	STEP_05_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF			0x002e//��ȼ·��ƿ���ӷ���---��һ����ƿ
#define 	STEP_05_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON			0x002f//������ƿ���ӷ���---�ڶ�����ƿ
#define 	STEP_05_F_1TANK_2GAS_GAS2_TIME_DELAY2				0x0030//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define 	STEP_05_F_1TANK_2GAS_GAS2_IS_GAS_PRESSURE			0x0031//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define 	STEP_05_F_1TANK_2GAS_GAS2_IS_COMP_OVER				0x0032//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define 	STEP_05_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF			0x0033//��ȼ·��ƿ���ӷ���---�ڶ�����ƿ

#define		STEP_05_F_1TANK_2GAS_IS_ISOLATION_FIRST				0x0034//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define 	STEP_05_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF		0x0035//�ر�ȼѹ�������ڷ���
#define		STEP_05_F_1TANK_2GAS_IS_ISOLATION_SECOND			0x0036//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���

#define		STEP_05_F_1TANK_2GAS_COMPRESSOR_STOP				0x0037//ȼѹ����ͣ��
#define		STEP_05_F_1TANK_2GAS_IS_COMPRESSOR_STOP				0x0038//�ж�ȼѹ����ͣ���Ƿ�����
#define		STEP_05_F_1TANK_2GAS_BYPATH_VALVE_ON				0x0039//��ȼѹ������·������
#define 	STEP_05_F_1TANK_2GAS_TIME_DELAY_BYPATH				0x003a//��ʱ�ȴ�time_bypath
#define		STEP_05_F_1TANK_2GAS_BYPATH_VALVE_OFF				0x003b//��ȼѹ������·������
#define 	STEP_05_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2		0x003c//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define 	STEP_05_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF		0x003d//�ر�ȼѹ�������ڷ���
#define 	STEP_05_F_1TANK_2GAS_IN_TANK_VALVE_OFF				0x003e//�ؽ������ѹ��·���ӷ���
#define 	STEP_05_F_1TANK_2GAS_SET_STATE_GOOD					0x003f//����ȼ����״̬��
#define 	STEP_05_F_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE		0x0040//�ж�ѹ�����¶��Ƿ�����
#define 	STEP_05_F_1TANK_2GAS_IS_NEED_EXCHANGE				0x0041//�ж��Ƿ���Ҫ����Һ��ģ���л�����

#define 	STEP_05_F_1TANK_2GAS_TIME_DELAY3					0x0042//��ʱ�ȴ�time_delay3
#define 	STEP_05_F_1TANK_2GAS_EXCHANGE_COOLER				0x0043//����Һ��ģ���л�����
#define		STEP_05_F_1TANK_2GAS_IS_EXCHANGE_COOLER				0x0044//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		STEP_05_F_1TANK_2GAS_COOLER_STOP					0x0045//Һ��ģ��ͣ��
#define		STEP_05_F_1TANK_2GAS_COMPRESSOR_POWER_OFF			0x0046//����ѹ�����ϵ�
#define		STEP_05_F_1TANK_2GAS_TGTHT530_POWER_OFF				0x0047//�������������ϵ�

//**************************************�������******************************************************************

//----------------------------------���������������һ���������-----------------------------------

#define 	STEP_05_F_2TANK_TANK1_IN_TANK_VALVE_ON				0x0048//���������ѹ��·���ӷ���---��һ������

#define 	STEP_05_F_2TANK_TANK1_TIME_DELAY_C					0x00a0//��ʱ�ȴ�

#define 	STEP_05_F_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE	0x0049//ͨ��ѹ���жϿ������䷧��---��һ������
#define 	STEP_05_F_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON		0x004a//��ȼѹ�������ڷ���---��һ������
#define 	STEP_05_F_2TANK_TANK1_TIME_DELAY1					0x004b//��ʱ�ȴ�time_delay1---��һ������
#define 	STEP_05_F_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE		0x004c//�ж�ѹ��������ѹ���Ƿ�����---��һ������
#define 	STEP_05_F_2TANK_TANK1_COMPRESSOR_START				0x004d//ȼѹ��������---��һ������

#define 	STEP_05_F_2TANK_TANK1_TIME_DELAY_D					0x00a1//��ʱ�ȴ�

#define 	STEP_05_F_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE	0x004e//�ж�ѹ��������ѹ���Ƿ�����---��һ������
#define 	STEP_05_F_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON		0x004f//��ȼѹ�������ڷ���---��һ������
#define 	STEP_05_F_2TANK_TANK1_NUMBER_COMP_GAS				0x0050//�жϳ�����ƿ����---��һ������

//һ����ƿ����
#define 	STEP_05_F_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON				0x0051//������ƿ���ӷ���---��һ������
#define 	STEP_05_F_2TANK_TANK1_1GAS_TIME_DELAY2					0x0052//��ʱ�ȴ�time_delay2---��һ������
#define 	STEP_05_F_2TANK_TANK1_1GAS_IS_GAS_PRESSURE				0x0053//�ж���ƿѹ���Ƿ�����---��һ������
#define 	STEP_05_F_2TANK_TANK1_1GAS_IS_COMP_OVER					0x0054//�ж���ƿ�����Ƿ����---��һ������
#define 	STEP_05_F_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF				0x0055//��ȼ·��ƿ���ӷ���---��һ������
#define 	STEP_05_F_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF			0x0056//�ؽ������ѹ��·���ӷ���---��һ������
#define 	STEP_05_F_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE	0x0057//ͨ��ѹ���жϹؽ����䲹�ӷ�---��һ������

//**************************************����ת���ڶ����������*****************************************************

//������ƿ����
#define 	STEP_05_F_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON			0x0058//������ƿ���ӷ���---��һ����ƿ
#define 	STEP_05_F_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2				0x0059//��ʱ�ȴ�time_delay2---��һ����ƿ
#define 	STEP_05_F_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE			0x005a//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define 	STEP_05_F_2TANK_TANK1_2GAS_GAS1_IS_COMP_OVER			0x005b//�ж���ƿ�����Ƿ����---��һ����ƿ
#define 	STEP_05_F_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF		0x005c//��ȼ·��ƿ���ӷ���---��һ����ƿ
#define 	STEP_05_F_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON			0x005d//������ƿ���ӷ���---�ڶ�����ƿ
#define 	STEP_05_F_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2				0x005e//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define 	STEP_05_F_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE			0x005f//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define 	STEP_05_F_2TANK_TANK1_2GAS_GAS2_IS_COMP_OVER			0x0060//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define 	STEP_05_F_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF		0x0061//��ȼ·��ƿ���ӷ���---�ڶ�����ƿ
#define 	STEP_05_F_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF			0x0062//�ؽ������ѹ��·���ӷ���
#define 	STEP_05_F_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE	0x0063//ͨ��ѹ���жϹؽ����䲹�ӷ�

//**************************************����ת���ڶ����������*****************************************************

//----------------------------------��������������ڶ����������-----------------------------------

#define 	STEP_05_F_2TANK_TANK2_IN_TANK_VALVE_ON					0x0064//���������ѹ��·���ӷ���---�ڶ�������

#define 	STEP_05_F_2TANK_TANK2_TIME_DELAY_E						0x00a2//��ʱ�ȴ�

#define 	STEP_05_F_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE		0x0065//ͨ��ѹ���жϿ������䷧��---�ڶ�������
#define 	STEP_05_F_2TANK_TANK2_NUMBER_COMP_GAS					0x0066//�жϳ�����ƿ����---�ڶ�������

//һ����ƿ����
#define 	STEP_05_F_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON				0x0067//������ƿ���ӷ���---�ڶ�������
#define 	STEP_05_F_2TANK_TANK2_1GAS_TIME_DELAY2					0x0068//��ʱ�ȴ�time_delay2---�ڶ�������
#define 	STEP_05_F_2TANK_TANK2_1GAS_IS_GAS_PRESSURE				0x0069//�ж���ƿѹ���Ƿ�����---�ڶ�������
#define 	STEP_05_F_2TANK_TANK2_1GAS_IS_COMP_OVER					0x006a//�ж���ƿ�����Ƿ����---�ڶ�������
#define 	STEP_05_F_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF				0x006b//��ȼ·��ƿ���ӷ���---�ڶ�������

#define		STEP_05_F_2TANK_TANK2_1GAS_IS_ISOLATION_FIRST			0x006c//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define 	STEP_05_F_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF		0x006d//�ر�ȼѹ�������ڷ���
#define		STEP_05_F_2TANK_TANK2_1GAS_IS_ISOLATION_SECOND			0x006e//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���

#define		STEP_05_F_2TANK_TANK2_1GAS_COMPRESSOR_STOP				0x006f//ȼѹ����ͣ��
#define		STEP_05_F_2TANK_TANK2_1GAS_IS_COMPRESSOR_STOP			0x0070//�ж�ȼѹ����ͣ���Ƿ�����
#define		STEP_05_F_2TANK_TANK2_1GAS_BYPATH_VALVE_ON				0x0071//��ȼѹ������·������
#define 	STEP_05_F_2TANK_TANK2_1GAS_TIME_DELAY_BYPATH			0x0072//��ʱ�ȴ�time_bypath
#define		STEP_05_F_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF				0x0073//��ȼѹ������·������
#define 	STEP_05_F_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2	0x0074//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define 	STEP_05_F_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF		0x0075//�ر�ȼѹ�������ڷ���
#define 	STEP_05_F_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF			0x0076//�ؽ������ѹ��·���ӷ���
#define 	STEP_05_F_2TANK_TANK2_1GAS_SET_STATE_GOOD				0x0077//����ȼ����״̬��
#define 	STEP_05_F_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE	0x0078//�ж�ѹ�����¶��Ƿ�����
#define 	STEP_05_F_2TANK_TANK2_1GAS_IS_NEED_EXCHANGE				0x0079//�ж��Ƿ���Ҫ����Һ��ģ���л�����

#define 	STEP_05_F_2TANK_TANK2_1GAS_TIME_DELAY3					0x007a//��ʱ�ȴ�time_delay3
#define 	STEP_05_F_2TANK_TANK2_1GAS_EXCHANGE_COOLER				0x007b//����Һ��ģ���л�����
#define		STEP_05_F_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER			0x007c//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		STEP_05_F_2TANK_TANK2_1GAS_COOLER_STOP					0x007d//Һ��ģ��ͣ��
#define		STEP_05_F_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF			0x007e//����ѹ�����ϵ�
#define		STEP_05_F_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF			0x007f//�������������ϵ�

//**************************************�������******************************************************************

//������ƿ����
#define 	STEP_05_F_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON			0x0080//������ƿ���ӷ���---��һ����ƿ
#define 	STEP_05_F_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2				0x0081//��ʱ�ȴ�time_delay2---��һ����ƿ
#define 	STEP_05_F_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE			0x0082//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define 	STEP_05_F_2TANK_TANK2_2GAS_GAS1_IS_COMP_OVER			0x0083//�ж���ƿ�����Ƿ����---��һ����ƿ
#define 	STEP_05_F_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF		0x0084//��ȼ·��ƿ���ӷ���---��һ����ƿ
#define 	STEP_05_F_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON			0x0085//������ƿ���ӷ���---�ڶ�����ƿ
#define 	STEP_05_F_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2				0x0086//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define 	STEP_05_F_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE			0x0087//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define 	STEP_05_F_2TANK_TANK2_2GAS_GAS2_IS_COMP_OVER			0x0088//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define 	STEP_05_F_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF		0x0089//��ȼ·��ƿ���ӷ���---�ڶ�����ƿ

#define		STEP_05_F_2TANK_TANK2_2GAS_IS_ISOLATION_FIRST			0x008a//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define 	STEP_05_F_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF		0x008b//�ر�ȼѹ�������ڷ���
#define		STEP_05_F_2TANK_TANK2_2GAS_IS_ISOLATION_SECOND			0x008c//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���

#define		STEP_05_F_2TANK_TANK2_2GAS_COMPRESSOR_STOP				0x008d//ȼѹ����ͣ��
#define		STEP_05_F_2TANK_TANK2_2GAS_IS_COMPRESSOR_STOP			0x008e//�ж�ȼѹ����ͣ���Ƿ�����
#define		STEP_05_F_2TANK_TANK2_2GAS_BYPATH_VALVE_ON				0x008f//��ȼѹ������·������
#define 	STEP_05_F_2TANK_TANK2_2GAS_TIME_DELAY_BYPATH			0x0090//��ʱ�ȴ�time_bypath
#define		STEP_05_F_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF				0x0091//��ȼѹ������·������
#define 	STEP_05_F_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2	0x0092//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define 	STEP_05_F_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF		0x0093//�ر�ȼѹ�������ڷ���
#define 	STEP_05_F_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF			0x0094//�ؽ������ѹ��·���ӷ���
#define 	STEP_05_F_2TANK_TANK2_2GAS_SET_STATE_GOOD				0x0095//����ȼ����״̬��
#define 	STEP_05_F_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE	0x0096//�ж�ѹ�����¶��Ƿ�����
#define 	STEP_05_F_2TANK_TANK2_2GAS_IS_NEED_EXCHANGE				0x0097//�ж��Ƿ���Ҫ����Һ��ģ���л�����

#define 	STEP_05_F_2TANK_TANK2_2GAS_TIME_DELAY3					0x0098//��ʱ�ȴ�time_delay3
#define 	STEP_05_F_2TANK_TANK2_2GAS_EXCHANGE_COOLER				0x0099//����Һ��ģ���л�����
#define		STEP_05_F_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER			0x009a//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		STEP_05_F_2TANK_TANK2_2GAS_COOLER_STOP					0x009b//Һ��ģ��ͣ��
#define		STEP_05_F_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF			0x009c//����ѹ�����ϵ�
#define		STEP_05_F_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF			0x009d//�������������ϵ�



//0x00a2

//**************************************�������******************************************************************

//����command--------------------------------------------------------------------------------------------

//------------------------------command---��ʼ���ý׶�---------------------------------------------------

//����Һ��ù���
#define		COMMAND_05_0001_F_INIT_COOLER_VALVE_ON_NO1			0x0001//Һ��ģ�鲹��ϵͳ���ſ���һ��
#define		COMMAND_05_0002_F_INIT_IS_COOLER_VALVE_ON_NO1		0x0002//�ж�Һ��ģ�鲹��ϵͳ���ſ���һ��
#define		COMMAND_05_0003_F_INIT_COOLER_VALVE_ON_NO2			0x0003//Һ��ģ�鲹��ϵͳ���ſ��ڶ���
#define		COMMAND_05_0004_F_INIT_IS_COOLER_VALVE_ON_NO2		0x0004//�ж�Һ��ģ�鲹��ϵͳ���ſ��ڶ���
#define		COMMAND_05_0005_F_INIT_COOLER_POWER_ON				0x0005//Һ��ģ�鹩��ͨ
#define		COMMAND_05_0006_F_INIT_TIME_1MIN_START				0x0006//��ʱ1min��ʱ��ʼ
#define		COMMAND_05_0007_F_INIT_IS_TIME_1MIN					0x0007//��ʱ1min�Ƿ�

//ͨ��ת���ж�Һ�乤���Ƿ�����
#define		COMMAND_05_0001_F_INIT_IS_COOLER_WORK				0x0008//ͨ��ת���ж�Һ�乤���Ƿ�����

//��ʱ�ȴ�time_delay
#define		COMMAND_05_0001_F_INIT_TIME_DELAY_START				0x0009//��ʱ�ȴ�time_delay��ʱ��ʼ
#define		COMMAND_05_0002_F_INIT_IS_TIME_DELAY				0x000a//�ж���ʱ�ȴ�time_delay

//�ж�ѹ�����¶��Ƿ�����
#define		COMMAND_05_0001_F_INIT_IS_COMPRESSOR_TEMPERATURE	0x000b//�ж�ѹ�����¶��Ƿ�����

//�������������ӵ�
#define		COMMAND_05_0001_F_INIT_TGTHT530_POWER_ON			0x000c//�����豸����ָ��
#define		COMMAND_05_0002_F_INIT_TGTHT530_TIME_1MIN_START		0x000d//��ʱ1min��ʱ��ʼ
#define		COMMAND_05_0003_F_INIT_TGTHT530_IS_TIME_1MIN		0x000e//�жϼ�ʱ1min�Ƿ�
#define		COMMAND_05_0004_F_INIT_TGTHT530_IS_POWER_ON			0x000f//ͨ�����������жϼӵ��Ƿ�����

//����ѹ�����ӵ�
#define		COMMAND_05_0001_F_INIT_COMPRESSOR_POWER_ON			0x0010//�����豸����ָ��
#define		COMMAND_05_0002_F_INIT_COMPRESSOR_TIME_1MIN_START	0x0011//��ʱ1min��ʱ��ʼ
#define		COMMAND_05_0003_F_INIT_COMPRESSOR_IS_TIME_1MIN		0x0012//�жϼ�ʱ1min�Ƿ�

//�������
#define		COMMAND_05_0001_F_INIT_ISOLATION_VALVE_OFF_NO1		0x0013//�����ƽ�ϵͳ�������رգ���һ��
#define		COMMAND_05_0002_F_INIT_TIME_1MIN_START_NO1			0x0014//��ʱ1min��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_INIT_IS_TIME_1MIN_NO1				0x0015//��ʱ1min�Ƿ񵽣���һ��
#define		COMMAND_05_0004_F_INIT_IS_ISOLATION_VALVE_OFF_NO1	0x0016//�жϸ����ƽ�ϵͳ�������رգ���һ��

#define		COMMAND_05_0005_F_INIT_ISOLATION_VALVE_OFF_NO2		0x0017//�����ƽ�ϵͳ�������رգ��ڶ���
#define		COMMAND_05_0006_F_INIT_TIME_1MIN_START_NO2			0x0018//��ʱ1min��ʱ��ʼ���ڶ���
#define		COMMAND_05_0007_F_INIT_IS_TIME_1MIN_NO2				0x0019//��ʱ1min�Ƿ񵽣��ڶ���
#define		COMMAND_05_0008_F_INIT_IS_ISOLATION_VALVE_OFF_NO2	0x001a//�жϸ����ƽ�ϵͳ�������رգ��ڶ���

#define		COMMAND_05_0009_F_INIT_ISOLATION_VALVE_OFF_NO3		0x001b//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_05_0010_F_INIT_TIME_1MIN_START_NO3			0x001c//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_05_0011_F_INIT_IS_TIME_1MIN_NO3				0x001d//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_05_0012_F_INIT_IS_ISOLATION_VALVE_OFF_NO3	0x001e//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_05_0013_F_INIT_ISOLATION_VALVE_OFF_NO4		0x001f//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_05_0014_F_INIT_TIME_1MIN_START_NO4			0x0020//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_05_0015_F_INIT_IS_TIME_1MIN_NO4				0x0021//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_05_0016_F_INIT_IS_ISOLATION_VALVE_OFF_NO4	0x0022//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_05_0017_F_INIT_ISOLATION_VALVE_OFF_NO5		0x0023//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_05_0018_F_INIT_TIME_1MIN_START_NO5			0x0024//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_05_0019_F_INIT_IS_TIME_1MIN_NO5				0x0025//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_05_0020_F_INIT_IS_ISOLATION_VALVE_OFF_NO5	0x0026//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_05_0021_F_INIT_ISOLATION_VALVE_OFF_NO6		0x0027//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_05_0022_F_INIT_TIME_1MIN_START_NO6			0x0028//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_05_0023_F_INIT_IS_TIME_1MIN_NO6				0x0029//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_05_0024_F_INIT_IS_ISOLATION_VALVE_OFF_NO6	0x002a//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_05_0025_F_INIT_ISOLATION_VALVE_OFF_NO7		0x002b//�����ƽ�ϵͳ�������رգ�������
#define		COMMAND_05_0026_F_INIT_TIME_1MIN_START_NO7			0x002c//��ʱ1min��ʱ��ʼ��������
#define		COMMAND_05_0027_F_INIT_IS_TIME_1MIN_NO7				0x002d//��ʱ1min�Ƿ񵽣�������
#define		COMMAND_05_0028_F_INIT_IS_ISOLATION_VALVE_OFF_NO7	0x002e//�жϸ����ƽ�ϵͳ�������رգ�������

#define		COMMAND_05_0029_F_INIT_ISOLATION_VALVE_OFF_NO8		0x002f//�����ƽ�ϵͳ�������رգ��ڰ���
#define		COMMAND_05_0030_F_INIT_TIME_1MIN_START_NO8			0x0030//��ʱ1min��ʱ��ʼ���ڰ���
#define		COMMAND_05_0031_F_INIT_IS_TIME_1MIN_NO8				0x0031//��ʱ1min�Ƿ񵽣��ڰ���
#define		COMMAND_05_0032_F_INIT_IS_ISOLATION_VALVE_OFF_NO8	0x0032//�жϸ����ƽ�ϵͳ�������رգ��ڰ���

#define		COMMAND_05_0033_F_INIT_ISOLATION_VALVE_OFF_NO9		0x0033//�����ƽ�ϵͳ�������رգ��ھ���
#define		COMMAND_05_0034_F_INIT_TIME_1MIN_START_NO9			0x0034//��ʱ1min��ʱ��ʼ���ھ���
#define		COMMAND_05_0035_F_INIT_IS_TIME_1MIN_NO9				0x0035//��ʱ1min�Ƿ񵽣��ھ���
#define		COMMAND_05_0036_F_INIT_IS_ISOLATION_VALVE_OFF_NO9	0x0036//�жϸ����ƽ�ϵͳ�������رգ��ھ���

//�жϳ����������
#define		COMMAND_05_0001_F_INIT_NUMBER_COMP_TANK				0x0037//�жϳ����������
			
//------------------------------command---һ���������-----------------------------------------------

//���������ѹ��·���ӷ���
#define		COMMAND_05_0001_F_1TANK_IN_TANK_VALVE_ON					0x0038//���������ѹ��·���ӷ���
#define		COMMAND_05_0002_F_1TANK_IS_IN_TANK_VALVE_ON					0x0039//�жϿ��������ѹ��·���ӷ���

//ͨ��ѹ���жϿ��������ѹ��·���ӷ���
#define		COMMAND_05_0001_F_1TANK_IS_IN_TANK_VALVE_ON_PRESSURE		0x003a//ͨ��ѹ���жϿ����ӷ���

//��ȼѹ�������ڷ���
#define		COMMAND_05_0001_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO1			0x003b//��ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO1		0x003c//�жϿ�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO2			0x003d//��ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO2		0x003e//�жϿ�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_1TANK_IN_COMPRESSOR_VALVE_ON_NO3			0x003f//��ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_1TANK_IS_IN_COMPRESSOR_VALVE_ON_NO3		0x0040//�жϿ�ȼѹ�������ڷ��ţ�������

//��ʱ�ȴ�time_delay1
#define		COMMAND_05_0001_F_1TANK_TIME_DELAY1_START					0x0041//��ʱ�ȴ�time_delay1��ʱ��ʼ
#define		COMMAND_05_0002_F_1TANK_IS_TIME_DELAY1						0x0042//�ж���ʱ�ȴ�time_delay1

//�ж�ѹ��������ѹ���Ƿ�����
#define		COMMAND_05_0001_F_1TANK_IS_IN_COMPRESSOR_PRESSURE			0x0043//�ж�ѹ��������ѹ���Ƿ�����

//ȼѹ��������
#define		COMMAND_05_0001_F_1TANK_COMPRESSOR_START					0x0044//�����豸����ָ�ѹ��������
#define		COMMAND_05_0002_F_1TANK_COMPRESSOR_TIME_1MIN_START			0x0045//��ʱ1min��ʱ��ʼ
#define		COMMAND_05_0003_F_1TANK_COMPRESSOR_IS_TIME_1MIN				0x0046//�ж�1min��ʱ
#define		COMMAND_05_0004_F_1TANK_IS_COMPRESSOR_START					0x0047//ͨ�����������ж������Ƿ�����

//�ж�ѹ��������ѹ���Ƿ�����
#define		COMMAND_05_0001_F_1TANK_IS_OUT_COMPRESSOR_PRESSURE			0x0048//�ж�ѹ��������ѹ���Ƿ�����

//��ȼѹ�������ڷ���
#define		COMMAND_05_0001_F_1TANK_OUT_COMPRESSOR_VALVE_ON				0x0049//��ȼѹ�������ڷ���
#define		COMMAND_05_0002_F_1TANK_IS_OUT_COMPRESSOR_VALVE_ON			0x004a//�жϿ�ȼѹ�������ڷ���

//�жϳ�����ƿ����
#define		COMMAND_05_0001_F_1TANK_NUMBER_COMP_GAS						0x004b//�жϳ�����ƿ����


//------------------------------command---һ���������----һ����ƿ����-----------------------------------

//������ƿ���ӷ���
#define		COMMAND_05_0001_F_1TANK_1GAS_IN_GAS_VALVE_ON				0x004c//������ƿ���ӷ���
#define		COMMAND_05_0002_F_1TANK_1GAS_IS_IN_GAS_VALVE_ON				0x004d//�жϿ�����ƿ���ӷ���

//��ʱ�ȴ�time_delay2
#define		COMMAND_05_0001_F_1TANK_1GAS_TIME_DELAY2_START				0x004e//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_05_0002_F_1TANK_1GAS_IS_TIME_DELAY2					0x004f//�ж���ʱ�ȴ�time_delay2

//�ж���ƿѹ���Ƿ�����
#define		COMMAND_05_0001_F_1TANK_1GAS_GAS_PRESSURE_NO1				0x0050//�ɼ���ƿѹ������һ��
#define		COMMAND_05_0002_F_1TANK_1GAS_TIME_30S_START_NO1				0x0051//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_1TANK_1GAS_IS_TIME_30S_NO1				0x0052//�ж϶�ʱ30s����һ��
#define		COMMAND_05_0004_F_1TANK_1GAS_GAS_PRESSURE_NO2				0x0053//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_05_0005_F_1TANK_1GAS_TIME_30S_START_NO2				0x0054//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_1TANK_1GAS_IS_TIME_30S_NO2				0x0055//�ж϶�ʱ30s���ڶ���
#define		COMMAND_05_0007_F_1TANK_1GAS_GAS_PRESSURE_NO3				0x0056//�ɼ���ƿѹ����������
#define		COMMAND_05_0008_F_1TANK_1GAS_TIME_30S_START_NO3				0x0057//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_1TANK_1GAS_IS_TIME_30S_NO3				0x0058//�ж϶�ʱ30s��������
#define		COMMAND_05_0010_F_1TANK_1GAS_GAS_PRESSURE_NO4				0x0059//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_05_0011_F_1TANK_1GAS_TIME_30S_START_NO4				0x005a//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_05_0012_F_1TANK_1GAS_IS_TIME_30S_NO4				0x005b//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_05_0013_F_1TANK_1GAS_GAS_PRESSURE_NO5				0x005c//�ɼ���ƿѹ���������
#define		COMMAND_05_0014_F_1TANK_1GAS_TIME_30S_START_NO5				0x005d//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_05_0015_F_1TANK_1GAS_IS_TIME_30S_NO5				0x005e//�ж϶�ʱ30s�������
#define		COMMAND_05_0016_F_1TANK_1GAS_GAS_PRESSURE_NO6				0x005f//�ɼ���ƿѹ����������
#define		COMMAND_05_0017_F_1TANK_1GAS_TIME_30S_START_NO6				0x0060//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0018_F_1TANK_1GAS_IS_TIME_30S_NO6				0x0061//�ж϶�ʱ30s��������
#define		COMMAND_05_0019_F_1TANK_1GAS_GAS_PRESSURE_NO7				0x0062//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_05_0020_F_1TANK_1GAS_TIME_30S_START_NO7				0x0063//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_05_0021_F_1TANK_1GAS_IS_TIME_30S_NO7				0x0064//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_05_0022_F_1TANK_1GAS_GAS_PRESSURE_NO8				0x0065//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_05_0023_F_1TANK_1GAS_TIME_30S_START_NO8				0x0066//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_05_0024_F_1TANK_1GAS_IS_TIME_30S_NO8				0x0067//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_05_0025_F_1TANK_1GAS_GAS_PRESSURE_NO9				0x0068//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_05_0026_F_1TANK_1GAS_TIME_30S_START_NO9				0x0069//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_05_0027_F_1TANK_1GAS_IS_TIME_30S_NO9				0x006a//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_05_0028_F_1TANK_1GAS_GAS_PRESSURE_NO10				0x006b//�ɼ���ƿѹ������ʮ��
#define		COMMAND_05_0029_F_1TANK_1GAS_IS_GAS_PRESSURE				0x006c//ѹ���ж���ƿѹ���Ƿ�����

//�ж���ƿ�����Ƿ����
#define		COMMAND_05_0001_F_1TANK_1GAS_IS_COMP_GAS_OVER				0x006d//�ж���ƿ�����Ƿ����

//��ȼ·��ƿ���ӷ���
#define		COMMAND_05_0001_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO1			0x006e//��ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO1		0x006f//�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO2			0x0070//��ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO2		0x0071//�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_1TANK_1GAS_IN_GAS_VALVE_OFF_NO3			0x0072//��ȼ·��ƿ���ӷ��ţ�������
#define		COMMAND_05_0006_F_1TANK_1GAS_IS_IN_GAS_VALVE_OFF_NO3		0x0073//�жϹ�ȼ·��ƿ���ӷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define		COMMAND_05_0001_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO1	0x0074//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_05_0002_F_1TANK_1GAS_FIRST_TIME_12S_START_NO1		0x0075//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO1			0x0076//�ж϶�ʱ12s����һ��
#define		COMMAND_05_0004_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO2	0x0077//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_05_0005_F_1TANK_1GAS_FIRST_TIME_12S_START_NO2		0x0078//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO2			0x0079//�ж϶�ʱ12s���ڶ���
#define		COMMAND_05_0007_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO3	0x007a//�ɼ�ѹ��������ѹ����������
#define		COMMAND_05_0008_F_1TANK_1GAS_FIRST_TIME_12S_START_NO3		0x007b//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_1TANK_1GAS_FIRST_IS_TIME_12S_NO3			0x007c//�ж϶�ʱ12s��������
#define		COMMAND_05_0010_F_1TANK_1GAS_FIRST_ISOLATION_PRESSURE_NO4	0x007d//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_05_0011_F_1TANK_1GAS_FIRST_IS_ISOLATION				0x007e//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//�ر�ȼѹ�������ڷ���
#define		COMMAND_05_0001_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1			0x007f//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x0080//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2			0x0081//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x0082//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3			0x0083//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x0084//�жϹر�ȼѹ�������ڷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���
#define		COMMAND_05_0001_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO1	0x0085//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_05_0002_F_1TANK_1GAS_SECOND_TIME_12S_START_NO1		0x0086//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO1			0x0087//�ж϶�ʱ12s����һ��
#define		COMMAND_05_0004_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO2	0x0088//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_05_0005_F_1TANK_1GAS_SECOND_TIME_12S_START_NO2		0x0089//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO2			0x008a//�ж϶�ʱ12s���ڶ���
#define		COMMAND_05_0007_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO3	0x008b//�ɼ�ѹ��������ѹ����������
#define		COMMAND_05_0008_F_1TANK_1GAS_SECOND_TIME_12S_START_NO3		0x008c//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_1TANK_1GAS_SECOND_IS_TIME_12S_NO3			0x008d//�ж϶�ʱ12s��������
#define		COMMAND_05_0010_F_1TANK_1GAS_SECOND_ISOLATION_PRESSURE_NO4	0x008e//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_05_0011_F_1TANK_1GAS_SECOND_IS_ISOLATION			0x008f//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//ȼѹ����ͣ��
#define		COMMAND_05_0001_F_1TANK_1GAS_COMPRESSOR_STOP				0x0090//�����豸����ָ�ѹ����ͣ��
#define		COMMAND_05_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START		0x0091//��ʱ1min��ʱ��ʼ
#define		COMMAND_05_0003_F_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN		0x0092//�ж�1min��ʱ

//�ж�ȼѹ����ͣ���Ƿ�����
#define		COMMAND_05_0001_F_1TANK_1GAS_COMPRESSOR_V_NO1				0x0093//�ɼ����ת�٣���һ��
#define		COMMAND_05_0002_F_1TANK_1GAS_COMPRESSOR_V_NO2				0x0094//�ɼ����ת�٣��ڶ���
#define		COMMAND_05_0003_F_1TANK_1GAS_COMPRESSOR_V_NO3				0x0095//�ɼ����ת�٣�������
#define		COMMAND_05_0004_F_1TANK_1GAS_COMPRESSOR_V_NO4				0x0096//�ɼ����ת�٣����Ĵ�
#define		COMMAND_05_0005_F_1TANK_1GAS_COMPRESSOR_V_NO5				0x0097//�ɼ����ת�٣������
#define		COMMAND_05_0006_F_1TANK_1GAS_COMPRESSOR_V_NO6				0x0098//�ɼ����ת�٣�������
#define		COMMAND_05_0007_F_1TANK_1GAS_COMPRESSOR_V_NO7				0x0099//�ɼ����ת�٣����ߴ�
#define		COMMAND_05_0008_F_1TANK_1GAS_COMPRESSOR_V_NO8				0x009a//�ɼ����ת�٣��ڰ˴�
#define		COMMAND_05_0009_F_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO1	0x009b//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_05_0010_F_1TANK_1GAS_TIME_12S_START					0x009c//��ʱ12s��ʱ��ʼ
#define		COMMAND_05_0011_F_1TANK_1GAS_IS_TIME_12S					0x009d//�ж϶�ʱ12s
#define		COMMAND_05_0012_F_1TANK_1GAS_OUT_COMPRESSOR_PRESSURE_NO2	0x009e//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_05_0013_F_1TANK_1GAS_IS_COMPRESSOR_STOP				0x009f//�ж�ȼѹ����ͣ���Ƿ�����

//��ȼѹ������·������
#define		COMMAND_05_0001_F_1TANK_1GAS_BYPATH_VALVE_ON				0x00a0//��ȼѹ������·������
#define		COMMAND_05_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_ON				0x00a1//�жϿ�ȼѹ������·������

//��ʱ�ȴ�time_bypath
#define		COMMAND_05_0001_F_1TANK_1GAS_TIME_BYPATH_START				0x00a2//��ʱ�ȴ�time_bypath��ʱ����
#define		COMMAND_05_0002_F_1TANK_1GAS_IS_TIME_BYPATH					0x00a3//�ж���ʱ�ȴ�time_bypath

//��ȼѹ������·������
#define		COMMAND_05_0001_F_1TANK_1GAS_BYPATH_VALVE_OFF				0x00a4//��ȼѹ������·������
#define		COMMAND_05_0002_F_1TANK_1GAS_IS_BYPATH_VALVE_OFF			0x00a5//�жϹ�ȼѹ������·������

//�ر�ȼѹ�������ڷ���
#define		COMMAND_05_0001_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1			0x00a6//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x00a7//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2			0x00a8//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x00a9//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_1TANK_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3			0x00aa//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_1TANK_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x00ab//�жϹر�ȼѹ�������ڷ��ţ�������

//�ر�ȼѹ�������ڷ���
#define		COMMAND_05_0001_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x00ac//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1		0x00ad//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x00ae//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2		0x00af//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_1TANK_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x00b0//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_1TANK_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3		0x00b1//�жϹر�ȼѹ�������ڷ��ţ�������

//�ؽ������ѹ��·���ӷ���
#define		COMMAND_05_0001_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO1				0x00b2//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO1			0x00b3//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO2				0x00b4//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO2			0x00b5//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_1TANK_1GAS_IN_TANK_VALVE_OFF_NO3				0x00b6//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_05_0006_F_1TANK_1GAS_IS_IN_TANK_VALVE_OFF_NO3			0x00b7//�жϹؽ������ѹ��·���ӷ��ţ�������

//����ȼ����״̬��
#define		COMMAND_05_0001_F_1TANK_1GAS_SET_STATE_GOOD						0x00b8//����ȼ����״̬��

//�ж�ѹ�����¶��Ƿ�����
#define		COMMAND_05_0001_F_1TANK_1GAS_IS_COMPRESSOR_TEMPERATURE			0x00b9//�ж�ѹ�����¶��Ƿ�����

//�ж��Ƿ���Ҫ����Һ��ģ���л�����
#define		COMMAND_05_0001_F_1TANK_1GAS_IS_NEED_EXCHANGE					0x00ba//�ж��Ƿ���Ҫ����Һ��ģ���л�����

//��ʱ�ȴ�time_delay3
#define		COMMAND_05_0001_F_1TANK_1GAS_TIME_DELAY3_START					0x00bb//��ʱ�ȴ�time_delay3��ʱ��ʼ
#define		COMMAND_05_0002_F_1TANK_1GAS_IS_TIME_DELAY3						0x00bc//�ж���ʱ�ȴ�time_delay3

//����Һ��ģ���л�����
#define		COMMAND_05_0001_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO1			0x00bd//Һ��ģ���л����򣬷��Ŷ�������һ��
#define		COMMAND_05_0002_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x00be//�ж�Һ��ģ���л����򣬷��Ŷ�������һ��
#define		COMMAND_05_0003_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO2			0x00bf//Һ��ģ���л����򣬷��Ŷ������ڶ���
#define		COMMAND_05_0004_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x00c0//�ж�Һ��ģ���л����򣬷��Ŷ������ڶ���
#define		COMMAND_05_0005_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO3			0x00c1//Һ��ģ���л����򣬷��Ŷ�����������
#define		COMMAND_05_0006_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x00c2//�ж�Һ��ģ���л����򣬷��Ŷ�����������
#define		COMMAND_05_0007_F_1TANK_1GAS_EXCHANGE_COOLER_VALVE_NO4			0x00c3//Һ��ģ���л����򣬷��Ŷ�����������
#define		COMMAND_05_0008_F_1TANK_1GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x00c4//�ж�Һ��ģ���л����򣬷��Ŷ�����������

//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		COMMAND_05_0001_F_1TANK_1GAS_IS_EXCHANGE_COOLER					0x00c5//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����

//Һ��ģ��ͣ��
#define		COMMAND_05_0001_F_1TANK_1GAS_COOLER_POWER_OFF					0x00c6//Һ��ģ��ͣ��

//����ѹ�����ϵ�
#define		COMMAND_05_0001_F_1TANK_1GAS_COMPRESSOR_POWER_OFF				0x00c7//�����豸����ָ��
//#define		COMMAND_05_0002_F_1TANK_1GAS_COMPRESSOR_TIME_1MIN_START			0x00c8//��ʱ1min��ʱ��ʼ
//#define		COMMAND_05_0003_F_1TANK_1GAS_COMPRESSOR_IS_TIME_1MIN			0x00c9//�жϼ�ʱ1min�Ƿ�

//�������������ϵ�
#define		COMMAND_05_0001_F_1TANK_1GAS_TGTHT530_POWER_OFF					0x00ca//�����豸����ָ��
#define		COMMAND_05_0002_F_1TANK_1GAS_TGTHT530_TIME_1MIN_START			0x00cb//��ʱ1min��ʱ��ʼ
#define		COMMAND_05_0003_F_1TANK_1GAS_TGTHT530_IS_TIME_1MIN				0x00cc//�жϼ�ʱ1min�Ƿ�



//------------------------------command---һ���������----������ƿ����-----------------------------------

//������ƿ���ӷ���---��һ����ƿ
#define		COMMAND_05_0001_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_ON				0x00cd//������ƿ���ӷ���
#define		COMMAND_05_0002_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_ON			0x00ce//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---��һ����ƿ
#define		COMMAND_05_0001_F_1TANK_2GAS_GAS1_TIME_DELAY2_START				0x00cf//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_05_0002_F_1TANK_2GAS_GAS1_IS_TIME_DELAY2				0x00d0//�ж���ʱ�ȴ�time_delay2


//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define		COMMAND_05_0001_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO1				0x00d1//�ɼ���ƿѹ������һ��
#define		COMMAND_05_0002_F_1TANK_2GAS_GAS1_TIME_30S_START_NO1			0x00d2//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO1				0x00d3//�ж϶�ʱ30s����һ��
#define		COMMAND_05_0004_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO2				0x00d4//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_05_0005_F_1TANK_2GAS_GAS1_TIME_30S_START_NO2			0x00d5//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO2				0x00d6//�ж϶�ʱ30s���ڶ���
#define		COMMAND_05_0007_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO3				0x00d7//�ɼ���ƿѹ����������
#define		COMMAND_05_0008_F_1TANK_2GAS_GAS1_TIME_30S_START_NO3			0x00d8//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO3				0x00d9//�ж϶�ʱ30s��������
#define		COMMAND_05_0010_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO4				0x00da//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_05_0011_F_1TANK_2GAS_GAS1_TIME_30S_START_NO4			0x00db//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_05_0012_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO4				0x00dc//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_05_0013_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO5				0x00dd//�ɼ���ƿѹ���������
#define		COMMAND_05_0014_F_1TANK_2GAS_GAS1_TIME_30S_START_NO5			0x00de//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_05_0015_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO5				0x00df//�ж϶�ʱ30s�������
#define		COMMAND_05_0016_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO6				0x00e0//�ɼ���ƿѹ����������
#define		COMMAND_05_0017_F_1TANK_2GAS_GAS1_TIME_30S_START_NO6			0x00e1//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0018_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO6				0x00e2//�ж϶�ʱ30s��������
#define		COMMAND_05_0019_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO7				0x00e3//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_05_0020_F_1TANK_2GAS_GAS1_TIME_30S_START_NO7			0x00e4//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_05_0021_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO7				0x00e5//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_05_0022_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO8				0x00e6//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_05_0023_F_1TANK_2GAS_GAS1_TIME_30S_START_NO8			0x00e7//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_05_0024_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO8				0x00e8//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_05_0025_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO9				0x00e9//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_05_0026_F_1TANK_2GAS_GAS1_TIME_30S_START_NO9			0x00ea//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_05_0027_F_1TANK_2GAS_GAS1_IS_TIME_30S_NO9				0x00eb//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_05_0028_F_1TANK_2GAS_GAS1_GAS_PRESSURE_NO10				0x00ec//�ɼ���ƿѹ������ʮ��
#define		COMMAND_05_0029_F_1TANK_2GAS_GAS1_IS_GAS_PRESSURE				0x00ed//ѹ���ж���ƿѹ���Ƿ�����


//�ж���ƿ�����Ƿ����---��һ����ƿ
#define		COMMAND_05_0001_F_1TANK_2GAS_GAS1_IS_COMP_GAS_OVER				0x00ee//�ж���ƿ�����Ƿ����


//��ȼ·��ƿ���ӷ���---��һ����ƿ
#define		COMMAND_05_0001_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1			0x00ef//��ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1		0x00f0//�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2			0x00f1//��ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2		0x00f2//�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_1TANK_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3			0x00f3//��ȼ·��ƿ���ӷ��ţ�������
#define		COMMAND_05_0006_F_1TANK_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3		0x00f4//�жϹ�ȼ·��ƿ���ӷ��ţ�������



//������ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_05_0001_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_ON				0x00f5//������ƿ���ӷ���
#define		COMMAND_05_0002_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_ON			0x00f6//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define		COMMAND_05_0001_F_1TANK_2GAS_GAS2_TIME_DELAY2_START				0x00f7//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_05_0002_F_1TANK_2GAS_GAS2_IS_TIME_DELAY2				0x00f8//�ж���ʱ�ȴ�time_delay2



//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define		COMMAND_05_0001_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO1				0x00f9//�ɼ���ƿѹ������һ��
#define		COMMAND_05_0002_F_1TANK_2GAS_GAS2_TIME_30S_START_NO1			0x00fa//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO1				0x00fb//�ж϶�ʱ30s����һ��
#define		COMMAND_05_0004_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO2				0x00fc//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_05_0005_F_1TANK_2GAS_GAS2_TIME_30S_START_NO2			0x00fd//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO2				0x00fe//�ж϶�ʱ30s���ڶ���
#define		COMMAND_05_0007_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO3				0x00ff//�ɼ���ƿѹ����������
#define		COMMAND_05_0008_F_1TANK_2GAS_GAS2_TIME_30S_START_NO3			0x0100//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO3				0x0101//�ж϶�ʱ30s��������
#define		COMMAND_05_0010_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO4				0x0102//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_05_0011_F_1TANK_2GAS_GAS2_TIME_30S_START_NO4			0x0103//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_05_0012_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO4				0x0104//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_05_0013_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO5				0x0105//�ɼ���ƿѹ���������
#define		COMMAND_05_0014_F_1TANK_2GAS_GAS2_TIME_30S_START_NO5			0x0106//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_05_0015_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO5				0x0107//�ж϶�ʱ30s�������
#define		COMMAND_05_0016_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO6				0x0108//�ɼ���ƿѹ����������
#define		COMMAND_05_0017_F_1TANK_2GAS_GAS2_TIME_30S_START_NO6			0x0109//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0018_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO6				0x010a//�ж϶�ʱ30s��������
#define		COMMAND_05_0019_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO7				0x010b//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_05_0020_F_1TANK_2GAS_GAS2_TIME_30S_START_NO7			0x010c//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_05_0021_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO7				0x010d//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_05_0022_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO8				0x010e//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_05_0023_F_1TANK_2GAS_GAS2_TIME_30S_START_NO8			0x010f//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_05_0024_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO8				0x0110//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_05_0025_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO9				0x0111//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_05_0026_F_1TANK_2GAS_GAS2_TIME_30S_START_NO9			0x0112//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_05_0027_F_1TANK_2GAS_GAS2_IS_TIME_30S_NO9				0x0113//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_05_0028_F_1TANK_2GAS_GAS2_GAS_PRESSURE_NO10				0x0114//�ɼ���ƿѹ������ʮ��
#define		COMMAND_05_0029_F_1TANK_2GAS_GAS2_IS_GAS_PRESSURE				0x0115//ѹ���ж���ƿѹ���Ƿ�����

//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define		COMMAND_05_0001_F_1TANK_2GAS_GAS2_IS_COMP_GAS_OVER				0x0116//�ж���ƿ�����Ƿ����


//��ȼ·��ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_05_0001_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1			0x0117//��ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1		0x0118//�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2			0x0119//��ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2		0x011a//�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_1TANK_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3			0x011b//��ȼ·��ƿ���ӷ��ţ�������
#define		COMMAND_05_0006_F_1TANK_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3		0x011c//�жϹ�ȼ·��ƿ���ӷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define		COMMAND_05_0001_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO1	0x011d//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_05_0002_F_1TANK_2GAS_FIRST_TIME_12S_START_NO1		0x011e//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO1			0x011f//�ж϶�ʱ12s����һ��
#define		COMMAND_05_0004_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO2	0x0120//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_05_0005_F_1TANK_2GAS_FIRST_TIME_12S_START_NO2		0x0121//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO2			0x0122//�ж϶�ʱ12s���ڶ���
#define		COMMAND_05_0007_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO3	0x0123//�ɼ�ѹ��������ѹ����������
#define		COMMAND_05_0008_F_1TANK_2GAS_FIRST_TIME_12S_START_NO3		0x0124//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_1TANK_2GAS_FIRST_IS_TIME_12S_NO3			0x0125//�ж϶�ʱ12s��������
#define		COMMAND_05_0010_F_1TANK_2GAS_FIRST_ISOLATION_PRESSURE_NO4	0x0126//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_05_0011_F_1TANK_2GAS_FIRST_IS_ISOLATION				0x0127//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//�ر�ȼѹ�������ڷ���
#define		COMMAND_05_0001_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x0128//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1	0x0129//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x012a//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2	0x012b//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x012c//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3	0x012d//�жϹر�ȼѹ�������ڷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ��������ڶ���
#define		COMMAND_05_0001_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO1	0x012e//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_05_0002_F_1TANK_2GAS_SECOND_TIME_12S_START_NO1		0x012f//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO1			0x0130//�ж϶�ʱ12s����һ��
#define		COMMAND_05_0004_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO2	0x0131//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_05_0005_F_1TANK_2GAS_SECOND_TIME_12S_START_NO2		0x0132//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO2			0x0133//�ж϶�ʱ12s���ڶ���
#define		COMMAND_05_0007_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO3	0x0134//�ɼ�ѹ��������ѹ����������
#define		COMMAND_05_0008_F_1TANK_2GAS_SECOND_TIME_12S_START_NO3		0x0135//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_1TANK_2GAS_SECOND_IS_TIME_12S_NO3			0x0136//�ж϶�ʱ12s��������
#define		COMMAND_05_0010_F_1TANK_2GAS_SECOND_ISOLATION_PRESSURE_NO4	0x0137//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_05_0011_F_1TANK_2GAS_SECOND_IS_ISOLATION			0x0138//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//ȼѹ����ͣ��
#define		COMMAND_05_0001_F_1TANK_2GAS_COMPRESSOR_STOP					0x0139//�����豸����ָ�ѹ����ͣ��
#define		COMMAND_05_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START			0x013a//��ʱ1min��ʱ��ʼ
#define		COMMAND_05_0003_F_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN			0x013b//�ж�1min��ʱ


//�ж�ȼѹ����ͣ���Ƿ�����
#define		COMMAND_05_0001_F_1TANK_2GAS_COMPRESSOR_V_NO1					0x013c//�ɼ����ת�٣���һ��
#define		COMMAND_05_0002_F_1TANK_2GAS_COMPRESSOR_V_NO2					0x013d//�ɼ����ת�٣��ڶ���
#define		COMMAND_05_0003_F_1TANK_2GAS_COMPRESSOR_V_NO3					0x013e//�ɼ����ת�٣�������
#define		COMMAND_05_0004_F_1TANK_2GAS_COMPRESSOR_V_NO4					0x013f//�ɼ����ת�٣����Ĵ�
#define		COMMAND_05_0005_F_1TANK_2GAS_COMPRESSOR_V_NO5					0x0140//�ɼ����ת�٣������
#define		COMMAND_05_0006_F_1TANK_2GAS_COMPRESSOR_V_NO6					0x0141//�ɼ����ת�٣�������
#define		COMMAND_05_0007_F_1TANK_2GAS_COMPRESSOR_V_NO7					0x0142//�ɼ����ת�٣����ߴ�
#define		COMMAND_05_0008_F_1TANK_2GAS_COMPRESSOR_V_NO8					0x0143//�ɼ����ת�٣��ڰ˴�
#define		COMMAND_05_0009_F_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO1		0x0144//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_05_0010_F_1TANK_2GAS_TIME_12S_START						0x0145//��ʱ12s��ʱ��ʼ
#define		COMMAND_05_0011_F_1TANK_2GAS_IS_TIME_12S						0x0146//�ж϶�ʱ12s
#define		COMMAND_05_0012_F_1TANK_2GAS_OUT_COMPRESSOR_PRESSURE_NO2		0x0147//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_05_0013_F_1TANK_2GAS_IS_COMPRESSOR_STOP					0x0148//�ж�ȼѹ����ͣ���Ƿ�����


//��ȼѹ������·������
#define		COMMAND_05_0001_F_1TANK_2GAS_BYPATH_VALVE_ON					0x0149//��ȼѹ������·������
#define		COMMAND_05_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_ON					0x014a//�жϿ�ȼѹ������·������


//��ʱ�ȴ�time_bypath
#define		COMMAND_05_0001_F_1TANK_2GAS_TIME_BYPATH_START					0x014b//��ʱ�ȴ�time_bypath��ʱ����
#define		COMMAND_05_0002_F_1TANK_2GAS_IS_TIME_BYPATH						0x014c//�ж���ʱ�ȴ�time_bypath


//��ȼѹ������·������
#define		COMMAND_05_0001_F_1TANK_2GAS_BYPATH_VALVE_OFF					0x014d//��ȼѹ������·������
#define		COMMAND_05_0002_F_1TANK_2GAS_IS_BYPATH_VALVE_OFF				0x014e//�жϹ�ȼѹ������·������

//�ر�ȼѹ�������ڷ���
#define		COMMAND_05_0001_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1			0x014f//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x0150//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2			0x0151//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x0152//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_1TANK_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3			0x0153//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_1TANK_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x0154//�жϹر�ȼѹ�������ڷ��ţ�������

//�ر�ȼѹ�������ڷ���
#define		COMMAND_05_0001_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x0155//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1		0x0156//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0157//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0158//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_1TANK_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x0159//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_1TANK_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3		0x015a//�жϹر�ȼѹ�������ڷ��ţ�������


//�ؽ������ѹ��·���ӷ���
#define		COMMAND_05_0001_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO1				0x015b//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO1			0x015c//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO2				0x015d//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO2			0x015e//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_1TANK_2GAS_IN_TANK_VALVE_OFF_NO3				0x015f//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_05_0006_F_1TANK_2GAS_IS_IN_TANK_VALVE_OFF_NO3			0x0160//�жϹؽ������ѹ��·���ӷ��ţ�������


//����ȼ����״̬��
#define		COMMAND_05_0001_F_1TANK_2GAS_SET_STATE_GOOD						0x0161//����ȼ����״̬��


//�ж�ѹ�����¶��Ƿ�����
#define		COMMAND_05_0001_F_1TANK_2GAS_IS_COMPRESSOR_TEMPERATURE			0x0162//�ж�ѹ�����¶��Ƿ�����

//�ж��Ƿ���Ҫ����Һ��ģ���л�����
#define		COMMAND_05_0001_F_1TANK_2GAS_IS_NEED_EXCHANGE					0x0163//�ж��Ƿ���Ҫ����Һ��ģ���л�����

//��ʱ�ȴ�time_delay3
#define		COMMAND_05_0001_F_1TANK_2GAS_TIME_DELAY3_START					0x0164//��ʱ�ȴ�time_delay3��ʱ��ʼ
#define		COMMAND_05_0002_F_1TANK_2GAS_IS_TIME_DELAY3						0x0165//�ж���ʱ�ȴ�time_delay3


//����Һ��ģ���л�����
#define		COMMAND_05_0001_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO1			0x0166//Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_05_0002_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x0167//�ж�Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_05_0003_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO2			0x0168//Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_05_0004_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x0169//�ж�Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_05_0005_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO3			0x016a//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_05_0006_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x016b//�ж�Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_05_0007_F_1TANK_2GAS_EXCHANGE_COOLER_VALVE_NO4			0x016c//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_05_0008_F_1TANK_2GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x016d//�ж�Һ��ģ���л�����,���Ŷ�����������

//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		COMMAND_05_0001_F_1TANK_2GAS_IS_EXCHANGE_COOLER					0x016e//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����

//Һ��ģ��ͣ��
#define		COMMAND_05_0001_F_1TANK_2GAS_COOLER_POWER_OFF					0x016f//Һ��ģ��ͣ��

//����ѹ�����ϵ�
#define		COMMAND_05_0001_F_1TANK_2GAS_COMPRESSOR_POWER_OFF				0x0170//�����豸����ָ��
//#define		COMMAND_05_0002_F_1TANK_2GAS_COMPRESSOR_TIME_1MIN_START			0x0171//��ʱ1min��ʱ��ʼ
//#define		COMMAND_05_0003_F_1TANK_2GAS_COMPRESSOR_IS_TIME_1MIN			0x0172//�жϼ�ʱ1min�Ƿ�

//�������������ϵ�
#define		COMMAND_05_0001_F_1TANK_2GAS_TGTHT530_POWER_OFF					0x0173//�����豸����ָ��
#define		COMMAND_05_0002_F_1TANK_2GAS_TGTHT530_TIME_1MIN_START			0x0174//��ʱ1min��ʱ��ʼ
#define		COMMAND_05_0003_F_1TANK_2GAS_TGTHT530_IS_TIME_1MIN				0x0175//�жϼ�ʱ1min�Ƿ�


//------------------------------command---�����������----��һ���������-----------------------------------

//���������ѹ��·���ӷ���---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_IN_TANK_VALVE_ON					0x0176//���������ѹ��·���ӷ���
#define		COMMAND_05_0002_F_2TANK_TANK1_IS_IN_TANK_VALVE_ON				0x0177//�жϿ��������ѹ��·���ӷ���


//ͨ��ѹ���жϿ������䷧��---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_IS_IN_TANK_VALVE_ON_PRESSURE		0x0178//ͨ��ѹ���жϿ����ӷ���


//��ȼѹ�������ڷ���---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO1		0x0179//��ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO1		0x017a//�жϿ�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO2		0x017b//��ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO2		0x017c//�жϿ�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK1_IN_COMPRESSOR_VALVE_ON_NO3		0x017d//��ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK1_IS_IN_COMPRESSOR_VALVE_ON_NO3		0x017e//�жϿ�ȼѹ�������ڷ��ţ�������


//��ʱ�ȴ�time_delay1---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_TIME_DELAY1_START					0x017f//��ʱ�ȴ�time_delay1��ʱ��ʼ
#define		COMMAND_05_0002_F_2TANK_TANK1_IS_TIME_DELAY1					0x0180//�ж���ʱ�ȴ�time_delay1


//�ж�ѹ��������ѹ���Ƿ�����---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_IS_IN_COMPRESSOR_PRESSURE			0x0181//�ж�ѹ��������ѹ���Ƿ�����


//ȼѹ��������---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_COMPRESSOR_START					0x0182//�����豸����ָ�ѹ��������
#define		COMMAND_05_0002_F_2TANK_TANK1_COMPRESSOR_TIME_1MIN_START		0x0183//��ʱ1min��ʱ��ʼ
#define		COMMAND_05_0003_F_2TANK_TANK1_COMPRESSOR_IS_TIME_1MIN			0x0184//�ж�1min��ʱ
#define		COMMAND_05_0004_F_2TANK_TANK1_IS_COMPRESSOR_START				0x0185//ͨ�����������ж������Ƿ�����


//�ж�ѹ��������ѹ���Ƿ�����---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_IS_OUT_COMPRESSOR_PRESSURE		0x0186//�ж�ѹ��������ѹ���Ƿ�����


//��ȼѹ�������ڷ���---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_OUT_COMPRESSOR_VALVE_ON			0x0187//��ȼѹ�������ڷ���
#define		COMMAND_05_0002_F_2TANK_TANK1_IS_OUT_COMPRESSOR_VALVE_ON		0x0188//�жϿ�ȼѹ�������ڷ���


//�жϳ�����ƿ����---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_NUMBER_COMP_GAS					0x0189//�жϳ�����ƿ����


//------------------------------command---�����������----��һ���������----һ����ƿ����--------------------

//������ƿ���ӷ���---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_1GAS_IN_GAS_VALVE_ON				0x018a//������ƿ���ӷ���
#define		COMMAND_05_0002_F_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_ON			0x018b//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_1GAS_TIME_DELAY2_START			0x018c//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_05_0002_F_2TANK_TANK1_1GAS_IS_TIME_DELAY2				0x018d//�ж���ʱ�ȴ�time_delay2


//�ж���ƿѹ���Ƿ�����---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_1GAS_GAS_PRESSURE_NO1				0x018e//�ɼ���ƿѹ������һ��
#define		COMMAND_05_0002_F_2TANK_TANK1_1GAS_TIME_30S_START_NO1			0x018f//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_2TANK_TANK1_1GAS_IS_TIME_30S_NO1				0x0190//�ж϶�ʱ30s����һ��
#define		COMMAND_05_0004_F_2TANK_TANK1_1GAS_GAS_PRESSURE_NO2				0x0191//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK1_1GAS_TIME_30S_START_NO2			0x0192//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_2TANK_TANK1_1GAS_IS_TIME_30S_NO2				0x0193//�ж϶�ʱ30s���ڶ���
#define		COMMAND_05_0007_F_2TANK_TANK1_1GAS_GAS_PRESSURE_NO3				0x0194//�ɼ���ƿѹ����������
#define		COMMAND_05_0008_F_2TANK_TANK1_1GAS_TIME_30S_START_NO3			0x0195//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_2TANK_TANK1_1GAS_IS_TIME_30S_NO3				0x0196//�ж϶�ʱ30s��������
#define		COMMAND_05_0010_F_2TANK_TANK1_1GAS_GAS_PRESSURE_NO4				0x0197//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_05_0011_F_2TANK_TANK1_1GAS_TIME_30S_START_NO4			0x0198//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_05_0012_F_2TANK_TANK1_1GAS_IS_TIME_30S_NO4				0x0199//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_05_0013_F_2TANK_TANK1_1GAS_GAS_PRESSURE_NO5				0x019a//�ɼ���ƿѹ���������
#define		COMMAND_05_0014_F_2TANK_TANK1_1GAS_TIME_30S_START_NO5			0x019b//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_05_0015_F_2TANK_TANK1_1GAS_IS_TIME_30S_NO5				0x019c//�ж϶�ʱ30s�������
#define		COMMAND_05_0016_F_2TANK_TANK1_1GAS_GAS_PRESSURE_NO6				0x019d//�ɼ���ƿѹ����������
#define		COMMAND_05_0017_F_2TANK_TANK1_1GAS_TIME_30S_START_NO6			0x019e//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0018_F_2TANK_TANK1_1GAS_IS_TIME_30S_NO6				0x019f//�ж϶�ʱ30s��������
#define		COMMAND_05_0019_F_2TANK_TANK1_1GAS_GAS_PRESSURE_NO7				0x01a0//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_05_0020_F_2TANK_TANK1_1GAS_TIME_30S_START_NO7			0x01a1//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_05_0021_F_2TANK_TANK1_1GAS_IS_TIME_30S_NO7				0x01a2//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_05_0022_F_2TANK_TANK1_1GAS_GAS_PRESSURE_NO8				0x01a3//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_05_0023_F_2TANK_TANK1_1GAS_TIME_30S_START_NO8			0x01a4//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_05_0024_F_2TANK_TANK1_1GAS_IS_TIME_30S_NO8				0x01a5//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_05_0025_F_2TANK_TANK1_1GAS_GAS_PRESSURE_NO9				0x01a6//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_05_0026_F_2TANK_TANK1_1GAS_TIME_30S_START_NO9			0x01a7//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_05_0027_F_2TANK_TANK1_1GAS_IS_TIME_30S_NO9				0x01a8//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_05_0028_F_2TANK_TANK1_1GAS_GAS_PRESSURE_NO10			0x01a9//�ɼ���ƿѹ������ʮ��
#define		COMMAND_05_0029_F_2TANK_TANK1_1GAS_IS_GAS_PRESSURE				0x01aa//ѹ���ж���ƿѹ���Ƿ�����

//�ж���ƿ�����Ƿ����---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_1GAS_IS_COMP_GAS_OVER				0x01ab//�ж���ƿ�����Ƿ����


//��ȼ·��ƿ���ӷ���---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO1			0x01ac//��ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO1		0x01ad//�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO2			0x01ae//��ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO2		0x01af//�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK1_1GAS_IN_GAS_VALVE_OFF_NO3			0x01b0//��ȼ·��ƿ���ӷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK1_1GAS_IS_IN_GAS_VALVE_OFF_NO3		0x01b1//�жϹ�ȼ·��ƿ���ӷ��ţ�������


//�ؽ������ѹ��·���ӷ���---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO1			0x01b2//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO1			0x01b3//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO2			0x01b4//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO2			0x01b5//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK1_1GAS_IN_TANK_VALVE_OFF_NO3			0x01b6//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_OFF_NO3			0x01b7//�жϹؽ������ѹ��·���ӷ��ţ�������

//ͨ��ѹ���жϹؽ����䲹�ӷ�---��һ������
#define		COMMAND_05_0001_F_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO1	0x01b8//ͨ��ѹ���жϹؽ����䲹�ӷ�����һ��
#define		COMMAND_05_0002_F_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO2	0x01b9//ͨ��ѹ���жϹؽ����䲹�ӷ����ڶ���
#define		COMMAND_05_0003_F_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO3	0x01ba//ͨ��ѹ���жϹؽ����䲹�ӷ���������
#define		COMMAND_05_0004_F_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO4	0x01bb//ͨ��ѹ���жϹؽ����䲹�ӷ���������
#define		COMMAND_05_0005_F_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE_NO5	0x01bc//ͨ��ѹ���жϹؽ����䲹�ӷ���������
#define		COMMAND_05_0006_F_2TANK_TANK1_1GAS_IS_IN_TANK_VALVE_PRESSURE		0x01bd//ͨ��ѹ���жϹؽ����䲹�ӷ�����ȡ��


//------------------------------command---�����������----��һ���������----������ƿ����--------------------

//������ƿ���ӷ���---��һ����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_ON				0x01be//������ƿ���ӷ���
#define		COMMAND_05_0002_F_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_ON			0x01bf//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---��һ����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK1_2GAS_GAS1_TIME_DELAY2_START			0x01c0//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_05_0002_F_2TANK_TANK1_2GAS_GAS1_IS_TIME_DELAY2				0x01c1//�ж���ʱ�ȴ�time_delay2

//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO1			0x01c2//�ɼ���ƿѹ������һ��
#define		COMMAND_05_0002_F_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO1			0x01c3//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO1				0x01c4//�ж϶�ʱ30s����һ��
#define		COMMAND_05_0004_F_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO2			0x01c5//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO2			0x01c6//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO2				0x01c7//�ж϶�ʱ30s���ڶ���
#define		COMMAND_05_0007_F_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO3			0x01c8//�ɼ���ƿѹ����������
#define		COMMAND_05_0008_F_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO3			0x01c9//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO3				0x01ca//�ж϶�ʱ30s��������
#define		COMMAND_05_0010_F_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO4			0x01cb//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_05_0011_F_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO4			0x01cc//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_05_0012_F_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO4				0x01cd//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_05_0013_F_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO5			0x01ce//�ɼ���ƿѹ���������
#define		COMMAND_05_0014_F_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO5			0x01cf//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_05_0015_F_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO5				0x01d0//�ж϶�ʱ30s�������
#define		COMMAND_05_0016_F_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO6			0x01d1//�ɼ���ƿѹ����������
#define		COMMAND_05_0017_F_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO6			0x01d2//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0018_F_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO6				0x01d3//�ж϶�ʱ30s��������
#define		COMMAND_05_0019_F_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO7			0x01d4//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_05_0020_F_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO7			0x01d5//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_05_0021_F_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO7				0x01d6//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_05_0022_F_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO8			0x01d7//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_05_0023_F_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO8			0x01d8//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_05_0024_F_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO8				0x01d9//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_05_0025_F_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO9			0x01da//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_05_0026_F_2TANK_TANK1_2GAS_GAS1_TIME_30S_START_NO9			0x01db//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_05_0027_F_2TANK_TANK1_2GAS_GAS1_IS_TIME_30S_NO9				0x01dc//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_05_0028_F_2TANK_TANK1_2GAS_GAS1_GAS_PRESSURE_NO10			0x01dd//�ɼ���ƿѹ������ʮ��
#define		COMMAND_05_0029_F_2TANK_TANK1_2GAS_GAS1_IS_GAS_PRESSURE				0x01de//ѹ���ж���ƿѹ���Ƿ�����

//�ж���ƿ�����Ƿ����---��һ����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK1_2GAS_GAS1_IS_COMP_GAS_OVER			0x01df//�ж���ƿ�����Ƿ����


//��ȼ·��ƿ���ӷ���---��һ����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1		0x01e0//��ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1		0x01e1//�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2		0x01e2//��ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2		0x01e3//�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK1_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3		0x01e4//��ȼ·��ƿ���ӷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK1_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3		0x01e5//�жϹ�ȼ·��ƿ���ӷ��ţ�������


//������ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_ON				0x01e6//������ƿ���ӷ���
#define		COMMAND_05_0002_F_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_ON			0x01e7//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK1_2GAS_GAS2_TIME_DELAY2_START			0x01e8//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_05_0002_F_2TANK_TANK1_2GAS_GAS2_IS_TIME_DELAY2				0x01e9//�ж���ʱ�ȴ�time_delay2


//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO1			0x01ea//�ɼ���ƿѹ������һ��
#define		COMMAND_05_0002_F_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO1			0x01eb//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO1				0x01ec//�ж϶�ʱ30s����һ��
#define		COMMAND_05_0004_F_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO2			0x01ed//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO2			0x01ee//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO2				0x01ef//�ж϶�ʱ30s���ڶ���
#define		COMMAND_05_0007_F_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO3			0x01f0//�ɼ���ƿѹ����������
#define		COMMAND_05_0008_F_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO3			0x01f1//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO3				0x01f2//�ж϶�ʱ30s��������
#define		COMMAND_05_0010_F_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO4			0x01f3//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_05_0011_F_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO4			0x01f4//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_05_0012_F_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO4				0x01f5//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_05_0013_F_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO5			0x01f6//�ɼ���ƿѹ���������
#define		COMMAND_05_0014_F_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO5			0x01f7//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_05_0015_F_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO5				0x01f8//�ж϶�ʱ30s�������
#define		COMMAND_05_0016_F_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO6			0x01f9//�ɼ���ƿѹ����������
#define		COMMAND_05_0017_F_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO6			0x01fa//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0018_F_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO6				0x01fb//�ж϶�ʱ30s��������
#define		COMMAND_05_0019_F_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO7			0x01fc//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_05_0020_F_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO7			0x01fd//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_05_0021_F_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO7				0x01fe//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_05_0022_F_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO8			0x01ff//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_05_0023_F_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO8			0x0200//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_05_0024_F_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO8				0x0201//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_05_0025_F_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO9			0x0202//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_05_0026_F_2TANK_TANK1_2GAS_GAS2_TIME_30S_START_NO9			0x0203//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_05_0027_F_2TANK_TANK1_2GAS_GAS2_IS_TIME_30S_NO9				0x0204//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_05_0028_F_2TANK_TANK1_2GAS_GAS2_GAS_PRESSURE_NO10			0x0205//�ɼ���ƿѹ������ʮ��
#define		COMMAND_05_0029_F_2TANK_TANK1_2GAS_GAS2_IS_GAS_PRESSURE				0x0206//ѹ���ж���ƿѹ���Ƿ�����


//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK1_2GAS_GAS2_IS_COMP_GAS_OVER			0x0207//�ж���ƿ�����Ƿ����

//��ȼ·��ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1		0x0208//��ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1		0x0209//�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2		0x020a//��ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2		0x020b//�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK1_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3		0x020c//��ȼ·��ƿ���ӷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK1_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3		0x020d//�жϹ�ȼ·��ƿ���ӷ��ţ�������


//�ؽ������ѹ��·���ӷ���
#define		COMMAND_05_0001_F_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO1			0x020e//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO1			0x020f//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO2			0x0210//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO2			0x0211//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK1_2GAS_IN_TANK_VALVE_OFF_NO3			0x0212//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_OFF_NO3			0x0213//�жϹؽ������ѹ��·���ӷ��ţ�������


//ͨ��ѹ���жϹؽ����䲹�ӷ�
#define		COMMAND_05_0001_F_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO1	0x0214//ͨ��ѹ���жϹؽ����䲹�ӷ�����һ��
#define		COMMAND_05_0002_F_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO2	0x0215//ͨ��ѹ���жϹؽ����䲹�ӷ����ڶ���
#define		COMMAND_05_0003_F_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO3	0x0216//ͨ��ѹ���жϹؽ����䲹�ӷ���������
#define		COMMAND_05_0004_F_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO4	0x0217//ͨ��ѹ���жϹؽ����䲹�ӷ���������
#define		COMMAND_05_0005_F_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE_NO5	0x0218//ͨ��ѹ���жϹؽ����䲹�ӷ���������
#define		COMMAND_05_0006_F_2TANK_TANK1_2GAS_IS_IN_TANK_VALVE_PRESSURE		0x0219//ͨ��ѹ���жϹؽ����䲹�ӷ�����ȡ��


//------------------------------command---�����������----�ڶ����������-----------------------------------

//���������ѹ��·���ӷ���---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_IN_TANK_VALVE_ON					0x021a//���������ѹ��·���ӷ���
#define		COMMAND_05_0002_F_2TANK_TANK2_IS_IN_TANK_VALVE_ON				0x021b//�жϿ��������ѹ��·���ӷ���


//ͨ��ѹ���жϿ������䷧��---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_IS_IN_TANK_VALVE_ON_PRESSURE		0x021c//ͨ��ѹ���жϿ����ӷ���

//�жϳ�����ƿ����---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_NUMBER_COMP_GAS					0x021d//�жϳ�����ƿ����


//------------------------------command---�����������----�ڶ����������----һ����ƿ����--------------------

//������ƿ���ӷ���---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_IN_GAS_VALVE_ON				0x021e//������ƿ���ӷ���
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_ON			0x021f//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_TIME_DELAY2_START			0x0220//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_IS_TIME_DELAY2				0x0221//�ж���ʱ�ȴ�time_delay2


//�ж���ƿѹ���Ƿ�����---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_GAS_PRESSURE_NO1				0x0222//�ɼ���ƿѹ������һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_TIME_30S_START_NO1			0x0223//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_1GAS_IS_TIME_30S_NO1				0x0224//�ж϶�ʱ30s����һ��
#define		COMMAND_05_0004_F_2TANK_TANK2_1GAS_GAS_PRESSURE_NO2				0x0225//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_1GAS_TIME_30S_START_NO2			0x0226//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_2TANK_TANK2_1GAS_IS_TIME_30S_NO2				0x0227//�ж϶�ʱ30s���ڶ���
#define		COMMAND_05_0007_F_2TANK_TANK2_1GAS_GAS_PRESSURE_NO3				0x0228//�ɼ���ƿѹ����������
#define		COMMAND_05_0008_F_2TANK_TANK2_1GAS_TIME_30S_START_NO3			0x0229//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_2TANK_TANK2_1GAS_IS_TIME_30S_NO3				0x022a//�ж϶�ʱ30s��������
#define		COMMAND_05_0010_F_2TANK_TANK2_1GAS_GAS_PRESSURE_NO4				0x022b//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_05_0011_F_2TANK_TANK2_1GAS_TIME_30S_START_NO4			0x022c//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_05_0012_F_2TANK_TANK2_1GAS_IS_TIME_30S_NO4				0x022d//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_05_0013_F_2TANK_TANK2_1GAS_GAS_PRESSURE_NO5				0x022e//�ɼ���ƿѹ���������
#define		COMMAND_05_0014_F_2TANK_TANK2_1GAS_TIME_30S_START_NO5			0x022f//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_05_0015_F_2TANK_TANK2_1GAS_IS_TIME_30S_NO5				0x0230//�ж϶�ʱ30s�������
#define		COMMAND_05_0016_F_2TANK_TANK2_1GAS_GAS_PRESSURE_NO6				0x0231//�ɼ���ƿѹ����������
#define		COMMAND_05_0017_F_2TANK_TANK2_1GAS_TIME_30S_START_NO6			0x0232//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0018_F_2TANK_TANK2_1GAS_IS_TIME_30S_NO6				0x0233//�ж϶�ʱ30s��������
#define		COMMAND_05_0019_F_2TANK_TANK2_1GAS_GAS_PRESSURE_NO7				0x0234//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_05_0020_F_2TANK_TANK2_1GAS_TIME_30S_START_NO7			0x0235//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_05_0021_F_2TANK_TANK2_1GAS_IS_TIME_30S_NO7				0x0236//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_05_0022_F_2TANK_TANK2_1GAS_GAS_PRESSURE_NO8				0x0237//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_05_0023_F_2TANK_TANK2_1GAS_TIME_30S_START_NO8			0x0238//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_05_0024_F_2TANK_TANK2_1GAS_IS_TIME_30S_NO8				0x0239//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_05_0025_F_2TANK_TANK2_1GAS_GAS_PRESSURE_NO9				0x023a//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_05_0026_F_2TANK_TANK2_1GAS_TIME_30S_START_NO9			0x023b//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_05_0027_F_2TANK_TANK2_1GAS_IS_TIME_30S_NO9				0x023c//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_05_0028_F_2TANK_TANK2_1GAS_GAS_PRESSURE_NO10			0x023d//�ɼ���ƿѹ������ʮ��
#define		COMMAND_05_0029_F_2TANK_TANK2_1GAS_IS_GAS_PRESSURE				0x023e//ѹ���ж���ƿѹ���Ƿ�����


//�ж���ƿ�����Ƿ����---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_IS_COMP_GAS_OVER				0x023f//�ж���ƿ�����Ƿ����


//��ȼ·��ƿ���ӷ���---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO1			0x0240//��ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO1		0x0241//�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO2			0x0242//��ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO2		0x0243//�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_1GAS_IN_GAS_VALVE_OFF_NO3			0x0244//��ȼ·��ƿ���ӷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK2_1GAS_IS_IN_GAS_VALVE_OFF_NO3		0x0245//�жϹ�ȼ·��ƿ���ӷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO1	0x0246//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO1		0x0247//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO1		0x0248//�ж϶�ʱ12s����һ��
#define		COMMAND_05_0004_F_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO2	0x0249//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO2		0x024a//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO2		0x024b//�ж϶�ʱ12s���ڶ���
#define		COMMAND_05_0007_F_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO3	0x024c//�ɼ�ѹ��������ѹ����������
#define		COMMAND_05_0008_F_2TANK_TANK2_1GAS_FIRST_TIME_12S_START_NO3		0x024d//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_2TANK_TANK2_1GAS_FIRST_IS_TIME_12S_NO3		0x024e//�ж϶�ʱ12s��������
#define		COMMAND_05_0010_F_2TANK_TANK2_1GAS_FIRST_ISOLATION_PRESSURE_NO4	0x024f//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_05_0011_F_2TANK_TANK2_1GAS_FIRST_IS_ISOLATION			0x0250//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//�ر�ȼѹ�������ڷ���---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x0251//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1	0x0252//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x0253//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2	0x0254//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x0255//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3	0x0256//�жϹر�ȼѹ�������ڷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO1	0x0257//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO1		0x0258//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO1			0x0259//�ж϶�ʱ12s����һ��
#define		COMMAND_05_0004_F_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO2	0x025a//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO2		0x025b//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO2			0x025c//�ж϶�ʱ12s���ڶ���
#define		COMMAND_05_0007_F_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO3	0x025d//�ɼ�ѹ��������ѹ����������
#define		COMMAND_05_0008_F_2TANK_TANK2_1GAS_SECOND_TIME_12S_START_NO3		0x025e//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_2TANK_TANK2_1GAS_SECOND_IS_TIME_12S_NO3			0x025f//�ж϶�ʱ12s��������
#define		COMMAND_05_0010_F_2TANK_TANK2_1GAS_SECOND_ISOLATION_PRESSURE_NO4	0x0260//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_05_0011_F_2TANK_TANK2_1GAS_SECOND_IS_ISOLATION				0x0261//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//ȼѹ����ͣ��---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_COMPRESSOR_STOP					0x0262//�����豸����ָ�ѹ����ͣ��
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START		0x0263//��ʱ1min��ʱ��ʼ
#define		COMMAND_05_0003_F_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN			0x0264//�ж�1min��ʱ


//�ж�ȼѹ����ͣ���Ƿ�����---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_COMPRESSOR_V_NO1					0x0265//�ɼ����ת�٣���һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_COMPRESSOR_V_NO2					0x0266//�ɼ����ת�٣��ڶ���
#define		COMMAND_05_0003_F_2TANK_TANK2_1GAS_COMPRESSOR_V_NO3					0x0267//�ɼ����ת�٣�������
#define		COMMAND_05_0004_F_2TANK_TANK2_1GAS_COMPRESSOR_V_NO4					0x0268//�ɼ����ת�٣����Ĵ�
#define		COMMAND_05_0005_F_2TANK_TANK2_1GAS_COMPRESSOR_V_NO5					0x0269//�ɼ����ת�٣������
#define		COMMAND_05_0006_F_2TANK_TANK2_1GAS_COMPRESSOR_V_NO6					0x026a//�ɼ����ת�٣�������
#define		COMMAND_05_0007_F_2TANK_TANK2_1GAS_COMPRESSOR_V_NO7					0x026b//�ɼ����ת�٣����ߴ�
#define		COMMAND_05_0008_F_2TANK_TANK2_1GAS_COMPRESSOR_V_NO8					0x026c//�ɼ����ת�٣��ڰ˴�
#define		COMMAND_05_0009_F_2TANK_TANK2_1GAS_OUT_COMPRESSOR_PRESSURE_NO1		0x026d//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_05_0010_F_2TANK_TANK2_1GAS_TIME_12S_START					0x026e//��ʱ12s��ʱ��ʼ
#define		COMMAND_05_0011_F_2TANK_TANK2_1GAS_IS_TIME_12S						0x026f//�ж϶�ʱ12s
#define		COMMAND_05_0012_F_2TANK_TANK2_1GAS_OUT_COMPRESSOR_PRESSURE_NO2		0x0270//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_05_0013_F_2TANK_TANK2_1GAS_IS_COMPRESSOR_STOP				0x0271//�ж�ȼѹ����ͣ���Ƿ�����


//��ȼѹ������·������---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_BYPATH_VALVE_ON					0x0272//��ȼѹ������·������
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_ON				0x0273//�жϿ�ȼѹ������·������


//��ʱ�ȴ�time_bypath---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_TIME_BYPATH_START				0x0274//��ʱ�ȴ�time_bypath��ʱ����
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_IS_TIME_BYPATH					0x0275//�ж���ʱ�ȴ�time_bypath


//��ȼѹ������·������---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_BYPATH_VALVE_OFF					0x0276//��ȼѹ������·������
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_IS_BYPATH_VALVE_OFF				0x0277//�жϹ�ȼѹ������·������

//�ر�ȼѹ�������ڷ���
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x0278//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1		0x0279//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x027a//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2		0x027b//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_1GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x027c//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK2_1GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3		0x027d//�жϹر�ȼѹ�������ڷ��ţ�������

//�ر�ȼѹ�������ڷ���
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x027e//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1	0x027f//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0280//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2	0x0281//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_1GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x0282//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK2_1GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3	0x0283//�жϹر�ȼѹ�������ڷ��ţ�������


//�ؽ������ѹ��·���ӷ���---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO1			0x0284//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO1			0x0285//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO2			0x0286//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO2			0x0287//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_1GAS_IN_TANK_VALVE_OFF_NO3			0x0288//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK2_1GAS_IS_IN_TANK_VALVE_OFF_NO3			0x0289//�жϹؽ������ѹ��·���ӷ��ţ�������


//����ȼ����״̬��---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_SET_STATE_GOOD					0x028a//����ȼ����״̬��


//�ж�ѹ�����¶��Ƿ�����---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_IS_COMPRESSOR_TEMPERATURE		0x028b//�ж�ѹ�����¶��Ƿ�����

//�ж��Ƿ���Ҫ����Һ��ģ���л�����
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_IS_NEED_EXCHANGE					0x028c//�ж��Ƿ���Ҫ����Һ��ģ���л�����

//��ʱ�ȴ�time_delay3---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_TIME_DELAY3_START				0x028d//��ʱ�ȴ�time_delay3��ʱ��ʼ
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_IS_TIME_DELAY3					0x028e//�ж���ʱ�ȴ�time_delay3


//����Һ��ģ���л�����---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_EXCHANGE_COOLER_VALVE_NO1		0x028f//Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x0290//�ж�Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_1GAS_EXCHANGE_COOLER_VALVE_NO2		0x0291//Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x0292//�ж�Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_1GAS_EXCHANGE_COOLER_VALVE_NO3		0x0293//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_05_0006_F_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x0294//�ж�Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_05_0007_F_2TANK_TANK2_1GAS_EXCHANGE_COOLER_VALVE_NO4		0x0295//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_05_0008_F_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x0296//�ж�Һ��ģ���л�����,���Ŷ�����������


//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����---�ڶ�������
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_IS_EXCHANGE_COOLER				0x0297//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����

//Һ��ģ��ͣ��
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_COOLER_POWER_OFF					0x0298//Һ��ģ��ͣ��

//����ѹ�����ϵ�
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_COMPRESSOR_POWER_OFF				0x0299//�����豸����ָ��
//#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_COMPRESSOR_TIME_1MIN_START		0x029a//��ʱ1min��ʱ��ʼ
//#define		COMMAND_05_0003_F_2TANK_TANK2_1GAS_COMPRESSOR_IS_TIME_1MIN			0x029b//�жϼ�ʱ1min�Ƿ�

//�������������ϵ�
#define		COMMAND_05_0001_F_2TANK_TANK2_1GAS_TGTHT530_POWER_OFF				0x029c//�����豸����ָ��
#define		COMMAND_05_0002_F_2TANK_TANK2_1GAS_TGTHT530_TIME_1MIN_START			0x029d//��ʱ1min��ʱ��ʼ
#define		COMMAND_05_0003_F_2TANK_TANK2_1GAS_TGTHT530_IS_TIME_1MIN			0x029e//�жϼ�ʱ1min�Ƿ�


//------------------------------command---�����������----�ڶ����������----������ƿ����--------------------

//������ƿ���ӷ���---��һ����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_ON				0x029f//������ƿ���ӷ���
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_ON			0x02a0//�жϿ�����ƿ���ӷ���


//��ʱ�ȴ�time_delay2---��һ����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_GAS1_TIME_DELAY2_START			0x02a1//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_GAS1_IS_TIME_DELAY2				0x02a2//�ж���ʱ�ȴ�time_delay2


//�ж���ƿѹ���Ƿ�����---��һ����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO1			0x02a3//�ɼ���ƿѹ������һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO1			0x02a4//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO1				0x02a5//�ж϶�ʱ30s����һ��
#define		COMMAND_05_0004_F_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO2			0x02a6//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO2			0x02a7//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO2				0x02a8//�ж϶�ʱ30s���ڶ���
#define		COMMAND_05_0007_F_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO3			0x02a9//�ɼ���ƿѹ����������
#define		COMMAND_05_0008_F_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO3			0x02aa//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO3				0x02ab//�ж϶�ʱ30s��������
#define		COMMAND_05_0010_F_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO4			0x02ac//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_05_0011_F_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO4			0x02ad//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_05_0012_F_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO4				0x02ae//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_05_0013_F_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO5			0x02af//�ɼ���ƿѹ���������
#define		COMMAND_05_0014_F_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO5			0x02b0//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_05_0015_F_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO5				0x02b1//�ж϶�ʱ30s�������
#define		COMMAND_05_0016_F_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO6			0x02b2//�ɼ���ƿѹ����������
#define		COMMAND_05_0017_F_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO6			0x02b3//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0018_F_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO6				0x02b4//�ж϶�ʱ30s��������
#define		COMMAND_05_0019_F_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO7			0x02b5//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_05_0020_F_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO7			0x02b6//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_05_0021_F_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO7				0x02b7//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_05_0022_F_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO8			0x02b8//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_05_0023_F_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO8			0x02b9//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_05_0024_F_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO8				0x02ba//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_05_0025_F_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO9			0x02bb//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_05_0026_F_2TANK_TANK2_2GAS_GAS1_TIME_30S_START_NO9			0x02bc//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_05_0027_F_2TANK_TANK2_2GAS_GAS1_IS_TIME_30S_NO9				0x02bd//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_05_0028_F_2TANK_TANK2_2GAS_GAS1_GAS_PRESSURE_NO10			0x02be//�ɼ���ƿѹ������ʮ��
#define		COMMAND_05_0029_F_2TANK_TANK2_2GAS_GAS1_IS_GAS_PRESSURE				0x02bf//ѹ���ж���ƿѹ���Ƿ�����


//�ж���ƿ�����Ƿ����---��һ����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_GAS1_IS_COMP_GAS_OVER			0x02c0//�ж���ƿ�����Ƿ����


//��ȼ·��ƿ���ӷ���---��һ����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO1		0x02c1//��ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO1		0x02c2//�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO2		0x02c3//��ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO2		0x02c4//�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_2GAS_GAS1_IN_GAS_VALVE_OFF_NO3		0x02c5//��ȼ·��ƿ���ӷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK2_2GAS_GAS1_IS_IN_GAS_VALVE_OFF_NO3		0x02c6//�жϹ�ȼ·��ƿ���ӷ��ţ�������


//������ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_ON				0x02c7//������ƿ���ӷ���
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_ON			0x02c8//�жϿ�����ƿ���ӷ���

//��ʱ�ȴ�time_delay2---�ڶ�����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_GAS2_TIME_DELAY2_START			0x02c9//��ʱ�ȴ�time_delay2��ʱ��ʼ
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_GAS2_IS_TIME_DELAY2				0x02ca//�ж���ʱ�ȴ�time_delay2


//�ж���ƿѹ���Ƿ�����---�ڶ�����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO1			0x02cb//�ɼ���ƿѹ������һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO1			0x02cc//��ʱ30s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO1				0x02cd//�ж϶�ʱ30s����һ��
#define		COMMAND_05_0004_F_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO2			0x02ce//�ɼ���ƿѹ�����ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO2			0x02cf//��ʱ30s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO2				0x02d0//�ж϶�ʱ30s���ڶ���
#define		COMMAND_05_0007_F_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO3			0x02d1//�ɼ���ƿѹ����������
#define		COMMAND_05_0008_F_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO3			0x02d2//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO3				0x02d3//�ж϶�ʱ30s��������
#define		COMMAND_05_0010_F_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO4			0x02d4//�ɼ���ƿѹ�������Ĵ�
#define		COMMAND_05_0011_F_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO4			0x02d5//��ʱ30s��ʱ��ʼ�����Ĵ�
#define		COMMAND_05_0012_F_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO4				0x02d6//�ж϶�ʱ30s�����Ĵ�
#define		COMMAND_05_0013_F_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO5			0x02d7//�ɼ���ƿѹ���������
#define		COMMAND_05_0014_F_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO5			0x02d8//��ʱ30s��ʱ��ʼ�������
#define		COMMAND_05_0015_F_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO5				0x02d9//�ж϶�ʱ30s�������
#define		COMMAND_05_0016_F_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO6			0x02da//�ɼ���ƿѹ����������
#define		COMMAND_05_0017_F_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO6			0x02db//��ʱ30s��ʱ��ʼ��������
#define		COMMAND_05_0018_F_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO6				0x02dc//�ж϶�ʱ30s��������
#define		COMMAND_05_0019_F_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO7			0x02dd//�ɼ���ƿѹ�������ߴ�
#define		COMMAND_05_0020_F_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO7			0x02de//��ʱ30s��ʱ��ʼ�����ߴ�
#define		COMMAND_05_0021_F_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO7				0x02df//�ж϶�ʱ30s�����ߴ�
#define		COMMAND_05_0022_F_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO8			0x02e0//�ɼ���ƿѹ�����ڰ˴�
#define		COMMAND_05_0023_F_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO8			0x02e1//��ʱ30s��ʱ��ʼ���ڰ˴�
#define		COMMAND_05_0024_F_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO8				0x02e2//�ж϶�ʱ30s���ڰ˴�
#define		COMMAND_05_0025_F_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO9			0x02e3//�ɼ���ƿѹ�����ھŴ�
#define		COMMAND_05_0026_F_2TANK_TANK2_2GAS_GAS2_TIME_30S_START_NO9			0x02e4//��ʱ30s��ʱ��ʼ���ھŴ�
#define		COMMAND_05_0027_F_2TANK_TANK2_2GAS_GAS2_IS_TIME_30S_NO9				0x02e5//�ж϶�ʱ30s���ھŴ�
#define		COMMAND_05_0028_F_2TANK_TANK2_2GAS_GAS2_GAS_PRESSURE_NO10			0x02e6//�ɼ���ƿѹ������ʮ��
#define		COMMAND_05_0029_F_2TANK_TANK2_2GAS_GAS2_IS_GAS_PRESSURE				0x02e7//ѹ���ж���ƿѹ���Ƿ�����


//�ж���ƿ�����Ƿ����---�ڶ�����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_GAS2_IS_COMP_GAS_OVER			0x02e8//�ж���ƿ�����Ƿ����


//��ȼ·��ƿ���ӷ���---�ڶ�����ƿ
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO1		0x02e9//��ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO1		0x02ea//�жϹ�ȼ·��ƿ���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO2		0x02eb//��ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO2		0x02ec//�жϹ�ȼ·��ƿ���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_2GAS_GAS2_IN_GAS_VALVE_OFF_NO3		0x02ed//��ȼ·��ƿ���ӷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK2_2GAS_GAS2_IS_IN_GAS_VALVE_OFF_NO3		0x02ee//�жϹ�ȼ·��ƿ���ӷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������һ��
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO1		0x02ef//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO1			0x02f0//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO1			0x02f1//�ж϶�ʱ12s����һ��
#define		COMMAND_05_0004_F_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO2		0x02f2//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO2			0x02f3//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO2			0x02f4//�ж϶�ʱ12s���ڶ���
#define		COMMAND_05_0007_F_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO3		0x02f5//�ɼ�ѹ��������ѹ����������
#define		COMMAND_05_0008_F_2TANK_TANK2_2GAS_FIRST_TIME_12S_START_NO3			0x02f6//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_2TANK_TANK2_2GAS_FIRST_IS_TIME_12S_NO3			0x02f7//�ж϶�ʱ12s��������
#define		COMMAND_05_0010_F_2TANK_TANK2_2GAS_FIRST_ISOLATION_PRESSURE_NO4		0x02f8//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_05_0011_F_2TANK_TANK2_2GAS_FIRST_IS_ISOLATION				0x02f9//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//�ر�ȼѹ�������ڷ���
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO1		0x02fa//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO1	0x02fb//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO2		0x02fc//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO2	0x02fd//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF_NO3		0x02fe//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF_NO3	0x02ff//�жϹر�ȼѹ�������ڷ��ţ�������

//ͨ��ѹ���жϸ�ѹ��·�����Ƿ���������2��
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO1	0x0300//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO1		0x0301//��ʱ12s��ʱ��ʼ����һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO1			0x0302//�ж϶�ʱ12s����һ��
#define		COMMAND_05_0004_F_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO2	0x0303//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO2		0x0304//��ʱ12s��ʱ��ʼ���ڶ���
#define		COMMAND_05_0006_F_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO2			0x0305//�ж϶�ʱ12s���ڶ���
#define		COMMAND_05_0007_F_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO3	0x0306//�ɼ�ѹ��������ѹ����������
#define		COMMAND_05_0008_F_2TANK_TANK2_2GAS_SECOND_TIME_12S_START_NO3		0x0307//��ʱ12s��ʱ��ʼ��������
#define		COMMAND_05_0009_F_2TANK_TANK2_2GAS_SECOND_IS_TIME_12S_NO3			0x0308//�ж϶�ʱ12s��������
#define		COMMAND_05_0010_F_2TANK_TANK2_2GAS_SECOND_ISOLATION_PRESSURE_NO4	0x0309//�ɼ�ѹ��������ѹ�������Ĵ�
#define		COMMAND_05_0011_F_2TANK_TANK2_2GAS_SECOND_IS_ISOLATION				0x030a//ͨ��ѹ���жϸ�ѹ��·�����Ƿ�����

//ȼѹ����ͣ��
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_COMPRESSOR_STOP					0x030b//�����豸����ָ�ѹ����ͣ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START		0x030c//��ʱ1min��ʱ��ʼ
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN			0x030d//�ж�1min��ʱ


//�ж�ȼѹ����ͣ���Ƿ�����
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_COMPRESSOR_V_NO1					0x030e//�ɼ����ת�٣���һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_COMPRESSOR_V_NO2					0x030f//�ɼ����ת�٣��ڶ���
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_COMPRESSOR_V_NO3					0x0310//�ɼ����ת�٣�������
#define		COMMAND_05_0004_F_2TANK_TANK2_2GAS_COMPRESSOR_V_NO4					0x0311//�ɼ����ת�٣����Ĵ�
#define		COMMAND_05_0005_F_2TANK_TANK2_2GAS_COMPRESSOR_V_NO5					0x0312//�ɼ����ת�٣������
#define		COMMAND_05_0006_F_2TANK_TANK2_2GAS_COMPRESSOR_V_NO6					0x0313//�ɼ����ת�٣�������
#define		COMMAND_05_0007_F_2TANK_TANK2_2GAS_COMPRESSOR_V_NO7					0x0314//�ɼ����ת�٣����ߴ�
#define		COMMAND_05_0008_F_2TANK_TANK2_2GAS_COMPRESSOR_V_NO8					0x0315//�ɼ����ת�٣��ڰ˴�
#define		COMMAND_05_0009_F_2TANK_TANK2_2GAS_OUT_COMPRESSOR_PRESSURE_NO1		0x0316//�ɼ�ѹ��������ѹ������һ��
#define		COMMAND_05_0010_F_2TANK_TANK2_2GAS_TIME_12S_START					0x0317//��ʱ12s��ʱ��ʼ
#define		COMMAND_05_0011_F_2TANK_TANK2_2GAS_IS_TIME_12S						0x0318//�ж϶�ʱ12s
#define		COMMAND_05_0012_F_2TANK_TANK2_2GAS_OUT_COMPRESSOR_PRESSURE_NO2		0x0319//�ɼ�ѹ��������ѹ�����ڶ���
#define		COMMAND_05_0013_F_2TANK_TANK2_2GAS_IS_COMPRESSOR_STOP				0x031a//�ж�ȼѹ����ͣ���Ƿ�����


//��ȼѹ������·������
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_BYPATH_VALVE_ON					0x031b//��ȼѹ������·������
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_ON				0x031c//�жϿ�ȼѹ������·������


//��ʱ�ȴ�time_bypath
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_TIME_BYPATH_START				0x031d//��ʱ�ȴ�time_bypath��ʱ����
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_IS_TIME_BYPATH					0x031e//�ж���ʱ�ȴ�time_bypath


//��ȼѹ������·������
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_BYPATH_VALVE_OFF					0x031f//��ȼѹ������·������
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_IS_BYPATH_VALVE_OFF				0x0320//�жϹ�ȼѹ������·������

//�ر�ȼѹ�������ڷ���
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO1	0x0321//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO1	0x0322//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO2	0x0323//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO2	0x0324//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_2GAS_OUT_COMPRESSOR_VALVE_OFF2_NO3	0x0325//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK2_2GAS_IS_OUT_COMPRESSOR_VALVE_OFF2_NO3	0x0326//�жϹر�ȼѹ�������ڷ��ţ�������


//�ر�ȼѹ�������ڷ���
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO1		0x0327//�ر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO1	0x0328//�жϹر�ȼѹ�������ڷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO2		0x0329//�ر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO2	0x032a//�жϹر�ȼѹ�������ڷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_2GAS_IN_COMPRESSOR_VALVE_OFF_NO3		0x032b//�ر�ȼѹ�������ڷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK2_2GAS_IS_IN_COMPRESSOR_VALVE_OFF_NO3	0x032c//�жϹر�ȼѹ�������ڷ��ţ�������


//�ؽ������ѹ��·���ӷ���
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO1			0x032d//�ؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO1			0x032e//�жϹؽ������ѹ��·���ӷ��ţ���һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO2			0x032f//�ؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO2			0x0330//�жϹؽ������ѹ��·���ӷ��ţ��ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_2GAS_IN_TANK_VALVE_OFF_NO3			0x0331//�ؽ������ѹ��·���ӷ��ţ�������
#define		COMMAND_05_0006_F_2TANK_TANK2_2GAS_IS_IN_TANK_VALVE_OFF_NO3			0x0332//�жϹؽ������ѹ��·���ӷ��ţ�������


//����ȼ����״̬��
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_SET_STATE_GOOD					0x0333//����ȼ����״̬��


//�ж�ѹ�����¶��Ƿ�����
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_IS_COMPRESSOR_TEMPERATURE		0x0334//�ж�ѹ�����¶��Ƿ�����

//�ж��Ƿ���Ҫ����Һ��ģ���л�����
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_IS_NEED_EXCHANGE					0x0335//�ж��Ƿ���Ҫ����Һ��ģ���л�����

//��ʱ�ȴ�time_delay3
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_TIME_DELAY3_START				0x0336//��ʱ�ȴ�time_delay3��ʱ��ʼ
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_IS_TIME_DELAY3					0x0337//�ж���ʱ�ȴ�time_delay3

//����Һ��ģ���л�����
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_EXCHANGE_COOLER_VALVE_NO1		0x0338//Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER_VALVE_NO1		0x0339//�ж�Һ��ģ���л�����,���Ŷ�������һ��
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_EXCHANGE_COOLER_VALVE_NO2		0x033a//Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_05_0004_F_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER_VALVE_NO2		0x033b//�ж�Һ��ģ���л�����,���Ŷ������ڶ���
#define		COMMAND_05_0005_F_2TANK_TANK2_2GAS_EXCHANGE_COOLER_VALVE_NO3		0x033c//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_05_0006_F_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER_VALVE_NO3		0x033d//�ж�Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_05_0007_F_2TANK_TANK2_2GAS_EXCHANGE_COOLER_VALVE_NO4		0x033e//Һ��ģ���л�����,���Ŷ�����������
#define		COMMAND_05_0008_F_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER_VALVE_NO4		0x033f//�ж�Һ��ģ���л�����,���Ŷ�����������

//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_IS_EXCHANGE_COOLER				0x0340//ͨ��ѹ���ж�Һ��ģ���л��Ƿ�����

//Һ��ģ��ͣ��
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_COOLER_POWER_OFF					0x0341//Һ��ģ��ͣ��

//����ѹ�����ϵ�
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_COMPRESSOR_POWER_OFF				0x0342//�����豸����ָ��
//#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_COMPRESSOR_TIME_1MIN_START		0x0343//��ʱ1min��ʱ��ʼ
//#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_COMPRESSOR_IS_TIME_1MIN			0x0344//�жϼ�ʱ1min�Ƿ�

//�������������ϵ�
#define		COMMAND_05_0001_F_2TANK_TANK2_2GAS_TGTHT530_POWER_OFF				0x0345//�����豸����ָ��
#define		COMMAND_05_0002_F_2TANK_TANK2_2GAS_TGTHT530_TIME_1MIN_START			0x0346//��ʱ1min��ʱ��ʼ
#define		COMMAND_05_0003_F_2TANK_TANK2_2GAS_TGTHT530_IS_TIME_1MIN			0x0347//�жϼ�ʱ1min�Ƿ�

//------------------------��������---------------------------------------------------------

void TGTHT510_supply_stage05_comp_F_main(void);

//-------------------------------------------------��ʼ���ý׶�----------------------------------------------------

uint16 TGTHT510_supply_stage05_comp_F_init_step_start_cooler(void);
uint16 TGTHT510_supply_stage05_comp_F_init_step_is_cooler_work(void);
uint16 TGTHT510_supply_stage05_comp_F_init_step_time_delay(void);
uint16 TGTHT510_supply_stage05_comp_F_init_step_is_compressor_temperature(void);
uint16 TGTHT510_supply_stage05_comp_F_init_step_TGTHT530_power_on(void);
uint16 TGTHT510_supply_stage05_comp_F_init_step_compressor_power_on(void);
uint16 TGTHT510_supply_stage05_comp_F_init_step_isolation(void);
uint16 TGTHT510_supply_stage05_comp_F_init_step_number_comp_tank(void);

//-------------------------------------------------һ���������----------------------------------------------------
uint16 TGTHT510_supply_stage05_comp_F_1tank_step_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_step_is_in_tank_valve_on_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_step_in_compressor_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_step_time_delay1(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_step_is_in_compressor_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_step_compressor_start(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_step_is_out_compressor_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_step_out_compressor_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_step_number_comp_gas(void);

//-----------------------------------һ�����������һ����ƿ����----------------------------------------------------
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_time_delay2(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_is_comp_over(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_is_compressor_temperature(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_is_need_exchange(void);


uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_time_delay3(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_exchange_cooler(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_is_exchange_cooler(void);

uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_1gas_step_TGTHT530_power_off(void);


//-----------------------------------һ�����������������ƿ����----------------------------------------------------
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_gas1_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_gas1_step_time_delay2(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_gas1_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_gas1_step_is_comp_over(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_gas1_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_gas2_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_gas2_step_time_delay2(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_gas2_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_gas2_step_is_comp_over(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_gas2_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_is_compressor_temperature(void);

uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_is_need_exchange(void);

uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_time_delay3(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_exchange_cooler(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_is_exchange_cooler(void);

uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage05_comp_F_1tank_2gas_step_TGTHT530_power_off(void);


//---------------------------------���������������һ���������----------------------------------------------------
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_step_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_step_is_in_tank_valve_on_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_step_in_compressor_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_step_time_delay1(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_step_is_in_compressor_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_step_compressor_start(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_step_is_out_compressor_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_step_out_compressor_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_step_number_comp_gas(void);

//---------------------------------���������������һ�����������һ����ƿ����--------------------------------------
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_1gas_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_1gas_step_time_delay2(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_1gas_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_1gas_step_is_comp_over(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_1gas_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_1gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_1gas_step_is_in_tank_valve_pressure(void);

//---------------------------------���������������һ�����������������ƿ����--------------------------------------
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_2gas_gas1_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_2gas_gas1_step_time_delay2(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_2gas_gas1_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_2gas_gas1_step_is_comp_over(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_2gas_gas1_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_2gas_gas2_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_2gas_gas2_step_time_delay2(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_2gas_gas2_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_2gas_gas2_step_is_comp_over(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_2gas_gas2_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_2gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank1_2gas_step_is_in_tank_valve_pressure(void);

//---------------------------------��������������ڶ����������----------------------------------------------------
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_step_in_tank_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_step_is_in_tank_valve_on_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_step_number_comp_gas(void);

//---------------------------------��������������ڶ������������һ����ƿ����--------------------------------------
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_time_delay2(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_is_comp_over(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_is_compressor_temperature(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_is_need_exchange(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_time_delay3(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_exchange_cooler(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_is_exchange_cooler(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_1gas_step_TGTHT530_power_off(void);


//---------------------------------��������������ڶ������������������ƿ����--------------------------------------
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_gas1_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_gas1_step_time_delay2(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_gas1_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_gas1_step_is_comp_over(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_gas1_step_in_gas_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_gas2_step_in_gas_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_gas2_step_time_delay2(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_gas2_step_is_gas_pressure(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_gas2_step_is_comp_over(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_gas2_step_in_gas_valve_off(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_is_isolation_first(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_out_compressor_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_is_isolation_second(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_compressor_stop(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_is_compressor_stop(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_bypath_valve_on(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_time_delay_bypath(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_bypath_valve_off(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_out_compressor_valve_off2(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_in_compressor_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_in_tank_valve_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_set_state_good(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_is_compressor_temperature(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_is_need_exchange(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_time_delay3(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_exchange_cooler(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_is_exchange_cooler(void);

uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_cooler_stop(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_compressor_power_off(void);
uint16 TGTHT510_supply_stage05_comp_F_2tank_tank2_2gas_step_TGTHT530_power_off(void);


//---------------------------------------------------------ͨ�ú���------------------------------------------------


void TGTHT510_supply_command_cooler_valve_on(uint16 n);
uint16 TGTHT510_supply_command_is_cooler_valve_on(uint16 n);
void TGTHT510_supply_command_cooler_power_on(void);
void TGTHT510_supply_command_cooler_power_off(void);


uint16 TGTHT510_supply_common_average(uint16 *p,uint16 n);
uint16 TGTHT510_supply_common_cooler_work(uint16 val);
uint16 TGTHT510_supply_common_is_cooler_to_compressor(uint16 comp_kind);
uint16 TGTHT510_supply_common_is_compressor_temperature(uint16 comp_kind);
uint16 TGTHT510_supply_common_is_in_tank_valve_on_pressure(uint16 tank);
uint16 TGTHT510_supply_common_is_in_compressor_pressure(uint16 comp_kind);
uint16 TGTHT510_supply_common_is_out_compressor_pressure(uint16 comp_kind);
void TGTHT510_supply_common_out_compressor_valve_on(uint16 comp_kind);
uint16 TGTHT510_supply_common_is_out_compressor_valve_on(uint16 comp_kind);
uint16 TGTHT510_supply_common_number_gas(uint16 comp_kind,uint16 tank_no);
void TGTHT510_supply_common_in_gas_valve_on(uint16 comp_kind,uint16 tank_no,uint16 gas_no);
uint16 TGTHT510_supply_common_is_in_gas_valve_on(uint16 comp_kind,uint16 tank_no,uint16 gas_no);
uint16 TGTHT510_supply_common_gas_pressure_get(uint16 comp_kind,uint16 tank_no,uint16 gas_no);
uint16 TGTHT510_supply_common_is_gas_pressure(uint16 *p);
uint16 TGTHT510_supply_common_is_gas_comp_over(uint16 comp_kind,uint16 tank_no,uint16 gas_no);
void TGTHT510_supply_common_tank_pressure_get(uint16 comp_kind,uint16 tank_no,uint16 gas_no,uint16 *val);
uint16 TGTHT510_supply_common_out_compressor_pressure_get(uint16 comp_kind);
uint16 TGTHT510_supply_common_is_isolation(uint16 *p);
void TGTHT510_supply_common_exchange_cooler(uint16 n);
uint16 TGTHT510_supply_common_is_exchange_cooler(uint16 n);
uint16 TGTHT510_supply_common_is_exchange_cooler_pressure(void);

void TGTHT510_supply_command_isolation_valve_off(uint16 n,uint16 isolation_tank);
uint16 TGTHT510_supply_command_is_isolation_valve_off(uint16 n,uint16 isolation_tank);


#endif
 
 
 
