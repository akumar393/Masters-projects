package edu.buffalo.cse.cse486586.simpledht;

import android.content.ContentValues;
import android.content.Context;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.app.Activity;
import android.telephony.TelephonyManager;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

public class SimpleDhtActivity extends Activity {

    static private final String TAG = SimpleDhtActivity.class.getSimpleName();
    static final String[] REMOTE_PORT = {"11108", "11112", "11116", "11120", "11124"};
    static final int SERVER_PORT = 10000;
    static int seqnum = 0;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_simple_dht_main);

        TextView tv = (TextView) findViewById(R.id.textView1);
        tv.setMovementMethod(new ScrollingMovementMethod());
        findViewById(R.id.button3).setOnClickListener(
                new OnTestClickListener(tv, getContentResolver()));


    final Button myButton = (Button) findViewById(R.id.button1);

        myButton.setOnClickListener(new View.OnClickListener()

    {

        @Override
        public void onClick (View v){
        ContextVariables contextVariables = (ContextVariables) getContext();
        Log.w(TAG, "My Node id: " + contextVariables.getMyNodeId() + "\nMy Predecessor : " + contextVariables.getMyPredecessor() + "My Successor : " + contextVariables.getMySuccessor());
        TextView tv = (TextView) findViewById(R.id.textView1);
        tv.append("My Node id: " + contextVariables.getMyNodeId() + "\nMy Predecessor : " + contextVariables.getMyPredecessor() + "\nMy Successor : " + contextVariables.getMySuccessor());
    }
    });
}

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_simple_dht_main, menu);
        return true;
    }


}
