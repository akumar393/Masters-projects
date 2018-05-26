package edu.buffalo.cse.cse486586.simpledynamo;

import android.content.ContentProvider;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.MatrixCursor;
import android.net.Uri;
import android.os.AsyncTask;
import android.telephony.TelephonyManager;
import android.util.Log;

import org.w3c.dom.Node;

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
import java.util.Arrays;
import java.util.Formatter;
import java.util.Hashtable;
import java.util.ServiceLoader;

public class SimpleDynamoProvider extends ContentProvider {

	static private final String TAG=SimpleDynamoProvider.class.getSimpleName();
	static final String[] REMOTE_PORT={"11108","11112","11116","11120","11124"};
	static final int SERVER_PORT=10000;
	static final String [] Node_List={"5562","5556","5554","5558","55560"};
	static final String msgdelimeter="####";
	static final String cursordelimeter="<==>";

	static final String InsertTask="InsertTask";
	static final String InsertReplicateTask="InsertReplicateTask";
	static final String QueryTask="QueryTask";
	static final String ReturnQueryTask="ReturnQueryTask";
	static final String DeleteTask="DeleteTask";
	static final String StarQuery="StarQuery";
	static final String StarDelete="StarDelete";
	static final String ReturnStarQuery="ReturnStarQuery";
	static final String RecoveryTask = "RecoveryTask";
	static final String UpdateTask= "UpdateTask";

	final static Uri uri = buildUri("content", "edu.buffalo.cse.cse486586.simpledynamo.provider");
	private static final String KEY="key";
	private static final String VALUE="value";

	static final String ourDHTS="\"@\"";
	static final String allDHTS="\"*\"";

	Hashtable<String,String> query=new Hashtable<String, String>();
	static final String[] columnnames={KEY,VALUE};
	MatrixCursor starmsgCursor=new MatrixCursor(columnnames);
	static final String NULL="null";

	String [] columns={KEY,VALUE};


	@Override
	public synchronized int delete(Uri uri, String selection, String[] selectionArgs) {
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
			new DeleteStarQueryClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR);

