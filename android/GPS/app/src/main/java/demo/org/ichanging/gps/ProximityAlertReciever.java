package demo.org.ichanging.gps;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.location.LocationManager;
import android.widget.Toast;

/**
 * Created by ChangingP on 2016/4/5.
 */
public class ProximityAlertReciever extends BroadcastReceiver
{

    @Override
    public void onReceive(Context context, Intent intent) {

        boolean isIn = intent.getBooleanExtra(LocationManager.KEY_PROXIMITY_ENTERING,false);

        if(isIn)
        {
            Toast.makeText(context,"You are in Company",Toast.LENGTH_SHORT).show();
        }else{
            Toast.makeText(context,"You are out Company",Toast.LENGTH_SHORT).show();
        }

    }
}
