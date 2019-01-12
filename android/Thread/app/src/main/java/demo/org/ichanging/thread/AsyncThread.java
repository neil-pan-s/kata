package demo.org.ichanging.thread;

import android.app.ProgressDialog;
import android.content.Context;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.nio.charset.MalformedInputException;

public class AsyncThread extends AppCompatActivity {

    private TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_async_thread);

        textView = (TextView) findViewById(R.id.textView);

    }

    public void download(View v) throws MalformedInputException, MalformedURLException {
        DownTask task = new DownTask(this);
        URL TaskUrl =  new URL("http://www.baidu.com");
        task.execute(TaskUrl);
    }


    class DownTask extends AsyncTask<URL,Integer,String>
    {
        ProgressDialog progressDialog;
        int hasRead = 0;
        Context mContext;

        public DownTask(Context ctx)
        {
            mContext = ctx;
        }

        @Override
        protected String doInBackground(URL... params) {
            StringBuilder stringBuilder = new StringBuilder();
            try
            {
                URLConnection connection = params[0].openConnection();
                BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(connection.getInputStream(),"utf-8"));
                String line = null;
                while((line = bufferedReader.readLine()) != null)
                {
                    stringBuilder.append(line+"\n");
                    System.out.println(line + "\n");
                    hasRead++;
                    publishProgress(hasRead);
                }
                return stringBuilder.toString();

            }catch (Exception e){
                e.printStackTrace();
            }

            return null;
        }

        @Override
        protected void onPostExecute(String s) {
            textView.setText(s);
            progressDialog.dismiss();
        }

        @Override
        protected void onPreExecute() {
            progressDialog = new ProgressDialog(mContext);
            progressDialog.setTitle("任务执行中");
            progressDialog.setMessage("任务正在执行中，请稍后...");
            progressDialog.setCancelable(false);
            progressDialog.setMax(100);
            progressDialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
            progressDialog.setIndeterminate(false);
            progressDialog.show();

        }

        @Override
        protected void onProgressUpdate(Integer... values) {

            textView.setText("Get " + values[0] + "Line");
            progressDialog.setProgress(values[0]);
        }
    }

}
