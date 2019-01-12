package demo.org.ichanging.actionbar;

import android.content.Context;
import android.net.Uri;
import android.os.Bundle;
import android.app.Fragment;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import org.w3c.dom.Text;

public class DummyFragment extends Fragment {
    public  static final  String ARG_SECTION_NUMBER = "section_number";

    @Override
    public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savadInstanceState)
    {
        TextView textView = new TextView(getActivity());
        textView.setGravity(Gravity.START);
        Bundle args = getArguments();
        textView.setText(args.getInt(ARG_SECTION_NUMBER) + "");
        return  textView;
    }
}
