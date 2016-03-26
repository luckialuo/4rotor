#include "startup\includes.h"

//#define ANALOGINSPICH1     0     /*MPX5004*/
//#define ANALOGINSPICH2     2     /*MPX6115*/


/****************************************************************************
* ���ƣ�AnalogInit(void)
* ���ܣ�AD������ʼ��
* ��ڲ�������
* ���ڲ�������
* ����ֵ����
* ��ע����
****************************************************************************/

void AnalogInit(void)
{
    
 	EQADC.CFPR[0].R = 0x80801301;                                               
    EQADC.CFCR[0].R = 0x0410;           /* Trigger CFIFO 0 using Single Scan SW mode */
    while (EQADC.FISR[0].B.EOQF !=1) {} /* Wait for End Of Queue flag */
    EQADC.FISR[0].B.EOQF = 1;           /* Clear End Of Queue flag */
}


/****************************************************************************
* ���ƣ�AnalogIn
* ���ܣ�AD��ѹ����
* ��ڲ�����ch--ADͨ���ţ�*volts--��ѹ��Χ(0~5V)
* ���ڲ�������
* ����ֵ��0--OK,-1--ERROR
* ��ע������12bit
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

