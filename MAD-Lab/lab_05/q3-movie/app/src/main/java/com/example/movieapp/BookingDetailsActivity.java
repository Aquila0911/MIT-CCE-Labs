package com.example.movieapp;

import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.UUID;

public class BookingDetailsActivity extends AppCompatActivity {

    private TextView tvDetails;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_booking_details);

        tvDetails = findViewById(R.id.tv_details);

        String movie = getIntent().getStringExtra("movie");
        String theatre = getIntent().getStringExtra("theatre");
        String showDate = getIntent().getStringExtra("date");
        String showTime = getIntent().getStringExtra("time");
        String ticketType = getIntent().getStringExtra("ticketType");

        String details = "Movie: " + movie + "\n" +
                "Theatre: " + theatre + "\n" +
                "Date: " + showDate + "\n" +
                "Time: " + showTime + "\n" +
                "Ticket Type: " + ticketType + "\n\n";
        tvDetails.setText(details);

        Button btn = findViewById(R.id.button);
        btn.setOnClickListener(v -> {
            Toast.makeText(this, "Booking Confirmed: " + UUID.randomUUID().toString(), Toast.LENGTH_LONG).show();
            finish();
        });
    }
}
