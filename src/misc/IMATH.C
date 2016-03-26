#include "MPC.H"

void SemInit()
{
} 
                        
void  SemLock ()
{
}

void  SemUnLock()
{
}

FP32 fexp(FP32 x)    
{
    FP32 y;
    y=(float)exp(x);
    return y;
}

FP32 fcos(FP32 x)
{
    FP32 y;
    y=(float)cos(x);
    return y;
}

 
FP32 fsin(FP32 x)
{ 
    FP32 y;
	y=(float)sin(x);
    return y;	
}

FP32 fatan2(FP32 x,FP32 y)
{
    FP32 z;
    z=(float)atan2(x,y);
    return	z;
}

FP32 fpow(FP32 x,FP32 y)
{
    FP32 z;
    z=(float)pow(x,y);
    return	z;
}



