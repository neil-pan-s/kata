#include "des.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned char fill_char[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//----��Կ����------
//ȥ��64λ��������Ϊ��żУ��λ�ĵ�8��16��24��32��40��48��56��64λ,
//ʣ�µ�56λ��Ϊ��Ч������Կ
//�ȷ���Կ�ṹ�塣����Կ�ֳ�����28λ�Ĳ��֣���36Ϊ�ֽ��,��ΪA��B��������
const unsigned char KPe[57] = { 0,
	57, 49, 41, 33, 25, 17, 9,
	1,  58, 50, 42, 34, 26, 18,
	10, 2,  59, 51, 43, 35, 27,
	19, 11, 3,  60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7,  62, 54, 46, 38, 30, 22,
	14, 6,  61, 53, 45, 37, 29,
	21, 13, 5,  28, 20, 12, 4};

//��Կ��λ��¼�ṹ��
//DES�㷨����Կ�Ǿ���16�ε����õ�һ����Կ��.
//��λ�ṹ�壬��ʾ�����ڵ�i�ε���ʱ��Կѭ�����Ƶ�λ��.
//�����ڵ�1�ε���ʱ��Կѭ������1λ,��3�ε���ʱ��Կѭ������2λ.
//�����õ��µ��������28λ��ֵ:a[i]��b[i]
const unsigned char Shifts[17] = {	0,
	1, 1, 2, 2, 2, 2, 2, 2,
	1, 2, 2, 2, 2, 2, 2, 1 };

//��Կѡȡ�ṹ��
//����i�ε������ɵ�����28λ������ԿΪa[i],b[i]�ϲ�
//�ϲ���õ��µ�56λ��Կ��c[i]=a[1]a[2]...a[28]b[1]b[2]...b[28]
//�ýṹ���ʾ���µ���Կ��ѡȡλ�á�������Կ�ĵ�1λΪ56λc[i]�ĵ�14λ
//��2λΪc[i]��17λ......���������ƣ�����Կ��48λΪ56λ��Կ��32λ
//��������е�i�ε������ܵ����ݽ��а�λ����48λʹ����Կ
const unsigned char CPe[49] = { 0,
	14, 17, 11, 24,  1,  5,  3, 28,
	15,  6, 21, 10,	23, 19, 12,  4,
	26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40,
	51, 45, 33, 48,	44, 49, 39, 56,
	34, 53, 46, 42, 50, 36, 29, 32 };

//����
//DES�㷨��Կ������Ҫ����16�ε���,�����16�ε���ǰ,ѭ��ִ�е�2��3��.
//�����γ�16�׼�����Կ:key[0] , key[1] , key[2] ,��. key[14] , key[15]
//��ÿ����һ�Σ�ѡȡһ��

//------���ݼ��ܲ���--------
//ȡ������
//���������ݣ��ֳ�64λ�����ݿ飬����64λ�����ʵ���ʽ����

//��ʼ��λ�ṹ��
//���������64λ���ݵ�ԭ��58λ������һλ,ԭ��50λ�����ڶ�λ��...��
//��������,���õ��µ�64λ����. ��Ϊ��ʼʱ��new_data
const unsigned char IPe[65] = { 0,
	58, 50, 42, 34, 26, 18, 10,  2,
	60, 52, 44, 36, 28, 20, 12,  4,
	62, 54, 46, 38, 30, 22, 14,  6,
	64, 56, 48, 40, 32, 24, 16,  8,
	57, 49, 41, 33, 25, 17,  9,  1,
	59, 51, 43, 35, 27, 19, 11,  3,
	61, 53, 45, 37, 29, 21, 13,  5,
	63, 55, 47, 39, 31, 23, 15,  7 };

