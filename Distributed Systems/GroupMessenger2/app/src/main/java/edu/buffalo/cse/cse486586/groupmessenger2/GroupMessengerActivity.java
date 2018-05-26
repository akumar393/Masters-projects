package edu.buffalo.cse.cse486586.groupmessenger2;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.app.Activity;
import android.telephony.TelephonyManager;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.lang.String;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.URI;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.Hashtable;
import java.util.PriorityQueue;
import java.util.concurrent.PriorityBlockingQueue;

/**
 * GroupMessengerActivity is the main Activity for the assignment.
 *
 * @author stevko
 *
 */
public class GroupMessengerActivity extends Activity {
    static final String TAG = GroupMessengerActivity.class.getSimpleName();
    static final ArrayList<String> REMOTE_PORT = new ArrayList<String>(Arrays.asList("11108", "11112", "11116", "11120", "11124"));
    //    static final String REMOTE_PORT1 = "11112";
//    static final String REMOTE_PORT2 = "11116";
//    static final String REMOTE_PORT3 = "11120";
//    static final String REMOTE_PORT4 = "11124";
    static final int SERVER_PORT = 10000;

    static int seqNum = 0;//{0,0,0,0,0};
    static final String MSG = "MSG";
    static final String PRO = "PRO";
    static final String AGR = "AGR";

    static final String msgdelim = "#%@";
    static final String processdelim = "_";
    static int activeclients = 5;

    int seqNum = 0;
    int msgcount = 1;
    int seqcount = 1;
    int curMaxagreed = 0;

    private final Object lock = new Object();
    private String thisPort = null;

    Hashtable<String, String> senderMsgList = new Hashtable<String, String>();
    Hashtable<String, Integer> proposals = new Hashtable<String, Integer>();
    Hashtable<String, ArrayList<Double>> proposalList = new Hashtable<String, ArrayList<Double>>();

    Hashtable<String, String> receivedMsgList = new Hashtable<String, String>();
    Hashtable<String, MessageAgreed> receiverProposalList = new Hashtable<String, MessageAgreed>();
    PriorityBlockingQueue<MessageAgreed> holdBackQueue = new PriorityBlockingQueue<MessageAgreed>(5);
    PriorityBlockingQueue<MessageAgreed> deliveryQueue = new PriorityBlockingQueue<MessageAgreed>(5);
    PriorityBlockingQueue<MessageAgreed> finalQueue = new PriorityBlockingQueue<MessageAgreed>(25);
    PriorityBlockingQueue<MessageAgreed> msgQueue = new PriorityBlockingQueue<MessageAgreed>(25, new MessageComparator());

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_group_messenger);

        /*
         * TODO: Use the TextView to display your messages. Though there is no grading component
         * on how you display the messages, if you implement it, it'll make your debugging easier.
         */
        TextView tv = (TextView) findViewById(R.id.textView1);
        tv.setMovementMethod(new ScrollingMovementMethod());

        /*
         * Registers OnPTestClickListener for "button1" in the layout, which is the "PTest" button.
         * OnPTestClickListener demonstrates how to access a ContentProvider.
         */
        findViewById(R.id.button1).setOnClickListener(
                new OnPTestClickListener(tv, getContentResolver()));

        /*
         * TODO: You need to register and implement an OnClickListener for the "Send" button.
         * In your implementation you need to get the message from the input box (EditText)
         * and send it to other AVDs.
         */

        TelephonyManager tel = (TelephonyManager) this.getSystemService(Context.TELEPHONY_SERVICE);
        String portStr = tel.getLine1Number().substring(tel.getLine1Number().length() - 4);
        final String myPort = String.valueOf((Integer.parseInt(portStr) * 2));
        thisPort=myPort;
        try {
            ServerSocket serverSocket = new ServerSocket(SERVER_PORT);
//            Log.e(TAG, "ServerSocket Check 1");
            new ServerTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, serverSocket);
