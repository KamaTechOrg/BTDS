#pragma once
#include "QuotedStream.hpp"
#include <iostream>
#include <set>
#include <iterator>

template <typename T>
struct SET {
    using value_type = T;
    std::set<T> items;                         // underlying ordered set

    void insert(const T& v) {
        items.insert(v);
    }

};


template<class Stream, typename T>
Stream& operator<<(Stream& os, const SET<T>& set) {
    os << "{";
    for (auto it = set.items.cbegin(); it != set.items.cend(); ++it) {
        os << *it;
        if (std::next(it) != set.items.cend()) os << ",";
    }
    return os << "}";
}
