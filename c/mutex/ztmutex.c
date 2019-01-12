#include "ztmutex.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*[method*******************************************************************************
 *def:  int ZTMutex_Init(TMutex *ctrl)
 *func: 创建并初始化一个互斥对象
 *args: 
 *      # ctrl 互斥信号结构 
*************************************************************************************]*/
int ZTMutex_Init(TMutex **ctrl)
{
    *ctrl = NULL;    
    *ctrl = (void*)malloc(sizeof(TMutex));
    memset(*ctrl, 0, sizeof(TMutex));

    //初始化互斥对象
    pthread_mutex_init(&((*ctrl)->mutex), NULL);
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTMutex_Destroy(TMutex *ctrl)
 *func: 释放互斥对象
 *args: 
 *      # ctrl 互斥信号结构
*************************************************************************************]*/
int ZTMutex_Destroy(TMutex *ctrl)
{
    if(ctrl == NULL) return -1;

    pthread_mutex_destroy(&(ctrl->mutex));
    free(ctrl);
    return 0;
}

/*[method*******************************************************************************
*def:  int ZTMutex_Lock(TMutex *ctrl)
*func: 加锁互斥对象
*args:
*      # ctrl 互斥信号结构
*************************************************************************************]*/
int ZTMutex_Lock(TMutex *ctrl)
{
    if(ctrl == NULL) return -1;

    pthread_mutex_lock(&(ctrl->mutex));
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTMutex_Unlock(TMutex *ctrl)
 *func: 解锁互斥对象
 *args:
 *      # ctrl 互斥信号结构
*************************************************************************************]*/
int ZTMutex_Unlock(TMutex *ctrl)
{
    if(ctrl == NULL) return -1;

    pthread_mutex_unlock(&(ctrl->mutex));
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTMutex_Trylock(TMutex *ctrl)
 *func: 尝试锁定互斥对象
        如果互斥对象当前处于解锁状态,将获得该锁并且函数将返回零。
        如果互斥对象已锁定,这个调用不会阻塞,会返回非零的 EBUSY 错误值。
 *args:
 *      # ctrl 互斥信号结构
*************************************************************************************]*/
int ZTMutex_Trylock(TMutex *ctrl)
{
    if(ctrl == NULL) return -2;

    if( pthread_mutex_trylock(&(ctrl->mutex)) != 0)
    {
        return -1;
    }

    return 0;
}