#pragma once
#include "ADTUndirectedGraph.h"

class ADTUndirectedGraphIterator
{
    friend class ADTUndirectedGraph;

private:
    const ADTUndirectedGraph &graph;
    std::map<Vertex, std::vector<Vertex>>::const_iterator current;

    ADTUndirectedGraphIterator(const ADTUndirectedGraph &graph);

public:
    void first();
    void next();
    Vertex getCurrent();
    bool valid() const;
};