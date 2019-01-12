package demo.org.ichanging.adapterview;

import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.SimpleAdapter;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class SimpleAdapterDemo extends Activity {

    private String[] names = {"二哥","二姐","二妹","二姑"};
    private String[] descs =
            {
                    "因为二，所以叫二哥!",
                    "因为二，所以叫二姐!",
                    "因为二，所以叫二妹!",
                    "因为二，所以叫二姑!",
            };
    private int[] pics =
            {
                    R.drawable.fengo,
                    R.drawable.fengo,
                    R.drawable.fengo,
                    R.drawable.fengo,
            };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_simple_adapter_demo);

        List<Map<String,Object>> listItems = new ArrayList<Map<String,Object>>();

        for(int  i = 0; i < names.length; i++)
        {
            Map<String,Object> listItem = new HashMap<String,Object>();
            listItem.put("pic",pics[i]);
            listItem.put("name",names[i]);
            listItem.put("desc",descs[i]);
            listItems.add(listItem);
        }

        SimpleAdapter simpleAdapter = new SimpleAdapter(this,listItems,R.layout.simple_item,
                new String[] { "name","pic","desc"},
                new int[] {R.id.name,R.id.pic,R.id.desc}
                );
        ListView list = (ListView) findViewById(R.id.listView);
        list.setAdapter(simpleAdapter);

        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                System.out.println(names[position] + "OnClick ");
            }
        });

        list.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                System.out.println(names[position] + "on clicked");

            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

    }
}