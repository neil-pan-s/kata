package demo.org.ichanging.intent;

import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.util.List;

public class IntentSystemActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_intent_system);

        ((Button) findViewById(R.id.buttonWeb)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent();
                intent.setAction(Intent.ACTION_VIEW);
                intent.setData(Uri.parse("http://www.baidu.com"));

                startActivity(intent);
            }
        });


        ((Button) findViewById(R.id.buttonContent)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

//                Intent intent = new Intent();
//                intent.setAction(Intent.ACTION_EDIT);
//                //编辑标识为 1 的联系人信息
//                intent.setData(Uri.parse("content://com.android.contacts/contacts/1"));
//                startActivity(intent);

                Intent intent = new Intent();
                intent.setAction(Intent.ACTION_SENDTO);
                intent.setData(Uri.parse("smsto://13352948637"));
                intent.putExtra("sms_body", "hello world");
                startActivity(intent);
            }
        });


        ((Button) findViewById(R.id.buttonTel)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent();
                intent.setAction(Intent.ACTION_DIAL);
                intent.setData(Uri.parse("tel:18079336668"));

                startActivity(intent);
            }
        });

    }
}
