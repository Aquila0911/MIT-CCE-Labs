package com.example.grocery;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    Spinner itemSpinner;
    Button addButton, calculateButton;
    TextView totalCostTextView;

    GroceryDBHelper dbHelper;
    ArrayAdapter<String> spinnerAdapter;
    ArrayList<String> itemList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        itemSpinner = findViewById(R.id.itemSpinner);
        addButton = findViewById(R.id.addButton);
        calculateButton = findViewById(R.id.calculateButton);
        totalCostTextView = findViewById(R.id.totalCostTextView);

        dbHelper = new GroceryDBHelper(this);

        itemList = new ArrayList<>();
        loadItems();

        spinnerAdapter = new ArrayAdapter<>(this, android.R.layout.simple_spinner_item, itemList);
        spinnerAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        itemSpinner.setAdapter(spinnerAdapter);

        addButton.setOnClickListener(v -> addItem());

        calculateButton.setOnClickListener(v -> {
            int totalCost = dbHelper.getTotalCost();
            totalCostTextView.setText("Total Cost: " + totalCost);
        });
    }

    private void loadItems() {
        // Add sample items if database is empty
        if (dbHelper.getItemCount() == 0) {
            dbHelper.insertItem("Apple", 30);
            dbHelper.insertItem("Banana", 10);
            dbHelper.insertItem("Milk", 50);
            dbHelper.insertItem("Bread", 40);
        }

        Cursor cursor = dbHelper.getAllItems();
        if (cursor.moveToFirst()) {
            do {
                String itemName = cursor.getString(1);
                int itemCost = cursor.getInt(2);
                itemList.add(itemName + " - Rs." + itemCost);
            } while (cursor.moveToNext());
        }
        cursor.close();
    }

    private void addItem() {
        String selectedItem = (String) itemSpinner.getSelectedItem();
        if (selectedItem != null) {
            String[] parts = selectedItem.split(" - Rs.");
            String itemName = parts[0];

            dbHelper.addSelectedItem(itemName);
            Toast.makeText(this, "Item Added: " + itemName, Toast.LENGTH_SHORT).show();
        }
    }

    static class GroceryDBHelper extends SQLiteOpenHelper {

        private static final String DB_NAME = "grocery.db";
        private static final int DB_VERSION = 1;

        private static final String ITEM_TABLE = "items";
        private static final String SELECTED_ITEM_TABLE = "selected_items";

        public GroceryDBHelper(Context context) {
            super(context, DB_NAME, null, DB_VERSION);
        }

        @Override
        public void onCreate(SQLiteDatabase db) {
            db.execSQL("CREATE TABLE " + ITEM_TABLE + " (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, cost INTEGER)");
            db.execSQL("CREATE TABLE " + SELECTED_ITEM_TABLE + " (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
        }

        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            db.execSQL("DROP TABLE IF EXISTS " + ITEM_TABLE);
            db.execSQL("DROP TABLE IF EXISTS " + SELECTED_ITEM_TABLE);
            onCreate(db);
        }

        public void insertItem(String name, int cost) {
            SQLiteDatabase db = this.getWritableDatabase();
            ContentValues values = new ContentValues();
            values.put("name", name);
            values.put("cost", cost);
            db.insert(ITEM_TABLE, null, values);
            db.close();
        }

        public Cursor getAllItems() {
            SQLiteDatabase db = this.getReadableDatabase();
            return db.rawQuery("SELECT * FROM " + ITEM_TABLE, null);
        }

        public int getItemCount() {
            SQLiteDatabase db = this.getReadableDatabase();
            Cursor cursor = db.rawQuery("SELECT COUNT(*) FROM " + ITEM_TABLE, null);
            int count = 0;
            if (cursor.moveToFirst()) {
                count = cursor.getInt(0);
            }
            cursor.close();
            return count;
        }

        public void addSelectedItem(String name) {
            SQLiteDatabase db = this.getWritableDatabase();
            ContentValues values = new ContentValues();
            values.put("name", name);
            db.insert(SELECTED_ITEM_TABLE, null, values);
            db.close();
        }

        public int getTotalCost() {
            SQLiteDatabase db = this.getReadableDatabase();
            String query = "SELECT SUM(cost) FROM " + ITEM_TABLE + " WHERE name IN (SELECT name FROM " + SELECTED_ITEM_TABLE + ")";
            Cursor cursor = db.rawQuery(query, null);
            int total = 0;
            if (cursor.moveToFirst()) {
                total = cursor.getInt(0);
            }
            cursor.close();
            return total;
        }
    }
}
