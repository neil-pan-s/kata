/* 
* @Author: ChangingP
* @Date:   2015-03-26 16:13:52
* @Last Modified by:   ChangingP
* @Last Modified time: 2015-03-27 08:58:01
*/

#include <stdio.h>
#include <unistd.h>
#include <memory.h>

#include <curl/curl.h>
#include "libcurl_interface.h"

#define SKIP_PEER_VERIFICATION
#define SKIP_HOSTNAME_VERIFICATION

//发送数据结构 
struct WriteThis {
  const char *readptr;  //当前发送数据指针
  long sizeleft;   //余下数据计数
};

//接收数据结构
struct ReadThis {
  char *writeptr;  //当前接收数据指针
  long sizecnt;	//接收数据计数
};

//libcurl发送数据的回调函数 
static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
	struct WriteThis *pooh = (struct WriteThis *)userp;

	if (size * nmemb < 1)
		return 0;

	if (pooh->sizeleft) {
		*(char *)ptr = pooh->readptr[0]; /* copy one single byte */
		pooh->readptr++;                 /* advance pointer */
		pooh->sizeleft--;                /* less data left */
		return 1;                        /* we return 1 byte at a time! */
	}

	return 0;                          /* no more data left to deliver */
}

//libcurl接收数据的回调函数 
static size_t write_callback( void *ptr, size_t size, size_t nmemb, void *stream )  
{  
	int iLen = 0;
	struct ReadThis *content = (struct ReadThis *)stream;

	iLen = size * nmemb;

	if (iLen < 1)
		return 0;

	//printf("size * nmemb  = %d\n", iLen );

	memcpy(content->writeptr,(char *)ptr,iLen); 
	content->writeptr += iLen;            
	content->sizecnt += iLen;               
	return iLen;                       

}  


/*
	发起 Http 请求
	# pi_caUrl Http请求地址 (以http://开始)  支持IP地址
		eg. http://ooxx.com
		eg. http://123.125.114.144  百度
	# pi_caParam Http请求Get/Post参数 
		eg. do=ooxx&times=100
	# po_caContent 返回的页面内容
	# pi_iMethod Get/Post方式标志
		= 0 Get传参
		= 1 POST传参
 */
int ZT_Curl_Http(char * pi_caUrl,char * pi_caParam,char * po_caContent,int pi_iMothed)
{
	char caUrl[2048] = {0};
	CURL *curl = NULL;
	CURLcode res;

	struct ReadThis content;

	content.writeptr = po_caContent;
	content.sizecnt = (long)0;

	if(pi_caUrl == NULL)
	{
		return -1;
	}		

	//URL　必须以http开始
	if (memcmp("http://", pi_caUrl, 7) != 0)
	{
		return -1;
	}

	if(pi_iMothed == 0) 	
	{
		//Get 传参 拼接域名和参数
		if(pi_caParam != NULL)
		{
			//URL 过长判断
			if((strlen(pi_caUrl)+strlen(pi_caParam)) > 2046 )
			{
				return -3;
			}	
			sprintf(caUrl,"%s?%s",pi_caUrl,pi_caParam);
		}else{
			sprintf(caUrl,"%.2047s",pi_caUrl);
		}
	}else{
		//POST 传参
		sprintf(caUrl,"%.2047s",pi_caUrl);
	}

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */
		curl_easy_setopt(curl, CURLOPT_URL, caUrl);

		//POST 传参
		if(pi_iMothed == 1)
		{	
			if(pi_caParam != NULL)
			{
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, pi_caParam);
				//curl_easy_setopt(curl, CURLOPT_POST, pi_caParam);
			}else{
				/* Now specify we want to POST data */
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, 1L);
			}	
		}

		//指定回调函数	 
		curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_callback);	
		//可作为接收或传递数据 
		curl_easy_setopt( curl, CURLOPT_WRITEDATA, &content);  

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			        curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return 0;

}

/*
	发起 Https 请求
	# pi_caUrl Http请求地址 (以http://开始)  支持IP地址
		eg. https://ooxx.com
		eg. https://123.125.114.144  百度
	# pi_caParam Http请求Get/Post参数 
		eg. do=ooxx&times=100
	# po_caContent 返回的页面内容
	# pi_iMethod Get/Post方式标志
		= 0 Get传参
		= 1 POST传参 
			eg. do=ooxx&times=100 
			eg. <xml><appid><![CDATA[wxd930ea5d5a258f4f]]></appid><auth_code><![CDATA[123456]]></auth_code></xml> 
	# pi_caSslCertPath CURLOPT_SSLCERT .pem 格式 
	# pi_caSslKeyPath  CURLOPT_SSLKey .pem 格式 
	# pi_caCaInfoPath  CURLOPT_CAINFO .pem 格式 
 */
