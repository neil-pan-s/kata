package demo.org.ichanging.network;

import android.content.Entity;
import android.os.Looper;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import org.apache.http.HttpEntity;
import org.apache.http.HttpHost;
import org.apache.http.HttpRequest;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.methods.HttpUriRequest;
import org.apache.http.conn.ClientConnectionManager;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.params.HttpParams;
import org.apache.http.protocol.HTTP;
import org.apache.http.protocol.HttpContext;
import org.apache.http.util.EntityUtils;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;


public class HttpClientDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_http_client_demo);

        final Toast toast = Toast.makeText(this,"",Toast.LENGTH_LONG);
        final HttpClient httpClient = new DefaultHttpClient();

        findViewById(R.id.getBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread() {
                    @Override
                    public void run() {
                        try {
                            HttpGet httpGet = new HttpGet("http://www.w3school.com.cn/demo/welcome_get.php?name=dasd&email=dasdas");
                            HttpResponse httpResponse = httpClient.execute(httpGet);
                            HttpEntity entity = httpResponse.getEntity();
                            if(entity != null)
                            {
                                BufferedReader br = new BufferedReader(new InputStreamReader(entity.getContent()));

                                StringBuilder sb = new StringBuilder();
                                String line = null;
                                while ( (line = br.readLine()) != null)
                                {
                                    sb.append(line);
                                }

                                System.out.println(sb.toString());
                                toast.setText(sb.toString());
                                toast.show();

                                br.close();
                            }

                        } catch (IOException e) {
                            e.printStackTrace();
                        }

                    }
                }.start();
            }
        });

        findViewById(R.id.postBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread() {
                    @Override
                    public void run() {

                        String Q = GetPostUtil.sendPost("http://www.w3school.com.cn/demo/welcome.php", "name=changingp&email=x");

                        try {
                            HttpPost httpPost = new HttpPost("http://www.w3school.com.cn/demo/welcome.php");

                            List<NameValuePair> params = new ArrayList<NameValuePair>();
                            params.add(new BasicNameValuePair("name","changingp"));
                            params.add(new BasicNameValuePair("email","xxxx#xxxx.ooo"));
                            httpPost.setEntity(new UrlEncodedFormEntity(params, HTTP.UTF_8));

                            HttpResponse httpResponse = httpClient.execute(httpPost);

                            //Server return succ
                            if(httpResponse.getStatusLine().getStatusCode() == 200)
                            {
                                HttpEntity entity = httpResponse.getEntity();
                                String msg = EntityUtils.toString(entity);

                                //线程中操作UI处理
                                Looper.prepare();
                                Toast.makeText(HttpClientDemo.this,msg,Toast.LENGTH_LONG).show();
                                Looper.loop();

                            }

                        } catch (IOException e) {
                            e.printStackTrace();
                        }

                    }
                }.start();
            }
        });


    }
}
