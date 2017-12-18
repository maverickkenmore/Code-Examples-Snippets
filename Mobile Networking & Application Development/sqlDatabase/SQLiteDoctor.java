package com.example.m1204231.mobilenetworking.sqlDatabase;

public class SQLiteDoctor {
    public String dr_first_name = "";
    public String dr_second_name = "";
    public String dr_user_name = "";
    public String dr_login_password = "";

    SQLiteDoctor(String dr_fn, String dr_sn, String dr_un, String dr_lp){
        dr_first_name = dr_fn;
        dr_second_name = dr_sn;
        dr_user_name = dr_un;
        dr_login_password = dr_lp;
    }
}
