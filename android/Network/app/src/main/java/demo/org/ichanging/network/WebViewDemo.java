package demo.org.ichanging.network;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;

public class WebViewDemo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_web_view_demo);

        WebView webView = (WebView)findViewById(R.id.webView);

        //不跳转到系统浏览器
        webView.setWebViewClient(new WebViewClient() {
            @Override
            public boolean shouldOverrideUrlLoading(WebView view, String url) {

                return false;
            }
        });


        //webView.loadUrl("http://www.baidu.com");

        //载入本地html
        webView.loadUrl("file:///android_asset/index.html");
        WebSettings webSettings = webView.getSettings();
        //开启Javascript
        webSettings.setJavaScriptEnabled(true);
        //传递 Java对象 给 Javascipt 调用
        webView.addJavascriptInterface(new HelloObject(this),"HelloObject");
    }
}
