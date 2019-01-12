#ifndef __SHA1_H__
#define __SHA1_H__
extern void CalcMsgDigest(unsigned char *message, int len, unsigned char *digest);
extern void _sha1(unsigned char * inbuf, int inlen, unsigned char * digest);
#endif

