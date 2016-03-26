#ifndef _GUIDE_H_
#define _GUIDE_H_


/*[������ʽ����]*/
#define PW_GuideNone       0                      /*[ָ��ң��]*/
#define PW_GuideHover      1                      /*[��ͣ����]*/
#define PW_GuideP2P        2                      /*[�㵽�㵼��]*/
#define PW_GuideAuto       3                      /*[������������]*/
#define PW_GuidePosition   4                      /*[�Ӿ�����]*/

#define PW_GuideDim1       5                      /*[һά����][����]*/
#define PW_GuideDim2       6                      /*[��ά����]*/
#define PW_GuideDim3       7                      /*[��ά����]*/

/*[��������ģ̬����]*/
#define PW_NavNone         0                      /*[�˹�����ģ̬]*/
#define PW_NavHover        1                      /*[��ͣģ̬]*/
#define PW_NavP2P          2                      /*[�㵽��ģ̬]*/
#define PW_NavAuto         3                      /*[��������ģ̬]*/
#define PW_NavPosition     4                      /*[�Ӿ�ģ̬]*/
#define PW_NavEnter        5                      /*[�������ģ̬]*/

#define PW_NavSpec         6                      /*[���߷���ģ̬]*/
#define PW_NavHome         7                      /*[�ؼ�ģ̬]*/

#define SOUND_None         0                     /*����������*/
#define SOUND_BiBi           1                     /*��������*/

#define URG_None              0                     /*urg����ģ̬*/
#define URG_Tkoff              1                     /*urg���*/
#define URG_Enter              2                     /*urg����*/
#define URG_Corridor        3                     /*urg����*/

extern  INT8U        ac_dot;                    /*[��ǰ���κ�]*/
extern  INT8U        land_dot;
extern  FP32         ac_dZ,                     /*[��ƫ��]*/
                               ac_dL,                     /*[���ɾ�]*/
                               ac_dH,                     /*[�߶Ȳ�]*/
                               ac_Hdot,
                               urg_dPsi1,                    
                               ac_dPsi;                   /*[ƫ����]*/
extern  LineStruc    AB;
extern  FP32         psi_cmd;                   /*[�������ָ��]*/

extern  INT8U        cmd_guid,                  /*[����������ʽ]*/
                     mode_guid,                 /*[������ʽ]*/
                     nav_guid,                  /*[����ģ̬]*/
                     sound,
                     info_guid,
                     urg_guid;                 /*[������Ϣ��Դ]*/
                         
extern  INT16S       prompt_guid;               /*[Ԥ������־][1=Ԥ������Ч][1=��Ч]*/
extern  float        dZ_mix,
                     dL_mix;
extern  INT16S  dZ_mix0, dL_mix0;

extern  INT16U   time_spec,spec_cnt;


void    GUID_Exit(void);                          /*[�˳�����������Ӧ]*/
void    GUID_Spec(void);
void sound_bibi(void);                         /*�������ȱ���*/
void    GUID_Hover(void);                         /*[��ͣ���й���]*/
void    GUID_AutoFly(void);                       /*[�����������й���]*/

#endif