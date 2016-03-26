#include "startup\includes.h"

CommStruc            COM[1];

/****************************************************************************
* ���ƣ�PPC_Com1Init
* ���ܣ����ش���1��ʼ��
* ��ڲ�����BaudRate--������  ParityMode--��żУ��λ   
* ���ڲ�������
* ����ֵ����
* ��ע��
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
		     ESCI_A.CR1.B.PE = 0x0;		/*��У��*/
		     break;
		case 1:
		     ESCI_A.CR1.B.PE = 0x1;
		     ESCI_A.CR1.B.PT = 0x0;		/*żУ��*/
		     break;		     
		case 2:
		     ESCI_A.CR1.B.PE = 0x1;
	   	     ESCI_A.CR1.B.PT = 0x1;		/*��У��*/
		     break;
		default:
		     ESCI_A.CR1.B.PE = 0x0;		/*��У��*/
		     break;
		
	}

} 

/****************************************************************************
* ���ƣ�PPC_Com1EnableInterrupt
* ���ܣ����ش���1�жϳ�ʼ��
* ��ڲ�������
* ���ڲ�������
* ����ֵ����
* ��ע��
****************************************************************************/ 


void PPC_Com1EnableInterrupt(void)
{  
    ESCI_A.CR1.B.RIE = 1;   /* Enable Rx interrupts */ 
    ESCI_A.CR1.B.TIE = 0;
	ESCI_A.CR1.B.TE  = 1;
	ESCI_A.CR1.B.RE  = 1;

 
}

/****************************************************************************
* ���ƣ�PPC_Com1RxLen
* ���ܣ����ش���1���ջ��������ݳ��Ȳ�ѯ
* ��ڲ�������
* ���ڲ�������
* ����ֵ�����ջ��������ݳ���
* ��ע��
****************************************************************************/ 

unsigned char  PPC_Com1RxLen (void)
{
    unsigned char len;

    len = (unsigned char)(COM[COM1].Rxhead - COM[COM1].Rxtail);  
    return (len);
}

/****************************************************************************
* ���ƣ�PPC_Com1TxLen
* ���ܣ����ش���1���ͻ��������ݳ��Ȳ�ѯ
* ��ڲ�������
* ���ڲ�������
* ����ֵ�����ͻ��������ݳ���
* ��ע��
****************************************************************************/ 

unsigned char  PPC_Com1TxLen (void)
{
    unsigned char len;
    
    len = (unsigned char)(COM[COM1].Txhead - COM[COM1].Txtail);
    return (len);
}

/****************************************************************************
* ���ƣ�PPC_Com1In
* ���ܣ����ش���1��ȡ����������
* ��ڲ�����buf[]--���ݴ洢��ַ��len--��ȡ�ĳ���
* ���ڲ�������
* ����ֵ��ʵ�����ݳ���
* ��ע��
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
* ���ƣ�PPC_Com1Out
* ���ܣ����ش���1��������
* ��ڲ�����buf[]--���ݴ洢��ַ��len--��ȡ�ĳ���
* ���ڲ�������
* ����ֵ��ʵ�ʷ������ݳ���
* ��ע��
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
* ���ƣ�PPC_Com1InterruptHandler
* ���ܣ����ش���1�жϴ�����
* ��ڲ�������
* ���ڲ�������
* ����ֵ����
* ��ע��
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


