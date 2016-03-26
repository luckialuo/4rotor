#ifndef _CMD_H_
#define _CMD_H_


extern  INT16S          tag_cmd_blocked;
extern  INT16S          on_reset;
extern  FP32            K_adjust;
extern  INT16S          on_safe;
extern  INT16S       fail_gps;

INT8U   TELE_GetCmd(INT8U B);              /*[将遥控指令原码翻译为遥控指令序号码]*/
void    TELE_CheckCmd(INT8U Cmd);          /*[遥控指令分析与执行]*/
void    TELE_Reset(void);                  /*[系统复位程序]*/

#endif
