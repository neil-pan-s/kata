package demo.org.ichanging.service;

import android.app.Service;
import android.os.Vibrator;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;

public class VibratorDemo extends AppCompatActivity {

    Vibrator  vibrator;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_vibrator_demo);

        vibrator =  (Vibrator) getSystemService(Service.VIBRATOR_SERVICE);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {

        vibrator.vibrate(1000);

        return super.onTouchEvent(event);
    }
}
