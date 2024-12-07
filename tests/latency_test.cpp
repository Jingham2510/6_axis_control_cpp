/*
Ping latency test for ABB client
Pings the ABB server 100 times
Saves the time taken for a response in a text file


*/

#include"../tcp_client/ABB_tcp_client.hpp"
#include <fstream>
#include<iostream>


int main(){

    ABB_tcp_client client = ABB_tcp_client("192.168.125.1", 8888);

    std::vector<float> times;

    //ping 100 times
    for(int i = 0; i < 100; i++){
        times.push_back(client.ping());
    } 

    //Save all the data to a text file 
    std::ofstream data_file("C:/Users/User/Documents/Results/robot_latency_tests/raw/latency_cpp.txt");
    for(int i = 0; i < times.size(); i++){
        data_file << times[i] << "\n";
    }
    
    data_file.close();

    return 0;
}