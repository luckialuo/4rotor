#include "startup\includes.h"

CommStruc            COM[1];

/****************************************************************************
* 名称：PPC_Com1Init
* 功能：板载串口1初始化
* 入口参数：BaudRate--波特率  ParityMode--奇偶校验位   
* 出口参数：无
* 返回值：无
* 备注：
****************************************************************************/ 

void PPC_Com1Init(unsigned long BaudRate,unsigned char ParityMode) 
{
	long cnt;
	
	SIU.PCR[89].R = 0x433;
	SIU.PCR[90].R = 0x433;
		
	switch (BaudRate) {
	    case 1200:
	    	cnt = DL_1200;   break;	/*   1200 baud */
	    case 2400:
	    	cnt = DL_2400;   break;	/*   2400 baud */
	    case 4800:
	    	cnt = DL_4800;   break;	/*   4800 baud */
	    case 9600:
	    	cnt = DL_9600;   break;	/*   9600 baud */
    	case 19200:
    		cnt = DL_19200;  break;	/*  19200 baud */
	    case 38400:
	    	cnt = DL_38400;  break;	/*  38400 baud */
	    case 57600:
	    	cnt = DL_57600;  break;	/*  57600 baud */
	    case 115200:
	    	cnt = DL_115200; break;	/* 115.2K baud */
    }
    
	ESCI_A.CR1.B.SBR = cnt;
	
	switch(ParityMode)
	{
		
		case 0:
		     ESCI_A.CR1.B.PE = 0x0;		/*无校验*/
		     break;
		case 1:
		     ESCI_A.CR1.B.PE = 0x1;
		     ESCI_A.CR1.B.PT = 0x0;		/*偶校验*/
		     break;		     
		case 2:
		     ESCI_A.CR1.B.PE = 0x1;
	   	     ESCI_A.CR1.B.PT = 0x1;		/*奇校验*/
		     break;
		default:
		     ESCI_A.CR1.B.PE = 0x0;		/*无校验*/
		     break;
		
	}

} 

/****************************************************************************
* 名称：PPC_Com1EnableInterrupt
* 功能：板载串口1中断初始化
* 入口参数：无
* 出口参数：无
* 返回值：无
* 备注：
****************************************************************************/ 


void PPC_Com1EnableInterrupt(void)
{  
    ESCI_A.CR1.B.RIE = 1;   /* Enable Rx interrupts */ 
    ESCI_A.CR1.B.TIE = 0;
	ESCI_A.CR1.B.TE  = 1;
	ESCI_A.CR1.B.RE  = 1;

 
}

/****************************************************************************
* 名称：PPC_Com1RxLen
* 功能：板载串口1接收缓冲区数据长度查询
* 入口参数：无
* 出口参数：无
* 返回值：接收缓冲区数据长度
* 备注：
****************************************************************************/ 

unsigned char  PPC_Com1RxLen (void)
{
    unsigned char len;

    len = (unsigned char)(COM[COM1].Rxhead - COM[COM1].Rxtail);  
    return (len);
}

/****************************************************************************
* 名称：PPC_Com1TxLen
* 功能：板载串口1发送缓冲区数据长度查询
* 入口参数：无
* 出口参数：无
* 返回值：发送缓冲区数据长度
* 备注：
****************************************************************************/ 

unsigned char  PPC_Com1TxLen (void)
{
    unsigned char len;
    
    len = (unsigned char)(COM[COM1].Txhead - COM[COM1].Txtail);
    return (len);
}

/****************************************************************************
* 名称：PPC_Com1In
* 功能：板载串口1读取缓冲区数据
* 入口参数：buf[]--数据存储地址，len--读取的长度
* 出口参数：无
* 返回值：实际数据长度
* 备注：
****************************************************************************/ 

unsigned char  PPC_Com1In (unsigned char buf[], unsigned char len)
{
    unsigned char RxLen,NumIn,idx;

    RxLen=PPC_Com1RxLen();
    if (RxLen>=len) NumIn=len;
    else            NumIn=RxLen;
    

	  for (idx=0;idx<NumIn;idx++) buf[idx]=COM[COM1].RxBuf[COM[COM1].Rxtail++];
	  return (NumIn);
}

/****************************************************************************
* 名称：PPC_Com1Out
* 功能：板载串口1发送数据
* 入口参数：buf[]--数据存储地址，len--读取的长度
* 出口参数：无
* 返回值：实际发送数据长度
* 备注：
****************************************************************************/ 

unsigned char  PPC_Com1Out(unsigned char buf[], unsigned char len)
{
    unsigned char TxLen,NumOut,idx;
    TxLen=PPC_Com1TxLen();
    if ((TxLen+len)<=PPC_ComTxBuffSize) NumOut=len;
    else            NumOut=(unsigned char)(PPC_ComTxBuffSize-TxLen);

    for (idx=0;idx<NumOut;idx++) {
      COM[COM1].TxBuf[COM[COM1].Txhead++]=buf[idx];
    }
    
    // ESCI_A.CR1.B.TE = 1;
    if (PPC_Com1TxLen()) {
    
       
        while((ESCI_A.SR.B.TDRE == 1)&&(ESCI_A.SR.B.RDRF == 0))      
        {
            ESCI_A.SR.B.TDRE = 1;
               
        }     
  
        ESCI_A.DR.B.D = COM[COM1].TxBuf[COM[COM1].Txtail++];          
        ESCI_A.CR1.B.TIE = 1;       
        /* Enable Tx interrupts*/ 	
     }	
	  return(NumOut);
}

/****************************************************************************
* 名称：PPC_Com1InterruptHandler
* 功能：板载串口1中断处理函数
* 入口参数：无
* 出口参数：无
* 返回值：无
* 备注：
****************************************************************************/ 

void PPC_Com1InterruptHandler(void)
{  
    
   if(ESCI_A.SR.B.RDRF == 1) 
    {        
        COM[COM1].RxBuf[COM[COM1].Rxhead++]= ESCI_A.DR.B.D ;
        ESCI_A.SR.B.RDRF=1; 
        
    } 
   
  if((ESCI_A.SR.B.TDRE == 1)&&(PPC_Com1TxLen()!=0)&&(ESCI_A.SR.B.RDRF == 0))  
    {
		    ESCI_A.SR.B.TDRE = 1; 
			ESCI_A.DR.B.D = COM[COM1].TxBuf[COM[COM1].Txtail++];		
    } 
    
     if(!PPC_Com1TxLen())
    	{ 
    	
    	  ESCI_A.CR1.B.TIE = 0;
    	  //  ESCI_A.CR1.B.TE = 0;  	   
    	   	
    	}
  
          			        
} 


