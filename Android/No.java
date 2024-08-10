package com.example.nodemcu_conn;

import android.os.AsyncTask;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import static com.example.nodemcu_conn.MainActivity.texr;

// AsyncTask is used to perform background tasks asynchronously
public class No extends AsyncTask<Void, Void, Void> {

    // This method performs the background task on a separate thread
    @Override
    protected Void doInBackground(Void... voids) {
        try {
            // Construct the URL for the HTTP request
            URL url = new URL("http://" + texr + "/no");

            // Open a connection to the specified URL
            HttpURLConnection httpUrlConnection = (HttpURLConnection) url.openConnection();

            // Get the input stream from the connection
            InputStream inputStream = httpUrlConnection.getInputStream();

            // Create a BufferedReader to read from the input stream
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));

            // Read the response if needed (not implemented in this example)

        } catch (MalformedURLException e) {
            // Handle URL-related exceptions
            e.printStackTrace();
        } catch (IOException e) {
            // Handle IO-related exceptions
            e.printStackTrace();
        }

        // Return null as the result type is Void
        return null;
    }

    // This method is called after the background task is completed
    @Override
    protected void onPostExecute(Void aVoid) {
        super.onPostExecute(aVoid);
        // Code to run after the task is completed (if needed)
    }
}
