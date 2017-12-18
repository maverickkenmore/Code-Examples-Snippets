package com.example.m1204231.mobilenetworking.sqlDatabase;

public class SQLiteUser {
    public String first_name = "";
    public String second_name = "";
    public String user_name = "";
    public String password = "";

    SQLiteUser(String fn, String se, String un, String pw){
        first_name = fn;
        second_name = se;
        user_name = un;
        password = pw;
    }
}
