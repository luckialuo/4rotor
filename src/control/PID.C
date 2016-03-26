#include "MPC.H"

/*--------------------------------------------------------------------------*/

KPIDStruc K,K_mix,K0;

/*--------------------------------------------------------------------------*/
void  PID_GetParm (void)
{
    INT16S      idx;
    INT8U    Buf[32];
    union   { INT8U B[2]; INT16S   D; } src;
    
    ROM_ReadBlock(2, Buf, sizeof(Buf));
    for (idx=0; idx<10; idx++) {
        src.B[1]=Buf[2*idx+0]; src.B[0]=Buf[2*idx+1];  K.f[idx] =src.D*0.01f;
    }
    ROM_ReadBlock(3, Buf, sizeof(Buf));
    for (idx=0; idx<12; idx++) {
        src.B[1]=Buf[2*idx+0]; src.B[0]=Buf[2*idx+1];  K.f[idx+10] =src.D*0.01f;
    }
    

    
    if(fabs(K.P.Kagama)<EPS)   K.P.Kagama=0.01f;
    if(fabs(K.P.Ketheta)<EPS)  K.P.Ketheta=0.01f;   


    K0=K;
    

}


void  PID_SetParm (void)
{
    INT16S      idx;
    INT8U    Buf[32];
    union   { INT8U B[2]; INT16S   D; } src;
    
    for (idx=0; idx<10; idx++) {
        src.D=(INT16S  )(K.f[idx] *100.0f);   Buf[2*idx+0]=src.B[1]; Buf[2*idx+1]=src.B[0];
    }
    ROM_WriteBlock(2, Buf, sizeof(Buf));

    for (idx=0; idx<12; idx++) {
        src.D=(INT16S  )(K.f[idx+10] *100.0f);   Buf[2*idx+0]=src.B[1]; Buf[2*idx+1]=src.B[0];
    }
    ROM_WriteBlock(3, Buf, sizeof(Buf));
}
