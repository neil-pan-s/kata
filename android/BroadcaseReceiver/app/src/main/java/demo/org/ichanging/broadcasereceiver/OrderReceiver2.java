package demo.org.ichanging.broadcasereceiver;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Toast;

public class OrderReceiver2 extends BroadcastReceiver {
    public OrderReceiver2() {
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        // TODO: This method is called when the BroadcastReceiver is receiving

        String result = null;

        Bundle bundle = getResultExtras(true);

        if(bundle != null) {
            result = bundle.getString("result");
        }

        Toast.makeText(context, "Msg:" + intent.getStringExtra("msg") + "\nResult: " + result, Toast.LENGTH_SHORT).show();

    }
}
