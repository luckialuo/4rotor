#ifndef _TEST_H_
#define _TEST_H_

extern  INT8U   tag_test,                          /*[地面检测标志][1=接通][0=断开]*/
                on_test_load,                     /*[允许数据装定标志]*/
                on_test_save,                     /*[允许数据保存标志]*/
                on_test_back;                     /*[数据回传标志]*/
extern  INT8U    ask_cmd,                          /*[数据回传命令字]*/
                ask_idx;                          /*[数据回传索引]*/
extern  INT8U    dot_total;                        /*[航路点数]*/
extern	INT8U	echo_test;                        /*[地面检测的回馈标志]*/
extern  INT8U    on_DA_volts;                      /*[D/A的电压测试方式][1=电压测试][0=物理量测试]*/

        void    TEST_RxMan(INT8U Buf[]);           /*[上行帧接收管理]*/
        void    TEST_Class1(INT8U Buf[]);          /*[控制命令]*/
        void    TEST_Class2(INT8U Buf[]);          /*[输出命令]*/
        void    TEST_Class3(INT8U Buf[]);          /*[用户参数设置命令]*/
        void    TEST_Class4(INT8U Buf[]);          /*[航路点设置命令]*/
        void    TEST_Class5(INT8U Buf[]);          /*[参数查询命令]*/
        //void    TEST_ResetHMS(void);              /*[利用GPS校时]*/

        void    TEST_TxMan(void);                 /*[下行帧发送管理]*/
        void    TEST_Frame1(INT8U Buf[]);          /*[下行1#帧]*/
        void    TEST_Frame2(INT8U Buf[]);          /*[下行2#帧]*/
        void    TEST_Frame3(INT8U Buf[]);          /*[下行3#帧]*/
        void    TEST_Frame4(INT8U Buf[]);          /*[下行4#帧]*/
        void    TEST_Frame5(INT8U Buf[]);          /*[下行5#帧]*/
        void    TEST_Frame6(INT8U Buf[]);          /*[下行6#帧]*/
		void    TEST_Frame7(INT8U Buf[]);          /*[下行7#帧]*/

#endif
