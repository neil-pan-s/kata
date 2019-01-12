#include "zttlv.h"
#include "ztstring.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef NULL
    #define NULL 0
#endif

/*[method*******************************************************************************
 *def:  int ZTTlv_Init(TTlv **p_Ctrl)
 *func: 创建一个ZTTLV数据存储结构
 *args: p_Ctrl  TLV数据控制指针  
*************************************************************************************]*/
int ZTTlv_Init(TTlv **p_Ctrl)
{
    TTlv * ctrl= NULL;

    if(p_Ctrl == NULL) return -1;

    //创建tlv对象
    ctrl = (void*)malloc(sizeof(TTlv));
    memset(ctrl, 0, sizeof(TTlv));

    ctrl->header = (TTlvItem*)malloc(sizeof(TTlvItem));
    memset(ctrl->header, 0, sizeof(TTlvItem));

    //初始化互斥对象
    ZTMutex_Init(&(ctrl->mutex));

    *p_Ctrl = ctrl;
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTTlv_Destroy(TTlv *p_Ctrl)
 *func: 释放一个ZTTLV数据存储结构
 *args: p_Ctrl  TLV数据控制指针  
*************************************************************************************]*/
int ZTTlv_Destroy(TTlv *p_Ctrl)
{
    TTlvItem *delitem=NULL;
    TTlvItem *item=NULL;
    TTlv     *ctrl=(TTlv*)p_Ctrl;

    if(p_Ctrl == NULL ) return -1;

    ZTMutex_Lock(ctrl->mutex);

    //释放链表
    item = ctrl->header;
    while( item->next != NULL )
    {
        delitem = (TTlvItem*)(item->next);
        item->next = delitem->next;      //从链表中删除该节点
        if( delitem->caValue != NULL ) free(delitem->caValue);
        free(delitem);
        delitem = NULL;
    }

    //释放头指针
    free(ctrl->header);
    ctrl->header = NULL;

    ZTMutex_Unlock(ctrl->mutex);
    ZTMutex_Destroy(ctrl->mutex);

    free(p_Ctrl);
    p_Ctrl = NULL;    
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTTlv_Set(TTlv *p_Ctrl,const char *p_caTag, const char *p_caValue, int p_iLn)
 *func: 添加tlv数据,如果标签已经存在,则修改该值为新的值
 *args: p_Ctrl  TLV数据控制指针  
        p_caTag     标签
        p_caValue   标签的值
        p_iLn       值的长度
*************************************************************************************]*/
int ZTTlv_Set(TTlv *p_Ctrl,const char *p_caTag, const char *p_caValue, int p_iLn)
{
    TTlvItem *item=NULL;
    TTlvItem *newitem=NULL;
    TTlv     *ctrl=(TTlv*)p_Ctrl;

    if(p_Ctrl == NULL ) return -1;
    if( p_iLn == -1 ) p_iLn = strlen(p_caValue);

    ZTMutex_Lock(ctrl->mutex);

    //查找指定名称的数据项是否存在
    item = ctrl->header;
    while( item->next != NULL )
    {
        item = (TTlvItem*)(item->next);
        if( strcmp(item->caTag, p_caTag)==0 )
        {
            if( item->caValue != NULL ) free(item->caValue);
            item->caValue = (char *)malloc(p_iLn + 4);
            memset(item->caValue, 0, p_iLn+4);
            memcpy(item->caValue, p_caValue, p_iLn);
            item->iValueLn = p_iLn;
            goto LAB_EXIT;
        }
    }

    //找到最后一个节点
    item = ctrl->header;
    while( item->next != NULL )
    {
        item = (TTlvItem*)(item->next);
    }

    //创建一个新节点
    newitem = (TTlvItem*)malloc(sizeof(TTlvItem));
    memset(newitem, 0, sizeof(TTlvItem));
    strcpy(newitem->caTag, p_caTag);
    newitem->caValue = (char *)malloc(p_iLn + 4);
    memset(newitem->caValue, 0, p_iLn+4);
    memcpy(newitem->caValue, p_caValue, p_iLn);
    newitem->iValueLn = p_iLn;

    //将节点添加到最后
    item->next = newitem;

LAB_EXIT:
    ZTMutex_Unlock(ctrl->mutex);
    return 0;
}


