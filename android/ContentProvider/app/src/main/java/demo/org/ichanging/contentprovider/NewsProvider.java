package demo.org.ichanging.contentprovider;

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

/**
 * Created by ChangingP on 2016/4/3.
 */
public class NewsProvider extends ContentProvider {

    private static UriMatcher matcher = new UriMatcher(UriMatcher.NO_MATCH);
    private static final int NEWS = 1;
    private static final int NEWSITEM = 2;
    private SqliteHelper dbHelper;

    static
    {
        //注册 绑定 URI CODE
        matcher.addURI(News.AUTHORITY,"news",NEWS);
        matcher.addURI(News.AUTHORITY,"newsitem/#",NEWSITEM);
    }

    @Override
    public boolean onCreate() {

        dbHelper = SqliteHelper.getInstance(this.getContext(),1);

        return false;
    }

    @Nullable
    @Override
    public Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs, String sortOrder) {
        SQLiteDatabase db = dbHelper.getReadableDatabase();
        switch (matcher.match(uri))
        {
            case NEWS:
                return db.query("news",projection,selection,selectionArgs,null,null,sortOrder);
            case NEWSITEM:
                long id = ContentUris.parseId(uri);
                String whereClause = News.NewsItem._ID + "=" + id;
                if(selection != null && !(selection.equals("")))
                {
                    whereClause = whereClause + " and " + selection;
                }

                return db.query("news",projection,whereClause,selectionArgs,null,null,sortOrder);
            default:
                throw new IllegalArgumentException("未知Uri: " + uri);
        }
    }

    @Nullable
    @Override
    public String getType(Uri uri) {
        switch (matcher.match(uri))
        {
            case NEWS:
                return "";
            case NEWSITEM:
                return "";
            default:
                throw new IllegalArgumentException("未知Uri: " + uri);
        }
    }

    @Nullable
    @Override
    public Uri insert(Uri uri, ContentValues values)
    {
        SQLiteDatabase db = dbHelper.getReadableDatabase();
        switch (matcher.match(uri))
        {
            case NEWS:
                long rowId = db.insert("news", News.NewsItem._ID, values);
                if (rowId > 0) {
                    //通知 ContentResolver
                    Uri newsUri = ContentUris.withAppendedId(uri, rowId);
                    getContext().getContentResolver().notifyChange(newsUri, null);
                    return newsUri;
                }
                break;
            default:
                throw new IllegalArgumentException("未知Uri: " + uri);
        }
        return null;
    }

    @Override
    public int delete(Uri uri, String selection, String[] selectionArgs) {
        int num = 0;
        SQLiteDatabase db = dbHelper.getReadableDatabase();
        switch(matcher.match(uri))
        {
            case NEWS:
                num = db.delete("news", selection, selectionArgs);
                break;
            case NEWSITEM:
                long id = ContentUris.parseId(uri);
                String whereClause = News.NewsItem._ID + "=" + id;
                if(selection != null && !(selection.equals("")))
                {
                    whereClause += " and " + selection;
                }
                num = db.delete("news",whereClause,selectionArgs);
                break;
            default:
                throw new IllegalArgumentException("未知Uri: " + uri);
        }

        getContext().getContentResolver().notifyChange(uri,null);
        return num;
    }

    @Override
    public int update(Uri uri, ContentValues values, String selection, String[] selectionArgs) {
        int num = 0;
        SQLiteDatabase db = dbHelper.getReadableDatabase();
        switch(matcher.match(uri))
        {
            case NEWS:
                num = db.update("news", values, selection, selectionArgs);
                break;
            case NEWSITEM:
                long id = ContentUris.parseId(uri);
                String whereClause = News.NewsItem._ID + "=" + id;
                if(selection != null && !(selection.equals("")))
                {
                    whereClause += " and " + selection;
                }
                num = db.update("news",values,whereClause,selectionArgs);
                break;
            default:
                throw new IllegalArgumentException("未知Uri: " + uri);
        }

        getContext().getContentResolver().notifyChange(uri,null);
        return num;
    }



}
