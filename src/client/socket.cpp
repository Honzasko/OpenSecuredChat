#include "../../include/client/socket.hpp"
#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void Client::Socket::CreateConnection(std::string ip, std::uint16_t port){
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(client_sock < 0){
        perror("socket failed:");
        return;
    }
    address.sin_port = htons(port);
    address.sin_family = AF_INET; 

    if((inet_pton(AF_INET,ip.c_str(),&address.sin_addr)) <= 0){
        perror("pton error:");
        return;
    }


    socklen_t client_size = sizeof(address);
    status = connect(client_sock, (struct sockaddr*)&address, client_size);
    if(status < 0) {
        perror("connect failed:");
        return;
    }

    initialized = true;

}

void Client::Socket::Send(std::string message){
    if(!initialized) return;

    const char* msg = message.c_str();
    send(client_sock, msg, message.size(), 0);
    
}

void Client::Socket::Close() {
    if(!initialized) return;

    close(client_sock);
    initialized = false;
}