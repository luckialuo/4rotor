#ifndef _GUIDE_H_
#define _GUIDE_H_


/*[导航方式定义]*/
#define PW_GuideNone       0                      /*[指令遥控]*/
#define PW_GuideHover      1                      /*[悬停导航]*/
#define PW_GuideP2P        2                      /*[点到点导航]*/
#define PW_GuideAuto       3                      /*[切入自主导航]*/
#define PW_GuidePosition   4                      /*[视觉导航]*/

#define PW_GuideDim1       5                      /*[一维导航][定向]*/
#define PW_GuideDim2       6                      /*[二维导航]*/
#define PW_GuideDim3       7                      /*[三维导航]*/

/*[自主飞行模态定义]*/
#define PW_NavNone         0                      /*[人工引导模态]*/
#define PW_NavHover        1                      /*[悬停模态]*/
#define PW_NavP2P          2                      /*[点到点模态]*/
#define PW_NavAuto         3                      /*[切入自主模态]*/
#define PW_NavPosition     4                      /*[视觉模态]*/
#define PW_NavEnter        5                      /*[点号切入模态]*/

#define PW_NavSpec         6                      /*[航线飞行模态]*/
#define PW_NavHome         7                      /*[回家模态]*/

#define SOUND_None         0                     /*蜂鸣器不响*/
#define SOUND_BiBi           1                     /*蜂鸣器响*/

#define URG_None              0                     /*urg导航模态*/
#define URG_Tkoff              1                     /*urg起飞*/
#define URG_Enter              2                     /*urg进窗*/
#define URG_Corridor        3                     /*urg走廊*/

extern  INT8U        ac_dot;                    /*[当前航段号]*/
extern  INT8U        land_dot;
extern  FP32         ac_dZ,                     /*[侧偏距]*/
                               ac_dL,                     /*[待飞距]*/
                               ac_dH,                     /*[高度差]*/
                               ac_Hdot,
                               urg_dPsi1,                    
                               ac_dPsi;                   /*[偏航角]*/
extern  LineStruc    AB;
extern  FP32         psi_cmd;                   /*[航向跟踪指令]*/

extern  INT8U        cmd_guid,                  /*[期望导航方式]*/
                     mode_guid,                 /*[导航方式]*/
                     nav_guid,                  /*[导航模态]*/
                     sound,
                     info_guid,
                     urg_guid;                 /*[导航信息来源]*/
                         
extern  INT16S       prompt_guid;               /*[预导航标志][1=预导航有效][1=无效]*/
extern  float        dZ_mix,
                     dL_mix;
extern  INT16S  dZ_mix0, dL_mix0;

extern  INT16U   time_spec,spec_cnt;


void    GUID_Exit(void);                          /*[退出自主导航响应]*/
void    GUID_Spec(void);
void sound_bibi(void);                         /*蜂鸣器比比声*/
void    GUID_Hover(void);                         /*[悬停飞行管理]*/
void    GUID_AutoFly(void);                       /*[切入自主飞行管理]*/

#endif
