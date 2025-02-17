package com.example.fitnesscenter;

import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

public class BaseActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the app bar.
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menuex, menu);

        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle menu item clicks
        if (item.getItemId() == R.id.action_contact) {
            Intent intent = new Intent(this, ContactUsActivity.class);
            startActivity(intent);
        } else if (item.getItemId() == R.id.action_about) {
            Intent intent = new Intent(this, AboutUsActivity.class);
            startActivity(intent);
        } else if (item.getItemId() == R.id.action_home) {
            if (!this.getClass().getSimpleName().equals("MainActivity")) {
                Intent intent = new Intent(this, MainActivity.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);
                startActivity(intent);
                finish();
            }
        } else if (item.getItemId() == R.id.action_workout) {
            Intent intent = new Intent(this, WorkoutActivity.class);
            startActivity(intent);
        } else if (item.getItemId() == R.id.action_trainers) {
            Intent intent = new Intent(this, TrainerActivity.class);
            startActivity(intent);
        } else if (item.getItemId() == R.id.action_membership) {
            Intent intent = new Intent(this, MembershipActivity.class);
            startActivity(intent);
        } else if (item.getItemId() == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
