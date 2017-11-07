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
    struct pkt buffer[BUFFER_SIZE] ;
        int ackonum=0;
	
	struct pkt globalpkt;
	
int computeChecksum(struct pkt packet)
{
    int i,sum=0;
	 int check=0;
	 char str[20];
	 memcpy(str, packet.payload,20);
     printf(" compute check : %s  length %d\n",str, strlen(str));
	 for(i=0;i<20;i++)
	{
		//printf("%char c\n",packet.payload[i]);
        //check = atoi(str);
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
    printf("A output is called");
    struct pkt packet;
	int i;
	if(cansend==false && message.data[0]!='\0')
	{
		      printf("too fast,buffering.....");
		     packet.seqnum=seqnum;  //1
		     packet.acknum=ackonum;
		     memcpy(packet.payload,message.data,20);
			 i= computeChecksum(packet);
			 printf("check retur %d\n",i);
			 packet.checksum=i;
			 
		     buffer[ctr].seqnum=packet.seqnum;
			 buffer[ctr].acknum=ackonum;
			 memcpy(buffer[ctr].payload,packet.payload,20);
			 buffer[ctr].checksum=packet.checksum;
			 ctr++;
			 datahere=true;
	}
	if(cansend==true && message.data[0]!='\0')
	{      
          printf("hi");
 		packet.seqnum=seqnum;   //0
		packet.acknum=ackonum;    //0
		    printf("seq num: %d and ack num: %d\n " ,packet.seqnum, packet.acknum);
			
	    memcpy(packet.payload,message.data,20);
		  printf("message :%s and length %d\n", packet.payload, strlen(packet.payload));
	
		 //memset((char*)&buff,'\0',sizeof(buff));
		 snum = seqnum;    //0
		i= computeChecksum(packet);
		printf("check retur %d\n",i);
		packet.checksum=i;
		printf("check returned %d\n", packet.checksum);
		
		   //store packet
		     
		    /* buffer[ctr].seqnum=packet.seqnum;
			 buffer[ctr].acknum=packet.acknum;
			 memcpy(buffer[ctr].payload,packet.payload,20);
			 buffer[ctr].checksum=packet.checksum;
			  ctr++;
			  datahere=true;
                    pop(head)
					  move ptr forward and make new head;*/
			memcpy(&globalpkt, &packet, sizeof(struct pkt));  
 			tolayer3(0,packet);
                 			
		       printf("f");
		    
               starttimer(0,timer_ticks);
                             cansend=false;
		            							 
					  
                                  
           								                     /*if(msg!=NULL)
				 														make pkt
																	tolayer3(A,pkt);// tolayer3 called here
																	storepkt();
																increment pkt counter
																start timer(pkt)
																   timer++;
															 flag=false;
															 /*if(timer==threshold) // threshold -- 10 timer_units + 2 buffering times
																A_timerinterrupt();*/
    }
	seqnum=!seqnum;
}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(packet)
  struct pkt packet;
{
	 printf("A input is called");
	 struct pkt temp;
    int calc=0,i;
	        printf("seq num: %d and ack num: %d\n " ,snum, packet.acknum);
			  //printf("message :%s and length %d\n",packet.payload, strlen(packet.payload));
        calc=computeChecksum(packet);
		printf("calc value is%d  pktchecksum %d\n",calc, packet.checksum);

          if(packet.acknum==seqnum && calc==packet.checksum)   //handle corruption here
		  {
			  printf("h");
			  stoptimer(0); 
                  //1
        	
			             
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
                                snum = temp.seqnum;  //1
                               if(ctr==0)
							       { datahere=false; }		//send head 1st packet
							  
						  }  
						      if(datahere==false)
							  {  
						          
								   cansend=true;

							  }
						  
                                     
                           	
							  
		        //memset((char*)&buff,'\0',sizeof(buff));
		  }  
		          
                                                        /*else
															receive(ack)
																	if(ack==pck no)
																		flag=true;
																			stop timer(pkt)*/

																			
}

/* called when A's timer goes off */
void A_timerinterrupt()
{
	  printf("A timer is called");
	struct pkt packet;
         starttimer(0,timer_ticks);
		 //packet.seqnum=seqnum;
         tolayer3(0,globalpkt); 
		 printf("i");
		 /*start_timer()
																resend(pkt);*/
}  

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init()
{
	int seqnum=0;
    /*bool cansend=true;
	int seqnum=0;
	float timer=0;
	float timer_ticks=10.0;
	char buffer[1000];*/
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
	     printf("j");
		 printf("seq num: %d and ack num: %d\n " ,packet.seqnum, packet.acknum);
			  printf("message :%s and length %d\n",packet.payload, strlen(packet.payload));
		 convert=computeChecksum(packet);
		 if(convert==packet.checksum && packet.seqnum== ackonum)
		 {  flipbit=0;	}
                      
                   
		 else 
		  {
                      flipbit=1;
		      
               //       packet.acknum=~ackonum;
                 //     tolayer3(1,packet);
		  }

		 if(flipbit==0)
		 {  
		          	printf("k");
				
                     memcpy(message.data,packet.payload,20);
		                printf("l");
		            tolayer5(1,message.data);
                            packet.acknum=ackonum;
					  
			               //   memcpy(buffer,packet,sizeof(packet));
			
		              
		              printf("m");
					  
		 /*memset(buffer,'\0',sizeof(buffer));
		 sprintf(buffer,"%d",packet.acknum);
		 strcat(buffer, store);
		 printf("n");
		 strcat(buffer," " );
		 printf("o");
		 strcat(buffer,packet.payload);
		 printf("p");
		 strcat(buffer," ");
		 printf("q");*/
		  ackonum=!ackonum;
                  tolayer3(1,packet);
		 }
               else
                 { 
			       printf("error in packet received,sending previous ack");
                   packet.acknum=!ackonum;
		           tolayer3(1,packet);
                 }  
    }
      	
                                                               /*     B_init();
	                                                if(pkt==corrupted)//checksum compute here
													      sleep();
														   else if( pkt=rcvpket)
														   {
															    receivepacket(pkt);
																extract_data();
																 tolayer5(B,data);
															    rcvpkt+=1;
														   }
														      sendpkt(rcvpkt);
															  call tolayer3(B,pkt);  // ack sent here */
}

/* the following routine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init()
{
    // int ackonum=1;
	int ackonum=0;
}
