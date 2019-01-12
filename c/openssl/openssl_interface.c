/* Certificate creation. Demonstrates some certificate related
 * operations.
 */


#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
 
#include "openssl_interface.h"

static 	BIO * g_BIOErr = NULL;	//用于记录内存泄露信息

/*
	SSL 初始化接口
	用于开启内存记录等功能 防止内存泄露 
	调试模式泄露信息记录到 RSA_DEFAULT_ERROR_FILE
 */
int ZT_SSL_Init()
{
	CRYPTO_malloc_debug_init();
	CRYPTO_set_mem_debug_options(V_CRYPTO_MDEBUG_ALL);

	//开启控制内存分配，记录内存信息
	CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);
	OpenSSL_add_all_algorithms();

	if(g_BIOErr == NULL)
	{	
#ifdef ZT_DEBUG					
		g_BIOErr = BIO_new_fp(stderr, BIO_NOCLOSE);
		//g_BIOErr = BIO_new_file(RSA_DEFAULT_ERROR_FILE, "w+");
#endif		
	}

	return 0;
}


/*
	SSL 关闭清理接口
	用于调用结束后 清理泄露的内存
 */
int ZT_SSL_Clear()
{
	//关闭内存记录
	//CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_OFF);

	CONF_modules_unload(1);        //for conf
	EVP_cleanup();                 //For EVP
	//ENGINE_cleanup();              //for engine

	//清除可能的泄露内存
	CRYPTO_cleanup_all_ex_data();

	ERR_remove_state(0);           //for ERR
	ERR_free_strings();            //for ERR

	if(g_BIOErr != NULL)
	{	
		//记录泄露内存到文件
		CRYPTO_mem_leaks(g_BIOErr);
		BIO_free(g_BIOErr);
	}
	g_BIOErr = NULL;
	return 0;

}


/*
	回调函数
 */
static void ZT_Callback(int p, int n, void *arg)
{
	char c = 'B';

	if (p == 0) c = '.';
	if (p == 1) c = '+';
	if (p == 2) c = '*';
	if (p == 3) c = '\n';
	fputc(c, stderr);
}

static int ZT_PrintHex(char * p_caMsg,unsigned char * p_caData,int p_iLen)
{
	int i = 0;
	char caBuff[1024]={0},caTmp[124]={0},caTmp1[4]={0};

	//增加说明信息
	sprintf(caTmp,"{%s}",p_caMsg);
	strcat(caBuff,caTmp);

	//增加16进制数据
	for(i = 0; i < p_iLen; i++)
	{
		memset(caTmp1,0,sizeof(caTmp1));
		sprintf(caTmp1, "%02X", p_caData[i]);
		strcat(caBuff,caTmp1);
	}

	strcat(caBuff,"\r\n");

	printf("%s\n",caBuff);

	return 0;
}


/*
	生成RSA秘钥对[此接口弃用]
	# p_iBits 秘钥位数 默认2048
	# p_lE  指数  默认RSA_3
		RSA_3  = 0x3L
		RSA_F4 = 0x10001L
	# po_RSA 秘钥结构出口参数	
 */
int ZT_Generate_RSA_key(int p_iBits,unsigned long p_lE,RSA ** po_RSA)
{
	int bits=2048;
	unsigned long e=RSA_3;
	RSA * r = NULL;

	if(p_iBits > 512)
	{
		bits = p_iBits;
	}

	if(p_lE == RSA_F4)
	{
		e=p_lE;
	}	

	//函数原型 RSA *RSA_generate_key(int bits, unsigned long e_value,void (*callback)(int,int,void *), void *cb_arg)
	//bits 是模数比特数，e_value 是公钥指数e，
	//callback 回调函数由用户实现，用于干预密钥生成过程中的一些运算，可为空。
	r =RSA_generate_key(bits,e,NULL,NULL);  //此函数已经弃用
	if(r != NULL)
	{

#ifdef ZT_DEBUG		
		//------------------------------
		RSA_print_fp(stdout,r,11);  //打印出RSA信息
		//------------------------------
#endif		
		*po_RSA = r;

	}else{
		*po_RSA = NULL;
		printf("-- %s -- %d -- RSA_generate_key Error\n",__func__,__LINE__);
		return -1;
	}	

	return 0;
}



/*
	生成RSA秘钥对
	# p_iBits 秘钥位数 默认2048
	# p_lE  指数  默认RSA_3
		RSA_3  = 0x3L
		RSA_F4 = 0x10001L
	# p_RSA 秘钥结构参数	
 */
int ZT_Generate_RSA(int p_iBits,unsigned long p_lE,RSA * p_RSA)
{
	int bits=2048 ,iRet = 0;
	unsigned long e=RSA_3;
	BIGNUM *bne = NULL;

	if(p_iBits > 512)
	{
		bits = p_iBits;
	}

	if(p_lE == RSA_F4)
	{
		e=p_lE;
	}	

	if(p_RSA == NULL)
	{
		return -2;
	}	

	bne=BN_new();
	BN_set_word(bne,e);

	//函数原型 int RSA_generate_key_ex(RSA *rsa, int bits, BIGNUM *e, BN_GENCB *cb);
	//bits 是模数比特数，e 是公钥指数，
	//cb 回调函数由用户实现，用于干预密钥生成过程中的一些运算，可为空。
	iRet =RSA_generate_key_ex(p_RSA,bits,bne,NULL);
	if(iRet == 1)
	{

#ifdef ZT_DEBUG		
		//------------------------------
		RSA_print_fp(stdout,p_RSA,11);  //打印出RSA信息
		//------------------------------
#endif		
		BN_free(bne);
	}else{
		BN_free(bne);
		p_RSA = NULL;
		return -1;
	}	

	return 0;
}

/*
	公私钥存储到文件
	# p_RSA RSA秘钥对结构
	# p_caPriPemPath 私钥文件名 	默认 RSA_DEFAULT_PRIKEY_FILE
	# p_caPubPemPath 公钥文件名 	默认 RSA_DEFAULT_PUBKEY_FILE
 */
int ZT_Rsa2Pem(RSA * p_RSA,char *p_caPriPemPath,char *p_caPubPemPath)
{
	int ret = 0;
	BIO * out = NULL;
	RSA * r = NULL;

	char caPriPath[124]={0};
	char caPubPath[124]={0};

	if(p_RSA == NULL)
	{	
		return -1;
	}	

	r = p_RSA;

	memset(caPriPath,0,sizeof(caPriPath));
	if( (p_caPriPemPath != NULL) && (strlen(p_caPriPemPath)>0))
	{
		sprintf(caPriPath,"%.124s",p_caPriPemPath);
	}else{
		sprintf(caPriPath,"%.124s",RSA_DEFAULT_PRIKEY_FILE);
	}

	memset(caPubPath,0,sizeof(caPubPath));
	if( (p_caPubPemPath != NULL) && (strlen(p_caPubPemPath)>0))
	{
		sprintf(caPubPath,"%.124s",p_caPubPemPath);
	}else{
		sprintf(caPubPath,"%.124s",RSA_DEFAULT_PUBKEY_FILE);
	}	
	
#ifdef ZT_DEBUG			
	printf("---------------- %s -- %d -------------- \n",__func__,__LINE__);
	RSA_print_fp(stdout,p_RSA,11);
	printf("---------------- %s -- %d -------------- \n",__func__,__LINE__);
#endif

	out = BIO_new_file(caPriPath, "w");
	ret = PEM_write_bio_RSAPrivateKey(out, r, NULL, NULL, 0, NULL, NULL);
	if (ret != 1)
	{
		BIO_free(out);
		return -2;
	}
	BIO_flush(out);
	BIO_free(out);

	out = BIO_new_file(caPubPath, "w");
	ret = PEM_write_bio_RSAPublicKey(out, r);
	if (ret != 1)
	{
		BIO_free(out);
		return -3;
	}
	BIO_flush(out);
	BIO_free(out);

	return 0;
}


