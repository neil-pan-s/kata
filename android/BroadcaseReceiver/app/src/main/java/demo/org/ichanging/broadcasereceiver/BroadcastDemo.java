package demo.org.ichanging.broadcasereceiver;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class BroadcastDemo extends AppCompatActivity {

    final String ACTION = "demo.org.ichanging.action.BROADCAST_TEST";
    final String ACTION_ORDER = "demo.org.ichanging.action.BROADCAST_ORDER_TEST";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_broadcast_demo);

        findViewById(R.id.sendBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent();
                intent.setAction(ACTION);
                intent.putExtra("msg", "hello world");

                sendBroadcast(intent);
            }
        });

        findViewById(R.id.xBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent();
                intent.setAction(ACTION_ORDER);
                intent.putExtra("msg", "hello world");

                sendOrderedBroadcast(intent, null);
            }
        });
    }
}
