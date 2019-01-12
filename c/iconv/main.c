/* 
* @Author: ChangingP
* @Date:   2015-03-26 22:41:39
* @Last Modified by:   ChangingP
* @Last Modified time: 2015-03-27 15:54:29
*/

#include <stdio.h>
#include <memory.h>
#include "zticonv.h"

#define DATA_UTF_8 "\xe7\xa9\xbf\xe8\xb6\x8a\xe9\x95\xbf\xe5\x9f\x8e\x2c\xe8\xb5\xb0\xe5\x90\x91\xe4\xb8\x96\xe7\x95\x8c"
#define DATA_GBK "\xb4\xa9\xd4\xbd\xb3\xa4\xb3\xc7\x2c\xd7\xdf\xcf\xf2\xca\xc0\xbd\xe7"

int main(int argc, char const *argv[])
{
	int iRet = 0,iLen = 0;	
	char caOut[124]={0};

	iRet = ZTIconv_Convert("UTF-8","GB18030",DATA_UTF_8,strlen(DATA_UTF_8),caOut,&iLen);
	printf("----------------- %s -- %d ---------------- iRet = %d\n",__func__,__LINE__,iRet);
	printf("caOut = %s,%x%x%x\n",caOut,0xFF&caOut[0],0xFF&caOut[1],0xFF&caOut[2]);

	memset(caOut,0,sizeof(caOut));

	iRet = ZTIconv_Dlopen("./lib/linux/libiconv.so");
	printf("----------------- %s -- %d ---------------- iRet = %d\n",__func__,__LINE__,iRet);

	iRet = ZTIconv_Dlconvert("UTF-8","GBK",DATA_UTF_8,strlen(DATA_UTF_8),caOut,&iLen);
	printf("----------------- %s -- %d ---------------- iRet = %d\n",__func__,__LINE__,iRet);
	printf("caOut = %s,%x%x%x\n",caOut,0xFF&caOut[0],0xFF&caOut[1],0xFF&caOut[2]);

	iRet = ZTIconv_Dlclose();
	printf("----------------- %s -- %d ---------------- iRet = %d\n",__func__,__LINE__,iRet);

	return 0;
}