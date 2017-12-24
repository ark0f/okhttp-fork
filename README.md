## OkHttp fork for C++ 
[![Build Status](https://travis-ci.org/Good-Pudge/okhttp-fork.svg?branch=master)](https://travis-ci.org/Good-Pudge/okhttp-fork)
[![Build status](https://ci.appveyor.com/api/projects/status/sfpb0w34urnfn59l?svg=true)](https://ci.appveyor.com/project/Good-Pudge/okhttp-fork)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/7fa35ce47ad34ad991db821a9ece9c42)](https://www.codacy.com/app/Good-Pudge/okhttp-fork?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Good-Pudge/okhttp-fork&amp;utm_campaign=Badge_Grade)

## Overview
* [Used libraries](#used_libs)
* [Installation](#installation)
* [Components](#components)
* [License](#license)

## <a name="used_libs"></a> Used libraries
* [OpenSSL](https://github.com/openssl/openssl)
* [Catch2](https://github.com/catchorg/Catch2) (automatically download single-include file into `tests/catch.hpp`)

## <a name="installation"></a> Installation
The first step:
````bash
git clone https://github.com/Good-Pudge/OkHttpFork.git
cd OkHttpFork
cd build
cmake ..
````
If you want to build the library as shared, use `BUILD_SHARED` option (default: `OFF`)
````bash
cmake .. -DBUILD_SHARED=ON
````  
Also you can use `TESTS` option to compile tests (default: `ON`)
````bash
cmake .. -DTESTS=ON
````

The second step for different systems:
* #### Windows:
    * MSVC:
    ````bash
    cmake --build . --target INSTALL
    ````
    * MinGW:
    ````bash
    mingw32-make -j2
    mingw32-make install
    ````
    * UNIX-like
    ````bash
    make -j2
    sudo make install
    ````
    Will installed directories in `${CMAKE_INSTALL_PREFIX}`. This are `include/ohf` and `lib`

## <a name="components"></a> Original library components
- [ ] Address
- [ ] Authenticator
- [ ] Cache
- [x] CacheControl
    - [x] Builder
- [x] Call
    - [x] Factory
- [x] Callback
- [ ] CertificatePinner
    - [ ] Builder
- [ ] Challenge
- [ ] CipherSuite
- [ ] Connection
- [ ] ConnectionPool
- [ ] ConnectionSpec
    - [ ] Builder
- [x] Cookie
    - [x] Builder
- [x] CookieJar
- [ ] Credentials
- [ ] Dispatcher
- [x] DNS
- [ ] EventListener
    - [ ] Factory
- [x] FormBody
    - [x] Builder
- [ ] Handshake
- [x] Headers
    * Iterator (additional)
    - [x] Builder
- [x] HttpURL
    - [x] Builder
- [ ] Interceptor
    - [ ] Chain
- [x] MediaType
- [x] MultipartBody
    - [x] Builder
    - [x] Part
- [ ] Client
    - [ ] Builder
- [x] Protocol
- [x] Request
    - [x] Builder
- [x] RequestBody
- [ ] Response
    - [ ] Builder
- [x] ResponseBody
- [ ] Route
- [x] WebSocket
    - [x] Factory
    - [x] Listener

#### Additional components:
* namespace `ssl`
    * Context
    * Initializer
    * Socket
    * SSL
* namespace `tcp`
    * Server
        * Connection
        * Iterator
    * Socket
        * StreamBuf
    * SSLServer (extends Server)
    * SSLSocket (extends Socket)
* InetAddress
* TimeUnit
* UDPSocket

## <a name="license"></a> License
OkHttp fork distribute with an Apache 2.0 License. See LICENSE and NOTICE for more info.
