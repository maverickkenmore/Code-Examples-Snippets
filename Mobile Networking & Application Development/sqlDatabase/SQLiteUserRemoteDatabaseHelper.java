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

public class SQLiteUserRemoteDatabaseHelper {
    private final String rootURL = "http://mayar.abertay.ac.uk/~1204231/";
    private final String insertURL = rootURL + "insertusers.php";
    private final String getListURL = rootURL + "getuserslist.php";
    private static final String[] COLUMN_USERS = {"Firstname", "Secondname", "Username", "Password"};
    private final Context parentActivityContext;

    /* Local storage for contacts list. */
    private ArrayList<SQLiteUser> usersOutput = new ArrayList<SQLiteUser>();

    SQLiteUserRemoteDatabaseHelper(Context context) { parentActivityContext = context;}

    public void addUser(SQLiteUser user) {
        AddUserTask task = new AddUserTask();
        task.execute(user);
    }

    public ArrayList<SQLiteUser> getUserList() {
        GetUserTask task = new GetUserTask();
        task.execute();
        return usersOutput;
    }

    // Asynchronous task for adding a contact to DB. Runs on a background thread.
    private class AddUserTask extends AsyncTask<SQLiteUser, Void, Void> {
        private final ProgressDialog progressDialog = new ProgressDialog(parentActivityContext);
        private HttpClient httpClient = new DefaultHttpClient();
        private HttpPost httpPost = new HttpPost(insertURL);

        /* Before executing this task, set the progressDialog message and show it. */
        @Override
        protected void onPreExecute() {
            this.progressDialog.setMessage("Adding user...");
            this.progressDialog.show();
        }

        /* This is what is done in the background. */
        // This function requires a list of parameters, but we will be using only one [0].
        @Override
        protected Void doInBackground(SQLiteUser... users) {
            SQLiteUser c = users[0];

            /* Add POST parameters to list. */
            ArrayList<NameValuePair> userDetails = new ArrayList<NameValuePair>(3); // note the size parameter
            userDetails.add(new BasicNameValuePair(COLUMN_USERS[0], c.first_name));
            userDetails.add(new BasicNameValuePair(COLUMN_USERS[1], c.second_name));
            userDetails.add(new BasicNameValuePair(COLUMN_USERS[2], c.user_name));
            userDetails.add(new BasicNameValuePair(COLUMN_USERS[2], c.password));

            /* Encode POST data. */
            try {
                httpPost.setEntity(new UrlEncodedFormEntity(userDetails));
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
    private class GetUserTask extends AsyncTask<Void, Void, ArrayList<SQLiteUser>> {
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
        protected ArrayList<SQLiteUser> doInBackground(Void... params) {

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
            JSONArray usersArray = null;
            if (responseString != null && responseString != "") {
                try {
                    usersArray = new JSONArray(responseString);
                } catch (JSONException e) {
                    // Log exceptions
                    e.printStackTrace();
                }
            }

            /* Create and ArrayList to hold our contacts. */
            ArrayList<SQLiteUser> users = new ArrayList<SQLiteUser>();

            if (usersArray != null) {
                /* Go through the list of contacts, and convert them to Contact objects, putting
                 those into an ArrayList. */
                for (int i = 0; i < usersArray.length(); i++) {
                    try {
                        JSONObject userEntry = usersArray.getJSONObject(i);
                        String firstname = userEntry.get(COLUMN_USERS[0]).toString();
                        String secondname = userEntry.get(COLUMN_USERS[1]).toString();
                        String username = userEntry.get(COLUMN_USERS[2]).toString();
                        String password = userEntry.get(COLUMN_USERS[3]).toString();

                        // Log for debugging.
                        Log.i("Response USER:", "" + firstname + ", " + secondname + ", " + username + ", " + password);
                        users.add(new SQLiteUser(firstname, secondname, username, password));
                    } catch (JSONException e) {
                        // Log exceptions
                        e.printStackTrace();
                    }
                }
            }
            /* Return the list of contacts. */
            return users;
        }

        /* After the task is finished, dismiss the progressDialog.*/
        @Override
        protected void onPostExecute(ArrayList<SQLiteUser> result) {
            usersOutput = result;
            this.progressDialog.dismiss();
        }
    }
}
