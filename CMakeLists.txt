cmake_minimum_required(VERSION 2.8)
project(OkHttpFork)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
endif()

set(CMAKE_CXX_STANDARD 11)

option(DTLS "Access to use DTLS" OFF)
if(DTLS)
    add_definitions(-DOKHTTPFORK_DTLS)
endif()

include_directories(include)

file(GLOB_RECURSE INCLUDE RELATIVE ${PROJECT_SOURCE_DIR} "include/*")
file(GLOB_RECURSE LIB RELATIVE ${PROJECT_SOURCE_DIR} "lib/*")

# Files for different systems
if(WIN32)
    file(GLOB FILES RELATIVE ${PROJECT_SOURCE_DIR} "lib/unix/*")
elseif(UNIX)
    file(GLOB FILES RELATIVE ${PROJECT_SOURCE_DIR} "lib/win32/*")
endif()
list(REMOVE_ITEM LIB ${FILES})

add_library(ohf ${INCLUDE} ${LIB})

# Libraries
# OpenSSL
find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    target_link_libraries(ohf ${OPENSSL_LIBRARIES})
endif()

# Socket
if (WIN32)
    target_link_libraries(ohf wsock32)
endif()

# Install
install(DIRECTORY "include/ohf/" DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ohf")
install(TARGETS ohf
        LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")

# Tests
option(TESTS "Unit-tests for ${PROJECT_NAME} using Catch2" ON)
if(TESTS)
    add_subdirectory(tests)
endif()
