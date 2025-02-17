package com.example.movieapp;

import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;
import androidx.appcompat.app.AppCompatActivity;

import com.example.movieapp.BookingDetailsActivity;

import java.util.Calendar;

public class MainActivity extends AppCompatActivity {

    private Spinner spinnerMovie, spinnerTheatre;
    private TextView tvDatePicker, tvTimePicker;
    private ToggleButton toggleTicketType;
    private Button btnBookNow, btnReset;
    private int selectedHour, selectedMinute;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize views
        spinnerMovie = findViewById(R.id.spinner_movie);
        spinnerTheatre = findViewById(R.id.spinner_theatre);
        tvDatePicker = findViewById(R.id.tv_date_picker);
        tvTimePicker = findViewById(R.id.tv_time_picker);
        toggleTicketType = findViewById(R.id.toggle_ticket_type);
        btnBookNow = findViewById(R.id.btn_book_now);
        btnReset = findViewById(R.id.btn_reset);

        // Open Date Picker when clicking the TextView
        tvDatePicker.setOnClickListener(v -> openDatePicker());

        // Open Time Picker when clicking the TextView
        tvTimePicker.setOnClickListener(v -> openTimePicker());

        // Book Now button click handler
        btnBookNow.setOnClickListener(v -> {
            if (validateInputs()) {
                openBookingSummary();
            }
        });

        // Reset button click handler
        btnReset.setOnClickListener(v -> resetFields());
    }

    private void openDatePicker() {
        Calendar calendar = Calendar.getInstance();
        DatePickerDialog datePickerDialog = new DatePickerDialog(
                this,
                (view, year, month, dayOfMonth) -> {
                    String selectedDate = year + "-" + (month + 1) + "-" + dayOfMonth;
                    tvDatePicker.setText(selectedDate);
                },
                calendar.get(Calendar.YEAR),
                calendar.get(Calendar.MONTH),
                calendar.get(Calendar.DAY_OF_MONTH)
        );
        datePickerDialog.getDatePicker().setMinDate(calendar.getTimeInMillis());
        datePickerDialog.show();
    }

    private void openTimePicker() {
        Calendar calendar = Calendar.getInstance();
        TimePickerDialog timePickerDialog = new TimePickerDialog(
                this,
                (view, hourOfDay, minute) -> {
                    selectedHour = hourOfDay;
                    selectedMinute = minute;
                    String selectedTime = String.format("%02d:%02d", hourOfDay, minute);
                    tvTimePicker.setText(selectedTime);
                },
                calendar.get(Calendar.HOUR_OF_DAY),
                calendar.get(Calendar.MINUTE),
                true
        );
        timePickerDialog.show();
    }

    private boolean validateInputs() {
        // Validate all fields
        if (tvDatePicker.getText().toString().equals("Select Date")) {
            showError("Please select a date");
            return false;
        }
        if (tvTimePicker.getText().toString().equals("Select Time")) {
            showError("Please select a time");
            return false;
        }
        if (Integer.parseInt(new String(tvTimePicker.getText().toString()).split(":")[0]) > 12 && toggleTicketType.isChecked()) {
            showError("Premium not available after 12!");
            return false;
        }
        return true;
    }

    private void showError(String message) {
        // You can show a toast or an error message to the user
        Toast.makeText(this, message, Toast.LENGTH_LONG).show();
    }

    private void openBookingSummary() {
        // Create an intent to pass booking details to the next activity
        Intent intent = new Intent(this, BookingDetailsActivity.class);

        // Pass data (movie, theatre, date, time, and ticket type)
        intent.putExtra("movie", spinnerMovie.getSelectedItem().toString());
        intent.putExtra("theatre", spinnerTheatre.getSelectedItem().toString());
        intent.putExtra("date", tvDatePicker.getText().toString());
        intent.putExtra("time", tvTimePicker.getText().toString());
        intent.putExtra("ticketType", toggleTicketType.isChecked() ? "Premium" : "Standard");

        startActivity(intent);
    }

    private void resetFields() {
        spinnerMovie.setSelection(0);
        spinnerTheatre.setSelection(0);
        tvDatePicker.setText("Select Date");
        tvTimePicker.setText("Select Time");
        toggleTicketType.setChecked(false);
    }
}
