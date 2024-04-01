#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
    int socketNum;
    int inetStatus;
    int connectStatus;
    struct sockaddr_in address;


    //server ip address
    // address.sin_addr.s_addr = "127.0.0.1";
    inetStatus = inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
    printf("inetStatus: %d\n", inetStatus);

    address.sin_family = AF_INET;
    address.sin_port = htons(1234);

    socketNum = socket(AF_INET, SOCK_STREAM, 0);

    connectStatus = connect(socketNum, (struct sockaddr *)&address, sizeof(address));
    printf("connectStatus: %d\n", connectStatus);

    char buffer[1024] = {0};
    int recvBytes;
    int readBytes;
    while(1)
    {
        printf("What do you want to send to the server?\n");
        readBytes = read(1, buffer, 1024);
        printf("sending: %s\n", buffer);
        send(socketNum, buffer, readBytes, 0);
        memset(buffer, 0, readBytes);

        recvBytes = recv(socketNum, buffer, 1024, 0);
        printf("recevied from server: %s\n", buffer);
        if(strncmp(buffer, "quit", 4) == 0)
        {
            // int sendSize;
            memset(buffer, 0, 1024);
            printf("Closing connection\n");
            // sendSize = sprintf(buffer, "quit");
            // send(clientSocket, buffer, sendSize, 0);
            break;
        }

        memset(buffer, 0, recvBytes);
    }

    return 0;
}