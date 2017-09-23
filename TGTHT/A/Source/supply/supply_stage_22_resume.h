/**
  ******************************************************************************
  * @file    supply_main.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器补加流程主程序头文件
  ******************************************************************************
  */
 
#ifndef __supply_stage_22_resume_h
#define __supply_stage_22_resume_h
 

/*声明结构体类型--------------------------------------------------------------*/



/*宏定义---------------------------------------------------------------------------*/

//步骤step----------------------------------------------------------------------

#define 	STEP_24_SUPPLY_DETECTION_DISABLE			0x0001//补加故障检测禁止
#define		STEP_24_SUPPLY_TEMPER_CTRL_DISABLE			0x0002//补加自动控温禁止
#define		STEP_24_SUPPLY_VALVE_ALL_OFF				0x0003//补加系统自锁阀关闭
#define		STEP_24_SUPPLY_VALVE_POWER_OFF				0x0004//补加系统自锁阀断电
#define		STEP_24_SUPPLY_IS_VALVE_POWER_OFF			0x0005//判断补加系统自锁阀断电

//命令command-------------------------------------------------------------------

//补加故障检测使能
#define		COMMAND_24_0001_DETECTION_DISABLE			0x0001

//补加自动控温使能
#define		COMMAND_24_0001_TEMPER_CTRL_DISABLE			0x0002

