#include "ztinifile.h"
#include "ztstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*[method*******************************************************************************
 *def:  int ZTIni_Init(TInifile **p_iniCtrl,const char *p_caPath)
 *func: 创建一个ini配置文件对象
 *args: p_iniCtrl ini文件控制结构指针
        p_caPath  配置文件路径  
*************************************************************************************]*/
int ZTIni_Init(TInifile **p_iniCtrl,const char *p_caPath)
{
    int   i=0;
    char  caLine[512]={0};
    char *cpPos=NULL;
    TIniItem *item=NULL;
    TIniItem *tail=NULL;
    FILE *fp=NULL;
    TInifile *ctrl=NULL;

    if(p_iniCtrl == NULL)
    {
        return -1;
    }    

    //创建配置文件控制结构
    ctrl = (TInifile*)malloc(sizeof(TInifile));
    memset(ctrl, 0, sizeof(TInifile));
    sprintf(ctrl->caPath, "%s", p_caPath);    //保存配置文件路径

    //创建一个空的头节点,该头节点不代表任何值,只为了操作方便
    ctrl->header = (TIniItem*)malloc(sizeof(TIniItem));
    memset(ctrl->header, 0, sizeof(TIniItem));

    //初始化互斥对象
    ZTMutex_Init(&(ctrl->mutex));

    //找到尾指针
    tail = ctrl->header;

    //循环读取文件内容保存
    fp = fopen(ctrl->caPath, "r");
    if( fp == NULL )
    {
        return -2;
    }

    memset(caLine, 0, sizeof(caLine));
    while( fgets(caLine, sizeof(caLine), fp)!=NULL )
    {
        //去掉前后的空字符
        ZT_Trim(caLine, caLine, TRIM_LEFT_RIGHT );
        if( strlen(caLine)==0 ) continue;

        //如果是一个扇区
        if( caLine[0] == '[' )
        {
            item = (TIniItem*)malloc(sizeof(TIniItem));
            memset(item, 0, sizeof(TIniItem));
            item->iType = 1;
            item->cpKey = (char*)malloc(strlen(caLine)+4);
            memset(item->cpKey, 0, strlen(caLine)+4);
            memcpy(item->cpKey, caLine+1, strlen(caLine)-2);
            tail->next = item;
            item->pre  = tail;
            tail = item;
            continue;
        }
        else
        {
            //对没有注释的附加一个注释,以方便处理
            if( strstr(caLine, "//")==NULL )
            {
                strcat(caLine, " //");
            }

            //判断语法是否正确
            cpPos = strstr(caLine, "=");
            if( cpPos == NULL ) continue;

            //创建一个新的节点,并将其加入链表中
            item = (TIniItem*)malloc(sizeof(TIniItem));
            memset(item, 0, sizeof(TIniItem));
            item->iType = 2;
            tail->next = item;
            item->pre  = tail;
            tail = item;

            //取得关键字
            i = cpPos - caLine;
            item->cpKey = (char*)malloc(i+4);
            memset(item->cpKey, 0, i+4);
            memcpy(item->cpKey, caLine, i);
            ZT_Trim(item->cpKey, item->cpKey, TRIM_LEFT_RIGHT);

            //取得值
            ZT_Trim(cpPos+1, caLine, TRIM_LEFT);
            cpPos = strstr(caLine, "//");
            i = cpPos - caLine;
            if( 0 < i )
            {
                item->cpValue = (char*)malloc(i+4);
                memset(item->cpValue, 0, i+4);
                memcpy(item->cpValue, caLine, i-1);
                ZT_Trim(item->cpValue, item->cpValue, TRIM_LEFT_RIGHT);
            }
            else   //如果节点数据为空,分配默认大小空间
            {
                item->cpValue = (char*)malloc(64);
                memset(item->cpValue, 0, 64);
            }

            //取得注释
            ZT_Trim(cpPos+2, caLine, TRIM_LEFT);
            i = strlen(caLine);
            item->cpRemark = (char*)malloc(i+4);
            memset(item->cpRemark, 0, i+4);
            memcpy(item->cpRemark, caLine, i);
        }
    }
    fclose(fp);

    *p_iniCtrl = ctrl;
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTIni_Close(TInifile *p_iniCtrl)
 *func: ZTInifile 结构析构函数
 *args: p_iniCtrl ini文件控制结构指针
*************************************************************************************]*/
int ZTIni_Close(TInifile *p_iniCtrl)
{
    TIniItem *item=NULL;
    TIniItem *delitem=NULL;
    TInifile *ctrl=(TInifile*)p_iniCtrl;

    if(p_iniCtrl == NULL)
    {
        return -1;
    }  

    ZTMutex_Lock(p_iniCtrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        delitem = (TIniItem*)(item->next);
        item->next = delitem->next;
        if( delitem->cpKey != NULL ) free(delitem->cpKey);
        if( delitem->cpValue != NULL ) free(delitem->cpValue);
        if( delitem->cpRemark != NULL ) free(delitem->cpRemark);
        free(delitem);
        delitem = NULL;
    }
    free(ctrl->header);
    ctrl->header = NULL;

    ZTMutex_Unlock(p_iniCtrl->mutex);
    ZTMutex_Destroy(p_iniCtrl->mutex);    
    free(p_iniCtrl);

    return 0;
}

