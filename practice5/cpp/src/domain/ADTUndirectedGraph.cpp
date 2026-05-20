#include "ADTUndirectedGraph.h"
#include "ADTUndirectedGraphIterator.h"

#include "../exceptions/HamCycleException.h"

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

ADTUndirectedGraph::ADTUndirectedGraph()
{
    // handle the vertices
    this->vertices = std::map<Vertex, std::vector<Vertex>>{};

    // handle costs
    this->costs = std::map<Edge, EdgeCost>{};
}

unsigned int ADTUndirectedGraph::nbVertices() const
{
    return this->vertices.size();
}

unsigned int ADTUndirectedGraph::nbEdges() const
{
    return this->costs.size();
}

bool ADTUndirectedGraph::isEdge(Vertex first, Vertex second) const
{

    // if the given vertices are not in the graph
    if (this->vertices.count(first) == 0 || this->vertices.count(second) == 0)
    {
        return false;
    }

    std::vector<Vertex> firstNeighbors = this->vertices.at(first);

    const auto &foundIt = std::find(firstNeighbors.begin(), firstNeighbors.end(), second);

    return foundIt != firstNeighbors.end();
}

unsigned int ADTUndirectedGraph::getDegree(Vertex vertex) const
{
    return this->vertices.at(vertex).size();
}

bool ADTUndirectedGraph::addEdge(Edge edge, EdgeCost cost)
{
    // check if edge is already in the graph
    // we can more easily do this by checking the costs map
    if (this->costs.count(edge) == 1)
    {
        return false;
    }

    // handle vertices
    this->vertices.at(edge.first).push_back(edge.second);
    this->vertices.at(edge.second).push_back(edge.first);
    // handle the cost map
    this->costs[edge] = cost;

    return true;
}

bool ADTUndirectedGraph::removeEdge(Edge edge)
{

    // check if edge exists in the graph
    // easiest way to do this is through the costs
    if (this->costs.count(edge) == 0)
    {
        return false;
    }

    // handle vertices
    auto &firstNeighbors = vertices[edge.first];
    auto itSecond = std::find(firstNeighbors.begin(), firstNeighbors.end(), edge.second);
    if (itSecond != firstNeighbors.end())
    {
        firstNeighbors.erase(itSecond);
    }
    auto &secondNeighbors = vertices[edge.second];
    auto itFirst = std::find(secondNeighbors.begin(), secondNeighbors.end(), edge.first);
    if (itFirst != secondNeighbors.end())
    {
        secondNeighbors.erase(itFirst);
    }

    // handle removing the edge from the costs
    this->costs.erase(edge);

    return true;
}

bool ADTUndirectedGraph::addVertex(Vertex vertex)
{
    // check if vertex is in graph already
    if (this->vertices.count(vertex) != 0)
    {
        return false;
    }

    // handle vertices
    this->vertices[vertex] = std::vector<Vertex>{};

    return true;
}

