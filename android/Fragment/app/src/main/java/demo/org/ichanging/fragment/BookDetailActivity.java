package demo.org.ichanging.fragment;

import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class BookDetailActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_book_detail);

        if(savedInstanceState == null)
        {
            BookDetailFragment fragment = new BookDetailFragment();
            Bundle argments = new Bundle();
            argments.putInt(BookDetailFragment.ITEM_ID,getIntent().getIntExtra(BookDetailFragment.ITEM_ID,0));
            fragment.setArguments(argments);
            getFragmentManager().beginTransaction().add(R.id.book_detail_container,fragment).commit();
        }
    }

}
