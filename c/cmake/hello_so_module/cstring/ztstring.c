#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

#include "ztstring.h"

#define __USE_BY_LINUX__ 

/*[method*******************************************************************************
 *def:  int ZT_HexPrint(unsigned char * p_caHex,int p_iLen)
 *func: 16�������ݴ�ӡ
 *args:
        p_caHex Դ����
        p_iLen  ����
*************************************************************************************]*/
int ZT_HexPrint(char *p_caSay,unsigned char * p_caHex,int p_iLen)
{
    int i = 0;

    printf("%s\n",p_caSay);
    for (i = 0; i < p_iLen; ++i)
    {
        printf("%02X",p_caHex[i]);
    }
    printf("\n");

    return 0;
}

/*[method*******************************************************************************
 *def:  int ZT_Asc2Bcd( char *p_caInStr , int p_iInStrLen , unsigned char * p_caOutStr,int p_iType )
 *func: ��Դ�������ڵ�ASCII��ת��Ϊѹ��BCD�룬�洢��Ŀ�Ļ������� ASCII��ֵ��Сд�����У���Χ(0~9��a~f��A~F)
 *args:
        p_caOutStr Ŀ�Ļ�����
        p_caInStr  Դ������
        p_iInStrLen Ҫת����ASCII������ ��λ�ֽ�
        p_iType   �˲������� p_iInStrLen Ϊ����ʱ��Ч
            = 0  �Ҳ���(�������)
            = 1  ����(���Ҷ���)
*************************************************************************************]*/
int ZT_Asc2Bcd( char *p_caInStr , int p_iInStrLen , unsigned char * p_caOutStr,int p_iType )
{
    int i = 0;
    char c = 0, ch = 0, cFlag = 0xFF;

    *p_caOutStr = 0x00;

    //����λ���� ���㴦��
    if((p_iInStrLen & 0x01) && (p_iType == 1) )
    {   
        cFlag = 0x00;            
    }

    for (i = 0; i < p_iInStrLen; i++)
    {
        ch = *p_caInStr;

        if( (ch >= 'a') && (ch <= 'f'))
        {
            c = ch - 'a' + 10;
        }
        else if( (ch >= 'A') && (ch <= 'F'))
        {
            c = ch - 'A' + 10;
        }
        else if( (ch >= '0') && (ch <= '9'))
        {
            c = ch - '0';
        }
        else
        {
            //�Ƿ��ַ�
            //��������λ
            c = (ch&0x0F); 
        }  

        if(!cFlag)
        {
            *p_caOutStr |= c;  //��4λ
            p_caOutStr++;
            //���
            *p_caOutStr = 0x00;
        }
        else
        {
            *p_caOutStr |= (c << 4); //��4λ
        }    

        //���ڱ�ʶ��żλ 
        cFlag = ~cFlag;   
        p_caInStr++;

    }

    return 0;
}

/*[method*******************************************************************************
 *def: int ZT_Bcd2Asc(unsigned char *p_caInStr , int p_iInStrLen ,char *p_caOutStr ,  char p_iType )
 *func: ��Դ�������ڵ�ѹ��BCD��ת��ΪASCII�룬�洢��Ŀ�Ļ�������
 *args:
        p_caOutStr Ŀ�Ļ�����
        p_caInStr  Դ������
        p_iInStrLen Ҫת����Hex������ ��λ ���ֽ�
        p_iType   �˲������� p_iInStrLen Ϊ����ʱ��Ч ����Ϊ��Դ����������
            = 0  �Ҳ���(�������)
            = 1  ����(���Ҷ���)
*************************************************************************************]*/
int ZT_Bcd2Asc(unsigned char *p_caInStr , int p_iInStrLen ,char *p_caOutStr ,  char p_iType )
{
    int i = 0;
    char ch = 0, cFlag = 0xFF;

    *p_caOutStr = 0x00;

    //����λ���� ���㴦��
    if((p_iInStrLen & 0x01) && (p_iType == 1) )
    {   
        *p_caOutStr = '0';
        p_caOutStr++;
        *p_caOutStr = 0x00;
    }

    for (i = 0; i < p_iInStrLen; i++)
    {        
        if(!cFlag)
        {
            ch = ((*p_caInStr) & 0x0F); //ȡ��4λ
        }
        else
        {
            ch = ((*p_caInStr)>>4); //ȡ��4λ
        }      

        if( (ch >= 0) && (ch <= 9))
        {
            *p_caOutStr = ch + '0';
        }
        else if( (ch >= 10) && (ch <= 16))
        {
            *p_caOutStr = ch -10 + 'A';
        }else{
            //�Ƿ��ַ�
            return -1;
        }

        p_caOutStr++;

        if(!cFlag)
        {
            p_caInStr++;
        }

        //���ڱ�ʶ��żλ 
        cFlag = ~cFlag;   

    }

    //����λ���� �Ҳ��㴦��
    if((p_iInStrLen & 0x01) && (p_iType == 0) )
    {   
        *p_caOutStr = '0';
    }

    return 0;
}

