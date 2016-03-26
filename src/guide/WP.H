#ifndef _WP_H_
#define _WP_H_

typedef struct {
    int     dot;              /*[航点号]*/
    float   lon,              /*[航点经度][deg]*/
            lat;              /*[航点纬度][deg]*/
    float   alt;              /*[高度][m]*/
    WORD    vxd;              /*[任务特征]*/
} PointStruc;

typedef struct {
    float    psi;              /*[航段方位角]deg]*/
    float    alt;              /*[航段高度][m]*/
    WORD     vxd;              /*[任务特征]*/
    float    lon,lat;          /*[航段终点经纬度][deg]*/
    float    len;              /*[航段长度][m]*/
} LineStruc;


float    WP_Psi2Psi(float A);                     /*[将航向方位角(0~360)的计算值转换为(-180~+180)]*/
float    WP_Psi(float x,float y);                 /*[计算直角坐标(x,y)形成的航向方位角]*/
void    WP_Pos2XY(float lon_ref,float lat_ref, float lon,float lat, float *x,float *y);
                                                  /*[将经纬度转化为东北系直角坐标]*/
void    WP_XY2Pos(float lon_ref,float lat_ref, float x,float y, float *lon,float *lat);
                                                  /*[将东北系直角坐标转化为经纬度]*/
void    WP_RotateXY(float x, float y, float Psi, float *xR, float *yR);
                                                  /*[将东北系直角坐标(x,y)旋转到真航向Psi上]*/

INT16S   WP_GetPoint(INT16S  dot, PointStruc *A); /*[取第dot个航路点数据]*/
int     WP_GetLine (int dot, LineStruc *AB);      /*[取第dot个航段数据]*/
void    WP_MakeLine(float lon_a,float lat_a, float lon_b,float lat_b, LineStruc *AB);
                                                  /*[根据A,B两点求取航段数据]*/
void    WP_LateWay(LineStruc *AB, float lon, float lat, float psi, float *dZ, float *dL, float *dPsi);
                                                  /*[求位置(lon,lat)相对于航段AB的待飞距离和侧偏距]*/
FP32  Psi_360(FP32 angle);
void WP_BL2xy(double B, double L, double *x, double *y);

#endif
