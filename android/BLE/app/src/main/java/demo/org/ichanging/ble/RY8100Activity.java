package demo.org.ichanging.ble;

import android.app.Activity;
import android.app.SearchManager;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.view.View;
import android.widget.ExpandableListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class RY8100Activity extends Activity {

    private final static String TAG = RY8100Activity.class.getSimpleName();

    public static final String EXTRAS_DEVICE_NAME = "DEVICE_NAME";
    public static final String EXTRAS_DEVICE_ADDRESS = "DEVICE_ADDRESS";

    private TextView mConnectionState;
    private TextView mDataField;
    private boolean mConnected = false;
    private String mDeviceName;
    private String mDeviceAddress;

    private BluetoothLeService mBluetoothLeService = null;
    private BluetoothGattCharacteristic mRWCharacteristic = null;

    //RY8100 读写 Characteristic
    public static String RY8100_RW_CHARACTERISTIC = "0000fff6-0000-1000-8000-00805f9b34fb";

    // Code to manage Service lifecycle.
    private final ServiceConnection mServiceConnection = new ServiceConnection() {

        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            mBluetoothLeService = ((BluetoothLeService.LocalBinder) service).getService();
            if (!mBluetoothLeService.initialize()) {
                Log.e(TAG, "Unable to initialize Bluetooth");
                finish();
            }
            // Automatically connects to the device upon successful start-up initialization.
            mBluetoothLeService.connect(mDeviceAddress);
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            mBluetoothLeService = null;
        }
    };

    // Handles various events fired by the Service.
    // ACTION_GATT_CONNECTED: connected to a GATT server.
    // ACTION_GATT_DISCONNECTED: disconnected from a GATT server.
    // ACTION_GATT_SERVICES_DISCOVERED: discovered GATT services.
    // ACTION_DATA_AVAILABLE: received data from the device.  This can be a result of read
    //                        or notification operations.
    private final BroadcastReceiver mGattUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            if (BluetoothLeService.ACTION_GATT_CONNECTED.equals(action)) {

                mConnected = true;
                mConnectionState.setText(R.string.connected);

                findViewById(R.id.connectBtn).setEnabled(false);
                findViewById(R.id.disconnectBtn).setEnabled(true);
                findViewById(R.id.versionBtn).setEnabled(true);
                findViewById(R.id.panBtn).setEnabled(true);

            } else if (BluetoothLeService.ACTION_GATT_DISCONNECTED.equals(action)) {
                mConnected = false;
                mConnectionState.setText(R.string.disconnected);

                findViewById(R.id.connectBtn).setEnabled(true);
                findViewById(R.id.disconnectBtn).setEnabled(false);
                findViewById(R.id.versionBtn).setEnabled(false);
                findViewById(R.id.panBtn).setEnabled(false);

            } else if (BluetoothLeService.ACTION_GATT_SERVICES_DISCOVERED.equals(action)) {

                // Show all the supported services and characteristics on the user interface.
                List<BluetoothGattService> gattServices = mBluetoothLeService.getSupportedGattServices();

                // Loops through available GATT Services.
                for (BluetoothGattService gattService : gattServices) {

                    //String uuid = gattService.getUuid().toString();

                    List<BluetoothGattCharacteristic> gattCharacteristics = gattService.getCharacteristics();

                    // Loops through available Characteristics.
                    for (BluetoothGattCharacteristic gattCharacteristic : gattCharacteristics) {
                        String uuid = gattCharacteristic.getUuid().toString();

                        //匹配 RW Characteristic
                        if(uuid.toLowerCase().equals(RY8100_RW_CHARACTERISTIC))
                        {
                            mRWCharacteristic = gattCharacteristic;

                            //设置数据改变时发送通知
                            mBluetoothLeService.setCharacteristicNotification(mRWCharacteristic, true);
                        }
                    }
                }

                if(mRWCharacteristic == null)
                {
                    //没有匹配的 RW Characteristic
                    Toast.makeText(RY8100Activity.this,"RY8100 Device not found",Toast.LENGTH_LONG).show();
                    finish();
                }

            } else if (BluetoothLeService.ACTION_DATA_AVAILABLE.equals(action)) {

                String data =  intent.getStringExtra(BluetoothLeService.EXTRA_DATA);

                Log.d(TAG, "BLE Read Data:[" + data + "]");

                mDataField.append("\nRecv:[" + data + "]");

            }
        }
    };

    private static IntentFilter makeGattUpdateIntentFilter() {
        final IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothLeService.ACTION_GATT_CONNECTED);
        intentFilter.addAction(BluetoothLeService.ACTION_GATT_DISCONNECTED);
        intentFilter.addAction(BluetoothLeService.ACTION_GATT_SERVICES_DISCOVERED);
        intentFilter.addAction(BluetoothLeService.ACTION_DATA_AVAILABLE);
        return intentFilter;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ry8100_demo);

        final Intent intent = getIntent();
        mDeviceName = intent.getStringExtra(EXTRAS_DEVICE_NAME);
        mDeviceAddress = intent.getStringExtra(EXTRAS_DEVICE_ADDRESS);

        ((TextView) findViewById(R.id.device_address)).setText(mDeviceAddress);

        mConnectionState = (TextView) findViewById(R.id.connection_state);
        mDataField = (TextView) findViewById(R.id.textView);

        getActionBar().setTitle(mDeviceName);
        getActionBar().setDisplayHomeAsUpEnabled(true);
        Intent gattServiceIntent = new Intent(this, BluetoothLeService.class);
        bindService(gattServiceIntent, mServiceConnection, BIND_AUTO_CREATE);

        View.OnClickListener clickListener = new View.OnClickListener() {

            private final  String version_cmd = "AA0114A4";
            private final  String pan_cmd = "AA156000000000642016041706343084953200000000008C";
            private final  String pan_cmd_1 = "AA156000000000642016041706343084953200";
            private final  String pan_cmd_2 = "000000008C";


            @Override
            public void onClick(View v) {

                switch (v.getId())
                {
                    case R.id.connectBtn:
                        if(mBluetoothLeService != null) mBluetoothLeService.connect(mDeviceAddress);
                        break;
                    case R.id.disconnectBtn:
                        if(mBluetoothLeService != null) mBluetoothLeService.disconnect();
                        break;
                    case R.id.panBtn:
                        if(mRWCharacteristic != null)
                        {
                            //pan_cmd length > 19 byte ,someone say ble max send is 19
                            //mRWCharacteristic.setValue(HexStringToByteArray(pan_cmd));
                            //mBluetoothLeService.writeCharacteristic(mRWCharacteristic);

                            mRWCharacteristic.setValue(HexStringToByteArray(pan_cmd_1));
                            mBluetoothLeService.writeCharacteristic(mRWCharacteristic);

                            mRWCharacteristic.setValue(HexStringToByteArray(pan_cmd_2));
                            mBluetoothLeService.writeCharacteristic(mRWCharacteristic);

                            Log.d(TAG, "BLE Write Data:[" + pan_cmd + "]");
                        }
                        break;
                    case R.id.versionBtn:
                        if(mRWCharacteristic != null) {

                            mRWCharacteristic.setValue(HexStringToByteArray(version_cmd));
                            mBluetoothLeService.writeCharacteristic(mRWCharacteristic);

                            Log.d(TAG, "BLE Write Data:[" + version_cmd + "]");
                        }
                        break;
                }
            }
        };

        findViewById(R.id.connectBtn).setOnClickListener(clickListener);
        findViewById(R.id.disconnectBtn).setOnClickListener(clickListener);
        findViewById(R.id.panBtn).setOnClickListener(clickListener);
        findViewById(R.id.versionBtn).setOnClickListener(clickListener);
    }


    @Override
    protected void onResume() {
        super.onResume();

        registerReceiver(mGattUpdateReceiver, makeGattUpdateIntentFilter());
        if (mBluetoothLeService != null) {
            final boolean result = mBluetoothLeService.connect(mDeviceAddress);
            Log.d(TAG, "Connect request result=" + result);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        unregisterReceiver(mGattUpdateReceiver);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unbindService(mServiceConnection);
        mBluetoothLeService = null;
    }


    /**
     * Utility method to convert a byte array to a hexadecimal string.
     *
     * @param bytes Bytes to convert
     * @return String, containing hexadecimal representation.
     */
    public static String ByteArrayToHexString(byte[] bytes) {
        final char[] hexArray = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
        char[] hexChars = new char[bytes.length * 2]; // Each byte has two hex characters (nibbles)
        int v;
        for (int j = 0; j < bytes.length; j++) {
            v = bytes[j] & 0xFF; // Cast bytes[j] to int, treating as unsigned value
            hexChars[j * 2] = hexArray[v >>> 4]; // Select hex character from upper nibble
            hexChars[j * 2 + 1] = hexArray[v & 0x0F]; // Select hex character from lower nibble
        }
        return new String(hexChars);
    }

    /**
     * Utility method to convert a hexadecimal string to a byte string.
     *
     * <p>Behavior with input strings containing non-hexadecimal characters is undefined.
     *
     * @param s String containing hexadecimal characters to convert
     * @return Byte array generated from input
     * @throws java.lang.IllegalArgumentException if input length is incorrect
     */
    public static byte[] HexStringToByteArray(String s) throws IllegalArgumentException {
        int len = s.length();
        if (len % 2 == 1) {
            throw new IllegalArgumentException("Hex string must have even number of characters");
        }
        byte[] data = new byte[len / 2]; // Allocate 1 byte per 2 hex characters
        for (int i = 0; i < len; i += 2) {
            // Convert each character into a integer (base-16), then bit-shift into place
            data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4)
                    + Character.digit(s.charAt(i+1), 16));
        }
        return data;
    }
}
