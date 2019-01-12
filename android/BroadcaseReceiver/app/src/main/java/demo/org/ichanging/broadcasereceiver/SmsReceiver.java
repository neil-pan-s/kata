package demo.org.ichanging.broadcasereceiver;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.telephony.SmsMessage;
import android.widget.Toast;

public class SmsReceiver extends BroadcastReceiver {
    public SmsReceiver() {
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        // TODO: This method is called when the BroadcastReceiver is receiving

        System.out.println("============= SmsReceiver onReceive : " + intent.getAction().toString() + "=============");

        //  android.provider.Telephony.SMS_RECEICED maybe is unused

        if(intent.getAction().equals("android.provider.Telephony.SMS_RECEICED"))
        {
            abortBroadcast();

            StringBuilder stringBuilder = new StringBuilder();
            Bundle bundle = intent.getExtras();

            if(bundle != null)
            {
                Object[] pdus = (Object[]) bundle.get("pdus");
                SmsMessage[] messages = new SmsMessage[pdus.length];

                for(int i = 0;i<pdus.length;i++)
                {
                    messages[i] = SmsMessage.createFromPdu((byte[]) pdus[i]);
                }

                for (SmsMessage message:messages)
                {
                    stringBuilder.append("From" + message.getDisplayOriginatingAddress());
                    stringBuilder.append("Body" + message.getDisplayMessageBody());
                }

                Toast.makeText(context,stringBuilder.toString(),Toast.LENGTH_SHORT).show();
            }

        }

    }
}
