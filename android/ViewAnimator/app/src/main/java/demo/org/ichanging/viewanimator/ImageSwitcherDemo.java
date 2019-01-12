package demo.org.ichanging.viewanimator;

import android.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.ImageSwitcher;
import android.widget.ImageView;
import android.widget.SimpleAdapter;
import android.widget.ViewSwitcher;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ImageSwitcherDemo extends AppCompatActivity {

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
    ImageSwitcher switcher;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image_switcher_demo);

        List<Map<String,Object>> listItems = new ArrayList<Map<String,Object>>();
        for(int i = 0;i < imagesIds.length;i++)
        {
            Map<String,Object> listItem = new HashMap<String,Object>();
            listItem.put("image",imagesIds[i]);
            listItems.add(listItem);

        }

        switcher = (ImageSwitcher) findViewById(R.id.imageSwitcher);
        switcher.setFactory(new ViewSwitcher.ViewFactory() {
            @Override
            public View makeView() {

                ImageView imageView = new ImageView(ImageSwitcherDemo.this);
                imageView.setScaleType(ImageView.ScaleType.FIT_CENTER);
                imageView.setLayoutParams(new ImageSwitcher.LayoutParams(
                        ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT ));
                return imageView;
            }
        });

        SimpleAdapter simpleAdater = new SimpleAdapter(this,listItems,R.layout.grid_cell,new String[]{"image"},new int[]{R.id.pic});

        GridView gridView = (GridView) findViewById(R.id.grid01);
        gridView.setAdapter(simpleAdater);
        gridView.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                switcher.setImageResource(imagesIds[position]);
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        gridView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                switcher.setImageResource(imagesIds[position]);
            }
        });

    }


}
