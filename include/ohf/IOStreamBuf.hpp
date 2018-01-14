//
// Created by Good_Pudge.
//

#ifndef PROJECT_IOSTREAMBUF_HPP
#define PROJECT_IOSTREAMBUF_HPP

#include <streambuf>
#include <vector>
#include <ohf/Config.hpp>

namespace ohf {
    class IOStreamBuf : public std::streambuf {
    protected:
        IOStreamBuf(Int32 write, Int32 read);

        Int32 sync() override;

        Int32 overflow(Int32 c) override;

        Int32 underflow() override;

        virtual Int32 write(const char *data, Int32 length) = 0;

        virtual Int32 read(char *data, Int32 length) = 0;
    private:
        std::vector<Int8> wb; // writing buffer
        std::vector<Int8> rb; // reading buffer
    };
}

#endif //PROJECT_IOSTREAMBUF_HPP
