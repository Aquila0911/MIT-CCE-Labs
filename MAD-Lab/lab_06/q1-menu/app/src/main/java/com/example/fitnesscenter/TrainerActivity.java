package com.example.fitnesscenter;

import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.widget.Toolbar;

public class TrainerActivity extends BaseActivity{
    int[] trainerImages = {R.drawable.cat1, R.drawable.cat2, R.drawable.cat3};
    String[] trainerNames = {"John Doe", "Jane Smith", "Mike Johnson"};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_trainer);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        ListView listView = findViewById(R.id.listView);

        // Set the custom adapter to the ListView
        listView.setAdapter(new TrainerAdapter());

        // Handle item clicks
        listView.setOnItemClickListener((parent, view, position, id) ->
                Toast.makeText(TrainerActivity.this, "Selected: " + trainerNames[position], Toast.LENGTH_SHORT).show()
        );
    }

    // Custom Adapter for ListView
    class TrainerAdapter extends BaseAdapter {
        @Override
        public int getCount() {
            return trainerNames.length;
        }

        @Override
        public Object getItem(int position) {
            return null;
        }

        @Override
        public long getItemId(int position) {
            return 0;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            if (convertView == null) {
                convertView = getLayoutInflater().inflate(R.layout.list_item, parent, false);
            }

            ImageView imageView = convertView.findViewById(R.id.trainer_image);
            TextView textView = convertView.findViewById(R.id.trainer_name);

            imageView.setImageResource(trainerImages[position]);
            textView.setText(trainerNames[position]);

            return convertView;
        }
    }
}
