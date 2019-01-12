#include "ztthread.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  THREAD_STACK_SIZE   2*1024*1024

#ifndef NULL
    #define NULL 0
#endif


/*[method*******************************************************************************
 *def:  int ZTThread_Init(Tthread ** p_thread)
 *func: 线程构造函数,初始化线程函数指针和互斥对象
*************************************************************************************]*/
int ZTThread_Init(Tthread ** p_thread,THREAD_FUNC p_func,void *p_args)
{
    Tthread* ctrl=NULL;

    if(p_thread == NULL) return -1;

    ctrl = (Tthread*)malloc(sizeof(Tthread));
    memset(ctrl, 0, sizeof(Tthread));

    ctrl->func = p_func;
    ctrl->args = p_args;

    *p_thread = ctrl;
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTThread_Destroy(Tthread *p_thread)
 *func: 线程析构函数,释放互斥对象
*************************************************************************************]*/
int ZTThread_Destroy(Tthread *p_thread)
{
    Tthread* ctrl=(Tthread*)p_thread;
    void ** p = NULL;
    if(p_thread == NULL) return -1;

    //删除线程属性结构
    pthread_attr_destroy(&(ctrl->pattr));

    //将该子线程的状态设置为detached,则该线程运行结束后会自动释放所有资源
    //父线程调用方式 pthread_detach(thread_id)（非阻塞，可立即返回）
    //pthread_detach(pthread_self());
    //pthread_detach(ctrl->handle);  //会影响后续启动线程的cleanup操作
    ZTThread_Join(ctrl,p);
    
    free(p_thread);
    return 0;
}


/*[method*******************************************************************************
 *def:  int ZTThread_Start(Tthread *p_thread)
 *func: 启动线程
*************************************************************************************]*/
int ZTThread_Start(Tthread *p_thread)
{
    Tthread* ctrl=(Tthread*)p_thread;
    if(p_thread == NULL) return -1;

    pthread_attr_init(&(ctrl->pattr));
    pthread_attr_setstacksize(&(ctrl->pattr), THREAD_STACK_SIZE);
    
    return pthread_create(&(ctrl->handle), &(ctrl->pattr), (ctrl->func),ctrl->args);
}


/*[method*******************************************************************************
 *def:  int ZTThread_Join(Tthread *p_thread)
 *func: 主线程等待某子线程执行结束 合并子线程 
        以阻塞的方式等待thread指定的线程结束。当函数返回时，被等待线程的资源被收回。
        如果线程已经结束，那么该函数会立即返回
 *args: p_thread 线程控制结构指针
        p_args   子线程调用 phread_exit()是传出的对象指针       
*************************************************************************************]*/
int ZTThread_Join(Tthread *p_thread,void **p_args)
{
    Tthread* ctrl=(Tthread*)p_thread;
    if(p_thread == NULL) return -1;

    return pthread_join(ctrl->handle, p_args);
}


/*[method*******************************************************************************
 *def:  int ZTThread_Cancel(Tthread *p_thread)
 *func: 主线程发送取消子线程请求
        pthread_cancel调用并不等待线程终止，它只提出请求。子线程在取消请求(pthread_cancel)发出后会继续运行，
        直到到达某个取消点(CancellationPoint)。取消点是线程检查是否被取消并按照请求进行动作的一个位置

        Pthread标准指定了以下几个取消点：
             pthread_testcancel
             所有调度点，如pthread_cond_wait、sigwait、select、sleep等
             试验表明 printf也是一个取消点        
*************************************************************************************]*/
int ZTThread_Cancel(Tthread *p_thread)
{
    Tthread* ctrl=(Tthread*)p_thread;
    if(p_thread == NULL) return -1;

    return pthread_cancel(ctrl->handle);
}

