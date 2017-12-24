//
// Created by Good_Pudge.
//

#include <ohf/Config.hpp>

#if defined(OKHTTPFORK_WINDOWS)
    #include "win32/SocketImpl.hpp"
#elif defined(OKHTTPFORK_UNIX)
    #include "unix/SocketImpl.hpp"
#endif
