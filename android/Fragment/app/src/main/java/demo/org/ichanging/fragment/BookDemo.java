package demo.org.ichanging.fragment;

import android.app.Activity;
import android.app.FragmentTransaction;
import android.content.Intent;
import android.os.Bundle;

public class BookDemo extends Activity implements BookListFragment.Callbacks {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_book_demo);

        // If we are in two-pane layout mode
        if (getResources().getBoolean(R.bool.pane_flag))
        {
            ((BookListFragment) getFragmentManager().findFragmentById(R.id.book_list))
                    .setActivateOnItemClick(true);
        }

    }

    @Override
    public void onItemSelected(Integer id) {

        // If we are in two-pane layout mode
        if (getResources().getBoolean(R.bool.pane_flag)) {

            //单列则更新fragment 显示
            Bundle arguments = new Bundle();
            arguments.putInt(BookDetailFragment.ITEM_ID, id);
            BookDetailFragment fragment = new BookDetailFragment();
            fragment.setArguments(arguments);

            FragmentTransaction transaction = getFragmentManager().beginTransaction();
            //add the fragment to back stack , press back can return last fragment
            transaction.addToBackStack(null);
            transaction.replace(R.id.book_detail_container, fragment).commit();

        }else{

            //单列模式 直接跳转新界面显示明细
            Intent intent = new Intent(this,BookDetailActivity.class);
            intent.putExtra(BookDetailFragment.ITEM_ID,id);
            startActivity(intent);
        }
    }
}
