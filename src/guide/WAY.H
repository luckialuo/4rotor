#ifndef _WAY_H_
#define _WAY_H_

extern  float    RunwayLon,                    /*[�ܵ��ο��㾭��][deg]*/
	             RunwayLat;                    /*[�ܵ��ο���γ��][deg]*/
extern  float    RunwayPsi;                    /*[�ܵ���½����][deg]*/
extern  float    RunwayAlt;                    /*[�ܵ�����][m]*/
extern  float    RunwayOffset;                 /*[�ܵ���ƫ��][deg]*/

void    WAY_GetParm(void);
void    WAY_SetParm(void);

#endif