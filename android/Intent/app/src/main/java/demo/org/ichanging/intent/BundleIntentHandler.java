package demo.org.ichanging.intent;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

public class BundleIntentHandler extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bundle_intent_handler);

        Intent intent = getIntent();

        Person p = (Person) intent.getSerializableExtra("Person");
        if(p != null)
        {
            Toast.makeText(this, "Name:" + p.getName() + "\nPwd:" + p.getPwd() + "\nGender: " + p.getGender(), Toast.LENGTH_SHORT).show();
        }else{
            Toast.makeText(this, "No Person Info", Toast.LENGTH_SHORT).show();
        }
    }
}
