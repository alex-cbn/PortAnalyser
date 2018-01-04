//
// Created by cuban on 1/4/18.
//

#include <iostream>
#include "ExceptionSocket.h"

ExceptionSocket::ExceptionSocket(std::string exception_message) {
    exception_message_ = exception_message;
}

void ExceptionSocket::Print() {
    std::cerr << exception_message_;
}

ExceptionSocket::ExceptionSocket() {
    exception_message_ = "Generic Socket Exception";
}