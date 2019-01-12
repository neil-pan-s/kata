package demo.org.ichanging.service;

import android.app.Service;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Binder;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

public class ServiceDemo extends AppCompatActivity {

    BindService.MyBinder binder;

    private ServiceConnection connection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            System.out.println("Service Connected");

            binder = (BindService.MyBinder) service;
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            System.out.println("Service Disconnected");
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_service_demo);

        final Intent intent = new Intent(this,BindService.class);
        findViewById(R.id.bindBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bindService(intent,connection,Service.BIND_AUTO_CREATE);
            }
        });

        findViewById(R.id.unbindBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                unbindService(connection);
            }
        });

        findViewById(R.id.statusBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(ServiceDemo.this,"Service  Count : " + binder.getCount(),Toast.LENGTH_SHORT).show();
            }
        });

        final Intent myintent = new Intent(this,MyService.class);

        findViewById(R.id.startBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startService(myintent);
            }
        });

        findViewById(R.id.stopBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                stopService(myintent);
            }
        });


        final Intent myintentservice = new Intent(this,MyIntentService.class);

        findViewById(R.id.xBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startService(myintentservice);
            }
        });

    }
}