//            Log.e(TAG, "ServerSocket Check 2");
        } catch (IOException e) {
//            e.printStackTrace();
            Log.e(TAG, "Can't create a ServerSocket");
            return;
        }

        final EditText editText = (EditText) findViewById(R.id.editText1);

        final Button myButton = (Button) findViewById(R.id.button4);

        myButton.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                String msg = editText.getText().toString() + "\n";
                editText.setText(""); // This is one way to reset the input box.
//                TextView localTextView = (TextView) findView
// one way to display a string.
                new ServerTask.ClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR, msg, myPort,String.valueOf(msgcount));
                String counter=myPort+msgdelim+msgcount;
                senderMsgList.put(counter,msg);
                proposals.put(counter,0);
                proposalList.put(counter,new ArrayList<Double>());
                msgcount++;
            }
        });

        /*
         * Register an OnKeyListener for the input box. OnKeyListener is an event handler that
         * processes each key event. The purpose of the following code is to detect an enter key
         * press event, and create a client thread so that the client thread can send the string
         * in the input box over the network.
         */
//        editText.setOnKeyListener(new View.OnKeyListener() {
//            @Override
//            public boolean onKey(View v, int keyCode, KeyEvent event) {
//                if ((event.getAction() == KeyEvent.ACTION_DOWN) &&
//                        (keyCode == KeyEvent.KEYCODE_ENTER)) {
//                    /*
//                     * If the key is pressed (i.e., KeyEvent.ACTION_DOWN) and it is an enter key
//                     * (i.e., KeyEvent.KEYCODE_ENTER), then we display the string. Then we create
//                     * an AsyncTask that sends the string to the remote AVD.
//                     */
//
////                    TextView remoteTextView = (TextView) findViewById(R.id.remote_text_display);
////                    remoteTextView.append("\n");
//
//                    /*
//                     * Note that the following AsyncTask uses AsyncTask.SERIAL_EXECUTOR, not
//                     * AsyncTask.THREAD_POOL_EXECUTOR as the above ServerTask does. To understand
//                     * the difference, please take a look at
//                     * http://developer.android.com/reference/android/os/AsyncTask.html
//                     */
//
//                    return true;
//                }
//                return false;
//            }
//        });

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_group_messenger, menu);
        return true;
    }

    private class ServerTask extends AsyncTask<ServerSocket, String, Void> {

        @Override
        protected Void doInBackground(ServerSocket... sockets) {
            ServerSocket serverSocket = sockets[0];
            String outputmsg = null;

            Socket socket = null;

            try {
                while (true) {
                    socket = serverSocket.accept();
                    InputStream is = socket.getInputStream();
                    DataInputStream dis = new DataInputStream(is);
                    byte[] data = new byte[128];
                    dis.read(data);
                    socket.close();
                    publishProgress(new String(data));

                    String msgReceived = new String(data);
                    String[] msg_interior = msgReceived.split(msgdelim);

                    switch (msg_interior[0]) {
                        case MSG:
                            //Log.d("Server received data count" + msg_interior[2]);
                            receivedMsgList.put(msg_interior[1], msg_interior[2]);
                            outputmsg = msg_interior[0] + msg_interior[1];
                            callClient(outputmsg);
                            break;
                        case PRO:
                            int tracker = 0;
                            ArrayList<Double> tempList = proposalList.get(msg_interior[1]);
                            if ((tracker = proposals.get(msg_interior[1]) + 1) < activeclients) {
                                tempList.add(Double.parseDouble(msg_interior[2]));
                                proposalList.put(msg_interior[1], tempList);
                                proposals.put(msg_interior[1], tracker);
                            }
                            Double agreedseq_no = Collections.max(tempList);
                            outputmsg = msg_interior[0] + msgdelim + msg_interior[1] + msgdelim + String.valueOf(agreedseq_no);
                            callClient(outputmsg);
                            break;

                        case AGR:
                            String mdata = receivedMsgList.get(msg_interior[1]);
                            if (mdata != null && msg_interior[1] != null) {
                                MessageAgreed tempagreed = new MessageAgreed(Double.parseDouble(msg_interior[2]), msg_interior[1], mdata, true);
                                checkDelivery(msg_interior[1], tempagreed);
                            }


                    }

                }
            } catch (IOException e) {
                e.printStackTrace();
            }



            /*
             * TODO: Fill in your server code that receives messages and passes them
             * to onProgressUpdate().
             */
            return null;
        }


        protected void onProgressUpdate(String... strings) {
            /*
             * The following code displays what is received in doInBackground().
             */

            String strReceived = strings[0].trim();
            TextView localTextView = (TextView) findViewById(R.id.textView1);
            localTextView.append(strReceived);
            localTextView.append("\n");

            /*
             * The following code creates a file in the AVD's internal storage and stores a file.
             *
             * For more information on file I/O on Android, please take a look at
             * http://developer.android.com/training/basics/data-storage/files.html
             */

//            GroupMessengerProvider contentProvider= new GroupMessengerProvider();
            /*Uri uri = buildUri("content", "edu.buffalo.cse.cse486586.groupmessenger1.provider");

            ContentValues cv =new ContentValues();
            cv.put("key",Integer.toString(seqNum++));
            cv.put("value",strReceived);
            getContentResolver().insert(uri,cv);*/

//            String key = (String) keyValueToInsert.get("key");
//            String val = (String) keyValueToInsert.get("value");

//            Cursor resultCursor = getContentResolver().query(uri, null, key, null, null);
//            if (resultCursor == null) {
//                Log.e(TAG, "Result null");
////                throw new Exception();
//            }
//
//            int keyIndex = resultCursor.getColumnIndex("key");
//            int valueIndex = resultCursor.getColumnIndex("value");
//            if (keyIndex == -1 || valueIndex == -1) {
//                Log.e(TAG, "Wrong columns");
//                resultCursor.close();
////                throw new Exception();
//            }
//
//            resultCursor.moveToFirst();
//
//            if (!(resultCursor.isFirst() && resultCursor.isLast())) {
//                Log.e(TAG, "Wrong number of rows");
//                resultCursor.close();
////                throw new Exception();
//            }
//
//            String returnKey = resultCursor.getString(keyIndex);
//            String returnValue = resultCursor.getString(valueIndex);
//            if (!(returnKey.equals(key) && returnValue.equals(val))) {
//                Log.e(TAG, "(key, value) pairs don't match\n key="+returnKey + "  Value="+returnValue);
//                resultCursor.close();
////                throw new Exception();
//            }else{
//                Log.e(TAG,"Values Saved key="+returnKey + "  Value="+returnValue);
//            }
//
//            resultCursor.close();
        }

        protected void callClient(String outputmsg) {

            if (outputmsg != null) {
                String[] casemsg = outputmsg.split(msgdelim);
                switch (casemsg[0]) {


                    case MSG:
                        new ProposalClientTask().execute(casemsg[1]);
                        break;
                    case PRO:
                        new AgreementClientTask().executeOnExecutor(outputmsg[1], outputmsg[2]);
                        break;
                }
            }
        }

        private void checkDelivery(String s, MessageAgreed tempagreed) {

            holdBackQueue.remove(receiverProposalList.get(s));
            deliveryQueue.add(tempagreed);

            MessageAgreed heldbackmsg = holdBackQueue.peek();
            MessageAgreed thismessage = deliveryQueue.peek();

            if (heldbackmsg != null) {
                while (true) {
                    if (thismessage != null && heldbackmsg.getSeqNum() > thismessage.getSeqNum()) ;
                    {
                        finalQueue.add(thismessage);
                        deliveryQueue.poll();
                        thismessage = deliveryQueue.peek();
                    }
                    else
                        break;

                }
            } else {
                while (true) {
                    if (thismessage != null) {
                        finalQueue.add(thismessage);
                        deliveryQueue.poll();
                        thismessage = deliveryQueue.peek();
                    } else
                        break;
                }
            }


        }

        private void printQueue(PriorityBlockingQueue<MessageAgreed> msgQueue) {
            PriorityBlockingQueue<MessageAgreed> finalq = new PriorityBlockingQueue<MessageAgreed>(msgQueue);
            for (MessageAgreed msg; (msg = finalq.poll()) != null)
                insertData(msg.getMsgData());
        }

        private void insertData(String msgData) {

            Uri uri = buildUri("content", "edu.buffalo.cse.cse486586.groupmessenger1.provider");
            ContentValues cv = new ContentValues();
            cv.put("key", Integer.toString(seqNum));
            cv.put("value", msgData);
            getContentResolver().insert(uri, cv);
        }

        /**
         * buildUri() demonstrates how to build a URI for a ContentProvider.
         *
         * @param scheme
         * @param authority
         * @return the URI
         */
        private Uri buildUri(String scheme, String authority) {
            Uri.Builder uriBuilder = new Uri.Builder();
            uriBuilder.authority(authority);
            uriBuilder.scheme(scheme);
            return uriBuilder.build();
        }

        /***
         * ClientTask is an AsyncTask that should send a string over the network.
         * It is created by ClientTask.executeOnExecutor() call whenever OnKeyListener.onKey() detects
         * an enter key press event.
         *
         * @author stevko
         *
         */

        private static class ClientTask extends AsyncTask<String, Void, Void> {

            @Override
            protected Void doInBackground(String... msgs) {
                String currPort = null;
                try {
                    Socket socket;
                    OutputStream os;
                    DataOutputStream dos;
                    String msgToSend = MSG + msgdelim + msgs[1] + processdelim + msgs[2] + msgdelim + msgs[0] + msgdelim;
                    int i;
                    for (i = activeclients - 1; i >= 0; i++) {
                        socket = new Socket(InetAddress.getByAddress(new byte[]{10, 0, 2, 2}), Integer.parseInt(REMOTE_PORT[i]));
                        currPort = REMOTE_PORT.get(i);
                        socket.setSoTimeout(5000);
                        OutputStream fout = socket.getOutputStream();
                        DataOutputStream dat = new DataOutputStream(fout);
                        dat.write(msgToSend.getBytes());
                        socket.close();
                    }
                /*
                 * TODO: Fill in your client code that sends out a message.
                 */

                } catch (SocketTimeoutException ste) {
                    Log.e(TAG, "SocketTimeout Exception at port " + currPort);
                    removeFailedClient(currPort);
                } catch (SocketException se) {
                    Log.e(TAG, "Socket Exception at port " + currPort);
                    removeFailedClient(currPort);
                } catch (UnknownHostException e) {
                    Log.e(TAG, "Proposal Client  UnknownHostException" + currPort);
                    removeFailedClient(currPort);
                } catch (IOException e) {
                    Log.e(TAG, "Proposal Client  socket IOException" + currPort);
                    removeFailedClient(currPort);
                } catch (Exception e) {
                    Log.e(TAG, "Proposal Client Exception ==>" + e.getMessage());
                }
                return null;
            }
        }

        private class ProposalClientTask extends AsyncTask<String, Void, Void> {

            @Override
            protected Void doInBackground(String... msgs) {

                String currentPort = null;
                try {
                    Socket socket;
                    OutputStream out;
                    DataOutputStream dos;
                    String[] temp = msgs[0].split(processdelim);
                    String senderPort = temp[0];
                    int seqtoSend;
                    synchronized (lock) {
                        seqtoSend = seqcount > curMaxagreed ? seqcount : curMaxagreed;
                        seqcount = seqcount + 1;
                    }
                    String strseqnumtoSend;
                    if (!thisPort.equals(null)) {
                        strseqnumtoSend = seqtoSend + "." + thisPort;

                    } else
                        strseqnumtoSend = seqtoSend + ".0";

                    MessageAgreed agreed = new MessageAgreed(Double.parseDouble(strseqnumtoSend), msgs[0], receivedMsgList.get(msgs[0]), false);
                    holdBackQueue.add(agreed);
                    msgQueue.add(agreed);
                    printQueue(msgQueue);
                    receiverProposalList.put(msgs[0], agreed);
                    String msgTosend = PRO + msgdelim + msgs[0] + msgdelim + strseqnumtoSend;
                    socket = new Socket(InetAddress.getByAddress(new byte[]{10, 0, 0, 2}, Integer.parseInt(senderPort)));
                    currentPort = senderPort;
                    socket.setSoTimeout(5000);
                    OutputStream out = socket.getOutputStream();
                    DataOutputStream dos = new DataOutputStream((out));
                    dos.write(msgTosend.getBytes());
                    socket.close();
                } catch (SocketTimeoutException ste) {
                    Log.e(TAG, "SocketTimeout Exception at port " + currentPort);
                    removeFailedClient(currentPort);
                } catch (SocketException se) {
                    Log.e(TAG, "Socket Exception at port " + currentPort);
                    removeFailedClient(currentPort);
                } catch (UnknownHostException e) {
                    Log.e(TAG, "Proposal Client  UnknownHostException" + currentPort);
                    removeFailedClient(currentPort);
                } catch (IOException e) {
                    Log.e(TAG, "Proposal Client  socket IOException" + currentPort);
                    removeFailedClient(currentPort);
                } catch (Exception e) {
                    Log.e(TAG, "Proposal Client Exception ==>" + e.getMessage());
                }
                return null;
            }
        }


        private class AgreementClientTask extends AsyncTask<String, Void, Void> {

            @Override
            protected Void doInBackground(String... msgs) {
                String currPort = null;
                try {
                    Socket socket;
                    OutputStream os;
                    DataOutputStream dos;
                    String msgToSend = AGR + msgdelim + msgs[0] + msgdelim + msgs[1];
                    int i;
                    for (i = activeclients - 1; i >= 0; i++) {
                        socket = new Socket(InetAddress.getByAddress(new byte[]{10, 0, 2, 2}), Integer.parseInt(REMOTE_PORT[i]));
                        currPort = REMOTE_PORT.get(i);
                        socket.setSoTimeout(5000);
                        OutputStream fout = socket.getOutputStream();
                        DataOutputStream dat = new DataOutputStream(fout);
                        dat.write(msgToSend.getBytes());
                        socket.close();
                    }
                } catch (UnknownHostException e1) {
                    e1.printStackTrace();
                } catch (SocketException e1) {
                    e1.printStackTrace();
                } catch (IOException e1) {
                    e1.printStackTrace();
                } catch (SocketTimeoutException ste) {
                    Log.e(TAG, "SocketTimeout Exception at port " + currPort);
                    removeFailedClient(currPort);
                } catch (SocketException se) {
                    Log.e(TAG, "Socket Exception at port " + currPort);
                    removeFailedClient(currPort);
                } catch (UnknownHostException e) {
                    Log.e(TAG, "Proposal Client  UnknownHostException" + currPort);
                    removeFailedClient(currPort);
                } catch (IOException e) {
                    Log.e(TAG, "Proposal Client  socket IOException" + currPort);
                    removeFailedClient(currPort);
                } catch (Exception e) {
                    Log.e(TAG, "Proposal Client Exception ==>" + e.getMessage());
                }
                return null;
            }
        }

        private void removeFailedClient(String currPort) {

            if (REMOTE_PORT.contains(currPort))
                REMOTE_PORT.remove(currPort);
            activeclients = REMOTE_PORT.size();
            PriorityBlockingQueue<MessageAgreed> tempq=new PriorityBlockingQueue<MessageAgreed>(holdBackQueue);
            for (MessageAgreed msg;(msg=holdBackQueue.poll())!=null)
            {
                if(msg.getOriginalId().contains(currPort)){
                    holdBackQueue.remove(msg);
                }
            }
            for(String p_count:proposals.keySet())
            {
                int count=0;
                if(proposals.get(p_count)==activeclients)
                {
                    ArrayList<Double> list=proposals.get(p_count);
                    for(Double seq_no:list)
                    {
                        String []arr=seq_no.split("\\.");
                        if(arr[1].length()==4)
                            arr[1]+="+0";
                        if(arr[1]==currPort)
                            break;
                        else
                            count++;

                    }
                    if(count==activeclients)
                    {
                        Double msgagreed=Collections.max(list);
                        String msgtoSend=PRO+msgdelim+p_count+msgdelim+String.valueOf(msgagreed);
                        new ServerTask().callClient(msgtoSend);
                    }
                }
            }

        }


    }

}