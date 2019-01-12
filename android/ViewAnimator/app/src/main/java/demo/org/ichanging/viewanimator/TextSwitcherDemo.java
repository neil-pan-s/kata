package demo.org.ichanging.viewanimator;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextSwitcher;
import android.widget.TextView;
import android.widget.ViewSwitcher;

public class TextSwitcherDemo extends AppCompatActivity {

    TextSwitcher textSwitcher;

    String[] words = new String[]
            {
                "砍人王",
                "二老板",
                "大老板",
                "保留"
            };
    int wordsIndex = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_text_switcher_demo);

        textSwitcher = (TextSwitcher) findViewById(R.id.textSwitcher);
        textSwitcher.setFactory(new ViewSwitcher.ViewFactory() {
            @Override
            public View makeView() {

                TextView tv = new TextView(TextSwitcherDemo.this);
                tv.setTextSize(40);
                tv.setTextColor(Color.DKGRAY);
                return  tv;
            }
        });

        next(null);

    }

    public void next(View view)
    {
        textSwitcher.setText(words[wordsIndex++ % words.length]);
    }
}
