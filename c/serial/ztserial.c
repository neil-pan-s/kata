#include "ztserial.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termio.h>
#include <string.h>

/*[method*******************************************************************************
 *def:  int ZTSerial_Init(TSerial ** p_serial)
 *func: �������ú���
*************************************************************************************]*/
int ZTSerial_Init(TSerial ** p_serial)
{
    TSerial *ctrl=NULL;

    if(p_serial == NULL) return -1;

    //���������ļ����ƽṹ
    ctrl = (TSerial*)malloc(sizeof(TSerial));
    memset(ctrl, 0, sizeof(TSerial));

	memset(ctrl->caComDevPath, 0, sizeof(64));

	ctrl->iComFd        = -1;              //�ļ�������,-1��ʾû�й����豸
    ctrl->iComBps       = 115200;          //���ڲ�����
    ctrl->iComParity    = 0;               //������żУ��
    ctrl->iComDatabit   = 8;               //����λ
    ctrl->iComStopbit   = 1;               //ֹͣλ

    *p_serial = ctrl;
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTSerial_SetParam(TSerial *p_serial,const char *p_caDev, int p_iBps, int p_iParity, int p_iDataBit, int p_iStopBit)
 *func: ���ò���
*************************************************************************************]*/
int ZTSerial_SetParam(TSerial *p_serial,const char *p_caDev, int p_iBps, int p_iParity, int p_iDataBit, int p_iStopBit)
{
	TSerial *ctrl=p_serial;

    if(p_serial == NULL) return -1;

    if( ctrl->iComFd != -1 ) ZTSerial_Close(ctrl);

	memset(ctrl->caComDevPath, 0, sizeof(64));

	ctrl->iComFd        = -1;              //�ļ�������,-1��ʾû�й����豸
    ctrl->iComBps       = p_iBps;          //���ڲ�����
    ctrl->iComParity    = p_iParity;       //������żУ��
    ctrl->iComDatabit   = p_iDataBit;      //����λ
    ctrl->iComStopbit   = p_iStopBit;      //ֹͣλ
    strcpy(ctrl->caComDevPath, p_caDev);   //�豸·��

    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTSerial_Open(TSerial *p_serial)
 *func: ��ָ���Ĵ���
 *ret:  0=ret   �ɹ�
        ret<0   ʧ��
*************************************************************************************]*/
int ZTSerial_Open(TSerial *p_serial)
{
	int  ret=0;
	TSerial *ctrl=p_serial;

	if(p_serial == NULL) return -1;

	ZTSerial_Close(ctrl);  //��������Ѿ��򿪣����ȹرգ��ٴ�

	ctrl->iComFd = open(ctrl->caComDevPath, O_RDWR | O_SYNC);  // | O_NDELAY |O_SYNC

	if( ctrl->iComFd < 0 ) return ERR_COM_OPEN_COM;
	ret = ZTSerial_SetAttribute(ctrl);

	return ret;
}

/*[method*******************************************************************************
 *def:  int ZTSerial_Close(TSerial *p_serial)
 *func: �ر�ָ���Ĵ���
*************************************************************************************]*/
int ZTSerial_Close(TSerial *p_serial)
{
	if(p_serial == NULL) return -1;

	TSerial *ctrl=p_serial;
	if( ctrl->iComFd != -1) close(ctrl->iComFd);
	ctrl->iComFd = -1;

	return 0;
}

/*[method*******************************************************************************
 *def:  int ZTSerial_Clear(TSerial *p_serial)
 *func: �����д����
*************************************************************************************]*/
int ZTSerial_Clear(TSerial *p_serial)
{
	if(p_serial == NULL) return -1;

	tcflush( p_serial->iComFd, TCIOFLUSH);
	return 0;	
}

/*[method*******************************************************************************
 *def:  int ZTSerial_Read(TSerial *p_serial,char *p_caOut, int p_iNeedReadLn)
 *func: �Ӵ��ڶ�ȡָ����������, ����ʵ�ʶ��������ݳ��ȡ��˷������÷�������ʽ��ȡ��������,
        ������ڵ�ǰû������,���������ء�
 *args: p_caOut       ��ȡ�������ݴ洢�ռ�
        p_iNeedReadLn ��Ҫ��ȡ�����ݳ���
 *ret:  ret<0        ʧ��
        0<=ret       ���������ݳ���
*************************************************************************************]*/
int ZTSerial_Read(TSerial *p_serial,char *p_caOut, int p_iNeedReadLn)
{
	int iReadyReadLn=0, iCurReadLn=0;
	TSerial *ctrl=p_serial;

    if(p_serial == NULL) return -1;

	if( ctrl->iComFd < 0 || p_iNeedReadLn< 1) return 0;

	while(1==1)
	{
		usleep(10);
		iCurReadLn = read( ctrl->iComFd, p_caOut+iReadyReadLn, p_iNeedReadLn-iReadyReadLn);
			//printf("iCurReadLn=%d\n",iCurReadLn);
		if( iCurReadLn<=0) return iReadyReadLn;
		iReadyReadLn = iReadyReadLn + iCurReadLn;
		if(iReadyReadLn==p_iNeedReadLn) return iReadyReadLn;
	}
	return iReadyReadLn;
}