//����������
//��һ�ε�����newData��Ϊ��������,��i(i > 1)�ε����Ե�i-1�ε�64λ�������Ϊ
//��������,��64λ���ݰ�λ�õȷֳ�����������:
//left = D1D2......D32          right = D33D34......D64
//����left����. ������չ�ṹ�壬��right��32λ��չ��48λ.
//������չ�ṹ��
//����չ���48λright���i�ε������ɵ�48λ������Կ���а�λ������
//�γ�һ���µ�48λ��right
const unsigned char EPe[49] = { 0,
	32,  1,  2,  3,  4,  5,  4,  5,
	6,  7,  8,  9,	 8,  9, 10, 11,
	12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21,
	22, 23, 24, 25,	24, 25, 26, 27,
	28, 29, 28, 29, 30, 31, 32,  1 };

//����ѹ��
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

//���ݻ�λ
const unsigned char PBox[33] = {0,
	16, 7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
	 2, 8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11,  4, 25
};

//��������
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
//**:���ܣ��������ַ�����ÿһλת���һ���ַ�([000]��[0001])����ע�ⲻ���ַ�0/1
//**:           �磺���ַ�'A'(1000001)ת����Ϊ'0''1''0''0''0''0''0''1'
//**:���룺DataInBit:Ҫת�����ַ���
//**:       bitsNum��Ҫת�����ֽ���*8����DataInBit�ĳ��ȳ���8
//**:�����DataInByte��ת����õ����ַ���(�����ǲ����ַ�)
//*:***************************************************************************/
void BitsToBytes( unsigned char *DataInBit, unsigned char *DataInByte, int BitsNum )
{
	int i;
	unsigned char Pos[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };

	for( i = 0; i < BitsNum; i++ )
	{
		//�����ӦλΪ1����Ϊ1������Ϊ0
		DataInByte[i] = ( DataInBit[ i / 8 ] & Pos[ i % 8 ] ) ? 0x01 : 0x00;
	}
}
//**:***************************************************************************
//**:���ܣ�BitsToBytes������̣�����������ʽ���ַ�����ת����Ϊ�ֽ��͡�
//**:���룺DataInByte:�ö�������ʽ��ʾ���ַ����� BytesNum��DataInByte�ĳ���.
//**:�����DataInBit��ת����õ����ַ�����
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
//**:���ܣ�1. ��ȡ��Ч��Կ��  2. ����Կ����16�ε�������
//**:       3. ������Կѡȡ���õ�16�������Կ
//**:**************************************************************************/
void DesSubkey( unsigned char *key,unsigned char Subkey[17][49])
{
	int i, j;
	union KEY56Bits TKey;
	unsigned char tmp[28];

	for( i = 1; i <= 56; i++ )
		TKey.Key[i] = key[KPe[i]];      //���õȷ���Կ�ṹ�壬��ȡ��Ч������Կ

	for( i = 1; i <= 16; i++ )  //ѭ������16�ε���
	{
        //��i�ε���ǰ��������Կǰ��Ҫ���Ƶ�Shifts[i]���ַ�
		memcpy( tmp, TKey.s.C, Shifts[i] );
		//����Կ����ָ��λ��
		memcpy( TKey.s.C, TKey.s.C + Shifts[i], 28 - Shifts[i] );
		//��������ǰShifts[i]���ַ�׷�ӵ�����
		memcpy( TKey.s.C + 28 - Shifts[i], tmp, Shifts[i] );

		memcpy( tmp, TKey.s.D, Shifts[i] );
		memcpy( TKey.s.D, TKey.s.D + Shifts[i], 28 - Shifts[i] );
		memcpy( TKey.s.D + 28 - Shifts[i], tmp, Shifts[i] );

		//������Կѡȡ����,�õ�������ĵ�i�������Կ.ÿ�������ԿΪ48��Ԫ��
		for( j = 1; j <= 48; j++ )
			Subkey[i][j] = TKey.Key[CPe[j]];
	}
}

