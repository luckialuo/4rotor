#ifndef _HOME_H_
#define _HOME_H_

extern  FP32   HomeLon, HomeLat;                                   /*[���ص�ο�λ��]*/
                     
void    GUID_HomePsi(FP32 ac_lon, FP32 ac_lat, FP32 *psi);         /*[���㵱ǰλ���뷵�ص�֮��ĵ�������]*/
void    GUID_HomeLine(FP32 ac_lon, FP32 ac_lat, LineStruc *AB);    /*[�ɵ�ǰλ�úͷ��ص��γɺ���AB]*/
void    GUID_HomeCheckGPS(void);                                   /*[���GPS״̬]*/
void    GUID_Home(void);                                           /*[��������]*/

#endif