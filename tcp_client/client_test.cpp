
#include "ABB_tcp_client.hpp"



int main(){

    

    ABB_tcp_client client = ABB_tcp_client("127.0.0.1", 8888);

    client.ping();

    //std::vector<float> test_jnts = {100, 0, 0, 0, -30, 0};
    //client.set_joints(test_jnts);

    std::vector<float> test_rel = {100, -200, 300};

    client.move_tool(test_rel);

    client.close_connection();

    return 0;
}



