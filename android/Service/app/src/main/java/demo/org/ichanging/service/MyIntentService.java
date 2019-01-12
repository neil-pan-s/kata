package demo.org.ichanging.service;

import android.app.IntentService;
import android.content.Intent;

/**
 * Created by ChangingP on 2016/4/3.
 */
public class MyIntentService extends IntentService {

    public MyIntentService()
    {
        super("MyIntentService");
    }

    //IntentService will start a new thread to execute
    //IntentService will stop after execute over
    @Override
    protected void onHandleIntent(Intent intent) {
        long endTime = System.currentTimeMillis() + 20*1000;

        System.out.println("onHandleIntent Start");

        while (System.currentTimeMillis() < endTime)
        {
            synchronized (this)
            {
                try {
                    wait(endTime - System.currentTimeMillis());
                    System.out.println("onHandleIntent Tick");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        System.out.println("onHandleIntent Over");
    }
}
