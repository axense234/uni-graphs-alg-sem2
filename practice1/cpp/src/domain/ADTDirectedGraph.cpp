#include "ADTDirectedGraph.h"
#include "ADTDirectedGraphIterator.h"
#include <iostream>

ADTDirectedGraph::ADTDirectedGraph()
{
    // handle outbound
    this->outbound = Outbound{};

    // handle inbound
    this->inbound = Inbound{};

    // handle costs
    this->costs = EdgeCosts{};
}

unsigned int ADTDirectedGraph::nbVertices() const
{
    unsigned int nbVertices = 0;

    for (const auto &_ : this->outbound)
    {
        nbVertices++;
    }

    return nbVertices;
}

unsigned int ADTDirectedGraph::nbEdges() const
{
    return this->costs.size();
}

bool ADTDirectedGraph::isEdge(Vertex first, Vertex second) const
{

    if (this->outbound.count(first) == 0 || this->inbound.count(second) == 0)
    {
        return false;
    }

    Vertices outboundNeigh = this->outbound.at(first);

    bool found = false;

    for (const Vertex &vertex : outboundNeigh)
    {
        if (vertex == second)
        {
            found = true;
            break;
        }
    }

    return found;
}

unsigned int ADTDirectedGraph::getInDegree(Vertex vertex) const
{
    return this->outbound.at(vertex).size();
}

unsigned int ADTDirectedGraph::getOutDegree(Vertex vertex) const
{
    return this->inbound.at(vertex).size();
}

bool ADTDirectedGraph::addEdge(Edge edge, EdgeCost cost)
{

    // check if edge vertices exist in the graph
    if (this->outbound.count(edge.first) == 0 || this->outbound.count(edge.second) == 0)
    {
        return false;
    }

    // check if edge is already in the graph
    // we can more easily do this by checking the costs map
    if (this->costs.count(edge) == 1)
    {
        return false;
    }

    // handle outbound
    this->outbound.at(edge.first).push_back(edge.second);
    // handle inbound
    this->inbound.at(edge.second).push_back(edge.first);
    // handle the cost map
    this->costs[edge] = cost;

    return true;
}

bool ADTDirectedGraph::removeEdge(Edge edge)
{

    // check if edge exists in the graph
    // easiest way to do this is through the costs
    if (this->costs.count(edge) == 0)
    {
        return false;
    }

    // handle outbound
    unsigned int outIndex = -1;
    Vertices &outboundNeigh = this->outbound.at(edge.first);
    for (unsigned int i = 0; i < outboundNeigh.size(); i++)
    {
        if (outboundNeigh.at(i) == edge.second)
        {
            outIndex = i;
            break;
        }
    }
    // remove the vertex from the outbound neighbors of first
    outboundNeigh.erase(outboundNeigh.begin() + outIndex);

    // handle inbound
    // basically the same thing as above but we change the source and dest
    unsigned int inIndex = -1;
    Vertices &inboundNeigh = this->inbound.at(edge.second);
    for (unsigned int i = 0; i < inboundNeigh.size(); i++)
    {
        if (inboundNeigh.at(i) == edge.first)
        {
            inIndex = i;
            break;
        }
    }
    // remove the vertex from the inbound neighbors of second
    inboundNeigh.erase(inboundNeigh.begin() + inIndex);

    // handle removing the edge from the costs
    this->costs.erase(edge);

    return true;
}

bool ADTDirectedGraph::addVertex(Vertex vertex)
{
    // check if vertex is in graph already
    if (this->outbound.count(vertex) != 0)
    {
        return false;
    }

    // handle outbound
    this->outbound[vertex] = Vertices{};

    // handle inbound
    this->inbound[vertex] = Vertices{};

    return true;
}

bool ADTDirectedGraph::removeVertex(Vertex vertex)
{

    // check if vertex is in the graphs
    if (this->outbound.count(vertex) == 0)
    {
        return false;
    }

    // handle inbound first
    Vertices &outboundNeigh = this->outbound.at(vertex);

    // we check in the inbound of the current vertex if we have any matches then delete said match
    for (const Vertex &currOutVertex : outboundNeigh)
    {
        Vertices &currInboundNeigh = this->inbound.at(currOutVertex);

        for (unsigned int i = 0; i < currInboundNeigh.size(); i++)
        {
            if (currInboundNeigh.at(i) == vertex)
            {
                currInboundNeigh.erase(currInboundNeigh.begin() + i);
                break;
            }
        }
    }

    // handle inbound
    Vertices &inboundNeigh = this->inbound.at(vertex);

    // we check in the outbound of the current vertex if we have any matches then delete said match
    for (const Vertex &currInVertex : inboundNeigh)
    {
        Vertices &currOutboundNeigh = this->outbound.at(currInVertex);

        for (unsigned int i = 0; i < currOutboundNeigh.size(); i++)
        {
            if (currOutboundNeigh.at(i) == vertex)
            {
                currOutboundNeigh.erase(currOutboundNeigh.begin() + i);
                break;
            }
        }
    }

    // now we delete the key from the inbound itself
    this->inbound.erase(vertex);

    // now we delete the key from the outbound itself
    this->outbound.erase(vertex);

    // handle costs

    // we iterate over the costs then if the key (type Edge) includes match we delete the entry
    for (const auto &[edge, cost] : this->costs)
    {
        if (edge.first == vertex || edge.second == vertex)
        {
            this->costs.erase(edge);
        }
    }

    return true;
}

ADTDirectedGraphIterator ADTDirectedGraph::parseVertices() const
{

    return ADTDirectedGraphIterator(*this);
}

VerticesIterator ADTDirectedGraph::parseOutboundOfGivenVertexBegin(Vertex vertex) const
{

    if (this->outbound.count(vertex) == 0)
    {
        throw std::exception();
    }

    return this->outbound.at(vertex).begin();
}

VerticesIterator ADTDirectedGraph::parseOutboundOfGivenVertexEnd(Vertex vertex) const
{

    if (this->outbound.count(vertex) == 0)
    {
        throw std::exception();
    }

    return this->outbound.at(vertex).end();
}

VerticesIterator ADTDirectedGraph::parseInboundOfGivenVertexEnd(Vertex vertex) const
{

    if (this->inbound.count(vertex) == 0)
    {
        throw std::exception();
    }

    return this->inbound.at(vertex).end();
}

VerticesIterator ADTDirectedGraph::parseInboundOfGivenVertexBegin(Vertex vertex) const
{

    if (this->inbound.count(vertex) == 0)
    {
        throw std::exception();
    }

    return this->inbound.at(vertex).begin();
}

EdgesIterator ADTDirectedGraph::parseEdgesBegin() const
{
    return this->costs.begin();
}

EdgesIterator ADTDirectedGraph::parseEdgesEnd() const
{
    return this->costs.end();
}