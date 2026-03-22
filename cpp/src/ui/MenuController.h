#pragma once

#include "MenuUI.h"

class MenuController
{

    friend class MenuUI;

private:
    const MenuUI &ui;
    ADTDirectedGraph &graph;

    /**
     * @brief Constructor.
     *
     * @param ui MenuUI dependency.
     */
    MenuController(const MenuUI &u, ADTDirectedGraph &g);

public:
    void displayCurrentNbVertices() const;
    void displayCurrentNbEdges() const;

    void displayGraphVertices() const;
    void displayGraphEdges() const;
    void displayOutboundEdgesOfGivenVertex() const;
    void displayInboundEdgesOfGivenVertex() const;

    void checkIfGivenEdgeIsGraphEdge() const;
    void displayInDegreeOfGivenVertex() const;
    void displayOutDegreeOfGivenVertex() const;

    void addGivenVertexToGraph();
    void removeGivenVertexFromGraph();
    void addGivenEdgeToGraph();
    void removeGivenEdgeFromGraph();

    void generateRandomGraphOfGivenNbVerticesAndNbEdges();
    void readGraphDataFromGivenFile();
    void writeGraphDataToGivenFile();
};