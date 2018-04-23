#ifndef ROUTER_HANDLER_H_
#define ROUTER_HANDLER_H_
#define ROUTERS 5

struct router_info
{
	    uint16_t router_id;
		uint16_t router_port;
		uint16_t data_port;
		uint16_t cost;
		uint32_t dest_ip_addr;
		uint16_t interval;
		uint16_t nexthop;

} *src_router;

char* table_payload;
uint16_t update_interval;
int create_router_sock(int router_port);
int new_router_conn(int sock_index);
void initrouters(struct CONTROL_PAYLOAD_INIT *c_payload);
void registerneighbour(int i,int count,struct CONTROL_PAYLOAD_INIT *c_payload, uint16_t update_interval);
int Neighbourcount();
uint16_t receive_routing_updates(int sock_index , int sec);
bool isNeighbour(uint32_t ip_addr);
struct Neighbours *getNeighbour1( int position);
struct Neighbours *getNeighbour2( uint16_t port);
struct Neighbours *getNeighbour( uint16_t timestamp);
void maketable(struct router_info r2[ROUTERS] ,uint16_t  no_of_routers);
void DoBellmanFord(struct ROUTING_UPDATE *r_update, uint16_t no_of_routers);
void setcosttoInfinity(uint16_t timestamp);	
int getId( int port);
int min(int x,int y);
int getarrivaltime();
#endif