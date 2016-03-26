#include "MPC.h"


void  Sys_Init(void)
{
	initPll(); 
    
    disableIrq(); 
    intInit(); 
    SpiFlashInit();
    NvramInit();
    EtpuInit();
    LedInit();
    AnalogInit();
    MpwmInit();
    time_init();
  
    PPC_Com1Init(57600,COM_PARITY_NONE); 
    PPC_Com1EnableInterrupt(); 
    UartCom2Init(115200,RS232,COM_PARITY_NONE);	//URGͨѶ
    UartCom3Init(115200,RS232,COM_PARITY_NONE);	//for AHRS
    UartCom4Init(9600,RS232,COM_PARITY_NONE);	//for SRF_TTL�Եس�����
//UartCom5Init(9600,RS232,COM_PARITY_NONE);	
//UartCom6Init(9600,RS232,COM_PARITY_NONE);	
    UartCom7Init(9600,RS232,COM_PARITY_NONE);	//������ɣ��SRWF 1028 Ϊ9600 ��XBEEΪ115200  ��TTL)

		
    enableIrq();
    
    ROM_LoadFlash();  
    RestoreParmROM();
    RestoreRPVs();
    LAW_ParmInit(); 
 

}