//
// Created by Good_Pudge.
//

#include <sstream>
#include <iomanip>
#include <iostream>
#include "../include/HttpUrl.hpp"
#include "../util/include/string.hpp"
#include "../include/Exception.hpp"

using namespace ohf;

std::string HttpUrl::encode(const std::string &str) {
    std::ostringstream oss;
    oss.fill('0');
    oss << std::hex;
    for (char c : str) {
        if (isalnum((unsigned char) c) || c == '-' || c == '_' || c == '.' || c == '~') {
            oss << c;
            continue;
        }

        oss << std::uppercase;
        oss << '%' << std::setw(2) << (int) (unsigned char) c;
        oss << std::nouppercase;
    }
    return oss.str();
}

std::string HttpUrl::decode(const std::string &str) {
    std::string encoded;
    // oss.fill('0');
    // oss << std::hex;
    for (std::string::size_type i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c == '%') {
            std::string hex = str.substr(i + 1, 2);
            try {
                encoded.push_back(std::stoi(hex, nullptr, 16));
            } catch (std::invalid_argument) {
                throw Exception(Exception::Code::INVALID_URI_HEX_CODE, "Invalid url hex code:" + hex);
            }
            i += 2;
        } else
            encoded += c;
    }
    return encoded;
}

// ohf::HttpUrl::Builder
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

// ohf::HttpUrl
HttpUrl::HttpUrl(const std::string &url) {
    std::string tempUrl = url;

    std::string::size_type offset = util::string::first_index_of(tempUrl, "://");
    // scheme
    if (offset == std::string::npos) { // if protocol not exists
        scheme_str = "http";
        port_num = 80;
    } else { // check protocol
        std::string protocol = tempUrl.substr(0, offset);
        port_num = HttpUrl::defaultPort(protocol);
        //if(port_num == -1)
        //    throw Exception(Exception::Code::UNSUPPORTED_PROTOCOL, "Unsupported protocol: " + protocol);
        scheme_str = protocol;
        offset += 3;
        tempUrl.erase(0, offset);
    }

    bool portExists = true;
    offset = tempUrl.find_first_of(':'); // find port pos
    if (offset == std::string::npos) { // if port not found
        offset = tempUrl.find_first_of('/'); // find path pos
        portExists = false;
    }

    // check query
    if (offset == std::string::npos) { // if path not found
        offset = tempUrl.find_first_of('?');
        if (offset != std::string::npos) // but found query, url is invalid
            throw Exception(Exception::Code::INVALID_URI, "Invalid url: " + url);
    }
    // check fragment
    if (offset == std::string::npos) { // if path not found
        offset = tempUrl.find_first_of('#');
        if (offset != std::string::npos) // but found fragment, url is invalid
            throw Exception(Exception::Code::INVALID_URI, "Invalid url: " + url);
    }

    // host
    if (offset == std::string::npos) { // if port and path not found
        host_str = tempUrl;

        int dotsCount = util::string::containsCount(host_str, ".");
        if (dotsCount < 1 || dotsCount > 3)
            throw Exception(Exception::Code::INVALID_HOST, "Invalid host: " + host_str);
    } else {
        host_str = tempUrl.substr(0, offset);

        int dotsCount = util::string::containsCount(host_str, ".");
        if (dotsCount < 1 || dotsCount > 3)
            throw Exception(Exception::Code::INVALID_HOST, "Invalid host: " + host_str);

        tempUrl.erase(0, ++offset);
    }

    // port
    if (portExists) {
        offset = tempUrl.find_first_of('/');
        std::string port = tempUrl.substr(0, offset);
        try {
            port_num = std::stoi(port);
        } catch (std::invalid_argument) {
            throw Exception(Exception::Code::INVALID_PORT, "Invalid port: " + port);
        }
        tempUrl.erase(0, offset);
    }

    bool queryExists = true;
    offset = tempUrl.find_first_of('?'); // find query
    if (offset == std::string::npos) { // if query not found
        offset = tempUrl.find_first_of('#'); // find fragment
        queryExists = false;
    }

    // path
    if (offset != std::string::npos) { // if path found
        std::string path = tempUrl.substr(0, offset);
        pathEndsWithSlash = util::string::endsWith(path, "/");
        pathSegments_vec = util::string::split(path, "/");
        tempUrl.erase(0, ++offset);
    }

    // query
    if (queryExists) {
        offset = tempUrl.find_first_of('#');
        std::vector<std::string> query = util::string::split(tempUrl.substr(0, offset), "&");
        for (const auto &parameter : query) {
            std::vector<std::string> nameValue = util::string::split(parameter, "=");
            if (nameValue.size() == 2)
                queryParameters[nameValue[0]] = HttpUrl::decode(nameValue[1]);
            else if (nameValue.size() == 1)
                queryParameters[nameValue[0]] = "";
            else
                throw Exception(Exception::Code::INVALID_QUERY_PARAMETER, "Invalid query parameter: " + parameter);
        }
        tempUrl.erase(0, ++offset);
    }

    if (offset != 0) // if fragment exists
        fragment_str = tempUrl;
}

HttpUrl::HttpUrl(const char *url) {
    *this = HttpUrl(std::string(url));
}

