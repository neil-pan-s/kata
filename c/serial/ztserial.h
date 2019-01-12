#ifndef __ZTSERIAL_H__
#define __ZTSERIAL_H__

//�������
typedef enum
{             
    ERR_COM_OPEN_COM                 = -201,   //�򿪴���ʧ��
    ERR_COM_WRITE                    = -202,   //д��������
    ERR_COM_BPS                      = -203,   //������ָ������
    ERR_COM_SETATTR                  = -204,   //��������ʧ��
    ERR_COM_READ_TIMEOUT             = -205,   //���������ݳ�ʱ
    ERR_COM_PKG_FMT                  = -206,   //���װ���ʽ��
    ERR_COM_READ                     = -207,   //�����ݴ���
    ERR_COM_RETSTS                   = -208,   //���ش���״̬
                                                  
}TSerialErr;

typedef struct
{
	int  iComFd;             //�����ļ�������
	int  iComBps;            //���ڲ�����
	int  iComParity;         //������żУ��
	int  iComDatabit;        //����λ
	int  iComStopbit;        //ֹͣλ
	char caComDevPath[64];   //�����豸�ļ�	
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
