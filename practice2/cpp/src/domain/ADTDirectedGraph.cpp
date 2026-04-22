#include "ADTDirectedGraph.h"
#include "ADTDirectedGraphIterator.h"

#include <iostream>
#include <set>
#include <utility>
#include <queue>
#include <algorithm>
#include <fstream>
#include <random>
#include <climits>
#include <vector>
#include <exception>

ADTDirectedGraph::ADTDirectedGraph()
{
    // handle outbound
    this->outbound = std::map<Vertex, std::vector<Vertex>>{};

    // handle inbound
    this->inbound = std::map<Vertex, std::vector<Vertex>>{};

    // handle costs
    this->costs = std::map<Edge, EdgeCost>{};
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
    return this->inbound.at(vertex).size();
}

unsigned int ADTDirectedGraph::getOutDegree(Vertex vertex) const
{
    return this->outbound.at(vertex).size();
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

    // handle inbound
    std::vector<Vertex> &inboundNeigh = this->inbound.at(vertex);

    // we check in the outbound of the current vertex if we have any matches then delete said match
    for (const Vertex &currInVertex : inboundNeigh)
    {
        std::vector<Vertex> &currOutboundNeigh = this->outbound.at(currInVertex);

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
    // compared to practice 1 this time we actually handle deleting properly when using iterators
    for (auto it = this->costs.begin(); it != this->costs.end();)
    {
        if (it->first.first == vertex || it->first.second == vertex)
        {
            it = this->costs.erase(it);
        }
        else
        {
            ++it;
        }
    }

    return true;
}

ADTDirectedGraphIterator ADTDirectedGraph::parseVertices() const
{

    return ADTDirectedGraphIterator(*this);
}

std::vector<Vertex>::const_iterator ADTDirectedGraph::parseOutboundOfGivenVertexBegin(Vertex vertex) const
{

    if (this->outbound.count(vertex) == 0)
    {
        throw std::exception();
    }

    return this->outbound.at(vertex).begin();
}

std::vector<Vertex>::const_iterator ADTDirectedGraph::parseOutboundOfGivenVertexEnd(Vertex vertex) const
{

    if (this->outbound.count(vertex) == 0)
    {
        throw std::exception();
    }

    return this->outbound.at(vertex).end();
}

std::vector<Vertex>::const_iterator ADTDirectedGraph::parseInboundOfGivenVertexEnd(Vertex vertex) const
{

    if (this->inbound.count(vertex) == 0)
    {
        throw std::exception();
    }

    return this->inbound.at(vertex).end();
}

std::vector<Vertex>::const_iterator ADTDirectedGraph::parseInboundOfGivenVertexBegin(Vertex vertex) const
{

    if (this->inbound.count(vertex) == 0)
    {
        throw std::exception();
    }

    return this->inbound.at(vertex).begin();
}

std::map<Edge, EdgeCost>::const_iterator ADTDirectedGraph::parseEdgesBegin() const
{
    return this->costs.begin();
}

std::map<Edge, EdgeCost>::const_iterator ADTDirectedGraph::parseEdgesEnd() const
{
    return this->costs.end();
}

std::pair<std::set<Vertex>, std::map<Vertex, Vertex>> ADTDirectedGraph::forwardBreadthFirstTraversal(ADTDirectedGraph graph, Vertex start)
{
    std::queue<Vertex> queue;
    std::map<Vertex, Vertex> prev;
    std::map<Vertex, Vertex> dist;
    std::set<Vertex> visited;

    queue.push(start);
    visited.insert(start);
    dist[start] = 0;
    prev[start] = start;

    while (!queue.empty())
    {
        // those 2 lines are equivalent to the q.enqueue operation
        Vertex x = queue.front();
        queue.pop();

        std::vector<Vertex>::const_iterator neighOutBegin = graph.parseOutboundOfGivenVertexBegin(x);
        std::vector<Vertex>::const_iterator neighOutEnd = graph.parseOutboundOfGivenVertexEnd(x);

        while (neighOutBegin != neighOutEnd)
        {
            Vertex y = *neighOutBegin;

            if (visited.find(y) == visited.end())
            {
                queue.push(y);
                visited.insert(y);
                dist[y] = dist[x] + 1;
                prev[y] = x;
            }

            ++neighOutBegin;
        }
    }

    return {visited, prev};
}

std::vector<Vertex> ADTDirectedGraph::findLowestLengthPathBetweenTwoVertices(ADTDirectedGraph graph, Vertex start, Vertex end)
{
    auto [visited, prev] = forwardBreadthFirstTraversal(graph, start);

    // we couldnt reach the end
    if (visited.find(end) == visited.end())
    {
        return {};
    }

    std::vector<Vertex> path;
    Vertex current = end;

    while (current != start)
    {
        path.push_back(current);
        current = prev[current];
    }
    path.push_back(start);

    // we used std::vector for the path meaning we can apply this alg
    std::reverse(path.begin(), path.end());

    return path;
}

bool ADTDirectedGraph::readGraph(ADTDirectedGraph &graph, const std::string &filename)
{
    std::ifstream inputFile(filename);

    // forgot to reset the damn graph
    graph = ADTDirectedGraph{};

    if (!inputFile.is_open())
    {
        return false;
    }

    unsigned int nbVertices, nbEdges;
    inputFile >> nbVertices >> nbEdges;

    Vertex first, second;
    EdgeCost cost;

    for (unsigned int i = 0; i < nbEdges; i++)
    {
        inputFile >> first >> second >> cost;

        graph.addVertex(first);
        graph.addVertex(second);

        graph.addEdge({first, second}, cost);
    }

    return true;
}

bool ADTDirectedGraph::writeGraph(const ADTDirectedGraph &graph, const std::string &filename)
{
    std::ofstream outputFile(filename);

    if (!outputFile.is_open())
    {
        return false;
    }

    outputFile << graph.nbVertices() << ' ' << graph.nbEdges() << std::endl;

    std::map<Edge, EdgeCost>::const_iterator startIt = graph.parseEdgesBegin();
    std::map<Edge, EdgeCost>::const_iterator endIt = graph.parseEdgesEnd();

    while (startIt != endIt)
    {

        Edge currEdge = startIt->first;
        EdgeCost currCost = startIt->second;

        outputFile << currEdge.first << ' ' << currEdge.second << ' ' << currCost << std::endl;

        ++startIt;
    }

    return true;
}

ADTDirectedGraph ADTDirectedGraph::generateRandomGraph(unsigned int nbVertices, unsigned int nbEdges)
{

    // so if we have nbEdges > nbVertices * (nbVertices - 1) we have a problemo
    if (nbEdges > nbVertices * (nbVertices - 1))
    {
        throw std::exception();
    }

    ADTDirectedGraph graph = ADTDirectedGraph{};

    // way of generating numbers from 0 to the limit of unsigned int
    // rd is a seed gen, gen is a mersenne twister engine
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> randomUnsignedInt(0, UINT_MAX);
    std::uniform_int_distribution<unsigned int> randomVerticesIndex(0, nbVertices - 1);

    std::vector<Vertex> generatedVertices = std::vector<Vertex>{};

    // we generate nbVertices number of vertices
    for (unsigned int i = 0; i < nbVertices; ++i)
    {
        unsigned int vertex = Vertex{randomUnsignedInt(gen)};
        graph.addVertex(vertex);
        generatedVertices.push_back(vertex);
    }

    // we handle generating random edges
    unsigned int generatedEdges = 0;
    while (generatedEdges < nbEdges)
    {

        Vertex firstVertex = generatedVertices.at(randomVerticesIndex(gen));
        Vertex secondVertex = generatedVertices.at(randomVerticesIndex(gen));

        // if we got unlucky and we already have an edge we just skip
        if (graph.isEdge(firstVertex, secondVertex))
        {
            continue;
        }

        // we create an edge with unsigned int cost as well
        unsigned int randomCost = EdgeCost{randomUnsignedInt(gen)};
        Edge createdEdge = Edge{firstVertex, secondVertex};
        graph.addEdge(createdEdge, randomCost);

        generatedEdges++;
    }

    return graph;
}
