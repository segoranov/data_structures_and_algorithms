#ifndef ADJACENCY_LIST_GRAPH_H_20200601
#define ADJACENCY_LIST_GRAPH_H_20200601

#include <unordered_map>
#include <utility>
#include <vector>

template <typename V>
using Edge = std::pair<V, V>;

template <typename V>
class GraphAdjList {
 public:
  GraphAdjList() = default;

  bool isEmpty() const { return adjList.empty(); }

 private:
  std::unordered_map<V, std::vector<V>> adjList;
};

#endif
