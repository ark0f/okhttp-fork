## OkHttp fork for C++ 
|           | master                                                                                                                                                                       | dev                                                                                                                                                                       |
|:---------:|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |:------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Travis CI | [![Build status](https://img.shields.io/travis/Good-Pudge/okhttp-fork/master.svg?style=flat-square)](https://travis-ci.org/Good-Pudge/okhttp-fork)                           | [![Build status](https://img.shields.io/travis/Good-Pudge/okhttp-fork/dev.svg?style=flat-square)](https://travis-ci.org/Good-Pudge/okhttp-fork)                           |
| AppVeyor  | [![Build status](https://img.shields.io/appveyor/ci/Good-Pudge/okhttp-fork/master.svg?style=flat-square)](https://ci.appveyor.com/project/Good-Pudge/okhttp-fork)            | [![Build status](https://img.shields.io/appveyor/ci/Good-Pudge/okhttp-fork/dev.svg?style=flat-square)](https://ci.appveyor.com/project/Good-Pudge/okhttp-fork)            |
| Codecov   | [![Codecov branch](https://img.shields.io/codecov/c/github/Good-Pudge/okhttp-fork/master.svg?style=flat-square)](https://codecov.io/gh/Good-Pudge/okhttp-fork/branch/master) | [![Codecov branch](https://img.shields.io/codecov/c/github/Good-Pudge/okhttp-fork/dev.svg?style=flat-square)](https://codecov.io/gh/Good-Pudge/okhttp-fork/branch/dev)    |


## Overview
* [Used libraries](#used_libs)
* [Supported compilers](#compilers)
* [Installation](#installation)
* [Components](#components)
* [License](#license)

## <a name="used_libs"></a> Used libraries
* [OpenSSL](https://github.com/openssl/openssl)
* [Catch2](https://github.com/catchorg/Catch2) (submodule in `tests`)

## <a name="compilers"></a> Compilers
You can use any compiler that support full C++11 standard. These are tested by me and CI:
* GCC >= 5
* MSVC >= 2015
* MinGW (7.2.0)
* Clang (3.8 and Travis CI default version)

These compilers tested and aren't supported:
* GCC 4.9.2 (issue: `mktime`)
* MSVC 2013 (issue: `noexcept`)

## <a name="installation"></a> Installation
The first step:
````bash
git clone https://github.com/Good-Pudge/OkHttpFork.git
cd OkHttpFork
cd build
cmake ..
````
If you want to build the library as shared, use `BUILD_SHARED_LIBS` option (default: `OFF`)
````bash
cmake .. -DBUILD_SHARED_LIBS=ON
````  
Also you can use `TESTS` option to compile tests (default: `ON`)
````bash
cmake .. -DTESTS=ON
````
And if you need DTLS, use `DTLS` option (default: `OFF`)
````bash
cmake .. -DDTLS=ON
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
* #### UNIX-like
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
    * Iterator
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
- [x] Response
    - [x] Builder
- [x] ResponseBody
    * StreamBuf
- [ ] Route
- [x] WebSocket
    - [x] Factory
    - [x] Listener

#### Additional and moved components:
* namespace `ssl`
    * Context
    * Initializer
    * Socket
    * SSL
    * Challenge
* namespace `tcp`
    * Server
        * Connection
        * Iterator
    * Socket
        * StreamBuf
    * SSLServer (extends Server)
    * SSLSocket (extends Socket)
* namespace `udp`
    * Socket
* IOStreamBuf
* InetAddress
* TimeUnit

## <a name="license"></a> License
OkHttp fork distribute with an Apache 2.0 License. See LICENSE and NOTICE for more info.