//补加系统自锁阀关闭
#define		COMMAND_24_0001_LVB01_OFF					0x0003//补加自锁阀LVb1关
#define		COMMAND_24_0002_LVB02_OFF					0x0004//补加自锁阀LVb2关
#define		COMMAND_24_0003_LVB03_OFF					0x0005//补加自锁阀LVb3关
#define		COMMAND_24_0004_LVB04_OFF					0x0006//补加自锁阀LVb4关
#define		COMMAND_24_0005_LVB05_OFF					0x0007//补加自锁阀LVb5关
#define		COMMAND_24_0006_LVB06_OFF					0x0008//补加自锁阀LVb6关
#define		COMMAND_24_0007_LVB07_OFF					0x0009//补加自锁阀LVb7关
#define		COMMAND_24_0008_LVB08_OFF					0x000a//补加自锁阀LVb8关
#define		COMMAND_24_0009_LVB09_OFF					0x000b//补加自锁阀LVb9关
#define		COMMAND_24_0010_LVB10_OFF					0x000c//补加自锁阀LVb10关
#define		COMMAND_24_0011_LVB11_OFF					0x000d//补加自锁阀LVb11关
#define		COMMAND_24_0012_LVB12_OFF					0x000e//补加自锁阀LVb12关
#define		COMMAND_24_0013_LVB13_OFF					0x000f//补加自锁阀LVb13关
#define		COMMAND_24_0014_LVB14_OFF					0x0010//补加自锁阀LVb14关
#define		COMMAND_24_0015_LVB15_OFF					0x0011//补加自锁阀LVb15关
#define		COMMAND_24_0016_LVB16_OFF					0x0012//补加自锁阀LVb16关
#define		COMMAND_24_0017_LVB17_OFF					0x0013//补加自锁阀LVb17关
#define		COMMAND_24_0018_LVB18_OFF					0x0014//补加自锁阀LVb18关
#define		COMMAND_24_0019_LVB19_OFF					0x0015//补加自锁阀LVb19关
#define		COMMAND_24_0020_LVB20_OFF					0x0016//补加自锁阀LVb20关
#define		COMMAND_24_0021_LVB21_OFF					0x0017//补加自锁阀LVb21关
#define		COMMAND_24_0022_LVB22_OFF					0x0018//补加自锁阀LVb22关
#define		COMMAND_24_0023_LVB23_OFF					0x0019//补加自锁阀LVb23关
#define		COMMAND_24_0024_LVB24_OFF					0x001a//补加自锁阀LVb24关
#define		COMMAND_24_0025_LVB25_OFF					0x001b//补加自锁阀LVb25关
#define		COMMAND_24_0026_LVB26_OFF					0x001c//补加自锁阀LVb26关
#define		COMMAND_24_0027_LVB39_OFF					0x001d//补加自锁阀LVb39关
#define		COMMAND_24_0028_LVB40_OFF					0x001e//补加自锁阀LVb40关
#define		COMMAND_24_0029_LVB41_OFF					0x001f//补加自锁阀LVb41关
#define		COMMAND_24_0030_LVB42_OFF					0x0020//补加自锁阀LVb42关
#define		COMMAND_24_0031_LVB43_OFF					0x0021//补加自锁阀LVb43关
#define		COMMAND_24_0032_LVB44_OFF					0x0022//补加自锁阀LVb44关
#define		COMMAND_24_0033_LVB45_OFF					0x0023//补加自锁阀LVb45关
#define		COMMAND_24_0034_LVB46_OFF					0x0024//补加自锁阀LVb46关
#define		COMMAND_24_0035_LVB47_OFF					0x0025//补加自锁阀LVb47关
#define		COMMAND_24_0036_LVB48_OFF					0x0026//补加自锁阀LVb48关
#define		COMMAND_24_0037_LVB49_OFF					0x0027//补加自锁阀LVb49关
#define		COMMAND_24_0038_LVB50_OFF					0x0028//补加自锁阀LVb50关
#define		COMMAND_24_0039_LVB51_OFF					0x0029//补加自锁阀LVb51关
#define		COMMAND_24_0040_LVB52_OFF					0x002a//补加自锁阀LVb52关
#define		COMMAND_24_0041_LVB53_OFF					0x002b//补加自锁阀LVb53关
#define		COMMAND_24_0042_LVB54_OFF					0x002c//补加自锁阀LVb54关
#define		COMMAND_24_0043_LVB55_OFF					0x002d//补加自锁阀LVb55关
#define		COMMAND_24_0044_LVB56_OFF					0x002e//补加自锁阀LVb56关
#define		COMMAND_24_0045_LVB57_OFF					0x002f//补加自锁阀LVb57关
#define		COMMAND_24_0046_LVB58_OFF					0x0030//补加自锁阀LVb58关
#define		COMMAND_24_0047_LVB59_OFF					0x0031//补加自锁阀LVb59关
#define		COMMAND_24_0048_LVB60_OFF					0x0032//补加自锁阀LVb60关
#define		COMMAND_24_0049_LVB61_OFF					0x0033//补加自锁阀LVb61关
#define		COMMAND_24_0050_LVB62_OFF					0x0034//补加自锁阀LVb62关
#define		COMMAND_24_0051_LVB63_OFF					0x0035//补加自锁阀LVb63关
#define		COMMAND_24_0052_LVB64_OFF					0x0036//补加自锁阀LVb64关
#define		COMMAND_24_0053_LVB65_OFF					0x0037//补加自锁阀LVb65关
#define		COMMAND_24_0054_LVB66_OFF					0x0038//补加自锁阀LVb66关
#define		COMMAND_24_0055_LVB67_OFF					0x0039//补加自锁阀LVb67关
#define		COMMAND_24_0056_LVB68_OFF					0x003a//补加自锁阀LVb68关
#define		COMMAND_24_0057_LVB69_OFF					0x003b//补加自锁阀LVb69关
#define		COMMAND_24_0058_LVB70_OFF					0x003c//补加自锁阀LVb70关
#define		COMMAND_24_0059_LVB71_OFF					0x003d//补加自锁阀LVb71关
#define		COMMAND_24_0060_LVB72_OFF					0x003e//补加自锁阀LVb72关
#define		COMMAND_24_0061_LVB73_OFF					0x003f//补加自锁阀LVb73关
#define		COMMAND_24_0062_LVB74_OFF					0x0040//补加自锁阀LVb74关
#define		COMMAND_24_0063_LVB75_OFF					0x0041//补加自锁阀LVb75关
#define		COMMAND_24_0064_LVB76_OFF					0x0042//补加自锁阀LVb76关
#define		COMMAND_24_0065_LVB77_OFF					0x0043//补加自锁阀LVb77关
#define		COMMAND_24_0066_LVB78_OFF					0x0044//补加自锁阀LVb78关
#define		COMMAND_24_0067_LVB79_OFF					0x0045//补加自锁阀LVb79关
#define		COMMAND_24_0068_LVB80_OFF					0x0046//补加自锁阀LVb80关
#define		COMMAND_24_0069_LVB81_OFF					0x0047//补加自锁阀LVb81关
#define		COMMAND_24_0070_LVB82_OFF					0x0048//补加自锁阀LVb82关
#define		COMMAND_24_0071_LVB83_OFF					0x0049//补加自锁阀LVb83关
#define		COMMAND_24_0072_LVB84_OFF					0x004a//补加自锁阀LVb84关
#define		COMMAND_24_0073_LVB85_OFF					0x004b//补加自锁阀LVb85关
#define		COMMAND_24_0074_LVB86_OFF					0x004c//补加自锁阀LVb86关
#define		COMMAND_24_0075_LVB87_OFF					0x004d//补加自锁阀LVb87关


