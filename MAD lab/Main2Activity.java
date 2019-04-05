package com.example.mahe.practice;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.ContextMenu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.ListView;
import android.widget.PopupMenu;
import android.widget.RadioButton;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.util.ArrayList;
import java.util.List;

public class Main2Activity extends AppCompatActivity implements CompoundButton.OnCheckedChangeListener {
    ToggleButton t1;
    RadioButton r1,r2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
r1=(RadioButton)findViewById(R.id.radioButton);
r2=(RadioButton)findViewById(R.id.radioButton2);
        t1 =  findViewById(R.id.toggle);



       t1.setOnCheckedChangeListener(this);

    }


    @Override
   public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
        if (isChecked == true) {
            Toast.makeText(Main2Activity.this, "On", Toast.LENGTH_SHORT).show();
        } else
            Toast.makeText(Main2Activity.this, "Off", Toast.LENGTH_SHORT).show();

    }
    public void go(View view) {
        boolean checked = ((RadioButton) view).isChecked();

        switch (view.getId()) {
            case R.id.radioButton:
                if (checked) {
                    Toast.makeText(Main2Activity.this, "button 1 checked", Toast.LENGTH_SHORT).show();
                    r2.setChecked(false);

                }

            case R.id.radioButton2:
                if (checked) {
                    Toast.makeText(Main2Activity.this, "button 2 checked", Toast.LENGTH_SHORT).show();
                    r1.setChecked(false);
                }

        }
    }

}

