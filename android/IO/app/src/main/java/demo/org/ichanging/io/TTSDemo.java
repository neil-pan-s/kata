package demo.org.ichanging.io;

import android.speech.tts.TextToSpeech;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Locale;

public class TTSDemo extends AppCompatActivity {

    TextToSpeech tts;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tts_demo);

        tts = new TextToSpeech(this, new TextToSpeech.OnInitListener() {
            @Override
            public void onInit(int status) {
                if(status == TextToSpeech.SUCCESS)
                {
                    //Unsupport Chinese Now !!
                    //int result = tts.setLanguage(Locale.CHINESE);
                    int result = tts.setLanguage(Locale.US);

                    if(result != TextToSpeech.LANG_COUNTRY_AVAILABLE && result != TextToSpeech.LANG_AVAILABLE)
                    {
                        Toast.makeText(TTSDemo.this,"TTS Language Unsupport",Toast.LENGTH_SHORT).show();
                    }
                }
            }
        });

        findViewById(R.id.buttonCN).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String words = ((TextView) findViewById(R.id.textViewCN)).getText().toString();
                tts.speak(words,TextToSpeech.QUEUE_FLUSH,null,"__cn__");
            }
        });


        findViewById(R.id.buttonUS).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String words = ((TextView) findViewById(R.id.textViewUS)).getText().toString();
                tts.speak(words,TextToSpeech.QUEUE_FLUSH,null,"__US__");
            }
        });
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        if(tts != null)
        {
            tts.shutdown();
        }
    }
}
