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
 *func: 16进制数据打印
 *args:
        p_caHex 源数据
        p_iLen  长度
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
 *func: 把源缓冲区内的ASCII码转化为压缩BCD码，存储到目的缓冲区内 ASCII码值大小写不敏感，范围(0~9，a~f，A~F)
 *args:
        p_caOutStr 目的缓冲区
        p_caInStr  源缓冲区
        p_iInStrLen 要转换的ASCII串长度 单位字节
        p_iType   此参数仅在 p_iInStrLen 为奇数时有效
            = 0  右补零(即左对齐)
            = 1  左补零(即右对齐)
*************************************************************************************]*/
int ZT_Asc2Bcd( char *p_caInStr , int p_iInStrLen , unsigned char * p_caOutStr,int p_iType )
{
    int i = 0;
    char c = 0, ch = 0, cFlag = 0xFF;

    *p_caOutStr = 0x00;

    //奇数位长度 左补零处理
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
            //非法字符
            //保留低四位
            c = (ch&0x0F); 
        }  

        if(!cFlag)
        {
            *p_caOutStr |= c;  //低4位
            p_caOutStr++;
            //清空
            *p_caOutStr = 0x00;
        }
        else
        {
            *p_caOutStr |= (c << 4); //高4位
        }    

        //用于标识奇偶位 
        cFlag = ~cFlag;   
        p_caInStr++;

    }

    return 0;
}

/*[method*******************************************************************************
 *def: int ZT_Bcd2Asc(unsigned char *p_caInStr , int p_iInStrLen ,char *p_caOutStr ,  char p_iType )
 *func: 把源缓冲区内的压缩BCD码转化为ASCII码，存储到目的缓冲区内
 *args:
        p_caOutStr 目的缓冲区
        p_caInStr  源缓冲区
        p_iInStrLen 要转换的Hex串长度 单位 半字节
        p_iType   此参数仅在 p_iInStrLen 为奇数时有效 补零为对源缓冲区补零
            = 0  右补零(即左对齐)
            = 1  左补零(即右对齐)
*************************************************************************************]*/
int ZT_Bcd2Asc(unsigned char *p_caInStr , int p_iInStrLen ,char *p_caOutStr ,  char p_iType )
{
    int i = 0;
    char ch = 0, cFlag = 0xFF;

    *p_caOutStr = 0x00;

    //奇数位长度 左补零处理
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
            ch = ((*p_caInStr) & 0x0F); //取低4位
        }
        else
        {
            ch = ((*p_caInStr)>>4); //取高4位
        }      

        if( (ch >= 0) && (ch <= 9))
        {
            *p_caOutStr = ch + '0';
        }
        else if( (ch >= 10) && (ch <= 16))
        {
            *p_caOutStr = ch -10 + 'A';
        }else{
            //非法字符
            return -1;
        }

        p_caOutStr++;

        if(!cFlag)
        {
            p_caInStr++;
        }

        //用于标识奇偶位 
        cFlag = ~cFlag;   

    }

    //奇数位长度 右补零处理
    if((p_iInStrLen & 0x01) && (p_iType == 0) )
    {   
        *p_caOutStr = '0';
    }

    return 0;
}

