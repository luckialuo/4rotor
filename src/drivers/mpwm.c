#include "startup\includes.h"


static float  unittime = 0;
#define CLOCKPRESCALE  80    
#define PWMINHIGHOFFSET 4
#define PWMOUTHIGHOFFSET 4

mpwm_t  MPWMIN[6];
mpwm_t  MPWMOUT[12];


/****************************************************************************
* 名称：MpwmInit
* 功能：板载PWM初始化(包含周期和高电平时间)
* 入口参数：无
* 出口参数：无
* 返回值：无
* 备注：底板PWM输入输出，1M的采样频率
****************************************************************************/ 

void MpwmInit()
{
    unsigned char i;

    EMIOS.MCR.B.GPRE= (CLOCKPRESCALE-1);      /* Divide 80 MHz sysclk by 79 +1 = 80 for 1MHz eMIOS clk*/
    EMIOS.MCR.B.ETB = 0;                      /* External time base is disabled; Ch 23 drives ctr bus A */
    EMIOS.MCR.B.GPREN = 1;   	              /* Enable eMIOS clock */
    EMIOS.MCR.B.GTBE = 1;		              /* Enable global time base */
    EMIOS.MCR.B.FRZ = 0;		              /* Disable stopping channels when in debug mode */
     
    unittime = 1000.0f*CLOCKPRESCALE/SYS_CLOCK_FREQ; 

   
    for(i=MPWMOUTCH1;i<=MPWMOUTCH12;i++)
    {
        MpwmOutDisable(i);
    	MPWMOUT[i].pwmper =  10;    /*unit-- ms*/ 
        MPWMOUT[i].pwmhi  = 1.5;
        MpwmOutInit(i);
        MpwmOutEnable(i);
    } 
    
    for(i=MPWMINCH1;i<=MPWMINCH6;i++)
    {
        MpwmInDisable(i);
        MpwmInInit(i);
        MpwmInEnable(i);
    } 
    
}


/****************************************************************************
* 名称：MpwmOutEnable
* 功能：板载PWM输出使能
* 入口参数：channel--通道号
* 出口参数：无
* 返回值：0--OK,-1--ERROR
* 备注：底板PWM输出
****************************************************************************/ 

int MpwmOutEnable(unsigned char channel)
{
   if(channel>11)
	  return(-1);
   
    switch(channel)	
    {
    	
        case 0:  EMIOS.CH[0].CCR.B.UCPREN  = 1;
                 break;
    	
    	case 1:  EMIOS.CH[1].CCR.B.UCPREN  = 1;
                 break;
                  
        case 2:  EMIOS.CH[2].CCR.B.UCPREN  = 1;
                 break;
                 
        case 3:  EMIOS.CH[3].CCR.B.UCPREN  = 1;
                 break;
                 
        case 4:  EMIOS.CH[4].CCR.B.UCPREN  = 1;
                 break;                 
                 
        case 5:  EMIOS.CH[5].CCR.B.UCPREN  = 1;
                 break;
                
        case 6:  EMIOS.CH[6].CCR.B.UCPREN  = 1;
                 break;
    	
    	case 7:  EMIOS.CH[7].CCR.B.UCPREN  = 1;
                 break;
                  
        case 8:  EMIOS.CH[8].CCR.B.UCPREN  = 1;
                 break;
                 
        case 9:  EMIOS.CH[9].CCR.B.UCPREN  = 1;
                 break;
                 
        case 10: EMIOS.CH[10].CCR.B.UCPREN = 1;
                 break;                 
                 
        case 11: EMIOS.CH[13].CCR.B.UCPREN = 1;
                 break;
                 
        default: break;  
    	
    }
	
	return(0);
	
}


/****************************************************************************
* 名称：MpwmOutDisable
* 功能：板载PWM输出禁止
* 入口参数：channel--通道号
* 出口参数：无
* 返回值：0--OK,-1--ERROR
* 备注：底板PWM输出
****************************************************************************/ 


