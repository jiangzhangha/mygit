/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ���������������������ͷ�ļ�
  ******************************************************************************
  */
 
#ifndef __supply_stage_02_set_h
#define __supply_stage_02_set_h
 

/*�����ṹ������--------------------------------------------------------------*/



/*�궨��----------------------------------------------------------------------*/

//����step----------------------------------------------------------------------

#define 	STEP_02_SUPPLY_DETECTION_ENABLE				0x0001//���ӹ��ϼ��ʹ��
#define		STEP_02_SUPPLY_TEMPER_CTRL_ENABLE			0x0002//�����Զ�����ʹ��
#define		STEP_02_SUPPLY_VALVE_POWER_ON				0x0003//����ϵͳ�������ӵ�
#define		STEP_02_SUPPLY_VALVE_ALL_OFF				0x0004//����ϵͳ�������ر�


//����command-------------------------------------------------------------------

//����ϵͳ�������ӵ�
#define		COMMAND_02_0001_EQU_VALVE_POWER_ON			0x0001//�����豸����ָ������������ӵ�
#define		COMMAND_02_0002_ASK_FOR_SERVICE				0x0002//���ͷ�������
#define		COMMAND_02_0003_TIME_1MIN_START				0x0003//��ʱ1min��ʼ
#define		COMMAND_02_0004_IS_TIME_1MIN				0x0004//��ʱ1min�Ƿ�
#define		COMMAND_02_0005_IS_VALVE_POWER_ON			0x0005//�ж�����������״̬�Ƿ�����


