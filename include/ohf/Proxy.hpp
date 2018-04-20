//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_PROXY_HPP
#define OKHTTPFORK_PROXY_HPP

namespace ohf {
    class Proxy {
    public:
        class Selector {
        public:

            bool operator ==(const Selector &selector) const;
        };

        bool operator ==(const Proxy &proxy) const;
    };
}

#endif //OKHTTPFORK_PROXY_HPP
