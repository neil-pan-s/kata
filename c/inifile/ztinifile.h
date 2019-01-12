#ifndef __ZTINIFILE_H__
#define __ZTINIFILE_H__

#include "ztmutex.h"

/*线程安全的*/

typedef struct
{
    int   iType;         //1:扇区, 2:值
    char *cpKey;         //关键字
    char *cpValue;       //值
    char *cpRemark;      //注释
    void *next;          //下一个元素
    void *pre;           //上一个元素
}TIniItem;

typedef struct
{
    char caPath[128]; //文件的原始路径
    TIniItem *header; //头指针
    TMutex *mutex;   //互斥对象,用于实现线程安全控制
} TInifile;


/*
    p_caPath      配置文件路径
    p_blLoad      载入配置文件是否成功
*/
int ZTIni_Init(TInifile **p_iniCtrl,const char *p_caPath);

int ZTIni_Close(TInifile *p_iniCtrl);

//按照配置文件形式,打印出当前的配置内容到标准输出上
void ZTIni_Print(TInifile *p_iniCtrl);

//保存配置到指定的配置文件,如果p_caPath为NULL,则保存到原配置文件
int ZTIni_Save(TInifile *p_iniCtrl,const char *p_caPath);

/*
    取得指定扇区下指定关键字的配置值,如果关键字不存在,则返回默认值,p_caValue可以为NULL
    返回值也是取得的关键字值,应用程序根据自己需要看取得值
    p_caSection         扇区
    p_caKey             关键字
    p_caValue           取得的值,可以为空,表示不需要将值保存到变量中
    p_caDef             默认值,当关键字不存在时,使用默认值返回
*/
const char* ZTIni_Get(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, char *p_caValue, const char *p_caDef);

//取得指定扇区下指定关键字的整型配置值
int ZTIni_GetInt(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, int p_iDef);

//保存关键字的值
int ZTIni_Set(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, char *p_caValue);

//保存关键字的值
int ZTIni_SetInt(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey, int p_iValue);

//删除指定的扇区
int ZTIni_DelSection(TInifile *p_iniCtrl,const char *p_caSection);

//删除指定的关键字
int ZTIni_DelKey(TInifile *p_iniCtrl,const char *p_caSection, const char *p_caKey);

//获得扇区的个数
int ZTIni_GetSecationCnt(TInifile *p_iniCtrl);

//获得指定序号的扇区名称
int ZTIni_GetSactionName(TInifile *p_iniCtrl,int p_iIdx, char *p_caName);

//取得一个指定的关键字
int ZTIni_GetKey(TInifile *p_iniCtrl,int p_iIdx, char *p_caSaction, char *p_caName, char *p_caValue);

#endif //__ZTINIFILE_H__
