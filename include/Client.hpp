//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_OKHTTPCLIENT_HPP
#define OKHTTPFORK_OKHTTPCLIENT_HPP

#include "Call.hpp"
#include "Authenticator.hpp"
#include "Cache.hpp"
#include "CertificatePinner.hpp"
#include "ConnectionPool.hpp"
#include "ConnectionSpec.hpp"
#include "CookieJar.hpp"
#include "Dispatcher.hpp"
#include "DNS.hpp"
#include "HostnameVerifier.hpp"
#include "Interceptor.hpp"
#include "Protocol.hpp"
#include "Proxy.hpp"
#include "ProxySelector.hpp"

namespace ohf {
    class Client {
    public:
        class Builder {
        public:
            Builder addInterceptor(const Interceptor &interceptor);

            Builder addNetworkInterceptor(const Interceptor &interceptor);

            Builder authenticator(const Authenticator &authenticator);

            Client build();

            Builder cache(const Cache &cache);

            Builder certificatePinner(const CertificatePinner &pinner);

            Builder connectionPool(const ConnectionPool &pool);

            Builder connectionSpecs(const std::vector<ConnectionSpec> &specs);

            Builder connectTimeout(time_t timeout);

            Builder cookieJar(const CookieJar &jar);

            Builder dispatcher(const Dispatcher &dispatcher);

            Builder dns(const DNS &dns);

            Builder followRedirects(bool follorRedirects);

            Builder follorSslRedirects(bool followProtocolRedirects);

            Builder hostnameVerifier(const HostnameVerifier &verifier);

            std::vector<Interceptor> &interceptors();

            std::vector<Interceptor> &networkInterceptors();

            Builder pingInterval(time_t interval);

            Builder protocols(const std::vector<Protocol> &protocols);

            Builder proxy(const Proxy &proxy);

            Builder proxyAuthenticator(const Authenticator &authenticator);

            Builder proxySelector(const ProxySelector &selector);

            Builder readTimeout(time_t timeout);

            Builder retryOnConnectionFailure(bool retry);

            //Builder socketFactory(const SocketFactory &factory);
            //Builder sslSocketFactory(const SSLSocketFactory &factory);
            //Builder sslSocketFactory(const SSLSocketFactory &factory, const X509TrustManager &manager);
            Builder writeTimeout(time_t timeout);
        };

        Authenticator authenticator();

        Cache cache();

        CertificatePinner certificatePinner();

        ConnectionPool connectionPool();

        std::vector<ConnectionSpec> connectionSpecs();

        int connectTimeoutMillis();

        CookieJar cookieJar();

        Dispatcher dispatcher();

        DNS dns();

        bool followRedirects();

        bool followSslRedirects();

        HostnameVerifier hostnameVerifier();

        std::vector<Interceptor> interceptors();

        std::vector<Interceptor> networkInterceptors();

        Builder newBuilder();

        void newCall(const Call &call);

        // WebSocket newWebSocket(const Request &request, const WebSocketListener &listener);
        int pingIntervalMillis();

        std::vector<Protocol> protocols();

        Proxy proxy();

        Authenticator proxyAuthenticator();

        ProxySelector proxySelector();

        int readTimeoutMillis();

        bool retryOnConnectionFailure();

        // SocketFactory socketFactory();
        // SSLSocketFactory sslSocketFactory();
        int writeTimeoutMillis();
    };
}

#endif //OKHTTPFORK_OKHTTPCLIENT_HPP
