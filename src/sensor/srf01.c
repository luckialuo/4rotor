#include "MPC.h"

SensorStruc	 ss_Srf;
FP32         height_alt,                   /*[alt∫ÏÕ‚≤‚∏ﬂ][m]*/
             theta_ini,
             height_onGround;

void sendBreak(unsigned char ncom)
{
	
	unsigned long i; 
	unsigned char string[2] = {0x01,0x54};  
	switch(ncom)
	{
		case 8:
		    SIU.PCR[157].R=0x0203;
	    	SIU.GPDO[157].R=0x01;  
	    		
	    	SIU.GPDO[157].R=0x00;
	    	for(i=0;i<10000;i++); 
	        SIU.GPDO[157].R=0x01;
	        
	        SIU.PCR[157].R=0x0603;
	    	break;
		default :
	    	break;
	}
	UartCom11Out(string,2);
}



void  Task_SrfRev(void)
{
  static  unsigned char rxBufferLen,numread,idx;
  static  unsigned char buff[256],temp[256];
  unsigned char srf[5];
  static   unsigned char head=0,tail=0,prt=0,len;
  static FP32 temp_height=0.0f;
    

    rxBufferLen=UartCom11RxLen();
    numread=rxBufferLen>256?256:rxBufferLen;
    
    if (numread) 
    {              
        UartCom11In(temp,numread);
        for (idx=0; idx<numread; idx++) 
        {
            	buff[head++]=temp[idx];
        }
            
    }
     
    len = head-tail; 
        
    while (len>= sizeof(srf))
    {
    
        if ((buff[tail]==0x01) && (buff[tail+1]==0x54))
        {
            prt=tail;                        
            for (idx=0;idx<sizeof(srf);idx++) 
                srf[idx]=buff[prt++];
           	    temp_height =MidVal(((srf[2]*0x100 + srf[3])/100.0f),0.4f,7.0f);
           	    height_alt = (temp_height-height_onGround)*fcos((theta_gyo-theta_ini)/Rad2Deg)*fcos(gama_gyo/Rad2Deg);        	    
           	    //height_alt=(srf[2]*0x100 + srf[3])/100.0f;
           	    ss_Srf.invalid=ss_Srf.fail=0;ss_Srf.counter++;	           	           	           	   	
           	   	tail=tail+sizeof(srf);
           	     
         }        	
         else
             tail++; 
         
         len = head-tail;
        }     
}


void  SRF_Monitor(void)                       
{

    static INT8U	 cnt = 0;
    static INT8U  flag1s = FALSE;
    static INT16U	 old_counter;
    
	ss_Srf.invalid +=1;    
    if (ss_Srf.invalid>=20) ss_Srf.fail=1;
    
	  cnt ++;
	  cnt %= 100;
	  if ((cnt%10) == 0)
	       flag1s = TRUE;                           
    	    
	  if (flag1s) 
	  {
	       flag1s = FALSE;
		   ss_Srf.freq  = ss_Srf.counter - old_counter;  
		   old_counter  = ss_Srf.counter;
	  }
	  
}