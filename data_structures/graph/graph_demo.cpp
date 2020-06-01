#include <fstream>
#include <iostream>

#include "adjacency_list_graph.h"

int main() {
  GraphAdjList<int> graph;
  graph.addEdge(1, 2);
  graph.addEdge(1, 3);

  graph.addEdge(2, 4);
  graph.addEdge(2, 5);

  graph.addEdge(3, 6);
  graph.addEdge(3, 7);

  graph.addEdge(4, 8);

  std::ofstream ofs{"test_graph.dot"};
  graph.printDOT(ofs);

  return 0;
}
