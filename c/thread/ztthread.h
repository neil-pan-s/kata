#ifndef __ZTTHREAD_H__
#define __ZTTHREAD_H__

#include <pthread.h>
#include "ztmutex.h"

typedef  void *(*THREAD_FUNC)(void*);
typedef  void (*THREAD_FUNC1)(void*);

//�߳̿��ƽṹ
typedef struct
{
    pthread_t       handle;  //�߳̾��
    pthread_attr_t  pattr;   //�߳�����
    THREAD_FUNC     func;    //�̺߳���ָ��
    void            *args;   //�̺߳�������
}Tthread;

typedef struct
{
	TMutex *mutex;	//������
	pthread_cond_t cond;	//��������		
}TCond;

//cleanup �߳̿��ƽṹ
typedef struct
{ 
    TMutex        *mutex;  //������
    THREAD_FUNC   func;  //�߳�ִ�к���ָ��
    void          *args;   //�߳�ִ�к�������
    THREAD_FUNC1  cleanfunc;  //�߳�cancel��Ӧʱ������ָ��
    TCond  *tcond;	//�����������ƽṹ
}TCleanUp;

//���߳̽ӿ�
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


//���߳̽ӿ�
void ZTSubThread_SetCancelmode();
void ZTSubThread_TestCancel();
void ZTSubThread_Exit(void * p_args);
void *ZTSubThread_Cleanup_Run(void * p_args);


#endif  //__ZTTHREAD_H__
