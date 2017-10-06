//
// Created by Good_Pudge.
//

#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include "../include/HttpURL.hpp"
#include "../util/string.hpp"
#include "../include/Exception.hpp"

namespace ohf {
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

    HttpURL::HttpURL(const std::string &url) :
            pathEndsWithSlash(false) {
        std::string tempUrl = url;

        std::string::size_type offset = util::string::firstIndexOf(tempUrl, "://");
        // scheme
        if (offset == std::string::npos) { // if protocol not exists
            mScheme = "http";
            mPort = 80;
        } else { // check protocol
            std::string protocol = tempUrl.substr(0, offset);
            mPort = HttpURL::defaultPort(protocol);
            mScheme = protocol;
            offset += 3;
            tempUrl.erase(0, offset);
        }

        offset = tempUrl.find_first_of('/');
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

        bool portExists = true;
        offset = tempUrl.find_first_of(':'); // find port pos
        if (offset == std::string::npos) { // if port not found
            offset = tempUrl.find_first_of('/'); // find path pos
            portExists = false;
        }

        // host
        if (offset == std::string::npos) { // if port and path not found
            mHost = tempUrl;
        } else {
            mHost = tempUrl.substr(0, offset);
            tempUrl.erase(0, ++offset);
        }

        // port
        if (portExists) {
            offset = tempUrl.find_first_of('/');
            std::string port = tempUrl.substr(0, offset);
            try {
                mPort = std::stoi(port);
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
            mPathSegments = util::string::split(path, "/");
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

        if (offset != std::string::npos && offset != 0) // if fragment exists
            mFragment = tempUrl;
    }

    HttpURL::HttpURL(const char *url) : HttpURL(std::string(url)) {
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

    std::string HttpURL::encodedFragment() const {
        return HttpURL::encode(mFragment);
    }

    std::string HttpURL::encodedPath() const {
        if (mPathSegments.empty())
            return std::string();

        std::ostringstream oss;
        for (int i = 0; i < mPathSegments.size() - 1; i++) {
            std::string pathSegment = mPathSegments[i];
            oss << HttpURL::encode(pathSegment) << "/";
        }
        oss << HttpURL::encode(mPathSegments[mPathSegments.size() - 1]);
        if (pathEndsWithSlash)
            oss << '/';
        return oss.str();
    }

    std::vector<std::string> HttpURL::encodedPathSegments() const {
        std::vector<std::string> path_segments;
        for (const auto &pathSegment : mPathSegments)
            path_segments.push_back(HttpURL::encode(pathSegment));
        return path_segments;
    }

    std::string HttpURL::encodedQuery() const {
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

    std::string HttpURL::fragment() const {
        return mFragment;
    }

    std::string HttpURL::host() const {
        return mHost;
    }

    bool HttpURL::isHttps() const {
        return mScheme == "https";
    }

    HttpURL::Builder HttpURL::newBuilder() const {
        HttpURL::Builder builder;
        builder.pathSegments = mPathSegments;
        builder.mQueryParameters = queryParameters;
        builder.mFragment = mFragment;
        builder.mHost = mHost;
        builder.mPort = mPort;
        builder.mScheme = mScheme;
        builder.mPathEndsWithFlash = pathEndsWithSlash;
        return builder;
    }

    std::vector<std::string> HttpURL::pathSegments() const {
        return mPathSegments;
    }

    int HttpURL::pathSize() const {
        if (mPathSegments.empty())
            return 0;
        std::ostringstream oss;
        for (int i = 0; i < mPathSegments.size() - 1; i++) {
            std::string pathSegment = mPathSegments[i];
            oss << HttpURL::encode(pathSegment) << "/";
        }
        oss << HttpURL::encode(mPathSegments[mPathSegments.size() - 1]);
        return oss.str().length();
    }

    int HttpURL::port() const {
        return mPort;
    }

    std::string HttpURL::query() const {
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

    std::string HttpURL::queryParameter(const std::string &name) const {
        return queryParameters.find(name) != queryParameters.end() ? queryParameters.at(name) : std::string();
    }

    std::string HttpURL::queryParameterName(int index) const {
        return std::next(queryParameters.begin(), index)->first;
    }

    std::vector<std::string> HttpURL::queryParameterNames() const {
        std::vector<std::string> names;
        for (const auto &nameValue : queryParameters)
            names.push_back(nameValue.first);
        return names;
    }

    std::string HttpURL::queryParameterValue(int index) const {
        return std::next(queryParameters.begin(), index)->second;
    }

    int HttpURL::querySize() const {
        return encodedQuery().length();
    }

    std::string HttpURL::scheme() const {
        return mScheme;
    }

    std::string HttpURL::url() const {
        std::ostringstream oss;

        oss << mScheme << "://" << mHost;
        if (mPort != -1 && defaultPort(mScheme) == -1) // if port specified but it is not default
            oss << ':' << mPort;

        oss << '/';
        std::string path = encodedPath();
        if (!path.empty())
            oss << path;

        std::string query = encodedQuery();
        if (!query.empty())
            oss << '?' << query;

        std::string fragment = encodedFragment();
        if (!fragment.empty())
            oss << '#' << fragment;

        return oss.str();
    }

    std::ostream &operator<<(std::ostream &stream, HttpURL &httpURL) {
        stream << httpURL.url();
        return stream;
    }

    bool HttpURL::operator==(const HttpURL &url) {
        auto ps1 = url.mPathSegments;
        std::sort(ps1.begin(), ps1.end());
        auto ps2 = std::move(this->mPathSegments);
        std::sort(ps2.begin(), ps2.end());

        return url.pathEndsWithSlash == this->pathEndsWithSlash
               && url.mScheme == this->mScheme
               && url.mHost == this->mHost
               && url.mFragment == this->mFragment
               && url.mPort == this->mPort
               && url.queryParameters == this->queryParameters
               && ps1 == ps2;
    }

    HttpURL::HttpURL(const Builder *builder):
            mPort(builder->mPort),
            pathEndsWithSlash(builder->mPathEndsWithFlash),
            mPathSegments(builder->pathSegments),
            queryParameters(builder->mQueryParameters),
            mFragment(builder->mFragment),
            mHost(builder->mHost),
            mScheme(builder->mScheme)
    {}
}