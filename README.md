## OkHttp fork for C++ [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg?style=flat-square)](https://opensource.org/licenses/Apache-2.0)
|           | master                                                                                                                                                                       | dev                                                                                                                                                                       |
|:---------:|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |:------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Travis CI | [![Build status](https://img.shields.io/travis/Good-Pudge/okhttp-fork/master.svg?style=flat-square)](https://travis-ci.org/Good-Pudge/okhttp-fork)                           | [![Build status](https://img.shields.io/travis/Good-Pudge/okhttp-fork/dev.svg?style=flat-square)](https://travis-ci.org/Good-Pudge/okhttp-fork)                           |
| AppVeyor  | [![Build status](https://img.shields.io/appveyor/ci/Good-Pudge/okhttp-fork/master.svg?style=flat-square)](https://ci.appveyor.com/project/Good-Pudge/okhttp-fork)            | [![Build status](https://img.shields.io/appveyor/ci/Good-Pudge/okhttp-fork/dev.svg?style=flat-square)](https://ci.appveyor.com/project/Good-Pudge/okhttp-fork)            |
| Codecov   | [![Codecov master](https://img.shields.io/codecov/c/github/Good-Pudge/okhttp-fork/master.svg?style=flat-square)](https://codecov.io/gh/Good-Pudge/okhttp-fork/branch/master) | [![Codecov branch](https://img.shields.io/codecov/c/github/Good-Pudge/okhttp-fork/dev.svg?style=flat-square)](https://codecov.io/gh/Good-Pudge/okhttp-fork/branch/dev)    |

## Overview
* [Used libraries](#used_libs)
* [Supported compilers](#compilers)
* [Installation](#installation)
* [CMake options](#options)
* [Components](#components)
* [License](#license)

## <a name="used_libs"></a> Used libraries
* [OpenSSL](https://github.com/openssl/openssl)
* [Catch2](https://github.com/catchorg/Catch2) (submodule in `tests`)

## <a name="compilers"></a> Compilers
You can use any compiler that support full C++11 standard. These were tested by me and CI:
* GCC >= 5
* MSVC >= 2015
* MinGW (7.2.0)
* Clang (3.8 and Travis CI default version)

These compilers tested and aren't supported:
* GCC 4.9.2 (issue: `std::get_time`)
* MSVC 2013 (issue: `noexcept`)

## <a name="installation"></a> Installation
````bash
git clone --recursive https://github.com/Good-Pudge/okhttp-fork.git
cd okhttp-fork
mkdir build
cd build
cmake ..
cmake --build . --target install
````

## <a name="options"></a> CMake options
* `CMAKE_INSTALL_PREFIX` - installation path that contain `include/ohf` and `lib`
* `BUILD_SHARED_LIBS` (default: `OFF`) - build library as shared.
* `BUILD_TESTING` (default: `OFF`) - build executable for tests.
* `BUILD_EXAMPLES` (default: `OFF`) - build executables of examples.
* `ENABLE_DTLS` (default: `OFF`, as WIP) - access to use DTLS components.

## <a name="components"></a> Original library components
- [x] Address
- [ ] Authenticator
- [ ] Cache
- [x] CacheControl
    - [x] Builder
- [x] Call
    - [x] Factory
- [x] Callback
- [ ] CertificatePinner
    - [ ] Builder
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
    * CipherSuite
    * Exception
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
* Exception

## <a name="license"></a> License
OkHttp fork distribute with an Apache 2.0 License. See LICENSE and NOTICE for more info.
