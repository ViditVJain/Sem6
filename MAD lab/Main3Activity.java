package com.example.mahe.practice;

import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.ListView;
import android.widget.PopupMenu;
import android.widget.TextView;
import android.widget.TimePicker;
import android.widget.Toast;

import java.text.DateFormat;
import java.util.ArrayList;
import java.util.Calendar;

public class Main3Activity extends AppCompatActivity implements
        DatePickerDialog.OnDateSetListener,TimePickerDialog.OnTimeSetListener {
Button b1,date;
TextView t;
int day,month,year,hour,minute;
int dayf,monthf,yearf,hourf,minf;
    ArrayList<String> ar = new ArrayList<>();
ListView l;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main3);
        b1=(Button)findViewById(R.id.button);
        l=(ListView)findViewById(R.id.list);
        date=(Button)findViewById(R.id.button3);
        t=(TextView)findViewById(R.id.textView);
        ar.add("Banana");
        ar.add("Potato");
        ar.add("Cucumber");
        ar.add("Milk");

        ArrayAdapter theAdapt = new ArrayAdapter(this, android.R.layout.simple_list_item_1, ar);
        l.setAdapter(theAdapt);

        l.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int i, long id) {
                Toast.makeText(Main3Activity.this, "Selected item: " + ar.get(i).toString(), Toast.LENGTH_SHORT).show();
            }
        });
        registerForContextMenu(l);
    }

    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {
        super.onCreateContextMenu(menu, v, menuInfo);
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.main_context_menu, menu);
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo) item.getMenuInfo();
        switch (item.getItemId()) {
            case R.id.On:
                Toast.makeText(Main3Activity.this, "Hello 1", Toast.LENGTH_SHORT).show();
                return true;


        }
        return super.onContextItemSelected(item);
    }
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);

        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
    public void w(View view) {
        PopupMenu p=new PopupMenu(Main3Activity.this,view);
        p.getMenuInflater().inflate(R.menu.popup_menu,p.getMenu());
        p.show();
        p.setOnMenuItemClickListener(new PopupMenu.OnMenuItemClickListener() {
            @Override
            public boolean onMenuItemClick(MenuItem item) {
                Toast.makeText(Main3Activity.this,item.getTitle(),Toast.LENGTH_SHORT).show();
                return true;
            }
        });
    }

    public void view(View view) {
        Calendar c=Calendar.getInstance();
        year=c.get(Calendar.YEAR);
        month=c.get(Calendar.MONTH);
        day=c.get(Calendar.DAY_OF_MONTH);

        DatePickerDialog d=new DatePickerDialog(Main3Activity.this,Main3Activity.this,year,month,day);
        d.show();
    }

    @Override
    public void onDateSet(DatePicker view, int i1, int i2, int i3) {
        yearf=i1;
        monthf=i2+1;
        dayf=i3;
        Calendar c=Calendar.getInstance();
        hour=c.get(Calendar.HOUR);
        minute=c.get(Calendar.MINUTE);

        TimePickerDialog t=new TimePickerDialog(Main3Activity.this,Main3Activity.this,hour,minute,true);
        t.show();
    }

    @Override
    public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
        hourf=hourOfDay;
        minf=minute;
        t.setText(yearf + " \n "+monthf+ "\n "+ dayf + "\n "+hourf+ "\n "+ minf);

    }

    public void b(View view) {
        Intent i =new Intent(Main3Activity.this,Main2Activity.class);
        startActivity(i);
    }
}