/*
	从文件读取公私钥
	# po_RSA RSA秘钥对结构 
	# p_caPriPemPath 私钥文件名 	默认 RSA_DEFAULT_PRIKEY_FILE 读取的私钥结构中 可以得到公钥
	调用此接口传出 po_RSA 结构, 需要调用 RSA_free() 释放 否则会有内存泄露
 */
int ZT_PriPem2Rsa(RSA ** po_RSA,char *p_caPriPemPath)
{
	BIO * out = NULL;
	RSA * r = NULL;

	char caPriPath[124]={0};


	if(po_RSA == NULL)
	{	
		return -1;
	}	

	//传入非空指针 会导致数据不变
	//p_RSA = NULL; 		

	memset(caPriPath,0,sizeof(caPriPath));
	if( (p_caPriPemPath != NULL) && (strlen(p_caPriPemPath)>0))
	{
		sprintf(caPriPath,"%.124s",p_caPriPemPath);
		out = BIO_new_file(caPriPath, "rb");
		r = PEM_read_bio_RSAPrivateKey(out,NULL, NULL, NULL);
		if (r == NULL)
		{
			BIO_free(out);
			return -2;
		}
		BIO_flush(out);
		BIO_free(out);

#ifdef ZT_DEBUG			
	printf("---------------- %s -- %d -------------- \n",__func__,__LINE__);
	if(r->d != NULL) //数据非空判断 
	{
		RSA_print_fp(stdout,r,11);
	}
	printf("---------------- %s -- %d -------------- \n",__func__,__LINE__);
#endif
		//传出RSA数据
		*po_RSA = r;
	}else{
		return -3;
	}

	return 0;
}

/*
	从文件读取公私钥
	# po_RSA RSA秘钥对结构
	# p_caPubPemPath 公钥文件名 	默认 RSA_DEFAULT_PUBKEY_FILE
	调用此接口传出 po_RSA 结构, 需要调用 RSA_free() 释放 否则会有内存泄露
 */
int ZT_PubPem2Rsa(RSA ** po_RSA,char *p_caPubPemPath)
{
	BIO * out = NULL;
	RSA * r = NULL;

	char caPubPath[124]={0};


	if(po_RSA == NULL)
	{	
		return -1;
	}	

	//传入非空指针 会导致数据不变
	//p_RSA = NULL; 		

	memset(caPubPath,0,sizeof(caPubPath));
	if( (p_caPubPemPath != NULL) && (strlen(p_caPubPemPath)>0))
	{		
		sprintf(caPubPath,"%.124s",p_caPubPemPath);
		out = BIO_new_file(caPubPath, "rb");
		r = PEM_read_bio_RSAPublicKey(out, NULL,NULL,NULL);
		if (r == NULL)
		{
			BIO_free(out);
			return -3;
		}
		BIO_flush(out);
		BIO_free(out);
#ifdef ZT_DEBUG			
	printf("---------------- %s -- %d -------------- \n",__func__,__LINE__);
	//if(r->d != NULL) //数据非空判断  
	{
		RSA_print_fp(stdout,r,11);
	}
	printf("---------------- %s -- %d -------------- \n",__func__,__LINE__);
#endif		
		//传出RSA数据
		*po_RSA = r;
	}else{
		return -3;
	}

	return 0;
}

/* Add extension using V3 code: we can set the config file as NULL
 * because we wont reference any other sections.
 */

static int ZT_MakeCert_Add_Ext(X509 *cert, int nid, char *value)
{
	X509_EXTENSION *ex;
	X509V3_CTX ctx;
	/* This sets the 'context' of the extensions. */
	/* No configuration database */
	X509V3_set_ctx_nodb(&ctx);
	/* Issuer and subject certs: both the target since it is self signed,
	 * no request and no CRL
	 */
	X509V3_set_ctx(&ctx, cert, cert, NULL, NULL, 0);
	ex = X509V3_EXT_conf_nid(NULL, &ctx, nid, value);
	if (!ex)
		return 0;

	X509_add_ext(cert, ex, -1);
	X509_EXTENSION_free(ex);
	return 1;
}


static int ZT_MakeCert_1(EVP_PKEY * p_APKey,EVP_PKEY * p_BPKey,X509 **x509p,CERT_INFO * pCertInfo,X509 * pAPubCert)
{
	X509 *x = NULL;
	EVP_PKEY *pkA = NULL,*pkB = NULL;
	RSA * rsa = NULL;
	X509_NAME *name = NULL;

	if(pCertInfo == NULL)
	{
		return -1;
	}

	if(p_APKey != p_BPKey)	//非自签名证书 必须要上级公钥证书
	{
		if(pAPubCert == NULL)
		{
			return -2;
		}
	}	

	if(p_APKey == NULL )
	{
		return -3;
	}	

	if(p_BPKey == NULL )
	{
		return -3;
	}	

	pkA = p_APKey;
	pkB = p_BPKey;

	if ((x509p == NULL) || (*x509p == NULL))
	{
		if ((x = X509_new()) == NULL)
			goto err;
	}
	else
		x = *x509p;

	// RSA_print_fp(stdout, pkA->pkey.rsa, 0);
	// printf("---------------- %s -- %d -------------- \n",__func__,__LINE__);

	X509_set_version(x, pCertInfo->iVersion);
	ASN1_INTEGER_set(X509_get_serialNumber(x), pCertInfo->iSerial);
	X509_gmtime_adj(X509_get_notBefore(x), 0);
	X509_gmtime_adj(X509_get_notAfter(x), (long)60 * 60 * 24 * (pCertInfo->iDays));


	//设置 p_BRSA 公钥到证书
	X509_set_pubkey(x, pkB);

	name = X509_get_subject_name(x);

	/* This function creates and adds the entry, working out the
	 * correct string type and performing checks on its length.
	 * Normally we'd check the return value for errors...
	 */
	X509_NAME_add_entry_by_txt(name, "C",MBSTRING_ASC, pCertInfo->caCountryName , -1, -1, 0);
	X509_NAME_add_entry_by_txt(name, "CN",MBSTRING_ASC, pCertInfo->caCommonName , -1, -1, 0);

	X509_NAME_add_entry_by_txt(name,LN_organizationName,MBSTRING_ASC,pCertInfo->caOrganizationName,-1,-1,0);

	X509_NAME_add_entry_by_txt(name,LN_organizationalUnitName,MBSTRING_ASC,pCertInfo->caOrganizationalUnitName, -1,-1,0);

	X509_NAME_add_entry_by_txt(name,LN_stateOrProvinceName,MBSTRING_ASC,pCertInfo->caStateName,-1,-1,0);

	X509_NAME_add_entry_by_txt(name,LN_localityName,MBSTRING_ASC,pCertInfo->caLocalityName, -1,-1,0);

	X509_NAME_add_entry_by_txt(name,LN_pkcs9_emailAddress,MBSTRING_ASC,pCertInfo->caEmail, -1,-1,0);

	if(p_APKey == p_BPKey)  //自签名证书
	{	
		/* Its self signed so set the issuer name to be the same as the
		 * subject.
		 */		
		X509_set_issuer_name(x, name);
	}else{
		X509_set_issuer_name(x,pAPubCert->cert_info->subject);
	}

	/* Add various extensions: standard extensions */
	ZT_MakeCert_Add_Ext(x, NID_basic_constraints, "critical,CA:TRUE");
	ZT_MakeCert_Add_Ext(x, NID_key_usage, "critical,keyCertSign,cRLSign");

	ZT_MakeCert_Add_Ext(x, NID_subject_key_identifier, "hash");

// 	/* Some Netscape specific extensions */
// 	// ZT_MakeCert_Add_Ext(x, NID_netscape_cert_type, "sslCA");

// 	// ZT_MakeCert_Add_Ext(x, NID_netscape_comment, "example comment extension");


// #ifdef CUSTOM_EXT
// 	/* Maybe even add our own extension based on existing */
// 	{
// 		int nid;
// 		nid = OBJ_create("1.2.3.4", "MyAlias", "My Test Alias Extension");
// 		X509V3_EXT_add_alias(nid, NID_netscape_comment);
// 		ZT_MkCert_Add_Ext(x, nid, "example comment alias");
// 	}
// #endif

	// X509_print_fp(stdout, x);
	// printf("---------------- %s -- %d -------------- \n",__func__,__LINE__);

	// RSA_print_fp(stdout, pkA->pkey.rsa, 0);
	// printf("---------------- %s -- %d -------------- \n",__func__,__LINE__);

	if (!X509_sign(x, pkA, EVP_sha1()))
		goto err;

	*x509p = x;
	return (1);
err:
	*x509p = x;
	return (0);
}

