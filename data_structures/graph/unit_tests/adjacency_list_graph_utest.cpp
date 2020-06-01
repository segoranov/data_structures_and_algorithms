#include "adjacency_list_graph.h"
#include "catch.hpp"

TEST_CASE("Graph adds vertices and edges properly") {
  GraphAdjList<int> graph;
  REQUIRE(graph.isEmpty());

  auto checkGraphEmptiness = [&graph] {
    REQUIRE(graph.isEmpty());
    REQUIRE(graph.vertices().empty());
    REQUIRE(!graph.contains(1));
    REQUIRE_THROWS_AS(graph.neighbors(1).empty(), std::logic_error);
    REQUIRE(graph.verticesCount() == 0);
    REQUIRE(graph.edgesCount() == 0);
  };

  SECTION("Add and remove 1 vertex to graph") {
    graph.addVertex(1);
    REQUIRE_FALSE(graph.isEmpty());
    REQUIRE(graph.vertices() == std::set<int>{1});
    REQUIRE(graph.contains(1));
    REQUIRE(graph.neighbors(1).empty());
    REQUIRE(graph.verticesCount() == 1);

    graph.removeVertex(1);

    checkGraphEmptiness();
  }

  SECTION("Add and remove 1 edge to graph") {
    graph.addEdge(1, 2);
    REQUIRE_FALSE(graph.isEmpty());
    REQUIRE(graph.vertices() == std::set<int>{1, 2});
    REQUIRE(graph.contains(1));
    REQUIRE(graph.contains(2));
    REQUIRE(graph.neighbors(1) == std::set<int>{2});
    REQUIRE(graph.neighbors(2).empty());
    REQUIRE(graph.verticesCount() == 2);
    REQUIRE(graph.hasEdge(1, 2));
    REQUIRE_FALSE(graph.hasEdge(2, 1));
    REQUIRE(graph.edgesCount() == 1);

    SECTION("Remove the edge with removeEdge method") {
      graph.removeEdge(1, 2);
      REQUIRE(graph.edgesCount() == 0);
      REQUIRE(graph.verticesCount() == 2);
    }

    SECTION("Remove the edge by removing vertices with removeVertex method") {
      graph.removeVertex(1);
      REQUIRE(graph.edgesCount() == 0);
      REQUIRE(graph.verticesCount() == 1);
      graph.removeVertex(2);
      checkGraphEmptiness();
    }
  }

  SECTION("Add and remove many vertices from graph") {
    for (int i = 0; i < 1000; i++) {
      graph.addVertex(i);
    }

    REQUIRE(graph.edgesCount() == 0);
    REQUIRE(graph.verticesCount() == 1000);

    for (int i = 0; i < 1000; i++) {
      REQUIRE(graph.contains(i));
    }

    for (int i = 999; i >= 0; i--) {
      REQUIRE(graph.verticesCount() == i + 1);
      graph.removeVertex(i);
    }

    checkGraphEmptiness();
  }

  SECTION("Add and remove many edges from graph") {
    // make a complete graph - every pair of vertices connected by an edge
    for (int i = 0; i < 250; i++) {
      for (int j = 0; j < 250; j++) {
        graph.addEdge(i, j);
        graph.addEdge(j, i);
      }
    }

    REQUIRE(graph.verticesCount() == 250);

    std::size_t expectedEdgesCount = 250 * 250;
    REQUIRE(graph.edgesCount() == expectedEdgesCount);

    for (int i = 0; i < 250; i++) {
      for (int j = 0; j < 250; j++) {
        REQUIRE(graph.hasEdge(i, j));
        REQUIRE(graph.hasEdge(j, i));
      }
    }

    for (int i = 0; i < 250; i++) {
      auto currentNeighbors = graph.neighbors(i);
      for (int j = 0; j < 250; j++) {
        REQUIRE(currentNeighbors.contains(j));
      }
    }

    // remove the edges
    for (int i = 0; i < 250; i++) {
      for (int j = 0; j < 250; j++) {
        REQUIRE(graph.edgesCount() == expectedEdgesCount);
        graph.removeEdge(i, j);
        --expectedEdgesCount;
      }
    }

    REQUIRE(graph.verticesCount() == 250);

    graph.clear();
    checkGraphEmptiness();
  }
}
