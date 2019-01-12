package demo.org.ichanging.intent;

import android.content.ComponentName;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

import java.util.Set;

public class EmptyDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_empty_demo);

        ComponentName componentName = getIntent().getComponent();

        String actionName = getIntent().getAction();
        Set<String> cates = getIntent().getCategories();
        Uri uri = getIntent().getData();
        String type = getIntent().getType();

        Toast.makeText(this,
                "Pkg Name:" + componentName.getPackageName() +
                "\n Class Name:" + componentName.getClassName() +
                "\n Action Name:" + actionName +
                "\n Cates Name:" + cates +
                "\n Data: " + uri +
                "\n Type: " + type
                ,Toast.LENGTH_LONG).show();

    }
}
