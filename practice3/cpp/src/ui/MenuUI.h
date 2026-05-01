#pragma once

#include "../domain/ADTDirectedGraph.h"
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <utility>

class MenuController;

enum COMMAND_CATEGORY
{
    PROPERTY,
    MUTATION,
    UTILITY,
    NONE
};

struct Command
{
    COMMAND_CATEGORY category;
    std::string description;
    std::function<void()> funcUsed;
};

class MenuUI
{
    friend class MenuController;

private:
    ADTDirectedGraph &graph;

    std::string userCommand;

public:
    /**
     * @brief Construct a new Menu UI object
     *
     * @param g Graph dependency.
     */
    MenuUI(ADTDirectedGraph &g);

    /**
     * @brief Starts the menu application :).
     *
     */
    void start();

    /**
     * @brief Displays the available commands.
     *
     */
    void help();

    std::vector<std::pair<std::string, Command>> constructAvailableCommands(MenuController controller);

    /**
     * @brief Gets the user command from the console.
     *
     * @return std::string command.
     *
     */
    std::string getUserCommand() const;

    /**
     * @brief Gets an unsigned int from the console.
     *
     * @param label Display label.
     * @return unsigned int
     */
    unsigned int getUserUnsignedInt(const std::string &label) const;

    /**
     * @brief Gets a Vertex from the console.
     *
     * @return Vertex
     */
    Vertex getUserVertex() const;

    /**
     * @brief Gets an Edge from the console.
     *
     * @return Edge
     */
    Edge getUserEdge() const;

    /**
     * @brief Get an Edge Cost from the console.
     *
     * @return EdgeCost
     */
    EdgeCost getUserEdgeCost() const;

    /**
     * @brief Gets a filename from the console.
     *
     * @return string
     */
    std::string getUserFilename() const;

    /**
     * @brief Returns a newly created controller instance.
     *
     * @return MenuController
     */
    MenuController controller() const;
};