/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器补加流程主程序头文件
  ******************************************************************************
  */
 
#ifndef __supply_stage_02_set_h
#define __supply_stage_02_set_h
 

/*声明结构体类型--------------------------------------------------------------*/



/*宏定义----------------------------------------------------------------------*/

//步骤step----------------------------------------------------------------------

#define 	STEP_02_SUPPLY_DETECTION_ENABLE				0x0001//补加故障检测使能
#define		STEP_02_SUPPLY_TEMPER_CTRL_ENABLE			0x0002//补加自动控温使能
#define		STEP_02_SUPPLY_VALVE_POWER_ON				0x0003//补加系统自锁阀加电
#define		STEP_02_SUPPLY_VALVE_ALL_OFF				0x0004//补加系统自锁阀关闭


//命令command-------------------------------------------------------------------

//补加系统自锁阀加电
#define		COMMAND_02_0001_EQU_VALVE_POWER_ON			0x0001//发送设备管理指令，补加自锁阀加电
#define		COMMAND_02_0002_ASK_FOR_SERVICE				0x0002//发送服务请求
#define		COMMAND_02_0003_TIME_1MIN_START				0x0003//计时1min开始
#define		COMMAND_02_0004_IS_TIME_1MIN				0x0004//延时1min是否到
#define		COMMAND_02_0005_IS_VALVE_POWER_ON			0x0005//判断自锁阀开关状态是否正常


