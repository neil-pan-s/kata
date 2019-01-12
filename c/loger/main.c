/* 
* @Author: ChangingP
* @Date:   2015-03-26 22:41:39
* @Last Modified by:   ChangingP
* @Last Modified time: 2015-03-28 19:09:56
*/

#include <stdio.h>
#include <memory.h>

#include "ztloger.h"

#define POST_PARAM_1 "appid=wxd930ea5d5a258f4f&auth_code=123456&body=test&device_info=123&mch_id=1900000109&nonce_str=960f228109051b9969f76c82bde183ac&out_trade_no=1400755861&spbill_create_ip=127.0.0.1&sub_mch_id=124&total_fee=1"
#define POST_PARAM_2 "<xml><appid><![CDATA[wxd930ea5d5a258f4f]]></appid><auth_code><![CDATA[123456]]></auth_code><body><![CDATA[test]]></body><device_info>123</device_info><mch_id>1900000109</mch_id><nonce_str><![CDATA[960f228109051b9969f76c82bde183ac]]></nonce_str><out_trade_no><![CDATA[1400755861]]></out_trade_no><spbill_create_ip><![CDATA[127.0.0.1]]></spbill_create_ip><sub_mch_id>124</sub_mch_id><total_fee>1</total_fee><sign><![CDATA[c380bec2bfd727a4b6845133519f3ad6]]></sign></xml>"

int main(int argc, char const *argv[])
{
	int iRet = 0;
	ZTLoger *g_loger = NULL;

	ZTLoger_Init(&g_loger,"loger_test.log",LG_DEBUG,true,1000);

	ZTLoger_Write(g_loger,LG_DEBUG,true,"越过长城,走向世界");
	ZTLoger_Write(g_loger,LG_DEBUG,true,POST_PARAM_1);
	ZTLoger_Write(g_loger,LG_DEBUG,true,POST_PARAM_2);

	ZTLoger_Write(g_loger,LG_DEBUG,true,"\x12\x34\x56\x78\x90");

	ZTLoger_Close(g_loger);

	return 0;
}