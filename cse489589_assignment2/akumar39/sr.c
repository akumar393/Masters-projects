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
#define INTERVAL 1.0

int N;
int nextseqnum=0,i,sendbase=0,rcvbase=0, head=0, outoforder;
bool datainbuffer=false, flag=false;
int timeseq;
bool ackreceived[1000];
float timer_ticks=50.0;
bool marked[1000];
    struct pkt sendbuffer[BUFFER_SIZE];
	    struct pkt rcvbuffer[BUFFER_SIZE];
         int ctr=0;
		struct pkt globalpkt;
		float total_time=0.0;
		float timeleft=0.0;
		int rear=0;
		static int top=0;
		
struct queue
{
	struct pkt store;
	float timeout;

}p[1000];

/*struct packetinfo
{
	struct pkt buff;
	float timeout;
}p[1000];*/	

void enqueue( struct pkt packet)
{   
   
   memcpy(&p[rear].store, &packet, sizeof(struct pkt));
    p[rear].timeout= get_sim_time() + timer_ticks;  //195
	printf("Timeout value set for packet is%f\n", p[rear].timeout);
    rear++; 
}

/*void addpacket(struct pkt packet)
{
   memcpy(&p[ctr].buff, &packet, sizeof(packet));	
   p[ctr].timeout= get_sim_time() + timer_ticks;
   ctr++;
}*/	

/*void trash(struct packetinfo p)
{
    struct 	pkt temp;
	memcpy(&temp, &p.buff, sizeof(p.buff));	
	p.timeout= 0.0;
}	*/
void dequeue(int var)
{
	struct pkt temp;
	int t;
	printf("Rear%d\n",rear);
	printf("Timeout value is%f\n" ,p[top].timeout);
	printf("shifting packet data and decr rear\n");	
	                   for(i=0;i<rear;i++)
					   {
						   if(p[i].store.seqnum==var)
						  {
							memcpy(&temp,&p[i].store, sizeof(p[i].store));
                              t=i;
							  break;
						  }
                       }		
						printf("t %d\n",t);					   
                           for(i=t;i<rear;i++)						
						   {
							   p[i]=p[i+1];  //shift all elements
								printf("Timeout value is%f\n" ,p[i].timeout);
						   }			
							
					//	p[rear].store.seqnum=-1;
						rear--;
						printf("Rear now is %d\n",rear);
						
}	
	
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
bool istimerrunning()
{
	float curr= get_sim_time();
	printf("Current time%f",curr);
	printf("Timeout of head element%f", p[0].timeout);
	if(rear>0)
		return true;
	else
		return false;
}	

bool iswindowfull(int seqnum, int base)
{
	N=getwinsize();
	      if(seqnum>=base+N)
		           return true;
		  else  
                  return false;			  
	
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
	printf("A output is called\n");
		printf("Rear Aoutput now is%d\n",rear);

   struct pkt packet;
  // struct queue q;
    N =getwinsize();
     int i=0;
	 
	 if(message.data[0]!='\0')
	{
		 printf("message :%s and length %d\n", message.data, strlen(message.data));
		 printf("a");
	     if(iswindowfull(nextseqnum,sendbase))
		 {
                  printf("Sequence no. out of window,buffering packet\n");
			      sendbuffer[nextseqnum].seqnum= nextseqnum;
                  sendbuffer[nextseqnum].acknum=nextseqnum;
				  memcpy(sendbuffer[nextseqnum].payload,message.data,20);
				  nextseqnum++;
				  outoforder=nextseqnum;
				  datainbuffer=true;

         }	
 
         if(nextseqnum>=sendbase && nextseqnum<sendbase+N)
		{
			  printf("Send base now is %d\n" ,sendbase);
			packet.seqnum=nextseqnum;
			packet.acknum=nextseqnum;
			memcpy(packet.payload,message.data,20);
			printf("message :%s and length %d\n", packet.payload, strlen(packet.payload));
			i= computeChecksum(packet);
			packet.checksum=i;
					printf("check returned %d\n", packet.checksum);
					
							
			    sendbuffer[head].seqnum=packet.seqnum;
			    sendbuffer[head].acknum=packet.seqnum;
			    memcpy(sendbuffer[head].payload,packet.payload,20);
			    sendbuffer[head].checksum=packet.checksum;
				head++;
				
				tolayer3(0,packet);
				
                    					      
						 
                     if (sendbase<nextseqnum || sendbase==nextseqnum)
						 
					 {      
					       if(istimerrunning())
						   {
                            	//addpacket(packet);
								enqueue(packet);  //1
						   }
                           else
                           {	
					          enqueue(packet);  
                              total_time =  timer_ticks;					   
							  printf("Starting timer from Aoutput for %d\n",nextseqnum);
                              starttimer(0,total_time);
							}
					 }
				 nextseqnum++;	//1 //2
		}
    }
		
 }

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(packet)
  struct pkt packet;
{
      printf("A input is called\n");
	  	printf("Rear Ainput now is%d\n",rear);

	  int calc=0,i=0;
	   float current = get_sim_time();  
	   float rem_time;
	  	N=getwinsize();
	  calc=packet.acknum;
		printf("calc value is%d\n",calc);
		printf("ack value is%d\n",packet.acknum);
		printf("send base:%d\n" ,sendbase);
		
