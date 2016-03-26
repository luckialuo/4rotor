#include "MPC.h"

static flag = 0;
FP32    height_alt,height_alt_2,height_alt_3,height_alt_4,height_alt0,height_alt1,height_alt2,height_alt3,height_alt4,height_alt5,height_alt6;
FP32    height_alt00,height_alt10,height_alt20,height_alt30,height_alt40,height_alt50,height_alt60;
FP32    height_speed,height_speed1,height_speed2,height_speed3,height_speed4,height_speed5,height_speed6;                   
DataSet ds[8];
static ii = 0, jj = 0;
SensorStruc	 ss_Srf;
INT32U    dtime,dtime2,dtime3,dtime1,dtime4,dtime5,dtime6;
FP32    srf_dZ,srf_dL,srf_ddZ,srf_ddL;
/*
void sendBreak1(void)   //50ms 20Hz 2分频 Com4
{
	
	unsigned long i; 
	static unsigned char string0[6] = {0x05,0x51,0x02,0x51,0x03,0x51};                //0x00表示地址， 0x54表示命令
    static unsigned char string2[2] = {0x02,0x54}; //对左超声波
    static unsigned char string3[2] = {0x03,0x54}; //对右超声波 
    static INT8U   cnt = 0;
    static INT32U  win_time2,old_time2,win_time3,old_time3;
    static float   height_old2=0.7,height_old3=0.7;

	cnt++;cnt%=2;                                 
    
    if(cnt==0)
    {
       //对右超声波
       Task_SrfRev();
	   height_alt30=height_alt;
	   
	   win_time3 = time_cnt;
	   dtime3 = win_time3 - old_time3;
	   
	   if(height_alt30>=2.2)
	   {
		  height_alt3=height_old3;
		  height_speed3=height_speed3/5.0f;
	   }
	   else 
	   {
		  height_alt3=height_alt30;
		  height_speed3=(height_alt3 - height_old3)/(dtime3/1000.0);
		  height_speed3=MidVal(height_speed3,-0.5f,0.5f);
		  height_old3=height_alt30;
		  old_time3=win_time3;
		  	
	   }
	   
       UartCom4Out(string2, 2);
       while(UartCom4TxLen()!=0);
    }
    
    
    if(cnt==1)
    {
       //对左超声波
       Task_SrfRev();
	   height_alt20=height_alt;
	   
	   win_time2 = time_cnt;
	   dtime2 = win_time2 - old_time2;
	   
	   if(height_alt20>=2.2)
	   {
		  height_alt2=height_old2;
		  height_speed2=height_speed2/5.0f;
	   }
	   else 
	   {
		  height_alt2=height_alt20;
		  height_speed2=(height_alt2 - height_old2)/(dtime2/1000.0);
		  height_speed2=MidVal(height_speed2,-0.5f,0.5f);
		  height_old2=height_alt20;
		  old_time2=win_time2;	
	   }
	   
       UartCom4Out(string3, 2);
       while(UartCom4TxLen()!=0);  
	       	
    }

 

}


void sendBreak2(void)   //50ms 20Hz 2分频 Com5
{
	
	unsigned long i; 
	static unsigned char string0[6] = {0x01,0x51,0x04,0x51,0x00,0x51};                //0x00表示地址， 0x54表示命令
    static unsigned char string1[2] = {0x01,0x54}; //对前超声波
    static unsigned char string2[2] = {0x04,0x54}; //对后超声波
    static INT8U   cnt = 0;
    static INT32U  win_time1,old_time1,win_time4,old_time4;
    static float   height_old1=0.7,height_old4=0.7;

	cnt++;cnt%=2;                                 
       
    
    if(cnt==0)
    {
       //对前超声波
       Task_SrfRev2();
	   height_alt10=height_alt_2;
	   
	   win_time1 = time_cnt;
	   dtime1 = win_time1 - old_time1;
	   
	   if(height_alt10>=2.2)
	   {
		  height_alt1=height_old1;
		  height_speed1=height_speed1/5.0f;
	   }
	   else 
	   {
		  height_alt1=height_alt10;
		  height_speed1=(height_alt1 - height_old1)/(dtime1/1000.0);
		  height_speed1=MidVal(height_speed1,-0.5f,0.5f);
		  height_old1=height_alt10;
		  old_time1=win_time1;
		  	  	
	   }
	   
	   UartCom5Out(string2, 2);
       while(UartCom5TxLen()!=0);
    }
    
    if(cnt==1)
    {
       //对后超声波
       Task_SrfRev2();
	   height_alt40=height_alt_2;
	   
	   win_time4 = time_cnt;
	   dtime4 = win_time4 - old_time4;
	   
	   if(height_alt40>=2.2)
	   {
		  height_alt4=height_old4;
		  height_speed4=height_speed4/5.0f;
	   }
	   else 
	   {
		  height_alt4=height_alt40;
		  height_speed4=(height_alt4 - height_old4)/(dtime4/1000.0);
		  height_speed4=MidVal(height_speed4,-0.5f,0.5f);
		  height_old4=height_alt40;
		  old_time4=win_time4;
  	
	   }
	   
       UartCom5Out(string1, 2);
       while(UartCom5TxLen()!=0);
    }
    
 
    

}
*/

