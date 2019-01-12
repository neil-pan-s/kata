package demo.org.ichanging.fragment;

import android.app.ExpandableListActivity;
import android.app.LauncherActivity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;

public class LauncherDemo extends LauncherActivity {

    String[] names = {"设置程序参数","查看星际兵种"};

    Class<?>[] classArr = {PerferenceActivityDemo.class, ExpandableListActivityDemo.class};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,android.R.layout.simple_list_item_1,names);
        setListAdapter(adapter);
    }

    @Override
    protected Intent intentForPosition(int position) {
        return new Intent(LauncherDemo.this,classArr[position]);
    }
}
