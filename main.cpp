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
    std::cout << "open connection to " <<strIp << std::endl;
    RC rceth = LKIF2_OpenDeviceETHER(&paramEther);
	int outNo0 = 0;
	LKIF_FLOATVALUE_OUT value;
	RC rc0 = LKIF2_GetCalcDataSingle((outNo0),&value);
    std::cout << "get value outputnr:" <<value.OutNo<<" Res: "<<value.FloatResult <<" Value:"<<value.Value<< std::endl;
	int outNo1 = 1;
	LKIF_FLOATVALUE_OUT value1;
	RC rc1 = LKIF2_GetCalcDataSingle((outNo1),&value1);
    std::cout << "get value  outputnr:" <<value1.OutNo<<" Res: " <<value1.FloatResult <<" Value:"<<value1.Value<< std::endl;
	int outNo2 = 2;
	LKIF_FLOATVALUE_OUT value2;
	RC rc2 = LKIF2_GetCalcDataSingle((outNo2),&value2);
    std::cout << "get value  outputnr:" <<value2.OutNo<<" Res: " <<value2.FloatResult <<" Value:"<<value2.Value<< std::endl;
    return 0;
}