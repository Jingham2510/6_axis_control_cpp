#include "ABB_tcp_client.hpp"
#include<iostream>
#include<chrono>
#include<sstream>


//Creates and connects to the ABB http socket
ABB_tcp_client::ABB_tcp_client(const char *client_ip, int client_port){


    ip = client_ip;
    port = client_port;


    //Initialise the WSA routines
    std::cout << "Starting client..." << "\n";

    if (WSAStartup(MAKEWORD(2,2), &wsa) !=0){
        std::cout << "Startup failed. ERR: " << WSAGetLastError() << "\n";
    }

    std::cout << "Client started" << "\n";

    //Create the socket
    create_sock();

    //Connect to the server
    connect_to_ABB();


}




//Creates a socket in the http client object
void ABB_tcp_client::create_sock(){

    std::cout << "Creating socket" << "\n";
    
    //Attempt to create the socket
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){

        std::cout << "Socket Creation Failed: " << WSAGetLastError();

    }

    else{
        std::cout << "Socket created" << "\n";
    }
}


//Connect toe the ABB http host
void ABB_tcp_client::connect_to_ABB(){

    std::cout << "Connecting to server..." << "\n";

    //Setup the server struct
    ABB_server.sin_addr.s_addr = inet_addr(ip);
    ABB_server.sin_family = AF_INET;    
    ABB_server.sin_port = htons(8888);


    //Attempt to connect to the socket
    if(connect(sock, (struct sockaddr*) &ABB_server, sizeof(ABB_server)) < 0){

        std::cout << "Connection error: " << WSAGetLastError() << "\n";

    }
    else{
        std::cout<< "Connected to: " << ip << "\n";
    }

}

//Closes the connection
void ABB_tcp_client::close_connection(){

    request("CLOS:1");
    closesocket(sock);
    WSACleanup();

}

//Send a request to the server
int ABB_tcp_client::request(std::string request){

    //Convert string to old C type for winsock compatibility
    const char *req = request.data();

    //Attempt to send the request
    if(send(sock, req, strlen(req), 0) < 0){

        std::cout << "ERR: send failed - " << WSAGetLastError() << "\n";
        return -1;
    }


    return 1;
}

//Recieve a response from the server
std::string ABB_tcp_client::recieve(){

    //Buffer to store the server reply
    char buff[2000];
    int recv_err;
    std::string response;

    //Attempt to read a reply from the socket
    if ((recv_err = recv(sock, buff, 2000, 0)) == SOCKET_ERROR){
        std::cout << "Err: socket read - " << WSAGetLastError() << "\n";
        return "SOCKERROR";
    }
    else{
        response = buff;
    }

    //Convert the c-string to a c++ string
    return response;
}

//Connection test
float ABB_tcp_client::ping(){

    //Auto used here because the type is ridiculously long
    //mark the time
    auto start = std::chrono::high_resolution_clock::now();

    //Complete the ping
    request("ECHO:PING");

    //Receive the response
    std::string response = recieve();

    //Mark the finish time
    auto stop = std::chrono::high_resolution_clock::now();

  
    auto exe_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << response << " - Ping complete - Time taken: " << exe_time.count() << "us\n";

    return exe_time.count();

}

//Set the joints to a specific angle
int ABB_tcp_client::set_joints(std::vector<float> jnt_angs){

    //The command to send to the server
    std::string cmd;

    //The string stream to create the command
    std::stringstream stream;

    //Check there are the correct number of joint angles    
    if (jnt_angs.size() != 6){
        std::cout << "ERR: incorrect number of joint angles!";
        return -1;
    }


    //A bit hacky but creates the set joint command with the correct format
    //No need to turn external axes the robot is set
    stream << "STJT:[[" << com_vec_to_string(jnt_angs) << "], [9E9,9E9,9E9,9E9,9E9,9E9]]";

    cmd = stream.str();
    //Send the set joint command to the ABB server
    request(cmd);

    //Print the response from the server
    std::cout << recieve() << "\n";

    
    return 1;
}



//Move the tool relative to its current position
std::string ABB_tcp_client::move_tool(std::vector<float> xyz){

    //The commmand and the command constructor
    std::string cmd;
    std::stringstream cmd_stream;
    std::stringstream ret_stream;
    std::string ret;


    //Check the xyz count is correct
    if(xyz.size() != 3){
        std::cout << "ERR: Incorrect number of coords supplied" << "\n";
    }

    cmd_stream << "MVTL:[" << com_vec_to_string(xyz) << "]";

    cmd = cmd_stream.str();

    request(cmd);



    std::string pos = recieve();

    std::string force = recieve();

  
    //assembled - and formatted
    ret_stream << pos.substr(0, pos.find("]") + 1) << "," << force.substr(0, force.find("]") + 1);

    
    return ret_stream.str();
}

std::string ABB_tcp_client::get_xyz() {

    //Send the getpos command
    request("GTPS:0");

    return recieve();

}

//Takes in a vector of floats then returns it as a string - comma seperated
std::string ABB_tcp_client::com_vec_to_string(std::vector<float> data){

    std::stringstream stream;

    //Goes through the whole array and adds it
    for(size_t i = 0; i <data.size(); i++){
     
        stream << data[i];
        
        if(i != data.size() - 1){
            stream <<  ",";
        }

    }

    return stream.str();


}