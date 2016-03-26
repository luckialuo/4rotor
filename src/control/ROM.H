#ifndef _ROM_H_
#define _ROM_H_

        void    ROM_LoadFlash(void);
        void    ROM_SaveFlash(void);
        void    ROM_ReadBlock(INT16S  no, INT8U Buf[], INT16S  len);
        void    ROM_WriteBlock(INT16S  no, INT8U Buf[], INT16S  len);
        void    ROM_ReadWP (INT16S  dot, INT8U Buf[], INT16S  len);
        void    ROM_WriteWP(INT16S  dot, INT8U Buf[], INT16S  len);
        void    ROM_DeleteWP(void);

#endif


/**************************************
  
  Bolck ����һ����
  ---------------
    No.0  --  AD[ 0]~AD[ 7]�ı������Ӻ�ƫ���� 
    No.1  --  AD[ 8]~AD[11]�ı������Ӻ�ƫ����
    No.2  --  DA[ 0]~DA[ 7]�ı������Ӻ�ƫ����
    No.3  --  PWMin[ 0]~PWMin[ 7]�ı������Ӻ�ƫ����
    No.4  --  PWMout[ 0]~PWMout[ 7]�ı������Ӻ�ƫ����       
    No.5  --  ������״̬����
    No.6  --  �����ܵ�����
    No.7  --  �û��������
    No.8  --  �������ò���
    No.9  --  ɲ�����Ʋ���
***************************************/