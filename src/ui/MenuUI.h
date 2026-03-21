#pragma once

#include "../domain/ADTDirectedGraph.h"

// forward declaration
class MenuController;

class MenuUI
{
    friend class MenuController;

private:
    ADTDirectedGraph graph;

    unsigned short userMenuOption;

public:
    /**
     * @brief Construct a new Menu UI object
     *
     * @param g Graph dependency.
     */
    MenuUI();

    /**
     * @brief Starts the menu application :).
     *
     */
    void start();

    /**
     * @brief Displays the available menu options.
     *
     */
    void displayMenuOptions() const;

    /**
     * @brief Gets an unsigned int from the console.
     *
     * @param label Display label.
     * @return unsigned int
     */
    unsigned int getUserUnsignedInt(char *label) const;

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

    MenuController controller() const;
};