#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/queue.h>
#include <unistd.h>
#include <string.h>
#include<time.h>

#include "../include/global.h"
#include "../include/network_util.h"
#include "../include/control_header_lib.h"
#include "../include/author.h"
#include "../include/connection_manager.h"
#include "../include/control_handler.h"
#include "../include/router_handler.h"
#include "../include/data_handler.h"
#include "../include/network_util.h"

#define INF 65535
#define TRUE 1
#define FALSE 0
#define ROUTERS 5

struct Neighbours
{
	int position;
    uint16_t neighbour_id;
	uint16_t next_hop_id;
	uint16_t router_port;
	uint16_t data_port;
	uint16_t cost;
	uint32_t ip;
	uint16_t interval;
    LIST_ENTRY(Neighbours) next;
	uint16_t timestamp;
}*connectio, con_temp[5];
LIST_HEAD(NeighboursHead, Neighbours) neighbours_list;

//void send_router_updates(int i,int router_socket,struct router_info *source_router, struct Neighbours *connection);


uint32_t count=0;
int pos=0;
uint16_t  no_of_routers;
bool wizard=FALSE;
int neighbour=0;
struct router_info r4[ROUTERS] = {{0,0,0,0,0,0,0}};
int id;


int create_router_sock( int router_port)
{
    int sock;
    struct sockaddr_in router_addr;
    socklen_t addrlen = sizeof(router_addr);

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
        ERROR("socket() failed");
	
	/* Make socket re-usable */
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, (int[]){1}, sizeof(int)) < 0)
        ERROR("setsockopt() failed");
	
	bzero(&router_addr, sizeof(router_addr));
	router_addr.sin_family = AF_INET;
    router_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    router_addr.sin_port = htons(router_port);
	
	if(bind(sock, (struct sockaddr *)&router_addr, sizeof(router_addr)) < 0)
        ERROR("bind() failed");

    return sock;

}
void maketable(struct router_info r2[] ,uint16_t  no_of_routers)
{
	printf("Making a table");
	table_payload = (char *) malloc(40*sizeof(char));

	//struct CONTROL_RESPONSE_PAYLOAD_INIT c_payload[5];
	
	for(int r=0; r< no_of_routers; r++)
	{	
            c1_payload[r].router_id = htons(r2[r].router_id);
            c1_payload[r].padding = htons(0x00);
			c1_payload[r].next_hop_id = htons(r2[r].nexthop);
			c1_payload[r].cost = htons(r2[r].cost);
    }
	table_payload = (char*)c1_payload;
}

void initrouters(struct CONTROL_PAYLOAD_INIT *c_payload)
{
	int i,b;
	LIST_INIT(&neighbours_list);
	no_of_routers= ntohs(c_payload->no_of_routers);
	printf("no of neighbours %d",no_of_routers);
	update_interval= ntohs(c_payload->update_interval);
	
	for(i=0; i< no_of_routers; i++)
	{
		printf("Router %d information is being stored",i);
		printf("count value is:%d]\n",count);
	   	registerneighbour(i,count,c_payload,update_interval);
		count=count+3;
	}
	
		
     maketable(r4, no_of_routers);
	
     for(int j=0; j< Neighbourcount();j++)
	  {
            connectio= getNeighbour1(j);                  
			send_router_updates(j,router_socket,connectio);
	  }	
	 
}

