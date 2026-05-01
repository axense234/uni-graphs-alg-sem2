#pragma once

#include "MenuUI.h"
#include "../domain/ADTUndirectedGraph.h"
#include "../domain/ADTDirectedGraph.h"

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

    void findLowestLengthPathBetweenTwoGivenVertices() const;
    void findConnectedComponentsOfGivenUndirectedGraph();

    void findMinimumCostWalkBetweenTwoGivenVertices();

    /**
     * @brief Converts a ADTDirectedGraph instance into a ADTUndirectedGraph instance and returns it.
     *
     * this should probably go somewhere else but ehh
     */
    ADTUndirectedGraph convertToUndirected(const ADTDirectedGraph &directedGraph);
};