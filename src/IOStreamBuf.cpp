//
// Created by Good_Pudge.
//

#include <ohf/IOStreamBuf.hpp>

namespace ohf{
    IOStreamBuf::IOStreamBuf(Int32 write, Int32 read) :
            wb((Uint32) write),
            rb((Uint32) read)
    {
        // write
        Int8 *buf = wb.data();
        setp(buf, buf + (wb.size() - 1));

        // read
        Int8 *start = rb.data();
        Int8 *end = start + rb.size();
        setg(start, end, end);
    };

    Int32 IOStreamBuf::sync() {
        if(pptr() && pptr() > pbase()) {
            Int32 sz = Int32(pptr() - pbase());

            if (write(pbase(), sz) == sz) {
                pbump(-sz);
                return 0;
            }
        }

        return -1;
    }

    Int32 IOStreamBuf::overflow(Int32 c) {
        if(c != traits_type::eof()) {
            *pptr() = (Int8) c;
            pbump(1);

            if(sync() == -1) return traits_type::eof();
        }

        return c;
    }

    Int32 IOStreamBuf::underflow() {
        if (gptr() < egptr()) {
            return *gptr();
        }

        Int32 got = read(eback(), (Int32) rb.size());
        setg(eback(), eback(), eback() + got);

        return got == 0 ? traits_type::eof() : *gptr();
    }
}
