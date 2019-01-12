package demo.org.ichanging.textview;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.widget.MultiAutoCompleteTextView;

public class AutoCompleteTextViewDemo extends AppCompatActivity {

    AutoCompleteTextView autoText;
    MultiAutoCompleteTextView multiAutoText;

    String[] books = new String[]
            {
                    "book 1",
                    "book 2",
                    "book 3",
                    "book 4",
            };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_auto_complete_text_view_demo);

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,android.R.layout.simple_dropdown_item_1line,books);

        autoText = (AutoCompleteTextView) findViewById(R.id.autoCompleteTextView_book);
        autoText.setAdapter(adapter);

        multiAutoText = (MultiAutoCompleteTextView) findViewById(R.id.multiAutoCompleteTextView);
        multiAutoText.setAdapter(adapter);

        multiAutoText.setTokenizer(new MultiAutoCompleteTextView.CommaTokenizer());
    }
}
