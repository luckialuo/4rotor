#include "MPC.H"

/*--------------------------------------------------------------------------*/

    INT8U     UserMsg[14];

/*--------------------------------------------------------------------------*/

void  MSG_SetParm (void)
{
    INT8U   Buf[32];   
    INT8U   idx;
    
    for(idx=0;idx<14;idx++)   Buf[idx]=UserMsg[idx];
    
    ROM_WriteBlock(7, Buf, sizeof(Buf));
}
 
void  MSG_GetParm (void)
{
    INT8U   Buf[32];   
    INT8U   idx;
     
    ROM_ReadBlock(7, Buf, sizeof(Buf));
    
    for(idx=0;idx<14;idx++) UserMsg[idx]=Buf[idx];
}

void  CFG_SetParm (void)
{
    INT8U   Buf[32];   
    dWordStruc src;
                                              
    src.DW= psi_offset_hmr;               Buf[0]=src.B[3]; Buf[1]=src.B[2];
                                          Buf[2]=(BYTE)simu_gps;
    src.DW= height_ini*10.0f;             Buf[3]=src.B[3]; Buf[4]=src.B[2];
                                          Buf[8]=dot_total;
                                         
    
    ROM_WriteBlock(8, Buf, sizeof(Buf));
}

void  CFG_GetParm (void)
{
    INT8U   Buf[32];   
    dWordStruc src;
    
    ROM_ReadBlock(8, Buf, sizeof(Buf));
                                                
    src.B[1]=Buf[0]; src.B[0]=Buf[1];       psi_offset_hmr = src.D[0];
                                            simu_gps = Buf[2];
    src.B[1]=Buf[3]; src.B[0]=Buf[4];       height_ini = src.D[0]/10.0f;
                                            dot_total = Buf[8];                                            	

}
