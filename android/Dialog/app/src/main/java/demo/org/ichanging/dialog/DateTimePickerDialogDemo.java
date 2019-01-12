package demo.org.ichanging.dialog;

import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.TimePicker;
import android.widget.Toast;

import java.util.Calendar;

public class DateTimePickerDialogDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_date_time_picker_dialog_demo);

        Button setDate = (Button) findViewById(R.id.setDate);
        Button setTime = (Button) findViewById(R.id.setTime);

        setDate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Calendar c = Calendar.getInstance();
                new DatePickerDialog(DateTimePickerDialogDemo.this,
                        new DatePickerDialog.OnDateSetListener()
                        {
                            @Override
                            public void onDateSet(DatePicker dp,int year,int month,int dayofMonth)
                            {

                                Toast.makeText(DateTimePickerDialogDemo.this,"set Date:" + year + "年" + month + "月" + dayofMonth + "日",Toast.LENGTH_SHORT).show();

                            }
                        }
                        ,c.get(Calendar.YEAR)
                        ,c.get(Calendar.MONTH)
                        ,c.get(Calendar.DAY_OF_MONTH)).show();
            }
        });

        setTime.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Calendar c = Calendar.getInstance();
                new TimePickerDialog(DateTimePickerDialogDemo.this,
                        new TimePickerDialog.OnTimeSetListener()
                        {
                            @Override
                            public void onTimeSet(TimePicker dp,int hourOfDay,int minute)
                            {
                                Toast.makeText(DateTimePickerDialogDemo.this,"set Time:" + hourOfDay + "时" + minute + "分",Toast.LENGTH_SHORT).show();
                            }
                        }
                        ,c.get(Calendar.HOUR_OF_DAY)
                        ,c.get(Calendar.MINUTE)
                        ,true).show();
            }
        });




    }
}