//**:***************************************************************************
//**:���ܣ�DES����/����
//**:����:	inData:����/����,����Ϊ8byte
//**:		outData:���ܺ������/���ܺ������,8byte
//**:		Key64Bits:��Կ,8Bytes
//**:       flag:flag=1��ʾ����,flag=2��ʾ����
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

	//��8�ֽ���Կ��Ϣת����Ϊ64Bytes��ʽ
	BitsToBytes( Key64Bits, Key64Bytes + 1, 64 );
	//������Կѡȡ���õ�16�������Կ
	DesSubkey( Key64Bytes,Subkey);
	//��8�ֽ�����/������Ϣ��ת����Ϊ64Bytes��ʽ
	BitsToBytes( inData, TextInByte.Text + 1, 64 );

	//������/���Ľ��г�ʼ��λ����. IPe�ǳ�ʼ��λ����
	for( i = 1; i <= 64; i++ )
		TmpText[0].Text[i] = TextInByte.Text[ IPe[i] ];
	//����16�ε�������
	for( i = 1; i <= 16; i++ )
	{
		//���ұ�ԭʼ��32λ���ָ�ֵ����ߵ�32λ
		for( j = 1; j <= 32; j++ )
			TmpText[i].sL.L[j] = TmpText[i-1].sR.R[j];

		//���ұߵ�32λ���ݽ�����չ,��չΪ48λ
		for( j = 1; j <= 48; j++ )
			EText.Text[j] = TmpText[i-1].sR.R[ EPe[j] ];
		//����i����չ�õ����ұ�48λ���ݣ����i�ε����õ��ļ�����Կ�����������
		if(flag==1)     //��i�ε�������ʱ,ʹ�õ�i����Կ
			for( j = 1; j <= 48; j++ )
				XText.Text[j] = EText.Text[j] ^ Subkey[i][j];
		else            //��i�ε�������ʱ,ʹ�õ�17-i����Կ
		    for( j = 1; j <= 48; j++ )
				XText.Text[j] = EText.Text[j] ^ Subkey[17-i][j];

		for( j = 0; j < 8; j++ )
		{
			//?������Ϊʲô��������
			m = XText.s.B[j][0] * 2 + XText.s.B[j][5];
			n = XText.s.B[j][1] * 8 + XText.s.B[j][2] * 4 + XText.s.B[j][3] * 2 + XText.s.B[j][4];
			//����������ѹ������ȡ�õ�ֵ������4λ(ѹ�������е����ݶ���0~15������4λ����
			//	������ݶ�ʧ���Ӷ�ʵ��������ѹ��)
			Rep = SBox[j][m][n] << 4;
			//��ѹ��������ݴ�ŵ�������,���õ�һ��32λ��Bytes�ַ���
			BitsToBytes( &Rep, SText + 4 * j + 1, 4 );
		}
		//�������ݻ�λ�ṹ��,����32λBytes�Ļ�λ����
		for( j = 1; j <= 32; j++ )
			PText[j] = SText[ PBox[j] ];
		//������õ���32λBytes�뱾�ּ����ԭʼ����ߵ�32λ�����������,
		//���õ���32λ��Ϊ���ּ���õ����ұߵ�32λֵ
		for( j = 1; j <= 32; j++ )
			TmpText[i].sR.R[j] = TmpText[i-1].sL.L[j] ^ PText[j];
	}

	//Ϊ��֤���ܺͽ��ܵĶԳ���,DES�㷨��ǰ15�ε���,ÿ���һ�ε�����Ҫ��
	//�ڻ�left��right��ֵ,16�ε������������ߵ���ֵ
	//��ǰ����㷨���Ѿ������˵�16�ε���ʱ�������ߵ����ݵ�,���Դ˴������һ�����
	for( i = 1; i <= 32; i++ )
	{
		TmpText[17].sL.L[i] = TmpText[16].sR.R[i];
		TmpText[17].sR.R[i] = TmpText[16].sL.L[i];
	}

	//��������������������������
	for( i = 1; i <= 64; i++ )
		TextInByte2.Text[i] = TmpText[17].Text[ FPe[i] ];

	//������������,ת����ΪBit,�Ӷ��õ����Ļ�����
	BytesToBits( TextInByte2.Text + 1, outData, 64 );

	return 0;
}

