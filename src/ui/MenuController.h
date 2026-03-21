#pragma once

#include "MenuUI.h"

class MenuController
{

    friend class MenuUI;

private:
    MenuUI &ui;

    /**
     * @brief Constructor.
     *
     * @param ui MenuUI dependency.
     */
    MenuController(MenuUI &u);

public:
    void displayCurrentNbVertices();
    void displayCurrentNbEdges();

    void displayGraphVertices();
    void displayOutboundEdgesOfGivenVertex();
    void displayInboundEdgesOfGivenVertex();

    void checkIfGivenEdgeIsGraphEdge();
    void displayInDegreeOfGivenVertex();
    void displayOutDegreeOfGivenVertex();

    void addGivenVertexToGraph();
    void removeGivenVertexFromGraph();
    void addGivenEdgeToGraph();
    void removeGivenEdgeFromGraph();

    void generateRandomGraphOfGivenNbVerticesAndNbEdges();
    void readGraphDataFromGivenFile();
    void writeGraphDataToGivenFile();
};