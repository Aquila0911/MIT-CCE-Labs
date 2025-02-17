package com.example.sportsapp;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.sportsapp.adapters.SportAdapter;
import com.example.sportsapp.models.Sport;
import com.squareup.picasso.Picasso;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private Spinner sportSpinner;
    private TextView selectedSportText;
    private ImageView sportImageView;
    private TextView sportDescriptionText;
    private List<Sport> sportList;

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

        sportSpinner = findViewById(R.id.sportSpinner);
        selectedSportText = findViewById(R.id.selectedSportText);
        sportImageView = findViewById(R.id.sportImageView);
        sportDescriptionText = findViewById(R.id.sportDescriptionText);

        // Create a list of sports with additional details
        sportList = new ArrayList<>();
        sportList.add(new Sport("Football", "Football is a team sport played with a spherical ball.", "https://th.bing.com/th/id/OIP.ONUF2gIsOHqmILSozWH12AHaE8?rs=1&pid=ImgDetMain"));
        sportList.add(new Sport("Basketball", "Basketball is a sport where two teams of five players compete to score points.", "https://th.bing.com/th/id/OSK.HEROLGeH8UiMicU5TyclP5omxRJoPk5RdlTKKwFadeqEvZ0?rs=1&pid=ImgDetMain"));
        sportList.add(new Sport("Tennis", "Tennis is a racket sport that can be played individually or in doubles.", "https://th.bing.com/th/id/R.0c316db9630d6db81c5c8d371dce7a8c?rik=V5GkzMfr6H3hGQ&riu=http%3a%2f%2fupload.wikimedia.org%2fwikipedia%2fcommons%2f3%2f3e%2fTennis_Racket_and_Balls.jpg&ehk=DdRfRq8%2fuzZ8iRdtc1jmyPocks58dVY6%2fiqsbPsEXnQ%3d&risl=1&pid=ImgRaw&r=0"));
        sportList.add(new Sport("Cricket", "Cricket is a bat-and-ball game played between two teams of eleven players.", "https://th.bing.com/th/id/OSK.HEROaoWLAhlH7cNUBeoLdSxqXtFcjLYkXSwqMCHX63a1h-0?rs=1&pid=ImgDetMain"));
        sportList.add(new Sport("Rugby", "Rugby is a collective team sport that involves carrying, passing, and kicking a ball.", "https://th.bing.com/th/id/R.6f97955c97cd97be3177a4b38b59a098?rik=UKOEd58DcwvnnQ&riu=http%3a%2f%2fcoachfore.org%2fwp-content%2fuploads%2f2018%2f06%2ffootball-and-politics.jpg&ehk=jMqlSLZ7gX18nfCEzjAdlRjZgIBenVLsY6oh4F7n2uk%3d&risl=&pid=ImgRaw&r=0"));

        // Create an ArrayAdapter to display the sport names in the Spinner
        List<String> sportNames = new ArrayList<>();
        for (Sport sport : sportList) {
            sportNames.add(sport.getName());
        }

        ArrayAdapter<String> adapter = new ArrayAdapter<>(this, android.R.layout.simple_spinner_item, sportNames);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        sportSpinner.setAdapter(adapter);

        // Set up a listener for the Spinner selection
        sportSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parentView, View selectedItemView, int position, long id) {
                // Get the selected sport from the list
                Sport selectedSport = sportList.get(position);

                // Update the UI with the selected sport's details
                selectedSportText.setText("Selected sport: " + selectedSport.getName());
                sportDescriptionText.setText(selectedSport.getDescription());

                // Load the sport's image using Picasso (if available)
                if (selectedSport.getImageUrl() != null && !selectedSport.getImageUrl().isEmpty()) {
                    Log.d("MainActivity", "Loading image url: " + selectedSport.getImageUrl());
                    Picasso.get().load(selectedSport.getImageUrl()).into(sportImageView);
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parentView) {
                // Handle case where no item is selected (optional)
            }
        });
    }
}