## OkHttp fork for C++ 
[![Build Status](https://travis-ci.org/Good-Pudge/okhttp-fork.svg?branch=master)](https://travis-ci.org/Good-Pudge/okhttp-fork)
[![Build status](https://ci.appveyor.com/api/projects/status/sfpb0w34urnfn59l?svg=true)](https://ci.appveyor.com/project/Good-Pudge/okhttp-fork)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/7fa35ce47ad34ad991db821a9ece9c42)](https://www.codacy.com/app/Good-Pudge/okhttp-fork?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Good-Pudge/okhttp-fork&amp;utm_campaign=Badge_Grade)

## Overview
* [Required libraries](#req_libs)
* [Installation](#installation)
* [Components](#components)
* [License](#license)

## <a name="req_libs"></a> Required libraries
* [OpenSSL](https://github.com/openssl/openssl)

## <a name="installation"></a> Installation
First step:
````bash
git clone https://github.com/Good-Pudge/OkHttpFork.git
cd OkHttpFork
cd build
cmake ..
````
If you want to build library as shared, use `BUILD_SHARED` option (default: OFF)
````bash
cmake .. -DBUILD_SHARED=ON
````  

Second step for different systems:
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
    And will be created directory `ohf` in which there are `include` and `lib` directories
* #### UNIX-like:
    ````bash
    make -j2
    sudo make install
    ````
    And include files will be installed to `/usr/include/ohf`, library into `/usr/lib/`

## <a name="components"></a> Components
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
* Socket (POSIX, Windows for now)
* SSLSocket (extends Socket)
* InetAddress
* TimeUnit

## <a name="license"></a> License
OkHttp fork distribute with an Apache 2.0 License. See LICENSE and NOTICE for more info.
