#ifndef _FUSION_H_
#define _FUSION_H_

extern  FP32    ac_lon, ac_lat;         /*[����/γ��]*/
extern  FP32    ac_Vd,                  /*[����]*/
                ac_psi,                 /*[�溽��][0~360]*/
                psi_cat;
           
extern  FP32    ac_height;
extern  INT32S  info_alt;               /*[�߶���ϢԴ]*/
extern  INT16S    dL_mix0,  dZ_mix0;


void        fusion_refresh_gps(FP32 lon, FP32 lat, FP32 psi);
void        fusion_guide(void);
void        fusion_slow(void);

#endif