package demo.org.ichanging.iso8583;

import demo.org.ichanging.iso8583.config.Config;
import demo.org.ichanging.iso8583.util.ToastUtil;

import android.app.Activity;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.view.View;
import android.widget.EditText;

public class SettingActivity extends AppCompatActivity {
	
	private EditText et_ip;
	private EditText et_port;
	private EditText et_tpdu;


	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.setting);
		
		et_ip = (EditText) findViewById(R.id.et_ip);
		et_port = (EditText) findViewById(R.id.et_port);
        et_tpdu = (EditText) findViewById(R.id.et_tpdu);
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		
		et_ip.setText(Config.CONNET_IP);
		et_port.setText(Config.CONNET_PORT + "");
        et_tpdu.setText(Config.CONNET_TPDU + "");

    }
	
	public void onclickHandler(View view){
		if(commit()){
			finish();
		}
	}
	
	public boolean commit(){
		String ip = et_ip.getText().toString();
		String temp_port = et_port.getText().toString();
        String tpdu = et_tpdu.getText().toString();

        if(TextUtils.isEmpty(ip)){
			ToastUtil.getInstance().toast("server ip address is null");
			return false;
		}
		
		
		if(TextUtils.isEmpty(temp_port)){
			ToastUtil.getInstance().toast("server port is null");
			return false;
		}

        if(TextUtils.isEmpty(tpdu)){
            ToastUtil.getInstance().toast("server tpdu is null");
            return false;
        }


        int port;
		
		try {
			port = Integer.parseInt(temp_port);
		} catch (NumberFormatException e) {
			ToastUtil.getInstance().toast("server port must be number");
			return false;
		}
		
		Config.resetConncet(ip, port);
        Config.resetTPDU(tpdu);
		
		return true;
	}
	
	@Override
	public void onBackPressed() {
		if(commit()){
			super.onBackPressed();
		}
	}

}
