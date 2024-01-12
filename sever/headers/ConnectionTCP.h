#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define CL_PORT 7777
#define SV_PORT 7772
#define MESSAGE_LENGTH 1024

namespace TCP_Client {
    extern const char* server_addr;
    extern char buff[MESSAGE_LENGTH];
    extern int socket_file_descriptor, connection;
    extern struct sockaddr_in serveraddress, client;
    
    int processMessage();
} // namespace TCP_Client

namespace TCP_Server {
    extern const char* server_addr;
    extern char buff[MESSAGE_LENGTH];
    extern struct sockaddr_in serveraddress, client;
    extern socklen_t length;
    extern int socket_file_descriptor, connection, bind_status, connection_status;

    int processRequest();
} // namespace TCP_Server
