package com.example.m1204231.mobilenetworking;

import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

import com.example.m1204231.mobilenetworking.sqlDatabase.BNewUser;
import com.example.m1204231.mobilenetworking.menuControl.DLoginScreen;


public class MainActivity extends ActionBarActivity {

    private static Button login_button1;
    private static Button sign_up_button1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.a_main_menu_screen);
        Log.d("Error Handling", "Selected View");

        // Get pointers to views defined in activity_main
        login_button1 = (Button) findViewById(R.id.login_button);
        sign_up_button1 = (Button) findViewById(R.id.sign_up_button);

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




    public void callIntent(View view) {
        Intent intent = null;
        switch (view.getId()) {

            case R.id.login_button:
                intent = new Intent(this, DLoginScreen.class);
                startActivity(intent);
                break;

            case R.id.sign_up_button:
                intent = new Intent(this, BNewUser.class);
                startActivity(intent);
                break;

            default:
                break;
        }

    }

}
