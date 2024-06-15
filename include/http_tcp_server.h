#ifndef INCLUDED_HTTP_TCPSERVER
#define INCLUDED_HTTP_TCPSERVER

#include <netinet/in.h>
#include <stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include <string>

namespace http{
    class TcpServer{
        public:
            TcpServer(std::string ip, int port );
            ~TcpServer();
        private:
            std::string m_ip_address_;
            int m_port_;
            int m_socket_;
            int m_new_socket_;
            long m_incoming_message_;

            struct sockaddr_in m_socket_address_;
            unsigned int m_socket_address_length_;
            std::string m_server_message_;

            int startServer();
            void closeServer();
    };
};
#endif 