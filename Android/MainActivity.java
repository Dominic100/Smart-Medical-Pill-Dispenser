package com.example.nodemcu_conn;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    // UI components
    private EditText ipxx1; // EditText for entering an IP address
    private static Button led; // Button for controlling an LED
    public static String texr; // Static variable to store the IP address

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // Set the theme before calling setContentView
        setTheme(R.style.AppTheme);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize UI components
        led = findViewById(R.id.click); // Find the Button with ID "click" in the layout
        ipxx1 = findViewById(R.id.ipadd); // Find the EditText with ID "ipadd" in the layout

        // Set a click listener for the LED button
        led.setOnClickListener(view -> {
            //texr = ipxx1.getText().toString(); // Uncomment this line to get IP from the EditText
            texr = "192.168.21.93"; // Hardcoded IP address (commented line suggests dynamic input)

            // Create an Intent to start the Dispense_activity class
            Intent ht1 = new Intent(MainActivity.this, Dispense_activity.class);

            // Start the Dispense_activity
            startActivity(ht1);
        });
    }
}