void sendBreak3(void)   //50ms 20Hz 1分频 Com6
{
	
	static unsigned char string0[6] = {0x05,0x51,0x02,0x51,0x03,0x51};                //0x01表示地址， 0x54表示命令
    static unsigned char string1[2] = {0x01,0x54}; //对地超声波
    static INT8U   cnt = 0;
    static INT32U  win_time,old_time;
    static float   height_old=0.2;

       UartCom4Out(string1, 2);
       while(UartCom4TxLen()!=0);
       
       //对地超声波
       Task_SrfRev3();
	   if(height_alt_3!=0) 
	   {
	   height_alt00=height_alt_3;
	   
	   win_time = time_cnt;
	   dtime = win_time - old_time;
	   
       if((height_alt00>=2.2)||(fabs(height_alt00-height_old)>0.5))
	   {
		  height_alt0=height_old;
		  height_speed=height_speed/5.0f;
	   }
	   else 
	   {
		  height_alt0=height_alt00;
		  height_speed=(height_alt0 - height_old)/(dtime/1000.0);
		  height_speed=MidVal(height_speed,-0.5f,0.5f);
		  height_old=height_alt00;
		  old_time=win_time;	
	   }
		
	   ac_height=height_alt0;//使用超声波高度
	   }
	   
	   

}

/*
void sendBreak4(void)   //50ms 20Hz 1分频 Com7
{
	
	unsigned long i; 
	static unsigned char string0[6] = {0x01,0x51,0x04,0x51,0x00,0x51};                //0x00表示地址， 0x54表示命令
    static unsigned char string1[2] = {0x00,0x54}; //对地超声波
    static INT8U   cnt = 0;
    static INT32U  win_time,old_time;
    static float   height_old=0.2;

	cnt++;cnt%=2;                                 
    
       UartCom7Out(string1, 2);
       while(UartCom7TxLen()!=0);
       
       //对地超声波
       Task_SrfRev4();
	   if(height_alt_4!=0) 
	   {
	   height_alt00=height_alt_4;
	   
	   win_time = time_cnt;
	   dtime = win_time - old_time;
	   
       if(height_alt00-height_old>0.3)
	   {
		  height_alt0=height_old;
		  height_speed=height_speed/5.0f;
	   }
	   else 
	   {
		  height_alt0=height_alt00;
		  height_speed=(height_alt0 - height_old)/(dtime/1000.0);
		  height_speed=MidVal(height_speed,-0.5f,0.5f);
		  height_old=height_alt00;
		  old_time=win_time;	
	   }
		
	   ac_height=height_alt0;//使用超声波高度
	   }   

}
*/

