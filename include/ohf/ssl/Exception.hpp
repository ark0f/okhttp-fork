//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_SSL_EXCEPTION_HPP
#define OKHTTPFORK_SSL_EXCEPTION_HPP

#include <ohf/Exception.hpp>
#include <ohf/Config.hpp>

namespace ohf {
    namespace ssl {
        class Exception : public ohf::Exception {
        public:
            explicit Exception(const Code &code);

            Exception(const Code &code, const SSL &ssl, Int32 retCode);

            Int32 sslCode() const noexcept;

            std::string sslMessage() const noexcept;

        private:
            Int32 ssl_code;
            std::string ssl_message;
        };
    }
}

#endif //OKHTTPFORK_SSL_EXCEPTION_HPP
