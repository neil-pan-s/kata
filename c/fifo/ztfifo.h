#ifndef __ZTFIFO_H__
#define __ZTFIFO_H__

/*
	有名管道通信
	通信数据格式:	1字节长度(hex) + 内容
 */


/*特别注意写管道时，设置打开管道文件的格式必须为可写*/
// #define FIFO_SERVER_W "fifo_hw_sr"	//写管道 (主程序)
// #define FIFO_SERVER_R "fifo_hr_sw"	//读管道 (主程序)

/*在这里设置打开管道文件的mode为只读形式*/
#define FIFOMODE (O_CREAT | O_RDWR | O_NONBLOCK)

#define RDWRMODE (O_RDWR | O_NONBLOCK)
#define RDMODE (O_RDONLY  | O_NONBLOCK)
#define WRMODE (O_WRONLY  | O_NONBLOCK)

int ZTFifo_init(char * p_caFifoName);
int ZTFifo_write(char *p_caFifoName,char * p_caCmd,int p_iLen);
int ZTFifo_read(char *p_caFifoName,char * p_caCmd,int timeout);

#endif