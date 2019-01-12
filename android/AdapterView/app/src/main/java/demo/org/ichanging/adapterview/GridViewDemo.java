package demo.org.ichanging.adapterview;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.SimpleAdapter;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class GridViewDemo extends AppCompatActivity {

    GridView grid;
    ImageView imageView;
    int[] imagesIds = new int[]
            {
                    R.drawable.photo_female__01,
                    R.drawable.photo_female__02,
                    R.drawable.photo_female__03,
                    R.drawable.photo_female__04,
                    R.drawable.photo_female__05,
                    R.drawable.photo_female__06,
                    R.drawable.photo_female__07,
                    R.drawable.photo_female__08,
                    R.drawable.photo_female__09,
                    R.drawable.photo_female__10,
                    R.drawable.photo_female__11,
                    R.drawable.photo_female__12,
            };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_grid_view_demo);

        List<Map<String,Object>> listItems = new ArrayList<Map<String,Object>>();
        for(int i = 0; i < imagesIds.length;i++)
        {
            Map<String,Object> listItem = new HashMap<String,Object>();
            listItem.put("image",imagesIds[i]);
            listItems.add(listItem);
        }

        imageView = (ImageView) findViewById(R.id.imageView_gridView);
        SimpleAdapter simpleAdapter = new SimpleAdapter(this,listItems,R.layout.grid_cell,
                new String[] {"image"},new int[]{R.id.pic});

        grid = (GridView) findViewById(R.id.gridView);
        grid.setAdapter(simpleAdapter);

        grid.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                imageView.setImageResource(imagesIds[position]);
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        grid.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                imageView.setImageResource(imagesIds[position]);
            }
        });
    }
}
