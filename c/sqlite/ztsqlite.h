#ifndef __ZTSQLITE_H__
#define __ZTSQLITE_H__

#define SQLITE_OK           0   /* Successful result */
#define SQLITE_ROW         100  /* sqlite3_step() has another row ready */

typedef struct sqlite3_stmt sqlite3_stmt;
typedef struct sqlite3 sqlite3;

extern void   zt_sqlite_column_text(sqlite3_stmt *ppStmt, int p_iCol, char *p_caValue, int p_iSize);
extern void   zt_sqlite_column_int(sqlite3_stmt *ppStmt, int iCol, int *p_iValue);
extern int    zt_sqlite_column_int(sqlite3_stmt *ppStmt, int iCol);
extern void   zt_sqlite_column_int(sqlite3_stmt *ppStmt, int iCol, double *p_fValue);
extern double zt_sqlite_column_float(sqlite3_stmt *ppStmt, int iCol);

extern int    zt_sqlite_prepare_v2(sqlite3 *db, const char *zSql, int nByte, sqlite3_stmt **ppStmt, const char **pzTail);
extern int    zt_sqlite_exec(sqlite3 *db, const char *zSql, int (*callback)(void*,int,char**,char**), void *, char **errmsg);

extern void   zt_sqlite_finalize(sqlite3_stmt *ppStmt);
extern int    zt_sqlite_step(sqlite3_stmt *ppStmt);
extern void   zt_sqlite_reset(sqlite3_stmt *ppStmt);
extern int    zt_sqlite_rows(sqlite3_stmt *ppStmt);
extern int    zt_sqlite_identity(sqlite3 *db, const char *p_caTable);

extern int    zt_sqlite_open(const char *p_caPath, sqlite3 **db, bool p_blExitFlag=true);
extern void   zt_sqlite_close(sqlite3 *db);

#endif  //__ZTSQLITE_H__
