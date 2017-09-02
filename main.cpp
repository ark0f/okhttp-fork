#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <regex>
#include "include/HttpUrl.hpp"
#include "include/Headers.hpp"
#include "include/Exception.hpp"
#include "include/MediaType.hpp"
#include "include/RequestBody.hpp"
#include "include/ResponseBody.hpp"
#include "include/Socket.hpp"
#include "include/SSLSocket.hpp"

int main() {
#if _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#else
    std::locale::global(std::locale(""));
#endif

    try {

        ohf::SSLSocket socket;

        std::iostream &os = socket.connect("www.youtube.com", 443);
        os << "GET / HTTP/1.1\r\n";
        os << "Host: www.youtube.com\r\n";
        os << "Connection: close\r\n\r\n";

        std::string test;
        os >> test;
        std::cout << test << std::endl;

        socket.disconnect();
    } catch (ohf::Exception &e) {
        std::cerr << e.what() << std::endl << "\tCode: " << e.code() << std::endl;
        return 1;
    }

    return 0;
}
