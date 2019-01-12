package demo.org.ichanging.fragment;

import android.app.Fragment;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class BookDetailFragment extends Fragment {

    public static final String ITEM_ID = "item_id";
    BookContent.Book book;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        if(getArguments().containsKey(ITEM_ID))
        {
            book = BookContent.Item_Map.get(getArguments().getInt(ITEM_ID));
        }
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_book_detail,container,false);
        if(book != null)
        {
            ((TextView) rootView.findViewById(R.id.book_title)).setText(book.title);
            ((TextView) rootView.findViewById(R.id.book_desc)).setText(book.desc);
        }

        return rootView;
    }
}
