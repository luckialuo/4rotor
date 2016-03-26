#include "MPC.H"

static INT8U  RomBuf[8192];  /*[8K FLASH]*/

void    ROM_LoadFlash (void)
{
  unsigned int n;
  unsigned long val;
  static unsigned long offset = 0x00000;
  

    for(n=0; n<=2048;n+=4)
    {
        val = SpiFlashRead(offset + n);
        
        RomBuf[n+3]=(unsigned char)val;
        RomBuf[n+2]=(unsigned char)(val>>8);
        RomBuf[n+1]=(unsigned char)(val>>16);
        RomBuf[n]=(unsigned char)(val>>24);     
    }
}

void    ROM_SaveFlash (void)
{
    unsigned long n;
    static unsigned long offset = 0x00000;
    union 
    {
        unsigned char B[4];
        unsigned long DW;
    }val;
   
    SpiFlashEraseSector(offset);
    for(n=0; n<=2048;n+=4)
    {
        val.B[3]=RomBuf[n+3];
        val.B[2]=RomBuf[n+2];
        val.B[1]=RomBuf[n+1];
        val.B[0]=RomBuf[n+0];
        SpiFlashProg(offset+n,val.DW);
    }
    
}

void  ROM_ReadBlock (INT16S  no, INT8U  Buf[], INT16S  len)
{
    INT16S  idx;
    for (idx=0; idx<len; idx++) Buf[idx]=RomBuf[no*32+idx];
}

void  ROM_WriteBlock (INT16S  no, INT8U  Buf[], INT16S  len)
{
    INT16S  idx;
    for (idx=0; idx<len; idx++) RomBuf[no*32+idx]=Buf[idx];
}

void  ROM_ReadWP (INT16S  dot, INT8U  Buf[], INT16S  len)
{
    INT16S  offset, idx;
    offset=1024+dot*len;
    for (idx=0; idx<len; idx++) Buf[idx]=RomBuf[offset+idx];
}

void  ROM_WriteWP (INT16S  dot, INT8U  Buf[], INT16S  len)
{
    INT16S  offset, idx;
    offset=1024+dot*len;
    for (idx=0; idx<len; idx++) RomBuf[offset+idx]=Buf[idx];
}

void  ROM_DeleteWP (void)
{
    INT16S  idx;
    for(idx=1024;idx<sizeof(RomBuf);idx++) RomBuf[idx]=0xff;
}

