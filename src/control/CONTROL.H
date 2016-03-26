#ifndef _CONTROL_H_
#define _CONTROL_H_


/***************************************************************/

#define PW_LateNone        0                      /*[�޶���]*/
#define PW_LateLeft        1                      /*[����ģ̬]*/
#define PW_LateRight       2                      /*[����ģ̬]*/

#define PW_LongNone        0                      /*[�޶���]*/
#define PW_LongForth       1                      /*[��ǰģ̬]*/
#define PW_LongBack        2                      /*[���ģ̬]*/

#define PW_VertNone        0                      /*[�޶���]*/
#define PW_VertUp          1                      /*[����ģ̬]*/
#define PW_VertDown        2                      /*[����ģ̬]*/

#define PW_RotaNone        0                      /*[�޶���]*/
#define PW_RotaLeft        1                      /*[����ģ̬]*/
#define PW_RotaRight       2                      /*[����ģ̬]*/


/***************************************************************/

#define PW_GamaLeft         -2.0f                    /*[�����ת��ָ��][-10��]*/
#define PW_GamaRight         2.0f                    /*[���ҹ�ת��ָ��][+10��]*/

#define PW_ThetaForth       -2.0f                    /*[��ǰ������ָ��][-10��]*/
#define PW_ThetaBack         2.0f                    /*[�������ָ��][+10��]*/

#define PW_HdotUp            1.0f                     /*[���������ٶ�ָ��][+1m/s]*/
#define PW_HdotDown         -1.0f                     /*[���������ٶ�ָ��][-1m/s]*/

#define PW_WyLeft            10.0f                    /*[����ƫ�����ٶ�ָ��][+10��/s]*/
#define PW_WyRight          -10.0f                    /*[����ƫ�����ٶ�ָ��][-10��/s]*/

/***************************************************************/

#define TOKEN_LateNone     0                      /*[������]*/
#define TOKEN_TurnLeft     1                      /*[ָ����������]*/
#define TOKEN_TurnRight    2                      /*[ָ����������]*/
#define TOKEN_TrackWay     3                      /*[��ƫ��������]*/

#define TOKEN_LongNone     0                      /*[������]*/
#define TOKEN_TurnForth    1                      /*[ָ����ǰ����]*/
#define TOKEN_TurnBack     2                      /*[ָ���������]*/

#define TOKEN_VertNone     0                      /*[������]*/
#define TOKEN_TurnUp       1                      /*[ָ����������]*/
#define TOKEN_TurnDown     2                      /*[ָ����������]*/

#define TOKEN_RotaNone     0                      /*[������]*/
#define TOKEN_RotaLeft     1                      /*[ָ����������]*/
#define TOKEN_RotaRight    2                      /*[ָ����������]*/



/***************************************************************/

extern INT8U    mode_late,mode_long,mode_vert,mode_rota,
                token_late,token_long,token_vert,token_rota;

extern INT16S   on_sky, on_takeoff,takeoff_pre;
extern int      tag_home, tag_land, tag_endwp;
                            

void    LATE(void);                     
void    LONG(void);                  
void    VERT(void);                
void    ROTA(void);                     
void    LATE_TrackWay(void);

#endif