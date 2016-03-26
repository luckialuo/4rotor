#ifndef _TIME_H
#define _TIME_H

#include "mpc5534.h"

extern   unsigned long    timetick;    
extern   unsigned char    tag_200us;
extern   unsigned char    tag_1ms;
extern   unsigned char    tag_2ms;
extern   unsigned char    tag_4ms;
extern   unsigned char    tag_5ms;
extern   unsigned char    tag_10ms;
extern   unsigned char    tag_15ms;
extern   unsigned char    tag_20ms;
extern   unsigned char    tag_40ms;
extern   unsigned char    tag_50ms;
extern   unsigned char    tag_80ms;
extern   unsigned char    tag_100ms;
extern   unsigned char    tag_125ms;
extern   unsigned char    tag_200ms;
extern   unsigned char    tag_500ms;
extern   unsigned char    tag_600ms;
extern   unsigned char    tag_1s;
extern   unsigned char    tag_2s;
extern   unsigned short   CPULoad;
extern   unsigned short   IdleCount;
extern   unsigned long    time_cnt;

void clr_time_flag(void);
void clr_wd_status(void);
void time_init(void);
void time_isr(void);
void watchdog_enable(void);
void watchdog_disable(void);


#endif

