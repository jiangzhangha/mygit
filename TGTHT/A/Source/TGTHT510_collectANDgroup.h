/**
  ******************************************************************************
  * @file    TGTHT510_collectANDgroup.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ�������ң��״̬�ɼ�����֡ģ��ͷ�ļ�
  ******************************************************************************
  */

#ifndef __TGTHT510_collectANDgroup_h
#define __TGTHT510_collectANDgroup_h 


/*�����ṹ������---------------------------------------------------------*/
typedef struct
{
	uint8 command_data[14];
	
}equiment_command_EPDU_command_data_TypeDef;//�����豸����ָ���еĳ̿�ָ��ṹ�壬14�ֽ�

typedef struct
{
	uint16 APID;
	uint8 VCID;

}equiment_command_EPDU_APID_VCID_TypeDef;//����APID��VCID�ṹ��


/*�궨��----------------------------------------------------------------------*/

#define COUNT_8BIT 		0x0202		//֡���кţ�8λ
#define COUNT_14BIT 	0x0303		//֡���кţ�14λ

#define ASK_FOR_SERVICE_EQUIMENT_COMMAND 	0x0505		//���������豸����ָ��
#define ASK_FOR_SERVICE_FAULT_CODE			0x0707		//�������󣬹��ϴ���
#define ASK_FOR_SERVICE_MEMORY				0x0909		//���������ڴ��´�


#define HEATER_ON 		0xaa55		//������״̬��ͨ
#define HEATER_OFF 		0x55aa		//������״̬�Ͽ�

#define VALVE_ON 		0x1010		//����״̬��
#define VALVE_OFF 		0x1212		//����״̬�ر�
#define VALVE_UNKNOW 	0x1414		//����״̬δ֪
#define VALVE_NO_POWER 	0x1818		//����״̬δ�ϵ�
#define VALVE_UNDEFINE 	0x1a1a		//����δ����



#define HEATER_STATE_READ_REG0 0x21000000
#define HEATER_STATE_READ_REG1 0x21000004
#define HEATER_STATE_READ_REG2 0x21000008
#define HEATER_STATE_READ_REG3 0x2100000c
#define HEATER_STATE_READ_REG4 0x22000000
#define HEATER_STATE_READ_REG5 0x22000004
#define HEATER_STATE_READ_REG6 0x22000008
#define HEATER_STATE_READ_REG7 0x2200000c    	//������״̬��ȡ�ⲿ��ַ
#define	HEATER_STATE_READ_GK   0x27000000		//��ر��ݼ���״̬



#ifdef TEST_VERSION

#define VALVE_STATE_READ_REG0 	(0x23800000+4*0x00)
#define VALVE_STATE_READ_REG1 	(0x23800000+4*0x01)
#define VALVE_STATE_READ_REG2 	(0x23800000+4*0x02)
#define VALVE_STATE_READ_REG3 	(0x23800000+4*0x03)
#define VALVE_STATE_READ_REG4 	(0x23800000+4*0x04)
#define VALVE_STATE_READ_REG5 	(0x23800000+4*0x05)
#define VALVE_STATE_READ_REG6 	(0x23800000+4*0x06)
#define VALVE_STATE_READ_REG7 	(0x23800000+4*0x07)
#define VALVE_STATE_READ_REG8 	(0x23800000+4*0x08)
#define VALVE_STATE_READ_REG9 	(0x23800000+4*0x09)
#define VALVE_STATE_READ_REG10 	(0x23800000+4*0x0a)
#define VALVE_STATE_READ_REG11 	(0x23800000+4*0x0b)		//����״̬��ȡ�ⲿ��ַ

#else
	
#define VALVE_STATE_READ_REG0 	0x24000000
#define VALVE_STATE_READ_REG1 	0x24000004
#define VALVE_STATE_READ_REG2 	0x24000008
#define VALVE_STATE_READ_REG3 	0x2400000c
#define VALVE_STATE_READ_REG4 	0x24000010
#define VALVE_STATE_READ_REG5 	0x24000014
#define VALVE_STATE_READ_REG6 	0x24000018
#define VALVE_STATE_READ_REG7 	0x2400001c
#define VALVE_STATE_READ_REG8 	0x24000020
#define VALVE_STATE_READ_REG9 	0x24000024
#define VALVE_STATE_READ_REG10 	0x24000028
#define VALVE_STATE_READ_REG11 	0x2400002c		//����״̬��ȡ�ⲿ��ַ

