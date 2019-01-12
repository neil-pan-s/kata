package demo.org.ichanging.network;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;

public class TimeSocketService extends Service {

    final int TIME_SERVICE_PORT = 6668;

    public TimeSocketService() {
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        throw new UnsupportedOperationException("Not yet implemented");
    }


    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {

        System.out.println("----------- TimeSocketService -----------");

        new Thread()
        {
            @Override
            public void run() {

                ServerSocket ss = null;

                try {
                    ss = new ServerSocket(TIME_SERVICE_PORT);
                } catch (IOException e) {
                    e.printStackTrace();
                    return;
                }

                while (true)
                {
                    try {
                        Socket s = ss.accept();

                        OutputStream os = s.getOutputStream();

                        SimpleDateFormat timeFmt=new SimpleDateFormat("yy/MM/dd HH:mm:ss");
                        String dateTime = timeFmt.format(new Date()).toString();

                        System.out.println("----------- "+ dateTime +" -----------");

                        os.write(dateTime.getBytes("utf-8"));
                        os.close();
                        s.close();

                    } catch (IOException e) {
                        e.printStackTrace();
                    }

                }
            }
        }.start();

        return START_STICKY;
    }

}
