//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_HTTPURL_HPP
#define OKHTTPFORK_HTTPURL_HPP

#include <vector>
#include <map>

namespace ohf {
    class HttpUrl {
    public:
        class Builder {
        public:
            // void addEncodedPathSegment(const std::string &encodedPathSegment);
            // void addEncodedPathSegments(const std::string &encodedPathSegments);
            // void addEncodedQueryParameter(const std::string &encodedName, const std::string &encodedValue);
            // void addPathSegment(const std::string &pathSegment);
            void addPathSegments(const std::string &pathSegments);

            // void addQueryParameter(const std::string &name, const std::string &value);
            HttpUrl build();

            // void encodedFragment(const std::string &encodedFragment);
            // void encodedPassword(const std::string &encodedPassword);
            // void encodedPath(const std::string &encodedPath);
            // void encodedQuery(const std::string &encodedQuery);
            // void encodedUsername(const std::string &encodedUsername);
            void fragment(const std::string &fragment);

            void host(const std::string &host);

            void port(const int &port);

            void query(const std::string &query);

            // void removeAllEncodedQueryParameters(const std::string &encodedName);
            // void removeAllQueryParameters(const std::string &name);
            void removeQueryParameter(const std::string &name);

            void removePathSegment(const int &index);

            void scheme(const std::string &scheme);

            // void setEncodedPathSegment(const int &index, const std::string &encodedPathSegment);
            // void setEncodedQueryParameter(const std::string &encodedName, const std::string &encodedValue);
            void setPathSegment(const int &index, std::string pathSegment);

            void setQueryParameter(const std::string &name, const std::string &value);

            void pathEndsWithSlash(bool b);

        private:
            std::map<std::string, std::string> queryParameters;
            bool pathEndsWithSlash_bool;
            std::vector<std::string> pathSegments;
            std::string fragment_str;
            std::string host_str;
            int port_num = 80;
            std::string scheme_str = "http";

            friend class HttpUrl;
        };

        static std::string encode(const std::string &str);

        static std::string decode(const std::string &str);

        static int defaultPort(std::string scheme);

        HttpUrl() = default;

        HttpUrl(const std::string &tempUrl);

        HttpUrl(const char *url);

        std::string encodedFragment();

        std::string encodedPath();

        std::vector<std::string> encodedPathSegments();

        std::string encodedQuery();

        bool operator==(const HttpUrl &url); // TODO: Compare values
        std::string fragment();

        // static HttpUrl get(const URI &uri);
        // static HttpUrl get(const URL &url);
        // static HttpUrl get(const std::string &url);
        std::string host();

        bool isHttps();

        Builder newBuilder();

        // Builder newBuilder(const std::string &link);
        std::vector<std::string> pathSegments();

        int pathSize();

        int port();

        std::string query(); // TODO: Handle empty parameter
        std::string queryParameter(const std::string &name);

        std::string queryParameterName(int index);

        std::vector<std::string> queryParameterNames();

        std::string queryParameterValue(int index);

        // std::vector<std::string> queryParameterValues(const std::string &name);
        int querySize();

        // std::string redact();
        // HttpUrl resolve(const std::string &link);
        std::string scheme();

        // std::string topPrivateDomain();
        // URI uri();
        // URL url();
        std::string url();

    private:
        bool pathEndsWithSlash;
        std::vector<std::string> pathSegments_vec;
        std::map<std::string, std::string> queryParameters;
        std::string fragment_str;
        std::string host_str;
        int port_num = -1;
        std::string scheme_str;
    };
}

#endif //OKHTTPFORK_HTTPURL_HPP
