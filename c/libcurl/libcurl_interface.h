#ifndef __LIBCURL_INTERFACE__H__
#define __LIBCURL_INTERFACE__H__


int ZT_Curl_Http(char * pi_caUrl,char * pi_caParam,char * po_caContent,int pi_iMothed);
int ZT_Curl_Https(char * pi_caUrl,char * pi_caParam,char * po_caContent,int pi_iMothed,
	char * pi_caSslCertPath,char * pi_caSslKeyPath,char *pi_caCaInfoPath);	


#endif

