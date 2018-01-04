//
// Created by cuban on 1/4/18.
//

#ifndef PORTANALYSER_EXCEPTIONSOCKET_H
#define PORTANALYSER_EXCEPTIONSOCKET_H


#include <string>

class ExceptionSocket {
private:
    std::string exception_message_;
public:
    void Print();
    ExceptionSocket();
    explicit ExceptionSocket(std::string exception_message);
};



#endif //PORTANALYSER_EXCEPTIONSOCKET_H
