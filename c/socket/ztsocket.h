#ifndef __SOCKET_C_H__
#define __SOCKET_C_H__

#include "ztmutex.h"

/*�̰߳�ȫ��*/

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
    HSocket    iFd;                //socket�ļ�������
    int    iConnTimeout;           //�����뷢�͵ĳ�ʱʱ��
    int    iRecvTimeout;           //���յĳ�ʱʱ��
    int    iSrvPort;               //�������˿�
    char   caSrvIP[20];            //������IP
    TMutex * mutex;                //�߳���
}TSocket;


//�������
typedef enum
{
    SUCC                             = 0,      //�����ɹ�
    CANCEL                           = -101,   //����ȡ��
                                    
    ERR_SCK_IP_FMT                   = -121,   //socket server ip��ʽ����
    ERR_SCK_NOT_CONNECT              = -122,   //�޷����ӷ�����
    ERR_SCK_SOCKET_FD                = -123,   //socket����������
    ERR_SCK_SEND_FAILD               = -124,   //socket����ʧ��
    ERR_SCK_SEND_LEN                 = -125,   //�������ݳ��ȴ���
    ERR_SCK_RECV_LEN                 = -126,   //���յ����ݳ��ȴ���
    ERR_SCK_RECV_TIMEOUT             = -127,   //���ճ�ʱ
    ERR_SCK_CREATE                   = -128,   //����������ʧ��
    ERR_SCK_NONBLOCK                 = -129,   //���÷�����ʧ��
    ERR_SCK_BIND                     = -130,   //�󶨶˿�ʧ��
    ERR_SCK_LISTEN                   = -131,   //�����˿�ʧ��
                                                                 
    ERR_UNKNOWN                      = -999   //δ֪����
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
