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
 *func: ����һ��ZTTLV���ݴ洢�ṹ
 *args: p_Ctrl  TLV���ݿ���ָ��  
*************************************************************************************]*/
int ZTTlv_Init(TTlv **p_Ctrl)
{
    TTlv * ctrl= NULL;

    if(p_Ctrl == NULL) return -1;

    //����tlv����
    ctrl = (void*)malloc(sizeof(TTlv));
    memset(ctrl, 0, sizeof(TTlv));

    ctrl->header = (TTlvItem*)malloc(sizeof(TTlvItem));
    memset(ctrl->header, 0, sizeof(TTlvItem));

    //��ʼ���������
    ZTMutex_Init(&(ctrl->mutex));

    *p_Ctrl = ctrl;
    return 0;
}

/*[method*******************************************************************************
 *def:  int ZTTlv_Destroy(TTlv *p_Ctrl)
 *func: �ͷ�һ��ZTTLV���ݴ洢�ṹ
 *args: p_Ctrl  TLV���ݿ���ָ��  
*************************************************************************************]*/
int ZTTlv_Destroy(TTlv *p_Ctrl)
{
    TTlvItem *delitem=NULL;
    TTlvItem *item=NULL;
    TTlv     *ctrl=(TTlv*)p_Ctrl;

    if(p_Ctrl == NULL ) return -1;

    ZTMutex_Lock(ctrl->mutex);

    //�ͷ�����
    item = ctrl->header;
    while( item->next != NULL )
    {
        delitem = (TTlvItem*)(item->next);
        item->next = delitem->next;      //��������ɾ���ýڵ�
        if( delitem->caValue != NULL ) free(delitem->caValue);
        free(delitem);
        delitem = NULL;
    }

    //�ͷ�ͷָ��
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
 *func: ���tlv����,�����ǩ�Ѿ�����,���޸ĸ�ֵΪ�µ�ֵ
 *args: p_Ctrl  TLV���ݿ���ָ��  
        p_caTag     ��ǩ
        p_caValue   ��ǩ��ֵ
        p_iLn       ֵ�ĳ���
*************************************************************************************]*/
int ZTTlv_Set(TTlv *p_Ctrl,const char *p_caTag, const char *p_caValue, int p_iLn)
{
    TTlvItem *item=NULL;
    TTlvItem *newitem=NULL;
    TTlv     *ctrl=(TTlv*)p_Ctrl;

    if(p_Ctrl == NULL ) return -1;
    if( p_iLn == -1 ) p_iLn = strlen(p_caValue);

    ZTMutex_Lock(ctrl->mutex);

    //����ָ�����Ƶ��������Ƿ����
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

    //�ҵ����һ���ڵ�
    item = ctrl->header;
    while( item->next != NULL )
    {
        item = (TTlvItem*)(item->next);
    }

    //����һ���½ڵ�
    newitem = (TTlvItem*)malloc(sizeof(TTlvItem));
    memset(newitem, 0, sizeof(TTlvItem));
    strcpy(newitem->caTag, p_caTag);
    newitem->caValue = (char *)malloc(p_iLn + 4);
    memset(newitem->caValue, 0, p_iLn+4);
    memcpy(newitem->caValue, p_caValue, p_iLn);
    newitem->iValueLn = p_iLn;

    //���ڵ���ӵ����
    item->next = newitem;

LAB_EXIT:
    ZTMutex_Unlock(ctrl->mutex);
    return 0;
}


