#include "ADTDirectedGraph.h"
#include <iostream>

/*
input:
3 5

0 1 5
2 0 3
0 0 2
1 2 5
0 2 9

handling:

outbound:
0: 1 0 2
1: 2
2: 0


inbound:
0: 0 2
1: 0
2: 0 1


costs:
0-1: 5
2-0: 3
0:0: 2
1:2: 5
0:2: 9




*/

ADTDirectedGraph::ADTDirectedGraph(int maxCapacity)
{
    // handle outbound
    this->outbound = Outbound{};
    for (int i = 0; i < maxCapacity; i++)
    {
        this->outbound[i] = std::vector<Vertex>{};
    }

    // handle inbound
    this->inbound = Inbound{};
    for (int i = 0; i < maxCapacity; i++)
    {
        this->inbound[i] = std::vector<Vertex>{};
    }

    // handle costs
    this->costs = EdgeCosts{};
}

ADTDirectedGraph::ADTDirectedGraph(const ADTDirectedGraph &g)
{
    // todo
}

ADTDirectedGraph::~ADTDirectedGraph()
{
    // optional, we don't need to manage deallocation rn
}

unsigned int ADTDirectedGraph::nbVertices() const
{
    unsigned int nbVertices = 0;

    for (const auto &[key, value] : this->outbound)
    {
        nbVertices++;
    }

    return nbVertices;
}

void ADTDirectedGraph::parseVertices(bool display) const
{

    if (display)
    {

        for (const auto &[key, value] : this->outbound)
        {
            std::cout << key << std::endl;
        }
    }
    else
    {
        for (const auto &[key, value] : this->outbound)
        {
            // do nothing
        }
    }
}

bool ADTDirectedGraph::isEdge(Vertex first, Vertex second) const
{

    std::vector<Vertex> inboundNeigh = this->outbound.at(first);

    bool found = false;

    for (const Vertex &vertex : inboundNeigh)
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

    // handle outbound
    this->outbound.at(edge.first).push_back(edge.second);
    // handle inbound
    this->inbound.at(edge.second).push_back(edge.first);
    // handle the cost map
    this->costs[edge] = cost;
}

bool ADTDirectedGraph::removeEdge(Edge edge)
{
    // handle outbound
    unsigned int outIndex = -1;
    std::vector<Vertex> &inboundNeigh = this->outbound.at(edge.first);
    for (int i = 0; i < inboundNeigh.size(); i++)
    {
        if (inboundNeigh.at(i) == edge.second)
        {
            outIndex = i;
            break;
        }
    }
    // remove the vertex from the outbound neighbors of first
    inboundNeigh.erase(inboundNeigh.begin() + outIndex);

    // handle inbound
    // basically the same thing as above but we change the source and dest
    unsigned int inIndex = -1;
    std::vector<Vertex> &outboundNeigh = this->inbound.at(edge.second);
    for (int i = 0; i < outboundNeigh.size(); i++)
    {
        if (outboundNeigh.at(i) == edge.first)
        {
            inIndex = i;
            break;
        }
    }
    // remove the vertex from the inbound neighbors of second
    outboundNeigh.erase(outboundNeigh.begin() + inIndex);

    // handle removing the edge from the costs
    this->costs.erase(edge);
}

bool ADTDirectedGraph::addVertex(Vertex vertex)
{
    // handle outbound
    this->outbound[vertex] = std::vector<Vertex>{};

    // handle inbound
    this->inbound[vertex] = std::vector<Vertex>{};
}

bool ADTDirectedGraph::removeVertex(Vertex vertex)
{
    // handle inbound first
    std::vector<Vertex> &inboundNeigh = this->outbound.at(vertex);

    // we check in the inbound of the current vertex if we have any matches then delete said match
    for (const Vertex &currOutVertex : inboundNeigh)
    {
        std::vector<Vertex> &currOutboundNeigh = this->inbound.at(currOutVertex);

        for (int i = 0; i < currOutboundNeigh.size(); i++)
        {
            if (currOutboundNeigh.at(i) == currOutVertex)
            {
                currOutboundNeigh.erase(currOutboundNeigh.begin() + i);
                break;
            }
        }
    }

    // now we delete the key from the outbound itself
    this->outbound.erase(vertex);

    // handle inbound
    std::vector<Vertex> &outboundNeigh = this->inbound.at(vertex);

    // we check in the outbound of the current vertex if we have any matches then delete said match
    for (const Vertex &currInVertex : outboundNeigh)
    {
        std::vector<Vertex> &currInboundNeigh = this->outbound.at(currInVertex);

        for (int i = 0; i < currInboundNeigh.size(); i++)
        {
            if (currInboundNeigh.at(i) == currInVertex)
            {
                currInboundNeigh.erase(currInboundNeigh.begin() + i);
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
}