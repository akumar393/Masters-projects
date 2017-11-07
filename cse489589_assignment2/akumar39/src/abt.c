#include "../include/simulator.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define UNUSED 0
#define true 1
#define false 0
#define BUFFER_SIZE 1000
    bool cansend=true;
	bool datahere=false;
	int flipbit=0, seqnum=0, snum =0;
	int ctr=0;
	float timer_ticks=20.0;
    struct pkt buffer[BUFFER_SIZE] ;      //Buffer to hold packets
        int ackonum=0;
	
	struct pkt globalpkt;
	
int computeChecksum(struct pkt packet)          //Calculates checksum of the packet
{
    int i,sum=0;
	 int check=0;
	 char str[20];
	 memcpy(str, packet.payload,20);
	 for(i=0;i<20;i++)
	{
		
		 check+= (int)(packet.payload[i]);
    }
     sum+= packet.seqnum + packet.acknum + check;	 
	 printf("final sum %d\n",sum);
	return sum;


}	

	
/* ******************************************************************
 ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose

   This code should be used for PA2, unidirectional data transfer 
   protocols (from A to B). Network properties:
   - one way network delay averages five time units (longer if there
     are other messages in the channel for GBN), but can be larger
   - packets can be corrupted (either the header or the data portion)
     or lost, according to user-defined probabilities
   - packets will be delivered in the order in which they were sent
     (although some can be lost).
**********************************************************************/

/********* STUDENTS WRITE THE NEXT SIX ROUTINES *********/

/* called from layer 5, passed the data to be sent to other side */
void A_output(message)
  struct msg message;
{  
    struct pkt packet;
	int i;
	if(cansend==false && message.data[0]!='\0')   //Buffer messages arriving too quickly at transport layer
	{
		      printf("too fast,buffering.....");
		     packet.seqnum=seqnum;  //1
		     packet.acknum=ackonum;
		     memcpy(packet.payload,message.data,20);
			 i= computeChecksum(packet);
			 packet.checksum=i;
			 
		     buffer[ctr].seqnum=packet.seqnum;
			 buffer[ctr].acknum=ackonum;
			 memcpy(buffer[ctr].payload,packet.payload,20);
			 buffer[ctr].checksum=packet.checksum;
			 ctr++;
			 datahere=true;
	}
	if(cansend==true && message.data[0]!='\0')    // Check if a packet is in transit or if the message arriving is NULL
	{      
 		packet.seqnum=seqnum;   
		packet.acknum=ackonum;    
			
	    memcpy(packet.payload,message.data,20);
	
		 snum = seqnum;    
		i= computeChecksum(packet);
		packet.checksum=i;
		
		   
			memcpy(&globalpkt, &packet, sizeof(struct pkt));   // Storing the packet in a global packet
 			tolayer3(0,packet);
                 			
		    
               starttimer(0,timer_ticks);
                             cansend=false;
		         							 
     }
	seqnum=!seqnum;
}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(packet)
  struct pkt packet;
{
	 struct pkt temp;
    int calc=0,i;
	       
        calc=computeChecksum(packet);
		
          		//check if packet is corrupted or not and the sequence number lies within the window
         if(packet.acknum==seqnum && calc==packet.checksum)   //handle corruption here
		  {
			  stoptimer(0); 
        	
			             //check if there is any packet in the buffer,if there is send it
			             if(datahere==true && ctr>0)
						 { 
					        printf("o");
					        temp= buffer[0];                 //1st packet out of buffer
							for(i=0;i<ctr;i++)
							{
								buffer[ctr]=buffer[ctr+1];  //shift all elements
							}
								ctr--;   
                                printf("sending buffer data");	
								memcpy(&globalpkt, &temp, sizeof(struct pkt));								
								tolayer3(0,temp); 
                                snum = temp.seqnum;  
                               if(ctr==0)
							       { datahere=false; }		//send head 1st packet
							  
						  }  
						      if(datahere==false)
							  {  
						          
								   cansend=true;

							  }
						  
                                     
                           	
							  
		        
		  }  
		          
                                                      

																			
}

/* called when A's timer goes off */
void A_timerinterrupt()                   
{
	struct pkt packet;
         starttimer(0,timer_ticks);
         tolayer3(0,globalpkt);           //Send the copy of the packet to network layer
		 printf("i");
		 
}  

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init()
{
	int seqnum=0;
   
}

/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at
 B*/
void B_input(packet)
  struct pkt packet;
{   
    printf("B input d called");
    struct msg message;	
	int i,convert=0;
	if(packet.payload[0]!='\0')  //handle corruption here
	{  
	    
		 convert=computeChecksum(packet);
		 if(convert==packet.checksum && packet.seqnum== ackonum)   //Check if the expected packet was received 
		 {  flipbit=0;	}
                      
                   
		 else 
		  {
                      flipbit=1;
		  }

		 if(flipbit==0)
		 {  
		          	printf("k");
				
                     memcpy(message.data,packet.payload,20);
		                printf("l");
		            tolayer5(1,message.data);
                            packet.acknum=ackonum;
					  
			             
			
		              
		              printf("m");
					  
		  ackonum=!ackonum;
                  tolayer3(1,packet);
		 }
               else                             //Send last received ack if wrong packet was received
                 { 
			       printf("error in packet received,sending previous ack");
                   packet.acknum=!ackonum;
		           tolayer3(1,packet);
                 }  
    }
      	
}

/* the following routine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init()
{
	int ackonum=0;
}
