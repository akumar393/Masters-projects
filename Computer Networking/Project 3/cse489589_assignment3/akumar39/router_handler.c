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
	uint16_t next_hop_id;
	uint16_t router_port;
	uint16_t data_port;
	uint16_t cost;
	uint32_t ip;
	uint16_t interval;
    LIST_ENTRY(Neighbours) next;
	uint16_t timestamp;
}*connection, *conn_temp;
LIST_HEAD(NeighboursHead, Neighbours) neighbours_list;

//void send_router_updates(int i,int router_socket,struct router_info *source_router, struct Neighbours *connection);


uint32_t count=0;
int pos=0;
struct router_info *src_router;
bool wizard=FALSE;
int neighbour=0;
struct router_info r3[5] = {{0,0,0,0,0,0,0}};



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
char *maketable(struct router_info r2[5] ,uint16_t  no_of_routers)
{
	printf("Making a table");
	struct CONTROL_RESPONSE_PAYLOAD_INIT* c_payload = malloc(sizeof(struct CONTROL_RESPONSE_PAYLOAD_INIT));
	
	for(int r=0; r< no_of_routers; r++)
	{	
            c_payload->router_id[r] = htons(r2[r].router_id);
            c_payload->padding[r] = 0x00;
			c_payload->next_hop_id[r] = htons(r2[r].nexthop);
			c_payload->cost[r] = htons(r2[r].cost);
    }
	char *cntrl_payload = (char*)c_payload;
	
	return cntrl_payload;
}

void initrouters(struct CONTROL_PAYLOAD_INIT *c_payload)
{
	int i,b;
	LIST_INIT(&neighbours_list);
	uint16_t  no_of_routers;
		char* table_payload =malloc(sizeof(char));
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
	
     table_payload= maketable(r3, no_of_routers);	 
    /*b =Neighbourcount();
	 printf("B value is\n%d",b);
     for(int j=0; i<=Neighbourcount();i++)
	  {
            connection= getNeighbour(j);                  
			send_router_updates(j,router_socket,src_router,connection);
	  }	
	  main_loop();*/
}

void registerneighbour(int i,int count, struct CONTROL_PAYLOAD_INIT *c_payload, uint16_t update_interval)
{
	  connection = malloc(sizeof(struct Neighbours));
	  //uint64_t mask1 = (1 << 16)-1;
	  //uint64_t mask2 = ((1<<16) -1) << 0;
	  char* str =malloc(50*sizeof(char));
	  bzero(str,sizeof(str));
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
          r3[i].router_id = ntohs(r1->router_id);
		  
	  uint16_t pack2 =(c_payload->router_fields[count]>>16)&mask; 
      r1->router_port= pack2;// correct
	 printf("router port%d\n",ntohs(r1->router_port));
	                   r3[i].router_port = ntohs(r1->router_port);
	 
      uint16_t pack3 = (c_payload->router_fields[count+1]&(unsigned int)0x0000FFFF);
      memcpy(&r1->data_port,&pack3,sizeof(uint16_t));// correct
	 printf("data port%d\n",ntohs(r1->data_port));
	           r3[i].data_port = ntohs(r1->data_port);

	 
      uint16_t pack4 = (c_payload->router_fields[count+1]>>16) &mask;
        memcpy(&r1->cost,&pack4,sizeof(uint16_t));// correct
     printf("cost is  %d\n",ntohs(r1->cost));
	           r3[i].cost = ntohs(r1->cost);


	       uint32_t pack5 = (c_payload->router_fields[count+2]);

      memcpy(&r1->dest_ip_addr,&pack5, sizeof(uint32_t));
	  
           snprintf(str, sizeof(str), "%lu", (uint32_t)r1->dest_ip_addr);	  
	      router_addr.sin_addr.s_addr = inet_addr(str);
           printf("ip addres of router %s\n",inet_ntoa(router_addr.sin_addr));
                    r3[i].dest_ip_addr= ntohl(r1->dest_ip_addr);		   
		   
	  r1->nexthop =r1->router_id;
	            r3[i].nexthop = ntohs(r1->nexthop);

	   
     if(r1->cost==0)
     {
            printf("This is the cost to the node itself\n");
			r3[i].interval = update_interval;
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
					  		
              //  bzero(src_router,sizeof(struct router_info*));
							
				//	   src_router =r1;
					   					  				  
     }
     else if(r1->cost== INF)
     {
            printf("This is the cost to the routers which are not reachable\n");
     } 
	 else
	 {
		 printf("Found a neighbour\n");
		 connection->position=pos;
		 connection->neighbour_id = r1->router_id;
		 connection->next_hop_id = r1->router_id;
		 connection->router_port =r1->router_port;
		 connection->data_port= r1->data_port;
		 connection->cost =r1->cost;
		 connection->ip = r1->dest_ip_addr;
         connection->interval=r1->interval;
		 neighbour++;
		 //connection->timestamp= c_payload->update_interval;
	     LIST_INSERT_HEAD(&neighbours_list, connection, next);
		 pos++;
		 
     }	      
	
}
struct Neighbours *getNeighbour( int position)
{
	LIST_FOREACH(connection, &neighbours_list, next)
		 {
			 if(connection->position==position)
				  return connection;
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
	char* str =malloc(50*sizeof(char));
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
	r_update->padding[i]=0x00;
	    
		           snprintf(str, sizeof(str), "%lu", (uint32_t)connection->ip);	  
                   router_addr.sin_addr.s_addr =inet_addr(str);				
            cntrl_payload = (char*) r_update;
			if(sendto(router_socket, cntrl_payload, sizeof(cntrl_payload), 0,(struct sockaddr*)&router_addr.sin_addr.s_addr,addrlen) < 0){
            free(cntrl_payload);
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
