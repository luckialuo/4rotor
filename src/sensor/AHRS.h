#ifndef _AHRS_H_
#define _AHRS_H_


void AHRSRx(BYTE Buf[]);
void Task_AHRSRev(void);
void AHRS_Monitor(void);
void	MTiG700_Rx(BYTE Buf[]);


extern FP32  Wx_gyo,Wy_gyo,Wz_gyo;
extern FP32  theta_gyo, gama_gyo, psi_hmr;
extern FP32  psi_offset_hmr;
extern FP32  lat_ahrs,lon_ahrs,height_ahrs,vel_x,vel_y,vel_z;
extern SensorStruc	 ss_AHRS;
extern FP32  accx;
extern FP32  accy;
extern FP32  accz;
extern INT8U  AHRS_status;

#endif