int MpwmOutDisable(unsigned char channel)
{
	if(channel>11)
	  return(-1);
   
    switch(channel)	
    {
    	
        case 0:  EMIOS.CH[0].CCR.B.UCPREN  = 0;
                 break;
    	
    	case 1:  EMIOS.CH[1].CCR.B.UCPREN  = 0;
                 break;
                  
        case 2:  EMIOS.CH[2].CCR.B.UCPREN  = 0;
                 break;
                 
        case 3:  EMIOS.CH[3].CCR.B.UCPREN  = 0;
                 break;
                 
        case 4:  EMIOS.CH[4].CCR.B.UCPREN  = 0;
                 break;                 
                 
        case 5:  EMIOS.CH[5].CCR.B.UCPREN  = 0;
                 break;
                
        case 6:  EMIOS.CH[6].CCR.B.UCPREN  = 0;
                 break;
    	
    	case 7:  EMIOS.CH[7].CCR.B.UCPREN  = 0;
                 break;
                  
        case 8:  EMIOS.CH[8].CCR.B.UCPREN  = 0;
                 break;
                 
        case 9:  EMIOS.CH[9].CCR.B.UCPREN  = 0;
                 break;
                 
        case 10: EMIOS.CH[10].CCR.B.UCPREN = 0;
                 break;                 
                 
        case 11: EMIOS.CH[13].CCR.B.UCPREN = 0;
                 break;
                 
        default: break;  
    	
    }
	
	return(0);
	
}

/*****************************pwm的输出******************************************************/
/****************************************************************************
* 名称：MpwmOutInit
* 功能：板载PWM对应通道初始化(包含周期和高电平时间)
* 入口参数：channel--通道号
* 出口参数：无
* 返回值：0--OK,-1--ERROR
* 备注：底板PWM输出
****************************************************************************/ 


