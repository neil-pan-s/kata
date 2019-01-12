package demo.org.ichanging.multi_media;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Environment;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.DateFormat;
import java.util.Calendar;
import java.util.Locale;

public class CameraDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera_demo);

        findViewById(R.id.button10).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                //调用camera app
                Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);

                // 指定开启系统相机的Action
                intent.setAction(MediaStore.ACTION_IMAGE_CAPTURE);
                intent.addCategory(Intent.CATEGORY_DEFAULT);

                startActivityForResult(intent, 0);
            }
        });


        findViewById(R.id.button11).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                try {
                    // 检测sd是否可用
                    if (!Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED))
                    {
                        Toast.makeText(CameraDemo.this,"No SDCard",Toast.LENGTH_SHORT).show();
                        return;
                    }

                    //需要确保此路径 camera可以访问
                    String fileName = getExternalCacheDir().getCanonicalPath() + "/shot.jpg";

                    //调用camera app
                    Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);

                    // 指定开启系统相机的Action
                    intent.setAction(MediaStore.ACTION_IMAGE_CAPTURE);
                    intent.addCategory(Intent.CATEGORY_DEFAULT);

                    // 根据文件地址创建文件
                    File file=new File(fileName);

                    // 把文件地址转换成Uri格式
                    Uri uri= Uri.fromFile(file);
                    // 设置系统相机拍摄照片完成后图片文件的存放地址
                    // 设置图片存放地址后 bundle.get("data") 不会返回缩略图
                    intent.putExtra(MediaStore.EXTRA_OUTPUT, uri);

                    startActivityForResult(intent, 1);

                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode == Activity.RESULT_OK) {

            //默认方法调用 camera
            if(requestCode == 0)
            {

                Bundle bundle = data.getExtras();

                //返回的是缩略图啊啊啊啊
                Bitmap bitmap = (Bitmap) bundle.get("data");// 获取相机返回的数据，并转换为Bitmap图片格式

                try {

                    String fileName = getCacheDir().getCanonicalPath() + "/shot.jpg";
                    FileOutputStream b = new FileOutputStream(fileName);
                    bitmap.compress(Bitmap.CompressFormat.JPEG, 100, b);// 把数据写入文件
                    b.flush();
                    b.close();

                    ((ImageView) findViewById(R.id.imageView)).setImageBitmap(bitmap);// 将图片显示在ImageView里

                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }


            }else if(requestCode == 1){
                //调用 camera 指定图片路径

                try {
                    String fileName = getExternalCacheDir().getCanonicalPath() + "/shot.jpg";
                    FileInputStream b = new FileInputStream(fileName);
                    Bitmap bitmap = BitmapFactory.decodeStream(b);
                    ((ImageView) findViewById(R.id.imageView)).setImageBitmap(bitmap);// 将图片显示在ImageView里

                } catch (IOException e) {
                    e.printStackTrace();
                }


            }


        } else {
            Toast.makeText(CameraDemo.this, "User Cancel", Toast.LENGTH_SHORT).show();
        }
    }
}
