//
// Created by Good_Pudge.
//

#if WIN32
#   include <windows.h>
#endif

#include <catch.hpp>
#include <internal/catch_session.h>

int main(int argc, char **argv) {
#if WIN32
    unsigned int cp = GetConsoleCP();
    unsigned int cpo = GetConsoleOutputCP();

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    int result = Catch::Session().run(argc, argv);

#if WIN32
    SetConsoleCP(cp);
    SetConsoleOutputCP(cpo);
#endif

    return result;
}
