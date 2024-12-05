
#include "ABB_tcp_client.hpp"



int main(){

    std::vector<float> test_jnts = {100, 0, 0, 0, -30, 0};

    ABB_tcp_client client = ABB_tcp_client("127.0.0.1", 8888);

    client.ping();


    client.set_joints(test_jnts);

    client.close_connection();

    return 0;
}



