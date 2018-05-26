package edu.buffalo.cse.cse486586.groupmessenger2;

/**
 * Created by abina on 20-05-2018.
 */

class MessageAgreed implements Comparable<MessageAgreed>{

   double seqNum;
   String originalId;
   String msgData;
   boolean isDeliverable;

    public MessageAgreed(double v, String msg, String s, boolean b) {

        this.seqNum=v;
        this.originalId=msg;
        this.msgData=s;
        this.isDeliverable=b;

    }

    public double getSeqNum() {
        return seqNum;
    }

    public void setSeqNum(double seqNum) {
        this.seqNum = seqNum;
    }

    public String getOriginalId() {
        return originalId;
    }

    public void setOriginalId(String originalId) {
        this.originalId = originalId;
    }

    public String getMsgData() {
        return msgData;
    }

    public void setMsgData(String msgData) {
        this.msgData = msgData;
    }

    public boolean isDeliverable() {
        return isDeliverable;
    }

    public void setDeliverable(boolean deliverable) {
        isDeliverable = deliverable;
    }


     public int compareTo(MessageAgreed obj)
     {
         if(this.seqNum>obj.seqNum)
             return 1;
         else if(this.seqnum<obj.seqnum)
             return -1;
         else
             return 0;
     }
}
