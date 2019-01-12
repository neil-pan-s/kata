#include <stdio.h>
#include <sqlite3.h>


int main()
{
    int iRet=0;
    char *ErrMsg;
    sqlite3 *db=NULL;
    sqlite3_stmt *ppStmt=NULL;

    iRet = sqlite3_open("test.db", &db);
    if(iRet)
    {
      printf("Can't open database: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      return -1;
    }else{
      printf("open database!\n");
    }

    /******************************************************************************
    int sqlite3_exec(
      sqlite3*,                                  // An open database
      const char *sql,                           // SQL to be evaluated
      int (*callback)(void*,int,char**,char**),  // Callback function
      void *,                                    // 1st argument to callback
      char **errmsg                              // Error msg written here
    );
    ********************************************************************************/
    //不使用回调函数
    iRet = sqlite3_exec(db, "insert into qttest(id,userName,userPwd) values(null,\"cat\",\"123456\")", NULL, NULL, &ErrMsg);
    if( iRet !=SQLITE_OK )
    {
      printf("SQL error: %s\n", ErrMsg);
      return -2;
    }else{
      printf("insert ok! \n");
    }

    /******************************************************************************
    int sqlite3_prepare(
      sqlite3 *db,            // Database handle
      const char *zSql,       // SQL statement, UTF-8 encoded
      int nByte,              // Maximum length of zSql in bytes
      sqlite3_stmt **ppStmt,  // OUT: Statement handle
      const char **pzTail     // OUT: Pointer to unused portion of zSql
    );
    ********************************************************************************/
    //数据库取数据,最大长度无效
    iRet = sqlite3_prepare(db,"select id,userName,userPwd from qttest", -1, &ppStmt, NULL);
    if( iRet != SQLITE_OK )
    {
        printf("Select error\n");
        //释放ppStmt
        sqlite3_finalize(ppStmt);
        return -3;
    }else{
        printf("user info:\n");
        while(sqlite3_step(ppStmt) == SQLITE_ROW)
        {
            printf("Id: %s\t", sqlite3_column_text(ppStmt, 0));
            printf("Name: %s\t", sqlite3_column_text(ppStmt, 1));
            printf("Pwd: %s\n", sqlite3_column_text(ppStmt, 2));
        }
        sqlite3_finalize(ppStmt);
    }

    sqlite3_close(db);
    return 0;
}
