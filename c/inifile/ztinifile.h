#ifndef __ZTINIFILE_H__
#define __ZTINIFILE_H__

#include "ztmutex.h"

/*�̰߳�ȫ��*/

typedef struct
{
    int   iType;         //1:����, 2:ֵ
    char *cpKey;         //�ؼ���
    char *cpValue;       //ֵ
    char *cpRemark;      //ע��
    void *next;          //��һ��Ԫ��
    void *pre;           //��һ��Ԫ��
}TIniItem;

typedef struct
{
    char caPath[128]; //�ļ���ԭʼ·��
    TIniItem *header; //ͷָ��
    TMutex *mutex;   //�������,����ʵ���̰߳�ȫ����
} TInifile;


/*
    p_caPath      �����ļ�·��
    p_blLoad      ���������ļ��Ƿ�ɹ�
*/
int ZTIni_Init(TInifile **p_iniCtrl,const char *p_caPath);

int ZTIni_Close(TInifile *p_iniCtrl);

//���������ļ���ʽ,��ӡ����ǰ���������ݵ���׼�����
void ZTIni_Print(TInifile *p_iniCtrl);

//�������õ�ָ���������ļ�,���p_caPathΪNULL,�򱣴浽ԭ�����ļ�
int ZTIni_Save(TInifile *p_iniCtrl,const char *p_caPath);

/*
    ȡ��ָ��������ָ���ؼ��ֵ�����ֵ,����ؼ��ֲ�����,�򷵻�Ĭ��ֵ,p_caValue����ΪNULL
    ����ֵҲ��ȡ�õĹؼ���ֵ,Ӧ�ó�������Լ���Ҫ��ȡ��ֵ
    p_caSection         ����
    p_caKey             �ؼ���
    p_caValue           ȡ�õ�ֵ,����Ϊ��,��ʾ����Ҫ��ֵ���浽������
    p_caDef             Ĭ��ֵ,���ؼ��ֲ�����ʱ,ʹ��Ĭ��ֵ����
*/
const char* ZTIni_Get(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, char *p_caValue, const char *p_caDef);

//ȡ��ָ��������ָ���ؼ��ֵ���������ֵ
int ZTIni_GetInt(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, int p_iDef);

//����ؼ��ֵ�ֵ
int ZTIni_Set(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, char *p_caValue);

//����ؼ��ֵ�ֵ
int ZTIni_SetInt(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, int p_iValue);

//ɾ��ָ��������
int ZTIni_DelSection(TInifile *p_iniCtrl,const char *p_caSection);

//ɾ��ָ���Ĺؼ���
int ZTIni_DelKey(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey);

//��������ĸ���
int ZTIni_GetSecationCnt(TInifile *p_iniCtrl);

//���ָ����ŵ���������
int ZTIni_GetSactionName(TInifile *p_iniCtrl,int p_iIdx, char *p_caName);

//ȡ��һ��ָ���Ĺؼ���
int ZTIni_GetKey(TInifile *p_iniCtrl,int p_iIdx, char *p_caSaction, char *p_caName, char *p_caValue);

#endif //__ZTINIFILE_H__