#endif

/*

#define VALVE_STATE_READ_REG0 	0x24000000
#define VALVE_STATE_READ_REG1 	0x24000004
#define VALVE_STATE_READ_REG2 	0x24000008
#define VALVE_STATE_READ_REG3 	0x2400000c
#define VALVE_STATE_READ_REG4 	0x24000010
#define VALVE_STATE_READ_REG5 	0x24000014
#define VALVE_STATE_READ_REG6 	0x24000018
#define VALVE_STATE_READ_REG7 	0x2400001c
#define VALVE_STATE_READ_REG8 	0x24000020
#define VALVE_STATE_READ_REG9 	0x24000024
#define VALVE_STATE_READ_REG10 	0x24000028
#define VALVE_STATE_READ_REG11 	0x2400002c		//����״̬��ȡ�ⲿ��ַ

*/

#define YK_ADDRESS_BASE 		0x23800000		//ң��OCָ��״̬�����䵽λ�źţ�24,25,26,27


#define BIT00					0x0001
#define BIT01					0x0002
#define BIT02					0x0004
#define BIT03					0x0008
#define BIT04					0x0010
#define BIT05					0x0020
#define BIT06					0x0040
#define BIT07					0x0080
#define BIT08					0x0100
#define BIT09					0x0200
#define BIT10					0x0400
#define BIT11					0x0800
#define BIT12					0x1000
#define BIT13					0x2000
#define BIT14					0x4000
#define BIT15					0x8000
#define BIT88					0xffff


#define WORD00					0x0000
#define WORD01					0x0001
#define WORD02					0x0002
#define WORD03					0x0003
#define WORD04					0x0004
#define WORD05					0x0005
#define WORD06					0x0006
#define WORD07					0x0007
#define WORD08					0x0008
#define WORD09					0x0009
#define WORD10					0x000a
#define WORD11					0x000b
#define WORD12					0x000c
#define WORD13					0x000d
#define WORD14					0x000e
#define WORD15					0x000f
#define WORD16					0x0010
#define WORD17					0x0011
#define WORD18					0x0012
#define WORD19					0x0013
#define WORD20					0x0014
#define WORD21					0x0015
#define WORD22					0x0016
#define WORD23					0x0017
#define WORD88					0xffff


/*
28: ��λ�ź�bit0~15:��1���䵽λ����1��2��3����2���䵽λ����1��2��3����3���䵽λ����1��2��3��ȼ1���䵽λ����1��2��3��
					ȼ2���䵽λ����1��2��3��ȼ3���䵽λ����1
29����λ�ź�bit0~1��ȼ3���䵽λ����2��3

30:bit0~15:	LVB7��0��LVB8��1��LVB9��2��LVB10��3��LVB11��4��LVB12��5��LVB39,41��6��LVB49,51��7��LVB59,61��8��
			LVB63,65��9��LVB40,42��10��LVB50,52��11��LVB60,62��12��LVB64,66��13��LVB13,15��14��LVB14,16��15��

31:bit0~15:	LVB23��0��LVB24��1��LVB21��2��LVB22��3��LVB87��4��LVB73,77��5��LVB73,71��6��LVB73,81��7��
			LVB73,85��8��LVB78,74��9��LVB72,74��10��LVB82,74��11��LVB86,74��12��LVB73,69��13��LVB70,74��14��
			���䵽λ��ֹ
			
32�����䵽λ����ʹ�ܽ�ֹ��־��bit0~5���ֱ�ΪO1��2��3��F1��2��3��λ����ʹ�ܻ��߽�ֹ
			
26��OC״̬����Ĵ�����д0xaaaa��ʾ���OC״̬

27:���䵽λʹ�ܣ�bit0~11���ֱ��ʾ01��O2��O3��F1��F2��F3���䵽λ�źŵ�ʹ�ܻ��߽�ֹ����
			д��11��ʾʹ�ܣ�д��00��ʾ��ֹ


*/

 
#define TANK_O1_POSITION	0x0101
#define TANK_O2_POSITION	0x0202
#define TANK_O3_POSITION	0x0303
#define TANK_F1_POSITION	0x0404
#define TANK_F2_POSITION	0x0505
#define TANK_F3_POSITION	0x0606



