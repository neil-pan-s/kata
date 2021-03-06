#ifndef _MD5_H__
#define _MD5_H__
/* MD5.H - header file for MD5C.C */

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
   rights reserved.

   License to copy and use this software is granted provided that it
   is identified as the "RSA Data Security, Inc. MD5 Message-Digest
   Algorithm" in all material mentioning or referencing this software
   or this function.

   License is also granted to make and use derivative works provided
   that such works are identified as "derived from the RSA Data
   Security, Inc. MD5 Message-Digest Algorithm" in all material
   mentioning or referencing the derived work.

   RSA Data Security, Inc. makes no representations concerning either
   the merchantability of this software or the suitability of this
   software for any particular purpose. It is provided "as is"
   without express or implied warranty of any kind.

   These notices must be retained in any copies of any part of this
   documentation and/or software.

   2007-09-15 Last modified by cheungmine.
 */

/* MD5 context. */
typedef struct {
    unsigned int state[4];                /* state (ABCD) */
    unsigned int count[2];                /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64];    /* input buffer */
} MD5_CTX;

void  MD5_init (MD5_CTX *);
void  MD5_update (MD5_CTX *, const unsigned char *str, unsigned int len);
void  MD5_fini (unsigned char[16], MD5_CTX *);

/*
	MD5 摘要接口
	# str 输入数据
	# len 输入数据长度
	# md5 摘要后MD5值 ASC
*/
int MD5_sign (const unsigned char *str, unsigned int len,unsigned char * md5);

#endif    /* _MD5_H__ */

