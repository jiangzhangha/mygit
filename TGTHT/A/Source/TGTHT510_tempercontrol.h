/**
  ******************************************************************************
  * @file    TGTHT510_tempercontrol.h
  * @author  ����
  * @version V1.00
  * @date    20150624
  * @brief   �ռ�վ���Ĳ��ƽ��������Զ�����ģ��ͷ�ļ�
  ******************************************************************************
  */

#ifndef __TGTHT510_tempercontrol_h
#define __TGTHT510_tempercontrol_h 

/*�����ṹ������---------------------------------------------------------*/

typedef struct
{
	uint16 control_state;			//�Ƿ������£�ENABLE��DISABLE
	uint16 fixed_output_state;		//�Ƿ�̶�ռ�ձ������ENABLE��DISABLE
	uint16 control_spot[3];			//���µ㣬�ֱ�ΪT1��T2��T3
	uint16 power[2];				//���ģ��ֱ�Ϊ��·���ģ���·����
	uint16 fixed_output_count;		//�̶�ռ�ر����������
	uint16 source_data[7];			//���������Դ��ʶ
	uint16 number;					//���»�··�ţ����Ϊ0~49·

}Temperature_control_block_TypeDef;	//�¶ȿ��ƿ�ṹ�嶨��

/*
source_data[7]Ϊ���������Դ��ʶ��

bit15��14Ϊ00��ʾ����¶ȴ�����ΪMF51��
bit15��14Ϊ01��ʾ����¶ȴ�����Ϊ�����裻
bit15��14Ϊ10��ʾ����¶ȴ�����ΪMF61��

bit13-12Ϊ01��ʾ�ò���¶�ֵλ���ƽ�ң����·��ң��֡��֡A֡��
bit13-12Ϊ10��ʾ�ò���¶�ֵλ���ƽ�ң����·��ң��֡��֡B֡��

bit11-10Ϊ00��ʾ�ò���¶�ֵ���ƽ�ң����·��ң��֡��Ϊ�֣�16λ����ʾ��
bit11-10Ϊ01��ʾ�ò���¶�ֵ���ƽ�ң����·��ң��֡��Ϊ���ֽڣ�8λ����ʾ��
bit11-10Ϊ10��ʾ�ò���¶�ֵ���ƽ�ң����·��ң��֡��Ϊ���ֽڣ�8λ����ʾ��

bit9-8����Ϊ00��Ԥ����

bit7-0ʹ���ֽڣ�8λ����ʾ�ò���¶�ֵ���ƽ�ң����·��ң��֡�л���λ�ã�

��Ч�����Ź̶�Ϊ0xffff

*/



typedef struct
{
	uint16 data_state_TGTHT100;		//ң����·���¶������Ƿ�������ENABLE��DISABLE
	uint16 data_state_KPU;			//����ң�������Ƿ�������ENABLE��DISABLE
	uint16 source;					//����ʹ��ң��������Դ��ң����·�л�������
	uint16 total_power;				//�������ƹ���
	
}Temperature_control_global_TypeDef;//�¶ȿ���ȫ�ֱ����ṹ�嶨��


typedef struct
{
	uint16 auto_control_data[50];				//�Զ����»�·��Ч�����¶ȣ������¶ȴ�С����˳������
	uint16 auto_control_num[50];				//�Զ����»�··�ţ������¶ȴ�С����˳������
	uint16 auto_control_count;					//�Զ����»�·����
	uint16 auto_control_last_state_main[50];	//�Զ����£���·��һ����״̬��ENABLE����DISABLE���±꼴���»�··��
	uint16 auto_control_last_state_less[50];	//�Զ����£���·��һ����״̬��ENABLE����DISABLE���±꼴���»�··��
	uint16 fixed_control_data[50];				//�̶�ռ�ձ��������
	uint16 fixed_control_num[50];				//�̶�ռ�ձ����·��
	uint16 fixed_control_count;					//�̶�ռ�ձ������·����
	
}Temperature_control_valid_data_TypeDef;//������Ч�����ṹ��


typedef struct
{
	uint16 temp[7];
}Temperature_control_temp_TypeDef;//������ʱ����



/*�궨��----------------------------------------------------------------------*/

#define SOURCE_DATA_A 			0x000a//ң����·�и�֡A
#define SOURCE_DATA_B 			0x000b//ң����·�и�֡B
#define SOURCE_DATA_AB			0x00ab//ң����·�и�֡a
#define SOURCE_DATA_NONE 		0xccff//�޿��²��

#define TEMPER_SPOT_T1			0x0752//���µ�T1��4���϶ȣ�MF61Դ��ֵ
#define TEMPER_SPOT_T2			0x06a9//���µ�T2��8���϶ȣ�MF61Դ��ֵ
#define TEMPER_SPOT_T3			0x0608//���µ�T3��12���϶ȣ�MF61Դ��ֵ

#define SOURCE_DATA_TGTHT100	0x4e4e//����ʹ��ң��������Դ���ƽ�ң����·��
#define SOURCE_DATA_KPU			0x6f6f//����ʹ��ң��������Դ������KPU

#define SENSOR_TYPE_51			0x5151//�¶ȴ��������ͣ�MF51
#define SENSOR_TYPE_61			0x6161//�¶ȴ��������ͣ�MF61
#define SENSOR_TYPE_PT			0xabab//�¶ȴ��������ͣ�������


#define HEATER_MAIN				0x3131//���ݼ�����ͨ
#define HEATER_LESS				0x3939//���ݼ�����ͨ
#define HEATER_BOTH				0x3f3f//������������ͨ

#define POWER_INITIAL			0x012c//��ʼ���ƹ���300w

#define FIXED_UPDATE			0x4e4e//�̶�ռ�ȼ����������ڸ��£�����ĳ·����Ϊ��
#define FIXED_NO_UPDATE			0x6f6f//�̶�ռ�ȼ����������ڸ��£�δ����ĳ·����Ϊ��

#define TEMP_RANGE_LESS_T1			0x2323//�¶�ֵС�ڿ��µ�T1	
#define TEMP_RANGE_BETWEEN_T1_T2	0x2626//�¶�ֵ�ڿ��µ�T1��T2֮��
#define TEMP_RANGE_BETWEEN_T2_T3	0x2929//�¶�ֵ�ڿ��µ�T2��T3֮��
#define TEMP_RANGE_MORE_T3			0x2e2e//�¶�ֵ���ڿ��µ�T3




#define TEMCONTROL_REG0 	0x21800000
#define TEMCONTROL_REG1 	0x21800004
#define TEMCONTROL_REG2 	0x21800008
#define TEMCONTROL_REG3 	0x2180000c
#define TEMCONTROL_REG4 	0x22800000
#define TEMCONTROL_REG5 	0x22800004
#define TEMCONTROL_REG6 	0x22800008
#define TEMCONTROL_REG7 	0x2280000c//��������������Ĵ�����ַ



/*
#define TEMP_MF51_NEG_50 	0x07e7//MF51,-50���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_NEG_40	0x07d5//MF51,-40���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_NEG_30	0x07ba//MF51,-30���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_NEG_20	0x0792//MF51,-20���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_NEG_10	0x0757//MF51,-10���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_MID_0		0x0707//MF51,0���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_10	0x069e//MF51,10���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_20	0x061f//MF51,20���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_30	0x058c//MF51,30���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_40	0x04ec//MF51,40���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_50	0x0448//MF51,50���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_60	0x03a8//MF51,60���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_70	0x0315//MF51,70���϶ȶ�ӦԴ��ֵ


#define TEMP_MF61_NEG_50 	0x078c//MF61,-50���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_NEG_40	0x0732//MF61,-40���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_NEG_30	0x06ac//MF61,-30���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_NEG_20	0x05f8//MF61,-20���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_NEG_10	0x051f//MF61,-10���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_MID_0		0x0436//MF61,0���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_10	0x0357//MF61,10���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_20	0x0292//MF61,20���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_30	0x01f2//MF61,30���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_40	0x0175//MF61,40���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_50	0x0117//MF61,50���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_60	0x00d1//MF61,60���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_70	0x009e//MF61,70���϶ȶ�ӦԴ��ֵ


#define TEMP_PT_NEG_50 		0x01b1//������,-50���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_NEG_40		0x01c1//������,-40���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_NEG_30		0x01d1//������,-30���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_NEG_20		0x01e1//������,-20���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_NEG_10		0x01f0//������,-10���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_MID_0		0x01ff//������,0���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_10		0x020e//������,10���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_20		0x021d//������,20���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_30		0x022b//������,30���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_40		0x0239//������,40���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_50		0x0247//������,50���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_60		0x0254//������,60���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_70		0x0262//������,70���϶ȶ�ӦԴ��ֵ

*/


