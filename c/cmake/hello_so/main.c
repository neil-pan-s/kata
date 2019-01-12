/* 
* @Author: ChangingP
* @Date:   2014-08-11 17:34:31
* @Last Modified by:   ChangingP
* @Last Modified time: 2015-04-10 09:36:29
*/
#include <stdio.h> 
#include <stdlib.h>
#include <memory.h>
#include <unistd.h> 
#include <fcntl.h>

#include "ztstring.h"

#define DATA_UTF_8 "\xe7\xa9\xbf\xe8\xb6\x8a\xe9\x95\xbf\xe5\x9f\x8e\x2c\xe8\xb5\xb0\xe5\x90\x91\xe4\xb8\x96\xe7\x95\x8c"

int main()
{

	ZT_HexPrint("DATA_UTF_8",DATA_UTF_8,25);

#ifdef ZT_DEBUG
	printf("defined ZT_DEBUG ..\n");
#endif 

    return 0;
}
