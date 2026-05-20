#include "MenuController.h"
#include "../domain/ADTDirectedGraphIterator.h"
#include "../exceptions/HamCycleException.h"

#include <iostream>
#include <set>

MenuController::MenuController(const MenuUI &u, ADTDirectedGraph &g) : ui(u), graph(g) {}

void MenuController::displayCurrentNbVertices() const
{
    std::cout << "Number of Vertices: " << this->graph.nbVertices() << std::endl;
}

void MenuController::displayCurrentNbEdges() const
{
    std::cout << "Number of Edges: " << this->graph.nbEdges() << std::endl;
}

void MenuController::displayGraphVertices() const
{

    if (this->graph.nbVertices() == 0)
    {
        std::cout << "No Vertices in Graph to display." << std::endl;
        return;
    }

    std::cout << "Vertices: \n";

    ADTDirectedGraphIterator it = this->graph.parseVertices();

    it.first();
    while (it.valid())
    {
        std::cout << it.getCurrent() << std::endl;
        it.next();
    }

    std::cout << std::endl;
}

void MenuController::displayGraphEdges() const
{

    if (this->graph.nbEdges() == 0)
    {
        std::cout << "No Edges in Graph to display." << std::endl;
        return;
    }

    std::cout << "Edges: \n";

    std::map<Edge, EdgeCost>::const_iterator startIt = this->graph.parseEdgesBegin();
    std::map<Edge, EdgeCost>::const_iterator endIt = this->graph.parseEdgesEnd();

    while (startIt != endIt)
    {

        std::cout << startIt->first.first << ' ' << startIt->first.second << ' ' << startIt->second << std::endl;

        ++startIt;
    }

    std::cout << std::endl;
}

void MenuController::displayOutboundEdgesOfGivenVertex() const
{
    Vertex vertex = this->ui.getUserVertex();

    std::cout << "Outbound Edges: \n";

    try
    {
        std::vector<Vertex>::const_iterator startIt = this->graph.parseOutboundOfGivenVertexBegin(vertex);
        std::vector<Vertex>::const_iterator endIt = this->graph.parseOutboundOfGivenVertexEnd(vertex);

        while (startIt != endIt)
        {

            std::cout << *startIt << std::endl;

            ++startIt;
        }

        std::cout << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Vertex doesn't exist in graph." << std::endl;
    }
}

void MenuController::displayInboundEdgesOfGivenVertex() const
{
    Vertex vertex = this->ui.getUserVertex();

    std::cout << "Inbound Edges: \n";

    try
    {

        std::vector<Vertex>::const_iterator startIt = this->graph.parseInboundOfGivenVertexBegin(vertex);
        std::vector<Vertex>::const_iterator endIt = this->graph.parseInboundOfGivenVertexEnd(vertex);

        while (startIt != endIt)
        {

            std::cout << *startIt << std::endl;

            ++startIt;
        }

        std::cout << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Vertex doesn't exist in graph." << std::endl;
    }
}

void MenuController::checkIfGivenEdgeIsGraphEdge() const
{
    Edge edge = this->ui.getUserEdge();

    if (this->graph.isEdge(edge.first, edge.second))
    {
        std::cout << "Given Edge is IN the graph." << std::endl;
    }
    else
    {
        std::cout << "Given Edge is NOT in the graph." << std::endl;
    }

    std::cout << std::endl;
}

void MenuController::displayInDegreeOfGivenVertex() const
{
    Vertex vertex = this->ui.getUserVertex();

    try
    {
        unsigned int degree = this->graph.getInDegree(vertex);
        std::cout << "In Degree of Given Vertex: " << degree << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Vertex " << vertex << " is not in the graph." << std::endl;
    }
}

void MenuController::displayOutDegreeOfGivenVertex() const
{
    Vertex vertex = this->ui.getUserVertex();

    try
    {
        unsigned int degree = this->graph.getOutDegree(vertex);
        std::cout << "Out Degree of Given Vertex: " << degree << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Vertex " << vertex << " is not in the graph." << std::endl;
    }
}

void MenuController::addGivenVertexToGraph()
{
    Vertex vertex = this->ui.getUserVertex();

    if (this->graph.addVertex(vertex))
    {
        std::cout << "Successfully added Vertex" << std::endl;
    }
    else
    {
        std::cout << "FAILED to add Vertex" << std::endl;
    }
}

