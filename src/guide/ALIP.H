#ifndef _ALIP_H_
#define _ALIP_H_


extern float	   gama1_AoL,		       /*[���»���](deg)*/
                   gama1_AoL_mix;              /*[���»���ң��](deg)*/
extern float  RunwayAlt_mix;

void    ALIP_Init(void);               /*[���»��켣�߲�����ʼ��]*/  
float   ALIP_Profile(float X);          /*[���»��켣���ϻ�ȡ�߶�ָ��](m)*/

#endif