package com.example.foodapp;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    // Declare CheckBox and Button
    private CheckBox foodItem1, foodItem2, foodItem3, foodItem4, foodItem5;
    private Button submitButton;

    public String[] places = {"1", "2", "3", "4"};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize views
        foodItem1 = findViewById(R.id.foodItem1);
        foodItem2 = findViewById(R.id.foodItem2);
        foodItem3 = findViewById(R.id.foodItem3);
        foodItem4 = findViewById(R.id.foodItem4);
        foodItem5 = findViewById(R.id.foodItem5);
        submitButton = findViewById(R.id.submitButton);

        int spinner1;
        Spinner spinner = findViewById(R.id.spinner1);
        ArrayAdapter<String> ad = new ArrayAdapter<>(
                this,
                android.R.layout.simple_spinner_item,
                places
        );
        ad.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(ad);

        if(foodItem3.isChecked() && foodItem2.isChecked()){
            spinner.setSelection(1);
        }

        // Set listener for submit button
        submitButton.setOnClickListener(v -> submitOrder());
    }

    // Method to handle order submission
    private void submitOrder() {
        // Create strings to store ordered items and their costs
        StringBuilder orderedItems = new StringBuilder();
        double totalCost = 0.0;

        // Check which items are selected and calculate total cost
        if (foodItem1.isChecked()) {
            orderedItems.append("Burger - $5\n");
            totalCost += 5;
        }
        if (foodItem2.isChecked()) {
            orderedItems.append("Pizza - $8\n");
            totalCost += 8;
        }
        if (foodItem3.isChecked()) {
            orderedItems.append("Pasta - $6\n");
            totalCost += 6;
        }
        if (foodItem4.isChecked()) {
            orderedItems.append("Salad - $4\n");
            totalCost += 4;
        }
        if (foodItem5.isChecked()) {
            orderedItems.append("Ice Cream - $3\n");
            totalCost += 3;
        }

        // If no item is selected, show a Toast message
        if (orderedItems.length() == 0) {
            Toast.makeText(this, "Please select at least one item!", Toast.LENGTH_SHORT).show();
            return;
        }

        // Pass data to OrderSummaryActivity
        Intent intent = new Intent(MainActivity.this, OrderSummaryActivity.class);
        intent.putExtra("orderedItems", orderedItems.toString());
        intent.putExtra("totalCost", totalCost);
        startActivity(intent);

        // Disable checkboxes after submitting the order
        foodItem1.setEnabled(false);
        foodItem2.setEnabled(false);
        foodItem3.setEnabled(false);
        foodItem4.setEnabled(false);
        foodItem5.setEnabled(false);
        submitButton.setEnabled(false);  // Disable submit button
    }
}
