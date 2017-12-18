package com.example.m1204231.mobilenetworking.sqlDatabase;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import com.example.m1204231.mobilenetworking.R;

import java.util.ArrayList;

public class SQLiteUserAdapter extends ArrayAdapter<SQLiteUser> {
    public SQLiteUserAdapter(Context context, ArrayList<SQLiteUser> SQLiteUsers){
        super(context, 0, SQLiteUsers);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        /* Get the contacts item for this position. */
        SQLiteUser SQLiteUser = getItem(position);
        /* Check if an existing view is being reused, otherwise inflate the view. */
        if (convertView == null) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.j_user_layout, parent, false);
        }
        /* Lookup view for data population. */
        TextView display_firstname = (TextView) convertView.findViewById(R.id.display_firstname);
        TextView display_secondname = (TextView) convertView.findViewById(R.id.display_secondname);
        TextView display_username = (TextView) convertView.findViewById(R.id.display_username);
        TextView display_password = (TextView) convertView.findViewById(R.id.display_password);

        /* Populate the data into the template view. */
        display_firstname.setText(SQLiteUser.first_name);
        display_secondname.setText(SQLiteUser.second_name);
        display_username.setText(SQLiteUser.user_name);
        display_password.setText(SQLiteUser.password);
        /* Return the completed view to render on screen. */
        return convertView;
    }
}