package com.example.m1204231.mobilenetworking.menuControl;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.View;

import com.example.m1204231.mobilenetworking.R;

/**
 * Created by User on 18/04/2015.
 */
public class ELoadingDataScreen extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.e_loading_data_screen);
        Log.d("Error Handling", "Selected View");

    }


    public void callIntent(View view) {
        Intent intent = null;
        switch (view.getId()) {


            case R.id.results_numerical_button:
                intent = new Intent(this, FUserOptions.class);
                startActivity(intent);
                break;

            default:
                break;
        }
    }
}
