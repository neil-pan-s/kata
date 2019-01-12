package demo.org.ichanging.myapplication;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if(MyApplication.getContext() != null)
        {
            Toast.makeText(this,"Get Context Succ\n" + MyApplication.getContext().toString(),Toast.LENGTH_LONG).show();
        }else{
            Toast.makeText(this,"Get Context Null",Toast.LENGTH_LONG).show();
        }

        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                findViewById(R.id.textView).setVisibility(View.INVISIBLE);
            }
        });

        findViewById(R.id.launch_next_activity_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent(MainActivity.this,EmptyActivity.class);
                intent.putExtra("play_load_key","yes");
                startActivity(intent);

            }
        });

    }



}
