#ifndef __ZTFILE_H__
#define __ZTFILE_H__

int ZT_FileSearch(char * pi_caSPath,char *pi_caSName,char * po_caFName);
int ZT_FileCopy(char * p_caOriginFile,char * p_caDestFile,int p_iOffsetS,int p_iOffsetE);
int ZT_FileSize(char * p_caFileName);

#endif