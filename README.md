# HTTPServer
## Introduction
My server will use a TCP/IP socket registered to an IP address on the computer. It will also have a specific port through the socket. The socket will listen for incoming network connections. 
Network connections that come into our server will be stored on a Queue of network threads. When the Queue is full, incoming network requests will start to fall through. 
The server will process each network thread synchronously. The network connection will be used to create a temporary socket through which the server reads data from the client and sends data to the client.