/*[method*******************************************************************************
 *def:  int ZTTlv_Print(TTlv *p_Ctrl,int p_iMaxLn)
 *func: 打印tlv数据
 *args: p_Ctrl  TLV数据控制指针
        p_iMaxLn      打印数据的最大长度
*************************************************************************************]*/
int ZTTlv_Print(TTlv *p_Ctrl,int p_iMaxLn)
{
    int  iMaxLn=0, i=0;
    char caFormat[48]={0};
    TTlvItem *item=NULL;
    TTlv     *ctrl=(TTlv*)p_Ctrl;

    if(p_Ctrl == NULL ) return -1;

    ZTMutex_Lock(ctrl->mutex);

    //查找名称的最大长度
    iMaxLn = 0;
    item = ctrl->header;
    while( item->next != NULL )
    {
        item = (TTlvItem*)(item->next);
        if( iMaxLn < (int)strlen(item->caTag) )
        {
            iMaxLn = strlen(item->caTag);
        }
    }

    memset(caFormat, 0, sizeof(caFormat));
    sprintf(caFormat, "  %c-%ds", '%', iMaxLn);

    //循环打印数据
    item = ctrl->header;

    while( item->next != NULL )
    {
        item = (TTlvItem*)(item->next);
        printf(caFormat, item->caTag);
        printf("[%04d]:", item->iValueLn);
        i = 0;
        while( (i < p_iMaxLn) && (i < item->iValueLn) )
        {
            if( (32<(item->caValue[i]&0xff)) && ((item->caValue[i]&0xff)<127)) //英文可见字符
            {
                //printf("%c", item->caValue[i]);
                printf("%02X", item->caValue[i]&0xff);
                i++;
            }
            else if( 161<=(item->caValue[i]&0xff) && (item->caValue[i]&0xff)<=254 &&
                     161<=(item->caValue[i+1]&0xff) && (item->caValue[i+1]&0xff)<=254 )  //汉字
            {
                printf("%c%c", item->caValue[i]&0xff, item->caValue[i+1]&0xff );
                i = i + 2;
            }
            else  //英文不可见字符
            {
                printf("%02X", item->caValue[i]&0xff);
                i++;
            }
        }
        printf("\n");
    }

    ZTMutex_Unlock(ctrl->mutex);
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTTlv_Clear(TTlv *p_Ctrl)
 *func: 清空所有的tlv名值对
 *args: p_Ctrl  TLV数据控制指针
*************************************************************************************]*/
int ZTTlv_Clear(TTlv *p_Ctrl)
{
    TTlvItem *delitem=NULL;
    TTlvItem *item=NULL;
    TTlv     *ctrl=(TTlv*)p_Ctrl;

    ZTMutex_Lock(ctrl->mutex);

    //释放链表
    item = ctrl->header;
    while( item->next != NULL )
    {
        delitem = (TTlvItem*)(item->next);
        item->next = delitem->next;      //从链表中删除该节点
        if( delitem->caValue != NULL ) free(delitem->caValue);
        free(delitem);
        delitem = NULL;
    }

    ctrl->header->next = NULL;

    ZTMutex_Unlock(ctrl->mutex);
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTTlv_ClearTag(TTlv *p_Ctrl,const char *p_caTag)
 *func: 清空指定类型的tlv名值对
 *args: p_Ctrl  TLV数据控制指针
        p_caTag    标签前缀,用于清空某一类型的标签
*************************************************************************************]*/
int ZTTlv_ClearTag(TTlv *p_Ctrl,const char *p_caTag)
{
    TTlvItem *item=NULL;
    TTlvItem *curitem=NULL;
    TTlv     *ctrl=(TTlv*)p_Ctrl;

    if(p_Ctrl == NULL ) return -1;

    ZTMutex_Lock(ctrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        curitem = (TTlvItem*)(item->next);
        if( memcmp(curitem->caTag, p_caTag, strlen(p_caTag))==0 )
        {
            item->next = curitem->next;
            if( curitem->caValue != NULL ) free(curitem->caValue);
            free(curitem);
            curitem = NULL;
        }
        else
        {
            item = (TTlvItem*)(item->next);
        }
    }

    ZTMutex_Unlock(ctrl->mutex);
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTTlv_Get(TTlv *p_Ctrl,const char *p_caTag, char *p_caValue,int *p_iLn)
 *func: 取得指定类型的名值对
 *args: p_Ctrl  TLV数据控制指针 
        p_caTag      标签
        p_caValue    取得的标签值
        p_iLn        标签数据长度
 *ret:  取得的值的长度
*************************************************************************************]*/
int ZTTlv_Get(TTlv *p_Ctrl,const char *p_caTag, char *p_caValue,int *p_iLn)
{
    int iValueLn=0;
    TTlvItem *item=NULL;
    TTlvItem *curitem=NULL;
    TTlv     *ctrl=(TTlv*)p_Ctrl;

    if(p_Ctrl == NULL ) return -1;
    ZTMutex_Lock(ctrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        curitem = (TTlvItem*)(item->next);
        if( strcmp(curitem->caTag, p_caTag )==0 )
        {
            memcpy(p_caValue, curitem->caValue, curitem->iValueLn);
            iValueLn = curitem->iValueLn;
            break;
        }
        item = (TTlvItem*)(item->next);
    }

    ZTMutex_Unlock(ctrl->mutex);

    *p_iLn = iValueLn;
    return iValueLn;
}

