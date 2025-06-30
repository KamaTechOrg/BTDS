#pragma once
#include "../has_print_method.hpp"
#include <iostream>
#include <memory>

template <typename T> struct LL {
  using value_type = T;

  /*----------------------------------  node  --------------------------------*/
  struct Node : std::enable_shared_from_this<Node> {
    T data;
    std::shared_ptr<Node> next; // shared ownership

    explicit Node(const T &v) : data(v) {}
    explicit Node(T &&v) : data(std::move(v)) {}
  };

  /*--------------------------------  members  -------------------------------*/
  std::shared_ptr<Node> head;

  LL() = default;

  /* deep-copy constructor / assignment */
  LL(const LL &other) {
    if (!other.head)
      return;
    head = std::make_shared<Node>(other.head->data);
    auto src = other.head->next;
    auto dst = head;
    while (src) {
      dst->next = std::make_shared<Node>(src->data);
      dst = dst->next;
      src = src->next;
    }
  }
  
  LL &operator=(const LL &other) {
    if (this != &other)
      LL(other).swap(*this);
    return *this;
  }

  /* shallow moves (just copy the shared_ptr) */
  LL(LL &&) noexcept = default;
  LL &operator=(LL &&) noexcept = default;

  /*---------------------------------  utils  --------------------------------*/
  void swap(LL &other) noexcept { head.swap(other.head); }

  void print() const {
    auto cur = head; // shared_ptr<Node>
    while (cur) {
      if constexpr (has_print_method<decltype(cur->data)>::value)
        cur->data.print(); // custom DS prints itself
      else
        std::cout << cur->data; // POD types

      cur = cur->next; // advance
      if (cur)
        std::cout << " -> ";
    }
  }
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const LL<T>& list)
{
    os << "LL( ";
    auto cur = list.head;
    while (cur)
    {
        if constexpr (has_print_method<decltype(cur->data)>::value)
            cur->data.print(os);          // forwards into the same stream
        else
            os << cur->data;

        cur = cur->next;
        if (cur) os << ", ";
    }
    os << " )";
    return os;
} 