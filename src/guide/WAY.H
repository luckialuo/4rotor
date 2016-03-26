#ifndef _WAY_H_
#define _WAY_H_

extern  float    RunwayLon,                    /*[跑道参考点经度][deg]*/
	             RunwayLat;                    /*[跑道参考点纬度][deg]*/
extern  float    RunwayPsi;                    /*[跑道着陆航向][deg]*/
extern  float    RunwayAlt;                    /*[跑道场高][m]*/
extern  float    RunwayOffset;                 /*[跑道磁偏角][deg]*/

void    WAY_GetParm(void);
void    WAY_SetParm(void);

#endif
