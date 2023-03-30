#include "keyence_client.h"
int main()
{
   std::cout << "test main keyence "
             << "\n";
   const char *ip = "192.168.0.104";
   keyence_client Kclient(ip);
   Kclient.connect();

   {
   std::cout<<Kclient.get_value_output(0)<<"\n";
   }
//   Kclient.get_value_output(0);
//   Kclient.get_value_output(1);
//   Kclient.get_value_output(2);

//   Kclient.get_value_all();
   return 0;
}