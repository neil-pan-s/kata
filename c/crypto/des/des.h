#ifndef __DES_H__
#define __DES_H__

/*[title
    ��׼DES/3DES����
]*/

/*[note
	DES�㷨��ΪECB��CBC����ģʽ, ��ʹ��ʱ���vec����0���ʾECB�㷨,��������Ϊ��ʼ����
]*/

/*[fields
]*/

/*[errcodes
]*/

/*[public */
int des(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec=0);
int undes(unsigned char *src, unsigned char *dst, unsigned char *key, int src_len, int key_len, unsigned char *vec=0);
/*]*/

#endif //__DES_H__
