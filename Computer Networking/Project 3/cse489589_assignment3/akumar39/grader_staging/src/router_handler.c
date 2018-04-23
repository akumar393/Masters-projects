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

struct Neighbours
{
    uint16_t neighbour_id;
    LIST_ENTRY(Neighbours) next;
	uint16_t update_interval;
}*connection, *conn_temp;
LIST_HEAD(NeighboursHead, Neighbours) neighbours_list;

uint32_t count=0;
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
	int i;
	LIST_INIT(&neighbours_list);
	uint16_t  no_of_neighbours, update_interval;
	no_of_neighbours = ntohs(c_payload->no_of_routers);
	printf("no of neighbours %d",no_of_neighbours);
	update_interval= ntohs(c_payload->update_interval);
	
	for(i=0; i< no_of_neighbours; i++)
	{
		printf("Router %d information is being stored",i);
		printf("count value is:%d]\n",count);
	   	registerneighbour(count,c_payload,update_interval);
		count=count+3;
	}	
}

void registerneighbour(int x, struct CONTROL_PAYLOAD_INIT *c_payload, uint16_t update_interval)
{
	  connection = malloc(sizeof(struct Neighbours));
	  //uint64_t mask1 = (1 << 16)-1;
	  //uint64_t mask2 = ((1<<16) -1) << 0;
	  char* str =(char*)malloc(sizeof(char)*256);
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

	       uint32_t pack5 = mask2&(c_payload->router_fields[count+2]&(unsigned int)0x0000FFFF);
                                                                  
      //memcpy(&r1->dest_ip_addr,&pack5, sizeof(uint32_t));
	       r1->dest_ip_addr= pack5;
           snprintf(str, sizeof(str), "%lu",(uint32_t) r1->dest_ip_addr);	  
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
					  
					data_socket = create_data_sock(r1->data_port);
                              printf("Data socket created\n");

                      FD_SET(data_socket, &master_list);
					  
					  if(data_socket >head_fd)
						  head_fd = data_socket;
					  
	     			//  main_loop();
					  
     }
     else if(r1->cost== INF)
     {
            printf("This is the cost to the routers which are not reachable\n");
     } 
	 else
	 {
		 printf("Found a neighbour\n");
		 connection->neighbour_id = r1->router_id;
		 //connection->update_interval= c_payload->update_interval;
	     LIST_INSERT_HEAD(&neighbours_list, connection, next);
     }	      
	
}	
/*void receiveupdates(int router_socket)
{
    struct sockaddr_in router_addr;
    socklen_t addrlen = sizeof(router_addr);

	bzero(&router_addr, sizeof(router_addr));

	if time within timer interval
	     rcvfrom(router_socket, msg)
		 
}*/	
