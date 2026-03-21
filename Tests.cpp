#include "Tests.h"
#include "ADTDirectedGraph.h"

#include <assert.h>

void testInit()
{
    ADTDirectedGraph graph = ADTDirectedGraph{5};
    assert(graph.nbVertices() == 5);
}