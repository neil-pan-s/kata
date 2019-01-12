#include "ztloger.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define __USE_BY_LINUX__

static unsigned int get_cur_msec();
static void get_datetime(char *p_caDate,char *p_caTime, char *p_caMsec);

/*[method***********************************************************************
 *def: int ZTLoger_Init(ZTLoger **p_loger��,const char *p_caFile, TLogerLev p_stLev, bool p_blPrint, int p_iMaxLines)
 *func: ��־�����캯��.��/����һ����־�ṹ.
 *args: p_loger��       ��־�ļ��ṹ
        p_caFile        ��־�ļ�·��
        p_stLev         �����¼�������־����
        p_blPrint       �Ƿ��ӡ������Ϣ��ָ��������豸��
        p_iMaxLines     ��������������
*****************************************************************************]*/
int ZTLoger_Init(ZTLoger **p_loger,const char *p_caFile, TLogerLev p_stLev, bool p_blPrint, int p_iMaxLines)
{

    if(p_loger == NULL) return -1;

    *p_loger = NULL;    
    *p_loger = (void*)malloc(sizeof(ZTLoger));
    memset(*p_loger, 0, sizeof(ZTLoger));

    (*p_loger)->iLines     = 0;
    (*p_loger)->stLogerLev = p_stLev;
    (*p_loger)->blPrint    = p_blPrint;
    (*p_loger)->iMaxLines  = p_iMaxLines;

    sprintf((*p_loger)->caFile, "%s", p_caFile);

    //�����ļ��� 
    ZTMutex_Init(&(*p_loger)->mutex);

    return 0;
}
/*[method***********************************************************************
 *def:  int ZTLoger_Close(ZTLoger *p_loger)
 *func: ��־�ṹ��������.�ر���־�ļ�.
*****************************************************************************]*/
int ZTLoger_Close(ZTLoger *p_loger)
{
    if(p_loger == NULL) return -1;

    if (NULL != p_loger->mutex)
    {
        ZTMutex_Destroy(p_loger->mutex);
        p_loger->mutex = NULL;
    }
    return 0;
}

