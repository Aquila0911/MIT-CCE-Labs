package com.example.testapp;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        Button b = findViewById(R.id.button1);
        b.setOnClickListener(view -> {
            LayoutInflater inflater = getLayoutInflater();
            View layout = inflater.inflate(R.layout.toast_layout, null);

            // Find the ImageView and TextView in the custom layout
            ImageView imageView = layout.findViewById(R.id.toast_image);
            TextView textView = layout.findViewById(R.id.toast_text);

            // Set the image and text (optional)
            imageView.setImageResource(R.drawable.ic_launcher_background); // Replace with your image
            textView.setText("This is a custom toast message! - 1");

            // Create the Toast object and set the custom layout
            Toast toast = new Toast(getApplicationContext());
            toast.setDuration(Toast.LENGTH_SHORT); // You can use LENGTH_LONG if needed
            toast.setView(layout);
            toast.show();
        });

        ToggleButton tb = findViewById(R.id.button2);
        tb.setOnClickListener(view -> {
            LayoutInflater inflater = getLayoutInflater();
            View layout = inflater.inflate(R.layout.toast_layout, null);

            // Find the ImageView and TextView in the custom layout
            ImageView imageView = layout.findViewById(R.id.toast_image);
            TextView textView = layout.findViewById(R.id.toast_text);

            // Set the image and text (optional)
            imageView.setImageResource(R.drawable.ic_launcher_foreground); // Replace with your image
            textView.setText("This is a custom toast message! - 2" + " - Checked: " + tb.isChecked());

            // Create the Toast object and set the custom layout
            Toast toast = new Toast(getApplicationContext());
            toast.setDuration(Toast.LENGTH_SHORT); // You can use LENGTH_LONG if needed
            toast.setView(layout);
            toast.show();
        });
    }
}