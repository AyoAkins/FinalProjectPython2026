#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
// This program is a CLIENT
// It will only work if a SERVER is already running on 127.0.0.1:9002
int main(void) {
    // -----------------------------
    // 1. Initialize Winsock (Windows Version of socket use)
    // -----------------------------
    WSADATA wsa;
    // WSADATA = structure that stores info about Winsock

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // -----------------------------
    //Creating socket
    // -----------------------------
    SOCKET netSocket;
    // SOCKET = Windows version of a socket descriptor (like int on Linux)
    /*
            socket() creates an endpoint for communication

            AF_INET      → Use IPv4
            SOCK_STREAM  → Use TCP (reliable connection)
            0            → Default protocol for TCP

            Think of this like: "create a phone"
        */

    //Connect is needed to connect the socket another socket
    // -----------------------------
    // 3. Define server address
    // -----------------------------
    struct sockaddr_in server_address;
    /*
        sockaddr_in = structure that stores:
        - IP address
        - Port number
        - Address family
    */

    server_address.sin_family = AF_INET; //fields to define
    // Must match the socket type (IPv4)

    server_address.sin_port = htons(9002); //conversion function(port num)
    /*
            htons = "host to network short"
            Converts the port number into network byte order

            Always use this for ports
        */

    //Server address we are connecting
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    /*
    inet_addr converts a string IP into binary form
    127.0.0.1 = localhost (your own computer)

    So this means:
    "connect to a server running on my machine"

    */

    // -----------------------------
    // 4. Connect to server
    // -----------------------------
    //Henry
    int start_port, end_port;

    printf("Enter starting port (e.g. 8000 9000): \n");
    scanf("%d", &start_port);
    printf("Enter ending port (e.g. 8000 9000): \n");
    scanf("%d", &end_port);
    if (start_port < 1 || end_port > 65535 || start_port > end_port) {
        printf("Invalid port range.\n");
        return 1;
    }
    for (int port = start_port; port <= end_port; port++) {
        netSocket = socket(AF_INET, SOCK_STREAM, 0); //Creates new socket every loop
        int timeout = 1000;
        setsockopt(netSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
        server_address.sin_port = htons(port); //sends the current port into connect
        int connection_status = connect(netSocket, (struct sockaddr*)&server_address, sizeof(server_address));
        /*
       connect() tries to establish a connection to the server
       returns int

       If successful:
           → A TCP connection is established

       If it fails:
           → No server is listening on that IP/port

       Think of this like: "dialing a phone number"
   */
            //EDIT
        if (connection_status == 0) { //IF PORT IS OPEN
            char server_response[256] = {0}; //Response
            char request[] = "GET / HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n"; //Request

            send(netSocket, request, strlen(request), 0); //Send a request
            const int bytes_received = recv(netSocket, server_response, sizeof(server_response), 0);
            if (bytes_received > 0) {

                server_response[bytes_received] = '\0'; //adds null operator

                if (strstr(server_response, "HTTP/") != NULL) {
                    printf("[OPEN] %d -> HTTP Server\n", port);
                    printf("The server sent the data: %s\n", server_response);

                }
                else if (strstr(server_response, "CUSTOM_SERVER_V1") != NULL) {
                    printf("[OPEN] %d -> My Custom Server\n", port);
}
                else {
                    printf("[OPEN] %d -> Unknown Service\n", port);
                    printf("The server sent the data: %s\n", server_response);
}

                //print out the server response


            }
        }
        else {
            printf("[CLOSED] %d\n", port);
        }
        closesocket(netSocket);
    }
    WSACleanup();

    return 0;

/*
    *WSAStartup → turn networking ON

    socket()   → create a communication endpoint (phone)

    sockaddr   → define who you want to talk to (IP + port)

    connect()  → attempt to connect (dial number)

    closesocket → hang up

    WSACleanup → turn networking OFF

    */
}