package demo.org.ichanging.network;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class SocketServerDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_socket_server_demo);

        final Intent myintent = new Intent(this,TimeSocketService.class);
        startService(myintent);

        final  Toast toast = Toast.makeText(this, "", Toast.LENGTH_SHORT);

        findViewById(R.id.connectBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread() {
                    @Override
                    public void run() {

                        try {
                            Socket s = new Socket("localhost", 6668);
                            BufferedReader reader = new BufferedReader(new InputStreamReader(s.getInputStream()));

                            String dateTime = reader.readLine();
                            System.out.println("============ " + dateTime + "============");
                            toast.setText(dateTime);
                            toast.show();

                            reader.close();

                            s.close();

                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }.start();
            }
        });
    }
}
