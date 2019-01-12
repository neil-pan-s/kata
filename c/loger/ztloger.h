#ifndef __ZTLOGER_H__
#define __ZTLOGER_H__

#include <stdbool.h>
#include "ztmutex.h"

/*
    要求日志文件中每行的长度,不能超过4096字节
*/

//日志级别
typedef enum
{
	LG_ERROR     = 0,     //严重错误
	LG_FLOW      = 1,     //流程信息
	LG_DEBUG     = 2,     //调试信息
	LG_HARD      = 7,     //硬件通讯信息
	LG_SEC       = 8,     //一般安全信息
	LG_MSEC      = 9      //重要安全信息
}TLogerLev;

struct ZTLoger_st
{
    int       iLines;           //文件的当前行数
    int       iMaxLines;        //允许保存的最大行数
    char      caFile[128];      //日志文件路径
    bool      blPrint;          //是否输出到标准错误设备
    TMutex  *mutex;            //日志文件锁
    TLogerLev stLogerLev;       //日志文件级别
};

typedef struct ZTLoger_st ZTLoger;

int ZTLoger_Init(ZTLoger **p_loger,const char *p_caFile, TLogerLev p_stLev, bool p_blPrint, int p_iMaxLines);
int ZTLoger_Close(ZTLoger *p_loger);
int ZTLoger_Check(ZTLoger *p_loger);
int ZTLoger_Write(ZTLoger *p_loger,TLogerLev p_stLev, bool p_blScreenFlag, const char *p_caFormat, ...);


#endif  //__LOGER_H__
