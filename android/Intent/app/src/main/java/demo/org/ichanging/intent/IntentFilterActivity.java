package demo.org.ichanging.intent;

import android.content.ComponentName;
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

public class IntentFilterActivity extends AppCompatActivity {

    public final  static  String TEST_ACTION = "demo.org.ichanging.intent.action.TEST";
    public final  static  String TEST_CATEGORY = "demo.org.ichanging.intent.category.CATEGORY";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_intent_filter);

        ((Button) findViewById(R.id.buttonComponent)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ComponentName componentName = new ComponentName(IntentFilterActivity.this, EmptyDemo.class);

                Intent intent = new Intent();
                intent.setComponent(componentName);

                //same as
                //Intent intent = new Intent(IntentFilterActivity.this,EmptyDemo.class);

                startActivity(intent);
            }
        });

        ((Button) findViewById(R.id.buttonAction)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent();
                intent.setAction(IntentFilterActivity.TEST_ACTION);
                startActivity(intent);
            }
        });


        ((Button) findViewById(R.id.buttonCate)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent();
                intent.setAction(IntentFilterActivity.TEST_ACTION);
                intent.addCategory(IntentFilterActivity.TEST_CATEGORY);
                startActivity(intent);
            }
        });


        ((Button) findViewById(R.id.buttonHome)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                //go android home
                Intent intent = new Intent();
                intent.setAction(Intent.ACTION_MAIN);
                intent.addCategory(Intent.CATEGORY_HOME);
                startActivity(intent);
            }
        });


        ((Button) findViewById(R.id.buttonScheme)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent();
                intent.setData(Uri.parse("ichanging:"));

                PackageManager packageManager = getPackageManager();
                List<ResolveInfo> activities = packageManager.queryIntentActivities(intent, 0);
                boolean isIntentSafe = activities.size() > 0;
                if(!isIntentSafe)
                {
                    Toast.makeText(IntentFilterActivity.this,"No Match Activity",Toast.LENGTH_SHORT).show();
                    return;

                }

                startActivity(intent);


            }
        });

        ((Button) findViewById(R.id.buttonSHPort)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent();
                intent.setData(Uri.parse("ichanging://www.ichanging.org:8888"));

                PackageManager packageManager = getPackageManager();
                List<ResolveInfo> activities = packageManager.queryIntentActivities(intent, 0);
                boolean isIntentSafe = activities.size() > 0;
                if(!isIntentSafe)
                {
                    Toast.makeText(IntentFilterActivity.this,"No Match Activity",Toast.LENGTH_SHORT).show();
                    return;
                }


                startActivity(intent);
            }
        });


        ((Button) findViewById(R.id.buttonSHPath)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent();
                intent.setData(Uri.parse("ichanging://www.ichanging.org/test"));

                PackageManager packageManager = getPackageManager();
                List<ResolveInfo> activities = packageManager.queryIntentActivities(intent, 0);
                boolean isIntentSafe = activities.size() > 0;
                if(!isIntentSafe)
                {
                    Toast.makeText(IntentFilterActivity.this,"No Match Activity",Toast.LENGTH_SHORT).show();
                    return;
                }


                startActivity(intent);
            }
        });

        ((Button) findViewById(R.id.buttonSHPP)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent();
                intent.setData(Uri.parse("ichanging://www.ichanging.org:1234/test"));

                PackageManager packageManager = getPackageManager();
                List<ResolveInfo> activities = packageManager.queryIntentActivities(intent, 0);
                boolean isIntentSafe = activities.size() > 0;
                if(!isIntentSafe)
                {
                    Toast.makeText(IntentFilterActivity.this,"No Match Activity",Toast.LENGTH_SHORT).show();
                    return;
                }


                startActivity(intent);
            }
        });

        ((Button) findViewById(R.id.buttonHPPM)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent();
                intent.setDataAndType(Uri.parse("ichanging://www.ichanging.org:1234/test"), "abc/xyz");

                PackageManager packageManager = getPackageManager();
                List<ResolveInfo> activities = packageManager.queryIntentActivities(intent, 0);
                boolean isIntentSafe = activities.size() > 0;
                if(!isIntentSafe)
                {
                    Toast.makeText(IntentFilterActivity.this,"No Match Activity",Toast.LENGTH_SHORT).show();
                    return;
                }

                startActivity(intent);
            }
        });
    }
}
