package demo.org.ichanging.menu;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class XMLCustomMenuDemo extends AppCompatActivity {

    private TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_xmlcustom_menu_demo);

        textView = (TextView) findViewById(R.id.textView);
        registerForContextMenu(textView);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflator = new MenuInflater(this);
        inflator.inflate(R.menu.menu_demo, menu);

        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {
        MenuInflater inflater = new MenuInflater(this);
        inflater.inflate(R.menu.conetxt_menu, menu);
        //super.onCreateContextMenu(menu, v, menuInfo);
        menu.setHeaderTitle(R.string.bg_title);
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {

        switch (item.getItemId())
        {
            case R.id.red:
                item.setChecked(true);
                textView.setBackgroundColor(Color.RED);
                break;
            case R.id.green:
                item.setChecked(true);
                textView.setBackgroundColor(Color.GREEN);
                break;
            case R.id.blue:
                item.setChecked(true);
                textView.setBackgroundColor(Color.BLUE);
                break;
        }

        return true;
    }


    @Override
    public boolean onOptionsItemSelected(MenuItem mi)
    {
        switch(mi.getItemId())
        {
            case R.id.font_10:
                textView.setTextSize(10*2);
                break;
            case R.id.font_12:
                textView.setTextSize(12*2);
                break;
            case R.id.font_14:
                textView.setTextSize(14*2);
                break;
            case R.id.font_16:
                textView.setTextSize(16*2);
                break;
            case R.id.font_18:
                textView.setTextSize(18*2);
                break;

            case R.id.red_font:
                textView.setTextColor(Color.RED);
                break;
            case R.id.green_font:
                textView.setTextColor(Color.GREEN);
                break;
            case R.id.blue_font:
                textView.setTextColor(Color.BLUE);
                break;
            case R.id.plain_item:
                Toast.makeText(XMLCustomMenuDemo.this,"Common Menu", Toast.LENGTH_SHORT).show();
                break;
        }

        return true;
    }

}

