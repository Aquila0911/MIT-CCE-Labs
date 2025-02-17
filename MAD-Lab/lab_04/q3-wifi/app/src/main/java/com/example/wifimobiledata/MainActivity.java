package com.example.wifimobiledata;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import android.widget.ToggleButton;

public class MainActivity extends AppCompatActivity {

    ToggleButton toggleButton;
    Button btnChangeMode;
    ImageView imageViewMode;
    boolean isWiFi = true; // as a default

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        toggleButton = findViewById(R.id.toggleButton);
        btnChangeMode = findViewById(R.id.btnChangeMode);
        imageViewMode = findViewById(R.id.imageViewMode);


        updateImageView();


        toggleButton.setOnCheckedChangeListener((buttonView, isChecked) -> {
            // Update mode based on toggle state
            if (isChecked) {
                // Wi-Fi mode
                isWiFi = true;
                Toast.makeText(MainActivity.this, "Current Mode: Wi-Fi", Toast.LENGTH_SHORT).show();
            } else {
                // Mobile Data mode
                isWiFi = false;
                Toast.makeText(MainActivity.this, "Current Mode: Mobile Data", Toast.LENGTH_SHORT).show();
            }
            updateImageView();
        });

        // Change Mode button listener
        btnChangeMode.setOnClickListener(v -> {
            // Change the toggle state and update the mode
            toggleButton.setChecked(isWiFi); // Set the toggle button according to the current mode
            if (isWiFi) {
                // Switch to Mobile Data mode
                isWiFi = false;
                Toast.makeText(MainActivity.this, "Switched to Mobile Data", Toast.LENGTH_SHORT).show();
            } else {
                // Switch to Wi-Fi mode
                isWiFi = true;
                Toast.makeText(MainActivity.this, "Switched to Wi-Fi", Toast.LENGTH_SHORT).show();
            }
            updateImageView();
        });
    }


    private void updateImageView() {
        if (isWiFi) {

            imageViewMode.setImageResource(R.drawable.wifi);
        } else {

            imageViewMode.setImageResource(R.drawable.mobile_data);
        }
    }
}
