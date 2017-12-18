package com.example.m1204231.mobilenetworking.sqlDatabase;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.m1204231.mobilenetworking.R;

import java.util.ArrayList;

public class SQLiteUserListActivity extends Activity {

    private SQLiteUserDatabaseHelper SQLiteUserDatabaseHelper;
    private ListView list;

    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.j_user_layout);

        list = (ListView)findViewById(R.id.list_users);

        list.setOnItemClickListener(new AdapterView.OnItemClickListener()
        {
            @Override
            public void onItemClick(AdapterView<?> arg0, View view,int position, long arg3)
            {
                deleteUserAndRefresh(view);
            }
        });

        /* Initialise the database our SQLiteOpenHelper object*/
        SQLiteUserDatabaseHelper = new SQLiteUserDatabaseHelper(this);

        populateList();
    }

    private void populateList(){
        /* Get contacts list from helper. */
        ArrayList<SQLiteUser> SQLiteUsers = SQLiteUserDatabaseHelper.getUserList();

        /* Create a list adapter bound to the contacts list. */
        SQLiteUserAdapter adapter = new SQLiteUserAdapter(this, SQLiteUsers);

        /* Attach the adapter to our list view. */
        list.setAdapter(adapter);
    }

    private void deleteUserAndRefresh(View view){
        /* Get text values from child views. */
        String first_name = ((TextView)view.findViewById(R.id.display_firstname)).getText().toString();
        String second_name = ((TextView)view.findViewById(R.id.display_secondname)).getText().toString();
        String user_name = ((TextView)view.findViewById(R.id.display_username)).getText().toString();
        String password = ((TextView)view.findViewById(R.id.display_password)).getText().toString();

        /* Query the database. */
        int result = SQLiteUserDatabaseHelper.removeUser(new SQLiteUser(first_name, second_name, user_name, password));

        /* Display toast notifying user of the number of deleted rows.  */
        Toast.makeText(SQLiteUserListActivity.this, result + " contacts were deleted from the database.", Toast.LENGTH_SHORT).show();

        /* Refresh the list of contacts. */
        populateList();
    }

}
