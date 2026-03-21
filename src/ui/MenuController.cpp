#include "MenuController.h"
#include "../helpers/Helpers.h"

#include <iostream>

MenuController::MenuController(MenuUI &u) : ui(u) {}

void MenuController::displayCurrentNbVertices()
{
    std::cout << "Number of Vertices: " << this->ui.graph.nbVertices() << std::endl;
}

void MenuController::displayCurrentNbEdges()
{
    std::cout << "Number of Edges: " << this->ui.graph.nbEdges() << std::endl;
}

void MenuController::displayGraphVertices()
{
    std::cout << "Vertices: \n";
    this->ui.graph.parseVertices(true);
    std::cout << std::endl;
}

void MenuController::displayOutboundEdgesOfGivenVertex()
{
    Vertex vertex = this->ui.getUserVertex();

    std::cout << "Outbound Edges: \n";
    this->ui.graph.parseOutboundEdges(vertex, true);
    std::cout << std::endl;
}

void MenuController::displayInboundEdgesOfGivenVertex()
{
    Vertex vertex = this->ui.getUserVertex();

    std::cout << "Inbound Edges: \n";
    this->ui.graph.parseInboundEdges(vertex, true);
    std::cout << std::endl;
}

void MenuController::checkIfGivenEdgeIsGraphEdge()
{
    Edge edge = this->ui.getUserEdge();

    if (this->ui.graph.isEdge(edge.first, edge.second))
    {
        std::cout << "Given Edge is IN the graph." << std::endl;
    }
    else
    {
        std::cout << "Given Edge is NOT in the graph." << std::endl;
    }

    std::cout << std::endl;
}

void MenuController::displayInDegreeOfGivenVertex()
{
    Vertex vertex = this->ui.getUserVertex();

    std::cout << "In Degree of Given Vertex: " << this->ui.graph.getInDegree(vertex) << std::endl;
}

void MenuController::displayOutDegreeOfGivenVertex()
{
    Vertex vertex = this->ui.getUserVertex();

    std::cout << "Out Degree of Given Vertex: " << this->ui.graph.getOutDegree(vertex) << std::endl;
}

void MenuController::addGivenVertexToGraph()
{
    Vertex vertex = this->ui.getUserVertex();

    if (this->ui.graph.addVertex(vertex))
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

    if (this->ui.graph.removeVertex(vertex))
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
    this->ui.graph = Helpers::generateRandomGraph(nbVertices, nbEdges);
}