package demo.org.ichanging.iso8583.socket;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketException;

import demo.org.ichanging.iso8583.config.Config;

/**
 * Created by ChangingP on 2016/4/10.
 */

public class SyncSocket extends Thread{

    public SyncSocket(){
    }

    @Override
    public void run() {
        try {
            Socket socket = new Socket();
            socket.connect(new InetSocketAddress(Config.CONNET_IP,
                    Config.CONNET_PORT), 5000);
            socket.setKeepAlive(true);

            new MsgReceiveHandler(socket).start();
            new MsgSendHandler(socket).start();

        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}