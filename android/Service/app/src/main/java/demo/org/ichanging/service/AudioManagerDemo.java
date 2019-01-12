package demo.org.ichanging.service;

import android.app.Service;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.support.v4.app.ServiceCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class AudioManagerDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio_manager_demo);

        final AudioManager audioManager = (AudioManager) getSystemService(Service.AUDIO_SERVICE);

        findViewById(R.id.playBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                MediaPlayer mediaPlayer = MediaPlayer.create(AudioManagerDemo.this,R.raw.song);
                mediaPlayer.setLooping(true);
                mediaPlayer.start();
            }
        });


        findViewById(R.id.volumeUpBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //指定调节音乐的音频 增大音量 显示UI
                audioManager.adjustStreamVolume(AudioManager.STREAM_MUSIC,AudioManager.ADJUST_RAISE,AudioManager.FLAG_SHOW_UI);
            }
        });


        findViewById(R.id.volumeDownBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //指定调节音乐的音频 降低音量 显示UI
                audioManager.adjustStreamVolume(AudioManager.STREAM_MUSIC, AudioManager.ADJUST_LOWER, AudioManager.FLAG_SHOW_UI);
            }
        });
    }
}
