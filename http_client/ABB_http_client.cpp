#include "ABB_http_client.hpp"
#include<iostream>

//Creates and connects to the ABB http socket
ABB_http_client::ABB_http_client(const char *client_ip, int client_port){


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
void ABB_http_client::create_sock(){

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
void ABB_http_client::connect_to_ABB(){

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
void ABB_http_client::close_connection(){

    closesocket(sock);
    WSACleanup();

}