//
// Created by Good_Pudge.
//

#include <ohf/ResponseBody.hpp>

namespace ohf {
    ResponseBody::StreamBuf::StreamBuf(Int32 write, Int32 read) : IOStreamBuf(write, read) {}

    void ResponseBody::StreamBuf::vector(const std::vector<Int8> &vector) {
        mVector = vector;
    }

    Int32 ResponseBody::StreamBuf::write(const char *data, Int32 length) {
        mVector.insert(mVector.end(), data, data + length);
        return length;
    }

    Int32 ResponseBody::StreamBuf::read(char *data, Int32 length) {
        Int32 retlen;
        std::vector<Int8>::iterator begin = mVector.begin();
        std::vector<Int8>::iterator end;

        if(length > mVector.size()) {
            retlen = (Int32) mVector.size();
            end = mVector.end();
        } else {
            retlen = length;
            end = mVector.begin() + length;
        }

        mVector.erase(begin, end);
        std::copy(begin, end, data);
        return retlen;
    }
}
