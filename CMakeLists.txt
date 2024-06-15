include_directories((${CMAKE_CURRENT_SOURCE_DIR}/include))

add_executable(HTTPServer ${CMAKE_SOURCE_DIR}/src/server.cpp)
target_include_directories(HTTPServer PRIVATE ${CMAKE_SOURCE_DIR}/include)