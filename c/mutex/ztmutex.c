#include "ztmutex.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*[method*******************************************************************************
 *def:  int ZTMutex_Init(TMutex *ctrl)
 *func: ��������ʼ��һ���������
 *args: 
 *      # ctrl �����źŽṹ 
*************************************************************************************]*/
int ZTMutex_Init(TMutex **ctrl)
{
    *ctrl = NULL;    
    *ctrl = (void*)malloc(sizeof(TMutex));
    memset(*ctrl, 0, sizeof(TMutex));

    //��ʼ���������
    pthread_mutex_init(&((*ctrl)->mutex), NULL);
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTMutex_Destroy(TMutex *ctrl)
 *func: �ͷŻ������
 *args: 
 *      # ctrl �����źŽṹ
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
*func: �����������
*args:
*      # ctrl �����źŽṹ
*************************************************************************************]*/
int ZTMutex_Lock(TMutex *ctrl)
{
    if(ctrl == NULL) return -1;

    pthread_mutex_lock(&(ctrl->mutex));
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTMutex_Unlock(TMutex *ctrl)
 *func: �����������
 *args:
 *      # ctrl �����źŽṹ
*************************************************************************************]*/
int ZTMutex_Unlock(TMutex *ctrl)
{
    if(ctrl == NULL) return -1;

    pthread_mutex_unlock(&(ctrl->mutex));
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTMutex_Trylock(TMutex *ctrl)
 *func: ���������������
        ����������ǰ���ڽ���״̬,����ø������Һ����������㡣
        ����������������,������ò�������,�᷵�ط���� EBUSY ����ֵ��
 *args:
 *      # ctrl �����źŽṹ
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