//补加系统自锁阀关闭
#define		COMMAND_02_0006_LVB01_OFF					0x0006//补加自锁阀LVb1关
#define		COMMAND_02_0007_LVB02_OFF					0x0007//补加自锁阀LVb2关
#define		COMMAND_02_0008_LVB03_OFF					0x0008//补加自锁阀LVb3关
#define		COMMAND_02_0009_LVB04_OFF					0x0009//补加自锁阀LVb4关
#define		COMMAND_02_0010_LVB05_OFF					0x000a//补加自锁阀LVb5关
#define		COMMAND_02_0011_LVB06_OFF					0x000b//补加自锁阀LVb6关
#define		COMMAND_02_0012_LVB07_OFF					0x000c//补加自锁阀LVb7关
#define		COMMAND_02_0013_LVB08_OFF					0x000d//补加自锁阀LVb8关
#define		COMMAND_02_0014_LVB09_OFF					0x000e//补加自锁阀LVb9关
#define		COMMAND_02_0015_LVB10_OFF					0x000f//补加自锁阀LVb10关
#define		COMMAND_02_0016_LVB11_OFF					0x0010//补加自锁阀LVb11关
#define		COMMAND_02_0017_LVB12_OFF					0x0011//补加自锁阀LVb12关
#define		COMMAND_02_0018_LVB13_OFF					0x0012//补加自锁阀LVb13关
#define		COMMAND_02_0019_LVB14_OFF					0x0013//补加自锁阀LVb14关
#define		COMMAND_02_0020_LVB15_OFF					0x0014//补加自锁阀LVb15关
#define		COMMAND_02_0021_LVB16_OFF					0x0015//补加自锁阀LVb16关
#define		COMMAND_02_0022_LVB17_OFF					0x0016//补加自锁阀LVb17关
#define		COMMAND_02_0023_LVB18_OFF					0x0017//补加自锁阀LVb18关
#define		COMMAND_02_0024_LVB19_OFF					0x0018//补加自锁阀LVb19关
#define		COMMAND_02_0025_LVB20_OFF					0x0019//补加自锁阀LVb20关
#define		COMMAND_02_0026_LVB21_OFF					0x001a//补加自锁阀LVb21关
#define		COMMAND_02_0027_LVB22_OFF					0x001b//补加自锁阀LVb22关
#define		COMMAND_02_0028_LVB23_OFF					0x001c//补加自锁阀LVb23关
#define		COMMAND_02_0029_LVB24_OFF					0x001d//补加自锁阀LVb24关
#define		COMMAND_02_0030_LVB25_OFF					0x001e//补加自锁阀LVb25关
#define		COMMAND_02_0031_LVB26_OFF					0x001f//补加自锁阀LVb26关
#define		COMMAND_02_0032_LVB39_OFF					0x0020//补加自锁阀LVb39关
#define		COMMAND_02_0033_LVB40_OFF					0x0021//补加自锁阀LVb40关
#define		COMMAND_02_0034_LVB41_OFF					0x0022//补加自锁阀LVb41关
#define		COMMAND_02_0035_LVB42_OFF					0x0023//补加自锁阀LVb42关
#define		COMMAND_02_0036_LVB43_OFF					0x0024//补加自锁阀LVb43关
#define		COMMAND_02_0037_LVB44_OFF					0x0025//补加自锁阀LVb44关
#define		COMMAND_02_0038_LVB45_OFF					0x0026//补加自锁阀LVb45关
#define		COMMAND_02_0039_LVB46_OFF					0x0027//补加自锁阀LVb46关
#define		COMMAND_02_0040_LVB47_OFF					0x0028//补加自锁阀LVb47关
#define		COMMAND_02_0041_LVB48_OFF					0x0029//补加自锁阀LVb48关
#define		COMMAND_02_0042_LVB49_OFF					0x002a//补加自锁阀LVb49关
#define		COMMAND_02_0043_LVB50_OFF					0x002b//补加自锁阀LVb50关
#define		COMMAND_02_0044_LVB51_OFF					0x002c//补加自锁阀LVb51关
#define		COMMAND_02_0045_LVB52_OFF					0x002d//补加自锁阀LVb52关
#define		COMMAND_02_0046_LVB53_OFF					0x002e//补加自锁阀LVb53关
#define		COMMAND_02_0047_LVB54_OFF					0x002f//补加自锁阀LVb54关
#define		COMMAND_02_0048_LVB55_OFF					0x0030//补加自锁阀LVb55关
#define		COMMAND_02_0049_LVB56_OFF					0x0031//补加自锁阀LVb56关
#define		COMMAND_02_0050_LVB57_OFF					0x0032//补加自锁阀LVb57关
#define		COMMAND_02_0051_LVB58_OFF					0x0033//补加自锁阀LVb58关
#define		COMMAND_02_0052_LVB59_OFF					0x0034//补加自锁阀LVb59关
#define		COMMAND_02_0053_LVB60_OFF					0x0035//补加自锁阀LVb60关
#define		COMMAND_02_0054_LVB61_OFF					0x0036//补加自锁阀LVb61关
#define		COMMAND_02_0055_LVB62_OFF					0x0037//补加自锁阀LVb62关
#define		COMMAND_02_0056_LVB63_OFF					0x0038//补加自锁阀LVb63关
#define		COMMAND_02_0057_LVB64_OFF					0x0039//补加自锁阀LVb64关
#define		COMMAND_02_0058_LVB65_OFF					0x003a//补加自锁阀LVb65关
#define		COMMAND_02_0059_LVB66_OFF					0x003b//补加自锁阀LVb66关
#define		COMMAND_02_0060_LVB67_OFF					0x003c//补加自锁阀LVb67关
#define		COMMAND_02_0061_LVB68_OFF					0x003d//补加自锁阀LVb68关
#define		COMMAND_02_0062_LVB69_OFF					0x003e//补加自锁阀LVb69关
#define		COMMAND_02_0063_LVB70_OFF					0x003f//补加自锁阀LVb70关
#define		COMMAND_02_0064_LVB71_OFF					0x0040//补加自锁阀LVb71关
#define		COMMAND_02_0065_LVB72_OFF					0x0041//补加自锁阀LVb72关
#define		COMMAND_02_0066_LVB73_OFF					0x0042//补加自锁阀LVb73关
#define		COMMAND_02_0067_LVB74_OFF					0x0043//补加自锁阀LVb74关
#define		COMMAND_02_0068_LVB75_OFF					0x0044//补加自锁阀LVb75关
#define		COMMAND_02_0069_LVB76_OFF					0x0045//补加自锁阀LVb76关
#define		COMMAND_02_0070_LVB77_OFF					0x0046//补加自锁阀LVb77关
#define		COMMAND_02_0071_LVB78_OFF					0x0047//补加自锁阀LVb78关
#define		COMMAND_02_0072_LVB79_OFF					0x0048//补加自锁阀LVb79关
#define		COMMAND_02_0073_LVB80_OFF					0x0049//补加自锁阀LVb80关
#define		COMMAND_02_0074_LVB81_OFF					0x004a//补加自锁阀LVb81关
#define		COMMAND_02_0075_LVB82_OFF					0x004b//补加自锁阀LVb82关
#define		COMMAND_02_0076_LVB83_OFF					0x004c//补加自锁阀LVb83关
#define		COMMAND_02_0077_LVB84_OFF					0x004d//补加自锁阀LVb84关
#define		COMMAND_02_0078_LVB85_OFF					0x004e//补加自锁阀LVb85关
#define		COMMAND_02_0079_LVB86_OFF					0x004f//补加自锁阀LVb86关
#define		COMMAND_02_0080_LVB87_OFF					0x0050//补加自锁阀LVb87关


