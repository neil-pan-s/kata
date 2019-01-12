#include "ztsocket.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef NULL
    #define NULL 0
#endif

/*[method*******************************************************************************
 *def:  int ZTSocket_Init(TSocket ** p_socketCtrl,const char *p_caSrv, int p_iPort, int p_iRecvTimeout, int p_iConnTimeout)
 *func: ����һ��socket����
 *args: p_caSrv         ������IP
        p_iPort         �������˿�
        p_iRecvTimeout  �������ݳ�ʱʱ��
        p_iConnTimeout  �������ݳ�ʱʱ��
*************************************************************************************]*/
int ZTSocket_Init(TSocket ** p_socketCtrl,const char *p_caSrv, int p_iPort, int p_iRecvTimeout, int p_iConnTimeout)
{
    TSocket *ctrl=NULL;

    if(p_socketCtrl == NULL) return -1;

    ctrl = (TSocket*)malloc(sizeof(TSocket));
    memset(ctrl, 0, sizeof(TSocket));

    ctrl->iConnTimeout = p_iConnTimeout;
    ctrl->iRecvTimeout = p_iRecvTimeout;
    ctrl->iSrvPort     = p_iPort;
    sprintf(ctrl->caSrvIP, "%s", p_caSrv);

    ZTMutex_Init(&(ctrl->mutex));

    *p_socketCtrl = ctrl;
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTSocket_Close(TSocket * p_socketCtrl)
 *func: ����һ��socket����
*************************************************************************************]*/
int ZTSocket_Close(TSocket * p_socketCtrl)
{
    if(p_socketCtrl == NULL) return -1;

    ZTMutex_Destroy(p_socketCtrl->mutex);
    free(p_socketCtrl);
    return 0;
}

/*[method*******************************************************************************
 *def:  public int ZTSocket::connect()
 *func: ����TCP����.
 *ret:  =SUCC    ��ʾ���ӳɹ�
        <0       ��ʾ����TCP����ʧ��
*************************************************************************************]*/
int ZTSocket_Connect(TSocket * p_socketCtrl)
{
    int iRet=0;
    struct sockaddr_in servaddr;
#if defined(__USE_BY_LINUX__)
    struct timeval send_time_val;
#endif
    TSocket *ctrl=(TSocket*)p_socketCtrl;
#if defined(__USE_BY_WIN32__)
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(1,1),&wsaData)) //����Windows Sockets DLL
    { 
        WSACleanup();
        return -199;
    }
#endif
    if(p_socketCtrl == NULL) return -1;

    ZTMutex_Lock(p_socketCtrl->mutex);

    //��ʱ����
#if defined(__USE_BY_LINUX__)
    send_time_val.tv_sec  = ctrl->iConnTimeout;  //���������ӵĳ�ʱʱ��,��Ϊ�̶���10��
    send_time_val.tv_usec = 0;
    //recv_time_val.tv_sec  = sck->timeout;   //���ճ�ʱ,���ճ�ʱ����ϵͳ����,���û�������Ƹ��ɿ�
    //recv_time_val.tv_usec = 0;        //sck->timeout�볬ʱ
#endif

    //SOCK_STREAM:IPPROTO_TCP; 
    //SOCK_DGRAM:IPPROTO_UDP
    //PF_INET����ʾ������Э����(TCP/IPЭ����)
    //SOCK_STREAM ��ʾ��ʽ����(TCP)�� SOCK_DGRAM��ʾ������(UDP)
    ctrl->iFd = socket(PF_INET, SOCK_STREAM, 0);			//��ʽsocket��TCP
    //setsockopt(p_socket->iFd, SOL_SOCKET, SO_RCVTIMEO, &recv_time_val, sizeof(struct timeval));
#if defined(__USE_BY_LINUX__)
    setsockopt(ctrl->iFd, SOL_SOCKET, SO_SNDTIMEO, &send_time_val, sizeof(struct timeval));
#elif defined(__USE_BY_WIN32__)
    setsockopt(ctrl->iFd, SOL_SOCKET, SO_SNDTIMEO, (char*)&(ctrl->iConnTimeout), sizeof(int));
