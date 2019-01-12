package demo.org.ichanging.otherswidget;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class NotificationDemo extends AppCompatActivity {

    static final int NOTIFICATION_ID = 0x123;
    NotificationManager nm;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_notification_demo);

        nm = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
    }

    public void send(View v)
    {
        Intent intent = new Intent(NotificationDemo.this,ScrollViewDemo.class);
        PendingIntent pi = PendingIntent.getActivity(NotificationDemo.this,0,intent,0);
        Notification notify = new Notification.Builder(this)
                .setAutoCancel(true)
                .setTicker("有新消息")
                .setSmallIcon(android.R.drawable.stat_notify_chat)
                .setContentTitle("你又收到一封情书")
                .setContentText("错误-郑愁予 点击查看")
                .setDefaults(Notification.DEFAULT_SOUND |Notification.DEFAULT_VIBRATE| Notification.DEFAULT_LIGHTS)
                //.setSound(Uri.parse("android.resource://demo.org.ichanging/"+R.raw.msg))
                .setWhen(System.currentTimeMillis())
                .setContentIntent(pi)
                .build();

        nm.notify(NOTIFICATION_ID,notify);
    }

    public  void del(View v)
    {
       nm.cancel(NOTIFICATION_ID);
    }

}
