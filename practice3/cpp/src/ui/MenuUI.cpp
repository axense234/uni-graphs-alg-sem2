#include "MenuUI.h"
#include "MenuController.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

std::vector<std::pair<std::string, Command>> MenuUI::constructAvailableCommands(MenuController controller)
{
    return std::vector<std::pair<std::string, Command>>{
        {"count vertices", {PROPERTY, "get the current number of vertices of the graph.\n", [controller]()
                            { controller.displayCurrentNbVertices(); }}},

        {"count edges", {PROPERTY, "get the current number of edges of the graph.\n", [controller]()
                         { controller.displayCurrentNbEdges(); }}},

        {"vertices", {PROPERTY, "display the vertices of the graph.\n", [controller]()
                      { controller.displayGraphVertices(); }}},

        {"edges", {PROPERTY, "display the edges of the graph (with cost included).\n", [controller]()
                   { controller.displayGraphEdges(); }}},

        {"outboundEdges", {PROPERTY, "display the outbound edges of a given vertex.\n", [controller]()
                           { controller.displayOutboundEdgesOfGivenVertex(); }}},

        {"inboundEdges", {PROPERTY, "display the inbound edges of a given vertex.\n", [controller]()
                          { controller.displayInboundEdgesOfGivenVertex(); }}},

        {"isEdge", {PROPERTY, "check if a given edge is an edge of the graph.\n", [controller]()
                    { controller.checkIfGivenEdgeIsGraphEdge(); }}},

        {"inDegree", {PROPERTY, "get the in-degree of a given vertex.\n", [controller]()
                      { controller.displayInDegreeOfGivenVertex(); }}},

        {"outDegree", {PROPERTY, "get the out-degree of a given vertex.\n", [controller]()
                       { controller.displayOutDegreeOfGivenVertex(); }}},

        {"add vertex", {MUTATION, "add a given vertex to the graph.\n", [controller]() mutable
                        { controller.addGivenVertexToGraph(); }}},

        {"remove vertex", {MUTATION, "remove a given vertex from the graph.\n", [controller]() mutable
                           { controller.removeGivenVertexFromGraph(); }}},

        {"add edge", {MUTATION, "add a given edge to the graph.\n", [controller]() mutable
                      { controller.addGivenEdgeToGraph(); }}},

        {"remove edge", {MUTATION, "remove a given edge from the graph.\n", [controller]() mutable
                         { controller.removeGivenEdgeFromGraph(); }}},

        {"generate random graph", {UTILITY, "generate a random graph with given nb of vertices and given nb of edges, this newly generated graph replaces the current graph.\n", [controller]() mutable
                                   { controller.generateRandomGraphOfGivenNbVerticesAndNbEdges(); }}},

        {"read graph", {UTILITY, "read from a given file graph data, this updates the current graph.\n", [controller]() mutable
                        { controller.readGraphDataFromGivenFile(); }}},

        {"write graph", {UTILITY, "write to a given filename graph data.\n", [controller]() mutable
                         { controller.writeGraphDataToGivenFile(); }}},

        {"exit", {UTILITY, "exit program.\n", []()
                  { std::exit(0); }}},

        {"help", {UTILITY, "display the available commands.\n", [this]()
                  { this->help(); }}},

        {"llp", {UTILITY, "find lowest length path between 2 vertices.\n", [controller]()
                 { controller.findLowestLengthPathBetweenTwoGivenVertices(); }}},

        {"ccug", {UTILITY, "finds the connected components of an undirected graph (transformed from directed to undirected)\n", [controller]() mutable
                  { controller.findConnectedComponentsOfGivenUndirectedGraph(); }}},
        {"dijkstra", {UTILITY, "finds the minimum cost walk between 2 given vertices", [controller]() mutable
                      {
                          controller.findMinimumCostWalkBetweenTwoGivenVertices();
                      }}}};
};

MenuUI::MenuUI(ADTDirectedGraph &g) : graph(g)
{
    this->userCommand = "";
}

void MenuUI::help()
{
    MenuController menuController = this->controller();
    std::vector<std::pair<std::string, Command>> availableCommands = this->constructAvailableCommands(menuController);

    std::cout
        << "\n -> graphs algorithms practice 2 <- \n";
    COMMAND_CATEGORY currentCategory = NONE;

    for (const auto &command : availableCommands)
    {
        if (currentCategory != command.second.category)
        {
            std::cout << "\n-------------------------------------------" << "-------------------------------------------\n";
            currentCategory = command.second.category;
        }
        std::cout << command.first << ": " << command.second.description;
    }
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

std::string MenuUI::getUserCommand() const
{
    std::string command;
    std::getline(std::cin, command);
    return command;
}

void MenuUI::start()
{

    this->help();
    MenuController menuController = this->controller();
    std::vector<std::pair<std::string, Command>> builtCommands = this->constructAvailableCommands(menuController);

    while (true)
    {
        this->userCommand = this->getUserCommand();
        if (!this->userCommand.empty())
        {
            auto foundIt = std::find_if(builtCommands.begin(), builtCommands.end(), [this](const std::pair<std::string, Command> &pair)
                                        { return pair.first == this->userCommand; });

            if (foundIt == builtCommands.end())
            {
                std::cout << "invalid command, type 'help' for available commands" << std::endl;
                continue;
            }
            else
            {
                std::pair<std::string, Command> command = *foundIt;
                command.second.funcUsed();
            }
        }
    }
}

MenuController MenuUI::controller() const
{
    return MenuController(*this, this->graph);
}