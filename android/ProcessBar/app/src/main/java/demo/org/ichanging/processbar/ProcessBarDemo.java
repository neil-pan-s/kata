package demo.org.ichanging.processbar;

import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ProgressBar;

public class ProcessBarDemo extends AppCompatActivity {

    ProgressBar bar_circle,bar;
    int status = 0;

    Handler mHandler= new Handler()
    {
        @Override
        public void handleMessage(Message msg)
        {
            if(msg.what == 0x111)
            {
                bar.setProgress(status);
                bar_circle.setProgress(status);
            }
        }

    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_process_bar_demo);

        bar = (ProgressBar) findViewById(R.id.progressBar);
        bar_circle = (ProgressBar) findViewById(R.id.progressBar_circle);

        new Thread()
        {
            public void run()
            {
                while(status < 100)
                {
                    status++;

                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    mHandler.sendEmptyMessage(0x111);

                }
            }
        }.start();
    }

}
