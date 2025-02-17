package com.example.foodapp;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

public class OrderSummaryActivity extends AppCompatActivity {

    private TextView orderedItemsList, totalCost;
    private Button backButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_order_summary);

        // Initialize views
        orderedItemsList = findViewById(R.id.orderedItemsList);
        totalCost = findViewById(R.id.totalCost);
        backButton = findViewById(R.id.backButton);

        // Get data from the Intent
        Intent intent = getIntent();
        String orderedItems = intent.getStringExtra("orderedItems");
        double cost = intent.getDoubleExtra("totalCost", 0.0);

        // Display ordered items and total cost
        orderedItemsList.setText(orderedItems);
        totalCost.setText("Total Cost: $" + cost);

        // Back button to return to the main activity
        backButton.setOnClickListener(v -> finish());
    }
}
