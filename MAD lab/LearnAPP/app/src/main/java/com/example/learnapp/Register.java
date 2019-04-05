package com.example.learnapp;

import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.Intent;
import android.graphics.Color;
import android.support.constraint.ConstraintLayout;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.TimePicker;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

public class Register extends AppCompatActivity implements TimePickerDialog.OnTimeSetListener, DatePickerDialog.OnDateSetListener {
    TextView txt, datepick;
    Button btn;
    Button submit_btn;
    RadioButton rM;
    RadioButton rF;
    EditText editText2;
    EditText editText3, timepick;
    ToggleButton toggleBtn;
    CheckBox colourBox;
    ConstraintLayout myLayout;
    Spinner spinner2;

    int hour, minute, year, month, day;
    Calendar c;
//    Spinner spinner1 = findViewById(R.id.spinner);
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);
        Intent intent = getIntent();
        String mesg = intent.getStringExtra(MainActivity.extra_thing);
//        Toast.makeText(this, mesg, Toast.LENGTH_LONG).show();
        txt = (TextView) findViewById(R.id.textView);
        txt.setText(mesg);

        myLayout = findViewById(R.id.myLayout);

        c = Calendar.getInstance();



        // DATE PICKER --------------------------------------
        datepick = findViewById(R.id.datepick);
        datepick.setText(Integer.toString(c.get(Calendar.DAY_OF_MONTH))+"/"+
                Integer.toString(c.get(Calendar.MONTH))+"/"+
                Integer.toString(c.get(Calendar.YEAR)));
        datepick.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                DatePickerDialog d = new DatePickerDialog(Register.this, Register.this, 2008, month, day);
                d.show();
            }
        });

        // TIME PICKER -------------------------------------
        timepick = findViewById(R.id.timepick);
        timepick.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                TimePickerDialog t = new TimePickerDialog(Register.this, Register.this, hour, minute, false);
                t.show();
            }
        });


        // SPINNER ------------------------------
        spinner2 = findViewById(R.id.spinner2);
        setSpinner();
        spinner2.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                String itemGot = parent.getItemAtPosition(position).toString();
                Toast.makeText(Register.this, itemGot, Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });
//        spinner2.getSelectedItem().toString();

        // CHECKBOX -------------------------
        colourBox = findViewById(R.id.checkBox);
        colourBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
//                    txt.setVisibility(View.VISIBLE);
                    myLayout.setBackgroundColor(Color.BLUE);
                }
                else{
//                    txt.setVisibility(View.INVISIBLE);
                    myLayout.setBackgroundColor(Color.WHITE);
                }
            }
        });

        // TOGGLEBUTTON ----------------------
        rM = findViewById(R.id.radioButtonM);
        rF = findViewById(R.id.radioButtonF);
        rF.setChecked(true);

        toggleBtn = findViewById(R.id.toggleButton);

        toggleBtn.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    txt.setVisibility(View.VISIBLE);
//                    bu.setBackgroundColor(333);
                }
                else{
                    txt.setVisibility(View.INVISIBLE);
//                    buttonView.setBackgroundColor(777);
                }

            }
        });

        // BUTTON ---------------------
        btn = (Button) findViewById(R.id.button2);
        btn.setOnClickListener(new View.OnClickListener(){
            public void onClick(View view){
                startActivity(new Intent(Register.this, MainActivity.class));
            }
        });

        // RADIOBUTTON ------------------------
        submit_btn = (Button) findViewById(R.id.submit_button);
        submit_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                editText2 = findViewById(R.id.editText2);
                editText3 = findViewById(R.id.editText3);

                if(rM.isChecked() ){
                    txt.setVisibility(View.INVISIBLE);
                }
                else{
                    txt.setVisibility(View.VISIBLE);
                }
                String displaytxt = editText2.getText().toString()
                        + "\n" + editText3.getText().toString()
                        + "\n" + spinner2.getSelectedItem().toString();
//                        + "\n" + spinner1.getSelectedItem().toString();
                txt.setText(displaytxt);
            }
        });
    }

    // SPINNER -------------------------------------------------------------------
    public void setSpinner(){
        List<String> items = new ArrayList<String>();
        items.add("Well Hello");
        items.add("Well Hi");
        items.add("Well High");
        ArrayAdapter<String> dataAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, items);
        dataAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner2.setAdapter(dataAdapter);


    }

    // DATE-TIME PICKERS --------------------------------------------------
    @Override
    public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
        String timeShow = Integer.toString(hourOfDay)+":"+Integer.toString(minute);
        Toast.makeText(this, timeShow, Toast.LENGTH_SHORT).show();
        timepick.setText(timeShow);
    }

    @Override
    public void onDateSet(DatePicker view, int year, int month, int dayOfMonth) {
        datepick.setText((Integer.toString(dayOfMonth)+"/"+Integer.toString(month+1)+"/"+Integer.toString(year)));
    }
//    public void toLogin(View view){
//        Intent intent = new Intent(this, MainActivity.class);
//        startActivity(new Intent(this, MainActivity.class));
//    }


    // MENU ----------------------------------------------------------
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater men = getMenuInflater();
        men.inflate(R.menu.menu, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()){
            case R.id.eggs:
                startActivity(new Intent(this, Eggs.class));
                break;
            case R.id.bread:
                Toast.makeText(this, "Bread!", Toast.LENGTH_SHORT).show();
                break;
            case R.id.milk:
                Toast.makeText(this, "Milk!", Toast.LENGTH_SHORT).show();
                break;
        }
        return super.onOptionsItemSelected(item);
    }

}
