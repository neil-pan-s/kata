package demo.org.ichanging.resource;

import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.media.MediaPlayer;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import junit.framework.Assert;

import java.io.IOException;

public class Mp3PlayDemo extends AppCompatActivity {

    MediaPlayer mediaPlayer1 = null;
    MediaPlayer mediaPlayer2 = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mp3_play_demo);

        mediaPlayer1 = MediaPlayer.create(this,R.raw.sound);

        AssetManager assetManager = getAssets();
        try
        {
            AssetFileDescriptor afd_sound = assetManager.openFd("sound.mp3");
            mediaPlayer2 = new MediaPlayer();
            mediaPlayer2.setDataSource(afd_sound.getFileDescriptor());
            mediaPlayer2.prepare();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }

        findViewById(R.id.rowButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mediaPlayer1.start();
            }
        });

        findViewById(R.id.assetsButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mediaPlayer2.start();
            }
        });
    }
}
