#ifndef _PARM_H_
#define _PARM_H_

extern  INT8U    UserMsg[14];                      /*[用户特殊信息]*/

        void  MSG_SetParm(void);                  /*[保存用户信息]*/
        void  MSG_GetParm(void);                  /*[获取用户信息]*/
        void  CFG_SetParm(void);                  /*[保存配置参数]*/
        void  CFG_GetParm(void);                  /*[获取配置参数]*/

#endif
