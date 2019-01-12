package org.ichanging.demo;

import android.os.Message;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.GridLayout;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import java.util.Timer;
import java.util.TimerTask;
import java.util.logging.LogRecord;
import android.os.Handler;

import org.ichanging.demo.R;

public class MainActivity extends AppCompatActivity {

    private static final String ACTIVITY_TAG="ScreenInfo";

    //For Case 4
//    private int currentColor = 0;
//    final  int[] colors = new int[]{
//            R.color.color1,
//            R.color.color2,
//            R.color.color3,
//            R.color.color4,
//            R.color.color5,
//            R.color.color6
//    };
//    final int[] names = new int[]{
//            R.id.textView2,
//            R.id.textView3,
//            R.id.textView4,
//            R.id.textView5,
//            R.id.textView6,
//            R.id.textView7
//    };
//
//    TextView[] views = new TextView[names.length];
//    Handler handler = new Handler()
//    {
//        @Override
//        public void handleMessage(Message msg)
//        {
//            //Log.i(ACTIVITY_TAG, "Handler - msg : " + msg );
//
//            //消息来源检测
//            if(msg.what == 0x123)
//            {
//
//                //Log.i(ACTIVITY_TAG, "Handler - msg.what : " + msg.what );
//
//                for(int i = 0;i < names.length; i++)
//                {
//                    views[i].setBackgroundResource(colors[(i + currentColor) % names.length]);
//                }
//                currentColor++;
//            }
//            super.handleMessage(msg);
//        }
//    };

    //For Case 6
    GridLayout gridLayout;
    String[] chars = new String[]
    {
        "7","8","9","÷",
        "4","5","6","×",
        "1","2","3","-",
        ".","0","=","+"
    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //Case 1
        //setContentView(R.layout.activity_main);
        //RelativeLayout root = (RelativeLayout) findViewById(R.id.root);

        //Case 2
//        setContentView(R.layout.tablelayout_main);
//        LinearLayout root = (LinearLayout) findViewById(R.id.table_root);

//        //Case 3
//        setContentView(R.layout.linearlayout_main);
//        LinearLayout root = (LinearLayout) findViewById(R.id.linear_main);


        //Case 4
//        setContentView(R.layout.framelayout_main);
//        FrameLayout root = (FrameLayout) findViewById(R.id.frame_main);
//
//        for(int i = 0;i < names.length;i++)
//        {
//            views[i] = (TextView) findViewById(names[i]);
//        }
//
//        new Timer().schedule(new TimerTask()
//        {
//            @Override
//            public void run() {
//                handler.sendEmptyMessage(0x123);
//            }
//        },0,200);

        //case 5
//        setContentView(R.layout.relativelayout_main);
//        RelativeLayout root = (RelativeLayout) findViewById(R.id.relative_main);


        //case 6
        setContentView(R.layout.gridlayout_main);
        gridLayout = (GridLayout) findViewById(R.id.grid_main);
        GridLayout root = (GridLayout) findViewById(R.id.grid_main);
        for(int i = 0;i < chars.length;i++)
        {
            Button btn = new Button(this);
            btn.setText(chars[i]);
            btn.setTextSize(40);
            btn.setPadding(5,35,5,35);
            GridLayout.Spec rowSpec = GridLayout.spec(i/4 + 2);
            GridLayout.Spec colSpec = GridLayout.spec(i%4);
            GridLayout.LayoutParams Params = new GridLayout.LayoutParams(rowSpec,colSpec);

            Params.setGravity(Gravity.FILL);
            gridLayout.addView(btn,Params);
        }


        //获取屏幕信息
        DisplayMetrics dm = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(dm);
        int screenWidth = dm.widthPixels;
        int screenHeight = dm.heightPixels;

        Log.i(ACTIVITY_TAG, "Pixels - screenWidth: " + screenWidth +"screenHeight: " + screenHeight);

        //Case 6 Need commented
//        final DrawView draw = new DrawView(this);
//        draw.setMinimumWidth(500);
//        draw.setMinimumHeight(300);
//        root.addView(draw);

    }


    public void MagicClickHandler(View source)
    {
        TextView tv = (TextView) findViewById(R.id.textView);
        if(tv != null)
        {
            tv.setText("Hello Android-" + new java.util.Date());
        }
    }

}