void registerneighbour(int i,int count, struct CONTROL_PAYLOAD_INIT *c_payload, uint16_t update_interval)
{
	  //uint64_t mask1 = (1 << 16)-1;
	  //uint64_t mask2 = ((1<<16) -1) << 0;
	  connectio = malloc(sizeof(struct Neighbours));	
	  //char* str =malloc(50*sizeof(char));
	  char str[INET_ADDRSTRLEN];
	 // bzero(str,sizeof(str));
	  unsigned int mask = ~(~0 << (31 - 16 + 1));     //www.stackoverflow.com
	   //uint32_t mask2 = ((1 << 32) -1);
	   
	   unsigned mask2 =0;
	   for (unsigned i=0; i<32 ;i++)
	   {  mask2 |=1 << i;  }
	   
	   struct router_info *r1 = malloc(sizeof(struct router_info));
      struct sockaddr_in router_addr;
      memset(&router_addr,'\0',sizeof(router_addr));
     	  
	 
	   uint16_t pack1 =(c_payload->router_fields[count]&(unsigned int)0x0000FFFF);
	  //memcpy(&r1->router_id,&packv2,sizeof(uint16_t)); //1 //9250 
	    r1->router_id= pack1;
	  printf("router id %d\n",ntohs(r1->router_id));
          r4[i].router_id = ntohs(r1->router_id);
		  
	  uint16_t pack2 =(c_payload->router_fields[count]>>16)&mask; 
      r1->router_port= pack2;// correct
	 printf("router port%d\n",ntohs(r1->router_port));
	                   r4[i].router_port = ntohs(r1->router_port);
	 
      uint16_t pack3 = (c_payload->router_fields[count+1]&(unsigned int)0x0000FFFF);
      memcpy(&r1->data_port,&pack3,sizeof(uint16_t));// correct
	 printf("data port%d\n",ntohs(r1->data_port));
	           r4[i].data_port = ntohs(r1->data_port);

	 
      uint16_t pack4 = (c_payload->router_fields[count+1]>>16) &mask;
        memcpy(&r1->cost,&pack4,sizeof(uint16_t));// correct
     printf("cost is  %d\n",ntohs(r1->cost));
	           r4[i].cost = ntohs(r1->cost);


	       uint32_t pack5 = (c_payload->router_fields[count+2]);

      memcpy(&r1->dest_ip_addr,&pack5, sizeof(uint16_t));
	  
           	  
	      router_addr.sin_addr.s_addr = pack5;
           printf("ip addres of router %s\n",inet_ntoa(router_addr.sin_addr));
		   	
		   
                    r4[i].dest_ip_addr= ntohl(r1->dest_ip_addr);		   
		   
	  r1->nexthop =r1->router_id;
	   
     if(r1->cost==0)
     {
		   
            printf("This is the cost to the node itself\n");
				   src_router = malloc(sizeof(struct router_info));
			r4[i].interval = update_interval;
				            r4[i].nexthop = ntohs(r1->nexthop);

	                    printf("update interval %d\n",r1->interval);
		
			router_socket = create_router_sock(r1->router_port);
                            printf("Router socket created\n");
                      FD_SET(router_socket, &master_list);
					//   printf("socket created at time %d",gettimeofday());
					if(router_socket >head_fd)
					  { head_fd = router_socket; }
					  
					  wizard=TRUE;
					  
					data_socket = create_data_sock(r1->data_port);
                              printf("Data socket created\n");

                      FD_SET(data_socket, &master_list);
					  
					if(data_socket >head_fd)
					  { head_fd = data_socket; }
					  		
                   src_router->router_id =ntohs(r1->router_id);
				   src_router->router_port=r1->router_port;
				   src_router->data_port=ntohs(r1->data_port);
					   src_router->cost=ntohs(r1->cost);
				   src_router->dest_ip_addr=r1->dest_ip_addr;
				   src_router->interval=ntohs(r1->interval);
				   src_router->nexthop=ntohs(r1->nexthop);
			   
			
					     //src_router =r1;
					   					  				  
     }
     else if(r1->cost== INF)
     {
		 	            r4[i].nexthop = ntohs(INF);

            printf("This is the cost to the routers which are not reachable\n");
     } 
	 else
	 {
		 	            r4[i].nexthop = ntohs(r1->nexthop);

		 printf("Found a neighbour\n");
		 connectio->position=pos;
		 connectio->neighbour_id = ntohs(r1->router_id);
		 connectio->next_hop_id = ntohs(r1->router_id);
		 connectio->router_port =r1->router_port;
		 connectio->data_port= ntohs(r1->data_port);
		 connectio->cost =ntohs(r1->cost);
		 connectio->ip = pack5;
         connectio->interval=ntohs(r1->interval);
		 neighbour++;
		 //connection->timestamp= c_payload->update_interval;
	     LIST_INSERT_HEAD(&neighbours_list, connectio, next);
		 memcpy(&con_temp[pos],connectio, sizeof(con_temp[pos]));
		 pos++;
		 
     }	      
	
}
struct Neighbours *getNeighbour1( int position)
{
	LIST_FOREACH(connectio, &neighbours_list, next)
		 {
			 if(connectio->position==position)
				  return connectio;
		 }
	
}
struct Neighbours *getNeighbour2( uint16_t port)
{
	LIST_FOREACH(connectio, &neighbours_list, next)
		 {
			 if(ntohs(connectio->router_port)==port)
				  return connectio;
		 }
	
}

