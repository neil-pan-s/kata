package demo.org.ichanging.broadcasereceiver;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Toast;

public class OrderReceiver extends BroadcastReceiver {
    public OrderReceiver() {
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        // TODO: This method is called when the BroadcastReceiver is receiving

        Toast.makeText(context, "Msg:" + intent.getStringExtra("msg"), Toast.LENGTH_SHORT).show();

        Bundle bundle = new Bundle();
        bundle.putString("result","hello dog");
        setResultExtras(bundle);

        //stop Broadcast
        //abortBroadcast();
    }
}
