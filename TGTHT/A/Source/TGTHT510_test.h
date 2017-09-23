/**
  ******************************************************************************
  * @file    TGTHT510_test.h
  * @author  蒋章
  * @version V1.00
  * @date    20150624
  * @brief   空间站核心舱推进管理器测试代码头文件
  ******************************************************************************
  */
 
 #ifndef __TGTHT510_test_h
 #define __TGTHT510_test_h
 
 
/*宏定义----------------------------------------------------------------------*/

//铂电阻温度值

#define TEMPER_PT_NEG_12	0x01ed
#define TEMPER_PT_NEG_11	0x01ef
#define TEMPER_PT_NEG_10	0x01f0
#define TEMPER_PT_NEG_09	0x01f2
#define TEMPER_PT_NEG_08	0x01f3
#define TEMPER_PT_NEG_07	0x01f5
#define TEMPER_PT_NEG_06	0x01f6
#define TEMPER_PT_NEG_05	0x01f8
#define TEMPER_PT_NEG_04	0x01f9
#define TEMPER_PT_NEG_03	0x01fb
#define TEMPER_PT_NEG_02	0x01fc
#define TEMPER_PT_NEG_01	0x01fe
#define TEMPER_PT_POS_00	0x01ff
#define TEMPER_PT_POS_01	0x0201
#define TEMPER_PT_POS_02	0x0202
#define TEMPER_PT_POS_03	0x0204
#define TEMPER_PT_POS_04	0x0205
#define TEMPER_PT_POS_05	0x0207
#define TEMPER_PT_POS_06	0x0208
#define TEMPER_PT_POS_07	0x020a
#define TEMPER_PT_POS_08	0x020b
#define TEMPER_PT_POS_09	0x020d
#define TEMPER_PT_POS_10	0x020e
#define TEMPER_PT_POS_11	0x0210
#define TEMPER_PT_POS_12	0x0211
#define TEMPER_PT_POS_13	0x0213
#define TEMPER_PT_POS_14	0x0214
#define TEMPER_PT_POS_15	0x0216
#define TEMPER_PT_POS_16	0x0217
#define TEMPER_PT_POS_17	0x0219
#define TEMPER_PT_POS_18	0x021a
#define TEMPER_PT_POS_19	0x021b
#define TEMPER_PT_POS_20	0x021d


//MF61温度值

#define TEMPER_MF61_NEG_12	0x0054
#define TEMPER_MF61_NEG_11	0x0053
#define TEMPER_MF61_NEG_10	0x0051
#define TEMPER_MF61_NEG_09	0x0050
#define TEMPER_MF61_NEG_08	0x004f
#define TEMPER_MF61_NEG_07	0x004d
#define TEMPER_MF61_NEG_06	0x004c
#define TEMPER_MF61_NEG_05	0x004a
#define TEMPER_MF61_NEG_04	0x0049
#define TEMPER_MF61_NEG_03	0x0047
#define TEMPER_MF61_NEG_02	0x0046
#define TEMPER_MF61_NEG_01	0x0044
#define TEMPER_MF61_POS_00	0x0043
#define TEMPER_MF61_POS_01	0x0041
#define TEMPER_MF61_POS_02	0x0040
#define TEMPER_MF61_POS_03	0x003f
#define TEMPER_MF61_POS_04	0x003d
#define TEMPER_MF61_POS_05	0x003c
#define TEMPER_MF61_POS_06	0x003a
#define TEMPER_MF61_POS_07	0x0039
#define TEMPER_MF61_POS_08	0x0038
#define TEMPER_MF61_POS_09	0x0036
#define TEMPER_MF61_POS_10	0x0035
#define TEMPER_MF61_POS_11	0x0034
#define TEMPER_MF61_POS_12	0x0032
#define TEMPER_MF61_POS_13	0x0031
#define TEMPER_MF61_POS_14	0x0030
#define TEMPER_MF61_POS_15	0x002f
#define TEMPER_MF61_POS_16	0x002d
#define TEMPER_MF61_POS_17	0x002c
#define TEMPER_MF61_POS_18	0x002b
#define TEMPER_MF61_POS_19	0x002a
#define TEMPER_MF61_POS_20	0x0029

//MF51温度值

#define TEMPER_MF51_NEG_12	0x0076
#define TEMPER_MF51_NEG_11	0x0075
#define TEMPER_MF51_NEG_10	0x0075
#define TEMPER_MF51_NEG_09	0x0075
#define TEMPER_MF51_NEG_08	0x0074
#define TEMPER_MF51_NEG_07	0x0074
#define TEMPER_MF51_NEG_06	0x0073
#define TEMPER_MF51_NEG_05	0x0073
#define TEMPER_MF51_NEG_04	0x0072
#define TEMPER_MF51_NEG_03	0x0072
#define TEMPER_MF51_NEG_02	0x0071
#define TEMPER_MF51_NEG_01	0x0071
#define TEMPER_MF51_POS_00	0x0070
#define TEMPER_MF51_POS_01	0x006f
#define TEMPER_MF51_POS_02	0x006f
#define TEMPER_MF51_POS_03	0x006e
#define TEMPER_MF51_POS_04	0x006e
#define TEMPER_MF51_POS_05	0x006d
#define TEMPER_MF51_POS_06	0x006c
#define TEMPER_MF51_POS_07	0x006c
#define TEMPER_MF51_POS_08	0x006b
#define TEMPER_MF51_POS_09	0x006a
#define TEMPER_MF51_POS_10	0x0069
#define TEMPER_MF51_POS_11	0x0069
#define TEMPER_MF51_POS_12	0x0068
#define TEMPER_MF51_POS_13	0x0067
#define TEMPER_MF51_POS_14	0x0066
#define TEMPER_MF51_POS_15	0x0066
#define TEMPER_MF51_POS_16	0x0065
#define TEMPER_MF51_POS_17	0x0064
#define TEMPER_MF51_POS_18	0x0063
#define TEMPER_MF51_POS_19	0x0062
#define TEMPER_MF51_POS_20	0x0061

 
 
/*函数声明--------------------------------------------------------------------*/

 void TGTHT510_test_TGTHT100_Temper(void);

 
 #endif
 
 
 
