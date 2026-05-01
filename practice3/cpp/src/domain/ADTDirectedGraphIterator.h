#pragma once
#include "ADTDirectedGraph.h"

class ADTDirectedGraphIterator
{
    friend class ADTDirectedGraph;

private:
    const ADTDirectedGraph &graph;
    std::map<Vertex, std::vector<Vertex>>::const_iterator currentVerticesIterator;

    ADTDirectedGraphIterator(const ADTDirectedGraph &graph);

public:
    void first();
    void next();
    Vertex getCurrent();
    bool valid() const;
};