#endif
    bzero(&servaddr, sizeof(struct sockaddr_in));     //��ʼ��servaddr
    servaddr.sin_family = PF_INET;
    servaddr.sin_port   = htons(ctrl->iSrvPort);

    if((servaddr.sin_addr.s_addr = inet_addr(ctrl->caSrvIP)) == INADDR_NONE)
    {
    #if defined(__USE_BY_LINUX__)
        close(ctrl->iFd);
    #elif defined(__USE_BY_WIN32__)
        closesocket(ctrl->iFd);
        WSACleanup();
    #endif
        ctrl->iFd = 0;
        iRet = ERR_SCK_IP_FMT;	//The IP is not correct!
        goto LAB_EXIT;
    }

    if(connect(ctrl->iFd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr))==0)	//��������
    {
        /* ���� socket ����Ϊ��������ʽ */
        #if defined(__USE_BY_LINUX__)
        if(fcntl(ctrl->iFd, F_SETFL, O_NONBLOCK) == -1)
        #elif defined(__USE_BY_WIN32__)
        unsigned long mode = 1;
        if(ioctlsocket(ctrl->iFd, FIONBIO, &mode) != 0)
        #endif
        {
            iRet = ERR_SCK_NONBLOCK;
            goto LAB_EXIT;
        }
        else
        {
            iRet = SUCC;   //�������ӳɹ�
            goto LAB_EXIT;
        }
    }
    else
    {
    #if defined(__USE_BY_LINUX__)
        close(ctrl->iFd);
    #elif defined(__USE_BY_WIN32__)
        closesocket(ctrl->iFd);
        WSACleanup();
    #endif
        ctrl->iFd = 0;
        iRet = ERR_SCK_NOT_CONNECT;
        goto LAB_EXIT;
    }

LAB_EXIT:
    ZTMutex_Unlock(p_socketCtrl->mutex);
    return iRet;
}

/*[method*******************************************************************************
 *def:  int ZTSocket_Disconnect(TSocket * p_socketCtrl)
 *func: �ر�socket����
*************************************************************************************]*/
int ZTSocket_Disconnect(TSocket * p_socketCtrl)
{
    TSocket *ctrl=(TSocket*)p_socketCtrl;

    if(p_socketCtrl == NULL) return -1;

    ZTMutex_Lock(p_socketCtrl->mutex);

    if(ctrl->iFd>0)
    {
    #if defined(__USE_BY_LINUX__)
        close(ctrl->iFd);
    #elif defined(__USE_BY_WIN32__)
        shutdown(ctrl->iFd, SD_BOTH);
        closesocket(ctrl->iFd);
        WSACleanup();
    #endif
    }
    ctrl->iFd = 0;

    ZTMutex_Unlock(p_socketCtrl->mutex);
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTSocket_Send(TSocket * p_socketCtrl,char *p_caData, int p_iLn)
 *func: ͨ��socket�������ݵ�Զ�˷�����.
 *args: p_caData   Ҫ���͵�����
        p_iLn      Ҫ���͵����ݳ���
 *ret:  =SUCC ��ʾ���ͳɹ�
        ���� ��ʾ����ʧ��
*************************************************************************************]*/
int ZTSocket_Send(TSocket * p_socketCtrl,char *p_caData, int p_iLn)
{
    int result=0;
    TSocket *ctrl=(TSocket*)p_socketCtrl;

    if(p_socketCtrl == NULL) return -1;

    if(ctrl->iFd == 0)	return ERR_SCK_SOCKET_FD;    //ָ����������������
    result = send(ctrl->iFd, p_caData, p_iLn, 0);    //����ɹ������ط����ֽ���

    if(result < 0) return ERR_SCK_SEND_FAILD;            //�������ݴ���
    if(result != p_iLn)   return ERR_SCK_SEND_LEN;      //�������ݳ��ȴ���

    return SUCC;
}

