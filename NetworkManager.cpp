#include "NetworkManager.h"
#include <cstring>

void NetworkManager::initSocket()
{
    #ifdef _WIN32 
        WSAData data;
        if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
            std::cout << "Winsock not started!";
            return;
        }
    #endif

    u_long iMode = 1;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        std::cout << "Could not create socket";
    }
    #ifdef _WIN32
        ioctlsocket(sock, FIONBIO, &iMode);
    #elif __linux__
        ioctl(sock, FIONBIO, &iMode);
    #endif

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons((unsigned short)6702);
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
}

void NetworkManager::send(std::string data) 
{
    unsigned long sent_bytes = sendto(sock, data.c_str(), data.size() + 1, 0, (sockaddr*)&address, sizeof(address));

    if (sent_bytes != data.size() + 1) {
        std::cout << "failed to send packet" << std::endl;
        return;
    }
}

std::string NetworkManager::receive()
{
    char packet_data[1024];
    socklen_t slen = sizeof(address);

    memset(packet_data, 0, sizeof(packet_data));
    int bytes = recvfrom(sock, packet_data, sizeof(packet_data), 0, (struct sockaddr*) &address, &slen);

    if (bytes > 0 && bytes < 1024)
        packet_data[bytes] = '\0';

    return packet_data;
}

void NetworkManager::clean() 
{
    shutdown(sock, 0);
    //closesocket(NetworkManager::sock);
    #ifdef _WIN32 
        WSACleanup();
    #endif
}
