package com.example.m1204231.mobilenetworking.sqlDatabase;

import android.app.ProgressDialog;
import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;

public class SQLiteDoctorRemoteDatabaseHelper {
    private final String rootURL = "http://mayar.abertay.ac.uk/~1204231/";
    private final String insertURL = rootURL + "insert.php";
    private final String getListURL = rootURL + "getlist.php";
    private static final String[] COLUMN_DOCTORS = {"First Name", "Second Name", "Username", "Password"};
    private final Context parentActivityContext;

    /* Local storage for contacts list. */
    private ArrayList<SQLiteDoctor> doctorsOutput = new ArrayList<SQLiteDoctor>();

    SQLiteDoctorRemoteDatabaseHelper(Context context) {
        parentActivityContext = context;
    }

    public void addDoctor(SQLiteDoctor doctor) {
        AddDoctorTask task = new AddDoctorTask();
        task.execute(doctor);
    }

    public ArrayList<SQLiteDoctor> getContactsList() {
        AddDoctorTask task = new AddDoctorTask();
        task.execute();
        return doctorsOutput;
    }

    // Asynchronous task for adding a contact to DB. Runs on a background thread.
    private class AddDoctorTask extends AsyncTask<SQLiteDoctor, Void, Void> {
        private final ProgressDialog progressDialog = new ProgressDialog(parentActivityContext);
        private HttpClient httpClient = new DefaultHttpClient();
        private HttpPost httpPost = new HttpPost(insertURL);

        /* Before executing this task, set the progressDialog message and show it. */
        @Override
        protected void onPreExecute() {
            this.progressDialog.setMessage("Adding contact...");
            this.progressDialog.show();
        }

        /* This is what is done in the background. */
        // This function requires a list of parameters, but we will be using only one [0].
        @Override
        protected Void doInBackground(SQLiteDoctor... doctors) {
            SQLiteDoctor c = doctors[0];

            /* Add POST parameters to list. */
            ArrayList<NameValuePair> doctorDetails = new ArrayList<NameValuePair>(3); // note the size parameter
            doctorDetails.add(new BasicNameValuePair(COLUMN_DOCTORS[0], c.dr_first_name));
            doctorDetails.add(new BasicNameValuePair(COLUMN_DOCTORS[1], c.dr_second_name));
            doctorDetails.add(new BasicNameValuePair(COLUMN_DOCTORS[2], c.dr_user_name));
            doctorDetails.add(new BasicNameValuePair(COLUMN_DOCTORS[3], c.dr_login_password));

            /* Encode POST data. */
            try {
                httpPost.setEntity(new UrlEncodedFormEntity(doctorDetails));
            } catch (UnsupportedEncodingException e) {
                e.printStackTrace();
            }

            /* Finally, make an HTTP POST request to server. */
            try {
                HttpResponse response = httpClient.execute(httpPost);
                HttpEntity entity = response.getEntity();
                String responseString = EntityUtils.toString(entity, "UTF-8");
                // Write response to log
                Log.i("Response:", responseString);
            } catch (ClientProtocolException e) {
                // Log exception
                e.printStackTrace();
            } catch (IOException e) {
                // Log exception
                e.printStackTrace();
            }
            return null; // must be here if return type is Void
        }

        /* After the task is finished, dismiss the progressDialog.*/
        @Override
        protected void onPostExecute(Void result) {
            // This is where we would process the results if needed.
            this.progressDialog.dismiss();
        }
    }


    // Asynchronous task for getting the list of contacts from the remote DB. Runs on a background thread.
    private class GetDoctorsTask extends AsyncTask<Void, Void, ArrayList<SQLiteDoctor>> {
        private final ProgressDialog progressDialog = new ProgressDialog(parentActivityContext);
        private HttpClient httpClient = new DefaultHttpClient();
        private HttpGet httpGet = new HttpGet(getListURL);

        /* Before executing this task, set the progressDialog message and show it. */
        @Override
        protected void onPreExecute() {
            this.progressDialog.setMessage("Retrieving contacts list...");
            this.progressDialog.show();
        }

        /* This is what is done in the background. */
        // This time we don't need to pass any parameters to the task, hence using Void.
        @Override
        protected ArrayList<SQLiteDoctor> doInBackground(Void... params) {

           /* Make an HTTP request. */
            HttpResponse response = null;
            String responseString = "";
            try {
                response = httpClient.execute(httpGet);
                HttpEntity entity = response.getEntity();
                responseString = EntityUtils.toString(entity, "UTF-8");

                // Write response to log for debugging.
                Log.i("Response:", responseString);
            } catch (ClientProtocolException e) {
                // Log exception
                e.printStackTrace();
            } catch (IOException e) {
                // Log exception
                e.printStackTrace();
            }

            // Process the results in background.
            JSONArray doctorsArray = null;
            if (responseString != null && responseString != "") {
                try {
                    doctorsArray = new JSONArray(responseString);
                } catch (JSONException e) {
                    // Log exceptions
                    e.printStackTrace();
                }
            }

            /* Create and ArrayList to hold our contacts. */
            ArrayList<SQLiteDoctor> doctors = new ArrayList<SQLiteDoctor>();

            if (doctorsArray != null) {
                /* Go through the list of contacts, and convert them to Contact objects, putting
                 those into an ArrayList. */
                for (int i = 0; i < doctorsArray.length(); i++) {
                    try {
                        JSONObject doctorEntry = doctorsArray.getJSONObject(i);
                        String drfirstname = doctorEntry.get(COLUMN_DOCTORS[0]).toString();
                        String drsecondname = doctorEntry.get(COLUMN_DOCTORS[1]).toString();
                        String drusername = doctorEntry.get(COLUMN_DOCTORS[2]).toString();
                        String drpassword = doctorEntry.get(COLUMN_DOCTORS[3]).toString();
                        // Log for debugging.
                        Log.i("Response DOCTOR:", "" + drfirstname + ", " + drsecondname + ", " + drusername + ", " + drpassword);
                        doctors.add(new SQLiteDoctor(drfirstname, drsecondname, drusername, drpassword));
                    } catch (JSONException e) {
                        // Log exceptions
                        e.printStackTrace();
                    }
                }
            }
            /* Return the list of contacts. */
            return doctors;
        }

        /* After the task is finished, dismiss the progressDialog.*/
        @Override
        protected void onPostExecute(ArrayList<SQLiteDoctor> result) {
            doctorsOutput = result;
            this.progressDialog.dismiss();
        }
    }
}