/*[method*******************************************************************************
 *def:  void ZTIni_Print(TInifile *p_iniCtrl)
 *func: 打印当前配置内容到标准输出
 *args: p_iniCtrl ini文件控制结构指针
*************************************************************************************]*/
void ZTIni_Print(TInifile *p_iniCtrl)
{
    TIniItem *item=NULL;
    TInifile *ctrl=(TInifile*)p_iniCtrl;

    if(p_iniCtrl == NULL)
    {
        return ;
    } 

    ZTMutex_Lock(p_iniCtrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        item = (TIniItem*)(item->next);
        if( item->iType == 1 )
        {
            printf("[%s]\n", item->cpKey);
        }
        else
        {
            printf("    %s = %s   //%s\n", item->cpKey, item->cpValue, item->cpRemark);
        }
    }

    ZTMutex_Unlock(p_iniCtrl->mutex);
}

/*[method*******************************************************************************
 *def:  int ZTIni_Save(TInifile *p_iniCtrl,const char *p_caPath)
 *func: 保存配置数据到指定的配置文件中,如果p_caPath=NULL则保存为原文件
 *args: p_iniCtrl ini文件控制结构指针
        p_caPath  保存的配置文件路径, 如果为NULL则保存为当前配置文件
*************************************************************************************]*/
int ZTIni_Save(TInifile *p_iniCtrl,const char *p_caPath)
{
    char caTmp[512]={0};
    TIniItem *item=NULL;
    FILE *fp=NULL;
    TInifile *ctrl=(TInifile*)p_iniCtrl;

    if(p_iniCtrl == NULL)
    {
        return -1;
    } 

    ZTMutex_Lock(p_iniCtrl->mutex);

    if( p_caPath != NULL )
    {
        fp = fopen(p_caPath, "w");
    }
    else
    {
        fp = fopen(ctrl->caPath, "w");
    }

    item = ctrl->header;
    while( item->next != NULL )
    {
        item = (TIniItem*)(item->next);
        if( item->iType == 1 )
        {
            memset(caTmp, 0, sizeof(caTmp));
            sprintf(caTmp, "\r\n[%s]\r\n", item->cpKey);
            fwrite(caTmp, 1, strlen(caTmp), fp);
        }
        else
        {
            memset(caTmp, 0, sizeof(caTmp));
            sprintf(caTmp, "    %s = %s   //%s\r\n", item->cpKey, item->cpValue, item->cpRemark);
            fwrite(caTmp, 1, strlen(caTmp), fp);
        }
    }
    fclose(fp);

    ZTMutex_Unlock(p_iniCtrl->mutex);

    return 0;
}

