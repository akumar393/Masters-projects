package edu.buffalo.cse.cse486586.simpledht;

import android.content.ContentProvider;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.MatrixCursor;
import android.net.Uri;
import android.os.AsyncTask;
import android.telephony.TelephonyManager;
import android.util.Log;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Formatter;


public class SimpleDhtProvider extends ContentProvider {

    static private final String TAG = SimpleDhtActivity.class.getSimpleName();
    static final String[] REMOTE_PORT = {"11108", "11112", "11116", "11120", "11124"};
    static final int SERVER_PORT = 10000;
    static final String NODE_JOIN_PORT="11108";
    static final String msgdelimeter="####";
    static final String cursordelimeter="<==>";

    final static Uri uri = buildURI("content", "edu.buffalo.cse.cse486586.simpledht.provider");

    static final String NodeJoin="NodeJoin";
    static final String NodeAdded="NodeAdded";
    static final String UpdatePredecessor= "UpdatePredecessor";
    static final String InsertTask="InsertTask";
    static final String QueryTask="QueryTask";
    static final String ReturnQueryTask="ReturnQueryTask";
    static final String DeleteTask="DeleteTask";
    static final String StarQuery="StarQuery";
    static final String StarDelete="StarDelete";
    static final String ReturnStarQuery="ReturnStarQuery";

    private static final String KEY="key";
    private static final String VALUE="value";

    static boolean isoriginatingPortquery=true;
    static String queryoriginatingPort="";

    static final String ourDHTS="\"*\"";
    static final String allDHTS="\"@\"";

    static final String[] columns={KEY,VALUE};
    MatrixCursor ourDHTScursor=new MatrixCursor(columns);
    MatrixCursor allDHTScursor=new MatrixCursor(columns);