void setcosttoInfinity(uint16_t timestamp)
{
       connectio =getNeighbour(timestamp);
	   connectio->cost=INF;
}

struct Neighbours *getNeighbour( uint16_t timestamp)
{
	LIST_FOREACH(connectio, &neighbours_list, next)
		 {
			 if(connectio->timestamp==timestamp)
				  return connectio;
		 }
	
}	
int Neighbourcount()
{
	  int count=0;
	     LIST_FOREACH(connectio, &neighbours_list, next)
		 {
			 count++;
		 }
return count;		 
}	

int getarrivaltime()
{
	     struct timeval t;
gettimeofday(&t, 0);
int64_t millitime = t.tv_sec * INT64_C(1000) + t.tv_usec / 1000;
}

void send_router_updates(int i, int router_socket,struct Neighbours *connectio)
{
	int ticks=0;
	char* str =malloc(50*sizeof(char));
	char* cntrl_payload = (char *) malloc(sizeof(char)*64000);
    struct ROUTING_UPDATE *r_update;
		  r_update= malloc(sizeof(struct ROUTING_UPDATE));	
	struct sockaddr_in router_addr;
	int count_of_neighbours;

	bzero(&router_addr, sizeof(router_addr));
	
	r_update->no_of_update_fields = Neighbourcount();
	r_update->src_router_port = htons(src_router->router_port);
	r_update->src_router_addr = htons(src_router->dest_ip_addr);
	
	for(int x=0;x< Neighbourcount();x++)
	{	
    r_update->router_ip[x]=con_temp[x].ip;
	r_update->router_port[x] = htons(con_temp[x].router_port);
	r_update->router_id[x]= htons(con_temp[x].neighbour_id);
	r_update->cost[x]= htons(con_temp[x].cost);
	r_update->padding[x]=0x00;
	}   
				 // printf("\nIp address to send to: %s\n",connectio->ip);
				  
				   // Send to the address
	               router_addr.sin_family = AF_INET;
				  // snprintf(str, sizeof(str), "%lu", (uint32_t)connectio->ip);	  
				     
				   	  
				   router_addr.sin_addr.s_addr = connectio->ip;
		           printf("ip addres of router %s\n",inet_ntoa(router_addr.sin_addr));
                   socklen_t addrlen = sizeof(router_addr);		
                   router_addr.sin_port= htons(connectio->router_port);	
				   
            cntrl_payload = (char*) r_update;
			
			printf("\n%lu\n",ntohs(connectio->router_port));
			while(ticks!=update_interval) //implement this
			{
				ticks++;
			}
		if(ticks==update_interval)	
		{		
	         printf("Now sending updates");
			if(sendto(router_socket, cntrl_payload, sizeof(cntrl_payload),0,(struct sockaddr*)&router_addr,addrlen) < 0){
             printf("\nFailure\n ");
			free(cntrl_payload);
            }
			else
				printf("update sent to neighbour at%d\n",i);
			} 			
	       // send udp update i.e r_update only after 1 update interval
}	
	
