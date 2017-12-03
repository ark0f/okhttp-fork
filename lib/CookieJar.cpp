//
// Created by Good_Pudge.
//

#include <ohf/CookieJar.hpp>

namespace ohf {
    /* CookieJar */
    std::vector<Cookie> CookieJar::NO_COOKIES::loadFromRequest(HttpURL &httpURL) {
        return std::vector<Cookie>();
    }

    void CookieJar::NO_COOKIES::saveFromResponse(HttpURL &httpURL, std::vector<Cookie> &cookies) {}
}