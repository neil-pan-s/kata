#ifndef __OPENSSL_INTERFACE_H__
#define	__OPENSSL_INTERFACE_H__

#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/x509v3.h>
#include <openssl/x509.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/asn1.h>
#include <openssl/objects.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <openssl/md4.h>
#include <openssl/des.h>
#include <openssl/aes.h>

#ifndef OPENSSL_NO_ENGINE
#include <openssl/engine.h>
#endif

#define RSA_DEFAULT_PRIKEY_FILE  "./RSA_Pri_Key.pem"
#define RSA_DEFAULT_PUBKEY_FILE  "./RSA_Pub_Key.pem"
#define RSA_DEFAULT_CERT_FILE  "./RSA_Cert.pem"
#define RSA_DEFAULT_CSR_FILE  "./RSA_Csr.pem"

#define RSA_DEFAULT_ROOT_PRIKEY_FILE  "./RSA_Root_Pri_Key.pem"
#define RSA_DEFAULT_ROOT_PUBKEY_FILE  "./RSA_Root_Pub_Key.pem"
#define RSA_DEFAULT_ROOT_CERT_FILE  "./RSA_Root_Cert.pem"
#define RSA_DEFAULT_ROOT_CSR_FILE  "./RSA_Root_Csr.pem"

#define RSA_DEFAULT_ERROR_FILE "./RSA_Error.log"	//内存泄露日志

//证书信息解析指令 openssl x509 -in RSA_Cert.pem -text 

//证书请求文件信息结构
typedef struct 
{
	int  iSerial;	//证书序列号
	int  iDays;		//有效日期
	int  iVersion;	//版本信息
	char caStateName[72];	//State or Province Name (full name)
	char caLocalityName[72];	//eg, city
	char caCommonName[72];	//eg, YOUR name
	char caCountryName[2+1]; //缩写 两字节 eg. CN
	char caOrganizationName[72];	//eg, company
	char caOrganizationalUnitName[72];	//eg, section
	char caEmail[72];	//Email Address
	char caChallengePWD[72]; //A challenge password 暂不支持
	char caOptionalName[72]; //An optional company name  暂不支持
}CERT_INFO;

/*外部接口*/

int ZT_SSL_Init();
int ZT_SSL_Clear();


//RSA 
int ZT_Generate_RSA(int p_iBits,unsigned long p_lE,RSA * p_RSA);
int ZT_Rsa2Pem(RSA * p_RSA,char *p_caPriPemPath,char *p_caPubPemPath);
int ZT_PubPem2Rsa(RSA ** po_RSA,char *p_caPubPemPath);
int ZT_PriPem2Rsa(RSA ** po_RSA,char *p_caPriPemPath);
int ZT_PriPem2PKey(char *p_caPriCertPath,	EVP_PKEY **po_PriKey);
int ZT_PubPem2PKey(char *p_caPubCertPath,	EVP_PKEY **po_PubKey);
int ZT_Make_Cert(EVP_PKEY * p_APKey,EVP_PKEY * p_BPKey,CERT_INFO *p_CertInfo,char *p_caCertPemPath,char * p_caAPubCertPemPath);
int ZT_Make_Req(EVP_PKEY *p_Key,CERT_INFO * pCertInfo,char *p_caReqPemPath);
int ZT_RSA_Sign(EVP_PKEY *p_Key,unsigned char *pi_caData,int pi_iDataLen,unsigned char *po_caSig,int * po_iSigLen);
int ZT_RSA_SignVerify(EVP_PKEY *p_Key,unsigned char *pi_caData,int pi_iDataLen,unsigned char *pi_caSig,int pi_iSigLen);
int ZT_Verify_Cert(char *p_caCertAPemPath,char *p_caCertBPemPath);

int ZT_RSA_PriEncrypt(RSA * p_RSA,int p_iPadding,char * pi_caData,char *po_caEData);
int ZT_RSA_PubDecrypt(RSA * p_RSA,int p_iPadding,char * po_caData,char *pi_caEData);
int ZT_RSA_PriDecrypt(RSA * p_RSA,int p_iPadding,char * po_caData,char *pi_caEData);
int ZT_RSA_PubEncrypt(RSA * p_RSA,int p_iPadding,char * pi_caData,char *po_caEData);

int ZT_Pkey2Rsa(EVP_PKEY * p_Pkey,RSA ** po_RSA);
int ZT_Rsa2Pkey(RSA * p_RSA,EVP_PKEY ** po_Pkey);

//Sha1
int ZT_File2Sha1(char * p_caFileName,unsigned char *po_caHash);

//Md5 
int ZT_MD5(unsigned char * pi_caData,int pi_iDataLen,char * po_caMd5);

//Base64 
int ZT_Base64Decode(unsigned char * pi_caBase64,int pi_iBase64Len,unsigned char * po_caData,int * po_iDataLen);
int ZT_Base64Encode(unsigned char * pi_caData,int pi_iDataLen,unsigned char * po_caBase64,int * po_iBase64Len);

//DES
int ZT_Generate_Des(unsigned char * po_caDesKey);
int ZT_CBC_Des(unsigned char * pi_caKey,unsigned char * pi_caVector,unsigned char * pi_caIn,int pi_iInLen,unsigned char * po_caOut,int pi_iMode );
int ZT_CBC_3Des(unsigned char * pi_caKey,unsigned char * pi_caVector,unsigned char * pi_caIn,int pi_iInLen,unsigned char * po_caOut,int pi_iMode );
int ZT_ECB_Des(unsigned char * pi_caKey,unsigned char * pi_caIn,unsigned char * po_caOut,int pi_iMode );
int ZT_ECB_3Des(unsigned char * pi_caKey,unsigned char * pi_caIn,unsigned char * po_caOut,int pi_iMode );

//AES 
int ZT_CBC_AES(unsigned char* pi_caKey,unsigned char* pi_caVec,unsigned char* pi_caIn,int pi_iInLen, unsigned char* po_caOut,int pi_iMode);
int ZT_ECB_AES(unsigned char* pi_caKey,unsigned char* pi_caIn, unsigned char* po_caOut,int pi_iMode);

#endif