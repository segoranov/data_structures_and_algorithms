#include "catch.hpp"
#include "graph_algorithms.h"

TEST_CASE("Test various algorithms on same test graph") {
  // generate test graph
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

  SECTION(
      "BFS for finding shortest paths between vertices 1 and 8 generates valid "
      "path") {
    auto pathBetween1And8 = BFS_shortest_path(graph, 1, 8);
    REQUIRE(pathBetween1And8 == Path<int>{1, 2, 4, 8});
  }

  SECTION(
      "BFS for finding shortest paths between vertices 3 and 8 generates valid "
      "path") {
    auto pathBetween1And8 = BFS_shortest_path(graph, 3, 8);
    REQUIRE(pathBetween1And8 == Path<int>{3, 6, 5, 8});
  }

  SECTION(
      "BFS  for finding shortest paths between vertices 1 and 9 should fail to "
      "generate a path") {
    REQUIRE(!BFS_shortest_path(graph, 1, 9));
  }
}
