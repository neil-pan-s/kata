package demo.org.ichanging.adapterview;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterViewFlipper;
import android.widget.BaseAdapter;
import android.widget.ImageView;

public class AdapterViewFlipperDemo extends AppCompatActivity {

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

    private AdapterViewFlipper flipper;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_adapter_view_flipper_demo);

        flipper = (AdapterViewFlipper) findViewById(R.id.adapterViewFlipper);
        BaseAdapter adapter = new BaseAdapter() {
            @Override
            public int getCount() {
                return imagesIds.length;
            }

            @Override
            public Object getItem(int position) {
                return position;
            }

            @Override
            public long getItemId(int position) {
                return position;
            }

            @Override
            public View getView(int position, View convertView, ViewGroup parent) {

                ImageView imageView = new ImageView(AdapterViewFlipperDemo.this);
                imageView.setImageResource(imagesIds[position]);
                imageView.setScaleType(ImageView.ScaleType.FIT_XY);
                imageView.setLayoutParams(
                        new ViewGroup.LayoutParams(
                                ViewGroup.LayoutParams.MATCH_PARENT,ViewGroup.LayoutParams.MATCH_PARENT
                        )
                );
                return imageView;
            }
        };
        flipper.setAdapter(adapter);
    }

    public  void flipper_prev(View source)
    {
        flipper.showPrevious();
        flipper.stopFlipping();
    }

    public  void flipper_next(View source)
    {
        flipper.showNext();
        flipper.stopFlipping();
    }

    public  void flipper_auto(View source)
    {
        flipper.startFlipping();
    }
}
