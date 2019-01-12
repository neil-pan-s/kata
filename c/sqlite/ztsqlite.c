#include "ztsqlite.h"
#include "sqlite3.h"
#include "zticonv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool blexitflag=true;

/*[method*******************************************************************************
 *def:  public void zt_sqlite_column_text(sqlite3_stmt *ppStmt, int p_iCol, char *p_caValue)
 *func: 获取sqlite数据库当前记录指定字段的值。
 *args: #ppStmt        查询记录集
        #p_iCol        列序号, 0开始
        #p_caValue     目标值
 *auth: coon  2012-08-26   第一次编写
*************************************************************************************]*/
void zt_sqlite_column_text(sqlite3_stmt *ppStmt, int p_iCol, char *p_caValue, int p_iSize)
{
    char *caTmp=NULL;

    caTmp = (char*)malloc(p_iSize);

    if( SQLITE_TEXT == sqlite3_column_type(ppStmt, p_iCol) )
    {
        switch(sqlite3_column_type(ppStmt, p_iCol))
        {
            case SQLITE_TEXT:
                memset(caTmp, 0, p_iSize);
                sprintf(caTmp, "%s", sqlite3_column_text(ppStmt, p_iCol));
                ZTIconv_Convert("utf-8", "gb18030", caTmp, strlen(caTmp), p_caValue, p_iSize);
                free(caTmp);
                return;
            default:
                printf("======ERROR the field[%d] datatype is not text.======\n", p_iCol);
                if( blexitflag ) exit(0);
                return;
        }
    }
    else
    {
        p_caValue[0] = 0;
    }
    free(caTmp);
}

/*[method*******************************************************************************
 *def:  public void zt_sqlite_column_int(sqlite3_stmt *ppStmt, int p_iCol, int *p_iValue)
 *func: 获取sqlite数据库当前记录指定字段的值。
 *args: #ppStmt        查询记录集
        #p_iCol        列序号, 0开始
        #p_caValue     目标值
 *auth: coon  2012-08-26   第一次编写
*************************************************************************************]*/
void zt_sqlite_column_int(sqlite3_stmt *ppStmt, int p_iCol, int *p_iValue)
{
    if( SQLITE_INTEGER == sqlite3_column_type(ppStmt, p_iCol) )
    {
        switch(sqlite3_column_type(ppStmt, p_iCol))
        {
            case SQLITE_INTEGER:
                *p_iValue = sqlite3_column_int(ppStmt, p_iCol);
                return;
            default:
                printf("======ERROR the field[%d] datatype is not integer.======\n", p_iCol);
                if( blexitflag ) exit(0);
                return;
        }
    }
    else
    {
        *p_iValue = 0;
    }
}

/*[method*******************************************************************************
 *def:  public int zt_sqlite_column_int(sqlite3_stmt *ppStmt, int p_iCol)
 *func: 获取sqlite数据库当前记录指定字段的值。
 *args: #ppStmt        查询记录集
        #p_iCol        列序号, 0开始
 *auth: coon  2012-08-26   第一次编写
*************************************************************************************]*/
int zt_sqlite_column_int(sqlite3_stmt *ppStmt, int p_iCol)
{
    if( SQLITE_INTEGER == sqlite3_column_type(ppStmt, p_iCol) )
    {
        switch(sqlite3_column_type(ppStmt, p_iCol))
        {
            case SQLITE_INTEGER:
                return sqlite3_column_int(ppStmt, p_iCol);
            default:
                printf("======ERROR the field[%d] datatype is not integer.======\n", p_iCol);
                if( blexitflag ) exit(0);
                return -1;
        }
    }
    return -1;
}

/*[method*******************************************************************************
 *def:  public void zt_sqlite_column_int(sqlite3_stmt *ppStmt, int p_iCol, double *p_dValue)
 *func: 获取sqlite数据库当前记录指定字段的值。
 *args: #ppStmt        查询记录集
        #p_iCol        列序号, 0开始
        #p_caValue     目标值
 *auth: coon  2012-08-26   第一次编写
*************************************************************************************]*/
void zt_sqlite_column_float(sqlite3_stmt *ppStmt, int p_iCol, double *p_dValue)
{
    if( SQLITE_FLOAT == sqlite3_column_type(ppStmt, p_iCol) )
    {
        switch(sqlite3_column_type(ppStmt, p_iCol))
        {
            case SQLITE_FLOAT:
                *p_dValue = sqlite3_column_double(ppStmt, p_iCol);
                return;
            default:
                printf("======ERROR the field[%d] datatype is not float.======\n", p_iCol);
                if( blexitflag ) exit(0);
                return;
        }
    }
    else
    {
        *p_dValue = 0.0;
    }
}

