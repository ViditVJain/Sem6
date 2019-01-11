package raghav.lab2;

import android.app.Dialog;
import android.support.v4.app.DialogFragment;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

//    public class myDialog extends DialogFragment {
//        public Dialog onCreateDialog(Bundle savedInstanceState) {
//            AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
//            builder.setMessage("Hello Dialog");
//            return builder.create();
//        }
//    }

    public void doThings(View view){
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage("Hello Dialog");

        AlertDialog alertDialog = builder.create();
        alertDialog.show();
    }

}

