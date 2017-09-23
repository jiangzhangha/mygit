/**
  ******************************************************************************
  * @file    TGTHT510_1553b.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ�������1553B���ߴ���ģ��ͷ�ļ�
  ******************************************************************************
  */
 
 #ifndef __TGTHT510_1553b_h
 #define __TGTHT510_1553b_h
 

/*�����ṹ������---------------------------------------------------------*/


#ifdef TEST_VERSION

typedef struct				  //�ӵ�ַ״̬��־��ѯ�ṹ��
{
	uint32 Subaddress_05_flag;//���Լ�ʹ��
	uint32 Subaddress_11_flag;//�ӵ�ַ11�����ͳ���ң���빤��ң��
	uint32 Subaddress_12_flag;//�ӵ�ַ12�������豸����ָ��
	uint32 Subaddress_13_flag;//�ӵ�ַ13�������Ǳ���ʾң��
	uint32 Subaddress_17_flag;//�ӵ�ַ17������ת��ǰ������ڲ������� ��֡
	uint32 Subaddress_19_flag;//�ӵ�ַ19������תGNC�ʼ�״̬��
	uint32 Subaddress_21_flag;//�ӵ�ַ21�������ڴ��´�����
	uint32 Subaddress_23_flag;//�ӵ�ַ23�����͹��ϴ���
	uint32 Subaddress_28_flag;//�ӵ�ַ28�����ͷ�������
	uint32 Subaddress_14_flag;//�ӵ�ַ14������520��530��540��������
	uint32 Subaddress_15_flag;//�ӵ�ַ15����������ָ�����ֿ�ָ��
	uint32 Subaddress_16_flag;//�ӵ�ַ16������ע��ָ��
	uint32 Subaddress_18_flag;//�ӵ�ַ18�����ܻ������Ͳ�����Ϣ������ת����1��
	uint32 Subaddress_20_flag;//�ӵ�ַ20�����ܻ������Ͳ�����Ϣ������ת����2��
	uint32 Subaddress_22_flag;//�ӵ�ַ22�������ۺϵ��Ӳɼ����ƽ�����������
	uint32 Subaddress_29_flag;//�ӵ�ַ29����������ָ��
	uint8 Current_Stack_Pointer;
}TGTHT510_1553B_Subaddress_flag_TypeDef;

#else
	
typedef struct				  //�ӵ�ַ״̬��־��ѯ�ṹ��
{
	uint32 Subaddress_11_flag;//�ӵ�ַ11�����ͳ���ң���빤��ң��
	uint32 Subaddress_12_flag;//�ӵ�ַ12�������豸����ָ��
	uint32 Subaddress_13_flag;//�ӵ�ַ13�������Ǳ���ʾң��
	uint32 Subaddress_17_flag;//�ӵ�ַ17������ת��ǰ������ڲ������� ��֡
	uint32 Subaddress_19_flag;//�ӵ�ַ19������תGNC�ʼ�״̬��
	uint32 Subaddress_21_flag;//�ӵ�ַ21�������ڴ��´�����
	uint32 Subaddress_23_flag;//�ӵ�ַ23�����͹��ϴ���
	uint32 Subaddress_28_flag;//�ӵ�ַ28�����ͷ�������
	uint32 Subaddress_14_flag;//�ӵ�ַ14������520��530��540��������
	uint32 Subaddress_15_flag;//�ӵ�ַ15����������ָ�����ֿ�ָ��
	uint32 Subaddress_16_flag;//�ӵ�ַ16������ע��ָ��
	uint32 Subaddress_18_flag;//�ӵ�ַ18�����ܻ������Ͳ�����Ϣ������ת����1��
	uint32 Subaddress_20_flag;//�ӵ�ַ20�����ܻ������Ͳ�����Ϣ������ת����2��
	uint32 Subaddress_22_flag;//�ӵ�ַ22�������ۺϵ��Ӳɼ����ƽ�����������
	uint32 Subaddress_29_flag;//�ӵ�ַ29����������ָ��
	uint8 Current_Stack_Pointer;
}TGTHT510_1553B_Subaddress_flag_TypeDef;

#endif



typedef struct
{
	uint16 inputcommand_head_word1;			//ע��ң��֡����ͷ1��1��
	uint16 inputcommand_head_word2;			//ע��ң��֡����ͷ2��1��
	uint8  inputcommand_head_byte;			//ע��ң��֡���кţ�1�ֽ�
	uint16 inputcommand_data[415];			//ע��ң��֡���ݣ����829�ֽ�
	uint16 inputcommand_CRC;				//ע��ң��֡CRCУ���֣�1��
	uint16 inputcommand_length;				//ע��ң��֡֡����1��
	uint16 inputcommand_data_length;		//ע��ң��֡�����򳤶ȣ�1��
}TGTHT510_1553B_inputcommand_TypeDef;		//ע��ң��֡���ݸ�ʽ����


typedef struct
{
	uint16 CG_GC_message_count_Z;			//�����빤��ң��ͨѶ״̬����,����BU65170
	uint16 CG_GC_message_count_B;			//�����빤��ң��ͨѶ״̬����,����BU65170
	uint16 YB_message_count;				//�Ǳ�ң��ͨѶ״̬����
	uint16 HYCT1100_T_message_count;		//ת������ͨѶ״̬����
	uint16 TGTHT100_message_count;			//�����ƽ�ң����·��ͨѶ״̬����
	uint16 TGTHT520a_message_count;			//�����ƽ�����������A��ͨѶ״̬����
	uint16 TGTHT520b_message_count;			//�����ƽ�����������B��ͨѶ״̬����
	uint16 TGTHT530_message_count;			//����ѹ�������������ͨѶ״̬����
	uint16 HYCT1100_R_message_count;		//���ջ���������Ϣ����ͨѶ״̬����
	uint16 KPU_message_count;				//��������ң������ͨѶ״̬����
	
	uint16 TGTHT100_validity;				//�����ƽ�ң����·��������Ч�Ա�־
	uint16 TGTHT520a_validity;				//�����ƽ�����������A��������Ч�Ա�־
	uint16 TGTHT520b_validity;				//�����ƽ�����������B��������Ч�Ա�־
	uint16 TGTHT530_validity;				//����ѹ�����������������ͨѶ״̬����
	uint16 HYCT1100_validity;				//���ջ�����������ͨѶ״̬����
	uint16 KPU_validity;					//��������ң������ͨѶ״̬����
	
}TGTHT510_1553B_message_state_TypeDef;		//����ͨѶ״̬���ݸ�ʽ����


typedef struct
{
	uint16 count;
	uint16 last_use_BU65170;
}TGTHT510_which_bus_TypeDef;


typedef struct
{
	uint16 Subaddress_11_service_flag;
	uint16 Subaddress_12_service_flag;
	uint16 Subaddress_13_service_flag;
	uint16 Subaddress_17_service_flag;
	uint16 Subaddress_19_service_flag;
	uint16 Subaddress_21_service_flag;
	uint16 Subaddress_23_service_flag;
	uint16 Subaddress_28_service_flag;
	uint16 Subaddress_14_service_flag;
	uint16 Subaddress_15_service_flag;
	uint16 Subaddress_16_service_flag;
	uint16 Subaddress_18_service_flag;
	uint16 Subaddress_20_service_flag;
	uint16 Subaddress_22_service_flag;
	
}TGTHT510_1553B_service_flag_TypeDef;	//����ָ���־�ṹ�嶨��




//---------����BU65170���ݺ궨��-----------------------------------------------------------------


#define BU65170_Z_RESET_REG					(uint32)0x26007ff8				//��λ�Ĵ�����д0xAA55��Ч
#define	BU65170_Z_STATUS_REG				(uint32)0x26007ffc				//����״̬�Ĵ�����0x5555�ɲ������������ɲ���

#define BU65170_Z_T_RAM_BASE				(uint32)0x26000000				//����BU65170��������������ַ
#define BU65170_Z_R_RAM_BASE				(uint32)0x26004000				//����BU65170��������������ַ

