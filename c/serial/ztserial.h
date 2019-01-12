#ifndef __ZTSERIAL_H__
#define __ZTSERIAL_H__

//错误代码
typedef enum
{             
    ERR_COM_OPEN_COM                 = -201,   //打开串口失败
    ERR_COM_WRITE                    = -202,   //写动作错误
    ERR_COM_BPS                      = -203,   //波特率指定错误
    ERR_COM_SETATTR                  = -204,   //设置属性失败
    ERR_COM_READ_TIMEOUT             = -205,   //读串口数据超时
    ERR_COM_PKG_FMT                  = -206,   //交易包格式错
    ERR_COM_READ                     = -207,   //读数据错误
    ERR_COM_RETSTS                   = -208,   //返回错误状态
                                                  
}TSerialErr;

typedef struct
{
	int  iComFd;             //串口文件描述符
	int  iComBps;            //串口波特率
	int  iComParity;         //串口奇偶校验
	int  iComDatabit;        //数据位
	int  iComStopbit;        //停止位
	char caComDevPath[64];   //串口设备文件	
}TSerial;

int ZTSerial_Init(TSerial ** p_serial);
int ZTSerial_SetParam(TSerial *p_serial,const char *p_caDev, int p_iBps, int p_iParity, int p_iDataBit, int p_iStopBit);
int ZTSerial_Open(TSerial *p_serial);
int ZTSerial_Close(TSerial *p_serial);
int ZTSerial_Clear(TSerial *p_serial);
int ZTSerial_Read(TSerial *p_serial,char *p_caOut, int p_iNeedReadLn);
int ZTSerial_Write(TSerial *p_serial,const char *p_caIn, int p_iSendLn);
int ZTSerial_SetAttribute(TSerial *p_serial);


#endif //__ZTSERIAL_H__
