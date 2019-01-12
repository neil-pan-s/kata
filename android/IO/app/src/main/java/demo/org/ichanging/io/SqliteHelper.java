package demo.org.ichanging.io;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class SqliteHelper extends SQLiteOpenHelper
{
    //singleton
    private static SqliteHelper mInstance = null;

    public static final String DATABASE_NAME = "test.db";

    //SimpleCursorAdapter只识别_id作为主键 -_-!!
    private static final String NAME_TABLE_CREATE =
            "create table if not exists news(_id integer primary key autoincrement," +
            "news_title varchar(50)," +
            "news_content varchar(255))";

    public SqliteHelper(Context context,int version)
    {

//        super(context,context.getFilesDir().toString() + "/" +DATABASE_NAME,null,version);
        super(context,DATABASE_NAME,null,version);
    }

    //单例模式
    public static synchronized SqliteHelper getInstance(Context context,int version)
    {
        if (mInstance == null)
        {
            mInstance = new SqliteHelper(context,version);
        }
        return mInstance;
    }

    public static boolean deleteDatabase(Context context)
    {
        //return context.deleteDatabase(context.getFilesDir().toString() + "/" + DATABASE_NAME);
        return context.deleteDatabase(DATABASE_NAME);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {

        db.execSQL(NAME_TABLE_CREATE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

    }
}