int MpwmOutInit(unsigned char channel)
{

	unsigned long temp;
	
	if(channel>11)
	  return(-1);
	
	switch(channel)	
    {
    	
        case 0:  temp = (unsigned long)(MPWMOUT[0].pwmper/unittime+0.5);
                 EMIOS.CH[0].CBDR.R  = temp;
                 temp = (unsigned long)(MPWMOUT[0].pwmhi/unittime+0.5)+PWMOUTHIGHOFFSET;
                 EMIOS.CH[0].CADR.R   = temp;
                 EMIOS.CH[0].CCR.B.UCPRE = 0;
                 EMIOS.CH[0].CCR.B.EDPOL = 1;
                 EMIOS.CH[0].CCR.B.MODE= 0x19;
                 EMIOS.CH[0].CCR.B.FEN=0x1; 
                 SIU.PCR[179].R = 0xE00; 
                 break;
    	
    	case 1:  temp = (unsigned long)(MPWMOUT[1].pwmper/unittime+0.5);
                 EMIOS.CH[1].CBDR.R   = temp;
                 temp = (unsigned long)(MPWMOUT[1].pwmhi/unittime+0.5)+PWMOUTHIGHOFFSET;
                 EMIOS.CH[1].CADR.R   = temp;
                 EMIOS.CH[1].CCR.B.UCPRE = 0;
                 EMIOS.CH[1].CCR.B.EDPOL = 1;
                 EMIOS.CH[1].CCR.B.MODE= 0x19;
                 EMIOS.CH[1].CCR.B.FEN=0x1; 
                 SIU.PCR[180].R = 0xE00;
                 break;
                  
        case 2:  temp = (unsigned long)(MPWMOUT[2].pwmper/unittime+0.5);
                 EMIOS.CH[2].CBDR.R   = temp;
                 temp = (unsigned long)(MPWMOUT[2].pwmhi/unittime+0.5)+PWMOUTHIGHOFFSET;
                 EMIOS.CH[2].CADR.R   = temp;
                 EMIOS.CH[2].CCR.B.UCPRE = 0;
                 EMIOS.CH[2].CCR.B.EDPOL = 1;
                 EMIOS.CH[2].CCR.B.MODE= 0x19;
                 EMIOS.CH[2].CCR.B.FEN=0x1; 
                 SIU.PCR[181].R = 0xE00;
                 break;
                 
        case 3:  temp = (unsigned long)(MPWMOUT[3].pwmper/unittime+0.5);
                 EMIOS.CH[3].CBDR.R   = temp;
                 temp = (unsigned long)(MPWMOUT[3].pwmhi/unittime+0.5)+PWMOUTHIGHOFFSET;
                 EMIOS.CH[3].CADR.R   = temp;
                 EMIOS.CH[3].CCR.B.UCPRE = 0;
                 EMIOS.CH[3].CCR.B.EDPOL = 1;
                 EMIOS.CH[3].CCR.B.MODE= 0x19;
                 EMIOS.CH[3].CCR.B.FEN=0x1; 
                 SIU.PCR[182].R = 0xE00;
                 break;
                 
        case 4:  temp = (unsigned long)(MPWMOUT[4].pwmper/unittime+0.5);
                 EMIOS.CH[4].CBDR.R   = temp;
                 temp = (unsigned long)(MPWMOUT[4].pwmhi/unittime+0.5)+PWMOUTHIGHOFFSET;
                 EMIOS.CH[4].CADR.R   = temp;
                 EMIOS.CH[4].CCR.B.UCPRE = 0;
                 EMIOS.CH[4].CCR.B.EDPOL = 1;
                 EMIOS.CH[4].CCR.B.MODE= 0x19;
                 EMIOS.CH[4].CCR.B.FEN=0x1; 
                 SIU.PCR[183].R = 0xE00;
                 break;                 
                 
        case 5:  temp = (unsigned long)(MPWMOUT[5].pwmper/unittime+0.5);
                 EMIOS.CH[5].CBDR.R  = temp;
                 temp = (unsigned long)(MPWMOUT[5].pwmhi/unittime+0.5)+PWMOUTHIGHOFFSET;
                 EMIOS.CH[5].CADR.R   = temp;
                 EMIOS.CH[5].CCR.B.UCPRE = 0;
                 EMIOS.CH[5].CCR.B.EDPOL = 1;
                 EMIOS.CH[5].CCR.B.MODE= 0x19;
                 EMIOS.CH[5].CCR.B.FEN=0x1; 
                 SIU.PCR[184].R = 0xE00;
                 break; 
                 
        case 6:  temp = (unsigned long)(MPWMOUT[6].pwmper/unittime+0.5);
                 EMIOS.CH[6].CBDR.R  = temp;
                 temp = (unsigned long)(MPWMOUT[6].pwmhi/unittime+0.5)+PWMOUTHIGHOFFSET;
                 EMIOS.CH[6].CADR.R   = temp;
                 EMIOS.CH[6].CCR.B.UCPRE = 0;
                 EMIOS.CH[6].CCR.B.EDPOL = 1;
                 EMIOS.CH[6].CCR.B.MODE= 0x19;
                 EMIOS.CH[6].CCR.B.FEN=0x1; 
                 SIU.PCR[185].R = 0xE00; 
                 break;
    	
    	case 7:  temp = (unsigned long)(MPWMOUT[7].pwmper/unittime+0.5);
                 EMIOS.CH[7].CBDR.R   = temp;
                 temp = (unsigned long)(MPWMOUT[7].pwmhi/unittime+0.5)+PWMOUTHIGHOFFSET;
                 EMIOS.CH[7].CADR.R   = temp;
                 EMIOS.CH[7].CCR.B.UCPRE = 0;
                 EMIOS.CH[7].CCR.B.EDPOL = 1;
                 EMIOS.CH[7].CCR.B.MODE= 0x19;
                 EMIOS.CH[7].CCR.B.FEN=0x1; 
                 SIU.PCR[186].R = 0xE00;
                 break;
                  
        case 8:  temp = (unsigned long)(MPWMOUT[8].pwmper/unittime+0.5);
                 EMIOS.CH[8].CBDR.R   = temp;
                 temp = (unsigned long)(MPWMOUT[8].pwmhi/unittime+0.5)+PWMOUTHIGHOFFSET;
                 EMIOS.CH[8].CADR.R   = temp;
                 EMIOS.CH[8].CCR.B.UCPRE = 0;
                 EMIOS.CH[8].CCR.B.EDPOL = 1;
                 EMIOS.CH[8].CCR.B.MODE= 0x19;
                 EMIOS.CH[8].CCR.B.FEN=0x1; 
                 SIU.PCR[187].R = 0xE00;
                 break;
                 
        case 9:  temp = (unsigned long)(MPWMOUT[9].pwmper/unittime+0.5);
                 EMIOS.CH[9].CBDR.R   = temp;
                 temp = (unsigned long)(MPWMOUT[9].pwmhi/unittime+0.5)+PWMOUTHIGHOFFSET;
                 EMIOS.CH[9].CADR.R   = temp;
                 EMIOS.CH[9].CCR.B.UCPRE = 0;
                 EMIOS.CH[9].CCR.B.EDPOL = 1;
                 EMIOS.CH[9].CCR.B.MODE= 0x19;
                 EMIOS.CH[9].CCR.B.FEN=0x1; 
                 SIU.PCR[188].R = 0xE00;
                 break;
                 
        case 10: temp = (unsigned long)(MPWMOUT[10].pwmper/unittime+0.5);
                 EMIOS.CH[10].CBDR.R   = temp;
                 temp = (unsigned long)(MPWMOUT[10].pwmhi/unittime+0.5)+PWMOUTHIGHOFFSET;
                 EMIOS.CH[10].CADR.R   = temp;
                 EMIOS.CH[10].CCR.B.UCPRE = 0;
                 EMIOS.CH[10].CCR.B.EDPOL = 1;
                 EMIOS.CH[10].CCR.B.MODE= 0x19;
                 EMIOS.CH[10].CCR.B.FEN=0x1; 
                 SIU.PCR[189].R = 0xE00;
                 break;                 
                 
        case 11: temp = (unsigned long)(MPWMOUT[11].pwmper/unittime+0.5);
                 EMIOS.CH[13].CBDR.R  = temp;
                 temp = (unsigned long)(MPWMOUT[11].pwmhi/unittime+0.5)+PWMOUTHIGHOFFSET;
                 EMIOS.CH[13].CADR.R   = temp;
                 EMIOS.CH[13].CCR.B.UCPRE = 0;
                 EMIOS.CH[13].CCR.B.EDPOL = 1;
                 EMIOS.CH[13].CCR.B.MODE= 0x19;
                 EMIOS.CH[13].CCR.B.FEN=0x1; 
                 SIU.PCR[192].R = 0xE00;
                 break;   
                 
        default: break;  
    	
    }
	
	
	return(0);
}


