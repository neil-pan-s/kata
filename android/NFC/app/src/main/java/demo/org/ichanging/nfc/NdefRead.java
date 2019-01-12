package demo.org.ichanging.nfc;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.PendingIntent;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.nfc.NdefMessage;
import android.nfc.NdefRecord;
import android.nfc.NfcAdapter;
import android.nfc.NfcManager;
import android.nfc.Tag;
import android.os.Parcelable;
import android.provider.Settings;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import demo.org.ichanging.nfc.record.ParsedNdefRecord;
import demo.org.ichanging.nfc.simulator.FakeTagsActivity;

public class NdefRead extends AppCompatActivity {

    private NfcAdapter mAdapter = null;
    private PendingIntent mPendingIntent = null;

    private static final DateFormat TIME_FORMAT = SimpleDateFormat.getDateTimeInstance();
    private LinearLayout mTagContent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tag_viewer);
        setTitle(R.string.ndef_read_title);

        mTagContent = (LinearLayout) findViewById(R.id.list);

        mAdapter = NfcAdapter.getDefaultAdapter(this);
        if (mAdapter == null) {
            Toast.makeText(this,"No NFC found on this device",Toast.LENGTH_SHORT).show();
            finish();
            return;
        }

        nfcEnableCheck();

        mPendingIntent = PendingIntent.getActivity(this, 0, new Intent(this, getClass()).addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP), 0);

        //Necessary
        resolveIntent(getIntent());
    }

    //判断NFC是否打开
    private void nfcEnableCheck() {
        if (!mAdapter.isEnabled())
        {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setMessage("NFC is not enabled. Please go to the NFC settings to enable it.");
            builder.setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialogInterface, int i) {
                    Intent intent = new Intent(Settings.ACTION_NFC_SETTINGS);
                    startActivity(intent);
                }
            });
            builder.setNegativeButton(android.R.string.cancel, new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialogInterface, int i) {
                    finish();
                }
            });
            builder.create().show();
        }
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

            nfcEnableCheck();


            /* Handles all MIME based dispatches. You should specify only the ones that you need. */
            IntentFilter ndefilter = new IntentFilter(NfcAdapter.ACTION_NDEF_DISCOVERED);

            try {
                ndefilter.addDataType("*/*");
            } catch (IntentFilter.MalformedMimeTypeException e) {
                e.printStackTrace();
            }

            IntentFilter[] intentFiltersArray = new IntentFilter[] { ndefilter, };

            /*
            * @param intent the PendingIntent to start for the dispatch
            * @param filters the IntentFilters to override dispatching for, or null to always dispatch
            * @param techLists the tech lists used to perform matching for dispatching of the
            *
            */
            mAdapter.enableForegroundDispatch(this, mPendingIntent, intentFiltersArray, null);
            //mAdapter.enableForegroundDispatch(this, mPendingIntent, null, null);
        }
    }


    //解析NFC数据
    void resolveIntent(Intent intent) {
        // Parse the intent
        String action = intent.getAction();

        System.out.println("========== Action " + action + " ==========");
        if (
                NfcAdapter.ACTION_TAG_DISCOVERED.equals(action) ||
                NfcAdapter.ACTION_TECH_DISCOVERED.equals(action) ||
                NfcAdapter.ACTION_NDEF_DISCOVERED.equals(action)
            )
        {
            // When a tag is discovered we send it to the service to be save. We
            // include a PendingIntent for the service to call back onto. This
            // will cause this activity to be restarted with onNewIntent(). At
            // that time we read it from the database and view it.
            Parcelable[] rawMsgs = intent.getParcelableArrayExtra(NfcAdapter.EXTRA_NDEF_MESSAGES);
            NdefMessage[] msgs;
            if (rawMsgs != null) {
                msgs = new NdefMessage[rawMsgs.length];
                for (int i = 0; i < rawMsgs.length; i++) {
                    msgs[i] = (NdefMessage) rawMsgs[i];
                    System.out.println(msgs[i]);

                    NdefRecord[] records = msgs[i].getRecords();
                    for (int j = 0; j < records.length; j++) {

                        //do something with Ndef Record
                        System.out.println(records[j]);

                    }
                }

                buildTagViews(msgs);
            } else {
                // Unknown tag type
                Toast.makeText(this, "TNF_UNKNOWN",Toast.LENGTH_LONG).show();
                return;
            }

        } else {
//            Toast.makeText(this, "Unknown intent " + intent,Toast.LENGTH_LONG).show();
//            finish();
//            return;
        }
    }

    //显示NDEF信息
    void buildTagViews(NdefMessage[] msgs)
    {
        if (msgs == null || msgs.length == 0) {
            return;
        }
        LayoutInflater inflater = LayoutInflater.from(this);
        LinearLayout content = mTagContent;

        // Parse the first message in the list
        // Build views for all of the sub records
        Date now = new Date();
        List<ParsedNdefRecord> records = NdefMessageParser.parse(msgs[0]);
        final int size = records.size();
        for (int i = 0; i < size; i++) {
            TextView timeView = new TextView(this);
            timeView.setText("\n" + TIME_FORMAT.format(now));
            content.addView(timeView, 0);
            ParsedNdefRecord record = records.get(i);
            content.addView(record.getView(this, inflater, content, i), 1 + i);
            content.addView(inflater.inflate(R.layout.tag_divider, content, false), 2 + i);
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
        resolveIntent(intent);

    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // If NFC is not available, we won't be needing this menu
        if (mAdapter == null) {
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
            case R.id.itemBankCard:
                intent = new Intent(this, BankCard.class);
                startActivity(intent);
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
}
