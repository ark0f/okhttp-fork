//
// Created by Good_Pudge.
//

#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <ohf/HttpURL.hpp>
#include <ohf/Exception.hpp>
#include <ohf/RangeException.hpp>
#include "util/string.hpp"

namespace ohf {
    std::string HttpURL::encode(const std::string &str) {
        std::ostringstream oss;
        oss.fill('0');
        oss << std::hex;
        for (char c : str) {
            if (isalnum((Uint8) c) || c == '-' || c == '_' || c == '.' || c == '~') {
                oss << c;
                continue;
            }

            oss << std::uppercase;
            oss << '%' << std::setw(2) << (Uint32) (Uint8) c;
            oss << std::nouppercase;
        }
        return oss.str();
    }

    std::string HttpURL::decode(const std::string &str) {
        std::ostringstream ss;
        for (std::string::size_type i = 0; i < str.length(); i++) {
            char c = str[i];
            if (c == '%') {
                std::string hex = str.substr(i + 1, 2);
                try {
                    ss << (char) std::stoi(hex, nullptr, 16);
                } catch(const std::invalid_argument&) {
                    throw Exception(Exception::Code::INVALID_URI_HEX_CODE, "Invalid uri hex code:" + hex);
                }
                i += 2;
            } else {
                ss << c;
            }
        }
        return ss.str();
    }

    HttpURL::HttpURL(const std::string &url) : mPathSuffix(false)
    {
        std::string tmpUrl = url;

        std::string::size_type offset = tmpUrl.find("://");
        // scheme
        if (offset == std::string::npos) { // if protocol not exists
            mScheme = "http";
            mPort = 80;
        } else { // check protocol
            std::string protocol = tmpUrl.substr(0, offset);
            mPort = HttpURL::defaultPort(protocol);
            mScheme = protocol;
            offset += 3;
            tmpUrl.erase(0, offset);
        }

        offset = tmpUrl.find_first_of('/');
        // check query
        if (offset == std::string::npos) { // if path not found
            offset = tmpUrl.find_first_of('?');
            if (offset != std::string::npos) // but found query - url is invalid
                throw Exception(Exception::Code::INVALID_URI, "Invalid url: " + url);
        }

        // check fragment
        if (offset == std::string::npos) { // if path not found
            offset = tmpUrl.find_first_of('#');
            if (offset != std::string::npos) // but found fragment - url is invalid
                throw Exception(Exception::Code::INVALID_URI, "Invalid url: " + url);
        }

        bool portExists = true;
        offset = tmpUrl.find_first_of(':'); // search port pos
        if (offset == std::string::npos) { // if port not found
            offset = tmpUrl.find_first_of('/'); // search path pos
            portExists = false;
        }

        // host
        if (offset == std::string::npos) { // if port and path not found
            mHost = tmpUrl;
            return;
        } else {
            mHost = tmpUrl.substr(0, offset);
            tmpUrl.erase(0, ++offset);
        }
        if(mHost.empty()) throw Exception(Exception::Code::HOST_IS_EMPTY, "Host is empty");

        // port
        if (portExists) {
            offset = tmpUrl.find_first_of('/');
            std::string port = tmpUrl.substr(0, offset);
            try {
                mPort = std::stoi(port);
            } catch (std::invalid_argument&) {
                throw Exception(Exception::Code::INVALID_PORT, "Invalid port: " + port);
            }
            tmpUrl.erase(0, offset);
        }

        bool queryExists = true;
        offset = tmpUrl.find_first_of('?'); // search query
        if (offset == std::string::npos) { // if query not found
            offset = tmpUrl.find_first_of('#'); // search fragment
            queryExists = false;
        }

        // path
        std::string path = tmpUrl.substr(0, offset);
        mPathSuffix = util::string::endsWith(path, "/");
        mPath = util::string::split(path, "/");
        if (offset != std::string::npos) {
            tmpUrl.erase(0, ++offset);
        }

        // query
        if (queryExists) {
            offset = tmpUrl.find_first_of('#');
            std::vector<std::string> query = util::string::split(tmpUrl.substr(0, offset), "&");
            for (const auto &parameter : query) {
                std::vector<std::string> nameValue = util::string::split(parameter, "=");
                if (nameValue.size() == 2)
                    mQuery[nameValue[0]] = HttpURL::decode(nameValue[1]);
                else if (nameValue.size() == 1)
                    mQuery[nameValue[0]] = std::string();
                else
                    throw Exception(Exception::Code::INVALID_QUERY_PARAMETER, "Invalid query parameter: " + parameter);
            }
            tmpUrl.erase(0, ++offset);
        }

        if (offset != std::string::npos && offset != 0) // if fragment exists
            mFragment = tmpUrl;
    }

    HttpURL::HttpURL(const char *url) : HttpURL(std::string(url)) {}

