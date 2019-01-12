package demo.org.ichanging.service;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Vibrator;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class AlarmDialog extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_alarm_dialog);

        new AlertDialog.Builder(AlarmDialog.this)
                .setTitle("Alarm")
                .setMessage("Good Thing Will Happend -_-")
                .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {

                        AlarmDialog.this.finish();
                    }
                }).show();
    }
}
