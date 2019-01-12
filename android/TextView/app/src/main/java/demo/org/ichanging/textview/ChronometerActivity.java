package demo.org.ichanging.textview;

import android.os.SystemClock;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Chronometer;

import static android.widget.Chronometer.*;

public class ChronometerActivity extends AppCompatActivity
{
    Chronometer ch;
    Button btn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chronometer);

        ch = (Chronometer) findViewById(R.id.chronometer);
        btn = (Button) findViewById(R.id.button);

        btn.setOnClickListener(new OnClickListener()
                               {
                                   @Override
                                   public void onClick(View v) {
                                       ch.setBase(SystemClock.elapsedRealtime());
                                       ch.start();
                                       btn.setEnabled(false);
                                   }
                               }
        );

        ch.setOnChronometerTickListener ( new OnChronometerTickListener()
                                          {
                                              @Override
                                              public void onChronometerTick(Chronometer ch)
                                              {
                                                  if(SystemClock.elapsedRealtime() - ch.getBase() >  20 * 1000)
                                                  {
                                                      ch.stop();
                                                      btn.setEnabled(true);
                                                  }
                                              }
                                          }
        );
    }
}
