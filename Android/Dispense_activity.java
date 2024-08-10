// Import necessary packages and classes
package com.example.nodemcu_conn;

import androidx.appcompat.app.AppCompatActivity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

// Declare the main activity class, extending AppCompatActivity
public class Dispense_activity extends AppCompatActivity {

    // Declare private member variables for buttons and an EditText
    private Button Dispense, No;
    private EditText editTextMessage;

    // Override the onCreate method, called when the activity is created
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // Call the superclass onCreate method
        super.onCreate(savedInstanceState);
        // Set the content view to the layout defined in activity_dispense.xml
        setContentView(R.layout.activity_dispense);

        // Initialize Button and EditText objects by finding views with their respective IDs
        Dispense = findViewById(R.id.btnDispense);
        No = findViewById(R.id.btnNo);
        editTextMessage = findViewById(R.id.editTextMessage);

        // Set a click listener for the Dispense button
        Dispense.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Get the text from the editTextMessage and convert it to a string
                String message = editTextMessage.getText().toString();
                // Create a new instance of the Dispense class (Assuming Dispense is an AsyncTask)
                Dispense process1 = new Dispense();
                // Execute the AsyncTask on a separate thread, passing the message as a parameter
                process1.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, message);
            }
        });

        // Set a click listener for the No button
        No.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Create a new instance of the No class (Assuming No is an AsyncTask)
                No process1 = new No();
                // Execute the AsyncTask on a separate thread
                process1.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
            }
        });
    }
}
