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

void ADTDirectedGraph::parseVertices(bool display) const
{
    for (const auto &[key, value] : this->outbound)
    {
        if (display)
        {
            std::cout << key << std::endl;
        }
    }
}

bool ADTDirectedGraph::isEdge(Vertex first, Vertex second) const
{

    std::vector<Vertex> outboundNeigh = this->outbound.at(first);

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
    std::vector<Vertex> &outboundNeigh = this->outbound.at(edge.first);
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
    std::vector<Vertex> &inboundNeigh = this->inbound.at(edge.second);
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
    this->outbound[vertex] = std::vector<Vertex>{};

    // handle inbound
    this->inbound[vertex] = std::vector<Vertex>{};

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
    std::vector<Vertex> &outboundNeigh = this->outbound.at(vertex);

    // we check in the inbound of the current vertex if we have any matches then delete said match
    for (const Vertex &currOutVertex : outboundNeigh)
    {
        std::vector<Vertex> &currInboundNeigh = this->inbound.at(currOutVertex);

        for (unsigned int i = 0; i < currInboundNeigh.size(); i++)
        {
            if (currInboundNeigh.at(i) == vertex)
            {
                currInboundNeigh.erase(currInboundNeigh.begin() + i);
                break;
            }
        }
    }

    // now we delete the key from the outbound itself
    this->outbound.erase(vertex);

    // handle inbound
    std::vector<Vertex> &inboundNeigh = this->inbound.at(vertex);

    // we check in the outbound of the current vertex if we have any matches then delete said match
    for (const Vertex &currInVertex : inboundNeigh)
    {
        std::vector<Vertex> &currOutboundNeigh = this->outbound.at(currInVertex);

        for (unsigned int i = 0; i < currOutboundNeigh.size(); i++)
        {
            if (currOutboundNeigh.at(i) == currInVertex)
            {
                currOutboundNeigh.erase(currOutboundNeigh.begin() + i);
                break;
            }
        }
    }

    // now we delete the key from the inbound itself
    this->inbound.erase(vertex);

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

void ADTDirectedGraph::parseOutboundEdges(Vertex vertex, bool display) const
{

    for (const auto &currVertex : this->outbound.at(vertex))
    {
        if (display)
        {
            std::cout << vertex << ' ' << currVertex << std::endl;
        }
    }
}

void ADTDirectedGraph::parseInboundEdges(Vertex vertex, bool display) const
{

    for (const auto &currVertex : this->inbound.at(vertex))
    {
        if (display)
        {
            std::cout << vertex << ' ' << currVertex << std::endl;
        }
    }
}

ADTDirectedGraphIterator ADTDirectedGraph::verticesIterator() const
{

    return ADTDirectedGraphIterator(*this);
}

Vertices::const_iterator ADTDirectedGraph::outboundIterator(Vertex vertex) const
{

    if (this->outbound.count(vertex) == 0)
    {
        throw std::exception();
    }

    return this->outbound.at(vertex).begin();
}

Vertices::const_iterator ADTDirectedGraph::inboundIterator(Vertex vertex) const
{

    if (this->inbound.count(vertex) == 0)
    {
        throw std::exception();
    }

    return this->inbound.at(vertex).begin();
}

EdgeCosts::const_iterator ADTDirectedGraph::edgesBeginIterator() const
{
    return this->costs.begin();
}

EdgeCosts::const_iterator ADTDirectedGraph::edgesEndIterator() const
{
    return this->costs.end();
}