///////////////////////////////////Des���ܡ�����////////////////////////////////
//**:***************************************************************************
//**:���ܣ�8�ֽ�DES����
//**:����:	Plaintext:����,����Ϊ8byte
//**:		Ciphertext:���ܺ������,8byte
//**:		Key64Bits:��Կ,8Bytes
//**:**************************************************************************/
int DesEncrypt( unsigned char *Plaintext, unsigned char *Ciphertext, unsigned char *Key64Bits )
{
    return DesProcess(Plaintext,Ciphertext,Key64Bits,1);
}
//**:***************************************************************************
//**:���ܣ�8�ֽ�DES����
//**:����:	Ciphertext:����,����Ϊ8byte
//**:		Plaintext:���ܺ������,8byte
//**:		Key64Bits:��Կ,8Bytes
//**:**************************************************************************/
int DesDecrypt( unsigned char *Ciphertext, unsigned char *Plaintext, unsigned char *Key64Bits )
{
	return DesProcess(Ciphertext,Plaintext,Key64Bits,2);
}
//**:***************************************************************************
//**:���ܣ�n��8�ֽ�DES����
//**:����:	Plaintext:�����ܵ�����
//**:		Ciphertext:���Ļ�����
//**:		TextLen:���ĵĳ���.����Ϊ8�ı���,������Ԥ�Ȳ���
//**:		Key8Bytes:��Կ,8byte
//**:**************************************************************************/
int GenerateDesCiphertext( unsigned char *Plaintext, unsigned char *Ciphertext,
				int TextLen, unsigned char *Key8Bytes, unsigned char *vec )
{
	int i, j, BlockTotal, ch1, ch2;
    unsigned char tmp_vec[9]={0};

	if( ( TextLen % 8 ) != 0 || TextLen == 0 ) return -10033;

	BlockTotal = TextLen / 8;

    if(vec != 0) memcpy(tmp_vec, vec, 8);   //��ȡ��ʼ����

	for( i = 0; i < BlockTotal; i++ )
	{
		if(vec != 0)    //CBC�㷨
		{
			//��ǰһ�μ��ܽ���뵱ǰ���Ľ������,�������ȥ����
			//��һ�μ���ʱʹ�õ��ǳ�ʼ���������Ľ������
			for(j = 0; j < 8; j++)
			{
                ch1 = tmp_vec[j] & 0xFF;
                ch2 = Plaintext[i * 8 + j] & 0xFF;
				tmp_vec[j] = ch1 ^ ch2;
            }

			//����
			DesEncrypt( tmp_vec, Ciphertext + i * 8, Key8Bytes );

			//�����ܽ���Ż�������,���´��Լ���ʹ��
			memcpy(tmp_vec, Ciphertext + i * 8, 8);
		}
		else   //ECB�㷨
			DesEncrypt( Plaintext + i * 8, Ciphertext + i * 8, Key8Bytes );
    }

	return 0;
}
//**:***************************************************************************
//**:���ܣ�n��8�ֽ�DES����
//**:����:	Ciphertext:�������Ļ�����
//**:		Plaintext:���ܺ������
//**:		TextLen:���ĵĳ���.����Ϊ8�ı���,������Ԥ�Ȳ���
//**:		Key8Bytes:��Կ,8byte
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
		if(vec != 0)   //CBC�㷨
		{
			//����
			DesDecrypt( Ciphertext + i * 8, tmp_Plain, Key8Bytes );

			//���ܽ�����������,�õ���������
			for(j = 0; j < 8; j++)
			{
                ch1 = tmp_vec[j] & 0xFF;
                ch2 = tmp_Plain[j] & 0xFF;
				Plaintext[i * 8 + j] = ch1 ^ ch2;
            }

			//��ǰһ�ε����ķŻ�����,����һ�ν�����ʹ��
			memcpy(tmp_vec, Ciphertext + i * 8, 8);
		}
		else  //ECB�㷨
			DesDecrypt( Ciphertext + i * 8, Plaintext + i * 8, Key8Bytes );
	}

	return 0;
}