/*[method***********************************************************************
 *def:  int ZTLoger_Check(ZTLoger *p_loger)
 *func: ����ļ������Ƿ񳬹��涨��С,��������涨��С,����нض�
 *args: p_loger��       ��־�ļ��ṹ
*****************************************************************************]*/
int ZTLoger_Check(ZTLoger *p_loger)
{
    int   i=0,iLines = 0;
    char  caLine[4096]={0}, caFile[128]={0}, caCmd[256]={0};
    FILE *fp=NULL;
    FILE *fp2=NULL;

    if(p_loger == NULL) return -1;

    //ͳ���ļ�����
    ZTMutex_Lock(p_loger->mutex);
    fp = fopen(p_loger->caFile, "r");
    if( fp == NULL )
    {
        ZTMutex_Unlock(p_loger->mutex);
        return -2;
    }

    while( 1 )
    {
        memset(caLine, 0, sizeof(caLine));
        if( fgets(caLine, sizeof(caLine), fp)==NULL ) break;
        iLines++;
    }
    fclose(fp);
    ZTMutex_Unlock(p_loger->mutex);

    //����ļ��Ƿ񳬹��涨����
    if( (0 < p_loger->iMaxLines) && (p_loger->iMaxLines < iLines) )
    {
        ZTMutex_Lock(p_loger->mutex);
        fp = fopen(p_loger->caFile, "r");
        //��λ�ض�λ��
        for(i=0; i<(iLines - (p_loger->iMaxLines)); i++)
        {
            fgets(caLine, sizeof(caLine), fp);
        }
        //������־����ʱ�ļ�
        memset(caFile, 0, sizeof(caFile));
        sprintf(caFile, "%s.bak", p_loger->caFile);
        fp2 = fopen(caFile, "w");
        iLines = 0;    //����ͳ���ļ��ĵ�ǰ����
        while( 1 )
        {
            memset(caLine, 0, sizeof(caLine));
            if( fgets(caLine, sizeof(caLine), fp)==NULL ) break;
            fwrite(caLine, 1, strlen(caLine), fp2);
            iLines++;
        }
        fclose(fp);
        fclose(fp2);
        p_loger->iLines = iLines;
        ZTMutex_Unlock(p_loger->mutex);

    #if defined(__USE_BY_LINUX__)
        memset(caCmd, 0, sizeof(caCmd));
        sprintf(caCmd, "mv %s %s", caFile, p_loger->caFile);
        system(caCmd);
    #elif defined(__USE_BY_WIN32__)
        MoveFileExA(caFile, p_loger->caFile, MOVEFILE_REPLACE_EXISTING);
    #endif
    }

    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTLoger_Write(ZTLoger *p_loger,TLogerLev p_stLev, bool p_blScreenFlag, const char *format, ...)
 *func: {04}���ݸ�ʽ�ַ�����¼һ����־��ÿ���Զ��������ʱ�䡣 &_
        ���з��ڸ�ʽ�ַ�����ָ��.
 *args: p_loger��           ��־�ļ��ṹ        
        p_stLev             ��ǰ��¼����־����
        p_blScreenFlag      ������Ϣ�Ƿ������������Ļ
        p_caFormat          ��ʽ�ַ���
 *ret:  0=   �ɹ�
        <0   ʧ��
*************************************************************************************]*/
int ZTLoger_Write(ZTLoger *p_loger,TLogerLev p_stLev, bool p_blScreenFlag, const char *p_caFormat, ...)
{
    int  n=0, iMaxLines=0;
    char dt[124]={0};     //�������ʱ�� + ��־������Ϣ
    FILE *fp=NULL;

    if(p_loger == NULL) return -1;

    //�����ǰ��־������������¼����־����,�򲻼�¼
    if( p_loger->stLogerLev < p_stLev ) return -2;

    //����Ƿ���Ҫ�ض���־
    iMaxLines = (int)(((float)(p_loger->iMaxLines)) * 1.2 );
    if( iMaxLines < p_loger->iLines )
    {
        ZTLoger_Check(p_loger);
    }

    va_list arg_ptr;              //�����������

    ZTMutex_Lock(p_loger->mutex);
    (p_loger->iLines)++;   //��־������1
    fp = fopen(p_loger->caFile, "a+");      //��־�ļ�,��׷�ӷ�ʽ��
    if(fp == NULL)
    {
        ZTMutex_Unlock(p_loger->mutex);
        return -3;
    }
    //ȡ�ñ������,��ʼ�����������
    va_start(arg_ptr, p_caFormat);

    if( (p_blScreenFlag == 1) && (p_loger->blPrint == true) )
    {
        vfprintf(stderr, p_caFormat, arg_ptr);
    }

    //ȡ������ʱ��
    get_datetime(dt, (char*)(dt+11), (char*)(dt+20));
    dt[10] = 32;   dt[19] = 32;   dt[23] = 32;

    switch(p_stLev)
    {
        case LG_ERROR:{ strcat(dt," [LG_ERROR] "); break;} //���ش���
        case LG_FLOW:{ strcat(dt," [LG_FLOW] "); break;}  //������Ϣ
        case LG_DEBUG:{ strcat(dt," [LG_DEBUG] "); break;} //������Ϣ
        case LG_HARD:{ strcat(dt," [LG_HARD] "); break;}  //Ӳ��ͨѶ��Ϣ
        case LG_SEC:{ strcat(dt," [LG_SEC] "); break;}   //һ�㰲ȫ��Ϣ
        case LG_MSEC:{ strcat(dt," [LG_MSEC] "); break;}  //��Ҫ��ȫ��Ϣ
        default:{ break;}
    }

    //д����ʱ�� + ��־������Ϣ
    fwrite(dt, 1, strlen(dt), fp);

    //����־����д����־�ļ�
    n = vfprintf(fp, p_caFormat, arg_ptr);  //����ֵΪд����ֽ���
    //���������������
    va_end(arg_ptr);

    //��־����
    fwrite("\n", 1, 1, fp);

    //ˢ���ļ�
    fflush(fp);

    fclose(fp);

    //system("sync");

    ZTMutex_Unlock(p_loger->mutex);
    return 0;
}


/*[method*******************************************************************************
 *def:  static void  get_datetime(char *p_caDate,char *p_caTime, char *p_caMsec)
 *func: ������Ҫȡ�õ�ǰ���ڵ���Ҫ����.
 *args: p_caDate      �����ַ���,NULL��ʾ����Ҫȡ����
        p_caTime      ʱ���ַ���,NULL��ʾ����Ҫȡʱ��
        p_caMsec      �����ַ���,NULL��ʾ����Ҫȡ����
 *ret:  0=   �ɹ�
        <0   ʧ��
*************************************************************************************]*/
static void get_datetime(char *p_caDate,char *p_caTime, char *p_caMsec)
{
    time_t t;
    struct tm *tm;
    char tmp1[16]={0}, tmp2[16]={0}, tmp3[16]={0};

    //ȡ������ʱ��
    time(&t);
    tm = localtime(&t);

    //������ʱ���ʽ��
    sprintf(tmp1, "%04d-%02d-%02d",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday);
    sprintf(tmp2, "%02d:%02d:%02d",tm->tm_hour,tm->tm_min,tm->tm_sec);
    sprintf(tmp3, "%03ud", get_cur_msec() % 1000);

    if(p_caDate != NULL) memcpy(p_caDate, tmp1, strlen(tmp1));
    if(p_caTime != NULL) memcpy(p_caTime, tmp2, strlen(tmp2));
    if(p_caMsec != NULL) memcpy(p_caMsec, tmp3, strlen(tmp3));
}

/*[method*******************************************************************************
 *def:  static unsigned int ZTLoger::get_cur_msec()
 *func: ��ȡʱ��ĺ���ֵ
*************************************************************************************]*/
static unsigned int get_cur_msec()
{
    unsigned int us=0;

#if defined(__USE_BY_LINUX__)
    struct timeval tv;
    gettimeofday(&tv,NULL);
    us = tv.tv_sec*1000 + tv.tv_usec / 1000;
#elif defined(__USE_BY_WIN32__)
    us = GetTickCount();
#endif
    return us;
}
