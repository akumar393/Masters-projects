#ifndef ROUTER_HANDLER_H_
#define ROUTER_HANDLER_H_

int create_router_sock(int router_port);
int new_router_conn(int sock_index);
bool isRouter(int sock_index);
void initrouters(struct CONTROL_PAYLOAD_INIT *c_payload);
void registerneighbour(int n,struct CONTROL_PAYLOAD_INIT *c_payload, uint16_t update_interval);


struct router_info
{
	    uint16_t router_id;
		uint16_t router_port;
		uint16_t data_port;
		uint16_t cost;
		uint32_t dest_ip_addr;
		uint16_t interval;

}*r1 ;
	
//bool control_recv_hook(int sock_index);

#endif