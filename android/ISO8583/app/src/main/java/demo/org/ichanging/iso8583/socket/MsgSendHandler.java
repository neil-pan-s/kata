package demo.org.ichanging.iso8583.socket;

import java.io.BufferedOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.SocketException;

import android.text.TextUtils;
import android.util.Log;

import demo.org.ichanging.iso8583.data.MsgEntity;
import demo.org.ichanging.iso8583.socket.MsgRequest.RequestCallback;

public class MsgSendHandler extends Thread {

	private static final String TAG = MsgSendHandler.class.getSimpleName();

	private Socket mSocket;
	OutputStream mOutputString = null;
	DataOutputStream mDataOutputStream = null;
	
	/** 会话唯一标识 */
//	private String mKey;
	
	public MsgSendHandler(Socket socket) {
		this.mSocket = socket;
	}

	public void run() {

		try {
			mOutputString = mSocket.getOutputStream();
			mDataOutputStream = new DataOutputStream(new BufferedOutputStream(
					mOutputString));

			while (true) {

				try {
					Thread.sleep(300);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				
				MsgRequest request = RequestQueueManager.getInstance().poll();
				if(request == null){
					continue;
				}
				RequestCallback callback = request.getSendCallBack();
				MsgParam param = request.getMsgParam();
				MsgEntity entity = param.getMsgEntity();
				
				if(entity == null){
					continue;
				}
			
				doMsgSend((MsgEntity) entity, callback);
				
			}

		} catch (SocketException e1) {
			e1.printStackTrace();
		} catch (IOException e1) {
			e1.printStackTrace();
		}

	}

	
	
	/**
	 * 发送文本消息
     *
     * TODO: 未处理发送异常
     *
	 * @param entity
	 */
	private void doMsgSend(MsgEntity entity, RequestCallback callback) {
		if (mDataOutputStream == null || entity == null || TextUtils.isEmpty(entity.data.toString())) {
			return;
		}
		
		Log.i(TAG, "send to client: " + entity.data);
		try {
			
			byte[] buffer = entity.data;
			
			mDataOutputStream.write(buffer);
			mDataOutputStream.flush();

		} catch (IOException e) {
//			e.printStackTrace();

		}
	}

}
