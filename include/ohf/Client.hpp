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
#include "TimeUnit.hpp"
#include "WebSocket.hpp"

namespace ohf {
    class Client {
    public:
        class Builder {
        public:
            Builder() = default;

            ~Builder();

            Client build();

            Builder& addInterceptor(const Interceptor &interceptor);

            Builder& addNetworkInterceptor(const Interceptor &interceptor);

            Builder& authenticator(const Authenticator &authenticator);

            Builder& cache(const Cache &cache);

            Builder& certificatePinner(const CertificatePinner &pinner);

            Builder& connectionPool(const ConnectionPool &pool);

            Builder& connectionSpecs(const std::vector<ConnectionSpec> &specs);

            Builder& connectTimeout(const TimeUnit &timeout);

            Builder& cookieJar(const CookieJar &jar);

            Builder& dispatcher(const Dispatcher &dispatcher);

            Builder& dns(const DNS &dns);

            Builder& followRedirects(bool follow);

            Builder& follorSSLRedirects(bool follow);

            Builder& hostnameVerifier(const HostnameVerifier &verifier);

            std::vector<Interceptor> interceptors();

            std::vector<Interceptor> networkInterceptors();

            Builder& pingInterval(const TimeUnit &interval);

            Builder& protocols(const std::vector<Protocol> &protocols);

            Builder& proxy(const Proxy &proxy);

            Builder& proxyAuthenticator(const Authenticator &authenticator);

            Builder& proxySelector(const Proxy::Selector &selector);

            Builder& readTimeout(const TimeUnit &timeout);

            Builder& retryOnConnectionFailure(bool retry);

            //Builder socketFactory(const SocketFactory &factory);
            //Builder sslSocketFactory(const SSLSocketFactory &factory);
            //Builder sslSocketFactory(const SSLSocketFactory &factory, const X509TrustManager &manager);

            Builder& writeTimeout(const TimeUnit &timeout);

        private:
            friend class ohf::Client;
        };

        Client();

        ~Client();

        Authenticator authenticator();

        Cache cache();

        CertificatePinner certificatePinner();

        ConnectionPool connectionPool();

        std::vector<ConnectionSpec> connectionSpecs();

        CookieJar& cookieJar();

        Dispatcher dispatcher();

        DNS& dns();

        bool followRedirects();

        bool followSSLRedirects();

        HostnameVerifier hostnameVerifier();

        std::vector<Interceptor> interceptors();

        std::vector<Interceptor> networkInterceptors();

        Builder newBuilder();

        std::shared_ptr<Call> newCall(const Request &request);

        std::shared_ptr<WebSocket> newWebSocket(const Request &request, const WebSocket::Listener &listener);

        TimeUnit pingInterval();

        std::vector<Protocol> protocols();

        Proxy proxy();

        Authenticator proxyAuthenticator();

        Proxy::Selector proxySelector();

        TimeUnit connectTimeout();

        TimeUnit readTimeout();

        TimeUnit writeTimeout();

        bool retryOnConnectionFailure();

        // SocketFactory socketFactory();
        // SSLSocketFactory sslSocketFactory();

    private:
        TimeUnit mReadTimeout;
        TimeUnit mWriteTimeout;
        TimeUnit mConnectTimeout;
        bool mFollowRedirects;
        bool mFollowSSLRedirects;

    };
}

#endif //OKHTTPFORK_OKHTTPCLIENT_HPP