int HttpUrl::defaultPort(std::string scheme) {
    util::string::toLower(scheme);
    if (scheme == "https")
        return 443;
    if (scheme == "http")
        return 80;
    if (scheme == "ftp")
        return 20;
    if (scheme == "telnet")
        return 23;
    if (scheme == "gopher")
        return 70;
    if (scheme == "wais")
        return 210;
    if (scheme == "irc")
        return 6667;
    if (scheme == "ldap")
        return 389;
    return -1;
}

std::string HttpUrl::encodedFragment() {
    return HttpUrl::encode(fragment_str);
}

std::string HttpUrl::encodedPath() {
    if (pathSegments_vec.empty())
        return std::string();

    std::ostringstream oss;
    for (int i = 0; i < pathSegments_vec.size() - 1; i++) {
        std::string pathSegment = pathSegments_vec[i];
        oss << HttpUrl::encode(pathSegment) << "/";
    }
    oss << HttpUrl::encode(pathSegments_vec[pathSegments_vec.size() - 1]);
    if (pathEndsWithSlash)
        oss << '/';
    return oss.str();
}

std::vector<std::string> HttpUrl::encodedPathSegments() {
    std::vector<std::string> path_segments;
    for (const auto &pathSegment : pathSegments_vec)
        path_segments.push_back(HttpUrl::encode(pathSegment));
    return path_segments;
}

std::string HttpUrl::encodedQuery() {
    if (queryParameters.empty())
        return std::string();

    std::ostringstream oss;
    for (int i = 0; i < queryParameters.size() - 1; i++) {
        auto entry = std::next(queryParameters.begin(), i);
        if (entry->second.empty())
            oss << entry->first << '&';
        else
            oss << entry->first << '=' << HttpUrl::encode(entry->second) << '&';
    }
    auto entry = std::next(queryParameters.begin(), queryParameters.size() - 1);
    if (entry->second.empty())
        oss << entry->first;
    else
        oss << entry->first << '=' << HttpUrl::encode(entry->second);
    return oss.str();
}

bool HttpUrl::operator==(const HttpUrl &url) {
    return this == &url;
}

std::string HttpUrl::fragment() {
    return fragment_str;
}

std::string HttpUrl::host() {
    return host_str;
}

bool HttpUrl::isHttps() {
    return scheme_str == "https";
}

HttpUrl::Builder HttpUrl::newBuilder() {
    HttpUrl::Builder builder;
    builder.pathSegments = pathSegments_vec;
    builder.queryParameters = queryParameters;
    builder.fragment_str = fragment_str;
    builder.host_str = host_str;
    builder.port_num = port_num;
    builder.scheme_str = scheme_str;
    builder.pathEndsWithSlash_bool = pathEndsWithSlash;
    return builder;
}

std::vector<std::string> HttpUrl::pathSegments() {
    return pathSegments_vec;
}

int HttpUrl::pathSize() {
    if (pathSegments_vec.empty())
        return 0;
    std::ostringstream oss;
    for (int i = 0; i < pathSegments_vec.size() - 1; i++) {
        std::string pathSegment = pathSegments_vec[i];
        oss << HttpUrl::encode(pathSegment) << "/";
    }
    oss << HttpUrl::encode(pathSegments_vec[pathSegments_vec.size() - 1]);
    return oss.str().length();
}

int HttpUrl::port() {
    return port_num;
}

std::string HttpUrl::query() {
    if (queryParameters.empty())
        return std::string();

    std::ostringstream oss;
    for (int i = 0; i < queryParameters.size() - 1; i++) {
        auto entry = std::next(queryParameters.begin(), i);
        if (entry->second.empty())
            oss << entry->first << '&';
        else
            oss << entry->first << '=' << entry->second << '&';
    }
    auto entry = std::next(queryParameters.begin(), queryParameters.size() - 1);
    if (entry->second.empty())
        oss << entry->first;
    else
        oss << entry->first << '=' << entry->second;
    return oss.str();
}

std::string HttpUrl::queryParameter(const std::string &name) {
    return queryParameters.find(name) != queryParameters.end() ? queryParameters.at(name) : std::string();
}

std::string HttpUrl::queryParameterName(int index) {
    return std::next(queryParameters.begin(), index)->first;
}

std::vector<std::string> HttpUrl::queryParameterNames() {
    std::vector<std::string> names;
    for (const auto &nameValue : queryParameters)
        names.push_back(nameValue.first);
    return names;
}

std::string HttpUrl::queryParameterValue(int index) {
    return std::next(queryParameters.begin(), index)->second;
}

int HttpUrl::querySize() {
    return encodedQuery().length();
}

std::string HttpUrl::scheme() {
    return scheme_str;
}

std::string HttpUrl::url() {
    std::ostringstream oss;

    oss << scheme_str << "://" << host_str;
    if (port_num != -1 && defaultPort(scheme_str) != -1) // if port specified but it is not default
        oss << ':' << port_num;
    oss << '/' << encodedPath();
    std::string query = encodedQuery();
    if (!query.empty())
        oss << '?' << encodedQuery();
    if (!fragment_str.empty())
        oss << '#' << encodedFragment();

    return oss.str();
}