bool ADTUndirectedGraph::removeVertex(Vertex vertex)
{

    // check if vertex is in the graph
    if (this->vertices.count(vertex) == 0)
    {
        return false;
    }

    // handle vertices
    this->vertices.erase(vertex);

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

ADTUndirectedGraphIterator ADTUndirectedGraph::parseVertices() const
{

    return ADTUndirectedGraphIterator(*this);
}

std::vector<Vertex>::const_iterator ADTUndirectedGraph::parseNeighOfGivenVertexBegin(Vertex vertex) const
{

    if (this->vertices.count(vertex) == 0)
    {
        throw std::exception();
    }

    return this->vertices.at(vertex).begin();
}

std::vector<Vertex>::const_iterator ADTUndirectedGraph::parseNeighOfGivenVertexEnd(Vertex vertex) const
{

    if (this->vertices.count(vertex) == 0)
    {
        throw std::exception();
    }

    return this->vertices.at(vertex).end();
}

std::map<Edge, EdgeCost>::const_iterator ADTUndirectedGraph::parseEdgesBegin() const
{
    return this->costs.begin();
}

std::map<Edge, EdgeCost>::const_iterator ADTUndirectedGraph::parseEdgesEnd() const
{
    return this->costs.end();
}

std::pair<std::set<Vertex>, std::map<Vertex, Vertex>> ADTUndirectedGraph::forwardBreadthFirstTraversal(ADTUndirectedGraph graph, Vertex start)
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

        std::vector<Vertex>::const_iterator neighOutBegin = graph.parseNeighOfGivenVertexBegin(x);
        std::vector<Vertex>::const_iterator neighOutEnd = graph.parseNeighOfGivenVertexEnd(x);

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

std::vector<std::set<Vertex>> ADTUndirectedGraph::findConnectedComponentsOfUndirectedGraph(ADTUndirectedGraph &graph)
{
    std::set<Vertex> visited;
    std::vector<std::set<Vertex>> components;

    // iterating
    ADTUndirectedGraphIterator it = graph.parseVertices();
    for (it.first(); it.valid(); it.next())
    {
        Vertex v = it.getCurrent();

        // its not visited then we do something (sets)
        if (visited.find(v) == visited.end())
        {
            // we get the component
            auto bfsRes = ADTUndirectedGraph::forwardBreadthFirstTraversal(graph, v);
            std::set<Vertex> component = bfsRes.first;

            // we mark all the vertices from the component as visited
            visited.insert(component.begin(), component.end());

            // we store the component
            components.push_back(component);
        }
    }

    return components;
}

std::vector<Vertex> ADTUndirectedGraph::findHamiltonianCycle(ADTUndirectedGraph &graph) noexcept(false)
{
    if (graph.nbVertices() == 0)
    {
        throw HamCycleException("graph is empty");
    }

    // check if we have a hamiltonian cycle
    ADTUndirectedGraphIterator it = graph.parseVertices();
    for (it.first(); it.valid(); it.next())
    {
        Vertex v = it.getCurrent();
        if (graph.getDegree(v) < 2)
        {
            throw HamCycleException("no hamiltonian cycle exists");
        }
    }

    std::vector<Vertex> path;
    std::set<Vertex> visited;

    // first valid vertex
    Vertex start;
    ADTUndirectedGraphIterator it2 = graph.parseVertices();
    if (it2.valid())
    {
        start = it2.getCurrent();
    }

    path.push_back(start);
    visited.insert(start);

    //  we use backtracking to find the hamiltonian cycle
    if (graph.hamiltonianCycleBT(start, path, visited, graph.vertices, graph.nbVertices()))
    {
        // its a cycle so we need to add the starting vertex at the end
        path.push_back(start);
        return path;
    }

    throw HamCycleException("no hamiltonian cycle exists");
}

bool ADTUndirectedGraph::hamiltonianCycleBT(Vertex current,
                                            std::vector<Vertex> &path,
                                            std::set<Vertex> &visited,
                                            const std::map<Vertex, std::vector<Vertex>> &vertices,
                                            unsigned int nbVertices)
{
    // base case, we want to see if we found a ham cycle
    if (path.size() == nbVertices)
    {
        Vertex firstVertex = path[0];
        Vertex lastVertex = current;

        const auto &neighbors = vertices.at(lastVertex);
        if (std::find(neighbors.begin(), neighbors.end(), firstVertex) != neighbors.end())
        {
            return true;
        }
        return false;
    }

    const auto &neighbors = vertices.at(current);

    for (Vertex nextVertex : neighbors)
    {
        if (visited.find(nextVertex) == visited.end())
        {
            path.push_back(nextVertex);
            visited.insert(nextVertex);

            if (hamiltonianCycleBT(nextVertex, path, visited, vertices, nbVertices))
            {
                return true;
            }

            // backtrack
            path.pop_back();
            visited.erase(nextVertex);
        }
    }

    return false;
}