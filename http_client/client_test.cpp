
#include "ABB_tcp_client.hpp"



int main(){

    ABB_tcp_client client = ABB_tcp_client("127.0.0.1", 8888);

    client.ping();

    client.close_connection();

    return 0;
}



