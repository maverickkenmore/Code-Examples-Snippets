package com.example.m1204231.mobilenetworking.pedometer;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;

import java.util.List;


public class PedometerActivity extends ActionBarActivity {


    private SensorManager sensorManager;
    private Sensor defaultAccelerometer;
    private SensorEventListener AccelerometerEventListener;
    private SensorEvent AccelerometerEvent;

    private float gravity[];
    private float linear_acceleration[];



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }


    public PedometerActivity()
    {
        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        if (sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER) != null) {
        // Success! There's a Accelerometer.
        defaultAccelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        List<Sensor> accelerometerSensors = sensorManager.getSensorList(Sensor.TYPE_ACCELEROMETER);
        }
        else
        {
        // Failure! No accelerometer.

        }
    }

    protected void onResume() {
        super.onResume();
        sensorManager.registerListener(AccelerometerEventListener, defaultAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
    }

    protected void onPause() {
        super.onPause();
        sensorManager.unregisterListener(AccelerometerEventListener);
    }

    public void onAccuracyChanged(Sensor defaultAccelerometer, int accuracy) {
    }

    public void onSensorChanged(SensorEvent AccelerometerEvent) {

        final float alpha = 0.8f;



        // Isolate the force of gravity with the low-pass filter.
        gravity[0] = alpha * gravity[0] + (1 - alpha) * AccelerometerEvent.values[0];
        gravity[1] = alpha * gravity[1] + (1 - alpha) * AccelerometerEvent.values[1];
        gravity[2] = alpha * gravity[2] + (1 - alpha) * AccelerometerEvent.values[2];

        // Remove the gravity contribution with the high-pass filter.
        linear_acceleration[0] = AccelerometerEvent.values[0] - gravity[0];
        linear_acceleration[1] = AccelerometerEvent.values[1] - gravity[1];
        linear_acceleration[2] = AccelerometerEvent.values[2] - gravity[2];

        // Do something with this sensor value.
    }

}