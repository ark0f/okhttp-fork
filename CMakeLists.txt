cmake_minimum_required(VERSION 2.8)
project(OkHttpFork)

set(CMAKE_CXX_STANDARD 11)

# Cross-platform files
set(LIB_SOURCE_FILES
        include/ohf/Config.hpp
        lib/Client.cpp include/ohf/Client.hpp
        include/ohf/Call.hpp # Interface
        lib/Response.cpp include/ohf/Response.hpp
        lib/Request.cpp lib/Request.Builder.cpp include/ohf/Request.hpp
        lib/ResponseBody.cpp include/ohf/ResponseBody.hpp
        lib/CacheControl.cpp lib/CacheControl.Builder.cpp include/ohf/CacheControl.hpp
        lib/Challenge.cpp include/ohf/Challenge.hpp
        lib/Handshake.cpp include/ohf/Handshake.hpp
        lib/Headers.cpp lib/Headers.Iterator.cpp lib/Headers.Builder.cpp include/ohf/Headers.hpp
        include/ohf/Protocol.hpp # Enum
        lib/CipherSuite.cpp include/ohf/CipherSuite.hpp
        lib/Certificate.cpp include/ohf/Certificate.hpp
        lib/Principal.cpp include/ohf/Principal.hpp
        lib/Authenticator.cpp include/ohf/Authenticator.hpp
        lib/Cache.cpp include/ohf/Cache.hpp
        lib/CertificatePinner.cpp include/ohf/CertificatePinner.hpp
        lib/ConnectionPool.cpp include/ohf/ConnectionPool.hpp
        lib/ConnectionSpec.cpp include/ohf/ConnectionSpec.hpp
        lib/CookieJar.cpp include/ohf/CookieJar.hpp # Interface
        lib/Dispatcher.cpp include/ohf/Dispatcher.hpp
        lib/DNS.cpp include/ohf/DNS.hpp # Interface
        lib/HostnameVerifier.cpp include/ohf/HostnameVerifier.hpp
        lib/Interceptor.cpp include/ohf/Interceptor.hpp
        lib/Proxy.cpp include/ohf/Proxy.hpp
        lib/ProxySelector.cpp include/ohf/ProxySelector.hpp
        lib/RequestBody.cpp include/ohf/RequestBody.hpp
        lib/HttpURL.cpp lib/HttpURL.Builder.cpp include/ohf/HttpURL.hpp
        lib/MediaType.cpp include/ohf/MediaType.hpp
        lib/Exception.cpp include/ohf/Exception.hpp
        lib/TCPSocket.cpp lib/TCPSocket.Builder.cpp lib/TCPSocket.Server.cpp lib/TCPSocket.Server.Iterator.cpp include/ohf/TCPSocket.hpp
        lib/UDPSocket.cpp include/ohf/UDPSocket.hpp
        lib/Socket.cpp lib/Socket.Builder.cpp include/ohf/Socket.hpp
        lib/SocketStreamBuf.cpp include/ohf/SocketStreamBuf.hpp
        lib/SocketImpl.hpp
        lib/SSLSocket.cpp include/ohf/SSLSocket.hpp
        lib/Cookie.cpp lib/Cookie.Builder.cpp include/ohf/Cookie.hpp
        lib/InetAddress.cpp include/ohf/InetAddress.hpp
        lib/FormBody.cpp lib/FormBody.Builder.cpp include/ohf/FormBody.hpp
        lib/MultipartBody.cpp lib/Multipart.Part.cpp lib/Multipart.Builder.cpp include/ohf/MultipartBody.hpp
        include/ohf/Callback.hpp # Interface
        include/ohf/WebSocket.hpp # Interface
        include/ohf/TLSVersion.hpp # Enum
        lib/TimeUnit.cpp include/ohf/TimeUnit.hpp)

include_directories(include)

# Files for different platforms
if (WIN32)
    set(LIB_SOURCE_FILES ${LIB_SOURCE_FILES}
            lib/Win32/WinUtils.hpp lib/Win32/WinUtils.cpp
            lib/Win32/InetAddress.cpp
            lib/Win32/SocketImpl.hpp lib/Win32/SocketImpl.cpp)
elseif (UNIX)
    set(LIB_SOURCE_FILES ${LIB_SOURCE_FILES}
            lib/UNIX/InetAddress.cpp
            lib/UNIX/SocketImpl.hpp lib/UNIX/SocketImpl.cpp)
endif ()

# Util files
set(LIB_SOURCE_FILES ${LIB_SOURCE_FILES}
        lib/util/string.cpp lib/util/string.hpp
        lib/util/util.cpp lib/util/util.hpp)

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
foreach (file ${LIB_SOURCE_FILES})
    string(REGEX MATCH ^include found ${file})
    if (found)
        install(FILES ${file} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ohf)
    endif ()
endforeach ()
install(TARGETS ohf DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
