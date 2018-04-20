//
// Created by Good_Pudge.
//

#include <ohf/Address.hpp>

namespace ohf {
    Address::Address(const std::string &host,
                     Uint16 port,
                     DNS *dns,
                     HostnameVerifier *hostnameVerifier,
                     const CertificatePinner &certificatePinner,
                     Authenticator *proxyAuthenticator,
                     const Proxy &proxy,
                     const std::vector<Protocol> &protocols,
                     const std::vector<ConnectionSpec> &connectionSpecs,
                     const Proxy::Selector &proxySelector) :
            mUrl(host + std::to_string(port)),
            mDNS(dns),
            mVerifier(hostnameVerifier),
            mPinner(certificatePinner),
            mAuthenticator(proxyAuthenticator),
            mProxy(proxy),
            mProtocols(protocols),
            mSpecs(connectionSpecs),
            mSelector(proxySelector)
    {}

    CertificatePinner Address::certificatePinner() const {
        return mPinner;
    }

    std::vector<ConnectionSpec> Address::connectionSpecs() const {
        return mSpecs;
    }

    std::shared_ptr<DNS> Address::dns() const {
        return mDNS;
    }

    std::shared_ptr<HostnameVerifier> Address::hostnameVerifier() const {
        return mVerifier;
    }

    std::vector<Protocol> Address::protocols() const {
        return mProtocols;
    }

    Proxy Address::proxy() const {
        return mProxy;
    }

    std::shared_ptr<Authenticator> Address::proxyAuthenticator() const {
        return mAuthenticator;
    }

    Proxy::Selector Address::proxySelector() const {
        return mSelector;
    }

    HttpURL Address::url() const {
        return mUrl;
    }

    std::string Address::toString() const { // TODO: Implement it
        return "";
    }

    bool Address::operator ==(const Address &address) const {
        return mUrl == address.mUrl
            && mDNS == address.mDNS
            && mVerifier == address.mVerifier
            && mPinner == address.mPinner
            && mAuthenticator == address.mAuthenticator
            && mProxy == address.mProxy
            && mProtocols == address.mProtocols
            && mSpecs == address.mSpecs
            && mSelector == address.mSelector;
    }

    std::ostream& operator <<(std::ostream &stream, const Address &address) {
        return stream << address.toString();
    }
}