#define TEMP_MF51_RANGE_SMALLER_NEG_50		0x0101//MF51�¶ȷ�Χ��С��-50���϶�
#define TEMP_MF51_RANGE_NEG_50_40			0x0202//MF51�¶ȷ�Χ�����ڵ���-50���϶ȣ�С��-40���϶�
#define TEMP_MF51_RANGE_NEG_40_30			0x0303//MF51�¶ȷ�Χ�����ڵ���-40���϶ȣ�С��-30���϶�
#define TEMP_MF51_RANGE_NEG_30_20			0x0404//MF51�¶ȷ�Χ�����ڵ���-30���϶ȣ�С��-20���϶�
#define TEMP_MF51_RANGE_NEG_20_10			0x0505//MF51�¶ȷ�Χ�����ڵ���-20���϶ȣ�С��-10���϶�
#define TEMP_MF51_RANGE_NEG_10_0			0x0606//MF51�¶ȷ�Χ�����ڵ���-10���϶ȣ�С��0���϶�
#define TEMP_MF51_RANGE_POS_0_10			0x0707//MF51�¶ȷ�Χ�����ڵ���0���϶ȣ�С��10���϶�
#define TEMP_MF51_RANGE_POS_10_20			0x0808//MF51�¶ȷ�Χ�����ڵ���10���϶ȣ�С��20���϶�
#define TEMP_MF51_RANGE_POS_20_30			0x0909//MF51�¶ȷ�Χ�����ڵ���20���϶ȣ�С��30���϶�
#define TEMP_MF51_RANGE_POS_30_40			0x0a0a//MF51�¶ȷ�Χ�����ڵ���30���϶ȣ�С��40���϶�
#define TEMP_MF51_RANGE_POS_40_50			0x0b0b//MF51�¶ȷ�Χ�����ڵ���40���϶ȣ�С��50���϶�
#define TEMP_MF51_RANGE_POS_50_60			0x0c0c//MF51�¶ȷ�Χ�����ڵ���50���϶ȣ�С��600���϶�
#define TEMP_MF51_RANGE_POS_60_70			0x0d0d//MF51�¶ȷ�Χ�����ڵ���60���϶ȣ�С��70���϶�
#define TEMP_MF51_RANGE_LARGER_POS_70		0x0e0e//MF51�¶ȷ�Χ�����ڵ���70���϶�


#define TEMP_MF51_RANGE_NEG_50_40_START_NUM		0//MF51�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF51_RANGE_NEG_40_30_START_NUM		10//MF51�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF51_RANGE_NEG_30_20_START_NUM		20//MF51�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF51_RANGE_NEG_20_10_START_NUM		30//MF51�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF51_RANGE_NEG_10_0_START_NUM		40//MF51�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF51_RANGE_POS_0_10_START_NUM		50//MF51�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF51_RANGE_POS_10_20_START_NUM		60//MF51�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF51_RANGE_POS_20_30_START_NUM		70//MF51�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF51_RANGE_POS_30_40_START_NUM		80//MF51�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF51_RANGE_POS_40_50_START_NUM		90//MF51�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF51_RANGE_POS_50_60_START_NUM		100//MF51�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF51_RANGE_POS_60_70_START_NUM		110//MF51�¶ȷ�Χ��ʼ��ѯ���±�ֵ



#define TEMP_MF61_RANGE_SMALLER_NEG_50		0x0101//MF61�¶ȷ�Χ��С��-50���϶�
#define TEMP_MF61_RANGE_NEG_50_40			0x0202//MF61�¶ȷ�Χ�����ڵ���-50���϶ȣ�С��-40���϶�
#define TEMP_MF61_RANGE_NEG_40_30			0x0303//MF61�¶ȷ�Χ�����ڵ���-40���϶ȣ�С��-30���϶�
#define TEMP_MF61_RANGE_NEG_30_20			0x0404//MF61�¶ȷ�Χ�����ڵ���-30���϶ȣ�С��-20���϶�
#define TEMP_MF61_RANGE_NEG_20_10			0x0505//MF61�¶ȷ�Χ�����ڵ���-20���϶ȣ�С��-10���϶�
#define TEMP_MF61_RANGE_NEG_10_0			0x0606//MF61�¶ȷ�Χ�����ڵ���-10���϶ȣ�С��0���϶�
#define TEMP_MF61_RANGE_POS_0_10			0x0707//MF61�¶ȷ�Χ�����ڵ���0���϶ȣ�С��10���϶�
#define TEMP_MF61_RANGE_POS_10_20			0x0808//MF61�¶ȷ�Χ�����ڵ���10���϶ȣ�С��20���϶�
#define TEMP_MF61_RANGE_POS_20_30			0x0909//MF61�¶ȷ�Χ�����ڵ���20���϶ȣ�С��30���϶�
#define TEMP_MF61_RANGE_POS_30_40			0x0a0a//MF61�¶ȷ�Χ�����ڵ���30���϶ȣ�С��40���϶�
#define TEMP_MF61_RANGE_POS_40_50			0x0b0b//MF61�¶ȷ�Χ�����ڵ���40���϶ȣ�С��50���϶�
#define TEMP_MF61_RANGE_POS_50_60			0x0c0c//MF61�¶ȷ�Χ�����ڵ���50���϶ȣ�С��600���϶�
#define TEMP_MF61_RANGE_POS_60_70			0x0d0d//MF61�¶ȷ�Χ�����ڵ���60���϶ȣ�С��70���϶�
#define TEMP_MF61_RANGE_LARGER_POS_70		0x0e0e//MF61�¶ȷ�Χ�����ڵ���70���϶�



#define TEMP_MF61_RANGE_NEG_50_40_START_NUM		0//MF61�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF61_RANGE_NEG_40_30_START_NUM		10//MF61�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF61_RANGE_NEG_30_20_START_NUM		20//MF61�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF61_RANGE_NEG_20_10_START_NUM		30//MF61�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF61_RANGE_NEG_10_0_START_NUM		40//MF61�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF61_RANGE_POS_0_10_START_NUM		50//MF61�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF61_RANGE_POS_10_20_START_NUM		60//MF61�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF61_RANGE_POS_20_30_START_NUM		70//MF61�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF61_RANGE_POS_30_40_START_NUM		80//MF61�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF61_RANGE_POS_40_50_START_NUM		90//MF61�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF61_RANGE_POS_50_60_START_NUM		100//MF61�¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_MF61_RANGE_POS_60_70_START_NUM		110//MF61�¶ȷ�Χ��ʼ��ѯ���±�ֵ


#define TEMP_PT_RANGE_SMALLER_NEG_50		0x0101//�������¶ȷ�Χ��С��-50���϶�
#define TEMP_PT_RANGE_NEG_50_40				0x0202//�������¶ȷ�Χ�����ڵ���-50���϶ȣ�С��-40���϶�
#define TEMP_PT_RANGE_NEG_40_30				0x0303//�������¶ȷ�Χ�����ڵ���-40���϶ȣ�С��-30���϶�
#define TEMP_PT_RANGE_NEG_30_20				0x0404//�������¶ȷ�Χ�����ڵ���-30���϶ȣ�С��-20���϶�
#define TEMP_PT_RANGE_NEG_20_10				0x0505//�������¶ȷ�Χ�����ڵ���-20���϶ȣ�С��-10���϶�
#define TEMP_PT_RANGE_NEG_10_0				0x0606//�������¶ȷ�Χ�����ڵ���-10���϶ȣ�С��0���϶�
#define TEMP_PT_RANGE_POS_0_10				0x0707//�������¶ȷ�Χ�����ڵ���0���϶ȣ�С��10���϶�
#define TEMP_PT_RANGE_POS_10_20				0x0808//�������¶ȷ�Χ�����ڵ���10���϶ȣ�С��20���϶�
#define TEMP_PT_RANGE_POS_20_30				0x0909//�������¶ȷ�Χ�����ڵ���20���϶ȣ�С��30���϶�
#define TEMP_PT_RANGE_POS_30_40				0x0a0a//�������¶ȷ�Χ�����ڵ���30���϶ȣ�С��40���϶�
#define TEMP_PT_RANGE_POS_40_50				0x0b0b//�������¶ȷ�Χ�����ڵ���40���϶ȣ�С��50���϶�
#define TEMP_PT_RANGE_POS_50_60				0x0c0c//�������¶ȷ�Χ�����ڵ���50���϶ȣ�С��600���϶�
#define TEMP_PT_RANGE_POS_60_70				0x0d0d//�������¶ȷ�Χ�����ڵ���60���϶ȣ�С��70���϶�
#define TEMP_PT_RANGE_LARGER_POS_70			0x0e0e//�������¶ȷ�Χ�����ڵ���70���϶�


