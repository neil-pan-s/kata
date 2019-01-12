package demo.org.ichanging.network;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;

public class UrlDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_url_demo);

        final Toast toast = Toast.makeText(this,"",Toast.LENGTH_SHORT);

        findViewById(R.id.xBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread()
                {
                    @Override
                    public void run() {

                        try {
                            URL url = new URL("http://www.baidu.com");
                            InputStream is = url.openStream();

                            BufferedReader reader = new BufferedReader(new InputStreamReader(is));
                            StringBuilder sb = new StringBuilder();
                            String line = null;
                            while ( (line = reader.readLine()) != null)
                            {
                                sb.append(line);
                            }

                            System.out.println(sb.toString());
                            toast.setText(sb.toString());
                            toast.show();

                            reader.close();
                            is.close();

                        } catch (MalformedURLException e) {
                            e.printStackTrace();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }.start();
            }
        });

    }
}
