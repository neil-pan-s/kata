package demo.org.ichanging.broadcasereceiver;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Toast;

public class BatteryReceiver extends BroadcastReceiver {
    public BatteryReceiver() {
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        // TODO: This method is called when the BroadcastReceiver is receiving

        Bundle bundle = intent.getExtras();
        int nowLevel = bundle.getInt("level");
        int fullLevel = bundle.getInt("scale");

        Toast.makeText(context,"Battery Low Status: " + nowLevel/fullLevel,Toast.LENGTH_SHORT).show();
    }
}
