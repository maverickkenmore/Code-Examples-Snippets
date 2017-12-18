package com.example.m1204231.mobilenetworking.pedometer;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.example.m1204231.mobilenetworking.menuControl.FUserOptions;
import com.example.m1204231.mobilenetworking.R;

/**
 * Created by User on 18/04/2015.
 */
public class Pedometer extends ActionBarActivity {

    private static Button pause_resume_button1;
    private static Button back_button1;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.g_pedometer);
        Log.d("Error Handling", "Selected View");

        // Get pointers to views defined in activity_main
        back_button1 = (Button) findViewById(R.id.back_button);
        pause_resume_button1 = (Button) findViewById(R.id.pause_resume_button);

    }


    public void callIntent(View view) {
        Intent intent = null;
        switch (view.getId()) {

            case R.id.back_button:
                intent = new Intent(this, FUserOptions.class);
                break;

            case R.id.pause_resume_button:
                break;

            default:
                break;
        }
    }
}
