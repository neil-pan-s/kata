#ifndef __DES_H__
#define __DES_H__

/*[title
    标准DES/3DES加密
]*/

/*[note
	DES算法分为ECB、CBC两种模式, 在使用时如果vec传入0则表示ECB算法,否则其中为初始向量
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
