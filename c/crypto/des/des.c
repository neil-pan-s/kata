#include "des.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned char fill_char[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//----密钥生成------
//去除64位密码中作为奇偶校验位的第8、16、24、32、40、48、56、64位,
//剩下的56位作为有效输入密钥
//等分密钥结构体。将密钥分成两个28位的部分，以36为分界点,分为A、B两个部分
const unsigned char KPe[57] = { 0,
	57, 49, 41, 33, 25, 17, 9,
	1,  58, 50, 42, 34, 26, 18,
	10, 2,  59, 51, 43, 35, 27,
	19, 11, 3,  60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7,  62, 54, 46, 38, 30, 22,
	14, 6,  61, 53, 45, 37, 29,
	21, 13, 5,  28, 20, 12, 4};

//密钥移位记录结构体
//DES算法的密钥是经过16次迭代得到一组密钥的.
//移位结构体，表示的是在第i次迭代时密钥循环左移的位数.
//比如在第1次迭代时密钥循环左移1位,第3次迭代时密钥循环左移2位.
//这样得到新的两组各长28位的值:a[i]、b[i]
const unsigned char Shifts[17] = {	0,
	1, 1, 2, 2, 2, 2, 2, 2,
	1, 2, 2, 2, 2, 2, 2, 1 };

//密钥选取结构体
//将第i次迭代生成的两个28位长的密钥为a[i],b[i]合并
//合并后得到新的56位密钥：c[i]=a[1]a[2]...a[28]b[1]b[2]...b[28]
//该结构体表示：新的密钥的选取位置。即新密钥的第1位为56位c[i]的第14位
//第2位为c[i]的17位......，依次类推，新密钥的48位为56位密钥的32位
//生成与进行第i次迭代加密的数据进行按位异或的48位使用密钥
const unsigned char CPe[49] = { 0,
	14, 17, 11, 24,  1,  5,  3, 28,
	15,  6, 21, 10,	23, 19, 12,  4,
	26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40,
	51, 45, 33, 48,	44, 49, 39, 56,
	34, 53, 46, 42, 50, 36, 29, 32 };

//迭代
//DES算法密钥生成需要进行16次迭代,在完成16次迭代前,循环执行第2、3步.
//最终形成16套加密密钥:key[0] , key[1] , key[2] ,…. key[14] , key[15]
//即每迭代一次，选取一次

//------数据加密操作--------
//取得数据
//将明文数据，分成64位的数据块，不足64位，以适当形式补齐

//初始换位结构体
//即把输入的64位数据的原第58位换到第一位,原第50位换到第二位，...，
//依此类推,最后得到新的64位数据. 成为初始时的new_data
const unsigned char IPe[65] = { 0,
	58, 50, 42, 34, 26, 18, 10,  2,
	60, 52, 44, 36, 28, 20, 12,  4,
	62, 54, 46, 38, 30, 22, 14,  6,
	64, 56, 48, 40, 32, 24, 16,  8,
	57, 49, 41, 33, 25, 17,  9,  1,
	59, 51, 43, 35, 27, 19, 11,  3,
	61, 53, 45, 37, 29, 21, 13,  5,
	63, 55, 47, 39, 31, 23, 15,  7 };

//叠代操作：
//第一次迭代以newData作为输入数据,第i(i > 1)次迭代以第i-1次的64位输出数据为
//输入数据,把64位数据按位置等分成左右两部分:
//left = D1D2......D32          right = D33D34......D64
//保持left不变. 利用扩展结构体，把right由32位扩展成48位.
//数据扩展结构体
//把扩展后的48位right与第i次迭代生成的48位加密密钥进行按位异或操作
//形成一个新的48位的right
const unsigned char EPe[49] = { 0,
	32,  1,  2,  3,  4,  5,  4,  5,
	6,  7,  8,  9,	 8,  9, 10, 11,
	12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21,
	22, 23, 24, 25,	24, 25, 26, 27,
	28, 29, 28, 29, 30, 31, 32,  1 };

