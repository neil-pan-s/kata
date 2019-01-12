/* 
* @Author: ChangingP
* @Date:   2015-03-26 22:41:39
* @Last Modified by:   ChangingP
* @Last Modified time: 2015-04-06 06:25:04
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <memory.h>
#include <ztstring.h>
#include "ztthread.h"

void ZTSubThread_Cleanup(void * arg)
{
    TCleanUp * ctrl = (TCleanUp *) arg;

    if(ctrl->tcond != NULL)
    {
    	printf("---------------- %s -- %d ----------------\n",__func__,__LINE__);
    	ZTThread_Cond_Destroy(ctrl->tcond);
    	printf("---------------- %s -- %d ----------------\n",__func__,__LINE__);
    }

    printf("---------------- %s -- %d ----------------\n",__func__,__LINE__);
    ZTMutex_Unlock(ctrl->mutex);
    printf("---------------- %s -- %d ----------------\n",__func__,__LINE__);   
}

void *ZTSubThread_Cond_Demo(void * arg)
{
	TCleanUp * cleanup = (TCleanUp *)arg;
	TCond *cond = cleanup->tcond;

	while(1)
	{
		sleep(1);
		printf("-------------- ZTSubThread_Cond_Demo wait start-------------\n");
		ZTThread_Cond_Wait(cond);
		printf("-------------- ZTSubThread_Cond_Demo wait end -------------\n");
	}	
}

void *ZTSubThread_Cleanup_Demo(void * arg)
{
	while(1)
	{
		printf("-------------- ZTSubThread_Cleanup_Demo -------------\n");
		sleep(1);
	}	
}

void * ZTSubThread_Demo(void * arg)
{
	while(1)
	{
		printf("-------------- ZTSubThread_RunDemo -------------\n");
		sleep(1);
	}	
}

int main(int argc, char const *argv[])
{
	int iRet = 0,a = 0;
	Tthread * thread = NULL;
	TCleanUp tcleanup;
	TMutex * mutex = NULL;

	memset(&tcleanup,0,sizeof(TCleanUp));

	/********************* 使用方法1 启动线程 并使用 cancel 停止 ***************************/
	ZTThread_Init(&thread,ZTSubThread_Demo,NULL);

	ZTThread_Start(thread);

    printf("---------------- %s -- %d ---------------- thread = %d\n",__func__,__LINE__,(int)thread->handle);

	//用于控制发送取消请求时间 输入数字后 线程即会停止
	scanf("%d",&a);

	//发送取消请求
	ZTThread_Cancel(thread);

	ZTThread_Destroy(thread);

	/********************* 使用方法2 启动 cleanup 线程 并使用 cancel 停止 ***************************/
	ZTMutex_Init(&mutex);

	tcleanup.mutex = mutex;
	tcleanup.func = ZTSubThread_Cleanup_Demo;
	tcleanup.cleanfunc = ZTSubThread_Cleanup;
	tcleanup.args = NULL;
	tcleanup.tcond = NULL;

	thread = NULL;
	ZTThread_Init(&thread,ZTSubThread_Cleanup_Run,(void*)&tcleanup);
	ZTThread_Start(thread);

    printf("---------------- %s -- %d ---------------- thread = %d\n",__func__,__LINE__,(int)thread->handle);

	//用于控制发送取消请求时间 输入数字后 线程即会停止
	scanf("%d",&a);

	//发送取消请求
	ZTThread_Cancel(thread);

	ZTThread_Destroy(thread);

	ZTMutex_Destroy(mutex);

	/********************* 使用方法3 启动 cleanup + cond 线程 ***************************/
	ZTMutex_Init(&mutex);

	tcleanup.mutex = mutex;
	tcleanup.func = ZTSubThread_Cond_Demo;
	tcleanup.cleanfunc = ZTSubThread_Cleanup;
	tcleanup.args = (void*)&tcleanup;

	ZTThread_Cond_Init(&(tcleanup.tcond));

	thread = NULL;
	ZTThread_Init(&thread,ZTSubThread_Cleanup_Run,(void*)&tcleanup);
	ZTThread_Start(thread);

    printf("---------------- %s -- %d ---------------- thread = %d\n",__func__,__LINE__,(int)thread->handle);

	//用于控制发送取消请求时间 输入数字后 线程即会停止
	scanf("%d",&a);
	ZTThread_Cond_Signal(tcleanup.tcond);

	ZTThread_Destroy(thread);

	ZTMutex_Destroy(mutex);


	return 0;
}
