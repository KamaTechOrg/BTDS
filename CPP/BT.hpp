#pragma once
#include "../has_print_method.hpp"
#include <iostream>
#include <memory>
#include <deque>
#include <sstream>
#include <vector>

template <typename T>
struct BT {
    using value_type = T;

    /* ───────────────────────────── Node ────────────────────────────── */
    struct Node {
        T data;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        explicit Node(const T& val)               // copy; no std::move
            : data(val), left(nullptr), right(nullptr) {}
    };

    std::shared_ptr<Node> root;                   // shared ownership

    /** Print to any `ostream` in *BT( … )* format.                      */
    void print(std::ostream& os = std::cout) const {
        auto vals = level_order();
        os << "BT(";
        for (std::size_t i = 0; i < vals.size(); ++i) {
            os << vals[i];
            if (i + 1 < vals.size()) os << ",";
        }
        os << ")";
    }
};

/* global stream-insertion operator – relies on the member `print()`     */
template <typename T>
std::ostream& operator<<(std::ostream& os, const BT<T>& tree) {
    tree.print(os);
    return os;
} 