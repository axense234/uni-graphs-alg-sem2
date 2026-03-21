#include "MenuUI.h"
#include "MenuController.h"
#include "../helpers/Helpers.h"

#include <iostream>

MenuUI::MenuUI()
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
    std::cout << "4: Display the Outbound Edges of a given Vertex.\n";
    std::cout << "5: Display the Inbound Edges of a given Vertex.\n";
    std::cout << "6: Check if a given Edge is an Edge of the Graph.\n";
    std::cout << "7: Get the in-degree of a given Vertex.\n";
    std::cout << "8: Get the out-degree of a given Vertex.\n";
    std::cout << "\n---------GRAPH MUTATION---------\n";
    std::cout << "9: Add a given Vertex to the Graph.\n";
    std::cout << "10: Remove a given Vertex from the Graph.\n";
    std::cout << "11: Add a given Edge to the Graph.\n";
    std::cout << "12: Remove a given Edge from the Graph.\n";
    std::cout << "\n---------UTILITIES---------\n";
    std::cout << "13: Generate a random Graph with given nb of vertices and given nb of edges. This newly generated Graph replaces the current Graph.\n";
    std::cout << "14: Read from a given file graph data. This updates the current Graph.\n";
    std::cout << "15: Write to a given filename graph data.\n";
}

unsigned int MenuUI::getUserUnsignedInt(char *label) const
{
    unsigned short value;

    std::cout << label;
    std::cin >> value;
    std::cout << std::endl;
}

Vertex MenuUI::getUserVertex() const
{
    Vertex vertex;
    std::cout << "Vertex (unsigned int): ";
    std::cin >> vertex;
    std::cout << std::endl;
}

Edge MenuUI::getUserEdge() const
{
    Edge edge;
    std::cout << "Edge (unsigned int, unsigned int): ";
    std::cin >> edge.first >> edge.second;
    std::cout << std::endl;
}

EdgeCost MenuUI::getUserEdgeCost() const
{
    EdgeCost cost;
    std::cout << "Edge Cost (unsigned int): ";
    std::cin >> cost;
    std::cout << std::endl;
}

void MenuUI::start()
{
    while (true)
    {
        this->userMenuOption = getUserUnsignedInt("Menu Option: ");
        switch (userMenuOption)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
            break;
        case 14:
            break;
        case 15:
            break;

        default:
            break;
        }
    }
}

MenuController MenuUI::controller() const
{
    return MenuController(*this);
}