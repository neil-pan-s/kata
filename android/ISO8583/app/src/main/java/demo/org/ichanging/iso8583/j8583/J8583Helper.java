package demo.org.ichanging.iso8583.j8583;

import android.content.Context;
import android.os.Message;

import com.solab.iso8583.IsoMessage;
import com.solab.iso8583.MessageFactory;
import com.solab.iso8583.util.HexCodec;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;

import de.greenrobot.event.EventBus;
import demo.org.ichanging.iso8583.data.MsgEntity;
import demo.org.ichanging.iso8583.data.PacketEntity;
import demo.org.ichanging.iso8583.socket.MsgParam;
import demo.org.ichanging.iso8583.socket.MsgRequest;
import demo.org.ichanging.iso8583.socket.RequestQueueManager;
import demo.org.ichanging.iso8583.socket.SocketManager;
import demo.org.ichanging.iso8583.util.LogUtil;

/**
 * Created by ChangingP on 2016/4/10.
 */
public class J8583Helper {

    private static final String TAG = J8583Helper.class.getSimpleName();
    private MessageFactory<IsoMessage> mMsgFactory;
    private Context mContext;

    public J8583Helper(Context context)
    {
        //初始化8583
        mMsgFactory = new MessageFactory<IsoMessage>();
        mMsgFactory.setCharacterEncoding("UTF-8");

        mContext = context;
    }

    /**
     * 从xml模板中打包
     * 此报文不包括 2字节报文长度 和 TPDU
     *
     * @param xmlPath xmlPath 路径 目前仅支持 res同级目录 resources获取xml
     * @param msgCode 消息类型 eg.0x200,0x800
     *
     */
    public IsoMessage packetFromXML(String xmlPath,int msgCode)
    {

        try {
            mMsgFactory.setConfigPath(xmlPath);
        } catch (IOException e) {
            e.printStackTrace();
        }

        IsoMessage iosMsg = mMsgFactory.newMessage(msgCode);
        iosMsg.setBinary(true);
        iosMsg.setBinaryBitmap(true);
        //设置报文头为16进制
        iosMsg.setIsoHeader(new String(HexCodec.hexDecode(iosMsg.getIsoHeader())));
        iosMsg.setForceSecondaryBitmap(false);

        byte[] buf = iosMsg.writeData();

        LogUtil.i(TAG, "packetFromXML - [" + HexCodec.hexEncode(buf, 0, buf.length) + "]");

        return iosMsg;
    }

    /**
     * 解包
     *
     * @param xmlPath xmlPath 路径 目前仅支持 res同级目录 resources获取xml
     * @param packet  报文数据 此报文不包括 2字节报文长度 和 TPDU
     * @param msgCode 消息类型 eg.0x200,0x800
     *
     */
    public IsoMessage unpacket(String xmlPath,int msgCode,byte[] packet)
    {
        IsoMessage iosMsg = null;

        //报文头为8字节 16进制
        try {
            iosMsg = mMsgFactory.parseMessage(packet, mMsgFactory.getIsoHeader(msgCode).length()/2);
        } catch (ParseException e) {
            e.printStackTrace();
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }

        LogUtil.i(TAG,"unpacket - [" + iosMsg.debugString() + "]");

        return iosMsg;
    }

    /*
     * TODO: 增加网络处理 和 重连处理
     */
    public void connectServer() {
        SocketManager.getInstance().startAsyncSocket("J8583Helper");
    }

    /**
     * 发送报文
     *
     * @param iosMsg ISO报文数据
     */
    public void sendPacket(IsoMessage iosMsg) {

        PacketEntity entity = new PacketEntity();

        entity.p_fileds = iosMsg.writeData();
        byte[] buf= entity.packet();

        LogUtil.i(TAG, "sendPacket - [" + HexCodec.hexEncode(buf, 0, buf.length) + "]");

        MsgParam param = new MsgParam();
        param.setMsgEntity(entity);

        //发送通知
        EventBus.getDefault().post(entity);

        MsgRequest request = new MsgRequest(param,
                new MsgRequest.RequestCallback() {

                    @Override
                    public void onRecvMsg(MsgParam param) {

                    }

                    @Override
                    public void onError(int errCode) {

                    }
                });

        RequestQueueManager.getInstance().push(request);
    }
}