/*[method*******************************************************************************
 *def:  int ZTThread_Cond_Init(TCond ** p_cond)
 *func: 创建并初始化一个条件变量结构
 *args: 
 *      p_cond 条件变量结构 
*************************************************************************************]*/
int ZTThread_Cond_Init(TCond ** p_cond)
{
    *p_cond = (TCond *)malloc(sizeof(TCond));

    pthread_cond_init(&((*p_cond)->cond),NULL);
    ZTMutex_Init(&((*p_cond)->mutex));
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTThread_Cond_Destroy(TCond * p_cond)
 *func: 释放条件变量结构
 *args: 
 *      p_cond 条件变量结构
*************************************************************************************]*/
int ZTThread_Cond_Destroy(TCond * p_cond)
{
    if(p_cond == NULL) return -1;

    ZTMutex_Destroy(p_cond->mutex);
    pthread_cond_destroy(&(p_cond->cond));

    free(p_cond);
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTThread_Cond_Signal(TCond * p_cond)
 *func: 激活一个等待该条件的线程
*************************************************************************************]*/
int ZTThread_Cond_Signal(TCond * p_cond)
{
   return pthread_cond_signal(&(p_cond->cond));
}

/*[method*******************************************************************************
 *def:  int ZTThread_Cond_BroadCast(TCond * p_cond)
 *func: 激活所有等待线程
*************************************************************************************]*/
int ZTThread_Cond_BroadCast(TCond * p_cond)
{
   return pthread_cond_broadcast(&(p_cond->cond));
}


/*[method*******************************************************************************
 *def:  int ZTThread_Cond_TimeWait(TCond * p_cond,int p_tMs)
 *func: 线程等待无条件等待条件变量
        调用此函数后 需要在 cleanup函数中解锁 mutex 否则muext 会一直死锁 
 *args: p_tMs 线程计时等待方式如果在给定时刻前条件没有满足，则返回ETIMEOUT，结束等待
*************************************************************************************]*/
int ZTThread_Cond_TimeWait(TCond * p_cond,int p_tMs)
{
    int iRet = 0;
    struct timespec reltime;

    //线程退出的时间点
    reltime.tv_sec = time(NULL) + p_tMs/1000;      
    reltime.tv_nsec = 0;

    ZTMutex_Lock(p_cond->mutex);
    //pthread_cond_timedwait 也是取消点之一
    //pthread_cond_timedwait()被取消，mutex是保持锁定状态的
    
    //函数原型
    //  int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime)
    //  abstime以与time()系统调用相同意义的绝对时间形式出现，0表示格林尼治时间1970年1月1日0时0分0秒。
    
    iRet = pthread_cond_timedwait(&(p_cond->cond),&(p_cond->mutex->mutex),&reltime);
    ZTMutex_Unlock(p_cond->mutex);

    return iRet;
}



/*[method*******************************************************************************
 *def:  int ZTThread_Cond_Wait(TCond * p_cond)
 *func: 线程等待无条件等待条件变量
        调用此函数后 需要在 cleanup函数中解锁 mutex 否则muext 会一直死锁 
*************************************************************************************]*/
int ZTThread_Cond_Wait(TCond * p_cond)
{
    int iRet = 0;
    ZTMutex_Lock(p_cond->mutex);
    //pthread_cond_wait 也是取消点之一
    //如果pthread_cond_wait()被取消，mutex是保持锁定状态的
    iRet = pthread_cond_wait(&(p_cond->cond),&(p_cond->mutex->mutex));
    ZTMutex_Unlock(p_cond->mutex);

    return iRet;
}


/*[method*******************************************************************************
 *def:  int ZTThread_CheckCancel()
 *func: 子线程中，设置线程取消信号响应方式
*************************************************************************************]*/
void ZTSubThread_SetCancelmode()
{

    //设置收到信号后设为CANCLED状态
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    //设置为收到信号后忽略CANCEL信号继续运行
    //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

    //延迟取消-设置收到取消信号后继续运行至下一个取消点再退出
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    //异步取消-设置收到取消信号后立即执行取消动作
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
}

