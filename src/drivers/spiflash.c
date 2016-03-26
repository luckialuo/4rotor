#include "startup\includes.h"


void   SpiFlashInit(void)
{

    
    SIU.PCR[109].R = 0x0A03;        /* MPC555x: Config pad as DSPI_C SCK output */
    SIU.PCR[108].R = 0x0900;        /* MPC555x: Config pad as DSPI_C SIN input */
    SIU.PCR[107].R = 0x0A03;        /* MPC555x: Config pad as DSPI_C SOUT output */
    SIU.PCR[110].R = 0x0A03;        /* MPC555x: Config pad as DSPI_C PCS0 output */
    
    DSPI_C.MCR.R = 0x80010000;      /* Configure DSPI_C as master */
    DSPI_C.CTAR[0].R = 0x780A3323;  /* Configure CTAR0  */
    DSPI_C.CTAR[1].R = 0x380A3323;  /* Configure CTAR1  */
   
}


void  SpiFlashEraseSector(unsigned long flashAdrs)
{
    unsigned short temp;
     
    flashAdrs = flashAdrs&0xff0000;
     
     
    DSPI_C.PUSHR.R = (0x18010000 + COMMANDWREN);
    while (DSPI_C.SR.B.EOQF != 1)
    {
    	
    }
    temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
    DSPI_C.MCR.B.CLR_TXF = 0x1;
    DSPI_C.MCR.B.CLR_RXF = 0x1;       
 	DSPI_C.SR.R = 0x90010000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */  
 	 
      
    DSPI_C.PUSHR.R = (0x80010000 + COMMANDSE*0x100 + ((flashAdrs>>16)&0xff));
    DSPI_C.PUSHR.R = (0x08010000 + (flashAdrs&0xffff));
     
    while (DSPI_C.SR.B.EOQF != 1)
    {
    	
    }
    temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
    temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
      
    DSPI_C.MCR.B.CLR_TXF = 0x1;
    DSPI_C.MCR.B.CLR_RXF = 0x1;  
     
 	DSPI_C.SR.R = 0x90010000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */ 
    
    temp = 0;
 	
    while(1)
    {
          DSPI_C.PUSHR.R = (0x08010000 + COMMANDRDSR*0x100);
          while (DSPI_C.SR.B.EOQF != 1)
          {
          	
          }
          temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
          
        
          DSPI_C.MCR.B.CLR_TXF = 0x1;
          DSPI_C.MCR.B.CLR_RXF = 0x1;  
     
 	      DSPI_C.SR.R = 0x90010000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */ 
 	      
 	      temp = (unsigned short)(temp&0xff);
          if((temp&0x1)!= 0x1)
              break;
     }	

      
    DSPI_C.PUSHR.R = (0x18010000 + COMMANDWRDI);  
    while (DSPI_C.SR.B.EOQF != 1)
    {
    	
    }
    temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
      
    DSPI_C.MCR.B.CLR_TXF = 0x1;
    DSPI_C.MCR.B.CLR_RXF = 0x1;  
     
 	DSPI_C.SR.R = 0x90010000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */ 

}

void   SpiFlashProg(unsigned long flashAdrs,unsigned long val)
{
    unsigned short temp;
    
    flashAdrs = (flashAdrs/4)*4;
     
    DSPI_C.PUSHR.R = (0x18010000 + COMMANDWREN);
    while (DSPI_C.SR.B.EOQF != 1)
    {
    	
    }
    temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
    DSPI_C.MCR.B.CLR_TXF = 0x1;
    DSPI_C.MCR.B.CLR_RXF = 0x1;       
 	DSPI_C.SR.R = 0x90010000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */ 

    
    DSPI_C.PUSHR.R = (0x80010000 + COMMANDPP*0x100 + ((flashAdrs>>16)&0xff));
    DSPI_C.PUSHR.R = (0x80010000 + (flashAdrs&0xffff));
    DSPI_C.PUSHR.R = (0x80010000 + ((val>>16)&0xffff));
    DSPI_C.PUSHR.R = (0x08010000 + (val&0xffff));
     
           
    while (DSPI_C.SR.B.EOQF != 1)
    {
    	
    }
    temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
    temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
    temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
    temp = (unsigned short)(DSPI_C.POPR.B.RXDATA); /* Read data received by master SPI */   
      
    DSPI_C.MCR.B.CLR_TXF = 0x1;
    DSPI_C.MCR.B.CLR_RXF = 0x1;  
     
 	DSPI_C.SR.R = 0x90010000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */ 
 	
 	temp = 0;
 	
    while(1)
    {
          DSPI_C.PUSHR.R = (0x08010000 + COMMANDRDSR*0x100);
          while (DSPI_C.SR.B.EOQF != 1)
          {
          	
          }
          temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
          
        
          DSPI_C.MCR.B.CLR_TXF = 0x1;
          DSPI_C.MCR.B.CLR_RXF = 0x1;  
     
 	      DSPI_C.SR.R = 0x90010000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */ 
 	      
 	      temp = (unsigned short)(temp&0xff);
          if((temp&0x1)!= 0x1)
              break;
     }	

      
    DSPI_C.PUSHR.R = (0x18010000 + COMMANDWRDI);    
    while (DSPI_C.SR.B.EOQF != 1)
    {
    	
    }
    temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
      
    DSPI_C.MCR.B.CLR_TXF = 0x1;
    DSPI_C.MCR.B.CLR_RXF = 0x1;  
     
 	DSPI_C.SR.R = 0x90010000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */ 
 	
}

unsigned long SpiFlashRead(unsigned long flashAdrs)
{
    unsigned long val;
    unsigned short temp;
    	
    flashAdrs = (flashAdrs/4)*4;

    DSPI_C.PUSHR.R = (0x80010000 + COMMANDREAD*0x100 + ((flashAdrs>>16)&0xff));
    DSPI_C.PUSHR.R = (0x80010000 + (flashAdrs&0xffff));
    DSPI_C.PUSHR.R = 0x80010000;
    DSPI_C.PUSHR.R = 0x08010000;
     
           
    while (DSPI_C.SR.B.EOQF != 1)
    {
    	
    }

    temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
    temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
    temp = (unsigned short)(DSPI_C.POPR.B.RXDATA);   /* Read data received by master SPI */
    val  = (temp<<16) + DSPI_C.POPR.B.RXDATA; /* Read data received by master SPI */  

    DSPI_C.MCR.B.CLR_TXF = 0x1;
    DSPI_C.MCR.B.CLR_RXF = 0x1;  
     
 	DSPI_C.SR.R = 0x90010000;        /* Clear TCF, RDRF, EOQ flags by writing 1 */
 	
    return(val);	 
	
}