/*****************************pwm的输出******************************************************/
/****************************************************************************
* 名称：MpwmOut
* 功能：板载PWM输出对应通道高电平时间设置
* 入口参数：channel--通道号
* 出口参数：无
* 返回值：0--OK,-1--ERROR
* 备注：底板PWM输出
****************************************************************************/ 

int MpwmOut(unsigned char channel)
{

	unsigned long temp;
	
	if(channel>13)
	  return(-1);
	
	temp = (unsigned long)(MPWMOUT[channel].pwmhi/unittime+0.5)+PWMOUTHIGHOFFSET;
    MPWMOUT[channel].pwmhi_cnt=temp;
	
	return(0);
}


void EMIOS0Interrupt(void)
{
	EMIOS.CH[0].CSR.B.FLAG = 1;
	EMIOS.CH[0].CADR.R = MPWMOUT[0].pwmhi_cnt;
	
}

void EMIOS1Interrupt(void)
{
	EMIOS.CH[1].CSR.B.FLAG = 1;
	EMIOS.CH[1].CADR.R = MPWMOUT[1].pwmhi_cnt;
	
}

void EMIOS2Interrupt(void)
{
	EMIOS.CH[2].CSR.B.FLAG = 1;
	EMIOS.CH[2].CADR.R = MPWMOUT[2].pwmhi_cnt;
	
}

void EMIOS3Interrupt(void)
{
	EMIOS.CH[3].CSR.B.FLAG = 1;
	EMIOS.CH[3].CADR.R = MPWMOUT[3].pwmhi_cnt;
	
}

void EMIOS4Interrupt(void)
{
	EMIOS.CH[4].CSR.B.FLAG = 1;
	EMIOS.CH[4].CADR.R = MPWMOUT[4].pwmhi_cnt;
	
}