void MenuController::removeGivenVertexFromGraph()
{
    Vertex vertex = this->ui.getUserVertex();

    if (this->graph.removeVertex(vertex))
    {
        std::cout << "Successfully removed Vertex" << std::endl;
    }
    else
    {
        std::cout << "FAILED to remove Vertex" << std::endl;
    }
}

void MenuController::addGivenEdgeToGraph()
{
    Edge edge = this->ui.getUserEdge();
    EdgeCost cost = this->ui.getUserEdgeCost();

    if (this->ui.graph.addEdge(edge, cost))
    {
        std::cout << "Successfully added Edge" << std::endl;
    }
    else
    {
        std::cout << "FAILED to add Edge" << std::endl;
    }
}

void MenuController::removeGivenEdgeFromGraph()
{
    Edge edge = this->ui.getUserEdge();

    if (this->ui.graph.removeEdge(edge))
    {
        std::cout << "Successfully removed Edge" << std::endl;
    }
    else
    {
        std::cout << "FAILED to remove Edge" << std::endl;
    }
}

void MenuController::generateRandomGraphOfGivenNbVerticesAndNbEdges()
{
    unsigned int nbVertices = this->ui.getUserUnsignedInt("Number of Vertices: ");
    unsigned int nbEdges = this->ui.getUserUnsignedInt("Number of Edges: ");

    std::cout << "Generating a Random Graph....bz....z......" << std::endl;
    try
    {
        this->ui.graph = ADTDirectedGraph::generateRandomGraph(nbVertices, nbEdges);
    }
    catch (const std::exception &e)
    {
        std::cout << "Too many edges man." << std::endl;
    }
}

void MenuController::readGraphDataFromGivenFile()
{
    std::string filename = this->ui.getUserFilename();

    bool res = ADTDirectedGraph::readGraph(this->graph, filename);

    if (res)
    {
        std::cout << "Reading from " << filename << " was successful." << std::endl;
    }
    else
    {
        std::cout << "Reading from " << filename << " FAILED." << std::endl;
    }
}

void MenuController::writeGraphDataToGivenFile()
{
    std::string filename = this->ui.getUserFilename();

    bool res = ADTDirectedGraph::writeGraph(this->graph, filename);

    if (res)
    {
        std::cout << "Writing to " << filename << " was successful." << std::endl;
    }
    else
    {
        std::cout << "Writing to " << filename << " FAILED." << std::endl;
    }
}

void MenuController::findMinimumCostWalkBetweenTwoGivenVerticesUsingDijkstra()
{
    Vertex start = this->ui.getUserVertex();
    Vertex end = this->ui.getUserVertex();

    std::pair<std::map<Vertex, EdgeCost>, std::map<Vertex, Vertex>> dijkstraRes = this->graph.dijkstraAlgorithm(this->graph, start, end);

    std::map<Vertex, EdgeCost> dist = dijkstraRes.first;
    std::map<Vertex, Vertex> prev = dijkstraRes.second;

    // we check if there is even a path between the 2 given vertices
    if (dist.find(end) == dist.end())
    {
        std::cout << "no path exists" << std::endl;
        return;
    }

    std::vector<Vertex> path;
    Vertex current = end;

    while (current != start)
    {
        path.push_back(current);
        current = prev[current];
    }

    path.push_back(start);

    // once again, since we used std::vector for the path we can apply this alg
    std::reverse(path.begin(), path.end());

    std::cout << "lowest cost walk from " << start << " to " << end << ":" << std::endl;
    for (size_t i = 0; i < path.size(); i++)
    {
        std::cout << path[i];
        if (i < path.size() - 1)
            std::cout << " -> ";
    }
    std::cout << std::endl;
    std::cout << "total cost: " << dist[end] << std::endl;
}