/*
	证书生成
	# p_APKey A级密钥结构 提供私钥对证书进行签名 
	# p_BPKey B级密钥结构 提供公钥生成证书
	# p_CertInfo 证书信息结构 
	# p_caCertPemPath 生成证书名
	# p_caAPubCertPemPath A级密钥公钥证书文件  用于生成非自签名证书时 提取公钥ISSUER 发行者信息 自签名证书保留为空

	PS: 自签名证书 只需要传入同一个密钥结构即可 即 p_APKey = p_BPKey
 */
int ZT_Make_Cert(EVP_PKEY * p_APKey,EVP_PKEY * p_BPKey,CERT_INFO *p_CertInfo,char *p_caCertPemPath,char * p_caAPubCertPemPath)
{
	int iRet = 0;
	X509 *x509 = NULL,*pAPubCert = NULL;
	EVP_PKEY *pkey = NULL;
	FILE *fp = NULL,*fpA = NULL;

	if((p_APKey == NULL) || (p_BPKey == NULL))
	{
		return -1;
	}

	if(p_CertInfo == NULL)
	{
		return -1;
	}	

	if(p_APKey != p_BPKey)	//非自签名证书 必须要上级公钥证书
	{
		if(p_caAPubCertPemPath == NULL)
		{
			return -2;
		}

		fpA = fopen (p_caAPubCertPemPath, "r");
		if (fpA == NULL) return -1;
		pAPubCert = PEM_read_X509(fpA, NULL, NULL, NULL);
		fclose (fpA);

		if (pAPubCert == NULL) {
			ERR_print_errors_fp (stderr);
			return -2;
		}

	}		

	iRet = ZT_MakeCert_1(p_APKey,p_BPKey,&x509,p_CertInfo,pAPubCert);
	if(iRet != 1)
	{
		X509_free(x509);
		X509_free(pAPubCert);		
		return -3;
	}	

#ifdef ZT_DEBUG
	X509_print_fp(stdout, x509);
#endif

	if((p_caCertPemPath != NULL) && (strlen(p_caCertPemPath) > 0))
	{
		fp=fopen(p_caCertPemPath,"wb");
	}else{
		fp=fopen(RSA_DEFAULT_CERT_FILE,"wb");
	}

	if(fp == NULL)
	{
		X509_free(x509);
		X509_free(pAPubCert);			
		return -3;
	}

	PEM_write_X509(fp, x509);
	fclose(fp);

	X509_free(x509);
	X509_free(pAPubCert);

	return (0);
}

/* Add extension using V3 code: we can set the config file as NULL
 * because we wont reference any other sections.
 */
static int ZT_MakeReq_add_ext(STACK_OF(X509_EXTENSION) *sk, int nid, char *value)
{
	X509_EXTENSION *ex;
	ex = X509V3_EXT_conf_nid(NULL, NULL, nid, value);
	if (!ex)
		return 0;
	sk_X509_EXTENSION_push(sk, ex);

	return 1;
}


static int ZT_MakeReq_1(X509_REQ **req, EVP_PKEY **pkeyp, CERT_INFO * pCertInfo)
{
	X509_REQ *x = NULL;
	EVP_PKEY *pk = NULL;
	RSA *rsa = NULL;
	X509_NAME *name = NULL;
	STACK_OF(X509_EXTENSION) *exts = NULL;

	pk = *pkeyp;

	if ((x = X509_REQ_new()) == NULL)
		goto err;

	if(pCertInfo == NULL)
	{
		goto err;
	}	

	X509_REQ_set_pubkey(x, pk);

	name = X509_REQ_get_subject_name(x);

	/* This function creates and adds the entry, working out the
	 * correct string type and performing checks on its length.
	 * Normally we'd check the return value for errors...
	 */

	X509_NAME_add_entry_by_txt(name, "C",MBSTRING_ASC, pCertInfo->caCountryName , -1, -1, 0);
	X509_NAME_add_entry_by_txt(name, "CN",MBSTRING_ASC, pCertInfo->caCommonName , -1, -1, 0);

	X509_NAME_add_entry_by_txt(name,LN_organizationName,MBSTRING_ASC,pCertInfo->caOrganizationName,-1,-1,0);

	X509_NAME_add_entry_by_txt(name,LN_organizationalUnitName,MBSTRING_ASC,pCertInfo->caOrganizationalUnitName, -1,-1,0);

	X509_NAME_add_entry_by_txt(name,LN_stateOrProvinceName,MBSTRING_ASC,pCertInfo->caStateName,-1,-1,0);

	X509_NAME_add_entry_by_txt(name,LN_localityName,MBSTRING_ASC,pCertInfo->caLocalityName, -1,-1,0);

	X509_NAME_add_entry_by_txt(name,LN_pkcs9_emailAddress,MBSTRING_ASC,pCertInfo->caEmail, -1,-1,0);


#ifdef REQUEST_EXTENSIONS
	/* Certificate requests can contain extensions, which can be used
	 * to indicate the extensions the requestor would like added to
	 * their certificate. CAs might ignore them however or even choke
	 * if they are present.
	 */

	/* For request extensions they are all packed in a single attribute.
	 * We save them in a STACK and add them all at once later...
	 */

	exts = sk_X509_EXTENSION_new_null();
	/* Standard extenions */

	ZT_MakeReq_add_ext(exts, NID_key_usage, "critical,digitalSignature,keyEncipherment");

	/* This is a typical use for request extensions: requesting a value for
	 * subject alternative name.
	 */

	ZT_MakeReq_add_ext(exts, NID_subject_alt_name, "email:steve@openssl.org");

	/* Some Netscape specific extensions */
	ZT_MakeReq_add_ext(exts, NID_netscape_cert_type, "client,email");



// #ifdef CUSTOM_EXT
// 	/* Maybe even add our own extension based on existing */
// 	{
// 		int nid;
// 		nid = OBJ_create("1.2.3.4", "MyAlias", "My Test Alias Extension");
// 		X509V3_EXT_add_alias(nid, NID_netscape_comment);
// 		ZT_MakeReq_add_ext(x, nid, "example comment alias");
// 	}
// #endif

	/* Now we've created the extensions we add them to the request */

	X509_REQ_add_extensions(x, exts);

	sk_X509_EXTENSION_pop_free(exts, X509_EXTENSION_free);

#endif

	if (!X509_REQ_sign(x, pk, EVP_sha1()))
		goto err;

	*req = x;
	return (1);
err:
	*req = x;
	return (0);
}

