#include <asm-generic/socket.h>
#include <cstdint>
#include <cstdio>
#include <netinet/in.h>
#include <cstddef>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "../../include/server/socket.hpp"
#include <functional>
#include <unistd.h>



Server::Socket::Socket(std::uint16_t port, bool ipv6){
    int opt = 1;

    if(ipv6) {
        if((server_fd = socket(AF_INET6,SOCK_STREAM,0)) < 0){
            perror("failed socket");
            return;
        }
        address.sin_family = AF_INET6;
    }
    else {
        if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0){
            perror("failed socket");
            return;
        }
        address.sin_family = AF_INET;

    }

    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,&opt, sizeof(opt))){
        perror("set socket reuseaddr");
        return;
    }
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT,&opt, sizeof(opt))) {
        perror("set socket reuseport");
        return;
    }

    
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("bind failed");
        return;
    }

    _initialited = true;


}

Server::Socket::~Socket() {
    close(server_fd);
}

void Server::Socket::Listen(std::function<void(const char*, std::size_t)> callback) {
    if(!_initialited) return;


    _listening = true;

    
    if(listen(server_fd, 10) < 0) {
        perror("listen failed");
        return;
    }

    while(_listening){
        
        struct sockaddr_in client = {0};
        socklen_t cSize = sizeof(client);
        int client_fd = accept(server_fd, (struct sockaddr*)&client, &cSize);

        if(client_fd > 0) {

            while (1) {
                char *buffer = new char[1024];
                int valread = read(client_fd,buffer,1024);
                if(valread > 0) callback(buffer,valread);
                else if (valread == 0) {
                
                    delete[] buffer;
                    break;
                }
                else if (valread == -1) {
                    delete[] buffer;
                    break;
                }

                delete[] buffer;
            }

            
            close(client_fd);

        }
    }
}

bool Server::Socket::IsInitialized(){
    return _initialited;
}

void Server::Socket::Stop(){
    _listening = false;
}