/*[method*******************************************************************************
 *def:  const char* ZTIni_Get(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, char *p_caValue, const char *p_caDef)
 *func: 取得指定关键字的值, 此方法支持同时从参数和函数返回值返回关键字的值,
        具体如何使用,由调用者自行选择
 *args: p_iniCtrl         ini文件控制结构指针
        p_caSection       扇区
        p_caKey           关键字
        p_caDef           默认值,不允许为空
 *output:   p_caValue     存放取得的关键字的值,如果为NULL表示不需要通过此变量返回配置值
 *ret:  取得的关键字的值.
*************************************************************************************]*/
const char* ZTIni_Get(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, char *p_caValue, const char *p_caDef)
{
    int   iSectionFind=0;
    char *cpReturn=NULL;
    TIniItem *item=NULL;
    TInifile *ctrl=(TInifile*)p_iniCtrl;

    if(p_iniCtrl == NULL)
    {
        return NULL;
    } 

    //需要返回参数且有默认值时,将默认值先保存到返回变量中
    if( p_caValue != NULL ) sprintf(p_caValue, "%s", p_caDef);

    ZTMutex_Lock(p_iniCtrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        item = (TIniItem*)(item->next);
        if( item->iType == 1 )  //如果是一个扇区定义
        {
            if( strcmp(item->cpKey, p_caSection)==0 )
            {
                iSectionFind = 1;   //置为找到扇区
            }
            else
            {
                if( iSectionFind == 1 )  //指定扇区的指定的关键字不存在
                {
                    if( p_caValue != NULL )
                    {
                        cpReturn = NULL;
                        goto LAB_EXIT;
                    }
                    cpReturn = (char*)p_caDef;
                    goto LAB_EXIT;
                }
            }
        }
        else if( (iSectionFind == 1 ) && (strcmp(item->cpKey, p_caKey)==0) )
        {
            if( p_caValue != NULL )
            {
                strcpy(p_caValue, item->cpValue);
                cpReturn = NULL;
                goto LAB_EXIT;
            }
            else
            {
                cpReturn = item->cpValue;
                goto LAB_EXIT;
            }
        }
    }
    cpReturn = (char*)p_caDef;

LAB_EXIT:
    ZTMutex_Unlock(p_iniCtrl->mutex);
    return cpReturn;
}

/*[method*******************************************************************************
 *def:  int ZTIni_GetInt(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, int p_iDef)
 *func: 取得指定关键字的整型值,如果关键字不存在,则返回默认值
 *args: p_iniCtrl         ini文件控制结构指针
        p_caSection     扇区
        p_caKey         关键字
        p_iDef          默认值
 *ret:  取得的配置值,如果关键字不存在则返回默认值
*************************************************************************************]*/
int ZTIni_GetInt(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, int p_iDef)
{
    int   iSectionFind=0, iReturn=0;
    TIniItem *item=NULL;
    TInifile *ctrl=(TInifile*)p_iniCtrl;

    if(p_iniCtrl == NULL)
    {
        return -1;
    } 

    //需要返回参数且有默认值时,将默认值先保存到返回变量中
    iReturn = p_iDef;

    ZTMutex_Lock(p_iniCtrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        item = (TIniItem*)(item->next);
        if( item->iType == 1 )  //如果是一个扇区定义
        {
            if( strcmp(item->cpKey, p_caSection)==0 )
            {
                iSectionFind = 1;   //置为找到扇区
            }
            else
            {
                if( iSectionFind == 1 )  //指定扇区的指定的关键字不存在
                {
                    goto LAB_EXIT;
                }
            }
        }
        else if( (iSectionFind == 1 ) && (strcmp(item->cpKey, p_caKey)==0) )
        {
            iReturn = atoi(item->cpValue);
            goto LAB_EXIT;
        }
    }

LAB_EXIT:
    ZTMutex_Unlock(p_iniCtrl->mutex);
    return iReturn;
}

