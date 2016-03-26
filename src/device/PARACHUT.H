#ifndef _PARACHUT_H_
#define _PARACHUT_H_

extern INT16S            open_par,                    /*[预开伞有效标志][1=有效][0=无效]*/
                     safe_par,                    /*[安全高度开伞标志]*/
                     auto_par;                    /*[航线上自动开伞特征]*/

       void        PAR_Monitor(void );             /*[预开伞监控任务][Task]*/
       void        PAR_AutoOpen(void );            /*[自动开伞任务][Task]*/
       void        PAR_SafeOpen(void);            /*[安全开伞任务][Task]*/
       void        PAR_ON(void);                  /*[开伞输出高电平]*/
       void        PAR_OFF(void);                 /*[开伞输出低电平]*/

#endif
