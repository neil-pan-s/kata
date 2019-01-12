package demo.org.ichanging.nfc;

import android.app.PendingIntent;
import android.content.Intent;
import android.content.IntentFilter;
import android.nfc.NdefMessage;
import android.nfc.NdefRecord;
import android.nfc.NfcAdapter;
import android.nfc.Tag;
import android.nfc.cardemulation.HostApduService;
import android.nfc.tech.NfcA;
import android.os.Parcelable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

import demo.org.ichanging.nfc.util.ApduUtil;

public class BankCard extends AppCompatActivity {

    private NfcAdapter mAdapter = null;
    private PendingIntent mPendingIntent = null;
    private ApduUtil mApduUtil = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_band_card_read);

        mAdapter=NfcAdapter.getDefaultAdapter(this);
        if(mAdapter==null)
        {
            Toast.makeText(this, "No NFC found on this device", Toast.LENGTH_SHORT).show();
            finish();
            return;
        }

        mPendingIntent = PendingIntent.getActivity(this, 0, new Intent(this, getClass()).addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP), 0);
        mApduUtil = new ApduUtil();

    }


    @Override
    public void onPause() {
        super.onPause();
        if (mAdapter != null)
        {
            mAdapter.disableForegroundDispatch(this);
        }
    }


    @Override
    public void onResume() {
        super.onResume();

        if (mAdapter != null) {
            mAdapter.enableForegroundDispatch(this, mPendingIntent, null, null);
        }
    }

    /*
     *
     * launchMode为singleTask的时候 通过Intent启到一个Activity
     * 如果系统已经存在一个实例 系统就会将请求发送到这个实例上
     * 但这个时候 系统就不会再调用通常情况下我们处理请求数据的onCreate方法 而是调用onNewIntent方法
     *
     */
    @Override
    public void onNewIntent(Intent intent) {

        //must store the new intent unless getIntent() will return the old one
        setIntent(intent);

        onReadCard(intent);

    }


    void onReadCard(Intent intent) {
        // Parse the intent
        String action = intent.getAction();

        //银行卡返回的ACTION 为 ACTION_TAG_DISCOVERED
        if (NfcAdapter.ACTION_TAG_DISCOVERED.equals(action))
        {

            Tag tagFromIntent = getIntent().getParcelableExtra(NfcAdapter.EXTRA_TAG);

            //do something with Ndef Record
            System.out.println(tagFromIntent);

            mApduUtil.onTagDiscovered(tagFromIntent);

            mApduUtil.onReadCard(this);

        } else {
            // Unknown tag type
            Toast.makeText(this, "TNF_UNKNOWN",Toast.LENGTH_LONG).show();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        if(mApduUtil != null)
        {
            mApduUtil.onClose();
        }
    }
}