/*[method*******************************************************************************
 *def:  int ZTIni_Set(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, char *p_caValue)
 *func: 设置指定关键字的值
 *args: p_iniCtrl      ini文件控制结构指针
        p_caSection    扇区
        p_caKey        关键字
        p_caValue      值
*************************************************************************************]*/
int ZTIni_Set(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, char *p_caValue)
{
    int   iSectionFind=0;
    TIniItem *item=NULL;
    TIniItem *newitem=NULL;
    TIniItem *preitem=NULL;
    TInifile *ctrl=(TInifile*)p_iniCtrl;

    if(p_iniCtrl == NULL)
    {
        return -1;
    } 

    ZTMutex_Lock(p_iniCtrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        item = (TIniItem*)(item->next);
        if( item->iType == 1 )  //如果是一个扇区定义
        {
            if( strcmp(item->cpKey, p_caSection)==0 )
            {
                iSectionFind = 1;   //置为找到扇区
            }
            else
            {
                if( iSectionFind == 1 )   //指定扇区的指定的关键字不存在
                {
                    preitem = (TIniItem*)(item->pre);  //指向前一个扇区的最后一个节点

                    //添加一个配置项
                    newitem = (TIniItem*)malloc(sizeof(TIniItem));
                    memset(newitem, 0, sizeof(TIniItem));
                    newitem->iType = 2;

                    newitem->cpKey = (char*)malloc(strlen(p_caKey)+4);
                    memset(newitem->cpKey, 0, strlen(p_caKey)+4);
                    memcpy(newitem->cpKey, p_caKey, strlen(p_caKey));

                    newitem->cpValue = (char*)malloc(strlen(p_caValue)+4);
                    memset(newitem->cpValue, 0, strlen(p_caValue)+4);
                    memcpy(newitem->cpValue, p_caValue, strlen(p_caValue));

                    newitem->cpRemark = (char*)malloc(4);
                    memset(newitem->cpRemark, 0, 4);

                    newitem->next = item;
                    newitem->pre  = preitem;
                    item->pre     = newitem;
                    preitem->next = newitem;
                    goto LAB_EXIT;
                }
            }
        }
        else if( (iSectionFind == 1 ) && (strcmp(item->cpKey, p_caKey)==0) )
        {
            free(item->cpValue);
            item->cpValue = NULL;

            item->cpValue = (char*)malloc(strlen(p_caValue)+4);
            memset(item->cpValue, 0, strlen(p_caValue)+4);
            strcpy(item->cpValue, p_caValue);
            goto LAB_EXIT;
        }
    }

    if( iSectionFind == 0 )
    {
        //添加一个新扇区
        newitem = (TIniItem*)malloc(sizeof(TIniItem));
        memset(newitem, 0, sizeof(TIniItem));
        newitem->iType = 1;

        newitem->cpKey = (char*)malloc(strlen(p_caSection)+4);
        memset(newitem->cpKey, 0, strlen(p_caSection)+4);
        memcpy(newitem->cpKey, p_caSection, strlen(p_caSection));

        newitem->next = NULL;
        newitem->pre  = item;
        item->next    = newitem;

        item = newitem;
    }

    //添加一个配置项
    newitem = (TIniItem*)malloc(sizeof(TIniItem));
    memset(newitem, 0, sizeof(TIniItem));
    newitem->iType = 2;

    newitem->cpKey = (char*)malloc(strlen(p_caKey)+4);
    memset(newitem->cpKey, 0, strlen(p_caKey)+4);
    memcpy(newitem->cpKey, p_caKey, strlen(p_caKey));

    newitem->cpValue = (char*)malloc(strlen(p_caValue)+4);
    memset(newitem->cpValue, 0, strlen(p_caValue)+4);
    memcpy(newitem->cpValue, p_caValue, strlen(p_caValue));

    newitem->cpRemark = (char*)malloc(4);
    memset(newitem->cpRemark, 0, 4);

    newitem->next = NULL;
    newitem->pre  = item;
    item->next    = newitem;

LAB_EXIT:
    ZTMutex_Unlock(p_iniCtrl->mutex);
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTIni_SetInt(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, int p_iValue)
 *func: 设置指定关键字的整型值
 *args: p_iniCtrl      ini文件控制结构指针
        p_caSection    扇区
        p_caKey        关键字
        p_iValue       值
*************************************************************************************]*/
int ZTIni_SetInt(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, int p_iValue)
{
    int   iSectionFind=0;
    TIniItem *item=NULL;
    TIniItem *newitem=NULL;
    TIniItem *preitem=NULL;
    TInifile *ctrl=(TInifile*)p_iniCtrl;

    if(p_iniCtrl == NULL)
    {
        return -1;
    } 

    ZTMutex_Lock(p_iniCtrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        item = (TIniItem*)(item->next);
        if( item->iType == 1 )  //如果是一个扇区定义
        {
            if( strcmp(item->cpKey, p_caSection)==0 )
            {
                iSectionFind = 1;   //置为找到扇区
            }
            else
            {
                if( iSectionFind == 1 )   //指定扇区的指定的关键字不存在
                {
                    preitem = (TIniItem*)(item->pre);  //指向前一个扇区的最后一个节点

                    //添加一个配置项
                    newitem = (TIniItem*)malloc(sizeof(TIniItem));
                    memset(newitem, 0, sizeof(TIniItem));
                    newitem->iType = 2;

                    newitem->cpKey = (char*)malloc(strlen(p_caKey)+4);
                    memset(newitem->cpKey, 0, strlen(p_caKey)+4);
                    memcpy(newitem->cpKey, p_caKey, strlen(p_caKey));

                    newitem->cpValue = (char*)malloc(12);
                    memset(newitem->cpValue, 0, 12);
                    sprintf(newitem->cpValue, "%d", p_iValue);

                    newitem->cpRemark = (char*)malloc(4);
                    memset(newitem->cpRemark, 0, 4);

                    newitem->next = item;
                    newitem->pre  = preitem;
                    item->pre     = newitem;
                    preitem->next = newitem;
                    goto LAB_EXIT;
                }
            }
        }
        else if( (iSectionFind == 1 ) && (strcmp(item->cpKey, p_caKey)==0) )
        {
            free(item->cpValue);
            item->cpValue = NULL;

            item->cpValue = (char*)malloc(12);
            memset(item->cpValue, 0, 12);
            sprintf(item->cpValue, "%d", p_iValue);
            goto LAB_EXIT;
        }
    }

    if( iSectionFind == 0 )
    {
        //添加一个新扇区
        newitem = (TIniItem*)malloc(sizeof(TIniItem));
        memset(newitem, 0, sizeof(TIniItem));
        newitem->iType = 1;

        newitem->cpKey = (char*)malloc(strlen(p_caSection)+4);
        memset(newitem->cpKey, 0, strlen(p_caSection)+4);
        memcpy(newitem->cpKey, p_caSection, strlen(p_caSection));

        newitem->next = NULL;
        newitem->pre  = item;
        item->next    = newitem;

        item = newitem;
    }

    //添加一个配置项
    newitem = (TIniItem*)malloc(sizeof(TIniItem));
    memset(newitem, 0, sizeof(TIniItem));
    newitem->iType = 2;

    newitem->cpKey = (char*)malloc(strlen(p_caKey)+4);
    memset(newitem->cpKey, 0, strlen(p_caKey)+4);
    memcpy(newitem->cpKey, p_caKey, strlen(p_caKey));

    newitem->cpValue = (char*)malloc(12);
    memset(newitem->cpValue, 0, 12);
    sprintf(newitem->cpValue, "%d", p_iValue);

    newitem->cpRemark = (char*)malloc(4);
    memset(newitem->cpRemark, 0, 4);

    newitem->next = NULL;
    newitem->pre  = item;
    item->next    = newitem;

LAB_EXIT:
    ZTMutex_Unlock(p_iniCtrl->mutex);
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTIni_DelKey(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey)
 *func: 删除指定关键字
 *args: p_iniCtrl      ini文件控制结构指针
        p_caSection     扇区
        p_caKey         关键字
*************************************************************************************]*/
int ZTIni_DelKey(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey)
{
    int   iSectionFind=0;
    TIniItem *item=NULL;
    TIniItem *pre=NULL;
    TIniItem *next=NULL;
    TInifile *ctrl=(TInifile*)p_iniCtrl;

    if(p_iniCtrl == NULL)
    {
        return -1;
    } 

    ZTMutex_Lock(p_iniCtrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        item = (TIniItem*)(item->next);
        if( item->iType == 1 )  //如果是一个扇区定义
        {
            if( strcmp(item->cpKey, p_caSection)==0 )
            {
                iSectionFind = 1;   //置为找到扇区
            }
            else
            {
                if( iSectionFind == 1 ) goto LAB_EXIT;  //指定扇区的指定的关键字不存在
            }
        }
        else if( (iSectionFind == 1 ) && (strcmp(item->cpKey, p_caKey)==0) )
        {
            pre  = (TIniItem*)(item->pre);
            next = (TIniItem*)(item->next);

            pre->next = next;
            if( next != NULL ) next->pre = pre;

            if( item->cpKey != NULL ) free(item->cpKey);
            if( item->cpValue != NULL ) free(item->cpValue);
            if( item->cpRemark != NULL ) free(item->cpRemark);
            free(item);
            item = NULL;
            goto LAB_EXIT;
        }
    }

LAB_EXIT:
    ZTMutex_Unlock(p_iniCtrl->mutex);
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTIni_DelSection(TInifile *p_iniCtrl,const char *p_caSection)
 *func: 删除指定扇区
 *args: p_iniCtrl       ini文件控制结构指针
        p_caSection     扇区
        p_caKey         关键字
*************************************************************************************]*/
int ZTIni_DelSection(TInifile *p_iniCtrl,const char *p_caSection)
{
    TIniItem *item=NULL, *temp=NULL;
    TInifile *ctrl=(TInifile*)p_iniCtrl;

    if(p_iniCtrl == NULL)
    {
        return -1;
    } 

    ZTMutex_Lock(p_iniCtrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        temp = (TIniItem*)(item->next);
        //如果是指定的扇区
        if( (temp->iType == 1) && (strcmp(temp->cpKey, p_caSection)==0) )
        {
            while( 1 )
            {
                //删除当前节点
                item->next = temp->next;

                if( temp->next != NULL ) ((TIniItem*)(temp->next))->pre = (void*)item;

                if( temp->cpKey != NULL ) free(temp->cpKey);
                if( temp->cpValue != NULL ) free(temp->cpValue);
                if( temp->cpRemark != NULL ) free(temp->cpRemark);
                free(temp);
                temp = NULL;

                temp = (TIniItem*)(item->next);
                if( temp == NULL ) goto LAB_EXIT;       //已经删除最后一个节点
                if( temp->iType == 1 ) goto LAB_EXIT;   //遇到下一个扇区
            }
        }
        else   item = temp; //循环 下一个节点
    }

LAB_EXIT:
    ZTMutex_Unlock(p_iniCtrl->mutex);
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTIni_GetSecationCnt(TInifile *p_iniCtrl)
 *func: 获得扇区的个数
 *args: p_iniCtrl       ini文件控制结构指针
*************************************************************************************]*/
int ZTIni_GetSecationCnt(TInifile *p_iniCtrl)
{
    int   iCnt=0;
    TIniItem *item=NULL, *temp=NULL;
    TInifile *ctrl=(TInifile*)p_iniCtrl;

    if(p_iniCtrl == NULL)
    {
        return -1;
    } 

    ZTMutex_Lock(p_iniCtrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        temp = (TIniItem*)(item->next);
        if( temp->iType == 1 ) iCnt++;
        item = temp;
    }

    ZTMutex_Unlock(p_iniCtrl->mutex);
    return iCnt;
}

