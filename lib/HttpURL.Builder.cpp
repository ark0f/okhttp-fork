//
// Created by Good_Pudge.
//

#include "../include/HttpURL.hpp"
#include "../util/string.hpp"
#include "../include/Exception.hpp"

namespace ohf {
    HttpURL::Builder::Builder() :
            mPathEndsWithFlash(false),
            mPort(80),
            mScheme("http") {}

    HttpURL::Builder &HttpURL::Builder::addPathSegments(const std::string &pathSegments) {
        mPathEndsWithFlash = util::string::endsWith(pathSegments, "/");
        std::vector<std::string> segments = util::string::split(pathSegments, "/");
        if (!segments.empty()) {
            for (const auto &segment : segments)
                this->pathSegments.push_back(HttpURL::decode(segment));
        }
        return *this;
    }

    HttpURL HttpURL::Builder::build() {
        return {this};
    }

    HttpURL::Builder &HttpURL::Builder::fragment(const std::string &fragment) {
        mFragment = HttpURL::decode(fragment);
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::host(const std::string &host) {
        mHost = HttpURL::decode(host);
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::port(const int &port) {
        mPort = port;
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::query(const std::string &query) {
        std::vector<std::string> queries = util::string::split(query, "&");
        for (const auto &parameter : queries) {
            std::vector<std::string> nameValue = util::string::split(parameter, "=");
            if (nameValue.size() == 2)
                mQueryParameters[nameValue[0]] = nameValue[1];
            else if (nameValue.size() == 1)
                mQueryParameters[nameValue[0]] = std::string();
            else
                throw Exception(Exception::Code::INVALID_QUERY_PARAMETER, "Invalid query parameter: " + parameter);
        }
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::removeQueryParameter(const std::string &name) {
        auto it = mQueryParameters.find(name);
        if (mQueryParameters.find(name) != mQueryParameters.end()) // found
            mQueryParameters.erase(it);
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::removePathSegment(const int &index) {
        if (index < this->pathSegments.size()) { // check out of range
            mPathEndsWithFlash = index != this->pathSegments.size() - 1;
            auto path_segment = std::next(this->pathSegments.begin(), index);
            this->pathSegments.erase(path_segment);
        }
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::scheme(const std::string &scheme) {
        mScheme = scheme;
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::setPathSegment(const int &index, std::string pathSegment) {
        if (index < pathSegments.size()) {
            if (util::string::endsWith(pathSegment, "/")) {
                pathSegment = pathSegment.substr(0, pathSegment.length() - 1);
                mPathEndsWithFlash = true;
            }
            pathSegments[index] = HttpURL::decode(pathSegment);
        }
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::setQueryParameter(const std::string &name, const std::string &value) {
        mQueryParameters[name] = HttpURL::decode(value);
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::pathEndsWithSlash(bool b) {
        mPathEndsWithFlash = b;
        return *this;
    }
}