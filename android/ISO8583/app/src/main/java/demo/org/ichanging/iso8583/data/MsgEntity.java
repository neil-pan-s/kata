
package demo.org.ichanging.iso8583.data;

import demo.org.ichanging.iso8583.config.Config;
import demo.org.ichanging.iso8583.util.AtomicIntegerUtil;

public class MsgEntity {

	public static final int TYPE_MSG = 1;
	public static final int TYPE_PACKET = 2;
	public static final int TYPE_FILE = 2;

    //报文类型
    private static final int type = TYPE_MSG;

	//报文唯一ID
	private int id= AtomicIntegerUtil.getIncrementID();

    //是否为发送数据
    public boolean isSend;
	
	//数据内容
	public byte[] data;
	
	public int getId() {
		return id;
	}

    @Override
    public String toString() {

        String format = "Msg - " +
                "[ID = " + id + "] - " +
                "[ Length = " + (data == null ? 0 : data.length) +"] - " +
                "[ isSend = " + isSend + "] - " +
                "[" + (data == null ? null : new String(data)) +"]";

        return format;
    }
}