		if(calc==packet.checksum && packet.acknum>=sendbase && packet.acknum< sendbase +N)
		{
			 printf("c");
			ackreceived[packet.acknum]=true;
			 printf("\nCorrect ack received\n");
			 printf("SEND BASE%d\n",sendbase);  //1
             printf("ACK RECEIVED%d\n", packet.acknum);  //3
			 printf("sendbase stays there]\n");
					    dequeue(packet.acknum); 
	                    p[packet.acknum].timeout =0.0;
						
					if(packet.acknum==sendbase)
					{	
				      printf("first element, moving sendbase forward\n");
					  stoptimer(0);
					 
					 if(rear>0)
					  {	 
                        printf("SEND BASE  now is %d\n",sendbase);
                        current = get_sim_time();  
	                     rem_time = p[0].timeout - current; //50 //100 // pop first packet and calculate its rem time 
	                     printf("Remaining time%f",rem_time);  
			   			 printf("Starting timer from A_input\n");
                 
                       starttimer(0, rem_time);
                      }
					}
			
              while(ackreceived[sendbase+i]==true)			
         	{
			       i++;
			}	
				  sendbase=sendbase+i;
			 if(datainbuffer==true)
					{
						printf("it came inside\n");
						while(sendbase<outoforder)
					  {
						 printf("inside while");
						 packet.seqnum=sendbuffer[sendbase].seqnum;
						 packet.acknum=sendbuffer[sendbase].acknum;
						 memcpy(packet.payload,sendbuffer[sendbase].payload,20);
						 packet.checksum=computeChecksum(packet);
					
						 total_time = timer_ticks;
						 						 tolayer3(0,packet);
												 starttimer(0, total_time );
						 sendbase++;
				
				       }
			        } 	
		}			
		else 
		{ 
	        printf("reached here");
	       // p[nextseqnum].timeout= get_sim_time() + timer_ticks;
 
			//starttimer(0, p[nextseqnum].timeout);
			printf("Ack received out of window");
			printf("Packet discarded");
		}
   		
}

/* called when A's timer goes off */
void A_timerinterrupt()
{
	int currentseq;
	printf("Timer interrupt called\n");
	printf("Rear timer interrupt now is%d\n",rear);
	struct pkt packet;
	currentseq = p[0].store.seqnum;
     float current = get_sim_time();   //200   //250
	          dequeue(currentseq);
			 packet.seqnum = sendbuffer[currentseq].seqnum;
	         packet.acknum=sendbuffer[currentseq].acknum;
			 memcpy(packet.payload,sendbuffer[currentseq].payload,20);
			 packet.checksum=sendbuffer[currentseq].checksum;
			  		           enqueue(packet);

	         float rem_time = p[0].timeout - current; //50 //100 // pop second packet and calculate its rem time 
	           printf("Remaining time%f\n",rem_time);  
			   			 printf("Starting timer from timerinterrupt\n");
                 
            starttimer(0, rem_time);
	        
    	
	
		printf("sim time%f\n",get_sim_time());
		printf("timeout%f\n",p[timeseq].timeout); 
             
                  tolayer3(0,packet);
			
		       
	
}  

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init()
{
	int i;
	N= getwinsize();
	for(i=sendbase;i< sendbase+N; i++)
		       {
			ackreceived[i]=false;
		        }
  
}

/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(packet)
  struct pkt packet;
{
	printf("B input is called\n");
    struct msg message;	
	int i,j,convert=0, count=0,temp=0;
	int storeseq;
	N= getwinsize();
	
	
	

	if(packet.payload[0]!='\0')  //handle corruption here
	{  
	     printf("j");
		 printf("seq num: %d and ack num: %d\n " ,packet.seqnum, packet.acknum);
	     printf("message :%s and length %d\n",packet.payload, strlen(packet.payload));
		 convert=computeChecksum(packet);
		 		printf("check returned %d\n", convert);
                 printf("coming sequence no, %d\n", packet.seqnum);
		 if(convert==packet.checksum && packet.seqnum>=rcvbase && packet.seqnum < rcvbase+N-1)
		 {
			 printf("%d",rcvbase);
			 storeseq= packet.seqnum;
			 marked[packet.seqnum]=true;
			 printf("Packet marked true\n",packet.seqnum);
                 
				rcvbuffer[storeseq].seqnum=packet.seqnum;
			    rcvbuffer[storeseq].acknum=packet.seqnum;
			    memcpy(rcvbuffer[storeseq].payload,packet.payload,20);
			    rcvbuffer[storeseq].checksum=packet.checksum;

    			printf("sending back acknowledgment\n");
                   packet.acknum= packet.seqnum;
                   packet.checksum=packet.acknum;
                   tolayer3(1,packet);

                for(i=rcvbase; i< rcvbase + N-1 ; i++)
				{
                    if(marked[i]==false)
					{
						temp=i;
				        printf("temp from ifis %d\n",temp);	
					     break;
					}	 
					
                }		
				     printf("temp is %d\n",temp);	
				     printf("rcvbase now is%d\n", rcvbase);
				    for(j=rcvbase;j<temp;j++)
					{
						 memcpy(message.data,rcvbuffer[j].payload,20);
		                 printf("l");
		                 tolayer5(1,message.data);	
                        rcvbase= rcvbase+1;   
						 
					}
					printf("rcvbase now is%d\n", rcvbase);
		}
		
	  else if( packet.seqnum<rcvbase)
	  {
		  packet.acknum=packet.seqnum;
		  packet.checksum=packet.seqnum;
		  tolayer3(1,packet);
		  
	  }
	 else if(iswindowfull(packet.seqnum,rcvbase) || convert!= packet.seqnum)
	{
		printf("Packet discarded");
	} 
}	

}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init()
{
	int i;
     for(i=rcvbase;i<1000; i++)
		marked[i]=false;
}
