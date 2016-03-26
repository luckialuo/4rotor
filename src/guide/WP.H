#ifndef _WP_H_
#define _WP_H_

typedef struct {
    int     dot;              /*[�����]*/
    float   lon,              /*[���㾭��][deg]*/
            lat;              /*[����γ��][deg]*/
    float   alt;              /*[�߶�][m]*/
    WORD    vxd;              /*[��������]*/
} PointStruc;

typedef struct {
    float    psi;              /*[���η�λ��]deg]*/
    float    alt;              /*[���θ߶�][m]*/
    WORD     vxd;              /*[��������]*/
    float    lon,lat;          /*[�����յ㾭γ��][deg]*/
    float    len;              /*[���γ���][m]*/
} LineStruc;


float    WP_Psi2Psi(float A);                     /*[������λ��(0~360)�ļ���ֵת��Ϊ(-180~+180)]*/
float    WP_Psi(float x,float y);                 /*[����ֱ������(x,y)�γɵĺ���λ��]*/
void    WP_Pos2XY(float lon_ref,float lat_ref, float lon,float lat, float *x,float *y);
                                                  /*[����γ��ת��Ϊ����ϵֱ������]*/
void    WP_XY2Pos(float lon_ref,float lat_ref, float x,float y, float *lon,float *lat);
                                                  /*[������ϵֱ������ת��Ϊ��γ��]*/
void    WP_RotateXY(float x, float y, float Psi, float *xR, float *yR);
                                                  /*[������ϵֱ������(x,y)��ת���溽��Psi��]*/

INT16S   WP_GetPoint(INT16S  dot, PointStruc *A); /*[ȡ��dot����·������]*/
int     WP_GetLine (int dot, LineStruc *AB);      /*[ȡ��dot����������]*/
void    WP_MakeLine(float lon_a,float lat_a, float lon_b,float lat_b, LineStruc *AB);
                                                  /*[����A,B������ȡ��������]*/
void    WP_LateWay(LineStruc *AB, float lon, float lat, float psi, float *dZ, float *dL, float *dPsi);
                                                  /*[��λ��(lon,lat)����ں���AB�Ĵ��ɾ���Ͳ�ƫ��]*/
FP32  Psi_360(FP32 angle);
void WP_BL2xy(double B, double L, double *x, double *y);

#endif