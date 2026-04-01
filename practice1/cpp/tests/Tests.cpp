#include "Tests.h"
#include "../src/domain/ADTDirectedGraph.h"

#include <assert.h>
#include <iostream>

void testInit()
{
    ADTDirectedGraph graph = ADTDirectedGraph{};
    assert(graph.nbVertices() == 0);
    std::cout << "testInit passed" << std::endl;
}

void testAddVertex()
{
    ADTDirectedGraph graph = ADTDirectedGraph{};

    assert(graph.addVertex(3) == true);
    assert(graph.addVertex(3) == false);
    assert(graph.addVertex(3) == false);
    assert(graph.addVertex(1) == true);
    assert(graph.addVertex(2) == true);
    assert(graph.addVertex(3) == false);
    assert(graph.addVertex(0) == true);

    std::cout << "testAddVertex passed" << std::endl;
}

void testRemoveVertex()
{
    ADTDirectedGraph graph = ADTDirectedGraph{};

    graph.addVertex(2);
    graph.addVertex(1);
    graph.addVertex(0);
    graph.addVertex(4);
    graph.addVertex(5);
    graph.addVertex(6);
    graph.addVertex(7);

    assert(graph.removeVertex(2) == true);
    assert(graph.removeVertex(1) == true);
    assert(graph.removeVertex(0) == true);
    assert(graph.removeVertex(4) == true);
    assert(graph.removeVertex(4) == false);
    assert(graph.removeVertex(2) == false);
    assert(graph.removeVertex(9) == false);

    std::cout << "testRemoveVertex passed" << std::endl;
}

void testAddEdge()
{
    ADTDirectedGraph graph = ADTDirectedGraph{};

    assert(graph.addVertex(3) == true);
    assert(graph.addVertex(3) == false);
    assert(graph.addVertex(3) == false);
    assert(graph.addVertex(1) == true);
    assert(graph.addVertex(2) == true);
    assert(graph.addVertex(3) == false);
    assert(graph.addVertex(0) == true);

    assert(graph.addEdge({3, 3}, 8) == true);
    assert(graph.addEdge({3, 3}, 8) == false);
    assert(graph.addEdge({4, 2}, 8) == false);
    assert(graph.addEdge({0, 1}, 3) == true);
    assert(graph.addEdge({2, 2}, 8) == true);

    std::cout << "testAddEdge passed" << std::endl;
}

void testRemoveEdge()
{
    ADTDirectedGraph graph = ADTDirectedGraph{};

    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);

    graph.addEdge({1, 2}, 3);
    graph.addEdge({2, 4}, 2);
    graph.addEdge({2, 2}, 4);
    graph.addEdge({4, 1}, 5);

    assert(graph.removeEdge({1, 2}) == true);
    assert(graph.removeEdge({1, 2}) == false);
    assert(graph.removeEdge({5, 5}) == false);
    assert(graph.removeEdge({4, 1}) == true);
    assert(graph.removeEdge({4, 1}) == false);

    std::cout << "testRemoveEdge passed" << std::endl;
}

void testIsEdge()
{

    ADTDirectedGraph graph = ADTDirectedGraph{};

    graph.addVertex(2);
    graph.addVertex(0);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addVertex(9);
    graph.addVertex(2);
    graph.addVertex(0);

    graph.addEdge({2, 3}, 3);
    graph.addEdge({2, 0}, 3);
    graph.addEdge({9, 2}, 3);
    graph.addEdge({3, 4}, 3);
    graph.addEdge({0, 8}, 3);
    graph.addEdge({2, 2}, 3);
    graph.addEdge({4, 9}, 3);

    assert(graph.isEdge(2, 3) == true);
    assert(graph.isEdge(2, 0) == true);
    assert(graph.isEdge(2, 0) == true);
    assert(graph.isEdge(9, 2) == true);
    assert(graph.isEdge(2, 2) == true);
    assert(graph.isEdge(2, 2) == true);
    assert(graph.isEdge(0, 11) == false);

    std::cout << "testIsEdge passed" << std::endl;
}