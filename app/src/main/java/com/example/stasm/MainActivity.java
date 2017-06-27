package com.example.stasm;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    private static final String ROOT = Environment.getExternalStorageDirectory().getAbsolutePath();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        long start = System.currentTimeMillis();
        loadMoreFaceJpeg(ROOT, ROOT + "/test/testface.jpg");
        long finish = System.currentTimeMillis();
        Log.w("MainActivity", "SPEND = " + (finish - start));
        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
    }

    public native void loadJpeg(String root, String path);

    public native void loadMoreFaceJpeg(String root, String path);

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
