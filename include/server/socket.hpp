#pragma once
#include <cstddef>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdint>
#include <functional>


namespace Server{

class Socket {
    private: 
        int server_fd;
        std::size_t valread;
        struct sockaddr_in address;
        socklen_t addrlen = sizeof(address);
        bool _initialited = false;
        bool _listening = false;

    public:
        Socket(std::uint16_t port, bool ipv6);
        void Listen(std::function<void(const char*, std::size_t)> callback);
        bool IsInitialized();
        ~Socket();
        void Stop();

};
}