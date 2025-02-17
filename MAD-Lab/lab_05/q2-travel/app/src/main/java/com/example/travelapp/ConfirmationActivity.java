package com.example.travelapp;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.util.UUID;

public class ConfirmationActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_confirmation);

        Intent intent = getIntent();
        String source = intent.getStringExtra("source");
        String destination = intent.getStringExtra("destination");
        String date = intent.getStringExtra("date");
        String one_way = intent.getStringExtra("one_way");

        TextView t1 = findViewById(R.id.textView6);
        TextView t2 = findViewById(R.id.textView7);
        TextView t3 = findViewById(R.id.textView8);
        TextView t4 = findViewById(R.id.textView9);
        TextView t5 = findViewById(R.id.textView10);

        t2.setText(t2.getText() + " " + source);
        t3.setText(t3.getText() + " " + destination);
        t4.setText(t4.getText() + " " + date);
        t5.setText(t5.getText() + " " + one_way);

        Button cb = findViewById(R.id.confirmBtn);
        cb.setOnClickListener(v->{
            Toast.makeText(this, "Your Booking has been confirmed succesfully!! Booking No.: " + UUID.randomUUID().toString(), Toast.LENGTH_LONG).show();
            finish();
        });

    }
}