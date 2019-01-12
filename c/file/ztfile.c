#include <sys/types.h> 
#include <dirent.h> 
#include <unistd.h> 
#include <stdio.h>   
#include <errno.h>
#include <memory.h>
#include <fcntl.h>
#include <sys/stat.h>

/*
	搜索 x 路径下的 y 后缀文件
	# pi_caSPath 文件搜索路劲
	# pi_caSName 文件后缀名 
	# po_caFName 匹配的文件名

	只返回第一个匹配的文件
 */
int ZT_FileSearch(char * pi_caSPath,char *pi_caSName,char * po_caFName)
{
	char * p = NULL;
    DIR	*dir = NULL;      
    struct dirent *ptr = NULL;

    dir = opendir(pi_caSPath);
	if(dir == NULL )
	{
		printf(" opendir %s failed,errno = %d ！\n",pi_caSPath,errno);
		return -2;
	}	
	
    while((ptr = readdir(dir)) != NULL)     
	{		
        printf("d_name: %s\n", ptr->d_name);
		p = strstr(ptr->d_name,pi_caSName);
		if(p != NULL)
		{
			strcpy(po_caFName,ptr->d_name);
			closedir(dir);     
			return 0;
		}
	}
	
    closedir(dir);     
    return -1; 
}

/*
	文件分割复制
	# p_caOriginFile 源文件
	# p_caDestFile 目标文件
	# p_iOffsetS 复制起始地址
	# p_iLen 复制长度 
		=-1 复制到文件尾
*/
int ZT_FileCopy(char * p_caOriginFile,char * p_caDestFile,int p_iOffsetS,int p_iLen)
{
	int fdA = 0,fdB = 0,iOffset = 0;
	struct stat st;

	unsigned char * pSource = NULL;
	
	memset(&st, 0x00, sizeof(struct stat));

	if(0 != stat(p_caOriginFile, &st))
	{
		printf("Failed to get length of [%s]!", p_caOriginFile);
		return -1;
	}
	printf("st.st_size = %d p_iOffsetS = %d p_iLen = %d n",(int)st.st_size,p_iOffsetS,p_iLen);

	//参数验证
	if( p_iOffsetS > st.st_size)
	{
		return -2;
	}
	
	//长度值小于0 复制到文件尾
	if(p_iLen <= 0)
	{
		iOffset = st.st_size - p_iOffsetS;
	}
	else
	{
		//偏移地址 + 长度超出 文件总长度 复制到文件尾
		if(p_iOffsetS + p_iLen > st.st_size )
		{
			iOffset = st.st_size - p_iOffsetS;
		}
		else if(p_iOffsetS + p_iLen <= st.st_size )
		{
			iOffset = p_iLen;
		}
	}
	

	if((fdA = open(p_caOriginFile, O_RDONLY) )< 0)
	{
		printf("open %s failed ,errno = %d\n",p_caOriginFile,errno);
		goto ERR;
	}

	if((fdB = open(p_caDestFile, O_WRONLY|O_CREAT|O_TRUNC) )< 0)
	{
		printf("open %s failed ,errno = %d\n",p_caDestFile,errno);
		goto ERR;
	}

	pSource = malloc(iOffset);
	if(pSource == NULL)
	{
		printf("malloc %d Failed,iOffset = %d \n",__func__,__LINE__,iOffset);
		goto ERR;
	}
	memset(pSource,0,iOffset);

	lseek(fdA, p_iOffsetS, SEEK_SET); 

	if( iOffset != read(fdA,pSource,iOffset))
	{
		printf("read %s error\n",p_caOriginFile);
		goto ERR;
	}

	if(	iOffset != write(fdB,pSource,iOffset))
	{
		printf("write %s error\n",p_caDestFile);
		goto ERR;
	}		

	if(pSource != NULL)
	{	
		free(pSource);
	}

	if(fdA != 0)
	{
		close(fdA);
	}
	
	if(fdB != 0)
	{
		close(fdB);
	}
	
	return 0;
ERR:
	if(pSource != NULL)
	{	
		free(pSource);
	}

	if(fdA != 0)
	{
		close(fdA);
	}
	
	if(fdB != 0)
	{
		close(fdB);
	}
	return -1;
}

/*
	取得文件大小
 */
int ZT_FileSize(char * p_caFileName)
{
	int iSize = 0;
    FILE * fp = NULL;
	
	fp= fopen(p_caFileName, "r");   
	if(fp == NULL)
	{
		return -1;
	}
	
    fseek(fp, 0L, SEEK_END);   
    iSize = ftell(fp);   
    fclose(fp);  
		
    return iSize;   
}
