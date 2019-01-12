#ifndef __ZTSTRING_H__
#define __ZTSTRING_H__

typedef enum
{
    TRIM_LEFT        = 1,    //去前导0x20, 0x09
    TRIM_RIGHT       = 2,    //去末尾0x20, 0x09, 0x0D, 0x0A
    TRIM_LEFT_RIGHT  = 3     //去前后空字符
}TTrimMode;

int ZT_Asc2Bcd( char *p_caInStr , int p_iInStrLen , unsigned char * p_caOutStr,int p_iType );
int ZT_Bcd2Asc(unsigned char *p_caInStr , int p_iInStrLen ,char *p_caOutStr ,  char p_iType );
void ZT_Trim(char *p_caInStr, char *p_caOutStr, TTrimMode p_stMode);
int  ZT_Fieldn(const char *p_caSrc, int p_iSrcLn, char p_cCh, int p_iN, char *p_caOut);
int ZT_ReplaceStr(char* src, const char* find_str, const char* rep_str, int src_len, int find_len, int rep_len);
unsigned int ZT_MsecTime();
void ZT_DateTime(char *p_caDate,char *p_caTime, char *p_caMsec);
int ZT_HexPrint(char *p_caSay,unsigned char * p_caHex,int p_iLen);



#endif  //__ZTSTRING_H__
