#include "include/client/socket.hpp"
#include <string>
#include <iostream>


int main(){

    Client::Socket *client = new Client::Socket;

    client->CreateConnection("127.0.0.1", 4000);

    while(1){
        std::cout << "Message: ";
        std::string message;
        std::getline(std::cin,message);

        if(message.empty()) continue;
       
        client->Send(message);
        

    }

    client->Close();
    delete client;


    return 0;
}


