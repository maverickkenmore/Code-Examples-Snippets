package com.example.m1204231.mobilenetworking.menuControl;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.example.m1204231.mobilenetworking.R;
import com.example.m1204231.mobilenetworking.sqlDatabase.BNewUser;

/**
 * Created by User on 18/04/2015.
 */
public class AMainMenu extends ActionBarActivity {

    private static Button login_button1;
    private static Button sign_up_button1;

    Intent intent = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.a_main_menu_screen);
        Log.d("Error Handling", "Selected View");

        // Get pointers to views defined in activity_main
        login_button1 = (Button) findViewById(R.id.login_button);
        sign_up_button1 = (Button) findViewById(R.id.sign_up_button);


    }

    public void callIntent(View view) {
        Intent intent = null;
        switch (view.getId()) {

            case R.id.login_button:
                intent = new Intent(this, DLoginScreen.class);
                Log.d("Button Works", "Button works in Intent Call");
                startActivity(intent);
                break;

            case R.id.sign_up_button:
                intent = new Intent(this, BNewUser.class);
                Log.d("Button Works", "Button works in Intent Call");
                startActivity(intent);
                break;

            default:
                break;
        }


    }
}