#define TEMP_PT_RANGE_NEG_50_40_START_NUM		0//�������¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_PT_RANGE_NEG_40_30_START_NUM		10//�������¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_PT_RANGE_NEG_30_20_START_NUM		20//�������¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_PT_RANGE_NEG_20_10_START_NUM		30//�������¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_PT_RANGE_NEG_10_0_START_NUM		40//�������¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_PT_RANGE_POS_0_10_START_NUM		50//�������¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_PT_RANGE_POS_10_20_START_NUM		60//�������¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_PT_RANGE_POS_20_30_START_NUM		70//�������¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_PT_RANGE_POS_30_40_START_NUM		80//�������¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_PT_RANGE_POS_40_50_START_NUM		90//�������¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_PT_RANGE_POS_50_60_START_NUM		100//�������¶ȷ�Χ��ʼ��ѯ���±�ֵ
#define TEMP_PT_RANGE_POS_60_70_START_NUM		110//�������¶ȷ�Χ��ʼ��ѯ���±�ֵ

//------------------------------------�¶ȿ��ƿ�궨��------------------------------

#define TCB_INVALID_DATA	0xffff		//��Ч���

#define TCB_SENSOR_PT_R		0x4000		//����¶ȴ�����Ϊ������
#define TCB_SENSOR_MF51		0x0000		//����¶ȴ�����ΪMF51
#define TCB_SENSOR_MF61		0x8000		//����¶ȴ�����ΪMF61

#define TCB_FROM_100_A		0x1000		//�������λ���ƽ�ң����·��ң��֡��֡A֡
#define TCB_FROM_100_B		0x2000		//�������λ���ƽ�ң����·��ң��֡��֡B֡

#define TCB_WORD_A			0x0000		//����������ƽ�ң����·��ң��֡��Ϊ�֣�16λ����ʾ
#define TCB_BYTE_H			0x0400		//����������ƽ�ң����·��ң��֡��Ϊ���ֽڣ�8λ����ʾ
#define TCB_BYTE_L			0x0800		//����������ƽ�ң����·��ң��֡��Ϊ���ֽڣ�8λ����ʾ

#define TCB_LOC_00			0x0000		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_01			0x0001		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_02			0x0002		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_03			0x0003		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_04			0x0004		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_05			0x0005		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_06			0x0006		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_07			0x0007		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_08			0x0008		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_09			0x0009		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_10			0x000a		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_11			0x000b		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_12			0x000c		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_13			0x000d		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_14			0x000e		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_15			0x000f		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_16			0x0010		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_17			0x0011		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_18			0x0012		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_19			0x0013		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_20			0x0014		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_21			0x0015		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_22			0x0016		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_23			0x0017		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_24			0x0018		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_25			0x0019		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_26			0x001a		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_27			0x001b		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_28			0x001c		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_29			0x001d		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_30			0x001e		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_31			0x001f		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_32			0x0020		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_33			0x0021		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_34			0x0022		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_35			0x0023		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_36			0x0024		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_37			0x0025		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_38			0x0026		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_39			0x0027		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_40			0x0028		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_41			0x0029		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_42			0x002a		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_43			0x002b		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_44			0x002c		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_45			0x002d		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_46			0x002e		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_47			0x002f		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_48			0x0030		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_49			0x0031		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_50			0x0032		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_51			0x0033		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_52			0x0034		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_53			0x0035		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_54			0x0036		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_55			0x0037		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_56			0x0038		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_57			0x0039		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_58			0x003a		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_59			0x003b		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_60			0x003c		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_61			0x003d		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_62			0x003e		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_63			0x003f		//����������ƽ�ң����·��ң��֡��λ�ö���
#define TCB_LOC_64			0x0040		//����������ƽ�ң����·��ң��֡��λ�ö���


//------------------------------------MF51�¶�Դ���ѯ��궨��------------------------------

