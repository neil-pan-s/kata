package demo.org.ichanging.menu;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.PopupMenu;
import android.widget.Toast;

public class PopupMenuDemo extends AppCompatActivity {

    PopupMenu popupMenu;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_popup_menu_demo);
    }

    public  void onPopupButtonClick(View v)
    {
        popupMenu = new PopupMenu(this,v);
        getMenuInflater().inflate(R.menu.popup_menu,popupMenu.getMenu());
        popupMenu.setOnMenuItemClickListener(new PopupMenu.OnMenuItemClickListener() {
            @Override
            public boolean onMenuItemClick(MenuItem item) {
                switch(item.getItemId())
                {
                    case R.id.exit:
                        popupMenu.dismiss();
                        break;
                    default:
                        Toast.makeText(PopupMenuDemo.this,"Click " + item.getTitle() + "Menu",Toast.LENGTH_SHORT).show();
                        break;
                }

                return true;
            }
        });
        popupMenu.show();
    }
}
