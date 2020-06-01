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
  };

  SECTION("Add and remove 1 vertex to graph") {
    graph.addVertex(1);
    REQUIRE_FALSE(graph.isEmpty());
    REQUIRE(graph.vertices() == std::unordered_set<int>{1});
    REQUIRE(graph.contains(1));
    REQUIRE(graph.neighbors(1).empty());
    REQUIRE(graph.verticesCount() == 1);

    graph.removeVertex(1);

    checkGraphEmptiness();
  }

  SECTION("Add and remove 1 edge to graph") {
    graph.addEdge(1, 2);
    REQUIRE_FALSE(graph.isEmpty());
    REQUIRE(graph.vertices() == std::unordered_set<int>{1, 2});
    REQUIRE(graph.contains(1));
    REQUIRE(graph.contains(2));
    REQUIRE(graph.neighbors(1) == std::vector<int>{2});
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
}