/*
	证书申请文件生成
	# pkey 密钥结构 提供私钥进行签名 
	# pCertInfo 证书相关信息 提供 证书提供者信息
	# p_caReqPemPath 生成证书申请文件名
 */
int ZT_Make_Req(EVP_PKEY * pkey,CERT_INFO * pCertInfo,char *p_caReqPemPath)
{
	int iRet = 0;
	FILE *fp = NULL;
	X509_REQ *req = NULL;

	if(pkey == NULL)
	{
		return -1;
	}

	if(pCertInfo == NULL)
	{
		return -1;
	}	

	iRet = ZT_MakeReq_1(&req, &pkey, pCertInfo);
	if(iRet != 1 )
	{
		X509_REQ_free(req);		
		return -3;
	}	

#ifdef ZT_DEBUG
	RSA_print_fp(stdout, pkey->pkey.rsa, 0);
	X509_REQ_print_fp(stdout, req);
#endif


	if((p_caReqPemPath != NULL) && (strlen(p_caReqPemPath) > 0))
	{
		fp=fopen(p_caReqPemPath,"wb");
	}else{
		fp=fopen(RSA_DEFAULT_CSR_FILE,"wb");
	}

	if(fp == NULL)
	{
		X509_REQ_free(req);
		return -2;
	}	
	PEM_write_X509_REQ(fp, req);
	fclose(fp);

	X509_REQ_free(req);

	//释放此pKey 会导致 传入参数 p_RSA 被释放
	//不释放此pKey 会内存泄露 
	//EVP_PKEY_free(pkey);		

	return (0);
}



/*
	读取PEM私钥文件中私钥
	# p_caPriCertPath 私钥文件路径
	# po_PriKey EVP_PKEY私钥结构  
	调用此接口后 需要调用EVP_PKEY_free(pkey) 释放
 */
int ZT_PriPem2PKey(char *p_caPriCertPath,	EVP_PKEY **po_PriKey)
{
	FILE *fp = NULL;
	EVP_PKEY *pkey = NULL;

	fp = fopen (p_caPriCertPath, "r");
	if (fp == NULL) return -1;
	pkey = PEM_read_PrivateKey(fp, NULL, NULL, NULL);
	fclose (fp);

	*po_PriKey = pkey;
	return 0;
}

/*
	读取X509 公钥证书公钥
	# p_caPubCertPath 公钥证书路径 证书而非公钥文件
	# po_PubKey 公钥 需要调用EVP_PKEY_free(pkey) 释放
 */
int ZT_PubPem2PKey(char *p_caPubCertPath,	EVP_PKEY **po_PubKey)
{
	FILE *fp = NULL;
	X509 *x509 = NULL;
	EVP_PKEY *pkey = NULL;

	fp = fopen (p_caPubCertPath, "r");
	if (fp == NULL) return -1;
	x509 = PEM_read_X509(fp, NULL, NULL, NULL);
	fclose (fp);

	if (x509 == NULL) {
		ERR_print_errors_fp (stderr);
		return -2;
	}

	/* Get public key - eay */
	pkey = X509_get_pubkey(x509);
	if (pkey == NULL) {
		X509_free(x509);
		ERR_print_errors_fp (stderr);
		return -3;
	}

	X509_free(x509);
	*po_PubKey = pkey;
	return 0;
}


/*
	RSA签名
	# p_Key 私钥
	# pi_caData 待签名数据
	# pi_iDataLen 待签名数据长度
	# po_caSig  签名结果 出口参数 Hex
	# po_iSigLen 签名结果长度 出口参数

	待增加 签名算法设置
 */
int ZT_RSA_Sign(EVP_PKEY *p_Key,unsigned char *pi_caData,int pi_iDataLen,unsigned char *po_caSig,int * po_iSigLen)
{
	int err = 0;
	int sig_len = 0;
	unsigned char sig_buf[4096]={0};
	EVP_MD_CTX md_ctx;
	EVP_MD * md = NULL;
	EVP_PKEY *pkey = NULL;

	if(p_Key == NULL)
	{
		return -1;
	}	

	pkey = p_Key;

	if((pi_caData == NULL) || (strlen(pi_caData)<=0))
	{
		return -1;
	}

	/* Just load the crypto library error strings,
	 * SSL_load_error_strings() loads the crypto AND the SSL ones */
	/* SSL_load_error_strings();*/
	ERR_load_crypto_strings();


	/* Do the signature */
	EVP_SignInit   (&md_ctx, EVP_sha1());
	//EVP_SignInit   (&md_ctx, EVP_md5());
	EVP_SignUpdate (&md_ctx, pi_caData, pi_iDataLen);
	sig_len = sizeof(sig_buf);
	err = EVP_SignFinal (&md_ctx, sig_buf, &sig_len, pkey);
	if (err != 1) {
		//openssl 未对 md_ctx.md_data 进行释放 
		OPENSSL_free(md_ctx.md_data);

		ERR_print_errors_fp(stderr);
		return -4;
	}

	//openssl 未对 md_ctx.md_data 进行释放 
	OPENSSL_free(md_ctx.md_data);

	*po_iSigLen = sig_len;
	memcpy(po_caSig,sig_buf,sig_len);

#ifdef ZT_DEBUG
	//ZT_PrintHex("Sign Data = \n",pi_caData,pi_iDataLen);
	ZT_PrintHex("Sign = ",(unsigned char*)po_caSig,*po_iSigLen);
#endif

	return 0;
}


/*
	RSA签名验证
	# p_Key 公钥
	# pi_caData 签名数据
	# pi_iDataLen 签名数据长度	
	# pi_caSig  待验证签名结果 Hex
	# pi_iSigLen 签名结果长度

 */
int ZT_RSA_SignVerify(EVP_PKEY *p_Key,unsigned char *pi_caData,int pi_iDataLen,unsigned char *pi_caSig,int pi_iSigLen)
{
	int err = 0,iLen = 0,iLen1 = 0;
	EVP_MD_CTX md_ctx;
	EVP_PKEY * pkey = NULL;
	unsigned char sig_buf[4096]={0};

	if(p_Key == NULL)
	{
		return -1;
	}	

	pkey = p_Key;

	if((pi_caData == NULL) || (strlen(pi_caData)<=0))
	{
		return -1;
	}

	if((pi_caSig == NULL) || (strlen(pi_caSig)<=0))
	{
		return -1;
	}

#ifdef ZT_DEBUG
	printf("---------------- %s -- %d -------------- \n",__func__,__LINE__);
	//ZT_PrintHex("Sign Data = \n",pi_caData,pi_iDataLen);
	ZT_PrintHex("Sign = ",(unsigned char*)pi_caSig,pi_iSigLen);
#endif	

	/* Just load the crypto library error strings,
	 * SSL_load_error_strings() loads the crypto AND the SSL ones */
	/* SSL_load_error_strings();*/
	ERR_load_crypto_strings();

	/* Verify the signature */

	EVP_VerifyInit   (&md_ctx, EVP_sha1());
	//EVP_SignInit   (&md_ctx, EVP_md5());
	EVP_VerifyUpdate (&md_ctx, pi_caData, pi_iDataLen);
	err = EVP_VerifyFinal (&md_ctx, pi_caSig, pi_iSigLen, pkey);
	if (err != 1) {
		//openssl 未对 md_ctx.md_data 进行释放 
		OPENSSL_free(md_ctx.md_data);

		ERR_print_errors_fp (stderr);
		return -3;
	}

	//openssl 未对 md_ctx.md_data 进行释放 
	OPENSSL_free(md_ctx.md_data);

	return (0);
}



