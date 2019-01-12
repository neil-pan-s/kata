/* 
* @Author: ChangingP
* @Date:   2015-03-26 22:41:39
* @Last Modified by:   ChangingP
* @Last Modified time: 2015-04-05 23:08:51
*/

#include <stdio.h>
#include <memory.h>
#include <ztstring.h>
#include "zttlv.h"

int main(int argc, char const *argv[])
{
	int iRet = 0,iLen = 0,iTLen = 0;
	char caTmp[1024]={0},caTestTLV[1024]={0};
	TTlv * p_Ctrl = NULL;

	ZTTlv_Init(&p_Ctrl);

	/*
	READ RECORD	读记录
	－－－－－－－－
	C-APDU：
	05 00 B2 01 0C 00    //读P1指定SFI ( = 01)的 记录 01 

	Ｒ-APDU：
	45  //长度
	70 	28 //70模板 28 长度
		61 26 	//应用模板  包含和应用目录入口相关的1个或多个数据对象 
			4F  08		A0 00 00 03 33 01 01 01 	//应用标识符
			50  0A 	50 42 4F 43 20 44 45 42 49 54 	//应用标签	PBOC DEBIT
			9F 12 	0A 	50 42 4F 43 20 44 45 42 49 54 	//应用首选名称 PBOC DEBIT
			87 01 	01 	//应用优先指示器	没有持卡人确认应用可以选择 不指定优先级
	90 00   	
	*/	
	
	ZTTlv_Set(p_Ctrl,"4F","\xA0\x00\x00\x03\x33\x01\x01\x01",8);	
	ZTTlv_Set(p_Ctrl,"50","\x50\x42\x4F\x43\x20\x44\x45\x42\x49\x54",10);
	ZTTlv_Set(p_Ctrl,"9F12","PBOC DEBIT",10);
	ZTTlv_Set(p_Ctrl,"87","\x01",1);

	ZTTlv_Print(p_Ctrl,102400);
	
	ZTTlv_Seal(p_Ctrl,"4F",0,caTmp,&iLen);
	ZTTlv_Seal(p_Ctrl,"50",0,caTmp,&iLen);
	ZTTlv_Seal(p_Ctrl,"9F12",0,caTmp,&iLen);
	ZTTlv_Seal(p_Ctrl,"87",0,caTmp,&iLen);

	ZTTlv_Package(p_Ctrl,"61",caTmp,&iLen);
	ZTTlv_Package(p_Ctrl,"70",caTmp,&iLen);

	ZTTlv_Set(p_Ctrl,"90",NULL,0);
	ZTTlv_Seal(p_Ctrl,"90",0,caTmp,&iLen);
	ZT_HexPrint("ZTTlv_Package \n",(unsigned char *)caTmp,iLen);
	
	memset(caTmp,0,sizeof(caTmp));		
	ZTTlv_Get(p_Ctrl,"90",caTmp,&iLen);
	ZT_HexPrint("ZTTlv_Get tag = 90 \n",(unsigned char *)caTmp,iLen);

	memset(caTmp,0,sizeof(caTmp));
	ZTTlv_Get(p_Ctrl,"4F",caTmp,&iLen);
	ZT_HexPrint("ZTTlv_Get tag = 4F \n",(unsigned char *)caTmp,iLen);

	memset(caTmp,0,sizeof(caTmp));
	ZTTlv_ClearTag(p_Ctrl,"4F");
	
	memset(caTmp,0,sizeof(caTmp));
	ZTTlv_Get(p_Ctrl,"4F",caTmp,&iLen);
	ZT_HexPrint("ZTTlv_Get tag = 4F \n",(unsigned char *)caTmp,iLen);

	printf("------------------------------------------------- \n");	

	ZTTlv_Clear(p_Ctrl);
	ZTTlv_Print(p_Ctrl,102400);

	memcpy(caTestTLV,"\x61\x26\x4F\x08\xA0\x00\x00\x03\x33\x01\x01\x01\x50\x0A\x50\x42\x4F\x43\x20\x44\x45\x42\x49\x54\x9F\x12\x0A\x50\x42\x4F\x43\x20\x44\x45\x42\x49\x54\x87\x01\x01",40);

	ZTTlv_UnPackage(p_Ctrl,caTestTLV,40);

	iRet = ZTTlv_Unseal(p_Ctrl,ZTTlv_GetTagValue(p_Ctrl,"61"),ZTTlv_GetTagLen(p_Ctrl,"61"));
	printf("------------ ZTTlv_Unseal iRet = %d --------------- \n",iRet);	

	ZTTlv_Print(p_Ctrl,102400);

	memset(caTmp,0,sizeof(caTmp));
	ZTTlv_Get(p_Ctrl,"4F",caTmp,&iLen);
	ZT_HexPrint("ZTTlv_Get tag = 4F \n",(unsigned char *)caTmp,iLen);
	
	ZTTlv_Destroy(p_Ctrl);

	return 0;
}