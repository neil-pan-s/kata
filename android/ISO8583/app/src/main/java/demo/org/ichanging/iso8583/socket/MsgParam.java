package demo.org.ichanging.iso8583.socket;

import demo.org.ichanging.iso8583.data.MsgEntity;

public class MsgParam {
	
	private MsgEntity mMsgEntity;
	
	public void setMsgEntity(MsgEntity entity){
		this.mMsgEntity = entity;
	}
	
	public MsgEntity getMsgEntity(){
		return mMsgEntity;
	}

}