#define TABLE_MF51_NEG_50	0x0136		//MF51�¶�Դ���ѯ��-50���϶�
#define TABLE_MF51_NEG_49	0x0126		//MF51�¶�Դ���ѯ��-49���϶�
#define TABLE_MF51_NEG_48	0x0117		//MF51�¶�Դ���ѯ��-48���϶�
#define TABLE_MF51_NEG_47	0x0108		//MF51�¶�Դ���ѯ��-47���϶�
#define TABLE_MF51_NEG_46	0x00fb		//MF51�¶�Դ���ѯ��-46���϶�
#define TABLE_MF51_NEG_45	0x00ee		//MF51�¶�Դ���ѯ��-45���϶�
#define TABLE_MF51_NEG_44	0x00e2		//MF51�¶�Դ���ѯ��-44���϶�
#define TABLE_MF51_NEG_43	0x00d6		//MF51�¶�Դ���ѯ��-43���϶�
#define TABLE_MF51_NEG_42	0x00cb		//MF51�¶�Դ���ѯ��-42���϶�
#define TABLE_MF51_NEG_41	0x00c1		//MF51�¶�Դ���ѯ��-41���϶�
#define TABLE_MF51_NEG_40	0x00b7		//MF51�¶�Դ���ѯ��-40���϶�
#define TABLE_MF51_NEG_39	0x00ae		//MF51�¶�Դ���ѯ��-39���϶�
#define TABLE_MF51_NEG_38	0x00a5		//MF51�¶�Դ���ѯ��-38���϶�
#define TABLE_MF51_NEG_37	0x009d		//MF51�¶�Դ���ѯ��-37���϶�
#define TABLE_MF51_NEG_36	0x0095		//MF51�¶�Դ���ѯ��-36���϶�
#define TABLE_MF51_NEG_35	0x008e		//MF51�¶�Դ���ѯ��-35���϶�
#define TABLE_MF51_NEG_34	0x0087		//MF51�¶�Դ���ѯ��-34���϶�
#define TABLE_MF51_NEG_33	0x0080		//MF51�¶�Դ���ѯ��-33���϶�
#define TABLE_MF51_NEG_32	0x007a		//MF51�¶�Դ���ѯ��-32���϶�
#define TABLE_MF51_NEG_31	0x0074		//MF51�¶�Դ���ѯ��-31���϶�
#define TABLE_MF51_NEG_30	0x006f		//MF51�¶�Դ���ѯ��-30���϶�
#define TABLE_MF51_NEG_29	0x0069		//MF51�¶�Դ���ѯ��-29���϶�
#define TABLE_MF51_NEG_28	0x0064		//MF51�¶�Դ���ѯ��-28���϶�
#define TABLE_MF51_NEG_27	0x005f		//MF51�¶�Դ���ѯ��-27���϶�
#define TABLE_MF51_NEG_26	0x005b		//MF51�¶�Դ���ѯ��-26���϶�
#define TABLE_MF51_NEG_25	0x0057		//MF51�¶�Դ���ѯ��-25���϶�
#define TABLE_MF51_NEG_24	0x0053		//MF51�¶�Դ���ѯ��-24���϶�
#define TABLE_MF51_NEG_23	0x004f		//MF51�¶�Դ���ѯ��-23���϶�
#define TABLE_MF51_NEG_22	0x004b		//MF51�¶�Դ���ѯ��-22���϶�
#define TABLE_MF51_NEG_21	0x0048		//MF51�¶�Դ���ѯ��-21���϶�
#define TABLE_MF51_NEG_20	0x0044		//MF51�¶�Դ���ѯ��-20���϶�
#define TABLE_MF51_NEG_19	0x0041		//MF51�¶�Դ���ѯ��-19���϶�
#define TABLE_MF51_NEG_18	0x003e		//MF51�¶�Դ���ѯ��-18���϶�
#define TABLE_MF51_NEG_17	0x003b		//MF51�¶�Դ���ѯ��-17���϶�
#define TABLE_MF51_NEG_16	0x0039		//MF51�¶�Դ���ѯ��-16���϶�
#define TABLE_MF51_NEG_15	0x0036		//MF51�¶�Դ���ѯ��-15���϶�
#define TABLE_MF51_NEG_14	0x0034		//MF51�¶�Դ���ѯ��-14���϶�
#define TABLE_MF51_NEG_13	0x0031		//MF51�¶�Դ���ѯ��-13���϶�
#define TABLE_MF51_NEG_12	0x002f		//MF51�¶�Դ���ѯ��-12���϶�
#define TABLE_MF51_NEG_11	0x002d		//MF51�¶�Դ���ѯ��-11���϶�
#define TABLE_MF51_NEG_10	0x002b		//MF51�¶�Դ���ѯ��-10���϶�
#define TABLE_MF51_NEG_09	0x0029		//MF51�¶�Դ���ѯ��-09���϶�
#define TABLE_MF51_NEG_08	0x0028		//MF51�¶�Դ���ѯ��-08���϶�
#define TABLE_MF51_NEG_07	0x0026		//MF51�¶�Դ���ѯ��-07���϶�
#define TABLE_MF51_NEG_06	0x0024		//MF51�¶�Դ���ѯ��-06���϶�
#define TABLE_MF51_NEG_05	0x0023		//MF51�¶�Դ���ѯ��-05���϶�
#define TABLE_MF51_NEG_04	0x0021		//MF51�¶�Դ���ѯ��-04���϶�
#define TABLE_MF51_NEG_03	0x0020		//MF51�¶�Դ���ѯ��-03���϶�
#define TABLE_MF51_NEG_02	0x001f		//MF51�¶�Դ���ѯ��-02���϶�
#define TABLE_MF51_NEG_01	0x001d		//MF51�¶�Դ���ѯ��-01���϶�
#define TABLE_MF51_MID_00	0x001c		//MF51�¶�Դ���ѯ��-00���϶�
#define TABLE_MF51_POS_01	0x001b		//MF51�¶�Դ���ѯ��+01���϶�
#define TABLE_MF51_POS_02	0x001a		//MF51�¶�Դ���ѯ��+02���϶�
#define TABLE_MF51_POS_03	0x0019		//MF51�¶�Դ���ѯ��+03���϶�
#define TABLE_MF51_POS_04	0x0018		//MF51�¶�Դ���ѯ��+04���϶�
#define TABLE_MF51_POS_05	0x0017		//MF51�¶�Դ���ѯ��+05���϶�
#define TABLE_MF51_POS_06	0x0016		//MF51�¶�Դ���ѯ��+06���϶�
#define TABLE_MF51_POS_07	0x0015		//MF51�¶�Դ���ѯ��+07���϶�
#define TABLE_MF51_POS_08	0x0014		//MF51�¶�Դ���ѯ��+08���϶�
#define TABLE_MF51_POS_09	0x0013		//MF51�¶�Դ���ѯ��+09���϶�
#define TABLE_MF51_POS_10	0x0013		//MF51�¶�Դ���ѯ��+10���϶�
#define TABLE_MF51_POS_11	0x0012		//MF51�¶�Դ���ѯ��+11���϶�
#define TABLE_MF51_POS_12	0x0011		//MF51�¶�Դ���ѯ��+12���϶�
#define TABLE_MF51_POS_13	0x0011		//MF51�¶�Դ���ѯ��+13���϶�
#define TABLE_MF51_POS_14	0x0010		//MF51�¶�Դ���ѯ��+14���϶�
#define TABLE_MF51_POS_15	0x000f		//MF51�¶�Դ���ѯ��+15���϶�
#define TABLE_MF51_POS_16	0x000f		//MF51�¶�Դ���ѯ��+16���϶�
#define TABLE_MF51_POS_17	0x000e		//MF51�¶�Դ���ѯ��+17���϶�
#define TABLE_MF51_POS_18	0x000e		//MF51�¶�Դ���ѯ��+18���϶�
#define TABLE_MF51_POS_19	0x000d		//MF51�¶�Դ���ѯ��+19���϶�
#define TABLE_MF51_POS_20	0x000d		//MF51�¶�Դ���ѯ��+20���϶�
#define TABLE_MF51_POS_21	0x000c		//MF51�¶�Դ���ѯ��+21���϶�
#define TABLE_MF51_POS_22	0x000c		//MF51�¶�Դ���ѯ��+22���϶�
#define TABLE_MF51_POS_23	0x000b		//MF51�¶�Դ���ѯ��+23���϶�
#define TABLE_MF51_POS_24	0x000b		//MF51�¶�Դ���ѯ��+24���϶�
#define TABLE_MF51_POS_25	0x000b		//MF51�¶�Դ���ѯ��+25���϶�
#define TABLE_MF51_POS_26	0x000a		//MF51�¶�Դ���ѯ��+26���϶�
#define TABLE_MF51_POS_27	0x000a		//MF51�¶�Դ���ѯ��+27���϶�
#define TABLE_MF51_POS_28	0x0009		//MF51�¶�Դ���ѯ��+28���϶�
#define TABLE_MF51_POS_29	0x0009		//MF51�¶�Դ���ѯ��+29���϶�
#define TABLE_MF51_POS_30	0x0009		//MF51�¶�Դ���ѯ��+30���϶�
#define TABLE_MF51_POS_31	0x0008		//MF51�¶�Դ���ѯ��+31���϶�
#define TABLE_MF51_POS_32	0x0008		//MF51�¶�Դ���ѯ��+32���϶�
#define TABLE_MF51_POS_33	0x0008		//MF51�¶�Դ���ѯ��+33���϶�
#define TABLE_MF51_POS_34	0x0008		//MF51�¶�Դ���ѯ��+34���϶�
#define TABLE_MF51_POS_35	0x0007		//MF51�¶�Դ���ѯ��+35���϶�
#define TABLE_MF51_POS_36	0x0007		//MF51�¶�Դ���ѯ��+36���϶�
#define TABLE_MF51_POS_37	0x0007		//MF51�¶�Դ���ѯ��+37���϶�
#define TABLE_MF51_POS_38	0x0007		//MF51�¶�Դ���ѯ��+38���϶�
#define TABLE_MF51_POS_39	0x0006		//MF51�¶�Դ���ѯ��+39���϶�
#define TABLE_MF51_POS_40	0x0006		//MF51�¶�Դ���ѯ��+40���϶�
#define TABLE_MF51_POS_41	0x0006		//MF51�¶�Դ���ѯ��+41���϶�
#define TABLE_MF51_POS_42	0x0006		//MF51�¶�Դ���ѯ��+42���϶�
#define TABLE_MF51_POS_43	0x0006		//MF51�¶�Դ���ѯ��+43���϶�
#define TABLE_MF51_POS_44	0x0005		//MF51�¶�Դ���ѯ��+44���϶�
#define TABLE_MF51_POS_45	0x0005		//MF51�¶�Դ���ѯ��+45���϶�
#define TABLE_MF51_POS_46	0x0005		//MF51�¶�Դ���ѯ��+46���϶�
#define TABLE_MF51_POS_47	0x0005		//MF51�¶�Դ���ѯ��+47���϶�
#define TABLE_MF51_POS_48	0x0005		//MF51�¶�Դ���ѯ��+48���϶�
#define TABLE_MF51_POS_49	0x0005		//MF51�¶�Դ���ѯ��+49���϶�
#define TABLE_MF51_POS_50	0x0004		//MF51�¶�Դ���ѯ��+50���϶�
#define TABLE_MF51_POS_51	0x0004		//MF51�¶�Դ���ѯ��+51���϶�
#define TABLE_MF51_POS_52	0x0004		//MF51�¶�Դ���ѯ��+52���϶�
#define TABLE_MF51_POS_53	0x0004		//MF51�¶�Դ���ѯ��+53���϶�
#define TABLE_MF51_POS_54	0x0004		//MF51�¶�Դ���ѯ��+54���϶�
#define TABLE_MF51_POS_55	0x0004		//MF51�¶�Դ���ѯ��+55���϶�
#define TABLE_MF51_POS_56	0x0004		//MF51�¶�Դ���ѯ��+56���϶�
#define TABLE_MF51_POS_57	0x0004		//MF51�¶�Դ���ѯ��+57���϶�
#define TABLE_MF51_POS_58	0x0003		//MF51�¶�Դ���ѯ��+58���϶�
#define TABLE_MF51_POS_59	0x0003		//MF51�¶�Դ���ѯ��+59���϶�
#define TABLE_MF51_POS_60	0x0003		//MF51�¶�Դ���ѯ��+60���϶�
#define TABLE_MF51_POS_61	0x0003		//MF51�¶�Դ���ѯ��+61���϶�
#define TABLE_MF51_POS_62	0x0003		//MF51�¶�Դ���ѯ��+62���϶�
#define TABLE_MF51_POS_63	0x0003		//MF51�¶�Դ���ѯ��+63���϶�
#define TABLE_MF51_POS_64	0x0003		//MF51�¶�Դ���ѯ��+64���϶�
#define TABLE_MF51_POS_65	0x0003		//MF51�¶�Դ���ѯ��+65���϶�
#define TABLE_MF51_POS_66	0x0003		//MF51�¶�Դ���ѯ��+66���϶�
#define TABLE_MF51_POS_67	0x0003		//MF51�¶�Դ���ѯ��+67���϶�
#define TABLE_MF51_POS_68	0x0003		//MF51�¶�Դ���ѯ��+68���϶�
#define TABLE_MF51_POS_69	0x0003		//MF51�¶�Դ���ѯ��+69���϶�
#define TABLE_MF51_POS_70	0x0002		//MF51�¶�Դ���ѯ��+70���϶�



