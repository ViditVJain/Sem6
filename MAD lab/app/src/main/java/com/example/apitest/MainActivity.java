package com.example.apitest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class MainActivity extends AppCompatActivity {
    String data = "";
    TextView display;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void apiCall(View view) {
        Toast.makeText(getApplicationContext(),"Hello before",Toast.LENGTH_SHORT).show();
        try {
            URL url = new URL("http://ws.audioscrobbler.com/2.0/?method=artist.getsimilar&artist=cher&api_key=d4d8ce6b7f878903fd54602d00a66f0d&format=json");
            HttpURLConnection httpurlconnection = (HttpURLConnection) url.openConnection();
            InputStream inputStream = httpurlconnection.getInputStream();
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            String line = "";
            while (line != null){
                line = bufferedReader.readLine();
                data = data + line;
            }

        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        display = findViewById(R.id.textView);
        display.setText(data);
        Toast.makeText(getApplicationContext(),"Hello after",Toast.LENGTH_SHORT).show();

    }
}
