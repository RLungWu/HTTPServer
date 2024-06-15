#include "http_tcp_server.h"

#include <cstdlib>
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
    
    const int BUFFER_SIZE = 30720;
}


namespace http{
    TcpServer::TcpServer(std::string ip, int port)
        : m_ip_address_(ip), m_port_(port), m_socket_(), 
        m_new_socket_(), m_incoming_message_(), m_socket_address_(), 
        m_socket_address_length_(sizeof(m_socket_address_)), 
        m_server_message_(buildResponse()){
        // Constructor
        
        m_socket_address_.sin_family = AF_INET;
        m_socket_address_.sin_addr.s_addr = inet_addr(m_ip_address_.c_str());
        m_socket_address_.sin_port = htons(m_port_);
        if(startServer() != 0){
            std::ostringstream ss;
            ss << "Failed to start server with port:" << ntohs(m_socket_address_.sin_port);
            log(ss.str());
        }
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

    void TcpServer::acceptConnection(int &new_socket){
        new_socket = accept(m_socket_, (struct sockaddr *)&m_socket_address_, &m_socket_address_length_);
        if(new_socket < 0){
            std::ostringstream ss;
            ss << "Server failed to accept incoming connection from addreess:" << inet_ntoa(m_socket_address_.sin_addr) << ",Port:" << ntohs(m_socket_address_.sin_port);
            exitWithError(ss.str());
        }
    }

    std::string TcpServer::buildResponse(){
        std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";
        std::ostringstream ss;
        ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n"<< htmlFile;

        return ss.str();
    }

    void TcpServer::startListen(){
        if(listen(m_socket_, 20) < 0){
            exitWithError("Socket listen failed");
        }

        std::ostringstream ss;
        ss << "Listening on Address:" << inet_ntoa(m_socket_address_.sin_addr) << "Server is listening on port:" << ntohs(m_socket_address_.sin_port);
        log(ss.str());

        int bytesReceived;

        while(1){
            log("-----Waiting for a new connection-----\n");
            acceptConnection(m_new_socket_);

            char buffer[BUFFER_SIZE] = {0};
            bytesReceived = read(m_new_socket_, buffer, BUFFER_SIZE);
            if(bytesReceived < 0){
                exitWithError("Failed to read bytes from client socket connection");
            }

            std::ostringstream ss;
            ss << "----------Recieved Request from Client----------\n";
            log(ss.str());

            sendResponse();

            close(m_new_socket_);
        }
    }
}