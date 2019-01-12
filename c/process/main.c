/* 
* @Author: ChangingP
* @Date:   2015-03-26 22:41:39
* @Last Modified by:   ChangingP
* @Last Modified time: 2015-04-06 16:05:39
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <memory.h>
#include <ztstring.h>
#include "ztprocess.h"

void bye(void)
{
	printf("here is func bye\n");
}

void * test(void* args)
{
	printf("hello world\n");
	sleep(3);
	ZTProcess_AtExit(bye);

	return NULL;
}

int main(int argc, char const *argv[])
{
	int pid = 0;

	pid = ZTProcess_Fork(test,NULL);

	printf(" fork pid = %d \n",pid);
	ZTProcess_Wait(pid,NULL);

	return 0;
}
