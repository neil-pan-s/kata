package demo.org.ichanging.iso8583.socket;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.net.SocketException;

import android.text.TextUtils;
import android.util.Log;

import demo.org.ichanging.iso8583.data.MsgEntity;
import demo.org.ichanging.iso8583.data.PacketEntity;
import demo.org.ichanging.iso8583.util.CommonUtil;
import demo.org.ichanging.iso8583.socket.SocketManager.SocketCallback;

import de.greenrobot.event.EventBus;

/** 双通道通信（接收和发送在不同的线程）*/
public class MsgReceiveHandler extends Thread {

	private static final String TAG = MsgReceiveHandler.class.getSimpleName();

	InputStream mInputString = null;
	DataInputStream mDataInputStream = null;

	private Socket mSocket;

	public MsgReceiveHandler(Socket socket) {
		this.mSocket = socket;
	}

	public void run() {

		try {
			mInputString = mSocket.getInputStream();
			// 1、访问Socket对象的getInputStream方法取得客户端发送过来的数据流
			mDataInputStream = new DataInputStream(new BufferedInputStream(
					mInputString));

			while (true) {

				try {
					Thread.sleep(300);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				
				if (mSocket == null || mDataInputStream == null) {
					return;
				}

                doMsgReceive(mDataInputStream);
            }

		} catch (SocketException e1) {
			e1.printStackTrace();
		} catch (IOException e1) {
			e1.printStackTrace();
		}

	}

	/**
	 * 接收信息
     *
     * TODO: 未处理接收超时和异常 + 通知上层应用
     *
	 * @param dis
	 * @throws IOException
	 */
	private void doMsgReceive(DataInputStream dis) throws IOException {
        String msg = null;
        byte[] header = new byte[8];

        Log.i(TAG, "before readLength");

        //读取两字节报文长度
        mDataInputStream.read(header, 0, 2);

        int msgLen = header[0] * 256 + header[1];

        Log.i(TAG, "run() -> len: " + msgLen);

        Log.i(TAG, "after readLength");
        int length = msgLen;
        Log.i(TAG, "doMsgReceive() -> length: " + length);

        byte[] buffer = new byte[length];
        int ret = dis.read(buffer, 0, buffer.length);
        if (ret == length) {
            msg = new String(buffer);
            Log.i(TAG, "doMsgReceive() -> msg: " + msg);
            if (!TextUtils.isEmpty(msg.trim())) {
                MsgEntity entity = new MsgEntity();
                entity.data = msg.getBytes();
                MsgParam msgParam = new MsgParam();
                msgParam.setMsgEntity(entity);

                //通知上层应用
            }
        }

	}
}
