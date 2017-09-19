//
// Created by Good_Pudge.
//

#include <sstream>
#include <iomanip>
#include <iostream>
#include "../include/HttpURL.hpp"
#include "../util/include/string.hpp"
#include "../include/Exception.hpp"

using namespace ohf;

std::string HttpURL::encode(const std::string &str) {
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

std::string HttpURL::decode(const std::string &str) {
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

HttpURL::HttpURL(const std::string &url) {
    std::string tempUrl = url;

    std::string::size_type offset = util::string::firstIndexOf(tempUrl, "://");
    // scheme
    if (offset == std::string::npos) { // if protocol not exists
        scheme_str = "http";
        port_num = 80;
    } else { // check protocol
        std::string protocol = tempUrl.substr(0, offset);
        port_num = HttpURL::defaultPort(protocol);
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
                queryParameters[nameValue[0]] = HttpURL::decode(nameValue[1]);
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

HttpURL::HttpURL(const char *url) {
    *this = HttpURL(std::string(url));
}

int HttpURL::defaultPort(std::string scheme) {
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

std::string HttpURL::encodedFragment() {
    return HttpURL::encode(fragment_str);
}

std::string HttpURL::encodedPath() {
    if (pathSegments_vec.empty())
        return std::string();

    std::ostringstream oss;
    for (int i = 0; i < pathSegments_vec.size() - 1; i++) {
        std::string pathSegment = pathSegments_vec[i];
        oss << HttpURL::encode(pathSegment) << "/";
    }
    oss << HttpURL::encode(pathSegments_vec[pathSegments_vec.size() - 1]);
    if (pathEndsWithSlash)
        oss << '/';
    return oss.str();
}

std::vector<std::string> HttpURL::encodedPathSegments() {
    std::vector<std::string> path_segments;
    for (const auto &pathSegment : pathSegments_vec)
        path_segments.push_back(HttpURL::encode(pathSegment));
    return path_segments;
}

std::string HttpURL::encodedQuery() {
    if (queryParameters.empty())
        return std::string();

    std::ostringstream oss;
    for (int i = 0; i < queryParameters.size() - 1; i++) {
        auto entry = std::next(queryParameters.begin(), i);
        if (entry->second.empty())
            oss << entry->first << '&';
        else
            oss << entry->first << '=' << HttpURL::encode(entry->second) << '&';
    }
    auto entry = std::next(queryParameters.begin(), queryParameters.size() - 1);
    if (entry->second.empty())
        oss << entry->first;
    else
        oss << entry->first << '=' << HttpURL::encode(entry->second);
    return oss.str();
}

bool HttpURL::operator==(const HttpURL &url) {
    return this == &url;
}

std::string HttpURL::fragment() {
    return fragment_str;
}

std::string HttpURL::host() {
    return host_str;
}

bool HttpURL::isHttps() {
    return scheme_str == "https";
}

HttpURL::Builder HttpURL::newBuilder() {
    HttpURL::Builder builder;
    builder.pathSegments = pathSegments_vec;
    builder.queryParameters = queryParameters;
    builder.fragment_str = fragment_str;
    builder.host_str = host_str;
    builder.port_num = port_num;
    builder.scheme_str = scheme_str;
    builder.pathEndsWithSlash_bool = pathEndsWithSlash;
    return builder;
}

std::vector<std::string> HttpURL::pathSegments() {
    return pathSegments_vec;
}

int HttpURL::pathSize() {
    if (pathSegments_vec.empty())
        return 0;
    std::ostringstream oss;
    for (int i = 0; i < pathSegments_vec.size() - 1; i++) {
        std::string pathSegment = pathSegments_vec[i];
        oss << HttpURL::encode(pathSegment) << "/";
    }
    oss << HttpURL::encode(pathSegments_vec[pathSegments_vec.size() - 1]);
    return oss.str().length();
}

int HttpURL::port() {
    return port_num;
}

std::string HttpURL::query() {
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

std::string HttpURL::queryParameter(const std::string &name) {
    return queryParameters.find(name) != queryParameters.end() ? queryParameters.at(name) : std::string();
}

std::string HttpURL::queryParameterName(int index) {
    return std::next(queryParameters.begin(), index)->first;
}

std::vector<std::string> HttpURL::queryParameterNames() {
    std::vector<std::string> names;
    for (const auto &nameValue : queryParameters)
        names.push_back(nameValue.first);
    return names;
}

std::string HttpURL::queryParameterValue(int index) {
    return std::next(queryParameters.begin(), index)->second;
}

int HttpURL::querySize() {
    return encodedQuery().length();
}

std::string HttpURL::scheme() {
    return scheme_str;
}

std::string HttpURL::url() {
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