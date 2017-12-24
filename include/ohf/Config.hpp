//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CONFIG_HPP
#define OKHTTPFORK_CONFIG_HPP

#if defined(_WIN32)
    #define OKHTTPFORK_WINDOWS
#elif defined(__unix__)
    #define OKHTTPFORK_UNIX
#endif

namespace ohf {
    typedef char Int8;
    typedef unsigned char Uint8;

    typedef short Int16;
    typedef unsigned short Uint16;

    typedef int Int32;
    typedef unsigned int Uint32;

    typedef long long Int64;
    typedef unsigned long long Uint64;
}

#endif //OKHTTPFORK_CONFIG_HPP