/*[method*******************************************************************************
 *def:  int ZTThread_CheckCancel()
 *func: 子线程中，在不包含取消点，但是又需要取消点的地方创建一个取消点，以便在一个没有包含取消点的执行代码线程中响应取消请求
        线程取消功能处于启用状态且取消状态设置为延迟状态时，pthread_testcancel()函数有效
        务必仅在线程取消线程操作安全的序列中插入pthread_testcancel()
*************************************************************************************]*/
void ZTSubThread_TestCancel()
{
    pthread_testcancel();
}


/*[method*******************************************************************************
 *def:  int ZTThread_Exit()
 *func: 子线程调用，用来结束当前子线程
        线程通过调用pthread_exit函数终止执行，就如同进程在结束时调用exit函数一样。
        这个函数的作用是，终止调用它的线程并返回一个指向某个对象的指针,该指针可通过phthread_join()获得。
*************************************************************************************]*/
void ZTSubThread_Exit(void * p_args)
{
    pthread_exit(p_args);
}


/*[method*******************************************************************************
 *def:  void ZTSubThread_Cleanup_Run(void * p_args)
 *func: Cleanup模式线程执行体,本函数实现使用cancel方法保证正确释放互斥锁
 *args: p_args  TCleanUp结构指针 
 
        TCleanUp 结构中相关数据和函数 需另实现 
        TMutex       * mutex;  //互斥锁
        THREAD_FUNC  func;  //线程执行函数指针
        void         *args; //线程执行函数参数
        THREAD_FUNC1  cleanfunc;  //线程cancel响应时清理函数指针
*************************************************************************************]*/
void *ZTSubThread_Cleanup_Run(void * p_args)
{
    TCleanUp * ctrl = (TCleanUp *)p_args;

    ZTSubThread_SetCancelmode();  //1:设置cancel的响应方式

    /*
        子线程cancel方法终止时,执行的清理函数,用于保证正确释放互斥锁等
           
        函数原型 
           void pthread_cleanup_push(void (*routine) (void  *),  void *arg)        
           #routine 为cancel方法终止线程后 执行的清理函数
           #arg 为该清理函数传参

        pthread_cleanup_push() 采用先入后出的栈结构管理
        void routine(void *arg)函数在调用pthread_cleanup_push()时压入清理函数栈
        多次对pthread_cleanup_push()的调用将在清理函数栈中形成一个函数链
        在执行该函数链时按照压栈的相反顺序弹出

        PS: 
            pthread_cleanup_push()/pthread_cleanup_pop()是以宏方式实现的
            pthread_cleanup_push()带有一个"{"，而pthread_cleanup_pop()带有一个"}"
            因此这两个函数必须成对出现，且必须位于程序的同一级别的代码段中才能通过编译
    */
    pthread_cleanup_push(ctrl->cleanfunc, ctrl);  //2:设置线程被cancel时执行的事件
    ZTMutex_Lock(ctrl->mutex);        //加锁


    /*
        Pthread标准指定了以下几个取消点：
             pthread_testcancel
             所有调度点，如pthread_cond_wait、sigwait、select、sleep等
             试验表明 printf也是一个取消点  
        所以 线程实现主体函数 必须包括 以上一个或多个取消点
     */
    
    printf("---------------- %s -- %d ----------------\n",__func__,__LINE__);    
    (ctrl->func)(ctrl->args);
    printf("---------------- %s -- %d ----------------\n",__func__,__LINE__);

    ZTMutex_Unlock(ctrl->mutex);      //解锁
    /*
        对pthread_cleanup_push()绑定的清理函数，按照压栈的相反顺序弹出,可用于解绑清理函数

        函数原型
            void pthread_cleanup_pop(int execute)
            #execute参数表示执行到pthread_cleanup_pop()时是否在弹出清理函数的同时执行该函数
            为0表示不执行 非0为执行
     */
    pthread_cleanup_pop(0);         //取消cancel时执行的事件

    return NULL;
}