/*[method*******************************************************************************
 *def:  int ZTTlv_GetValue(TTlv *p_Ctrl,const char *p_caTag)
 *func: 取得指定类型的名值对
 *args: p_Ctrl  TLV数据控制指针 
        p_caTag      标签
 *ret:  取得的标签值
*************************************************************************************]*/
char *ZTTlv_GetTagValue(TTlv *p_Ctrl,const char *p_caTag)
{
    TTlvItem *item=NULL;
    TTlvItem *curitem=NULL;
    TTlv     *ctrl=(TTlv*)p_Ctrl;

    if(p_Ctrl == NULL ) return "";
    ZTMutex_Lock(ctrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        curitem = (TTlvItem*)(item->next);
        if( strcmp(curitem->caTag, p_caTag )==0 )
        {
            ZTMutex_Unlock(ctrl->mutex);
            return curitem->caValue;
        }
        item = (TTlvItem*)(item->next);
    }

    ZTMutex_Unlock(ctrl->mutex);

    return "";
}


/*[method*******************************************************************************
 *def:  int ZTTlv_GetValue(TTlv *p_Ctrl,const char *p_caTag)
 *func: 取得指定类型的名值对
 *args: p_Ctrl  TLV数据控制指针 
        p_caTag      标签
 *ret:  取得的标签值长度
*************************************************************************************]*/
int ZTTlv_GetTagLen(TTlv *p_Ctrl,const char *p_caTag)
{
    TTlvItem *item=NULL;
    TTlvItem *curitem=NULL;
    TTlv     *ctrl=(TTlv*)p_Ctrl;

    if(p_Ctrl == NULL ) return -1;
    ZTMutex_Lock(ctrl->mutex);

    item = ctrl->header;
    while( item->next != NULL )
    {
        curitem = (TTlvItem*)(item->next);
        if( strcmp(curitem->caTag, p_caTag )==0 )
        {
            ZTMutex_Unlock(ctrl->mutex);
            return curitem->iValueLn;
        }
        item = (TTlvItem*)(item->next);
    }

    ZTMutex_Unlock(ctrl->mutex);

    return -1;
}

