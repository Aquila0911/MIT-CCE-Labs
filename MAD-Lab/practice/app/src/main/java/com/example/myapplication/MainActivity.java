package com.example.myapplication;

import android.app.DatePickerDialog;
import android.content.Context;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private Button submitButton;
    private Button resetButton;
    private Button dateButton;
    private ToggleButton toggleButton;
    private TextView dateTV;
    private EditText nameText;
    private Spinner srcSpinner;
    private Spinner dstSpinner;

    public boolean oneway;
    DBHelper dbHelper = new DBHelper(this);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        submitButton = findViewById(R.id.submitButton);
        resetButton = findViewById(R.id.resetButton);
        dateButton = findViewById(R.id.dateButton);
        toggleButton = findViewById(R.id.toggleButton);
        dateTV = findViewById(R.id.dateTV);
        nameText = findViewById(R.id.nameText);
        srcSpinner = findViewById(R.id.srcSpinner);
        dstSpinner = findViewById(R.id.dstSpinner);

        List<String> spinnerArray =  new ArrayList<String>();
        spinnerArray.add("Kolkata");
        spinnerArray.add("Bengaluru");
        spinnerArray.add("Delhi");
        spinnerArray.add("Mumbai");

        ArrayAdapter<String> spinnerArrayAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, spinnerArray);
        spinnerArrayAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        srcSpinner.setAdapter(spinnerArrayAdapter);
        dstSpinner.setAdapter(spinnerArrayAdapter);

        dateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                final Calendar c = Calendar.getInstance();
                int year = c.get(Calendar.YEAR);
                int month = c.get(Calendar.MONTH);
                int day = c.get(Calendar.DAY_OF_MONTH);

                DatePickerDialog datePickerDialog = new DatePickerDialog(MainActivity.this,
                        new DatePickerDialog.OnDateSetListener() {
                            @Override
                            public void onDateSet(DatePicker view, int year, int monthOfYear, int dayOfMonth) {
                                // on below line we are setting date to our text view.
                                dateTV.setText(dayOfMonth + "-" + (monthOfYear + 1) + "-" + year);
                            }
                        }, year, month, day);

                datePickerDialog.getDatePicker().setMinDate(c.getTimeInMillis());
                datePickerDialog.show();
            }
        });

        toggleButton.setOnCheckedChangeListener((buttonView, isChecked) -> {
            oneway = isChecked;
        });

        resetButton.setOnClickListener(v -> {
            nameText.setText("");
            srcSpinner.setSelection(0);
            dstSpinner.setSelection(0);
            dateTV.setText("");
            toggleButton.setChecked(false);
            oneway = false;
        });

        submitButton.setOnClickListener(v -> {
            String source = srcSpinner.getSelectedItem().toString();
            String destination = dstSpinner.getSelectedItem().toString();
            String name = nameText.getText().toString();
            String date = dateTV.getText().toString();

            Intent intent = new Intent(MainActivity.this, NewActivity.class);
            intent.putExtra("source", source);
            intent.putExtra("destination", destination);
            intent.putExtra("name", name);
            intent.putExtra("date", date);
            intent.putExtra("one_way", oneway ? "true" : "false");
            startActivity(intent);
        });

    }
    static class DBHelper extends SQLiteOpenHelper {
        private static final String DB_NAME = "travel.db";
        private static final int DB_VERSION = 1;
        private static final String TABLE_NAME = "travel";

        public DBHelper(Context context) {
            super(context, DB_NAME, null, DB_VERSION);
        }

        @Override
        public void onCreate(SQLiteDatabase db) {
            db.execSQL("CREATE TABLE " + TABLE_NAME + " (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, source TEXT, destination TEXT)");
        }

        @Override
        public void onUpgrade(SQLiteDatabase db, int i, int i1) {
            db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
            onCreate(db);
        }
    }
}