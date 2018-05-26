package edu.buffalo.cse.cse486586.simpledynamo;

/**
 * Created by abina on 21-05-2018.
 */
import android.app.Application;

public class ContextVariables {

    private static String myPort="";
    private static String myNodeId="";
    private static String myHashNode="";
    private static String mySuccessorOne="";
    private static String mySuccessorTwo="";

    public static String getMyPort() {
        return myPort;
    }

    public static void setMyPort(String myPort) {
        ContextVariables.myPort = myPort;
    }

    public static String getMyNodeId() {
        return myNodeId;
    }

    public static void setMyNodeId(String myNodeId) {
        ContextVariables.myNodeId = myNodeId;
    }

    public static String getMyHashNode() {
        return myHashNode;
    }

    public static void setMyHashNode(String myHashNode) {
        ContextVariables.myHashNode = myHashNode;
    }

    public static String getMySuccessorOne() {
        return mySuccessorOne;
    }

    public static void setMySuccessorOne(String mySuccessorOne) {
        ContextVariables.mySuccessorOne = mySuccessorOne;
    }

    public static String getMySuccessorTwo() {
        return mySuccessorTwo;
    }

    public static void setMySuccessorTwo(String mySuccessorTwo) {
        ContextVariables.mySuccessorTwo = mySuccessorTwo;
    }







}
