package demo.org.ichanging.jni;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        JniHello j = new JniHello();

        j.hello();
        j.testArguments(new String("Hello Dog"),1024,false);

        Toast.makeText(this,
                "testReturnInt:" + j.testReturnInt() +
                "\ntestReturnBool:" + j.testReturnBool() +
                "\ntestReturnString:" + j.testReturnString()
        ,Toast.LENGTH_LONG).show();
    }
}
