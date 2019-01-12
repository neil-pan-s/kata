package demo.org.ichanging.fragment;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class LifeActivity extends AppCompatActivity {

    Button finishBtn,startBtn;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_life);

        finishBtn = (Button) findViewById(R.id.finishBtn);
        startBtn = (Button) findViewById(R.id.startBtn);

        finishBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LifeActivity.this.finish();
            }
        });


        startBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(LifeActivity.this, BookDemo.class);
                startActivity(intent);
            }
        });

    }
}
