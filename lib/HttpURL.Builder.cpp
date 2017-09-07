//
// Created by Good_Pudge.
//

#include "../include/HttpURL.hpp"
#include "../util/include/string.hpp"
#include "../include/Exception.hpp"

using namespace ohf;

void HttpUrl::Builder::addPathSegments(const std::string &pathSegments) {
    pathEndsWithSlash_bool = util::string::endsWith(pathSegments, "/");
    std::vector<std::string> segments = util::string::split(pathSegments, "/");
    if (!segments.empty()) {
        for (const auto &segment : segments)
            this->pathSegments.push_back(HttpUrl::decode(segment));
    }
}

HttpUrl HttpUrl::Builder::build() {
    HttpUrl url;
    url.pathSegments_vec = pathSegments;
    url.queryParameters = queryParameters;
    url.fragment_str = fragment_str;
    if (host_str.empty())
        throw Exception(Exception::Code::HOST_IS_EMPTY, "Host is empty: ");
    url.host_str = host_str;
    url.port_num = port_num;
    url.scheme_str = scheme_str;
    url.pathEndsWithSlash = pathEndsWithSlash_bool;
    return url;
}

void HttpUrl::Builder::fragment(const std::string &fragment) {
    fragment_str = HttpUrl::decode(fragment);
}

void HttpUrl::Builder::host(const std::string &host) {
    host_str = HttpUrl::decode(host);
}

void HttpUrl::Builder::port(const int &port) {
    port_num = port;
}

void HttpUrl::Builder::query(const std::string &query) {
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

void HttpUrl::Builder::removeQueryParameter(const std::string &name) {
    auto it = queryParameters.find(name);
    if (queryParameters.find(name) != queryParameters.end()) // found
        queryParameters.erase(it);
}

void HttpUrl::Builder::removePathSegment(const int &index) {
    if (index < this->pathSegments.size()) { // check out of range
        pathEndsWithSlash_bool = index != this->pathSegments.size() - 1;
        auto path_segment = std::next(this->pathSegments.begin(), index);
        this->pathSegments.erase(path_segment);
    }
}

void HttpUrl::Builder::scheme(const std::string &scheme) {
    scheme_str = scheme;
}

void HttpUrl::Builder::setPathSegment(const int &index, std::string pathSegment) {
    if (index < pathSegments.size()) {
        if (util::string::endsWith(pathSegment, "/")) {
            pathSegment = pathSegment.substr(0, pathSegment.length() - 1);
            pathEndsWithSlash_bool = true;
        }
        pathSegments[index] = HttpUrl::decode(pathSegment);
    }
}

void HttpUrl::Builder::setQueryParameter(const std::string &name, const std::string &value) {
    queryParameters[name] = HttpUrl::decode(value);
}

void HttpUrl::Builder::pathEndsWithSlash(bool b) {
    pathEndsWithSlash_bool = b;
}