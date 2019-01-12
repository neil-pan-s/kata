package demo.org.ichanging.menu;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

import org.w3c.dom.Text;

public class ContextMenuDemo extends AppCompatActivity {

    final int MENU1 = 0x111;
    final int MENU2 = 0x112;
    final int MENU3 = 0x113;

    private TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_context_menu_demo);

        textView = (TextView) findViewById(R.id.textview);
        //长按触发
        registerForContextMenu(textView);

    }

    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {

        menu.add(0,MENU1,0,"RED");
        menu.add(0,MENU2,0,"GREEN");
        menu.add(0, MENU3, 0, "BLUE");

        //menu.setGroupCheckable(0, true, true);
        menu.setHeaderTitle("选择背景色");

        //super.onCreateContextMenu(menu, v, menuInfo);
    }


    @Override
    public boolean onContextItemSelected(MenuItem item) {

        switch (item.getItemId())
        {
            case MENU1:
                item.setChecked(true);
                textView.setBackgroundColor(Color.RED);
                break;
            case MENU2:
                item.setChecked(true);
                textView.setBackgroundColor(Color.GREEN);
                break;
            case MENU3:
                item.setChecked(true);
                textView.setBackgroundColor(Color.BLUE);
                break;
        }

        return true;
    }


}
