package com.example.m1204231.mobilenetworking.sqlDatabase;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import java.util.ArrayList;

public class SQLiteUserDatabaseHelper extends SQLiteOpenHelper {
    /* Initialise constants. */
    private static final int DATABASE_VERSION = 1;
    private static final String DATABASE_NAME = "SQLiteLabDB";
    private static final String USERS_TABLE_NAME = "Users";
    private static final String[] COLUMN_USERS = {"First Name","Last Name","Username", "Password"};
    /* Construct CREATE query string. */
    private static final String USERS_TABLE_CREATE =
            "CREATE TABLE " + USERS_TABLE_NAME + " (" +
                    COLUMN_USERS[0] + " TEXT, " +
                    COLUMN_USERS[1] + " TEXT, " +
                    COLUMN_USERS[2] + " TEXT, " +
                    COLUMN_USERS[3] + " TEXT);";

    SQLiteUserDatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        // Creates the database if it doesn't exist and adds the "contacts" table.
        /* Execute SQL query. */
        db.execSQL(USERS_TABLE_CREATE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // can be left empty for the purposes of our tutorial
    }

    public void addUser(SQLiteUser c){
        /* Pack contact details in ContentValues object for database insertion. */
        ContentValues row = new ContentValues();
        row.put(this.COLUMN_USERS[0], c.first_name);
        row.put(this.COLUMN_USERS[1], c.second_name);
        row.put(this.COLUMN_USERS[2], c.user_name);
        row.put(this.COLUMN_USERS[3], c.password);
        // The first parameter is a column name, the second is a value.

        /* Get writable database and insert the new row to the "contacts" table. */
        SQLiteDatabase db = this.getWritableDatabase();
        db.insert(USERS_TABLE_NAME, null, row);
        db.close();
    }

    public int getNumberOfUsers(){
        /* Query the database and check the number of rows returned. */
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor result = db.query(USERS_TABLE_NAME, COLUMN_USERS, null, null, null, null, null, null);

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


    public boolean userExists(SQLiteUser user){
        /* Check if contact exists in the local database. */
        ArrayList<SQLiteUser> existingUsers = getUserList();
        for(int i = 0; i < existingUsers.size(); i++){
            /* Go through all existing contacts and compare the details to a given contact. */
            SQLiteUser c = existingUsers.get(i);
            if(c.first_name.equals(user.first_name) && c.second_name.equals(user.second_name) && c.user_name.equals(user.user_name) && c.password.equals(user.password)){
                /* If everything matches up, return true. */
                return true;
            }
        }
        /* If nothing matches up, return false. */
        return false;
    }

    public ArrayList<SQLiteUser> getUserList(){
        /* Get the readable database. */
        SQLiteDatabase db = this.getReadableDatabase();

        /* Get all contacts by querying the database. */
        Cursor result = db.query(USERS_TABLE_NAME, COLUMN_USERS, null, null, null, null, null, null);

        /* Convert results to a list of Contact objects. */
        ArrayList<SQLiteUser> SQLiteUser = new ArrayList<SQLiteUser>();

        for(int i = 0; i < result.getCount(); i++){
            result.moveToPosition(i);
            /* Create a Contact object with using data from name, email, phone columns. Add it to list. */
            SQLiteUser.add(new SQLiteUser(result.getString(0), result.getString(1), result.getString(2), result.getString(3)));
        }

        return SQLiteUser;
    }

    public int removeUser(SQLiteUser c){
        SQLiteDatabase db = this.getWritableDatabase();
        String whereClause = "First Name = '" + c.first_name + "' AND Second Name = '" + c.second_name + "' AND Username = '" + c.user_name + "' AND Password = '" + c.password + "'";
        // Returns the number of affected rows. 0 means no rows were deleted.
        return db.delete(USERS_TABLE_NAME, whereClause, null);
    }

}