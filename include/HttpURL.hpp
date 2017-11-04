//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_HTTPURL_HPP
#define OKHTTPFORK_HTTPURL_HPP

#include <vector>
#include <map>
#include "Config.hpp"

namespace ohf {
    class HttpURL {
    public:
        class Builder {
        public:
            Builder();

            // void addEncodedPathSegment(const std::string &encodedPathSegment);
            // void addEncodedPathSegments(const std::string &encodedPathSegments);
            // void addEncodedQueryParameter(const std::string &encodedName, const std::string &encodedValue);
            // void addPathSegment(const std::string &pathSegment);
            Builder &addPathSegments(const std::string &pathSegments);

            // void addQueryParameter(const std::string &name, const std::string &value);
            HttpURL build();

            // void encodedFragment(const std::string &encodedFragment);
            // void encodedPassword(const std::string &encodedPassword);
            // void encodedPath(const std::string &encodedPath);
            // void encodedQuery(const std::string &encodedQuery);
            // void encodedUsername(const std::string &encodedUsername);
            Builder &fragment(const std::string &fragment);

            Builder &host(const std::string &host);

            Builder &port(Uint16 port);

            Builder &query(const std::string &query);

            // void removeAllEncodedQueryParameters(const std::string &encodedName);
            // void removeAllQueryParameters(const std::string &name);
            Builder &removeQueryParameter(const std::string &name);

            Builder &removePathSegment(Uint32 index);

            Builder &scheme(const std::string &scheme);

            // void setEncodedPathSegment(const int &index, const std::string &encodedPathSegment);
            // void setEncodedQueryParameter(const std::string &encodedName, const std::string &encodedValue);
            Builder &setPathSegment(Uint32 index, std::string pathSegment);

            Builder &setQueryParameter(const std::string &name, const std::string &value);

            Builder &pathEndsWithSlash(bool b);

        private:
            Uint16 mPort;
            std::map<std::string, std::string> mQueryParameters;
            bool mPathEndsWithFlash;
            std::vector<std::string> pathSegments;
            std::string mFragment, mHost, mScheme;

            friend class ohf::HttpURL;
        };

        static std::string encode(const std::string &str);

        static std::string decode(const std::string &str);

        static Uint16 defaultPort(std::string scheme);

        explicit HttpURL(const std::string &tempUrl);

        HttpURL(const char *url);

        std::string encodedFragment() const;

        std::string encodedPath() const;

        std::vector<std::string> encodedPathSegments() const;

        std::string encodedQuery() const;

        std::string fragment() const;

        // static HttpURL get(const URI &uri);
        // static HttpURL get(const URL &url);
        // static HttpURL get(const std::string &url);
        std::string host() const;

        bool isHttps() const;

        Builder newBuilder() const;

        // Builder newBuilder(const std::string &link);
        std::vector<std::string> pathSegments() const;

        Uint32 pathSize() const;

        Uint16 port() const;

        std::string query() const;

        std::string queryParameter(const std::string &name) const;

        std::string queryParameterName(Uint32 index) const;

        std::vector<std::string> queryParameterNames() const;

        std::string queryParameterValue(Uint32 index) const;

        // std::vector<std::string> queryParameterValues(const std::string &name);
        Uint32 querySize() const;

        // std::string redact();
        // HttpURL resolve(const std::string &link);
        std::string scheme() const;

        // std::string topPrivateDomain();
        // URI uri();
        // URL url();
        std::string url() const;

        HttpURL *clone() const;

        std::string toString() const;

        bool operator==(const HttpURL &url);

        friend std::ostream &operator<<(std::ostream &stream, const HttpURL &httpURL);
    private:
        HttpURL(const Builder *builder);
        //HttpURL(const HttpURL *url);

        Uint16 mPort;
        bool pathEndsWithSlash;
        std::vector<std::string> mPathSegments;
        std::map<std::string, std::string> queryParameters;
        std::string mFragment, mHost, mScheme;
    };
}

#endif //OKHTTPFORK_HTTPURL_HPP
