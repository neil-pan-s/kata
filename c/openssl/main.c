/* 
* @Author: Administrator
* @Date:   2015-03-12 15:42:07
* @Last Modified by:   ChangingP
* @Last Modified time: 2015-03-26 02:09:31
*/


#include <stdio.h>
#include <string.h>
#include <memory.h>

#include "openssl_interface.h"

int main()
{
	int bits = 2048,iRet = 0,iLen = 0;
	unsigned long e=RSA_3;	
	RSA *g_pARSA = NULL,*g_pBRSA = NULL;
	EVP_PKEY *g_pAKey = NULL,*g_pBKey = NULL;
	CERT_INFO g_RootCertInfo;
	CERT_INFO g_CertInfo;

	char caTmp[4096]={0};

	memset(&g_CertInfo,0,sizeof(CERT_INFO));
	memset(&g_RootCertInfo,0,sizeof(CERT_INFO));

	//配置根证书信息
	g_RootCertInfo.iSerial = 1;
	g_RootCertInfo.iDays = 365;
	g_RootCertInfo.iVersion = 1;
	strcpy(g_RootCertInfo.caCountryName,"CN");	
	strcpy(g_RootCertInfo.caStateName,"GuangDong");
	strcpy(g_RootCertInfo.caLocalityName,"ShenZhen");
	strcpy(g_RootCertInfo.caCommonName,"Szzt CA Auth");
	strcpy(g_RootCertInfo.caOrganizationName,"SZZT ELECTORNIC CO.Ltd");
	strcpy(g_RootCertInfo.caOrganizationalUnitName,"SZZT ELECTORNIC CO.Ltd");
	strcpy(g_RootCertInfo.caEmail,"panquanjin@szzt.com.cn");

	//配置用户证书信息
	g_CertInfo.iSerial = 1;
	g_CertInfo.iDays = 365;
	g_CertInfo.iVersion = 1;
	strcpy(g_CertInfo.caCountryName,"CN");	
	strcpy(g_CertInfo.caStateName,"GuangDong");
	strcpy(g_CertInfo.caLocalityName,"ShenZhen");
	strcpy(g_CertInfo.caCommonName,"Szzt Pos");
	strcpy(g_CertInfo.caOrganizationName,"SZZT ELECTORNIC CO.Ltd");
	strcpy(g_CertInfo.caOrganizationalUnitName,"SZZT ELECTORNIC CO.Ltd");
	strcpy(g_CertInfo.caEmail,"panquanjin@szzt.com.cn");


	ZT_SSL_Init(); //must

	printf("---------------- %s -- %d -------------- \n",__func__,__LINE__);
	/*************************************　生成 Root RSA Start ********************************/ 

	g_pARSA = RSA_new();
	printf("---------------- %s -- %d -------------- g_pARSA =%p \n",__func__,__LINE__,g_pARSA);

	//生成RSA秘钥对
	ZT_Generate_RSA(bits,e,g_pARSA);
	printf("---------------- %s -- %d -------------- g_pARSA =%p \n",__func__,__LINE__,g_pARSA);

	if(g_pARSA == NULL)
	{
		return -1;
	}	

	//生成RSA秘钥 存储到文件
	iRet = ZT_Rsa2Pem(g_pARSA,RSA_DEFAULT_ROOT_PRIKEY_FILE,RSA_DEFAULT_ROOT_PUBKEY_FILE);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);
	RSA_free(g_pARSA);

	g_pARSA = NULL;
	//从文件读取RSA结构公钥
	ZT_PubPem2Rsa(&g_pARSA,RSA_DEFAULT_ROOT_PUBKEY_FILE);
	RSA_free(g_pARSA);

	g_pARSA = NULL;
	//从文件读取RSA结构私钥
	ZT_PriPem2Rsa(&g_pARSA,RSA_DEFAULT_ROOT_PRIKEY_FILE);
	RSA_free(g_pARSA);

	g_pAKey = NULL;
	//从文件读取 EVP_PKEY 结构私钥
	iRet = ZT_PriPem2PKey(RSA_DEFAULT_ROOT_PRIKEY_FILE,&g_pAKey);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);
	//EVP_PKEY_free(g_pAKey);		//生成CSR CERT 需要使用此 私钥EVP_PKEY 暂不释放

	// 生成证书请求文件
	iRet = ZT_Make_Req(g_pAKey,&g_RootCertInfo,RSA_DEFAULT_ROOT_CSR_FILE);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);
	//EVP_PKEY_free(g_pAKey);
	
	// 生成自签名证书
	iRet = ZT_Make_Cert(g_pAKey,g_pAKey,&g_RootCertInfo,RSA_DEFAULT_ROOT_CERT_FILE,NULL);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);
	EVP_PKEY_free(g_pAKey);
	
	g_pAKey = NULL;
	//从证书文件读取 EVP_PKEY 结构公钥
	iRet = ZT_PubPem2PKey(RSA_DEFAULT_ROOT_CERT_FILE,&g_pAKey);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);
	EVP_PKEY_free(g_pAKey);

	printf("---------------- %s -- %d -------------- \n",__func__,__LINE__);

	/*************************************　生成 Root RSA End ********************************/ 

	/*************************************　生成 User RSA Start ********************************/ 
	
	g_pBRSA = RSA_new();

	//生成RSA秘钥对
	ZT_Generate_RSA(bits,e,g_pBRSA);
	printf("---------------- %s -- %d -------------- g_pBRSA =%p \n",__func__,__LINE__,g_pBRSA);

	if(g_pBRSA == NULL)
	{
		return -1;
	}	


	//生成RSA秘钥 存储到文件
	iRet = ZT_Rsa2Pem(g_pBRSA,NULL,NULL);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);
	RSA_free(g_pBRSA);

	g_pBKey = NULL;
	//从文件读取 EVP_PKEY 结构私钥
	iRet = ZT_PriPem2PKey(RSA_DEFAULT_PRIKEY_FILE,&g_pBKey);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);
	//EVP_PKEY_free(g_pBKey);		//生成CSR CERT 需要使用此 私钥EVP_PKEY 暂不释放

	// 生成证书请求文件
	iRet = ZT_Make_Req(g_pBKey,&g_CertInfo,NULL);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);

	g_pAKey = NULL;
	//从文件读取 EVP_PKEY 结构私钥
	iRet = ZT_PriPem2PKey(RSA_DEFAULT_ROOT_PRIKEY_FILE,&g_pAKey);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);
	//EVP_PKEY_free(g_pAKey);		//生成CSR CERT 需要使用此 私钥EVP_PKEY 暂不释放

	// 生成证书文件
	iRet = ZT_Make_Cert(g_pAKey,g_pBKey,&g_CertInfo,NULL,RSA_DEFAULT_ROOT_CERT_FILE);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);
	EVP_PKEY_free(g_pAKey);
	EVP_PKEY_free(g_pBKey);

	/*************************************　生成 User RSA End ********************************/ 

	//证书验签
	iRet = ZT_Verify_Cert(RSA_DEFAULT_ROOT_CERT_FILE,RSA_DEFAULT_CERT_FILE);
	printf("---------------- %s -- %d -------------- ZT_Verify_Cert =%d \n",__func__,__LINE__,iRet);

	g_pBKey = NULL;
	//从文件读取 EVP_PKEY 结构私钥
	iRet = ZT_PriPem2PKey(RSA_DEFAULT_PRIKEY_FILE,&g_pBKey);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);
	//EVP_PKEY_free(g_pBKey);		//后续操作需要使用此 私钥EVP_PKEY 暂不释放

	iRet = ZT_RSA_Sign(g_pBKey,"hello world",strlen("hello world"),caTmp,&iLen);
	EVP_PKEY_free (g_pBKey);
	printf("---------------- %s -- %d -------------- ZT_RSA_Sign = %d\n",__func__,__LINE__,iRet);

	g_pBKey = NULL;
	iRet = ZT_PubPem2PKey(RSA_DEFAULT_CERT_FILE,&g_pBKey);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);
	//EVP_PKEY_free(g_pBKey);		//后续操作需要使用此 私钥EVP_PKEY 暂不释放

	iRet = ZT_RSA_SignVerify(g_pBKey,"hello world",strlen("hello world"),caTmp,iLen);
	EVP_PKEY_free (g_pBKey);	
	printf("---------------- %s -- %d -------------- ZT_RSA_SignVerify = %d\n",__func__,__LINE__,iRet);

	/*************************************　公私钥 加解密  ********************************/ 

	char caRSAData[4096]={0},caRSAEData[4096]={0};

	g_pARSA = NULL;
	//从文件读取 RSA 结构私钥
	iRet = ZT_PriPem2Rsa(&g_pARSA,RSA_DEFAULT_PRIKEY_FILE);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);

	g_pBKey = NULL;
	iRet = ZT_PubPem2PKey(RSA_DEFAULT_CERT_FILE,&g_pBKey);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);

	ZT_Pkey2Rsa(g_pBKey,&g_pBRSA);

	//私钥加密 
	strcpy(caRSAData,"1111111111111111111111111111111111111111111111");
	ZT_RSA_PriEncrypt(g_pARSA,RSA_PKCS1_PADDING,caRSAData,caRSAEData);

	//公钥解密 
	memset(caRSAData,0,sizeof(caRSAData));
	ZT_RSA_PubDecrypt(g_pBRSA,RSA_PKCS1_PADDING,caRSAData,caRSAEData);

	memset(caRSAData,0,sizeof(caRSAData));
	strcpy(caRSAData,"222222222222222222222222222222222222222222222222");

	//公钥加密 
	ZT_RSA_PubEncrypt(g_pBRSA,RSA_PKCS1_PADDING,caRSAData,caRSAEData);

	//私钥解密
	memset(caRSAData,0,sizeof(caRSAData));
	ZT_RSA_PriDecrypt(g_pARSA,RSA_PKCS1_PADDING,caRSAData,caRSAEData);

	RSA_free(g_pARSA);
	EVP_PKEY_free(g_pBKey);

	/*************************************　公私钥 加解密  ********************************/ 


	unsigned char caData[512]={0},caBase64[1024]={0};
	int iDataLen = 0,iBase64Len = 0;

	strcpy(caData,"123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"); 

	ZT_Base64Encode(caData,strlen(caData),caBase64,&iBase64Len);

	memset(caData,0,sizeof(caData));
	ZT_Base64Decode(caBase64,iBase64Len,caData,&iDataLen);

	char caMd5[24]={0};
	ZT_MD5(caData,strlen(caData),caMd5);


	char caKey[33] = "\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x00";
	char caVector[17] = "\x33\x33\x33\x33\x33\x33\x33\x33\x33\x33\x33\x33\x33\x33\x33\x33\x00";
	char caIn[33] = "\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x00";
	char caOut[124]={0};

	//3倍长密钥
	char ca3DesKey[33] = "\x11\x11\x11\x11\x11\x11\x11\x11\x22\x22\x22\x22\x22\x22\x22\x22\x33\x33\x33\x33\x33\x33\x33\x33\x00";
	//2倍长密钥
	char ca3DesKey1[33] = "\x11\x11\x11\x11\x11\x11\x11\x11\x22\x22\x22\x22\x22\x22\x22\x22\x00\x00\x00\x00\x00\x00\x00\x00\x00";

	//3倍长密钥 3DES CBC
	ZT_CBC_3Des(ca3DesKey,caVector,caIn,32,caOut,DES_ENCRYPT);
	memset(caIn,0,sizeof(caIn));
	ZT_CBC_3Des(ca3DesKey,caVector,caOut,32,caIn,DES_DECRYPT);

	//2倍长密钥 3DES CBC
	memset(caOut,0,sizeof(caOut));
	ZT_CBC_3Des(ca3DesKey1,caVector,caIn,32,caOut,DES_ENCRYPT);
	memset(caIn,0,sizeof(caIn));
	ZT_CBC_3Des(ca3DesKey1,caVector,caOut,32,caIn,DES_DECRYPT);

	//3倍长密钥 3DES ECB
	memset(caOut,0,sizeof(caOut));
	ZT_ECB_3Des(ca3DesKey,caIn,caOut,DES_ENCRYPT);
	memset(caIn,0,sizeof(caIn));
	ZT_ECB_3Des(ca3DesKey,caOut,caIn,DES_DECRYPT);

	//2倍长密钥 3DES ECB 
	memset(caOut,0,sizeof(caOut));
	ZT_ECB_3Des(ca3DesKey1,caIn,caOut,DES_ENCRYPT);
	memset(caIn,0,sizeof(caIn));
	ZT_ECB_3Des(ca3DesKey1,caOut,caIn,DES_DECRYPT);


	ZT_CBC_Des(caKey,caVector,caIn,32,caOut,DES_ENCRYPT);
	memset(caIn,0,sizeof(caIn));
	ZT_CBC_Des(caKey,caVector,caOut,32,caIn,DES_DECRYPT);

	memset(caOut,0,sizeof(caOut));
	ZT_ECB_Des(caKey,caIn,caOut,DES_ENCRYPT);
	memset(caIn,0,sizeof(caIn));
	ZT_ECB_Des(caKey,caOut,caIn,DES_DECRYPT);


	char caDes[124]={0};
	ZT_Generate_Des(caDes);

	char caAesIn[124]={0};
	char caAesOut[256]={0};
	char caAesVec[17]={0};
	char caAesKey[17]={0};

	memcpy(caAesIn,"\x12\x34\x56\x78\x90\x12\x34\x56\x78\x90\x12\x34\x56\x78\x90\x12\x34\x56\x78\x90\x12\x34\x56\x78\x90\x12\x34\x56\x78\x90\x12\x34",32);
	memcpy(caAesKey,"\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11",16);
	iRet = ZT_CBC_AES(caAesKey,caAesVec,caAesIn,strlen(caAesIn), caAesOut,AES_ENCRYPT);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);

	memset(caAesIn,0,sizeof(caAesIn));
	iRet = ZT_CBC_AES(caAesKey,caAesVec,caAesOut,strlen(caAesOut), caAesIn,AES_DECRYPT);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);

	memset(caAesOut,0,sizeof(caAesOut));
	iRet = ZT_ECB_AES(caAesKey,caAesIn,caAesOut,AES_ENCRYPT);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);

	memset(caAesIn,0,sizeof(caAesIn));
	iRet = ZT_ECB_AES(caAesKey,caAesOut,caAesIn,AES_DECRYPT);
	printf("---------------- %s -- %d -------------- iRet =%d \n",__func__,__LINE__,iRet);

	ZT_SSL_Clear();  //must

	return 0;
}