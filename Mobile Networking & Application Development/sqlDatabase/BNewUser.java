package com.example.m1204231.mobilenetworking.sqlDatabase;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.example.m1204231.mobilenetworking.R;
import com.example.m1204231.mobilenetworking.menuControl.AMainMenu;
import com.example.m1204231.mobilenetworking.menuControl.CCompleteRegistration;
import com.example.m1204231.mobilenetworking.sqlDatabase.SQLiteUser;
import com.example.m1204231.mobilenetworking.sqlDatabase.SQLiteUserDatabaseHelper;
import com.example.m1204231.mobilenetworking.sqlDatabase.SQLiteUserAdapter;
import com.example.m1204231.mobilenetworking.sqlDatabase.SQLiteUserListActivity;

import java.util.ArrayList;

/**
 * Created by User on 18/04/2015.
 */
public class BNewUser extends ActionBarActivity {

    private EditText field_first_name;
    private EditText field_second_name;
    private EditText field_user_name;
    private EditText field_password;
    private EditText field_retypepassword;

    private static Button back_button1;
    private static Button confirm_button1;

    private static Button view_users_button1;

    private SQLiteUserDatabaseHelper userDatabaseHelper;
    private SQLiteUserRemoteDatabaseHelper SQLiteUserRemoteDatabaseHelper;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.b_new_user);
        Log.d("Error Handling", "Selected View");


        /* Initialise our SQLiteOpenHelper object. */
        userDatabaseHelper = new SQLiteUserDatabaseHelper(this);
        /* Initialise the remote DB helper object. */
        SQLiteUserRemoteDatabaseHelper = new SQLiteUserRemoteDatabaseHelper(this);


        // Get pointers to views defined in activity_main
        field_first_name = (EditText)findViewById(R.id.first_name_edit);
        field_second_name = (EditText)findViewById(R.id.second_name_edit);
        field_user_name = (EditText)findViewById(R.id.user_name_edit);
        field_password = (EditText)findViewById(R.id.password_edit);
        field_retypepassword = (EditText)findViewById(R.id.retype_password_edit);

        back_button1 = (Button) findViewById(R.id.back_button);
        confirm_button1 = (Button) findViewById(R.id.confirm_button);
        view_users_button1 = (Button) findViewById(R.id.confirm_button);

    }

    public interface MyMessageDialogListener {
        public void onClosed(String firstname, String secondname, String username, String password, String retypedpassword);
    }

    public void callIntent(View view) {
        Intent intent = null;

        String firstname = field_first_name.getText().toString();
        String secondname = field_second_name.getText().toString();
        String username = field_user_name.getText().toString();
        String password = field_password.getText().toString();
        String retypepassword = field_retypepassword.getText().toString();

        switch (view.getId()) {

            case R.id.back_button:
                intent = new Intent(this, AMainMenu.class);
                startActivity(intent);
                break;

            case R.id.view_users_button:
                intent = new Intent(this, SQLiteUserListActivity.class);
                startActivity(intent);
                break;

            case R.id.confirm_button:
                if(field_password != null && field_retypepassword != null)
                {
                    intent = new Intent(this, CCompleteRegistration.class);
                    if(password.equals(retypepassword))
                    {
                        SQLiteUserRemoteDatabaseHelper.addUser(new SQLiteUser(firstname, secondname, username, password));
                        addToContacts(view);
                        startActivity(intent);
                    }


                }
                break;

            default:
                break;
        }
    }



    // called when button is pressed
    public void addToContacts(View v) {
        /* Get entered fields data. */
        String firstname = field_first_name.getText().toString();
        String secondname = field_second_name.getText().toString();
        String username = field_user_name.getText().toString();
        String password = field_password.getText().toString();


        if (!userDatabaseHelper.userExists(new SQLiteUser(firstname, secondname, username, password)))
        {

            /* Construct a Contact object and pass it to the helper for database insertion */
            userDatabaseHelper.addUser(new SQLiteUser(firstname, secondname, username, password));

            /* Also pass it ot the remote DB helper for external DB insertion. */
            SQLiteUserRemoteDatabaseHelper.addUser(new SQLiteUser(firstname, secondname, username, password));


        } else {
            Toast.makeText(this, "Contact already exists!", Toast.LENGTH_SHORT).show();
        }

        /* Optional: clear the fields after the entry is added to the database.  */
        field_first_name.setText("");
        field_second_name.setText("");
        field_user_name.setText("");
        field_password.setText("");

    }

    public void downloadBackup(View v) {
        /* Download contacts from remote database. */
        ArrayList<SQLiteUser> users = SQLiteUserRemoteDatabaseHelper.getUserList();
        int count = 0;
        for(int i = 0; i < users.size(); i++){
            SQLiteUser c = users.get(i);
            /* Check if contact already exists in the local database. */
            if(!userDatabaseHelper.userExists(c)){
                /* If not, add it. */
                SQLiteUserRemoteDatabaseHelper.addUser(c);
                /* Count added contacts. */
                count++;
            }
        }
        Toast.makeText(this, count + " contacts were recovered!", Toast.LENGTH_SHORT).show();

    }


}
