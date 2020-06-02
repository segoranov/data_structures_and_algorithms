#include <fstream>
#include <iostream>

#include "adjacency_list_graph.h"
#include "graph_algorithms.h"

GraphAdjList<int> createTestGraph() {
  GraphAdjList<int> graph;
  graph.addEdge(1, 2);
  graph.addEdge(1, 3);

  graph.addEdge(2, 4);
  graph.addEdge(2, 5);

  graph.addEdge(3, 6);
  graph.addEdge(3, 7);

  graph.addEdge(4, 8);

  graph.addEdge(6, 5);
  graph.addEdge(5, 8);
  graph.addEdge(9, 7);
  return graph;
}

template <typename V>
void printPathIfPresent(const std::optional<Path<V>>& path) {
  if (!path) {
    std::cout << "Does not exist.\n";
  } else {
    for (const auto& vertex : *path) {
      std::cout << vertex << ' ';
    }
    std::cout << '\n';
  }
}

void BFS_demo() {
  GraphAdjList<int> graph{createTestGraph()};

  {
    std::cout << "Starting BFS from 1 to 8.\n";
    auto path = GraphAlgorithms::BFS_shortest_path(graph, 1, 8);
    std::cout << "BFS finished. Shortest path from 1 to 8: ";
    printPathIfPresent(path);
  }

  {
    std::cout << "Starting BFS from 1 to 9.\n";
    auto path = GraphAlgorithms::BFS_shortest_path(graph, 1, 9);
    std::cout << "BFS finished. Shortest path from 1 to 9: ";
    printPathIfPresent(path);
  }
}

int main() {
  std::cout << "Creating test graph.\n";
  GraphAdjList<int> graph{createTestGraph()};

  std::ofstream ofs{"test_graph.dot"};
  graph.printDOT(ofs);
  BFS_demo();

  return 0;
}
