/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ���������������������ͷ�ļ�
  ******************************************************************************
  */
 
#ifndef __supply_stage_04_leak_h
#define __supply_stage_04_leak_h
 

/*�����ṹ������--------------------------------------------------------------*/



/*�궨��---------------------------------------------------------------------------*/

//����step----------------------------------------------------------------------

#define 	STEP_04_SUPPLY_VALVE_ON_CONNECT				0x0001//���������Ͻ������ӷ���
#define 	STEP_04_SUPPLY_LEAK_INPUT_COMMAND			0x0002//��©��������ָ��ע��

//����command-------------------------------------------------------------------

//���������Ͻ������ӷ���

#define		COMMAND_04_0001_VALVE_ON_CONNECT_NO1		0x0001//���������Ͻ������ӷ��ŵ�һ��
#define		COMMAND_04_0002_IS_VALVE_ON_CONNECT_NO1		0x0002//�жϿ��������Ͻ������ӷ��ŵ�һ��
#define		COMMAND_04_0003_VALVE_ON_CONNECT_NO2		0x0003//���������Ͻ������ӷ��ŵڶ���
#define		COMMAND_04_0004_IS_VALVE_ON_CONNECT_NO2		0x0004//�жϿ��������Ͻ������ӷ��ŵڶ���

//��©����ָ��
#define 	COMMAND_04_0005_LEAK_VALVE_NO1				0x0005//����©����ָ��
#define 	COMMAND_04_0006_LEAK_IS_VALVE_NO1			0x0006//�жϿ���©����ָ��
#define 	COMMAND_04_0007_LEAK_VALVE_NO2				0x0007//����©����ָ��
#define 	COMMAND_04_0008_LEAK_IS_VALVE_NO2			0x0008//�жϿ���©����ָ��
#define 	COMMAND_04_0009_LEAK_VALVE_NO3				0x0009//����©����ָ��
#define 	COMMAND_04_0010_LEAK_IS_VALVE_NO3			0x000a//�жϿ���©����ָ��
#define 	COMMAND_04_0011_LEAK_VALVE_NO4				0x000b//����©����ָ��
#define 	COMMAND_04_0012_LEAK_IS_VALVE_NO4			0x000c//�жϿ���©����ָ��
#define 	COMMAND_04_0013_LEAK_VALVE_NO5				0x000d//����©����ָ��
#define 	COMMAND_04_0014_LEAK_IS_VALVE_NO5			0x000e//�жϿ���©����ָ��
#define 	COMMAND_04_0015_LEAK_VALVE_NO6				0x000f//����©����ָ��
#define 	COMMAND_04_0016_LEAK_IS_VALVE_NO6			0x0010//�жϿ���©����ָ��
#define 	COMMAND_04_0017_LEAK_VALVE_NO7				0x0011//����©����ָ��
#define 	COMMAND_04_0018_LEAK_IS_VALVE_NO7			0x0012//�жϿ���©����ָ��
#define 	COMMAND_04_0019_LEAK_VALVE_NO8				0x0013//����©����ָ��
#define 	COMMAND_04_0020_LEAK_IS_VALVE_NO8			0x0014//�жϿ���©����ָ��
#define 	COMMAND_04_0021_LEAK_VALVE_NO9				0x0015//����©����ָ��
#define 	COMMAND_04_0022_LEAK_IS_VALVE_NO9			0x0016//�жϿ���©����ָ��
#define 	COMMAND_04_0023_LEAK_VALVE_NO10				0x0017//����©����ָ��
#define 	COMMAND_04_0024_LEAK_IS_VALVE_NO10			0x0018//�жϿ���©����ָ��
#define 	COMMAND_04_0025_LEAK_VALVE_NO11				0x0019//����©����ָ��
#define 	COMMAND_04_0026_LEAK_IS_VALVE_NO11			0x001a//�жϿ���©����ָ��
#define 	COMMAND_04_0027_LEAK_VALVE_NO12				0x001b//����©����ָ��
#define 	COMMAND_04_0028_LEAK_IS_VALVE_NO12			0x001c//�жϿ���©����ָ��

#define		COMMAND_04_0029_LEAK_TIME_START				0x001d//��ʼ�ȴ���©����ʱ��
#define		COMMAND_04_0030_LEAK_IS_TIME				0x001e//�жϼ�©����ʱ���Ƿ�

