#include "http_tcp_server.h"

#include<iostream>
#include<sstream>
#include<unistd.h>

namespace{
    void log(const std::string &message){
        std::cout << message << std::endl;
    }

    void exitWithError(const std::string &error){
        log("Error: " + error);
        exit(1);
    }
}


namespace http{
    TcpServer::TcpServer(std::string ip, int port)
        : m_ip_address_(ip), m_port_(port), m_socket_(), 
        m_new_socket_(), m_incoming_message_(), m_socket_address_(), 
        m_socket_address_length_(sizeof(m_socket_address_)), 
        m_server_message_(buildResponse()){
        // Constructor
        startServer();
    }

    TcpServer::~TcpServer(){
        // Destructor
        closeServer();
    }

    int TcpServer::startServer(){
        m_socket_ = socket(AF_INET, SOCK_STREAM,0);
        if(m_socket_ < 0){
            exitWithError("Socket creation failed");
            return 1;
        }
        return 0;
    }

    void TcpServer::closeServer(){
        close(m_socket_);
        close(m_new_socket_);
        exit(0);
    }
}