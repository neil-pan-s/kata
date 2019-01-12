#include "clist.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 使用二级指针的原因是为了方便修改链表头指针的值 */

/*[method*******************************************************************************
 *def:  public void clist_init(CLIST *header)
 *func:
        初始化头指针,头指针由用户自己定义一个CLIST_ITEMDE节点
*************************************************************************************]*/
void clist_init(CLIST *header)
{
	memset(header->name, 0, sizeof(header->name));
	header->value = 0;
	header->value_ln = 0;
	header->next = 0;    //下一个节点
}

/*[method*******************************************************************************
 *def:  public void clist_free(CLIST *header)
 *func:
        释放指针
*************************************************************************************]*/
void clist_free(CLIST *header)
{
    struct CLIST_ITEM *item, *next;

	item = header->next;
	while( item != 0 )
	{
		next = item->next;
		if(item->value != 0) free(item->value);  //释放节点的值空间
		free(item);         //释放节点
		item = next;
	}
}

/*[method*******************************************************************************
 *def:  public void clist_delete(CLIST *header, const char *name, int flag)
 *func:
        删除指定的节点
 *args:
        #name 节点名称
        #flag flag=1:删除节点名称以name为前缀的所有节点, flag=0删除指定的节点
        #header	链表头指针
*************************************************************************************]*/
void clist_delete(CLIST *header, const char *name, int flag)
{
	struct CLIST_ITEM *item1, *item2;

	//查找指定的节点
	item2 = header;
	item1 = item2->next;
	while( item1 != 0 )
	{
		if( flag == 0 )  //删除指定节点
		{
			if( strcmp(item1->name, name) == 0 )   //当前节点是需要删除的节点
			{
				item2->next = item1->next;
				//从内存清除数据,确保不会泄露用户数据
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
			if( memcmp(item1->name, name, strlen(name)) == 0 )   //当前节点是需要删除的节点
			{
				item2->next = item1->next;
				//从内存清除数据,确保不会泄露用户数据
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
        清除指定类型元素的值,以name_like为名称前缀的域.
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
        修改节点值
 *args:
        header    头节点
        name      需要设置的节点名
        value     需要设置的节点值
        ln        值的长度
 *ret:
        =0   修改成功
        <0   节点不存在
*************************************************************************************]*/
int clist_set_value(CLIST *header, const char *name, char *value, int ln)
{
	struct CLIST_ITEM *item, *tmp_item1, *tmp_item2;
	char *char_pos;

	//删除以存在的同名节点
	clist_delete(header, name, 0);

    if(ln == -1 ) ln =  strlen(value);

	//申请节点空间
	item = (struct CLIST_ITEM*)malloc(sizeof(CLIST));

	//保存节点名称
	strcpy(item->name, name);
    item->next = 0;
    //申请值空间
	char_pos = (char*)malloc(ln+1);
	memset(char_pos, 0, ln+1);
	memcpy(char_pos, value, ln);
	item->value = char_pos;
	item->value_ln = ln;

	//将新节点加在最前面
	tmp_item1 = (struct CLIST_ITEM*)(header);
	tmp_item2 = tmp_item1->next;
	tmp_item1->next = item;
	item->next = tmp_item2;

//	free(item);
//	free(char_pos);

/*
    //查找最后一个节点
    last = (struct CLIST_ITEM*)(header);
    while( last->next != 0)
        last = last->next;

    //将新节点添加到最后
    last->next = item;
*/
	return 0;
}

/*[method*******************************************************************************
 *def:  public void clist_get_value(CLIST *header, const char *name, char *value)
 *func:
        取得指定节点的值
 *ret:
        <0  没有找到指定的节点
        0>=  值的长度
*************************************************************************************]*/
int clist_get_value(CLIST *header, const char *name, char *value)
{
	int found_like=0;

	struct CLIST_ITEM *item;

	//查找指定的节点
	item = header->next;
	while( item != 0 )
	{
		if(strcmp(item->name, name) == 0) break;   //发现同名的节点
		if( memcmp(item->name, name, strlen(name))==0 ) found_like=1;
		item = item->next;
	}
	if( item == 0 && found_like==1 ) return ERR_CLIST_LIKE;  //有相似的节点
	if(item == 0 ) return ERR_CLIST_NOT_FOUND;   //没有同名的节点

	//取得值
	memcpy(value, item->value, item->value_ln);

	return item->value_ln;
}

/*[method*******************************************************************************
 *def:  public void clist_prn(CLIST *header, int flag, int ln)
 *func:
        to print the names and values of the clist
 *args
 		header	链表头指针
 		flag	显示格式
 		ln		长度
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
