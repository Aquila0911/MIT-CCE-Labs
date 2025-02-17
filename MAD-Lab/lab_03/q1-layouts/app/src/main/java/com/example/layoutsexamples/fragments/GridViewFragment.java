package com.example.layoutsexamples.fragments;

import android.os.Build;
import android.os.Bundle;

import androidx.annotation.RequiresApi;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.TextView;

import com.example.layoutsexamples.R;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link GridViewFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
@RequiresApi(api = Build.VERSION_CODES.S)
public class GridViewFragment extends Fragment {
    private final int[] colorIds = {
            android.R.color.holo_red_light, android.R.color.holo_orange_light, android.R.color.holo_green_light, android.R.color.holo_blue_light,
            android.R.color.holo_purple, android.R.color.holo_blue_bright, android.R.color.darker_gray, android.R.color.holo_orange_dark,
            android.R.color.holo_red_dark, android.R.color.holo_green_dark, android.R.color.holo_blue_dark, android.R.color.system_accent1_100,
            android.R.color.white, android.R.color.black, android.R.color.darker_gray, android.R.color.background_light
    };

    // TODO: Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";

    // TODO: Rename and change types of parameters
    private String mParam1;
    private String mParam2;

    public GridViewFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment GridViewFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static GridViewFragment newInstance(String param1, String param2) {
        GridViewFragment fragment = new GridViewFragment();
        Bundle args = new Bundle();
        args.putString(ARG_PARAM1, param1);
        args.putString(ARG_PARAM2, param2);
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            mParam1 = getArguments().getString(ARG_PARAM1);
            mParam2 = getArguments().getString(ARG_PARAM2);
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_grid_view, container, false);
        GridView gridView = view.findViewById(R.id.gridView);
        ColorAdapter colorAdapter = new ColorAdapter();
        gridView.setAdapter(colorAdapter);

        return view;
    }

    public class ColorAdapter extends BaseAdapter {

        @Override
        public int getCount() {
            return colorIds.length;  // 16 colors for 4x4 grid
        }

        @Override
        public Object getItem(int position) {
            return colorIds[position];
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            TextView colorBox;
            if (convertView == null) {
                // If no reusable view, create new TextView
                colorBox = new TextView(getContext());
                colorBox.setLayoutParams(new GridView.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));  // Box size
                colorBox.setPadding(8, 8, 8, 8);  // Padding around the box
                colorBox.setText("");  // No text, just the color box
            } else {
                colorBox = (TextView) convertView;  // Reuse view
            }

            // Set background color from colorIds array
            colorBox.setBackgroundResource(colorIds[position]);
            return colorBox;
        }
    }
}