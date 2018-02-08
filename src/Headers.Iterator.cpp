//
// Created by Good_Pudge.
//

#include <ohf/Headers.hpp>
#include <iostream>

namespace ohf {
    Headers::Iterator::Iterator(Uint32 index, const Headers *headers) :
            index(index),
            headers(headers)
    {
        swapPair();
    }

    void Headers::Iterator::swapPair() {
        if(headers != nullptr && 0 <= index < headers->size()) {
            Pair &&valueType = headers->pair(index);
            type.swap(valueType);
            outOfRange = false;
        } else {
            outOfRange = true;
        }
    }

    bool Headers::Iterator::isOutOfRange() const {
        return outOfRange;
    }

    // operator *
    const Headers::Pair& Headers::Iterator::operator *() const {
        return type;
    }

    const Headers::Pair& Headers::Iterator::operator *() {
        return type;
    }

    // operator ->
    const Headers::Pair* Headers::Iterator::operator ->() const {
        return &type;
    }

    const Headers::Pair* Headers::Iterator::operator ->() {
        return &type;
    }

    // operator ++
    const Headers::Iterator Headers::Iterator::operator ++(Int32) const {
        return {index + 1, headers};
    }

    const Headers::Iterator& Headers::Iterator::operator ++() {
        index++;

        swapPair();

        return *this;
    }

    // operator --
    const Headers::Iterator Headers::Iterator::operator --(Int32) const {
        return {index - 1, headers};
    }

    const Headers::Iterator& Headers::Iterator::operator --() {
        index--;

        swapPair();

        return *this;
    }

    // operator +
    const Headers::Iterator Headers::Iterator::operator +(Uint32 index) const {
        return {this->index + index, headers};
    }

    // operator -
    const Headers::Iterator Headers::Iterator::operator -(Uint32 index) const {
        return {this->index - index, headers};
    }

    // operator +=
    const Headers::Iterator& Headers::Iterator::operator +=(Uint32 index) {
        this->index += index;

        swapPair();

        return *this;
    }

    // operator -=
    const Headers::Iterator& Headers::Iterator::operator -=(Uint32 index) {
        this->index -= index;

        swapPair();

        return *this;
    }

    // operator ==
    bool Headers::Iterator::operator ==(const Iterator &right) const {
        return (type == right.type) && (index == right.index);
    }

    // operator !=
    bool Headers::Iterator::operator !=(const Iterator &right) const {
        return (type != right.type) && (index != right.index);
    }
}
