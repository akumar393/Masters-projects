#ifndef CONTROL_HANDLER_LIB_H_
#define CONTROL_HANDLER_LIB_H_

#define CNTRL_HEADER_SIZE 8
#define CNTRL_RESP_HEADER_SIZE 8

#define PACKET_USING_STRUCT // Comment this out to use alternate packet crafting technique

#ifdef PACKET_USING_STRUCT
    struct __attribute__((__packed__)) CONTROL_HEADER
    {
        uint32_t dest_ip_addr;
        uint8_t control_code;
        uint8_t response_time;
        uint16_t payload_len;
    };

    struct __attribute__((__packed__)) CONTROL_RESPONSE_HEADER
    {
        uint32_t controller_ip_addr;
        uint8_t control_code;
        uint8_t response_code;
        uint16_t payload_len;
    };
	
	struct __attribute__((__packed__)) CONTROL_PAYLOAD_INIT
    {
		uint16_t no_of_routers;
		uint16_t update_interval;
		uint32_t router_fields[100];
		//uint16_t router_port[10];
		//uint16_t data_port[10];
		//uint16_t cost[10];
		//uint32_t dest_ip_addr[10];
        
    };
	
	struct __attribute__((__packed__)) ROUTING_UPDATE
    {
		uint16_t no_of_update_fields;
		uint16_t src_router_port;
		uint32_t src_router_addr;
		uint32_t router_ip[10];
		uint16_t padding[10];
		uint16_t router_id[10];
		uint16_t cost[10];
		uint32_t dest_ip_addr[10];
        
    }ROUTING_UPDATE;
#endif

char* create_response_header(int sock_index, uint8_t control_code, uint8_t response_code, uint16_t payload_len);

#endif