void EMIOS5Interrupt(void)
{
	EMIOS.CH[5].CSR.B.FLAG = 1;
	EMIOS.CH[5].CADR.R = MPWMOUT[5].pwmhi_cnt;
	
}

void EMIOS6Interrupt(void)
{
	EMIOS.CH[6].CSR.B.FLAG = 1;
	EMIOS.CH[6].CADR.R = MPWMOUT[6].pwmhi_cnt;
	
}

void EMIOS7Interrupt(void)
{
	EMIOS.CH[7].CSR.B.FLAG = 1;
	EMIOS.CH[7].CADR.R = MPWMOUT[7].pwmhi_cnt;
	
}

void EMIOS8Interrupt(void)
{
	EMIOS.CH[8].CSR.B.FLAG = 1;
	EMIOS.CH[8].CADR.R = MPWMOUT[8].pwmhi_cnt;
	
}

void EMIOS9Interrupt(void)
{
	EMIOS.CH[9].CSR.B.FLAG = 1;
	EMIOS.CH[9].CADR.R = MPWMOUT[9].pwmhi_cnt;
	
}

void EMIOS10Interrupt(void)
{
	EMIOS.CH[10].CSR.B.FLAG = 1;
	EMIOS.CH[10].CADR.R = MPWMOUT[10].pwmhi_cnt;
	
}

void EMIOS13Interrupt(void)
{
	EMIOS.CH[13].CSR.B.FLAG = 1;
	EMIOS.CH[13].CADR.R = MPWMOUT[11].pwmhi_cnt;
	
}

/************************************pwm的捕获************************************************/
/****************************************************************************
* 名称：MpwmInEnable
* 功能：板载PWM输入对应通道使能
* 入口参数：channel--通道号
* 出口参数：无
* 返回值：0--OK,-1--ERROR
* 备注：底板PWM输入
****************************************************************************/

int MpwmInEnable(unsigned char channel)
{
   if(channel>5)
	  return(-1);
   
    switch(channel)	
    {
    	
        case 0:  EMIOS.CH[11].CCR.B.UCPREN  = 1;
                 break;
    	
    	case 1:  EMIOS.CH[16].CCR.B.UCPREN  = 1;
                 break;
                  
        case 2:  EMIOS.CH[17].CCR.B.UCPREN  = 1;
                 break;
                 
        case 3:  EMIOS.CH[18].CCR.B.UCPREN  = 1;
                 break;
                 
        case 4:  EMIOS.CH[19].CCR.B.UCPREN  = 1;
                 break;                 
                 
        case 5:  EMIOS.CH[20].CCR.B.UCPREN  = 1;
                 break;
                 
        default: break;  
    	
    }
	
	return(0);
	
}

/****************************************************************************
* 名称：MpwmInDisable
* 功能：板载PWM输入对应通道禁止
* 入口参数：channel--通道号
* 出口参数：无
* 返回值：0--OK,-1--ERROR
* 备注：底板PWM输入
****************************************************************************/

int MpwmInDisable(unsigned char channel)
{
	if(channel>5)
	  return(-1);
   
    switch(channel)	
    {
    	
        case 0:  EMIOS.CH[11].CCR.B.UCPREN  = 0;
                 break;
    	
    	case 1:  EMIOS.CH[16].CCR.B.UCPREN  = 0;
                 break;
                  
        case 2:  EMIOS.CH[17].CCR.B.UCPREN  = 0;
                 break;
                 
        case 3:  EMIOS.CH[18].CCR.B.UCPREN  = 0;
                 break;
                 
        case 4:  EMIOS.CH[19].CCR.B.UCPREN  = 0;
                 break;                 
                 
        case 5:  EMIOS.CH[20].CCR.B.UCPREN  = 0;
                 break;
                 
        default: break;  
    	
    }
	
	return(0);
	
}