/*[method*******************************************************************************
 *def:  int ZTSerial_Write(TSerial *p_serial,const char *p_caIn, int p_iSendLn)
 *func: �򴮿ڷ�������,�ֶη���,ÿ�η���100�ֽ�����,ÿ��100�ֽ����ݺ�,�ȴ�100ms
 *args: p_caIn    ��Ҫ���͵����ݴ洢�ռ�
        p_iSendLn ��Ҫ��ȡ�����ݳ���
 *ret:  ret<0        ʧ��
        0<=ret       ʵ�ʷ��͵����ݳ���
*************************************************************************************]*/
int ZTSerial_Write(TSerial *p_serial,const char *p_caIn, int p_iSendLn)
{
	int iReadyWriteLn=0, iCurNeedWriteLn=0, iCurWriteLn=0;
	TSerial *ctrl=p_serial;

    if(p_serial == NULL) return -1;

	if( ctrl->iComFd < 0 || p_iSendLn< 1) return 0;

	while(1==1)
	{
		if( (p_iSendLn-iReadyWriteLn) >512 )
			 iCurNeedWriteLn = 512;
		else iCurNeedWriteLn = p_iSendLn - iReadyWriteLn;

		iCurWriteLn = write( ctrl->iComFd, p_caIn+iReadyWriteLn, iCurNeedWriteLn);
		if( iCurWriteLn < 0) return ERR_COM_WRITE;

		iReadyWriteLn = iReadyWriteLn + iCurWriteLn;
		if(iReadyWriteLn == p_iSendLn) break;
		usleep(300000);
	}
	return iReadyWriteLn;
}

/*[method*******************************************************************************
 *def:  int ZTSerial_SetAttribute(TSerial *p_serial)
 *func: ���ô�������
 *ret:  ret=0   �ɹ�
        ret<0   ʧ��
*************************************************************************************]*/
int ZTSerial_SetAttribute(TSerial *p_serial)
{
	struct termios tios;  //�����ն����Խṹ
	int iSpeed=0, iModemcontrl=0;
	TSerial *ctrl=p_serial;

    if(p_serial == NULL) return -1;

	memset(&tios, 0, sizeof(tios));

	switch(ctrl->iComBps)
	{
		case 300:     iSpeed = B300;     break;
		case 600:     iSpeed = B600;     break;
		case 1200:    iSpeed = B1200;    break;
		case 1800:    iSpeed = B1800;    break;
		case 2400:    iSpeed = B2400;    break;
		case 4800:    iSpeed = B4800;    break;
		case 9600:    iSpeed = B9600;    break;
		case 19200:   iSpeed = B19200;   break;
		case 38400:   iSpeed = B38400;   break;
		case 57600:   iSpeed = B57600;   break;
		case 115200:  iSpeed = B115200;  break;
		default: return ERR_COM_BPS;
	}

	tcgetattr(ctrl->iComFd, &tios);  //1����ȡ�������ԣ�Ĭ�ϵĻ���ǰ���õģ�

 	tios.c_cflag     &= ~(CSIZE | CSTOPB | PARENB);	   //2������Ϊ���ô�������
	tios.c_cflag     |= CS8 | CREAD | HUPCL | CLOCAL;  //3����������μ�LINUX���ն���������

	tios.c_iflag      = IGNBRK | IGNPAR;
	tios.c_oflag      = 0;
	tios.c_lflag      = 0;
	tios.c_cc[VMIN]   = 0;    //���ٿɶ�����
	tios.c_cc[VTIME]  = 1;    //�ȴ�����ʱ��,10��ı���

  	cfsetospeed (&tios, iSpeed);   //4���������������
	cfsetispeed (&tios, iSpeed);   //5���������벨����

    //6��ʹ�������õ�����������Ч
	if (tcsetattr(ctrl->iComFd, TCSAFLUSH, &tios) < 0) return ERR_COM_SETATTR;

	iModemcontrl = TIOCM_DTR;
	ioctl(ctrl->iComFd, TIOCMBIS, &iModemcontrl);
	iModemcontrl = TIOCM_RTS;
	ioctl(ctrl->iComFd, TIOCMBIS, &iModemcontrl);

	return 0;
}