//数据压缩
const unsigned char SBox[8][4][16] = {
    {{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
	 {0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
	 {4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
	{15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}},

	{{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
	 {3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
	 {0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
	{13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}},

	{{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
	{13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
	{13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
	 {1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}},

	 {{7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
	{13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
	{10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
	 {3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}},

	 {{2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
	{14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
	 {4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
	{11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}},

	{{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
	{10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
	 {9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
	 {4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}},

	 {{4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
	{13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
	 {1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
	 {6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}},

	{{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
	 {1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
	 {7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
	 {2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}}
};

//数据换位
const unsigned char PBox[33] = {0,
	16, 7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
	 2, 8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11,  4, 25
};

//数据整理
const unsigned char FPe[65] = { 0,
	40,  8, 48, 16, 56, 24, 64, 32,	39,  7, 47, 15, 55, 23, 63, 31,
	38,  6, 46, 14, 54, 22, 62, 30,	37,  5, 45, 13, 53, 21, 61, 29,
	36,  4, 44, 12, 52, 20, 60, 28,	35,  3, 43, 11, 51, 19, 59, 27,
	34,  2, 42, 10, 50, 18, 58, 26,	33,  1, 41,  9, 49, 17, 57, 25 };

////////////////////////////////////////////////////////////////////////////////

union KEY56Bits
{
	struct
	{
		unsigned char NoUse;
		unsigned char C[28];
		unsigned char D[28];
	}s;
	unsigned char Key[57];
};

union TEXT64Bits
{
	unsigned char Text[65];
	struct
	{
		unsigned char L[33];
		unsigned char NoUse[32];
	}sL;
	struct
	{
		unsigned char NoUse[32];
		unsigned char R[33];
	}sR;
};

union TEXT48Bits
{
	struct
	{
		unsigned char NoUse;
		unsigned char B[8][6];
	}s;
	unsigned char Text[49];
};

void BitsToBytes( unsigned char *DataInBit, unsigned char *DataInByte, int BitsNum );
void BytesToBits( unsigned char *DataInByte, unsigned char *DataInBit, int BytesNum );
void DesSubkey( unsigned char *key,unsigned char Subkey[17][49]);
int DesProcess( unsigned char *inData, unsigned char *outData,
				unsigned char *Key64Bits, int flag );
int DesEncrypt( unsigned char *Plaintext, unsigned char *Ciphertext, unsigned char *Key64Bits );
int DesDecrypt( unsigned char *Ciphertext, unsigned char *Plaintext, unsigned char *Key64Bits );
int GenerateDesCiphertext( unsigned char *Plaintext, unsigned char *Ciphertext,
				int TextLen, unsigned char *Key8Bytes, unsigned char *vec );
int GenerateDesPlaintext( unsigned char *Ciphertext, unsigned char *Plaintext,
			int CiphertextLen, unsigned char *Key8Bytes, unsigned char *vec );
int TripleDesEncrypt( unsigned char *Plaintext, unsigned char *Ciphertext,
			unsigned char *Key24Bits);
int TripleDesDecrypt( unsigned char *Ciphertext, unsigned char *Plaintext,
			unsigned char *Key24Bits);
int Generate3DesCiphertext( unsigned char *Plaintext, unsigned char *Ciphertext,
			int TextLen, unsigned char *Key16Bytes, unsigned char *vec );
int Generate3DesPlaintext( unsigned char *Ciphertext, unsigned char *Plaintext,
			int TextLen, unsigned char *Key16Bytes, unsigned char *vec );

//**:***************************************************************************
//**:功能：将输入字符串的每一位转变成一个字符([000]或[0001])——注意不是字符0/1
//**:           如：将字符'A'(1000001)转换成为'0''1''0''0''0''0''0''1'
//**:输入：DataInBit:要转换的字符串
//**:       bitsNum：要转换的字节数*8，即DataInBit的长度乘以8
//**:输出：DataInByte：转换后得到的字符串(可能是不见字符)
//*:***************************************************************************/
void BitsToBytes( unsigned char *DataInBit, unsigned char *DataInByte, int BitsNum )
{
	int i;
	unsigned char Pos[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };

	for( i = 0; i < BitsNum; i++ )
	{
		//如果对应位为1，则为1，否则为0
		DataInByte[i] = ( DataInBit[ i / 8 ] & Pos[ i % 8 ] ) ? 0x01 : 0x00;
	}
}
//**:***************************************************************************
//**:功能：BitsToBytes的逆过程：将二进制形式的字符串，转换成为字节型。
//**:输入：DataInByte:用二进制形式表示的字符串， BytesNum：DataInByte的长度.
//**:输出：DataInBit：转换后得到的字符串。
//*:***************************************************************************/
void BytesToBits( unsigned char *DataInByte, unsigned char *DataInBit, int BytesNum )
{
	int i;
	unsigned char Pos[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };

	for( i = 0; i <= ( BytesNum - 1 ) / 8; i++ )
		DataInBit[i] = 0x00;
	for( i = 0; i < BytesNum; i++ )
		DataInBit[ i / 8 ] |= ( DataInByte[i] * Pos[ i % 8 ] );
}

//**:***************************************************************************
//**:功能：1. 提取有效密钥。  2. 对密钥进行16次迭代运算
//**:       3. 进行密钥选取，得到16组加密密钥
//**:**************************************************************************/
void DesSubkey( unsigned char *key,unsigned char Subkey[17][49])
{
	int i, j;
	union KEY56Bits TKey;
	unsigned char tmp[28];

	for( i = 1; i <= 56; i++ )
		TKey.Key[i] = key[KPe[i]];      //利用等分密钥结构体，提取有效输入密钥

	for( i = 1; i <= 16; i++ )  //循环进行16次迭代
	{
        //第i次迭代前，保留密钥前需要左移的Shifts[i]个字符
		memcpy( tmp, TKey.s.C, Shifts[i] );
		//将密钥左依指定位数
		memcpy( TKey.s.C, TKey.s.C + Shifts[i], 28 - Shifts[i] );
		//将保留的前Shifts[i]个字符追加到后面
		memcpy( TKey.s.C + 28 - Shifts[i], tmp, Shifts[i] );

		memcpy( tmp, TKey.s.D, Shifts[i] );
		memcpy( TKey.s.D, TKey.s.D + Shifts[i], 28 - Shifts[i] );
		memcpy( TKey.s.D + 28 - Shifts[i], tmp, Shifts[i] );

		//根据密钥选取矩阵,得到迭代后的第i组加密密钥.每组加密密钥为48个元素
		for( j = 1; j <= 48; j++ )
			Subkey[i][j] = TKey.Key[CPe[j]];
	}
}

//**:***************************************************************************
//**:功能：DES加密/解密
//**:参数:	inData:明文/密文,必须为8byte
//**:		outData:加密后的密文/解密后的明文,8byte
//**:		Key64Bits:密钥,8Bytes
//**:       flag:flag=1表示加密,flag=2表示解密
//**:**************************************************************************/
int DesProcess( unsigned char *inData, unsigned char *outData,
				unsigned char *Key64Bits, int flag )
{
	int i, j;
	int m, n;
	unsigned char Rep;
    unsigned char Key64Bytes[65],SText[33],PText[33];
    unsigned char Subkey[17][49];
    union TEXT64Bits TextInByte,TextInByte2,TmpText[18];
    union TEXT48Bits EText,XText;

	//将8字节密钥信息转换成为64Bytes形式
	BitsToBytes( Key64Bits, Key64Bytes + 1, 64 );
	//进行密钥选取，得到16组加密密钥
	DesSubkey( Key64Bytes,Subkey);
	//将8字节明文/密文信息，转换成为64Bytes形式
	BitsToBytes( inData, TextInByte.Text + 1, 64 );

	//将明文/密文进行初始换位处理. IPe是初始换位矩阵
	for( i = 1; i <= 64; i++ )
		TmpText[0].Text[i] = TextInByte.Text[ IPe[i] ];
	//进行16次迭代运算
	for( i = 1; i <= 16; i++ )
	{
		//将右边原始的32位部分赋值给左边的32位
		for( j = 1; j <= 32; j++ )
			TmpText[i].sL.L[j] = TmpText[i-1].sR.R[j];

		//将右边的32位数据进行扩展,扩展为48位
		for( j = 1; j <= 48; j++ )
			EText.Text[j] = TmpText[i-1].sR.R[ EPe[j] ];
		//将第i次扩展得到的右边48位数据，与第i次迭代得到的加密密钥进行异或运算
		if(flag==1)     //第i次迭代加密时,使用第i组密钥
			for( j = 1; j <= 48; j++ )
				XText.Text[j] = EText.Text[j] ^ Subkey[i][j];
		else            //第i次迭代解密时,使用第17-i组密钥
		    for( j = 1; j <= 48; j++ )
				XText.Text[j] = EText.Text[j] ^ Subkey[17-i][j];

		for( j = 0; j < 8; j++ )
		{
			//?不明白为什么这样计算
			m = XText.s.B[j][0] * 2 + XText.s.B[j][5];
			n = XText.s.B[j][1] * 8 + XText.s.B[j][2] * 4 + XText.s.B[j][3] * 2 + XText.s.B[j][4];
			//将利用数据压缩矩阵取得的值，左移4位(压缩矩阵中的数据都是0~15，左移4位不会
			//	造成数据丢失，从而实现了数据压缩)
			Rep = SBox[j][m][n] << 4;
			//将压缩后的数据存放到变量中,最后得到一个32位的Bytes字符串
			BitsToBytes( &Rep, SText + 4 * j + 1, 4 );
		}
		//利用数据换位结构体,进行32位Bytes的换位处理
		for( j = 1; j <= 32; j++ )
			PText[j] = SText[ PBox[j] ];
		//将计算得到的32位Bytes与本轮计算的原始的左边的32位进行异或运算,
		//将得到的32位作为本轮计算得到的右边的32位值
		for( j = 1; j <= 32; j++ )
			TmpText[i].sR.R[j] = TmpText[i-1].sL.L[j] ^ PText[j];
	}

	//为保证加密和解密的对称性,DES算法的前15次迭代,每完成一次迭代都要交
	//第换left和right的值,16次迭代不交换两者的数值
	//但前面的算法是已经交换了第16次迭代时左右两边的数据的,所以此处将左右换回来
	for( i = 1; i <= 32; i++ )
	{
		TmpText[17].sL.L[i] = TmpText[16].sR.R[i];
		TmpText[17].sR.R[i] = TmpText[16].sL.L[i];
	}

	//利用数据整理矩阵进行数据整理
	for( i = 1; i <= 64; i++ )
		TextInByte2.Text[i] = TmpText[17].Text[ FPe[i] ];

	//将整理后的数据,转换成为Bit,从而得到密文或明文
	BytesToBits( TextInByte2.Text + 1, outData, 64 );

	return 0;
}

///////////////////////////////////Des加密、解密////////////////////////////////
//**:***************************************************************************
//**:功能：8字节DES加密
//**:参数:	Plaintext:明文,必须为8byte
//**:		Ciphertext:加密后的密文,8byte
//**:		Key64Bits:密钥,8Bytes
//**:**************************************************************************/
int DesEncrypt( unsigned char *Plaintext, unsigned char *Ciphertext, unsigned char *Key64Bits )
{
    return DesProcess(Plaintext,Ciphertext,Key64Bits,1);
}
//**:***************************************************************************
//**:功能：8字节DES解密
//**:参数:	Ciphertext:密文,必须为8byte
//**:		Plaintext:解密后的明文,8byte
//**:		Key64Bits:密钥,8Bytes
//**:**************************************************************************/
int DesDecrypt( unsigned char *Ciphertext, unsigned char *Plaintext, unsigned char *Key64Bits )
{
	return DesProcess(Ciphertext,Plaintext,Key64Bits,2);
}
//**:***************************************************************************
//**:功能：n个8字节DES加密
//**:参数:	Plaintext:待加密的明文
//**:		Ciphertext:密文缓冲区
//**:		TextLen:明文的长度.必须为8的倍数,不足请预先补齐
//**:		Key8Bytes:密钥,8byte
//**:**************************************************************************/
int GenerateDesCiphertext( unsigned char *Plaintext, unsigned char *Ciphertext,
				int TextLen, unsigned char *Key8Bytes, unsigned char *vec )
{
	int i, j, BlockTotal, ch1, ch2;
    unsigned char tmp_vec[9]={0};

	if( ( TextLen % 8 ) != 0 || TextLen == 0 ) return -10033;

	BlockTotal = TextLen / 8;

    if(vec != 0) memcpy(tmp_vec, vec, 8);   //获取初始向量

	for( i = 0; i < BlockTotal; i++ )
	{
		if(vec != 0)    //CBC算法
		{
			//将前一次加密结果与当前明文进行异或,将异或结果去加密
			//第一次加密时使用的是初始向量与明文进行异或
			for(j = 0; j < 8; j++)
			{
                ch1 = tmp_vec[j] & 0xFF;
                ch2 = Plaintext[i * 8 + j] & 0xFF;
				tmp_vec[j] = ch1 ^ ch2;
            }

			//加密
			DesEncrypt( tmp_vec, Ciphertext + i * 8, Key8Bytes );

			//将加密结果放回向量中,供下次以加密使用
			memcpy(tmp_vec, Ciphertext + i * 8, 8);
		}
		else   //ECB算法
			DesEncrypt( Plaintext + i * 8, Ciphertext + i * 8, Key8Bytes );
    }

	return 0;
}
//**:***************************************************************************
//**:功能：n个8字节DES解密
//**:参数:	Ciphertext:待解密文缓冲区
//**:		Plaintext:解密后的明文
//**:		TextLen:密文的长度.必须为8的倍数,不足请预先补齐
//**:		Key8Bytes:密钥,8byte
//**:**************************************************************************/
int GenerateDesPlaintext( unsigned char *Ciphertext, unsigned char *Plaintext,
			int CiphertextLen, unsigned char *Key8Bytes, unsigned char *vec )
{
	int i, j, BlockTotal, ch1, ch2;
	unsigned char tmp_vec[9]={0};
	unsigned char tmp_Plain[9]={0};

	if( ( CiphertextLen % 8 ) != 0 || CiphertextLen == 0 ) return -10033;

	BlockTotal = CiphertextLen / 8;

	if(vec != 0) memcpy(tmp_vec, vec, 8);

	for( i = 0; i < BlockTotal; i++ )
	{
		if(vec != 0)   //CBC算法
		{
			//解密
			DesDecrypt( Ciphertext + i * 8, tmp_Plain, Key8Bytes );

			//解密结果与向量异或,得到解密数据
			for(j = 0; j < 8; j++)
			{
                ch1 = tmp_vec[j] & 0xFF;
                ch2 = tmp_Plain[j] & 0xFF;
				Plaintext[i * 8 + j] = ch1 ^ ch2;
            }

			//将前一次的密文放回向量,供下一次解密是使用
			memcpy(tmp_vec, Ciphertext + i * 8, 8);
		}
		else  //ECB算法
			DesDecrypt( Ciphertext + i * 8, Plaintext + i * 8, Key8Bytes );
	}

	return 0;
}

///////////////////////////////////3Des加密、解密///////////////////////////////
//**:***************************************************************************
//**:功能：8字节3DES加密
//**:参数:	Plaintext:明文,必须为8byte
//**:		Ciphertext:加密后的密文,必须为8byte
//**:		Key24Bits:密钥,24Bytes
//**:**************************************************************************/
int TripleDesEncrypt( unsigned char *Plaintext, unsigned char *Ciphertext,
			unsigned char *Key24Bits)
{
	unsigned char PText1[8];
	unsigned char PText2[8];

	DesEncrypt( Plaintext, PText1, Key24Bits );
	DesDecrypt( PText1, PText2, Key24Bits + 8 );
	DesEncrypt( PText2, Ciphertext, Key24Bits + 16 );

	return 0;
}
//**:***************************************************************************
//**:功能：8字节3DES解密
//**:参数:	Ciphertext:密文,必须为8byte
//**:		Plaintext:解密后的明文,8byte
//**:		Key64Bits:密钥,16Bytes
//**:**************************************************************************/
int TripleDesDecrypt( unsigned char *Ciphertext, unsigned char *Plaintext,
			unsigned char *Key24Bits)
{
	unsigned char PText1[8];
	unsigned char PText2[8];

	DesDecrypt( Ciphertext, PText1, Key24Bits + 16 );
	DesEncrypt( PText1, PText2, Key24Bits + 8 );
	DesDecrypt( PText2, Plaintext, Key24Bits );

	return 0;
}
//**:***************************************************************************
//**:功能：n个8字节3DES加密数据
//**:输入:	Plaintext:待加密的明文
//**:		Ciphertext:密文缓冲区
//**:		TextLen:明文的长度
//**:		Key16Bytes:密钥,16byte
//**:***************************************************************************
int Generate3DesCiphertext( unsigned char *Plaintext, unsigned char *Ciphertext,
			int TextLen, unsigned char *Key24Bytes, unsigned char *vec )
{
	int i, j, BlockTotal, ch1 ,ch2;
	unsigned char tmp_vec[9]={0};

	if(vec != 0) memcpy(tmp_vec, vec, 8);   //获取初始向量

	if( ( TextLen % 8 ) != 0 || TextLen == 0 ) return -10033;

	BlockTotal = TextLen / 8;

	for( i = 0; i < BlockTotal; i++ )
	{
		if(vec != 0)  //CBC 算法
		{
			//将前一次加密结果与当前明文进行异或,将异或结果去加密
			//第一次加密时使用的是初始向量与明文进行异或
			for(j = 0; j < 8; j++)
			{
                ch1 = tmp_vec[j] & 0xFF;
                ch2 = Plaintext[i * 8 + j] & 0xFF;
				tmp_vec[j] = ch1 ^ ch2;
            }

			//加密
			TripleDesEncrypt( tmp_vec, Ciphertext + i * 8, Key24Bytes );

			//将加密结果放回向量中,供下次以加密使用
			memcpy(tmp_vec, Ciphertext + i * 8, 8);
		}
		else  //ECB 算法
			TripleDesEncrypt( Plaintext + i * 8, Ciphertext + i * 8, Key24Bytes );
	}

	return 0;
}
//**:***************************************************************************
//**:功能：n个8字节3DES解密数据
//**:输入:	Plaintext:输出的明文
//**:		Ciphertext:密文缓冲区
//**:		TextLen:明文的长度
//**:		Key16Bytes:密钥,16byte
//**:***************************************************************************
int Generate3DesPlaintext( unsigned char *Ciphertext, unsigned char *Plaintext,
			int TextLen, unsigned char *Key24Bytes, unsigned char *vec )
{
	int i, j, BlockTotal, ch1, ch2;
	unsigned char tmp_vec[9]={0};
	unsigned char tmp_Plain[9]={0};

	if(vec != 0) memcpy(tmp_vec, vec, 8);   //获取初始向量

	if( ( TextLen % 8 ) != 0 || TextLen == 0 ) return -10033;

	BlockTotal = TextLen / 8;

	for( i = 0; i < BlockTotal; i++ )
	{
		if(vec != 0)   //CBC算法
		{
			//解密
			TripleDesDecrypt( Ciphertext + i * 8, tmp_Plain, Key24Bytes );

			//解密结果与向量异或,得到解密数据
			for(j = 0; j < 8; j++)
			{
                ch1 = tmp_vec[j] & 0xFF;
                ch2 = tmp_Plain[j] & 0xFF;
				Plaintext[i * 8 + j] = ch1 ^ ch2;
            }

			//将前一次的密文放回向量,供下一次解密是使用
			memcpy(tmp_vec, Ciphertext + i * 8, 8);
		}
		else  //ECB算法
			TripleDesDecrypt( Ciphertext + i * 8, Plaintext + i * 8, Key24Bytes );
	}

	return 0;
}


/////////////////////以下为对外接口/////////////////////////////////////////////
/*[method*******************************************************************************
 *def:  public int des(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec=NULL)
 *func:
        对指定字符串,使用指定密钥,执行DES/3DES加密处理.数据不能超过8192字节长度.
        当密钥是8字节时,使用des加密,密钥是16字节时,使用3des加密.
 *args:
        #src      需要加密的源数据
        #key      加密的密钥
        #src_len  源数据长度
        #key_len  密钥长度8/16,8:执行des加密 16：执行3DES加密
 *output:
        #dst    加密后的数据
 *ret:
        =0 成功
        其它 失败
*************************************************************************************]*/
int des(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec)
{
	int fill_len=0;
	unsigned char tmp_buff[8192];
	unsigned char key24byte[25]={0};

	memset(tmp_buff, 0x00, sizeof(tmp_buff));
	memcpy(tmp_buff, src, src_len);
	if(0<(src_len % 8))		//不是8的倍数,进行补齐
	{
    	fill_len = (8 - src_len % 8);		//取得需要补齐的字节数
		memcpy(tmp_buff+src_len, fill_char, fill_len);	//补齐为8的倍数
	}
	fill_len = fill_len + src_len;		//取得补齐后的实际长度
	if(key_len==8)		//DES加密
	{
		return GenerateDesCiphertext(tmp_buff, dst, fill_len, key, vec );
	}
	if(key_len==16)		//2倍3DES加密
	{
        memcpy(key24byte, key, 16);
        memcpy(key24byte+16, key, 8);
		return Generate3DesCiphertext(tmp_buff, dst, fill_len, key24byte, vec );
	}
	if(key_len==24)     //3倍3DES加密
    {
        return Generate3DesCiphertext(tmp_buff, dst, fill_len, key, vec );
    }
	return -10032;
}

/*[method*******************************************************************************
 *def:  public int undes(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec=NULL)
 *func:
        对指定字符串,使用指定密钥,执行DES/3DES解密处理,当密钥为8字节时使用des
        解密,密钥为16字节时使用3des解密.
 *args:
        #src      需要解密的源数据
        #key      解密的密钥
        #src_len  源数据长度
        #key_len  密钥长度8/16,8:执行des解密 16：执行3DES解密
 *output:
        #dst    解密后的数据
 *ret:
        =0 成功
        其它 失败
*************************************************************************************]*/
int undes(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec)
{
    unsigned char key24byte[25]={0};

	if(0<(src_len % 8)) return -10033;		//不是8的倍数,错误

	if(key_len==8)		//DES加密
	{
		return GenerateDesPlaintext(src, dst, src_len, key, vec );
	}
	if(key_len==16)		//2倍3DES加密
	{
        memcpy(key24byte, key, 16);
        memcpy(key24byte+16, key, 8);
		return Generate3DesPlaintext(src, dst, src_len, key24byte, vec );
	}
	if(key_len==24)		//3倍3DES加密
	{
		return Generate3DesPlaintext(src, dst, src_len, key, vec );
	}
	return -10034;
}