#define BU65170_Z_T_CG_GC_BASE				(BU65170_Z_T_RAM_BASE+4*0x0400)	//���ݻ���ַ��RT11�����ͳ���ң���빤��ң��
#define BU65170_Z_T_COMMAND_EQUIP_BASE		(BU65170_Z_T_RAM_BASE+4*0x0500)	//���ݻ���ַ��RT12�������豸����ָ��
#define BU65170_Z_T_YB_BASE					(BU65170_Z_T_RAM_BASE+4*0x0520)	//���ݻ���ַ��RT13�������Ǳ�ң��
#define BU65170_Z_T_HYCT1100_BASE			(BU65170_Z_T_RAM_BASE+4*0x0540)	//���ݻ���ַ��RT17������ת��ǰ������ڲ�������
#define BU65170_Z_T_GNC_BASE				(BU65170_Z_T_RAM_BASE+4*0x05c0)	//���ݻ���ַ��RT19������תGNC�ʼ�״̬��
#define BU65170_Z_T_MEMORY_BASE				(BU65170_Z_T_RAM_BASE+4*0x0600)	//���ݻ���ַ��RT21�������ڴ��´�����


#define BU65170_Z_T_CODEFAULT_BASE			(BU65170_Z_T_RAM_BASE+4*0x0720)	//���ݻ���ַ��RT23�����͹��ϴ���
#define BU65170_Z_T_ASKFORSERIVE_BASE		(BU65170_Z_T_RAM_BASE+4*0x0760)	//���ݻ���ַ��RT28�����ͷ�������


#ifdef TEST_VERSION

#define BU65170_Z_T_TEST_FM_STATE_BASE		(BU65170_Z_T_RAM_BASE+4*0x0e00)	//���ݻ���ַ��RT05�����ͷ���״̬��Ϣ����
#define BU65170_Z_T_TEST_FM_STATE_POINTER	(BU65170_Z_T_RAM_BASE+4*0x0165)	//��ѯָ�룬RT05�����ͷ���״̬��Ϣ����

#endif

#define BU65170_Z_T_CG_GC_POINTER			(BU65170_Z_T_RAM_BASE+4*0x016b)	//��ѯָ�룬RT11�����ͳ���ң���빤��ң��
#define BU65170_Z_T_COMMAND_EQUIP_POINTER	(BU65170_Z_T_RAM_BASE+4*0x016c)	//��ѯָ�룬RT12�������豸����ָ��
#define BU65170_Z_T_YB_POINTER				(BU65170_Z_T_RAM_BASE+4*0x016d)	//��ѯָ�룬RT13�������Ǳ�ң��
#define BU65170_Z_T_HYCT1100_POINTER		(BU65170_Z_T_RAM_BASE+4*0x0171)	//��ѯָ�룬RT17�����ͻ���������Ϣң��
#define BU65170_Z_T_GNC_POINTER				(BU65170_Z_T_RAM_BASE+4*0x0173)	//��ѯָ�룬RT19������תGNC�ʼ�״̬��
#define BU65170_Z_T_MEMORY_POINTER			(BU65170_Z_T_RAM_BASE+4*0x0175)	//��ѯָ�룬RT21�������ڴ��´�����


#define BU65170_Z_T_CODEFAULT_POINTER		(BU65170_Z_T_RAM_BASE+4*0x0177)	//��ѯָ�룬RT23�����͹��ϴ���
#define BU65170_Z_T_ASKFORSERIVE_POINTER	(BU65170_Z_T_RAM_BASE+4*0x017c)	//��ѯָ�룬RT28�����ͷ�������

//----SRAM��-----------------------
#define BU65170_Z_R_TGTHT_BASE				(BU65170_Z_R_RAM_BASE+4*0x0203)	//���ݻ���ַ��RT14����������������·����ѹ��������203-402
#define BU65170_Z_R_BUS_COMMAND_BASE		(BU65170_Z_R_RAM_BASE+4*0x0403)	//���ݻ���ַ��RT15����������ָ������403-442
#define BU65170_Z_R_INPUT_COMMAND_BASE		(BU65170_Z_R_RAM_BASE+4*0x0443)	//���ݻ���ַ��RT16������ע��ָ������443-842
#define BU65170_Z_R_HYCT1100_DATA1_BASE		(BU65170_Z_R_RAM_BASE+4*0x0843)	//���ݻ���ַ��RT18�����ջ��˷ɴ���������843-902
#define BU65170_Z_R_HYCT1100_DATA2_BASE		(BU65170_Z_R_RAM_BASE+4*0x0903)	//���ݻ���ַ��RT20�����ջ��˷ɴ���������903-982


#define BU65170_Z_R_KPU_BASE				(BU65170_Z_R_RAM_BASE+4*0x0983)	//���ݻ���ַ��RT22����������ң������983-a02
#define BU65170_Z_R_INTER_COMMAND_BASE		(BU65170_Z_R_RAM_BASE+4*0x0a03)	//���ݻ���ַ��RT29����������ָ������a03-b02
#define BU65170_Z_R_MODE_CODE_BASE			(BU65170_Z_R_RAM_BASE+4*0x0b03)	//���ݻ���ַ��RT31�����շ�ʽ��������ac3-b02

#define BU65170_Z_R_STACK_DATA				(BU65170_Z_R_RAM_BASE+4*0x0000)	//��ջA����,0-200
#define BU65170_Z_R_STACK_POINTER			(BU65170_Z_R_RAM_BASE+4*0x0201)	//��ջAָ��201-202


//---------����BU65170���ݺ궨��-----------------------------------------------------------------


#define BU65170_B_RESET_REG					(uint32)0x26027ff8				//��λ�Ĵ�����д0xAA55��Ч
#define	BU65170_B_STATUS_REG				(uint32)0x26027ffc				//����״̬�Ĵ�����0x5555�ɲ������������ɲ���

#define BU65170_B_T_RAM_BASE				(uint32)0x26020000				//����BU65170��������������ַ
#define BU65170_B_R_RAM_BASE				(uint32)0x26024000				//����BU65170��������������ַ

#define BU65170_B_T_CG_GC_BASE				(BU65170_B_T_RAM_BASE+4*0x0400)	//���ݻ���ַ��RT11�����ͳ���ң���빤��ң��
#define BU65170_B_T_COMMAND_EQUIP_BASE		(BU65170_B_T_RAM_BASE+4*0x0500)	//���ݻ���ַ��RT12�������豸����ָ��
#define BU65170_B_T_YB_BASE					(BU65170_B_T_RAM_BASE+4*0x0520)	//���ݻ���ַ��RT13�������Ǳ�ң��
#define BU65170_B_T_HYCT1100_BASE			(BU65170_B_T_RAM_BASE+4*0x0540)	//���ݻ���ַ��RT17�����ͻ���������Ϣң��
#define BU65170_B_T_GNC_BASE				(BU65170_B_T_RAM_BASE+4*0x05c0)	//���ݻ���ַ��RT19������תGNC�ʼ�״̬��
#define BU65170_B_T_MEMORY_BASE				(BU65170_B_T_RAM_BASE+4*0x0600)	//���ݻ���ַ��RT21�������ڴ��´�����


#define BU65170_B_T_CODEFAULT_BASE			(BU65170_B_T_RAM_BASE+4*0x0720)	//���ݻ���ַ��RT23�����͹��ϴ���
#define BU65170_B_T_ASKFORSERIVE_BASE		(BU65170_B_T_RAM_BASE+4*0x0760)	//���ݻ���ַ��RT28�����ͷ�������

#ifdef TEST_VERSION

#define BU65170_B_T_TEST_FM_STATE_BASE		(BU65170_B_T_RAM_BASE+4*0x0e00)	//���ݻ���ַ��RT05�����ͷ���״̬��Ϣ����
#define BU65170_B_T_TEST_FM_STATE_POINTER	(BU65170_B_T_RAM_BASE+4*0x0165)	//��ѯָ�룬RT05�����ͷ���״̬��Ϣ����

#endif

#define BU65170_B_T_CG_GC_POINTER			(BU65170_B_T_RAM_BASE+4*0x016b)	//��ѯָ�룬RT11�����ͳ���ң���빤��ң��
#define BU65170_B_T_COMMAND_EQUIP_POINTER	(BU65170_B_T_RAM_BASE+4*0x016c)	//��ѯָ�룬RT12�������豸����ָ��
#define BU65170_B_T_YB_POINTER				(BU65170_B_T_RAM_BASE+4*0x016d)	//��ѯָ�룬RT13�������Ǳ�ң��
#define BU65170_B_T_HYCT1100_POINTER		(BU65170_B_T_RAM_BASE+4*0x0171)	//��ѯָ�룬RT17�����ͻ���������Ϣң��
#define BU65170_B_T_GNC_POINTER				(BU65170_B_T_RAM_BASE+4*0x0173)	//��ѯָ�룬RT19������תGNC�ʼ�״̬��!
#define BU65170_B_T_MEMORY_POINTER			(BU65170_B_T_RAM_BASE+4*0x0175)	//��ѯָ�룬RT21�������ڴ��´�����



#define BU65170_B_T_CODEFAULT_POINTER		(BU65170_B_T_RAM_BASE+4*0x0177)	//��ѯָ�룬RT23�����͹��ϴ���
#define BU65170_B_T_ASKFORSERIVE_POINTER	(BU65170_B_T_RAM_BASE+4*0x017c)	//��ѯָ�룬RT28�����ͷ�������


//----SRAM��-----------------------
#define BU65170_B_R_TGTHT_BASE				(BU65170_B_R_RAM_BASE+4*0x0203)	//���ݻ���ַ��RT14����������������·����ѹ��������203-402
#define BU65170_B_R_BUS_COMMAND_BASE		(BU65170_B_R_RAM_BASE+4*0x0403)	//���ݻ���ַ��RT15����������ָ������403-442
#define BU65170_B_R_INPUT_COMMAND_BASE		(BU65170_B_R_RAM_BASE+4*0x0443)	//���ݻ���ַ��RT16������ע��ָ������443-842
#define BU65170_B_R_HYCT1100_DATA1_BASE		(BU65170_B_R_RAM_BASE+4*0x0843)	//���ݻ���ַ��RT18�����ջ��˷ɴ���������843-902
#define BU65170_B_R_HYCT1100_DATA2_BASE		(BU65170_B_R_RAM_BASE+4*0x0903)	//���ݻ���ַ��RT18�����ջ��˷ɴ���������903-982


#define BU65170_B_R_KPU_BASE				(BU65170_B_R_RAM_BASE+4*0x0983)	//���ݻ���ַ��RT22����������ң������983-a02
#define BU65170_B_R_INTER_COMMAND_BASE		(BU65170_B_R_RAM_BASE+4*0x0a03)	//���ݻ���ַ��RT29����������ָ������a03-b02
#define BU65170_B_R_MODE_CODE_BASE			(BU65170_B_R_RAM_BASE+4*0x0b03)	//���ݻ���ַ��RT31�����շ�ʽ��������ac3-b02

#define BU65170_B_R_STACK_DATA				(BU65170_B_R_RAM_BASE+4*0x0000)	//��ջA����,0-200
#define BU65170_B_R_STACK_POINTER			(BU65170_B_R_RAM_BASE+4*0x0201)	//��ջAָ��201-202


//---------�������ݺ궨��---------------------------------------------------------------------
//#define BU65170_READ_ALLOW					0x0000
#define BU65170_READ_ALLOW					0x5555
#define BU65170_READ_NOT_ALLOW				0xaaaa

#define BU65170_Z							(uint16)0x1234					//����BU65170
#define BU65170_B							(uint16)0x4321					//����BU65170

#define BU65170_CG_GC_POINTER				0x0400
#define BU65170_YB_POINTER					0x0520
#define BU65170_TGTHT_POINTER				0x0800
#define BU65170_INPUT_COMMAND_POINTER		0x0a00
#define BU65170_HYCT1100_POINTER			0x0540
#define BU65170_ASKFORSERIVE_POINTER		0x0760
#define BU65170_COMMAND_EQUIP_POINTER		0x0500
#define BU65170_GNC_POINTER					0x05c0
#define BU65170_MEMORY_POINTER				0x0600
#define BU65170_HYCT_DATA1_POINTER			0x0c00
#define BU65170_HYCT_DATA2_POINTER			0x0c80



#define BU65170_R_STACK_DATA_LEN			0x0100							//��ջ����
#define BU65170_R_STACK_POINTER_LEN			0x0001							//��ջAָ�볤��

#define TYPE_SEND_HYCT_FORE					(uint16)0x1234 //��־������ת��ǰ��ڲ�������
#define TYPE_SEND_HYCT_BACK					(uint16)0x4321 //��־������ת������ڲ�������

#define TYPE_RECEIVE_HYCT_DATA1				(uint16)0x1234 //��־�����ܻ������Ͳ�����Ϣ������ת����1
#define TYPE_RECEIVE_HYCT_DATA2				(uint16)0x4321 //��־�����ܻ������Ͳ�����Ϣ������ת����2



