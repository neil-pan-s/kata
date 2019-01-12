#include "ztloger.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define __USE_BY_LINUX__

static unsigned int get_cur_msec();
static void get_datetime(char *p_caDate,char *p_caTime, char *p_caMsec);

/*[method***********************************************************************
 *def: int ZTLoger_Init(ZTLoger **p_loger　,const char *p_caFile, TLogerLev p_stLev, bool p_blPrint, int p_iMaxLines)
 *func: 日志对象构造函数.打开/创建一个日志结构.
 *args: p_loger　       日志文件结构
        p_caFile        日志文件路径
        p_stLev         允许记录的最大日志级别
        p_blPrint       是否打印调试信息到指定的输出设备上
        p_iMaxLines     允许保存的最大行数
*****************************************************************************]*/
int ZTLoger_Init(ZTLoger **p_loger,const char *p_caFile, TLogerLev p_stLev, bool p_blPrint, int p_iMaxLines)
{

    if(p_loger == NULL) return -1;

    *p_loger = NULL;    
    *p_loger = (void*)malloc(sizeof(ZTLoger));
    memset(*p_loger, 0, sizeof(ZTLoger));

    (*p_loger)->iLines     = 0;
    (*p_loger)->stLogerLev = p_stLev;
    (*p_loger)->blPrint    = p_blPrint;
    (*p_loger)->iMaxLines  = p_iMaxLines;

    sprintf((*p_loger)->caFile, "%s", p_caFile);

    //创建文件锁 
    ZTMutex_Init(&(*p_loger)->mutex);

    return 0;
}
/*[method***********************************************************************
 *def:  int ZTLoger_Close(ZTLoger *p_loger)
 *func: 日志结构析构函数.关闭日志文件.
*****************************************************************************]*/
int ZTLoger_Close(ZTLoger *p_loger)
{
    if(p_loger == NULL) return -1;

    if (NULL != p_loger->mutex)
    {
        ZTMutex_Destroy(p_loger->mutex);
        p_loger->mutex = NULL;
    }
    return 0;
}

