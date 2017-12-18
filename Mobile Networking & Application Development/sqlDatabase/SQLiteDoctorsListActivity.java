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



public class SQLiteDoctorsListActivity extends Activity {

    private SQLiteDoctorsDatabaseHelper SQLiteDoctorsDatabaseHelper;
    private ListView list;

    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.k_dr_layout);

        list = (ListView)findViewById(R.id.list_doctors);

        list.setOnItemClickListener(new AdapterView.OnItemClickListener()
        {
            @Override
            public void onItemClick(AdapterView<?> arg0, View view,int position, long arg3)
            {
                deleteDoctorAndRefresh(view);
            }
        });

        /* Initialise the database our SQLiteOpenHelper object*/
        SQLiteDoctorsDatabaseHelper = new SQLiteDoctorsDatabaseHelper(this);

        populateList();
    }

    private void populateList(){
        /* Get contacts list from helper. */
        ArrayList<SQLiteDoctor> SQLiteDoctors = SQLiteDoctorsDatabaseHelper.getContactsList();

        /* Create a list adapter bound to the contacts list. */
        SQLiteDoctorsAdapter adapter = new SQLiteDoctorsAdapter(this, SQLiteDoctors);

        /* Attach the adapter to our list view. */
        list.setAdapter(adapter);
    }

    private void deleteDoctorAndRefresh(View view){
        /* Get text values from child views. */
        String first_name = ((TextView)view.findViewById(R.id.first_name_text)).getText().toString();
        String second_name = ((TextView)view.findViewById(R.id.second_name_text)).getText().toString();
        String user_name = ((TextView)view.findViewById(R.id.user_name_text)).getText().toString();
        String password = ((TextView)view.findViewById(R.id.password_text)).getText().toString();

        /* Query the database. */
        int result = SQLiteDoctorsDatabaseHelper.removeDoctor(new SQLiteDoctor(first_name, second_name, user_name, password));

        /* Display toast notifying user of the number of deleted rows.  */
        Toast.makeText(SQLiteDoctorsListActivity.this, result + " contacts were deleted from the database.", Toast.LENGTH_SHORT).show();

        /* Refresh the list of contacts. */
        populateList();
    }

}
