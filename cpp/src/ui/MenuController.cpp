#include "MenuController.h"
#include "../helpers/Helpers.h"
#include "../domain/ADTDirectedGraphIterator.h"

#include <iostream>

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

    EdgesIterator startIt = this->graph.parseEdgesBegin();
    EdgesIterator endIt = this->graph.parseEdgesEnd();

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
        VerticesIterator startIt = this->graph.parseOutboundOfGivenVertexBegin(vertex);
        VerticesIterator endIt = this->graph.parseOutboundOfGivenVertexEnd(vertex);

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

        VerticesIterator startIt = this->graph.parseInboundOfGivenVertexBegin(vertex);
        VerticesIterator endIt = this->graph.parseInboundOfGivenVertexEnd(vertex);

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
        this->ui.graph = Helpers::generateRandomGraph(nbVertices, nbEdges);
    }
    catch (const std::exception &e)
    {
        std::cout << "Too many edges man." << std::endl;
    }
}

void MenuController::readGraphDataFromGivenFile()
{
    std::string filename = this->ui.getUserFilename();

    bool res = Helpers::readGraph(this->graph, filename);

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

    bool res = Helpers::writeGraph(this->graph, filename);

    if (res)
    {
        std::cout << "Writing to " << filename << " was successful." << std::endl;
    }
    else
    {
        std::cout << "Writing to " << filename << " FAILED." << std::endl;
    }
}