/*
	证书验证
	# p_caCertAPemPath 验签证书
	# p_caCertBPemPath 待验签证书
 */
int ZT_Verify_Cert(char *p_caCertAPemPath,char *p_caCertBPemPath)
{
	int iRet = 0;
	X509_STORE_CTX *ctx = NULL;        //证书存储区句柄
    X509 *CertA = NULL;                //X509证书结构体，保存根证书	
    X509 *CertB = NULL;                //X509证书结构体，保存用户证书
    STACK_OF(X509) *caCertStack = NULL;
    X509_STORE *rootCertStore = NULL;    //根证书存储区
	FILE *  fpA,*fpB;

	fpA = fopen (p_caCertAPemPath, "r");
	if (fpA == NULL) return -2;
	CertA = PEM_read_X509(fpA, NULL, NULL, NULL);
	fclose (fpA);

	if (CertA == NULL) {
		ERR_print_errors_fp (stderr);
		return -2;
	}

#ifdef ZT_DEBUG
	X509_print_fp(stdout, CertA);
#endif

	fpB = fopen (p_caCertBPemPath, "r");
	if (fpB == NULL) return -3;
	CertB = PEM_read_X509(fpB, NULL, NULL, NULL);
	fclose (fpB);

	if (CertB == NULL) {
		ERR_print_errors_fp (stderr);
		return -3;
	}

#ifdef ZT_DEBUG
	X509_print_fp(stdout, CertB);
#endif

	OpenSSL_add_all_algorithms(); // MUST

	//新建X509证书存储区
    rootCertStore = X509_STORE_new();

    //添加根证书到证书存储区
    //**********************************************************************
    //多级证书关键处在这里，将所有的根证书加到这里。
    iRet = X509_STORE_add_cert(rootCertStore,CertA);
    if(iRet != 1)
    {
        return -4;
    }    
    //X509_STORE_add_cert(rootCertStore,CertX);    
    //**********************************************************************

    //设置检查CRL标志位，如果设置此标志位，则检查CRL，否则不检查CRL。
    //X509_STORE_set_flags(rootCertStore,X509_V_FLAG_CRL_CHECK);
    
    //新建证书存储区句柄
    ctx = X509_STORE_CTX_new();
    if(ctx == NULL)
    {
    	X509_free(CertA);
    	X509_free(CertB);
    	return -4;
    }	

    //初始化根证书存储区、用户证书
    iRet = X509_STORE_CTX_init(ctx,rootCertStore,CertB,caCertStack);
    if(iRet != 1)
    {
        X509_free(CertA);
        X509_free(CertB);
        X509_STORE_CTX_cleanup(ctx);
        X509_STORE_CTX_free(ctx);
        X509_STORE_free(rootCertStore);
        return -4;
    }

    //验证用户证书
    iRet = X509_verify_cert(ctx);    
    if(iRet != 1)
    {
        printf("verify error= %d,info:%s\n",ctx->error,X509_verify_cert_error_string(ctx->error));
	    X509_free(CertA);
	    X509_free(CertB);
	    X509_STORE_CTX_cleanup(ctx);
	    X509_STORE_CTX_free(ctx);
	    X509_STORE_free(rootCertStore);        
        return -1;
    }
    
    X509_free(CertA);
    X509_free(CertB);
    X509_STORE_CTX_cleanup(ctx);
    X509_STORE_CTX_free(ctx);
    X509_STORE_free(rootCertStore);
    return 0;
}


/*
	EVP_PKEY 结构转换到 RSA 
	# po_RSA 转换后的RSA结构 
	# p_Pkey  EVP_PKEY结构 

	使用后需要调用 EVP_PKEY_free() 释放p_Pkey po_RSA 会同步释放
 */
int ZT_Pkey2Rsa(EVP_PKEY * p_Pkey,RSA ** po_RSA)
{
	if(p_Pkey == NULL)
	{
		return -1;
	}	

	// RSA_print_fp(stdout, p_Pkey->pkey.rsa, 0);

	*po_RSA  = p_Pkey->pkey.rsa;
	return 0;
}


/*
	RSA 结构转换到 EVP_PKEY 
	# p_RSA 待转换RSA结构 
	# po_Pkey  转换后的EVP_PKEY结构 出口参数 使用后需要调用 EVP_PKEY_free() 释放
 */
int ZT_Rsa2Pkey(RSA * p_RSA,EVP_PKEY ** po_Pkey )
{
	EVP_PKEY * pk = NULL;
	pk=EVP_PKEY_new();

	//设置EVP_PKEY 中的RSA 密钥结构，使它代表该RSA 密钥。
	if (!EVP_PKEY_assign_RSA(pk, p_RSA))
	{
		EVP_PKEY_free(pk);
		return -1;
	}

	// RSA_print_fp(stdout, pk->pkey.rsa, 0);

	*po_Pkey  = pk;
	return 0;
}

/*
	私钥加密接口
	# p_RSA 私钥RSA结构
	# p_iPadding 填充格式
		RSA_PKCS1_PADDING填充模式下 pi_caData不得大于 RSA_size(p_RSA)-11
		RSA_X931_PADDING pi_caData不得大于 RSA_size(p_RSA)-2

	# pi_caData 输入数据
	# po_caEData 加密后数据

	加密后生成结果 长度 == RSA_size(p_RSA) 即 模长
 */
int ZT_RSA_PriEncrypt(RSA * p_RSA,int p_iPadding,char * pi_caData,char *po_caEData)
{
	int iLen = 0,iKeyLen = 0,iPadding = 0;

#ifdef ZT_DEBUG			
	//RSA_print_fp(stdout,p_RSA,11);
#endif	

	iKeyLen = RSA_size(p_RSA);

	switch(p_iPadding)
	{
		case RSA_PKCS1_PADDING: { iKeyLen-=11; break;}
		case RSA_X931_PADDING: { iKeyLen-=2; break;}
		case RSA_NO_PADDING: { break;}
		default:{ return -1;}
	}

	// 函数原型  int RSA_private_encrypt(int flen, unsigned char *from,unsigned char *to, RSA *rsa, int padding);
	
	iLen = RSA_private_encrypt(iKeyLen,pi_caData,po_caEData,p_RSA,p_iPadding);
	if(iLen < 0)
	{
		return -2;
	}

#ifdef ZT_DEBUG
	ZT_PrintHex("Data = ",(unsigned char*)pi_caData,strlen(pi_caData));
	ZT_PrintHex("EData = ",po_caEData,iLen);
#endif

	return iLen;
}

/*
	公钥解密接口
	# p_RSA 公钥RSA结构
	# p_iPadding 加密时填充格式
	# po_caData 解密后数据
	# pi_caEData 加密数据

	解密后生成结果 长度 == RSA_size(p_RSA) 即 模长
 */
