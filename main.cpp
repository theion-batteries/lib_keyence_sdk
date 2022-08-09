#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "LKIF2.h"
#include <iostream>
int main()
{
    
    std::cout << "running test keyence app" << std::endl;
    
    const char* strIp = "192.168.0.104";
    LKIF_OPENPARAM_ETHERNET paramEther;
    paramEther.IPAddress.S_un.S_addr = inet_addr(strIp);

    if (paramEther.IPAddress.S_un.S_addr == INADDR_NONE)
    {
        std::cout << "error adress" << std::endl;
    }
    RC rc = LKIF2_OpenDeviceETHER(&paramEther);
    
    return 0;
}