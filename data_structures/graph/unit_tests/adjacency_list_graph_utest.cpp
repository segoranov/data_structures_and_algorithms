#include "adjacency_list_graph.h"
#include "catch.hpp"

TEST_CASE("Construct empty graph") {
  GraphAdjList<int> graph;
  REQUIRE(graph.isEmpty());
}

TEST_CASE("Add and remove 1 vertex to graph") {
  GraphAdjList<int> graph;
  graph.addVertex(1);
  REQUIRE_FALSE(graph.isEmpty());
  REQUIRE(graph.vertices() == std::vector<int>{1});
  REQUIRE(graph.contains(1));
  REQUIRE(graph.neighbors(1).empty());
  REQUIRE(graph.verticesCount() == 1);

  graph.removeVertex(1);
  REQUIRE(graph.isEmpty());
  REQUIRE(graph.vertices().empty());
  REQUIRE(!graph.contains(1));
  REQUIRE_THROWS_AS(graph.neighbors(1).empty(), std::logic_error);
  REQUIRE(graph.verticesCount() == 0);
}

TEST_CASE("Add and remove 1 edge to graph") {}
