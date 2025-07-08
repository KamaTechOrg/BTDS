#pragma once
#include "QuotedStream.hpp"
#include <iostream>
#include <sstream>
#include <map>

template <typename K, typename V>
struct MAP {
    using key_type    = K;
    using mapped_type = V;

    std::map<K,V> items;          // underlying associative container

    void insert(const K& k, const V& v) { items.insert({k,v}); }

};

template<class Stream, typename K, typename V>
Stream& operator<<(Stream& os, const MAP<K, V>& map) {
    os << "{";
    bool first = true;
    for (const auto& [k, v] : map.items) {
        if (!first) os << ",";
        first = false;

        os << k;
        os << ":";
        os << v;
    }
    return os << "}";
}
