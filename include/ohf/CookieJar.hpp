//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_COOKIEJAR_HPP
#define OKHTTPFORK_COOKIEJAR_HPP

#include <vector>
#include "Cookie.hpp"

namespace ohf {
    class CookieJar {
    public:
        virtual std::vector<Cookie> loadFromRequest(HttpURL &httpURL) = 0;

        virtual void saveFromResponse(HttpURL &httpURL, std::vector<Cookie> &cookies) = 0;

        class NO_COOKIES;
    };

    class CookieJar::NO_COOKIES : public CookieJar {
    public:
        std::vector<Cookie> loadFromRequest(HttpURL &httpURL);

        void saveFromResponse(HttpURL &httpURL, std::vector<Cookie> &cookies);
    };
}

#endif //OKHTTPFORK_COOKIEJAR_HPP