/*[method***********************************************************************
 *def:  int ZTLoger_Check(ZTLoger *p_loger)
 *func: 检查文件内容是否超过规定大小,如果超过规定大小,则进行截断
 *args: p_loger　       日志文件结构
*****************************************************************************]*/
int ZTLoger_Check(ZTLoger *p_loger)
{
    int   i=0,iLines = 0;
    char  caLine[4096]={0}, caFile[128]={0}, caCmd[256]={0};
    FILE *fp=NULL;
    FILE *fp2=NULL;

    if(p_loger == NULL) return -1;

    //统计文件行数
    ZTMutex_Lock(p_loger->mutex);
    fp = fopen(p_loger->caFile, "r");
    if( fp == NULL )
    {
        ZTMutex_Unlock(p_loger->mutex);
        return -2;
    }

    while( 1 )
    {
        memset(caLine, 0, sizeof(caLine));
        if( fgets(caLine, sizeof(caLine), fp)==NULL ) break;
        iLines++;
    }
    fclose(fp);
    ZTMutex_Unlock(p_loger->mutex);

    //检查文件是否超过规定行数
    if( (0 < p_loger->iMaxLines) && (p_loger->iMaxLines < iLines) )
    {
        ZTMutex_Lock(p_loger->mutex);
        fp = fopen(p_loger->caFile, "r");
        //定位截断位置
        for(i=0; i<(iLines - (p_loger->iMaxLines)); i++)
        {
            fgets(caLine, sizeof(caLine), fp);
        }
        //保存日志到临时文件
        memset(caFile, 0, sizeof(caFile));
        sprintf(caFile, "%s.bak", p_loger->caFile);
        fp2 = fopen(caFile, "w");
        iLines = 0;    //重新统计文件的当前行数
        while( 1 )
        {
            memset(caLine, 0, sizeof(caLine));
            if( fgets(caLine, sizeof(caLine), fp)==NULL ) break;
            fwrite(caLine, 1, strlen(caLine), fp2);
            iLines++;
        }
        fclose(fp);
        fclose(fp2);
        p_loger->iLines = iLines;
        ZTMutex_Unlock(p_loger->mutex);

    #if defined(__USE_BY_LINUX__)
        memset(caCmd, 0, sizeof(caCmd));
        sprintf(caCmd, "mv %s %s", caFile, p_loger->caFile);
        system(caCmd);
    #elif defined(__USE_BY_WIN32__)
        MoveFileExA(caFile, p_loger->caFile, MOVEFILE_REPLACE_EXISTING);
    #endif
    }

    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTLoger_Write(ZTLoger *p_loger,TLogerLev p_stLev, bool p_blScreenFlag, const char *format, ...)
 *func: {04}根据格式字符串记录一行日志，每次自动添加日期时间。 &_
        换行符在格式字符串中指定.
 *args: p_loger　           日志文件结构        
        p_stLev             当前记录的日志级别
        p_blScreenFlag      本条信息是否允许输出到屏幕
        p_caFormat          格式字符串
 *ret:  0=   成功
        <0   失败
*************************************************************************************]*/
int ZTLoger_Write(ZTLoger *p_loger,TLogerLev p_stLev, bool p_blScreenFlag, const char *p_caFormat, ...)
{
    int  n=0, iMaxLines=0;
    char dt[124]={0};     //存放日期时间 + 日志级别信息
    FILE *fp=NULL;

    if(p_loger == NULL) return -1;

    //如果当前日志级别大于允许记录的日志级别,则不记录
    if( p_loger->stLogerLev < p_stLev ) return -2;

    //检查是否需要截断日志
    iMaxLines = (int)(((float)(p_loger->iMaxLines)) * 1.2 );
    if( iMaxLines < p_loger->iLines )
    {
        ZTLoger_Check(p_loger);
    }

    va_list arg_ptr;              //变体参数变量

    ZTMutex_Lock(p_loger->mutex);
    (p_loger->iLines)++;   //日志行数加1
    fp = fopen(p_loger->caFile, "a+");      //日志文件,以追加方式打开
    if(fp == NULL)
    {
        ZTMutex_Unlock(p_loger->mutex);
        return -3;
    }
    //取得变体参数,开始变体参数处理
    va_start(arg_ptr, p_caFormat);

    if( (p_blScreenFlag == 1) && (p_loger->blPrint == true) )
    {
        vfprintf(stderr, p_caFormat, arg_ptr);
    }

    //取得日期时间
    get_datetime(dt, (char*)(dt+11), (char*)(dt+20));
    dt[10] = 32;   dt[19] = 32;   dt[23] = 32;

    switch(p_stLev)
    {
        case LG_ERROR:{ strcat(dt," [LG_ERROR] "); break;} //严重错误
        case LG_FLOW:{ strcat(dt," [LG_FLOW] "); break;}  //流程信息
        case LG_DEBUG:{ strcat(dt," [LG_DEBUG] "); break;} //调试信息
        case LG_HARD:{ strcat(dt," [LG_HARD] "); break;}  //硬件通讯信息
        case LG_SEC:{ strcat(dt," [LG_SEC] "); break;}   //一般安全信息
        case LG_MSEC:{ strcat(dt," [LG_MSEC] "); break;}  //重要安全信息
        default:{ break;}
    }

    //写日期时间 + 日志级别信息
    fwrite(dt, 1, strlen(dt), fp);

    //将日志内容写入日志文件
    n = vfprintf(fp, p_caFormat, arg_ptr);  //返回值为写入的字节数
    //结束变体参数处理
    va_end(arg_ptr);

    //日志换行
    fwrite("\n", 1, 1, fp);

    //刷新文件
    fflush(fp);

    fclose(fp);

    //system("sync");

    ZTMutex_Unlock(p_loger->mutex);
    return 0;
}


/*[method*******************************************************************************
 *def:  static void  get_datetime(char *p_caDate,char *p_caTime, char *p_caMsec)
 *func: 根据需要取得当前日期的需要部分.
 *args: p_caDate      日期字符串,NULL表示不需要取日期
        p_caTime      时间字符串,NULL表示不需要取时间
        p_caMsec      毫秒字符串,NULL表示不需要取毫秒
 *ret:  0=   成功
        <0   失败
*************************************************************************************]*/
static void get_datetime(char *p_caDate,char *p_caTime, char *p_caMsec)
{
    time_t t;
    struct tm *tm;
    char tmp1[16]={0}, tmp2[16]={0}, tmp3[16]={0};

    //取得日期时间
    time(&t);
    tm = localtime(&t);

    //将日期时间格式化
    sprintf(tmp1, "%04d-%02d-%02d",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday);
    sprintf(tmp2, "%02d:%02d:%02d",tm->tm_hour,tm->tm_min,tm->tm_sec);
    sprintf(tmp3, "%03ud", get_cur_msec() % 1000);

    if(p_caDate != NULL) memcpy(p_caDate, tmp1, strlen(tmp1));
    if(p_caTime != NULL) memcpy(p_caTime, tmp2, strlen(tmp2));
    if(p_caMsec != NULL) memcpy(p_caMsec, tmp3, strlen(tmp3));
}

/*[method*******************************************************************************
 *def:  static unsigned int ZTLoger::get_cur_msec()
 *func: 获取时间的毫秒值
*************************************************************************************]*/
static unsigned int get_cur_msec()
{
    unsigned int us=0;

#if defined(__USE_BY_LINUX__)
    struct timeval tv;
    gettimeofday(&tv,NULL);
    us = tv.tv_sec*1000 + tv.tv_usec / 1000;
#elif defined(__USE_BY_WIN32__)
    us = GetTickCount();
#endif
    return us;
}
