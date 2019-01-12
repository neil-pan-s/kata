package demo.org.ichanging.adapterview;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

public class BaseAdapterDemo extends AppCompatActivity {

    ListView baseList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_base_adapter_demo);

        baseList = (ListView) findViewById(R.id.listView_base);
        BaseAdapter adapter = new BaseAdapter() {
            @Override
            public int getCount() {
                return 40;
            }

            @Override
            public Object getItem(int position) {
                return null;
            }

            @Override
            public long getItemId(int position) {
                return position;
            }

            @Override
            public View getView(int position, View convertView, ViewGroup parent) {
                LinearLayout lineLayout = new LinearLayout(BaseAdapterDemo.this);
                lineLayout.setOrientation(0);
                ImageView image = new ImageView(BaseAdapterDemo.this);
                image.setImageResource(R.drawable.fengo);
                TextView text = new TextView(BaseAdapterDemo.this);
                text.setText("Number " + (position+1) +" Item");
                text.setTextSize(20);
                text.setTextColor(Color.RED);
                lineLayout.addView(image);
                lineLayout.addView(text);

                return lineLayout;
            }
        };

        baseList.setAdapter(adapter);
    }
}
