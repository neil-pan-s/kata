package demo.org.ichanging.network;

import android.app.AlertDialog;
import android.content.Context;
import android.webkit.JavascriptInterface;
import android.widget.Toast;

/**
 * Created by ChangingP on 2016/4/5.
 */
public class HelloObject
{
    Context  mContext;
    HelloObject(Context c)
    {
        mContext = c;
    }

    @JavascriptInterface
    public  void showToast(String Msg)
    {
        Toast.makeText(mContext,Msg,Toast.LENGTH_SHORT).show();
    }

    @JavascriptInterface
    public  void showAlertDialog(String Title,String Msg)
    {
        new AlertDialog.Builder(mContext)
                .setTitle(Title)
                .setMessage(Msg)
                .setPositiveButton("ok",null)
                .create()
                .show();
    }
}
