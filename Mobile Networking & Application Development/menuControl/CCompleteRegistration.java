package com.example.m1204231.mobilenetworking.menuControl;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.example.m1204231.mobilenetworking.R;

/**
 * Created by User on 18/04/2015.
 */
public class CCompleteRegistration extends ActionBarActivity {

    private static Button confirm_button1;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.c_completed_registration);
        Log.d("Error Handling", "Selected View");

        // Get pointers to views defined in activity_main
        confirm_button1 = (Button) findViewById(R.id.confirm_button);

    }

    public void callIntent(View view) {
        Intent intent = null;
        switch (view.getId()) {


            case R.id.confirm_button:
                intent = new Intent(this, AMainMenu.class);
                startActivity(intent);
                break;

            default:
                break;
        }
    }
}
