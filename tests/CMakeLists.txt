cmake_minimum_required(VERSION 2.8)
project(ohf_tests)

set(CMAKE_CXX_STANDARD 11)

file(DOWNLOAD
        https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch.hpp)

add_executable(ohf_tests main.cpp catch.hpp
        cache_control.hpp
        cookie.hpp
        headers.hpp
        form_body.hpp
        http_url.hpp
        inet_address.hpp
        media_type.hpp
        multipart_body.hpp
        request.hpp
        request_body.hpp
        time_unit.hpp)
target_link_libraries(ohf_tests ohf)
