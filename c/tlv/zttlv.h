#ifndef __ZTTLV_H__
#define __ZTTLV_H__

#include "ztmutex.h"

/*�̰߳�ȫ��*/

typedef struct
{
    char  caTag[5];
    //int   iTagLn;    //��δʹ��
    char *caValue;    
    int   iValueLn;
    void *next;
}TTlvItem;

typedef struct
{
    TTlvItem  *header;      //ͷָ��
    TMutex  *mutex;         //�̻߳�����    
}TTlv;


//����һ��ZTTLV���ݴ洢�ṹ
int ZTTlv_Init(TTlv **p_Ctrl);

//�ͷ�һ��ZTTLV���ݴ洢�ṹ
int ZTTlv_Destroy(TTlv *p_Ctrl);

/*
    ����һ����ǩ��ֵ,����ñ�ǩ������,�����һ����ǩ
    p_caTag     ��ǩ
    p_caValue   ��ǩ��Ӧ��ֵ
    p_iLn       ֵ�ĳ���
*/
int  ZTTlv_Set(TTlv *p_Ctrl,const char *p_caTag, const char *p_caValue, int p_iLn);

//��ӡ���еı�ǩ����,������,p_iMaxLn��ӡ��ֵ����󳤶�
int ZTTlv_Print(TTlv *p_Ctrl,int p_iMaxLn);

//������е�tlv��ֵ��
int ZTTlv_Clear(TTlv *p_Ctrl);

//���ָ�����͵ı�ǩ, p_caTagָ����ǩ��ǰ׺
int ZTTlv_ClearTag(TTlv *p_Ctrl,const char *p_caTag);

//ȡ��һ����ǩ��ֵ
int ZTTlv_Get(TTlv *p_Ctrl,const char *p_caTag, char *p_caValue,int *p_iLn);
//ȡ�ñ�ǩֵ
char *ZTTlv_GetTagValue(TTlv *p_Ctrl,const char *p_caTag);
//ȡ�ñ�ǩֵ����
int ZTTlv_GetTagLen(TTlv *p_Ctrl,const char *p_caTag);

/*
    ��һ����ǩ��ֵ�鵽ָ���Ľ��װ���
    p_caTag     ��ǩ
    p_iBCD      �Ƿ�ִ��ѹ��, 1:ѹ��, 2:��ѹ��
    p_caBuff    ������ݵĻ�����
    p_iBuffLn   �Ѿ��еİ����ݳ���,�����Ҫ���¸ó���
*/
int ZTTlv_Seal(TTlv *p_Ctrl,const char *p_caTag, int p_iBCD, char *p_caBuff, int *p_iBuffLn);

//��ָ���İ��е�һ��tlvԪ�ؽ����
int ZTTlv_Unseal(TTlv *p_Ctrl,const char *p_caBuff, int p_iLn);

/*
    �������� 
    p_caTag     �������ǩ
    p_caBuff    ����õĻ�����
    p_ipLn      ����������
*/
int ZTTlv_Package(TTlv *p_Ctrl,char *p_caTag,char *p_caBuff, int *p_ipLn);

/*
    �������� 
    p_caBuff    ����õĻ�����
    p_ipLn      ���������� ��δʹ�� �ɴ�0
*/
int ZTTlv_UnPackage(TTlv *p_Ctrl,const char *p_caBuff, int p_ipLn);

#endif  //__ZTTLV_H__
