#pragma once
#include "QuotedStream.hpp"
#include <iostream>
#include <memory>

template <typename T> struct DLL {
	using value_type = T;

	struct Node : std::enable_shared_from_this<Node> {
		T data;
		std::shared_ptr<Node> next;
		std::weak_ptr<Node> prev;
		explicit Node(const T& v) : data(v) {}
		explicit Node(T&& v) : data(std::move(v)) {}
	};

	std::shared_ptr<Node> head;

};

template<class Stream, typename T>
Stream& operator<<(Stream& os, const DLL<T>& list) {
	{
		os << "DLL( ";
		auto cur = list.head;

		while (cur)
		{
			os << cur->data;

			cur = cur->next;
			if (cur) os << ", ";
		}
		os << " )";
		return os;
	}
}