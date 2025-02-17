package com.example.myapplication;

import android.graphics.Typeface;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;

import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.util.Timer;
import java.util.TimerTask;

class InputTextWatcher implements TextWatcher {
    int delay = 1000;
    Timer timer = new Timer();
    TextView view;
    EditText input_text;

    InputTextWatcher(TextView text_view, EditText input) {
        view = text_view;
        input_text = input;
    }

    @Override
    public void beforeTextChanged(CharSequence s, int start, int count, int after) {

    }

    @Override
    public void onTextChanged(CharSequence s, int start, int before, int count) {
        timer.cancel();
        timer.purge();
    }

    @Override
    public void afterTextChanged(Editable s) {
        timer = new Timer();
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                view.setText(input_text.getText());
            }
        };
        timer.schedule(task, delay);
    }
}

public class MainActivity extends AppCompatActivity {
    EditText input_text = null;
    TextView text_view = null;
    ImageButton bold_button = null;
    ImageButton italic_button = null;


    private boolean _bold = false;
    private boolean _italic = false;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // Entry point to application, lifecycle related stuff done here

        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        input_text = findViewById(R.id.editTextTextMultiLine);
        text_view = findViewById(R.id.textView2);
        bold_button = findViewById(R.id.imageButton);
        italic_button = findViewById(R.id.imageButton2);

        input_text.addTextChangedListener(new InputTextWatcher(text_view, input_text));

        bold_button.setOnClickListener(view -> {
            _bold = !_bold;
            text_view.setTypeface(getFont());
        });
        italic_button.setOnClickListener(view -> {
            _italic = !_italic;
            text_view.setTypeface(getFont());
        });

        Log.d("MainActivity", "Application Setup");
    }

    @Override
    protected void onStart() {
        // App is now visible to user

        super.onStart();
        Log.d("MainActivity", "Application Started");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d("MainActivity", "Application Focused");
    }

    @Override
    protected void onPause() {
        // An activity comes to foreground like a phone call
        super.onPause();
        Log.d("MainActivity", "Application Interrupted");

        /*
        onPause() execution is very brief and does not necessarily offer enough time to perform save operations.
        For this reason, don't use onPause() to save application or user data, make network calls, or execute database transactions.
        Such work might not complete before the method completes.
        Instead, perform heavy-load shutdown operations during onStop(). For more information about suitable operations to perform during onStop()
         */
    }

    @Override
    protected void onStop() {
        // Activity no longer visible
        super.onStop();
        Log.d("MainActivity", "Application Stopped");
    }

    @Override
    protected void onRestart() {
        // From stop to restart, when user brings up activity again
        super.onRestart();
        Log.d("MainActivity", "Application Restarted");
    }

    // onDestroy called when activity finished or killed

    public Typeface getFont() {
        if (_bold && _italic) {
            return Typeface.defaultFromStyle(Typeface.BOLD_ITALIC);
        }
        if (_italic || _bold) {
            return Typeface.defaultFromStyle(_bold ? Typeface.BOLD : Typeface.ITALIC);
        }
        return Typeface.defaultFromStyle(Typeface.NORMAL);
    }
}
