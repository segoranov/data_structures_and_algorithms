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
    auto pathBetween1And8 = GraphAlgorithms::BFS_shortest_path(graph, 1, 8);
    REQUIRE(pathBetween1And8 == Path<int>{1, 2, 4, 8});
  }

  SECTION(
      "BFS for finding shortest paths between vertices 3 and 8 generates valid "
      "path") {
    auto pathBetween3And8 = GraphAlgorithms::BFS_shortest_path(graph, 3, 8);
    REQUIRE(pathBetween3And8 == Path<int>{3, 6, 5, 8});
  }

  SECTION(
      "BFS  for finding shortest paths between vertices 1 and 9 should fail to "
      "generate a path") {
    REQUIRE(!GraphAlgorithms::BFS_shortest_path(graph, 1, 9));
  }

  SECTION(
      "DFS traversing the whole graph starting from vertice 1 generates valid "
      "traversal") {
    auto dfsTraversalFrom1 = GraphAlgorithms::DFS_traversal(graph, 1);
    REQUIRE(dfsTraversalFrom1 == Traversal<int>{1, 2, 4, 8, 5, 3, 6, 7});
  }

  SECTION(
      "DFS traversing the whole graph starting from vertice 9 generates valid "
      "traversal") {
    auto dfsTraversalFrom9 = GraphAlgorithms::DFS_traversal(graph, 9);
    REQUIRE(dfsTraversalFrom9 == Traversal<int>{9, 7});
  }

  SECTION(
      "DFS traversing the whole graph starting from vertice 2 generates valid "
      "traversal") {
    auto dfsTraversalFrom2 = GraphAlgorithms::DFS_traversal(graph, 2);
    REQUIRE(dfsTraversalFrom2 == Traversal<int>{2, 4, 8, 5});
  }
}
