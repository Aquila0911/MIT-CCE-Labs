package com.example.moviereview;


import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.RatingBar;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    EditText movieName, movieYear;
    RatingBar ratingBar;
    Button submitButton;
    ListView movieListView;
    TableLayout reviewTable;

    MovieDBHelper dbHelper;
    ArrayAdapter<String> listAdapter;
    ArrayList<String> movieList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        movieName = findViewById(R.id.movieName);
        movieYear = findViewById(R.id.movieYear);
        ratingBar = findViewById(R.id.ratingBar);
        submitButton = findViewById(R.id.submitButton);
        movieListView = findViewById(R.id.movieListView);
        reviewTable = findViewById(R.id.reviewTable);

        dbHelper = new MovieDBHelper(this);
        movieList = new ArrayList<>();

        listAdapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, movieList);
        movieListView.setAdapter(listAdapter);

        loadMovies();

        submitButton.setOnClickListener(v -> addReview());

        movieListView.setOnItemClickListener((parent, view, position, id) -> {
            String selectedMovie = movieList.get(position);
            displayMovieDetails(selectedMovie);
        });
    }

    private void addReview() {
        String name = movieName.getText().toString();
        String year = movieYear.getText().toString();
        int rating = (int) ratingBar.getRating();

        if (name.isEmpty() || year.isEmpty()) {
            Toast.makeText(this, "Please fill all fields", Toast.LENGTH_SHORT).show();
            return;
        }

        dbHelper.insertReview(name, year, rating);
        if (!movieList.contains(name)) {
            movieList.add(name);
            listAdapter.notifyDataSetChanged();
        }

        movieName.setText("");
        movieYear.setText("");
        ratingBar.setRating(0);
        Toast.makeText(this, "Review Added", Toast.LENGTH_SHORT).show();
    }

    private void loadMovies() {
        Cursor cursor = dbHelper.getAllMovies();
        if (cursor.moveToFirst()) {
            do {
                String name = cursor.getString(0);
                if (!movieList.contains(name)) {
                    movieList.add(name);
                }
            } while (cursor.moveToNext());
        }
        cursor.close();
    }

    private void displayMovieDetails(String movie) {
        reviewTable.removeAllViews();

        Cursor cursor = dbHelper.getMovieDetails(movie);
        if (cursor.moveToFirst()) {
            do {
                TableRow row = new TableRow(this);

                TextView yearView = new TextView(this);
                yearView.setText(cursor.getString(0));
                row.addView(yearView);

                TextView ratingView = new TextView(this);
                ratingView.setText(cursor.getString(1));
                row.addView(ratingView);

                reviewTable.addView(row);
            } while (cursor.moveToNext());
        }
        cursor.close();
    }

    static class MovieDBHelper extends SQLiteOpenHelper {

        private static final String DB_NAME = "movies.db";
        private static final int DB_VERSION = 1;

        private static final String TABLE_NAME = "reviews";

        public MovieDBHelper(Context context) {
            super(context, DB_NAME, null, DB_VERSION);
        }

        @Override
        public void onCreate(SQLiteDatabase db) {
            db.execSQL("CREATE TABLE " + TABLE_NAME + " (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, year TEXT, rating INTEGER)");
        }

        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
            onCreate(db);
        }

        public void insertReview(String name, String year, int rating) {
            SQLiteDatabase db = this.getWritableDatabase();
            ContentValues values = new ContentValues();
            values.put("name", name);
            values.put("year", year);
            values.put("rating", rating);
            db.insert(TABLE_NAME, null, values);
            db.close();
        }

        public Cursor getAllMovies() {
            SQLiteDatabase db = this.getReadableDatabase();
            return db.rawQuery("SELECT DISTINCT name FROM " + TABLE_NAME, null);
        }

        public Cursor getMovieDetails(String name) {
            SQLiteDatabase db = this.getReadableDatabase();
            return db.rawQuery("SELECT year, rating FROM " + TABLE_NAME + " WHERE name = ?", new String[]{name});
        }
    }
}
