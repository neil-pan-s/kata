package demo.org.ichanging.otherswidget;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.DatePicker;
import android.widget.TimePicker;
import android.widget.Toast;

import java.util.Calendar;

public class DateTimePickerDemo extends AppCompatActivity {

    private static final String TAG = "DateTimePickerDemo";

    DatePicker datePicker;
    TimePicker timePicker;
    Toast toast;

    private int year;
    private int month;
    private int day;
    private int hour;
    private int minute;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_date_time_picker_demo);

        datePicker = (DatePicker) findViewById(R.id.datePicker);
        timePicker = (TimePicker) findViewById(R.id.timePicker);
        timePicker.setVisibility(View.INVISIBLE);

        toast = Toast.makeText(DateTimePickerDemo.this,"",Toast.LENGTH_SHORT);


        Calendar c = Calendar.getInstance();
        year = c.get(Calendar.YEAR);
        month = c.get(Calendar.MONTH);
        day = c.get(Calendar.DATE);
        hour = c.get(Calendar.HOUR);
        minute = c.get(Calendar.MINUTE);

        datePicker.init(year, month, day, new DatePicker.OnDateChangedListener() {
            @Override
            public void onDateChanged(DatePicker view, int year, int monthOfYear, int dayOfMonth) {
                DateTimePickerDemo.this.year = year;
                DateTimePickerDemo.this.month = monthOfYear;
                DateTimePickerDemo.this.day = dayOfMonth;

                showDate(year,month,day,hour,minute);
            }
        });

        timePicker.setOnTimeChangedListener(new TimePicker.OnTimeChangedListener() {
            @Override
            public void onTimeChanged(TimePicker view, int hourOfDay, int minute) {
                DateTimePickerDemo.this.hour = hourOfDay;
                DateTimePickerDemo.this.minute = minute;

                showDate(year, month, day, hour, minute);
            }
        });
    }

    private  void showDate(int year,int month,int day,int hour,int minute)
    {
        Log.i(TAG,"====== DateTime:"+year+"年"+(month+1)+"月"+day+"日 "+hour+"时"+minute+"分");
        toast.setText("DateTime:"+year+"年"+(month+1)+"月"+day+"日 "+hour+"时"+minute+"分");
        toast.show();
    }

    public void turnWidget(View v)
    {
        if(timePicker.getVisibility() == View.INVISIBLE)
            timePicker.setVisibility(View.VISIBLE);
        else if(timePicker.getVisibility() == View.VISIBLE)
            timePicker.setVisibility(View.INVISIBLE);

        if(datePicker.getVisibility() == View.INVISIBLE)
            datePicker.setVisibility(View.VISIBLE);
        else if(datePicker.getVisibility() == View.VISIBLE)
            datePicker.setVisibility(View.INVISIBLE);

    }

}
