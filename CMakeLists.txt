cmake_minimum_required(VERSION 2.8)
project(OkHttpFork)

set(CMAKE_CXX_STANDARD 11)

# Cross-platform files
set(LIB_SOURCE_FILES
        lib/Client.cpp include/Client.hpp
        include/Call.hpp # Interface
        lib/Response.cpp include/Response.hpp
        lib/Request.cpp include/Request.hpp
        lib/ResponseBody.cpp include/ResponseBody.hpp
        lib/CacheControl.cpp lib/CacheControl.Builder.cpp include/CacheControl.hpp
        lib/Challenge.cpp include/Challenge.hpp
        lib/Handshake.cpp include/Handshake.hpp
        lib/Headers.cpp lib/Headers.Builder.cpp include/Headers.hpp
        lib/Protocol.cpp include/Protocol.hpp
        lib/CipherSuite.cpp include/CipherSuite.hpp
        lib/Certificate.cpp include/Certificate.hpp
        lib/Principal.cpp include/Principal.hpp
        lib/Authenticator.cpp include/Authenticator.hpp
        lib/Cache.cpp include/Cache.hpp
        lib/CertificatePinner.cpp include/CertificatePinner.hpp
        lib/ConnectionPool.cpp include/ConnectionPool.hpp
        lib/ConnectionSpec.cpp include/ConnectionSpec.hpp
        lib/CookieJar.cpp include/CookieJar.hpp # Interface
        lib/Dispatcher.cpp include/Dispatcher.hpp
        lib/DNS.cpp include/DNS.hpp # Interface
        lib/HostnameVerifier.cpp include/HostnameVerifier.hpp
        lib/Interceptor.cpp include/Interceptor.hpp
        lib/Proxy.cpp include/Proxy.hpp
        lib/ProxySelector.cpp include/ProxySelector.hpp
        lib/RequestBody.cpp include/RequestBody.hpp
        lib/HttpURL.cpp lib/HttpURL.Builder.cpp include/HttpURL.hpp
        lib/MediaType.cpp include/MediaType.hpp
        lib/Exception.cpp include/Exception.hpp
        lib/Socket.cpp lib/SocketStreamBuf.cpp include/Socket.hpp
        lib/SSLSocket.cpp include/SSLSocket.hpp
        lib/Cookie.cpp lib/Cookie.Builder.cpp include/Cookie.hpp
        lib/InetAddress.cpp include/InetAddress.hpp
        lib/FormBody.cpp lib/FormBody.Builder.cpp include/FormBody.hpp
        lib/MultipartBody.cpp lib/Multipart.Part.cpp lib/Multipart.Builder.cpp include/MultipartBody.hpp
        include/Callback.hpp # Interface
        include/WebSocket.hpp) # Interface

# Files for different platforms
if (WIN32)
    set(LIB_SOURCE_FILES ${LIB_SOURCE_FILES}
            lib/Win32/Socket.cpp
            lib/Win32/WSAInit.hpp
            lib/Win32/InetAddress.cpp)
elseif (UNIX)
    set(LIB_SOURCE_FILES ${LIB_SOURCE_FILES}
            lib/UNIX/Socket.cpp
            lib/UNIX/InetAddress.cpp)
endif ()

# Util files
set(LIB_SOURCE_FILES ${LIB_SOURCE_FILES}
        util/string.cpp util/string.hpp
        util/util.cpp util/util.hpp)

option(BUILD_SHARED OFF)
if (BUILD_SHARED)
    add_library(ohf SHARED ${LIB_SOURCE_FILES})
else ()
    add_library(ohf STATIC ${LIB_SOURCE_FILES})
endif ()

# Libraries
# OpenSSL
find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    target_link_libraries(ohf ${OPENSSL_LIBRARIES})
endif ()

# Socket
if (WIN32)
    target_link_libraries(ohf wsock32)
endif ()

# Install
if (WIN32)
    set(INCLUDE_INSTALL_PATH ${CMAKE_CURRENT_BINARY_DIR}/ohf/include/ohf)
    set(LIB_INSTALL_PATH ${CMAKE_CURRENT_BINARY_DIR}/ohf/lib)
elseif (UNIX)
    set(INCLUDE_INSTALL_PATH /usr/include/ohf)
    set(LIB_INSTALL_PATH /usr/lib)
endif ()

foreach (file ${LIB_SOURCE_FILES})
    string(REGEX MATCH ^include found ${file})
    if (found)
        install(FILES ${file} DESTINATION ${INCLUDE_INSTALL_PATH})
    endif ()
endforeach ()
install(TARGETS ohf DESTINATION ${LIB_INSTALL_PATH})