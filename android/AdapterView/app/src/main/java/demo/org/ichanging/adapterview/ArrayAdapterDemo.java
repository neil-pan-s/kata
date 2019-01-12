package demo.org.ichanging.adapterview;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListAdapter;
import android.widget.ListView;

public class ArrayAdapterDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_array_adapter);

        ListView list1 = (ListView) findViewById(R.id.listView1);
        String[] arr1 = {"book1","book2","book3","book4"};
        ArrayAdapter<String> listAdapter1 = new ArrayAdapter<String>(this,R.layout.array_item,arr1);
        list1.setAdapter((ListAdapter) listAdapter1);


        ListView list2 = (ListView) findViewById(R.id.listView2);
        String[] arr2 = {"book5","book6","book7","book8"};
        ArrayAdapter<String> listAdapter2 = new ArrayAdapter<String>(this,R.layout.array_item,arr2);
        list2.setAdapter((ListAdapter) listAdapter2);
    }
}

