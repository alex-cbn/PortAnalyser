//
// Created by cuban on 1/4/18.
//

#include "SocketWrapper.h"
#include <tuple>
#include <cstring>


SocketWrapper::SocketWrapper(const std::string host_ip, int port_number, bool initialize) {
    host_ip_ = host_ip;
    host_port_ = port_number;
    end_point_descriptor.sin_family = AF_INET;
    end_point_descriptor.sin_port = htons((uint16_t) port_number);
    inet_aton(host_ip_.c_str(), &end_point_descriptor.sin_addr);
    socket_ = 0;
    if (!initialize)
        return;
    try {
        socket_ = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_ < 0) {
            Close();
            throw (ExceptionSocket("Socket could not be created"));
        }
    }
    catch (ExceptionSocket &exception_socket) {
        exception_socket.Print();
        exit(-1);
    }
}

void SocketWrapper::Bind() {
    int enable = 1;
    try {
        if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
            throw (ExceptionSocket("Sa nu mergi"));
        }
        if (bind(socket_, (struct sockaddr *) &end_point_descriptor, sizeof(end_point_descriptor)) < 0) {
            Close();
            throw (ExceptionSocket("Socket could not be bound"));
        }
    }
    catch (ExceptionSocket &exception_socket) {
        exception_socket.Print();
        exit(-1);
    }
}

void SocketWrapper::Connect(SocketWrapper connect_to_socket) {
    try {
        if (connect(socket_, (struct sockaddr *) &connect_to_socket.end_point_descriptor,
                    (socklen_t) sizeof(connect_to_socket.end_point_descriptor)) < 0) {
            throw (ExceptionSocket("Can't connect to Endpoint"));

        }
    }
    catch (ExceptionSocket &exception_socket) {
        //exception_socket.Print();
        throw ExceptionSocket("namai ba");
    }
}

void SocketWrapper::Listen() {
    listen(socket_, 5);
}

std::string SocketWrapper::Read(SocketWrapper &read_from_socket) {
    char buffer[50];
    read(read_from_socket.GetSocket(), buffer, 50);
    return std::string(buffer);
}

void SocketWrapper::Write(SocketWrapper &write_to_socket, std::string write_me) {
    char buffer[50];
    strcpy(buffer, write_me.c_str());
    write(this->GetSocket(), buffer, strlen(buffer));
}

void SocketWrapper::Close() {
    close(socket_);
}

SocketWrapper &SocketWrapper::Accept() {
    struct sockaddr_in socket_address;
    int reply_socket;
    try {
        if ((reply_socket = accept(socket_, (sockaddr *) &socket_address, (socklen_t *) (sizeof(sockaddr)))) == -1) {
            Close();
            throw (ExceptionSocket("Socket can't accept"));
        }
    }
    catch (ExceptionSocket &exception_socket) {
        exception_socket.Print();
        exit(-1);
        return *(new SocketWrapper());
    }
    return *(new SocketWrapper(reply_socket, socket_address));
}

int SocketWrapper::GetSocket() {
    return socket_;
}

SocketWrapper::SocketWrapper(int open_socket, struct sockaddr_in open_socket_descriptor) {
    socket_ = open_socket;
    end_point_descriptor = open_socket_descriptor;
    host_ip_ = inet_ntoa(open_socket_descriptor.sin_addr);
    host_port_ = ntohs(open_socket_descriptor.sin_port);
}

