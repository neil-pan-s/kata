package demo.org.ichanging.iso8583.config;

import demo.org.ichanging.iso8583.util.SharedPreUtil;

public class Config {
	
	public static final String KEY_FIRST = "key_first";
	
	public static final String KEY_IP = "key_ip";
	public static final String KEY_PORT = "key_port";
	public static final String KEY_TPDU = "key_tpdu";

	public static int CONNET_PORT = 5013;
	public static String CONNET_IP = "172.22.103.109";
	public static String CONNET_TPDU = "6000050000";
	
	/**
	 * app启动时初始化服务器信息
	 */
	public static void initConnect(){
		SharedPreUtil sp = SharedPreUtil.getInstance();
		if(sp.getBoolean(KEY_FIRST, true)){
			sp.putBoolean(KEY_FIRST, false);
			sp.putString(KEY_IP, CONNET_IP);
			sp.putInt(KEY_PORT, CONNET_PORT);
			sp.putString(KEY_TPDU, CONNET_TPDU);
		}else{
			Config.CONNET_IP = sp.getString(KEY_IP);
			Config.CONNET_PORT = sp.getInt(KEY_PORT);
			Config.CONNET_TPDU = sp.getString(KEY_TPDU);
		}
	}
	
	/**
	 * 重置服务器信息
	 * @param ip
	 * @param port
	 */
	public static void resetConncet(final String ip, final int port){
		Config.CONNET_IP = ip;
		Config.CONNET_PORT = port;
		SharedPreUtil sp = SharedPreUtil.getInstance();
		sp.putString(KEY_IP, CONNET_IP);
		sp.putInt(KEY_PORT, CONNET_PORT);
	}
	
	/**
	 * 设置TPDU
	 * @param tpdu
	 */
	public static void resetTPDU(final String tpdu){
		Config.CONNET_TPDU = tpdu;
		SharedPreUtil sp = SharedPreUtil.getInstance();
		sp.putString(KEY_TPDU, CONNET_TPDU);
	}

}
