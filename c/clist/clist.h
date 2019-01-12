#ifndef __CLIST_H__
#define __CLIST_H__

#define CLIST_BASE           (-10100)
#define ERR_CLIST_NOT_FOUND  (CLIST_BASE+(-1))
#define ERR_CLIST_LIKE       (CLIST_BASE+(-2))   //有相似的名称,名称前n个与指定名称相同

typedef struct CLIST_ITEM
{
	char name[48];      //数据变量名,最大允许47个字符
	char *value;        //值
	int  value_ln;      //值的长度
	struct CLIST_ITEM *next;
}CLIST;

void clist_init(CLIST *header);    //初始化clist
void clist_free(CLIST *header);    //释放clist

void clist_delete(CLIST *header, const char *name, int flag);    //删除指定节点

int  clist_set_value(CLIST *header, const char *name, char *value, int ln);  //修改节点值
int  clist_get_value(CLIST *header, const char *name, char *value);   //取得指定元素的值
void clist_prn(CLIST *header, int flag, int ln);   //打印当前数据内容

void clist_clear(CLIST *header, const char *name_like);   //清除指定类型元素的值

void clist_demo();

#endif  //__CLIST_H__
