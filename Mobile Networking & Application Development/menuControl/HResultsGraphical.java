package com.example.m1204231.mobilenetworking.menuControl;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.example.m1204231.mobilenetworking.R;

/**
 * Created by User on 19/04/2015.
 */
public class HResultsGraphical extends ActionBarActivity {


    private static Button calories_burned_button1;
    private static Button back_button1;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.h_graph_layout);
        Log.d("Error Handling", "Selected View");

        // Get pointers to views defined in activity_main
        calories_burned_button1 = (Button) findViewById(R.id.calories_burned_button);
        back_button1 = (Button) findViewById(R.id.back_button);


    }

    public void callIntent(View view) {
        Intent intent = null;
        switch (view.getId()) {

            case R.id.calories_burned_button:
                intent = new Intent(this, HResultsGraphical.class);
                startActivity(intent);
                break;

            case R.id.back_button:
                intent = new Intent(this, FUserOptions.class);
                startActivity(intent);
                break;

            default:
                break;
        }
    }
}