    private static Uri buildURI(String scheme, String authority){

        Uri.Builder uribuild=new Uri.Builder();
        uribuild.authority(authority);
        uribuild.scheme(scheme);
        return uribuild.build();
    }
    @Override
    public int delete(Uri uri, String selection, String[] selectionArgs) {
        // TODO Auto-generated method stub
        if(selection.equals(ourDHTS)){
            String[] files=getContext().fileList();
            for(String file:files) {
                getContext().deleteFile(file);
            }
        }
        else if(selection.equals(allDHTS)){
            String[] files=getContext().fileList();
            for(String file:files) {
                getContext().deleteFile(file);
            }
            new DeleteQueryClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR);
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            else{
                getContext().deleteFile(selection);
            }
        }
        return 0;
    }

    @Override
    public String getType(Uri uri) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public Uri insert(Uri uri, ContentValues values) {
        // TODO Auto-generated method stub
        String key;
        String value;
        ContextVariables contextVariables=(ContextVariables)getContext();
        try {
            key = values.get(KEY).toString();
            value = values.get(VALUE).toString();
            if (contextVariables.getMySuccessor().equals("") || contextVariables.getMySuccessor().equals(contextVariables.getMyNodeId()) || keyLookup(key)) {

                FileOutputStream fout = getContext().openFileOutput(key, Context.MODE_PRIVATE);
                fout.write(value.getBytes());
                fout.close();
            } else {
                new InsertClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR, getPortId(contextVariables.getMySuccessor()), key, value);
            }
        }catch(IOException ioe){
            Log.e(TAG,"Insert Exception"+ioe.getMessage());
        }catch(NullPointerException npe){
            Log.e(TAG,"Insert Exception"+npe.getMessage());
        }catch(Exception e){
            Log.e(TAG,"Insert Exception"+e.getMessage());
        }
        Log.v("insert", values.toString());
        return uri;
    }



    @Override
    public boolean onCreate() {
        // TODO Auto-generated method stub
        TelephonyManager tel = (TelephonyManager) getContext().getSystemService(Context.TELEPHONY_SERVICE);
        String portStr = tel.getLine1Number().substring(tel.getLine1Number().length() - 4);
        final String myPort = String.valueOf((Integer.parseInt(portStr) * 2));
        ContextVariables contextVariables=(ContextVariables)getContext();
        contextVariables.setMyPort(myPort);
        contextVariables.setMyNodeId(portStr);
        try {
            contextVariables.setMyHashNode(genHash(portStr));
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }

        try{
            ServerSocket server=new ServerSocket(SERVER_PORT);
            new ServerTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR,server);

        }catch (IOException e) {
            Log.e(TAG, "Can't create a ServerSocket");
            return false;
        }

        new NodeJoinClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR,myPort);

        return false;
    }

    @Override
    public Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs,
            String sortOrder) {
        // TODO Auto-generated method stub
        String msg="";
        MatrixCursor cursor=new MatrixCursor(columns);
        int keyIndex= cursor.getColumnIndex(KEY);
        int valueIndex=cursor.getColumnIndex(VALUE);

        FileInputStream fis;
        BufferedInputStream bis;
        int temp;
        ContextVariables contextVariables=getContext();
        if(selection.equals(ourDHTS)){

            String []files=getContext().fileList();
            for( String file:files){
                msg="";
                try {
                    fis=getContext().openFileInput(file);
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
                bis=new BufferedInputStream(fis);
                try {
                    while((temp=bis.read())!=-1){
                        msg+=(char)temp;
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }

            cursor.addRow(new String[]{file,msg});
            }
            return cursor;
        }
        else if(selection.equals(allDHTS)){
            String []files=getContext().fileList();
            for(String file:files){
                msg="";
                try {
                    fis=getContext().openFileInput(file);
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
                bis=new BufferedInputStream(fis);
                    try {
                        while((temp=bis.read())!=-1){
                            msg+=(char)temp;
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                    }

                allDHTScursor.addRow(new String[]{file,msg});
            }
            if(!contextVariables.getMyNodeId().equals(contextVariables.getMySuccessor())){

                new StarQueryClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR,getPortId(contextVariables.getMySuccessor()),contextVariables.getMyPort());
                try{
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            return allDHTScursor;
        }
        else{
            try{
                if(contextVariables.getMySuccessor().equals("")|| contextVariables.getMySuccessor().equals(contextVariables.getMyNodeId())|| keyLookUp(selection))
                {
                    fis=getContext().openFileInput(selection);
                    bis=new BufferedInputStream(fis);
                    try {
                        while((temp=bis.read())!=-1){
                            msg+=(char)temp;
                        }
                        bis.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    cursor.addRow(new String[]{selection,msg});
                }
                else{
                    String origin=contextVariables.getMyPort();
                    if(!isoriginatingPortquery)
                    {
                        origin=queryoriginatingPort;
                    }
                    new QueryClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR,getPortId(contextVariables.getMySuccessor()),selection,origin);

                    if(isoriginatingPortquery){
                        try {
                            Thread.sleep(500);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                    if(ourDHTScursor.moveToFirst()){
                        do {
                            if (selection.equals(ourDHTScursor.getString(keyIndex))) {
                                cursor.addRow(new String[]{selection, ourDHTScursor.getString(valueIndex)});
                                return cursor;
                            }
                        }while(ourDHTScursor.moveToNext());
                    }else{
                       // Log.w("Cursor is null");
                    }
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }catch (IOException ioe) {
//                Log.w(TAG," Query IOexception"+ ioe.getMessage());
            } catch (NullPointerException npe) {
//                Log.w(TAG," Query NullPointerException"+ npe.getMessage());
            } catch (Exception e){
//                Log.w(TAG," Query Exception"+ e.getMessage());
            }
        }





        return null;
    }

    @Override
    public int update(Uri uri, ContentValues values, String selection, String[] selectionArgs) {
        // TODO Auto-generated method stub
        return 0;
    }

    private String genHash(String input) throws NoSuchAlgorithmException {
        MessageDigest sha1 = MessageDigest.getInstance("SHA-1");
        byte[] sha1Hash = sha1.digest(input.getBytes());
        Formatter formatter = new Formatter();
        for (byte b : sha1Hash) {
            formatter.format("%02x", b);
        }
        return formatter.toString();
    }
    private String genHashNodeWrapper(String nodeId){

        if((null==nodeId )|| "".equals(nodeId))
        {
            return "";
        }
        else {
            try {
                return genHash(nodeId);
            } catch (NoSuchAlgorithmException e) {
                e.printStackTrace();
            }
        }
        return null;
    }
    private class ServerTask extends AsyncTask<ServerSocket, String, Void> {
        @Override
        protected Void doInBackground(ServerSocket... sockets) {
            ServerSocket serverSocket =sockets[0];

            try{
                while(true){

                    Socket socket=serverSocket.accept();
                    InputStream io=socket.getInputStream();
                    BufferedReader bio=new BufferedReader(new InputStreamReader(io));
                    String incoming=bio.readLine();
                    socket.close();

                    String [] splitter= incoming.split(msgdelimeter);
                    ContextVariables contextVariables=(ContextVariables)getContext();

                    switch(splitter[0]){

                        case NodeJoin:
                            callClientTask(incoming);
                            break;
                        case NodeAdded:
                            ContextVariables contextVariables=(ContextVariables)getContext();
                            contextVariables.setMyPredecessor(splitter[1]);
                            contextVariables.setMyHashPredecessor(genHashNodeWrapper(splitter[1]));
                            contextVariables.setMySuccessor(splitter[2]);
                            contextVariables.setMyHashSuccessor(genHashNodeWrapper(splitter[2]));
                            break;
                        case UpdatePredecessor:
                            ContextVariables contextVariables=(ContextVariables)getContext();
                            contextVariables.setMySuccessor(splitter[2]);
                            contextVariables.setMyHashSuccessor(genHashNodeWrapper(splitter[2]));
                            break;
                        case InsertTask:
                            ContentValues cv=new ContentValues();
                            cv.put(KEY,splitter[1]);
                            cv.put(VALUE,splitter[2]);
                            insert(uri,cv);
                            break;
                        case QueryTask:
                            isoriginatingPortquery=false;
                            queryoriginatingPort=splitter[1];
                            String key="";
                            String value="";
                            Cursor curse=query(uri,null,splitter[1],null,null);
                            if(curse.moveToFirst()){
                                int keyindex=curse.getColumnIndex(KEY);
                                int valueindex=curse.getColumnIndex(VALUE);
                                key=curse.getString(keyindex);
                                value=curse.getString(valueindex);
                                String msgtoSend=ReturnQueryTask+msgdelimeter+key+msgdelimeter+value+msgdelimeter+splitter[2]+msgdelimeter;
                                callClientTask(msgtoSend);
                            }
                            isoriginatingPortquery=true;
                            queryoriginatingPort="";
                            break;

                        case ReturnQueryTask:
                            ourDHTScursor.addRow(new String[] {splitter[1],splitter[2]});
                            break;
                        case StarQuery:
                                String rows="";
                                if(!splitter[1].equals(contextVariables.getMyPort())){

                                    curse = query(uri, null, splitter[1], null, null);
                                    if (curse != null && curse.getCount() > 0) {
                                        int keyIndex = curse.getColumnIndex(KEY);
                                        int valueIndex = curse.getColumnIndex(VALUE);
                                        if(curse.moveToFirst()) {
                                            do {
                                                rows += curse.getString(keyIndex) + cursordelimeter + curse.getString(valueIndex) + msgdelimeter;
                                            } while (curse.moveToNext());
                                        }
                                        new ReturnStarQueryClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR, splitter[1], rows);
                                    }
                            }
                            break;

                        case ReturnStarQuery:
                            for(int i=0;i<splitter.length;i++)
                            {
                                if(splitter[i].contains(cursordelimeter))
                                {
                                    allDHTScursor.addRow(new String[]{splitter[i].split(cursordelimeter)[0],splitter[i].split(cursordelimeter)[1]});
                                }
                            }
                            break;
                        case DeleteTask:
                            delete(uri,ourDHTS,null);
                            break;
                    }
            }
            } catch (IOException e) {
                e.printStackTrace();
            }catch (Exception e){
                Log.e(TAG, " Server Task Exception :" + e.getMessage());
            }
            return null;

        }

        protected void onProgressUpdate(String...strings) {
            /*
             * The following code displays what is received in doInBackground().
             */


            /*
             * The following code creates a file in the AVD's internal storage and stores a file.
             *
             * For more information on file I/O on Android, please take a look at
             * http://developer.android.com/training/basics/data-storage/files.html
             */

        }

        protected void callClientTask(String msg){
            if(msg!=null) {
                String[] msgs = msg.split(msgdelimeter);
                switch (msgs[0]) {
                    case NodeJoin:
                        //NodeJoin+####+newAppNodeId
                        new NodeJoinTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR, msgs[1],msgs[2]);
                        break;
                    case InsertTask:

                        break;
                    case ReturnQueryTask:
                        //ReturnQueryTask####key####value####originatingPort####
                        new ReturnQueryClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR, msgs[3],msgs[1],msgs[2]);
                        break;
                    case DeleteTask:


                }
            }

        }
    }
    /***
     * ClientTask is an AsyncTask that should send a string over the network.
     * It is created by ClientTask.executeOnExecutor() call whenever OnKeyListener.onKey() detects
     * an enter key press event.
     *
     * @author stevko
     *
     */
    private class InsertClientTask extends AsyncTask<String, Void, Void> {

        @Override
        protected Void doInBackground(String... msgs) {
                Socket socket;
                OutputStream os;
                PrintWriter pw;
                try{
                    String msgTosend= InsertTask+msgdelimeter+msgs[1]+msgdelimeter+msgs[2]+msgdelimeter;
                    socket=new Socket(InetAddress.getByAddress(new byte[]{10,0,0,2}),Integer.parseInt(msgs[0]));
                    os=socket.getOutputStream();
                    pw=new PrintWriter(os,true);
                    pw.println(msgTosend);
                    pw.flush();
                    socket.close();
                    //pw.flush();
                } catch (UnknownHostException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            return null;
        }
    }

    private class StarQueryClientTask extends AsyncTask<String, Void, Void> {

        @Override
        protected Void doInBackground(String... msgs) {
                Socket socket;
                OutputStream os;
                PrintWriter pw;
                try{
                    String msgToSend=StarQuery+msgdelimeter+msgs[1];

                        socket=new Socket(InetAddress.getByAddress(new byte[]{10,0,0,2}),Integer.parseInt(msgs[0]));
                        os=socket.getOutputStream();
                        pw=new PrintWriter(os,true);
                        pw.println(msgToSend)
                        pw.flush();
                        socket.close();
                        //pw.flush();

                    }catch (UnknownHostException e) {
                        e.printStackTrace();
                    }catch (IOException e) {
                        e.printStackTrace();
                    }
               return null;
                }

    }

    private static class ReturnStarQueryClientTask extends AsyncTask<String, Void, Void> {

        @Override
        protected Void doInBackground(String... msgs) {

            try{
                Socket socket;
                OutputStream os;
                PrintWriter pw;
                ContextVariables contextVariables=(ContextVariables)getContext();

                    String msgTosend=ReturnQueryTask+msgdelimeter+msgs[1]+contextVariables.getMyNodeId()+msgdelimeter;
                    socket=new Socket(InetAddress.getByAddress(new byte[]{10,0,0,2}),Integer.parseInt(msgs[0]));
                    os=socket.getOutputStream();
                    pw=new PrintWriter(os,true);
                    pw.println(msgTosend);
                    pw.flush();
                    socket.close();
                    //pw.flush();
                } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return null;
        }
    }

    private class DeleteQueryClientTask extends AsyncTask<Void, Void, Void> {

        @Override
        protected Void doInBackground(Void... msgs) {

            try{
                Socket socket;
                OutputStream os;
                PrintWriter pw;
                String msgToSend=DeleteTask+msgdelimeter;
                ContextVariables contextVariables=(ContextVariables)getContext();

                for(int i=0;i<REMOTE_PORT.length;i++) {
                    if (!(REMOTE_PORT[i] == contextVariables.getMyPort())) {

                        socket = new Socket(InetAddress.getByAddress(new byte[]{10, 0, 0, 2}), Integer.parseInt(REMOTE_PORT[i]));
                        os = socket.getOutputStream();
                        pw = new PrintWriter(os, true);
                        pw.println(msgToSend);
                        pw.flush();
                        socket.close();
                    }
                }
            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return null;
        }
    }

    private class QueryClientTask extends AsyncTask<String, Void, Void> {

        @Override
        protected Void doInBackground(String... msgs) {
            try{
                Socket socket;
                OutputStream os;
                PrintWriter pw;
                ContextVariables contextVariables=(ContextVariables)getContext();

                String msgTosend=QueryTask+msgdelimeter+msgs[1]+msgdelimeter+msgs[2]+msgdelimeter;
                socket=new Socket(InetAddress.getByAddress(new byte[]{10,0,0,2}),Integer.parseInt(msgs[0]));
                os=socket.getOutputStream();
                pw=new PrintWriter(os,true);
                pw.println(msgTosend);
                pw.flush();
                socket.close();
                //pw.flush();
            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return null;
        }
    }

    private class ReturnQueryClientTask extends AsyncTask<String, Void, Void> {

        @Override
        protected Void doInBackground(String... msgs) {
            try {
                Socket socket;
                OutputStream os;
                PrintWriter pw;
                ContextVariables contextVariables = (ContextVariables) getContext();

                String msgTosend = ReturnQueryTask + msgdelimeter + msgs[1]+msgdelimeter +msgs[2]+msgdelimeter + contextVariables.getMyNodeId() + msgdelimeter;
                socket = new Socket(InetAddress.getByAddress(new byte[]{10, 0, 0, 2}), Integer.parseInt(msgs[0]));
                os = socket.getOutputStream();
                pw = new PrintWriter(os, true);
                pw.println(msgTosend);
                pw.flush();
                socket.close();
               // pw.flush();
            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return null;
        }
    }

    private class NodeJoinClientTask extends AsyncTask<String, Void, Void> {
        @Override
        protected Void doInBackground(String... msgs) {
            try {
                Socket socket;
                OutputStream os;
                PrintWriter pw;
                ContextVariables contextVariables = (ContextVariables) getContext();

                String msgTosend = NodeJoin+msgdelimeter+msgs[0]+msgdelimeter+contextVariables.getMyNodeId()+msgdelimeter;
                socket = new Socket(InetAddress.getByAddress(new byte[]{10, 0, 0, 2}), Integer.parseInt(msgs[0]));
                os = socket.getOutputStream();
                pw = new PrintWriter(os, true);
                pw.println(msgTosend);
                pw.flush();
                socket.close();
            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return null;
        }
    }

    private class NodeJoinTask extends AsyncTask<String, Void, Void> {

        @Override
        protected Void doInBackground(String... msgs) {
            try{
                ContextVariables contextVariables=(ContextVariables)getContext();
                OutputStream os;
                PrintWriter pw;
                String msgToSend;
                Socket socket;
                if(LookUp(msgs[1])){
                    String temp=contextVariables.getMyPredecessor();
                    if(temp.equals(""))
                    {
                        temp=contextVariables.getMyNodeId();
                    }
                    msgToSend=NodeAdded+msgdelimeter+contextVariables.getMyNodeId()+msgdelimeter+temp+msgdelimeter;
                    socket=new Socket(InetAddress.getByAddress(new byte[]{10,0,0,2}),Integer.parseInt(msgs[1]));
                    os=socket.getOutputStream();
                    pw=new PrintWriter(os,true);
                    pw.println(msgToSend);
                    pw.flush();
                    socket.close();


                    if(!contextVariables.getMyPredecessor()==null || contextVariables.getMyPredecessor().equals("")){
                        msgToSend=UpdatePredecessor+msgdelimeter+msgs[1]+msgdelimeter;
                        socket=new Socket(InetAddress.getByAddress(new byte[]{10,0,0,2}),Integer.parseInt(msgs[1]));
                        os=socket.getOutputStream();
                        pw=new PrintWriter(os,true);
                        pw.println(msgToSend);
                        pw.flush();
                        socket.close();

                    }
                    contextVariables.setMyPredecessor(msgs[1]);
                    contextVariables.setMyHashPredecessor(msgs[1]);
                }
                else if(contextVariables.getMyNodeId().equals(contextVariables.getMySuccessor())) {
                    msgToSend=NodeAdded+msgdelimeter+contextVariables.getMyNodeId()+msgdelimeter+contextVariables.getMyNodeId()+msgdelimeter;
                    socket=new Socket(InetAddress.getByAddress(new byte[]{10,0,0,2}),Integer.parseInt(msgs[1]));
                    os=socket.getOutputStream();
                    pw=new PrintWriter(os,true);
                    pw.println(msgToSend);
                    pw.flush();
                    socket.close();

                }else{
                    msgToSend=NodeJoin+msgdelimeter+msgs[0]+msgdelimeter+contextVariables.getMyNodeId()+msgdelimeter;
                    socket=new Socket(InetAddress.getByAddress(new byte[]{10,0,0,2}),Integer.parseInt(msgs[1]));
                    os=socket.getOutputStream();
                    pw=new PrintWriter(os,true);
                    pw.println(msgToSend);
                    pw.flush();
                    socket.close();
                }
            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }


            return null;
        }

    }

    private boolean keyLookUp(String newkey){

         String hashofnewkey=genHash(newkey);
         ContextVariables contextVariables=(ContextVariables)getContext();
         if(hashofnewkey.compareTo(contextVariables.getMyHashPredecessor())>0 && hashofnewkey.compareTo(contextVariables.getMyHashNode())<=0)
         {
             return true;
         }
         else if(hashofnewkey.compareTo(contextVariables.getMyHashPredecessor())>0 && contextVariables.getMyHashPredecessor().compareTo(contextVariables.getMyHashNode())>0)
         {
             return true;
         }
         else if(contextVariables.getMyHashPredecessor().compareTo(contextVariables.getMyHashNode())>0 && hashofnewkey.compareTo(contextVariables.getMyHashPredecessor())<=0)
         {
             return true;
         }
         else
         {
             return false;
         }

    }

    private boolean LookUp(String newNode){
        String hashofnewnode=genHashNodeWrapper(newNode);
        ContextVariables contextVariables=(ContextVariables)getContext();
        if(hashofnewnode.compareTo(contextVariables.getMyHashPredecessor())>0 && hashofnewnode.compareTo(contextVariables.getMyHashNode())<=0)
        {
            return true;
        }
        else if(hashofnewnode.compareTo(contextVariables.getMyHashPredecessor())>0 && contextVariables.getMyHashPredecessor().compareTo(contextVariables.getMyHashNode())>0)
        {
            return true;
        }
        else if(contextVariables.getMyHashPredecessor().compareTo(contextVariables.getMyHashNode())>0 && hashofnewnode.compareTo(contextVariables.getMyHashPredecessor())<=0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    private String getPortId(String NodeId){
        switch(NodeId){
            case "5554":
                return "11108";
            case "5556":
                return "11112";
            case "5558":
                return "11116";
            case "5560":
                return "11120";
            case "5562":
                return "11124";
        }
        return "";
    }

}
