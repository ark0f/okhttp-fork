//
// Created by Senya on 02.09.2017.
//

#include <iostream>
#include <ohf/Exception.hpp>
#include <ohf/ResponseBody.hpp>

int main() {
    try {
        ohf::MediaType common = "text/html";

        ohf::ResponseBody body(common, "Hello");
        std::cout << "Bytes: " << body.bytes() << std::endl;
        std::cout << "String: " << body.string() << std::endl;
        std::cout << "Content-Type: " << body.contentType().type() << std::endl;
        std::cout << "Content-Length: " << body.contentLength() << std::endl;
    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl << "\tCode: " << e.code() << std::endl;
    }
}
