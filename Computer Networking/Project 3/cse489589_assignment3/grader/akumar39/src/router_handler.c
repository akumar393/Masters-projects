#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/queue.h>
#include <unistd.h>
#include <string.h>

#include "../include/global.h"
#include "../include/network_util.h"
#include "../include/control_header_lib.h"
#include "../include/author.h"
#include "../include/connection_manager.h"
#include "../include/control_handler.h"
#include "../include/router_handler.h"
#include "../include/data_handler.h"

#define INF 65535
#define TRUE 1
#define FALSE 0

struct Neighbours
{
	int position;
    uint16_t neighbour_id;
	uint16_t router_port;
	uint16_t data_port;
	uint16_t cost;
	uint32_t ip;
	uint16_t interval;
	uint16_t timestamp;
    LIST_ENTRY(Neighbours) next;
	
}*connection1, *conn_temp;
LIST_HEAD(NeighboursHead, Neighbours) neighbours_list;

//void send_router_updates(int i,int router_socket,struct router_info *source_router, struct Neighbours *r1);


uint32_t count=0;
struct router_info *src_router ;
bool wizard=FALSE;
int neighbour=0;
int pos=0;

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
void initrouters(struct CONTROL_PAYLOAD_INIT *c_payload)
{
	int i, bb;
	LIST_INIT(&neighbours_list);
	uint16_t  no_of_neighbours, update_interval;
	no_of_neighbours = ntohs(c_payload->no_of_routers);
	printf("no of neighbours %d",no_of_neighbours);
	update_interval= ntohs(c_payload->update_interval);
	
	for(i=0; i< no_of_neighbours; i++)
	{
		printf("Router %d information is being stored",i);
		printf("count value is:%d\n",count);
	   	registerneighbour(count,c_payload,update_interval);
		count=count+3;
	}
	 
	 b =Neighbourcount();
	 printf("%d",b);
     for(int j=0; i<=Neighbourcount();i++)
	  {
              connection= getNeighbour(j);                  
			send_router_updates(j,router_socket,src_router,connection);
	  }	
}

