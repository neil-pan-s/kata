package demo.org.ichanging.intent;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class ActivityLifeDemo extends AppCompatActivity {

    final static String TAG = "LOG_TAG";

    Button finishBtn,startBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_activity_life_demo);

        Log.d(TAG, "========= onCreate =======");

        finishBtn = (Button) findViewById(R.id.finishBtn);
        startBtn = (Button) findViewById(R.id.startBtn);

        finishBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ActivityLifeDemo.this.finish();
            }
        });


        startBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ActivityLifeDemo.this,EmptyDemo.class);
                startActivity(intent);
            }
        });

    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.d(TAG, "========= onStart =======");
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        Log.d(TAG, "========= onRestart =======");

    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d(TAG, "========= onResume =======");
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.d(TAG, "========= onPause =======");
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.d(TAG, "========= onStop =======");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d(TAG, "========= onDestroy =======");

    }
}
