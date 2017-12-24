//
// Created by Good_Pudge.
//

#include <ohf/HttpURL.hpp>
#include "util/string.hpp"
#include <ohf/Exception.hpp>

namespace ohf {
    HttpURL::Builder::Builder() :
            mPathSuffix(false),
            mPort(80),
            mScheme("http")
    {}

    HttpURL::Builder &HttpURL::Builder::addPathSegments(const std::string &pathSegments) {
        mPathSuffix = util::string::endsWith(pathSegments, "/");
        std::vector<std::string> segments = util::string::split(pathSegments, "/");
        if (!segments.empty()) {
            for (const auto &segment : segments)
                mPath.push_back(HttpURL::decode(segment));
        }
        return *this;
    }

    HttpURL HttpURL::Builder::build() {
        return {this};
    }

    HttpURL::Builder &HttpURL::Builder::fragment(const std::string &fragment) {
        mPathSuffix = true;
        mFragment = HttpURL::decode(fragment);
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::host(const std::string &host) {
        mHost = HttpURL::decode(host);
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::port(Uint16 port) {
        mPort = port;
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::query(const std::string &query) {
        mPathSuffix = true;
        std::vector<std::string> queries = util::string::split(query, "&");
        for (const auto &parameter : queries) {
            std::vector<std::string> nameValue = util::string::split(parameter, "=");
            if (nameValue.size() == 2)
                mQuery[nameValue[0]] = nameValue[1];
            else if (nameValue.size() == 1)
                mQuery[nameValue[0]] = std::string();
            else
                throw Exception(Exception::Code::INVALID_QUERY_PARAMETER, "Invalid query parameter: " + parameter);
        }
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::removeQueryParameter(const std::string &name) {
        auto it = mQuery.find(name);
        if (mQuery.find(name) != mQuery.end())
            mQuery.erase(it);
        if(mQuery.empty() && mFragment.empty() && mPath.empty()) mPathSuffix = false;
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::removePathSegment(Uint32 index) {
        if (index < this->mPath.size()) {
            mPathSuffix = index != this->mPath.size() - 1;
            auto path_segment = std::next(this->mPath.begin(), index);
            this->mPath.erase(path_segment);
        }
        if(mPath.empty()) mPathSuffix = false;
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::scheme(const std::string &scheme) {
        mScheme = scheme;
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::setPathSegment(Uint32 index, std::string pathSegment) {
        if (index < mPath.size()) {
            if (util::string::endsWith(pathSegment, "/")) {
                pathSegment = pathSegment.substr(0, pathSegment.length() - 1);
                mPathSuffix = true;
            }
            mPath[index] = HttpURL::decode(pathSegment);
        }
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::setQueryParameter(const std::string &name, const std::string &value) {
        mQuery[name] = HttpURL::decode(value);
        return *this;
    }

    HttpURL::Builder &HttpURL::Builder::pathEndsWithSlash(bool b) {
        mPathSuffix = b;
        return *this;
    }
}