package demo.org.ichanging.fragment;

import android.content.Context;
import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;


public class LifeFragment extends Fragment {

    final String TAG = "=== LifeFragment ===";

    public LifeFragment() {
        // Required empty public constructor

    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.d(TAG, "---- onCreate ----");

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        Log.d(TAG, "---- onCreateView ----");

        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_life, container, false);
    }


    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

        Log.d(TAG, "---- onActivityCreated ----");

    }


    @Override
    public void onStop() {
        super.onStop();

        Log.d(TAG, "---- onStop ----");

    }

    @Override
    public void onStart() {
        super.onStart();

        Log.d(TAG, "---- onStart ----");

    }


    @Override
    public void onPause() {
        super.onPause();

        Log.d(TAG, "---- onPause ----");

    }

    @Override
    public void onResume() {
        super.onResume();

        Log.d(TAG, "---- onResume ----");

    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);

        Log.d(TAG, "---- onAttach ----");

    }

    @Override
    public void onDetach() {
        super.onDetach();

        Log.d(TAG, "---- onDetach ----");

    }

    @Override
    public void onDestroy() {
        super.onDestroy();

        Log.d(TAG, "---- onDestroy ----");
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();

        Log.d(TAG, "---- onDestroyView ----");

    }
}