/*****************************pwm的输出******************************************************/
/****************************************************************************
* 名称：MpwmInInit
* 功能：板载PWM输入对应通道初始化
* 入口参数：channel--通道号
* 出口参数：无
* 返回值：0--OK,-1--ERROR
* 备注：底板PWM输入
****************************************************************************/ 
int MpwmInInit(unsigned char channel)
{
	
	if(channel>5)
	  return(-1);
	
	switch(channel)	
    {
    	
        case 0:  EMIOS.CH[11].CCR.B.UCPRE = 0;
                 EMIOS.CH[11].CCR.B.EDPOL = 0;
                 EMIOS.CH[11].CCR.B.BSL = 0x3;
                 EMIOS.CH[11].CCR.B.MODE= 0x4; 
                 SIU.PCR[190].R = 0xD00;   
                 break;
    	
    	case 1:  EMIOS.CH[16].CCR.B.UCPRE = 0;
                 EMIOS.CH[16].CCR.B.EDPOL = 0;
                 EMIOS.CH[16].CCR.B.BSL = 0x3;
                 EMIOS.CH[16].CCR.B.MODE = 0x4;
                 SIU.PCR[195].R = 0xD00; 
                 break;
                  
        case 2:  EMIOS.CH[17].CCR.B.UCPRE = 0;
                 EMIOS.CH[17].CCR.B.EDPOL = 0;
                 EMIOS.CH[17].CCR.B.BSL  = 0x3;
                 EMIOS.CH[17].CCR.B.MODE = 0x4;
                 SIU.PCR[196].R = 0xD00;
                 break;
                 
        case 3:  EMIOS.CH[18].CCR.B.UCPRE = 0;
                 EMIOS.CH[18].CCR.B.EDPOL = 0;
                 EMIOS.CH[18].CCR.B.BSL  = 0x3;
                 EMIOS.CH[18].CCR.B.MODE = 0x4;
                 SIU.PCR[197].R = 0xD00;                    
                 break;
                 
        case 4:  EMIOS.CH[19].CCR.B.UCPRE = 0;
                 EMIOS.CH[19].CCR.B.EDPOL = 0;
                 EMIOS.CH[19].CCR.B.BSL=0x3;
                 EMIOS.CH[19].CCR.B.MODE= 0x4;
                 SIU.PCR[198].R = 0xD00;
                 break;                 
                 
        case 5:  EMIOS.CH[20].CCR.B.UCPRE = 0;
                 EMIOS.CH[20].CCR.B.EDPOL = 0;
                 EMIOS.CH[20].CCR.B.BSL=0x3;
                 EMIOS.CH[20].CCR.B.MODE= 0x4;
                 SIU.PCR[199].R = 0xD00;
                 break;
                 
        default: break;  
    	
    }
	
	
	return(0);
}

/****************************************************************************
* 名称：MpwmIn
* 功能：板载PWM输入对应通道采样
* 入口参数：channel--通道号
* 出口参数：无
* 返回值：0--OK,-1--ERROR
* 备注：底板PWM输入
****************************************************************************/

