package demo.org.ichanging.otherswidget;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.NumberPicker;
import android.widget.Toast;

public class NumberPickerDemo extends AppCompatActivity {

    Toast mToast;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_number_picker_demo);

        mToast = Toast.makeText(NumberPickerDemo.this,"",Toast.LENGTH_SHORT);

        NumberPicker numberPicker = (NumberPicker) findViewById(R.id.numberPicker);
        numberPicker.setMaxValue(50);
        numberPicker.setMinValue(10);
        numberPicker.setValue(25);

        numberPicker.setOnValueChangedListener(new NumberPicker.OnValueChangeListener() {
            @Override
            public void onValueChange(NumberPicker picker, int oldVal, int newVal) {
                mToast.setText("curValue: " + newVal);
                mToast.show();
            }
        });

    }
}
