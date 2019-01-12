/* 
* @Author: ChangingP
* @Date:   2015-03-26 22:41:39
* @Last Modified by:   ChangingP
* @Last Modified time: 2015-03-27 08:58:35
*/

#include <stdio.h>
#include <memory.h>

#include "libcurl_interface.h"

#define POST_PARAM_1 "appid=wxd930ea5d5a258f4f&auth_code=123456&body=test&device_info=123&mch_id=1900000109&nonce_str=960f228109051b9969f76c82bde183ac&out_trade_no=1400755861&spbill_create_ip=127.0.0.1&sub_mch_id=124&total_fee=1"
#define POST_PARAM_2 "<xml><appid><![CDATA[wxd930ea5d5a258f4f]]></appid><auth_code><![CDATA[123456]]></auth_code><body><![CDATA[test]]></body><device_info>123</device_info><mch_id>1900000109</mch_id><nonce_str><![CDATA[960f228109051b9969f76c82bde183ac]]></nonce_str><out_trade_no><![CDATA[1400755861]]></out_trade_no><spbill_create_ip><![CDATA[127.0.0.1]]></spbill_create_ip><sub_mch_id>124</sub_mch_id><total_fee>1</total_fee><sign><![CDATA[c380bec2bfd727a4b6845133519f3ad6]]></sign></xml>"

int main(int argc, char const *argv[])
{
	int iRet = 0;
	char caTmp[1024000]={0};  //设置超大缓冲区
	
	//Http Get 
	//memset(caTmp,0,sizeof(caTmp));
	//iRet = ZT_Curl_Http("http://123.125.114.144/s","wd=www.ichanging.org",caTmp,0);
	memset(caTmp,0,sizeof(caTmp));
	iRet = ZT_Curl_Http("http://www.baidu.com/s","wd=www.ichanging.org",caTmp,0);
	printf("------------------------ %s -- %d ----------------------------------- iRet = %d\n",__func__,__LINE__,iRet);
	printf("------------------------ %s -- %d ----------------------------------- \n%s\n",__func__,__LINE__,caTmp);



	// //Http Post
	memset(caTmp,0,sizeof(caTmp));
	iRet = ZT_Curl_Http("http://www.ichanging.org","s=spi",caTmp,1);
	printf("------------------------ %s -- %d ----------------------------------- iRet = %d\n",__func__,__LINE__,iRet);
	printf("------------------------ %s -- %d ----------------------------------- \n%s\n",__func__,__LINE__,caTmp);

	//Https Get
	//参照页面  无Get 传参
	//memset(caTmp,0,sizeof(caTmp));
	//iRet = ZT_Curl_Https("https://cshall.alipay.com/lab/cateQuestion.htm",NULL,caTmp,0,NULL,NULL,NULL);  
	//参照页面  有Get 传参
	memset(caTmp,0,sizeof(caTmp));
	iRet = ZT_Curl_Https("https://cshall.alipay.com/lab/cateQuestion.htm","cateId=233057&pcateId=",caTmp,0,NULL,NULL,NULL);
	printf("------------------------ %s -- %d ----------------------------------- iRet = %d\n",__func__,__LINE__,iRet);
	printf("------------------------ %s -- %d ----------------------------------- \n%s\n",__func__,__LINE__,caTmp);

	//Https Post 
	memset(caTmp,0,sizeof(caTmp));
	iRet = ZT_Curl_Https("https://api.mch.weixin.qq.com/pay/micropay",POST_PARAM_2,caTmp,1,"./certs/apiclient_cert.pem","./certs/apiclient_key.pem","./certs/rootca.pem");
	printf("------------------------ %s -- %d ----------------------------------- iRet = %d\n",__func__,__LINE__,iRet);
	printf("------------------------ %s -- %d ----------------------------------- \n%s\n",__func__,__LINE__,caTmp);

	//Https Post 
	memset(caTmp,0,sizeof(caTmp));
	iRet = ZT_Curl_Https("https://api.mch.weixin.qq.com/pay/micropay",POST_PARAM_1,caTmp,1,"./certs/apiclient_cert.pem","./certs/apiclient_key.pem","./certs/rootca.pem");
	printf("------------------------ %s -- %d ----------------------------------- iRet = %d\n",__func__,__LINE__,iRet);
	printf("------------------------ %s -- %d ----------------------------------- \n%s\n",__func__,__LINE__,caTmp);

	return 0;
}