#pragma once
#include "ADTDirectedGraph.h"

class ADTDirectedGraphIterator
{
    friend class ADTDirectedGraph;

private:
    const ADTDirectedGraph &graph;
    Vertex currentVertex;

    ADTDirectedGraphIterator(const ADTDirectedGraph &graph);

public:
    void first();
    void next();
    Vertex getCurrent();
    bool valid() const;
};