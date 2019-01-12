#ifndef __SOCKET_C_H__
#define __SOCKET_C_H__

#include "ztmutex.h"

/*线程安全的*/

#define __USE_BY_LINUX__ 

#if defined(__USE_BY_LINUX__)
typedef int HSocket;
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#elif defined(__USE_BY_WIN32__)
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
typedef SOCKET HSocket;
#endif

typedef struct
{
    HSocket    iFd;                //socket文件描述符
    int    iConnTimeout;           //连接与发送的超时时间
    int    iRecvTimeout;           //接收的超时时间
    int    iSrvPort;               //服务器端口
    char   caSrvIP[20];            //服务器IP
    TMutex * mutex;                //线程锁
}TSocket;


//错误代码
typedef enum
{
    SUCC                             = 0,      //操作成功
    CANCEL                           = -101,   //操作取消
                                    
    ERR_SCK_IP_FMT                   = -121,   //socket server ip格式错误
    ERR_SCK_NOT_CONNECT              = -122,   //无法链接服务器
    ERR_SCK_SOCKET_FD                = -123,   //socket描述符错误
    ERR_SCK_SEND_FAILD               = -124,   //socket发送失败
    ERR_SCK_SEND_LEN                 = -125,   //发送数据长度错误
    ERR_SCK_RECV_LEN                 = -126,   //接收的数据长度错误
    ERR_SCK_RECV_TIMEOUT             = -127,   //接收超时
    ERR_SCK_CREATE                   = -128,   //创建描述符失败
    ERR_SCK_NONBLOCK                 = -129,   //设置非阻塞失败
    ERR_SCK_BIND                     = -130,   //绑定端口失败
    ERR_SCK_LISTEN                   = -131,   //监听端口失败
                                                                 
    ERR_UNKNOWN                      = -999   //未知错误
}TSocketErr;

int ZTSocket_Init(TSocket ** p_socketCtrl,const char *p_caSrv, int p_iPort, int p_iRecvTimeout, int p_iConnTimeout);
int ZTSocket_Close(TSocket * p_socketCtrl);
int ZTSocket_Connect(TSocket * p_socketCtrl);
int ZTSocket_Disconnect(TSocket * p_socketCtrl);
int ZTSocket_Send(TSocket * p_socketCtrl,char *p_caData, int p_iLn);
int ZTSocket_Recv(TSocket * p_socketCtrl,char *p_caBuff, int p_iLn);
int ZTSocket_Listen(TSocket * p_socketCtrl);
int ZTSocket_Accept(TSocket * p_socketCtrl,char *p_caClientIP);

#endif  //__SOCKET_C_H__
