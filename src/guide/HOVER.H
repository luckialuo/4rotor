#ifndef _HOVER_H_
#define _HOVER_H_

extern  PointStruc   HoverWay[7];       /*[������·�����ݽṹ]*/
extern  INT16S           HoverDot,          /*[��ǰ�������][0~6]*/
                     HoverNum;          /*[����Ȧ��]*/

void    GUID_HoverInit(INT16S  clockwise);           /*[������ʼ��,���ڼ���HoverWay]*/
void    GUID_HoverLine(INT16S  dot, LineStruc *AB);  /*[���� ��ȡ�������]*/
void    GUID_Hover(void);                 /*[�������й���]*/

#endif