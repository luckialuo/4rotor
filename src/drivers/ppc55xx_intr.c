#include "startup\includes.h"


/****************************************************************************
* 名称：intInit
* 功能：中断初始化
* 入口参数：无
* 出口参数：无
* 返回值：无
* 备注：无
****************************************************************************/ 

void intInit(void)
{
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)UartInterrupt2Rx,ETPUA21_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)UartInterrupt2Tx,ETPUA17_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)UartInterrupt3Rx,ETPUA22_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)UartInterrupt3Tx,ETPUA29_INT_VECTOR,1); 
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)UartInterrupt4Rx,ETPUA14_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)UartInterrupt4Tx,ETPUA19_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)UartInterrupt5Rx,ETPUA6_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)UartInterrupt5Tx,ETPUA11_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)UartInterrupt6Rx,ETPUA9_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)UartInterrupt6Tx,ETPUA1_INT_VECTOR,1); 
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)UartInterrupt7Rx,ETPUA15_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)UartInterrupt7Tx,ETPUA7_INT_VECTOR,1);
        
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)PPC_Com1InterruptHandler,ESCIA_INT_VECTOR,1);    
    
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)EMIOS0Interrupt,EMIOS0_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)EMIOS1Interrupt,EMIOS1_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)EMIOS2Interrupt,EMIOS2_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)EMIOS3Interrupt,EMIOS3_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)EMIOS4Interrupt,EMIOS4_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)EMIOS5Interrupt,EMIOS5_INT_VECTOR,1); 
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)EMIOS6Interrupt,EMIOS6_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)EMIOS7Interrupt,EMIOS7_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)EMIOS8Interrupt,EMIOS8_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)EMIOS9Interrupt,EMIOS9_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)EMIOS10Interrupt,EMIOS10_INT_VECTOR,1);
    INTC_InstallINTCInterruptHandler((INTCInterruptFn)EMIOS13Interrupt,EMIOS13_INT_VECTOR,1);

}

void enableIrq(void) {
/* Use one of the following two lines to lower the INTC current priority */
    INTC.CPR.B.PRI = 0;	       /* MPC555x: Lower INTC's current priority */
    asm(" wrteei 1");	    	   /* Enable external interrupts */
}


void disableIrq(void)
{	
	asm(" wrteei 0");	    	   /* Enable external interrupts */
}

void initPll(void)
{
	FMPLL.SYNCR.R = 0x03080000;         
    while (FMPLL.SYNSR.B.LOCK != 1) {}; /* Wait for FMPLL to LOCK  */
    FMPLL.SYNCR.R = 0x03000000;         
}

/****************************************************************************
* 名称：dec2num_matrix
* 功能：64位整型 (IEEE double 格式) 转 浮点 
* 入口参数：*d--64位整型
* 出口参数：无
* 返回值：转出的浮点值
* 备注：无
****************************************************************************/ 

double dec2num_matrix(const decimalt *d)
{
double factorial[24]={0.5, 0.25, 0.125, 0.0625,       
                      0.03125, 0.015625, 0.0078125,
                      0.00390625,  0.001953125,
                      0.0009765625, 0.00048828125,
                      0.000244140625, 0.0001220703125, 0.00006103515625,
                      0.000030517578125, 0.0000152587890625,0.00000762939453125,
                      0.000003814697265625, 0.0000019073486328125,
                      0.00000095367431640625, 0.000000476837158203125,
                      0.0000002384185791015625, 0.000000119209289555078125,
                      0.000000059604644775390625};
   double value = 0.0;                         
   double temp[2]={1.0, 0.0};
   unsigned char bit;
   long exponent=0;
   long i;
   
   
   exponent=(d->UW[0]&0x7ff0)>>4;
   exponent=exponent-1023;
   if(exponent<0)
   {
    exponent=-exponent;
    for(i=0;i<exponent;i++)
    temp[0]=temp[0]/2;
   }
   
   else
   {
     for(i=0;i<exponent;i++)    
        temp[0]=temp[0]*2;      
   }
  
  
   for(i=0;i<20;i++)
   {
     bit=((d->DW[0]>>i)&0x1);
     temp[1]=temp[1]+bit*factorial[19-i];
   }
   for(i=28;i<32;i++)
   {
     bit=((d->DW[1]>>i)&0x1);
       temp[1]=temp[1]+bit*factorial[51-i];
    
   }
   
    value = (1+temp[1])*temp[0];
    if((d->B[0]&0x80) ==0x80)          //判断正负  首位1负 0正
      return(-value);
    else
      return(value);
}


