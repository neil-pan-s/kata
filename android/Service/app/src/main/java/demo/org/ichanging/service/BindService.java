package demo.org.ichanging.service;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.support.annotation.Nullable;

/**
 * Created by ChangingP on 2016/4/3.
 */
public class BindService extends Service {

    private int count;
    private boolean quit;

    public class MyBinder extends Binder
    {
        public int getCount()
        {
            return count;
        }
    }

    private MyBinder binder = new MyBinder();

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        System.out.println("Service is Binded");
        return binder;
    }

    @Override
    public void onCreate() {
        super.onCreate();

        System.out.println("Service is Created");

        new Thread()
        {

            @Override
            public void run() {
                while (!quit)
                {
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                    count++;
                }
            }
        }.start();
    }

    @Override
    public boolean onUnbind(Intent intent) {
        System.out.println("Service is Unbinded");

        return true;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();

        this.quit = true;
        System.out.println("Service is Destroyed");

    }
}
