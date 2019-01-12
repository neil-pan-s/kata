package demo.org.ichanging.resource;

import android.animation.AnimatorInflater;
import android.animation.ArgbEvaluator;
import android.animation.ObjectAnimator;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.ImageView;

public class StateListDrawableDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_state_list_drawable_demo);

        //适用于单元素修改 eg. 同时修改字体大小和背景需使用代码辅助


        final ImageView img = (ImageView) findViewById(R.id.imageView);
        final Animation img_anim = AnimationUtils.loadAnimation(this,R.anim.img_anim);

        //使动画保持在播放的最后一帧
        //img_anim.setFillAfter(true);

        Button btn = (Button) findViewById(R.id.button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                img.startAnimation(img_anim);
            }
        });


        ObjectAnimator colorAnim = (ObjectAnimator) AnimatorInflater.loadAnimator(
                StateListDrawableDemo.this,R.animator.color_anim);
        colorAnim.setEvaluator(new ArgbEvaluator());
        colorAnim.setTarget((Button) findViewById(R.id.button2));
        colorAnim.start();

    }





}
