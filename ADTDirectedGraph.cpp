#include "ADTDirectedGraph.h"
#include <iostream>

ADTDirectedGraph::ADTDirectedGraph()
{
    this->outbound = {};
    this->inbound = {};
    this->costs = {};
}

ADTDirectedGraph::ADTDirectedGraph(const ADTDirectedGraph &g)
{
    // todo
}

ADTDirectedGraph::~ADTDirectedGraph()
{
    // todo
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

    std::vector<Vertex> vertices = this->outbound.at(first);

    bool found = false;

    for (const Vertex &vertex : vertices)
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
    return this->inbound.at(vertex).size();
}

unsigned int ADTDirectedGraph::getOutDegree(Vertex vertex) const
{
    return this->outbound.at(vertex).size();
}

bool ADTDirectedGraph::addEdge(Edge edge, EdgeCost cost)
{

    // handle outbound
    this->outbound[edge.first].push_back(edge.second);
    // handle inbound
    this->inbound[edge.second].push_back(edge.first);
    // handle the cost map
    this->costs[edge] = cost;
}

bool ADTDirectedGraph::removeEdge(Edge edge)
{
    // handle outbound
    unsigned int outIndex = -1;
    std::vector<Vertex> &outboundArr = this->outbound.at(edge.first);
    for (int i = 0; i < outboundArr.size(); i++)
    {
        if (outboundArr.at(i) == edge.second)
        {
            outIndex = i;
            break;
        }
    }
    // remove the vertex from the outbound neighbors of first
    outboundArr.erase(outboundArr.begin() + outIndex);

    // handle inbound
    // basically the same thing as above but we change the source and dest
    unsigned int inIndex = -1;
    std::vector<Vertex> &inboundArr = this->inbound.at(edge.second);
    for (int i = 0; i < inboundArr.size(); i++)
    {
        if (inboundArr.at(i) == edge.first)
        {
            inIndex = i;
            break;
        }
    }
    // remove the vertex from the inbound neighbors of second
    inboundArr.erase(inboundArr.begin() + inIndex);

    // handle removing the edge from the costs
    this->costs.erase(edge);
}