//------------------------------------MF61�¶�Դ���ѯ��궨��------------------------------

#define TABLE_MF61_NEG_50	0x0e56		//MF61�¶�Դ���ѯ��-50���϶�
#define TABLE_MF61_NEG_49	0x0e48		//MF61�¶�Դ���ѯ��-49���϶�
#define TABLE_MF61_NEG_48	0x0e3a		//MF61�¶�Դ���ѯ��-48���϶�
#define TABLE_MF61_NEG_47	0x0e2b		//MF61�¶�Դ���ѯ��-47���϶�
#define TABLE_MF61_NEG_46	0x0e1b		//MF61�¶�Դ���ѯ��-46���϶�
#define TABLE_MF61_NEG_45	0x0e0b		//MF61�¶�Դ���ѯ��-45���϶�
#define TABLE_MF61_NEG_44	0x0df9		//MF61�¶�Դ���ѯ��-44���϶�
#define TABLE_MF61_NEG_43	0x0de7		//MF61�¶�Դ���ѯ��-43���϶�
#define TABLE_MF61_NEG_42	0x0dd4		//MF61�¶�Դ���ѯ��-42���϶�
#define TABLE_MF61_NEG_41	0x0dc1		//MF61�¶�Դ���ѯ��-41���϶�
#define TABLE_MF61_NEG_40	0x0dac		//MF61�¶�Դ���ѯ��-40���϶�
#define TABLE_MF61_NEG_39	0x0d97		//MF61�¶�Դ���ѯ��-39���϶�
#define TABLE_MF61_NEG_38	0x0d80		//MF61�¶�Դ���ѯ��-38���϶�
#define TABLE_MF61_NEG_37	0x0d69		//MF61�¶�Դ���ѯ��-37���϶�
#define TABLE_MF61_NEG_36	0x0d51		//MF61�¶�Դ���ѯ��-36���϶�
#define TABLE_MF61_NEG_35	0x0d38		//MF61�¶�Դ���ѯ��-35���϶�
#define TABLE_MF61_NEG_34	0x0d1e		//MF61�¶�Դ���ѯ��-34���϶�
#define TABLE_MF61_NEG_33	0x0d04		//MF61�¶�Դ���ѯ��-33���϶�
#define TABLE_MF61_NEG_32	0x0ce8		//MF61�¶�Դ���ѯ��-32���϶�
#define TABLE_MF61_NEG_31	0x0ccb		//MF61�¶�Դ���ѯ��-31���϶�
#define TABLE_MF61_NEG_30	0x0cae		//MF61�¶�Դ���ѯ��-30���϶�
#define TABLE_MF61_NEG_29	0x0c90		//MF61�¶�Դ���ѯ��-29���϶�
#define TABLE_MF61_NEG_28	0x0c70		//MF61�¶�Դ���ѯ��-28���϶�
#define TABLE_MF61_NEG_27	0x0c50		//MF61�¶�Դ���ѯ��-27���϶�
#define TABLE_MF61_NEG_26	0x0c2f		//MF61�¶�Դ���ѯ��-26���϶�
#define TABLE_MF61_NEG_25	0x0c0d		//MF61�¶�Դ���ѯ��-25���϶�
#define TABLE_MF61_NEG_24	0x0bea		//MF61�¶�Դ���ѯ��-24���϶�
#define TABLE_MF61_NEG_23	0x0bc7		//MF61�¶�Դ���ѯ��-23���϶�
#define TABLE_MF61_NEG_22	0x0ba2		//MF61�¶�Դ���ѯ��-22���϶�
#define TABLE_MF61_NEG_21	0x0b7d		//MF61�¶�Դ���ѯ��-21���϶�
#define TABLE_MF61_NEG_20	0x0b57		//MF61�¶�Դ���ѯ��-20���϶�
#define TABLE_MF61_NEG_19	0x0b31		//MF61�¶�Դ���ѯ��-19���϶�
#define TABLE_MF61_NEG_18	0x0b09		//MF61�¶�Դ���ѯ��-18���϶�
#define TABLE_MF61_NEG_17	0x0ae2		//MF61�¶�Դ���ѯ��-17���϶�
#define TABLE_MF61_NEG_16	0x0ab9		//MF61�¶�Դ���ѯ��-16���϶�
#define TABLE_MF61_NEG_15	0x0a90		//MF61�¶�Դ���ѯ��-15���϶�
#define TABLE_MF61_NEG_14	0x0a66		//MF61�¶�Դ���ѯ��-14���϶�
#define TABLE_MF61_NEG_13	0x0a3c		//MF61�¶�Դ���ѯ��-13���϶�
#define TABLE_MF61_NEG_12	0x0a11		//MF61�¶�Դ���ѯ��-12���϶�
#define TABLE_MF61_NEG_11	0x09e6		//MF61�¶�Դ���ѯ��-11���϶�
#define TABLE_MF61_NEG_10	0x09bb		//MF61�¶�Դ���ѯ��-10���϶�
#define TABLE_MF61_NEG_09	0x098f		//MF61�¶�Դ���ѯ��-09���϶�
#define TABLE_MF61_NEG_08	0x0963		//MF61�¶�Դ���ѯ��-08���϶�
#define TABLE_MF61_NEG_07	0x0937		//MF61�¶�Դ���ѯ��-07���϶�
#define TABLE_MF61_NEG_06	0x090b		//MF61�¶�Դ���ѯ��-06���϶�
#define TABLE_MF61_NEG_05	0x08df		//MF61�¶�Դ���ѯ��-05���϶�
#define TABLE_MF61_NEG_04	0x08b2		//MF61�¶�Դ���ѯ��-04���϶�
#define TABLE_MF61_NEG_03	0x0886		//MF61�¶�Դ���ѯ��-03���϶�
#define TABLE_MF61_NEG_02	0x0859		//MF61�¶�Դ���ѯ��-02���϶�
#define TABLE_MF61_NEG_01	0x082d		//MF61�¶�Դ���ѯ��-01���϶�
#define TABLE_MF61_MID_00	0x0801		//MF61�¶�Դ���ѯ��-00���϶�
#define TABLE_MF61_POS_01	0x07d5		//MF61�¶�Դ���ѯ��+01���϶�
#define TABLE_MF61_POS_02	0x07a9		//MF61�¶�Դ���ѯ��+02���϶�
#define TABLE_MF61_POS_03	0x077e		//MF61�¶�Դ���ѯ��+03���϶�
#define TABLE_MF61_POS_04	0x0752		//MF61�¶�Դ���ѯ��+04���϶�
#define TABLE_MF61_POS_05	0x0728		//MF61�¶�Դ���ѯ��+05���϶�
#define TABLE_MF61_POS_06	0x06fd		//MF61�¶�Դ���ѯ��+06���϶�
#define TABLE_MF61_POS_07	0x06d3		//MF61�¶�Դ���ѯ��+07���϶�
#define TABLE_MF61_POS_08	0x06a9		//MF61�¶�Դ���ѯ��+08���϶�
#define TABLE_MF61_POS_09	0x0680		//MF61�¶�Դ���ѯ��+09���϶�
#define TABLE_MF61_POS_10	0x0658		//MF61�¶�Դ���ѯ��+10���϶�
#define TABLE_MF61_POS_11	0x0630		//MF61�¶�Դ���ѯ��+11���϶�
#define TABLE_MF61_POS_12	0x0608		//MF61�¶�Դ���ѯ��+12���϶�
#define TABLE_MF61_POS_13	0x05e1		//MF61�¶�Դ���ѯ��+13���϶�
#define TABLE_MF61_POS_14	0x05bb		//MF61�¶�Դ���ѯ��+14���϶�
#define TABLE_MF61_POS_15	0x0595		//MF61�¶�Դ���ѯ��+15���϶�
#define TABLE_MF61_POS_16	0x0570		//MF61�¶�Դ���ѯ��+16���϶�
#define TABLE_MF61_POS_17	0x054c		//MF61�¶�Դ���ѯ��+17���϶�
#define TABLE_MF61_POS_18	0x0528		//MF61�¶�Դ���ѯ��+18���϶�
#define TABLE_MF61_POS_19	0x0505		//MF61�¶�Դ���ѯ��+19���϶�
#define TABLE_MF61_POS_20	0x04e3		//MF61�¶�Դ���ѯ��+20���϶�
#define TABLE_MF61_POS_21	0x04c1		//MF61�¶�Դ���ѯ��+21���϶�
#define TABLE_MF61_POS_22	0x04a0		//MF61�¶�Դ���ѯ��+22���϶�
#define TABLE_MF61_POS_23	0x0480		//MF61�¶�Դ���ѯ��+23���϶�
#define TABLE_MF61_POS_24	0x0460		//MF61�¶�Դ���ѯ��+24���϶�
#define TABLE_MF61_POS_25	0x0441		//MF61�¶�Դ���ѯ��+25���϶�
#define TABLE_MF61_POS_26	0x0423		//MF61�¶�Դ���ѯ��+26���϶�
#define TABLE_MF61_POS_27	0x0406		//MF61�¶�Դ���ѯ��+27���϶�
#define TABLE_MF61_POS_28	0x03e9		//MF61�¶�Դ���ѯ��+28���϶�
#define TABLE_MF61_POS_29	0x03cd		//MF61�¶�Դ���ѯ��+29���϶�
#define TABLE_MF61_POS_30	0x03b2		//MF61�¶�Դ���ѯ��+30���϶�
#define TABLE_MF61_POS_31	0x0397		//MF61�¶�Դ���ѯ��+31���϶�
#define TABLE_MF61_POS_32	0x037d		//MF61�¶�Դ���ѯ��+32���϶�
#define TABLE_MF61_POS_33	0x0364		//MF61�¶�Դ���ѯ��+33���϶�
#define TABLE_MF61_POS_34	0x034b		//MF61�¶�Դ���ѯ��+34���϶�
#define TABLE_MF61_POS_35	0x0333		//MF61�¶�Դ���ѯ��+35���϶�
#define TABLE_MF61_POS_36	0x031c		//MF61�¶�Դ���ѯ��+36���϶�
#define TABLE_MF61_POS_37	0x0305		//MF61�¶�Դ���ѯ��+37���϶�
#define TABLE_MF61_POS_38	0x02ef		//MF61�¶�Դ���ѯ��+38���϶�
#define TABLE_MF61_POS_39	0x02d9		//MF61�¶�Դ���ѯ��+39���϶�
#define TABLE_MF61_POS_40	0x02c4		//MF61�¶�Դ���ѯ��+40���϶�
#define TABLE_MF61_POS_41	0x02b0		//MF61�¶�Դ���ѯ��+41���϶�
#define TABLE_MF61_POS_42	0x029c		//MF61�¶�Դ���ѯ��+42���϶�
#define TABLE_MF61_POS_43	0x0289		//MF61�¶�Դ���ѯ��+43���϶�
#define TABLE_MF61_POS_44	0x0276		//MF61�¶�Դ���ѯ��+44���϶�
#define TABLE_MF61_POS_45	0x0264		//MF61�¶�Դ���ѯ��+45���϶�
#define TABLE_MF61_POS_46	0x0253		//MF61�¶�Դ���ѯ��+46���϶�
#define TABLE_MF61_POS_47	0x0242		//MF61�¶�Դ���ѯ��+47���϶�
#define TABLE_MF61_POS_48	0x0231		//MF61�¶�Դ���ѯ��+48���϶�
#define TABLE_MF61_POS_49	0x0221		//MF61�¶�Դ���ѯ��+49���϶�
#define TABLE_MF61_POS_50	0x0211		//MF61�¶�Դ���ѯ��+50���϶�
#define TABLE_MF61_POS_51	0x0202		//MF61�¶�Դ���ѯ��+51���϶�
#define TABLE_MF61_POS_52	0x01f4		//MF61�¶�Դ���ѯ��+52���϶�
#define TABLE_MF61_POS_53	0x01e5		//MF61�¶�Դ���ѯ��+53���϶�
#define TABLE_MF61_POS_54	0x01d8		//MF61�¶�Դ���ѯ��+54���϶�
#define TABLE_MF61_POS_55	0x01ca		//MF61�¶�Դ���ѯ��+55���϶�
#define TABLE_MF61_POS_56	0x01bd		//MF61�¶�Դ���ѯ��+56���϶�
#define TABLE_MF61_POS_57	0x01b0		//MF61�¶�Դ���ѯ��+57���϶�
#define TABLE_MF61_POS_58	0x01a4		//MF61�¶�Դ���ѯ��+58���϶�
#define TABLE_MF61_POS_59	0x0198		//MF61�¶�Դ���ѯ��+59���϶�
#define TABLE_MF61_POS_60	0x018d		//MF61�¶�Դ���ѯ��+60���϶�
#define TABLE_MF61_POS_61	0x0182		//MF61�¶�Դ���ѯ��+61���϶�
#define TABLE_MF61_POS_62	0x0177		//MF61�¶�Դ���ѯ��+62���϶�
#define TABLE_MF61_POS_63	0x016c		//MF61�¶�Դ���ѯ��+63���϶�
#define TABLE_MF61_POS_64	0x0162		//MF61�¶�Դ���ѯ��+64���϶�
#define TABLE_MF61_POS_65	0x0158		//MF61�¶�Դ���ѯ��+65���϶�
#define TABLE_MF61_POS_66	0x014f		//MF61�¶�Դ���ѯ��+66���϶�
#define TABLE_MF61_POS_67	0x0146		//MF61�¶�Դ���ѯ��+67���϶�
#define TABLE_MF61_POS_68	0x013d		//MF61�¶�Դ���ѯ��+68���϶�
#define TABLE_MF61_POS_69	0x0134		//MF61�¶�Դ���ѯ��+69���϶�
#define TABLE_MF61_POS_70	0x012b		//MF61�¶�Դ���ѯ��+70���϶�



//------------------------------------�������¶�Դ���ѯ��궨��------------------------------

#define TABLE_PT_NEG_50		0x045c		//�������¶�Դ���ѯ��-50���϶�
#define TABLE_PT_NEG_49		0x045f		//�������¶�Դ���ѯ��-49���϶�
#define TABLE_PT_NEG_48		0x0463		//�������¶�Դ���ѯ��-48���϶�
#define TABLE_PT_NEG_47		0x0467		//�������¶�Դ���ѯ��-47���϶�
#define TABLE_PT_NEG_46		0x046b		//�������¶�Դ���ѯ��-46���϶�
#define TABLE_PT_NEG_45		0x046f		//�������¶�Դ���ѯ��-45���϶�
#define TABLE_PT_NEG_44		0x0473		//�������¶�Դ���ѯ��-44���϶�
#define TABLE_PT_NEG_43		0x0476		//�������¶�Դ���ѯ��-43���϶�
#define TABLE_PT_NEG_42		0x047a		//�������¶�Դ���ѯ��-42���϶�
#define TABLE_PT_NEG_41		0x047e		//�������¶�Դ���ѯ��-41���϶�
#define TABLE_PT_NEG_40		0x0482		//�������¶�Դ���ѯ��-40���϶�
#define TABLE_PT_NEG_39		0x0485		//�������¶�Դ���ѯ��-39���϶�
#define TABLE_PT_NEG_38		0x0489		//�������¶�Դ���ѯ��-38���϶�
#define TABLE_PT_NEG_37		0x048d		//�������¶�Դ���ѯ��-37���϶�
#define TABLE_PT_NEG_36		0x0491		//�������¶�Դ���ѯ��-36���϶�
#define TABLE_PT_NEG_35		0x0494		//�������¶�Դ���ѯ��-35���϶�
#define TABLE_PT_NEG_34		0x0498		//�������¶�Դ���ѯ��-34���϶�
#define TABLE_PT_NEG_33		0x049c		//�������¶�Դ���ѯ��-33���϶�
#define TABLE_PT_NEG_32		0x049f		//�������¶�Դ���ѯ��-32���϶�
#define TABLE_PT_NEG_31		0x04a3		//�������¶�Դ���ѯ��-31���϶�
#define TABLE_PT_NEG_30		0x04a7		//�������¶�Դ���ѯ��-30���϶�
#define TABLE_PT_NEG_29		0x04aa		//�������¶�Դ���ѯ��-29���϶�
#define TABLE_PT_NEG_28		0x04ae		//�������¶�Դ���ѯ��-28���϶�
#define TABLE_PT_NEG_27		0x04b1		//�������¶�Դ���ѯ��-27���϶�
#define TABLE_PT_NEG_26		0x04b5		//�������¶�Դ���ѯ��-26���϶�
#define TABLE_PT_NEG_25		0x04b9		//�������¶�Դ���ѯ��-25���϶�
#define TABLE_PT_NEG_24		0x04bc		//�������¶�Դ���ѯ��-24���϶�
#define TABLE_PT_NEG_23		0x04c0		//�������¶�Դ���ѯ��-23���϶�
#define TABLE_PT_NEG_22		0x04c3		//�������¶�Դ���ѯ��-22���϶�
#define TABLE_PT_NEG_21		0x04c7		//�������¶�Դ���ѯ��-21���϶�
#define TABLE_PT_NEG_20		0x04cb		//�������¶�Դ���ѯ��-20���϶�
#define TABLE_PT_NEG_19		0x04ce		//�������¶�Դ���ѯ��-19���϶�
#define TABLE_PT_NEG_18		0x04d2		//�������¶�Դ���ѯ��-18���϶�
#define TABLE_PT_NEG_17		0x04d5		//�������¶�Դ���ѯ��-17���϶�
#define TABLE_PT_NEG_16		0x04d9		//�������¶�Դ���ѯ��-16���϶�
#define TABLE_PT_NEG_15		0x04dc		//�������¶�Դ���ѯ��-15���϶�
#define TABLE_PT_NEG_14		0x04e0		//�������¶�Դ���ѯ��-14���϶�
#define TABLE_PT_NEG_13		0x04e3		//�������¶�Դ���ѯ��-13���϶�
#define TABLE_PT_NEG_12		0x04e7		//�������¶�Դ���ѯ��-12���϶�
#define TABLE_PT_NEG_11		0x04ea		//�������¶�Դ���ѯ��-11���϶�
#define TABLE_PT_NEG_10		0x04ee		//�������¶�Դ���ѯ��-10���϶�
#define TABLE_PT_NEG_09		0x04f1		//�������¶�Դ���ѯ��-09���϶�
#define TABLE_PT_NEG_08		0x04f5		//�������¶�Դ���ѯ��-08���϶�
#define TABLE_PT_NEG_07		0x04f8		//�������¶�Դ���ѯ��-07���϶�
#define TABLE_PT_NEG_06		0x04fb		//�������¶�Դ���ѯ��-06���϶�
#define TABLE_PT_NEG_05		0x04ff		//�������¶�Դ���ѯ��-05���϶�
#define TABLE_PT_NEG_04		0x0502		//�������¶�Դ���ѯ��-04���϶�
#define TABLE_PT_NEG_03		0x0506		//�������¶�Դ���ѯ��-03���϶�
#define TABLE_PT_NEG_02		0x0509		//�������¶�Դ���ѯ��-02���϶�
#define TABLE_PT_NEG_01		0x050c		//�������¶�Դ���ѯ��-01���϶�
#define TABLE_PT_MID_00		0x0510		//�������¶�Դ���ѯ��-00���϶�
#define TABLE_PT_POS_01		0x0513		//�������¶�Դ���ѯ��+01���϶�
#define TABLE_PT_POS_02		0x0516		//�������¶�Դ���ѯ��+02���϶�
#define TABLE_PT_POS_03		0x051a		//�������¶�Դ���ѯ��+03���϶�
#define TABLE_PT_POS_04		0x051d		//�������¶�Դ���ѯ��+04���϶�
#define TABLE_PT_POS_05		0x0521		//�������¶�Դ���ѯ��+05���϶�
#define TABLE_PT_POS_06		0x0524		//�������¶�Դ���ѯ��+06���϶�
#define TABLE_PT_POS_07		0x0527		//�������¶�Դ���ѯ��+07���϶�
#define TABLE_PT_POS_08		0x052a		//�������¶�Դ���ѯ��+08���϶�
#define TABLE_PT_POS_09		0x052e		//�������¶�Դ���ѯ��+09���϶�
#define TABLE_PT_POS_10		0x0531		//�������¶�Դ���ѯ��+10���϶�
#define TABLE_PT_POS_11		0x0534		//�������¶�Դ���ѯ��+11���϶�
#define TABLE_PT_POS_12		0x0538		//�������¶�Դ���ѯ��+12���϶�
#define TABLE_PT_POS_13		0x053b		//�������¶�Դ���ѯ��+13���϶�
#define TABLE_PT_POS_14		0x053e		//�������¶�Դ���ѯ��+14���϶�
#define TABLE_PT_POS_15		0x0541		//�������¶�Դ���ѯ��+15���϶�
#define TABLE_PT_POS_16		0x0545		//�������¶�Դ���ѯ��+16���϶�
#define TABLE_PT_POS_17		0x0548		//�������¶�Դ���ѯ��+17���϶�
#define TABLE_PT_POS_18		0x054b		//�������¶�Դ���ѯ��+18���϶�
#define TABLE_PT_POS_19		0x054e		//�������¶�Դ���ѯ��+19���϶�
#define TABLE_PT_POS_20		0x0551		//�������¶�Դ���ѯ��+20���϶�
#define TABLE_PT_POS_21		0x0555		//�������¶�Դ���ѯ��+21���϶�
#define TABLE_PT_POS_22		0x0558		//�������¶�Դ���ѯ��+22���϶�
#define TABLE_PT_POS_23		0x055b		//�������¶�Դ���ѯ��+23���϶�
#define TABLE_PT_POS_24		0x055e		//�������¶�Դ���ѯ��+24���϶�
#define TABLE_PT_POS_25		0x0561		//�������¶�Դ���ѯ��+25���϶�
#define TABLE_PT_POS_26		0x0564		//�������¶�Դ���ѯ��+26���϶�
#define TABLE_PT_POS_27		0x0568		//�������¶�Դ���ѯ��+27���϶�
#define TABLE_PT_POS_28		0x056b		//�������¶�Դ���ѯ��+28���϶�
#define TABLE_PT_POS_29		0x056e		//�������¶�Դ���ѯ��+29���϶�
#define TABLE_PT_POS_30		0x0571		//�������¶�Դ���ѯ��+30���϶�
#define TABLE_PT_POS_31		0x0574		//�������¶�Դ���ѯ��+31���϶�
#define TABLE_PT_POS_32		0x0577		//�������¶�Դ���ѯ��+32���϶�
#define TABLE_PT_POS_33		0x057a		//�������¶�Դ���ѯ��+33���϶�
#define TABLE_PT_POS_34		0x057d		//�������¶�Դ���ѯ��+34���϶�
#define TABLE_PT_POS_35		0x0581		//�������¶�Դ���ѯ��+35���϶�
#define TABLE_PT_POS_36		0x0584		//�������¶�Դ���ѯ��+36���϶�
#define TABLE_PT_POS_37		0x0587		//�������¶�Դ���ѯ��+37���϶�
#define TABLE_PT_POS_38		0x058a		//�������¶�Դ���ѯ��+38���϶�
#define TABLE_PT_POS_39		0x058d		//�������¶�Դ���ѯ��+39���϶�
#define TABLE_PT_POS_40		0x0590		//�������¶�Դ���ѯ��+40���϶�
#define TABLE_PT_POS_41		0x0593		//�������¶�Դ���ѯ��+41���϶�
#define TABLE_PT_POS_42		0x0596		//�������¶�Դ���ѯ��+42���϶�
#define TABLE_PT_POS_43		0x0599		//�������¶�Դ���ѯ��+43���϶�
#define TABLE_PT_POS_44		0x059c		//�������¶�Դ���ѯ��+44���϶�
#define TABLE_PT_POS_45		0x059f		//�������¶�Դ���ѯ��+45���϶�
#define TABLE_PT_POS_46		0x05a2		//�������¶�Դ���ѯ��+46���϶�
#define TABLE_PT_POS_47		0x05a5		//�������¶�Դ���ѯ��+47���϶�
#define TABLE_PT_POS_48		0x05a8		//�������¶�Դ���ѯ��+48���϶�
#define TABLE_PT_POS_49		0x05ab		//�������¶�Դ���ѯ��+49���϶�
#define TABLE_PT_POS_50		0x05ae		//�������¶�Դ���ѯ��+50���϶�
#define TABLE_PT_POS_51		0x05b1		//�������¶�Դ���ѯ��+51���϶�
#define TABLE_PT_POS_52		0x05b4		//�������¶�Դ���ѯ��+52���϶�
#define TABLE_PT_POS_53		0x05b7		//�������¶�Դ���ѯ��+53���϶�
#define TABLE_PT_POS_54		0x05ba		//�������¶�Դ���ѯ��+54���϶�
#define TABLE_PT_POS_55		0x05bd		//�������¶�Դ���ѯ��+55���϶�
#define TABLE_PT_POS_56		0x05c0		//�������¶�Դ���ѯ��+56���϶�
#define TABLE_PT_POS_57		0x05c3		//�������¶�Դ���ѯ��+57���϶�
#define TABLE_PT_POS_58		0x05c5		//�������¶�Դ���ѯ��+58���϶�
#define TABLE_PT_POS_59		0x05c8		//�������¶�Դ���ѯ��+59���϶�
#define TABLE_PT_POS_60		0x05cb		//�������¶�Դ���ѯ��+60���϶�
#define TABLE_PT_POS_61		0x05ce		//�������¶�Դ���ѯ��+61���϶�
#define TABLE_PT_POS_62		0x05d1		//�������¶�Դ���ѯ��+62���϶�
#define TABLE_PT_POS_63		0x05d4		//�������¶�Դ���ѯ��+63���϶�
#define TABLE_PT_POS_64		0x05d7		//�������¶�Դ���ѯ��+64���϶�
#define TABLE_PT_POS_65		0x05da		//�������¶�Դ���ѯ��+65���϶�
#define TABLE_PT_POS_66		0x05dd		//�������¶�Դ���ѯ��+66���϶�
#define TABLE_PT_POS_67		0x05df		//�������¶�Դ���ѯ��+67���϶�
#define TABLE_PT_POS_68		0x05e2		//�������¶�Դ���ѯ��+68���϶�
#define TABLE_PT_POS_69		0x05e5		//�������¶�Դ���ѯ��+69���϶�
#define TABLE_PT_POS_70		0x05e8		//�������¶�Դ���ѯ��+70���϶�





#define TEMP_MF51_NEG_50 	TABLE_MF51_NEG_50//MF51,-50���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_NEG_40	TABLE_MF51_NEG_40//MF51,-40���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_NEG_30	TABLE_MF51_NEG_30//MF51,-30���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_NEG_20	TABLE_MF51_NEG_20//MF51,-20���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_NEG_10	TABLE_MF51_NEG_10//MF51,-10���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_MID_0		TABLE_MF51_MID_00//MF51,0���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_10	TABLE_MF51_POS_10//MF51,10���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_20	TABLE_MF51_POS_20//MF51,20���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_30	TABLE_MF51_POS_30//MF51,30���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_40	TABLE_MF51_POS_40//MF51,40���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_50	TABLE_MF51_POS_50//MF51,50���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_60	TABLE_MF51_POS_60//MF51,60���϶ȶ�ӦԴ��ֵ
#define TEMP_MF51_POS_70	TABLE_MF51_POS_70//MF51,70���϶ȶ�ӦԴ��ֵ


#define TEMP_MF61_NEG_50 	TABLE_MF61_NEG_50//MF61,-50���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_NEG_40	TABLE_MF61_NEG_40//MF61,-40���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_NEG_30	TABLE_MF61_NEG_30//MF61,-30���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_NEG_20	TABLE_MF61_NEG_20//MF61,-20���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_NEG_10	TABLE_MF61_NEG_10//MF61,-10���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_MID_0		TABLE_MF61_MID_00//MF61,0���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_10	TABLE_MF61_POS_10//MF61,10���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_20	TABLE_MF61_POS_20//MF61,20���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_30	TABLE_MF61_POS_30//MF61,30���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_40	TABLE_MF61_POS_40//MF61,40���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_50	TABLE_MF61_POS_50//MF61,50���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_60	TABLE_MF61_POS_60//MF61,60���϶ȶ�ӦԴ��ֵ
#define TEMP_MF61_POS_70	TABLE_MF61_POS_70//MF61,70���϶ȶ�ӦԴ��ֵ


