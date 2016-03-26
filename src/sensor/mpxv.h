#ifndef __MPXV__
#define __MPXV__

double CaculHeight(double detain);
double CaculSpeed(double detein);
void   Task_MpxvRev(void);
void   MPXV_Monitor(void);
    
/*---------------------------------------------------------------------------*/
	extern SensorStruc	 ss_Mpxv;
	extern FP32           Vi_adc;                        /*[adc 空速][m]*/
	extern FP32        height_adc;                       /*[adc气压高度][m]*/
/*---------------------------------------------------------------------------*/
    
#endif