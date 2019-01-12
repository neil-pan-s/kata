package demo.org.ichanging.actionbar;

import android.app.Fragment;
import android.app.FragmentTransaction;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;

public class ActionBarDropDownDemo extends AppCompatActivity implements ActionBar.OnNavigationListener{

    private static final String SELECTED_ITEM = "selected_item";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_action_bar_drop_down_demo);

        final ActionBar actionBar = getSupportActionBar();
        actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_LIST);
        actionBar.setListNavigationCallbacks(
                new ArrayAdapter<String>(
                        this,android.R.layout.simple_list_item_1,android.R.id.text1,
                            new String[]{"Page 1","Page 2","Page 3"})
                ,this);


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
        outState.putInt(SELECTED_ITEM, getActionBar().getSelectedNavigationIndex());
    }

    @Override
    public boolean onNavigationItemSelected(int itemPosition, long itemId) {
        Fragment fragment = new DummyFragment();
        Bundle args = new Bundle();
        args.putInt(DummyFragment.ARG_SECTION_NUMBER,itemPosition+1);
        fragment.setArguments(args);
        FragmentTransaction fragmentTransaction = getFragmentManager().beginTransaction();
        fragmentTransaction.replace(R.id.container, fragment);
        fragmentTransaction.commit();
        return true;
    }
}