#define STATE_LVb01 0x00
#define STATE_LVb02 0x01
#define STATE_LVb03 0x02
#define STATE_LVb04 0x03
#define STATE_LVb05 0x04
#define STATE_LVb06 0x05
#define STATE_LVb07 0x06
#define STATE_LVb08 0x07
#define STATE_LVb09 0x08
#define STATE_LVb10 0x09
#define STATE_LVb11 0x0a
#define STATE_LVb12 0x0b
#define STATE_LVb13 0x0c
#define STATE_LVb14 0x0d
#define STATE_LVb15 0x0e
#define STATE_LVb16 0x0f
#define STATE_LVb17 0x10
#define STATE_LVb18 0x11
#define STATE_LVb19 0x12
#define STATE_LVb20 0x13
#define STATE_LVb21 0x14
#define STATE_LVb22 0x15
#define STATE_LVb23 0x16
#define STATE_LVb24 0x17
#define STATE_LVb25 0x18
#define STATE_LVb26 0x19
#define STATE_LVb27 0x1a
#define STATE_LVb28 0x1b
#define STATE_LVb29 0x1c
#define STATE_LVb30 0x1d
#define STATE_LVb31 0x1e
#define STATE_LVb32 0x1f
#define STATE_LVb33 0x20
#define STATE_LVb34 0x21
#define STATE_LVb35 0x22
#define STATE_LVb36 0x23
#define STATE_LVb37 0x24
#define STATE_LVb38 0x25
#define STATE_LVb39 0x26
#define STATE_LVb40 0x27
#define STATE_LVb41 0x28
#define STATE_LVb42 0x29
#define STATE_LVb43 0x2a
#define STATE_LVb44 0x2b
#define STATE_LVb45 0x2c
#define STATE_LVb46 0x2d
#define STATE_LVb47 0x2e
#define STATE_LVb48 0x2f
#define STATE_LVb49 0x30
#define STATE_LVb50 0x31
#define STATE_LVb51 0x32
#define STATE_LVb52 0x33
#define STATE_LVb53 0x34
#define STATE_LVb54 0x35
#define STATE_LVb55 0x36
#define STATE_LVb56 0x37
#define STATE_LVb57 0x38
#define STATE_LVb58 0x39
#define STATE_LVb59 0x3a
#define STATE_LVb60 0x3b
#define STATE_LVb61 0x3c
#define STATE_LVb62 0x3d
#define STATE_LVb63 0x3e
#define STATE_LVb64 0x3f
#define STATE_LVb65 0x40
#define STATE_LVb66 0x41
#define STATE_LVb67 0x42
#define STATE_LVb68 0x43
#define STATE_LVb69 0x44
#define STATE_LVb70 0x45
#define STATE_LVb71 0x46
#define STATE_LVb72 0x47
#define STATE_LVb73 0x48
#define STATE_LVb74 0x49
#define STATE_LVb75 0x4a
#define STATE_LVb76 0x4b
#define STATE_LVb77 0x4c
#define STATE_LVb78 0x4d
#define STATE_LVb79 0x4e
#define STATE_LVb80 0x4f
#define STATE_LVb81 0x50
#define STATE_LVb82 0x51
#define STATE_LVb83 0x52
#define STATE_LVb84 0x53
#define STATE_LVb85 0x54
#define STATE_LVb86 0x55
#define STATE_LVb87 0x56
#define STATE_DVb 0x57					//����״̬����


