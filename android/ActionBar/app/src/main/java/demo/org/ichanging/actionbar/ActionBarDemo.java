package demo.org.ichanging.actionbar;

import android.content.Intent;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

public class ActionBarDemo extends AppCompatActivity {

    TextView textView;
    ActionBar actionBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_action_bar_demo);

        textView = (TextView) findViewById(R.id.textView);

        actionBar = getSupportActionBar();
        if(actionBar == null)
        {
            System.out.println(" ==================== ActionBar is NULL ====================");

            findViewById(R.id.button).setEnabled(false);
            findViewById(R.id.button2).setEnabled(false);
            return;
        }

        actionBar.setDisplayShowHomeEnabled(true);
        //actionBar.setHomeButtonEnabled(true);
        actionBar.setDefaultDisplayHomeAsUpEnabled(true);

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        MenuInflater inflater = new MenuInflater(this);
        inflater.inflate(R.menu.menu_main,menu);

        return super.onCreateOptionsMenu(menu);
    }

    public void showActionBar(View v)
    {
        actionBar.show();
    }

    public void hideActionBar(View v)
    {
        actionBar.hide();
    }


    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        switch (item.getItemId())
        {
            case R.id.plain_item:
                Intent intent = new Intent(this,EmptyDemo.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                startActivity(intent);
                break;
            default:break;
        }

        return true;
    }
}
