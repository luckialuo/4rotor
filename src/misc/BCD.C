#include "MPC.H"

INT8U    Bin2Bcd(INT8U  B)
{   return (B/10*16+B%10);  }

INT8U    Bcd2Bin(INT8U  B)
{   return (B/16*10+B%16);  }