/*[method*******************************************************************************
 *def:  public double zt_sqlite_column_float(sqlite3_stmt *ppStmt, int p_iCol)
 *func: 获取sqlite数据库当前记录指定字段的值。
 *args: #ppStmt        查询记录集
        #p_iCol        列序号, 0开始
 *auth: coon  2012-08-26   第一次编写
*************************************************************************************]*/
double zt_sqlite_column_float(sqlite3_stmt *ppStmt, int p_iCol)
{
    if( SQLITE_FLOAT == sqlite3_column_type(ppStmt, p_iCol) )
    {
        switch(sqlite3_column_type(ppStmt, p_iCol))
        {
            case SQLITE_FLOAT:
                return sqlite3_column_double(ppStmt, p_iCol);
            default:
                printf("======ERROR the field[%d] datatype is not float.======\n", p_iCol);
                if( blexitflag ) exit(0);
                return -1.0;
        }
    }
    return 0.0;
}

int zt_sqlite_prepare_v2(
    sqlite3 *db,            /* Database handle */
    const char *zSql,       /* SQL statement, UTF-8 encoded */
    int nByte,              /* Maximum length of zSql in bytes. */
    sqlite3_stmt **ppStmt,  /* OUT: Statement handle */
    const char **pzTail     /* OUT: Pointer to unused portion of zSql */
)
{
    int  iRet=0;
    char caTmp[4096]={0};

    memset(caTmp, 0, sizeof(caTmp));
    code_convert("gb18030", "utf-8", (char*)zSql, strlen((char*)zSql), caTmp, 4096);

    iRet = sqlite3_prepare_v2(db, caTmp, nByte, ppStmt, pzTail);
    if( iRet != SQLITE_OK )
    {
        printf("======ERROR the sql[ %s ] is error!======\n", zSql);
        if( blexitflag ) exit(0);
        iRet = -1;
    }

    return iRet;
}

int zt_sqlite_exec(
  sqlite3 *db,                                  /* An open database */
  const char *zSql,                           /* SQL to be evaluated */
  int (*callback)(void*,int,char**,char**),  /* Callback function */
  void *,                                    /* 1st argument to callback */
  char **errmsg                              /* Error msg written here */
)
{
    int  iRet=0;
    char caTmp[5000]={0};

    memset(caTmp, 0, sizeof(caTmp));
    ZTIconv_Convert("gb18030", "utf-8", (char*)zSql, strlen((char*)zSql), caTmp, sizeof(caTmp));

    iRet = sqlite3_exec(db, caTmp, callback, NULL, errmsg);
    if( iRet != SQLITE_OK )
    {
        printf("======ERROR the sql[ %s ] is error!======\n", zSql);
        if( blexitflag ) exit(0);
        iRet = -1;
    }

    return iRet;
}

void zt_sqlite_finalize(sqlite3_stmt *ppStmt)
{
    sqlite3_finalize(ppStmt);
}

int zt_sqlite_step(sqlite3_stmt *ppStmt)
{
    return sqlite3_step(ppStmt);
}

int zt_sqlite_open(const char *p_caPath, sqlite3 **db, bool p_blExitFlag)
{
    blexitflag = p_blExitFlag;
    sqlite3_config(SQLITE_CONFIG_SERIALIZED);
    return sqlite3_open(p_caPath, db);
}

void zt_sqlite_close(sqlite3 *db)
{
    sqlite3_close(db);
}

void zt_sqlite_reset(sqlite3_stmt *ppStmt)
{
    sqlite3_reset(ppStmt);
}

/*[method*******************************************************************************
 *def:  public int  zt_sqlite_rows(sqlite3_stmt *ppStmt)
 *func: 取得记录条数,会重置记录集的指针。
 *args: #ppStmt        查询记录集
 *auth: coon  2013-02-21   第一次编写
*************************************************************************************]*/
int zt_sqlite_rows(sqlite3_stmt *ppStmt)
{
    int iRows=0;

    if( ppStmt == NULL ) return 0;

    zt_sqlite_reset(ppStmt);
    while (zt_sqlite_step(ppStmt) == SQLITE_ROW)
    {
        iRows++;
    }
    zt_sqlite_reset(ppStmt);

    return iRows;
}

int zt_sqlite_identity(sqlite3 *db, const char *p_caTable)
{
    int  iRet;
    char caSql[128]={0};
    sqlite3_stmt *ppStmt=NULL;

    memset(caSql, 0, sizeof(caSql));
    sprintf(caSql, "select max(last_insert_rowid()) from %s ", p_caTable);

    iRet = sqlite3_prepare_v2(db, caSql, -1, &ppStmt, NULL);
    if( iRet != SQLITE_OK )
    {
        printf("======ERROR the sql[ %s ] is error!======\n", caSql);
        if( blexitflag ) exit(0);
        iRet = -1;
    }
    else
    {
        zt_sqlite_step(ppStmt);
        iRet = sqlite3_column_int(ppStmt, 0);
    }
    zt_sqlite_finalize(ppStmt);

    return iRet;
}
