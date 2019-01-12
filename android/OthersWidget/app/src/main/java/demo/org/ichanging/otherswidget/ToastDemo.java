package demo.org.ichanging.otherswidget;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.ColorFilter;
import android.graphics.drawable.Drawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

public class ToastDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_toast_demo);

        Button btn = (Button) findViewById(R.id.button);

        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Toast toast = Toast.makeText(ToastDemo.this,"hello world",Toast.LENGTH_SHORT);
                toast.show();
            }
        });

        Button btn2 = (Button) findViewById(R.id.button2);
        btn2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast toast = new Toast(ToastDemo.this);
                toast.setGravity(Gravity.CENTER, 0, 0);

                ImageView image = new ImageView(ToastDemo.this);
                image.setImageResource(R.drawable.ic_launcher);

                LinearLayout layout = new LinearLayout(ToastDemo.this);
                //layout.setBackgroundColor(Color.BLACK);
                layout.addView(image);

                TextView textView = new TextView(ToastDemo.this);
                textView.setText("\nhello world");
                textView.setTextSize(24);
                textView.setTextColor(Color.DKGRAY);
                layout.addView(textView);

                toast.setView(layout);
                toast.setDuration(Toast.LENGTH_LONG);
                toast.show();
            }
        });

    }
}