/*�궨��----------------------------------------------------------------------*/

 
 #define TGTHT510_1553B_REG_BASE (uint32)0x26000000   						//1553B�Ĵ�������ַ
 #define TGTHT510_1553B_RAM_BASE (uint32)0x26010000							//1553B����������ַ
 
 #define TGTHT510_1553B_REG_InterruptMaskReg 					(TGTHT510_1553B_REG_BASE+4*0x00)
 #define TGTHT510_1553B_REG_ConfigurationReg1 					(TGTHT510_1553B_REG_BASE+4*0x01)
 #define TGTHT510_1553B_REG_ConfigurationReg2 					(TGTHT510_1553B_REG_BASE+4*0x02)
 #define TGTHT510_1553B_REG_StartResetReg 						(TGTHT510_1553B_REG_BASE+4*0x03)
 #define TGTHT510_1553B_REG_CommandStackPointerReg 				(TGTHT510_1553B_REG_BASE+4*0x03)
 #define TGTHT510_1553B_REG_RTSubaddressControlWordReg 			(TGTHT510_1553B_REG_BASE+4*0x04)
 #define TGTHT510_1553B_REG_TimeTagReg 							(TGTHT510_1553B_REG_BASE+4*0x05)
 #define TGTHT510_1553B_REG_InterruptStatusReg 					(TGTHT510_1553B_REG_BASE+4*0x06)
 #define TGTHT510_1553B_REG_ConfigurationReg3 					(TGTHT510_1553B_REG_BASE+4*0x07)
 #define TGTHT510_1553B_REG_ConfigurationReg4 					(TGTHT510_1553B_REG_BASE+4*0x08)
 #define TGTHT510_1553B_REG_ConfigurationReg5 					(TGTHT510_1553B_REG_BASE+4*0x09)
 #define TGTHT510_1553B_REG_DataStackAddressReg 				(TGTHT510_1553B_REG_BASE+4*0x0A)
 #define TGTHT510_1553B_REG_BCFrameTimeRemainingReg 			(TGTHT510_1553B_REG_BASE+4*0x0B)
 #define TGTHT510_1553B_REG_BCTimeRemainingToNextMessageReg 	(TGTHT510_1553B_REG_BASE+4*0x0C)
 #define TGTHT510_1553B_REG_RTLastCommandWord 					(TGTHT510_1553B_REG_BASE+4*0x0D)
 #define TGTHT510_1553B_REG_RTStatusWordReg 					(TGTHT510_1553B_REG_BASE+4*0x0E)
 #define TGTHT510_1553B_REG_RTBITWordReg 						(TGTHT510_1553B_REG_BASE+4*0x0F)

 #define TGTHT510_1553B_RAM_STACK_POINTER_A 					(TGTHT510_1553B_RAM_BASE+4*0x0100)	//RTָ���ջָ��A
 #define TGTHT510_1553B_RAM_LOOKUP_A_BASE 						(TGTHT510_1553B_RAM_BASE+4*0x0140)	//RT��ѯ��A����ַ
 #define TGTHT510_1553B_RAM_MODE_INTERRUPT_TABLE 				(TGTHT510_1553B_RAM_BASE+4*0x0108)	//��ʽָ��ѡ���жϱ����ַ
 
 #define TGTHT510_1553B_RAM_ILLEGAL_NONBROADCAST_TABLE			(TGTHT510_1553B_RAM_BASE+4*0x0380)	//�ǹ㲥���ա�������Ϣ�Ƿ������ַ
 #define TGTHT510_1553B_RAM_BUSY_TABLE							(TGTHT510_1553B_RAM_BASE+4*0x0240)	//æ�����ַ
 
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_LOOKUP			(TGTHT510_1553B_RAM_BASE+4*0x01A0)   //RT��ѯ���ӵ�ַ�����ֻ���ַ
 #define TGTHT510_1553B_RAM_RECEIVE_LOOKUP 						(TGTHT510_1553B_RAM_BASE+4*0x0140)	//RT��ѯ����ղ�ѯָ�����ַ
 #define TGTHT510_1553B_RAM_TRANSMIT_LOOKUP   					(TGTHT510_1553B_RAM_BASE+4*0x0160)	//RT��ѯ���Ͳ�ѯָ�����ַ
 #define TGTHT510_1553B_RAM_BROADCAST_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x0180)	//RT��ѯ��㲥��ѯָ�����ַ
 
 #define TGTHT510_1553B_RAM_RT11_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x016B)   //RT�ӵ�ַ11���Ͳ�ѯָ��
 #define TGTHT510_1553B_RAM_RT12_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x016C)   //RT�ӵ�ַ12���Ͳ�ѯָ��
 #define TGTHT510_1553B_RAM_RT13_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x016D)   //RT�ӵ�ַ13���Ͳ�ѯָ��
 #define TGTHT510_1553B_RAM_RT17_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x0171)   //RT�ӵ�ַ17���Ͳ�ѯָ��
 #define TGTHT510_1553B_RAM_RT23_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x0177)   //RT�ӵ�ַ23���Ͳ�ѯָ��
 #define TGTHT510_1553B_RAM_RT25_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x0179)   //RT�ӵ�ַ25���Ͳ�ѯָ��
 #define TGTHT510_1553B_RAM_RT28_TRANSMIT_LOOKUP 				(TGTHT510_1553B_RAM_BASE+4*0x017C)   //RT�ӵ�ַ28���Ͳ�ѯָ��

 #define TGTHT510_1553B_RAM_RT14_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x014E)	//RT�ӵ�ַ14���ղ�ѯָ��
 #define TGTHT510_1553B_RAM_RT15_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x014F)	//RT�ӵ�ַ15���ղ�ѯָ��
 #define TGTHT510_1553B_RAM_RT16_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x0150)	//RT�ӵ�ַ16���ղ�ѯָ��
 #define TGTHT510_1553B_RAM_RT18_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x0152)	//RT�ӵ�ַ18���ղ�ѯָ��
 #define TGTHT510_1553B_RAM_RT22_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x0156)	//RT�ӵ�ַ22���ղ�ѯָ��
 #define TGTHT510_1553B_RAM_RT29_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x015D)	//RT�ӵ�ַ29���ղ�ѯָ��
 #define TGTHT510_1553B_RAM_RT31_RECEIVE_LOOKUP 					(TGTHT510_1553B_RAM_BASE+4*0x015F)	//RT�ӵ�ַ31���ղ�ѯָ��
 
 
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT11				(TGTHT510_1553B_RAM_BASE+4*0x01AB)	//RT�ӵ�ַ11������
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT12				(TGTHT510_1553B_RAM_BASE+4*0x01AC)	//RT�ӵ�ַ12������
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT13				(TGTHT510_1553B_RAM_BASE+4*0x01AD)	//RT�ӵ�ַ13������
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT17				(TGTHT510_1553B_RAM_BASE+4*0x01B1)	//RT�ӵ�ַ17������
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT23				(TGTHT510_1553B_RAM_BASE+4*0x01B7)	//RT�ӵ�ַ23������
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT25				(TGTHT510_1553B_RAM_BASE+4*0x01B9)	//RT�ӵ�ַ25������
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT28				(TGTHT510_1553B_RAM_BASE+4*0x01BC)	//RT�ӵ�ַ28������
 
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT14				(TGTHT510_1553B_RAM_BASE+4*0x01AE)	//RT�ӵ�ַ14������
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT15				(TGTHT510_1553B_RAM_BASE+4*0x01AF)	//RT�ӵ�ַ15������
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT16				(TGTHT510_1553B_RAM_BASE+4*0x01B0)	//RT�ӵ�ַ16������
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT18				(TGTHT510_1553B_RAM_BASE+4*0x01B2)	//RT�ӵ�ַ18������
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT22				(TGTHT510_1553B_RAM_BASE+4*0x01B6)	//RT�ӵ�ַ22������
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT29				(TGTHT510_1553B_RAM_BASE+4*0x01BD)	//RT�ӵ�ַ29������
 #define TGTHT510_1553B_RAM_SUBADD_CONTROL_WORD_RT31				(TGTHT510_1553B_RAM_BASE+4*0x01BF)	//RT�ӵ�ַ31������
 
 /*����ָ�����ַ�����޸�-----------------------------------------------------*/
#define TGTHT510_1553B_RAM_TRANSMIT_CG_GC_BASE 				0x0400						//�����빤��ң�����ݻ���ַ��RT11
#define TGTHT510_1553B_RAM_TRANSMIT_COMMAND_EQUIP_BASE  	0x0540						//�豸�����ָ�����ַ��RT12
#define TGTHT510_1553B_RAM_TRANSMIT_YB_BASE 				0x05A0						//�Ǳ�ң�����ݻ���ַ��RT13
#define TGTHT510_1553B_RAM_TRANSMIT_HYCT1100_BASE			0x0C00						//�ͻ���ң�����ݻ���ַ��RT17
#define TGTHT510_1553B_RAM_TRANSMIT_CODEFAULT_BASE         	0x0600						//�ƽ����ϴ������ַ��RT23
#define TGTHT510_1553B_RAM_TRANSMIT_TGTHT510_BASE			0x0DC0						//���ƽ�����������ң�����ݻ���ַ��RT25
#define TGTHT510_1553B_RAM_TRANSMIT_ASKFORSERIVE_BASE     	0x0660                 		//�����������ݻ���ַ��RT28

#define TGTHT510_1553B_RAM_RECEIVE_FROM_TGTHT_BASE			0x0700						//����ң����·�С�ѹ������������ң�⣬RT14
#define TGTHT510_1553B_RAM_RECEIVE_BUS_COMMAND_BASE			0x0840						//�����������ֿ�ָ�RT15
#define TGTHT510_1553B_RAM_RECEIVE_INPUT_COMMAND_BASE 		0x08A0						//����ע��ָ�RT16
#define TGTHT510_1553B_RAM_RECEIVE_FROM_HYCT1100_BASE		0x0C80						//���ջ��˷ɴ��������ݣ�RT18
#define TGTHT510_1553B_RAM_RECEIVE_FROM_KPU_BASE			0x0D00						//��������ң�����ݣ�RT22
#define TGTHT510_1553B_RAM_RECEIVE_INTERACTIVE_COMMAND_BASE	0x0AE0						//��������ָ�����ݣ�RT29
#define TGTHT510_1553B_RAM_RECEIVE_MODE_CODE_BASE			0x0BA0						//���շ�ʽ���룬RT31
 
 /*RT�ӵ�ַ�����֣����޸�-----------------------------------------------------*/
 
#define T_SUBADD_CONTROL_WORD_RT11						0x0800//���ͳ���ң���빤��ң�⣬ѭ������ģʽ��256��
#define T_SUBADD_CONTROL_WORD_RT12						0x0000//�����豸����ָ�����Ϣģʽ
#define T_SUBADD_CONTROL_WORD_RT13						0x0000//�����Ǳ�ң�⣬����Ϣģʽ
#define T_SUBADD_CONTROL_WORD_RT17						0x0000//���ͻ���ң�����ݣ�����������
#define T_SUBADD_CONTROL_WORD_RT23						0x0000//�����ƽ����ϴ��룬����Ϣģʽ
#define T_SUBADD_CONTROL_WORD_RT25						0x0000//���͹�����B��ң�⣬����������
#define T_SUBADD_CONTROL_WORD_RT28						0x0000//���ͷ������󣬵���Ϣģʽ

#define R_SUBADD_CONTROL_WORD_RT14						0x0040//����ң����·�С�ѹ������������ң�⣬ѭ������ģʽ��256��
#define R_SUBADD_CONTROL_WORD_RT15						0x0000//�����������ֿ�ָ�����Ϣģʽ
#define R_SUBADD_CONTROL_WORD_RT16						0x0060//����ע��ָ�ѭ������ģʽ��512��
#define R_SUBADD_CONTROL_WORD_RT18						0x0000//���ջ����������ݣ�����������
#define R_SUBADD_CONTROL_WORD_RT22						0x0000//��������ң�����ݣ�����������
#define R_SUBADD_CONTROL_WORD_RT29						0x0020//��������ָ�ѭ������ģʽ��128��
#define R_SUBADD_CONTROL_WORD_RT31						0x0000//���շ�ʽ���룬����Ϣģʽ

