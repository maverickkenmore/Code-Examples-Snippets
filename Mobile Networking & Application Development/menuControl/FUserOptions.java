package com.example.m1204231.mobilenetworking.menuControl;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.example.m1204231.mobilenetworking.pedometer.Pedometer;
import com.example.m1204231.mobilenetworking.R;

/**
 * Created by User on 18/04/2015.
 */


public class FUserOptions extends ActionBarActivity {

    private static Button pedometer_button1;
    private static Button results_graphical_button1;
    private static Button results_numerical_button1;
    private static Button log_off_button1;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.b_new_user);
        Log.d("Error Handling", "Selected View");

        // Get pointers to views defined in activity_main
        pedometer_button1 = (Button) findViewById(R.id.pedometer_button);
        results_graphical_button1 = (Button) findViewById(R.id.results_graphical_button);
        results_numerical_button1 = (Button) findViewById(R.id.results_numerical_button);
        log_off_button1 = (Button) findViewById(R.id.log_off_button);

    }


    public void callIntent(View view) {
        Intent intent = null;
        switch (view.getId()) {

            case R.id.log_off_button:
                intent = new Intent(this, AMainMenu.class);
                startActivity(intent);
                break;

            case R.id.pedometer_button:
                intent = new Intent(this, Pedometer.class);
                startActivity(intent);
                break;

            case R.id.results_graphical_button:
                intent = new Intent(this, HResultsGraphical.class);
                startActivity(intent);
                break;

            case R.id.results_numerical_button:
                intent = new Intent(this, IResultsNumerical.class);
                startActivity(intent);
                break;

            default:
                break;
        }
    }
}
