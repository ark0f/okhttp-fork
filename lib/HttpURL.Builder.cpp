//
// Created by Good_Pudge.
//

#include "../include/HttpURL.hpp"
#include "../util/string.hpp"
#include "../include/Exception.hpp"

using namespace ohf;

void HttpURL::Builder::addPathSegments(const std::string &pathSegments) {
    pathEndsWithSlash_bool = util::string::endsWith(pathSegments, "/");
    std::vector<std::string> segments = util::string::split(pathSegments, "/");
    if (!segments.empty()) {
        for (const auto &segment : segments)
            this->pathSegments.push_back(HttpURL::decode(segment));
    }
}

HttpURL HttpURL::Builder::build() {
    HttpURL url;
    url.mPathSegments = pathSegments;
    url.queryParameters = queryParameters;
    url.mFragment = fragment_str;
    if (host_str.empty())
        throw Exception(Exception::Code::HOST_IS_EMPTY, "Host is empty: ");
    url.mHost = host_str;
    url.mPort = port_num;
    url.mScheme = scheme_str;
    url.pathEndsWithSlash = pathEndsWithSlash_bool;
    return url;
}

void HttpURL::Builder::fragment(const std::string &fragment) {
    fragment_str = HttpURL::decode(fragment);
}

void HttpURL::Builder::host(const std::string &host) {
    host_str = HttpURL::decode(host);
}

void HttpURL::Builder::port(const int &port) {
    port_num = port;
}

void HttpURL::Builder::query(const std::string &query) {
    std::vector<std::string> queries = util::string::split(query, "&");
    for (const auto &parameter : queries) {
        std::vector<std::string> nameValue = util::string::split(parameter, "=");
        if (nameValue.size() == 2)
            queryParameters[nameValue[0]] = nameValue[1];
        else if (nameValue.size() == 1)
            queryParameters[nameValue[0]] = std::string();
        else
            throw Exception(Exception::Code::INVALID_QUERY_PARAMETER, "Invalid query parameter: " + parameter);
    }
}

void HttpURL::Builder::removeQueryParameter(const std::string &name) {
    auto it = queryParameters.find(name);
    if (queryParameters.find(name) != queryParameters.end()) // found
        queryParameters.erase(it);
}

void HttpURL::Builder::removePathSegment(const int &index) {
    if (index < this->pathSegments.size()) { // check out of range
        pathEndsWithSlash_bool = index != this->pathSegments.size() - 1;
        auto path_segment = std::next(this->pathSegments.begin(), index);
        this->pathSegments.erase(path_segment);
    }
}

void HttpURL::Builder::scheme(const std::string &scheme) {
    scheme_str = scheme;
}

void HttpURL::Builder::setPathSegment(const int &index, std::string pathSegment) {
    if (index < pathSegments.size()) {
        if (util::string::endsWith(pathSegment, "/")) {
            pathSegment = pathSegment.substr(0, pathSegment.length() - 1);
            pathEndsWithSlash_bool = true;
        }
        pathSegments[index] = HttpURL::decode(pathSegment);
    }
}

void HttpURL::Builder::setQueryParameter(const std::string &name, const std::string &value) {
    queryParameters[name] = HttpURL::decode(value);
}

void HttpURL::Builder::pathEndsWithSlash(bool b) {
    pathEndsWithSlash_bool = b;
}