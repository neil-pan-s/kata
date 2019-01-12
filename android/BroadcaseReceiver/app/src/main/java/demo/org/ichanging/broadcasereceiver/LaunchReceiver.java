package demo.org.ichanging.broadcasereceiver;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class LaunchReceiver extends BroadcastReceiver {
    public LaunchReceiver() {
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        // TODO: This method is called when the BroadcastReceiver is receiving

        //开机自动启动某项服务
//        Intent intent1 = new Intent(context,xxxxService.class);
//        context.startService(intent1);
    }
}
