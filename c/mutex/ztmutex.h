#ifndef __ZTMUTEX_H__
#define __ZTMUTEX_H__

#include <pthread.h>

/*
	通常使用 pthread_mutex_lock() 和 pthread_mutex_unlock() 来保护数据结构。
	通过线程的锁定和解锁，对于某一数据结构，确保某一时刻只能有一个线程能够访问它。
 */


struct TMutex_st
{
    pthread_mutex_t	mutex;       //互斥信号
};

typedef struct TMutex_st TMutex;

int ZTMutex_Init(TMutex **ctrl);
int ZTMutex_Destroy(TMutex *ctrl);
int ZTMutex_Lock(TMutex *ctrl);
int ZTMutex_Unlock(TMutex *ctrl);
int ZTMutex_Trylock(TMutex *ctrl);

#endif  //__ZTMUTEX_H__
