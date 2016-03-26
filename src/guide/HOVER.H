#ifndef _HOVER_H_
#define _HOVER_H_

extern  PointStruc   HoverWay[7];       /*[盘旋航路点数据结构]*/
extern  INT16S           HoverDot,          /*[当前盘旋点号][0~6]*/
                     HoverNum;          /*[盘旋圈数]*/

void    GUID_HoverInit(INT16S  clockwise);           /*[盘旋初始化,用于计算HoverWay]*/
void    GUID_HoverLine(INT16S  dot, LineStruc *AB);  /*[盘旋 读取盘旋点号]*/
void    GUID_Hover(void);                 /*[盘旋飞行管理]*/

#endif
