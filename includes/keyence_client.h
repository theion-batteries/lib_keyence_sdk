#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "LKIF2.h"
#include <iostream>


class keyence_client
{
    private:
    const char* IP;
    RC Conn;
    RC Val;
    double LastValue;
    public:
    keyence_client(const char* ip);
    void connect();
    double get_value_output(int outputNr);

};