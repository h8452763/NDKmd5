package com.example.jiang.ndktest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    int i=0;


    static {
        System.loadLibrary("native-lib");
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        JniUtils jniUtils = new JniUtils();
        String s=jniUtils.getEncrypt("admin");
        TextView tv = (TextView) findViewById(R.id.tv);
        tv.setText(s+"");
    }

    public void changeInt(int s){
        i=300;
    }

}
