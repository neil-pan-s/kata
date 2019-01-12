package demo.org.ichanging.intent;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;

public class BundleIntent extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
          super.onCreate(savedInstanceState);
          setContentView(R.layout.activity_bundle_intent);

        Button btn = (Button) findViewById(R.id.Register);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                EditText name = (EditText) findViewById(R.id.editName);
                EditText pwd = (EditText) findViewById(R.id.editPwd);

                RadioButton male = (RadioButton) findViewById(R.id.male);
                RadioButton female = (RadioButton) findViewById(R.id.female);

                String gender = male.isChecked() ? "Mr." : "Ms.";
                Person p = new Person(name.getText().toString(),pwd.getText().toString(),gender);
                Bundle data = new Bundle();
                data.putSerializable("Person",p);
                Intent intent = new Intent(BundleIntent.this,BundleIntentHandler.class);
                intent.putExtras(data);
                startActivity(intent);
            }
        });

    }
}
