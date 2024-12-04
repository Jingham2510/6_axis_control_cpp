#include <winsock2.h>
#include <string>

#ifndef ABB_HTTP_CLIENT 
#define ABB_HTTP_CLIENT



//Relevant winsock library
#pragma comment(lib, "ws2_32.lib")

//Definition of the ABB-http client 
class ABB_http_client{
    public:
        //Creates the http client and auto connects to the socket
        ABB_http_client(const char *, int);

    private:
        //Windows socket data
        WSADATA wsa;
        //ABB server socket
        SOCKET sock;

        //ABB server IP
        const char *ip;
        //ABB server port
        int port;

        //The server struct 
        struct sockaddr_in ABB_server;


        //Creates a socket
        void create_sock();

        //Connects to the ABB client for the given ip
        void connect_to_ABB();


        //Closes the connection
        void close_connection();

    

};

#endif