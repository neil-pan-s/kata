package demo.org.ichanging.service;

import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.telephony.PhoneStateListener;
import android.telephony.TelephonyManager;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.Switch;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class TelephonyManagerDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_telephony_manager_demo);

        TelephonyManager telephonyManager = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);

        String[] statusNames = getResources().getStringArray(R.array.statusNames);
        String[] simState = getResources().getStringArray(R.array.simState);
        String[] phoneType = getResources().getStringArray(R.array.phoneType);

        ArrayList<String> statusValues = new ArrayList<>();

        //依照statusName Array 顺序 载入数据
        statusValues.add(telephonyManager.getDeviceId());
        statusValues.add(telephonyManager.getDeviceSoftwareVersion());
        statusValues.add(telephonyManager.getNetworkOperator());
        statusValues.add(telephonyManager.getNetworkOperatorName());
        statusValues.add(phoneType[telephonyManager.getPhoneType()]);
        statusValues.add(telephonyManager.getCellLocation().toString());
        statusValues.add(telephonyManager.getSimCountryIso());
        statusValues.add(telephonyManager.getSimSerialNumber());
        statusValues.add(simState[telephonyManager.getSimState()]);

        ArrayList<Map<String,String>> status = new ArrayList<>();

        for(int i = 0;i < statusNames.length ;i++)
        {
            HashMap<String,String> map = new HashMap<>();
            map.put("name",statusNames[i]);
            map.put("value",statusValues.get(i));
            status.add(map);
        }

        SimpleAdapter adapter = new SimpleAdapter(
                this,
                status,
                R.layout.line,
                new String[]{"name","value"},
                new int[]{R.id.name,R.id.value}
        );

        ((ListView) findViewById(R.id.listView)).setAdapter(adapter);


        //创建一个通话状态监听器
        PhoneStateListener phoneStateListener = new PhoneStateListener()
        {
            @Override
            public void onCallStateChanged(int state, String incomingNumber) {
                switch(state)
                {
                    case TelephonyManager.CALL_STATE_IDLE:
                    case TelephonyManager.CALL_STATE_OFFHOOK:
                        break;
                    case TelephonyManager.CALL_STATE_RINGING:
                        //come a call
                        Toast.makeText(TelephonyManagerDemo.this,"Call:" + incomingNumber,Toast.LENGTH_SHORT).show();
                        break;
                    default:break;
                }
                super.onCallStateChanged(state,incomingNumber);
            }
        };

        //listen to the call
        telephonyManager.listen(phoneStateListener,PhoneStateListener.LISTEN_CALL_STATE);

    }

}