/*[method*******************************************************************************
 *def:  int ZTTlv_Seal(TTlv *p_Ctrl,const char *p_caTag, int p_iBCD, char *p_caBuff, int *p_iBuffLn)
 *func: 组指定域到包中 
 *args: p_Ctrl  TLV数据控制指针 
        p_caTag     标签
        p_iBDC      是否压缩
        p_caBuff    组包用的缓冲区
        p_iBuffLn   缓冲区已有的数据长度
 *output:  p_iBffLn   组包后新的数据长度
*************************************************************************************]*/
int ZTTlv_Seal(TTlv *p_Ctrl,const char *p_caTag, int p_iBCD, char *p_caBuff, int *p_iBuffLn)
{
    int   iValueLn=0;
    char *cpValue=NULL;
    TTlvItem *item=NULL;
    TTlvItem *curitem=NULL;
    TTlv     *ctrl=(TTlv*)p_Ctrl;

    if(p_Ctrl == NULL ) return -1;
    ZTMutex_Lock(ctrl->mutex);

    //取得值
    item = ctrl->header;
    while( item->next != NULL )
    {
        curitem = (TTlvItem*)(item->next);
        if( strcmp(curitem->caTag, p_caTag )==0 )
        {
            iValueLn = curitem->iValueLn;
            cpValue = (char *)malloc(iValueLn+4);
            memset(cpValue, 0, iValueLn+4);
            memcpy(cpValue, curitem->caValue, iValueLn);
            break;
        }
        item = (TTlvItem*)(item->next);
    }
    ZTMutex_Unlock(ctrl->mutex);
    if( (iValueLn == 0) && (cpValue != NULL) )
    {
        free(cpValue);
        return -1;
    }

    //组标签
    ZT_Asc2Bcd((char *)p_caTag , strlen(p_caTag),(unsigned char *)(p_caBuff+(*p_iBuffLn)),0);

    *p_iBuffLn = (*p_iBuffLn) + (strlen(p_caTag)+1)/2;
    //组长度
    if(iValueLn < 128)
    {    
        //单字节长度处理
        p_caBuff[*p_iBuffLn+0] = iValueLn;
        *p_iBuffLn = (*p_iBuffLn) + 1;
    }
    else if(iValueLn < 256)
    {
        //两字节长度处理
        p_caBuff[*p_iBuffLn+0] = 0x81;  
        p_caBuff[*p_iBuffLn+1] = iValueLn % 256;
        *p_iBuffLn = (*p_iBuffLn) + 2;      
    }
    else if(iValueLn < 256*256)
    {
        //三字节长度处理
        p_caBuff[*p_iBuffLn+0] = 0x82;  
        p_caBuff[*p_iBuffLn+1] = iValueLn / 256;
        p_caBuff[*p_iBuffLn+2] = iValueLn % 256 ;        
        *p_iBuffLn = (*p_iBuffLn) + 3;      
    }
    else
    {
        //长度异常
        return -2;
    }

    //组值
    if( p_iBCD == 1 )  //压缩
    {
        ZT_Asc2Bcd(cpValue , strlen(cpValue),(unsigned char *)(p_caBuff+(*p_iBuffLn)),0);
        *p_iBuffLn = (*p_iBuffLn) + iValueLn / 2;
    }
    else
    {
        memcpy(p_caBuff+(*p_iBuffLn), cpValue, iValueLn);
        *p_iBuffLn = (*p_iBuffLn) + iValueLn;
    }

    if( cpValue != NULL ) free(cpValue);
    return *p_iBuffLn;
}

/*[method*******************************************************************************
 *def:  int ZTTlv_Package(TTlv *p_Ctrl,char *p_caTag,char *p_caBuff, int *p_ipLn)
 *func: 复合域打包 
 *args: p_caTag     复合域标签
        p_caBuff    组包用的缓冲区
        p_ipLn      缓冲区长度
 *output:  p_ipLn   组包后新的数据长度
*************************************************************************************]*/
int ZTTlv_Package(TTlv *p_Ctrl,char *p_caTag,char *p_caBuff, int *p_ipLn)
{
    int iLen;
    char *cpBuff=NULL;

    cpBuff = (char *)malloc((*p_ipLn) + 8 );
    memset(cpBuff, 0, (*p_ipLn) + 8 );

    //Tag名处理
    ZT_Asc2Bcd((char *)p_caTag , strlen(p_caTag),(unsigned char *)cpBuff,0);
    iLen = (strlen(p_caTag)+1)/2;    

    //组长度
    if(*p_ipLn < 128)
    {    
        //单字节长度处理
        cpBuff[iLen] = *p_ipLn;
        iLen += 1;
    }
    else if(*p_ipLn < 256)
    {
        //两字节长度处理
        cpBuff[iLen] = 0x81;  
        cpBuff[iLen+1] = (*p_ipLn) % 256;
        iLen += 2;      
    }
    else if(*p_ipLn < 256*256)
    {
        //三字节长度处理        
        cpBuff[iLen] = 0x82;  
        cpBuff[iLen+1] = (*p_ipLn) / 256;
        cpBuff[iLen+2] = (*p_ipLn) % 256 ;        
        iLen += 3;      
    }
    else
    {
        //长度异常
        return -2;
    }

    ZTTlv_Set(p_Ctrl,p_caTag, p_caBuff, *p_ipLn);

    memcpy(cpBuff+iLen, p_caBuff, *p_ipLn);
    memcpy(p_caBuff, cpBuff, (*p_ipLn)+iLen);
    *p_ipLn = (*p_ipLn) + iLen;
    free(cpBuff);
    return 0;    
}


