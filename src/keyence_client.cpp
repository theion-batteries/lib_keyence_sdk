#include "keyence_client.h"

keyence_client::keyence_client(const char* ip) :IP(ip) {}
enum_hw_feedback keyence_client::connect()
{

    std::cout << "connecting to keyence keyence controller via tcp" << std::endl;
    LKIF_OPENPARAM_ETHERNET paramEther;
    paramEther.IPAddress.S_un.S_addr = inet_addr(IP);
    if (paramEther.IPAddress.S_un.S_addr == INADDR_NONE)
    {
        std::cout << "error IP" << std::endl;
    }
    std::cout << "open connection to " << IP << std::endl;
    RC Conn = LKIF2_OpenDeviceETHER(&paramEther);
    if (Conn == RC_OK)
    {
        std::cout << "keyence connection success" << std::endl;
        return enum_hw_feedback::hw_success;
    }
    else
    {
        std::cout << "keyence connection failed" << std::endl;
        return enum_hw_feedback::hw_error;
    }


}
double keyence_client::get_value_output(int outputNr)
{
    RC Val = LKIF2_GetCalcDataSingle((outputNr), &value);
    if (DataIsValid())
    {
        std::cout << "get valid data from output number: " << outputNr << " Value:" << value.Value << std::endl;
        return value.Value;
    }
    std::cout << "invalid datafrom output number: " << outputNr << " Value:" << value.Value << std::endl;
    return NULL;
}
bool keyence_client::DataIsValid()
{
    if (value.FloatResult == LKIF_FLOATRESULT_VALID) return true;
    return false;

}

void keyence_client::disconnect()
{
    LKIF2_CloseDevice();
}