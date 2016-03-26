#ifndef _HOME_H_
#define _HOME_H_

extern  FP32   HomeLon, HomeLat;                                   /*[返回点参考位置]*/
                     
void    GUID_HomePsi(FP32 ac_lon, FP32 ac_lat, FP32 *psi);         /*[计算当前位置与返回点之间的地理航向]*/
void    GUID_HomeLine(FP32 ac_lon, FP32 ac_lat, LineStruc *AB);    /*[由当前位置和返回点形成航段AB]*/
void    GUID_HomeCheckGPS(void);                                   /*[监控GPS状态]*/
void    GUID_Home(void);                                           /*[返航管理]*/

#endif
