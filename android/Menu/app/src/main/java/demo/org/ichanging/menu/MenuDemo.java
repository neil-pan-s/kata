package demo.org.ichanging.menu;

import android.content.Intent;
import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.SubMenu;
import android.widget.EditText;
import android.widget.Toast;

public class MenuDemo extends AppCompatActivity {

    final int FONT_10 = 0x111;
    final int FONT_12 = 0x112;
    final int FONT_14 = 0x113;
    final int FONT_16 = 0x114;
    final int FONT_18 = 0x115;

    final int PLAIN_ITEM = 0x11b;
    final int FONT_RED = 0x116;
    final int FONT_BLUE = 0x117;
    final int FONT_GREEN = 0x118;
    private EditText edit;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu_demo);

        edit = (EditText) findViewById(R.id.editText);

    }

    @Override
    public  boolean onCreateOptionsMenu(Menu menu) {
        SubMenu fontMenu = menu.addSubMenu("字体大小");
//        fontMenu.setIcon(R.drawable.font);
//        fontMenu.setHeaderIcon(R.drawable.font);

        fontMenu.setHeaderTitle("选着字体大小");
        fontMenu.add(0, FONT_10, 0, "10号");
        fontMenu.add(0, FONT_12, 4, "12号");
        fontMenu.add(0, FONT_14, 3, "14号");
        fontMenu.add(0, FONT_16, 2, "16号");
        fontMenu.add(0, FONT_18, 1, "18号");

        //无效
        //MenuItem item_empty = menu.add("Go Empty");
        //item_empty.setIntent(new Intent(this, EmptyDemo.class));

        MenuItem item = menu.add(0, PLAIN_ITEM, 0, "普通项菜单");
        item.setOnMenuItemClickListener(new MenuItem.OnMenuItemClickListener() {
            @Override
            public boolean onMenuItemClick(MenuItem item) {

                Toast.makeText(MenuDemo.this,"Common Menu",Toast.LENGTH_SHORT).show();

                return true;
            }
        });

        SubMenu colorMenu = menu.addSubMenu("字体菜单");
//        colorMenu.setIcon(R.drawable.color);
//        colorMenu.setHeaderIcon(R.drawable.color);

        colorMenu.setHeaderTitle("选着文字大小");
        colorMenu.add(0, FONT_RED, 0, "红 色");
        colorMenu.add(0, FONT_GREEN, 0, "绿 色");
        colorMenu.add(0, FONT_BLUE, 0, "蓝 色");

        return super.onCreateOptionsMenu(menu);

    }

    @Override
    public boolean onOptionsItemSelected(MenuItem mi)
    {
        switch(mi.getItemId())
        {
            case FONT_10:
                edit.setTextSize(10*2);
                break;
            case FONT_12:
                edit.setTextSize(12*2);
                break;
            case FONT_14:
                edit.setTextSize(14*2);
                break;
            case FONT_16:
                edit.setTextSize(16*2);
                break;
            case FONT_18:
                edit.setTextSize(18*2);
                break;

            case FONT_RED:
                edit.setTextColor(Color.RED);
                break;
            case FONT_GREEN:
                edit.setTextColor(Color.GREEN);
                break;
            case FONT_BLUE:
                edit.setTextColor(Color.BLUE);
                break;
            case PLAIN_ITEM:
                //Toast.makeText(MenuDemo.this,"Common Menu",Toast.LENGTH_SHORT).show();
                break;
        }

        return true;
    }


}