/*[method*******************************************************************************
 *def:  int ZTSocket_Recv(TSocket * p_socketCtrl,char *p_caBuff, int p_iLn)
 *func: �������ݰ���
 *args: #p_iLn        ��Ҫ���յ����ݳ���
 *output: #p_caBuff   ���յ�����
 *ret:    =SUCC   ��ʾ�ɹ�
          <0      ��ʾʧ��
*************************************************************************************]*/
int ZTSocket_Recv(TSocket * p_socketCtrl,char *p_caBuff, int p_iLn)
{
    int ready_recv_ln, cur_recv_ln;
    int timeout=10;
    time_t begin;
    TSocket *ctrl=(TSocket*)p_socketCtrl;

    if(p_socketCtrl == NULL) return -1;

    if(ctrl->iFd == 0)    	return ERR_SCK_SOCKET_FD;     //��ʼ��ʧ��.ָ��������������

    timeout       = ctrl->iRecvTimeout;
    begin         = time(NULL);
    ready_recv_ln = 0;
    cur_recv_ln   = 0;
    while( 1==1 )
    {
        cur_recv_ln = recv(ctrl->iFd, p_caBuff+ready_recv_ln, p_iLn - ready_recv_ln, 0);
        if( 0 <= cur_recv_ln ) ready_recv_ln = ready_recv_ln + cur_recv_ln;
        if( p_iLn <= ready_recv_ln) return SUCC;
        if( 0 < cur_recv_ln) continue;
        
        usleep(10000);

        if( (time(NULL)-begin) > timeout ) return ERR_SCK_RECV_TIMEOUT;
    }

    return ERR_UNKNOWN;
}

/*[method*******************************************************************************
 *def:  int ZTSocket_Listen(TSocket * p_socketCtrl)
 *func: �󶨲�����ָ���˿�
 *ret:    =SUCC   ��ʾ�ɹ�
          <0      ��ʾʧ��
*************************************************************************************]*/
int ZTSocket_Listen(TSocket * p_socketCtrl)
{
    int iRet=0;
    struct sockaddr_in my_addr;
    TSocket *ctrl=(TSocket*)p_socketCtrl;
#if defined(__USE_BY_WIN32__)
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(1,1),&wsaData)) //����Windows Sockets DLL
    { 
        WSACleanup();
        return -199;
    }
#endif 
    if(p_socketCtrl == NULL) return -1;

    //����socket
    ctrl->iFd = socket(AF_INET, SOCK_STREAM, 0);

    //����socket����
    my_addr.sin_family      = AF_INET;
    my_addr.sin_port        = htons(ctrl->iSrvPort);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(my_addr.sin_zero),8);

    //�󶨶˿�
    iRet = bind(ctrl->iFd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));
    if( iRet == -1 ) return ERR_SCK_BIND;

    //����socketΪ������ģʽ
#if defined(__USE_BY_LINUX__)
    fcntl(ctrl->iFd, F_SETFL, O_NONBLOCK);
#elif defined(__USE_BY_WIN32__)
    unsigned long mode = 1;
    ioctlsocket(ctrl->iFd, FIONBIO, &mode);
#endif


    //�����˿�
    iRet = listen(ctrl->iFd, 1);
    if( iRet ==-1 ) return ERR_SCK_LISTEN;
    return SUCC;
}

/*[method*******************************************************************************
 *def:  int ZTSocket_Accept(TSocket * p_socketCtrl,char *p_caClientIP)
 *func: �������˿��Ƿ�����������
 *ret:  ���������Ӧ���ļ����
*************************************************************************************]*/
int ZTSocket_Accept(TSocket * p_socketCtrl,char *p_caClientIP)
{
    int iClientFd=0;
    struct sockaddr_in client_addr;
#if defined(__USE_BY_WIN32__)  
    int sin_size;  
#endif  
#if defined(__USE_BY_LINUX__)  
    socklen_t sin_size;  
#endif  
    TSocket *ctrl=(TSocket*)p_socketCtrl;

    if(p_socketCtrl == NULL) return -1;

    sin_size = sizeof(client_addr);
    memset(&client_addr, 0, sizeof(struct sockaddr_in));

    iClientFd = accept(ctrl->iFd, (struct sockaddr*)&client_addr, &sin_size);

    if( 0 < iClientFd ) sprintf(p_caClientIP, "%s", inet_ntoa(client_addr.sin_addr));

    return iClientFd;
}

