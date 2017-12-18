package com.example.m1204231.mobilenetworking.sqlDatabase;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import com.example.m1204231.mobilenetworking.R;

import java.util.ArrayList;

public class SQLiteDoctorsAdapter extends ArrayAdapter<SQLiteDoctor> {
    public SQLiteDoctorsAdapter(Context context, ArrayList<SQLiteDoctor> SQLiteDoctors){
        super(context, 0, SQLiteDoctors);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        /* Get the contacts item for this position. */
        SQLiteDoctor SQLiteDoctor = getItem(position);
        /* Check if an existing view is being reused, otherwise inflate the view. */
        if (convertView == null) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.i_results_numeric, parent, false);
        }
        /* Lookup view for data population. */
        TextView display_first_name = (TextView) convertView.findViewById(R.id.first_name_text);
        TextView display_last_name = (TextView) convertView.findViewById(R.id.second_name_text);
        TextView display_user_name = (TextView) convertView.findViewById(R.id.user_name_text);
        TextView display_password = (TextView) convertView.findViewById(R.id.password_text);
        /* Populate the data into the template view. */
        display_first_name.setText(SQLiteDoctor.dr_first_name);
        display_last_name.setText(SQLiteDoctor.dr_second_name);
        display_user_name.setText(SQLiteDoctor.dr_user_name);
        display_password.setText(SQLiteDoctor.dr_login_password);
        /* Return the completed view to render on screen. */
        return convertView;
    }
}