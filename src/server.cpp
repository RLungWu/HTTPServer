#include <http_tcp_server.h>


int main(){

    http::TcpServer server = http::TcpServer("0.0.0.0", 8080);

    return 0;
}