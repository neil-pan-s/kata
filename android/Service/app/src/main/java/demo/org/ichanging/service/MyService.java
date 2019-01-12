package demo.org.ichanging.service;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.support.annotation.Nullable;

/**
 * Created by ChangingP on 2016/4/3.
 */
public class MyService extends Service{

    private boolean quit;

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();

        System.out.println("Service Created");
    }

//
//    START_NOT_STICKY：当Service因为内存不足而被系统kill后，接下来未来的某个时间内，即使系统内存足够可用，系统也不会尝试重新创建此Service。除非程序中Client明确再次调用startService(...)启动此Service。
//
//    START_STICKY：当Service因为内存不足而被系统kill后，接下来未来的某个时间内，当系统内存足够可用的情况下，系统将会尝试重新创建此Service，一旦创建成功后将回调onStartCommand(...)方法，但其中的Intent将是null，pendingintent除外。
//
//    START_REDELIVER_INTENT：与START_STICKY唯一不同的是，回调onStartCommand(...)方法时，其中的Intent将是非空，将是最后一次调用startService(...)中的intent。
//
//    START_STICKY_COMPATIBILITY：compatibility version of {@link #START_STICKY} that does not guarantee that {@link #onStartCommand} will be called again after being killed。此值一般不会使用，所以注意前面三种情形就好。

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        System.out.println("Service Started");

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
                    System.out.println("----------- Service Tick -----------");
                }
            }
        }.start();

        return START_STICKY;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();

        this.quit = true;
        System.out.println("Service Destroyed");
    }
}
