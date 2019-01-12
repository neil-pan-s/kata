package demo.org.ichanging.jni;

/**
 * Created by ChangingP on 2016/4/12.
 */
public class JniHello {

    public native void hello();

    public native int testReturnInt();
    public native boolean testReturnBool();
    public native String testReturnString();

    public native void testArguments(String str,int x,boolean t);

    static
    {
        System.loadLibrary("JniHello");
    }

    public static void main(String[] args)
    {

        new JniHello().hello();
    }

}
