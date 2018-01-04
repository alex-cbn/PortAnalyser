#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include "ExceptionSocket.h"
#include "SocketWrapper.h"

//portanalyser -tcp/-udp/-all HOST

std::vector<std::string> Tokenize(std::string string, char delimiter) {
    std::vector<std::string> result;
    auto found = string.find(delimiter);
    while (found != std::string::npos) {
        found = string.find(delimiter);
        result.push_back(string.substr(0, found));
        string = string.substr(found + 1, string.length());
    }
    return result;
}

std::vector<int> Atoi(const std::vector<std::string> &vector) {
    std::vector<int> result;

    for (const auto &i : vector) {
        result.push_back(atoi(i.c_str()));
    }

    return result;
}

bool IsIp(const std::string &host) {
    int count = static_cast<int>(std::count(host.begin(), host.end(), '.'));
    if (count != 3) {
        return false;
    }
    std::vector<int> vector = Atoi(Tokenize(host, '.'));
    for (const auto &i : vector) {
        if (i > 255) {
            return false;
        }
    }
    return true;
}

bool IsHostname(const std::string &host) {
    return true;
}

int HandleArguments(int argc, char **argv) {  //0 tcp | 1 udp | 2 both
    int mode = -1;
    if (argc != 3) {
        std::cout << "Incorrect argument count supplied" << std::endl;
        return -1;
    }
    if (strcmp(argv[1], "-tcp") == 0) {
        mode = 0;
    }
    if (strcmp(argv[1], "-udp") == 0) {
        mode = 1;
    }
    if (strcmp(argv[1], "-all") == 0) {
        mode = 2;
    }
    if (mode == -1) {
        std::cout << "Invalid selector argument";
        exit(-1);
    }
    return mode;
}

void TestPort(const std::string &host, int port) {
    SocketWrapper socket = SocketWrapper("192.168.56.144", 40002, true);
    socket.Bind();
    try {
        socket.Connect(SocketWrapper(host, port, false));
        std::cout << "Port " << port << " is open" << std::endl;
    }
    catch (...) {
        //std::cout << "Port " << port << " is closed" << std::endl;
    }
    socket.Close();
}

void TcpScanv2(const std::string &host, int begin_port_range, int end_port_range) {
    for (int i = begin_port_range; i <= end_port_range; i++) {
        TestPort(host, i);
    }
}

int main(int argc, char **argv) {
    TcpScanv2("127.0.0.1", 0, 30140);
    int mode = HandleArguments(argc, argv);


    return 0;
}