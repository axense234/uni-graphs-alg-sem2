#include "ADTUndirectedGraph.h"
#include "ADTUndirectedGraphIterator.h"

#include <exception>
#include <iterator>

ADTUndirectedGraphIterator::ADTUndirectedGraphIterator(const ADTUndirectedGraph &g) : graph(g)
{
    if (this->graph.nbVertices() == 0)
    {
        throw std::exception();
    }
    this->current = this->graph.vertices.begin();
}

void ADTUndirectedGraphIterator::first()
{
    if (this->graph.nbVertices() == 0)
    {
        throw std::exception();
    }
    this->current = this->graph.vertices.begin();
}

void ADTUndirectedGraphIterator::next()
{
    if (!this->valid())
    {
        throw std::exception();
    }

    this->current++;
    return;
}

Vertex ADTUndirectedGraphIterator::getCurrent()
{
    if (!this->valid())
    {
        throw std::exception();
    }

    return this->current->first;
}

bool ADTUndirectedGraphIterator::valid() const
{
    return this->current != this->graph.vertices.end();
}
