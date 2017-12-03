//
// Created by Senya on 02.09.2017.
//

#include <iostream>
#include <string>
#include <ohf/Exception.hpp>
#include <ohf/HttpURL.hpp>

int main() {
    try {
        //encode / decode
        std::cout << "Decoded string \"%D0%9F%D1%80%D0%B8%D0%B2%D0%B5%D1%82\": " // "Привет" mean "Hello" in russian language
                  << ohf::HttpURL::decode("%D0%9F%D1%80%D0%B8%D0%B2%D0%B5%D1%82") << std::endl;
        std::cout << "Encoded string \"Привет\":                               "
                  << ohf::HttpURL::encode("Привет") << std::endl;
        std::cout << "Encoded string \"Hello, world\":                         "
                  << ohf::HttpURL::encode("Hello, world") << std::endl;

        //default ports
        std::cout << "HTTPS:              " << ohf::HttpURL::defaultPort("https") << std::endl;
        std::cout << "HTTP:               " << ohf::HttpURL::defaultPort("http") << std::endl;
        std::cout << "UNDEFINED PROTOCOL: " << ohf::HttpURL::defaultPort("undefined") << std::endl;

        ohf::HttpURL url = "https://www.google.com/search?q=123#TEST";
        std::cout << "Encoded fragment:      " << url.encodedFragment() << std::endl;
        std::cout << "Fragment:              " << url.fragment() << std::endl;
        std::cout << "Encoded path:          " << url.encodedPath() << std::endl;
        std::cout << "Encoded path segment from vector: " << url.encodedPathSegments()[0] << std::endl;
        std::cout << "Encoded query:         " << url.encodedQuery() << std::endl;
        std::cout << "Query:                 " << url.query() << std::endl;

        ohf::HttpURL copyUrl = url;
        std::cout << "Self equals copy: " << (url == copyUrl) << std::endl;
        std::cout << "Host:                  " << url.host() << std::endl;
        std::cout << "Is HTTPS:              " << url.isHttps() << std::endl;
        std::cout << "Path segment from vector: " << url.pathSegments()[0] << std::endl;
        std::cout << "Path size:             " << url.pathSize() << std::endl;
        std::cout << "Port:                  " << url.port() << std::endl;
        std::cout << "URL:                   " << url.url() << std::endl;
        std::cout << "Query parameter \"q\":   " << url.queryParameter("q") << std::endl;
        std::cout << "Query parameter name:  " << url.queryParameterName(0) << std::endl;
        std::cout << "Query parameter value: " << url.queryParameterValue(0) << std::endl;
        std::cout << "Query size:            " << url.querySize() << std::endl;
        std::cout << "Scheme:                " << url.scheme() << std::endl;

        ohf::HttpURL u = ohf::HttpURL::Builder()
                .addPathSegments("/path/search/google/")
                .fragment("GOOGLE")
                .host("www.google.com")
                .port(228)
                .query("q=123&lang=ru_RU")
                .removeQueryParameter("lang")
                .removePathSegment(0)
                .scheme("ftp")
                .setPathSegment(1, "kek/")
                .setQueryParameter("pos", "1,0")
                .build();

        std::cout << u << std::endl;
    } catch (ohf::Exception &e) {
        std::cout << e.what() << std::endl << "\tCode: " << e.code() << std::endl;
    }
}
