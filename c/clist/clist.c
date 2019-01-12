#include "clist.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ʹ�ö���ָ���ԭ����Ϊ�˷����޸�����ͷָ���ֵ */

/*[method*******************************************************************************
 *def:  public void clist_init(CLIST *header)
 *func:
        ��ʼ��ͷָ��,ͷָ�����û��Լ�����һ��CLIST_ITEMDE�ڵ�
*************************************************************************************]*/
void clist_init(CLIST *header)
{
	memset(header->name, 0, sizeof(header->name));
	header->value = 0;
	header->value_ln = 0;
	header->next = 0;    //��һ���ڵ�
}

/*[method*******************************************************************************
 *def:  public void clist_free(CLIST *header)
 *func:
        �ͷ�ָ��
*************************************************************************************]*/
void clist_free(CLIST *header)
{
    struct CLIST_ITEM *item, *next;

	item = header->next;
	while( item != 0 )
	{
		next = item->next;
		if(item->value != 0) free(item->value);  //�ͷŽڵ��ֵ�ռ�
		free(item);         //�ͷŽڵ�
		item = next;
	}
}

/*[method*******************************************************************************
 *def:  public void clist_delete(CLIST *header, const char *name, int flag)
 *func:
        ɾ��ָ���Ľڵ�
 *args:
        #name �ڵ�����
        #flag flag=1:ɾ���ڵ�������nameΪǰ׺�����нڵ�, flag=0ɾ��ָ���Ľڵ�
        #header	����ͷָ��
*************************************************************************************]*/
void clist_delete(CLIST *header, const char *name, int flag)
{
	struct CLIST_ITEM *item1, *item2;

	//����ָ���Ľڵ�
	item2 = header;
	item1 = item2->next;
	while( item1 != 0 )
	{
		if( flag == 0 )  //ɾ��ָ���ڵ�
		{
			if( strcmp(item1->name, name) == 0 )   //��ǰ�ڵ�����Ҫɾ���Ľڵ�
			{
				item2->next = item1->next;
				//���ڴ��������,ȷ������й¶�û�����
				if( item1->value != 0)
				{
					memset(item1->value, 0, item1->value_ln);
					free(item1->value);    //free the current node's value
				}
				free(item1);     //free the current node
				return;
			}
		}
		else
		{
			if( memcmp(item1->name, name, strlen(name)) == 0 )   //��ǰ�ڵ�����Ҫɾ���Ľڵ�
			{
				item2->next = item1->next;
				//���ڴ��������,ȷ������й¶�û�����
				if( item1->value != 0)
				{
					memset(item1->value, 0, item1->value_ln);
					free(item1->value);    //free the current node's value
				}
				free(item1);     //free the current node
				item1 = item2->next;
				continue;
			}
		}

		item2 = item1;
		item1 = item2->next;
	}
}

/*[method*******************************************************************************
 *def:  public void clist_clear(CLIST *header, const char *name_like)
 *func:
        ���ָ������Ԫ�ص�ֵ,��name_likeΪ����ǰ׺����.
*************************************************************************************]*/
void clist_clear(CLIST *header, const char *name_like)
{
    struct CLIST_ITEM *item;

	item = header->next;
	while( item != 0 )
	{
        if( memcmp(item->name, name_like, strlen(name_like))== 0)
        {
            memset(item->value, 0, item->value_ln);
            item->value_ln = 0;
        }
		item = item->next;
	}
}

