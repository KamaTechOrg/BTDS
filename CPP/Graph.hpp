// Graph.hpp
#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename T> struct Graph {
	using value_type = T;

	bool directed = true;                      // default -> directed
	std::vector<T> vertices;                   // keeps labels in insertion order
	std::vector<std::vector<std::size_t>> adj; // adjacency list (index based)

	/* --------------------------------------------------------------------- */
	void add_edge(const T& u, const T& v) {
		auto idx = [this](const T& x) {
			auto it = std::find(vertices.begin(), vertices.end(), x);
			if (it == vertices.end()) {
				vertices.push_back(x);
				adj.emplace_back();
				return vertices.size() - 1;
			}
			return std::size_t(it - vertices.begin());
		};

		std::size_t ui = idx(u), vi = idx(v);
		adj[ui].push_back(vi);
		if (!directed)
			adj[vi].push_back(ui);
	}
};


template<class Stream, typename T>
Stream& operator<<(Stream& os, const Graph<T>& arr) {
	for (std::size_t i = 0; i < g.vertices.size(); ++i) {
		os << g.vertices[i] << " -> ";
		for (auto j : g.adj[i]) {
			os << g.vertices[j] << ' ';
		}
		os << '\n';
	}
	return os;
}