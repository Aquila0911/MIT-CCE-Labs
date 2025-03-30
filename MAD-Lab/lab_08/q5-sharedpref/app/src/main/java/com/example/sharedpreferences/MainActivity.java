package com.example.sharedpreferences;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private EditText nameInput, emailInput;
    private Button saveButton;

    private static final String PREFS_NAME = "UserPrefs";
    private static final String KEY_NAME = "name";
    private static final String KEY_EMAIL = "email";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        nameInput = findViewById(R.id.nameInput);
        emailInput = findViewById(R.id.emailInput);
        saveButton = findViewById(R.id.saveButton);

        loadSavedData(); // Restore saved data

        saveButton.setOnClickListener(v -> {
            saveData();
            Toast.makeText(MainActivity.this, "Data Saved", Toast.LENGTH_SHORT).show();
        });
    }

    // Save data to SharedPreferences
    private void saveData() {
        SharedPreferences sharedPreferences = getSharedPreferences(PREFS_NAME, MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putString(KEY_NAME, nameInput.getText().toString());
        editor.putString(KEY_EMAIL, emailInput.getText().toString());
        editor.apply(); // Apply changes asynchronously
    }

    // Load data from SharedPreferences
    private void loadSavedData() {
        SharedPreferences sharedPreferences = getSharedPreferences(PREFS_NAME, MODE_PRIVATE);
        String savedName = sharedPreferences.getString(KEY_NAME, "");
        String savedEmail = sharedPreferences.getString(KEY_EMAIL, "");

        nameInput.setText(savedName);
        emailInput.setText(savedEmail);
    }
}
