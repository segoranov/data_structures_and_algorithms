#ifndef GRAPH_ALGORITHMS_H_20200601
#define GRAPH_ALGORITHMS_H_20200601

#include <deque>
#include <optional>
#include <queue>
#include <stack>
#include <unordered_set>
#include <utility>

#include "adjacency_list_graph.h"

template <typename V>  // V <-> type of vertex in graph
using Path = std::deque<V>;

template <typename V>
using Traversal = std::vector<V>;

class GraphAlgorithms {
 public:
  /**
   * BFS algorithm for graph.
   *
   * Input: graph, starting vertex and goal vertex
   * Output: Shortest path from the starting vertex to the goal vertex if it
   * exists. Otherwise empty optional.
   *
   * @throw std::logic_error if either 'from' or 'to' is not in the graph
   */
  template <typename V>
  static std::optional<Path<V>> BFS_shortest_path(const GraphAdjList<V>& graph,
                                                  const V& from, const V& to) {
    if (!graph.contains(from) || !graph.contains(to)) {
      throw std::logic_error{"Graph does not contain needed vertex."};
    }

    if (from == to) {
      return Path<V>{from};
    }

    // Structures used to restore the path from the end to the beginning
    using VertexWithParent = std::pair<V, V>;
    using History = std::stack<VertexWithParent>;

    History history;

    std::queue<V> toVisit;
    toVisit.push(from);
    std::unordered_set<V> visited;
    visited.insert(from);

    bool reachedGoal = false;
    while (!toVisit.empty() && !reachedGoal) {
      auto currentVertex = toVisit.front();
      toVisit.pop();

      if (currentVertex == to) {
        reachedGoal = true;
      }

      for (const auto& neighbor : graph.neighbors(currentVertex)) {
        if (!visited.contains(neighbor)) {
          toVisit.push(neighbor);
          visited.insert(neighbor);
          history.push(VertexWithParent{neighbor, currentVertex});
        }
      }
    }

    // Now we have to restore the path if there is one

    if (!reachedGoal) {
      return std::nullopt;
    }

    Path<V> result;
    while (!history.empty()) {
      const auto& [vertex, parent] = history.top();

      if (parent == from) {
        // Path is restored.. This is the end of the loop.
        result.push_front(vertex);
        result.push_front(from);
        break;
      }

      history.pop();
      result.push_front(vertex);
      while (!history.empty() && history.top().first != parent) {
        history.pop();
      }
    }

    return result;
  }

  /**
   * DFS algorithm for graph.
   *
   * Input: graph and starting vertex
   * Output: Traversal of the graph (visited vertices in std::vector)
   *
   * @throw std::logic_error if 'start' is not in the graph
   */
  template <typename V>
  static Traversal<V> DFS_traversal(const GraphAdjList<V>& graph,
                                    const V& start) {
    if (!graph.contains(start)) {
      throw std::logic_error{"Graph does not contain needed vertex."};
    }

    Traversal<V> traversal;
    std::unordered_set<V> visited;
    DFS_traversal_rec(graph, start, traversal, visited);
    return traversal;
  }

 private:
  template <typename V>
  static void DFS_traversal_rec(const GraphAdjList<V>& graph,
                                const V& currentVertex, Traversal<V>& traversal,
                                std::unordered_set<V>& visited) {
    visited.insert(currentVertex);
    traversal.push_back(currentVertex);
    for (const auto& neighbor : graph.neighbors(currentVertex)) {
      if (!visited.contains(neighbor)) {
        DFS_traversal_rec(graph, neighbor, traversal, visited);
      }
    }
  }
};

#endif
