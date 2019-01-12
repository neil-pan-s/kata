package demo.org.ichanging.iso8583.socket;

/** 消息发送请求 */
public class MsgRequest {

    private MsgParam mParam;
	private RequestCallback mCallBack;

	public MsgRequest(MsgParam param, RequestCallback callBack){
		this.mParam = param;
		this.mCallBack = callBack;
	}
	
	public RequestCallback getSendCallBack() {
		return mCallBack;
	}

	public void setCallBack(RequestCallback callBack) {
		this.mCallBack = callBack;
	}

	public void setMsgParam(MsgParam param){
		this.mParam = param;
	}
	
	public MsgParam getMsgParam(){
		return mParam;
	}

    public interface RequestCallback{

        void onRecvMsg(MsgParam param);

        void onError(int errCode);
    }

}