/*APID���壬���޸�-----------------------------------------------------*/
#define T_APID_CG 					0x0300//APID���ͳ���ң��
#define T_APID_GC					0x0301//APID���͹���ң��
#define T_APID_YB					0x0302//APID�����Ǳ�ң��
#define T_APID_HYCT_FORE			0x0016//APID����ת��ǰ��ڲ�������
#define T_APID_HYCT_BACK			0x0016//APID����ת������ڲ�������
#define T_APID_GNC					0x0306//APID����ת��GNC�ʼ�״̬��
#define T_APID_MEMORY				0x0307//APID�����ڴ��´�����
#define T_APID_CODEFAULT			0x0304//APID���͹��ϴ���

#define R_APID_TGTHT100				0x0306//APID�����ƽ�ң����·��ң��
#define R_APID_TGTHT530				0x0306//APID����ѹ�������������ң��
#define R_APID_TGTHT520a			0x0306//APID�����ƽ���������������ң��
#define R_APID_TGTHT520b			0x0306//APID�����ƽ���������������ң��
#define R_APID_HYCT_DATA1			0x0308//APID���ջ������͵Ĳ���״̬��Ϣ������ת����1��
#define R_APID_HYCT_DATA2			0x0308//APID���ջ������͵Ĳ���״̬��Ϣ������ת����2��
#define R_APID_KPU					0x0306//APID�����ۺϵ��Ӳɼ����ƽ�����������

 /*����ͷ���壬���޸�-----------------------------------------------------*/
 
#define T_SUBSERVICE_CG 			0x0100//����ͷ�����ͳ���ң��
#define T_SUBSERVICE_GC				0x0100//����ͷ�����͹���ң��
#define T_SUBSERVICE_YB				0x0100//����ͷ�������Ǳ�ң��
#define T_SUBSERVICE_HYCT_FORE		0x0167//����ͷ������ת��ǰ��ڲ�������
#define T_SUBSERVICE_HYCT_BACK		0x0168//����ͷ������ת������ڲ�������
#define T_SUBSERVICE_GNC			0x1060//����ͷ������ת��GNC�ʼ�״̬��
#define T_SUBSERVICE_MEMORY			0x0100//����ͷ�������ڴ��´�����
#define T_SUBSERVICE_CODEFAULT		0x0100//����ͷ�����͹��ϴ���

#define R_SUBSERVICE_TGTHT100_A		0x0160//����ͷ�������ƽ�ң����·��ң��
#define R_SUBSERVICE_TGTHT100_B		0x0166//����ͷ�������ƽ�ң����·��ң��

#define R_SUBSERVICE_TGTHT530		0x0165//����ͷ������ѹ�������������ң��
#define R_SUBSERVICE_TGTHT520a		0x0163//����ͷ�������ƽ���������������ң��
#define R_SUBSERVICE_TGTHT520b		0x0161//����ͷ�������ƽ���������������ң��
#define R_SUBSERVICE_HYCT_DATA1		0x0100//����ͷ�����ջ������͵Ĳ���״̬��Ϣ������ת����1��
#define R_SUBSERVICE_HYCT_DATA2		0x0101//����ͷ�����ջ������͵Ĳ���״̬��Ϣ������ת����2��
#define R_SUBSERVICE_KPU			0x0100//����ͷ�������ۺϵ��Ӳɼ����ƽ�����������

 /*Դ�����ȶ��壬���޸�--------------------------------------------------------*/
 
 #define EPDU_LENGTH_TGTHT100		0x009f//�ƽ�ң����·��EPDUԴ�����ȣ�159��
 #define EPDU_LENGTH_TGTHT530		0x001f//���������EPDUԴ�����ȣ�32��
 #define EPDU_LENGTH_TGTHT520A		0x000c//�ƽ�������������·EPDUԴ�����ȣ�12��
 #define EPDU_LENGTH_TGTHT520B		0x000c//�ƽ�������������·EPDUԴ�����ȣ�12��
 #define EPDU_LENGTH_ERROR			0xefef//EPDUԴ�����ȴ���
 
 /*EPDUԴ�����ͣ����޸�--------------------------------------------------------*/
 #define EPDU_TYPE_TGTHT100A 			0x0101//�ƽ�ң����·��EPDUԴ����֡A
 #define EPDU_TYPE_TGTHT100B 			0x0202//�ƽ�ң����·��EPDUԴ����֡B
 #define EPDU_TYPE_TGTHT530 			0x0303//���������EPDUԴ��
 #define EPDU_TYPE_TGTHT520A 			0x0404//�ƽ�������������·EPDUԴ��
 #define EPDU_TYPE_TGTHT520B 			0x0505//�ƽ�������������·EPDUԴ��
 #define EPDU_TYPE_ERROR				0x0606//EPDUԴ�����ʹ���
 
 /*ע��ָ�����ͣ����޸�--------------------------------------------------------*/
 #define INPUT_COMMAND_TYPE_POWER				0x0101//�޸ķ�ֵ����
 #define INPUT_COMMAND_TYPE_MULTI_CONTR_SPOT	0x0202//�޸Ķ�����»�·�Ŀ��µ�
 #define INPUT_COMMAND_TYPE_ALL_CONTR_SPOT		0x0303//�޸�ȫ�����»�·�Ŀ��µ�
 #define INPUT_COMMAND_TYPE_ONE_MEA_SPOT		0x0404//�޸�ĳһ���»�·�Ŀ��²��
 #define INPUT_COMMAND_TYPE_ONE_FIXED			0x0505//ָ��ĳһ���»�·����ָ��ռ�ձ����
 #define INPUT_COMMAND_TYPE_ALL_RESUME			0x0606//�ָ����п��»�·����״̬
 #define INPUT_COMMAND_TYPE_SOURCE				0x0707//ָ�����²�����Դѡ��
 #define INPUT_COMMAND_TYPE_PLACE_SIGNAL_EN		0x0808//ָ��ĳһ·���䵽λ�ź�ʹ��
 #define INPUT_COMMAND_TYPE_PLACE_SIGNAL_DIS	0x0909//ָ��ĳһ·���䵽λ�źŽ�ֹ
 #define INPUT_COMMAND_TYPE_FAULT_EN			0x0a0a//ָ��ĳһ·�ʼ�ʹ��
 #define INPUT_COMMAND_TYPE_FAULT_DIS			0x0b0b//ָ��ĳһ·�ʼ��ֹ
 #define INPUT_COMMAND_TYPE_SUPPLY_STAGE		0x0c0c//���ӽ׶�ע��
 #define INPUT_COMMAND_TYPE_SUPPLY_PARA			0x0d0d//���Ӳ���ע��
 #define INPUT_COMMAND_TYPE_EXHAUST				0x0e0e//ע���©�����ŷ�ʱ��
 #define INPUT_COMMAND_TYPE_MAX_COMP			0x0f0f//ע��������ʱ��
 #define INPUT_COMMAND_TYPE_MAX_VELOCITY		0x1010//ע����󲹼�����
 #define INPUT_COMMAND_TYPE_MIN_VELOCITY		0x1111//ע����С��������
 #define INPUT_COMMAND_TYPE_MAX_FLOW			0x1212//ע����󲹼�����ʱ��
 #define INPUT_COMMAND_TYPE_TEMP_CONTR_MODE		0x1313//ע�벹�ӹ�·�¶ȿ���ģʽ
 #define INPUT_COMMAND_TYPE_COMP_START_MIN		0x1414//ע��ѹ���������¶�����
 #define INPUT_COMMAND_TYPE_COMP_START_MAX		0x1515//ע��ѹ���������¶�����
 #define INPUT_COMMAND_TYPE_COMP_ALARM			0x1616//ע��ѹ���������¶���ֵ
 #define INPUT_COMMAND_TYPE_COM_COOLER			0x1717//ע��ѹ������Һ���¶Ȳ�ֵ
 #define INPUT_COMMAND_TYPE_COMP_PRESSURE		0x1818//ע��ѹ������������ѹ��
 #define INPUT_COMMAND_TYPE_COMP_STOP_PRE		0x1919//ע��ѹ����ͣ�������ѹ��ֵ
 #define INPUT_COMMAND_TYPE_DP_HIGH				0x1a1a//ע���ѹѹ���仯��ֵ
 #define INPUT_COMMAND_TYPE_DP1_LOW				0x1b1b//ע���ѹѹ���仯��ֵ1
 #define INPUT_COMMAND_TYPE_DP2_LOW				0x1c1c//ע���ѹѹ���仯��ֵ2
 #define INPUT_COMMAND_TYPE_MAX_REPRESS			0x1d1d//ע�����ѹʱ��
 #define INPUT_COMMAND_TYPE_COMP_START_SPEED	0x1e1e//ע��ѹ��������ת��
 #define INPUT_COMMAND_TYPE_COMP_STOP_SPEED		0x1f1f//ע��ѹ����ͣ��ת��
 #define INPUT_COMMAND_TYPE_DELAY_SHORT			0x2020//ע���޸Ķ���ʱ
 #define INPUT_COMMAND_TYPE_DELAY_LONG			0x2121//ע���޸ĳ���ʱ
 #define INPUT_COMMAND_TYPE_BYPATH_TIME			0x2222//ע���޸���·������ʱ��
 #define INPUT_COMMAND_TYPE_EPS1				0x2323//ע���޸�ƫ��eps1
 #define INPUT_COMMAND_TYPE_EPS2				0x2424//ע���޸�ƫ��eps2
 #define INPUT_COMMAND_TYPE_IN_COMP_MAX			0x2525//ע���޸�ѹ����������ѹ��
 #define INPUT_COMMAND_TYPE_IN_COMP_MIN			0x2626//ע���޸�ѹ������С����ѹ��
 #define INPUT_COMMAND_TYPE_OUT_COMP_MIN		0x2727//ע���޸�ѹ������С����ѹ��
 #define INPUT_COMMAND_TYPE_HYCT				0x2828//ע���޸Ļ������ѹѹ��
 #define INPUT_COMMAND_TYPE_SENSOR_PIPE_F		0x2929//ע���޸�ȼ����Һ·ѹ���������趨
 #define INPUT_COMMAND_TYPE_SENSOR_PIPE_O		0x2a2a//ע���޸�������Һ·ѹ���������趨
 #define INPUT_COMMAND_TYPE_SENSOR_TANK_F		0x2b2b//ע���޸�ȼ����ѹ���������趨
 #define INPUT_COMMAND_TYPE_SENSOR_TANK_O		0x2c2c//ע���޸�������ѹ���������趨
 #define INPUT_COMMAND_TYPE_SENSOR_IN_COMP		0x2d2d//ע���޸�ѹ��������ѹ���������趨
 #define INPUT_COMMAND_TYPE_SENSOR_LOW_PIPE		0x2e2e//ע���޸ĵ�ѹ��·ѹ���������趨
 #define INPUT_COMMAND_TYPE_SUPPLY_CONTINUE_G	0x2f2f//ע��ָ�����Ӳ����������
 #define INPUT_COMMAND_TYPE_AUTO_RESUME			0x3030//�ָ�ĳһ���»�·Ϊ�Զ�����״̬
 #define INPUT_COMMAND_TYPE_EQU_COMMAND			0x3131//ע���豸����ָ��
 #define INPUT_COMMAND_TYPE_HEAT_ON				0x3232//ע�������ָͨ��
 
 #define INPUT_COMMAND_TYPE_SUPPLY_PAUSE		0x3333//ע�벹����ָͣ��
 #define INPUT_COMMAND_TYPE_SUPPLY_BREAK		0x3434//ע�벹����ָֹ��
 #define INPUT_COMMAND_TYPE_SUPPLY_CONTINUE		0x3535//ע�벹�Ӽ���ָ��

 #define INPUT_COMMAND_TYPE_CPU_SET				0x3636//ע��CPU״̬��λָ��
 #define INPUT_COMMAND_TYPE_SUPPLY_LEAK			0x3737//ע���©����ָ��
 #define INPUT_COMMAND_TYPE_STAGE_FAULT			0x3838//ע��׶ιʼ�״̬����
 
 #define INPUT_COMMAND_TYPE_COMPRESSOR_FLAG		0x3939//ע��ѹ����ʹ�ñ�־������ָ��


 
 #define INPUT_COMMAND_TYPE_ERROR				0xefff//ע��ָ�����ͷǷ�

 