/*[method*******************************************************************************
 *def:  int ZTTlv_Print(TTlv *p_Ctrl,int p_iMaxLn)
 *func: ��ӡtlv����
 *args: p_Ctrl  TLV���ݿ���ָ��
        p_iMaxLn      ��ӡ���ݵ���󳤶�
*************************************************************************************]*/
int ZTTlv_Print(TTlv *p_Ctrl,int p_iMaxLn)
{
    int  iMaxLn=0, i=0;
    char caFormat[48]={0};
    TTlvItem *item=NULL;
    TTlv     *ctrl=(TTlv*)p_Ctrl;

    if(p_Ctrl == NULL ) return -1;

    ZTMutex_Lock(ctrl->mutex);

    //�������Ƶ���󳤶�
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

    //ѭ����ӡ����
    item = ctrl->header;

    while( item->next != NULL )
    {
        item = (TTlvItem*)(item->next);
        printf(caFormat, item->caTag);
        printf("[%04d]:", item->iValueLn);
        i = 0;
        while( (i < p_iMaxLn) && (i < item->iValueLn) )
        {
            if( (32<(item->caValue[i]&0xff)) && ((item->caValue[i]&0xff)<127)) //Ӣ�Ŀɼ��ַ�
            {
                //printf("%c", item->caValue[i]);
                printf("%02X", item->caValue[i]&0xff);
                i++;
            }
            else if( 161<=(item->caValue[i]&0xff) && (item->caValue[i]&0xff)<=254 &&
                     161<=(item->caValue[i+1]&0xff) && (item->caValue[i+1]&0xff)<=254 )  //����
            {
                printf("%c%c", item->caValue[i]&0xff, item->caValue[i+1]&0xff );
                i = i + 2;
            }
            else  //Ӣ�Ĳ��ɼ��ַ�
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
 *func: ������е�tlv��ֵ��
 *args: p_Ctrl  TLV���ݿ���ָ��
*************************************************************************************]*/
int ZTTlv_Clear(TTlv *p_Ctrl)
{
    TTlvItem *delitem=NULL;
    TTlvItem *item=NULL;
    TTlv     *ctrl=(TTlv*)p_Ctrl;

    ZTMutex_Lock(ctrl->mutex);

    //�ͷ�����
    item = ctrl->header;
    while( item->next != NULL )
    {
        delitem = (TTlvItem*)(item->next);
        item->next = delitem->next;      //��������ɾ���ýڵ�
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
 *func: ���ָ�����͵�tlv��ֵ��
 *args: p_Ctrl  TLV���ݿ���ָ��
        p_caTag    ��ǩǰ׺,�������ĳһ���͵ı�ǩ
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
 *func: ȡ��ָ�����͵���ֵ��
 *args: p_Ctrl  TLV���ݿ���ָ�� 
        p_caTag      ��ǩ
        p_caValue    ȡ�õı�ǩֵ
        p_iLn        ��ǩ���ݳ���
 *ret:  ȡ�õ�ֵ�ĳ���
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
 *func: ȡ��ָ�����͵���ֵ��
 *args: p_Ctrl  TLV���ݿ���ָ�� 
        p_caTag      ��ǩ
 *ret:  ȡ�õı�ǩֵ
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
 *func: ȡ��ָ�����͵���ֵ��
 *args: p_Ctrl  TLV���ݿ���ָ�� 
        p_caTag      ��ǩ
 *ret:  ȡ�õı�ǩֵ����
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
 *func: ��ָ���򵽰��� 
 *args: p_Ctrl  TLV���ݿ���ָ�� 
        p_caTag     ��ǩ
        p_iBDC      �Ƿ�ѹ��
        p_caBuff    ����õĻ�����
        p_iBuffLn   ���������е����ݳ���
 *output:  p_iBffLn   ������µ����ݳ���
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

    //ȡ��ֵ
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

    //���ǩ
    ZT_Asc2Bcd((char *)p_caTag , strlen(p_caTag),(unsigned char *)(p_caBuff+(*p_iBuffLn)),0);

    *p_iBuffLn = (*p_iBuffLn) + (strlen(p_caTag)+1)/2;
    //�鳤��
    if(iValueLn < 128)
    {    
        //���ֽڳ��ȴ���
        p_caBuff[*p_iBuffLn+0] = iValueLn;
        *p_iBuffLn = (*p_iBuffLn) + 1;
    }
    else if(iValueLn < 256)
    {
        //���ֽڳ��ȴ���
        p_caBuff[*p_iBuffLn+0] = 0x81;  
        p_caBuff[*p_iBuffLn+1] = iValueLn % 256;
        *p_iBuffLn = (*p_iBuffLn) + 2;      
    }
    else if(iValueLn < 256*256)
    {
        //���ֽڳ��ȴ���
        p_caBuff[*p_iBuffLn+0] = 0x82;  
        p_caBuff[*p_iBuffLn+1] = iValueLn / 256;
        p_caBuff[*p_iBuffLn+2] = iValueLn % 256 ;        
        *p_iBuffLn = (*p_iBuffLn) + 3;      
    }
    else
    {
        //�����쳣
        return -2;
    }

    //��ֵ
    if( p_iBCD == 1 )  //ѹ��
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
 *func: �������� 
 *args: p_caTag     �������ǩ
        p_caBuff    ����õĻ�����
        p_ipLn      ����������
 *output:  p_ipLn   ������µ����ݳ���
*************************************************************************************]*/
int ZTTlv_Package(TTlv *p_Ctrl,char *p_caTag,char *p_caBuff, int *p_ipLn)
{
    int iLen;
    char *cpBuff=NULL;

    cpBuff = (char *)malloc((*p_ipLn) + 8 );
    memset(cpBuff, 0, (*p_ipLn) + 8 );

    //Tag������
    ZT_Asc2Bcd((char *)p_caTag , strlen(p_caTag),(unsigned char *)cpBuff,0);
    iLen = (strlen(p_caTag)+1)/2;    

    //�鳤��
    if(*p_ipLn < 128)
    {    
        //���ֽڳ��ȴ���
        cpBuff[iLen] = *p_ipLn;
        iLen += 1;
    }
    else if(*p_ipLn < 256)
    {
        //���ֽڳ��ȴ���
        cpBuff[iLen] = 0x81;  
        cpBuff[iLen+1] = (*p_ipLn) % 256;
        iLen += 2;      
    }
    else if(*p_ipLn < 256*256)
    {
        //���ֽڳ��ȴ���        
        cpBuff[iLen] = 0x82;  
        cpBuff[iLen+1] = (*p_ipLn) / 256;
        cpBuff[iLen+2] = (*p_ipLn) % 256 ;        
        iLen += 3;      
    }
    else
    {
        //�����쳣
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
 *func: ��� 
 *args: p_caBuff     ��Ҫ���������
        p_iLn        ���ݵĳ���
*************************************************************************************]*/
int ZTTlv_Unseal(TTlv *p_Ctrl,const char *p_caBuff, int p_iLn)
{
    char  caTag[8]={0}, caLen[8]={0},caTagTmp[8]={0};
    char *caBuff=NULL,*caBuffTmp = NULL;
    int   iPos, iLen;

    iPos = 0;
    while( iPos < p_iLn )
    {
        //tag ����
        memset(caTag, 0, sizeof(caTag));        
        memset(caTagTmp, 0, sizeof(caTagTmp));
        memcpy(caTagTmp, p_caBuff+iPos, 2);

        //���ֽ�tag 
        //�� bit5-bit1�����кţ���5��λ��Ϊ1ʱ����Ҫ��tag����չ����һ���ֽ��У�Ҳ����Tagռ2���ֽ�
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
        
        //���ȴ���
        memset(caLen, 0, sizeof(caLen));
        memcpy(caLen, p_caBuff+iPos, 2);
        
        if((caLen[0]&0x82) == 0x82) 
        {
            //���ֽڳ��ȴ���
            iPos = iPos + 3;
            iLen = (caLen[1]&0xff)*256 + (caLen[1]&0xff);
        }        
        else if((caLen[0]&0x81) == 0x81 )  
        {
            //˫�ֽڳ��ȴ���
            iPos = iPos + 2;
            iLen = caLen[1]&0xff;
        }
        else if( caLen[0] < 128)  
        {
            //���ֽڳ��ȴ���
            iPos = iPos + 1;
            iLen = caLen[0];
        }
        else
        {
            //�����쳣
            return -2;
        }  
        
        caBuff = (char *)malloc(iLen+4);      
        memset(caBuff, 0, iLen+4);
        if( (caLen[0]&0x80) == 0x80 )   //����ѹ��
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
 *func: �������� 
 *args: p_caBuff    ����õĻ�����
        p_ipLn      ���������� ��δʹ�� �ɴ�0
*************************************************************************************]*/
int ZTTlv_UnPackage(TTlv *p_Ctrl,const char *p_caBuff, int p_ipLn)
{
    char  caTag[8]={0}, caLen[8]={0};
    char *caBuff=NULL;
    int   iPos, iLen;

    iPos = 0;

    //tag ����
    memset(caTag, 0, sizeof(caTag)); 

    //bit6�����������Ԫ�ṹ��bit6 = 0 ���ڼ�����Ԫ�ṹ��bit6 = 1 ���ڽṹ�����ϣ�����Ԫ�ṹ
    if((p_caBuff[0]&0x20) == 0x20)
    {
        iPos = iPos + 1;
        ZT_Bcd2Asc((unsigned char *)p_caBuff, 2, caTag,0); 
    }   
    else 
    {   
        //�Ǹ����� 
        return -1;          
    }    
    
    //���ȴ���
    memset(caLen, 0, sizeof(caLen));
    memcpy(caLen, p_caBuff+iPos, 2);
    
    if((caLen[0]&0x82) == 0x82) 
    {
        //���ֽڳ��ȴ���
        iPos = iPos + 3;
        iLen = (caLen[1]&0xff)*256 + (caLen[1]&0xff);
    }        
    else if((caLen[0]&0x81) == 0x81 )  
    {
        //˫�ֽڳ��ȴ���
        iPos = iPos + 2;
        iLen = caLen[1]&0xff;
    }
    else if( caLen[0] < 128)  
    {
        //���ֽڳ��ȴ���
        iPos = iPos + 1;
        iLen = caLen[0];
    }
    else
    {
        //�����쳣
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