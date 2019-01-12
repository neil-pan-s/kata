package demo.org.ichanging.configuration;

import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class ConfigurationDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_configuration_demo);

        Button btn = (Button) findViewById(R.id.button);

        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //横竖屏切换
                Configuration cfg = getResources().getConfiguration();
                if(cfg.orientation == Configuration.ORIENTATION_LANDSCAPE)
                {
                    ConfigurationDemo.this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
                }

                if(cfg.orientation == Configuration.ORIENTATION_PORTRAIT)
                {
                    ConfigurationDemo.this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
                }
            }
        });
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

        String screen = (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE) ? "横向屏幕" : "竖向屏幕";
        Toast.makeText(this,"Orientation: " + screen,Toast.LENGTH_SHORT).show();
    }
}
