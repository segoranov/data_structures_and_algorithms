#ifndef ADJACENCY_LIST_GRAPH_H_20200601
#define ADJACENCY_LIST_GRAPH_H_20200601

#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template <typename V>
using Edge = std::pair<V, V>;

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

  /**
   * Adds an edge to the graph if it is not there
   */
  void addEdge(const Edge<V>& edge) {}

  /**
   * Removes an edge from the graph if it is there
   */
  void removeEdge(const Edge<V>& edge) {}

  /**
   * Returns all the vertices in the graph
   */
  std::vector<V> vertices() const {
    std::vector<V> result;
    for (const auto& [vertex, _] : adjList) {
      result.push_back(vertex);
    }

    return result;
  }

  /**
   * Returns the number of vertices in the graph
   */
  std::size_t verticesCount() const { return adjList.size(); }

  /**
   * Returns all vertices y such that there is an edge from the vertex to y
   *
   * @throw std::logic_error if the vertex is not in the graph
   */
  std::vector<V> neighbors(const V& vertex) const {
    if (!contains(vertex)) {
      throw std::logic_error{"Vertex not in the graph."};
    }

    return adjList.find(vertex)->second;
  }

  /**
   * Returns whether there is an edge between v1 and v2
   *
   * @throw std::logic_error if either v1 or v2 are not in the graph
   */
  bool adjacent(const V& v1, const V& v2) const {
    if (!contains(v1) || !contains(v2)) {
      throw std::logic_error{"Vertex not in the graph."};
    }

    const auto v1_adjacents = adjList.find(v1)->second;
    for (const auto& adj : v1_adjacents) {
      if (adj == v2) return true;
    }

    const auto v2_adjacents = adjList.find(v2)->second;
    for (const auto& adj : v2) {
      if (adj == v1) return true;
    }

    return false;
  }

  /**
   * Returns whether or not the graph contains the vertex
   */
  bool contains(const V& vertex) const { return adjList.contains(vertex); }

 private:
  std::unordered_map<V, std::vector<V>> adjList;
};

#endif
