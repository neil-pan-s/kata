package demo.org.ichanging.iso8583.socket;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketException;

import demo.org.ichanging.iso8583.config.Config;

/**  连接管理类 */
public class SocketManager{

    public static final int ERR_BASE = -1000;
    public static final int SOCKET_ERR_TIMEOUT = (ERR_BASE -1);
    public static final int SOCKET_ERR_CONNECT = (ERR_BASE -2);
    public static final int SOCKET_ERR_SEND    = (ERR_BASE -3);
    public static final int SOCKET_ERR_RECV    = (ERR_BASE -4);

    private static final SocketManager sINSTANCE = new SocketManager();

    public interface SocketCallback
    {

        void onConnect();

        void onDisconnect();

        void onSend();

        void onRecvMsg(MsgParam param);

        void onError(int errCode);
    }

	private SocketManager() {};

	public static SocketManager getInstance() {
		return sINSTANCE;
	}
	
	/**
	 * 启动一个异步socket
     * 全双工通信 异步socket 报文无需一应一答
     *
	 * @param key
	 */
	public void startAsyncSocket(String key){ new AsyncSocket().start(); }

    /**
     * 启动一个同步socket
     * 同步socket 报文一应一答模式
     *
     * @param key
     */
    public void startSyncSocket(String key){
        new SyncSocket().start();
    }

}
