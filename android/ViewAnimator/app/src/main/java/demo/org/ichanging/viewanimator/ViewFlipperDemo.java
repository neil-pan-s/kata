package demo.org.ichanging.viewanimator;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ViewFlipper;

public class ViewFlipperDemo extends AppCompatActivity {

    ViewFlipper viewFlipper;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_view_flipper_demo);

        viewFlipper = (ViewFlipper) findViewById(R.id.viewFlipper);
    }

    public  void prev(View V)
    {
        viewFlipper.setInAnimation(this,R.anim.slide_in_right);
        viewFlipper.setOutAnimation(this, R.anim.slide_out_left);

        viewFlipper.showPrevious();
        viewFlipper.stopFlipping();
    }

    public  void next(View V)
    {
        viewFlipper.setInAnimation(this,android.R.anim.slide_in_left);
        viewFlipper.setOutAnimation(this,android.R.anim.slide_out_right);

        viewFlipper.showNext();
        viewFlipper.stopFlipping();
    }

    public  void auto(View V)
    {
        viewFlipper.setInAnimation(this,android.R.anim.slide_in_left);
        viewFlipper.setOutAnimation(this,android.R.anim.slide_out_right);

        viewFlipper.startFlipping();
    }
}