//����ϵͳ�������ر�
#define		COMMAND_02_0006_LVB01_OFF					0x0006//����������LVb1��
#define		COMMAND_02_0007_LVB02_OFF					0x0007//����������LVb2��
#define		COMMAND_02_0008_LVB03_OFF					0x0008//����������LVb3��
#define		COMMAND_02_0009_LVB04_OFF					0x0009//����������LVb4��
#define		COMMAND_02_0010_LVB05_OFF					0x000a//����������LVb5��
#define		COMMAND_02_0011_LVB06_OFF					0x000b//����������LVb6��
#define		COMMAND_02_0012_LVB07_OFF					0x000c//����������LVb7��
#define		COMMAND_02_0013_LVB08_OFF					0x000d//����������LVb8��
#define		COMMAND_02_0014_LVB09_OFF					0x000e//����������LVb9��
#define		COMMAND_02_0015_LVB10_OFF					0x000f//����������LVb10��
#define		COMMAND_02_0016_LVB11_OFF					0x0010//����������LVb11��
#define		COMMAND_02_0017_LVB12_OFF					0x0011//����������LVb12��
#define		COMMAND_02_0018_LVB13_OFF					0x0012//����������LVb13��
#define		COMMAND_02_0019_LVB14_OFF					0x0013//����������LVb14��
#define		COMMAND_02_0020_LVB15_OFF					0x0014//����������LVb15��
#define		COMMAND_02_0021_LVB16_OFF					0x0015//����������LVb16��
#define		COMMAND_02_0022_LVB17_OFF					0x0016//����������LVb17��
#define		COMMAND_02_0023_LVB18_OFF					0x0017//����������LVb18��
#define		COMMAND_02_0024_LVB19_OFF					0x0018//����������LVb19��
#define		COMMAND_02_0025_LVB20_OFF					0x0019//����������LVb20��
#define		COMMAND_02_0026_LVB21_OFF					0x001a//����������LVb21��
#define		COMMAND_02_0027_LVB22_OFF					0x001b//����������LVb22��
#define		COMMAND_02_0028_LVB23_OFF					0x001c//����������LVb23��
#define		COMMAND_02_0029_LVB24_OFF					0x001d//����������LVb24��
#define		COMMAND_02_0030_LVB25_OFF					0x001e//����������LVb25��
#define		COMMAND_02_0031_LVB26_OFF					0x001f//����������LVb26��
#define		COMMAND_02_0032_LVB39_OFF					0x0020//����������LVb39��
#define		COMMAND_02_0033_LVB40_OFF					0x0021//����������LVb40��
#define		COMMAND_02_0034_LVB41_OFF					0x0022//����������LVb41��
#define		COMMAND_02_0035_LVB42_OFF					0x0023//����������LVb42��
#define		COMMAND_02_0036_LVB43_OFF					0x0024//����������LVb43��
#define		COMMAND_02_0037_LVB44_OFF					0x0025//����������LVb44��
#define		COMMAND_02_0038_LVB45_OFF					0x0026//����������LVb45��
#define		COMMAND_02_0039_LVB46_OFF					0x0027//����������LVb46��
#define		COMMAND_02_0040_LVB47_OFF					0x0028//����������LVb47��
#define		COMMAND_02_0041_LVB48_OFF					0x0029//����������LVb48��
#define		COMMAND_02_0042_LVB49_OFF					0x002a//����������LVb49��
#define		COMMAND_02_0043_LVB50_OFF					0x002b//����������LVb50��
#define		COMMAND_02_0044_LVB51_OFF					0x002c//����������LVb51��
#define		COMMAND_02_0045_LVB52_OFF					0x002d//����������LVb52��
#define		COMMAND_02_0046_LVB53_OFF					0x002e//����������LVb53��
#define		COMMAND_02_0047_LVB54_OFF					0x002f//����������LVb54��
#define		COMMAND_02_0048_LVB55_OFF					0x0030//����������LVb55��
#define		COMMAND_02_0049_LVB56_OFF					0x0031//����������LVb56��
#define		COMMAND_02_0050_LVB57_OFF					0x0032//����������LVb57��
#define		COMMAND_02_0051_LVB58_OFF					0x0033//����������LVb58��
#define		COMMAND_02_0052_LVB59_OFF					0x0034//����������LVb59��
#define		COMMAND_02_0053_LVB60_OFF					0x0035//����������LVb60��
#define		COMMAND_02_0054_LVB61_OFF					0x0036//����������LVb61��
#define		COMMAND_02_0055_LVB62_OFF					0x0037//����������LVb62��
#define		COMMAND_02_0056_LVB63_OFF					0x0038//����������LVb63��
#define		COMMAND_02_0057_LVB64_OFF					0x0039//����������LVb64��
#define		COMMAND_02_0058_LVB65_OFF					0x003a//����������LVb65��
#define		COMMAND_02_0059_LVB66_OFF					0x003b//����������LVb66��
#define		COMMAND_02_0060_LVB67_OFF					0x003c//����������LVb67��
#define		COMMAND_02_0061_LVB68_OFF					0x003d//����������LVb68��
#define		COMMAND_02_0062_LVB69_OFF					0x003e//����������LVb69��
#define		COMMAND_02_0063_LVB70_OFF					0x003f//����������LVb70��
#define		COMMAND_02_0064_LVB71_OFF					0x0040//����������LVb71��
#define		COMMAND_02_0065_LVB72_OFF					0x0041//����������LVb72��
#define		COMMAND_02_0066_LVB73_OFF					0x0042//����������LVb73��
#define		COMMAND_02_0067_LVB74_OFF					0x0043//����������LVb74��
#define		COMMAND_02_0068_LVB75_OFF					0x0044//����������LVb75��
#define		COMMAND_02_0069_LVB76_OFF					0x0045//����������LVb76��
#define		COMMAND_02_0070_LVB77_OFF					0x0046//����������LVb77��
#define		COMMAND_02_0071_LVB78_OFF					0x0047//����������LVb78��
#define		COMMAND_02_0072_LVB79_OFF					0x0048//����������LVb79��
#define		COMMAND_02_0073_LVB80_OFF					0x0049//����������LVb80��
#define		COMMAND_02_0074_LVB81_OFF					0x004a//����������LVb81��
#define		COMMAND_02_0075_LVB82_OFF					0x004b//����������LVb82��
#define		COMMAND_02_0076_LVB83_OFF					0x004c//����������LVb83��
#define		COMMAND_02_0077_LVB84_OFF					0x004d//����������LVb84��
#define		COMMAND_02_0078_LVB85_OFF					0x004e//����������LVb85��
#define		COMMAND_02_0079_LVB86_OFF					0x004f//����������LVb86��
#define		COMMAND_02_0080_LVB87_OFF					0x0050//����������LVb87��


