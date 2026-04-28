#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
//Server
int main(void) {
    // -----------------------------
    // 1. Initialize Winsock (Windows Version of socket use)
    // -----------------------------

    WSADATA wsa;
    char server_message[256] = "CUSTOM_SERVER_V1: Hello from my project!";    /*
    WSADATA = structure that stores info about Winsock

    WSAStartup:
        → Turns ON Windows networking
        → Must be called before using sockets
    */

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }
    // -----------------------------
    //Create the server socket
    // -----------------------------
    SOCKET server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    /*
        socket() creates an endpoint for communication

        AF_INET      → IPv4
        SOCK_STREAM  → TCP (reliable connection)
        0            → default protocol

        Think: "create a phone to receive calls"
    */


    //Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY resolves to any IP

    /*
    INADDR_ANY means:
    → Accept connections from ANY IP on this machine

    htons():
    → converts port to network byte order
*/

    // -----------------------------
    // 4. Bind socket
    // -----------------------------
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)); //Bound to IPM port

    /*
    bind() attaches the socket to:
    → IP address
    → Port

    Think: "assign a phone number to your phone"
*/

    // -----------------------------
    // 5. Listen for connections
    // -----------------------------
    listen(server_socket, 5);
    /*
        listen():
        → puts socket into "waiting for calls" mode

        5 = backlog
        → max number of queued connections
    */

    // -----------------------------
    // 6. Accept client connection
    // -----------------------------
        bool isForever = true;
        int endNum;
        struct sockaddr_in client_address;
        int client_size = sizeof(client_address);

        while (isForever) {
            SOCKET client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_size);

            /* last two parameters are structure and size that contain address of client connection
             similar to socket address similar to binding
             listen for connection--> returns socket to manipulate anything on client's side

            accept():
                → waits for a client to connect

                returns:
                → NEW socket for communication with that client

                IMPORTANT:
                server_socket stays open for new connections
                client_socket is for talking to THIS client

             */
            printf("Client connected from: %s\n", inet_ntoa(client_address.sin_addr));
            // -----------------------------
            // 7. Send data to client
            // -----------------------------
            char buffer[256];
            int bytes = 0;
            while ((bytes = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
                buffer[bytes] = '\0';
                send(client_socket, server_message, strlen(server_message), 0);
            }

            scanf("Please enter 1 to end the Server", &endNum);
            if (endNum == 1) {
                isForever = false;
            }


            /*
            send():
            → sends data over the connection

            strlen() ensures we only send actual message
            */
            closesocket(client_socket);

        }
            // -----------------------------
            // 8. Close sockets + cleanup
            // -----------------------------

            /*
            closesocket → close connection
            WSACleanup  → turn OFF Winsock
        */
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