/*[method*******************************************************************************
 *def:  void ZTIni_GetSactionName(TInifile *p_iniCtrl,int p_iIdx, char *p_caName)
 *func: 获得指定序号的扇区名称,序号从0开始
 *args: p_iniCtrl       ini文件控制结构指针
*************************************************************************************]*/
int ZTIni_GetSactionName(TInifile *p_iniCtrl,int p_iIdx, char *p_caName)
{
    int   iCnt=0;
    TIniItem *item=NULL, *temp=NULL;
    TInifile *ctrl=(TInifile*)p_iniCtrl;

    if(p_iniCtrl == NULL)
    {
        return -1;
    } 

    ZTMutex_Lock(p_iniCtrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        temp = (TIniItem*)(item->next);
        if( (1 == temp->iType) && (p_iIdx == iCnt) )
        {
            strcpy(p_caName, temp->cpKey);
            break;
        }
        if( 1 == temp->iType ) iCnt++;
        item = temp;
    }

    ZTMutex_Unlock(p_iniCtrl->mutex);
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTIni_GetKey(TInifile *p_iniCtrl,int p_iIdx, char *p_caSaction, char *p_caName, char *p_caValue)
 *func: 取得指定序号的关键字, 序号从0开始
 *args: p_iniCtrl       ini文件控制结构指针
*************************************************************************************]*/
int ZTIni_GetKey(TInifile *p_iniCtrl,int p_iIdx, char *p_caSaction, char *p_caName, char *p_caValue)
{
    int iIdx=0, iRet=0;
    TIniItem *item=NULL;
    TInifile *ctrl=(TInifile*)p_iniCtrl;

    if(p_iniCtrl == NULL)
    {
        return -1;
    } 
    
    ZTMutex_Lock(p_iniCtrl->mutex);

    iIdx = 0;
    item = ctrl->header;
    while( item->next != NULL )
    {
        item = (TIniItem*)(item->next);
        if( 1 == item->iType )    //记录扇区
        {
            strcpy(p_caSaction, item->cpKey);
        }

        if( p_iIdx == iIdx )   //指定的序号
        {
            if( 1 == item->iType )   //扇区
            {
                iRet = 1;
                goto LAB_EXIT;
            }
            else   //关键字
            {
                strcpy(p_caName, item->cpKey);
                strcpy(p_caValue, item->cpValue);
                iRet = 2;
                goto LAB_EXIT;
            }
        }
        iIdx++;
    }

LAB_EXIT:
    ZTMutex_Unlock(p_iniCtrl->mutex);
    return iRet;
}
