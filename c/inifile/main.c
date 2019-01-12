/* 
* @Author: ChangingP
* @Date:   2015-03-26 22:41:39
* @Last Modified by:   ChangingP
* @Last Modified time: 2015-03-28 23:32:26
*/

#include <stdio.h>
#include <memory.h>

#include "ztinifile.h"

int main(int argc, char const *argv[])
{
	int iRet = 0;
	char caTmp[512]={0};
	TInifile *p_iniCtrl;

	ZTIni_Init(&p_iniCtrl,"./Settings.ini");

	ZTIni_Print(p_iniCtrl);

	ZTIni_Get(p_iniCtrl,"ZCfgSvc","AAAMessageBoxEnabled",caTmp,"我是默认值");
	printf("ZTIni_Get AAAMessageBoxEnabled %s\n",caTmp);

	iRet = ZTIni_GetInt(p_iniCtrl,"ZCfgSvc","AutoConnect",999);
	printf("ZTIni_GetInt AutoConnect %d\n",iRet);

	ZTIni_Set(p_iniCtrl,"ZCfgSvc","1xMessageBoxEnabled","设置为设置");

	ZTIni_Save(p_iniCtrl,NULL);

	ZTIni_SetInt(p_iniCtrl,"ZCfgSvc","MSZCFG",12345);

	ZTIni_Close(p_iniCtrl);

	return 0;
}