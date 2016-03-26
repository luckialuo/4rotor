#include "startup\includes.h"

//#define ANALOGINSPICH1     0     /*MPX5004*/
//#define ANALOGINSPICH2     2     /*MPX6115*/


/****************************************************************************
* 名称：AnalogInit(void)
* 功能：AD采样初始化
* 入口参数：无
* 出口参数：无
* 返回值：无
* 备注：无
****************************************************************************/

void AnalogInit(void)
{
    
 	EQADC.CFPR[0].R = 0x80801301;                                               
    EQADC.CFCR[0].R = 0x0410;           /* Trigger CFIFO 0 using Single Scan SW mode */
    while (EQADC.FISR[0].B.EOQF !=1) {} /* Wait for End Of Queue flag */
    EQADC.FISR[0].B.EOQF = 1;           /* Clear End Of Queue flag */
}


/****************************************************************************
* 名称：AnalogIn
* 功能：AD电压采样
* 入口参数：ch--AD通道号，*volts--电压范围(0~5V)
* 出口参数：无
* 返回值：0--OK,-1--ERROR
* 备注：板载12bit
****************************************************************************/

short  AnalogIn(unsigned char ch, float *volts)
{
	
   
    if(ch>24)
	  return(-1);
    
    
    EQADC.CFPR[0].R = (0x80000000 + (ch<<8));   
    EQADC.CFCR[0].R = 0x0410;                  /* Trigger CFIFO 0 using Single Scan SW mode */     
    while (EQADC.FISR[0].B.RFDF != 1){}        /* Wait for RFIFO 0's Drain Flag to set */
    if(ch == 6)
    {
    	*volts = (4.5*(EQADC.RFPR[0].R-4)) / (0x3fff );       /* ADC result */ 
    }
    else
    {
    	*volts = (4.5*(EQADC.RFPR[0].R-4))/0x3fff;       /* ADC result */        
    }
    EQADC.FISR[0].B.RFDF = 1;                  /* Clear RFIFO 0's Drain Flag */
    EQADC.FISR[0].B.EOQF = 1;                  /* Clear CFIFO's End of Queue flag */
	
	return(0);
}

