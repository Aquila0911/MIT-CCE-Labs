package com.example.travelapp;

import android.app.DatePickerDialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.util.Calendar;
import java.util.Date;

public class MainActivity extends AppCompatActivity {
    private Button pickDateBtn;
    private TextView selectedDateTV;

    public String source = "", destination = "";

    public boolean one_way;

    private String[] places = {
            "Delhi", "Mumbai", "Kolkata", "Chennai", "Bangalore", "Ahmedabad", "Chandigarh", "Jaipur"
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // on below line we are initializing our variables.
        pickDateBtn = findViewById(R.id.idBtnPickDate);
        selectedDateTV = findViewById(R.id.idTVSelectedDate);

        // on below line we are adding click listener for our pick date button
        pickDateBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // on below line we are getting
                // the instance of our calendar.
                final Calendar c = Calendar.getInstance();

                // on below line we are getting
                // our day, month and year.
                int year = c.get(Calendar.YEAR);
                int month = c.get(Calendar.MONTH);
                int day = c.get(Calendar.DAY_OF_MONTH);

                // on below line we are creating a variable for date picker dialog.
                DatePickerDialog datePickerDialog = new DatePickerDialog(
                        // on below line we are passing context.
                        MainActivity.this,
                        new DatePickerDialog.OnDateSetListener() {
                            @Override
                            public void onDateSet(DatePicker view, int year,
                                                  int monthOfYear, int dayOfMonth) {
                                // on below line we are setting date to our text view.
                                selectedDateTV.setText(dayOfMonth + "-" + (monthOfYear + 1) + "-" + year);

                            }
                        },
                        // on below line we are passing year,
                        // month and day for selected date in our date picker.
                        year, month, day);

                datePickerDialog.getDatePicker().setMinDate(c.getTimeInMillis());
                // at last we are calling show to
                // display our date picker dialog.
                datePickerDialog.show();
            }
        });

//        Spinner

        Spinner sourceSpinner = findViewById(R.id.spinner2);
        Spinner destinationSpinner = findViewById(R.id.spinner3);

        ArrayAdapter<String> ad = new ArrayAdapter<>(
                this,
                android.R.layout.simple_spinner_item,
                places
        );
        ad.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        sourceSpinner.setAdapter(ad);
        destinationSpinner.setAdapter(ad);

//        Toggle Button

        ToggleButton tg = findViewById(R.id.toggleButton);
        tg.setOnCheckedChangeListener((buttonView, isChecked) -> {
            one_way = isChecked;
        });

//      Submit & Reset

        Button submit = findViewById(R.id.button2);
        Button reset = findViewById(R.id.button3);

        submit.setOnClickListener(v->{
            source = sourceSpinner.getSelectedItem().toString();
            destination = destinationSpinner.getSelectedItem().toString();
            if(source.equals(destination)){
                Toast.makeText(this, "Please select a different destination!!", Toast.LENGTH_LONG).show();
                return;
            }

            if(source.isEmpty() || destination.isEmpty() || selectedDateTV.getText().toString().isEmpty()) {
                Toast.makeText(this, "Please Enter All the fields!", Toast.LENGTH_LONG).show();
                return;
            }
            Intent intent = new Intent(this, ConfirmationActivity.class);
            intent.putExtra("source", source);
            intent.putExtra("destination", destination);
            intent.putExtra("date", selectedDateTV.getText().toString());
            intent.putExtra("one_way", one_way ? "true" : "false");
            startActivity(intent);
        });

        reset.setOnClickListener(v->{
            sourceSpinner.setSelection(0);
            destinationSpinner.setSelection(0);
            selectedDateTV.setText("");
            source = "";
            destination = "";
            tg.setChecked(false);
            one_way = false;
        });
    }

}