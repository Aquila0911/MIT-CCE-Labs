package com.example.layoutsexample.fragments;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import com.example.layoutsexample.R;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link TableLayoutFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class TableLayoutFragment extends Fragment {

    // TODO: Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";

    // TODO: Rename and change types of parameters
    private String mParam1;
    private String mParam2;

    public TableLayoutFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment TableLayoutFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static TableLayoutFragment newInstance(String param1, String param2) {
        TableLayoutFragment fragment = new TableLayoutFragment();
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
        View view = inflater.inflate(R.layout.fragment_table_layout, container, false);

        // Setup TableLayout
        TableLayout tableLayout = view.findViewById(R.id.tableLayout);

        // Adding the "Header" row (like the first row in Excel)
        TableRow headerRow = new TableRow(getContext());
        for (int i = 0; i < 5; i++) {
            EditText headerCell = new EditText(getContext());
            headerCell.setText("Column " + (i + 1));  // Header text
            headerCell.setPadding(10, 10, 10, 10);
            headerCell.setBackgroundResource(android.R.color.darker_gray);  // Background color for header
            headerRow.addView(headerCell);
        }
        tableLayout.addView(headerRow);

        // Adding multiple rows of data (like the rows in Excel)
        for (int i = 1; i <= 10; i++) {  // Create 10 rows
            TableRow dataRow = new TableRow(getContext());
            for (int j = 0; j < 5; j++) {  // Create 5 columns per row
                EditText dataCell = new EditText(getContext());
                dataCell.setText("Data " + i + "," + (j + 1));  // Cell data
                dataCell.setPadding(10, 10, 10, 10);
                dataCell.setBackgroundResource(android.R.color.white);  // Background color for data cells
                dataRow.addView(dataCell);
            }
            tableLayout.addView(dataRow);
        }

        return view;
    }
}