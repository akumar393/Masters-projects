#ifndef DATA_HANDLER_H_
#define DATA_HANDLER_H_

int create_data_sock(int data_port);
int new_data_conn(int sock_index);
bool isData(int sock_index);
//bool control_recv_hook(int sock_index);

#endif