int ZT_RSA_PubDecrypt(RSA * p_RSA,int p_iPadding,char * po_caData,char *pi_caEData)
{
	int iLen = 0,iKeyLen = 0,iPadding = 0;

	iKeyLen = RSA_size(p_RSA);

	iLen = RSA_public_decrypt(iKeyLen,pi_caEData,po_caData,p_RSA,p_iPadding);
	if(iLen < 0)
	{
		return -2;
	}

#ifdef ZT_DEBUG
	ZT_PrintHex("EData = ",pi_caEData,iKeyLen);	
	ZT_PrintHex("Data = ",(unsigned char*)po_caData,iLen);
#endif

	return iLen;
}

/*
	公钥加密接口
	# p_RSA 私钥RSA结构
	# p_iPadding 填充格式
		RSA_PKCS1_PADDING填充模式下 pi_caData不得大于 RSA_size(p_RSA)-11
		RSA_X931_PADDING pi_caData不得大于 RSA_size(p_RSA)-2

	# pi_caData 输入数据
	# po_caEData 加密后数据

	加密后生成结果 长度 == RSA_size(p_RSA) 即 模长
 */
int ZT_RSA_PubEncrypt(RSA * p_RSA,int p_iPadding,char * pi_caData,char *po_caEData)
{
	int iLen = 0,iKeyLen = 0,iPadding = 0;

#ifdef ZT_DEBUG			
	//RSA_print_fp(stdout,p_RSA,11);
#endif	

	iKeyLen = RSA_size(p_RSA);

	switch(p_iPadding)
	{
		case RSA_PKCS1_PADDING: { iKeyLen-=11; break;}
		case RSA_SSLV23_PADDING: { iKeyLen-=11; break;}
		case RSA_X931_PADDING: { iKeyLen-=2; break;}
		case RSA_NO_PADDING: { break;}
		case RSA_PKCS1_OAEP_PADDING:{ iKeyLen = iKeyLen -2 * SHA_DIGEST_LENGTH-2 ;}
		default:{ return -1;}
	}

	iLen = RSA_public_encrypt(iKeyLen,pi_caData,po_caEData,p_RSA,p_iPadding);
	if(iLen < 0)
	{
		return -2;
	}

#ifdef ZT_DEBUG
	ZT_PrintHex("Data = ",(unsigned char*)pi_caData,strlen(pi_caData));
	ZT_PrintHex("EData = ",po_caEData,iLen);
#endif

	return iLen;
}

/*
	公钥解密接口
	# p_RSA 公钥RSA结构
	# p_iPadding 加密时填充格式
	# po_caData 解密后数据
	# pi_caEData 加密数据

	解密后生成结果 长度 == RSA_size(p_RSA) 即 模长
 */
int ZT_RSA_PriDecrypt(RSA * p_RSA,int p_iPadding,char * po_caData,char *pi_caEData)
{
	int iLen = 0,iKeyLen = 0,iPadding = 0;

	iKeyLen = RSA_size(p_RSA);

	iLen = RSA_private_decrypt(iKeyLen,pi_caEData,po_caData,p_RSA,p_iPadding);
	if(iLen < 0)
	{
		return -2;
	}

#ifdef ZT_DEBUG
	ZT_PrintHex("EData = ",pi_caEData,iKeyLen);	
	ZT_PrintHex("Data = ",(unsigned char*)po_caData,iLen);
#endif

	return iLen;
}


/*
	sha1Hash 
	# p_caFileName 待哈希摘要文件
	# po_caHash 哈希结果,为定长20字节 Hex 
*/
int ZT_File2Sha1(char * p_caFileName,unsigned char *po_caHash)
{
	int fd = 0,iRet = 0,i = 0;
	unsigned char * pSource = NULL;
	struct stat st;
	
	memset(&st, 0x00, sizeof(struct stat));

	if(0 != stat(p_caFileName, &st))
	{
		printf("Failed to get length of [%s]!", p_caFileName);
		return -1;
	}
	printf("------------- %s -- %d st.st_size = %d --------------\n",__func__,__LINE__,(int)st.st_size);

	if((fd = open(p_caFileName, O_RDONLY) )< 0)
	{
		printf("open %s failed ,errno = %d\n",p_caFileName,errno);
		return -1;
	}

	pSource = malloc(st.st_size);
	//从文件中读取数据
	if(st. st_size != read(fd, pSource, st.st_size))
	{
		printf("read %s failed ,errno = %d\n",p_caFileName,errno);		
		free(pSource);
		close(fd);
		return -1;
	}
	
	//openssl sha1 算法
	SHA1(pSource,(int)st.st_size,po_caHash);
	
	printf("TF_Update_Sha1 %s :\n",p_caFileName);
	for(i = 0;i<20;i++)
	{
		printf("%02X",po_caHash[i]);
	}	
	printf("\n");
	
	printf("------------- %s -- %d --------------\n",__func__,__LINE__);
	free(pSource);
	close(fd);
	return 0;
}

/*
	Base64 编码
	# pi_caData 待编码数据
	# pi_iDataLen 待编码数据长度
	# po_caBase64 编码后数据
	# po_iBase64Len 编码后数据长度

	此接口返回带格式数据 每80字符插入一个换行
 */
int ZT_Base64Encode(unsigned char * pi_caData,int pi_iDataLen,unsigned char * po_caBase64,int * po_iBase64Len)
{
	EVP_ENCODE_CTX ectx;
	int iCnt = 0;


	EVP_EncodeInit(&ectx);
	EVP_EncodeUpdate(&ectx,po_caBase64,&iCnt,pi_caData,pi_iDataLen);
	*po_iBase64Len = iCnt;  
	EVP_EncodeFinal(&ectx, po_caBase64 + iCnt, &iCnt);
	*po_iBase64Len += iCnt ; 

#ifdef ZT_DEBUG
	printf("---------------- \n%s \n---------------- \n",pi_caData);
	printf("---------------- \n%s \n[%d]\n---------------- \n",po_caBase64,*po_iBase64Len);
#endif

	return 0;
}

/*
	Base64 解码
	# po_caData 解码后数据
	# po_iDataLen 解码后数据长度
	# pi_caBase64 待解码数据
	# pi_iBase64Len 待解码数据长度

	此接口需传入带格式数据 每80字符插入一个换行
 */
int ZT_Base64Decode(unsigned char * pi_caBase64,int pi_iBase64Len,unsigned char * po_caData,int * po_iDataLen)
{
	EVP_ENCODE_CTX dctx;
	int iCnt = 0;

	EVP_DecodeInit(&dctx);

	//输入数据为满行的数据时，返回为1；如果输入数据是最后一行数据的时候，返回0；返回－1则表明出错
	EVP_DecodeUpdate(&dctx,po_caData, &iCnt, pi_caBase64, pi_iBase64Len);	
	*po_iDataLen = iCnt;
	EVP_DecodeFinal(&dctx, po_caData+iCnt, &iCnt);
	*po_iDataLen += iCnt;

#ifdef ZT_DEBUG
	printf("---------------- \n%s \n---------------- \n",pi_caBase64);
	printf("---------------- \n%s \n[%d]\n---------------- \n",po_caData,*po_iDataLen);
#endif

	return 0;
}


/*
	计算MD5
	# pi_caData 待计算数据
	# pi_iDataLen 待计算数据长度
	# po_caMd5 MD5摘要数据

	MD5 摘要数据为定长 16 字节
 */
