//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_ADDRESS_HPP
#define OKHTTPFORK_ADDRESS_HPP

#include <ohf/CertificatePinner.hpp>
#include <ohf/ConnectionSpec.hpp>
#include <ohf/DNS.hpp>
#include <ohf/HostnameVerifier.hpp>
#include <ohf/Protocol.hpp>
#include <ohf/Proxy.hpp>
#include <ohf/Authenticator.hpp>
#include <ohf/HttpURL.hpp>
#include <memory>

namespace ohf {
    class Address {
    public:
        Address(const std::string &host,
                Uint16 port,
                DNS *dns,
                HostnameVerifier *hostnameVerifier,
                const CertificatePinner &certificatePinner,
                Authenticator *proxyAuthenticator,
                const Proxy &proxy,
                const std::vector<Protocol> &protocols,
                const std::vector<ConnectionSpec> &connectionSpecs,
                const Proxy::Selector &proxySelector);

        CertificatePinner certificatePinner() const;

        std::vector<ConnectionSpec> connectionSpecs() const;

        std::shared_ptr<DNS> dns() const;

        std::shared_ptr<HostnameVerifier> hostnameVerifier() const;

        std::vector<Protocol> protocols() const;

        Proxy proxy() const;

        std::shared_ptr<Authenticator> proxyAuthenticator() const;

        Proxy::Selector proxySelector() const;

        HttpURL url() const;

        std::string toString() const;

        bool operator ==(const Address &address) const;

        friend std::ostream& operator <<(std::ostream &stream, const Address &address);

    private:
        HttpURL mUrl;
        std::shared_ptr<DNS> mDNS;
        std::shared_ptr<HostnameVerifier> mVerifier;
        CertificatePinner mPinner;
        std::shared_ptr<Authenticator> mAuthenticator;
        Proxy mProxy;
        std::vector<Protocol> mProtocols;
        std::vector<ConnectionSpec> mSpecs;
        Proxy::Selector mSelector;
    };
}

#endif //OKHTTPFORK_ADDRESS_HPP
