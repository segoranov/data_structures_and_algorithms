#include "adjacency_list_graph.h"
#include "catch.hpp"

TEST_CASE("Construct empty graph") {
  GraphAdjList<int> graph;
  REQUIRE(graph.isEmpty());
}