int MpwmIn(unsigned char channel)
{
    unsigned long temp[2];
    unsigned long A1,B1,A2,B2;	
	
	if(channel>5)
	  return(-1);
	
    switch(channel)	
    {
    	
        case 0:  if(EMIOS.CH[11].CSR.B.FLAG== 0)
                 {
        	         MPWMIN[0].pwmhi = 0;/* printf("0x%x,0x%x\n\r",EMIOS.CH[20].CBDR.R,EMIOS.CH[20].CADR.R);*/
                 }
                 else
                 {

                     temp[0] = EMIOS.CH[11].CBDR.R;
                     temp[1] = EMIOS.CH[11].CADR.R;
                     A2 = EMIOS.CH[11].CADR.R;
                     B2 = EMIOS.CH[11].CBDR.R;
                 
                     EMIOS.CH[11].CSR.B.FLAG = 1;
                 
                     if(A1!=A2) 
                     {
                 	      if(B1!=B2)
                 	      {
                 	          temp[0] = A2;
                 	          temp[1] = B2;	
                 	      }
                 	      else
                 	      {
                 	          temp[0] = A1;
                 	          temp[1] = B1;	
                 	      }
                     }
                     else
                     {
                 	     temp[0] = A2;
                 	     temp[1] = B2;
                     }                  
                  
                     if(temp[0]>=temp[1])
                         temp[0]  = temp[0]- temp[1]+PWMINHIGHOFFSET;
                     else 
                     {
                         temp[0] = temp[0]+0x1000000-temp[1]+PWMINHIGHOFFSET;
                     }      
                        
                     MPWMIN[0].pwmhi = temp[0]*unittime; 
                 	
                 }            
                  
                 break;
    	
    	case 1:  
    			 if(EMIOS.CH[16].CSR.B.FLAG== 0)
                 {
        	         MPWMIN[1].pwmhi = 0;/* printf("0x%x,0x%x\n\r",EMIOS.CH[20].CBDR.R,EMIOS.CH[20].CADR.R);*/
                 }
                 else
	                 {
	    			 B1 = EMIOS.CH[16].CBDR.R;
	                 A1 = EMIOS.CH[16].CADR.R;
	                 A2 = EMIOS.CH[16].CADR.R;
	                 B2 = EMIOS.CH[16].CBDR.R;
	                 
	                 EMIOS.CH[16].CSR.B.FLAG = 1;
	                 
	                 if(A1!=A2) 
	                 {
	                 	  if(B1!=B2)
	                 	  {
	                 	      temp[0] = A2;
	                 	      temp[1] = B2;	
	                 	  }
	                 	  else
	                 	  {
	                 	      temp[0] = A1;
	                 	      temp[1] = B1;	
	                 	  }
	                 }                 
	                 else
	                 {
	                 	 temp[0] = A2;
	                 	 temp[1] = B2;
	                 } 
	                 
	                 if(temp[0]>=temp[1])
	                     temp[0]  = temp[0]- temp[1]+PWMINHIGHOFFSET;
	                 else 
	                 {
	                     temp[0] = temp[0]+0x1000000-temp[1]+PWMINHIGHOFFSET;
	                 }  
	                                
	                 MPWMIN[1].pwmhi = temp[0]*unittime;  
	                 }
	                 
                 break;
                  
        case 2:  
        		 if(EMIOS.CH[17].CSR.B.FLAG== 0)
                 {
        	         MPWMIN[2].pwmhi = 0;/* printf("0x%x,0x%x\n\r",EMIOS.CH[20].CBDR.R,EMIOS.CH[20].CADR.R);*/
                 }
                 else
	             { 
	                 EMIOS.CH[17].CSR.B.FLAG = 1;
	        		 B1 = EMIOS.CH[17].CBDR.R;
	                 A1 = EMIOS.CH[17].CADR.R;
	                 A2 = EMIOS.CH[17].CADR.R;
	                 B2 = EMIOS.CH[17].CBDR.R;
	               
	                 if(A1!=A2) 
	                 {
	                 	  if(B1!=B2)
	                 	  {
	                 	      temp[0] = A2;
	                 	      temp[1] = B2;	
	                 	  }
	                 	  else
	                 	  {
	                 	      temp[0] = A1;
	                 	      temp[1] = B1;	
	                 	  }
	                 }                 
	                 else
	                 {
	                 	 temp[0] = A2;
	                 	 temp[1] = B2;
	                 } 
	                 
	                 if(temp[0]>=temp[1])
	                      temp[0]  = temp[0]- temp[1]+PWMINHIGHOFFSET;
	                 else 
	                 {
	                      temp[0] = temp[0]+0x1000000-temp[1]+PWMINHIGHOFFSET;
	                 } 
	                       
	                 MPWMIN[2].pwmhi = temp[0]*unittime;
	             }
                 
                 break;
                 
        case 3: 
           	     if(EMIOS.CH[18].CSR.B.FLAG== 0)
                 {
        	         MPWMIN[3].pwmhi = 0;/* printf("0x%x,0x%x\n\r",EMIOS.CH[20].CBDR.R,EMIOS.CH[20].CADR.R);*/
                 }
                 else
	             {
	        		 B1 = EMIOS.CH[18].CBDR.R;
	                 A1 = EMIOS.CH[18].CADR.R;
	                 A2 = EMIOS.CH[18].CADR.R;
	                 B2 = EMIOS.CH[18].CBDR.R;
	                 
	                 EMIOS.CH[18].CSR.B.FLAG = 1;     
	                 if(A1!=A2) 
	                 {
	                 	  if(B1!=B2)
	                 	  {
	                 	      temp[0] = A2;
	                 	      temp[1] = B2;	
	                 	  }
	                 	  else
	                 	  {
	                 	      temp[0] = A1;
	                 	      temp[1] = B1;	
	                 	  }
	                 }                 
	                 else
	                 {
	                 	 temp[0] = A2;
	                 	 temp[1] = B2;
	                 } 
	                 
	                 if(temp[0]>=temp[1])
	                      temp[0]  = temp[0]- temp[1]+PWMINHIGHOFFSET;
	                 else 
	                 {
	                      temp[0] = temp[0]+0x1000000-temp[1]+PWMINHIGHOFFSET;
	                 }                
	                 MPWMIN[3].pwmhi = temp[0]*unittime;
	             }
	             
                 break;
                 
        case 4: 
        		 if(EMIOS.CH[19].CSR.B.FLAG== 0)
                 {
        	         MPWMIN[4].pwmhi = 0;/* printf("0x%x,0x%x\n\r",EMIOS.CH[20].CBDR.R,EMIOS.CH[20].CADR.R);*/
                 }
                 else
		         {
	        		 B1 = EMIOS.CH[19].CBDR.R;
	                 A1 = EMIOS.CH[19].CADR.R;
	                 A2 = EMIOS.CH[19].CADR.R;
	                 B2 = EMIOS.CH[19].CBDR.R;
	                 EMIOS.CH[19].CSR.B.FLAG = 1;
	                 if(A1!=A2) 
	                 {
	                 	  if(B1!=B2)
	                 	  {
	                 	      temp[0] = A2;
	                 	      temp[1] = B2;	
	                 	  }
	                 	  else
	                 	  {
	                 	      temp[0] = A1;
	                 	      temp[1] = B1;	
	                 	  }
	                 }                 
	                 else
	                 {
	                 	 temp[0] = A2;
	                 	 temp[1] = B2;
	                 } 
	                 
	                 if(temp[0]>=temp[1])
	                      temp[0]  = temp[0]- temp[1]+PWMINHIGHOFFSET;
	                 else 
	                 {
	                      temp[0] = temp[0]+0x1000000-temp[1]+PWMINHIGHOFFSET;
	                 }               
	                 MPWMIN[4].pwmhi = temp[0]*unittime;
		         }
	             
                 break;   
                 
                 
        case 5: 
        		 if(EMIOS.CH[20].CSR.B.FLAG== 0)
                 {
        	         MPWMIN[5].pwmhi = 0;/* printf("0x%x,0x%x\n\r",EMIOS.CH[20].CBDR.R,EMIOS.CH[20].CADR.R);*/
                 }
                 else
		         { 
		             B1 = EMIOS.CH[20].CBDR.R;
	                 A1 = EMIOS.CH[20].CADR.R;
	                 A2 = EMIOS.CH[20].CADR.R;
	                 B2 = EMIOS.CH[20].CBDR.R;
	                 EMIOS.CH[20].CSR.B.FLAG = 1;
	                 if(A1!=A2) 
	                 {
	                 	  if(B1!=B2)
	                 	  {
	                 	      temp[0] = A2;
	                 	      temp[1] = B2;	
	                 	  }
	                 	  else
	                 	  {
	                 	      temp[0] = A1;
	                 	      temp[1] = B1;	
	                 	  }
	                 }                 
	                 else
	                 {
	                 	 temp[0] = A2;
	                 	 temp[1] = B2;
	                 } 
	                 
	                 if(temp[0]>=temp[1])
	                      temp[0]  = temp[0]- temp[1]+PWMINHIGHOFFSET;
	                 else 
	                 {
	                      temp[0] = temp[0]+0x1000000-temp[1]+PWMINHIGHOFFSET;
	                 }            
	                 MPWMIN[5].pwmhi = temp[0]*unittime;
		         }
		  //       printf("A1 = %f, A2 = 0x%x, B1 = 0x%x, B2 = 0x%x\n\r", MPWMIN[5].pwmhi, A2, B1, B2);
	             
                 break;
                 
        default: break;  
    	
    }
	
    return(0);	
	
}

