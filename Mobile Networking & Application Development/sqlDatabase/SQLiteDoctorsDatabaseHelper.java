package com.example.m1204231.mobilenetworking.sqlDatabase;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import java.util.ArrayList;

public class SQLiteDoctorsDatabaseHelper extends SQLiteOpenHelper {
    /* Initialise constants. */
    private static final int DATABASE_VERSION = 1;
    private static final String DATABASE_NAME = "SQLiteLabDB";
    private static final String DOCTORS_TABLE_NAME = "doctors";
    private static final String[] COLUMN_DOCTORS = {"First Name","Last Name", "User Name", "Password"};
    /* Construct CREATE query string. */
    private static final String DOCTORS_TABLE_CREATE =
            "CREATE TABLE " + DOCTORS_TABLE_NAME + " (" +
                    COLUMN_DOCTORS[0] + " TEXT, " +
                    COLUMN_DOCTORS[1] + " TEXT, " +
                    COLUMN_DOCTORS[2] + " TEXT, " +
                    COLUMN_DOCTORS[3] + " TEXT);";

    SQLiteDoctorsDatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        // Creates the database if it doesn't exist and adds the "contacts" table.
        /* Execute SQL query. */
        db.execSQL(DOCTORS_TABLE_CREATE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // can be left empty for the purposes of our tutorial
    }

    public void addDoctor(SQLiteDoctor c){
        /* Pack contact details in ContentValues object for database insertion. */
        ContentValues row = new ContentValues();
        row.put(this.COLUMN_DOCTORS[0], c.dr_first_name);
        row.put(this.COLUMN_DOCTORS[1], c.dr_second_name);
        row.put(this.COLUMN_DOCTORS[2], c.dr_user_name);
        row.put(this.COLUMN_DOCTORS[3], c.dr_login_password);
        // The first parameter is a column name, the second is a value.

        /* Get writable database and insert the new row to the "contacts" table. */
        SQLiteDatabase db = this.getWritableDatabase();
        db.insert(DOCTORS_TABLE_NAME, null, row);
        db.close();
    }

    public int getNumberOfDoctors(){
        /* Query the database and check the number of rows returned. */
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor result = db.query(DOCTORS_TABLE_NAME, COLUMN_DOCTORS, null, null, null, null, null, null);

        /* Make sure the query returned a valid result before trying to change text on screen.*/
        if(result != null) {
            /* Display result. */
            int contactsCount = result.getCount();
            db.close();
            return contactsCount;
        } else {
            return -1;
        }
    }

    public ArrayList<SQLiteDoctor> getContactsList(){
        /* Get the readable database. */
        SQLiteDatabase db = this.getReadableDatabase();

        /* Get all contacts by querying the database. */
        Cursor result = db.query(DOCTORS_TABLE_NAME, COLUMN_DOCTORS, null, null, null, null, null, null);

        /* Convert results to a list of Contact objects. */
        ArrayList<SQLiteDoctor> SQLiteDoctors = new ArrayList<SQLiteDoctor>();

        for(int i = 0; i < result.getCount(); i++){
            result.moveToPosition(i);
            /* Create a Contact object with using data from name, email, phone columns. Add it to list. */
            SQLiteDoctors.add(new SQLiteDoctor(result.getString(0), result.getString(1), result.getString(2), result.getString(3)));
        }

        return SQLiteDoctors;
    }

    public int removeDoctor(SQLiteDoctor c){
        SQLiteDatabase db = this.getWritableDatabase();
        String whereClause = "First Name = '" + c.dr_first_name + "' AND Second Name = '" + c.dr_second_name + "AND User Name = '" + c.dr_user_name + "' AND Password = '" + c.dr_login_password + "'";
        // Returns the number of affected rows. 0 means no rows were deleted.
        return db.delete(DOCTORS_TABLE_NAME, whereClause, null);
    }
}