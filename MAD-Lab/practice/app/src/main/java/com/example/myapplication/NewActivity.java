package com.example.myapplication;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;

public class NewActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_new);

        Intent intent = getIntent();
        String source = intent.getStringExtra("source");
        String destination = intent.getStringExtra("destination");
        String name = intent.getStringExtra("name");
        String date = intent.getStringExtra("date");
        String one_way = intent.getStringExtra("one_way");

        TextView t1 = findViewById(R.id.textView6);
        TextView t2 = findViewById(R.id.textView7);
        TextView t3 = findViewById(R.id.textView8);
        TextView t4 = findViewById(R.id.textView11);
        TextView t5 = findViewById(R.id.textView9);

        t1.setText(t1.getText() + " " + name);
        t2.setText(t2.getText() + " " + source);
        t3.setText(t3.getText() + " " + destination);
        t4.setText(t4.getText() + " " + date);
        t5.setText(t5.getText() + " " + one_way);
    }
}
