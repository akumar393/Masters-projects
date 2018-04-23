#include <sys/socket.h>
#include <netinet/in.h>
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

#define INF ((1<<16)-1)

struct Neighbours
{
    uint16_t neighbour_id;
    LIST_ENTRY(Neighbours) next;
	uint16_t update_interval;
}*connection, *conn_temp;
LIST_HEAD(NeighboursHead, Neighbours) neighbours_list;

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
	no_of_neighbours = c_payload->no_of_routers;
	printf("no of neighbours %d",no_of_neighbours);
	update_interval= c_payload->update_interval;
	
	for(i=0; i< no_of_neighbours; i++)
	{
		printf("Router %d information is being stored",i);
	   	registerneighbour(i,c_payload,update_interval);
	}	
}

void registerneighbour(int n, struct CONTROL_PAYLOAD_INIT *c_payload, uint16_t update_interval)
{
	  connection = malloc(sizeof(struct Neighbours));
      r1=malloc(sizeof(struct router_info));
	  r1->router_id =  c_payload->router_id[n];
      r1->router_port = c_payload->router_port[n];
      r1->data_port = c_payload->data_port[n];
      r1->cost = c_payload->cost[n];  // cost 0 // cost 7 // cost -1 // cost 2 //cost -1
      r1->dest_ip_addr = c_payload->dest_ip_addr[n];

     if(r1->cost==0)
     {
            printf("This is the cost to the node itself\n");
			r1->interval = c_payload->update_interval;
			
			router_socket = create_router_sock(r1->router_port);
                      FD_SET(router_socket, &master_list);
					  
					  if(router_socket >head_fd)
						  head_fd = router_socket;
					  
					data_socket = create_data_sock(r1->data_port);
                      FD_SET(data_socket, &master_list);
					  
					  if(data_socket >head_fd)
						  head_fd = data_socket;
					  
					  main_loop();
					  
     }
     else if(r1->cost== INF)
     {
            printf("This is the cost to the routers which are not reachable\n");
     } 
	 else
	 {
		 printf("Found a neighbour\n");
		 connection->neighbour_id = r1->router_id;
		 connection->update_interval= c_payload->update_interval;
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