int ZT_MD5(unsigned char * pi_caData,int pi_iDataLen,char * po_caMd5)
{

	//MD2 、MD4、MD5、SHA、SHA1、SHA256、SHA512 算法用法相同
	MD5(pi_caData,pi_iDataLen,po_caMd5);

#ifdef ZT_DEBUG
	ZT_PrintHex("Data = ",(unsigned char*)pi_caData,pi_iDataLen);
	ZT_PrintHex("MD5 = ",po_caMd5,16);
#endif
	return 0;
}

/*
	DES CBC算法 
	# pi_caKey 加密密钥  Hex BCD  单倍长密钥 即 8字节
	# pi_caVector 初始化向量 Hex BCD 8字节
	# pi_caIn 待加密数据  Hex BCD   长度应为8的倍数 否则不足8字节的部分 将自动后补0 
	# pi_caInLen 输入数据长度 	
	# po_caOut 加密后数据  Hex BCD
	# pi_iMode 加密/解密 
		= DES_ENCRYPT  加密模式
		= DES_DECRYPT  解密模式
 */
int ZT_CBC_Des(unsigned char * pi_caKey,unsigned char * pi_caVector,unsigned char * pi_caIn,int pi_iInLen,unsigned char * po_caOut,int pi_iMode )
{
	int iRet = 0;
	DES_cblock in,out,vec;
	DES_key_schedule ks;

	pi_caKey[8] = 0x00; //单倍长密钥
	DES_set_key_unchecked(pi_caKey,&ks);
	memcpy(&vec,pi_caVector,8);

	if(pi_iMode == DES_ENCRYPT)
	{
		des_ncbc_encrypt(pi_caIn,po_caOut,pi_iInLen,ks,&vec,DES_ENCRYPT);
		//des_ede3_cbc_encrypt(caInTmp,po_caOut,8,ks,ks,ks,&vec,DES_ENCRYPT);		
	}else if(pi_iMode == DES_DECRYPT){
		//des_ede3_cbc_encrypt(caInTmp,po_caOut,8,ks,ks,ks,&vec,DES_DECRYPT);		
		des_ncbc_encrypt(pi_caIn,po_caOut,pi_iInLen,ks,&vec,DES_DECRYPT);
	}else{
		return -3;
	}

#ifdef ZT_DEBUG
	ZT_PrintHex("DES CBC Vec = ",(unsigned char*)pi_caVector,8);	
	ZT_PrintHex("DES CBC Key = ",(unsigned char*)pi_caKey,strlen(pi_caKey));	
	ZT_PrintHex("DES CBC In = ",(unsigned char*)pi_caIn,pi_iInLen);
	ZT_PrintHex("DES CBC Out = ",po_caOut,strlen(po_caOut));
#endif

	return 0;
}

/*
	3DES CBC算法 
	# pi_caKey 加密密钥  Hex BCD  3倍长密钥 即 8x3字节
	# pi_caVector 初始化向量 Hex BCD 8字节
	# pi_caIn 待加密数据  Hex BCD   长度应为8的倍数 否则不足8字节的部分 将自动后补0 
	# pi_caInLen 输入数据长度 	
	# po_caOut 加密后数据  Hex BCD
	# pi_iMode 加密/解密 
		= DES_ENCRYPT  加密模式
		= DES_DECRYPT  解密模式

	支持两倍长密钥的3des运算 
	程序自动将 pi_caKey第一段密钥(前8字节密钥)用作第三段密钥((后8字节密钥))
 */
int ZT_CBC_3Des(unsigned char * pi_caKey,unsigned char * pi_caVector,unsigned char * pi_caIn,int pi_iInLen,unsigned char * po_caOut,int pi_iMode )
{
	int iRet = 0;
	DES_cblock vec;
	DES_key_schedule ks1,ks2,ks3;
	unsigned char caKeyTmp[9]={0};

	memset(caKeyTmp,0,sizeof(caKeyTmp));
	memcpy(caKeyTmp,pi_caKey,8);
	DES_set_key_unchecked(caKeyTmp,&ks1);

	memset(caKeyTmp,0,sizeof(caKeyTmp));
	memcpy(caKeyTmp,pi_caKey+8,8);
	DES_set_key_unchecked(caKeyTmp,&ks2);

	if(strlen(pi_caKey) == 16)
	{
		//两倍长密钥支持
		memcpy(&ks3,&ks1,sizeof(DES_key_schedule));
	}else{	
		memset(caKeyTmp,0,sizeof(caKeyTmp));
		memcpy(caKeyTmp,pi_caKey+16,8);
		DES_set_key_unchecked(caKeyTmp,&ks3);	
	}

	memcpy(&vec,pi_caVector,8);

	if(pi_iMode == DES_ENCRYPT)
	{
		des_ede3_cbc_encrypt(pi_caIn,po_caOut,pi_iInLen,ks1,ks2,ks3,&vec,DES_ENCRYPT);
	}else if(pi_iMode == DES_DECRYPT){
		des_ede3_cbc_encrypt(pi_caIn,po_caOut,pi_iInLen,ks1,ks2,ks3,&vec,DES_DECRYPT);
	}else{
		return -3;
	}

#ifdef ZT_DEBUG
	ZT_PrintHex("3DES CBC Vec = ",(unsigned char*)pi_caVector,8);	
	ZT_PrintHex("3DES CBC Key = ",(unsigned char*)pi_caKey,strlen(pi_caKey));	
	ZT_PrintHex("3DES CBC In = ",(unsigned char*)pi_caIn,pi_iInLen);
	ZT_PrintHex("3DES CBC Out = ",po_caOut,strlen(po_caOut));
#endif

	return 0;
}


/*
	DES ECB算法
	# pi_caKey 加密密钥  Hex BCD 
	# pi_caIn 待加密数据  Hex BCD 8字节数据 超出部分忽略 不足8字节自动补0
	# po_caOut 加密后数据  Hex BCD 定长8字节
	# pi_iMode 加密/解密 
		= DES_ENCRYPT  加密模式
		= DES_DECRYPT  解密模式

	每次对8字节数据进行处理 待加密数据可以分组调用此接口进行后拼接
 */
int ZT_ECB_Des(unsigned char * pi_caKey,unsigned char * pi_caIn,unsigned char * po_caOut,int pi_iMode )
{
	des_cblock in,out;
	des_key_schedule ks;

	/*
		DES_set_key_checked(pi_caKey,&ks);
		return -1   wrong odd parity key
			   -2   weak key
			   error the key schedule is not generated
	 */
	pi_caKey[8] = 0x00; //单倍长密钥
	DES_set_key_unchecked(pi_caKey, &ks);
	memcpy(in, pi_caIn, 8);
	memset(po_caOut, 0, 8);

	if(pi_iMode == DES_ENCRYPT)
	{
		des_ecb_encrypt(&in, &out, ks, DES_ENCRYPT);
	}else if(pi_iMode == DES_DECRYPT){
		des_ecb_encrypt(&in, &out, ks, DES_DECRYPT);
	}else{
		return -3;
	}

	memcpy(po_caOut,&out,8);

#ifdef ZT_DEBUG
	ZT_PrintHex("DES ECB Key = ",(unsigned char*)pi_caKey,8);
	ZT_PrintHex("DES ECB In = ",(unsigned char*)pi_caIn,8);
	ZT_PrintHex("DES ECB Out = ",po_caOut,8);
#endif

	return 0;
}

