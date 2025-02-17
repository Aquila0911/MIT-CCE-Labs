package com.example.vehicleparking;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private Spinner spinnerVehicleType;
    private EditText edtVehicleNumber, edtRCNumber;
    private Button btnSubmit;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        spinnerVehicleType = findViewById(R.id.spinnerVehicleType);
        edtVehicleNumber = findViewById(R.id.edtVehicleNumber);
        edtRCNumber = findViewById(R.id.edtRCNumber);
        btnSubmit = findViewById(R.id.btnSubmit);

        btnSubmit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String vehicleType = spinnerVehicleType.getSelectedItem().toString();
                String vehicleNumber = edtVehicleNumber.getText().toString();
                String rcNumber = edtRCNumber.getText().toString();

                // Check for empty fields
                if (vehicleNumber.isEmpty() || rcNumber.isEmpty()) {
                    Toast.makeText(MainActivity.this, "Please fill in all fields", Toast.LENGTH_SHORT).show();
                } else {
                    Intent intent = new Intent(MainActivity.this, ConfirmationActivity.class);
                    intent.putExtra("vehicleType", vehicleType);
                    intent.putExtra("vehicleNumber", vehicleNumber);
                    intent.putExtra("rcNumber", rcNumber);
                    startActivity(intent);
                }
            }
        });
    }
}