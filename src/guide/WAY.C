#include "MPC.H"

/*----------------------------------------------------------------------------*/

    float    RunwayLon,
             RunwayLat;
    float    RunwayPsi;
    float    RunwayAlt;
    float    RunwayOffset;

/*----------------------------------------------------------------------------*/


void  WAY_GetParm (void)
{
    BYTE       Buf[32];
    dWordStruc src;
    
    ROM_ReadBlock(6, Buf, sizeof(Buf));
    src.B[0]=Buf[ 0]; src.B[1]=Buf[ 1];
    src.B[2]=Buf[ 2]; src.B[3]=Buf[ 3];    RunwayLon    =src.DW*1e-6; 
    src.B[0]=Buf[ 4]; src.B[1]=Buf[ 5];
    src.B[2]=Buf[ 6]; src.B[3]=Buf[ 7];    RunwayLat    =src.DW*1e-6;
    src.B[0]=Buf[ 8]; src.B[1]=Buf[ 9];    
    src.B[2]=Buf[10]; src.B[3]=Buf[11];    RunwayAlt    =src.DW/10.0f;
    src.B[0]=Buf[12]; src.B[1]=Buf[13];    RunwayPsi    =src.W[0]/10.0f;
    src.B[0]=Buf[14]; src.B[1]=Buf[15];    RunwayOffset =src.D[0]/10.0f;

  }


void  WAY_SetParm (void)
{
    BYTE       Buf[32];
    dWordStruc src;

    src.DW = RunwayLon*1e6;         Buf[ 0]=src.B[0]; Buf[ 1]=src.B[1];
                                    Buf[ 2]=src.B[2]; Buf[ 3]=src.B[3];
    src.DW = RunwayLat*1e6;;        Buf[ 4]=src.B[0]; Buf[ 5]=src.B[1];
                                    Buf[ 6]=src.B[2]; Buf[ 7]=src.B[3];
    src.DW = RunwayAlt*10.0f;       Buf[ 8]=src.B[0]; Buf[ 9]=src.B[1];
                                    Buf[10]=src.B[2]; Buf[11]=src.B[3];
    src.W[0] = RunwayPsi*10.0f;     Buf[12]=src.B[0]; Buf[13]=src.B[1];
    src.D[0] = RunwayOffset*10.0f;  Buf[14]=src.B[0]; Buf[15]=src.B[1];

    ROM_WriteBlock(6, Buf, sizeof(Buf));
}

