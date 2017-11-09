cmake_minimum_required(VERSION 2.8)
project(OkHttpFork)

set(CMAKE_CXX_STANDARD 11)

# Cross-platform files
set(LIB_SOURCE_FILES
        include/Config.hpp
        lib/Client.cpp include/Client.hpp
        include/Call.hpp # Interface
        lib/Response.cpp include/Response.hpp
        lib/Request.cpp lib/Request.Builder.cpp include/Request.hpp
        lib/ResponseBody.cpp include/ResponseBody.hpp
        lib/CacheControl.cpp lib/CacheControl.Builder.cpp include/CacheControl.hpp
        lib/Challenge.cpp include/Challenge.hpp
        lib/Handshake.cpp include/Handshake.hpp
        lib/Headers.cpp lib/Headers.Builder.cpp include/Headers.hpp
        include/Protocol.hpp # Enum
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
        lib/TCPSocket.cpp lib/TCPSocket.Builder.cpp include/TCPSocket.hpp
        lib/UDPSocket.cpp include/UDPSocket.hpp
        lib/Socket.cpp lib/Socket.Builder.cpp include/Socket.hpp
        lib/SocketStreamBuf.cpp include/SocketStreamBuf.hpp
        lib/SocketImpl.hpp
        lib/SSLSocket.cpp include/SSLSocket.hpp
        lib/Cookie.cpp lib/Cookie.Builder.cpp include/Cookie.hpp
        lib/InetAddress.cpp include/InetAddress.hpp
        lib/FormBody.cpp lib/FormBody.Builder.cpp include/FormBody.hpp
        lib/MultipartBody.cpp lib/Multipart.Part.cpp lib/Multipart.Builder.cpp include/MultipartBody.hpp
        include/Callback.hpp # Interface
        include/WebSocket.hpp # Interface
        include/TLSVersion.hpp # Enum
        lib/TimeUnit.cpp include/TimeUnit.hpp)

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
if(NOT CMAKE_INSTALL_PREFIX)
    if(WIN32)
        set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})
    elseif(UNIX)
        set(CMAKE_INSTALL_PREFIX /usr)
    endif()
endif()

foreach (file ${LIB_SOURCE_FILES})
    string(REGEX MATCH ^include found ${file})
    if (found)
        install(FILES ${file} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
    endif ()
endforeach ()
install(TARGETS ohf DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)