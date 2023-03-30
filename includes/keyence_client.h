#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "LKIF2.h"
#include <iostream>
#include "hardware_feedback.h"
#include <map>

class keyence_client
{
private:
    std::string IP = "192.168.0.104";
    RC Conn;
    RC Val;
    double LastValue;
    LKIF_FLOATVALUE_OUT value;

    std::map<RC, std::string> rc_error{
        {RC_OK, "RC_OK"},
        {RC_NAK_COMMAND, "RC_NAK_COMMAND"},                   // Command error
        {RC_NAK_COMMAND_LENGTH, "RC_NAK_COMMAND_LENGTH"},     // Command length error
        {RC_NAK_TIMEOUT, "RC_NAK_TIMEOUT"},                   // Timeout
        {RC_NAK_CHECKSUM, "RC_NAK_CHECKSUM"},                 // Check sum error
        {RC_NAK_INVALID_STATE, "RC_NAK_INVALID_STATE"},       // Status error
        {RC_NAK_OTHER, "RC_NAK_OTHER"},                       // Other error
        {RC_NAK_PARAMETER, "RC_NAK_PARAMETER"},               // Parameter error
        {RC_NAK_OUT_STAGE, "RC_NAK_OUT_STAGE"},               // OUT calculation count limitation error
        {RC_NAK_OUT_HEAD_NUM, "RC_NAK_OUT_HEAD_NUM"},         // No. of used head/OUT over error
        {RC_NAK_OUT_INVALID_CALC, "RC_NAK_OUT_INVALID_CALC"}, // OUT which cannot be used for calculation was specified for calculation.
        {RC_NAK_OUT_VOID, "RC_NAK_OUT_VOID"},                 // OUT which specified for calculation is not found.
        {RC_NAK_INVALID_CYCLE, "RC_NAK_INVALID_CYCLE"},       // Unavailable sampling cycle
        {RC_NAK_CTRL_ERROR, "RC_NAK_CTRL_ERROR"},             // Main unit error
        {RC_NAK_SRAM_ERROR, "RC_NAK_SRAM_ERROR"},             // Setting value error
        ///////////////////////////////////////////////
        // Communication DLL error notification
        //
        {RC_ERR_OPEN_DEVICE, "RC_ERR_OPEN_DEVICE"}, // Opening the device failed.
        {RC_ERR_NO_DEVICE, "RC_ERR_NO_DEVICE"},     // The device is not open.
        {RC_ERR_SEND, "RC_ERR_SEND"},               // Command sending error
        {RC_ERR_RECEIVE, "RC_ERR_RECEIVE"},         // Response receiving error
        {RC_ERR_TIMEOUT, "RC_ERR_TIMEOUT"},         // Timeout
        {RC_ERR_NODATA, "RC_ERR_NODATA"},           // No data
        {RC_ERR_NOMEMORY, "RC_ERR_NOMEMORY"},       // No free memory

        {RC_ERR_DISCONNECT, "RC_ERR_DISCONNECT"}, // Cable disconnection suspected
        {RC_ERR_UNKNOWN, "RC_ERR_UNKNOWN"}        // Undefined error
    };

public:
    keyence_client(std::string ip);
    ~keyence_client();
    wgm_feedbacks::enum_hw_feedback connect();
    double get_value_output(int outputNr);
    bool DataIsValid();
    void disconnect();
    double get_value_all();
};
