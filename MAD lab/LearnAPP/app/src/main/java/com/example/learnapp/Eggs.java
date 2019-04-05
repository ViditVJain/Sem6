package com.example.learnapp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

public class Eggs extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_eggs);
        Toast.makeText(this, "Eggs!", Toast.LENGTH_SHORT).show();
    }
}
