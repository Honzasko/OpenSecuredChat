#include "include/server/object.hpp"
#include <csignal>

Server::Object *s;

extern "C" void sigint(int signum){
    if(s->IsInitialized()) s->Stop();
    delete s;
}

int main(){
    Server::Properties properties;

    properties.port = 4000;
    properties.ipv6 = false;

    s = new Server::Object(properties);

    std::signal(SIGINT,sigint);
    

    s->Start();

    return 0;
}