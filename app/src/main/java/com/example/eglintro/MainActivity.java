package com.example.eglintro;

import android.app.NativeActivity;
import android.os.Bundle;

public class MainActivity extends NativeActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Do some Java work, e.g. start service
        // startService(new Intent(getApplicationContext(), AugmentedAdasService.class));
    }
}