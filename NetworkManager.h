#pragma once
#include <string>
#include <iostream>

#ifdef __linux__ 
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
    #include <errno.h>
    #include <sys/ioctl.h>
#elif _WIN32
    #include <WS2tcpip.h>
    #pragma comment (lib, "ws2_32.lib")
#endif


class NetworkManager {
public:
    void initSocket();
    void send(std::string data);
    std::string receive();
    void clean();

private:
    sockaddr_in address;
    #ifdef __linux__ 
        int sock;
    #elif _WIN32
        SOCKET sock;
    #endif
};
