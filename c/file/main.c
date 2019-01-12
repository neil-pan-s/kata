/* 
* @Author: ChangingP
* @Date:   2015-03-26 22:41:39
* @Last Modified by:   ChangingP
* @Last Modified time: 2015-03-28 19:40:06
*/

#include <stdio.h>
#include <memory.h>

#include "ztfile.h"

int main(int argc, char const *argv[])
{
	int iRet = 0;
	char caTmp[512]={0};

	ZT_FileSearch("./",".c",caTmp);
	printf("ZT_FileSearch *.c = %s \n",caTmp);
	
	iRet = ZT_FileSize("./makefile");
	printf("ZT_FileSize makefile = %d \n",iRet);

	return 0;
}