#define		COMMAND_02_0081_IS_LVB01_OFF				0x0051//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0082_IS_LVB02_OFF				0x0052//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0083_IS_LVB03_OFF				0x0053//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0084_IS_LVB04_OFF				0x0054//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0085_IS_LVB05_OFF				0x0055//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0086_IS_LVB06_OFF				0x0056//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0087_IS_LVB07_OFF				0x0057//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0088_IS_LVB08_OFF				0x0058//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0089_IS_LVB09_OFF				0x0059//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0090_IS_LVB10_OFF				0x005a//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0091_IS_LVB11_OFF				0x005b//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0092_IS_LVB12_OFF				0x005c//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0093_IS_LVB13_OFF				0x005d//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0094_IS_LVB14_OFF				0x005e//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0095_IS_LVB15_OFF				0x005f//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0096_IS_LVB16_OFF				0x0060//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0097_IS_LVB17_OFF				0x0061//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0098_IS_LVB18_OFF				0x0062//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0099_IS_LVB19_OFF				0x0063//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0100_IS_LVB20_OFF				0x0064//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0101_IS_LVB21_OFF				0x0065//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0102_IS_LVB22_OFF				0x0066//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0103_IS_LVB23_OFF				0x0067//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0104_IS_LVB24_OFF				0x0068//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0105_IS_LVB25_OFF				0x0069//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0106_IS_LVB26_OFF				0x006a//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0107_IS_LVB39_OFF				0x006b//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0108_IS_LVB40_OFF				0x006c//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0109_IS_LVB41_OFF				0x006d//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0110_IS_LVB42_OFF				0x006e//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0111_IS_LVB43_OFF				0x006f//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0112_IS_LVB44_OFF				0x0070//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0113_IS_LVB45_OFF				0x0071//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0114_IS_LVB46_OFF				0x0072//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0115_IS_LVB47_OFF				0x0073//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0116_IS_LVB48_OFF				0x0074//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0117_IS_LVB49_OFF				0x0075//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0118_IS_LVB50_OFF				0x0076//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0119_IS_LVB51_OFF				0x0077//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0120_IS_LVB52_OFF				0x0078//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0121_IS_LVB53_OFF				0x0079//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0122_IS_LVB54_OFF				0x007a//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0123_IS_LVB55_OFF				0x007b//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0124_IS_LVB56_OFF				0x007c//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0125_IS_LVB57_OFF				0x007d//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0126_IS_LVB58_OFF				0x007e//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0127_IS_LVB59_OFF				0x007f//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0128_IS_LVB60_OFF				0x0080//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0129_IS_LVB61_OFF				0x0081//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0130_IS_LVB62_OFF				0x0082//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0131_IS_LVB63_OFF				0x0083//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0132_IS_LVB64_OFF				0x0084//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0133_IS_LVB65_OFF				0x0085//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0134_IS_LVB66_OFF				0x0086//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0135_IS_LVB67_OFF				0x0087//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0136_IS_LVB68_OFF				0x0088//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0137_IS_LVB69_OFF				0x0089//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0138_IS_LVB70_OFF				0x008a//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0139_IS_LVB71_OFF				0x008b//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0140_IS_LVB72_OFF				0x008c//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0141_IS_LVB73_OFF				0x008d//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0142_IS_LVB74_OFF				0x008e//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0143_IS_LVB75_OFF				0x008f//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0144_IS_LVB76_OFF				0x0090//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0145_IS_LVB77_OFF				0x0091//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0146_IS_LVB78_OFF				0x0092//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0147_IS_LVB79_OFF				0x0093//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0148_IS_LVB80_OFF				0x0094//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0149_IS_LVB81_OFF				0x0095//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0150_IS_LVB82_OFF				0x0096//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0151_IS_LVB83_OFF				0x0097//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0152_IS_LVB84_OFF				0x0098//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0153_IS_LVB85_OFF				0x0099//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0154_IS_LVB86_OFF				0x009a//判断自锁阀LVb1是否关闭
#define		COMMAND_02_0155_IS_LVB87_OFF				0x009b//判断自锁阀LVb1是否关闭


//---------函数声明--------------------------------------------------------------------

void TGTHT510_supply_stage02_set_main(void);
void TGTHT510_supply_stage02_set_supply_valve_power_on(void);
void TGTHT510_supply_stage02_set_supply_valve_all_off(void);




#endif
 
 
 
