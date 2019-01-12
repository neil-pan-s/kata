package demo.org.ichanging.io;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;
import android.widget.Toast;
import android.widget.ViewFlipper;

public class GestureDemo extends AppCompatActivity implements GestureDetector.OnGestureListener {

    Toast toast;
    ViewFlipper flipper;
    GestureDetector detector;

    Animation[] animations = new Animation[4];

    final int MIN_FLIP_DISTANCE = 50;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gesture_demo);

        detector = new GestureDetector(this,this);

        flipper  = (ViewFlipper) findViewById(R.id.viewFlipper);
        flipper.addView(addImageView(R.drawable.photo_female__01));
        flipper.addView(addImageView(R.drawable.photo_female__02));
        flipper.addView(addImageView(R.drawable.photo_female__03));
        flipper.addView(addImageView(R.drawable.photo_female__04));
        flipper.addView(addImageView(R.drawable.photo_female__05));

        animations[0] = AnimationUtils.loadAnimation(this,R.anim.left_in);
        animations[1] = AnimationUtils.loadAnimation(this,R.anim.left_out);
        animations[2] = AnimationUtils.loadAnimation(this,R.anim.right_in);
        animations[3] = AnimationUtils.loadAnimation(this,R.anim.right_in);

        toast = Toast.makeText(this,"",Toast.LENGTH_SHORT);
    }

    private View addImageView(int resId)
    {
        ImageView imageView = new ImageView(this);
        imageView.setImageResource(resId);
        imageView.setScaleType(ImageView.ScaleType.CENTER);
        return imageView;
    }

    //Important !!
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return detector.onTouchEvent(event);
    }

    //滑动的最后触发（即手指Up抬起时触发）
    @Override
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
        toast.setText("Fling");
        toast.show();

        if(e1.getX() - e2.getX() > MIN_FLIP_DISTANCE)
        {
            flipper.setInAnimation(animations[0]);
            flipper.setOutAnimation(animations[1]);
            flipper.showPrevious();
            return true;
        }

        if(e2.getX() - e1.getX() > MIN_FLIP_DISTANCE)
        {
            flipper.setInAnimation(animations[2]);
            flipper.setOutAnimation(animations[3]);
            flipper.showNext();
            return true;
        }

        return false;
    }

    //拖动或滑动的过程中不断触发
    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
        toast.setText("Scrolling");
        toast.show();
        return false;
    }

    @Override
    public boolean onDown(MotionEvent e) {
        toast.setText("Touch Down");
        toast.show();

        return false;
    }

    @Override
    public void onShowPress(MotionEvent e) {
        toast.setText("Touching");
        toast.show();
    }

    @Override
    public boolean onSingleTapUp(MotionEvent e) {
        toast.setText("Single Tap Up");
        toast.show();
        return false;
    }

    @Override
    public void onLongPress(MotionEvent e) {
        toast.setText("Long Press");
        toast.show();
    }

}
