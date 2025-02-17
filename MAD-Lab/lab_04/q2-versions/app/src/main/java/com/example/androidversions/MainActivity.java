package com.example.androidversions;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

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

        Button buttonAndroid1 = findViewById(R.id.button_android_1);
        Button buttonAndroid2 = findViewById(R.id.button_android_2);
        Button buttonAndroid3 = findViewById(R.id.button_android_3);
        Button buttonAndroid4 = findViewById(R.id.button_android_4);
        Button buttonAndroid5 = findViewById(R.id.button_android_5);
        Button buttonAndroid6 = findViewById(R.id.button_android_6);
        Button buttonAndroid7 = findViewById(R.id.button_android_7);
        Button buttonAndroid8 = findViewById(R.id.button_android_8);
        Button buttonAndroid9 = findViewById(R.id.button_android_9);
        Button buttonAndroid10 = findViewById(R.id.button_android_10);

        buttonAndroid1.setOnClickListener(view -> showToast("Android 1.5 (Cupcake)", R.drawable.icon_cupcake));
        buttonAndroid2.setOnClickListener(view -> showToast("Android 2.3 (Gingerbread)", R.drawable.icon_gingerbread));
        buttonAndroid3.setOnClickListener(view -> showToast("Android 4.0 (Ice Cream Sandwich)", R.drawable.icon_icecream_sandwich));
        buttonAndroid4.setOnClickListener(view -> showToast("Android 5.0 (Lollipop)", R.drawable.icon_lollipop));
        buttonAndroid5.setOnClickListener(view -> showToast("Android 6.0 (Marshmallow)", R.drawable.icon_marshmallow));
        buttonAndroid6.setOnClickListener(view -> showToast("Android 7.0 (Nougat)", R.drawable.icon_nougat));
        buttonAndroid7.setOnClickListener(view -> showToast("Android 8.0 (Oreo)", R.drawable.icon_oreo));
        buttonAndroid8.setOnClickListener(view -> showToast("Android 9.0 (Pie)", R.drawable.icon_pie));
        buttonAndroid9.setOnClickListener(view -> showToast("Android 10 (Q)", R.drawable.icon_q));
        buttonAndroid10.setOnClickListener(view -> showToast("Android 11 (R)", R.drawable.icon_r));
    }

    private void showToast(String versionName, int iconResId) {
        LayoutInflater inflater = getLayoutInflater();
        View layout = inflater.inflate(R.layout.toast_layout, null);

        // Find the ImageView and TextView in the custom layout
        ImageView imageView = layout.findViewById(R.id.toast_image);
        TextView textView = layout.findViewById(R.id.toast_text);

        // Set the image and text (optional)
        imageView.setImageResource(iconResId); // Replace with your image
        textView.setText(versionName);

        // Create the Toast object and set the custom layout
        Toast toast = new Toast(getApplicationContext());
        toast.setDuration(Toast.LENGTH_SHORT); // You can use LENGTH_LONG if needed
        toast.setView(layout);
        toast.show();
    }
}