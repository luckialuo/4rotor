#include "startup\includes.h"


unsigned long    timetick=1;    
unsigned char    tag_200us;
unsigned char    tag_1ms;
unsigned char    tag_2ms;
unsigned char    tag_4ms;
unsigned char    tag_5ms;
unsigned char    tag_10ms;
unsigned char    tag_15ms;
unsigned char    tag_20ms;
unsigned char    tag_40ms;
unsigned char    tag_50ms;
unsigned char    tag_80ms;
unsigned char    tag_100ms;
unsigned char    tag_125ms;
unsigned char    tag_200ms;
unsigned char    tag_500ms;
unsigned char    tag_600ms;
unsigned char    tag_1s;
unsigned char    tag_2s;
unsigned short   CPULoad;
unsigned short   IdleCount=1L;
unsigned long    time_cnt;

/****************************************************************************
* 名称：time_init
* 功能：定时器初始化
* 入口参数：无
* 出口参数：无
* 返回值：无
* 备注：无
****************************************************************************/ 

asm void time_init(void) {
  li		r0, 0		       	/* Initialize time base to 0  */
  mttbu		r0					  
  mttbl		r0	
  lis		r0, 0x0001		/* Load initial DEC value of 80000  1ms*/
  ori		r0, r0, 0x387F
  mtdec		r0
  mtdecar	r0				/* Load same initial value to DECAR	 */
  lis		r0, 0x0440		/* Enable DEC interrupt and auto-reload	*/
//  lis		r0, 0xA452		/* Enable DEC interrupt and auto-reload	WDT 0.8388608S*/
  ori		r0, r0,0x0
  mttcr		r0
  li		r0, 0x4000		  	/* Enable Time Base and Decrementer (set TBEN) */
  mthid0	r0
}

asm void clr_time_flag(void) {
  lis		r0, 0x0800
  mttsr		r0 				/* Write "1" clear DEC Interrupt Status flag */
}


asm void watchdog_enable(void)
{
	
  lis		r0, 0xA452		
  ori		r0, r0,0x0
  mttcr		r0	
	
}


asm void watchdog_disable(void)
{
	
    lis		r0, 0x0440	
    ori		r0, r0,0x0
    mttcr		r0		
	
}



asm void clr_wd_status(void)
{
   // prevent a watchdog timeout reset by writing TSR[WIS] with 1 (clears the bit)
  lis  r0, 0x4000 //load r6 with TSR[WIS] bit (bit 1)
  mttsr  r0  // move the val back to TSR
}

/****************************************************************************
* 名称：time_isr
* 功能：定时器中断函数
* 入口参数：无
* 出口参数：无
* 返回值：无
* 备注：无
****************************************************************************/ 

void time_isr (void)
{


    
   clr_time_flag();
   timetick=(timetick+1)%(50000*60); 
                              tag_1ms   = 1;
                              
    time_cnt++;time_cnt%=1000000000; 
                              
                              
    if ((timetick % 2 ) == 0)	tag_2ms  = 1;
    if ((timetick % 4 ) == 0)	tag_4ms  = 1; 
    if ((timetick % 5 ) == 0)	tag_5ms  = 1;                          
	if ((timetick % 10 ) == 0)	tag_10ms  = 1;
	if ((timetick % 15 ) == 0)	tag_15ms  = 1;
	if ((timetick % 20 ) == 0)	tag_20ms  = 1;
	if ((timetick % 40  ) == 0)	tag_40ms  = 1;
	if ((timetick % 50 ) == 0)	tag_50ms  = 1;
	if ((timetick % 80 ) == 0)	tag_80ms  = 1;
	if ((timetick % 100 ) == 0)	tag_100ms = 1;
	if ((timetick % 125 ) == 0)	tag_125ms = 1;
	if ((timetick % 200 ) == 0)	tag_200ms = 1;
	if ((timetick % 500) == 0) { tag_500ms = 1; CPULoad=(unsigned short)(50000L/IdleCount); IdleCount=1; } 
    if ((timetick % 600) == 0)   tag_600ms = 1;
	if ((timetick % 1000) == 0){ tag_1s    = 1;}
	if ((timetick % 2000) == 0)	tag_2s    = 1;      
	
    
}


