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
  
  Bolck 分配一览表
  ---------------
    No.0  --  AD[ 0]~AD[ 7]的比例因子和偏移量 
    No.1  --  AD[ 8]~AD[11]的比例因子和偏移量
    No.2  --  DA[ 0]~DA[ 7]的比例因子和偏移量
    No.3  --  PWMin[ 0]~PWMin[ 7]的比例因子和偏移量
    No.4  --  PWMout[ 0]~PWMout[ 7]的比例因子和偏移量       
    No.5  --  发动机状态参数
    No.6  --  机场跑道参数
    No.7  --  用户特殊参数
    No.8  --  修正配置参数
    No.9  --  刹车控制参数
***************************************/
