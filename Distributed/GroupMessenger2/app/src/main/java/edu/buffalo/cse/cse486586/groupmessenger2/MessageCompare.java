package edu.buffalo.cse.cse486586.groupmessenger2;

/**
 * Created by abina on 21-05-2018.
 */
import java.util.Comparator;

public class MessageCompare {

    public int compare(MessageAgreed lhs, MessageAgreed rhs) {
        try {
            int lhs_port = Integer.parseInt(lhs.getOriginalId().split(GroupMessengerActivity.processdelim)[0]);
            int rhs_port = Integer.parseInt(rhs.getOriginalId().split(GroupMessengerActivity.processdelim)[0]);
            int lhs_count = Integer.parseInt(lhs.getOriginalId().split(GroupMessengerActivity.processdelim)[1]);
            int rhs_count = Integer.parseInt(rhs.getOriginalId().split(GroupMessengerActivity.processdelim)[1]);


            if (lhs_port > rhs_port) {
                return 1;
            } else if (lhs_port < rhs_port) {
                return -1;
            } else if (lhs_count > rhs_count) {
                return 1;
            } else if (lhs_count < rhs_count) {
                return -1;
            }
            return 0;
        }catch(Exception e){
            return 0;
        }

    }
}