#define 	COMMAND_04_0031_LEAK_VALVE_NO13				0x001f//�ؼ�©����ָ��
#define 	COMMAND_04_0032_LEAK_IS_VALVE_NO13			0x0020//�жϹؼ�©����ָ��
#define 	COMMAND_04_0033_LEAK_VALVE_NO14				0x0021//�ؼ�©����ָ��
#define 	COMMAND_04_0034_LEAK_IS_VALVE_NO14			0x0022//�жϹؼ�©����ָ��
#define 	COMMAND_04_0035_LEAK_VALVE_NO15				0x0023//�ؼ�©����ָ��
#define 	COMMAND_04_0036_LEAK_IS_VALVE_NO15			0x0024//�жϹؼ�©����ָ��
#define 	COMMAND_04_0037_LEAK_VALVE_NO16				0x0025//�ؼ�©����ָ��
#define 	COMMAND_04_0038_LEAK_IS_VALVE_NO16			0x0026//�жϹؼ�©����ָ��
#define 	COMMAND_04_0039_LEAK_VALVE_NO17				0x0027//�ؼ�©����ָ��
#define 	COMMAND_04_0040_LEAK_IS_VALVE_NO17			0x0028//�жϹؼ�©����ָ��
#define 	COMMAND_04_0041_LEAK_VALVE_NO18				0x0029//�ؼ�©����ָ��
#define 	COMMAND_04_0042_LEAK_IS_VALVE_NO18			0x002a//�жϹؼ�©����ָ��
#define 	COMMAND_04_0043_LEAK_VALVE_NO19				0x002b//�ؼ�©����ָ��
#define 	COMMAND_04_0044_LEAK_IS_VALVE_NO19			0x002c//�жϹؼ�©����ָ��
#define 	COMMAND_04_0045_LEAK_VALVE_NO20				0x002d//�ؼ�©����ָ��
#define 	COMMAND_04_0046_LEAK_IS_VALVE_NO20			0x002e//�жϹؼ�©����ָ��
#define 	COMMAND_04_0047_LEAK_VALVE_NO21				0x002f//�ؼ�©����ָ��
#define 	COMMAND_04_0048_LEAK_IS_VALVE_NO21			0x0030//�жϹؼ�©����ָ��
#define 	COMMAND_04_0049_LEAK_VALVE_NO22				0x0031//�ؼ�©����ָ��
#define 	COMMAND_04_0050_LEAK_IS_VALVE_NO22			0x0032//�жϹؼ�©����ָ��
#define 	COMMAND_04_0051_LEAK_VALVE_NO23				0x0033//�ؼ�©����ָ��
#define 	COMMAND_04_0052_LEAK_IS_VALVE_NO23			0x0034//�жϹؼ�©����ָ��
#define 	COMMAND_04_0053_LEAK_VALVE_NO24				0x0035//�ؼ�©����ָ��
#define 	COMMAND_04_0054_LEAK_IS_VALVE_NO24			0x0036//�жϹؼ�©����ָ��

#define 	COMMAND_04_0055_LEAK_VALVE_NO25				0x0037//�ؽ������Ͻ�������
#define 	COMMAND_04_0056_LEAK_IS_VALVE_NO25			0x0038//�жϹؽ������Ͻ�������
#define 	COMMAND_04_0057_LEAK_VALVE_NO26				0x0039//�ؽ������Ͻ�������
#define 	COMMAND_04_0058_LEAK_IS_VALVE_NO26			0x003a//�жϹؽ������Ͻ�������
#define 	COMMAND_04_0059_LEAK_VALVE_NO27				0x003b//�ؽ������Ͻ�������
#define 	COMMAND_04_0060_LEAK_IS_VALVE_NO27			0x003c//�жϹؽ������Ͻ�������
#define 	COMMAND_04_0061_LEAK_VALVE_NO28				0x003d//�ؽ������Ͻ�������
#define 	COMMAND_04_0062_LEAK_IS_VALVE_NO28			0x003e//�жϹؽ������Ͻ�������
#define 	COMMAND_04_0063_LEAK_VALVE_NO29				0x003f//�ؽ������Ͻ�������
#define 	COMMAND_04_0064_LEAK_IS_VALVE_NO29			0x0040//�жϹؽ������Ͻ�������
#define 	COMMAND_04_0065_LEAK_VALVE_NO30				0x0041//�ؽ������Ͻ�������
#define 	COMMAND_04_0066_LEAK_IS_VALVE_NO30			0x0042//�жϹؽ������Ͻ�������
#define 	COMMAND_04_0067_LEAK_VALVE_NO31				0x0043//�ؽ������Ͻ�������
#define 	COMMAND_04_0068_LEAK_IS_VALVE_NO31			0x0044//�жϹؽ������Ͻ�������
#define 	COMMAND_04_0069_LEAK_VALVE_NO32				0x0045//�ؽ������Ͻ�������
#define 	COMMAND_04_0070_LEAK_IS_VALVE_NO32			0x0046//�жϹؽ������Ͻ�������



//-------------------------��������------------------------------------------------

void TGTHT510_supply_stage04_leak_main(void);
void TGTHT510_supply_stage04_leak_valve_on_connect(void);
void TGTHT510_supply_stage04_leak_command_valve_on_connect(uint16 n);
uint16 TGTHT510_supply_stage04_leak_command_is_valve_on_connect(uint16 n);

void TGTHT510_supply_stage04_leak_valve_on_gas(void);
void TGTHT510_supply_stage04_leak_command_valve_on_gas(uint16 n);
uint16 TGTHT510_supply_stage04_leak_command_is_valve_on_gas(uint16 n);





#endif
 
 
 
 
 

 
 
