#include "MenuController.h"
#include "../domain/ADTDirectedGraphIterator.h"

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
