#include "keyence_client.h"

int main()
{
  const char* ip = "192.168.0.104";
   keyence_client Kclient(ip);
   Kclient.connect();
   Kclient.get_value_output(0);
   Kclient.get_value_output(1);
   Kclient.get_value_output(2);

    return 0;
}