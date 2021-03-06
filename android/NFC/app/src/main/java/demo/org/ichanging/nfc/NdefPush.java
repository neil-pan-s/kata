package demo.org.ichanging.nfc;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.nfc.NdefMessage;
import android.nfc.NdefRecord;
import android.nfc.NfcAdapter;
import android.nfc.NfcAdapter.CreateNdefMessageCallback;
import android.nfc.NfcAdapter.OnNdefPushCompleteCallback;
import android.nfc.NfcEvent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.Parcelable;
import android.provider.Settings;
import android.support.v7.app.AppCompatActivity;
import android.text.format.Time;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Locale;

import demo.org.ichanging.nfc.simulator.FakeTagsActivity;


public class NdefPush extends AppCompatActivity implements CreateNdefMessageCallback,OnNdefPushCompleteCallback {

    NfcAdapter mNfcAdapter;
    TextView mInfoText;

    private static final int MESSAGE_SENT = 1;

    /** This handler receives a message from onNdefPushComplete */
    private final Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case MESSAGE_SENT:
                    Toast.makeText(getApplicationContext(), "Message sent!", Toast.LENGTH_LONG).show();
                    break;
            }
        }
    };


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ndefpush);
        setTitle(R.string.ndef_push_title);

        mInfoText = (TextView) findViewById(R.id.textView);
        // Check for available NFC Adapter
        mNfcAdapter = NfcAdapter.getDefaultAdapter(this);
        if (mNfcAdapter == null)
        {
            Toast.makeText(this,"No NFC found on this device",Toast.LENGTH_SHORT).show();
            finish();
            return;
        }

        beamEnableCheck();

        // Register callback to set NDEF message
        mNfcAdapter.setNdefPushMessageCallback(this, this);
        // Register callback to listen for message-sent success
        mNfcAdapter.setOnNdefPushCompleteCallback(this, this);

    }


    /**
     * Implementation for the CreateNdefMessageCallback interface
     */
    @Override
    public NdefMessage createNdefMessage(NfcEvent event) {
        Time time = new Time();
        time.setToNow();
        String text = ("Beam me up!\n\n" + "Beam Time: " + time.format("%H:%M:%S"));

        //TNF_MIME_MEDIA
//        NdefMessage msg = new NdefMessage(NdefRecord.createMime(
//                "application/com.example.android.beam", text.getBytes())
//                /**
//                 * The Android Application Record (AAR) is commented out. When a device
//                 * receives a push with an AAR in it, the application specified in the AAR
//                 * is guaranteed to run. The AAR overrides the tag dispatch system.
//                 * You can add it back in to guarantee that this
//                 * activity starts when receiving a beamed message. For now, this code
//                 * uses the tag dispatch system.
//                 */
//                //,NdefRecord.createApplicationRecord("com.example.android.beam")
//        );

        // TNF_WELL_KNOWN RTD_TEXT
        // Need Api Level 21 -_-!!
        // NdefMessage msg = new NdefMessage(NdefRecord.createTextRecord(null,text));

        NdefMessage msg = new NdefMessage(FakeTagsActivity.newTextRecord(text, Locale.ENGLISH,true));

        return msg;
    }

    //判断Android Beam 是否打开
    private void beamEnableCheck() {
        if (!mNfcAdapter.isNdefPushEnabled())
        {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setMessage("NFC Beam is not enabled. Please go to the NFC settings to enable it.");
            builder.setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialogInterface, int i) {
                    Intent intent = new Intent(Settings.ACTION_NFCSHARING_SETTINGS);
                    startActivity(intent);
                }
            });
            builder.setNegativeButton(android.R.string.cancel, new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialogInterface, int i) {
                    //finish();
                }
            });
            builder.create().show();
        }
    }

    /**
     * Implementation for the OnNdefPushCompleteCallback interface
     */
    @Override
    public void onNdefPushComplete(NfcEvent arg0) {
        // A handler is needed to send messages to the activity when this
        // callback occurs, because it happens from a binder thread
        mHandler.obtainMessage(MESSAGE_SENT).sendToTarget();
    }

    @Override
    public void onResume() {
        super.onResume();
        // Check to see that the Activity started due to an Android Beam
        if (NfcAdapter.ACTION_NDEF_DISCOVERED.equals(getIntent().getAction())) {
            processIntent(getIntent());
        }
    }

    @Override
    public void onNewIntent(Intent intent) {
        // onResume gets called after this to handle the intent
        setIntent(intent);
    }

    /**
     * Parses the NDEF Message from the intent and prints to the TextView
     */
    void processIntent(Intent intent) {
        Parcelable[] rawMsgs = intent.getParcelableArrayExtra(
 NfcAdapter.EXTRA_NDEF_MESSAGES);
        // only one message sent during the beam
        NdefMessage msg = (NdefMessage) rawMsgs[0];
        // record 0 contains the MIME type, record 1 is the AAR, if present
        mInfoText.setText(new String(msg.getRecords()[0].getPayload()));
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // If NFC is not available, we won't be needing this menu
        if (mNfcAdapter == null) {
            return super.onCreateOptionsMenu(menu);
        }
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.options, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        Intent intent = null;
        switch (item.getItemId()) {
            case R.id.itemSimulator:
                intent = new Intent(this, FakeTagsActivity.class);
                startActivity(intent);
                return true;
            case R.id.itemBeam:
                intent = new Intent(this, NdefPush.class);
                startActivity(intent);
                return true;
            case R.id.itemNdef:
                intent = new Intent(this, NdefRead.class);
                startActivity(intent);
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
}