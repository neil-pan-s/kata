package demo.org.ichanging.io;

import android.net.Uri;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import org.apache.http.util.EncodingUtils;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintStream;

public class FileDemo extends AppCompatActivity {


    Toast mToast;

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_file_demo);

            mToast = Toast.makeText(this,"",Toast.LENGTH_SHORT);

            //What the Fuck , No SD but HuaWeiPhone return true
            if(!isSdcardExist())
            {
                mToast.setText("No SDCard");
                mToast.show();
            }


            findViewById(R.id.button1).setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    String content = readRaw(R.raw.test);
                    mToast.setText(content);
                    mToast.show();
                }
            });

            findViewById(R.id.button2).setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    String content = readAssets("test.txt");
                    mToast.setText(content);
                    mToast.show();
                }
            });


            findViewById(R.id.button3).setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    String content = null;
                    try {
                        content = readFile("test.txt");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    mToast.setText(content);
                    mToast.show();
                }
            });

            findViewById(R.id.button4).setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    try {
                        writeFile("test.txt","Hello world - by writeFile");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            });

            findViewById(R.id.button5).setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    String content = null;

                    try {
                        content = readSdcardFile("test.txt");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }

                    mToast.setText(content);
                    mToast.show();
                }
            });


            findViewById(R.id.button6).setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    try {
                        writeSdcardFile("test.txt", "Hello world - by writeSdcardFile");
                    } catch (IOException e) {
                        e.printStackTrace();
                    }


                }
            });


        findViewById(R.id.button5).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String content = null;
                try {
                    content = readSDFile("test.txt");
                } catch (IOException e) {
                    e.printStackTrace();
                }
                mToast.setText(content);
                mToast.show();
            }
        });


        findViewById(R.id.button8).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    writeSDFile("test.txt", "Hello world - by writeSDFile");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });



        findViewById(R.id.button9).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String sdDirPath = "";

                boolean isExist = Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED);
                if(isExist)
                {
                    File sdDir = Environment.getExternalStorageDirectory();
                    try {
                        sdDirPath = sdDir.getCanonicalPath();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }

                    System.out.println("========　SD PATH: " + sdDirPath + "  ========");


                    String content = readLineFile(sdDirPath + "test.txt");
                    mToast.setText(content);
                    mToast.show();
                }else {
                    System.out.println("======== No SD ========");
                }

            }
        });

    }



    public String readLineFile(String absolutefilePath)
    {
        FileInputStream fis = null;

        try {
            fis = new FileInputStream(absolutefilePath);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        if(fis == null) return null;

        BufferedReader bufferReader = new BufferedReader(new InputStreamReader(fis));
        StringBuilder stringBuilder = new StringBuilder("");
        String line = null;

        try {

            while ((line = bufferReader.readLine()) != null)
            {
                System.out.println("[" + line + "]");

                stringBuilder.append(line);
            }

            bufferReader.close();

        } catch (IOException e) {
            e.printStackTrace();
        }

        return  stringBuilder.toString();

    }


    //读取 assets/raw 目录下文件
    //eg. fd = R.id.test
    private String readRaw(int fd)
    {
        String res = "";
        try{

            //得到资源中的Raw数据流s
            InputStream in = getResources().openRawResource(fd);

            //得到数据的大小
            int length = in.available();

            byte [] buffer = new byte[length];

            //读取数据
            in.read(buffer);

            //依raw 文件的编码类型选择合适的编码，如果不调整会乱码
            // Gradle 需添加 compile 'org.apache.httpcomponents:httpcore:4.4.4'
            res = EncodingUtils.getString(buffer, "UTF-8");

            //关闭
            in.close();

        }catch(Exception e){
            e.printStackTrace();
        }

        return res;
    }


    private String readAssets(String fileName)
    {
        String res = "";
        try{

            //得到资源中的数据流
            InputStream in = getResources().getAssets().open(fileName);

            //得到数据的大小
            int length = in.available();

            byte [] buffer = new byte[length];

            //读取数据
            in.read(buffer);

            //依raw 文件的编码类型选择合适的编码，如果不调整会乱码
            // Gradle 需添加 compile 'org.apache.httpcomponents:httpcore:4.4.4'
            res = EncodingUtils.getString(buffer, "UTF-8");

            //关闭
            in.close();

        }catch(Exception e){
            e.printStackTrace();
        }

        return res;
    }

    //写/data/data/<应用程序名>目录上的文件数据
    public void writeFile(String fileName,String writestr) throws IOException{
        try{

            FileOutputStream fout =openFileOutput(fileName, MODE_PRIVATE);

            byte [] bytes = writestr.getBytes();

            fout.write(bytes);

            fout.close();
        }

        catch(Exception e){
            e.printStackTrace();
        }
    }

    //读/data/data/<应用程序名>目录上的文件数据
    public String readFile(String fileName) throws IOException {
        String res="";
        try{
            FileInputStream fin = openFileInput(fileName);
            int length = fin.available();
            byte [] buffer = new byte[length];
            fin.read(buffer);
            res = EncodingUtils.getString(buffer, "UTF-8");
            fin.close();
        }
        catch(Exception e){
            e.printStackTrace();
        }
        return res;

    }


    // SD = /mnt/sdcard/


    private boolean isSdcardExist()
    {
        String sdDirPath = "";


        boolean isExist = Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED);
        if(isExist)
        {
            File sdDir = Environment.getExternalStorageDirectory();
            try {
                sdDirPath = sdDir.getCanonicalPath();
            } catch (IOException e) {
                e.printStackTrace();
            }

            System.out.println("========　SD PATH: " + sdDirPath + "  ========");
        }

        return isExist;
    }


    //写数据到SD中的文件
    public void writeSdcardFile(String fileName,String write_str) throws IOException{

        try{

            FileOutputStream fout = new FileOutputStream(fileName);
            byte [] bytes = write_str.getBytes();

            fout.write(bytes);
            fout.close();
        }

        catch(Exception e){
            e.printStackTrace();
        }
    }


    //读SD中的文件
    public String readSdcardFile(String fileName) throws IOException{

        String res="";

        try{
            FileInputStream fin = new FileInputStream(fileName);

            int length = fin.available();

            byte [] buffer = new byte[length];
            fin.read(buffer);

            res = EncodingUtils.getString(buffer, "UTF-8");

            fin.close();
        }

        catch(Exception e){
            e.printStackTrace();
        }
        return res;
    }

//    String Name = File.getName();  //获得文件或文件夹的名称：
//    String parentPath = File.getParent();  //获得文件或文件夹的父目录
//    String path = File.getAbsoultePath();//绝对路经
//    String path = File.getPath();//相对路经
//    File.createNewFile();//建立文件
//    File.mkDir(); //建立文件夹
//    File.isDirectory(); //判断是文件或文件夹
//    File[] files = File.listFiles();  //列出文件夹下的所有文件和文件夹名
//    File.renameTo(dest);  //修改文件夹和文件名
//    File.delete();  //删除文件夹或文件

    //使用File类读SD文件
    public String readSDFile(String fileName) throws IOException {

        String res = "";

        File file = new File(fileName);

        FileInputStream fis = new FileInputStream(file);

        int length = fis.available();

        byte [] buffer = new byte[length];
        fis.read(buffer);

        res = EncodingUtils.getString(buffer, "UTF-8");

        fis.close();
        return res;
    }

    //使用File类写SD文件
    public void writeSDFile(String fileName, String write_str) throws IOException{

        File file = new File(fileName);

        FileOutputStream fos = new FileOutputStream(file);

        byte [] bytes = write_str.getBytes();

        fos.write(bytes);

        fos.close();
    }




}
