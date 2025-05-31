#include "../../include/server/object.hpp"
#include "../../include/server/socket.hpp"
#include <cstddef>
#include <iostream>

Server::Object::Object(Server::Properties properties){
    
    s = new Socket(properties.port,properties.ipv6);
    initiliazed = true;
}

void Server::Object::Start(){

    s->Listen([](const char* data, std::size_t len){
        std::cout << data << std::endl;
    });    
}

bool Server::Object::IsInitialized() {
    return initiliazed;
}

void Server::Object::Stop() {
    s->Stop();
}

Server::Object::~Object() {
    delete s;
}

