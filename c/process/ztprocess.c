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
 *func: �ӽ��̴������� ���ƽ���ӳ��
 *args: p_func �ӽ���ִ�к���ָ��
        p_args �ӽ���ִ�к�������
 *ret:  �ӽ���ID
*************************************************************************************]*/
int ZTProcess_Fork(VOID_FUNC p_func,void *p_args)
{
    pid_t pid;

    pid = fork();

    // ���������fork��ʱ����һ����ȫ���Ƶ��ӳ��򱻴�����
    // ���ӽ��̶�����fork�����õĵط�����ִ����ȥ
    // ��������fork�����ķ���ֵ���ӽ��̵Ľ��̺�
    // �ӽ�����fork�����ķ���ֵ����

    //�ӽ���
    if( pid == 0)
    {    
        p_func(p_args);
        exit(0);        //��ֹ�ӽ��̼�������
    }

    return pid;
}

/*[method*******************************************************************************
 *def:  int ZTProcess_AtExit(VOID_FUNC2 p_func)
 *func: ע����ֹ����(��mainִ�н�������õĺ���)
        exit������Щע�ắ����˳�������� �Ǽ�ʱ���˳���෴ ͬһ�����������ǼǶ�Σ���Ҳ�ᱻ���ö�Ρ�
 *args: p_func ������ֹ����ָ��
*************************************************************************************]*/
int ZTProcess_AtExit(VOID_FUNC2 p_func)
{
    return atexit(p_func); 
}

/*[method*******************************************************************************
 *def:  int ZTProcess_Wait(int p_pid,int * p_status)
 *func: �ȴ��ӽ��̽������˺�������ʱֹͣĿǰ���̵�ִ�У�ֱ�����ź��������ӽ��̽���
 *args: p_pid �ӽ���ID
        p_status �ӽ��̵Ľ���״ֵ̬ ������λNULL
 *ret:  �ӽ��̵Ľ���ʶ����
*************************************************************************************]*/
int ZTProcess_Wait(int p_pid,int * p_status)
{
    printf(" -------------- waitpid : %d -------------- \n",p_pid);
    return waitpid(p_pid,p_status,0);    
}

/*[method*******************************************************************************
 *def:  int ZTProcess_Execve(char *p_bin ,char* p_argv[],char **p_env)
 *func: ִ��һ����ִ���ļ������浱ǰ���̵�ִ��ӳ�� �滻����ӳ��
        �õ��ò�û�������µĽ��̣�������ԭ�н��̵Ļ����ϣ��滻ԭ�н��̵����ģ�����ǰ����ͬһ������
        ���̺�PID ����
 *args: p_bin ���̿�ִ�г���·��
        p_argv ����ִ�в���
        p_env  ����ִ�л�������  ����ֱ�Ӵ��� environ
*************************************************************************************]*/
int ZTProcess_Execve(char *p_bin ,char* p_argv[],char **p_env)
{
    return execve(p_bin,p_argv,p_env);
}

/*[method*******************************************************************************
 *def:  void ZTProcess_PrintEnv(char **p_env)
 *func: ��ӡ���̻�������ֵ
 *args: p_env  ����ִ�л������� 
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
 *func: ���ý��̻�������ֵ
 *args: p_caName  ���̻��������� eg. PATH
        p_caValue ���̻�������ֵ
*************************************************************************************]*/
int ZTProcess_SetEnv(char *p_caName,char *p_caValue)
{
    //ɾ���Ѵ��ڵ����ж���
    return setenv((const char *)p_caName, (const char *)p_caValue,0);
}

/*[method*******************************************************************************
 *def:  char *ZTProcess_GetEnv(char * p_envName)
 *func: ȡ�ý��̻�������ֵ
 *args: p_envName  ����ִ�л��������� 
 *ret: ָ����name������value��ָ��,��Ϊ�ҵ��򷵻�NULL
*************************************************************************************]*/
char *ZTProcess_GetEnv(char * p_envName)
{
    return getenv((const char *)p_envName);
}

/*[method*******************************************************************************
 *def:  int ZTProcess_Kill(int p_pid)
 *func: ͨ������ID kill ĳ������
 *args: p_pid  ����ID
*************************************************************************************]*/
int ZTProcess_Kill(int p_pid)
{
    char caCmd[512] = {0};
    
    sprintf(caCmd,"kill %d",p_pid);
    return system(caCmd);
}

/*[method*******************************************************************************
 *def:  int ZTProcess_Kill2(char * p_binName)
 *func: ͨ������ִ���ļ��� kill ĳ������
 *args: p_binName  ����ִ���ļ���
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
 *func: ͨ����������sh�ű� ����һ������  ���ַ�ʽ���� ��sh�ű��� ���û��������� 
 *args: p_shPath  ��������sh�ű�
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
 *func: ִ��system�����
 *args: p_caCmd��������
*************************************************************************************]*/
int ZTProcess_System(char *p_caCmd)
{
    return system(p_caCmd);
}

