#ifndef _FUSION_H_
#define _FUSION_H_

extern  FP32    ac_lon, ac_lat;         /*[经度/纬度]*/
extern  FP32    ac_Vd,                  /*[地速]*/
                ac_psi,                 /*[真航向][0~360]*/
                psi_cat;
           
extern  FP32    ac_height;
extern  INT32S  info_alt;               /*[高度信息源]*/
extern  INT16S    dL_mix0,  dZ_mix0;


void        fusion_refresh_gps(FP32 lon, FP32 lat, FP32 psi);
void        fusion_guide(void);
void        fusion_slow(void);

#endif
