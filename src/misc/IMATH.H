#ifndef _MATH_H_
#define _MATH_H_

void  SemInit( );
void  SemLock(  );
void  SemUnLock( );

FP32 fexp(FP32 x);
FP32 fcos(FP32 x);
FP32 fsin(FP32 x);


FP32 fatan2(FP32 x,FP32 y);

FP32 fpow(FP32 x,FP32 y);


INT32S    iexp(INT32S   x);
INT16S    isin(INT16S   x);
INT16S    icos(INT16S   x);
INT32S    iatan(INT32S   x);
INT32S    iatan2(INT32S   y,INT32S    x);

#endif