/*
	3DES ECB算法
	# pi_caKey 加密密钥  Hex BCD 3倍长密钥 即 8x3字节
	# pi_caIn 待加密数据  Hex BCD 8字节数据 超出部分忽略 不足8字节自动补0
	# po_caOut 加密后数据  Hex BCD 定长8字节 
	# pi_iMode 加密/解密 
		= DES_ENCRYPT  加密模式
		= DES_DECRYPT  解密模式

	每次对8字节数据进行处理 待加密数据可以分组调用此接口进行后拼接
	支持两倍长密钥的3des运算 
	程序自动将 pi_caKey第一段密钥(前8字节密钥)用作第三段密钥((后8字节密钥))
 */
int ZT_ECB_3Des(unsigned char * pi_caKey,unsigned char * pi_caIn,unsigned char * po_caOut,int pi_iMode )
{
	des_cblock in,out;
	DES_key_schedule ks1,ks2,ks3;
	unsigned char caKeyTmp[9]={0};

	memset(caKeyTmp,0,sizeof(caKeyTmp));
	memcpy(caKeyTmp,pi_caKey,8);
	DES_set_key_unchecked(caKeyTmp,&ks1);

	memset(caKeyTmp,0,sizeof(caKeyTmp));
	memcpy(caKeyTmp,pi_caKey+8,8);
	DES_set_key_unchecked(caKeyTmp,&ks2);

	if(strlen(pi_caKey) == 16)
	{
		//两倍长密钥支持
		memcpy(&ks3,&ks1,sizeof(DES_key_schedule));
	}else{	
		memset(caKeyTmp,0,sizeof(caKeyTmp));
		memcpy(caKeyTmp,pi_caKey+16,8);
		DES_set_key_unchecked(caKeyTmp,&ks3);	
	}

	if(pi_iMode == DES_ENCRYPT)
	{
		des_ecb3_encrypt(pi_caIn, po_caOut, ks1,ks2,ks3,DES_ENCRYPT);
	}else if(pi_iMode == DES_DECRYPT){
		des_ecb3_encrypt(pi_caIn, po_caOut, ks1,ks2,ks3,DES_DECRYPT);
	}else{
		return -3;
	}

#ifdef ZT_DEBUG
	ZT_PrintHex("3DES ECB Key = ",(unsigned char*)pi_caKey,strlen(pi_caKey));	
	ZT_PrintHex("3DES ECB In = ",(unsigned char*)pi_caIn,strlen(pi_caIn));
	ZT_PrintHex("3DES ECB Out = ",po_caOut,strlen(po_caOut));
#endif

	return 0;
}

/*
	DES 密钥生成接口
	# po_caDesKey 生成的DES密钥 Hex 16字节

	// typedef struct DES_ks
	// {
	//     union
	//     {
	//         DES_cblock cblock;
	//         DES_LONG deslong[2];
	//     } ks[16];
	// } DES_key_schedule;
	 
	// sizeof(DES_cblock) = 8字节
	// sizeof(const_DES_cblock ) = 8字节

*/
int ZT_Generate_Des(unsigned char * po_caDesKey)
{

	des_cblock key;

	DES_random_key(&key);

	memcpy(po_caDesKey,&key,16);

#ifdef ZT_DEBUG
	ZT_PrintHex("ZT_Generate_Des = ",(unsigned char*)po_caDesKey,16);
#endif

	return 0;
}



/*
	AES CBC 加密解密接口
	# pi_caKey 密钥 128位 = 16字节
	# pi_caVec 初始化向量 长度为  AES_BLOCK_SIZE = 16
	# pi_caIn 输入数据 长度必须为16的倍数	否则不足16字节的部分 将被丢弃  
	# pi_caInLen 输入数据长度 
	# po_caOut 数据数据 
	# pi_iMode 加密模式/解密模式
		= AES_ENCRYPT 加密
		= AES_DECRYPT 解密

	此加密接口 暂只支持 128位密钥(16字节)
 */
int ZT_CBC_AES(unsigned char* pi_caKey,unsigned char* pi_caVec,unsigned char* pi_caIn,int pi_iInLen, unsigned char* po_caOut,int pi_iMode)
{
	unsigned char caVec[AES_BLOCK_SIZE]={0};

    if((!pi_caKey) || (!pi_caVec) || (!pi_caIn))
    {
    	return -1;
    }

    
    if(pi_iInLen < 0)
    {
    	return -2;
    }	

    memcpy(caVec,pi_caVec,AES_BLOCK_SIZE);

    AES_KEY aes;

    if(pi_iMode == AES_ENCRYPT)
    {
	    if(AES_set_encrypt_key(pi_caKey, 128, &aes) < 0)
	    {
	        return -3;
	    }
	    AES_cbc_encrypt(pi_caIn, po_caOut, pi_iInLen, &aes, caVec, AES_ENCRYPT);
	}else if(pi_iMode == AES_DECRYPT){
		if(AES_set_decrypt_key(pi_caKey, 128, &aes) < 0)
	    {
	        return -3;
	    }
	    AES_cbc_encrypt(pi_caIn, po_caOut, pi_iInLen, &aes, caVec, AES_DECRYPT);
	}else{
		return -3;
	}

#ifdef ZT_DEBUG
	ZT_PrintHex("AES CBC Vec = ",(unsigned char*)pi_caVec,16);	
	ZT_PrintHex("AES CBC Key = ",(unsigned char*)pi_caKey,strlen(pi_caKey));	
	ZT_PrintHex("AES CBC In = ",(unsigned char*)pi_caIn,strlen(pi_caIn));
	ZT_PrintHex("AES CBC Out = ",po_caOut,strlen(po_caOut));
#endif

    return 0;
}


/*
	AES ECB 加密解密接口
	# pi_caKey 密钥 128位 = 16字节
	# pi_caIn 输入数据 长度必须为16 
	# pi_caInLen 输入数据长度 
	# po_caOut 数据数据 
	# pi_iMode 加密模式/解密模式
		= AES_ENCRYPT 加密
		= AES_DECRYPT 解密

	每次只能加解密16字节数据 	待加密数据可以分组调用此接口进行后拼接
	此加密接口 暂只支持 128位密钥(16字节)
 */
int ZT_ECB_AES(unsigned char* pi_caKey,unsigned char* pi_caIn, unsigned char* po_caOut,int pi_iMode)
{
    if((!pi_caKey) || (!pi_caIn))
    {
    	return -1;
    }

    AES_KEY aes;

    if(pi_iMode == AES_ENCRYPT)
    {
	    if(AES_set_encrypt_key(pi_caKey, 128, &aes) < 0)
	    {
	        return -3;
	    }

	    AES_ecb_encrypt(pi_caIn, po_caOut, &aes, AES_ENCRYPT);
	}else if(pi_iMode == AES_DECRYPT){
		if(AES_set_decrypt_key(pi_caKey, 128, &aes) < 0)
	    {
	        return -3;
	    }
	    AES_ecb_encrypt(pi_caIn, po_caOut, &aes, AES_DECRYPT);
	}else{
		return -3;
	}

#ifdef ZT_DEBUG
	ZT_PrintHex("AES ECB Key = ",(unsigned char*)pi_caKey,strlen(pi_caKey));	
	ZT_PrintHex("AES ECB In = ",(unsigned char*)pi_caIn,strlen(pi_caIn));
	ZT_PrintHex("AES ECB Out = ",po_caOut,strlen(po_caOut));
#endif

    return 0;
}