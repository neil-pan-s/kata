package demo.org.ichanging.network;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.MalformedURLException;
import java.net.URL;

public class GetPostDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_get_post_demo);

        final Toast toast = Toast.makeText(this,"",Toast.LENGTH_LONG);

        findViewById(R.id.getBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread()
                {
                    @Override
                    public void run() {

                        //String Q = GetPostUtil.sendGet("http://wwww.baidu.com/s","wd=changingp");
                        String Q = GetPostUtil.sendGet("http://www.w3school.com.cn/demo/welcome_get.php","name=dasd&email=dasdas");

                        //String utfText = new String(Q.getBytes(),"utf-8");

                        System.out.println(Q);

                        toast.setText(Q);
                        toast.show();

                    }
                }.start();
            }
        });

        findViewById(R.id.postBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread()
                {
                    @Override
                    public void run() {

                        String Q = GetPostUtil.sendPost("http://www.w3school.com.cn/demo/welcome.php", "name=changingp&email=x");

                        System.out.println(Q);

                        toast.setText(Q);
                        toast.show();

                    }
                }.start();
            }
        });


    }
}