///////////////////////////////////3Des���ܡ�����///////////////////////////////
//**:***************************************************************************
//**:���ܣ�8�ֽ�3DES����
//**:����:	Plaintext:����,����Ϊ8byte
//**:		Ciphertext:���ܺ������,����Ϊ8byte
//**:		Key24Bits:��Կ,24Bytes
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
//**:���ܣ�8�ֽ�3DES����
//**:����:	Ciphertext:����,����Ϊ8byte
//**:		Plaintext:���ܺ������,8byte
//**:		Key64Bits:��Կ,16Bytes
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
//**:���ܣ�n��8�ֽ�3DES��������
//**:����:	Plaintext:�����ܵ�����
//**:		Ciphertext:���Ļ�����
//**:		TextLen:���ĵĳ���
//**:		Key16Bytes:��Կ,16byte
//**:***************************************************************************
int Generate3DesCiphertext( unsigned char *Plaintext, unsigned char *Ciphertext,
			int TextLen, unsigned char *Key24Bytes, unsigned char *vec )
{
	int i, j, BlockTotal, ch1 ,ch2;
	unsigned char tmp_vec[9]={0};

	if(vec != 0) memcpy(tmp_vec, vec, 8);   //��ȡ��ʼ����

	if( ( TextLen % 8 ) != 0 || TextLen == 0 ) return -10033;

	BlockTotal = TextLen / 8;

	for( i = 0; i < BlockTotal; i++ )
	{
		if(vec != 0)  //CBC �㷨
		{
			//��ǰһ�μ��ܽ���뵱ǰ���Ľ������,�������ȥ����
			//��һ�μ���ʱʹ�õ��ǳ�ʼ���������Ľ������
			for(j = 0; j < 8; j++)
			{
                ch1 = tmp_vec[j] & 0xFF;
                ch2 = Plaintext[i * 8 + j] & 0xFF;
				tmp_vec[j] = ch1 ^ ch2;
            }

			//����
			TripleDesEncrypt( tmp_vec, Ciphertext + i * 8, Key24Bytes );

			//�����ܽ���Ż�������,���´��Լ���ʹ��
			memcpy(tmp_vec, Ciphertext + i * 8, 8);
		}
		else  //ECB �㷨
			TripleDesEncrypt( Plaintext + i * 8, Ciphertext + i * 8, Key24Bytes );
	}

	return 0;
}
//**:***************************************************************************
//**:���ܣ�n��8�ֽ�3DES��������
//**:����:	Plaintext:���������
//**:		Ciphertext:���Ļ�����
//**:		TextLen:���ĵĳ���
//**:		Key16Bytes:��Կ,16byte
//**:***************************************************************************
int Generate3DesPlaintext( unsigned char *Ciphertext, unsigned char *Plaintext,
			int TextLen, unsigned char *Key24Bytes, unsigned char *vec )
{
	int i, j, BlockTotal, ch1, ch2;
	unsigned char tmp_vec[9]={0};
	unsigned char tmp_Plain[9]={0};

	if(vec != 0) memcpy(tmp_vec, vec, 8);   //��ȡ��ʼ����

	if( ( TextLen % 8 ) != 0 || TextLen == 0 ) return -10033;

	BlockTotal = TextLen / 8;

	for( i = 0; i < BlockTotal; i++ )
	{
		if(vec != 0)   //CBC�㷨
		{
			//����
			TripleDesDecrypt( Ciphertext + i * 8, tmp_Plain, Key24Bytes );

			//���ܽ�����������,�õ���������
			for(j = 0; j < 8; j++)
			{
                ch1 = tmp_vec[j] & 0xFF;
                ch2 = tmp_Plain[j] & 0xFF;
				Plaintext[i * 8 + j] = ch1 ^ ch2;
            }

			//��ǰһ�ε����ķŻ�����,����һ�ν�����ʹ��
			memcpy(tmp_vec, Ciphertext + i * 8, 8);
		}
		else  //ECB�㷨
			TripleDesDecrypt( Ciphertext + i * 8, Plaintext + i * 8, Key24Bytes );
	}

	return 0;
}


