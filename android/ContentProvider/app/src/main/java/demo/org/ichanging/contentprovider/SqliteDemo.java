package demo.org.ichanging.contentprovider;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.CursorAdapter;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;
import android.widget.Toast;

import java.io.File;

public class SqliteDemo extends AppCompatActivity {

    SqliteHelper sqliteHelper;
    ListView listView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sqlite_demo);

        Log.i("SqliteDemo", "Path : " + this.getFilesDir().toString());

        //SqliteHelper.deleteDatabase(this);

        sqliteHelper = SqliteHelper.getInstance(this, 1);

        listView  = (ListView) findViewById(R.id.listView);
    }

    public void queryRecord(View v)
    {
        StringBuilder stringBuilder = new StringBuilder();

        Cursor cursor = sqliteHelper.getReadableDatabase().rawQuery("select * from news", null);

        if(cursor.getCount() <= 0)
        {
            Toast.makeText(this,"Empty DB",Toast.LENGTH_SHORT).show();
            return;
        }

        while(cursor.moveToNext())
        {
            int id = cursor.getInt(cursor.getColumnIndex("_id"));
            String title = cursor.getString(cursor.getColumnIndex("news_title"));
            String content = cursor.getString(cursor.getColumnIndex("news_content"));

            String buffer = "\nRecord Data:" +
                    " _id = " + id +
                    " news_title = " + title +
                    " news_content = " + content;

            stringBuilder.append(buffer);

            Log.i("SqliteDemo", buffer );
        }

        Toast.makeText(this,stringBuilder.toString(),Toast.LENGTH_SHORT).show();

        cursor.moveToFirst();

        //SimpleCursorAdapter只识别_id作为主键 -_-!!
        SimpleCursorAdapter adapter = new SimpleCursorAdapter(SqliteDemo.this,R.layout.record,cursor,
                new String[] {"news_title","news_content"},
                new int[] {R.id.news_title,R.id.news_content},
                CursorAdapter.FLAG_REGISTER_CONTENT_OBSERVER
        );

        listView.setAdapter(adapter);

    }

    public void insertRecord(View v)
    {
        sqliteHelper.getReadableDatabase().execSQL("insert into news (_id,news_title,news_content) values(null,?,?)", new String[]{"hi", "hello world"});
    }

    public void updateRecord(View v)
    {
        sqliteHelper.getReadableDatabase().execSQL("update news set news_content='hello dog' where news_title='hi'");
    }

    public void deleteRecord(View v)
    {
        sqliteHelper.getReadableDatabase().execSQL("delete from news where news_title='hi'");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        if(sqliteHelper != null)
        {
            sqliteHelper.close();
        }
    }
}