/*ע��ָ��ȣ���EPDU��ȫ�����ȣ���λΪ��-----------------------------------------------*/
 
 #define INPUT_COMMAND_LEN_POWER				0x0007//�޸ķ�ֵ����
 //#define INPUT_COMMAND_LEN_MULTI_CONTR_SPOT		0x0202//�޸Ķ�����»�·�Ŀ��µ�
 #define INPUT_COMMAND_LEN_ALL_CONTR_SPOT		0x0009//�޸�ȫ�����»�·�Ŀ��µ�
 #define INPUT_COMMAND_LEN_ONE_MEA_SPOT			0x000e//�޸�ĳһ���»�·�Ŀ��²��
 #define INPUT_COMMAND_LEN_ONE_FIXED			0x0008//ָ��ĳһ���»�·����ָ��ռ�ձ����
 #define INPUT_COMMAND_LEN_ALL_RESUME			0x0007//�ָ����п��»�·����״̬
 #define INPUT_COMMAND_LEN_SOURCE				0x0007//ָ�����²�����Դѡ��
 #define INPUT_COMMAND_LEN_PLACE_SIGNAL_EN		0x0007//ָ��ĳһ·���䵽λ�ź�ʹ��
 #define INPUT_COMMAND_LEN_PLACE_SIGNAL_DIS		0x0007//ָ��ĳһ·���䵽λ�źŽ�ֹ
 #define INPUT_COMMAND_LEN_FAULT_EN				0x0007//ָ��ĳһ·�ʼ�ʹ��
 #define INPUT_COMMAND_LEN_FAULT_DIS			0x0007//ָ��ĳһ·�ʼ��ֹ
 #define INPUT_COMMAND_LEN_SUPPLY_STAGE			0x0007//���ӽ׶�ע��
 #define INPUT_COMMAND_LEN_SUPPLY_PARA			0x0026//���Ӳ���ע��
 #define INPUT_COMMAND_LEN_EXHAUST				0x0007//ע���©�����ŷ�ʱ��
 #define INPUT_COMMAND_LEN_MAX_COMP				0x0008//ע��������ʱ��
 #define INPUT_COMMAND_LEN_MAX_VELOCITY			0x0007//ע����󲹼�����
 #define INPUT_COMMAND_LEN_MIN_VELOCITY			0x0007//ע����С��������
 #define INPUT_COMMAND_LEN_MAX_FLOW				0x0007//ע����󲹼�����ʱ��
 #define INPUT_COMMAND_LEN_TEMP_CONTR_MODE		0x0007//ע�벹�ӹ�·�¶ȿ���ģʽ
 #define INPUT_COMMAND_LEN_COMP_START_MIN		0x0007//ע��ѹ���������¶�����
 #define INPUT_COMMAND_LEN_COMP_START_MAX		0x0007//ע��ѹ���������¶�����
 #define INPUT_COMMAND_LEN_COMP_ALARM			0x0007//ע��ѹ���������¶���ֵ
 #define INPUT_COMMAND_LEN_COM_COOLER			0x0007//ע��ѹ������Һ���¶Ȳ�ֵ
 #define INPUT_COMMAND_LEN_COMP_PRESSURE		0x0007//ע��ѹ������������ѹ��
 #define INPUT_COMMAND_LEN_COMP_STOP_PRE		0x0007//ע��ѹ����ͣ�������ѹ��ֵ
 #define INPUT_COMMAND_LEN_DP_HIGH				0x0007//ע���ѹѹ���仯��ֵ
 #define INPUT_COMMAND_LEN_DP1_LOW				0x0007//ע���ѹѹ���仯��ֵ1
 #define INPUT_COMMAND_LEN_DP2_LOW				0x0007//ע���ѹѹ���仯��ֵ2
 #define INPUT_COMMAND_LEN_MAX_REPRESS			0x0007//ע�����ѹʱ��
 #define INPUT_COMMAND_LEN_COMP_START_SPEED		0x0007//ע��ѹ��������ת��
 #define INPUT_COMMAND_LEN_COMP_STOP_SPEED		0x0007//ע��ѹ����ͣ��ת��
 #define INPUT_COMMAND_LEN_DELAY_SHORT			0x0007//ע���޸Ķ���ʱ
 #define INPUT_COMMAND_LEN_DELAY_LONG			0x0007//ע���޸ĳ���ʱ
 #define INPUT_COMMAND_LEN_BYPATH_TIME			0x0007//ע���޸���·������ʱ��
 #define INPUT_COMMAND_LEN_EPS1					0x0007//ע���޸�ƫ��eps1
 #define INPUT_COMMAND_LEN_EPS2					0x0007//ע���޸�ƫ��eps2
 #define INPUT_COMMAND_LEN_IN_COMP_MAX			0x0007//ע���޸�ѹ����������ѹ��
 #define INPUT_COMMAND_LEN_IN_COMP_MIN			0x0007//ע���޸�ѹ������С����ѹ��
 #define INPUT_COMMAND_LEN_OUT_COMP_MIN			0x0007//ע���޸�ѹ������С����ѹ��
 #define INPUT_COMMAND_LEN_HYCT					0x0007//ע���޸Ļ������ѹѹ��
 #define INPUT_COMMAND_LEN_SENSOR_PIPE_F		0x0007//ע���޸�ȼ����Һ·ѹ���������趨
 #define INPUT_COMMAND_LEN_SENSOR_PIPE_O		0x0007//ע���޸�������Һ·ѹ���������趨
 #define INPUT_COMMAND_LEN_SENSOR_TANK_F		0x0007//ע���޸�ȼ����ѹ���������趨
 #define INPUT_COMMAND_LEN_SENSOR_TANK_O		0x0007//ע���޸�������ѹ���������趨
 #define INPUT_COMMAND_LEN_SENSOR_IN_COMP		0x0007//ע���޸�ѹ��������ѹ���������趨
 #define INPUT_COMMAND_LEN_SENSOR_LOW_PIPE		0x0007//ע���޸ĵ�ѹ��·ѹ���������趨
 #define INPUT_COMMAND_LEN_SUPPLY_CONTINUE_G	0x0008//ע��ָ�����Ӳ����������
 #define INPUT_COMMAND_LEN_AUTO_RESUME			0x0007//�ָ�ĳһ���»�·Ϊ�Զ�����״̬
 #define INPUT_COMMAND_LEN_EQU_COMMAND			0x0007//ע���豸����ָ��
 #define INPUT_COMMAND_LEN_HEAT_ON				0x0007//ע�������ָͨ��
 
 #define INPUT_COMMAND_LEN_SUPPLY_PAUSE			0x0007//ע�벹����ָͣ��
 #define INPUT_COMMAND_LEN_SUPPLY_BREAK			0x0007//ע�벹����ָֹ��
 #define INPUT_COMMAND_LEN_SUPPLY_CONTINUE		0x0007//ע�벹�Ӽ���ָ��
 
 #define INPUT_COMMAND_LEN_CPU_SET				0x0007//ע��CPU״̬��λָ��
 #define INPUT_COMMAND_LEN_SUPPLY_LEAK			0x0007//ע���©����ָ��
 #define INPUT_COMMAND_LEN_STAGE_FAULT			0x0007//ע��׶ιʼ�״̬����
 
 #define INPUT_COMMAND_LEN_COMPRESSOR_FLAG		0x0007//ע��ѹ����ʹ�ñ�־������ָ��

 
 #define INPUT_COMMAND_LEN_UNKNOW				0xdfff//ע��ָ�����ͷǷ�
 

