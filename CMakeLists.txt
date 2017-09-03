cmake_minimum_required(VERSION 2.4)
project(OkHttpFork)

set(CMAKE_CXX_STANDARD 11)

set(LIB_SOURCE_FILES
        lib/Client.cpp include/Client.hpp
        lib/Call.cpp include/Call.hpp
        lib/Response.cpp include/Response.hpp
        lib/Request.cpp include/Request.hpp
        lib/ResponseBody.cpp include/ResponseBody.hpp
        lib/CacheControl.cpp include/CacheControl.hpp
        lib/Challenge.cpp include/Challenge.hpp
        lib/Handshake.cpp include/Handshake.hpp
        lib/Headers.cpp include/Headers.hpp
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
        lib/CookieJar.cpp include/CookieJar.hpp
        lib/Dispatcher.cpp include/Dispatcher.hpp
        lib/Dns.cpp include/Dns.hpp
        lib/HostnameVerifier.cpp include/HostnameVerifier.hpp
        lib/Interceptor.cpp include/Interceptor.hpp
        lib/Proxy.cpp include/Proxy.hpp
        lib/ProxySelector.cpp include/ProxySelector.hpp
        lib/RequestBody.cpp include/RequestBody.hpp
        lib/HttpUrl.cpp include/HttpUrl.hpp
        lib/MediaType.cpp include/MediaType.hpp
        lib/Exception.cpp include/Exception.hpp
        lib/Socket.cpp include/Socket.hpp
        lib/SSLSocket.cpp include/SSLSocket.hpp
        lib/Cookie.cpp include/Cookie.hpp)
set(LIB_SOURCE_FILES ${LIB_SOURCE_FILES}
        util/lib/string.cpp util/include/string.hpp
        util/lib/util.cpp util/include/util.hpp
        )
add_library(ohf SHARED ${LIB_SOURCE_FILES})

#OpenSSL
find_package(OpenSSL)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    target_link_libraries(ohf ${OPENSSL_LIBRARIES})
else ()
    message(FATAL_ERROR "OpenSSL not found")
endif ()
