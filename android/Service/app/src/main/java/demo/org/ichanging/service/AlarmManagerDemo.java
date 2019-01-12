package demo.org.ichanging.service;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class AlarmManagerDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_alarm_manager_demo);

        findViewById(R.id.setBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {


                Intent intent = new Intent(AlarmManagerDemo.this,AlarmDialog.class);
                PendingIntent pendingIntent = PendingIntent.getActivity(
                        AlarmManagerDemo.this, 0, intent, 0);

                Calendar c = Calendar.getInstance();
                c.setTimeInMillis(System.currentTimeMillis());

                //2015-4-4 1:10
                //c.set(2016,4,4,1,10);

                //5s After
                c.add(Calendar.SECOND,5);

                AlarmManager alarmManager = (AlarmManager) getSystemService(ALARM_SERVICE);
                alarmManager.set(AlarmManager.RTC_WAKEUP,c.getTimeInMillis(),pendingIntent);

                //5s repeat
                //alarmManager.setRepeating(AlarmManager.ELAPSED_REALTIME_WAKEUP,0,5000,pendingIntent);

            }
        });



    }
}