/*[method*******************************************************************************
 *def:  void ZT_Trim(char *p_caInStr, char *p_caOutStr, TTrimMode p_stMode)
 *func: ȥ��ǰ��Ŀ��ַ�, p_caOutStr������p_caInStr��ͬһ������
 *args: p_caInStr      Դ�ַ���
        p_stMode       ����ģʽ
            TRIM_LEFT        = 1,    //ȥǰ��0x20, 0x09
            TRIM_RIGHT       = 2,    //ȥĩβ0x20, 0x09, 0x0D, 0x0A
            TRIM_LEFT_RIGHT  = 3     //ȥǰ����ַ�
 *output:  p_caOutStr     Ŀ���ַ���
*************************************************************************************]*/
void ZT_Trim(char *p_caInStr, char *p_caOutStr, TTrimMode p_stMode)
{
    int   i = 0;
    char *caTmp = NULL;

    caTmp = (char*)malloc(strlen(p_caInStr) + 4);
    memset(caTmp, 0, strlen(p_caInStr) + 4);

    //��Ҫȥ��ǰ���ո�
    if ( (p_stMode == TRIM_LEFT) || (p_stMode == TRIM_LEFT_RIGHT) )
    {
        i = 0;
        while ( (p_caInStr[i] == 0x20) || (p_caInStr[i] == 0x09))
        {
            i++;
        }
        sprintf(caTmp, "%s", p_caInStr + i);
    }
    else
    {
        sprintf(caTmp, "%s", p_caInStr);
    }

    //ɾ��ĩβ�Ŀո�TAB���س�������
    if ( (p_stMode == TRIM_RIGHT ) || (p_stMode == TRIM_LEFT_RIGHT ))
    {
        while ( (0 < strlen(caTmp)) &&
                ( (caTmp[strlen(caTmp) - 1] == 0x20) || (caTmp[strlen(caTmp) - 1] == 0x09) ||
                  (caTmp[strlen(caTmp) - 1] == 0x0D) || (caTmp[strlen(caTmp) - 1] == 0x0A) ))
            caTmp[strlen(caTmp) - 1] = 0;
    }

    sprintf(p_caOutStr, "%s", caTmp);
    free(caTmp);
}

/*[method*******************************************************************************
 *def:  int ZT_fieldn(const char *p_caSrc, int p_iSrcLn, char p_cCh, int p_iN, char *p_caOut)
 *func: ȥ��ǰ��Ŀ��ַ�, p_caOutStr������p_caInStr��ͬһ������
 *args: p_caInStr      Դ�ַ���
        p_stMode       ����ģʽ
            TRIM_LEFT        = 1,    //ȥǰ��0x20, 0x09
            TRIM_RIGHT       = 2,    //ȥĩβ0x20, 0x09, 0x0D, 0x0A
            TRIM_LEFT_RIGHT  = 3     //ȥǰ����ַ�
 *output:  p_caOutStr     Ŀ���ַ���
*************************************************************************************]*/
int ZT_Fieldn(const char *p_caSrc, int p_iSrcLn, char p_cCh, int p_iN, char *p_caOut)
{
    int   i = 0, iN = 0, iLn = 0, iStart = 0, iEnd = 0;
    char *p_cpTmp = NULL;

    if ( -1 == p_iSrcLn ) p_iSrcLn = strlen(p_caSrc);

    p_cpTmp = (char*)malloc(p_iSrcLn + 4);
    memset(p_cpTmp, 0, p_iSrcLn + 4);
    memcpy(p_cpTmp, p_caSrc, p_iSrcLn);
    p_cpTmp[p_iSrcLn] = p_cCh;

    iStart = 0;      //��ǰ��Ŀ�ʼλ��,��ʼʱ,ָ���һ���ַ�
    iN = 0;          //�������÷ָ�������
    for (i = 0; i <= p_iSrcLn; i++)
    {
        if ( (p_cpTmp[i] & 0xff) == p_cCh ) //��һ���ָ���
        {
            iN++;
            if ( p_iN < iN ) break;
            if ( p_iN == iN )    //������ƶ�����
            {
                iEnd = i - 1;
                break;
            }
            else
            {
                iStart = i + 1;   //��ʼλ��ָ��ָ�����һ���ַ�
            }
        }
    }

    if ( iStart <= iEnd )
    {
        memcpy(p_caOut, p_cpTmp + iStart, iEnd - iStart + 1);
        iLn = iEnd - iStart + 1;
    }
    free(p_cpTmp);

    return iLn;
}


