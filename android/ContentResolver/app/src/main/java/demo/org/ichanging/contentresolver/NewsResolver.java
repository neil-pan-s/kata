package demo.org.ichanging.contentresolver;

import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.ContentValues;
import android.database.Cursor;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

public class NewsResolver extends AppCompatActivity {

    ContentResolver contentResolver;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_news_solver);

        contentResolver = getContentResolver();

        if(!uriVerify(News.NewsItem.NEWS_CONTENT_URI))
        {
            Toast.makeText(NewsResolver.this,"No Match App Uri",Toast.LENGTH_SHORT).show();
            return;
        }

        findViewById(R.id.insertBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ContentValues values = new ContentValues();
                values.put(News.NewsItem.TITLE,"uri_hi");
                values.put(News.NewsItem.CONTENT, "uri_hello_world");

                Uri uri = contentResolver.insert(News.NewsItem.NEWS_CONTENT_URI, values);

                //根据返回的Uri 判断是否插入成功
                long id = ContentUris.parseId(uri);
                if(id > 0) {
                    Toast.makeText(NewsResolver.this,"Insert News Suc,Row Id = " + id ,Toast.LENGTH_SHORT).show();
                }else{
                    Toast.makeText(NewsResolver.this,"Insert News Fail",Toast.LENGTH_SHORT).show();
                }

            }
        });


        findViewById(R.id.updateBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ContentValues values = new ContentValues();
                values.put(News.NewsItem.TITLE,"hi");
                values.put(News.NewsItem.CONTENT, "uri_hello_world");

                //更新 news_title="uri_hi"
                int num = contentResolver.update(
                        News.NewsItem.NEWS_CONTENT_URI,
                        values,
                        News.NewsItem.TITLE + "=?", new String[]{"uri_hi"});

                if(num > 0) {
                    Toast.makeText(NewsResolver.this,"Update News Suc,Row Affect Num = " + num ,Toast.LENGTH_SHORT).show();
                }else{
                    Toast.makeText(NewsResolver.this,"Update News Fail",Toast.LENGTH_SHORT).show();
                }

            }
        });

        findViewById(R.id.updateIDBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ContentValues values = new ContentValues();
                values.put(News.NewsItem.TITLE,"hi");
                values.put(News.NewsItem.CONTENT, "uri_hello_world");

                //此_id 需要已在数据库中存在
                int id  = 10;

                //修改uri 传递需要修改的 news _id
                Uri uri = ContentUris.withAppendedId( News.NewsItem.NEWSITEM_CONTENT_URI,id);

                //更新 _id = x
                int num = contentResolver.update(
                        uri,
                        values,
                        null,null);

                if(num > 0) {
                    Toast.makeText(NewsResolver.this,"Update ID = " + id + " News Suc,Row Affect Num = " + num ,Toast.LENGTH_SHORT).show();
                }else{
                    Toast.makeText(NewsResolver.this,"Update ID = " + id + " News Fail",Toast.LENGTH_SHORT).show();
                }

            }
        });


        findViewById(R.id.deleteBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                //删除所有 news_title="uri_hi"
                int num = contentResolver.delete(
                        News.NewsItem.NEWS_CONTENT_URI,
                        News.NewsItem.TITLE + "=?", new String[]{"uri_hi"});

                if(num > 0) {
                    Toast.makeText(NewsResolver.this,"Delete News Suc,Row Affect Num = " + num ,Toast.LENGTH_SHORT).show();
                }else{
                    Toast.makeText(NewsResolver.this,"Delete News Fail",Toast.LENGTH_SHORT).show();
                }

            }
        });


        findViewById(R.id.queryBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                StringBuilder stringBuilder = new StringBuilder();

                Cursor cursor = contentResolver.query(
                        News.NewsItem.NEWS_CONTENT_URI, new String[] {"*"},null,null,null);

                if(cursor.getCount() <= 0)
                {
                    Toast.makeText(NewsResolver.this,"Query No News",Toast.LENGTH_SHORT).show();
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

                    Log.i("Query News:", buffer );
                }

                Toast.makeText(NewsResolver.this,stringBuilder.toString(),Toast.LENGTH_SHORT).show();
            }
        });

    }

    private boolean uriVerify(Uri _uri)
    {
        //判断指定的ContentProvider是否存在
        Cursor cursor = getContentResolver().query(_uri, new String[]{"_id"},
                null, null, null);
        if (cursor == null) {
            Log.d("uriVerify", "No App Uri:" + _uri);
            return false;
        }

        return true;
    }

}
