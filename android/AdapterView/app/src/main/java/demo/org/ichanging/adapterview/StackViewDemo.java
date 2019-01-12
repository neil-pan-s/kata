package demo.org.ichanging.adapterview;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.SimpleAdapter;
import android.widget.StackView;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class StackViewDemo extends AppCompatActivity {

    StackView stackView;

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
        setContentView(R.layout.activity_stack_view_demo);

        stackView = (StackView) findViewById(R.id.stackView);
        List<Map<String,Object>> listItems = new ArrayList<Map<String,Object>>();

        for(int i = 0;i < imagesIds.length;i++)
        {
            Map<String,Object> listItem = new HashMap<String,Object>();
            listItem.put("image",imagesIds[i]);
            listItems.add(listItem);
        }

        SimpleAdapter simpleAdapter = new SimpleAdapter(this,listItems,R.layout.stack_cell,new String[]{"image"},new int[]{R.id.pic});
        stackView.setAdapter(simpleAdapter);

    }

    public  void stack_prev(View source)
    {
        stackView.showPrevious();

    }


    public  void stack_next(View source)
    {

        stackView.showNext();

    }


}