/*[method*******************************************************************************
 *def:  public int clist_set_value(CLIST *header, const char *name, char *value, int ln)
 *func:
        �޸Ľڵ�ֵ
 *args:
        header    ͷ�ڵ�
        name      ��Ҫ���õĽڵ���
        value     ��Ҫ���õĽڵ�ֵ
        ln        ֵ�ĳ���
 *ret:
        =0   �޸ĳɹ�
        <0   �ڵ㲻����
*************************************************************************************]*/
int clist_set_value(CLIST *header, const char *name, char *value, int ln)
{
	struct CLIST_ITEM *item, *tmp_item1, *tmp_item2;
	char *char_pos;

	//ɾ���Դ��ڵ�ͬ���ڵ�
	clist_delete(header, name, 0);

    if(ln == -1 ) ln =  strlen(value);

	//����ڵ�ռ�
	item = (struct CLIST_ITEM*)malloc(sizeof(CLIST));

	//����ڵ�����
	strcpy(item->name, name);
    item->next = 0;
    //����ֵ�ռ�
	char_pos = (char*)malloc(ln+1);
	memset(char_pos, 0, ln+1);
	memcpy(char_pos, value, ln);
	item->value = char_pos;
	item->value_ln = ln;

	//���½ڵ������ǰ��
	tmp_item1 = (struct CLIST_ITEM*)(header);
	tmp_item2 = tmp_item1->next;
	tmp_item1->next = item;
	item->next = tmp_item2;

//	free(item);
//	free(char_pos);

/*
    //�������һ���ڵ�
    last = (struct CLIST_ITEM*)(header);
    while( last->next != 0)
        last = last->next;

    //���½ڵ���ӵ����
    last->next = item;
*/
	return 0;
}

/*[method*******************************************************************************
 *def:  public void clist_get_value(CLIST *header, const char *name, char *value)
 *func:
        ȡ��ָ���ڵ��ֵ
 *ret:
        <0  û���ҵ�ָ���Ľڵ�
        0>=  ֵ�ĳ���
*************************************************************************************]*/
int clist_get_value(CLIST *header, const char *name, char *value)
{
	int found_like=0;

	struct CLIST_ITEM *item;

	//����ָ���Ľڵ�
	item = header->next;
	while( item != 0 )
	{
		if(strcmp(item->name, name) == 0) break;   //����ͬ���Ľڵ�
		if( memcmp(item->name, name, strlen(name))==0 ) found_like=1;
		item = item->next;
	}
	if( item == 0 && found_like==1 ) return ERR_CLIST_LIKE;  //�����ƵĽڵ�
	if(item == 0 ) return ERR_CLIST_NOT_FOUND;   //û��ͬ���Ľڵ�

	//ȡ��ֵ
	memcpy(value, item->value, item->value_ln);

	return item->value_ln;
}

/*[method*******************************************************************************
 *def:  public void clist_prn(CLIST *header, int flag, int ln)
 *func:
        to print the names and values of the clist
 *args
 		header	����ͷָ��
 		flag	��ʾ��ʽ
 		ln		����
*************************************************************************************]*/
void clist_prn(CLIST *header, int flag, int ln)
{
	struct CLIST_ITEM *item;

	item = header->next;
	while(item != 0)
	{
		printf("%36s[%04d]=", item->name, item->value_ln);
		if( flag == 1)
			printf("%s", item->value);
		else
		{
			int i, tmp_ln;
			if( item->value_ln > ln )
				 tmp_ln = ln;
			else tmp_ln = item->value_ln;

			for(i=0; i<tmp_ln; i++)
				printf("%02X ", item->value[i]&0xff);
		}
		printf("\n");
		item = item->next;
	}
}


/*[method*******************************************************************************
 *def:  public void clist_demo()
 *func:
        the demo how to use the clist
*************************************************************************************]*/
void clist_demo()
{
    CLIST header;

    clist_init(&header);
    clist_set_value(&header, "item1", "12345", -1);
    clist_set_value(&header, "item2", "abcde", 5);
    clist_set_value(&header, "item3", "DERESF", 6);
    clist_set_value(&header, "item4", "76543", -1);
    clist_set_value(&header, "item5", "kffdsht", -1);

    clist_prn(&header, 1, 20);

    clist_set_value(&header, "item4", "87532", -1);
    clist_delete(&header, "item3", 0);

    clist_prn(&header, 1, 20);

    clist_free(&header);
}
