package com.example.vehicleparking;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;

import java.util.Random;

public class ConfirmationActivity extends AppCompatActivity {

    private TextView tvVehicleDetails;
    private Button btnConfirm, btnEdit;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_confirmation);

        tvVehicleDetails = findViewById(R.id.tvVehicleDetails);
        btnConfirm = findViewById(R.id.btnConfirm);
        btnEdit = findViewById(R.id.btnEdit);

        // Retrieve the data from the Intent
        String vehicleType = getIntent().getStringExtra("vehicleType");
        String vehicleNumber = getIntent().getStringExtra("vehicleNumber");
        String rcNumber = getIntent().getStringExtra("rcNumber");

        String vehicleDetails = "Vehicle Type: " + vehicleType + "\n" +
                "Vehicle Number: " + vehicleNumber + "\n" +
                "RC Number: " + rcNumber;

        tvVehicleDetails.setText(vehicleDetails);

        btnConfirm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Generate a random serial number for parking allotment
                Random random = new Random();
                int serialNumber = random.nextInt(100000);
                Toast.makeText(ConfirmationActivity.this, "Parking Allotment Confirmed. Serial Number: " + serialNumber, Toast.LENGTH_SHORT).show();
                finish();  // Close the current activity and return to the main screen
            }
        });

        btnEdit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();  // Return to the MainActivity to edit the details
            }
        });
    }
}