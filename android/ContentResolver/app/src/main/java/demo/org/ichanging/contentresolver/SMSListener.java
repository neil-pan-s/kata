package demo.org.ichanging.contentresolver;

import android.database.ContentObserver;
import android.database.Cursor;
import android.net.Uri;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

public class SMSListener extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_smslistener);

        getContentResolver().registerContentObserver(Uri.parse("content://sms"),true,new SmsObserver(new Handler()));
    }

    private final class SmsObserver extends ContentObserver
    {

        /**
         * Creates a content observer.
         *
         * @param handler The handler to run {@link #onChange} on, or null if none.
         */
        public SmsObserver(Handler handler) {
            super(handler);

        }

        @Override
        public void onChange(boolean selfChange) {
            StringBuilder stringBuilder = new StringBuilder();
            Cursor cursor = getContentResolver().query(Uri.parse("content://sms/inbox/"),null,null,null,null);
            while(cursor.moveToNext())
            {
                stringBuilder.append("\nAddress:").append(cursor.getString(cursor.getColumnIndex("address")));
                stringBuilder.append("\nSubject:").append(cursor.getString(cursor.getColumnIndex("subject")));
                stringBuilder.append("\nBody:").append(cursor.getString(cursor.getColumnIndex("body")));
                stringBuilder.append("\nDate:").append(cursor.getLong(cursor.getColumnIndex("date")));

                System.out.println("Get SMS:" + stringBuilder.toString());
            }

            cursor.moveToFirst();
            stringBuilder.setLength(0);

            stringBuilder.append("\nAddress:").append(cursor.getString(cursor.getColumnIndex("address")));
            stringBuilder.append("\nSubject:").append(cursor.getString(cursor.getColumnIndex("subject")));
            stringBuilder.append("\nBody:").append(cursor.getString(cursor.getColumnIndex("body")));
            stringBuilder.append("\nDate:").append(cursor.getString(cursor.getColumnIndex("date")));

            Toast.makeText(SMSListener.this,stringBuilder.toString(),Toast.LENGTH_LONG).show();
        }
    }


}

