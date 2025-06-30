#pragma once
#include "../has_print_method.hpp"
#include <iostream>
#include <sstream>
#include <map>

template <typename K, typename V>
struct MAP {
    using key_type    = K;
    using mapped_type = V;

    std::map<K,V> items;          // underlying associative container

    void insert(const K& k, const V& v) { items.insert({k,v}); }

    void print(std::ostream& os = std::cout) const {
        os << "{";
        bool first = true;
        for (const auto& [k,v] : items) {
            if (!first) os << ",";
            first = false;

            if constexpr (has_print_method<K>::value) k.print(os); else os << k;
            os << ":";
            if constexpr (has_print_method<V>::value) v.print(os); else os << v;
        }
        os << "}";
    }
};

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const MAP<K,V>& m) { m.print(os); return os; } 