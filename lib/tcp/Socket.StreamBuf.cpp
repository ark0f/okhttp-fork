//
// Created by Good_Pudge.
//

#include <ohf/tcp/Socket.hpp>

namespace ohf {
    namespace tcp {
        Socket::StreamBuf::StreamBuf(const IO &io, tcp::Socket *socket) :
                socket(socket),
                rb(io.reading),
                wb(io.writing)
        {
            // read
            char_type *start = rb.data();
            char_type *end = start + rb.size();
            setg(start, end, end);

            // write
            char_type *buf = wb.data();
            setp(buf, buf + (wb.size() - 1));

        };

        int Socket::StreamBuf::overflow(int c) {
            if(c != traits_type::eof()) {
                *pptr() = c;
                pbump(1);

                if(sync() == -1) return traits_type::eof();
            }

            return c;
        }

        int Socket::StreamBuf::sync() {
            if(pptr() && pptr() > pbase()) {
                Int32 sz = Int32(pptr() - pbase());

                if (socket->send(pbase(), sz) == sz) {
                    pbump(-sz);
                    return 0;
                }
            }

            return -1;
        }

        int Socket::StreamBuf::underflow() {
            if (gptr() < egptr()) {
                return *gptr();
            }

            Int32 received = socket->receive(eback(), rb.size());
            setg(eback(), eback(), eback() + received);

            return received == 0 ? traits_type::eof() : *gptr();
        }
    }
}