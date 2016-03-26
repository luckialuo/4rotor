#ifndef _ALIP_H_
#define _ALIP_H_


extern float	   gama1_AoL,		       /*[陡下滑角](deg)*/
                   gama1_AoL_mix;              /*[陡下滑角遥调](deg)*/
extern float  RunwayAlt_mix;

void    ALIP_Init(void);               /*[对下滑轨迹线参数初始化]*/  
float   ALIP_Profile(float X);          /*[从下滑轨迹线上获取高度指令](m)*/

#endif
