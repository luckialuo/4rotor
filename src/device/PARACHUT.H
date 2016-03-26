#ifndef _PARACHUT_H_
#define _PARACHUT_H_

extern INT16S            open_par,                    /*[Ԥ��ɡ��Ч��־][1=��Ч][0=��Ч]*/
                     safe_par,                    /*[��ȫ�߶ȿ�ɡ��־]*/
                     auto_par;                    /*[�������Զ���ɡ����]*/

       void        PAR_Monitor(void );             /*[Ԥ��ɡ�������][Task]*/
       void        PAR_AutoOpen(void );            /*[�Զ���ɡ����][Task]*/
       void        PAR_SafeOpen(void);            /*[��ȫ��ɡ����][Task]*/
       void        PAR_ON(void);                  /*[��ɡ����ߵ�ƽ]*/
       void        PAR_OFF(void);                 /*[��ɡ����͵�ƽ]*/

#endif