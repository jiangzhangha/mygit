/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ���������������������ͷ�ļ�
  ******************************************************************************
  */
 
#ifndef __supply_stage_22_resume_h
#define __supply_stage_22_resume_h
 

/*�����ṹ������--------------------------------------------------------------*/



/*�궨��---------------------------------------------------------------------------*/

//����step----------------------------------------------------------------------

#define 	STEP_24_SUPPLY_DETECTION_DISABLE			0x0001//���ӹ��ϼ���ֹ
#define		STEP_24_SUPPLY_TEMPER_CTRL_DISABLE			0x0002//�����Զ����½�ֹ
#define		STEP_24_SUPPLY_VALVE_ALL_OFF				0x0003//����ϵͳ�������ر�
#define		STEP_24_SUPPLY_VALVE_POWER_OFF				0x0004//����ϵͳ�������ϵ�
#define		STEP_24_SUPPLY_IS_VALVE_POWER_OFF			0x0005//�жϲ���ϵͳ�������ϵ�

//����command-------------------------------------------------------------------

//���ӹ��ϼ��ʹ��
#define		COMMAND_24_0001_DETECTION_DISABLE			0x0001

//�����Զ�����ʹ��
#define		COMMAND_24_0001_TEMPER_CTRL_DISABLE			0x0002

