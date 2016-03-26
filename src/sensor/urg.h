/*
 * Copyright(C) 2013 Airmud UAV Lab. All rights reserved.
 */
/*
 * urg.h
 * Original Author: wwb@stu.xmu.edu.cn, 2013-6-21
 *
 * 飞控板之间的数据通讯
 *
 * History
 *     V1.0 
 */
 
 #ifndef _URG_H_
 #define _URG_H_
 
 typedef struct 
 {
    unsigned char urg_head[2];   /* 帧头 */
    unsigned char urg_mode;      /* 模式 */
    short urg_dL;                          /* URG待飞距 */
    short urg_dZ;                          /* URG侧偏距 */
    short urg_dPsi;                       /* URG偏航角 */
    short urg_ddL;                        /* URG前向飞行速率 */
    short urg_ddZ;                        /* URG侧向移动速率 */
    short urg_front_point;             /* URG正前方障碍物距离 */
    short urg_left_point;                /* URG正左方障碍物距离 */
    short urg_right_point;              /* URG正右方障碍物距离 */
    unsigned char urg_buf[20];     /* 数据填充，保证结构体空间为40字节 */
    unsigned char urg_sum;         /* 和校验位 */
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
 