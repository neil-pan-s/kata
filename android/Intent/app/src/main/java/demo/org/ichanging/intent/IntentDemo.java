package demo.org.ichanging.intent;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class IntentDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_intent_demo);

        Button btn = (Button) findViewById(R.id.button);
        btn.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Intent intent = new Intent(IntentDemo.this,EmptyDemo.class);
                startActivity(intent);
            }
        });

        Button btn_r = (Button) findViewById(R.id.button_r);
        btn_r.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(IntentDemo.this,SelectCityDemo.class);
                startActivityForResult(intent,999);
            }
        });
    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        System.out.println("============== requestCode " + requestCode + "resultCode" + resultCode + "===============");

        if(requestCode == 999 && resultCode == 0)
        {
            Bundle bundle = data.getExtras();
            String resultCity = bundle.getString("city");
            Toast.makeText(this,"Choose City:" + resultCity,Toast.LENGTH_SHORT).show();
        }
    }
}
