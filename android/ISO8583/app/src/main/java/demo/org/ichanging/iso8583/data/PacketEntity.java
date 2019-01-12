
package demo.org.ichanging.iso8583.data;

import demo.org.ichanging.iso8583.config.Config;

public class PacketEntity extends MsgEntity {
	
	/** packet0800 报文格式: 2字节报文长度 + 5字节 TPDU + 6字节报文头 + 2字节消息类型 + 16字节位图 + 报文数据域 */

	//报文类型
	private static final int type = TYPE_PACKET;

	//2字节报文长度
	public byte[] p_len;

	//5字节 tpdu
	public byte[] p_tpdu;

	//报文数据域  6字节报文头 + 2字节消息类型 + 16字节位图 + 报文数据域
	public byte[] p_fileds;

	//拼接上 tdpu 和 报文长度
	public byte[] packet()
	{
		if(p_fileds == null) return null;

		data = new byte[p_fileds.length + 5 + 2];
		byte[] p_tpdu = Config.CONNET_TPDU.getBytes();
		byte[] p_len = new byte[2];

		//拼接TPDU 预留两字节报文长度
		System.arraycopy(data,2,p_tpdu,0,5);
		//拼接数据域
		System.arraycopy(data,7,p_fileds,0,p_fileds.length);

		//更新报文长度
		int len = data.length - 2;
		data[0] = (byte) (len / 256);
		data[1] = (byte) (len % 256);

		p_len[0] = data[0];
		p_len[1] = data[1];

		return data;
	}

	//剥离 tdpu 和 报文长度
	public byte[] unpacket()
	{
		byte[] p_len = new byte[2];

		p_len[0] = data[0];
		p_len[1] = data[1];

		//报文长度
		int len = p_len[0]*256 + p_len[1];
		p_fileds = new byte[len-5];

		//取 TPDU
		System.arraycopy(p_tpdu,0,data,2,5);
		//取 数据域
		System.arraycopy(p_fileds,0,data,7,len - 5);

		return p_fileds;
	}

}