/*ע��ָ���ң��״̬ �궨��--------------------------------------------------------*/

 #define INPUT_COMMAND_EPDU_NUM_ERROR			0xaaaa
 #define INPUT_COMMAND_EPDU_DEAL_ERROR			0xbbbb
 
 
/*����ָ��̵������������޸�--------------------------------------------------------*/
 
 #define BUS_RELAY_BASE_ADDRESS					(uint32)0x25800000
 
 #define BUS_RELAY_HEATER_ON_BASE_ADDRESS		(uint32)0x25800004
 
 #define BUS_MAIN_HEATER_POWER_ON				0xe1e1//�ƽ����ݼ���������ͨ
 #define BUS_MAIN_HEATER_POWER_OFF				0xe2e2//�ƽ����ݼ����������
 #define BUS_LESS_HEATER_POWER_ON				0xe3e3//�ƽ����ݼ���������ͨ
 #define BUS_LESS_HEATER_POWER_OFF				0xe4e4//�ƽ����ݼ����������
 
 #define BUS_COOLER_1_MAIN_POWER_ON				0xe5e5//Һ��ģ��I���ù���ͨ
 #define BUS_COOLER_1_LESS_POWER_ON				0xe6e6//Һ��ģ��I���ù���ͨ
 #define BUS_COOLER_1_POWER_OFF					0xe7e7//Һ��ģ��I�������ù����
 #define BUS_COOLER_2_MAIN_POWER_ON				0xe8e8//Һ��ģ��II���ù���ͨ
 #define BUS_COOLER_2_LESS_POWER_ON				0xe9e9//Һ��ģ��II���ù���ͨ
 #define BUS_COOLER_2_POWER_OFF					0xeaea//Һ��ģ��II�������ù����
 
 //-----------------------------------����--------------------------------------------------
 #define BUS_MAIN_HEATER_POWER_OFF_AND			0xbfff//�ƽ����ݼ���������ϣ���������
 #define BUS_MAIN_HEATER_POWER_OFF_OR			0x8000//�ƽ����ݼ���������ϣ���������
 //bit15Ϊ1��bit14Ϊ0
 
 #define BUS_MAIN_HEATER_POWER_ON_AND			0xbfff//�ƽ����ݼ���������ͨ����������
 #define BUS_MAIN_HEATER_POWER_ON_OR			0x8000//�ƽ����ݼ���������ͨ����������
 //bit15Ϊ1��bit14Ϊ0
 
 #define BUS_LESS_HEATER_POWER_OFF_AND			0xffbf//�ƽ����ݼ���������ϣ���������
 #define BUS_LESS_HEATER_POWER_OFF_OR			0x0080//�ƽ����ݼ���������ϣ���������
 //bit7Ϊ1��bit6Ϊ0
 
 #define BUS_LESS_HEATER_POWER_ON_AND			0xefff//�ƽ����ݼ���������ͨ����������
 #define BUS_LESS_HEATER_POWER_ON_OR			0x2000//�ƽ����ݼ���������ͨ����������
 //bit13Ϊ1��bit12Ϊ0
 
 #define BUS_COOLER_1_MAIN_POWER_ON_AND			0xefff//Һ��ģ��I���ù���ͨ����������
 #define BUS_COOLER_1_MAIN_POWER_ON_OR			0x2000//Һ��ģ��I���ù���ͨ����������
 //bit13Ϊ1��bit12Ϊ0
 
 #define BUS_COOLER_1_LESS_POWER_ON_AND			0xfbff//Һ��ģ��I���ù���ͨ����������
 #define BUS_COOLER_1_LESS_POWER_ON_OR			0x0800//Һ��ģ��I���ù���ͨ����������
 //bit11Ϊ1��bit10Ϊ0
 
 #define BUS_COOLER_1_POWER_OFF_AND				0xfeff//Һ��ģ��I�������ù���ϣ���������
 #define BUS_COOLER_1_POWER_OFF_OR				0x0200//Һ��ģ��I�������ù���ϣ���������
 //bit9Ϊ1��bit8Ϊ0
 
 #define BUS_COOLER_2_MAIN_POWER_ON_AND			0xffef//Һ��ģ��II���ù���ͨ����������
 #define BUS_COOLER_2_MAIN_POWER_ON_OR			0x0020//Һ��ģ��II���ù���ͨ����������
 //bit5Ϊ1��bit4Ϊ0
 
 #define BUS_COOLER_2_LESS_POWER_ON_AND			0xfffb//Һ��ģ��II���ù���ͨ����������
 #define BUS_COOLER_2_LESS_POWER_ON_OR			0x0008//Һ��ģ��II���ù���ͨ����������
 //bit3Ϊ1��bit2Ϊ0
 
 #define BUS_COOLER_2_POWER_OFF_AND				0xfffe//Һ��ģ��II�������ù���ϣ���������
 #define BUS_COOLER_2_POWER_OFF_OR				0x0002//Һ��ģ��II�������ù���ϣ���������
 //bit1Ϊ1��bit0Ϊ0
 
 /*����ͨѶ״̬ �궨��-----------------------------------------------------------*/

 #define MESSAGE_STATE_MAX_COUNT				0x0003	//��ʱʱ������ż�ֵ��Լ1.5s
 
 #define MESSAGE_STATE_VALIDITY_TRUE			0xaaaa	//�������ݽ�����Ч
 #define MESSAGE_STATE_VALIDITY_FALSE			0x5555	//�������ݽ�����Ч
 #define MESSAGE_STATE_VALIDITY_UNKNOW			0x55aa	//����������Ч��δ֪
 
 #define MESSAGE_STATE_NORMAL					0x4e	//ͨѶ����
 #define MESSAGE_STATE_ABNORMAL					0x6f	//ͨѶ��ʱ
 #define MESSAGE_STATE_R_ERROR					0xaa	//ͨѶ�������ݴ���
 
 
