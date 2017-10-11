//
// Created by Good_Pudge.
//

#include "../include/MultipartBody.hpp"
#include <chrono>
#include <random>

namespace ohf {
    MultipartBody::Builder::Builder() {
        long long int time = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 mt(time);
        std::uniform_int_distribution<int> random(0, 25);
        for (int i = 0; i < 10; i++)
            mBoundary.push_back('a' + random(mt));
        mBoundary += std::to_string(time);
        for (int i = 0; i < 10; i++)
            mBoundary.push_back('A' + random(mt));
    }

    MultipartBody::Builder::Builder(const std::string &boundary) :
            mBoundary(boundary) {}

    MultipartBody::Builder &MultipartBody::Builder::addFormDataPart(const std::string &name, const std::string &value) {
        mParts.emplace_back(name, value);
        return *this;
    }

    MultipartBody::Builder &MultipartBody::Builder::addFormDataPart(
            const std::string &name,
            const std::string &filename,
            const RequestBody &body) {
        mParts.emplace_back(name, filename, body);
        return *this;
    }

    MultipartBody::Builder &MultipartBody::Builder::addPart(const Headers &headers, const RequestBody &body) {
        mParts.emplace_back(headers, body);
        return *this;
    }

    MultipartBody::Builder &MultipartBody::Builder::addPart(const Part &part) {
        mParts.push_back(part);
        return *this;
    }

    MultipartBody::Builder &MultipartBody::Builder::addPart(const RequestBody &body) {
        mParts.emplace_back(body);
        return *this;
    }

    MultipartBody::Builder &MultipartBody::Builder::setType(const MediaType &type) {
        mType = type;
        return *this;
    }

    MultipartBody MultipartBody::Builder::build() {
        return {this};
    }
}