#ifndef ADJACENCY_LIST_GRAPH_H_20200601
#define ADJACENCY_LIST_GRAPH_H_20200601

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

/// The class represents directed graph without weights using adjacency list
/// representation
template <typename V>
class GraphAdjList {
 public:
  GraphAdjList() = default;

  /**
   * Returns whether the graph is empty or not
   *
   * O(1)
   */
  bool isEmpty() const { return adjList.empty(); }

  /**
   * Adds a vertex to the graph if it is not there
   */
  void addVertex(const V& vertex) { adjList.insert({vertex, {}}); }

  /**
   * Removes a vertex from the graph if it is there
   */
  void removeVertex(const V& vertex) {
    adjList.erase(vertex);

    for (auto& [_, adjacentToVertex] : adjList) {
      adjacentToVertex.erase(
          std::remove_if(adjacentToVertex.begin(), adjacentToVertex.end(),
                         [&](const V& v) { return v == vertex; }),
          adjacentToVertex.end());
    }
  }

  void addEdge(const V& from, const V& to) {
    if (!contains(from)) {  // 'from' is in the graph
      adjList.insert({from, std::vector{to}});
      if (!contains(to)) {
        adjList.insert({to, {}});
      }
    } else {  // 'from' is not in the graph
      // check to see if there is already such an edge
      std::vector<V>& fromAdjacents = adjList.find(from)->second;
      for (const auto& adj : fromAdjacents) {
        if (adj == to) return;
      }

      fromAdjacents.push_back(to);
    }
  }

  /**
   * Removes an edge from the graph if it is there
   */
  void removeEdge(const V& from, const V& to) {
    if (!contains(from) || !contains(to)) {
      return;
    }

    auto& fromAdjacents = adjList.find(from)->second;
    fromAdjacents.erase(
        std::remove_if(fromAdjacents.begin(), fromAdjacents.end(),
                       [&](const V& v) { return v == to; }),
        fromAdjacents.end());
  }

  /**
   * Returns all the vertices in the graph
   */
  std::unordered_set<V> vertices() const {
    std::unordered_set<V> result;
    for (const auto& [vertex, _] : adjList) {
      result.insert(vertex);
    }

    return result;
  }

  /**
   * Returns the number of vertices in the graph
   */
  std::size_t verticesCount() const { return adjList.size(); }

  /**
   * Returns the number of edges in the graph
   */
  std::size_t edgesCount() const {
    std::size_t result = 0;
    for (const auto& [_, adjacents] : adjList) {
      result += adjacents.size();
    }

    return result;
  }

  /**
   * Returns all vertices y such that there is an edge from the vertex to y
   *
   * @throw std::logic_error if the vertex is not in the graph
   */
  std::unordered_set<V> neighbors(const V& vertex) const {
    if (!contains(vertex)) {
      throw std::logic_error{"Vertex not in the graph."};
    }

    std::unordered_set<V> result;
    const auto& adjacents = adjList.find(vertex)->second;
    for (const auto& adj : adjacents) {
      result.insert(adj);
    }

    return result;
  }

  /**
   * Returns whether there is an edge from 'from' to 'to'
   *
   * @throw std::logic_error if either 'from' or 'to' are not in the graph
   */
  bool hasEdge(const V& from, const V& to) const {
    if (!contains(from) || !contains(to)) {
      throw std::logic_error{"Vertex not in the graph."};
    }

    const auto& fromAdjacents = adjList.find(from)->second;
    for (const auto& adj : fromAdjacents) {
      if (adj == to) return true;
    }

    return false;
  }

  /**
   * Returns whether or not the graph contains the vertex
   */
  bool contains(const V& vertex) const { return adjList.contains(vertex); }

  /**
   * Makes the graph empty - removes all vertices and edges
   */
  void clear() { adjList.clear(); }

  /**
   * Prints the graph in DOT format
   */
  void printDOT(std::ostream& os = std::cout) {
    os << "digraph g {\n";
    for (V const& v : vertices()) {
      os << v << ";\n";
      for (auto const& neighbor : neighbors(v))
        os << v << " -> " << neighbor << ";\n";
    }
    os << "}\n";
  }

 private:
  std::unordered_map<V, std::vector<V>> adjList;
};

#endif
