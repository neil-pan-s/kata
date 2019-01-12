#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "ztfifo.h"

/*
    有名管道创建
 */
int ZTFifo_init(char * p_caFifoName)
{

    /*创建有名管道，设置为可读写，无阻塞，如果不存在则按照指定权限创建*/
    if ((mkfifo(p_caFifoName, FIFOMODE) < 0) && (errno != EEXIST)) 
    {
        return -1;
    }
    return 0;
}

/*
    写管道接口
    写数据格式  1字节长度(hex) + 内容
 */
int ZTFifo_write(char *p_caFifoName, char * p_caCmd, int p_iLen)
{
    int fd = 0;
    int nwrite = 0;

    /*打开管道文件，可写非阻塞*/
    if ((fd = open(p_caFifoName, WRMODE)) < 0) 
    {
        printf("open fifo_name %s failed \n", p_caFifoName);
        return -1;
    }

    if (p_iLen <= 0) 
    {
        close(fd);
        return -2;
    }

    /*向管道文件中写入数据*/
    if ((nwrite = write(fd, p_caCmd, p_iLen)) < 0) 
    {
        if (errno == EAGAIN) {
            printf("The FIFO has not been read yet.Please try later\n");
            close(fd);
            return -3;
        }
    }

    close(fd);
    return 0;
}


/*
    读管道接口
    读数据格式  1字节长度(hex) + 内容
 */
int ZTFifo_read(char *p_caFifoName, char * p_caCmd, int timeout)
{
    int  fd = 0, iCmdLen = 0,iLen = 0,z = 0;
    char readbuf[512] = {0};
    time_t begin = 0; //记录开始时间

    memset(readbuf, 0, sizeof(readbuf));

    /*打开管道文件，可读非阻塞*/
    if ((fd = open(p_caFifoName, RDMODE)) < 0) 
    {
        return -1;
    }

    begin = time(NULL);

    //等待数据
    do
    {

        z = read(fd, readbuf, 1);
        if (z != 1)
        {
            usleep(1000 * 10);
            continue;
        }

        if (readbuf[0] != 0x00)
        {
            //读到开始字节
            iLen += 1;
            break;
        }

        if ((timeout > 0) && ( time(NULL) - begin > timeout ))
        {
            close(fd);
            return -2;
        }

    } while (1);

    iCmdLen = readbuf[0];
    begin = time(NULL);

    do
    {
        z = read(fd, readbuf + iLen, 4);
        if ( z > 0)
        {
            iLen += z;
        }

        if (iLen > iCmdLen) break;


        if ((timeout > 0) && ( time(NULL) - begin > timeout ))
        {

            close(fd);
            return -2;
        }

    } while (1);

    memcpy(p_caCmd, readbuf, iLen);
    close(fd);


    /*读完后清空管道文件*/
    if ((fd = open(p_caFifoName, RDMODE | O_TRUNC)) < 0) {
        printf("TRUNC fifo_name %s failed \n", p_caFifoName);
    } else {
        printf("TRUNC fifo_name %s succ\n", p_caFifoName);
        close(fd);
    }

    return iLen;
}
