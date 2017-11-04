//
// Created by Good_Pudge.
//

#include "../include/Config.hpp"

#if defined(OKHTTPFORK_WINDOWS)
    #include "Win32/SocketImpl.hpp"
#elif defined(OKHTTPFORK_UNIX)
    #include "UNIX/SocketImpl.hpp"
#endif