void registerneighbour(int count, struct CONTROL_PAYLOAD_INIT *c_payload, uint16_t update_interval)
{
	  connection1 = malloc(sizeof(struct Neighbours));
	  //uint64_t mask1 = (1 << 16)-1;
	  //uint64_t mask2 = ((1<<16) -1) << 0;
	  char* str =malloc(50*sizeof(char));
	  bzero(str,sizeof(str));
	  unsigned int mask = ~(~0 << (31 - 16 + 1));     //www.stackoverflow.com
	   //uint32_t mask2 = ((1 << 32) -1);
	   
	   unsigned mask2 =0;
	   for (unsigned i=0; i<32 ;i++)
	   {  mask2 |=1 << i;  }
	   
	   
	  struct router_info *r1=malloc(sizeof(struct router_info));
      struct sockaddr_in router_addr;
      memset(&router_addr,'\0',sizeof(router_addr));
     	  
	 
	   uint16_t pack1 =(c_payload->router_fields[count]&(unsigned int)0x0000FFFF);
	  //memcpy(&r1->router_id,&packv2,sizeof(uint16_t)); //1 //9250 
	    r1->router_id= pack1;
	  printf("router id %d\n",ntohs(r1->router_id));
          
	  uint16_t pack2 =(c_payload->router_fields[count]>>16)&mask; 
      r1->router_port= pack2;// correct
	 printf("router port%d\n",ntohs(r1->router_port));
	 
      uint16_t pack3 = (c_payload->router_fields[count+1]&(unsigned int)0x0000FFFF);
      memcpy(&r1->data_port,&pack3,sizeof(uint16_t));// correct
	 printf("data port%d\n",ntohs(r1->data_port));
	 
      uint16_t pack4 = (c_payload->router_fields[count+1]>>16) &mask;
        memcpy(&r1->cost,&pack4,sizeof(uint16_t));// correct
     printf("cost is  %d\n",ntohs(r1->cost));

	       uint32_t pack5 = (c_payload->router_fields[count+2]);

      memcpy(&r1->dest_ip_addr,&pack5, sizeof(uint32_t));
	  
           snprintf(str, sizeof(str), "%lu", (uint32_t)r1->dest_ip_addr);	  
	      router_addr.sin_addr.s_addr = inet_addr(str);
           printf("ip addres of router %s\n",inet_ntoa(router_addr.sin_addr));

    
     if(r1->cost==0)
     {
            printf("This is the cost to the node itself\n");
			r1->interval = update_interval;
	                    printf("update interval %d\n",r1->interval);
		
			router_socket = create_router_sock(r1->router_port);
                            printf("Router socket created\n");
                      FD_SET(router_socket, &master_list);
					  
					  if(router_socket >head_fd)
						  head_fd = router_socket;
					  
					  wizard=TRUE;
					  
					data_socket = create_data_sock(r1->data_port);
                              printf("Data socket created\n");

                      FD_SET(data_socket, &master_list);
					  
					  if(data_socket >head_fd)
						  head_fd = data_socket;
					  
					  	  
	     			 //main_loop();
					  
					   src_router =r1;
					  
					  
     }
     else if(r1->cost== INF)
     {
            printf("This is the cost to the routers which are not reachable\n");
     } 
	 else
	 {
		 printf("Found a neighbour\n");
		 connection1->position=pos;
		 connection1->neighbour_id = r1->router_id;
		 connection1->router_port =r1->router_port;
		 connection1->data_port= r1->data_port;
		 connection1->cost =r1->cost;
		 connection1->ip = r1->dest_ip_addr;
         connection1->interval=r1->interval;
		 neighbour++;
		 //connection->timestamp= c_payload->update_interval;
	     LIST_INSERT_HEAD(&neighbours_list, connection1, next);
		 pos++;
		 
     }	      
	
}
struct Neighbours *getNeighbour( int position)
{
	LIST_FOREACH(connection1, &neighbours_list, next)
		 {
			 if(connection1->position==position)
				  return connection1;
		 }
	
}	
int Neighbourcount()
{
	  int count=0;
	     LIST_FOREACH(connection, &neighbours_list, next)
		 {
			 count++;
		 }
return count;		 
}	

void send_router_updates(int i, int router_socket, struct router_info *source_router, struct Neighbours *connection)
{
	struct ROUTING_UPDATE * r_update;
	char* cntrl_payload = (char *) malloc(sizeof(char)*64000);
	struct sockaddr_in router_addr;
	int count_of_neighbours;
    socklen_t addrlen = sizeof(router_addr);

	bzero(&router_addr, sizeof(router_addr));
	
	count_of_neighbours = Neighbourcount();
	r_update->no_of_update_fields = count_of_neighbours;
	r_update->src_router_port = ntohs(source_router->router_port);
	r_update->src_router_addr = ntohs(source_router->dest_ip_addr);
	r_update->router_port[i] = ntohs(connection->router_port);
	r_update->router_id[i]= ntohs(connection->neighbour_id);
	r_update->cost[i]= ntohs(connection->cost);
	r_update->padding[i]=0xFFFF;
	    LIST_FOREACH(connection, &neighbours_list, next)
		{
				
            cntrl_payload = (char*) r_update;
			if(sendto(router_socket, cntrl_payload, sizeof(cntrl_payload), 0,(struct sockaddr*)&router_addr.sin_addr.s_addr,sizeof(router_addr)) < 0){
            free(cntrl_payload);
            } 
		}			
	       // send udp update i.e r_update
}	
	
void receive_routing_updates(int router_socket)
{
    struct sockaddr_in router_addr;
    socklen_t addrlen = sizeof(router_addr);

	bzero(&router_addr, sizeof(router_addr));

	char* cntrl_payload = (char *) malloc(sizeof(char)*64000);
        bzero(cntrl_payload, sizeof(cntrl_payload));
        if(recvfrom(router_socket, cntrl_payload, sizeof(cntrl_payload),0, (struct sockaddr*)&router_addr.sin_addr.s_addr,&addrlen) < 0){
            free(cntrl_payload);
        } 
    struct ROUTING_UPDATE * r_update = (struct ROUTING_UPDATE*)cntrl_payload;
		//store time and implement timer 
}	
