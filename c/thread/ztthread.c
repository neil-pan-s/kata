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
 *func: �̹߳��캯��,��ʼ���̺߳���ָ��ͻ������
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
 *func: �߳���������,�ͷŻ������
*************************************************************************************]*/
int ZTThread_Destroy(Tthread *p_thread)
{
    Tthread* ctrl=(Tthread*)p_thread;
    void ** p = NULL;
    if(p_thread == NULL) return -1;

    //ɾ���߳����Խṹ
    pthread_attr_destroy(&(ctrl->pattr));

    //�������̵߳�״̬����Ϊdetached,����߳����н�������Զ��ͷ�������Դ
    //���̵߳��÷�ʽ pthread_detach(thread_id)�������������������أ�
    //pthread_detach(pthread_self());
    //pthread_detach(ctrl->handle);  //��Ӱ����������̵߳�cleanup����
    ZTThread_Join(ctrl,p);
    
    free(p_thread);
    return 0;
}


/*[method*******************************************************************************
 *def:  int ZTThread_Start(Tthread *p_thread)
 *func: �����߳�
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
 *func: ���̵߳ȴ�ĳ���߳�ִ�н��� �ϲ����߳� 
        �������ķ�ʽ�ȴ�threadָ�����߳̽���������������ʱ�����ȴ��̵߳���Դ���ջء�
        ����߳��Ѿ���������ô�ú�������������
 *args: p_thread �߳̿��ƽṹָ��
        p_args   ���̵߳��� phread_exit()�Ǵ����Ķ���ָ��       
*************************************************************************************]*/
int ZTThread_Join(Tthread *p_thread,void **p_args)
{
    Tthread* ctrl=(Tthread*)p_thread;
    if(p_thread == NULL) return -1;

    return pthread_join(ctrl->handle, p_args);
}


/*[method*******************************************************************************
 *def:  int ZTThread_Cancel(Tthread *p_thread)
 *func: ���̷߳���ȡ�����߳�����
        pthread_cancel���ò����ȴ��߳���ֹ����ֻ����������߳���ȡ������(pthread_cancel)�������������У�
        ֱ������ĳ��ȡ����(CancellationPoint)��ȡ�������̼߳���Ƿ�ȡ��������������ж�����һ��λ��

        Pthread��׼ָ�������¼���ȡ���㣺
             pthread_testcancel
             ���е��ȵ㣬��pthread_cond_wait��sigwait��select��sleep��
             ������� printfҲ��һ��ȡ����        
*************************************************************************************]*/
int ZTThread_Cancel(Tthread *p_thread)
{
    Tthread* ctrl=(Tthread*)p_thread;
    if(p_thread == NULL) return -1;

    return pthread_cancel(ctrl->handle);
}

/*[method*******************************************************************************
 *def:  int ZTThread_Cond_Init(TCond ** p_cond)
 *func: ��������ʼ��һ�����������ṹ
 *args: 
 *      p_cond ���������ṹ 
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
 *func: �ͷ����������ṹ
 *args: 
 *      p_cond ���������ṹ
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
 *func: ����һ���ȴ����������߳�
*************************************************************************************]*/
int ZTThread_Cond_Signal(TCond * p_cond)
{
   return pthread_cond_signal(&(p_cond->cond));
}

/*[method*******************************************************************************
 *def:  int ZTThread_Cond_BroadCast(TCond * p_cond)
 *func: �������еȴ��߳�
*************************************************************************************]*/
int ZTThread_Cond_BroadCast(TCond * p_cond)
{
   return pthread_cond_broadcast(&(p_cond->cond));
}


/*[method*******************************************************************************
 *def:  int ZTThread_Cond_TimeWait(TCond * p_cond,int p_tMs)
 *func: �̵߳ȴ��������ȴ���������
        ���ô˺����� ��Ҫ�� cleanup�����н��� mutex ����muext ��һֱ���� 
 *args: p_tMs �̼߳�ʱ�ȴ���ʽ����ڸ���ʱ��ǰ����û�����㣬�򷵻�ETIMEOUT�������ȴ�
*************************************************************************************]*/
int ZTThread_Cond_TimeWait(TCond * p_cond,int p_tMs)
{
    int iRet = 0;
    struct timespec reltime;

    //�߳��˳���ʱ���
    reltime.tv_sec = time(NULL) + p_tMs/1000;      
    reltime.tv_nsec = 0;

    ZTMutex_Lock(p_cond->mutex);
    //pthread_cond_timedwait Ҳ��ȡ����֮һ
    //pthread_cond_timedwait()��ȡ����mutex�Ǳ�������״̬��
    
    //����ԭ��
    //  int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime)
    //  abstime����time()ϵͳ������ͬ����ľ���ʱ����ʽ���֣�0��ʾ��������ʱ��1970��1��1��0ʱ0��0�롣
    
    iRet = pthread_cond_timedwait(&(p_cond->cond),&(p_cond->mutex->mutex),&reltime);
    ZTMutex_Unlock(p_cond->mutex);

    return iRet;
}



/*[method*******************************************************************************
 *def:  int ZTThread_Cond_Wait(TCond * p_cond)
 *func: �̵߳ȴ��������ȴ���������
        ���ô˺����� ��Ҫ�� cleanup�����н��� mutex ����muext ��һֱ���� 
*************************************************************************************]*/
int ZTThread_Cond_Wait(TCond * p_cond)
{
    int iRet = 0;
    ZTMutex_Lock(p_cond->mutex);
    //pthread_cond_wait Ҳ��ȡ����֮һ
    //���pthread_cond_wait()��ȡ����mutex�Ǳ�������״̬��
    iRet = pthread_cond_wait(&(p_cond->cond),&(p_cond->mutex->mutex));
    ZTMutex_Unlock(p_cond->mutex);

    return iRet;
}


