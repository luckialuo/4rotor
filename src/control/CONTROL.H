#ifndef _CONTROL_H_
#define _CONTROL_H_


/***************************************************************/

#define PW_LateNone        0                      /*[无定义]*/
#define PW_LateLeft        1                      /*[向左模态]*/
#define PW_LateRight       2                      /*[向右模态]*/

#define PW_LongNone        0                      /*[无定义]*/
#define PW_LongForth       1                      /*[向前模态]*/
#define PW_LongBack        2                      /*[向后模态]*/

#define PW_VertNone        0                      /*[无定义]*/
#define PW_VertUp          1                      /*[向上模态]*/
#define PW_VertDown        2                      /*[向下模态]*/

#define PW_RotaNone        0                      /*[无定义]*/
#define PW_RotaLeft        1                      /*[左旋模态]*/
#define PW_RotaRight       2                      /*[右旋模态]*/


/***************************************************************/

#define PW_GamaLeft         -2.0f                    /*[向左滚转角指令][-10度]*/
#define PW_GamaRight         2.0f                    /*[向右滚转角指令][+10度]*/

#define PW_ThetaForth       -2.0f                    /*[向前俯仰角指令][-10度]*/
#define PW_ThetaBack         2.0f                    /*[向后俯仰角指令][+10度]*/

#define PW_HdotUp            1.0f                     /*[向上升降速度指令][+1m/s]*/
#define PW_HdotDown         -1.0f                     /*[向下升降速度指令][-1m/s]*/

#define PW_WyLeft            10.0f                    /*[向左偏航角速度指令][+10度/s]*/
#define PW_WyRight          -10.0f                    /*[向右偏航角速度指令][-10度/s]*/

/***************************************************************/

#define TOKEN_LateNone     0                      /*[空令牌]*/
#define TOKEN_TurnLeft     1                      /*[指令向左令牌]*/
#define TOKEN_TurnRight    2                      /*[指令向右令牌]*/
#define TOKEN_TrackWay     3                      /*[侧偏跟踪令牌]*/

#define TOKEN_LongNone     0                      /*[空令牌]*/
#define TOKEN_TurnForth    1                      /*[指令向前令牌]*/
#define TOKEN_TurnBack     2                      /*[指令向后令牌]*/

#define TOKEN_VertNone     0                      /*[空令牌]*/
#define TOKEN_TurnUp       1                      /*[指令向上令牌]*/
#define TOKEN_TurnDown     2                      /*[指令向下令牌]*/

#define TOKEN_RotaNone     0                      /*[空令牌]*/
#define TOKEN_RotaLeft     1                      /*[指令左旋令牌]*/
#define TOKEN_RotaRight    2                      /*[指令右旋令牌]*/



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