#define		COMMAND_02_0081_IS_LVB01_OFF				0x0051//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0082_IS_LVB02_OFF				0x0052//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0083_IS_LVB03_OFF				0x0053//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0084_IS_LVB04_OFF				0x0054//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0085_IS_LVB05_OFF				0x0055//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0086_IS_LVB06_OFF				0x0056//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0087_IS_LVB07_OFF				0x0057//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0088_IS_LVB08_OFF				0x0058//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0089_IS_LVB09_OFF				0x0059//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0090_IS_LVB10_OFF				0x005a//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0091_IS_LVB11_OFF				0x005b//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0092_IS_LVB12_OFF				0x005c//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0093_IS_LVB13_OFF				0x005d//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0094_IS_LVB14_OFF				0x005e//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0095_IS_LVB15_OFF				0x005f//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0096_IS_LVB16_OFF				0x0060//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0097_IS_LVB17_OFF				0x0061//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0098_IS_LVB18_OFF				0x0062//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0099_IS_LVB19_OFF				0x0063//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0100_IS_LVB20_OFF				0x0064//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0101_IS_LVB21_OFF				0x0065//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0102_IS_LVB22_OFF				0x0066//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0103_IS_LVB23_OFF				0x0067//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0104_IS_LVB24_OFF				0x0068//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0105_IS_LVB25_OFF				0x0069//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0106_IS_LVB26_OFF				0x006a//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0107_IS_LVB39_OFF				0x006b//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0108_IS_LVB40_OFF				0x006c//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0109_IS_LVB41_OFF				0x006d//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0110_IS_LVB42_OFF				0x006e//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0111_IS_LVB43_OFF				0x006f//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0112_IS_LVB44_OFF				0x0070//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0113_IS_LVB45_OFF				0x0071//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0114_IS_LVB46_OFF				0x0072//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0115_IS_LVB47_OFF				0x0073//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0116_IS_LVB48_OFF				0x0074//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0117_IS_LVB49_OFF				0x0075//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0118_IS_LVB50_OFF				0x0076//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0119_IS_LVB51_OFF				0x0077//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0120_IS_LVB52_OFF				0x0078//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0121_IS_LVB53_OFF				0x0079//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0122_IS_LVB54_OFF				0x007a//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0123_IS_LVB55_OFF				0x007b//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0124_IS_LVB56_OFF				0x007c//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0125_IS_LVB57_OFF				0x007d//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0126_IS_LVB58_OFF				0x007e//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0127_IS_LVB59_OFF				0x007f//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0128_IS_LVB60_OFF				0x0080//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0129_IS_LVB61_OFF				0x0081//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0130_IS_LVB62_OFF				0x0082//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0131_IS_LVB63_OFF				0x0083//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0132_IS_LVB64_OFF				0x0084//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0133_IS_LVB65_OFF				0x0085//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0134_IS_LVB66_OFF				0x0086//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0135_IS_LVB67_OFF				0x0087//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0136_IS_LVB68_OFF				0x0088//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0137_IS_LVB69_OFF				0x0089//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0138_IS_LVB70_OFF				0x008a//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0139_IS_LVB71_OFF				0x008b//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0140_IS_LVB72_OFF				0x008c//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0141_IS_LVB73_OFF				0x008d//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0142_IS_LVB74_OFF				0x008e//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0143_IS_LVB75_OFF				0x008f//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0144_IS_LVB76_OFF				0x0090//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0145_IS_LVB77_OFF				0x0091//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0146_IS_LVB78_OFF				0x0092//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0147_IS_LVB79_OFF				0x0093//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0148_IS_LVB80_OFF				0x0094//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0149_IS_LVB81_OFF				0x0095//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0150_IS_LVB82_OFF				0x0096//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0151_IS_LVB83_OFF				0x0097//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0152_IS_LVB84_OFF				0x0098//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0153_IS_LVB85_OFF				0x0099//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0154_IS_LVB86_OFF				0x009a//�ж�������LVb1�Ƿ�ر�
#define		COMMAND_02_0155_IS_LVB87_OFF				0x009b//�ж�������LVb1�Ƿ�ر�


//---------��������--------------------------------------------------------------------

void TGTHT510_supply_stage02_set_main(void);
void TGTHT510_supply_stage02_set_supply_valve_power_on(void);
void TGTHT510_supply_stage02_set_supply_valve_all_off(void);




#endif
 
 
 
