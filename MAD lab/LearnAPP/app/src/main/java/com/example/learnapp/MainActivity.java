package com.example.learnapp;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    EditText editText;
    public static String extra_thing;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    protected void onStart() {
        super.onStart();
        Toast.makeText(this, "hello", Toast.LENGTH_SHORT).show();
    }

    public void toRegister(View view){
        editText = (EditText) findViewById(R.id.editText);
        String mesg = editText.getText().toString();
        Intent intent = new Intent(this, Register.class);
        intent.putExtra(extra_thing, mesg);
        startActivity(intent);
    }
}
