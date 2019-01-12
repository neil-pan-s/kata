package demo.org.ichanging.dialog;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.Toast;

public class AlertDialogDemo extends AppCompatActivity {

    String[] items = new String[]
            {
                "hello binggo",
                "hello fengo",
                "hello dog",
                "hello cat",
            };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_alert_dialog_demo);

    }

    public void simple(View v)
    {
        AlertDialog.Builder builder = new AlertDialog.Builder(this)
                .setTitle("TEST")
                .setIcon(R.drawable.ic_launcher)
                .setMessage("Hello World");

        setPositiveButton(builder);
        setNegativeButton(builder);
        builder.create().show();

    }

    private AlertDialog.Builder setPositiveButton(AlertDialog.Builder builder)
    {
        return builder.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                System.out.println("yes click");
            }
        });
    }

    private AlertDialog.Builder setNegativeButton(AlertDialog.Builder builder)
    {
        return builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                System.out.println("Cancel click");
            }
        });
    }

    public void simpleList(View v)
    {
        AlertDialog.Builder builder = new AlertDialog.Builder(this)
                .setTitle("TEST LIST")
                .setIcon(R.drawable.ic_launcher)
                .setItems(items, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        System.out.println("clicked" + items[which]);
                    }
                });

        setPositiveButton(builder);
        setNegativeButton(builder);
        builder.create().show();
    }


    public void singleChoice(View v)
    {
        AlertDialog.Builder builder = new AlertDialog.Builder(this)
                .setTitle("TEST LIST")
                .setIcon(R.drawable.ic_launcher)
                .setSingleChoiceItems(items, 1, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        System.out.println("clicked" + items[which]);
                    }
                });

        setPositiveButton(builder);
        setNegativeButton(builder);
        builder.create().show();
    }


    public void multiChoice(View v)
    {
        AlertDialog.Builder builder = new AlertDialog.Builder(this)
                .setTitle("TEST LIST")
                .setIcon(R.drawable.ic_launcher)
                .setMultiChoiceItems(items, new boolean[]{false, true, false, true}, new DialogInterface.OnMultiChoiceClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which, boolean isChecked) {
                        System.out.println("" + items[which] + isChecked);
                    }
                });

        setPositiveButton(builder);
        setNegativeButton(builder);
        builder.create().show();
    }

    public void custom(View v)
    {
        final LinearLayout loginForm = (LinearLayout) getLayoutInflater().inflate(R.layout.login,null);

        AlertDialog.Builder builder = new AlertDialog.Builder(this)
                .setTitle("TEST LIST")
                .setIcon(R.drawable.ic_launcher)
                .setView(loginForm)
                .setPositiveButton("login", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        EditText name = (EditText) loginForm.findViewById(R.id.name);
                        EditText pwd = (EditText) loginForm.findViewById(R.id.pwd);

                        Toast.makeText(AlertDialogDemo.this,"Name:" + name.getText() + "Pwd:" + pwd.getText(),Toast.LENGTH_SHORT).show();
                    }
                })
                .setNegativeButton("cancel", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(AlertDialogDemo.this,"Cancel",Toast.LENGTH_SHORT).show();
                    }
                });

        builder.create().show();
    }



}
