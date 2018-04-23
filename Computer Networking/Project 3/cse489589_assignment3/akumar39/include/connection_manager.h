#ifndef CONNECTION_MANAGER_H_
#define CONNECTION_MANAGER_H_

int control_socket, router_socket, data_socket;
int head_fd;
fd_set master_list, watch_list;

void init();
void main_loop();

#endif