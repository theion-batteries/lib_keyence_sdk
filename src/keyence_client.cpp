#include "keyence_client.h"

keyence_client::keyence_client(const char* ip = "192.168.0.104") :IP(ip) {}
void keyence_client::connect()
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
        std::cout << "connection success" << std::endl;

}
double keyence_client::get_value_output(int outputNr)
{
        LKIF_FLOATVALUE_OUT value;
        RC Val = LKIF2_GetCalcDataSingle((outputNr), &value);
        std::cout << "get value outputnr:" << value.OutNo << " Value:" << value.Value << std::endl;
        return value.Value;
}