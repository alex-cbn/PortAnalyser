//
// Created by cuban on 1/4/18.
//

#ifndef PORTANALYSER_SOCKETWRAPPER_H
#define PORTANALYSER_SOCKETWRAPPER_H


#include <sys/socket.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ExceptionSocket.h"
#include <stdlib.h>


class SocketWrapper {
private:
    struct sockaddr_in end_point_descriptor;
    std::string host_ip_;
    int host_port_;
    int socket_;
public:
    enum SocketTypes{
        UNIX = 1,
        INET = 2,

    };
    SocketWrapper(std::string host_ip, int port_number, bool initialize);
    SocketWrapper(int open_socket, struct sockaddr_in open_socket_descriptor);
    void Bind();
    void Listen();
    std::string Read(SocketWrapper& read_from_socket);
    void Write(SocketWrapper& write_to_socket, std::string write_me);
    void Close();
    void Connect(SocketWrapper connect_to_socket);
    SocketWrapper& Accept();
    int GetSocket();
    SocketWrapper() = default;
};



#endif //PORTANALYSER_SOCKETWRAPPER_H
