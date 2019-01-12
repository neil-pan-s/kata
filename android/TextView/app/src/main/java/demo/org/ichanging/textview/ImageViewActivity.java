package demo.org.ichanging.textview;

import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;

public class ImageViewActivity extends AppCompatActivity {

    int[] images = new int[]
    {
            R.drawable.xgmm_btn,
            R.drawable.yhkcz_btn,
            R.drawable.xgmm_btn,
            R.drawable.yhyw_btn,
            R.drawable.zjqc_btn,
    };

    int curImgIndex = 2;
    private int alpha = 255;

    private static final String ACTIVITY_TAG="ScreenInfo";

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image_view);

        final Button plus = (Button) findViewById(R.id.btn_plus);
        final Button minus = (Button) findViewById(R.id.btn_minus);
        final Button next = (Button) findViewById(R.id.btn_next);

        final ImageView image1 = (ImageView) findViewById(R.id.imageView);
        final ImageView image2 = (ImageView) findViewById(R.id.imageView2);

        next.setOnClickListener(new OnClickListener()
        {
            @Override
            public void onClick(View v) {
                image1.setImageResource( images[++curImgIndex % images.length]);
            }
        });

        View.OnClickListener listener = new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                if( v == plus)
                {
                    alpha += 20;
                }
                if( v == minus)
                {
                    alpha -= 20;
                }
                if(alpha >= 255)
                {
                    alpha = 255;
                }
                if(alpha <= 0)
                {
                    alpha = 0;
                }

                image1.setImageAlpha(alpha);
            }

        };

        plus.setOnClickListener(listener);
        minus.setOnClickListener(listener);

        image1.setOnTouchListener(new View.OnTouchListener()
        {
            @Override
            public boolean onTouch(View view,MotionEvent event)
            {
                BitmapDrawable bitmapDrawable = (BitmapDrawable) image1.getDrawable();
                Bitmap bitmap = bitmapDrawable.getBitmap();
                double scale = 1.0 * bitmap.getHeight() / image1.getHeight();

                int iOffset = 40;

                int x = (int) (event.getX() * scale);
                int y = (int) (event.getY() * scale);

                if(x + iOffset > bitmap.getWidth())
                {
                    x = bitmap.getWidth() - iOffset;
                }

                if(y + iOffset> bitmap.getHeight())
                {
                    y = bitmap.getHeight() - iOffset;
                }

                if(x <= 0)
                {
                    x = bitmap.getWidth();
                }

                if(y <= 0)
                {
                    y = bitmap.getHeight();
                }

                Log.i(ACTIVITY_TAG, "bitmap width = " + x + "height " + y);

                image2.setImageBitmap(Bitmap.createBitmap(bitmap, x, y, iOffset,iOffset));
                image2.setImageAlpha(alpha);
                return false;
            }
        });
    }
}
