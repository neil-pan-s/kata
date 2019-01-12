package demo.org.ichanging.multi_media;

import android.media.MediaPlayer;
import android.media.MediaRecorder;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import java.io.File;
import java.io.IOException;

public class MediaRecorderDemo extends AppCompatActivity {

    File recordFile = null;
    MediaRecorder mRecorder;
    MediaPlayer mPlayer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_media_recorder_demo);

        mPlayer = new MediaPlayer();

        try {
            recordFile = new File(getCacheDir().getCanonicalPath() + "/record.amr");
        } catch (IOException e) {
            e.printStackTrace();
        }

        findViewById(R.id.button6).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {

                    mRecorder = new MediaRecorder();
                    mRecorder.setAudioSource(MediaRecorder.AudioSource.MIC); // 设置声音来源
                    mRecorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP); //设置声音的输出格式 必须在编码格式前设置
                    mRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB); //设置声音编码格式
                    mRecorder.setOutputFile(recordFile.getAbsolutePath());

                    mRecorder.prepare();
                    mRecorder.start();

                    Toast.makeText(MediaRecorderDemo.this,"Please Speak Now",Toast.LENGTH_LONG).show();

                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        findViewById(R.id.button7).setOnClickListener(new View.OnClickListener() {
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
                    try {
                        mPlayer.setDataSource(recordFile.getCanonicalPath());//获取绝对路径来播放音频
                        mPlayer.prepare();
                        mPlayer.start();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
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