/*[method*******************************************************************************
 *def:  public int ZT_ReplaceStr(char* src, const char* find_str, const char* rep_str, int src_len, int find_len, int rep_len)
 *func: �������ַ����е�ָ���ַ���,��ָ�����ַ����滻.
        �ַ������Ȳ��ܴ���1024�ֽ�.
 *args: #src           Դ�ַ���
        #fine_str      ��Ҫ���ҵ��ַ���
        #rep_str       �����滻���ַ���
        #src_ln        Դ�ַ�������
        #find_len      ��Ҫ���ҵ��ַ����ĳ���
        #rep_len       �����滻���ַ����ĳ���
 *output: #src           �滻����ַ���
 *ret: 0<=ret  �������ַ�������
*************************************************************************************]*/
int ZT_ReplaceStr(char* src, const char* find_str, const char* rep_str, int src_len, int find_len, int rep_len)
{
    char* tmp_pos;
    int ret_ln, ln1, ln2, i_pos;
    char *pos1 = NULL;
    char *pos2 = NULL;
    int  ca_ln = 0;
    ret_ln = src_len;
    pos1 = (char*) calloc(src_len + 1, sizeof(char));
    pos2 = (char*) calloc(src_len + 1, sizeof(char));
    memcpy(pos1, src, src_len);
    ca_ln = src_len + 1;
    i_pos = 0;
    while (1 == 1)
    {
        tmp_pos = strstr(pos1 + i_pos, find_str);
        if (tmp_pos == NULL) break;
        memset(pos2, 0, ca_ln);
        ln1 = tmp_pos - pos1;        //���Ҳ���֮ǰ�ĳ���
        ln2 = src_len - ln1 - strlen(find_str);   //���Ҳ���֮��ĳ���

        memcpy(pos2, pos1, ln1);
        memcpy(pos2 + ln1, rep_str, rep_len);
        memcpy(pos2 + ln1 + rep_len, pos1 + ln1 + find_len, ln2);
        i_pos = ln1 + rep_len - 1;    //�����Ѽ�ⲿ��,���������滻�Ĵ��а����б��滻�Ĵ��Ӷ������ڴ�����Ĵ���

        ret_ln = ln1 + rep_len + ln2;
        memset(pos1, 0, ca_ln);
        memcpy(pos1, pos2, ret_ln);
        src_len = strlen(pos1);     //�ǳ���Ҫ
    }

    memset(src, 0, ret_ln + 1);
    memcpy(src, pos1, ret_ln);
    free(pos1);
    free(pos2);
    return ret_ln;
}


/*[method*******************************************************************************
 *def:  public unsigned int ZT_MsecTime()
 *func: ��ȡʱ��ĺ���ֵ
*************************************************************************************]*/
unsigned int ZT_MsecTime()
{
    unsigned int us = 0;

#if defined(__USE_BY_LINUX__)
    struct timeval tv;
    gettimeofday(&tv, NULL);
    us = tv.tv_sec * 1000 + tv.tv_usec / 1000;
#elif defined(__USE_BY_WIN32__)
    us = GetTickCount();
#endif
    return us;
}

/*[method*******************************************************************************
 *def:  public void ZT_DateTime(char *p_caDate,char *p_caTime, char *p_caMsec)
 *func: ������Ҫȡ�õ�ǰ���ڵ���Ҫ����.
 *args: p_caDate      �����ַ���,NULL��ʾ����Ҫȡ����
        p_caTime      ʱ���ַ���,NULL��ʾ����Ҫȡʱ��
        p_caMsec      �����ַ���,NULL��ʾ����Ҫȡ����
 *ret:  0=   �ɹ�
        <0   ʧ��
*************************************************************************************]*/
void ZT_DateTime(char *p_caDate, char *p_caTime, char *p_caMsec)
{
    time_t t;
    struct tm *tm;
    char tmp1[16] = {0}, tmp2[16] = {0}, tmp3[16] = {0};

    //ȡ������ʱ��
    time(&t);
    tm = localtime(&t);

    //������ʱ���ʽ��
    sprintf(tmp1, "%04d-%02d-%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
    sprintf(tmp2, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
    sprintf(tmp3, "%03ud", ZT_MsecTime() % 1000);

    if (p_caDate != NULL) memcpy(p_caDate, tmp1, strlen(tmp1));
    if (p_caTime != NULL) memcpy(p_caTime, tmp2, strlen(tmp2));
    if (p_caMsec != NULL) memcpy(p_caMsec, tmp3, strlen(tmp3));
}





