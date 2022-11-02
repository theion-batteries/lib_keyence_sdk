#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "LKIF2.h"
#include <iostream>

enum class enum_hw_feedback
{
    hw_success = 4,
    hw_error = -3
};

class keyence_client
{
private:
    const char* IP;
    RC Conn;
    RC Val;
    double LastValue;
    LKIF_FLOATVALUE_OUT value;
public:
    keyence_client(const char* ip = "192.168.0.104");
    enum_hw_feedback connect();
    double get_value_output(int outputNr);
    bool DataIsValid();
    void disconnect();

};

