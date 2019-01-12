/* 
* @Author: ChangingP
* @Date:   2015-03-26 22:41:39
* @Last Modified by:   ChangingP
* @Last Modified time: 2015-03-28 19:45:48
*/

#include <stdio.h>
#include <memory.h>

#include "ztstring.h"

#define DATA_UTF_8 "\xe7\xa9\xbf\xe8\xb6\x8a\xe9\x95\xbf\xe5\x9f\x8e\x2c\xe8\xb5\xb0\xe5\x90\x91\xe4\xb8\x96\xe7\x95\x8c"
#define DATA_GBK "\xb4\xa9\xd4\xbd\xb3\xa4\xb3\xc7\x2c\xd7\xdf\xcf\xf2\xca\xc0\xbd\xe7"

int main(int argc, char const *argv[])
{
	int iRet = 0,iLen = 0;	
	char caOut[124]={0};

	memset(caOut,0,sizeof(caOut));
	iRet = ZT_Asc2Bcd("1234567890111111111222222222",28,(unsigned char *)caOut,0);
	printf("------------- %s -- %d ------------ iRet = %d\n",__func__,__LINE__,iRet);
	ZT_HexPrint("",(unsigned char *)caOut,14);

	memset(caOut,0,sizeof(caOut));
	ZT_Asc2Bcd("1234567890111111111222222223",27,(unsigned char *)caOut,1);
	ZT_HexPrint("caOut = ",(unsigned char *)caOut,14);

	memset(caOut,0,sizeof(caOut));
	ZT_Asc2Bcd("123456789011111111122222222",27,(unsigned char *)caOut,0);
	ZT_HexPrint("caOut = ",(unsigned char *)caOut,14);

	memset(caOut,0,sizeof(caOut));
	ZT_Asc2Bcd("123456789011111111122222222",27,(unsigned char *)caOut,1);
	ZT_HexPrint("caOut = ",(unsigned char *)caOut,14);

	memset(caOut,0,sizeof(caOut));
	ZT_Bcd2Asc((unsigned char *)"\x12\x34\x56\x78\x90\x11\x11\x11\x11\x12\x22\x22\x22\x22",14,caOut,0);
	ZT_HexPrint("caOut = ",(unsigned char *)caOut,28);

	memset(caOut,0,sizeof(caOut));
	ZT_Bcd2Asc((unsigned char *)"\x12\x34\x56\x78\x90\x11\x11\x11\x11\x12\x22\x22\x22",13,caOut,1);
	ZT_HexPrint("caOut = ",(unsigned char *)caOut,28);

	memset(caOut,0,sizeof(caOut));
	ZT_Bcd2Asc((unsigned char *)"\x12\x34\x56\x78\x90\x11\x11\x11\x11\x12\x22\x22\x22\x22",27,caOut,0);
	ZT_HexPrint("caOut = ",(unsigned char *)caOut,28);	

	printf("----------------- %s -- %d ---------------- iRet = %d\n",__func__,__LINE__,iRet);

	return 0;
}