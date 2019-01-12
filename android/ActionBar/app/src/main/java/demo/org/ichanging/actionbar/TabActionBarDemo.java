package demo.org.ichanging.actionbar;

import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentTransaction;
import android.os.Bundle;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;

public class TabActionBarDemo extends AppCompatActivity implements ActionBar.TabListener{

    private static final String SELECTED_ITEM = "selected_item";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tab_action_bar_demo);

        final ActionBar actionBar = getSupportActionBar();
        actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);
        actionBar.addTab(actionBar.newTab().setText("Page 1").setTabListener(this));
        actionBar.addTab(actionBar.newTab().setText("Page 2").setTabListener(this));
        actionBar.addTab(actionBar.newTab().setText("Page 3").setTabListener(this));

    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {

        if(savedInstanceState.containsKey(SELECTED_ITEM))
        {
            getActionBar().setSelectedNavigationItem(savedInstanceState.getInt(SELECTED_ITEM));
        }
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {

        outState.putInt(SELECTED_ITEM,getActionBar().getSelectedNavigationIndex());

    }

    @Override
    public void onTabUnselected(ActionBar.Tab tab, android.support.v4.app.FragmentTransaction ft) {

    }

    @Override
    public void onTabReselected(ActionBar.Tab tab, android.support.v4.app.FragmentTransaction ft) {

    }

    @Override
    public void onTabSelected(ActionBar.Tab tab, android.support.v4.app.FragmentTransaction ft) {
        Fragment fragment = new DummyFragment();
        Bundle args = new Bundle();
        args.putInt(DummyFragment.ARG_SECTION_NUMBER,tab.getPosition()+1);
        fragment.setArguments(args);
        FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
        fragmentTransaction.replace(R.id.container,fragment);
        fragmentTransaction.commit();
    }
}
