#ifndef __ZTTHREAD_H__
#define __ZTTHREAD_H__

#include <pthread.h>
#include "ztmutex.h"

typedef  void *(*THREAD_FUNC)(void*);
typedef  void (*THREAD_FUNC1)(void*);

//线程控制结构
typedef struct
{
    pthread_t       handle;  //线程句柄
    pthread_attr_t  pattr;   //线程属性
    THREAD_FUNC     func;    //线程函数指针
    void            *args;   //线程函数参数
}Tthread;

typedef struct
{
	TMutex *mutex;	//互斥锁
	pthread_cond_t cond;	//条件变量		
}TCond;

//cleanup 线程控制结构
typedef struct
{ 
    TMutex        *mutex;  //互斥锁
    THREAD_FUNC   func;  //线程执行函数指针
    void          *args;   //线程执行函数参数
    THREAD_FUNC1  cleanfunc;  //线程cancel响应时清理函数指针
    TCond  *tcond;	//条件变量控制结构
}TCleanUp;

//主线程接口
int ZTThread_Init(Tthread ** p_thread,THREAD_FUNC p_func,void *p_args);
int ZTThread_Destroy(Tthread *p_thread);
int ZTThread_Start(Tthread *p_thread);
int ZTThread_Join(Tthread *p_thread,void ** p_args);
int ZTThread_Cancel(Tthread *p_thread);

int ZTThread_Cond_Init(TCond ** p_cond);
int ZTThread_Cond_Destroy(TCond * p_cond);
int ZTThread_Cond_Signal(TCond * p_cond);
int ZTThread_Cond_BroadCast(TCond * p_cond);
int ZTThread_Cond_TimeWait(TCond * p_cond,int p_tMs);
int ZTThread_Cond_Wait(TCond * p_cond);


//子线程接口
void ZTSubThread_SetCancelmode();
void ZTSubThread_TestCancel();
void ZTSubThread_Exit(void * p_args);
void *ZTSubThread_Cleanup_Run(void * p_args);


#endif  //__ZTTHREAD_H__
