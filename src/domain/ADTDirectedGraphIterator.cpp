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
    this->currentVertex = this->graph.outbound.begin()->first;
}

void ADTDirectedGraphIterator::first()
{
    if (this->graph.nbVertices() == 0)
    {
        throw std::exception();
    }
    this->currentVertex = this->graph.outbound.begin()->first;
}

void ADTDirectedGraphIterator::next()
{
    if (!this->valid())
    {
        throw std::exception();
    }

    this->currentVertex = std::next(this->graph.outbound.find(this->currentVertex))->first;
    return;
}

Vertex ADTDirectedGraphIterator::getCurrent()
{
    if (!this->valid())
    {
        throw std::exception();
    }

    return this->currentVertex;
}

bool ADTDirectedGraphIterator::valid() const
{
    return this->currentVertex < this->graph.nbVertices();
}
