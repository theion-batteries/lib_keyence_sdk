#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "LKIF2.h"
#include <iostream>
#include "hardware_feedback.h"

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
    wgm_feedbacks::enum_hw_feedback connect();
    double get_value_output(int outputNr);
    bool DataIsValid();
    void disconnect();

};