void MenuController::findLowestLengthPathBetweenTwoGivenVertices() const
{
    Vertex start = this->ui.getUserVertex();
    Vertex end = this->ui.getUserVertex();

    std::vector<Vertex> path = this->graph.findLowestLengthPathBetweenTwoVertices(this->graph, start, end);

    if (path.empty())
    {
        std::cout << "no path exists" << std::endl;
        ;
    }
    else
    {
        std::cout << "shortest path from " << start << " to " << end << " (length: " << path.size() - 1 << "):\n";

        for (size_t i = 0; i < path.size(); ++i)
        {
            std::cout << path[i];
            if (i < path.size() - 1)
            {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl
                  << std::endl;
    }
}

ADTUndirectedGraph MenuController::convertToUndirected(const ADTDirectedGraph &directedGraph)
{
    ADTUndirectedGraph undirectedGraph;

    // handle vertices
    for (auto vertexIt = directedGraph.parseVertices(); vertexIt.valid(); vertexIt.next())
    {
        undirectedGraph.addVertex(vertexIt.getCurrent());
    }

    // handle edges
    for (auto edgeIt = directedGraph.parseEdgesBegin(); edgeIt != directedGraph.parseEdgesEnd(); ++edgeIt)
    {
        Edge directedEdge = edgeIt->first;
        EdgeCost cost = edgeIt->second;

        // undirected edge
        Edge undirectedEdge = {directedEdge.first, directedEdge.second};

        // duplicate handling
        if (!undirectedGraph.isEdge(undirectedEdge.first, undirectedEdge.second))
        {
            undirectedGraph.addEdge(undirectedEdge, cost);
        }
    }

    return undirectedGraph;
}

void MenuController::findConnectedComponentsOfGivenUndirectedGraph()
{
    try
    {
        /* code */

        ADTUndirectedGraph transformedGraph = this->convertToUndirected(this->graph);

        std::vector<std::set<Vertex>> foundComponents = ADTUndirectedGraph::findConnectedComponentsOfUndirectedGraph(transformedGraph);

        std::cout << "connected components\n";
        std::cout << "hit: " << foundComponents.size() << "\n\n";

        for (size_t i = 0; i < foundComponents.size(); ++i)
        {
            std::cout << "component " << (i + 1) << ": { ";

            bool first = true;
            for (Vertex v : foundComponents[i])
            {
                if (!first)
                    std::cout << ", ";
                std::cout << v;
                first = false;
            }
            std::cout << " }\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "something went wrong" << std::endl;
    }
}

void MenuController::findMinimumCostWalkBetweenTwoGivenVerticesUsingFord()
{
    Vertex start = this->ui.getUserVertex();
    Vertex end = this->ui.getUserVertex();

    try
    {
        std::pair<std::map<Vertex, int>, std::map<Vertex, Vertex>> fordRes = this->graph.bellmanFordAlgorithm(this->graph, start, end);

        std::map<Vertex, int> dist = fordRes.first;
        std::map<Vertex, Vertex> prev = fordRes.second;

        // we check if there is even a path between the 2 given vertices
        if (dist[end] == BIG_VALUE || prev.find(end) == prev.end() || dist.find(end) == dist.end())
        {
            std::cout << "no path exists" << std::endl;
            return;
        }

        // we can now check for negative cost cycles
        for (const auto &edgeWithCost : this->graph.costs)
        {
            Vertex y = edgeWithCost.first.second;
            Vertex x = edgeWithCost.first.first;
            EdgeCost cost = edgeWithCost.second;

            // if we can still make improvements then it means there is a negative cost somewhere
            if (dist[x] != BIG_VALUE && dist[y] > dist[x] + cost)
            {
                std::cout << "negative cost cycle detected" << std::endl;
                return;
            }
        }

        std::vector<Vertex> path;
        std::set<Vertex> visited;
        Vertex current = end;

        while (current != start)
        {
            if (visited.find(current) != visited.end())
            {
                break;
            }
            visited.insert(current);

            path.push_back(current);
            current = prev[current];
        }

        path.push_back(start);
        std::reverse(path.begin(), path.end());

        std::cout << "lowest cost walk from " << start << " to " << end << ":" << std::endl;
        for (size_t i = 0; i < path.size(); i++)
        {
            std::cout << path[i];
            if (i < path.size() - 1)
                std::cout << " -> ";
        }
        std::cout << std::endl;
        std::cout << "total cost: " << dist[end] << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "negative cost cycles found using ford's" << std::endl;
    }
}

void MenuController::findMinimumCostWalkBetweenTwoGivenVerticesUsingFloydWarshall()
{
    Vertex start = this->ui.getUserVertex();
    Vertex end = this->ui.getUserVertex();

    std::pair<std::vector<std::vector<unsigned int>>, std::vector<std::vector<Vertex>>> floydWarshallRes = this->graph.floydWarshallAlgorithm(this->graph);

    std::vector<std::vector<unsigned int>> dist = floydWarshallRes.first;
    std::vector<std::vector<Vertex>> prev = floydWarshallRes.second;

    // we check if there is even a path between the 2 given vertices
    if (dist[start][end] == BIG_VALUE)
    {
        std::cout << "no path exists" << std::endl;
        return;
    }

    std::vector<Vertex> path;
    Vertex current = end;

    while (current != start)
    {
        path.push_back(current);
        current = prev[start][current];
    }
    path.push_back(start);

    std::reverse(path.begin(), path.end());

    std::cout << "lowest cost walk from " << start << " to " << end << ":" << std::endl;
    for (size_t i = 0; i < path.size(); i++)
    {
        std::cout << path[i];
        if (i < path.size() - 1)
            std::cout << " -> ";
    }
    std::cout << std::endl;
    std::cout << "total cost: " << dist[start][end] << std::endl;
}

void MenuController::findHighestCostPathBetweenTwoGivenVerticesUsingPredecessors()
{

    if (this->graph.nbVertices() == 0)
    {
        std::cout << "graph is empty" << std::endl;
        return;
    }

    std::pair<bool, std::vector<unsigned int>> topoResult = ADTDirectedGraph::topologicalSort(this->graph);

    if (!topoResult.first)
    {
        std::cout << "graph is not a dag" << std::endl;
        return;
    }

    Vertex start = this->ui.getUserVertex();
    Vertex end = this->ui.getUserVertex();

    if (this->graph.outbound.count(start) == 0 || this->graph.outbound.count(end) == 0)
    {
        std::cout << "both vertices need to exist in the graph" << std::endl;
        return;
    }

    std::vector<Vertex> topoOrder = topoResult.second;

    std::cout << "topologicall order: ";
    for (size_t i = 0; i < topoOrder.size(); i++)
    {
        std::cout << topoOrder[i];
        if (i < topoOrder.size() - 1)
        {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    std::map<Vertex, int> dist;
    std::map<Vertex, Vertex> prev;

    for (const Vertex &v : topoOrder)
    {
        dist[v] = SMALL_VALUE;
        prev[v] = v;
    }

    dist[start] = 0;

    bool startReached = false;

    // we need to iterate through the vertices topologically
    for (const Vertex &u : topoOrder)
    {
        // we want to handle edges that go before our start edge since we can only go left to right
        if (u == start)
        {
            startReached = true;
        }
        if (!startReached)
        {
            continue;
        }

        // we want to verify if the vertex is actually reachable
        if (dist[u] == SMALL_VALUE)
        {
            continue;
        }

        // we want to go through the neighbors of u and update our maps
        std::vector<unsigned int>::const_iterator outBegin = this->graph.parseOutboundOfGivenVertexBegin(u);
        std::vector<unsigned int>::const_iterator outEnd = this->graph.parseOutboundOfGivenVertexEnd(u);

        while (outBegin != outEnd)
        {
            Vertex v = *outBegin;
            EdgeCost weight = this->graph.costs.at(Edge{u, v});

            // highest cost path
            if (dist[v] < dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
            ++outBegin;
        }
    }

    // if we couldnt reach the end it means there is no path from start to end
    if (dist[end] == SMALL_VALUE)
    {
        std::cout << "no path between given vertices" << std::endl;
        return;
    }

    // we reconstruct the path as always
    std::vector<Vertex> path;
    Vertex current = end;

    while (current != start)
    {
        path.push_back(current);
        current = prev[current];
    }
    path.push_back(start);

    // reverse
    std::reverse(path.begin(), path.end());

    // this should be a function on its own but ehh
    std::cout << "lowest cost walk from " << start << " to " << end << ":" << std::endl;
    for (size_t i = 0; i < path.size(); i++)
    {
        std::cout << path[i];
        if (i < path.size() - 1)
            std::cout << " -> ";
    }
    std::cout << std::endl;
    std::cout << "total cost: " << dist[end] << std::endl;
}

void MenuController::findHamiltonianCycleOfGraph()
{

    try
    {
        ADTUndirectedGraph transformedGraph = this->convertToUndirected(this->graph);

        std::vector<Vertex> hamCycle = ADTUndirectedGraph::findHamiltonianCycle(transformedGraph);

        std::cout << "hamiltonian cycle" << std::endl;
        for (int i = 0; i < hamCycle.size(); i++)
        {
            std::cout << hamCycle[i];
            if (i < hamCycle.size() - 1)
            {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
    catch (const HamCycleException &e)
    {
        std::cerr << e.what() << '\n';
    }
}