int ZT_Curl_Https(char * pi_caUrl,char * pi_caParam,char * po_caContent,int pi_iMothed,
	char * pi_caSslCertPath,char * pi_caSslKeyPath,char *pi_caCaInfoPath)
{
	char caUrl[2048] = {0};
	CURL *curl = NULL;
	CURLcode res;
	struct WriteThis pooh;
	struct ReadThis content;

	content.writeptr = po_caContent;
	content.sizecnt = (long)0;

	if(pi_caUrl == NULL)
	{
		return -1;
	}		

	//URL　必须以http开始
	if (memcmp("https://", pi_caUrl, 8) != 0)
	{
		return -1;
	}

	if(pi_iMothed == 0) 	
	{
		//Get 传参 拼接域名和参数
		if(pi_caParam != NULL)
		{
			//URL 过长判断
			if((strlen(pi_caUrl)+strlen(pi_caParam)) > 2046 )
			{
				return -3;
			}	
			sprintf(caUrl,"%s?%s",pi_caUrl,pi_caParam);
		}else{
			sprintf(caUrl,"%.2047s",pi_caUrl);
		}
	}else{
		//POST 传参
		sprintf(caUrl,"%.2047s",pi_caUrl);

		if(pi_caParam != NULL)
		{	
			pooh.readptr = pi_caParam;
			pooh.sizeleft = (long)strlen(pi_caParam);
		}
	}


	/* In windows, this will init the winsock stuff */
	res = curl_global_init(CURL_GLOBAL_DEFAULT);
	/* Check for errors */
	if (res != CURLE_OK) {
		fprintf(stderr, "curl_global_init() failed: %s\n",
		curl_easy_strerror(res));
		return 1;
	}

	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. */
		curl_easy_setopt(curl, CURLOPT_URL,caUrl);

		//POST 传参 方法1 
		if(pi_iMothed == 1) 	
		{
			if(pi_caParam != NULL)
			{
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, pi_caParam);
				//curl_easy_setopt(curl, CURLOPT_POST, pi_caParam);
			}else{
				/* Now specify we want to POST data */
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, 1L);
			}				
		}
		

		//POST 传参 方法2 回调函数实现  暂不开放此方法 
		if(pi_iMothed == 2) 	
		{
			curl_easy_setopt(curl, CURLOPT_POST, 1L);
			if(pi_caParam != NULL)
			{
				/* we want to use our own read function */
				curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

				/* pointer to pass to our read function */
				curl_easy_setopt(curl, CURLOPT_READDATA, &pooh);
			}
		}

		//指定回调函数	 
		curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_callback);	
		//可作为接收或传递数据 
		curl_easy_setopt( curl, CURLOPT_WRITEDATA, &content);  	

		/* get verbose debug output please */
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
	
#ifdef SKIP_PEER_VERIFICATION
		/*
		 * If you want to connect to a site who isn't using a certificate that is
		 * signed by one of the certs in the CA bundle you have, you can skip the
		 * verification of the server's certificate. This makes the connection
		 * A LOT LESS SECURE.
		 *
		 * If you have a CA cert for the server stored someplace else than in the
		 * default bundle, then the CURLOPT_CAPATH option might come handy for
		 * you.
		 */
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif


#ifdef SKIP_HOSTNAME_VERIFICATION
		/*
		 * If the site you're connecting to uses a different host name that what
		 * they have mentioned in their server certificate's commonName (or
		 * subjectAltName) fields, libcurl will refuse to connect. You can skip
		 * this check, but this will make the connection less secure.
		 */
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

		//设置证书
		if( access(pi_caSslCertPath,F_OK) == 0)
		{	
			curl_easy_setopt(curl, CURLOPT_SSLCERT, pi_caSslCertPath);
		}
		if(access(pi_caSslKeyPath,F_OK) == 0)
		{	
			curl_easy_setopt(curl, CURLOPT_SSLKEY, pi_caSslKeyPath);
		}
		if(access(pi_caCaInfoPath,F_OK) == 0)
		{
			curl_easy_setopt(curl, CURLOPT_CAINFO, pi_caCaInfoPath);
		}

		/*
		  If you use POST to a HTTP 1.1 server, you can send data without knowing
		  the size before starting the POST if you use chunked encoding. You
		  enable this by adding a header like "Transfer-Encoding: chunked" with
		  CURLOPT_HTTPHEADER. With HTTP 1.0 or without chunked transfer, you must
		  specify the size in the request.
		*/
#ifdef USE_CHUNKED
		{
			struct curl_slist *chunk = NULL;

			chunk = curl_slist_append(chunk, "Transfer-Encoding: chunked");
			res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
			/* use curl_slist_free_all() after the *perform() call to free this
			   list again */
		}
#else
		/* Set the expected POST size. If you want to POST large amounts of data,
		   consider CURLOPT_POSTFIELDSIZE_LARGE */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, pooh.sizeleft);
#endif

#ifdef DISABLE_EXPECT
		/*
		  Using POST with HTTP 1.1 implies the use of a "Expect: 100-continue"
		  header.  You can disable this header with CURLOPT_HTTPHEADER as usual.
		  NOTE: if you want chunked transfer too, you need to combine these two
		  since you can only set one list of headers with CURLOPT_HTTPHEADER. */

		/* A less good option would be to enforce HTTP 1.0, but that might also
		   have other implications. */
		{
			struct curl_slist *chunk = NULL;

			chunk = curl_slist_append(chunk, "Expect:");
			res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
			/* use curl_slist_free_all() after the *perform() call to free this
			   list again */
		}
#endif	

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			        curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	return 0;
}