/*[method*******************************************************************************
 *def:  public void ZTTlv2::unseal(const char *p_caBuff, int p_iLn)
 *func: 解包 
 *args: p_caBuff     需要解包的数据
        p_iLn        数据的长度
*************************************************************************************]*/
int ZTTlv_Unseal(TTlv *p_Ctrl,const char *p_caBuff, int p_iLn)
{
    char  caTag[8]={0}, caLen[8]={0},caTagTmp[8]={0};
    char *caBuff=NULL,*caBuffTmp = NULL;
    int   iPos, iLen;

    iPos = 0;
    while( iPos < p_iLn )
    {
        //tag 处理
        memset(caTag, 0, sizeof(caTag));        
        memset(caTagTmp, 0, sizeof(caTagTmp));
        memcpy(caTagTmp, p_caBuff+iPos, 2);

        //单字节tag 
        //当 bit5-bit1代表串行号，当5个位都为1时，需要将tag域扩展到下一个字节中，也就是Tag占2个字节
        if((caTagTmp[0]&0x1F) != 0x1F)
        {
            iPos = iPos + 1;
            ZT_Bcd2Asc((unsigned char *)caTagTmp, 2, caTag,0);    
        }   
        else 
        {
            iPos = iPos + 2;
            ZT_Bcd2Asc((unsigned char *)caTagTmp, 4, caTag,0);            
        }    
        
        //长度处理
        memset(caLen, 0, sizeof(caLen));
        memcpy(caLen, p_caBuff+iPos, 2);
        
        if((caLen[0]&0x82) == 0x82) 
        {
            //三字节长度处理
            iPos = iPos + 3;
            iLen = (caLen[1]&0xff)*256 + (caLen[1]&0xff);
        }        
        else if((caLen[0]&0x81) == 0x81 )  
        {
            //双字节长度处理
            iPos = iPos + 2;
            iLen = caLen[1]&0xff;
        }
        else if( caLen[0] < 128)  
        {
            //单字节长度处理
            iPos = iPos + 1;
            iLen = caLen[0];
        }
        else
        {
            //长度异常
            return -2;
        }  
        
        caBuff = (char *)malloc(iLen+4);      
        memset(caBuff, 0, iLen+4);
        if( (caLen[0]&0x80) == 0x80 )   //数据压缩
        {
            caBuffTmp =  (char *)malloc(iLen+4);
            memset(caBuffTmp, 0, iLen+4);            
            memcpy(caBuffTmp, p_caBuff+iPos, (iLen+1) / 2 );
            ZT_Bcd2Asc((unsigned char *)caBuffTmp, (iLen+1) / 2, caBuff,0);
            iPos = iPos + (iLen+1) / 2;
            free(caBuffTmp);
        }
        else
        {
            memcpy(caBuff, p_caBuff+iPos, iLen);
            iPos = iPos + iLen;
        }
        ZTTlv_Set(p_Ctrl,caTag, caBuff, iLen);
        free(caBuff);
    }
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTTlv_UnPackage(TTlv *p_Ctrl,const char *p_caBuff, int p_ipLn)
 *func: 复合域解包 
 *args: p_caBuff    解包用的缓冲区
        p_ipLn      缓冲区长度 暂未使用 可传0
*************************************************************************************]*/
int ZTTlv_UnPackage(TTlv *p_Ctrl,const char *p_caBuff, int p_ipLn)
{
    char  caTag[8]={0}, caLen[8]={0};
    char *caBuff=NULL;
    int   iPos, iLen;

    iPos = 0;

    //tag 处理
    memset(caTag, 0, sizeof(caTag)); 

    //bit6代表的是数据元结构，bit6 = 0 属于简单数据元结构，bit6 = 1 属于结构（复合）数据元结构
    if((p_caBuff[0]&0x20) == 0x20)
    {
        iPos = iPos + 1;
        ZT_Bcd2Asc((unsigned char *)p_caBuff, 2, caTag,0); 
    }   
    else 
    {   
        //非复合域 
        return -1;          
    }    
    
    //长度处理
    memset(caLen, 0, sizeof(caLen));
    memcpy(caLen, p_caBuff+iPos, 2);
    
    if((caLen[0]&0x82) == 0x82) 
    {
        //三字节长度处理
        iPos = iPos + 3;
        iLen = (caLen[1]&0xff)*256 + (caLen[1]&0xff);
    }        
    else if((caLen[0]&0x81) == 0x81 )  
    {
        //双字节长度处理
        iPos = iPos + 2;
        iLen = caLen[1]&0xff;
    }
    else if( caLen[0] < 128)  
    {
        //单字节长度处理
        iPos = iPos + 1;
        iLen = caLen[0];
    }
    else
    {
        //长度异常
        return -2;
    }  
    
    caBuff = (char *)malloc(iLen+4);      
    memset(caBuff, 0, iLen+4);   
    memcpy(caBuff, p_caBuff+iPos, iLen);
    iPos = iPos + iLen;
    ZTTlv_Set(p_Ctrl,caTag, caBuff, iLen);
    free(caBuff);
    return 0;    
}