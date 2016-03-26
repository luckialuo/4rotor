/*
 * Copyright(C) 2013 Airmud UAV Lab. All rights reserved.
 */
/*
 * urg.c
 * Original Author: wwb@stu.xmu.edu.cn, 2013-6-21
 *
 * 飞控板之间的数据通讯
 *
 * History
 *     V1.0 
 */
 
#include "MPC.h"

urg_deal_union_type urg_deal_union;
SensorStruc          urg04lx;

void  Task_UrgRev(void)
{
    volatile  static  BYTE    buf[256], head = 0, tail = 0, tmp = 0;
    static               BYTE    ptr, len, check, FCCdata[40];
    static               int          RxQueLen,  numread,  idx;

    RxQueLen=UartCom2RxLen();
    numread=RxQueLen>40?40:RxQueLen;
    if (numread) {
        UartCom2In(FCCdata, numread);  
        for (idx = 0; idx < numread; idx++) {
            buf[head++] = FCCdata[idx];
        }
    }
    
    len = head - tail;
    while (len >= sizeof(FCCdata)) {
        tmp = tail + 1;
        if ((buf[tail] == 0xEB) && (buf[tail + 1] == 0x90)) {
            ptr = tail;
            for (idx = 0; idx < sizeof(FCCdata); idx++) {
                FCCdata[idx] = buf[ptr++];
            }
            check = 0;
            for(idx = 0; idx < sizeof(FCCdata); idx++) {
                check += FCCdata[idx];
            }
            if (check == 0) {
                memcpy(urg_deal_union.buf, FCCdata, sizeof(urg_deal_union.buf));
                urg04lx.invalid = urg04lx.fail = 0; 
                urg04lx.counter++;
                tail += sizeof(FCCdata);
                fusion_slow(); /* 更新数据 */				
            } else {
                tail ++;
            }
        } else {
            tail ++;
        }
        len=head-tail;
    }
}

void URG_Monitor(void) 
{
    static INT16U     flag=0, cnt=0, old=0;

    urg04lx.invalid += 1;
    if (urg04lx.invalid >= 5) {
        urg04lx.fail = 1;
    }
    cnt = (cnt + 1) % 100;
    if ((cnt%10) == 0) flag = 1;
    if (flag) {  
        flag = 0;
        urg04lx.freq = urg04lx.counter - old;
        old = urg04lx.counter;
    }
}