/////////////////////����Ϊ����ӿ�/////////////////////////////////////////////
/*[method*******************************************************************************
 *def:  public int des(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec=NULL)
 *func:
        ��ָ���ַ���,ʹ��ָ����Կ,ִ��DES/3DES���ܴ���.���ݲ��ܳ���8192�ֽڳ���.
        ����Կ��8�ֽ�ʱ,ʹ��des����,��Կ��16�ֽ�ʱ,ʹ��3des����.
 *args:
        #src      ��Ҫ���ܵ�Դ����
        #key      ���ܵ���Կ
        #src_len  Դ���ݳ���
        #key_len  ��Կ����8/16,8:ִ��des���� 16��ִ��3DES����
 *output:
        #dst    ���ܺ������
 *ret:
        =0 �ɹ�
        ���� ʧ��
*************************************************************************************]*/
int des(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec)
{
	int fill_len=0;
	unsigned char tmp_buff[8192];
	unsigned char key24byte[25]={0};

	memset(tmp_buff, 0x00, sizeof(tmp_buff));
	memcpy(tmp_buff, src, src_len);
	if(0<(src_len % 8))		//����8�ı���,���в���
	{
    	fill_len = (8 - src_len % 8);		//ȡ����Ҫ������ֽ���
		memcpy(tmp_buff+src_len, fill_char, fill_len);	//����Ϊ8�ı���
	}
	fill_len = fill_len + src_len;		//ȡ�ò�����ʵ�ʳ���
	if(key_len==8)		//DES����
	{
		return GenerateDesCiphertext(tmp_buff, dst, fill_len, key, vec );
	}
	if(key_len==16)		//2��3DES����
	{
        memcpy(key24byte, key, 16);
        memcpy(key24byte+16, key, 8);
		return Generate3DesCiphertext(tmp_buff, dst, fill_len, key24byte, vec );
	}
	if(key_len==24)     //3��3DES����
    {
        return Generate3DesCiphertext(tmp_buff, dst, fill_len, key, vec );
    }
	return -10032;
}

/*[method*******************************************************************************
 *def:  public int undes(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec=NULL)
 *func:
        ��ָ���ַ���,ʹ��ָ����Կ,ִ��DES/3DES���ܴ���,����ԿΪ8�ֽ�ʱʹ��des
        ����,��ԿΪ16�ֽ�ʱʹ��3des����.
 *args:
        #src      ��Ҫ���ܵ�Դ����
        #key      ���ܵ���Կ
        #src_len  Դ���ݳ���
        #key_len  ��Կ����8/16,8:ִ��des���� 16��ִ��3DES����
 *output:
        #dst    ���ܺ������
 *ret:
        =0 �ɹ�
        ���� ʧ��
*************************************************************************************]*/
int undes(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec)
{
    unsigned char key24byte[25]={0};

	if(0<(src_len % 8)) return -10033;		//����8�ı���,����

	if(key_len==8)		//DES����
	{
		return GenerateDesPlaintext(src, dst, src_len, key, vec );
	}
	if(key_len==16)		//2��3DES����
	{
        memcpy(key24byte, key, 16);
        memcpy(key24byte+16, key, 8);
		return Generate3DesPlaintext(src, dst, src_len, key24byte, vec );
	}
	if(key_len==24)		//3��3DES����
	{
		return Generate3DesPlaintext(src, dst, src_len, key, vec );
	}
	return -10034;
}