/*[method*******************************************************************************
 *def:  int ZTThread_CheckCancel()
 *func: ���߳��У������߳�ȡ���ź���Ӧ��ʽ
*************************************************************************************]*/
void ZTSubThread_SetCancelmode()
{

    //�����յ��źź���ΪCANCLED״̬
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    //����Ϊ�յ��źź����CANCEL�źż�������
    //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

    //�ӳ�ȡ��-�����յ�ȡ���źź������������һ��ȡ�������˳�
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    //�첽ȡ��-�����յ�ȡ���źź�����ִ��ȡ������
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
}

/*[method*******************************************************************************
 *def:  int ZTThread_CheckCancel()
 *func: ���߳��У��ڲ�����ȡ���㣬��������Ҫȡ����ĵط�����һ��ȡ���㣬�Ա���һ��û�а���ȡ�����ִ�д����߳�����Ӧȡ������
        �߳�ȡ�����ܴ�������״̬��ȡ��״̬����Ϊ�ӳ�״̬ʱ��pthread_testcancel()������Ч
        ��ؽ����߳�ȡ���̲߳�����ȫ�������в���pthread_testcancel()
*************************************************************************************]*/
void ZTSubThread_TestCancel()
{
    pthread_testcancel();
}


/*[method*******************************************************************************
 *def:  int ZTThread_Exit()
 *func: ���̵߳��ã�����������ǰ���߳�
        �߳�ͨ������pthread_exit������ִֹ�У�����ͬ�����ڽ���ʱ����exit����һ����
        ��������������ǣ���ֹ���������̲߳�����һ��ָ��ĳ�������ָ��,��ָ���ͨ��phthread_join()��á�
*************************************************************************************]*/
void ZTSubThread_Exit(void * p_args)
{
    pthread_exit(p_args);
}


/*[method*******************************************************************************
 *def:  void ZTSubThread_Cleanup_Run(void * p_args)
 *func: Cleanupģʽ�߳�ִ����,������ʵ��ʹ��cancel������֤��ȷ�ͷŻ�����
 *args: p_args  TCleanUp�ṹָ�� 
 
        TCleanUp �ṹ��������ݺͺ��� ����ʵ�� 
        TMutex       * mutex;  //������
        THREAD_FUNC  func;  //�߳�ִ�к���ָ��
        void         *args; //�߳�ִ�к�������
        THREAD_FUNC1  cleanfunc;  //�߳�cancel��Ӧʱ������ָ��
*************************************************************************************]*/
void *ZTSubThread_Cleanup_Run(void * p_args)
{
    TCleanUp * ctrl = (TCleanUp *)p_args;

    ZTSubThread_SetCancelmode();  //1:����cancel����Ӧ��ʽ

    /*
        ���߳�cancel������ֹʱ,ִ�е�������,���ڱ�֤��ȷ�ͷŻ�������
           
        ����ԭ�� 
           void pthread_cleanup_push(void (*routine) (void  *),  void *arg)        
           #routine Ϊcancel������ֹ�̺߳� ִ�е�������
           #arg Ϊ������������

        pthread_cleanup_push() ������������ջ�ṹ����
        void routine(void *arg)�����ڵ���pthread_cleanup_push()ʱѹ��������ջ
        ��ζ�pthread_cleanup_push()�ĵ��ý���������ջ���γ�һ��������
        ��ִ�иú�����ʱ����ѹջ���෴˳�򵯳�

        PS: 
            pthread_cleanup_push()/pthread_cleanup_pop()���Ժ귽ʽʵ�ֵ�
            pthread_cleanup_push()����һ��"{"����pthread_cleanup_pop()����һ��"}"
            �����������������ɶԳ��֣��ұ���λ�ڳ����ͬһ����Ĵ�����в���ͨ������
    */
    pthread_cleanup_push(ctrl->cleanfunc, ctrl);  //2:�����̱߳�cancelʱִ�е��¼�
    ZTMutex_Lock(ctrl->mutex);        //����


    /*
        Pthread��׼ָ�������¼���ȡ���㣺
             pthread_testcancel
             ���е��ȵ㣬��pthread_cond_wait��sigwait��select��sleep��
             ������� printfҲ��һ��ȡ����  
        ���� �߳�ʵ�����庯�� ������� ����һ������ȡ����
     */
    
    printf("---------------- %s -- %d ----------------\n",__func__,__LINE__);    
    (ctrl->func)(ctrl->args);
    printf("---------------- %s -- %d ----------------\n",__func__,__LINE__);

    ZTMutex_Unlock(ctrl->mutex);      //����
    /*
        ��pthread_cleanup_push()�󶨵�������������ѹջ���෴˳�򵯳�,�����ڽ��������

        ����ԭ��
            void pthread_cleanup_pop(int execute)
            #execute������ʾִ�е�pthread_cleanup_pop()ʱ�Ƿ��ڵ�����������ͬʱִ�иú���
            Ϊ0��ʾ��ִ�� ��0Ϊִ��
     */
    pthread_cleanup_pop(0);         //ȡ��cancelʱִ�е��¼�

    return NULL;
}
