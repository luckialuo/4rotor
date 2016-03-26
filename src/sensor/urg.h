/*
 * Copyright(C) 2013 Airmud UAV Lab. All rights reserved.
 */
/*
 * urg.h
 * Original Author: wwb@stu.xmu.edu.cn, 2013-6-21
 *
 * �ɿذ�֮�������ͨѶ
 *
 * History
 *     V1.0 
 */
 
 #ifndef _URG_H_
 #define _URG_H_
 
 typedef struct 
 {
    unsigned char urg_head[2];   /* ֡ͷ */
    unsigned char urg_mode;      /* ģʽ */
    short urg_dL;                          /* URG���ɾ� */
    short urg_dZ;                          /* URG��ƫ�� */
    short urg_dPsi;                       /* URGƫ���� */
    short urg_ddL;                        /* URGǰ��������� */
    short urg_ddZ;                        /* URG�����ƶ����� */
    short urg_front_point;             /* URG��ǰ���ϰ������ */
    short urg_left_point;                /* URG�����ϰ������ */
    short urg_right_point;              /* URG���ҷ��ϰ������ */
    unsigned char urg_buf[20];     /* ������䣬��֤�ṹ��ռ�Ϊ40�ֽ� */
    unsigned char urg_sum;         /* ��У��λ */
}urg_deal_data_type;
 
typedef union
{
    urg_deal_data_type urg_deal_data;
    unsigned char buf[40];
}urg_deal_union_type;
 
extern urg_deal_union_type urg_deal_union;
extern SensorStruc          urg04lx;

void Task_UrgRev();
void URG_Monitor();

 #endif /*  #ifndef _URG_H_ */
 