            else{
				getContext().deleteFile(selection);
			}
		}
		return 0;
	}

	@Override
	public  String getType(Uri uri) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public synchronized Uri insert(Uri uri, ContentValues values) {
		// TODO Auto-generated method stub
		String key;
		String value;
		ContextVariables contextVariables=(ContextVariables)getContext();
		try {
			key = values.get(KEY).toString();
			value = values.get(VALUE).toString();
			String destnode=keyLookUp(key);
			if(destnode.equals(contextVariables.getMyNodeId())){
				FileOutputStream fos=getContext().openFileOutput(key,Context.MODE_PRIVATE);
				fos.write(value.getBytes());
				fos.close();
			}
			else {
				new InsertClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR, getPortId(destnode), key, value);
			}
			new InsertReplicateClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR, getPortId(destnode)), key, value);
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
	public  boolean onCreate() {
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
		int index= Arrays.asList(Node_List).indexOf(portStr);
		contextVariables.setMySuccessorOne(Node_List[(index+1)%5]);
		contextVariables.setMySuccessorTwo(Node_List[(index+2)%5]);

		try{
			ServerSocket server=new ServerSocket(SERVER_PORT);
			new ServerTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR,server);

		}catch (IOException e) {
			Log.e(TAG, "Can't create a ServerSocket");
			return false;
		}

		String []files=getContext().fileList();
		if(files!=null && files.length>0){
			for(String file:files){
				getContext().deleteFile(file);
			}
		}
		new RecoveryClientTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR,portStr);
		return false;

	}

	@Override
	public synchronized Cursor query(Uri uri, String[] projection, String selection,
			String[] selectionArgs, String sortOrder) {
		// TODO Auto-generated method stub
		ContextVariables contextVariables = (ContextVariables) getContext();
		MatrixCursor cursor = new MatrixCursor(columnnames);
		int keyIndex = cursor.getColumnIndex(KEY);
		int valueIndex = cursor.getColumnIndex(VALUE);
		FileInputStream fis;
		BufferedInputStream bis;
		int temp;
		String msgTosend = "";
		if (selection.equals(ourDHTS)) {
			String[] files = getContext().fileList();
			for (String file : files) {
				msgTosend = "";
				try {
					fis = getContext().openFileInput(file);
				} catch (FileNotFoundException e) {
					e.printStackTrace();
				}
				bis = new BufferedInputStream(fis);
				try {
					while ((temp = bis.read()) != -1) {
						msgTosend += (char) temp;
					}
					bis.close();
				} catch (IOException e) {
					e.printStackTrace();
				} catch (NullPointerException npe) {
					npe.printStackTrace();
				}
				cursor.addRow(new String[]{file, msgTosend});
			}
			return cursor;
		} else if (selection.equals(allDHTS)) {

			String[] files = getContext().fileList();
			for (String file : files) {
				msgTosend = "";
				try {
					fis = getContext().openFileInput(file);
				} catch (FileNotFoundException e) {
					e.printStackTrace();
				}
				bis = new BufferedInputStream(fis);
				try {
					while ((temp = bis.read()) != -1) {
						msgTosend += (char) temp;
					}
					bis.close();
				} catch (IOException e) {
					e.printStackTrace();
				} catch (NullPointerException npe) {
					npe.printStackTrace();
				}
				starmsgCursor.addRow(new String[]{file, msgTosend});
			}
			new StarQueryClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR, contextVariables.getMyPort());
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			return starmsgCursor;
		} else {
			try {
				query.put(selection, NULL);
				String destnode = keyLookUp(selection);
				if (destnode.equals(contextVariables.getMyNodeId())) {
					try {
						fis = getContext().openFileInput(selection);
					} catch (FileNotFoundException e) {
						e.printStackTrace();
					}
					bis = new BufferedInputStream(fis);
					try {
						while ((temp = bis.read()) != -1) {
							msgTosend += (char) temp;
						}
						bis.close();

					} catch (IOException e) {
						e.printStackTrace();
					}
				} else {
					String origin = contextVariables.getMyPort();
					new QueryClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR, destnode, selection, origin);
				}

				while (true) {
					if (query.get(selection) != null) {
						cursor.addRow(new String[]{selection, query.get(selection)});
					} else {
						//Log.w("Cursor is empty");
					}

				}
			} catch (NullPointerException npe) {
				Log.w(TAG," Query NullPointerException"+ npe.getMessage());
			} catch (Exception e){
				Log.w(TAG," Query Exception"+ e.getMessage());
			}
		}
		return cursor;
	}

	@Override
	public synchronized int update(Uri uri, ContentValues values, String selection,
			String[] selectionArgs) {
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


	private class ServerTask extends AsyncTask<ServerSocket, String, Void> {
		@Override
		protected Void doInBackground(ServerSocket... sockets) {
			ServerSocket serverSocket = sockets[0];

			try {
				while (true) {

					Socket socket = serverSocket.accept();
					InputStream io = socket.getInputStream();
					BufferedReader bio = new BufferedReader(new InputStreamReader(io));
					String incoming = bio.readLine();
					socket.close();

					String[] splitter = incoming.split(msgdelimeter);
					ContextVariables contextVariables = (ContextVariables) getContext();
					FileInputStream fis;
					BufferedInputStream bis;
					int temp;
					ContentValues cv;
					String key;
					String value;
					String msgvalue = "";

					switch (splitter[0]) {

						case RecoveryTask:
							String[] files = getContext().fileList();
							String predecessorOne = getPredecessorOne(splitter[1]);
							String predecessorTwo = getPredecessorTwo(splitter[1]);
							String updatemsg = "";
							for (String file : files) {
								String coordinate = keyLookUp(file);
								if (coordinate.equals(splitter[1]) || coordinate.equals(predecessorOne) || coordinate.equals(predecessorTwo)) {
									msgvalue = "";
									try {
										fis = getContext().openFileInput(file);
										bis = new BufferedInputStream(fis);
										while ((temp = bis.read()) != -1) {
											msgvalue += (char) temp;
										}
										bis.close();
									} catch (IOException ioe) {
										Log.e(TAG, "IOException processing requestTask : " + ioe.getMessage());
									} catch (NullPointerException npe) {
										Log.e(TAG, "NullPointerException processing requestTask : " + npe.getMessage());
									}
									updatemsg = file + msgdelimeter + msgvalue + msgdelimeter;
								}
							}
							new UpdateClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR, splitter[1], updatemsg);
							break;

						case UpdateTask:
							for (String msg : splitter) {
								if (msg.contains(cursordelimeter)) {
									key = msg.split(cursordelimeter)[0];
									value = msg.split(cursordelimeter)[1];
									FileOutputStream fos = getContext().openFileOutput(key, Context.MODE_PRIVATE);
									try {
										fos.write(value.getBytes());
									} catch (IOException e) {
										e.printStackTrace();
									}
									try {
										fos.close();
									} catch (IOException e) {
										e.printStackTrace();
									}
								}
							}
							break;
						case InsertTask:
							try {
								key = splitter[1];
								value = splitter[2];
								FileOutputStream fos = getContext().openFileOutput(key, Context.MODE_PRIVATE);
								fos.write(value.getBytes());
								fos.close();
							} catch (IOException ioe) {
								Log.e(TAG, "ReplicateInsert Exception" + ioe.getMessage());
							} catch (NullPointerException npe) {
								Log.e(TAG, "ReplicateInsert Exception" + npe.getMessage());
							} catch (Exception e) {
								Log.e(TAG, "ReplicateInsert Exception" + e.getMessage());
							}
							 break;

						    case InsertReplicateTask:
									try {
										key = splitter[1];

										value = splitter[2];
										FileOutputStream fos = getContext().openFileOutput(key, Context.MODE_PRIVATE);
										fos.write(value.getBytes());
										fos.close();
									} catch (IOException ioe) {
										Log.e(TAG, "ReplicateInsert Exception" + ioe.getMessage());
									} catch (NullPointerException npe) {
										Log.e(TAG, "ReplicateInsert Exception" + npe.getMessage());
									} catch (Exception e) {
										Log.e(TAG, "ReplicateInsert Exception" + e.getMessage());
									}
									break;

						       case QueryTask:

											MatrixCursor curse = new MatrixCursor(columnnames);

											try {
												fis = getContext().openFileInput(splitter[1]);
												bis = new BufferedInputStream(fis);
												while ((temp = bis.read()) != -1) {
													msgvalue += (char) temp;
												}
												bis.close();
												curse.addRow(new String[]{splitter[1], msgvalue});
											} catch (FileNotFoundException e1) {
												e1.printStackTrace();
											} catch (IOException e1) {
												e1.printStackTrace();
											}
											int keyindex = curse.getColumnIndex(KEY);
											int valueindex = curse.getColumnIndex(VALUE);
											key = curse.getString(keyindex);
											value = curse.getString(valueindex);
											String msgtoSend = ReturnQueryTask + msgdelimeter + key + msgdelimeter + value + msgdelimeter + splitter[2] + msgdelimeter;
											callClientTask(msgtoSend);

									    break;

								case ReturnQueryTask:
									query.put(splitter[1], splitter[2]);
									break;
								case StarQuery:
									String rows = "";
									if (!splitter[1].equals(contextVariables.getMyPort())) {

										Cursor curser = query(uri, null, splitter[1], null, null);
										if (curser != null && curser.getCount() > 0) {
											int keyIndex = curser.getColumnIndex(KEY);
											int valueIndex = curser.getColumnIndex(VALUE);
											if (curser.moveToFirst()) {
												do {
													rows += curser.getString(keyIndex) + cursordelimeter + curser.getString(valueIndex) + msgdelimeter;
												} while (curser.moveToNext());
											}
											new ReturnStarQueryClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR, splitter[1], rows);
										}
									}
									break;

								case ReturnStarQuery:
									for (int i = 0; i < splitter.length; i++) {
										if (splitter[i].contains(cursordelimeter)) {
											starmsgCursor.addRow(new String[]{splitter[i].split(cursordelimeter)[0], splitter[i].split(cursordelimeter)[1]});
										}
									}
									break;

								case StarDelete:
									String [] filess = getContext().fileList();
									for (String dike : filess) {
										getContext().deleteFile(dike);
									}
									break;
								case DeleteTask:
									getContext().deleteFile(splitter[1]);
									break;

							}
					}

			} catch (IOException e) {
				Log.e(TAG, " Server Task IOException :" + e.getMessage() + " ==> ");
				e.printStackTrace();
			} catch (Exception e) {
				Log.e(TAG, " Server Task Exception :" + e.getMessage());
				e.printStackTrace();
			}

			return null;

		}
		protected void onProgressUpdate(String...strings) {
		}

		private void callClientTask(String msg) {
			if (msg != null) {
				String[] msgs = msg.split(msgdelimeter);
				switch (msgs[0]) {
					case InsertTask:

						break;
					case ReturnQueryTask:
						//ReturnQueryTask####key####value####originatingPort####
						new ReturnQueryClientTask().executeOnExecutor(AsyncTask.SERIAL_EXECUTOR, msgs[3], msgs[1], msgs[2]);
						break;
					case DeleteTask:


				}
			}
		}
	}
	private class RecoveryClientTask extends AsyncTask<String, Void, Void> {

		@Override
		protected Void doInBackground(String... msgs) {
			Socket socket;
			OutputStream os;
			PrintWriter pw;
			for(String Port:REMOTE_PORT) {

				if (!Port.equals(getPortId(msgs[0]))) {
					try {
						String msgToSend = RecoveryTask + msgdelimeter + msgs[0];

						socket = new Socket(InetAddress.getByAddress(new byte[]{10, 0, 0, 2}), Integer.parseInt(msgs[0]));
						os = socket.getOutputStream();
						pw = new PrintWriter(os, true);
						pw.println(msgToSend);
						pw.flush();
						socket.close();
						//pw.flush();

					} catch (UnknownHostException e) {
						e.printStackTrace();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}
			return null;
		}

	}

	private class UpdateClientTask extends AsyncTask<String, Void, Void> {

		@Override
		protected Void doInBackground(String... msgs) {
			Socket socket;
			OutputStream os;
			PrintWriter pw;
			try{
				String msgToSend=UpdateTask+msgdelimeter+msgs[1];
				socket=new Socket(InetAddress.getByAddress(new byte[]{10,0,0,2}),Integer.parseInt(msgs[0]));
				os=socket.getOutputStream();
				pw=new PrintWriter(os,true);
				pw.println(msgToSend);
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
	private class InsertReplicateClientTask extends AsyncTask<String, Void, Void> {

		@Override
		protected Void doInBackground(String... msgs) {
			ContextVariables contextVariables = (ContextVariables) getContext();
			OutputStream os;
			PrintWriter pw;
			String msgToSend;
			Socket socket;
			int index=Arrays.asList(REMOTE_PORT).indexOf(msgs[0]);
			String[] preferList = new String[]{REMOTE_PORT[(index+1)%5],REMOTE_PORT[(index+2)%5]}
			for (String Port : preferList) {
				try {
					String msgTosend = InsertReplicateTask+msgdelimeter+msgs[1]+msgdelimeter+msgs[2]+msgdelimeter;
					socket = new Socket(InetAddress.getByAddress(new byte[]{10, 0, 0, 2}), Integer.parseInt(Port));
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
				String msgToSend=StarQuery+msgdelimeter+msgs[0]+msgdelimeter;

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

	private  class ReturnStarQueryClientTask extends AsyncTask<String, Void, Void> {

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

	private class DeleteStarQueryClientTask extends AsyncTask<Void, Void, Void> {

		@Override
		protected Void doInBackground(Void... msgs) {

			try{
				Socket socket;
				OutputStream os;
				PrintWriter pw;
				String msgToSend=StarDelete+msgdelimeter;
				ContextVariables contextVariables=(ContextVariables)getContext();

				for(int i=0;i<REMOTE_PORT.length;i++)
				{
					if (!(REMOTE_PORT[i]==contextVariables.getMyPort())) {
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

	private class DeleteClientTask extends AsyncTask<String, Void, Void> {
		@Override
		protected Void doInBackground(String... msgs) {
			try {
				Socket socket;
				OutputStream os;
				PrintWriter pw;
				ContextVariables contextVariables = (ContextVariables) getContext();

				String msgTosend = DeleteTask+msgdelimeter+msgs[1];
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

	private class DeleteReplicaTask extends AsyncTask<String, Void, Void> {

		@Override
		protected Void doInBackground(String... msgs) {
				ContextVariables contextVariables = (ContextVariables) getContext();
				OutputStream os;
				PrintWriter pw;
				String msgToSend;
				Socket socket;
				String[] preferList = new String[]{getPredecessorOne(msgs[0]), getPredecessorTwo(msgs[0])};
				for (String Port : preferList) {
					try {
						String msgTosend = DeleteTask + msgdelimeter + msgs[1];
						socket = new Socket(InetAddress.getByAddress(new byte[]{10, 0, 0, 2}), Integer.parseInt(Port));
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
				}
				return null;
			}
		}



	private String keyLookUp(String newkey){
		try {
			String hashNewkey = genHash(newkey);

			if(genHash(Node_List[0]).compareTo(hashNewkey) >=0 || genHash(Node_List[4]).compareTo(hashNewkey)<0){
				return Node_List[0];
			}else if(genHash(Node_List[1]).compareTo(hashNewkey)>=0 && genHash(Node_List[0]).compareTo(hashNewkey)<0 ){
				return Node_List[1];
			}else if(genHash(Node_List[2]).compareTo(hashNewkey)>=0 && genHash(Node_List[1]).compareTo(hashNewkey)<0 ){
				return Node_List[2];
			}else if(genHash(Node_List[3]).compareTo(hashNewkey)>=0 && genHash(Node_List[2]).compareTo(hashNewkey)<0 ){
				return Node_List[3];
			}else if(genHash(Node_List[4]).compareTo(hashNewkey)>=0 && genHash(Node_List[3]).compareTo(hashNewkey)<0 ){
				return Node_List[4];
			}

		}catch(Exception e){
			Log.e(TAG,"Key LookUp Error "+ e.getMessage());
		}
		Log.e(TAG, "KeyLookupError Null value returned");
		return null;
	}

	private static Uri buildUri(String scheme, String authority) {
		Uri.Builder uriBuilder = new Uri.Builder();
		uriBuilder.authority(authority);
		uriBuilder.scheme(scheme);
		return uriBuilder.build();
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
	private String getPredecessorTwo(String nodeId){

		if(nodeId.equals("5562")){
			return "5558";
		}
		else if(nodeId.equals("5554")){
			return "5562";
		}else if(nodeId.equals("5556")){
			return "5560";
		}else if(nodeId.equals("5558")){
			return "5556";
		}else if(nodeId.equals("5560")){
			return "5554";
		}
		return null;
	}
	private String getPredecessorOne(String nodeId){

		if(nodeId.equals("5562")){
			return "5558";
		}
		else if(nodeId.equals("5554")){
			return "5562";
		}else if(nodeId.equals("5556")){
			return "5560";
		}else if(nodeId.equals("5558")){
			return "5556";
		}else if(nodeId.equals("5560")){
			return "5554";
		}
		return null;
	}




}
