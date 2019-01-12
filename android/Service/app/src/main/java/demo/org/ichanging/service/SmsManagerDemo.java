package demo.org.ichanging.service;

import android.app.PendingIntent;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.view.View;

public class SmsManagerDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sms_manager_demo);

        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                PendingIntent pendingIntent = PendingIntent.getActivity(SmsManagerDemo.this, 0, new Intent(), 0);

                SmsManager smsManager = SmsManager.getDefault();
                smsManager.sendTextMessage("18079336668", null, "hello boss", pendingIntent, null);
            }
        });
    }
}