uint16_t receive_routing_updates(int router_socket, int sec)
{
	printf("it comes inside");
		  connectio = malloc(sizeof(struct Neighbours));	
    struct sockaddr_in router_addr;
    socklen_t addrlen = sizeof(router_addr);

	bzero(&router_addr, sizeof(router_addr));

	char* cntrl_payload = (char *) malloc(sizeof(char)*64000);
        bzero(cntrl_payload, sizeof(cntrl_payload));
		
		printf("Received an update from a neighbour");
        if(recvfrom(router_socket, cntrl_payload, sizeof(cntrl_payload),0,(struct sockaddr*)&router_addr,addrlen) < 0){
            free(cntrl_payload);
        } 
       struct ROUTING_UPDATE *r_update = (struct ROUTING_UPDATE*)cntrl_payload;
	     uint16_t port = r_update->src_router_port;
		 connectio= getNeighbour2(port);
		 connectio->timestamp = getarrivaltime()+ (sec)/1000;   // wait until sec to receive next update
		 
				     DoBellmanFord(r_update,no_of_routers);	   
		 
		//store time and implement timer 
		return connectio->timestamp;
}	

int getId( int port)
{
		LIST_FOREACH(connectio, &neighbours_list, next)
        {
            if(ntohs(connectio->router_port)== port)
				return connectio->neighbour_id;
		}
}	

int min(int x,int y)
{
	if(x<y)
		return x;
	else
		return y;
}

int findpos()
{
	int z=0;
	while(c1_payload[z].cost!=htons(src_router->cost))
	{
		z++;
	}
	if(ntohs(c1_payload[z].cost)==src_router->cost)
		 return z;
}	
	
void DoBellmanFord( struct ROUTING_UPDATE *r_update,uint16_t no_of_routers)
{
	// cost 0, cost 7 ,cost 5 ,cost 65535, cost 65535
	int i,j,k,l;
		 int cost_table[ROUTERS][ROUTERS];
		 int id= getId(r_update->src_router_port);
		 
		 int position= findpos();
		 
		 for(l=0;l<no_of_routers;l++)
			 for(k=0;k<no_of_routers;k++)
			 {  
						cost_table[l][k]=INF; 
			 }
		 
		for(l=0;l<no_of_routers;l++) 
		 for(k=0;k<no_of_routers;k++)
		 { 
	         if(l==position)
			      {cost_table[l][k]= ntohs(c1_payload[k].cost); }
		 }
		  
  for(l=0;l<no_of_routers;l++)		 
	for(k=0;k<no_of_routers;k++)
	{
		if(ntohs(c1_payload[l].router_id)== id && cost_table[l][k] > ntohs(r_update->cost[k]) )
		     cost_table[l][k]= ntohs(r_update->cost[k]);
		/*if(c1_payload[i].cost > r_update.cost[i]) 
		         c1_payload[i].cost = r_update.cost[i];*/
	}
	for(l=0;l<no_of_routers;l++)		 
	for(k=0;k<no_of_routers;k++)
	{
		 
		 if(l==k)
			 cost_table[l][k]=0;
		 else 
			 i=k;
			 while(i<no_of_routers)
		   {	 
              cost_table[l][k]= min(cost_table[l][k] ,cost_table[l][i] + cost_table[i][k]);
			 
	           i++;                     
		   }
		
	}	
		for(k=0;k<no_of_routers;k++)
		{
			  	c1_payload[k].cost = cost_table[src_router->router_id][k];
		}
	//call send_router_updates after updating conn_temp
	  for(int j=0; j<=Neighbourcount();j++)
	  {
		  	con_temp[j].cost = cost_table[src_router->router_id][j];
            connectio= getNeighbour1(j);   
			send_router_updates(j,router_socket,connectio);
	  }
}	