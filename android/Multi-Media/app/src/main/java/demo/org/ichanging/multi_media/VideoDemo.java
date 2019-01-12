package demo.org.ichanging.multi_media;

import android.media.MediaPlayer;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.MediaController;
import android.widget.VideoView;

import java.io.File;

public class VideoDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_video_demo);

        final VideoView videoView = (VideoView) findViewById(R.id.videoView);
        MediaController mediaController = new MediaController(this);
        mediaController.setMediaPlayer(videoView);
        //mediaController.hide();

        //Huawei movie
        File video = new File("/system/media/Pre-loaded/Movies/Honor.mp4");

        if(video.exists())
        {
            videoView.setVideoPath(video.getAbsolutePath());
            videoView.setMediaController(mediaController);

            //设置循环播放
            videoView.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
                @Override
                public void onPrepared(MediaPlayer mp) {
                    mp.setLooping(true);
                    mp.start();
                }
            });

            videoView.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
                @Override
                public void onCompletion(MediaPlayer mp) {
                    videoView.start();
                }
            });

            videoView.requestFocus();
            videoView.start();
        }

    }
}
