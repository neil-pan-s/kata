package demo.org.ichanging.multi_media;

import android.media.MediaPlayer;
import android.media.MediaRecorder;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.MediaController;
import android.widget.Toast;
import android.widget.VideoView;

import java.io.File;
import java.io.IOException;

public class VideoRecorderDemo extends AppCompatActivity {

    File recordFile = null;
    MediaRecorder mRecorder;
    SurfaceView sView;

    private boolean isRecording = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_video_recorder_demo);

        final VideoView videoView = (VideoView) findViewById(R.id.videoView1);
        final MediaController mediaController = new MediaController(this);
        mediaController.setMediaPlayer(videoView);
        //mediaController.hide();


        sView = (SurfaceView) findViewById(R.id.surfaceView);
        sView.getHolder().setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
        sView.getHolder().setFixedSize(320, 280);
        sView.getHolder().setKeepScreenOn(true);

        try {
            recordFile = new File(getCacheDir().getCanonicalPath() + "/record.mp4");
        } catch (IOException e) {
            e.printStackTrace();
        }

        findViewById(R.id.button8).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {

                    mRecorder = new MediaRecorder();
                    mRecorder.reset();
                    mRecorder.setAudioSource(MediaRecorder.AudioSource.MIC); // 设置声音来源
                    mRecorder.setVideoSource(MediaRecorder.VideoSource.CAMERA);
                    mRecorder.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
                    //设置视频的输出格式 必须在设置音频 视频编码格式前
                    mRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.DEFAULT);
                    mRecorder.setVideoEncoder(MediaRecorder.VideoEncoder.MPEG_4_SP);

                    //mRecorder.setVideoSize(320, 280); //cause error MediaRecorder: start failed: -19
                    mRecorder.setVideoFrameRate(4);

                    mRecorder.setOutputFile(recordFile.getAbsolutePath());
                    mRecorder.setPreviewDisplay(sView.getHolder().getSurface());
                    mRecorder.prepare();
                    mRecorder.start();

                    isRecording = true;

                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        findViewById(R.id.button9).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if(mRecorder != null)
                {
                    mRecorder.stop();
                    mRecorder.release();
                    mRecorder = null;
                }

                if(recordFile != null && recordFile.exists())
                {
                    videoView.setVideoPath(recordFile.getAbsolutePath());
                    videoView.setMediaController(mediaController);
                    videoView.requestFocus();
                    videoView.start();
                }

            }
        });
    }

    @Override
    protected void onDestroy() {

        if(mRecorder != null)
        {
            mRecorder.stop();
            mRecorder.release();
            mRecorder = null;
        }

        super.onDestroy();
    }
}