#define TEMP_PT_NEG_50 		TABLE_PT_NEG_50//������,-50���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_NEG_40		TABLE_PT_NEG_40//������,-40���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_NEG_30		TABLE_PT_NEG_30//������,-30���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_NEG_20		TABLE_PT_NEG_20//������,-20���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_NEG_10		TABLE_PT_NEG_10//������,-10���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_MID_0		TABLE_PT_MID_00//������,0���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_10		TABLE_PT_POS_10//������,10���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_20		TABLE_PT_POS_20//������,20���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_30		TABLE_PT_POS_30//������,30���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_40		TABLE_PT_POS_40//������,40���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_50		TABLE_PT_POS_50//������,50���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_60		TABLE_PT_POS_60//������,60���϶ȶ�ӦԴ��ֵ
#define TEMP_PT_POS_70		TABLE_PT_POS_70//������,70���϶ȶ�ӦԴ��ֵ



/*��������--------------------------------------------------------------------*/

void TGTHT510_tempercontrol_initial(void);
uint16 TGTHT510_tempercontrol_mf51_to_mf61(uint16 temp_mf51);
uint16 TGTHT510_tempercontrol_mf51_range_calculate(uint16 temp_mf51);
uint16 TGTHT510_tempercontrol_mf51_sourcecode_to_centigrade_calculate(uint16 temp_mf51,uint16 range);
uint16 TGTHT510_tempercontrol_mf51_centigrade_num_calculate(uint16 start_i,uint16 temp_mf51);
uint16 TGTHT510_tempercontrol_pt_to_mf61(uint16 temp_pt);
uint16 TGTHT510_tempercontrol_pt_range_calculate(uint16 temp_pt);
uint16 TGTHT510_tempercontrol_pt_centigrade_num_calculate(uint16 start_i,uint16 temp_pt);
uint16 TGTHT510_tempercontrol_pt_sourcecode_to_centigrade_calculate(uint16 temp_pt,uint16 range);
void TGTHT510_tempercontrol_valid_data_generate(uint16 type);
void TGTHT510_tempercontrol_valid_data_from_TGTHT100(void);
void TGTHT510_tempercontrol_valid_data_from_TGTHT100_fixed_control(uint16 num);
void TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control(uint16 num);
Temperature_control_temp_TypeDef TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control_source_data(uint16 num);
uint16 TGTHT510_tempercontrol_valid_data_from_TGTHT100_auto_control_source_data_sort(Temperature_control_temp_TypeDef d);
void TGTHT510_tempercontrol_valid_data_from_TGTHT100_sort(void);
void TGTHT510_tempercontrol_reg_output(void);
void TGTHT510_tempercontrol_reg_setbit(uint16 num,uint16 type);
void TGTHT510_tempercontrol_reg_clear(void);
uint16 TGTHT510_tempercontrol_power_calculate(uint16 num,uint16 type);
uint16 TGTHT510_tempercontrol_9s_flag(void);
void TGTHT510_tempercontrol_main(void);
uint16 TGTHT510_tempercontrol_fixed_control_count_update(void);
uint16 TGTHT510_tempercontrol_fixed_control(uint16 max_power);
uint16 TGTHT510_tempercontrol_auto_control(uint16 max_power);
uint16 TGTHT510_tempercontrol_auto_control_temper_range(uint16 num,uint16 temper);
void TGTHT510_tempercontrol_supply_is_auto_control(uint16 mode);



#endif 
  















  
  
  
