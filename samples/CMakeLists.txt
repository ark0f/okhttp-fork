cmake_minimum_required(VERSION 2.8)
project(ohf_samples)

set(CMAKE_CXX_STANDARD 11)

add_executable(cookie cookie.cpp)
target_link_libraries(cookie ohf)

add_executable(headers headers.cpp)
target_link_libraries(headers ohf)

add_executable(http_url http_url.cpp)
target_link_libraries(http_url ohf)

add_executable(inet_address inet_address.cpp)
target_link_libraries(inet_address ohf)

add_executable(media_type media_type.cpp)
target_link_libraries(media_type ohf)

add_executable(request_body request_body.cpp)
target_link_libraries(request_body ohf)

add_executable(response_body response_body.cpp)
target_link_libraries(response_body ohf)

add_executable(ssl_socket ssl_socket.cpp)
target_link_libraries(ssl_socket ohf)

add_executable(tcp_socket socket.cpp)
target_link_libraries(tcp_socket ohf)

add_executable(udp_socket udp_socket.cpp)
target_link_libraries(udp_socket ohf)
