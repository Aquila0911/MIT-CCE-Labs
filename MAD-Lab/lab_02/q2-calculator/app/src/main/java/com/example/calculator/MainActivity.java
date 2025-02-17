package com.example.calculator;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.google.android.material.button.MaterialButton;

import java.text.DecimalFormat;

public class MainActivity extends AppCompatActivity {
    private static final char ADDITION = '+';
    private static final char SUBTRACTION = '-';
    private static final char MULTIPLICATION = '*';
    private static final char DIVISION = '/';
    private static final char PERCENT = '%';
    private char currentSymbol;
    private double firstValue = Double.NaN;
    private double secondValue;
    private TextView inputDisplay, outputDisplay;
    private DecimalFormat decimalFormat;

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

        decimalFormat = new DecimalFormat("#.##########");
        inputDisplay = findViewById(R.id.input);
        outputDisplay = findViewById(R.id.output);
        MaterialButton button0 = findViewById(R.id.btn0);
        MaterialButton button1 = findViewById(R.id.btn1);
        MaterialButton button2 = findViewById(R.id.btn2);
        MaterialButton button3 = findViewById(R.id.btn3);
        MaterialButton button4 = findViewById(R.id.btn4);
        MaterialButton button5 = findViewById(R.id.btn5);
        MaterialButton button6 = findViewById(R.id.btn6);
        MaterialButton button7 = findViewById(R.id.btn7);
        MaterialButton button8 = findViewById(R.id.btn8);
        MaterialButton button9 = findViewById(R.id.btn9);
        MaterialButton buttonAdd = findViewById(R.id.add);
        MaterialButton buttonSub = findViewById(R.id.subtract);
        MaterialButton buttonDivide = findViewById(R.id.division);
        MaterialButton buttonDot = findViewById(R.id.btnPoint);
        MaterialButton buttonMultiply = findViewById(R.id.multiply);
        MaterialButton buttonClear = findViewById(R.id.clear);
        MaterialButton buttonOFF = findViewById(R.id.off);
        MaterialButton buttonEqual = findViewById(R.id.equal);
        MaterialButton buttonPercent = findViewById(R.id.percent);

        button0.setOnClickListener(view -> inputDisplay.setText(inputDisplay.getText() + "0"));
        button1.setOnClickListener(view -> inputDisplay.setText(inputDisplay.getText() + "1"));
        button2.setOnClickListener(view -> inputDisplay.setText(inputDisplay.getText() + "2"));
        button3.setOnClickListener(view -> inputDisplay.setText(inputDisplay.getText() + "3"));
        button4.setOnClickListener(view -> inputDisplay.setText(inputDisplay.getText() + "4"));
        button5.setOnClickListener(view -> inputDisplay.setText(inputDisplay.getText() + "5"));
        button6.setOnClickListener(view -> inputDisplay.setText(inputDisplay.getText() + "6"));
        button7.setOnClickListener(view -> inputDisplay.setText(inputDisplay.getText() + "7"));
        button8.setOnClickListener(view -> inputDisplay.setText(inputDisplay.getText() + "8"));
        button9.setOnClickListener(view -> inputDisplay.setText(inputDisplay.getText() + "9"));
        buttonAdd.setOnClickListener(view -> {
            allCalculations();
            currentSymbol = ADDITION;
            outputDisplay.setText(decimalFormat.format(firstValue) + "+");
            inputDisplay.setText(null);
        });
        buttonSub.setOnClickListener(view -> {
            allCalculations();
            currentSymbol = SUBTRACTION;
            outputDisplay.setText(decimalFormat.format(firstValue) + "-");
            inputDisplay.setText(null);
        });
        buttonMultiply.setOnClickListener(view -> {
            allCalculations();
            currentSymbol = MULTIPLICATION;
            outputDisplay.setText(decimalFormat.format(firstValue) + "x");
            inputDisplay.setText(null);
        });
        buttonDivide.setOnClickListener(view -> {
            allCalculations();
            currentSymbol = DIVISION;
            outputDisplay.setText(decimalFormat.format(firstValue) + "/");
            inputDisplay.setText(null);
        });
        buttonPercent.setOnClickListener(view -> {
            allCalculations();
            currentSymbol = PERCENT;
            outputDisplay.setText(decimalFormat.format(firstValue) + "%");
            inputDisplay.setText(null);
        });
        buttonDot.setOnClickListener(view -> inputDisplay.setText(inputDisplay.getText() + "."));
        buttonClear.setOnClickListener(view -> {
            if (inputDisplay.getText().length() > 0) {
                CharSequence currentText = inputDisplay.getText();
                inputDisplay.setText(currentText.subSequence(0, currentText.length() - 1));
            } else {
                firstValue = Double.NaN;
                secondValue = Double.NaN;
                inputDisplay.setText("");
                outputDisplay.setText("");
            }
        });
        buttonOFF.setOnClickListener(view -> finish());
        buttonEqual.setOnClickListener(view -> {
            allCalculations();
            outputDisplay.setText(decimalFormat.format(firstValue));
            firstValue = Double.NaN;
            currentSymbol = '0';
        });
    }

    private void allCalculations(){
        if (!Double.isNaN(firstValue)) {
            secondValue = Double.parseDouble(inputDisplay.getText().toString());
            inputDisplay.setText(null);
            if (currentSymbol == ADDITION)
                firstValue = this.firstValue + secondValue;
            else if (currentSymbol == SUBTRACTION)
                firstValue = this.firstValue - secondValue;
            else if (currentSymbol == MULTIPLICATION)
                firstValue = this.firstValue * secondValue;
            else if (currentSymbol == DIVISION)
                firstValue = this.firstValue / secondValue;
            else if (currentSymbol == PERCENT)
                firstValue = this.firstValue % secondValue;
        } else {
            try {
                firstValue = Double.parseDouble(inputDisplay.getText().toString());
            } catch (NumberFormatException e) {
                Log.e("MainActivity", "Exception caught while executing the process.", e);
            }
        }
    }
}