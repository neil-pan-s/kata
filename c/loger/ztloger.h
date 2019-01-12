#ifndef __ZTLOGER_H__
#define __ZTLOGER_H__

#include <stdbool.h>
#include "ztmutex.h"

/*
    Ҫ����־�ļ���ÿ�еĳ���,���ܳ���4096�ֽ�
*/

//��־����
typedef enum
{
	LG_ERROR     = 0,     //���ش���
	LG_FLOW      = 1,     //������Ϣ
	LG_DEBUG     = 2,     //������Ϣ
	LG_HARD      = 7,     //Ӳ��ͨѶ��Ϣ
	LG_SEC       = 8,     //һ�㰲ȫ��Ϣ
	LG_MSEC      = 9      //��Ҫ��ȫ��Ϣ
}TLogerLev;

struct ZTLoger_st
{
    int       iLines;           //�ļ��ĵ�ǰ����
    int       iMaxLines;        //��������������
    char      caFile[128];      //��־�ļ�·��
    bool      blPrint;          //�Ƿ��������׼�����豸
    TMutex  *mutex;            //��־�ļ���
    TLogerLev stLogerLev;       //��־�ļ�����
};

typedef struct ZTLoger_st ZTLoger;

int ZTLoger_Init(ZTLoger **p_loger,const char *p_caFile, TLogerLev p_stLev, bool p_blPrint, int p_iMaxLines);
int ZTLoger_Close(ZTLoger *p_loger);
int ZTLoger_Check(ZTLoger *p_loger);
int ZTLoger_Write(ZTLoger *p_loger,TLogerLev p_stLev, bool p_blScreenFlag, const char *p_caFormat, ...);


#endif  //__LOGER_H__