//判断补加系统自锁阀关闭
#define		COMMAND_24_0001_IS_LVB01_OFF				0x004e//判断补加自锁阀LVb1关
#define		COMMAND_24_0002_IS_LVB02_OFF				0x004f//判断补加自锁阀LVb2关
#define		COMMAND_24_0003_IS_LVB03_OFF				0x0050//判断补加自锁阀LVb3关
#define		COMMAND_24_0004_IS_LVB04_OFF				0x0051//判断补加自锁阀LVb4关
#define		COMMAND_24_0005_IS_LVB05_OFF				0x0052//判断补加自锁阀LVb5关
#define		COMMAND_24_0006_IS_LVB06_OFF				0x0053//判断补加自锁阀LVb6关
#define		COMMAND_24_0007_IS_LVB07_OFF				0x0054//判断补加自锁阀LVb7关
#define		COMMAND_24_0008_IS_LVB08_OFF				0x0055//判断补加自锁阀LVb8关
#define		COMMAND_24_0009_IS_LVB09_OFF				0x0056//判断补加自锁阀LVb9关
#define		COMMAND_24_0010_IS_LVB10_OFF				0x0057//判断补加自锁阀LVb10关
#define		COMMAND_24_0011_IS_LVB11_OFF				0x0058//判断补加自锁阀LVb11关
#define		COMMAND_24_0012_IS_LVB12_OFF				0x0059//判断补加自锁阀LVb12关
#define		COMMAND_24_0013_IS_LVB13_OFF				0x005a//判断补加自锁阀LVb13关
#define		COMMAND_24_0014_IS_LVB14_OFF				0x005b//判断补加自锁阀LVb14关
#define		COMMAND_24_0015_IS_LVB15_OFF				0x005c//判断补加自锁阀LVb15关
#define		COMMAND_24_0016_IS_LVB16_OFF				0x005d//判断补加自锁阀LVb16关
#define		COMMAND_24_0017_IS_LVB17_OFF				0x005e//判断补加自锁阀LVb17关
#define		COMMAND_24_0018_IS_LVB18_OFF				0x005f//判断补加自锁阀LVb18关
#define		COMMAND_24_0019_IS_LVB19_OFF				0x0060//判断补加自锁阀LVb19关
#define		COMMAND_24_0020_IS_LVB20_OFF				0x0061//判断补加自锁阀LVb20关
#define		COMMAND_24_0021_IS_LVB21_OFF				0x0062//判断补加自锁阀LVb21关
#define		COMMAND_24_0022_IS_LVB22_OFF				0x0063//判断补加自锁阀LVb22关
#define		COMMAND_24_0023_IS_LVB23_OFF				0x0064//判断补加自锁阀LVb23关
#define		COMMAND_24_0024_IS_LVB24_OFF				0x0065//判断补加自锁阀LVb24关
#define		COMMAND_24_0025_IS_LVB25_OFF				0x0066//判断补加自锁阀LVb25关
#define		COMMAND_24_0026_IS_LVB26_OFF				0x0067//判断补加自锁阀LVb26关
#define		COMMAND_24_0027_IS_LVB39_OFF				0x0068//判断补加自锁阀LVb39关
#define		COMMAND_24_0028_IS_LVB40_OFF				0x0069//判断补加自锁阀LVb40关
#define		COMMAND_24_0029_IS_LVB41_OFF				0x006a//判断补加自锁阀LVb41关
#define		COMMAND_24_0030_IS_LVB42_OFF				0x006b//判断补加自锁阀LVb42关
#define		COMMAND_24_0031_IS_LVB43_OFF				0x006c//判断补加自锁阀LVb43关
#define		COMMAND_24_0032_IS_LVB44_OFF				0x006d//判断补加自锁阀LVb44关
#define		COMMAND_24_0033_IS_LVB45_OFF				0x006e//判断补加自锁阀LVb45关
#define		COMMAND_24_0034_IS_LVB46_OFF				0x006f//判断补加自锁阀LVb46关
#define		COMMAND_24_0035_IS_LVB47_OFF				0x0070//判断补加自锁阀LVb47关
#define		COMMAND_24_0036_IS_LVB48_OFF				0x0071//判断补加自锁阀LVb48关
#define		COMMAND_24_0037_IS_LVB49_OFF				0x0072//判断补加自锁阀LVb49关
#define		COMMAND_24_0038_IS_LVB50_OFF				0x0073//判断补加自锁阀LVb50关
#define		COMMAND_24_0039_IS_LVB51_OFF				0x0074//判断补加自锁阀LVb51关
#define		COMMAND_24_0040_IS_LVB52_OFF				0x0075//判断补加自锁阀LVb52关
#define		COMMAND_24_0041_IS_LVB53_OFF				0x0076//判断补加自锁阀LVb53关
#define		COMMAND_24_0042_IS_LVB54_OFF				0x0077//判断补加自锁阀LVb54关
#define		COMMAND_24_0043_IS_LVB55_OFF				0x0078//判断补加自锁阀LVb55关
#define		COMMAND_24_0044_IS_LVB56_OFF				0x0079//判断补加自锁阀LVb56关
#define		COMMAND_24_0045_IS_LVB57_OFF				0x007a//判断补加自锁阀LVb57关
#define		COMMAND_24_0046_IS_LVB58_OFF				0x007b//判断补加自锁阀LVb58关
#define		COMMAND_24_0047_IS_LVB59_OFF				0x007c//判断补加自锁阀LVb59关
#define		COMMAND_24_0048_IS_LVB60_OFF				0x007d//判断补加自锁阀LVb60关
#define		COMMAND_24_0049_IS_LVB61_OFF				0x007e//判断补加自锁阀LVb61关
#define		COMMAND_24_0050_IS_LVB62_OFF				0x007f//判断补加自锁阀LVb62关
#define		COMMAND_24_0051_IS_LVB63_OFF				0x0080//判断补加自锁阀LVb63关
#define		COMMAND_24_0052_IS_LVB64_OFF				0x0081//判断补加自锁阀LVb64关
#define		COMMAND_24_0053_IS_LVB65_OFF				0x0082//判断补加自锁阀LVb65关
#define		COMMAND_24_0054_IS_LVB66_OFF				0x0083//判断补加自锁阀LVb66关
#define		COMMAND_24_0055_IS_LVB67_OFF				0x0084//判断补加自锁阀LVb67关
#define		COMMAND_24_0056_IS_LVB68_OFF				0x0085//判断补加自锁阀LVb68关
#define		COMMAND_24_0057_IS_LVB69_OFF				0x0086//判断补加自锁阀LVb69关
#define		COMMAND_24_0058_IS_LVB70_OFF				0x0087//判断补加自锁阀LVb70关
#define		COMMAND_24_0059_IS_LVB71_OFF				0x0088//判断补加自锁阀LVb71关
#define		COMMAND_24_0060_IS_LVB72_OFF				0x0089//判断补加自锁阀LVb72关
#define		COMMAND_24_0061_IS_LVB73_OFF				0x008a//判断补加自锁阀LVb73关
#define		COMMAND_24_0062_IS_LVB74_OFF				0x008b//判断补加自锁阀LVb74关
#define		COMMAND_24_0063_IS_LVB75_OFF				0x008c//判断补加自锁阀LVb75关
#define		COMMAND_24_0064_IS_LVB76_OFF				0x008d//判断补加自锁阀LVb76关
#define		COMMAND_24_0065_IS_LVB77_OFF				0x008e//判断补加自锁阀LVb77关
#define		COMMAND_24_0066_IS_LVB78_OFF				0x008f//判断补加自锁阀LVb78关
#define		COMMAND_24_0067_IS_LVB79_OFF				0x0090//判断补加自锁阀LVb79关
#define		COMMAND_24_0068_IS_LVB80_OFF				0x0091//判断补加自锁阀LVb80关
#define		COMMAND_24_0069_IS_LVB81_OFF				0x0092//判断补加自锁阀LVb81关
#define		COMMAND_24_0070_IS_LVB82_OFF				0x0093//判断补加自锁阀LVb82关
#define		COMMAND_24_0071_IS_LVB83_OFF				0x0094//判断补加自锁阀LVb83关
#define		COMMAND_24_0072_IS_LVB84_OFF				0x0095//判断补加自锁阀LVb84关
#define		COMMAND_24_0073_IS_LVB85_OFF				0x0096//判断补加自锁阀LVb85关
#define		COMMAND_24_0074_IS_LVB86_OFF				0x0097//判断补加自锁阀LVb86关
#define		COMMAND_24_0075_IS_LVB87_OFF				0x0098//判断补加自锁阀LVb87关


//补加系统自锁阀断电
#define		COMMAND_24_0001_VALVE_POWER_OFF				0x0099


//判断补加系统自锁阀断电
#define		COMMAND_24_0001_IS_VALVE_POWER_OFF			0x009a



//函数声明-------------------------------------------------------------------------------

void TGTHT510_supply_stage22_resume_main(void);
uint16 TGTHT510_supply_stage22_resume_step_detection_disable(void);
uint16 TGTHT510_supply_stage22_resume_step_supply_temperature_control_disable(void);
uint16 TGTHT510_supply_stage22_resume_step_valve_all_off(void);
uint16 TGTHT510_supply_stage22_resume_step_valve_power_off(void);
uint16 TGTHT510_supply_stage22_resume_step_is_valve_power_off(void);


#endif
 
 
 
