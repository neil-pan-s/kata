#ifndef __ZTPROCESS_H__
#define __ZTPROCESS_H__

typedef  void *(*VOID_FUNC)(void*);
typedef  void (*VOID_FUNC1)(void*);
typedef  void (*VOID_FUNC2)(void);

int ZTProcess_Fork(VOID_FUNC p_func,void *p_args);
int ZTProcess_AtExit(VOID_FUNC2 p_func);
int ZTProcess_Wait(int p_pid,int * p_status);
int ZTProcess_Execve(char *p_bin ,char* p_argv[],char **p_env);
void ZTProcess_PrintEnv(char **p_env);
int ZTProcess_SetEnv(char * p_caName,char *p_caValue);
char *ZTProcess_GetEnv(char * p_envName);
int ZTProcess_Kill(int p_pid);
int ZTProcess_Kill2(char * p_binName);
int ZTProcess_Start(char * p_shPath);
int ZTProcess_System(char *p_caCmd);

#endif  //__ZTPROCESS_H__
