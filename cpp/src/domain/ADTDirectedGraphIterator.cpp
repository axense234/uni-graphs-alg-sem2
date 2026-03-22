#include "ADTDirectedGraph.h"
#include "ADTDirectedGraphIterator.h"

#include <exception>
#include <iterator>

ADTDirectedGraphIterator::ADTDirectedGraphIterator(const ADTDirectedGraph &g) : graph(g)
{
    if (this->graph.nbVertices() == 0)
    {
        throw std::exception();
    }
    this->currentVerticesIterator = this->graph.outbound.begin();
}

void ADTDirectedGraphIterator::first()
{
    if (this->graph.nbVertices() == 0)
    {
        throw std::exception();
    }
    this->currentVerticesIterator = this->graph.outbound.begin();
}

void ADTDirectedGraphIterator::next()
{
    if (!this->valid())
    {
        throw std::exception();
    }

    this->currentVerticesIterator = std::next(this->currentVerticesIterator);
    return;
}

Vertex ADTDirectedGraphIterator::getCurrent()
{
    if (!this->valid())
    {
        throw std::exception();
    }

    return this->currentVerticesIterator->first;
}

bool ADTDirectedGraphIterator::valid() const
{
    return this->currentVerticesIterator != this->graph.outbound.end();
}
