#pragma once
#include "../has_print_method.hpp"
#include <iostream>
#include <memory>

template <typename T> struct DLL {
  using value_type = T;

  struct Node : std::enable_shared_from_this<Node> {
    T data;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
    explicit Node(const T &v) : data(v) {}
    explicit Node(T &&v) : data(std::move(v)) {}
  };

  std::shared_ptr<Node> head;

  void print() const {
    auto cur = head;
    while (cur) {
      if constexpr (has_print_method<decltype(cur->data)>::value)
        cur->data.print();
      else
        std::cout << cur->data;
      cur = cur->next;
      if (cur)
        std::cout << " <-> ";
    }
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const DLL<T>& list)
{
    os << "DLL( ";
    auto cur = list.head;

    while (cur)
    {
        if constexpr (has_print_method<decltype(cur->data)>::value)
            cur->data.print(os);       // forward into the same stream
        else
            os << cur->data;

        cur = cur->next;
        if (cur) os << ", ";
    }
    os << " )";
    return os;
} 