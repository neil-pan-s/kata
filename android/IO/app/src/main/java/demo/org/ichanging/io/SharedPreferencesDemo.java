package demo.org.ichanging.io;

import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.Date;

public class SharedPreferencesDemo extends AppCompatActivity {

    SharedPreferences preferences;
    SharedPreferences.Editor preferences_editor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_shared_preferences);


        preferences = getSharedPreferences("ichanging",MODE_PRIVATE);
        preferences_editor = preferences.edit();

        findViewById(R.id.rbutton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String time = preferences.getString("time","1970-01-01");
                int rand = preferences.getInt("rand",0);

                Toast.makeText(SharedPreferencesDemo.this,"Time: " + time + "Rand: " + rand,Toast.LENGTH_LONG).show();
            }
        });

        findViewById(R.id.wbutton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy:MM:dd-hh:mm:ss");
                preferences_editor.putString("time",simpleDateFormat.format(new Date()));
                preferences_editor.putInt("rand",(int) (Math.random()*100));
                preferences_editor.commit();
            }
        });

    }
}
