#include "startup\includes.h"


/****************************************************************************
* ���ƣ�NvramInit
* ���ܣ�nvram ��ʼ��
* ��ڲ�������
* ���ڲ�������
* ����ֵ����
* ��ע����
****************************************************************************/

void   NvramInit(void)
{
    SIU.PCR[102].R = 0x0603;        /* MPC555x: Config pad as DSPI_B SCK output */
    SIU.PCR[103].R = 0x0500;        /* MPC555x: Config pad as DSPI_B SIN input */
    SIU.PCR[104].R = 0x0603;        /* MPC555x: Config pad as DSPI_B SOUT output */
    SIU.PCR[105].R = 0x0603;        /* MPC555x: Config pad as DSPI_B PCS0 output */
    
    DSPI_B.MCR.R = 0x80010000;      /* Configure DSPI_B as master */
    DSPI_B.CTAR[0].R = 0x780A7724;  /* Configure CTAR0  */
    DSPI_B.CTAR[1].R = 0x380A7724;  /* Configure CTAR1  */	
	
}

/****************************************************************************
* ���ƣ�NvramRead
* ���ܣ�nvram ��
* ��ڲ�����offset-- ƫ�Ƶ�ַ(0x0~0x10000)
* ���ڲ�����*val-- 16Bit����
* ����ֵ��0--OK,-1--ERROR
* ��ע����
****************************************************************************/

long NvramRead(unsigned long offset,unsigned short *val)
{
    unsigned short temp;
    
    if(offset > MAX_OFFSET)
        return(-1);
    	
    offset = (offset/2)*2;

    DSPI_B.PUSHR.R = (0x80010000 + COMMANDNREAD*0x100 + ((offset>>16)&0xff));
    DSPI_B.PUSHR.R = (0x80010000 + (offset&0xffff));
    DSPI_B.PUSHR.R = 0x08010000;
        
    while (DSPI_B.SR.B.EOQF != 1)
    {
    	
    }

    temp = (unsigned short)(DSPI_B.POPR.B.RXDATA);   /* Read data received by master SPI */
    temp = (unsigned short)(DSPI_B.POPR.B.RXDATA);   /* Read data received by master SPI */
    temp = (unsigned short)(DSPI_B.POPR.B.RXDATA);   /* Read data received by master SPI */
    *val  = temp;  

    DSPI_B.MCR.B.CLR_TXF = 0x1;
    DSPI_B.MCR.B.CLR_RXF = 0x1;  
     
 	DSPI_B.SR.R = 0x90020000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */
    return(0);	
}

/****************************************************************************
* ���ƣ�NvramWrite
* ���ܣ�nvram д
* ��ڲ�����offset-- ƫ�Ƶ�ַ(0x0~0x10000)   val-- 16Bit����
* ���ڲ�������
* ����ֵ��0--OK,-1--ERROR
* ��ע����
****************************************************************************/

long NvramWrite(unsigned long offset,unsigned short val)
{
   
    unsigned short temp;
    
    if(offset > MAX_OFFSET)
        return(-1);
    
    offset = (offset/2)*2;
     
    DSPI_B.PUSHR.R = (0x18010000 + COMMANDNWREN);
    while (DSPI_B.SR.B.EOQF != 1)
    {
    	
    }
    temp = (unsigned short)(DSPI_B.POPR.B.RXDATA);   /* Read data received by master SPI */
    DSPI_B.MCR.B.CLR_TXF = 0x1;
    DSPI_B.MCR.B.CLR_RXF = 0x1;       
 	DSPI_B.SR.R = 0x90020000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */ 

    
    DSPI_B.PUSHR.R = (0x80010000 + COMMANDNWRITE*0x100 + ((offset>>16)&0xff));
    DSPI_B.PUSHR.R = (0x80010000 + (offset&0xffff));
    DSPI_B.PUSHR.R = (0x08010000 + val);
     
           
    while (DSPI_B.SR.B.EOQF != 1)
    {
    	
    }
    temp = (unsigned short)(DSPI_B.POPR.B.RXDATA);   /* Read data received by master SPI */
    temp = (unsigned short)(DSPI_B.POPR.B.RXDATA);   /* Read data received by master SPI */
    temp = (unsigned short)(DSPI_B.POPR.B.RXDATA);   /* Read data received by master SPI */
      
    DSPI_B.MCR.B.CLR_TXF = 0x1;
    DSPI_B.MCR.B.CLR_RXF = 0x1;  
     
 	DSPI_B.SR.R = 0x90020000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */ 
 	
 
    DSPI_B.PUSHR.R = (0x18020000 + COMMANDNWRDI);    
    while (DSPI_B.SR.B.EOQF != 1)
    {
    	
    }
    temp = (unsigned short)(DSPI_B.POPR.B.RXDATA);   /* Read data received by master SPI */
      
    DSPI_B.MCR.B.CLR_TXF = 0x1;
    DSPI_B.MCR.B.CLR_RXF = 0x1;  
     
 	DSPI_B.SR.R = 0x90020000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */ 
 	
    return(0);
	
}