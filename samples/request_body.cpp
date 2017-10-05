//
// Created by Senya on 02.09.2017.
//

#include <fstream>
#include <iostream>
#include <ohf/RequestBody.hpp>
#include <ohf/Exception.hpp>

int main() {
    try {
        ohf::MediaType common = "text/html";

        std::ifstream ifs("CMakeLists.txt", std::ios_base::binary);
        ohf::RequestBody ifsbody(common, ifs);
        std::cout << "std::ifstream | Content length: " << ifsbody.contentLength() << std::endl;

        char content[] = "Hello, world";
        ohf::RequestBody charBody(common, content);
        std::cout << "char[] | Content length: " << charBody.contentLength() << std::endl;

        ohf::RequestBody cutCharBody(common, content, 3, 5);
        std::cout << "char[] with offset and length | Content length: " << cutCharBody.contentLength() << std::endl;

        std::string c = "Hello, world";
        ohf::RequestBody stringBody(common, c);
        std::cout << "std::string | Content length: " << stringBody.contentLength() << std::endl;

        std::cout << "ohf::MediaType | Type: " << stringBody.contentType().type() << std::endl;
    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl << "\tCode: " << e.code() << std::endl;
    }
}