#include "ADTDirectedGraph.h"
#include "ADTDirectedGraphIterator.h"
#include <exception>

ADTDirectedGraphIterator::ADTDirectedGraphIterator(const ADTDirectedGraph &g) : graph(g)
{
    this->currentVertex = 0;
}
// BC = WC = TC: Theta(1)

void ADTDirectedGraphIterator::first()
{
    this->currentVertex = 0;
}
// BC = WC = TC: Theta(1)

void ADTDirectedGraphIterator::next()
{
    if (!this->valid())
    {
        throw std::exception();
    }

    this->currentVertex++;
    return;
}
// BC = WC = TC: Theta(1)

Vertex ADTDirectedGraphIterator::getCurrent()
{
    if (!this->valid())
    {
        throw std::exception();
    }

    return currentVertex;
}
// BC = WC = TC: Theta(1)

bool ADTDirectedGraphIterator::valid() const
{
    return this->currentVertex < this->graph.maxCapacity;
}
// BC = WC = TC: Theta(1)