/*[method*******************************************************************************
 *def:  void ZT_Trim(char *p_caInStr, char *p_caOutStr, TTrimMode p_stMode)
 *func: 去除前后的空字符, p_caOutStr可以与p_caInStr是同一个变量
 *args: p_caInStr      源字符串
        p_stMode       处理模式
            TRIM_LEFT        = 1,    //去前导0x20, 0x09
            TRIM_RIGHT       = 2,    //去末尾0x20, 0x09, 0x0D, 0x0A
            TRIM_LEFT_RIGHT  = 3     //去前后空字符
 *output:  p_caOutStr     目标字符串
*************************************************************************************]*/
void ZT_Trim(char *p_caInStr, char *p_caOutStr, TTrimMode p_stMode)
{
    int   i = 0;
    char *caTmp = NULL;

    caTmp = (char*)malloc(strlen(p_caInStr) + 4);
    memset(caTmp, 0, strlen(p_caInStr) + 4);

    //需要去掉前导空格
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

    //删除末尾的空格、TAB、回车、换行
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
 *func: 去除前后的空字符, p_caOutStr可以与p_caInStr是同一个变量
 *args: p_caInStr      源字符串
        p_stMode       处理模式
            TRIM_LEFT        = 1,    //去前导0x20, 0x09
            TRIM_RIGHT       = 2,    //去末尾0x20, 0x09, 0x0D, 0x0A
            TRIM_LEFT_RIGHT  = 3     //去前后空字符
 *output:  p_caOutStr     目标字符串
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

    iStart = 0;      //当前域的开始位置,初始时,指向第一个字符
    iN = 0;          //解析到得分隔符个数
    for (i = 0; i <= p_iSrcLn; i++)
    {
        if ( (p_cpTmp[i] & 0xff) == p_cCh ) //是一个分隔符
        {
            iN++;
            if ( p_iN < iN ) break;
            if ( p_iN == iN )    //如果是制定的域
            {
                iEnd = i - 1;
                break;
            }
            else
            {
                iStart = i + 1;   //开始位置指向分隔符后一个字符
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
 *func: 将给定字符串中的指定字符串,用指定的字符串替换.
        字符串长度不能大于1024字节.
 *args: #src           源字符串
        #fine_str      需要查找的字符串
        #rep_str       用来替换的字符串
        #src_ln        源字符串长度
        #find_len      需要查找的字符串的长度
        #rep_len       用于替换的字符串的长度
 *output: #src           替换后的字符串
 *ret: 0<=ret  处理后的字符串长度
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
        ln1 = tmp_pos - pos1;        //查找部分之前的长度
        ln2 = src_len - ln1 - strlen(find_str);   //查找部分之后的长度

        memcpy(pos2, pos1, ln1);
        memcpy(pos2 + ln1, rep_str, rep_len);
        memcpy(pos2 + ln1 + rep_len, pos1 + ln1 + find_len, ln2);
        i_pos = ln1 + rep_len - 1;    //跳过已检测部分,避免用于替换的串中包含有被替换的串从而导致内存溢出的错误

        ret_ln = ln1 + rep_len + ln2;
        memset(pos1, 0, ca_ln);
        memcpy(pos1, pos2, ret_ln);
        src_len = strlen(pos1);     //非常重要
    }

    memset(src, 0, ret_ln + 1);
    memcpy(src, pos1, ret_ln);
    free(pos1);
    free(pos2);
    return ret_ln;
}


/*[method*******************************************************************************
 *def:  public unsigned int ZT_MsecTime()
 *func: 获取时间的毫秒值
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
 *func: 根据需要取得当前日期的需要部分.
 *args: p_caDate      日期字符串,NULL表示不需要取日期
        p_caTime      时间字符串,NULL表示不需要取时间
        p_caMsec      毫秒字符串,NULL表示不需要取毫秒
 *ret:  0=   成功
        <0   失败
*************************************************************************************]*/
void ZT_DateTime(char *p_caDate, char *p_caTime, char *p_caMsec)
{
    time_t t;
    struct tm *tm;
    char tmp1[16] = {0}, tmp2[16] = {0}, tmp3[16] = {0};

    //取得日期时间
    time(&t);
    tm = localtime(&t);

    //将日期时间格式化
    sprintf(tmp1, "%04d-%02d-%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
    sprintf(tmp2, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
    sprintf(tmp3, "%03ud", ZT_MsecTime() % 1000);

    if (p_caDate != NULL) memcpy(p_caDate, tmp1, strlen(tmp1));
    if (p_caTime != NULL) memcpy(p_caTime, tmp2, strlen(tmp2));
    if (p_caMsec != NULL) memcpy(p_caMsec, tmp3, strlen(tmp3));
}





