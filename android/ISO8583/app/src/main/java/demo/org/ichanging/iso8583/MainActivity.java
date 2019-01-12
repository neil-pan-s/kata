package demo.org.ichanging.iso8583;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.math.BigInteger;
import java.net.URL;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.solab.iso8583.IsoMessage;
import com.solab.iso8583.IsoType;
import com.solab.iso8583.MessageFactory;
import com.solab.iso8583.codecs.BigIntBcdCodec;
import com.solab.iso8583.codecs.LongBcdCodec;
import com.solab.iso8583.util.HexCodec;

import demo.org.ichanging.iso8583.data.MsgEntity;
import demo.org.ichanging.iso8583.data.PacketEntity;
import demo.org.ichanging.iso8583.j8583.J8583Helper;
import demo.org.ichanging.iso8583.socket.MsgParam;
import demo.org.ichanging.iso8583.socket.MsgRequest;
import demo.org.ichanging.iso8583.socket.RequestQueueManager;
import demo.org.ichanging.iso8583.socket.SocketManager;
import demo.org.ichanging.iso8583.util.CommonUtil;

import de.greenrobot.event.EventBus;
import demo.org.ichanging.iso8583.util.LogUtil;

public class MainActivity extends AppCompatActivity {

    private final byte[] PACKET_HEADER = HexCodec.hexDecode("603100011001");

	private static final String TAG = MainActivity.class.getSimpleName();
    private J8583Helper j8583Helper;

    TextView mText = null;

	private Handler mHandler = new Handler() {

		public void handleMessage(android.os.Message msg) {
			MsgEntity entity = (MsgEntity) msg.obj;
			if (entity != null) {
                LogUtil.i(TAG,"\n\nPacket:" + entity.toString());
                mText.append("\n\nPacket:" + entity.toString());
			}
		};
	};

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		getWindow().setSoftInputMode(
                WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);

        j8583Helper = new J8583Helper(this);

        mText = (TextView) findViewById(R.id.textView);
        findViewById(R.id.loginBtn).setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                packetLogin();
            }
        });

    }

    public void packetLogin() {

        final BigIntBcdCodec bigintCodec = new BigIntBcdCodec();
        final LongBcdCodec longCodec = new LongBcdCodec();
        final BigInteger b29 = new BigInteger("12345678901234567890123456789");

//        IsoMessage m1 = new IsoMessage();
//        m1.setType(0x200);
//        m1.setBinary(true);
//        m1.setBinaryBitmap(true);
//        m1.setIsoHeader(new String(PACKET_HEADER));
//
//        m1.setValue(2, 1234567890l, longCodec, IsoType.LLBIN, 0);
//        m1.setValue(3, b29, bigintCodec, IsoType.LLBIN, 0);
//        byte[] buf = m1.writeData();
//        System.out.println("MENSAJE: " + HexCodec.hexEncode(buf, 0, buf.length));

        IsoMessage isoMsg = j8583Helper.packetFromXML("packet0800.xml",0x800);
        j8583Helper.sendPacket(isoMsg);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.menu, menu);
		return true;
	}

	@Override
    public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case R.id.setting:
			Intent intent = new Intent(this, SettingActivity.class);
			startActivity(intent);
			return true;
		case R.id.connect:
            j8583Helper.connectServer();
			return true;

		default:
			return super.onOptionsItemSelected(item);
		}
	}

	@Override
	protected void onStart() {
		super.onStart();

		EventBus.getDefault().register(this);
	}

	@Override
	protected void onPause() {
		super.onPause();
	}

	@Override
	protected void onStop() {
		super.onStop();

		EventBus.getDefault().unregister(this);
	}

	/**
	 * 接收消息事件
	 * 
	 * @param entity
	 */
	public void onEvent(MsgEntity entity) {
		if (entity == null) {
			return;
		}

		Message msg = mHandler.obtainMessage();
		msg.obj = entity;
		mHandler.sendMessage(msg);
	}

}