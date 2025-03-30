package com.example.taskmanager;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Spinner;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.Arrays;

public class MainActivity extends AppCompatActivity {

    EditText taskName, dueDate;
    Spinner priority;
    Button addButton;
    ListView taskListView;

    DBHelper dbHelper;
    ArrayAdapter<String> adapter;
    ArrayList<String> taskList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        taskName = findViewById(R.id.taskName);
        dueDate = findViewById(R.id.dueDate);
        priority = findViewById(R.id.priority);
        addButton = findViewById(R.id.addButton);
        taskListView = findViewById(R.id.taskListView);

        dbHelper = new DBHelper(this);
        taskList = new ArrayList<>();

        adapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, taskList);
        taskListView.setAdapter(adapter);

        // Populate spinner with priority levels
        ArrayAdapter<String> priorityAdapter = new ArrayAdapter<>(this, android.R.layout.simple_spinner_item, Arrays.asList("High", "Medium", "Low"));
        priorityAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        priority.setAdapter(priorityAdapter);

        loadTasks();

        addButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                addTask();
            }
        });

        taskListView.setOnItemLongClickListener((parent, view, position, id) -> {
            String task = taskList.get(position);
            dbHelper.deleteTask(task);
            taskList.remove(position);
            adapter.notifyDataSetChanged();
            Toast.makeText(MainActivity.this, "Task Deleted", Toast.LENGTH_SHORT).show();
            return true;
        });
    }

    private void addTask() {
        String name = taskName.getText().toString();
        String date = dueDate.getText().toString();
        String level = priority.getSelectedItem().toString();

        if (!name.isEmpty() && !date.isEmpty()) {
            dbHelper.insertTask(name, date, level);
            taskList.add(name + " - " + date + " - " + level);
            adapter.notifyDataSetChanged();
            taskName.setText("");
            dueDate.setText("");
            Toast.makeText(this, "Task Added", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(this, "Please fill all fields", Toast.LENGTH_SHORT).show();
        }
    }

    private void loadTasks() {
        Cursor cursor = dbHelper.getTasks();
        if (cursor.moveToFirst()) {
            do {
                String name = cursor.getString(1);
                String date = cursor.getString(2);
                String level = cursor.getString(3);
                taskList.add(name + " - " + date + " - " + level);
            } while (cursor.moveToNext());
        }
        cursor.close();
    }

    static class DBHelper extends SQLiteOpenHelper {

        private static final String DB_NAME = "tasks.db";
        private static final int DB_VERSION = 1;
        private static final String TABLE_NAME = "tasks";

        public DBHelper(Context context) {
            super(context, DB_NAME, null, DB_VERSION);
        }

        @Override
        public void onCreate(SQLiteDatabase db) {
            db.execSQL("CREATE TABLE " + TABLE_NAME + " (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, due_date TEXT, priority TEXT)");
        }

        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
            onCreate(db);
        }

        public void insertTask(String name, String date, String priority) {
            SQLiteDatabase db = this.getWritableDatabase();
            ContentValues values = new ContentValues();
            values.put("name", name);
            values.put("due_date", date);
            values.put("priority", priority);
            db.insert(TABLE_NAME, null, values);
            db.close();
        }

        public Cursor getTasks() {
            SQLiteDatabase db = this.getReadableDatabase();
            return db.rawQuery("SELECT * FROM " + TABLE_NAME, null);
        }

        public void deleteTask(String task) {
            SQLiteDatabase db = this.getWritableDatabase();
            String name = task.split(" - ")[0];
            db.delete(TABLE_NAME, "name = ?", new String[]{name});
            db.close();
        }
    }
}
