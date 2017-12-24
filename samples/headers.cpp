//
// Created by Senya on 02.09.2017.
//

#include <iostream>
#include <string>
#include <ohf/Exception.hpp>
#include <ohf/Headers.hpp>

int main() {
    try {
        ohf::Headers headers = ohf::Headers::Builder()
                .add("Connection: close")
                .add("How", "IDK")
                .set("Hello", "world")
                .add("Server", "own")
                .add("Date", "Tue, 15 Nov 2010 08:12:31 GMT")
                .build();

        std::cout << "Header by get(\"Hello\"): " << headers.get("Hello") << std::endl
                  << "Date: " << headers.getDate().seconds() << std::endl
                  << "Name by index: " << headers.name(0) << std::endl
                  << "Name by vector: " << headers.names()[0] << std::endl
                  << "Value by index: " << headers.value(0) << std::endl
                  << "Value by vector: " << headers.values("How")[0] << std::endl
                  << "Size: " << headers.size() << std::endl
                  << "Self equals self: " << (headers == headers) << std::endl;

        headers = headers.newBuilder()
                .add("XXX", "YYY")
                .build();

        std::cout << "Header \"XXX\" by builder: " << headers.get("XXX") << std::endl;

        std::map<std::string, std::string> map;
        map["WWW"] = "AAA";
        ohf::Headers h(map);
        std::cout << "Header \"WWW\" by ohf::Headers(std::map<std::string, std::string>): "
                  << h.get("WWW")
                  << std::endl;

        std::cout << "h equals headers: " << (h == headers) << std::endl;

        for(const auto &header : headers) {
            std::cout << header.first << ": " << header.second << std::endl;
        }
        /* OR
         *
         * for(const auto &name : headers.names()) {
         *     for(const auto &value : headers.values(name)) {
         *         std::cout << name << ": " << value << std::endl;
         *     }
         * }
         */
    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl << "\tCode: " << e.code() << std::endl;
        return 1;
    }

    return 0;
}