    Uint16 HttpURL::defaultPort(std::string scheme) {
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
        return 0;
    }

    std::string HttpURL::encodedFragment() const {
        return HttpURL::encode(mFragment);
    }

    std::string HttpURL::encodedPath() const {
        if (mPath.empty()) return "/";

        std::ostringstream oss;
        oss << '/';
        for (int i = 0; i < mPath.size() - 1; i++) {
            std::string pathSegment = mPath[i];
            oss << HttpURL::encode(pathSegment) << "/";
        }
        oss << HttpURL::encode(mPath[mPath.size() - 1]);
        if (mPathSuffix)
            oss << '/';
        return oss.str();
    }

    std::vector<std::string> HttpURL::encodedPathSegments() const {
        std::vector<std::string> path_segments;
        for (const auto &pathSegment : mPath)
            path_segments.push_back(HttpURL::encode(pathSegment));
        return path_segments;
    }

    std::string HttpURL::encodedQuery() const {
        if (mQuery.empty())
            return std::string();

        std::ostringstream oss;
        for (int i = 0; i < mQuery.size() - 1; i++) {
            auto entry = std::next(mQuery.begin(), i);
            if (entry->second.empty())
                oss << entry->first << '&';
            else
                oss << entry->first << '=' << HttpURL::encode(entry->second) << '&';
        }
        auto entry = std::next(mQuery.begin(), mQuery.size() - 1);
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
        builder.mPath = mPath;
        builder.mQuery = mQuery;
        builder.mFragment = mFragment;
        builder.mHost = mHost;
        builder.mPort = mPort;
        builder.mScheme = mScheme;
        builder.mPathSuffix = mPathSuffix;
        return builder;
    }

    std::vector<std::string> HttpURL::pathSegments() const {
        return mPath;
    }

    Uint32 HttpURL::pathSize() const {
        return encodedPath().size();
    }

    Uint16 HttpURL::port() const {
        return mPort;
    }

    std::map<std::string, std::string> HttpURL::queryMap() {
        return mQuery;
    }

    std::string HttpURL::query() const {
        if (mQuery.empty())
            return std::string();

        std::ostringstream oss;
        for (int i = 0; i < mQuery.size() - 1; i++) {
            auto entry = std::next(mQuery.begin(), i);
            if (entry->second.empty())
                oss << entry->first << '&';
            else
                oss << entry->first << '=' << entry->second << '&';
        }
        auto entry = std::next(mQuery.begin(), mQuery.size() - 1);
        if (entry->second.empty())
            oss << entry->first;
        else
            oss << entry->first << '=' << entry->second;
        return oss.str();
    }

    std::string HttpURL::queryParameter(const std::string &name) const {
        return mQuery.find(name) != mQuery.end() ? mQuery.at(name) : std::string();
    }

    std::string HttpURL::queryParameterName(Uint32 index) const {
        if(index >= mQuery.size())
            throw RangeException(index);
        return std::next(mQuery.begin(), index)->first;
    }

    std::vector<std::string> HttpURL::queryParameterNames() const {
        std::vector<std::string> names;
        for (const auto &nameValue : mQuery)
            names.push_back(nameValue.first);
        return names;
    }

    std::string HttpURL::queryParameterValue(Uint32 index) const {
        if(index >= mQuery.size())
            throw RangeException(index);
        return std::next(mQuery.begin(), index)->second;
    }

    Uint64 HttpURL::querySize() const {
        return encodedQuery().length();
    }

    std::string HttpURL::scheme() const {
        return mScheme;
    }

    std::string HttpURL::url() const {
        std::ostringstream oss;

        if(!mScheme.empty()) oss << mScheme << "://";

        oss << mHost;

        if (mPort != 0 && defaultPort(mScheme) == 0) // if port specified but it is not default
            oss << ':' << mPort;

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

    std::string HttpURL::toString() const {
        return url();
    }

    bool HttpURL::operator ==(const HttpURL &url) const {
        auto ps1 = url.mPath;
        std::sort(ps1.begin(), ps1.end());
        auto ps2 = this->mPath;
        std::sort(ps2.begin(), ps2.end());

        return url.mPathSuffix == this->mPathSuffix
               && url.mScheme == this->mScheme
               && url.mHost == this->mHost
               && url.mFragment == this->mFragment
               && url.mPort == this->mPort
               && url.mQuery == this->mQuery
               && ps1 == ps2;
    }

    std::ostream &operator<<(std::ostream &stream, const HttpURL &httpURL) {
        return stream << httpURL.url();
    }

    HttpURL::HttpURL(const Builder *builder) :
            mPort(builder->mPort),
            mPathSuffix(builder->mPathSuffix),
            mPath(builder->mPath),
            mQuery(builder->mQuery),
            mFragment(builder->mFragment),
            mHost(builder->mHost),
            mScheme(builder->mScheme)
    {}


}
