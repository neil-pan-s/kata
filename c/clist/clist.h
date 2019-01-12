#ifndef __CLIST_H__
#define __CLIST_H__

#define CLIST_BASE           (-10100)
#define ERR_CLIST_NOT_FOUND  (CLIST_BASE+(-1))
#define ERR_CLIST_LIKE       (CLIST_BASE+(-2))   //�����Ƶ�����,����ǰn����ָ��������ͬ

typedef struct CLIST_ITEM
{
	char name[48];      //���ݱ�����,�������47���ַ�
	char *value;        //ֵ
	int  value_ln;      //ֵ�ĳ���
	struct CLIST_ITEM *next;
}CLIST;

void clist_init(CLIST *header);    //��ʼ��clist
void clist_free(CLIST *header);    //�ͷ�clist

void clist_delete(CLIST *header, const char *name, int flag);    //ɾ��ָ���ڵ�

int  clist_set_value(CLIST *header, const char *name, char *value, int ln);  //�޸Ľڵ�ֵ
int  clist_get_value(CLIST *header, const char *name, char *value);   //ȡ��ָ��Ԫ�ص�ֵ
void clist_prn(CLIST *header, int flag, int ln);   //��ӡ��ǰ��������

void clist_clear(CLIST *header, const char *name_like);   //���ָ������Ԫ�ص�ֵ

void clist_demo();

#endif  //__CLIST_H__
