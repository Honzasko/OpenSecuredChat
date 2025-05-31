
#pragma once
#include <cstdint>
#include <string>
#include <netinet/in.h>

namespace Client {
    class Socket {
        private:
            int client_sock, status;
            struct sockaddr_in address;
            bool initialized = false;
        public:    
            void CreateConnection(std::string ip,std::uint16_t port);
            void Send(std::string message);
            void Close();
        };

}