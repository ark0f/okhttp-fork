cmake_minimum_required(VERSION 2.8)
project(OkHttpFork)

set(CMAKE_CXX_STANDARD 11)

# Cross-platform files
set(LIB_SOURCE_FILES
        lib/Client.cpp include/Client.hpp
        lib/Call.cpp include/Call.hpp
        lib/Response.cpp include/Response.hpp
        lib/Request.cpp include/Request.hpp
        lib/ResponseBody.cpp include/ResponseBody.hpp
        lib/CacheControl.cpp include/CacheControl.hpp
        lib/Challenge.cpp include/Challenge.hpp
        lib/Handshake.cpp include/Handshake.hpp
        lib/Headers.cpp lib/Headers.Builder.cpp include/Headers.hpp
        lib/Protocol.cpp include/Protocol.hpp
        lib/CipherSuite.cpp include/CipherSuite.hpp
        lib/TLSVersion.cpp include/TLSVersion.hpp
        lib/Certificate.cpp include/Certificate.hpp
        lib/Principal.cpp include/Principal.hpp
        lib/Authenticator.cpp include/Authenticator.hpp
        lib/Cache.cpp include/Cache.hpp
        lib/CertificatePinner.cpp include/CertificatePinner.hpp
        lib/ConnectionPool.cpp include/ConnectionPool.hpp
        lib/ConnectionSpec.cpp include/ConnectionSpec.hpp
        include/CookieJar.hpp # Interface
        lib/Dispatcher.cpp include/Dispatcher.hpp
        lib/Dns.cpp include/Dns.hpp
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
        lib/Cookie.cpp lib/Cookie.Builder.cpp include/Cookie.hpp)

# Files for different platforms
if (WIN32)
    set(SYSTEM_LIB_PATH lib/Win32)
elseif (UNIX)
    set(SYSTEM_LIB_PATH lib/UNIX)
endif ()

set(LIB_SOURCE_FILES ${LIB_SOURCE_FILES}
        ${SYSTEM_LIB_PATH}/Socket.cpp)

# Util files
set(LIB_SOURCE_FILES ${LIB_SOURCE_FILES}
        util/lib/string.cpp util/include/string.hpp
        util/lib/util.cpp util/include/util.hpp)

add_library(ohf SHARED ${LIB_SOURCE_FILES})

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
    set(INCLUDE_INSTALL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ohf/include/ohf)
    set(LIB_INSTALL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ohf/lib)
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