/*ע���豸����ָ�� �궨��-----------------------------------------------------------*/

#define INPUT_COMMAND_TYPE_TGTHT530a_ON_POWER 		0xa1a1
#define INPUT_COMMAND_TYPE_TGTHT530b_ON_POWER 		0xa2a2
#define INPUT_COMMAND_TYPE_TGTHT530c_ON_POWER 		0xa3a3
#define INPUT_COMMAND_TYPE_TGTHT530a_OFF_POWER 		0xa4a4
#define INPUT_COMMAND_TYPE_TGTHT530b_OFF_POWER 		0xa5a5
#define INPUT_COMMAND_TYPE_TGTHT530c_OFF_POWER 		0xa6a6
#define INPUT_COMMAND_TYPE_COMPRESS_A_ON_POWER 		0xa7a7
#define INPUT_COMMAND_TYPE_COMPRESS_B_ON_POWER 		0xa8a8
#define INPUT_COMMAND_TYPE_COMPRESS_C_ON_POWER 		0xa9a9
#define INPUT_COMMAND_TYPE_COMPRESS_A_OFF_POWER 	0xaaaa
#define INPUT_COMMAND_TYPE_COMPRESS_B_OFF_POWER		0xabab
#define INPUT_COMMAND_TYPE_COMPRESS_C_OFF_POWER 	0xacac
#define INPUT_COMMAND_TYPE_COMPRESS_A_START 		0xadad
#define INPUT_COMMAND_TYPE_COMPRESS_B_START 		0xaeae
#define INPUT_COMMAND_TYPE_COMPRESS_C_START 		0xafaf
#define INPUT_COMMAND_TYPE_COMPRESS_A_STOP 			0xb0b0
#define INPUT_COMMAND_TYPE_COMPRESS_B_STOP 			0xb1b1
#define INPUT_COMMAND_TYPE_COMPRESS_C_STOP 			0xb2b2
#define INPUT_COMMAND_TYPE_VALVE_SUPPLY_ON_POWER 	0xb3b3
#define INPUT_COMMAND_TYPE_VALVE_SUPPLY_OFF_POWER 	0xb4b4
#define INPUT_COMMAND_TYPE_LVt1K					0xb5b5
#define INPUT_COMMAND_TYPE_LVt1G					0xb6b6
#define INPUT_COMMAND_TYPE_LVt6K					0xb7b7
#define INPUT_COMMAND_TYPE_LVt6G					0xb8b8

 
 
/*1553B���ߴ���ģ�麯������---------------------------------------------------*/


#ifdef TEST_VERSION

void TGTHT510_1553b_transmitcommand_test_FM_state(uint16 which_bu65170);

#endif


void TGTHT510_1553b_initial(void);
uint16 TGTHT510_1553b_wait_for_fpga(uint16 which_bu65170);
uint16 TGTHT510_1553b_get_data(uint16 which_bu65170,uint32 base_address,uint16 *buf,uint16 len);
uint16 TGTHT510_1553b_set_data(uint16 which_bu65170,uint32 base_address,uint16 *buf,uint16 len);
void TGTHT510_1553b_receiveANDtransmitdata(uint16 which_bu65170);
void TGTHT510_1553b_message_state_dealing(void);
void TGTHT510_1553b_message_count_update(void);
uint16 TGTHT510_which_bus_choice(void);
void TGTHT510_1553b_main(void);	
void TGTHT510_1553b_dealing(uint16 which_bu65170);	
void TGTHT510_1553b_transmitdata_CGandGC(uint16 which_bu65170);
void TGTHT510_1553b_transmitdata_YBYC(uint16 which_bu65170);
void TGTHT510_1553b_transmitdata_HYCT1100(uint16 which_bu65170);
void TGTHT510_1553b_transmitdata_GNC(uint16 which_bu65170);
void TGTHT510_1553b_transmitdata_MEMORY(uint16 which_bu65170);

void TGTHT510_1553b_transmitdata_askforserive(uint16 which_bu65170);

void TGTHT510_1553b_transmitcommand_equiment(uint16 which_bu65170);
uint8 TGTHT510_1553b_receivedata_subsystem_EPDU_sum_get(uint16 type,uint16 *p,uint16 length);
uint8 TGTHT510_1553b_receivedata_subsystem_EPDU_sum_calculate(uint16 type,uint16 *p,uint16 size);
uint16 TGTHT510_1553b_receivedata_subsystem_EPDU_length_generate(uint16 type);
void TGTHT510_1553b_receivedata_subsystem_buffer(uint16 type,uint16 *p,uint16 length);
uint16 TGTHT510_1553b_receivedata_subsystem_save_EPDU(uint16 type,uint16 start_i,uint16 which_bu65170);
void TGTHT510_1553b_receivedata_subsystem(uint16 which_bu65170);
uint16 TGTHT510_1553b_receivecommand_buscommand_ISO_calculate(uint16 *p,uint16 size);
uint16 TGTHT510_1553b_receivecommand_buscommand_is_correct(uint16 *p);
void TGTHT510_1553b_receivecommand_buscommand_code_dealing(uint8 code);
void TGTHT510_1553b_receivecommand_buscommand(uint16 which_bu65170);
uint16 TGTHT510_1553b_receivecommand_inputcommand_CRC_calculate(TGTHT510_1553B_inputcommand_TypeDef a);
uint16 TGTHT510_1553b_receivecommand_inputcommand_is_correct(TGTHT510_1553B_inputcommand_TypeDef a);
TGTHT510_1553B_inputcommand_TypeDef TGTHT510_1553b_receivecommand_inputcommand_save(uint16 which_bu65170);
uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_dealing(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_is_correct(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i,uint16 length);
uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_length_get(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
uint16 TGTHT510_1553b_receivecommand_inputcommand_EPDU_length_type_judge(uint16 type);
void TGTHT510_1553b_receivecommand_inputcommand_dealing(TGTHT510_1553B_inputcommand_TypeDef a);
void TGTHT510_1553b_receivecommand_inputcommand(uint16 which_bu65170);
void TGTHT510_1553b_receivedata_HYCT1100(uint16 which_bu65170,uint16 type);

void TGTHT510_1553b_receivedata_KPU(uint16 which_bu65170);

void TGTHT510_1553b_receivecommand_interactivecommand(uint16 which_bu65170);
void TGTHT510_1553b_relay_dealing(uint16 code);

void TGTHT510_1553b_inputcommand_dealing_power(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_multi_contr_spot(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_all_contr_spot(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_one_mea_spot(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_one_fixed(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_auto_resume(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_all_resume(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_source(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_place_signal_en(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_place_signal_dis(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_fault_en(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_fault_dis(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_supply_stage(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_supply_para(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_exhaust(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_max_comp(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_max_velocity(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_min_velocity(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_max_flow(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_temp_contr_mode(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_start_min(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_start_max(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_alarm(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_cooler(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_comp_pressure(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_stop_pre(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_dp_high(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_dp1_low(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_dp2_low(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_max_repress(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_start_speed(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_comp_stop_speed(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_delay_short(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_delay_long(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_time_bypath(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_eps1(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_eps2(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_pressure_comp_in_max(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_pressure_comp_in_min(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_pressure_comp_out_min(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_pressure_hyc(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_sensor_pipe_F(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_sensor_pipe_O(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_sensor_tank_F(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_sensor_tank_O(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_sensor_comp_in(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_sensor_pipe_low(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_supply_continue_g(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_equ_command(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_heat_on(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_supply_pause(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_supply_break(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_supply_continue(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_cpu_set(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_leak(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);
void TGTHT510_1553b_inputcommand_dealing_stage_fault(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);

void TGTHT510_1553b_inputcommand_dealing_compressor_flag_set(TGTHT510_1553B_inputcommand_TypeDef a,uint16 start_i);


 
 #endif
