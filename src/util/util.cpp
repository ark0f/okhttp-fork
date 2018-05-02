//
// Created by Good_Pudge.
//

#include "util.hpp"
#include <ohf/Exception.hpp>
#include <sstream>
#include <iomanip>

namespace util {
    std::vector<ohf::Int8> readStream(std::istream &stream) {
        std::vector<ohf::Int8> buffer;
        int c;
        while ((c = stream.get()) != EOF)
            buffer.push_back((char) c);
        if (stream.bad())
            throw ohf::Exception(ohf::Exception::Code::FAILED_TO_READ_STREAM, "Failed to read stream: ");
        return buffer;
    }

    std::time_t parseDate(const std::string &what, const std::string &format) {
        std::tm t{};

        std::istringstream iss(what);
        iss >> std::get_time(&t, format.c_str());

        if(iss.fail()) {
            throw ohf::Exception(ohf::Exception::Code::FAILED_TO_PARSE_TIME,
                                 "Failed to parse time: data: " + what + "; format: " + format);
        }

        std::time_t current = std::time(nullptr);
        std::time_t gmt   = std::mktime(std::gmtime(&current));
        std::time_t local = std::mktime(std::localtime(&current));
        std::time_t difference = gmt - local;

        return std::mktime(&t) - difference;
    }
}