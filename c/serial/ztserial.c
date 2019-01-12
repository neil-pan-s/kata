#include "ztserial.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termio.h>
#include <string.h>

/*[method*******************************************************************************
 *def:  int ZTSerial_Init(TSerial ** p_serial)
 *func: 串口配置函数
*************************************************************************************]*/
int ZTSerial_Init(TSerial ** p_serial)
{
    TSerial *ctrl=NULL;

    if(p_serial == NULL) return -1;

    //创建配置文件控制结构
    ctrl = (TSerial*)malloc(sizeof(TSerial));
    memset(ctrl, 0, sizeof(TSerial));

	memset(ctrl->caComDevPath, 0, sizeof(64));

	ctrl->iComFd        = -1;              //文件描述符,-1表示没有关联设备
    ctrl->iComBps       = 115200;          //串口波特率
    ctrl->iComParity    = 0;               //串口奇偶校验
    ctrl->iComDatabit   = 8;               //数据位
    ctrl->iComStopbit   = 1;               //停止位

    *p_serial = ctrl;
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTSerial_SetParam(TSerial *p_serial,const char *p_caDev, int p_iBps, int p_iParity, int p_iDataBit, int p_iStopBit)
 *func: 设置参数
*************************************************************************************]*/
int ZTSerial_SetParam(TSerial *p_serial,const char *p_caDev, int p_iBps, int p_iParity, int p_iDataBit, int p_iStopBit)
{
	TSerial *ctrl=p_serial;

    if(p_serial == NULL) return -1;

    if( ctrl->iComFd != -1 ) ZTSerial_Close(ctrl);

	memset(ctrl->caComDevPath, 0, sizeof(64));

	ctrl->iComFd        = -1;              //文件描述符,-1表示没有关联设备
    ctrl->iComBps       = p_iBps;          //串口波特率
    ctrl->iComParity    = p_iParity;       //串口奇偶校验
    ctrl->iComDatabit   = p_iDataBit;      //数据位
    ctrl->iComStopbit   = p_iStopBit;      //停止位
    strcpy(ctrl->caComDevPath, p_caDev);   //设备路径

    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTSerial_Open(TSerial *p_serial)
 *func: 打开指定的串口
 *ret:  0=ret   成功
        ret<0   失败
*************************************************************************************]*/
int ZTSerial_Open(TSerial *p_serial)
{
	int  ret=0;
	TSerial *ctrl=p_serial;

	if(p_serial == NULL) return -1;

	ZTSerial_Close(ctrl);  //如果串口已经打开，则先关闭，再打开

	ctrl->iComFd = open(ctrl->caComDevPath, O_RDWR | O_SYNC);  // | O_NDELAY |O_SYNC

	if( ctrl->iComFd < 0 ) return ERR_COM_OPEN_COM;
	ret = ZTSerial_SetAttribute(ctrl);

	return ret;
}

/*[method*******************************************************************************
 *def:  int ZTSerial_Close(TSerial *p_serial)
 *func: 关闭指定的串口
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
 *func: 清除读写缓存
*************************************************************************************]*/
int ZTSerial_Clear(TSerial *p_serial)
{
	if(p_serial == NULL) return -1;

	tcflush( p_serial->iComFd, TCIOFLUSH);
	return 0;	
}

/*[method*******************************************************************************
 *def:  int ZTSerial_Read(TSerial *p_serial,char *p_caOut, int p_iNeedReadLn)
 *func: 从串口读取指定长度数据, 返回实际读到的数据长度。此方法采用非阻塞方式读取串口数据,
        如果串口当前没有数据,则立即返回。
 *args: p_caOut       读取到的数据存储空间
        p_iNeedReadLn 需要读取的数据长度
 *ret:  ret<0        失败
        0<=ret       读到的数据长度
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
 *func: 向串口发送数据,分段发送,每次发送100字节数据,每发100字节数据后,等待100ms
 *args: p_caIn    需要发送的数据存储空间
        p_iSendLn 需要读取的数据长度
 *ret:  ret<0        失败
        0<=ret       实际发送的数据长度
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
 *func: 设置串口属性
 *ret:  ret=0   成功
        ret<0   失败
*************************************************************************************]*/
int ZTSerial_SetAttribute(TSerial *p_serial)
{
	struct termios tios;  //定义终端属性结构
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

	tcgetattr(ctrl->iComFd, &tios);  //1、获取串口属性（默认的或以前设置的）

 	tios.c_cflag     &= ~(CSIZE | CSTOPB | PARENB);	   //2、以下为设置串口属性
	tios.c_cflag     |= CS8 | CREAD | HUPCL | CLOCAL;  //3、具体意义参见LINUX的终端属性设置

	tios.c_iflag      = IGNBRK | IGNPAR;
	tios.c_oflag      = 0;
	tios.c_lflag      = 0;
	tios.c_cc[VMIN]   = 0;    //最少可读数据
	tios.c_cc[VTIME]  = 1;    //等待数据时间,10秒的倍数

  	cfsetospeed (&tios, iSpeed);   //4、设置输出波特率
	cfsetispeed (&tios, iSpeed);   //5、设置输入波特率

    //6、使以上设置的属性立即生效
	if (tcsetattr(ctrl->iComFd, TCSAFLUSH, &tios) < 0) return ERR_COM_SETATTR;

	iModemcontrl = TIOCM_DTR;
	ioctl(ctrl->iComFd, TIOCMBIS, &iModemcontrl);
	iModemcontrl = TIOCM_RTS;
	ioctl(ctrl->iComFd, TIOCMBIS, &iModemcontrl);

	return 0;
}

