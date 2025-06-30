#pragma once
#include "../has_print_method.hpp"
#include "iostream"
#include <vector>

template <typename T> struct ARR {
  using value_type = T;
  std::vector<T> elements;

  T &operator[](size_t i) { return elements[i]; }
  const T &operator[](size_t i) const { return elements[i]; }

  void print(std::ostream& os = std::cout) const {
    os << "[";
    for (size_t i = 0; i < elements.size(); ++i) {
      if constexpr (has_print_method<decltype(elements[i])>::value) {
        elements[i].print(os);
      } else {
        os << elements[i];
      }
      if (i + 1 < elements.size())
        os << ",";
    }
    os << "]";
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const ARR<T> &arr) {
  arr.print(os); // forward to provided stream
  return os;
} 