/*�豸����ָ��궨�壬���޸�-----------------------------------------------------*/
 #define LVt1K 0x00
 #define LVt1G 0x01
 #define LVt7K 0x02
 #define LVt7G 0x03
 #define LVt9K 0x04
 #define LVt9G 0x05
 #define LVt11K 0x06
 #define LVt11G 0x07
 #define LVt31K 0x08
 #define LVt31G 0x09
 #define LVt37K 0x0a
 #define LVt37G 0x0b
 #define LVt43K 0x0c
 #define LVt43G 0x0d
 #define LVt45K 0x0e
 #define LVt45G 0x0f
 #define LVt51K 0x10
 #define LVt51G 0x11
 #define LVt2K 0x12
 #define LVt2G 0x13
 #define LVt8K 0x14
 #define LVt8G 0x15
 #define LVt10K 0x16
 #define LVt10G 0x17
 #define LVt12K 0x18
 #define LVt12G 0x19
 #define LVt32K 0x1a
 #define LVt32G 0x1b
 #define LVt38K 0x1c
 #define LVt38G 0x1d
 #define LVt44K 0x1e
 #define LVt44G 0x1f
 #define LVt46K 0x20
 #define LVt46G 0x21
 #define LVt52K 0x22
 #define LVt52G 0x23
 #define LVt3K 0x24
 #define LVt3G 0x25
 #define LVt20K 0x26
 #define LVt20G 0x27
 #define LVt24K 0x28
 #define LVt24G 0x29
 #define LVt27K 0x2a
 #define LVt27G 0x2b
 #define LVt35K 0x2c
 #define LVt35G 0x2d
 #define LVt19K 0x2e
 #define LVt19G 0x2f
 #define LVt23K 0x30
 #define LVt23G 0x31
 #define LVt28K 0x32
 #define LVt28G 0x33
 #define LVt36K 0x34
 #define LVt36G 0x35		//��·����������
 #define LVt6K 0x36
 #define LVt6G 0x37
 #define LVt16K 0x38
 #define LVt16G 0x39
 #define LVt18K 0x3a
 #define LVt18G 0x3b
 #define LVt22K 0x3c
 #define LVt22G 0x3d
 #define LVt26K 0x3e
 #define LVt26G 0x3f
 #define LVt13K 0x40
 #define LVt13G 0x41
 #define LVt29K 0x42
 #define LVt29G 0x43
 #define LVt39K 0x44
 #define LVt39G 0x45
 #define LVt41K 0x46
 #define LVt41G 0x47
 #define LVt5K 0x48
 #define LVt5G 0x49
 #define LVt15K 0x4a
 #define LVt15G 0x4b
 #define LVt17K 0x4c
 #define LVt17G 0x4d
 #define LVt21K 0x4e
 #define LVt21G 0x4f
 #define LVt25K 0x50
 #define LVt25G 0x51
 #define LVt34K 0x52
 #define LVt34G 0x53
 #define LVt48K 0x54
 #define LVt48G 0x55
 #define LVt50K 0x56
 #define LVt50G 0x57
 #define LVt54K 0x58
 #define LVt54G 0x59
 #define LVt33K 0x5a
 #define LVt33G 0x5b
 #define LVt47K 0x5c
 #define LVt47G 0x5d
 #define LVt49K 0x5e
 #define LVt49G 0x5f
 #define LVt53K 0x60
 #define LVt53G 0x61
 #define LVt4K 0x62
 #define LVt4G 0x63
 #define LVt14K 0x64
 #define LVt14G 0x65
 #define LVt30K 0x66
 #define LVt30G 0x67
 #define LVt40K 0x68
 #define LVt40G 0x69
 #define LVt42K 0x6a
 #define LVt42G 0x6b		//��·����������
 
 #define TGTHT530a_ON_POWER 0x6c  		//���������a�ӵ�
 #define TGTHT530b_ON_POWER 0x6d		//���������b�ӵ�
 #define TGTHT530c_ON_POWER 0x6e		//���������c�ӵ�
 #define TGTHT530a_OFF_POWER 0x6f		//���������a�ϵ�
 #define TGTHT530b_OFF_POWER 0x70		//���������b�ϵ�
 #define TGTHT530c_OFF_POWER 0x71		//���������c�ϵ�
 #define COMPRESS_A_ON_POWER 0x72		//ѹ����A�ӵ�
 #define COMPRESS_B_ON_POWER 0x73		//ѹ����B�ӵ�
 #define COMPRESS_C_ON_POWER 0x74		//ѹ����C�ӵ�
 #define COMPRESS_A_OFF_POWER 0x75		//ѹ����A�ϵ�
 #define COMPRESS_B_OFF_POWER 0x76		//ѹ����B�ϵ�
 #define COMPRESS_C_OFF_POWER 0x77		//ѹ����C�ϵ�
 #define COMPRESS_A_START 0x78			//ѹ����A����
 #define COMPRESS_B_START 0x79			//ѹ����B����
 #define COMPRESS_C_START 0x7a			//ѹ����C����
 #define COMPRESS_A_STOP 0x7b			//ѹ����Aͣ��
 #define COMPRESS_B_STOP 0x7c			//ѹ����Bͣ��
 #define COMPRESS_C_STOP 0x7d			//ѹ����Cͣ��
 #define VALVE_SUPPLY_ON_POWER 0x7e		//���ӷ��żӵ�
 #define VALVE_SUPPLY_OFF_POWER 0x7f	//���ӷ��Ŷϵ�
 
 
