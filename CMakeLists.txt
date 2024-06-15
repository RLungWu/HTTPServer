cmake_minimum_required(VERSION 3.10)
project(HTTPServer)

include_directories((${CMAKE_CURRENT_SOURCE_DIR}/include))

add_executable(HTTPServer 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/http_tcp_server.cpp 
)

target_include_directories(HTTPServer PRIVATE ${CMAKE_SOURCE_DIR}/include)