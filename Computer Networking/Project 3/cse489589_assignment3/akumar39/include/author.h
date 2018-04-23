#ifndef AUTHOR_H_
#define AUTHOR_H_

void author_response(int sock_index);
void init_response(int sock_index, char* cntrl_payload);
void router_response(int sock_index, struct CONTROL_RESPONSE_PAYLOAD_INIT c1_payload[]);

#endif