package demo.org.ichanging.contentprovider;

import android.net.Uri;
import android.provider.BaseColumns;

/**
 * Created by ChangingP on 2016/4/3.
 */
public final  class News {

    public static final String AUTHORITY = "demo.org.ichanging.contentprovider.newsprovider";

    public static final class NewsItem implements BaseColumns
    {
        public final static String _ID = "_id";
        public final static String TITLE = "news_title";
        public final static String CONTENT = "news_content";

        public final static Uri NEWS_CONTENT_URI = Uri.parse(
                "content://" + AUTHORITY + "/news"
        );

        public final static Uri NEWSITEM_CONTENT_URI = Uri.parse(
                "content://" + AUTHORITY + "/newsitem"
        );

    }


}