//����ϵͳ�������ر�
#define		COMMAND_24_0001_LVB01_OFF					0x0003//����������LVb1��
#define		COMMAND_24_0002_LVB02_OFF					0x0004//����������LVb2��
#define		COMMAND_24_0003_LVB03_OFF					0x0005//����������LVb3��
#define		COMMAND_24_0004_LVB04_OFF					0x0006//����������LVb4��
#define		COMMAND_24_0005_LVB05_OFF					0x0007//����������LVb5��
#define		COMMAND_24_0006_LVB06_OFF					0x0008//����������LVb6��
#define		COMMAND_24_0007_LVB07_OFF					0x0009//����������LVb7��
#define		COMMAND_24_0008_LVB08_OFF					0x000a//����������LVb8��
#define		COMMAND_24_0009_LVB09_OFF					0x000b//����������LVb9��
#define		COMMAND_24_0010_LVB10_OFF					0x000c//����������LVb10��
#define		COMMAND_24_0011_LVB11_OFF					0x000d//����������LVb11��
#define		COMMAND_24_0012_LVB12_OFF					0x000e//����������LVb12��
#define		COMMAND_24_0013_LVB13_OFF					0x000f//����������LVb13��
#define		COMMAND_24_0014_LVB14_OFF					0x0010//����������LVb14��
#define		COMMAND_24_0015_LVB15_OFF					0x0011//����������LVb15��
#define		COMMAND_24_0016_LVB16_OFF					0x0012//����������LVb16��
#define		COMMAND_24_0017_LVB17_OFF					0x0013//����������LVb17��
#define		COMMAND_24_0018_LVB18_OFF					0x0014//����������LVb18��
#define		COMMAND_24_0019_LVB19_OFF					0x0015//����������LVb19��
#define		COMMAND_24_0020_LVB20_OFF					0x0016//����������LVb20��
#define		COMMAND_24_0021_LVB21_OFF					0x0017//����������LVb21��
#define		COMMAND_24_0022_LVB22_OFF					0x0018//����������LVb22��
#define		COMMAND_24_0023_LVB23_OFF					0x0019//����������LVb23��
#define		COMMAND_24_0024_LVB24_OFF					0x001a//����������LVb24��
#define		COMMAND_24_0025_LVB25_OFF					0x001b//����������LVb25��
#define		COMMAND_24_0026_LVB26_OFF					0x001c//����������LVb26��
#define		COMMAND_24_0027_LVB39_OFF					0x001d//����������LVb39��
#define		COMMAND_24_0028_LVB40_OFF					0x001e//����������LVb40��
#define		COMMAND_24_0029_LVB41_OFF					0x001f//����������LVb41��
#define		COMMAND_24_0030_LVB42_OFF					0x0020//����������LVb42��
#define		COMMAND_24_0031_LVB43_OFF					0x0021//����������LVb43��
#define		COMMAND_24_0032_LVB44_OFF					0x0022//����������LVb44��
#define		COMMAND_24_0033_LVB45_OFF					0x0023//����������LVb45��
#define		COMMAND_24_0034_LVB46_OFF					0x0024//����������LVb46��
#define		COMMAND_24_0035_LVB47_OFF					0x0025//����������LVb47��
#define		COMMAND_24_0036_LVB48_OFF					0x0026//����������LVb48��
#define		COMMAND_24_0037_LVB49_OFF					0x0027//����������LVb49��
#define		COMMAND_24_0038_LVB50_OFF					0x0028//����������LVb50��
#define		COMMAND_24_0039_LVB51_OFF					0x0029//����������LVb51��
#define		COMMAND_24_0040_LVB52_OFF					0x002a//����������LVb52��
#define		COMMAND_24_0041_LVB53_OFF					0x002b//����������LVb53��
#define		COMMAND_24_0042_LVB54_OFF					0x002c//����������LVb54��
#define		COMMAND_24_0043_LVB55_OFF					0x002d//����������LVb55��
#define		COMMAND_24_0044_LVB56_OFF					0x002e//����������LVb56��
#define		COMMAND_24_0045_LVB57_OFF					0x002f//����������LVb57��
#define		COMMAND_24_0046_LVB58_OFF					0x0030//����������LVb58��
#define		COMMAND_24_0047_LVB59_OFF					0x0031//����������LVb59��
#define		COMMAND_24_0048_LVB60_OFF					0x0032//����������LVb60��
#define		COMMAND_24_0049_LVB61_OFF					0x0033//����������LVb61��
#define		COMMAND_24_0050_LVB62_OFF					0x0034//����������LVb62��
#define		COMMAND_24_0051_LVB63_OFF					0x0035//����������LVb63��
#define		COMMAND_24_0052_LVB64_OFF					0x0036//����������LVb64��
#define		COMMAND_24_0053_LVB65_OFF					0x0037//����������LVb65��
#define		COMMAND_24_0054_LVB66_OFF					0x0038//����������LVb66��
#define		COMMAND_24_0055_LVB67_OFF					0x0039//����������LVb67��
#define		COMMAND_24_0056_LVB68_OFF					0x003a//����������LVb68��
#define		COMMAND_24_0057_LVB69_OFF					0x003b//����������LVb69��
#define		COMMAND_24_0058_LVB70_OFF					0x003c//����������LVb70��
#define		COMMAND_24_0059_LVB71_OFF					0x003d//����������LVb71��
#define		COMMAND_24_0060_LVB72_OFF					0x003e//����������LVb72��
#define		COMMAND_24_0061_LVB73_OFF					0x003f//����������LVb73��
#define		COMMAND_24_0062_LVB74_OFF					0x0040//����������LVb74��
#define		COMMAND_24_0063_LVB75_OFF					0x0041//����������LVb75��
#define		COMMAND_24_0064_LVB76_OFF					0x0042//����������LVb76��
#define		COMMAND_24_0065_LVB77_OFF					0x0043//����������LVb77��
#define		COMMAND_24_0066_LVB78_OFF					0x0044//����������LVb78��
#define		COMMAND_24_0067_LVB79_OFF					0x0045//����������LVb79��
#define		COMMAND_24_0068_LVB80_OFF					0x0046//����������LVb80��
#define		COMMAND_24_0069_LVB81_OFF					0x0047//����������LVb81��
#define		COMMAND_24_0070_LVB82_OFF					0x0048//����������LVb82��
#define		COMMAND_24_0071_LVB83_OFF					0x0049//����������LVb83��
#define		COMMAND_24_0072_LVB84_OFF					0x004a//����������LVb84��
#define		COMMAND_24_0073_LVB85_OFF					0x004b//����������LVb85��
#define		COMMAND_24_0074_LVB86_OFF					0x004c//����������LVb86��
#define		COMMAND_24_0075_LVB87_OFF					0x004d//����������LVb87��


