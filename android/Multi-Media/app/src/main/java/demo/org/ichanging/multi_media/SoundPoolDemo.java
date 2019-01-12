package demo.org.ichanging.multi_media;

import android.media.AudioAttributes;
import android.media.SoundPool;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import java.util.HashMap;

public class SoundPoolDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sound_pool_demo);

        AudioAttributes attr = new AudioAttributes.Builder()
                .setUsage(AudioAttributes.USAGE_GAME)       //设置音效使用场景
                .setContentType(AudioAttributes.CONTENT_TYPE_MUSIC)  //设置音效类型
                .build();

        final SoundPool soundPool = new SoundPool.Builder()
                .setAudioAttributes(attr) //设置音效池属性
                .setMaxStreams(10)  //设置最大载入10个音频流
                .build();

        final HashMap<Integer, Integer> soundMap = new HashMap<>();
        soundMap.put(1, soundPool.load(this, R.raw.windows_balloon, 1));
        soundMap.put(2, soundPool.load(this, R.raw.windows_battery_critical, 1));
        soundMap.put(3, soundPool.load(this, R.raw.windows_battery_low, 1));
        soundMap.put(4, soundPool.load(this, R.raw.windows_critical_stop, 1));
        soundMap.put(5, soundPool.load(this, R.raw.windows_default, 1));

        View.OnClickListener listener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int i = 1;

                switch (v.getId())
                {
                    case R.id.button: i = 1; break;
                    case R.id.button2: i = 2; break;
                    case R.id.button3: i = 3; break;
                    case R.id.button4: i = 4; break;
                    case R.id.button5: i = 5; break;
                    default:break;
                }

                soundPool.play(soundMap.get(i),1,1,0,0,1);
            }
        };

        findViewById(R.id.button).setOnClickListener(listener);
        findViewById(R.id.button2).setOnClickListener(listener);
        findViewById(R.id.button3).setOnClickListener(listener);
        findViewById(R.id.button4).setOnClickListener(listener);
        findViewById(R.id.button5).setOnClickListener(listener);
    }


}
