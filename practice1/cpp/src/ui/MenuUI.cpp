#include "MenuUI.h"
#include "MenuController.h"

#include <iostream>

MenuUI::MenuUI(ADTDirectedGraph &g) : graph(g)
{
    this->userMenuOption = 0;
}

void MenuUI::displayMenuOptions() const
{
    std::cout << "\n---------MENU OPTIONS---------\n";
    std::cout << "\n---------GRAPH PROPERTIES---------\n";
    std::cout << "1: Get the current number of Vertices of the Graph.\n";
    std::cout << "2: Get the current number of Edges of the Graph.\n";
    std::cout << "3: Display the Vertices of the Graph.\n";
    std::cout << "4: Display the Edges of the Graph (with cost included).\n";
    std::cout << "5: Display the Outbound Edges of a given Vertex.\n";
    std::cout << "6: Display the Inbound Edges of a given Vertex.\n";
    std::cout << "7: Check if a given Edge is an Edge of the Graph.\n";
    std::cout << "8: Get the in-degree of a given Vertex.\n";
    std::cout << "9: Get the out-degree of a given Vertex.\n";
    std::cout << "\n---------GRAPH MUTATION---------\n";
    std::cout << "10: Add a given Vertex to the Graph.\n";
    std::cout << "11: Remove a given Vertex from the Graph.\n";
    std::cout << "12: Add a given Edge to the Graph.\n";
    std::cout << "13: Remove a given Edge from the Graph.\n";
    std::cout << "\n---------UTILITIES---------\n";
    std::cout << "14: Generate a random Graph with given nb of vertices and given nb of edges. This newly generated Graph replaces the current Graph.\n";
    std::cout << "15: Read from a given file graph data. This updates the current Graph.\n";
    std::cout << "16: Write to a given filename graph data.\n";
    std::cout << "17: Exit program.\n";
    std::cout << std::endl;
}

unsigned int MenuUI::getUserUnsignedInt(const std::string &label) const
{
    unsigned int value;
    long long catcher;

    while (true)
    {

        std::cout << label;
        if (std::cin >> catcher && catcher >= 0)
        {
            value = catcher;
            std::cout << std::endl;
            return value;
        }
        std::cin.clear();
        std::cout << "Invalid input, expected an unsigned int." << std::endl;
    }
}

Vertex MenuUI::getUserVertex() const
{
    Vertex vertex;
    long long vertexCatcher;
    while (true)
    {
        std::cout << "Vertex (unsigned int): ";

        if (std::cin >> vertexCatcher && vertexCatcher >= 0)
        {
            vertex = vertexCatcher;
            std::cout << std::endl;
            return vertex;
        }
        std::cin.clear();
        std::cout << "Invalid input, expected a Vertex (unsigned int)." << std::endl;
    }
}

Edge MenuUI::getUserEdge() const
{
    Edge edge;
    long long firstCatcher;
    long long secondCatcher;
    while (true)
    {
        std::cout << "Edge (unsigned int, unsigned int): ";

        if (std::cin >> firstCatcher >> secondCatcher && firstCatcher >= 0 && secondCatcher >= 0)
        {
            edge = {firstCatcher, secondCatcher};
            std::cout << std::endl;
            return edge;
        }
        std::cin.clear();
        std::cout << "Invalid input, expected an Edge (ex: 2 5)." << std::endl;
    }

    return edge;
}

EdgeCost MenuUI::getUserEdgeCost() const
{
    EdgeCost cost;
    long long costCatcher;
    while (true)
    {
        std::cout << "Cost (unsigned int): ";

        if (std::cin >> costCatcher && costCatcher >= 0)
        {
            cost = costCatcher;
            std::cout << std::endl;
            return cost;
        }
        std::cin.clear();
        std::cout << "Invalid input, expected an EdgeCost (unsigned int)." << std::endl;
    }
}

std::string MenuUI::getUserFilename() const
{
    std::string filename;

    while (true)
    {
        std::cout << "Filename: ";

        if (std::cin >> filename)
        {
            std::cout << std::endl;
            return filename;
        }
        std::cin.clear();
        std::cout << "Invalid input, expected a Filename (string)." << std::endl;
    }
}

void MenuUI::start()
{

    MenuController menuController = this->controller();

    while (true)
    {
        this->displayMenuOptions();
        this->userMenuOption = getUserUnsignedInt("Menu Option: ");
        switch (userMenuOption)
        {
        case 1:
            menuController.displayCurrentNbVertices();
            break;
        case 2:
            menuController.displayCurrentNbEdges();
            break;
        case 3:
            menuController.displayGraphVertices();
            break;
        case 4:
            menuController.displayGraphEdges();
            break;
        case 5:
            menuController.displayOutboundEdgesOfGivenVertex();
            break;
        case 6:
            menuController.displayInboundEdgesOfGivenVertex();
            break;
        case 7:
            menuController.checkIfGivenEdgeIsGraphEdge();
            break;
        case 8:
            menuController.displayInDegreeOfGivenVertex();
            break;
        case 9:
            menuController.displayOutDegreeOfGivenVertex();
            break;
        case 10:
            menuController.addGivenVertexToGraph();
            break;
        case 11:
            menuController.removeGivenVertexFromGraph();
            break;
        case 12:
            menuController.addGivenEdgeToGraph();
            break;
        case 13:
            menuController.removeGivenEdgeFromGraph();
            break;
        case 14:
            menuController.generateRandomGraphOfGivenNbVerticesAndNbEdges();
            break;
        case 15:
            menuController.readGraphDataFromGivenFile();
            break;
        case 16:
            menuController.writeGraphDataToGivenFile();
            break;
        case 17:
            std::cout << "Exiting..." << std::endl;
            return;
        default:
            break;
        }
    }
}

MenuController MenuUI::controller() const
{
    return MenuController(*this, this->graph);
}