package demo.org.ichanging.myapplication;

import android.content.Intent;
import android.test.ActivityUnitTestCase;
import android.test.suitebuilder.annotation.MediumTest;
import android.widget.Button;

/**
 * Created by ChangingP on 2016/4/6.
 * ActiviUnitTestCase类提供对于单个Activity进行分离测试的支持。
 * 要创建单元测试，我们的测试类应该继承自ActiviUnitTestCase。继承ActiviUnitTestCase的Activity不会被Android自动启动。
 *
 */
public class MainActivityIntentTest extends ActivityUnitTestCase<MainActivity> {

    private Intent mLaunchIntent;

    public MainActivityIntentTest() {
        super(MainActivity.class);
    }

    @Override
    protected void setUp() throws Exception {
        super.setUp();

        mLaunchIntent = new Intent(getInstrumentation().getTargetContext(), MainActivity.class);
        //startActivity(mLaunchIntent, null, null);

    }

//    单元测试目标可能包括:
//    验证当Button被按下时，启动的LaunchActivity是否正确
//    验证启动的Intent是否包含有效的数据
    @MediumTest
    public void testEmptyActivityWasLaunchedWithIntent() {

        //要单独启动Activity，我们需要显式的调用startActivity()方法，并传递一个Intent来启动我们的目标Activity
        startActivity(mLaunchIntent, null, null);

        final Button launchNextButton = (Button) getActivity().findViewById(R.id.launch_next_activity_button);

        //因为LaunchActivity是独立运行的，所以不可以使用TouchUtils库来操作UI。
        //如果要直接进行Button点击，我们可以调用performClick()方法
        launchNextButton.performClick();

        //验证启动的Intent是否包含有效的数据
        final Intent launchIntent = getStartedActivityIntent();
        assertNotNull("Intent was null", launchIntent);
//        assertTrue("isFinishCalled ", isFinishCalled());

        final String payload = launchIntent.getStringExtra("play_load_key");
        assertEquals("Payload is empty", "no", payload);
    }

}