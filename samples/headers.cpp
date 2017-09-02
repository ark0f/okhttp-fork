//
// Created by Senya on 02.09.2017.
//

#include <iostream>
#include <string>
#include "../include/Exception.hpp"
#include "../include/Headers.hpp"

int main() {
    try {
        ohf::Headers::Builder builder;
        builder.add("Connection: close");
        builder.add("How", "IDK");
        builder.set("Hello", "world");
        builder["Server"] = "own";
        builder["Date"] = "Tue, 15 Nov 2010 08:12:31 GMT";

        ohf::Headers headers = builder.build();
        std::cout << "Header by [\"Hello\"]: " << headers["Hello"] << std::endl;
        std::cout << "Header by get(\"How\"): " << headers.get("How") << std::endl;
        std::cout << "Date: " << headers.getDate() << std::endl;
        std::cout << "Name by index: " << headers.name(0) << std::endl;
        std::cout << "Name by vector: " << headers.names()[0] << std::endl;
        std::cout << "Value by index: " << headers.value(0) << std::endl;
        std::cout << "Value by vector: " << headers.values()[0] << std::endl;
        std::cout << "Size: " << headers.size() << std::endl;
        std::cout << "Self equals self: " << (headers == headers) << std::endl;

        ohf::Headers::Builder b = headers.newBuilder();
        b.add("XXX", "YYY");
        headers = b.build();

        std::cout << "Header \"XXX\" by builder: " << headers["XXX"] << std::endl;

        std::map<std::string, std::string> map;
        map["WWW"] = "AAA";
        ohf::Headers h = ohf::Headers::of(map);
        std::cout << "Header \"WWW\" by ohf::Headers::of: " << h["WWW"] << std::endl;

        std::cout << "h equals headers: " << (h == headers) << std::endl;
    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl << "\tCode: " << e.code() << std::endl;
    }
}