/*�豸����ָ��궨�壬���޸�-----------------------------------------------------*/

 #define APID_TGTHT520a_VALVE_EQUIMENT_COMMAND 		0x0302//�豸����ָ��APID���ƽ�����������ָ��
 #define APID_TGTHT520b_VALVE_EQUIMENT_COMMAND 		0x0304//�豸����ָ��APID���ƽ�����������ָ��
 #define APID_TGTHT530_POWER_EQUIMENT_COMMAND 		0x00ef//�豸����ָ��APID������������Ӷϵ�ָ��
 #define APID_VALVE_POWER_EQUIMENT_COMMAND			0x00cc//�豸����ָ��APID������ϵͳ���żӶϵ�ָ��
 #define APID_COMPRESS_POWER_EQUIMENT_COMMAND		0x00ef//�豸����ָ��APID��ѹ�����Ӷϵ�ָ��
 #define APID_COMPRESS_START_STOP_EQUIMENT_COMMAND	0x0308//�豸����ָ��APID��ѹ��������ͣ��ָ��
 #define APID_ERROR									0xaa55//����APID����
 
 
 #define VCID_TGTHT520_A_EQUIMENT_COMMAND 		0x02//�豸����ָ������ͨ������·����������
 #define VCID_TGTHT520_B_EQUIMENT_COMMAND 		0x02//�豸����ָ������ͨ������·����������
 #define VCID_TGTHT530_A_EQUIMENT_COMMAND 		0x02//�豸����ָ������ͨ���������������A
 #define VCID_TGTHT530_B_EQUIMENT_COMMAND 		0x02//�豸����ָ������ͨ���������������B
 #define VCID_TGTHT530_C_EQUIMENT_COMMAND 		0x02//�豸����ָ������ͨ���������������C
 #define VCID_POWER_EQUIMENT_COMMAND			0x02//�豸����ָ������ͨ������Դ�����������޸ģ���������
 #define VCID_ERROR								0x02//����VCID����
 
 
 
 
 

/*��������--------------------------------------------------------------------*/

void TGTHT510_collectANDgroup_initial(void);
void TGTHT510_collectANDgroup_main(void);
void TGTHT510_collectANDgroup_heater_state_collect_save(void);
uint16 TGTHT510_collectANDgroup_is_heater_state(uint16 *p,uint16 sc_number);
void TGTHT510_collectANDgroup_valve_state_collect_save(void);
uint16 TGTHT510_collectANDgroup_is_valve_state(uint16 valve_number);
uint16 TGTHT510_collectANDgroup_EPDU_count_generate(uint16 count,uint16 mode);
uint8 TGTHT510_collectANDgroup_sum_generate(uint16 *p,uint16 number);
void TGTHT510_collectANDgroup_CG_group(void);
void TGTHT510_collectANDgroup_CG_data_generate(void);
void TGTHT510_collectANDgroup_GC_data_generate(void);
void TGTHT510_collectANDgroup_YB_data_generate(void);
void TGTHT510_collectANDgroup_GC_group(void);
void TGTHT510_collectANDgroup_YB_group(void);
void TGTHT510_collectANDgroup_GNC_group(void);
void TGTHT510_collectANDgroup_MEMORY_group(void);



void TGTHT510_collectANDgroup_ask_for_service_generate(uint16 mode);
void TGTHT510_collectANDgroup_equiment_command_generate(uint8 command);
equiment_command_EPDU_command_data_TypeDef TGTHT510_collectANDgroup_equiment_command_EPDU_command_generate(uint8 command);
equiment_command_EPDU_APID_VCID_TypeDef TGTHT510_collectANDgroup_equiment_command_APID_VCID_generate(uint8 command);
uint16 TGTHT510_collectANDgroup_equiment_command_ISO_generate(uint8 *p,uint16 size);
uint16 TGTHT510_collectANDgroup_Byte_CRC(uint16 CRC,uint8 inputdata);
uint16 TGTHT510_collectANDgroup_CRC_generate(uint16 *p,uint16 size);
void TGTHT510_collectANDgroup_HYCT_group(void);
void TGTHT510_collectANDgroup_yk_state_collect_save(void);

uint16 TGTHT510_collectANDgroup_combine(uint16 high,uint16 low);
void TGTHT510_tank_position_set(uint16 tank,uint16 flag);
void TGTHT510_collectANDgroup_CG_supply_group(void);






#endif 


