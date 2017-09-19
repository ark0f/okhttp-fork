# OkHttp fork for C++
#### Required libraries:
* [OpenSSL](https://github.com/openssl/openssl)

#### Installation:
First step:
````bash
git clone https://github.com/Good-Pudge/OkHttpFork.git
cd OkHttpFork
cmake .
````
Second step for different systems:
* ##### Windows:
    MSVC:
    ````bash
    cmake --build . --target INSTALL --configure Release
    ````
    MinGW:
    ````bash
    mingw32-make -j2
    ````
* ##### UNIX-like:
    ````bash
    make -j2
    sudo make install
    ````

#### Implemented components:
* Headers
* HttpURL
* MediaType
* RequestBody
* ResponseBody
* Socket (Windows, POSIX for now)
* SSLSocket (Windows, POSIX for now)
* Cookie
* CookieJar
