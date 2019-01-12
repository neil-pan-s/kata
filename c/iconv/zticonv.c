#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <dlfcn.h>
#include <unistd.h>
#include "iconv.h"

typedef iconv_t (*piconv_open)(const char* tocode, const char* fromcode);
typedef int (*piconv_close)(iconv_t cd);
typedef size_t (*piconv)(iconv_t cd,  char* * inbuf, size_t *inbytesleft, char* * outbuf, size_t *outbytesleft);

void *handle = NULL;
piconv_open iconv_open1= NULL;
piconv_close iconv_close1=NULL;
piconv iconv1=NULL;


/*[method*******************************************************************************
 *def:  int ZTIconv_Convert(char *p_caInEncoding,char *p_caOutEncoding,char *p_caIn,int p_iInLen,char *p_caOut,int *p_iOutLen)
 *func: ���ݱ���ת�� 
 *args: 
		#p_caInCharset �������ݱ����ʽ
		#p_caOutCharset ������ݱ����ʽ
		#p_caIn	  �������� 	
 		#p_iInLen   �������ݳ���	
 		#p_caOut  ת��������
		#p_iOutLen ת�������ݳ��� �˲�������ǰ ��Ԥ������ת������ 
*************************************************************************************]*/
int ZTIconv_Convert(char *p_caInCharset,char *p_caOutCharset,char *p_caIn,int p_iInLen,char *p_caOut,int *p_iOutLen)
{	
	int iRet=0;
	iconv_t cd = 0;	

	cd=iconv_open(p_caOutCharset,p_caInCharset);
	if((int)cd == -1 ) 
	{
			return -1;				
	}
  
    //δԤ�����ת��ֵĬ�ϴ���
    if(*p_iOutLen <= 0)
    { 
        *p_iOutLen = 2048;  //����Ҫ��������ת��ֵ
	}

    iRet = iconv(cd,&p_caIn,&p_iInLen,&p_caOut, p_iOutLen);       
	if(iRet < 0) 
	{
			iconv_close(cd);    
			return -2;	
	}

	iconv_close(cd);    
  		
	return 0;  	
}	

/*[method*******************************************************************************
 *def:  int ZTIconv_Dlopen(char *p_caLibPath)
 *func: ����iconv��̬��
 *args: 
		#p_caLibPath ��·��
*************************************************************************************]*/
int ZTIconv_Dlopen(char *p_caLibPath)
{
    if(access(p_caLibPath,F_OK) != 0) return -1;  

    handle = dlopen (p_caLibPath, RTLD_LAZY);

    if (!handle) return -1;

    if(!(iconv1                  = (piconv)dlsym(handle,"iconv"))) return -1;
    if(!(iconv_open1            = (piconv_open)dlsym(handle,"iconv_open"))) return -1;
    if(!(iconv_close1        = (piconv_close)dlsym(handle,"iconv_close"))) return -1;
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTIconv_Dlclose()
 *func: �ر�iconv��̬��
 *args: 
		#p_caLibPath ��·��
*************************************************************************************]*/
int ZTIconv_Dlclose()
{
    if (!handle) return -1;

    dlclose(handle);
    iconv1 =NULL;
    iconv_open1= NULL;
    iconv_close1=NULL;
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTIconv_Dlconvert(const char *p_caInCharset, const char *p_caOutCharset,char *p_caIn,int p_iInlen,char *p_caOut,int p_iOutLen)
 *func: ���ݱ���ת�� 
 *args: 
		#p_caInCharset �������ݱ����ʽ
		#p_caOutCharset ������ݱ����ʽ
		#p_caIn	  �������� 	
 		#p_iLen   �������ݳ���	
 		#p_caOut  ת��������
		#p_iOutLen ת�������ݳ���  
*************************************************************************************]*/
int ZTIconv_Dlconvert(const char *p_caInCharset, const char *p_caOutCharset,char *p_caIn,int p_iInlen,char *p_caOut,int *p_iOutLen)
{
    iconv_t cd;
    int  iRet=0;

    //if(ZTIconv_Dlopen("./lib/linux/libiconv_plug.so")) return -1;

    //δԤ�����ת��ֵĬ�ϴ���
    if(*p_iOutLen <= 0)
    { 
        *p_iOutLen = 2048;  //����Ҫ��������ת��ֵ
    }

    cd = iconv_open1(p_caOutCharset,p_caInCharset);
    if (cd<=0) return -1;

    iRet = iconv1(cd,&p_caIn,&p_iInlen,&p_caOut,p_iOutLen);
    if (iRet==-1) return -1;
    iconv_close1(cd);

    //ZTIconv_Dlclose();
    return 0;
}


