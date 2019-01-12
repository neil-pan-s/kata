package demo.org.ichanging.adapterview;

import android.app.ListActivity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListAdapter;
import android.widget.ListView;

public class ListActivityDemo extends ListActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        String[] arr1 = {"book1","book2","book3","book4"};

        ArrayAdapter<String> listAdapter1 = new ArrayAdapter<String>(this,android.R.layout.simple_list_item_1,arr1);
        //ArrayAdapter<String> listAdapter1 = new ArrayAdapter<String>(this,android.R.layout.simple_list_item_multiple_choice,arr1);

        setListAdapter(listAdapter1);

    }
}
