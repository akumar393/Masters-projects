#include "../include/simulator.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>

#define UNUSED 0
#define true 1
#define false 0
#define BUFFER_SIZE 1000
    bool cansend=true;
	bool datainbuffer=false;
	int head=0,flipbit=0, nextseqnum=0, base=0, expectedseqnum=0, expectedacknum=0, trackinorderack=0,outoforder;
	int N;
	
	float timer_ticks=20.0;
    struct pkt buffer[BUFFER_SIZE];
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

/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/

/* called from layer 5, passed the data to be sent to other side */
void A_output(message)
  struct msg message;
{
	printf("A output is called");
    struct pkt packet;
	int i=0;
		N=getwinsize();
	if(message.data[0]!='\0')
	{
		printf("message :%s and length %d\n", message.data, strlen(message.data));
		 printf("a");
		 if(nextseqnum>=base+N)
     	 { 
			 printf("Sequence no. out of window,buffering packet");
			      buffer[nextseqnum].seqnum= nextseqnum;
                  buffer[nextseqnum].acknum=nextseqnum;
				  memcpy(buffer[nextseqnum].payload,message.data,20);
				  nextseqnum++;
				  outoforder=nextseqnum;
				  datainbuffer=true;
				  
		 }	   
		if(nextseqnum>=0 && nextseqnum<base+N)
		{
			
			packet.seqnum=nextseqnum;
			packet.acknum=nextseqnum;
			memcpy(packet.payload,message.data,20);
			printf("message :%s and length %d\n", packet.payload, strlen(packet.payload));
			i= computeChecksum(packet);
			packet.checksum=i;
					printf("check returned %d\n", packet.checksum);
					
							
			    buffer[head].seqnum=packet.seqnum;
			    buffer[head].acknum=packet.seqnum;
			    memcpy(buffer[head].payload,packet.payload,20);
			    buffer[head].checksum=packet.checksum;
				head++;
			
						memcpy(&globalpkt, &packet, sizeof(struct pkt));  
              					  			tolayer3(0,packet);

			// c base 2 nextseqnum 2 <N nextseq 3 d base 2 nextseqnum 3 <N 
			      if(base==nextseqnum)
				  {
					  printf("reached seqnum");
			          starttimer(0,timer_ticks); 
								expectedacknum=nextseqnum;	
				  }
				nextseqnum++;	
		}
        					 
	
		
	}	
}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(packet)
  struct pkt packet;
{
      printf("A input is called");
	  int calc=0;
	  	N=getwinsize();
	  calc=packet.seqnum + packet.acknum;
		printf("calc value is%d\n",calc);
		
		if(calc==packet.checksum && packet.acknum>=base && packet.acknum< base +N)
		{
			 printf("c");
			 printf("Correct ack received");
			 base=packet.acknum+1;
			 printf("Base:%d",base);
			 printf("Nextseqnum:%d",nextseqnum);

			 if(base==nextseqnum)
			   {
				   stoptimer(0);
			   } 
               else
			   { 
		         			  starttimer(0,timer_ticks); 
			   }
			  
				  if(datainbuffer==true && base==N)
					{
						printf("it came inside");
						while(base<outoforder)
					  {
						 printf("inside while");
						 packet.seqnum=buffer[base].seqnum;
						 packet.acknum=buffer[base].acknum;
						 memcpy(packet.payload,buffer[base].payload,20);
						 packet.checksum=computeChecksum(packet);
					     starttimer(0,timer_ticks);
						 tolayer3(0,packet);
						 base++;
					  }
			        } 						 

			
		}
        else
              printf("Duplicate ack,packet discarded");
}

/* called when A's timer goes off */
void A_timerinterrupt()
{
    printf("A timer is called");
	int temp=0;
		N=getwinsize();
	struct pkt packet;
	  printf("%d",base);
         starttimer(0,timer_ticks);
	  	 /*temp=base;
		 
		 while(temp<base +N)
		 {
			 packet.seqnum=buffer[temp].seqnum;
			 packet.acknum=buffer[temp].acknum;
			 memcpy(packet.payload,buffer[temp].payload,20);
			 packet.checksum= buffer[temp].checksum;
			tolayer3(0,packet);
            temp++;			
		 }	*/

        while(base<=nextseqnum-1)
		{
             packet.seqnum=buffer[base].seqnum;
			 packet.acknum=buffer[base].acknum;
			 memcpy(packet.payload,buffer[base].payload,20);
			 packet.checksum= buffer[base].checksum;
			 tolayer3(0,packet);
			 base++;
        }	
		 
}  

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init()
{
	int flipbit=0, nextseqnum=0, base=0, expectedacknum=0;

}

/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(packet)
  struct pkt packet;
{
         printf("B input is called");
    struct msg message;	
	int i,convert=0;
	if(packet.payload[0]!='\0')  //handle corruption here
	{  
	     printf("j");
		 printf("seq num: %d and ack num: %d\n " ,packet.seqnum, packet.acknum);
			  printf("message :%s and length %d\n",packet.payload, strlen(packet.payload));
		 convert=computeChecksum(packet);
		 		printf("check returned %d\n", convert);
                 printf("coming sequence no, %d\n", packet.seqnum);
				 printf("expected %d\n", expectedseqnum);
		 if(convert==packet.checksum && packet.seqnum==expectedseqnum)
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
					     
                            packet.acknum=expectedseqnum;
                            packet.seqnum=expectedseqnum;
                            packet.checksum=packet.acknum+packet.seqnum;									
		              
		              printf("sending proper ack to layer3");
					  trackinorderack= expectedseqnum;  //0
		      expectedseqnum++;
			  
                  tolayer3(1,packet);
		 }
		 else
		 {
			printf("sending last inorder  ack");
					  packet.acknum=trackinorderack;
					  packet.seqnum=trackinorderack;
                            packet.checksum=packet.acknum + packet.seqnum;
					  tolayer3(1,packet); 
		 }	 
	}	 
}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init()
{
     int expectedseqnum=0;
}
