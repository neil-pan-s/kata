package demo.org.ichanging.otherswidget;

import android.app.TabActivity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TabHost;

public class TabHostDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tab_host_demo);


        TabHost tabHost = (TabHost) findViewById(R.id.tabHost);

        //Important!
        tabHost.setup();

        TabHost.TabSpec tab1 = tabHost.newTabSpec("tab1").setIndicator("已接电话").setContent(R.id.linearLayout);
		//将一个Activity 内容设置为 Tab页内容 
 		//TabHost.TabSpec tab1 = tabHost.newTabSpec("tab1").setIndicator("已接电话").setContent(new Intent(this,xxxx.class));

        tabHost.addTab(tab1);

        TabHost.TabSpec tab2 = tabHost.newTabSpec("tab2").setIndicator("未接电话").setContent(R.id.linearLayout2);
        tabHost.addTab(tab2);

        TabHost.TabSpec tab3 = tabHost.newTabSpec("tab3").setIndicator("呼出电话").setContent(R.id.linearLayout3);
        tabHost.addTab(tab3);

    }
}