void changeAddr(void)                                                              
{
    static unsigned char string1[8] = 
    {
      0x01, 0xA0, 0x01, 0xAA, 0x01, 0xA5, 0x01, 0x00	
    };
    
    UartCom4Out(string1, 8);
}


/*
void  Task_SrfRev(void)
{
  static  unsigned char rxBufferLen,numread,idx;
  static  unsigned char buf[256],temp[2],temp0[256];
  static  unsigned char srf[4];
  static  unsigned char head=0,tail=0,prt=0,len;
  dWordStruc  src;  


    rxBufferLen=UartCom4RxLen();
    numread=rxBufferLen>255?255:rxBufferLen;
    if (numread==2) 
    {       
        UartCom4In(temp,numread);
	    
		height_alt =(temp[0]*0x100 + temp[1])/100.0f;
		height_alt = MidVal(height_alt,0.0,2.2);				
		//src.B[0]=srf[3];src.B[1]=srf[4];height_alt=src.D[0]/100.0f;
        
	}
	else UartCom4In(temp0,numread);      
}


void  Task_SrfRev2(void)
{
  static  unsigned char rxBufferLen,numread,idx;
  static  unsigned char buf[256],temp[2],temp0[256];
  static  unsigned char srf[4];
  static  unsigned char head=0,tail=0,prt=0,len;
  dWordStruc  src;  


    rxBufferLen=UartCom5RxLen();
    numread=rxBufferLen>255?255:rxBufferLen;
    if (numread==2) 
    {       
        UartCom5In(temp,numread);
	    
		height_alt_2 =(temp[0]*0x100 + temp[1])/100.0f;
		height_alt_2 = MidVal(height_alt_2,0.0,2.2);				
		//src.B[0]=srf[3];src.B[1]=srf[4];height_alt=src.D[0]/100.0f;
    	
	}
	else UartCom5In(temp0,numread);     
}
*/

void  Task_SrfRev3(void)
{
  static  unsigned char rxBufferLen,numread,idx;
  static  unsigned char buf[256],temp[2],temp0[256];
  static  unsigned char srf[4];
  static  unsigned char head=0,tail=0,prt=0,len;



    rxBufferLen=UartCom4RxLen();
    numread=rxBufferLen>255?255:rxBufferLen;
    if (numread==2) 
    {       
        UartCom4In(temp,numread);
	    
		height_alt_3 =(temp[0]*0x100 + temp[1])/100.0f;
		height_alt_3 = MidVal(height_alt_3,0.0,2.2);				
		//src.B[0]=srf[3];src.B[1]=srf[4];height_alt=src.D[0]/100.0f;
		ss_Srf.invalid=ss_Srf.fail=0;ss_Srf.counter++;
    	
	}
	else UartCom4In(temp0,numread);     
}
/*
void  Task_SrfRev4(void)
{
  static  unsigned char rxBufferLen,numread,idx;
  static  unsigned char buf[256],temp[2],temp0[256];
  static  unsigned char srf[4];
  static  unsigned char head=0,tail=0,prt=0,len;
  dWordStruc  src;  


    rxBufferLen=UartCom7RxLen();
    numread=rxBufferLen>255?255:rxBufferLen;
    if (numread==2) 
    {       
        UartCom7In(temp,numread);
	    
		height_alt_4 =(temp[0]*0x100 + temp[1])/100.0f;
		height_alt_4 = MidVal(height_alt_4,0.0,2.2);				
		//src.B[0]=srf[3];src.B[1]=srf[4];height_alt=src.D[0]/100.0f;
		
    	
	}
	else UartCom7In(temp0,numread);     
}
*/

void  SRF_Monitor(void)                       
{

    static INT8U	 cnt = 0;
    static INT8U     flag1s = FALSE;
    static INT16U	 old_counter;
    
	ss_Srf.invalid +=1;    
    if (ss_Srf.invalid>=8) ss_Srf.fail=1;
    
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
