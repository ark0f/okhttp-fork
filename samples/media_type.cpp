//
// Created by Senya on 02.09.2017.
//

#include <iostream>
#include "include/Exception.hpp"
#include "include/MediaType.hpp"

int main() {
    try {
        ohf::MediaType mediaType("text/html");
        std::cout << "Type: " << mediaType.type() << std::endl;
        std::cout << "Subtype: " << mediaType.subtype() << std::endl;
        std::cout << "Charset: " << mediaType.charset() << std::endl;
        std::cout << "Charset with default value: " << mediaType.charset("utf8") << std::endl;
        std::cout << "Boundary: " << mediaType.boundary() << std::endl;
        std::cout << "Boundary with default value: " << mediaType.boundary("----123123") << std::endl;
        std::cout << "Self equals self: " << (mediaType == mediaType) << std::endl;
    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl << "\tCode: " << e.code() << std::endl;
    }
}
