#ifndef __ZTTLV_H__
#define __ZTTLV_H__

#include "ztmutex.h"

/*线程安全的*/

typedef struct
{
    char  caTag[5];
    //int   iTagLn;    //暂未使用
    char *caValue;    
    int   iValueLn;
    void *next;
}TTlvItem;

typedef struct
{
    TTlvItem  *header;      //头指针
    TMutex  *mutex;         //线程互斥锁    
}TTlv;


//创建一个ZTTLV数据存储结构
int ZTTlv_Init(TTlv **p_Ctrl);

//释放一个ZTTLV数据存储结构
int ZTTlv_Destroy(TTlv *p_Ctrl);

/*
    设置一个标签的值,如果该标签不存在,则添加一个标签
    p_caTag     标签
    p_caValue   标签对应的值
    p_iLn       值的长度
*/
int  ZTTlv_Set(TTlv *p_Ctrl,const char *p_caTag, const char *p_caValue, int p_iLn);

//打印所有的标签内容,调试用,p_iMaxLn打印的值的最大长度
int ZTTlv_Print(TTlv *p_Ctrl,int p_iMaxLn);

//清空所有的tlv名值对
int ZTTlv_Clear(TTlv *p_Ctrl);

//清空指定类型的标签, p_caTag指定标签的前缀
int ZTTlv_ClearTag(TTlv *p_Ctrl,const char *p_caTag);

//取得一个标签的值
int ZTTlv_Get(TTlv *p_Ctrl,const char *p_caTag, char *p_caValue,int *p_iLn);
//取得标签值
char *ZTTlv_GetTagValue(TTlv *p_Ctrl,const char *p_caTag);
//取得标签值长度
int ZTTlv_GetTagLen(TTlv *p_Ctrl,const char *p_caTag);

/*
    将一个标签的值组到指定的交易包中
    p_caTag     标签
    p_iBCD      是否执行压缩, 1:压缩, 2:不压缩
    p_caBuff    组包数据的缓冲区
    p_iBuffLn   已经有的包数据长度,组包后要更新该长度
*/
int ZTTlv_Seal(TTlv *p_Ctrl,const char *p_caTag, int p_iBCD, char *p_caBuff, int *p_iBuffLn);

//将指定的包中的一级tlv元素解出来
int ZTTlv_Unseal(TTlv *p_Ctrl,const char *p_caBuff, int p_iLn);

/*
    复合域打包 
    p_caTag     复合域标签
    p_caBuff    组包用的缓冲区
    p_ipLn      缓冲区长度
*/
int ZTTlv_Package(TTlv *p_Ctrl,char *p_caTag,char *p_caBuff, int *p_ipLn);

/*
    复合域解包 
    p_caBuff    组包用的缓冲区
    p_ipLn      缓冲区长度 暂未使用 可传0
*/
int ZTTlv_UnPackage(TTlv *p_Ctrl,const char *p_caBuff, int p_ipLn);

#endif  //__ZTTLV_H__
