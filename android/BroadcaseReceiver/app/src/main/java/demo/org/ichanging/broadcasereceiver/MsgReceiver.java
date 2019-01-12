package demo.org.ichanging.broadcasereceiver;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

public class MsgReceiver extends BroadcastReceiver {
    public MsgReceiver() {
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        // TODO: This method is called when the BroadcastReceiver is receiving

        Toast.makeText(context,"Msg:" + intent.getStringExtra("msg"),Toast.LENGTH_SHORT).show();

    }
}
