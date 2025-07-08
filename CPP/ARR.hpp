#pragma once
#include "QuotedStream.hpp"
#include "iostream"
#include <vector>

template <typename T> struct ARR {
	using value_type = T;
	std::vector<T> elements;

	T& operator[](size_t i) { return elements[i]; }
	const T& operator[](size_t i) const { return elements[i]; }

};


template<class Stream, typename T>
Stream& operator<<(Stream& os, const ARR<T>& arr) {
	os << "[";
	for (size_t i = 0; i < arr.elements.size(); ++i) {
		os << arr.elements[i];
		if (i + 1 < arr.elements.size())
			os << ",";
	}
	os << "]";
	return os;
}