//�жϲ���ϵͳ�������ر�
#define		COMMAND_24_0001_IS_LVB01_OFF				0x004e//�жϲ���������LVb1��
#define		COMMAND_24_0002_IS_LVB02_OFF				0x004f//�жϲ���������LVb2��
#define		COMMAND_24_0003_IS_LVB03_OFF				0x0050//�жϲ���������LVb3��
#define		COMMAND_24_0004_IS_LVB04_OFF				0x0051//�жϲ���������LVb4��
#define		COMMAND_24_0005_IS_LVB05_OFF				0x0052//�жϲ���������LVb5��
#define		COMMAND_24_0006_IS_LVB06_OFF				0x0053//�жϲ���������LVb6��
#define		COMMAND_24_0007_IS_LVB07_OFF				0x0054//�жϲ���������LVb7��
#define		COMMAND_24_0008_IS_LVB08_OFF				0x0055//�жϲ���������LVb8��
#define		COMMAND_24_0009_IS_LVB09_OFF				0x0056//�жϲ���������LVb9��
#define		COMMAND_24_0010_IS_LVB10_OFF				0x0057//�жϲ���������LVb10��
#define		COMMAND_24_0011_IS_LVB11_OFF				0x0058//�жϲ���������LVb11��
#define		COMMAND_24_0012_IS_LVB12_OFF				0x0059//�жϲ���������LVb12��
#define		COMMAND_24_0013_IS_LVB13_OFF				0x005a//�жϲ���������LVb13��
#define		COMMAND_24_0014_IS_LVB14_OFF				0x005b//�жϲ���������LVb14��
#define		COMMAND_24_0015_IS_LVB15_OFF				0x005c//�жϲ���������LVb15��
#define		COMMAND_24_0016_IS_LVB16_OFF				0x005d//�жϲ���������LVb16��
#define		COMMAND_24_0017_IS_LVB17_OFF				0x005e//�жϲ���������LVb17��
#define		COMMAND_24_0018_IS_LVB18_OFF				0x005f//�жϲ���������LVb18��
#define		COMMAND_24_0019_IS_LVB19_OFF				0x0060//�жϲ���������LVb19��
#define		COMMAND_24_0020_IS_LVB20_OFF				0x0061//�жϲ���������LVb20��
#define		COMMAND_24_0021_IS_LVB21_OFF				0x0062//�жϲ���������LVb21��
#define		COMMAND_24_0022_IS_LVB22_OFF				0x0063//�жϲ���������LVb22��
#define		COMMAND_24_0023_IS_LVB23_OFF				0x0064//�жϲ���������LVb23��
#define		COMMAND_24_0024_IS_LVB24_OFF				0x0065//�жϲ���������LVb24��
#define		COMMAND_24_0025_IS_LVB25_OFF				0x0066//�жϲ���������LVb25��
#define		COMMAND_24_0026_IS_LVB26_OFF				0x0067//�жϲ���������LVb26��
#define		COMMAND_24_0027_IS_LVB39_OFF				0x0068//�жϲ���������LVb39��
#define		COMMAND_24_0028_IS_LVB40_OFF				0x0069//�жϲ���������LVb40��
#define		COMMAND_24_0029_IS_LVB41_OFF				0x006a//�жϲ���������LVb41��
#define		COMMAND_24_0030_IS_LVB42_OFF				0x006b//�жϲ���������LVb42��
#define		COMMAND_24_0031_IS_LVB43_OFF				0x006c//�жϲ���������LVb43��
#define		COMMAND_24_0032_IS_LVB44_OFF				0x006d//�жϲ���������LVb44��
#define		COMMAND_24_0033_IS_LVB45_OFF				0x006e//�жϲ���������LVb45��
#define		COMMAND_24_0034_IS_LVB46_OFF				0x006f//�жϲ���������LVb46��
#define		COMMAND_24_0035_IS_LVB47_OFF				0x0070//�жϲ���������LVb47��
#define		COMMAND_24_0036_IS_LVB48_OFF				0x0071//�жϲ���������LVb48��
#define		COMMAND_24_0037_IS_LVB49_OFF				0x0072//�жϲ���������LVb49��
#define		COMMAND_24_0038_IS_LVB50_OFF				0x0073//�жϲ���������LVb50��
#define		COMMAND_24_0039_IS_LVB51_OFF				0x0074//�жϲ���������LVb51��
#define		COMMAND_24_0040_IS_LVB52_OFF				0x0075//�жϲ���������LVb52��
#define		COMMAND_24_0041_IS_LVB53_OFF				0x0076//�жϲ���������LVb53��
#define		COMMAND_24_0042_IS_LVB54_OFF				0x0077//�жϲ���������LVb54��
#define		COMMAND_24_0043_IS_LVB55_OFF				0x0078//�жϲ���������LVb55��
#define		COMMAND_24_0044_IS_LVB56_OFF				0x0079//�жϲ���������LVb56��
#define		COMMAND_24_0045_IS_LVB57_OFF				0x007a//�жϲ���������LVb57��
#define		COMMAND_24_0046_IS_LVB58_OFF				0x007b//�жϲ���������LVb58��
#define		COMMAND_24_0047_IS_LVB59_OFF				0x007c//�жϲ���������LVb59��
#define		COMMAND_24_0048_IS_LVB60_OFF				0x007d//�жϲ���������LVb60��
#define		COMMAND_24_0049_IS_LVB61_OFF				0x007e//�жϲ���������LVb61��
#define		COMMAND_24_0050_IS_LVB62_OFF				0x007f//�жϲ���������LVb62��
#define		COMMAND_24_0051_IS_LVB63_OFF				0x0080//�жϲ���������LVb63��
#define		COMMAND_24_0052_IS_LVB64_OFF				0x0081//�жϲ���������LVb64��
#define		COMMAND_24_0053_IS_LVB65_OFF				0x0082//�жϲ���������LVb65��
#define		COMMAND_24_0054_IS_LVB66_OFF				0x0083//�жϲ���������LVb66��
#define		COMMAND_24_0055_IS_LVB67_OFF				0x0084//�жϲ���������LVb67��
#define		COMMAND_24_0056_IS_LVB68_OFF				0x0085//�жϲ���������LVb68��
#define		COMMAND_24_0057_IS_LVB69_OFF				0x0086//�жϲ���������LVb69��
#define		COMMAND_24_0058_IS_LVB70_OFF				0x0087//�жϲ���������LVb70��
#define		COMMAND_24_0059_IS_LVB71_OFF				0x0088//�жϲ���������LVb71��
#define		COMMAND_24_0060_IS_LVB72_OFF				0x0089//�жϲ���������LVb72��
#define		COMMAND_24_0061_IS_LVB73_OFF				0x008a//�жϲ���������LVb73��
#define		COMMAND_24_0062_IS_LVB74_OFF				0x008b//�жϲ���������LVb74��
#define		COMMAND_24_0063_IS_LVB75_OFF				0x008c//�жϲ���������LVb75��
#define		COMMAND_24_0064_IS_LVB76_OFF				0x008d//�жϲ���������LVb76��
#define		COMMAND_24_0065_IS_LVB77_OFF				0x008e//�жϲ���������LVb77��
#define		COMMAND_24_0066_IS_LVB78_OFF				0x008f//�жϲ���������LVb78��
#define		COMMAND_24_0067_IS_LVB79_OFF				0x0090//�жϲ���������LVb79��
#define		COMMAND_24_0068_IS_LVB80_OFF				0x0091//�жϲ���������LVb80��
#define		COMMAND_24_0069_IS_LVB81_OFF				0x0092//�жϲ���������LVb81��
#define		COMMAND_24_0070_IS_LVB82_OFF				0x0093//�жϲ���������LVb82��
#define		COMMAND_24_0071_IS_LVB83_OFF				0x0094//�жϲ���������LVb83��
#define		COMMAND_24_0072_IS_LVB84_OFF				0x0095//�жϲ���������LVb84��
#define		COMMAND_24_0073_IS_LVB85_OFF				0x0096//�жϲ���������LVb85��
#define		COMMAND_24_0074_IS_LVB86_OFF				0x0097//�жϲ���������LVb86��
#define		COMMAND_24_0075_IS_LVB87_OFF				0x0098//�жϲ���������LVb87��


//����ϵͳ�������ϵ�
#define		COMMAND_24_0001_VALVE_POWER_OFF				0x0099


//�жϲ���ϵͳ�������ϵ�
#define		COMMAND_24_0001_IS_VALVE_POWER_OFF			0x009a



//��������-------------------------------------------------------------------------------

void TGTHT510_supply_stage22_resume_main(void);
uint16 TGTHT510_supply_stage22_resume_step_detection_disable(void);
uint16 TGTHT510_supply_stage22_resume_step_supply_temperature_control_disable(void);
uint16 TGTHT510_supply_stage22_resume_step_valve_all_off(void);
uint16 TGTHT510_supply_stage22_resume_step_valve_power_off(void);
uint16 TGTHT510_supply_stage22_resume_step_is_valve_power_off(void);


#endif
 
 
 
