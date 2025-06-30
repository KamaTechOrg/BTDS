// Tree.hpp
#pragma once
#include <iostream>
#include <memory>
#include <vector>

template <typename T> struct Tree {
  using value_type = T;

  struct Node {
    T data;
    std::vector<std::unique_ptr<Node>> children;
    explicit Node(T val) : data(std::move(val)) {}
  };

  std::unique_ptr<Node> root;

  /* Optional pretty-printer -- same style as BT::print() */
  void print_node(const Node *node, int indent = 0) const {
    if (!node)
      return;
    std::cout << std::string(indent, ' ') << node->data << "\n";
    for (const auto &ch : node->children)
      print_node(ch.get(), indent + 2);
  }
  void print() const { print_node(root.get()); }
};

template <typename T>
void print_tree_node(const typename Tree<T>::Node *node, std::ostream &os,
                     int indent = 0) {
  if (!node)
    return;
  os << std::string(indent, ' ') << node->data << '\n';
  for (const auto &ch : node->children) {
    print_tree_node<T>(ch.get(), os, indent + 2);
  }
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Tree<T> &tree) {
  print_tree_node<T>(tree.root.get(), os);
  return os;
} 