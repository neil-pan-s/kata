#include "ztprocess.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/*[method*******************************************************************************
 *def:  int ZTProcess_Fork(VOID_FUNC p_func)
 *func: 子进程创建函数 复制进程映像
 *args: p_func 子进程执行函数指针
        p_args 子进程执行函数参数
 *ret:  子进程ID
*************************************************************************************]*/
int ZTProcess_Fork(VOID_FUNC p_func,void *p_args)
{
    pid_t pid;

    pid = fork();

    // 当程序调用fork的时候，则一个完全复制的子程序被创建。
    // 父子进程都将从fork被调用的地方继续执行下去
    // 父进程中fork函数的返回值是子进程的进程号
    // 子进程中fork函数的返回值是零

    //子进程
    if( pid == 0)
    {    
        p_func(p_args);
        exit(0);        //终止子进程继续运行
    }

    return pid;
}

/*[method*******************************************************************************
 *def:  int ZTProcess_AtExit(VOID_FUNC2 p_func)
 *func: 注册终止函数(即main执行结束后调用的函数)
        exit调用这些注册函数的顺序与它们 登记时候的顺序相反 同一个函数如若登记多次，则也会被调用多次。
 *args: p_func 进程终止函数指针
*************************************************************************************]*/
int ZTProcess_AtExit(VOID_FUNC2 p_func)
{
    return atexit(p_func); 
}

/*[method*******************************************************************************
 *def:  int ZTProcess_Wait(int p_pid,int * p_status)
 *func: 等待子进程结束，此函数将暂时停止目前进程的执行，直到有信号来到或子进程结束
 *args: p_pid 子进程ID
        p_status 子进程的结束状态值 可以置位NULL
 *ret:  子进程的进程识别码
*************************************************************************************]*/
int ZTProcess_Wait(int p_pid,int * p_status)
{
    printf(" -------------- waitpid : %d -------------- \n",p_pid);
    return waitpid(p_pid,p_status,0);    
}

/*[method*******************************************************************************
 *def:  int ZTProcess_Execve(char *p_bin ,char* p_argv[],char **p_env)
 *func: 执行一个可执行文件来代替当前进程的执行映像 替换进程映像
        该调用并没有生成新的进程，而是在原有进程的基础上，替换原有进程的正文，调用前后是同一个进程
        进程号PID 不变
 *args: p_bin 进程可执行程序路径
        p_argv 进程执行参数
        p_env  进程执行环境变量  可以直接传入 environ
*************************************************************************************]*/
int ZTProcess_Execve(char *p_bin ,char* p_argv[],char **p_env)
{
    return execve(p_bin,p_argv,p_env);
}

/*[method*******************************************************************************
 *def:  void ZTProcess_PrintEnv(char **p_env)
 *func: 打印进程环境变量值
 *args: p_env  进程执行环境变量 
*************************************************************************************]*/
void ZTProcess_PrintEnv(char **p_env)
{
    int i = 0;

    printf("-------------- Shell Environment --------------\n");
    for (i=0;p_env[i]!=NULL;i++)
    {
        printf("%s\n",p_env[i]);
    }
    printf("------------------------------------------------\n");    
}

/*[method*******************************************************************************
 *def:  void ZTProcess_PrintEnv(char **p_env)
 *func: 设置进程环境变量值
 *args: p_caName  进程环境变量名 eg. PATH
        p_caValue 进程环境变量值
*************************************************************************************]*/
int ZTProcess_SetEnv(char *p_caName,char *p_caValue)
{
    //删除已存在的现有定义
    return setenv((const char *)p_caName, (const char *)p_caValue,0);
}

/*[method*******************************************************************************
 *def:  char *ZTProcess_GetEnv(char * p_envName)
 *func: 取得进程环境变量值
 *args: p_envName  进程执行环境变量名 
 *ret: 指向与name关联的value的指针,若为找到则返回NULL
*************************************************************************************]*/
char *ZTProcess_GetEnv(char * p_envName)
{
    return getenv((const char *)p_envName);
}

/*[method*******************************************************************************
 *def:  int ZTProcess_Kill(int p_pid)
 *func: 通过进程ID kill 某个进程
 *args: p_pid  进程ID
*************************************************************************************]*/
int ZTProcess_Kill(int p_pid)
{
    char caCmd[512] = {0};
    
    sprintf(caCmd,"kill %d",p_pid);
    return system(caCmd);
}

/*[method*******************************************************************************
 *def:  int ZTProcess_Kill2(char * p_binName)
 *func: 通过进程执行文件名 kill 某个进程
 *args: p_binName  进程执行文件名
*************************************************************************************]*/
int ZTProcess_Kill2(char * p_binName)
{
    char caCmd[512] = {0};
    
    //sprintf(caCmd,"ps -A | grep %s |grep -v grep | xargs kill",p_binName);
    //sprintf(caCmd,"ps | grep %s |grep -v grep | xargs kill",p_binName);
    sprintf(caCmd,"killall %s",p_binName);
	printf(" -------------- ZTProcess_Kill2 : %s -------------- \n",caCmd);    
    return system(caCmd);
}

/*[method*******************************************************************************
 *def:  int ZTProcess_Start(char * p_shPath)
 *func: 通过进程启动sh脚本 启动一个进程  此种方式可以 在sh脚本中 设置环境变量等 
 *args: p_shPath  进程启动sh脚本
        eg. p_shPath = ./ztpos.sh

        #! /bin/sh

        LANG=zh_CN.UTF-8
        LC_CTYPE=zh_CN.utf8
        export USER LOGNAME PS1 PATH LANG LC_CTYPE

        cd /yaffs/pos/
        export LD_LIBRARY_PATH=/yaffs/pos/lib:$LD_LIBRARY_PATH 
        /yaffs/pos/ztpos -qws&

*************************************************************************************]*/
int ZTProcess_Start(char * p_shPath)
{
    char caCmd[512] = {0};

    sprintf(caCmd,"%s",p_shPath);
    return system(caCmd);    
}

/*[method*******************************************************************************
 *def:  int ZTProcess_System(char *p_caCmd)
 *func: 执行system　命令　
 *args: p_caCmd　　命令
*************************************************************************************]*/
int ZTProcess_System(char *p_caCmd)
{
    return system(p_caCmd);
}

