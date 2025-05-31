#pragma once
#include "socket.hpp"
#include <cstdint>

namespace Server {
    typedef struct {
        std::uint16_t port;
        bool ipv6;
        }Properties;
        
        
        class Object {
            private:
                Socket *s;
                bool initiliazed = false;
        
            public:
                Object(Properties properties);
                void Start();
                bool IsInitialized();
                void Stop();
                ~Object();
        
        };

}
