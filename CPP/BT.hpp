#pragma once
#include "QuotedStream.hpp"
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

	/* ──────────────────────── helpers / printers ───────────────────── */

	template <typename T>
	static uint64_t tree_size(const std::shared_ptr<Node> root)
	{
		if (!root) return 0;
		return 1 + tree_size<T>(root->left) + tree_size<T>(root->right);
	}
};


template<class Stream, typename T>
Stream& operator<<(Stream& os, const BT<T>& tree)
{
    using NodePtr = std::shared_ptr<typename BT<T>::Node>;
    if (!tree.root) { os << "BT()"; return os; }

    /* -- breadth-first queue that keeps nullptr placeholders -- */
    std::deque<NodePtr> q{ tree.root };
    std::vector<std::optional<T>> slots;          // one entry per *slot*

    while (!q.empty()) {
        NodePtr n = q.front(); q.pop_front();
        if (n) {
            slots.emplace_back(n->data);
            /* enqueue *both* children so gaps are preserved            */
            q.push_back(n->left);
            q.push_back(n->right);
        }
        else {
            slots.emplace_back(std::nullopt);
        }
    }

    /* trim dangling nulls at the far right (standard in LeetCode/GfG serialisation) */
    while (!slots.empty() && !slots.back())
        slots.pop_back();

    os << "BT(";
    for (std::size_t i = 0; i < slots.size(); ++i) {
        if (slots[i]) os << *slots[i];           // real node
        /* else leave the position empty to print ",," for a gap */
        if (i + 1 < slots.size()) os << ", ";
    }
    os << ')';
    return os;
}