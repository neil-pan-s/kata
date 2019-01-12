/**
* @file sha1.c
* @brief 采用SHA1计算摘要

*/
//#include "stdafx.h"
#include <stdio.h>
#include <string.h>


unsigned long H0=0x67452301;
unsigned long H1=0xEFCDAB89;
unsigned long H2=0x98BADCFE;
unsigned long H3=0x10325476;
unsigned long H4=0xC3D2E1F0;

unsigned long K[4]={0x5A827999,0x6ED9EBA1,0x8F1BBCDC,0xCA62C1D6};

//////////////////////////////////////////////////////////////
//function 1:	Generate Message									//
//input:														//
//	in:		Original message									//
//	inlen:	length of Original message							//
//output:														//
// out:		message(64byte)									//
//////////////////////////////////////////////////////////////
void GenerateMSG(unsigned char *in, int inlen, unsigned char *out, int outlen)
{
	int i;

	memset(out,0x00,outlen);
	memcpy(out,in,inlen);
	out[inlen]=0x80;
	i=(inlen+8)/64+1;
	out[outlen-3]=(inlen*8)/(256*256);
	out[outlen-2]=(inlen*8)/256;
	out[outlen-1]=(inlen*8)%256;
}

//////////////////////////////////////////////////////////////
//function 2:	logical function									//
//input:														//
//	B:	word32												//
//	C:	word32												//
//	D:	word32												//
//output:														//
// out:	word32												//
//function 3 and 5 is same, All use logical function 2					//
//////////////////////////////////////////////////////////////
unsigned long LFunc(unsigned long B,unsigned long C,unsigned long D,int type)
{
	if(type<=19&&type>=0)			return (B&C)|(~B&D);
	else if(type<=39&&type>=20)		return B^C^D;
	else if(type<=59&&type>=40)		return (B&C)|(B&D)|(C&D);
	else 							return B^C^D;
}

//////////////////////////////////////////////////////////////
//function 3:	COMPUTING THE MESSAGE DIGEST					//
//input:														//
//	in:		MSG												//
//	inlen:	length of MSG										//
//output:														//
// out:		dgt												//
//////////////////////////////////////////////////////////////

unsigned long  SFunc(unsigned long x,int n)
{
	return ((x<<n)|(x>>(32-n)));
}


/**
* @fn CalcMsgDigest
* @brief 采用SHA1计算摘要

* @param (in)	char *message  		需要摘要的数据
* @param (in)	int len				数据长度
* @param (out)	unsigned char *res	计算出的摘要
* @return  void
*/ 
unsigned char msgtmp[2048];
unsigned long W[80];
void CalcMsgDigest(unsigned char *message, int len, unsigned char *digest)
{
	int block,msgtmplen;//,padding;
	int i,j,k;
	unsigned long wtmp1,wtmp2;
	unsigned long h0,h1,h2,h3,h4;
	unsigned long A,B,C,D,E;
 
	h0=H0;
	h1=H1;
	h2=H2;
	h3=H3;
	h4=H4;
	block=(len+8)/64;
	msgtmplen=((len+8)/64+1)*64;
	GenerateMSG(message, len, msgtmp, msgtmplen);
	for(j=0;j<block+1;j++)
	{
		memset(W,0,80);
		A=h0;
		B=h1;
		C=h2;
		D=h3;
		E=h4;
		for(i=0;i<16;i++)
		{
				for(k=0;k<4;k++)
				{
					W[i]|=(unsigned long)(msgtmp[4*i+64*j+k]);
					if(k<3)	W[i]=W[i]<<8;
				}
		}
		for(i=16;i<80;i++)
		{
			wtmp1=W[i-3]^W[i-8]^W[i-14]^W[i-16];
			W[i]=SFunc(wtmp1,1);
		}
		for(i=0;i<80;i++)
		{
			wtmp2=SFunc(A,5)+LFunc(B,C,D,i)+E+W[i]+K[i/20];
			E=D;
			D=C;
			C=SFunc(B,30);
			B=A;
			A=wtmp2;
		}
		h0+=A;
		h1+=B;
		h2+=C;
		h3+=D;
		h4+=E;
	}

	for(i=0;i<4;i++)	digest[i]=(h0<<(i*8))>>24;
	for(i=0;i<4;i++)	digest[i+4]=(h1<<(i*8))>>24;
	for(i=0;i<4;i++)	digest[i+8]=(h2<<(i*8))>>24;
	for(i=0;i<4;i++)	digest[i+12]=(h3<<(i*8))>>24;
	for(i=0;i<4;i++)	digest[i+16]=(h4<<(i*8))>>24;
}
void _sha1(unsigned char * inbuf, int inlen, unsigned char * digest)
{

  	CalcMsgDigest(inbuf, inlen, digest);

}


int sha1_demo()
{
	int i=0;
	unsigned char caTmp[1024]={0};
	unsigned char caOut[1024]={0};

	memcpy(caTmp,"\x05\x01\x03\x02\x02\x40\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xBB\xED\x4E\xD2\x1C",110);
	
	_sha1(caTmp,110,caOut);
	
	printf("_sha1 = \n");
	for(i=0;i<20;i++)
	{
		printf("%02x",caOut[i]);
	}
	printf("\n");
	
	//正确结果 = 25831F162812FBE5F7B7664E634C3E525AA77060
	
	while(1);
	return 0;
}




