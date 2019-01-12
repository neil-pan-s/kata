package demo.org.ichanging.myapplication;

import android.content.Intent;
import android.test.ActivityInstrumentationTestCase2;
import android.test.TouchUtils;
import android.test.suitebuilder.annotation.MediumTest;
import android.test.suitebuilder.annotation.SmallTest;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

/**
 * Created by ChangingP on 2016/4/6.
 * Android Instrumentation框架适用于创建应用程序中UI部件的白盒测试
 * 测试程序可以获得UI线程的对象，但是如果它尝试改变UI线程对象的值，会得到WrongThreadException错误。
 */
public class MainActivityTest extends ActivityInstrumentationTestCase2<MainActivity> {

    private MainActivity mActivity;
    private TextView mText;
    private Button mButton;

    public MainActivityTest()
    {
        super(MainActivity.class);
    }


//    通常在setUp()方法中，我们应该:
//        为setUp() 调用父类构造函数，这是JUnit要求的。
//        初始化测试数据集的状态，具体而言：
//        定义保存测试数据及状态的实例变量
//        创建并保存正在测试的Activity的引用实例。
//        获得想要测试的Activity中任何UI组件的引用。

    @Override
    protected void setUp() throws Exception {
        super.setUp();

        //把touch mode设置为真可以防止在执行编写的测试方法时，人为的UI操作获取到控件的焦点
        setActivityInitialTouchMode(true);

        mActivity = getActivity();

        mButton = (Button) mActivity.findViewById(R.id.button);
        mText = (TextView) mActivity.findViewById(R.id.textView);
    }


    //如果测试方法只需要几毫秒的时间，那么它应该被标记为@SmallTest
    //长时间运行的测试（100毫秒或更多）通常被标记为@MediumTest或@LargeTest

    @MediumTest
    public void testPreconditions() {
        assertNotNull("mActivity is null", mActivity);
        assertNotNull("mText is null",mText);
    }

    @MediumTest
    public void testTextView() {
        final String expected = "Hello World!";
        final String actual = mText.getText().toString();
        assertEquals(expected, actual);
    }

    @MediumTest
    public void testClickMeButton_clickButtonAndExpectInfoText() {

        //模拟点击
        TouchUtils.clickView(this, mButton);
        //验证是否可见
        assertTrue(View.INVISIBLE == mText.getVisibility());
    }

    @SmallTest
    public void testMyApplication()
    {
        assertNotNull("MyApplication.getContext() is null", MyApplication.getContext());

        //打印无效
        System.out.println("Get Context Succ\n" + MyApplication.getContext().toString());
    }


}
