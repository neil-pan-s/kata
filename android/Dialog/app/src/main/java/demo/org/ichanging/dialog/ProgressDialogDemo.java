package demo.org.ichanging.dialog;

import android.app.ProgressDialog;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;

public class ProgressDialogDemo extends AppCompatActivity {

    final static int MAX_PROGRESS = 100;
    int iProgressStatus = 0;
    int hasData = 0;

    ProgressDialog progressDialog1,progressDialog2;

    Handler handler = new Handler()
    {
        @Override
        public void handleMessage(Message msg)
        {
            if(msg.what == 0x123)
            {
                progressDialog2.setProgress(iProgressStatus);
            }
        }
    };



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_progress_dialog_demo);
    }

    public void showSpinner(View v)
    {
        ProgressDialog.show(this, "提示", "正在处理中,请稍候...", false, true);
    }

    public void showIndeteminate(View v)
    {
        progressDialog1 = new ProgressDialog(ProgressDialogDemo.this);
        progressDialog1.setTitle("提示");
        progressDialog1.setMessage("正在处理中,请稍候...");
        progressDialog1.setCancelable(true);
        progressDialog1.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
        progressDialog1.setIndeterminate(true);
        progressDialog1.show();
    }

    public void showProgress(View v)
    {
        iProgressStatus = 0;
        hasData = 0;
        progressDialog2  = new ProgressDialog(ProgressDialogDemo.this);
        progressDialog2.setMax(MAX_PROGRESS);
        progressDialog2.setTitle("任务完成百分比");
        progressDialog2.setMessage("耗时任务的完成百分比");
        progressDialog2.setCancelable(true);
        progressDialog2.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
        progressDialog2.setIndeterminate(false);
        progressDialog2.show();

        new Thread()
        {
            public void run()
            {
                while(iProgressStatus < MAX_PROGRESS)
                {
                    iProgressStatus++;
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    handler.sendEmptyMessage(0x123);

                }

                if(iProgressStatus >= MAX_PROGRESS)
                {
                    progressDialog2.dismiss();
                }
            }
        }.start();
    }


}

